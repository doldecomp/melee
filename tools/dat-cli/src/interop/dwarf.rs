//! A faithful index of the type information in a DWARF file.
//!
//! Every node is identified by the offset of its DIE in `.debug_info`, and
//! every kind mirrors a DWARF tag. Nothing here is inferred: views such as
//! canonical names, `dat:` annotation semantics or text dumps are built on
//! top of this and must not add facts of their own.

pub mod annotation;
pub mod cache;
pub mod canonical;
pub mod expr;
pub mod render;
pub mod roots;

use anyhow::{Context, Result, bail};
use gimli::{
    AttributeValue, DebugInfoOffset, DwAt, DwTag, EndianSlice,
    EntriesTreeNode, MacroEntry, MacroString, Reader, ReaderOffset,
    RelocateReader, RunTimeEndian, UnitRef,
};
use object::{Object, ObjectSection};
use rayon::prelude::*;
use std::{
    borrow::Cow,
    collections::{BTreeMap, HashMap},
    path::Path,
    sync::Mutex,
};
use winnow::{
    ModalResult, Parser,
    ascii::multispace0,
    combinator::{opt, preceded},
    token::{rest, take_till, take_while},
};

/// Emitted by clang for `btf_decl_tag` and `btf_type_tag`; not in gimli.
pub const DW_TAG_LLVM_ANNOTATION: DwTag = DwTag(0x6000);

/// The offset of a DIE in `.debug_info`, unique across the whole file.
pub type DieId = u64;

/// An interned string: equal strings have equal symbols.
pub type Str = string_interner::DefaultSymbol;
pub type Strings = string_interner::DefaultStringInterner;

#[derive(Debug, Default, serde::Serialize, serde::Deserialize)]
pub struct TypeGraph {
    pub strings: Strings,
    pub units: Vec<Unit>,
    pub types: BTreeMap<DieId, Type>,
    /// Variables carrying annotations, such as the root witnesses
    /// declared by `DAT_ROOTS`.
    pub variables: BTreeMap<DieId, Variable>,
    /// File-scope variables with a static address, by name; the first
    /// definition wins.
    pub globals: HashMap<Str, Global>,
    /// The contents of the file's allocated sections, by start address, so
    /// the initial values of globals can be read.
    pub sections: Vec<(u64, Vec<u8>)>,
}

/// A variable at a fixed address.
#[derive(
    Debug, Clone, Copy, PartialEq, Eq, serde::Serialize, serde::Deserialize,
)]
pub struct Global {
    pub ty: Option<DieId>,
    pub address: u64,
}

#[derive(Debug, serde::Serialize, serde::Deserialize)]
pub struct Unit {
    pub name: Option<Str>,
    /// The size of a pointer, which pointer types do not always state.
    pub address_size: u8,
    pub macros: Vec<Macro>,
}

/// A `DW_MACRO_define`, split into its name (with any parameter list) and
/// replacement text.
#[derive(
    Debug, Clone, Copy, PartialEq, Eq, serde::Serialize, serde::Deserialize,
)]
pub struct Macro {
    pub name: Str,
    pub value: Str,
}

#[derive(
    Debug, Clone, PartialEq, Eq, serde::Serialize, serde::Deserialize,
)]
pub struct Type {
    /// Index into [`TypeGraph::units`].
    pub unit: usize,
    pub name: Option<Str>,
    pub byte_size: Option<u64>,
    /// `DW_AT_decl_file`, as a path.
    pub decl_file: Option<Str>,
    /// The function the type is declared in, if not at file scope.
    pub scope: Option<Str>,
    pub annotations: Vec<Annotation>,
    pub kind: TypeKind,
}

