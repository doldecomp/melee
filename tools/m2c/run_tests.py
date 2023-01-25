#!/usr/bin/env python3
import argparse
import contextlib
from dataclasses import dataclass, field
import difflib
import io
import logging
import multiprocessing
import re
import shlex
import sys
from coverage import Coverage  # type: ignore
from pathlib import Path
from typing import Any, Iterator, List, Optional, Pattern, Tuple

from m2c.options import Options

CRASH_STRING = "CRASHED\n"

PATH_FLAGS = {"--context", "--incbin-dir"}


@dataclass(frozen=True)
class TestOptions:
    should_overwrite: bool
    diff_context: int
    filter_re: Pattern[str]
    fraction: Optional[int] = None
    parallel: Optional[int] = None
    extra_flags: List[str] = field(default_factory=list)
    coverage: Any = None


@dataclass(frozen=True, order=True)
class TestCase:
    name: str
    asm_file: Path
    output_file: Path
    brief_crashes: bool = True
    flags_path: Optional[Path] = None
    flags: List[str] = field(default_factory=list)


def set_up_logging(debug: bool) -> None:
    logging.basicConfig(
        format="[%(levelname)s] %(message)s",
        level=logging.DEBUG if debug else logging.INFO,
    )


def get_test_flags(flags_path: Path) -> List[str]:
    if not flags_path.is_file():
        return []

    flags_str = flags_path.read_text()
    flags_list = shlex.split(flags_str)
    for i, flag in enumerate(flags_list):
        if flag not in PATH_FLAGS:
            continue
        if i + 1 >= len(flags_list):
            raise Exception(f"{flags_path} contains {flag} without argument")
        flags_list[i + 1] = str(flags_path.parent / flags_list[i + 1])

    return flags_list


def decompile_and_compare(
    test_case: TestCase, test_options: TestOptions
) -> Tuple[Optional[bool], str]:
    # This import is deferred so it can be profiled by the coverage tool
    from m2c.main import parse_flags

    logging.debug(
        f"Decompiling {test_case.asm_file}"
        + (f" into {test_case.output_file}" if test_options.should_overwrite else "")
    )
    try:
        original_contents = test_case.output_file.read_text()
    except FileNotFoundError:
        if not test_options.should_overwrite:
            logging.error(f"{test_case.output_file} does not exist. Skipping.")
            return None, f"{test_case.output_file} does not exist. Skippping."
        original_contents = "(file did not exist)"

    test_flags = ["--sanitize-tracebacks", "--stop-on-error"]
    test_flags.extend(test_case.flags)
    if test_case.flags_path is not None:
        test_flags.extend(get_test_flags(test_case.flags_path))
    test_flags.append(str(test_case.asm_file))
    test_flags.extend(test_options.extra_flags)
    options = parse_flags(test_flags)

    final_contents = decompile_and_capture_output(options, test_case.brief_crashes)

    if test_options.should_overwrite:
        test_case.output_file.parent.mkdir(parents=True, exist_ok=True)
        test_case.output_file.write_text(final_contents)

    changed = final_contents != original_contents
    if changed:
        return False, "\n".join(
            [
                f"Output of {test_case.asm_file} changed! Diff:",
                *difflib.unified_diff(
                    original_contents.splitlines(),
                    final_contents.splitlines(),
                    n=test_options.diff_context,
                ),
            ]
        )
    return True, ""


def decompile_and_capture_output(options: Options, brief_crashes: bool) -> str:
    # This import is deferred so it can be profiled by the coverage tool
    from m2c.main import run as decompile

    out_string = io.StringIO()
    with contextlib.redirect_stdout(out_string):
        returncode = decompile(options)
    out_text = out_string.getvalue()
    # Rewrite paths in the output to be relative (e.g. in tracebacks)
    out_text = out_text.replace(str(Path(__file__).parent), ".")
    if returncode == 0:
        return out_text
    else:
        if brief_crashes:
            return CRASH_STRING
        else:
            return f"{CRASH_STRING}\n{out_text}"


def create_e2e_tests(
    e2e_top_dir: Path,
    e2e_test_path: Path,
) -> List[TestCase]:

    cases: List[TestCase] = []
    for asm_file in e2e_test_path.glob("*.s"):
        output_file = asm_file.parent.joinpath(asm_file.stem + "-out.c")
        flags_path = asm_file.parent.joinpath(asm_file.stem + "-flags.txt")
        name = f"e2e:{asm_file.relative_to(e2e_top_dir)}"

        cases.append(
            TestCase(
                name=name,
                asm_file=asm_file,
                output_file=output_file,
                brief_crashes=True,
                flags_path=flags_path,
                flags=["--function", "test"],
            )
        )
    cases.sort()
    return cases


def find_tests_basic(asm_dir: Path) -> Iterator[List[Path]]:
    # This has been tested with doldecomp projects for SMS, Melee, and SMB1
    for asm_file in asm_dir.rglob("*.s"):
        yield [asm_file]


