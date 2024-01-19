s32 func_00400090(s32);                             /* static */

s32 test(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp24;
    s32 sp20;
    s32 sp1C;

    sp24 = arg0 + arg1;
    sp20 = arg1 + arg2;
    sp1C = arg2 + arg3;
    if ((sp24 != 0) && (sp20 != 0) && (sp1C != 0)) {
        sp24 = func_00400090(sp24 + arg0);
        if (sp24 >= 0xB) {
            sp24 = func_00400090(sp24 + arg1);
            sp20 = func_00400090(sp20 + arg2);
            sp1C = func_00400090(sp1C + arg3);
            if ((sp24 != 0) && (sp20 != 0) && (sp1C != 0)) {
                return 1;
            }
        }
    }
    return 0;
}
