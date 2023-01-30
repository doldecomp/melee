#!/usr/bin/env python3
from pathlib import Path
from typing import Generator


def get_root_path() -> Path:
    return Path(__file__).parents[2]


def get_build_path() -> Path:
    return get_root_path() / "build"


def get_expected_path() -> Path:
    return get_root_path() / "expected"


def get_src_path() -> Path:
    return get_root_path() / "src"


def get_asm_path() -> Path:
    return get_root_path() / "asm"


def get_src_files() -> Generator[Path, None, None]:
    return get_src_path().rglob("*.c")


def get_asm_files() -> Generator[Path, None, None]:
    return get_asm_path().rglob("*.s")
