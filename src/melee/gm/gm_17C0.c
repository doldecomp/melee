#include "gmregclear.h"
#include "platform.h"

#include "gm/forward.h"
#include <sysdolphin/baselib/forward.h>

#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/random.h>
#include <sysdolphin/baselib/tobj.h>
#include <melee/cm/camera.h>
#include <melee/db/db.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ftbosslib.h>
#include <melee/ft/ftlib.h>
#include <melee/gm/gm_18A1.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/gmregcommon.h>
#include <melee/gm/types.h>
#include <melee/gr/ground.h>
#include <melee/gr/grpushon.h>
#include <melee/gr/stage.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbbgflash.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lbcardnew.h>
#include <melee/lb/lbtime.h>
#include <melee/pl/player.h>
#include <melee/ty/toy.h>

typedef struct lbl_804706D8_t {
    s16 x0;
    u8 x2;
    u8 x3;
} lbl_804706D8_t;

static struct lbl_804706C0_t {
    int x0;
    int x4;
    int x8;
    int xC; // HP (stamina)
    int x10;
    int x14;
} lbl_804706C0;

static lbl_804706D8_t lbl_804706D8[12];

typedef struct RegClearCharEntry {
    /* 0x00 */ u8 x0;
    /* 0x01 */ u8 x1;
    /* 0x02 */ u8 x2;
    /* 0x03 */ u8 x3;
    /* 0x04 */ f32 x4;
    /* 0x08 */ f32 x8;
} RegClearCharEntry;

StartMeleeData gmClassic_80472AF8;
MatchExitInfo gmClassic_8047086C;
DebugGameOverData gmClassic_80470850;
CSSData gmClassic_80470708;

void fn_8017C0C8(void)
{
    PlayerInitData sp8;
    gm_SetupPlayerDefaults(&sp8);
    sp8.slot_type = Gm_PKind_Cpu;
    sp8.stocks = 1;
    sp8.cpu_kind = 4;
    sp8.cpu_level = Player_GetCpuLevel(2);
    sp8.cpu_kind = Player_GetCpuType(2);
    sp8.x18 = Player_GetAttackRatio(2);
    sp8.x1C = Player_GetUnk50(2);
    sp8.color = 0;
    sp8.ckind = CKIND_CREZYH;
    sp8.team = 4;
    sp8.xC_b7 = true;
    sp8.hp = lbl_804706C0.xC;
    sp8.xD_b2 = true;
    sp8.xD_b0 = true;
    sp8.xD_b2 = true;
    sp8.spawn_dir = 1;
    gm_8016EDDC(1, &sp8);
}

