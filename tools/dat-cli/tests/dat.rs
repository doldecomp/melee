use melee_dat::hsd::Archive;
use std::path::PathBuf;

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
