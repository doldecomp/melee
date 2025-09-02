/**
 * @todo also contains Target scenes, maybe gmstadium is a better name,
 * since these are all in the single player "stadium" menu
 */
#include "gmmultiman.h"

#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/types.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lbcardnew.h>
#include <melee/lb/lbdvd.h>
#include <melee/lb/types.h>

extern CSSData gm_804950F0;
extern VsModeData gm_80495238;
extern MatchExitInfo gm_80495370;
extern StartMeleeData gm_80490AA8;
extern StartMeleeData gm_80490BE0;
extern StartMeleeData gm_80490960;
extern u8 gm_804D68E8;
extern u8 gm_804D68E9;
extern u8 gm_804D68F0;
extern s8 gm_804D68F1;

MinorScene gm_803DECB8_MinorScenes[] = {
    {
        0x00,
        0x03,
        0,
        gm_801B632C,
        gm_801B63C4,
        {
            0x08,
            &gm_80490960,
            &gm_80490960,
        },
    },
    {
        0x01,
        0x03,
        0,
        gm_801B6428,
        gm_801B65D4,
        {
            0x02,
            &gm_80490AA8,
            &gm_80490BE0,
        },
    },
    { 0xFF },
};

MinorScene gm_803DED00_MinorScenes[] = {
    {
        0x00,
        0x03,
        0,
        gm_801B6AD8,
        gm_801B6B70,
        {
            MN_CSS,
            &gm_804950F0,
            &gm_804950F0,
        },
    },
    {
        0x01,
        0x03,
        0,
        gm_801B6BE8,
        gm_801B6F44,
        {
            MN_VS,
            &gm_80495238,
            &gm_80495370,
        },
    },
    { -1 },
};

MinorScene gm_803DED48_MinorScenes[] = {
    {
        0x00,
        0x03,
        0,
        gm_801B7044,
        gm_801B70DC,
        {
            MN_CSS,
            &gm_804950F0,
            &gm_804950F0,
        },
    },
    {
        0x01,
        0x03,
        0,
        gm_801B7154,
        gm_801B74F0,
        {
            MN_VS,
            &gm_80495238,
            &gm_80495370,
        },
    },
    { -1 },
};

MinorScene gm_803DED90_MinorScenes[] = {
    {
        0x00,
        0x03,
        0,
        gm_801B75F0,
        gm_801B7688,
        {
            MN_CSS,
            &gm_804950F0,
            &gm_804950F0,
        },
    },
    {
        0x01,
        0x03,
        0,
        gm_801B7700,
        gm_801B7AA0,
        {
            MN_VS,
            &gm_80495238,
            &gm_80495370,
        },
    },
    { 0xFF },
};

MinorScene gm_803DEDD8_MinorScenes[] = {
    {
        0x00,
        0x03,
        0,
        gm_801B7B74,
        gm_801B7C0C,
        {
            MN_CSS,
            &gm_804950F0,
            &gm_804950F0,
        },
    },
    {
        0x01,
        0x03,
        0,
        gm_801B7C84,
        gm_801B8024,
        {
            MN_VS,
            &gm_80495238,
            &gm_80495370,
        },
    },
    { 0xFF },
};

MinorScene gm_803DEE20_MinorScenes[] = {
    {
        0x00,
        0x03,
        0,
        gm_801B8110,
        gm_801B81A8,
        {
            MN_CSS,
            &gm_804950F0,
            &gm_804950F0,
        },
    },
    {
        0x01,
        0x03,
        0,
        gm_801B8220,
        gm_801B8580,
        {
            MN_VS,
            &gm_80495238,
            &gm_80495370,
        },
    },
    { -1 },
};

MinorScene gm_803DEE68_MinorScenes[] = {
    {
        0x00,
        0x03,
        0,
        gm_801B863C,
        gm_801B86D4,
        {
            MN_CSS,
            &gm_804950F0,
            &gm_804950F0,
        },
    },
    {
        0x01,
        0x03,
        0,
        gm_801B874C,
        gm_801B8AF8,
        {
            MN_VS,
            &gm_80495238,
            &gm_80495370,
        },
    },
    { 0xFF },
};

