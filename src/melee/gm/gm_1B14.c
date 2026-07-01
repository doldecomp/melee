#include "gm_1B14.h"

#include "gm_1B03.h"
#include "gm_1B0FF.h"
#include "gmvsdata.h"

#include "gm/gm_1A3F.h"
#include "gm/gm_1BA8.h"
#include "gm/gmmovieend.h"
#include "melee/gm/gm_unsplit.h"
#include "melee/gm/gmcamera.h"
#include "melee/gm/gmmain_lib.h"
#include "melee/gm/gmresult.h"
#include "melee/gm/gmtoulib.h"
#include "melee/gm/gmvsmelee.h"
#include "melee/gm/types.h"
#include "melee/lb/lbaudio_ax.h"
#include "melee/lb/lbcardgame.h"
#include "melee/lb/lbcardnew.h"
#include "melee/lb/lbdvd.h"
#include "melee/lb/lbsnap.h"
#include "melee/lb/lbtime.h"
#include "melee/lb/types.h"
#include "melee/mn/types.h"

#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/random.h>

/* 4D68C0 */ static u8 gm_804D68C0;
/* 4D68C1 */ static u8 gm_804D68C1;
/* 4D68C8 */ static UNK_T gm_804D68C8[1];

GameScene gm_803DD9A0_Scenes[] = {
    {
        0x00,
        0x03,
        0,
        gm_801B14A0,
        gm_801B14DC,
        {
            GS_CSS,
            &gm_804807B0,
            &gm_804807B0,
        },
    },
    {
        0x01,
        0x03,
        0,
        gm_801B1514,
        gm_801B154C,
        {
            GS_SSS,
            &gm_80480668,
            &gm_80480668,
        },
    },
    {
        0x02,
        0x03,
        0,
        gm_801B1588,
        gm_801B15C8,
        {
            GS_VS,
            &gm_80480530,
            &gm_80479D98,
        },
    },
    {
        0x03,
        0x03,
        0,
        gm_801B1648,
        gm_801B1688,
        {
            GS_SUDDEN_DEATH,
            &gm_80480530,
            &gm_8047E2A4,
        },
    },
    {
        0x04,
        0x03,
        0,
        gm_801B16A8,
        gm_801B16C8,
        {
            GS_RESULTS,
            &gm_8047C020,
            NULL,
        },
    },
    {
        0x80,
        0x02,
        0,
        gm_801BFA6C,
        NULL,
        {
            GS_APPROACH,
            &gm_804D6860,
            &gm_804D6860,
        },
    },
    {
        0x81,
        0x02,
        0,
        gm_801BFABC,
        gm_801A6254,
        {
            GS_VS,
            &gm_80480530,
            &gm_80479D98,
        },
    },
    {
        0xC0,
        0x02,
        0,
        gm_801BFCFC,
        gm_801A6308,
        {
            GS_PRIZE_INTERFACE,
            &un_804A1F48,
            NULL,
        },
    },
    { 0xFF },
};

GameScene gm_803DDA78_Scenes[] = {
    {
        0x01,
        0x02,
        0,
        gm_801B13B8,
        NULL,
        {
            GS_VS,
            &gm_80480530,
            &gm_80479D98,
        },
    },
    {
        0x03,
        0x02,
        0,
        gm_801B16A8,
        NULL,
        {
            GS_RESULTS,
            &gm_8047C020,
            NULL,
        },
    },
    { 0xFF },
};

