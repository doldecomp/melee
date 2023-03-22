# dadosod
---

#### Facilitate the process of creating a decompilation project for a given Wii/Gamecube game

# Features
 - Disassembly DOL
   - Guess/Calculate common sections name
   - Divide each section into his own file
   - Divide the bss section appropriately (`.bss`, `.sbss` and `.sbss2`)
   - Partial Data Type Detection for Data Section (No `.incbin`)
   - Linker Script (With appropriate section alignment)

# Usage

### Command Line Options
|Command|Description|
|-|-|
|`dadosod dol`|[Disassembly a dol executable](#dols-command-options)|

### Dol's command options
|Command|Description||
|-|-|-|
|`<dol_file_path>`|[Path of the dol file]()|**Required**|


# Planned Features
 - Disassembly DOL
   - Detect `.init`'s `_rom_copy_info` and `_bss_init_info` (**Wii Only**)
   - Automatic Output Shift-ability
   - Library Splitting
   - Symbol Map
 - Disassembly REL
 - Disassembly RSO

# Special Thanks
- [camthesaxman](https://github.com/camthesaxman) - Author of the original `doldisasm.py` script

### From where the name comes
`dadosod` is `disassembly` in Gaelic
