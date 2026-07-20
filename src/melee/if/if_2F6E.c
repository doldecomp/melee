#include "if_2F6E.h"

#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <melee/gm/gm_16AE.h>
#include <melee/gm/types.h>
#include <melee/if/if_2F72.h>
#include <melee/if/ifall.h>
#include <melee/if/types.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbspdisplay.h>
#include <melee/sc/types.h>

/* 3F9628 */ Element_803F9628 ifStatus_803F9628[8] = {
    { NULL, 0, if_802F74D0, 0x7C860U, 8, 0, { 0 }, 0, NULL, NULL, 0, 0 },
    { NULL, 0, if_802F73C4, 0xC351U, 0, 0, { 0 }, 0, NULL, NULL, 0, 0 },
    { NULL, 0, if_802F74D0, 0x7C85EU, 0, 0, { 0 }, 0, NULL, NULL, 0, 0 },
    { NULL, 0, if_802F73C4, 0x7C85DU, 0, 0, { 0 }, 0, NULL, NULL, 0, 0 },
    { NULL, 0, if_802F73C4, 0x7C857U, 10, 0, { 0 }, 0, NULL, NULL, 0, 0 },
    { NULL, 0, if_802F74D0, 0x7C855U, 8, 0, { 0 }, 0, NULL, NULL, 0, 0 },
    { NULL, 0, if_802F74D0, 0x9C48U, 0, 0, { 0 }, 0, NULL, NULL, 0, 0 },
    { NULL, 0, if_802F74D0, 0x9C46U, 0, 0, { 0 }, 0, NULL, NULL, 0, 0 },
};

void ifStatus_802F6EA4(int arg0, int arg1, int arg2, int arg3, Event arg4,
                       Event arg5)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;

    if (arg0 == 8) {
        if (arg4 != NULL) {
            ((IfStatusCb) arg4)(-1);
        }
        if (arg5 != NULL) {
            ((IfStatusCb) arg5)(-1);
        }
        if (arg1 >= 0) {
            lbAudioAx_800237A8(arg1, 0x7F, 0x40);
        }
        if (arg1 >= 0) {
            lbAudioAx_800237A8(arg2, 0x7F, 0x40);
        }
    } else {
        Element_803F9628* e;
        e = &ifStatus_803F9628[arg0];
        e->x20 = arg1;
        e->x24 = arg2;
        e->x11 = arg3;
        if (e->x0 != NULL) {
            HSD_GObjPLink_80390228(e->x0);
        }
        gobj = GObj_Create(0xE, 0xE, 0);
        jobj = HSD_JObjLoadJoint(e->x14->joint);
        lb_80011C18(jobj, 0x08000000);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
        if (e->x8 != NULL) {
            HSD_GObj_SetupProc(gobj, e->x8, 0);
        }
        lb_8000C0E8(jobj, 0, e->x14);
        HSD_JObjReqAnimAll(jobj, 0.0f);
        HSD_JObjAnimAll(jobj);
        e->x12.x0 = 0;
        e->x12.x1 = 0;
        e->x12.x2 = 0;
        e->x0 = gobj;
        e->x18 = (IfStatusCb) arg4;
        e->x1C = (IfStatusCb) arg5;
    }
}

void ifStatus_802F7034(UNK_T arg0)
{
    lbl_8046B6A0_t* big_thing;
    int a;
    int b;
    int c;
    u8 unkB;
    u8 mr;

    big_thing = gm_16AE_GetUnkData_0();
    if (big_thing->unk_10 != 0) {
        a = big_thing->unk_10 - 1;
    } else {
        a = -1;
    }
    if (big_thing->unk_14 != 0) {
        b = big_thing->unk_14 - 1;
    } else {
        b = -1;
    }
    if (big_thing->unk_18 != 0) {
        c = big_thing->unk_18;
    } else {
        c = 0;
    }

    unkB = big_thing->unk_B;
    if (unkB != 0) {
        ifStatus_802F6EA4(unkB - 1, a, b, c, arg0, NULL);
        return;
    }
    mr = big_thing->match_result;
    if (mr == OUTCOME_TIMEOUT) {
        ifStatus_802F6EA4(0, a, b, c, arg0, NULL);
        return;
    }
    if (big_thing->x24C8.x5_1) {
        if (mr == OUTCOME_UNK_1P_BONUS_STAGE_END) {
            ifStatus_802F6EA4(7, a, b, c, arg0, NULL);
            return;
        }
        ifStatus_802F6EA4(6, a, b, c, arg0, NULL);
        return;
    }
    ifStatus_802F6EA4(5, a, b, c, arg0, NULL);
}

void ifStatus_802F7134(void)
{
    u8 _[8];
    HSD_Archive** archive;
    DynamicModelDesc** volatile models;
    int i;

    for (i = 0; i < 8; i++) {
        ifStatus_803F9628[i].x0 = NULL;
        ifStatus_803F9628[i].x4 = 0;
    }

    archive = ifAll_GetArchive();
    lbArchive_LoadSections(*archive, (void**) &models, "ScInfCnt_scene_models",
                           0);

    for (i = 0; i < 8; i++) {
        ifStatus_803F9628[i].x14 = models[i];
    }
}

/// free
void ifStatus_802F7220(void)
{
    s32 i;
    for (i = 0; i < 8; i++) {
        if (ifStatus_803F9628[i].x0 != NULL) {
            HSD_GObjPLink_80390228(ifStatus_803F9628[i].x0);
            ifStatus_803F9628[i].x0 = NULL;
        }
    }
}
