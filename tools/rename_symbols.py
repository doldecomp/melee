import re
from pathlib import Path
from re import Match
from elftools.elf.elffile import ELFFile
from elftools.elf.sections import Symbol

root = Path(__file__) / '../../'
debug_elf = root / 'expected/build/ssbm.us.1.2/main.elf'
src = root / 'src'
asm = root / 'asm'
target_files = [*asm.glob('**/*.s'),
                *src.glob('**/*.c'),
                *src.glob('**/*.h')]
target_files = filter(lambda p: p.suffix not in ['.s.s', '.s.c', '.c.s'], target_files)
target_files = map(lambda p: p.resolve(), target_files)
target_files = list(target_files)

illegal_names = set(['_ctors', '_dtors', '_eti_init_info', '_SDA_BASE_'])


def filter_symbol(symbol: Symbol):
    return symbol.entry.st_info.bind != "STB_LOCAL" and symbol.name not in illegal_names


def get_key(symbol: Symbol):
    return f'{symbol.entry.st_value:08X}'


with open(debug_elf, "rb") as f:
    e = ELFFile(f)
    symbol_table = e.get_section_by_name(".symtab")
    symbols = symbol_table.iter_symbols()
    symbols = filter(filter_symbol, symbols)
    symbols = dict((get_key(s), s.name) for s in symbols)

name_re = re.compile(r"\b(?:lbl|func)_(?P<addr>[\dA-F]{8})\b")


def get_new_name(m: Match):
    addr = m['addr']
    result = symbols.get(addr, m[0])
    if result != m[0]:
        print(f'{m[0]} -> {result}')
    return result


for file in target_files:
    with open(file, "r") as f:
        text = f.read()

    new_text = name_re.sub(get_new_name, text)

    if text != new_text:
        with open(file, "w") as f:
            f.write(new_text)
