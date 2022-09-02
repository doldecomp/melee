from argparse import ArgumentParser
from sys import argv

from .asm_util import AsmUtil
from .cw_map import Map
from .dol import Dol
from .progress import SliceGroup, calc_exec_progress, calc_slice_group_progress


def main(groups: list[SliceGroup], exec_callback: "function", group_callback: "function"):
    parser = ArgumentParser()
    # Either DOL or REL is required
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument("--dol", type=str,
                       required=False, help="Path to DOL")
    group.add_argument("--rel", type=str,
                       required=False, help="Path to REL")
    parser.add_argument("--map", type=str,
                        required=True, help="Path to symbol map")
    parser.add_argument("--asm-root", nargs="?", type=str,
                        required=False, default="asm/", help="Path to asm")
    parser.add_argument("--asm-src-ext", nargs="?", type=str, required=False,
                        default=".s", help="Custom assembly source file extension")
    parser.add_argument("--asm-obj-ext", nargs="?", type=str, required=False,
                        default=".o", help="Custom assembly object file extension (such as Melee's \".s.o\")")
    parser.add_argument("--obj-files-mk", nargs="?", type=str, required=False,
                        default="obj_files.mk", help="Path to obj_files.mk")
    parser.add_argument("--old-map", nargs="?", type=bool, required=False,
                        default=False, help="Whether to use the old map format")
    args = parser.parse_args(argv[1:])

    dol = Dol(args.dol)
    dol_map = Map(args.map, args.old_map)

    # All assembly source built by the makefile
    obj_files = AsmUtil.get_obj_files_mk_asm(
        args.obj_files_mk, args.asm_root, args.asm_obj_ext)
    # DOL/REL sections from the assembly source
    sections = AsmUtil.get_obj_list_sections(
        obj_files, dol_map, args.asm_src_ext, args.asm_obj_ext)

    # Calculate full progress (REL/DOL)
    calc_exec_progress(dol, sections, exec_callback)

    # Calculate progress of slices
    if len(groups) > 0:
        print("Slices:")
        for group in groups:
            calc_slice_group_progress(group, sections, group_callback)
