//! `samples`: archive data typed by the DWARF, compared with objdiff.
//!
//! One unit per archive file, each built in steps a build system runs:
//! - `slice`: the archive → `target/<unit>.o`, its sampled objects under
//!   their archive names, plus `target/<unit>.samples` saying what each is
//! - `codegen`: the target object → `src/<unit>.c`, generated from the types
//! - (the build compiles `src/<unit>.c` to `base/<unit>.o`)
//! - `project`: every unit's sidecar → `objdiff.json`
//!
//! `report` compares the built units.

use super::project::{Check, Project};
use anyhow::{Context, Result, bail};
use globset::{Glob, GlobSetBuilder};
use melee_dat::{
    dwarf::{TypeGraph, cache::TypesFile, canonical::Canonical},
    hsd::Archive,
    samples::{
        CWriter, Instance, Picker, SampleInfo, Source, root_of, target_object,
    },
};
use object::{
    Object, ObjectSection, ObjectSymbol, RelocationTarget, SectionKind,
};
use rayon::prelude::*;
use serde::{Deserialize, Serialize};
use serde_json::json;
use std::{
    collections::{BTreeMap, BTreeSet},
    fs,
    io::{self, Write},
    path::{Path, PathBuf},
    process::Command as Process,
};

#[derive(clap::Args)]
pub struct Args {
    #[command(subcommand)]
    command: Command,
}

#[derive(clap::Subcommand)]
enum Command {
    /// Write an archive's samples as a target object, with a sidecar
    Slice(Slice),

    /// Write the C for a target object's samples, from the types
    Codegen(Codegen),

    /// Write the objdiff project for the units' sidecars
    Project(ProjectArgs),

    /// Compare the built units' samples
    Report(Report),
}

#[derive(clap::Args)]
struct Slice {
    /// The archive, relative to the archives' directory, e.g. `PlMr.dat`
    archive: String,
    #[command(flatten)]
    check: Check,
    /// The target object; its sidecar is written next to it as `.samples`
    #[arg(short, long)]
    output: PathBuf,
    /// Every typed object, not just the best instance of each type
    #[arg(long)]
    all: bool,
    /// Types never to sample, as globs on their names (e.g.
    /// `HSD_VtxDescList`); data they point to stays bytes
    #[arg(long)]
    exclude: Vec<String>,
}

#[derive(clap::Args)]
struct Codegen {
    /// The target object, with its sidecar next to it
    target: PathBuf,
    /// ELF or object with DWARF [default: $MELEE_DWARF_ELF]
    #[arg(long)]
    dwarf: Option<PathBuf>,
    /// The compact types file from `types export`, instead of the DWARF
    #[arg(long, conflicts_with = "dwarf")]
    types: Option<PathBuf>,
    #[arg(short, long)]
    output: PathBuf,
}

#[derive(clap::Args)]
struct ProjectArgs {
    /// The units' sidecars (`target/<unit>.samples`)
    sidecars: Vec<PathBuf>,
    /// `objdiff.json`; its directory is the project's, with `target/`,
    /// `src/` and `base/`
    #[arg(short, long)]
    output: PathBuf,
}

#[derive(clap::Args)]
struct Report {
    /// The project directory
    #[arg(default_value = "build/GALE01/dat")]
    dir: PathBuf,
    #[arg(long)]
    json: bool,
}

pub fn run(Args { command }: Args) -> Result<()> {
    match command {
        Command::Slice(args) => slice(args),
        Command::Codegen(args) => codegen(args),
        Command::Project(args) => project(args),
        Command::Report(args) => report(args),
    }
}

/// What `slice` writes next to a target object.
#[derive(Serialize, Deserialize)]
struct Sidecar {
    /// The archive file, e.g. `PlMr.dat`.
    archive: String,
    samples: Vec<SampleInfo>,
    /// Everything else the samples point to, by name, with its root.
    externs: BTreeMap<String, String>,
}

fn sidecar_path(target: &Path) -> PathBuf {
    target.with_extension("samples")
}

fn read_sidecar(path: &Path) -> Result<Sidecar> {
    let bytes =
        fs::read(path).with_context(|| format!("{}", path.display()))?;
    postcard::from_bytes(&bytes).with_context(|| format!("{}", path.display()))
}