void fn_8017C1A4(HSD_GObj* unused)
{
    struct lbl_804706C0_t* tmp = &lbl_804706C0;
    int temp_r29;
    int temp_r29_2;
    int temp_r28;
    int temp_r27;
    int temp_r27_2;
    int temp_r31;
    int temp_r3;
    int temp_r3_3;
    lbl_8046B6A0_t* temp_r3_2;
    lbl_8046B6A0_t* temp_r3_4;
    PAD_STACK(8);

    temp_r31 = ftBossLib_8015C74C();
    temp_r29 = ftBossLib_8015C7EC();
    temp_r27 = ftBossLib_8015C88C();
    temp_r3 = ftBossLib_8015C9CC();
    switch (tmp->x0) {
    case 0:
        if (tmp->x8 == 0) {
            temp_r3_2 = gm_16AE_GetUnkData_0();
            temp_r3_2->x24C8.disable_pausing = false;
            temp_r3_2->hud_enabled = 0;
            lbAudioAx_800237A8(0x81650, 0x7F, 0x40);
            ftLib_80086824();
            tmp->x8 = 1;
        } else if (ftBossLib_8015C270() == 0) {
            tmp->x0 = 2;
        }
        break;
    case 1:
        if (tmp->x8 == 0) {
            gm_16AE_GetUnkData_0();
            lbAudioAx_800236DC();
            ftBossLib_8015CA6C(0x1D9);
            Player_SetMoreFlagsBit4(0, 1);
            Player_SetMoreFlagsBit3(0, 1);
            tmp->x10 = ft_80087C58(Player_GetEntity(0));
            ft_80087C64(Player_GetEntity(0), 2);
            tmp->x14 = ft_80087C58(Player_GetEntity(2));
            ft_80087C64(Player_GetEntity(2), 2);
            tmp->x8 = 1;
        } else if (tmp->x8 == 1) {
            lbAudioAx_800237A8(0x81651, 0x7F, 0x40);
            fn_8017C0C8();
            tmp->x8 = 2;
        } else if (ftBossLib_8015C2A8() == 0) {
            gm_16AE_GetUnkData_0();
            Stage_80225074(0);
            ftBossLib_8015CB7C();
            Player_SetMoreFlagsBit4(0, 0);
            Player_SetMoreFlagsBit3(0, 0);
            ft_80087C64(Player_GetEntity(0), tmp->x10);
            ft_80087C64(Player_GetEntity(2), tmp->x14);
            ftBossLib_8015CC14();
            tmp->x0 = 4U;
        }
        break;
    case 2:
        temp_r3_4 = gm_16AE_GetUnkData_0();
        temp_r3_4->hud_enabled = 1;
        Stage_80225074(0);
        ftLib_800868A4();
        ftBossLib_8015CC14();
        tmp->x0 = 3;
        break;
    case 3:
        if (Player_GetRemainingHP(2) <= 0) {
            tmp->x0 = 7;
            tmp->x8 = 0;
        } else if (Player_GetRemainingHP(2) <= 0.5F * tmp->xC && fn_8017EDDC())
        {
            tmp->x0 = 1;
            tmp->x8 = 0;
        }
        break;
    case 4:
        if (Player_GetRemainingHP(2) <= 0 && Player_GetRemainingHP(1) <= 0) {
            tmp->x0 = 7;
            tmp->x8 = 0;
        } else if (Player_GetRemainingHP(2) <= 0 ||
                   Player_GetRemainingHP(1) <= 0)
        {
            tmp->x0 = 6;
            tmp->x8 = 0;
        }
        break;
    case 5:
        if (Player_GetRemainingHP(2) <= 0 && Player_GetRemainingHP(1) <= 0) {
            tmp->x0 = 7;
            tmp->x8 = 0;
        }
        break;
    case 6:
        if (Player_GetRemainingHP(2) <= 0) {
            tmp->x4 = 2;
        } else {
            tmp->x4 = 1;
        }
        temp_r27_2 = temp_r31 + temp_r29;
        if (tmp->x8 == 0) {
            ftBossLib_8015CB9C(tmp->x4);
            gm_801A4634(6);
        } else if (tmp->x8 == temp_r31) {
            lbAudioAx_8002438C(0x4E200);
            ftBossLib_8015CC14();
            gm_801A4674(6);
            gm_SetGameSpeed(0.5f);
        } else if (tmp->x8 >= temp_r27_2) {
            gm_SetGameSpeed(1.0f);
            tmp->x0 = 5;
        }
        if (Player_GetRemainingHP(2) <= 0 && Player_GetRemainingHP(1) <= 0) {
            tmp->x0 = 7;
            tmp->x8 = 0;
        } else if (tmp->x8 <= temp_r27_2) {
            tmp->x8++;
        }
        break;
    case 7:
        temp_r28 = temp_r31 + temp_r27;
        temp_r29_2 = temp_r3 + temp_r28;
        if (tmp->x8 == 0) {
            temp_r3_4 = gm_16AE_GetUnkData_0();
            temp_r3_4->hud_enabled = 0;
            if (tmp->x4 == 2) {
                tmp->x4 = 1;
            } else {
                tmp->x4 = 2;
            }
            ftBossLib_8015CB9C(tmp->x4);
            gm_801A4634(6);
            Player_80031790(0);
            Player_80036844(0, 1);
            temp_r3_4 = gm_16AE_GetUnkData_0();
            temp_r3_4->x24C8.x0_6 = false;
        } else if (tmp->x8 == temp_r31) {
            lbAudioAx_8002438C(0x4E200);
            ftBossLib_8015CC14();
            gm_801A4674(6);
            gm_SetGameSpeed(0.5f);
            lbBgFlash_80020688(temp_r27);
        } else if (tmp->x8 == temp_r28) {
            lbBgFlash_800205F0(temp_r3);
        } else if (tmp->x8 >= temp_r29_2) {
            lbAudioAx_80028B90();
            gm_SetGameSpeed(1.0f);
            gm_8016B33C(8);
            gm_8016B328();
            break;
        }
        if (tmp->x8 >= temp_r31) {
            lbAudioAx_80028B6C();
        }
        if (tmp->x8 <= temp_r28 && tmp->x8 % 30 == 0) {
            gm_80167858(Player_GetPlayerId(0), Player_GetNametagSlotID(0), 2,
                        0x1E);
            Camera_80030E44(3, NULL);
        }
        if (tmp->x8 <= temp_r29_2) {
            tmp->x8++;
        }
        break;
    }
}

void fn_8017C71C(void)
{
    struct lbl_804706C0_t* tmp = &lbl_804706C0;
    HSD_GObj_SetupProc(GObj_Create(0xF, 0x11, 0), fn_8017C1A4, 0x15);
    tmp->x0 = 0;
    tmp->x4 = 1;
    tmp->x8 = 0;
    tmp->xC = ftBossLib_8015C530(gm_8017E068());
    Player_SetOtherStamina(2, tmp->xC);
    ftLib_80087508(FTKIND_CREZYH, 0);
}

void fn_8017C7A0(void)
{
    lbBgFlash_8002063C(0x30);
    if (Ground_801C1DAC()) {
        gm_8016B350(0x7C85E);
        return;
    }
    gm_8016B350(0x9C48);
}

void fn_8017C7EC(void)
{
    lbl_8046B6A0_t* temp_r31;
    Unk1PData* temp_r30;

    temp_r30 = fn_8017DF28();
    temp_r31 = gm_16AE_GetUnkData_1();
    temp_r31->timer_seconds = grPushOn_80219230(temp_r30->x0.ckind);
}

