extern ? symbol;

s32 test(void) {
    s32 temp_a1;
    s32 temp_v0;

    temp_v0 = symbol.unk0 + 4;
    temp_a1 = symbol.unk4;
    symbol.unk0 = temp_a1;
    return temp_v0 + (&symbol + 8)->unk4 + temp_a1;
}
