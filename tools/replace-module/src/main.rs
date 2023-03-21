use anyhow::Result;
use clap::Parser;
use globset::{Glob, GlobSet, GlobSetBuilder};
use lazy_static::lazy_static;
use log::{debug, error, info, warn};
use regex::Regex;
use std::path::Path;
use std::{env, fs};
use walkdir::WalkDir;

#[derive(Parser)]
#[command(author, version, about, long_about = None)]
struct Opts {
    module: String,
    symbols: Vec<String>,
}

lazy_static! {
    static ref GLOBSET: GlobSet = {
        let mut builder = GlobSetBuilder::new();
        builder.add(Glob::new("./{asm,docs,src}/**/*.{c,h,dox,md}").unwrap());
        builder.build().unwrap()
    };
    static ref SYMBOL_REGEX: Regex =
        Regex::new(r"(lbl|func_)([[:xdigit:]]{8})").unwrap();
}

fn main() -> Result<()> {
    env_logger::builder().format_timestamp_nanos().init();
    let cli: Opts = Opts::parse();
    melee_utils::set_current_dir()?;

    let addrs: Vec<String> = cli
        .symbols
        .iter()
        .filter_map(|symbol| queue_symbol(symbol))
        .collect();

    let regex = Regex::new(&format!(r"\b(lbl|func)_({})\b", addrs.join("|")))?;

    for entry in WalkDir::new(".") {
        let entry = entry?;
        let path_buf = entry.path().to_path_buf();
        if entry.file_type().is_file() && GLOBSET.is_match(&path_buf) {
            replace_symbols(&cli.module, &regex, &path_buf)?;
        }
    }

    Ok(())
}

fn queue_symbol(symbol: &str) -> Option<String> {
    if let Some(captures) = SYMBOL_REGEX.captures(symbol) {
        Some(captures[2].to_string())
    } else {
        None
    }
}

fn replace_symbols(module: &str, regex: &Regex, path: &Path) -> Result<()> {
    let content = fs::read_to_string(path)?;

    let expr = format!("{module}_$2");
    let replaced = regex.replace_all(&content, expr);
    debug!("{replaced}");
    // fs::write(path, replaced.as_ref())?;

    Ok(())
}
