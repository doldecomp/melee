use melee_dat::dwarf::{
    TypeGraph, TypeKind,
    canonical::Canonical,
    roots::{RootName, roots},
};
use std::{path::PathBuf, sync::LazyLock};

/// `MELEE_DWARF_ELF` (set by nix), or a single object from the `ppc-dwarf`
/// CMake preset, which is much faster to load. Only the default is skipped
/// when missing; a path given explicitly must exist.
static GRAPH: LazyLock<Option<TypeGraph>> = LazyLock::new(|| {
    if let Some(path) = std::env::var_os("MELEE_DWARF_ELF") {
        return Some(TypeGraph::load(PathBuf::from(path)).unwrap());
    }
    let path = PathBuf::from(env!("CARGO_MANIFEST_DIR")).join(
        "../../build/ppc-dwarf/CMakeFiles/melee.dir/src/melee/ft/fighter.c.obj",
    );
    if !path.exists() {
        eprintln!("skipping: {} not found", path.display());
        return None;
    }
    Some(TypeGraph::load(&path).unwrap())
});

fn record<'a>(graph: &'a TypeGraph, name: &str) -> &'a melee_dat::dwarf::Type {
    graph
        .named(name)
        .map(|(_, t)| t)
        .find(|t| {
            matches!(
                t.kind,
                TypeKind::Record {
                    declaration: false,
                    ..
                }
            )
        })
        .unwrap_or_else(|| panic!("no definition of {name}"))
}

#[test]
fn archive_header_layout() {
    let Some(graph) = GRAPH.as_ref() else { return };
    let header = record(graph, "HSD_ArchiveHeader");
    assert_eq!(header.byte_size, Some(0x20));
    let TypeKind::Record { members, .. } = &header.kind else {
        unreachable!()
    };
    let offsets: Vec<_> = members
        .iter()
        .map(|m| (graph.str(m.name.unwrap()), m.offset.unwrap()))
        .collect();
    assert_eq!(
        offsets[..3],
        [("file_size", 0), ("data_size", 4), ("nb_reloc", 8)]
    );
}

#[test]
fn joint_union_annotations() {
    let Some(graph) = GRAPH.as_ref() else { return };
    let joint = record(graph, "HSD_Joint");
    assert_eq!(joint.byte_size, Some(0x40));

    let TypeKind::Record { members, .. } = &joint.kind else {
        unreachable!()
    };
    let u = members
        .iter()
        .find(|m| m.name.map(|n| graph.str(n)) == Some("u"))
        .unwrap();
    assert_eq!(u.offset, Some(0x10));

    let TypeKind::Record {
        union: true,
        members,
        ..
    } = &graph.types[&u.ty.unwrap()].kind
    else {
        panic!("HSD_Joint.u is not a union");
    };
    // Each member's `btf_decl_tag`, without whitespace, which formatting
    // may change
    let tag = graph.strings.get("btf_decl_tag");
    let tags: Vec<_> = members
        .iter()
        .map(|m| {
            let values: Vec<String> = m
                .annotations
                .iter()
                .filter(|a| a.name == tag)
                .map(|a| graph.str(a.value.unwrap()).replace(' ', ""))
                .collect();
            (graph.str(m.name.unwrap()), values)
        })
        .collect();
    let tag = |value: &str| vec![value.replace(' ', "")];
    assert_eq!(
        tags,
        [
            (
                "dobjdesc",
                tag("dat:if(!(flags & (JOBJ_PTCL | JOBJ_SPLINE)))")
            ),
            ("spline", tag("dat:if((flags & JOBJ_SPLINE) != 0)")),
            ("ptcl", tag("dat:if((flags & JOBJ_PTCL) != 0)")),
        ]
    );
}

#[test]
fn macros_resolve_constants() {
    let Some(graph) = GRAPH.as_ref() else { return };
    let value = |name: &str| {
        graph
            .units
            .iter()
            .flat_map(|u| &u.macros)
            .find(|m| graph.str(m.name) == name)
            .map(|m| graph.str(m.value))
    };
    assert_eq!(value("JOBJ_SPLINE"), Some("(1 << 14)"));
    assert_eq!(value("JOBJ_PTCL"), Some("(1 << 5)"));
    assert!(value("union_type_ptcl(o)").is_some());
}

#[test]
fn canonical_covers_every_die() {
    let Some(graph) = GRAPH.as_ref() else { return };
    let canonical = Canonical::new(graph);
    assert!(graph.types.keys().all(|&die| canonical.of(die).is_some()));
    let dies: usize = canonical.types.iter().map(|t| t.dies.len()).sum();
    assert_eq!(dies, graph.types.len());
}

