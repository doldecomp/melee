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
import os
import platform
import shutil
import stat
import urllib.request
import zipfile
from typing import Callable, Dict
from pathlib import Path


def binutils_url(tag):
    uname = platform.uname()
    system = uname.system.lower()
    arch = uname.machine.lower()
    if system == "darwin":
        system = "macos"
        arch = "universal"
    elif arch == "amd64":
        arch = "x86_64"

    repo = "https://github.com/encounter/gc-wii-binutils"
    return f"{repo}/releases/download/{tag}/{system}-{arch}.zip"


def compilers_url(tag: str) -> str:
    return f"https://files.decomp.dev/compilers_{tag}.zip"


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


def objdiff_cli_url(tag: str) -> str:
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

    repo = "https://github.com/encounter/objdiff"
    return f"{repo}/releases/download/{tag}/objdiff-cli-{system}-{arch}{suffix}"


def sjiswrap_url(tag: str) -> str:
    repo = "https://github.com/encounter/sjiswrap"
    return f"{repo}/releases/download/{tag}/sjiswrap-windows-x86.exe"


def wibo_url(tag: str) -> str:
    uname = platform.uname()
    arch = uname.machine.lower()
    system = uname.system.lower()
    if system == "darwin":
        arch = "macos"

    repo = "https://github.com/decompals/wibo"
    return f"{repo}/releases/download/{tag}/wibo-{arch}"


TOOLS: Dict[str, Callable[[str], str]] = {
    "binutils": binutils_url,
    "compilers": compilers_url,
    "dtk": dtk_url,
    "objdiff-cli": objdiff_cli_url,
    "sjiswrap": sjiswrap_url,
    "wibo": wibo_url,
}


def download(url, response, output) -> None:
    if url.endswith(".zip"):
        data = io.BytesIO(response.read())
        with zipfile.ZipFile(data) as f:
            f.extractall(output)
        # Make all files executable
        for root, _, files in os.walk(output):
            for name in files:
                os.chmod(os.path.join(root, name), 0o755)
        output.touch(mode=0o755)  # Update dir modtime
    else:
        with open(output, "wb") as f:
            shutil.copyfileobj(response, f)
        st = os.stat(output)
        os.chmod(output, st.st_mode | stat.S_IEXEC)


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
    try:
        with urllib.request.urlopen(req) as response:
            download(url, response, output)
    except urllib.error.URLError as e:
        if str(e).find("CERTIFICATE_VERIFY_FAILED") == -1:
            raise e
        try:
            import certifi
            import ssl
        except ImportError:
            print(
                '"certifi" module not found. Please install it using "python -m pip install certifi".'
            )
            return

        with urllib.request.urlopen(
            req, context=ssl.create_default_context(cafile=certifi.where())
        ) as response:
            download(url, response, output)


if __name__ == "__main__":
    main()
