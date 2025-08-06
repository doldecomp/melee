#include "gmhomerun.h"

#include "gm_1B03.static.h"

#include "gm_unsplit.h"
#include "gmvsdata.h"

#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/random.h>
#include <melee/db/db.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmcamera.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/gmresult.h>
#include <melee/gm/gmresultplayer.h>
#include <melee/gm/gmtou.h>
#include <melee/gm/gmvsmelee.h>
#include <melee/gm/types.h>
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
#include <melee/un/un_2FC9.h>
#include <melee/vi/types.h>
#include <melee/vi/vi0102.h>
#include <melee/vi/vi0402.h>
#include <melee/vi/vi0501.h>
#include <melee/vi/vi1101.h>
#include <melee/vi/vi1201v1.h>

MinorScene gm_803DF198_MinorScenes[] = {
    {
        0,
        3,
        0,
        (void (*)(MinorScene*)) gm_801B98E8,
        gm_801B999C,
        {
            MN_CSS,
            &gm_804807B0,
            &gm_804807B0,
        },
    },
    {
        1,
        3,
        0,
        gm_801B9A3C,
        gm_801B9DD8,
        {
            MN_VS,
            &gm_80480530,
            &gm_80479D98,
        },
    },
    { -1 },
};

extern VsModeData gm_80497618;
extern u8 gm_804D68F8;
extern u8 gm_804D68F9;

/// #gm_801B98E8

void gm_801B999C(MinorScene* scene)
{
    VsModeData* vs = &gm_80497618;
    CSSData* temp_r3;

    temp_r3 = gm_801A4284(scene);
    if (temp_r3->pending_scene_change == 2) {
        gm_801A42F8(MJ_MENU);
        return;
    }
    gm_80167A14(vs->data.players);
    gm_801B0730(temp_r3, &vs->data.players[0].c_kind, NULL,
                &vs->data.players[0].color, &vs->data.players[0].xA, NULL);
    vs->data.players[1].c_kind = 0x1F;
    vs->data.players[1].xE = 0xF;
    vs->data.players[1].x1C = 1.0f;
    vs->data.players[1].slot_type = 1;
    vs->data.players[1].stocks = 1;
    vs->data.players[1].team = 1;
}

#pragma push
#pragma dont_inline on
void gm_801B9A3C(MinorScene* arg0)
{
    StartMeleeData* data;
    VsModeData* vs = &gm_80497618;
    int i;

    data = gm_801A427C(arg0);
    gm_80167A64(&data->rules);

    data->rules = vs->data.rules;

    data->rules.xE = 0x54;
    data->rules.x0_0 = 1;
    data->rules.x0_6 = true;
    data->rules.x1_0 = true;
    data->rules.x4_2 = false;
    data->rules.x4_4 = false;

    data->rules.x8 = 0;
    data->rules.xB = -1;
    data->rules.x10 = 0xA;
    data->rules.x34 = 1.0f;
    data->rules.x30 = 1.0f;

    data->rules.x5_0 = true;
    data->rules.x1_3 = true;
    data->rules.x44 = gm_80181998;

    data->rules.x3_3 = true;
    data->rules.x3_2 = true;
    data->rules.x7 = 9;

    for (i = 0; i < 6; i++) {
        data->players[i] = vs->data.players[i];
        data->players[i].xC_b1 = false;
        data->players[i].xD_b3 = true;
    }

    gm_801B0620(&data->players[0], vs->data.players[0].c_kind,
                vs->data.players[0].color, 1, gm_804D68F8);
    data->players[0].xD_b2 = true;
    gm_8016F088(data);
    gm_80181A00(data->players[0].c_kind, (u8) data->players[0].xA);
    gm_80180B18();
}
#pragma pop

void gm_801B9DD8(MinorScene* arg0)
{
    u32 temp_r31;
    s32* temp_r3_2;
    u8 temp_r30;
    MatchExitInfo* temp_r3;

    temp_r3 = gm_801A4284(arg0);
    gm_80162968(temp_r3->match_end.frame_count / 60);
    gm_8016247C(temp_r3->match_end.player_standings[0].xE);
    gm_80180BA0();
    if (temp_r3->match_end.result == 8) {
        gm_SetScenePendingMinor(1);
        return;
    }
    temp_r30 =
        gm_80164024(temp_r3->match_end.player_standings[0].character_kind);
    temp_r31 = gm_80180AE4();
    if (gm_801734D0(temp_r31) != 0x148) {
        gm_80164504();
    }
    temp_r3_2 = gmMainLib_8015D084(temp_r30);
    if (temp_r31 > *temp_r3_2) {
        *temp_r3_2 = temp_r31;
    }
    gm_80173B30(temp_r31);
    gm_80173EEC();
    gm_80172898(8);
    if (gm_80173754(0x20, gm_804D68F8) == 0) {
        gm_SetScenePendingMinor(0);
    }
}

void gm_801B9EB8_OnInit(void)
{
    VsModeData* data = &gm_80497618;
    gm_80167B50(data);
}

void gm_801B9EE4_OnLoad(void)
{
    gm_804D68F8 = gm_801677F0();
    gm_804D68F9 = 0;
}
