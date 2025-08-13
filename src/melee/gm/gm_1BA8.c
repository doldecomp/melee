#include "gm_1BA8.h"

#include "gm_1BA8.static.h"

#include "gm_unsplit.h"

#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/random.h>
#include <melee/db/db.h>
#include <melee/ft/ftlib.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmcamera.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/gmresult.h>
#include <melee/gm/gmresultplayer.h>
#include <melee/gm/gmtou.h>
#include <melee/gm/gmvsmelee.h>
#include <melee/gm/types.h>
#include <melee/gr/ground.h>
#include <melee/if/ifstock.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbbgflash.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lbcardnew.h>
#include <melee/lb/lbdvd.h>
#include <melee/lb/lbmthp.h>
#include <melee/lb/lbsnap.h>
#include <melee/lb/lbtime.h>
#include <melee/lb/types.h>
#include <melee/mn/mngallery.h>
#include <melee/mn/types.h>
#include <melee/pl/player.h>
#include <melee/pl/plbonuslib.h>
#include <melee/un/un_2FC9.h>
#include <melee/vi/types.h>
#include <melee/vi/vi0102.h>
#include <melee/vi/vi0402.h>
#include <melee/vi/vi0501.h>
#include <melee/vi/vi1101.h>
#include <melee/vi/vi1201v1.h>

MinorScene gm_803DF618_MinorScenes[] = {
    {
        0,
        3,
        0,
        gm_801BAA60,
        gm_801BAAD0,
        {
            MN_CSS,
            &gm_80497758,
            &gm_80497758,
        },
    },
    {
        1,
        3,
        0,
        gm_801BAD70,
        gm_801BB758,
        {
            MN_VS,
            &gm_804978A0,
            &gm_804979D8,
        },
    },
    { 0xFF },
};

/* 49E548 */ static struct gm_8049E548_t gm_8049E548;

extern u8 gm_804D68F8;
extern u8 gm_804D68F9;

void gm_801BA8FC(void)
{
    lbArchive_LoadSymbols("GmEvent.dat", &gm_804D6900,
                          "sqEventInitDataLevelTbl", 0);
}

/// #gm_801BA938

#pragma push
#pragma dont_inline on
void gm_801BAA60(MinorScene* arg0)
{
    struct EventData* temp_r31 = &gmMainLib_804D3EE0->unk_530;
    CSSData* css = gm_801A427C(arg0);
    PAD_STACK(8);

    gm_801B06B0(css, 0xE, temp_r31->x2, 0, temp_r31->x3, temp_r31->x4, 0,
                temp_r31->x6);
    if (temp_r31->x44 == 1) {
        gm_801BA938(temp_r31, 1, 4, 1);
    }
}
#pragma pop

void gm_801BAAD0(MinorScene* arg0)
{
    CSSData* temp_r3;
    struct EventData* temp_r31;

    temp_r31 = &gmMainLib_804D3EE0->unk_530;
    temp_r3 = gm_801A4284(arg0);
    if (temp_r3->pending_scene_change == 2) {
        gm_801A42F8(MJ_MENU);
        return;
    }
    gm_801B0730(temp_r3, &temp_r31->x2, NULL, &temp_r31->x3, &temp_r31->x4,
                NULL);
    temp_r31->x8 = -1;
    temp_r31->x9 = -1;
    temp_r31->xA = -1;
}

/// #gm_801BAB40

/// #gm_801BAC9C

/// #gm_801BAD70

/// #gm_801BB758

void gm_801BBA60_OnInit(void)
{
    struct EventData* temp_r6;
    int i;

    temp_r6 = &gmMainLib_804D3EE0->unk_530;
    gmMainLib_804D3EE0->unk_530.x0 = 0;
    temp_r6->x1 = 0;
    temp_r6->x2 = 0x21;
    temp_r6->x3 = 0;
    temp_r6->x4 = 0x78;
    temp_r6->unk_535 = 0;
    temp_r6->x6 = 0;
    temp_r6->x7 = 0;
    temp_r6->x8 = -1;
    temp_r6->x9 = -1;
    temp_r6->xA = -1;
    temp_r6->xB_0 = false;
    temp_r6->xB_1 = false;
    temp_r6->xB_2 = false;
    temp_r6->xB_3 = false;
    temp_r6->xB_4 = false;
    temp_r6->xB_5 = false;
    temp_r6->xB_6 = false;
    temp_r6->xC = 0;
    temp_r6->x10 = 0;
    temp_r6->x14 = 0;
    temp_r6->x18 = 0;
    temp_r6->x1C = 1.0F;
    temp_r6->x20 = 0;
    temp_r6->x24 = 0;
    temp_r6->x28 = 0;
    temp_r6->x2C = 0;
    temp_r6->x30 = 0;
    temp_r6->x34 = 0;
    temp_r6->x38 = 0x21;
    temp_r6->x3C = 0;
    temp_r6->x40 = 0;
    temp_r6->x44 = -1;
    temp_r6->x45 = 0;
    temp_r6->x48 = 0;

    for (i = 0; i < 4; i++) {
        temp_r6->x4C[i] = 0x21;
        temp_r6->x50[i] = 0;
    }
}

