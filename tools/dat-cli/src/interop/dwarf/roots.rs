//! Root witnesses: the static variables `DAT_ROOTS` declares for each
//! `(&dst, "name")` pair passed to an archive loader.
//!
//! A witness has the type of `&dst`, a pointer to the pointer the symbol is
//! loaded into, so the root's type is two pointers down. Its `dat:root`
//! annotation is the name argument as written.

pub use super::annotation::RootName;
use super::{
    DieId, TypeGraph, TypeKind, Variable,
    annotation::DatTag,
    canonical::Canonical,
    expr::{eval_expr, identifier},
};
use crate::walk::macros;
use std::collections::HashMap;
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
    /// `DAT_BIND`s on the path through the loader's global name table.
    pub bindings: Vec<(String, u64)>,
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
            roots.push(Root {
                name,
                ty,
                bindings: Vec::new(),
                witness,
            });
        } else {
            roots.extend(names.into_iter().map(|(value, bindings)| Root {
                name: RootName::Literal(value),
                ty,
                bindings,
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
    macros: HashMap<String, String>,
}

#[derive(Clone)]
struct Cursor {
    at: u64,
    ty: DieId,
    index: u64,
    bindings: Vec<(String, u64)>,
}

type BoundName = (String, Vec<(String, u64)>);

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
            macros: macros(graph),
        }
    }

    /// Every string `expr` can evaluate to, or `None` if it isn't a path
    /// from a global to strings.
    fn strings(&self, expr: &str) -> Option<Vec<BoundName>> {
        let (base, steps) = path.parse(expr).ok()?;
        let global = self.graph.globals.get(&self.graph.strings.get(base)?)?;
        let mut cursors = vec![Cursor {
            at: global.address,
            ty: global.ty?,
            index: 0,
            bindings: Vec::new(),
        }];
        for step in &steps {
            cursors = cursors
                .into_iter()
                .flat_map(|cursor| self.step(cursor, step))
                .collect();
        }
        let mut strings = Vec::new();
        for cursor in cursors {
            if let Some(s) = self.string(cursor.at, cursor.ty)? {
                let value = (s, cursor.bindings);
                if !strings.contains(&value) {
                    strings.push(value);
                }
            }
        }
        Some(strings)
    }

    fn step(&self, mut cursor: Cursor, step: &Step) -> Vec<Cursor> {
        match step {
            Step::Index => self
                .elements(cursor.at, cursor.ty)
                .into_iter()
                .enumerate()
                .map(|(index, (at, ty))| Cursor {
                    at,
                    ty,
                    index: index as u64,
                    bindings: cursor.bindings.clone(),
                })
                .collect(),
            Step::Field(name) => {
                self.field(cursor, name).into_iter().collect()
            }
            Step::Arrow(name) => {
                let Some((at, ty)) = self.deref(cursor.at, cursor.ty) else {
                    return Vec::new();
                };
                cursor.at = at;
                cursor.ty = ty;
                self.field(cursor, name).into_iter().collect()
            }
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

    fn field(&self, mut cursor: Cursor, name: &str) -> Option<Cursor> {
        let TypeKind::Record { members, .. } =
            &self.graph.types[&strip(self.graph, Some(cursor.ty))?].kind
        else {
            return None;
        };
        let member = members
            .iter()
            .find(|m| m.name.map(|n| self.graph.str(n)) == Some(name))?;
        for annotation in &member.annotations {
            let Some(DatTag::Bind(name, expr)) = annotation
                .value
                .and_then(|v| DatTag::parse(self.graph.str(v)))
            else {
                continue;
            };
            let value = eval_expr(&self.macros, &expr, &|name| {
                if name == "_index" {
                    Some(cursor.index)
                } else {
                    cursor
                        .bindings
                        .iter()
                        .rev()
                        .find(|(n, _)| n == name)
                        .map(|(_, value)| *value)
                }
            });
            if let Some(value) = value {
                cursor.bindings.push((name, value));
            }
        }
        cursor.at += member.offset?;
        cursor.ty = member.ty?;
        Some(cursor)
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

#[cfg(test)]
mod tests {
    use super::*;
    use crate::dwarf::{Annotation, Global, Member, Type, Unit};

    #[test]
    fn loader_name_table_bindings_survive_expansion_and_cache() {
        let mut graph = TypeGraph::default();
        graph.units.push(Unit {
            name: None,
            address_size: 4,
            macros: Vec::new(),
        });
        let name = graph.strings.get_or_intern("name");
        let bind = graph.strings.get_or_intern("dat:bind(kind, _index)");
        let member = Member {
            name: Some(name),
            ty: Some(2),
            offset: Some(0),
            bit_size: None,
            bit_offset: None,
            annotations: vec![Annotation {
                name: None,
                value: Some(bind),
            }],
        };
        let kinds = [
            (
                1,
                1,
                TypeKind::Base {
                    encoding: gimli::DW_ATE_signed_char.0,
                },
            ),
            (2, 4, TypeKind::Pointer { target: Some(1) }),
            (
                3,
                4,
                TypeKind::Record {
                    union: false,
                    declaration: false,
                    members: vec![member],
                },
            ),
            (
                4,
                12,
                TypeKind::Array {
                    element: Some(3),
                    dims: vec![Some(3)],
                },
            ),
            (5, 4, TypeKind::Pointer { target: Some(3) }),
            (6, 4, TypeKind::Pointer { target: Some(5) }),
        ];
        for (die, size, kind) in kinds {
            graph.types.insert(
                die,
                Type {
                    unit: 0,
                    name: None,
                    byte_size: Some(size),
                    decl_file: None,
                    scope: None,
                    annotations: Vec::new(),
                    kind,
                },
            );
        }
        let names = graph.strings.get_or_intern("names");
        graph.globals.insert(
            names,
            Global {
                address: 0x100,
                ty: Some(4),
            },
        );
        let pointer = graph.strings.get_or_intern("pointer");
        graph.globals.insert(
            pointer,
            Global {
                address: 0x200,
                ty: Some(5),
            },
        );
        graph.sections = vec![
            (
                0x100,
                [0x300u32, 0x304, 0x304]
                    .into_iter()
                    .flat_map(u32::to_be_bytes)
                    .collect(),
            ),
            (0x200, 0x100u32.to_be_bytes().to_vec()),
            (0x300, b"one\0two\0".to_vec()),
        ];
        let annotation =
            graph.strings.get_or_intern("dat:root(names[kind].name)");
        graph.variables.insert(
            7,
            Variable {
                unit: 0,
                name: None,
                ty: Some(6),
                decl_file: None,
                decl_line: None,
                scope: None,
                annotations: vec![Annotation {
                    name: None,
                    value: Some(annotation),
                }],
            },
        );
        let canonical = Canonical::new(&graph);
        let memory = Memory::new(&graph, &canonical);
        let expected = vec![
            ("one".into(), vec![("kind".into(), 0)]),
            ("two".into(), vec![("kind".into(), 1)]),
            ("two".into(), vec![("kind".into(), 2)]),
        ];
        assert_eq!(memory.strings("names[kind].name"), Some(expected.clone()));
        assert_eq!(memory.strings("pointer[kind].name"), Some(expected));
        assert_eq!(
            memory.strings("pointer->name"),
            Some(vec![("one".into(), vec![("kind".into(), 0)])])
        );
        let expanded = roots(&graph, &canonical);
        assert_eq!(expanded.len(), 3);
        assert_eq!(expanded[2].bindings, [("kind".into(), 2)]);
        let cache = super::super::cache::TypesFile::build(&graph);
        assert_eq!(cache.root_bindings["one"], [("kind".into(), 0)]);
        // Like root types, duplicate root names retain the first witness.
        assert_eq!(cache.root_bindings["two"], [("kind".into(), 1)]);
        let bytes = postcard::to_stdvec(&cache).unwrap();
        let restored: super::super::cache::TypesFile =
            postcard::from_bytes(&bytes).unwrap();
        assert_eq!(restored.root_bindings, cache.root_bindings);
    }
}