void gm_8017C838(void)
{
    s8 sp10[3];

    lbl_8046B6A0_t* temp_r3;
    int i;
    s8 var_r3;
    s8* var_r31;
    UnkAdventureData* temp_r30;

    PAD_STACK(8);

    temp_r30 = gm_GetAdventureData();
    temp_r3 = gm_16AE_GetUnkData_0();
    var_r31 = sp10;
    sp10[0] = FTKIND_NONE;
    sp10[1] = FTKIND_NONE;
    sp10[2] = FTKIND_NONE;
    switch (temp_r3->x24C8.stkind) {
    case 0x3B:
        sp10[0] = FTKIND_YOSHI;
        break;
    case 0x3F:
        sp10[0] = FTKIND_LINK;
        break;
    case 0x44:
        sp10[0] = FTKIND_KIRBY;
        if (temp_r30->x0.x0.ckind == CKIND_KIRBY && temp_r30->x0.x0.color == 0)
        {
            var_r3 = 1;
        } else {
            var_r3 = 0;
        }
        ftLib_80087610(var_r3);
        break;
    case 0x48:
        sp10[0] = 0xC;
        if (gm_IsCKindUnlocked(CKIND_PICHU) != 0) {
            sp10[1] = FTKIND_PICHU;
        }
        if (gm_IsCKindUnlocked(CKIND_PURIN) != 0) {
            sp10[2] = FTKIND_PURIN;
        }
        break;
    case 0x4C:
        sp10[0] = FTKIND_POPO;
        sp10[1] = FTKIND_NANA;
        break;
    case 0x4E:
        sp10[0] = FTKIND_BOY;
        sp10[1] = FTKIND_GIRL;
        break;
    }

    for (i = 0; i < 3; i++) {
        if (*var_r31 != FTKIND_MAX) {
            ftLib_80087574(*var_r31);
        }
        var_r31++;
    }
    Camera_80030E34(0.2f);
}

void gm_8017C984(UNK_T arg0)
{
    memzero(arg0, 0x74);
}

static const u8 lbl_803B7C08[3][5] = {
    { 1, 2, 3, 5, 10 },
    { 1, 2, 3, 5, 10 },
    { 10, 10, 10, 10, 10 },
};

void gm_8017C9A8(DebugGameOverData* arg0, Unk1PData* arg1, u8 arg2)
{
    PAD_STACK(8);
    arg0->x0 = arg1->xC.x18;
    arg0->x8 = arg2;
    arg0->ckind = arg1->x0.ckind;
    arg0->slot = arg1->x0.slot;
    arg0->x15 = arg1->x0.nametag;
    arg0->x18 = gm_801623D8();
    arg0->x16 = lbl_803B7C08[arg2][arg1->x0.cpu_level];
}

void gm_8017CA38(DebugGameOverData* arg0, Unk1PData* arg1, gmm_x0_528_t* arg2,
                 u8 arg3)
{
    u8 temp_r31;

    arg1->xC.x14 = arg0->x18;
    gm_801623FC(arg1->xC.x14);
    if (arg0->xC == 0) {
        temp_r31 = gm_80173224(arg3, 0);
        switch (gm_GetCurrentGameMode()) {
        case GM_CLASSIC:
            fn_80162BFC(arg1->x0.ckind, arg0->x4);
            break;
        case GM_ADVENTURE:
            fn_80162DF8(arg1->x0.ckind, arg0->x4);
            break;
        case GM_ALLSTAR:
            fn_80162FF4(arg1->x0.ckind, arg0->x4);
            break;
        }
        Ground_801C5A60();
        gm_8017390C(fn_8017DF90(), 0);
        gm_80173EEC();
        gm_80172898(0x40);
        if (temp_r31 == CHKIND_NONE) {
            if (gm_80173754(1, arg1->x0.slot) == 0) {
                gm_ChangeGameModeAfterCurrentScene(GM_MENU);
            }
        } else {
            gm_InitChallengerData(arg1->x0.ckind, arg1->x0.color,
                                  arg1->x0.slot, arg1->x0.nametag, temp_r31,
                                  1U);
            gm_ChangeGameModeAfterCurrentScene(GM_CHALLENGER_APPROACH);
        }
    } else {
        arg1->xC.x18 = lbTime_8000AEC8((u32) arg0->x4, 1U);
        arg1->x0.stocks = arg2->stocks;
        arg1->xC.xD = lbTime_8000AF74((u32) arg1->xC.xD, 1);
        gm_SetNextGameModeStateId(arg1->x0.mode);
    }
}

