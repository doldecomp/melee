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

from tools.project import (
    LibDict,
    Object,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

# Game versions
DEFAULT_VERSION = 0
VERSIONS = ["GALE01"]

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
parser.add_argument(
    "--msg-style",
    choices=["mpw", "std", "gcc", "ide", "parseable"],
    default="gcc",
    help="message style of the compiler (default 'gcc')",
)
parser.add_argument(
    "--max-errors",
    type=int,
    default=1,
    help="the maximum number of errors allowed by the compiler (default 1)",
)
parser.add_argument(
    "--warn-all",
    action="store_true",
    help="emit all compiler warnings",
)
parser.add_argument(
    "--no-warn-error",
    action="store_false",
    dest="warn_error",
    help="compiler warnings are not considered errors",
)
parser.add_argument(
    "--must-match",
    action="store_true",
    help="define MUST_MATCH for make compatibility",
)
parser.add_argument(
    "--no-require-protos",
    dest="require_protos",
    action="store_false",
    help="do not require function prototypes",
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
    f"-DVERSION={version_num}",
    "-DWIP",
]

if config.debug:
    cflags_base.extend(["-sym on", "-DDEBUG=1"])
else:
    cflags_base.append("-DNDEBUG=1")

if args.max_errors is not None:
    cflags_base.append(f"-maxerrors {args.max_errors}")
    if args.max_errors == 0:
        cflags_base.append("-nofail")

if args.msg_style is not None:
    cflags_base.append(f"-msgstyle {args.msg_style}")

if args.warn_all:
    cflags_base.append("-warn all")

if args.warn_error:
    cflags_base.append("-warn iserror")

if args.must_match:
    cflags_base.append("-DMUST_MATCH")

if args.require_protos:
    cflags_base.append("-requireprotos")

# Metrowerks library flags
cflags_runtime = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
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
    cflags=cflags_base,
    fix_epilogue=True,
    includes: List[str] = includes_base,
    system_includes: List[str] = system_includes_base,
) -> LibDict:
    def make_includes(includes: List[str]) -> Iterator[str]:
        return map(lambda s: f"-i {s}", includes)

    return {
        "lib": lib_name,
        "mw_version": f"GC/1.2.5{'n' if fix_epilogue else ''}",
        "cflags": [
            *cflags,
            *make_includes(includes),
            "-I-",
            *make_includes(system_includes),
        ],
        "host": False,
        "objects": objects,
    }


def DolphinLib(lib_name: str, objects: Objects, fix_epilogue=False) -> LibDict:
    return Lib(
        lib_name,
        objects,
        fix_epilogue=fix_epilogue,
        includes=[
            *includes_base,
            "src/melee",  # HACK
        ],
        system_includes=[
            *system_includes_base,
            "src/sysdolphin",  # HACK
        ],
    )


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


def RuntimeLib(lib_name: str, objects: Objects) -> LibDict:
    return Lib(
        lib_name,
        objects,
        cflags=cflags_runtime,
        includes=[
            *includes_base,
            "src/melee",  # HACK
        ],
        system_includes=[
            *system_includes_base,
            "src/sysdolphin",  # HACK
        ],
    )


Matching = True
NonMatching = False

