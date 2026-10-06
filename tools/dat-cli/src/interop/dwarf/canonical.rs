//! Groups the DIEs of a [`TypeGraph`] that describe the same type.
//!
//! Every unit repeats the types of the headers it includes, so one C type is
//! usually many DIEs. Two DIEs are the same type when their signatures are
//! equal: named records, enums and typedefs are referred to by name, which
//! breaks every possible cycle, and everything else is compared by structure.
//! Nothing is copied from the graph; a canonical type is a set of DIEs, read
//! through its representative.

use super::{
    Annotation, DieId, Str, Type, TypeGraph, TypeKind, annotation::DatTag,
};
use std::collections::HashMap;

/// Index into [`Canonical::types`].
#[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub struct CanonId(pub u32);

#[derive(Debug)]
pub struct CanonType {
    /// The first DIE with this signature, whose [`Type`] describes it.
    pub rep: DieId,
    pub dies: Vec<DieId>,
    /// For display only: the type's own name, else the typedef naming it,
    /// else the member path it was declared at (e.g. `HSD_Joint::u`).
    pub display: Option<String>,
}

/// A name with more than one distinct definition.
#[derive(Debug)]
pub struct Conflict {
    pub name: Str,
    pub variants: Vec<CanonId>,
}

#[derive(Debug, Default)]
pub struct Canonical {
    pub types: Vec<CanonType>,
    by_die: HashMap<DieId, CanonId>,
    by_name: HashMap<Str, Vec<CanonId>>,
    /// Definitions of one name that disagree within a file or in a header.
    pub conflicts: Vec<Conflict>,
    /// Distinct types that share a name, each declared in its own source
    /// file. Legal C, but ambiguous when looking a type up by name.
    pub ambiguities: Vec<Conflict>,
    /// Named types declared inside a function rather than at file scope.
    pub locals: Vec<CanonId>,
}

impl Canonical {
    pub fn new(graph: &TypeGraph) -> Self {
        let mut sigs = Signatures::new(graph);
        let mut canonical = Canonical::default();
        let mut by_sig = HashMap::new();

        for (&die, ty) in &graph.types {
            let sig = sigs.definition(die);
            let id = *by_sig.entry(sig).or_insert_with(|| {
                let id = CanonId(canonical.types.len() as u32);
                canonical.types.push(CanonType {
                    rep: die,
                    dies: Vec::new(),
                    display: ty.name.map(|n| graph.str(n).to_owned()),
                });
                match (ty.name, ty.scope) {
                    (Some(_), Some(_)) => canonical.locals.push(id),
                    (Some(name), None) => {
                        canonical.by_name.entry(name).or_default().push(id)
                    }
                    (None, _) => {}
                }
                id
            });
            canonical.types[id.0 as usize].dies.push(die);
            canonical.by_die.insert(die, id);
        }

        canonical.find_conflicts(graph);
        canonical.name_anonymous(graph);
        canonical
    }

    pub fn get(&self, id: CanonId) -> &CanonType {
        &self.types[id.0 as usize]
    }

    /// The canonical type a DIE belongs to.
    pub fn of(&self, die: DieId) -> Option<CanonId> {
        self.by_die.get(&die).copied()
    }

    /// Every type `roots` lead to, through members, pointers, arrays,
    /// typedefs and qualifiers.
    pub fn reachable(
        &self,
        graph: &TypeGraph,
        roots: impl IntoIterator<Item = DieId>,
    ) -> std::collections::BTreeSet<CanonId> {
        let mut reached = std::collections::BTreeSet::new();
        let mut queue: Vec<DieId> = roots.into_iter().collect();
        while let Some(die) = queue.pop() {
            let Some(id) = self.of(die) else { continue };
            if !reached.insert(id) {
                continue;
            }
            let ty = &graph.types[&self.get(id).rep];
            // And the types `DAT_TYPE` names, which the walk follows
            let named = |annotations: &[Annotation]| {
                annotations
                    .iter()
                    .filter_map(|a| {
                        match DatTag::parse(graph.str(a.value?))? {
                            DatTag::Type(name) => Some(name),
                            _ => None,
                        }
                    })
                    .flat_map(|name| self.lookup(graph, &name))
                    .collect::<Vec<_>>()
            };
            queue.extend(named(&ty.annotations));
            // A declaration's definition, as the walk resolves it
            if let TypeKind::Record {
                declaration: true, ..
            } = ty.kind
            {
                queue.extend(
                    self.definition(graph, id).map(|d| self.get(d).rep),
                );
            }
            if let TypeKind::Record { members, .. } = &ty.kind {
                for member in members {
                    queue.extend(named(&member.annotations));
                }
            }
            let mut next = |t: &Option<DieId>| queue.extend(*t);
            match &ty.kind {
                TypeKind::Pointer { target }
                | TypeKind::Typedef { target }
                | TypeKind::Const { target }
                | TypeKind::Volatile { target }
                | TypeKind::Restrict { target } => next(target),
                TypeKind::Array { element, .. } => next(element),
                TypeKind::Record { members, .. } => {
                    members.iter().for_each(|m| next(&m.ty));
                }
                TypeKind::Enum { underlying, .. } => next(underlying),
                TypeKind::Subroutine { .. }
                | TypeKind::Base { .. }
                | TypeKind::Unspecified => {}
            }
        }
        reached
    }

