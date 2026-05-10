#include "groldkongo.h"

#include <platform.h>

#include "forward.h"

#include "ft/ftdevice.h"
#include "gr/granime.h"
#include "gr/grmaterial.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/random.h>

static struct {
    /* 0x00 */ s16 x0;
    /* 0x02 */ s16 x2;
    /* 0x04 */ u8 pad_04[0x10];
    /* 0x14 */ f32 x14;
    /* 0x18 */ f32 x18;
    /* 0x1C */ u8 pad_1C[0x10];
    /* 0x2C */ s16 x2C;
    /* 0x2E */ s16 x2E;
    /* 0x30 */ s16 x30;
    /* 0x32 */ s16 x32;
    /* 0x34 */ s16 x34;
    /* 0x36 */ s16 x36;
    /* 0x38 */ s16 x38;
    /* 0x3A */ s16 x3A;
    /* 0x3C */ u8 pad_3C[0xC];
    /* 0x48 */ f32 x48;
    /* 0x4C */ s32 x4C;
    /* 0x50 */ s32 x50;
}* grOk_804D6A90;

StageCallbacks grOk_803E658C[4] = {
    { grOldKongo_8020F618, grOldKongo_8020F644, grOldKongo_8020F64C,
      grOldKongo_8020F650, 0 },
    { grOldKongo_8020F6E4, grOldKongo_8020F880, grOldKongo_8020F888,
      grOldKongo_80210058, 0 },
    { grOldKongo_8021005C, grOldKongo_802100F4, grOldKongo_802100FC,
      grOldKongo_80210450, 0 },
    { grOldKongo_8020F654, grOldKongo_8020F6B4, grOldKongo_8020F6BC,
      grOldKongo_8020F6E0, 0xC0000000 },
};

void grOldKongo_8020F468(bool arg) {}

void grOldKongo_8020F46C(void)
{
    grOk_804D6A90 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grOldKongo_8020F52C(0);
    grOldKongo_8020F52C(3);
    grOldKongo_8020F52C(1);
    grOldKongo_8020F52C(2);
    Ground_801C39C0();
    Ground_801C3BB4();
}

void grOldKongo_8020F4E4(void) {}

void grOldKongo_8020F4E8(void)
{
    HSD_GObj* gobj;
    gobj = Ground_801C2BA4(1);
    ftCo_800C0764(gobj, 2, grOldKongo_80210454);
    grZakoGenerator_801CAE04(NULL);
}

bool grOldKongo_8020F524(void)
{
    return false;
}

HSD_GObj* grOldKongo_8020F52C(int arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grOk_803E658C[arg0];

    gobj = Ground_GetStageGObj(arg0);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "groldkongo.c", 0xD5,
                 arg0);
    }

    return gobj;
}

void grOldKongo_8020F618(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grOldKongo_8020F644(Ground_GObj* gobj)
{
    return false;
}

void grOldKongo_8020F64C(Ground_GObj* arg) {}

void grOldKongo_8020F650(Ground_GObj* arg) {}

void grOldKongo_8020F654(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x10_flags.b5 = 1;
}

bool grOldKongo_8020F6B4(Ground_GObj* gobj)
{
    return false;
}

void grOldKongo_8020F6BC(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
    lb_800115F4();
}

void grOldKongo_8020F6E0(Ground_GObj* arg) {}

void grOldKongo_8020F6E4(Ground_GObj* gobj)
{
    Vec3 sp14;
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    grAnime_801C8138(gobj, gp->map_id, 0);
    grMaterial_801C94D8(jobj);
    gp->gv.oldkongo.xE8 = 1.0f;
    gp->gv.oldkongo.xEC = 1.0f;
    gp->gv.oldkongo.xD8 = 0.0f;
    gp->gv.oldkongo.xDC = 0.0f;
    gp->gv.oldkongo.xC4 = 0;
    gp->gv.oldkongo.xC6 = 0;
    gp->gv.oldkongo.xC8 = 2;
    gp->gv.oldkongo.xD4 = NULL;
    gp->gv.oldkongo.xE0 = 0.0f;
    gp->gv.oldkongo.xE4 = 0.0f;
    gp->gv.oldkongo.xEC = grOk_804D6A90->x48;
    gp->gv.oldkongo.xCC = rand_range(grOk_804D6A90->x18, grOk_804D6A90->x14);
    gp->gv.oldkongo.xCE = rand_range(grOk_804D6A90->x50, grOk_804D6A90->x4C);
    lb_8000B1CC(Ground_801C3FA4(gobj, 1), NULL, &sp14);
    Ground_801C4D70(gobj, &sp14, gp->gv.oldkongo.xDC);
}

bool grOldKongo_8020F880(Ground_GObj* gobj)
{
    return false;
}

/// #grOldKongo_8020F888

void grOldKongo_80210058(Ground_GObj* arg) {}

void grOldKongo_8021005C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObjSetFlagsAll(jobj, 0x10);
    gp->gv.unk.xC4 = rand_range(grOk_804D6A90->x2, grOk_804D6A90->x0);
}

