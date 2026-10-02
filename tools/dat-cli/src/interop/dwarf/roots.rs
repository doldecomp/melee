//! Root witnesses: the static variables `DAT_ROOTS` declares for each
//! `(&dst, "name")` pair passed to an archive loader.
//!
//! A witness has the type of `&dst`, a pointer to the pointer the symbol is
//! loaded into, so the root's type is two pointers down. Its `dat:root`
//! annotation is the name argument as written.

pub use super::annotation::RootName;
use super::{
    DieId, TypeGraph, TypeKind, Variable, annotation::DatTag,
    canonical::Canonical, expr::identifier,
};
use winnow::{
    ModalResult, Parser,
    combinator::{alt, delimited, eof, preceded, repeat},
    token::take_till,
};

#[derive(Debug, Clone)]
pub struct Root<'g> {
    pub name: RootName,
    /// The type the symbol is loaded as; `None` for `void`.
    pub ty: Option<DieId>,
    pub witness: &'g Variable,
}

impl Root<'_> {
    /// The source location of the loader call, e.g. `mnmain.c:2781`.
    pub fn location(&self, graph: &TypeGraph) -> String {
        let file = self.witness.decl_file.map_or("?", |f| graph.str(f));
        // Relative to src/; a `#line` directive can leave a bare file name
        let file = match file.rsplit_once("/src/") {
            Some((_, rel)) => rel,
            None => file.rsplit_once('/').map_or(file, |(_, name)| name),
        };
        match self.witness.decl_line {
            Some(line) => format!("{file}:{line}"),
            None => file.to_owned(),
        }
    }

    pub fn function<'g>(&self, graph: &'g TypeGraph) -> Option<&'g str> {
        self.witness.scope.map(|s| graph.str(s))
    }
}

/// Every root in the graph, in DIE order. A witness whose name is an
/// expression over globals, like `names[kind].b`, gives one root per string
/// it can evaluate to; any other expression is kept as written.
pub fn roots<'g>(
    graph: &'g TypeGraph,
    canonical: &Canonical,
) -> Vec<Root<'g>> {
    let memory = Memory::new(graph, canonical);
    let mut roots = Vec::new();
    for witness in graph.variables.values() {
        let Some(name) = witness.annotations.iter().find_map(|a| {
            match DatTag::parse(graph.str(a.value?))? {
                DatTag::Root(name) => Some(name),
                _ => None,
            }
        }) else {
            continue;
        };
        let ty = pointee(graph, pointee(graph, witness.ty));
        let names = match &name {
            RootName::Expr(expr) => memory.strings(expr).unwrap_or_default(),
            RootName::Literal(_) => Vec::new(),
        };
        if names.is_empty() {
            roots.push(Root { name, ty, witness });
        } else {
            roots.extend(names.into_iter().map(|value| Root {
                name: RootName::Literal(value),
                ty,
                witness,
            }));
        }
    }
    roots
}

/// A step of a path from a global: `[...]`, `.field` or `->field`.
#[derive(Debug, Clone, PartialEq, Eq)]
enum Step {
    /// Any index; every element is visited.
    Index,
    Field(String),
    Arrow(String),
}

/// `global[...].field->field...`; indices may be any expression.
fn path<'i>(input: &mut &'i str) -> ModalResult<(&'i str, Vec<Step>)> {
    let step = alt((
        delimited('[', brackets, ']').value(Step::Index),
        preceded('.', identifier).map(|f: &str| Step::Field(f.to_owned())),
        preceded("->", identifier).map(|f: &str| Step::Arrow(f.to_owned())),
    ));
    (identifier, repeat(0.., step), eof)
        .map(|(base, steps, _)| (base, steps))
        .parse_next(input)
}

/// The contents of `[...]`, with brackets inside it balanced.
fn brackets(input: &mut &str) -> ModalResult<()> {
    repeat(
        0..,
        alt((
            take_till(1.., ['[', ']']).void(),
            ('[', brackets, ']').void(),
        )),
    )
    .parse_next(input)
}

/// The initialized data of the file, read through the types of its globals.
struct Memory<'a> {
    graph: &'a TypeGraph,
    canonical: &'a Canonical,
    /// Every global's extent, `(start, end)`, sorted by start.
    extents: Vec<(u64, u64)>,
}

impl<'a> Memory<'a> {
    fn new(graph: &'a TypeGraph, canonical: &'a Canonical) -> Self {
        let mut extents: Vec<_> = graph
            .globals
            .values()
            .filter_map(|g| {
                let size = canonical.byte_size(graph, g.ty?)?;
                Some((g.address, g.address + size))
            })
            .collect();
        extents.sort_unstable();
        Memory {
            graph,
            canonical,
            extents,
        }
    }

    /// Every string `expr` can evaluate to, or `None` if it isn't a path
    /// from a global to strings.
    fn strings(&self, expr: &str) -> Option<Vec<String>> {
        let (base, steps) = path.parse(expr).ok()?;
        let global = self.graph.globals.get(&self.graph.strings.get(base)?)?;
        let mut cursors = vec![(global.address, global.ty?)];
        for step in &steps {
            cursors = cursors
                .into_iter()
                .flat_map(|(at, ty)| self.step(at, ty, step))
                .collect();
        }
        let mut strings = Vec::new();
        for (at, ty) in cursors {
            if let Some(s) = self.string(at, ty)?
                && !strings.contains(&s)
            {
                strings.push(s);
            }
        }
        Some(strings)
    }

