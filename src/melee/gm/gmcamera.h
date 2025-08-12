#ifndef GALE01_1A2224
#define GALE01_1A2224

#include <placeholder.h>

#include "baselib/forward.h"

#include "dolphin/types.h"

typedef struct _gmCameraUnkStruct3 {
    /*0x00*/ u8 x0_padding[0x24 - 0x0];
    /*0x24*/ float x24;
    /*0x28*/ float x28;
    /*0x2C*/ u8 x2C_padding[0x49 - 0x2C];
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
    /*0x04*/ u8 x4_padding[0x20 - 0x4];
    /*0x20*/ u32 x20;
    /*0x24*/ u32 x24;
    /*0x28*/ s32 x28;
    /*0x2C*/ u32 x2C;
    /*0x30*/ s32 x30;
    /*0x34*/ u8 pad_x34[0x38 - 0x34];
    /*0x38*/ u32 x38;
    /*0x3C*/ u8 pad_x3C[0x40 - 0x3C];
    /*0x40*/ s32 x40;
    /*0x44*/ u32 x44;
    /*0x48*/ HSD_Text* x48;
    /*0x4C*/ u8 pad_x4C[0x54 - 0x4C];
    /*0x54*/ u32 x54;
} gmCameraUnkStruct;

typedef struct _gmCameraUnkStructPtrs {
    /*0x00*/ u8 x0_padding[0x58 - 0x0];
} gmCameraUnkStruct2Ptrs;

union _gmCameraUnkUnion {
    gmCameraUnkStruct gcus;
    // gmCameraUnkStruct2* gcus2_ptrs[0x58/4];
    gmCameraUnkStruct2Ptrs gcus2_ptrs;
};

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
/* 1A26C0 */ UNK_RET gmCamera_801A26C0(UNK_PARAMS);
/* 1A2798 */ UNK_RET gmCamera_801A2798(UNK_PARAMS);
/* 1A2800 */ UNK_RET gmCamera_801A2800(UNK_PARAMS);
/* 1A28AC */ UNK_RET gmCamera_801A28AC(UNK_PARAMS);
/* 1A292C */ UNK_RET gmCamera_801A292C(UNK_PARAMS);
/* 1A2AAC */ UNK_RET gmCamera_801A2AAC(UNK_PARAMS);
/* 1A2BB0 */ UNK_RET gmCamera_801A2BB0(UNK_PARAMS);
/* 1A2BF0 */ UNK_RET gmCamera_801A2BF0(UNK_PARAMS);
/* 1A2D44 */ UNK_RET gmCamera_801A2D44(UNK_PARAMS);
/* 1A2FBC */ UNK_RET gmCamera_801A2FBC(UNK_PARAMS);
/* 1A2FFC */ UNK_RET gmCamera_801A2FFC(UNK_PARAMS);
/* 1A3048 */ UNK_RET gmCamera_801A3048(UNK_PARAMS);
/* 1A3098 */ UNK_RET gmCamera_801A3098(UNK_PARAMS);
/* 1A30E4 */ UNK_RET gmCamera_801A30E4(UNK_PARAMS);
/* 1A31D8 */ UNK_RET fn_801A31D8(UNK_PARAMS);
/* 1A31FC */ UNK_RET gmCamera_801A31FC(UNK_PARAMS);
/* 1A33BC */ void gmCamera_801A33BC(void);
/* 1A34FC */ void gmCamera_801A34FC_OnFrame(void);
/* 1A3634 */ void gmCamera_801A3634_OnEnter(UNK_T);
/* 1A367C */ void gmCamera_801A367C_OnLeave(UNK_T);

#endif
