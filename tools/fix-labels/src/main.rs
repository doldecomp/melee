use ahash::AHashMap;
use anyhow::{Context, Result};
use cwparse::map::{self, hex, Identifier, Line, Origin};
use itertools::Itertools;
use log::{info, trace};
use melee_utils::{replace_symbols, ROOT};
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
        IntoParallelIterator, IntoParallelRefIterator, ParallelIterator,
    },
    str::ParallelString,
};
use std::{
    collections::HashMap, fs::File, num::ParseIntError, path::Path, str,
    sync::Arc,
};

fn anon_func<'a, E>(input: &'a str) -> IResult<&'a str, u32, E>
where
    E: ParseError<&'a str> + FromExternalError<&'a str, ParseIntError>,
{
    all_consuming(preceded(pair(alphanumeric1, char('_')), hex(8)))(input)
}

fn relative_path<'a>(path: &'a Path) -> &'a Path {
    path.strip_prefix(&*ROOT).unwrap_or(path.as_ref())
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
                        Some((
                            &obj[0..obj.len() - 2],
                            Arc::<str>::from(*name),
                            virt_addr,
                        ))
                    } else {
                        None
                    }
                }
                _ => None,
            }
        })
        .collect::<Vec<_>>();

    to_rename
        .into_iter()
        .sorted_by(|(a, _, _), (b, _, _)| a.cmp(b))
        .group_by(|(file, _, _)| *file)
        .into_iter()
        .map(|(key, group)| {
            let path = asm_files
                .get(key)
                .context("Failed to find asm file.")?
                .as_path();

            let replacements = group
                .map(|(_, from, addr)| {
                    trace!("found {} in {:#?}", &from, relative_path(path));
                    let to = format!(".L_{:8X}", addr);
                    Ok((Arc::<str>::from(from), Arc::from(to)))
                })
                .collect::<Result<HashMap<_, _, ahash::RandomState>>>()?;

            Ok((path, replacements))
        })
        .collect::<Result<Vec<_>>>()?
        .into_par_iter()
        .try_for_each(|(path, replacements)| {
            info!(
                "replacing {} symbols in {:#?}",
                replacements.len(),
                relative_path(path)
            );

            replace_symbols(path, &replacements).with_context(|| {
                format!(
                    "Failed to replace symbols in {:#?}",
                    relative_path(path)
                )
            })
        })?;

    Ok(())
}
