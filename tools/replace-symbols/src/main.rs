use ahash::{HashMapExt, HashSetExt};
use anyhow::{bail, Result};
use clap::{self, Parser};
use log::{info, trace, warn};
use melee_utils::{replace_symbols, walk_src};
use rayon::prelude::{IntoParallelIterator, ParallelIterator};
use std::{
    collections::{HashMap, HashSet},
    fs::File,
    io::{stdin, Read},
    sync::Arc,
};

#[derive(Parser)]
#[command(author, version, about, long_about = None)]
struct Cli {
    /// A path to a file with one or more word replacements in the form of
    /// "FROM:TO". Uses stdin if empty or "-".
    path: Option<String>,
}

fn main() -> Result<()> {
    env_logger::try_init()?;
    let cli = Cli::parse();

    let mut input = String::with_capacity(16);
    if let Some(path) = cli.path.filter(|s| s != "-") {
        File::open(path)?.read_to_string(&mut input)?;
    } else {
        stdin().read_to_string(&mut input)?;
    }

    let args = input.split_whitespace().collect::<Vec<_>>();

    if args.len() < 1 {
        bail!("Please provide at least one colon-separated replacement.");
    }

    let mut replacements =
        HashMap::<Arc<str>, Arc<str>, ahash::RandomState>::with_capacity(
            args.len(),
        );

    let mut duplicates = HashSet::<Arc<str>, ahash::RandomState>::new();

    args.iter().try_for_each(|replacement| {
        let splits = replacement.split(":").collect::<Vec<_>>();

        if splits.len() < 2 {
            bail!("Separate replacements with colons.");
        }
        if splits.len() > 2 {
            bail!("Replacements must be provided in pairs.");
        }

        let from = splits[0];
        let to = splits[1];

        if from == to {
            warn!(r#""{}" is replacing itself. Skipping."#, from);
            return Ok(());
        }

        let replacement_exists = replacements.contains_key(from);
        let duplicate_exists = duplicates.contains(from);
        if replacement_exists || duplicate_exists {
            if !duplicates.contains(from) {
                warn!(
                    r#""{}" is being replaced more than once. Skipping."#,
                    from
                );
                duplicates.insert(Arc::from(from));
            }
            if replacement_exists {
                replacements.remove(from);
            }
            return Ok(());
        }

        trace!("{} -> {}", from, to);
        replacements.insert(Arc::from(from), Arc::from(to));

        Ok(())
    })?;

    let src = walk_src()?;

    info!(
        "replacing {} symbols in {} source files",
        replacements.len(),
        src.len()
    );

    src.into_par_iter()
        .try_for_each(|path| replace_symbols(path, &replacements))?;

    Ok(())
}
