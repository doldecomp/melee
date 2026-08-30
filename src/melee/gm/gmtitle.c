#include "gmtitle.h"

#include "gm_unsplit.h"

#include "gm/gmevent.h"
#include "gm/gmmain_lib.h"
#include "gm/gmopening.h"
#include "mn/inlines.h"

#include <baselib/sislib.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/displayfunc.h>
#include <sysdolphin/baselib/fog.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/random.h>
#include <melee/db/db.h>
#include <melee/gm/types.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lblanguage.h>
#include <melee/lb/lbmthp.h>
#include <melee/lb/lbspdisplay.h>
#include <melee/lb/lbtime.h>
#include <melee/mn/mnmain.h>
#include <melee/sc/types.h>

static StaticModelDesc model_desc_0;
static StaticModelDesc model_desc_1;
static char debug_text_buffer[0x80];
static AnimLoopSettings loop_settings_0 = { 0, 1600.0F, 400.0F };
static AnimLoopSettings loop_settings_1 = { 0, 1330.0F, 130.0F };
static Vec3 jobj_translate = { 0, -3, 0 };

static HSD_CameraDescPerspective* cobj_desc;
static LightList** list_list;
static HSD_FogDesc* fog_desc;
static int countdown_timer;
static u32 frame_count;
static GXBool bg_initialized;

HSD_GObj* gmTitle_801A12C4(void)
{
    HSD_GObj* gobj = GObj_Create(HSD_GOBJ_CLASS_UI, 15, 0);
    HSD_JObj* jobj = HSD_JObjLoadJoint(model_desc_0.joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 9, 0);
    HSD_JObjAddAnimAll(jobj, model_desc_0.animjoint,
                       model_desc_0.matanim_joint,
                       model_desc_0.shapeanim_joint);
    HSD_JObjReqAnimAll(jobj, loop_settings_0.loop_frame);
    HSD_JObjAnimAll(jobj);

    HSD_JObjSetTranslate(jobj, &jobj_translate);
    {
        HSD_JObj* result;
        lb_80011E24(jobj, &result, 3, -1);
        HSD_JObjSetFlagsAll(result, JOBJ_HIDDEN);
        lb_80011E24(jobj, &result, 1, -1);
        HSD_JObjSetFlagsAll(result, JOBJ_HIDDEN);
    }
    return gobj;
}

/// Animation callback for background
static void gmTitle_801A146C(HSD_GObj* gobj)
{
    mn_8022ED6C(GET_JOBJ(gobj), &loop_settings_1);
}

static inline bool isActiveTitle(void)
{
    if (gm_GetCurrentGameMode() == GM_TITLE ||
        (gm_GetCurrentGameMode() == GM_OPENING_MV &&
         gm_GetCurrentSceneIndex() == GS_VS))
    {
        return false;
    }
    return true;
}

/// Set up title screen animated background
static void fn_801A1498_inline(void)
{
    HSD_GObj* gobj = GObj_Create(HSD_GOBJ_CLASS_UI, 15, 0);
    HSD_JObj* jobj = HSD_JObjLoadJoint(model_desc_1.joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 3, 0);
    HSD_JObjAddAnimAll(jobj, model_desc_1.animjoint,
                       model_desc_1.matanim_joint,
                       model_desc_1.shapeanim_joint);
    HSD_GObj_SetupProc(gobj, gmTitle_801A146C, 0);
    if (isActiveTitle()) {
        HSD_JObjReqAnimAll(jobj, loop_settings_1.start_frame);
    } else {
        HSD_JObjReqAnimAll(jobj, 130.0F);
    }
    HSD_JObjAnimAll(jobj);
}

static void fn_801A1498(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    if (gm_804D67EC > 5400) {
        mn_8022ED6C(jobj, &loop_settings_0);
    } else {
        HSD_JObjReqAnimAll(jobj, gm_804D67EC - 5130);
        HSD_JObjAnimAll(jobj);
    }
    if (bg_initialized == GX_FALSE) {
        if (mn_8022F298(jobj) >= 270.0F) {
            fn_801A1498_inline();
            lbMthp_8001F614(0);
            bg_initialized = GX_TRUE;
        }
    }
}

static void gmTitle_801A1630(HSD_GObj* gobj)
{
    mn_8022ED6C(GET_JOBJ(gobj), &loop_settings_0);
}