void gm_8017CBAC(UnkAdventureData* arg0, gmm_x0_528_t* arg1, u8 arg2)
{
    s32 temp_r3_2;
    u8 temp_r31;
    u8* temp_r3;

    temp_r31 = gm_CKindToSelKind(arg0->x0.x0.ckind);
    Ground_801C5A60();
    switch (arg2) {
    case 21:
        gmMainLib_8015D134(temp_r31);
        fn_80162BFC(arg0->x0.x0.ckind, arg0->x0.xC.x18);
        temp_r3 = gmMainLib_8015D194(temp_r31);
        if (*temp_r3 < arg0->x0.x0.cpu_level) {
            *temp_r3 = arg0->x0.x0.cpu_level;
        }
        temp_r3_2 = gmMainLib_8015D1AC(temp_r31);
        if ((arg0->x0.x0.cpu_level == 4) &&
            ((temp_r3_2 == 0) || (arg1->stocks < temp_r3_2)))
        {
            gmMainLib_8015D1C8(temp_r31, arg1->stocks);
        }
        break;
    case 22:
        gmMainLib_8015D25C(temp_r31);
        fn_80162DF8(arg0->x0.x0.ckind, arg0->x0.xC.x18);
        temp_r3 = gmMainLib_8015D2BC(temp_r31);
        if (*temp_r3 < arg0->x0.x0.cpu_level) {
            *temp_r3 = arg0->x0.x0.cpu_level;
        }
        temp_r3_2 = gmMainLib_8015D2D4(temp_r31);
        if ((arg0->x0.x0.cpu_level == 4) &&
            ((temp_r3_2 == 0) || (arg1->stocks < temp_r3_2)))
        {
            gmMainLib_8015D2F0(temp_r31, arg1->stocks);
        }
        break;
    case 23:
        gmMainLib_8015D384(temp_r31);
        fn_80162FF4(arg0->x0.x0.ckind, arg0->x0.xC.x18);
        if (!gm_80164430(0x1F)) {
            gm_80164504(0x1F);
        }
        temp_r3 = gmMainLib_8015D3E4(temp_r31);
        if (*temp_r3 < arg0->x0.x0.cpu_level) {
            *temp_r3 = arg0->x0.x0.cpu_level;
        }
        temp_r3_2 = gmMainLib_8015D3FC(temp_r31);
        if ((arg0->x0.x0.cpu_level == 4) &&
            (temp_r3_2 == 0 || arg1->stocks < temp_r3_2))
        {
            gmMainLib_8015D418(temp_r31, arg1->stocks);
        }
        break;
    }
    lbCardNew_AllocWorkArea();
    lbCardGame_LoadArchive(0);
    lbCardGame_UpdatePowerTime();
    gm_SetPendingGameMode(arg2);
    gm_SetNewGameModePending();
}

u8 gm_8017CD94(UnkAdventureData* arg0, int arg1, int arg2, int arg3)
{
    u8 num_colors;
    u8 result;

    num_colors = gm_80169238(arg1);
    if (arg0->x0.x54 != NULL) {
        result = arg0->x0.x54(arg2, arg0->x0.x0.cpu_level, arg3);
        if (num_colors != 0) {
            return result % num_colors;
        }
        return 0;
    }
    return 0;
}

static inline s32 gm_8017CE34_CountEnemies(const s8* arg0)
{
    s32 count = 0;
    s32 i;

    for (i = 0; i < 3; i++) {
        if ((s32) arg0[i] != 0x21) {
            count++;
        }
    }
    return count;
}

static inline void gm_8017CE34_SetupColors(Unk1PData* arg1, s32 count,
                                           s8* arg2, u8* colors)
{
    s32 color_idx;
    u8* out_color = colors;
    u8 num_colors;
    u8 result;

    for (color_idx = 0; color_idx < 3; color_idx++) {
        num_colors = gm_80169238((u8) arg2[color_idx]);
        if (arg1->x54 != NULL) {
            result = arg1->x54(count, arg1->x0.cpu_level, color_idx);
            if (num_colors != 0) {
                result %= num_colors;
            } else {
                result = 0;
            }
        } else {
            result = 0;
        }
        *out_color = result;
        out_color++;
    }
}

static inline u8 gm_8017CE34_GetCpuLevel(Unk1PData* arg1)
{
    return arg1->x0.cpu_level;
}

