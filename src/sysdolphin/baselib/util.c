#include <sysdolphin/baselib/util.h>

float lbl_80406DF0[] = {
    1.0f,
    0,
    0,
    0,
    0,
    1.0f,
    0,
    0,
    0,
    0,
    1.0f,
    0
};

void HSD_MulColor(GXColor* arg0, GXColor* arg1, GXColor* dest) {
    dest->u8.r = (arg0->u8.r * arg1->u8.r) / 255U;
    dest->u8.g = (arg0->u8.g * arg1->u8.g) / 255U;
    dest->u8.b = (arg0->u8.b * arg1->u8.b) / 255U;
    dest->u8.a = (arg0->u8.a * arg1->u8.a) / 255U;
}

// HSD_CountSetBits?
u32 func_8037A7EC(u32 c) {
    int ret = 0;
    int i;

    for(i = 0; i < 32; i++) {
        if ((c) & (1 << i)) {
            ret++;
        }
    }
    return ret;
}

s32 func_8037A8AC(u32 arg0) {
    switch (arg0) {
        case 0:
            return 0;
        case 1:
            return 3;
        case 2:
            return 6;
        case 3:
            return 9;
        case 4:
            return 12;
        case 5:
            return 15;
        case 6:
            return 18;
        case 7:
            return 21;
        case 8:
            return 24;
        case 9:
            return 27;
        default:
            __assert("util.c", 132, "0");
            return 0;
    }
}
