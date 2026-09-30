//! Samples: one instance of each archive type, as a target object for
//! objdiff and as C that should compile to the same bytes.
//!
//! Archives are too large to diff whole, so each type the walk finds is
//! sampled once. A sample is the instance's bytes, with its relocated words
//! pointing to externs named after their targets (`dat_PlMr_1A40`). The C
//! side declares the same externs, so objdiff compares the pointers by name.
//! A type whose sample matches is taken to match in every archive.

use crate::{
    dwarf::{
        DieId, TypeGraph, TypeKind,
        canonical::{CanonId, Canonical},
        render::Renderer,
    },
    hsd::Archive,
    walk::Walk,
};
use anyhow::{Result, bail};
use object::{
    Architecture, BinaryFormat, Endianness, RelocationFlags, SectionKind,
    SymbolFlags, SymbolKind, SymbolScope,
    write::{Object, Relocation, StandardSegment, Symbol, SymbolSection},
};
use std::{
    collections::{BTreeMap, BTreeSet},
    fmt::Write,
};

/// MWCC puts initialized data this small in `.sdata`.
const SMALL_DATA_MAX: u64 = 8;

const FLOAT: u8 = gimli::constants::DW_ATE_float.0;
const SIGNED: u8 = gimli::constants::DW_ATE_signed.0;
const SIGNED_CHAR: u8 = gimli::constants::DW_ATE_signed_char.0;

/// Where a sample's instance is.
#[derive(Debug, Clone, PartialEq, Eq, PartialOrd, Ord)]
pub struct Location {
    /// The file relative to the dat base, e.g. `PlMr.dat`.
    pub file: String,
    /// Offset of the archive in its file.
    pub archive: usize,
    /// Offset of the instance in the archive's data.
    pub offset: u32,
}

/// One instance chosen to stand for its type.
#[derive(Debug, Clone)]
pub struct Sample {
    /// The type's representative DIE.
    pub die: DieId,
    /// The type's name, as C spells it (`HSD_Joint`, `struct Foo`).
    pub type_name: String,
    /// The header that declares the type, relative to its include directory.
    pub header: String,
    /// Other headers the sample needs, such as its typedef's.
    pub includes: Vec<String>,
    pub size: u64,
    pub location: Location,
    /// Relocated words in the instance.
    pub relocs: usize,
    /// Nonzero bytes in the instance.
    pub nonzero: usize,
    /// The walk found nothing wrong in its own fields.
    pub clean: bool,
    /// The member each tagged union inside chose, by the union's offset in
    /// the archive and its type.
    pub choices: BTreeMap<(u32, CanonId), usize>,
    /// Those choices by member name, in order: which variant of the type
    /// this is.
    pub variant: Vec<String>,
}

impl Sample {
    /// The symbol both sides define.
    pub fn symbol(&self) -> String {
        let mut symbol = format!("sample_{}", identifier(&self.type_name));
        for member in &self.variant {
            symbol.push_str("__");
            symbol.push_str(&identifier(member));
        }
        symbol
    }

    /// The unit it belongs to: its header without the extension, e.g.
    /// `sysdolphin/baselib/jobj`.
    pub fn unit(&self) -> &str {
        self.header.strip_suffix(".h").unwrap_or(&self.header)
    }
}

/// Why a type the walk found has no sample.
#[derive(Debug, Clone)]
pub struct Skipped {
    pub type_name: String,
    pub reason: String,
}

/// Picks the samples from walked archives.
pub struct Picker<'a> {
    graph: &'a TypeGraph,
    canonical: &'a Canonical,
    renderer: Renderer<'a>,
    /// By type and variant.
    best: BTreeMap<(String, Vec<String>), Sample>,
    skipped: BTreeMap<String, String>,
    /// Variants that need a type of their own, with where one is.
    variants: BTreeMap<String, String>,
    /// Unions some instance's tag chose a member of.
    chosen: BTreeSet<String>,
}

