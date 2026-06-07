# Melee PR Review QA Standards

Use this as the review checklist for decomp PRs and worker output. Code should
look like maintainable original C, and matching-only tactics should be backed by
local build, objdiff, or regression evidence.

## Source Rules

### Recover Natural Loops

Do:

- Use `for`, `while`, or `do while` when repeated blocks vary only by an index,
  pointer, or counter.
- Test an exact `int` counter when relying on MWCC loop unrolling.
- Index from the original base pointer when later code still needs that base.

Do not:

- Leave repeated generated-looking blocks just because they currently match.
- Mutate the only copy of a base pointer if the original address is needed
  later.
- Keep unrolled code unless cleaner loop forms were checked and failed.

### Prefer Typed Fields Over Pointer Math

Do prefer access forms in this order:

1. real field on the actual struct
2. correct `GroundVars`, `FighterVars`, or `ItemVars` union arm
3. temporary internal struct with explicit padding
4. `M2C_FIELD`
5. raw pointer arithmetic only as a last resort

Do:

- Replace raw offsets with real fields when the type is known.
- Model item, fighter, ground, and HSD object data at the correct offset instead
  of borrowing unrelated fields.
- Treat `M2C_FIELD` as temporary bridge code.

Do not:

- Use `((u8*) obj) + offset` when a field, union arm, helper, or temporary struct
  can express the access.
- Add new `M2C_FIELD` uses when the real type can reasonably be recovered.
- Treat raw pointer math as finished source style.

### Recognize Header Inlines

Do:

- Map expanded header asserts back to the inline helper in the owning header.
- For `jobj.h` asserts, use the line number to identify the matching
  `HSD_JObj*` inline.
- Prefer existing `HSD_JObjSet*` and `HSD_JObjGet*` forms when they represent
  the source-level operation.
- Use `GET_JOBJ` only when surrounding source shape or objdiff evidence shows it
  is the right source-level form.

Do not:

- Keep expanded `__assert("jobj.h", line, ...)` code when the header inline is
  identifiable.
- Treat `GET_JOBJ` as automatically correct; some sites need it, and some need
  an explicit JObj access form instead.
- Redefine header macros or local helper names just to force an inline.
- Manually expand an inline without objdiff evidence.

### Use Project Assert And Report Macros

Do:

- Use `HSD_ASSERT(line, cond)` for plain asserts.
- Use `HSD_ASSERTMSG(line, cond, msg)` when the message string is real.
- Use `HSD_ASSERTREPORT(line, cond, ...)` when the report side effect is real.
- Use `OSReport(...)` or `OSPanic(__FILE__, ...)` when the source has that
  behavior.

Do not:

- Leave direct `__assert` blocks when an existing project macro represents the
  same source.
- Invent fake assert strings, fake report globals, or dummy storage to force a
  match.
- Drop a real report or panic side effect while cleaning up an assert.

### Keep Literals Inline Unless Data Evidence Says Otherwise

Do:

- Keep constants, strings, and float literals inline when there is no real data
  ownership evidence.
- Verify section ownership before promoting a literal to a named symbol.
- Use named data only when symbol metadata, section placement, or surrounding
  source supports it.

Do not:

- Create static string or float symbols just because generated code exposed an
  address.
- Add fake data anchors, dummy static functions, or data-order globals as normal
  source style.
- Move literals out of source without checking `.data`, `.rodata`, `.sdata`, or
  `.sdata2` ownership.

### Use Canonical Control Flow And Macros

Do:

- Try a grouped `switch` for range dispatch or repeated adjacent branches.
- Try ternaries for select-like assignments.
- Use project macros such as `ABS`, `MIN`, `MAX`, and `CLAMP` when they express
  the natural source.
- Convert goto-heavy generated output into structured C when it can still match.

Do not:

- Preserve branch ladders or generated gotos before testing ordinary source
  forms.
- Replace readable control flow with fake code solely to match one local
  sequence.
- Ignore common expression macros when the assembly shape suggests them.

## Matching Tactic Rules

### Require Evidence For Matching Tactics

Do require targeted evidence before keeping:

