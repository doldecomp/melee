#!/usr/bin/env python3
"""Run synth's private loader on the native host under ASan and UBSan.

Requires Clang and a configured build (for generated project headers).
The fixture uses host-order scalar values; file byte-order conversion and
GameCube device emulation are outside this test.
"""

import os
from pathlib import Path
import subprocess
import sys
import tempfile

root = Path(__file__).resolve().parents[2]
with tempfile.TemporaryDirectory(prefix="synth-portability-") as tmp:
    binary = str(Path(tmp) / "test")
    command = [
        os.environ.get("CC", "clang"),
        "-Isrc", "-Isrc/MSL", "-Ilibs/dolphin/include", "-Ibuild/GALE01/include",
        "-fno-builtin", "-ffunction-sections", "-fdata-sections",
        "-Wno-pointer-bool-conversion", "-Wno-tautological-pointer-compare",
        "-Wno-incompatible-library-redeclaration", "-fsanitize=address,undefined",
        "-fno-sanitize-recover=all", "tools/tests/synth_portability.c",
        "-Wl,-dead_strip" if sys.platform == "darwin" else "-Wl,--gc-sections",
        "-o", binary,
    ]
    subprocess.run(command, cwd=root, check=True)
    subprocess.run([binary], cwd=root, check=True)