UNK_T gm_801B6320(void)
{
    return &gmMainLib_804D3EE0->unk_530.unk_584;
}

/// #gm_801B632C

/// #gm_801B63C4

/// #gm_801B6428

/// #gm_801B65D4

void gm_801B67E8_OnInit(void)
{
    struct gmm_x0_584_t* temp_r4 =
        (struct gmm_x0_584_t*) &gmMainLib_804D3EE0->unk_530.unk_584.unk_584;
    gmMainLib_804D3EE0->unk_530.unk_584.unk_584 = 0x21;
    temp_r4->unk_585 = 0;
    temp_r4->unk_586 = 0x78;
}

void gm_801B6808_OnLoad(void)
{
    gm_804D68E8 = gm_801677F0();
    gm_804D68E9 = 0;
}

void gm_801B6834(void)
{
    gm_80167B50(&gmMainLib_804D3EE0->unk_1490);
}

void gm_801B685C(void)
{
    gm_804D68F0 = gm_801677F0();
    gm_804D68F1 = 0;
    lb_8001C550();
}

bool gm_801B688C(bool arg0)
{
    s32 temp_r31;
    int temp_r30;
    VsModeData* temp_r29;
    u8 temp_r3;
    u16 tmp;

    PAD_STACK(8);

    temp_r29 = &gmMainLib_804D3EE0->unk_1490;
    lb_8001C550();
    lb_8001D164(0);
    lb_8001CE00();
    if ((gm_80181A14() != 0) && (gm_801A4310() == MJ_15MIN_VS) &&
        ((tmp = gm_80173498()) != 0x148))
    {
        gm_80164504(tmp);
    }
    temp_r30 = gm_80181A14();
    temp_r31 = gm_80181A34();
    gm_80173C70(temp_r29->data.players[0].c_kind, gm_80181A24(), temp_r31,
                temp_r30);
    gm_80173EEC();
    gm_80172898(0x20);
    if ((gm_80181A14() != 0) && (gm_801A4310() == MJ_100MAN_VS)) {
        temp_r3 = gm_80173460(temp_r29->data.players[0].c_kind);
        if (temp_r3 != 0x21) {
            gm_801736E8(temp_r29->data.players[0].c_kind,
                        temp_r29->data.players[0].color, gm_804D68F0,
                        temp_r29->data.players[0].xA, temp_r3, gm_801A4310());
            gm_801A42F8(MJ_CHALLENGER_APPROACH);
            return true;
        }
    }
    if (gm_80173754(gm_801A4310(), gm_804D68F0)) {
        return true;
    }
    return false;
}

void gm_801B69C0(StartMeleeData* arg0)
{
    gmMainLib_8015CC34();
    arg0->rules.x0_0 = 0;
    arg0->rules.x0_6 = true;
    arg0->rules.x0_7 = true;
    arg0->rules.x10 = 0;
    arg0->rules.timer_shows_hours = true;
    arg0->rules.x4_2 = true;
    arg0->rules.x2_5 = false;
    arg0->rules.x5_0 = false;
    arg0->rules.x4_4 = false;
    arg0->rules.x4_3 = true;
    arg0->rules.x5_1 = true;
    arg0->rules.is_teams = true;
    arg0->rules.xE = 0x11D;
    arg0->rules.x18 = 0;
    arg0->rules.xB = 2;
    arg0->rules.x2C = 0.5F;
    arg0->rules.x20 = 0xFFFFFFFFFFFBFCFF;
    arg0->rules.x44 = gm_80182174;
    arg0->rules.x3_3 = true;
    arg0->rules.x3_2 = true;
    arg0->rules.x0_3 = 6;
}