- `PAD_STACK` or `FORCE_PAD_STACK`
- declaration order changes
- branch-local or widened local lifetimes
- dummy stack locals
- volatile locals
- manual inline expansion
- direct global or extern access instead of a struct path
- temporary structs with offset padding

Do not:

- Use a matching tactic if it shifts nearby functions, changes data order, or
  hides a real type.
- Treat a tactic as permanent style without a cleanup reason.
- Keep local/register/stack churn that has no objdiff benefit.

### Avoid New Pragmas, `register`, And Inline Assembly

Do:

- Scope unavoidable pragmas as tightly as possible.
- Prove any pragma or inline-assembly exception does not affect adjacent
  functions.
- Remove `register` and similar keyword steering when it is not required.

Do not:

- Add new `#pragma global_optimizer off` for normal source.
- Leave unbalanced or empty `#pragma push` / `#pragma pop` blocks.
- Add unexplained `#pragma dont_inline`.
- Use inline assembly outside SDK-like code unless there is no reasonable C
  alternative.

## Data, Naming, And File Rules

### Respect Data Sections And TU Splits

Do:

- Treat `.sdata`, `.sdata2`, `.sbss`, `.rodata`, and `.data` placement as part
  of the match.
- Fix symbol size and type metadata in `symbols.txt` when metadata is wrong.
- Use local `@NNN` labels for compiler-local data when appropriate.
- Use assert filenames, string clusters, object names, and float groups as TU
  split evidence.

Do not:

- Add dummy C storage to compensate for incorrect symbol metadata.
- Move data across TUs without checking split boundaries.
- Treat data section placement as cosmetic.

### Be Conservative With Names

Do:

- Use semantic names when the role is evidenced.
- Keep `fn_<addr>`, `lbl_<addr>`, or module-address names when semantics are not
  proven.
- Use short local role names such as `fp`, `ip`, `gp`, `gobj`, and `jobj` when
  those roles are clear.
- Clean up generated names once the role is known.

Do not:

- Invent semantic names from guesses.
- Rename address-style symbols before the source meaning is supported.
- Leave `temp_rXX`-style names when a clear local role is known.

### Keep Headers And Includes Truthful

Do:

- Update prototypes when a function body proves the signature.
- Remove stale `UNK_RET` and `UNK_PARAMS`.
- Put declarations in the real owning header.
- Use established local include style, such as `<MSL/math.h>` or
  `<baselib/gobj.h>`, when nearby code does.
- Run `python configure.py --require-protos` before handoff when applicable.

Do not:

- Add fake local declarations when the real header should own them.
- Leave mismatched prototypes after recovering a function body.
- Hide missing prototypes behind source-local declarations.

### Keep Formatting And Mechanical Changes Reviewable

Do:

- Keep formatting-only sweeps separate from semantic matching work when
  possible.
- Apply broad style conventions gradually or only in files already being touched.
- Include a from/to table or reproducible command for large rename or labeling
  changes.
- Keep the corresponding main header first in `.c` files so the header proves it
  can stand alone.
- Respect 80-column expectations, EditorConfig checks, `clang-format`, and
  scoped `clang-format off/on` blocks around MWERKS inline-asm cases.

Do not:

- Mix broad mechanical churn with matching changes when it obscures review.
- Reformat unrelated files just because a PR touches nearby code.
- Leave formatter exceptions open-ended after a rebase.
- Force repeated history rewrites when the normal final merge is already
  squashed.

## Verification Rules

Do:

- Run the narrow touched-object build when possible.
- Run full `ninja` before handoff when the blast radius is nontrivial.
- Run objdiff or checkdiff for every claimed matched symbol or unit.
- Inspect adjacent functions when changing pragmas, includes, data, literals, or
  TU ownership.
- Report broken matches, fuzzy regressions, and metric regressions explicitly.
- Keep tool or regression-gate changes separate from decomp source changes.

Do not:

- Claim a match without local build and objdiff/checkdiff evidence.
- Hide regressions behind a broad "builds locally" statement.
- Mix tooling changes and decomp source changes when either can be reviewed
  separately.
