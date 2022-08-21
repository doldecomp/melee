extern s32 glob;

void test(s8 arg0) {
    s8 temp_r5;
    s8 temp_r6;

    temp_r5 = arg0 * 2;
    glob = (s32) (s8) arg0;
    temp_r6 = arg0 * 3;
    glob = (s32) (s8) temp_r5;
    glob = (s32) (s8) temp_r6;
    glob = (s32) (s16) arg0;
    glob = (s32) (s16) temp_r5;
    glob = (s32) (s16) temp_r6;
}