config.warn_missing_config = args.verbose
config.warn_missing_source = args.verbose
config.libs = [
    MeleeLib(
        "lb (Library)",
        [
            Object(Matching, "melee/lb/lbcommand.c"),
            Object(NonMatching, "melee/lb/lbcollision.c"),
            Object(Matching, "melee/lb/lblanguage.c"),
            Object(Matching, "melee/lb/lbtime.c"),
            Object(Matching, "melee/lb/lb_00B0.c"),
            Object(NonMatching, "melee/lb/lb_00CE.c"),
            Object(NonMatching, "melee/lb/lbvector.c"),
            Object(NonMatching, "melee/lb/lbshadow.c"),
            Object(NonMatching, "melee/lb/lb_00F9.c"),
            Object(NonMatching, "melee/lb/lbarq.c"),
            Object(NonMatching, "melee/lb/lbmemory.c"),
            Object(NonMatching, "melee/lb/lbheap.c"),
            Object(NonMatching, "melee/lb/lbfile.c"),
            Object(NonMatching, "melee/lb/lbarchive.c"),
            Object(NonMatching, "melee/lb/lbdvd.c"),
            Object(NonMatching, "melee/lb/lb_0192.c"),
            Object(NonMatching, "melee/lb/lb_0198.c"),
            Object(NonMatching, "melee/lb/lbsnap.c"),
            Object(NonMatching, "melee/lb/lbgx.c"),
            Object(NonMatching, "melee/lb/lbanim.c"),
            Object(NonMatching, "melee/lb/lbmthp.c"),
            Object(NonMatching, "melee/lb/lbbgflash.c"),
            #
            Object(NonMatching, "melee/lb/lbrefract_data.c"),
            Object(NonMatching, "melee/lb/lbrefract1.c"),
            Object(NonMatching, "melee/lb/lbrefract2.c"),
            #
            Object(NonMatching, "melee/lb/lbaudio_ax.c"),
        ],
    ),
    MeleeLib(
        "cm (Camera)",
        [
            Object(NonMatching, "melee/cm/camera.c"),
            Object(Matching, "melee/cm/cmsnap.c"),
        ],
    ),
    MeleeLib(
        "pl (Player)",
        [
            Object(NonMatching, "melee/pl/player.c"),
            Object(NonMatching, "melee/pl/plstale.c"),
            Object(NonMatching, "melee/pl/pltrick.c"),
            Object(NonMatching, "melee/pl/plbonus.c"),
            Object(NonMatching, "melee/pl/plbonuslib.c"),
            Object(NonMatching, "melee/pl/pl_040D.c"),
        ],
    ),
    MeleeLib(
        "mp (Map)",
        [
            Object(NonMatching, "melee/mp/mpcoll.c"),
            Object(NonMatching, "melee/mp/mplib.c"),
            Object(NonMatching, "melee/mp/mpisland.c"),
        ],
    ),
    MeleeLib(
        "ef (Visual effects)",
        [
            Object(NonMatching, "melee/ef/eflib.c"),
            Object(NonMatching, "melee/ef/efsync.c"),
            Object(NonMatching, "melee/ef/ef_061D.c"),
            Object(NonMatching, "melee/ef/efasync.c"),
        ],
    ),
    MeleeLib(
        "ft (Fighters)",
        [
            # Main
            Object(NonMatching, "melee/ft/fighter.c"),
            Object(NonMatching, "melee/ft/ftanim.c"),
            Object(NonMatching, "melee/ft/ftaction.c"),
            Object(NonMatching, "melee/ft/ftparts.c"),
            Object(Matching, "melee/ft/ftcamera.c"),
            Object(NonMatching, "melee/ft/ftcoll.c"),
            Object(Matching, "melee/ft/ft_07C1.c"),
            Object(Matching, "melee/ft/ft_07C6.c"),
            Object(NonMatching, "melee/ft/ftcommon.c"),
            Object(NonMatching, "melee/ft/ftdrawcommon.c"),
            Object(NonMatching, "melee/ft/ftcliffcommon.c"),
            Object(NonMatching, "melee/ft/ftwalljump.c"),
            Object(Matching, "melee/ft/ft_0819.c"),
            Object(Matching, "melee/ft/ft_081B.c"),
            Object(NonMatching, "melee/ft/ft_0852.c"),
            Object(NonMatching, "melee/ft/ftdata.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_Init.c"),
            Object(NonMatching, "melee/ft/ftlib.c"),
            Object(Matching, "melee/ft/ftwaitanim.c"),
            Object(NonMatching, "melee/ft/ft_0877.c"),
            Object(NonMatching, "melee/ft/ft_0881.c"),
            Object(NonMatching, "melee/ft/ft_0892.c"),
            # Common
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_Wait.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_08A6.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_Attack1.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_AttackDash.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_AttackS3.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_AttackHi3.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_AttackLw3.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_AttackS4.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_AttackHi4.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_AttackLw4.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_AttackAir.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_LandingAir.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_Damage.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_DamageFall.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_DamageIce.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_Guard.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_ItemGet.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_ItemThrow.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_SpecialS.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_SpecialAir.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_FallSpecial.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_Lift.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_DownBound.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_DownStand.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_Down.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_DownAttack.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_Passive.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_PassiveStand.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_ShieldBreakFly.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_ShieldBreakFall.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_ShieldBreakDown.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_ShieldBreakStand.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_Furafura.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_Escape.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_EscapeAir.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_Rebound.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_Pass.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_Ottotto.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_CliffWait.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_CliffClimb.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_CliffAttack.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_CliffEscape.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_CliffJump.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_CargoWait.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_CargoWalk.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_CargoTurn.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_CargoKneebend.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_CargoJump.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_CargoFall.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_CargoLanding.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_CargoThrow.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_09C4.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_Shouldered.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_CaptureCaptain.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_09CB.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_BarrelWait.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_StopWall.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_StopCeil.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_DownDamage.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_MissFoot.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_09F4.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_09F7.c"),
            Object(Matching, "melee/ft/chara/ftMario/ftMr_Strings.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_0A01.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_0B3E.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_CaptureYoshi.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_YoshiEgg.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_CaptureKoopa.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_CaptureDamageKoopa.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_CaptureWaitKoopa.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_ThrownKoopa.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_CaptureMewtwo.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_ThrownMewtwo.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_CaptureKirby.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_CaptureWaitKirby.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_ThrownKirby.c"),
            Object(NonMatching, "melee/ft/ft_3C61.c"),
            # Main again
            Object(NonMatching, "melee/ft/ftdemo.c"),
            Object(NonMatching, "melee/ft/ft_0BEC.c"),
            Object(Matching, "melee/ft/ft_0BEF.c"),
            Object(NonMatching, "melee/ft/ft_0BF0.c"),
            Object(NonMatching, "melee/ft/ftmaterial.c"),
            Object(NonMatching, "melee/ft/ftcolanim.c"),
            Object(NonMatching, "melee/ft/ftdevice.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_Bury.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_FlyReflect.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_PassiveWall.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_PassiveCeil.c"),
            Object(NonMatching, "melee/ft/ftafterimage.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_DamageSong.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_0C35.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_AirCatch.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_DamageBind.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_WarpStar.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_HammerWait.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_HammerWalk.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_HammerTurn.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_HammerJump.c"),
            Object(NonMatching, "melee/ft/chara/ftCommon/ftCo_HammerKneeBend.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_HammerFall.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_HammerLanding.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_0C60.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_DemoCallback0.c"),
            Object(NonMatching, "melee/ft/ft_0C31.c"),
            Object(NonMatching, "melee/ft/ftmetal.c"),
            Object(NonMatching, "melee/ft/ft_0C88.c"),
            Object(NonMatching, "melee/ft/ftswing.c"),
            Object(NonMatching, "melee/ft/ft_0CD1.c"),
            Object(NonMatching, "melee/ft/ftstarrodswing.c"),
            Object(NonMatching, "melee/ft/ftlipstickswing.c"),
            Object(NonMatching, "melee/ft/ft_0CDD.c"),
            Object(NonMatching, "melee/ft/ftattacks4combo.c"),
            Object(NonMatching, "melee/ft/ft_0CEE.c"),
            Object(NonMatching, "melee/ft/ftchangeparam.c"),
            Object(NonMatching, "melee/ft/ft_0D14.c"),
            # Donkey Kong (common states)
            Object(Matching, "melee/ft/chara/ftDonkey/ftDk_HeavyWait0.c"),
            Object(Matching, "melee/ft/chara/ftDonkey/ftDk_HeavyWalk.c"),
            Object(NonMatching, "melee/ft/ftwalkcommon.c"),
            Object(Matching, "melee/ft/chara/ftDonkey/ftDk_MS_345_0.c"),
            Object(Matching, "melee/ft/chara/ftDonkey/ftDk_HeavyTurn.c"),
            Object(Matching, "melee/ft/chara/ftDonkey/ftDk_HeavyFall.c"),
            Object(Matching, "melee/ft/chara/ftDonkey/ftDk_HeavyJump.c"),
            Object(Matching, "melee/ft/chara/ftDonkey/ftDk_HeavyWait1.c"),
            Object(Matching, "melee/ft/chara/ftDonkey/ftDk_HeavyLanding.c"),
            # Mario
            Object(Matching, "melee/ft/chara/ftMario/ftMr_Init.c"),
            Object(NonMatching, "melee/ft/chara/ftMario/ftMr_SpecialN.c"),
            Object(NonMatching, "melee/ft/chara/ftMario/ftMr_SpecialS.c"),
            Object(NonMatching, "melee/ft/chara/ftMario/ftMr_SpecialHi.c"),
            Object(NonMatching, "melee/ft/chara/ftMario/ftMr_SpecialLw.c"),
            # Captain Falcon
            Object(NonMatching, "melee/ft/chara/ftCaptain/ftCa_Init.c"),
            Object(NonMatching, "melee/ft/chara/ftCaptain/ftCa_SpecialN.c"),
            Object(NonMatching, "melee/ft/chara/ftCaptain/ftCa_SpecialS.c"),
            Object(NonMatching, "melee/ft/chara/ftCaptain/ftCa_SpecialLw.c"),
            Object(NonMatching, "melee/ft/chara/ftCaptain/ftCa_SpecialHi.c"),
            # Fox
            Object(Matching, "melee/ft/chara/ftFox/ftFx_Init.c"),
            Object(NonMatching, "melee/ft/chara/ftFox/ftFx_AppealS.c"),
            Object(NonMatching, "melee/ft/chara/ftFox/ftFx_SpecialN.c"),
            Object(NonMatching, "melee/ft/chara/ftFox/ftFx_SpecialHi.c"),
            Object(NonMatching, "melee/ft/chara/ftFox/ftFx_SpecialLw.c"),
            Object(NonMatching, "melee/ft/chara/ftFox/ftFx_SpecialS.c"),
            # Link
            Object(NonMatching, "melee/ft/chara/ftLink/ftLk_Init.c"),
            Object(NonMatching, "melee/ft/chara/ftLink/ftLk_AttackAir.c"),
            Object(NonMatching, "melee/ft/chara/ftLink/ftLk_SpecialLw.c"),
            Object(NonMatching, "melee/ft/chara/ftLink/ftLk_SpecialHi.c"),
            Object(NonMatching, "melee/ft/chara/ftLink/ftLk_SpecialS.c"),
            Object(NonMatching, "melee/ft/chara/ftLink/ftLk_SpecialN.c"),
            # Kirby
            Object(NonMatching, "melee/ft/chara/ftKirby/ftKb_Init.c"),
            # Donkey Kong
            Object(NonMatching, "melee/ft/chara/ftDonkey/ftDk_Init.c"),
            Object(NonMatching, "melee/ft/chara/ftDonkey/ftDk_SpecialLw.c"),
            Object(NonMatching, "melee/ft/chara/ftDonkey/ftDk_SpecialS.c"),
            Object(NonMatching, "melee/ft/chara/ftDonkey/ftDk_SpecialN.c"),
            Object(NonMatching, "melee/ft/chara/ftDonkey/ftDk_SpecialHi.c"),
            # Sheik
            Object(Matching, "melee/ft/chara/ftSeak/ftSk_Init.c"),
            Object(NonMatching, "melee/ft/chara/ftSeak/ftSk_SpecialS.c"),
            Object(NonMatching, "melee/ft/chara/ftSeak/ftSk_SpecialN.c"),
            Object(NonMatching, "melee/ft/chara/ftSeak/ftSk_SpecialHi.c"),
            Object(NonMatching, "melee/ft/chara/ftSeak/ftSk_SpecialLw.c"),
            # Ness
            Object(Matching, "melee/ft/chara/ftNess/ftNs_Init.c"),
            Object(NonMatching, "melee/ft/chara/ftNess/ftNs_AttackS4.c"),
            Object(NonMatching, "melee/ft/chara/ftNess/ftNs_AttackHi4.c"),
            Object(Matching, "melee/ft/chara/ftNess/ftNs_AttackLw4.c"),
            Object(NonMatching, "melee/ft/chara/ftNess/ftNs_SpecialS.c"),
            Object(NonMatching, "melee/ft/chara/ftNess/ftNs_SpecialN.c"),
            Object(NonMatching, "melee/ft/chara/ftNess/ftNs_SpecialHi.c"),
            Object(NonMatching, "melee/ft/chara/ftNess/ftNs_SpecialLw.c"),
            # Peach
            Object(NonMatching, "melee/ft/chara/ftPeach/ftPe_Init.c"),
            Object(NonMatching, "melee/ft/chara/ftPeach/ftPe_Float.c"),
            Object(Matching, "melee/ft/chara/ftPeach/ftPe_FloatFall.c"),
            Object(NonMatching, "melee/ft/chara/ftPeach/ftPe_FloatAttack.c"),
            Object(Matching, "melee/ft/chara/ftPeach/ftPe_AttackS4.c"),
            Object(NonMatching, "melee/ft/chara/ftPeach/ftPe_SpecialS.c"),
            Object(NonMatching, "melee/ft/chara/ftPeach/ftPe_SpecialLw.c"),
            Object(NonMatching, "melee/ft/chara/ftPeach/ftPe_SpecialHi.c"),
            Object(NonMatching, "melee/ft/chara/ftPeach/ftPe_SpecialN.c"),
            # Popo
            Object(Matching, "melee/ft/chara/ftPopo/ftPp_Init.c"),
            Object(NonMatching, "melee/ft/chara/ftPopo/ftPp_SpecialN.c"),
            Object(NonMatching, "melee/ft/chara/ftPopo/ftPp_SpecialS.c"),
            Object(NonMatching, "melee/ft/chara/ftPp_SpecialS.c"),
            # Nana
            Object(NonMatching, "melee/ft/chara/ftNana/ftNn_Init.c"),
            Object(Matching, "melee/ft/chara/ftNana/ftNn_Unk0.c"),
            # Pikachu
            Object(NonMatching, "melee/ft/chara/ftPikachu/ftPk_Init.c"),
            Object(NonMatching, "melee/ft/chara/ftPikachu/ftPk_SpecialN.c"),
            Object(NonMatching, "melee/ft/chara/ftPikachu/ftPk_SpecialS.c"),
            Object(NonMatching, "melee/ft/chara/ftPikachu/ftPk_SpecialHi.c"),
            Object(NonMatching, "melee/ft/chara/ftPikachu/ftPk_SpecialLw.c"),
            # Samus
            Object(Matching, "melee/ft/chara/ftSamus/ftSs_Init.c"),
            Object(NonMatching, "melee/ft/chara/ftSamus/ftSs_SpecialLw_0.c"),
            Object(NonMatching, "melee/ft/chara/ftSamus/ftSs_SpecialN.c"),
            Object(NonMatching, "melee/ft/chara/ftSamus/ftSs_SpecialS.c"),
            Object(NonMatching, "melee/ft/chara/ftSamus/ftSs_SpecialHi.c"),
            Object(NonMatching, "melee/ft/chara/ftSamus/ftSs_SpecialLw_1.c"),
            # Yoshi
            Object(NonMatching, "melee/ft/chara/ftYoshi/ftYs_Init.c"),
            Object(NonMatching, "melee/ft/chara/ftYoshi/ftYs_Guard.c"),
            Object(NonMatching, "melee/ft/chara/ftYoshi/ftYs_SpecialN.c"),
            # Bowser
            Object(NonMatching, "melee/ft/chara/ftKoopa/ftKp_Init.c"),
            Object(Matching, "melee/ft/chara/ftKoopa/ftKp_Unk1.c"),
            Object(NonMatching, "melee/ft/chara/ftKp_SpecialS.c"),
            # Marth
            Object(Matching, "melee/ft/chara/ftMars/ftMs_Init.c"),
            Object(NonMatching, "melee/ft/chara/ftMars/ftMs_SpecialN.c"),
            Object(NonMatching, "melee/ft/chara/ftMars/ftMs_SpecialS.c"),
            Object(NonMatching, "melee/ft/chara/ftMars/ftMs_SpecialHi.c"),
            Object(NonMatching, "melee/ft/chara/ftMars/ftMs_SpecialLw.c"),
            # Zelda
            Object(NonMatching, "melee/ft/chara/ftZelda/ftZd_Init.c"),
            Object(NonMatching, "melee/ft/chara/ftZelda/ftZd_SpecialHi.c"),
            Object(NonMatching, "melee/ft/chara/ftZelda/ftZd_SpecialN.c"),
            Object(NonMatching, "melee/ft/chara/ftZelda/ftZd_SpecialLw.c"),
            Object(NonMatching, "melee/ft/chara/ftZelda/ftZd_SpecialS.c"),
            # Jigglypuff
            Object(NonMatching, "melee/ft/chara/ftPurin/ftPr_Init.c"),
            # Luigi
            Object(Matching, "melee/ft/chara/ftLuigi/ftLg_Init.c"),
            Object(Matching, "melee/ft/chara/ftLuigi/ftLg_SpecialN.c"),
            Object(NonMatching, "melee/ft/chara/ftLuigi/ftLg_SpecialS.c"),
            Object(NonMatching, "melee/ft/chara/ftLuigi/ftLg_SpecialHi.c"),
            Object(NonMatching, "melee/ft/chara/ftLuigi/ftLg_SpecialLw.c"),
            # Mewtwo
            Object(Matching, "melee/ft/chara/ftMewtwo/ftMt_Init.c"),
            Object(NonMatching, "melee/ft/chara/ftMewtwo/ftMt_SpecialHi.c"),
            Object(NonMatching, "melee/ft/chara/ftMewtwo/ftMt_SpecialLw.c"),
            Object(NonMatching, "melee/ft/chara/ftMewtwo/ftMt_SpecialS.c"),
            Object(NonMatching, "melee/ft/chara/ftMewtwo/ftMt_SpecialN.c"),
            # Young Link
            Object(NonMatching, "melee/ft/chara/ftCLink/ftCl_Init.c"),
            Object(NonMatching, "melee/ft/chara/ftCLink/ftCl_AppealS.c"),
            # Dr. Mario
            Object(NonMatching, "melee/ft/chara/ftDrMario/ftDr_Init.c"),
            Object(NonMatching, "melee/ft/chara/ftDrMario/ftDr_AppealS.c"),
            # Falco
            Object(NonMatching, "melee/ft/chara/ftFalco/ftFc_Init.c"),
            # Pichu
            Object(Matching, "melee/ft/chara/ftPichu/ftPc_Init.c"),
            # Mr. Game & Watch
            Object(Matching, "melee/ft/chara/ftGameWatch/ftGw_Init.c"),
            Object(NonMatching, "melee/ft/chara/ftGameWatch/ftGw_AttackS4.c"),
            Object(NonMatching, "melee/ft/chara/ftGameWatch/ftGw_AttackLw3.c"),
            Object(NonMatching, "melee/ft/chara/ftGameWatch/ftGw_AttackAir.c"),
            Object(NonMatching, "melee/ft/chara/ftGameWatch/ftGw_Attack11.c"),
            Object(Matching, "melee/ft/chara/ftGameWatch/ftGw_Attack100.c"),
            Object(NonMatching, "melee/ft/chara/ftGameWatch/ftGw_SpecialS.c"),
            Object(NonMatching, "melee/ft/chara/ftGameWatch/ftGw_SpecialLw.c"),
            Object(NonMatching, "melee/ft/chara/ftGameWatch/ftGw_SpecialHi.c"),
            Object(NonMatching, "melee/ft/chara/ftGameWatch/ftGw_SpecialN.c"),
            # Ganondorf
            Object(Matching, "melee/ft/chara/ftGanon/ftGn_Init.c"),
            # Roy
            Object(Matching, "melee/ft/chara/ftEmblem/ftFe_Init.c"),
            # Wireframe (boy)
            Object(Matching, "melee/ft/chara/ftZakoBoy/ftBo_Init.c"),
            # Wireframe (girl)
            Object(Matching, "melee/ft/chara/ftZakoGirl/ftGl_Init.c"),
            # Giga Koopa
            Object(NonMatching, "melee/ft/chara/ftGigaKoopa/ftGk_Init.c"),
            # Sandbag
            Object(Matching, "melee/ft/chara/ftSandbag/ftSb_Init.c"),
            # Master Hand
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_Init.c"),
            Object(NonMatching, "melee/ft/chara/ftMasterHand/ftMh_Wait1_0.c"),
            Object(NonMatching, "melee/ft/chara/ftMasterHand/ftMh_Wait1_2.c"),
            Object(NonMatching, "melee/ft/chara/ftMasterHand/ftMh_Entry.c"),
            Object(NonMatching, "melee/ft/chara/ftMasterHand/ftMh_Damage_0.c"),
            Object(NonMatching, "melee/ft/chara/ftMasterHand/ftMh_Sweep.c"),
            Object(NonMatching, "melee/ft/chara/ftMasterHand/ftMh_SweepWait.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_Slap.c"),
            Object(NonMatching, "melee/ft/chara/ftMasterHand/ftMh_Walk.c"),
            Object(NonMatching, "melee/ft/chara/ftMasterHand/ftMh_Drill.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_RockCrush.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_PaperCrush.c"),
            Object(NonMatching, "melee/ft/chara/ftMasterHand/ftMh_Poke.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_FingerBeam.c"),
            Object(NonMatching, "melee/ft/chara/ftMasterHand/ftMh_FingerGun.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_FingerGun3.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_BackAirplane1.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_BackAirplane2.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_BackAirplane3.c"),
            Object(NonMatching, "melee/ft/chara/ftMasterHand/ftMh_BackCrush_0.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_BackCrush_1.c"),
            Object(NonMatching, "melee/ft/chara/ftMasterHand/ftMh_BackDisappear.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_Squeeze.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_Wait1_1.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_Squeezing.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_Throw.c"),
            Object(NonMatching, "melee/ft/chara/ftMasterHand/ftMh_Slam.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_TagCrush.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_TagApplaud.c"),
            Object(NonMatching, "melee/ft/chara/ftMasterHand/ftMh_TagRockPaper.c"),
            Object(NonMatching, "melee/ft/chara/ftMasterHand/ftMh_TagCancel.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_CaptureMasterHand.c"),
            Object(
                Matching, "melee/ft/chara/ftMasterHand/ftMh_CaptureDamageMasterHand.c"
            ),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_ThrownMasterHand.c"),
            # Crazy Hand
            Object(NonMatching, "melee/ft/chara/ftCrazyHand/ftCh_Init.c"),
            Object(NonMatching, "melee/ft/chara/ftCrazyHand/ftCh_Unk0.c"),
            # Main
            Object(NonMatching, "melee/ft/ftbosslib.c"),
        ],
    ),
    MeleeLib(
        "gm (Main game loop)",
        [
            Object(NonMatching, "melee/gm/gmmain_lib.c"),
            Object(NonMatching, "melee/gm/gmmain.c"),
            Object(NonMatching, "melee/gm/gm_1601.c"),
            Object(NonMatching, "melee/gm/gmtitle.c"),
            Object(NonMatching, "melee/gm/gmcamera.c"),
            Object(NonMatching, "melee/gm_1A36.c"),
        ],
    ),
    MeleeLib(
        "gr (Ground, stages)",
        [
            # Main
            Object(NonMatching, "melee/gr/ground.c"),
            Object(NonMatching, "melee/gr/grdisplay.c"),
            Object(NonMatching, "melee/gr/grdatfiles.c"),
            Object(NonMatching, "melee/gr/granime.c"),
            Object(NonMatching, "melee/gr/grmaterial.c"),
            Object(NonMatching, "melee/gr/grlib.c"),
            Object(NonMatching, "melee/gr/grdynamicattr.c"),
            Object(NonMatching, "melee/gr/grzakogenerator.c"),
            # Individual stages
            Object(NonMatching, "melee/gr/grfzerocar.c"),
            Object(NonMatching, "melee/gr/grizumi.c"),
            Object(NonMatching, "melee/gr/grcastle.c"),
            Object(NonMatching, "melee/gr/grstadium.c"),
            Object(NonMatching, "melee/gr/grkongo.c"),
            Object(NonMatching, "melee/gr/grzebes.c"),
            Object(NonMatching, "melee/gr/grcorneria.c"),
            Object(NonMatching, "melee/gr/grstory.c"),
            Object(NonMatching, "melee/gr/gronett.c"),
            Object(NonMatching, "melee/gr/grbigblue.c"),
            Object(NonMatching, "melee/gr/grmutecity.c"),
            Object(NonMatching, "melee/gr/grfourside.c"),
            Object(NonMatching, "melee/gr/grgreatbay.c"),
            Object(NonMatching, "melee/gr/gricemt.c"),
            Object(NonMatching, "melee/gr/grinishie1.c"),
            Object(NonMatching, "melee/gr/grinishie2.c"),
            Object(NonMatching, "melee/gr/grkraid.c"),
            Object(NonMatching, "melee/gr/grrcruise.c"),
            Object(NonMatching, "melee/gr/grshrine.c"),
            Object(NonMatching, "melee/gr/gryorster.c"),
            Object(NonMatching, "melee/gr/grgarden.c"),
            Object(NonMatching, "melee/gr/grvenom.c"),
            Object(NonMatching, "melee/gr/grtest.c"),
            Object(NonMatching, "melee/gr/grkinokoroute.c"),
            Object(NonMatching, "melee/gr/grshrineroute.c"),
            Object(NonMatching, "melee/gr/grzebesroute.c"),
            Object(NonMatching, "melee/gr/grbigblueroute.c"),
            Object(NonMatching, "melee/gr/grfigure1.c"),
            Object(NonMatching, "melee/gr/grfigure2.c"),
            Object(NonMatching, "melee/gr/grfigure3.c"),
            Object(NonMatching, "melee/gr/groldyoshi.c"),
            Object(NonMatching, "melee/gr/groldkongo.c"),
            Object(NonMatching, "melee/gr/groldpupupu.c"),
            Object(NonMatching, "melee/gr/grpura.c"),
            Object(NonMatching, "melee/gr/grgreens.c"),
            Object(NonMatching, "melee/gr/grflatzone.c"),
            Object(NonMatching, "melee/gr/grpushon.c"),
            Object(NonMatching, "melee/gr/grfigureget.c"),
            Object(NonMatching, "melee/gr/grbattle.c"),
            Object(NonMatching, "melee/gr/grlast.c"),
            Object(NonMatching, "melee/gr/grhomerun.c"),
            Object(NonMatching, "melee/gr/grheal.c"),
            # Break the Targets stages
            Object(Matching, "melee/gr/grtmario.c"),
            Object(NonMatching, "melee/gr/grtcaptain.c"),
            Object(NonMatching, "melee/gr/grtclink.c"),
            Object(NonMatching, "melee/gr/grtdonkey.c"),
            Object(Matching, "melee/gr/grtdrmario.c"),
            Object(Matching, "melee/gr/grtfalco.c"),
            Object(Matching, "melee/gr/grtfox.c"),
            Object(Matching, "melee/gr/grticeclimber.c"),
            Object(Matching, "melee/gr/grtkirby.c"),
            Object(NonMatching, "melee/gr/grtkoopa.c"),
            Object(Matching, "melee/gr/grtlink.c"),
            Object(Matching, "melee/gr/grtluigi.c"),
            Object(NonMatching, "melee/gr/grtmars.c"),
            Object(Matching, "melee/gr/grtmewtwo.c"),
            Object(NonMatching, "melee/gr/grtness.c"),
            Object(Matching, "melee/gr/grtpeach.c"),
            Object(NonMatching, "melee/gr/grtpichu.c"),
            Object(NonMatching, "melee/gr/grtpikachu.c"),
            Object(NonMatching, "melee/gr/grtpurin.c"),
            Object(Matching, "melee/gr/grtsamus.c"),
            Object(Matching, "melee/gr/grtseak.c"),
            Object(NonMatching, "melee/gr/grtyoshi.c"),
            Object(Matching, "melee/gr/grtzelda.c"),
            Object(NonMatching, "melee/gr/grtgamewatch.c"),
            Object(NonMatching, "melee/gr/grtemblem.c"),
            Object(NonMatching, "melee/gr/grtganon.c"),
            # Main
            Object(Matching, "melee/gr/stage.c"),
        ],
    ),
    MeleeLib(
        "db (Debug)",
        [
            Object(NonMatching, "melee/db/db_2253.c"),
        ],
    ),
    MeleeLib(
        "mn (Menus)",
        [
            Object(NonMatching, "melee/mn_2295.c"),
            Object(NonMatching, "melee/mn/mnitemsw.c"),
            Object(NonMatching, "melee/mn/mnstagesw.c"),
            Object(NonMatching, "melee/mn/mnname.c"),
            Object(NonMatching, "melee/mn/mnnamenew.c"),
            Object(NonMatching, "melee/mn/mndiagram.c"),
            Object(NonMatching, "melee/mn/mndiagram2.c"),
            Object(NonMatching, "melee/mn/mndiagram3.c"),
            Object(NonMatching, "melee/mn/mnvibration.c"),
            Object(NonMatching, "melee/mn/mnsound.c"),
            Object(NonMatching, "melee/mn/mndeflicker.c"),
            Object(NonMatching, "melee/mn/mnsoundtest.c"),
            Object(NonMatching, "melee/mn/mnlanguage.c"),
            Object(NonMatching, "melee/mn/mnhyaku.c"),
            Object(NonMatching, "melee/mn/mnevent.c"),
            Object(NonMatching, "melee/mn/mndatadel.c"),
            Object(NonMatching, "melee/mn/mncount.c"),
            Object(NonMatching, "melee/mn/mninfo.c"),
            Object(NonMatching, "melee/mn/mninfobonus.c"),
            Object(NonMatching, "melee/mn/mnsnap.c"),
            Object(NonMatching, "melee/mn/mngallery.c"),
            Object(NonMatching, "melee/mn/mnstagesel.c"),
            Object(NonMatching, "melee/mn/mncharsel.c"),
        ],
    ),
    MeleeLib(
        "it (Items)",
        [
            # Main
            Object(NonMatching, "melee/it/item.c"),
            Object(NonMatching, "melee/it/it_26B1.c"),
            Object(NonMatching, "melee/it/it_266F.c"),
            Object(NonMatching, "melee/it/itcoll.c"),
            Object(NonMatching, "melee/it/it_3F14.c"),
            Object(NonMatching, "melee/it/it_3F23.c"),
            Object(NonMatching, "melee/it/it_3F31.c"),
            Object(NonMatching, "melee/it/it_2725.c"),
            # Individual items
            Object(NonMatching, "melee/it/items/itcapsule.c"),
            Object(NonMatching, "melee/it/items/itbombhei.c"),
            Object(NonMatching, "melee/it/items/itdosei.c"),
            Object(NonMatching, "melee/it/items/itheart.c"),
            Object(NonMatching, "melee/it/items/ittomato.c"),
            Object(Matching, "melee/it/items/itstar.c"),
            Object(NonMatching, "melee/it/items/itbat.c"),
            Object(NonMatching, "melee/it/items/itsword.c"),
            Object(NonMatching, "melee/it/items/itbox.c"),
            Object(NonMatching, "melee/it/items/ittaru.c"),
            Object(NonMatching, "melee/it/items/itegg.c"),
            Object(NonMatching, "melee/it/items/itkusudama.c"),
            Object(NonMatching, "melee/it/items/itparasol.c"),
            Object(NonMatching, "melee/it/items/itgshell.c"),
            Object(NonMatching, "melee/it/items/itrshell.c"),
            Object(NonMatching, "melee/it/items/itlgun.c"),
            Object(NonMatching, "melee/it/items/itfreeze.c"),
            Object(NonMatching, "melee/it/items/itfoods.c"),
            Object(NonMatching, "melee/it/items/itmsbomb.c"),
            Object(NonMatching, "melee/it/items/itflipper.c"),
            Object(NonMatching, "melee/it/items/itsscope.c"),
            Object(NonMatching, "melee/it/items/itstarrod.c"),
            Object(NonMatching, "melee/it/items/itharisen.c"),
            Object(NonMatching, "melee/it/items/itfflower.c"),
            Object(NonMatching, "melee/it/items/itkinoko.c"),
            Object(NonMatching, "melee/it/items/itdkinoko.c"),
            Object(Matching, "melee/it/items/ithammer.c"),
            Object(NonMatching, "melee/it/items/itwstar.c"),
            Object(NonMatching, "melee/it/items/itscball.c"),
            Object(NonMatching, "melee/it/items/itrabbitc.c"),
            Object(NonMatching, "melee/it/items/itmetalb.c"),
            Object(NonMatching, "melee/it/items/itlipstick.c"),
            Object(NonMatching, "melee/it/items/itspycloak.c"),
            Object(NonMatching, "melee/it/items/ittarucann.c"),
            Object(NonMatching, "melee/it/items/itmball.c"),
            Object(NonMatching, "melee/it/items/itlgunray.c"),
            Object(NonMatching, "melee/it/items/itstarrodstar.c"),
            Object(NonMatching, "melee/it/items/itsscopebeam.c"),
            Object(NonMatching, "melee/it/items/itlgunbeam.c"),
            Object(NonMatching, "melee/it/items/ithammerhead.c"),
            Object(NonMatching, "melee/it/items/itlipstickspore.c"),
            Object(NonMatching, "melee/it/items/itfflowerflame.c"),
            Object(NonMatching, "melee/it/items/itevyoshiegg.c"),
            # Fighter-related items
            Object(NonMatching, "melee/it/items/itmariofireball.c"),
            Object(NonMatching, "melee/it/items/itkirbycutterbeam.c"),
            Object(NonMatching, "melee/it/items/itfoxlaser.c"),
            Object(NonMatching, "melee/it/items/itfoxillusion.c"),
            Object(NonMatching, "melee/it/items/itlinkbomb.c"),
            Object(NonMatching, "melee/it/items/itlinkboomerang.c"),
            Object(NonMatching, "melee/it/items/itlinkhookshot.c"),
            Object(NonMatching, "melee/it/items/itlinkarrow.c"),
            Object(NonMatching, "melee/it/items/itnesspkfire.c"),
            Object(NonMatching, "melee/it/items/itnesspkfirepillar.c"),
            Object(NonMatching, "melee/it/items/itnesspkflush.c"),
            Object(NonMatching, "melee/it/items/itnesspkthunderball.c"),
            Object(NonMatching, "melee/it/items/itnesspkthundertrail.c"),
            Object(NonMatching, "melee/it/items/itkoopaflame.c"),
            Object(NonMatching, "melee/it/items/itnessbat.c"),
            Object(NonMatching, "melee/it/items/it_2ADA.c"),
            Object(NonMatching, "melee/it/items/itkirbyhammer.c"),
            Object(NonMatching, "melee/it/items/itfoxblaster.c"),
            Object(NonMatching, "melee/it/items/itlinkbow.c"),
            Object(NonMatching, "melee/it/items/itnesspkflushexplode.c"),
            Object(NonMatching, "melee/it/items/itseakneedlethrown.c"),
            Object(NonMatching, "melee/it/items/itseakneedleheld.c"),
            Object(Matching, "melee/it/items/itseakvanish.c"),
            Object(NonMatching, "melee/it/items/itpikachuthunder.c"),
            Object(NonMatching, "melee/it/items/itmariocape.c"),
            Object(NonMatching, "melee/it/items/ityoshieggthrow.c"),
            Object(Matching, "melee/it/items/ityoshistar.c"),
            Object(NonMatching, "melee/it/items/itpikachutjoltground.c"),
            Object(NonMatching, "melee/it/items/itpikachutjoltair.c"),
            Object(NonMatching, "melee/it/items/itsamusbomb.c"),
            Object(NonMatching, "melee/it/items/itsamuschargeshot.c"),
            Object(NonMatching, "melee/it/items/itsamusmissile.c"),
            Object(NonMatching, "melee/it/items/itsamusgrapple.c"),
            Object(NonMatching, "melee/it/items/itseakchain.c"),
            Object(NonMatching, "melee/it/items/itpeachexplode.c"),
            Object(NonMatching, "melee/it/items/itpeachturnip.c"),
            Object(Matching, "melee/it/items/itpeachparasol.c"),
            Object(NonMatching, "melee/it/items/itpeachtoad.c"),
            Object(NonMatching, "melee/it/items/itpeachtoadspore.c"),
            Object(NonMatching, "melee/it/items/itnessyoyo.c"),
            Object(NonMatching, "melee/it/items/itluigifireball.c"),
            Object(NonMatching, "melee/it/items/itdrmariopill.c"),
            Object(NonMatching, "melee/it/items/itclimbersice.c"),
            Object(NonMatching, "melee/it/items/itclimbersblizzard.c"),
            Object(NonMatching, "melee/it/items/itclimbersstring.c"),
            Object(NonMatching, "melee/it/items/itzeldadinfire.c"),
            Object(NonMatching, "melee/it/items/itzeldadinfireexplode.c"),
            Object(NonMatching, "melee/it/items/itmewtwodisable.c"),
            Object(NonMatching, "melee/it/items/itmewtwoshadowball.c"),
            Object(NonMatching, "melee/it/items/itgamewatchgreenhouse.c"),
            Object(NonMatching, "melee/it/items/itgamewatchmanhole.c"),
            Object(NonMatching, "melee/it/items/itgamewatchfire.c"),
            Object(NonMatching, "melee/it/items/itgamewatchparachute.c"),
            Object(NonMatching, "melee/it/items/itgamewatchturtle.c"),
            Object(NonMatching, "melee/it/items/itgamewatchbreath.c"),
            Object(NonMatching, "melee/it/items/itkirbygamewatchchefpan.c"),
            Object(NonMatching, "melee/it/items/itgamewatchjudge.c"),
            Object(NonMatching, "melee/it/items/itgamewatchpanic.c"),
            Object(NonMatching, "melee/it/items/itgamewatchrescue.c"),
            Object(NonMatching, "melee/it/items/itgamewatchchef.c"),
            Object(NonMatching, "melee/it/items/itclinkmilk.c"),
            # Pokémon
            Object(NonMatching, "melee/it/items/ittosakinto.c"),
            Object(NonMatching, "melee/it/items/itchicorita.c"),
            Object(NonMatching, "melee/it/items/itchicoritaleaf.c"),
            Object(NonMatching, "melee/it/items/itkabigon.c"),
            Object(NonMatching, "melee/it/items/itkamex.c"),
            Object(NonMatching, "melee/it/items/itmatadogas.c"),
            Object(NonMatching, "melee/it/items/itlizardon.c"),
            Object(NonMatching, "melee/it/items/itfire.c"),
            Object(NonMatching, "melee/it/items/itthunder.c"),
            Object(NonMatching, "melee/it/items/itfreezer.c"),
            Object(NonMatching, "melee/it/items/itsonans.c"),
            Object(NonMatching, "melee/it/items/ithassam.c"),
            Object(NonMatching, "melee/it/items/itunknown.c"),
            Object(NonMatching, "melee/it/items/itentei.c"),
            Object(NonMatching, "melee/it/items/itraikou.c"),
            Object(NonMatching, "melee/it/items/itsuikun.c"),
            Object(NonMatching, "melee/it/items/itkireihana.c"),
            Object(NonMatching, "melee/it/items/itmarumine.c"),
            Object(NonMatching, "melee/it/items/itlugia.c"),
            Object(NonMatching, "melee/it/items/ithouou.c"),
            Object(Matching, "melee/it/items/itmetamon.c"),
            Object(NonMatching, "melee/it/items/itpippi.c"),
            Object(NonMatching, "melee/it/items/ittogepy.c"),
            Object(NonMatching, "melee/it/items/itmew.c"),
            Object(NonMatching, "melee/it/items/itcerebi.c"),
            Object(NonMatching, "melee/it/items/ithitodeman.c"),
            Object(NonMatching, "melee/it/items/itlucky.c"),
            Object(Matching, "melee/it/items/itporygon2.c"),
            Object(NonMatching, "melee/it/items/ithinoarashi.c"),
            Object(NonMatching, "melee/it/items/itmaril.c"),
            Object(NonMatching, "melee/it/items/itfushigibana.c"),
            # Indivudal items
            Object(NonMatching, "melee/it/items/itoldkuri.c"),
            Object(Matching, "melee/it/items/itmato.c"),
            Object(NonMatching, "melee/it/items/itheiho.c"),
            Object(NonMatching, "melee/it/items/itlikelike.c"),
            Object(NonMatching, "melee/it/items/itnokonoko.c"),
            Object(NonMatching, "melee/it/items/itzgshell.c"),
            Object(NonMatching, "melee/it/items/itzrshell.c"),
            Object(NonMatching, "melee/it/items/itpatapata.c"),
            Object(NonMatching, "melee/it/items/itklap.c"),
            Object(NonMatching, "melee/it/items/itoldottosea.c"),
            Object(NonMatching, "melee/it/items/itwhitebea.c"),
            # Stage-related items
            Object(NonMatching, "melee/it/items/itoctarock.c"),
            Object(NonMatching, "melee/it/items/it_2E5A.c"),
            Object(NonMatching, "melee/it/items/it_2E6A.c"),
            Object(NonMatching, "melee/it/items/itarwinglaser.c"),
            Object(NonMatching, "melee/it/items/itoctarockstone.c"),
            Object(NonMatching, "melee/it/items/itleadead.c"),
            Object(NonMatching, "melee/it/items/itgreatfoxlaser.c"),
            Object(NonMatching, "melee/it/items/ittincle.c"),
            Object(NonMatching, "melee/it/items/itkyasarin.c"),
            Object(NonMatching, "melee/it/items/itwhispyapple.c"),
            Object(NonMatching, "melee/it/items/ittools.c"),
            Object(NonMatching, "melee/it/items/itkyasarinegg.c"),
            Object(NonMatching, "melee/it/items/itmasterhandlaser.c"),
            Object(NonMatching, "melee/it/items/itmasterhandbullet.c"),
            Object(NonMatching, "melee/it/items/itcrazyhandbomb.c"),
            Object(NonMatching, "melee/it/items/itcoin.c"),
            Object(NonMatching, "melee/it/items/itkirby_2F23.c"),
            Object(NonMatching, "melee/it/items/it_2F28.c"),
            Object(Matching, "melee/it/items/it_2F2B.c"),
            Object(Matching, "melee/it/items/itkirbyyoshispecialn.c"),
            Object(NonMatching, "melee/it/items/it_27CF.c"),
        ],
    ),
    MeleeLib(
        "if (User interface)",
        [
            Object(NonMatching, "melee/if/ifall.c"),
            Object(NonMatching, "melee/if/iftime.c"),
            Object(NonMatching, "melee/if/ifstatus_data.c"),
            Object(NonMatching, "melee/if/ifstatus.c"),
            Object(NonMatching, "melee/if/if_2F72.c"),
            Object(NonMatching, "melee/if/ifstock.c"),
            Object(NonMatching, "melee/if/ifmagnify.c"),
        ],
    ),
    MeleeLib(
        "un (Unknown)",
        [
            Object(NonMatching, "melee/un_2FC9.c"),
        ],
    ),
    MeleeLib(
        "ty (Toy, trophies)",
        [
            Object(NonMatching, "melee/ty/toy.c"),
            Object(NonMatching, "melee/ty/tylist.c"),
            Object(NonMatching, "melee/ty/tyfigupon.c"),
            Object(NonMatching, "melee/ty/tydisplay.c"),
        ],
    ),
    MeleeLib(
        "vi (Visual, cutscenes)",
        [
            Object(NonMatching, "melee/vi/vi.c"),
            Object(NonMatching, "melee/vi/vi0102.c"),
            Object(NonMatching, "melee/vi/vi0401.c"),
            Object(NonMatching, "melee/vi/vi0402.c"),
            Object(NonMatching, "melee/vi/vi0501.c"),
            Object(NonMatching, "melee/vi/vi0502.c"),
            Object(NonMatching, "melee/vi/vi0601.c"),
            Object(NonMatching, "melee/vi/vi0801.c"),
            Object(NonMatching, "melee/vi/vi1101.c"),
            Object(NonMatching, "melee/vi/vi1201v1.c"),
            Object(NonMatching, "melee/vi/vi1201v2.c"),
            Object(NonMatching, "melee/vi/vi1202.c"),
        ],
    ),
    RuntimeLib(
        "Gekko runtime",
        [
            Object(Matching, "Runtime/__va_arg.c"),
            Object(Matching, "Runtime/global_destructor_chain.c"),
            Object(NonMatching, "Runtime/Gecko_ExceptionPPC.c"),
            Object(Matching, "Runtime/Gecko_setjmp.c"),
            Object(NonMatching, "Runtime/runtime.c"),
            Object(Matching, "Runtime/__init_cpp_exceptions.c"),
        ],
    ),
    RuntimeLib(
        "MSL (Metrowerks Standard Libraries)",
        [
            Object(NonMatching, "MSL/abort_exit.c"),
            Object(NonMatching, "MSL/ansi_fp.c"),
            Object(NonMatching, "MSL/buffer_io.c"),
            Object(Matching, "MSL/PPC_EABI/critical_regions.gamecube.c"),
            Object(Matching, "MSL/ctype.c"),
            Object(NonMatching, "MSL/direct_io.c"),
            Object(Matching, "MSL/cstring.c"),
            Object(NonMatching, "MSL/mem_funcs.c"),
            Object(NonMatching, "MSL/printf.c"),
            Object(Matching, "MSL/rand.c"),
            Object(Matching, "MSL/string.c"),
            Object(Matching, "MSL/errno.c"),
            Object(NonMatching, "MSL/strtoul.c"),
            Object(NonMatching, "MSL/console_io.c"),
            Object(Matching, "MSL/wchar_io.c"),
            Object(Matching, "MSL/math_1.c"),
            Object(NonMatching, "MSL/trigf.c"),
            Object(NonMatching, "MSL/math.c"),
        ],
    ),
    RuntimeLib(
        "MetroTRK (Metrowerks Target Resident Kernel)",
        [
            Object(NonMatching, "MetroTRK/mainloop.c"),
            Object(NonMatching, "MetroTRK/nubevent.c"),
            Object(NonMatching, "MetroTRK/nubinit.c"),
            Object(NonMatching, "MetroTRK/msg.c"),
            Object(NonMatching, "MetroTRK/msgbuf.c"),
            Object(NonMatching, "MetroTRK/serpoll.c"),
            Object(NonMatching, "MetroTRK/dispatch.c"),
            Object(NonMatching, "MetroTRK/msghndlr.c"),
            Object(NonMatching, "MetroTRK/flush_cache.c"),
            Object(NonMatching, "MetroTRK/mem_TRK.c"),
            Object(NonMatching, "MetroTRK/targimpl.c"),
            Object(NonMatching, "MetroTRK/dolphin_trk.c"),
            Object(NonMatching, "MetroTRK/mpc_7xx_603e.c"),
            Object(NonMatching, "MetroTRK/main_TRK.c"),
            Object(NonMatching, "MetroTRK/dolphin_trk_glue.c"),
            Object(NonMatching, "MetroTRK/targcont.c"),
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
            Object(NonMatching, "dolphin/OdemuExi2/DebuggerDriver.c"),
        ],
    ),
    DolphinLib(
        "hio",
        [
            Object(NonMatching, "dolphin/hio/hio.c"),
        ],
    ),
    DolphinLib(
        "mcc",
        [
            Object(NonMatching, "dolphin/mcc/mcc.c"),
            Object(NonMatching, "dolphin/mcc/fio.c"),
        ],
    ),
    DolphinLib(
        "thp",
        [
            Object(NonMatching, "dolphin/thp/THPDec.c"),
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
            Object(NonMatching, "dolphin/db/db.c"),
        ],
    ),
    DolphinLib(
        "dsp",
        [
            Object(NonMatching, "dolphin/dsp/dsp.c"),
            Object(Matching, "dolphin/dsp/dsp_debug.c"),
            Object(NonMatching, "dolphin/dsp/dsp_task.c"),
        ],
    ),
    DolphinLib(
        "dvd",
        [
            Object(NonMatching, "dolphin/dvd/dvdlow.c"),
            Object(NonMatching, "dolphin/dvd/dvdfs.c"),
            Object(NonMatching, "dolphin/dvd/dvd.c"),
            Object(NonMatching, "dolphin/dvd/dvdqueue.c"),
            Object(NonMatching, "dolphin/dvd/dvderror.c"),
            Object(NonMatching, "dolphin/dvd/fstload.c"),
        ],
    ),
    DolphinLib(
        "gx",
        [
            Object(NonMatching, "dolphin/gx/GXInit.c"),
            Object(NonMatching, "dolphin/gx/GXFifo.c"),
            Object(Matching, "dolphin/gx/GXAttr.c"),
            Object(Matching, "dolphin/gx/GXMisc.c"),
            Object(Matching, "dolphin/gx/GXGeometry.c"),
            Object(Matching, "dolphin/gx/GXFrameBuf.c"),
            Object(Matching, "dolphin/gx/GXLight.c"),
            Object(NonMatching, "dolphin/gx/GXTexture.c"),
            Object(Matching, "dolphin/gx/GXBump.c"),
            Object(Matching, "dolphin/gx/GXTev.c"),
            Object(Matching, "dolphin/gx/GXPixel.c"),
            Object(Matching, "dolphin/gx/GXStubs.c"),
            Object(Matching, "dolphin/gx/GXDisplayList.c"),
            Object(NonMatching, "dolphin/gx/GXTransform.c"),
            Object(NonMatching, "dolphin/gx/GXPerf.c"),
        ],
    ),
    DolphinLib(
        "mtx",
        [
            Object(NonMatching, "dolphin/mtx/mtx.c"),
            Object(NonMatching, "dolphin/mtx/mtxvec.c"),
            Object(Matching, "dolphin/mtx/mtx44.c"),
            Object(NonMatching, "dolphin/mtx/vec.c"),
        ],
    ),
    DolphinLib(
        "os",
        [
            Object(NonMatching, "dolphin/os/OSInit.c"),
            Object(Matching, "dolphin/os/OSAlarm.c"),
            Object(Matching, "dolphin/os/OSAlloc.c"),
            Object(Matching, "dolphin/os/OSArena.c"),
            Object(NonMatching, "dolphin/os/OSAudioSystem.c"),
            Object(Matching, "dolphin/os/OSCache.c"),
            Object(Matching, "dolphin/os/OSContext.c"),
            Object(Matching, "dolphin/os/OSError.c"),
            Object(Matching, "dolphin/os/OSExi.c"),
            Object(Matching, "dolphin/os/OSFont.c"),
            Object(Matching, "dolphin/os/OSInterrupt.c"),
            Object(Matching, "dolphin/os/OSLink.c"),
            Object(NonMatching, "dolphin/os/OSMemory.c"),
            Object(Matching, "dolphin/os/OSMutex.c"),
            Object(Matching, "dolphin/os/OSReboot.c"),
            Object(NonMatching, "dolphin/os/OSReset.c"),
            Object(Matching, "dolphin/os/OSResetSW.c"),
            Object(Matching, "dolphin/os/OSRtc.c"),
            Object(NonMatching, "dolphin/os/OSSerial.c"),
            Object(NonMatching, "dolphin/os/OSSerial_data.c"),
            Object(NonMatching, "dolphin/os/OSSync.c"),
            Object(NonMatching, "dolphin/os/OSThread.c"),
            Object(NonMatching, "dolphin/os/OSThread_data.c"),
            Object(NonMatching, "dolphin/os/OSTime.c"),
            Object(Matching, "dolphin/os/OSUartExi.c"),
            Object(NonMatching, "dolphin/os/init/__ppc_eabi_init_data.c"),
            Object(Matching, "dolphin/os/init/__ppc_eabi_init.c"),
        ],
    ),
    DolphinLib(
        "pad",
        [
            Object(Matching, "dolphin/pad/PadClamp.c"),
            Object(NonMatching, "dolphin/pad/pad.c"),
        ],
        fix_epilogue=True,
    ),
    DolphinLib(
        "vi",
        [
            Object(NonMatching, "dolphin/vi/vi.c"),
        ],
    ),
    DolphinLib(
        "ai",
        [
            Object(NonMatching, "dolphin/ai/ai.c"),
        ],
    ),
    DolphinLib(
        "ar",
        [
            Object(NonMatching, "dolphin/ar/ar.c"),
            Object(NonMatching, "dolphin/ar/arq.c"),
        ],
    ),
    DolphinLib(
        "card",
        [
            Object(Matching, "dolphin/card/CARDBios.c"),
            Object(NonMatching, "dolphin/card/CARDUnlock.c"),
            Object(NonMatching, "dolphin/card/CARDRdwr.c"),
            Object(NonMatching, "dolphin/card/CARDBlock.c"),
            Object(NonMatching, "dolphin/card/CARDDir.c"),
            Object(Matching, "dolphin/card/CARDCheck.c"),
            Object(Matching, "dolphin/card/CARDMount.c"),
            Object(Matching, "dolphin/card/CARDFormat.c"),
            Object(Matching, "dolphin/card/CARDOpen.c"),
            Object(NonMatching, "dolphin/card/CARDCreate.c"),
            Object(Matching, "dolphin/card/CARDRead.c"),
            Object(Matching, "dolphin/card/CARDWrite.c"),
            Object(Matching, "dolphin/card/CARDDelete.c"),
            Object(NonMatching, "dolphin/card/CARDStat.c"),
            Object(Matching, "dolphin/card/CARDRename.c"),
        ],
        fix_epilogue=True,
    ),
    DolphinLib(
        "ax",
        [
            Object(Matching, "dolphin/ax/AX.c"),
            Object(NonMatching, "dolphin/ax/AXAlloc.c"),
            Object(NonMatching, "dolphin/ax/AXAux.c"),
            Object(NonMatching, "dolphin/ax/AXCL.c"),
            Object(NonMatching, "dolphin/ax/AXOut.c"),
            Object(NonMatching, "dolphin/ax/AXSPB.c"),
            Object(NonMatching, "dolphin/ax/AXVPB.c"),
            Object(NonMatching, "dolphin/ax/AXProf.c"),
            Object(NonMatching, "dolphin/ax/DSPCode.c"),
        ],
    ),
    DolphinLib(
        "axfx",
        [
            Object(NonMatching, "dolphin/axfx/reverb_hi.c"),
            Object(NonMatching, "dolphin/axfx/reverb_std.c"),
            Object(NonMatching, "dolphin/axfx/chorus.c"),
            Object(NonMatching, "dolphin/axfx/delay.c"),
            Object(Matching, "dolphin/axfx/axfx.c"),
        ],
    ),
    SysdolphinLib(
        "sysdolphin (HAL base library)",
        [
            Object(Matching, "sysdolphin/baselib/dobj.c"),
            Object(NonMatching, "sysdolphin/baselib/tobj.c"),
            Object(Matching, "sysdolphin/baselib/state.c"),
            Object(NonMatching, "sysdolphin/baselib/tev.c"),
            Object(NonMatching, "sysdolphin/baselib/mobj.c"),
            Object(Matching, "sysdolphin/baselib/aobj.c"),
            Object(NonMatching, "sysdolphin/baselib/lobj.c"),
            Object(NonMatching, "sysdolphin/baselib/cobj.c"),
            Object(NonMatching, "sysdolphin/baselib/fobj.c"),
            Object(NonMatching, "sysdolphin/baselib/pobj.c"),
            Object(NonMatching, "sysdolphin/baselib/jobj.c"),
            Object(NonMatching, "sysdolphin/baselib/displayfunc.c"),
            Object(NonMatching, "sysdolphin/baselib/initialize.c"),
            Object(Matching, "sysdolphin/baselib/video.c"),
            Object(NonMatching, "sysdolphin/baselib/controller.c"),
            Object(NonMatching, "sysdolphin/baselib/rumble.c"),
            Object(NonMatching, "sysdolphin/baselib/spline.c"),
            Object(Matching, "sysdolphin/baselib/mtx.c"),
            Object(Matching, "sysdolphin/baselib/util.c"),
            Object(NonMatching, "sysdolphin/baselib/objalloc.c"),
            Object(NonMatching, "sysdolphin/baselib/robj.c"),
            Object(Matching, "sysdolphin/baselib/id.c"),
            Object(Matching, "sysdolphin/baselib/wobj.c"),
            Object(Matching, "sysdolphin/baselib/fog.c"),
            Object(Matching, "sysdolphin/baselib/perf.c"),
            Object(Matching, "sysdolphin/baselib/list.c"),
            Object(Matching, "sysdolphin/baselib/object.c"),
            Object(NonMatching, "sysdolphin/baselib/quatlib.c"),
            Object(Matching, "sysdolphin/baselib/memory.c"),
            Object(NonMatching, "sysdolphin/baselib/shadow.c"),
            Object(Matching, "sysdolphin/baselib/archive.c"),
            Object(Matching, "sysdolphin/baselib/random.c"),
            Object(NonMatching, "sysdolphin/baselib/bytecode.c"),
            Object(NonMatching, "sysdolphin/baselib/class.c"),
            Object(NonMatching, "sysdolphin/baselib/hash.c"),
            Object(NonMatching, "sysdolphin/baselib/texp.c"),
            Object(NonMatching, "sysdolphin/baselib/texpdag.c"),
            Object(NonMatching, "sysdolphin/baselib/leak.c"),
            Object(NonMatching, "sysdolphin/baselib/debug.c"),
            Object(NonMatching, "sysdolphin/baselib/synth.c"),
            Object(NonMatching, "sysdolphin/baselib/axdriver.c"),
            Object(NonMatching, "sysdolphin/baselib/devcom.c"),
            Object(NonMatching, "sysdolphin/baselib/gobjproc.c"),
            Object(NonMatching, "sysdolphin/baselib/gobjplink.c"),
            Object(NonMatching, "sysdolphin/baselib/gobjgxlink.c"),
            Object(Matching, "sysdolphin/baselib/gobjobject.c"),
            Object(Matching, "sysdolphin/baselib/gobjuserdata.c"),
            Object(NonMatching, "sysdolphin/baselib/gobj.c"),
            Object(NonMatching, "sysdolphin/baselib/baselib_shared_data_003.c"),
            Object(NonMatching, "sysdolphin/baselib/baselib_unknown_009.c"),
            Object(NonMatching, "sysdolphin/baselib/baselib_unknown_010.c"),
            Object(NonMatching, "sysdolphin/baselib/baselib_unknown_011.c"),
            Object(NonMatching, "sysdolphin/baselib/baselib_unknown_002.c"),
            Object(NonMatching, "sysdolphin/baselib/psdisp.c"),
            Object(NonMatching, "sysdolphin/baselib/psdisptev.c"),
            Object(NonMatching, "sysdolphin/baselib/psappsrt.c"),
            Object(NonMatching, "sysdolphin/baselib/sobjlib.c"),
            Object(NonMatching, "sysdolphin/baselib/sislib.c"),
            Object(NonMatching, "sysdolphin/baselib/baselib_shared_data_001.c"),
            Object(NonMatching, "sysdolphin/baselib/baselib_shared_data_002.c"),
            Object(NonMatching, "sysdolphin/baselib/hsd_40FF.c"),
            Object(NonMatching, "sysdolphin/baselib/hsd_3A94.c"),
            Object(NonMatching, "sysdolphin/baselib/hsd_3AA7.c"),
            Object(NonMatching, "sysdolphin/baselib/hsd_3B27.c"),
            Object(NonMatching, "sysdolphin/baselib/hsd_3B2B.c"),
            Object(NonMatching, "sysdolphin/baselib/hsd_3B2E.c"),
            Object(NonMatching, "sysdolphin/baselib/hsd_3B33.c"),
            Object(NonMatching, "sysdolphin/baselib/hsd_3B34.c"),
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