GameScene gm_803DDAC0_Scenes[] = {
    {
        0x00,
        0x03,
        0,
        gm_801B1724,
        NULL,
        {
            GS_TOU_SETUP,
            NULL,
            NULL,
        },
    },
    {
        0x01,
        0x03,
        0,
        NULL,
        NULL,
        {
            GS_TOU_BRACKET,
            NULL,
            NULL,
        },
    },
    {
        0x02,
        0x03,
        0,
        NULL,
        NULL,
        {
            GS_TOU_ALT,
            NULL,
            NULL,
        },
    },
    {
        0x03,
        0x03,
        0,
        gm_801B174C,
        gm_801B1788,
        {
            GS_SSS,
            gm_8048BD20,
            gm_8048BD20,
        },
    },
    {
        0x04,
        0x03,
        0,
        gm_801B1810,
        gm_801B1834,
        {
            GS_VS,
            &gm_804876D8,
            &gm_80487810,
        },
    },
    {
        0x05,
        0x03,
        0,
        gm_801B18D4,
        gm_801B1A2C,
        {
            GS_SUDDEN_DEATH,
            &gm_804876D8,
            gm_8048BE68,
        },
    },
    {
        0x06,
        0x03,
        0,
        gm_801B1A84,
        gm_801B1AD4,
        {
            GS_RESULTS,
            gm_80489A98,
            NULL,
        },
    },
    { 0xFF },
};

GameScene gm_803DDB80_Scenes[] = {
    {
        0x00,
        0x03,
        0,
        gm_801B1B74,
        gm_801B1C24,
        {
            GS_CSS,
            &gm_8048E230,
            &gm_8048E230,
        },
    },
    {
        0x01,
        0x03,
        0,
        gm_801B1EB8,
        gm_801B1EEC,
        {
            GS_SSS,
            &gm_8048E378,
            &gm_8048E378,
        },
    },
    {
        0x02,
        0x03,
        0,
        gm_801B1F70,
        gm_801B2204,
        {
            GS_TRAINING_MODE,
            &gm_8048E4C0,
            gm_8048E5F8,
        },
    },
    { 0xFF },
};

GameScene gm_CameraModeScenes[] = {
    {
        0x00,
        0x03,
        0,
        gm_801B24B4,
        gm_801B2510,
        {
            GS_CAMERA_VS,
            gm_804D68C8,
            gm_804D68C8,
        },
    },
    {
        0x01,
        0x03,
        0,
        gm_801B254C,
        gm_801B25D4,
        {
            GS_CSS,
            &gm_804807B0,
            &gm_804807B0,
        },
    },
    {
        0x02,
        0x03,
        0,
        gm_801B26AC,
        gm_801B2704,
        {
            GS_SSS,
            &gm_80480668,
            &gm_80480668,
        },
    },
    {
        0x03,
        0x03,
        0,
        gm_PrepCameraModeVSScene,
        gm_801B2AF8,
        {
            GS_VS,
            &gm_80480530,
            &gm_80479D98,
        },
    },
    { 0xFF },
};

void gm_801B14A0(GameScene* arg0)
{
    gm_801A5618(arg0, gm_801A5244(), 0);
}

void gm_801B14DC(GameScene* arg0)
{
    gm_801A5680(arg0, gm_801A5244());
}

void gm_801B1514(GameScene* arg0)
{
    gm_801A5754(arg0, gm_801A5244());
}

void gm_801B154C(GameScene* arg0)
{
    gm_801A57A8(arg0, gm_801A5244(), 0);
}

void gm_801B1588(GameScene* arg0)
{
    gm_801A583C(arg0, gm_801A5244(), NULL, NULL);
}

void gm_801B15C8(GameScene* arg0)
{
    s32 i;
    MatchExitInfo* mei;

    gm_801A5AF0(arg0, 4, 3);
    mei = gm_801A4284(arg0);
    for (i = 0; i < 6; i++) {
        if (mei->match_end.player_standings[i].slot_type != Gm_PKind_NA) {
            gm_80162A98(mei->match_end.player_standings[i].x20);
            gm_80162B4C(mei->match_end.player_standings[i].self_destructs);
            gm_80162A4C(mei->match_end.player_standings[i].x44);
        }
    }
}

void gm_801B1648(GameScene* arg0)
{
    gm_801A5C3C(arg0, gm_801A5244(), NULL, NULL);
}

void gm_801B1688(GameScene* arg0)
{
    gm_801A5EC8(arg0);
}

void gm_801B16A8(GameScene* arg0)
{
    gm_801A5F00(arg0);
}

void gm_801B16C8(GameScene* arg0)
{
    gm_801A5F64(arg0, gm_801A5244(), 0);
    if (gm_801743A4(gm_8047C020.match_end.result) == 0) {
        gm_801623A4(&gm_8047C020.match_end);
    }
}