impl<'a> Picker<'a> {
    pub fn new(graph: &'a TypeGraph, canonical: &'a Canonical) -> Self {
        Picker {
            graph,
            canonical,
            renderer: Renderer::new(graph, canonical),
            best: BTreeMap::new(),
            skipped: BTreeMap::new(),
            variants: BTreeMap::new(),
            chosen: BTreeSet::new(),
        }
    }

    /// Consider every object one archive's walk typed.
    pub fn add(
        &mut self,
        file: &str,
        archive_offset: usize,
        archive: &Archive,
        walk: &Walk,
    ) {
        let relocs: BTreeSet<u32> = archive.relocs.iter().copied().collect();
        for (&offset, types) in &walk.objects {
            // An object reached as several types stands for none of them
            let [id] = types.iter().copied().collect::<Vec<_>>()[..] else {
                continue;
            };
            let mut die = self.canonical.get(id).rep;
            let TypeKind::Record { union, members, .. } =
                &self.graph.types[&die].kind
            else {
                continue;
            };
            // A tagged union stands for the member its tag chose, declared
            // as that member's own type, as the game's code does (e.g.
            // `HSD_CameraDescPerspective` for `HSD_CObjDesc`)
            if *union {
                let union_name = self.renderer.declare(Some(die), "");
                let Some(member) =
                    walk.choices.get(&(offset, id)).and_then(|&i| members.get(i))
                else {
                    if !self.chosen.contains(&union_name) {
                        self.skipped.entry(union_name).or_insert_with(|| {
                            "a union no instance's tag chooses a member of".into()
                        });
                    }
                    continue;
                };
                self.skipped.remove(&union_name);
                self.chosen.insert(union_name.clone());
                let member_die = member.ty.map(|t| self.resolve(t));
                let named = member_die.is_some_and(|d| {
                    let t = &self.graph.types[&d];
                    t.name.is_some() && matches!(t.kind, TypeKind::Record { .. })
                });
                if !named {
                    let name = member.name.map_or("?", |n| self.graph.str(n));
                    self.skipped.insert(
                        format!("{union_name}.{name}"),
                        "a variant with no type of its own".into(),
                    );
                    continue;
                }
                die = member_die.unwrap();
            }
            let ty = &self.graph.types[&die];
            let (mut type_name, mut typedef_header) = self.spelling(die);
            // An anonymous struct is named by its typedef, e.g. `Vec2`
            if ty.name.is_none() {
                match self.typedef_of(die) {
                    Some((name, header)) => {
                        type_name = name;
                        typedef_header = header;
                    }
                    None => {
                        self.skipped.insert(type_name, "anonymous".into());
                        continue;
                    }
                }
            }
            let Some(header) =
                ty.decl_file.and_then(|f| header(self.graph.str(f)))
            else {
                self.skipped.insert(type_name, "not declared in a header".into());
                continue;
            };
            let Some(size) = self.canonical.byte_size(self.graph, die) else {
                continue;
            };
            let end = offset as u64 + size;
            if size == 0 || end > archive.data.len() as u64 {
                continue;
            }
            // Only instances the walk found nothing wrong in: every
            // relocated word explained, and no finding through them
            let inside = relocs.range(offset..end as u32);
            let path = walk.paths.get(&offset).map_or("", String::as_str);
            let clean = inside.clone().all(|at| walk.pointers.contains(at))
                && !walk.issues.iter().any(|i| {
                    // Findings in its own fields, not behind its pointers
                    i.path()
                        .strip_prefix(path)
                        .is_some_and(|rest| !rest.contains("->"))
                });
            // A tagged union inside that chose other than its first member
            // can't be written as C89: that variant needs a type of its own
            let choices: BTreeMap<(u32, CanonId), usize> = walk
                .choices
                .range((offset, CanonId(0))..(end as u32, CanonId(0)))
                .map(|(&k, &v)| (k, v))
                .collect();
            let writer = CWriter::new(self.graph, self.canonical);
            let nested = choices.iter().find(|&(&(at, union), &i)| {
                i != 0
                    && (at, id) != (offset, id)
                    && !writer.first_carries(union, i)
            });
            if let Some((&(at, union), &index)) = nested {
                let member = match &self.canonical.ty(self.graph, union).kind {
                    TypeKind::Record { members, .. } => members
                        .get(index)
                        .and_then(|m| m.name)
                        .map_or("?", |n| self.graph.str(n)),
                    _ => "?",
                };
                let union_name = self
                    .renderer
                    .declare(Some(self.canonical.get(union).rep), "");
                self.variants
                    .entry(format!(
                        "{type_name} with {union_name} at +0x{:X} as .{member}",
                        at - offset
                    ))
                    .or_insert_with(|| {
                        format!("{file}@0x{archive_offset:X} at 0x{offset:X}")
                    });
                continue;
            }
            // The variant, by the members nested unions chose; a union
            // object's own choice is already its type
            let variant = choices
                .iter()
                .filter(|&(&(at, union), _)| (at, union) != (offset, id))
                .map(|(&(_, union), &index)| {
                    match &self.canonical.ty(self.graph, union).kind {
                        TypeKind::Record { members, .. } => members
                            .get(index)
                            .and_then(|m| m.name)
                            .map_or(index.to_string(), |n| {
                                self.graph.str(n).to_owned()
                            }),
                        _ => index.to_string(),
                    }
                })
                .collect();
            let bytes = &archive.data[offset as usize..end as usize];
            let candidate = Sample {
                die,
                type_name: type_name.clone(),
                header,
                includes: typedef_header.into_iter().collect(),
                size,
                location: Location {
                    file: file.to_owned(),
                    archive: archive_offset,
                    offset,
                },
                relocs: relocs.range(offset..end as u32).count(),
                nonzero: bytes.iter().filter(|&&b| b != 0).count(),
                clean,
                choices,
                variant,
            };
            // A clean instance if there is one, so that a sample fails
            // only where its type is wrong everywhere; then the one that
            // exercises the most: pointers, then data
            let key = (type_name, candidate.variant.clone());
            let better = self.best.get(&key).is_none_or(|best| {
                (candidate.clean, candidate.relocs, candidate.nonzero)
                    > (best.clean, best.relocs, best.nonzero)
            });
            if better {
                self.best.insert(key, candidate);
            }
        }
    }

