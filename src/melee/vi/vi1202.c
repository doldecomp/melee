#include "vi/vi1202.h"

#include "vi.h"

#include "baselib/forward.h"

#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ft/ft_0C31.h"
#include "ft/ftlib.h"
#include "gm/gm_1601.h"
#include "gm/gm_unsplit.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "pl/player.h"
#include "pl/plbonuslib.h"
#include "sc/types.h"
#include "ty/toy.h"
#include "ty/tylist.h"

#include <baselib/aobj.h>
#include <baselib/cobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>

struct vi1202_UnkStruct {
    /* 0x00 */ s32 x0;
    /* 0x04 */ s32 x4;
    /* 0x08 */ f32 x8;
    /* 0x0C */ u32 xC;
    /* 0x10 */ s32 x10;
    /* 0x14 */ s32 x14;
    /* 0x18 */ s32 x18;
    /* 0x1C */ s32 x1C;
    /* 0x20 */ s32 x20;
    /* 0x24 */ s32 x24;
    /* 0x28 */ s32 x28;
    /* 0x2C */ s32 x2C;
};

static SceneDesc* un_804D7040;
static SceneDesc* un_804D7044;
static HSD_Joint* un_804D7048;
static HSD_JObj* un_804D704C;

void un_8032110C(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_80321130(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_80321154(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_80321178(void)
{
    s32 i;
    HSD_GObj* gobj;
    HSD_JObj* jobj;

    i = 0;
    while ((un_804D7040->models)[i] != NULL) {
        gobj = GObj_Create(0xE, 0xF, 0);
        jobj = HSD_JObjLoadJoint((un_804D7040->models)[i]->joint);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
        gm_8016895C(jobj, (un_804D7040->models)[i], 0);
        HSD_JObjReqAnimAll(jobj, 0.0f);
        HSD_JObjAnimAll(jobj);
        HSD_GObjProc_8038FD54(gobj, un_80321154, 0x17);
        lb_80011E24(jobj, &un_804D704C, 2, -1);
        i++;
    }
    lbAudioAx_80026F2C(0x18);
    lbAudioAx_8002702C(8, 0x0020000000000000ULL);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

void vi1202_RunFrame(HSD_GObj* gobj)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    HSD_CObjAnim(cobj);
    if (cobj->aobj->curr_frame == 100.0F) {
        vi_8031C9B4(0xE, 0);
    }
    if (cobj->aobj->curr_frame == cobj->aobj->end_frame) {
        lb_800145F4();
        gm_801A4B60();
    }
}

static void HSD_JObjSetRotationY_2(HSD_JObj* jobj, f32 y)
{
    ((jobj) ? ((void) 0) : __assert("jobj.h", 660, "jobj"));
    ((!(jobj->flags & JOBJ_USE_QUATERNION))
         ? ((void) 0)
         : __assert("jobj.h", 661, "!(jobj->flags & JOBJ_USE_QUATERNION)"));
    jobj->rotate.y = y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(jobj);
    }
}

static void HSD_JObjSetScaleX_2(HSD_JObj* jobj, f32 x)
{
    ((jobj) ? ((void) 0) : __assert("jobj.h", 776, "jobj"));
    jobj->scale.x = x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(jobj);
    }
}

static void HSD_JObjSetScaleY_2(HSD_JObj* jobj, f32 x)
{
    ((jobj) ? ((void) 0) : __assert("jobj.h", 791, "jobj"));
    jobj->scale.y = x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(jobj);
    }
}

static void HSD_JObjSetScaleZ_2(HSD_JObj* jobj, f32 x)
{
    ((jobj) ? ((void) 0) : __assert("jobj.h", 806, "jobj"));
    jobj->scale.z = x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(jobj);
    }
}

static void HSD_JObjSetTranslateX_2(HSD_JObj* jobj, f32 x)
{
    ((jobj) ? ((void) 0) : __assert("jobj.h", 932, "jobj"));
    jobj->translate.x = x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(jobj);
    }
}

static void HSD_JObjSetTranslateY_2(HSD_JObj* jobj, f32 y)
{
    ((jobj) ? ((void) 0) : __assert("jobj.h", 947, "jobj"));
    jobj->translate.y = y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(jobj);
    }
}

static void HSD_JObjSetTranslateZ_2(HSD_JObj* jobj, f32 z)
{
    ((jobj) ? ((void) 0) : __assert("jobj.h", 962, "jobj"));
    jobj->translate.z = z;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(jobj);
    }
}