#[test]
fn canonical_joint() {
    let Some(graph) = GRAPH.as_ref() else { return };
    let canonical = Canonical::new(graph);
    let name = graph.strings.get("HSD_Joint").unwrap();

    let ids = canonical.named(name);
    let definition = ids
        .iter()
        .copied()
        .find(|&id| {
            matches!(
                canonical.ty(graph, id).kind,
                TypeKind::Record {
                    declaration: false,
                    ..
                }
            )
        })
        .unwrap();
    // The typedef and any forward declaration resolve to the one definition
    for &id in ids {
        if matches!(canonical.ty(graph, id).kind, TypeKind::Record { .. }) {
            assert_eq!(canonical.definition(graph, id), Some(definition));
        }
    }
    assert!(canonical.conflicts.iter().all(|c| c.name != name));

    let TypeKind::Record { members, .. } =
        &canonical.ty(graph, definition).kind
    else {
        unreachable!()
    };
    let u = members
        .iter()
        .find(|m| m.name.map(|n| graph.str(n)) == Some("u"))
        .unwrap();
    let union = canonical.of(u.ty.unwrap()).unwrap();
    assert_eq!(canonical.get(union).display.as_deref(), Some("HSD_Joint_u"));
}

#[test]
fn root_witnesses() {
    let path = PathBuf::from(env!("CARGO_MANIFEST_DIR")).join(
        "../../build/ppc-dwarf/CMakeFiles/melee.dir/src/melee/mn/mnmain.c.obj",
    );
    if !path.exists() {
        eprintln!("skipping: {} not found", path.display());
        return;
    }
    let graph = TypeGraph::load(&path).unwrap();
    let canonical = Canonical::new(&graph);
    let roots = roots(&graph, &canonical);
    let root = roots
        .iter()
        .find(|r| r.name == RootName::Literal("MenMainBack_Top_joint".into()))
        .expect("no witness for MenMainBack_Top_joint");
    let ty = &graph.types[&root.ty.unwrap()];
    assert_eq!(ty.name.map(|n| graph.str(n)), Some("HSD_Joint"));
    assert!(root.location(&graph).starts_with("melee/mn/mnmain.c:"));
}

#[test]
fn food_inline_count_from_dwarf_matches_the_archive() {
    use melee_dat::{
        hsd::Archive,
        walk::{Walker, macros},
    };
    let Some(graph) = GRAPH.as_ref() else { return };
    let files = std::env::var_os("MELEE_DAT_FILES")
        .map(PathBuf::from)
        .unwrap_or_else(|| {
            PathBuf::from(env!("CARGO_MANIFEST_DIR"))
                .join("../../orig/GALE01/files")
        });
    let path = files.join("ItCo.dat");
    if !path.exists() {
        eprintln!("skipping: {} not found", path.display());
        return;
    }
    let bytes = std::fs::read(path).unwrap();
    let archive = Archive::parse(&bytes).unwrap();
    let public = archive
        .publics
        .iter()
        .find(|p| {
            archive.symbol_at(p.symbol) == Some(b"itPublicData".as_slice())
        })
        .unwrap();
    let word = |at: u32| {
        u32::from_be_bytes(
            archive.data[at as usize..at as usize + 4]
                .try_into()
                .unwrap(),
        )
    };
    let kind = graph
        .types
        .values()
        .find_map(|ty| {
            let TypeKind::Enum { enumerators, .. } = &ty.kind else {
                return None;
            };
            enumerators
                .iter()
                .find(|e| e.name.map(|n| graph.str(n)) == Some("It_Kind_Foods"))
                .map(|e| e.value as u32)
        })
        .unwrap();
    let table = word(public.offset + 4);
    let article = word(table + 4 * kind);
    let attrs = word(article + 4);
    let count = word(attrs);
    assert!(count > 1);
    let die = graph
        .named("itFoodsAttributes")
        .find_map(|(die, ty)| {
            matches!(
                ty.kind,
                TypeKind::Record {
                    declaration: false,
                    ..
                }
            )
            .then_some(die)
        })
        .unwrap();
    let canonical = Canonical::new(graph);
    let macros = macros(graph);
    let mut walker = Walker::new(graph, &canonical, &macros, &archive);
    walker.root(attrs, die, "foods", &[]);
    let walked = walker.finish();
    assert!(walked.issues.is_empty(), "{:?}", walked.issues);
    for i in 0..count {
        let entry = attrs + 4 + i * 16;
        assert!(walked.pointers.contains(&entry), "food {i}");
        assert_eq!(walked.extents[&entry], entry + 16);
        assert!(walked.objects.contains_key(&word(entry)), "food {i} joint");
    }
    assert!(!walked.extents.contains_key(&(attrs + 4 + count * 16)));
}
