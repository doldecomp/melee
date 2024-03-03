#!/usr/bin/env python3

import git


def checkout_except(repo: git.Repo, target: str, base: str):
    common = next(iter(repo.merge_base(target, base)))
    target_files = repo.commit(base).diff(target)
    base_files = set(repo.git.diff(common, base, name_only=True).splitlines())
    for d in target_files:
        if d.a_path in base_files:
            continue

        change_type = d.change_type

        if change_type not in {"A", "D", "M", "R"}:
            raise ValueError(f"Unknown change type: {change_type}")

        if change_type in {"D", "R"}:
            repo.index.remove(d.a_path, working_tree=True)

        if change_type in {"A", "M", "R"}:
            repo.git.checkout(target, "--", d.b_path)
            repo.index.add(d.b_path)


if __name__ == "__main__":
    import sys
    import os
    import argparse

    script_name = os.path.basename(__file__)

    parser = argparse.ArgumentParser(
        description="Check out all files that are not " "changed between two branches"
    )
    parser.add_argument(
        "base", nargs="?", default="HEAD", help="base branch (default HEAD)"
    )
    parser.add_argument(
        "target", nargs="?", default="master", help="target branch (default master)"
    )
    args = parser.parse_args()

    if not args.base or not args.target:
        parser.print_usage()
        sys.exit(1)

    checkout_except(git.Repo(), args.target, args.base)