static inline void gm_801B6AD8_inline(MinorScene* scene, int x)
{
    CSSData* temp_r3;
    VsModeData* temp_r31;
    struct GameCache* temp_r31_2;

    temp_r31 = &gmMainLib_804D3EE0->unk_1490;
    temp_r3 = gm_801A427C(scene);
    temp_r31->data.players[0].stocks = 1;
    temp_r31->data.players[0].x18 = 1.0F;
    temp_r31->data.players[0].x1C = 1.0F;
    gm_801B06B0(temp_r3, x, temp_r31->data.players[0].c_kind, 1,
                temp_r31->data.players[0].color, temp_r31->data.players[0].xA,
                0, gm_804D68F0);
    temp_r31_2 = &lbDvd_8001822C()->game_cache;
    lbDvd_800174BC();
    temp_r31_2->entries[1].char_id = CKIND_BOY;
    temp_r31_2->entries[1].color = 0;
    temp_r31_2->entries[2].char_id = CKIND_GIRL;
    temp_r31_2->entries[2].color = 0;
    temp_r31_2->stage_id = 0x11D;
    lbDvd_80018254();
}

void gm_801B6AD8(MinorScene* scene)
{
    gm_801B6AD8_inline(scene, 0x11);
}

void gm_801B6B70(MinorScene* scene)
{
    VsModeData* temp_r31;
    CSSData* temp_r3;

    PAD_STACK(8);

    temp_r31 = &gmMainLib_804D3EE0->unk_1490;
    temp_r3 = gm_801A4284(scene);
    if (temp_r3->pending_scene_change == 2) {
        gm_801A42F8(MJ_MENU);
        return;
    }
    gm_80167A14(temp_r31->data.players);
    gm_801B0730(temp_r3, &temp_r31->data.players[0].c_kind, NULL,
                &temp_r31->data.players[0].color,
                &temp_r31->data.players[0].xA, NULL);
}

void gm_801B6BE8(MinorScene* scene)
{
    VsModeData* temp_r31;
    UnkMultimanData* temp_r30;
    StartMeleeData* temp_r3;
    s32* temp_r29;
    int i;

    PAD_STACK(8);

    temp_r31 = &gmMainLib_804D3EE0->unk_1490;
    temp_r3 = gm_801A427C(scene);

    temp_r3->rules = temp_r31->data.rules;
    gm_801B69C0(temp_r3);
    gm_80167A14(temp_r3->players);

    for (i = 0; i < 6; i++) {
        temp_r3->players[i] = temp_r31->data.players[i];
    }
    gm_801B0620(temp_r3->players, temp_r31->data.players[0].c_kind,
                temp_r31->data.players[0].color, 1, gm_804D68F0);

    for (i = 1; i < 6; i++) {
        temp_r3->players[i].team = !temp_r3->players[0].team;
    }

    gm_8016F088(temp_r3);
    gm_80182554(temp_r3->players[0].c_kind, 0x21);
    temp_r29 =
        gmMainLib_8015D6A4(gm_80164024(temp_r31->data.players[0].c_kind));
    temp_r30 = gm_80182DF0(temp_r31->data.players[0].c_kind, 0x21);
    temp_r30->x0_0 =
        gmMainLib_8015D6BC(gm_80164024(temp_r31->data.players[0].c_kind));
    gm_80181A44(temp_r31->data.players[0].c_kind, 0x21, temp_r30->x0_0);
    if (temp_r30->x0_0) {
        temp_r30->x4 = *temp_r29;
        gm_80181B64(temp_r31->data.players[0].c_kind, 0x21, temp_r30->x4);
        /*
         */
    } else {
        temp_r30->x2 = *temp_r29;
        gm_80181AC8(temp_r31->data.players[0].c_kind, 0x21, temp_r30->x2);
        gm_80181B64(temp_r31->data.players[0].c_kind, 0x21, 0x0FFFFFFF);
    }
}

