//! Samples: one instance of each archive type, as a target object for
//! objdiff and as C that should compile to the same bytes.
//!
//! By default each type the walk finds is sampled once per variant its
//! tagged unions choose; `--all` samples every typed object. Samples are
//! grouped into one unit per archive. A sample is the instance's bytes under
//! the name the archive gives it, or else one [`name_of`] makes up from the
//! walk path (local to the unit), with its relocated words pointing to
//! symbols named the same way. The C side defines the same names with
//! designated initializers, generated from the types, so objdiff compares
//! data and pointers by name. A type whose
//! sample matches is taken to match in every archive.

use crate::{
    dwarf::{
        DieId, Member, TypeGraph, TypeKind,
        canonical::{CanonId, Canonical},
        render::Renderer,
    },
    hsd::Archive,
    walk::Walk,
};
use anyhow::{Context, Result, bail};
use globset::GlobSet;
use object::{
    Architecture, BinaryFormat, Endianness, RelocationFlags, SectionKind,
    SymbolFlags, SymbolKind, SymbolScope,
    write::{Object, Relocation, StandardSegment, Symbol, SymbolId, SymbolSection},
};
use std::{
    collections::{BTreeMap, BTreeSet},
    fmt::Write,
};

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
    /// The type's DIE. For a union object, the member its tag chose: the
    /// archive only holds that member's bytes.
    pub die: DieId,
    /// The type as C declares it (`struct HSD_Joint`, `Vec2`, or
    /// `typeof(((union U *) 0)->member)` for a union object).
    pub type_name: String,
    /// The type's name for looking it up again: its tag, or the typedef
    /// that names it.
    pub lookup: String,
    /// For a union object, the member its tag chose.
    pub member: Option<String>,
    /// The root the walk first reached it from, e.g. `ftDataMario`.
    pub root: String,
    /// The header that declares the type, relative to its include directory.
    pub header: String,
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
    /// The unit it belongs to: its archive's file without the extension,
    /// e.g. `PlMr`.
    pub fn unit(&self) -> &str {
        let file = &self.location.file;
        file.strip_suffix(".dat").unwrap_or(file)
    }
}

/// Why a type the walk found has no sample.
#[derive(Debug, Clone)]
pub struct Skipped {
    pub type_name: String,
    pub reason: &'static str,
}

/// A sample as the sidecar next to its target object describes it.
#[derive(Debug, Clone, serde::Serialize, serde::Deserialize)]
pub struct SampleInfo {
    /// Its symbol in the target object.
    pub symbol: String,
    /// The archive names it: a public symbol, global in both objects. The
    /// others are local to the unit: `LOCAL` (`static`, kept) in C.
    pub public: bool,
    /// Where it was in the archive.
    pub offset: u32,
    /// Offset of the archive in its file; nonzero inside packed files.
    pub archive: usize,
    pub size: u64,
    /// The type as C declares it.
    pub type_name: String,
    /// The type's tag or typedef name, to look it up in the DWARF.
    pub lookup: String,
    /// For a union object, the member its tag chose.
    pub member: Option<String>,
    /// The root the walk first reached it from.
    pub root: String,
    /// The header that declares the type.
    pub header: String,
    /// The members its tagged unions chose, in order.
    pub variant: Vec<String>,
    pub choices: Vec<Choice>,
}

/// The member a tagged union inside a sample chose.
#[derive(Debug, Clone, serde::Serialize, serde::Deserialize)]
pub struct Choice {
    /// Offset of the union in the sample.
    pub offset: u32,
    /// The union type, as C declares it.
    pub union: String,
    /// Index of the member.
    pub member: usize,
}

/// A sample's data, as codegen reads it from the target object.
pub struct Instance<'a> {
    pub info: &'a SampleInfo,
    pub bytes: &'a [u8],
    /// Relocated words, by offset in the sample, with the symbol each
    /// points to.
    pub relocs: BTreeMap<u32, String>,
}

/// An object's type as C declares it, from [`Picker::describe`].
pub struct Typed {
    /// The record's DIE, or the member's for a union object.
    pub die: DieId,
    pub type_name: String,
    pub lookup: String,
    pub member: Option<String>,
    pub header: String,
    pub size: u64,
    /// The type and the union member, for telling samples apart.
    pub key: String,
}

/// A sample's type and variant, and in [`Picker::all`] mode its archive
/// and offset.
type PickKey = (String, Vec<String>, Option<(usize, u32)>);

/// Picks the samples from walked archives.
pub struct Picker<'a> {
    graph: &'a TypeGraph,
    canonical: &'a Canonical,
    renderer: Renderer<'a>,
    /// By type and variant, and in [`Picker::all`] mode by location too.
    best: BTreeMap<PickKey, Sample>,
    skipped: BTreeMap<String, &'static str>,
    /// Keep every instance, not the best of each type and variant.
    all: bool,
    /// Types never sampled, by name.
    exclude: GlobSet,
}

impl<'a> Picker<'a> {
    pub fn new(graph: &'a TypeGraph, canonical: &'a Canonical) -> Self {
        Picker {
            graph,
            canonical,
            renderer: Renderer::new(graph, canonical),
            best: BTreeMap::new(),
            skipped: BTreeMap::new(),
            all: false,
            exclude: GlobSet::empty(),
        }
    }

