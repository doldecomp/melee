# Common BSS

When passed the `-common on` flag, `mwcc` will generate global BSS symbols as **common**. The linker deduplicates common symbols with the same name, and allocates an area at the **end** of `.bss` for them.

This is a legacy feature, allowing uninitialized global variables to be defined in headers without linker errors:

```c
// foo.h
int foo;
```

With `-common on`, any TU that includes `foo.h` will define `foo` as a **common** symbol. The linker will deduplicate `foo` across TUs, similar to weak symbols. Common symbols are then generated at the **end** of `.bss`, after all other `.bss` symbols.

With `-common off`, `foo` would be defined as a **global** symbol, and the linker would error out with a duplicate symbol error if `foo.h` was included in multiple TUs.

In `splits.txt`, common BSS can be defined with the `common` attribute:

```yaml
foo.cpp:
	.text       start:0x80047E5C end:0x8004875C
	.ctors      start:0x803A54C4 end:0x803A54C8
	.data       start:0x803B1B40 end:0x803B1B60
	.bss        start:0x803DF828 end:0x803DFA8C
	.bss        start:0x8040D4AC end:0x8040D4D8 common
```

As shown above, a file can contain both regular `.bss` and common `.bss`. Marking common `.bss` appropriately is important for determining the final link order.

## Detection

Example from Pikmin 2:
```
00016e60 00000c 805069c0  1 .bss 	utilityU.a PSMainSide_CreaturePrm.cpp
00016e60 00000c 805069c0  4 @3464 	utilityU.a PSMainSide_CreaturePrm.cpp
00016e6c 000048 805069cc  4 saoVVOutput_direction___Q214JStudio_JStage14TAdaptor_light 	JSystem.a object-light.cpp
00016eb4 0000d0 80506a14  4 saoVVOutput___Q214JStudio_JStage14TAdaptor_actor 	JSystem.a object-actor.cpp
```

In this example, we see a symbol from `utilityU.a PSMainSide_CreaturePrm.cpp`. We know that this file is very close to the _end_ of the link order. Afterwards, there's a symbol from `JSystem.a object-light.cpp`, which is very close to the _beginning_ of the link order.

A file can't be both at the beginning and end of the link order, so it's a strong indication that `saoVVOutput_direction___Q214JStudio_JStage14TAdaptor_light` marks the beginning of the common BSS section.

One other indication from this example is the lack of a `.bss` section symbol from `JSystem.a object-actor.cpp` and any following files in the link order. Section symbols aren't generated for common BSS.

Without a map, it's harder to tell if there's a common BSS section, but guesses can be made. When looking at XREFs in Ghidra, if a symbol is close to the _end_ of `.bss`, but has XREFs from various addresses close to the _beginning_ of `.text`, it could be an indication of common BSS.

For games built with older versions of the linker, the inflation bug (described below) can also be used to detect common BSS.

## Inflation bug

In older versions of the linker (<= GC 2.6?), when calculating the size of common symbols, the linker will accidentally set the size of the first common symbol in a TU to the size of the _entire_ common section in that TU.

Example from Pikmin 2:

```
# Section Addr | Size | Addr | Alignment | Name | File
00017260 000188 80506dc0  4 mPadList__10JUTGamePad 	JSystem.a JUTGamePad.cpp
000173e8 000030 80506f48  4 mPadStatus__10JUTGamePad 	JSystem.a JUTGamePad.cpp
00017418 0000c0 80506f78  4 mPadButton__10JUTGamePad 	JSystem.a JUTGamePad.cpp
000174d8 000040 80507038  4 mPadMStick__10JUTGamePad 	JSystem.a JUTGamePad.cpp
00017518 000040 80507078  4 mPadSStick__10JUTGamePad 	JSystem.a JUTGamePad.cpp
00017558 00000c 805070b8  4 sPatternList__19JUTGamePadLongPress 	JSystem.a JUTGamePad.cpp
```

In this example, `mPadList__10JUTGamePad` is the first common symbol in the TU, and was inflated to include the size of all other common symbols in the TU. In reality, it's only supposed to be `0xC` bytes, given `0x188 - 0x30 - 0xC0 - 0x40 - 0x40 - 0xC`.

This can be useful to determine if symbols are in the same TU without a map: if a `.bss` symbol is much larger than expected, it could be the first common symbol in a TU. One can subtract the sizes of following symbols to find the true size of the symbol, along with the end of the TU's common symbols.

To reproduce this behavior, the `.comment` section must be present in the object. See [`.comment` section](comment_section.md) for more details.
