//! Types the data of an archive by walking it from its typed roots.
//!
//! Starting from each root symbol, the walk lays the root's type over the
//! archive's data and follows every pointer field through the relocation
//! table (see `Locate` in `lbarchive.c`: each entry is the data offset of a
//! word holding another data offset). What it reaches is typed; what does not
//! line up with the relocations is reported.

use crate::{
    dwarf::{
        DieId, Member, TypeGraph, TypeKind,
        annotation::DatTag,
        canonical::{CanonId, Canonical},
        expr::{Expr, eval_expr},
    },
    hsd::Archive,
};
use std::{
    collections::{BTreeMap, BTreeSet, HashMap, HashSet},
    rc::Rc,
};

/// Something in the data that disagrees with the types laid over it.
#[derive(Debug, Clone, PartialEq, Eq, PartialOrd, Ord)]
pub enum Issue {
    /// A pointer field holding a non-zero value that is not relocated.
    UnrelocatedPointer { at: u32, value: u32, path: String },
    /// A relocated word under a field that is not a pointer.
    RelocatedScalar { at: u32, path: String },
    /// A type extending past the end of the data.
    OutOfBounds { at: u32, path: String },
    /// A union none of whose members could be chosen, so none was
    /// followed.
    AmbiguousUnion { at: u32, path: String },
}

impl std::fmt::Display for Issue {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            // Words are shown signed, so sentinels like -1 read as such
            Issue::UnrelocatedPointer { at, value, path } => write!(
                f,
                "0x{at:X}: {path} holds {:#X} ({}), which is not relocated",
                value, *value as i32
            ),
            Issue::RelocatedScalar { at, path } => {
                write!(f, "0x{at:X}: {path} is not a pointer but is relocated")
            }
            Issue::OutOfBounds { at, path } => {
                write!(f, "0x{at:X}: {path} extends past the data")
            }
            Issue::AmbiguousUnion { at, path } => {
                write!(f, "0x{at:X}: {path} is a union with no valid member")
            }
        }
    }
}

impl Issue {
    pub fn kind(&self) -> &'static str {
        match self {
            Issue::UnrelocatedPointer { .. } => "unrelocated pointer",
            Issue::RelocatedScalar { .. } => "relocated scalar",
            Issue::OutOfBounds { .. } => "out of bounds",
            Issue::AmbiguousUnion { .. } => "ambiguous union",
        }
    }
}

enum Choice<'m> {
    Member(&'m Member),
    /// Every member's condition is false: the union holds nothing.
    Unused,
    /// Some member has no condition, or one that cannot be evaluated.
    Ambiguous,
}

#[derive(Debug, Default)]
pub struct Walk {
    /// Every object start reached, with the types it was reached as.
    pub objects: BTreeMap<u32, BTreeSet<CanonId>>,
    /// Relocated words the walk found a pointer field for.
    pub pointers: HashSet<u32>,
    /// Pointers followed to a target of unknown type (`void*`, functions).
    pub untyped_pointers: usize,
    /// Pointer fields holding -1, which the data uses like null.
    pub sentinels: usize,
    pub issues: BTreeSet<Issue>,
}

/// Names a `DAT_BIND` gives values to, for everything reached through the
/// member it is on. Inner bindings shadow outer ones.
#[derive(Debug)]
struct Scope {
    name: String,
    value: u64,
    outer: Env,
}

type Env = Option<Rc<Scope>>;

fn lookup(env: &Env, name: &str) -> Option<u64> {
    let mut scope = env.as_deref();
    while let Some(s) = scope {
        if s.name == name {
            return Some(s.value);
        }
        scope = s.outer.as_deref();
    }
    None
}

