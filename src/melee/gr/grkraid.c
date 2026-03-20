#include "grkraid.h"

#include "cm/camera.h"
#include "ft/ftlib.h"

#include "gr/forward.h"

#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include "mn/forward.h"

#include <baselib/controller.h>
#include <baselib/random.h>

S16Vec3 grKr_803E4C78[] = { { 0, 3, 12 }, { 1, 3, 12 }, { 2, 3, 12 },
                            { 3, 3, 12 }, { 4, 3, 12 }, { 5, 3, 12 } };

StageCallbacks grKr_803E4C9C[5] = {
    { grKraid_801FE1B0, grKraid_801FE1DC, grKraid_801FE1E4, grKraid_801FE1E8,
      0 },
    { grKraid_801FE1EC, grKraid_801FE2C8, grKraid_801FE2D0, grKraid_801FE35C,
      0 },
    { grKraid_801FE360, grKraid_801FE3A4, grKraid_801FE3AC, grKraid_801FE3B0,
      0 },
    { grKraid_801FE3B4, grKraid_801FE438, grKraid_801FE440, grKraid_801FE6D4,
      0xC0000000 },
    { grKraid_801FE818, grKraid_801FE9F8, grKraid_801FEA00, grKraid_801FF14C,
      0 }
};

StageData grKr_803E4D0C = {
    KRAID,
    grKr_803E4C9C,
    "/GrKr.dat",
    grKraid_OnInit,
    grKraid_OnDemoInit,
    grKraid_OnLoad,
    grKraid_OnStart,
    grKraid_801FE0BC,
    grKraid_OnTouchLine,
    grKraid_OnCheckShadowRender,
    (1 << 0),
    grKr_803E4C78,
    6,
};

static grKr_804D6A08_t* grKr_804D6A08;
static int grKr_804D6A0C;

void grKraid_OnDemoInit(int unused)
{
    return;
}

void grKraid_OnInit(void)
{
    HSD_GObj* gobj;

    grKr_804D6A08 = Ground_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    grKraid_801FE0C4(0);
    grKraid_801FE0C4(2);
    grKraid_801FE0C4(3);
    gobj = grKraid_801FE0C4(4);
    HSD_JObjSetFlagsAll(GET_JOBJ(gobj), 0x10);
    gobj = grKraid_801FE0C4(1);
    HSD_JObjSetFlagsAll(GET_JOBJ(gobj), 0x10);
    Ground_801C39C0();
    Ground_801C3BB4();
}

void grKraid_OnLoad(void) {}

void grKraid_OnStart(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grKraid_801FE0BC(void)
{
    return false;
}

static char grKr_803E4D40[32] = "%s:%d: couldn t get gobj(id=%d)\n";
static char grKr_803E4D64[9] = __FILE__;

HSD_GObj* grKraid_801FE0C4(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grKr_803E4C9C[gobj_id];

    gobj = Ground_GetStageGObj(gobj_id);

    if (gobj != NULL) {
        Ground* gp = gobj->user_data;
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);
        if (callbacks->callback3 != NULL) {
            gp->x1C_callback = callbacks->callback3;
        }
        if (callbacks->callback0 != NULL) {
            callbacks->callback0(gobj);
        }
        if (callbacks->callback2 != NULL) {
            HSD_GObj_SetupProc(gobj, callbacks->callback2, 4);
        }
    } else {
        OSReport(grKr_803E4D40, grKr_803E4D64, 223, gobj_id);
    }

    return gobj;
}

void grKraid_801FE1B0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grKraid_801FE1DC(Ground_GObj* gobj)
{
    return false;
}

void grKraid_801FE1E4(Ground_GObj* gobj)
{
    return;
}

void grKraid_801FE1E8(Ground_GObj* gobj)
{
    return;
}

void grKraid_801FE1EC(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    Vec3 scale;

    scale.x = scale.y = scale.z = Ground_801C0498();
    HSD_JObjSetScale(GET_JOBJ(gobj), &scale);
    gp->x11_flags.b012 = 1;
}

bool grKraid_801FE2C8(Ground_GObj* gobj)
{
    return false;
}

