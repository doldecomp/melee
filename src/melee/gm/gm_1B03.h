#ifndef MELEE_GM_1B03_H
#define MELEE_GM_1B03_H

#include <placeholder.h>

#include <melee/gm/forward.h>
#include <melee/mn/forward.h>
#include <sysdolphin/baselib/forward.h>

struct gm_8049E548_t {
    /* 0x00 */ char c_kind[4];
    /* 0x04 */ u8 x4[4];
    /* 0x08 */ u8 unk_8;
    /* 0x09 */ u8 unk_9;
    /* 0x0A */ s8 unk_A;
    /* 0x0B */ char pad_B[1];
    /* 0x0C */ u16 unk_C; ///< InternalStageId
    /* 0x0E */ s8 unk_E;  /* inferred */
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
/* 1B0730 */ void gm_801B0730(CSSData*, s8* ckind, u8* stocks, u8* color,
                              u8* nametag, u8* cpu_level);
/* 1B07B4 */ void gm_801B07B4(CSSData*, s8, s8, s8, u8, u8, u8);
/* 1B07E8 */ void gm_801B07E8(CSSData*, s8*, s8*, s8*, s8*, u8*);
/* 1B087C */ void gm_801B087C(GameScene*);
/* 1B089C */ void gm_801B089C(GameScene*);
/* 1B099C */ void gm_801B099C(GameScene*);
/* 1B09C0 */ void gm_801B09C0(GameScene*);
/* 1B09F8 */ int fn_801B09F8(int);
/* 1B0A34 */ void gm_801B0A34(GameScene*);
/* 1B0A8C */ int fn_801B0A8C(int);
/* 1B0AC8 */ void gm_801B0AC8(GameScene*);
/* 1B0B00 */ void gm_801B0B00(GameScene*);
/* 1B0B24 */ void gm_801B0B24(GameScene*);
/* 1B0B48 */ void gm_801B0B48(GameScene*);
/* 1B0B8C */ void gm_801B0B8C(GameScene*);
/* 1B0BF0 */ void gm_801B0BF0(GameScene*);
/* 1B0C18 */ void gm_801B0C18(GameScene*);
/* 1B0C50 */ void gm_801B0C50(GameScene*);
/* 1B0C74 */ void gm_801B0C74(GameScene*);
/* 1B0CF0 */ void gm_801B0CF0(GameScene*);
/* 1B0DD0 */ void gm_801B0DD0(GameScene*);
/* 1B0F1C */ void gm_801B0F1C(GameScene*);
/* 1B0F60 */ void gm_801B0F60(GameScene*);
/* 1B0F90 */ void gm_801B0F90(GameScene*);
/* 1B0FB8 */ void gm_801B0FB8(GameScene*);
/* 1B0FF8 */ void gm_801B0FF8(GameScene*);
/* 1B138C */ void gm_801B138C(GameScene*);
/* 1B13B8 */ void gm_801B13B8(GameScene*);
/* 1B14A0 */ void gm_801B14A0(GameScene*);
/* 1B14DC */ void gm_801B14DC(GameScene*);
/* 1B1514 */ void gm_801B1514(GameScene*);
/* 1B154C */ void gm_801B154C(GameScene*);
/* 1B1588 */ void gm_801B1588(GameScene*);
/* 1B15C8 */ void gm_801B15C8(GameScene*);
/* 1B1648 */ void gm_801B1648(GameScene*);
/* 1B1688 */ void gm_801B1688(GameScene*);
/* 1B16A8 */ void gm_801B16A8(GameScene*);
/* 1B16C8 */ void gm_801B16C8(GameScene*);
/* 1B1724 */ void gm_801B1724(GameScene*);
/* 1B174C */ void gm_801B174C(GameScene*);
/* 1B1788 */ void gm_801B1788(GameScene*);
/* 1B1810 */ void gm_801B1810(GameScene*);
/* 1B1834 */ void gm_801B1834(GameScene*);
/* 1B18D4 */ void gm_801B18D4(GameScene*);
/* 1B1A2C */ void gm_801B1A2C(GameScene*);
/* 1B1A84 */ void gm_801B1A84(GameScene*);
/* 1B1AD4 */ void gm_801B1AD4(GameScene*);
/* 1B1B74 */ void gm_801B1B74(GameScene*);
/* 1B1C24 */ void gm_801B1C24(GameScene*);
/* 1B1EB8 */ void gm_801B1EB8(GameScene*);
/* 1B1EEC */ void gm_801B1EEC(GameScene*);
/* 1B1F6C */ void fn_801B1F6C(int);
/* 1B1F70 */ void gm_801B1F70(GameScene*);
/* 1B2204 */ void gm_801B2204(GameScene*);
/* 1B2298 */ void gm_801B2298_OnInit(void);
/* 1B23C4 */ void gm_801B23C4_OnLoad(void);
/* 1B23F0 */ void gm_801B23F0(void);
/* 1B24B4 */ void gm_801B24B4(GameScene*);
/* 1B2510 */ void gm_801B2510(GameScene*);
/* 1B254C */ void gm_801B254C(GameScene*);
/* 1B25D4 */ void gm_801B25D4(GameScene*);
/* 1B26AC */ void gm_801B26AC(GameScene*);
/* 1B2704 */ void gm_801B2704(GameScene*);
/* 1B2790 */ void gm_801B2790(GameScene*);
/* 1B2AF8 */ void gm_801B2AF8(GameScene*);
/* 1B2B7C */ void gm_801B2B7C_OnInit(void);

#endif
