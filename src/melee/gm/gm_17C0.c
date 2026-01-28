#include "gm_17C0.h"

#include "gm_unsplit.h"

#include <math_ppc.h>
#include <dolphin/gx.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/random.h>
#include <sysdolphin/baselib/tobj.h>
#include <sysdolphin/baselib/util.h>
#include <melee/cm/camera.h>
#include <melee/db/db.h>
#include <melee/ef/efasync.h>
#include <melee/ef/eflib.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ftbosslib.h>
#include <melee/ft/ftlib.h>
#include <melee/gm/gmadventure.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/types.h>
#include <melee/gr/ground.h>
#include <melee/gr/grpushon.h>
#include <melee/gr/stage.h>
#include <melee/it/item.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbbgflash.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lbcardnew.h>
#include <melee/lb/lbtime.h>
#include <melee/mp/mpcoll.h>
#include <melee/pl/player.h>
#include <melee/sc/types.h>

struct lbl_80472D28_t {
    /*   +0 */ char pad_0[0x104];
    /* +104 */ int x104;
    /* +108 */ char pad_108[0xE];
    /* +116 */ u8 x116;
};

struct lbl_80472E48_t {
    /* 0x00 */ char pad_0[4];
    /* 0x04 */ s32 unk_4;        /* inferred */
    /* 0x08 */ s32 unk_8;        /* inferred */
    /* 0x0C */ char pad_C[0x74]; /* maybe part of unk_8[0x1E]? */
}; /* size = 0x80 */
STATIC_ASSERT(sizeof(struct lbl_80472E48_t) == 0x80);

/// Adventure mode stage data table entry (size 0x1A)
/// Table has 110 entries: 22 stages × 5 difficulty levels
/// Indexed as: difficulty * 5 + stage_slot
typedef struct AdventureStageEntry {
    /* 0x00 */ u8 stage_kind;
    /* 0x01 */ u8 pad_1;
    /* 0x02 */ u16 scale0_pct; ///< Divided by 100 to get ratio
    /* 0x04 */ u16 scale1_pct; ///< Divided by 100 to get ratio
    /* 0x06 */ u8 pad_6[0x14];
} AdventureStageEntry;
STATIC_ASSERT(sizeof(AdventureStageEntry) == 0x1A);

/// Allstar mode stage data table entry (size 0x1A)
/// Table has 55 entries: 11 stages × 5 difficulty levels
typedef struct AllstarStageEntry {
    /* 0x00 */ u8 stage_kind;
    /* 0x01 */ u8 pad_1;
    /* 0x02 */ u16 scale0_pct; ///< Divided by 100 to get ratio
    /* 0x04 */ u16 scale1_pct; ///< Divided by 100 to get ratio
    /* 0x06 */ u8 pad_6[0xA];
    /* 0x10 */ u16 scale2_pct; ///< Divided by 100 to get ratio
    /* 0x12 */ u16 scale3_pct; ///< Divided by 100 to get ratio
    /* 0x14 */ u8 pad_14[0x6];
} AllstarStageEntry;
STATIC_ASSERT(sizeof(AllstarStageEntry) == 0x1A);

extern AdventureStageEntry lbl_803D7AC0[110];
extern AllstarStageEntry lbl_803D85F0[55];

static struct lbl_804706C0_t {
    int x0;
    int x4;
    int x8;
    int xC; // HP (stamina)
    int x10;
    int x14;
} lbl_804706C0;

static UnkAdventureData lbl_80472C30;
static UnkAllstarData lbl_80472CB0;
static struct lbl_80472D28_t lbl_80472D28;
static struct lbl_80472E48_t lbl_80472E48;
static int lbl_80472EC8[4];

