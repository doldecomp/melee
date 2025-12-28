#!/usr/bin/env python3
"""
Analyzes symbol dependencies between object files to find "leaf" NonMatching files.

Leaf files are NonMatching files that no other NonMatching file depends on,
meaning they can potentially be converted to Matching without breaking the build.

Usage:
    python tools/dep_graph.py                    # Show leaf NonMatching files
    python tools/dep_graph.py --all              # Show full dependency info
    python tools/dep_graph.py --deps FILE        # Show what FILE depends on
    python tools/dep_graph.py --rdeps FILE       # Show what depends on FILE
    python tools/dep_graph.py --cycles           # Detect dependency cycles
    python tools/dep_graph.py --chain            # Show unlock chains
"""

import argparse
import json
import re
import shutil
import subprocess
import sys
from collections import defaultdict
from dataclasses import dataclass, field
from pathlib import Path
from typing import Literal

ROOT = Path(__file__).parents[1]
BUILD_DIR = ROOT / "build" / "GALE01"
REPORT_PATH = ROOT / "build" / "GALE01" / "report.json"

# Match Object() declarations in configure.py
OBJECT_PATTERN = re.compile(
    r'Object\s*\(\s*(Matching|NonMatching|Equivalent|MatchingFor[^)]*)\s*,\s*"([^"]+)"'
)


@dataclass
class ObjectFile:
    path: str
    status: Literal["Matching", "NonMatching", "Equivalent"]
    defined_symbols: set[str] = field(default_factory=set)
    undefined_symbols: set[str] = field(default_factory=set)
    function_count: int = 0
    match_percent: float = 0.0


def find_nm_tool() -> str:
    """Find the best nm tool to use for PowerPC ELF files."""
    # Prefer powerpc-eabi-nm if available
    ppc_nm = shutil.which("powerpc-eabi-nm")
    if ppc_nm:
        return ppc_nm

    # Check devkitPPC
    devkit_nm = Path("/opt/devkitpro/devkitPPC/bin/powerpc-eabi-nm")
    if devkit_nm.exists():
        return str(devkit_nm)

    # Fall back to system nm (llvm-nm on macOS works with PowerPC ELF)
    system_nm = shutil.which("nm")
    if system_nm:
        return system_nm

    raise RuntimeError("No suitable nm tool found. Install powerpc-eabi-nm or ensure nm is in PATH.")


def parse_configure() -> dict[str, ObjectFile]:
    """Parse configure.py to get object file status."""
    objects: dict[str, ObjectFile] = {}

    configure_path = ROOT / "configure.py"
    content = configure_path.read_text()

    for match in OBJECT_PATTERN.finditer(content):
        status_str, path = match.groups()

        # Normalize status
        if status_str == "Matching" or status_str.startswith("MatchingFor"):
            status = "Matching"
        elif status_str == "NonMatching":
            status = "NonMatching"
        else:
            status = "Equivalent"

        objects[path] = ObjectFile(path=path, status=status)

    return objects


def load_report() -> dict:
    """Load report.json if it exists."""
    if REPORT_PATH.exists():
        with open(REPORT_PATH) as f:
            return json.load(f)
    return {}


def get_object_path(src_path: str) -> Path:
    """Convert source path to object file path."""
    return BUILD_DIR / "src" / Path(src_path).with_suffix(".o")


def analyze_symbols(nm_tool: str, obj_path: Path) -> tuple[set[str], set[str]]:
    """Get defined and undefined symbols from an object file using nm."""
    defined: set[str] = set()
    undefined: set[str] = set()

    if not obj_path.exists():
        return defined, undefined

    try:
        # Use POSIX format (-P) for consistent parsing: name type [value] [size]
        result = subprocess.run(
            [nm_tool, "-P", str(obj_path)],
            capture_output=True,
            text=True,
            check=True,
        )

        for line in result.stdout.splitlines():
            parts = line.split()
            if len(parts) >= 2:
                name = parts[0]
                sym_type = parts[1]

                if sym_type == "U":
                    # Undefined symbol
                    undefined.add(name)
                elif sym_type in "TtDdBbCcRrVvWwSs":
                    # Defined symbol (various types)
                    defined.add(name)
    except subprocess.CalledProcessError:
        # Try without -P flag as fallback
        try:
            result = subprocess.run(
                [nm_tool, str(obj_path)],
                capture_output=True,
                text=True,
                check=True,
            )

            for line in result.stdout.splitlines():
                parts = line.split()
                if len(parts) >= 2:
                    # Format: [address] type name  OR  type name (for undefined)
                    if parts[0] == "U":
                        undefined.add(parts[1])
                    elif len(parts) >= 3 and parts[1] in "TtDdBbCcRrVvWwSs":
                        defined.add(parts[2])
                    elif len(parts) == 2 and parts[0] in "TtDdBbCcRrVvWwSs":
                        defined.add(parts[1])
        except (subprocess.CalledProcessError, FileNotFoundError):
            pass
    except FileNotFoundError:
        print(f"Error: nm tool not found: {nm_tool}", file=sys.stderr)
        sys.exit(1)

    return defined, undefined


