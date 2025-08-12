#ifndef MELEE_GM_RESULT_STATIC_H
#define MELEE_GM_RESULT_STATIC_H

#include <placeholder.h>

#include "baselib/forward.h"
#include "gm/forward.h"
#include "sc/forward.h"

#include <dolphin/mtx.h>

struct ResultsPlayerData {
    /* +00 */ u8 x0; ///< flags
    /* +01 */ u8 page;
    /* +02 */ u16 x2;
    /* +04 */ f32 scroll_offset;
    /* +08 */ HSD_GObj* fighter_gobj;
    /* +0C */ HSD_GObj* camera;
    /* +10 */ HSD_Text* stats_text[3][10]; ///< 3 pages with 10 entries?
    // /* +10 */ HSD_Text* stats_x10[10]; ///< these text arrays are the
    // scrollable stats
    // /* +3C */ HSD_Text* stats_x3C[10];
    // /* +60 */ HSD_Text* stats_x60[10];
    /* +88 */ HSD_Text* ko_count;
    /* +8C */ HSD_Text* ko_time;
    /* +90 */ HSD_JObj* jobjs[15];
    /* +CC */ Vec3 stats_position;
};

struct ResultsData {
    /* +00 */ u8 x0;
    /* +01 */ u8 x1; ///< some sort of state
    /* +02 */ char pad_02[0x4 - 0x2];
    /* +04 */ u8 x4; ///< winner?
    /* +05 */ u8 x5; ///< team winner?
    /* +06 */ u8 x6; ///< also winner?
    /* +08 */ s32 x8;
    /* +0C */ f32 xC;
    /* +10 */ SceneDesc* pnlsce;
    /* +14 */ SceneDesc* flmsce;
    /* +18 */ HSD_GObj* x18; ///< main proc?
    /* +1C */ HSD_CObj* cobj;
    /* +20 */ HSD_JObj* x20; ///< winner logo?
    /* +24 */ HSD_JObj* x24;
    /* +28 */ HSD_JObj* x28;
    /* +2C */ HSD_Text* x2C;
    /* +30 */ HSD_JObj* x30;
    /* +34 */ HSD_JObj* x34[6];
    /* +4C */ Vec3 x4C[6];
    /* +94 */ MatchEnd* x94;
    /* +98 */ struct ResultsPlayerData player_data[6];
};
STATIC_ASSERT(sizeof(struct ResultsData) == 0x5A8);

static struct ResultsData lbl_8046DBE8;
static u32 lbl_804D3FA0;
static u32 lbl_804D3FA4;
static s8 lbl_804D3FB0 = 0x30;

#endif
