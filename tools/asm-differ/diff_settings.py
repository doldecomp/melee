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


# TODO gc-wii-binutils
def find_objdump() -> str:
    if (objdump := env("PPC_EABI_OBJDUMP")) is None:
        devkitpro = env("DEVKITPRO", "/opt/devkitpro")
        devkitppc = env("DEVKITPPC", f"{devkitpro}/devkitPPC")
        objdump = f"{devkitppc}/bin/powerpc-eabi-objdump{get_exe_suffix()}"

    return objdump


def apply(config, _):
    config["baseimg"] = "orig/GALE01/sys/main.dol"
    config["myimg"] = "build/GALE01/main.dol"
    config["mapfile"] = "build/GALE01/main.elf.MAP"
    config["source_directories"] = ["src", "asm"]
    config["arch"] = "ppc"
    config["map_format"] = "mw"
    config["build_dir"] = "build/GALE01/src"
    config["expected_dir"] = "build/GALE01/obj"
    config["make_command"] = ["ninja"]

    config["objdump_executable"] = find_objdump()
