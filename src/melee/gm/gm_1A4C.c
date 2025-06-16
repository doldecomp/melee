#include "gm_1A4C.h"

#include "gm_1A4C.static.h"

#include "gm_1601.h"
#include "gm_1A36.h"
#include "gm_1B03.h"

#include "baselib/fog.h"
#include "baselib/gobjgxlink.h"
#include "baselib/gobjobject.h"
#include "baselib/gobjproc.h"
#include "baselib/lobj.h"
#include "baselib/memory.h"
#include "baselib/random.h"
#include "baselib/sislib.h"
#include "db/db.h"
#include "ef/efasync.h"
#include "ef/eflib.h"
#include "gm/gmmain_lib.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbbgflash.h"
#include "lb/lbcardgame.h"
#include "lb/lbdvd.h"
#include "lb/lblanguage.h"
#include "lb/lbmthp.h"
#include "lb/lbsnap.h"
#include "lb/types.h"
#include "mn/mngallery.h"
#include "mn/types.h"
#include "ty/toy.h"
#include "un/un_2FC9.h"

#include <dolphin/dvd.h>
#include <dolphin/os/OSRtc.h>
#include <dolphin/vi.h>
#include <baselib/controller.h>
#include <baselib/devcom.h>
#include <baselib/sobjlib.h>
#include <baselib/video.h>

MinorSceneHandler* gm_801A50A0(void)
{
    return gm_803DA920;
}

MajorScene* gm_801A50AC(void)
{
    return &gm_803DACA4;
}

/// #gm_801A50B8

/// #gm_801A5130

/// #gm_801A51A8

/// #gm_801A5220

s8* gm_801A5244(void)
{
    return &gmMainLib_804D3EE0->unk_590;
}

UNK_T gm_801A5250(void)
{
    return &gm_804D6730;
}

/// #gm_801A5258

/// #gm_801A52D0

/// #gm_801A5360

/// #gm_801A5598

/// #gm_801A55C4

/// #gm_801A55EC

void gm_801A5614(void) {}

/// #gm_801A5618

/// #gm_801A5680

/// #gm_801A5754

/// #gm_801A57A8

/// #gm_801A583C

/// #gm_801A5AF0

/// #gm_801A5C3C

/// #gm_801A5EC8

/// #gm_801A5F00

/// #gm_801A5F64

/// #gm_801A6254

/// #gm_801A6308

/// #gm_801A632C_OnEnter

/// #gm_801A637C_OnEnter

/// #gm_801A64A8_OnFrame

/// #gm_801A659C

/// #gm_801A6630

/// #fn_801A6664

/// #fn_801A6844

/// #fn_801A6868

/// #gm_801A68D8

/// #fn_801A6A48

/// #fn_801A6ACC

/// #fn_801A6B6C

/// #fn_801A6C30

/// #gm_801A6C54

/// #fn_801A6D78

/// #gm_801A6DC0

/// #gm_801A6EE4

/// #gm_801A7070_OnEnter

/// #gm_801A79D4_OnFrame

/// #fn_801A7A44

/// #fn_801A7A68

/// #fn_801A7A8C

/// #gm_801A7B00

/// #fn_801A7FB4

/// #fn_801A80CC

/// #fn_801A80F0

/// #gm_801A8114

/// #fn_801A851C

/// #gm_801A85E4

/// #gm_801A8D54

/// #gm_801A9094

/// #fn_801A9498

/// #fn_801A94BC

/// #gm_801A9630

/// #gm_801A9B30_OnEnter

/// #gm_801A9D0C_OnFrame

/// #gm_801A9DD0

/// #fn_801A9FCC

/// #fn_801AA0E8

/// #gm_801AA110_OnEnter

/// #gm_801AA28C_OnFrame

/// #gm_801AA644

/// #gm_801AA664

/// #gm_801AA688

/// #gm_801AA6D8

/// #gm_801AA6FC

/// #gm_801AA774

/// #gm_801AA7C4_OnFrame

/// #fn_801AA7F8