def find_tests_oot(asm_dir: Path) -> Iterator[List[Path]]:
    rodata_suffixes = [".rodata.s", ".rodata2.s"]
    for asm_file in asm_dir.rglob("*.s"):
        # Skip .rodata files
        asm_name = asm_file.name
        if any(asm_name.endswith(s) for s in rodata_suffixes):
            continue
        path_list = [asm_file]

        # Check for .rodata in the same directory
        for suffix in rodata_suffixes:
            path = asm_file.parent / asm_name.replace(".s", suffix)
            if path.exists():
                path_list.append(path)

        yield path_list


def find_tests_mm(asm_dir: Path) -> Iterator[List[Path]]:
    for asm_file in asm_dir.rglob("*.text.s"):
        path_list = [asm_file]

        # Find .data/.rodata/.bss files in their data directory
        data_path = Path(
            str(asm_file).replace("/asm/overlays/", "/data/").replace("/asm/", "/data/")
        ).parent
        for f in data_path.glob("*.s"):
            path_list.append(f)

        yield path_list


def find_tests_splat(asm_dir: Path) -> Iterator[List[Path]]:
    # This has only been tested with Paper Mario, but should work with other splat projects
    for asm_file in (asm_dir / "nonmatchings").rglob("*.s"):
        path_list = [asm_file]

        # Find .data/.rodata/.bss files in their data directory
        data_path = Path(
            str(asm_file).replace("/nonmatchings/", "/data/")
        ).parent.parent
        for f in data_path.glob("*.s"):
            path_list.append(f)

        yield path_list


def create_project_tests(
    base_dir: Path,
    output_dir: Path,
    context_file: Optional[Path],
    name_prefix: str,
) -> List[TestCase]:
    cases: List[TestCase] = []
    asm_dir = base_dir / "asm"
    if "oot" in base_dir.parts:
        file_iter = find_tests_oot(asm_dir)
        base_flags = ["--target=mips-ido-c", "--stack-structs", "--unk-underscore"]
    elif "mm" in base_dir.parts:
        file_iter = find_tests_mm(asm_dir)
        base_flags = ["--target=mips-ido-c", "--stack-structs", "--unk-underscore"]
    elif "papermario" in base_dir.parts:
        file_iter = find_tests_splat(asm_dir)
        base_flags = [
            "--target=mips-gcc-c",
            "--stack-structs",
            "--unk-underscore",
            "--pointer-style=left",
        ]
    else:
        file_iter = find_tests_basic(asm_dir)
        base_flags = [
            "--incbin-dir",
            str(base_dir),
            "--stack-structs",
            "--unk-underscore",
        ]

    for file_list in file_iter:
        if not file_list:
            continue

        flags = base_flags + ["--deterministic-vars"]
        if context_file is not None:
            flags.extend(["--context", str(context_file)])

        test_path = file_list[0].relative_to(base_dir / "asm")
        name = f"{name_prefix}:{test_path}"
        output_file = (output_dir / test_path).with_suffix(".c")

        cases.append(
            TestCase(
                name=name,
                asm_file=file_list[0],
                output_file=output_file,
                brief_crashes=False,
                flags=flags + [str(p) for p in file_list[1:]],
            )
        )
    cases.sort()
    return cases


def run_test(
    test: Tuple[TestCase, TestOptions]
) -> Tuple[TestCase, Optional[bool], str]:
    test_case, test_options = test
    if test_options.coverage:
        test_options.coverage.switch_context(test_case.name)
    did_pass, output = decompile_and_compare(test_case, test_options)
    return test_case, did_pass, output


