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

    /// The native archive interface: its tables, and what it should reach
    Native(cmd::native::Args),
}

fn main() -> Result<()> {
    env_logger::init();
    let result = match <Cli as clap::Parser>::parse().command {
        Commands::Types(args) => cmd::types::run(args),
        Commands::Symbols(args) => cmd::symbols::run(args),
        Commands::Samples(args) => cmd::samples::run(args),
        Commands::Native(args) => cmd::native::run(args),
    };
    // Output piped into e.g. `head` ends early; that's not an error
    match result {
        Err(e)
            if e.downcast_ref::<std::io::Error>().is_some_and(|e| {
                e.kind() == std::io::ErrorKind::BrokenPipe
            }) =>
        {
            Ok(())
        }
        result => result,
    }
}
