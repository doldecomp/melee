import subprocess
import sys
from datetime import datetime

import utils


def make(args: list[str]) -> int:
    root = utils.get_root_path()
    cmd = ["make"] + args

    proc = subprocess.Popen(
        cmd, cwd=root, stdout=subprocess.PIPE, stderr=subprocess.PIPE
    )

    while proc.poll() is None:
        out = proc.stdout.readline()
        err = proc.stdout.readline()
        if out:
            print(out.decode(), end="")
        if err:
            print(err.decode(), end="", file=sys.stderr)

    return proc.returncode


def get_build_time() -> str:
    return datetime.now().strftime("%H:%M:%S.%f")


def run(args):
    from utils import get_build_path, get_root_path

    build_path = get_build_path()
    make_args = []

    print(f"Build started at {get_build_time()}.")

    if args.pretty:
        print("Formatting.")
        make(["format"])

    if args.clean:
        print("Cleaning.")
        make(["clean"])
    elif args.rebuild:
        print(f'Removing files matching pattern "{args.rebuild}".')
        for file in build_path.rglob(args.rebuild):
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
    result = make(make_args)

    if result != 0:
        print(f"Build failed at {get_build_time()}.")

    if args.expected:
        raise NotImplementedError()


def attach_subparser(subparsers):
    parser_build = subparsers.add_parser(
        "build", aliases=["b"], help="Build the project"
    )
    parser_build.add_argument(
        "-c",
        "--clean",
        action="store_true",
        help='"make clean" before running make',
    )
    parser_build.add_argument(
        "-r",
        "--rebuild",
        type=str,
        help="rebuild: delete *.o files matching the given pattern;"
        " -c takes priority",
    )
    parser_build.add_argument(
        "-e",
        "--expected",
        action="store_true",
        help="after a successful make run, sync build to expected/build",
    )
    parser_build.add_argument(
        "-f",
        "--frank",
        action="store_true",
        help="pass EPILOGUE_PROCESS=1 to make",
    )
    parser_build.add_argument(
        "-m",
        "--map",
        action="store_true",
        help="pass GENERATE_MAP=1 to make",
    )
    parser_build.add_argument(
        "-n",
        "--non-matching",
        action="store_true",
        help="pass NON_MATCHING=1 to make",
    )
    parser_build.add_argument(
        "-s",
        "--skip-check",
        action="store_true",
        help="pass SKIP_CHECK=1 to make",
    )
    parser_build.add_argument(
        "-x",
        "--clear",
        action="store_true",
        help="clear the console before executing this script",
    )
    parser_build.add_argument(
        "-l",
        "--log",
        action="store_true",
        help="tee output to build.log",
    )
    parser_build.add_argument(
        "-d",
        "--dump",
        action="store_true",
        help="dump the built dol to asm (requires dadosod)",
    )
    parser_build.add_argument(
        "-j",
        "--jobs",
        type=int,
        help="pass a number of threads to make",
    )
    parser_build.add_argument(
        "-p",
        "--pretty",
        action="store_true",
        help='run "make format" before running make',
    )

    parser_build.set_defaults(func=run)
