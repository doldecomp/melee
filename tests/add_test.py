#!/usr/bin/env python3
import argparse
import logging
import os
import subprocess
import sys
from contextlib import ExitStack
from pathlib import Path
from tempfile import NamedTemporaryFile
from typing import Dict, List, Optional, Tuple
from dataclasses import dataclass, field, replace
from ppc_disasm import disassemble_ppc_elf

logger = logging.getLogger(__name__)


def set_up_logging(debug: bool) -> None:
    logging.basicConfig(
        format="[%(levelname)s] %(message)s",
        level=logging.DEBUG if debug else logging.INFO,
    )


@dataclass
class PathsToBinaries:
    IDO_CC: Optional[Path]
    MWCC_CC: Optional[Path]
    WINE: Optional[Path]


def get_environment_variables() -> PathsToBinaries:
    def load(env_var_name: str, error_message: str) -> Optional[Path]:
        env_var = os.environ.get(env_var_name)
        if env_var is None:
            logger.error(error_message)
            return None
        path = Path(env_var)
        if not path.exists():
            logger.error(error_message + " (path does not exist)")
            return None
        return path

    IDO_CC = load(
        "IDO_CC",
        "env variable IDO_CC should point to recompiled IDO cc binary",
    )
    MWCC_CC = load(
        "MWCC_CC", "env variable MWCC_CC should point to a PPC cc binary (mwcceppc.exe)"
    )
    if MWCC_CC and sys.platform.startswith("linux"):
        WINE = load("WINE", "env variable WINE should point to wine or wibo binary")
    return PathsToBinaries(IDO_CC=IDO_CC, MWCC_CC=MWCC_CC, WINE=WINE)


@dataclass
class Compiler:
    name: str
    cc_command: List[str]

    def with_cc_flags(self, flags: List[str]) -> "Compiler":
        return replace(self, cc_command=self.cc_command + flags)


def get_ido_compilers(paths: PathsToBinaries) -> List[Tuple[str, Compiler]]:
    if paths.IDO_CC is not None:
        ido = Compiler(
            name="ido",
            cc_command=[
                str(paths.IDO_CC),
                "-c",
                "-Wab,-r4300_mul",
                "-non_shared",
                "-G",
                "0",
                "-Xcpluscomm",
                "-fullwarn",
                "-wlint",
                "-woff",
                "819,820,852,821,827,826",
                "-signed",
            ],
        )
        return [
            ("irix-g", ido.with_cc_flags(["-g", "-mips2"])),
            ("irix-o2", ido.with_cc_flags(["-O2", "-mips2"])),
            # ("irix-g-mips1", ido.with_cc_flags(["-O2", "-mips1"]))
            # ("irix-o2-mips1", ido.with_cc_flags(["-O2", "-mips1"]))
        ]
    logger.warning("IDO tools not found; skipping MIPS compilers")
    return []


def get_mwcc_compilers(paths: PathsToBinaries) -> List[Tuple[str, Compiler]]:
    if paths.MWCC_CC is not None:
        cc_command = [
            str(paths.MWCC_CC),
            "-c",
            "-Cpp_exceptions",
            "off",
            "-proc",
            "gekko",
            "-fp",
            "hard",
            "-enum",
            "int",
            "-nodefaults",
        ]
        ok = True
        if paths.MWCC_CC.suffix == ".exe" and sys.platform.startswith("linux"):
            if paths.WINE:
                cc_command.insert(0, str(paths.WINE))
            else:
                ok = False
        if ok:
            mwcc = Compiler(
                name="mwcc",
                cc_command=cc_command,
            )
            return [
                ("mwcc-o4p", mwcc.with_cc_flags(["-O4,p"])),
                # ("mwcc-o4p-s0", mwcc.with_cc_flags(["-O4,p", "-sdata", "0", "-sdata2", "0"]))
            ]
    logger.warning("MWCC tools not found; skipping PPC compilers")
    return []