void gm_801B1724(GameScene* arg0)
{
    lb_8001C550();
    lb_8001D164(0);
}

void gm_801B174C(GameScene* arg0)
{
    SSSData* sss;

    sss = gm_801A427C(arg0);
    sss->x1 = 0;
    sss->no_lras = 1;
    sss->force_stage_id = -1;
    sss->unk_stage = 0;
}

void gm_801B1788(GameScene* arg0)
{
    u16 stage;
    SSSData* sss;

    sss = gm_801A4284(arg0);
    if (sss->start_game != 0) {
        gm_SetPendingScene(4);
        stage = sss->data.data.rules.xE;
        gm_8018F634()->x28 = stage;
        return;
    }
    if (gm_804771C4.match_type == 0) {
        gm_8019A828();
        gm_SetPendingScene(1);
        return;
    }
    gm_8018F634()->x32 = 0;
    gm_SetPendingScene(2);
}

void gm_801B1810(GameScene* arg0)
{
    StartMeleeData* data = gm_801A427C(arg0);
    gm_801905F0(data);
}

void gm_801B1834(GameScene* arg0)
{
    MatchExitInfo* mei;

    mei = gm_801A4284(arg0);
    if (gm_801A52D0(&mei->match_end) != 0) {
        gm_8016260C(mei->match_end.x5, mei->match_end.result);
        gm_801628C4(mei->match_end.frame_count / 60,
                    gm_80162800(&mei->match_end));
    }
    if ((gm_80167140(&mei->match_end) != 0) &&
        (gm_8018F1B0(&mei->match_end) != 0))
    {
        gm_SetPendingScene(5);
        return;
    }
    gm_SetPendingScene(6);
}

#pragma dont_inline on
void gm_801B18D4(GameScene* arg0)
{
    StartMeleeData* smd;
    s32 i;

    smd = gm_801A427C(arg0);

    for (i = 0; i < 4; i++) {
        smd->players[i] = gm_804876D8.players[i];
    }

    /// @todo :: figure out how to call this not inlined
    gm_801B0474(smd, &gm_80487810.match_end);
}
#pragma dont_inline reset

void gm_801B1A2C(GameScene* arg0)
{
    MatchExitInfo* mei;

    mei = gm_801A4284(arg0);
    gm_801629B4(mei->match_end.frame_count / 60);
    gm_80166CCC(&gm_80487810.match_end, &mei->match_end);
}

void gm_801B1A84(GameScene* arg0)
{
    ResultsMatchInfo* rmi;

    rmi = gm_801A427C(arg0);
    rmi->match_end = gm_80487810.match_end;
}

void gm_801B1AD4(GameScene* arg0)
{
    ResultsMatchInfo* rmi;

    rmi = gm_801A427C(arg0);
    gm_80477738 = rmi->match_end;

    gm_8016247C(gm_801688AC(&rmi->match_end));
    if (gm_804771C4.match_type == 0) {
        gm_SetPendingScene(1);
        gm_8018F634()->cur_option = 0x1F;
        return;
    }
    gm_8019E634();
    gm_SetPendingScene(2);
}

#pragma dont_inline on
void gm_801B1B74(GameScene* arg0)
{
    VsModeData* vs_data;
    CSSData* css;
    PAD_STACK(8);

    vs_data = &gmMainLib_804D3EE0->unk_D10;
    css = gm_801A427C(arg0);
    if ((u8) gm_804D68C1 != 0) {
        lb_8001C550();
        lb_8001D164(0);
        lb_8001CE00();
    }
    gm_801B06B0(css, 0x17U, vs_data->data.players[0].c_kind, 1,
                vs_data->data.players[0].color, vs_data->data.players[0].xA,
                9U, gm_804D68C0);
    gm_801B07B4(css, vs_data->data.players[1].c_kind, 1,
                vs_data->data.players[1].color, vs_data->data.players[1].xA,
                0U, gm_804D68C0);
    lbDvd_800174BC();
    gm_804D68C1 = lbTime_8000AF74((u32) gm_804D68C1, 1);
}
#pragma dont_inline reset

