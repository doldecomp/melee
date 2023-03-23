use anyhow::{Context, Result};
use clap::Parser;
use goblin::elf::{sym::STB_GLOBAL, Elf};
use regex::Regex;
use std::fs::File;
use std::io::Read;
use std::path::PathBuf;

#[derive(Parser)]
#[command(author, version, about, long_about = None)]
struct Args {
    elf: PathBuf,
}

fn main() -> Result<()> {
    let args = Args::parse();

    let mut elf_file =
        File::open(&args.elf).context("Failed to open ELF file")?;

    let mut elf_data = Vec::new();
    elf_file
        .read_to_end(&mut elf_data)
        .expect("Failed to read ELF file");

    let elf = Elf::parse(&elf_data).expect("Failed to parse ELF file");

    let text_section = elf
        .section_headers
        .iter()
        .find(|sh| {
            let sh_name = elf.shdr_strtab.get_at(sh.sh_name).unwrap();
            sh_name == ".text"
        })
        .expect("Failed to find .text section");

    let re = Regex::new(r"\w+_([0-9a-fA-F]{8})").unwrap();

    for symbol in elf.syms.iter() {
        if symbol.st_value >= text_section.sh_addr
            && symbol.st_value < text_section.sh_addr + text_section.sh_size
        {
            let name = elf.strtab.get_at(symbol.st_name).unwrap();
            if symbol.st_bind() == STB_GLOBAL {
                continue;
            }

            let new_name = if let Some(captures) = re.captures(name) {
                format!(".L{}", captures.get(1).unwrap().as_str())
            } else {
                format!(".L{}", name)
            };

            println!("{} -> {}", name, new_name);
        }
    }
    Ok(())
}
