use std::{
    collections::BTreeMap,
    fs::File,
    hash::{BuildHasher, Hash, Hasher},
    io::{BufWriter, Write},
    marker::PhantomData,
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
use log::{debug, error, info, warn};
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

struct TreeSymbol<'a> {
    name: String,
    tu: &'a str,
    r#type: &'a str,
    scope: &'a str,
}

struct TableSymbol<'a> {
    section: &'a str,
    addr: NonZeroU32,
    size: u32,
    align: Option<NonZeroU8>,
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

struct Context<'a> {
    tree_symbols: AHashMap<u64, TreeSymbol<'a>>,
    table_symbols: AHashMap<u64, TableSymbol<'a>>,
    splits: Vec<Split<'a>>,
    sections: Vec<Section<'a>>,
    src_paths: AHashMap<u64, PathBuf>,
    raw: &'a str,
    line: usize,
}

impl<'a> Context<'a> {
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
        if let Some(_) = map.insert(key, value) {
            bail!(Self::format_error_raw(
                line,
                raw,
                "tried to insert existing symbol into the map"
            ));
        }
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
            }) if tu.ends_with(".c.o") => {
                self.push_tree_symbol(&id, tu, &scope, &r#type)?
            }
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
            }) if tu.ends_with(".c.o") => {
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
            map::Line::TreeNode(tree::Node {
                depth: _,
                data:
                    tree::Data::Object(
                        _,
                        tree::Specifier {
                            r#type: _,
                            scope: _,
                            origin:
                                map::Origin {
                                    obj: tu,
                                    src: None,
                                    asm: false,
                                },
                        },
                    ),
            })
            | map::Line::SectionSymbol(section_table::Symbol {
                addr: _,
                virt_addr: _,
                data: _,
                id: _,
                origin:
                    map::Origin {
                        obj: tu,
                        src: None,
                        asm: false,
                    },
            }) if tu.ends_with(".s.o") => (),
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

    fn write_splits<W>(writer: &mut W)
    where
        W: Write,
    {
    }
}

#[derive(Default)]
struct ConfigWriter<'a> {
    src_paths: AHashMap<String, PathBuf>,
    _todo: PhantomData<&'a str>,
}

