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
}

mod args {
    use clap::Args;
    use std::path::PathBuf;

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
    }
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
