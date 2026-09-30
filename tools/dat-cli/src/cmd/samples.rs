use anyhow::Result;
use melee_dat::{config::get_config, hsd::Archive};
use std::fs;

#[derive(clap::Args)]
pub struct Args {
    #[command(subcommand)]
    command: Command,
}

#[derive(clap::Subcommand)]
enum Command {
    /// Check the current config
    Check(args::Check),

    /// Dump information about all configured DAT files
    Dump(args::Dump),

    /// Build a sample object from a DAT file
    Build(args::Build),
}

mod args {
    use clap::Args;
    use std::path::PathBuf;

    #[derive(Args)]
    pub struct Check {
        pub cfg_path: PathBuf,
        #[arg(short = 'p', long)]
        pub proj_path: Option<PathBuf>,
    }

    #[derive(Args)]
    pub struct Dump {
        pub dat_path: PathBuf,
    }

    #[derive(Args)]
    pub struct Build {
        pub dat_path: PathBuf,
        pub obj_path: PathBuf,
    }
}

pub fn run(Args { command }: Args) -> Result<()> {
    match command {
        Command::Check(args) => check(args),
        Command::Dump(args) => dump(args),
        Command::Build(args) => build(args),
    }
}

fn check(args: args::Check) -> Result<()> {
    let config = get_config(args.proj_path.as_ref(), args.cfg_path)?;
    dbg!(config);
    Ok(())
}

fn dump(args: args::Dump) -> Result<()> {
    let bytes = fs::read(args.dat_path)?;
    let archive = Archive::parse(&bytes)?;
    println!("{:#?}", archive);
    Ok(())
}

fn build(args: args::Build) -> Result<()> {
    let dat = fs::read(&args.dat_path)?;
    let archive = Archive::parse(&dat)?;
    let obj = archive.to_object()?;
    fs::write(&args.obj_path, obj)?;
    Ok(())
}
