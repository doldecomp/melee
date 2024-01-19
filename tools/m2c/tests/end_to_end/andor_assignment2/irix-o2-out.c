s32 func_00400090(s32, s32, s32, s32);              /* static */

s32 test(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp2C;
    s32 sp28;
    s32 sp1C;
    s32 sp18;
    s32 temp_a3;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;

    temp_v0 = arg0 + arg1;
    if (temp_v0 != 0) {
        temp_a3 = arg1 + arg2;
        if (temp_a3 != 0) {
            temp_v1 = arg2 + arg3;
            if (temp_v1 != 0) {
                sp18 = temp_v1;
                sp1C = temp_a3;
                temp_v0_2 = func_00400090(temp_v0 + arg0, temp_a3);
                if (temp_v0_2 >= 0xB) {
                    sp1C = temp_a3;
                    sp2C = func_00400090(temp_v0_2 + arg1, arg1, arg2, temp_a3);
                    sp28 = func_00400090(temp_a3 + arg2);
                    temp_v0_3 = func_00400090(sp18 + arg3);
                    if ((sp2C != 0) && (sp28 != 0) && (temp_v0_3 != 0)) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
