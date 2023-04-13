#ifndef MELEE_GM_CODE_801601C4_H
#define MELEE_GM_CODE_801601C4_H

#include <Runtime/platform.h>

struct datetime {
    u16 year;
    u8 month, day, hour, minute, second;
};

bool gm_80160968(void);
bool gm_80164600(void);
bool gm_80164840(u8);
bool gm_80164ABC(void);
bool gm_8016AE44(void);
bool gm_8016AE80(void);
bool gm_8016AEDC(void);
bool gm_8016B0B4(void);
bool gm_8016B0D4(void);
bool gm_8016B0FC(void);
bool gm_8016B168(void);
bool gm_8016B1C4(void);
bool gm_8016B1D8(void);
bool gm_8016B238(void);
bool gm_8016B3A0(void);
bool gm_8016B3D8(void);
bool gm_8016B41C(void);
bool gm_8016C5C0(int pl_slot);
bool gm_8017E068(void);
bool gm_8018841C(void);
void gm_80160854(void);
void gm_80168B34(void);
void gm_801692E8(int, struct datetime* datetime);
void gm_8016B248(void);
void gm_8016B498(void);

#endif