bool grOldKongo_802100F4(Ground_GObj* gobj)
{
    return false;
}

/// #grOldKongo_802100FC

void grOldKongo_80210450(Ground_GObj* arg) {}

/// #grOldKongo_80210454

void grOldKongo_802105AC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if (gp->gv.oldkongo.xC6 == 1) {
        gp->gv.oldkongo.xC6 = 2;
    }
}

void grOldKongo_802105C8(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    if (gp->gv.oldkongo.xC6 != 1) {
        return;
    }
    HSD_ASSERT(751, gp->gv.oldkongo.xD4);
    if (((u8*) gp->gv.oldkongo.xD4)[2] == 8) {
        gp->gv.oldkongo.xC6 = 0;
        gp->gv.oldkongo.xD4 = NULL;
        grMaterial_801C95C4(gobj);
    }
}

extern f32 grOk_804DB9CC;
extern f32 grOk_804DBA04;
extern f32 grOk_804DBA08;
extern f32 grOk_804DBA0C;
extern f32 grOk_804DBA10;
extern f32 grOk_804DBA14;
extern f32 grOk_804DBA18;
extern f32 grOk_804DBA1C;

// HSD_ASSERT in grOldKongo_80210650 below passes __FILE__ to __assert.
// The original binary references the pre-existing "groldkongo.c" string
// at grOk_803E6640; point __FILE__ at that symbol so the relocation
// matches exactly rather than pulling in a fresh string-literal copy.
extern char grOk_803E6640[];
#undef __FILE__
#define __FILE__ grOk_803E6640

f32 grOldKongo_80210650(void)
{
    f32 result;
    s32 total;
    s32 r;

    total = grOk_804D6A90->x2C + grOk_804D6A90->x2E + grOk_804D6A90->x30 +
            grOk_804D6A90->x32 + grOk_804D6A90->x34 + grOk_804D6A90->x36 +
            grOk_804D6A90->x38 + grOk_804D6A90->x3A;

    if (total != 0) {
        r = HSD_Randi(total);
    } else {
        r = 0;
    }

    if ((r -= grOk_804D6A90->x2C) < 0) {
        result = grOk_804DBA04;
    } else if ((r -= grOk_804D6A90->x2E) < 0) {
        result = grOk_804DBA08;
    } else if ((r -= grOk_804D6A90->x30) < 0) {
        result = grOk_804DBA0C;
    } else if ((r -= grOk_804D6A90->x32) < 0) {
        result = grOk_804DB9CC;
    } else if ((r -= grOk_804D6A90->x34) < 0) {
        result = grOk_804DBA10;
    } else if ((r -= grOk_804D6A90->x36) < 0) {
        result = grOk_804DBA14;
    } else if ((r -= grOk_804D6A90->x38) < 0) {
        result = grOk_804DBA18;
    } else if ((r -= grOk_804D6A90->x3A) < 0) {
        result = grOk_804DBA1C;
    } else {
        HSD_ASSERT(786, 0);
    }

    return result;
}

DynamicsDesc* grOldKongo_80210780(enum_t gobj)
{
    return false;
}

bool grOldKongo_80210788(Vec3* a, int arg, HSD_JObj* joint)
{
    Vec3 b;

    lb_8000B1CC(joint, NULL, &b);

    if (a->y > b.y) {
        return true;
    } else {
        return false;
    }
}
