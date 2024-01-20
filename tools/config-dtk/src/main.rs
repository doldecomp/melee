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
    let symbols_file = fs::read_to_string(in_txt_path.join("symbols.txt"))?;

    let mut map_parser = {
        let root = &root_path("src")?;
        let paths = melee_utils::walk_src()?;
        cw_map::Parser::parse(&map_file, root, paths)?
    };

    let mut config_parser = dtk_config::Parser::parse_symbols(&symbols_file)?;

    let sorted_keys = map_parser
        .table_symbols
        .iter()
        .map(|(key, sym)| (sym.addr, *key))
        .collect::<BTreeMap<_, _>>();

    let mut prev_addr: Option<NonZeroU32> = None;
    for (_, key) in sorted_keys.iter().rev() {
        let sym = map_parser.table_symbols.get_mut(key).unwrap();
        if let (Some(prev_addr), 0) = (prev_addr, sym.size) {
            sym.size = prev_addr.get() - sym.addr.get();
        }
        prev_addr = Some(sym.addr);
    }

    {
        let file = File::create(&out_symbols_path)?;
        info!(
            "Writing symbols to {}",
            out_symbols_path
                .to_str()
                .context("Failed to convert the path to a string")?
        );

        let mut writer = BufWriter::new(file);

        for key in sorted_keys.values() {
            let table_sym = map_parser
                .table_symbols
                .get(&*key)
                .context("could not retrieve table symbol again")?;

            let tree_sym = match map_parser.tree_symbols.get(key) {
                Some(v) => v,
                None => {
                    warn!("missing tree symbol for {:08x}", table_sym.addr);
                    continue;
                }
            };

            write!(
                writer,
                "{} = {}:0x{:08X}; // type:{} size:0x{:X} scope:{}",
                tree_sym.name,
                table_sym.section,
                table_sym.addr,
                tree_sym.r#type,
                table_sym.size,
                tree_sym.scope,
            )?;
            if let Some(align) = table_sym.align.map(|nz| nz.get()) {
                write!(writer, " align:{}", align)?;
            }
            writeln!(writer)?;
        }
    }

    {
        let mut file = std::io::stdout().lock();
        for (_, sym) in config_parser.symbols {
            writeln!(file, "{:X?}", sym)?;
        }
    }

    Ok(())
}
