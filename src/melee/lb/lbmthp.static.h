#ifndef __GALE01_01E8F8
#define __GALE01_01E8F8

#include "lbmthp.h" // IWYU pragma: export

#include <dolphin/os/OSAlarm.h>

/* 4333E0 */ static struct lbl_804333E0_t lbl_804333E0;
#define Movieplayer lbl_804333E0
/* 4D7CC0 */ static float lb_804D7CC0;

/* 4D7CE0 */ static float lbl_804D7CE0;

struct lbl_803BAFE8_t {
    /* 0x00 */ s32 x0;
    /* 0x04 */ u16 x4;
    /* 0x06 */ u16 x6;
    /* 0x08 */ s32 x8;
    /* 0x0C */ s32 xC;
    /* 0x10 */ s32 x10;
    /* 0x14 */ s32 x14;
}; /* size = 0x18 */

typedef struct lbMthp_DataBlock {
    /* 0x000 */ char file[0xC];
    /* 0x00C */ char assert_cancelflag[0xC];
    /* 0x018 */ char report_filnum[0x24];
    /* 0x03C */ char assert_curr_packed_size[0x28];
    /* 0x064 */ char warning_frame_offsets[0x28];
    /* 0x08C */ char warning_file_format[0x2C];
    /* 0x0B8 */ char report_by_sugano[0x18];
    /* 0x0D0 */ char report_base[0xC];
    /* 0x0DC */ char report_size[0xC];
    /* 0x0E8 */ char report_count[0xC];
    /* 0x0F4 */ char report_csizep[0xC];
    /* 0x100 */ char report_magic[0x18];
    /* 0x118 */ char report_version[0x18];
    /* 0x130 */ char report_buf_size[0x18];
    /* 0x148 */ char report_x_size[0x18];
    /* 0x160 */ char report_y_size[0x18];
    /* 0x178 */ char report_framerate[0x1C];
    /* 0x194 */ char report_num_frames[0x1C];
    /* 0x1B0 */ char report_first_frame[0x1C];
    /* 0x1CC */ char report_frame_offsets[0x1C];
    /* 0x1E8 */ char report_first_frame_size[0x20];
    /* 0x208 */ char assert_movieplayer_power[0x14];
    /* 0x21C */ char assert_heap_size[0x1C];
    /* 0x238 */ struct lbl_803BAFE8_t sobj_desc;
} lbMthp_DataBlock;
STATIC_ASSERT(sizeof(lbMthp_DataBlock) == 0x250);

/* 3BADB0 */ static char lbl_803BADB0[9] = "lbmthp.c";
/* 3BADBC */ static char lbl_803BADBC[0xC] = "!cancelflag";
/* 3BADC8 */ static char lbl_803BADC8[0x22] =
    "filnum = %d, ofs = %d, by sugano.";
/* 3BADEC */ static char lbl_803BADEC[0x27] =
    "(u32)streamPlayer->currPackedSize != 0";
/* 3BAE14 */ static char str_Warning_frame_offsets_not_supported[0x27] =
    "Warning : frame offsets not supported\n";
/* 3BAE3C */ static char lbl_803BAE3C[0x2C] =
    "Warning : file format is newer than player\n";
/* 3BAE68 */ static char lbl_803BAE68[0x16] = "by sugano & yoshiki.\n";
/* 3BAE80 */ static char lbl_803BAE80[0x9] = "base %x\n";
/* 3BAE8C */ static char lbl_803BAE8C[0x9] = "size %d\n";
/* 3BAE98 */ static char lbl_803BAE98[0xA] = "count %d\n";
/* 3BAEA4 */ static char lbl_803BAEA4[0xB] = "csizep %x\n";
/* 3BAEB0 */ static char lbl_803BAEB0[0x15] = "[LbMthp] magic = %s\n";
/* 3BAEC8 */ static char lbl_803BAEC8[0x17] = "[LbMthp] version = %d\n";
/* 3BAEE0 */ static char lbl_803BAEE0[0x17] = "[LbMthp] bufSize = %d\n";
/* 3BAEF8 */ static char lbl_803BAEF8[0x15] = "[LbMthp] xSize = %d\n";
/* 3BAF10 */ static char lbl_803BAF10[0x15] = "[LbMthp] ySize = %d\n";
/* 3BAF28 */ static char lbl_803BAF28[0x19] = "[LbMthp] framerate = %d\n";
/* 3BAF44 */ static char lbl_803BAF44[0x19] = "[LbMthp] numFrames = %d\n";
/* 3BAF60 */ static char lbl_803BAF60[0x1A] = "[LbMthp] firstFrame = %d\n";
/* 3BAF7C */ static char lbl_803BAF7C[0x1C] = "[LbMthp] frameOffsets = %d\n";
/* 3BAF98 */ static char lbl_803BAF98[0x1E] = "[LbMthp] firstFrameSize = %d\n";
/* 3BAFB8 */ static char lbl_803BAFB8[0x13] = "!MoviePlayer.power";
/* 3BAFCC */ static char lbl_803BAFCC[0x1C] = "heap_size >= memoryRequired";
/* 3BAFE8 */ static struct lbl_803BAFE8_t lbMthp_803BAFE8 = {
    0, 0x280, 0x1E0, 6, 0, 0, 0,
};

#define lbl_803BAFE8 (((lbMthp_DataBlock*) lbl_803BADB0)->sobj_desc)

/* 4D3830 */ static SDATA char str_0[] = "0";
/* 4D3834 */ extern s32 lbl_804D3834;

#endif