    /// Look through typedefs and qualifiers, and from declarations to
    /// their definitions.
    fn resolve(&self, mut die: DieId) -> DieId {
        loop {
            match &self.graph.types[&die].kind {
                TypeKind::Typedef { target: Some(t) }
                | TypeKind::Const { target: Some(t) }
                | TypeKind::Volatile { target: Some(t) } => die = *t,
                TypeKind::Record {
                    declaration: true, ..
                } => {
                    return self
                        .canonical
                        .of(die)
                        .and_then(|id| self.canonical.definition(self.graph, id))
                        .map_or(die, |id| self.canonical.get(id).rep);
                }
                _ => return die,
            }
        }
    }

    /// A typedef that names an anonymous record, with its header.
    fn typedef_of(&self, die: DieId) -> Option<(String, Option<String>)> {
        let id = self.canonical.of(die)?;
        self.canonical.types.iter().find_map(|t| {
            let ty = &self.graph.types[&t.rep];
            let TypeKind::Typedef { target: Some(target) } = ty.kind else {
                return None;
            };
            if self.canonical.of(target) != Some(id) {
                return None;
            }
            Some((
                self.graph.str(ty.name?).to_owned(),
                ty.decl_file.and_then(|f| header(self.graph.str(f))),
            ))
        })
    }

