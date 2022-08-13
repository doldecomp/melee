import re
import struct
from math import ceil
from pathlib import Path
from typing import TextIO, Match, Callable, Any, Tuple, Union, List

root = Path(__file__).parent.parent

options = {
    'input_file': root / "asm/sysdolphin/baselib/baselib_unknown_001.s"
}

default_options = {
    'zero': 'null',  # How to treat zero-value dwords
    # None: do not change zero-value dwords
    # 'hex': force zero to '0x00000000'
    # 'int': force zero to '0'
    # 'null': force zero to 'NULL'
    # 'float': force zero to '0.0'

    'find_ascii': True,  # Attempt to find zero-terminated ASCII strings
    'find_f32': True,  # Attempt to find 4-byte floating-point
    'find_s32': True,  # Attempt to find negative 4-byte values
    'find_u32': True,  # Attempt to find positive 4-byte values

    'min_ascii_len': 5,  # Minimum length for a byte array to be considered a string
    's32_min_value': -1000,  # Lowest acceptable value for s32
    'u32_max_value': 1000,  # Highest acceptable value for u32
    'f32_max_abs_value': 1000,  # Biggest acceptable  value for f32
    'f32_min_abs_value': 0.0001,  # Smallest acceptable value for f32
    'f32_max_digits': 5,  # Maximum number of digits for f32 (excludes - and .)
}

options = {**options, **default_options}

dword_re = re.compile(r"^(?P<indent>\s*)\.4byte (?:(?P<null>NULL)|0x(?P<hex>[\dA-F]{8}))$")


def take_buffer_len(buffer: bytearray, length: int, str_fn: Callable[[bytearray], Union[str, List[str], None]]):
    if len(buffer) < length:
        return None, buffer
    if result := str_fn(buffer[:length]):
        return result, buffer[length:]
    return None, buffer


def try_get_dword(buffer: bytearray, unpack_format: str, result_filter: Callable[[Any], bool],
                  instruction: str, result_format: str) -> Tuple[Union[str, List[str], None], bytearray]:
    def get_dword_str(dword: bytearray) -> str:
        result, = struct.unpack(unpack_format, dword)
        if not result_filter(result):
            return None
        return f'{instruction} {result_format.format(result)}'

    return take_buffer_len(buffer, 4, get_dword_str)


def try_get_zero(buffer: bytearray) -> Tuple[Union[str, List[str], None], bytearray]:
    def get_dword_str(dword: bytearray) -> str:
        dword_int, = struct.unpack('>I', dword)
        if dword_int != 0:
            return None

        zero_opt = options['zero']
        value: str
        instruction: str = '4byte'
        if zero_opt == 'hex':
            value = '0x00000000'
        elif zero_opt == 'int':
            instruction, value = 'int', '0'
        elif zero_opt == 'float':
            instruction, value = 'float', '0.0'
        elif zero_opt == 'null':
            value = 'NULL'
        else:
            raise ValueError(zero_opt)
        return f"{instruction} {value}"

    return take_buffer_len(buffer, 4, get_dword_str)


def try_get_f32(buffer: bytearray) -> Tuple[Union[str, List[str], None], bytearray]:
    def result_filter(f: float) -> bool:
        if f == 0.0:
            return False
        if f != f:  # NaN
            return False
        abs_f = abs(f)
        if (min_abs := options.get('f32_min_abs_value')) and abs_f < min_abs:
            return False
        if (max_abs := options.get('f32_max_abs_value')) and abs_f > max_abs:
            return False
        if (max_digits := options.get('f32_max_digits')) and len(str(abs_f).replace('.', '')) > max_digits:
            return False
        return True

    return try_get_dword(buffer, '>f', result_filter, 'float', '{}')


def try_get_u32(buffer: bytearray) -> Tuple[Union[str, List[str], None], bytearray]:
    def result_filter(i: int) -> bool:
        if i == 0:
            return False
        if max_value := options.get('u32_max_value'):
            return i < max_value
        return True

    return try_get_dword(buffer, '>I', result_filter, 'int', '{}')


def try_get_s32(buffer: bytearray) -> Tuple[Union[str, List[str], None], bytearray]:
    def result_filter(i: int) -> bool:
        if i >= 0:
            return False
        if min_value := options.get('s32_min_value'):
            return i > min_value
        return True

    return try_get_dword(buffer, '>i', result_filter, 'int', '{}')


def get_dword_hex(buffer: bytearray) -> Tuple[Union[str, List[str], None], bytearray]:
    if len(buffer) < 4:
        return None, buffer
    return f"4byte 0x{buffer[:4].hex().upper()}", buffer[4:]


def is_printable(b: int) -> bool:
    return 0x20 <= b < 0x80


def is_valid_char(b: int) -> bool:
    line_feed = 0xA
    return is_printable(b) or b == line_feed or b == 0


def try_get_ascii(buffer: bytearray) -> Tuple[Union[str, List[str], None], bytearray]:
    length = 0

    if buffer[0] == 0:
        return None, buffer

    for b in buffer:
        if not is_valid_char(b):
            return None, buffer

        if b == 0:
            break
        else:
            length += 1

    instruction = 'ascii'

    if length <= 0 or ((min_len := options.get('min_ascii_len')) and length < min_len):
        return None, buffer

    decode = buffer[:length].decode("ascii").replace('\\', '\\\\').replace('\n', '\\n')

    end = ceil(length / 4) * 4
    alignment = end - length
    if alignment == 1:
        alignment = 0
        instruction = 'asciz'

    result = [f'{instruction} "{decode}"']
    if alignment != 0:
        result.append('balign 4')

    return result, buffer[end:]


def take_buffer(buffer: bytearray) -> Tuple[Union[str, List[str], None], bytearray]:
    try_funcs = [
        try_get_ascii if options.get('find_ascii') else None,
        try_get_zero if options.get('zero') else None,
        try_get_f32 if options.get('find_f32') else None,
        try_get_s32 if options.get('find_s32') else None,
        try_get_u32 if options.get('find_u32') else None,
        get_dword_hex
    ]
    active_funcs = filter(lambda fn: fn is not None, try_funcs)
    eval_funcs = map(lambda fn: fn(buffer), active_funcs)
    where_has_value = filter(lambda pair: pair[0], eval_funcs)
    return next(where_has_value, (None, bytearray()))


def write_buffer(f: TextIO, buffer: bytearray, indent: str):
    while len(buffer) > 0:
        value, buffer = take_buffer(buffer)
        if not value:
            continue
        if not isinstance(value, list):
            value = [value]
        for e in value:
            f.write(f'{indent}.{e}\n')


def read_match(match: Match[str] | None):
    if not match:
        return None

    result = match['hex']
    if result:
        return result

    if match['null']:
        if options.get('zero'):
            return '0' * 8

    return None


def main():
    path = Path(options['input_file'])

    with open(path, "r") as f:
        text = f.readlines()
        text.append('')

    with open(path, "w") as f:
        indent: str | None = None
        reading: bool = False
        buffer: bytearray

        for i, line in enumerate(text):
            match = dword_re.match(line)

            value = read_match(match)
            if value:
                if not reading:
                    buffer = bytearray()
                    reading = True
                if not indent:
                    indent = match['indent']
                buffer += bytearray.fromhex(value)
            else:
                if reading:
                    reading = False
                    write_buffer(f, buffer, indent)
                    indent = None
                f.write(line)


if __name__ == "__main__":
    main()
