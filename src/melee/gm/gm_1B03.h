#ifndef MELEE_GM_1B03_H
#define MELEE_GM_1B03_H

#include <placeholder.h>

#include <melee/gm/forward.h>
#include <melee/mn/forward.h>
#include <sysdolphin/baselib/forward.h>

struct gm_801B0FF8_arg0_x10_t {
    /* +0 */ s8 x0;
    /* +1 */ s8 x1;
    /* +2 */ s8 x2;
};

struct gm_8049E548_t {
    /* 0x00 */ char c_kind[4];
    /* 0x04 */ u8 x4[4];
    /* 0x08 */ u8 unk_8;
    /* 0x09 */ u8 unk_9;
    /* 0x0A */ s8 unk_A;
    /* 0x0B */ char pad_B[1];
    /* 0x0C */ u16 unk_C; ///< InternalStageId
    /* 0x0E */ s8 unk_E; /* inferred */
    /* 0x0F */ char pad_F[1];
}; /* size = 0x10 */
STATIC_ASSERT(sizeof(struct gm_8049E548_t) == 0x10);

/* 1B0348 */ void gm_801B0348(StartMeleeData*); /// Character tints?
/* 1B0474 */ void gm_801B0474(StartMeleeData*, MatchEnd*);
/* 1B05F4 */ void gm_801B05F4(PlayerInitData*, int);
/* 1B0620 */ void gm_801B0620(PlayerInitData*, u8 c_kind, u8 color, u8 stocks,
                              u8);
/* 1B0664 */ void gm_801B0664(PlayerInitData*, u8 c_kind, u8 color, u8 stocks,
                              u8);
/* 1B06B0 */ void gm_801B06B0(CSSData*, u8 match_type, s8 c_kind, s8 stocks,
                              s8 color, u8, u8 cpu_level, u8 slot);
/* 1B0730 */ void gm_801B0730(CSSData*, s8*, s8*, u8*, s8*, u8*);
/* 1B07B4 */ void gm_801B07B4(CSSData*, s8, s8, s8, u8, u8, u8);
/* 1B07E8 */ void gm_801B07E8(CSSData*, s8*, s8*, s8*, s8*, u8*);
/* 1B087C */ void gm_801B087C(MinorScene*);
/* 1B089C */ void gm_801B089C(MinorScene*);
/* 1B099C */ void gm_801B099C(MinorScene*);
/* 1B09C0 */ void gm_801B09C0(MinorScene*);
/* 1B09F8 */ int fn_801B09F8(int);
/* 1B0A34 */ void gm_801B0A34(MinorScene*);
/* 1B0A8C */ int fn_801B0A8C(int);
/* 1B0AC8 */ void gm_801B0AC8(MinorScene*);
/* 1B0B00 */ void gm_801B0B00(MinorScene*);
/* 1B0B24 */ void gm_801B0B24(MinorScene*);
/* 1B0B48 */ void gm_801B0B48(MinorScene*);
/* 1B0B8C */ void gm_801B0B8C(MinorScene*);
/* 1B0BF0 */ void gm_801B0BF0(MinorScene*);
/* 1B0C18 */ void gm_801B0C18(MinorScene*);
/* 1B0C50 */ void gm_801B0C50(MinorScene*);
/* 1B0C74 */ void gm_801B0C74(MinorScene*);
/* 1B0CF0 */ void gm_801B0CF0(MinorScene*);
/* 1B0DD0 */ void gm_801B0DD0(MinorScene*);
/* 1B0F1C */ void gm_801B0F1C(MinorScene*);
/* 1B0F60 */ void gm_801B0F60(MinorScene*);
/* 1B0F90 */ void gm_801B0F90(MinorScene*);
/* 1B0FB8 */ void gm_801B0FB8(MinorScene*);
/* 1B0FF8 */ void gm_801B0FF8(MinorScene*);
/* 1B138C */ void gm_801B138C(MinorScene*);
/* 1B13B8 */ void gm_801B13B8(MinorScene*);
/* 1B14A0 */ void gm_801B14A0(MinorScene*);
/* 1B14DC */ void gm_801B14DC(MinorScene*);
/* 1B1514 */ void gm_801B1514(MinorScene*);
/* 1B154C */ void gm_801B154C(MinorScene*);
/* 1B1588 */ void gm_801B1588(MinorScene*);
/* 1B15C8 */ void gm_801B15C8(MinorScene*);
/* 1B1648 */ void gm_801B1648(MinorScene*);
/* 1B1688 */ void gm_801B1688(MinorScene*);
/* 1B16A8 */ void gm_801B16A8(MinorScene*);
/* 1B16C8 */ void gm_801B16C8(MinorScene*);
/* 1B1724 */ void gm_801B1724(MinorScene*);
/* 1B174C */ void gm_801B174C(MinorScene*);
/* 1B1788 */ void gm_801B1788(MinorScene*);
/* 1B1810 */ void gm_801B1810(MinorScene*);
/* 1B1834 */ void gm_801B1834(MinorScene*);
/* 1B18D4 */ void gm_801B18D4(MinorScene*);
/* 1B1A2C */ void gm_801B1A2C(MinorScene*);
/* 1B1A84 */ void gm_801B1A84(MinorScene*);
/* 1B1AD4 */ void gm_801B1AD4(MinorScene*);
/* 1B1B74 */ void gm_801B1B74(MinorScene*);
/* 1B1C24 */ void gm_801B1C24(MinorScene*);
/* 1B1EB8 */ void gm_801B1EB8(MinorScene*);
/* 1B1EEC */ void gm_801B1EEC(MinorScene*);
/* 1B1F6C */ void fn_801B1F6C(int);
/* 1B1F70 */ void gm_801B1F70(MinorScene*);
/* 1B2204 */ void gm_801B2204(MinorScene*);
/* 1B2298 */ void gm_801B2298_OnInit(void);
/* 1B23C4 */ void gm_801B23C4_OnLoad(void);
/* 1B23F0 */ UNK_T gm_801B23F0(void);
/* 1B24B4 */ void gm_801B24B4(MinorScene*);
/* 1B2510 */ void gm_801B2510(MinorScene*);
/* 1B254C */ void gm_801B254C(MinorScene*);
/* 1B25D4 */ void gm_801B25D4(MinorScene*);
/* 1B26AC */ void gm_801B26AC(MinorScene*);
/* 1B2704 */ void gm_801B2704(MinorScene*);
/* 1B2790 */ void gm_801B2790(MinorScene*);
/* 1B2AF8 */ void gm_801B2AF8(MinorScene*);
/* 1B2B7C */ void gm_801B2B7C_OnInit(void);

#endif
