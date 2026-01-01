#include "vi/vi1201v1.static.h"

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

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ft/ft_0C31.h"
#include "ft/ftdemo.h"
#include "pl/player.h"
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
#include "mp/mpcoll.h"
#include "sc/types.h"
#include "ty/toy.h"
#include "ty/tylist.h"
#include "vi.h"

// .data section 0x80400258 - 0x80400xxx
char un_80400258[0x100];

extern SceneDesc* un_804D6FE0;
extern SceneDesc* un_804D6FE4;
extern HSD_Archive* un_804D6FE8;
extern HSD_Joint* un_804D6FEC;
extern void* un_804D6FF0;
extern u32 un_804D6FF4;
extern s32 un_804D6FF8;
extern u8 un_804D6FFC;
extern u8 un_804D6FFD;
extern void* un_804D7000;

static f32 un_804DE0F8;
static f32 un_804DE0FC;
static f32 un_804DE100;

void un_8031F990(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_8031F9B4(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_8031F9D8(u8 char_index, u8 costume_id)
{
    ftDemo_ObjAllocInit();
    Player_InitAllPlayers();
    Player_80036E20(char_index, un_804D6FE8, 0);
    Player_SetPlayerCharacter(0, char_index);
    Player_SetCostumeId(0, costume_id);
    Player_SetPlayerId(0, 0);
    Player_SetSlottype(0, 2);
    Player_SetFacingDirection(0, un_804DE100);
    Player_80032768(0, (Vec3*)un_80400258);
    Player_80036F34(0, 1);
    un_804D7000 = Player_GetEntity(0);
    lbAudioAx_80026F2C(0x18);
    lbAudioAx_8002702C(0x8, (u64)0x20 << 32);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

/// #fn_8031FAA8

void fn_8031FB90(HSD_GObj* gobj, int unused)
{
    u8* colors;
    char pad[8];
    if (un_804D7000 != NULL) {
        lbShadow_8000F38C(0);
    }
    if (HSD_CObjSetCurrent(GET_COBJ(gobj)) != 0) {
        colors = (u8*)&un_804D6FF4;
        HSD_SetEraseColor(colors[0], colors[1], colors[2], colors[3]);
        HSD_CObjEraseScreen(GET_COBJ(gobj), 1, 0, 1);
        vi_8031CA04(gobj);
        gobj->gxlink_prios = 0x881;
        *(s32*)((char*)gobj + 0x20) = 0;
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

void fn_8031FC30(HSD_GObj* gobj)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    HSD_CObjAnim(cobj);
    if (cobj->aobj->curr_frame == 1.0F) {
        vi_8031C9B4(0xd, 0);
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
    if ((f32)un_804D6FF8 >= 30.0F) {
        HSD_GObjPLink_80390228(gobj);
    } else {
        un_804D6FF8 = un_804D6FF8 + 1;
    }
}

void un_8031FD18_OnEnter(void* arg)
{
    u8* input = arg;
    s32 i = 0;
    u8 char_index;
    HSD_CObj* cobj;
    HSD_GObj* gobj;
    char* str_table;
    HSD_JObj* jobj;
    HSD_JObj* child;
    HSD_Fog* fog;
    HSD_LObj* lobj;
    f32 scale;

    un_804D6FFC = input[0];
    str_table = un_80400258;
    un_804D6FFD = input[1];
    un_804D7000 = (void*)i;

    lbAudioAx_800236DC();
    efLib_8005B4B8();
    efAsync_8006737C(0);
    lbAudioAx_80023F28(0x59);
    lbAudioAx_80024E50(1);

    char_index = input[0];

    un_804D6FE8 = lbArchive_LoadSymbols(str_table + 0x34, &un_804D6FE0,
                                        str_table + 0x44, NULL);
    lbArchive_LoadSymbols(str_table + 0x58, &un_804D6FEC,
                          str_table + 0x64, NULL);
    lbArchive_LoadSymbols(str_table + 0x80, &un_804D6FE4,
                          str_table + 0x90, NULL);
    un_803124BC();
    un_804D6FE8 = lbArchive_LoadSymbols(gm_80160438(char_index), NULL);

    gobj = GObj_Create(0x13, 0x14, 0);
    cobj = lb_80013B14((HSD_CameraDescPerspective*)un_804D6FE0->cameras->desc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, (void (*)(HSD_GObj*, int))fn_8031FB90, 8);
    HSD_CObjAddAnim(cobj, un_804D6FE0->cameras->anims[0]);
    HSD_CObjReqAnim(cobj, un_804DE100);
    HSD_CObjAnim(cobj);
    HSD_GObjProc_8038FD54(gobj, fn_8031FC30, 0);

    for (i = 0; un_804D6FE0->models[i] != NULL; i++) {
        gobj = GObj_Create(0xe, 0xf, 0);
        jobj = HSD_JObjLoadJoint(un_804D6FE0->models[i]->joint);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xb, 0);
        gm_8016895C(jobj, un_804D6FE0->models[i], 0);
        HSD_JObjReqAnimAll(jobj, un_804DE100);
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

    gobj = GObj_Create(0xe, 0xf, 0);
    jobj = HSD_JObjLoadJoint(un_804D6FEC);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xb, 0);

    HSD_ASSERT(0x308, jobj != NULL);
    jobj->scale.x = un_804DE0F8;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirtySub(jobj);
    }

    HSD_ASSERT(0x317, jobj != NULL);
    jobj->scale.y = un_804DE0F8;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirtySub(jobj);
    }

    HSD_ASSERT(0x326, jobj != NULL);
    jobj->scale.z = un_804DE0F8;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirtySub(jobj);
    }

    lb_8000C1C0(jobj, un_804D6FF0);
    lb_8000C290(jobj, un_804D6FF0);
    HSD_GObjProc_8038FD54(gobj, un_8031F9B4, 0);

    gobj = GObj_Create(0xe, 0xf, 0);
    jobj = HSD_JObjLoadJoint(un_804D6FE4->models[0]->joint->child->child);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xb, 0);
    HSD_GObjProc_8038FD54(gobj, un_8031F990, 0);

    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }

    scale = -un_803060BC(0x1e, 0);
    HSD_ASSERT(0x3a4, child != NULL);
    child->translate.x = scale;
    if (!(child->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(child);
    }

    scale = -un_803060BC(0x1e, 1);
    HSD_ASSERT(0x3b3, child != NULL);
    child->translate.y = scale;
    if (!(child->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(child);
    }

    scale = -un_803060BC(0x1e, 2);
    HSD_ASSERT(0x3c2, child != NULL);
    child->translate.z = scale;
    if (!(child->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(child);
    }

    scale = -un_803060BC(0x1e, 5);
    HSD_ASSERT(0x294, child != NULL);
    HSD_ASSERT(0x295, !(child->flags & JOBJ_USE_QUATERNION));
    child->rotate.x = scale;
    if (!(child->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(child);
    }

    scale = un_804DE0FC / un_803060BC(0x1e, 3);
    scale = un_804DE0F8 * (un_803060BC(0x1e, 4) * scale);

    HSD_ASSERT(0x308, child != NULL);
    child->scale.x = scale;
    if (!(child->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(child);
    }

    HSD_ASSERT(0x317, child != NULL);
    child->scale.y = scale;
    if (!(child->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(child);
    }

    HSD_ASSERT(0x326, child != NULL);
    child->scale.z = scale;
    if (!(child->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(child);
    }

    lb_8000C1C0(jobj, un_804D6FF0);
    lb_8000C290(jobj, un_804D6FF0);

    gobj = GObj_Create(0xb, 3, 0);
    fog = HSD_FogLoadDesc(un_804D6FE0->fogs->desc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7848, fog);
    GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 0, 0);
    HSD_GObjProc_8038FD54(gobj, fn_8031FCBC, 0);
    un_804D6FF4 = *(u32*)&fog->color;
    un_804D6FF8 = 0;

    gobj = GObj_Create(0xb, 3, 0);
    lobj = lb_80011AC4(un_804D6FE0->lights);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0);

    lbAudioAx_80024E50(0);
}

void un_80320490_OnFrame(void)
{
    vi_8031CAAC();
}

void un_803204B0(int arg0, int arg1)
{
    M2C_FIELD(&un_804D7038, u8*, 0) = arg0;
    M2C_FIELD(&un_804D7038, u8*, 1) = arg1;
}
