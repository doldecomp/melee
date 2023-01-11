#ifndef MELEE_GM_CODE_801601C4_H
#define MELEE_GM_CODE_801601C4_H

#include <dolphin/types.h>

struct datetime {
    u16 year;
    u8 month, day, hour, minute, second;
};

BOOL func_80164840(u8);
BOOL func_8016AEDC(void);
BOOL func_8016B0FC(void);
BOOL func_8016B1C4(void);
BOOL func_8016B238(void);
BOOL func_8016B3A0(void);
BOOL func_8016B41C(void);
BOOL func_8016B0B4(void);
BOOL func_8016B168(void);
void func_801692E8(int, struct datetime* datetime);
BOOL func_8016B3D8(void);

#endif