void vi1202_OnEnter(void* arg)
{
    f32 scale;
    HSD_LObj* lobj;
    HSD_CObj* cobj;
    HSD_JObj* jobj;
    HSD_JObj* child;
    HSD_GObj *gobj, *cam_gobj;
    PAD_STACK(24);

    lbAudioAx_80023694();
    lbAudioAx_800236DC();
    efLib_8005B4B8();
    efAsync_8006737C(0);
    lbAudioAx_80023F28(0x5A);
    lbAudioAx_80024E50(1);

    lbArchive_LoadSymbols("Vi1202.dat", &un_804D7040, "visual1202Scene", NULL);
    lbArchive_LoadSymbols("TyKoopaR.dat", &un_804D7048,
                          "ToyKoopaRModel_TopN_joint", NULL);
    lbArchive_LoadSymbols("GmRgStnd.dat", &un_804D7044, "standScene", NULL);
    un_803124BC();

    gobj = GObj_Create(0xB, 0x3, 0);
    lobj = lb_80011AC4(un_804D7040->lights);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0);

    cam_gobj = GObj_Create(0x13, 0x14, 0);
    cobj =
        lb_80013B14((HSD_CameraDescPerspective*) un_804D7040->cameras->desc);
    HSD_GObjObject_80390A70(cam_gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(cam_gobj, HSD_GObj_803910D8, 0x8);
    cam_gobj->gxlink_prios = 0x8A9;
    HSD_CObjAddAnim(cobj, un_804D7040->cameras->anims[0]);
    HSD_CObjReqAnim(cobj, 0.0f);
    HSD_CObjAnim(cobj);
    HSD_GObjProc_8038FD54(cam_gobj, vi1202_RunFrame, 0);
    un_80321178();

    gobj = GObj_Create(0xE, 0xF, 0);
    jobj = HSD_JObjLoadJoint(un_804D7048);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);

    HSD_JObjSetScaleX(jobj, 0.49f);
    HSD_JObjSetScaleY(jobj, 0.49f);
    HSD_JObjSetScaleZ(jobj, 0.49f);

    lb_8000C1C0(jobj, un_804D704C);
    lb_8000C290(jobj, un_804D704C);
    HSD_GObjProc_8038FD54(gobj, un_80321130, 0x17);

    gobj = GObj_Create(0xE, 0xF, 0);
    jobj = HSD_JObjLoadJoint(un_804D7044->models[0]->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    HSD_GObjProc_8038FD54(gobj, un_8032110C, 0x17);

    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }

    HSD_JObjSetTranslateX_2(child, -un_803060BC(0x1F, 0));
    HSD_JObjSetTranslateY_2(child, -un_803060BC(0x1F, 1));
    HSD_JObjSetTranslateZ_2(child, -un_803060BC(0x1F, 2));
    HSD_JObjSetRotationY_2(child, -un_803060BC(0x1F, 5));

    scale = 0.49f * (un_803060BC(0x1F, 4) * (1.0f / un_803060BC(0x1F, 3)));

    HSD_JObjSetScaleX_2(child, scale);
    HSD_JObjSetScaleY_2(child, scale);
    HSD_JObjSetScaleZ_2(child, scale);

    lb_8000C1C0(jobj, un_804D704C);
    lb_8000C290(jobj, un_804D704C);
    lbAudioAx_80024E50(0);
}

void vi1202_OnFrame(void)
{
    vi_8031CAAC();
}

extern char un_804A2F08[];
extern vi1202_UnkStruct* un_804D7050;
extern char mpLib_80458868[];

void un_80321900(void)
{
    HSD_GObj* gobj = GObj_Create(0x16, 0x17, 0);
    HSD_GObjProc_8038FD54(gobj, fn_803219AC, 0x13);
    un_804D7050 = (vi1202_UnkStruct*) un_804A2F08;
    un_80321950(un_804D7050);
}

void un_80321950(vi1202_UnkStruct* s)
{
    s->x0 = 0;
    s->x4 = 0x10000;
    s->x8 = 0.0F;
    s->xC = 0;
    s->x10 = gCrowdConfig->cheer_limit;
    s->x14 = 0x83D60;
    s->x18 = gCrowdConfig->max_gasp_count;
    s->x1C = 0;
    s->x20 = 0;
    s->x24 = 0;
    s->x2C = -1;
    s->x28 = -1;
}

void fn_803219AC(HSD_GObj* gobj)
{
    vi1202_UnkStruct* data = un_804D7050;
    if (data->x4 < 0x10000) {
        data->x4 = data->x4 + 1;
    }
    un_80321A00(gobj);
    un_80321AF4(gobj);
}