pub struct Walker<'a> {
    graph: &'a TypeGraph,
    canonical: &'a Canonical,
    macros: &'a HashMap<String, String>,
    data: &'a [u8],
    relocs: HashSet<u32>,
    /// Offsets of public symbols, which bound `DAT_EXTENT` arrays.
    publics: HashSet<u32>,
    /// Offsets some relocated pointer refers to: where objects start, which
    /// also bound `DAT_EXTENT` arrays.
    targets: HashSet<u32>,
    walk: Walk,
    visited: HashSet<(u32, CanonId)>,
    /// Objects still to walk, each with the bindings in effect where it
    /// was reached.
    queue: Vec<(u32, DieId, String, Env)>,
    env: Env,
}

impl<'a> Walker<'a> {
    pub fn new(
        graph: &'a TypeGraph,
        canonical: &'a Canonical,
        macros: &'a HashMap<String, String>,
        archive: &'a Archive<'a>,
    ) -> Self {
        Walker {
            graph,
            canonical,
            macros,
            data: archive.data,
            relocs: archive.relocs.iter().copied().collect(),
            publics: archive.publics.iter().map(|p| p.offset).collect(),
            targets: archive
                .relocs
                .iter()
                .filter_map(|&r| {
                    let at = r as usize;
                    Some(u32::from_be_bytes(
                        archive.data.get(at..at + 4)?.try_into().ok()?,
                    ))
                })
                .collect(),
            walk: Walk::default(),
            visited: HashSet::new(),
            queue: Vec::new(),
            env: None,
        }
    }

    /// Walk everything reachable from an object of type `die` at `offset`.
    pub fn root(&mut self, offset: u32, die: DieId, name: &str) {
        self.queue.push((offset, die, name.to_owned(), None));
        while let Some((offset, die, path, env)) = self.queue.pop() {
            self.env = env;
            self.object(offset, die, path);
        }
    }

    pub fn finish(self) -> Walk {
        self.walk
    }

    fn object(&mut self, offset: u32, die: DieId, path: String) {
        let Some(die) = self.resolve(Some(die)) else {
            return;
        };
        let Some(id) = self.canonical.of(die) else {
            return;
        };
        if !self.visited.insert((offset, id)) {
            return;
        }
        self.walk.objects.entry(offset).or_default().insert(id);
        self.layout(offset, die, &path, None);
    }

