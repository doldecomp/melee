use melee_dat::{
    hsd::{Archive, archive_name},
    symbols::SymbolFile,
};
use std::{collections::BTreeMap, path::PathBuf};

/// `MELEE_DAT_DIR`, or the project's extracted disc files. Read at run time
/// so that a checkout without the disc still compiles.
fn dat_paths() -> Vec<PathBuf> {
    let dir = std::env::var_os("MELEE_DAT_DIR")
        .map(PathBuf::from)
        .unwrap_or_else(|| {
            PathBuf::from(env!("CARGO_MANIFEST_DIR"))
                .join("../../orig/GALE01/files")
        });
    let Ok(entries) = std::fs::read_dir(&dir) else {
        return Vec::new();
    };
    let mut paths: Vec<_> = entries
        .filter_map(|e| Some(e.ok()?.path()))
        .filter(|p| {
            let name = p.file_name().unwrap_or_default().to_string_lossy();
            name.ends_with(".dat")
        })
        .collect();
    paths.sort();
    paths
}

#[test]
fn size_matches_header() {
    let paths = dat_paths();
    if paths.is_empty() {
        eprintln!("skipping: no DAT files found");
        return;
    }
    for path in paths {
        let bytes = std::fs::read(&path).unwrap();
        let archives = Archive::parse_packed(&bytes)
            .unwrap_or_else(|e| panic!("{}: {e}", path.display()));
        let (at, last) = archives.last().expect("no archives");
        // The last archive may be padded to 32 bytes like the others
        let end = at + last.header.file_size as usize;
        assert!(
            (end..=end.next_multiple_of(32)).contains(&bytes.len()),
            "{}: archives end at {end:#X}, file is {:#X}",
            path.display(),
            bytes.len()
        );
    }
}

#[test]
fn explicit_symbols_match_real_archive_locations() {
    let paths = dat_paths();
    if paths.is_empty() {
        assert!(
            std::env::var_os("MELEE_DAT_DIR").is_none(),
            "no DAT files in MELEE_DAT_DIR"
        );
        eprintln!("skipping: no DAT files found");
        return;
    }
    let repo = PathBuf::from(env!("CARGO_MANIFEST_DIR")).join("../..");
    let symbols = SymbolFile::parse(
        &std::fs::read_to_string(repo.join("config/GALE01/dat_symbols.txt"))
            .unwrap(),
    )
    .unwrap();
    let mut entries = BTreeMap::<_, Vec<_>>::new();
    for entry in symbols.entries() {
        entries
            .entry(entry.archive.as_str())
            .or_default()
            .push(entry);
    }
    let (mut publics, mut aliases) = (0, 0);
    for path in paths {
        let bytes = std::fs::read(&path).unwrap();
        let file = path.file_name().unwrap().to_str().unwrap();
        for (at, archive) in Archive::parse_packed(&bytes).unwrap() {
            let name = archive_name(file, at);
            for entry in entries.remove(name.as_str()).unwrap_or_default() {
                if let Some((_, public)) = archive
                    .named_publics()
                    .find(|(name, _)| *name == entry.name.as_bytes())
                {
                    assert_eq!(entry.address, public.offset, "{entry}");
                    publics += 1;
                } else {
                    assert!(entry.ty.is_some(), "alias needs a type: {entry}");
                    assert!(
                        entry.address < archive.header.data_size,
                        "{entry}"
                    );
                    aliases += 1;
                }
            }
        }
    }
    assert!(
        entries.is_empty(),
        "entries reference absent archives: {:?}",
        entries.keys()
    );
    eprintln!("checked {publics} public entries and {aliases} aliases");
}
