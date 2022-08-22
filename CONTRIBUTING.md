# <a name="heading"></a>Melee Coding Style

This document is to act as a guideline for how you should submit Pull Requests.

# Sections

- [Introduction](#introduction)
- [Coding Style and Formatting](#coding-style-and-formatting)


# <a name="introduction"></a>Introduction

This document aims to clarify the coding standard required for a Pull Request to be accepted. 

While not all code submitted at this time conforms to this standard, it is the intention of the project to correct it in time.


# <a name="coding-style-and-formatting"></a>Coding Style and Formatting

- [Naming](#naming)
- [Structs](#structs)
- [Functions](#functions)
- [Conditionals](#conditionals)

## <a name="naming"></a>Naming
- Avoid naming a function that you are not matching. If you have not matched to understand the functionality, don't expect that someone else did just because they named it.
- Affix functions within Melee related code with the file's name. While asserts may indicate this was not the case for your function, this is to make the code easier to read.
	- Use Lower Camel Casing for the function's filename if it is made up of multiple words.
	- Use Upper Camel Casing for the function's name itself, unless it is a standard library reimplementation.
	- Examples:
	
	```
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
		
		```
		typedef struct Player {
			/* 0x00 */ u8 x0_thing;
			/* 0x04 */ u32 x4_filler[3];
			/* 0x10 */ u8 x10_thing;
		};
		```
		- No:
		```
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
