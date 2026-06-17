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

/* 477738 */ extern MatchEnd gm_80477738;
/* 480F20 */ extern MatchExitInfo gm_80480F20;
/* 4831A8 */ extern struct ResultsMatchInfo gm_804831A8;
/* 48542C */ extern UNK_T gm_8048542C[0xC / 4];
/* 485438 */ extern UNK_T gm_80485438[0x1C / 4];
/* 485454 */ extern UNK_T gm_80485454[0x2284 / 4];
/* 4876D8 */ extern StartMeleeData gm_804876D8;
/* 487810 */ extern MatchExitInfo gm_80487810;
/* 489A98 */ extern UNK_T gm_80489A98[0x2288 / 4];
/* 48BD20 */ extern UNK_T gm_8048BD20[0x148 / 4];
/* 48BE68 */ extern UNK_T gm_8048BE68[0x23C8 / 4];
/* 48E230 */ extern CSSData gm_8048E230;
/* 48E378 */ extern SSSData gm_8048E378;
/* 48E4C0 */ extern StartMeleeData gm_8048E4C0;
/* 48E5F8 */ extern UNK_T gm_8048E5F8[0x2288 / 4];
/* 4D6878 */ extern u32 gm_804D6878[2];
/* 4D6880 */ extern UNK_T gm_804D6880[0x4 / 4];
/* 4D6884 */ extern UNK_T gm_804D6884[0x8 / 4];
/* 4D688C */ extern UNK_T gm_804D688C[0x4 / 4];
/* 4D6890 */ extern UNK_T gm_804D6890[0x8 / 4];
/* 4D6898 */ extern UNK_T gm_804D6898[0x4 / 4];
/* 4D689C */ extern UNK_T gm_804D689C[0x8 / 4];
/* 4D68A4 */ extern UNK_T gm_804D68A4[0x8 / 4];
/* 4D68B0 */ extern UNK_T gm_804D68B0[0x8 / 4];

#endif