static void gm_801B07E8_layer(CSSData* css_data, s8* c_kind, s8* stocks,
                              s8* color, s8* arg4, u8* level)
{
    gm_801B07E8(css_data, c_kind, stocks, color, arg4, level);
}

void gm_801B1C24(GameScene* arg0)
{
    VsModeData* vs = &gmMainLib_804D3EE0->unk_D10;
    CSSData* css = gm_801A4284(arg0);
    s32 i;
    u64 mask;
    struct GameCache* cache;
    s32 j;
    PAD_STACK(0x10);

    if (css->pending_scene_change == 2) {
        gm_801A42F8(GM_MENU);
        return;
    }
    gm_80167A14(vs->data.players);
    gm_801B0730(css, &vs->data.players[0].c_kind, NULL,
                &vs->data.players[0].color, &vs->data.players[0].xA, NULL);
    gm_801B07E8_layer(css, &vs->data.players[1].c_kind, NULL,
                      (s8*) &vs->data.players[1].color,
                      (s8*) &vs->data.players[1].xA, NULL);
    j = (i = 2);
    vs->data.players[1].xE = 0;
    for (; i < 4; i++, j++) {
        vs->data.players[i] = vs->data.players[1];
        vs->data.players[i].color = (vs->data.players[i - 1].color + 1) %
                                    gm_80169238(vs->data.players[j].c_kind);
        if (vs->data.players[i].color == vs->data.players[0].color) {
            vs->data.players[i].color =
                (vs->data.players[i].color + 1) %
                gm_80169238(vs->data.players[j].c_kind);
        }
        vs->data.players[i].slot_type = 3;
    }
    if (gm_804D68C0 == 0) {
        vs->data.players[1].slot = 0;
        vs->data.players[2].slot = 0;
        vs->data.players[3].slot = 0;
    } else {
        j = 1;
        for (i = 0; i < 4; i++) {
            if (gm_804D68C0 != i) {
                vs->data.players[j].slot = i + 1;
                j++;
            }
        }
    }
    cache = &lbDvd_8001822C()->game_cache;
    cache->entries[2].char_id = (s8) vs->data.players[2].c_kind;
    cache->entries[2].color = vs->data.players[2].color;
    cache->entries[3].char_id = (s8) vs->data.players[3].c_kind;
    cache->entries[3].color = vs->data.players[3].color;
    lbDvd_80018254();
    mask = 0;
    for (i = 0; i < 4; i++) {
        mask |= lbAudioAx_80026E84(vs->data.players[i].c_kind);
    }
    lbAudioAx_80026F2C(0x14);
    lbAudioAx_8002702C(4, mask);
    lbAudioAx_80027168();
}

void gm_801B1EB8(GameScene* arg0)
{
    SSSData* sss;

    sss = gm_801A427C(arg0);
    sss->x1 = 0;
    sss->force_stage_id = -1;
    sss->unk_stage = 0;
}

void gm_801B1EEC(GameScene* arg0)
{
    VsModeData* vs_data;
    SSSData* sss;
    s16 stage_id;

    vs_data = &gmMainLib_804D3EE0->unk_D10;
    sss = gm_801A4284(arg0);
    if (sss->start_game == 0) {
        gm_SetPendingScene(0);
        return;
    }
    stage_id = sss->data.data.rules.xE;
    gm_80473814.x6 = stage_id;
    vs_data->data.rules.xE = stage_id;
    lbAudioAx_80026F2C(0x18);
    lbAudioAx_8002702C(8, lbAudioAx_80026EBC((enum InternalStageId)(
                                                 u16) vs_data->data.rules.xE));
    lbAudioAx_80027168();
}

void fn_801B1F6C(int unused) {}

