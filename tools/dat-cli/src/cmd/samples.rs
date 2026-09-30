//! `samples`: one instance of each archive type, compared with objdiff.
//!
//! `build` writes, under the configured directory:
//! - `target/<unit>.o`: the sampled bytes from the archives
//! - `src/<unit>.c`: C generated from the current types
//! - `base/<unit>.o`: that C, compiled like the game's code
//! - `objdiff.json`: a project pairing them
//!
//! `report` compares them. Edit a type, rebuild the DWARF, and run both
//! again.

use super::project::{Check, Project};
use anyhow::{Context, Result, bail};
use globset::{Glob, GlobSet, GlobSetBuilder};
use melee_dat::{
    config::get_config,
    hsd::Archive,
    samples::{CWriter, Picker, Sample, Skipped, Source, target_object},
};
use rayon::prelude::*;
use serde::Serialize;
use serde_json::json;
use std::{
    collections::BTreeMap,
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
    /// List the samples: one instance of each type the walk finds
    List(List),

    /// Write the target objects and C, and compile the C
    Build(Build),

    /// Compare the samples with objdiff
    Report(Report),
}

#[derive(clap::Args)]
struct List {
    #[command(flatten)]
    check: Check,
    #[arg(long)]
    json: bool,
}

#[derive(clap::Args)]
struct Build {
    #[command(flatten)]
    check: Check,
    /// Only units whose name matches (glob; repeatable)
    #[arg(short, long)]
    unit: Vec<String>,
}

#[derive(clap::Args)]
struct Report {
    /// Project config
    #[arg(default_value = "config/GALE01/dat.yml")]
    cfg_path: PathBuf,
    #[arg(short = 'p', long)]
    proj_path: Option<PathBuf>,
    /// Print objdiff's report instead of the table
    #[arg(long)]
    json: bool,
}

pub fn run(Args { command }: Args) -> Result<()> {
    match command {
        Command::List(args) => list(args),
        Command::Build(args) => build(args),
        Command::Report(args) => report(args),
    }
}

/// The samples and the types that have none.
fn pick(project: &Project) -> Result<(Vec<Sample>, Vec<Skipped>)> {
    let mut picker = Picker::new(&project.graph, &project.canonical);
    project.walk_all(&GlobSet::empty(), |w| {
        let offset = w
            .name
            .split_once('@')
            .and_then(|(_, o)| usize::from_str_radix(&o[2..], 16).ok())
            .unwrap_or(0);
        picker.add(w.file, offset, w.archive, &w.result);
        Ok(())
    })?;
    Ok(picker.finish())
}

#[derive(Serialize)]
struct Row<'a> {
    #[serde(rename = "type")]
    ty: &'a str,
    symbol: String,
    unit: &'a str,
    file: &'a str,
    archive: usize,
    offset: u32,
    size: u64,
    relocations: usize,
}

fn list(args: List) -> Result<()> {
    let project = Project::load(&args.check)?;
    let (samples, skipped) = pick(&project)?;
    let rows: Vec<Row> = samples
        .iter()
        .map(|s| Row {
            ty: &s.type_name,
            symbol: s.symbol(),
            unit: s.unit(),
            file: &s.location.file,
            archive: s.location.archive,
            offset: s.location.offset,
            size: s.size,
            relocations: s.relocs,
        })
        .collect();
    let mut out = io::stdout().lock();
    if args.json {
        let skipped: BTreeMap<&str, &str> = skipped
            .iter()
            .map(|s| (s.type_name.as_str(), s.reason.as_str()))
            .collect();
        let report = json!({ "samples": rows, "skipped": skipped });
        serde_json::to_writer_pretty(&mut out, &report)?;
        writeln!(out)?;
        return Ok(());
    }
    for r in &rows {
        let archive = match r.archive {
            0 => String::new(),
            a => format!("@0x{a:X}"),
        };
        writeln!(
            out,
            "{}: {} ({:#X} bytes, {} relocations) from {}{archive} at 0x{:X}",
            r.unit, r.ty, r.size, r.relocations, r.file, r.offset
        )?;
    }
    for s in &skipped {
        writeln!(out, "skipped: {} ({})", s.type_name, s.reason)?;
    }
    let mut units: Vec<_> = rows.iter().map(|r| r.unit).collect();
    units.sort();
    units.dedup();
    eprintln!(
        "{} samples in {} units, {} types skipped",
        rows.len(),
        units.len(),
        skipped.len()
    );
    Ok(())
}

/// The samples directory and the game object whose compile command
/// samples reuse.
fn samples_config(
    cfg_path: &Path,
    proj_path: Option<&PathBuf>,
) -> Result<(PathBuf, PathBuf)> {
    let config = get_config(proj_path, cfg_path)?;
    let proj = proj_path.cloned().unwrap_or_default();
    Ok((
        proj.join(config.samples.dir.as_str()),
        PathBuf::from(config.samples.compile_like.as_str()),
    ))
}