    /// Lay the type `die` over the data at `offset`. `parent` is the record
    /// a union is a member of, which its members' conditions refer to.
    fn layout(
        &mut self,
        offset: u32,
        die: DieId,
        path: &str,
        parent: Option<(DieId, u32)>,
    ) {
        let Some(die) = self.resolve(Some(die)) else {
            return;
        };
        // A record ending in a `DAT_EXTENT` array has no fixed size
        if !self.has_extent(die)
            && let Some(size) = self.canonical.byte_size(self.graph, die)
            && u64::from(offset) + size > self.data.len() as u64
        {
            self.issue(Issue::OutOfBounds {
                at: offset,
                path: path.to_owned(),
            });
            return;
        }
        let graph = self.graph;
        match &graph.types[&die].kind {
            TypeKind::Record {
                union: false,
                members,
                ..
            } => {
                for member in members {
                    // Bitfields hold no pointers
                    if member.bit_size.is_some() {
                        continue;
                    }
                    let (Some(ty), Some(at)) = (member.ty, member.offset)
                    else {
                        continue;
                    };
                    let path = field(path, member.name.map(|n| graph.str(n)));
                    let parent = Some((die, offset));
                    let at = offset + at as u32;
                    let binds = self.binds(member);
                    let outer = self.env.clone();
                    self.env = self.bound(&outer, &binds, parent, 0);
                    let declared = self.declared_type(member);
                    if let Some(count) = self.count(member, die, offset) {
                        self.counted(
                            at, ty, declared, count, &path, &binds, parent,
                        );
                    } else if let Some(target) = declared {
                        self.typed(at, target, &path);
                    } else if self.is_extent(member) {
                        self.extent(at, ty, &path, &binds, parent);
                    } else if !binds.is_empty()
                        && let Some((element, size, count)) = self.array(ty)
                    {
                        for i in 0..count {
                            self.env = self.bound(&outer, &binds, parent, i);
                            let path = format!("{path}[{i}]");
                            self.layout(
                                at + (i * size) as u32,
                                element,
                                &path,
                                parent,
                            );
                        }
                    } else {
                        self.layout(at, ty, &path, parent);
                    }
                    self.env = outer;
                }
            }
            TypeKind::Record {
                union: true,
                members,
                ..
            } => {
                // Views of plain data need no condition: nothing to follow
                if !self.has_pointers(die) {
                    return self.scalar(offset, die, path);
                }
                let member = match self.choose(members, offset, parent) {
                    Choice::Member(member) => member,
                    Choice::Unused => return,
                    // Following a guess could misread everything behind it
                    Choice::Ambiguous => {
                        self.issue(Issue::AmbiguousUnion {
                            at: offset,
                            path: path.to_owned(),
                        });
                        return;
                    }
                };
                if let Some(ty) = member.ty {
                    let path = field(path, member.name.map(|n| graph.str(n)));
                    self.layout(offset, ty, &path, parent);
                }
            }
            TypeKind::Array { element, dims } => {
                let Some(element) = self.resolve(*element) else {
                    return;
                };
                let Some(size) = self.canonical.byte_size(graph, element)
                else {
                    return;
                };
                // An unbounded array is walked as its first element
                let count: u64 = dims.iter().map(|d| d.unwrap_or(1)).product();
                for i in 0..count {
                    let path = format!("{path}[{i}]");
                    self.layout(
                        offset + (i * size) as u32,
                        element,
                        &path,
                        parent,
                    );
                }
            }
            TypeKind::Pointer { target } => {
                let value = self.word(offset);
                if self.relocs.contains(&offset) {
                    self.walk.pointers.insert(offset);
                    match self.pointee(*target) {
                        Some(target) => self.queue.push((
                            value,
                            target,
                            format!("{path}->"),
                            self.env.clone(),
                        )),
                        None => self.walk.untyped_pointers += 1,
                    }
                } else {
                    self.unrelocated(offset, value, path);
                }
            }
            TypeKind::Base { .. } | TypeKind::Enum { .. } => {
                if self.relocs.contains(&offset) {
                    self.issue(Issue::RelocatedScalar {
                        at: offset,
                        path: path.to_owned(),
                    });
                }
            }
            _ => {}
        }
    }

    /// Walk a `DAT_EXTENT` array: every element until the next public
    /// symbol, object or pointer target, the end of the data, or an element
    /// that does not fit its type.
    fn extent(
        &mut self,
        offset: u32,
        array: DieId,
        path: &str,
        binds: &[(String, Expr)],
        parent: Option<(DieId, u32)>,
    ) {
        let outer = self.env.clone();
        let Some(array) = self.resolve(Some(array)) else {
            return;
        };
        let TypeKind::Array { element, .. } = self.graph.types[&array].kind
        else {
            return self.layout(offset, array, path, parent);
        };
        let Some(element) = self.resolve(element) else {
            return;
        };
        let Some(size) = self.canonical.byte_size(self.graph, element) else {
            return;
        };
        let size = size as u32;
        for i in 0.. {
            let at = offset + i * size;
            if at as usize + size as usize > self.data.len() {
                break;
            }
            let boundary = self.publics.contains(&at)
                || self.targets.contains(&at)
                || self.walk.objects.contains_key(&at);
            if i > 0 && (boundary || !self.fits(at, element)) {
                break;
            }
            self.env = self.bound(&outer, binds, parent, i.into());
            self.layout(at, element, &format!("{path}[{i}]"), parent);
        }
        self.env = outer;
    }