#pragma push
#pragma dont_inline on
void gm_801B1F70(GameScene* arg0)
{
    VsModeData* vs;
    StartMeleeData* data;
    int i;

    vs = &gmMainLib_804D3EE0->unk_D10;
    data = gm_801A427C(arg0);
    gm_80167A64(&data->rules);

    data->rules = vs->data.rules;
    data->rules.x3C = fn_801B1F6C;

    data->rules.x3_6 = true;
    data->rules.x2_5 = false;
    data->rules.x2_1 = true;
    gm_80167A14(data->players);

    for (i = 0; i < 4; i++) {
        data->players[i] = vs->data.players[i];
        data->players[i].xC_b1 = false;
        data->players[i].xD_b2 = true;
    }

    gm_801B0620(&data->players[0], vs->data.players[0].c_kind,
                vs->data.players[0].color, 1, gm_804D68C0);

    for (i = 1; i < 4; i++) {
        PlayerInitData* var_r30 = &data->players[i];
        gm_801B0664(&data->players[i], vs->data.players[i].c_kind,
                    vs->data.players[i].color, 1,
                    vs->data.players[i].slot - 1);
        if (i - 1 != 0) {
            data->players[i].slot_type = Gm_PKind_NA;
        }
    }

    gm_8016F088(data);
    gm_80189CDC(data);
}
#pragma pop

void gm_801B2204(GameScene* arg0)
{
    MatchExitInfo* temp_r3;

    temp_r3 = gm_801A4284(arg0);
    gm_80162968(temp_r3->match_end.frame_count / 60);
    gm_8016247C(temp_r3->match_end.player_standings[0].xE);
    gm_80163298(temp_r3->match_end.player_standings[0].character_kind,
                (u16) gm_80188454(
                    temp_r3->match_end.player_standings[0].character_kind));
    gm_80173BC4(temp_r3->match_end.player_standings[0].character_kind);
    gm_80173EEC();
    if (!gm_80173754(0x1C, gm_804D68C0)) {
        gm_SetPendingScene(0);
    }
    lbAudioAx_80024030(1);
}

void gm_801B2298_OnInit(void)
{
    VsModeData* temp_r31 = &gmMainLib_804D3EE0->unk_D10;
    int i;

    gm_80167B50(temp_r31);

    for (i = 0; i < 4; i++) {
        temp_r31->data.players[i].color = i;
        temp_r31->data.players[i].xE = 0;
        if (i != 0) {
            temp_r31->data.players[1].c_kind = 0x21;
        }
        gm_80473814.players[i] = temp_r31->data.players[i];
    }
}

void gm_801B23C4_OnLoad(void)
{
    gm_804D68C0 = gm_801677F0();
    gm_804D68C1 = 0;
}

void gm_801B23F0(void)
{
    size_t size = GXGetTexBufferSize(0x280, 0x1E0, 4, 0, 0);
    lbDvd_80017740(0, 0x7D6, 4, 4, OSRoundUp32B(size), 0, 1, 0x20, 0);
    lbDvd_80017740(0, 0x7D7, 4, 4, lbSnap_8001E204(), 0, 1, 0x20, 0);
    lbDvd_80017740(0, 0x7D8, 4, 4, lbSnap_8001E210(), 0, 1, 0x20, 0);
}

void gm_801B24B4(GameScene* arg0)
{
    Unk80433380_48* temp_r31_2;
    struct GameCache* temp_r31;

    temp_r31 = &lbDvd_8001822C()->game_cache;
    lbDvd_800174BC();
    temp_r31->mode_id = GM_CAMERA_MODE;
    lbDvd_80018254();
    lb_8001C550();
    temp_r31_2 = lbDvd_GetPreloadedArchive(0x7D8);
    lbSnap_8001E218(lbDvd_GetPreloadedArchive(0x7D7), temp_r31_2);
}

void gm_801B2510(GameScene* arg0)
{
    int* data = gm_801A4284(arg0);
    int temp_r0 = *data;
    if (temp_r0 == 1 || temp_r0 == 2) {
        gm_801A42F8(GM_MENU);
    }
}

void gm_801B254C(GameScene* arg0)
{
    VsModeData* temp_r31;
    u8* temp_r3;
    CSSData* temp_r30;
    struct GameCache* temp_r30_2;

    temp_r31 = &gmMainLib_804D3EE0->unk_950;
    temp_r30 = gm_801A427C(arg0);
    temp_r3 = gm_801A5250();

    temp_r30->match_type = 1;
    temp_r30->ko_star_counts = temp_r3;

    temp_r30->data = *temp_r31;

    temp_r30_2 = &lbDvd_8001822C()->game_cache;
    lbDvd_800174BC();
    temp_r30_2->mode_id = GM_CAMERA_MODE;
    lbDvd_80018254();
}

