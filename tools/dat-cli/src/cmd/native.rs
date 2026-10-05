//! `native`: the tables of `native/`, the C library that reads archives into
//! the game's own types on any platform, and what it should reach.
//!
//! - `codegen`: the type, member, expression and root tables, as C, from
//!   the DWARF and `dat_symbols.txt`
//! - `expect`: what the walk reaches in each archive, in the form the
//!   library's `dat_trace` prints, for its end-to-end tests

use super::project::{Check, Project};
use anyhow::{Context, Result};
use globset::GlobSet;
use melee_dat::{
    config::gather_files,
    dwarf::{
        DieId, TypeKind,
        annotation::{DatTag, Script},
        canonical::CanonId,
        expr::{BinaryOp, Expr, UnaryOp},
    },
    hsd::Archive,
    symbols::Count,
    walk::{Issue, Walk},
};
use std::{
    collections::{BTreeMap, BTreeSet, HashMap},
    fmt::Write as _,
    fs,
    io::{self, Write},
    path::PathBuf,
};

#[derive(clap::Args)]
pub struct Args {
    #[command(subcommand)]
    command: Command,
}

#[derive(clap::Subcommand)]
enum Command {
    /// Write the library's tables for every type the archives' roots lead
    /// to, and every archive's roots
    Codegen(Codegen),

    /// Print what the walk reaches in each archive, as `dat_trace` does
    Expect(Expect),
}

#[derive(clap::Args)]
struct Codegen {
    #[command(flatten)]
    check: Check,
    /// The C source to write
    #[arg(long)]
    out: PathBuf,
    /// The header to write, declaring the schema and type indices
    #[arg(long)]
    header: PathBuf,
}

#[derive(clap::Args)]
struct Expect {
    #[command(flatten)]
    check: Check,
    /// Only these archives (globs on file names)
    #[arg(long)]
    only: Vec<String>,
}

pub fn run(Args { command }: Args) -> Result<()> {
    match command {
        Command::Codegen(args) => codegen(args),
        Command::Expect(args) => expect(args),
    }
}

// The library's `DatKind`, `DatOp`, `DatFunction` and `DatCount`
const KIND_VOID: u8 = 0;
const KIND_INT: u8 = 1;
const KIND_FLOAT: u8 = 2;
const KIND_POINTER: u8 = 3;
const KIND_STRUCT: u8 = 4;
const KIND_UNION: u8 = 5;
const KIND_ARRAY: u8 = 6;
const KIND_TYPEDEF: u8 = 7;
const KIND_QUALIFIER: u8 = 8;

const OP_INT: u8 = 0;
const OP_NAME: u8 = 1;
const OP_CALL: u8 = 2;
const OP_NOT: u8 = 3;
const OP_BITNOT: u8 = 4;
const OP_NEG: u8 = 5;
const OP_FAIL: u8 = 24;

/// How deep the walker evaluates macros within macros.
const MACRO_DEPTH: usize = 16;

const NONE: i32 = -1;

#[derive(Default, Clone)]
struct TypeRow {
    name: String,
    id: u32,
    kind: u8,
    is_signed: bool,
    raw: bool,
    blob: bool,
    has_pointers: bool,
    has_extent: bool,
    size: u64,
    native_size: String,
    target: i32,
    resolved: i32,
    count: u64,
    members: usize,
    nmembers: usize,
    terminator: i32,
    type_tag: i32,
}

struct MemberRow {
    name: i32,
    ty: i32,
    offset: u64,
    bit_offset: u64,
    bit_size: u64,
    has_offset: bool,
    extent: bool,
    native_offset: String,
    native_size: String,
    accessors: Option<usize>,
    count: i32,
    terminator: i32,
    cond: i32,
    type_tag: i32,
    script: i32,
    binds: usize,
    nbinds: usize,
}

struct ExprRow {
    op: u8,
    a: i32,
    b: i32,
    value: u64,
}

struct RootRow {
    name: String,
    alias: bool,
    address: u32,
    ty: i32,
    count_kind: u8,
    count: u64,
    binds: usize,
    nbinds: usize,
}

struct FileRow {
    file: String,
    archive: usize,
    roots: usize,
    nroots: usize,
}

