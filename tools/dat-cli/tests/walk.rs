use melee_dat::{
    dwarf::{
        Annotation, Member, Type, TypeGraph, TypeKind, Unit,
        canonical::Canonical,
    },
    hsd::{Archive, ArchiveHeader, NamedSymbol},
    walk::{Issue, Walk, Walker},
};
use std::collections::HashMap;

#[test]
fn tagged_plain_union_uses_the_selected_record_size() {
    let mut graph = graph(None);
    ty(
        &mut graph,
        11,
        None,
        Some(8),
        TypeKind::Array {
            element: Some(1),
            dims: vec![Some(2)],
        },
    );
    let small = member(&mut graph, "small", 1, 0, &["dat:if(kind == 0)"]);
    let large = member(&mut graph, "large", 11, 0, &["dat:if(kind == 1)"]);
    ty(
        &mut graph,
        10,
        Some("PlainChoice"),
        Some(8),
        TypeKind::Record {
            union: true,
            declaration: false,
            members: vec![small, large],
        },
    );
    let canonical = Canonical::new(&graph);
    let macros = HashMap::new();
    for (kind, size, relocs) in
        [(0, 4, vec![]), (0, 8, vec![4]), (1, 8, vec![])]
    {
        let data = [123u32.to_be_bytes(), 456u32.to_be_bytes()].concat();
        let archive = Archive {
            header: ArchiveHeader {
                file_size: 0,
                data_size: size as u32,
                reloc_count: relocs.len() as u32,
                public_count: 0,
                extern_count: 0,
                version: [0; 12],
            },
            data: &data[..size],
            relocs,
            publics: vec![],
            externs: vec![],
            symbols: &[],
        };
        for array in [false, true] {
            let mut walker = Walker::new(&graph, &canonical, &macros, &archive);
            let binds = [("kind".into(), kind)];
            if array {
                walker.root_array(0, 10, Some(1), "root", &binds);
            } else {
                walker.root(0, 10, "root", &binds);
            }
            let walked = walker.finish();
            assert!(walked.issues.is_empty(), "{:?}", walked.issues);
            assert_eq!(walked.choices[&(0, canonical.of(10).unwrap())], kind as usize);
            assert_eq!(walked.extents[&0], if kind == 0 { 4 } else { 8 });
            assert!(walked.pointers.is_empty());
        }
    }
}

fn tag(graph: &mut TypeGraph, value: &str) -> Annotation {
    Annotation {
        name: Some(graph.strings.get_or_intern("btf_decl_tag")),
        value: Some(graph.strings.get_or_intern(value)),
    }
}

fn member(
    graph: &mut TypeGraph,
    name: &str,
    ty: u64,
    offset: u64,
    tags: &[&str],
) -> Member {
    Member {
        name: Some(graph.strings.get_or_intern(name)),
        ty: Some(ty),
        offset: Some(offset),
        bit_size: None,
        bit_offset: None,
        annotations: tags.iter().map(|value| tag(graph, value)).collect(),
    }
}

fn ty(
    graph: &mut TypeGraph,
    id: u64,
    name: Option<&str>,
    size: Option<u64>,
    kind: TypeKind,
) {
    let name = name.map(|name| graph.strings.get_or_intern(name));
    graph.types.insert(
        id,
        Type {
            unit: 0,
            name,
            byte_size: size,
            decl_file: None,
            scope: None,
            annotations: Vec::new(),
            kind,
        },
    );
}

/// A count followed by an inline array of tagged unions. Its elements
/// point to leaves through a DAT_TYPE typedef, and bind their own index.
fn graph(bound: Option<u64>) -> TypeGraph {
    let mut graph = TypeGraph::default();
    graph.units.push(Unit {
        name: None,
        address_size: 4,
        macros: Vec::new(),
    });
    ty(
        &mut graph,
        1,
        Some("u32"),
        Some(4),
        TypeKind::Base {
            encoding: gimli::DW_ATE_unsigned.0,
        },
    );
    let value = member(&mut graph, "value", 1, 0, &[]);
    ty(
        &mut graph,
        2,
        Some("Leaf"),
        Some(4),
        TypeKind::Record {
            union: false,
            declaration: false,
            members: vec![value],
        },
    );
    ty(
        &mut graph,
        3,
        None,
        Some(4),
        TypeKind::Pointer { target: None },
    );
    ty(
        &mut graph,
        4,
        Some("LeafPtr"),
        Some(4),
        TypeKind::Typedef { target: Some(3) },
    );
    let typed = tag(&mut graph, "dat:type(Leaf)");
    graph.types.get_mut(&4).unwrap().annotations.push(typed);
    let first = member(&mut graph, "first", 4, 0, &["dat:if(slot == 0)"]);
    let second = member(&mut graph, "second", 4, 0, &["dat:if(slot == 1)"]);
    ty(
        &mut graph,
        5,
        Some("Entry"),
        Some(4),
        TypeKind::Record {
            union: true,
            declaration: false,
            members: vec![first, second],
        },
    );
    ty(
        &mut graph,
        6,
        None,
        bound.map(|n| n * 4),
        TypeKind::Array {
            element: Some(5),
            dims: vec![bound],
        },
    );
    ty(
        &mut graph,
        8,
        Some("s32"),
        Some(4),
        TypeKind::Base {
            encoding: gimli::DW_ATE_signed.0,
        },
    );
    let count = member(&mut graph, "count", 8, 0, &[]);
    let entries = member(
        &mut graph,
        "entries",
        6,
        4,
        &["dat:count(count)", "dat:bind(slot, _index)"],
    );
    ty(
        &mut graph,
        7,
        Some("Root"),
        Some(4 + bound.unwrap_or(0) * 4),
        TypeKind::Record {
            union: false,
            declaration: false,
            members: vec![count, entries],
        },
    );
    graph
}

