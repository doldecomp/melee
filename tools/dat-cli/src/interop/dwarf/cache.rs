//! A compact, derived form of a [`TypeGraph`] for tools that run many times
//! against the same DWARF.
//!
//! The DWARF repeats every header's types in every unit, and deduplicating
//! them takes seconds and gigabytes. The cache keeps one DIE per canonical
//! type, with every type reference pointing to those, plus what is
//! otherwise computed from the rest of the DWARF: the macros and the types
//! the loaders load each root name as.

use super::{
    DieId, Type, TypeGraph, TypeKind,
    canonical::Canonical,
    roots::{RootName, roots},
};
use crate::walk::macros;
use anyhow::{Context, Result};
use serde::{Deserialize, Serialize};
use std::{
    collections::{BTreeMap, HashMap},
    fs,
    path::Path,
};

#[derive(Serialize, Deserialize)]
pub struct TypesFile {
    /// Only the canonical types' representatives; no variables, globals or
    /// section contents.
    pub graph: TypeGraph,
    /// Macros and enum constants, for annotation expressions.
    pub macros: HashMap<String, String>,
    /// The type each root name is loaded as, by the loaders the DWARF
    /// records.
    pub roots: BTreeMap<String, DieId>,
}

impl TypesFile {
    pub fn build(graph: &TypeGraph) -> Self {
        let canonical = Canonical::new(graph);
        let rep = |die: DieId| {
            canonical.of(die).map_or(die, |id| canonical.get(id).rep)
        };
        let mut roots_by_name = BTreeMap::new();
        for root in roots(graph, &canonical) {
            if let (RootName::Literal(name), Some(ty)) = (root.name, root.ty) {
                roots_by_name.entry(name).or_insert(rep(ty));
            }
        }
        let types = canonical
            .types
            .iter()
            .map(|t| {
                let mut ty = graph.types[&t.rep].clone();
                remap(&mut ty, &rep);
                (t.rep, ty)
            })
            .collect();
        let compact = TypeGraph {
            strings: graph.strings.clone(),
            units: graph
                .units
                .iter()
                .map(|u| super::Unit {
                    name: u.name,
                    address_size: u.address_size,
                    macros: Vec::new(),
                })
                .collect(),
            types,
            ..TypeGraph::default()
        };
        TypesFile {
            graph: compact,
            macros: macros(graph),
            roots: roots_by_name,
        }
    }

    pub fn load(path: &Path) -> Result<Self> {
        let bytes =
            fs::read(path).with_context(|| format!("{}", path.display()))?;
        postcard::from_bytes(&bytes)
            .with_context(|| format!("{}", path.display()))
    }

    pub fn save(&self, path: &Path) -> Result<()> {
        fs::write(path, postcard::to_stdvec(self)?)
            .with_context(|| format!("{}", path.display()))
    }
}

/// Point every type reference of `ty` at its representative.
fn remap(ty: &mut Type, rep: &impl Fn(DieId) -> DieId) {
    let one = |die: &mut Option<DieId>| {
        if let Some(d) = die {
            *d = rep(*d);
        }
    };
    match &mut ty.kind {
        TypeKind::Pointer { target }
        | TypeKind::Typedef { target }
        | TypeKind::Const { target }
        | TypeKind::Volatile { target }
        | TypeKind::Restrict { target } => one(target),
        TypeKind::Array { element, .. } => one(element),
        TypeKind::Record { members, .. } => {
            for member in members {
                one(&mut member.ty);
            }
        }
        TypeKind::Enum { underlying, .. } => one(underlying),
        TypeKind::Subroutine { ret, params, .. } => {
            one(ret);
            for param in params {
                one(param);
            }
        }
        TypeKind::Base { .. } | TypeKind::Unspecified => {}
    }
}