/// @todo similar to ::gm_801AA688
static bool isEmblemUnlocked(void)
{
    if (gm_IsCKindUnlocked(CKIND_MARS) || gm_IsCKindUnlocked(CKIND_EMBLEM)) {
        return true;
    }
    return false;
}

HSD_GObj* gmTitle_801A165C(void)
{
    HSD_GObj* gobj = GObj_Create(HSD_GOBJ_CLASS_UI, 15, 0);
    HSD_JObj* jobj = HSD_JObjLoadJoint(model_desc_0.joint);
    u8 kind = HSD_GObj_JObjKind;

    HSD_GObjObject_80390A70(gobj, kind, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 9, 0);
    HSD_JObjAddAnimAll(jobj, model_desc_0.animjoint,
                       model_desc_0.matanim_joint,
                       model_desc_0.shapeanim_joint);
    if (isActiveTitle()) {
        bg_initialized = GX_FALSE;
        HSD_JObjReqAnimAll(jobj, loop_settings_0.start_frame);
        HSD_GObj_SetupProc(gobj, fn_801A1498, 0);
    } else {
        HSD_JObjReqAnimAll(jobj, 400.0F);
        HSD_GObj_SetupProc(gobj, gmTitle_801A1630, 0);
    }
    HSD_JObjAnimAll(jobj);
    if (!isEmblemUnlocked()) {
        HSD_JObj* result;
        lb_80011E24(jobj, &result, 7, -1);
        HSD_JObjSetFlagsAll(result, JOBJ_HIDDEN);
    }
    {
        datetime time;
        int second;
        gm_801692E8(lbTime_GetTimeInSeconds(), &time);
        second = time.second;
        while (second != 0) {
            HSD_Rand();
            second--;
        }
    }
    gm_SetupTitleDemo();
    return gobj;
}

static void gmTitle_801A1814(HSD_GObj* gobj, int unused)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    if (HSD_CObjSetCurrent(GET_COBJ(gobj))) {
        HSD_GObj_80390ED0(gobj, 0x7);
        HSD_CObjEndCurrent();
    }
}

void gmTitle_801A185C(void)
{
    HSD_GObj* gobj = GObj_Create(HSD_GOBJ_CLASS_CAMERA, 20, 0);
    HSD_CObj* cobj = lb_80013B14(cobj_desc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_CameraKind, cobj);
    GObj_SetupGXLinkMax(gobj, gmTitle_801A1814, 0xC);
    gobj->gxlink_prios = 0x209;
}

static void gmTitle_801A18D4(HSD_GObj* gobj, int unused)
{
    GXColor erase_color = fog_desc->color;
    if (HSD_CObjSetCurrent(GET_COBJ(gobj))) {
        HSD_SetEraseColor(erase_color.r, erase_color.g, erase_color.b,
                          erase_color.a);
        HSD_CObjEraseScreen(GET_COBJ(gobj), 1, 0, 1);
        HSD_CObjEndCurrent();
    }
}

void gmTitle_801A1944(void)
{
    HSD_GObj* gobj = GObj_Create(HSD_GOBJ_CLASS_CAMERA, 20, 0);
    HSD_CObj* cobj = lb_80013B14(cobj_desc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_CameraKind, cobj);
    GObj_SetupGXLinkMax(gobj, gmTitle_801A18D4, 0);
}

void gmTitle_801A19AC(void)
{
    HSD_GObj* gobj = GObj_Create(HSD_GOBJ_CLASS_LIGHT, 3, 128);
    HSD_LObj* lobj = lb_80011AC4(list_list);
    PAD_STACK(4);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_LightKind, lobj);
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0);
}

static void gmTitle_801A1A18(HSD_GObj* gobj)
{
    HSD_FogInterpretAnim(GET_FOG(gobj));
}

HSD_GObj* gmTitle_801A1A3C(void)
{
    HSD_GObj* gobj = GObj_Create(HSD_GOBJ_CLASS_FOG, 3, 0);
    HSD_Fog* fog = HSD_FogLoadDesc(fog_desc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_FogKind, fog);
    GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 0, 0);
    HSD_GObj_SetupProc(gobj, gmTitle_801A1A18, 0);
    return gobj;
}

