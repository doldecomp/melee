#include "gmstaffroll.h"

#include "gm_unsplit.h"

#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/displayfunc.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/fog.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/lobj.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/random.h>
#include <melee/ef/efasync.h>
#include <melee/ef/eflib.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbbgflash.h>
#include <melee/lb/lblanguage.h>
#include <melee/sc/types.h>
#include <melee/un/un_2FC9.h>

struct gm_804D67F8_t {
    char pad_0[0x948];
};
STATIC_ASSERT(sizeof(struct gm_804D67F8_t) == 0x948);

/* 4D67F8 */ static struct {
    struct {
        u8 pad0[0x54];
        HSD_GObj* x54;
        u8 pad58[0x8c - 0x58];
        GXColor x8c;
    }* win[2];
    int x8;
}* gm_804D67F8;

struct gm_804D67FC_t {
    char pad_0[0x2E68];
};
STATIC_ASSERT(sizeof(struct gm_804D67FC_t) == 0x2E68);

/* 4D67FC */ static struct {
    int index;
    struct {
        u8 pad[0x44];
        Mtx mtx;
    }* x4;
    u8 pad[0x3C - 8];
}* gm_804D67FC;

struct gm_804D6804_t {
    /* +0 */ float x0;
    /* +4 */ float x4;
};

/* 4D6804 */ static struct gm_804D6804_t gm_804D6804;
/* 4D680C */ static struct {
    u8 pad[0x54];
    HSD_GObj* x54;
}* gm_804D680C;

/* 4D6810 */ static s32 gm_804D6810;
/* 4D6814 */ static s32 gm_804D6814;
/* 4D6818 */ static s32 gm_804D6818;
/* 4D681C */ static s32 gm_804D681C;
/* 4D6820 */ static s32 gm_804D6820;
/* 4D6824 */ static f32 gm_804D6824;
/* 4D6828 */ static f32 gm_804D6828;
/* 4D682C */ static HSD_JObj* gm_804D682C;
/* 4D6830 */ static HSD_CObj* gm_804D6830;
/* 4D6834 */ static HSD_CObj* gm_804D6834;
/* 4D6838 */ static HSD_Fog* gm_804D6838;
/* 4D683C */ static UNK_T gm_804D683C;
/* 4D6840 */ static SceneDesc* gm_804D6840;
/* 4D6844 */ static DynamicModelDesc** gm_804D6844;
/* 4D6848 */ static s32 gm_804D6848;
/* 4D684C */ static s32 gm_804D684C;

bool gm_801AA644(void)
{
    return gmMainLib_8015EDD4();
}

bool gm_801AA664(int arg0)
{
    gm_80164840(arg0);
}

bool gm_801AA688(void)
{
    PAD_STACK(4);
    return gm_80164840(9) || gm_80164840(0x17);
}

void gm_801AA6D8(s16 arg0)
{
    un_803048C0(arg0);
}

bool gm_801AA6FC(void)
{
    PAD_STACK(4);
    return un_803048C0(0x10B) || un_803048C0(0x10A) || un_803048C0(0x109);
}

bool gm_801AA774(void)
{
    PAD_STACK(4);
    return un_803048C0(0x107) || un_803048C0(0x108);
}

void gm_801AA7C4_OnFrame(void)
{
    if (gm_804D6814 >= 0x134D) {
        lbAudioAx_80028B90();
        lbAudioAx_800236DC();
        gm_801A4B60();
    }
}

void fn_801AA7F8(HSD_GObj* gobj)
{
    HSD_CObj* cobj = gobj->hsd_obj;
    int i;
    if (gm_804D6818 == 0) {
        for (i = 0; i < gm_804D681C; i++) {
            HSD_CObjAnim(cobj);
        }
    }
}

static int gm_804D6800;

