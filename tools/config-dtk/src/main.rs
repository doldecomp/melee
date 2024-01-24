use std::{
    collections::{BTreeMap, BTreeSet},
    ffi::OsString,
    fs::{self, File},
    io::{BufWriter, Write as IoWrite},
    path::{Path, PathBuf},
    process::exit,
};

use std::{path::Component::Normal, str};

use ahash::{AHashMap, AHashSet};
use anyhow::{Context, Result};
use dtk_config::{SplitKey, SplitValue};
use itertools::Itertools;
use log::{info, warn};
use pathdiff::diff_paths;

use clap::Parser as ClapParser;

pub(crate) mod cw_map;
pub(crate) mod dtk_config;
pub(crate) mod types;

#[derive(ClapParser)]
#[command(author, version, about, long_about = None)]
struct Cli {
    /// Generate splits.txt
    #[arg(long)]
    splits: bool,

    /// Generate symbols.txt
    #[arg(long)]
    symbols: bool,
}

fn root_path<P>(p: P) -> Result<PathBuf>
where
    P: AsRef<Path>,
{
    Ok(melee_utils::ROOT.join(p).canonicalize()?)
}

fn main() -> Result<()> {
    env_logger::init();
    let args = Cli::parse();

    let map_file = {
        let path = root_path("build/ssbm.us.1.2/GALE01.map")?;
        fs::read_to_string(path).context("Failed to read the map file")?
    };

    let in_txt_path = root_path("config/GALE01")?;

    if !args.splits && !args.symbols {
        eprintln!("Pass --splits and/or --symbols to write config files.");
        exit(1);
    }

    let tu_paths = resolve_tu_paths()?;

    let map_parser = cw_map::Parser::parse(&map_file, &tu_paths)?;

    if args.splits {
        // TODO write_splits(config_splits, map_spits)
        write_splits(&in_txt_path, &map_parser)?;
    }

    if args.symbols {
        // TODO write_symbols(config_symbols, map_symbols)
        write_symbols(&in_txt_path, map_parser)?;
    }

    Ok(())
}

fn write_symbols(
    in_txt_path: &PathBuf,
    mut map_parser: cw_map::Parser<'_>,
) -> Result<(), anyhow::Error> {
    let in_symbols_path = in_txt_path.join("symbols.txt");
    let symbols_file = fs::read_to_string(&in_symbols_path)?;
    let mut config_symbols = dtk_config::parse_symbols(&symbols_file)?;
    let sorted_keys = map_parser
        .table_symbols
        .iter()
        .map(|(key, sym)| (sym.addr, *key))
        .collect::<BTreeMap<_, _>>();
    let mut prev_addr: Option<u32> = None;
    for (_, key) in sorted_keys.iter().rev() {
        let sym = map_parser.table_symbols.get_mut(key).unwrap();
        if let (Some(prev_addr), 0) = (prev_addr, sym.size) {
            sym.size = prev_addr - sym.addr;
        }
        prev_addr = Some(sym.addr);
    }
    for (addr, sym) in config_symbols.iter_mut() {
        if let Some(key) = sorted_keys.get(addr) {
            if let Some(tree_sym) = map_parser.tree_symbols.get(key) {
                if !sym.is_named() {
                    sym.name = &tree_sym.name;
                }

                if sym.scope.is_none() {
                    sym.scope = Some(tree_sym.scope);
                }
            }
        }
    }
    let path = &in_symbols_path;
    let file = File::create(path)?;
    let mut w = BufWriter::new(file);
    info!(
        "Writing symbols to {}",
        path.to_str()
            .context("Failed to convert the path to a string")?
    );
    Ok(for sym in config_symbols.values() {
        writeln!(w, "{}", sym.to_txt()?)?;
    })
}

fn get_earliest_start(splits: &Vec<(SplitKey, SplitValue)>) -> u32 {
    splits
        .iter()
        .find_or_last(|(key, _)| key.section == ".text")
        .map(|(_, value)| value.start)
        .unwrap()
}