void un_80321A00(HSD_GObj* gobj)
{
    s32 zero;
    vi1202_UnkStruct* data = un_804D7050;
    CrowdConfig* vdata = gCrowdConfig;

    if (data->x18 >= vdata->max_gasp_count) {
        if (data->x10 < vdata->cheer_limit) {
            data->x10 = data->x10 + 1;
        }
        return;
    }

    if (lbAudioAx_80023710(data->x2C) != 0) {
        return;
    }
    data->x18 = data->x18 + 1;

    if (data->x18 < gCrowdConfig->max_gasp_count) {
        if (data->x1C != 0) {
            zero = 0;
            data->x1C = zero;
            data->x10 = zero;
            data->x18 = gCrowdConfig->max_gasp_count;
            un_80321C28();
            if (data->x20 != 0) {
                un_80321CA4(0x144);
                data->x20 = zero;
            }
        } else {
            un_80321BF8(data->x14);
        }
    } else {
        data->x10 = 0;
        un_80321C28();
        un_80321CA4(0x140);
    }
}

void un_80321AF4(HSD_GObj* gobj)
{
    char* mpLib = mpLib_80458868;
    HSD_GObj* cur;
    vi1202_UnkStruct* data = un_804D7050;
    s32 old_x24 = data->x24;
    s32 flag = 0;
    Vec3 pos;
    char pad[12];

    data->x24 = 0;
    cur = HSD_GObj_Entities->fighters;

    while (cur != NULL) {
        if (ftLib_8008732C(cur) == 0) {
            if (ftLib_8008731C(cur) == 0) {
                ftLib_80086644(cur, &pos);

                if (pos.y <
                    gCrowdConfig->blastzone_y_offset + *(f32*) (mpLib + 0x14))
                {
                    data->x24 = data->x24 + 1;
                } else {
                    if (data->xC == ftLib_80087460(cur)) {
                        flag = 1;
                    }
                }
            }
        }
        cur = cur->next;
    }

    if (old_x24 < gCrowdConfig->fighters_near_blastzone) {
        if (data->x24 >= gCrowdConfig->fighters_near_blastzone) {
            if (flag != 0) {
                un_8032201C(data->xC, 3);
            } else {
                un_80322178(3);
            }
        }
    }
}

void un_80321BF8(int arg0)
{
    vi1202_UnkStruct* data = un_804D7050;
    data->x2C = lbAudioAx_800240B4(arg0);
}

void un_80321C28(void)
{
    vi1202_UnkStruct* data = un_804D7050;
    if (lbAudioAx_80023710(data->x2C) != 0) {
        lbAudioAx_800236B8(data->x2C);
    }
    data->x2C = -1;
}

static void un_80321C70_inline(void)
{
    vi1202_UnkStruct* data;

    data = un_804D7050;

    if (data->x18 >= gCrowdConfig->max_gasp_count ||
        data->x18 < gCrowdConfig->x24)
    {
        return;
    }
    data->x1C = 1;
}

#pragma push
#pragma dont_inline on
void un_80321C70(void)
{
    vi1202_UnkStruct* data;

    data = un_804D7050;

    if (data->x18 >= gCrowdConfig->max_gasp_count ||
        data->x18 < gCrowdConfig->x24)
    {
        return;
    }
    data->x1C = 1;
}

void un_80321CA4(s32 arg)
{
    vi1202_UnkStruct* data = un_804D7050;
    un_80321CE8();
    data->x28 = lbAudioAx_8002411C(arg);
}
#pragma pop

void un_80321CE8(void)
{
    vi1202_UnkStruct* data = un_804D7050;
    if (lbAudioAx_80023710(data->x28) != 0) {
        lbAudioAx_800236B8(data->x28);
    }
    data->x28 = -1;
}

static void un_80321CE8_caller(u32 arg0)
{
    vi1202_UnkStruct* data = un_804D7050;
    if (lbAudioAx_80023710(data->x28) != 0) {
        lbAudioAx_800236B8(data->x28);
    }
    data->x28 = -1;
    data->x28 = lbAudioAx_8002411C(arg0);
}

void un_80321D30(u32 arg0, f32 arg1)
{
    s32 cat;
    vi1202_UnkStruct* data;

    data = un_804D7050;
    cat = un_80322298(arg1);
    if (cat >= 2) {
        if (un_80321EBC(arg0, arg1) != 0) {
            un_80321CE8();
            return;
        }
    }

    switch (cat) {
    case 3: {
        un_80321CE8_caller(0x140);
        break;
    }
    case 2: {
        un_80321CE8_caller(0x141);
        break;
    }
    case 1: {
        un_80321CE8_caller(0x142);
        break;
    }
    }

    if (arg0 != 0) {
        if (data->xC == arg0) {
            un_80321C70_inline();
        }
    }
}