void grKraid_801FE2D0(Ground_GObj* gobj)
{
    HSD_PadStatus* master = HSD_PadMasterStatus;
    Ground* gp = GET_GROUND(gobj);
    if ((master[1].trigger & PAD_BUTTON_A) != 0) {
        grKr_804D6A0C += 1;
        if (grKr_804D6A0C > 6) {
            grKr_804D6A0C = 0;
        }
        OSReport("*** Req Effect Anime %d\n", grKr_804D6A0C);
        grAnime_801C8138(gobj, gp->map_id, grKr_804D6A0C);
    }
}

void grKraid_801FE35C(Ground_GObj* gobj)
{
    return;
}

void grKraid_801FE360(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 2;
}

bool grKraid_801FE3A4(Ground_GObj* gobj)
{
    return false;
}

void grKraid_801FE3AC(Ground_GObj* gobj)
{
    return;
}

void grKraid_801FE3B0(Ground_GObj* gobj)
{
    return;
}

void grKraid_801FE6D4(Ground_GObj* gobj)
{
    return;
}

void grKraid_801FE3B4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    Ground_801C2ED0(jobj, gp->map_id);
    gp->gv.kraid.x0 = 0;
    gp->gv.kraid.x4 = 0.0f;
    gp->gv.kraid.x8 = 0.0f;
    gp->gv.kraid.xC = 0.0f;
    grAnime_801C8138(gobj, gp->map_id, 0);
    grAnime_801C7FF8(gobj, 0xD, 0x7, 0x2, 0.0f, 1.0f);
}

bool grKraid_801FE438(Ground_GObj* gobj)
{
    return false;
}

static inline int rand_inline(int a, int b)
{
    if (a > b) {
        return b + (a - b != 0 ? HSD_Randi(a - b) : 0);
    } else if (a < b) {
        return a + (b - a != 0 ? HSD_Randi(b - a) : 0);
    } else {
        return a;
    }
}

const Vec grKr_803B8278 = { 0.0f, 0.0f, 0.0f };
void grKraid_801FE440(Ground_GObj* gobj)
{
    float fVar2;
    float fVar3;
    float fVar4;
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = Ground_801C3FA4(gobj, 0);
    Vec pos = grKr_803B8278;
    switch (gp->gv.kraid.x0) {
    case 0:
        if (gp->gv.kraid.x4)
        { /// @remark Explicit != 0.0f comparison leads to incorrect ordering
            gp->gv.kraid.x10 = rand_inline(grKr_804D6A08->map_time_max,
                                           grKr_804D6A08->map_time_min);
            gp->gv.kraid.x0 = 1;
            grAnime_801C7FF8(gobj, 18, 7, 1, 0.0f, 1.0f);
            Ground_801C53EC(420007);
            gp->gv.kraid.x1 = 1;
        }
        break;
    case 1:
        if (gp->gv.kraid.x10 == 0) {
            gp->gv.kraid.x8 -= gp->gv.kraid.xC;
        } else {
            gp->gv.kraid.x10 += -1;
        }
        fVar2 = gp->gv.kraid.xC < 0.0f ? -gp->gv.kraid.xC : gp->gv.kraid.xC;
        fVar3 = gp->gv.kraid.x8;
        if (fVar3 < 0.0f) {
            fVar4 = -fVar3;
        } else {
            fVar4 = fVar3;
        }
        if (fVar4 < fVar2) {
            gp->gv.kraid.xC = 0.0f;
            gp->gv.kraid.x8 = 0.0f;
            gp->gv.kraid.x4 = 0.0f;
            gp->gv.kraid.x0 = 0;
        } else {
            fVar3 = fVar3 * (3.14159265f / 180);
            HSD_JObjAddRotationZ(jobj, fVar3);
            Camera_80030E44(1, &pos);
        }
        break;
    }
    if (gp->gv.kraid.x1 != 0 && grAnime_801C83D0(gobj, 18, 7) != 0) {
        grAnime_801C7FF8(gobj, 18, 7, 0, 0.0f, 1.0f);
        gp->gv.kraid.x1 = 0;
    }
    lb_800115F4();
    Ground_801C2FE0(gobj);
    grKraid_801FF150(gobj);
}

