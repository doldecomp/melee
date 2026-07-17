#ifndef MELEE_MN_STATIC_NAME_H
#define MELEE_MN_STATIC_NAME_H

#include "mnname.h" // IWYU pragma: export

#include <placeholder.h>

#include "mn/forward.h"

#include "mn/types.h"

#include <baselib/forward.h>

#include <dolphin/mtx.h>

/// Loaded section pointers for one of the name-entry menu archive models
/// (joint, animjoint, matanim_joint, shapeanim_joint).
typedef struct {
    void* joint;
    void* anim_joint;
    void* matanim_joint;
    void* shapeanim_joint;
} MnNameArchive;

/// Name-entry menu animation loop windows (.data block owned by this
/// translation unit; see symbols.txt 0x803ED538..0x803ED62F).
/* 3ED538 */ AnimLoopSettings mnName_803ED538[4] = {
    { 0.0F, 0.0F, -0.1F },
    { 0.0F, 0.0F, -0.1F },
    { 0.0F, 0.0F, -0.1F },
    { 0.0F, 0.0F, -0.1F },
};
/* 3ED568 */ AnimLoopSettings mnName_803ED568 = { 50.0F, 59.0F, -0.1F };
/* 3ED574 */ AnimLoopSettings mnName_803ED574 = { 40.0F, 49.0F, -0.1F };
/* 3ED580 */ AnimLoopSettings mnName_803ED580 = { 30.0F, 39.0F, -0.1F };
/* 3ED58C */ AnimLoopSettings mnName_803ED58C = { 10.0F, 19.0F, -0.1F };
/* 3ED598 */ AnimLoopSettings mnName_803ED598 = { 20.0F, 29.0F, -0.1F };
/* 3ED5A4 */ f32 mnName_803ED5A4[23] = {
    0.0F, 9.0F, -0.1F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
    1.0F, 0.0F, 0.0F,  2.0F, 3.0F, 4.0F, 0.0F, 5.0F, 6.0F, 7.0F, 8.0F,
};
/* 3ED600 */ f32 mnName_803ED600[6] = {
    0.0F, 9.0F, -0.1F, 20.0F, 29.0F, -0.1F,
};
/* 3ED618 */ Vec3 mnName_803ED618[2] = {
    { -2.0F, 0.5F, 0.0F },
    { -5.5F, -2.9F, 23.0F },
};

/// Animation loop window lookup table for mnName_FindAnimLoop (.rodata block
/// owned by this translation unit; see symbols.txt 0x803B8510..0x803B8527).
/// The last entry treats the leading three floats of mnName_803ED5A4 as an
/// AnimLoopSettings window, mirroring the retail data layout.
/* 3B8510 */ static AnimLoopSettings* const mnName_803B8510[6] = {
    &mnName_803ED568, &mnName_803ED574, &mnName_803ED580,
    &mnName_803ED58C, &mnName_803ED598, (AnimLoopSettings*) mnName_803ED5A4,
};

/// Display order of the saved name entries, followed by the loaded archive
/// section pointers (.bss block owned by this translation unit; see
/// symbols.txt 0x804A0648..0x804A06EF).
/* 4A0648 */ static u8 mnName_NameDisplayOrder[0x78];
/* 4A06C0 */ static MnNameArchive mnName_804A06C0;
/* 4A06D0 */ static MnNameArchive mnName_804A06D0;
/* 4A06E0 */ static MnNameArchive mnName_804A06E0;

#endif
