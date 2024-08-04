#!/usr/bin/env python3

###
# Downloads various tools from GitHub releases.
#
# Usage:
#   python3 tools/download_tool.py wibo build/tools/wibo --tag 1.0.0
#
# If changes are made, please submit a PR to
# https://github.com/encounter/dtk-template
###

import argparse
import io
import platform
import shutil
import stat
import urllib.request
import zipfile
from pathlib import Path
from typing import Callable, Dict


def dtk_url(tag: str) -> str:
    uname = platform.uname()
    suffix = ""
    system = uname.system.lower()
    if system == "darwin":
        system = "macos"
    elif system == "windows":
        suffix = ".exe"
    arch = uname.machine.lower()
    if arch == "amd64":
        arch = "x86_64"

    repo = "https://github.com/encounter/decomp-toolkit"
    return f"{repo}/releases/download/{tag}/dtk-{system}-{arch}{suffix}"


TOOLS: Dict[str, Callable[[str], str]] = {
    "dtk": dtk_url,
}


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("tool", help="Tool name")
    parser.add_argument("output", type=Path, help="output file path")
    parser.add_argument("--tag", help="GitHub tag", required=True)
    args = parser.parse_args()

    url = TOOLS[args.tool](args.tag)
    output = Path(args.output)

    print(f"Downloading {url} to {output}")
    req = urllib.request.Request(url, headers={"User-Agent": "Mozilla/5.0"})
    with urllib.request.urlopen(req) as response:
        if url.endswith(".zip"):
            data = io.BytesIO(response.read())
            with zipfile.ZipFile(data) as f:
                f.extractall(output)
            output.touch(mode=0o755)
        else:
            output.parent.mkdir(parents=True, exist_ok=True)
            with output.open("wb") as f:
                shutil.copyfileobj(response, f)
            st = output.stat()
            output.chmod(st.st_mode | stat.S_IEXEC)


if __name__ == "__main__":
    main()
