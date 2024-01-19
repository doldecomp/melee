mod cw_map;

use ahash::AHashMap;
use anyhow::{Context as AnyhowContext, Result};
use cw_map::Context;
use log::{info, warn};
use std::{
    collections::BTreeMap,
    fs::File,
    io::{BufWriter, Write as IoWrite},
    marker::PhantomData,
    num::NonZeroU32,
    path::PathBuf,
    str,
};

#[derive(Default)]
struct ConfigWriter<'a> {
    src_paths: AHashMap<String, PathBuf>,
    _todo: PhantomData<&'a str>,
}

fn main() -> Result<()> {
    env_logger::init();

    let map_path = melee_utils::ROOT
        .join("build/ssbm.us.1.2/GALE01.map")
        .canonicalize()?;
    let map_file =
        File::open(&map_path).context("Failed to open the map file.")?;
    let mmap = unsafe { memmap2::Mmap::map(&map_file) }
        .context("Failed to create the memory map.")?;
    let input = str::from_utf8(mmap.as_ref())
        .context("Failed to convert to UTF-8.")?;

    let txt_path = melee_utils::ROOT.join("build/GALE01").canonicalize()?;
    let splits_path = txt_path.join("splits.txt");
    let symbols_path = txt_path.join("symbols.txt");

    let mut ctx = {
        let root = &melee_utils::ROOT.join("src");
        let paths = melee_utils::walk_src()?;
        Context::parse(input, root, paths)?
    };

    let sorted_keys = ctx
        .table_symbols
        .iter()
        .map(|(key, sym)| (sym.addr, *key))
        .collect::<BTreeMap<_, _>>();

    let mut prev_addr: Option<NonZeroU32> = None;
    for (_, key) in sorted_keys.iter().rev() {
        let sym = ctx.table_symbols.get_mut(key).unwrap();
        if let (Some(prev_addr), 0) = (prev_addr, sym.size) {
            sym.size = prev_addr.get() - sym.addr.get();
        }
        prev_addr = Some(sym.addr);
    }

    let file = File::create(&symbols_path)?;
    info!(
        "Writing symbols to {}",
        symbols_path
            .to_str()
            .context("Failed to convert the path to a string")?
    );

    let mut writer = BufWriter::new(file);

    for key in sorted_keys.values() {
        let table_sym = ctx
            .table_symbols
            .get(&*key)
            .context("could not retrieve table symbol again")?;

        let tree_sym = match ctx.tree_symbols.get(key) {
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

    Ok(())
}
