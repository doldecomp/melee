use std::hash::{BuildHasher, Hash, Hasher};

use ahash::{AHashMap, RandomState};
use anyhow::{anyhow, bail, Context, Result};
use cwparse::{map, memory_table, section_table, tree};
use itertools::Itertools;
use log::{debug, error, trace};
use rayon::{prelude::ParallelIterator, str::ParallelString};

use crate::types::{Split, TableSymbol, TreeSymbol};

fn section_to_string(name: &map::SectionName<&str>) -> Result<&'static str> {
    match name {
        map::SectionName::Bss => Ok(".bss"),
        map::SectionName::Ctors => Ok(".ctors"),
        map::SectionName::Data => Ok(".data"),
        map::SectionName::ExTab => Ok("extab"),
        map::SectionName::ExTabIndex => Ok("extabindex"),
        map::SectionName::Init => Ok(".init"),
        map::SectionName::RoData => Ok(".rodata"),
        map::SectionName::SBss => Ok(".sbss"),
        map::SectionName::SBss2 => Ok(".sbss2"),
        map::SectionName::SData => Ok(".sdata"),
        map::SectionName::SData2 => Ok(".sdata2"),
        map::SectionName::Text => Ok(".text"),
        map::SectionName::Dtors => Ok(".dtors"),
        map::SectionName::Unknown(_) => {
            Err(anyhow!("Can't return an unknown section name."))
        }
    }
}

fn id_to_string(id: &map::Identifier<&str>) -> String {
    match id {
        map::Identifier::Relative { idx } => format!("@{idx}"),
        map::Identifier::StringBase { idx } => format!("@stringBase{idx}"),
        map::Identifier::Named {
            name,
            instance: None,
        }
        | map::Identifier::Mangled { name } => String::from(*name),
        map::Identifier::Named {
            name,
            instance: Some(instance),
        } => format!("{}${}", name, instance),
        map::Identifier::Section { name, idx: None } => {
            String::from(section_to_string(&name).unwrap())
        }
        map::Identifier::Section {
            name,
            idx: Some(idx),
        } => format!("..{}.{}", section_to_string(&name).unwrap(), idx),
        map::Identifier::DotL { name } => format!("lbl{name}"),
    }
}

pub(crate) struct Parser<'a> {
    pub(crate) tree_symbols: AHashMap<u64, TreeSymbol<'a>>,
    pub(crate) table_symbols: AHashMap<u64, TableSymbol<'a>>,
    pub(crate) splits: Vec<Split<'a>>,
    raw: &'a str,
    line: usize,
    tu_paths: &'a AHashMap<String, String>,
    cur_tu: &'a str,
    cur_section: &'a str,
}

impl<'a> Parser<'a> {
    pub(crate) fn parse(
        input: &'a str,
        tu_paths: &'a AHashMap<String, String>,
    ) -> Result<Self> {
        let hasher = RandomState::new();
        let mut parser = Parser {
            tree_symbols: AHashMap::with_hasher(hasher.clone()),
            table_symbols: AHashMap::with_hasher(hasher.clone()),
            splits: Default::default(),
            raw: Default::default(),
            line: Default::default(),
            tu_paths,
            cur_tu: Default::default(),
            cur_section: Default::default(),
        };

        let lines = input
            .par_lines()
            .map(|line| {
                map::line::<()>(line).map(|parsed| (line.trim(), parsed.1))
            })
            .collect::<Result<Vec<_>, _>>()
            .context("Failed to parse lines.")?;

        for (raw, parsed) in lines {
            parser.push_line(&parsed, raw)?;
        }

        Ok(parser)
    }

    fn format_error_raw(line: usize, raw: &str, msg: &str) -> String {
        format!("{}\n{}: {}", msg, line, raw.trim())
    }

    fn format_error(&self, msg: &str) -> String {
        Self::format_error_raw(self.line, &self.raw, msg)
    }

    fn resolve_tu(&self, tu: &'a str) -> Result<&'a str> {
        let key = tu.split_once('.').unwrap().0;
        self.tu_paths
            .get(key)
            .ok_or_else(|| {
                anyhow!(
                    "{}",
                    self.format_error(&format!(
                        "could not resolve translation unit \"{}\"",
                        &key
                    ))
                )
            })
            .map(String::as_str)
    }

    fn push_symbol<V>(
        map: &mut AHashMap<u64, V>,
        tu: &str,
        id: &map::Identifier<&str>,
        value: V,
        line: usize,
        raw: &str,
    ) -> Result<()> {
        let key = {
            let mut hasher = map.hasher().build_hasher();
            tu.hash(&mut hasher);
            id.hash(&mut hasher);
            hasher.finish()
        };
        if map.get(&key).is_some() {
            trace!(
                "{}",
                Self::format_error_raw(
                    line,
                    raw,
                    "tried to insert existing symbol into the map"
                )
            );
        }
        map.insert(key, value);
        Ok(())
    }

    fn push_tree_symbol(
        &mut self,
        id: &map::Identifier<&str>,
        tu: &'a str,
        scope: &tree::Scope,
        r#type: &tree::Type,
    ) -> Result<()> {
        let sym = TreeSymbol {
            name: id_to_string(id),
            r#type: match r#type {
                tree::Type::None => "label",
                tree::Type::Object => "object",
                tree::Type::Function => "function",
                tree::Type::Section => bail!("Type shouldn't be \"section\"."),
            },
            scope: match scope {
                tree::Scope::Global => "global",
                tree::Scope::Local => "local",
                tree::Scope::Weak => "weak",
            },
        };
        Self::push_symbol(
            &mut self.tree_symbols,
            tu,
            id,
            sym,
            self.line,
            self.raw,
        )
    }