    /// Every canonical type with this name, whether a typedef or a tag.
    pub fn named(&self, name: Str) -> &[CanonId] {
        self.by_name.get(&name).map_or(&[], Vec::as_slice)
    }

    /// The representatives of the types a C type name refers to, e.g.
    /// `HSD_Joint`, `struct HSD_Joint`, `u8*` or `void*`.
    pub fn lookup(&self, graph: &TypeGraph, name: &str) -> Vec<DieId> {
        if let Some(target) = name.strip_suffix('*') {
            let targets: Vec<_> = self
                .lookup(graph, target.trim_end())
                .into_iter()
                .filter_map(|die| self.of(die))
                .collect();
            return self
                .types
                .iter()
                .filter(|canon| {
                    matches!(
                        graph.types[&canon.rep].kind,
                        TypeKind::Pointer { target: pointee }
                            if match pointee {
                                Some(t) => self.of(t).is_some_and(|t| targets.contains(&t)),
                                // DWARF has no type DIE for void.
                                None => target.trim() == "void",
                            }
                    )
                })
                .map(|canon| canon.rep)
                .collect();
        }
        let name = graph.strings.get(name.trim_start_matches("struct "));
        name.into_iter()
            .flat_map(|name| self.named(name))
            .map(|&id| self.get(id).rep)
            .collect()
    }

