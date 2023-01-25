extern ? symbol;

s32 test(void) {
    s32 temp_v0;

    temp_v0 = symbol.unk0 + 4;
    symbol.unk0 = (s32) symbol.unk4;
    return temp_v0 + (&symbol + 8)->unk4 + symbol.unk4;
}
