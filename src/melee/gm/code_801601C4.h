#ifndef MELEE_GM_CODE_801601C4_H
#define MELEE_GM_CODE_801601C4_H

#include <Runtime/platform.h>

struct datetime {
    u16 year;
    u8 month, day, hour, minute, second;
};

bool func_80164840(u8);
bool func_8016AEDC(void);
bool func_8016B0FC(void);
bool func_8016B1C4(void);
bool func_8016B238(void);
bool func_8016B3A0(void);
bool func_8016B41C(void);
bool func_8016B0B4(void);
bool func_8016B168(void);
void func_801692E8(int, struct datetime* datetime);
bool func_8016B3D8(void);
void func_8016AE44(void);
void func_80160968(void);
void func_80160854(void);
void func_80168B34(void);
void func_8016B498(void);
bool func_80164600(void);
bool func_80164ABC(void);
bool func_8016C5C0(int pl_slot);
bool func_8017E068(void);
bool func_8016AE80(void);
bool func_8018841C(void);
bool func_8016B1D8(void);
bool func_8016B0D4(void);

#endif
