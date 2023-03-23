use anyhow::{Context, Result};
use clap::Parser;
use itertools::Itertools;
use lazy_static::lazy_static;
use log::{debug, info};
use melee_utils::{replace_all, SRC_FILES};
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
    info!("Module is \"{}\" and regex is `{}`.", &cli.module, regex);

    replace_all(&regex, format!("{}_$1", &cli.module))
}
