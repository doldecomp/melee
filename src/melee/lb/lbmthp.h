#ifndef GALE01_01E8F8
#define GALE01_01E8F8

#include <placeholder.h>
#include <platform.h>

#include "lb/forward.h"
#include <baselib/forward.h>

/* THPDec function declarations */
BOOL THPInit(void);
void THPDec_8032F8D4(u32, void*);
s32 THPDec_8032FD40(void* arg0, u16 height);
void THPDec_80331340(s32, void*, void*, void*, s32);
void THPDec_803313D0(s32, void*, void*, void*);
s32 THPVideoDecode(void*, void*, s32, s32, void*);

/* Struct used by fn_8001EBF0 for THP decode component init */
typedef struct THPDecComp {
    /* 0x00 */ u8 pad0[0x08];
    /* 0x08 */ u32 unk_08;
    /* 0x0C */ u32 unk_0C;
    /* 0x10 */ u32 unk_10;
    /* 0x14 */ u32 unk_14;
    /* 0x18 */ u32 unk_18;
    /* 0x1C */ u32 unk_1C;
    /* 0x20 */ u32 unk_20;
    /* 0x24 */ u32 unk_24;
    /* 0x28 */ u32 unk_28;
    /* 0x2C */ u8 pad2C[0x40 - 0x2C];
    /* 0x40 */ u32 unk_40;
    /* 0x44 */ u32 width;
    /* 0x48 */ u32 height;
    /* 0x4C */ u32* unk_4C;
    /* 0x50 */ void* unk_50;
    /* 0x54 */ void* unk_54;
    /* 0x58 */ void* unk_58;
    /* 0x5C */ u8 pad5C[0x64 - 0x5C];
    /* 0x64 */ u32 unk_64;
    /* 0x68 */ s32 unk_68;
    /* 0x6C */ s32 unk_6C;
    /* 0x70 */ s32 unk_70;
    /* 0x74 */ u32 unk_74;
    /* 0x78 */ u32 unk_78;
    /* 0x7C */ u32 unk_7C;
    /* 0x80 */ u32 unk_80;
    /* 0x84 */ u32 unk_84;
    /* 0x88 */ u32 unk_88;
    /* 0x8C */ u32 unk_8C;
    /* 0x90 */ u32 unk_90;
    /* 0x94 */ s32 unk_94;
    /* 0x98 */ s32 unk_98;
    /* 0x9C */ u32 unk_9C;
    /* 0xA0 */ u16 unk_A0;
    /* 0xA2 */ u16 unk_A2;
    /* 0xA4 */ u8 unk_A4;
    /* 0xA5 */ u8 padA5[0xA8 - 0xA5];
    /* 0xA8 */ u16 unk_A8;
    /* 0xAA */ u16 unk_AA;
    /* 0xAC */ u8 unk_AC;
    /* 0xAD */ u8 padAD[0x100 - 0xAD];
    /* 0x100 */ u32 unk_100;
    /* 0x104 */ u32 unk_104;
    /* 0x108 */ s32 unk_108;
    /* 0x10C */ s32 unk_10C;
    /* 0x110 */ s32 unk_110;
    /* 0x114 */ u8 pad114[0x11C - 0x114];
    /* 0x11C */ s32 unk_11C;
    /* 0x120 */ u32 unk_120;
    /* 0x124 */ u32 currPackedSize;
    /* 0x128 */ s32 unk_128;
    /* 0x12C */ u8 pad12C[0x130 - 0x12C];
    /* 0x130 */ s32 unk_130;
    /* 0x134 */ s32 unk_134;
    /* 0x138 */ u32 unk_138;
    /* 0x13C */ u32 unk_13C;
} THPDecComp;

/* 01E910 */ void fn_8001E910(int, int, void*, bool);
/* 01EB14 */ s32 fn_8001EB14(THPDecComp* data, const char* path);
/* 01EBF0 */ s32 fn_8001EBF0(THPDecComp* data);
/* 01ECF4 */ void fn_8001ECF4(THPDecComp* data, void* buf);
/* 01EF5C */ s32 fn_8001EF5C(THPDecComp* data);
/* 01F06C */ s32 fn_8001F06C(THPDecComp* data);
/* 01F13C */ s32 fn_8001F13C(THPDecComp* data);
/* 01F294 */ s32 fn_8001F294(void);
/* 01F2A4 */ s32 fn_8001F2A4(void);
/* 01F410 */ void lbMthp_8001F410(const char* filename, UNK_T, int, int, int);
/* 01F578 */ void lbMthp_8001F578(void);
/* 01F5C4 */ s32 lbMthp_8001F5C4(void);
/* 01F5D4 */ s32 lbMthp_8001F5D4(void);
/* 01F5E4 */ s32 lbMthp_8001F5E4(void);
/* 01F5F4 */ s32 lbMthp_8001F5F4(void);
/* 01F604 */ s32 lbMthp_8001F604(void);
/* 01F614 */ void lbMthp_8001F614(s32 arg0);
/* 01F624 */ HSD_SObj* lbMthp_8001F624(HSD_GObj*, int, int);
/* 01F67C */ void lbMthp_8001F67C(HSD_GObj*, int);
/* 01F800 */ void lbMthp_8001F800(void);
/* 01F87C */ void lbMthp_8001F87C(void);
/* 01F890 */ void* lbMthp8001F890(HSD_GObj*);
/* 01F928 */ void lbMthp8001F928(HSD_GObj*, int);
/* 01FAA0 */ UNK_RET lbMthp8001FAA0(const char* filename, int, int);

#endif
