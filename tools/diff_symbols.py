#!/usr/bin/env python3
"""
Compare two symbol map files and report matching virtual addresses with different names.
"""

import argparse
import sys
import json
from pathlib import Path

import pyparsing as pp

# Type alias: address -> (name, fuzzy_percent)
# fuzzy_percent is always a float for JSON; for text it is None.
SymbolData = dict[int, tuple[str, float | None]]

# ---------- pyparsing grammars ----------

# symbol line: identifier = .section:0xADDRESS; ...
identifier = pp.Word(pp.alphas + "_", pp.alphanums + "_")
hex_addr = pp.Combine("0x" + pp.Word(pp.hexnums))
section = "." + pp.Word(pp.alphanums + "_")
symbol_line_grammar = (
    identifier("name")
    + pp.Suppress("=")
    + section
    + pp.Suppress(":")
    + hex_addr("address")
    + pp.restOfLine
)

# .text start line: .text       start:0x80005940 end:0x80005BB0
# Use leave_whitespace() (snake_case) instead of deprecated leaveWhitespace()
space = pp.White().leave_whitespace()
text_start_grammar = (
    pp.Literal(".text")
    + space[...]
    + "start:"
    + hex_addr("addr")
    + space[...]
    + "end:"
    + hex_addr("end")
)

# For splits.txt: file header and indented section lines
# A header line: not indented, ends with colon
file_header = (~pp.White()) + pp.Word(pp.alphas, pp.alphanums + "/._") + ":" + pp.LineEnd()
# An indented line: starts with whitespace
indented_line = pp.LineStart() + pp.White() + pp.restOfLine

# Parser for the whole file using IndentedBlock (official API)
block = pp.Group(file_header + pp.IndentedBlock(indented_line))
file_grammar = block[...] + pp.StringEnd()


def parse_text_symbols(content: str) -> SymbolData:
    label_pattern = pp.Regex(r'\btype:label\b')
    result: SymbolData = {}
    for line in content.splitlines():
        line_stripped = line.strip()
        if not line_stripped or label_pattern.search_string(line_stripped):
            continue
        try:
            parsed = symbol_line_grammar.parse_string(line_stripped, parse_all=True)
        except pp.ParseException:
            continue
        name = parsed.name
        addr = int(parsed.address, 16)
        result.setdefault(addr, (name, None))
    return result


def parse_text_units(content: str) -> SymbolData:
    result: SymbolData = {}
    try:
        parsed_blocks = file_grammar.parse_string(content, parse_all=True)
    except pp.ParseException:
        return result

    for block in parsed_blocks:
        header = block[0].strip()
        if header.startswith("Sections:"):
            continue
        indented_lines = block[1]
        for line in indented_lines:
            try:
                parsed = text_start_grammar.parse_string(line, parse_all=True)
                addr = int(parsed.addr, 16)
                if addr not in result:
                    result[addr] = (header, None)
            except pp.ParseException:
                pass
    return result


def parse_json_symbols(content: str) -> SymbolData:
    try:
        data = json.loads(content)
    except json.JSONDecodeError:
        return {}

    result: SymbolData = {}
    for unit in data.get("units", []):
        for func in unit.get("functions", []):
            metadata = func.get("metadata", {})
            addr_str = metadata.get("virtual_address")
            if not addr_str:
                continue
            try:
                addr = int(addr_str)
            except ValueError:
                continue
            name = func.get("name")
            if not name:
                continue
            fuzzy = func.get("fuzzy_match_percent")
            if fuzzy is None:
                fuzzy = 100.0
            else:
                try:
                    fuzzy = float(fuzzy)
                except (TypeError, ValueError):
                    fuzzy = 0.0
            if addr not in result:
                result[addr] = (name, fuzzy)
    return result


def parse_json_units(content: str) -> SymbolData:
    try:
        data = json.loads(content)
    except json.JSONDecodeError:
        return {}

    result: SymbolData = {}
    for unit in data.get("units", []):
        unit_name = unit.get("name")
        if not unit_name:
            continue
        sections = unit.get("sections", [])
        text_section = next((s for s in sections if s.get("name") == ".text"), None)
        if not text_section:
            continue
        metadata = text_section.get("metadata", {})
        addr_str = metadata.get("virtual_address")
        if not addr_str:
            continue
        try:
            addr = int(addr_str)
        except ValueError:
            continue
        fuzzy = unit.get("measures", {}).get("fuzzy_match_percent")
        if fuzzy is None:
            fuzzy = 100.0
        else:
            try:
                fuzzy = float(fuzzy)
            except (TypeError, ValueError):
                fuzzy = 0.0
        if addr not in result:
            result[addr] = (unit_name, fuzzy)
    return result


