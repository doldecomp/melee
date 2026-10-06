use melee_dat::dtk::SymbolFile;

#[test]
fn reads_dtk_symbols_and_optional_sizes() {
    let symbols = SymbolFile::parse(
        "\n # comment\n // comment\n\
        ftData_Table_Unk0 = .data:0x803C0FC8; // type:object size:0x108 scope:global data:4byte\n\
        __dt__13mDoExt_bckAnmFv = .text:2147483648; // size:92 align:4\n\
        label = extab:0X80300000; // hidden\n\
        absolute = ABS:123;\n\
        empty_comment = .data:0; //\n",
    )
    .unwrap();
    assert_eq!(symbols.entries.len(), 5);
    let table = symbols.lookup("ftData_Table_Unk0").unwrap();
    assert_eq!(table.section, ".data");
    assert_eq!(table.address, 0x803C0FC8);
    assert_eq!(table.size, Some(0x108));
    let function = symbols.lookup("__dt__13mDoExt_bckAnmFv").unwrap();
    assert_eq!(function.address, 0x80000000);
    assert_eq!(function.size, Some(92));
    assert_eq!(symbols.lookup("label").unwrap().size, None);
    assert_eq!(symbols.lookup("absolute").unwrap().section, "ABS");
    assert_eq!(symbols.lookup("empty_comment").unwrap().size, None);
}

#[test]
fn repeated_local_names_do_not_prevent_global_lookup() {
    let symbols = SymbolFile::parse(
        "@219 = .data:0x80000000; // scope:local\n\
        @219 = .data:0x80000004; // scope:local\n\
        global = .data:0x80000008; // size:4\n",
    )
    .unwrap();
    assert_eq!(symbols.lookup("global").unwrap().address, 0x80000008);
    assert!(
        symbols
            .lookup("@219")
            .unwrap_err()
            .to_string()
            .contains("ambiguous")
    );
    assert!(
        symbols
            .lookup("missing")
            .unwrap_err()
            .to_string()
            .contains("no symbol")
    );
}

#[test]
fn malformed_addresses_and_sizes_report_the_line() {
    for bad in [
        "x = .data:0x100000000;",
        "x = .data:4294967296;",
        "x = .data:0x;",
        "x = .data:-1;",
        "x = .data:0; // size:",
        "x = .data:0; // size:0x100000000",
        "x = .data:0; // size:4junk",
        "x = .data:0; // size:4 size:8",
        "x = .data:0",
        "x = .data:0; trailing",
    ] {
        let error =
            SymbolFile::parse(&format!("// comment\n{bad}")).unwrap_err();
        assert!(error.to_string().contains("line 2"), "{bad}: {error}");
    }
}
