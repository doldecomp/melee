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
import json
import os
import sys
from collections.abc import Iterator
from pathlib import Path
from typing import cast

from tools.project import (
    BuildConfig,
    BuildConfigUnit,
    Library,
    Object,
    ProgressCategory,
    ProjectConfig,
    calculate_progress,
    file_is_c_cpp,
    generate_build,
    is_windows,
    load_build_config,
)

# Game versions
DEFAULT_VERSION = 0
VERSIONS = ["GALE01"]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    choices=["configure", "progress"],
    default="configure",
    help="script mode (default: configure)",
    nargs="?",
)
parser.add_argument(
    "-v",
    "--version",
    choices=VERSIONS,
    type=str.upper,
    default=VERSIONS[DEFAULT_VERSION],
    help="version to build",
)
parser.add_argument(
    "--build-dir",
    metavar="DIR",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--binutils",
    metavar="BINARY",
    type=Path,
    help="path to binutils (optional)",
)
parser.add_argument(
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--debug",
    action="store_true",
    help="build with debug info (implies --non-matching)",
)
parser.add_argument(
    "--asm",
    action="store_true",
    help="override src files with asm equivalents (implies --non-matching)",
)
parser.add_argument(
    "--linkable",
    action="store_true",
    help="enable non-matching but linkable units",
)
parser.add_argument(
    "--sym",
    choices=["on", "off", "auto"],
    default="auto",
    help="whether to enable \"-sym on\" (default 'auto', on for non-matching units)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        metavar="BINARY",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--dtk",
    metavar="BINARY | DIR",
    type=Path,
    help="path to decomp-toolkit binary or source (optional)",
)
parser.add_argument(
    "--objdiff",
    metavar="BINARY | DIR",
    type=Path,
    help="path to objdiff-cli binary or source (optional)",
)
parser.add_argument(
    "--reloc-diffs",
    type=str,
    choices=["none", "name_address", "data_value", "all"],
    default="data_value",
    help="how relocation targets will be diffed in the report (default 'data_value')",
)
parser.add_argument(
    "--sjiswrap",
    metavar="EXE",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--ninja",
    metavar="BINARY",
    type=Path,
    help="path to ninja binary (optional)",
)
parser.add_argument(
    "--verbose",
    action="store_true",
    help="print verbose output",
)
parser.add_argument(
    "--msg-style",
    choices=["mpw", "std", "gcc", "ide", "parseable"],
    default="std",
    help="message style of the compiler and linker (default 'std')",
)
parser.add_argument(
    "--max-errors",
    type=int,
    default=1,
    help="the maximum number of errors allowed by the compiler (0 meaning unlimited, default 1)",
)
parser.add_argument(
    "--warn",
    dest="warn",
    type=str,
    choices=["all", "off", "error"],
    default="off",
    help="warning level (default 'off')",
)
parser.add_argument(
    "--lint-all",
    action="store_true",
    help="do not disable any clang warnings",
)
parser.add_argument(
    "--no-lint-error",
    dest="lint_error",
    action="store_false",
    help="do not treat clang warnings as errors",
)
parser.add_argument(
    "--require-protos",
    dest="require_protos",
    action="store_true",
    help="require function prototypes",
)
parser.add_argument(
    "--allow-auto-splits",
    dest="allow_auto_splits",
    action="store_true",
    help="allow dtk auto-splits",
)
parser.add_argument(
    "--non-matching",
    dest="non_matching",
    action="store_true",
    help="builds equivalent (but non-matching) or modded objects",
)
parser.add_argument(
    "--no-progress",
    dest="progress",
    action="store_false",
    help="disable progress calculation",
)
parser.add_argument(
    "--no-compile-commands",
    dest="compile_commands",
    action="store_false",
    help="do not generate compile_commands.json",
)
parser.add_argument(
    "--no-always-apply",
    dest="always_apply",
    action="store_false",
    help="do not always run dtk dol apply after linking",
)
args = parser.parse_args()

if any({args.debug, args.asm, args.linkable}) or args.sym == "on":
    args.non_matching = True


config = ProjectConfig()
config.version = str(args.version)
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.dtk_path = args.dtk
config.objdiff_path = args.objdiff
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.generate_map = args.map
config.non_matching = args.non_matching
config.sjiswrap_path = args.sjiswrap
config.ninja_path = args.ninja
config.progress = args.progress
if not is_windows():
    config.wrapper = args.wrapper
if not args.asm:
    config.asm_dir = None

config.generate_compile_commands = False  # Handled internally

# Tool versions
config.binutils_tag = "2.42-2"
config.compilers_tag = "20251118"
config.dtk_tag = "v1.8.3"
config.objdiff_tag = "v3.6.1"
config.sjiswrap_tag = "v1.2.2"
config.wibo_tag = "0.7.0"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    "-I include",
    "-I src",
    f"-I build/{config.version}/include",
    f"--defsym BUILD_VERSION={version_num}",
]
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
    f"-warn {args.warn}",
]
if args.debug:
    config.ldflags.append("-g")  # Or -gdwarf-2 for Wii linkers
if args.map:
    config.ldflags.append("-mapunused")
    # config.ldflags.append("-listclosure") # For Wii linkers

# Use for any additional files that should cause a re-configure when modified
config.reconfig_deps = []

# Progress
config.progress_use_fancy = True
config.progress_code_fancy_frac = 293
config.progress_code_fancy_item = "Trophies"
config.progress_data_fancy_frac = 51
config.progress_data_fancy_item = "Event Matches"

# Optional numeric ID for decomp.me preset
# Can be overridden in libraries or objects
config.scratch_preset_id = 63

# GC/Wii compiler flags
cflags_base = [
    "-nowraplines",
    "-cwd source",
    "-Cpp_exceptions off",
    "-proc gekko",
    "-fp hardware",
    "-align powerpc",
    "-nosyspath",
    "-fp_contract on",
    "-O4,p",
    "-multibyte",
    "-enum int",
    "-nodefaults",
    "-inline auto",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-RTTI off",
    "-str reuse",
    f"-DBUILD_VERSION={version_num}",
    f"-DVERSION_{config.version}",
]


if args.sym in {"on", "off"}:
    cflags_base.append(f"-sym {args.sym}")
if not args.non_matching:
    cflags_base.append("-DMUST_MATCH")
if args.verbose:
    cflags_base.append("-verbose")

cflags_base.append(f"-maxerrors {args.max_errors}")
if args.max_errors == 0:
    cflags_base.append("-nofail")

cflags_base.append(f"-msgstyle {args.msg_style}")
config.ldflags.append(f"-msgstyle {args.msg_style}")
cflags_base.append(f"-warn {args.warn}")

if args.require_protos:
    cflags_base.append("-requireprotos")

# Metrowerks library flags
cflags_runtime = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-common off",
]

# Metrowerks libc flags
cflags_libc = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str pool,readonly",
    "-common off",
    "-inline deferred",
]

# MetroTRK flags
cflags_trk = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-pool off",
    "-sdata 0",
    "-sdata2 0",
    "-inline on,noauto",
    "-rostr",
]

includes_base = [
    "src",
    "src/MSL",
    "src/Runtime",
    "extern/dolphin/include",
    f"build/{config.version}/include",
]

cflags_melee = [
    *cflags_base,
]


config.linker_version = "GC/1.3.2"

# Native compiler flags

clang_includes = [
    "src/melee",
    "src/melee/ft/kinds",
]

clang_system_includes = [
    "src",
    "src/MSL",
    "src/Runtime",
    "src/sysdolphin",
    "extern/dolphin/include",
    "extern/dolphin/src",
    f"build/{config.version}/include",
]

clang_warnings = [
    "all",
    "extra",
    "c2x-extensions",
    "implicit-function-declaration",
    "implicit-int",
    "incompatible-pointer-types",
    "pointer-type-mismatch",
    "strict-prototypes",
    "typedef-redefinition",
]

if args.lint_error:
    clang_warnings.append("error")

clang_disabled_warnings = [
    "bitfield-constant-conversion",
    "integer-overflow",
    "missing-braces",
    "missing-field-initializers",
    "return-type",
    "sign-compare",
    "sometimes-uninitialized",
    "unused-but-set-variable",
    "unused-parameter",
    "unused-value",
    "unused-variable",
]


clang_flags_base = [
    "-xc",
    "-std=c99",
    "-nostdinc",
    "-fno-builtin",
    "--target=ppc32-none-eabi",
    "-DLINT",
    "-fno-short-enums",
    *[f"-I{s}" for s in clang_includes],
    *[f"-isystem{s}" for s in clang_system_includes],
    *[f"-W{s}" for s in clang_warnings],
]

if not args.lint_all:
    clang_flags_base.extend(f"-Wno-{s}" for s in clang_disabled_warnings),

config.extra_clang_flags.extend(clang_flags_base)


Objects = list[Object]


def Lib(
    lib_name: str,
    objects: Objects,
    cflags=cflags_base,
    fix_epilogue=True,
    fix_trk=False,
    includes: list[str] = includes_base,
    src_dir: str | None = None,
    category: str | None = None,
) -> Library:
    def make_includes(includes: list[str]) -> Iterator[str]:
        return map(lambda s: f"-i {s}", includes)

    if args.sym == "auto":
        for obj in objects:
            extra_cflags = cast(list[str], obj.options["extra_cflags"])
            extra_cflags.append(f"-sym {'off' if obj.completed else 'on'}")

    lib = {
        "lib": lib_name,
        "mw_version": f"GC/1.2.5{'n' if fix_epilogue else ''}",
        "cflags": [
            *cflags,
            *make_includes(includes),
        ],
        "host": False,
        "progress_category": category,
        "objects": objects,
    }

    if fix_trk:
        lib["mw_version"] = "GC/1.1p1"

    if src_dir is not None:
        lib["src_dir"] = src_dir

    return lib


def DolphinLib(lib_name: str, objects: Objects, fix_epilogue=False) -> Library:
    cflags = cflags_base + [
        "-requireprotos",
        "-fp_contract off",
        "-ir extern/dolphin/src",
    ]
    src_dir = "extern/dolphin/src"
    includes = [
        "extern/dolphin/include",
        "extern/dolphin/include/libc",
        "src/MSL",
    ]

    return Lib(
        lib_name,
        objects,
        fix_epilogue=fix_epilogue,
        src_dir=src_dir,
        cflags=cflags,
        includes=includes,
        category="sdk",
    )


def SysdolphinLib(lib_name: str, objects: Objects) -> Library:
    return Lib(
        lib_name,
        objects,
        includes=[
            *includes_base,
            "src/sysdolphin",
            f"build/{config.version}/sysdolphin",
        ],
        category="hsd",
    )


def MeleeLib(lib_name: str, objects: Objects) -> Library:
    return Lib(
        lib_name,
        objects,
        includes=[
            *includes_base,
            "src/melee",
            "src/melee/ft/kinds",
            "src/sysdolphin",
        ],
        category="game",
    )


def RuntimeLib(lib_name: str, objects: Objects) -> Library:
    return Lib(
        lib_name,
        objects,
        cflags=cflags_runtime,
        fix_epilogue=False,
        category="runtime",
    )


