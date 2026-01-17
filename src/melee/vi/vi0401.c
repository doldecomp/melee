#include "vi0401.h"

#include <placeholder.h>

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ft/ftdemo.h"
#include "gm/gm_17C0.h"
#include "gm/gm_1A36.h"
#include "gm/gm_1A45.h"
#include "gm/gm_unsplit.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "it/item.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "mp/mpcoll.h"
#include "pl/player.h"
#include "sc/types.h"
#include "vi/types.h"
#include "vi/vi.h"

#include <baselib/aobj.h>
#include <baselib/cobj.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/lobj.h>

static SceneDesc* un_804D6F48;
static SceneDesc* un_804D6F4C;
static SceneDesc* un_804D6F50;
static HSD_Archive* un_804D6F54;
static HSD_JObj* un_804D6F58;
static GXColor erase_colors_vi0401;
static ViCharaDesc un_804D6F60;

void vi0401_8031D020(int arg0, int arg1)
{
    un_804D6F60.p1_char_index = arg0;
    un_804D6F60.p1_costume_index = arg1;
}

void un_8031D030(CharacterKind char_kind, int costume)
{
    Vec3 pos;

    Camera_80028B9C(6);
    lb_8000FCDC();
    mpColl_80041C78();
    Ground_801C0378(0x40);
    Stage_802251E8(6, 0);
    Item_80266FA8();
    Item_80266FCC();
    Stage_8022524C();
    Stage_8022532C(6, 0);

    ftDemo_ObjAllocInit();
    Player_InitAllPlayers();

    Player_80036E20(char_kind, un_804D6F54, 3);
    Player_SetPlayerCharacter(0, char_kind);
    Player_SetCostumeId(0, costume);
    Player_SetPlayerId(0, 0);
    Player_SetSlottype(0, Gm_PKind_Demo);
    Player_SetFacingDirection(0, 1.0f);

    HSD_JObjGetTranslation2(un_804D6F58, &pos);
    Player_80032768(0, &pos);
    Player_80036F34(0, 8);

    lbAudioAx_80026F2C(0x18);
    lbAudioAx_8002702C(8, (u64) 0x100 << 32);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
    lbAudioAx_80024634(0x88);
}

static void vi0401_8031D18C(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

static void vi0401_8031D1B0(HSD_GObj* gobj, int unused)
{
    HSD_CObj* cobj;

    cobj = GET_COBJ(gobj);
    if (HSD_CObjSetCurrent(cobj)) {
        HSD_SetEraseColor(erase_colors_vi0401.r, erase_colors_vi0401.g,
                          erase_colors_vi0401.b, erase_colors_vi0401.a);
        cobj = GET_COBJ(gobj);
        HSD_CObjEraseScreen(cobj, 1, 0, 1);
        vi_8031CA04(gobj);
        gobj->gxlink_prios = 0x281;
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

static void vi0401_8031D23C(HSD_GObj* gobj)
{
    HSD_AObj* aobj;
    HSD_CObj* cobj = GET_COBJ(gobj);

    HSD_CObjAnim(cobj);
    aobj = cobj->aobj;
    if (aobj->curr_frame == aobj->end_frame) {
        lb_800145F4();
        gm_801A4B60();
    }
}

static void fn_8031D168(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_8031D288_OnEnter(void* data)
{
    int i;
    HSD_CObj* cobj;
    HSD_GObj* cam_gobj;
    HSD_GObj* fog_gobj;
    HSD_Fog* fog;
    HSD_GObj* light_gobj;
    HSD_LObj* lobj;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    HSD_JObj* child;

    ViCharaDesc* desc = (ViCharaDesc*) data;
    u8 char_index = desc->p1_char_index;

    lbAudioAx_800236DC();
    efLib_8005B4B8();
    efAsync_8006737C(0);

    lbArchive_LoadSymbols("Vi0401.dat", &un_804D6F48, "visual0401Scene",
                          &un_804D6F4C, "visual0401InfoScene", 0);
    lbArchive_LoadSymbols("IfAll.dat", &un_804D6F50, "ScInfDmg_scene_data",
                          NULL);
    un_804D6F54 = lbArchive_LoadSymbols(viGetCharAnimByIndex(char_index), 0);

    fog_gobj = GObj_Create(0xB, 3, 0);
    fog = HSD_FogLoadDesc(un_804D6F48->fogs->desc);
    HSD_GObjObject_80390A70(fog_gobj, HSD_GObj_804D7848, fog);
    GObj_SetupGXLink(fog_gobj, HSD_GObj_FogCallback, 0, 0);
    erase_colors_vi0401 = fog->color;

    light_gobj = GObj_Create(0xB, 3, 0);
    lobj = lb_80011AC4(un_804D6F48->lights);
    HSD_GObjObject_80390A70(light_gobj, HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(light_gobj, HSD_GObj_LObjCallback, 0, 0);

    cam_gobj = GObj_Create(0x13, 0x14, 0);
    cobj =
        lb_80013B14((HSD_CameraDescPerspective*) un_804D6F48->cameras->desc);
    HSD_GObjObject_80390A70(cam_gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(cam_gobj, vi0401_8031D1B0, 0x5);
    cam_gobj->gxlink_prios = 0x2A9;
    HSD_CObjAddAnim(cobj, un_804D6F48->cameras->anims[0]);
    HSD_CObjReqAnim(cobj, 0.0f);
    HSD_CObjAnim(cobj);
    HSD_GObjProc_8038FD54(cam_gobj, vi0401_8031D23C, 0);

    for (i = 0; un_804D6F48->models[i] != NULL; i++) {
        gobj = GObj_Create(0xE, 0xF, 0);
        jobj = HSD_JObjLoadJoint(un_804D6F48->models[i]->joint);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 9, 0);
        gm_8016895C(jobj, un_804D6F48->models[i], 0);
        HSD_JObjReqAnimAll(jobj, 0.0f);
        HSD_JObjAnimAll(jobj);
        HSD_GObjProc_8038FD54(gobj, vi0401_8031D18C, 0x17);
        if (i == 0) {
            lb_80011E24(jobj, (HSD_JObj**) &un_804D6F58, 1, -1);
        }
    }

    cam_gobj = GObj_Create(0x13, 0x14, 0);
    cobj =
        lb_80013B14((HSD_CameraDescPerspective*) un_804D6F50->cameras->desc);
    HSD_GObjObject_80390A70(cam_gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(cam_gobj, HSD_GObj_803910D8, 0x8);
    gobj->gxlink_prios = 0x801;

    for (i = 0; un_804D6F4C->models[i] != NULL; i++) {
        gobj = GObj_Create(0xE, 0xF, 0);
        jobj = HSD_JObjLoadJoint(un_804D6F4C->models[i]->joint);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 9, 0);
        gm_8016895C(jobj, un_804D6F4C->models[i], 0);
        HSD_JObjReqAnimAll(jobj, 0.0f);
        HSD_JObjAnimAll(jobj);
        HSD_GObjProc_8038FD54(gobj, fn_8031D168, 0x17);
    }
    un_8031D030(desc->p1_char_index, desc->p1_costume_index);
    vi_8031C9B4(1, 0);

    lbAudioAx_800237A8(0x61a88, 0x7F, 0x40);
    lbAudioAx_800237A8(0x61a89, 0x7F, 0x40);
    lbAudioAx_800237A8(0x61a8a, 0x7F, 0x40);
}

void un_8031D698_OnFrame(void)
{
    u64 result = gm_801A36A0(gm_8017E430());
    if ((result & 0x1000) != 0) {
        lb_800145F4();
        gm_801A4B60();
    }
}