void gm_8017CE34(StartMeleeData* arg0, Unk1PData* arg1, s8* arg2, u8 arg3,
                 u8 arg4, u8 arg5, s32 arg6, StKind arg7, s32 count, s32 arg9)
{
    u8 colors[16];
    u8 enemy_level;
    s32 boss_count;
    u8 enemy_cpu_type;
    s32 player_idx;
    f32 attack_ratio;
    u8 player_stocks;
    u8 player_ckind;
    s32 flags;
    s8* enemy_kind;
    f32 defense_ratio;
    u8 enemy_ckind;
    s32 enemy_count;
    s32 enemy_idx;
    u8* color_iter;

    PAD_STACK(4);

    boss_count = 0;
    enemy_level = 0;
    enemy_cpu_type = 0;
    arg1->xC.xC = 1;
    fn_8017E21C();
    fn_8016F030(arg0);
    arg0->rules.x30 = 1.0f;
    arg0->rules.x4_4 = 1;

    switch (arg9) {
    case 0:
        arg0->rules.xA = 0;
        break;
    case 1:
        arg0->rules.xA = 3;
        break;
    case 2:
        arg0->rules.xA = 2;
        break;
    }

    arg0->rules.x1_1 = 1;
    arg0->rules.x4_2 = 1;
    arg0->rules.x4_3 = 1;
    arg0->rules.x2_5 = 0;
    arg0->rules.x0_3 = arg1->xB;

    if (arg6 != 0) {
        arg0->rules.time_limit = (u32) arg6;
        arg0->rules.x0_6 = 1;
    } else {
        arg0->rules.x0_6 = 0;
    }

    arg0->rules.x18 = (u32) arg1->xC.x18;
    arg0->rules.stkind = (u16) arg7;
    arg0->rules.xB = arg1->x48((u8) count, arg1->x0.cpu_level);

    arg0->rules.x20 = (u64) -1;

    enemy_count = gm_8017CE34_CountEnemies(arg2);
    if (enemy_count == 0) {
        arg0->rules.x5_1 = 1;
    }
    if (arg1->x8 & 1) {
        arg0->rules.x2_7 = 1;
    }
    if (arg1->x8 & 0x20) {
        arg0->rules.x4_5 = 1;
    }
    if (arg1->x8 & 0x80) {
        arg1->xC.xC = 5;
        switch ((s32) arg1->x9) {
        case 1:
            arg0->rules.on_pause_override = gm_80165290;
            arg0->rules.x9 = 1;
            arg0->rules.x3_1 = 0;
            arg0->players[0].xC_b1 = 0;
            break;
        case 2:
            arg0->rules.x9 = 3;
            arg0->rules.x44 = fn_8017C7EC;
            break;
        case 3:
            arg0->rules.x9 = 2;
            arg0->rules.x7 = 9;
            arg0->rules.x4_4 = 0;
            arg0->rules.x50 = (void (*)(u8)) fn_8017C7A0;
            arg0->rules.xD = 0x30;
            break;
        }
    }

    if ((arg1->x8 & 0x80) != 0) {
        player_stocks = 1;
    } else {
        player_stocks = arg1->x0.stocks;
    }

    if ((arg1->x0.ckind == CKIND_ZELDA) && (arg1->xC.x12 != 0)) {
        player_ckind = CKIND_SEAK;
    } else if (((arg1->x8 & 0x80) != 0) && (arg1->x9 == 1) &&
               (arg1->x0.ckind == CKIND_POPONANA))
    {
        player_ckind = CHKIND_POPO;
    } else {
        player_ckind = (u8) arg1->x0.ckind;
    }

    gm_SetupHumanPlayer(arg0->players, player_ckind, arg1->x0.color,
                        player_stocks, arg1->x0.slot);
    arg0->players[0].nametag = arg1->x0.nametag;
    arg0->players[0].spawn_dir = (s8) arg1->xA;

    {
        u8 team_color;
        if (arg1->x58 != NULL) {
            team_color =
                arg1->x58((u8) count, gm_8017CE34_GetCpuLevel(arg1), 0);
        } else {
            team_color = 0;
        }

        {
            player_idx =
                fn_8017DD7C(arg0->players, arg1->xC.x24, team_color) + 1;
            arg0->rules.is_teams = 1;
        }
    }

    attack_ratio = arg1->x64((u8) count, arg1->x0.cpu_level);
    defense_ratio = arg1->x68((u8) count, arg1->x0.cpu_level);

    color_iter = colors;
    gm_8017CE34_SetupColors(arg1, count, arg2, color_iter);

    {
        s32 temp_r3_4 = arg1->x8 & 8;
        if ((temp_r3_4 != 0) && (arg1->xC.x11 == 0)) {
            s32 base_enemy_count;
            s32 event_enemy_count;
            s32 special_stage;
            s32 special_enemy_mode;
            u8 sp8;
            u8 first_enemy;
            u32 stage_flags;

            base_enemy_count = gm_8017CE34_CountEnemies(arg2);
            arg1->xC.xC = 3;
            event_enemy_count = base_enemy_count;
            special_stage = 0;
            special_enemy_mode = 0;
            sp8 = 0;
            if (arg1->x4C != NULL) {
                enemy_level = arg1->x4C((u8) count, arg1->x0.cpu_level, 0U);
            }

            first_enemy = (u8) arg2[0];
            if ((s8) first_enemy != 4) {
                if ((u8) (first_enemy - 0x1B) <= 1U) {
                    arg0->rules.x0_3 = 6;
                    event_enemy_count = 5;
                    colors[0] = 0;
                    special_stage = 1;
                    special_enemy_mode = 1;
                } else if (((s8) first_enemy == 0xD) &&
                           (((s32) arg2[1] != 0xD) || ((s32) arg2[2] != 0xD)))
                {
                    special_enemy_mode = 2;
                }
            }

            stage_flags = Ground_801C5AD0(Stage_8022519C(arg7));

            gm_8016A22C((s8) (u8) arg2[0], arg2[1], arg2[2], colors[0],
                        colors[1], colors[2], special_stage,
                        special_enemy_mode, sp8, (u8) arg1->x0.ckind,
                        arg1->x0.color, (s32) enemy_level, (s32) arg3,
                        event_enemy_count, (s32) stage_flags, (s32) arg5,
                        (s32) arg4, attack_ratio, defense_ratio);
            gm_8016A21C(&arg0->rules);
            arg1->xC.x11 = 0;
            if (arg1->x8 & 4) {
                fn_8016A450();
            }
            if ((u8) special_enemy_mode == 1) {
                fn_8016A46C();
                arg0->players[0].xC_b5 = 1;
            }
        } else if (temp_r3_4 != 0) {
            gm_8016A21C(&arg0->rules);
            arg1->xC.x11 = 0;
        }
    }

    gmRegSetupEnemyColorTable((s8) (u8) arg1->x0.ckind, arg1->x0.color, arg2,
                              colors);

    enemy_idx = 0;
    for (;;) {
        enemy_kind = &arg2[enemy_idx];
        if ((s32) (u8) enemy_kind[0] != 0x21) {
            if (arg1->x8 & 8) {
                if (arg1->x4C != NULL) {
                    enemy_level =
                        arg1->x4C((u8) count, arg1->x0.cpu_level, 0U);
                }
                if (arg1->x50 != NULL) {
                    enemy_cpu_type =
                        arg1->x50((u8) count, arg1->x0.cpu_level, 0U);
                }
            } else {
                if (arg1->x4C != NULL) {
                    u8 selected_enemy_level =
                        arg1->x4C((u8) count, arg1->x0.cpu_level, enemy_idx);
                    enemy_level = selected_enemy_level;
                }
                if (arg1->x50 != NULL) {
                    enemy_cpu_type =
                        arg1->x50((u8) count, arg1->x0.cpu_level, enemy_idx);
                }
            }
            gm_SetupPlayerDefaults(&arg0->players[player_idx]);
            arg0->players[player_idx].slot_type = 1;
            arg0->players[player_idx].ckind = (s8) (u8) enemy_kind[0];
            arg0->players[player_idx].stocks = 1;
            arg0->players[player_idx].cpu_level = enemy_level;
            arg0->players[player_idx].cpu_kind = enemy_cpu_type;
            arg0->players[player_idx].x18 = attack_ratio;
            arg0->players[player_idx].x1C = defense_ratio;
            arg0->players[player_idx].color = *color_iter;
            if (arg1->x8 & 2) {
                arg0->players[player_idx].x20 = 2.0f;
                arg0->players[player_idx].xB = 2;
            } else {
                arg0->players[player_idx].x20 = 1.0f;
                arg0->players[player_idx].xB = 0;
            }
            if (arg1->x8 & 4) {
                arg0->players[player_idx].xC_b2 = 1;
                arg0->players[player_idx].cpu_kind = 0x1B;
            }
            if ((s32) arg0->players[player_idx].ckind == CKIND_GKOOPS) {
                arg0->players[player_idx].xC_b1 = 0;
            }
            enemy_ckind = (u8) arg0->players[player_idx].ckind;
            if (((s8) enemy_ckind == CKIND_MASTERH) ||
                ((s8) enemy_ckind == CKIND_CREZYH))
            {
                arg0->players[player_idx].xC_b7 = 1;
                arg0->players[player_idx].hp = 0x12C;
                arg0->players[player_idx].xD_b2 = 1;
                arg0->players[player_idx].xD_b0 = 1;
                arg0->players[player_idx].xD_b2 = 1;
                arg0->players[player_idx].spawn_dir = -1;
                if ((s32) arg0->players[player_idx].ckind == CKIND_CREZYH) {
                    arg0->players[player_idx].slot_type = 3;
                }
                boss_count += 1;
            }
            if (arg0->rules.is_teams == 1) {
                arg0->players[player_idx].team = 4;
            }
            player_idx += 1;
            if (player_idx >= 6) {
                break;
            }
        } else {
            if ((enemy_idx == 0) && ((s32) enemy_kind[1] == 0x1A)) {
                arg0->players[player_idx].slot_type = 3;
                player_idx += 1;
            }
        }
        enemy_idx += 1;
        color_iter += 1;
        if (enemy_idx >= 3) {
            break;
        }
    }

    {
        s32 i;
        for (i = player_idx; i < 6; i++) {
            arg0->players[i].slot_type = 3;
        }
    }

    flags = arg1->x8;
    if (flags & 0x40) {
        arg1->xC.xC = 7;
    } else if (flags & 1) {
        if ((flags & 8) && (arg3 > 1U)) {
            arg1->xC.xC = 4;
        } else {
            arg1->xC.xC = 2;
        }
    }
    if (boss_count != 0) {
        arg0->rules.x1_2 = 1;
        arg0->rules.x1_3 = 1;
        arg0->rules.x1_4 = 1;
        arg0->rules.x0_3 = 3;
        arg0->rules.disable_pausing = 1;
        arg0->rules.x7 = 0;
        arg0->rules.x44 = (void (*)(void)) fn_8017C71C;
        arg1->xC.xC = 6;
    }
    if (arg7 == 0x49) {
        arg1->xC.xC = 8;
    }
}