    /// Keep every instance of every type, except the types `exclude`
    /// matches.
    pub fn select(mut self, all: bool, exclude: GlobSet) -> Self {
        self.all = all;
        self.exclude = exclude;
        self
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
            let typed = match self.describe(id, offset, walk) {
                Ok(typed) => typed,
                Err(Some((type_name, reason))) => {
                    self.skipped.entry(type_name).or_insert(reason);
                    continue;
                }
                Err(None) => continue,
            };
            let Typed {
                die,
                type_name,
                lookup,
                member: member_name,
                header,
                size,
                key: key_name,
            } = typed;
            if self.exclude.is_match(&key_name)
                || self.exclude.is_match(&lookup)
            {
                continue;
            }
            let end = offset as u64 + size;
            if size == 0 || end > archive.data.len() as u64 {
                continue;
            }
            // Whether the walk found nothing wrong in it: every relocated
            // word explained, and no finding in its own fields
            let inside = relocs.range(offset..end as u32);
            let path = walk.paths.get(&offset).map_or("", String::as_str);
            let clean = inside.clone().all(|at| walk.pointers.contains(at))
                && !walk.issues.iter().any(|i| {
                    // Not behind its pointers
                    i.path()
                        .strip_prefix(path)
                        .is_some_and(|rest| !rest.contains("->"))
                });
            // The variant: what each tagged union inside chose
            let choices: BTreeMap<(u32, CanonId), usize> = walk
                .choices
                .range((offset, CanonId(0))..(end as u32, CanonId(0)))
                .filter(|&(&key, _)| key != (offset, id))
                .map(|(&k, &v)| (k, v))
                .collect();
            let variant = choices
                .iter()
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
            let root = root_of(path).to_owned();
            let bytes = &archive.data[offset as usize..end as usize];
            let candidate = Sample {
                die,
                type_name: type_name.clone(),
                lookup,
                member: member_name,
                root,
                header,
                size,
                location: Location {
                    file: file.to_owned(),
                    archive: archive_offset,
                    offset,
                },
                relocs: inside.count(),
                nonzero: bytes.iter().filter(|&&b| b != 0).count(),
                clean,
                choices,
                variant,
            };
            // A clean instance if there is one, so that a sample fails
            // only where its type is wrong everywhere; then the one that
            // exercises the most: pointers, then data
            let at = self.all.then_some((archive_offset, offset));
            let key = (key_name, candidate.variant.clone(), at);
            let better = self.best.get(&key).is_none_or(|best| {
                (candidate.clean, candidate.relocs, candidate.nonzero)
                    > (best.clean, best.relocs, best.nonzero)
            });
            if better {
                self.best.insert(key, candidate);
            }
        }
    }

    /// How C declares an object the walk typed as `id`: a record declared
    /// in a header, or the member a union object's tag chose. `Err` with
    /// the type and why not, or `None` where it isn't a record.
    pub fn describe(
        &self,
        id: CanonId,
        offset: u32,
        walk: &Walk,
    ) -> Result<Typed, Option<(String, &'static str)>> {
        let die = self.canonical.get(id).rep;
        let ty = &self.graph.types[&die];
        if !matches!(ty.kind, TypeKind::Record { .. }) {
            return Err(None);
        }
        let mut type_name = self.renderer.declare(Some(die), "");
        let mut lookup = ty
            .name
            .map(|n| self.graph.str(n).to_owned())
            .unwrap_or_default();
        let mut decl_file = ty.decl_file;
        // An anonymous record is named by its typedef, e.g. `Vec2`
        if ty.name.is_none() {
            let Some(typedef) = self.typedef_of(id) else {
                return Err(Some((type_name, "anonymous")));
            };
            let typedef = &self.graph.types[&typedef];
            type_name = typedef
                .name
                .map_or(type_name, |n| self.graph.str(n).to_owned());
            lookup = type_name.clone();
            decl_file = typedef.decl_file;
        }
        let Some(header) = decl_file.and_then(|f| header(self.graph.str(f)))
        else {
            return Err(Some((type_name, "not declared in a header")));
        };
        let mut die = die;
        let mut key = type_name.clone();
        let mut member_name = None;
        if let TypeKind::Record {
            union: true,
            members,
            ..
        } = &ty.kind
        {
            // A union object is the member its tag chose: the archive only
            // holds that member's bytes, and other data follows
            let member = walk
                .choices
                .get(&(offset, id))
                .and_then(|&i| members.get(i));
            let Some((member, member_ty)) =
                member.and_then(|m| Some((m, m.ty?)))
            else {
                return Err(Some((
                    type_name,
                    "a union no tag chooses a member of",
                )));
            };
            let name = member.name.map_or("?", |n| self.graph.str(n));
            key = format!("{type_name}.{name}");
            type_name = format!("typeof((({type_name} *) 0)->{name})");
            member_name = Some(name.to_owned());
            die = member_ty;
        }
        let size = self.member_size(die).ok_or(None)?;
        Ok(Typed {
            die,
            type_name,
            lookup,
            member: member_name,
            header,
            size,
            key,
        })
    }

    /// What codegen needs to know about a sample, by name.
    pub fn info(
        &self,
        sample: &Sample,
        symbol: String,
        public: bool,
    ) -> SampleInfo {
        let base = sample.location.offset;
        SampleInfo {
            symbol,
            public,
            offset: sample.location.offset,
            archive: sample.location.archive,
            size: sample.size,
            type_name: sample.type_name.clone(),
            lookup: sample.lookup.clone(),
            member: sample.member.clone(),
            root: sample.root.clone(),
            header: sample.header.clone(),
            variant: sample.variant.clone(),
            choices: sample
                .choices
                .iter()
                .map(|(&(at, union), &member)| Choice {
                    offset: at - base,
                    union: self
                        .renderer
                        .declare(Some(self.canonical.get(union).rep), ""),
                    member,
                })
                .collect(),
        }
    }

    /// The size of a member's type, through typedefs.
    fn member_size(&self, mut die: DieId) -> Option<u64> {
        while let TypeKind::Typedef { target: Some(t) }
        | TypeKind::Const { target: Some(t) }
        | TypeKind::Volatile { target: Some(t) } =
            self.graph.types[&die].kind
        {
            die = t;
        }
        self.canonical.byte_size(self.graph, die)
    }

    /// A typedef that names an anonymous record.
    fn typedef_of(&self, id: CanonId) -> Option<DieId> {
        self.canonical.types.iter().map(|t| t.rep).find(|rep| {
            let ty = &self.graph.types[rep];
            matches!(
                ty.kind,
                TypeKind::Typedef { target: Some(t) }
                    if ty.name.is_some() && self.canonical.of(t) == Some(id)
            )
        })
    }

    pub fn finish(self) -> (Vec<Sample>, Vec<Skipped>) {
        let skipped = self
            .skipped
            .into_iter()
            .filter(|(name, _)| {
                !self.best.keys().any(|(t, _, _)| {
                    t == name
                        || t.strip_prefix(name.as_str())
                            .is_some_and(|m| m.starts_with('.'))
                })
            })
            .map(|(type_name, reason)| Skipped { type_name, reason })
            .collect();
        (self.best.into_values().collect(), skipped)
    }
}