/// #gm_801BBB64

void gm_801BBEA8_OnLoad(void)
{
    struct EventData* temp_r30;
    struct gm_804D6900_t** temp_r29;
    u8 temp_r28;
    u8 temp_r3;
    PAD_STACK(8);

    temp_r30 = &gmMainLib_804D3EE0->unk_530;
    gm_801BA8FC();

    temp_r29 = gm_804D6900;
    temp_r28 = temp_r30->unk_535;
    temp_r30->x0 = 0;
    temp_r30->x1 = 0;
    temp_r30->x6 = gm_801677F0();
    temp_r30->x7 = 0;
    temp_r30->xB_0 = false;
    temp_r30->xB_1 = false;
    temp_r30->xB_2 = false;
    temp_r30->xB_3 = false;
    temp_r30->xB_4 = false;
    temp_r30->xB_5 = false;
    temp_r30->xB_6 = false;
    temp_r30->xC = 0;
    temp_r30->x10 = 0;
    temp_r30->x14 = 0;
    temp_r30->x18 = 0;
    temp_r30->x1C = 1.0F;
    temp_r30->x20 = 0;
    temp_r30->x24 = 0;
    temp_r30->x28 = 0;
    temp_r30->x2C = 0;
    temp_r30->x30 = 0;
    temp_r30->x34 = 0;
    temp_r30->x38 = 0x21;
    temp_r30->x3C = 0;
    temp_r30->x40 = 0;
    gm_801BBB64();
    if (*temp_r29[temp_r28]->x14 != 0x21) {
        gm_SetSceneMinor(1);
    }
}

void gm_801BBFE4_OnUnload(void) {}

void fn_801BBFE8(void)
{
    gm_801A4310();
    gm_801BC00C();
}

/// #gm_801BC00C

static u8 gm_803DF918[] = {
    0x00, 0x11, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
    0x0B, 0x0C, 0x0D, 0x24, 0x0F, 0x10, 0x01, 0x12, 0x13, 0x14, 0x15,
    0x1A, 0x17, 0x18, 0x19, 0x16, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20,
    0x21, 0x2F, 0x23, 0x0E, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B,
    0x2C, 0x2D, 0x2E, 0x22, 0x30, 0x31, 0x32,
};

extern gm_803DF94C_t gm_804D4330, gm_804D43B8, gm_804D4340, gm_804D4348,
    gm_804D4350, gm_804D4358, gm_804D4360, gm_804D4368, gm_804D4370,
    gm_804D4378, gm_804D4380, gm_804D4388, gm_804D4390, gm_804D4398,
    gm_804D4450, gm_804D43A8, gm_804D43B0, gm_804D4338, gm_804D43C0,
    gm_804D43C8, gm_804D43D0, gm_804D43D8, gm_804D4400, gm_804D43E8,
    gm_804D43F0, gm_804D43F8, gm_804D43E0, gm_804D4408, gm_804D4410,
    gm_804D4418, gm_804D4420, gm_804D4428, gm_804D4430, gm_804D4438,
    gm_804D44A8, gm_804D4448, gm_804D43A0, gm_804D4458, gm_804D4460,
    gm_804D4468, gm_804D4470, gm_804D4478, gm_804D4480, gm_804D4488,
    gm_804D4490, gm_804D4498, gm_804D44A0, gm_804D4440, gm_804D44B0,
    gm_804D44B8, gm_804D44C0;

gm_803DF94C_t* gm_803DF94C[] = {
    &gm_804D4330, &gm_804D43B8, &gm_804D4340, &gm_804D4348, &gm_804D4350,
    &gm_804D4358, &gm_804D4360, &gm_804D4368, &gm_804D4370, &gm_804D4378,
    &gm_804D4380, &gm_804D4388, &gm_804D4390, &gm_804D4398, &gm_804D4450,
    &gm_804D43A8, &gm_804D43B0, &gm_804D4338, &gm_804D43C0, &gm_804D43C8,
    &gm_804D43D0, &gm_804D43D8, &gm_804D4400, &gm_804D43E8, &gm_804D43F0,
    &gm_804D43F8, &gm_804D43E0, &gm_804D4408, &gm_804D4410, &gm_804D4418,
    &gm_804D4420, &gm_804D4428, &gm_804D4430, &gm_804D4438, &gm_804D44A8,
    &gm_804D4448, &gm_804D43A0, &gm_804D4458, &gm_804D4460, &gm_804D4468,
    &gm_804D4470, &gm_804D4478, &gm_804D4480, &gm_804D4488, &gm_804D4490,
    &gm_804D4498, &gm_804D44A0, &gm_804D4440, &gm_804D44B0, &gm_804D44B8,
    &gm_804D44C0
};

