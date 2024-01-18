#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object matching status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

import argparse
import sys
from pathlib import Path
from typing import Iterator, List

from tools.project import (LibDict, Object, ProjectConfig, calculate_progress,
                           generate_build, is_windows)

# Game versions
DEFAULT_VERSION = 0
VERSIONS = [
    "GALE01",  # 0
]

if len(VERSIONS) > 1:
    versions_str = ", ".join(VERSIONS[:-1]) + f" or {VERSIONS[-1]}"
else:
    versions_str = VERSIONS[0]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    default="configure",
    help="configure or progress (default: configure)",
    nargs="?",
)
parser.add_argument(
    "--version",
    dest="version",
    default=VERSIONS[DEFAULT_VERSION],
    help=f"version to build ({versions_str})",
)
parser.add_argument(
    "--build-dir",
    dest="build_dir",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--compilers",
    dest="compilers",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    dest="map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--debug",
    dest="debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        dest="wrapper",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--build-dtk",
    dest="build_dtk",
    type=Path,
    help="path to decomp-toolkit source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    dest="sjiswrap",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--verbose",
    dest="verbose",
    action="store_true",
    help="print verbose output",
)
args = parser.parse_args()

config = ProjectConfig()
config.version = args.version.upper()
if config.version not in VERSIONS:
    sys.exit(f"Invalid version '{config.version}', expected {versions_str}")
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.build_dtk_path = args.build_dtk
config.compilers_path = args.compilers
config.debug = args.debug
config.generate_map = args.map
config.sjiswrap_path = args.sjiswrap
if not is_windows():
    config.wrapper = args.wrapper

# Tool versions
config.compilers_tag = "20231018"
config.dtk_tag = "v0.6.2"
config.sjiswrap_tag = "v1.1.1"
config.wibo_tag = "0.6.9"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
    # "-listclosure", # Uncomment for Wii linkers
]

# Base flags, common to most GC/Wii games.
# Generally leave untouched, with overrides added below.
cflags_base = [
    "-msgstyle gcc",  # TODO arg
    "-nowraplines",
    "-cwd source",
    "-Cpp_exceptions off",
    "-proc gekko",
    "-fp hardware",
    "-align powerpc",
    "-fp_contract on",
    "-O4,p",
    "-enum int",
    "-nodefaults",
    "-inline auto",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-RTTI off",
    "-str reuse",
    # "-W all",  # TODO
    "-maxerrors 1",  # TODO arg
    "-DMUST_MATCH",  # TODO arg
    f"-DVERSION={version_num}",
]

# Debug flags
# TODO
if config.debug:
    cflags_base.extend(["-sym on", "-DDEBUG=1"])
else:
    cflags_base.append("-DNDEBUG=1")

# Metrowerks library flags
cflags_runtime = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-gccinc",
    "-common off",
    "-inline auto",
]

includes_base = ["src"]

system_includes_base = [
    "src",
    "src/MSL",
    "src/Runtime",
    f"build/{config.version}/include",
]

cflags_melee = [
    *cflags_base,
]

config.linker_version = "GC/1.3.2"

Objects = List[Object]


def Lib(
    lib_name: str,
    objects: Objects,
    includes: List[str] = includes_base,
    system_includes: List[str] = system_includes_base,
) -> LibDict:
    def make_includes(includes: List[str]) -> Iterator[str]:
        return map(lambda s: f"-i {s}", includes)

    return {
        "lib": lib_name,
        "mw_version": "GC/1.2.5n",
        "cflags": [
            *cflags_base,
            *make_includes(includes),
            "-I-",
            *make_includes(system_includes),
        ],
        "host": False,
        "objects": objects,
    }


def DolphinLib(lib_name: str, objects: Objects) -> LibDict:
    return Lib(lib_name, objects)


def SysdolphinLib(lib_name: str, objects: Objects) -> LibDict:
    return Lib(
        lib_name,
        objects,
        includes=[
            *includes_base,
            "src/melee",  # HACK for lbrefract
            "src/sysdolphin",
        ],
        system_includes=[
            *system_includes_base,
            "src/dolphin",
            "src/sysdolphin",
        ],
    )


def MeleeLib(lib_name: str, objects: Objects) -> LibDict:
    return Lib(
        lib_name,
        objects,
        includes=[
            *includes_base,
            "src/melee",
            "src/melee/ft/chara",
        ],
        system_includes=[
            *system_includes_base,
            "src/dolphin",
            "src/sysdolphin",
        ],
    )


Matching = True
NonMatching = False

config.warn_missing_config = config.debug
config.warn_missing_source = config.debug
config.libs = [
    SysdolphinLib(
        "sysdolphin",
        [
            Object(Matching, "sysdolphin/baselib/dobj.c"),
            Object(NonMatching, "sysdolphin/baselib/tobj.c"),
            Object(Matching, "sysdolphin/baselib/state.c"),
            Object(NonMatching, "sysdolphin/baselib/tev.c"),
            Object(Matching, "sysdolphin/baselib/mobj.c"),
            Object(Matching, "sysdolphin/baselib/aobj.c"),
            Object(Matching, "sysdolphin/baselib/lobj.c"),
            Object(NonMatching, "sysdolphin/baselib/cobj.c"),
            Object(Matching, "sysdolphin/baselib/fobj.c"),
            Object(Matching, "sysdolphin/baselib/pobj.c"),
            Object(NonMatching, "sysdolphin/baselib/jobj.c"),
            Object(Matching, "sysdolphin/baselib/initialize.c"),
            Object(Matching, "sysdolphin/baselib/video.c"),
            Object(Matching, "sysdolphin/baselib/rumble.c"),
            Object(NonMatching, "sysdolphin/baselib/spline.c"),
            Object(Matching, "sysdolphin/baselib/util.c"),
            Object(Matching, "sysdolphin/baselib/objalloc.c"),
            Object(NonMatching, "sysdolphin/baselib/robj.c"),
            Object(Matching, "sysdolphin/baselib/id.c"),
            Object(Matching, "sysdolphin/baselib/wobj.c"),
            Object(Matching, "sysdolphin/baselib/fog.c"),
            Object(Matching, "sysdolphin/baselib/list.c"),
            Object(Matching, "sysdolphin/baselib/object.c"),
            Object(Matching, "sysdolphin/baselib/random.c"),
            Object(NonMatching, "sysdolphin/baselib/texp.c"),
            Object(NonMatching, "sysdolphin/baselib/texpdag.c"),
            Object(Matching, "sysdolphin/baselib/debug.c"),
            Object(NonMatching, "sysdolphin/baselib/psdisp.c"),
            Object(NonMatching, "sysdolphin/baselib/psdisptev.c"),
            Object(NonMatching, "sysdolphin/baselib/psappsrt.c"),
            Object(NonMatching, "sysdolphin/baselib/sobjlib.c"),
            Object(NonMatching, "sysdolphin/baselib/sislib.c"),
        ],
    ),
    MeleeLib(
        "cm",
        [
            Object(Matching, "melee/cm/cmsnap.c"),
        ],
    ),
    MeleeLib(
        "db",
        [
            Object(NonMatching, "melee/db/db_2253.c"),
        ],
    ),
]

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress and write progress.json
    config.progress_each_module = args.verbose
    config.progress_all = False
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
