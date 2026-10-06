#ifndef GALE01_21A620
#define GALE01_21A620

#include <melee/gr/forward.h>

#include <dat_macros.h>

/* 3E7F90 */ extern StageData grNLa_StageData;

/// Color animation scripts, played by #grMaterial_801C9604.
struct grLast_YakumonoParam {
    union ColorOverlay_x8_t* x0 DAT_SCRIPT(colAnimCommandLength(_command));
    union ColorOverlay_x8_t* x4 DAT_SCRIPT(colAnimCommandLength(_command));
    union ColorOverlay_x8_t* x8 DAT_SCRIPT(colAnimCommandLength(_command));
    union ColorOverlay_x8_t* xC DAT_SCRIPT(colAnimCommandLength(_command));
};

#endif
