#ifndef GALE01_1A2224
#define GALE01_1A2224

#include <placeholder.h>

#include "baselib/forward.h"

#include "dolphin/types.h"

typedef struct _gmCameraUnkStruct3 {
    /*0x00*/ u8 x0_padding[0x24 - 0x0];
    /*0x24*/ s32 x24;
    /*0x28*/ s32 x28;
    /*0x2C*/ s32 x2C;
    /*0x30*/ u8 x30_padding[0x49 - 0x30];
    /*0x49*/ u8 x49;
} gmCameraUnkStruct3;

typedef struct _gmCameraUnkStruct2 {
    /*0x00*/ u8 x0_padding[0x24 - 0x0];
    /*0x24*/ u32 x24;
    /*0x28*/ u32 x28;
    /*0x2C*/ int x2C;
    /*0x30*/ u32 x30;
} gmCameraUnkStruct2;

typedef struct _gmCameraUnkStruct {
    /*0x00*/ void* ifvscam; ///< interface dat file loaded from 801a3254
    /*0x04*/ HSD_JObj* x4;
    /*0x08*/ HSD_JObj* x8;
    /*0x0C*/ s32 xC;
    /*0x10*/ s32 x10;
    /*0x14*/ s32 x14;
    /*0x18*/ u32 x18;
    /*0x1C*/ void* x1C;
    /*0x20*/ u32 x20;
    /*0x24*/ u32 x24;
    /*0x28*/ s32 x28;
    /*0x2C*/ u32 x2C;
    /*0x30*/ s32 x30;
    /*0x34*/ u8 pad_x34[0x38 - 0x34];
    /*0x38*/ u32 x38;
    /*0x3C*/ u8 pad_x3C[0x40 - 0x3C];
    /*0x40*/ s32 x40;
    /*0x44*/ s32 x44;
    /*0x48*/ HSD_Text* x48[3];
    /*0x54*/ u32 x54;
} gmCameraUnkStruct;

typedef struct _gmCameraUnkStruct2Ptrs {
    /*0x00*/ u8 x0_padding[0x58 - 0x0];
} gmCameraUnkStruct2Ptrs;

typedef struct _gmCameraUnkStruct4 {
    /*0x00*/ bool x0;
    /*0x04*/ u32 x4;
    /*0x08*/ u32 x8;
    /*0x0C*/ u32 xC;
} gmCameraUnkStruct4;

typedef struct _gmCameraUnkStruct4Ptrs {
    /*0x00*/ u8 x0_padding[0x24 - 0x0];
    /*0x24*/ gmCameraUnkStruct4 x24[2];
} gmCameraUnkStruct4Ptrs;

union _gmCameraUnkUnion {
    gmCameraUnkStruct gcus;
    // gmCameraUnkStruct2* gcus2_ptrs[0x58/4];
    gmCameraUnkStruct2Ptrs gcus2_ptrs;
    gmCameraUnkStruct4Ptrs gcus4;
};

typedef struct _gmCameraUnkFuncTable {
    /*0x00*/ struct{
                 u8 x0;
                 u8 x1;
                 u16 x2;
             } flags;
    /*0x04*/ void (*x4)(void);
    /*0x08*/ void (*x8)(void);
} gmCameraUnkFuncTable;

/* 479BC8 */ extern union _gmCameraUnkUnion gmCamera_80479BC8;
/* 4DA9B8 */ extern float gmCamera_804DA9B8;
/* 4DA9BC */ extern float gmCamera_804DA9BC;
/* 4DA9C0 */ extern float gmCamera_804DA9C0;

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
/* 1A33BC */ void gmCamera_801A33BC(void);
/* 1A34FC */ void gmCamera_801A34FC_OnFrame(void);
/* 1A3634 */ void gmCamera_801A3634_OnEnter(UNK_T);
/* 1A367C */ void gmCamera_801A367C_OnLeave(UNK_T);

/* 3DA6B4 */ extern gmCameraUnkFuncTable gmCamera_803DA6B4[];

#endif
