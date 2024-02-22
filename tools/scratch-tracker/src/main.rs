mod address;
mod decompme_api;
mod dtk_config;
mod parse;
mod scratch;
mod scratch_config;

use crate::{address::Address, scratch::Scratch};
use anyhow::{bail, Result};
use clap::{Parser, Subcommand};
use decompme_api::Completion;
use dtk_config::addr_to_symbol;
use env_logger;
use rayon::prelude::*;
use scratch::try_parse_addr;
use std::{
    fs::{self, File},
    io::{BufWriter, Write},
    path::PathBuf,
    process,
};
use tabled::{
    builder::Builder,
    settings::{object::Columns, Alignment, Style},
};
use url::Url;

#[derive(Debug, Parser)]
#[command(author, version, about, long_about = None)]
struct ProgramArgs {
    #[command(subcommand)]
    command: Commands,
}

#[derive(Debug, Subcommand)]
enum Commands {
    List {
        start: Address,
        end: Option<Address>,
        #[arg(short, long)]
        no_ok: bool,
    },
    Ok {
        start: Address,
        end: Option<Address>,
    },
    Refresh,
    Seed {
        from: Option<Url>,
    },
    Update,
    Replace {
        #[arg(required = true)]
        paths: Vec<PathBuf>,
    },
}

fn try_main(args: ProgramArgs) -> Result<()> {
    use Commands::*;
    match args.command {
        List { start, end, no_ok } => list(start, end, no_ok)?,
        Ok { start, end } => ok(start, end)?,
        Refresh => refresh()?,
        Seed { from } => seed(from)?,
        Update => update()?,
        Replace { paths } => replace(paths)?,
    }
    Result::Ok(())
}

fn refresh() -> Result<()> {
    let mut scratches = scratch_config::load()?;
    scratch_config::fix_families(&mut scratches)?;
    scratch_config::save(&mut scratches)?;
    Ok(())
}

fn addr_in_range(
    value: &Address,
    start: &Address,
    end: &Option<Address>,
) -> bool {
    if let Some(end) = end {
        value >= start && value < end
    } else {
        value == start
    }
}

fn ok(start: Address, end: Option<Address>) -> Result<()> {
    if end.is_some_and(|end| start > end) {
        bail!("start must come before end");
    }

    let mut scratches = scratch_config::load()?;

    scratches
        .par_iter_mut()
        .filter(|s| addr_in_range(&s.addr, &start, &end))
        .for_each(|s| s.completion = Completion::Ok);

    scratch_config::save(&mut scratches)?;

    Ok(())
}

fn list(start: Address, end: Option<Address>, no_ok: bool) -> Result<()> {
    const URL: &str = "https://decomp.me/scratch/";
    const EMPTY_CELL: &str = "-";

    if end.is_some_and(|end| start > end) {
        bail!("start must come before end");
    }

    let mut scratches: Vec<_> = {
        let mut vec: Vec<_> = scratch_config::load()?
            .into_iter()
            .filter(|s| addr_in_range(&s.addr, &start, &end))
            .collect();

        if no_ok {
            vec.retain(|s| s.completion != Completion::Ok);
        }

        vec
    };
    scratches.par_sort_unstable_by(Scratch::txt_order);

    let mut builder = Builder::default();
    let show_addr = end.is_some_and(|end| start != end);
    let completion_col = 2 + if show_addr { 1 } else { 0 };

    for scratch in scratches {
        let mut record = Vec::new();
        if show_addr {
            record.push(scratch.addr.to_string());
        }
        record.extend(vec![
            scratch.name,
            scratch.author.unwrap_or(EMPTY_CELL.to_owned()),
            scratch.completion.to_string(),
            format!("{}{}", URL, scratch.id),
        ]);
        builder.push_record(record);
    }

    let mut table = builder.build();
    table
        .with(Style::empty())
        .modify(Columns::single(completion_col), Alignment::right());
    println!("{}", table);

    Ok(())
}

fn seed(from: Option<Url>) -> Result<()> {
    decompme_api::seed_loop(from, false)
}

fn update() -> Result<()> {
    decompme_api::seed_loop(None, true)
}

fn replace(paths: Vec<PathBuf>) -> Result<()> {
    for path in paths {
        let s = fs::read_to_string(&path)?;
        let f = File::create(&path)?;
        let mut w = BufWriter::new(f);
        replace_in_str(&mut w, &s)?;
    }
    Ok(())
}

fn replace_word<F: Fn(u32) -> Option<String>>(
    word: &str,
    lookup: F,
) -> String {
    try_parse_addr(word)
        .and_then(lookup)
        .unwrap_or_else(|| word.to_owned())
}

fn replace_in_str<W: Write>(w: &mut W, s: &str) -> Result<()> {
    let mut word = String::new();
    let lookup = addr_to_symbol()?;

    for c in s.chars() {
        match c {
            'a'..='z' | 'A'..='Z' | '0'..='9' | '_' => {
                word.push(c);
            }
            _ => {
                if !word.is_empty() {
                    w.write_all(&replace_word(&word, &lookup).as_bytes())?;
                    word.clear();
                }
                w.write_all(&[c as u8])?;
            }
        }
    }

    if !word.is_empty() {
        w.write_all(&replace_word(&word, &lookup).as_bytes())?;
    }

    Ok(())
}

fn main() {
    env_logger::init();
    let args = ProgramArgs::parse();

    match try_main(args) {
        Ok(_) => {
            log::info!("Finished");
        }
        Err(e) => {
            log::error!("Error: {:?}", e);
            process::exit(-1);
        }
    }
}
