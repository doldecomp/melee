# Getting Started

See [Dependencies](dependencies.md) first.

1. [Create a new repository from this template](https://github.com/new?template_name=dtk-template&template_owner=encounter), then clone it.

2. Rename `orig/GAMEID` to the game's ID. (For example, `GLZE01` for _The Legend of Zelda: The Wind Waker_.)

3. Extract your game to `orig/[GAMEID]`. In Dolphin, use "Extract Entire Disc" for GameCube games, or use "Data Partition" -> "Extract Entire Partition" for Wii games.

4. Rename `config/GAMEID` to the game's ID and modify `config/[GAMEID]/config.yml` appropriately, using [`config.example.yml`](/config/GAMEID/config.example.yml) as a reference. If the game doesn't use RELs, the `modules` list in `config.yml` can be removed.

5. Generate a `config/[GAMEID]/build.sha1` file for verification. This file is a list of SHA-1 hashes for each build artifact. One possible way:

    ```sh
    dtk shasum orig/[GAMEID]/sys/main.dol orig/[GAMEID]/files/*.rel -o config/[GAMEID]/build.sha1
    ```

6. Modify the paths in `config/[GAMEID]/build.sha1` to point to the `build` directory instead of `orig`. The DOL will be built at `build/[GAMEID]/main.dol`, and modules will be built at `build/[GAMEID]/[module_name]/[module_name].rel`.

7. Update `VERSIONS` in [`configure.py`](/configure.py) with the game ID.

8. Run `python configure.py` to generate the initial `build.ninja`.

9. Run `ninja` to perform initial analysis.

If all goes well, the initial `symbols.txt` and `splits.txt` should be automatically generated. Though it's likely it won't build yet. See [Post-analysis](#post-analysis) for next steps.

## Using a `.map`

If the game has `.map` files matching the DOL (and RELs, if applicable), they can be used to fill out `symbols.txt` and `splits.txt` automatically during the initial analysis.

Add the `map` key to `config.yml`, pointing to the `.map` file from the game disc. (For example, `orig/[GAMEID]/files/main.map`.) For RELs, add a `map` key to each module in `config.yml`.

If the game uses [common BSS](common_bss.md), be sure to set `common_start` as well. (See [`config.example.yml`](/config/GAMEID/config.example.yml).) Otherwise, the final link order may fail to be determined.

Once the initial analysis is completed, `symbols.txt` and `splits.txt` will be generated from the map information. **Remove** the `map` fields from `config.yml` to avoid conflicts.

## Post-analysis

After the initial analysis, `symbols.txt` and `splits.txt` will be generated. These files can be modified to adjust symbols and split points.

If the game uses C++ exceptions, it's required to set up a split for the `__init_cpp_exceptions.cpp` file. This differs between linker versions.

Often indicated by the following error:

```
#   runtime sources 'global_destructor_chain.c' and
#   '__init_cpp_exceptions.cpp' both need to be updated to latest version.
```

### GC 1.0 - 2.6 linkers

```yaml
# splits.txt
Runtime.PPCEABI.H/__init_cpp_exceptions.cpp:
	.text       start:0x803294EC end:0x80329568
	.ctors      start:0x80338680 end:0x80338684
	.dtors      start:0x80338820 end:0x80338828
	.sdata      start:0x803F67F0 end:0x803F67F8
```

`.text`:  
Find the following symbols in `symbols.txt`:

```
GetR2__Fv = .text:0x803294EC; // type:function size:0x8 scope:local align:4
__fini_cpp_exceptions = .text:0x803294F4; // type:function size:0x34 scope:global align:4
__init_cpp_exceptions = .text:0x80329528; // type:function size:0x40 scope:global align:4
```

The split end is the address of `__init_cpp_exceptions` + size.

`.ctors`:  
Find the address of `__init_cpp_exception_reference` or `_ctors` in symbols.txt.  
Always size 4.

`.dtors`:  
Look for the address of `__destroy_global_chain_reference` or `_dtors` in symbols.txt.  
If `__fini_cpp_exceptions_reference` is present, it's size 8, otherwise size 4

`.sdata`:  
Find the following symbol in `symbols.txt`:

```
fragmentID = .sdata:0x803F67F0; // type:object size:0x4 scope:local align:4 data:4byte
```

The split end includes any inter-TU padding, so it's usually size 8.

### GC 2.7+ and Wii linkers

```yaml
# splits.txt
Runtime.PPCEABI.H/__init_cpp_exceptions.cpp:
	.text       start:0x80345C34 end:0x80345CA4
	.ctors      start:0x803A54A0 end:0x803A54A4 rename:.ctors$10
	.dtors      start:0x803A56A0 end:0x803A56A4 rename:.dtors$10
	.dtors      start:0x803A56A4 end:0x803A56A8 rename:.dtors$15
	.sdata      start:0x80418CA8 end:0x80418CB0
```

`.text`:  
Find the following symbols in `symbols.txt`:

```
__fini_cpp_exceptions = .text:0x80345C34; // type:function size:0x34 scope:global
__init_cpp_exceptions = .text:0x80345C68; // type:function size:0x3C scope:global
```

The split end is the address of `__init_cpp_exceptions` + size.

`.ctors$10`:  
Find the address of `__init_cpp_exception_reference` or `_ctors` in symbols.txt.  
Always size 4.

`.dtors$10`:  
Look for the address of `__destroy_global_chain_reference` or `_dtors` in symbols.txt.  
Always size 4.

`.dtors$15`:  
Look for the address of `__fini_cpp_exceptions_reference` in symbols.txt.  
Always size 4.

`.sdata`:  
Find the following symbol in `symbols.txt`:

```
fragmentID = .sdata:0x80418CA8; // type:object size:0x4 scope:local data:4byte
```

The split end includes any inter-TU padding, so it's usually size 8.
