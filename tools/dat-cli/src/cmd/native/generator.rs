//! The schema's contents: every type the archives' roots lead to, one per
//! canonical type, with how C spells it natively, and every archive's
//! roots.

use super::super::project::Project;
use anyhow::{Context, Result};
use melee_dat::{
    config::gather_files,
    dwarf::{
        DieId, TypeKind,
        annotation::{DatTag, Script},
        canonical::CanonId,
        expr::Expr,
    },
    hsd::Archive,
    symbols::Count,
};
use std::{
    collections::{BTreeSet, HashMap},
    fs,
};

/// No type: index 0 of the schema's types.
pub const NONE: i32 = 0;

/// The library's `DatKind`.
#[derive(Default, Clone, Copy, PartialEq, Eq)]
pub enum Kind {
    #[default]
    Void,
    Int,
    Float,
    Pointer,
    Struct,
    Union,
    Array,
    Typedef,
    Qualifier,
}

impl Kind {
    pub fn c(self) -> &'static str {
        match self {
            Kind::Void => "DAT_KIND_VOID",
            Kind::Int => "DAT_KIND_INT",
            Kind::Float => "DAT_KIND_FLOAT",
            Kind::Pointer => "DAT_KIND_POINTER",
            Kind::Struct => "DAT_KIND_STRUCT",
            Kind::Union => "DAT_KIND_UNION",
            Kind::Array => "DAT_KIND_ARRAY",
            Kind::Typedef => "DAT_KIND_TYPEDEF",
            Kind::Qualifier => "DAT_KIND_QUALIFIER",
        }
    }
}

#[derive(Default)]
pub struct TypeRow {
    pub die: Option<DieId>,
    /// The name traces print.
    pub name: String,
    pub id: u32,
    pub kind: Kind,
    pub is_signed: bool,
    pub raw: bool,
    pub blob: bool,
    pub has_pointers: bool,
    pub has_extent: bool,
    pub unbounded: bool,
    pub size: u64,
    pub native_size: String,
    pub target: i32,
    pub resolved: i32,
    pub count: u64,
    pub members: Vec<MemberRow>,
    pub terminator: Option<Expr>,
    /// How many elements the terminator takes.
    pub terminator_length: u64,
    /// Pointer typedefs: `DAT_COUNT`.
    pub count_tag: Option<Expr>,
    pub type_tag: i32,
    /// Pointer typedefs: `DAT_SCRIPT` or `DAT_BYTE_SCRIPT`.
    pub script: Option<ScriptRow>,
    /// The headers its native spellings need.
    pub headers: BTreeSet<String>,
}

/// Where C puts a member natively.
pub enum Place {
    /// Its own field of the record: `offsetof` and `sizeof` of it.
    Field { record: String, field: String },
    /// An anonymous member, at the first member inside it, or one without
    /// a bound, as big as one element.
    At { offset: String, size: String },
    /// A bitfield, through accessors of the record's field.
    Bits { record: String, field: String },
    /// Nowhere C can name.
    Unplaced,
}

pub struct MemberRow {
    pub name: Option<String>,
    pub ty: i32,
    pub offset: Option<u64>,
    pub bit_offset: u64,
    pub bit_size: u64,
    pub extent: bool,
    pub place: Place,
    pub count: Option<Expr>,
    pub terminator: Option<Expr>,
    /// How many elements the terminator takes.
    pub terminator_length: u64,
    pub cond: Option<Expr>,
    pub type_tag: i32,
    pub script: Option<ScriptRow>,
    pub binds: Vec<(String, Expr)>,
    /// The annotations with expressions, as written.
    pub annotations: Vec<String>,
}

pub enum ScriptRow {
    /// A table in the code, by its name, and its bytes.
    Table(String, Vec<u8>),
    Length(Expr),
    /// A byte-script command-length expression.
    Bytes(Expr),
}

pub struct RootRow {
    pub name: String,
    pub alias: bool,
    pub address: u32,
    pub ty: i32,
    pub count: Count,
    /// `script:`, for an alias that is a command script.
    pub script: Option<ScriptRow>,
    pub binds: Vec<(String, u64)>,
}

pub struct FileRow {
    pub file: String,
    pub archive: usize,
    pub roots: Vec<RootRow>,
}

/// What names an anonymous record or enum.
struct Owner {
    /// How C spells it.
    spelling: String,
    /// The header declaring what names it.
    header: Option<String>,
    /// A name for it: the typedef's, or the record's and member's.
    name: String,
}

