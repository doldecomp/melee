import csv
import json
import re
from functools import reduce
from pathlib import Path
from re import Match
from typing import Callable, Any


def flat_map(f, xs):
    return reduce(lambda a, b: a + b, map(f, xs))


root = Path(__file__) / '../../'

src_key_re = re.compile(r"^\w+\.[chis]$")
src_paths = [root / 'src', root / 'asm', root / 'include']
src_paths = flat_map(lambda p: list(p.rglob('*.*')), src_paths)
src_paths = map(lambda p: (p.name, p.relative_to(root).as_posix()), src_paths)
src_paths = filter(lambda pair: src_key_re.match(pair[0]), src_paths)
src_paths = dict(src_paths)

map_path = root / 'build/ssbm.us.1.2/GALE01.map'

section_re = re.compile(r"^\.(\w+) section layout$")

symbol_re = re.compile(
    r"^  (?P<local_addr>[\da-f]{8}) (?P<size>[\da-f]{6})"
    r" (?P<global_addr>[\da-f]{8})(?:  (?P<alignment>\d))?"
    r" (?P<name>@?[\.\w]+)(?: \(entry of (?P<parent>@?[\.\w]+)\))?"
    r" \t(?P<filename>@?[\w \.]+)\.o $")

relative_label_re = re.compile(r"@(\d+)")


def match_to_dict(match: Match, section: str):
    result = {}
    group_dict = match.groupdict()

    def put(key: str, conversion: Callable[[str], Any], result_key=None, default=None):
        if result_key is None:
            result_key = key
        if (value := group_dict.get(key)) is not None:
            if (value := conversion(value)) is not None:
                result[result_key] = value
                return

        if default is not None:
            result[result_key] = default

    def put_int(key: str, base: int = 16, result_key=None, default=None):
        put(key, lambda s: int(s, base), result_key, default)

    def put_str(key: str, result_key=None, default=None):
        put(key, lambda s: s, result_key, default)

    def process_name(name: str):
        if m := relative_label_re.match(name):
            return f'{section}_{m[1]}'
        return name

    put_int('local_addr', result_key='localAddress')
    put_int('size', default=0)
    put_int('global_addr', result_key='globalAddress')
    put_int('alignment', 10, default=1)
    put('name', process_name)
    put_str('parent')
    put('filename', lambda s: src_paths.get(s), result_key='translationUnit')
    return result


def main():
    map_json = {}
    with open(map_path, 'r') as f:
        for line in f:
            if match := section_re.match(line):
                section = match[1]
            elif match := symbol_re.match(line):
                entry = match_to_dict(match, section)
                map_json[f"{entry['globalAddress']:08X}"] = entry

    with open(root / 'build/map.csv', 'w', newline='') as f:
        writer = csv.DictWriter(f, fieldnames=[
            'localAddress', 'size', 'globalAddress', 'alignment', 'name', 'parent', 'translationUnit'
        ])
        writer.writeheader()
        for entry in map_json.values():
            writer.writerow(entry)


if __name__ == "__main__":
    main()
