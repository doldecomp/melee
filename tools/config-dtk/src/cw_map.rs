use std::{
    hash::{BuildHasher, Hash, Hasher},
    num::{NonZeroU32, NonZeroU8},
    path::{Path, PathBuf},
    str,
};

use ahash::{AHashMap, RandomState};
use anyhow::{anyhow, bail, Context as AnyhowContext, Result};
use cwparse::{
    map::{self},
    memory_table, section_table, tree,
};
use log::{debug, error, warn};
use pathdiff::diff_paths;
use rayon::{prelude::ParallelIterator, str::ParallelString};

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

pub(crate) struct TreeSymbol<'a> {
    pub(crate) name: String,
    pub(crate) tu: &'a str,
    pub(crate) r#type: &'a str,
    pub(crate) scope: &'a str,
}

pub(crate) struct TableSymbol<'a> {
    pub(crate) section: &'a str,
    pub(crate) addr: NonZeroU32,
    pub(crate) size: u32,
    pub(crate) align: Option<NonZeroU8>,
}

struct Split<'a> {
    section: &'a str,
    tu: &'a str,
    start: NonZeroU32,
    end: Option<NonZeroU32>,
}

struct Section<'a> {
    name: &'a str,
    r#type: &'a str,
    addr: NonZeroU32,
}

pub(crate) struct Context<'a> {
    pub(crate) tree_symbols: AHashMap<u64, TreeSymbol<'a>>,
    pub(crate) table_symbols: AHashMap<u64, TableSymbol<'a>>,
    splits: Vec<Split<'a>>,
    sections: Vec<Section<'a>>,
    src_paths: AHashMap<u64, PathBuf>,
    raw: &'a str,
    line: usize,
}

impl<'a> Context<'a> {
    pub(crate) fn parse(
        input: &'a str,
        root: &Path,
        paths: Vec<PathBuf>,
    ) -> Result<Self> {
        let mut ctx = Context::new()?;

        let lines = input
            .par_lines()
            .map(|line| {
                map::line::<()>(line).map(|parsed| (line.trim(), parsed.1))
            })
            .collect::<Result<Vec<_>, _>>()
            .context("Failed to parse lines.")?;

        ctx.push_src_paths(root, paths)?;

        for (raw, parsed) in lines {
            ctx.push_line(&parsed, raw)?;
        }

        Ok(ctx)
    }