/// The command `ninja` runs for `object`, with `{in}` and `{outdir}` in
/// place of its source and output directory.
fn compile_template(object: &Path) -> Result<String> {
    let output = Process::new("ninja")
        .args(["-t", "commands"])
        .arg(object)
        .output()
        .context("running ninja")?;
    if !output.status.success() {
        bail!(
            "ninja -t commands {}: {}",
            object.display(),
            String::from_utf8_lossy(&output.stderr)
        );
    }
    let commands = String::from_utf8(output.stdout)?;
    let command = commands.lines().last().context("no command")?;
    // The compile itself, without the dependency file handling after it
    let command = command.split(" && ").next().unwrap_or(command);
    let words: Vec<&str> = command.split(' ').collect();
    let mut out = Vec::new();
    let mut i = 0;
    while i < words.len() {
        match words[i] {
            "-MMD" => {}
            "-c" => {
                out.push("-c {in}".to_owned());
                i += 1;
            }
            "-o" => {
                out.push("-o {outdir}".to_owned());
                i += 1;
            }
            word => out.push(word.to_owned()),
        }
        i += 1;
    }
    let template = out.join(" ");
    if !template.contains("{in}") || !template.contains("{outdir}") {
        bail!("no -c and -o in: {command}");
    }
    Ok(template)
}

/// The `-i` directories of a compile command.
fn include_dirs(template: &str) -> Vec<PathBuf> {
    let words: Vec<&str> = template.split(' ').collect();
    words
        .windows(2)
        .filter(|w| w[0] == "-i")
        .map(|w| PathBuf::from(w[1]))
        .collect()
}

/// `header` if an include directory has it, else the nearest parent
/// header that one does (`dolphin/mtx/GeoTypes.h` to `dolphin/mtx.h`).
fn find_header(dirs: &[PathBuf], header: &str) -> String {
    let exists = |h: &str| dirs.iter().any(|d| d.join(h).is_file());
    let mut candidate = header.to_owned();
    loop {
        if exists(&candidate) {
            return candidate;
        }
        let stem = candidate.strip_suffix(".h").unwrap_or(&candidate);
        match stem.rsplit_once('/') {
            Some((parent, _)) => candidate = format!("{parent}.h"),
            None => return header.to_owned(),
        }
    }
}

