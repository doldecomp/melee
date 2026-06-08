#include "gmopening.h"

#include "gm_unsplit.h"
#include "gmtitle.h"

#include <stdio.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/particle.h>
#include <sysdolphin/baselib/sobjlib.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lblanguage.h>
#include <melee/lb/lbmthp.h>
#include <melee/mn/types.h>

/* 3B7D68 */ static const Vec3 gm_803B7D68 = { 0.0f, 0.0f, 1.0f };
/* 3B7D74 */ static const Vec3 gm_803B7D74 = { 0.0f, 0.0f, 0.0f };
/* 480B38 */ static PerfLabelLine gm_80480B38[4];
/* 4D67D0 */ static bool gm_804D67D0;
/* 4D67D4 */ static HSD_GObj* gm_804D67D4;
/* 4D67D8 */ static HSD_GObj* gm_804D67D8;
/* 4D67DC */ static bool gm_804D67DC;
/* 4D67E0 */ static u8 gm_804D67E0;
/* 4D67E1 */ static u8 gm_804D67E1;
/* 4D67E2 */ static u8 gm_804D67E2;
/* 4D67E4 */ static u32 gm_804D67E4;
/* 4D67E8 */ static HSD_GObj* gm_804D67E8;
/* 4D67EC */ u32 gm_804D67EC;
/* 4D67F0 */ int gm_804D67F0;
/* 4D67F4 */ static HSD_GObj* gm_804D67F4;

static void sdata2_order(void)
{
    (void) 82.0f;
    (void) 290.0f;
}

