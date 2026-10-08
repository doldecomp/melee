#ifndef GALE01_2087B0
#define GALE01_2087B0

#include <melee/gr/forward.h>

#include <melee/gr/types.h>

/* 3E5988 */ extern StageData grSh_Route_StageData;

struct grShrineRoute_YakumonoParam {
    union ColorOverlay_x8_t* x0 DAT_SCRIPT(colAnimCommandLength(_command));
    union ColorOverlay_x8_t* x4 DAT_SCRIPT(colAnimCommandLength(_command));
    union ColorOverlay_x8_t* x8 DAT_SCRIPT(colAnimCommandLength(_command));
    union ColorOverlay_x8_t* xC DAT_SCRIPT(colAnimCommandLength(_command));
    void* x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    f32 x20;
    int x24;
    /// Indexed by enemy spawn point, from 0x20
    grZakoGenerator_SpawnDesc spawn_descs[] DAT_EXTENT;
};

#endif