bool un_80321EBC(u32 arg0, f32 arg1)
{
    s32 port;
    vi1202_UnkStruct* data;
    HSD_GObj* gobj;
    u32 arg0_copy = arg0;

    data = un_804D7050;
    gobj = ftLib_8008741C(arg0_copy);
    if (gobj == NULL) {
        goto skip;
    }

    port = ftLib_800874BC(gobj);
    if (Player_8003248C(ftLib_80086BE0(gobj), port) == 1) {
        goto skip;
    }

    if (ftLib_80087120(gobj) < gCrowdConfig->x1C) {
        goto skip;
    }
    if (data->x10 < gCrowdConfig->cheer_limit) {
        goto skip;
    }
    if (data->xC == arg0) {
    skip:
        return 0;
    }

    data->x14 = ftLib_8008746C(gobj);
    if (data->x14 == 0x83D60) {
        return 0;
    }

    {
        vi1202_UnkStruct* data2 = un_804D7050;
        s32 sfx;
        if (lbAudioAx_80023710(data2->x2C) != 0) {
            lbAudioAx_800236B8(data2->x2C);
        }
        data2->x2C = -1;
        if (un_80322298(arg1) == 3) {
            sfx = 0x140;
        } else {
            sfx = 0x141;
        }
        data2 = un_804D7050;
        data2->x2C = lbAudioAx_800240B4(sfx);
    }

    data->xC = arg0;
    data->x18 = 0;

    port = ftLib_800874BC(gobj);
    pl_8003FDA0(ftLib_80086BE0(gobj), port);

    return 1;
}

bool un_8032201C(u32 arg0, s32 cat)
{
    vi1202_UnkStruct* data = un_804D7050;
    HSD_GObj* gobj;
    char pad[16];

    switch (cat) {
    case 3:
        if (lbAudioAx_80023710(data->x28) != 0) {
            lbAudioAx_800236B8(data->x28);
        }
        data->x28 = -1;
        data->x28 = lbAudioAx_8002411C(0x13d);
        break;
    case 2:
        if (lbAudioAx_80023710(data->x28) != 0) {
            lbAudioAx_800236B8(data->x28);
        }
        data->x28 = -1;
        data->x28 = lbAudioAx_8002411C(0x13e);
        break;
    case 1:
        if (lbAudioAx_80023710(data->x28) != 0) {
            lbAudioAx_800236B8(data->x28);
        }
        data->x28 = -1;
        data->x28 = lbAudioAx_8002411C(0x13f);
        break;
    case 0:
        return false;
    }

    if (arg0 != 0) {
        if (data->xC == arg0) {
            un_80321C70_inline();
        }

        gobj = ftLib_8008741C(arg0);
        pl_8003FDC8(ftLib_80086BE0(gobj), ftLib_800874BC(gobj));
    }
    return true;
}

void un_80322178(int arg)
{
    vi1202_UnkStruct* data;
    char pad[8];

    switch (arg) {
    case 0:
        break;
    case 3:
        data = un_804D7050;
        if (lbAudioAx_80023710(data->x28) != 0) {
            lbAudioAx_800236B8(data->x28);
        }
        data->x28 = -1;
        data->x28 = lbAudioAx_8002411C(0x13d);
        break;
    case 2:
        data = un_804D7050;
        if (lbAudioAx_80023710(data->x28) != 0) {
            lbAudioAx_800236B8(data->x28);
        }
        data->x28 = -1;
        data->x28 = lbAudioAx_8002411C(0x13e);
        break;
    case 1:
        data = un_804D7050;
        if (lbAudioAx_80023710(data->x28) != 0) {
            lbAudioAx_800236B8(data->x28);
        }
        data->x28 = -1;
        data->x28 = lbAudioAx_8002411C(0x13f);
        break;
    }
}

bool un_80322258(float arg)
{
    f32 val2c = gCrowdConfig->horiz_margin;

    if (arg < val2c + M2C_FIELD(mpLib_80458868, f32*, 0x18)) {
        goto ret_true;
    }
    if (!(arg > M2C_FIELD(mpLib_80458868, f32*, 0x1C) - val2c)) {
        goto ret_false;
    }
ret_true:
    return 1;
ret_false:
    return 0;
}

