#include "gm_1879.h"

#include "gm_unsplit.h"

#include "cm/camera.h"
#include "dolphin/pad.h"
#include "ef/efasync.h"
#include "ef/eflib.h"
#include "gm/gm_1A36.h"
#include "gm/gm_1A3F.h"
#include "gm/gm_1A45.h"
#include "gm/types.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbbgflash.h"
#include "lb/lbspdisplay.h"
#include "mn/inlines.h"
#include "mp/mpcoll.h"
#include "pl/player.h"
#include "sc/types.h"

#include <baselib/aobj.h>
#include <baselib/cobj.h>
#include <baselib/dobj.h>
#include <baselib/fog.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/mobj.h>
#include <baselib/state.h>
#include <baselib/tobj.h>
#include <baselib/wobj.h>
typedef struct gm_1832_StageState {
    u8 stage_index : 5;
    u8 done : 1;
    u8 flash : 1;
    u8 active : 1;
} gm_1832_StageState;

static struct gm_1832_804736C0_t {
    SceneDesc* x0;
    struct SceneCameraDesc* x4;
    HSD_GObj* x8;
    u8 pad_C[0x28];
    u16 x34;
    gm_1832_StageState x36;
    struct {
        u8 frame_counter : 4;
        u8 anim_state : 2;
        u8 state2 : 2;
    } x37;
    u8 x38;
    u8 pad_39[7];
} lbl_804736C0;
ASSERT_SIZE(struct gm_1832_804736C0_t, 0x40);
typedef struct gm_1832_804736C0_t gm_1832_804736C0_t;

static inline void fn_80187AB4_LoadAnim(HSD_JObj* jobj,
                                        gm_1832_804736C0_t* data)
{
    DynamicModelDesc* desc = data->x0->models[11 - data->x36.stage_index];
    int anim_state;

    if (desc->anims != NULL) {
        anim_state = data->x37.anim_state;
        if (desc->anims[anim_state] != NULL) {
            lb_8000C0E8(jobj, anim_state, desc);
            HSD_JObjReqAnimAll(jobj, 0.0f);
            HSD_JObjAnimAll(jobj);
        }
    }
}

void fn_80187910(HSD_GObj* arg0)
{
    Vec3 sp10;
    gm_1832_804736C0_t* data;
    HSD_CObj* cobj;
    s32 frame;
    f32 scale;

    PAD_STACK(4);
    (void) 0.0f;
    data = &lbl_804736C0;
    cobj = arg0->hsd_obj;
    if (gm_GetButtonsTriggered(data->x38) & PAD_BUTTON_A) {
        data->x37.frame_counter = (s32) cobj->eyepos->aobj->curr_frame / 300;
        if (++data->x37.frame_counter >= 8U) {
            data->x37.frame_counter = 0;
        }
        frame = data->x37.frame_counter * 0x12C;
        HSD_CObjRemoveAnim(cobj);
        HSD_CObjAddAnim(cobj, *data->x4->anims);
        HSD_CObjReqAnim(cobj, (f32) frame);
    }
    HSD_CObjAnim(cobj);
    HSD_CObjGetInterest(cobj, &sp10);
    scale = Ground_801C0498();
    sp10.x *= scale;
    sp10.y *= scale;
    sp10.z *= scale;
    HSD_CObjSetInterest(cobj, &sp10);
    HSD_CObjGetEyePosition(cobj, &sp10);
    scale = Ground_801C0498();
    sp10.x *= scale;
    sp10.y *= scale;
    sp10.z *= scale;
    HSD_CObjSetEyePosition(cobj, &sp10);
}

typedef struct {
    u8 pad_hi : 4;
    u8 state : 2;
    u8 pad_lo : 2;
} x37_state_bits;

