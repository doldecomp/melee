#ifndef SYSDOLPHIN_BASELIB_SOBJLIB_H
#define SYSDOLPHIN_BASELIB_SOBJLIB_H

#include <placeholder.h>

#include <sysdolphin/baselib/forward.h>

extern GObjFuncs HSD_SObjLib_8040C3A4;
extern u8 HSD_SObjLib_804D7960;

typedef struct HSD_SObj_803A477C_t {
    u8 pad0[0x10];
    float x10, x14;
    u8 pad18[0x3C - 0x18];
    u8 x3C, x3D, x3E, x3F;
    u8 x40;
} HSD_SObj_803A477C_t;

/* 3A44A4 */ void HSD_SObjLib_803A44A4(void);
/* 3A44D4 */ UNK_RET HSD_SObjLib_803A44D4(UNK_PARAMS);
/* 3A466C */ UNK_RET HSD_SObjLib_803A466C(UNK_PARAMS);
/* 3A4740 */ void HSD_SObjLib_803A4740(HSD_JObj*);
/* 3A477C */ HSD_SObj_803A477C_t* HSD_SObjLib_803A477C(HSD_GObj*, int, int,
                                                       int, int, int);
/* 3A49E0 */ void HSD_SObjLib_803A49E0(HSD_GObj*, int);
/* 3A4A68 */ UNK_RET HSD_SObjLib_803A4A68(UNK_PARAMS);
/* 3A54EC */ void HSD_SObjLib_803A54EC(HSD_GObj*, int);
/* 3A55DC */ void HSD_SObjLib_803A55DC(HSD_GObj*, int, int, int);

#endif