#[derive(
    Debug, Clone, PartialEq, Eq, serde::Serialize, serde::Deserialize,
)]
pub enum TypeKind {
    /// `DW_TAG_base_type`, with its `DW_ATE_*` encoding.
    Base {
        encoding: u8,
    },
    /// `DW_TAG_unspecified_type`.
    Unspecified,
    /// `DW_TAG_pointer_type`; no target means `void*`.
    Pointer {
        target: Option<DieId>,
    },
    Typedef {
        target: Option<DieId>,
    },
    Const {
        target: Option<DieId>,
    },
    Volatile {
        target: Option<DieId>,
    },
    Restrict {
        target: Option<DieId>,
    },
    /// `DW_TAG_array_type`; a dimension is `None` when it has no bound.
    Array {
        element: Option<DieId>,
        dims: Vec<Option<u64>>,
    },
    /// `DW_TAG_structure_type` or `DW_TAG_union_type`.
    Record {
        union: bool,
        declaration: bool,
        members: Vec<Member>,
    },
    /// `DW_TAG_enumeration_type`.
    Enum {
        underlying: Option<DieId>,
        enumerators: Vec<Enumerator>,
    },
    /// `DW_TAG_subroutine_type`.
    Subroutine {
        ret: Option<DieId>,
        params: Vec<Option<DieId>>,
        variadic: bool,
    },
}

#[derive(
    Debug, Clone, PartialEq, Eq, serde::Serialize, serde::Deserialize,
)]
pub struct Member {
    pub name: Option<Str>,
    pub ty: Option<DieId>,
    /// `DW_AT_data_member_location`, in bytes.
    pub offset: Option<u64>,
    pub bit_size: Option<u64>,
    /// `DW_AT_data_bit_offset`, in bits from the start of the record.
    pub bit_offset: Option<u64>,
    pub annotations: Vec<Annotation>,
}

#[derive(
    Debug, Clone, PartialEq, Eq, serde::Serialize, serde::Deserialize,
)]
pub struct Enumerator {
    pub name: Option<Str>,
    pub value: i64,
}

/// A `DW_TAG_variable` with at least one annotation.
#[derive(
    Debug, Clone, PartialEq, Eq, serde::Serialize, serde::Deserialize,
)]
pub struct Variable {
    /// Index into [`TypeGraph::units`].
    pub unit: usize,
    pub name: Option<Str>,
    pub ty: Option<DieId>,
    pub decl_file: Option<Str>,
    pub decl_line: Option<u64>,
    /// The function the variable is declared in, if not at file scope.
    pub scope: Option<Str>,
    pub annotations: Vec<Annotation>,
}

/// A `DW_TAG_LLVM_annotation`: `name` is the attribute that produced it
/// (e.g. `btf_decl_tag`) and `value` its argument, both verbatim.
#[derive(
    Debug, Clone, PartialEq, Eq, serde::Serialize, serde::Deserialize,
)]
pub struct Annotation {
    pub name: Option<Str>,
    pub value: Option<Str>,
}

impl TypeGraph {
    pub fn load(path: impl AsRef<Path>) -> Result<Self> {
        let path = path.as_ref();
        let data = std::fs::read(path)
            .with_context(|| format!("failed to read {}", path.display()))?;
        Self::parse(&data)
            .with_context(|| format!("failed to parse {}", path.display()))
    }

    pub fn parse(data: &[u8]) -> Result<Self> {
        let file = object::File::parse(data)?;
        let endian = if file.is_little_endian() {
            RunTimeEndian::Little
        } else {
            RunTimeEndian::Big
        };

        let sections = gimli::DwarfSections::load(
            |id| -> Result<(Cow<'_, [u8]>, Relocations)> {
                Ok(match file.section_by_name(id.name()) {
                    Some(section) => (
                        section.uncompressed_data()?,
                        Relocations(section.relocation_map()?),
                    ),
                    None => (Cow::Borrowed(&[]), Relocations::default()),
                })
            },
        )?;
        let dwarf = sections.borrow(|(data, relocations)| {
            RelocateReader::new(EndianSlice::new(data, endian), relocations)
        });

        // String tables are never relocated, so they can be read directly
        let section = |name| -> Result<Cow<'_, [u8]>> {
            Ok(match file.section_by_name(name) {
                Some(section) => section.uncompressed_data()?,
                None => Cow::Borrowed(&[]),
            })
        };
        let mut strings = Strings::new();
        let interner = Interner {
            debug_str: intern_section(&mut strings, &section(".debug_str")?),
            debug_line_str: intern_section(
                &mut strings,
                &section(".debug_line_str")?,
            ),
            fallback: Mutex::new(strings),
        };

