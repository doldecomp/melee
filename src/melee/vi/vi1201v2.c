#include "vi/vi1201v2.h"

#include "vi.h"

#include "cm/camera.h"
#include "ft/ftdemo.h"
#include "gm/gm_1601.h"
#include "gm/gm_unsplit.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "it/item.h"
#include "lb/lb_00F9.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbshadow.h"
#include "mn/mnmain.h"
#include "mp/mpcoll.h"
#include "pl/player.h"
#include "sc/types.h"

#include "vi/forward.h"

#include <baselib/aobj.h>
#include <baselib/cobj.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>

Vec3 un_804002F8 = { 0.0f, 0.0f, 0.0f };
Vec3 un_80400304 = { 0.0f, 0.0f, 0.0f };

static SceneDesc* un_804D7010;
static HSD_Archive* un_804D7018;
static HSD_Archive* un_804D701C;
static HSD_JObj* un_804D7024;
static un_804D7004_t un_804D7038;

void un_803204B0(int arg0, int arg1)
{
    M2C_FIELD(&un_804D7038, u8*, 0) = arg0;
    M2C_FIELD(&un_804D7038, u8*, 1) = arg1;
}

void un_803204C0(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_803204E4(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_80320508(CharacterKind char_kind, int costume)
{
    char pad[16];

    Camera_80028B9C(6);
    lb_8000FCDC();
    mpColl_80041C78();
    Ground_801C0378(0x40);
    Stage_802251E8(0x20, 0);
    Item_80266FA8();
    Item_80266FCC();
    Stage_8022524C();
    Stage_8022532C(0x20, 0x1A);
    ftDemo_ObjAllocInit();
    Player_InitAllPlayers();
    Player_80036E20(char_kind, un_804D7018, 3);
    Player_SetPlayerCharacter(0, char_kind);
    Player_SetCostumeId(0, costume);
    Player_SetPlayerId(0, 0);
    Player_SetSlottype(0, 2);
    Player_SetFacingDirection(0, -1.0f);
    Player_80032768(0, &un_804002F8);
    Player_80036F34(0, 8);
    Player_SetPlayerAndEntityFacingDirection(0, 0.0f);
}

void un_803205F4(void)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    char pad[16];

    gobj = GObj_Create(0xE, 0xF, 0);
    jobj = HSD_JObjLoadJoint(un_804D7010->models[1]->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    gm_8016895C(jobj, un_804D7010->models[1], 0);
    HSD_JObjReqAnimAll(jobj, 251.0f);
    HSD_GObjProc_8038FD54(gobj, mn_8022EAE0, 0);

    Player_80036E20(0x1D, un_804D701C, 8);
    Player_SetPlayerCharacter(1, 0x1D);
    Player_SetCostumeId(1, 0);
    Player_SetPlayerId(1, 0);
    Player_SetSlottype(1, 2);
    Player_SetFacingDirection(1, -1.0f);
    Player_80032768(1, &un_80400304);
    Player_80036F34(1, 0xF);
    Player_SetScale(1, 1.0f / Player_80032BB0(1));

    lbAudioAx_80026F2C(0x18);
    lbAudioAx_8002702C(8, 0x0020000000000000ULL);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

void un_8032074C(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    char pad[24];
    HSD_JObjAnimAll(jobj);
    if (mn_8022F298(jobj) == 1.0F) {
        if (un_804D7030 != NULL) {
            HSD_GObjPLink_80390228(un_804D7030);
            un_804D7030 = NULL;
        }
        if (un_804D7034 != NULL) {
            HSD_GObjPLink_80390228(un_804D7034);
            un_804D7034 = NULL;
        }
        un_803205F4();
    }
}

void un_803207C4(void)
{
    HSD_JObj* jobj;
    HSD_GObj* gobj;
    s32 i = 0;

    while (un_804D7010->models[i] != NULL) {
        if (i != 1) {
            gobj = GObj_Create(0xE, 0xF, 0);
            jobj = HSD_JObjLoadJoint(un_804D7010->models[i]->joint);
            HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
            GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
            gm_8016895C(jobj, un_804D7010->models[i], 0);
            HSD_JObjReqAnimAll(jobj, 0.0f);
            HSD_JObjAnimAll(jobj);
            if (i == 0) {
                HSD_GObjProc_8038FD54(gobj, un_8032074C, 0);
                lb_80011E24(jobj, &un_804D7024, 2, -1);
            } else {
                HSD_GObjProc_8038FD54(gobj, mn_8022EAE0, 0);
            }
        }
        i++;
    }
}

void un_803208F0(HSD_GObj* gobj)
{
    u8* colors;
    char pad[8];
    lbShadow_8000F38C(0);
    if (HSD_CObjSetCurrent(GET_COBJ(gobj)) != 0) {
        colors = &un_804D7028;
        HSD_SetEraseColor(colors[0], colors[1], colors[2], colors[3]);
        HSD_CObjEraseScreen(GET_COBJ(gobj), 1, 0, 1);
        vi_8031CA04(gobj);
        gobj->gxlink_prios = 0x881;
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

void un_80320984(HSD_GObj* gobj)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    HSD_CObjAnim(cobj);
    if (cobj->aobj->curr_frame == 130.0F || cobj->aobj->curr_frame == 190.0F) {
        vi_8031C9B4(0xD, 0);
    }
    if (cobj->aobj->curr_frame == 251.0F) {
        vi_8031C9B4(1, 0xDB);
    }
    if (cobj->aobj->curr_frame == cobj->aobj->end_frame) {
        lb_800145F4();
        gm_801A4B60();
    }
}

void fn_80320A1C(HSD_GObj* gobj)
{
    HSD_FogInterpretAnim(gobj->hsd_obj);
}

void un_803210EC_OnFrame(void)
{
    vi_8031CAAC();
}