void grKraid_801FE6D8(HSD_JObj* hand, float param2)
{
    Ground* map = Ground_801C2BA4(3)->user_data;
    Vec handpos;
    f32 rot;
    f32 min;
    f32 max;
    if (map->gv.kraid.x4 == 0.0f) {
        map->gv.kraid.x4 = param2;
        lb_8000B1CC(hand, NULL, &handpos);
        OSReport("Kraid Hand Pos = %f\n", handpos.x);
        max = grKr_804D6A08->map_rot_spd_max;
        min = grKr_804D6A08->map_rot_spd_min;
        rot = (max / min) / 132.0f;
        rot = rot * min;
        grKr_804D6A08->map_rot_spd_min = grKr_804D6A08->map_rot_spd_min;
        map->gv.kraid.x8 = rot * ((handpos.x < 0.0f) ? -handpos.x : handpos.x);
        if (map->gv.kraid.x8 < grKr_804D6A08->map_rot_spd_min) {
            map->gv.kraid.x8 = grKr_804D6A08->map_rot_spd_min;
        }
        if (map->gv.kraid.x8 > grKr_804D6A08->map_rot_spd_max) {
            map->gv.kraid.x8 = grKr_804D6A08->map_rot_spd_max;
        }
        map->gv.kraid.x8 = map->gv.kraid.x8 * map->gv.kraid.x4;
        map->gv.kraid.xC = map->gv.kraid.x8 / grKr_804D6A08->map_time_acl;
        Ground_801C53EC(420005);
        Camera_80030E44(3, &handpos);
    }
}

void grKraid_801FE818(Ground_GObj* gobj)
{
    float fVar2;
    float fVar3;
    float fVar1;
    s8 iVar;

    Ground* gp = GET_GROUND(gobj);
    gp->gv.kraid2.x10 = Ground_801C3FA4(gobj, 31);
    gp->gv.kraid2.x14 = Ground_801C3FA4(gobj, 47);
    fVar1 = (fVar3 = 0.0f);
    gp->gv.kraid2.x4 = 0;
    gp->gv.kraid2.x3 = 0;

    fVar2 = grKr_804D6A08->kraid_pos_x[0];
    if (fVar2 < 0.0f) {
        gp->gv.kraid2.x3 = 0;
        fVar3 = fVar2;
    } else {
        if (fVar2 > fVar1) {
            fVar1 = fVar2;
            gp->gv.kraid2.x4 = 0;
        }
    }
    fVar2 = grKr_804D6A08->kraid_pos_x[1];
    if (fVar2 < fVar3) {
        gp->gv.kraid2.x3 = 1;
        fVar3 = fVar2;
    } else {
        if (fVar2 > fVar1) {
            fVar1 = fVar2;
            gp->gv.kraid2.x4 = 1;
        }
    }
    fVar2 = grKr_804D6A08->kraid_pos_x[2];
    if (fVar2 < fVar3) {
        gp->gv.kraid2.x3 = 2;
        fVar3 = fVar2;
    } else {
        if (fVar2 > fVar1) {
            fVar1 = fVar2;
            gp->gv.kraid2.x4 = 2;
        }
    }
    fVar2 = grKr_804D6A08->kraid_pos_x[3];
    if (fVar2 < fVar3) {
        gp->gv.kraid2.x3 = 3;
        fVar3 = fVar2;
    } else {
        if (fVar2 > fVar1) {
            fVar1 = fVar2;
            gp->gv.kraid2.x4 = 3;
        }
    }
    fVar2 = grKr_804D6A08->kraid_pos_x[4];
    if (fVar2 < fVar3) {
        gp->gv.kraid2.x3 = 4;
        fVar3 = fVar2;
    } else {
        if (fVar2 > fVar1) {
            fVar1 = fVar2;
            gp->gv.kraid2.x4 = 4;
        }
    }
    fVar2 = grKr_804D6A08->kraid_pos_x[5];
    if (fVar2 < fVar3) {
        gp->gv.kraid2.x3 = 5;
        fVar3 = fVar2;
    } else {
        if (fVar2 > fVar1) {
            fVar1 = fVar2;
            gp->gv.kraid2.x4 = 5;
        }
    }
    gp->gv.kraid2.x0 = 0;
    gp->gv.kraid2.xC = grKr_804D6A08->kraid_wait_time +
                       ((s32) grKr_804D6A08->kraid_wait_time_add != 0
                            ? HSD_Randi(grKr_804D6A08->kraid_wait_time_add)
                            : 0);
    gp->gv.kraid2.x8 = 0.0f;
    fVar2 = 0;
    iVar = (u8) fVar2;
    gp->gv.kraid2.x2 = iVar;
    gp->gv.kraid2.x1 = iVar;
    gp->gv.kraid2.x5 = 1;
}