    /// The type behind a canonical ID, read from its representative DIE.
    pub fn ty<'g>(&self, graph: &'g TypeGraph, id: CanonId) -> &'g Type {
        &graph.types[&self.get(id).rep]
    }

    /// A declaration's definition, when its name has exactly one.
    pub fn definition(
        &self,
        graph: &TypeGraph,
        id: CanonId,
    ) -> Option<CanonId> {
        let ty = self.ty(graph, id);
        let TypeKind::Record {
            union,
            declaration: true,
            ..
        } = ty.kind
        else {
            return Some(id);
        };
        let mut definitions =
            self.named(ty.name?).iter().copied().filter(|&other| {
                matches!(
                    self.ty(graph, other).kind,
                    TypeKind::Record { union: u, declaration: false, .. }
                        if u == union
                )
            });
        let definition = definitions.next()?;
        definitions.next().is_none().then_some(definition)
    }

    /// `sizeof` a type, looking through typedefs and qualifiers and
    /// resolving declarations to their definitions; `None` for `void`,
    /// functions and incomplete types.
    pub fn byte_size(&self, graph: &TypeGraph, die: DieId) -> Option<u64> {
        let ty = graph.types.get(&die)?;
        match &ty.kind {
            TypeKind::Typedef { target }
            | TypeKind::Const { target }
            | TypeKind::Volatile { target }
            | TypeKind::Restrict { target } => {
                self.byte_size(graph, (*target)?)
            }
            TypeKind::Array { element, dims } => {
                let element = self.byte_size(graph, (*element)?)?;
                dims.iter()
                    .try_fold(element, |size, dim| Some(size * (*dim)?))
            }
            TypeKind::Record {
                declaration: true, ..
            } => {
                let definition = self.definition(graph, self.of(die)?)?;
                self.ty(graph, definition).byte_size
            }
            TypeKind::Subroutine { .. } => None,
            TypeKind::Pointer { .. } => ty
                .byte_size
                .or(Some(graph.units[ty.unit].address_size.into())),
            _ => ty.byte_size,
        }
    }

    fn find_conflicts(&mut self, graph: &TypeGraph) {
        let mut names: Vec<_> = self.by_name.iter().collect();
        names.sort_unstable_by_key(|(_, ids)| ids[0]);
        for (&name, ids) in names {
            // Group the definitions by namespace: typedefs, tags, the rest
            let mut by_kind: HashMap<u8, Vec<CanonId>> = HashMap::new();
            for &id in ids {
                let namespace = match self.ty(graph, id).kind {
                    TypeKind::Typedef { .. } => 0,
                    TypeKind::Record {
                        declaration: true, ..
                    } => continue,
                    TypeKind::Record { .. } | TypeKind::Enum { .. } => 1,
                    _ => 2,
                };
                by_kind.entry(namespace).or_default().push(id);
            }
            let mut groups: Vec<_> = by_kind.into_values().collect();
            groups.sort_unstable();
            for variants in groups {
                if variants.len() < 2 {
                    continue;
                }
                let mut files: Vec<_> = variants
                    .iter()
                    .map(|&v| self.ty(graph, v).decl_file)
                    .collect();
                let in_sources = files
                    .iter()
                    .all(|f| f.is_some_and(|f| graph.str(f).ends_with(".c")));
                files.sort_unstable();
                files.dedup();
                let conflict = Conflict { name, variants };
                if in_sources && files.len() == conflict.variants.len() {
                    self.ambiguities.push(conflict);
                } else {
                    self.conflicts.push(conflict);
                }
            }
        }
    }

    fn name_anonymous(&mut self, graph: &TypeGraph) {
        // `typedef struct { ... } Foo`
        for index in 0..self.types.len() {
            let ty = &graph.types[&self.types[index].rep];
            if let (Some(name), TypeKind::Typedef { target: Some(t) }) =
                (ty.name, &ty.kind)
            {
                self.name_if_anonymous(*t, || graph.str(name).to_owned());
            }
        }
        // Members of an anonymous type, e.g. `_reent::_new`, or `Foo::@2`
        // for the anonymous member at index 2. Repeat until nothing changes,
        // so that types nested in other anonymous types are named too.
        let mut changed = true;
        while changed {
            changed = false;
            for index in 0..self.types.len() {
                let Some(parent) = self.types[index].display.clone() else {
                    continue;
                };
                let TypeKind::Record { members, .. } =
                    &graph.types[&self.types[index].rep].kind
                else {
                    continue;
                };
                for (index, member) in members.iter().enumerate() {
                    let Some(ty) = member.ty else { continue };
                    changed |=
                        self.name_if_anonymous(ty, || match member.name {
                            Some(name) => {
                                format!("{parent}::{}", graph.str(name))
                            }
                            None => format!("{parent}::@{index}"),
                        });
                }
            }
        }
    }

    /// Whether the type was anonymous and has now been named.
    fn name_if_anonymous(
        &mut self,
        die: DieId,
        name: impl FnOnce() -> String,
    ) -> bool {
        if let Some(id) = self.of(die) {
            let ty = &mut self.types[id.0 as usize];
            if ty.display.is_none() {
                ty.display = Some(name());
                return true;
            }
        }
        false
    }
}

/// Interned signatures, so comparing two types is comparing two integers.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
struct SigId(u32);

#[derive(Debug, Clone, PartialEq, Eq, Hash)]
enum Sig {
    Void,
    /// A reference to a DIE that is not a type in the graph.
    Missing,
    Base {
        name: Option<Str>,
        size: Option<u64>,
        encoding: u8,
    },
    Unspecified(Option<Str>),
    /// A reference to a named record or enum.
    Tag(Str),
    /// A reference to a typedef.
    TypedefRef(Str),
    Typedef {
        name: Option<Str>,
        target: SigId,
        annotations: Vec<(Option<Str>, Option<Str>)>,
    },
    Pointer(SigId),
    Const(SigId),
    Volatile(SigId),
    Restrict(SigId),
    Array {
        element: SigId,
        dims: Vec<Option<u64>>,
    },
    Record {
        name: Option<Str>,
        union: bool,
        declaration: bool,
        size: Option<u64>,
        annotations: Vec<(Option<Str>, Option<Str>)>,
        members: Vec<MemberSig>,
    },
    Enum {
        name: Option<Str>,
        size: Option<u64>,
        underlying: SigId,
        enumerators: Vec<(Option<Str>, i64)>,
    },
    Subroutine {
        ret: SigId,
        params: Vec<SigId>,
        variadic: bool,
    },
}

#[derive(Debug, Clone, PartialEq, Eq, Hash)]
struct MemberSig {
    name: Option<Str>,
    offset: Option<u64>,
    bit_size: Option<u64>,
    bit_offset: Option<u64>,
    annotations: Vec<(Option<Str>, Option<Str>)>,
    ty: SigId,
}

