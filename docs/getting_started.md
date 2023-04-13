@page getting_started Getting Started
# Introduction

This doc is designed to help beginners get into Melee decompilation (and hopefully contribute). We'll also try to answer common questions here and talk about motivations for working on this project.

# Goals of the project

The goal of this repo is to **write C code that, after being compiled, matches the PowerPC assembly 100%**. There's a bit of nuance here though. Let’s first take a look at what we’re working with:

![](compilation_diagram.png)

The details for what produces these different artifacts is out-of-scope. Here’s what some Melee C code looks like ([link](https://github.com/doldecomp/melee/blob/0b3f4aeebc17d8e9c3d8ea792d8d8e412c2ad436/src/melee/ft/chara/ftMewtwo/ftMewtwo_SpecialHi.c#L15-L21)):

```c
void ftMewtwo_SpecialHi_CreateGFX(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    ftMewtwo_SpecialHi_SetStartGFX(fighter_gobj);
    fp->cb.x21BC_callback_Accessory4 = NULL;
}
```

and its corresponding PowerPC assembly:

```asm
.global ftMewtwo_SpecialHi_CreateGFX
ftMewtwo_SpecialHi_CreateGFX:
/* 801450A0 00000000  7C 08 02 A6 */	mflr r0
/* 801450A4 00000004  90 01 00 04 */	stw r0, 0x4(r1)
/* 801450A8 00000008  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 801450AC 0000000C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 801450B0 00000010  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 801450B4 00000014  48 00 00 21 */	bl ftMewtwo_SpecialHi_SetStartGFX
/* 801450B8 00000018  38 00 00 00 */	li r0, 0x0
/* 801450BC 0000001C  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 801450C0 00000020  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 801450C4 00000024  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 801450C8 00000028  38 21 00 18 */	addi r1, r1, 0x18
/* 801450CC 0000002C  7C 08 03 A6 */	mtlr r0
/* 801450D0 00000030  4E 80 00 20 */	blr
```

So the repo is filled with `.s` files and `.c` files, where the C code inside the `.c` files, each of which are a 100% translation of its corresponding `.s` file that used to be in the repo. Note that once we successfully decompile a function, we remove it from the assembly.

# Do we have to write all this C code by hand?

No! And even initially, the code doesn’t have to be super-readable as we’re trying to get 100% match rate first.

So you can actually view the above example in an online tool that we use called decomp.me. Here’s a link to [that specific decompliation](https://decomp.me/scratch/Mkmnx). If you want to try doing this yourself, follow these steps:

1. Copy the assembly in the example
2. Hit “New Scratch”
3. Select Platform “GameCube / Wii”
4. Set the preset to “Super Smash Bros. Melee”
5. Copy in the contents of [this link](https://doldecomp.github.io/melee/ctx.html) into the “Context” section. More on that later.
6. Copy in the ASM into “Target assembly” and hit “Create scratch”

When you initially create a new “scratch” in this site, it’ll actually do its best to decompile the assembly you give it (try hitting the “Decompile” button in the link). You’ll notice things it spits out like

```c
temp_r31 = arg0->unk2C;
```

which can be translated in kind-of-English as “`temp_r31` takes the value at the memory address of `arg0 + 0x2c`.” If you don’t know anything about `arg0`, you can translate it to sketchy-C

```c
// The u8* conversion is because C automatically figures out pointer size for
// you, which means for an s32, you'd have to do arg0 + 0x2c / 4
temp_r31 = *((s32 *) ((u8 *) arg0 + 0x2c))
```

…while this accomplishes the goal of getting a 100% match (you could pretty much do every memory access and set like this), we actually can guess what `arg0` is in this case because of the file it’s in. You can do some digging yourself, but that line ends up translating to something like:

```c
Fighter* fp = GET_FIGHTER(fighter_gobj);
```

## What was going on with the Context?

Think of the context as a giant header file which you then `#include` at the top of your file. To generate context from a local repo, use `m2ctx`. Run `python3 tools/m2ctx/m2ctx.py -h` for a list of options.

# Alright, how do I try decompiling?

So you want to find some assembly that:

- no one is working on
- isn’t that long as you’re new
- isn’t already decompiled

In [this public Trello board](https://trello.com/b/pz2ACtnS/melee-decompilation), you can see which assembly files have been claimed or unclaimed. So don’t pick a function in a `.s` file that’s claimed. Note that this is a read-only link. If you want write access, join the [Discord](https://discord.gg/hKx3FJJgrV)!

To make sure it’s not already decompiled, take the label (e.g. `ftColl_8007B8CC`) and search the repo for instances of it. If you don’t see any C code definitions with implementations, then it at least hasn’t been committed to the repo. You can also use `grep`:
```sh
grep -rn 'ftColl_8007B8CC' src
```

You then want to make sure no one is working on it. So search [decomp.me](http://decomp.me) for that label, and it’ll flag if anyone has tried decompiling it. If it’s clearly abandoned, it’s probably okay to fork it and try it out.

After you’ve done these steps, follow the above steps for pasting into [decomp.me](http://decomp.me) 🙂.

# Resources

- [PowerPC ISA PDF](https://math-atlas.sourceforge.net/devel/assembly/ppc_isa.pdf). Note that the GameCube’s processor is a PowerPC CPU running in 32bit mode, so some of the instructions’ effects aren’t relevant (e.g. `lwzu` zeros out part of the register, but only in 64bit mode).
    - also note that the floating point registers are 64bit / `double`s.
- [Guide on getting started](https://hackmd.io/@ValorZardK/rkbSHra0Y) that’s a bit more detailed