        let mut headers = Vec::new();
        let mut iter = dwarf.units();
        while let Some(header) = iter.next()? {
            headers.push(header);
        }

        // Units are independent, so read them in parallel. Strings resolve
        // through the tables interned above; macros are split afterwards.
        let parsed = headers
            .into_par_iter()
            .enumerate()
            .map(|(index, header)| {
                let unit = dwarf.unit(header)?;
                parse_unit(&interner, unit.unit_ref(&dwarf), index)
            })
            .collect::<Result<Vec<_>>>()?;

        let mut strings = interner.fallback.into_inner().unwrap();
        let mut split = HashMap::new();
        let mut units = Vec::with_capacity(parsed.len());
        let mut types = Vec::new();
        let mut variables = Vec::new();
        let mut globals = HashMap::new();
        for unit in parsed {
            let macros = unit
                .macros
                .iter()
                .map(|&text| {
                    *split
                        .entry(text)
                        .or_insert_with(|| split_define(&mut strings, text))
                })
                .collect();
            units.push(Unit {
                name: unit.name,
                address_size: unit.address_size,
                macros,
            });
            types.extend(unit.types);
            variables.extend(unit.variables);
            for (name, global) in unit.globals {
                globals.entry(name).or_insert(global);
            }
        }
        types.sort_unstable_by_key(|&(id, _)| id);

        Ok(TypeGraph {
            strings,
            units,
            types: types.into_iter().collect(),
            variables: variables.into_iter().collect(),
            globals,
            sections: file
                .sections()
                .filter(|s| s.address() != 0)
                .filter_map(|s| Some((s.address(), s.data().ok()?.to_vec())))
                .filter(|(_, data)| !data.is_empty())
                .collect(),
        })
    }

    /// `len` bytes at a static address, if the file has them.
    pub fn bytes(&self, address: u64, len: usize) -> Option<&[u8]> {
        let (start, data) = self.sections.iter().find(|(start, data)| {
            (*start..*start + data.len() as u64).contains(&address)
        })?;
        let at = (address - start) as usize;
        data.get(at..at + len)
    }

    pub fn str(&self, s: Str) -> &str {
        self.strings.resolve(s).unwrap_or_default()
    }

    /// Every type with this name, whether a typedef or a tag.
    pub fn named(&self, name: &str) -> impl Iterator<Item = (DieId, &Type)> {
        let name = self.strings.get(name);
        self.types
            .iter()
            .filter(move |(_, t)| name.is_some() && t.name == name)
            .map(|(&id, t)| (id, t))
    }
}

/// A unit read independently of the others.
struct ParsedUnit {
    name: Option<Str>,
    address_size: u8,
    /// The text of each `DW_MACRO_define`, not yet split.
    macros: Vec<Str>,
    types: Vec<(DieId, Type)>,
    variables: Vec<(DieId, Variable)>,
    globals: Vec<(Str, Global)>,
}

fn parse_unit<R: Reader>(
    interner: &Interner,
    unit: UnitRef<'_, R>,
    index: usize,
) -> Result<ParsedUnit> {
    let mut tree = unit.entries_tree(None)?;
    let root = tree.root()?;
    let entry = root.entry();

    let name = entry
        .attr_value(gimli::DW_AT_name)
        .map(|value| interner.attr(unit, value))
        .transpose()?;
    let macros = match entry.attr_value(gimli::DW_AT_macros) {
        Some(AttributeValue::DebugMacroRef(offset)) => {
            interner.macros(unit, offset)?
        }
        _ => Vec::new(),
    };

    let mut walker = Walker {
        unit,
        index,
        files: files(interner, unit)?,
        scope: None,
        types: Vec::new(),
        variables: Vec::new(),
        globals: Vec::new(),
        interner,
    };
    walker.children(root)?;
    Ok(ParsedUnit {
        name,
        address_size: unit.encoding().address_size,
        macros,
        types: walker.types,
        variables: walker.variables,
        globals: walker.globals,
    })
}

/// Interns every string of a string section up front, by offset.
fn intern_section(strings: &mut Strings, section: &[u8]) -> HashMap<u64, Str> {
    let mut offsets = HashMap::new();
    let mut offset = 0;
    for s in section.split(|&b| b == 0) {
        let symbol = strings.get_or_intern(String::from_utf8_lossy(s));
        offsets.insert(offset as u64, symbol);
        offset += s.len() + 1;
    }
    offsets
}