    /// Whether the data at `offset` is consistent with `die` without
    /// following pointers: pointer fields are relocated or null, and no
    /// other field is relocated.
    fn fits(&self, offset: u32, die: DieId) -> bool {
        let Some(die) = self.resolve(Some(die)) else {
            return true;
        };
        match &self.graph.types[&die].kind {
            TypeKind::Pointer { .. } => {
                self.relocs.contains(&offset)
                    || matches!(self.word(offset), 0 | u32::MAX)
            }
            TypeKind::Base { .. } | TypeKind::Enum { .. } => {
                !self.relocs.contains(&offset)
            }
            TypeKind::Record {
                union: false,
                members,
                ..
            } => members.iter().all(|m| {
                m.bit_size.is_some()
                    || match (m.ty, m.offset) {
                        (Some(ty), Some(at)) => {
                            self.fits(offset + at as u32, ty)
                        }
                        _ => true,
                    }
            }),
            TypeKind::Array { element, dims } => {
                let (Some(element), Some(size)) = (
                    self.resolve(*element),
                    self.resolve(*element)
                        .and_then(|e| self.canonical.byte_size(self.graph, e)),
                ) else {
                    return true;
                };
                let count: u64 = dims.iter().map(|d| d.unwrap_or(1)).product();
                (0..count)
                    .all(|i| self.fits(offset + (i * size) as u32, element))
            }
            _ => true,
        }
    }

    /// The number of elements a `DAT_COUNT` pointer member refers to,
    /// evaluated against the other fields of its record.
    fn count(&self, member: &Member, record: DieId, base: u32) -> Option<u64> {
        let count = member.annotations.iter().find_map(|a| {
            match DatTag::parse(self.graph.str(a.value?))? {
                DatTag::Count(count) => Some(count),
                _ => None,
            }
        })?;
        eval_expr(self.macros, &count, &|name| {
            self.name(Some((record, base)), name)
        })
    }

    /// Follow a pointer to `count` consecutive elements, of the type it
    /// points to or else `element` (from `DAT_TYPE`).
    #[allow(clippy::too_many_arguments)]
    fn counted(
        &mut self,
        offset: u32,
        pointer: DieId,
        element: Option<DieId>,
        count: u64,
        path: &str,
        binds: &[(String, Expr)],
        parent: Option<(DieId, u32)>,
    ) {
        let Some(pointer) = self.resolve(Some(pointer)) else {
            return;
        };
        let target = match self.graph.types[&pointer].kind {
            TypeKind::Pointer { target } => target,
            // A pointer-sized integer given a type
            _ if element.is_some() => None,
            _ => return self.layout(offset, pointer, path, None),
        };
        let value = self.word(offset);
        if !self.relocs.contains(&offset) {
            self.unrelocated(offset, value, path);
            return;
        }
        self.walk.pointers.insert(offset);
        let Some(element) = element.or_else(|| self.pointee(target)) else {
            self.walk.untyped_pointers += 1;
            return;
        };
        let Some(size) = self.canonical.byte_size(self.graph, element) else {
            return;
        };
        // A count beyond the data is itself a finding, reported per element
        let outer = self.env.clone();
        for i in 0..count.min(self.data.len() as u64) {
            let env = self.bound(&outer, binds, parent, i);
            self.queue.push((
                value + (i * size) as u32,
                element,
                format!("{path}[{i}]"),
                env,
            ));
        }
    }

    /// A pointer field that is not relocated: null, the -1 the data also
    /// uses for none, or an error.
    fn unrelocated(&mut self, offset: u32, value: u32, path: &str) {
        match value {
            0 => {}
            u32::MAX => self.walk.sentinels += 1,
            _ => self.issue(Issue::UnrelocatedPointer {
                at: offset,
                value,
                path: path.to_owned(),
            }),
        }
    }

    /// The type a `DAT_TYPE` member refers to, looked up by name.
    fn declared_type(&self, member: &Member) -> Option<DieId> {
        let name =
            member.annotations.iter().find_map(|a| {
                match DatTag::parse(self.graph.str(a.value?))? {
                    DatTag::Type(name) => Some(name),
                    _ => None,
                }
            })?;
        let name =
            self.graph.strings.get(name.trim_start_matches("struct "))?;
        self.canonical
            .named(name)
            .iter()
            .map(|&id| self.canonical.get(id).rep)
            .find_map(|die| self.resolve(Some(die)))
    }