def Libc(lib_name: str, objects: Objects) -> Library:
    return Lib(
        lib_name,
        objects,
        cflags=cflags_libc,
        fix_epilogue=False,
        category="runtime",
    )


def TRKLib(lib_name: str, objects: Objects) -> Library:
    return Lib(
        lib_name,
        objects,
        cflags=cflags_trk,
        fix_epilogue=False,
        fix_trk=True,
        category="runtime",
    )


Matching = True  # Object matches and should be linked
NonMatching = False  # Object does not match and should not be linked
Equivalent = (
    config.non_matching
)  # Object should be linked when configured with --non-matching
Linkable = bool(args.linkable)  # Object is linkable but non-matching


# Object is only matching for specific versions
def MatchingFor(*versions):
    return config.version in versions


config.warn_missing_config = True
config.warn_missing_source = True

config.libs = [
    MeleeLib(
        "lb (Library)",
        [
            Object(Matching, "melee/lb/lbcommand.c"),
            Object(Linkable, "melee/lb/lbcollision.c"),
            Object(Matching, "melee/lb/lblanguage.c"),
            Object(Matching, "melee/lb/lbtime.c"),
            Object(Matching, "melee/lb/lb_00B0.c"),
            Object(Matching, "melee/lb/lb_00CE.c"),
            Object(Matching, "melee/lb/lbvector.c"),
            Object(Matching, "melee/lb/lbshadow.c"),
            Object(Matching, "melee/lb/lb_00F9.c"),
            Object(Matching, "melee/lb/lbspdisplay.c"),
            Object(Matching, "melee/lb/lb_013B.c"),
            Object(Matching, "melee/lb/lb_0146.c"),
            Object(Matching, "melee/lb/lbarq.c"),
            Object(Matching, "melee/lb/lbmemory.c"),
            Object(Matching, "melee/lb/lbheap.c"),
            Object(Matching, "melee/lb/lbfile.c"),
            Object(Matching, "melee/lb/lbarchive.c"),
            Object(Matching, "melee/lb/lbdvd.c"),
            Object(Matching, "melee/lb/lb_0192.c"),
            Object(Matching, "melee/lb/lb_0195.c"),
            Object(Matching, "melee/lb/lbcardnew.c"),
            Object(Matching, "melee/lb/lbcardgame.c"),
            Object(Linkable, "melee/lb/lbsnap.c"),
            Object(Matching, "melee/lb/lbgx.c"),
            Object(Matching, "melee/lb/lbanim.c"),
            Object(Matching, "melee/lb/lbmthp.c"),
            Object(Matching, "melee/lb/lb_01F8.c"),
            Object(Matching, "melee/lb/lbbgflash.c"),
            Object(Matching, "melee/lb/lb_020A.c"),
            Object(Matching, "melee/lb/lb_0219.c"),
            Object(Matching, "melee/lb/lbrefract.c"),
            Object(Matching, "melee/lb/lbtrigf.c"),
            Object(Matching, "melee/lb/lbaudio_ax.c"),
        ],
    ),
    MeleeLib(
        "cm (Camera)",
        [
            Object(Matching, "melee/cm/camera.c"),
            Object(Matching, "melee/cm/cmsnap.c"),
        ],
    ),
    MeleeLib(
        "pl (Player)",
        [
            Object(Matching, "melee/pl/player.c"),
            Object(Matching, "melee/pl/plstale.c"),
            Object(Matching, "melee/pl/plattack.c"),
            Object(Matching, "melee/pl/pltrick.c"),
            Object(Matching, "melee/pl/plbonus.c"),
            Object(Matching, "melee/pl/plbonuslib.c"),
            Object(Matching, "melee/pl/pl_040D.c"),
        ],
    ),
    MeleeLib(
        "mp (Map)",
        [
            Object(Matching, "melee/mp/mpcoll.c"),
            Object(Matching, "melee/mp/mplib.c"),
            Object(Matching, "melee/mp/mpisland.c"),
        ],
    ),
    MeleeLib(
        "ef (Visual effects)",
        [
            Object(Matching, "melee/ef/efdata.c"),
            Object(Matching, "melee/ef/eflib.c"),
            Object(Matching, "melee/ef/efsync.c"),
            Object(Matching, "melee/ef/efalt.c"),
            Object(Matching, "melee/ef/efasync.c"),
        ],
    ),
    MeleeLib(
        "ft (Fighters)",
        [
            # Main
            Object(Matching, "melee/ft/fighter.c"),
            Object(Matching, "melee/ft/ftanim.c"),
            Object(Matching, "melee/ft/ftaction.c"),
            Object(Matching, "melee/ft/ftparts.c"),
            Object(Matching, "melee/ft/ftcamera.c"),
            Object(Matching, "melee/ft/ftcoll.c"),
            Object(Matching, "melee/ft/ft_07C1.c"),
            Object(Matching, "melee/ft/ft_07C6.c"),
            Object(Matching, "melee/ft/ftcommon.c"),
            Object(Matching, "melee/ft/ftdrawcommon.c"),
            Object(Matching, "melee/ft/ftcliffcommon.c"),
            Object(Matching, "melee/ft/ftwalljump.c"),
            Object(Matching, "melee/ft/ft_0819.c"),
            Object(Matching, "melee/ft/ft_081B.c"),
            Object(Matching, "melee/ft/ft_084E.c"),
            Object(Matching, "melee/ft/ftdata.c"),
            Object(Matching, "melee/ft/ftmotionstates.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_Init.c"),
            Object(Matching, "melee/ft/ftlib.c"),
            Object(Matching, "melee/ft/ft_0877.c"),
            Object(Matching, "melee/ft/ft_0881.c"),
            Object(Matching, "melee/ft/ft_0892.c"),
            Object(Matching, "melee/ft/ft_0899.c"),
            Object(Matching, "melee/ft/ft_08A1.c"),
            # Common
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_Wait.c"),
            Object(Matching, "melee/ft/ftwaitanim.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_Attack1.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_AttackDash.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_AttackS3.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_AttackHi3.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_AttackLw3.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_AttackS4.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_AttackHi4.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_AttackLw4.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_AttackAir.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_LandingAir.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_Damage.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_DamageFall.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_DamageIce.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_Guard.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftpickupitem.c"),
            Object(Linkable, "melee/ft/kinds/ftCommon/ftCo_ItemThrow.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_SpecialS.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_SpecialAir.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_FallSpecial.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_Lift.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_DownBound.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_DownStand.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_Down.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_DownAttack.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_Passive.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_PassiveStand.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_ShieldBreakFly.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_ShieldBreakFall.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_ShieldBreakDown.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_ShieldBreakStand.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_Furafura.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_Escape.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_EscapeAir.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_Rebound.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_Pass.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_Ottotto.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CliffWait.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CliffClimb.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CliffAttack.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CliffEscape.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CliffJump.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CargoWait.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CargoWalk.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CargoTurn.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CargoKneebend.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CargoJump.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CargoFall.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CargoLanding.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CargoThrow.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_09C4.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_Shouldered.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CaptureCaptain.c"),
            Object(Matching, "melee/ft/ftdynamics.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_BarrelWait.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_StopWall.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_StopCeil.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_DownDamage.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_MissFoot.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_09F4.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_09F7.c"),
            Object(Matching, "melee/ft/kinds/ftMario/ftmariostrings.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_0A01.c"),
            Object(Matching, "melee/ft/ftcmdscript.c"),
            Object(Matching, "melee/ft/ftcpuattack.c"),
            Object(Matching, "melee/ft/ft_3C61.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CaptureYoshi.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_YoshiEgg.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CaptureKoopa.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CaptureDamageKoopa.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CaptureWaitKoopa.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_ThrownKoopa.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CaptureMewtwo.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_ThrownMewtwo.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CaptureKirby.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CaptureWaitKirby.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_ThrownKirby.c"),
            # Main again
            Object(Matching, "melee/ft/ftdemo.c"),
            Object(Matching, "melee/ft/ft_0BEC.c"),
            Object(Matching, "melee/ft/ft_0BEF.c"),
            Object(Matching, "melee/ft/ft_0BF0.c"),
            Object(Matching, "melee/ft/ftmaterial.c"),
            Object(Matching, "melee/ft/ftcolanim.c"),
            Object(Matching, "melee/ft/ftdevice.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_Bury.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_FlyReflect.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_PassiveWall.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_PassiveCeil.c"),
            Object(Linkable, "melee/ft/ftafterimage.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_DamageSong.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_0C35.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_AirCatch.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_DamageBind.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_WarpStar.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_HammerWait.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_HammerWalk.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_HammerTurn.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_HammerJump.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_HammerKneeBend.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_HammerFall.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_HammerLanding.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_0C60.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_DemoCallback0.c"),
            Object(Matching, "melee/ft/ft_0C31.c"),
            Object(Matching, "melee/ft/ftCo_800C703C.c"),
            Object(Matching, "melee/ft/ftCo_800C7070.c"),
            Object(Matching, "melee/ft/ftCo_800C70D0.c"),
            Object(Matching, "melee/ft/ftCo_800C7178.c"),
            Object(Matching, "melee/ft/ftCo_800C7220.c"),
            Object(Matching, "melee/ft/ftCo_800C739C.c"),
            Object(Matching, "melee/ft/ftCo_800C7434.c"),
            Object(Matching, "melee/ft/ftCo_800C7590.c"),
            Object(Matching, "melee/ft/ftCo_800C78B0.c"),
            Object(Matching, "melee/ft/ftCo_800C7CA0.c"),
            Object(Matching, "melee/ft/ftmetal.c"),
            Object(Matching, "melee/ft/ft_0C88.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_DownSpot.c"),
            Object(Matching, "melee/ft/ft_0C8C.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_Barrel.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_Walk.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_Turn.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_TurnRun.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_Dash.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_Run.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_RunDirect.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_RunBrake.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_Jump.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_KneeBend.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_JumpAerial.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_Fall.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_FallAerial.c"),
            Object(Matching, "melee/ft/ftswing.c"),
            Object(Matching, "melee/ft/ft_0CD1.c"),
            Object(Matching, "melee/ft/ft_0CD3.c"),
            Object(Matching, "melee/ft/ftstarrodswing.c"),
            Object(Matching, "melee/ft/ftlipstickswing.c"),
            Object(Matching, "melee/ft/ft_0CDD.c"),
            Object(Matching, "melee/ft/ft_0CDF.c"),
            Object(Matching, "melee/ft/ft_0CE3.c"),
            Object(Matching, "melee/ft/ftattacks4combo.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_ItemParasolOpen.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_ItemParasolFall.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_ItemParasolFallSpecial.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_ItemParasolDamageFall.c"),
            Object(Matching, "melee/ft/ftchangeparam.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_KinokoGiantStart.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_KinokoGiantEnd.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_KinokoSmallStart.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_KinokoSmallEnd.c"),
            Object(Matching, "melee/ft/ft_0D27.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_ItemScrew.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_DamageScrew.c"),
            Object(Matching, "melee/ft/ft_0D31.c"),
            Object(Matching, "melee/ft/ft_0D4D.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_Landing.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_Squat.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_SquatWait.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_SquatRv.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_0D67.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_Attack100.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_0D72.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_JumpAerialF1.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_ItemScopeStart.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_ItemScopeRapid.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_ItemScopeFire.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_ItemScope.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_Catch.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_0D8E.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_0D95.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CatchPull.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CatchWait.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CatchAttack.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CatchCut.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CapturePulled.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CaptureWait.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CaptureJump.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_0DC2.c"),
            # Common throw-related
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_CaptureCut.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_Throw.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_Thrown.c"),
            Object(Matching, "melee/ft/kinds/ftCommon/ftCo_AppealS.c"),
            Object(Matching, "melee/ft/ft_0DF0.c"),
            Object(Matching, "melee/ft/ft_0DF1.c"),
            # Donkey Kong (common states)
            Object(Matching, "melee/ft/kinds/ftDonkey/ftdonkeyheavywait0.c"),
            Object(Matching, "melee/ft/kinds/ftDonkey/ftdonkeyheavywalk.c"),
            Object(Matching, "melee/ft/ftwalkcommon.c"),
            Object(Matching, "melee/ft/kinds/ftDonkey/ftdonkeyms3450.c"),
            Object(Matching, "melee/ft/kinds/ftDonkey/ftdonkeyheavyturn.c"),
            Object(Matching, "melee/ft/kinds/ftDonkey/ftdonkeyheavyfall.c"),
            Object(Matching, "melee/ft/kinds/ftDonkey/ftdonkeyheavyjump.c"),
            Object(Matching, "melee/ft/kinds/ftDonkey/ftdonkeyheavywait1.c"),
            Object(Matching, "melee/ft/kinds/ftDonkey/ftdonkeyheavylanding.c"),
            # Mario
            Object(Matching, "melee/ft/kinds/ftMario/ftmario.c"),
            Object(Matching, "melee/ft/kinds/ftMario/ftmariospecialn.c"),
            Object(Matching, "melee/ft/kinds/ftMario/ftmariospecials.c"),
            Object(Matching, "melee/ft/kinds/ftMario/ftmariospecialhi.c"),
            Object(Matching, "melee/ft/kinds/ftMario/ftmariospeciallw.c"),
            # Captain Falcon
            Object(Matching, "melee/ft/kinds/ftCaptain/ftcaptain.c"),
            Object(Matching, "melee/ft/kinds/ftCaptain/ftcaptainspecialn.c"),
            Object(Matching, "melee/ft/kinds/ftCaptain/ftcaptainspecials.c"),
            Object(Matching, "melee/ft/kinds/ftCaptain/ftcaptainspeciallw.c"),
            Object(Matching, "melee/ft/kinds/ftCaptain/ftcaptainspecialhi.c"),
            # Fox
            Object(Matching, "melee/ft/kinds/ftFox/ftfox.c"),
            Object(Matching, "melee/ft/kinds/ftFox/ftfoxappeals.c"),
            Object(Matching, "melee/ft/kinds/ftFox/ftfoxspecialn.c"),
            Object(Matching, "melee/ft/kinds/ftFox/ftfoxspecialhi.c"),
            Object(Matching, "melee/ft/kinds/ftFox/ftfoxspeciallw.c"),
            Object(Matching, "melee/ft/kinds/ftFox/ftfoxspecials.c"),
            # Link
            Object(Matching, "melee/ft/kinds/ftLink/ftlink.c"),
            Object(Matching, "melee/ft/kinds/ftLink/ftlinkattackair.c"),
            Object(Matching, "melee/ft/kinds/ftLink/ftlinkspeciallw.c"),
            Object(Matching, "melee/ft/kinds/ftLink/ftlinkspecialhi.c"),
            Object(Matching, "melee/ft/kinds/ftLink/ftlinkspecials.c"),
            Object(Matching, "melee/ft/kinds/ftLink/ftlinkspecialn.c"),
            # Kirby
            Object(Matching, "melee/ft/kinds/ftKirby/ftkirby.c"),
            Object(Matching, "melee/ft/kinds/ftKirby/ftkirbydata.c"),
            Object(Matching, "melee/ft/kinds/ftKirby/ftkirbyattackdash.c"),
            Object(Matching, "melee/ft/kinds/ftKirby/ftkirbyspecialhi.c"),
            Object(Matching, "melee/ft/kinds/ftKirby/ftkirbyspeciallw.c"),
            Object(Matching, "melee/ft/kinds/ftKirby/ftkirbyspecials.c"),
            Object(Matching, "melee/ft/kinds/ftKirby/ftkirbyspecialn.c"),
            Object(Matching, "melee/ft/kinds/ftKirby/ftkirbyspecialmario.c"),
            Object(Matching, "melee/ft/kinds/ftKirby/ftkirbyspecialluigi.c"),
            Object(Matching, "melee/ft/kinds/ftKirby/ftkirbyspecialcaptain.c"),
            Object(Matching, "melee/ft/kinds/ftKirby/ftkirbyspecialpikachu.c"),
            Object(Matching, "melee/ft/kinds/ftKirby/ftkirbyspecialkoopa.c"),
            Object(Matching, "melee/ft/kinds/ftKirby/ftkirbyspeciallink.c"),
            Object(Matching, "melee/ft/kinds/ftKirby/ftkirbyspecialsamus.c"),
            Object(Matching, "melee/ft/kinds/ftKirby/ftKb_SpecialNFx.c"),
            Object(Matching, "melee/ft/kinds/ftKirby/ftkirbyspecialfox.c"),
            Object(Matching, "melee/ft/kinds/ftKirby/ftkirbyspecialness.c"),
            Object(Matching, "melee/ft/kinds/ftKirby/ftkirbyspecialdonkey.c"),
            Object(Matching, "melee/ft/kinds/ftKirby/ftkirbyspecialpurin.c"),
            Object(Matching, "melee/ft/kinds/ftKirby/ftkirbyspecialzelda.c"),
            Object(Matching, "melee/ft/kinds/ftKirby/ftkirbyspecialseak.c"),
            Object(Matching, "melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c"),
            Object(Matching, "melee/ft/kinds/ftKirby/ftkirbyspecialiceclimber.c"),
            Object(Matching, "melee/ft/kinds/ftKirby/ftkirbyspecialyoshi.c"),
            Object(Matching, "melee/ft/kinds/ftKirby/ftkirbycaptureyoshi.c"),
            Object(Matching, "melee/ft/kinds/ftKirby/ftkirbyyoshiegg.c"),
            Object(Matching, "melee/ft/kinds/ftKirby/ftkirbyspecialmars.c"),
            Object(Matching, "melee/ft/kinds/ftKirby/ftkirbyspecialpeach.c"),
            Object(Matching, "melee/ft/kinds/ftKirby/ftkirbyspecialgamewatch.c"),
            # Donkey Kong
            Object(Matching, "melee/ft/kinds/ftDonkey/ftdonkey.c"),
            Object(Matching, "melee/ft/kinds/ftDonkey/ftdonkeyspeciallw.c"),
            Object(Matching, "melee/ft/kinds/ftDonkey/ftdonkeyspecials.c"),
            Object(Matching, "melee/ft/kinds/ftDonkey/ftdonkeyspecialn.c"),
            Object(Matching, "melee/ft/kinds/ftDonkey/ftdonkeyspecialhi.c"),
            # Sheik
            Object(Matching, "melee/ft/kinds/ftSeak/ftseak.c"),
            Object(Matching, "melee/ft/kinds/ftSeak/ftseakspecials.c"),
            Object(Matching, "melee/ft/kinds/ftSeak/ftseakspecialn.c"),
            Object(Matching, "melee/ft/kinds/ftSeak/ftseakspecialhi.c"),
            Object(Matching, "melee/ft/kinds/ftSeak/ftseakspeciallw.c"),
            # Ness
            Object(Matching, "melee/ft/kinds/ftNess/ftness.c"),
            Object(Matching, "melee/ft/kinds/ftNess/ftnessattacks4.c"),
            Object(Matching, "melee/ft/kinds/ftNess/ftnessattackhi4.c"),
            Object(Matching, "melee/ft/kinds/ftNess/ftnessattacklw4.c"),
            Object(Matching, "melee/ft/kinds/ftNess/ftnessspecials.c"),
            Object(Matching, "melee/ft/kinds/ftNess/ftnessspecialn.c"),
            Object(Matching, "melee/ft/kinds/ftNess/ftnessspecialhi.c"),
            Object(Matching, "melee/ft/kinds/ftNess/ftnessspeciallw.c"),
            # Peach
            Object(Matching, "melee/ft/kinds/ftPeach/ftpeach.c"),
            Object(Matching, "melee/ft/kinds/ftPeach/ftpeachfloat.c"),
            Object(Matching, "melee/ft/kinds/ftPeach/ftpeachfloatfall.c"),
            Object(Matching, "melee/ft/kinds/ftPeach/ftpeachfloatattack.c"),
            Object(Matching, "melee/ft/kinds/ftPeach/ftpeachattacks4.c"),
            Object(Matching, "melee/ft/kinds/ftPeach/ftpeachspecials.c"),
            Object(Matching, "melee/ft/kinds/ftPeach/ftpeachspeciallw.c"),
            Object(Matching, "melee/ft/kinds/ftPeach/ftpeachspecialhi.c"),
            Object(Matching, "melee/ft/kinds/ftPeach/ftpeachspecialn.c"),
            # Popo
            Object(Matching, "melee/ft/kinds/ftPopo/ftpopo.c"),
            Object(Matching, "melee/ft/kinds/ftPopo/ftpopospecialn.c"),
            Object(Matching, "melee/ft/kinds/ftPopo/ftpopospecials.c"),
            Object(Matching, "melee/ft/kinds/ftPopo/ftpopospecialhi.c"),
            Object(Matching, "melee/ft/kinds/ftPopo/ftpopospeciallw.c"),
            # Nana
            Object(Matching, "melee/ft/kinds/ftNana/ftnana.c"),
            Object(Matching, "melee/ft/kinds/ftNana/ftnanaspecialhi.c"),
            Object(Matching, "melee/ft/kinds/ftNana/ftnanaspecials.c"),
            # Pikachu
            Object(Matching, "melee/ft/kinds/ftPikachu/ftpikachu.c"),
            Object(Matching, "melee/ft/kinds/ftPikachu/ftpikachuspecialn.c"),
            Object(Matching, "melee/ft/kinds/ftPikachu/ftpikachuspecials.c"),
            Object(Matching, "melee/ft/kinds/ftPikachu/ftpikachuspecialhi.c"),
            Object(Matching, "melee/ft/kinds/ftPikachu/ftpikachuspeciallw.c"),
            # Samus
            Object(Matching, "melee/ft/kinds/ftSamus/ftsamus.c"),
            Object(Matching, "melee/ft/kinds/ftSamus/ftsamusspeciallw0.c"),
            Object(Matching, "melee/ft/kinds/ftSamus/ftsamusspecialn.c"),
            Object(Matching, "melee/ft/kinds/ftSamus/ftsamusspecials.c"),
            Object(Matching, "melee/ft/kinds/ftSamus/ftsamusspecialhi.c"),
            Object(Matching, "melee/ft/kinds/ftSamus/ftsamusspeciallw1.c"),
            # Yoshi
            Object(Matching, "melee/ft/kinds/ftYoshi/ftyoshi.c"),
            Object(Matching, "melee/ft/kinds/ftYoshi/ftyoshiguard.c"),
            Object(Matching, "melee/ft/kinds/ftYoshi/ftyoshispecialn.c"),
            Object(Matching, "melee/ft/kinds/ftYoshi/ftyoshispecialhi.c"),
            Object(Matching, "melee/ft/kinds/ftYoshi/ftyoshispeciallw.c"),
            Object(Matching, "melee/ft/kinds/ftYoshi/ftyoshispecials.c"),
            # Bowser
            Object(Matching, "melee/ft/kinds/ftKoopa/ftkoopa.c"),
            Object(Matching, "melee/ft/kinds/ftKoopa/ftkoopaspecials.c"),
            Object(Matching, "melee/ft/kinds/ftKoopa/ftkoopaspeciallw.c"),
            Object(Matching, "melee/ft/kinds/ftKoopa/ftkoopaspecialn.c"),
            Object(Matching, "melee/ft/kinds/ftKoopa/ftkoopaspecialhi.c"),
            # Marth
            Object(Matching, "melee/ft/kinds/ftMars/ftmars.c"),
            Object(Matching, "melee/ft/kinds/ftMars/ftmarsspecialn.c"),
            Object(Matching, "melee/ft/kinds/ftMars/ftmarsspecials.c"),
            Object(Matching, "melee/ft/kinds/ftMars/ftmarsspecialhi.c"),
            Object(Matching, "melee/ft/kinds/ftMars/ftmarsspeciallw.c"),
            # Zelda
            Object(Matching, "melee/ft/kinds/ftZelda/ftzelda.c"),
            Object(Matching, "melee/ft/kinds/ftZelda/ftzeldaspecialhi.c"),
            Object(Matching, "melee/ft/kinds/ftZelda/ftzeldaspecialn.c"),
            Object(Matching, "melee/ft/kinds/ftZelda/ftzeldaspeciallw.c"),
            Object(Matching, "melee/ft/kinds/ftZelda/ftzeldaspecials.c"),
            # Jigglypuff
            Object(Matching, "melee/ft/kinds/ftPurin/ftpurin.c"),
            Object(Matching, "melee/ft/kinds/ftPurin/ftpurinspecialhi.c"),
            Object(Matching, "melee/ft/kinds/ftPurin/ftpurinspeciallw.c"),
            Object(Matching, "melee/ft/kinds/ftPurin/ftpurinspecials.c"),
            Object(Matching, "melee/ft/kinds/ftPurin/ftpurinspecialn.c"),
            # Luigi
            Object(Matching, "melee/ft/kinds/ftLuigi/ftluigi.c"),
            Object(Matching, "melee/ft/kinds/ftLuigi/ftluigispecialn.c"),
            Object(Matching, "melee/ft/kinds/ftLuigi/ftluigispecials.c"),
            Object(Matching, "melee/ft/kinds/ftLuigi/ftluigispecialhi.c"),
            Object(Matching, "melee/ft/kinds/ftLuigi/ftluigispeciallw.c"),
            # Mewtwo
            Object(Matching, "melee/ft/kinds/ftMewtwo/ftmewtwo.c"),
            Object(Matching, "melee/ft/kinds/ftMewtwo/ftmewtwospecialhi.c"),
            Object(Matching, "melee/ft/kinds/ftMewtwo/ftmewtwospeciallw.c"),
            Object(Matching, "melee/ft/kinds/ftMewtwo/ftmewtwospecials.c"),
            Object(Matching, "melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c"),
            # Young Link
            Object(Matching, "melee/ft/kinds/ftCLink/ftclink.c"),
            Object(Matching, "melee/ft/kinds/ftCLink/ftclinkappeals.c"),
            # Dr. Mario
            Object(Matching, "melee/ft/kinds/ftDrMario/ftdrmario.c"),
            Object(Matching, "melee/ft/kinds/ftDrMario/ftdrmarioappeals.c"),
            # Falco
            Object(Matching, "melee/ft/kinds/ftFalco/ftfalco.c"),
            # Pichu
            Object(Matching, "melee/ft/kinds/ftPichu/ftpichu.c"),
            # Mr. Game & Watch
            Object(Matching, "melee/ft/kinds/ftGameWatch/ftgamewatch.c"),
            Object(Matching, "melee/ft/kinds/ftGameWatch/ftgamewatchattacks4.c"),
            Object(Matching, "melee/ft/kinds/ftGameWatch/ftgamewatchattacklw3.c"),
            Object(Matching, "melee/ft/kinds/ftGameWatch/ftgamewatchattackair.c"),
            Object(Matching, "melee/ft/kinds/ftGameWatch/ftgamewatchattack11.c"),
            Object(Matching, "melee/ft/kinds/ftGameWatch/ftgamewatchattack100.c"),
            Object(Matching, "melee/ft/kinds/ftGameWatch/ftgamewatchspecials.c"),
            Object(Matching, "melee/ft/kinds/ftGameWatch/ftgamewatchspeciallw.c"),
            Object(Matching, "melee/ft/kinds/ftGameWatch/ftgamewatchspecialhi.c"),
            Object(Matching, "melee/ft/kinds/ftGameWatch/ftgamewatchspecialn.c"),
            # Ganondorf
            Object(Matching, "melee/ft/kinds/ftGanon/ftganon.c"),
            # Roy
            Object(Matching, "melee/ft/kinds/ftEmblem/ftemblem.c"),
            # Wireframe (boy)
            Object(Matching, "melee/ft/kinds/ftZakoBoy/ftboy.c"),
            # Wireframe (girl)
            Object(Matching, "melee/ft/kinds/ftZakoGirl/ftgirl.c"),
            # Giga Koopa
            Object(Matching, "melee/ft/kinds/ftGigaKoopa/ftgkoopa.c"),
            # Sandbag
            Object(Matching, "melee/ft/kinds/ftSandbag/ftsandbag.c"),
            # Master Hand
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhand.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandwait10.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandwait12.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandentry.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhanddamage0.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandsweep.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandsweepwait.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandslap.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandwalk.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhanddrill.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandrockcrush.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandpapercrush.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandpoke.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandfingerbeam.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandfingergun.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandfingergun3.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandbackairplane1.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandbackairplane2.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandbackairplane3.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandbackcrush0.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandbackcrush1.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandbackdisappear.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandsqueeze.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandwait11.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandsqueezing.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandthrow.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandslam.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandtagcrush.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandtagapplaud.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandtagrockpaper.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandtagcancel.c"),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandcapturemasterhand.c"),
            Object(
                Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandcapturedamagemasterhand.c"
            ),
            Object(Matching, "melee/ft/kinds/ftMasterHand/ftmasterhandthrownmasterhand.c"),
            # Crazy Hand
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhand.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandwait10.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandentry.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhanddamage0.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandsweep.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandsweepwait.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandwalk.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhanddrill.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandrockcrush0.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandrockcrush1.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandpoke.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandfingerbeam0.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandfingerbeam.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandbackairplane1.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandbackairplane2.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandbackairplane3.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandbackcrush.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandbackdisappear.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandwait11.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandgrab.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandcancel.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandsqueezing0.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandsqueezing1.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandsqueeze.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandthrow.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandslam.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandtagrockpaper.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandfingergun2.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandtaggrab.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandgrabunk1b174.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandcapturecrazyhand.c"),
            Object(
                Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandcapturedamagecrazyhand.c"
            ),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandcapturewaitcrazyhand.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandthrowncrazyhand.c"),
            Object(Matching, "melee/ft/kinds/ftCrazyHand/ftcrazyhandtagcancel.c"),
            # Main
            Object(Matching, "melee/ft/ftbosslib.c"),
        ],
    ),
    MeleeLib(
        "gm (Main game loop)",
        [
            Object(Matching, "melee/gm/gmmain_lib.c"),
            Object(Matching, "melee/gm/gmmain.c"),
            Object(Matching, "melee/gm/gm_1601.c"),
            Object(Linkable, "melee/gm/gm_16A2.c"),
            Object(Matching, "melee/gm/gm_16AE.c"),
            Object(Matching, "melee/gm/gm_16F1.c"),
            Object(Matching, "melee/gm/gm_1736.c"),
            Object(Matching, "melee/gm/gmresult.c"),
            Object(Linkable, "melee/gm/gmresultplayer.c"),
            Object(Matching, "melee/gm/gm_17AD.c"),
            Object(Matching, "melee/gm/gm_17BA.c"),
            Object(Matching, "melee/gm/gmregcommon.c"),
            Object(Linkable, "melee/gm/gmregclear.c"),
            Object(Matching, "melee/gm/gm_1832.c"),
            Object(Matching, "melee/gm/gm_186E.c"),
            Object(Matching, "melee/gm/gm_1879.c"),
            Object(Linkable, "melee/gm/gm_1884.c"),
            Object(Linkable, "melee/gm/gmtoulib.c"),
            Object(Matching, "melee/gm/gmtou_0.c"),
            Object(Matching, "melee/gm/gmtou_1.c"),
            Object(Linkable, "melee/gm/gmtou_2.c"),
            Object(Matching, "melee/gm/gm_19EF.c"),
            Object(Matching, "melee/gm/gmpause.c"),
            Object(Matching, "melee/gm/gmtitle.c"),
            Object(Matching, "melee/gm/gmcamera.c"),
            Object(Matching, "melee/gm/gm_1A33.c"),
            Object(Matching, "melee/gm/gm_1A36.c"),
            Object(Matching, "melee/gm/gm_1A3F.c"),
            Object(Matching, "melee/gm/gm_1A45.c"),
            Object(Matching, "melee/gm/gmscdata.c"),
            Object(Matching, "melee/gm/gmmenu.c"),
            Object(Matching, "melee/gm/gmvsmelee.c"),
            Object(Matching, "melee/gm/gmmovieend.c"),
            Object(Matching, "melee/gm/gmregtyfall.c"),
            Object(Matching, "melee/gm/gm_1A7A.c"),
            Object(Matching, "melee/gm/gmregenddisp.c"),
            Object(Matching, "melee/gm/gm_1A9B.c"),
            Object(Matching, "melee/gm/gmopening.c"),
            Object(Linkable, "melee/gm/gmstaffroll.c"),
            Object(Matching, "melee/gm/gmhowto.c"),
            Object(Matching, "melee/gm/gmomake15.c"),
            Object(Matching, "melee/gm/gmprogressive.c"),
            Object(Matching, "melee/gm/gmapproach.c"),
            Object(Matching, "melee/gm/gm_1ADD.c"),
            Object(Matching, "melee/gm/gm_1AED.c"),
            Object(Matching, "melee/gm/gm_1B03.c"),
            # Game modes
            Object(Matching, "melee/gm/gmtitlemode.c"),
            Object(Matching, "melee/gm/gmdebugmode.c"),
            Object(Matching, "melee/gm/gmmenumode.c"),
            Object(Matching, "melee/gm/gmvsmode.c"),
            Object(Matching, "melee/gm/gmtoumode.c"),
            Object(Matching, "melee/gm/gmcameramode.c"),
            Object(Matching, "melee/gm/gmtrainingmode.c"),
            Object(Matching, "melee/gm/gmclassic.c"),
            Object(Matching, "melee/gm/gmadventure.c"),
            Object(Linkable, "melee/gm/gmallstar.c"),
            Object(Matching, "melee/gm/gmmultiman.c"),
            Object(Matching, "melee/gm/gmsupersudden.c"),
            Object(Matching, "melee/gm/gmtiny.c"),
            Object(Matching, "melee/gm/gmgiant.c"),
            Object(Matching, "melee/gm/gmstamina.c"),
            Object(Matching, "melee/gm/gmhomerun.c"),
            Object(Matching, "melee/gm/gmfixedcamera.c"),
            Object(Matching, "melee/gm/gmsinglebutton.c"),
            Object(Matching, "melee/gm/gminvisible.c"),
            Object(Matching, "melee/gm/gmslomo.c"),
            Object(Matching, "melee/gm/gmlightning.c"),
            Object(Matching, "melee/gm/gmevent.c"),
            Object(Matching, "melee/gm/gmtoygallery.c"),
            Object(Matching, "melee/gm/gmtoylottery.c"),
            Object(Matching, "melee/gm/gmtoycollection.c"),
            Object(Matching, "melee/gm/gmhanyucss.c"),
            Object(Matching, "melee/gm/gmhanyusss.c"),
            Object(Matching, "melee/gm/gmgover.c"),
            Object(Matching, "melee/gm/gmopeningmode.c"),
            Object(Matching, "melee/gm/gmprogressivemode.c"),
            Object(Matching, "melee/gm/gmboot.c"),
            Object(Matching, "melee/gm/gm_1BFA.c"),
        ],
    ),
    MeleeLib(
        "gr (Ground, stages)",
        [
            # Main
            Object(Matching, "melee/gr/ground.c"),
            Object(Matching, "melee/gr/grdisplay.c"),
            Object(Matching, "melee/gr/grdatfiles.c"),
            Object(Matching, "melee/gr/granime.c"),
            Object(Matching, "melee/gr/grmaterial.c"),
            Object(Matching, "melee/gr/grlib.c"),
            Object(Matching, "melee/gr/grdynamicattr.c"),
            Object(Matching, "melee/gr/grzakogenerator.c"),
            # Individual stages
            Object(Matching, "melee/gr/grfzerocar.c"),
            Object(Matching, "melee/gr/grizumi.c"),
            Object(Matching, "melee/gr/grcastle.c"),
            Object(Matching, "melee/gr/grpstadium.c"),
            Object(Matching, "melee/gr/grkongo.c"),
            Object(Matching, "melee/gr/grzebes.c"),
            Object(Matching, "melee/gr/grcorneria.c"),
            Object(Matching, "melee/gr/grstory.c"),
            Object(Matching, "melee/gr/gronett.c"),
            Object(Linkable, "melee/gr/grbigblue.c"),
            Object(Matching, "melee/gr/grmutecity.c"),
            Object(Matching, "melee/gr/grfourside.c"),
            Object(Matching, "melee/gr/grgreatbay.c"),
            Object(Matching, "melee/gr/gricemt.c"),
            Object(Linkable, "melee/gr/grinishie1.c"),
            Object(Matching, "melee/gr/grinishie2.c"),
            Object(Matching, "melee/gr/grkraid.c"),
            Object(Matching, "melee/gr/grrcruise.c"),
            Object(Matching, "melee/gr/grshrine.c"),
            Object(Matching, "melee/gr/gryorster.c"),
            Object(Matching, "melee/gr/grgarden.c"),
            Object(Matching, "melee/gr/grvenom.c"),
            Object(Matching, "melee/gr/grtest.c"),
            Object(Matching, "melee/gr/grkinokoroute.c"),
            Object(Matching, "melee/gr/grshrineroute.c"),
            Object(Matching, "melee/gr/grzebesroute.c"),
            Object(Matching, "melee/gr/grbigblueroute.c"),
            Object(Matching, "melee/gr/grfigure1.c"),
            Object(Matching, "melee/gr/grfigure2.c"),
            Object(Matching, "melee/gr/grfigure3.c"),
            Object(Matching, "melee/gr/groldyoshi.c"),
            Object(Matching, "melee/gr/groldkongo.c"),
            Object(Matching, "melee/gr/groldpupupu.c"),
            Object(Matching, "melee/gr/grpura.c"),
            Object(Matching, "melee/gr/grgreens.c"),
            Object(Matching, "melee/gr/grflatzone.c"),
            Object(Matching, "melee/gr/grpushon.c"),
            Object(Matching, "melee/gr/grfigureget.c"),
            Object(Matching, "melee/gr/grbattle.c"),
            Object(Matching, "melee/gr/grlast.c"),
            Object(Matching, "melee/gr/grhomerun.c"),
            Object(Matching, "melee/gr/grheal.c"),
            # Break the Targets stages
            Object(Matching, "melee/gr/grtmario.c"),
            Object(Matching, "melee/gr/grtcaptain.c"),
            Object(Matching, "melee/gr/grtclink.c"),
            Object(Matching, "melee/gr/grtdonkey.c"),
            Object(Matching, "melee/gr/grtdrmario.c"),
            Object(Matching, "melee/gr/grtfalco.c"),
            Object(Matching, "melee/gr/grtfox.c"),
            Object(Matching, "melee/gr/grticeclimber.c"),
            Object(Matching, "melee/gr/grtkirby.c"),
            Object(Matching, "melee/gr/grtkoopa.c"),
            Object(Matching, "melee/gr/grtlink.c"),
            Object(Matching, "melee/gr/grtluigi.c"),
            Object(Matching, "melee/gr/grtmars.c"),
            Object(Matching, "melee/gr/grtmewtwo.c"),
            Object(Matching, "melee/gr/grtness.c"),
            Object(Matching, "melee/gr/grtpeach.c"),
            Object(Matching, "melee/gr/grtpichu.c"),
            Object(Matching, "melee/gr/grtpikachu.c"),
            Object(Matching, "melee/gr/grtpurin.c"),
            Object(Matching, "melee/gr/grtsamus.c"),
            Object(Matching, "melee/gr/grtseak.c"),
            Object(Matching, "melee/gr/grtyoshi.c"),
            Object(Matching, "melee/gr/grtzelda.c"),
            Object(Matching, "melee/gr/grtgamewatch.c"),
            Object(Matching, "melee/gr/grtemblem.c"),
            Object(Matching, "melee/gr/grtganon.c"),
            # Main
            Object(Matching, "melee/gr/stage.c"),
        ],
    ),
    MeleeLib(
        "db (Debug)",
        [
            Object(Matching, "melee/db/dbinit.c"),
            Object(Matching, "melee/db/dbitem.c"),
            Object(Matching, "melee/db/dbcpu.c"),
            Object(Matching, "melee/db/dbanim.c"),
            Object(Matching, "melee/db/dbcamera.c"),
            Object(Matching, "melee/db/dbsound.c"),
            Object(Matching, "melee/db/dbeffect.c"),
            Object(Matching, "melee/db/dbscreenshot.c"),
            Object(Matching, "melee/db/dberror.c"),
            Object(Matching, "melee/db/dbbonus.c"),
            Object(Matching, "melee/db/dballoc.c"),
        ],
    ),
    MeleeLib(
        "mn (Menus)",
        [
            Object(Matching, "melee/mn/mnmain.c"),
            Object(Matching, "melee/mn/mn_22EC.c"),
            Object(Linkable, "melee/mn/mnmainrule.c"),
            Object(Linkable, "melee/mn/mnruleplus.c"),
            Object(Linkable, "melee/mn/mnitemsw.c"),
            Object(Linkable, "melee/mn/mnstagesw.c"),
            Object(Linkable, "melee/mn/mnname.c"),
            Object(Linkable, "melee/mn/mnnamenew.c"),
            Object(Linkable, "melee/mn/mndiagram.c"),
            Object(Linkable, "melee/mn/mndiagram2.c"),
            Object(Linkable, "melee/mn/mndiagram3.c"),
            Object(Linkable, "melee/mn/mnvibration.c"),
            Object(Linkable, "melee/mn/mnsound.c"),
            Object(Matching, "melee/mn/mndeflicker.c"),
            Object(Matching, "melee/mn/mnsoundtest.c"),
            Object(Matching, "melee/mn/mnlanguage.c"),
            Object(Matching, "melee/mn/mnhyaku.c"),
            Object(Matching, "melee/mn/mnevent.c"),
            Object(Matching, "melee/mn/mndatadel.c"),
            Object(Matching, "melee/mn/mncount.c"),
            Object(Matching, "melee/mn/mninfo.c"),
            Object(Matching, "melee/mn/mninfobonus.c"),
            Object(Linkable, "melee/mn/mnsnap.c"),
            Object(Matching, "melee/mn/mngallery.c"),
            Object(Matching, "melee/mn/mnstagesel.c"),
            Object(Matching, "melee/mn/mncharsel.c"),
        ],
    ),
    MeleeLib(
        "it (Items)",
        [
            # Main
            Object(Matching, "melee/it/item.c"),
            Object(Matching, "melee/it/it_26B1.c"),
            Object(Matching, "melee/it/itspawn.c"),
            Object(Matching, "melee/it/itgroundcoll.c"),
            Object(Matching, "melee/it/itdraw.c"),
            Object(Matching, "melee/it/itdrop.c"),
            Object(Matching, "melee/it/itcoll.c"),
            Object(Matching, "melee/it/it_3F14.c"),
            Object(Matching, "melee/it/it_2725.c"),
            Object(Matching, "melee/it/ithitbox.c"),
            Object(Matching, "melee/it/itmaplib.c"),
            Object(Matching, "melee/it/itmaterial.c"),
            Object(Matching, "melee/it/iteffect.c"),
            Object(Matching, "melee/it/itanimlist.c"),
            Object(Matching, "melee/it/it_279C.c"),
            Object(Matching, "melee/it/it_3F2F.c"),
            Object(Matching, "melee/it/itzako.c"),
            # Individual items
            Object(Matching, "melee/it/kinds/itcapsule.c"),
            Object(Matching, "melee/it/kinds/itbombhei.c"),
            Object(Matching, "melee/it/kinds/itdosei.c"),
            Object(Matching, "melee/it/kinds/itheart.c"),
            Object(Matching, "melee/it/kinds/ittomato.c"),
            Object(Matching, "melee/it/kinds/itstar.c"),
            Object(Matching, "melee/it/kinds/itbat.c"),
            Object(Matching, "melee/it/kinds/itsword.c"),
            Object(Matching, "melee/it/kinds/itbox.c"),
            Object(Matching, "melee/it/kinds/ittaru.c"),
            Object(Matching, "melee/it/kinds/itegg.c"),
            Object(Matching, "melee/it/kinds/itkusudama.c"),
            Object(Matching, "melee/it/kinds/itparasol.c"),
            Object(Matching, "melee/it/kinds/itgshell.c"),
            Object(Matching, "melee/it/kinds/itrshell.c"),
            Object(Matching, "melee/it/kinds/itlgun.c"),
            Object(Matching, "melee/it/kinds/itfreeze.c"),
            Object(Matching, "melee/it/kinds/itfoods.c"),
            Object(Matching, "melee/it/kinds/itmsbomb.c"),
            Object(Matching, "melee/it/kinds/itflipper.c"),
            Object(Matching, "melee/it/kinds/itsscope.c"),
            Object(Matching, "melee/it/kinds/itstarrod.c"),
            Object(Matching, "melee/it/kinds/itharisen.c"),
            Object(Matching, "melee/it/kinds/itfflower.c"),
            Object(Matching, "melee/it/kinds/itkinoko.c"),
            Object(Matching, "melee/it/kinds/itdkinoko.c"),
            Object(Matching, "melee/it/kinds/ithammer.c"),
            Object(Matching, "melee/it/kinds/itwstar.c"),
            Object(Matching, "melee/it/kinds/itscball.c"),
            Object(Matching, "melee/it/kinds/itrabbitc.c"),
            Object(Matching, "melee/it/kinds/itmetalb.c"),
            Object(Matching, "melee/it/kinds/itlipstick.c"),
            Object(Matching, "melee/it/kinds/itspycloak.c"),
            Object(Matching, "melee/it/kinds/ittarucann.c"),
            Object(Matching, "melee/it/kinds/itmball.c"),
            Object(Matching, "melee/it/kinds/itlgunray.c"),
            Object(Matching, "melee/it/kinds/itstarrodstar.c"),
            Object(Matching, "melee/it/kinds/itsscopebeam.c"),
            Object(Matching, "melee/it/kinds/itlgunbeam.c"),
            Object(Matching, "melee/it/kinds/ithammerhead.c"),
            Object(Matching, "melee/it/kinds/itlipstickspore.c"),
            Object(Matching, "melee/it/kinds/itfflowerflame.c"),
            Object(Matching, "melee/it/kinds/itevyoshiegg.c"),
            # Fighter-related items
            Object(Matching, "melee/it/kinds/itmariofireball.c"),
            Object(Matching, "melee/it/kinds/itkirbycutterbeam.c"),
            Object(Matching, "melee/it/kinds/itfoxlaser.c"),
            Object(Matching, "melee/it/kinds/itfoxillusion.c"),
            Object(Matching, "melee/it/kinds/itlinkbomb.c"),
            Object(Matching, "melee/it/kinds/itlinkboomerang.c"),
            Object(Matching, "melee/it/kinds/itlinkhookshot.c"),
            Object(Matching, "melee/it/kinds/itlinkarrow.c"),
            Object(Matching, "melee/it/kinds/itnesspkfire.c"),
            Object(Matching, "melee/it/kinds/itnesspkfirepillar.c"),
            Object(Matching, "melee/it/kinds/itnesspkflash.c"),
            Object(Matching, "melee/it/kinds/itnesspkthunderball.c"),
            Object(Matching, "melee/it/kinds/itnesspkthundertrail.c"),
            Object(Matching, "melee/it/kinds/itkoopaflame.c"),
            Object(Matching, "melee/it/kinds/itnessbat.c"),
            Object(Matching, "melee/it/kinds/it_2ADA.c"),
            Object(Matching, "melee/it/kinds/itkirbyhammer.c"),
            Object(Matching, "melee/it/kinds/itfoxblaster.c"),
            Object(Matching, "melee/it/kinds/itlinkbow.c"),
            Object(Matching, "melee/it/kinds/itnesspkflashexplode.c"),
            Object(Matching, "melee/it/kinds/itseakneedlethrown.c"),
            Object(Matching, "melee/it/kinds/itseakneedleheld.c"),
            Object(Matching, "melee/it/kinds/itseakvanish.c"),
            Object(Matching, "melee/it/kinds/itpikachuthunder.c"),
            Object(Matching, "melee/it/kinds/itmariocape.c"),
            Object(Matching, "melee/it/kinds/ityoshieggthrow.c"),
            Object(Matching, "melee/it/kinds/ityoshistar.c"),
            Object(Matching, "melee/it/kinds/itpikachutjoltground.c"),
            Object(Matching, "melee/it/kinds/itpikachutjoltair.c"),
            Object(Matching, "melee/it/kinds/itsamusbomb.c"),
            Object(Matching, "melee/it/kinds/itsamuschargeshot.c"),
            Object(Matching, "melee/it/kinds/itsamusmissile.c"),
            Object(Matching, "melee/it/kinds/itsamusgrapple.c"),
            Object(Matching, "melee/it/kinds/itseakchain.c"),
            Object(Matching, "melee/it/kinds/itpeachexplode.c"),
            Object(Matching, "melee/it/kinds/itpeachturnip.c"),
            Object(Matching, "melee/it/kinds/itpeachparasol.c"),
            Object(Matching, "melee/it/kinds/itpeachtoad.c"),
            Object(Matching, "melee/it/kinds/itpeachtoadspore.c"),
            Object(Matching, "melee/it/kinds/itnessyoyo.c"),
            Object(Matching, "melee/it/kinds/itluigifireball.c"),
            Object(Matching, "melee/it/kinds/itdrmariopill.c"),
            Object(Matching, "melee/it/kinds/itclimbersice.c"),
            Object(Matching, "melee/it/kinds/itclimbersblizzard.c"),
            Object(Matching, "melee/it/kinds/itclimbersstring.c"),
            Object(Matching, "melee/it/kinds/itzeldadinfire.c"),
            Object(Matching, "melee/it/kinds/itzeldadinfireexplode.c"),
            Object(Matching, "melee/it/kinds/itmewtwodisable.c"),
            Object(Matching, "melee/it/kinds/itmewtwoshadowball.c"),
            Object(Matching, "melee/it/kinds/itgamewatchgreenhouse.c"),
            Object(Matching, "melee/it/kinds/itgamewatchmanhole.c"),
            Object(Matching, "melee/it/kinds/itgamewatchfire.c"),
            Object(Matching, "melee/it/kinds/itgamewatchparachute.c"),
            Object(Matching, "melee/it/kinds/itgamewatchturtle.c"),
            Object(Matching, "melee/it/kinds/itgamewatchbreath.c"),
            Object(Matching, "melee/it/kinds/itkirbygamewatchchefpan.c"),
            Object(Matching, "melee/it/kinds/itgamewatchjudge.c"),
            Object(Matching, "melee/it/kinds/itgamewatchpanic.c"),
            Object(Matching, "melee/it/kinds/itgamewatchrescue.c"),
            Object(Matching, "melee/it/kinds/itgamewatchchef.c"),
            Object(Matching, "melee/it/kinds/itclinkmilk.c"),
            # Pokémon
            Object(Matching, "melee/it/kinds/ittosakinto.c"),
            Object(Matching, "melee/it/kinds/itchicorita.c"),
            Object(Matching, "melee/it/kinds/itkabigon.c"),
            Object(Matching, "melee/it/kinds/itkamex.c"),
            Object(Matching, "melee/it/kinds/itmatadogas.c"),
            Object(Matching, "melee/it/kinds/itlizardon.c"),
            Object(Matching, "melee/it/kinds/itfire.c"),
            Object(Matching, "melee/it/kinds/itthunder.c"),
            Object(Matching, "melee/it/kinds/itfreezer.c"),
            Object(Matching, "melee/it/kinds/itsonans.c"),
            Object(Matching, "melee/it/kinds/ithassam.c"),
            Object(Matching, "melee/it/kinds/itunknown.c"),
            Object(Matching, "melee/it/kinds/itentei.c"),
            Object(Matching, "melee/it/kinds/itraikou.c"),
            Object(Matching, "melee/it/kinds/itsuikun.c"),
            Object(Matching, "melee/it/kinds/itkireihana.c"),
            Object(Matching, "melee/it/kinds/itmarumine.c"),
            Object(Matching, "melee/it/kinds/itlugia.c"),
            Object(Matching, "melee/it/kinds/ithouou.c"),
            Object(Matching, "melee/it/kinds/itmetamon.c"),
            Object(Matching, "melee/it/kinds/itpippi.c"),
            Object(Matching, "melee/it/kinds/ittogepy.c"),
            Object(Matching, "melee/it/kinds/itmew.c"),
            Object(Matching, "melee/it/kinds/itcerebi.c"),
            Object(Matching, "melee/it/kinds/ithitodeman.c"),
            Object(Matching, "melee/it/kinds/itlucky.c"),
            Object(Matching, "melee/it/kinds/itporygon2.c"),
            Object(Matching, "melee/it/kinds/ithinoarashi.c"),
            Object(Matching, "melee/it/kinds/itmaril.c"),
            Object(Matching, "melee/it/kinds/itfushigibana.c"),
            # Indivudal items
            Object(Matching, "melee/it/kinds/itoldkuri.c"),
            Object(Matching, "melee/it/kinds/itmato.c"),
            Object(Matching, "melee/it/kinds/itheiho.c"),
            Object(Matching, "melee/it/kinds/itlikelike.c"),
            Object(Matching, "melee/it/kinds/itnokonoko.c"),
            Object(Matching, "melee/it/kinds/itzgshell.c"),
            Object(Matching, "melee/it/kinds/itzrshell.c"),
            Object(Matching, "melee/it/kinds/itpatapata.c"),
            Object(Matching, "melee/it/kinds/itklap.c"),
            Object(Matching, "melee/it/kinds/itoldottosea.c"),
            Object(Matching, "melee/it/kinds/itwhitebea.c"),
            # Stage-related items
            Object(Matching, "melee/it/kinds/itoctarock.c"),
            Object(Matching, "melee/it/kinds/it_2E5A.c"),
            Object(Matching, "melee/it/kinds/ityaku.c"),
            Object(Matching, "melee/it/kinds/itarwinglaser.c"),
            Object(Matching, "melee/it/kinds/itoctarockstone.c"),
            Object(Matching, "melee/it/kinds/itleadead.c"),
            Object(Matching, "melee/it/kinds/itgreatfoxlaser.c"),
            Object(Matching, "melee/it/kinds/ittincle.c"),
            Object(Matching, "melee/it/kinds/itkyasarin.c"),
            Object(Matching, "melee/it/kinds/itwhispyapple.c"),
            Object(Matching, "melee/it/kinds/ittools.c"),
            Object(Matching, "melee/it/kinds/itkyasarinegg.c"),
            Object(Matching, "melee/it/kinds/itmasterhandlaser.c"),
            Object(Matching, "melee/it/kinds/itmasterhandbullet.c"),
            Object(Matching, "melee/it/kinds/itcrazyhandbomb.c"),
            Object(Matching, "melee/it/kinds/itcoin.c"),
            Object(Matching, "melee/it/kinds/itkirby_2F23.c"),
            Object(Matching, "melee/it/kinds/it_2F28.c"),
            Object(Matching, "melee/it/kinds/ityoshitongue.c"),
            Object(Matching, "melee/it/kinds/itkirbyyoshispecialn.c"),
            Object(Matching, "melee/it/kinds/ityoshiegglay.c"),
        ],
    ),
    MeleeLib(
        "if (User interface)",
        [
            Object(Matching, "melee/if/ifall.c"),
            Object(Matching, "melee/if/iftime.c"),
            Object(Matching, "melee/if/ifstatus.c"),
            Object(Matching, "melee/if/if_2F6E.c"),
            Object(Matching, "melee/if/if_2F72.c"),
            Object(Linkable, "melee/if/ifstock.c"),
            Object(Matching, "melee/if/ifmagnify.c"),
            Object(Matching, "melee/if/ifnametag.c"),
            Object(Matching, "melee/if/ifhazard.c"),
            Object(Matching, "melee/if/if_2FD9.c"),
            Object(Matching, "melee/if/ifprize.c"),
            Object(Matching, "melee/if/ifcoget.c"),
            Object(Matching, "melee/if/if_2FF2.c"),
            Object(Matching, "melee/if/soundtest.c"),
            Object(Matching, "melee/if/textdraw.c"),
            Object(Matching, "melee/if/textlib.c"),
            Object(Matching, "melee/if/textlib_1.c"),
        ],
    ),
    MeleeLib(
        "ty (Toy, trophies)",
        [
            Object(Matching, "melee/ty/toy.c"),
            Object(Matching, "melee/ty/tylist.c"),
            Object(Matching, "melee/ty/tyfigupon.c"),
            Object(Linkable, "melee/ty/tydisplay.c"),
        ],
    ),
    MeleeLib(
        "vi (Visual, cutscenes)",
        [
            Object(Matching, "melee/vi/vi.c"),
            Object(Matching, "melee/vi/vi0102.c"),
            Object(Matching, "melee/vi/vi0401.c"),
            Object(Matching, "melee/vi/vi0402.c"),
            Object(Matching, "melee/vi/vi0501.c"),
            Object(Matching, "melee/vi/vi0502.c"),
            Object(Matching, "melee/vi/vi0601.c"),
            Object(Matching, "melee/vi/vi0801.c"),
            Object(Matching, "melee/vi/vi1101.c"),
            Object(Matching, "melee/vi/vi1201v1.c"),
            Object(Matching, "melee/vi/vi1201v2.c"),
            Object(Matching, "melee/vi/vi1202.c"),
        ],
    ),
    MeleeLib(
        "sfx (Sound effects)",
        [
            Object(Matching, "melee/sfx/sfx_unk.c"),
            Object(Matching, "melee/sfx/crowdsfx.c"),
        ],
    ),
    RuntimeLib(
        "Gekko runtime",
        [
            Object(Matching, "Runtime/__mem.c"),
            Object(Matching, "Runtime/__va_arg.c"),
            Object(Matching, "Runtime/global_destructor_chain.c"),
            Object(Matching, "Runtime/Gecko_ExceptionPPC.c"),
            Object(Matching, "Runtime/Gecko_setjmp.c"),
            Object(Matching, "Runtime/runtime.c"),
            Object(Matching, "Runtime/__init_cpp_exceptions.c"),
        ],
    ),
    Libc(
        "MSL (Metrowerks Standard Libraries)",
        [
            Object(Matching, "MSL/abort_exit.c"),
            Object(Matching, "MSL/ansi_fp.c"),
            Object(Matching, "MSL/buffer_io.c"),
            Object(Matching, "MSL/PPC_EABI/critical_regions.gamecube.c"),
            Object(Matching, "MSL/ctype.c"),
            Object(Matching, "MSL/direct_io.c"),
            Object(Matching, "MSL/mbstring.c"),
            Object(Matching, "MSL/mem.c"),
            Object(Matching, "MSL/mem_funcs.c"),
            Object(Matching, "MSL/misc_io.c"),
            Object(Matching, "MSL/ansi_files.c"),
            Object(Matching, "MSL/printf.c"),
            Object(Matching, "MSL/rand.c"),
            Object(Matching, "MSL/string.c"),
            Object(Matching, "MSL/errno.c"),
            Object(Matching, "MSL/strtoul.c"),
            Object(Matching, "MSL/uart_console_io.c"),
            Object(Matching, "MSL/wchar_io.c"),
            Object(Matching, "MSL/math_1.c"),
            Object(Matching, "MSL/float.c"),
            Object(Matching, "MSL/trigf.c"),
            Object(Matching, "MSL/math.c"),
            Object(Matching, "MSL/math_data.c"),
        ],
    ),
    TRKLib(
        "MetroTRK (Metrowerks Target Resident Kernel)",
        [
            Object(Matching, "MetroTRK/mainloop.c"),
            Object(Matching, "MetroTRK/nubevent.c"),
            Object(Matching, "MetroTRK/nubinit.c"),
            Object(Matching, "MetroTRK/msg.c"),
            Object(Matching, "MetroTRK/msgbuf.c"),
            Object(Matching, "MetroTRK/serpoll.c"),
            Object(Matching, "MetroTRK/usr_put.c"),
            Object(Matching, "MetroTRK/dispatch.c"),
            Object(Matching, "MetroTRK/msghndlr.c"),
            Object(Matching, "MetroTRK/support.c"),
            Object(Matching, "MetroTRK/mutex_TRK.c"),
            Object(Matching, "MetroTRK/notify.c"),
            Object(Matching, "MetroTRK/flush_cache.c"),
            Object(Matching, "MetroTRK/mem_TRK.c"),
            Object(Matching, "MetroTRK/__exception.s"),
            Object(Matching, "MetroTRK/targimpl.c"),
            Object(Matching, "MetroTRK/dolphin_trk.c"),
            Object(Matching, "MetroTRK/mpc_7xx_603e.c"),
            Object(Matching, "MetroTRK/main_TRK.c"),
            Object(Matching, "MetroTRK/dolphin_trk_glue.c"),
            Object(Matching, "MetroTRK/targcont.c"),
        ],
    ),
    DolphinLib(
        "amcstubs",
        [
            Object(Matching, "dolphin/amcstubs/AmcExi2Stubs.c"),
        ],
    ),
    DolphinLib(
        "OdemuExi2",
        [
            Object(Matching, "dolphin/odenotstub/odenotstub.c"),
        ],
    ),
    DolphinLib(
        "hio",
        [
            Object(Matching, "dolphin/hio/hio.c"),
        ],
        fix_epilogue=True,
    ),
    DolphinLib(
        "mcc",
        [
            Object(Matching, "dolphin/mcc/mcc.c"),
            Object(Matching, "dolphin/mcc/fio.c"),
        ],
    ),
    DolphinLib(
        "thp",
        [
            Object(Matching, "dolphin/thp/THPDec.c"),
        ],
    ),
    DolphinLib(
        "base",
        [
            Object(Matching, "dolphin/base/PPCArch.c"),
        ],
    ),
    DolphinLib(
        "db",
        [
            Object(Matching, "dolphin/db/db.c"),
        ],
    ),
    DolphinLib(
        "dsp",
        [
            Object(Matching, "dolphin/dsp/dsp.c"),
            Object(Matching, "dolphin/dsp/dsp_debug.c"),
            Object(Matching, "dolphin/dsp/dsp_task.c"),
        ],
    ),
    DolphinLib(
        "dvd",
        [
            Object(Matching, "dolphin/dvd/dvdlow.c"),
            Object(Matching, "dolphin/dvd/dvdfs.c"),
            Object(Matching, "dolphin/dvd/dvd.c"),
            Object(Matching, "dolphin/dvd/dvdqueue.c"),
            Object(Matching, "dolphin/dvd/dvderror.c"),
            Object(Matching, "dolphin/dvd/fstload.c"),
        ],
    ),
    DolphinLib(
        "gx",
        [
            Object(Matching, "dolphin/gx/GXInit.c"),
            Object(Matching, "dolphin/gx/GXFifo.c"),
            Object(Matching, "dolphin/gx/GXAttr.c"),
            Object(Matching, "dolphin/gx/GXMisc.c"),
            Object(Matching, "dolphin/gx/GXGeometry.c"),
            Object(Matching, "dolphin/gx/GXFrameBuf.c"),
            Object(Matching, "dolphin/gx/GXLight.c"),
            Object(Matching, "dolphin/gx/GXTexture.c"),
            Object(Matching, "dolphin/gx/GXBump.c"),
            Object(Matching, "dolphin/gx/GXTev.c"),
            Object(Matching, "dolphin/gx/GXPixel.c"),
            Object(Matching, "dolphin/gx/GXStubs.c"),
            Object(Matching, "dolphin/gx/GXDisplayList.c"),
            Object(Matching, "dolphin/gx/GXTransform.c"),
            Object(Matching, "dolphin/gx/GXPerf.c"),
        ],
    ),
    DolphinLib(
        "mtx",
        [
            Object(Matching, "dolphin/mtx/mtx.c"),
            Object(Matching, "dolphin/mtx/mtxvec.c"),
            Object(Matching, "dolphin/mtx/mtx44.c"),
            Object(Matching, "dolphin/mtx/vec.c"),
        ],
        fix_epilogue=True,
    ),
    DolphinLib(
        "os",
        [
            Object(Matching, "dolphin/os/OS.c"),
            Object(Matching, "dolphin/os/OSAlarm.c"),
            Object(Matching, "dolphin/os/OSAlloc.c"),
            Object(Matching, "dolphin/os/OSArena.c"),
            Object(Matching, "dolphin/os/OSAudioSystem.c"),
            Object(Matching, "dolphin/os/OSCache.c"),
            Object(Matching, "dolphin/os/OSContext.c"),
            Object(Matching, "dolphin/os/OSError.c"),
            Object(Matching, "dolphin/os/OSExi.c"),
            Object(Matching, "dolphin/os/OSFont.c"),
            Object(Matching, "dolphin/os/OSInterrupt.c"),
            Object(Matching, "dolphin/os/OSLink.c"),
            Object(Matching, "dolphin/os/OSMemory.c"),
            Object(Matching, "dolphin/os/OSMutex.c"),
            Object(Matching, "dolphin/os/OSReboot.c"),
            Object(Matching, "dolphin/os/OSReset.c"),
            Object(Matching, "dolphin/os/OSResetSW.c"),
            Object(Matching, "dolphin/os/OSRtc.c"),
            Object(Matching, "dolphin/os/OSSerial.c"),
            Object(Matching, "dolphin/os/OSSync.c"),
            Object(Matching, "dolphin/os/OSThread.c"),
            Object(Matching, "dolphin/os/OSTime.c"),
            Object(Matching, "dolphin/os/OSUartExi.c"),
            Object(Matching, "dolphin/os/init/__start.c"),
            Object(Matching, "dolphin/os/init/__ppc_eabi_init.c"),
        ],
    ),
    DolphinLib(
        "pad",
        [
            Object(Matching, "dolphin/pad/PadClamp.c"),
            Object(Matching, "dolphin/pad/pad.c"),
        ],
        fix_epilogue=True,
    ),
    DolphinLib(
        "vi",
        [
            Object(Matching, "dolphin/vi/vi.c"),
        ],
    ),
    DolphinLib(
        "ai",
        [
            Object(Matching, "dolphin/ai/ai.c"),
        ],
    ),
    DolphinLib(
        "ar",
        [
            Object(Matching, "dolphin/ar/ar.c"),
            Object(Matching, "dolphin/ar/arq.c"),
        ],
    ),
    DolphinLib(
        "card",
        [
            Object(Matching, "dolphin/card/CARDBios.c"),
            Object(Matching, "dolphin/card/CARDUnlock.c"),
            Object(Matching, "dolphin/card/CARDRdwr.c"),
            Object(Matching, "dolphin/card/CARDBlock.c"),
            Object(Matching, "dolphin/card/CARDDir.c"),
            Object(Matching, "dolphin/card/CARDCheck.c"),
            Object(Matching, "dolphin/card/CARDMount.c"),
            Object(Matching, "dolphin/card/CARDFormat.c"),
            Object(Matching, "dolphin/card/CARDOpen.c"),
            Object(Matching, "dolphin/card/CARDCreate.c"),
            Object(Matching, "dolphin/card/CARDRead.c"),
            Object(Matching, "dolphin/card/CARDWrite.c"),
            Object(Matching, "dolphin/card/CARDDelete.c"),
            Object(Matching, "dolphin/card/CARDStat.c"),
            Object(Matching, "dolphin/card/CARDRename.c"),
        ],
        fix_epilogue=True,
    ),
    DolphinLib(
        "ax",
        [
            Object(Matching, "dolphin/ax/AX.c"),
            Object(Matching, "dolphin/ax/AXAlloc.c"),
            Object(Matching, "dolphin/ax/AXAux.c"),
            Object(Matching, "dolphin/ax/AXCL.c"),
            Object(Matching, "dolphin/ax/AXOut.c"),
            Object(Matching, "dolphin/ax/AXSPB.c"),
            Object(Matching, "dolphin/ax/AXVPB.c"),
            Object(Matching, "dolphin/ax/AXProf.c"),
            Object(Matching, "dolphin/ax/DSPCode.c"),
        ],
    ),
    DolphinLib(
        "axfx",
        [
            Object(Matching, "dolphin/axfx/reverb_hi.c"),
            Object(Matching, "dolphin/axfx/reverb_std.c"),
            Object(Matching, "dolphin/axfx/chorus.c"),
            Object(Matching, "dolphin/axfx/delay.c"),
            Object(Matching, "dolphin/axfx/axfx.c"),
        ],
    ),
    SysdolphinLib(
        "sysdolphin (HAL base library)",
        [
            Object(Matching, "sysdolphin/baselib/dobj.c"),
            Object(Matching, "sysdolphin/baselib/tobj.c"),
            Object(Matching, "sysdolphin/baselib/state.c"),
            Object(Matching, "sysdolphin/baselib/tev.c"),
            Object(Matching, "sysdolphin/baselib/mobj.c"),
            Object(Matching, "sysdolphin/baselib/aobj.c"),
            Object(Matching, "sysdolphin/baselib/lobj.c"),
            Object(Matching, "sysdolphin/baselib/cobj.c"),
            Object(Matching, "sysdolphin/baselib/fobj.c"),
            Object(Matching, "sysdolphin/baselib/pobj.c"),
            Object(Matching, "sysdolphin/baselib/jobj.c"),
            Object(Matching, "sysdolphin/baselib/displayfunc.c"),
            Object(Matching, "sysdolphin/baselib/initialize.c"),
            Object(Matching, "sysdolphin/baselib/video.c"),
            Object(Matching, "sysdolphin/baselib/controller.c"),
            Object(Matching, "sysdolphin/baselib/rumble.c"),
            Object(Matching, "sysdolphin/baselib/spline.c"),
            Object(Matching, "sysdolphin/baselib/mtx.c"),
            Object(Matching, "sysdolphin/baselib/util.c"),
            Object(Matching, "sysdolphin/baselib/objalloc.c"),
            Object(Matching, "sysdolphin/baselib/robj.c"),
            Object(Matching, "sysdolphin/baselib/id.c"),
            Object(Matching, "sysdolphin/baselib/wobj.c"),
            Object(Matching, "sysdolphin/baselib/fog.c"),
            Object(Matching, "sysdolphin/baselib/perf.c"),
            Object(Matching, "sysdolphin/baselib/list.c"),
            Object(Matching, "sysdolphin/baselib/object.c"),
            Object(Matching, "sysdolphin/baselib/quatlib.c"),
            Object(Matching, "sysdolphin/baselib/memory.c"),
            Object(Matching, "sysdolphin/baselib/shadow.c"),
            Object(Matching, "sysdolphin/baselib/archive.c"),
            Object(Matching, "sysdolphin/baselib/random.c"),
            Object(Matching, "sysdolphin/baselib/bytecode.c"),
            Object(Matching, "sysdolphin/baselib/class.c"),
            Object(Matching, "sysdolphin/baselib/hash.c"),
            Object(Matching, "sysdolphin/baselib/texp.c"),
            Object(Matching, "sysdolphin/baselib/texpdag.c"),
            Object(Matching, "sysdolphin/baselib/leak.c"),
            Object(Matching, "sysdolphin/baselib/debug.c"),
            Object(Matching, "sysdolphin/baselib/synth.c"),
            Object(Matching, "sysdolphin/baselib/axdriver.c"),
            Object(Matching, "sysdolphin/baselib/devcom.c"),
            Object(Matching, "sysdolphin/baselib/gobjproc.c"),
            Object(Matching, "sysdolphin/baselib/gobjplink.c"),
            Object(Matching, "sysdolphin/baselib/gobjgxlink.c"),
            Object(Matching, "sysdolphin/baselib/gobjobject.c"),
            Object(Matching, "sysdolphin/baselib/gobjuserdata.c"),
            Object(Matching, "sysdolphin/baselib/gobj.c"),
            Object(Matching, "sysdolphin/baselib/gobjinit.c"),
            Object(Linkable, "sysdolphin/baselib/hsd_3915.c"),
            Object(Matching, "sysdolphin/baselib/hsd_392C.c"),
            Object(Matching, "sysdolphin/baselib/hsd_3933.c"),
            Object(Matching, "sysdolphin/baselib/hsd_393C.c"),
            Object(Matching, "sysdolphin/baselib/debugconsole_main.c"),
            Object(Matching, "sysdolphin/baselib/hsd_397E.c"),
            Object(Matching, "sysdolphin/baselib/hsd_3982.c"),
            Object(
                Linkable,
                "sysdolphin/baselib/particle.c",
                extra_cflags=["-Cpp_exceptions on"],
            ),
            Object(
                Matching,
                "sysdolphin/baselib/generator.c",
                extra_cflags=["-Cpp_exceptions on"],
            ),
            Object(
                Linkable,
                "sysdolphin/baselib/psdisp.c",
                extra_cflags=["-Cpp_exceptions on"],
            ),
            Object(
                Matching,
                "sysdolphin/baselib/psdisptev.c",
                extra_cflags=["-Cpp_exceptions on"],
            ),
            Object(
                Matching,
                "sysdolphin/baselib/psappsrt.c",
                extra_cflags=["-Cpp_exceptions on"],
            ),
            Object(Matching, "sysdolphin/baselib/sobjlib.c"),
            Object(Matching, "sysdolphin/baselib/sislib.c"),
            Object(Matching, "sysdolphin/baselib/hsd_3A64.c"),
            Object(Matching, "sysdolphin/baselib/hsd_3A76.c"),
            Object(Matching, "sysdolphin/baselib/sislib_font.c"),
            Object(Matching, "sysdolphin/baselib/hsd_4D11.c"),
            Object(Matching, "sysdolphin/baselib/hsd_3A94.c"),
            Object(Matching, "sysdolphin/baselib/hsd_3B27.c"),
            Object(Matching, "sysdolphin/baselib/hsd_3B2B.c"),
            Object(Matching, "sysdolphin/baselib/hsd_3B2E.c"),
            Object(
                Matching,
                "sysdolphin/baselib/hsd_3B33.c",
                extra_cflags=["-Cpp_exceptions on"],
            ),
            Object(
                Linkable,
                "sysdolphin/baselib/hsd_3B34.c",
                extra_cflags=["-Cpp_exceptions on"],
            ),
            Object(
                Linkable,
                "sysdolphin/baselib/hsd_3B5C.c",
                extra_cflags=["-Cpp_exceptions on"],
            ),
        ],
    ),
]


