#include "vi.h"

#include "vi/vi1201v1.static.h"

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

// .data section 0x80400258 - 0x80400xxx
typedef struct Vi1201SceneData {
    /* 0x00 */ Vec3 player_spawn;
    /* 0x0C */ char pad_0C[0x28];
    /* 0x34 */ char* scene1_file;
    /* 0x38 */ char pad_38[0x0C];
    /* 0x44 */ char* scene1_symbol;
    /* 0x48 */ char pad_48[0x10];
    /* 0x58 */ char* scene2_file;
    /* 0x5C */ char pad_5C[0x08];
    /* 0x64 */ char* scene2_symbol;
    /* 0x68 */ char pad_68[0x18];
    /* 0x80 */ char* scene3_file;
    /* 0x84 */ char pad_84[0x0C];
    /* 0x90 */ char* scene3_symbol;
    /* 0x94 */ char pad_94[0x6C];
} Vi1201SceneData; /* size = 0x100 */

Vi1201SceneData un_80400258;

static f32 un_804DE0F8;
static f32 un_804DE0FC;
static f32 un_804DE100;
static f32 un_804DE104;

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
    char pad[16];

    ftDemo_ObjAllocInit();
    Player_InitAllPlayers();
    Player_80036E20(char_index, un_804D6FE8, 0);
    Player_SetPlayerCharacter(0, char_index);
    Player_SetCostumeId(0, costume_id);
    Player_SetPlayerId(0, 0);
    Player_SetSlottype(0, 2);
    Player_SetFacingDirection(0, un_804DE100);
    Player_80032768(0, &un_80400258.player_spawn);
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
    char pad[4];

    HSD_JObjAnimAll(gobj->hsd_obj);
    jobj = gobj->hsd_obj;
    if (mn_8022F298(jobj) != un_804DE104) {
        return;
    }
    lb_80011E24(jobj, &child, 1, -1);
    jobj = child;
    HSD_ASSERT(0x3D3, jobj);

    pos = jobj->translate;
    scale_x = un_804DE100;
    scale_y = un_804DE0FC;

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

    un_804D6FE8 = lbArchive_LoadSymbols(un_80400258.scene1_file, &un_804D6FE0,
                                        un_80400258.scene1_symbol, NULL);
    lbArchive_LoadSymbols(un_80400258.scene2_file, &un_804D6FEC,
                          un_80400258.scene2_symbol, NULL);
    lbArchive_LoadSymbols(un_80400258.scene3_file, &un_804D6FE4,
                          un_80400258.scene3_symbol, NULL);
    un_803124BC();
    un_804D6FE8 = lbArchive_LoadSymbols(gm_80160438(char_index), NULL);

    gobj = GObj_Create(0x13, 0x14, 0);
    cobj =
        lb_80013B14((HSD_CameraDescPerspective*) un_804D6FE0->cameras->desc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, (void (*)(HSD_GObj*, int)) fn_8031FB90, 8);
    HSD_CObjAddAnim(cobj, un_804D6FE0->cameras->anims[0]);
    HSD_CObjReqAnim(cobj, un_804DE100);
    HSD_CObjAnim(cobj);
    HSD_GObjProc_8038FD54(gobj, fn_8031FC30, 0);

    for (i = 0; un_804D6FE0->models[i] != NULL; i++) {
        gobj = GObj_Create(0xE, 0xF, 0);
        jobj = HSD_JObjLoadJoint(un_804D6FE0->models[i]->joint);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
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

    gobj = GObj_Create(0xE, 0xF, 0);
    jobj = HSD_JObjLoadJoint(un_804D6FEC);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);

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

    gobj = GObj_Create(0xE, 0xF, 0);
    jobj = HSD_JObjLoadJoint(un_804D6FE4->models[0]->joint->child->child);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    HSD_GObjProc_8038FD54(gobj, un_8031F990, 0);

    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }

    scale = -un_803060BC(0x1E, 0);
    HSD_ASSERT(0x3A4, child != NULL);
    child->translate.x = scale;
    if (!(child->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(child);
    }

    scale = -un_803060BC(0x1E, 1);
    HSD_ASSERT(0x3B3, child != NULL);
    child->translate.y = scale;
    if (!(child->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(child);
    }

    scale = -un_803060BC(0x1E, 2);
    HSD_ASSERT(0x3C2, child != NULL);
    child->translate.z = scale;
    if (!(child->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(child);
    }

    scale = -un_803060BC(0x1E, 5);
    HSD_ASSERT(0x294, child != NULL);
    HSD_ASSERT(0x295, !(child->flags & JOBJ_USE_QUATERNION));
    child->rotate.x = scale;
    if (!(child->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(child);
    }

    scale = un_804DE0FC / un_803060BC(0x1E, 3);
    scale = un_804DE0F8 * (un_803060BC(0x1E, 4) * scale);

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

    gobj = GObj_Create(0xB, 3, 0);
    fog = HSD_FogLoadDesc(un_804D6FE0->fogs->desc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7848, fog);
    GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 0, 0);
    HSD_GObjProc_8038FD54(gobj, fn_8031FCBC, 0);
    un_804D6FF4 = *(u32*) &fog->color;
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

void un_803204B0(int arg0, int arg1)
{
    M2C_FIELD(&un_804D7038, u8*, 0) = arg0;
    M2C_FIELD(&un_804D7038, u8*, 1) = arg1;
}