void fn_801AA854(HSD_GObj* gobj, int code)
{
    int i;
    HSD_CObj* cobj = gobj->hsd_obj;
    Mtx sp10;

    if (HSD_CObjSetCurrent(cobj)) {
        HSD_SetEraseColor(gm_804D6838->color.r, gm_804D6838->color.g,
                          gm_804D6838->color.b, 0xFF);
        HSD_CObjEraseScreen(cobj, 1, 0, 0);
        HSD_GObj_80390ED0(gobj, 7);
        HSD_FogSet(NULL);
        PSMTXCopy(cobj->view_mtx, sp10);
        gobj = HSD_GObj_804D7824[9];
        while (gobj != NULL) {
            if (gobj != HSD_GObj_804D7824[9]) {
                __assert(
                    "gmstaffroll.c", 0x167,
                    "gobj == HSD_GObjGXLinkHead[Gm_GObj_GXLink_PlyCursor]");
            }
            for (i = gm_804D6800 - 1; i >= 0; i--) {
                if (gm_804D67F8[gm_804D67FC[i].index].win[0] == 0) {
                    __assert("gmstaffroll.c", 0x169,
                             "staffInfo[staffInfoSortBuf[i].index].win[0]");
                }
                if (gm_804D67F8[gm_804D67FC[i].index].win[1] == 0) {
                    __assert("gmstaffroll.c", 0x16A,
                             "staffInfo[staffInfoSortBuf[i].index].win[1]");
                }
                PSMTXConcat(cobj->view_mtx, gm_804D67FC[i].x4->mtx,
                            cobj->view_mtx);
                if (cobj->view_mtx[2][2] >= 0.0F) {
                    HSD_SisLib_803A84BC(
                        gm_804D67F8[gm_804D67FC[i].index].win[0]->x54, 2);
                    HSD_SisLib_803A84BC(
                        gm_804D67F8[gm_804D67FC[i].index].win[1]->x54, 2);
                }
                PSMTXCopy(sp10, cobj->view_mtx);
            }
            gobj = gobj->next_gx;
        }
        HSD_CObjEndCurrent();
    }
}

static struct {
    u8 pad[0x54];
    HSD_GObj* x54;
}* gm_80480D58[6];

void fn_801AAA28(HSD_GObj* gobj, int code)
{
    int i;
    HSD_GObj_803910D8(gobj, code);
    if (HSD_CObjSetCurrent(GET_COBJ(gobj))) {
        for (i = 0; i < 6; i++) {
            if (gm_80480D58[i] != NULL) {
                HSD_SisLib_803A84BC(gm_80480D58[i]->x54, 2);
            }
        }
        if (gm_804D680C != NULL) {
            HSD_SisLib_803A84BC(gm_804D680C->x54, 2);
        }
    }
    HSD_CObjEndCurrent();
}

void fn_801AAABC(HSD_GObj* gobj)
{
    HSD_LObj* lobj = gobj->hsd_obj;
    int i;
    if (gm_804D6818 == 0) {
        for (i = 0; i < gm_804D681C; i++) {
            HSD_LObjAnimAll(lobj);
        }
    }
}

void fn_801AAB18(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    int i;
    if (gm_804D6818 == 0) {
        for (i = 0; i < gm_804D681C; i++) {
            HSD_JObjAnimAll(jobj);
        }
    }
}

/// #fn_801AAB74

/// #fn_801AB200

void fn_801AC67C(HSD_GObj* gobj)
{
    int i;
    HSD_Fog* fog = gobj->hsd_obj;
    if (gm_804D6818 == 0) {
        for (i = 0; i < gm_804D681C; i++) {
            HSD_FogInterpretAnim(fog);
        }
    }
}

/* 3DD0F0 */ static HSD_CObjDesc gm_803DD0F0 = { 0 };

