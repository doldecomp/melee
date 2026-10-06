use melee_dat::dol::Dol;

fn word(bytes: &mut [u8], at: usize, value: u32) {
    bytes[at..at + 4].copy_from_slice(&value.to_be_bytes());
}

fn fixture() -> Vec<u8> {
    let mut bytes = vec![0; 0x128];
    // A text and data section whose file order differs from address order.
    word(&mut bytes, 0, 0x120);
    word(&mut bytes, 0x48, 0x80001000);
    word(&mut bytes, 0x90, 8);
    word(&mut bytes, 7 * 4, 0x100);
    word(&mut bytes, 0x48 + 7 * 4, 0x80300000);
    word(&mut bytes, 0x90 + 7 * 4, 16);
    word(&mut bytes, 0xD8, 0x80400000);
    word(&mut bytes, 0xDC, 8);
    word(&mut bytes, 0x100, 0x80300008);
    word(&mut bytes, 0x104, 2);
    bytes[0x108..0x110].copy_from_slice(b"PlMr\0xxx");
    bytes[0x120..0x128].copy_from_slice(b"ABCDtext");
    bytes
}

#[test]
fn maps_virtual_addresses_and_strings_to_initialized_bytes() {
    let bytes = fixture();
    let dol = Dol::parse(&bytes).unwrap();
    assert_eq!(dol.bytes(0x80001000, 8).unwrap(), b"ABCDtext");
    let pointer = u32::from_be_bytes(
        dol.bytes(0x80300000, 4).unwrap().try_into().unwrap(),
    );
    assert_eq!(dol.string(pointer).unwrap(), "PlMr");
    assert_eq!(dol.bytes(0x80300004, 4).unwrap(), 2u32.to_be_bytes());
}

#[test]
fn rejects_bss_gaps_and_ranges_crossing_a_section_boundary() {
    let bytes = fixture();
    let dol = Dol::parse(&bytes).unwrap();
    for (address, size) in [
        (0x80400000, 4), // BSS
        (0x80300010, 1), // one past the data section
        (0x8030000F, 2), // begins in data but extends beyond it
        (0x80001008, 4), // gap after text
        (u32::MAX, 2),
    ] {
        assert!(dol.bytes(address, size).is_err());
    }
    assert!(
        dol.string(0x80001000)
            .unwrap_err()
            .to_string()
            .contains("unterminated")
    );
}

#[test]
fn rejects_truncated_and_invalid_sections() {
    assert!(Dol::parse(&[0; 0xFF]).is_err());
    let mut truncated = fixture();
    truncated.pop();
    assert!(Dol::parse(&truncated).is_err());
    for (at, value) in [
        (0, 0xFF),            // file data overlaps the header
        (0, u32::MAX),        // file range outside input
        (0x48, u32::MAX - 3), // virtual address overflow
        (0x48, 0x80300008),   // overlapping initialized sections
    ] {
        let mut bytes = fixture();
        word(&mut bytes, at, value);
        assert!(Dol::parse(&bytes).is_err(), "at {at:#X}: {value:#X}");
    }
}

#[test]
fn ignores_unused_section_slots() {
    let mut bytes = fixture();
    word(&mut bytes, 4, u32::MAX);
    word(&mut bytes, 0x48 + 4, u32::MAX);
    let dol = Dol::parse(&bytes).unwrap();
    assert_eq!(dol.string(0x80300008).unwrap(), "PlMr");
}
