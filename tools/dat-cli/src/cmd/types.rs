use super::dwarf_path;
use anyhow::Result;
use melee_dat::dwarf::{TypeGraph, canonical::Canonical, render::Renderer};
use std::io::{self, Write};

#[derive(clap::Args)]
pub struct Args {
    #[command(subcommand)]
    command: Command,
}

#[derive(clap::Subcommand)]
enum Command {
    /// Print type definitions as C-like text with offsets and annotations
    Dump(args::Dump),

    /// Write the compact types file other commands take with `--types`
    Export(args::Export),

    /// Records with the same layout under different names: likely the same
    /// data defined twice
    Duplicates(args::Duplicates),

    /// Types the archives' roots reach that a `.c` file declares, which
    /// generated C can't include
    Unhoisted(args::Unhoisted),
}

mod args {
    use clap::Args;
    use std::path::PathBuf;

    #[derive(Args)]
    pub struct Export {
        /// ELF or object with DWARF [default: $MELEE_DWARF_ELF]
        #[arg(long)]
        pub dwarf: Option<PathBuf>,
        #[arg(short, long)]
        pub output: PathBuf,
    }

    #[derive(Args)]
    pub struct Unhoisted {
        /// The compact types file from `types export`
        #[arg(long)]
        pub types: PathBuf,
    }

    #[derive(Args)]
    pub struct Duplicates {
        /// ELF or object with DWARF [default: $MELEE_DWARF_ELF]
        #[arg(long, conflicts_with = "types")]
        pub dwarf: Option<PathBuf>,
        /// The compact types file from `types export`, instead of the DWARF
        #[arg(long)]
        pub types: Option<PathBuf>,
        /// Only records at least this many bytes
        #[arg(long, default_value_t = 16)]
        pub min_size: u64,
        /// Also groups none of whose records the archives' roots reach
        #[arg(long)]
        pub all: bool,
    }

    #[derive(Args)]
    pub struct Dump {
        /// ELF or object with DWARF [default: $MELEE_DWARF_ELF]
        #[arg(long)]
        pub dwarf: Option<PathBuf>,
        /// Only these types, by display name (e.g. `HSD_Joint::u`)
        #[arg(short, long)]
        pub name: Vec<String>,
    }
}

pub fn run(Args { command }: Args) -> Result<()> {
    match command {
        Command::Dump(args) => dump(args),
        Command::Export(args) => export(args),
        Command::Duplicates(args) => duplicates(args),
        Command::Unhoisted(args) => unhoisted(args),
    }
}

fn export(args: args::Export) -> Result<()> {
    let graph = TypeGraph::load(dwarf_path(args.dwarf)?)?;
    melee_dat::dwarf::cache::TypesFile::build(&graph).save(&args.output)
}

fn dump(args: args::Dump) -> Result<()> {
    let graph = TypeGraph::load(dwarf_path(args.dwarf)?)?;
    let canonical = Canonical::new(&graph);
    let renderer = Renderer::new(&graph, &canonical);

    let mut listed: Vec<_> = (0..canonical.types.len() as u32)
        .map(melee_dat::dwarf::canonical::CanonId)
        .filter(|&id| renderer.is_listed(id))
        .filter(|&id| {
            args.name.is_empty()
                || renderer
                    .display(id)
                    .is_some_and(|d| args.name.iter().any(|n| n == d))
        })
        .collect();
    // A typedef before the tag it names
    listed.sort_by_key(|&id| {
        let typedef = matches!(
            canonical.ty(&graph, id).kind,
            melee_dat::dwarf::TypeKind::Typedef { .. }
        );
        (renderer.display(id), !typedef, id)
    });

    let mut out = io::stdout().lock();
    for id in listed {
        writeln!(out, "{}", renderer.definition(id))?;
    }

    if args.name.is_empty() {
        for (label, list) in [
            ("conflict", &canonical.conflicts),
            ("ambiguity", &canonical.ambiguities),
        ] {
            for c in list {
                writeln!(
                    out,
                    "// {label}: {} has {} definitions",
                    graph.str(c.name),
                    c.variants.len()
                )?;
            }
        }
    }
    Ok(())
}

/// A record's layout without names or pointee types: its size, and each
/// member's offset, bit field, size and whether it is a pointer.
type Layout = (u64, bool, Vec<(u64, u64, u64, u64, bool)>);