bool gm_8017D7AC(MatchExitInfo* arg0, Unk1PData* arg1, u8 arg2)
{
    u8 temp_r0;

    arg1->xC.x14 =
        lbTime_8000AEC8(arg1->xC.x14, arg0->match_end.player_standings[0].xE);
    gm_8016247C(arg0->match_end.player_standings[0].xE);
    arg1->xC.x1C =
        lbTime_8000AEC8(arg1->xC.x1C, arg0->match_end.player_standings[0].x44);
    gm_80162968(arg0->match_end.frame_count / 60);
    if (!(arg1->x8 & 0x80)) {
        arg1->xC.x20 =
            lbTime_8000AEC8(arg1->xC.x20, arg0->match_end.frame_count);
    }
    if (arg0->match_end.player_standings[0].ftkind == 7) {
        arg1->xC.x12 = 1;
    } else {
        arg1->xC.x12 = 0;
    }
    if (fn_8016B510() != 0) {
        arg1->xC.xF = 1;
    }
    if (fn_8016B4BC() != 0) {
        arg1->xC.xE = 1;
    }
    temp_r0 = arg0->match_end.outcome;
    if ((temp_r0 == OUTCOME_NO_CONTEST || temp_r0 == OUTCOME_RETRY) &&
        DbLevel <= DbLKind_DebugDevelop)
    {
        switch (gm_GetCurrentGameMode()) {
        case GM_CLASSIC:
            fn_80162BFC(arg1->x0.ckind, arg1->xC.x18);
            break;
        case GM_ADVENTURE:
            fn_80162DF8(arg1->x0.ckind, arg1->xC.x18);
            break;
        case GM_ALLSTAR:
            fn_80162FF4(arg1->x0.ckind, arg1->xC.x18);
            break;
        }
        gm_ChangeGameModeAfterCurrentScene(GM_MENU);
        return 0;
    }
    fn_8017E3C8();
    if (!(arg1->x8 & 0x80)) {
        arg1->x0.stocks = arg0->match_end.player_standings[0].stocks;
        if (arg1->x0.stocks != 0) {
            if (arg0->match_end.outcome == OUTCOME_TIMEOUT) {
                arg1->x0.stocks--;
                if (arg1->x0.stocks == 0) {
                    gm_SetNextGameModeStateId(arg2);
                    return 0;
                }
                if (!(arg1->x8 & 0x40)) {
                    arg1->xC.x10++;
                    gm_SetNextGameModeStateId(gm_GetCurrentSceneIndex());
                    return 0;
                }
            }
        } else {
            arg1->xC.x10 = 0;
            gm_SetNextGameModeStateId(arg2);
            return 0;
        }
    }
    arg1->xC.x18 = arg0->x0;
    arg1->xC.x10 = 0;
    return 1;
}

