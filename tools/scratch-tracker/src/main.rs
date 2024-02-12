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
use env_logger;
use rayon::prelude::*;
use std::process;
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
}

fn try_main(args: ProgramArgs) -> Result<()> {
    use Commands::*;
    match args.command {
        List { start, end } => list(start, end)?,
        Ok { start, end } => ok(start, end)?,
        Refresh => refresh()?,
        Seed { from } => seed(from)?,
        Update => update()?,
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

fn list(start: Address, end: Option<Address>) -> Result<()> {
    const URL: &str = "https://decomp.me/scratch/";
    const EMPTY_CELL: &str = "-";

    if end.is_some_and(|end| start > end) {
        bail!("start must come before end");
    }

    let mut scratches: Vec<_> = scratch_config::load()?
        .into_iter()
        .filter(|s| addr_in_range(&s.addr, &start, &end))
        .collect();
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
