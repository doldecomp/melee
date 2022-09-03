# calcprogress
 Progress checker for GC/Wii decompilation projects that use the CodeWarrior linker + devkitPPC GNU assembler
## Limitations
  - When assembly and source files have the same name, only the first one will be seen in the map, as calcprogress cannot distinguish between them.
    - To work around this, you can:
      - Link the assembly portion before the decompiled source
      - Name the object files differently (i.e. `file.s.o` vs. `file.c.o`)
## Usage
```
usage: calcprogress.py [-h] (--dol DOL | --rel REL) --map MAP [--asm-root [ASM_ROOT]] [--asm-src-ext [ASM_SRC_EXT]] [--asm-obj-ext [ASM_OBJ_EXT]]
                       [--obj-files-mk [OBJ_FILES_MK]] [--old-map [OLD_MAP]]

optional arguments:
  --asm-root [ASM_ROOT]
                        Path to asm (default: "asm/")
  --asm-src-ext [ASM_SRC_EXT]
                        Custom assembly source file extension (default: ".s")
  --asm-obj-ext [ASM_OBJ_EXT]
                        Custom assembly object file extension (default: ".o")
  --obj-files-mk [OBJ_FILES_MK]
                        Path to obj_files.mk (default: "/obj_files.mk")
  --old-map [OLD_MAP]
                        Whether to use the old map format (default: False)

required arguments:
  --dol DOL             Path to DOL
  --rel REL             Path to REL
  --map MAP             Path to symbol map
```
- **Use the `--asm-src-ext`/`--asm-obj-ext` arguments if your project does not use `.s` and `.o` respectively.**
  
## Customization
- Custom library/range progress tracking
    - Create `Slice` objects for areas of the DOL you would like to specifically track progress, such as libraries.
    - For each group of slices you would like to track, put them into a list, which should be inserted into `EXEC_SLICE_GROUPS` through `SliceGroup` objects.
    - Progress for slice groups in `EXEC_SLICE_GROUPS` will be shown separately, underneath the general code/data progress.
    - Example:
        ```py
        NW4R_SLICES = [
            # (Slice start, Slice end)
            NW4R_CODE = Slice(0x800076e0, 0x800838a8),
            NW4R_RODATA = Slice(0x80375780, 0x80378c18)
        ]

        EXEC_SLICE_GROUPS = [
            # (Group name, Slice list)
            SliceGroup("NW4R", NW4R_SLICES)
        ]
        ```
        ```
        Code sections: 134324 / 3473024 bytes in src (3.867638%)
        Data sections: 142162 / 1518492 bytes in src (9.362051%)
        Slices:
            NW4R: 104628 / 508360 bytes in src (20.581478%)
        ```
- Custom progress display
   - In `calcprogress.py`, configure the following functions for your project:
     - `exec_progress_callback`: Any custom main exectuable (DOL/REL) progress display
     - `slice_group_progress_callback`: Any custom slice group progress display
  
## Design
 - Rather than calculating the size of decompiled source files, this script opts to get the size of the non-decompiled, assembly files:
1. Base DOL is read to get the total code/data size
2. Symbol map is parsed to find all section header symbols in each source file.
   - Section header symbols refer to the first symbol in a given section (`.section` directive).
   - With sections containing pure assembly, the size of the first (header) symbol will contain the size of the entire section (before alignment), so it is used to easily find the size of the section's assembly.
   - In version r39 and earlier of devkitPPC, its assembler would title these header symbols with the name of the section. r40 now uses the name of the first symbol: regardless, it still reveals the whole section size.
3. `obj_files.mk` is parsed to determine what assembly files are going to be linked.
   - This is not required by this design but saves time by not parsing any additional assembly that is not needed.
4. All assembly listed above is parsed for `.section` directives, which are tracked by their size and type (code/data).
5. Assembly section sizes are summed up against the code/data sum found by the DOL's sections.
  
## Credits
 - Twilight Princess team from zeldaret, for the concept of calculating progress by finding the size of the assembly, rather than trying to assume what has been decompiled from the map