    /// A `DAT_TYPE` field: followed as a pointer to `target` when relocated,
    /// whatever its declared type.
    fn typed(&mut self, offset: u32, target: DieId, path: &str) {
        if self.relocs.contains(&offset) {
            self.walk.pointers.insert(offset);
            let value = self.word(offset);
            self.queue.push((
                value,
                target,
                format!("{path}->"),
                self.env.clone(),
            ));
        }
    }

    /// A name in an expression: a field of `record`, else a binding. Macros
    /// and enum constants are resolved by the evaluator after these.
    fn name(&self, record: Option<(DieId, u32)>, name: &str) -> Option<u64> {
        record
            .and_then(|(record, base)| self.field_value(record, base, name))
            .or_else(|| lookup(&self.env, name))
    }

    /// A member's `DAT_BIND`s, in order.
    fn binds(&self, member: &Member) -> Vec<(String, Expr)> {
        member
            .annotations
            .iter()
            .filter_map(|a| match DatTag::parse(self.graph.str(a.value?))? {
                DatTag::Bind(name, value) => Some((name, value)),
                _ => None,
            })
            .collect()
    }

    /// `outer` extended with `binds`, evaluated in `record` for the element
    /// at `index` (which the expressions see as `_index`). A binding that
    /// cannot be evaluated is left out, so names it would shadow stay
    /// visible.
    fn bound(
        &self,
        outer: &Env,
        binds: &[(String, Expr)],
        record: Option<(DieId, u32)>,
        index: u64,
    ) -> Env {
        let mut env = outer.clone();
        for (name, value) in binds {
            let value = eval_expr(self.macros, value, &|n| match n {
                "_index" => Some(index),
                _ => record
                    .and_then(|(r, base)| self.field_value(r, base, n))
                    .or_else(|| lookup(outer, n)),
            });
            if let Some(value) = value {
                env = Some(Rc::new(Scope {
                    name: name.clone(),
                    value,
                    outer: env,
                }));
            }
        }
        env
    }

    /// An array type's element, element size and element count.
    fn array(&self, die: DieId) -> Option<(DieId, u64, u64)> {
        let TypeKind::Array { element, dims } =
            &self.graph.types[&self.resolve(Some(die))?].kind
        else {
            return None;
        };
        let element = self.resolve(*element)?;
        let size = self.canonical.byte_size(self.graph, element)?;
        Some((element, size, dims.iter().map(|d| d.unwrap_or(1)).product()))
    }

    fn is_extent(&self, member: &Member) -> bool {
        member.annotations.iter().any(|a| {
            a.value.and_then(|v| DatTag::parse(self.graph.str(v)))
                == Some(DatTag::Extent)
        })
    }

    /// Whether any part of a type is a pointer, looking through records,
    /// unions and arrays but not through pointers.
    fn has_pointers(&self, die: DieId) -> bool {
        let Some(die) = self.resolve(Some(die)) else {
            return false;
        };
        match &self.graph.types[&die].kind {
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

    /// Plain data: report any relocated word within it.
    fn scalar(&mut self, offset: u32, die: DieId, path: &str) {
        let size = self.canonical.byte_size(self.graph, die).unwrap_or(0);
        for at in (offset..offset + size as u32).step_by(4) {
            if self.relocs.contains(&at) {
                self.issue(Issue::RelocatedScalar {
                    at,
                    path: path.to_owned(),
                });
            }
        }
    }

    /// Whether a record ends in a `DAT_EXTENT` array.
    fn has_extent(&self, die: DieId) -> bool {
        match &self.graph.types[&die].kind {
            TypeKind::Record { members, .. } => {
                members.last().is_some_and(|m| self.is_extent(m))
            }
            _ => false,
        }
    }

    /// The first union member whose `dat:if` condition holds. Conditions
    /// read the fields of the record containing the union, or else those of
    /// the union's own record members, for a union whose members share a
    /// common initial sequence. A lone member needs no condition.
    fn choose<'m>(
        &self,
        members: &'m [Member],
        base: u32,
        parent: Option<(DieId, u32)>,
    ) -> Choice<'m> {
        if let [member] = members {
            return Choice::Member(member);
        }
        let mut decided = true;
        for member in members {
            let condition = member.annotations.iter().find_map(|a| {
                match DatTag::parse(self.graph.str(a.value?))? {
                    DatTag::If(cond) => Some(cond),
                    _ => None,
                }
            });
            let holds = condition.and_then(|cond| {
                eval_expr(self.macros, &cond, &|name| {
                    if let Some((record, at)) = parent
                        && let Some(value) = self.field_value(record, at, name)
                    {
                        return Some(value);
                    }
                    members
                        .iter()
                        .find_map(|m| {
                            self.field_value(self.resolve(m.ty)?, base, name)
                        })
                        .or_else(|| lookup(&self.env, name))
                })
            });
            match holds {
                Some(0) => {}
                Some(_) => return Choice::Member(member),
                None => decided = false,
            }
        }
        if decided {
            Choice::Unused
        } else {
            Choice::Ambiguous
        }
    }

