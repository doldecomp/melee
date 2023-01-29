import itertools
import re
from os import PathLike
from pathlib import Path
from typing import Iterable, Union

_root = Path(__file__).parents[3]
_valid_suffixes = {'.c', '.h'}

_asm_func_re = re.compile(
    r"^[\s\w\*]*?\basm\b[\s\w\*]*?"
    r"(?P<type>[\s\w\*]+)\b(?P<name>\w+)\s*\(.*?\)\s*\{.*?}",
    flags=re.MULTILINE | re.DOTALL)


def _flatmap(func, *iterable):
    return itertools.chain.from_iterable(map(func, *iterable))


def search(*src_paths: Iterable[Union[str, bytes, PathLike]]):
    result = set()
    src_paths = map(Path, src_paths)
    src_paths = _flatmap(lambda p: p.rglob('*.*'), src_paths)
    src_paths = filter(lambda p: p.suffix in _valid_suffixes, src_paths)
    path: Path
    for path in src_paths:
        text = path.read_text()
        for match in _asm_func_re.finditer(text):
            result.add(match['name'])
    return result