fn write_splits(
    in_txt_path: &PathBuf,
    map_parser: &cw_map::Parser<'_>,
) -> Result<(), anyhow::Error> {
    let in_splits_path = in_txt_path.join("splits.txt");
    let splits_file = fs::read_to_string(&in_splits_path)?;
    let mut config_splits = dtk_config::parse_splits(&splits_file)?;
    let path = &in_splits_path;
    let file = File::create(path)?;

    let mut w = BufWriter::new(file);
    info!(
        "Writing splits to {}",
        path.to_str()
            .context("Failed to convert the path to a string")?
    );
    writeln!(w, "{}", config_splits.layout)?;

    for split in &map_parser.splits {
        // TODO: Use SplitKey and SplitValue in cw_map
        if split.end.is_none() {
            continue;
        }
        let key = SplitKey {
            tu: split.tu,
            section: split.section,
        };
        if config_splits.splits.contains_key(&key) {
            continue;
        }
        config_splits.splits.insert(
            key,
            SplitValue {
                start: split.start,
                end: split.end.unwrap(),
            },
        );
    }

    let groups = config_splits
        .splits
        .into_iter()
        .group_by(|kvp| kvp.0.tu)
        .into_iter()
        .map(|(key, group)| {
            let group = group
                .sorted_by(|a, b| a.1.start.cmp(&b.1.start))
                .collect_vec();
            (key, group)
        })
        .into_iter()
        .sorted_by(|a, b| {
            get_earliest_start(&a.1).cmp(&get_earliest_start(&b.1))
        })
        .collect_vec();

    for (tu, sections) in groups {
        writeln!(w, "\n{}.c:", tu)?;
        for (key, value) in sections {
            writeln!(
                w,
                "\t{:<11} start:{:#010X} end:{:#010X}",
                key.section, value.start, value.end
            )?;
        }
    }
    Ok(())
}

fn make_os_str_set(strs: Vec<&str>) -> AHashSet<OsString> {
    strs.into_iter().map(OsString::from).collect()
}

fn resolve_tu_paths() -> Result<AHashMap<String, String>> {
    let root = &*melee_utils::ROOT;
    let paths = melee_utils::walk_src()?;
    let os_exts = make_os_str_set(vec!["h", "c", "s"]);
    let h_ext = OsString::from("h");
    let heads = make_os_str_set(vec!["asm", "src"]);
    let mut map = BTreeMap::<String, (bool, BTreeSet<String>)>::new();

    for path in paths {
        let ext = match path.extension() {
            Some(v) if !os_exts.contains(v) => {
                continue;
            }
            None => continue,
            Some(v) => v,
        };

        let diff = diff_paths(&path, &root).with_context(|| {
            format!("failed to diff {:?} with {:?}", path, root)
        })?;
        match diff.components().next() {
            Some(Normal(v)) if !heads.contains(v) => {
                continue;
            }
            None => continue,
            Some(_) => (),
        }

        let key = path
            .file_stem()
            .context("path had no file stem")?
            .to_str()
            .context("failed to convert the file stem to a str")?
            .to_owned();

        let value = diff
            .iter()
            .skip(1)
            .collect::<PathBuf>()
            .with_extension("")
            .to_str()
            .context("failed to convert the path to a str")?
            .to_owned();

        let entry = map.entry(key).or_default();
        entry.0 |= ext != h_ext;
        entry.1.insert(value);
    }

    Ok(map
        .into_iter()
        .filter_map(|(key, (is_obj, value))| {
            if !is_obj {
                return None;
            }
            match value.len() {
                0 => unreachable!(),
                1 => Some((key, value.into_iter().next().unwrap())),
                2.. => {
                    warn!(
                        "ambiguous translation unit \"{}\"\n{}",
                        key,
                        value.into_iter().collect::<Vec<_>>().join("\n")
                    );
                    None
                }
            }
        })
        .collect())
}
