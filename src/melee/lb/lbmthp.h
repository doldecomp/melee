#ifndef GALE01_01E8F8
#define GALE01_01E8F8

#include <placeholder.h>
#include <platform.h>

#include "lb/forward.h"
#include <baselib/forward.h>

/* THPDec function declaration */
s32 THPDec_8032FD40(void* arg0, u16 height);

/* Struct used by fn_8001EBF0 for THP decode component init */
typedef struct THPDecComp {
    /* 0x00 */ u8 pad0[0x40];
    /* 0x40 */ u32 unk_40;
    /* 0x44 */ u32 width;
    /* 0x48 */ u32 height;
    /* 0x4C */ u8 pad4C[0x68 - 0x4C];
    /* 0x68 */ u32 unk_68;
    /* 0x6C */ u8 pad6C[0x78 - 0x6C];
    /* 0x78 */ u32 unk_78;
    /* 0x7C */ u32 unk_7C;
    /* 0x80 */ u32 unk_80;
    /* 0x84 */ u32 unk_84;
    /* 0x88 */ u32 unk_88;
    /* 0x8C */ u8 pad8C[0x90 - 0x8C];
    /* 0x90 */ u32 unk_90;
    /* 0x94 */ s32 unk_94;
    /* 0x98 */ u8 pad98[0x9C - 0x98];
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
} THPDecComp;

/* 01E910 */ UNK_RET fn_8001E910(UNK_PARAMS);
/* 01EB14 */ UNK_RET fn_8001EB14(UNK_PARAMS);
/* 01EBF0 */ s32 fn_8001EBF0(THPDecComp* data);
/* 01ECF4 */ UNK_RET fn_8001ECF4(UNK_PARAMS);
/* 01EF5C */ UNK_RET fn_8001EF5C(UNK_PARAMS);
/* 01F06C */ UNK_RET fn_8001F06C(UNK_PARAMS);
/* 01F13C */ UNK_RET fn_8001F13C(UNK_PARAMS);
/* 01F294 */ s32 fn_8001F294(void);
/* 01F2A4 */ UNK_RET fn_8001F2A4(UNK_PARAMS);
/* 01F410 */ void lbMthp_8001F410(const char* filename, UNK_T, int, int, int);
/* 01F578 */ UNK_RET lbMthp_8001F578(UNK_PARAMS);
/* 01F5C4 */ s32 lbMthp_8001F5C4(void);
/* 01F5D4 */ s32 lbMthp_8001F5D4(void);
/* 01F5E4 */ s32 lbMthp_8001F5E4(void);
/* 01F5F4 */ s32 lbMthp_8001F5F4(void);
/* 01F604 */ s32 lbMthp_8001F604(void);
/* 01F614 */ void lbMthp_8001F614(s32 arg0);
/* 01F624 */ HSD_SObj_803A477C_t* lbMthp_8001F624(HSD_GObj*, int, int);
/* 01F67C */ void lbMthp_8001F67C(HSD_GObj*, int);
/* 01F800 */ void lbMthp_8001F800(void);
/* 01F87C */ void lbMthp_8001F87C(void);
/* 01F890 */ UNK_T lbMthp8001F890(HSD_GObj*);
/* 01F928 */ void lbMthp8001F928(HSD_GObj*, int);
/* 01FAA0 */ UNK_RET lbMthp8001FAA0(const char* filename, int, int);

#endif
