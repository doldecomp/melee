#ifndef __GALE01_1D5238
#define __GALE01_1D5238

#include <platform.h>
#include <placeholder.h>

#include "mp/forward.h"

#include "gr/types.h"

/* 1D7700 */ static void fn_801D7700(Ground* gp, UNK_T, UNK_T, UNK_T,
                                     mpLib_GroundEnum arg4);
/* 1D7E60 */ static void fn_801D7E60(Ground* gp, UNK_T, UNK_T, UNK_T,
                                     mpLib_GroundEnum arg4);
/* 1D8134 */ static int fn_801D8134(HSD_GObj* arg0, HSD_GObj* arg1);
/* 1D8444 */ static DynamicsDesc* grKongo_801D8444(enum_t);

static StageCallbacks* grKg_803E16E0;

static struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    s16 unk44;
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
    s16 unk4E;
    s16 unk50;
    s16 unk52;
    f32 unk54;
    f32 unk58;
    f32 unk5C;
    f32 unk60;
    s32 unk64;
    s32 unk68;
    f32 unk6C;
    f32 unk70;
    f32 unk74;
    f32 unk78;
    f32 unk7C;
    f32 unk80;
    s32 unk84;
    f32 unk88;
    f32 unk8C;
    f32 unk90;
    f32 unk94;
    f32 unk98;
}* grKg_804D6980;

extern StageInfo stage_info;

#endif
