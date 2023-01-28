#!/usr/bin/env python3
from pathlib import Path


def get_root_path() -> Path:
    return Path(__file__).parents[2]


def get_build_path() -> Path:
    return get_root_path() / "build"


def get_expected_path() -> Path:
    return get_root_path() / "expected"