fn build(args: Build) -> Result<()> {
    let (dir, compile_like) =
        samples_config(&args.check.cfg_path, args.check.proj_path.as_ref())?;
    let template = compile_template(&compile_like)?;
    let project = Project::load(&args.check)?;
    let (mut samples, _) = pick(&project)?;
    // The DWARF build's headers aren't always the game's; include what
    // the game's compiler can find
    let dirs = include_dirs(&template);
    for sample in &mut samples {
        sample.header = find_header(&dirs, &sample.header);
        for include in &mut sample.includes {
            *include = find_header(&dirs, include);
        }
    }

    let mut filter = GlobSetBuilder::new();
    for glob in &args.unit {
        filter.add(Glob::new(glob)?);
    }
    let filter = filter.build()?;
    let mut units: BTreeMap<String, Vec<Sample>> = BTreeMap::new();
    for sample in samples {
        let unit = sample.unit().to_owned();
        if args.unit.is_empty() || filter.is_match(&unit) {
            units.entry(unit).or_default().push(sample);
        }
    }

    // Each archive a sample reads, parsed once
    let mut files: BTreeMap<String, Vec<u8>> = BTreeMap::new();
    for sample in units.values().flatten() {
        let file = &sample.location.file;
        if !files.contains_key(file) {
            let path = project.base.join(file);
            let bytes = fs::read(&path)
                .with_context(|| format!("{}", path.display()))?;
            files.insert(file.clone(), bytes);
        }
    }
    let mut archives: BTreeMap<(&str, usize), Archive> = BTreeMap::new();
    for (file, bytes) in &files {
        for (at, archive) in Archive::parse_packed(bytes)? {
            archives.insert((file, at), archive);
        }
    }
    let sources: BTreeMap<(&str, usize), Source> =
        archives.iter().map(|(&k, a)| (k, Source::new(a))).collect();

    // Start clean, so units that no longer exist don't linger
    for sub in ["target", "src", "base"] {
        let _ = fs::remove_dir_all(dir.join(sub));
    }
    let writer = CWriter::new(&project.graph, &project.canonical);
    for (unit, samples) in &units {
        let pairs: Vec<(&Sample, &Source)> = samples
            .iter()
            .map(|s| {
                let key = (s.location.file.as_str(), s.location.archive);
                (s, &sources[&key])
            })
            .collect();
        let target = dir.join("target").join(format!("{unit}.o"));
        fs::create_dir_all(target.parent().unwrap())?;
        fs::write(&target, target_object(&pairs)?)?;
        let source = dir.join("src").join(format!("{unit}.c"));
        fs::create_dir_all(source.parent().unwrap())?;
        fs::write(&source, writer.unit(&pairs)?)?;
    }

    // Compile every unit like the game's code
    let names: Vec<&String> = units.keys().collect();
    let failed: Vec<(String, String)> = names
        .par_iter()
        .filter_map(|unit| {
            let source = dir.join("src").join(format!("{unit}.c"));
            let base = dir.join("base").join(format!("{unit}.o"));
            let outdir = base.parent()?.to_owned();
            let _ = fs::create_dir_all(&outdir);
            let command = template
                .replace("{in}", &source.to_string_lossy())
                .replace("{outdir}", &outdir.to_string_lossy());
            match Process::new("sh").arg("-c").arg(&command).output() {
                Ok(o) if o.status.success() => None,
                Ok(o) => Some((
                    unit.to_string(),
                    String::from_utf8_lossy(&o.stdout).into_owned()
                        + &String::from_utf8_lossy(&o.stderr),
                )),
                Err(e) => Some((unit.to_string(), e.to_string())),
            }
        })
        .collect();
    for (unit, log) in &failed {
        eprintln!("{unit}: doesn't compile:\n{}", log.trim_end());
    }

    // An objdiff project over the directory
    let project_units: Vec<_> = units
        .keys()
        .map(|unit| {
            json!({
                "name": format!("dat/{unit}"),
                "target_path": format!("target/{unit}.o"),
                "base_path": format!("base/{unit}.o"),
                "metadata": {
                    "progress_categories": ["dat"],
                    "source_path": format!("src/{unit}.c"),
                },
            })
        })
        .collect();
    let objdiff = json!({
        "min_version": "2.0.0-beta.5",
        "build_target": false,
        "build_base": false,
        "progress_categories": [{ "id": "dat", "name": "Archive samples" }],
        "units": project_units,
    });
    fs::create_dir_all(&dir)?;
    fs::write(
        dir.join("objdiff.json"),
        serde_json::to_string_pretty(&objdiff)?,
    )?;
    eprintln!(
        "{} units in {}: {} compiled, {} failed",
        units.len(),
        dir.display(),
        units.len() - failed.len(),
        failed.len()
    );
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
        let percent = |n: f64, d: f64| if d == 0.0 { 100.0 } else { n * 100.0 / d };
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
}

/// objdiff's diff of one unit: each sample's match.
fn diff_unit(dir: &Path, unit: &str) -> Result<Vec<SampleMatch>> {
    let output = Process::new("objdiff-cli")
        .args(["diff", "-p"])
        .arg(dir)
        .args(["-u", unit, "-o", "-"])
        .output()
        .context("running objdiff-cli")?;
    if !output.status.success() {
        bail!(
            "objdiff-cli diff -u {unit}: {}",
            String::from_utf8_lossy(&output.stderr)
        );
    }
    let diff: serde_json::Value = serde_json::from_slice(&output.stdout)?;
    let symbols = diff["left"]["symbols"].as_array().cloned().unwrap_or_default();
    Ok(symbols
        .iter()
        .filter_map(|s| {
            let name = s["name"].as_str()?;
            if !name.starts_with("sample_") {
                return None;
            }
            let size = s["size"].as_str().and_then(|v| v.parse().ok()).unwrap_or(0);
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
    let (dir, _) = samples_config(&args.cfg_path, args.proj_path.as_ref())?;
    let project: serde_json::Value = serde_json::from_str(
        &fs::read_to_string(dir.join("objdiff.json"))
            .context("no objdiff.json: run `samples build` first")?,
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
            let samples = diff_unit(&dir, name)?;
            let mut measures = MatchMeasures::default();
            for sample in &samples {
                measures.add(sample);
            }
            Ok(UnitMatch {
                name: name.trim_start_matches("dat/").to_owned(),
                measures,
                samples,
            })
        })
        .collect::<Result<_>>()?;
    let mut total = MatchMeasures::default();
    for unit in &units {
        total.merge(&unit.measures);
    }

    let mut out = io::stdout().lock();
    if args.json {
        let report = json!({ "version": 1, "measures": total, "units": units });
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
            s.match_percent,
            s.name.trim_start_matches("sample_"),
            s.size
        )?;
    }
    writeln!(
        out,
        "{}/{} samples match, {:.2}% of their bytes",
        total.matched_samples, total.total_samples, total.matched_data_percent
    )?;
    Ok(())
}