void gm_801B6F44(MinorScene* scene)
{
    UnkMultimanData* temp_r3_2;
    VsModeData* temp_r29;
    s32* temp_r30;
    MatchExitInfo* temp_r3;

    PAD_STACK(8);

    temp_r29 = &gmMainLib_804D3EE0->unk_1490;
    temp_r3 = gm_801A4284(scene);
    if (temp_r3->match_end.result == 8) {
        gm_SetScenePendingMinor(1);
        return;
    }
    gm_80162968(temp_r3->match_end.frame_count / 60);
    gm_8016247C(temp_r3->match_end.player_standings[0].xE);
    gm_80182578();
    temp_r30 =
        gmMainLib_8015D6A4(gm_80164024(temp_r29->data.players[0].c_kind));
    temp_r3_2 = gm_80182DF0(temp_r29->data.players[0].c_kind, 0x21);
    if (temp_r3_2->x0_0) {
        gmMainLib_8015D6D8(gm_80164024(temp_r29->data.players[0].c_kind), 1);
        *temp_r30 = temp_r3_2->x4;
    } else {
        gmMainLib_8015D6D8(gm_80164024(temp_r29->data.players[0].c_kind), 0);
        *temp_r30 = temp_r3_2->x2;
    }
    if (!gm_801B688C(temp_r3_2->x0_0)) {
        gm_SetScenePendingMinor(0);
    }
}

void gm_801B7044(MinorScene* scene)
{
    gm_801B6AD8_inline(scene, 0x12);
}

void gm_801B70DC(MinorScene* scene)
{
    VsModeData* temp_r31;
    CSSData* temp_r3;

    PAD_STACK(8);

    temp_r31 = &gmMainLib_804D3EE0->unk_1490;
    temp_r3 = gm_801A4284(scene);
    if (temp_r3->pending_scene_change == 2) {
        gm_801A42F8(MJ_MENU);
        return;
    }
    gm_80167A14(temp_r31->data.players);
    gm_801B0730(temp_r3, &temp_r31->data.players[0].c_kind, NULL,
                &temp_r31->data.players[0].color,
                &temp_r31->data.players[0].xA, NULL);
}

void gm_801B7154(MinorScene* scene)
{
    VsModeData* temp_r31;
    UnkMultimanData* temp_r30;
    s32* temp_r29;
    StartMeleeData* temp_r3;
    int i;

    PAD_STACK(8);

    temp_r31 = &gmMainLib_804D3EE0->unk_1490;
    temp_r3 = gm_801A427C(scene);

    temp_r3->rules = temp_r31->data.rules;
    gm_801B69C0(temp_r3);
    gm_80167A14(temp_r3->players);

    for (i = 0; i < 6; i++) {
        temp_r3->players[i] = temp_r31->data.players[i];
    }

    gm_801B0620(temp_r3->players, temp_r31->data.players[0].c_kind,
                temp_r31->data.players[0].color, 1, gm_804D68F0);

    for (i = 1; i < 6; i++) {
        temp_r3->players[i].team = !temp_r3->players[0].team;
        temp_r3->players[i].xC_b1 = false;
    }
    gm_8016F088(temp_r3);
    gm_80182554(temp_r3->players[0].c_kind, 0x22);
    temp_r29 =
        gmMainLib_8015D6F8(gm_80164024(temp_r31->data.players[0].c_kind));
    temp_r30 = gm_80182DF0(temp_r31->data.players[0].c_kind, 0x22);
    temp_r30->x0_0 =
        gmMainLib_8015D710(gm_80164024(temp_r31->data.players[0].c_kind));
    gm_80181A44(temp_r31->data.players[0].c_kind, 0x22, temp_r30->x0_0);
    if (temp_r30->x0_0) {
        temp_r30->x4 = *temp_r29;
        gm_80181B64(temp_r31->data.players[0].c_kind, 0x22, temp_r30->x4);
        return;
    }
    temp_r30->x2 = *temp_r29;
    gm_80181AC8(temp_r31->data.players[0].c_kind, 0x22, temp_r30->x2);
    gm_80181B64(temp_r31->data.players[0].c_kind, 0x22, 0x0FFFFFFF);
}