HSD_Archive* gmTitle_801A1AC0(void)
{
    const char dat[] = "GmTtAll.dat";
    const char usd[] = "GmTtAll.usd";

    return lbArchive_LoadSymbols(
        lbLang_IsSettingUS() ? usd : dat, &model_desc_0.joint,
        "TtlMoji_Top_joint", &model_desc_0.animjoint, "TtlMoji_Top_animjoint",
        &model_desc_0.matanim_joint, "TtlMoji_Top_matanim_joint",
        &model_desc_0.shapeanim_joint, "TtlMoji_Top_shapeanim_joint",

        &cobj_desc, "ScTitle_cam_int1_camera", &list_list,
        "ScTitle_scene_lights", &fog_desc, "ScTitle_fog",

        &model_desc_1.joint, "TtlBg_Top_joint", &model_desc_1.animjoint,
        "TtlBg_Top_animjoint", &model_desc_1.matanim_joint,
        "TtlBg_Top_matanim_joint", &model_desc_1.shapeanim_joint,
        "TtlBg_Top_shapeanim_joint",

        &gm_804D67F0, "TitleMark_sobjdesc", 0);
}

void gm_Scene_Title_OnFrame(void)
{
    int input = gm_GetButtonsTriggered(PAD_ALL_CONTROLLERS);
    int* tmp;
    if (countdown_timer != 0) {
        countdown_timer--;
        return;
    }
    frame_count++;
    if (frame_count > 600) {
        tmp = gm_GetCurrentSceneExitData();
        *tmp = 0;
        gm_801A4B60();
    } else if (input & HSD_PAD_START) {
        lbAudioAx_80026F2C(0x1C);
        lbAudioAx_8002702C(0xC, 0);
        lbAudioAx_80027168();
        lbAudioAx_80027648();
        sfxForward();
        gmMainLib_8015ECBC();
        tmp = gm_GetCurrentSceneExitData();
        *tmp = input;
        gm_801A4B60();
    } else if (DbLevel >= DbLKind_DebugRom) {
        if (input & HSD_PAD_Y) {
            sfxForward();
            tmp = gm_GetCurrentSceneExitData();
            *tmp = input;
            gm_801A4B60();
        } else if (input & HSD_PAD_A) {
            sfxForward();
            tmp = gm_GetCurrentSceneExitData();
            *tmp = input;
            gm_801A4B60();
        } else if (input & HSD_PAD_X) {
            sfxForward();
            tmp = gm_GetCurrentSceneExitData();
            *tmp = input;
            gm_801A4B60();
        }
    }
}

static char* gmTitle_801A1D38(const char* src, char* dst)
{
    while (*src != '\0') {
        if (*src == 0x20) {
            dst[0] = -0x7F;
            dst[1] = 0x40;
            dst += 2;
        } else if (*src >= 0x30 && *src <= 0x39) {
            dst[0] = -0x7E;
            dst[1] = *src + 0x1F;
            dst += 2;
        } else if (*src >= 0x41 && *src <= 0x5A) {
            dst[0] = -0x7E;
            dst[1] = *src + 0x1F;
            dst += 2;
        } else if (*src >= 0x61 && *src <= 0x7A) {
            dst[0] = -0x7E;
            dst[1] = *src - 0xE0;
            dst += 2;
        } else {
            dst[0] = -0x7F;
            dst[1] = 0x44;
            dst += 2;
        }
        src++;
    }
    dst[0] = 0;
    return dst;
}

void gm_Scene_Title_OnEnter(void* unused)
{
    HSD_Text* text;
    int scale;
    HSD_Archive* archive;

    lbAudioAx_800236DC();
    countdown_timer = 20;
    frame_count = 0;

    archive = gmTitle_801A1AC0();
    (void) archive;

    lbAudioAx_80026F2C((1 << 1) | (1 << 4));
    lbAudioAx_8002702C(2, 4);
    lbAudioAx_80027168();

    gmTitle_801A1A3C();
    gmTitle_801A19AC();
    gmTitle_801A1944();
    gmTitle_801A185C();
    gmTitle_801A165C();

    lbAudioAx_80027648();
    gm_PreloadTitleDemo();

    fn_801A1498_inline();

    // Debug shows the build timestamp on the title screen
    if (DbLevel >= DbLKind_NoDebugRom) {
        HSD_SisLib_803A611C(0, NULL, 9, 0xD, 0, 0xE, 0, 0x13);
        text = HSD_SisLib_803A6754(0, 0);
        gmTitle_801A1D38(db_build_timestamp, debug_text_buffer);
        scale =
            HSD_SisLib_803A6B98(text, 30.0F, 30.0F, "%s", debug_text_buffer);
        text->default_kerning = 1;
        HSD_SisLib_803A7548(text, scale, 0.7f, 0.55f);
    }
}
