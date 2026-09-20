# Audio record layouts

The synth cleanup distinguishes three representations:

- SFX file records contain two 32-bit header words and 0x40 bytes per voice.
  They do not contain a native pointer or native struct tail padding.
- Loaded records add a hash link and sound id. Their allocation and cursor
  stride include native alignment padding. A bank owns one allocation containing
  its header and variable-sized group records; byte offsets are used only when
  crossing those record boundaries.
- AX addresses and SRC ratios contain named high and low 16-bit fields.
  Portable code combines and splits these values explicitly. A union overlay
  does not provide byte-order conversion.

`SFX_GROUP_FILE_HEADER_SIZE` measures the serialized part of the group header;
`SFX_GROUP_RUNTIME_OVERHEAD` measures everything added in memory. In particular,
`sizeof(SfxGroup) - offsetof(SfxGroup, voice_count)` is not the file header size:
with 64-bit pointers it also counts four bytes of tail padding. The loader uses
`memmove` when expansion overlaps its staged input.

The default source uses typed PStream voice and loop-state members. The
`MUST_MATCH` branches retain the retail compiler's word-index expressions,
word overlays, overlapping forward copy, and address-load instruction. These
branches serve binary reconstruction; they are not portable implementations.
Keep compiler-specific expressions here rather than changing the runtime types
or making the default code reinterpret unrelated objects. A new shared spelling
can replace a branch when both the native tests and retail build pass.

The first PStream data callback has the actual four-argument DevCom signature.
Those parameter slots replace its former 16-byte artificial stack pad; no
function-pointer cast is needed.

## Validation

After configuring the project, run:

```sh
python3 tools/tests/synth_portability.py
ninja
```

The native test compiles the actual private implementation with Clang, ASan,
and UBSan. It exercises both load callbacks with adjacent stereo and mono
records, relocation across halfword carries and negative deltas, non-looping
voices, repeated SRC conversion, and a rumble script with a counted loop.
The fixture supplies host-order scalars. It does not implement big-endian file
loading or emulate GameCube devices, and passing it does not establish that the
whole audio backend runs on a different platform.

The matching build must still reproduce `config/GALE01/build.sha1`. Compare
changed objects with objdiff as well, and run the repository's source checks and
Clang syntax checks. Keep source fixed while compiling and reporting progress
so the object report and linked binary describe the same revision.