void gm_801B74F0(MinorScene* scene)
{
    UnkMultimanData* temp_r3_2;
    VsModeData* temp_r29;
    s32* temp_r30;
    MatchExitInfo* temp_r3;
    PAD_STACK(8);

    temp_r29 = &gmMainLib_804D3EE0->unk_1490;
    temp_r3 = gm_801A4284(scene);
    if (temp_r3->match_end.result == 8) {
        gm_SetScenePendingMinor(1);
        return;
    }
    gm_80162968(temp_r3->match_end.frame_count / 60);
    gm_8016247C(temp_r3->match_end.player_standings[0].xE);
    gm_80182578();
    temp_r30 =
        gmMainLib_8015D6F8(gm_80164024(temp_r29->data.players[0].c_kind));
    temp_r3_2 = gm_80182DF0(temp_r29->data.players[0].c_kind, 0x22);
    if (temp_r3_2->x0_0) {
        gmMainLib_8015D72C(gm_80164024(temp_r29->data.players[0].c_kind), 1);
        *temp_r30 = temp_r3_2->x4;
    } else {
        gmMainLib_8015D72C(gm_80164024(temp_r29->data.players[0].c_kind), 0);
        *temp_r30 = temp_r3_2->x2;
    }
    if (gm_801B688C(temp_r3_2->x0_0) == 0) {
        gm_SetScenePendingMinor(0);
    }
}

void gm_801B75F0(MinorScene* scene)
{
    gm_801B6AD8_inline(scene, 0x13);
}

void gm_801B7688(MinorScene* scene)
{
    VsModeData* temp_r31;
    CSSData* temp_r3;
    PAD_STACK(8);

    temp_r31 = &gmMainLib_804D3EE0->unk_1490;
    temp_r3 = gm_801A4284(scene);
    if (temp_r3->pending_scene_change == 2) {
        gm_801A42F8(MJ_MENU);
        return;
    }
    gm_80167A14(temp_r31->data.players);
    gm_801B0730(temp_r3, &temp_r31->data.players[0].c_kind, NULL,
                &temp_r31->data.players[0].color,
                &temp_r31->data.players[0].xA, NULL);
}

static inline VsModeData* getMultimanData(void)
{
    return &gmMainLib_804D3EE0->unk_1490;
}

void gm_801B7700(MinorScene* scene)
{
    StartMeleeData* temp_r3;
    VsModeData* temp_r30;
    UnkMultimanData* temp_r28;
    s32 var_r29;
    u16* temp_r27;
    int i;

    temp_r30 = getMultimanData();
    temp_r3 = gm_801A427C(scene);

    temp_r3->rules = temp_r30->data.rules;
    gm_801B69C0(temp_r3);
    temp_r3->rules.x0_6 = true;
    temp_r3->rules.x0_7 = false;
    temp_r3->rules.x10 = 0xB4;
    gm_80167A14(temp_r3->players);

    for (i = 0; i < 6; i++) {
        temp_r3->players[i] = temp_r30->data.players[i];
    }

    gm_801B0620(temp_r3->players, temp_r30->data.players[0].c_kind,
                temp_r30->data.players[0].color, 1, gm_804D68F0);

    for (i = 1; i < 6; i++) {
        temp_r3->players[i].team = !temp_r3->players[0].team;
        temp_r3->players[i].xC_b1 = false;
    }

    gm_8016F088(temp_r3);
    gm_80182554(temp_r3->players[0].c_kind, 0x23);
    temp_r27 =
        gmMainLib_8015D74C(gm_80164024(temp_r30->data.players[0].c_kind));
    temp_r28 = gm_80182DF0(temp_r30->data.players[0].c_kind, 0x23);
    temp_r28->x0_0 = *temp_r27 ? true : false;
    gm_80181A44(temp_r30->data.players[0].c_kind, 0x23, temp_r28->x0_0);
    if (temp_r28->x0_0) {
        temp_r28->x2 = (u16) *temp_r27;
        gm_80181AC8(temp_r30->data.players[0].c_kind, 0x23, temp_r28->x2);
    } else {
        temp_r28->x2 = 0;
        gm_80181AC8(temp_r30->data.players[0].c_kind, 0x23, 0);
    }
}

