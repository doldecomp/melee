use crate::mw_map::{
    regex::{EMPTY_RE, LINKER_SYM_RE},
    types,
};
use ::regex::Regex;
use anyhow::{anyhow, Context, Result};
use internment::Intern;
use log::trace;
use std::{
    fs::File,
    io::{BufRead, BufReader},
    path::Path,
};

use super::regex::SECTION_SYM_RE;

enum State {
    PreLinker,
    LinkerSym(types::LinkerSym),
    PreSection,
    Section(types::Section),
    SectionSym(types::SectionSym),
    PreMemoryMap,
    MemoryMap,
    PreLinkerGenSym,
    LinkGenSym,
    EOF,
}

impl State {
    fn regex(&self) -> &Regex {
        match self {
            State::PreLinker => &EMPTY_RE,
            State::LinkerSym(_) => &LINKER_SYM_RE,
            State::PreSection => &EMPTY_RE,
            State::Section(_) => todo!(),
            State::SectionSym(_) => &SECTION_SYM_RE,
            State::PreMemoryMap => &EMPTY_RE,
            State::MemoryMap => todo!(),
            State::PreLinkerGenSym => &EMPTY_RE,
            State::LinkGenSym => todo!(),
            State::EOF => &EMPTY_RE,
        }
    }
}

fn parse_linker(
    lines: &mut impl Iterator<Item = Result<String, std::io::Error>>,
) -> Result<Vec<types::LinkerSym>> {
    for res in lines {
        match LINKER_SYM_RE.captures(&res?) {
            None => break,
            Some(caps) => {
                let depth = caps
                    .name("depth")
                    .context("Failed to parse the symbol depth.")?
                    .as_str()
                    .parse::<usize>()?;

                let name = Intern::new({
                    use types::SymName::*;
                    match ["name", "label"]
                        .map(|s| caps.name(s).map(|m| m.as_str()))
                    {
                        [Some(name), None] => Named {
                            name: Intern::from_ref(name),
                        },
                        [None, Some(label)] => Relative {
                            label: label.parse::<usize>()?,
                        },
                        _ => unreachable!("Unexpected name group value."),
                    }
                });

                let instance = caps
                    .name("instance")
                    .map(|s| s.as_str().parse::<usize>())
                    .transpose()?;

                let src = {
                    use types::SymSrc::*;
                    match ["linker", "file", "ext"]
                        .map(|s| caps.name(s).map(|m| m.as_str()))
                    {
                        [Some("linker"), None, None] => Ok(Linker),
                        [None, Some(file), Some(ext)] => Ok(Object {
                            file: Intern::from_ref(file),
                            ext: Intern::from_ref(ext),
                        }),
                        [None, None, None] => {
                            Err(anyhow!("Failed to parse the symbol name."))
                        }
                        [_, _, _] => {
                            unreachable!("Unexpected linker group.")
                        }
                    }
                }?;

                trace!(
                    r"{{
    depth: {depth},
    src: {src:#?}
    name: {name:#?},
    instance: {instance:#?},
}}"
                );
            }
        }
    }
    todo!()
}

impl types::Map {
    pub fn parse(map_path: &Path) -> Result<types::Map> {
        let file = File::open(map_path)?;
        let reader = BufReader::new(file);
        // let writer = BufWriter::new(File::open())

        // TODO skip head line by match
        let lines = reader.lines();

        parse_linker(&mut lines.skip(1))?;
        todo!()
    }
}

#[cfg(test)]
mod tests {
    use super::types::Map;
    use crate::utils::ROOT;
    use log::trace;

    fn init_logger() {
        let _ = env_logger::builder()
            .is_test(true)
            .filter_level(log::LevelFilter::Debug)
            .try_init();
    }

    #[test]
    fn test_parse_map() {
        init_logger();
        let path = &*ROOT.join("build/ssbm.us.1.2/GALE01.map");
        let result = Map::parse(path);

        match result {
            Ok(parsed_map) => {
                trace!("Parsed map: {:#?}", parsed_map);
            }
            Err(e) => {
                panic!("Error parsing map: {}", e);
            }
        }
    }
}
