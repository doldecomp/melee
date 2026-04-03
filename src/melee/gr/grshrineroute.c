#include "grshrineroute.h"

#include "ground.h"
#include "types.h"

#include <platform.h>

#include "baselib/forward.h"

#include "baselib/jobj.h"
#include "ef/efsync.h"
#include "ft/ftdevice.h"
#include "ft/ftlib.h"
#include "gr/grdisplay.h"
#include "gr/grmaterial.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "lb/lb_00B0.h"
#include "lb/lbvector.h"
#include "mp/mplib.h"
#include "pl/player.h"

#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/lobj.h>
#include <baselib/random.h>
#include <MSL/trigf.h>

s16 grSh_Route_803E58E0[8] = {
    0x33, 0x4F, 0x65, 0x66, 0x73, 0x74, 0x83, 0x00
};

StageCallbacks grSh_Route_803E58F0[7] = {
    {
        grShrineRoute_802089AC,
        grShrineRoute_802089D8,
        grShrineRoute_802089E0,
        grShrineRoute_802089E4,
        0,
    },
    {
        grShrineRoute_8020A868,
        grShrineRoute_8020A894,
        grShrineRoute_8020A89C,
        grShrineRoute_8020A8A0,
        0,
    },
    {
        grShrineRoute_802089E8,
        grShrineRoute_80208A28,
        grShrineRoute_80208A30,
        grShrineRoute_80208A34,
        0,
    },
    {
        grShrineRoute_8020A868,
        grShrineRoute_8020A894,
        grShrineRoute_8020A89C,
        grShrineRoute_8020A8A0,
        0,
    },
    {
        grShrineRoute_80208D14,
        grShrineRoute_80208F0C,
        grShrineRoute_80208F70,
        grShrineRoute_80209AEC,
        0xC0000000,
    },
    {
        grShrineRoute_80209AF0,
        grShrineRoute_80209BE4,
        grShrineRoute_80209BEC,
        grShrineRoute_8020A100,
        0,
    },
    {
        grShrineRoute_8020A104,
        grShrineRoute_8020A214,
        grShrineRoute_8020A21C,
        grShrineRoute_8020A864,
        0,
    },
};

StageData grSh_Route_803E5988 = {
    SHRINEROUTE,
    grSh_Route_803E58F0,
    "/GrNSr.dat",
    grShrineRoute_OnInit,
    grShrineRoute_OnDemoInit,
    grShrineRoute_OnLoad,
    grShrineRoute_OnStart,
    grShrineRoute_802088B8,
    grShrineRoute_OnTouchLine,
    grShrineRoute_OnCheckShadowRender,
    (1 << 0),
    NULL,
    0,
};

static struct {
    int x0;
    int x4;
    int x8;
    int xC;
    int x10;
    f32 x14;
    f32 x18;
    int x1C;
    int x20;
    int x24;
    grZakoGenerator_SpawnDesc x28;
}* grSh_Route_804D6A58;

extern float grNKr_804DB868;
extern HSD_LightDesc grSh_Route_803E5D74;
extern HSD_LightDesc grSh_Route_803E5D90;
extern Vec3 grSh_Route_803B836C;
extern Vec3 grSh_Route_803B8378;
extern Vec3 grSh_Route_803B8384;
extern Vec3 grSh_Route_803B8390;

extern struct grSh_Route_LightConfig {
    /* 0x00 */ GXColor x0;
    /* 0x04 */ Vec3 x4;
    /* 0x10 */ Vec3 x10;
    /* 0x1C */ s32 x1C;
    /* 0x20 */ f32 x20;
    /* 0x24 */ s32 x24;
    /* 0x28 */ f32 x28;
    /* 0x2C */ f32 x2C;
    /* 0x30 */ s32 x30;
} grSh_Route_803E5A58[];

float grShrineRoute_802087B0(void)
{
    return grNKr_804DB868;
}

void grShrineRoute_OnDemoInit(bool arg) {}

