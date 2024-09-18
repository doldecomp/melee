# `splits.txt`

This file contains file splits for a module.

Example:

```yaml
path/to/file.cpp:
	.text       start:0x80047E5C end:0x8004875C
	.ctors      start:0x803A54C4 end:0x803A54C8
	.data       start:0x803B1B40 end:0x803B1B60
	.bss        start:0x803DF828 end:0x803DFA8C
	.bss        start:0x8040D4AC end:0x8040D4D8 common
```

## Format

```yaml
path/to/file.cpp: [file attributes]
    section     [section attributes]
    ...
```

- `path/to/file.cpp` The name of the source file, usually relative to `src`. The file does **not** need to exist to start.  
  This corresponds to an entry in `configure.py` for specifying compiler flags and other options.

### File attributes

- `comment:` Overrides the `mw_comment_version` setting in [`config.yml`](/config/GAMEID/config.example.yml) for this file. See [Comment section](comment_section.md).
  - `comment:0` is used to disable `.comment` section generation for a file that wasn't compiled with `mwcc`.  
  Example: `TRK_MINNOW_DOLPHIN/ppc/Export/targsupp.s: comment:0`  
  This file was assembled and only contains label symbols. Generating a `.comment` section for it will crash `mwld`.

- `order:` Allows influencing the resolved link order of objects. This is **not required**, as decomp-toolkit will generate the link order automatically. This can be used to fine-tune the link order for ambiguous cases.  
  Example:
  ```
  file1.cpp: order:0
    ...

  file2.cpp: order:1
    ...

  file3.cpp: order:2
    ...
  ```
  This ensures that `file2.cpp` is always anchored in between 1 and 3 when resolving the final link order.

### Section attributes

- `start:` The start address of the section within the file. For DOLs, this is the absolute address (e.g. `0x80001234`). For RELs, this is the section-relative address (e.g. `0x1234`).
- `end:` The end address of the section within the file.
- `align:` Specifies the alignment of the section. If not specified, the default alignment for the section is used.
- `rename:` Writes this section under a different name when generating the split object. Used for `.ctors$10`, etc.
- `common` Only valid for `.bss`. See [Common BSS](common_bss.md).
- `skip` Skips this data when writing the object file. Used for ignoring data that's linker-generated.