void gm_801A9DD0(HSD_GObj* arg0, u16 arg1, u16 arg2, int arg3, int arg4)
{
    HSD_CObj* cobj;
    f32 roll = 0.0f;
    f32 far_val;
    f32 near_val = 0.0f;
    f32 top;
    f32 bottom;
    f32 left;
    f32 right;
    Scissor viewport;
    Scissor scissor;
    Vec3 eye = gm_803B7D68;
    Vec3 interest = gm_803B7D74;

    far_val = 2.0f;
    bottom = (f32) (-(s32) (u16) arg2);
    right = (f32) arg1;
    top = 0.0f;
    left = 0.0f;

    if (arg4 != 0) {
        s32 temp = (s32) (arg1 - 0x248) / 2;
        left = (f32) temp;
        right = (f32) (temp + 0x248);
    }
    viewport.left = 0;
    scissor.left = 0;
    viewport.right = arg1;
    scissor.right = arg1;
    viewport.top = 0;
    scissor.top = 0;
    viewport.bottom = arg2;
    scissor.bottom = arg2;
    cobj = HSD_CObjAlloc();
    HSD_CObjSetProjectionType(cobj, PROJ_ORTHO);
    HSD_CObjSetViewport(cobj, (HSD_RectS16*) &viewport);
    HSD_CObjSetScissor(cobj, &scissor);
    HSD_CObjSetEyePosition(cobj, &eye);
    HSD_CObjSetInterest(cobj, &interest);
    HSD_CObjSetRoll(cobj, roll);
    HSD_CObjSetNear(cobj, near_val);
    HSD_CObjSetFar(cobj, far_val);
    HSD_CObjSetOrtho(cobj, top, bottom, left, right);
    HSD_GObjObject_80390A70(arg0, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(arg0, HSD_SObjLib_803A54EC, (u32) arg3);
}

#pragma push
#pragma force_active on
static float unused_floats[] = {
    0.0f, 1600.0, 400.0f, 0.0f, 1330.0f, 130.0f, 0.0f, -3.0f, 0.0f,
};
#pragma pop

void* fn_801A9FCC(void)
{
    u32 ms;
    s32 idx;
    PerfLabelLine* lines = gm_80480B38;

    lines[0].unk_04 = 0;

    idx = 0;
    sprintf(lines[idx].text, "\\cffff00%2d", lbMthp_8001F5F4());

    lines[0].next = &lines[1];
    lines[1].unk_04 = 0;

    ms = lbMthp_8001F5E4();
    idx = 1;
    sprintf(lines[idx].text, "\\cffff00%2d", ms);

    lines[1].next = &lines[2];
    lines[2].unk_04 = 0;

    ms = (u32) ((f32) (u32) lbMthp_8001F5D4() /
                (f32) (*(u32*) 0x800000F8 / 4 / 1000));
    idx = 2;
    sprintf(lines[idx].text, "\\cffff00%3d", ms);

    lines[2].next = &lines[3];
    lines[2].next = NULL;

    return lines;
}

void fn_801AA0E8(void)
{
    hsd_80392528((Event) fn_801A9FCC);
}

/* 3DBFB4 */ static int gm_803DBFB4[] = {
    0x000004E2, 0x00000002, 0x0000018A, 0x00000001, 0x00010000, 0x00000002,
};

void gm_801AA110_OnEnter(UNK_T arg0)
{
    HSD_GObj* temp_r3;
    HSD_GObj* temp_r3_2;
    HSD_GObj* temp_r3_3;
    PAD_STACK(8);

    gm_804D67D0 = 0;
    gm_804D67D4 = 0;
    gm_804D67D8 = 0;
    gm_804D67EC = 0;
    gm_804D67E0 = 0;
    gm_804D67E1 = 0;
    gm_804D67DC = 0;
    gm_804D67E2 = 0;
    gmTitle_801A1AC0();
    lbAudioAx_80026F2C(0x12);
    lbAudioAx_8002702C(2, 4);
    lbAudioAx_80027168();
    gmMainLib_8015F588(0);
    gmTitle_801A1A3C();
    gmTitle_801A19AC();
    gmTitle_801A1944();

    temp_r3 = GObj_Create(0x13, 0x14, 0);
    gm_804D67F4 = temp_r3;
    gm_801A9DD0(temp_r3, 0x280, 0x1E0, 8, 0);
    temp_r3->gxlink_prios = 0x800;

    temp_r3_2 = GObj_Create(0x13, 0x14, 0);
    gm_801A9DD0(temp_r3_2, 0x280, 0x1E0, 0xB, 1);
    temp_r3_2->gxlink_prios = 0x20000;
    gmTitle_801A185C();

    temp_r3_3 = GObj_Create(0xE, 0xF, 0);
    gm_804D67E8 = temp_r3_3;
    GObj_SetupGXLink(temp_r3_3, lbMthp_8001F67C, 0xB, 0);
    lbMthp_8001F624(temp_r3_3, 0x280, 0x1E0);

    lbAudioAx_80027648();
    lbAudioAx_80023F28(0x3E);
    lbAudioAx_80024E50(1);
    lbMthp_8001F410("MvOpen.mth", gm_803DBFB4, 0, 0, 0);
    lbAudioAx_80024E50(0);
    gm_804D6724 = fn_801AA0E8;
}

void gm_801AA28C_OnFrame(void)
{
    HSD_GObj* temp_r3_2;
    int temp_r3;
    HSD_SObj* temp_r3_3;
    PAD_STACK(4);

    lbMthp_8001F578();
    temp_r3 = lbMthp_8001F5C4();
    if ((u32) gm_804D67EC > 0x1518) {
        gm_804D67EC += 1;
    } else {
        gm_804D67EC = (u32) temp_r3;
    }
    if (lbLang_IsSettingUS() != 0) {
        if (gm_804D67E0 == 0 && gm_804D67EC >= 0x13AA) {
            lbAudioAx_800237A8(0x4E21, 0x7F, 0x40);
            gm_804D67E0 = 1;
        }
    } else {
        if (gm_804D67E0 == 0 && gm_804D67EC >= 0x1374) {
            lbAudioAx_800237A8(0x4E22, 0x7F, 0x40);
            gm_804D67E0 = 1;
        }
        if (gm_804D67E1 == 0 && gm_804D67EC >= 0x13EC) {
            lbAudioAx_800237A8(0x4E23, 0x7F, 0x40);
            gm_804D67E1 = 1;
        }
    }
    if (((u8) gm_804D67E2 == 0) && ((u32) gm_804D67EC >= 0x1374U)) {
        gmMainLib_8015F500();
        gm_804D67E2 = 1;
    }
    if (gm_804D67D4 == NULL && gm_804D67EC >= 0x1C6 && gm_804D67EC < 0x202) {
        temp_r3_2 = GObj_Create(0xEU, 0xFU, 0U);
        HSD_GObjObject_80390A70(temp_r3_2, HSD_SObjLib_804D7960, NULL);
        GObj_SetupGXLink(temp_r3_2, HSD_SObjLib_803A49E0, 0x11U, 0U);
        temp_r3_3 =
            HSD_SObjLib_803A477C(temp_r3_2, gm_804D67F0, 0, 0, 0x80, 0);
        temp_r3_3->x10 = 82.0f;
        temp_r3_3->x14 = 290.0f;
        gm_804D67D4 = temp_r3_2;
    }
    if ((gm_804D67D4 != NULL) && ((u32) gm_804D67EC >= 0x202)) {
        HSD_GObjPLink_80390228(gm_804D67D4);
        gm_804D67D4 = NULL;
    }
    if ((gm_804D67D8 == NULL) && ((u32) gm_804D67EC >= 0x3B6) &&
        (gm_804D67EC < 0x3CE))
    {
        gm_804D67D8 = gmTitle_801A12C4();
    }
    if ((gm_804D67D8 != NULL) && (gm_804D67EC >= 0x3CE)) {
        HSD_GObjPLink_80390228(gm_804D67D8);
        gm_804D67D8 = NULL;
    }
    if (!gm_804D67D0 && (gm_804D67EC >= 0x140A)) {
        gmTitle_801A165C();
        gm_804D67D0 = true;
        gm_804D67E4 = (600.0f + (400.0f + gm_804D67EC));
    }
    if (lbMthp_8001F604() != 0 && !gm_804D67DC && gm_804D67D0) {
        gm_801BF3F8();
        gm_804D67DC = true;
    }
    if (gm_804D67D0 && (gm_804D67EC == gm_804D67E4)) {
        lbAudioAx_800236DC();
        gm_801A4B60();
    } else if (gmMainLib_8046B0F0.xC && lbMthp_8001F604() == 0) {
        gmMainLib_8015F500();
        lbAudioAx_800236DC();
        lbAudioAx_80023694();
        gm_801A4B74();
        gm_801A42E8(GM_TITLE);
        gm_801A42D4();
    } else if (gm_804D67EC > 0x157C) {
        if (gm_801A36A0(4) & 0x1000) {
            gmMainLib_8015F500();
            lbAudioAx_800236DC();
            lbAudioAx_80024030(1);
            gm_801A4B60();
            gm_80173EEC();
            gm_80172898(0x100);
            if (!gm_80173754(1, 0)) {
                gm_801A42E8(GM_MENU);
            }
            gm_801A42D4();
        }
    } else {
        if (gm_801A36A0(4) & 0x1100) {
            gmMainLib_8015F500();
            lbAudioAx_800236DC();
            lbAudioAx_80023694();
            lbAudioAx_80024030(1);
            gm_801A4B60();
            gm_801A42E8(GM_TITLE);
            gm_801A42D4();
        }
    }
}