    fn new() -> Result<Context<'a>> {
        let hasher = RandomState::new();
        Ok(Self {
            // TODO: parse_lines as separate step
            tree_symbols: AHashMap::with_hasher(hasher.clone()),
            table_symbols: AHashMap::with_hasher(hasher.clone()),
            splits: Vec::default(),
            sections: Vec::default(),
            src_paths: AHashMap::with_hasher(hasher.clone()),
            raw: &"",
            line: 0,
        })
    }

    fn format_error_raw(line: usize, raw: &str, msg: &str) -> String {
        format!("{}\n{}: {}", msg, line, raw.trim())
    }

    fn format_error(&self, msg: &str) -> String {
        Self::format_error_raw(self.line, &self.raw, msg)
    }

    fn strip_tu(tu: &str) -> &str {
        tu.strip_suffix(".o").unwrap_or(tu)
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
            warn!(
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
            tu: Self::strip_tu(tu),
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
            addr: NonZeroU32::new(addr)
                .with_context(|| self.format_error("address is zero: {}"))?,
            size: {
                if size == 0 {
                    warn!("{}", self.format_error("size is zero"));
                }
                size
            },
            align: align
                .map(|n| {
                    NonZeroU8::new(n)
                        .with_context(|| self.format_error("align is zero"))
                })
                .transpose()?,
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
        section: &map::SectionName<&str>,
        tu: &'a str,
        start: u32,
    ) -> Result<()> {
        if let Some(Split { end: None, .. }) = self.splits.last() {
            bail!(self.format_error("cannot push a new split when the current split isn't completed"))
        }
        let split = Split {
            section: section_to_string(section)?,
            tu: Self::strip_tu(tu),
            start: NonZeroU32::new(start)
                .with_context(|| self.format_error("section start is zero"))?,
            end: None,
        };
        Ok(self.splits.push(split))
    }

    fn push_split_end(&mut self, end: u32) -> Result<()> {
        let end = NonZeroU32::new(end)
            .with_context(|| self.format_error("section end is zero"))
            .map(Some)?;
        if let Some(split @ Split { end: None, .. }) = self.splits.last_mut() {
            Ok(split.end = end)
        } else {
            Err(anyhow!(self.format_error(
                "cannot push a new split when one has not been started"
            )))
        }
    }

    fn push_section(
        &mut self,
        section: &map::SectionName<&str>,
        addr: u32,
    ) -> Result<()> {
        Ok(self.sections.push(Section {
            name: section_to_string(section)?,
            r#type: match section {
                map::SectionName::Bss => "bss",
                map::SectionName::Ctors => "rodata",
                map::SectionName::Data => "data",
                map::SectionName::Dtors => "rodata",
                map::SectionName::ExTab => "rodata",
                map::SectionName::ExTabIndex => "rodata",
                map::SectionName::Init => "code",
                map::SectionName::RoData => "rodata",
                map::SectionName::SBss => "bss",
                map::SectionName::SBss2 => "bss",
                map::SectionName::SData => "data",
                map::SectionName::SData2 => "rodata",
                map::SectionName::Text => "code",
                map::SectionName::Unknown(_) => {
                    bail!(self.format_error("unknown section name."))
                }
            },
            addr: NonZeroU32::new(addr)
                .with_context(|| self.format_error("address is zero"))?,
        }))
    }

    fn push_line(
        &mut self,
        parsed: &map::Line<&'a str>,
        raw: &'a str,
    ) -> Result<()> {
        self.raw = raw;
        self.line += 1;
        self.match_line(parsed)
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
            | map::Line::SectionTitle(_)
            | map::Line::TreeNode(tree::Node {
                data:
                    tree::Data::Linker(_)
                    | tree::Data::Object(
                        map::Identifier::Section { name: _, idx: _ },
                        _,
                    ),
                depth: _,
            }) => (),
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
            | map::Line::SectionSymbol(section_table::Symbol {
                addr: _,
                virt_addr: _,
                data: section_table::Data::Child { .. },
                id: map::Identifier::Section { .. },
                origin:
                    map::Origin {
                        obj: _,
                        src: None,
                        asm: false,
                    },
            })
            | map::Line::MemoryEntry(memory_table::Entry {
                data: memory_table::Data::Debug { .. },
                size: _,
                file_addr: _,
            }) => debug!("{}", self.format_error("ignoring")),
            map::Line::SectionSymbol(section_table::Symbol {
                addr: _,
                virt_addr: addr,
                data: _,
                id: map::Identifier::Section { name, idx: None },
                origin:
                    map::Origin {
                        obj: tu,
                        src: None,
                        asm: false,
                    },
            }) if tu.ends_with(".c.o") => {
                // debug!("{}", self.format_error("ignoring"))
                if self.splits.len() > 0 {
                    self.push_split_end(*addr)?;
                }
                self.push_split_start(name, tu, *addr)?;
                // error!("{}", self.format_error("not handled"));
                // TODO: Doesn't cover the end of the symbol map
            }
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
                        warn!("{}", self.format_error("child symbol"));
                        (0, None)
                    }
                };
                self.push_table_symbol(&id, tu, *addr, size, &align.copied())?;
            }
            map::Line::MemoryEntry(memory_table::Entry {
                data:
                    memory_table::Data::Main {
                        name,
                        virt_addr: addr,
                    },
                size,
                file_addr: _,
            }) => {
                if *size == 0 {
                    debug!(
                        "{}",
                        self.format_error("ignoring zero-length section")
                    );
                }
                self.push_section(name, *addr)?;
            }
            other => error!("Unexpected match: {:?}", other),
        })
    }

    fn push_src_paths(
        &mut self,
        root: &Path,
        paths: Vec<PathBuf>,
    ) -> Result<()> {
        for path in paths {
            if path.extension().and_then(|s| s.to_str()) != Some("c") {
                continue;
            }
            let key = {
                let file_name = path.file_name().with_context(|| {
                    format!("failed to get the filename for {:?}", path)
                })?;
                let file_str = path
                    .file_name()
                    .with_context(|| {
                        format!("failed to get the filename for {:?}", path)
                    })?
                    .to_str()
                    .with_context(|| {
                        format!(
                            "failed to convert the filename for {:?}",
                            file_name
                        )
                    })?;
                self.src_paths.hasher().hash_one(file_str)
            };
            let value = {
                diff_paths(&path, &root).with_context(|| {
                    format!("failed to diff {:?} with {:?}", path, root)
                })?
            };
            if let Some(existing) = self.src_paths.insert(key, value) {
                bail!("duplicate src path: {:?}", existing);
            }
        }
        Ok(())
    }
}
