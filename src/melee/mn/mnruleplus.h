#ifndef MELEE_MN_RULEPLUS_H
#define MELEE_MN_RULEPLUS_H

#include <placeholder.h>

#include "mn/forward.h"

#include "mn/types.h"

#include <sysdolphin/baselib/forward.h>

enum RulePlusOption {
    RULEPLUS_TIME_LIMIT,
    RULEPLUS_FRIENDLY_FIRE,
    RULEPLUS_PAUSE,
    RULEPLUS_SCORE,
    RULEPLUS_SD_PENALTY,
    RULEPLUS_STAGE_SELECT,
    RULEPLUS_COUNT,
};

typedef struct _MenuRulesPlusData {
    MenuKind8 menu_kind;
    u8 hovered_selection;
    union {
        struct {
            u8 time_limit;
            u8 friendly_fire;
            u8 pause;
            u8 score;
            u8 sd_penalty;
        };
        u8 values[5];
    } rule_values;
    u8 x7;
    MenuState8 state;
    HSD_JObj* xC[10]; ///< layout tree?
    HSD_JObj* x34[6][7];
    HSD_Text* description;
} MenuRulesPlusData;

typedef struct mn_803ED1D0_t {
    u16 x0[7];                    ///< option jobj mapping?
    u16 xE[6];                    ///< value jobj mapping?
    float text_start_frames[12];
    AnimLoopSettings x4C;
    AnimLoopSettings x58;
    AnimLoopSettings x64[2]; ///< [0] = unselected, [1] = selected (non-stage)
    AnimLoopSettings x7C[2]; ///< [0] = unselected, [1] = selected (stage)
    AnimLoopSettings x94;
} mn_803ED1D0_t;
STATIC_ASSERT(sizeof(mn_803ED1D0_t) == 0xA0);

/* 23201C */ void fn_8023201C(HSD_GObj*);
/* 232458 */ AnimLoopSettings* mn_80232458(u8, u8, u8);
/* 2324E4 */ void mn_802324E4(u8, MenuRulesPlusData*);
/* 232660 */ void mn_80232660(HSD_GObj*, HSD_JObj*, u8);
/* 2327A4 */ void mn_802327A4(HSD_GObj*, u32, u32);
/* 232D4C */ void mn_80232D4C(HSD_GObj*, u32, u32);
/* 232F44 */ void fn_80232F44(HSD_GObj*);
/* 233218 */ HSD_GObj* mn_80233218(MenuState);
/* 2339FC */ void mn_802339FC(void);

#endif
