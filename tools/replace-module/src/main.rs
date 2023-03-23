use anyhow::{Context, Result};
use clap::Parser;
use itertools::Itertools;
use lazy_static::lazy_static;
use log::info;
use melee_utils::{replace, walk_src};
use regex::Regex;
use std::{fs, io::Read};

#[derive(Parser)]
#[command(author, version, about, long_about = None)]
struct Args {
    prefix: String,
    symbols: Option<String>,
}

lazy_static! {
    static ref SYMBOL_RE: Regex =
        Regex::new(r"(?:lbl|func)_([[:xdigit:]]{8})").unwrap();
}

fn main() -> Result<()> {
    env_logger::builder().format_timestamp_nanos().init();
    let args = Args::parse();

    let symbols = match &args.symbols.filter(|s| s != "-") {
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

    let regex = Regex::new(&format!(
        r"\b(?:lbl|func)_({})\b",
        SYMBOL_RE
            .captures_iter(&symbols)
            .map(|c| c[1].to_owned())
            .unique()
            .join("|")
    ))?;

    info!("Prefix is \"{}\" and regex is `{}`.", &args.prefix, regex);
    let to = format!("{}_$1", &args.prefix);
    for path in walk_src()? {
        replace(&regex, &to, &path)?;
    }

    Ok(())
}
