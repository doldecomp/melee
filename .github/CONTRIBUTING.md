# <a name="heading"></a>Melee Coding Style

This document is to act as a guideline for how you should submit Pull Requests.

# Sections

- [Introduction](#introduction)
- [Coding Style and Formatting](#coding-style-and-formatting)


# <a name="introduction"></a>Introduction

This document aims to clarify the coding standard required for a Pull Request to be accepted.

While not all code submitted at this time conforms to this standard, it is the intention of the project to correct it in time.


# <a name="coding-style-and-formatting"></a>Coding Style and Formatting

- [Auto formatting](#auto-formatting)
- [Naming](#naming)
- [Structs](#structs)
- [Functions](#functions)
- [Conditionals](#conditionals)
- [Pull Requests](#prs)

## <a name="auto-formatting"></a>Auto Formatting
C code that's contributed to this codebase should have `clang-format` ran on it. You can do this easily by adding the C files you changed, and then running [`git clang-format`](https://ortogonal.github.io/cpp/git-clang-format/), which will run `clang-format` on staged files.

## <a name="naming"></a>Naming
- Avoid naming a function that you are not matching. If you have not matched to understand the functionality, don't expect that someone else did just because they named it.
- Affix functions within Melee related code with the file's name. While asserts may indicate this was not the case for your function, this is to make the code easier to read.
    - Use Lower Camel Casing for the function's filename if it is made up of multiple words.
    - Use Upper Camel Casing for the function's name itself, unless it is a standard library reimplementation.
    - Examples:

    ```c
        lbVector_sin
        lbArchive_Parse
        Player_DoThing
        Stage_GetLeftBlastZone
        ftFox_LaserOnDeath
    ```

## <a name="structs"></a>Structs
- Structs should be formatted the following way for Melee related code. This does not apply to code from libraries:
    - Prefix struct variables in larger structs, such as those seen in Fighters, with their offset
    - If you copy structs from another project, remove any members from the struct which are not part of your code or existing code.
        - Yes:

        ```c
        typedef struct Player {
            /* 0x00 */ u8 x0_thing;
            /* 0x04 */ u32 x4_filler[3];
            /* 0x10 */ u8 x10_thing;
        };
        ```
        - No:
        ```c
        typedef struct Player {
            u8 thing;
            u32 something;
            u32 something2;
            u32 something3;
            u8 thing;
        };
        ```

## <a name="functions"></a>Functions
- Functions acting as just a stub, IE. do nothing, should have an explicit ```return``` rather than being empty

## <a name="conditionals"></a>Conditionals
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

## <a name="prs"></a>Pull Requests

If you just want to get started and match a function, you don't need to create a PR! You can just [create an issue](https://github.com/doldecomp/melee/issues/new) with your decomp.me link and a maintainer will add your code to the repo.

If you're familiar with git and want to make changes locally, you can also [fork the repo](https://docs.github.com/en/get-started/quickstart/fork-a-repo) to your personal GitHub. When submitting code, try to group your changes into fewer but larger PRs, as it'a easier to review that way.

When you open a PR, the `#melee` channel on Discord will be notified.
