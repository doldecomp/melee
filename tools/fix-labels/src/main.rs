use anyhow::{Context, Result};
use clap::Parser;
use goblin::{elf::Elf, elf32::sym::STB_LOCAL};
use lazy_static::lazy_static;
use melee_utils::{replace, walk_src};
use regex::{Regex, RegexBuilder};
use std::{fs::File, io::Read, path::PathBuf, usize};

#[derive(Parser)]
#[command(author, version, about, long_about = None)]
struct Args {
    elf: PathBuf,
}

lazy_static! {
    static ref UNK_FUNC_RE: Regex = Regex::new(r"^\w+_80([[:xdigit:]]{6})$")
        .expect("Failed to parse UNK_FUNC_RE.");
}

fn main() -> Result<()> {
    env_logger::builder().format_timestamp_nanos().init();
    let args = Args::parse();

    let mut elf_file =
        File::open(&args.elf).context("Failed to open ELF file")?;

    let mut elf_data = Vec::new();
    elf_file
        .read_to_end(&mut elf_data)
        .context("Failed to read ELF file")?;

    let elf = Elf::parse(&elf_data).context("Failed to parse ELF file")?;

    let text_section = elf
        .section_headers
        .iter()
        .filter(|sh| {
            let name = elf.shdr_strtab.get_at(sh.sh_name);
            name == Some(".text")
        })
        .next()
        .context("Failed to find the text section.")?;

    let text_range =
        (text_section.sh_addr + 0xA0B8)..(text_section.sh_addr + 0xFF74);

    let regex = RegexBuilder::new(&format!(r"\b\w+_80({})\b", {
        let vec = elf
            .syms
            .iter()
            .filter(|sym| {
                text_range.contains(&sym.st_value)
                    && sym.st_bind() == STB_LOCAL
            })
            .map(|sym| {
                let name = elf
                    .strtab
                    .get_at(sym.st_name)
                    .context("Failed to get the symbol name.")?
                    .to_owned();

                Ok(name)
            })
            .filter_map(|res| {
                res.and_then(|name| {
                    UNK_FUNC_RE
                        .captures(&name)
                        .map(|capture| {
                            capture
                                .get(1)
                                .map(|group| group.as_str().to_owned())
                                .context(
                                    "Failed to get the first capture group \
                                            from UNK_FUNC_RE.",
                                )
                        })
                        .transpose()
                })
                .transpose()
            })
            .collect::<Result<Vec<_>>>()?;
        assert!(vec.len() > 0);
        vec.join("|")
    }))
    .size_limit(usize::MAX)
    .build()?;

    println!("{regex:?}");
    for path in walk_src()? {
        // TODO They are local symbols so we can just replace per file
        replace(&regex, ".L$1", &path)?;
    }

    Ok(())
}
