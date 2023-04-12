use ahash::AHashMap;
use anyhow::{Context, Result};
use cwparse::map::{self, hex, Identifier, Line, Origin};
use dashmap::DashSet;
use itertools::Itertools;
use log::{debug, error, info};
use melee_utils::{replace, ROOT};
use memmap2::Mmap;
use nom::{
    character::complete::{alphanumeric1, char},
    combinator::all_consuming,
    error::{FromExternalError, ParseError},
    sequence::{pair, preceded},
    IResult,
};
use rayon::{
    prelude::{
        IndexedParallelIterator, IntoParallelIterator,
        IntoParallelRefIterator, ParallelIterator,
    },
    str::ParallelString,
};
use regex::RegexBuilder;
use std::{fs::File, num::ParseIntError, str};

fn anon_func<'a, E>(input: &'a str) -> IResult<&'a str, u32, E>
where
    E: ParseError<&'a str> + FromExternalError<&'a str, ParseIntError>,
{
    all_consuming(preceded(pair(alphanumeric1, char('_')), hex(8)))(input)
}

fn main() -> Result<()> {
    env_logger::try_init()?;

    let path = &*ROOT.join("build/ssbm.us.1.2/GALE01.map");
    let file = File::open(path).context("Failed to open the map file.")?;
    let mmap = unsafe { Mmap::map(&file) }
        .context("Failed to create the memory map.")?;
    let input = str::from_utf8(mmap.as_ref())
        .context("Failed to convert to UTF-8.")?;
    let lines = input
        .par_lines()
        .map(|line| map::line::<()>(line).map(|line| line.1))
        .collect::<Result<Vec<_>, _>>()
        .context("Failed to parse lines.")?;

    let asm_files = glob::glob(
        &*ROOT
            .join("asm/**/*.s")
            .to_str()
            .context("Failed to create the glob.")?,
    )?
    .into_iter()
    .map(|res| {
        res.context("Failed to get a path from the glob.")
            .map(|path| {
                let name = path
                    .file_name()
                    .context("Failed to get a filename from the path.")?
                    .to_string_lossy()
                    .to_string()
                    .clone();

                Ok((name, path))
            })?
    })
    .collect::<Result<AHashMap<_, _>>>()?;

    let to_rename = lines
        .par_iter()
        .filter_map(|line| {
            use cwparse::tree::*;

            match line {
                Line::TreeNode(Node {
                    data:
                        Data::Object(
                            Identifier::Named { name, .. },
                            Specifier {
                                scope: Scope::Local,
                                origin: Origin { obj, .. },
                                ..
                            },
                        ),
                    ..
                }) if obj.ends_with(".s.o") => {
                    if let Ok(("", virt_addr)) = anon_func::<()>(name) {
                        Some((&obj[0..obj.len() - 2], *name, virt_addr))
                    } else {
                        None
                    }
                }
                _ => None,
            }
        })
        .collect::<DashSet<_, ahash::RandomState>>();

    info!("found {} symbols to replace", to_rename.len());

    let replacements = to_rename
        .into_iter()
        .sorted_by(|(a, _, _), (b, _, _)| a.cmp(b))
        .group_by(|(file, _, _)| *file)
        .into_iter()
        .map(|(key, group)| {
            let path = asm_files
                .get(key)
                .context("Failed to find asm file.")?
                .as_path();

            let addrs = group
                .map(|(_, name, addr)| {
                    debug!("Found {} in {:#?}.", &name, &path);
                    format!("{:8X}", addr)
                })
                .into_iter()
                .join("|");

            let pattern = format!(r"\b(?:[[:alnum:]]+)_({})\b", addrs);
            Ok((pattern, path))
        })
        .collect::<Result<Vec<_>>>()?;

    let total = replacements.len();
    info!("replacing in {} files", total);

    let mut results = Vec::<Result<()>>::with_capacity(total);

    replacements
        .into_par_iter()
        .map(|(pattern, path)| {
            const LIMIT: usize = 1 << 22; // 4 MiB

            let re = RegexBuilder::new(&pattern).size_limit(LIMIT).build()?;
            replace(&re, r".L_$1", path)
        })
        .collect_into_vec(&mut results);

    let mut errors: usize = 0;
    for res in results {
        if let Err(err) = res {
            error!("{}", err);
            errors += 1;
        }
    }

    info!("{} succeeded; {} failed", total - errors, errors);

    Ok(())
}
