from pathlib import Path
from elftools.elf.elffile import ELFFile
from tqdm import tqdm

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

f = open(debug_elf, "rb")
e = ELFFile(f)
symtab = e.get_section_by_name(".symtab")
symbols = [x for x in symtab.iter_symbols()]

for fname in target_files:
    f = open(fname, "r")
    file_text = f.read()
    f.close()

    for sym in tqdm(symbols):
        if sym.entry.st_info.bind != "STB_LOCAL" and sym.name != '_ctors' and sym.name != '_dtors' and sym.name != '_eti_init_info':
            hexstr = hex(sym.entry.st_value)[2:].upper()

            file_text = file_text.replace(f"lbl_{hexstr}", sym.name)
            file_text = file_text.replace(f"func_{hexstr}", sym.name)

    f = open(fname, "w")
    f.write(file_text)
    f.close()
