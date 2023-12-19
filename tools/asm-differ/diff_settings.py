import os
import platform
from typing import Optional


def get_exe_suffix():
    if (system := platform.system()) == "Linux":
        return ""
    elif system == "Windows":
        return ".exe"
    else:
        raise RuntimeError("Platform not recognized.")


def env(name: str, default: Optional[str] = None) -> Optional[str]:
    return os.environ.get(name, default)


def apply(config, _):
    config["baseimg"] = "expected/build/ssbm.us.1.2/main.dol"
    config["myimg"] = "build/wip/ssbm.us.1.2/main.dol"
    config["mapfile"] = "build/wip/ssbm.us.1.2/GALE01.map"
    config["source_directories"] = ["src", "asm"]
    config["arch"] = "ppc"
    config["map_format"] = "mw"
    config["build_dir"] = "build/wip/ssbm.us.1.2/src"
    config["expected_dir"] = "expected/build/ssbm.us.1.2/src"

    config["makeflags"] = [
        f"WINE={env('WINE', 'wine')}",
        "GENERATE_MAP=1",
        "WIP=1",
        "MAX_ERRORS=0",
        "WARN_ERROR=0",
        "MSG_STYLE=std",
    ]

    devkitpro = env("DEVKITPRO", "/opt/devkitpro")
    devkitppc = env("DEVKITPPC", f"{devkitpro}/devkitPPC")
    objdump = f"{devkitppc}/bin/powerpc-eabi-objdump{get_exe_suffix()}"
    config["objdump_executable"] = objdump
