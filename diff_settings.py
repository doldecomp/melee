import os
import platform


def get_exe_suffix():
    if (system := platform.system()) == 'Linux':
        return ''
    elif system == 'Windows':
        return '.exe'
    else:
        raise "Platform not recognized."


def apply(config, args):
    config["baseimg"] = "expected/build/ssbm.us.1.2/main.dol"
    config["myimg"] = "build/ssbm.us.1.2/main.dol"
    config["mapfile"] = "build/ssbm.us.1.2/GALE01.map"
    config["source_directories"] = ["src", "include", "asm"]
    config["arch"] = "ppc"
    config["map_format"] = "mw" # gnu, mw, ms
    config["build_dir"] = "build/ssbm.us.1.2/src" # only needed for mw and ms map format
    # config["makeflags"] = []
    config["objdump_executable"] = f"{os.environ['DEVKITPRO']}/devkitPPC/bin/powerpc-eabi-objdump{get_exe_suffix()}"
