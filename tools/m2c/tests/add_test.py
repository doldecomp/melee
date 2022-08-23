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
    SM64_TOOLS: Optional[Path]
    MWCC_CC: Optional[Path]


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
    SM64_TOOLS = load(
        "SM64_TOOLS",
        (
            "env variable SM64_TOOLS should point to a checkout of "
            "https://github.com/queueRAM/sm64tools/, with mipsdisasm built"
        ),
    )
    MWCC_CC = load(
        "MWCC_CC", "env variable MWCC_CC should point to a PPC cc binary (mwcceppc.exe)"
    )
    return PathsToBinaries(IDO_CC=IDO_CC, SM64_TOOLS=SM64_TOOLS, MWCC_CC=MWCC_CC)


@dataclass
class Compiler:
    name: str
    cc_command: List[str]

    def with_cc_flags(self, flags: List[str]) -> "Compiler":
        return replace(self, cc_command=self.cc_command + flags)


def get_compilers(paths: PathsToBinaries) -> List[Tuple[str, Compiler]]:
    compilers: List[Tuple[str, Compiler]] = []
    if paths.IDO_CC is not None and paths.SM64_TOOLS is not None:
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
        compilers.append(("irix-g", ido.with_cc_flags(["-g", "-mips2"])))
        compilers.append(("irix-o2", ido.with_cc_flags(["-O2", "-mips2"])))
        # compilers.append(("irix-g-mips1", ido.with_cc_flags(["-O2", "-mips1"])))
        # compilers.append(("irix-o2-mips1", ido.with_cc_flags(["-O2", "-mips1"])))
    else:
        logger.warning("IDO tools not found; skipping MIPS compilers")

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
        if paths.MWCC_CC.suffix == ".exe" and sys.platform.startswith("linux"):
            cc_command.insert(0, "/usr/bin/wine")
        mwcc = Compiler(
            name="mwcc",
            cc_command=cc_command,
        )
        compilers.append(("mwcc-o4p", mwcc.with_cc_flags(["-O4,p"])))
        # compilers.append(("mwcc-o4p-s0", mwcc.with_cc_flags(["-O4,p", "-sdata", "0", "-sdata2", "0"])))
    else:
        logger.warning("MWCC tools not found; skipping PPC compilers")

    return compilers


@dataclass
class DisassemblyInfo:
    entry_point: bytes
    disasm: bytes


def do_disassembly_step(
    temp_out_file: str, env_vars: PathsToBinaries
) -> DisassemblyInfo:
    section_lines: List[str] = subprocess.run(
        ["mips-linux-gnu-readelf", "-S", temp_out_file],
        stdout=subprocess.PIPE,
        encoding="utf-8",
    ).stdout.split("\n")

    header_lines: List[bytes] = subprocess.run(
        ["mips-linux-gnu-readelf", "-h", temp_out_file], stdout=subprocess.PIPE
    ).stdout.split(b"\n")

    entry_point: bytes = b""
    for line in header_lines:
        if b"Entry" in line:
            entry_point = line.split(b" ")[-1]
            break
    if not entry_point:
        raise Exception("no entry point found in ELF file")

    for section_line in section_lines:
        if " .text" not in section_line:
            continue
        addr = "0x" + section_line[42:][:7]
        index = "0x" + section_line[51:][:5]
        size = "0x" + section_line[58:][:5]
        break
    else:
        raise Exception("missing .text section in ELF file")

    arg = f"{addr}:{index}+{size}"
    entry_point_str = entry_point.decode("utf-8", "replace")
    logger.debug(
        f"Calling mipsdisasm with arg {arg} and entry point {entry_point_str}..."
    )
    assert env_vars.SM64_TOOLS is not None
    final_asm = subprocess.run(
        [env_vars.SM64_TOOLS / "mipsdisasm", temp_out_file, arg],
        stdout=subprocess.PIPE,
    ).stdout

    if final_asm is None:
        raise Exception("mipsdisasm didn't output anything")

    return DisassemblyInfo(entry_point, final_asm)


