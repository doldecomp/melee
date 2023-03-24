use anyhow::{Context, Result};
use internment::Intern;
use lazy_static::lazy_static;
use log::{debug, trace};
use regex::{Match, Regex};
use std::{
    fs::File,
    io::{BufRead, BufReader},
    path::Path,
};
use MetrowerksSymbolName::{Named, Relative};

lazy_static! {
    static ref LINKER_SYM_RE: Regex = Regex::new(
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

#[derive(Debug)]
enum MetrowerksSymbolSource {
    Linker,
    Object {
        file: Intern<String>,
        ext: Intern<String>,
    },
}

#[derive(Default, Debug, PartialEq, Eq, Hash)]
enum MetrowerksSymbolName {
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
struct MetrowerksSymbol {
    depth: usize,
    addr: usize,
    size: usize,
    virt_addr: usize,
    align: Option<usize>,
    name: MetrowerksSymbolName,
    instance: Option<usize>,
    parent: Option<Intern<MetrowerksSymbol>>,
    file: String,
    ext: String,
}

#[derive(Default, Debug)]
struct MetrowerksSection {
    name: Intern<String>,
    syms: Vec<MetrowerksSymbol>,
}

#[derive(Default, Debug)]
struct MetrowerksMap {
    sections: Vec<MetrowerksSection>,
}

impl MetrowerksMap {
    pub fn parse(path: &Path) -> Result<MetrowerksMap> {
        let file = File::open(path)?;
        let reader = BufReader::new(file);

        // TODO skip head line by match
        for res in reader.lines().skip(1) {
            let line = res?;
            match LINKER_SYM_RE.captures(&line) {
                None => break,
                Some(caps) => {
                    let depth = caps
                        .name("depth")
                        .context("Failed to parse the symbol depth.")?
                        .as_str()
                        .parse::<usize>()?;

                    let name = Intern::new({
                        match (caps.name("name"), caps.name("label")) {
                            (Some(name), None) => Named {
                                name: Intern::new(name.as_str().to_owned()),
                            },
                            (None, Some(label)) => Relative {
                                label: label.as_str().parse::<usize>()?,
                            },
                            _ => unreachable!("Unexpected name group value."),
                        }
                    });

                    let instance = caps
                        .name("instance")
                        .map(|s| s.as_str().parse::<usize>())
                        .transpose()?;

                    let src: MetrowerksSymbolSource = {
                        match caps.name("linker").map(|m| m.as_str()) {
                            Some("linker") => {
                                debug_assert_eq!(caps.name("file"), None);
                                debug_assert_eq!(caps.name("ext"), None);

                                MetrowerksSymbolSource::Linker
                            }
                            Some(_) => unreachable!(
                                "Unexpected value of \"linker\" group."
                            ),
                            None => {
                                let get_group = |field: &str| -> Result<&str> {
                                    caps.name(field)
                                        .map(|r#match| r#match.as_str())
                                        .with_context(|| {
                                            format!(
                                                "Failed to get the {field} \
                                                of a symbol."
                                            )
                                        })
                                };

                                MetrowerksSymbolSource::Object {
                                    file: Intern::from_ref(get_group("file")?),
                                    ext: Intern::from_ref(get_group("ext")?),
                                }
                            }
                        }
                    };
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
}

#[cfg(test)]
mod tests {
    use crate::ROOT;

    use super::MetrowerksMap;

    fn init_logger() {
        let _ = env_logger::builder()
            .is_test(true)
            .filter_level(log::LevelFilter::Trace)
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