/// Builds the rows, one type per canonical type.
pub struct Generator<'a> {
    pub project: &'a Project,
    index: HashMap<CanonId, i32>,
    /// By index; the first is no type.
    pub types: Vec<TypeRow>,
    /// Each type's members, filled in once every type is listed.
    pending: Vec<(i32, DieId)>,
    /// How C spells anonymous types, by the typedef or member that has
    /// one.
    owners: HashMap<CanonId, Owner>,
    /// The headers noted since the last `take_headers`.
    noted: BTreeSet<String>,
    /// Members whose native place C can't name.
    pub unplaced: BTreeSet<String>,
    /// Named types a `.c` file declares, which no header can provide.
    pub unhoisted: BTreeSet<String>,
}

impl<'a> Generator<'a> {
    pub fn new(project: &'a Project) -> Self {
        let mut generator = Generator {
            project,
            index: HashMap::new(),
            types: vec![TypeRow::default()],
            pending: Vec::new(),
            owners: HashMap::new(),
            noted: BTreeSet::new(),
            unplaced: BTreeSet::new(),
            unhoisted: BTreeSet::new(),
        };
        generator.find_owners();
        generator
    }

    pub fn str(&self, s: melee_dat::dwarf::Str) -> &'a str {
        self.project.graph.str(s)
    }

    pub fn ty(&self, die: DieId) -> &'a melee_dat::dwarf::Type {
        &self.project.graph.types[&die]
    }

    /// The walker's `resolve`: through typedefs and qualifiers, and from
    /// declarations to their definitions.
    pub fn resolve(&self, mut die: DieId) -> Option<DieId> {
        let canonical = &self.project.canonical;
        loop {
            match &self.project.graph.types.get(&die)?.kind {
                TypeKind::Typedef { target }
                | TypeKind::Const { target }
                | TypeKind::Volatile { target }
                | TypeKind::Restrict { target } => die = (*target)?,
                TypeKind::Record {
                    declaration: true, ..
                } => {
                    let id = canonical.of(die)?;
                    let definition =
                        canonical.definition(&self.project.graph, id)?;
                    return Some(canonical.get(definition).rep);
                }
                _ => return Some(die),
            }
        }
    }

    fn tags(
        &self,
        annotations: &[melee_dat::dwarf::Annotation],
    ) -> Vec<DatTag> {
        annotations
            .iter()
            .filter_map(|a| DatTag::parse(self.str(a.value?)))
            .collect()
    }

    /// The header declaring a named type, or the one declaring what names
    /// an anonymous one.
    fn spelling_header(&self, die: DieId) -> Option<String> {
        let ty = self.ty(die);
        match ty.name {
            Some(_) if ty.scope.is_none() => header(self.str(ty.decl_file?)),
            Some(_) => None,
            None => self
                .owners
                .get(&self.project.canonical.of(die)?)?
                .header
                .clone(),
        }
    }

    /// How C spells anonymous records and enums: by the typedef naming
    /// them, else through the member of a type C can spell that has one.
    fn find_owners(&mut self) {
        let graph = &self.project.graph;
        let canonical = &self.project.canonical;
        for ty in graph.types.values() {
            if let (Some(name), None, TypeKind::Typedef { target: Some(t) }) =
                (ty.name, ty.scope, &ty.kind)
                && let Some(id) = canonical.of(*t)
                && self.is_anonymous(*t)
            {
                let header = ty.decl_file.and_then(|f| header(graph.str(f)));
                self.owners.entry(id).or_insert_with(|| Owner {
                    spelling: graph.str(name).to_owned(),
                    header,
                    name: graph.str(name).to_owned(),
                });
            }
        }
        let mut changed = true;
        while changed {
            changed = false;
            for canon in &canonical.types {
                let TypeKind::Record { members, .. } =
                    &graph.types[&canon.rep].kind
                else {
                    continue;
                };
                let Some(parent) = self.spell(canon.rep) else {
                    continue;
                };
                let parent_header = self.spelling_header(canon.rep);
                let parent_name = self.name_of(canon.rep);
                for member in members {
                    let (Some(name), Some(mut ty)) = (member.name, member.ty)
                    else {
                        continue;
                    };
                    let mut access =
                        format!("(({parent}*)0)->{}", graph.str(name));
                    let mut dereferenced = false;
                    // Through arrays and pointers to the anonymous type
                    loop {
                        match &graph.types[&ty].kind {
                            TypeKind::Array {
                                element: Some(e),
                                dims,
                            } => {
                                if dereferenced {
                                    access = format!("({access})");
                                    dereferenced = false;
                                }
                                for _ in dims {
                                    access.push_str("[0]");
                                }
                                ty = *e;
                            }
                            TypeKind::Pointer { target: Some(t) } => {
                                access = format!("*{access}");
                                dereferenced = true;
                                ty = *t;
                            }
                            TypeKind::Const { target: Some(t) }
                            | TypeKind::Volatile { target: Some(t) } => {
                                ty = *t
                            }
                            _ => break,
                        }
                    }
                    if !self.is_anonymous(ty) {
                        continue;
                    }
                    let Some(id) = canonical.of(ty) else { continue };
                    if let std::collections::hash_map::Entry::Vacant(e) =
                        self.owners.entry(id)
                    {
                        e.insert(Owner {
                            spelling: format!("__typeof__({access})"),
                            header: parent_header.clone(),
                            name: format!("{parent_name}_{}", graph.str(name)),
                        });
                        changed = true;
                    }
                }
            }
        }
    }

    /// A record's or enum's name, else its owner's name for it.
    pub fn name_of(&self, die: DieId) -> String {
        let ty = self.ty(die);
        match ty.name {
            Some(name) => self.str(name).to_owned(),
            None => self
                .project
                .canonical
                .of(die)
                .and_then(|id| self.owners.get(&id))
                .map_or_else(|| "anonymous".to_owned(), |o| o.name.clone()),
        }
    }

    fn is_anonymous(&self, die: DieId) -> bool {
        let ty = self.ty(die);
        ty.name.is_none()
            && matches!(
                ty.kind,
                TypeKind::Record { .. } | TypeKind::Enum { .. }
            )
    }

    /// The C spelling of a type, where C can name it.
    pub fn spell(&self, die: DieId) -> Option<String> {
        let ty = self.ty(die);
        match &ty.kind {
            TypeKind::Base { .. } => Some(self.str(ty.name?).to_owned()),
            TypeKind::Typedef { target } if ty.scope.is_none() => {
                match self.includable(die) {
                    true => Some(self.str(ty.name?).to_owned()),
                    // The toolchain's own, e.g. newlib's `__uintptr_t`: the host
                    // has its own, which may differ, so by what it names
                    false => self.spell((*target)?),
                }
            }
            TypeKind::Record { union, .. } => match ty.name {
                Some(name) if ty.scope.is_none() => Some(format!(
                    "{} {}",
                    if *union { "union" } else { "struct" },
                    self.str(name)
                )),
                Some(_) => None,
                None => self
                    .owners
                    .get(&self.project.canonical.of(die)?)
                    .map(|owner| owner.spelling.clone()),
            },
            TypeKind::Enum { .. } => match ty.name {
                Some(name) if ty.scope.is_none() => {
                    Some(format!("enum {}", self.str(name)))
                }
                Some(_) => None,
                None => self
                    .owners
                    .get(&self.project.canonical.of(die)?)
                    .map(|owner| owner.spelling.clone()),
            },
            TypeKind::Const { target } | TypeKind::Volatile { target } => {
                self.spell((*target)?)
            }
            TypeKind::Pointer { .. } => Some("void*".to_owned()),
            _ => None,
        }
    }

    /// Whether the schema can include what declares a named type: a header
    /// of the game's, not the toolchain's or a source file.
    fn includable(&self, die: DieId) -> bool {
        self.ty(die)
            .decl_file
            .is_some_and(|f| header(self.str(f)).is_some())
    }

    /// Whether a type is an array with a dimension without a bound.
    fn unbounded(&self, die: DieId) -> bool {
        let mut die = die;
        loop {
            match &self.ty(die).kind {
                TypeKind::Typedef { target: Some(t) }
                | TypeKind::Const { target: Some(t) }
                | TypeKind::Volatile { target: Some(t) } => die = *t,
                TypeKind::Array { dims, .. } => {
                    return dims.iter().any(Option::is_none);
                }
                _ => return false,
            }
        }
    }

    /// Note the header C needs to spell a type, which the TU it is in
    /// includes.
    fn note_header(&mut self, die: DieId) {
        let ty = self.ty(die);
        if ty.name.is_some()
            && ty.scope.is_none()
            && let Some(file) = ty.decl_file.map(|f| self.str(f))
            && header(file).is_none()
            && file.ends_with(".c")
        {
            self.unhoisted
                .insert(format!("{} ({file})", self.str(ty.name.unwrap())));
        }
        if let Some(header) = self.spelling_header(die) {
            self.noted.insert(header);
        }
    }

    fn take_headers(&mut self) -> BTreeSet<String> {
        std::mem::take(&mut self.noted)
    }

    /// `sizeof` the type natively, as a C constant expression; `0` where C
    /// can't name it.
    fn native_size(&mut self, die: DieId) -> String {
        let ty = self.ty(die);
        match &ty.kind {
            // An array without a bound has no `sizeof`: one element, as the
            // walker counts it
            TypeKind::Typedef { target }
                if ty.scope.is_some()
                    || ty.name.is_none()
                    || !self.includable(die)
                    || self.unbounded(die) =>
            {
                match target {
                    Some(t) => self.native_size(*t),
                    None => "0".into(),
                }
            }
            TypeKind::Const { target }
            | TypeKind::Volatile { target }
            | TypeKind::Restrict { target } => match target {
                Some(t) => self.native_size(*t),
                None => "0".into(),
            },
            TypeKind::Array { element, dims } => {
                let count: u64 = dims.iter().map(|d| d.unwrap_or(1)).product();
                match element {
                    // Keep sizeof on the left so multiplication uses its
                    // unsigned size_t width, including in nested arrays.
                    Some(e) => format!("{} * {count}", self.native_size(*e)),
                    None => "0".into(),
                }
            }
            TypeKind::Record {
                declaration: true, ..
            } => match self.resolve(die) {
                Some(d) if d != die => self.native_size(d),
                _ => "0".into(),
            },
            TypeKind::Unspecified | TypeKind::Subroutine { .. } => "0".into(),
            _ => match self.spell(die) {
                Some(spelling) => {
                    self.note_header(die);
                    // A typedef of a struct another header defines
                    if let Some(definition) = self.resolve(die)
                        && definition != die
                    {
                        self.note_header(definition);
                    }
                    format!("sizeof({spelling})")
                }
                None => "0".into(),
            },
        }
    }

    /// The index of a type, listing it and what it refers to.
    pub fn type_index(&mut self, die: DieId) -> i32 {
        let canonical = &self.project.canonical;
        let graph = &self.project.graph;
        let Some(id) = canonical.of(die) else {
            return NONE;
        };
        // A declaration is its definition
        if let TypeKind::Record {
            declaration: true, ..
        } = graph.types[&die].kind
            && let Some(definition) = canonical.definition(graph, id)
            && definition != id
        {
            return self.type_index(canonical.get(definition).rep);
        }
        if let Some(&index) = self.index.get(&id) {
            return index;
        }
        let die = canonical.get(id).rep;
        let index = self.types.len() as i32;
        self.index.insert(id, index);
        self.types.push(TypeRow::default());
        let ty = self.ty(die);
        let mut row = TypeRow {
            die: Some(die),
            name: canonical
                .get(id)
                .display
                .clone()
                .unwrap_or_else(|| "?".into()),
            id: id.0,
            size: canonical.byte_size(graph, die).unwrap_or(0),
            ..TypeRow::default()
        };
        row.raw = self.is_raw(die);
        let tags = self.tags(&ty.annotations);
        row.blob = tags.contains(&DatTag::Blob);
        match &ty.kind {
            TypeKind::Base { encoding } => {
                row.kind = match *encoding {
                    e if e == gimli::DW_ATE_float.0 => Kind::Float,
                    _ => Kind::Int,
                };
                row.is_signed = *encoding == gimli::DW_ATE_signed.0
                    || *encoding == gimli::DW_ATE_signed_char.0;
            }
            TypeKind::Enum {
                underlying,
                enumerators,
            } => {
                row.kind = Kind::Int;
                row.is_signed = match underlying.map(|u| &self.ty(u).kind) {
                    Some(TypeKind::Base { encoding }) => {
                        *encoding == gimli::DW_ATE_signed.0
                            || *encoding == gimli::DW_ATE_signed_char.0
                    }
                    _ => enumerators.iter().any(|e| e.value < 0),
                };
            }
            TypeKind::Pointer { target } => {
                row.kind = Kind::Pointer;
                row.target = target.map_or(NONE, |t| self.type_index(t));
            }
            TypeKind::Typedef { target } => {
                row.kind = Kind::Typedef;
                row.target = target.map_or(NONE, |t| self.type_index(t));
                for tag in &tags {
                    match tag {
                        DatTag::Terminated(value, length)
                            if row.terminator.is_none() =>
                        {
                            row.terminator = Some(value.clone());
                            row.terminator_length = *length;
                        }
                        DatTag::Count(count) if row.count_tag.is_none() => {
                            row.count_tag = Some(count.clone());
                        }
                        DatTag::Script(script) if row.script.is_none() => {
                            row.script = Some(self.script(script.clone()));
                        }
                        DatTag::Type(name) if row.type_tag == NONE => {
                            // As the walker's `typedef_type`: the type as
                            // named, unresolved
                            let found = canonical
                                .lookup(graph, name)
                                .into_iter()
                                .find(|&d| self.resolve(d).is_some());
                            row.type_tag =
                                found.map_or(NONE, |d| self.type_index(d));
                        }
                        _ => {}
                    }
                }
            }
            TypeKind::Const { target }
            | TypeKind::Volatile { target }
            | TypeKind::Restrict { target } => {
                row.kind = Kind::Qualifier;
                row.target = target.map_or(NONE, |t| self.type_index(t));
            }
            TypeKind::Array { element, dims } => {
                row.kind = Kind::Array;
                row.target = element.map_or(NONE, |e| self.type_index(e));
                row.count = dims.iter().map(|d| d.unwrap_or(1)).product();
                row.unbounded = dims.iter().any(Option::is_none);
            }
            TypeKind::Record {
                union,
                declaration: false,
                ..
            } => {
                row.kind = if *union { Kind::Union } else { Kind::Struct };
                self.pending.push((index, die));
            }
            TypeKind::Record { .. }
            | TypeKind::Unspecified
            | TypeKind::Subroutine { .. } => {
                row.kind = Kind::Void;
            }
        }
        let outer = self.take_headers();
        row.native_size = match row.kind {
            Kind::Void => "0".into(),
            _ => self.native_size(die),
        };
        row.headers = std::mem::replace(&mut self.noted, outer);
        row.resolved = match self.resolve(die) {
            Some(r) if r == die => index,
            Some(r) => self.type_index(r),
            None => NONE,
        };
        if matches!(row.kind, Kind::Struct | Kind::Union) {
            row.has_pointers = self.has_pointers(die);
            row.has_extent = self.has_extent(die);
        } else if let Some(r) = self.resolve(die) {
            row.has_pointers = self.has_pointers(r);
            row.has_extent = self.has_extent(r);
        }
        self.types[index as usize] = row;
        index
    }

    /// The walker's `is_raw`.
    fn is_raw(&self, die: DieId) -> bool {
        let Some(ty) = self.project.graph.types.get(&die) else {
            return false;
        };
        if self.tags(&ty.annotations).contains(&DatTag::Blob) {
            return false;
        }
        match ty.kind {
            TypeKind::Typedef { target }
            | TypeKind::Const { target }
            | TypeKind::Volatile { target }
            | TypeKind::Array {
                element: target, ..
            } => target.is_some_and(|t| self.is_raw(t)),
            TypeKind::Base { encoding } => {
                encoding == gimli::DW_ATE_unsigned_char.0
            }
            _ => false,
        }
    }

    /// The walker's `has_pointers`.
    fn has_pointers(&self, die: DieId) -> bool {
        let Some(die) = self.resolve(die) else {
            return false;
        };
        match &self.ty(die).kind {
            TypeKind::Pointer { .. } => true,
            TypeKind::Record { members, .. } => members
                .iter()
                .any(|m| m.ty.is_some_and(|ty| self.has_pointers(ty))),
            TypeKind::Array { element, .. } => {
                element.is_some_and(|e| self.has_pointers(e))
            }
            _ => false,
        }
    }

    /// The walker's `has_extent`.
    fn has_extent(&self, die: DieId) -> bool {
        match &self.ty(die).kind {
            TypeKind::Record { members, .. } => {
                members.last().is_some_and(|m| {
                    self.tags(&m.annotations).contains(&DatTag::Extent)
                })
            }
            _ => false,
        }
    }

    /// List each record's members, until no type is left without them.
    pub fn fill_members(&mut self) {
        while let Some((index, die)) = self.pending.pop() {
            let TypeKind::Record { members, .. } = &self.ty(die).kind else {
                continue;
            };
            let outer = self.take_headers();
            let parent = self.spell(die);
            if parent.is_some() {
                self.note_header(die);
            }
            let mut rows = Vec::new();
            for (position, member) in members.iter().enumerate() {
                rows.push(self.member(
                    index,
                    parent.as_deref(),
                    position,
                    member,
                ));
            }
            let headers = std::mem::replace(&mut self.noted, outer);
            let row = &mut self.types[index as usize];
            row.members = rows;
            row.headers.extend(headers);
        }
    }

    fn member(
        &mut self,
        record: i32,
        parent: Option<&str>,
        position: usize,
        member: &melee_dat::dwarf::Member,
    ) -> MemberRow {
        let name = member.name.map(|n| self.str(n));
        // Listing the type notes its own headers, not this record's
        let noted = self.take_headers();
        let ty = member.ty.map_or(NONE, |t| self.type_index(t));
        self.noted = noted;
        let tags = self.tags(&member.annotations);
        let annotations = member
            .annotations
            .iter()
            .filter_map(|a| a.value.map(|v| self.str(v)))
            .filter(|v| {
                matches!(
                    DatTag::parse(v),
                    Some(
                        DatTag::Count(_)
                            | DatTag::Terminated(..)
                            | DatTag::If(_)
                            | DatTag::Bind(..)
                            | DatTag::Script(_)
                    )
                )
            })
            .map(str::to_owned)
            .collect();
        let mut row = MemberRow {
            name: name.map(str::to_owned),
            ty,
            offset: member.offset,
            bit_offset: 0,
            bit_size: 0,
            extent: tags.contains(&DatTag::Extent),
            place: Place::Unplaced,
            count: None,
            terminator: None,
            terminator_length: 1,
            cond: None,
            type_tag: NONE,
            script: None,
            binds: Vec::new(),
            annotations,
        };
        if let Some(bits) = member.bit_size {
            row.bit_size = bits;
            row.bit_offset =
                member.bit_offset.unwrap_or(member.offset.unwrap_or(0) * 8);
            match (parent, name) {
                (Some(parent), Some(name)) => {
                    row.place = Place::Bits {
                        record: parent.to_owned(),
                        field: name.to_owned(),
                    };
                }
                (None, Some(name)) => {
                    let record = self.types[record as usize].name.clone();
                    self.unplaced.insert(format!("{record}::{name}"));
                }
                _ => {}
            }
        } else {
            // Where C puts it: by its name, or for an anonymous member, by
            // the first member inside it, at its start
            let path = match name {
                Some(name) => Some(name.to_owned()),
                None => member.ty.and_then(|t| self.first_leaf(t)),
            };
            match (parent, path) {
                (Some(parent), Some(path)) => {
                    let unbounded =
                        member.ty.is_some_and(|t| self.unbounded(t));
                    row.place = match name {
                        Some(name) if !unbounded => Place::Field {
                            record: parent.to_owned(),
                            field: name.to_owned(),
                        },
                        _ => Place::At {
                            offset: format!("offsetof({parent}, {path})"),
                            size: member
                                .ty
                                .map_or("0".into(), |t| self.native_size(t)),
                        },
                    };
                }
                _ => {
                    let record = self.types[record as usize].name.clone();
                    self.unplaced.insert(format!(
                        "{record}::{}",
                        name.map_or_else(
                            || format!("@{position}"),
                            str::to_owned
                        )
                    ));
                }
            }
        }
        for tag in tags {
            match tag {
                DatTag::Count(value) if row.count.is_none() => {
                    row.count = Some(value);
                }
                DatTag::Terminated(value, length) if row.terminator.is_none() => {
                    row.terminator = Some(value);
                    row.terminator_length = length;
                }
                DatTag::If(value) if row.cond.is_none() => {
                    row.cond = Some(value);
                }
                DatTag::Type(name) if row.type_tag == NONE => {
                    // As the walker's `declared_type`: resolved
                    let found = self
                        .project
                        .canonical
                        .lookup(&self.project.graph, &name)
                        .into_iter()
                        .find_map(|d| self.resolve(d));
                    let noted = self.take_headers();
                    row.type_tag = found.map_or(NONE, |d| self.type_index(d));
                    self.noted = noted;
                }
                DatTag::Script(script) if row.script.is_none() => {
                    row.script = Some(self.script(script));
                }
                DatTag::Bind(name, value) => row.binds.push((name, value)),
                _ => {}
            }
        }
        row
    }

    /// The name of the first member inside an anonymous member, through
    /// anonymous members: where C places it.
    fn first_leaf(&self, die: DieId) -> Option<String> {
        let die = self.resolve(die)?;
        let TypeKind::Record { members, .. } = &self.ty(die).kind else {
            return None;
        };
        let first = members.first()?;
        if first.bit_size.is_some() {
            return None;
        }
        match first.name {
            Some(name) => Some(self.str(name).to_owned()),
            None => self.first_leaf(first.ty?),
        }
    }

    fn script(&self, script: Script) -> ScriptRow {
        match script {
            Script::Table(table) => {
                let graph = &self.project.graph;
                let bytes = graph
                    .strings
                    .get(&table)
                    .and_then(|name| graph.globals.get(&name))
                    .and_then(|global| {
                        let size = global.ty.and_then(|ty| {
                            self.project.canonical.byte_size(graph, ty)
                        })?;
                        graph.bytes(global.address, size as usize)
                    })
                    .map(<[u8]>::to_vec)
                    .unwrap_or_default();
                ScriptRow::Table(table, bytes)
            }
            Script::Length(length) => ScriptRow::Length(length),
            Script::Bytes(length) => ScriptRow::Bytes(length),
        }
    }

    /// Each archive of each file with roots: the files' archives in order,
    /// publics then aliases, as `Project::walk` takes them.
    pub fn file_roots(&mut self) -> Result<Vec<FileRow>> {
        let project = self.project;
        let mut files = Vec::new();
        let mut paths = gather_files(&project.base, &project.include)?;
        paths.sort();
        for path in paths {
            let file = path
                .strip_prefix(&project.base)?
                .to_string_lossy()
                .into_owned();
            let bytes = fs::read(&path)?;
            let archives = Archive::parse_packed(&bytes)
                .with_context(|| format!("{}", path.display()))?;
            for (index, (at, archive)) in archives.iter().enumerate() {
                let mut roots = Vec::new();
                let mut seen = BTreeSet::new();
                for (name, _) in archive.named_publics() {
                    let name = String::from_utf8_lossy(name).into_owned();
                    if !seen.insert(name.clone()) {
                        continue;
                    }
                    let Some((die, count)) = project.root(&name, &file) else {
                        continue;
                    };
                    let binds = project
                        .root_bindings
                        .get(&name)
                        .cloned()
                        .unwrap_or_default();
                    roots.push(RootRow {
                        name,
                        alias: false,
                        address: 0,
                        ty: self.type_index(die),
                        count,
                        script: None,
                        binds,
                    });
                }
                for (address, entry) in project.aliases(&file, *at) {
                    let Some(ty) = &entry.ty else { continue };
                    roots.push(RootRow {
                        name: entry.name.clone(),
                        alias: true,
                        address,
                        ty: self.type_index(project.symbol_types[ty]),
                        count: entry.count.unwrap_or(Count::One),
                        script: entry.script().map(|s| self.script(s)),
                        binds: Vec::new(),
                    });
                }
                if !roots.is_empty() {
                    files.push(FileRow {
                        file: file.clone(),
                        archive: index,
                        roots,
                    });
                }
            }
        }
        // Listing the roots' types notes headers, which the types have
        // their own of
        self.noted.clear();
        Ok(files)
    }
}

/// The include path of a header from its DWARF path, e.g.
/// `/.../src/melee/ft/types.h` to `melee/ft/types.h`; `None` for the
/// toolchain's own (newlib's, the compiler's), which the host has its own of.
pub fn header(path: &str) -> Option<String> {
    if !path.ends_with(".h") {
        return None;
    }
    source(path)
}

/// A path of the game's sources from its DWARF path, as [`header`] does,
/// headers or not.
pub fn source(path: &str) -> Option<String> {
    if path.contains("newlib") || path.contains("/lib/clang/") {
        return None;
    }
    let at = ["/src/", "/include/"]
        .iter()
        .filter_map(|dir| path.rfind(dir).map(|at| at + dir.len()))
        .max()?;
    match &path[at..] {
        // The SDK's typedefs it declares again with annotations, for the
        // DWARF build only: natively, the SDK's own
        "dat_macros.h" => Some("dolphin/mtx.h".to_owned()),
        path => Some(path.to_owned()),
    }
}