/// An object file's relocations for one DWARF section. A linked file has
/// none: its references are already resolved.
#[derive(Debug, Default)]
struct Relocations(object::read::RelocationMap);

impl gimli::Relocate for &Relocations {
    fn relocate_address(
        &self,
        offset: usize,
        value: u64,
    ) -> gimli::Result<u64> {
        Ok(self.0.relocate(offset as u64, value))
    }

    fn relocate_offset(
        &self,
        offset: usize,
        value: usize,
    ) -> gimli::Result<usize> {
        <usize as ReaderOffset>::from_u64(
            self.0.relocate(offset as u64, value as u64),
        )
    }
}

/// Maps DWARF's string references to our symbols.
struct Interner {
    debug_str: HashMap<u64, Str>,
    debug_line_str: HashMap<u64, Str>,
    /// For strings that are not at the start of a string table entry.
    fallback: Mutex<Strings>,
}

impl Interner {
    fn attr<R: Reader>(
        &self,
        unit: UnitRef<'_, R>,
        value: AttributeValue<R>,
    ) -> Result<Str> {
        let known = match value {
            AttributeValue::DebugStrRef(o) => {
                self.debug_str.get(&o.0.into_u64())
            }
            AttributeValue::DebugStrOffsetsIndex(i) => {
                self.debug_str.get(&unit.string_offset(i)?.0.into_u64())
            }
            AttributeValue::DebugLineStrRef(o) => {
                self.debug_line_str.get(&o.0.into_u64())
            }
            _ => None,
        };
        match known {
            Some(&symbol) => Ok(symbol),
            // Inline, or pointing into the middle of a string
            None => self.intern(unit.attr_string(value)?),
        }
    }

    fn intern<R: Reader>(&self, s: R) -> Result<Str> {
        let s = s.to_string_lossy()?;
        Ok(self.fallback.lock().unwrap().get_or_intern(s))
    }

    fn macros<R: Reader>(
        &self,
        unit: UnitRef<'_, R>,
        offset: gimli::DebugMacroOffset<R::Offset>,
    ) -> Result<Vec<Str>> {
        let mut macros = Vec::new();
        let mut pending = vec![offset];
        while let Some(offset) = pending.pop() {
            let mut entries = unit.macros(offset)?;
            while let Some(entry) = entries.next()? {
                match entry {
                    MacroEntry::Define { text, .. } => {
                        macros.push(self.macro_string(unit, text)?)
                    }
                    MacroEntry::Import { offset } => pending.push(offset),
                    _ => {}
                }
            }
        }
        Ok(macros)
    }

    fn macro_string<R: Reader>(
        &self,
        unit: UnitRef<'_, R>,
        text: MacroString<R>,
    ) -> Result<Str> {
        let offset = match text {
            MacroString::StringPointer(o) => Some(o.0.into_u64()),
            MacroString::IndirectStringPointer(i) => {
                Some(unit.string_offset(i)?.0.into_u64())
            }
            _ => None,
        };
        match offset.and_then(|o| self.debug_str.get(&o)) {
            Some(&symbol) => Ok(symbol),
            None => self.intern(text.string(unit)?),
        }
    }
}

/// Split `NAME value` or `NAME(args) value` into its name and value.
fn split_define(strings: &mut Strings, text: Str) -> Macro {
    let s = strings.resolve(text).unwrap_or_default().to_owned();
    let (name, value) = define.parse(&s).unwrap_or((&s, ""));
    Macro {
        name: strings.get_or_intern(name),
        value: strings.get_or_intern(value),
    }
}

/// A `DW_MACRO_define` string: the name, with any parameter list, and the
/// replacement text.
fn define<'i>(input: &mut &'i str) -> ModalResult<(&'i str, &'i str)> {
    let name = (
        take_while(1.., |c: char| c.is_ascii_alphanumeric() || c == '_'),
        opt(('(', take_till(0.., ')'), ')')),
    )
        .take()
        .parse_next(input)?;
    let value = preceded(multispace0, rest).parse_next(input)?;
    Ok((name, value))
}