fn walk(graph: &TypeGraph, count: u32) -> Walk {
    let words = [count, 16, 20, 16, 123, 456];
    let data: Vec<_> = words.into_iter().flat_map(u32::to_be_bytes).collect();
    let archive = Archive {
        header: ArchiveHeader {
            file_size: 0,
            data_size: data.len() as u32,
            reloc_count: 3,
            public_count: 1,
            extern_count: 0,
            version: [0; 12],
        },
        data: &data,
        relocs: vec![4, 8, 12],
        // A symbol inside the array must not shorten an explicit count.
        publics: vec![NamedSymbol {
            offset: 8,
            symbol: 0,
        }],
        externs: Vec::new(),
        symbols: b"interior\0",
    };
    let canonical = Canonical::new(graph);
    let macros = HashMap::new();
    let mut walker = Walker::new(graph, &canonical, &macros, &archive);
    walker.root(0, 7, "root", &[]);
    walker.finish()
}

#[test]
fn inline_count_follows_all_elements_and_binds_each_index() {
    let graph = graph(None);
    let walked = walk(&graph, 2);
    assert!(walked.issues.is_empty(), "{:?}", walked.issues);
    assert_eq!(walked.pointers.len(), 2);
    assert!(walked.pointers.contains(&4));
    assert!(walked.pointers.contains(&8));
    assert!(!walked.pointers.contains(&12));
    assert!(walked.objects.contains_key(&16));
    assert!(walked.objects.contains_key(&20));
    let canonical = Canonical::new(&graph);
    let entry = canonical.of(5).unwrap();
    assert_eq!(walked.choices[&(4, entry)], 0);
    assert_eq!(walked.choices[&(8, entry)], 1);
    assert_eq!(walked.extents[&8], 12);
}

#[test]
fn inline_count_zero_follows_nothing() {
    let walked = walk(&graph(None), 0);
    assert!(walked.issues.is_empty());
    assert!(walked.pointers.is_empty());
    assert_eq!(walked.objects.len(), 1);
    assert_eq!(walked.extents.len(), 1);
    assert_eq!(walked.extents[&0], 4);
}

#[test]
fn inline_count_rejects_truncated_and_negative_counts() {
    let graph = graph(None);
    for count in [6, u32::MAX] {
        let walked = walk(&graph, count);
        assert_eq!(walked.issues.len(), 1);
        assert!(matches!(
            walked.issues.first(),
            Some(Issue::OutOfBounds { at: 4, .. })
        ));
        assert!(walked.pointers.is_empty());
        assert_eq!(walked.objects.len(), 1);
    }
}

#[test]
fn inline_count_respects_fixed_capacity() {
    let graph = graph(Some(2));
    let walked = walk(&graph, 1);
    assert!(walked.issues.is_empty());
    assert_eq!(walked.pointers.len(), 1);
    let walked = walk(&graph, 3);
    assert!(matches!(
        walked.issues.first(),
        Some(Issue::OutOfBounds { at: 4, .. })
    ));
    assert!(walked.pointers.is_empty());
}

/// Counted lists behind a fixed-size row of pointers. The binding belongs
/// to the root, so it must survive both the row and its pointer typedefs.
fn counted_lists(inline: bool, count: u32) -> (TypeGraph, Vec<u8>, Vec<u32>) {
    let mut graph = graph(None);
    graph.types.get_mut(&3).unwrap().kind =
        TypeKind::Pointer { target: Some(2) };
    let count_tag = tag(&mut graph, "dat:count(Root::count)");
    graph.types.get_mut(&4).unwrap().annotations = vec![count_tag];
    graph.types.get_mut(&6).unwrap().kind = TypeKind::Array {
        element: Some(4),
        dims: vec![Some(2)],
    };
    graph.types.get_mut(&6).unwrap().byte_size = Some(8);
    ty(
        &mut graph,
        9,
        None,
        Some(4),
        TypeKind::Pointer { target: Some(6) },
    );
    let count_member = member(&mut graph, "count", 1, 0, &[]);
    let rows = member(
        &mut graph,
        "rows",
        if inline { 6 } else { 9 },
        4,
        if inline {
            &["dat:bind(Root::count, count)"]
        } else {
            &["dat:extent", "dat:bind(Root::count, count)"]
        },
    );
    let root = graph.types.get_mut(&7).unwrap();
    root.byte_size = Some(if inline { 12 } else { 8 });
    root.kind = TypeKind::Record {
        union: false,
        declaration: false,
        members: vec![count_member, rows],
    };
    let words = if inline {
        vec![count, 24, 36, 0, 0, 0, 11, 12, 13, 21, 22, 23]
    } else {
        vec![count, 16, 0, 0, 24, 36, 11, 12, 13, 21, 22, 23]
    };
    let data = words.into_iter().flat_map(u32::to_be_bytes).collect();
    let relocs = if inline { vec![4, 8] } else { vec![4, 16, 20] };
    (graph, data, relocs)
}