    /// How C names a record: its typedef where one of the same name refers
    /// to it (`HSD_Joint`), else its tag (`struct HSD_Joint`).
    /// Also the typedef's header, when it has one.
    fn spelling(&self, die: DieId) -> (String, Option<String>) {
        let tagged = self.renderer.declare(Some(die), "");
        let Some(name) = self.graph.types[&die].name else {
            return (tagged, None);
        };
        let name = self.graph.str(name);
        let id = self.canonical.of(die);
        let typedef = self.canonical.lookup(self.graph, name).into_iter().find(|&t| {
            let TypeKind::Typedef { target: Some(target) } = self.graph.types[&t].kind
            else {
                return false;
            };
            let target = self.canonical.of(target);
            target.is_some()
                && (target == id
                    || target.and_then(|t| self.canonical.definition(self.graph, t)) == id)
        });
        match typedef {
            Some(t) => (
                name.to_owned(),
                self.graph.types[&t]
                    .decl_file
                    .and_then(|f| header(self.graph.str(f))),
            ),
            None => (tagged, None),
        }
    }

    pub fn finish(self) -> (Vec<Sample>, Vec<Skipped>) {
        let variants = self.variants.into_iter().map(|(variant, at)| Skipped {
            type_name: variant,
            reason: format!("needs a type of its own ({at})"),
        });
        let skipped = self
            .skipped
            .into_iter()
            .filter(|(name, _)| !self.best.keys().any(|(t, _)| t == name))
            .map(|(type_name, reason)| Skipped { type_name, reason })
            .chain(variants)
            .collect();
        (self.best.into_values().collect(), skipped)
    }
}

/// The include path of a header from its DWARF path, e.g.
/// `/.../src/melee/ft/types.h` to `melee/ft/types.h`; `None` if it isn't a
/// header.
fn header(path: &str) -> Option<String> {
    if !path.ends_with(".h") {
        return None;
    }
    let at = ["/src/", "/include/"]
        .iter()
        .filter_map(|dir| path.rfind(dir).map(|at| at + dir.len()))
        .max()?;
    Some(path[at..].to_owned())
}

/// A C identifier from a type name: `struct HSD_Joint` to `HSD_Joint`.
fn identifier(name: &str) -> String {
    let name = name
        .trim_start_matches("struct ")
        .trim_start_matches("union ");
    name.chars()
        .map(|c| if c.is_ascii_alphanumeric() { c } else { '_' })
        .collect()
}

/// The extern a relocated word points to, named after its target, e.g.
/// `dat_PlMr_1A40`, or `dat_PlBoAJ_1F20_34` inside a packed file.
pub fn target_symbol(location: &Location, target: u32) -> String {
    let stem = location.file.strip_suffix(".dat").unwrap_or(&location.file);
    let stem = identifier(stem);
    match location.archive {
        0 => format!("dat_{stem}_{target:X}"),
        archive => format!("dat_{stem}_{archive:X}_{target:X}"),
    }
}

/// The archive data a sample reads.
pub struct Source<'a> {
    pub archive: &'a Archive<'a>,
    relocs: BTreeSet<u32>,
}

impl<'a> Source<'a> {
    pub fn new(archive: &'a Archive<'a>) -> Self {
        Source {
            archive,
            relocs: archive.relocs.iter().copied().collect(),
        }
    }

    fn bytes(&self, offset: u32, size: u64) -> &[u8] {
        &self.archive.data[offset as usize..offset as usize + size as usize]
    }

    fn word(&self, offset: u32) -> u32 {
        u32::from_be_bytes(self.bytes(offset, 4).try_into().unwrap())
    }

    /// Relocated words in `offset..offset + size`, with their targets.
    fn relocs(&self, offset: u32, size: u64) -> Vec<(u32, u32)> {
        self.relocs
            .range(offset..offset + size as u32)
            .map(|&at| (at, self.word(at)))
            .collect()
    }
}

