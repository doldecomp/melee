mod coverage;
mod motions;

use super::project::Project;

use super::dwarf_path;
use anyhow::{Context, Result};
use globset::GlobSet;
use melee_dat::{
    config::{gather_files, get_config},
    dwarf::{
        TypeGraph,
        canonical::Canonical,
        render::Renderer,
        roots::{RootName, roots},
    },
    hsd::Archive,
};
use std::{
    collections::{BTreeMap, BTreeSet},
    fs,
    io::{self, Write},
};

#[derive(clap::Args)]
pub struct Args {
    #[command(subcommand)]
    command: Command,
}

#[derive(clap::Subcommand)]
enum Command {
    /// List the archive symbols the code loads by name, with their types
    Roots(args::Roots),

    /// Check the roots' types against the archives that define them
    Check(args::Check),

    /// Check packed animations against the game's motion tables
    CheckMotions(motions::Args),

    /// Type each archive's data by walking it from its roots
    Walk(args::Check),

    /// How much of each archive the walk explains, and where the gaps are
    Coverage(args::Coverage),
}

mod args {
    use clap::Args;
    use std::path::PathBuf;

    #[derive(Args)]
    pub struct Roots {
        /// ELF or object with DWARF [default: $MELEE_DWARF_ELF]
        #[arg(long)]
        pub dwarf: Option<PathBuf>,
    }

    pub use crate::cmd::project::Check;

    #[derive(Args)]
    pub struct Coverage {
        #[command(flatten)]
        pub check: Check,
        /// What to list
        #[arg(long, value_enum, default_value_t)]
        pub by: super::coverage::View,
        /// Only archives whose file matches (glob; repeatable)
        #[arg(short, long)]
        pub archive: Vec<String>,
        /// Rows to show in the table, by size; 0 for all
        #[arg(long, default_value_t = 25)]
        pub top: usize,
        /// Also list every unexplained relocation
        #[arg(long)]
        pub list: bool,
        #[arg(long, value_enum, default_value_t)]
        pub format: super::coverage::Format,
    }
}

pub fn run(Args { command }: Args) -> Result<()> {
    match command {
        Command::Roots(args) => list_roots(args),
        Command::Check(args) => check(args),
        Command::CheckMotions(args) => motions::run(args),
        Command::Walk(args) => walk(args),
        Command::Coverage(args) => coverage::run(args),
    }
}

/// Call sites, by the type they load a symbol as (`None` for `void`).
type SitesByType = BTreeMap<Option<String>, Vec<String>>;

fn list_roots(args: args::Roots) -> Result<()> {
    let graph = TypeGraph::load(dwarf_path(args.dwarf)?)?;
    let canonical = Canonical::new(&graph);
    let renderer = Renderer::new(&graph, &canonical);

    // Call sites by name, then by the type they load the symbol as. The
    // same expression in different functions names unrelated symbols, so
    // expressions are also keyed by their function.
    let mut by_name: BTreeMap<(RootName, Option<String>), SitesByType> =
        BTreeMap::new();
    for root in roots(&graph, &canonical) {
        let ty = root.ty.map(|ty| renderer.declare(Some(ty), ""));
        let site = match root.function(&graph) {
            Some(function) => format!("{} {function}", root.location(&graph)),
            None => root.location(&graph),
        };
        let scope = match root.name {
            RootName::Literal(_) => None,
            RootName::Expr(_) => root.function(&graph).map(str::to_owned),
        };
        by_name
            .entry((root.name, scope))
            .or_default()
            .entry(ty)
            .or_default()
            .push(site);
    }

    let (mut typed, mut untyped, mut conflicts) = (0, 0, 0);
    let mut out = io::stdout().lock();
    for ((name, _), types) in &by_name {
        let name = match name {
            RootName::Literal(name) => name.clone(),
            RootName::Expr(expr) => format!("({expr})"),
        };
        let void = types.get(&None);
        let known: Vec<_> = types
            .iter()
            .filter_map(|(t, s)| Some((t.as_ref()?, s)))
            .collect();
        match known.as_slice() {
            [] => untyped += 1,
            [_] => typed += 1,
            _ => conflicts += 1,
        }
        let conflict = if known.len() > 1 { " conflict" } else { "" };
        for (ty, sites) in &known {
            writeln!(
                out,
                "{name} // type:{ty}{conflict} {}",
                sites.join(", ")
            )?;
        }
        if let Some(sites) = void {
            let prefix = if known.is_empty() { "" } else { "  " };
            writeln!(out, "{prefix}{name} // untyped {}", sites.join(", "))?;
        }
    }
    eprintln!(
        "{} roots: {typed} typed, {untyped} untyped, {conflicts} conflicting",
        by_name.len()
    );
    Ok(())
}

