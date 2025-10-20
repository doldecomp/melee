#include "gmtitle.h"

#include "gm_unsplit.h"

#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/displayfunc.h>
#include <sysdolphin/baselib/fog.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/random.h>
#include <melee/db/db.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/types.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lblanguage.h>
#include <melee/lb/lbmthp.h>
#include <melee/lb/lbtime.h>
#include <melee/mn/mnmain.h>
#include <melee/sc/types.h>

static StaticModelDesc gmTitle_80479B28;
static StaticModelDesc gmTitle_80479B38;
static char gmTitle_80479B48[0x80]; // debug text
Vec3 gmTitle_803DA4F0 = { 0, 1600.0F, 400.0F };
Vec3 gmTitle_803DA4FC = { 0, 1330.0F, 130.0F };
Vec3 gmTitle_803DA508 = { 0, -3, 0 };

static HSD_CameraDescPerspective* gmTitle_804D6708;
static LightList** gmTitle_804D670C;
static HSD_FogDesc* gmTitle_804D6710;
static int gmTitle_804D6714;
static u32 gmTitle_804D6718;
static u8 gmTitle_804D671C;

extern u32 gm_804D67EC;

HSD_GObj* gmTitle_801A12C4(void)
{
    HSD_JObj* sp8;
    HSD_GObj* gobj = GObj_Create(0xE, 0xF, 0);
    HSD_JObj* jobj = HSD_JObjLoadJoint(gmTitle_80479B28.joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 9, 0);
    HSD_JObjAddAnimAll(jobj, gmTitle_80479B28.animjoint,
                       gmTitle_80479B28.matanim_joint,
                       gmTitle_80479B28.shapeanim_joint);
    HSD_JObjReqAnimAll(jobj, gmTitle_803DA4F0.z);
    HSD_JObjAnimAll(jobj);

    HSD_JObjSetTranslate(jobj, &gmTitle_803DA508);
    lb_80011E24(jobj, &sp8, 3, -1);
    HSD_JObjSetFlagsAll(sp8, JOBJ_HIDDEN);
    lb_80011E24(jobj, &sp8, 1, -1);
    HSD_JObjSetFlagsAll(sp8, JOBJ_HIDDEN);
    return gobj;
}

/// Animation callback for background
static void gmTitle_801A146C(HSD_GObj* gobj)
{
    mn_8022ED6C(GET_JOBJ(gobj), &gmTitle_803DA4FC);
}

/// Set up title screen animated background
static inline void fn_801A1498_inline(void)
{
    bool var_r0;
    HSD_GObj* gobj = GObj_Create(0xE, 0xF, 0);
    HSD_JObj* jobj = HSD_JObjLoadJoint(gmTitle_80479B38.joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 3, 0);
    HSD_JObjAddAnimAll(jobj, gmTitle_80479B38.animjoint,
                       gmTitle_80479B38.matanim_joint,
                       gmTitle_80479B38.shapeanim_joint);
    HSD_GObjProc_8038FD54(gobj, gmTitle_801A146C, 0);
    if (gm_801A4310() == MJ_TITLE ||
        (gm_801A4310() == MJ_OPENING_MV && gm_801A42C4() == MN_VS))
    {
        var_r0 = false;
    } else {
        var_r0 = true;
    }
    if (var_r0 != 0) {
        HSD_JObjReqAnimAll(jobj, gmTitle_803DA4FC.x);
    } else {
        HSD_JObjReqAnimAll(jobj, 130.0F);
    }
    HSD_JObjAnimAll(jobj);
}

static void fn_801A1498(HSD_GObj* arg0)
{
    HSD_JObj* jobj = GET_JOBJ(arg0);
    if (gm_804D67EC > 0x1518) {
        mn_8022ED6C(jobj, &gmTitle_803DA4F0);
    } else {
        HSD_JObjReqAnimAll(jobj, gm_804D67EC - 0x140A);
        HSD_JObjAnimAll(jobj);
    }
    if (gmTitle_804D671C == 0) {
        if (mn_8022F298(jobj) >= 270.0F) {
            fn_801A1498_inline();
            lbMthp_8001F614(0);
            gmTitle_804D671C = 1;
        }
    }
}