fn slice(args: Slice) -> Result<()> {
    let project = Project::load(&args.check)?;
    let path = project.base.join(&args.archive);
    let bytes =
        fs::read(&path).with_context(|| format!("{}", path.display()))?;
    let archives = Archive::parse_packed(&bytes)
        .with_context(|| format!("{}", path.display()))?;

    // This archive's best instance of each type and variant
    let mut exclude = GlobSetBuilder::new();
    for glob in &args.exclude {
        exclude.add(Glob::new(glob)?);
    }
    let mut picker = Picker::new(&project.graph, &project.canonical)
        .select(args.all, exclude.build()?);
    let mut walks = BTreeMap::new();
    for (at, archive) in &archives {
        let (_, walk) = project.walk(&args.archive, archive);
        picker.add(&args.archive, *at, archive, &walk);
        walks.insert(*at, walk);
    }
    let (mut samples, _) = picker.finish();
    samples.sort_by_key(|s| (s.location.archive, s.location.offset));

    let sources: BTreeMap<usize, Source> = archives
        .iter()
        .map(|(at, a)| (*at, Source::new(a, *at)))
        .collect();
    let pairs: Vec<_> = samples
        .iter()
        .map(|s| (s, &sources[&s.location.archive]))
        .collect();
    let picker = Picker::new(&project.graph, &project.canonical);
    let mut infos = Vec::new();
    let mut names = BTreeSet::new();
    for (sample, source) in &pairs {
        let name = source.name(sample.location.offset);
        if !names.insert(name.clone()) {
            bail!("{}: two samples named {name}", args.archive);
        }
        infos.push(picker.info(sample, name));
    }
    // The other data the samples point to belongs to the root of the
    // object it is in: the nearest one the walk reached at or before it
    let mut externs = BTreeMap::new();
    for (sample, source) in &pairs {
        let paths = &walks[&sample.location.archive].paths;
        for (_, target) in source.relocs(sample.location.offset, sample.size) {
            let name = source.name(target);
            if !names.contains(&name) {
                let root = paths
                    .range(..=target)
                    .next_back()
                    .map_or("unknown", |(_, path)| root_of(path));
                externs.entry(name).or_insert_with(|| root.to_owned());
            }
        }
    }

    if let Some(dir) = args.output.parent() {
        fs::create_dir_all(dir)?;
    }
    fs::write(&args.output, target_object(&pairs)?)?;
    // The target's order, for linking the base object's `.data` the same:
    // clang lays variables out where an initializer first points to them
    let mut script = String::from("SECTIONS\n{\n    .data : {\n");
    for info in &infos {
        script += &format!("        *(.data.{})\n", info.symbol);
    }
    script += "        *(.data .data.*)\n    }\n}\n";
    fs::write(args.output.with_extension("ld"), script)?;
    let sidecar = Sidecar {
        archive: args.archive,
        samples: infos,
        externs,
    };
    fs::write(sidecar_path(&args.output), postcard::to_stdvec(&sidecar)?)?;
    Ok(())
}

fn codegen(args: Codegen) -> Result<()> {
    let sidecar = read_sidecar(&sidecar_path(&args.target))?;
    let data = fs::read(&args.target)
        .with_context(|| format!("{}", args.target.display()))?;
    let obj = object::File::parse(&*data)?;

    // Each symbol's bytes and relocations, from the object
    let section = obj.section_by_name(".data");
    let bytes = match &section {
        Some(section) => section.data()?,
        None => &[],
    };
    let mut relocs: BTreeMap<u64, String> = BTreeMap::new();
    if let Some(section) = &section {
        for (at, reloc) in section.relocations() {
            if let RelocationTarget::Symbol(id) = reloc.target() {
                let name = obj.symbol_by_index(id)?.name()?.to_owned();
                relocs.insert(at, name);
            }
        }
    }
    let symbols: BTreeMap<&str, (u64, u64)> = obj
        .symbols()
        .filter(|s| s.is_definition())
        .filter_map(|s| Some((s.name().ok()?, (s.address(), s.size()))))
        .collect();
    let instances = sidecar
        .samples
        .iter()
        .map(|info| {
            let &(at, size) = symbols
                .get(info.symbol.as_str())
                .with_context(|| format!("no symbol {}", info.symbol))?;
            Ok(Instance {
                info,
                bytes: &bytes[at as usize..(at + size) as usize],
                relocs: relocs
                    .range(at..at + size)
                    .map(|(&r, name)| ((r - at) as u32, name.clone()))
                    .collect(),
            })
        })
        .collect::<Result<Vec<_>>>()?;

    let graph = match &args.types {
        Some(path) => TypesFile::load(path)?.graph,
        None => TypeGraph::load(super::dwarf_path(args.dwarf)?)?,
    };
    let canonical = Canonical::new(&graph);
    let roots = CWriter::new(&graph, &canonical).unit(
        &sidecar.archive,
        &instances,
        &sidecar.externs,
    )?;

    // A directory of each root's header and source, next to the unit's
    // file, which includes the sources: `src/PlMr/ftDataMario.{h,c}`,
    // `src/PlMr.c`
    let stem = args
        .output
        .file_stem()
        .context("output without a name")?
        .to_string_lossy()
        .into_owned();
    let dir = args.output.with_extension("");
    if dir.exists() {
        fs::remove_dir_all(&dir)?;
    }
    fs::create_dir_all(&dir)?;
    let mut unit = format!(
        "/**\n * @file\n \
         * The samples of every root in `{}`.\n \
         * Generated by `melee-dat samples codegen`.\n */\n\n",
        sidecar.archive
    );
    for root in &roots {
        fs::write(dir.join(format!("{}.h", root.name)), &root.header)?;
        unit += &format!("#include \"{stem}/{}.h\"\n", root.name);
    }
    for root in &roots {
        if let Some(source) = &root.source {
            fs::write(dir.join(format!("{}.c", root.name)), source)?;
            unit += &format!("#include \"{stem}/{}.c\"\n", root.name);
        }
    }
    fs::write(&args.output, unit)?;
    Ok(())
}

