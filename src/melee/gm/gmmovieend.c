/**
 * @todo this file also contains the OnEnter callback for MN_DEBUG_MENU,
 * which should probably be split out into a separate file
 */

#include "gmmovieend.h"

#include "gm_unsplit.h"
#include "gmopening.h"

#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/sobjlib.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/types.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbmthp.h>
#include <melee/mn/types.h>
#include <melee/un/un_2FC9.h>

void gm_801A6254(MinorScene* arg0)
{
    u8 temp_ret;
    u8 temp_r0;
    MatchExitInfo* temp_r30;
    u8* temp_r31;

    temp_r30 = gm_801A4284(arg0);
    temp_r31 = gm_801736DC();
    gm_80162968(temp_r30->match_end.frame_count / 60);
    gm_8016247C(temp_r30->match_end.player_standings[0].xE);
    temp_r0 = temp_r30->match_end.result;
    if (temp_r0 != 7 && temp_r0 != 8 &&
        temp_r30->match_end.player_standings[0].stocks != 0)
    {
        gm_80164910(temp_r31[4]);
    } else {
        temp_ret = gm_80160638(temp_r31[4]);
        gmMainLib_8015DB2C(temp_ret);
    }
    gm_80173EEC();
    gm_80172898(0x100);
    if (gm_801721EC() == 0) {
        gm_SetScenePendingMinor(0);
    }
}

void gm_801A6308(MinorScene* arg0)
{
    gm_SetScenePendingMinor(0);
}

void gm_801A632C_OnEnter(void* arg0_)
{
    struct {
        UNK_T unk0;
        UNK_T unk4;
    }* arg0 = arg0_;
    un_802FF710();
    un_802FF6A0();
    un_80304168(arg0->unk0, 0, 0xA, 0xA);
    un_80302DF8(un_80302DF0(), arg0->unk4);
}

static u32 gm_804D6738;
static u8 gm_804D673C;

static char* gm_803DB1F4[0x1A] = {
    // clang-format off
    "MvEndCaptain.mth",
    "MvEndDonkey.mth",
    "MvEndFox.mth",
    "MvEndGamewatch.mth",
    "MvEndKirby.mth",
    "MvEndKoopa.mth",
    "MvEndLink.mth",
    "MvEndLuigi.mth",
    "MvEndMario.mth",
    "MvEndMarth.mth",
    "MvEndMewtwo.mth",
    "MvEndNess.mth",
    "MvEndPeach.mth",
    "MvEndPikachu.mth",
    "MvEndPoponana.mth",
    "MvEndPurin.mth",
    "MvEndSamus.mth",
    "MvEndYoshi.mth",
    "MvEndZelda.mth",
    "MvEndZelda.mth",
    "MvEndFalco.mth",
    "MvEndClink.mth",
    "MvEndDrmario.mth",
    "MvEndRoy.mth",
    "MvEndPichu.mth",
    "MvEndGanon.mth",
    // clang-format on
};
static int gm_803DB25C[0x1A] = {
    // clang-format off
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    // clang-format on
};

extern Event gm_804D6724;

void gm_801A637C_OnEnter(void* arg0)
{
    HSD_GObj* temp_r3;
    HSD_GObj* temp_r3_2;
    HSD_SObj_803A477C_t* temp_r3_3;
    const char* filename;
    PAD_STACK(8);

    gm_804D6738 = 0;
    gm_804D673C = 0x1E;
    temp_r3 = GObj_Create(0x13, 0x14, 0);
    gm_801A9DD0(temp_r3, 0x280, 0x1E0, 8, 0);
    temp_r3->gxlink_prios = 0x800;
    temp_r3_2 = GObj_Create(0xE, 0xF, 0);
    HSD_GObjObject_80390A70(temp_r3_2, HSD_SObjLib_804D7960, NULL);
    GObj_SetupGXLink(temp_r3_2, lbMthp_8001F67C, 0xB, 0);
    temp_r3_3 = lbMthp_8001F624(temp_r3_2, 0x1C0, 0x150);
    temp_r3_3->x10 = 96.0F;
    temp_r3_3->x14 = 72.0F;
    lbAudioAx_80023F28(gm_803DB25C[gm_801BEFB0()]);
    lbAudioAx_80024E50(1);
    filename = gm_803DB1F4[gm_801BEFB0()];
    lbMthp_8001F410(filename, 0, 0, 0, 0);
    lbAudioAx_80024E50(0);
    gm_804D6724 = fn_801AA0E8;
}

void gm_801A64A8_OnFrame(void)
{
    int temp_r31;
    bool var_r30;

    var_r30 = false;
    lbMthp_8001F578();
    temp_r31 = lbMthp_8001F5C4();
    if (lbMthp_8001F604() != 0) {
        gm_804D6738++;
    } else {
        gm_804D6738 = temp_r31;
    }
    if (gm_804D673C != 0) {
        gm_804D673C--;
        return;
    }
    if (gmMainLib_8046B0F0.xC != 0 && lbMthp_8001F604() == 0) {
        var_r30 = true;
    }
    if (gm_804D6738 >= 0x1A4 || (gm_801A36A0(gm_801BF010()) & 0x1000) ||
        var_r30)
    {
        lbAudioAx_800236DC();
        lbAudioAx_80023694();
        if (var_r30) {
            gm_801A4B74();
            return;
        }
        gm_801A4B60();
    }
}