/// The root a walk path starts from.
pub fn root_of(path: &str) -> &str {
    path.split(['.', '-', '['])
        .next()
        .filter(|r| !r.is_empty())
        .unwrap_or("unknown")
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

/// Whether a name from an archive can be used as a C identifier.
fn is_identifier(name: &str) -> bool {
    let mut chars = name.chars();
    chars
        .next()
        .is_some_and(|c| c.is_ascii_alphabetic() || c == '_')
        && chars.all(|c| c.is_ascii_alphanumeric() || c == '_')
}

/// The fields of a walk path, each with the indices after it:
/// `ftDataMario.x48_items->[4].x8->child->` is `ftDataMario`, `x48_items_4`,
/// `x8`, `child`. Script offsets (`+0x1C`) are left out.
fn segments(path: &str) -> Vec<String> {
    let is_word = |c: char| c.is_ascii_alphanumeric() || c == '_';
    let mut out: Vec<String> = Vec::new();
    let mut rest = path;
    while let Some(c) = rest.chars().next() {
        let word = rest.find(|c| !is_word(c)).unwrap_or(rest.len());
        if word > 0 {
            out.push(rest[..word].to_owned());
            rest = &rest[word..];
            continue;
        }
        rest = &rest[c.len_utf8()..];
        match c {
            '[' => {
                let end = rest.find(']').unwrap_or(rest.len());
                let index = &rest[..end];
                if let Some(last) = out.last_mut()
                    && !index.is_empty()
                    && index.chars().all(is_word)
                {
                    *last += &format!("_{index}");
                }
                rest = rest.get(end + 1..).unwrap_or("");
            }
            '+' => rest = &rest[rest.find(|c| !is_word(c)).unwrap_or(rest.len())..],
            _ => {}
        }
    }
    out
}

/// Data an archive doesn't name, for [`assign_names`].
pub struct Unnamed<'r> {
    /// Offset of its archive in the file.
    pub archive: usize,
    pub offset: u32,
    /// For data the samples point to but that isn't written as C: the root
    /// it belongs to. Its name is global, so it starts with that root,
    /// which the archive names.
    pub elided: Option<&'r str>,
}

/// A name for data its archive doesn't name: the field the walk first
/// reached it through, with any indices, then its offset (`child_x1A0`,
/// `x1C_4_x2818`), or only the offset where no field reaches it. An elided
/// object's name starts with its root (`ftDataFox_ad_x5F20`). Flat, however
/// deep the data is, and unique by its offset.
fn name_of(
    path: Option<&str>,
    elided: Option<&str>,
    archive: usize,
    offset: u32,
) -> String {
    let at = match archive {
        0 => format!("x{offset:X}"),
        archive => format!("x{archive:X}_{offset:X}"),
    };
    // The root itself isn't a field
    let segments = path.map(segments).unwrap_or_default();
    let name = match &segments[..] {
        [_, .., field] => format!("{field}_{at}"),
        _ => at,
    };
    match elided {
        Some(root) => format!("{root}_{name}"),
        None => name,
    }
}

/// Names the data its archive doesn't name, with [`name_of`].
pub fn assign_names(sources: &mut BTreeMap<usize, Source>, wanted: &[Unnamed]) {
    for u in wanted {
        if let Some(source) = sources.get_mut(&u.archive) {
            let path = source.paths.get(&u.offset).map(String::as_str);
            let name = name_of(path, u.elided, u.archive, u.offset);
            source.names.insert(u.offset, name);
        }
    }
}

/// One archive's data, as samples read and name it.
pub struct Source<'a> {
    pub archive: &'a Archive<'a>,
    /// Offset of the archive in its file; nonzero inside packed files.
    archive_offset: usize,
    relocs: BTreeSet<u32>,
    /// Words the loader points at other archives' symbols, with their names.
    externs: BTreeMap<u32, String>,
    /// Public symbols by offset.
    publics: BTreeMap<u32, String>,
    /// The walk's first path to each object, by offset.
    paths: BTreeMap<u32, String>,
    /// Names [`assign_names`] gave the data the archive doesn't name.
    names: BTreeMap<u32, String>,
}

