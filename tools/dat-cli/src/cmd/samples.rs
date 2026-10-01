//! `samples`: archive data typed by the DWARF, compared with objdiff.
//!
//! One unit per archive file, `<module>/<archive>` (`Pl/PlMr`), each built
//! in steps a build system runs:
//! - `slice`: the archive → `target/<unit>.o`, its sampled objects under
//!   their archive names and the rest by name and size (see
//!   [`target_object`]), plus `target/<unit>.samples` saying what each
//!   sample is, and for the base `target/<unit>.ld`, ordering its samples
//!   like the target's, and `target/<unit>.rest.o`, the rest the walk
//!   explains
//! - `codegen`: the target object → `src/<unit>.c`, generated from the types
//! - `macros`: `src/macros.h`, which every unit's C includes
//! - (the build compiles `src/<unit>.c` to `base/<unit>.o`)
//! - `project`: every unit's sidecar → `objdiff.json`
//!
//! `report` compares the built units.

use super::project::{Check, Project};
use anyhow::{Context, Result, bail};
use globset::{Glob, GlobSetBuilder};
use melee_dat::{
    coverage::{coverage, family},
    dwarf::{
        TypeGraph, cache::TypesFile, canonical::Canonical, render::Renderer,
    },
    hsd::Archive,
    samples::{
        CWriter, Elided, ElidedType, Instance, Picker, SampleInfo, Source, Unnamed,
        Piece, SAMPLED, INFERRED, assign_names, rest_object, root_of,
        target_object,
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
    /// Write a hash of the types an archive's roots lead to, if it changed:
    /// the unit's other steps depend on it instead of every type
    Types(TypesArgs),

    /// Write an archive's samples as a target object, with a sidecar
    Slice(Slice),

    /// Write the C for a target object's samples, from the types
    Codegen(Codegen),

    /// Write the definitions the generated C includes (`macros.h`)
    Macros(MacrosArgs),

    /// Write the objdiff project for the units' sidecars
    Project(ProjectArgs),

    /// Compare the built units' samples
    Report(Report),
}

#[derive(clap::Args)]
struct TypesArgs {
    /// The archive, relative to the archives' directory, e.g. `PlMr.dat`
    archive: String,
    #[command(flatten)]
    check: Check,
    /// The hash; left alone when unchanged, so that its dependents are too
    #[arg(short, long)]
    output: PathBuf,
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
struct MacrosArgs {
    /// Left alone when unchanged, so that its dependents are too
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
        Command::Types(args) => types(args),
        Command::Slice(args) => slice(args),
        Command::Codegen(args) => codegen(args),
        Command::Macros(args) => macros(args),
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
    /// The data in the archive the samples point to but that isn't written
    /// as C, by name.
    elided: BTreeMap<String, Elided>,
    /// The archive's externs the samples point to: other archives'
    /// symbols, which the loader links in by name.
    externs: BTreeSet<String>,
    /// Whether the types explain the whole file: every relocation, every
    /// public symbol and the data it reaches, and nothing the walk finds
    /// wrong. Every target symbol outside the samples must be inferred in
    /// the base. objdiff's `complete`, the analog of code linked into the game.
    complete: bool,
}

fn sidecar_path(target: &Path) -> PathBuf {
    target.with_extension("samples")
}

fn read_sidecar(path: &Path) -> Result<Sidecar> {
    let bytes =
        fs::read(path).with_context(|| format!("{}", path.display()))?;
    postcard::from_bytes(&bytes).with_context(|| format!("{}", path.display()))
}

/// Everything an archive's samples depend on from the types: the root
/// names it has and their types, the definition of every type those lead
/// to, and the macros their annotations use.
fn types(args: TypesArgs) -> Result<()> {
    use std::hash::{DefaultHasher, Hash, Hasher};
    let project = Project::load(&args.check)?;
    let path = project.base.join(&args.archive);
    let bytes =
        fs::read(&path).with_context(|| format!("{}", path.display()))?;
    let archives = Archive::parse_packed(&bytes)
        .with_context(|| format!("{}", path.display()))?;
    let renderer = Renderer::new(&project.graph, &project.canonical);

    let mut text = String::new();
    let mut roots = Vec::new();
    for (_, archive) in &archives {
        for (name, _) in archive.named_publics() {
            let name = String::from_utf8_lossy(name);
            if let Some(entry) = project.symbols.lookup(&name, &args.archive) {
                // Include resolved values, so changes to constants used by
                // a root binding also invalidate this archive's samples.
                text += &format!(
                    "bindings {:?}\n",
                    entry.bindings(&project.macros)?
                );
            }
            if let Some(&ty) = project.root_types.get(name.as_ref()) {
                let count = project
                    .symbols
                    .lookup(&name, &args.archive)
                    .and_then(|e| e.count);
                text += &format!("count {count:?}\n");
                text += &format!(
                    "root {name}: {}\n",
                    renderer.declare(Some(ty), "")
                );
                roots.push(ty);
            } else if let Some(spec) = project
                .symbols
                .lookup(&name, &args.archive)
                .and_then(|e| e.ty.as_ref())
            {
                text += &format!("symbol {name}: {spec}\n");
                roots.push(project.symbol_types[&spec.name]);
            }
        }
    }
    let definitions: String = project
        .canonical
        .reachable(&project.graph, roots)
        .into_iter()
        .filter(|&id| renderer.is_listed(id))
        .map(|id| renderer.definition(id))
        .collect();
    // The macros and enumerators the annotations might use
    let identifiers: BTreeSet<&str> = definitions
        .split(|c: char| !(c.is_ascii_alphanumeric() || c == '_'))
        .filter(|w| !w.is_empty())
        .collect();
    text += &definitions;
    for identifier in identifiers {
        if let Some(value) = project.macros.get(identifier) {
            text += &format!("#define {identifier} {value}\n");
        }
    }

    let mut hasher = DefaultHasher::new();
    text.hash(&mut hasher);
    let hash = format!("{:016x}\n", hasher.finish());
    if fs::read_to_string(&args.output).ok().as_deref() != Some(&hash) {
        if let Some(dir) = args.output.parent() {
            fs::create_dir_all(dir)?;
        }
        fs::write(&args.output, hash)?;
    }
    Ok(())
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
        let (_, walk) = project.walk(&args.archive, archive)?;
        picker.add(&args.archive, *at, archive, &walk);
        walks.insert(*at, walk);
    }
    let (mut samples, _) = picker.finish();
    samples.sort_by_key(|s| (s.location.archive, s.location.offset));

    let unit = args.archive.strip_suffix(".dat").unwrap_or(&args.archive);
    let mut sources: BTreeMap<usize, Source> = archives
        .iter()
        .map(|(at, a)| (*at, Source::new(a, *at, unit, &walks[at].paths)))
        .collect();
    let sampled: BTreeSet<(usize, u32)> = samples
        .iter()
        .map(|s| (s.location.archive, s.location.offset))
        .collect();
    // The other data the samples point to belongs to the root of the
    // object it is in: the nearest one the walk reached at or before it
    let mut elided = BTreeMap::new();
    let mut externs = BTreeSet::new();
    let describer = Picker::new(&project.graph, &project.canonical);
    // Where elided data ends, without a type: the next place something
    // starts
    let starts: BTreeMap<usize, BTreeSet<u32>> = archives
        .iter()
        .map(|(at, archive)| {
            let source = &sources[at];
            let mut starts: BTreeSet<u32> =
                archive.publics.iter().map(|p| p.offset).collect();
            starts.extend(walks[at].objects.keys());
            starts.extend(
                source
                    .relocs(0, archive.data.len() as u64)
                    .iter()
                    .map(|&(_, t)| t),
            );
            (*at, starts)
        })
        .collect();
    for sample in &samples {
        let at = sample.location.archive;
        let source = &sources[&at];
        for (_, name) in source.externs(sample.location.offset, sample.size) {
            externs.insert(name.to_owned());
        }
        let walk = &walks[&at];
        for (_, target) in source.relocs(sample.location.offset, sample.size) {
            if sampled.contains(&(at, target)) {
                continue;
            }
            let root = walk
                .paths
                .range(..=target)
                .next_back()
                .map_or("unknown", |(_, path)| root_of(path))
                .to_owned();
            // As far as the walk typed it
            let typed = walk.extents.get(&target).map(|&end| end - target);
            let end = source.archive.data.len() as u32;
            let size = typed.map_or_else(
                || {
                    starts[&at]
                        .range(target + 1..)
                        .next()
                        .map_or(end, |&s| s.min(end))
                        - target
                },
                |size| size,
            );
            // Declared as its type where the walk typed it as one record
            let ty = walk
                .objects
                .get(&target)
                .and_then(|types| match types.iter().collect::<Vec<_>>()[..] {
                    [&id] => describer.describe(id, target, walk).ok(),
                    _ => None,
                })
                .filter(|t| t.size == u64::from(size))
                .map(|t| ElidedType {
                    type_name: t.type_name,
                    lookup: t.lookup,
                    member: t.member,
                    header: t.header,
                });
            elided
                .entry((at, target))
                .or_insert(Elided { root, size, ty });
        }
    }
    // The rest of the archive, split where something starts
    let mut rest: Vec<(usize, u32, u32)> = Vec::new();
    for (at, archive) in &archives {
        let end = archive.data.len() as u32;
        let spans: BTreeMap<u32, u32> = samples
            .iter()
            .filter(|s| s.location.archive == *at)
            .map(|s| (s.location.offset, s.location.offset + s.size as u32))
            .collect();
        let mut bounds: BTreeSet<u32> = starts[at].range(..end).copied().collect();
        bounds.insert(0);
        bounds.extend(spans.values().filter(|&&e| e < end));
        let bounds: Vec<u32> = bounds.into_iter().collect();
        for (i, &from) in bounds.iter().enumerate() {
            let to = bounds.get(i + 1).copied().unwrap_or(end);
            let covered = spans
                .range(..=from)
                .next_back()
                .is_some_and(|(_, &e)| from < e);
            if !covered && from < to {
                rest.push((*at, from, to - from));
            }
        }
    }
    // Names for what the archive doesn't name
    let wanted: Vec<Unnamed> = sampled
        .iter()
        .map(|&(archive, offset)| (archive, offset, None))
        .chain(
            elided
                .iter()
                .map(|(&(archive, offset), e)| (archive, offset, Some(&*e.root))),
        )
        .filter(|&(archive, offset, _)| !sources[&archive].is_public(offset))
        .map(|(archive, offset, elided)| Unnamed {
            archive,
            offset,
            elided,
        })
        .collect();
    assign_names(&mut sources, &wanted);
    let pointed: BTreeSet<(usize, u32)> = elided.keys().copied().collect();
    let elided: BTreeMap<String, Elided> = elided
        .into_iter()
        .map(|((at, target), e)| (sources[&at].name(target), e))
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
        let public = source.is_public(sample.location.offset);
        infos.push(picker.info(sample, name, public));
    }

    if let Some(dir) = args.output.parent() {
        fs::create_dir_all(dir)?;
    }
    let pieces: Vec<Piece> = pairs
        .iter()
        .map(|(sample, source)| Piece {
            source,
            offset: sample.location.offset,
            size: sample.size,
            global: source.is_public(sample.location.offset),
        })
        .collect();
    // The rest the walk explains: typed data, with no relocation it can't
    // explain
    let coverages: BTreeMap<usize, _> = archives
        .iter()
        .map(|(at, archive)| {
            (*at, coverage(&project.graph, &project.canonical, archive, &walks[at]))
        })
        .collect();
    let typed: BTreeMap<usize, Vec<(u32, u32)>> = walks
        .iter()
        .map(|(at, walk)| {
            let mut extents: Vec<(u32, u32)> = Vec::new();
            let data = sources[at].archive.data;
            for (&offset, &end) in &walk.extents {
                // Objects start on words, and GX data (texels, palettes,
                // display lists) on 32 bytes: zeros up to either are padding
                let zeros = |to: u32| {
                    let to = to.min(data.len() as u32);
                    data[end as usize..to as usize]
                        .iter()
                        .all(|&b| b == 0)
                        .then_some(to)
                };
                let end = zeros(end.next_multiple_of(32))
                    .or_else(|| zeros(end.next_multiple_of(4)))
                    .unwrap_or(end);
                match extents.last_mut() {
                    Some(last) if offset <= last.1 => last.1 = last.1.max(end),
                    _ => extents.push((offset, end)),
                }
            }
            (*at, extents)
        })
        .collect();
    let explained: Vec<bool> = rest
        .iter()
        .map(|&(at, offset, size)| {
            let end = offset + size;
            typed[&at].iter().any(|&(from, to)| from <= offset && end <= to)
                && !coverages[&at]
                    .unexplained
                    .iter()
                    .any(|u| (offset..end).contains(&u.at))
        })
        .collect();
    // Only what has a global name goes in the objects: the archive's public
    // symbols and the data the samples point to. The rest is only reached
    // through those, and the C never names it: a global is inferred when it
    // and everything it reaches without passing another global or a sample
    // are explained
    let spans: BTreeMap<(usize, u32), usize> = rest
        .iter()
        .enumerate()
        .map(|(i, &(at, offset, _))| ((at, offset), i))
        .collect();
    let named = |i: usize| {
        let (at, offset, _) = rest[i];
        sources[&at].is_public(offset) || pointed.contains(&(at, offset))
    };
    let mut target_rest = Vec::new();
    let mut inferred = Vec::new();
    for (i, &(at, offset, size)) in rest.iter().enumerate() {
        if !named(i) {
            continue;
        }
        let source = &sources[&at];
        let mut seen = BTreeSet::from([i]);
        let mut stack = vec![i];
        let mut all = true;
        while let Some(i) = stack.pop() {
            if !explained[i] {
                all = false;
                break;
            }
            let (_, from, size) = rest[i];
            for (_, target) in source.relocs(from, size.into()) {
                if let Some(&j) = spans.get(&(at, target))
                    && !named(j)
                    && seen.insert(j)
                {
                    stack.push(j);
                }
            }
        }
        let piece = Piece {
            source,
            offset,
            size: size.into(),
            // The archive names only its public symbols. The C declares
            // elided data extern, but the base's references to it needn't
            // bind: objdiff compares relocations to undefined symbols by name
            global: source.is_public(offset),
        };
        if all {
            inferred.push(piece.clone());
        }
        target_rest.push(piece);
    }
    // The target defines all of it and the C doesn't, so objdiff counts it as
    // missing; the base defines what is inferred, by name and size, so that
    // objdiff matches it
    fs::write(
        &args.output,
        target_object(&pieces, &target_rest, &args.archive)?,
    )?;
    fs::write(args.output.with_extension("rest.o"), rest_object(&inferred)?)?;
    // The target's order, for linking the base object's samples the same:
    // clang lays variables out where an initializer first points to them
    let mut script = format!("SECTIONS\n{{\n    {SAMPLED} : {{\n");
    for info in &infos {
        script += &format!("        *(.data.{})\n", info.symbol);
    }
    // Then what the walk explains, under the target's names
    script += &format!(
        "        *(.data .data.*)\n    }}\n    {INFERRED} : {{ *({INFERRED}) }}\n}}\n"
    );
    fs::write(args.output.with_extension("ld"), script)?;
    let sidecar = Sidecar {
        archive: args.archive,
        samples: infos,
        elided,
        externs,
        complete: inferred.len() == target_rest.len()
            && inferred.iter().zip(&target_rest).all(|(base, target)| {
                base.source.file_offset(base.offset)
                    == target.source.file_offset(target.offset)
                    && base.size == target.size
            })
            && archives.iter().all(|(at, archive)| {
                let walk = &walks[at];
                walk.issues.is_empty()
                    && archive
                        .publics
                        .iter()
                        .all(|p| walk.objects.contains_key(&p.offset))
                    && coverages[at].unexplained.is_empty()
            }),
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
    let section = obj.section_by_name(SAMPLED);
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
        &sidecar.elided,
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

fn macros(args: MacrosArgs) -> Result<()> {
    const MACROS: &str = include_str!("../../assets/macros.h");
    if fs::read_to_string(&args.output).ok().as_deref() != Some(MACROS) {
        if let Some(dir) = args.output.parent() {
            fs::create_dir_all(dir)?;
        }
        fs::write(&args.output, MACROS)?;
    }
    Ok(())
}

/// The units' top-level directory in objdiff, like the code's `main/`.
const PROJECT_DIR: &str = "dat";

fn project(args: ProjectArgs) -> Result<()> {
    let mut units = Vec::new();
    for path in &args.sidecars {
        let sidecar = read_sidecar(path)?;
        if sidecar.samples.is_empty() {
            continue;
        }
        let stem = path
            .file_stem()
            .context("sidecar without a name")?
            .to_string_lossy();
        // Grouped by module, as the build lays them out: `Pl/PlMr`
        let unit = format!("{}/{stem}", family(&stem));
        units.push(json!({
            "name": format!("{PROJECT_DIR}/{unit}"),
            "target_path": format!("target/{unit}.o"),
            "base_path": format!("base/{unit}.o"),
            "metadata": {
                "complete": sidecar.complete,
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
    /// The base object's contents outside its samples and inferred data,
    /// e.g. code or strings
    /// from headers, which the target doesn't have.
    extra: Vec<String>,
}

/// Allocated sections of a unit's base object other than its samples and
/// inferred data, with their sizes.
fn extra_sections(dir: &Path, unit: &str) -> Result<Vec<String>> {
    let path = dir.join(format!("base/{unit}.o"));
    let data =
        fs::read(&path).with_context(|| format!("{}", path.display()))?;
    let obj = object::File::parse(&*data)?;
    Ok(obj
        .sections()
        .filter(|s| s.size() > 0 && !matches!(s.name(), Ok(SAMPLED | INFERRED)))
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
        .filter_map(|u| u["name"].as_str())
        .map(|name| {
            let unit = name.strip_prefix(PROJECT_DIR).unwrap_or(name);
            unit.trim_start_matches('/').to_owned()
        })
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
