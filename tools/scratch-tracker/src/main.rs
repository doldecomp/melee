mod address;
mod decompme_api;
mod dtk_config;
mod parse;
mod scratch;
mod scratch_config;

use crate::{address::Address, scratch::Scratch};
use anyhow::Result;
use clap::{Parser, Subcommand};
use env_logger;
use rayon::slice::ParallelSliceMut;
use std::process;
use url::Url;

#[derive(Debug, Parser)]
#[command(author, version, about, long_about = None)]
struct ProgramArgs {
    #[command(subcommand)]
    command: Commands,
}

#[derive(Debug, Subcommand)]
enum Commands {
    List { addr: Address },
    Refresh,
    Seed { from: Option<Url> },
    Update,
}

fn try_main(args: ProgramArgs) -> Result<()> {
    use Commands::*;
    match args.command {
        List { addr } => list(addr)?,
        Refresh => refresh()?,
        Seed { from } => seed(from)?,
        Update => update()?,
    }
    Ok(())
}

fn refresh() -> Result<()> {
    let mut scratches = scratch_config::load()?;
    scratch_config::fix_families(&mut scratches)?;
    scratch_config::save(&mut scratches)?;
    Ok(())
}

fn list(addr: Address) -> Result<()> {
    const URL: &str = "https://decomp.me/scratch/";
    const EMPTY_CELL: &str = "-";
    const EMPTY_WIDTH: usize = EMPTY_CELL.len();
    let mut scratches: Vec<_> = scratch_config::load()?
        .into_iter()
        .filter(|s| s.addr == addr)
        .collect();
    scratches.par_sort_unstable_by(Scratch::txt_order);

    let name_width = scratches
        .iter()
        .map(|s| s.name.len())
        .max()
        .unwrap_or_default();

    let author_width = scratches
        .iter()
        .map(|s| s.author.as_ref().map_or(EMPTY_WIDTH, |a| a.len()))
        .max()
        .unwrap_or_default();

    for scratch in scratches {
        println!(
            "{:<name_width$} {:<author_width$} {:>6} {}",
            scratch.name,
            scratch.author.unwrap_or(EMPTY_CELL.to_owned()),
            scratch.completion.to_string(),
            format!("{}{}", URL, scratch.id)
        );
    }

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