static void gmTitle_801A1630(HSD_GObj* gobj)
{
    mn_8022ED6C(GET_JOBJ(gobj), &gmTitle_803DA4F0);
}

HSD_GObj* gmTitle_801A165C(void)
{
    int var_r0;
    HSD_JObj* sp10;
    datetime sp8;

    HSD_GObj* gobj = GObj_Create(0xE, 0xF, 0);
    HSD_JObj* jobj = HSD_JObjLoadJoint(gmTitle_80479B28.joint);
    int second;

    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 9, 0);
    HSD_JObjAddAnimAll(jobj, gmTitle_80479B28.animjoint,
                       gmTitle_80479B28.matanim_joint,
                       gmTitle_80479B28.shapeanim_joint);

    if (gm_801A4310() == MJ_TITLE ||
        (gm_801A4310() == MJ_OPENING_MV && gm_801A42C4() == MN_VS))
    {
        var_r0 = false;
    } else {
        var_r0 = true;
    }
    if (var_r0) {
        gmTitle_804D671C = 0;
        HSD_JObjReqAnimAll(jobj, gmTitle_803DA4F0.x);
        HSD_GObjProc_8038FD54(gobj, fn_801A1498, 0);
    } else {
        HSD_JObjReqAnimAll(jobj, 400.0F);
        HSD_GObjProc_8038FD54(gobj, gmTitle_801A1630, 0);
    }
    HSD_JObjAnimAll(jobj);
    if (gm_80164840(CKIND_MARS) || gm_80164840(CKIND_EMBLEM)) {
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (!var_r0) {
        lb_80011E24(jobj, &sp10, 7, -1);
        HSD_JObjSetFlagsAll(sp10, JOBJ_HIDDEN);
    }
    gm_801692E8(lbTime_8000AFBC(), &sp8);
    second = sp8.second;
    while (second != 0) {
        HSD_Rand();
        second--;
    }
    gm_801BF128();
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
    HSD_GObj* gobj = GObj_Create(0x13, 0x14, 0);
    HSD_CObj* cobj = lb_80013B14(gmTitle_804D6708);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, gmTitle_801A1814, 0xC);
    gobj->gxlink_prios = 0x209;
}

static void gmTitle_801A18D4(HSD_GObj* gobj, int unused)
{
    GXColor erase_color = gmTitle_804D6710->color;
    if (HSD_CObjSetCurrent(GET_COBJ(gobj))) {
        HSD_SetEraseColor(erase_color.r, erase_color.g, erase_color.b,
                          erase_color.a);
        HSD_CObjEraseScreen(GET_COBJ(gobj), 1, 0, 1);
        HSD_CObjEndCurrent();
    }
}

void gmTitle_801A1944(void)
{
    HSD_GObj* gobj = GObj_Create(0x13, 0x14, 0);
    HSD_CObj* cobj = lb_80013B14(gmTitle_804D6708);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, gmTitle_801A18D4, 0);
}

void gmTitle_801A19AC(void)
{
    HSD_GObj* gobj = GObj_Create(0xB, 0x3, 0x80);
    HSD_LObj* lobj = lb_80011AC4(gmTitle_804D670C);
    PAD_STACK(4);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0);
}

static void gmTitle_801A1A18(HSD_GObj* gobj)
{
    HSD_FogInterpretAnim(GET_FOG(gobj));
}

HSD_GObj* gmTitle_801A1A3C(void)
{
    HSD_GObj* gobj = GObj_Create(0xA, 0x3, 0);
    HSD_Fog* fog = HSD_FogLoadDesc(gmTitle_804D6710);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7848, fog);
    GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 0, 0);
    HSD_GObjProc_8038FD54(gobj, gmTitle_801A1A18, 0);
    return gobj;
}

