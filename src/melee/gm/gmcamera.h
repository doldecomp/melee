#ifndef GALE01_1A2224
#define GALE01_1A2224

#include <placeholder.h>

#include "baselib/forward.h"

#include "dolphin/types.h"

typedef struct _gmCameraUnkStruct4 {
    /*0x00*/ bool x0;
    /*0x04*/ int x4;
    /*0x08*/ int x8;
    /*0x0C*/ int xC;
} gmCameraUnkStruct4;

typedef struct _gmCameraUnkStruct {
    /*0x00*/ void* ifvscam; ///< interface dat file loaded from 801a3254
    /*0x04*/ HSD_JObj* x4;
    /*0x08*/ HSD_JObj* x8;
    /*0x0C*/ s32 xC;
    /*0x10*/ s32 x10;
    /*0x14*/ s32 x14;
    /*0x18*/ s32 x18;
    /*0x1C*/ void* x1C;
    /*0x20*/ int x20;
    /*0x24*/ gmCameraUnkStruct4 x24[2];
    /*0x44*/ s32 x44;
    /*0x48*/ HSD_Text* x48[3];
    /*0x54*/ int x54;
} gmCameraUnkStruct;

typedef struct _gmCameraUnkFuncTable {
    /*0x00*/ struct {
        u8 x0;
        u16 x2;
    } flags;
    /*0x04*/ void (*x4)(void);
    /*0x08*/ void (*x8)(void);
} gmCameraUnkFuncTable;

/* 1A2224 */ u8* gmCamera_801A2224(u8* arg0, u32 arg1);
/* 1A2334 */ HSD_Text* gmCamera_801A2334(s32, f32, f32, f32, f32);
/* 1A253C */ void gmCamera_801A253C(s32*, s32*);
/* 1A25C8 */ UNK_RET gmCamera_801A25C8(UNK_PARAMS);
/* 1A2640 */ s32 gmCamera_801A2640(void);
/* 1A2650 */ UNK_RET gmCamera_801A2650(UNK_PARAMS);
/* 1A26C0 */ void gmCamera_801A26C0(void);
/* 1A2798 */ void gmCamera_801A2798(void);
/* 1A2800 */ void gmCamera_801A2800(void);
/* 1A28AC */ void gmCamera_801A28AC(void);
/* 1A292C */ void gmCamera_801A292C(void);
/* 1A2AAC */ void gmCamera_801A2AAC(void);
/* 1A2BB0 */ void gmCamera_801A2BB0(void);
/* 1A2BF0 */ void gmCamera_801A2BF0(void);
/* 1A2D44 */ void gmCamera_801A2D44(void);
/* 1A2FBC */ void gmCamera_801A2FBC(void);
/* 1A2FFC */ void gmCamera_801A2FFC(void);
/* 1A3048 */ void gmCamera_801A3048(s32);
/* 1A3098 */ UNK_RET gmCamera_801A3098(UNK_PARAMS);
/* 1A30E4 */ UNK_RET gmCamera_801A30E4(UNK_PARAMS);
/* 1A31D8 */ UNK_RET fn_801A31D8(HSD_GObj*);
/* 1A31FC */ UNK_RET gmCamera_801A31FC(UNK_PARAMS);

#endif