/// #fn_801AA854

/// #fn_801AAA28

/// #fn_801AAABC

/// #fn_801AAB18

/// #fn_801AAB74

/// #fn_801AB200

/// #fn_801AC67C

void gm_801AC6D8_OnEnter(void)
{
    HSD_JObj* jobj_arr[2];
    int const gx_link = 11;

    efLib_8005B4B8();
    efAsync_8006737C(0);
    gm_804D67F8 = HSD_MemAlloc(sizeof(struct gm_804D67F8_t));
    gm_804D67FC = HSD_MemAlloc(sizeof(struct gm_804D67FC_t));
    HSD_SisLib_803A62A0(0, "SdStRoll.dat", "SIS_StRollData");
    HSD_SisLib_803A611C(0, -1, 9, 13, 0, 18, 0, 19);
    lbAudioAx_8002702C(16, lbAudioAx_80026F2C(28));
    lbAudioAx_80027168();
    gm_804D683C = lbArchive_80016DBC(
        "GmStRoll.dat", (void**) &gm_804D6840, "ScGamRegStaffroll_scene_data",
        &gm_804D6844, "ScGamRegStaffrollNames_scene_modelset", 0);
    {
        HSD_GObj* gobj = GObj_Create(17, 19, 0);
        HSD_CObj* cobj = HSD_CObjLoadDesc(gm_804D6840->cameras->desc);
        gm_804D6830 = cobj;
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, gm_804D6830);
        GObj_SetupGXLinkMax(gobj, fn_801AA854, 5);
        gobj->gxlink_prios = 0x189;
        HSD_CObjAddAnim(cobj, gm_804D6840->cameras->anims[0]);
        HSD_CObjReqAnim(cobj, 0.0f);
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
        HSD_LObjReqAnimAll(lobj, 0.0f);
        HSD_GObjProc_8038FD54(gobj, fn_801AAABC, 0);
    }
    {
        HSD_GObj* gobj = GObj_Create(0xA, 3, 0);
        HSD_Fog* fog = HSD_FogLoadDesc(gm_804D6840->fogs->desc);
        gm_804D6838 = fog;
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7848, fog);
        GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 3, 0);
        HSD_Fog_8037DE7C(fog, gm_804D6840->fogs->anims[0][0]);
        HSD_FogReqAnim(fog, 0.0f);
        HSD_GObjProc_8038FD54(gobj, fn_801AC67C, 0);
    }
    {
        HSD_GObj* gobj = GObj_Create(3, 5, 0);
        HSD_JObj* jobj = HSD_JObjLoadJoint(gm_804D6840->models[1][0]);
        gm_804D682C = jobj;
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 3, 0);
        gm_8016895C(jobj, gm_804D6840->models[1], 0);
        HSD_JObjReqAnimAll(jobj, 0.0f);
        {
            if (lbLang_IsSettingUS()) {
                lb_80011E24(jobj, jobj_arr, 103, 20, -1);
                M2C_FIELD(M2C_FIELD(M2C_FIELD(jobj_arr[0]->u.ptcl, void**, 8),
                                    void**, 8),
                          s32*, 0x58) =
                    M2C_FIELD(
                        M2C_FIELD(M2C_FIELD(jobj_arr[1]->u.ptcl, void**, 8),
                                  void**, 8),
                        s32*, 0x58);
            }
        }
        HSD_GObjProc_8038FD54(gobj, fn_801AAB18, 0);
    }
    {
        HSD_GObj* gobj = GObj_Create(14, 15, 0);
        HSD_JObj* jobj = HSD_JObjLoadJoint(gm_804D6844[0][0]);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, NULL, 9, 0);
        gm_8016895C(jobj, gm_804D6844[0], 0);
        HSD_JObjReqAnimAll(jobj, 0.0f);
        {
            ssize_t i;
            HSD_JObj* cur;
            /// @todo Length of #gm_804D6844 is 10
            for (i = 1; i < 10; i++) {
                HSD_JObj* jobj = HSD_JObjLoadJoint(gm_804D6844[i][0]);
                gm_8016895C(jobj, *gm_804D6844[i], 0);
                HSD_JObjReqAnimAll(jobj, 0.0f);
                {
                    for (cur = jobj->child; cur != NULL;) {
                        HSD_JObjReparent(cur, jobj);
                    }
                }
            }
        }
        HSD_GObjProc_8038FD54(gobj, fn_801AAB74, 1);
    }
    {
        HSD_GObj* gobj = GObj_Create(14, 15, 0);
        HSD_JObj* jobj = HSD_JObjLoadJoint(gm_804D6840->models[0][0]);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, gx_link, 0);
        gm_8016895C(jobj, gm_804D6840->models[0], 0);
        lb_80011E24(jobj, jobj_arr, ARRAY_SIZE(jobj_arr), 20, -1);
        HSD_JObjReqAnimAll(jobj_arr[0], 0.0f);
        HSD_JObjReqAnimAll(jobj_arr[1], 0.0f);
        HSD_GObjProc_8038FD54(gobj, fn_801AB200, 13);
    }
    lbAudioAx_80027648();
    {
        s32 r = HSD_Randi(5);
        lbAudioAx_80023F28(lbAudioAx_8002305C(gm_801BEFB0(), r == 0));
        lbBgFlash_800209F4();
        gm_804D6804.x0 = gm_804D6804.x4 = 0.0F;
        memzero(gm_804D67F8, sizeof(struct gm_804D67F8_t));
        gm_80480D58.x0 = 0;
        gm_80480D58.x4 = 0;
        gm_80480D58.x8 = 0;
        gm_80480D58.xC = 0;
        gm_80480D58.x10 = 0;
        gm_80480D58.x14 = 0;
        gm_804D680C = 0;
        gm_804D6810 = 0;
        gm_804D6814 = 0;
        gm_804D6818 = 0;
        gm_804D681C = 1;
        gm_804D6820 = 0;
        gm_804D6824 = gm_804D6828 = 0.0f;
        gm_804D6848 = 0;
        gm_804D684C = 0;
    }
}

