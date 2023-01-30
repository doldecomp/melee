#!/usr/bin/env python3
import os
import shutil
import subprocess
import sys
from datetime import datetime
from pathlib import Path
from typing import IO, Union

import utils


def run_proc(
    cmd: str,
    args: list[str],
    out_log: Union[IO[str], None] = None,
    err_log: Union[IO[str], None] = None,
) -> int:
    def print_line(b: bytes, log: Union[IO[str], None]):
        print(b.decode(), end="")
        if log is not None:
            log.write(b.decode().rstrip() + os.linesep)

    root = utils.get_root_path()

    proc = subprocess.Popen(
        [cmd] + args, cwd=root, stdout=subprocess.PIPE, stderr=subprocess.PIPE
    )

    while proc.poll() is None:
        out = proc.stdout.readline()
        err = proc.stdout.readline()
        if out:
            print_line(out, out_log)
        if err:
            print_line(err, err_log)

    return proc.returncode


def get_build_time() -> str:
    return datetime.now().strftime("%H:%M:%S.%f")


def run(args):
    root_path = utils.get_root_path()
    build_path = utils.get_build_path()
    make_cmd = "make"
    dadosod_cmd = "dadosod"
    make_args = []

    if args.clear:
        clear_cmd = "cls" if sys.platform == "win32" else "clear"
        os.system(clear_cmd)

    if args.log:
        out_log = root_path.joinpath("build.log").open("a")
        err_log = root_path.joinpath("build_errors.log").open("a")
    else:
        out_log = None
        err_log = None

    def run_proc_logged(cmd, *args) -> int:
        return run_proc(cmd, list(args), out_log, err_log)

    def sync_dir(src: Path, dst: Path):
        dst.mkdir(exist_ok=True, parents=True)
        return run_proc_logged("rsync", "-a", "--delete", str(src), str(dst))

    print(f"Build started at {get_build_time()}.")

    if args.pretty:
        print("Formatting.")
        run_proc_logged(make_cmd, "format")

    if args.clean:
        print("Cleaning.")
        run_proc_logged(make_cmd, "clean")
    elif args.rebuild:
        print(f'Removing object files matching pattern "{args.rebuild}".')
        for file in build_path.rglob(args.rebuild):
            if file.suffix != ".o":
                continue

            print(f"Removing {file.relative_to(build_path)}")
            if file.is_dir():
                file.rmdir()
            elif file.is_file():
                file.unlink()
            else:
                raise ValueError("Unknown pathlib.Path type")

    if args.non_matching:
        make_args += ["NON_MATCHING=1"]
    elif args.skip_check:
        make_args += ["SKIP_CHECK=1"]

    if args.frank:
        make_args += ["EPILOGUE_PROCESS=1"]

    if args.map:
        make_args += ["GENERATE_MAP=1"]

    if args.jobs:
        make_args += ["-j", str(args.jobs)]

    print(f"Running make with {' '.join(make_args)}.")
    result = run_proc_logged(make_cmd, *make_args)
    succeeded = result == 0

    map_path = build_path / "ssbm.us.1.2/GALE01.map"
    if map_path.exists():
        # TODO Proper module
        sys.path.insert(0, str(root_path.joinpath("tools").resolve()))
        from parse_map import main as parse_map

        print("Parsing map.")
        parse_map()

    dump_path = None
    if args.dump:
        dump_path = root_path / "dump"
        print(f"Dumping main.dol to {dump_path.relative_to(root_path)}.")
        shutil.rmtree(dump_path, ignore_errors=True)
        dump_path.mkdir(parents=True)
        dol_path = build_path / "ssbm.us.1.2/main.dol"

        # TODO: Get from parse_map module
        map_csv_path = build_path / "map.csv"

        run_proc_logged(
            dadosod_cmd,
            "dol",
            str(dol_path),
            "-m",
            str(map_csv_path),
            "-o",
            str(dump_path),
        )

    if args.expected and succeeded:
        expected_path = utils.get_expected_path()
        print("Syncing build to expected.")
        sync_dir(build_path, expected_path)

        if args.dump and dump_path is not None:
            print("Syncing dump to expected.")
            sync_dir(dump_path, expected_path)

    print(
        f"Build {'succeeded' if succeeded else 'failed'} at {get_build_time()}."
    )

    exit(result)


def attach_subparser(subparsers):
    parser = subparsers.add_parser(
        "build", aliases=["b"], help="build the project"
    )
    parser.add_argument(
        "-c",
        "--clean",
        action="store_true",
        help='"make clean" before running make',
    )
    parser.add_argument(
        "-r",
        "--rebuild",
        type=str,
        help="delete *.o files matching the given pattern;"
        " -c takes priority",
    )
    parser.add_argument(
        "-e",
        "--expected",
        action="store_true",
        help="after a successful make run, sync build to expected/build",
    )
    parser.add_argument(
        "-f",
        "--frank",
        action="store_true",
        help="pass EPILOGUE_PROCESS=1 to make",
    )
    parser.add_argument(
        "-m",
        "--map",
        action="store_true",
        help="pass GENERATE_MAP=1 to make",
    )
    parser.add_argument(
        "-n",
        "--non-matching",
        action="store_true",
        help="pass NON_MATCHING=1 to make",
    )
    parser.add_argument(
        "-s",
        "--skip-check",
        action="store_true",
        help="pass SKIP_CHECK=1 to make",
    )
    parser.add_argument(
        "-x",
        "--clear",
        action="store_true",
        help="clear the console before executing this script",
    )
    parser.add_argument(
        "-l",
        "--log",
        action="store_true",
        help="tee output to build.log",
    )
    parser.add_argument(
        "-d",
        "--dump",
        action="store_true",
        help="dump the built dol to asm (requires dadosod)",
    )
    parser.add_argument(
        "-j",
        "--jobs",
        type=int,
        help="pass a number of threads to make",
    )
    parser.add_argument(
        "-p",
        "--pretty",
        action="store_true",
        help='run "make format" before running make',
    )

    parser.set_defaults(func=run)
