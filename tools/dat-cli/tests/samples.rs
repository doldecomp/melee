use melee_dat::samples::INFERRED;
use object::{Object, ObjectSection, ObjectSymbol, SymbolKind};
use std::{collections::BTreeMap, fs, path::PathBuf};

fn inferred_symbols(path: PathBuf) -> BTreeMap<String, u64> {
    let bytes = fs::read(&path).unwrap();
    let object = object::File::parse(&*bytes).unwrap();
    let Some(section) = object.section_by_name(INFERRED) else {
        return BTreeMap::new();
    };
    object
        .symbols()
        .filter(|symbol| {
            symbol.kind() == SymbolKind::Data
                && symbol.section_index() == Some(section.index())
        })
        .map(|symbol| (symbol.name().unwrap().to_owned(), symbol.size()))
        .collect()
}

/// Inspect a real samples build: no original archives or generated objects
/// are stored in the repository. An explicitly supplied build must exist.
#[test]
fn complete_units_include_every_inferred_symbol() {
    let dir = if let Some(path) = std::env::var_os("MELEE_DAT_BUILD") {
        PathBuf::from(path)
    } else {
        let dir = PathBuf::from(env!("CARGO_MANIFEST_DIR"))
            .join("../../build/GALE01/dat");
        if !dir.join("objdiff.json").exists() {
            eprintln!("skipping: no DAT samples build found");
            return;
        }
        dir
    };
    let project: serde_json::Value =
        serde_json::from_slice(&fs::read(dir.join("objdiff.json")).unwrap())
            .unwrap();
    let (mut units, mut symbols) = (0, 0);
    for unit in project["units"].as_array().unwrap() {
        if unit["metadata"]["complete"] != true {
            continue;
        }
        units += 1;
        let target =
            inferred_symbols(dir.join(unit["target_path"].as_str().unwrap()));
        let base =
            inferred_symbols(dir.join(unit["base_path"].as_str().unwrap()));
        for (name, size) in target {
            symbols += 1;
            assert_eq!(
                base.get(&name),
                Some(&size),
                "{} is complete but {name} ({size} bytes) is missing or has the wrong size in the base",
                unit["name"].as_str().unwrap()
            );
        }
    }
    eprintln!("checked {units} complete units and {symbols} inferred symbols");
}
