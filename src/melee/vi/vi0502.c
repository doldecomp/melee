#include "vi0502.h"

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ef/eflib.h"

#include "ft/forward.h"

#include "ft/ftdemo.h"
#include "gm/gm_unsplit.h"
#include "gr/grlib.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "it/item.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbshadow.h"
#include "mp/mpcoll.h"
#include "pl/player.h"
#include "sc/types.h"
#include "vi/types.h"
#include "vi/vi.h"

#include <dolphin/gx.h>
#include <baselib/aobj.h>
#include <baselib/cobj.h>
#include <baselib/displayfunc.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/lobj.h>
#include <baselib/mtx.h>
#include <baselib/wobj.h>

Vec3 initial_pos = { 0, -3.0f, 0 };

static SceneDesc* un_804D6F90;
static HSD_Archive* un_804D6F94;
static HSD_Archive* un_804D6F98;
static HSD_Archive* un_804D6F9C;
static GXColor erase_colors_vi0502;
static HSD_GObj* kirby_gobj;
static ViCharaDesc* un_804D6FA8;

void un_8031E110(int arg0, int arg1, int arg2)
{
    un_804D6FA8->p1_char_index = arg0;
    un_804D6FA8->p1_costume_index = arg1;
    un_804D6FA8->p2_costume_index = arg2;
}

void vi0502_8031E124(CharacterKind player_kind, int player_costume,
                     int kirby_costume)
{
    HSD_JObj* jobj;
    VecMtxPtr pmtx;

    Camera_80028B9C(6);
    lb_8000FCDC();
    mpColl_80041C78();
    Ground_801C0378(0x40);
    Stage_802251E8(17, 0);
    Item_80266FA8();
    Item_80266FCC();
    Ground_801C04BC(0.7f);
    Stage_8022524C();
    Stage_8022532C(17, 0);

    ftDemo_ObjAllocInit();
    Player_InitAllPlayers();

    Player_80036E20(player_kind, un_804D6F94, 3);
    Player_SetPlayerCharacter(0, player_kind);
    Player_SetCostumeId(0, player_costume);
    Player_SetPlayerId(0, 0);
    Player_SetSlottype(0, Gm_PKind_Demo);
    Player_SetFacingDirection(0, 1.0f);
    Player_80032768(0, &initial_pos);
    Player_80036F34(0, 8);

    Player_80036E20(CKIND_KIRBY, un_804D6F9C, 7);
    Player_SetPlayerCharacter(1, CKIND_KIRBY);
    Player_SetCostumeId(1, kirby_costume);
    Player_SetPlayerId(1, 0);
    Player_SetSlottype(1, Gm_PKind_Demo);
    Player_SetFacingDirection(1, 1.0f);
    Player_80036F34(1, 14);

    kirby_gobj = Player_GetEntity(1);
    jobj = GET_JOBJ(kirby_gobj);
    HSD_JObjReqAnimAll(jobj, 120.0f);
    HSD_JObjAnimAll(jobj);
    jobj = GET_JOBJ(kirby_gobj);
    pmtx = grLib_801C9A10();
    HSD_JObjGetTranslation2(jobj, &pmtx[1]);

    HSD_JObjReqAnimAll(jobj, 0.0f);

    lbAudioAx_80026F2C(0x1C);
    lbAudioAx_8002702C(12, 0x80000004000);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

void vi0502_8031E304(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

static void vi0502_8031E328(HSD_GObj* gobj, int unused)
{
    HSD_CObj* cobj;
    lbShadow_8000F38C(0);
    cobj = GET_COBJ(gobj);
    if (HSD_CObjSetCurrent(cobj)) {
        HSD_SetEraseColor(erase_colors_vi0502.r, erase_colors_vi0502.g,
                          erase_colors_vi0502.b, erase_colors_vi0502.a);
        cobj = GET_COBJ(gobj);
        HSD_CObjEraseScreen(cobj, 1, 0, 1);
        vi_8031CA04(gobj);
        gobj->gxlink_prios = 0x281;
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

void vi0502_RunFrame(HSD_GObj* gobj)
{
    HSD_CObj* cobj;

    cobj = GET_COBJ(gobj);
    HSD_CObjAnim(cobj);

    if (30.0f == cobj->eyepos->aobj->curr_frame) {
        vi_8031C9B4(14, 0);
        lbAudioAx_800237A8(430009, 0x7F, 0x40);
    }
    if (cobj->eyepos->aobj->curr_frame == cobj->eyepos->aobj->end_frame) {
        lb_800145F4();
        gm_801A4B60();
    }
}

void un_8031E444_OnEnter(void* arg)
{
    u8* input = arg;
    HSD_GObj* gobj;
    HSD_CObj* cobj;
    HSD_Fog* fog;
    HSD_LObj* lobj;
    HSD_JObj* jobj;
    CharacterKind char_kind;
    s32 i;

    lbAudioAx_800236DC();
    efLib_8005B4B8();
    efAsync_8006737C(0);

    char_kind = input[0];

    un_804D6F9C = lbArchive_LoadSymbols("Vi0502.dat", &un_804D6F90,
                                        "visual0502Scene", NULL);
    un_804D6F94 = lbArchive_LoadSymbols(viGetCharAnimByIndex(char_kind), NULL);
    un_804D6F98 = lbArchive_LoadSymbols("IrAls.dat", NULL);

    gobj = GObj_Create(0xB, 3, 0);
    fog = HSD_FogLoadDesc(un_804D6F90->fogs->desc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7848, fog);
    GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 0, 0);
    *(GXColor*) &erase_colors_vi0502 = fog->color;

    gobj = GObj_Create(0xB, 3, 0);
    lobj = lb_80011AC4(un_804D6F90->lights);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0);

    gobj = GObj_Create(0x13, 0x14, 0);
    cobj =
        lb_80013B14((HSD_CameraDescPerspective*) un_804D6F90->cameras->desc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, (void (*)(HSD_GObj*, int)) vi0502_8031E328, 5);
    HSD_CObjAddAnim(cobj, un_804D6F90->cameras->anims[0]);
    HSD_CObjReqAnim(cobj, 0.0f);
    HSD_CObjAnim(cobj);
    HSD_GObjProc_8038FD54(gobj, vi0502_RunFrame, 0);

    for (i = 0; un_804D6F90->models[i] != NULL; i++) {
        gobj = GObj_Create(0xE, 0xF, 0);
        jobj = HSD_JObjLoadJoint(un_804D6F90->models[i]->joint);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 9, 0);
        gm_8016895C(jobj, un_804D6F90->models[i], 0);
        HSD_JObjReqAnimAll(jobj, 0.0f);
        HSD_JObjAnimAll(jobj);
        HSD_GObjProc_8038FD54(gobj, vi0502_8031E304, 0x17);
    }

    vi0502_8031E124(input[0], input[1], input[3]);
}
