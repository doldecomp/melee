# DAT symbol files

`config/GALE01/dat_symbols.txt` supplements the roots recorded by loaders
in the DWARF build. Each line names one public symbol or alias:

```text
PlyCaptain5K_Share_ACTION_Wait1_figatree = PlCaAJ.dat:0x24BC; // type:FigaTree
map_plit = GrNLa.dat:0x51D34; // terminated:0
ftDataEmblem_unused_joint = PlFe.dat:0x3AD70; // type:HSD_Joint
```

The archive is a path relative to the config's `base`. The address is a
32-bit offset from the start of that archive's data, after its 32-byte
header. Names, archive paths and addresses must be explicit; `*` and `?`
wildcards are unsupported. Names must be C identifiers. Each name occurs
once per archive.

Files such as `PlCaAJ.dat` pack several archives, padded to 32 bytes. The
first uses the file name; later archives use `file.dat@0xOFFSET`, where
`OFFSET` is the archive header's byte offset in the file. The address after
`:` remains relative to that archive's data. This is the same identity
shown by `symbols coverage`.

An entry matching a public symbol's name and offset supplies its metadata.
The loader still determines its type and bindings; `type:` supplies a type
when no loader does. A count can supplement a loader-derived type without
repeating it, as in `map_plit` above. Loader-derived roots need no entry
unless they need additional metadata.

An entry that does not name a public symbol gives its data a C alias and
starts another walk after the public roots. It needs a `type:`. These
aliases cover structurally verified export leftovers that no public symbol
or pointer reaches. They establish a root for inference, not a game loader.
Aliases are visited in file order and have their own binding scope.

## Attributes

Attributes follow `//`, separated by spaces. They mirror DAT annotations:

| Attribute | Meaning |
| --- | --- |
| `type:T` | Root type, like `DAT_TYPE(T)`; accepts `T` or `T*`. |
| `count:N` | Exactly `N` elements, like `DAT_COUNT(N)`; zero is valid. |
| `extent` | Elements up to the next public symbol or pointer target. |
| `terminated:V` | Through the first unrelocated element whose first word (or whole value if smaller) equals `V`. |
| `script:S` | Alias is a command script, like `DAT_SCRIPT(S)`. |

Without a count, the root is one element. Integers accept decimal or
`0x` hexadecimal notation. Script arguments contain no whitespace, for
example `script:ftAction_803C0870` or
`script:itCommandLength(_command)`. Unknown attributes are retained when
printing the file. Standalone `//` lines and blank lines are ignored;
keep format explanations and entry rationale here rather than in the
symbol file.

## Entry details

- Stage `yakumono_param` types vary by archive. Pokemon Stadium's four
  transformation archives repeat its parameters; only `GrPs.dat`'s are
  read. Stages whose parameters are unread retain their one zero word.
- `mnNameAutoName*` and `mnNameRefuseName*` lists end with a pointer to an
  empty string. Their explicit counts include that entry. The unused
  default-name roots contain only the terminator.
- Texture and palette publics without a reached descriptor use `type:u8
  extent` or `type:u16 extent`; their exact dimensions remain unknown.
- `ftDemo*MotionFile*` publics are byte arrays containing archives relocated
  by the game at runtime. This differs from a file packing archives at
  its top level.
- `ItCo.dat` data at `0x50A0–0x7DDC` copies `0x2FC–0x303C` with pointers
  to the originals. The `ItCo_copy_*` aliases use the originals' types.