/// A unit's target object: every sample's bytes, with relocations to the
/// externs their words point to.
pub fn target_object(samples: &[(&Sample, &Source)]) -> Result<Vec<u8>> {
    let mut obj =
        Object::new(BinaryFormat::Elf, Architecture::PowerPc, Endianness::Big);
    let segment = obj.segment_name(StandardSegment::Data).to_vec();
    let data =
        obj.add_section(segment.clone(), b".data".to_vec(), SectionKind::Data);
    let sdata =
        obj.add_section(segment, b".sdata".to_vec(), SectionKind::Data);
    let mut externs = BTreeMap::new();
    for (sample, source) in samples {
        let section = if sample.size <= SMALL_DATA_MAX {
            sdata
        } else {
            data
        };
        let offset = sample.location.offset;
        // Relocated words hold their target in the relocation, as a
        // compiler writes them; the archive's value is only an offset
        let mut bytes = source.bytes(offset, sample.size).to_vec();
        for (word, _) in source.relocs(offset, sample.size) {
            let at = (word - offset) as usize;
            bytes[at..at + 4].fill(0);
        }
        let at = obj.append_section_data(section, &bytes, 4);
        obj.add_symbol(Symbol {
            name: sample.symbol().into_bytes(),
            value: at,
            size: sample.size,
            kind: SymbolKind::Data,
            scope: SymbolScope::Linkage,
            weak: false,
            section: SymbolSection::Section(section),
            flags: SymbolFlags::None,
        });
        for (word, target) in source.relocs(offset, sample.size) {
            let name = target_symbol(&sample.location, target);
            let symbol = *externs.entry(name.clone()).or_insert_with(|| {
                obj.add_symbol(Symbol {
                    name: name.into_bytes(),
                    value: 0,
                    size: 0,
                    kind: SymbolKind::Data,
                    scope: SymbolScope::Linkage,
                    weak: false,
                    section: SymbolSection::Undefined,
                    flags: SymbolFlags::None,
                })
            });
            obj.add_relocation(
                section,
                Relocation {
                    offset: at + u64::from(word - offset),
                    symbol,
                    addend: 0,
                    flags: RelocationFlags::Elf {
                        r_type: object::elf::R_PPC_ADDR32,
                    },
                },
            )?;
        }
    }
    Ok(obj.write()?)
}

/// Writes C initializers that should compile to a sample's bytes.
pub struct CWriter<'a> {
    graph: &'a TypeGraph,
    canonical: &'a Canonical,
    renderer: Renderer<'a>,
}

impl<'a> CWriter<'a> {
    pub fn new(graph: &'a TypeGraph, canonical: &'a Canonical) -> Self {
        CWriter {
            graph,
            canonical,
            renderer: Renderer::new(graph, canonical),
        }
    }

    /// A unit's C: its headers, the externs its pointers name, and one
    /// definition per sample.
    pub fn unit(&self, samples: &[(&Sample, &Source)]) -> Result<String> {
        let mut externs = BTreeSet::new();
        let mut defs = String::new();
        for (sample, source) in samples {
            let offset = sample.location.offset;
            for (_, target) in source.relocs(offset, sample.size) {
                externs.insert(target_symbol(&sample.location, target));
            }
            let location = &sample.location;
            let archive = match location.archive {
                0 => String::new(),
                a => format!("@0x{a:X}"),
            };
            writeln!(
                defs,
                "/// {}{archive} at 0x{:X}",
                location.file, location.offset
            )?;
            let mut init = String::new();
            let slots = BTreeSet::new();
            self.value(&mut init, sample, source, sample.die, offset, &slots, 0)?;
            writeln!(defs, "{} {} = {init};\n", sample.type_name, sample.symbol())?;
        }
        let mut out = String::from(concat!(
            "// Generated by `melee-dat samples build` from the types.\n\n",
            "#include <Runtime/platform.h>\n",
        ));
        let headers: BTreeSet<&str> = samples
            .iter()
            .flat_map(|(s, _)| {
                std::iter::once(s.header.as_str())
                    .chain(s.includes.iter().map(String::as_str))
            })
            .collect();
        for header in headers {
            writeln!(out, "#include <{header}>")?;
        }
        out.push('\n');
        for name in externs {
            writeln!(out, "extern u8 {name}[];")?;
        }
        if !samples.is_empty() {
            out.push('\n');
        }
        out.push_str(&defs);
        Ok(out)
    }