void gm_801B7AA0(MinorScene* scene)
{
    UnkMultimanData* temp_r3_2;
    VsModeData* temp_r30;
    u16* temp_r31;
    MatchExitInfo* temp_r3;
    PAD_STACK(8);

    temp_r30 = &gmMainLib_804D3EE0->unk_1490;
    temp_r3 = gm_801A4284(scene);
    if (temp_r3->match_end.result == 8) {
        gm_SetScenePendingMinor(1);
        return;
    }
    gm_80162968(temp_r3->match_end.frame_count / 60);
    gm_8016247C(temp_r3->match_end.player_standings[0].xE);
    gm_80182578();
    temp_r31 =
        gmMainLib_8015D74C(gm_80164024(temp_r30->data.players[0].c_kind));
    temp_r3_2 = gm_80182DF0(temp_r30->data.players[0].c_kind, 0x23);
    if (temp_r3_2->x0_0) {
        *temp_r31 = temp_r3_2->x2;
    } else {
        *temp_r31 = 0;
    }
    if (gm_801B688C(temp_r3_2->x0_0) == 0) {
        gm_SetScenePendingMinor(0);
    }
}

void gm_801B7B74(MinorScene* scene)
{
    gm_801B6AD8_inline(scene, 0x14);
}

void gm_801B7C0C(MinorScene* scene)
{
    VsModeData* temp_r31;
    CSSData* temp_r3;
    PAD_STACK(8);

    temp_r31 = &gmMainLib_804D3EE0->unk_1490;
    temp_r3 = gm_801A4284(scene);
    if (temp_r3->pending_scene_change == 2) {
        gm_801A42F8(MJ_MENU);
        return;
    }
    gm_80167A14(temp_r31->data.players);
    gm_801B0730(temp_r3, &temp_r31->data.players[0].c_kind, NULL,
                &temp_r31->data.players[0].color,
                &temp_r31->data.players[0].xA, NULL);
}

void gm_801B7C84(MinorScene* scene)
{
    VsModeData* temp_r30;
    StartMeleeData* temp_r3;
    UnkMultimanData* temp_r28;
    u16* temp_r27;
    int i;

    temp_r30 = getMultimanData();
    temp_r3 = gm_801A427C(scene);

    PAD_STACK(8);

    temp_r3->rules = temp_r30->data.rules;
    gm_801B69C0(temp_r3);
    temp_r3->rules.x0_6 = true;
    temp_r3->rules.x0_7 = false;
    temp_r3->rules.x10 = 0x384;
    gm_80167A14(temp_r3->players);

    for (i = 0; i < 6; i++) {
        temp_r3->players[i] = temp_r30->data.players[i];
    }

    gm_801B0620(temp_r3->players, temp_r30->data.players[0].c_kind,
                temp_r30->data.players[0].color, 1, gm_804D68F0);

    for (i = 1; i < 6; i++) {
        temp_r3->players[i].team = !temp_r3->players[0].team;
        temp_r3->players[i].xC_b1 = false;
    }

    gm_8016F088(temp_r3);
    gm_80182554(temp_r3->players[0].c_kind, 0x24);
    temp_r27 =
        gmMainLib_8015D7A4(gm_80164024(temp_r30->data.players[0].c_kind));
    temp_r28 = gm_80182DF0(temp_r30->data.players[0].c_kind, 0x24);
    temp_r28->x0_0 = *temp_r27 ? true : false;
    gm_80181A44(temp_r30->data.players[0].c_kind, 0x24, temp_r28->x0_0);
    if (temp_r28->x0_0) {
        temp_r28->x2 = *temp_r27;
        gm_80181AC8(temp_r30->data.players[0].c_kind, 0x24, temp_r28->x2);
    } else {
        temp_r28->x2 = 0;
        gm_80181AC8(temp_r30->data.players[0].c_kind, 0x24, 0);
    }
}