void grShrineRoute_OnInit(void)
{
    grSh_Route_804D6A58 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 0;
    grShrineRoute_802088C0(0);
    grShrineRoute_802088C0(4);
    grShrineRoute_802088C0(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    grShrineRoute_8020B0AC();
}

void grShrineRoute_OnLoad(void)
{
    grShrineRoute_802088C0(6);
}

void grShrineRoute_OnStart(void)
{
    int val;
    grZakoGenerator_801CAE04(&grSh_Route_804D6A58->x28);
    val = grSh_Route_804D6A58->x24;
    if (val != 0) {
        val = HSD_Randi(grSh_Route_804D6A58->x24);
    } else {
        val = 0;
    }
    if (val == 0) {
        grZakoGenerator_801CAEB0(Ground_801C5840(), Ground_801C5940());
    }
}

bool grShrineRoute_802088B8(void)
{
    return false;
}

HSD_GObj* grShrineRoute_802088C0(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grSh_Route_803E58F0[gobj_id];

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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 271, gobj_id);
    }

    return gobj;
}

void grShrineRoute_802089AC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grShrineRoute_802089D8(Ground_GObj* arg)
{
    return false;
}

void grShrineRoute_802089E0(Ground_GObj* arg) {}

void grShrineRoute_802089E4(Ground_GObj* arg) {}

void grShrineRoute_802089E8(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    grMaterial_801C94D8(jobj);
}

bool grShrineRoute_80208A28(Ground_GObj* arg)
{
    return false;
}

void grShrineRoute_80208A30(Ground_GObj* arg) {}

void grShrineRoute_80208A34(Ground_GObj* arg) {}

void fn_80208A38(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    u8 flags[6];
    Vec3 pos;
    HSD_JObj* jobj;
    HSD_GObj* effect;
    HSD_JObj* ejobj;
    Ground* iter;
    int i;
    PAD_STACK(16);

    flags[0] = 0;
    flags[1] = 0;
    flags[2] = 0;
    flags[3] = 0;
    flags[4] = 0;
    flags[5] = 0;
    flags[HSD_Randi(6)] = 1;

    iter = gp;
    i = 0;
    do {
        jobj = Ground_801C2CF4(i + 0xBD);
        if (jobj != NULL) {
            if (flags[i] != 0) {
                *(HSD_GObj**) ((u8*) iter + 0x108) = grShrineRoute_802088C0(3);
            } else {
                *(HSD_GObj**) ((u8*) iter + 0x108) = grShrineRoute_802088C0(1);
            }
            lb_8000B1CC(jobj, NULL, &pos);
            effect = *(HSD_GObj**) ((u8*) iter + 0x108);
            if (effect != NULL) {
                ejobj = GET_JOBJ(effect);
                HSD_JObjSetTranslate(ejobj, &pos);
                HSD_JObjSetScaleX(ejobj, grSh_Route_804D6A58->x14);
                HSD_JObjSetScaleY(ejobj, grSh_Route_804D6A58->x14);
                HSD_JObjSetScaleZ(ejobj, grSh_Route_804D6A58->x14);
            }
        }
        i++;
        iter = (Ground*) ((u8*) iter + 4);
    } while (i < 6);
}

void grShrineRoute_80208D14(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    Vec3 center;
    Ground* iter;
    int i;
    PAD_STACK(16);

    mpLib_80058560();
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x8_callback = NULL;
    gp->xC_callback = NULL;
    grMaterial_801C94D8(Ground_801C3FA4(gobj, 1));
    grMaterial_801C94D8(Ground_801C3FA4(gobj, 1));

    gp->gv.shrineroute.xC4 = 0;
    gp->gv.shrineroute.xC6 = 0;
    gp->gv.shrineroute.xC8 = 0;
    gp->gv.shrineroute.xCE = 0;
    gp->gv.shrineroute.xD4 = 0;
    gp->gv.shrineroute.xCA = 0;
    gp->gv.shrineroute.xCC = 0;

    gp->x11_flags.b012 = 2;
    stage_info.x6DC = 0;

    gp->gv.shrineroute2.x108 = NULL;
    gp->gv.shrineroute2.x10C = 0;
    gp->gv.shrineroute2.x110 = 0;
    gp->gv.shrineroute2.x114 = 0;
    gp->gv.shrineroute2.x118 = 0;
    gp->gv.shrineroute2.x11C = NULL;

    ftCo_800C07F8(gobj, 3, grShrineRoute_8020AE08);
    mpJointSetCb1(8, gp, (mpLib_Callback) grShrineRoute_8020AD58);
    mpJointSetCb1(9, gp, (mpLib_Callback) grShrineRoute_8020AD58);
    mpJointSetCb1(0xA, gp, (mpLib_Callback) grShrineRoute_8020AD58);
    mpJointSetCb1(0xB, gp, (mpLib_Callback) grShrineRoute_8020AD58);
    mpJointSetCb1(0xC, gp, (mpLib_Callback) grShrineRoute_8020AD58);
    mpJointSetCb1(0xD, gp, (mpLib_Callback) grShrineRoute_8020AD58);

    if (Ground_801C2D24(0x94, &center)) {
        iter = gp;
        i = 0;
        do {
            iter->gv.shrineroute3.xE4 = Ground_801C2CF4(i + 0x7F);
            if (iter->gv.shrineroute3.xE4 != NULL) {
                HSD_JObjGetTranslation(iter->gv.shrineroute3.xE4,
                                       (Vec3*) &iter->gv.shrineroute3.xD8);
                lbVector_Sub((Vec3*) &iter->gv.shrineroute3.xD8, &center);
            }
            i++;
            iter = (Ground*) ((u8*) iter + 16);
        } while (i < 3);
    } else {
        gp->gv.shrineroute3.xE4 = NULL;
        *(HSD_JObj**) ((u8*) gp + 0xF4) = NULL;
        *(HSD_JObj**) ((u8*) gp + 0x104) = NULL;
    }

    Ground_801C10B8(gobj, fn_80208A38);
}

