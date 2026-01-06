#include "grgarden.h"

#include <platform.h>

#include "baselib/psstructs.h"
#include "ft/ftdevice.h"
#include "ft/ftlib.h"
#include "gm/gm_16AE.h"
#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/grlib.h"
#include "gr/grmaterial.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/stage.h"
#include "gr/types.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/random.h>

StageCallbacks grGd_803E5248[] = {
    { grGarden_80202D60, grGarden_80202D8C, grGarden_80202D94,
      grGarden_80202D98, 0 },
    { grGarden_80203004, grGarden_80203090, grGarden_80203098,
      grGarden_802031A0, 0 }, // cranky kong
    { grGarden_80202DC8, grGarden_80202E40, grGarden_80202E48,
      grGarden_80202E68, 0xC0000000 }, // main stage
    { grGarden_802031A4, grGarden_80203248, grGarden_80203250,
      grGarden_80203494, 0 }, // klaptrap
    { grGarden_80202E6C, grGarden_80202F34, grGarden_80202F3C,
      grGarden_80202F40, 0 }, // background
    { grGarden_80202F44, grGarden_80202F94, grGarden_80202F9C,
      grGarden_80202FA0, 0 }, // birds
    { grGarden_80202FA4, grGarden_80202FF4, grGarden_80202FFC,
      grGarden_80203000, 0 } // water
};

StageData grGd_803E4800 = {
    5,
    grGd_803E5248,
    "/GrGd.dat",
    grGarden_80202B70,
    grGarden_80202B6C,
    grGarden_80202C24,
    grGarden_80202C4C,
    grGarden_80202C70,
    grGarden_802035C8,
    grGarden_802035D0,
    1,
    0,
    0,
};

GardenParams* grGd_804D6A28;

void grGarden_80202B6C(bool arg) {}

void grGarden_80202B70(void)
{
    grGd_804D6A28 = Ground_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    grGarden_80202C78(0);
    grGarden_80202C78(4);
    grGarden_80202C78(5);
    grGarden_80202C78(6);
    grGarden_80202C78(1);
    grGarden_80202C78(3);
    grGarden_80202C78(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    if ((Stage_80225194() != 62) && gm_8016B238() == 0) {
        Ground_801C53EC(0x64194);
    }
}

void grGarden_80202C24(void)
{
    Ground_801C53EC(0x64193);
}

void grGarden_80202C4C(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grGarden_80202C70(void)
{
    return false;
}

/// #grGarden_80202C78
HSD_GObj* grGarden_80202C78(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grGd_803E5248[gobj_id];

    gobj = Ground_801C14D0(gobj_id);

    if (gobj != NULL) {
        Ground* gp = GET_GROUND(gobj);
        gp->x8_callback = 0;
        gp->xC_callback = 0;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);
        if (callbacks->callback3 != NULL) {
            gp->x1C_callback = callbacks->callback3;
        }

        if (callbacks->callback0 != NULL) {
            callbacks->callback0(gobj);
        }

        if (callbacks->callback2 != NULL) {
            HSD_GObjProc_8038FD54(gobj, callbacks->callback2, 4);
        }
        // HSD_GObjProc_8038FD54(gobj,gobj_id,4);
        // if(callbacks) {
        //	callbacks->callback0(gobj);
        // }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grgarden.c", 0xE3,
                 gobj_id);
    }

    return gobj;
}

void grGarden_80202D60(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grGarden_80202D8C(Ground_GObj* arg)
{
    return false;
}

void grGarden_80202D94(Ground_GObj* arg) {}

void grGarden_80202D98(Ground_GObj* arg) {}

void fn_80202D9C(Ground_GObj* arg)
{
    ftCo_800C06E8(arg, 4, fn_8020349C);
}

/// #grGarden_80202DC8
void grGarden_80202DC8(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x8_callback = NULL;
    gp->xC_callback = NULL;
    Ground_801C10B8(gobj, fn_80202D9C);
    gp->x11_flags.b012 = 1;
    gp->x10_flags.b5 = 1;
}

bool grGarden_80202E40(Ground_GObj* arg)
{
    return false;
}

void grGarden_80202E48(Ground_GObj* arg)
{
    lb_800115F4();
}

void grGarden_80202E68(Ground_GObj* arg) {}

/// #grGarden_80202E6C
void grGarden_80202E6C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x8_callback = NULL;
    gp->xC_callback = NULL;
    gp->x11_flags.b012 = 1;
    Ground_801C4E70(Ground_801C3FA4(gobj, 4), Ground_801C3FA4(gobj, 3),
                    Ground_801C3FA4(gobj, 7), Ground_801C3FA4(gobj, 6),
                    Ground_801C3FA4(gobj, 10), Ground_801C3FA4(gobj, 9));
}

