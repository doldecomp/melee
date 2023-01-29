from dataclasses import dataclass
from os.path import basename
from re import match

from .cw_map import Map


class AsmUtil:
    # Section declaration
    SECTION_REGEX = r"^\s*.section\s+(?P<Name>.[a-zA-Z0-9_$]+)"

    # Section type
    SECTION_CODE = 0
    SECTION_DATA = 1

    @dataclass
    class Section:
        start: int
        size: int
        type: int

    @staticmethod
    def get_obj_files_mk_asm(obj_files_mk_path: str, asm_root: str, obj_ext: str) -> list[str]:
        """Generate list of assembly object filenames, using obj_files.mk.
        Paths are relative to the project's asm directory.

        Args:
            obj_files_mk_path (str): Path to obj_files.mk
            asm_root (str): Project root assembly directory
            obj_ext (str): Project assembly object file extension

        Returns:
            list[str]: Assembly object file names (relative to assembly root dir)
        """
        asm_files = []

        # Read file data
        with open(obj_files_mk_path, "r") as f:
            obj_files = f.readlines()

        # Ensure asm directory has slash
        if not asm_root.endswith("/"):
            asm_root = f"{asm_root}/"

        for line in obj_files:
            # Create relative path
            dir_idx = line.rfind(asm_root)
            if dir_idx == -1:
                continue
            line = line[dir_idx:]

            # Trim after extension
            ext_idx = line.rfind(obj_ext)
            assert ext_idx != -1
            line = line[:ext_idx + len(obj_ext)]

            asm_files.append(line)

        return asm_files

    @staticmethod
    def get_section_type_from_name(name: str) -> int:
        """Get the type of the specified section
        """
        code = (
            ".init", ".text"
        )
        data = (
            "extab_", "extab", "._extab", "._exidx", "extabindex_", "extabindex", ".ctors", ".dtors", "._ctors",
            "._dtors", ".file", ".rodata", ".data", ".bss", ".sdata", ".sbss", ".sdata2", ".sbss2"
        )
        if name in code:
            return AsmUtil.SECTION_CODE
        elif name in data:
            return AsmUtil.SECTION_DATA
        # As a failsafe, if the section is actually unknown,
        # it is probably some unique data (like OGWS' ".file" section)
        print(f"Unidentifiable section! ({name})")
        print("Assuming this is a DATA section.")
        return AsmUtil.SECTION_DATA

    @staticmethod
    def swap_file_extension(file: str, ext_from: str, ext_to: str) -> str:
        """Convert object file name to assembly file name.
        """
        # Trim file extension
        ext_idx = file.rfind(ext_from)
        if ext_idx != -1:
            # Add assembly source extension
            return f"{file[:ext_idx]}{ext_to}"
        return file

    @staticmethod
    def get_obj_sections(obj_file: str, cw_map: Map, src_ext: str, obj_ext: str) -> list["AsmUtil.Section"]:
        """Create list of sections in assembly object file.
        Requires map from DOL.
        """
        sections = []
        sections_found = set()
        # Read asm
        filepath = AsmUtil.swap_file_extension(obj_file, obj_ext, src_ext)
        with open(filepath, "r", encoding="utf-8", errors="ignore") as f:
            asm = f.readlines()
        # Find sections in asm file by looking for .section directives
        for line in asm:
            sect_match = match(AsmUtil.SECTION_REGEX, line)
            if sect_match != None:
                # Section name
                sect_name = sect_match.group("Name")
                # Avoid recounting the same section
                if sect_name not in sections_found:
                    # Header symbols in current object file
                    my_file_headers = cw_map.headers[basename(obj_file)]
                    # Header symbol for current section
                    try:
                        my_header = my_file_headers[sect_name]
                        # Create summable section object
                        section = AsmUtil.Section(
                            my_header.virt_ofs, my_header.size, AsmUtil.get_section_type_from_name(sect_name))
                        assert section.start > 0 and section.size >= 0
                        sections.append(section)
                    except KeyError:
                        # Newer DKP will not generate size 0 sections
                        pass
                    sections_found.add(sect_name)

        # Dump sections
        # print(f"File: {obj_file}")
        # print("Sections:")
        # for i in sections:
        #     if i.type == AsmUtil.SECTION_DATA:
        #         print(
        #             f"start: {hex(i.start & 0xFFFFFFFF)}, size: {hex(i.size & 0xFFFFFFFF)}, type: {('CODE', 'DATA')[i.type]}")
        # print()

        return sections

    @staticmethod
    def get_obj_list_sections(obj_files: list[str], cw_map: Map, src_ext: str, obj_ext: str) -> list["AsmUtil.Section"]:
        """Create list of sections in list of assembly object files.
        Requires map from DOL.
        """
        sections = []
        for obj_file in obj_files:
            sections += AsmUtil.get_obj_sections(obj_file,
                                                 cw_map, src_ext, obj_ext)
        return sections