    /// Look through typedefs and qualifiers, and from declarations to
    /// their definitions.
    fn resolve(&self, mut die: DieId) -> DieId {
        loop {
            match &self.graph.types[&die].kind {
                TypeKind::Typedef { target: Some(t) }
                | TypeKind::Const { target: Some(t) }
                | TypeKind::Volatile { target: Some(t) }
                | TypeKind::Restrict { target: Some(t) } => die = *t,
                TypeKind::Record {
                    declaration: true, ..
                } => {
                    return self
                        .canonical
                        .of(die)
                        .and_then(|id| {
                            self.canonical.definition(self.graph, id)
                        })
                        .map_or(die, |id| self.canonical.get(id).rep);
                }
                _ => return die,
            }
        }
    }

    /// The initializer for a value of type `die` at `offset`.
    fn value(
        &self,
        out: &mut String,
        sample: &Sample,
        source: &Source,
        die: DieId,
        offset: u32,
        // Offsets where an enclosing union has a pointer in some member
        slots: &BTreeSet<u32>,
        depth: usize,
    ) -> Result<()> {
        if depth > 32 {
            bail!("{}: type nests too deep", sample.type_name);
        }
        let spelled = die;
        let die = self.resolve(die);
        let size = self.canonical.byte_size(self.graph, die).unwrap_or(0);
        match &self.graph.types[&die].kind {
            TypeKind::Record {
                union: false,
                members,
                ..
            } => {
                out.push('{');
                let mut first = true;
                for member in members {
                    let Some(ty) = member.ty else { continue };
                    if !first {
                        out.push_str(", ");
                    }
                    first = false;
                    if let Some(bits) = member.bit_size {
                        let start = member
                            .bit_offset
                            .unwrap_or(member.offset.unwrap_or(0) * 8);
                        let value = self.bits(source, offset, start, bits);
                        let signed = self.signed(ty);
                        let value = if signed
                            && bits < 64
                            && value >> (bits - 1) & 1 == 1
                        {
                            (value as i64) - (1i64 << bits)
                        } else {
                            value as i64
                        };
                        write!(out, "{value}")?;
                        continue;
                    }
                    let at = offset + member.offset.unwrap_or(0) as u32;
                    // A flexible array has no size and no initializer
                    let elements =
                        self.canonical.byte_size(self.graph, self.resolve(ty));
                    if elements == Some(0) {
                        out.push_str("{0}");
                        continue;
                    }
                    self.value(out, sample, source, ty, at, slots, depth + 1)?;
                }
                if first {
                    out.push('0');
                }
                out.push('}');
            }
            TypeKind::Record {
                union: true,
                members,
                ..
            } => {
                // C89 initializes a union through its first member only
                let Some(ty) = members.first().and_then(|m| m.ty) else {
                    out.push_str("{0}");
                    return Ok(());
                };
                // Relocations where the member its tag chose has pointers;
                // where no tag chose, wherever any member has one
                let mut slots = slots.clone();
                let chosen = self
                    .canonical
                    .of(die)
                    .and_then(|id| sample.choices.get(&(offset, id)))
                    .and_then(|&i| members.get(i));
                let candidates: Vec<_> = match chosen {
                    Some(member) => vec![member],
                    None => members.iter().collect(),
                };
                for member in candidates {
                    if let Some(ty) = member.ty {
                        self.pointer_offsets(ty, offset, &mut slots, 0);
                    }
                }
                out.push('{');
                self.value(out, sample, source, ty, offset, &slots, depth + 1)?;
                out.push('}');
            }
            TypeKind::Array { element, dims } => {
                let Some(element) = *element else {
                    out.push_str("{0}");
                    return Ok(());
                };
                let element_size = self
                    .canonical
                    .byte_size(self.graph, self.resolve(element))
                    .unwrap_or(0);
                let count: u64 = dims.iter().map(|d| d.unwrap_or(0)).product();
                // Nested dimensions are laid out flat, which C accepts
                out.push('{');
                if count == 0 || element_size == 0 {
                    out.push('0');
                }
                for i in 0..count {
                    if i > 0 {
                        out.push_str(", ");
                    }
                    let at = offset + (i * element_size) as u32;
                    self.value(out, sample, source, element, at, slots, depth + 1)?;
                }
                out.push('}');
            }
            TypeKind::Pointer { .. } => {
                let cast = self.renderer.declare(Some(spelled), "");
                self.word(out, sample, source, offset, &cast)?;
            }
            TypeKind::Base { encoding } => {
                // A relocated word is written as its raw value, the same
                // bytes without the relocation, so objdiff shows that the
                // field should be a pointer. Unless another member of an
                // enclosing union has one there
                if slots.contains(&offset) && source.relocs.contains(&offset) {
                    let cast = self.renderer.declare(Some(spelled), "");
                    return self.word(out, sample, source, offset, &cast);
                }
                let bytes = source.bytes(offset, size);
                match (*encoding, size) {
                    (FLOAT, 4) => {
                        let v = f32::from_be_bytes(bytes.try_into().unwrap());
                        float(out, format!("{v:?}"), v.is_finite(), "f")?;
                    }
                    (FLOAT, 8) => {
                        let v = f64::from_be_bytes(bytes.try_into().unwrap());
                        float(out, format!("{v:?}"), v.is_finite(), "")?;
                    }
                    _ => {
                        let value = bytes
                            .iter()
                            .fold(0u64, |acc, &b| acc << 8 | u64::from(b));
                        let signed = matches!(*encoding, SIGNED | SIGNED_CHAR);
                        integer(out, value, size, signed)?;
                    }
                }
            }
            TypeKind::Enum { .. } => {
                let bytes = source.bytes(offset, size);
                let value =
                    bytes.iter().fold(0u64, |acc, &b| acc << 8 | u64::from(b));
                integer(out, value, size, true)?;
            }
            _ => out.push('0'),
        }
        Ok(())
    }