/// The paths of a unit's line program files, by `DW_AT_decl_file` index.
fn files<R: Reader>(
    interner: &Interner,
    unit: UnitRef<'_, R>,
) -> Result<Vec<Str>> {
    let Some(program) = &unit.line_program else {
        return Ok(Vec::new());
    };
    let header = program.header();
    header
        .file_names()
        .iter()
        .map(|file| {
            let mut path = String::new();
            if let Some(dir) = file.directory(header) {
                path.push_str(&unit.attr_string(dir)?.to_string_lossy()?);
                path.push('/');
            }
            path.push_str(
                &unit.attr_string(file.path_name())?.to_string_lossy()?,
            );
            Ok(interner.fallback.lock().unwrap().get_or_intern(path))
        })
        .collect()
}

struct Walker<'i, 'u, R: Reader> {
    unit: UnitRef<'u, R>,
    index: usize,
    files: Vec<Str>,
    /// The enclosing function, while walking one.
    scope: Option<Str>,
    types: Vec<(DieId, Type)>,
    variables: Vec<(DieId, Variable)>,
    globals: Vec<(Str, Global)>,
    interner: &'i Interner,
}

impl<R: Reader> Walker<'_, '_, R> {
    /// Visit every child, recording any type DIEs found at any depth.
    fn children(&mut self, node: EntriesTreeNode<'_, '_, R>) -> Result<()> {
        let mut children = node.children();
        while let Some(child) = children.next()? {
            self.node(child)?;
        }
        Ok(())
    }