    fn step(&self, at: u64, ty: DieId, step: &Step) -> Vec<(u64, DieId)> {
        match step {
            Step::Index => self.elements(at, ty),
            Step::Field(name) => {
                self.field(at, ty, name).into_iter().collect()
            }
            Step::Arrow(name) => self
                .deref(at, ty)
                .and_then(|(p, target)| self.field(p, target, name))
                .into_iter()
                .collect(),
        }
    }

    /// The elements of an array, or of the global a pointer points into
    /// from the element it points to onwards.
    fn elements(&self, at: u64, ty: DieId) -> Vec<(u64, DieId)> {
        let graph = self.graph;
        let Some(ty) = strip(graph, Some(ty)) else {
            return Vec::new();
        };
        let (start, element, count) = match &graph.types[&ty].kind {
            TypeKind::Array { element, dims } => {
                let Some(element) = strip(graph, *element) else {
                    return Vec::new();
                };
                // Further dimensions stay part of each element
                let count = dims.first().copied().flatten().unwrap_or(0);
                (at, element, count)
            }
            TypeKind::Pointer { .. } => {
                let Some((p, element)) = self.deref(at, ty) else {
                    return Vec::new();
                };
                let size = self.size(element).unwrap_or(0).max(1);
                let end = self.extent_end(p).unwrap_or(p);
                (p, element, (end - p) / size)
            }
            _ => return Vec::new(),
        };
        let size = self.size(element).unwrap_or(0);
        (0..count).map(|i| (start + i * size, element)).collect()
    }

    fn field(&self, at: u64, ty: DieId, name: &str) -> Option<(u64, DieId)> {
        let TypeKind::Record { members, .. } =
            &self.graph.types[&strip(self.graph, Some(ty))?].kind
        else {
            return None;
        };
        let member = members
            .iter()
            .find(|m| m.name.map(|n| self.graph.str(n)) == Some(name))?;
        Some((at + member.offset?, member.ty?))
    }

    /// The address a pointer at `at` holds, and the type it points to.
    fn deref(&self, at: u64, ty: DieId) -> Option<(u64, DieId)> {
        let TypeKind::Pointer { target } =
            self.graph.types[&strip(self.graph, Some(ty))?].kind
        else {
            return None;
        };
        let p = self.word(at)?;
        (p != 0).then_some((p, target?))
    }

    /// A `char*` or `char[]` at `at` as a string; `None` inside if it isn't
    /// one, `Some(None)` if it is but can't be read (e.g. null).
    fn string(&self, at: u64, ty: DieId) -> Option<Option<String>> {
        let ty = strip(self.graph, Some(ty))?;
        let (start, element) = match &self.graph.types[&ty].kind {
            TypeKind::Array { element, .. } => (Some(at), *element),
            TypeKind::Pointer { target } => {
                (self.word(at).filter(|&p| p != 0), *target)
            }
            _ => return None,
        };
        let element = &self.graph.types[&strip(self.graph, element)?];
        if !matches!(element.kind, TypeKind::Base { .. })
            || element.byte_size != Some(1)
        {
            return None;
        }
        Some(start.map(|start| {
            let bytes: Vec<u8> = (start..start + 256)
                .map_while(|a| self.graph.bytes(a, 1).map(|b| b[0]))
                .take_while(|&b| b != 0)
                .collect();
            String::from_utf8_lossy(&bytes).into_owned()
        }))
    }

    fn word(&self, at: u64) -> Option<u64> {
        let bytes = self.graph.bytes(at, 4)?;
        Some(u32::from_be_bytes(bytes.try_into().ok()?).into())
    }

    fn size(&self, die: DieId) -> Option<u64> {
        self.canonical.byte_size(self.graph, die)
    }

    /// The end of the global containing `address`.
    fn extent_end(&self, address: u64) -> Option<u64> {
        let i = self.extents.partition_point(|&(start, _)| start <= address);
        let (_, end) = self.extents.get(i.checked_sub(1)?)?;
        (address < *end).then_some(*end)
    }
}

/// Look through typedefs and qualifiers.
fn strip(graph: &TypeGraph, mut die: Option<DieId>) -> Option<DieId> {
    while let TypeKind::Typedef { target }
    | TypeKind::Const { target }
    | TypeKind::Volatile { target } = graph.types.get(&die?)?.kind
    {
        die = target;
    }
    die
}

/// The target of a pointer, looking through typedefs and qualifiers.
fn pointee(graph: &TypeGraph, mut die: Option<DieId>) -> Option<DieId> {
    loop {
        match &graph.types.get(&die?)?.kind {
            TypeKind::Typedef { target }
            | TypeKind::Const { target }
            | TypeKind::Volatile { target }
            | TypeKind::Restrict { target } => die = *target,
            TypeKind::Pointer { target } => return *target,
            _ => return None,
        }
    }
}