bool grGarden_80202F34(Ground_GObj* arg)
{
    return false;
}

void grGarden_80202F3C(Ground_GObj* arg) {}

void grGarden_80202F40(Ground_GObj* arg) {}

void grGarden_80202F44(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x8_callback = NULL;
    gp->xC_callback = NULL;
    gp->x11_flags.b012 = 1;
}

bool grGarden_80202F94(Ground_GObj* arg)
{
    return false;
}

void grGarden_80202F9C(Ground_GObj* arg) {}

void grGarden_80202FA0(Ground_GObj* arg) {}

/// #grGarden_80202FA4
void grGarden_80202FA4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x8_callback = NULL;
    gp->xC_callback = NULL;
    gp->x11_flags.b012 = 2;
}

bool grGarden_80202FF4(Ground_GObj* arg)
{
    return false;
}

void grGarden_80202FFC(Ground_GObj* arg) {}

void grGarden_80203000(Ground_GObj* arg) {}

/// #grGarden_80203004
void grGarden_80203004(Ground_GObj* gobj)
{
    int iVar1;
    Ground* gp = GET_GROUND(gobj);
    gp->gv.garden.xc4 = 0;
    iVar1 = grGd_804D6A28->x8;
    iVar1 = (iVar1 != 0) ? HSD_Randi(iVar1) : 0;
    gp->gv.garden.xc8 = iVar1 + 1;
    grAnime_801C8138(gobj, gp->map_id, gp->gv.garden.xc4);
    gp->x8_callback = NULL;
    gp->xC_callback = NULL;
    gp->x11_flags.b012 = 1;
}

bool grGarden_80203090(Ground_GObj* arg)
{
    return false;
}

/// #grGarden_80203098
void grGarden_80203098(Ground_GObj* gobj)
{
    int iVar1;
    Ground* gp = GET_GROUND(gobj);
    if ((grAnime_801C83D0(gobj, 0, 7) != NULL) ||
        (grAnime_801C84A4(gobj, 0, 7) != NULL))
    {
        if (gp->gv.garden.xc8 == 0) {
            gp->gv.garden.xc4 = gp->gv.garden.xc4 + 1;
            if (3 < gp->gv.garden.xc4) {
                gp->gv.garden.xc4 = 0;
            }
            if (gp->gv.garden.xc4 == 0) {
                if (grGd_804D6A28->x8 != 0) {
                    iVar1 = HSD_Randi(grGd_804D6A28->x8);
                } else {
                    iVar1 = 0;
                }
                gp->gv.garden.xc8 = iVar1 + 1;
            } else if (gp->gv.garden.xc4 == 2) {
                if (grGd_804D6A28->xC != 0) {
                    iVar1 = HSD_Randi(grGd_804D6A28->xC);
                } else {
                    iVar1 = 0;
                }
                gp->gv.garden.xc8 = iVar1 + 1;
            }
            grAnime_801C8138(gobj, gp->map_id, gp->gv.garden.xc4);
        } else {
            gp->gv.garden.xc8 = gp->gv.garden.xc8 - 1;
        }
    }
}

void grGarden_802031A0(Ground_GObj* arg) {}

/// #grGarden_802031A4
void grGarden_802031A4(Ground_GObj* gobj)
{
    int iVar1;
    Ground* gp = GET_GROUND(gobj);
    gp->gv.garden2.xc4 = grMaterial_801C8CFC(
        0, 0, gp, Ground_801C3FA4(gobj, 8), fn_80203498, 0, 0);
    if (grGd_804D6A28->x14 != 0) {
        iVar1 = HSD_Randi(grGd_804D6A28->x14);
    } else {
        iVar1 = 0;
    }
    gp->gv.garden2.xcc = grGd_804D6A28->x10 + iVar1;
    gp->gv.garden2.xc8 = 0;
    gp->x8_callback = NULL;
    gp->xC_callback = NULL;
    gp->x11_flags.b012 = 1;
}