fn duplicates(args: args::Duplicates) -> Result<()> {
    use melee_dat::dwarf::{DieId, TypeKind};
    use std::collections::{BTreeMap, BTreeSet};

    let (graph, roots) = match &args.types {
        Some(path) => {
            let file = melee_dat::dwarf::cache::TypesFile::load(path)?;
            (file.graph, file.roots.into_values().collect())
        }
        None => {
            let graph = TypeGraph::load(dwarf_path(args.dwarf)?)?;
            let file = melee_dat::dwarf::cache::TypesFile::build(&graph);
            (graph, file.roots.into_values().collect::<Vec<_>>())
        }
    };
    let canonical = Canonical::new(&graph);
    let rep =
        |die: DieId| canonical.of(die).map_or(die, |id| canonical.get(id).rep);
    // Every type the roots lead to, through members and pointers
    let mut reached: BTreeSet<DieId> = BTreeSet::new();
    let mut queue: Vec<DieId> = roots.iter().map(|&d| rep(d)).collect();
    while let Some(die) = queue.pop() {
        if !reached.insert(die) {
            continue;
        }
        let mut next = |t: &Option<DieId>| {
            if let Some(t) = t {
                queue.push(rep(*t));
            }
        };
        match &graph.types[&die].kind {
            TypeKind::Pointer { target }
            | TypeKind::Typedef { target }
            | TypeKind::Const { target }
            | TypeKind::Volatile { target }
            | TypeKind::Restrict { target } => next(target),
            TypeKind::Array { element, .. } => next(element),
            TypeKind::Record { members, .. } => {
                members.iter().for_each(|m| next(&m.ty));
            }
            _ => {}
        }
    }
    // Through typedefs and qualifiers
    let resolve = |mut die: DieId| loop {
        match graph.types[&die].kind {
            TypeKind::Typedef { target: Some(t) }
            | TypeKind::Const { target: Some(t) }
            | TypeKind::Volatile { target: Some(t) } => die = t,
            _ => return die,
        }
    };

    // Every record's names: its tag, and the typedefs naming it
    let mut names: BTreeMap<DieId, BTreeSet<String>> = BTreeMap::new();
    for t in &canonical.types {
        let ty = &graph.types[&t.rep];
        let named = match ty.kind {
            TypeKind::Record {
                declaration: false, ..
            } => Some((t.rep, ty)),
            TypeKind::Typedef {
                target: Some(target),
            } => {
                let record = resolve(target);
                matches!(
                    graph.types[&record].kind,
                    TypeKind::Record {
                        declaration: false,
                        ..
                    }
                )
                .then_some((record, ty))
            }
            _ => None,
        };
        if let Some((record, ty)) = named
            && let Some(name) = ty.name
        {
            let record = rep(record);
            let file = ty.decl_file.map_or("?", |f| graph.str(f));
            let file = file.rsplit_once("/src/").map_or(file, |(_, f)| f);
            names
                .entry(record)
                .or_default()
                .insert(format!("{} ({file})", graph.str(name)));
        }
    }

    let mut groups: BTreeMap<Layout, Vec<DieId>> = BTreeMap::new();
    for &record in names.keys() {
        let TypeKind::Record { union, members, .. } =
            &graph.types[&record].kind
        else {
            continue;
        };
        let Some(size) = canonical.byte_size(&graph, record) else {
            continue;
        };
        if size < args.min_size || members.len() < 2 {
            continue;
        }
        let members = members
            .iter()
            .map(|m| {
                let ty = m.ty.map(resolve);
                (
                    m.offset.unwrap_or(0),
                    m.bit_offset.unwrap_or(0),
                    m.bit_size.unwrap_or(0),
                    m.ty.and_then(|t| canonical.byte_size(&graph, t))
                        .unwrap_or(0),
                    ty.is_some_and(|t| {
                        matches!(
                            graph.types[&t].kind,
                            TypeKind::Pointer { .. }
                        )
                    }),
                )
            })
            .collect();
        groups
            .entry((size, *union, members))
            .or_default()
            .push(record);
    }

    let mut groups: Vec<_> = groups
        .into_iter()
        .filter(|(_, records)| records.len() > 1)
        .filter(|(_, records)| {
            args.all || records.iter().any(|r| reached.contains(r))
        })
        .collect();
    groups.sort_by_key(|((size, _, members), _)| {
        (std::cmp::Reverse(*size), members.len())
    });
    let mut out = io::stdout().lock();
    for ((size, _, members), records) in &groups {
        writeln!(out, "{size:#X} bytes, {} members:", members.len())?;
        for record in records {
            let names: Vec<_> =
                names[record].iter().map(String::as_str).collect();
            let dat = if reached.contains(record) {
                "dat "
            } else {
                "    "
            };
            writeln!(out, "  {dat}{}", names.join(", "))?;
        }
    }
    writeln!(out, "{} groups", groups.len())?;
    Ok(())
}

fn unhoisted(args: args::Unhoisted) -> Result<()> {
    let file = melee_dat::dwarf::cache::TypesFile::load(&args.types)?;
    let graph = file.graph;
    let canonical = Canonical::new(&graph);
    let renderer = Renderer::new(&graph, &canonical);
    let mut rows = std::collections::BTreeSet::new();
    for id in canonical.reachable(&graph, file.roots.into_values()) {
        let ty = &graph.types[&canonical.get(id).rep];
        let (Some(_), Some(decl)) = (ty.name, ty.decl_file) else {
            continue;
        };
        let decl = graph.str(decl);
        if decl.ends_with(".c") && renderer.is_listed(id) {
            let decl = decl.rsplit_once("/src/").map_or(decl, |(_, f)| f);
            let name = renderer.display(id).unwrap_or("?");
            rows.insert((decl.to_owned(), name.to_owned()));
        }
    }
    let mut out = io::stdout().lock();
    for (decl, name) in &rows {
        writeln!(out, "{decl}  {name}")?;
    }
    writeln!(out, "{} types", rows.len())?;
    Ok(())
}