impl<'a> Source<'a> {
    /// `paths` are the walk's: where each object was first reached from.
    /// `unit` prefixes the externs' names.
    pub fn new(
        archive: &'a Archive<'a>,
        archive_offset: usize,
        unit: &str,
        paths: &BTreeMap<u32, String>,
    ) -> Self {
        let mut publics = BTreeMap::new();
        for (name, symbol) in archive.named_publics() {
            if let Ok(name) = std::str::from_utf8(name)
                && is_identifier(name)
            {
                publics.entry(symbol.offset).or_insert(name.to_owned());
            }
        }
        Source {
            archive,
            archive_offset,
            relocs: archive.relocs.iter().copied().collect(),
            // Every unit pointing to an extern declares it again, without
            // a type: prefixed so that the declarations don't collide in an
            // index of the units' sources
            externs: archive
                .extern_slots()
                .into_iter()
                .map(|(at, name)| {
                    (at, format!("{unit}_{}", String::from_utf8_lossy(name)))
                })
                .collect(),
            publics,
            paths: paths.clone(),
            names: BTreeMap::new(),
        }
    }

    /// Where `offset` is in the file: inside a packed file, past the
    /// archives before it.
    pub fn file_offset(&self, offset: u32) -> u64 {
        (self.archive_offset + offset as usize) as u64
    }

    /// Whether the archive names the data at `offset`.
    pub fn is_public(&self, offset: u32) -> bool {
        self.publics.contains_key(&offset)
    }

    /// Extern slots in `offset..offset + size`, with the externs' names.
    pub fn externs(&self, offset: u32, size: u64) -> Vec<(u32, &str)> {
        self.externs
            .range(offset..offset + size as u32)
            .map(|(&at, name)| (at, name.as_str()))
            .collect()
    }

    /// What the data at `offset` is called: its public symbol's name, else
    /// the one [`assign_names`] gave it, else `x<OFFSET>` (`x<ARCHIVE>_<OFFSET>`
    /// inside a packed file).
    pub fn name(&self, offset: u32) -> String {
        if let Some(name) = self.publics.get(&offset).or(self.names.get(&offset))
        {
            return name.clone();
        }
        match self.archive_offset {
            0 => format!("x{offset:X}"),
            archive => format!("x{archive:X}_{offset:X}"),
        }
    }

    fn bytes(&self, offset: u32, size: u64) -> &[u8] {
        &self.archive.data[offset as usize..offset as usize + size as usize]
    }

    fn word(&self, offset: u32) -> u32 {
        u32::from_be_bytes(self.bytes(offset, 4).try_into().unwrap())
    }

    /// Relocated words in `offset..offset + size`, with their targets.
    pub fn relocs(&self, offset: u32, size: u64) -> Vec<(u32, u32)> {
        self.relocs
            .range(offset..offset + size as u32)
            .map(|&at| (at, self.word(at)))
            .collect()
    }
}

/// The samples' section, in both objects. objdiff takes a section's kind
/// from its type and flags, and pairs sections and symbols by section name;
/// it lists sections by name, hence the numbers.
pub const SAMPLED: &str = ".0.sampled";
/// The rest of the archive: all of it in the target, and in the base what
/// the walk explains by its type, which objdiff pairs by name and matches by
/// size. The rest shows as missing in the base.
pub const INFERRED: &str = ".1.inferred";

/// A span of archive data an object defines.
#[derive(Clone)]
pub struct Piece<'s, 'a> {
    pub source: &'s Source<'a>,
    pub offset: u32,
    pub size: u64,
    /// Global with default visibility, else local.
    pub global: bool,
}

fn data_symbol(name: String, section: SymbolSection, value: u64, size: u64, global: bool) -> Symbol {
    Symbol {
        name: name.into_bytes(),
        value,
        size,
        kind: SymbolKind::Data,
        // Global with default visibility, or local
        scope: match global {
            true => SymbolScope::Dynamic,
            false => SymbolScope::Compilation,
        },
        weak: false,
        section,
        flags: SymbolFlags::None,
    }
}

/// Every piece in a section of uninitialized data, in order, by name and
/// size only.
fn add_bss(
    obj: &mut Object,
    section: &str,
    pieces: &[Piece],
    symbols: &mut BTreeMap<String, SymbolId>,
) {
    if pieces.is_empty() {
        return;
    }
    let segment = obj.segment_name(StandardSegment::Data).to_vec();
    let bss = obj.add_section(
        segment,
        section.as_bytes().to_vec(),
        SectionKind::UninitializedData,
    );
    for piece in pieces {
        let at = obj.append_section_bss(bss, piece.size, 1);
        let name = piece.source.name(piece.offset);
        let id = obj.add_symbol(data_symbol(
            name.clone(),
            SymbolSection::Section(bss),
            at,
            piece.size,
            piece.global,
        ));
        symbols.insert(name, id);
    }
}

