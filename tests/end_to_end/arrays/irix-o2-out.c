extern ? D_400120;
extern ? D_410130;

s32 test(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v1;

    sp->unk0 = (s32) D_400120.unk0;
    temp_v1 = arg0 * 4;
    sp->unk4 = (u16) D_400120.unk4;
    return (arg2 + temp_v1)->unk4 + (*(sp + arg0) * *(arg1 + temp_v1)) + *(&D_410130 + (arg0 * 2));
}
