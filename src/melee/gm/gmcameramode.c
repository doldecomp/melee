#include "gmcameramode.h"

#include "gm_1B03.h"
#include "gmvsdata.h"

#include "gm/gm_1A3F.h"

#include "lb/forward.h"

#include "melee/gm/gm_unsplit.h"
#include "melee/gm/gmcamera.h"
#include "melee/gm/gmmain_lib.h"
#include "melee/gm/gmvsmelee.h"
#include "melee/gm/types.h"
#include "melee/lb/lbaudio_ax.h"
#include "melee/lb/lbcardnew.h"
#include "melee/lb/lbdvd.h"
#include "melee/lb/lbsnap.h"
#include "melee/lb/types.h"
#include "melee/mn/types.h"

#include <dolphin/os.h>

/* 1B24B4 */ static void gm_801B24B4(GameModeState*);
/* 1B2510 */ static void gm_801B2510(GameModeState*);
/* 1B254C */ static void gm_801B254C(GameModeState*);
/* 1B25D4 */ static void gm_801B25D4(GameModeState*);
/* 1B26AC */ static void gm_801B26AC(GameModeState*);
/* 1B2704 */ static void gm_801B2704(GameModeState*);
/* 1B2790 */ static void gm_PrepCameraModeVSScene(GameModeState*);
/* 1B2AF8 */ static void gm_801B2AF8(GameModeState*);
/* 4D68C8 */ static s64 gm_804D68C8;

GameModeState gm_Mode_Camera_States[] = {
    {
        0,
        lbDvdPreload_3,
        0,
        gm_801B24B4,
        gm_801B2510,
        {
            GS_CAMERA_VS,
            &gm_804D68C8,
            &gm_804D68C8,
        },
    },
    {
        1,
        lbDvdPreload_3,
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
        2,
        lbDvdPreload_3,
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
        3,
        lbDvdPreload_3,
        0,
        gm_PrepCameraModeVSScene,
        gm_801B2AF8,
        {
            GS_VS,
            &gm_80480530,
            &gm_80479D98,
        },
    },
    { -1 },
};

void gm_801B23F0(void)
{
    size_t size = GXGetTexBufferSize(640, 480, 4, 0, 0);
    lbDvd_80017740(0, 2006, 4, 4, OSRoundUp32B(size), 0, 1, 32, 0);
    lbDvd_80017740(0, 2007, 4, 4, lbSnap_8001E204(), 0, 1, 32, 0);
    lbDvd_80017740(0, 2008, 4, 4, lbSnap_8001E210(), 0, 1, 32, 0);
}

void gm_801B24B4(GameModeState* arg0)
{
    Unk80433380_48* temp_r31_2;
    struct GameCache* temp_r31;

    temp_r31 = &lbDvd_GetPreloadCacheScene()->game_cache;
    lbDvd_800174BC();
    temp_r31->mode_kind = GM_CAMERA_MODE;
    lbDvd_80018254();
    lb_8001C550();
    temp_r31_2 = lbDvd_GetPreloadedArchive(0x7D8);
    lbSnap_8001E218(lbDvd_GetPreloadedArchive(0x7D7), temp_r31_2);
}

void gm_801B2510(GameModeState* arg0)
{
    int* data = gm_GetGameSceneLeaveData(arg0);
    int temp_r0 = *data;
    if (temp_r0 == 1 || temp_r0 == 2) {
        gm_ChangeGameModeAfterCurrentScene(GM_MENU);
    }
}

void gm_801B254C(GameModeState* arg0)
{
    VsModeData* temp_r31;
    u8* temp_r3;
    CSSData* temp_r30;
    struct GameCache* temp_r30_2;

    temp_r31 = &gmMainLib_804D3EE0->unk_950;
    temp_r30 = gm_GetGameSceneLoadData(arg0);
    temp_r3 = gm_801A5250();

    temp_r30->match_type = 1;
    temp_r30->ko_star_counts = temp_r3;

    temp_r30->data = *temp_r31;

    temp_r30_2 = &lbDvd_GetPreloadCacheScene()->game_cache;
    lbDvd_800174BC();
    temp_r30_2->mode_kind = GM_CAMERA_MODE;
    lbDvd_80018254();
}

void gm_801B25D4(GameModeState* arg0)
{
    VsModeData* temp_r31;
    u64 temp_ret;
    CSSData* temp_r3;
    int i;

    temp_r31 = &gmMainLib_804D3EE0->unk_950;
    temp_r3 = gm_GetGameSceneLeaveData(arg0);
    if (temp_r3->pending_scene_change == 2) {
        gm_ChangeGameModeAfterCurrentScene(GM_MENU);
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

void gm_801B26AC(GameModeState* arg0)
{
    SSSData* sss;
    VsModeData* vs;
    vs = &gmMainLib_804D3EE0->unk_950;
    sss = gm_GetGameSceneLoadData(arg0);
    sss->data = *vs;
    gm_80167FC4(sss);
}

void gm_801B2704(GameModeState* arg0)
{
    VsModeData* temp_r31;
    SSSData* var_r3;

    temp_r31 = &gmMainLib_804D3EE0->unk_950;
    var_r3 = gm_GetGameSceneLeaveData(arg0);
    if (var_r3->start_game != 0) {
        *temp_r31 = var_r3->data;
        lbAudioAx_80026F2C(0x18);
        lbAudioAx_8002702C(8, lbAudioAx_80026EBC(temp_r31->data.rules.stkind));
        lbAudioAx_80027168();
        return;
    }
    gm_SetPendingSceneIndex(1);
}

void gm_PrepCameraModeVSScene(GameModeState* arg0)
{
    VsModeData* vs;
    StartMeleeData* start;
    int i;

    vs = &gmMainLib_804D3EE0->unk_950;
    start = gm_GetGameSceneLoadData(arg0);
    gm_80167BC8(vs);

    start->rules = vs->data.rules;
    start->rules.match_mode = 0;

    start->rules.x0_6 = vs->data.rules.x4_4 = false;

    start->rules.x5_0 = true;
    start->rules.x1_2 = true;
    start->rules.x1_3 = true;
    start->rules.x2_5 = false;
    start->rules.x2_6 = false;
    start->rules.x3_1 = false;
    start->rules.x4_0 = false;

    start->rules.on_unpause_override = gm_80165268;
    start->rules.on_pause_override = gm_80165268;
    start->rules.check_for_pauser_override = gm_CameraModeVSGetPauser;
    start->rules.x44 = gmCamera_801A31FC;
    start->rules.x48 = gmCamera_801A3098;
    start->rules.x4C = gmCamera_801A30E4;

    start->rules.xD = 1;
    start->rules.disable_pausing = false;

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

void gm_801B2AF8(GameModeState* arg0)
{
    VsModeData* temp_r30;
    u8* temp_r29;

    temp_r30 = &gmMainLib_804D3EE0->unk_950;
    temp_r29 = gm_801A5250();
    gm_80168638(&gm_80479D98.match_end);
    gm_80168710(&gm_80479D98.match_end, temp_r30);
    gm_8016247C(gm_801688AC(&gm_80479D98.match_end));
    gm_801A5258(temp_r29, &gm_80479D98.match_end);
    gm_SetPendingSceneIndex(1);
}

void gm_Mode_Camera_OnInit(void)
{
    gm_80167B50(&gmMainLib_804D3EE0->unk_950);
}