bool grKraid_801FE9F8(Ground_GObj* gobj)
{
    return false;
}

void grKraid_801FEA00(Ground_GObj* gobj)
{
    s8 cVar3;
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    PAD_STACK(0x70);
    switch (gp->gv.kraid2.x0) {
    case 0:
        if (gp->gv.kraid2.xC <= 0) {
            Ground* map = Ground_801C2BA4(3)->user_data;
            if ((int) map->gv.kraid.x4 == 0) {
                grKraid_801FEE54(gobj);
                HSD_JObjClearFlagsAll(jobj, 0x10);
                HSD_JObjClearFlagsAll(Ground_801C2BA4(1)->hsd_obj, 0x10);
                grKraid_801FF068(gobj, 3);
                Ground_801C53EC(420001);
                Ground_801C53EC(420008);
                gp->gv.kraid2.x0 = 1;
            }
        } else {
            gp->gv.kraid2.xC += -1;
        }
        break;
    case 1:
        if (grAnime_801C83D0(gobj, 0, 7) != 0) {
            grKraid_801FF068(gobj, HSD_Randi(3));
            gp->gv.kraid2.xC = 0;
            gp->gv.kraid2.x0 = 2;
        }
        break;
    case 2:
        cVar3 = gp->gv.kraid2.x1;
        if (cVar3 == 0 && gp->gv.kraid2.xC == 80) {
            Ground_801C53EC(420000);
        } else if (cVar3 == 1 && gp->gv.kraid2.xC == 45) {
            Ground_801C53EC(420000);
        } else if (cVar3 == 2 && gp->gv.kraid2.xC == 55) {
            Ground_801C5440(gp, 0, 420000);
        }
        cVar3 = gp->gv.kraid2.x1;
        if (cVar3 == 2 && gp->gv.kraid2.xC == 161) {
            Ground_801C5544(gp, 0);
            Ground_801C53EC(420004);
        } else if (cVar3 == 2 && gp->gv.kraid2.xC == 246) {
            Ground_801C53EC(420004);
        }
        if (grAnime_801C83D0(gobj, 0, 7) != 0) {
            grKraid_801FF068(gobj, gp->gv.kraid2.x8 + 5.0f);
            gp->gv.kraid2.xC = 0;
            gp->gv.kraid2.x0 = 3;
        }
        gp->gv.kraid2.xC++;
        break;
    case 3:
        if (gp->gv.kraid2.x1 == 5) {
            Ground* map = Ground_801C2BA4(3)->user_data;
            if ((int) map->gv.kraid.x4 == 0 && gp->gv.kraid2.xC >= 147 &&
                gp->gv.kraid2.xC <= 169)
            {
                if (gp->gv.kraid2.xC == 147) {
                    Ground_801C53EC(420003);
                }
                if (grKraid_801FF0E0(gobj, 1)) {
                    gp->gv.kraid2.x5 = 1;
                    gp->gv.kraid2.x8 = 1.0f;
                    grKraid_801FE6D8(gp->gv.kraid2.x14, -1.0f);
                }
            }
            gp->gv.kraid2.xC++;
        } else {
            Ground* map = Ground_801C2BA4(3)->user_data;
            if ((int) map->gv.kraid.x4 == 0 && gp->gv.kraid2.xC >= 123 &&
                gp->gv.kraid2.xC <= 138)
            {
                if (gp->gv.kraid2.xC == 123) {
                    Ground_801C53EC(420003);
                }
                if (grKraid_801FF0E0(gobj, 0)) {
                    gp->gv.kraid2.x5 = 1;
                    gp->gv.kraid2.x8 = 1.0f;
                    grKraid_801FE6D8(gp->gv.kraid2.x10, 1.0f);
                }
            }
            gp->gv.kraid2.xC++;
        }
        if (grAnime_801C83D0(gobj, 0, 7) != 0) {
            grKraid_801FF068(gobj, 4);
            Ground_801C53EC(420002);
            Ground_801C53EC(420008);
            gp->gv.kraid2.x0 = 4;
        }
        break;
    case 4:
        if (grAnime_801C83D0(gobj, 0, 7) != 0) {
            gp->gv.kraid2.xC = grKr_804D6A08->kraid_wait_time +
                               grKr_804D6A08->kraid_wait_time_add;
            HSD_JObjSetFlagsAll(jobj, 0x10);
            HSD_JObjSetFlagsAll(Ground_801C2BA4(1)->hsd_obj, 0x10);
            gp->gv.kraid2.xC =
                grKr_804D6A08->kraid_wait_time +
                ((s32) grKr_804D6A08->kraid_wait_time_add != 0
                     ? HSD_Randi(grKr_804D6A08->kraid_wait_time_add)
                     : 0);
            gp->gv.kraid2.x0 = 0;
        }
        break;
    }
}