# Optional callback to adjust link order. This can be used to add, remove, or reorder objects.
# This is called once per module, with the module ID and the current link order.
#
# For example, this adds "dummy.c" to the end of the DOL link order if configured with --non-matching.
# "dummy.c" *must* be configured as a Matching (or Equivalent) object in order to be linked.
def link_order_callback(module_id: int, objects: list[str]) -> list[str]:
    # Don't modify the link order for matching builds
    if not config.non_matching:
        return objects
    if module_id == 0:  # DOL
        return objects + ["dummy.c"]
    return objects


# Uncomment to enable the link order callback.
# config.link_order_callback = link_order_callback


# Extra categories for progress tracking
config.progress_categories = [
    ProgressCategory("game", "Game Code"),
    ProgressCategory("hsd", "HSD Code"),
    ProgressCategory("sdk", "Dolphin SDK Code"),
    ProgressCategory("runtime", "Gekko Runtime Code"),
]
config.print_progress_categories = args.verbose
config.progress_each_module = args.verbose

# Optional extra arguments to `objdiff-cli report generate`
config.progress_report_args = [
    # Marks relocations as mismatching if the target value is different
    f"--config functionRelocDiffs={args.reloc_diffs}",
]


def generate_compile_commands(objects: dict[str, Object], build_config: BuildConfig):

    clangd_config = []

    def add_unit(build_obj: BuildConfigUnit) -> None:
        obj = objects.get(build_obj["name"])
        if obj is None:
            return

        # Skip unresolved objects
        if (
            obj.src_path is None
            or obj.src_obj_path is None
            or not file_is_c_cpp(obj.src_path)
        ):
            return

        unit_config = {
            "directory": Path.cwd(),
            "file": obj.src_path,
            "output": obj.src_obj_path,
            "arguments": [
                "clang",
                *[*config.extra_clang_flags, *obj.options["extra_clang_flags"]],
                "-c",
                obj.src_path,
                "-o",
                obj.src_obj_path,
            ],
        }
        clangd_config.append(unit_config)

    if build_config is not None:
        # Add DOL units
        for unit in build_config["units"]:
            add_unit(unit)

        # Add REL units
        for module in build_config["modules"]:
            for unit in module["units"]:
                add_unit(unit)

    # Write compile_commands.json
    with Path("compile_commands.json").open("w", encoding="utf-8") as w:

        def default_format(o):
            if isinstance(o, Path):
                return o.resolve().as_posix()
            return str(o)

        json.dump(clangd_config, w, indent=2, default=default_format)


if args.mode == "configure":
    if args.always_apply:
        config.custom_build_steps = {
            "post-ok": [
                {
                    "outputs": "always_apply",
                    "rule": "phony",
                    "implicit": ["apply"],
                }
            ]
        }

    # Write build.ninja and objdiff.json
    generate_build(config)

    config.validate()
    objects = config.objects()
    build_config = load_build_config(config, config.out_path() / "config.json")

    if not build_config:
        exit(0)

    if not args.allow_auto_splits:
        for unit in build_config["units"]:
            if unit["autogenerated"]:
                print(
                    f"\033[31mERROR\033[0m Found an auto-generated split ({unit['name']}).",
                    "\033[31mERROR\033[0m Make sure the DOL is fully covered in splits.txt.",
                    sep=os.linesep,
                )
                exit(1)

    if args.compile_commands:
        generate_compile_commands(objects, build_config)
elif args.mode == "progress":
    # Print progress information
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
