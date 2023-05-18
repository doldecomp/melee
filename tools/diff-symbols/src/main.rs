use anyhow::{Context, Result};
use clap::Parser;
use cwparse::map::{self, Line};
use dashmap::DashMap;
use memmap2::Mmap;
use rayon::{
    self,
    prelude::{
        IntoParallelIterator, IntoParallelRefIterator, ParallelIterator,
    },
    slice::ParallelSliceMut,
    str::ParallelString,
};
use std::{
    fs::File,
    path::{Path, PathBuf},
    str,
    sync::Arc,
};

#[derive(Parser)]
#[command(author, version, about, long_about = None)]
struct Cli {
    /// Format output as an HTML table for GitHub
    #[arg(short, long)]
    table: bool,

    /// The map file whose symbols to import
    src: PathBuf,

    /// The map file of the current codebase
    dst: PathBuf,
}

struct Symbols {
    _file: File,
    _mmap: Mmap,
    _bytes: Arc<[u8]>,
    map: DashMap<u32, Arc<str>, ahash::RandomState>,
}

fn parse_symbols<P: AsRef<Path>>(path: P) -> Result<Symbols> {
    let file = File::open(path).context("Failed to open the map file.")?;

    let mmap = unsafe { Mmap::map(&file) }
        .context("Failed to create the memory map.")?;

    let bytes: Arc<[u8]> = Arc::from(mmap.as_ref());

    let input =
        str::from_utf8(&bytes).context("Failed to convert to UTF-8.")?;

    let lines = input
        .par_lines()
        .map(|line| map::line::<()>(line).map(|line| line.1))
        .collect::<Result<Vec<_>, _>>()
        .context("Failed to parse lines.")?;

    let map = lines
        .par_iter()
        .filter_map(|line| {
            use cwparse::{map::Identifier, section_table::Symbol};

            match line {
                Line::SectionSymbol(Symbol {
                    virt_addr,
                    id:
                        Identifier::Named {
                            name,
                            instance: None,
                        },
                    ..
                }) => Some((*virt_addr, Arc::from(*name))),
                _ => None,
            }
        })
        .collect::<DashMap<_, _, ahash::RandomState>>();

    Ok(Symbols {
        _file: file,
        _mmap: mmap,
        _bytes: bytes,
        map,
    })
}

fn main() -> Result<()> {
    let cli = Cli::parse();

    let symbols = [&cli.src, &cli.dst]
        .into_par_iter()
        .map(|p| {
            parse_symbols(p).with_context(|| {
                format!(
                    "Failed to read symbols from {}.",
                    p.as_os_str().to_string_lossy()
                )
            })
        })
        .collect::<Result<Vec<_>>>()?;

    let src = &symbols[0];
    let dst = &symbols[1];

    let mut combined = src
        .map
        .par_iter()
        .filter_map(|x| {
            let (addr, src) = x.pair();

            match dst.map.get(addr) {
                Some(dst) => {
                    let dst = dst.value();
                    if src == dst {
                        None
                    } else {
                        Some((*addr, src.clone(), dst.clone()))
                    }
                }
                None => None,
            }
        })
        .collect::<Vec<_>>();

    combined.par_sort_unstable_by_key(|(addr, _, _)| *addr);

    if cli.table {
        println!(
            "<details>\n\
            \x20 <summary>Renamed symbols</summary>\n\
            \x20 <table>\n\
            \x20   <tr><th>Address</th><th>From</th><th>To</th></tr>"
        );
    }

    for (addr, src, dst) in combined {
        if cli.table {
            println!(
                "    <tr>\
                 <td><code>{:8X}</code></td>\
                 <td><code>{}</code></td>\
                 <td><code>{}</code></td>\
                 </tr>",
                addr,
                dst.as_ref(),
                src.as_ref()
            );
        } else {
            println!("{}:{}", dst.as_ref(), src.as_ref());
        }
    }

    if cli.table {
        println!("  </table>\n</details>")
    }

    Ok(())
}