/// #gm_801BC488

void gm_801BC4F4(HSD_GObj* gobj)
{
    s32 temp_r0;
    u32 temp_r30;
    u32 temp_r29;
    struct EventData* temp_r28;
    u32 var_r27;
    int i;
    bool var_r25;
    u32 var_r4;
    PAD_STACK(8);

    temp_r30 = gmMainLib_804D3EE0->unk_530.unk_535;
    temp_r28 = &gmMainLib_804D3EE0->unk_530;
    temp_r28->xB_1 = true;
    temp_r29 = gmMainLib_8015CF5C(temp_r30);
    var_r25 = false;
    if (temp_r28->xB_6) {
        var_r4 = gm_8016AEDC();
        var_r4 += temp_r28->x34;
        if (temp_r30 == 0x31) {
            var_r4 = temp_r28->x34;
        }
        if (var_r4 > 0x34BBF) {
            var_r4 = 0x34BBF;
        }
        temp_r28->xC = var_r4;
        if (temp_r29 == 0 || var_r4 < temp_r29) {
            var_r25 = true;
        }
    } else {
        var_r27 = 0;
        for (i = 1; i < 6; i++) {
            if (Player_GetPlayerSlotType(i) != Gm_PKind_NA) {
                var_r27 += Player_GetKOsByPlayerIndex(0, i);
            }
        }
        if (temp_r30 == 0x1F) {
            var_r27 = Player_GetKOsByPlayerIndex(0, 1) - pl_8003FBFC(0);
        }
        if (var_r27 > -1) {
            var_r27 = -1;
        }
        temp_r28->xC = var_r27;
        if (var_r27 > temp_r29) {
            var_r25 = true;
        }
    }
    Player_80036844(0, 1);
    lbAudioAx_80028B90();
    gm_SetGameSpeed(1.0F);
    if (var_r25) {
        gm_8016B33C(2);
        gm_8016B350(0x9C40);
        gm_8016B364(0x144);
    } else {
        gm_8016B33C(2);
        gm_8016B364(0x145);
    }
    gm_8016B328();
    HSD_GObjPLink_80390228(gobj);
}

void gm_801BC670(void)
{
    struct EventData* temp_r31 = &gmMainLib_804D3EE0->unk_530;
    struct gm_804D6900_x4_t* temp_r30 = gm_804D6900[0]->x4;
    PAD_STACK(0x18);

    temp_r31->xB_2 = true;
    temp_r31->x10 = 0x78 - temp_r30->x4;
    temp_r31->x2C = gm_8016AEEC();
    temp_r31->x30 = gm_8016AEFC();
    if (temp_r31->x2C < temp_r30->x0) {
        temp_r31->x2C = temp_r30->x0;
        temp_r31->x30 = 0;
    }
    if (Player_80036394(0) == 7) {
        temp_r31->x38 = 0x13;
    } else {
        temp_r31->x38 = 0x21;
    }
    temp_r31->x34 += gm_8016AEDC();
    Player_80036844(0, 1);
    lbAudioAx_80028B90();
    gm_SetGameSpeed(1.0F);
    gm_8016B33C(8);
    gm_8016B328();
}

