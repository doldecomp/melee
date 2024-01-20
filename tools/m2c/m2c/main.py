import argparse
import gc
import sys
import traceback
from pathlib import Path
from typing import Dict, List, Optional, Union

from .c_types import build_typemap, dump_typemap
from .error import DecompFailure
from .flow_graph import FlowGraph, build_flowgraph, visualize_flowgraph
from .if_statements import get_function_text
from .options import CodingStyle, Options, Target
from .asm_file import AsmData, Function, parse_file
from .instruction import InstrProcessingFailure
from .translate import (
    Arch,
    FunctionInfo,
    GlobalInfo,
    translate_to_ast,
    narrow_func_call_outputs,
)
from .types import TypePool
from .arch_mips import MipsArch
from .arch_ppc import PpcArch


def print_current_exception(sanitize: bool) -> None:
    """Print a traceback for the current exception to stdout.

    If `sanitize` is true, the filename's full path is stripped,
    and the line is set to 0. These changes make the test output
    less brittle."""
    if sanitize:
        tb = traceback.TracebackException(*sys.exc_info())
        if tb.exc_type == InstrProcessingFailure and tb.__cause__:
            tb = tb.__cause__
        for frame in tb.stack:
            frame.lineno = 0
            frame.filename = Path(frame.filename).name
        for line in tb.format(chain=False):
            print(line, end="")
    else:
        traceback.print_exc(file=sys.stdout)


def print_exception_as_comment(
    exc: Exception, context: Optional[str], sanitize: bool
) -> None:
    context_phrase = f" in {context}" if context is not None else ""
    if isinstance(exc, OSError):
        print(f"/* OSError{context_phrase}: {exc} */")
        return
    elif isinstance(exc, DecompFailure):
        print("/*")
        print(f"Decompilation failure{context_phrase}:\n")
        print(exc)
        print("*/")
    else:
        print("/*")
        print(f"Internal error{context_phrase}:\n")
        print_current_exception(sanitize=sanitize)
        print("*/")


def run(options: Options) -> int:
    arch: Arch
    if options.target.arch == Target.ArchEnum.MIPS:
        arch = MipsArch()
    elif options.target.arch == Target.ArchEnum.PPC:
        arch = PpcArch()
    else:
        raise ValueError(f"Invalid target arch: {options.target.arch}")

    all_functions: Dict[str, Function] = {}
    asm_data = AsmData()
    try:
        for filename in options.filenames:
            if filename == "-":
                asm_file = parse_file(sys.stdin, arch, options)
            else:
                with open(filename, "r", encoding="utf-8-sig") as f:
                    asm_file = parse_file(f, arch, options)
            all_functions.update((fn.name, fn) for fn in asm_file.functions)
            asm_file.asm_data.merge_into(asm_data)

        if options.heuristic_strings:
            asm_data.detect_heuristic_strings()
        typemap = build_typemap(options.c_contexts, use_cache=options.use_cache)
    except Exception as e:
        print_exception_as_comment(
            e, context=None, sanitize=options.sanitize_tracebacks
        )
        return 1

    if options.dump_typemap:
        dump_typemap(typemap)
        return 0

    if not options.function_indexes_or_names:
        functions = list(all_functions.values())
    else:
        functions = []
        for index_or_name in options.function_indexes_or_names:
            if isinstance(index_or_name, int):
                if not (0 <= index_or_name < len(all_functions)):
                    print(
                        f"Function index {index_or_name} is out of bounds (must be between "
                        f"0 and {len(all_functions) - 1}).",
                        file=sys.stderr,
                    )
                    return 1
                functions.append(list(all_functions.values())[index_or_name])
            else:
                if index_or_name not in all_functions:
                    print(f"Function {index_or_name} not found.", file=sys.stderr)
                    return 1
                functions.append(all_functions[index_or_name])

    fmt = options.formatter()
    function_names = set(all_functions.keys())
    typepool = TypePool(
        unknown_field_prefix="unk_" if fmt.coding_style.unknown_underscore else "unk",
        unk_inference=options.unk_inference,
    )
    global_info = GlobalInfo(
        asm_data,
        arch,
        options.target,
        function_names,
        typemap,
        typepool,
        deterministic_vars=options.deterministic_vars,
    )

    flow_graphs: List[Union[FlowGraph, Exception]] = []
    for function in functions:
        try:
            narrow_func_call_outputs(function, global_info)
            graph = build_flowgraph(
                function,
                global_info.asm_data,
                arch,
                fragment=False,
                print_warnings=options.debug,
            )
            flow_graphs.append(graph)
        except Exception as e:
            # Store the exception for later, to preserve the order in the output
            flow_graphs.append(e)

    # Perform the preliminary passes to improve type resolution, but discard the results/exceptions
    for i in range(options.passes - 1):
        preliminary_infos = []
        for function, flow_graph in zip(functions, flow_graphs):
            try:
                if isinstance(flow_graph, Exception):
                    raise flow_graph
                flow_graph.reset_block_info()
                info = translate_to_ast(function, flow_graph, options, global_info)
                preliminary_infos.append(info)
            except Exception:
                pass
        try:
            global_info.global_decls(fmt, options.global_decls, [])
        except Exception:
            pass
        for info in preliminary_infos:
            try:
                get_function_text(info, options)
            except Exception:
                pass

        # This operation can change struct field paths, so it is only performed
        # after discarding all of the translated Expressions.
        typepool.prune_structs()

    function_infos: List[Union[FunctionInfo, Exception]] = []
    for function, flow_graph in zip(functions, flow_graphs):
        try:
            if isinstance(flow_graph, Exception):
                raise flow_graph
            flow_graph.reset_block_info()
            info = translate_to_ast(function, flow_graph, options, global_info)
            function_infos.append(info)
        except Exception as e:
            # Store the exception for later, to preserve the order in the output
            function_infos.append(e)

    return_code = 0
    try:
        if options.visualize_flowgraph is not None:
            fn_info = function_infos[0]
            if isinstance(fn_info, Exception):
                raise fn_info
            print(visualize_flowgraph(fn_info.flow_graph, options.visualize_flowgraph))
            return 0

        type_decls = typepool.format_type_declarations(
            fmt, stack_structs=options.print_stack_structs
        )
        if type_decls:
            print(type_decls)

        global_decls = global_info.global_decls(
            fmt,
            options.global_decls,
            [fn for fn in function_infos if isinstance(fn, FunctionInfo)],
        )
        if global_decls:
            print(global_decls)
    except Exception as e:
        print_exception_as_comment(
            e, context=None, sanitize=options.sanitize_tracebacks
        )
        return_code = 1

    for index, (function, function_info) in enumerate(zip(functions, function_infos)):
        if index != 0:
            print()
        try:
            if options.print_assembly:
                print(function)
                print()

            if isinstance(function_info, Exception):
                raise function_info

            function_text = get_function_text(function_info, options)
            print(function_text)

        except Exception as e:
            print_exception_as_comment(
                e,
                context=f"function {function.name}",
                sanitize=options.sanitize_tracebacks,
            )
            return_code = 1

    for warning in typepool.warnings:
        print(fmt.with_comments("", comments=[warning]))

    return return_code