void gm_801B8024(MinorScene* scene)
{
    UnkMultimanData* temp_r3_2;
    VsModeData* temp_r29;
    u16* temp_r30;
    MatchExitInfo* temp_r3;
    PAD_STACK(8);

    temp_r29 = &gmMainLib_804D3EE0->unk_1490;
    temp_r3 = gm_801A4284(scene);
    if (temp_r3->match_end.result == 8) {
        gm_SetScenePendingMinor(1);
        return;
    }
    gm_80162968(temp_r3->match_end.frame_count / 60);
    gm_8016247C(temp_r3->match_end.player_standings[0].xE);
    gm_80182578();
    temp_r30 =
        gmMainLib_8015D7A4(gm_80164024(temp_r29->data.players[0].c_kind));
    temp_r3_2 = gm_80182DF0(temp_r29->data.players[0].c_kind, 0x24);
    if (temp_r3_2->x0_0) {
        *temp_r30 = temp_r3_2->x2;
        gmMainLib_8015D780(gm_80164024(temp_r29->data.players[0].c_kind));
    } else {
        *temp_r30 = 0;
    }
    if (gm_801B688C(temp_r3_2->x0_0) == 0) {
        gm_SetScenePendingMinor(0);
    }
}

void gm_801B8110(MinorScene* scene)
{
    gm_801B6AD8_inline(scene, 0x15);
}

void gm_801B81A8(MinorScene* scene)
{
    VsModeData* temp_r31;
    CSSData* temp_r3;
    PAD_STACK(8);

    temp_r31 = &gmMainLib_804D3EE0->unk_1490;
    temp_r3 = gm_801A4284(scene);
    if (temp_r3->pending_scene_change == 2) {
        gm_801A42F8(MJ_MENU);
        return;
    }
    gm_80167A14(temp_r31->data.players);
    gm_801B0730(temp_r3, &temp_r31->data.players[0].c_kind, NULL,
                &temp_r31->data.players[0].color,
                &temp_r31->data.players[0].xA, NULL);
}

void gm_801B8220(MinorScene* scene)
{
    VsModeData* temp_r30 = &gmMainLib_804D3EE0->unk_1490;
    StartMeleeData* temp_r3 = gm_801A427C(scene);
    s32* temp_r29;
    UnkMultimanData* temp_r3_3;
    int i;

    PAD_STACK(8);

    temp_r3->rules = temp_r30->data.rules;
    gm_801B69C0(temp_r3);
    temp_r3->rules.x0_6 = false;
    temp_r3->rules.x0_7 = false;
    temp_r3->rules.x10 = 0;
    temp_r3->rules.x5_0 = true;
    temp_r3->rules.x5_1 = false;
    gm_80167A14(temp_r3->players);

    for (i = 0; i < 6; i++) {
        temp_r3->players[i] = temp_r30->data.players[i];
    }

    gm_801B0620(temp_r3->players, temp_r30->data.players[0].c_kind,
                temp_r30->data.players[0].color, 1, gm_804D68F0);

    for (i = 1; i < 6; i++) {
        temp_r3->players[i].team = !temp_r3->players[0].team;
        temp_r3->players[i].xC_b1 = false;
    }

    gm_8016F088(temp_r3);
    gm_80182554(temp_r3->players[0].c_kind, 0x25);
    temp_r29 =
        gmMainLib_8015D7BC(gm_80164024(temp_r30->data.players[0].c_kind));
    temp_r3_3 = gm_80182DF0(temp_r30->data.players[0].c_kind, 0x25);
    temp_r3_3->x2 = *temp_r29;
    gm_80181AC8(temp_r30->data.players[0].c_kind, 0x25, temp_r3_3->x2);
}

void gm_801B8580(MinorScene* scene)
{
    UnkMultimanData* temp_r3_2;
    VsModeData* temp_r30;
    s32* temp_r31;
    MatchExitInfo* temp_r3;
    PAD_STACK(8);

    temp_r30 = &gmMainLib_804D3EE0->unk_1490;
    temp_r3 = gm_801A4284(scene);
    if (temp_r3->match_end.result == 8) {
        gm_SetScenePendingMinor(1U);
        return;
    }
    gm_80162968(temp_r3->match_end.frame_count / 60);
    gm_8016247C(temp_r3->match_end.player_standings[0].xE);
    gm_80182578();
    temp_r31 =
        gmMainLib_8015D7BC(gm_80164024(temp_r30->data.players[0].c_kind));
    temp_r3_2 = gm_80182DF0(temp_r30->data.players[0].c_kind, 0x25);
    *temp_r31 = temp_r3_2->x2;
    if (!gm_801B688C(temp_r3_2->x0_0)) {
        gm_SetScenePendingMinor(0U);
    }
}

