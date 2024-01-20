use std::{
    collections::BTreeMap,
    fs::{self, File},
    io::{stdout, BufWriter, Write as IoWrite},
    marker::PhantomData,
    num::NonZeroU32,
    path::{Path, PathBuf},
    str,
};

use ahash::AHashMap;
use anyhow::{anyhow, Context, Result};
use cw_map::Parser;
use log::{info, warn};

pub(crate) mod cw_map;
pub(crate) mod dtk_config;

#[derive(Default)]
struct ConfigWriter<'a> {
    src_paths: AHashMap<String, PathBuf>,
    _todo: PhantomData<&'a str>,
}

fn root_path<P>(p: P) -> Result<PathBuf>
where
    P: AsRef<Path>,
{
    Ok(melee_utils::ROOT.join(p).canonicalize()?)
}

fn main() -> Result<()> {
    env_logger::init();

    let map_file = {
        let path = root_path("build/ssbm.us.1.2/GALE01.map")?;
        fs::read_to_string(path).context("Failed to read the map file")?
    };

    let out_txt_path = root_path("build/GALE01")?;
    let out_splits_path = out_txt_path.join("splits.txt");
    let out_symbols_path = out_txt_path.join("symbols.txt");

    let in_txt_path = root_path("config/GALE01")?;
    let in_symbols_path = in_txt_path.join("symbols.txt");
    let symbols_file = fs::read_to_string(&in_symbols_path)?;

    let mut map_parser = {
        let root = &root_path("src")?;
        let paths = melee_utils::walk_src()?;
        cw_map::Parser::parse(&map_file, root, paths)?
    };

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

    {
        let path = &in_symbols_path;
        let file = File::create(path)?;
        let mut writer = BufWriter::new(file);

        info!(
            "Writing symbols to {}",
            path.to_str()
                .context("Failed to convert the path to a string")?
        );

        for sym in config_symbols.values() {
            writeln!(writer, "{}", sym.to_txt()?)?;
        }
    }

    Ok(())
}