    fn push_table_symbol(
        &mut self,
        id: &map::Identifier<&str>,
        tu: &str,
        addr: u32,
        size: u32,
        align: &Option<u8>,
    ) -> Result<()> {
        let sym = TableSymbol {
            section: {
                if let Some(Split { section, .. }) = self.splits.last() {
                    *section
                } else {
                    bail!(self.format_error(
                        "cannot push a table symbol without a section set"
                    ))
                }
            },
            addr,
            size: {
                if size == 0 {
                    trace!("{}", self.format_error("size is zero"));
                }
                size
            },
            align: *align,
        };
        Self::push_symbol(
            &mut self.table_symbols,
            tu,
            id,
            sym,
            self.line,
            self.raw,
        )
    }

    fn push_split_start(
        &mut self,
        section: &'a str,
        tu: &'a str,
        start: u32,
    ) -> Result<()> {
        if let Some(Split { end: None, .. }) = self.splits.last() {
            bail!(self.format_error("cannot push a new split when the current split isn't completed"))
        }
        let split = Split {
            section,
            tu,
            start,
            end: None,
        };
        self.splits.push(split);
        Ok(())
    }

    fn push_split_end(&mut self, end: u32) -> Result<()> {
        if let Some(split @ Split { end: None, .. }) = self.splits.last_mut() {
            Ok(split.end = Some(end))
        } else {
            Err(anyhow!(self.format_error(
                "cannot push a new split when one has not been started"
            )))
        }
    }

    fn push_line(
        &mut self,
        parsed: &map::Line<&'a str>,
        raw: &'a str,
    ) -> Result<()> {
        self.raw = raw;
        self.line += 1;
        self.match_line(parsed)?;

        // match parsed {
        //     map::Line::SectionSymbol(sym) {

        // }
        // }
        // if self.cur_tu == *tu {
        //     ()
        // }
        // // if self.line
        // if self.splits.len() > 0 {
        //     if let Err(err) = self.push_split_end(*addr) {
        //         debug!("{}", err);
        //     }
        // }
        // if let Err(err) =
        //     self.push_split_start(self.cur_section, tu, *addr)
        // {
        //     error!("{}", err);
        // }
        // // TODO: Doesn't cover the end of the symbol map
        Ok(())
    }

    fn match_line(&mut self, parsed: &map::Line<&'a str>) -> Result<()> {
        Ok(match parsed {
            map::Line::Empty
            | map::Line::TreeTitle(_)
            | map::Line::SectionColumns0
            | map::Line::SectionColumns1
            | map::Line::SectionSeparator
            | map::Line::MemoryTitle
            | map::Line::MemoryColumns0
            | map::Line::MemoryColumns1
            | map::Line::LinkerTitle
            | map::Line::LinkerEntry(_)
            | map::Line::TreeNode(tree::Node {
                data:
                    tree::Data::Linker(_)
                    | tree::Data::Object(
                        map::Identifier::Section { name: _, idx: _ },
                        _,
                    ),
                depth: _,
            }) => (),
            map::Line::SectionTitle(name) => {
                self.cur_section = section_to_string(name)?
            }
            map::Line::TreeNode(tree::Node {
                data:
                    tree::Data::Object(
                        _,
                        tree::Specifier {
                            origin:
                                map::Origin {
                                    obj: _,
                                    src: None,
                                    asm: false,
                                },
                            r#type: tree::Type::Section,
                            scope: _,
                        },
                    ),
                depth: _,
            })
            | map::Line::MemoryEntry(memory_table::Entry {
                data: memory_table::Data::Debug { .. },
                size: _,
                file_addr: _,
            }) => trace!("{}", self.format_error("ignoring")),

            map::Line::TreeNode(tree::Node {
                data:
                    tree::Data::Object(
                        id,
                        tree::Specifier {
                            origin:
                                map::Origin {
                                    obj: tu,
                                    src: None,
                                    asm: false,
                                },
                            r#type,
                            scope,
                        },
                    ),
                depth: _,
            }) => self.push_tree_symbol(&id, tu, &scope, &r#type)?,
            map::Line::SectionSymbol(section_table::Symbol {
                addr: _,
                virt_addr: addr,
                data,
                id,
                origin:
                    map::Origin {
                        obj: tu,
                        src: None,
                        asm: false,
                    },
            }) => {
                let (size, align) = match data {
                    section_table::Data::Parent { size, align } => {
                        (*size, Some(align))
                    }
                    _ => {
                        trace!("{}", self.format_error("child symbol"));
                        (0, None)
                    }
                };

                if let Ok(tu) = self.resolve_tu(tu) {
                    if self.cur_tu != tu {
                        if self.splits.len() > 0 {
                            if let Err(err) = self.push_split_end(*addr) {
                                debug!("{}", err);
                            }
                        }
                        if let Err(err) =
                            self.push_split_start(self.cur_section, tu, *addr)
                        {
                            debug!("{}", err);
                        }
                        // TODO: Doesn't cover the end of the symbol map
                        self.cur_tu = tu;
                    }
                }

                self.push_table_symbol(&id, tu, *addr, size, &align.copied())?;
            }
            map::Line::MemoryEntry(memory_table::Entry {
                data:
                    memory_table::Data::Main {
                        name: _,
                        virt_addr: _,
                    },
                size,
                file_addr: _,
            }) => {
                if *size == 0 {
                    trace!(
                        "{}",
                        self.format_error("ignoring zero-length section")
                    );
                }
            }
            other => error!("Unexpected match: {:?}", other),
        })
    }
}
