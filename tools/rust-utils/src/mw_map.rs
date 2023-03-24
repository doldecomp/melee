use anyhow::{Context, Result};
use lazy_static::lazy_static;
use log::debug;
use regex::Regex;
use std::{
    fs::File,
    io::{BufRead, BufReader},
    path::Path,
};

lazy_static! {
    static ref LINKER_SYM_RE: Regex = Regex::new(
        r"(?xm) # Ignore whitespace, multiline
        # Start of line with leading spaces
        ^\x20*

        # Linker depth
        (?P<depth>[[:digit:]]+)\]\x20

        # Name of the symbol (word with dots allowed, optional @ prefix)
        (?P<name>@?[\.[:word:]]+)\x20

        # Source of a symbol is either the linker or a file
        (?:
            found\x20as\x20(?P<linker>linker)\x20generated\x20symbol |

            # Non-linker symbols have a type and a scope
            \(
            (?P<type>func|object|notype),
            (?P<scope>global|local)
            \)\x20found\x20in\x20
            (?P<file>[\.[:word:]]+?)
            \.(?P<ext>\w+)\.o\x20
        )$"
    )
    .expect("Failed to compile SYMBOL_RE.");
    static ref SECTION_SYM_RE: Regex = Regex::new(
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
    )
    .expect("Failed to compile SYMBOL_RE.");
}

enum MetrowerksSymbolSource<'a> {
    Linker,
    Object { file: &'a str, ext: &'a str },
}

#[derive(Default, Debug)]
enum MetrowerksSymbolName<'a> {
    #[default]
    Unknown,
    Relative {
        label: usize,
    },
    Named {
        name: &'a str,
    },
}

#[derive(Default, Debug)]
struct MetrowerksSymbol<'a> {
    depth: usize,
    addr: usize,
    size: usize,
    virt_addr: usize,
    align: Option<usize>,
    name: MetrowerksSymbolName<'a>,
    parent: Option<&'a MetrowerksSymbol<'a>>,
    file: String,
    ext: String,
}

#[derive(Default, Debug)]
struct MetrowerksSection<'a> {
    name: String,
    syms: Vec<MetrowerksSymbol<'a>>,
}

#[derive(Default, Debug)]
struct MetrowerksMap<'a> {
    sections: Vec<MetrowerksSection<'a>>,
}

impl<'a> MetrowerksMap<'a> {
    pub fn parse(path: &Path) -> Result<MetrowerksMap<'a>> {
        let file = File::open(path)?;
        let reader = BufReader::new(file);
        // let mut map = MetrowerksMap::default();
        // let mut section = &MetrowerksSection::default();

        for res in reader.lines() {
            let line = res?;
            if LINKER_SYM_RE.is_match(&line) {
                debug!("{}", line);
            }
        }

        todo!()
    }
}

#[cfg(test)]
mod tests {
    use crate::ROOT;

    use super::MetrowerksMap;

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

        // Call the parse function and handle any errors.
        let result = MetrowerksMap::parse(path);
        match result {
            Ok(parsed_map) => {
                println!("Parsed map: {:#?}", parsed_map);
            }
            Err(e) => {
                panic!("Error parsing map: {}", e);
            }
        }
    }
}