#ifdef MUST_MATCH
#pragma opt_propagation off
#endif
static inline s32 pick_random_ckind(u8* arr, const u8* used_ckinds,
                                    const u8* preset_ckinds)
{
    struct {
        s32 count;
        u8* cursor;
    } scan;
    u8 temp;
    s32 j;
    s32 i;
    s32 swap_idx;
    u8 ckind;
    s32 used_idx;
    s32 preset_idx;
    u8* base;
    u8* w;
    u8* w2;

    base = arr;
    scan.cursor = base;
    scan.count = 0;
    while ((s32) *scan.cursor != CHKIND_NONE) {
        scan.cursor++;
        scan.count++;
    }

    w = base;
    for (j = 0; j < scan.count; j++) {
        temp = *w;
        swap_idx = HSD_Randi(scan.count);
        *w++ = base[swap_idx];
        base[swap_idx] = temp;
    }

    w2 = base;
    for (i = 0; i < scan.count; i++) {
        if (gm_IsCKindUnlocked(*w2) != 0) {
            ckind = *w2;
            for (used_idx = 0; used_idx < 4; used_idx++) {
                if ((s8) ckind == (s8) used_ckinds[used_idx]) {
                    used_idx = -1;
                    break;
                }
            }
            if (used_idx != -1) {
                for (preset_idx = 0; preset_idx < 3; preset_idx++) {
                    if ((s8) ckind == (s8) preset_ckinds[preset_idx]) {
                        preset_idx = -1;
                        break;
                    }
                }
                if (preset_idx != -1) {
                    return base[i];
                }
            }
        }
        w2++;
    }

    return CHKIND_NONE;
}

s32 fn_8017D9C0(const u8* used_ckinds, const u8* preset_ckinds)
{
    return pick_random_ckind(lbl_803D79F0, used_ckinds, preset_ckinds);
}
#ifdef MUST_MATCH
#pragma opt_propagation reset
#pragma dont_inline on
#endif

void gm_8017DB58(struct Unk1PData_x24* arg0)
{
    int i;
    for (i = 0; i < 3; i++) {
        arg0[i].ckind = CHKIND_NONE;
    }
}

u8 gm_8017DB6C(gm_8017DB6C_arg0_t* arg0, int index)
{
    return arg0[index].x0;
}

u8 gm_8017DB78(gm_8017DB6C_arg0_t* arg0, int index)
{
    return arg0[index].x1;
}

s32 gm_8017DB88(void* arg0, u8 arg1, s32 arg2, s32 arg3, u8* arg4, u8 arg5,
                u8 (*arg6)(s32, s32, u8), u8 (*arg7)(s32, s32, u8),
                u8 (*arg8)(s32, s32, u8), f32 (*arg9)(s32, s32),
                f32 (*arg10)(s32, s32))
{
    u8 chars[4];
    s32 val;
    f32 fval;

    {
        u8* p;
        RegClearCharEntry* out;
        s32 i;
        s32 count;

        count = fn_8017DE54(arg1, arg4);
        chars[1] = 0x21;
        out = arg0;
        chars[2] = 0x21;
        p = chars;
        i = 0;
        chars[3] = 0x21;
        chars[0] = arg5;
        for (; i < count; i++) {
            p[1] = fn_8017D9C0(chars, arg4);
            out->x0 = p[1];
            if (arg8 != NULL) {
                val = arg8(arg3, arg2, (u8) i);
            } else {
                val = 0;
            }
            out->x1 = val;
            if (arg6 != NULL) {
                val = arg6(arg3, arg2, (u8) i);
            } else {
                val = 0;
            }
            out->x2 = val;
            if (arg7 != NULL) {
                val = arg7(arg3, arg2, (u8) i);
            } else {
                val = 0;
            }
            out->x3 = val;
            if (arg9 != NULL) {
                fval = arg9(arg3, arg2);
            } else {
                fval = 0.0f;
            }
            out->x4 = fval;
            if (arg10 != NULL) {
                fval = arg10(arg3, arg2);
            } else {
                fval = 0.0f;
            }
            out->x8 = fval;
            p++;
            out++;
        }
        for (; i < 3; i++) {
            ((RegClearCharEntry*) arg0)[i].x0 = 0x21;
        }
        return count;
    }
}
#ifdef MUST_MATCH
#pragma dont_inline off

