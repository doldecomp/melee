#!/usr/bin/env python3
import os
import subprocess

if __name__ == "__main__":
    short_sha = os.getenv("SHORT_SHA")
    tree_url = os.getenv("TREE_URL")

    progress = subprocess.run(
        [
            "python",
            "tools/calcprogress/calcprogress.py",
            "--dol",
            "build/ssbm.us.1.2/main.dol",
            "--map",
            "build/ssbm.us.1.2/GALE01.map",
            "--asm-obj-ext",
            ".s.o",
            "--old-map",
            "true",
        ],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        universal_newlines=True,
    ).stdout.strip()

    readme = f"""# Super Smash Bros Melee Dump

This is a dump of the built ELF from Super Smash Bros Melee.

* For files built from raw assembly, see [`asm`](/asm).
* For files built from C source code, see [`src`](/src).
* For the CodeWarrior map file, which can be used with Dolphin, see [`GALE01.map`](/GALE01.map).
* For the context file that can be used on [decomp.me](https://decomp.me/), see [`ctx.c`](/ctx.c).
* This dump was created from commit [`{short_sha}`]({tree_url}).

# Progress

```
{progress}
```"""

    print(readme)
