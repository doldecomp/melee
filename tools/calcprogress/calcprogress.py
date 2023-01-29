"""
calcprogress

1) Configure file extension functions
    - Depending on your project's convention, calcprogress must know
      what file extension is expected, in order to derive source/object names
      from translation units.
    - If your project does not use the default ".s" extension (ex: ".asm") for assembly source files,
      set your extension using the --asm-src-ext argument.
    - If your project does not use the default ".o" extension (ex: ".s.o") for assembly source files,
      set your extension using the --asm-obj-ext argument.

2) Configure progress output
    - To add custom slices (ranges) for progress tracking, edit the DOL_SLICE_GROUPS list.
    - To add custom output for your project, edit the exec_progress_callback
      and slice_group_progress_callback functions (both in this file). Example code is written
      in each function.
"""

from src.main import main

"""All executable slice groups.
- This is designed for tracking multiple slices together.
- The script will always display generic code/data progress,
  but you can add groups here to track things like libraries.
  (See the README for an example.)
"""
EXEC_SLICE_GROUPS = [
    # SliceGroup("My Slice Group", [MySlice1, MySlice2, MySlice3, ...]),
]


def exec_progress_callback(src_code: int, total_code: int, src_data: int, total_data: int):
    """Executable (DOL/REL) progress callback.
    Any game-specific counters or extra things should go here.
    """
    # Example code:
    print("Example executable progress callback!")
    code_progress = src_code / total_code  # range [0, 1]
    data_progress = src_data / total_data  # range [0, 1]
    total_progress = (code_progress + data_progress) / (1 + 1)
    total_percent = total_progress * 100
    print(f"{total_percent}% of this executable has been decompiled")


def slice_group_progress_callback(name: str, src_size: int, total_size: int):
    """Slice group progress callback.
    Any game-specific counters or extra things should go here.
    """
    # Example code:
    print("Example slice group progress callback!")
    slice_progress = src_size / total_size * 100
    print(f"{slice_progress}% of this slice group ({name}) has been decompiled")


if __name__ == "__main__":
    main(EXEC_SLICE_GROUPS, exec_progress_callback,
         slice_group_progress_callback)
