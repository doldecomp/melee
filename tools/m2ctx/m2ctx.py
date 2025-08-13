#!/usr/bin/env python3

import html
import os
import subprocess
import sys
from pathlib import Path
from typing import List

here = Path(__file__).parent
root = (here / "../../").resolve()
src = root / "src"
build = root / "build"
header_path = build / "ctx.h"
source_path = build / "ctx.c"
render_path = build / "ctx.html"
template_path = root / "tools/ctx_template.html"
mwcc_command = root / "tools/mwcc_compiler/1.2.5e/mwcceppc.exe"

MWCC_FLAGS = [
    "-EP",
    "-Cpp_exceptions",
    "off",
    "-proc",
    "gekko",
    "-fp",
    "hard",
    "-fp_contract",
    "on",
    "-O4,p",
    "-enum",
    "int",
    "-nodefaults",
    "-inline",
    "auto",
    "-i",
    "src/melee",
    "-i",
    "src/melee/ft/chara",
    "-I-",
    "-i",
    "src",
    "-i",
    "src/MSL",
    "-i",
    "src/Runtime",
    "-i",
    "src/sysdolphin",
    "-i",
    "extern/dolphin/include",
    "-DM2CTX",
]

class CmdPreprocessor(Preprocessor):
    def __init__(self, input_file):
        super(CmdPreprocessor, self).__init__()

        # Override Preprocessor instance variables
        version='1.30'
        self.define("__PCPP_VERSION__ " + version)
        self.define("__PCPP_ALWAYS_FALSE__ 0")
        self.define("__PCPP_ALWAYS_TRUE__ 1")
        self.line_directive = None
        self.compress = 2

        self.bypass_ifpassthru = False
        self.potential_include_guard = None

        includes = [
            "src",
            "src/MSL",
            "src/Runtime",
            "src/sysdolphin",
            "src/melee",
            "src/melee/ft/chara",
            "extern/dolphin/include",
        ]
        defines = [
            "__MWERKS__",
            "M2CTX",
        ]
        self.undefines = [
            "FIGHTERVARS_SIZE",
        ]
        self.passthru_keywords = [
            "M2CTX_DUAL",
        ]

        self.compress = 2
        for val in includes:
            self.add_path(val)
        for val in defines:
            self.define(val)
        for val in self.undefines:
            self.undef(val)

        string_buffer = io.StringIO()
        try:
            with open(input_file, 'r') as file:
                file_content = file.read()
                self.parse(file_content)
            self.write(string_buffer)
        except:
            print(traceback.print_exc(10), file = sys.stderr)
            print("\nINTERNAL PREPROCESSOR ERROR AT AROUND %s:%d, FATALLY EXITING NOW\n"
                % (self.lastdirective.source, self.lastdirective.lineno), file = sys.stderr)
            sys.exit(-99)
        finally:
            self.output_string = string_buffer.getvalue()

    def on_unknown_macro_in_defined_expr(self,tok):
        if tok.value in self.undefines:
            return False
        if tok.value in self.passthru_keywords:
            return None  # Pass through as expanded as possible
        return super(CmdPreprocessor, self).on_unknown_macro_in_defined_expr(tok)

    def on_unknown_macro_in_expr(self,ident):
        if ident in self.undefines:
            return super(CmdPreprocessor, self).on_unknown_macro_in_expr(ident)
        if ident in self.passthru_keywords:
            return None  # Pass through as expanded as possible
        return super(CmdPreprocessor, self).on_unknown_macro_in_expr(ident)

    def on_unknown_macro_function_in_expr(self,ident):
        if ident in self.undefines:
            return super(CmdPreprocessor, self).on_unknown_macro_function_in_expr(ident)
        if ident in self.passthru_keywords:
            return None  # Pass through as expanded as possible
        return super(CmdPreprocessor, self).on_unknown_macro_function_in_expr(ident)

    def on_directive_handle(self,directive,toks,ifpassthru,precedingtoks):
        if ifpassthru:
            if directive.value == 'if' or directive.value == 'elif' or directive == 'else' or directive.value == 'endif':
                self.bypass_ifpassthru = len([tok for tok in toks if tok.value == '__PCPP_ALWAYS_FALSE__' or tok.value == '__PCPP_ALWAYS_TRUE__']) > 0
            if not self.bypass_ifpassthru and (directive.value == 'define' or directive.value == 'undef'):
                if toks[0].value != self.potential_include_guard:
                    raise OutputDirective(Action.IgnoreAndPassThrough)  # Don't execute anything with effects when inside an #if expr with undefined macro
        super(CmdPreprocessor, self).on_directive_handle(directive,toks,ifpassthru,precedingtoks)
        return None  # Pass through defines

    def on_comment(self,tok):
        return True  # Pass through comments


