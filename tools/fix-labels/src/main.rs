use goblin::elf::{sym::STB_GLOBAL, Elf};
use regex::Regex;
use std::env;
use std::fs::File;
use std::io::Read;

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        println!("Usage: {} <elf_file>", args[0]);
        return;
    }

    let elf_file_path = &args[1];
    let mut elf_file =
        File::open(elf_file_path).expect("Failed to open ELF file");

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
}