void gm_801BC754(HSD_GObj* gobj)
{
    lbl_8046B6A0_t* temp_r3;
    lbl_8046B6A0_t* temp_r3_2;
    bool var_r0;
    bool var_r0_2;
    int count;
    int i;
    struct EventData* temp_r29;
    struct EventData* temp_r28;
    struct EventData* temp_r28_2;
    struct EventData* temp_r28_3;

    PAD_STACK(0x48);

    temp_r29 = &gmMainLib_804D3EE0->unk_530;
    switch (gm_8016AE38()->x24C8.x0_0) {
    case 1:
        count = 0;
        temp_r28 = &gmMainLib_804D3EE0->unk_530;
        for (i = 1; i < 6; i++) {
            if (Player_GetPlayerSlotType(i) != Gm_PKind_NA &&
                Player_GetStocks(i) != 0)
            {
                count += 1;
            }
        }
        if (temp_r28->xB_3) {
            count += gm_80169384();
        }
        if (count == 0) {
            gm_801BC4F4(gobj);
            return;
        }
        if (Player_GetP1Stock() <= 0) {
            gmMainLib_804D3EE0->unk_530.xB_1 = false;
            lbAudioAx_80028B90();
            gm_SetGameSpeed(1.0F);
            gm_8016B33C(6);
            gm_8016B364(0x148);
            gm_8016B378(0x28);
            gm_8016B328();
            HSD_GObjPLink_80390228(gobj);
            return;
        }
        temp_r28_2 = &gmMainLib_804D3EE0->unk_530;
        temp_r3 = gm_8016AE38();
        if (temp_r28_2->xB_0) {
            var_r0 = false;
        } else if (temp_r3->x24C8.x0_6 && gm_8016AEEC() == 0 &&
                   gm_8016AEFC() == 0x3B)
        {
            var_r0 = true;
        } else {
            var_r0 = false;
        }
        if (var_r0) {
            gmMainLib_804D3EE0->unk_530.xB_1 = false;
            lbAudioAx_80028B90();
            gm_SetGameSpeed(1.0F);
            gm_8016B33C(6);
            gm_8016B364(0x148);
            gm_8016B378(0x28);
            gm_8016B328();
            HSD_GObjPLink_80390228(gobj);
        }
        break;
    case 0:
    case 2:
        temp_r28_3 = &gmMainLib_804D3EE0->unk_530;
        temp_r3_2 = gm_8016AE38();
        if (temp_r28_3->xB_0) {
            var_r0_2 = false;
        } else if (temp_r3_2->x24C8.x0_6 && gm_8016AEEC() == 0 &&
                   gm_8016AEFC() == 0x3B)
        {
            var_r0_2 = true;
        } else {
            var_r0_2 = false;
        }
        if (var_r0_2) {
            if (temp_r29->x7 == gm_801BC488()) {
                gm_801BC4F4(gobj);
                return;
            }
            gmMainLib_804D3EE0->unk_530.xB_1 = false;
            lbAudioAx_80028B90();
            gm_SetGameSpeed(1.0F);
            gm_8016B33C(6);
            gm_8016B364(0x148);
            gm_8016B378(0x28);
            gm_8016B328();
            HSD_GObjPLink_80390228(gobj);
        }
        break;
    }
}

