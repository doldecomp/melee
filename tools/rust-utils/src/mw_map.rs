use anyhow::{anyhow, bail, Context, Result};
use internment::Intern;
use lazy_static::lazy_static;
use log::{debug, trace};
use regex::{Match, Regex, RegexSet};
use std::{
    fs::File,
    io::{BufRead, BufReader, BufWriter, Lines},
    path::Path,
};

macro_rules! regex_expect {
    ($regex:expr) => {
        $regex.expect(&format!("Failed to compile {}.", stringify!($regex)))
    };
}

macro_rules! create_regex {
    ($name:ident, $regex:expr) => {
        lazy_static! {
            static ref $name: Regex = Regex::new($regex)
                .expect(&format!("Failed to compile {}.", stringify!($name)));
        }
    };
}

create_regex!(EMPTY_RE, "^$");
create_regex!(
    LINKER_SYM_RE,
    r"(?xm) # Ignore whitespace, multiline
        # Start of line with leading spaces
        ^\x20*

        # Linker depth
        (?P<depth>[[:digit:]]+)\]\x20

        # Name of the symbol (word with dots allowed, or @ + number)
        (?:
            (?P<name>[\.[:word:]]+) |
            @(?P<label>[[:digit:]]+)
        )
        # Data symbols can be instanced with $ and then a number
        (?:\$(?P<instance>[[:digit:]]+))?
        \x20

        # Source of a symbol is either the linker or a file
        (?:
            found\x20as\x20(?P<linker>linker)\x20generated\x20symbol |

            # Non-linker symbols have a type and a scope
            \(
            (?P<type>section|object|func|notype),
            (?P<scope>global|local|weak)
            \)\x20found\x20in\x20
            (?P<file>[\.[:word:]]+?)
            \.(?P<ext>\w+)\.o\x20
        )$"
);
create_regex!(
    SECTION_SYM_RE,
    r"(?xm) # Ignore whitespace, multiline

        # Start of line with two spaces
        ^\x20{2}

        # Starting address (8-digit hex)
        (?P<addr>[[:xdigit:]]{8})

        \x20

        # Size (6-digit hex)
        (?P<size>[[:xdigit:]]{6})


        \x20

        # Virtual address (8-digit hex)
        (?P<virt_addr>[[:xdigit:]]{8})

        # Optional alignment value
        (?:
           \x20{2}
           (?P<align>[[:digit:]])
        )?

        \x20

        # Name of the symbol (word with dots allowed, optional @ prefix)
        (?P<name>
            @?[\.[:word:]]+
        )

        # Parent symbol or section (optional)
        (?:
            \x20\(entry\x20of\x20(?P<parent>
                @?[\.\w]+?
            )
            \)
        )?

        \x20\t

        # Filename with .o extension
        (?P<file>
            [[:word:]\x20\.]+
        )

        # Source file extension
        \.
        (?P<ext>
            \w+
        )

        # Don't capture .o extension
        \.o
        \x20

        # End of line
        $"
);

#[derive(Debug)]
enum SymSrc {
    Linker,
    Object {
        file: Intern<String>,
        ext: Intern<String>,
    },
}

#[derive(Default, Debug, PartialEq, Eq, Hash)]
enum SymName {
    #[default]
    Unknown,
    Relative {
        label: usize,
    },
    Named {
        name: Intern<String>,
    },
}

#[derive(Default, Debug)]
struct LinkerSym {
    depth: usize,
    name: SymName,
    instance: Option<usize>,
    parent: Option<Intern<Sym>>,
    file: String,
    ext: String,
}

#[derive(Default, Debug)]
struct SectionSym {
    addr: usize,
    size: usize,
    virt_addr: usize,
    align: Option<usize>,
    name: SymName,
    file: String,
    ext: String,
}

#[derive(Default, Debug)]
struct Sym {
    depth: usize,
    addr: usize,
    size: usize,
    virt_addr: usize,
    align: Option<usize>,
    name: SymName,
    instance: Option<usize>,
    parent: Option<Intern<Sym>>,
    file: String,
    ext: String,
}

#[derive(Default, Debug)]
struct Section {
    name: Intern<String>,
    syms: Vec<Sym>,
}

#[derive(Default, Debug)]
struct Map {
    sections: Vec<Section>,
}

enum State {
    PreLinker,
    LinkerSym,
    PreSection,
    Section,
    SectionSym,
    PreMemoryMap,
    MemoryMap,
    PreLinkerGenSym,
    LinkGenSym,
}

impl State {
    fn regex(&self) -> Option<&Regex> {
        use State::*;

        match self {
            PreLinker => None,
            _ => todo!(),
        }
    }
}

fn parse_linker(
    lines: &mut impl Iterator<Item = Result<String, std::io::Error>>,
) -> Result<Vec<LinkerSym>> {
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
                    use SymName::*;
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
                    use SymSrc::*;
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
impl Map {
    pub fn parse(map_path: &Path) -> Result<Map> {
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
    use super::Map;
    use crate::ROOT;
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