void gm_801B863C(MinorScene* scene)
{
    gm_801B6AD8_inline(scene, 0x16);
}

void gm_801B86D4(MinorScene* scene)
{
    VsModeData* temp_r31;
    CSSData* temp_r3;
    PAD_STACK(8);

    temp_r31 = &gmMainLib_804D3EE0->unk_1490;
    temp_r3 = gm_801A4284(scene);
    if (temp_r3->pending_scene_change == 2) {
        gm_801A42F8(MJ_MENU);
        return;
    }
    gm_80167A14(temp_r31->data.players);
    gm_801B0730(temp_r3, &temp_r31->data.players[0].c_kind, NULL,
                &temp_r31->data.players[0].color,
                &temp_r31->data.players[0].xA, NULL);
}

void gm_801B874C(MinorScene* scene)
{
    VsModeData* temp_r29 = &gmMainLib_804D3EE0->unk_1490;
    StartMeleeData* temp_r3 = gm_801A427C(scene);
    s32* temp_r28;
    UnkMultimanData* temp_r3_3;
    int i;

    PAD_STACK(8);

    temp_r3->rules = temp_r29->data.rules;
    gm_801B69C0(temp_r3);
    temp_r3->rules.xB = -1;
    temp_r3->rules.x0_6 = false;
    temp_r3->rules.x0_7 = false;
    temp_r3->rules.x10 = 0;
    temp_r3->rules.x5_0 = true;
    temp_r3->rules.x5_1 = false;
    gm_80167A14(temp_r3->players);

    for (i = 0; i < 6; i++) {
        temp_r3->players[i] = temp_r29->data.players[i];
    }

    gm_801B0620(temp_r3->players, temp_r29->data.players[0].c_kind,
                temp_r29->data.players[0].color, 1, gm_804D68F0);

    for (i = 1; i < 6; i++) {
        temp_r3->players[i].team = !temp_r3->players[0].team;
        temp_r3->players[i].xD_b4 = true;
        temp_r3->players[i].xC_b1 = false;
    }

    gm_8016F088(temp_r3);
    gm_80182554(temp_r3->players[0].c_kind, 0x26);
    temp_r28 =
        gmMainLib_8015D7D4(gm_80164024(temp_r29->data.players[0].c_kind));
    temp_r3_3 = gm_80182DF0(temp_r29->data.players[0].c_kind, 0x26);
    temp_r3_3->x2 = *temp_r28;
    gm_80181AC8(temp_r29->data.players[0].c_kind, 0x26, temp_r3_3->x2);
}

void gm_801B8AF8(MinorScene* arg0)
{
    UnkMultimanData* temp_r3_2;
    VsModeData* temp_r30;
    s32* temp_r31;
    MatchExitInfo* temp_r3;
    PAD_STACK(8);

    temp_r30 = &gmMainLib_804D3EE0->unk_1490;
    temp_r3 = gm_801A4284(arg0);
    if (temp_r3->match_end.result == 8) {
        gm_SetScenePendingMinor(1);
        return;
    }
    gm_80162968(temp_r3->match_end.frame_count / 60);
    gm_8016247C(temp_r3->match_end.player_standings[0].xE);
    gm_80182578();
    temp_r31 =
        gmMainLib_8015D7D4(gm_80164024((u8) temp_r30->data.players[0].c_kind));
    temp_r3_2 =
        gm_80182DF0((s32) (s8) (u8) temp_r30->data.players[0].c_kind, 0x26);
    *temp_r31 = (s32) temp_r3_2->x2;
    if (!gm_801B688C(temp_r3_2->x0_0)) {
        gm_SetScenePendingMinor(0);
    }
}