/// Builds the tables, one type per canonical type.
struct Generator<'a> {
    project: &'a Project,
    index: HashMap<CanonId, i32>,
    types: Vec<TypeRow>,
    /// Each type's members, filled in once every type is listed, so that a
    /// type's members are contiguous.
    pending: Vec<(i32, DieId)>,
    members: Vec<MemberRow>,
    exprs: Vec<ExprRow>,
    args: Vec<i32>,
    binds: Vec<(i32, i32)>,
    scripts: Vec<(Option<Vec<u8>>, i32)>,
    names: Vec<String>,
    name_ids: HashMap<String, i32>,
    macro_nodes: HashMap<(String, usize), i32>,
    /// Bitfield accessors: the record's C type and the field's name.
    accessors: Vec<(String, String)>,
    /// How C spells anonymous types, by the typedef or member that has
    /// one.
    owners: HashMap<CanonId, String>,
    headers: BTreeSet<String>,
    /// Members whose native place C can't name.
    unplaced: BTreeSet<String>,
    /// Named types a `.c` file declares, which no header can provide.
    unhoisted: BTreeSet<String>,
}

impl<'a> Generator<'a> {
    fn new(project: &'a Project) -> Self {
        let mut generator = Generator {
            project,
            index: HashMap::new(),
            types: Vec::new(),
            pending: Vec::new(),
            members: Vec::new(),
            exprs: Vec::new(),
            args: Vec::new(),
            binds: Vec::new(),
            scripts: Vec::new(),
            names: Vec::new(),
            name_ids: HashMap::new(),
            macro_nodes: HashMap::new(),
            accessors: Vec::new(),
            owners: HashMap::new(),
            headers: BTreeSet::new(),
            unplaced: BTreeSet::new(),
            unhoisted: BTreeSet::new(),
        };
        generator.find_owners();
        generator
    }