struct Signatures<'g> {
    graph: &'g TypeGraph,
    ids: HashMap<Sig, SigId>,
    definitions: HashMap<DieId, SigId>,
    references: HashMap<DieId, SigId>,
}

impl<'g> Signatures<'g> {
    fn new(graph: &'g TypeGraph) -> Self {
        Signatures {
            graph,
            ids: HashMap::new(),
            definitions: HashMap::new(),
            references: HashMap::new(),
        }
    }

    fn intern(&mut self, sig: Sig) -> SigId {
        let next = SigId(self.ids.len() as u32);
        *self.ids.entry(sig).or_insert(next)
    }

    /// How a type is referred to from another: named records, enums and
    /// typedefs by name, anything else by its full definition.
    fn reference(&mut self, target: Option<DieId>) -> SigId {
        let Some(die) = target else {
            return self.intern(Sig::Void);
        };
        if let Some(&sig) = self.references.get(&die) {
            return sig;
        }
        let sig = match self.graph.types.get(&die) {
            None => self.intern(Sig::Missing),
            Some(Type {
                name: Some(name),
                kind: TypeKind::Record { .. } | TypeKind::Enum { .. },
                ..
            }) => self.intern(Sig::Tag(*name)),
            Some(Type {
                name: Some(name),
                kind: TypeKind::Typedef { .. },
                ..
            }) => self.intern(Sig::TypedefRef(*name)),
            Some(_) => self.definition(die),
        };
        self.references.insert(die, sig);
        sig
    }

    /// Follow a chain of typedefs to the type it names.
    fn resolve(&self, mut target: Option<DieId>) -> Option<DieId> {
        while let Some(Type {
            kind: TypeKind::Typedef { target: next },
            ..
        }) = target.and_then(|die| self.graph.types.get(&die))
        {
            target = *next;
        }
        target
    }

    /// A type's full signature.
    fn definition(&mut self, die: DieId) -> SigId {
        if let Some(&sig) = self.definitions.get(&die) {
            return sig;
        }
        let graph = self.graph;
        let Some(ty) = graph.types.get(&die) else {
            return self.intern(Sig::Missing);
        };
        let annotations = annotations(&ty.annotations);
        let sig = match &ty.kind {
            TypeKind::Base { encoding } => Sig::Base {
                name: ty.name,
                size: ty.byte_size,
                encoding: *encoding,
            },
            TypeKind::Unspecified => Sig::Unspecified(ty.name),
            TypeKind::Pointer { target } => {
                Sig::Pointer(self.reference(*target))
            }
            // Compared by what they finally name, so that e.g. `size_t`
            // defined via `__size_t` equals `size_t` defined directly
            TypeKind::Typedef { target } => Sig::Typedef {
                name: ty.name,
                target: self.reference(self.resolve(*target)),
                annotations,
            },
            TypeKind::Const { target } => Sig::Const(self.reference(*target)),
            TypeKind::Volatile { target } => {
                Sig::Volatile(self.reference(*target))
            }
            TypeKind::Restrict { target } => {
                Sig::Restrict(self.reference(*target))
            }
            TypeKind::Array { element, dims } => Sig::Array {
                element: self.reference(*element),
                dims: dims.clone(),
            },
            TypeKind::Record {
                union,
                declaration,
                members,
            } => Sig::Record {
                name: ty.name,
                union: *union,
                declaration: *declaration,
                size: ty.byte_size,
                annotations,
                members: members
                    .iter()
                    .map(|m| MemberSig {
                        name: m.name,
                        offset: m.offset,
                        bit_size: m.bit_size,
                        bit_offset: m.bit_offset,
                        annotations: self::annotations(&m.annotations),
                        ty: self.reference(m.ty),
                    })
                    .collect(),
            },
            TypeKind::Enum {
                underlying,
                enumerators,
            } => Sig::Enum {
                name: ty.name,
                size: ty.byte_size,
                underlying: self.reference(*underlying),
                enumerators: enumerators
                    .iter()
                    .map(|e| (e.name, e.value))
                    .collect(),
            },
            TypeKind::Subroutine {
                ret,
                params,
                variadic,
            } => Sig::Subroutine {
                ret: self.reference(*ret),
                params: params.iter().map(|&p| self.reference(p)).collect(),
                variadic: *variadic,
            },
        };
        let sig = self.intern(sig);
        self.definitions.insert(die, sig);
        sig
    }
}

fn annotations(annotations: &[Annotation]) -> Vec<(Option<Str>, Option<Str>)> {
    annotations.iter().map(|a| (a.name, a.value)).collect()
}