def enrich_from_report(objects: dict[str, ObjectFile], report: dict) -> None:
    """Add function count and match percentage from report.json."""
    units = report.get("units", [])
    for unit in units:
        unit_name = unit.get("name", "")
        # Strip "main/" prefix if present
        if unit_name.startswith("main/"):
            unit_name = unit_name[5:]

        # Find matching object
        for path, obj in objects.items():
            if path == unit_name or path.replace(".c", "") == unit_name:
                functions = unit.get("functions", [])
                obj.function_count = len(functions)
                if functions:
                    total_match = sum(
                        float(f.get("fuzzy_match_percent", 0)) for f in functions
                    )
                    obj.match_percent = total_match / len(functions)
                break


def build_dependency_graph(
    objects: dict[str, ObjectFile],
    nm_tool: str,
) -> tuple[dict[str, set[str]], dict[str, set[str]]]:
    """
    Build forward and reverse dependency graphs.

    Returns:
        deps: file -> set of files it depends on
        rdeps: file -> set of files that depend on it
    """
    symbol_to_file: dict[str, str] = {}

    print("Analyzing object files...", file=sys.stderr)
    for path, obj in objects.items():
        obj_path = get_object_path(path)
        defined, undefined = analyze_symbols(nm_tool, obj_path)
        obj.defined_symbols = defined
        obj.undefined_symbols = undefined

        for sym in defined:
            symbol_to_file[sym] = path

    # Build dependency graph
    deps: dict[str, set[str]] = defaultdict(set)
    rdeps: dict[str, set[str]] = defaultdict(set)

    for path, obj in objects.items():
        for sym in obj.undefined_symbols:
            if sym in symbol_to_file:
                dep_file = symbol_to_file[sym]
                if dep_file != path:
                    deps[path].add(dep_file)
                    rdeps[dep_file].add(path)

    return deps, rdeps


def find_leaves(
    objects: dict[str, ObjectFile],
    rdeps: dict[str, set[str]],
    include_matching: bool = False,
) -> list[tuple[str, int]]:
    """
    Find NonMatching files that no other NonMatching file depends on.

    Returns list of (path, undefined_count) tuples, sorted by undefined count.
    """
    target_status = {"NonMatching"}
    if include_matching:
        target_status.add("Matching")

    target_files = {p for p, o in objects.items() if o.status in target_status}
    non_matching = {p for p, o in objects.items() if o.status == "NonMatching"}

    leaves: list[tuple[str, int]] = []
    for path in sorted(target_files):
        if objects[path].status != "NonMatching":
            continue

        # Get files that depend on this one
        dependents = rdeps.get(path, set())
        # Filter to only NonMatching dependents
        nm_dependents = dependents & non_matching

        if not nm_dependents:
            undefined_count = len(objects[path].undefined_symbols)
            leaves.append((path, undefined_count))

    # Sort by undefined count (fewer = easier to convert)
    leaves.sort(key=lambda x: (x[1], x[0]))
    return leaves


