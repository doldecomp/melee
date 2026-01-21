#include "vi0501.h"

#include "dolphin/mtx.h"
#include "ef/efasync.h"
#include "ef/eflib.h"

#include "forward.h"

#include "gm/gm_1601.h"
#include "gm/gm_1A45.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbshadow.h"
#include "mn/mnmain.h"
#include "sc/types.h"
#include "vi/types.h"
#include "vi/vi.h"

#include <dolphin/gx.h>
#include <baselib/aobj.h>
#include <baselib/cobj.h>
#include <baselib/displayfunc.h>
#include <baselib/fog.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjproc.h>
#include <baselib/wobj.h>

static SceneDesc* un_804D6F70;
static HSD_Archive* un_804D6F74;
static HSD_Archive* un_804D6F78;
static GXColor erase_colors_vi0501;
static float un_804D6F80;
static ViCharaDesc un_804D6F84;

static Vec3 initial_pos = { 0.0f, 0.0f, 0.0f };

void un_8031D9E4(int arg0, int arg1, int arg2)
{
    ViCharaDesc* desc;
    un_804D6F84.p1_char_index = arg0;
    desc = &un_804D6F84;
    desc->p1_costume_index = arg1;
    desc->p2_costume_index = arg2;
}

/// #un_8031D9F8

void vi_8031DC80(HSD_GObj* gobj, int unused)
{
    PAD_STACK(8);
    lbShadow_8000F38C(0);
    vi_RunCamera(gobj, (u8*) &erase_colors_vi0501, 0x281);
}

void fn_8031DD14(HSD_GObj* gobj)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    f32 frame;

    HSD_CObjAnim(cobj);
    frame = cobj->aobj->curr_frame;

    if (60.0f == frame || 70.0f == frame || 85.0f == frame) {
        vi_8031C9B4(0xC, 0);
        lbAudioAx_800237A8(0x222F9, 0x7F, 0x40);

        if (60.0f == cobj->aobj->curr_frame) {
            lbAudioAx_800237A8(0x73, 0x7F, 0x40);
        }
        if (70.0f == cobj->aobj->curr_frame) {
            lbAudioAx_800237A8(0x74, 0x7F, 0x40);
        }
        if (85.0f == cobj->aobj->curr_frame) {
            lbAudioAx_800237A8(0x73, 0x7F, 0x40);
        }
    }

    frame = cobj->aobj->curr_frame;
    if (98.0f == frame || 108.0f == frame || 123.0f == frame) {
        lbAudioAx_800237A8(0x22308, 0x7F, 0x40);
    }

    if (cobj->aobj->curr_frame == cobj->aobj->end_frame) {
        lb_800145F4();
        gm_801A4B60();
    }
}
void un_8031DE58_OnEnter(void* arg)
{
    s32 i;
    u8 char_index;
    HSD_GObj* fog_gobj;
    HSD_GObj* light_gobj;
    HSD_GObj* camera_gobj;
    HSD_GObj* model_gobj;
    HSD_Fog* fog;
    HSD_LObj* lobj;
    HSD_CObj* cobj;
    HSD_JObj* jobj;
    ViCharaDesc* desc;

    lbAudioAx_800236DC();
    efLib_8005B4B8();
    efAsync_8006737C(0);

    desc = (ViCharaDesc*) arg;
    char_index = desc->p1_char_index;

    un_804D6F74 = lbArchive_LoadSymbols("Vi0501.dat", &un_804D6F70,
                                        "visual0501Scene", NULL);
    un_804D6F78 =
        lbArchive_LoadSymbols(viGetCharAnimByIndex(char_index), NULL);

    fog_gobj = GObj_Create(0xB, 3, 0);
    fog = HSD_FogLoadDesc(un_804D6F70->fogs->desc);
    HSD_GObjObject_80390A70(fog_gobj, HSD_GObj_804D7848, fog);
    GObj_SetupGXLink(fog_gobj, HSD_GObj_FogCallback, 0, 0);
    erase_colors_vi0501 = fog->color;

    light_gobj = GObj_Create(0xB, 3, 0);
    lobj = lb_80011AC4(un_804D6F70->lights);
    HSD_GObjObject_80390A70(light_gobj, HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(light_gobj, HSD_GObj_LObjCallback, 0, 0);

    camera_gobj = GObj_Create(0x13, 0x14, 0);
    cobj =
        lb_80013B14((HSD_CameraDescPerspective*) un_804D6F70->cameras->desc);
    HSD_GObjObject_80390A70(camera_gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(camera_gobj, vi_8031DC80, 5);
    HSD_CObjAddAnim(cobj, un_804D6F70->cameras->anims[0]);
    HSD_CObjReqAnim(cobj, 0.0f);
    HSD_CObjAnim(cobj);
    HSD_GObjProc_8038FD54(camera_gobj, fn_8031DD14, 0);

    for (i = 0; un_804D6F70->models[i] != NULL; i++) {
        model_gobj = GObj_Create(0xE, 0xF, 0);
        jobj = HSD_JObjLoadJoint(un_804D6F70->models[i]->joint);
        HSD_GObjObject_80390A70(model_gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(model_gobj, HSD_GObj_JObjCallback, 9, 0);
        gm_8016895C(jobj, un_804D6F70->models[i], 0);
        HSD_JObjReqAnimAll(jobj, 0.0f);
        HSD_JObjAnimAll(jobj);
        HSD_GObjProc_8038FD54(model_gobj, mn_8022EAE0, 0x17);
    }

    un_8031D9F8(desc->p1_char_index, desc->p1_costume_index,
                desc->p2_costume_index, (int) &desc->spawn_count);
    lbAudioAx_800237A8(0x20B, 0x7F, 0x40);
    lbAudioAx_800237A8(0x20C, 0x7F, 0x40);
}

void vi_8031E0F0_OnFrame(void)
{
    vi_8031CAAC();
}