void gm_801ACC90_OnLeave(void) {}

UNK_T gm_801ACC94(void)
{
    return &gm_803DD2C0;
}

/// #gm_801ACCA0_OnEnter

/// #gm_801ACD8C_OnFrame

/// #gm_801ACE94_OnEnter

/// #gm_801ACF8C_OnFrame

/// #gm_801AD088

/// #gm_801AD254

/// #gm_801AD620_OnFrame

/// #gm_801AD874_OnEnter

/// #gm_801AD8EC_OnLeave

/// #fn_801AD920

/// #gm_801ADB04

/// #gm_801ADC88_OnFrame

/// #gm_801ADCE4_OnEnter

/// #gm_801ADDA8_OnLeave

/// #gm_801ADDD8

void gm_801ADDD8(void)
{
    memzero(&gm_803DD4D0, sizeof(gm_803DD4D0));
    gm_803DD4D0.unkC = -0x3E7;
    gm_801AEBB0();
}

extern int gm_804D686C;

bool gm_801ADE1C(int arg0, int arg1, f32 arg2, f32 arg3)
{
    HSD_Text* text;
    struct unkd4d0* temp_r0;
    struct unkd4d0* next;
    struct unkd4d0* cur;

    cur = &gm_803DD4D0;
    next = HSD_MemAlloc(sizeof(struct unkd4d0));
    memzero(next, sizeof(struct unkd4d0));
    next->unkC = arg0;
    next->unk10 = arg1;
    next->unk14 = arg2;
    next->unk18 = arg3;

    for (; true; cur = cur->next) {

        if (cur->next != NULL) {
            continue;
        }

        cur->next = next;
        next->unk4 = cur;
        next->next = NULL;
        next->unk8 = NULL;
        next->unk1C = gm_801AECC4(1);
        if (next->unk1C != NULL) {
            HSD_JObjSetTranslateX(GET_JOBJ(next->unk1C), next->unk14);
        }
        if (next->unk1C != NULL) {
            HSD_JObjSetTranslateY(GET_JOBJ(next->unk1C), next->unk18);
        }
        next->unk20 = HSD_SisLib_803A5ACC(3, (s32) gm_804D686C, -14.0f + next->unk14, -9.0f - next->unk18, 0.0f, 30.8f, 4.6f);
        text = next->unk20;
        text->x34.x = 0.079f;
        text->x34.y = 0.079f;
        next->unk20->x4A = 0;
        next->unk20->x48 = 0;
        HSD_SisLib_803A6368(next->unk20, next->unk10);
        break;
    }

    return true;
}