def main(
    project_dirs: List[Tuple[Path, bool]],
    test_options: TestOptions,
) -> int:
    # Collect tests
    test_cases: List[TestCase] = []

    e2e_top_dir = Path(__file__).parent / "tests" / "end_to_end"
    for e2e_test_path in e2e_top_dir.iterdir():
        test_cases.extend(create_e2e_tests(e2e_top_dir, e2e_test_path))

    for project_dir, use_context in project_dirs:
        name_prefix = project_dir.name
        if project_dir.match("papermario/ver/us"):
            name_prefix = "papermario_us"
        elif project_dir.match("papermario/ver/jp"):
            name_prefix = "papermario_jp"

        context_file: Optional[Path] = None
        if use_context:
            name_prefix = f"{name_prefix}_ctx"
            context_file = project_dir / "ctx.c"
            if not context_file.exists():
                raise Exception(
                    f"{project_dir} tests require context file, but {context_file} does not exist"
                )

        output_dir = Path(__file__).parent / "tests" / "project" / name_prefix

        test_cases.extend(
            create_project_tests(
                project_dir,
                output_dir,
                context_file,
                name_prefix,
            )
        )

    passed, failed = 0, 0
    total = len(test_cases)
    if test_options.filter_re is not None:
        test_cases = [t for t in test_cases if test_options.filter_re.search(t.name)]
    if test_options.fraction is not None:
        test_cases = test_cases[:: test_options.fraction]
    skipped = total - len(test_cases)

    test_iterator: Iterator[Tuple[TestCase, Optional[bool], str]]
    if test_options.parallel:
        pool = multiprocessing.Pool(processes=test_options.parallel)
        test_iterator = pool.imap_unordered(
            run_test,
            ((t, test_options) for t in test_cases),
            chunksize=4,
        )
    else:
        test_iterator = (run_test((t, test_options)) for t in test_cases)

    for test_case, did_pass, output in test_iterator:
        if did_pass is None:
            logging.info(f"[SKIP] {test_case.name}")
            skipped += 1
        elif did_pass:
            logging.info(f"[PASS] {test_case.name}")
            passed += 1
        else:
            logging.info(f"[FAIL] {test_case.name}")
            failed += 1
        if output:
            logging.info(output)

    if test_options.parallel:
        pool.terminate()

    logging.info(
        f"Test summary: {passed} passed, {skipped} skipped, {failed} failed, {passed + skipped + failed} total"
    )

    if failed > 0 and not test_options.should_overwrite:
        return 1
    return 0


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Run and record end-to-end decompiler tests."
    )
    parser.add_argument(
        "--debug", dest="debug", help="print debug info", action="store_true"
    )
    parser.add_argument(
        "-j",
        "--parallel",
        metavar="N",
        dest="parallel",
        type=int,
        help=("Run tests in parallel, with this many processes."),
    )
    parser.add_argument(
        "--diff-context",
        metavar="N",
        dest="diff_context",
        default=3,
        type=int,
        help=("Number of lines of context to print with in diff output."),
    )
    parser.add_argument(
        "--overwrite",
        dest="should_overwrite",
        action="store_true",
        help=(
            "overwrite the contents of the test output files. "
            "Do this once before committing."
        ),
    )
    parser.add_argument(
        "--filter",
        metavar="REGEX",
        dest="filter_re",
        type=lambda x: re.compile(x),
        help=("Only run tests matching this regular expression."),
    )
    parser.add_argument(
        "-K",
        "--fraction",
        metavar="N",
        dest="fraction",
        type=int,
        help=("Only run 1 in every N tests."),
    )
    parser.add_argument(
        "--project",
        metavar="DIR",
        dest="project_dirs",
        action="append",
        default=[],
        type=lambda p: (Path(p), False),
        help=(
            "Run tests on the asm files from a decompilation project. "
            "The zeldaret/oot and zeldaret/mm projects are supported. "
            "Can be specified multiple times."
        ),
    )
    parser.add_argument(
        "extra_flags",
        nargs=argparse.REMAINDER,
        help="Additional arguments to pass to m2c. Use `--` to separate them from run_tests's flags.",
    )
    parser.add_argument(
        "--project-with-context",
        metavar="DIR",
        dest="project_dirs",
        action="append",
        default=[],
        type=lambda p: (Path(p), True),
        help=(
            "Same as --project, but use the C context file `ctx.c` "
            "from the base directory. "
            "Can be specified multiple times."
        ),
    )
    cov_group = parser.add_argument_group("Coverage")
    cov_group.add_argument(
        "--coverage",
        dest="coverage",
        action="store_true",
        help="Compute code coverage for tests",
    )
    cov_group.add_argument(
        "--coverage-html",
        metavar="DIR",
        dest="coverage_html",
        help="Output coverage HTML report to directory",
        default="htmlcov/",
    )
    cov_group.add_argument(
        "--coverage-emit-data",
        dest="coverage_emit_data",
        action="store_true",
        help="Emit a .coverage data file",
    )
    args = parser.parse_args()
    set_up_logging(args.debug)

    cov = None
    if args.coverage:
        logging.info("Computing code coverage.")
        coverage_data_file = None
        if args.coverage_emit_data:
            coverage_data_file = ".coverage"
            logging.info(f"Writing coverage data to {coverage_data_file}")
        cov = Coverage(include="src/*", data_file=coverage_data_file, branch=True)
        cov.start()

    if args.should_overwrite:
        logging.info("Overwriting test output files.")

    if "--" in args.extra_flags:
        args.extra_flags.remove("--")

    test_options = TestOptions(
        should_overwrite=args.should_overwrite,
        diff_context=args.diff_context,
        filter_re=args.filter_re,
        fraction=args.fraction,
        parallel=args.parallel,
        extra_flags=args.extra_flags,
        coverage=cov,
    )
    ret = main(args.project_dirs, test_options)

    if cov is not None:
        cov.stop()
        cov.html_report(
            directory=args.coverage_html, show_contexts=True, skip_empty=True
        )
        logging.info(f"Wrote html coverage report to {args.coverage_html}")

    sys.exit(ret)