    /// Whether a union's first member can carry member `index`: C89
    /// initializes a union through its first member, which has to be as
    /// large and have a pointer wherever the chosen member does.
    pub fn first_carries(&self, union: CanonId, index: usize) -> bool {
        let TypeKind::Record { members, .. } =
            &self.canonical.ty(self.graph, union).kind
        else {
            return false;
        };
        let (Some(first), Some(chosen)) = (
            members.first().and_then(|m| m.ty),
            members.get(index).and_then(|m| m.ty),
        ) else {
            return false;
        };
        let size = |die| {
            self.canonical
                .byte_size(self.graph, self.resolve(die))
                .unwrap_or(0)
        };
        let (mut first_pointers, mut chosen_pointers) =
            (BTreeSet::new(), BTreeSet::new());
        self.pointer_offsets(first, 0, &mut first_pointers, 0);
        self.pointer_offsets(chosen, 0, &mut chosen_pointers, 0);
        size(first) >= size(chosen) && chosen_pointers.is_subset(&first_pointers)
    }

    /// Every offset where `die` at `base` has a pointer.
    fn pointer_offsets(
        &self,
        die: DieId,
        base: u32,
        out: &mut BTreeSet<u32>,
        depth: usize,
    ) {
        if depth > 32 {
            return;
        }
        let die = self.resolve(die);
        match &self.graph.types[&die].kind {
            TypeKind::Pointer { .. } => {
                out.insert(base);
            }
            TypeKind::Record { members, .. } => {
                for m in members {
                    if let (Some(ty), None) = (m.ty, m.bit_size) {
                        let at = base + m.offset.unwrap_or(0) as u32;
                        self.pointer_offsets(ty, at, out, depth + 1);
                    }
                }
            }
            TypeKind::Array { element: Some(e), dims } => {
                let size = self
                    .canonical
                    .byte_size(self.graph, self.resolve(*e))
                    .unwrap_or(0);
                let count: u64 = dims.iter().map(|d| d.unwrap_or(0)).product();
                for i in 0..count.min(4096) {
                    let at = base + (i * size) as u32;
                    self.pointer_offsets(*e, at, out, depth + 1);
                }
            }
            _ => {}
        }
    }