fn main() -> Result<()> {
    env_logger::init();

    let map_path = melee_utils::ROOT
        .join("build/ssbm.us.1.2/GALE01.map")
        .canonicalize()?;
    let map_file =
        File::open(&map_path).context("Failed to open the map file.")?;
    let mmap = unsafe { memmap2::Mmap::map(&map_file) }
        .context("Failed to create the memory map.")?;
    let input = str::from_utf8(mmap.as_ref())
        .context("Failed to convert to UTF-8.")?;
    let mut ctx = Context::new()?;

    let txt_path = melee_utils::ROOT.join("config/GALE01").canonicalize()?;
    let splits_path = txt_path.join("splits.txt");
    let symbols_path = txt_path.join("symbols.txt");

    {
        let root = &melee_utils::ROOT.join("src");
        let paths = melee_utils::walk_src()?;
        ctx.push_src_paths(root, paths)?;
    }

    let lines = input
        .par_lines()
        .map(|line| {
            map::line::<()>(line).map(|parsed| (line.trim(), parsed.1))
        })
        .collect::<Result<Vec<_>, _>>()
        .context("Failed to parse lines.")?;

    for (raw, parsed) in lines {
        ctx.push_line(&parsed, raw)?;
    }

    let mut sorted_syms = BTreeMap::new();
    for key in ctx.tree_symbols.keys() {
        let tree_sym = ctx.tree_symbols.get(key).unwrap();
        let table_sym = ctx.table_symbols.get(key).unwrap();
        let sym_str = format!(
            "{} = {}:0x{:08X}; // type:{} size:0x{:X} scope:{}",
            tree_sym.name,
            table_sym.section,
            table_sym.addr,
            tree_sym.r#type,
            table_sym.size,
            tree_sym.scope
        );
        sorted_syms.insert(table_sym.addr, sym_str);
    }

    let file = File::create(&symbols_path)?;
    info!(
        "Writing symbols to {}",
        symbols_path
            .to_str()
            .context("Failed to convert the path to a string")?
    );
    let mut writer = BufWriter::new(file);
    for (_, s) in &sorted_syms {
        writeln!(writer, "{}", s)?;
    }

    // for (raw, parsed) in lines {
    //     tracker.push_line(&parsed, raw);
    // }

    // HACK: Throw in the ctors and dtors
    // {
    //     let tu = "__init_cpp_exceptions.c";
    //     {
    //         let section = ".ctors";
    //         let addr = NonZeroU32::new(0x803B7240).unwrap();
    //         // TODO
    //         // splits_map.insert(
    //         //     (tu, section),
    //         //     SplitSection {
    //         //         name: section,
    //         //         start: addr,
    //         //         size: Some(4),
    //         //     },
    //         // );

    //         // TODO
    //         // let id = map::Identifier::Named {
    //         //     name: "_ctors",
    //         //     instance: None,
    //         // };
    //         // symbols_map.insert(
    //         //     hash_builder.hash_one((tu, &id)),
    //         s//     Symbol {
    //         //         id: Some(id_to_string(&id)),
    //         //         section: Some(section),
    //         //         addr: Some(addr),
    //         //         r#type: Some("label"),
    //         //         size: Some(0),
    //         //         scope: Some("global"),
    //         //         align: None,
    //         //     },
    //         // );

    //         // let id = map::Identifier::Named {
    //         //     name: "__init_cpp_exceptions_reference",
    //         //     instance: None,
    //         // };
    //         // symbols_map.insert(
    //         //     hash_builder.hash_one((tu, &id)),
    //         //     Symbol {
    //         //         id: Some(id_to_string(&id)),
    //         //         section: Some(section),
    //         //         addr: Some(addr),
    //         //         r#type: Some("object"),
    //         //         size: Some(4),
    //         //         scope: Some("global"),
    //         //         align: None,
    //         //     },
    //         // );
    //     }
    //     {
    //         let section = ".dtors";
    //         let addr = NonZeroU32::new(0x803B7260).unwrap();
    //         // TODO
    //         // splits_map.insert(
    //         //     (tu, section),
    //         //     SplitSection {
    //         //         name: section,
    //         //         start: addr,
    //         //         size: Some(8),
    //         //     },
    //         // );

    //         // TODO
    //         //     let id = map::Identifier::Named {
    //         //         name: "_dtors",
    //         //         instance: None,
    //         //     };
    //         //     symbols_map.insert(
    //         //         hash_builder.hash_one((tu, &id)),
    //         //         Symbol {
    //         //             id: Some(id_to_string(&id)),
    //         //             section: Some(section),
    //         //             addr: Some(addr),
    //         //             r#type: Some("label"),
    //         //             size: Some(0),
    //         //             scope: Some("global"),
    //         //             align: None,
    //         //         },
    //         //     );

    //         //     let id = map::Identifier::Named {
    //         //         name: "__destroy_global_chain_reference",
    //         //         instance: None,
    //         //     };
    //         //     symbols_map.insert(
    //         //         hash_builder.hash_one((tu, &id)),
    //         //         Symbol {
    //         //             id: Some(id_to_string(&id)),
    //         //             section: Some(section),
    //         //             addr: Some(addr),
    //         //             r#type: Some("object"),
    //         //             size: Some(4),
    //         //             scope: Some("global"),
    //         //             align: None,
    //         //         },
    //         //     );

    //         //     let id = map::Identifier::Named {
    //         //         name: "__fini_cpp_exceptions_reference",
    //         //         instance: None,
    //         //     };
    //         //     symbols_map.insert(
    //         //         hash_builder.hash_one((tu, &id)),
    //         //         Symbol {
    //         //             id: Some(id_to_string(&id)),
    //         //             section: Some(section),
    //         //             addr: Some(NonZeroU32::new(addr.get() + 4).unwrap()),
    //         //             r#type: Some("object"),
    //         //             size: Some(4),
    //         //             scope: Some("global"),
    //         //             align: None,
    //         //         },
    //         //     );
    //     }
    // }

    {
        // let file = File::create(&splits_path)?;
        // info!(
        //     "Writing splits to {}",
        //     splits_path
        //         .to_str()
        //         .context("Failed to convert the path to a string")?
        // );
        // let mut writer = BufWriter::new(file);

        // writeln!(writer, "Sections:")?;

        // let mut elf_sections = elf_sections.into_iter().collect::<Vec<_>>();
        // elf_sections.sort_by_key(|s| s.addr);

        // for section in elf_sections {
        //     const SECTION_ALIGN: u8 = 8;
        //     writeln!(
        //         writer,
        //         "\t{:12}type:{} align:{}",
        //         section.name, section.r#type, SECTION_ALIGN
        //     )?;
        // }
        // writeln!(writer)?;

        // // TODO
        // // debug!("Splits are:\n{:#x?}", &splits_map);

        // // for (tu, path) in src_paths.into_iter() {
        // //     splits.clear();
        // //     for (_, split) in splits_map.iter().filter(|((k, _), _)| *k == &tu) {
        // //         splits.push(split);
        // //     }
        // //     splits.sort_by_key(|s| s.start);

        // //     writeln!(
        // //         writer,
        // //         "{}:",
        // //         path.to_str().context("Failed to write the path.")?
        // //     )?;
        // //     for split in splits.iter() {
        // //         writeln!(
        // //             writer,
        // //             "\t{:12}start:0x{:08X} end:0x{:08X}",
        // //             split.name,
        // //             split.start.get(),
        // //             split.start.get() + split.size.context("Section size is unset.")?
        // //         )?;
        // //     }
        // //     writeln!(writer)?;
        // // }
    }
    {
        // let mut symbols = symbols_map.into_values().collect::<Vec<_>>();
        // symbols.par_sort_by(|a, b| a.addr.cmp(&b.addr));
        // let file = File::create(&symbols_path)?;

        // info!(
        //     "Writing symbols to {}",
        //     symbols_path
        //         .to_str()
        //         .context("Failed to convert the path to a string")?
        // );

        // let mut writer = BufWriter::new(file);

        // for symbol in symbols {
        //     let (id, addr, section) =
        //         match (symbol.id, symbol.addr, symbol.section) {
        //             (Some(id), Some(addr), Some(section)) => {
        //                 (id, addr, section)
        //             }
        //             (None, Some(addr), _) => {
        //                 error!("Failed to get the symbol id at {}", addr);
        //                 continue;
        //             }
        //             (Some(id), None, _) => {
        //                 error!("Failed to get the symbol address for {}.", id);
        //                 continue;
        //             }
        //             (Some(id), Some(addr), None) => {
        //                 error!(
        //                 "Failed to get the symbol section for {} at {:08X}",
        //                 id, addr
        //             );
        //                 continue;
        //             }
        //             (None, None, None) => {
        //                 error!("Failed to get unknown symbol info.");
        //                 continue;
        //             }
        //             (None, None, Some(_)) => todo!(),
        //         };

        //     write!(writer, "{id} = {section}:0x{addr:08X};")?;

        //     let mut tags = Vec::<String>::new();

        //     if let Some(r#type) = symbol.r#type {
        //         tags.push(format!("type:{type}"));
        //     }

        //     if let Some(size) = symbol.size {
        //         tags.push(format!("size:0x{size:X}"));
        //     }

        //     if let Some(scope) = symbol.scope {
        //         tags.push(format!("scope:{scope}"));
        //     }

        //     if let Some(align) = symbol.align {
        //         tags.push(format!("align:{align}"));
        //     }

        //     if tags.len() > 0 {
        //         write!(writer, " // {}", &tags.join(" "))?;
        //     }

        //     writeln!(writer)?;
        // }
    }
    Ok(())
}