bool grGarden_80203248(Ground_GObj* arg)
{
    return false;
}

inline float absoluteValue(float fVar1)
{
    if (fVar1 < 0.0f) {
        fVar1 = -fVar1;
    }
    return fVar1;
}

/// #grGarden_80203250
void grGarden_80203250(Ground_GObj* gobj)
{
    int iVar1;
    int iVar4;
    float fVar1;
    float dVar1;
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = Ground_801C3FA4(gobj, 0);
    switch (gp->gv.garden2.xc8) {
    case 0:
        if (gp->gv.garden2.xcc == 0) {
            Item_80268E5C(gp->gv.garden2.xc4, 2, 2);
            grAnime_801C8138(gobj, gp->map_id, 0);
            dVar1 = grGd_804D6A28->x18;
            fVar1 = grGd_804D6A28->x1C - dVar1;

            if (fVar1 < 0.0f) {
                fVar1 = -fVar1;
            }
            iVar1 = fVar1;
            if (iVar1 != 0) {
                iVar1 = HSD_Randi(iVar1);
            } else {
                iVar1 = 0;
            }
            dVar1 += iVar1;
            HSD_JObjSetTranslateX(jobj, dVar1);
            // HSD_JObjMtxIsDirty(jobj);
            gp->gv.garden2.xcc = 0;
            gp->gv.garden2.xc8 = 1;
        } else {
            gp->gv.garden2.xcc = gp->gv.garden2.xcc - 1;
        }
        break;
    case 1:
        iVar4 = gp->gv.garden2.xcc;
        if (iVar4 == 38 || iVar4 == 148) {
            Ground_801C53EC(410001);
        } else if (iVar4 == 110 || iVar4 == 210) {
            Ground_801C53EC(410002);
        }
        if (grAnime_801C83D0(gobj, 0, 7)) {
            Item_80268E5C(gp->gv.garden2.xc4, 0, 2);
            HSD_JObjRemoveAnimAll(jobj);
            if (grGd_804D6A28->x14 != 0) {
                iVar1 = HSD_Randi(grGd_804D6A28->x14);
            } else {
                iVar1 = 0;
            }
            gp->gv.garden2.xcc = grGd_804D6A28->x10 + iVar1;
            gp->gv.garden2.xc8 = 0;
        }
        gp->gv.garden2.xcc = gp->gv.garden2.xcc + 1;
        break;
    }
}

void grGarden_80203494(Ground_GObj* arg) {}

void fn_80203498(Item_GObj* item_gobj, Ground* gp) {}

/// #fn_8020349C
bool fn_8020349C(u32 unk, HSD_GObj* player, Vec3* water)
{
    bool uVar1;
    float dVar3;
    Vec3 current;
    Vec3 previous;
    dVar3 = grGd_804D6A28->x0;
    ftLib_80086644(player, &current);
    ftLib_80086684(player, &previous);
    if (current.y < dVar3) {
        if (previous.y > dVar3) {
            dVar3 = ftLib_80086B80(player) / 10.0f;
            current.y = -30.0f;
            grGarden_80203560((dVar3), &current);
            Ground_801C53EC(410000);
        }
        uVar1 = true;
        water->x = grGd_804D6A28->x4;
        water->y = 0.0f;
        water->z = 0.0f;
    } else {
        uVar1 = false;
    }
    return uVar1;
}

void grGarden_80203560(float param1, Vec3* vec)
{
    HSD_Generator* gen = grLib_801C96F8(0x753A, 0x1E, vec);
    if (gen != NULL) {
        gen = (HSD_Generator*) gen->appsrt;
        gen->pos.x *= param1;
        gen->pos.y *= param1;
        gen->pos.z *= param1;
    }
}

DynamicsDesc* grGarden_802035C8(enum_t arg)
{
    return NULL;
}

bool grGarden_802035D0(Vec3* a, int b, HSD_JObj* jobj)
{
    Vec3 vec;
    lb_8000B1CC(jobj, NULL, &vec);
    if (a->y > vec.y) {
        return true;
    } else {
        return false;
    }
}

f32 grGarden_80203624(void)
{
    return -20.0f;
}