/// A unit's target object: the samples' bytes in [`SAMPLED`], with
/// relocations to the names their words point to, then the rest of the
/// archive in [`INFERRED`], uninitialized, so objdiff never diffs bytes of
/// it. Both in archive order; each symbol's offset in the archive is in the
/// `.note.split` (see [`split_note`]).
pub fn target_object(samples: &[Piece], rest: &[Piece], archive: &str) -> Result<Vec<u8>> {
    let build = |note: Option<Vec<u8>>| -> Result<Vec<u8>> {
        let mut obj =
            Object::new(BinaryFormat::Elf, Architecture::PowerPc, Endianness::Big);
        let segment = obj.segment_name(StandardSegment::Data).to_vec();
        let data = obj.add_section(segment, SAMPLED.as_bytes().to_vec(), SectionKind::Data);
        // Every piece first, so that pointers between them use their symbols
        let mut symbols = BTreeMap::new();
        let mut placed = Vec::new();
        for &Piece {
            source,
            offset,
            size,
            global,
        } in samples
        {
            // Relocated words hold their target in the relocation, as a
            // compiler writes them; the archive's value is only an offset
            let mut bytes = source.bytes(offset, size).to_vec();
            // So do the words the loader links to other archives' symbols
            let externs = source.externs(offset, size);
            let words = source.relocs(offset, size).into_iter().map(|(w, _)| w);
            for word in words.chain(externs.iter().map(|&(w, _)| w)) {
                let at = (word - offset) as usize;
                bytes[at..at + 4].fill(0);
            }
            let at = obj.append_section_data(data, &bytes, 4);
            let name = source.name(offset);
            let id = obj.add_symbol(data_symbol(
                name.clone(),
                SymbolSection::Section(data),
                at,
                size,
                global,
            ));
            symbols.insert(name, id);
            placed.push(at);
        }
        add_bss(&mut obj, INFERRED, rest, &mut symbols);
        for (piece, at) in samples.iter().zip(placed) {
            let Piece {
                source,
                offset,
                size,
                ..
            } = *piece;
            let relocs = source
                .relocs(offset, size)
                .into_iter()
                .map(|(word, target)| (word, source.name(target)));
            let externs = source
                .externs(offset, size)
                .into_iter()
                .map(|(word, name)| (word, name.to_owned()));
            for (word, name) in relocs.chain(externs) {
                let id = *symbols.entry(name.clone()).or_insert_with(|| {
                    obj.add_symbol(data_symbol(name, SymbolSection::Undefined, 0, 0, true))
                });
                obj.add_relocation(
                    data,
                    Relocation {
                        offset: at + u64::from(word - offset),
                        symbol: id,
                        addend: 0,
                        flags: RelocationFlags::Elf {
                            r_type: object::elf::R_PPC_ADDR32,
                        },
                    },
                )?;
            }
        }
        if let Some(note) = note {
            let section = obj.add_section(
                Vec::new(),
                b".note.split".to_vec(),
                SectionKind::Note,
            );
            obj.set_section_data(section, note, 4);
        }
        Ok(obj.write()?)
    };
    // The note is indexed by the symbol table, which only the written
    // object orders; a section without symbols doesn't reorder it
    let addresses: BTreeMap<String, u64> = samples
        .iter()
        .chain(rest)
        .map(|p| (p.source.name(p.offset), p.source.file_offset(p.offset)))
        .collect();
    let first = build(None)?;
    let note = split_note(&first, &addresses, archive)?;
    build(Some(note))
}

/// The base's share of the rest of the archive: the data the walk explains
/// by its type, in [`INFERRED`] by name and size like the target's, so that
/// objdiff pairs and matches them without diffing bytes.
pub fn rest_object(inferred: &[Piece]) -> Result<Vec<u8>> {
    let mut obj =
        Object::new(BinaryFormat::Elf, Architecture::PowerPc, Endianness::Big);
    add_bss(&mut obj, INFERRED, inferred, &mut BTreeMap::new());
    Ok(obj.write()?)
}

/// A `.note.split` section as decomp-toolkit writes one and objdiff reads it
/// (objdiff-core's `split_meta.rs`): the generator, the module (the archive
/// file) and every symbol's original address, here its offset in the file,
/// which objdiff shows as the symbol's virtual address.
fn split_note(object: &[u8], addresses: &BTreeMap<String, u64>, archive: &str) -> Result<Vec<u8>> {
    use object::{Object as _, ObjectSymbol as _};
    let file = object::File::parse(object)?;
    // Index 0 is the null symbol, which the iterator skips
    let mut virt = vec![0u32; 1];
    for symbol in file.symbols() {
        let index = symbol.index().0;
        if virt.len() <= index {
            virt.resize(index + 1, 0);
        }
        if symbol.is_definition()
            && let Some(&at) = addresses.get(symbol.name()?)
        {
            virt[index] = at as u32;
        }
    }
    let mut out = Vec::new();
    let mut note = |kind: &[u8; 4], desc: &[u8]| {
        out.extend_from_slice(&6u32.to_be_bytes());
        out.extend_from_slice(&(desc.len() as u32).to_be_bytes());
        out.extend_from_slice(kind);
        out.extend_from_slice(b"Split\0\0\0");
        out.extend_from_slice(desc);
        out.resize(out.len().next_multiple_of(4), 0);
    };
    note(b"GENR", b"melee-dat");
    note(b"MODN", archive.as_bytes());
    let desc: Vec<u8> = virt.iter().flat_map(|a| a.to_be_bytes()).collect();
    note(b"VIRT", &desc);
    Ok(out)
}

/// Data the samples point to that isn't written as C: declared, as its type
/// or as bytes.
#[derive(serde::Serialize, serde::Deserialize)]
pub struct Elided {
    /// The root it belongs to: its header declares it.
    pub root: String,
    /// Its type's size where the walk typed it, else up to where the next
    /// object, public symbol or pointer target starts.
    pub size: u32,
    /// Its type where the walk typed it as one record; else it's bytes.
    pub ty: Option<ElidedType>,
}

/// An elided object's type, declared like a sample's.
#[derive(serde::Serialize, serde::Deserialize)]
pub struct ElidedType {
    pub type_name: String,
    pub lookup: String,
    pub member: Option<String>,
    pub header: String,
}