void gm_801BC9E8(HSD_GObj* gobj)
{
    lbl_8046B6A0_t* temp_r3;
    bool var_r0;
    struct EventData* temp_r30_2;
    struct gm_804D6900_x4_t* temp_r30 =
        gm_804D6900[gmMainLib_804D3EE0->unk_530.unk_535]->x4;
    u32 coins = Player_GetCoins(0);
    PAD_STACK(0x28);

    if (coins >= temp_r30->x0) {
        gm_801BC4F4(gobj);
        return;
    }
    temp_r30_2 = &gmMainLib_804D3EE0->unk_530;
    temp_r3 = gm_8016AE38();
    if (temp_r30_2->xB_0) {
        var_r0 = false;
    } else if (temp_r3->x24C8.x0_6 && gm_8016AEEC() == 0 &&
               gm_8016AEFC() == 0x3B)
    {
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (var_r0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
    }
}

void gm_801BCAF0(HSD_GObj* gobj)
{
    HSD_GObj* temp_r3;
    lbl_8046B6A0_t* temp_r3_2;
    s32 var_r0;
    s32 var_r0_2;
    struct EventData* temp_r30;
    s32 var_r30;
    s32 var_r29;
    PAD_STACK(0x28);

    var_r30 = 1;
    var_r29 = 0;
    do {
        if ((Player_GetStocks(var_r30) <= 0) &&
            (temp_r3 = Player_GetEntity(var_r30), ((temp_r3 == NULL) == 0)))
        {
            if (ftLib_800872A4(temp_r3) == FTKIND_SEAK) {
                var_r0 = 1;
            } else {
                Player_SetStocks(var_r30, 1);
                gm_8016F00C(var_r30);
                goto block_6;
            }
        } else {
        block_6:
            var_r0 = 0;
        }
        if (var_r0 != 0) {
            var_r29 += 1;
        }
        var_r30 += 1;
    } while (var_r30 < 3);
    if (var_r29 == 2) {
        gm_801BC4F4(gobj);
        return;
    }
    if (Player_GetP1Stock() <= 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
        return;
    }
    temp_r30 = &gmMainLib_804D3EE0->unk_530;
    temp_r3_2 = gm_8016AE38();
    if (temp_r30->xB_0) {
        var_r0_2 = 0;
    } else if (temp_r3_2->x24C8.x0_6 && gm_8016AEEC() == 0 &&
               gm_8016AEFC() == 0x3B)
    {
        var_r0_2 = 1;
    } else {
        var_r0_2 = 0;
    }
    if (var_r0_2 != 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
    }
}

/// #gm_801BCC9C

void gm_801BCF20(HSD_GObj* gobj)
{
    gm_801BCC9C(gobj);
}

void gm_801BCF40(HSD_GObj* gobj)
{
    lbl_8046B6A0_t* temp_r3;
    bool var_r0;
    struct EventData* temp_r31;
    PAD_STACK(0x20);

    if (Player_GetP1Stock() <= 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
        return;
    }
    temp_r31 = &gmMainLib_804D3EE0->unk_530;
    temp_r3 = gm_8016AE38();
    if (temp_r31->xB_0) {
        var_r0 = false;
    } else if (temp_r3->x24C8.x0_6 && gm_8016AEEC() == 0 &&
               gm_8016AEFC() == 0x3B)
    {
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (var_r0) {
        gm_801BC4F4(gobj);
    }
}

/// #gm_801BD028

void gm_801BD164(HSD_GObj* gobj)
{
    lbl_8046B6A0_t* temp_r3;
    s32 temp_r30;
    s32 var_r0;
    struct EventData* temp_r30_2;
    PAD_STACK(0x28);

    if (Player_GetStocks(2) <= 0) {
        temp_r30 = Player_GetKOsByPlayerIndex(1, 2);
        if (Player_GetKOsByPlayerIndex(0, 2) > temp_r30) {
            gm_801BC4F4(gobj);
        } else {
            gmMainLib_804D3EE0->unk_530.xB_1 = false;
            lbAudioAx_80028B90();
            gm_SetGameSpeed(1.0F);
            gm_8016B33C(6);
            gm_8016B364(0x148);
            gm_8016B378(0x28);
            gm_8016B328();
            HSD_GObjPLink_80390228(gobj);
        }
    }
    if (Player_GetP1Stock() <= 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
        return;
    }
    temp_r30_2 = &gmMainLib_804D3EE0->unk_530;
    temp_r3 = gm_8016AE38();
    if (temp_r30_2->xB_0) {
        var_r0 = 0;
    } else if (temp_r3->x24C8.x0_6 && gm_8016AEEC() == 0 &&
               gm_8016AEFC() == 0x3B)
    {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
    }
}

void gm_801BD30C(HSD_GObj* gobj)
{
    lbl_8046B6A0_t* temp_r3;
    s32 var_r0;
    struct EventData* temp_r31;
    PAD_STACK(0x20);

    if (Player_GetStocks(1) <= 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
        return;
    }
    if (Player_GetP1Stock() <= 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
        return;
    }
    temp_r31 = &gmMainLib_804D3EE0->unk_530;
    temp_r3 = gm_8016AE38();
    if (temp_r31->xB_0) {
        var_r0 = 0;
    } else if (temp_r3->x24C8.x0_6 && gm_8016AEEC() == 0 &&
               gm_8016AEFC() == 0x3B)
    {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        gm_801BC4F4(gobj);
    }
}

void gm_801BD44C(HSD_GObj* gobj)
{
    gm_801BCC9C(gobj);
}

/// #gm_801BD46C

void gm_801BD658(HSD_GObj* gobj)
{
    lbl_8046B6A0_t* temp_r3;
    bool var_r0;
    s32 var_r30;
    int i;
    struct EventData* temp_r28;
    struct EventData* temp_r28_2;
    PAD_STACK(0x28);

    var_r30 = 0;
    temp_r28 = &gmMainLib_804D3EE0->unk_530;
    for (i = 1; i < 6; i++) {
        if (Player_GetPlayerSlotType(i) != Gm_PKind_NA &&
            Player_GetStocks(i) != 0)
        {
            var_r30 += 1;
        }
    }
    if (temp_r28->xB_3) {
        var_r30 += gm_80169384();
    }
    if (var_r30 == 0) {
        gm_801BC4F4(gobj);
        ifStock_802FA2D0(0);
        return;
    }
    if (Player_GetP1Stock() <= 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0f);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
        return;
    }
    temp_r28_2 = &gmMainLib_804D3EE0->unk_530;
    temp_r3 = gm_8016AE38();
    if (temp_r28_2->xB_0) {
        var_r0 = false;
    } else if (temp_r3->x24C8.x0_6 && gm_8016AEEC() == 0 &&
               gm_8016AEFC() == 0x3B)
    {
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (var_r0 != 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0f);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
    }
}

void gm_801BD7FC(HSD_GObj* gobj)
{
    lbl_8046B6A0_t* temp_r3;
    bool var_r0;
    struct EventData* temp_r31;
    PAD_STACK(0x20);

    if (Player_GetStocks(1) <= 0) {
        gm_801BC4F4(gobj);
        return;
    }
    if (Player_GetP1Stock() <= 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
        return;
    }
    temp_r31 = &gmMainLib_804D3EE0->unk_530;
    temp_r3 = gm_8016AE38();
    if (temp_r31->xB_0) {
        var_r0 = false;
    } else if (temp_r3->x24C8.x0_6 && gm_8016AEEC() == 0 &&
               gm_8016AEFC() == 0x3B)
    {
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (var_r0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
    }
}

void gm_801BD93C(HSD_GObj* gobj)
{
    lbl_8046B6A0_t* temp_r3;
    bool var_r0;
    struct EventData* temp_r31;
    PAD_STACK(0x38);

    if (Player_GetStocks(2) <= 0) {
        gm_801BC4F4(gobj);
        return;
    }
    if (Player_GetStocks(1) <= 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
        return;
    }
    if (Player_GetP1Stock() <= 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
        return;
    }
    temp_r31 = &gmMainLib_804D3EE0->unk_530;
    temp_r3 = gm_8016AE38();
    if (temp_r31->xB_0) {
        var_r0 = false;
    } else if (temp_r3->x24C8.x0_6 && gm_8016AEEC() == 0 &&
               gm_8016AEFC() == 0x3B)
    {
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (var_r0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
    }
}

void gm_801BDAD4(HSD_GObj* gobj)
{
    gm_801BCC9C(gobj);
}

void gm_801BDAF4(HSD_GObj* arg0)
{
    lbl_8046B6A0_t* temp_r3;
    s32 temp_r30_2;
    s32 temp_r31;
    bool var_r0;
    struct EventData* temp_r30;
    PAD_STACK(0x10);

    temp_r30 = &gmMainLib_804D3EE0->unk_530;
    temp_r3 = gm_8016AE38();
    if (temp_r30->xB_0) {
        var_r0 = false;
    } else if (temp_r3->x24C8.x0_6 && gm_8016AEEC() == 0 &&
               gm_8016AEFC() == 0x3B)
    {
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (var_r0 != 0) {
        temp_r30_2 = pl_8003FC20(1);
        temp_r31 = Player_GetKOsByPlayerIndex(0, 1);
        if (temp_r31 - pl_8003FBFC(0) > temp_r30_2) {
            gm_801BC4F4(arg0);
            return;
        }
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0f);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(arg0);
    }
}

void gm_801BDC08(HSD_GObj* arg0)
{
    lbl_8046B6A0_t* temp_r3;
    bool var_r0;
    struct EventData* temp_r31;
    PAD_STACK(0x20);

    if (Ground_801C1D84() != 0U) {
        gm_801BC4F4(arg0);
        return;
    }
    if (Player_GetP1Stock() <= 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0f);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(arg0);
        return;
    }
    temp_r31 = &gmMainLib_804D3EE0->unk_530;
    temp_r3 = gm_8016AE38();
    if (temp_r31->xB_0) {
        var_r0 = false;
    } else if (temp_r3->x24C8.x0_6 && gm_8016AEEC() == 0 &&
               gm_8016AEFC() == 0x3B)
    {
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (var_r0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0f);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(arg0);
    }
}

void gm_801BDD44(HSD_GObj* arg0)
{
    lbl_8046B6A0_t* temp_r3;
    bool var_r0;
    struct EventData* temp_r31;
    PAD_STACK(0x20);

    if (Player_GetStocks(2) <= 0 && Player_GetStocks(3) <= 0) {
        gm_801BC4F4(arg0);
        return;
    }
    if (Player_GetP1Stock() <= 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0f);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(arg0);
        return;
    }
    temp_r31 = &gmMainLib_804D3EE0->unk_530;
    temp_r3 = gm_8016AE38();
    if (temp_r31->xB_0) {
        var_r0 = false;
    } else if (temp_r3->x24C8.x0_6 && gm_8016AEEC() == 0 &&
               gm_8016AEFC() == 0x3B)
    {
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (var_r0 != 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0f);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(arg0);
    }
}

/// #gm_801BDE94

void gm_801BE37C(HSD_GObj* gobj)
{
    gm_801BCC9C(gobj);
}

/// #gm_801BE39C

void gm_801BE618(HSD_GObj* gobj)
{
    gm_801BCC9C(gobj);
}

/// #gm_801BE638

void gm_801BEA10(int arg0)
{
    Player_SetPlayerAndEntityCpuType(
        arg0, gm_804D6900[gmMainLib_804D3EE0->unk_530.unk_535]->xC->x16);
}

void gm_801BEA4C(int arg0)
{
    gm_801BEA10(arg0);
}

void gm_801BEA88(int arg0)
{
    PAD_STACK(0x10);
    gm_801BEA10(arg0);
    if (arg1 == 0) {
        Player_SetModelScale(arg0, 2.0F);
    }
}

/// #gm_801BEA88

void gm_801BEAF0(int arg0)
{
    gm_801BEA10(arg0);
}

void gm_801BEB2C(int arg0)
{
    gm_801BEA10(arg0);
}

void gm_801BEB68(int arg0)
{
    gmMainLib_804D3EE0->unk_530.x18 = arg0;
}

void gm_801BEB74(u8 arg0)
{
    gmMainLib_804D3EE0->unk_530.unk_535 = arg0;
}

u8 gm_801BEB80(void)
{
    return gmMainLib_804D3EE0->unk_530.unk_535;
}

bool gm_801BEB8C(u8 arg0)
{
    return gm_804D6900[arg0]->x8->x1_0;
}

u8 gm_801BEBA8(u8 arg0)
{
    return gm_803DF918[arg0];
}

u8 gm_801BEBC0(u8 arg0)
{
    u8* tmp = gm_803DF918;
    u8 i;
    for (i = 0; i < 0x33; i++) {
        if (arg0 == tmp[i]) {
            break;
        }
    }
    return i;
}

/// #gm_801BEBF8

UNK_T gm_801BEC54(void)
{
    struct gm_804D6900_t* temp_r3;
    temp_r3 = gm_804D6900[gmMainLib_804D3EE0->unk_530.unk_535];
    if (temp_r3 == NULL) {
        return NULL;
    }
    return temp_r3->x4;
}

void gm_801BEC80(MinorScene* arg)
{
    gm_801A42E8(1);
    gm_801A42D4();
}

void gm_801BECA8(MinorScene* arg)
{
    lb_8001C550();
    lb_8001D164(0);
}

void gm_801BECD0(MinorScene* arg)
{
    gm_80172898(4);
    if (gm_80173754(1, 0) == 0) {
        gm_801A42E8(1);
        gm_801A42D4();
    }
}

void gm_801BED14(MinorScene* arg)
{
    gm_801A42E8(1);
    gm_801A42D4();
}

void gm_801BED3C(MinorScene* arg0)
{
    CSSData* temp_r31 = gm_801A427C(arg0);
    temp_r31->data = *gm_801A5244();

    gm_80164F18();
    if (temp_r31->match_type & 1) {
        gm_80164A0C(7);
    }
}

/// #gm_801BEDA8

void gm_801BEE58(MinorScene* arg0)
{
    SSSData* var_r3 = gm_801A427C(arg0);
    var_r3->data = gmMainLib_804D3EE0->unk_590;
}

/// #gm_801BEE9C

void gm_801BEF84(MinorScene* arg)
{
    lbMthp_8001F800();
}

/* 49C178 */ static u8 gm_8049C178[16];

#pragma push
#pragma dont_inline on
void gm_801BEFA4(s8 arg0)
{
    gm_8049C178[0] = arg0;
}
#pragma pop

int gm_801BEFB0(void)
{
    return gm_8049C178[0];
}

#pragma push
#pragma dont_inline on
void gm_801BEFC0(int arg0)
{
    gm_8049C178[1] = arg0;
}
#pragma pop

u8 gm_801BEFD0(void)
{
    return M2C_FIELD(&gm_8049C178, u8*, 1);
}

void gm_801BEFE0(s8 arg0)
{
    M2C_FIELD(&gm_8049C178, s8*, 0xA) = arg0;
}

u8 gm_801BEFF0(void)
{
    return M2C_FIELD(&gm_8049C178, u8*, 0xA);
}

void gm_801BF000(s8 arg0)
{
    M2C_FIELD(&gm_8049C178, s8*, 9) = arg0;
}

int gm_801BF010(void)
{
    return M2C_FIELD(&gm_8049C178, u8*, 9);
}

void gm_801BF020(s8 arg0)
{
    M2C_FIELD(&gm_8049C178, s8*, 8) = arg0;
}

u8 gm_801BF030(void)
{
    return M2C_FIELD(&gm_8049C178, u8*, 8);
}

void gm_801BF040(s8 arg0)
{
    M2C_FIELD(&gm_8049C178, s8*, 2) = arg0;
}

int gm_801BF050(void)
{
    return M2C_FIELD(&gm_8049C178, u8*, 2);
}

void gm_801BF060(MinorScene* arg0)
{
    int* temp_r3 = gm_801A4284(arg0);
    if (g_debugLevel >= 3) {
        if (*temp_r3 & 0x100) {
            gm_801A42E8(0xE);
            gm_801A42D4();
        } else if (*temp_r3 & 0x1000) {
            gm_801A42E8(1);
            gm_801A42D4();
        } else if (*temp_r3 & 0x400) {
            gm_801A42E8(7);
            gm_801A42D4();
        } else if (*temp_r3 & 0x800) {
            gm_801A42E8(6);
            gm_801A42D4();
        }
    } else if (*temp_r3 & 0x1000) {
        gm_80173EEC();
        gm_80172898(0x100);
        if (gm_80173754(1, 0) == 0) {
            gm_801A42E8(1);
        }
        gm_801A42D4();
    }
}

/// #gm_801BF128

/// #gm_801BF3F8

void gm_801BF4DC(MinorScene* arg0)
{
    StartMeleeData* temp_r31;
    VsModeData* temp_r30;
    int i;

    temp_r30 = &gmMainLib_804D3EE0->unk_1710;
    temp_r31 = gm_801A427C(arg0);
    gm_80167BC8(temp_r30);
    gm_8016F088(temp_r31);
    gm_80168FC4();
    gm_80167A64(&temp_r31->rules);

    temp_r31->rules.x0_0 = gm_801BF6B8();
    temp_r31->rules.x0_6 = false;
    temp_r31->rules.x10 = 0;
    temp_r31->rules.x1_0 = false;
    temp_r31->rules.x1_2 = true;
    temp_r31->rules.x1_3 = true;
    temp_r31->rules.x2_4 = true;
    temp_r31->rules.x7 = 0;
    temp_r31->rules.x44 = gm_80183218;
    temp_r31->rules.x34 = 1.0F;
    temp_r31->rules.xE = (u16) gm_801BF694();
    gm_80167A14(temp_r31->players);

    for (i = 0; i < 4; i++) {
        CharacterKind kind = gm_801BF648(i);
        temp_r31->players[i].c_kind = kind;
        temp_r31->players[i].color = gm_801BF670(i);
        temp_r31->players[i].slot_type = Gm_PKind_Cpu;
        temp_r31->players[i].cpu_level = 9;
        temp_r31->players[i].xE = 4;
        temp_r31->players[i].xC_b1 = false;
        if (temp_r31->rules.x0_0 == 1) {
            temp_r31->players[i].stocks = 0x63;
        }
    }
}

void gm_801BF634(s32 arg0, s8 character_kind)
{
    gm_8049E548.c_kind[arg0] = character_kind;
}

s8 gm_801BF648(s32 arg0)
{
    return gm_8049E548.c_kind[arg0];
}

void gm_801BF65C(s32 arg0, s8 arg1)
{
    gm_8049E548.x4[arg0] = arg1;
}

u8 gm_801BF670(s32 arg0)
{
    return gm_8049E548.x4[arg0];
}

void gm_801BF684(s16 arg0)
{
    gm_8049E548.unk_C = arg0;
}

u8 gm_801BF694(void)
{
    return gm_8049E548.unk_C;
}

void gm_801BF6A8(s8 arg0)
{
    gm_8049E548.unk_A = arg0;
}

u8 gm_801BF6B8(void)
{
    return gm_8049E548.unk_A;
}

void gm_801BF6C8(s8 arg0)
{
    gm_8049E548.unk_8 = arg0;
}

int gm_801BF6D8(void)
{
    return gm_8049E548.unk_8;
}

void gm_801BF6E8(s8 arg0)
{
    gm_8049E548.unk_9 = arg0;
}

int gm_801BF6F8(void)
{
    return gm_8049E548.unk_9;
}

void gm_801BF708(s8 arg0)
{
    gm_8049E548.unk_E = arg0;
}

u8 gm_801BF718(void)
{
    return gm_8049E548.unk_E;
}

extern u8 un_804D6F3C[8];
extern u8 un_804D6FD8[8];

void gm_801BF728(MinorScene* arg)
{
    s32 temp_r31;
    s32 temp_r31_2;
    PAD_STACK(4);

    un_804D6F3C[1] = 1;
    un_804D6F3C[3] = 1;
    vi0102_8031D020(0xE, HSD_Randi(4));
    temp_r31 = HSD_Randi(4);
    un_8031D9E4(0xE, HSD_Randi(4), temp_r31);
    un_804D6F84[4] = HSD_Randi(0x1B);
    un_804D6F84[5] = HSD_Randi(0x1B);
    un_804D6F84[6] = HSD_Randi(0x1B);
    temp_r31_2 = HSD_Randi(4);
    un_8031E110(0xE, HSD_Randi(4), temp_r31_2);
    un_804D6FD8[0] = 0xE;
    un_804D6FD8[1] = HSD_Randi(4);
    un_8031F980(0xE, HSD_Randi(4));
    un_803204B0(0xE, HSD_Randi(4));
    gm_801BEFA4(8);
    gm_801BEFC0(HSD_Randi(4));
}

void gm_801BF834(MinorScene* arg)
{
    gm_801A42E8(0);
    gm_801A42D4();
}

void gm_801BF85C(MinorScene* arg)
{
    PreloadCacheScene* temp_r31 = lbDvd_8001822C();
    PAD_STACK(4);
    lbDvd_800174BC();
    temp_r31->is_heap_persistent[1] = 0;
    lbDvd_80018254();
}

void gm_801BF898(MinorScene* arg)
{
    lbMthp_8001F800();
}

void gm_801BF8B8(MinorScene* arg)
{
    lbMthp_8001F800();
}

void gm_801BF8D8(MinorScene* arg)
{
    lbMthp_8001F800();
}

void gm_801BF8F8(MinorScene* arg0)
{
    int* val = gm_801A427C(arg0);
    *val = 1;
}

void gm_801BF920(MinorScene* arg0)
{
    gm_801A4284(arg0);
    gm_801A42F8(MJ_BOOT);
}
