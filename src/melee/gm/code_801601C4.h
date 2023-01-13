#ifndef MELEE_GM_CODE_801601C4_H
#define MELEE_GM_CODE_801601C4_H

#include <Runtime/platform.h>

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
void func_8016AE44(void);
void func_80160968(void);
void func_80160854(void);
void func_80168B34(void);
void func_8016B498(void);
BOOL func_80164600(void);
BOOL func_80164ABC(void);
BOOL func_8016C5C0(int pl_slot);
BOOL func_8017E068(void);
BOOL func_8016AE80(void);
BOOL func_8018841C(void);

#endif