    fn node(&mut self, node: EntriesTreeNode<'_, '_, R>) -> Result<()> {
        let entry = node.entry();
        let tag = entry.tag();
        let id = self.id(entry.offset())?;
        let name = self.name(entry)?;
        let byte_size = entry
            .attr_value(gimli::DW_AT_byte_size)
            .and_then(|v| v.udata_value());
        let target = self.reference(entry, gimli::DW_AT_type)?;
        let decl_file = match entry.attr_value(gimli::DW_AT_decl_file) {
            Some(AttributeValue::FileIndex(i)) => self.files.get(i as usize),
            Some(value) => {
                value.udata_value().and_then(|i| self.files.get(i as usize))
            }
            None => None,
        }
        .copied();
        let mut annotations = Vec::new();

        let kind = match tag {
            gimli::DW_TAG_base_type => TypeKind::Base {
                encoding: match entry.attr_value(gimli::DW_AT_encoding) {
                    Some(AttributeValue::Encoding(e)) => e.0,
                    _ => 0,
                },
            },
            gimli::DW_TAG_unspecified_type => TypeKind::Unspecified,
            gimli::DW_TAG_pointer_type => TypeKind::Pointer { target },
            gimli::DW_TAG_typedef => TypeKind::Typedef { target },
            gimli::DW_TAG_const_type => TypeKind::Const { target },
            gimli::DW_TAG_volatile_type => TypeKind::Volatile { target },
            gimli::DW_TAG_restrict_type => TypeKind::Restrict { target },
            gimli::DW_TAG_array_type => {
                let mut dims = Vec::new();
                let mut children = node.children();
                while let Some(child) = children.next()? {
                    let child_entry = child.entry();
                    if child_entry.tag() == gimli::DW_TAG_subrange_type {
                        dims.push(subrange_count(child_entry));
                    } else {
                        self.node(child)?;
                    }
                }
                self.insert(
                    id,
                    name,
                    byte_size,
                    decl_file,
                    annotations,
                    TypeKind::Array {
                        element: target,
                        dims,
                    },
                );
                return Ok(());
            }
            gimli::DW_TAG_structure_type | gimli::DW_TAG_union_type => {
                let declaration = matches!(
                    entry.attr_value(gimli::DW_AT_declaration),
                    Some(AttributeValue::Flag(true))
                );
                let mut members = Vec::new();
                let mut children = node.children();
                while let Some(child) = children.next()? {
                    match child.entry().tag() {
                        gimli::DW_TAG_member => {
                            members.push(self.member(child)?)
                        }
                        DW_TAG_LLVM_ANNOTATION => {
                            annotations.push(self.annotation(child.entry())?)
                        }
                        _ => self.node(child)?,
                    }
                }
                self.insert(
                    id,
                    name,
                    byte_size,
                    decl_file,
                    annotations,
                    TypeKind::Record {
                        union: tag == gimli::DW_TAG_union_type,
                        declaration,
                        members,
                    },
                );
                return Ok(());
            }
            gimli::DW_TAG_enumeration_type => {
                let mut enumerators = Vec::new();
                let mut children = node.children();
                while let Some(child) = children.next()? {
                    let child_entry = child.entry();
                    if child_entry.tag() == gimli::DW_TAG_enumerator {
                        enumerators.push(Enumerator {
                            name: self.name(child_entry)?,
                            value: constant(child_entry).unwrap_or_default(),
                        });
                    } else {
                        self.node(child)?;
                    }
                }
                self.insert(
                    id,
                    name,
                    byte_size,
                    decl_file,
                    annotations,
                    TypeKind::Enum {
                        underlying: target,
                        enumerators,
                    },
                );
                return Ok(());
            }
            gimli::DW_TAG_subroutine_type => {
                let mut params = Vec::new();
                let mut variadic = false;
                let mut children = node.children();
                while let Some(child) = children.next()? {
                    let child_entry = child.entry();
                    match child_entry.tag() {
                        gimli::DW_TAG_formal_parameter => params.push(
                            self.reference(child_entry, gimli::DW_AT_type)?,
                        ),
                        gimli::DW_TAG_unspecified_parameters => {
                            variadic = true
                        }
                        _ => self.node(child)?,
                    }
                }
                self.insert(
                    id,
                    name,
                    byte_size,
                    decl_file,
                    annotations,
                    TypeKind::Subroutine {
                        ret: target,
                        params,
                        variadic,
                    },
                );
                return Ok(());
            }
            gimli::DW_TAG_subprogram => {
                let outer = std::mem::replace(&mut self.scope, name);
                self.children(node)?;
                self.scope = outer;
                return Ok(());
            }
            gimli::DW_TAG_variable => {
                let decl_line = entry
                    .attr_value(gimli::DW_AT_decl_line)
                    .and_then(|v| v.udata_value());
                let address = match self.scope {
                    None => self.address(entry)?,
                    Some(_) => None,
                };
                let mut children = node.children();
                while let Some(child) = children.next()? {
                    if child.entry().tag() == DW_TAG_LLVM_ANNOTATION {
                        annotations.push(self.annotation(child.entry())?);
                    } else {
                        self.node(child)?;
                    }
                }
                if let (Some(name), Some(address)) = (name, address) {
                    self.globals.push((
                        name,
                        Global {
                            ty: target,
                            address,
                        },
                    ));
                }
                if !annotations.is_empty() {
                    self.variables.push((
                        id,
                        Variable {
                            unit: self.index,
                            name,
                            ty: target,
                            decl_file,
                            decl_line,
                            scope: self.scope,
                            annotations,
                        },
                    ));
                }
                return Ok(());
            }
            // Not a type, but types can be declared inside it
            _ => return self.children(node),
        };

        // Leaf types may still carry annotations (e.g. on a typedef)
        let mut children = node.children();
        while let Some(child) = children.next()? {
            if child.entry().tag() == DW_TAG_LLVM_ANNOTATION {
                annotations.push(self.annotation(child.entry())?);
            } else {
                self.node(child)?;
            }
        }
        self.insert(id, name, byte_size, decl_file, annotations, kind);
        Ok(())
    }

    /// A variable's static address, from a location of `DW_OP_addr` or
    /// `DW_OP_addrx` alone.
    fn address(
        &self,
        entry: &gimli::DebuggingInformationEntry<R>,
    ) -> Result<Option<u64>> {
        let Some(AttributeValue::Exprloc(expr)) =
            entry.attr_value(gimli::DW_AT_location)
        else {
            return Ok(None);
        };
        let mut ops = expr.operations(self.unit.encoding());
        let address = match ops.next()? {
            Some(gimli::Operation::Address { address }) => address,
            Some(gimli::Operation::AddressIndex { index }) => {
                self.unit.address(index)?
            }
            _ => return Ok(None),
        };
        Ok((ops.next()?.is_none() && address != 0).then_some(address))
    }