    fn str(&self, s: melee_dat::dwarf::Str) -> &'a str {
        self.project.graph.str(s)
    }

    fn ty(&self, die: DieId) -> &'a melee_dat::dwarf::Type {
        &self.project.graph.types[&die]
    }

    /// The walker's `resolve`: through typedefs and qualifiers, and from
    /// declarations to their definitions.
    fn resolve(&self, mut die: DieId) -> Option<DieId> {
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

    fn name_id(&mut self, name: &str) -> i32 {
        if let Some(&id) = self.name_ids.get(name) {
            return id;
        }
        let id = self.names.len() as i32;
        self.names.push(name.to_owned());
        self.name_ids.insert(name.to_owned(), id);
        id
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
                self.owners
                    .entry(id)
                    .or_insert_with(|| graph.str(name).to_owned());
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
                for member in members {
                    let (Some(name), Some(mut ty)) = (member.name, member.ty)
                    else {
                        continue;
                    };
                    let mut access =
                        format!("((({parent}*)0)->{})", graph.str(name));
                    // Through arrays and pointers to the anonymous type
                    loop {
                        match &graph.types[&ty].kind {
                            TypeKind::Array {
                                element: Some(e),
                                dims,
                            } => {
                                for _ in dims {
                                    access.push_str("[0]");
                                }
                                ty = *e;
                            }
                            TypeKind::Pointer { target: Some(t) } => {
                                access = format!("(*{access})");
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
                        e.insert(format!("__typeof__({access})"));
                        changed = true;
                    }
                }
            }
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
    fn spell(&self, die: DieId) -> Option<String> {
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
                None => {
                    self.owners.get(&self.project.canonical.of(die)?).cloned()
                }
            },
            TypeKind::Enum { .. } => match ty.name {
                Some(name) if ty.scope.is_none() => {
                    Some(format!("enum {}", self.str(name)))
                }
                Some(_) => None,
                None => {
                    self.owners.get(&self.project.canonical.of(die)?).cloned()
                }
            },
            TypeKind::Const { target } | TypeKind::Volatile { target } => {
                self.spell((*target)?)
            }
            TypeKind::Pointer { .. } => Some("void*".to_owned()),
            _ => None,
        }
    }

    /// Whether the tables can include what declares a named type: a header
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

    /// The header declaring a named type, which the tables include.
    fn note_header(&mut self, die: DieId) {
        let ty = self.ty(die);
        if ty.name.is_none() || ty.scope.is_some() {
            return;
        }
        let Some(file) = ty.decl_file.map(|f| self.str(f)) else {
            return;
        };
        match header(file) {
            Some(header) => {
                self.headers.insert(header);
            }
            None if file.ends_with(".c") => {
                self.unhoisted.insert(format!(
                    "{} ({file})",
                    self.str(ty.name.unwrap())
                ));
            }
            None => {}
        }
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
                    Some(e) => format!("{count} * ({})", self.native_size(*e)),
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
                    format!("sizeof({spelling})")
                }
                None => "0".into(),
            },
        }
    }

    /// The table index of a type, listing it and what it refers to.
    fn type_index(&mut self, die: DieId) -> i32 {
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
            name: canonical
                .get(id)
                .display
                .clone()
                .unwrap_or_else(|| "?".into()),
            id: id.0,
            size: canonical.byte_size(graph, die).unwrap_or(0),
            target: NONE,
            resolved: NONE,
            terminator: NONE,
            type_tag: NONE,
            ..TypeRow::default()
        };
        row.raw = self.is_raw(die);
        let tags = self.tags(&ty.annotations);
        row.blob = tags.contains(&DatTag::Blob);
        match &ty.kind {
            TypeKind::Base { encoding } => {
                row.kind = match *encoding {
                    e if e == gimli::DW_ATE_float.0 => KIND_FLOAT,
                    _ => KIND_INT,
                };
                row.is_signed = *encoding == gimli::DW_ATE_signed.0
                    || *encoding == gimli::DW_ATE_signed_char.0;
            }
            TypeKind::Enum {
                underlying,
                enumerators,
            } => {
                row.kind = KIND_INT;
                row.is_signed = match underlying.map(|u| &self.ty(u).kind) {
                    Some(TypeKind::Base { encoding }) => {
                        *encoding == gimli::DW_ATE_signed.0
                            || *encoding == gimli::DW_ATE_signed_char.0
                    }
                    _ => enumerators.iter().any(|e| e.value < 0),
                };
            }
            TypeKind::Pointer { target } => {
                row.kind = KIND_POINTER;
                row.target = target.map_or(NONE, |t| self.type_index(t));
            }
            TypeKind::Typedef { target } => {
                row.kind = KIND_TYPEDEF;
                row.target = target.map_or(NONE, |t| self.type_index(t));
                for tag in &tags {
                    match tag {
                        DatTag::Terminated(value)
                            if row.terminator == NONE =>
                        {
                            row.terminator = self.expr(value, 0);
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
                row.kind = KIND_QUALIFIER;
                row.target = target.map_or(NONE, |t| self.type_index(t));
            }
            TypeKind::Array { element, dims } => {
                row.kind = KIND_ARRAY;
                row.target = element.map_or(NONE, |e| self.type_index(e));
                row.count = dims.iter().map(|d| d.unwrap_or(1)).product();
            }
            TypeKind::Record {
                union,
                declaration: false,
                ..
            } => {
                row.kind = if *union { KIND_UNION } else { KIND_STRUCT };
                self.pending.push((index, die));
            }
            TypeKind::Record { .. }
            | TypeKind::Unspecified
            | TypeKind::Subroutine { .. } => {
                row.kind = KIND_VOID;
            }
        }
        row.native_size = match row.kind {
            KIND_VOID => "0".into(),
            _ => self.native_size(die),
        };
        row.resolved = match self.resolve(die) {
            Some(r) if r == die => index,
            Some(r) => self.type_index(r),
            None => NONE,
        };
        if matches!(row.kind, KIND_STRUCT | KIND_UNION) {
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
    fn fill_members(&mut self) {
        while let Some((index, die)) = self.pending.pop() {
            let TypeKind::Record { members, .. } = &self.ty(die).kind else {
                continue;
            };
            let parent = self.spell(die);
            if parent.is_some() {
                self.note_header(die);
            }
            let mut rows = Vec::new();
            for (position, member) in members.iter().enumerate() {
                rows.push(self.member(
                    die,
                    parent.as_deref(),
                    position,
                    member,
                ));
            }
            let start = self.members.len();
            self.members.extend(rows);
            let row = &mut self.types[index as usize];
            row.members = start;
            row.nmembers = members.len();
        }
    }

    fn member(
        &mut self,
        record: DieId,
        parent: Option<&str>,
        position: usize,
        member: &melee_dat::dwarf::Member,
    ) -> MemberRow {
        let name = member.name.map(|n| self.str(n));
        let ty = member.ty.map_or(NONE, |t| self.type_index(t));
        let tags = self.tags(&member.annotations);
        let mut row = MemberRow {
            name: name.map_or(NONE, |n| self.name_id(n)),
            ty,
            offset: member.offset.unwrap_or(0),
            bit_offset: 0,
            bit_size: 0,
            has_offset: member.offset.is_some(),
            extent: tags.contains(&DatTag::Extent),
            native_offset: "0".into(),
            native_size: "0".into(),
            accessors: None,
            count: NONE,
            terminator: NONE,
            cond: NONE,
            type_tag: NONE,
            script: NONE,
            binds: self.binds.len(),
            nbinds: 0,
        };
        if let Some(bits) = member.bit_size {
            row.bit_size = bits;
            row.bit_offset =
                member.bit_offset.unwrap_or(member.offset.unwrap_or(0) * 8);
            match (parent, name) {
                (Some(parent), Some(name)) => {
                    row.accessors = Some(self.accessors.len());
                    self.accessors.push((parent.to_owned(), name.to_owned()));
                }
                (None, Some(name)) => {
                    let record = self.type_index(record);
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
                    row.native_offset = format!("offsetof({parent}, {path})");
                    let unbounded =
                        member.ty.is_some_and(|t| self.unbounded(t));
                    row.native_size = match name {
                        Some(name) if !unbounded => {
                            format!("sizeof((({parent}*)0)->{name})")
                        }
                        _ => member
                            .ty
                            .map_or("0".into(), |t| self.native_size(t)),
                    };
                }
                _ => {
                    let record = self.type_index(record);
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
                DatTag::Count(value) if row.count == NONE => {
                    row.count = self.expr(&value, 0);
                }
                DatTag::Terminated(value) if row.terminator == NONE => {
                    row.terminator = self.expr(&value, 0);
                }
                DatTag::If(value) if row.cond == NONE => {
                    row.cond = self.expr(&value, 0);
                }
                DatTag::Type(name) if row.type_tag == NONE => {
                    // As the walker's `declared_type`: resolved
                    let found = self
                        .project
                        .canonical
                        .lookup(&self.project.graph, &name)
                        .into_iter()
                        .find_map(|d| self.resolve(d));
                    row.type_tag = found.map_or(NONE, |d| self.type_index(d));
                }
                DatTag::Script(script) if row.script == NONE => {
                    row.script = self.script(&script);
                }
                DatTag::Bind(name, value) => {
                    let name = self.name_id(&name);
                    let value = self.expr(&value, 0);
                    self.binds.push((name, value));
                    row.nbinds += 1;
                }
                _ => {}
            }
        }
        // Binds pushed by nested types' members would interleave; members
        // are listed one record at a time, so they don't
        row.binds = self.binds.len() - row.nbinds;
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

    fn script(&mut self, script: &Script) -> i32 {
        let row = match script {
            Script::Table(table) => {
                let graph = &self.project.graph;
                let bytes = graph
                    .strings
                    .get(table)
                    .and_then(|name| graph.globals.get(&name))
                    .and_then(|global| {
                        let size = global.ty.and_then(|ty| {
                            self.project.canonical.byte_size(graph, ty)
                        })?;
                        graph.bytes(global.address, size as usize)
                    })
                    .map(<[u8]>::to_vec)
                    .unwrap_or_default();
                (Some(bytes), NONE)
            }
            Script::Length(length) => (None, self.expr(length, 0)),
        };
        self.scripts.push(row);
        self.scripts.len() as i32 - 1
    }

    fn node(&mut self, op: u8, a: i32, b: i32, value: u64) -> i32 {
        self.exprs.push(ExprRow { op, a, b, value });
        self.exprs.len() as i32 - 1
    }

    /// An expression as nodes, its names resolved at run time as the walk
    /// resolves them, then as macros, whose bodies are expanded here as the
    /// walker expands them.
    fn expr(&mut self, expr: &Expr, depth: usize) -> i32 {
        if depth > MACRO_DEPTH {
            return self.node(OP_FAIL, NONE, NONE, 0);
        }
        match expr {
            Expr::Int(value) => self.node(OP_INT, NONE, NONE, *value),
            Expr::Name(name) => {
                let id = self.name_id(name);
                let fallback = self.macro_node(name, depth + 1);
                self.node(OP_NAME, id, fallback, 0)
            }
            Expr::Call(function, args) => {
                let function = match function.as_str() {
                    "itCommandLength" => 0,
                    "GXGetTexBufferSize" => 1,
                    _ => return self.node(OP_FAIL, NONE, NONE, 0),
                };
                let nodes: Vec<i32> =
                    args.iter().map(|a| self.expr(a, depth)).collect();
                let start = self.args.len() as i32;
                self.args.extend(&nodes);
                self.node(OP_CALL, function, start, nodes.len() as u64)
            }
            Expr::Unary(op, a) => {
                let a = self.expr(a, depth);
                let op = match op {
                    UnaryOp::Not => OP_NOT,
                    UnaryOp::BitNot => OP_BITNOT,
                    UnaryOp::Neg => OP_NEG,
                };
                self.node(op, a, NONE, 0)
            }
            Expr::Binary(op, a, b) => {
                let a = self.expr(a, depth);
                let b = self.expr(b, depth);
                self.node(binary_op(*op), a, b, 0)
            }
        }
    }

    /// A macro's body as nodes at `depth`, or `NONE` without one.
    fn macro_node(&mut self, name: &str, depth: usize) -> i32 {
        let key = (name.to_owned(), depth);
        if let Some(&node) = self.macro_nodes.get(&key) {
            return node;
        }
        let Some(body) = self
            .project
            .macros
            .get(name)
            .and_then(|body| Expr::parse(body))
        else {
            return NONE;
        };
        // Reserved first, for macros that refer to themselves
        let node = self.node(OP_FAIL, NONE, NONE, 0);
        self.macro_nodes.insert(key, node);
        let body = self.expr(&body, depth);
        self.exprs[node as usize] = ExprRow {
            op: OP_NAME,
            a: NONE,
            b: body,
            value: 0,
        };
        node
    }
}

fn binary_op(op: BinaryOp) -> u8 {
    match op {
        BinaryOp::Or => 6,
        BinaryOp::And => 7,
        BinaryOp::BitOr => 8,
        BinaryOp::BitXor => 9,
        BinaryOp::BitAnd => 10,
        BinaryOp::Eq => 11,
        BinaryOp::Ne => 12,
        BinaryOp::Lt => 13,
        BinaryOp::Gt => 14,
        BinaryOp::Le => 15,
        BinaryOp::Ge => 16,
        BinaryOp::Shl => 17,
        BinaryOp::Shr => 18,
        BinaryOp::Add => 19,
        BinaryOp::Sub => 20,
        BinaryOp::Mul => 21,
        BinaryOp::Div => 22,
        BinaryOp::Rem => 23,
    }
}

/// The include path of a header from its DWARF path, e.g.
/// `/.../src/melee/ft/types.h` to `melee/ft/types.h`; `None` for the
/// toolchain's own (newlib's, the compiler's), which the host has its own of.
fn header(path: &str) -> Option<String> {
    if !path.ends_with(".h")
        || path.contains("newlib")
        || path.contains("/lib/clang/")
    {
        return None;
    }
    let at = ["/src/", "/include/"]
        .iter()
        .filter_map(|dir| path.rfind(dir).map(|at| at + dir.len()))
        .max()?;
    Some(path[at..].to_owned())
}

/// A C string literal.
fn literal(s: &str) -> String {
    let mut out = String::from("\"");
    for c in s.bytes() {
        match c {
            b'"' => out.push_str("\\\""),
            b'\\' => out.push_str("\\\\"),
            0x20..=0x7E => out.push(c as char),
            _ => {
                let _ = write!(out, "\\{c:03o}");
            }
        }
    }
    out.push('"');
    out
}

/// The roots, the values their loaders bind, and which archives they are
/// in.
type FileRoots = (Vec<RootRow>, Vec<(i32, u64)>, Vec<FileRow>);

/// Each archive of each file, with its roots: the files' archives in order,
/// publics then aliases, as `Project::walk` takes them.
fn file_roots(
    project: &Project,
    generator: &mut Generator,
) -> Result<FileRoots> {
    let mut roots = Vec::new();
    let mut root_binds = Vec::new();
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
            let start = roots.len();
            let mut seen = BTreeSet::new();
            for (name, _) in archive.named_publics() {
                let name = String::from_utf8_lossy(name).into_owned();
                if !seen.insert(name.clone()) {
                    continue;
                }
                let Some((die, count)) = project.root(&name, &file) else {
                    continue;
                };
                let binds = root_binds.len();
                for (bind, value) in project
                    .root_bindings
                    .get(&name)
                    .map(Vec::as_slice)
                    .unwrap_or_default()
                {
                    root_binds.push((generator.name_id(bind), *value));
                }
                let (count_kind, count) = count_row(count);
                roots.push(RootRow {
                    name,
                    alias: false,
                    address: 0,
                    ty: generator.type_index(die),
                    count_kind,
                    count,
                    binds,
                    nbinds: root_binds.len() - binds,
                });
            }
            for (address, entry) in project.aliases(&file, *at) {
                let Some(ty) = &entry.ty else { continue };
                let (count_kind, count) =
                    count_row(entry.count.unwrap_or(Count::One));
                roots.push(RootRow {
                    name: entry.name.clone(),
                    alias: true,
                    address,
                    ty: generator.type_index(project.symbol_types[ty]),
                    count_kind,
                    count,
                    binds: root_binds.len(),
                    nbinds: 0,
                });
            }
            if roots.len() > start {
                files.push(FileRow {
                    file: file.clone(),
                    archive: index,
                    roots: start,
                    nroots: roots.len() - start,
                });
            }
        }
    }
    Ok((roots, root_binds, files))
}

fn count_row(count: Count) -> (u8, u64) {
    match count {
        Count::One => (0, 0),
        Count::Exactly(n) => (1, n),
        Count::Unbounded => (2, 0),
    }
}

/// A C identifier for a type's index macro.
fn identifier(name: &str) -> Option<String> {
    let id: String = name
        .chars()
        .map(|c| {
            if c.is_ascii_alphanumeric() || c == '_' {
                c
            } else {
                '_'
            }
        })
        .collect();
    (!id.is_empty() && !id.starts_with(|c: char| c.is_ascii_digit()))
        .then_some(id)
}

fn codegen(args: Codegen) -> Result<()> {
    let project = Project::load(&args.check)?;
    let mut generator = Generator::new(&project);
    let (roots, root_binds, files) = file_roots(&project, &mut generator)?;
    // Every type a type refers to is listed by now, but members may list
    // more, which have members of their own
    generator.fill_members();
    for member in &generator.unplaced {
        log::warn!("no native place for {member}");
    }
    for ty in &generator.unhoisted {
        log::warn!("declared in a source file, not a header: {ty}");
    }

    let mut c = String::new();
    c.push_str(concat!(
        "/**\n",
        " * @file\n",
        " * The archives' types and roots, for the native archive interface.\n",
        " * Generated by `melee-dat native codegen`.\n",
        " */\n\n",
        "#include <stddef.h>\n",
        "#include <stdint.h>\n\n",
        "#include <dat/archive.h>\n\n",
    ));
    for header in &generator.headers {
        writeln!(c, "#include <{header}>")?;
    }
    let file_name = args
        .header
        .file_name()
        .map(|f| f.to_string_lossy().into_owned())
        .unwrap_or_default();
    writeln!(c, "\n#include \"{file_name}\"\n")?;
    for (i, (record, field)) in generator.accessors.iter().enumerate() {
        writeln!(
            c,
            "static void set_{i}(void* o, uint64_t v) {{ (({record}*) o)->{field} = v; }}"
        )?;
        writeln!(
            c,
            "static uint64_t get_{i}(const void* o) {{ return (uint64_t) ((const {record}*) o)->{field}; }}"
        )?;
    }

    c.push_str("\nstatic const DatType types[] = {\n");
    for t in &generator.types {
        writeln!(
            c,
            "    {{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}}},",
            literal(&t.name),
            t.id,
            t.kind,
            u8::from(t.is_signed),
            u8::from(t.raw),
            u8::from(t.blob),
            u8::from(t.has_pointers),
            u8::from(t.has_extent),
            t.size,
            t.native_size,
            t.target,
            t.resolved,
            t.count,
            t.members,
            t.nmembers,
            t.terminator,
            t.type_tag,
        )?;
    }
    c.push_str("};\n\nstatic const DatMember members[] = {\n");
    for m in &generator.members {
        let (set, get) = match m.accessors {
            Some(i) => (format!("set_{i}"), format!("get_{i}")),
            None => ("NULL".into(), "NULL".into()),
        };
        writeln!(
            c,
            "    {{{}, {}, {}, {}, {}, {}, {}, {}, {}, {set}, {get}, {}, {}, {}, {}, {}, {}, {}}},",
            m.name,
            m.ty,
            m.offset,
            m.bit_offset,
            m.bit_size,
            u8::from(m.has_offset),
            u8::from(m.extent),
            m.native_offset,
            m.native_size,
            m.count,
            m.terminator,
            m.cond,
            m.type_tag,
            m.script,
            m.binds,
            m.nbinds,
        )?;
    }
    if generator.members.is_empty() {
        c.push_str("    {0},\n");
    }
    c.push_str("};\n\nstatic const DatExpr exprs[] = {\n");
    for e in &generator.exprs {
        writeln!(c, "    {{{}, {}, {}, {}ull}},", e.op, e.a, e.b, e.value)?;
    }
    if generator.exprs.is_empty() {
        c.push_str("    {0},\n");
    }
    c.push_str("};\n\nstatic const int32_t args[] = {");
    for a in &generator.args {
        write!(c, "{a}, ")?;
    }
    c.push_str("0};\n\nstatic const DatBind binds[] = {\n");
    for (name, value) in &generator.binds {
        writeln!(c, "    {{{name}, {value}}},")?;
    }
    c.push_str("    {0},\n};\n\n");
    for (i, (table, _)) in generator.scripts.iter().enumerate() {
        if let Some(table) = table {
            write!(c, "static const uint8_t script_{i}[] = {{")?;
            for b in table {
                write!(c, "{b}, ")?;
            }
            c.push_str("0};\n");
        }
    }
    c.push_str("\nstatic const DatScript scripts[] = {\n");
    for (i, (table, length)) in generator.scripts.iter().enumerate() {
        match table {
            Some(table) => {
                writeln!(c, "    {{script_{i}, {}, -1}},", table.len())?
            }
            None => writeln!(c, "    {{NULL, 0, {length}}},")?,
        }
    }
    c.push_str("    {0},\n};\n\nstatic const char* const names[] = {\n");
    for name in &generator.names {
        writeln!(c, "    {},", literal(name))?;
    }
    c.push_str("    NULL,\n};\n\nstatic const DatRoot roots[] = {\n");
    for r in &roots {
        writeln!(
            c,
            "    {{{}, {}, 0x{:X}, {}, {}, {}ull, {}, {}}},",
            literal(&r.name),
            u8::from(r.alias),
            r.address,
            r.ty,
            r.count_kind,
            r.count,
            r.binds,
            r.nbinds,
        )?;
    }
    c.push_str("    {0},\n};\n\nstatic const DatRootBind root_binds[] = {\n");
    for (name, value) in &root_binds {
        writeln!(c, "    {{{name}, {value}ull}},")?;
    }
    c.push_str("    {0},\n};\n\nstatic const DatFileRoots files[] = {\n");
    for f in &files {
        writeln!(
            c,
            "    {{{}, {}, {}, {}}},",
            literal(&f.file),
            f.archive,
            f.roots,
            f.nroots
        )?;
    }
    write!(
        c,
        concat!(
            "    {{0}},\n}};\n\n",
            "const DatSchema melee_dat_schema = {{\n",
            "    types, {},\n",
            "    members, exprs, args, binds, scripts,\n",
            "    names, {},\n",
            "    roots, root_binds, files, {},\n",
            "}};\n",
        ),
        generator.types.len(),
        generator.names.len(),
        files.len(),
    )?;
    fs::write(&args.out, c)?;

    let mut h = String::from(concat!(
        "/**\n",
        " * @file\n",
        " * The schema of the archives' types, and their indices by name.\n",
        " * Generated by `melee-dat native codegen`.\n",
        " */\n\n",
        "#ifndef DAT_MELEE_TABLES_H\n",
        "#define DAT_MELEE_TABLES_H\n\n",
        "#include <dat/archive.h>\n\n",
        "extern const DatSchema melee_dat_schema;\n\n",
    ));
    let mut seen = BTreeSet::new();
    for (index, t) in generator.types.iter().enumerate() {
        let ty = project.canonical.ty(&project.graph, CanonId(t.id));
        if ty.name.is_none() || ty.scope.is_some() {
            continue;
        }
        let prefix = match ty.kind {
            TypeKind::Record { union: true, .. } => "union_",
            TypeKind::Record { .. } => "struct_",
            TypeKind::Enum { .. } => "enum_",
            _ => "",
        };
        let Some(id) = identifier(&format!("{prefix}{}", t.name)) else {
            continue;
        };
        if seen.insert(id.clone()) {
            writeln!(h, "#define DAT_TYPE_{id} {index}")?;
        }
    }
    h.push_str("\n#endif\n");
    fs::write(&args.header, h)?;
    eprintln!(
        "{} types, {} members, {} expression nodes, {} roots in {} archives; {} members without a native place",
        generator.types.len(),
        generator.members.len(),
        generator.exprs.len(),
        roots.len(),
        files.len(),
        generator.unplaced.len(),
    );
    Ok(())
}

/// What a walk reached, as `dat_trace` prints it.
pub fn trace(
    out: &mut impl Write,
    walk: &Walk,
    name_of: &dyn Fn(CanonId) -> String,
) -> io::Result<()> {
    for (offset, ids) in &walk.objects {
        for id in ids {
            writeln!(out, "object 0x{offset:X} {} {}", id.0, name_of(*id))?;
        }
    }
    let mut pointers: Vec<_> = walk.pointers.iter().copied().collect();
    pointers.sort();
    for at in pointers {
        writeln!(out, "pointer 0x{at:X}")?;
    }
    for (offset, end) in &walk.extents {
        writeln!(out, "extent 0x{offset:X} 0x{end:X}")?;
    }
    for ((offset, id), index) in &walk.choices {
        writeln!(out, "choice 0x{offset:X} {} {index}", id.0)?;
    }
    let issues: BTreeSet<(u8, u32, u32)> = walk
        .issues
        .iter()
        .map(|issue| match *issue {
            Issue::UnrelocatedPointer { at, value, .. } => (0, at, value),
            Issue::RelocatedScalar { at, .. } => (1, at, 0),
            Issue::OutOfBounds { at, .. } => (2, at, 0),
            Issue::AmbiguousUnion { at, .. } => (3, at, 0),
            Issue::UnknownCommand { at, opcode, .. } => {
                (4, at, u32::from(opcode))
            }
        })
        .collect();
    const KINDS: [&str; 5] = [
        "unrelocated-pointer",
        "relocated-scalar",
        "out-of-bounds",
        "ambiguous-union",
        "unknown-command",
    ];
    for (kind, at, value) in issues {
        writeln!(out, "issue {} 0x{at:X} 0x{value:X}", KINDS[kind as usize])?;
    }
    writeln!(out, "untyped-pointers {}", walk.untyped_pointers)?;
    writeln!(out, "sentinels {}", walk.sentinels)?;
    Ok(())
}

fn expect(args: Expect) -> Result<()> {
    let project = Project::load(&args.check)?;
    let mut only = globset::GlobSetBuilder::new();
    for glob in &args.only {
        only.add(globset::Glob::new(glob)?);
    }
    let only: GlobSet = only.build()?;
    let names: BTreeMap<CanonId, String> = project
        .canonical
        .types
        .iter()
        .enumerate()
        .map(|(i, t)| {
            (
                CanonId(i as u32),
                t.display.clone().unwrap_or_else(|| "?".into()),
            )
        })
        .collect();
    let name_of =
        |id: CanonId| names.get(&id).cloned().unwrap_or_else(|| "?".into());
    let mut out = io::BufWriter::new(io::stdout().lock());
    project.walk_all(&only, |walked| {
        if !walked.rooted {
            return Ok(());
        }
        writeln!(out, "archive {}", walked.name)?;
        trace(&mut out, &walked.result, &name_of)?;
        Ok(())
    })?;
    out.flush()?;
    Ok(())
}
