s32 test(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp4;
    s32 sp0;
    s32 temp_t4;

    sp0 = 0;
    if ((arg0 != 0) && ((arg1 != 0) || (arg2 != 0))) {
loop_3:
        sp0 += 1;
        if (arg0 != 0) {
            if ((arg1 != 0) || (arg2 != 0)) {
                goto loop_3;
            }
        }
    }
    if ((arg0 != 0) || ((arg1 != 0) && (arg2 != 0))) {
loop_9:
        sp0 += 1;
        if (arg0 != 0) {
            goto loop_9;
        }
        if ((arg1 != 0) && (arg2 != 0)) {
            goto loop_9;
        }
    }
    if (arg0 != 0) {
loop_13:
        sp0 += 1;
        if ((arg1 != 0) && ((arg2 != 0) || (arg3 != 0))) {
            goto block_30;
        }
        sp0 += 1;
        if ((arg1 != 0) || ((arg2 != 0) && (arg3 != 0))) {
            goto block_30;
        }
        sp0 += 1;
        if ((arg1 != 0) && ((arg2 != 0) || (arg3 != 0))) {

        } else {
            sp0 += 1;
            if ((arg1 != 0) || ((arg2 != 0) && (arg3 != 0))) {

            } else {
                sp0 += 1;
block_30:
                if (arg0 != 0) {
                    goto loop_13;
                }
            }
        }
    }
    sp4 = 0;
    if ((arg0 != 0) || (arg1 != 0)) {
loop_33:
        sp0 += 1;
        temp_t4 = sp4 + (arg2 + arg3);
        sp4 = temp_t4;
        if (temp_t4 < 0xA) {
            if ((arg0 != 0) || (arg1 != 0)) {
                goto loop_33;
            }
        }
    }
    return sp0;
}
