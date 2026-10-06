use melee_dat::hsd::{Archive, PackedMotion};

fn archive(symbol: &[u8]) -> Vec<u8> {
    let mut bytes = vec![0; 32];
    bytes.extend_from_slice(&[0; 4]);
    bytes.extend_from_slice(&[0; 8]); // public at data offset 0
    bytes.extend_from_slice(symbol);
    bytes.push(0);
    let size = bytes.len() as u32;
    bytes[..4].copy_from_slice(&size.to_be_bytes());
    bytes[4..8].copy_from_slice(&4u32.to_be_bytes());
    bytes[12..16].copy_from_slice(&1u32.to_be_bytes());
    bytes
}

fn packed() -> (Vec<u8>, Vec<PackedMotion<'static>>) {
    let first = archive(b"first");
    let unused = archive(b"unused");
    let last = archive(b"last");
    let mut bytes = first.clone();
    // Actual packed files retain arbitrary bytes between their archives.
    bytes.resize(bytes.len().next_multiple_of(32), 0xA5);
    bytes.extend_from_slice(&unused);
    bytes.resize(bytes.len().next_multiple_of(32), 0x5A);
    let at = bytes.len() as u32;
    bytes.extend_from_slice(&last);
    let motions = vec![
        PackedMotion {
            offset: 0,
            size: first.len() as u32,
            symbol: b"first",
        },
        PackedMotion {
            offset: at,
            size: last.len() as u32,
            symbol: b"last",
        },
        PackedMotion {
            offset: at,
            size: last.len() as u32,
            symbol: b"last",
        },
        PackedMotion {
            offset: u32::MAX,
            size: 0,
            symbol: b"ignored",
        },
    ];
    (bytes, motions)
}

#[test]
fn duplicate_empty_and_unreferenced_motions() {
    let (bytes, motions) = packed();
    let check = Archive::check_packed_motions(&bytes, &motions).unwrap();
    assert_eq!(check.checked, 3);
    assert_eq!(check.unreferenced, 1);
    assert_eq!(Archive::parse_packed(&bytes).unwrap().len(), 3);
}

#[test]
fn motion_must_start_at_an_archive_boundary() {
    let (bytes, mut motions) = packed();
    motions[1].offset += 4;
    let error = Archive::check_packed_motions(&bytes, &motions).unwrap_err();
    assert!(error.to_string().contains("motion 1"));
    assert!(error.to_string().contains("not an archive boundary"));
}

#[test]
fn motion_size_is_exact_not_the_padded_size() {
    let (bytes, mut motions) = packed();
    motions[0].size = motions[0].size.next_multiple_of(32);
    let error = Archive::check_packed_motions(&bytes, &motions).unwrap_err();
    assert!(error.to_string().contains("table size"));
}

#[test]
fn motion_name_must_exist_in_the_selected_archive() {
    let (bytes, mut motions) = packed();
    motions[1].symbol = b"first";
    let error = Archive::check_packed_motions(&bytes, &motions).unwrap_err();
    assert!(error.to_string().contains("no public symbol `first`"));
}

#[test]
fn unreferenced_archives_still_need_valid_headers() {
    let (mut bytes, motions) = packed();
    let unused = archive(b"first").len().next_multiple_of(32);
    bytes[unused..unused + 4].copy_from_slice(&u32::MAX.to_be_bytes());
    assert!(Archive::check_packed_motions(&bytes, &motions).is_err());
}