    /// A pointer-sized word: the extern it points to, or its value.
    fn word(
        &self,
        out: &mut String,
        sample: &Sample,
        source: &Source,
        offset: u32,
        cast: &str,
    ) -> Result<()> {
        let value = source.word(offset);
        if source.relocs.contains(&offset) {
            write!(
                out,
                "({cast}) {}",
                target_symbol(&sample.location, value)
            )?;
        } else if value == 0 {
            out.push('0');
        } else {
            write!(out, "({cast}) 0x{value:X}")?;
        }
        Ok(())
    }

    /// Bits `start..start + len` of the record at `offset`, counted from the
    /// most significant bit of its first byte.
    fn bits(&self, source: &Source, offset: u32, start: u64, len: u64) -> u64 {
        (start..start + len).fold(0, |acc, bit| {
            let byte =
                source.archive.data[offset as usize + (bit / 8) as usize];
            acc << 1 | u64::from(byte >> (7 - bit % 8) & 1)
        })
    }

    fn signed(&self, die: DieId) -> bool {
        match self.graph.types[&self.resolve(die)].kind {
            TypeKind::Base { encoding } => {
                matches!(encoding, SIGNED | SIGNED_CHAR)
            }
            TypeKind::Enum { .. } => true,
            _ => false,
        }
    }
}

/// A float literal from Rust's shortest round-trip form, e.g. `1.0`,
/// `-1.564736` or `1e-7`.
fn float(
    out: &mut String,
    v: String,
    finite: bool,
    suffix: &str,
) -> Result<()> {
    if !finite {
        // No literal has these bits; objdiff will show the difference
        write!(out, "0.0{suffix} /* {v} */")?;
    } else {
        write!(out, "{v}{suffix}")?;
    }
    Ok(())
}

fn integer(
    out: &mut String,
    value: u64,
    size: u64,
    signed: bool,
) -> Result<()> {
    let bits = size * 8;
    if signed && bits > 0 && bits < 64 && value >> (bits - 1) & 1 == 1 {
        let v = value as i64 - (1i64 << bits);
        write!(out, "{v}")?;
    } else if value > 9 {
        write!(out, "0x{value:X}")?;
    } else {
        write!(out, "{value}")?;
    }
    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn headers() {
        assert_eq!(
            header("/x/melee/src/melee/ft/types.h").as_deref(),
            Some("melee/ft/types.h")
        );
        assert_eq!(
            header("/x/libs/dolphin/include/dolphin/mtx.h").as_deref(),
            Some("dolphin/mtx.h")
        );
        assert_eq!(header("/x/src/melee/gr/grzebes.c"), None);
    }

    #[test]
    fn target_symbols() {
        let at = |file: &str, archive| Location {
            file: file.into(),
            archive,
            offset: 0,
        };
        assert_eq!(target_symbol(&at("PlMr.dat", 0), 0x1A40), "dat_PlMr_1A40");
        assert_eq!(
            target_symbol(&at("PlBoAJ.dat", 0x1F20), 0x34),
            "dat_PlBoAJ_1F20_34"
        );
    }
}
