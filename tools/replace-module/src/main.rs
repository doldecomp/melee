use anyhow::{Context, Result};
use clap::Parser;
use globset::{Glob, GlobSet, GlobSetBuilder};
use itertools::Itertools;
use lazy_static::lazy_static;
use log::{debug, info};
use regex::Regex;
use std::{fs, io::Read, path::Path};
use walkdir::WalkDir;

#[derive(Parser)]
#[command(author, version, about, long_about = None)]
struct Opts {
    module: String,
    symbols: Option<String>,
}

lazy_static! {
    static ref GLOBSET: GlobSet = GlobSetBuilder::new()
        .add(Glob::new("./{asm,docs,src}/**/*.{s,c,h,dox,md}").unwrap())
        .add(Glob::new("./obj_files.mk").unwrap())
        .build()
        .unwrap();
    static ref SYMBOL_RE: Regex =
        Regex::new(r"(?:lbl|func)_([[:xdigit:]]{8})").unwrap();
}

fn main() -> Result<()> {
    env_logger::builder().format_timestamp_nanos().init();
    let cli: Opts = Opts::parse();

    let symbols = match &cli.symbols.filter(|s| s != "-") {
        Some(path) => {
            let mut contents = String::new();
            fs::File::open(path)
                .with_context(|| {
                    format!("Failed to open symbols file: {:?}", path)
                })?
                .read_to_string(&mut contents)
                .with_context(|| {
                    format!("Failed to read symbols file: {:?}", path)
                })?;
            contents
        }
        None => {
            let mut buffer = String::new();
            std::io::stdin().read_to_string(&mut buffer)?;
            buffer
        }
    };

    let addrs = SYMBOL_RE
        .captures_iter(&symbols)
        .map(|c| c[1].to_owned())
        .unique()
        .join("|");

    let regex = Regex::new(&format!(r"\b(?:lbl|func)_({})\b", addrs))?;
    info!("Regex is `{}`.", regex);

    for entry in WalkDir::new(".") {
        let entry = entry?;
        let path_buf = entry.path().to_path_buf();
        if entry.file_type().is_file() && GLOBSET.is_match(&path_buf) {
            replace_symbols(&cli.module, &regex, &path_buf)?;
        }
    }

    Ok(())
}

fn replace_symbols(module: &str, regex: &Regex, path: &Path) -> Result<()> {
    let content = fs::read_to_string(path)?;
    debug!("Searching {:?}.", path);

    let expr = format!("{module}_$1");
    let replaced = regex.replace_all(&content, expr);
    fs::write(path, replaced.as_ref())?;

    Ok(())
}