PCPP_FLAGS = [
    "--passthru-defines",
    "--passthru-comments",
    "--line-directive",
    "--compress",
    "-I",
    "src",
    "-I",
    "src/MSL",
    "-I",
    "src/Runtime",
    "-I",
    "src/sysdolphin",
    "-I",
    "src/melee",
    "-I",
    "src/melee/ft/chara",
    "-I",
    "extern/dolphin/include",
    "-D",
    "__MWERKS__",
    "-D",
    "M2CTX",
    "-U",
    "FIGHTERVARS_SIZE",
]

def write_header(path: Path):
    files = sorted({f"#include <{file.relative_to(src)}>" for file in src.rglob("*.h")})
    path.write_text("\n".join(files), encoding="utf-8")

def try_import(c_command: List[str], quiet: bool):
    try:
        out_text = subprocess.check_output(c_command, cwd=root, encoding="utf8")
    except subprocess.CalledProcessError as err:
        print(
            "Failed to preprocess input file, when running command:\n"
            + " ".join(c_command),
            file=sys.stderr,
        )
        if not quiet:
            print(err.output, file=sys.stderr)
        sys.exit(1)

    if not out_text:
        print("Output is empty - aborting")
        sys.exit(1)

    return out_text

def pcpp_import(in_file: Path, quiet: bool) -> str:
    p = CmdPreprocessor(in_file)
    return p.output_string

def mwcc_import(in_file: Path, quiet: bool) -> str:
    c_command = [str(mwcc_command), *MWCC_FLAGS, "-E", str(in_file)]

    if sys.platform != "win32":
        wine = os.environ.get("WINE", "wine")
        c_command = [wine] + c_command

    return try_import(c_command, quiet)

def main():
    import argparse

    parser = argparse.ArgumentParser(
        description="""Create a context file which can be used for mips_to_c"""
    )

    parser.add_argument(
        "-q", "--quiet", action="store_true", help="do not print the output"
    )
    parser.add_argument(
        "-n",
        "--no-file",
        action="store_true",
        help=f"do not write {source_path.relative_to(root)}",
    )
    parser.add_argument(
        "-x",
        "--clipboard",
        action="store_true",
        help="copy the output to the clipboard (requires pyperclip)",
    )
    parser.add_argument(
        "-c",
        "--colorize",
        action="store_true",
        help="colorize the output (requires pygments)",
    )
    parser.add_argument(
        "-f",
        "--format",
        action="store_true",
        help="format the output (requires clang-format)",
    )
    parser.add_argument(
        "-p",
        "--preprocessor",
        action="store_true",
        help="preserve preprocessor directives (requires pcpp)",
    )
    parser.add_argument(
        "-r", "--render", action="store_true", help="render the context to html"
    )
    args = parser.parse_args()

    write_header(header_path)

    if args.preprocessor:
        import traceback, copy, io, re
        from pcpp.preprocessor import Preprocessor, OutputDirective, Action

        output = pcpp_import(header_path, args.quiet)
    else:
        output = mwcc_import(header_path, args.quiet)

    if args.format:
        try:
            output = subprocess.check_output(
                ["clang-format"], cwd=root, input=output, encoding="utf8"
            )
        except subprocess.CalledProcessError as err:
            print(f"Failed to format the output:\n{err.output}", file=sys.stderr)

    output = output.strip()

    if not args.no_file:
        source_path.write_text(output, encoding="utf-8")

    if args.clipboard:
        import pyperclip

        pyperclip.copy(output)

    if args.render:
        template = template_path.read_text()
        html_output = template.format(ctx=html.escape(output))
        render_path.write_text(html_output, encoding="utf-8")

    if not args.quiet:
        if args.colorize:
            try:
                import colorama

                colorama.just_fix_windows_console()
            except ModuleNotFoundError:
                pass
            from pygments import highlight
            from pygments.formatters import TerminalFormatter
            from pygments.lexers import CLexer

            output = highlight(output, CLexer(), TerminalFormatter())

        print(output)


if __name__ == "__main__":
    main()