void grKraid_801FEE54(HSD_GObj* gobj)
{
    s32 iVar3;
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    PAD_STACK(0x10);
    if (gp->gv.kraid2.x5 != 0) {
        do {
            iVar3 = HSD_Randi(6);
        } while (gp->gv.kraid2.x2 == iVar3);
    } else {
        iVar3 = HSD_Randi(2) != 0 ? gp->gv.kraid2.x3 : gp->gv.kraid2.x4;
    }
    gp->gv.kraid2.x5 = 0;
    gp->gv.kraid2.x2 = iVar3;
    HSD_JObjSetTranslateX(jobj, grKr_804D6A08->kraid_pos_x[iVar3]);
    HSD_JObjSetTranslateX(Ground_801C2BA4(1)->hsd_obj,
                          grKr_804D6A08->kraid_pos_x[iVar3]);
    if (grKr_804D6A08->kraid_pos_x[iVar3] == 0.0f) {
        if (HSD_Randi(2) != 0) {
            iVar3 = 1;
        } else {
            iVar3 = 0;
        }
        gp->gv.kraid2.x8 = iVar3;
    } else if (grKr_804D6A08->kraid_pos_x[iVar3] < 0.0f) {
        gp->gv.kraid2.x8 = 0.0f;
    } else {
        gp->gv.kraid2.x8 = 1.0f;
    }
}

void grKraid_801FF068(HSD_GObj* gobj, int val)
{
    int temp;
    Ground* gp = GET_GROUND(gobj);
    PAD_STACK(8);

    gp->gv.kraid.x1 = val;
    grAnime_801C8138(gobj, gp->map_id, gp->gv.kraid.x1);
    temp = gp->gv.kraid.x1;
    gobj = Ground_801C2BA4(1);
    gp = GET_GROUND(gobj);
    gp->gv.kraid.x1 = temp;
    grAnime_801C8138(gobj, gp->map_id, gp->gv.kraid.x1);
    gp->gv.kraid.x0 = 1;
}

bool grKraid_801FF0E0(Ground_GObj* gobj, int flag)
{
    Ground* gp = GET_GROUND(gobj);
    int val;
    bool comp;

    if (flag == 1) {
        val = 0x9e;
    } else {
        val = 0x82;
    }
    comp = gp->gv.kraid2.xC >= val ? true : false;
    if (comp != false) {
        ftLib_80086C9C(0xC, 0x0);
    }
    return comp;
}

void grKraid_801FF14C(Ground_GObj* gobj)
{
    return;
}

void grKraid_801FF150(Ground_GObj* gobj) {}

DynamicsDesc* grKraid_OnTouchLine(enum_t unused)
{
    return false;
}

bool grKraid_OnCheckShadowRender(Vec3* a, int _, HSD_JObj* joint)
{
    return true;
}
