from elftools.elf.elffile import ELFFile
f = open(debug_elf, "rb")
e = ELFFile(f)
symtab = e.get_section_by_name(".symtab")
symbols = [x for x in symtab.iter_symbols()]

for fname in asm_files:
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