    fn member(&mut self, node: EntriesTreeNode<'_, '_, R>) -> Result<Member> {
        let entry = node.entry();
        let mut member = Member {
            name: self.name(entry)?,
            ty: self.reference(entry, gimli::DW_AT_type)?,
            offset: entry
                .attr_value(gimli::DW_AT_data_member_location)
                .and_then(|v| v.udata_value()),
            bit_size: entry
                .attr_value(gimli::DW_AT_bit_size)
                .and_then(|v| v.udata_value()),
            bit_offset: entry
                .attr_value(gimli::DW_AT_data_bit_offset)
                .and_then(|v| v.udata_value()),
            annotations: Vec::new(),
        };
        let mut children = node.children();
        while let Some(child) = children.next()? {
            if child.entry().tag() == DW_TAG_LLVM_ANNOTATION {
                member.annotations.push(self.annotation(child.entry())?);
            } else {
                self.node(child)?;
            }
        }
        Ok(member)
    }

    fn annotation(
        &mut self,
        entry: &gimli::DebuggingInformationEntry<R>,
    ) -> Result<Annotation> {
        Ok(Annotation {
            name: self.name(entry)?,
            value: entry
                .attr_value(gimli::DW_AT_const_value)
                .map(|value| self.interner.attr(self.unit, value))
                .transpose()?,
        })
    }

    fn insert(
        &mut self,
        id: DieId,
        name: Option<Str>,
        byte_size: Option<u64>,
        decl_file: Option<Str>,
        annotations: Vec<Annotation>,
        kind: TypeKind,
    ) {
        self.types.push((
            id,
            Type {
                unit: self.index,
                name,
                byte_size,
                decl_file,
                scope: self.scope,
                annotations,
                kind,
            },
        ));
    }

    fn id(&self, offset: gimli::UnitOffset<R::Offset>) -> Result<DieId> {
        match offset.to_debug_info_offset(&self.unit.header) {
            Some(DebugInfoOffset(o)) => Ok(o.into_u64()),
            None => bail!("DIE is not in .debug_info"),
        }
    }

    fn name(
        &mut self,
        entry: &gimli::DebuggingInformationEntry<R>,
    ) -> Result<Option<Str>> {
        entry
            .attr_value(gimli::DW_AT_name)
            .map(|value| self.interner.attr(self.unit, value))
            .transpose()
    }

    fn reference(
        &self,
        entry: &gimli::DebuggingInformationEntry<R>,
        attr: DwAt,
    ) -> Result<Option<DieId>> {
        Ok(match entry.attr_value(attr) {
            Some(AttributeValue::UnitRef(offset)) => Some(self.id(offset)?),
            Some(AttributeValue::DebugInfoRef(DebugInfoOffset(o))) => {
                Some(o.into_u64())
            }
            _ => None,
        })
    }
}

fn subrange_count<R: Reader>(
    entry: &gimli::DebuggingInformationEntry<R>,
) -> Option<u64> {
    if let Some(count) = entry
        .attr_value(gimli::DW_AT_count)
        .and_then(|v| v.udata_value())
    {
        return Some(count);
    }
    entry
        .attr_value(gimli::DW_AT_upper_bound)
        .and_then(|v| v.udata_value())
        .map(|upper| upper + 1)
}

fn constant<R: Reader>(
    entry: &gimli::DebuggingInformationEntry<R>,
) -> Option<i64> {
    let value = entry.attr_value(gimli::DW_AT_const_value)?;
    value
        .sdata_value()
        .or_else(|| value.udata_value().map(|u| u as i64))
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn defines() {
        let split = |text| define.parse(text).unwrap();
        assert_eq!(
            split("JOBJ_SPLINE (1 << 14)"),
            ("JOBJ_SPLINE", "(1 << 14)")
        );
        assert_eq!(
            split("union_type_ptcl(o) (o->flags & JOBJ_PTCL)"),
            ("union_type_ptcl(o)", "(o->flags & JOBJ_PTCL)")
        );
        assert_eq!(split("EMPTY"), ("EMPTY", ""));
        assert_eq!(split("F(a, b) a + b"), ("F(a, b)", "a + b"));
    }
}
