#include "vi/vi1201v1.h"

#include "vi.h"

#include "baselib/forward.h"

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/ft_0C31.h"
#include "ft/ftdemo.h"
#include "gm/gm_1601.h"
#include "gm/gm_unsplit.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbshadow.h"
#include "mn/mnmain.h"
#include "mp/mpcoll.h"
#include "pl/player.h"
#include "sc/types.h"
#include "ty/toy.h"
#include "ty/tylist.h"

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
#include <baselib/lobj.h>

/* 4D6FE0 */ static SceneDesc* un_804D6FE0;
/* 4D6FE4 */ static SceneDesc* un_804D6FE4;
/* 4D6FE8 */ static HSD_Archive* un_804D6FE8;
/* 4D6FEC */ static HSD_Joint* un_804D6FEC;
/* 4D6FF0 */ static HSD_JObj* un_804D6FF0;
/* 4D6FF4 */ static GXColor un_804D6FF4;
/* 4D6FF8 */ static s32 un_804D6FF8;
/* 4D6FFC */ static u8 un_804D6FFC;
/* 4D6FFD */ static u8 un_804D6FFD;
/* 4D7000 */ static void* un_804D7000;
static un_804D7004_t un_804D7004;

Vec3 player_spawn = { 0.0f, 0.0f, 0.0f };

void un_8031F980(int arg0, int arg1)
{
    M2C_FIELD(&un_804D7004, u8*, 0) = arg0;
    M2C_FIELD(&un_804D7004, u8*, 1) = arg1;
}

