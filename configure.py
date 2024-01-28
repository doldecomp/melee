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
    "--require-protos",
    dest="require_protos",
    action="store_true",
    help="require function prototypes",
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
config.dtk_tag = "v0.7.2"
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
    )


def SysdolphinLib(lib_name: str, objects: Objects) -> LibDict:
    return Lib(
        lib_name,
        objects,
        includes=[
            *includes_base,
            "src/sysdolphin",
        ],
        system_includes=[
            *system_includes_base,
            "src/dolphin",
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
    )


Matching = True

# Unconfirmed, might link as-is or with minor changes
Unknown = False

# Definitely not matching yet
NonMatching = False

config.warn_missing_config = args.verbose
config.warn_missing_source = args.verbose
config.libs = [
    MeleeLib(
        "lb (Library)",
        [
            Object(Matching, "melee/lb/lbcommand.c"),
            Object(Unknown, "melee/lb/lbcollision.c"),
            Object(Matching, "melee/lb/lblanguage.c"),
            Object(Matching, "melee/lb/lbtime.c"),
            Object(Unknown, "melee/lb/lb_00B0.c"),
            Object(Unknown, "melee/lb/lb_00CE.c"),
            Object(Unknown, "melee/lb/lbvector.c"),
            Object(Unknown, "melee/lb/lbshadow.c"),
            Object(Unknown, "melee/lb/lb_00F9.c"),
            Object(Unknown, "melee/lb/lbarq.c"),
            Object(Unknown, "melee/lb/lbmemory.c"),
            Object(Unknown, "melee/lb/lbheap.c"),
            Object(Unknown, "melee/lb/lbfile.c"),
            Object(Unknown, "melee/lb/lbarchive.c"),
            Object(Unknown, "melee/lb/lbdvd.c"),
            Object(Unknown, "melee/lb/lb_0192.c"),
            Object(Unknown, "melee/lb/lb_0198.c"),
            Object(Unknown, "melee/lb/lbsnap.c"),
            Object(Unknown, "melee/lb/lbgx.c"),
            Object(Unknown, "melee/lb/lbanim.c"),
            Object(Unknown, "melee/lb/lbmthp.c"),
            Object(Unknown, "melee/lb/lbbgflash.c"),
            Object(Unknown, "melee/lb/lbrefract.c"),
            Object(Unknown, "melee/lb/lbaudio_ax.c"),
        ],
    ),
    MeleeLib(
        "cm (Camera)",
        [
            Object(Unknown, "melee/cm/camera.c"),
            Object(Matching, "melee/cm/cmsnap.c"),
        ],
    ),
    MeleeLib(
        "pl (Player)",
        [
            Object(Matching, "melee/pl/player.c"),
            Object(Unknown, "melee/pl/plstale.c"),
            Object(Unknown, "melee/pl/pltrick.c"),
            Object(Unknown, "melee/pl/plbonus.c"),
            Object(Unknown, "melee/pl/plbonuslib.c"),
            Object(Unknown, "melee/pl/pl_040D.c"),
        ],
    ),
    MeleeLib(
        "mp (Map)",
        [
            Object(Unknown, "melee/mp/mpcoll.c"),
            Object(Unknown, "melee/mp/mplib.c"),
            Object(Unknown, "melee/mp/mpisland.c"),
        ],
    ),
    MeleeLib(
        "ef (Visual effects)",
        [
            Object(Unknown, "melee/ef/eflib.c"),
            Object(Unknown, "melee/ef/efsync.c"),
            Object(Unknown, "melee/ef/ef_061D.c"),
            Object(Unknown, "melee/ef/efasync.c"),
        ],
    ),
    MeleeLib(
        "ft (Fighters)",
        [
            # Main
            Object(Matching, "melee/ft/fighter.c"),
            Object(Unknown, "melee/ft/ftanim.c"),
            Object(Unknown, "melee/ft/ftaction.c"),
            Object(Unknown, "melee/ft/ftparts.c"),
            Object(Matching, "melee/ft/ftcamera.c"),
            Object(Unknown, "melee/ft/ftcoll.c"),
            Object(Unknown, "melee/ft/ft_07C1.c"),
            Object(Unknown, "melee/ft/ft_07C6.c"),
            Object(Unknown, "melee/ft/ftcommon.c"),
            Object(Unknown, "melee/ft/ftdrawcommon.c"),
            Object(Unknown, "melee/ft/ftcliffcommon.c"),
            Object(Unknown, "melee/ft/ftwalljump.c"),
            Object(Unknown, "melee/ft/ft_0819.c"),
            Object(Unknown, "melee/ft/ft_081B.c"),
            Object(Unknown, "melee/ft/ft_0852.c"),
            Object(Unknown, "melee/ft/ftdata.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_Init.c"),
            Object(Unknown, "melee/ft/ftlib.c"),
            Object(Matching, "melee/ft/ftwaitanim.c"),
            Object(Unknown, "melee/ft/ft_0877.c"),
            Object(Unknown, "melee/ft/ft_0881.c"),
            Object(Unknown, "melee/ft/ft_0892.c"),
            # Common
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_Wait.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_08A6.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_Attack1.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_AttackDash.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_AttackS3.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_AttackHi3.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_AttackLw3.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_AttackS4.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_AttackHi4.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_AttackLw4.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_AttackAir.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_LandingAir.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_Damage.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_DamageFall.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_DamageIce.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_Guard.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_ItemGet.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_ItemThrow.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_SpecialS.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_SpecialAir.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_FallSpecial.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_Lift.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_DownBound.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_DownStand.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_Down.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_DownAttack.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_Passive.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_PassiveStand.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_ShieldBreakFly.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_ShieldBreakFall.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_ShieldBreakDown.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_ShieldBreakStand.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_Furafura.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_Escape.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_EscapeAir.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_Rebound.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_Pass.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_Ottotto.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_CliffWait.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_CliffClimb.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_CliffAttack.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_CliffEscape.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_CliffJump.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_CargoWait.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_CargoWalk.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_CargoTurn.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_CargoKneebend.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_CargoJump.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_CargoFall.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_CargoLanding.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_CargoThrow.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_09C4.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_Shouldered.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_CaptureCaptain.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_09CB.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_BarrelWait.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_StopWall.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_StopCeil.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_DownDamage.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_MissFoot.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_09F4.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_09F7.c"),
            Object(Matching, "melee/ft/chara/ftMario/ftMr_Strings.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_0A01.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_0B3E.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_CaptureYoshi.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_YoshiEgg.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_CaptureKoopa.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_CaptureDamageKoopa.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_CaptureWaitKoopa.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_ThrownKoopa.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_CaptureMewtwo.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_ThrownMewtwo.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_CaptureKirby.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_CaptureWaitKirby.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_ThrownKirby.c"),
            Object(Unknown, "melee/ft/ft_3C61.c"),
            # Main again
            Object(Unknown, "melee/ft/ftdemo.c"),
            Object(Unknown, "melee/ft/ft_0BEC.c"),
            Object(Matching, "melee/ft/ft_0BEF.c"),
            Object(Unknown, "melee/ft/ft_0BF0.c"),
            Object(Unknown, "melee/ft/ftmaterial.c"),
            Object(Unknown, "melee/ft/ftcolanim.c"),
            Object(Unknown, "melee/ft/ftdevice.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_Bury.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_FlyReflect.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_PassiveWall.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_PassiveCeil.c"),
            Object(Unknown, "melee/ft/ftafterimage.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_DamageSong.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_0C35.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_AirCatch.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_DamageBind.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_WarpStar.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_HammerWait.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_HammerWalk.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_HammerTurn.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_HammerJump.c"),
            Object(Unknown, "melee/ft/chara/ftCommon/ftCo_HammerKneeBend.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_HammerFall.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_HammerLanding.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_0C60.c"),
            Object(Matching, "melee/ft/chara/ftCommon/ftCo_DemoCallback0.c"),
            Object(Unknown, "melee/ft/ft_0C31.c"),
            Object(Unknown, "melee/ft/ftmetal.c"),
            Object(Unknown, "melee/ft/ft_0C88.c"),
            Object(Unknown, "melee/ft/ftswing.c"),
            Object(Unknown, "melee/ft/ft_0CD1.c"),
            Object(Unknown, "melee/ft/ftstarrodswing.c"),
            Object(Unknown, "melee/ft/ftlipstickswing.c"),
            Object(Unknown, "melee/ft/ft_0CDD.c"),
            Object(Unknown, "melee/ft/ftattacks4combo.c"),
            Object(Unknown, "melee/ft/ft_0CEE.c"),
            Object(Unknown, "melee/ft/ftchangeparam.c"),
            Object(Unknown, "melee/ft/ft_0D14.c"),
            # Donkey Kong (common states)
            Object(Matching, "melee/ft/chara/ftDonkey/ftDk_HeavyWait0.c"),
            Object(Matching, "melee/ft/chara/ftDonkey/ftDk_HeavyWalk.c"),
            Object(Unknown, "melee/ft/ftwalkcommon.c"),
            Object(Matching, "melee/ft/chara/ftDonkey/ftDk_MS_345_0.c"),
            Object(Matching, "melee/ft/chara/ftDonkey/ftDk_HeavyTurn.c"),
            Object(Matching, "melee/ft/chara/ftDonkey/ftDk_HeavyFall.c"),
            Object(Matching, "melee/ft/chara/ftDonkey/ftDk_HeavyJump.c"),
            Object(Matching, "melee/ft/chara/ftDonkey/ftDk_HeavyWait1.c"),
            Object(Matching, "melee/ft/chara/ftDonkey/ftDk_HeavyLanding.c"),
            # Mario
            Object(Matching, "melee/ft/chara/ftMario/ftMr_Init.c"),
            Object(Unknown, "melee/ft/chara/ftMario/ftMr_SpecialN.c"),
            Object(Unknown, "melee/ft/chara/ftMario/ftMr_SpecialS.c"),
            Object(Unknown, "melee/ft/chara/ftMario/ftMr_SpecialHi.c"),
            Object(Unknown, "melee/ft/chara/ftMario/ftMr_SpecialLw.c"),
            # Captain Falcon
            Object(Unknown, "melee/ft/chara/ftCaptain/ftCa_Init.c"),
            Object(Unknown, "melee/ft/chara/ftCaptain/ftCa_SpecialN.c"),
            Object(Unknown, "melee/ft/chara/ftCaptain/ftCa_SpecialS.c"),
            Object(Unknown, "melee/ft/chara/ftCaptain/ftCa_SpecialLw.c"),
            Object(Unknown, "melee/ft/chara/ftCaptain/ftCa_SpecialHi.c"),
            # Fox
            Object(Matching, "melee/ft/chara/ftFox/ftFx_Init.c"),
            Object(Unknown, "melee/ft/chara/ftFox/ftFx_AppealS.c"),
            Object(Unknown, "melee/ft/chara/ftFox/ftFx_SpecialN.c"),
            Object(Unknown, "melee/ft/chara/ftFox/ftFx_SpecialHi.c"),
            Object(Unknown, "melee/ft/chara/ftFox/ftFx_SpecialLw.c"),
            Object(Unknown, "melee/ft/chara/ftFox/ftFx_SpecialS.c"),
            # Link
            Object(Unknown, "melee/ft/chara/ftLink/ftLk_Init.c"),
            Object(Unknown, "melee/ft/chara/ftLink/ftLk_AttackAir.c"),
            Object(Unknown, "melee/ft/chara/ftLink/ftLk_SpecialLw.c"),
            Object(Unknown, "melee/ft/chara/ftLink/ftLk_SpecialHi.c"),
            Object(Unknown, "melee/ft/chara/ftLink/ftLk_SpecialS.c"),
            Object(Unknown, "melee/ft/chara/ftLink/ftLk_SpecialN.c"),
            # Kirby
            Object(Unknown, "melee/ft/chara/ftKirby/ftKb_Init.c"),
            # Donkey Kong
            Object(Unknown, "melee/ft/chara/ftDonkey/ftDk_Init.c"),
            Object(Unknown, "melee/ft/chara/ftDonkey/ftDk_SpecialLw.c"),
            Object(Unknown, "melee/ft/chara/ftDonkey/ftDk_SpecialS.c"),
            Object(Unknown, "melee/ft/chara/ftDonkey/ftDk_SpecialN.c"),
            Object(Unknown, "melee/ft/chara/ftDonkey/ftDk_SpecialHi.c"),
            # Sheik
            Object(Matching, "melee/ft/chara/ftSeak/ftSk_Init.c"),
            Object(Unknown, "melee/ft/chara/ftSeak/ftSk_SpecialS.c"),
            Object(Unknown, "melee/ft/chara/ftSeak/ftSk_SpecialN.c"),
            Object(Unknown, "melee/ft/chara/ftSeak/ftSk_SpecialHi.c"),
            Object(Unknown, "melee/ft/chara/ftSeak/ftSk_SpecialLw.c"),
            # Ness
            Object(Matching, "melee/ft/chara/ftNess/ftNs_Init.c"),
            Object(Unknown, "melee/ft/chara/ftNess/ftNs_AttackS4.c"),
            Object(Unknown, "melee/ft/chara/ftNess/ftNs_AttackHi4.c"),
            Object(Matching, "melee/ft/chara/ftNess/ftNs_AttackLw4.c"),
            Object(Unknown, "melee/ft/chara/ftNess/ftNs_SpecialS.c"),
            Object(Unknown, "melee/ft/chara/ftNess/ftNs_SpecialN.c"),
            Object(Unknown, "melee/ft/chara/ftNess/ftNs_SpecialHi.c"),
            Object(Unknown, "melee/ft/chara/ftNess/ftNs_SpecialLw.c"),
            # Peach
            Object(Matching, "melee/ft/chara/ftPeach/ftPe_Init.c"),
            Object(Unknown, "melee/ft/chara/ftPeach/ftPe_Float.c"),
            Object(Matching, "melee/ft/chara/ftPeach/ftPe_FloatFall.c"),
            Object(Matching, "melee/ft/chara/ftPeach/ftPe_FloatAttack.c"),
            Object(Matching, "melee/ft/chara/ftPeach/ftPe_AttackS4.c"),
            Object(Matching, "melee/ft/chara/ftPeach/ftPe_SpecialS.c"),
            Object(Unknown, "melee/ft/chara/ftPeach/ftPe_SpecialLw.c"),
            Object(Matching, "melee/ft/chara/ftPeach/ftPe_SpecialHi.c"),
            Object(Matching, "melee/ft/chara/ftPeach/ftPe_SpecialN.c"),
            # Popo
            Object(Matching, "melee/ft/chara/ftPopo/ftPp_Init.c"),
            Object(Unknown, "melee/ft/chara/ftPopo/ftPp_SpecialN.c"),
            Object(Unknown, "melee/ft/chara/ftPopo/ftPp_SpecialS.c"),
            Object(Unknown, "melee/ft/chara/ftPp_SpecialS.c"),
            # Nana
            Object(Unknown, "melee/ft/chara/ftNana/ftNn_Init.c"),
            Object(Matching, "melee/ft/chara/ftNana/ftNn_Unk0.c"),
            # Pikachu
            Object(Unknown, "melee/ft/chara/ftPikachu/ftPk_Init.c"),
            Object(Unknown, "melee/ft/chara/ftPikachu/ftPk_SpecialN.c"),
            Object(Unknown, "melee/ft/chara/ftPikachu/ftPk_SpecialS.c"),
            Object(Unknown, "melee/ft/chara/ftPikachu/ftPk_SpecialHi.c"),
            Object(Unknown, "melee/ft/chara/ftPikachu/ftPk_SpecialLw.c"),
            # Samus
            Object(Matching, "melee/ft/chara/ftSamus/ftSs_Init.c"),
            Object(Unknown, "melee/ft/chara/ftSamus/ftSs_SpecialLw_0.c"),
            Object(Unknown, "melee/ft/chara/ftSamus/ftSs_SpecialN.c"),
            Object(Unknown, "melee/ft/chara/ftSamus/ftSs_SpecialS.c"),
            Object(Unknown, "melee/ft/chara/ftSamus/ftSs_SpecialHi.c"),
            Object(Unknown, "melee/ft/chara/ftSamus/ftSs_SpecialLw_1.c"),
            # Yoshi
            Object(Unknown, "melee/ft/chara/ftYoshi/ftYs_Init.c"),
            Object(Unknown, "melee/ft/chara/ftYoshi/ftYs_Guard.c"),
            Object(Unknown, "melee/ft/chara/ftYoshi/ftYs_SpecialN.c"),
            # Bowser
            Object(Unknown, "melee/ft/chara/ftKoopa/ftKp_Init.c"),
            Object(Matching, "melee/ft/chara/ftKoopa/ftKp_Unk1.c"),
            Object(Unknown, "melee/ft/chara/ftKp_SpecialS.c"),
            # Marth
            Object(Matching, "melee/ft/chara/ftMars/ftMs_Init.c"),
            Object(Unknown, "melee/ft/chara/ftMars/ftMs_SpecialN.c"),
            Object(Unknown, "melee/ft/chara/ftMars/ftMs_SpecialS.c"),
            Object(Unknown, "melee/ft/chara/ftMars/ftMs_SpecialHi.c"),
            Object(Unknown, "melee/ft/chara/ftMars/ftMs_SpecialLw.c"),
            # Zelda
            Object(Unknown, "melee/ft/chara/ftZelda/ftZd_Init.c"),
            Object(Unknown, "melee/ft/chara/ftZelda/ftZd_SpecialHi.c"),
            Object(Unknown, "melee/ft/chara/ftZelda/ftZd_SpecialN.c"),
            Object(Unknown, "melee/ft/chara/ftZelda/ftZd_SpecialLw.c"),
            Object(Unknown, "melee/ft/chara/ftZelda/ftZd_SpecialS.c"),
            # Jigglypuff
            Object(Unknown, "melee/ft/chara/ftPurin/ftPr_Init.c"),
            # Luigi
            Object(Matching, "melee/ft/chara/ftLuigi/ftLg_Init.c"),
            Object(Matching, "melee/ft/chara/ftLuigi/ftLg_SpecialN.c"),
            Object(Unknown, "melee/ft/chara/ftLuigi/ftLg_SpecialS.c"),
            Object(Unknown, "melee/ft/chara/ftLuigi/ftLg_SpecialHi.c"),
            Object(Unknown, "melee/ft/chara/ftLuigi/ftLg_SpecialLw.c"),
            # Mewtwo
            Object(Matching, "melee/ft/chara/ftMewtwo/ftMt_Init.c"),
            Object(Unknown, "melee/ft/chara/ftMewtwo/ftMt_SpecialHi.c"),
            Object(Unknown, "melee/ft/chara/ftMewtwo/ftMt_SpecialLw.c"),
            Object(Unknown, "melee/ft/chara/ftMewtwo/ftMt_SpecialS.c"),
            Object(Unknown, "melee/ft/chara/ftMewtwo/ftMt_SpecialN.c"),
            # Young Link
            Object(Unknown, "melee/ft/chara/ftCLink/ftCl_Init.c"),
            Object(Unknown, "melee/ft/chara/ftCLink/ftCl_AppealS.c"),
            # Dr. Mario
            Object(Unknown, "melee/ft/chara/ftDrMario/ftDr_Init.c"),
            Object(Unknown, "melee/ft/chara/ftDrMario/ftDr_AppealS.c"),
            # Falco
            Object(Unknown, "melee/ft/chara/ftFalco/ftFc_Init.c"),
            # Pichu
            Object(Matching, "melee/ft/chara/ftPichu/ftPc_Init.c"),
            # Mr. Game & Watch
            Object(Matching, "melee/ft/chara/ftGameWatch/ftGw_Init.c"),
            Object(Unknown, "melee/ft/chara/ftGameWatch/ftGw_AttackS4.c"),
            Object(Unknown, "melee/ft/chara/ftGameWatch/ftGw_AttackLw3.c"),
            Object(Unknown, "melee/ft/chara/ftGameWatch/ftGw_AttackAir.c"),
            Object(Unknown, "melee/ft/chara/ftGameWatch/ftGw_Attack11.c"),
            Object(Matching, "melee/ft/chara/ftGameWatch/ftGw_Attack100.c"),
            Object(Unknown, "melee/ft/chara/ftGameWatch/ftGw_SpecialS.c"),
            Object(Unknown, "melee/ft/chara/ftGameWatch/ftGw_SpecialLw.c"),
            Object(Unknown, "melee/ft/chara/ftGameWatch/ftGw_SpecialHi.c"),
            Object(Unknown, "melee/ft/chara/ftGameWatch/ftGw_SpecialN.c"),
            # Ganondorf
            Object(Matching, "melee/ft/chara/ftGanon/ftGn_Init.c"),
            # Roy
            Object(Matching, "melee/ft/chara/ftEmblem/ftFe_Init.c"),
            # Wireframe (boy)
            Object(Matching, "melee/ft/chara/ftZakoBoy/ftBo_Init.c"),
            # Wireframe (girl)
            Object(Matching, "melee/ft/chara/ftZakoGirl/ftGl_Init.c"),
            # Giga Koopa
            Object(Unknown, "melee/ft/chara/ftGigaKoopa/ftGk_Init.c"),
            # Sandbag
            Object(Matching, "melee/ft/chara/ftSandbag/ftSb_Init.c"),
            # Master Hand
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_Init.c"),
            Object(Unknown, "melee/ft/chara/ftMasterHand/ftMh_Wait1_0.c"),
            Object(Unknown, "melee/ft/chara/ftMasterHand/ftMh_Wait1_2.c"),
            Object(Unknown, "melee/ft/chara/ftMasterHand/ftMh_Entry.c"),
            Object(Unknown, "melee/ft/chara/ftMasterHand/ftMh_Damage_0.c"),
            Object(Unknown, "melee/ft/chara/ftMasterHand/ftMh_Sweep.c"),
            Object(Unknown, "melee/ft/chara/ftMasterHand/ftMh_SweepWait.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_Slap.c"),
            Object(Unknown, "melee/ft/chara/ftMasterHand/ftMh_Walk.c"),
            Object(Unknown, "melee/ft/chara/ftMasterHand/ftMh_Drill.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_RockCrush.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_PaperCrush.c"),
            Object(Unknown, "melee/ft/chara/ftMasterHand/ftMh_Poke.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_FingerBeam.c"),
            Object(Unknown, "melee/ft/chara/ftMasterHand/ftMh_FingerGun.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_FingerGun3.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_BackAirplane1.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_BackAirplane2.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_BackAirplane3.c"),
            Object(Unknown, "melee/ft/chara/ftMasterHand/ftMh_BackCrush_0.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_BackCrush_1.c"),
            Object(Unknown, "melee/ft/chara/ftMasterHand/ftMh_BackDisappear.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_Squeeze.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_Wait1_1.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_Squeezing.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_Throw.c"),
            Object(Unknown, "melee/ft/chara/ftMasterHand/ftMh_Slam.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_TagCrush.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_TagApplaud.c"),
            Object(Unknown, "melee/ft/chara/ftMasterHand/ftMh_TagRockPaper.c"),
            Object(Unknown, "melee/ft/chara/ftMasterHand/ftMh_TagCancel.c"),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_CaptureMasterHand.c"),
            Object(
                Matching, "melee/ft/chara/ftMasterHand/ftMh_CaptureDamageMasterHand.c"
            ),
            Object(Matching, "melee/ft/chara/ftMasterHand/ftMh_ThrownMasterHand.c"),
            # Crazy Hand
            Object(Unknown, "melee/ft/chara/ftCrazyHand/ftCh_Init.c"),
            Object(Unknown, "melee/ft/chara/ftCrazyHand/ftCh_Unk0.c"),
            # Main
            Object(Unknown, "melee/ft/ftbosslib.c"),
        ],
    ),
    MeleeLib(
        "gm (Main game loop)",
        [
            Object(Unknown, "melee/gm/gmmain_lib.c"),
            Object(Unknown, "melee/gm/gmmain.c"),
            Object(Unknown, "melee/gm/gm_1601.c"),
            Object(Unknown, "melee/gm/gmtitle.c"),
            Object(Unknown, "melee/gm/gmcamera.c"),
            Object(Unknown, "melee/gm_1A36.c"),
        ],
    ),
    MeleeLib(
        "gr (Ground, stages)",
        [
            # Main
            Object(Unknown, "melee/gr/ground.c"),
            Object(Unknown, "melee/gr/grdisplay.c"),
            Object(Unknown, "melee/gr/grdatfiles.c"),
            Object(Unknown, "melee/gr/granime.c"),
            Object(Unknown, "melee/gr/grmaterial.c"),
            Object(Unknown, "melee/gr/grlib.c"),
            Object(Unknown, "melee/gr/grdynamicattr.c"),
            Object(Unknown, "melee/gr/grzakogenerator.c"),
            # Individual stages
            Object(Unknown, "melee/gr/grfzerocar.c"),
            Object(Unknown, "melee/gr/grizumi.c"),
            Object(Unknown, "melee/gr/grcastle.c"),
            Object(Unknown, "melee/gr/grstadium.c"),
            Object(Unknown, "melee/gr/grkongo.c"),
            Object(Unknown, "melee/gr/grzebes.c"),
            Object(Unknown, "melee/gr/grcorneria.c"),
            Object(Unknown, "melee/gr/grstory.c"),
            Object(Unknown, "melee/gr/gronett.c"),
            Object(Unknown, "melee/gr/grbigblue.c"),
            Object(Unknown, "melee/gr/grmutecity.c"),
            Object(Unknown, "melee/gr/grfourside.c"),
            Object(Unknown, "melee/gr/grgreatbay.c"),
            Object(Unknown, "melee/gr/gricemt.c"),
            Object(Unknown, "melee/gr/grinishie1.c"),
            Object(Unknown, "melee/gr/grinishie2.c"),
            Object(Unknown, "melee/gr/grkraid.c"),
            Object(Unknown, "melee/gr/grrcruise.c"),
            Object(Unknown, "melee/gr/grshrine.c"),
            Object(Unknown, "melee/gr/gryorster.c"),
            Object(Unknown, "melee/gr/grgarden.c"),
            Object(Unknown, "melee/gr/grvenom.c"),
            Object(Unknown, "melee/gr/grtest.c"),
            Object(Unknown, "melee/gr/grkinokoroute.c"),
            Object(Unknown, "melee/gr/grshrineroute.c"),
            Object(Unknown, "melee/gr/grzebesroute.c"),
            Object(Unknown, "melee/gr/grbigblueroute.c"),
            Object(Unknown, "melee/gr/grfigure1.c"),
            Object(Unknown, "melee/gr/grfigure2.c"),
            Object(Unknown, "melee/gr/grfigure3.c"),
            Object(Unknown, "melee/gr/groldyoshi.c"),
            Object(Unknown, "melee/gr/groldkongo.c"),
            Object(Unknown, "melee/gr/groldpupupu.c"),
            Object(Unknown, "melee/gr/grpura.c"),
            Object(Unknown, "melee/gr/grgreens.c"),
            Object(Unknown, "melee/gr/grflatzone.c"),
            Object(Unknown, "melee/gr/grpushon.c"),
            Object(Unknown, "melee/gr/grfigureget.c"),
            Object(Unknown, "melee/gr/grbattle.c"),
            Object(Unknown, "melee/gr/grlast.c"),
            Object(Unknown, "melee/gr/grhomerun.c"),
            Object(Unknown, "melee/gr/grheal.c"),
            # Break the Targets stages
            Object(Matching, "melee/gr/grtmario.c"),
            Object(Unknown, "melee/gr/grtcaptain.c"),
            Object(Unknown, "melee/gr/grtclink.c"),
            Object(Unknown, "melee/gr/grtdonkey.c"),
            Object(Matching, "melee/gr/grtdrmario.c"),
            Object(Matching, "melee/gr/grtfalco.c"),
            Object(Matching, "melee/gr/grtfox.c"),
            Object(Unknown, "melee/gr/grticeclimber.c"),
            Object(Matching, "melee/gr/grtkirby.c"),
            Object(Unknown, "melee/gr/grtkoopa.c"),
            Object(Matching, "melee/gr/grtlink.c"),
            Object(Matching, "melee/gr/grtluigi.c"),
            Object(Unknown, "melee/gr/grtmars.c"),
            Object(Matching, "melee/gr/grtmewtwo.c"),
            Object(Unknown, "melee/gr/grtness.c"),
            Object(Matching, "melee/gr/grtpeach.c"),
            Object(Unknown, "melee/gr/grtpichu.c"),
            Object(Unknown, "melee/gr/grtpikachu.c"),
            Object(Unknown, "melee/gr/grtpurin.c"),
            Object(Matching, "melee/gr/grtsamus.c"),
            Object(Matching, "melee/gr/grtseak.c"),
            Object(Unknown, "melee/gr/grtyoshi.c"),
            Object(Matching, "melee/gr/grtzelda.c"),
            Object(Unknown, "melee/gr/grtgamewatch.c"),
            Object(Unknown, "melee/gr/grtemblem.c"),
            Object(Unknown, "melee/gr/grtganon.c"),
            # Main
            Object(Matching, "melee/gr/stage.c"),
        ],
    ),
    MeleeLib(
        "db (Debug)",
        [
            Object(Unknown, "melee/db/db_2253.c"),
        ],
    ),
    MeleeLib(
        "mn (Menus)",
        [
            Object(Unknown, "melee/mn_2295.c"),
            Object(Unknown, "melee/mn/mnitemsw.c"),
            Object(Unknown, "melee/mn/mnstagesw.c"),
            Object(Unknown, "melee/mn/mnname.c"),
            Object(Unknown, "melee/mn/mnnamenew.c"),
            Object(Unknown, "melee/mn/mndiagram.c"),
            Object(Unknown, "melee/mn/mndiagram2.c"),
            Object(Unknown, "melee/mn/mndiagram3.c"),
            Object(Unknown, "melee/mn/mnvibration.c"),
            Object(Unknown, "melee/mn/mnsound.c"),
            Object(Matching, "melee/mn/mndeflicker.c"),
            Object(Unknown, "melee/mn/mnsoundtest.c"),
            Object(Unknown, "melee/mn/mnlanguage.c"),
            Object(Unknown, "melee/mn/mnhyaku.c"),
            Object(Unknown, "melee/mn/mnevent.c"),
            Object(Unknown, "melee/mn/mndatadel.c"),
            Object(Unknown, "melee/mn/mncount.c"),
            Object(Unknown, "melee/mn/mninfo.c"),
            Object(Unknown, "melee/mn/mninfobonus.c"),
            Object(Unknown, "melee/mn/mnsnap.c"),
            Object(Unknown, "melee/mn/mngallery.c"),
            Object(Unknown, "melee/mn/mnstagesel.c"),
            Object(Unknown, "melee/mn/mncharsel.c"),
        ],
    ),
    MeleeLib(
        "it (Items)",
        [
            # Main
            Object(Unknown, "melee/it/item.c"),
            Object(Unknown, "melee/it/it_26B1.c"),
            Object(Unknown, "melee/it/it_266F.c"),
            Object(Unknown, "melee/it/itcoll.c"),
            Object(Unknown, "melee/it/it_3F14.c"),
            Object(Unknown, "melee/it/it_3F23.c"),
            Object(Unknown, "melee/it/it_3F31.c"),
            Object(Unknown, "melee/it/it_2725.c"),
            # Individual items
            Object(Unknown, "melee/it/items/itcapsule.c"),
            Object(Unknown, "melee/it/items/itbombhei.c"),
            Object(Unknown, "melee/it/items/itdosei.c"),
            Object(Unknown, "melee/it/items/itheart.c"),
            Object(Unknown, "melee/it/items/ittomato.c"),
            Object(Matching, "melee/it/items/itstar.c"),
            Object(Unknown, "melee/it/items/itbat.c"),
            Object(Unknown, "melee/it/items/itsword.c"),
            Object(Unknown, "melee/it/items/itbox.c"),
            Object(Unknown, "melee/it/items/ittaru.c"),
            Object(Unknown, "melee/it/items/itegg.c"),
            Object(Unknown, "melee/it/items/itkusudama.c"),
            Object(Unknown, "melee/it/items/itparasol.c"),
            Object(Unknown, "melee/it/items/itgshell.c"),
            Object(Unknown, "melee/it/items/itrshell.c"),
            Object(Unknown, "melee/it/items/itlgun.c"),
            Object(Unknown, "melee/it/items/itfreeze.c"),
            Object(Unknown, "melee/it/items/itfoods.c"),
            Object(Unknown, "melee/it/items/itmsbomb.c"),
            Object(Unknown, "melee/it/items/itflipper.c"),
            Object(Unknown, "melee/it/items/itsscope.c"),
            Object(Unknown, "melee/it/items/itstarrod.c"),
            Object(Unknown, "melee/it/items/itharisen.c"),
            Object(Unknown, "melee/it/items/itfflower.c"),
            Object(Unknown, "melee/it/items/itkinoko.c"),
            Object(Unknown, "melee/it/items/itdkinoko.c"),
            Object(Matching, "melee/it/items/ithammer.c"),
            Object(Unknown, "melee/it/items/itwstar.c"),
            Object(Unknown, "melee/it/items/itscball.c"),
            Object(Unknown, "melee/it/items/itrabbitc.c"),
            Object(Unknown, "melee/it/items/itmetalb.c"),
            Object(Unknown, "melee/it/items/itlipstick.c"),
            Object(Matching, "melee/it/items/itspycloak.c"),
            Object(Unknown, "melee/it/items/ittarucann.c"),
            Object(Unknown, "melee/it/items/itmball.c"),
            Object(Unknown, "melee/it/items/itlgunray.c"),
            Object(Unknown, "melee/it/items/itstarrodstar.c"),
            Object(Unknown, "melee/it/items/itsscopebeam.c"),
            Object(Unknown, "melee/it/items/itlgunbeam.c"),
            Object(Unknown, "melee/it/items/ithammerhead.c"),
            Object(Unknown, "melee/it/items/itlipstickspore.c"),
            Object(Unknown, "melee/it/items/itfflowerflame.c"),
            Object(Unknown, "melee/it/items/itevyoshiegg.c"),
            # Fighter-related items
            Object(Unknown, "melee/it/items/itmariofireball.c"),
            Object(Unknown, "melee/it/items/itkirbycutterbeam.c"),
            Object(Unknown, "melee/it/items/itfoxlaser.c"),
            Object(Unknown, "melee/it/items/itfoxillusion.c"),
            Object(Unknown, "melee/it/items/itlinkbomb.c"),
            Object(Unknown, "melee/it/items/itlinkboomerang.c"),
            Object(Unknown, "melee/it/items/itlinkhookshot.c"),
            Object(Unknown, "melee/it/items/itlinkarrow.c"),
            Object(Unknown, "melee/it/items/itnesspkfire.c"),
            Object(Unknown, "melee/it/items/itnesspkfirepillar.c"),
            Object(Unknown, "melee/it/items/itnesspkflush.c"),
            Object(Unknown, "melee/it/items/itnesspkthunderball.c"),
            Object(Unknown, "melee/it/items/itnesspkthundertrail.c"),
            Object(Unknown, "melee/it/items/itkoopaflame.c"),
            Object(Unknown, "melee/it/items/itnessbat.c"),
            Object(Unknown, "melee/it/items/it_2ADA.c"),
            Object(Unknown, "melee/it/items/itkirbyhammer.c"),
            Object(Unknown, "melee/it/items/itfoxblaster.c"),
            Object(Unknown, "melee/it/items/itlinkbow.c"),
            Object(Unknown, "melee/it/items/itnesspkflushexplode.c"),
            Object(Unknown, "melee/it/items/itseakneedlethrown.c"),
            Object(Unknown, "melee/it/items/itseakneedleheld.c"),
            Object(Matching, "melee/it/items/itseakvanish.c"),
            Object(Unknown, "melee/it/items/itpikachuthunder.c"),
            Object(Unknown, "melee/it/items/itmariocape.c"),
            Object(Unknown, "melee/it/items/ityoshieggthrow.c"),
            Object(Matching, "melee/it/items/ityoshistar.c"),
            Object(Unknown, "melee/it/items/itpikachutjoltground.c"),
            Object(Unknown, "melee/it/items/itpikachutjoltair.c"),
            Object(Unknown, "melee/it/items/itsamusbomb.c"),
            Object(Unknown, "melee/it/items/itsamuschargeshot.c"),
            Object(Unknown, "melee/it/items/itsamusmissile.c"),
            Object(Unknown, "melee/it/items/itsamusgrapple.c"),
            Object(Unknown, "melee/it/items/itseakchain.c"),
            Object(Unknown, "melee/it/items/itpeachexplode.c"),
            Object(Unknown, "melee/it/items/itpeachturnip.c"),
            Object(Matching, "melee/it/items/itpeachparasol.c"),
            Object(Unknown, "melee/it/items/itpeachtoad.c"),
            Object(Unknown, "melee/it/items/itpeachtoadspore.c"),
            Object(Unknown, "melee/it/items/itnessyoyo.c"),
            Object(Unknown, "melee/it/items/itluigifireball.c"),
            Object(Unknown, "melee/it/items/itdrmariopill.c"),
            Object(Unknown, "melee/it/items/itclimbersice.c"),
            Object(Unknown, "melee/it/items/itclimbersblizzard.c"),
            Object(Unknown, "melee/it/items/itclimbersstring.c"),
            Object(Unknown, "melee/it/items/itzeldadinfire.c"),
            Object(Unknown, "melee/it/items/itzeldadinfireexplode.c"),
            Object(Unknown, "melee/it/items/itmewtwodisable.c"),
            Object(Unknown, "melee/it/items/itmewtwoshadowball.c"),
            Object(Unknown, "melee/it/items/itgamewatchgreenhouse.c"),
            Object(Unknown, "melee/it/items/itgamewatchmanhole.c"),
            Object(Unknown, "melee/it/items/itgamewatchfire.c"),
            Object(Unknown, "melee/it/items/itgamewatchparachute.c"),
            Object(Unknown, "melee/it/items/itgamewatchturtle.c"),
            Object(Unknown, "melee/it/items/itgamewatchbreath.c"),
            Object(Unknown, "melee/it/items/itkirbygamewatchchefpan.c"),
            Object(Unknown, "melee/it/items/itgamewatchjudge.c"),
            Object(Unknown, "melee/it/items/itgamewatchpanic.c"),
            Object(Unknown, "melee/it/items/itgamewatchrescue.c"),
            Object(Unknown, "melee/it/items/itgamewatchchef.c"),
            Object(Unknown, "melee/it/items/itclinkmilk.c"),
            # Pokémon
            Object(Unknown, "melee/it/items/ittosakinto.c"),
            Object(Unknown, "melee/it/items/itchicorita.c"),
            Object(Unknown, "melee/it/items/itchicoritaleaf.c"),
            Object(Unknown, "melee/it/items/itkabigon.c"),
            Object(Unknown, "melee/it/items/itkamex.c"),
            Object(Unknown, "melee/it/items/itmatadogas.c"),
            Object(Unknown, "melee/it/items/itlizardon.c"),
            Object(Unknown, "melee/it/items/itfire.c"),
            Object(Unknown, "melee/it/items/itthunder.c"),
            Object(Unknown, "melee/it/items/itfreezer.c"),
            Object(Unknown, "melee/it/items/itsonans.c"),
            Object(Unknown, "melee/it/items/ithassam.c"),
            Object(Unknown, "melee/it/items/itunknown.c"),
            Object(Unknown, "melee/it/items/itentei.c"),
            Object(Unknown, "melee/it/items/itraikou.c"),
            Object(Unknown, "melee/it/items/itsuikun.c"),
            Object(Unknown, "melee/it/items/itkireihana.c"),
            Object(Unknown, "melee/it/items/itmarumine.c"),
            Object(Unknown, "melee/it/items/itlugia.c"),
            Object(Unknown, "melee/it/items/ithouou.c"),
            Object(Matching, "melee/it/items/itmetamon.c"),
            Object(Unknown, "melee/it/items/itpippi.c"),
            Object(Unknown, "melee/it/items/ittogepy.c"),
            Object(Unknown, "melee/it/items/itmew.c"),
            Object(Unknown, "melee/it/items/itcerebi.c"),
            Object(Unknown, "melee/it/items/ithitodeman.c"),
            Object(Unknown, "melee/it/items/itlucky.c"),
            Object(Matching, "melee/it/items/itporygon2.c"),
            Object(Unknown, "melee/it/items/ithinoarashi.c"),
            Object(Unknown, "melee/it/items/itmaril.c"),
            Object(Unknown, "melee/it/items/itfushigibana.c"),
            # Indivudal items
            Object(Unknown, "melee/it/items/itoldkuri.c"),
            Object(Matching, "melee/it/items/itmato.c"),
            Object(Unknown, "melee/it/items/itheiho.c"),
            Object(Unknown, "melee/it/items/itlikelike.c"),
            Object(Unknown, "melee/it/items/itnokonoko.c"),
            Object(Unknown, "melee/it/items/itzgshell.c"),
            Object(Unknown, "melee/it/items/itzrshell.c"),
            Object(Unknown, "melee/it/items/itpatapata.c"),
            Object(Unknown, "melee/it/items/itklap.c"),
            Object(Unknown, "melee/it/items/itoldottosea.c"),
            Object(Unknown, "melee/it/items/itwhitebea.c"),
            # Stage-related items
            Object(Unknown, "melee/it/items/itoctarock.c"),
            Object(Unknown, "melee/it/items/it_2E5A.c"),
            Object(Unknown, "melee/it/items/it_2E6A.c"),
            Object(Unknown, "melee/it/items/itarwinglaser.c"),
            Object(Unknown, "melee/it/items/itoctarockstone.c"),
            Object(Unknown, "melee/it/items/itleadead.c"),
            Object(Unknown, "melee/it/items/itgreatfoxlaser.c"),
            Object(Unknown, "melee/it/items/ittincle.c"),
            Object(Unknown, "melee/it/items/itkyasarin.c"),
            Object(Unknown, "melee/it/items/itwhispyapple.c"),
            Object(Unknown, "melee/it/items/ittools.c"),
            Object(Unknown, "melee/it/items/itkyasarinegg.c"),
            Object(Unknown, "melee/it/items/itmasterhandlaser.c"),
            Object(Unknown, "melee/it/items/itmasterhandbullet.c"),
            Object(Unknown, "melee/it/items/itcrazyhandbomb.c"),
            Object(Unknown, "melee/it/items/itcoin.c"),
            Object(Unknown, "melee/it/items/itkirby_2F23.c"),
            Object(Unknown, "melee/it/items/it_2F28.c"),
            Object(Matching, "melee/it/items/it_2F2B.c"),
            Object(Matching, "melee/it/items/itkirbyyoshispecialn.c"),
            Object(Unknown, "melee/it/items/it_27CF.c"),
        ],
    ),
    MeleeLib(
        "if (User interface)",
        [
            Object(Unknown, "melee/if/ifall.c"),
            Object(Unknown, "melee/if/iftime.c"),
            Object(Unknown, "melee/if/ifstatus_data.c"),
            Object(Unknown, "melee/if/ifstatus.c"),
            Object(Unknown, "melee/if/if_2F72.c"),
            Object(Unknown, "melee/if/ifstock.c"),
            Object(Unknown, "melee/if/ifmagnify.c"),
        ],
    ),
    MeleeLib(
        "un (Unknown)",
        [
            Object(Unknown, "melee/un_2FC9.c"),
        ],
    ),
    MeleeLib(
        "ty (Toy, trophies)",
        [
            Object(Unknown, "melee/ty/toy.c"),
            Object(Unknown, "melee/ty/tylist.c"),
            Object(Unknown, "melee/ty/tyfigupon.c"),
            Object(Unknown, "melee/ty/tydisplay.c"),
        ],
    ),
    MeleeLib(
        "vi (Visual, cutscenes)",
        [
            Object(Unknown, "melee/vi/vi.c"),
            Object(Unknown, "melee/vi/vi0102.c"),
            Object(Unknown, "melee/vi/vi0401.c"),
            Object(Unknown, "melee/vi/vi0402.c"),
            Object(Unknown, "melee/vi/vi0501.c"),
            Object(Unknown, "melee/vi/vi0502.c"),
            Object(Unknown, "melee/vi/vi0601.c"),
            Object(Unknown, "melee/vi/vi0801.c"),
            Object(Unknown, "melee/vi/vi1101.c"),
            Object(Unknown, "melee/vi/vi1201v1.c"),
            Object(Unknown, "melee/vi/vi1201v2.c"),
            Object(Unknown, "melee/vi/vi1202.c"),
        ],
    ),
    RuntimeLib(
        "Gekko runtime",
        [
            Object(Matching, "Runtime/__va_arg.c"),
            Object(Matching, "Runtime/global_destructor_chain.c"),
            Object(Unknown, "Runtime/Gecko_ExceptionPPC.c"),
            Object(Unknown, "Runtime/Gecko_setjmp.c"),
            Object(Unknown, "Runtime/runtime.c"),
            Object(Matching, "Runtime/__init_cpp_exceptions.c"),
        ],
    ),
    RuntimeLib(
        "MSL (Metrowerks Standard Libraries)",
        [
            Object(Unknown, "MSL/abort_exit.c"),
            Object(Unknown, "MSL/ansi_fp.c"),
            Object(Unknown, "MSL/buffer_io.c"),
            Object(Matching, "MSL/PPC_EABI/critical_regions.gamecube.c"),
            Object(Matching, "MSL/ctype.c"),
            Object(Unknown, "MSL/direct_io.c"),
            Object(Matching, "MSL/cstring.c"),
            Object(Unknown, "MSL/mem_funcs.c"),
            Object(Unknown, "MSL/printf.c"),
            Object(Matching, "MSL/rand.c"),
            Object(Matching, "MSL/string.c"),
            Object(Matching, "MSL/errno.c"),
            Object(Unknown, "MSL/strtoul.c"),
            Object(Unknown, "MSL/console_io.c"),
            Object(Matching, "MSL/wchar_io.c"),
            Object(Matching, "MSL/math_1.c"),
            Object(Unknown, "MSL/trigf.c"),
            Object(Unknown, "MSL/math.c"),
        ],
    ),
    RuntimeLib(
        "MetroTRK (Metrowerks Target Resident Kernel)",
        [
            Object(Unknown, "MetroTRK/mainloop.c"),
            Object(Unknown, "MetroTRK/nubevent.c"),
            Object(Unknown, "MetroTRK/nubinit.c"),
            Object(Unknown, "MetroTRK/msg.c"),
            Object(Unknown, "MetroTRK/msgbuf.c"),
            Object(Unknown, "MetroTRK/serpoll.c"),
            Object(Unknown, "MetroTRK/dispatch.c"),
            Object(Unknown, "MetroTRK/msghndlr.c"),
            Object(Unknown, "MetroTRK/flush_cache.c"),
            Object(Unknown, "MetroTRK/mem_TRK.c"),
            Object(Unknown, "MetroTRK/targimpl.c"),
            Object(Unknown, "MetroTRK/dolphin_trk.c"),
            Object(Unknown, "MetroTRK/mpc_7xx_603e.c"),
            Object(Unknown, "MetroTRK/main_TRK.c"),
            Object(Unknown, "MetroTRK/dolphin_trk_glue.c"),
            Object(Unknown, "MetroTRK/targcont.c"),
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
            Object(Unknown, "dolphin/OdemuExi2/DebuggerDriver.c"),
        ],
    ),
    DolphinLib(
        "hio",
        [
            Object(Unknown, "dolphin/hio/hio.c"),
        ],
    ),
    DolphinLib(
        "mcc",
        [
            Object(Unknown, "dolphin/mcc/mcc.c"),
            Object(Unknown, "dolphin/mcc/fio.c"),
        ],
    ),
    DolphinLib(
        "thp",
        [
            Object(Unknown, "dolphin/thp/THPDec.c"),
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
            Object(Unknown, "dolphin/dvd/dvdlow.c"),
            Object(Matching, "dolphin/dvd/dvdfs.c"),
            Object(Matching, "dolphin/dvd/dvd.c"),
            Object(Matching, "dolphin/dvd/dvdqueue.c"),
            Object(Unknown, "dolphin/dvd/dvderror.c"),
            Object(Matching, "dolphin/dvd/fstload.c"),
        ],
    ),
    DolphinLib(
        "gx",
        [
            Object(Unknown, "dolphin/gx/GXInit.c"),
            Object(Matching, "dolphin/gx/GXFifo.c"),
            Object(Unknown, "dolphin/gx/GXAttr.c"),
            Object(Matching, "dolphin/gx/GXMisc.c"),
            Object(Matching, "dolphin/gx/GXGeometry.c"),
            Object(Unknown, "dolphin/gx/GXFrameBuf.c"),
            Object(Matching, "dolphin/gx/GXLight.c"),
            Object(Unknown, "dolphin/gx/GXTexture.c"),
            Object(Unknown, "dolphin/gx/GXBump.c"),
            Object(Unknown, "dolphin/gx/GXTev.c"),
            Object(Unknown, "dolphin/gx/GXPixel.c"),
            Object(Matching, "dolphin/gx/GXStubs.c"),
            Object(Matching, "dolphin/gx/GXDisplayList.c"),
            Object(Unknown, "dolphin/gx/GXTransform.c"),
            Object(Unknown, "dolphin/gx/GXPerf.c"),
        ],
    ),
    DolphinLib(
        "mtx",
        [
            Object(Unknown, "dolphin/mtx/mtx.c"),
            Object(Unknown, "dolphin/mtx/mtxvec.c"),
            Object(Matching, "dolphin/mtx/mtx44.c"),
            Object(Unknown, "dolphin/mtx/vec.c"),
        ],
    ),
    DolphinLib(
        "os",
        [
            Object(Matching, "dolphin/os/OSInit.c"),
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
            Object(Unknown, "dolphin/os/OSReboot.c"),
            Object(Unknown, "dolphin/os/OSReset.c"),
            Object(Matching, "dolphin/os/OSResetSW.c"),
            Object(Matching, "dolphin/os/OSRtc.c"),
            Object(Unknown, "dolphin/os/OSSerial.c"),
            Object(Matching, "dolphin/os/OSSync.c"),
            Object(Unknown, "dolphin/os/OSThread.c"),
            Object(Matching, "dolphin/os/OSTime.c"),
            Object(Unknown, "dolphin/os/OSUartExi.c"),
        ],
    ),
    DolphinLib(
        "pad",
        [
            Object(Matching, "dolphin/pad/PadClamp.c"),
            Object(Unknown, "dolphin/pad/pad.c"),
        ],
        fix_epilogue=True,
    ),
    DolphinLib(
        "vi",
        [
            Object(Unknown, "dolphin/vi/vi.c"),
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
            Object(Unknown, "dolphin/ar/ar.c"),
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
            Object(Unknown, "dolphin/ax/AXAlloc.c"),
            Object(Unknown, "dolphin/ax/AXAux.c"),
            Object(Unknown, "dolphin/ax/AXCL.c"),
            Object(Unknown, "dolphin/ax/AXOut.c"),
            Object(Unknown, "dolphin/ax/AXSPB.c"),
            Object(Unknown, "dolphin/ax/AXVPB.c"),
            Object(Unknown, "dolphin/ax/AXProf.c"),
            Object(Unknown, "dolphin/ax/DSPCode.c"),
        ],
    ),
    DolphinLib(
        "axfx",
        [
            Object(Unknown, "dolphin/axfx/reverb_hi.c"),
            Object(Unknown, "dolphin/axfx/reverb_std.c"),
            Object(Unknown, "dolphin/axfx/chorus.c"),
            Object(Unknown, "dolphin/axfx/delay.c"),
            Object(Matching, "dolphin/axfx/axfx.c"),
        ],
    ),
    SysdolphinLib(
        "sysdolphin (HAL base library)",
        [
            Object(Matching, "sysdolphin/baselib/dobj.c"),
            Object(Unknown, "sysdolphin/baselib/tobj.c"),
            Object(Matching, "sysdolphin/baselib/state.c"),
            Object(Unknown, "sysdolphin/baselib/tev.c"),
            Object(Unknown, "sysdolphin/baselib/mobj.c"),
            Object(Matching, "sysdolphin/baselib/aobj.c"),
            Object(Unknown, "sysdolphin/baselib/lobj.c"),
            Object(Unknown, "sysdolphin/baselib/cobj.c"),
            Object(Unknown, "sysdolphin/baselib/fobj.c"),
            Object(Unknown, "sysdolphin/baselib/pobj.c"),
            Object(Unknown, "sysdolphin/baselib/jobj.c"),
            Object(Unknown, "sysdolphin/baselib/displayfunc.c"),
            Object(Unknown, "sysdolphin/baselib/initialize.c"),
            Object(Unknown, "sysdolphin/baselib/video.c"),
            Object(Unknown, "sysdolphin/baselib/controller.c"),
            Object(Unknown, "sysdolphin/baselib/rumble.c"),
            Object(Unknown, "sysdolphin/baselib/spline.c"),
            Object(Matching, "sysdolphin/baselib/mtx.c"),
            Object(Matching, "sysdolphin/baselib/util.c"),
            Object(Unknown, "sysdolphin/baselib/objalloc.c"),
            Object(Unknown, "sysdolphin/baselib/robj.c"),
            Object(Matching, "sysdolphin/baselib/id.c"),
            Object(Matching, "sysdolphin/baselib/wobj.c"),
            Object(Matching, "sysdolphin/baselib/fog.c"),
            Object(Matching, "sysdolphin/baselib/perf.c"),
            Object(Matching, "sysdolphin/baselib/list.c"),
            Object(Matching, "sysdolphin/baselib/object.c"),
            Object(Unknown, "sysdolphin/baselib/quatlib.c"),
            Object(Matching, "sysdolphin/baselib/memory.c"),
            Object(Unknown, "sysdolphin/baselib/shadow.c"),
            Object(Matching, "sysdolphin/baselib/archive.c"),
            Object(Matching, "sysdolphin/baselib/random.c"),
            Object(Unknown, "sysdolphin/baselib/bytecode.c"),
            Object(Unknown, "sysdolphin/baselib/class.c"),
            Object(Unknown, "sysdolphin/baselib/hash.c"),
            Object(Unknown, "sysdolphin/baselib/texp.c"),
            Object(Unknown, "sysdolphin/baselib/texpdag.c"),
            Object(Unknown, "sysdolphin/baselib/leak.c"),
            Object(Unknown, "sysdolphin/baselib/debug.c"),
            Object(Unknown, "sysdolphin/baselib/synth.c"),
            Object(Unknown, "sysdolphin/baselib/axdriver.c"),
            Object(Unknown, "sysdolphin/baselib/devcom.c"),
            Object(Unknown, "sysdolphin/baselib/gobjproc.c"),
            Object(Unknown, "sysdolphin/baselib/gobjplink.c"),
            Object(Unknown, "sysdolphin/baselib/gobjgxlink.c"),
            Object(Matching, "sysdolphin/baselib/gobjobject.c"),
            Object(Matching, "sysdolphin/baselib/gobjuserdata.c"),
            Object(Unknown, "sysdolphin/baselib/gobj.c"),
            Object(Unknown, "sysdolphin/baselib/baselib_shared_data_003.c"),
            Object(Unknown, "sysdolphin/baselib/baselib_unknown_009.c"),
            Object(Unknown, "sysdolphin/baselib/baselib_unknown_010.c"),
            Object(Unknown, "sysdolphin/baselib/baselib_unknown_011.c"),
            Object(Unknown, "sysdolphin/baselib/baselib_unknown_002.c"),
            Object(Unknown, "sysdolphin/baselib/psdisp.c"),
            Object(Unknown, "sysdolphin/baselib/psdisptev.c"),
            Object(Unknown, "sysdolphin/baselib/psappsrt.c"),
            Object(Unknown, "sysdolphin/baselib/sobjlib.c"),
            Object(Unknown, "sysdolphin/baselib/sislib.c"),
            Object(Unknown, "sysdolphin/baselib/baselib_shared_data_001.c"),
            Object(Unknown, "sysdolphin/baselib/baselib_shared_data_002.c"),
            Object(Unknown, "sysdolphin/baselib/hsd_40FF.c"),
            Object(Unknown, "sysdolphin/baselib/hsd_3A94.c"),
            Object(Unknown, "sysdolphin/baselib/hsd_3AA7.c"),
            Object(Unknown, "sysdolphin/baselib/hsd_3B27.c"),
            Object(Unknown, "sysdolphin/baselib/hsd_3B2B.c"),
            Object(Unknown, "sysdolphin/baselib/hsd_3B2E.c"),
            Object(Unknown, "sysdolphin/baselib/hsd_3B33.c"),
            Object(Unknown, "sysdolphin/baselib/hsd_3B34.c"),
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