void gm_801B25D4(GameScene* arg0)
{
    VsModeData* temp_r31;
    u64 temp_ret;
    CSSData* temp_r3;
    int i;

    temp_r31 = &gmMainLib_804D3EE0->unk_950;
    temp_r3 = gm_801A4284(arg0);
    if (temp_r3->pending_scene_change == 2) {
        gm_801A42F8(GM_MENU);
        return;
    }

    *temp_r31 = temp_r3->data;

    temp_ret = 0;
    for (i = 0; i < 6; i++) {
        temp_ret |= lbAudioAx_80026E84(temp_r3->data.data.players[i].c_kind);
    }

    lbAudioAx_80026F2C(0x14);
    lbAudioAx_8002702C(4, temp_ret);
    lbAudioAx_80027168();
}

void gm_801B26AC(GameScene* arg0)
{
    SSSData* sss;
    VsModeData* vs;
    vs = &gmMainLib_804D3EE0->unk_950;
    sss = gm_801A427C(arg0);
    sss->data = *vs;
    gm_80167FC4(sss);
}

void gm_801B2704(GameScene* arg0)
{
    VsModeData* temp_r31;
    SSSData* var_r3;

    temp_r31 = &gmMainLib_804D3EE0->unk_950;
    var_r3 = gm_801A4284(arg0);
    if (var_r3->start_game != 0) {
        *temp_r31 = var_r3->data;
        lbAudioAx_80026F2C(0x18);
        lbAudioAx_8002702C(8, lbAudioAx_80026EBC(temp_r31->data.rules.xE));
        lbAudioAx_80027168();
        return;
    }
    gm_SetPendingScene(1);
}

void gm_PrepCameraModeVSScene(GameScene* arg0)
{
    VsModeData* vs;
    StartMeleeData* start;
    int i;

    vs = &gmMainLib_804D3EE0->unk_950;
    start = gm_801A427C(arg0);
    gm_80167BC8(vs);

    start->rules = vs->data.rules;
    start->rules.x0_0 = 0;

    start->rules.x0_6 = vs->data.rules.x4_4 = false;

    start->rules.x5_0 = true;
    start->rules.x1_2 = true;
    start->rules.x1_3 = true;
    start->rules.x2_5 = false;
    start->rules.x2_6 = false;
    start->rules.x3_1 = false;
    start->rules.x4_0 = false;

    start->rules.x38 = gm_80165268;
    start->rules.x3C = gm_80165268;
    start->rules.x40_check_for_pauser = gm_CameraModeVSGetPauser;
    start->rules.x44 = gmCamera_801A31FC;
    start->rules.x48 = gmCamera_801A3098;
    start->rules.x4C = gmCamera_801A30E4;

    start->rules.xD = 1;
    start->rules.x2_4 = false;

    for (i = 0; i < 6; i++) {
        start->players[i] = vs->data.players[i];
        start->players[i].xD_b3 = true;
    }

    gm_801B0348(start);
    gm_8016F088(start);
    gm_80168FC4();
    lb_8001C550();
    lbSnap_8001E218(lbDvd_GetPreloadedArchive(0x7D7),
                    lbDvd_GetPreloadedArchive(0x7D8));
}

void gm_801B2AF8(GameScene* arg0)
{
    VsModeData* temp_r30;
    u8* temp_r29;

    temp_r30 = &gmMainLib_804D3EE0->unk_950;
    temp_r29 = gm_801A5250();
    gm_80168638(&gm_80479D98.match_end);
    gm_80168710(&gm_80479D98.match_end, temp_r30);
    gm_8016247C(gm_801688AC(&gm_80479D98.match_end));
    gm_801A5258(temp_r29, &gm_80479D98.match_end);
    gm_SetPendingScene(1);
}

void gm_801B2B7C_OnInit(void)
{
    gm_80167B50(&gmMainLib_804D3EE0->unk_950);
}