fn project(args: ProjectArgs) -> Result<()> {
    let mut units = Vec::new();
    for path in &args.sidecars {
        let sidecar = read_sidecar(path)?;
        if sidecar.samples.is_empty() {
            continue;
        }
        let unit = path
            .file_stem()
            .context("sidecar without a name")?
            .to_string_lossy()
            .into_owned();
        units.push(json!({
            "name": unit,
            "target_path": format!("target/{unit}.o"),
            "base_path": format!("base/{unit}.o"),
            "metadata": {
                "complete": false,
                "source_path": format!("src/{unit}.c"),
                "progress_categories": ["dat"],
                "auto_generated": false,
            },
        }));
    }
    let objdiff = json!({
        "min_version": "2.0.0-beta.5",
        // The build that writes this file, so objdiff can rebuild a base
        // object with `ninja base/<unit>.o`
        "custom_make": "ninja",
        "build_target": false,
        "build_base": true,
        "progress_categories": [{ "id": "dat", "name": "Dat Samples" }],
        "units": units,
    });
    if let Some(dir) = args.output.parent() {
        fs::create_dir_all(dir)?;
    }
    fs::write(&args.output, serde_json::to_string_pretty(&objdiff)? + "\n")?;
    Ok(())
}

/// A sample's match, from objdiff's diff of its unit.
#[derive(Serialize, Clone)]
struct SampleMatch {
    name: String,
    size: u64,
    match_percent: f64,
}

#[derive(Serialize, Default, Clone)]
struct MatchMeasures {
    total_samples: u64,
    matched_samples: u64,
    matched_samples_percent: f64,
    total_data: u64,
    /// Bytes, weighted by each sample's match.
    matched_data: f64,
    matched_data_percent: f64,
}

impl MatchMeasures {
    fn add(&mut self, sample: &SampleMatch) {
        self.total_samples += 1;
        self.matched_samples += u64::from(sample.match_percent >= 100.0);
        self.total_data += sample.size;
        self.matched_data += sample.size as f64 * sample.match_percent / 100.0;
        self.finish();
    }

    fn merge(&mut self, other: &MatchMeasures) {
        self.total_samples += other.total_samples;
        self.matched_samples += other.matched_samples;
        self.total_data += other.total_data;
        self.matched_data += other.matched_data;
        self.finish();
    }

    fn finish(&mut self) {
        let percent =
            |n: f64, d: f64| if d == 0.0 { 100.0 } else { n * 100.0 / d };
        self.matched_samples_percent =
            percent(self.matched_samples as f64, self.total_samples as f64);
        self.matched_data_percent =
            percent(self.matched_data, self.total_data as f64);
    }
}

#[derive(Serialize)]
struct UnitMatch {
    name: String,
    measures: MatchMeasures,
    samples: Vec<SampleMatch>,
    /// The base object's contents outside `.data`, e.g. code or strings
    /// from headers, which the target doesn't have.
    extra: Vec<String>,
}

