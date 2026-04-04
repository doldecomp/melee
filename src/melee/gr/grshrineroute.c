#include "grshrineroute.h"

#include "ground.h"
#include "types.h"

#include <platform.h>

#include "baselib/forward.h"

#include "baselib/jobj.h"
#include "cm/camera.h"
#include "gm/gm_1601.h"
#include "gr/granime.h"
#include "gr/grlib.h"
#include "gr/stage.h"
#include "lb/lb_00F9.h"
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
#include <MSL/math_ppc.h>
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
    f32 x1C;
    f32 x20;
    int x24;
    grZakoGenerator_SpawnDesc x28;
}* grSh_Route_804D6A58;

extern float grNKr_804DB868;
extern HSD_LightDesc grSh_Route_803E5D74;
extern HSD_LightDesc grSh_Route_803E5D90;
extern Vec3 grSh_Route_803B8360;
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
    int i;
    float unused1;
    PAD_STACK(16);

    flags[0] = 0;
    flags[1] = 0;
    flags[2] = 0;
    flags[3] = 0;
    flags[4] = 0;
    flags[5] = 0;
    flags[HSD_Randi(6)] = 1;

    for (i = 0; i < 6; i++) {
        jobj = Ground_801C2CF4(i + 0xBD);
        if (jobj != NULL) {
            if (flags[i] != 0) {
                gp->gv.shrineroute.symbols[i] = grShrineRoute_802088C0(3);
            } else {
                gp->gv.shrineroute.symbols[i] = grShrineRoute_802088C0(1);
            }
            lb_8000B1CC(jobj, NULL, &pos);
            effect = gp->gv.shrineroute.symbols[i];
            if (effect != NULL) {
                ejobj = GET_JOBJ(effect);
                HSD_JObjSetTranslate(ejobj, &pos);
                HSD_JObjSetScaleX(ejobj, grSh_Route_804D6A58->x14);
                HSD_JObjSetScaleY(ejobj, grSh_Route_804D6A58->x14);
                HSD_JObjSetScaleZ(ejobj, grSh_Route_804D6A58->x14);
            }
        }
    }
}

