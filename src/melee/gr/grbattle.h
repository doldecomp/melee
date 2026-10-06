#ifndef GALE01_219C98
#define GALE01_219C98

#include <melee/gr/forward.h>

#include <dat_macros.h>

/* 3E7E38 */ extern StageData grNBa_StageData;

/// Color animation scripts for the background, played by
/// #grMaterial_801C9604.
struct grBattle_YakumonoParam {
    union ColorOverlay_x8_t*
        bg_curr_color_overlay DAT_SCRIPT(colAnimCommandLength(_command));
    union ColorOverlay_x8_t*
        bg_prev_color_overlay DAT_SCRIPT(colAnimCommandLength(_command));
};

#endif
