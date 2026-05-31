#ifndef GALE01_01E8F8
#define GALE01_01E8F8

#include <placeholder.h>
#include <platform.h>

#include "lb/forward.h"
#include <baselib/forward.h>

#include <dolphin/gx/GXStruct.h>
#include <dolphin/thp/thp.h>

/* THPDec function declarations */
BOOL THPInit(void);
s32 THPDec_8032F8D4(u32, void*);
s32 THPDec_8032FD40(THPDec_8032FD40_Data* arg0, u16 height);
void THPDec_80331340(s32, void*, void*, void*, s32);
void THPDec_803313D0(s32, void*, void*, void*);
s32 THPVideoDecode(void*, void*, void*, void*, void*);

/* Struct used by fn_8001EBF0 for THP decode component init */
typedef struct THPDecComp {
    /* 0x00 */ u8 pad0[0x08];
    /* 0x08 */ u32 version;
    /* 0x0C */ u32 buf_size;
    /* 0x10 */ u32 x_size;
    /* 0x14 */ u32 y_size;
    /* 0x18 */ u32 frame_rate;
    /* 0x1C */ u32 num_frames;
    /* 0x20 */ u32 first_frame;
    /* 0x24 */ u32 frame_offsets;
    /* 0x28 */ u32 first_frame_size;
    /* 0x2C */ u8 pad2C[0x40 - 0x2C];
    /* 0x40 */ u32 unk_40;
    /* 0x44 */ u32 width;
    /* 0x48 */ u32 height;
    /* 0x4C */ u32* frame_buffers;
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
    /* 0x9C */ THPDec_8032FD40_Data unk_9C;
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
    /* 0x120 */ u32 curr_file_offset;
    /* 0x124 */ u32 currPackedSize;
    /* 0x128 */ s32 file_entrynum;
    /* 0x12C */ u8 pad12C[0x130 - 0x12C];
    /* 0x130 */ s32 unk_130;
    /* 0x134 */ s32 unk_134;
    /* 0x138 */ u32 unk_138;
    /* 0x13C */ u32 unk_13C;
} THPDecComp;

struct lbl_804333E0_t {
    /* 0x000 */ char pad_0[0x20];
    /* 0x020 */ u32 unk_20;
    /* 0x024 */ char pad_24[0x1C];
    /* 0x040 */ u32 unk_40;
    /* 0x044 */ u32 unk_44;
    /* 0x048 */ u32 unk_48;
    /* 0x04C */ void** frame_buffers;
    /* 0x050 */ void* unk_50;
    /* 0x054 */ void* unk_54;
    /* 0x058 */ void* unk_58;
    /* 0x05C */ char pad_5C[0xC];
    /* 0x068 */ s32 unk_68;
    /* 0x06C */ char pad_6C[0x4];
    /* 0x070 */ s32 unk_70;
    /* 0x074 */ u32 unk_74;
    /* 0x078 */ s32 unk_78;
    /* 0x07C */ s32 unk_7C;
    /* 0x080 */ s32 unk_80;
    /* 0x084 */ s32 unk_84;
    /* 0x088 */ s32 unk_88;
    /* 0x08C */ u32 unk_8C;
    /* 0x090 */ s32 unk_90;
    /* 0x094 */ char pad_94[0x70];
    /* 0x104 */ u32 unk_104;
    /* 0x108 */ s32 unk_108;
    /* 0x10C */ s32 unk_10C;
    /* 0x110 */ s32 unk_110;
    /* 0x114 */ char pad_114[0xC];
    /* 0x120 */ u32 curr_file_offset;
    /* 0x124 */ u32 currPackedSize;
    /* 0x128 */ s32 file_entrynum;
    /* 0x12C */ u32* rate_table;
    /* 0x130 */ s32 unk_130;
    /* 0x134 */ s32 unk_134;
    /* 0x138 */ s32 unk_138;
    /* 0x13C */ u32 unk_13C;
    /* 0x140 */ void* unk_140;
    /* 0x144 */ s32 unk_144;
    /* 0x148 */ s32 unk_148;
    /* 0x14C */ s32 power;
    /* 0x150 */ OSAlarm unk_150;
    /* 0x178 */ GXTexObj unk_178;
    /* 0x198 */ GXTexObj unk_198;
    /* 0x1B8 */ GXTexObj unk_1B8;
}; /* size = 0x1D8 */
STATIC_ASSERT(sizeof(struct lbl_804333E0_t) == 0x1D8);

/* 01E910 */ void fn_8001E910(int, int, void*, int);
/* 01EB14 */ s32 fn_8001EB14(THPDecComp* data, const char* path);
/* 01EBF0 */ s32 fn_8001EBF0(THPDecComp* data);
/* 01ECF4 */ void fn_8001ECF4(THPDecComp* data, void* buf);
/* 01EF5C */ s32 fn_8001EF5C(THPDecComp* data);
/* 01F06C */ s32 fn_8001F06C(THPDecComp* data);
/* 01F13C */ s32 fn_8001F13C(THPDecComp* data);
/* 01F294 */ s32 fn_8001F294(void);
/* 01F2A4 */ s32 fn_8001F2A4(void);
/* 01F410 */ void lbMthp_8001F410(const char* filename, void* rate_table,
                                  int buf, int heap_size, int loop);
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
