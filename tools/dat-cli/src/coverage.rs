//! Which relocations a walk explains, and why the rest are not.
//!
//! An unexplained relocation is one of:
//! - a gap: inside a typed object, or in data a pointer reaches. A type is
//!   missing or wrong.
//! - trailing: after the end of a typed object, where nothing points. The
//!   type is too short, or the data after it is unreferenced.
//! - unreferenced: in data nothing reaches from a public symbol. No type
//!   can explain it.

use crate::{
    dwarf::{TypeGraph, canonical::Canonical},
    hsd::Archive,
    walk::Walk,
};
use std::collections::{BTreeSet, HashMap, HashSet};

#[derive(Debug, Clone, Copy, PartialEq, Eq, serde::Serialize)]
#[serde(rename_all = "lowercase")]
pub enum Kind {
    Gap,
    Trailing,
    Unreferenced,
}

/// An unexplained relocation.
#[derive(Debug, Clone)]
pub struct Unexplained {
    /// Offset of the relocated word in the data.
    pub at: u32,
    pub kind: Kind,
    /// The nearest object the walk typed at or before it.
    pub owner: Option<u32>,
}

#[derive(Debug, Clone, Default)]
pub struct Coverage {
    pub relocs: usize,
    pub explained: usize,
    pub unexplained: Vec<Unexplained>,
}

impl Coverage {
    pub fn count(&self, kind: Kind) -> usize {
        self.unexplained.iter().filter(|u| u.kind == kind).count()
    }
}

/// Classify an archive's relocations after walking it.
///
/// The data is cut into spans, which are reachable when a public symbol
/// starts one, or a relocated word in a reachable span points into it.
/// Coarse spans start at public symbols and pointer targets; fine spans
/// also at the start and end of every object the walk typed. Unreferenced
/// data is unreachable even in coarse spans; trailing data only in fine
/// ones, where it starts past a typed object's end.
pub fn coverage(
    graph: &TypeGraph,
    canonical: &Canonical,
    archive: &Archive,
    walk: &Walk,
) -> Coverage {
    let word = |at: u32| {
        let at = at as usize;
        archive
            .data
            .get(at..at + 4)
            .map_or(0, |b| u32::from_be_bytes(b.try_into().unwrap()))
    };
    let publics: Vec<u32> = archive.publics.iter().map(|p| p.offset).collect();

    let mut coarse: BTreeSet<u32> = BTreeSet::from([0]);
    coarse.extend(&publics);
    coarse.extend(archive.relocs.iter().map(|&r| word(r)));
    let mut fine = coarse.clone();
    for (&offset, types) in &walk.objects {
        fine.insert(offset);
        let size = types
            .iter()
            .filter_map(|&id| {
                canonical.byte_size(graph, canonical.get(id).rep)
            })
            .max()
            .unwrap_or(0);
        if size > 0 {
            fine.insert(offset + size as u32);
        }
    }
    let coarse = Reach::new(coarse, archive, &publics, word);
    let fine = Reach::new(fine, archive, &publics, word);

    let mut unexplained: Vec<Unexplained> = archive
        .relocs
        .iter()
        .filter(|at| !walk.pointers.contains(at))
        .map(|&at| Unexplained {
            at,
            kind: if !coarse.reaches(at) {
                Kind::Unreferenced
            } else if !fine.reaches(at) {
                Kind::Trailing
            } else {
                Kind::Gap
            },
            owner: walk.objects.range(..=at).next_back().map(|(&o, _)| o),
        })
        .collect();
    unexplained.sort_by_key(|u| u.at);
    Coverage {
        relocs: archive.relocs.len(),
        explained: archive.relocs.len() - unexplained.len(),
        unexplained,
    }
}

/// Which spans of an archive's data are reachable from its public symbols.
struct Reach {
    starts: BTreeSet<u32>,
    reachable: HashSet<u32>,
}

impl Reach {
    fn new(
        starts: BTreeSet<u32>,
        archive: &Archive,
        publics: &[u32],
        word: impl Fn(u32) -> u32,
    ) -> Self {
        let span = |at: u32| *starts.range(..=at).next_back().unwrap_or(&0);
        // Relocations by the span they are in
        let mut edges: HashMap<u32, Vec<u32>> = HashMap::new();
        for &r in &archive.relocs {
            edges.entry(span(r)).or_default().push(span(word(r)));
        }
        let mut reachable = HashSet::new();
        let mut queue: Vec<u32> = publics.iter().map(|&p| span(p)).collect();
        while let Some(s) = queue.pop() {
            if reachable.insert(s) {
                queue.extend(edges.get(&s).into_iter().flatten());
            }
        }
        Reach { starts, reachable }
    }

    fn reaches(&self, at: u32) -> bool {
        let span = *self.starts.range(..=at).next_back().unwrap_or(&0);
        self.reachable.contains(&span)
    }
}

/// An archive's family for grouping, e.g. `Pl` for `PlMrNr.dat`.
pub fn family(file: &str) -> &str {
    file.get(..2).unwrap_or(file)
}

/// A walk path without its root's name, indices or repeated links, for
/// grouping: `ftDataMario.x0->child->child` becomes `.x0->child`.
pub fn generic_path(path: &str) -> String {
    let field = path.find(['.', '-', '[']).map_or("", |at| &path[at..]);
    let mut out = String::new();
    let mut in_index = false;
    for c in field.chars() {
        match c {
            '[' => {
                in_index = true;
                out.push_str("[]");
            }
            ']' => in_index = false,
            _ if in_index => {}
            _ => out.push(c),
        }
    }
    for link in ["->child", "->next"] {
        let twice = format!("{link}{link}");
        while out.contains(&twice) {
            out = out.replace(&twice, link);
        }
    }
    out
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn generic_paths() {
        assert_eq!(
            generic_path("ftDataMario.x1C->[2]->x8->[0]->child->child->next"),
            ".x1C->[]->x8->[]->child->next"
        );
        assert_eq!(generic_path("itemdata"), "");
    }
}