void gm_801AC6D8_OnEnter(void* unused)
{
    HSD_JObj* jobj_arr[2];
    HSD_GObj* gobj;
    HSD_CObj* cobj;
    int i;
    int const gx_link = 11;
    PAD_STACK(0x10);

    efLib_8005B4B8();
    efAsync_8006737C(0);
    gm_804D67F8 = HSD_MemAlloc(sizeof(struct gm_804D67F8_t));
    gm_804D67FC = HSD_MemAlloc(sizeof(struct gm_804D67FC_t));
    HSD_SisLib_803A62A0(0, "SdStRoll.dat", "SIS_StRollData");
    HSD_SisLib_803A611C(0, (void*) -1, 9, 13, 0, 18, 0, 19);
    lbAudioAx_80026F2C(28);
    lbAudioAx_8002702C(16, 0x4000000000000ULL);
    lbAudioAx_80027168();
    gm_804D683C = lbArchive_80016DBC(
        "GmStRoll.dat", &gm_804D6840, "ScGamRegStaffroll_scene_data",
        &gm_804D6844, "ScGamRegStaffrollNames_scene_modelset", 0);
    {
        gobj = GObj_Create(17, 19, 0);
        cobj = HSD_CObjLoadDesc(gm_804D6840->cameras[0].desc);
        gm_804D6830 = cobj;
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
        GObj_SetupGXLinkMax(gobj, fn_801AA854, 5);
        gobj->gxlink_prios = 0x189;
        HSD_CObjAddAnim(cobj, gm_804D6840->cameras[0].anims[0]);
        HSD_CObjReqAnim(cobj, 0.0F);
        HSD_GObjProc_8038FD54(gobj, fn_801AA7F8, 0);
    }
    {
        HSD_GObj* gobj = GObj_Create(19, 20, 0);
        HSD_CObj* cobj = HSD_CObjLoadDesc(&gm_803DD0F0);
        gm_804D6834 = cobj;
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
        GObj_SetupGXLinkMax(gobj, fn_801AAA28, 8);
        gobj->gxlink_prios = 1LL << gx_link;
    }
    {
        HSD_GObj* gobj = GObj_Create(gx_link, 3, 0);
        HSD_LObj* lobj = lb_80011AC4(gm_804D6840->lights);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A, lobj);
        GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0);
        HSD_LObjReqAnimAll(lobj, 0.0F);
        HSD_GObjProc_8038FD54(gobj, fn_801AAABC, 0);
    }
    {
        HSD_GObj* gobj = GObj_Create(0xA, 3, 0);
        HSD_Fog* fog = HSD_FogLoadDesc(gm_804D6840->fogs[0].desc);
        gm_804D6838 = fog;
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7848, fog);
        GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 3, 0);
        HSD_Fog_8037DE7C(fog, gm_804D6840->fogs[0].anims[0]->aobjdesc);
        HSD_FogReqAnim(fog, 0.0F);
        HSD_GObjProc_8038FD54(gobj, fn_801AC67C, 0);
    }
    {
        HSD_GObj* gobj = GObj_Create(3, 5, 0);
        HSD_JObj* jobj = HSD_JObjLoadJoint(gm_804D6840->models[1]->joint);
        gm_804D682C = jobj;
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 3, 0);
        gm_8016895C(jobj, gm_804D6840->models[1], 0);
        HSD_JObjReqAnimAll(jobj, 0.0F);
        {
            if (lbLang_IsSettingUS()) {
                lb_80011E24(jobj, jobj_arr, 103, 20, -1);
                M2C_FIELD(M2C_FIELD(jobj_arr[1]->u.dobj->mobj, void**, 8),
                          s32*, 0x58) =
                    M2C_FIELD(M2C_FIELD(jobj_arr[1]->u.dobj->mobj, void**, 8),
                              s32*, 0x58);
            }
        }
        HSD_GObjProc_8038FD54(gobj, fn_801AAB18, 0);
    }
    {
        HSD_GObj* gobj = GObj_Create(14, 15, 0);
        HSD_JObj* jobj = HSD_JObjLoadJoint(gm_804D6844[0]->joint);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, NULL, 9, 0);
        gm_8016895C(jobj, gm_804D6844[0], 0);
        HSD_JObjReqAnimAll(jobj, 0.0F);
        {
            /// @todo Length of #gm_804D6844 is 10
            for (i = 1; i < 10; i++) {
                HSD_JObj* jobj = HSD_JObjLoadJoint(gm_804D6844[i]->joint);
                gm_8016895C(jobj, gm_804D6844[i], 0);
                HSD_JObjReqAnimAll(jobj, 0.0F);
                while (jobj->child != NULL) {
                    HSD_JObjReparent(jobj->child, jobj);
                }
            }
        }
        HSD_GObjProc_8038FD54(gobj, fn_801AAB74, 1);
    }
    {
        HSD_GObj* gobj = GObj_Create(14, 15, 0);
        HSD_JObj* jobj = HSD_JObjLoadJoint(gm_804D6840->models[0]->joint);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, gx_link, 0);
        gm_8016895C(jobj, gm_804D6840->models[0], 0);
        lb_80011E24(jobj, jobj_arr, ARRAY_SIZE(jobj_arr), 20, -1);
        HSD_JObjReqAnimAll(jobj_arr[0], 0.0F);
        HSD_JObjReqAnimAll(jobj_arr[1], 0.0F);
        HSD_GObjProc_8038FD54(gobj, fn_801AB200, 13);
    }
    lbAudioAx_80027648();
    {
        u32 r = HSD_Randi(5);
        lbAudioAx_80023F28(lbAudioAx_8002305C(gm_801BEFB0(), !-r));
        lbBgFlash_800209F4();
        gm_804D6804.x0 = gm_804D6804.x4 = 0.0F;
        memzero(gm_804D67F8, sizeof(struct gm_804D67F8_t));
        gm_80480D58[0] = 0;
        gm_80480D58[1] = 0;
        gm_80480D58[2] = 0;
        gm_80480D58[3] = 0;
        gm_80480D58[4] = 0;
        gm_80480D58[5] = 0;
        gm_804D680C = NULL;
        gm_804D6810 = 0;
        gm_804D6814 = 0;
        gm_804D6818 = 0;
        gm_804D681C = 1;
        gm_804D6820 = 0;
        gm_804D6824 = gm_804D6828 = 0.0F;
        gm_804D6848 = 0;
        gm_804D684C = 0;
    }
}

void gm_801ACC90_OnLeave(void* unused) {}