/// @todo .sdata2 order hack

#endif

s32 fn_8017DD7C(PlayerInitData* arg0, Unk1PData_x24* arg1, u8 arg2)
{
    s32 index = 1;
    int i;
    for (i = 0; i < 3; i++) {
        if (arg1[i].ckind != CHKIND_NONE) {
            gm_SetupPlayerDefaults(&arg0[index]);
            arg0[index].ckind = arg1[i].ckind;
            arg0[index].slot_type = 1;
            arg0[index].stocks = 1;
            arg0[index].team = arg0->team;
            arg0[index].color = arg1[i].x1;
            arg0[index].cpu_kind = arg1[i].x3;
            arg0[index].cpu_level = arg1[i].x2;
            arg0[index].x18 = arg1[i].x4;
            arg0[index].x1C = arg1[i].x8;
            arg0[index].xD_b1 = 1;
            if (arg0[index].ckind == CKIND_GKOOPS) {
                arg0[index].xC_b1 = 0;
            }
            index++;
        }
    }
    return index - 1;
}

s32 fn_8017DE54(u8 arg0, u8* arg1)
{
    u8* p;
    s32 count;

    if (arg0 & 0x20) {
        return 0;
    }
    if (arg0 & 0x10) {
        count = 0;
        if ((s32) arg1[0] != 0x21) {
            count = 1;
        }
        p = &arg1[1];
        if ((s32) *p != 0x21) {
            count += 1;
        }
        if ((s32) p[1] != 0x21) {
            count += 1;
        }
        return 3 - count;
    }
    if (arg0 & 2) {
        return 2;
    }
    return 0;
}

Unk1PData* fn_8017DEC8(int arg0)
{
    switch (arg0) {
    case 0:
        return &gm_GetAdventureData()->x0;
    case 1:
        return &gm_GetAllStarData()->x0;
    case 2:
        return &gm_80473A18.x0;
    default:
        return NULL;
    }
}

Unk1PData* fn_8017DF28(void)
{
    switch (gm_GetCurrentGameMode()) {
    case GM_CLASSIC:
        return &gm_GetAllStarData()->x0;
    case GM_ADVENTURE:
        return &gm_GetAdventureData()->x0;
    case GM_ALLSTAR:
        return &gm_80473A18.x0;
    default:
        return NULL;
    }
}

u8 fn_8017DF90(void)
{
    switch (gm_GetCurrentGameMode()) {
    case GM_CLASSIC:
        return 1;
    case GM_ADVENTURE:
        return 0;
    case GM_ALLSTAR:
        return 2;
    default:
        return 3;
    }
}

int gm_8017DFF4(int arg0)
{
    Unk1PData* var_r3 = fn_8017DEC8(arg0);
    if (var_r3 != NULL) {
        return var_r3->x0.cpu_level;
    }
    return -1;
}

int gm_8017E068(void)
{
    Unk1PData* var_r3 = fn_8017DF28();
    if (var_r3 != NULL) {
        return var_r3->x0.cpu_level;
    }
    return -1;
}

int fn_8017E0E4(void)
{
    Unk1PData* var_r3 = fn_8017DF28();
    if (var_r3 != NULL) {
        return var_r3->xC.xC;
    }
    return -1;
}

bool fn_8017E160(void)
{
    Unk1PData* var_r3 = fn_8017DF28();
    struct Unk1PData_xC* temp_r3_2;

    if (var_r3 != NULL) {
        int i;
        for (i = 0; i < 3; i++) {
            if (var_r3->xC.x24[i].ckind != CHKIND_NONE) {
                return true;
            }
        }
        return false;
    }
    return false;
}

void fn_8017E21C(void)
{
    int i;
    for (i = 0; i < 12; i++) {
        lbl_804706D8[i].x0 = -1;
    }
}

s8 gm_8017E280(u16 arg0, u32 arg1)
{
    lbl_804706D8_t* var_r7 = lbl_804706D8;
    s32 index;
    index = 0;
    for (index = 0; index < 12; index++) {
        if (arg0 == var_r7[index].x0) {
            var_r7[index].x2 += arg1;
            return var_r7[index].x2;
        }
    }
    index = 0;
    for (index = 0; index < 12; index++) {
        if (var_r7[index].x0 == -1) {
            var_r7[index].x0 = arg0;
            var_r7[index].x2 = arg1;
            return (u8) arg1;
        }
    }
    return -1;
}

int fn_8017E318(void)
{
    int i;
    int sum = 0;
    for (i = 0; i < 12; i++) {
        if (lbl_804706D8[i].x0 != -1) {
            sum += lbl_804706D8[i].x2;
        }
    }
    return sum;
}

void fn_8017E3C8(void)
{
    int i = 0;
    PAD_STACK(8);
    for (i = 0; i < 12; i++) {
        if (lbl_804706D8[i].x0 != -1) {
            Toy_SetUnlockState(lbl_804706D8[i].x0, lbl_804706D8[i].x2);
        }
    }
}