/// A root's samples, the archive externs it declares, and the elided data
/// it declares.
type RootParts<'i, 'n> =
    (Vec<&'i Instance<'i>>, Vec<&'n str>, Vec<(&'n str, &'n Elided)>);

/// A root's generated C, named after it.
pub struct RootFiles {
    pub name: String,
    pub header: String,
    /// None for a root with no samples, only data they point to.
    pub source: Option<String>,
}

/// A root name as a file name.
fn file_name(root: &str) -> String {
    root.chars()
        .map(|c| if c.is_ascii_alphanumeric() { c } else { '_' })
        .collect()
}

/// Writes C initializers that should compile to a sample's bytes.
pub struct CWriter<'a> {
    graph: &'a TypeGraph,
    canonical: &'a Canonical,
    renderer: Renderer<'a>,
    /// The types of the unit's samples and typed elided data, by symbol,
    /// so pointers to them need no cast.
    samples: std::cell::RefCell<BTreeMap<String, CanonId>>,
}

impl<'a> CWriter<'a> {
    pub fn new(graph: &'a TypeGraph, canonical: &'a Canonical) -> Self {
        CWriter {
            graph,
            canonical,
            renderer: Renderer::new(graph, canonical),
            samples: Default::default(),
        }
    }

    /// A unit's C, one root at a time: its header, declaring the root's
    /// samples, and its source, defining them.
    /// `elided` is the other data in the archive the samples point to, by
    /// name; `externs` are the archive's externs they point to, which the
    /// first root pointing to each declares. Both are declared as `UNK_T`
    /// unless the walk typed them.
    pub fn unit(
        &self,
        archive: &str,
        instances: &[Instance],
        elided: &BTreeMap<String, Elided>,
        externs: &BTreeSet<String>,
    ) -> Result<Vec<RootFiles>> {
        let mut linked: BTreeMap<&str, &str> = BTreeMap::new();
        for inst in instances {
            for name in inst.relocs.values() {
                if let Some(name) = externs.get(name) {
                    linked.entry(name).or_insert(inst.info.root.as_str());
                }
            }
        }
        let owners: BTreeMap<&str, &str> = instances
            .iter()
            .map(|i| (i.info.symbol.as_str(), i.info.root.as_str()))
            .chain(elided.iter().map(|(n, e)| (n.as_str(), e.root.as_str())))
            .chain(linked.iter().map(|(&n, &r)| (n, r)))
            .collect();
        let mut samples = BTreeMap::new();
        let typed = instances
            .iter()
            .map(|i| {
                let info = i.info;
                (&info.symbol, &info.lookup, &info.member)
            })
            .chain(elided.iter().filter_map(|(name, e)| {
                let ty = e.ty.as_ref()?;
                Some((name, &ty.lookup, &ty.member))
            }));
        for (symbol, lookup, member) in typed {
            let die = self.resolve(self.die_of(symbol, lookup, member)?);
            if let Some(id) = self.canonical.of(die) {
                samples.insert(symbol.clone(), id);
            }
        }
        *self.samples.borrow_mut() = samples;
        let mut roots: BTreeMap<&str, RootParts> = BTreeMap::new();
        for inst in instances {
            roots
                .entry(inst.info.root.as_str())
                .or_default()
                .0
                .push(inst);
        }
        for (name, e) in elided {
            roots
                .entry(e.root.as_str())
                .or_default()
                .2
                .push((name.as_str(), e));
        }
        for (&name, &root) in &linked {
            roots.entry(root).or_default().1.push(name);
        }
        roots
            .into_iter()
            .map(|(root, (instances, linked, elided))| {
                Ok(RootFiles {
                    name: file_name(root),
                    header: self
                        .header(archive, root, &instances, &linked, &elided)?,
                    source: if instances.is_empty() {
                        None
                    } else {
                        Some(self.source(archive, root, &instances, &owners)?)
                    },
                })
            })
            .collect()
    }

    /// A root's header: an extern declaration of each of its samples, and
    /// of the other data in it that samples point to, as bytes.
    fn header(
        &self,
        archive: &str,
        root: &str,
        instances: &[&Instance],
        linked: &[&str],
        elided: &[(&str, &Elided)],
    ) -> Result<String> {
        let guard = format!("DAT_{}_H", file_name(root).to_uppercase());
        let mut out = format!(
            concat!(
                "/**\n",
                " * @file\n",
                " * The samples of `{root}` in `{archive}`, and the data they ",
                "point to.\n",
                " * Generated by `melee-dat samples codegen`.\n",
                " */\n\n",
                "#ifndef {guard}\n",
                "#define {guard}\n\n",
                "#include \"../../macros.h\"\n\n",
                "#include <Runtime/platform.h>\n",
                "#include <placeholder.h>\n",
            ),
            root = root,
            archive = archive,
            guard = guard,
        );
        let headers: BTreeSet<&str> = instances
            .iter()
            .map(|i| i.info.header.as_str())
            .chain(elided.iter().filter_map(|(_, e)| Some(&*e.ty.as_ref()?.header)))
            .collect();
        for header in headers {
            writeln!(out, "#include <{header}>")?;
        }
        // Each kind of declaration as a Doxygen member group
        let mut group = |name: &str, doc: &str, lines: Vec<String>| {
            if lines.is_empty() {
                return Ok(());
            }
            write!(out, "\n/**\n * @name {name}\n * {doc}\n * @{{\n */\n")?;
            for line in lines {
                writeln!(out, "{line}")?;
            }
            writeln!(out, "/// @}}")
        };
        group(
            "Samples",
            &format!("Defined in `{}.c`.", file_name(root)),
            instances
                .iter()
                .map(|i| {
                    let storage = if i.info.public { "extern" } else { "LOCAL" };
                    format!("{storage} {} {};", i.info.type_name, i.info.symbol)
                })
                .collect(),
        )?;
        group(
            "Externs",
            concat!(
                "Data the program supplies by name when it loads the archive; ",
                "Melee's loader sets each to NULL (`lbArchive_InitializeDAT`).",
            ),
            linked
                .iter()
                .map(|n| format!("extern UNK_T {n};"))
                .collect(),
        )?;
        group(
            "Elided",
            "Data in this archive the samples point to that isn't written as C.",
            elided
                .iter()
                .map(|(n, e)| match &e.ty {
                    Some(ty) => format!("extern {} {n};", ty.type_name),
                    None => format!("extern UNK_T {n}; // {:#X} bytes", e.size),
                })
                .collect(),
        )?;
        writeln!(out, "\n#endif")?;
        Ok(out)
    }