void grShrineRoute_80208D14(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    Vec3 center;
    int i;
    PAD_STACK(12);

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

    for (i = 0; i < 6; i++) {
        gp->gv.shrineroute.symbols[i] = NULL;
    }

    ftCo_800C07F8(gobj, 3, grShrineRoute_8020AE08);
    mpJointSetCb1(8, gp, (mpLib_Callback) grShrineRoute_8020AD58);
    mpJointSetCb1(9, gp, (mpLib_Callback) grShrineRoute_8020AD58);
    mpJointSetCb1(0xA, gp, (mpLib_Callback) grShrineRoute_8020AD58);
    mpJointSetCb1(0xB, gp, (mpLib_Callback) grShrineRoute_8020AD58);
    mpJointSetCb1(0xC, gp, (mpLib_Callback) grShrineRoute_8020AD58);
    mpJointSetCb1(0xD, gp, (mpLib_Callback) grShrineRoute_8020AD58);

    if (Ground_801C2D24(0x94, &center)) {
        HSD_JObj* jobj;
        for (i = 0; i < 3; i++) {
            jobj = Ground_801C2CF4(i + 0x7F);
            gp->gv.shrineroute.platforms[i].jobj = jobj;
            if (jobj != NULL) {
                HSD_JObjGetTranslation(gp->gv.shrineroute.platforms[i].jobj,
                                       &gp->gv.shrineroute.platforms[i].offset);
                lbVector_Sub(&gp->gv.shrineroute.platforms[i].offset, &center);
            }
        }
    } else {
        gp->gv.shrineroute.platforms[0].jobj = NULL;
        gp->gv.shrineroute.platforms[1].jobj = NULL;
        gp->gv.shrineroute.platforms[2].jobj = NULL;
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
void grShrineRoute_80208F70(Ground_GObj* gobj)
{
    Vec3 sp88;
    Vec3 sp7C;
    Vec3 sp68;
    Vec3 sp5C;
    Vec3 sp50;
    Vec3 sp44;
    Ground* gp = gobj->user_data;
    HSD_GObj* player;
    s32 track_plat = 0;
    PAD_STACK(64);

    player = Ground_801C57A4();
    if (player != NULL) {
        ftLib_80086644(player, &sp7C);
    } else {
        sp7C.z = 0.0f;
        sp7C.y = 0.0f;
        sp7C.x = 0.0f;
    }

    switch (gp->gv.shrineroute.xC4) {
    case 0: {
        f32 radius;
        s32 result;
        track_plat = 0;
        radius = grSh_Route_804D6A58->x20 * Ground_801C0498();
        result = Ground_801C3DB4(grShrineRoute_80208F14,
                                 grSh_Route_804D6A58->x1C *
                                     Ground_801C0498(),
                                 radius);
        if (result != -1) {
            s32 ix = result - 0xBD;
            if (!(gp->gv.shrineroute.xC6 & (1 << ix))) {
                gp->gv.shrineroute.xC8 = (u16)result;
                HSD_ASSERT(0x213, gp->gv.shrineroute.symbols[ix]);
                {
                    s32 mid =
                        ((Ground*)gp->gv.shrineroute.symbols[ix]
                             ->user_data)
                            ->map_id;
                    if (player != NULL) {
                        Player_80031790(
                            (s32)ftLib_80086BE0(player));
                    }
                    if (mid == 3) {
                        gp->gv.shrineroute.xC4 = 6;
                        gp->gv.shrineroute.xD0 = 0x3C;
                    } else {
                        HSD_GObj* temp;
                        HSD_JObj* ejobj;

                        gp->gv.shrineroute.xC4 = 1;
                        gp->gv.shrineroute.xCE = 0x3C;
                        mpLib_80057BC0(0);
                        mpLib_80057BC0(1);
                        mpLib_80057BC0(2);
                        mpLib_80057BC0(3);
                        mpLib_80057BC0(4);
                        mpLib_80057BC0(5);
                        mpLib_80057BC0(6);
                        mpLib_80057BC0(7);
                        temp = grShrineRoute_802088C0(5);
                        gp->gv.shrineroute.xD4 = (u32)temp;
                        if (temp != NULL) {
                            ejobj = ((HSD_GObj*)gp->gv
                                         .shrineroute.xD4)
                                        ->hsd_obj;
                            HSD_JObjSetFlagsAll(ejobj, 0x10);
                            Ground_801C2D24(result, &sp88);
                            HSD_JObjSetTranslate(ejobj, &sp88);
                        }
                        grMaterial_801C9604(
                            (HSD_GObj*)gobj,
                            grSh_Route_804D6A58->x0, 0);
                        temp = Ground_801C2BA4(2);
                        if (temp != NULL) {
                            grMaterial_801C9604(
                                temp,
                                grSh_Route_804D6A58->x0, 0);
                        }
                        if (result != 0xBD) {
                            HSD_JObj* j = Ground_801C3FA4(
                                (HSD_GObj*)gobj, 0x13);
                            if (j != NULL) {
                                HSD_JObjSetFlagsAll(j, 0x10);
                            }
                            mpLib_80057BC0(8);
                        }
                        if (result != 0xBE) {
                            HSD_JObj* j = Ground_801C3FA4(
                                (HSD_GObj*)gobj, 0x14);
                            if (j != NULL) {
                                HSD_JObjSetFlagsAll(j, 0x10);
                            }
                            mpLib_80057BC0(9);
                        }
                        if (result != 0xBF) {
                            HSD_JObj* j = Ground_801C3FA4(
                                (HSD_GObj*)gobj, 0x12);
                            if (j != NULL) {
                                HSD_JObjSetFlagsAll(j, 0x10);
                            }
                            mpLib_80057BC0(0xA);
                        }
                        if (result != 0xC0) {
                            HSD_JObj* j = Ground_801C3FA4(
                                (HSD_GObj*)gobj, 0x11);
                            if (j != NULL) {
                                HSD_JObjSetFlagsAll(j, 0x10);
                            }
                            mpLib_80057BC0(0xB);
                        }
                        if (result != 0xC1) {
                            HSD_JObj* j = Ground_801C3FA4(
                                (HSD_GObj*)gobj, 0x10);
                            if (j != NULL) {
                                HSD_JObjSetFlagsAll(j, 0x10);
                            }
                            mpLib_80057BC0(0xC);
                        }
                        if (result != 0xC2) {
                            HSD_JObj* j = Ground_801C3FA4(
                                (HSD_GObj*)gobj, 0xF);
                            if (j != NULL) {
                                HSD_JObjSetFlagsAll(j, 0x10);
                            }
                            mpLib_80057BC0(0xD);
                        }
                        stage_info.x6DC = 1;
                        {
                            HSD_JObj* dst =
                                Ground_801C2CF4(5);
                            HSD_JObj* src =
                                Ground_801C2CF4(result - 0xA);
                            if (dst != NULL) {
                                HSD_JObjGetTranslation(
                                    src, &sp68);
                                HSD_JObjSetTranslate(
                                    dst, &sp68);
                            }
                        }
                        grZakoGenerator_801CAF08();
                        grShrineRoute_8020B020(
                            (HSD_GObj*)gobj,
                            (s32)gp->gv.shrineroute.xC8, 1);
                    }
                }
            }
        }
        break;
    }
    case 1: {
        track_plat = 1;
        if (grLib_801C96E8((HSD_GObj*)gobj) != 0) {
            gp->gv.shrineroute.xC4 = 2;
            HSD_JObjSetFlagsAll(
                Ground_801C3FA4((HSD_GObj*)gobj, 1), 0x10);
            HSD_JObjSetFlagsAll(
                Ground_801C3FA4((HSD_GObj*)gobj, 1), 0x10);
            {
                HSD_GObj* gr2 = Ground_801C2BA4(2);
                if (gr2 != NULL) {
                    HSD_JObjSetFlagsAll(
                        Ground_801C3FA4(gr2, 0), 0x10);
                }
            }
            grAnime_801C7A04((HSD_GObj*)gobj, 0, 7U, 0.0f);
            grLib_801C9908(gobj->hsd_obj);
            if (gp->gv.shrineroute.xD4 != 0) {
                grMaterial_801C9604(
                    (HSD_GObj*)gp->gv.shrineroute.xD4,
                    grSh_Route_804D6A58->x4, 0);
            }
        }
        break;
    }
    case 2: {
        track_plat = 1;
        if (gp->gv.shrineroute.xD4 != 0) {
            HSD_JObj* ejobj =
                ((HSD_GObj*)gp->gv.shrineroute.xD4)->hsd_obj;
            if (HSD_JObjGetFlags(ejobj) & 0x10) {
                void* anim =
                    ((HSD_GObj*)gp->gv.shrineroute.xD4)
                        ->user_data;
                HSD_JObjClearFlagsAll(ejobj, 0x10);
                grAnime_801C8138(
                    (HSD_GObj*)gp->gv.shrineroute.xD4,
                    ((Ground*)anim)->map_id, 0);
            }
        }
        {
            HSD_GObj* eff2 =
                (HSD_GObj*)gp->gv.shrineroute.xD4;
            if (((eff2 != NULL) &&
                 (grLib_801C96E8(eff2) != 0)) ||
                (gp->gv.shrineroute.xD4 == 0))
            {
                gp->gv.shrineroute.xC4 = 3;
                Ground_801C5750();
                gm_801674C4(6, 1, 1,
                             (s8)(gp->gv.shrineroute.xC8 - 0xA),
                             (s32)grShrineRoute_8020AD24);
                Player_80031900();
                grShrineRoute_8020AF38(
                    (HSD_GObj*)gobj,
                    (s32)gp->gv.shrineroute.xC8);
            }
        }
        break;
    }
    case 3: {
        track_plat = 1;
        if ((Ground_801C5764() == 1) &&
            (gp->gv.shrineroute.xCA != 0) &&
            (gp->gv.shrineroute.xCC != 0))
        {
            gp->gv.shrineroute.xC6 = (u16)(
                gp->gv.shrineroute.xC6 |
                (1 << (gp->gv.shrineroute.xC8 - 0xBD)));
            grZakoGenerator_801CAEF0(1);
            grShrineRoute_8020B020((HSD_GObj*)gobj, -1, 0);
            gp->gv.shrineroute.xCE = 0x3C;
            mpJointListAdd(0);
            mpJointListAdd(1);
            mpJointListAdd(2);
            mpJointListAdd(3);
            mpJointListAdd(4);
            mpJointListAdd(5);
            mpJointListAdd(6);
            mpJointListAdd(7);
            grShrineRoute_8020B0AC();
            if (gp->gv.shrineroute.xD4 != 0) {
                grMaterial_801C9604(
                    (HSD_GObj*)gp->gv.shrineroute.xD4,
                    grSh_Route_804D6A58->x8, 0);
            }
            stage_info.x6DC = 0;
            gp->gv.shrineroute.xC4 = 4;
        }
        break;
    }
    case 4: {
        HSD_GObj* eff4;
        track_plat = 0;
        eff4 = (HSD_GObj*)gp->gv.shrineroute.xD4;
        if (((eff4 != NULL) &&
             (grLib_801C96E8(eff4) != 0)) ||
            (gp->gv.shrineroute.xD4 == 0))
        {
            HSD_GObj* temp4;
            gp->gv.shrineroute.xC4 = 5;
            grLib_801C9908(
                ((HSD_GObj*)gp->gv.shrineroute.xD4)->hsd_obj);
            temp4 = (HSD_GObj*)gp->gv.shrineroute.xD4;
            if (temp4 != NULL) {
                Ground_801C4A08(temp4);
                gp->gv.shrineroute.xD4 = 0;
            }
            grMaterial_801C9604(
                (HSD_GObj*)gobj, grSh_Route_804D6A58->xC, 0);
            {
                HSD_GObj* gr2 = Ground_801C2BA4(2);
                if (gr2 != NULL) {
                    grMaterial_801C9604(
                        gr2, grSh_Route_804D6A58->xC, 0);
                }
            }
        }
        break;
    }
    case 5: {
        HSD_JObj* j19;
        track_plat = 0;
        j19 = Ground_801C3FA4((HSD_GObj*)gobj, 1);
        if (HSD_JObjGetFlags(j19) & 0x10) {
            HSD_GObj* gr2;
            u16 pid;
            HSD_JObjClearFlagsAll(j19, 0x10);
            HSD_JObjClearFlagsAll(
                Ground_801C3FA4((HSD_GObj*)gobj, 1), 0x10);
            gr2 = Ground_801C2BA4(2);
            if (gr2 != NULL) {
                HSD_JObjClearFlagsAll(
                    Ground_801C3FA4(gr2, 0), 0x10);
            }
            grAnime_801C8138((HSD_GObj*)gobj, gp->map_id, 0);
            pid = gp->gv.shrineroute.xC8;
            if ((s32)pid != 0xBD) {
                HSD_JObj* j = Ground_801C3FA4(
                    (HSD_GObj*)gobj, 0x13);
                if (j != NULL) {
                    HSD_JObjClearFlagsAll(j, 0x10);
                }
                mpJointListAdd(8);
            }
            if ((s32)pid != 0xBE) {
                HSD_JObj* j = Ground_801C3FA4(
                    (HSD_GObj*)gobj, 0x14);
                if (j != NULL) {
                    HSD_JObjClearFlagsAll(j, 0x10);
                }
                mpJointListAdd(9);
            }
            if ((s32)pid != 0xBF) {
                HSD_JObj* j = Ground_801C3FA4(
                    (HSD_GObj*)gobj, 0x12);
                if (j != NULL) {
                    HSD_JObjClearFlagsAll(j, 0x10);
                }
                mpJointListAdd(0xA);
            }
            if ((s32)pid != 0xC0) {
                HSD_JObj* j = Ground_801C3FA4(
                    (HSD_GObj*)gobj, 0x11);
                if (j != NULL) {
                    HSD_JObjClearFlagsAll(j, 0x10);
                }
                mpJointListAdd(0xB);
            }
            if ((s32)pid != 0xC1) {
                HSD_JObj* j = Ground_801C3FA4(
                    (HSD_GObj*)gobj, 0x10);
                if (j != NULL) {
                    HSD_JObjClearFlagsAll(j, 0x10);
                }
                mpJointListAdd(0xC);
            }
            if ((s32)pid != 0xC2) {
                HSD_JObj* j = Ground_801C3FA4(
                    (HSD_GObj*)gobj, 0xF);
                if (j != NULL) {
                    HSD_JObjClearFlagsAll(j, 0x10);
                }
                mpJointListAdd(0xD);
            }
            mpLib_80058560();
        }
        if (grLib_801C96E8((HSD_GObj*)gobj) != 0) {
            gp->gv.shrineroute.xC4 = 0;
        }
        break;
    }
    case 6:
        stage_info.flags |= 0x10;
        break;
    }

    if (track_plat == 0) {
        if (player != NULL) {
            if (ftLib_80086EC0(player) != 0) {
                Stage_UnkSetVec3TCam_Offset(&sp5C);
                gp->gv.shrineroute.xCE = 0x3C;
            } else if (ftLib_8008732C(player) != 0) {
                Stage_UnkSetVec3TCam_Offset(&sp5C);
                gp->gv.shrineroute.xCE = 0;
            } else {
                sp5C = sp7C;
            }
        } else {
            Stage_UnkSetVec3TCam_Offset(&sp5C);
        }
        Camera_80030AE0(1);
    } else {
        Ground_801C2D24((s32)gp->gv.shrineroute.xC8, &sp5C);
        sp5C.y += 30.0f;
        Camera_80030AE0(0);
    }

    {
        u16 timer = gp->gv.shrineroute.xCE;
        if (timer == 0) {
            Ground_801C38BC(sp5C.x, sp5C.y);
        } else {
            f32 t = 1.0f / (f32)timer;
            Stage_UnkSetVec3TCam_Offset(&sp50);
            lbVector_Sub(&sp5C, &sp50);
            sp5C.x *= t;
            sp5C.y *= t;
            sp5C.z *= t;
            lbVector_Add(&sp50, &sp5C);
            Ground_801C38BC(sp50.x, sp50.y);
            gp->gv.shrineroute.xCE =
                (u16)(gp->gv.shrineroute.xCE - 1);
        }
    }

    Stage_UnkSetVec3TCam_Offset(&sp44);
    {
        s32 k;
        for (k = 0; k < 3; k++) {
            HSD_JObj* jobj = gp->gv.shrineroute.platforms[k].jobj;
            if (jobj != NULL) {
                f32 tx = gp->gv.shrineroute.platforms[k].offset.x + sp44.x;
                HSD_JObjSetTranslateX(jobj, tx);
                jobj = gp->gv.shrineroute.platforms[k].jobj;
                {
                    f32 ty = gp->gv.shrineroute.platforms[k].offset.y + sp44.y;
                    HSD_JObjSetTranslateY(jobj, ty);
                }
            }
        }
    }

    gp->gv.shrineroute.xCA = 0;
    gp->gv.shrineroute.xCC = 0;
    lb_800115F4();
}

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

void grShrineRoute_80209BEC(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    f32 vel;
    f32 rot;

    gp->gv.shrineroute3.xC8 += gp->gv.shrineroute3.xD0;
    gp->gv.shrineroute3.xC8 *= 0.99f;
    if (gp->gv.shrineroute3.xC8 > 0.0008726646f) {
        gp->gv.shrineroute3.xC8 = 0.0008726646f;
    } else if (gp->gv.shrineroute3.xC8 < -0.0008726646f) {
        gp->gv.shrineroute3.xC8 = -0.0008726646f;
    }

    gp->gv.shrineroute3.xCC += gp->gv.shrineroute3.xD4;
    gp->gv.shrineroute3.xCC *= 0.99f;
    if (gp->gv.shrineroute3.xCC > 0.0008726646f) {
        gp->gv.shrineroute3.xCC = 0.0008726646f;
    } else if (gp->gv.shrineroute3.xCC < -0.0008726646f) {
        gp->gv.shrineroute3.xCC = -0.0008726646f;
    }

    vel = gp->gv.shrineroute3.xC8;
    rot = vel + HSD_JObjGetRotationX(jobj);
    if (rot > 0.2617994f) {
        rot = 0.2617994f;
        if (vel < 0.0f) {
            vel = -vel;
        }
        gp->gv.shrineroute3.xC8 = -vel;
        gp->gv.shrineroute3.xD0 =
            0.00006981317f * -HSD_Randf() - 0.000017453292f;
    } else if (rot < -0.2617994f) {
        rot = -0.2617994f;
        if (vel < 0.0f) {
            vel = -vel;
        }
        gp->gv.shrineroute3.xC8 = vel;
        gp->gv.shrineroute3.xD0 =
            0.00006981317f * HSD_Randf() + 0.000017453292f;
    }
    HSD_JObjSetRotationX(jobj, rot);

    vel = gp->gv.shrineroute3.xCC;
    rot = vel + HSD_JObjGetRotationY(jobj);
    if (rot > 0.17453292f) {
        rot = 0.17453292f;
        if (vel < 0.0f) {
            vel = -vel;
        }
        gp->gv.shrineroute3.xCC = -vel;
        gp->gv.shrineroute3.xD4 =
            0.00006981317f * -HSD_Randf() - 0.000017453292f;
    } else if (rot < -0.17453292f) {
        rot = -0.17453292f;
        if (vel < 0.0f) {
            vel = -vel;
        }
        gp->gv.shrineroute3.xCC = vel;
        gp->gv.shrineroute3.xD4 =
            0.00006981317f * HSD_Randf() + 0.000017453292f;
    }
    HSD_JObjSetRotationY(jobj, rot);

    if (gp->gv.shrineroute3.xC4 != NULL) {
        rot = gp->gv.shrineroute3.xD8 +
              HSD_JObjGetRotationX(gp->gv.shrineroute3.xC4);
        if (rot > 6.283185307179586) {
            rot = (f32)((f64)rot - 6.283185307179586);
        } else if (rot < -6.283185307179586) {
            rot = (f32)((f64)rot + 6.283185307179586);
        }
        HSD_JObjSetRotationX(gp->gv.shrineroute3.xC4, rot);

        rot = gp->gv.shrineroute3.xDC +
              HSD_JObjGetRotationY(gp->gv.shrineroute3.xC4);
        if (rot > 6.283185307179586) {
            rot = (f32)((f64)rot - 6.283185307179586);
        } else if (rot < -6.283185307179586) {
            rot = (f32)((f64)rot + 6.283185307179586);
        }
        HSD_JObjSetRotationY(gp->gv.shrineroute3.xC4, rot);
    }

    if (lb_8000B134(jobj)) {
        grShrineRoute_8020A8A4(gobj);
    }
}

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
        gp->gv.shrineroute2.xC8[gp->gv.shrineroute2.x168] = lobj;
        gp->gv.shrineroute2.x118[gp->gv.shrineroute2.x168] =
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

void grShrineRoute_8020A21C(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    HSD_GObj* player;
    Vec3 player_pos;
    Vec3 light_pos;
    s32 sorted[20];
    f32 distances[20];
    Vec3 pos1;
    Vec3 pos2;
    Vec3 dir;
    GXColor color;
    Vec3 temp_pos;
    s32 color_val;
    f32* dp;
    s32* sp;
    s32 count;
    s32 i;
    s32 j;
    s32 best;
    f32 min_dist;
    f32 ref_dist;
    f32 weight;
    f32 dx;
    f32 dy;
    f32 dist_sq;

    player = Ground_801C57A4();
    if (player != NULL) {
        ftLib_80086644(player, &player_pos);
    } else {
        player_pos.z = 0.0f;
        player_pos.y = 0.0f;
        player_pos.x = 0.0f;
    }

    if ((u32)gp->gv.shrineroute2.xC4 != 0) {
        sp = sorted;
        dp = distances;
        i = 0;
        while (i < (s32)gp->gv.shrineroute2.x168) {
            HSD_LObj* lobj = gp->gv.shrineroute2.xC8[i];
            s32 type = lobj->flags & 3;

            if (type == 0) {
                *dp = -100.0f;
            } else if ((u32)(type - 1) <= 1U) {
                HSD_LObjGetPosition(lobj, &pos1);
                dx = player_pos.x - pos1.x;
                dy = player_pos.y - pos1.y;
                {
                    f32 dx2 = dx * dx;
                    f32 dy2 = dy * dy;
                    dist_sq = dx2 + dy2;
                }
                *dp = sqrtf(dist_sq);
            } else if (type == 3) {
                HSD_LObjGetPosition(lobj, &pos2);
                dx = player_pos.x - pos2.x;
                if (dx < 0.0f) {
                    dx = -dx;
                }
                *dp = dx;
            } else {
                HSD_ASSERT(0x4A1, 0);
            }

            if (*dp < 10.0f) {
                *dp = 10.0f;
            }
            *sp = i;
            dp += 1;
            sp += 1;
            i += 1;
        }

        /* Selection sort by distance */
        sp = sorted;
        i = 0;
        while (i < (s32)gp->gv.shrineroute2.x168) {
            count = (s32)gp->gv.shrineroute2.x168;
            min_dist = 3.4028235e38f;
            best = 0;
            for (j = i; j < count; j++) {
                if (min_dist > distances[sorted[j]]) {
                    best = j;
                    min_dist = distances[sorted[j]];
                }
            }
            {
                s32 tmp = *sp;
                s32* bestp = &sorted[best];
                i += 1;
                *sp = *bestp;
                sp += 1;
                *bestp = tmp;
            }
        }

        /* Enable first 6 lights, disable rest */
        sp = sorted;
        i = 0;
        while (i < (s32)gp->gv.shrineroute2.x168) {
            if (i < 6) {
                HSD_LObjClearFlags(
                    gp->gv.shrineroute2.xC8[*sp], 0x20);
            } else {
                HSD_LObjSetFlags(
                    gp->gv.shrineroute2.xC8[*sp], 0x20);
            }
            sp += 1;
            i += 1;
        }

        /* Compute weighted direction */
        dir = grSh_Route_803B8360;
        ref_dist = distances[sorted[1]];

        sp = &sorted[1];
        i = 1;
        while (i < (s32)gp->gv.shrineroute2.x168) {
            if (HSD_LObjGetPosition(
                    gp->gv.shrineroute2.xC8[*sp],
                    &light_pos) != 0)
            {
                weight = ref_dist / distances[*sp];
                lbVector_Sub(&light_pos, &player_pos);
                if (light_pos.y < 15.0f) {
                    if (light_pos.y < 0.0f) {
                        weight = 0.0f;
                    } else {
                        weight *= light_pos.y / 15.0f;
                    }
                }
                lbVector_Normalize(&light_pos);
                light_pos.x *= weight;
                light_pos.y *= weight;
                light_pos.z *= weight;
                lbVector_Add(&dir, &light_pos);
            }
            sp += 1;
            i += 1;
        }

        /* Compute magnitude and normalize direction */
        dist_sq = dir.z * dir.z + (dir.x * dir.x + dir.y * dir.y);
        dist_sq = sqrtf(dist_sq);
        if (dist_sq < 0.01f) {
            dir.y = 100.0f;
        }
        lbVector_Normalize(&dir);
        dir.x *= 20.0f;
        dir.y *= 20.0f;
        dir.z *= 20.0f;
        lbVector_Add(&dir, &player_pos);

        /* Set spotlight */
        HSD_LObjSetPosition(gp->gv.shrineroute2.x16C, &dir);
        HSD_LObjSetInterest(gp->gv.shrineroute2.x16C, &player_pos);
        HSD_LObjSetFlags(gp->gv.shrineroute2.x16C, 0x400);

        /* Color from 2nd nearest */
        {
            f32 dist_diff;
            dist_diff = distances[sorted[2]] - distances[sorted[1]];
            HSD_LObjGetColor(
                gp->gv.shrineroute2.xC8[sorted[1]], &color);
            if (dist_diff < 50.0f) {
                f32 ratio = dist_diff / 50.0f;
                color.r = (u8)(s32)((f32)(u8)color.r * ratio);
                color.g = (u8)(s32)((f32)color.g * ratio);
                color.b = (u8)(s32)((f32)color.b * ratio);
            }
        }
        color_val = *(s32*)&color;
        HSD_LObjSetColor(gp->gv.shrineroute2.x170, *(GXColor*)&color_val);

        /* Copy position from 2nd nearest */
        if (HSD_LObjGetPosition(
                gp->gv.shrineroute2.xC8[sorted[1]],
                &temp_pos) == 0)
        {
            temp_pos.z = 0.0f;
            temp_pos.y = 0.0f;
            temp_pos.x = 0.0f;
        }
        HSD_LObjSetPosition(gp->gv.shrineroute2.x170, &temp_pos);

        /* Copy interest from 2nd nearest */
        if (HSD_LObjGetInterest(
                gp->gv.shrineroute2.xC8[sorted[1]],
                &temp_pos) == 0)
        {
            temp_pos.z = 0.0f;
            temp_pos.y = 0.0f;
            temp_pos.x = 0.0f;
        }
        HSD_LObjSetInterest(gp->gv.shrineroute2.x170, &temp_pos);

        /* Copy and modify flags */
        gp->gv.shrineroute2.x170->flags =
            gp->gv.shrineroute2.xC8[sorted[1]]->flags;
        gp->gv.shrineroute2.x170->flags =
            (u16)(gp->gv.shrineroute2.x170->flags & ~4);
        gp->gv.shrineroute2.x170->flags =
            (u16)(gp->gv.shrineroute2.x170->flags | 8);
    }
}

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
    s32 ix = arg1 - 0xBD;

    pgobj = Ground_801C57A4();

    if (gp->gv.shrineroute.symbols[ix] != NULL) {
        scale = 0.7f;
        if (((Ground*) gp->gv.shrineroute.symbols[ix]->user_data)->map_id == 1) {
            scale *= grSh_Route_804D6A58->x14;
        } else {
            scale *= grSh_Route_804D6A58->x18;
        }
        jobj = Ground_801C2CF4(arg1);
        efSync_Spawn(0x428, gobj, jobj, &scale);
        Ground_801C4A08(gp->gv.shrineroute.symbols[ix]);
        gp->gv.shrineroute.symbols[ix] = NULL;
        if (pgobj != NULL) {
            ftLib_80086C18(pgobj, 0xB, 0x1E);
        }
    }
}

void grShrineRoute_8020B020(HSD_GObj* gobj, int r4, int r5)
{
    Ground* gp = gobj->user_data;
    int comp;
    int i;

    comp = r4 - 189;
    for (i = 0; i < 6; i++) {
        if (r4 == -1 || i != comp) {
            if (gp->gv.shrineroute.symbols[i]) {
                if (GET_JOBJ(gp->gv.shrineroute.symbols[i])) {
                    if (r5) {
                        HSD_JObjSetFlagsAll(gp->gv.shrineroute.symbols[i]->hsd_obj,
                                            JOBJ_HIDDEN);
                    } else {
                        HSD_JObjClearFlagsAll(
                            gp->gv.shrineroute.symbols[i]->hsd_obj, JOBJ_HIDDEN);
                    }
                }
            }
        }
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
