#ifndef SYSDOLPHIN_BASELIB_SOBJLIB_H
#define SYSDOLPHIN_BASELIB_SOBJLIB_H

#include <placeholder.h>

#include "dolphin/gx/GXStruct.h"

#include <sysdolphin/baselib/forward.h>
#include <sysdolphin/baselib/gobj.h>

extern GObjFuncs HSD_SObjLib_8040C3A4;
extern u8 HSD_SObjLib_804D7960;

struct HSD_SObj {
    /* 0x00 */ void* x0;
    /* 0x04 */ HSD_SObj* next;
    /* 0x08 */ HSD_SObj* prev;
    /* 0x0C */ HSD_GObj* gobj;
    /* 0x10 */ f32 x10;
    /* 0x14 */ f32 x14;
    /* 0x18 */ f32 x18;
    /* 0x1C */ f32 x1C;
    /* 0x20 */ f32 x20;
    /* 0x24 */ f32 x24;
    /* 0x28 */ f32 x28;
    /* 0x2C */ f32 x2C;
    /* 0x30 */ f32 x30;
    /* 0x34 */ u16 x34;
    /* 0x36 */ u16 x36;
    /* 0x38 */ GXColor x38;
    /* 0x3C */ GXColor x3C;
    /* 0x40 */ u32 x40;
    /* 0x44 */ u8 x44;
    /* 0x48 */ u32 x48;
    /* 0x4C */ void (*x4C_callback)(HSD_SObj*);
    /* 0x50 */ GXTexObj x50_texobj;
    /* 0x70 */ GXTlutObj x70_tlutobj;
    /* 0x7C */ GXTexObj x7C_texobj;
};

typedef HSD_SObj HSD_SObj_803A477C_t;

/* 3A44A4 */ void HSD_SObjLib_803A44A4(void);
/* 3A44D4 */ void HSD_SObjLib_803A44D4(HSD_GObj*, HSD_SObj*, u8);
/* 3A466C */ void HSD_SObjLib_803A466C(HSD_SObj*);
/* 3A4740 */ void HSD_SObjLib_803A4740(HSD_SObj*);
/* 3A477C */ HSD_SObj* HSD_SObjLib_803A477C(HSD_GObj*, int, int, int, u8, int);
/* 3A49E0 */ void HSD_SObjLib_803A49E0(HSD_GObj*, int);
/* 3A4A68 */ void HSD_SObjLib_803A4A68(HSD_SObj*);
/* 3A54EC */ void HSD_SObjLib_803A54EC(HSD_GObj*, int);
/* 3A55DC */ void HSD_SObjLib_803A55DC(HSD_GObj*, u16, u16, int);

#endif
