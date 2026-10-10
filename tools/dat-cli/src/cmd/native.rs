//! `native`: the schema of `native/`, the C library that reads archives into
//! the game's own types on any platform, and what it should reach.
//!
//! - `codegen`: the schema, as C, from the DWARF and `dat_symbols.txt`: a
//!   compiled reader for each type, in a file for each game header
//!   (see [`emit`])
//! - `expect`: what the walk reaches in each archive, in the form the
//!   library's `dat_trace` prints, for its end-to-end tests

mod emit;
mod fixtures;
mod generator;

use super::project::{Check, Project};
use anyhow::Result;
use generator::Generator;
use globset::GlobSet;
use melee_dat::{
    dwarf::canonical::CanonId,
    walk::{Issue, Walk},
};
use std::{
    collections::{BTreeMap, BTreeSet},
    io::{self, Write},
    path::PathBuf,
};

#[derive(clap::Args)]
pub struct Args {
    #[command(subcommand)]
    command: Command,
}

#[derive(clap::Subcommand)]
enum Command {
    /// Write the library's schema: every type the archives' roots lead to,
    /// and every archive's roots
    Codegen(Codegen),

    /// Print what the walk reaches in each archive, as `dat_trace` does
    Expect(Expect),

    /// Generate the native regression fixtures with the production emitter.
    #[command(hide = true)]
    Fixtures { out_dir: PathBuf },
}

#[derive(clap::Args)]
struct Codegen {
    #[command(flatten)]
    check: Check,
    /// The directory to write the schema's sources to, which holds only
    /// them: sources no longer generated are removed
    #[arg(long)]
    out_dir: PathBuf,
}

#[derive(clap::Args)]
struct Expect {
    #[command(flatten)]
    check: Check,
    /// Only these archives (globs on file names)
    #[arg(long)]
    only: Vec<String>,
}

pub fn run(Args { command }: Args) -> Result<()> {
    match command {
        Command::Codegen(args) => codegen(args),
        Command::Expect(args) => expect(args),
        Command::Fixtures { out_dir } => fixtures::generate(&out_dir),
    }
}

fn codegen(args: Codegen) -> Result<()> {
    let project = Project::load(&args.check)?;
    let mut generator = Generator::new(&project);
    let files = generator.file_roots()?;
    // Every type a type refers to is listed by now, but members may list
    // more, which have members of their own
    generator.fill_members();
    for member in &generator.unplaced {
        log::warn!("no native place for {member}");
    }
    for ty in &generator.unhoisted {
        log::warn!("declared in a source file, not a header: {ty}");
    }
    let output = emit::emit(&generator, &files)?;
    emit::write(&args.out_dir, &output)?;
    eprintln!(
        "{} types, {} members, {} roots in {} archives, in {} files; {} members without a native place",
        generator.types.len() - 1,
        generator
            .types
            .iter()
            .map(|t| t.members.len())
            .sum::<usize>(),
        files.iter().map(|f| f.roots.len()).sum::<usize>(),
        files.len(),
        output.len(),
        generator.unplaced.len(),
    );
    Ok(())
}

/// What a walk reached, as `dat_trace` prints it.
pub fn trace(
    out: &mut impl Write,
    walk: &Walk,
    name_of: &dyn Fn(CanonId) -> String,
) -> io::Result<()> {
    for (offset, ids) in &walk.objects {
        for id in ids {
            writeln!(out, "object 0x{offset:X} {} {}", id.0, name_of(*id))?;
        }
    }
    let mut pointers: Vec<_> = walk.pointers.iter().copied().collect();
    pointers.sort();
    for at in pointers {
        writeln!(out, "pointer 0x{at:X}")?;
    }
    for (offset, end) in &walk.extents {
        writeln!(out, "extent 0x{offset:X} 0x{end:X}")?;
    }
    for ((offset, id), index) in &walk.choices {
        writeln!(out, "choice 0x{offset:X} {} {index}", id.0)?;
    }
    let issues: BTreeSet<(u8, u32, u32)> = walk
        .issues
        .iter()
        .map(|issue| match *issue {
            Issue::UnrelocatedPointer { at, value, .. } => (0, at, value),
            Issue::RelocatedScalar { at, .. } => (1, at, 0),
            Issue::OutOfBounds { at, .. } => (2, at, 0),
            Issue::AmbiguousUnion { at, .. } => (3, at, 0),
            Issue::UnknownCommand { at, opcode, .. } => {
                (4, at, u32::from(opcode))
            }
        })
        .collect();
    const KINDS: [&str; 5] = [
        "unrelocated-pointer",
        "relocated-scalar",
        "out-of-bounds",
        "ambiguous-union",
        "unknown-command",
    ];
    for (kind, at, value) in issues {
        writeln!(out, "issue {} 0x{at:X} 0x{value:X}", KINDS[kind as usize])?;
    }
    writeln!(out, "untyped-pointers {}", walk.untyped_pointers)?;
    writeln!(out, "sentinels {}", walk.sentinels)?;
    Ok(())
}

fn expect(args: Expect) -> Result<()> {
    let project = Project::load(&args.check)?;
    let mut only = globset::GlobSetBuilder::new();
    for glob in &args.only {
        only.add(globset::Glob::new(glob)?);
    }
    let only: GlobSet = only.build()?;
    let names: BTreeMap<CanonId, String> = project
        .canonical
        .types
        .iter()
        .enumerate()
        .map(|(i, t)| {
            (
                CanonId(i as u32),
                t.display.clone().unwrap_or_else(|| "?".into()),
            )
        })
        .collect();
    let name_of =
        |id: CanonId| names.get(&id).cloned().unwrap_or_else(|| "?".into());
    let mut out = io::BufWriter::new(io::stdout().lock());
    project.walk_all(&only, |walked| {
        if !walked.rooted {
            return Ok(());
        }
        writeln!(out, "archive {}", walked.name)?;
        trace(&mut out, &walked.result, &name_of)?;
        Ok(())
    })?;
    out.flush()?;
    Ok(())
}
