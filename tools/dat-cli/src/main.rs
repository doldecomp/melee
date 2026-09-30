mod cmd;

use anyhow::Result;

#[derive(clap::Parser)]
struct Cli {
    #[command(subcommand)]
    command: Commands,
}

#[derive(clap::Subcommand)]
enum Commands {
    /// Inspect the types described by the DWARF build
    Types(cmd::types::Args),

    /// Inspect the archive symbols the code loads by name
    Symbols(cmd::symbols::Args),

    /// Manage DAT samples for objdiff
    Samples(cmd::samples::Args),
}

fn main() -> Result<()> {
    env_logger::init();
    match <Cli as clap::Parser>::parse().command {
        Commands::Types(args) => cmd::types::run(args),
        Commands::Symbols(args) => cmd::symbols::run(args),
        Commands::Samples(args) => cmd::samples::run(args),
    }
}