def get_compilers(paths: PathsToBinaries) -> List[Tuple[str, Compiler]]:
    compilers: List[Tuple[str, Compiler]] = []
    compilers.extend(get_ido_compilers(paths))
    compilers.extend(get_mwcc_compilers(paths))
    return compilers


def disassemble_mips_elf(temp_out_file: str) -> bytes:
    return subprocess.run(
        [
            sys.executable,
            "-m",
            "spimdisasm.elfObjDisasm",
            "--Mreg-names",
            "o32",
            "--quiet",
            temp_out_file,
            "-",
        ],
        stdout=subprocess.PIPE,
        check=True,
    ).stdout


def do_compilation_step(
    temp_o_file: str,
    in_file: str,
    compiler: Compiler,
) -> None:
    args = compiler.cc_command + [
        "-o",
        temp_o_file,
        in_file,
    ]
    subprocess.run(args)


def run_compile(in_file: Path, out_file: Path, compiler: Compiler) -> None:
    flags_str = " ".join(compiler.cc_command)
    logger.info(f"Compiling {in_file} to {out_file} using: {flags_str}")
    with NamedTemporaryFile(suffix=".o") as temp_o_file:
        logger.debug(f"Compiling {in_file} using: {flags_str}")
        do_compilation_step(temp_o_file.name, str(in_file), compiler)
        if compiler.name == "ido":
            final_asm = disassemble_mips_elf(temp_o_file.name)
            out_file.write_bytes(final_asm)
        elif compiler.name == "mwcc":
            with open(temp_o_file.name, "rb") as o_f:
                with out_file.open("w") as out_f:
                    disassemble_ppc_elf(o_f, out_f)
        else:
            assert False, compiler.name
    logger.info(f"Successfully wrote disassembly to {out_file}.")


def add_test_from_file(
    orig_file: Path, env_vars: PathsToBinaries, compilers: List[Tuple[str, Compiler]]
) -> None:
    test_dir = orig_file.parent
    for asm_filename, compiler in compilers:
        asm_file_path = test_dir / (asm_filename + ".s")
        try:
            run_compile(orig_file, asm_file_path, compiler)
            if compiler.name == "mwcc":
                # If the flags file doesn't exist, initialize it with the correct --target
                ppc_flags = test_dir / (asm_filename + "-flags.txt")
                if not ppc_flags.exists():
                    ppc_flags.write_text("--target ppc-mwcc-c\n")
        except Exception:
            logger.exception(f"Failed to compile {asm_file_path}")


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Add or update end-to-end decompiler tests."
    )
    parser.add_argument(
        "files",
        help=(
            "Files containing C code to compile (then decompile). "
            "Each one must have a path of the form "
            "`tests/end_to_end/TEST_NAME/orig.c`."
        ),
        nargs="+",
    )
    parser.add_argument(
        "--debug", dest="debug", help="print debug info", action="store_true"
    )

    args = parser.parse_args()
    set_up_logging(args.debug)

    env_vars = get_environment_variables()
    compilers = get_compilers(env_vars)
    if not compilers:
        return 2

    for orig_filename in args.files:
        orig_file = Path(orig_filename).resolve()
        if not orig_file.is_file():
            logger.error(f"{orig_file} does not exist. Skipping.")
            continue
        expected_c_file = (
            Path(__file__).parent / "end_to_end" / orig_file.parent.name / "orig.c"
        ).resolve()
        expected_cpp_file = expected_c_file.with_suffix(".cpp")
        if orig_file != expected_c_file and orig_file != expected_cpp_file:
            logger.error(
                f"`{orig_file}` does not have a path of the form `{expected_c_file}` or `{expected_cpp_file}`! Skipping."
            )
            continue
        add_test_from_file(orig_file, env_vars, compilers)

    return 0


if __name__ == "__main__":
    sys.exit(main())
