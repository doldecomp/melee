use dadosod::doldisasm;

use argh::FromArgs;
use doldisasm::DolCmd;

#[derive(Debug, PartialEq, FromArgs)]
/// disassembly of wii/gc executable file
struct DadosodCmd {
    #[argh(subcommand)]
    executable: DadosodSubCmd,
}

#[derive(Debug, PartialEq, FromArgs)]
#[argh(subcommand)]
enum DadosodSubCmd {
    Dol(DolCmd),
    // Rel(RelCmd),
    // Rso(RsoCmd),
}

fn main() {
    let cmd: DadosodCmd = argh::from_env();
    println!("Dadosods v{}\n", env!("CARGO_PKG_VERSION"));
    match cmd.executable {
        DadosodSubCmd::Dol(d) => d.run().unwrap(),
    }
}
