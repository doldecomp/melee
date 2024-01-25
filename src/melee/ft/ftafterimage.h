#ifndef GALE01_0C2600
#define GALE01_0C2600

#include <platform.h>
#include "ft/forward.h"
#include <dolphin/mtx/forward.h>

#include <placeholder.h>
#include <dolphin/mtx/types.h>

struct _m2c_stack_ftCo_800C2600 {
    /* 0x000 */ char pad_0[0x24];
    /* 0x024 */ float sp24;
    /* 0x028 */ char pad_28[0x1C];
    /* 0x044 */ Vec3 sp44;
    /* 0x050 */ Vec3 sp50;
    /* 0x05C */ Vec3 sp5C;
    /* 0x068 */ Vec3 sp68;
    /* 0x074 */ Vec3 sp74;
    /* 0x080 */ u8 sp80;    /* inferred */
    /* 0x081 */ u8 sp81;    /* inferred */
    /* 0x082 */ u8 sp82;    /* inferred */
    /* 0x083 */ u8 sp83;    /* inferred */
    /* 0x084 */ UNK_T sp84; /* inferred */
    /* 0x084 */ char pad_84[0x10];
    /* 0x094 */ Vec3 sp94;          /* inferred */
    /* 0x0A0 */ u8 spA0;            /* inferred */
    /* 0x0A1 */ u8 spA1;            /* inferred */
    /* 0x0A2 */ u8 spA2;            /* inferred */
    /* 0x0A3 */ u8 spA3;            /* inferred */
    /* 0x0A4 */ char pad_A4[0x950]; /* maybe part of spA3[0x951]? */
    /* 0x9F4 */ float sp9F4;        /* inferred */
    /* 0x9F8 */ float sp9F8;        /* inferred */
    /* 0x9FC */ char pad_9FC[8];    /* maybe part of sp9F8[3]? */
    /* 0xA04 */ float spA04;        /* inferred */
    /* 0xA08 */ f64 spA08;          /* inferred */
    /* 0xA10 */ f64 spA10;          /* inferred */
    /* 0xA18 */ f64 spA18;          /* inferred */
    /* 0xA20 */ char pad_A20[0xE8];
}; /* size = 0xB10 */

/* generated */ extern jtbl_t jtbl_803C6C00;
/* label */ extern void lbl_800C27C0(void);
/* label */ extern void lbl_800C27C8(void);
/* label */ extern void lbl_800C27B4(void);

/* generated */ extern jtbl_t jtbl_803C6C54;
/* label */ extern void lbl_800C30CC(void);
/* label */ extern void lbl_800C30D4(void);
/* label */ extern void lbl_800C30C0(void);

/* 0C2600 */ void ftCo_800C2600(Fighter_GObj* gobj, u32 arg1);
/* 0C2FD8 */ void ftCo_800C2FD8(Fighter_GObj* gobj);

#endif