/// #gm_801AE050

void gm_801AE44C(int arg0, float val)
{
    struct unkd4d0* cur;

    for (cur = gm_803DD4D0.next; cur != NULL; cur = cur->next) {
        if (cur->unkC == arg0) {
            HSD_JObj* jobj = GET_JOBJ(cur->unk1C);
            HSD_JObjAddTranslationY(jobj->child->child->child->next, -val);
        }
    }
}

void gm_801AE544(int arg0, float val)
{
    struct unkd4d0* cur;

    for (cur = gm_803DD4D0.next; cur != NULL; cur = cur->next) {
        if (cur->unkC == arg0) {
            HSD_JObj* jobj = GET_JOBJ(cur->unk1C);
            HSD_JObjAddTranslationY(jobj->child->child->child->next->child, -val);
        }
    }
}

/// #gm_801AE640

/// #gm_801AE74C

/// #gm_801AE848

/// #fn_801AE948

void gm_801AEBB0(void)
{
    HSD_GObj* gobj;
    PAD_STACK(4);

    lbArchive_80016DBC("NtMsgWin.dat", (void**) &gm_804D6868,
            "ScNtcCommon_scene_data", 0);

    if (lbLang_IsSavedLanguageUS()) {
        HSD_SisLib_803A62A0(3, "SdMsgBox.usd", "SIS_MessageData");
    } else {
        HSD_SisLib_803A62A0(3, "SdMsgBox.dat", "SIS_MessageData");
    }

    gobj = GObj_Create(20, 21, 0);
    {
        HSD_CObj* desc = HSD_CObjLoadDesc(gm_804D6868->cameras[0]);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, desc);
    }
    GObj_SetupGXLinkMax(gobj, HSD_GObj_803910D8, 0);
    gobj->gxlink_prios = 0x4000;

    gm_804D686C = HSD_SisLib_803A611C(3, (u32) gobj, 9, 13, 0, 14, 0, 18);
    HSD_GObjProc_8038FD54(GObj_Create(15, 17, 0), fn_801AE948, 0);
}

HSD_GObj* gm_801AECC4(int model_idx)
{
    HSD_GObj* gobj = GObj_Create(9, 13, 0);
    HSD_JObj* jobj = HSD_JObjLoadJoint(gm_804D6868->models[model_idx]->joint);
    HSD_GObjObject_80390A70(gobj, (u8) HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 14, 0);
    gm_8016895C(jobj, gm_804D6868->models[model_idx], 0);
    HSD_JObjReqAnimAll(jobj, 0.0F);
    HSD_JObjAnimAll(jobj);
    if (model_idx == 1) {
        HSD_JObjSetFlagsAll(jobj->child->child->next->child->next, 0x10);
        HSD_JObjSetFlagsAll(jobj->child->child->next->next, 0x10);
    }
    return gobj;
}

static HSD_PadStatus* get_master_status(u8 i)
{
    return &HSD_PadMasterStatus[i];
}

static HSD_PadStatus* get_copy_status(u8 i)
{
    return &HSD_PadCopyStatus[i];
}

u32 gm_801AEDC8(void)
{
    u32 result = 0;
    int i;
    for (i = 0; i < 4; i++) {
        if (get_master_status(i)->err == 0) {
            result |= get_copy_status(i)->trigger;
        }
    }
    return result;
}