    /// A root's source: its samples' definitions, after the headers of every
    /// root they point into.
    fn source(
        &self,
        archive: &str,
        root: &str,
        instances: &[&Instance],
        owners: &BTreeMap<&str, &str>,
    ) -> Result<String> {
        // What the pointers name, in the order they first do
        let mut referenced = Vec::new();
        let mut seen = BTreeSet::new();
        let mut defs = String::new();
        for inst in instances {
            for name in inst.relocs.values() {
                if seen.insert(name.as_str()) {
                    referenced.push(name.as_str());
                }
            }
            let info = inst.info;
            let die = self.die_of(&info.symbol, &info.lookup, &info.member)?;
            let mut init = String::new();
            self.value(&mut init, inst, die, 0, 0)?;
            let info = inst.info;
            let at = match info.archive {
                0 => format!("0x{:X}", info.offset),
                archive => format!("0x{archive:X}+0x{:X}", info.offset),
            };
            write!(defs, "/// `{archive}` at {at}.")?;
            if !info.variant.is_empty() {
                write!(
                    defs,
                    " Its unions' members: {}.",
                    info.variant.join(", ")
                )?;
            }
            defs.push('\n');
            let storage = if info.public { "" } else { "LOCAL " };
            writeln!(
                defs,
                "{storage}{} {} = {init};\n",
                info.type_name, info.symbol
            )?;
        }
        let mut out = format!(
            "/**\n * @file\n \
             * The samples of `{root}` in `{archive}`.\n \
             * Generated by `melee-dat samples codegen`.\n */\n\n"
        );
        // This root's declarations, then those of every other root it
        // points into
        let mut roots = vec![root];
        for name in referenced {
            let owner = owners
                .get(name)
                .with_context(|| format!("no root declares {name}"))?;
            if !roots.contains(owner) {
                roots.push(owner);
            }
        }
        roots[1..].sort_unstable();
        for root in roots {
            writeln!(out, "#include \"{}.h\"", file_name(root))?;
        }
        out.push('\n');
        out.push_str(&defs);
        Ok(out)
    }

