# <a name="heading"></a>Melee Coding Style

This document is to act as a guideline for how you should submit Pull Requests.

# Sections

- [Introduction](#introduction)
- [Coding Style and Formatting](#coding-style-and-formatting)
- [Compiler Notes](#compiler-notes)
- [Pull Requests](#prs)
- [AI Assistance](#ai)


# <a name="introduction"></a>Introduction

This document aims to clarify the coding standard required for a Pull Request to
be accepted.

While not all code submitted at this time conforms to this standard, it is the
intention of the project to correct it in time.

# <a name="coding-style-and-formatting"></a>Coding Style and Formatting

- [Caveats](#caveats)
- [Auto formatting](#auto-formatting)
- [Functions](#functions)
- [Structs](#structs)
- [Conditionals](#conditionals)
- [Variables](#variables)
- [Primitives](#primitives)
- [Enums](#enums)
- [Literals](#literals)
- [Headers](#headers)

## <a name="caveats"></a>Caveats

The original source is the gold standard for this decompilation project.

While the style-guide below should be closely followed, there are times where
convention may be reasonably broken in order to more closely reflect what the
original developers wrote.  Some strings embedded in the binary provide some
indication about what some things were named.

In cases where there is a clear connection between a string embedded in the
binary and an identifier in the decompiled code, we break convention and
prioritize the identifier name from the original source.

## <a name="auto-formatting"></a>Auto Formatting

`clang-format` should be run on all C code in `src`. The easiest way to do this
is to install and run [`pre-commit`](https://pre-commit.com/), which will run
the formatter with every commit. `pre-commit` is included in our dev packages:

```
pip install -r reqs/dev.txt # Install the pre-commit package
pre-commit # Install the commit hook
pre-commit run --all-files # Run the hook once on existing code
```

## <a name="functions"></a>Functions

- Avoid naming a function that you are not matching. If you have not matched to
  understand the functionality, don't expect that someone else did just because
  they named it.
- Naming exported methods (the majority of cases)
    - Applies to any method that is defined in a .h file, with a .c
      implementation.
    - Prefix functions within Melee related code with the file's name. While
      asserts may indicate this was not the case for your function, this is to
      make the code easier to read.
    - Use lowerCamelCasing for the function's filename.
    - Use UpperCamelCasing for the function's name itself, unless it is a
      standard library reimplementation.
    - Examples:

    ```c
        lbVector_sin
        lbArchive_Parse
        Player_DoThing
        Stage_GetLeftBlastZone
        ftFox_LaserOnDeath
    ```
- Naming non-exported/local static inlines
    - Applies only to methods that have no accomanying .h definition. These are
      local and only used in the .c file where they are created.
    - Use lowerCamelCasing for the function name
    - Examples:

    ```c
        someInlineMethod
        someNonExportedThing
        getFooID
        getFighterCKind
    ```
- Empty stub functions should use `{}` rather than `{ return; }`
- Arguments should be snake_case
- Oftentimes a method will return a u8, but the associated values are enum
  values. In these situations, document the actual enum type clearly in doxygen.
  See the [Enum Types](#enum-types) section of this doc for more details.

### <a name="structs"></a>Structs

- Structs should include explicit information about offsets
    - Top-level Struct offsets begin at 0.
    - Struct members should include the offsets of their members as an inline
      comment before the type declaration.
    - Even when the struct member is well understood and named, the offset
      comment should be retained.
    - Struct offset comments must all be the same width, using 0s for
      left-padding.
- Struct definitions should never contain child structs.
- When a struct members name/purpose is unknown, it should be written as
  `x<Hex-Offset>`.
- Struct offsets should contain bit offsets when applicable
- Bitmasks should be defined via union
- When a section of a struct is only functioning as padding, it should be
  written as `x<Hex-Offset>_pad` and use a u8 array.
- Struct member names should be snake_case.
- Struct definitions should be defined in `types.h` for a given module.
- Typedefs associated with a given struct should be in the sibling `forward.h`
  file in the same module.
- Examples:
    - Yes:

      ```c
      struct Player {
          /* +C00 */ u32 x0;
          /* +C04 */ u8 x4_pad[12];
          /* +C10 */ u8 well_known_something;
          /* +C11 */ u8 foo_bar;
          /* +C12 */ u8 x13
      };
      ```

    - No:

      ```c
      struct Player {
          u8 thing;
          u32 something;
          u32 something2;
          u32 something3;
          u8 well_known_something;
          u8 bits
      };
      ```

- **Do not copy structs from another project**

### <a name="conditionals"></a>Conditionals
- Make NULL checks explicit
    - Yes: `if (ptr != NULL)`
    - No: `if (!ptr)`
- Do not leave `else` or `else if` conditions dangling unless the `if` condition lacks braces.
  - Yes:

    ```c
    if (condition)
    {
      // code
    }
    else
    {
      // code
    }
    ```
  - Yes:

    ```c
    if (condition)
      // code line
    else
      // code line
    ```
  - No:

    ```c
    if (condition)
    {
      // code
    }
    else
      // code line
    ```

## <a name="variables"></a>Variables
- Variable names should be snake_case
- Variable names should be descriptive for functionality that is well understood
- Examples:
    - Good:
      ```c
        bool luigi_unlocked = gm_IsCKindUnlocked(CKIND_LUIGI)
      ```
    - Acceptable:
      ```c
        bool intr = gm_8015CDC8(CKIND_LUIGI)
      ```
    - Bad:
      ```c
        bool b = gm_IsCKindUnlocked(CKIND_LUIGI)
      ```

## <a name="primitives"></a>Primitives

### Numeric types

Generally speaking, `int` or `unsigned int` should be the preferred type for
whole numbers, unless there is some specific context about a piece of code or
struct that dictates a specific bit width. In practice, `int` is more likely to
be used throughout a codebase, and the goal of this decmopilation project is to
try to match the original source.

When explicit fixed-width numbers are necessary, use the following types:
- Booleans: `bool`
- Bitmasks: Use the smallest unsigned explicit width int type that fits the
  mask. (`u8`, `u16`, `u32`, `u64`)
- 8-bit  whole: `u8` or `s8`
- 16-bit whole: `unsigned short` or `short`
- 32-bit whole: `u32` or `s32`
- 64-bit whole: `u64` or `s64`
- 32-bit floating point: `float`
- 64-bit floating point: `double`

See the [Integer Types](#integer-types) section for more information about
techinical quirks surrounding various integer types.

### Specialized types
- Single character: `char`
- Strings: `char*`
- Unknown 32 bit pointer: `UNK_T`.
- Enums: `enum_t` as a placeholder until the actual enum is defined.
- OS Timestamps: `OSTime`

## <a name="enums"></a>Enums
- Enum declarations should include a clear means of determining the value for each
  entry
  - May be a comment prefix with the hexadecimal value. There must be enough
    left-padded 0s so that each comment is the same width.
  - May be an explicit value decl such as `FOO_BAR = 4`
- Each enum value for a given type should have a unique prefix that makes them
  easy to identify as a group.
- Enum value names should be descriptive when well understood.
- Enum value names should contain their offset when not well understood.
- Enum value names should be in SCREAMING_SNAKE_CASE
  clearly in doxygen. See the [#enum-types](enum types) docs for more info
- Enum definitions should be defined in `types.h` for a given module.
- Typedefs associated with a given enum should be in the sibling `forward.h`
  file in the same module.
- Examples:
    - Good:
    ```c
    typedef enum CharacterKind {
        /* 0x00 */ CKIND_CAPTAIN,
        /* 0x01 */ CKIND_DONKEY,
        /* 0x02 */ CKIND_FOX,
        ...
        /* 0x20 */ CHKIND_POPO,
        /* 0x21 */ CHKIND_NONE,
        /* 0x22 */ CHKIND_MAX = CHKIND_NONE
    } CharacterKind;
    ```
    - Acceptable:
    ```c
    typedef enum FooKind {
        /* 0x0 */ FOO_BAR,
        /* 0x1 */ FOO_BAZ,
        /* 0x2 */ FOO_0x2,
        /* 0x3 */ FOO_WOOZLE,
        /* 0x4 */ FOO_0x4,
        /* 0x5 */ FOO_WOZZLE,
        /* 0x6 */ FOO_MAX,
    } CharacterKind;
    ```
    - Bad:
    ```c
    typedef enum FooKind {
        FOO_BAR,
        FOO_BAZ,
        FOO_0x2,
        FOO_WOOZLE,
        /* 0x4 */  FOO_0x3,
        ...
        /* 0x1A */ FOO_WOZZLE,
        /* 0x1B */ FOO_MAX,
    } CharacterKind;
    ```

## <a name="literals"></a>Literals
- Integer literals
  - Yes: `123U` for `u32`
  - Yes: `123456L` for `s64`
  - Yes: `123456LU` for `u64`
  - Yes: `0xABC` for hexidecimal
  - No: `0XABC`
- Floating-point literals
  - Yes: `1.23F` for `f32`
  - No: `1.23f`
  - Yes: `1.23L` for `f64`
  - No: `1.23`
  - Yes: `1.23e-5F`
  - No: `1.23E-5F`
  - No:
    - `1.`
    - `1.F`
    - `1.f`
    - `1.L`
  - No: `1` for `f32` or `f64`

## <a name="headers"></a>Headers

- Every TU header (meaning things that actually appear in splits.txt) must
  contain its own symbols according to the split, and only those members. Extra
  inlines, types, etc. are not allowed. Symbols must appear in address order.
  static symbols should appear at the top of the C file, not the header.
- A TU may define a *.static.h file. This is a temporary file to aid in m2c
  decompilation runs, so it should be considered as part of the C file, and
  entirely private. It should be deleted when the TU is linked (marked as
  Matching).
- types.h for each module contains relevant types primary to that module. It's
  difficult to discern where a type truly belongs, so we're not very strict
  about that. Types should be only struct X and/or union X definitions, not
  typedefs.
- One forward.h corresponds to each types.h and is responsible for providing a
  typedef for each struct and union, and typedefs of function pointers. It is
  also the place to define enums, global const simple types like integers that
  don't get emitted as symbols, and #define constants. The purpose of this
  separation is to avoid circular inclusions.
- If an inline function is shared by multiple TUs but its function body isn't a
  real symbol, it goes in inlines.h for the most relevant module. An exception
  is made if that inline function contains an assert which proves its source file.
- Documentation belongs in *.dox and should be kept out of the C and H files
  with minimal exceptions. @todo comments are allowed anywhere.

# <a name="compiler-notes"></a>Compiler Notes

This section documents quirks/gotchas related to the C language and mwcc.

## <a name="integer-types"></a>Integer Types

`char`, `short`, `long`, and `long long` all tell the compiler specific bit
widths to use for a given type. For the gamecube, these are `8`, `16`, `32`,
and `64` bits respectively.

The `int` type provides no such indication to the compiler, specifying only that
the platform-native int type should be used. This lets the compiler try to be
smart about what it does for a given value, contextually making optimizations
in the binary.  This can lead to situations where the compiler may emit opcodes
that make an int type appear as any width from 8 to 32 bits in decomp.  In
practice, A signed 8-bit integer (`s8`) declaration in particular is extremely
rare, and is usually really an `int` in disguise.

## <a name="enum-types"></a>Enum Types

Enum typedefs in this project always resolve to `int` currently.  This is a
quirk of the current compiler setup. Often a method will return a `u8`, but
it's for an enum return value. Check related docs and use-sites to determine
the actual type.

# <a name="prs"></a>Pull Requests

If you just want to get started and match a function, you don't need to create a PR! You can just [create an issue](https://github.com/doldecomp/melee/issues/new) with your decomp.me link and a maintainer will add your code to the repo.

If you're familiar with git and want to make changes locally, you can also [fork the repo](https://docs.github.com/en/get-started/quickstart/fork-a-repo) to your personal GitHub. When submitting code, try to group your changes into fewer but larger PRs, as it'a easier to review that way.

# <a name="ai"></a>AI Assistance

Using AI to match functions is acceptable and frequently practiced. However, please adhere to the following guidelines:
* Refrain from allowing AI to name fields in structs or other globally accessible identifiers.
* Discourage AI from attempting to match data sections, instead focusing solely on code matches.
* When submitting pull requests or issues, avoid including AI output in the body or in comments, and do not submit automated code reviews. An AI summary which is both relevant and concise may be included if it is wrapped in markdown comments (`>`) to differentiate it from human writing.