s32 un_80322298(float arg)
{
    CrowdConfig* vdata = gCrowdConfig;
    if (arg >= vdata->kb_threshold_high) {
        return 3;
    }
    if (arg >= vdata->kb_threshold_mid) {
        return 2;
    }
    if (arg >= vdata->kb_threshold_low) {
        return 1;
    }
    return 0;
}

f32 un_803222EC(f32 arg1, f32 arg2)
{
    CrowdConfig* vdata = gCrowdConfig;
    if (!(arg2 > vdata->angle_min)) {
        return arg1;
    }
    if (!(arg2 < vdata->angle_max)) {
        return arg1;
    }
    return arg1 * vdata->angle_mult;
}

void un_80322314(void)
{
    vi1202_UnkStruct* data = un_804D7050;
    CrowdConfig* vdata = gCrowdConfig;
    if (data->x18 >= vdata->max_gasp_count) {
        return;
    }
    data->x1C = 1;
    data->x20 = 1;
}

void un_8032233C(u32 arg0, u32 arg1)
{
    s32 cat;
    vi1202_UnkStruct* data = un_804D7050;
    HSD_GObj* gobj;
    f32 kb_mag;
    PAD_STACK(8);

    gobj = ftLib_8008741C(arg0);
    kb_mag = ftLib_80087454(ftLib_8008741C(arg1));

    if (kb_mag >= gCrowdConfig->kb_threshold_high) {
        cat = 3;
    } else if (kb_mag >= gCrowdConfig->kb_threshold_mid) {
        cat = 2;
    } else if (kb_mag >= gCrowdConfig->kb_threshold_low) {
        cat = 1;
    } else {
        cat = 0;
    }

    if (cat == 0) {
        return;
    }

    if (gobj != NULL) {
        if (ftLib_80087454(gobj) >= 3.0f) {
            un_80321D30(arg0, kb_mag);
            goto end;
        }
    }

    if (data->x0 == arg0) {
        if ((f32) data->x4 < gCrowdConfig->x18) {
            un_80321D30(arg0, kb_mag > data->x8 ? kb_mag : data->x8);
            goto end;
        }
    }

    switch (cat) {
    case 3:
        un_80321CA4(0x144);
        break;
    case 2:
        un_80321CA4(0x145);
        break;
    case 1:
        un_80321CA4(0x146);
        break;
    }

    if (cat == 3 || (cat == 2 && data->xC == arg1)) {
        un_80321C70();
    }
end:
    data->x4 = 0;
    data->x0 = arg0;
    data->x8 = kb_mag;
}

bool un_803224DC(s32 spawn_id, f32 pos_x, f32 kb_mag)
{
    CrowdConfig* vdata = gCrowdConfig;
    s32 cat;
    s32 out_of_bounds;
    s32 tmp_cat;

    if (kb_mag >= vdata->kb_threshold_high) {
        tmp_cat = 3;
    } else if (kb_mag >= vdata->kb_threshold_mid) {
        tmp_cat = 2;
    } else if (kb_mag >= vdata->kb_threshold_low) {
        tmp_cat = 1;
    } else {
        tmp_cat = 0;
    }

    {
        f32 val2c = vdata->horiz_margin;
        f32 val18 = M2C_FIELD(mpLib_80458868, f32*, 0x18);
        f32 val1c;

        cat = tmp_cat;

        if (pos_x < val2c + val18) {
            goto oob;
        }
        val1c = M2C_FIELD(mpLib_80458868, f32*, 0x1C);
        if (!(pos_x > val1c - val2c)) {
            goto inb;
        }
    oob:
        out_of_bounds = 1;
        goto check;
    inb:
        out_of_bounds = 0;
    }
check:
    if (out_of_bounds != 0) {
        un_8032201C(spawn_id, cat);
    } else {
        return 0;
    }
}

int un_80322598(int arg0, float arg1)
{
    f32 val14 = M2C_FIELD(mpLib_80458868, f32*, 0x14);
    s32 cat;
    CrowdConfig* vdata;
    if (arg1 >= val14) {
        goto ret_zero;
    }
    vdata = gCrowdConfig;
    if (arg1 < vdata->recovery_y_low + val14) {
    ret_zero:
        return 0;
    }
    if (arg1 > vdata->recovery_y_high + val14) {
        cat = 3;
    } else if (arg1 > vdata->recovery_y_mid + val14) {
        cat = 2;
    } else {
        cat = 1;
    }
    un_8032201C(arg0, cat);
}