void fn_80187AB4(HSD_GObj* gobj)
{
    gm_1832_804736C0_t* data = &lbl_804736C0;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    int state = data->x37.anim_state;
    PAD_STACK(16);

    switch (state) {
    case 0:
        if (lb_8000B09C(jobj) == 0) {
            data->x37.anim_state = 1;
            fn_80187AB4_LoadAnim(jobj, data);
            data->x34 = 0x960;
        }
        break;
    case 1:
        if ((u32) data->x36.active == 1U) {
            data->x36.flash = 1;
        }
        if (data->x36.flash) {
            data->x37.anim_state = 2;
            data->x36.done = 1;
            lbBgFlash_8002063C(1);
        }
        if (lb_8000B09C(jobj) == 0) {
            fn_80187AB4_LoadAnim(jobj, data);
        }
        break;
    case 2:
        if (lb_8000B09C(jobj) == 0) {
            data->x36.done = 1;
            HSD_GObjPLink_80390228(gobj);
        }
        break;
    }
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void fn_80187C9C(HSD_GObj* gobj, int arg1)
{
    GXSetZMode(0, GX_NEVER, 0);
    HSD_GObj_JObjCallback(gobj, arg1);
    HSD_StateInvalidate(0x40);
}

void fn_80187CF4(HSD_GObj* gobj)
{
    gm_1832_804736C0_t* data = &lbl_804736C0;
    HSD_JObj* jobj = gobj->hsd_obj;
    int state = data->x37.state2;
    DynamicModelDesc* desc;
    int anim_state;

    switch (state) {
    case 0:
        if (lb_8000B09C(jobj) == 0) {
            data->x37.state2 = 1;
            anim_state = data->x37.state2;
            desc = data->x0->models[12];
            if (desc->anims[anim_state] != NULL) {
                lb_8000C0E8(jobj, anim_state, desc);
                HSD_JObjReqAnimAll(jobj, 0.0f);
                HSD_JObjAnimAll(jobj);
            }
        }
        break;
    case 1:
        if (lb_8000B09C(jobj) == 0) {
            data->x37.state2 = 2;
            anim_state = data->x37.state2;
            desc = data->x0->models[12];
            if (desc->anims[anim_state] != NULL) {
                lb_8000C0E8(jobj, anim_state, desc);
                HSD_JObjReqAnimAll(jobj, 0.0f);
                HSD_JObjAnimAll(jobj);
            }
        }
        break;
    case 2:
        if (gm_GetButtonsTriggered(data->x38) & PAD_BUTTON_START) {
            sfxForward();
            data->x36.active = 1;
            data->x37.state2 = 3;
            anim_state = data->x37.state2;
            desc = data->x0->models[12];
            if (desc->anims[anim_state] != NULL) {
                lb_8000C0E8(jobj, anim_state, desc);
                HSD_JObjReqAnimAll(jobj, 0.0f);
                HSD_JObjAnimAll(jobj);
            }
        } else if (lb_8000B09C(jobj) == 0) {
            anim_state = data->x37.state2;
            desc = data->x0->models[12];
            if (desc->anims[anim_state] != NULL) {
                lb_8000C0E8(jobj, anim_state, desc);
                HSD_JObjReqAnimAll(jobj, 0.0f);
                HSD_JObjAnimAll(jobj);
            }
        }
        break;
    case 3:
        if (lb_8000B09C(jobj) == 0) {
            HSD_GObjPLink_80390228(gobj);
        }
        break;
    }
    HSD_JObjAnimAll(gobj->hsd_obj);
}

static char* gm_1832_NormalArchiveNames[12] = {
    "mc01", "mc02", "mc03", "mc04", "mc05", "mc06",
    "mc07", "mc08", "mc09", "mc10", "mc11", "mc12",
};

static s32 gm_1832_NormalBgmIds[12] = { 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C,
                                        0x1C, 0x1C, 0x1C, 0x14, 0x14, 0x1C };

static u64 gm_1832_NormalAudioMasks[12] = {
    0x0002000010000000, 0x0000002000000100, 0x0002000000010000,
    0x0000010004000000, 0x0000080200004000, 0x0000000800000C00,
    0x0001000001000000, 0x0002000000000040, 0x0000008000200000,
    0x0000000000002000, 0x0000000000060000, 0x0020000000009000,
};

static char gm_1832_NormalSceneDataName[] = "ScItrNormal_scene_data";

static HSD_Archive* lbl_804D6620;

typedef struct gm_80187F48_EnterData {
    u8 x0;
    u8 stage_index;
    u16 stkind;
} gm_80187F48_EnterData;

static inline StKind gm_GetStKind(gm_80187F48_EnterData* data)
{
    return data->stkind;
}

static inline u64 gm_80187F48_GetAudioConfig(u8 stage_index)
{
    return lbAudioAx_80026E84(Player_GetPlayerCharacter(0)) |
           gm_1832_NormalAudioMasks[stage_index];
}

static inline void gm_80187F48_OnEnter_inline(gm_80187F48_EnterData* arg0)
{
    gm_1832_804736C0_t* data;
    HSD_GObj* gobj;
    HSD_CObj* cobj;
    u8 stage_index;

    data = &lbl_804736C0;
    data->x38 = arg0->x0;
    lb_8000FCDC();
    mpColl_80041C78();
    Ground_801C0378(0x40);
    Stage_802251E8(gm_GetStKind(arg0), NULL);
    Item_80266F70();
    Item_80266FCC();
    efLib_Init();
    efAsync_LoadSync(0);
    efAsync_LoadSync(0x1F);
    Stage_8022524C();
    Player_InitAllPlayers();
    lbBgFlash_800209F4();

    stage_index = arg0->stage_index;
    data->x37.anim_state = 0;
    data->x37.frame_counter = 0;
    data->x34 = 0;
    data->x36.done = 0;
    data->x36.flash = 0;
    data->x36.stage_index = stage_index;
    data->x37.state2 = 0;
    data->x36.active = 0;

    {
        u8 si = arg0->stage_index;
        lbl_804D6620 = lbArchive_80016DBC(
            "IrNml", &data->x0, gm_1832_NormalSceneDataName, &data->x4,
            gm_1832_NormalArchiveNames[si], NULL);

        lbAudioAx_80026F2C(gm_1832_NormalBgmIds[si]);
        lbAudioAx_8002702C(gm_1832_NormalBgmIds[si],
                           gm_80187F48_GetAudioConfig(si));
    }
    lbAudioAx_80027168();
    lbAudioAx_80027648();

    gobj = GObj_Create(0x13, 0x14, 0);
    data->x8 = gobj;
    cobj = HSD_CObjLoadDesc(data->x4->desc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_CameraKind, cobj);
    GObj_SetupGXLinkMax(gobj, (GObj_RenderFunc) (Event) Camera_800304E0, 8);
    HSD_GObj_SetupProc(gobj, fn_80187910, 0);
    HSD_CObjAddAnim(cobj, *data->x4->anims);
    HSD_CObjReqAnim(cobj, 0.0f);

    {
        HSD_GObj* scene_gobj = GObj_Create(0x13, 0x14, 0);
        HSD_CObj* scene_cobj = HSD_CObjLoadDesc(data->x0->cameras[0].desc);
        HSD_GObjObject_80390A70(scene_gobj, HSD_GObj_CameraKind, scene_cobj);
        GObj_SetupGXLinkMax(scene_gobj, HSD_GObj_803910D8, 8);
        scene_gobj->gxlink_prios = 0xC00;
    }

    {
        HSD_GObj* light_gobj = GObj_Create(0xB, 3, 0);
        HSD_LObj* lobj = lb_80011AC4(data->x0->lights);
        HSD_GObjObject_80390A70(light_gobj, HSD_GObj_LightKind, lobj);
        GObj_SetupGXLink(light_gobj, HSD_GObj_LObjCallback, 0xA, 0);
    }

    {
        HSD_JObj* model_jobj;
        HSD_GObj* model_gobj;
        gm_1832_StageState* state = &data->x36;
        DynamicModelDesc* model_desc;
        HSD_AnimJoint** anims;
        int model_stage;
        int model_anim_idx;

        model_gobj = GObj_Create(0xE, 0xF, 0);
        model_jobj = HSD_JObjLoadJoint(
            data->x0->models[11 - state->stage_index]->joint);
        lb_80011C18(model_jobj, 0x08000000);
        HSD_GObjObject_80390A70(model_gobj, HSD_GObj_JObjKind, model_jobj);
        GObj_SetupGXLink(model_gobj, fn_80187C9C, 0xB, 0xB);

        model_stage = state->stage_index;
        (void) model_stage;
        model_desc = data->x0->models[11 - model_stage];
        anims = model_desc->anims;
        if (anims != NULL) {
            model_anim_idx = data->x37.anim_state;
            if (anims[model_anim_idx] != NULL) {
                lb_8000C0E8(model_jobj, model_anim_idx, model_desc);
                HSD_JObjReqAnimAll(model_jobj, 0.0f);
                HSD_JObjAnimAll(model_jobj);
            }
        }
        HSD_GObj_SetupProc(model_gobj, fn_80187AB4, 0);
    }

    {
        HSD_GObj* model_gobj = GObj_Create(0xE, 0xF, 0);
        HSD_JObj* model_jobj = HSD_JObjLoadJoint(data->x0->models[12]->joint);
        int model_anim_idx;
        DynamicModelDesc* model_desc;
        lb_80011C18(model_jobj, 0x08000000);
        HSD_GObjObject_80390A70(model_gobj, HSD_GObj_JObjKind, model_jobj);
        GObj_SetupGXLink(model_gobj, fn_80187C9C, 0xB, 0xB);

        model_anim_idx = data->x37.state2;
        model_desc = data->x0->models[12];
        if (model_desc->anims[model_anim_idx] != NULL) {
            lb_8000C0E8(model_jobj, model_anim_idx, model_desc);
            HSD_JObjReqAnimAll(model_jobj, 0.0f);
            HSD_JObjAnimAll(model_jobj);
        }

        HSD_JObjReqAnimAll(model_jobj, 0.0f);
        HSD_JObjAnimAll(model_jobj);
        HSD_GObj_SetupProc(model_gobj, fn_80187CF4, 0);
    }
    lbAudioAx_80023F28(0x2E);
}

void gm_Scene_IntroNormal_OnEnter(void* arg0)
{
    PAD_STACK(32);
    gm_80187F48_OnEnter_inline(arg0);
}

void gm_Scene_IntroNormal_OnLeave(void* arg0)
{
    HSD_Archive** var = &lbl_804D6620;
    lbArchive_80016EFC(*var);
}

void gm_Scene_IntroNormal_OnFrame(void)
{
    if (lbl_804736C0.x36.done) {
        gm_801A4B60();
    }
}

f32 gm_801883C0(void)
{
    HSD_GObj* gobj;
    HSD_CObj* cobj;
    HSD_AObj* aobj;

    gobj = lbl_804736C0.x8;
    if (gobj == NULL) {
        goto return_default;
    }

    cobj = gobj->hsd_obj;
    goto check_cobj;

return_default:
    return 0.0f;

check_cobj:
    aobj = cobj->eyepos->aobj;
    if (aobj != NULL) {
        return aobj->curr_frame;
    }

    aobj = cobj->interest->aobj;
    if (aobj != NULL) {
        return aobj->curr_frame;
    }

    return 0.0f;
}

bool gm_8018841C(void)
{
    if (gm_GetCurrentGameMode() == GM_TRAINING) {
        return true;
    }
    return false;
}
