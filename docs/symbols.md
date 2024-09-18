# `symbols.txt`

This file contains all symbols for a module, one per line.

Example line:

```
__dt__13mDoExt_bckAnmFv = .text:0x800DD2EC; // type:function size:0x5C scope:global align:4
```

## Format

Numbers can be written as decimal or hexadecimal. Hexadecimal numbers must be prefixed with `0x`.

Comment lines starting with `//` or `#` are permitted, but are currently **not** preserved when updating the file.

```
symbol_name = section:address; // [attributes]
```

- `symbol_name` - The name of the symbol. (For C++, this is the mangled name, e.g. `__dt__13mDoExt_bckAnmFv`)
- `section` - The section the symbol is in.
- `address` - The address of the symbol. For DOLs, this is the absolute address (e.g. `0x80001234`). For RELs, this is the section-relative address (e.g. `0x1234`).

### Attributes

All attributes are optional, and are separated by spaces.

- `type:` The symbol type. `function`, `object`, or `label`.
- `size:` The size of the symbol.
- `scope:` The symbol's visibility. `global` (default), `local` or `weak`.
- `align:` The symbol's alignment.
- `data:` The data type used when writing disassembly. `byte`, `2byte`, `4byte`, `8byte`, `float`, `double`, `int`, `short`, `string`, `wstring`, `string_table`, or `wstring_table`.
- `hidden` Marked as "hidden" in the generated object. (Only used for extab)
- `force_active` Marked as ["exported"](comment_section.md) in the generated object, and added to `FORCEACTIVE` in the generated `ldscript.lcf`. Prevents the symbol from being deadstripped.
- `noreloc` Prevents the _contents_ of the symbol from being interpreted as addresses. Used for objects containing data that look like pointers, but aren't.
- `noexport` When `export_all` is enabled, this excludes the symbol from being exported. Used for symbols that are affected by linker `-code_merging`.
- `stripped` Indicates a symbol that was stripped by the linker. Used for symbols that affect the [common BSS inflation bug](common_bss.md), despite not existing in the final binary.