    /// A sample's type, looked up by name; for a union object, the member
    /// its tag chose.
    fn die_of(
        &self,
        symbol: &str,
        lookup: &str,
        member: &Option<String>,
    ) -> Result<DieId> {
        let record = self
            .canonical
            .lookup(self.graph, lookup)
            .into_iter()
            .map(|die| self.resolve(die))
            .find(|die| {
                matches!(
                    self.graph.types[die].kind,
                    TypeKind::Record {
                        declaration: false,
                        ..
                    }
                )
            });
        let Some(record) = record else {
            bail!("{symbol}: no type `{lookup}`");
        };
        let Some(member) = member else {
            return Ok(record);
        };
        let TypeKind::Record { members, .. } = &self.graph.types[&record].kind
        else {
            unreachable!()
        };
        members
            .iter()
            .find(|m| m.name.is_some_and(|n| self.graph.str(n) == member))
            .and_then(|m| m.ty)
            .with_context(|| format!("{symbol}: no member `{member}`"))
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

    fn size(&self, die: DieId) -> u64 {
        self.canonical
            .byte_size(self.graph, self.resolve(die))
            .unwrap_or(0)
    }

    /// `.name = ` for a member, or nothing for an anonymous one, which
    /// then initializes the next member in order.
    fn designator(&self, member: &Member) -> String {
        member
            .name
            .map_or(String::new(), |n| format!(".{} = ", self.graph.str(n)))
    }

    /// The initializer for a value of type `die` at `offset`.
    fn value(
        &self,
        out: &mut String,
        inst: &Instance,
        die: DieId,
        offset: u32,
        depth: usize,
    ) -> Result<()> {
        if depth > 32 {
            bail!("{}: type nests too deep", inst.info.symbol);
        }
        let spelled = die;
        let die = self.resolve(die);
        let size = self.size(die);
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
                    // Unnamed bitfields are padding; a flexible array has
                    // no size and no initializer
                    let bitfield = member.bit_size.is_some();
                    if (bitfield && member.name.is_none())
                        || (!bitfield && self.size(ty) == 0)
                    {
                        continue;
                    }
                    if !first {
                        out.push_str(", ");
                    }
                    first = false;
                    out.push_str(&self.designator(member));
                    if let Some(bits) = member.bit_size {
                        let start = member
                            .bit_offset
                            .unwrap_or(member.offset.unwrap_or(0) * 8);
                        let value = bits_at(inst.bytes, offset, start, bits);
                        let negative = self.signed(ty)
                            && bits < 64
                            && value >> (bits - 1) & 1 == 1;
                        let value = match negative {
                            true => value as i64 - (1i64 << bits),
                            false => value as i64,
                        };
                        write!(out, "{value}")?;
                        continue;
                    }
                    let at = offset + member.offset.unwrap_or(0) as u32;
                    self.value(out, inst, ty, at, depth + 1)?;
                }
                // A trailing comma lays the sample's members out one per
                // line when the C is formatted. clang-format leaves an
                // initializer alone if a nested one has one too
                if first {
                    out.push('0');
                } else if depth == 0 {
                    out.push(',');
                }
                out.push('}');
            }
            TypeKind::Record {
                union: true,
                members,
                ..
            } => {
                // The member its tag chose; else the largest, which holds
                // every byte
                let union = self.renderer.declare(Some(die), "");
                let chosen = inst
                    .info
                    .choices
                    .iter()
                    .find(|c| c.offset == offset && c.union == union)
                    .and_then(|c| members.get(c.member));
                let largest = members
                    .iter()
                    .rev()
                    .max_by_key(|m| m.ty.map_or(0, |ty| self.size(ty)));
                let Some(member) = chosen.or(largest) else {
                    out.push_str("{0}");
                    return Ok(());
                };
                let Some(ty) = member.ty else {
                    out.push_str("{0}");
                    return Ok(());
                };
                out.push('{');
                out.push_str(&self.designator(member));
                self.value(out, inst, ty, offset, depth + 1)?;
                out.push('}');
            }
            TypeKind::Array { element, dims } => {
                let Some(element) = *element else {
                    out.push_str("{0}");
                    return Ok(());
                };
                let element_size = self.size(element);
                // Nested dimensions are laid out flat, which C accepts
                let count: u64 = dims.iter().map(|d| d.unwrap_or(0)).product();
                out.push('{');
                if count == 0 || element_size == 0 {
                    out.push('0');
                }
                for i in 0..count {
                    if i > 0 {
                        out.push_str(", ");
                    }
                    let at = offset + (i * element_size) as u32;
                    self.value(out, inst, element, at, depth + 1)?;
                }
                out.push('}');
            }
            TypeKind::Pointer { target: pointee } => {
                let cast = self.renderer.declare(Some(spelled), "");
                let value = word_at(inst.bytes, offset);
                if let Some(target) = inst.relocs.get(&offset) {
                    // A sample of the pointee's own type needs no cast
                    let pointee = pointee
                        .map(|p| self.resolve(p))
                        .and_then(|p| self.canonical.of(p));
                    let same = pointee.is_some()
                        && self.samples.borrow().get(target)
                            == pointee.as_ref();
                    match same {
                        true => write!(out, "&{target}")?,
                        false => write!(out, "({cast}) &{target}")?,
                    }
                } else if value == 0 {
                    out.push_str("NULL");
                } else {
                    write!(out, "({cast}) 0x{value:X}")?;
                }
            }
            // A relocated word under a scalar is written as its raw value:
            // the same bytes without the relocation, so objdiff shows that
            // the field should be a pointer
            TypeKind::Base { encoding } => {
                let bytes = &inst.bytes
                    [offset as usize..(offset as u64 + size) as usize];
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
                let bytes = &inst.bytes
                    [offset as usize..(offset as u64 + size) as usize];
                let value =
                    bytes.iter().fold(0u64, |acc, &b| acc << 8 | u64::from(b));
                integer(out, value, size, true)?;
            }
            _ => out.push('0'),
        }
        Ok(())
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

/// Bits `start..start + len` of the record at `offset`, counted from the
/// most significant bit of its first byte.
fn bits_at(bytes: &[u8], offset: u32, start: u64, len: u64) -> u64 {
    (start..start + len).fold(0, |acc, bit| {
        let byte = bytes[offset as usize + (bit / 8) as usize];
        acc << 1 | u64::from(byte >> (7 - bit % 8) & 1)
    })
}

fn word_at(bytes: &[u8], offset: u32) -> u32 {
    let at = offset as usize;
    u32::from_be_bytes(bytes[at..at + 4].try_into().unwrap())
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
    fn identifiers() {
        assert!(is_identifier("ftDataMario"));
        assert!(is_identifier("_x1"));
        assert!(!is_identifier("1x"));
        assert!(!is_identifier("a-b"));
        assert!(!is_identifier(""));
    }

    #[test]
    fn path_segments() {
        assert_eq!(
            segments("ftDataMario.x48_items->[4].x8->child->"),
            ["ftDataMario", "x48_items_4", "x8", "child"]
        );
        assert_eq!(segments("a->[1][3]"), ["a_1_3"]);
        assert_eq!(segments("a.script+0x1C->next->"), ["a", "script", "next"]);
    }

    #[test]
    fn names() {
        let path = Some("ftDataMario.x1C->[4].x8->child->");
        assert_eq!(name_of(path, None, 0, 0x1A0), "child_x1A0");
        assert_eq!(
            name_of(path, Some("ftDataMario"), 0, 0x1A0),
            "ftDataMario_child_x1A0"
        );
        assert_eq!(name_of(Some("itemdata->[3]"), None, 0, 0x10), "x10");
        assert_eq!(name_of(Some("a.x1C->[4]"), None, 0, 0x10), "x1C_4_x10");
        assert_eq!(name_of(None, Some("map_head"), 0, 0x10), "map_head_x10");
        assert_eq!(name_of(path, None, 0x2000, 0x1A0), "child_x2000_1A0");
    }
}