bool grShrineRoute_80208F0C(Ground_GObj* arg)
{
    return false;
}

bool grShrineRoute_80208F14(void)
{
    HSD_GObj* gobj;
    Ground* gp;

    gobj = Ground_801C2BA4(4);
    if (gobj != NULL) {
        gp = GET_GROUND(gobj);
        if (gp != NULL) {
            if (gp->gv.shrineroute.xCA != 0) {
                if (gp->gv.shrineroute.xCC != 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

/// #grShrineRoute_80208F70

void grShrineRoute_80209AEC(Ground_GObj* arg) {}

void grShrineRoute_80209AF0(Ground_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Ground* gp = GET_GROUND(gobj);

    gp->x8_callback = NULL;
    gp->xC_callback = NULL;
    gp->x11_flags.b012 = 2;
    grMaterial_801C94D8(jobj);
    gp->gv.shrineroute3.xC4 = Ground_801C3FA4(gobj, 10);
    grShrineRoute_8020A8A4(gobj);
    gp->gv.shrineroute3.xCC = 0;
    gp->gv.shrineroute3.xC8 = 0;
    gp->gv.shrineroute3.xD0 = 0.00006981317F * HSD_Randf() + 0.000017453292F;
    gp->gv.shrineroute3.xD0 *= (HSD_Randi(2) != 0) ? 1.0F : -1.0F;
    gp->gv.shrineroute3.xD4 = 0.00006981317F * HSD_Randf() + 0.000017453292F;
    gp->gv.shrineroute3.xD4 *= (HSD_Randi(2) != 0) ? 1.0F : -1.0F;
}

bool grShrineRoute_80209BE4(Ground_GObj* arg)
{
    return false;
}

/// #grShrineRoute_80209BEC

void grShrineRoute_8020A100(Ground_GObj* arg) {}

void grShrineRoute_8020A104(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_GObj* lgobj = HSD_GObj_Entities->xC;
    HSD_LObj* lobj;

    while (lgobj) {
        if (HSD_GObjGetClassifier(lgobj) != 0xC) {
            lgobj = HSD_GObjGetNext(lgobj);
        } else {
            break;
        }
    }
    HSD_ASSERT(1106, lgobj);
    gp->gv.shrineroute2.xC4 = lgobj;
    grShrineRoute_8020AA40(gp->gv.shrineroute2.xC4);

    lobj = GET_LOBJ(gp->gv.shrineroute2.xC4);
    gp->gv.shrineroute2.x168 = 0;
    while (lobj != NULL) {
        (&gp->gv.shrineroute2.xC8)[gp->gv.shrineroute2.x168] = lobj;
        (&gp->gv.shrineroute2.x118)[gp->gv.shrineroute2.x168] =
            HSD_LObjGetFlags(lobj);

        lobj = HSD_LObjGetNext(lobj);
        gp->gv.shrineroute2.x168 += 1;
    }

    gp->gv.shrineroute2.x16C = grShrineRoute_8020AB58(gp->gv.shrineroute2.xC4);
    gp->gv.shrineroute2.x170 = grShrineRoute_8020AC44(gp->gv.shrineroute2.xC4);
    grShrineRoute_8020A21C(gobj);
}

bool grShrineRoute_8020A214(Ground_GObj* arg)
{
    return false;
}

/// #grShrineRoute_8020A21C

void grShrineRoute_8020A864(Ground_GObj* arg) {}

void grShrineRoute_8020A868(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grShrineRoute_8020A894(Ground_GObj* arg)
{
    return false;
}

void grShrineRoute_8020A89C(Ground_GObj* arg) {}

void grShrineRoute_8020A8A0(Ground_GObj* arg) {}

void grShrineRoute_8020A8A4(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    f32 angle;

    if (gp->gv.shrineroute3.xC4 != NULL) {
        angle = (f32)(6.283185307179586 * HSD_Randf());
        HSD_JObjSetTranslateX(gp->gv.shrineroute3.xC4, 300.0f * cosf(angle));
        HSD_JObjSetTranslateY(gp->gv.shrineroute3.xC4, 300.0f * sinf(angle));
        gp->gv.shrineroute3.xD8 = 0.04363323f * ((2.0f * HSD_Randf()) - 1.0f);
        gp->gv.shrineroute3.xDC = 0.04363323f * ((2.0f * HSD_Randf()) - 1.0f);
    }
}

void grShrineRoute_8020AA40(HSD_GObj* gobj)
{
    HSD_LObj* lobj;
    struct grSh_Route_LightConfig* config;
    u32 i;
    GXColor color;

    if (gobj != NULL) {
        lobj = HSD_LObjGetNext(GET_LOBJ(gobj));
        config = grSh_Route_803E5A58;
        i = 0;
        do {
            if (lobj != NULL) {
                color = config->x0;
                HSD_LObjSetColor(lobj, color);
                HSD_LObjSetPosition(lobj, &config->x4);
                HSD_LObjSetDistAttn(lobj, config->x2C, config->x28,
                                    config->x30);
                if (config->x1C == 2) {
                    lobj->flags = 6;
                } else if (config->x1C == 3) {
                    lobj->flags = 7;
                    HSD_LObjSetInterest(lobj, &config->x10);
                    HSD_LObjSetSpot(lobj, config->x20, config->x24);
                }
            } else {
                OSReport("%s:%d: oioi...\n");
            }
            config++;
            i++;
            lobj = HSD_LObjGetNext(lobj);
        } while (i < 15);
    }
}

HSD_LObj* grShrineRoute_8020AB58(Ground_GObj* gobj)
{
    HSD_LObj* new_lobj;
    HSD_LObj* lobj;
    Vec3 pos;

    if (gobj == NULL || (lobj = gobj->hsd_obj) == NULL) {
        return NULL;
    }
    while ((lobj == NULL ? NULL : lobj->next) != NULL) {
        lobj = lobj == NULL ? NULL : lobj->next;
    }
    new_lobj = HSD_LObjLoadDesc(&grSh_Route_803E5D74);
    if (new_lobj != NULL) {
        pos = grSh_Route_803B836C;
        HSD_LObjSetNext(lobj, new_lobj);
        HSD_LObjSetPosition(new_lobj, &pos);
        HSD_LObjSetFlags(new_lobj, 0x20);
    }
    return new_lobj;
    PAD_STACK(8);
}

HSD_LObj* grShrineRoute_8020AC44(HSD_GObj* gobj)
{
    HSD_LObj* new_lobj;
    HSD_LObj* lobj;
    Vec3 pos;
    PAD_STACK(8);

    if (gobj == NULL || (lobj = gobj->hsd_obj) == NULL) {
        return NULL;
    }
    while ((lobj == NULL ? NULL : lobj->next) != NULL) {
        lobj = lobj == NULL ? NULL : lobj->next;
    }
    new_lobj = HSD_LObjLoadDesc(&grSh_Route_803E5D90);
    if (new_lobj != NULL) {
        pos = grSh_Route_803B8378;
        HSD_LObjSetNext(lobj, new_lobj);
        HSD_LObjSetPosition(new_lobj, &pos);
    }
    return new_lobj;
}

bool grShrineRoute_8020AD24(bool arg)
{
    if (arg == 1) {
        Ground_801C5740(arg);
        return 1;
    }
    return 0;
}

void grShrineRoute_8020AD58(Ground* gp, int r4, CollData* r5, int r6, int r7)
{
    HSD_GObj* pgobj;
    u32 slot;
    PAD_STACK(0x10);

    if ((int) r5->x34_flags.b1234 == 1 && r7 == 2) {
        slot = ftLib_80086BE0(r5->x0_gobj);
        if (r5->x0_gobj == Player_GetEntity(slot)) {
            gp->gv.shrineroute.xCA = 1;
            pgobj = Player_GetEntityAtIndex(slot, 1);
            if (pgobj) {
                if (!ftLib_8008731C(pgobj)) {
                    return;
                }
            }
            gp->gv.shrineroute.xCC = 1;
            return;
        }
        gp->gv.shrineroute.xCC = 1;
    }
}

s32 grShrineRoute_8020AE08(HSD_GObj* gobj, HSD_GObj* player_gobj, s32* out)
{
    Vec3 lo, hi;
    Vec3 pos;
    Ground* gp = gobj->user_data;
    f32 scale;
    PAD_STACK(16);

    if (gp->gv.shrineroute.xC4 == 1 || gp->gv.shrineroute.xC4 == 3) {
        return 0;
    }

    lo = grSh_Route_803B8384;
    hi = grSh_Route_803B8390;
    scale = Ground_801C0498();
    lo.x *= scale;
    lo.y *= scale;
    hi.x *= scale;
    lo.z *= scale;
    hi.y *= scale;
    hi.z *= scale;

    ftLib_80086644(player_gobj, &pos);

    if (pos.y < lo.y) {
        if (lo.x < pos.x && pos.x < hi.x) {
            *out = grSh_Route_804D6A58->x10;
            return 1;
        }
    }

    return 0;
}

void grShrineRoute_8020AF38(HSD_GObj* gobj, s32 arg1)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_GObj* pgobj;
    HSD_JObj* jobj;
    f32 scale;
    Ground* gp2;

    pgobj = Ground_801C57A4();
    gp2 = (Ground*) ((s32*) gp + (arg1 - 189));

    if (gp2->gv.shrineroute2.x108 != NULL) {
        scale = 0.7f;
        if (((Ground*) gp2->gv.shrineroute2.x108->user_data)->map_id == 1) {
            scale *= grSh_Route_804D6A58->x14;
        } else {
            scale *= grSh_Route_804D6A58->x18;
        }
        jobj = Ground_801C2CF4(arg1);
        efSync_Spawn(0x428, gobj, jobj, &scale);
        Ground_801C4A08(gp2->gv.shrineroute2.x108);
        gp2->gv.shrineroute2.x108 = NULL;
        if (pgobj != NULL) {
            ftLib_80086C18(pgobj, 0xB, 0x1E);
        }
    }
}

void grShrineRoute_8020B020(HSD_GObj* gobj, int r4, int r5)
{
    Ground* gp = GET_GROUND(gobj);
    int comp;
    int i;

    comp = r4 - 189;
    for (i = 0; i < 6; i++) {
        if (r4 == -1 || i != comp) {
            if (gp->gv.shrineroute2.x108) {
                if (GET_JOBJ(gp->gv.shrineroute2.x108)) {
                    if (r5) {
                        HSD_JObjSetFlagsAll(gp->gv.shrineroute2.x108->hsd_obj,
                                            JOBJ_HIDDEN);
                    } else {
                        HSD_JObjClearFlagsAll(
                            gp->gv.shrineroute2.x108->hsd_obj, JOBJ_HIDDEN);
                    }
                }
            }
        }
        gp = (Ground*) &gp->gobj;
    }
}

void grShrineRoute_8020B0AC(void)
{
    u32 i;

    for (i = 0; i < 7; i++) {
        mpLib_800575B0(grSh_Route_803E58E0[i]);
    }
}

DynamicsDesc* grShrineRoute_OnTouchLine(enum_t arg)
{
    return false;
}

bool grShrineRoute_OnCheckShadowRender(Vec3* a, int b, HSD_JObj* jobj)
{
    Vec3 vec;
    lb_8000B1CC(jobj, NULL, &vec);
    if (a->y > vec.y) {
        return true;
    } else {
        return false;
    }
}