def parse_symbols_dispatch(
    content: str,
    *,
    text_mode: bool = False,
    unit_mode: bool = False
) -> SymbolData:
    match (text_mode, unit_mode):
        case (True, True):
            return parse_text_units(content)
        case (True, False):
            return parse_text_symbols(content)
        case (False, True):
            return parse_json_units(content)
        case (False, False):
            return parse_json_symbols(content)


def read_file_content(filename: str) -> str:
    """Read from a file or stdin if filename == '-'."""
    if filename == "-":
        return sys.stdin.read()
    try:
        return Path(filename).read_text(encoding="utf-8")
    except OSError as e:
        print(f"Error reading {filename}: {e}", file=sys.stderr)
        sys.exit(1)


def format_percent(value: float | None) -> str:
    if value is None:
        return "N/A"
    return f"{value:.2f}"


def main() -> None:
    parser = argparse.ArgumentParser(
        description=(
            "Compare two symbol map files (report.json JSON format, "
            "or text format like symbols.txt / splits.txt) and report symbols "
            "that share a virtual address but have different names."
        )
    )

    parser.add_argument("baseline", help="Baseline (old) symbol file (use '-' for stdin)")
    parser.add_argument("current", help="Current (new) symbol file (use '-' for stdin)")

    parser.add_argument(
        "-t", "--text",
        action="store_true",
        help="Input is in text format (symbols.txt for functions; splits.txt when used with -u)"
    )
    parser.add_argument(
        "-u", "--units",
        action="store_true",
        help="Compare compilation units by .text section address (works with both text and JSON)"
    )
    parser.add_argument(
        "-p", "--percent",
        choices=['none', 'eq', 'ne', 'lt', 'gt'],
        default='none',
        help="Filter by fuzzy_match_percent (current vs baseline): "
             "eq (equal), ne (not equal), lt (current < baseline), gt (current > baseline). "
             "Default 'none' shows only name differences. (JSON only)"
    )

    args = parser.parse_args()

    if args.baseline == "-" and args.current == "-":
        print("Error: both input files cannot be stdin.", file=sys.stderr)
        sys.exit(1)

    if args.percent != 'none' and args.text:
        print("Error: --percent requires JSON input (do not use --text).", file=sys.stderr)
        sys.exit(1)

    baseline_content = read_file_content(args.baseline)
    current_content = read_file_content(args.current)

    baseline_data = parse_symbols_dispatch(baseline_content, text_mode=args.text, unit_mode=args.units)
    current_data = parse_symbols_dispatch(current_content, text_mode=args.text, unit_mode=args.units)

    if args.percent != 'none':
        all_addrs = set(baseline_data.keys()) | set(current_data.keys())

        rows = []
        max_name_len = 0
        max_old_len = 0
        max_new_len = 0

        for addr in sorted(all_addrs):
            name1, _ = baseline_data.get(addr, ("", 0.0))
            name2, _ = current_data.get(addr, ("", 0.0))
            name = name2 if name2 else name1
            if not name:
                continue

            fuzzy_baseline = baseline_data.get(addr, (None, 0.0))[1] if addr in baseline_data else 0.0
            fuzzy_current = current_data.get(addr, (None, 0.0))[1] if addr in current_data else 0.0

            op = args.percent
            match op:
                case 'eq':
                    show = (fuzzy_baseline == fuzzy_current)
                case 'ne':
                    show = (fuzzy_baseline != fuzzy_current)
                case 'lt':
                    show = (fuzzy_current < fuzzy_baseline)
                case 'gt':
                    show = (fuzzy_current > fuzzy_baseline)
                case _:
                    assert False, f"Unexpected operator: {op}"

            if show:
                old_pct = format_percent(fuzzy_baseline)
                new_pct = format_percent(fuzzy_current)
                rows.append((name, old_pct, new_pct))
                max_name_len = max(max_name_len, len(name))
                max_old_len = max(max_old_len, len(old_pct))
                max_new_len = max(max_new_len, len(new_pct))

        for name, old_pct, new_pct in rows:
            print(f"{name:>{max_name_len}} | fuzzy_match  |   {old_pct:>{max_old_len}} -> {new_pct:>{max_new_len}}")
    else:
        common_addrs = set(baseline_data.keys()) & set(current_data.keys())
        for addr in sorted(common_addrs):
            name1, _ = baseline_data[addr]
            name2, _ = current_data[addr]
            if name1 != name2:
                print(f"{name1}:{name2}")


if __name__ == "__main__":
    main()