def find_unlock_chain(
    objects: dict[str, ObjectFile],
    rdeps: dict[str, set[str]],
    max_depth: int = 3,
) -> list[tuple[str, list[str]]]:
    """
    Find files that would unlock other files when converted to Matching.

    Returns list of (file, [files_it_unlocks]) tuples.
    """
    non_matching = {p for p, o in objects.items() if o.status == "NonMatching"}

    def get_nm_dependents(path: str) -> set[str]:
        return rdeps.get(path, set()) & non_matching

    def would_become_leaf(path: str, converted: set[str]) -> bool:
        """Check if path would become a leaf if 'converted' files were Matching."""
        nm_dependents = get_nm_dependents(path) - converted
        return len(nm_dependents) == 0

    # Find files that would unlock others
    unlock_map: dict[str, list[str]] = defaultdict(list)

    for path in non_matching:
        # What files depend on this one?
        nm_dependents = get_nm_dependents(path)
        if not nm_dependents:
            continue  # Already a leaf

        # If this file were converted, which files would become leaves?
        for dependent in nm_dependents:
            if would_become_leaf(dependent, {path}):
                unlock_map[path].append(dependent)

    # Sort by number of files unlocked (most impactful first)
    result = [(path, unlocks) for path, unlocks in unlock_map.items() if unlocks]
    result.sort(key=lambda x: -len(x[1]))
    return result


def find_cycles(deps: dict[str, set[str]], max_cycles: int = 20) -> list[list[str]]:
    """Find dependency cycles using DFS. Returns at most max_cycles."""
    cycles: list[list[str]] = []
    visited: set[str] = set()
    rec_stack: set[str] = set()
    path: list[str] = []

    def dfs(node: str) -> bool:
        if len(cycles) >= max_cycles:
            return False

        visited.add(node)
        rec_stack.add(node)
        path.append(node)

        for neighbor in deps.get(node, set()):
            if neighbor not in visited:
                if dfs(neighbor):
                    return True
            elif neighbor in rec_stack:
                cycle_start = path.index(neighbor)
                cycles.append(path[cycle_start:] + [neighbor])
                if len(cycles) >= max_cycles:
                    return True

        path.pop()
        rec_stack.remove(node)
        return False

    for node in deps:
        if node not in visited:
            dfs(node)
            if len(cycles) >= max_cycles:
                break

    return cycles


def print_leaves(
    leaves: list[tuple[str, int]],
    objects: dict[str, ObjectFile],
) -> None:
    """Print leaf NonMatching files, ranked by complexity."""
    print(f"\nLeaf NonMatching files ({len(leaves)} files):")
    print("These can potentially be converted to Matching without breaking other NonMatching files.")
    print("Sorted by external symbol count (fewer = easier to convert).\n")

    for path, undefined_count in leaves:
        obj = objects[path]
        func_info = f", {obj.function_count} funcs" if obj.function_count else ""
        match_info = f", {obj.match_percent:.1f}% matched" if obj.match_percent else ""
        print(f"  {path}")
        print(f"    -> {undefined_count} external refs{func_info}{match_info}")


def print_unlock_chain(
    chain: list[tuple[str, list[str]]],
    objects: dict[str, ObjectFile],
    limit: int = 20,
) -> None:
    """Print files that would unlock other files when converted."""
    print(f"\nHigh-impact files ({min(len(chain), limit)} shown):")
    print("Converting these would make other NonMatching files become leaves.\n")

    for path, unlocks in chain[:limit]:
        obj = objects[path]
        undefined_count = len(obj.undefined_symbols)
        print(f"  {path} ({undefined_count} external refs)")
        print(f"    -> would unlock: {', '.join(unlocks)}")


def print_deps(
    path: str,
    deps: dict[str, set[str]],
    objects: dict[str, ObjectFile],
) -> None:
    """Print what a file depends on."""
    if path not in objects:
        print(f"Error: {path} not found in configure.py", file=sys.stderr)
        return

    file_deps = deps.get(path, set())
    obj = objects[path]

    print(f"\n{path} ({obj.status})")
    print(f"Depends on {len(file_deps)} files:\n")

    for dep in sorted(file_deps):
        dep_obj = objects.get(dep)
        status = dep_obj.status if dep_obj else "unknown"
        print(f"  {dep} ({status})")


def print_rdeps(
    path: str,
    rdeps: dict[str, set[str]],
    objects: dict[str, ObjectFile],
) -> None:
    """Print what depends on a file."""
    if path not in objects:
        print(f"Error: {path} not found in configure.py", file=sys.stderr)
        return

    file_rdeps = rdeps.get(path, set())
    obj = objects[path]

    print(f"\n{path} ({obj.status})")
    print(f"Depended on by {len(file_rdeps)} files:\n")

    for dep in sorted(file_rdeps):
        dep_obj = objects.get(dep)
        status = dep_obj.status if dep_obj else "unknown"
        print(f"  {dep} ({status})")


