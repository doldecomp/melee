#ifndef GALE01_1D84A0
#define GALE01_1D84A0

#include <melee/gr/forward.h>

#include <dolphin/mtx.h>

/* 1D84A4 */ void grZebes_801D84A4(void);
/* 1D8644 */ void grZebes_801D8644(HSD_GObj*);
/* 1D881C */ void grZebes_801D881C(HSD_GObj*);
/* 1D9100 */ void grZebes_801D9100(HSD_GObj*);
/* 1D925C */ void grZebes_801D925C(HSD_GObj*);
/* 1D9508 */ void grZebes_801D9508(Ground_GObj*);
/* 1D9758 */ void grZebes_801D9758(Ground_GObj*);
/* 1D9798 */ void grZebes_801D9798(HSD_GObj*);
/* 1D99E0 */ void grZebes_801D99E0(HSD_GObj*);
/* 1D9F30 */ void grZebes_801D9F30(Ground_GObj*);
/* 1D9F84 */ void grZebes_801D9F84(Ground_GObj*);
/* 1DA3F4 */ void grZebes_801DA3F4(Vec3*);
/* 1DA4FC */ void grZebes_801DA4FC(Ground_GObj*);
/* 1DB088 */ s32 grZebes_801DB088(Ground*, s32);
/* 1DCB64 */ bool grZebes_801DCB64(Vec3*, int);
/* 1DCBB0 */ bool grZebes_801DCBB0(Vec3*, int);
/* 1DCBFC */ bool grZebes_801DCBFC(Ground_GObj*, HSD_GObj*, void*);
/* 1DCCC8 */ float grZebes_801DCCC8(void);
/*3E1B2C */ extern StageData grZe_StageData;

typedef struct grZe_AcidLevelEntry {
    /* +0 */ s16 x0_base;
    /* +2 */ s16 x2_delay_min;
    /* +4 */ s16 x4_delay_max;
    /* +6 */ s16 x6_level;
} grZe_AcidLevelEntry;

typedef struct grZe_YakumonoParam {
    /* 0x00 */ f32 x00;
    /* 0x04 */ f32 x04;
    /* 0x08 */ f32 x08;
    /* 0x0C */ f32 x0C;
    /* 0x10 */ s32 x10;
    /* 0x14 */ u8 pad_14[0x2C - 0x14];
    /* 0x2C */ void* x2C;
    /* 0x30 */ f32 x30;
    /* 0x34 */ f32 x34;
    /* 0x38 */ f32 x38;
    /* 0x3C */ f32 x3C;
    /* 0x40 */ f32 x40;
    /* 0x44 */ f32 x44;
    /* 0x48 */ f32 x48;
    /* 0x4C */ f32 x4C;
    /* 0x50 */ f32 x50;
    /* 0x54 */ f32 x54;
    /* 0x58 */ f32 x58;
    /* 0x5C */ f32 x5C;
    /* 0x60 */ f32 x60;
    /* 0x64 */ f32 x64;
    /* 0x68 */ f32 x68;
    /* 0x6C */ f32 x6C;
    /* 0x70 */ f32 x70;
    /* 0x74 */ f32 x74;
    /* 0x78 */ f32 x78;
    /* 0x7C */ f32 x7C;
    /* 0x80 */ f32 x80;
    /* 0x84 */ f32 x84;
    /* 0x88 */ f32 x88;
    /* 0x8C */ f32 x8C;
    /* 0x90 */ f32 x90;
    /* 0x94 */ f32 x94;
    /* 0x98 */ f32 x98;
    /* 0x9C */ f32 x9C;
    /* 0xA0 */ grZe_AcidLevelEntry xA0_entries[30];
} grZe_YakumonoParam;

#endif