def do_linker_step(temp_out_file: str, temp_o_file: str) -> None:
    subprocess.run(
        ["mips-linux-gnu-ld", "-o", temp_out_file, temp_o_file, "-e", "test"]
    )


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


def do_fix_lohi_step(disasm_info: DisassemblyInfo) -> bytes:
    logger.debug("Fixing %lo and %hi macros...")

    def replace_last(s: bytes, a: bytes, b: bytes) -> bytes:
        return b.join(s.rsplit(a, 1))

    output: List[bytes] = []
    waiting_hi: Dict[bytes, Tuple[int, int, bytes]] = {}
    for line in disasm_info.disasm.split(b"\n"):
        line = line.strip()
        if (disasm_info.entry_point + b" ")[2:].upper() in line:
            output.append(b"glabel test")

        index = len(output)
        if line.startswith(b"func"):
            line = b"glabel " + line[:-1]
        elif b"lui" in line:
            reg, imm_hex = line.split(b" ")[-2::]
            imm = int(imm_hex, 0)
            if 0x10 <= imm < 0x1000:  # modestly large lui is probably a pointer
                waiting_hi[reg[:-1]] = (index, imm, imm_hex)
        else:
            lo_regs = [reg for reg in waiting_hi.keys() if reg in line]
            if lo_regs and b"0x" in line:
                lo_reg = lo_regs[0]
                hi_ind, hi_imm, hi_imm_hex = waiting_hi[lo_reg]
                lo_imm_hex = line.split(b" ")[-1].split(b"(")[0]
                lo_imm = int(lo_imm_hex, 0)
                if lo_imm >= 0x8000:
                    lo_imm -= 0x10000
                sym = b"D_" + bytes(hex((hi_imm << 16) + lo_imm)[2:].upper(), "utf-8")
                line = replace_last(line, lo_imm_hex, b"%lo(" + sym + b")")
                output[hi_ind] = replace_last(
                    output[hi_ind], hi_imm_hex, b"%hi(" + sym + b")"
                )
                del waiting_hi[lo_reg]
        output.append(line)
    return b"\n".join(output)


def irix_compile(
    in_file: Path, out_file: Path, env_vars: PathsToBinaries, compiler: Compiler
) -> None:
    flags_str = " ".join(compiler.cc_command)
    logger.info(f"Compiling {in_file} to {out_file} using: {flags_str}")
    with ExitStack() as stack:
        temp_o_file = stack.enter_context(NamedTemporaryFile(suffix=".o")).name
        temp_out_file = stack.enter_context(NamedTemporaryFile(suffix=".out")).name
        logger.debug(f"Compiling and linking {in_file} using: {flags_str}")
        do_compilation_step(temp_o_file, str(in_file), compiler)
        do_linker_step(temp_out_file, temp_o_file)
        disasm_info = do_disassembly_step(temp_out_file, env_vars)
        final_asm = do_fix_lohi_step(disasm_info)
    out_file.write_bytes(final_asm)
    logger.info(f"Successfully wrote disassembly to {out_file}.")


def ppc_compile(in_file: Path, out_file: Path, compiler: Compiler) -> None:
    flags_str = " ".join(compiler.cc_command)
    logger.info(f"Compiling {in_file} to {out_file} using: {flags_str}")
    with NamedTemporaryFile(suffix=".o") as temp_o_file:
        logger.debug(f"Compiling {in_file} using: {flags_str}")
        do_compilation_step(temp_o_file.name, str(in_file), compiler)
        with open(temp_o_file.name, "rb") as o_f:
            with out_file.open("w") as out_f:
                disassemble_ppc_elf(o_f, out_f)
    logger.info(f"Successfully wrote disassembly to {out_file}.")


def add_test_from_file(
    orig_file: Path, env_vars: PathsToBinaries, compilers: List[Tuple[str, Compiler]]
) -> None:
    test_dir = orig_file.parent
    for asm_filename, compiler in compilers:
        asm_file_path = test_dir / (asm_filename + ".s")
        try:
            if compiler.name == "ido":
                irix_compile(orig_file, asm_file_path, env_vars, compiler)
            elif compiler.name == "mwcc":
                ppc_compile(orig_file, asm_file_path, compiler)

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
