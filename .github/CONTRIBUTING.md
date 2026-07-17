# <a name="heading"></a>Melee Coding Style

This document is to act as a guideline for how you should submit Pull Requests.

# Sections

- [Introduction](#introduction)
- [Coding Style and Formatting](#coding-style-and-formatting)
- [Pull Requests](#prs)
- [AI Assistance](#ai)


# <a name="introduction"></a>Introduction

This document aims to clarify the coding standard required for a Pull Request to be accepted.

While not all code submitted at this time conforms to this standard, it is the intention of the project to correct it in time.


# <a name="coding-style-and-formatting"></a>Coding Style and Formatting

This style-guide has recently been updated. Existing code may not perfectly follow it, but any new code you contribute should.

- [Auto formatting](#auto-formatting)
- [Functions](#functions)
- [Structs](#structs)
- [Functions](#functions)
- [Conditionals](#conditionals)
- [Variables](#variables)
- [Primitives](#primitives)
- [Enums](#enums)
- [Literals](#literals)

## <a name="auto-formatting"></a>Auto Formatting
`clang-format` should be run on all C code in `src`. The easiest way to do this is to install and run [`pre-commit`](https://pre-commit.com/), which will run the formatter with every commit. `pre-commit` is included in our dev packages:

```
pip install -r reqs/dev.txt # Install the pre-commit package
pre-commit # Install the commit hook
pre-commit run --all-files # Run the hook once on existing code
```

## <a name="functions"></a>Functions

- Avoid naming a function that you are not matching. If you have not matched to understand the functionality, don't expect that someone else did just because they named it.
- Naming exported methods (the majority of cases)
    - Applies to any method that is defined in a .h file, with a .c implementation.
    - Prefix functions within Melee related code with the file's name. While asserts may indicate this was not the case for your function, this is to make the code easier to read.
    - Use lowerCamelCasing for the function's filename if it is made up of multiple words.
    - Use UpperCamelCasing for the function's name itself, unless it is a standard library reimplementation.
    - Examples:

    ```c
        lbVector_sin
        lbArchive_Parse
        Player_DoThing
        Stage_GetLeftBlastZone
        ftFox_LaserOnDeath
    ```
- Naming non-exported/local static inlines
    - Applies only to methods that have no accomanying .h definition. These are local and only used in the .c file where
      they are created.
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

### <a name="structs"></a>Structs

- Structs should include explicit information about offsets
    - Top-level Struct offsets begin at 0.
    - Nested structs continue from their parents offset.
    - Struct members should include the offsets of their members as an inline comment before the type declaration.
    - Even when the struct member is well understood and named, the offset comment should be retained.
    - Struct offset comments must all be the same width, using 0s for left-padding.
- Struct definitions may contain child structs only if their associated members are not pointer references.
- When a struct members name/purpose is unknown, it should be written as `x<Hex-Offset>`.
- When a section of a struct is only functioning as padding, it should be written as `x<Hex-Offset>_pad` and use a u8 array.
- Struct member names should be snake_case.
- Examples:
    - Yes:

      ```c
      typedef struct Player {
          /* 0x00 */ u32 x0;
          /* 0x04 */ u8 x4_pad[12];
          /* 0x10 */ u8 well_known_something;
          /* 0x11 */ u8 some_bitmask
      };
      ```

    - No:

      ```c
      typedef struct Player {
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
- Prefer primitive types with explicit bit widths
- When a type is an unknown 32 bit integer and likely a pointer, declare it as UNK_T

| Target Type                             | Good  | Bad            |
|-----------------------------------------|-------|----------------|
| 8-bit unsigned integer                  | u8    | unsigned char  |
| 16-bit unsigned integer                 | u16   | unsigned short |
| 32-bit unsigned integer                 | u32   | unsigned int   |
| 64-bit unsigned integer                 | u64   | unsigned long  |
| 8-bit signed integer                    | s8    | char           |
| 16-bit signed integer                   | s16   | short          |
| 32-bit signed integer                   | s32   | int            |
| 64-bit signed integer                   | s64   | long           |
| 8-bit float                             | f8    |                |
| 16-bit float                            | f16   |                |
| 32-bit float                            | f32   | float          |
| 64-bit float                            | f64   | double         |
| Unknown Pointer                         | UNK_T | void*          |

## <a name="enums"></a>Enums
- Enum declarations should include a clear means of determining the value for each entry
  - May be a comment prefix with the hexadecimal value. There must be enough left-padded 0s so that each comment is the
    same width.
  - May be an explicit value decl such as `FOO_BAR = 4`
- Each enum value for a given type should have a unique prefix that makes them easy to identify as a group.
- Enum value names should be descriptive when well understood.
- Enum value names should contain their offset when not well understood.
- Enum value names should be in SCREAMING_SNAKE_CASE
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

# <a name="prs"></a>Pull Requests

If you just want to get started and match a function, you don't need to create a PR! You can just [create an issue](https://github.com/doldecomp/melee/issues/new) with your decomp.me link and a maintainer will add your code to the repo.

If you're familiar with git and want to make changes locally, you can also [fork the repo](https://docs.github.com/en/get-started/quickstart/fork-a-repo) to your personal GitHub. When submitting code, try to group your changes into fewer but larger PRs, as it'a easier to review that way.

# <a name="ai"></a>AI Assistance

Using AI to match functions is acceptable and frequently practiced. However, please adhere to the following guidelines:
* Refrain from allowing AI to name fields in structs or other globally accessible identifiers.
* Discourage AI from attempting to match data sections, instead focusing solely on code matches.
* When submitting pull requests or issues, avoid including AI output in the body or in comments, and do not submit automated code reviews. An AI summary which is both relevant and concise may be included if it is wrapped in markdown comments (`>`) to differentiate it from human writing.