#[test]
fn array_elements_keep_pointer_typedef_counts() {
    // The inline member takes the per-element binding path; the extent
    // pointer reaches a row whose elements take the ordinary array path.
    for (inline, count) in [(false, 3), (true, 3), (false, 0), (true, 0)] {
        let (graph, data, relocs) = counted_lists(inline, count);
        let archive = Archive {
            header: ArchiveHeader {
                file_size: 0,
                data_size: data.len() as u32,
                reloc_count: relocs.len() as u32,
                public_count: 0,
                extern_count: 0,
                version: [0; 12],
            },
            data: &data,
            relocs,
            publics: Vec::new(),
            externs: Vec::new(),
            symbols: &[],
        };
        let canonical = Canonical::new(&graph);
        let macros = HashMap::new();
        let mut walker = Walker::new(&graph, &canonical, &macros, &archive);
        walker.root(0, 7, "root", &[]);
        let walked = walker.finish();
        assert!(walked.issues.is_empty(), "{:?}", walked.issues);
        assert_eq!(walked.pointers.len(), if inline { 2 } else { 3 });
        if count > 0 {
            // Plain lists have one extent covering the entire count.
            assert_eq!(walked.extents.get(&24), Some(&36), "{inline}");
            assert_eq!(walked.extents.get(&36), Some(&48), "{inline}");
        } else {
            assert!(!walked.objects.contains_key(&24));
            assert!(!walked.objects.contains_key(&36));
        }
        assert!(!walked.extents.contains_key(&48));
    }
}

/// Follow an array of pointers annotated with `DAT_BYTE_SCRIPT`.
/// A 0x7F argument must not end the script. An unterminated script must not
/// receive an inferred extent.
#[test]
fn byte_scripts_end_by_command_length() {
    let mut graph = TypeGraph::default();
    graph.units.push(Unit {
        name: None,
        address_size: 4,
        macros: Vec::new(),
    });
    ty(
        &mut graph,
        1,
        Some("u8"),
        Some(1),
        TypeKind::Base {
            encoding: gimli::DW_ATE_unsigned_char.0,
        },
    );
    ty(
        &mut graph,
        2,
        None,
        Some(4),
        TypeKind::Pointer { target: Some(1) },
    );
    ty(
        &mut graph,
        3,
        Some("Script"),
        None,
        TypeKind::Typedef { target: Some(2) },
    );
    let script = tag(&mut graph, "dat:bytescript(cpuCommandLength(_command))");
    graph.types.get_mut(&3).unwrap().annotations = vec![script];
    ty(
        &mut graph,
        4,
        None,
        Some(12),
        TypeKind::Array {
            element: Some(3),
            dims: vec![Some(3)],
        },
    );
    let mut data = Vec::new();
    for word in [12u32, 16, 24] {
        data.extend(word.to_be_bytes());
    }
    data.extend([0x80, 0x7F, 0x7F, 0, 0x01, 0xC0, 0x01, 0x02, 0x7F, 0, 0, 0]);
    data.extend([0x01, 0x02]);
    let archive = Archive {
        header: ArchiveHeader {
            file_size: 0,
            data_size: data.len() as u32,
            reloc_count: 3,
            public_count: 0,
            extern_count: 0,
            version: [0; 12],
        },
        data: &data,
        relocs: vec![0, 4, 8],
        publics: Vec::new(),
        externs: Vec::new(),
        symbols: &[],
    };
    let canonical = Canonical::new(&graph);
    let macros = HashMap::new();
    let mut walker = Walker::new(&graph, &canonical, &macros, &archive);
    walker.root(0, 4, "root", &[]);
    let walked = walker.finish();
    assert_eq!(walked.pointers.len(), 3);
    assert_eq!(walked.extents.get(&12), Some(&15));
    assert_eq!(walked.extents.get(&16), Some(&21));
    assert!(!walked.extents.contains_key(&24));
    assert_eq!(walked.issues.len(), 1);
    assert!(matches!(
        walked.issues.first(),
        Some(Issue::OutOfBounds { at: 26, .. })
    ));
}
