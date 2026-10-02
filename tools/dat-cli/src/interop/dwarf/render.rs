//! Renders canonical types as C-like text for review.
//!
//! The output is meant to be read and diffed, not compiled: anonymous types
//! are written under their display names (e.g. `union HSD_Joint::u`), and
//! every member carries its offset and annotations from the DWARF.

use super::{
    Annotation, DieId, Member, Type, TypeGraph, TypeKind,
    canonical::{CanonId, Canonical},
};
use std::fmt::Write;

pub struct Renderer<'a> {
    graph: &'a TypeGraph,
    canonical: &'a Canonical,
}

impl<'a> Renderer<'a> {
    pub fn new(graph: &'a TypeGraph, canonical: &'a Canonical) -> Self {
        Renderer { graph, canonical }
    }

    /// The name a canonical type is listed and looked up under.
    pub fn display(&self, id: CanonId) -> Option<&'a str> {
        self.canonical.get(id).display.as_deref()
    }

    /// Whether a canonical type is worth listing on its own: definitions of
    /// records and enums, and typedefs, at file scope.
    pub fn is_listed(&self, id: CanonId) -> bool {
        let ty = self.canonical.ty(self.graph, id);
        ty.scope.is_none()
            && self.display(id).is_some()
            && matches!(
                ty.kind,
                TypeKind::Record {
                    declaration: false,
                    ..
                } | TypeKind::Enum { .. }
                    | TypeKind::Typedef { .. }
            )
    }

    /// The full definition of a listed type.
    pub fn definition(&self, id: CanonId) -> String {
        let ty = self.canonical.ty(self.graph, id);
        let mut out = String::new();
        match &ty.kind {
            TypeKind::Record { members, .. } => {
                self.record(&mut out, id, ty, members)
            }
            TypeKind::Enum { enumerators, .. } => {
                let _ = writeln!(
                    out,
                    "{} {{{}",
                    self.tag(id, ty),
                    self.size_comment(ty)
                );
                for e in enumerators {
                    let name = e.name.map_or("?", |n| self.graph.str(n));
                    let _ = writeln!(out, "    {name} = {},", e.value);
                }
                out.push_str("};\n");
            }
            TypeKind::Typedef { target } => {
                let name = self.display(id).unwrap_or("?");
                let _ = writeln!(
                    out,
                    "typedef {}{};",
                    self.declare(*target, name),
                    self.annotations(&ty.annotations)
                );
            }
            _ => {}
        }
        out
    }

    fn record(
        &self,
        out: &mut String,
        id: CanonId,
        ty: &Type,
        members: &[Member],
    ) {
        let _ = writeln!(
            out,
            "{}{} {{{}",
            self.tag(id, ty),
            self.annotations(&ty.annotations),
            self.size_comment(ty)
        );
        for member in members {
            let name = member.name.map_or("", |n| self.graph.str(n));
            let location = match (member.bit_offset, member.bit_size) {
                (Some(bits), Some(_)) => {
                    format!("+0x{:X}:{}", bits / 8, bits % 8)
                }
                _ => format!("+0x{:X}", member.offset.unwrap_or(0)),
            };
            let bits = member
                .bit_size
                .map_or(String::new(), |size| format!(" : {size}"));
            let _ = writeln!(
                out,
                "    /* {location} */ {}{bits}{};",
                self.declare(member.ty, name),
                self.annotations(&member.annotations)
            );
        }
        out.push_str("};\n");
    }

    /// `struct Foo`, `union Foo::u` or `enum Bar`.
    fn tag(&self, id: CanonId, ty: &Type) -> String {
        let keyword = match ty.kind {
            TypeKind::Record { union: true, .. } => "union",
            TypeKind::Record { .. } => "struct",
            TypeKind::Enum { .. } => "enum",
            _ => "",
        };
        match (ty.name, self.display(id)) {
            (Some(name), _) => format!("{keyword} {}", self.graph.str(name)),
            (None, Some(display)) => {
                format!("{keyword} /* anonymous */ {display}")
            }
            (None, None) => format!("{keyword} /* anonymous */"),
        }
    }

    fn size_comment(&self, ty: &Type) -> String {
        ty.byte_size
            .map_or(String::new(), |size| format!(" /* size 0x{size:X} */"))
    }

    fn annotations(&self, annotations: &[Annotation]) -> String {
        annotations
            .iter()
            .filter_map(|a| a.value)
            .map(|value| format!(" /* {} */", self.graph.str(value)))
            .collect()
    }

    /// A C declaration of `inner` with type `target`; `None` is `void`.
    pub fn declare(&self, target: Option<DieId>, inner: &str) -> String {
        let Some(die) = target else {
            return join("void", inner);
        };
        let Some(ty) = self.graph.types.get(&die) else {
            return join("/* missing */", inner);
        };
        match &ty.kind {
            TypeKind::Pointer { target } => {
                self.declare(*target, &format!("*{inner}"))
            }
            TypeKind::Const { target } => {
                self.qualify("const", *target, inner)
            }
            TypeKind::Volatile { target } => {
                self.qualify("volatile", *target, inner)
            }
            TypeKind::Restrict { target } => {
                self.qualify("restrict", *target, inner)
            }
            TypeKind::Array { element, dims } => {
                let mut inner = parenthesize(inner);
                for dim in dims {
                    match dim {
                        Some(n) => {
                            let _ = write!(inner, "[{n}]");
                        }
                        None => inner.push_str("[]"),
                    }
                }
                self.declare(*element, &inner)
            }
            TypeKind::Subroutine {
                ret,
                params,
                variadic,
            } => {
                let mut list: Vec<_> =
                    params.iter().map(|&p| self.declare(p, "")).collect();
                if *variadic {
                    list.push("...".to_owned());
                }
                if list.is_empty() {
                    list.push("void".to_owned());
                }
                let inner =
                    format!("{}({})", parenthesize(inner), list.join(", "));
                self.declare(*ret, &inner)
            }
            _ => join(&self.name(die, ty), inner),
        }
    }

    /// Qualifiers bind to the pointer they follow, or else lead the type.
    fn qualify(
        &self,
        qualifier: &str,
        target: Option<DieId>,
        inner: &str,
    ) -> String {
        match target.and_then(|t| self.graph.types.get(&t)) {
            Some(Type {
                kind: TypeKind::Pointer { target },
                ..
            }) => self.declare(*target, &format!("*{qualifier} {inner}")),
            _ => format!("{qualifier} {}", self.declare(target, inner)),
        }
    }

    /// How a named, tagged or anonymous type is referred to.
    fn name(&self, die: DieId, ty: &Type) -> String {
        let id = self.canonical.of(die);
        match (&ty.kind, ty.name) {
            (TypeKind::Record { .. } | TypeKind::Enum { .. }, _) => match id {
                Some(id) => self.tag(id, ty),
                None => "/* missing */".to_owned(),
            },
            (_, Some(name)) => self.graph.str(name).to_owned(),
            _ => "/* unnamed */".to_owned(),
        }
    }
}

fn join(base: &str, inner: &str) -> String {
    if inner.is_empty() {
        base.to_owned()
    } else {
        format!("{base} {inner}")
    }
}

/// Pointers bind looser than arrays and calls, so `*p` needs parentheses
/// before either is applied to it.
fn parenthesize(inner: &str) -> String {
    if inner.starts_with('*') {
        format!("({inner})")
    } else {
        inner.to_owned()
    }
}