extern UNK_T gm_804D67F0;

HSD_Archive* gmTitle_801A1AC0(void)
{
    const char dat[] = "GmTtAll.dat";
    const char usd[] = "GmTtAll.usd";

    return lbArchive_LoadSymbols(
        lbLang_IsSettingUS() ? usd : dat, &gmTitle_80479B28.joint,
        "TtlMoji_Top_joint", &gmTitle_80479B28.animjoint,
        "TtlMoji_Top_animjoint", &gmTitle_80479B28.matanim_joint,
        "TtlMoji_Top_matanim_joint", &gmTitle_80479B28.shapeanim_joint,
        "TtlMoji_Top_shapeanim_joint",

        &gmTitle_804D6708, "ScTitle_cam_int1_camera", &gmTitle_804D670C,
        "ScTitle_scene_lights", &gmTitle_804D6710, "ScTitle_fog",

        &gmTitle_80479B38.joint, "TtlBg_Top_joint",
        &gmTitle_80479B38.animjoint, "TtlBg_Top_animjoint",
        &gmTitle_80479B38.matanim_joint, "TtlBg_Top_matanim_joint",
        &gmTitle_80479B38.shapeanim_joint, "TtlBg_Top_shapeanim_joint",

        &gm_804D67F0, "TitleMark_sobjdesc", 0);
}

void gmTitle_801A1C18_OnFrame(void)
{
    int input = gm_801A36A0(4);
    int* tmp;
    if (gmTitle_804D6714 != 0) {
        gmTitle_804D6714--;
        return;
    }
    gmTitle_804D6718++;
    if (gmTitle_804D6718 > 600) {
        tmp = gm_801A4B9C();
        *tmp = 0;
        gm_801A4B60();
    } else if (input & HSD_PAD_START) {
        lbAudioAx_80026F2C(0x1C);
        lbAudioAx_8002702C(0xC, 0);
        lbAudioAx_80027168();
        lbAudioAx_80027648();
        lbAudioAx_80024030(1);
        gmMainLib_8015ECBC();
        tmp = gm_801A4B9C();
        *tmp = input;
        gm_801A4B60();
    } else if (g_debugLevel >= 3) {
        if (input & HSD_PAD_Y) {
            lbAudioAx_80024030(1);
            tmp = gm_801A4B9C();
            *tmp = input;
            gm_801A4B60();
        } else if (input & HSD_PAD_A) {
            lbAudioAx_80024030(1);
            tmp = gm_801A4B9C();
            *tmp = input;
            gm_801A4B60();
        } else if (input & HSD_PAD_X) {
            lbAudioAx_80024030(1);
            tmp = gm_801A4B9C();
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

void gmTitle_801A1E20_OnEnter(void* unused)
{
    HSD_Text* text;
    int scale;
    PAD_STACK(8);

    lbAudioAx_800236DC();
    gmTitle_804D6714 = 0x14;
    gmTitle_804D6718 = 0;

    gmTitle_801A1AC0();

    lbAudioAx_80026F2C(0x12);
    lbAudioAx_8002702C(2, 4);
    lbAudioAx_80027168();

    gmTitle_801A1A3C();
    gmTitle_801A19AC();
    gmTitle_801A1944();
    gmTitle_801A185C();
    gmTitle_801A165C();

    lbAudioAx_80027648();
    gm_801BF3F8();

    fn_801A1498_inline();

    // Debug shows the build timestamp on the title screen
    if (g_debugLevel >= 1) {
        HSD_SisLib_803A611C(0, NULL, 9, 0xD, 0, 0xE, 0, 0x13);
        text = HSD_SisLib_803A6754(0, 0);
        gmTitle_801A1D38(db_build_timestamp, gmTitle_80479B48);
        scale =
            HSD_SisLib_803A6B98(text, 30.0F, 30.0F, "%s", gmTitle_80479B48);
        text->default_kerning = 1;
        HSD_SisLib_803A7548(text, scale, 0.7f, 0.55f);
    }
}