def parse_flags(flags: List[str]) -> Options:
    parser = argparse.ArgumentParser(
        description="Decompile assembly to C.",
        usage="%(prog)s [-t mips-ido-c] [--context C_FILE] [-f FN ...] filename [filename ...]",
    )

    group = parser.add_argument_group("Input Options")
    group.add_argument(
        metavar="filename",
        nargs="+",
        dest="filenames",
        help="Input asm filename(s)",
    )
    group.add_argument(
        "--context",
        metavar="C_FILE",
        dest="c_contexts",
        action="append",
        type=Path,
        default=[],
        help="Read variable types/function signatures/structs from an existing C file. "
        "The file must already have been processed by the C preprocessor.",
    )
    group.add_argument(
        "--no-cache",
        action="store_false",
        dest="use_cache",
        help="Disable caching of variable types/function signatures/structs from the parsed C context. "
        "This option should be used for untrusted environments. "
        'The cache for "foo/ctx_bar.c" is stored in "foo/ctx_bar.c.m2c". '
        "The *.m2c files automatically regenerate when the source file change, and can be ignored.",
    )
    group.add_argument(
        "-D",
        metavar="SYM[=VALUE]",
        dest="defined",
        action="append",
        default=[],
        help="Mark preprocessor symbol as defined",
    )
    group.add_argument(
        "-U",
        metavar="SYM",
        dest="undefined",
        action="append",
        default=[],
        help="Mark preprocessor symbol as undefined",
    )
    group.add_argument(
        "--incbin-dir",
        dest="incbin_dirs",
        action="append",
        default=[],
        type=Path,
        help="Add search path for loading .incbin directives in the input asm",
    )

    group = parser.add_argument_group("Output Options")
    group.add_argument(
        "-f",
        "--function",
        metavar="FN",
        dest="functions",
        action="append",
        default=[],
        help="Function index or name to decompile",
    )
    group.add_argument(
        "--globals",
        dest="global_decls",
        type=Options.GlobalDeclsEnum,
        choices=list(Options.GlobalDeclsEnum),
        default="used",
        help="Control which global declarations & initializers are emitted. "
        '"all" includes all globals with entries in .data/.rodata/.bss, as well as inferred symbols. '
        '"used" only includes symbols used by the decompiled functions that are not in the context (default). '
        '"none" does not emit any global declarations. ',
    )
    group.add_argument(
        "--stack-structs",
        dest="print_stack_structs",
        action="store_true",
        help=(
            "Include template structs for each function's stack. These can be modified and passed back "
            "into m2c with --context to set the types & names of stack vars."
        ),
    )
    group.add_argument(
        "--debug",
        dest="debug",
        action="store_true",
        help="Print debug info inline",
    )
    group.add_argument(
        "--print-assembly",
        dest="print_assembly",
        action="store_true",
        help="Print assembly of function to decompile",
    )
    group.add_argument(
        "--dump-typemap",
        dest="dump_typemap",
        action="store_true",
        help="Dump information about all functions and structs from the provided C "
        "context. Mainly useful for debugging.",
    )
    group.add_argument(
        "--visualize",
        dest="visualize_flowgraph",
        nargs="?",
        default=None,
        const=Options.VisualizeTypeEnum.C,
        type=Options.VisualizeTypeEnum,
        choices=list(Options.VisualizeTypeEnum),
        help="Print an SVG visualization of the control flow graph using graphviz",
    )
    group.add_argument(
        "--sanitize-tracebacks",
        dest="sanitize_tracebacks",
        action="store_true",
        help=argparse.SUPPRESS,
    )

    group = parser.add_argument_group("Formatting Options")
    group.add_argument(
        "--valid-syntax",
        dest="valid_syntax",
        action="store_true",
        help="Emit valid C syntax, using macros to indicate unknown types or other "
        "unusual statements. Macro definitions are in `m2c_macros.h`.",
    )
    brace_style = group.add_mutually_exclusive_group()
    brace_style.add_argument(
        "--allman",
        dest="allman",
        action="store_true",
        help="Put braces on separate lines",
    )
    brace_style.add_argument(
        "--knr",
        dest="knr",
        action="store_true",
        help="Put function opening braces on separate lines",
    )
    group.add_argument(
        "--indent-switch-contents",
        dest="indent_switch_contents",
        action="store_true",
        help="Indent switch statements' contents an extra level",
    )
    group.add_argument(
        "--pointer-style",
        dest="pointer_style",
        help="Control whether to output pointer asterisks next to the type name (left) "
        "or next to the variable name (right). Default: right",
        choices=["left", "right"],
        default="right",
    )
    group.add_argument(
        "--unk-underscore",
        dest="unknown_underscore",
        help="Emit unk_X instead of unkX for unknown struct accesses",
        action="store_true",
    )
    group.add_argument(
        "--hex-case",
        dest="hex_case",
        help="Display case labels in hex rather than decimal",
        action="store_true",
    )
    group.add_argument(
        "--comment-style",
        dest="comment_style",
        type=CodingStyle.CommentStyle,
        choices=list(CodingStyle.CommentStyle),
        default="multiline",
        help=(
            "Comment formatting. "
            '"multiline" for C-style `/* ... */`, '
            '"oneline" for C++-style `// ...`, '
            '"none" to disable comments. '
            "Default: multiline"
        ),
    )
    group.add_argument(
        "--comment-column",
        dest="comment_column",
        metavar="N",
        type=int,
        default=52,
        help="Column number to justify comments to. Set to 0 to disable justification. Default: 52",
    )
    group.add_argument(
        "--no-casts",
        dest="skip_casts",
        action="store_true",
        help="Don't emit any type casts",
    )
    group.add_argument(
        "--zfill-constants",
        dest="zfill_constants",
        action="store_true",
        help="Pad hex constants with 0's to fill their type's width.",
    )
    group.add_argument(
        "--force-decimal",
        dest="force_decimal",
        action="store_true",
        help="Force decimal values",
    )
    group.add_argument(
        "--deterministic-vars",
        dest="deterministic_vars",
        action="store_true",
        help="Name temp and phi vars after their location in the source asm, "
        "rather than using an incrementing suffix. Can help reduce diff size in tests.",
    )

    group = parser.add_argument_group("Analysis Options")
    group.add_argument(
        "-t",
        "--target",
        dest="target",
        type=Target.parse,
        default="mips-ido-c",
        help="Target architecture, compiler, and language triple. "
        "Supported triples: mips-ido-c, mips-gcc-c, mipsel-gcc-c, ppc-mwcc-c++, ppc-mwcc-c. "
        "Default is mips-ido-c, `ppc` is an alias for ppc-mwcc-c++. ",
    )
    group.add_argument(
        "--passes",
        "-P",
        dest="passes",
        metavar="N",
        type=int,
        default=2,
        help="Number of translation passes to perform. Each pass may improve type resolution and produce better "
        "output, particularly when decompiling multiple functions. Default: 2",
    )
    group.add_argument(
        "--stop-on-error",
        dest="stop_on_error",
        action="store_true",
        help="Stop when encountering any error",
    )
    group.add_argument(
        "--void",
        dest="void",
        action="store_true",
        help="Assume the decompiled function returns void",
    )
    group.add_argument(
        "--gotos-only",
        dest="ifs",
        action="store_false",
        help="Disable control flow generation; emit gotos for everything",
    )
    group.add_argument(
        "--no-ifs",
        dest="ifs",
        action="store_false",
        help=argparse.SUPPRESS,
    )
    group.add_argument(
        "--no-switches",
        dest="switch_detection",
        action="store_false",
        help=(
            "Disable detecting irregular switch statements from if trees. "
            "Jump tables switches are still emitted."
        ),
    )
    group.add_argument(
        "--no-andor",
        dest="andor_detection",
        action="store_false",
        help="Disable detection of &&/||",
    )
    group.add_argument(
        "--no-unk-inference",
        dest="unk_inference",
        action="store_false",
        help=(
            "Disable type inference on unknown struct fields & unknown global symbol types. "
            "See the README for more information on unknown inference."
        ),
    )
    group.add_argument(
        "--heuristic-strings",
        dest="heuristic_strings",
        action="store_true",
        help="Heuristically detect strings in rodata even when not defined using .asci/.asciz.",
    )
    group.add_argument(
        "--reg-vars",
        metavar="REGISTERS",
        dest="reg_vars",
        help="Use single variables instead of temps/phis for the given "
        "registers (comma separated)",
    )
    group.add_argument(
        "--goto",
        metavar="PATTERN",
        dest="goto_patterns",
        action="append",
        default=["GOTO"],
        help="Emit gotos for branches on lines containing this substring "
        '(possibly within a comment). Default: "GOTO". Multiple '
        "patterns are allowed.",
    )
    group.add_argument(
        "--pdb-translate",
        dest="pdb_translate",
        action="store_true",
        help=argparse.SUPPRESS,
    )
    group.add_argument(
        "--disable-gc",
        dest="disable_gc",
        action="store_true",
        help="Disable Python garbage collection. Can improve performance at "
        "the risk of running out of memory.",
    )

    args = parser.parse_args(flags)
    reg_vars = args.reg_vars.split(",") if args.reg_vars else []
    preproc_defines: Dict[str, Optional[int]] = {d: None for d in args.undefined}
    for d in args.defined:
        parts = d.split("=", 1)
        preproc_defines[parts[0]] = int(parts[1], 0) if len(parts) >= 2 else 1

    coding_style = CodingStyle(
        newline_after_function=args.allman or args.knr,
        newline_after_if=args.allman,
        newline_before_else=args.allman,
        switch_indent_level=2 if args.indent_switch_contents else 1,
        pointer_style_left=args.pointer_style == "left",
        unknown_underscore=args.unknown_underscore,
        hex_case=args.hex_case,
        comment_style=args.comment_style,
        comment_column=args.comment_column,
    )

    functions: List[Union[int, str]] = []
    for fn in args.functions:
        try:
            functions.append(int(fn))
        except ValueError:
            functions.append(fn)

    # The debug output interferes with the visualize output
    if args.visualize_flowgraph is not None:
        args.debug = False

    return Options(
        filenames=args.filenames,
        function_indexes_or_names=functions,
        debug=args.debug,
        void=args.void,
        ifs=args.ifs,
        switch_detection=args.switch_detection,
        andor_detection=args.andor_detection,
        skip_casts=args.skip_casts,
        zfill_constants=args.zfill_constants,
        force_decimal=args.force_decimal,
        heuristic_strings=args.heuristic_strings,
        reg_vars=reg_vars,
        goto_patterns=args.goto_patterns,
        stop_on_error=args.stop_on_error,
        print_assembly=args.print_assembly,
        visualize_flowgraph=args.visualize_flowgraph,
        c_contexts=args.c_contexts,
        use_cache=args.use_cache,
        dump_typemap=args.dump_typemap,
        pdb_translate=args.pdb_translate,
        preproc_defines=preproc_defines,
        coding_style=coding_style,
        sanitize_tracebacks=args.sanitize_tracebacks,
        valid_syntax=args.valid_syntax,
        global_decls=args.global_decls,
        target=args.target,
        print_stack_structs=args.print_stack_structs,
        unk_inference=args.unk_inference,
        passes=args.passes,
        incbin_dirs=args.incbin_dirs,
        deterministic_vars=args.deterministic_vars,
        disable_gc=args.disable_gc,
    )


def main() -> None:
    # Large functions can sometimes require a higher recursion limit than the
    # CPython default. Cap to INT_MAX to avoid an OverflowError, though.
    sys.setrecursionlimit(min(2**31 - 1, 10 * sys.getrecursionlimit()))
    options = parse_flags(sys.argv[1:])
    if options.disable_gc:
        gc.disable()
        gc.set_threshold(0)
    sys.exit(run(options))


if __name__ == "__main__":
    main()