void un_8031F990(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_8031F9B4(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_8031F9D8(CharacterKind char_index, int costume_id)
{
    PAD_STACK(16);

    ftDemo_ObjAllocInit();
    Player_InitAllPlayers();
    Player_80036E20(char_index, un_804D6FE8, 0);
    Player_SetPlayerCharacter(0, char_index);
    Player_SetCostumeId(0, costume_id);
    Player_SetPlayerId(0, 0);
    Player_SetSlottype(0, 2);
    Player_SetFacingDirection(0, 0.0f);
    Player_80032768(0, &player_spawn);
    Player_80036F34(0, 1);
    un_804D7000 = Player_GetEntity(0);
    lbAudioAx_80026F2C(0x18);
    lbAudioAx_8002702C(0x8, (u64) 0x20 << 48);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

void fn_8031FAA8(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    Vec3 pos;
    f32 scale_x;
    f32 scale_y;
    HSD_JObj* child;
    PAD_STACK(4);

    HSD_JObjAnimAll(gobj->hsd_obj);
    jobj = gobj->hsd_obj;
    if (mn_8022F298(jobj) != 120.0f) {
        return;
    }
    lb_80011E24(jobj, &child, 1, -1);
    jobj = child;
    HSD_JObjGetTranslation2(jobj, &pos);
    scale_x = 0.0f;
    scale_y = 1.0f;

    efSync_Spawn(0x42B, gobj, &pos, &scale_x, &scale_y, 0x00FFFFFF,
                 0x00808080);
    lbAudioAx_800237A8(0x61, 0x7F, 0x40);
}
void fn_8031FB90(HSD_GObj* gobj)
{
    GXColor* colors;
    char pad[8];
    if (un_804D7000 != NULL) {
        lbShadow_8000F38C(0);
    }
    if (HSD_CObjSetCurrent(GET_COBJ(gobj)) != 0) {
        colors = (GXColor*) &un_804D6FF4;
        HSD_SetEraseColor(colors->r, colors->g, colors->b, colors->a);
        HSD_CObjEraseScreen(GET_COBJ(gobj), 1, 0, 1);
        vi_8031CA04(gobj);
        gobj->gxlink_prios = 0x881;
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

void fn_8031FC30(HSD_GObj* gobj)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    HSD_CObjAnim(cobj);
    if (cobj->aobj->curr_frame == 1.0F) {
        vi_8031C9B4(0xD, 0);
    }
    if (cobj->aobj->curr_frame == 30.0F) {
        un_8031F9D8(un_804D6FFC, un_804D6FFD);
    }
    if (cobj->aobj->curr_frame == cobj->aobj->end_frame) {
        lb_800145F4();
        gm_801A4B60();
    }
}

void fn_8031FCBC(HSD_GObj* gobj)
{
    if ((f32) un_804D6FF8 >= 30.0F) {
        HSD_GObjPLink_80390228(gobj);
    } else {
        un_804D6FF8 = un_804D6FF8 + 1;
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

void un_8031FD18_OnEnter(void* arg)
{
    u8* input = arg;
    s32 i = 0;
    u8 char_index;
    HSD_CObj* cobj;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    HSD_JObj* child;
    HSD_Fog* fog;
    HSD_LObj* lobj;
    f32 scale;
    char pad[24];

    un_804D6FFC = input[0];
    un_804D6FFD = input[1];
    un_804D7000 = (void*) i;

    lbAudioAx_800236DC();
    efLib_8005B4B8();
    efAsync_8006737C(0);
    lbAudioAx_80023F28(0x59);
    lbAudioAx_80024E50(1);

    char_index = input[0];

    un_804D6FE8 = lbArchive_LoadSymbols("Vi1201v1.dat", &un_804D6FE0,
                                        "visual1201v1Scene", NULL);
    lbArchive_LoadSymbols("TyKoopa.dat", &un_804D6FEC,
                          "ToyKoopaModel_TopN_joint", NULL);
    lbArchive_LoadSymbols("GmRgStnd.dat", &un_804D6FE4, "standScene", NULL);
    un_803124BC();
    un_804D6FE8 = lbArchive_LoadSymbols(gm_80160438(char_index), NULL);

    gobj = GObj_Create(0x13, 0x14, 0);
    cobj =
        lb_80013B14((HSD_CameraDescPerspective*) un_804D6FE0->cameras->desc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, (void (*)(HSD_GObj*, int)) fn_8031FB90, 8);
    HSD_CObjAddAnim(cobj, un_804D6FE0->cameras->anims[0]);
    HSD_CObjReqAnim(cobj, 0.0f);
    HSD_CObjAnim(cobj);
    HSD_GObjProc_8038FD54(gobj, fn_8031FC30, 0);

    for (; un_804D6FE0->models[i] != NULL; i++) {
        gobj = GObj_Create(0xE, 0xF, 0);
        jobj = HSD_JObjLoadJoint(un_804D6FE0->models[i]->joint);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
        gm_8016895C(jobj, un_804D6FE0->models[i], 0);
        HSD_JObjReqAnimAll(jobj, 0.0f);
        HSD_JObjAnimAll(jobj);
        HSD_GObjProc_8038FD54(gobj, fn_8031FAA8, 0);
        lb_80011E24(jobj, &un_804D6FF0, 3, -1);
    }

    Camera_80028B9C(6);
    lb_8000FCDC();
    mpColl_80041C78();
    Ground_801C0378(0x40);
    Stage_802251E8(0x20, 0);
    Item_80266FA8();
    Item_80266FCC();
    Stage_8022524C();
    Stage_8022532C(0x20, 0x19);

    gobj = GObj_Create(0xE, 0xF, 0);
    jobj = HSD_JObjLoadJoint(un_804D6FEC);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);

    HSD_JObjSetScaleX(jobj, 0.55f);
    HSD_JObjSetScaleY(jobj, 0.55f);
    HSD_JObjSetScaleZ(jobj, 0.55f);

    lb_8000C1C0(jobj, un_804D6FF0);
    lb_8000C290(jobj, un_804D6FF0);
    HSD_GObjProc_8038FD54(gobj, un_8031F9B4, 0);

    gobj = GObj_Create(0xE, 0xF, 0);
    jobj = HSD_JObjLoadJoint(un_804D6FE4->models[0]->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    HSD_GObjProc_8038FD54(gobj, un_8031F990, 0);

    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }

    HSD_JObjSetTranslateX_2(child, -un_803060BC(0x1E, 0));
    HSD_JObjSetTranslateY_2(child, -un_803060BC(0x1E, 1));
    HSD_JObjSetTranslateZ_2(child, -un_803060BC(0x1E, 2));
    HSD_JObjSetRotationY_2(child, -un_803060BC(0x1E, 5));

    scale = 0.55f * (un_803060BC(0x1E, 4) * (1.0f / un_803060BC(0x1E, 3)));

    HSD_JObjSetScaleX_2(child, scale);
    HSD_JObjSetScaleY_2(child, scale);
    HSD_JObjSetScaleZ_2(child, scale);

    lb_8000C1C0(jobj, un_804D6FF0);
    lb_8000C290(jobj, un_804D6FF0);

    gobj = GObj_Create(0xB, 3, 0);
    fog = HSD_FogLoadDesc(un_804D6FE0->fogs->desc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7848, fog);
    GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 0, 0);
    HSD_GObjProc_8038FD54(gobj, fn_8031FCBC, 0);
    un_804D6FF4 = fog->color;
    un_804D6FF8 = 0;

    gobj = GObj_Create(0xB, 3, 0);
    lobj = lb_80011AC4(un_804D6FE0->lights);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0);

    lbAudioAx_80024E50(0);
}

void un_80320490_OnFrame(void)
{
    vi_8031CAAC();
}