    /// The value of a scalar field of the record at `base`.
    fn field_value(
        &self,
        record: DieId,
        base: u32,
        name: &str,
    ) -> Option<u64> {
        let TypeKind::Record { members, .. } = &self.graph.types[&record].kind
        else {
            return None;
        };
        let member = members
            .iter()
            .find(|m| m.name.map(|n| self.graph.str(n)) == Some(name))?;
        let at = base + member.offset? as u32;
        let size = self.canonical.byte_size(self.graph, member.ty?)?;
        let bytes = self.data.get(at as usize..at as usize + size as usize)?;
        Some(bytes.iter().fold(0, |v, &b| v << 8 | u64::from(b)))
    }

    /// The type a pointer points to, if it can be followed.
    fn pointee(&self, target: Option<DieId>) -> Option<DieId> {
        let target = self.resolve(target)?;
        match self.graph.types[&target].kind {
            TypeKind::Subroutine { .. } | TypeKind::Unspecified => None,
            _ => Some(target),
        }
    }

    /// Look through typedefs and qualifiers, and from declarations to their
    /// definitions.
    fn resolve(&self, mut die: Option<DieId>) -> Option<DieId> {
        loop {
            let ty = self.graph.types.get(&die?)?;
            match &ty.kind {
                TypeKind::Typedef { target }
                | TypeKind::Const { target }
                | TypeKind::Volatile { target }
                | TypeKind::Restrict { target } => die = *target,
                TypeKind::Record {
                    declaration: true, ..
                } => {
                    let id = self.canonical.of(die?)?;
                    let definition =
                        self.canonical.definition(self.graph, id)?;
                    return Some(self.canonical.get(definition).rep);
                }
                _ => return die,
            }
        }
    }

    fn word(&self, offset: u32) -> u32 {
        let at = offset as usize;
        self.data
            .get(at..at + 4)
            .map_or(0, |b| u32::from_be_bytes(b.try_into().unwrap()))
    }

    fn issue(&mut self, issue: Issue) {
        self.walk.issues.insert(issue);
    }
}

fn field(path: &str, name: Option<&str>) -> String {
    let name = name.unwrap_or("?");
    if path.ends_with("->") {
        format!("{path}{name}")
    } else {
        format!("{path}.{name}")
    }
}

/// The first definition of each macro, by name.
pub fn macros(graph: &TypeGraph) -> HashMap<String, String> {
    let mut macros = HashMap::new();
    for m in graph.units.iter().flat_map(|u| &u.macros) {
        macros
            .entry(graph.str(m.name).to_owned())
            .or_insert_with(|| graph.str(m.value).to_owned());
    }
    // Enum constants resolve like macros whose body is their value
    for ty in graph.types.values() {
        if let TypeKind::Enum { enumerators, .. } = &ty.kind {
            for e in enumerators {
                if let Some(name) = e.name {
                    macros
                        .entry(graph.str(name).to_owned())
                        .or_insert_with(|| format!("({})", e.value));
                }
            }
        }
    }
    macros
}