/// Allocated sections of a unit's base object other than `.data`, with
/// their sizes.
fn extra_sections(dir: &Path, unit: &str) -> Result<Vec<String>> {
    let path = dir.join(format!("base/{unit}.o"));
    let data =
        fs::read(&path).with_context(|| format!("{}", path.display()))?;
    let obj = object::File::parse(&*data)?;
    Ok(obj
        .sections()
        .filter(|s| s.size() > 0 && s.name() != Ok(".data"))
        .filter(|s| {
            matches!(
                s.kind(),
                SectionKind::Text
                    | SectionKind::Data
                    | SectionKind::ReadOnlyData
                    | SectionKind::ReadOnlyDataWithRel
                    | SectionKind::ReadOnlyString
                    | SectionKind::UninitializedData
            )
        })
        .map(|s| {
            format!("{} ({:#X} bytes)", s.name().unwrap_or("?"), s.size())
        })
        .collect())
}

/// objdiff's diff of one unit's target and base objects: each sample's
/// match.
fn diff_unit(dir: &Path, unit: &str) -> Result<Vec<SampleMatch>> {
    let target = dir.join("target").join(format!("{unit}.o"));
    let sidecar = read_sidecar(&sidecar_path(&target))?;
    let samples: BTreeSet<&str> =
        sidecar.samples.iter().map(|s| s.symbol.as_str()).collect();
    let output = Process::new("objdiff-cli")
        .arg("diff")
        .arg("-1")
        .arg(&target)
        .arg("-2")
        .arg(dir.join("base").join(format!("{unit}.o")))
        .args(["-o", "-"])
        .output()
        .context("running objdiff-cli")?;
    if !output.status.success() {
        bail!(
            "objdiff-cli diff {unit}: {}",
            String::from_utf8_lossy(&output.stderr)
        );
    }
    let diff: serde_json::Value = serde_json::from_slice(&output.stdout)?;
    let symbols = diff["left"]["symbols"]
        .as_array()
        .cloned()
        .unwrap_or_default();
    Ok(symbols
        .iter()
        .filter_map(|s| {
            let name = s["name"].as_str()?;
            if !samples.contains(name) {
                return None;
            }
            let size =
                s["size"].as_str().and_then(|v| v.parse().ok()).unwrap_or(0);
            // A symbol with no counterpart has no match percent
            let match_percent = s["match_percent"].as_f64().unwrap_or(0.0);
            Some(SampleMatch {
                name: name.to_owned(),
                size,
                match_percent,
            })
        })
        .collect())
}

fn report(args: Report) -> Result<()> {
    let project: serde_json::Value = serde_json::from_str(
        &fs::read_to_string(args.dir.join("objdiff.json")).with_context(
            || {
                format!(
                    "no objdiff.json in {}: build the samples first",
                    args.dir.display()
                )
            },
        )?,
    )?;
    let names: Vec<String> = project["units"]
        .as_array()
        .into_iter()
        .flatten()
        .filter_map(|u| u["name"].as_str().map(str::to_owned))
        .collect();
    let units: Vec<UnitMatch> = names
        .par_iter()
        .map(|name| {
            let samples = diff_unit(&args.dir, name)?;
            let mut measures = MatchMeasures::default();
            for sample in &samples {
                measures.add(sample);
            }
            Ok(UnitMatch {
                name: name.clone(),
                measures,
                samples,
                extra: extra_sections(&args.dir, name)?,
            })
        })
        .collect::<Result<_>>()?;
    let mut total = MatchMeasures::default();
    for unit in &units {
        total.merge(&unit.measures);
    }

    let mut out = io::stdout().lock();
    if args.json {
        let report =
            json!({ "version": 1, "measures": total, "units": units });
        serde_json::to_writer_pretty(&mut out, &report)?;
        writeln!(out)?;
        return Ok(());
    }
    // Only what doesn't match
    let mut rows: Vec<(&str, &SampleMatch)> = units
        .iter()
        .flat_map(|u| u.samples.iter().map(move |s| (u.name.as_str(), s)))
        .filter(|(_, s)| s.match_percent < 100.0)
        .collect();
    rows.sort_by(|a, b| a.1.match_percent.total_cmp(&b.1.match_percent));
    for (unit, s) in &rows {
        writeln!(
            out,
            "{:6.1}%  {}  ({unit}, {:#X} bytes)",
            s.match_percent, s.name, s.size
        )?;
    }
    for unit in &units {
        for section in &unit.extra {
            writeln!(out, "  extra  {section} in base/{}.o", unit.name)?;
        }
    }
    writeln!(
        out,
        "{}/{} samples match in {} units, {:.2}% of their bytes",
        total.matched_samples,
        total.total_samples,
        units.len(),
        total.matched_data_percent
    )?;
    Ok(())
}