void fn_8017C0C8(void)
{
    PlayerInitData sp8;
    gm_8016795C(&sp8);
    sp8.slot_type = Gm_PKind_Cpu;
    sp8.stocks = 1;
    sp8.xE = 4;
    sp8.cpu_level = Player_GetCpuLevel(2);
    sp8.xE = Player_GetCpuType(2);
    sp8.x18 = Player_GetAttackRatio(2);
    sp8.x1C = Player_GetUnk50(2);
    sp8.color = 0;
    sp8.c_kind = CKIND_CREZYH;
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
            temp_r3_2 = gm_8016AE38();
            temp_r3_2->x24C8.x2_4 = false;
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
            gm_8016AE38();
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
            gm_8016AE38();
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
        temp_r3_4 = gm_8016AE38();
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
            temp_r3_4 = gm_8016AE38();
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
            temp_r3_4 = gm_8016AE38();
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
    HSD_GObjProc_8038FD54(GObj_Create(0xF, 0x11, 0), fn_8017C1A4, 0x15);
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
    temp_r31 = gm_8016AE44();
    temp_r31->timer_seconds = grPushOn_80219230(temp_r30->ckind);
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

    temp_r30 = gm_8017E424();
    temp_r3 = gm_8016AE38();
    var_r31 = sp10;
    sp10[0] = FTKIND_NONE;
    sp10[1] = FTKIND_NONE;
    sp10[2] = FTKIND_NONE;
    switch (temp_r3->x24C8.xE) {
    case 0x3B:
        sp10[0] = FTKIND_YOSHI;
        break;
    case 0x3F:
        sp10[0] = FTKIND_LINK;
        break;
    case 0x44:
        sp10[0] = FTKIND_KIRBY;
        if (temp_r30->x0.ckind == CKIND_KIRBY && temp_r30->x0.color == 0) {
            var_r3 = 1;
        } else {
            var_r3 = 0;
        }
        ftLib_80087610(var_r3);
        break;
    case 0x48:
        sp10[0] = 0xC;
        if (gm_80164840(CKIND_PICHU) != 0) {
            sp10[1] = FTKIND_PICHU;
        }
        if (gm_80164840(CKIND_PURIN) != 0) {
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

extern u8 lbl_803B7C08[][5];

void gm_8017C9A8(DebugGameOverData* arg0, Unk1PData* arg1, u8 arg2)
{
    PAD_STACK(8);
    arg0->x0 = arg1->xC.x18;
    arg0->x8 = arg2;
    arg0->ckind = arg1->ckind;
    arg0->slot = arg1->slot;
    arg0->x15 = arg1->x4;
    arg0->x18 = gm_801623D8();
    arg0->x16 = lbl_803B7C08[arg2][arg1->cpu_level];
}

void gm_8017CA38(DebugGameOverData* arg0, Unk1PData* arg1, gmm_x0_528_t* arg2,
                 u8 arg3)
{
    u8 temp_r31;

    arg1->xC.x14 = arg0->x18;
    gm_801623FC(arg1->xC.x14);
    if (arg0->xC == 0) {
        temp_r31 = gm_80173224(arg3, 0);
        switch (gm_801A4310()) {
        case 3:
            fn_80162BFC(arg1->ckind, arg0->x4);
            break;
        case 4:
            fn_80162DF8(arg1->ckind, arg0->x4);
            break;
        case 5:
            fn_80162FF4(arg1->ckind, arg0->x4);
            break;
        }
        Ground_801C5A60();
        gm_8017390C(fn_8017DF90(), 0);
        gm_80173EEC();
        gm_80172898(0x40);
        if (temp_r31 == CHKIND_NONE) {
            if (gm_80173754(1, arg1->slot) == 0) {
                gm_801A42F8(1);
            }
        } else {
            gm_801736E8(arg1->ckind, arg1->color, arg1->slot, arg1->x4,
                        temp_r31, 1U);
            gm_801A42F8(0x14);
        }
    } else {
        arg1->xC.x18 = lbTime_8000AEC8((u32) arg0->x4, 1U);
        arg1->stocks = arg2->stocks;
        arg1->xC.xD = lbTime_8000AF74((u32) arg1->xC.xD, 1);
        gm_SetScenePendingMinor(arg1->x7);
    }
}

void gm_8017CBAC(UnkAdventureData* arg0, gmm_x0_528_t* arg1, u8 arg2)
{
    s32 temp_r3_2;
    u8 temp_r31;
    u8* temp_r3;

    temp_r31 = gm_80164024(arg0->x0.ckind);
    Ground_801C5A60();
    switch (arg2) {
    case 21:
        gmMainLib_8015D134(temp_r31);
        fn_80162BFC(arg0->x0.ckind, arg0->x0.xC.x18);
        temp_r3 = gmMainLib_8015D194(temp_r31);
        if (*temp_r3 < arg0->x0.cpu_level) {
            *temp_r3 = arg0->x0.cpu_level;
        }
        temp_r3_2 = gmMainLib_8015D1AC(temp_r31);
        if ((arg0->x0.cpu_level == 4) &&
            ((temp_r3_2 == 0) || (arg1->stocks < temp_r3_2)))
        {
            gmMainLib_8015D1C8(temp_r31, arg1->stocks);
        }
        break;
    case 22:
        gmMainLib_8015D25C(temp_r31);
        fn_80162DF8(arg0->x0.ckind, arg0->x0.xC.x18);
        temp_r3 = gmMainLib_8015D2BC(temp_r31);
        if (*temp_r3 < arg0->x0.cpu_level) {
            *temp_r3 = arg0->x0.cpu_level;
        }
        temp_r3_2 = gmMainLib_8015D2D4(temp_r31);
        if ((arg0->x0.cpu_level == 4) &&
            ((temp_r3_2 == 0) || (arg1->stocks < temp_r3_2)))
        {
            gmMainLib_8015D2F0(temp_r31, arg1->stocks);
        }
        break;
    case 23:
        gmMainLib_8015D384(temp_r31);
        fn_80162FF4(arg0->x0.ckind, arg0->x0.xC.x18);
        if (!gm_80164430(0x1F)) {
            gm_80164504(0x1F);
        }
        temp_r3 = gmMainLib_8015D3E4(temp_r31);
        if (*temp_r3 < arg0->x0.cpu_level) {
            *temp_r3 = arg0->x0.cpu_level;
        }
        temp_r3_2 = gmMainLib_8015D3FC(temp_r31);
        if ((arg0->x0.cpu_level == 4) &&
            (temp_r3_2 == 0 || arg1->stocks < temp_r3_2))
        {
            gmMainLib_8015D418(temp_r31, arg1->stocks);
        }
        break;
    }
    lb_8001C550();
    lb_8001D164(0);
    lb_8001CE00();
    gm_801A42E8(arg2);
    gm_801A42D4();
}

/// #gm_8017CD94

/// #gm_8017CE34

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
    if (arg0->match_end.player_standings[0].character_id == 7) {
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
    temp_r0 = arg0->match_end.result;
    if ((temp_r0 == 7 || temp_r0 == 8) && g_debugLevel <= 2) {
        switch (gm_801A4310()) {
        case 3:
            fn_80162BFC(arg1->ckind, arg1->xC.x18);
            break;
        case 4:
            fn_80162DF8(arg1->ckind, arg1->xC.x18);
            break;
        case 5:
            fn_80162FF4(arg1->ckind, arg1->xC.x18);
            break;
        }
        gm_801A42F8(1);
        return 0;
    }
    fn_8017E3C8();
    if (!(arg1->x8 & 0x80)) {
        arg1->stocks = arg0->match_end.player_standings[0].stocks;
        if (arg1->stocks != 0) {
            if (arg0->match_end.result == 1) {
                arg1->stocks--;
                if (arg1->stocks == 0) {
                    gm_SetScenePendingMinor(arg2);
                    return 0;
                }
                if (!(arg1->x8 & 0x40)) {
                    arg1->xC.x10++;
                    gm_SetScenePendingMinor(gm_801A42C4());
                    return 0;
                }
            }
        } else {
            arg1->xC.x10 = 0;
            gm_SetScenePendingMinor(arg2);
            return 0;
        }
    }
    arg1->xC.x18 = arg0->x0;
    arg1->xC.x10 = 0;
    return 1;
}

/// #fn_8017D9C0

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

/// #gm_8017DB88

/// #fn_8017DD7C

/// #fn_8017DE54

Unk1PData* fn_8017DEC8(int arg0)
{
    switch (arg0) {
    case 0:
        return &gm_8017E424()->x0;
    case 1:
        return &gm_8017EB30()->x0;
    case 2:
        return &gm_80473A18.x0;
    default:
        return NULL;
    }
}

Unk1PData* fn_8017DF28(void)
{
    switch (gm_801A4310()) {
    case MJ_CLASSIC:
        return &gm_8017EB30()->x0;
    case MJ_ADVENTURE:
        return &gm_8017E424()->x0;
    case MJ_ALLSTAR:
        return &gm_80473A18.x0;
    default:
        return NULL;
    }
}

u8 fn_8017DF90(void)
{
    switch (gm_801A4310()) {
    case MJ_CLASSIC:
        return 1;
    case MJ_ADVENTURE:
        return 0;
    case MJ_ALLSTAR:
        return 2;
    default:
        return 3;
    }
}

int gm_8017DFF4(int arg0)
{
    Unk1PData* var_r3 = fn_8017DEC8(arg0);
    if (var_r3 != NULL) {
        return var_r3->cpu_level;
    }
    return -1;
}

int gm_8017E068(void)
{
    Unk1PData* var_r3 = fn_8017DF28();
    if (var_r3 != NULL) {
        return var_r3->cpu_level;
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

/// #fn_8017E21C

/// #gm_8017E280

/// #fn_8017E318

/// #fn_8017E3C8

UnkAdventureData* gm_8017E424(void)
{
    return &lbl_80472C30;
}

u8 gm_8017E430(void)
{
    return lbl_80472C30.x0.slot;
}

/// #gm_8017E440

int gm_8017E48C(MinorScene* scene)
{
    int count = 0;
    int i;
    for (i = 0; scene->idx != gm_803DE1B8_MinorScenes[i].idx; i++) {
        if (gm_803DE1B8_MinorScenes[i].info.class_id == 2) {
            count++;
        }
    }
    return count;
}

/// #gm_8017E4C4

/// Get adventure stage kind for given difficulty and stage slot.
/// The (u8) cast on difficulty is required - these functions are called
/// via function pointers typed as f32(*)(int, u8) in UnkAdventureData.
u8 gm_8017E500(int difficulty, u8 stage_slot)
{
    return lbl_803D7AC0[stage_slot + ((u8) difficulty * 5)].stage_kind;
}

f32 gm_8017E528(int difficulty, u8 stage_slot)
{
    return (f32) lbl_803D7AC0[stage_slot + ((u8) difficulty * 5)].scale0_pct /
           100.0F;
}

f32 gm_8017E578(int difficulty, u8 stage_slot)
{
    return (f32) lbl_803D7AC0[stage_slot + ((u8) difficulty * 5)].scale1_pct /
           100.0F;
}

/// #gm_8017E5C8

u8 gm_8017E5FC(int difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D7AC0[stage_slot + ((u8) difficulty * 5)].pad_6[1 + arg2 * 3];
}

u8 gm_8017E630(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D7AC0[stage_slot + (u8) difficulty * 5].pad_6[arg2 * 3 + 2];
}

f32 gm_8017E664(u8 difficulty, u8 stage_slot)
{
    return (f32) lbl_803D7AC0[stage_slot + (difficulty * 5)].scale0_pct /
           100.0F;
}

f32 gm_8017E6B4(u8 difficulty, u8 stage_slot)
{
    return (f32) lbl_803D7AC0[stage_slot + (difficulty * 5)].scale1_pct /
           100.0F;
}

u8 gm_8017E704(int difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D7AC0[stage_slot + ((u8) difficulty * 5)]
        .pad_6[0x0E + arg2 * 3];
}

/// #gm_8017E738

/// #gm_8017E76C

/// #gm_8017E7A0

bool gm_8017E7E0(void)
{
    return lbl_80472C30.x7C == 0x14;
}

/// #gm_8017E7FC

/// #fn_8017E8A4

UnkAllstarData* gm_8017EB30(void)
{
    return &lbl_80472CB0;
}

u8 gm_8017EB3C(u8 difficulty, u8 stage_slot)
{
    return lbl_803D85F0[stage_slot + (difficulty * 5)].stage_kind;
}

u8 gm_8017EB64(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D85F0[stage_slot + (difficulty * 5)].pad_6[arg2 * 3];
}

u8 gm_8017EB98(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D85F0[stage_slot + difficulty * 5].pad_6[arg2 * 3 + 1];
}

u8 gm_8017EBCC(u8 arg0, u8 arg1, u8 arg2)
{
    u8* p;
    s32 idx;
    idx = arg1 + arg0 * 5;
    p = (u8*) lbl_803D85F0;
    return p[idx * 0x1A + arg2 * 3 + 8];
}

f32 gm_8017EC00(u8 difficulty, u8 stage_slot)
{
    return (f32) lbl_803D85F0[stage_slot + (difficulty * 5)].scale2_pct /
           100.0F;
}

f32 gm_8017EC50(u8 difficulty, u8 stage_slot)
{
    return (f32) lbl_803D85F0[stage_slot + (difficulty * 5)].scale3_pct /
           100.0F;
}


u8 gm_8017ECA0(u8 arg0, u8 arg1, u8 arg2)
{
    return lbl_803D85F0[arg1 + ((u8) arg0 * 5)].pad_14[arg2 * 3];
}

/// #gm_8017ECD4

/// #gm_8017ED08

f32 gm_8017ED3C(u8 difficulty, u8 stage_slot)
{
    return (f32) lbl_803D85F0[stage_slot + (difficulty * 5)].scale0_pct /
           100.0F;
}

f32 gm_8017ED8C(u8 difficulty, u8 stage_slot)
{
    return (f32) lbl_803D85F0[stage_slot + (difficulty * 5)].scale1_pct /
           100.0F;
}

/// #fn_8017EDDC

/// #fn_8017EE40

int fn_8017F008(void)
{
    int r3 = fn_80171A88();
    if (r3 == 3) {
        return 4;
    } else if (r3 == 1) {
        return 1;
    } else if (r3 == 2) {
        return 8;
    } else if (r3 == 7) {
        return 0x20;
    } else if (r3 == 6) {
        return 0x80;
    } else if (r3 == 8) {
        return 0x40;
    } else if (r3 == 4) {
        return 0x10;
    } else {
        return 0xFD;
    }
}

/// #fn_8017F09C

/// #fn_8017F14C

/// #fn_8017F1B8

int fn_8017F294(void)
{
    return lbl_80472D28.x104;
}

/// #fn_8017F2A4

/// #fn_8017F47C

/// #fn_8017F608

/// #fn_8017FA1C

/// #fn_8017FBA4

/// #fn_8017FE54

/// #fn_8017FF1C

/// #fn_801803FC

/// #fn_80180630

int fn_80180AC0(void)
{
    if (lbl_80472D28.x116 == 1) {
        return 1;
    }
    return 0;
}
s32 gm_80180AE4(void)
{
    return lbl_80472EC8[0] * 0xA;
}

Fighter_GObj* gm_80180AF4(void)
{
    return Player_GetEntity(1);
}

/// #gm_80180B18

/// #gm_80180BA0

/// #fn_80180C14

/// #fn_80180C60

/// #fn_80181598

/// #fn_80181708

static SceneDesc* lbl_804D65CC;
static SceneDesc* lbl_804D65D0;
extern HSD_Archive* lbl_804D65C8;

void gm_80181998(void)
{
    lbl_804D65C8 = lbArchive_80016DBC("IfHrNoCn", &lbl_804D65CC,
                                      "ScInfCnt_scene_models", 0);
    lbl_804D65C8 = lbArchive_80016DBC("IfHrReco", &lbl_804D65D0,
                                      "ScInfCnt_scene_models", 0);
    fn_80181708();
}

void gm_80181A00(s32 arg0, s32 arg1)
{
    lbl_80472E48.unk_4 = arg0;
    lbl_80472E48.unk_8 = arg1;
}

static struct {
    u8 x0;
    u16 x2;
    int x4;
    int pad;
} lbl_80473594;

int gm_80181A14(void)
{
    return lbl_80473594.x0;
}

u32 gm_80181A24(void)
{
    return lbl_80473594.x2;
}

s32 gm_80181A34(void)
{
    return lbl_80473594.x4;
}

/// #gm_80181A44

/// #gm_80181AC8

/// #gm_80181B64

int fn_80181BFC(int* arg0)
{
    int i;
    int count = 0;

    for (i = 1; i < 6; i++) {
        if (Player_GetFalls(i) == 0 &&
            Player_GetPlayerSlotType(i) != Gm_PKind_NA)
        {
            count += 1;
        } else if (arg0 != NULL) {
            *arg0 = i;
        }
    }
    return count;
}

/// #fn_80181C80

/// #fn_80181E18

/// #gm_80182174

bool gm_80182510(void)
{
    switch (gm_801A4310()) {
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x26:
        return true;
    }
    return false;
}

/// #gm_80182554

/// #gm_80182578

/// #fn_80182B5C

/// #gm_80182DF0

extern u8 lbl_804D65E8;

void fn_80182F40(HSD_GObj* unused)
{
    int i;
    int temp_r31;
    int temp_r31_2;

    if (gm_801A36A0(4) & 0x1100) {
        lbAudioAx_80024C84();
        lbAudioAx_80023694();
        lbAudioAx_80024030(1);
        gm_801A4B60();
        gm_801A42E8(MJ_TITLE);
        gm_801A42D4();
        return;
    }
    if (gm_801A4BA8() >= 0x4B0) {
        lbAudioAx_80024C84();
        lbAudioAx_80023694();
        if (gm_801A42C4() == 3 && gmMainLib_8015DB00() % 2 == 0) {
            gmMainLib_8015DB18();
            gm_SetScenePendingMinor(0);
        }
        gm_801A4B60();
        return;
    }
    switch (lbl_804D65E8) {
    case 0:
        if (gm_801A4BA8() == 0x190) {
            lbl_804D65E8 = 1;
            temp_r31 = gm_801BF6D8();
            Camera_8002EEC8(60.0F);
            Camera_8002E6FC(temp_r31);
            Camera_8002ED9C(30.0F);
            Camera_8002EC7C(0.017453292F * (HSD_Randi(0x47) - 0x23));
            Camera_8002EB5C(0.017453292F * HSD_Randi(0x10));
            for (i = 0; i < 4; i++) {
                if (i != gm_801BF6D8()) {
                    Player_SetPlayerAndEntityCpuLevel(i, 2);
                }
                Player_SetMoreFlagsBit4(i, 1);
            }
        }
        break;
    case 1:
        if (gm_801A4BA8() == 0x280 || Player_800368F8(gm_801BF6D8()) == 0) {
            lbl_804D65E8 = 2;
            temp_r31_2 = gm_801BF6F8();
            Camera_8002EEC8(60.0F);
            Camera_8002E6FC(temp_r31_2);
            Camera_8002ED9C(30.0F);
            Camera_8002EC7C(0.017453292F * (HSD_Randi(0x47) - 0x23));
            Camera_8002EB5C(0.017453292F * HSD_Randi(0x10));
            Player_SetPlayerAndEntityCpuLevel(gm_801BF6F8(), 9);
            for (i = 0; i < 4; i++) {
                if (i != gm_801BF6F8()) {
                    Player_SetPlayerAndEntityCpuLevel(i, 2);
                }
            }
        }
        break;
    case 2:
        if (gm_801A4BA8() == 0x370 || Player_800368F8(gm_801BF6F8()) == 0) {
            Camera_8002F474();
            for (i = 0; i < 4; i++) {
                Player_SetPlayerAndEntityCpuLevel(i, 9);
                Player_SetMoreFlagsBit4(i, 0);
            }
        }
        break;
    case 3:
        break;
    }
}

void gm_80183218(void)
{
    lbl_804D65E8 = 0;
    HSD_GObjProc_8038FD54(GObj_Create(0xF, 0x11, 0), fn_80182F40, 0x15);
}