/// Where each public symbol name is defined: archive path and extent.
fn index_archives(
    args: &args::Check,
) -> Result<BTreeMap<String, Vec<(String, u32)>>> {
    let config = get_config(args.proj_path.as_ref(), &args.cfg_path)?;
    let base = args
        .proj_path
        .clone()
        .unwrap_or_default()
        .join(config.base.as_str());
    let mut index: BTreeMap<String, Vec<(String, u32)>> = BTreeMap::new();
    let mut paths = gather_files(&base, &config.include)?;
    paths.sort();
    for path in paths {
        let bytes = fs::read(&path)?;
        let file = path.strip_prefix(&base)?.to_string_lossy().into_owned();
        let archives = Archive::parse_packed(&bytes)
            .with_context(|| format!("{}", path.display()))?;
        for (at, archive) in archives {
            let rel = match at {
                0 => file.clone(),
                _ => format!("{file}@{at:#X}"),
            };
            for (name, symbol) in archive.named_publics() {
                index
                    .entry(String::from_utf8_lossy(name).into_owned())
                    .or_default()
                    .push((rel.clone(), archive.extent(symbol.offset)));
            }
        }
    }
    Ok(index)
}

fn check(args: args::Check) -> Result<()> {
    let index = index_archives(&args)?;
    let graph = TypeGraph::load(dwarf_path(args.dwarf.clone())?)?;
    let canonical = Canonical::new(&graph);
    let renderer = Renderer::new(&graph, &canonical);

    // Each literal root name with the distinct types it is loaded as
    let mut types: BTreeMap<String, BTreeSet<_>> = BTreeMap::new();
    let mut dynamic = 0;
    for root in roots(&graph, &canonical) {
        match root.name {
            RootName::Literal(name) => {
                let entry = types.entry(name).or_default();
                if let Some(ty) = root.ty {
                    entry.insert(ty);
                }
            }
            RootName::Expr(_) => dynamic += 1,
        }
    }

    let mut out = io::stdout().lock();
    let (mut ok, mut missing, mut untyped, mut incomplete, mut overflows) =
        (0, 0, 0, 0, 0);
    for (name, dies) in &types {
        let Some(instances) = index.get(name) else {
            missing += 1;
            writeln!(out, "missing: {name} is in no archive")?;
            continue;
        };
        if dies.is_empty() {
            untyped += 1;
            continue;
        }
        let mut good = true;
        for &die in dies {
            let ty = renderer.declare(Some(die), "");
            let Some(size) = canonical.byte_size(&graph, die) else {
                incomplete += 1;
                good = false;
                writeln!(out, "incomplete: {name} as {ty}")?;
                continue;
            };
            for (archive, extent) in instances {
                if size > u64::from(*extent) {
                    overflows += 1;
                    good = false;
                    let problem = format!("{ty} is 0x{size:X}");
                    writeln!(
                        out,
                        "overflow: {name} in {archive} is 0x{extent:X}: {problem}"
                    )?;
                }
            }
        }
        ok += usize::from(good);
    }
    let total = types.len();
    let problems = format!(
        "{missing} missing, {incomplete} incomplete, {overflows} overflows"
    );
    writeln!(
        out,
        "{total} named roots: {ok} fit, {untyped} untyped, {problems}; \
{dynamic} call sites name a root by expression"
    )?;
    Ok(())
}

fn walk(args: args::Check) -> Result<()> {
    let project = Project::load(&args)?;
    let renderer = Renderer::new(&project.graph, &project.canonical);
    let mut out = io::stdout().lock();
    let (mut walked, mut publics, mut typed, mut relocs, mut explained) =
        (0, 0, 0, 0, 0);
    let (mut untyped_pointers, mut sentinels, mut conflicts) = (0, 0, 0);
    let mut kinds: BTreeMap<&str, usize> = BTreeMap::new();
    project.walk_all(&GlobSet::empty(), |w| {
        publics += w.archive.publics.len();
        relocs += w.archive.relocs.len();
        if !w.rooted {
            return Ok(());
        }
        let result = &w.result;
        walked += 1;
        typed += w
            .archive
            .publics
            .iter()
            .filter(|p| result.objects.contains_key(&p.offset))
            .count();
        explained += result.pointers.len();
        untyped_pointers += result.untyped_pointers;
        sentinels += result.sentinels;
        for (offset, types) in &result.objects {
            if types.len() > 1 {
                conflicts += 1;
                let names: Vec<_> = types
                    .iter()
                    .map(|&id| {
                        renderer
                            .declare(Some(project.canonical.get(id).rep), "")
                    })
                    .collect();
                writeln!(
                    out,
                    "{}: object at 0x{offset:X} reached as {}",
                    w.name,
                    names.join(", ")
                )?;
            }
        }
        for issue in &result.issues {
            *kinds.entry(issue.kind()).or_default() += 1;
            writeln!(out, "{}: {}: {issue}", w.name, issue.kind())?;
        }
        Ok(())
    })?;

    eprintln!(
        "walked {walked} archives: {typed}/{publics} public symbols typed, \
{explained}/{relocs} relocations explained, {untyped_pointers} untyped \
pointers, {sentinels} -1 pointers, {conflicts} objects reached as several \
types"
    );
    for (kind, count) in kinds {
        eprintln!("  {count} {kind}");
    }
    Ok(())
}
