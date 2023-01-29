from dataclasses import dataclass
from re import match

SYMBOL_NEW_REGEX = r"^\s*"\
    r"(?P<SectOfs>\w{8})\s+"\
    r"(?P<Size>\w{6})\s+"\
    r"(?P<VirtOfs>\w{8})\s+"\
    r"(?P<FileOfs>\w{8})\s+"\
    r"(\d{1,2}\s+)?"\
    r"(?P<Symbol>[0-9A-Za-z_<>$@.,*\\]*)"\
    r"(\s+\(entry of.*\)\s+)?\s*"\
    r"(?P<Object>\S*)"
SYMBOL_OLD_REGEX = r"^\s*"\
    r"(?P<SectOfs>\w{8})\s+"\
    r"(?P<Size>\w{6})\s+"\
    r"(?P<VirtOfs>\w{8})\s+"\
    r"(\d{1,2}\s+)?"\
    r"(?P<Symbol>[0-9A-Za-z_<>$@.,*\\]*)"\
    r"(\s+\(entry of.*\)\s+)?\s*"\
    r"(?P<Object>\S*)"

MAP_SECTION_REGEX = r"^(?P<Name>\S+)\ssection layout"


@dataclass
class Symbol:
    sect_ofs: int
    size: int
    virt_ofs: int
    virt_end: int
    file_ofs: int
    name: str
    object_file: str

    @staticmethod
    def parse(line: str, old_linker: bool) -> "Symbol":
        """Create symbol object from line of CW symbol map"""
        # Compatability with older maps (off by default)
        regex = SYMBOL_OLD_REGEX if old_linker else SYMBOL_NEW_REGEX
        # Search for match
        match_obj = match(regex, line)
        if match_obj == None:
            return None
        # Old linker has no file offset
        fileOfs = -1 if old_linker else int(match_obj.group("FileOfs"), 16)
        # Build symbol object
        return Symbol(
            int(match_obj.group("SectOfs"), 16),
            int(match_obj.group("Size"), 16),
            int(match_obj.group("VirtOfs"), 16),
            -1,  # End address set later
            fileOfs,
            match_obj.group("Symbol"),
            match_obj.group("Object"))


@dataclass
class Map():
    # Dictionary of section header symbols.
    # Outer dict key = object file name, value = header dict
    # Header dict key = section name, value = header symbol
    headers: dict[str, dict[str, Symbol]]

    def __init__(self, path: str, old_linker: bool):
        """Open and parse symbol map file"""
        # Initialize dict
        self.headers = dict()
        # Read asm
        with open(path, "r") as f:
            map_data = f.readlines()

        # Current object file
        curr_obj = None
        # Start of current section
        sect_start = -1
        # Parse each section of the symbol map
        for i in range(len(map_data)):
            # Search for "* section layout"
            sect_match = match(MAP_SECTION_REGEX, map_data[i])
            if sect_match != None:
                # Parse current section if this is not the first section
                if sect_start != -1:
                    self.parse_section(
                        sect_name, map_data[sect_start:i], old_linker)
                sect_start = i
                sect_name = sect_match.group("Name")
        # Parse last section to EOF
        self.parse_section(sect_name, map_data[sect_start:i], old_linker)

    def parse_section(self, sect_name: str, map_data: list[str], old_linker: bool):
        """Parse a section of the map file, generating header symbols"""

        # Find header symbols
        curr_object = None
        for line in map_data:
            # Search for symbol in current line
            symbol = Symbol.parse(line, old_linker)
            if symbol != None:
                # "Header symbol" refers to the first symbol in the object file
                obj_file = symbol.object_file
                if obj_file != curr_object:
                    # Create object file entry
                    if obj_file not in self.headers:
                        self.headers[obj_file] = dict()
                    # Create header symbol entry
                    self.headers[obj_file][sect_name] = symbol
                    # Set current object file
                    curr_object = obj_file