def print_all(
    objects: dict[str, ObjectFile],
    deps: dict[str, set[str]],
    rdeps: dict[str, set[str]],
) -> None:
    """Print full dependency information."""
    matching = [p for p, o in objects.items() if o.status == "Matching"]
    non_matching = [p for p, o in objects.items() if o.status == "NonMatching"]
    equivalent = [p for p, o in objects.items() if o.status == "Equivalent"]

    print(f"\nObject file summary:")
    print(f"  Matching:     {len(matching)}")
    print(f"  NonMatching:  {len(non_matching)}")
    print(f"  Equivalent:   {len(equivalent)}")
    print(f"  Total:        {len(objects)}")

    # Count cross-status dependencies
    nm_to_nm = 0
    nm_to_m = 0
    m_to_nm = 0

    for path, file_deps in deps.items():
        src_status = objects[path].status
        for dep in file_deps:
            if dep in objects:
                dst_status = objects[dep].status
                if src_status == "NonMatching" and dst_status == "NonMatching":
                    nm_to_nm += 1
                elif src_status == "NonMatching" and dst_status == "Matching":
                    nm_to_m += 1
                elif src_status == "Matching" and dst_status == "NonMatching":
                    m_to_nm += 1

    print(f"\nDependency summary:")
    print(f"  NonMatching -> NonMatching: {nm_to_nm}")
    print(f"  NonMatching -> Matching:    {nm_to_m}")
    print(f"  Matching -> NonMatching:    {m_to_nm}")


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Analyze symbol dependencies between object files.",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__,
    )
    parser.add_argument(
        "--all",
        action="store_true",
        help="Show full dependency summary",
    )
    parser.add_argument(
        "--deps",
        metavar="FILE",
        help="Show what FILE depends on",
    )
    parser.add_argument(
        "--rdeps",
        metavar="FILE",
        help="Show what depends on FILE (reverse dependencies)",
    )
    parser.add_argument(
        "--cycles",
        action="store_true",
        help="Detect and report dependency cycles (shows first 20)",
    )
    parser.add_argument(
        "--chain",
        action="store_true",
        help="Show unlock chains (files that would enable other conversions)",
    )
    parser.add_argument(
        "--matching",
        action="store_true",
        help="Include Matching files in leaf analysis",
    )
    parser.add_argument(
        "--limit",
        type=int,
        default=0,
        metavar="N",
        help="Limit output to N results (0 = unlimited)",
    )
    args = parser.parse_args()

    # Find nm tool
    try:
        nm_tool = find_nm_tool()
    except RuntimeError as e:
        print(f"Error: {e}", file=sys.stderr)
        sys.exit(1)

    # Parse configure.py
    objects = parse_configure()
    if not objects:
        print("Error: No objects found in configure.py", file=sys.stderr)
        sys.exit(1)

    # Load report.json for function counts and match percentages
    report = load_report()
    enrich_from_report(objects, report)

    # Build dependency graph
    deps, rdeps = build_dependency_graph(objects, nm_tool)

    if args.all:
        print_all(objects, deps, rdeps)
        leaves = find_leaves(objects, rdeps, args.matching)
        if args.limit > 0:
            leaves = leaves[:args.limit]
        print_leaves(leaves, objects)
    elif args.deps:
        print_deps(args.deps, deps, objects)
    elif args.rdeps:
        print_rdeps(args.rdeps, rdeps, objects)
    elif args.cycles:
        cycles = find_cycles(deps)
        if cycles:
            print(f"\nFound dependency cycles (showing first {len(cycles)}):\n")
            for i, cycle in enumerate(cycles, 1):
                print(f"  Cycle {i}: {' -> '.join(cycle)}")
        else:
            print("\nNo dependency cycles found.")
    elif args.chain:
        chain = find_unlock_chain(objects, rdeps)
        limit = args.limit if args.limit > 0 else 20
        print_unlock_chain(chain, objects, limit)
    else:
        # Default: show leaf NonMatching files
        leaves = find_leaves(objects, rdeps, args.matching)
        if args.limit > 0:
            leaves = leaves[:args.limit]
        print_leaves(leaves, objects)


if __name__ == "__main__":
    main()
