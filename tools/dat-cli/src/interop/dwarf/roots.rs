//! Root witnesses: the static variables `DAT_ROOTS` declares for each
//! `(&dst, "name")` pair passed to an archive loader.
//!
//! A witness has the type of `&dst`, a pointer to the pointer the symbol is
//! loaded into, so the root's type is two pointers down. Its `dat:root`
//! annotation is the name argument as written.

pub use super::annotation::RootName;
use super::{DieId, TypeGraph, TypeKind, Variable, annotation::DatTag};

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

/// Every root witness in the graph, in DIE order.
pub fn roots(graph: &TypeGraph) -> Vec<Root<'_>> {
    graph
        .variables
        .values()
        .filter_map(|witness| {
            let name =
                witness.annotations.iter().find_map(
                    |a| match DatTag::parse(graph.str(a.value?))? {
                        DatTag::Root(name) => Some(name),
                        _ => None,
                    },
                )?;
            // A global string's value, read from the file
            let name = match name {
                RootName::Expr(expr) => match global_string(graph, &expr) {
                    Some(value) => RootName::Literal(value),
                    None => RootName::Expr(expr),
                },
                literal => literal,
            };
            Some(Root {
                name,
                ty: pointee(graph, pointee(graph, witness.ty)),
                witness,
            })
        })
        .collect()
}

/// The initial value of the global `char` array `name`, up to its first NUL.
fn global_string(graph: &TypeGraph, name: &str) -> Option<String> {
    let global = graph.globals.get(&graph.strings.get(name)?)?;
    let TypeKind::Array { element, dims } =
        &graph.types.get(&strip(graph, global.ty)?)?.kind
    else {
        return None;
    };
    let element = graph.types.get(&strip(graph, *element)?)?;
    if !matches!(element.kind, TypeKind::Base { .. })
        || element.byte_size != Some(1)
    {
        return None;
    }
    let len = dims.first().copied().flatten()?;
    let bytes = graph.bytes(global.address, len as usize)?;
    let end = bytes.iter().position(|&b| b == 0).unwrap_or(bytes.len());
    Some(String::from_utf8_lossy(&bytes[..end]).into_owned())
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
