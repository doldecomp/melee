#include "gmregclear.h"

#include "gm_unsplit.h"
#include "platform.h"

#include "baselib/forward.h"

#include <math_ppc.h>
#include <dolphin/gx.h>
#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/random.h>
#include <sysdolphin/baselib/sislib.h>
#include <sysdolphin/baselib/tobj.h>
#include <sysdolphin/baselib/util.h>
#include <melee/cm/camera.h>
#include <melee/db/db.h>
#include <melee/ef/efasync.h>
#include <melee/ef/eflib.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ftbosslib.h>
#include <melee/ft/ftlib.h>
#include <melee/gm/gm_1601.h>
#include <melee/gm/gm_1A36.h>
#include <melee/gm/gm_1B03.h>
#include <melee/gm/gmadventure.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/gmregcommon.h>
#include <melee/gm/types.h>
#include <melee/gr/ground.h>
#include <melee/gr/grpushon.h>
#include <melee/gr/stage.h>
#include <melee/if/ifcoget.h>
#include <melee/if/ifnametag.h>
#include <melee/if/ifstatus.h>
#include <melee/if/ifstock.h>
#include <melee/if/iftime.h>
#include <melee/it/item.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbbgflash.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lbcardnew.h>
#include <melee/lb/lblanguage.h>
#include <melee/lb/lbtime.h>
#include <melee/mp/mpcoll.h>
#include <melee/pl/player.h>
#include <melee/sc/types.h>
#include <melee/ty/toy.h>

typedef struct lbl_804706D8_t {
    s16 x0;
    u8 x2;
    u8 x3;
} lbl_804706D8_t;

lbl_804706D8_t lbl_804706D8[12];

struct lbl_80472D28_t {
    /*   +0 */ char pad_0[0x20];
    /* +20 */ HSD_JObj* x20;
    /* +24 */ HSD_JObj* x24;
    /* +28 */ char pad_28[4];
    /* +2C */ HSD_GObj* x2C;
    /* +30 */ HSD_ImageDesc x30;
    /* +48 */ HSD_Archive* x48;
    /* +4C */ DynamicModelDesc x4C;
    /* +5C */ void* x5C;
    /* +60 */ void* x60;
    /* +64 */ char pad_64[0x20];
    /* +84 */ HSD_Text* x84;
    /* +88 */ char pad_88[0x38];
    /* +C0 */ u16 xC0;
    /* +C2 */ u16 pad_C2;
    /* +C4 */ u32 xC4;
    /* +C8 */ u8 xC8;
    /* +C9 */ u8 pad_C9[3];
    /* +CC */ s32 xCC;
    /* +D0 */ s32 xD0;
    /* +D4 */ s32 xD4;
    /* +D8 */ s32 xD8;
    /* +DC */ s32 xDC;
    /* +E0 */ s32 xE0;
    /* +E4 */ s32 xE4;
    /* +E8 */ s32 xE8;
    /* +EC */ s32 xEC;
    /* +F0 */ s32 xF0;
    /* +F4 */ s32 xF4;
    /* +F8 */ s32 xF8;
    /* +FC */ s32 xFC;
    /* +100 */ s32 x100;
    /* +104 */ int x104;
    /* +108 */ s16 x108;
    /* +10A */ s16 x10A;
    /* +10C */ f32 x10C;
    /* +110 */ u32 x110;
    /* +114 */ u8 x114;
    /* +115 */ u8 x115;
    /* +116 */ u8 x116;
    /* +117 */ u8 x117;
    /* +118 */ u8 x118;
    /* +119 */ u8 x119;
    /* +11A */ u8 x11A;
    /* +11B */ u8 x11B;
    /* +11C */ u8 x11C;
    /* +11D */ u8 x11D;
    /* +11E */ u8 x11E;
    /* +11F */ u8 x11F;
};

struct lbl_80472E48_t {
    /* 0x00 */ u8 x0;
    /* 0x01 */ char pad_1[3];
    /* 0x04 */ s32 unk_4; /* inferred */
    /* 0x08 */ s32 unk_8; /* inferred */
    /* 0x0C */ u32 xC;
    /* 0x10 */ u8 x10;
    /* 0x11 */ char pad_11[3];
    /* 0x14 */ s32 x14[0x1B];
    /* 0x80 */ s32 x80;
    /* 0x84 */ s32 x84;
    /* 0x88 */ s32 x88;
    /* 0x8C */ s32 x8C;
}; /* size = 0x90 */
STATIC_ASSERT(sizeof(struct lbl_80472E48_t) == 0x90);

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
u16 lbl_803D8B88[] = { 0x18, 0x16, 0x12, 0x3, 0x5, 0x4, 0x6, 0x1a, 0x19, 0x7 };

typedef struct RegClearEv {
    /* 0x00 */ char pad_0[0x1C];
    /* 0x1C */ HSD_ImageDesc* x1C;
    /* 0x20 */ f32 x20;
} RegClearEv;

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
typedef struct RegClearSpawnEntry {
    /* 0x00 */ s32 x0;
    /* 0x04 */ u8 x4;
    /* 0x05 */ u8 x5;
    /* 0x06 */ u8 x6;
    /* 0x07 */ u8 x7;
    /* 0x08 */ f32 x8;
    /* 0x0C */ f32 xC;
} RegClearSpawnEntry;

typedef struct RegClearCharEntry {
    /* 0x00 */ u8 x0;
    /* 0x01 */ u8 x1;
    /* 0x02 */ u8 x2;
    /* 0x03 */ u8 x3;
    /* 0x04 */ f32 x4;
    /* 0x08 */ f32 x8;
} RegClearCharEntry;

struct {
    /* 0x000 */ s32 x0;
    /* 0x004 */ s32 x4;
    /* 0x008 */ s32 x8;
    /* 0x00C */ PlayerInitData xC;
    /* 0x030 */ u8 pad_30[0x24];
    /* 0x054 */ RegClearSpawnEntry x54[101];
    /* 0x6A4 */ RegClearSpawnEntry* x6A4;
    /* 0x6A8 */ RegClearSpawnEntry* x6A8;
    /* 0x6AC */ RegClearSpawnEntry* x6AC;
    /* 0x6B0 */ RegClearSpawnEntry* x6B0;
    /* 0x6B4 */ RegClearSpawnEntry* x6B4;
    /* 0x6B8 */ RegClearSpawnEntry* x6B8;
    /* 0x6BC */ u8 x6BC;
    /* 0x6BD */ u8 pad_6BD;
    /* 0x6BE */ u16 x6BE;
    /* 0x6C0 */ int x6C0;
    /* 0x6C4 */ int x6C4;
    /* 0x6C8 */ int x6C8;
    /* 0x6CC */ s8 x6CC;
    /* 0x6CD */ u8 x6CD;
} lbl_80472ED8;

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

u8 gm_8017CD94(UnkAdventureData* arg0, int arg1, int arg2, int arg3)
{
    u8 num_colors;
    u8 result;

    num_colors = gm_80169238(arg1);
    if (arg0->x54 != NULL) {
        result = arg0->x54(arg2, arg0->x0.cpu_level, arg3);
        if (num_colors != 0) {
            return result % num_colors;
        }
        return 0;
    }
    return 0;
}

s32 gm_8017CE34(StartMeleeData* arg0, UnkAdventureData* arg1, s8* arg2,
                u8 arg3, u8 arg4, u8 arg5, s32 arg6, InternalStageId arg7,
                s32 count, s32 arg9)
{
    u8 colors[3];
    s32 var_r20;
    u8 var_r22;
    u8 var_r21;
    s32 var_r28;
    s32 var_r4;
    u8 var_r6;
    s32 var_r4_2;
    u8 var_r3;
    s32 var_r25;
    s32 var_r25_3;
    s32 var_r23_2;
    s8* temp_r24;
    u8 temp_r0_2;
    f32 temp_f29;
    f32 temp_f28;
    u8* var_r26;
    s32 sp8;

    PAD_STACK(24);

    var_r20 = 0;
    var_r22 = 0;
    var_r21 = 0;
    arg1->x0.xC.xC = 1;
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
    arg0->rules.x0_3 = arg1->x0.xB;

    if (arg6 != 0) {
        arg0->rules.x10 = (u32) arg6;
        arg0->rules.x0_6 = 1;
    } else {
        arg0->rules.x0_6 = 0;
    }

    arg0->rules.x18 = (u32) arg1->x0.xC.x18;
    arg0->rules.xE = (u16) arg7;
    arg0->rules.xB = arg1->x48((u8) count, arg1->x0.cpu_level);

    var_r4 = 0;
    arg0->rules.x20 = (u64) -1;

    if ((s32) (u8) arg2[0] != 0x21) {
        var_r4 = 1;
    }
    {
        s8* p = &arg2[1];
        if ((s32) *p != 0x21) {
            var_r4 += 1;
        }
        if ((s32) p[1] != 0x21) {
            var_r4 += 1;
        }
    }
    if (var_r4 == 0) {
        arg0->rules.x5_1 = 1;
    }
    if (arg1->x0.x8 & 1) {
        arg0->rules.x2_7 = 1;
    }
    if (arg1->x0.x8 & 0x20) {
        arg0->rules.x4_5 = 1;
    }
    if (arg1->x0.x8 & 0x80) {
        arg1->x0.xC.xC = 5;
        switch ((s32) arg1->x0.x9) {
        case 1:
            arg0->rules.x3C = gm_80165290;
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

    if ((arg1->x0.x8 & 0x80) != 0) {
        var_r6 = 1;
    } else {
        var_r6 = arg1->x0.stocks;
    }

    var_r4_2 = (u8) arg1->x0.ckind;
    if ((var_r4_2 == 0x12) && ((u8) arg1->x0.xC.x12 != 0)) {
        var_r4_2 = 0x13;
    } else if (((arg1->x0.x8 & 0x80) != 0) && ((u8) arg1->x0.x9 == 1) &&
               ((s8) var_r4_2 == 0xE)) {
        var_r4_2 = 0x20;
    }

    gm_801B0620(arg0->players, var_r4_2, arg1->x0.color, var_r6,
                arg1->x0.slot);
    arg0->players[0].xA = arg1->x0.x4;
    arg0->players[0].spawn_dir = (s8) arg1->x0.xA;

    {
        u8 var_r5;
        if (arg1->x58 != NULL) {
            var_r5 = arg1->x58((u8) count, arg1->x0.cpu_level, 0);
        } else {
            var_r5 = 0;
        }

        {
            var_r28 =
                fn_8017DD7C(arg0->players, arg1->x0.xC.x24, var_r5) + 1;
            arg0->rules.is_teams = 1;
        }
    }

    temp_f29 = arg1->x64((u8) count, arg1->x0.cpu_level);
    temp_f28 = arg1->x68((u8) count, arg1->x0.cpu_level);

    var_r26 = colors;
    {
        u8* var_r24 = var_r26;
        s8* var_r18 = arg2;
        for (var_r25 = 0; var_r25 < 3; var_r25++) {
            u8 temp_r23 = gm_80169238((u8) *var_r18);
            u8 var_r0;
            if (arg1->x54 != NULL) {
                u8 temp_r3_3;
                temp_r3_3 = arg1->x54((u8) count, arg1->x0.cpu_level,
                                      (u8) var_r25);
                if (temp_r23 != 0) {
                    var_r0 = temp_r3_3 % temp_r23;
                } else {
                    var_r0 = 0;
                }
            } else {
                var_r0 = 0;
            }
            *var_r24 = var_r0;
            var_r24 += 1;
            var_r18 += 1;
        }
    }

    {
        s32 temp_r3_4 = arg1->x0.x8 & 8;
        if ((temp_r3_4 != 0) && ((u8) arg1->x0.xC.x11 == 0)) {
            s32 var_r4_3;
            s32 var_r23;
            s32 var_r24_2;
            s32 var_r25_2;
            u8 temp_r4;
            u32 temp_r3_5;

            var_r4_3 = 0;
            if ((s32) (u8) arg2[0] != 0x21) {
                var_r4_3 = 1;
            }
            {
                s8* p = &arg2[1];
                if ((s32) *p != 0x21) {
                    var_r4_3 += 1;
                }
                if ((s32) p[1] != 0x21) {
                    var_r4_3 += 1;
                }
            }
            arg1->x0.xC.xC = 3;
            var_r23 = var_r4_3;
            var_r24_2 = 0;
            var_r25_2 = 0;
            sp8 = 0;
            if (arg1->x4C != NULL) {
                var_r22 = arg1->x4C((u8) count, arg1->x0.cpu_level, 0U);
            }

            temp_r4 = (u8) arg2[0];
            if ((s8) temp_r4 != 4) {
                if ((u8) (temp_r4 - 0x1B) <= 1U) {
                    arg0->rules.x0_3 = 6;
                    var_r23 = 5;
                    colors[0] = 0;
                    var_r24_2 = 1;
                    var_r25_2 = 1;
                } else if (((s8) temp_r4 == 0xD) &&
                           (((s32) arg2[1] != 0xD) ||
                            ((s32) arg2[2] != 0xD))) {
                    var_r25_2 = 2;
                }
            }

            temp_r3_5 = Ground_801C5AD0(Stage_8022519C(arg7));

            gm_8016A22C((s8) (u8) arg2[0], (s8) arg2[1], (s8) arg2[2],
                        colors[0], colors[1], (s32) colors[2],
                        var_r24_2, var_r25_2,
                        sp8, (u8) arg1->x0.ckind, arg1->x0.color,
                        (s32) var_r22, (s32) arg3, var_r23,
                        (s32) temp_r3_5, (s32) arg5, (s32) arg4,
                        temp_f29, temp_f28);
            gm_8016A21C(&arg0->rules);
            arg1->x0.xC.x11 = 0;
            if (arg1->x0.x8 & 4) {
                fn_8016A450();
            }
            if ((u8) var_r25_2 == 1) {
                fn_8016A46C();
                arg0->players[0].xC_b5 = 1;
            }
        } else if (temp_r3_4 != 0) {
            gm_8016A21C(&arg0->rules);
            arg1->x0.xC.x11 = 0;
        }
    }

    gmRegSetupEnemyColorTable((s8) (u8) arg1->x0.ckind, arg1->x0.color,
                              arg2, colors);

    var_r25_3 = var_r28 * 0x24;
    var_r23_2 = 0;
    for (;;) {
        temp_r24 = &arg2[var_r23_2];
        if ((s32) (u8) temp_r24[0] != 0x21) {
            if (arg1->x0.x8 & 8) {
                if (arg1->x4C != NULL) {
                    var_r22 = arg1->x4C((u8) count, arg1->x0.cpu_level, 0U);
                }
                if (arg1->x50 != NULL) {
                    var_r21 =
                        arg1->x50((u8) count, arg1->x0.cpu_level, 0U);
                }
            } else {
                if (arg1->x4C != NULL) {
                    var_r22 = arg1->x4C((u8) count, arg1->x0.cpu_level,
                                        var_r23_2);
                }
                if (arg1->x50 != NULL) {
                    var_r21 = arg1->x50((u8) count, arg1->x0.cpu_level,
                                        var_r23_2);
                }
            }
            {
                PlayerInitData* p =
                    (PlayerInitData*) ((u8*) arg0 + var_r25_3 + 0x60);
                gm_8016795C(p);
                p->slot_type = 1;
                p->c_kind = (s8) (u8) temp_r24[0];
                p->stocks = 1;
                p->cpu_level = var_r22;
                p->xE = var_r21;
                p->x18 = temp_f29;
                p->x1C = temp_f28;
                p->color = *var_r26;
                if (arg1->x0.x8 & 2) {
                    p->x20 = 2.0f;
                    p->xB = 2;
                } else {
                    p->x20 = 1.0f;
                    p->xB = 0;
                }
                if (arg1->x0.x8 & 4) {
                    p->xC_b2 = 1;
                    p->xE = 0x1B;
                }
                if ((s32) p->c_kind == 0x1D) {
                    p->xC_b1 = 0;
                }
                temp_r0_2 = (u8) p->c_kind;
                if (((s8) temp_r0_2 == 0x1A) || ((s8) temp_r0_2 == 0x1E)) {
                    p->xC_b7 = 1;
                    p->hp = 0x12C;
                    p->xD_b2 = 1;
                    p->xD_b0 = 1;
                    p->xD_b2 = 1;
                    p->spawn_dir = -1;
                    if ((s32) p->c_kind == 0x1E) {
                        p->slot_type = 3;
                    }
                    var_r20 += 1;
                }
                if ((u8) arg0->rules.is_teams == 1) {
                    p->team = 4;
                }
            }
            var_r28 += 1;
            var_r25_3 += 0x24;
            if (var_r28 >= 6) {
                break;
            }
        } else {
            if (((s32) var_r23_2 == 0) && ((s32) temp_r24[1] == 0x1A)) {
                ((PlayerInitData*) ((u8*) arg0 + var_r25_3 + 0x60))
                    ->slot_type = 3;
                var_r28 += 1;
                var_r25_3 += 0x24;
            }
        }
        var_r23_2 += 1;
        var_r26 += 1;
        if ((s32) var_r23_2 >= 3) {
            break;
        }
    }

    {
        s32 i;
        for (i = var_r28; i < 6; i++) {
            arg0->players[i].slot_type = 3;
        }
    }

    var_r3 = arg1->x0.x8;
    if (var_r3 & 0x40) {
        arg1->x0.xC.xC = 7;
    } else if (var_r3 & 1) {
        if ((var_r3 & 8) && (arg3 > 1U)) {
            arg1->x0.xC.xC = 4;
        } else {
            arg1->x0.xC.xC = 2;
        }
    }
    if (var_r20 != 0) {
        arg0->rules.x1_2 = 1;
        arg0->rules.x1_3 = 1;
        arg0->rules.x1_4 = 1;
        arg0->rules.x0_3 = 3;
        arg0->rules.x2_4 = 1;
        arg0->rules.x7 = 0;
        arg0->rules.x44 = (void (*)(void)) fn_8017C71C;
        arg1->x0.xC.xC = 6;
    }
    if (arg7 == 0x49) {
        arg1->x0.xC.xC = 8;
    }
    return (s32) var_r3;
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

s32 fn_8017D9C0(u8* arg0, u8* arg1)
{
    s32 len;
    s32 i;
    u8* p;
    u8 temp;
    u8* dst;
    u8 ch;
    s32 var_r0;
    s32 var_r0_2;
    u8* base;

    base = lbl_803D79F0;
    p = base;
    len = 0;
    while ((s32) *p != 0x21) {
        p++;
        len++;
    }

    p = base;
    for (i = 0; i < len; i++) {
        temp = *p;
        dst = &base[HSD_Randi(len)];
        *p = *dst;
        p++;
        *dst = temp;
    }

    p = base;
    for (i = 0; i < len; i++) {
        if (gm_80164840(*p) != 0) {
            ch = *p;
            if ((s8) ch == (s8) arg0[0]) {
                var_r0 = -1;
            } else if ((s8) ch == (s8) arg0[1]) {
                var_r0 = -1;
            } else if ((s8) ch == (s8) arg0[2]) {
                var_r0 = -1;
            } else if ((s8) ch == (s8) arg0[3]) {
                var_r0 = -1;
            } else {
                var_r0 = 4;
            }
            if (var_r0 != -1) {
                if ((s8) ch == (s8) arg1[0]) {
                    var_r0_2 = -1;
                } else if ((s8) ch == (s8) arg1[1]) {
                    var_r0_2 = -1;
                } else if ((s8) ch == (s8) arg1[2]) {
                    var_r0_2 = -1;
                } else {
                    var_r0_2 = 3;
                }
                if (var_r0_2 != -1) {
                    return (s32) base[i];
                }
            }
        }
        p++;
    }

    return 0x21;
    PAD_STACK(8);
}

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

s32 gm_8017DB88(void* arg0, u8 arg1, s32 arg2, s32 arg3,
                u8* arg4, u8 arg5, u8 (*arg6)(s32, s32, u8),
                u8 (*arg7)(s32, s32, u8), u8 (*arg8)(s32, s32, u8),
                f32 (*arg9)(s32, s32), f32 (*arg10)(s32, s32))
{
    RegClearCharEntry* out;
    u8 chars[4];
    u8* p;
    s32 count;
    s32 i;
    u8 val;
    f32 fval;

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

s32 fn_8017DD7C(PlayerInitData* arg0, Unk1PData_x24* arg1, u8 arg2)
{
    s32 index = 1;
    int i;
    for (i = 0; i < 3; i++) {
        if (arg1[i].ckind != CHKIND_NONE) {
            gm_8016795C(&arg0[index]);
            arg0[index].c_kind = arg1[i].ckind;
            arg0[index].slot_type = 1;
            arg0[index].stocks = 1;
            arg0[index].team = arg0->team;
            arg0[index].color = arg1[i].x1;
            arg0[index].xE = arg1[i].x3;
            arg0[index].cpu_level = arg1[i].x2;
            arg0[index].x18 = arg1[i].x4;
            arg0[index].x1C = arg1[i].x8;
            arg0[index].xD_b1 = 1;
            if (arg0[index].c_kind == CKIND_GKOOPS) {
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
            Trophy_SetUnlockState(lbl_804706D8[i].x0, lbl_804706D8[i].x2);
        }
    }
}

UnkAdventureData* gm_8017E424(void)
{
    return &lbl_80472C30;
}

u8 gm_8017E430(void)
{
    return lbl_80472C30.x0.slot;
}

u8 gm_8017E440(void)
{
    UnkAdventureData* r31 = &lbl_80472C30;
    if (gm_801677F8(r31->x0.slot, r31->x0.x4) == false) {
        return 4;
    }
    return r31->x0.slot;
}

u8 gm_8017E48C(MinorScene* scene)
{
    u8 count = 0;
    int i;
    for (i = 0; scene->idx != gm_803DE1B8_MinorScenes[i].idx; i++) {
        if (gm_803DE1B8_MinorScenes[i].info.class_id == 2) {
            count++;
        }
    }
    return count;
}

struct gm_803DE650_t* gm_8017E4C4(u8 arg0)
{
    struct gm_803DE650_t* ptr;
    for (ptr = gm_803DE650; ptr->x0 != 0xFF; ptr++) {
        if (ptr->x0 == arg0) {
            return ptr;
        }
    }
    return NULL;
}

/// Get adventure stage kind for given difficulty and stage slot.
/// The (u8) cast on difficulty is required - these functions are called
/// via function pointers typed as f32(*)(int, u8) in UnkAdventureData.
u8 gm_8017E500(u8 difficulty, u8 stage_slot)
{
    return lbl_803D7AC0[stage_slot + difficulty * 5].stage_kind;
}

f32 gm_8017E528(u8 difficulty, u8 stage_slot)
{
    return lbl_803D7AC0[stage_slot + difficulty * 5].scale0_pct / 100.0F;
}

f32 gm_8017E578(u8 difficulty, u8 stage_slot)
{
    return lbl_803D7AC0[stage_slot + difficulty * 5].scale1_pct / 100.0F;
}

u8 gm_8017E5C8(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D7AC0[stage_slot + difficulty * 5].pad_6[arg2 * 3];
}

u8 gm_8017E5FC(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D7AC0[stage_slot + difficulty * 5].pad_6[1 + arg2 * 3];
}

u8 gm_8017E630(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D7AC0[stage_slot + (u8) difficulty * 5].pad_6[arg2 * 3 + 2];
}

f32 gm_8017E664(u8 difficulty, u8 stage_slot)
{
    return lbl_803D7AC0[stage_slot + difficulty * 5].scale0_pct / 100.0F;
}

f32 gm_8017E6B4(u8 difficulty, u8 stage_slot)
{
    return lbl_803D7AC0[stage_slot + difficulty * 5].scale1_pct / 100.0F;
}

u8 gm_8017E704(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D7AC0[stage_slot + difficulty * 5].pad_6[0x0E + arg2 * 3];
}

u8 gm_8017E738(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D7AC0[stage_slot + difficulty * 5].pad_6[0xF + arg2 * 3];
}

u8 gm_8017E76C(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D7AC0[stage_slot + difficulty * 5].pad_6[0x10 + (arg2 * 3)];
}

void gm_8017E7A0(u8 arg0)
{
    if (arg0 == 1) {
        Player_LoseStock(0);
        ifStatus_802F6948(0);
        ifStatus_802F6E3C(0);
    }
}

bool gm_8017E7E0(void)
{
    return lbl_80472C30.x7C == 0x14;
}

void gm_8017E7FC(u8 arg0)
{
    UnkAdventureData* r31 = &lbl_80472C30;
    bool cond;

    if (gm_801A4310() == 4 && r31->x0.cpu_level >= 2 &&
        r31->x0.xC.x20 + gm_8016AEDC() < 0xFD20U)
    {
        cond = true;
    } else {
        cond = false;
    }

    if (!cond) {
        struct StartMeleeRules* rules = gm_8016AE50();
        rules->x4_5 = 1;
        r31->x77 = 0;
        gm_SetScenePendingMinor(0x5A);
    } else {
        r31->x77 = 1;
        gm_SetScenePendingMinor(0x5A);
    }
}

typedef struct {
    u8 b7 : 1, b6 : 1, b5 : 1, b4 : 1, b3 : 1, b2 : 1, b1 : 1, b0 : 1;
} u8_bits;

#pragma dont_inline on
void fn_8017E8A4(int arg0_int)
{
    MatchEnd* arg0 = (MatchEnd*) arg0_int;
    lbl_8046B6A0_t* gm = gm_8016AE38();
    struct gm_803DE650_t* stage = gm_8017E4C4(gm_801A42C4());
    UnkAdventureData* adv = &lbl_80472C30;
    u8* flags = arg0->_x448;
    gmm_x0_528_t* main_data;
    u32 total_time;
    int i;

    if (fn_8017E318() > 0) {
        ((u8_bits*)&flags[2])->b3 = 1;
    }

    if (gm->x24C8.x4_5) {
        main_data = gmMainLib_8015CDD4();
        total_time = adv->x0.xC.x20 + gm_8016AEDC();
        ((u8_bits*)&flags[0])->b6 = 1;

        if ((u8) adv->x0.cpu_level == 4) {
            ((u8_bits*)&flags[0])->b3 = 1;
        }

        if (total_time < 0xC4E0U) {
            ((u8_bits*)&flags[2])->b6 = 1;
        } else if (total_time < 0x13560U) {
            ((u8_bits*)&flags[2])->b7 = 1;
        }

        if ((u32) adv->x0.xC.x1C == 0U &&
            (u32) arg0->player_standings[0].x44 == 0U)
        {
            ((u8_bits*)&flags[1])->b1 = 1;
        }

        if ((u8) adv->x0.xC.xE != 0) {
            ((u8_bits*)&flags[2])->b5 = 1;
        }

        if ((u8) adv->x0.xC.xF != 0) {
            ((u8_bits*)&flags[2])->b4 = 1;
        }

        if ((u8) adv->x0.xC.xD != 0) {
            ((u8_bits*)&flags[1])->b0 = 1;
        } else if ((s8) arg0->player_standings[0].stocks ==
                   (s32) main_data->stocks)
        {
            ((u8_bits*)&arg0->_x448[1])->b2 = 1;
        }
    }

    if (stage->x0 == 3) {
        for (i = 0; i < 6; i++) {
            if (Player_GetPlayerSlotType(i) == Gm_PKind_Cpu &&
                Player_GetPlayerCharacter(i) == CKIND_LUIGI)
            {
                ((u8_bits*)&flags[1])->b7 = 1;
                return;
            }
        }
    }

    if (stage->x0 == 0x11) {
        if (gm->unk_C >= 5) {
            ((u8_bits*)&flags[1])->b6 = 1;
            return;
        }
    }

    if (stage->x0 == 0x25) {
        ((u8_bits*)&flags[1])->b5 = 1;
        return;
    } else if (stage->x0 == 0x53) {
        for (i = 0; i < 6; i++) {
            if (Player_GetPlayerSlotType(i) == Gm_PKind_Cpu &&
                Player_GetPlayerCharacter(i) == CKIND_LUIGI)
            {
                ((u8_bits*)&flags[1])->b4 = 1;
                return;
            }
        }
    }

    if (stage->x0 == 0x5C) {
        ((u8_bits*)&flags[1])->b3 = 1;
    }

    PAD_STACK(8);
}
#pragma dont_inline reset

UnkAllstarData* gm_8017EB30(void)
{
    return &lbl_80472CB0;
}

u8 gm_8017EB3C(u8 difficulty, u8 stage_slot)
{
    return lbl_803D85F0[stage_slot + difficulty * 5].stage_kind;
}

u8 gm_8017EB64(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D85F0[stage_slot + difficulty * 5].pad_6[arg2 * 3];
}

u8 gm_8017EB98(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D85F0[stage_slot + difficulty * 5].pad_6[arg2 * 3 + 1];
}

u8 gm_8017EBCC(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D85F0[stage_slot + difficulty * 5].pad_6[arg2 * 3 + 2];
}

f32 gm_8017EC00(u8 difficulty, u8 stage_slot)
{
    return lbl_803D85F0[stage_slot + difficulty * 5].scale2_pct / 100.0F;
}

f32 gm_8017EC50(u8 difficulty, u8 stage_slot)
{
    return lbl_803D85F0[stage_slot + difficulty * 5].scale3_pct / 100.0F;
}

u8 gm_8017ECA0(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D85F0[stage_slot + difficulty * 5].pad_14[arg2 * 3];
}

u8 gm_8017ECD4(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D85F0[stage_slot + ((u8) difficulty * 5)]
        .pad_14[arg2 * 3 + 1];
}

u8 gm_8017ED08(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D85F0[stage_slot + ((u8) difficulty * 5)]
        .pad_14[arg2 * 3 + 2];
}

f32 gm_8017ED3C(u8 difficulty, u8 stage_slot)
{
    return lbl_803D85F0[stage_slot + difficulty * 5].scale0_pct / 100.0F;
}

f32 gm_8017ED8C(u8 difficulty, u8 stage_slot)
{
    return lbl_803D85F0[stage_slot + difficulty * 5].scale1_pct / 100.0F;
}

bool fn_8017EDDC(void)
{
    UnkAllstarData* p;

    if (gm_801A4310() == MJ_CLASSIC) {
        p = &lbl_80472CB0;
        if (p->x0.xC.xD == 0 && p->x0.cpu_level >= 2 && p->x0.xC.x20 < 0x5208)
        {
            return true;
        }
    }
    return false;
}

#pragma dont_inline on
void fn_8017EE40(int arg0_int)
{
    MatchEnd* arg0 = (MatchEnd*) arg0_int;
    struct StartMeleeRules* rules;
    gmm_x0_528_t* main_data;
    u32 total_time;
    int i;

    rules = gm_8016AE50();

    if (fn_8017E318() > 0) {
        ((u8_bits*)&arg0->_x448[2])->b3 = 1;
    }

    if (rules->x4_5) {
        main_data = gmMainLib_8015CDC8();
        total_time = lbl_80472CB0.x0.xC.x20 + gm_8016AEDC();
        ((u8_bits*)&arg0->_x448[0])->b7 = 1;

        if ((u8) lbl_80472CB0.x0.cpu_level == 4) {
            ((u8_bits*)&arg0->_x448[0])->b4 = 1;
        }

        if (total_time < 0x3840U) {
            ((u8_bits*)&arg0->_x448[2])->b6 = 1;
        } else if (total_time < 0x5460U) {
            ((u8_bits*)&arg0->_x448[2])->b7 = 1;
        }

        if ((u32) lbl_80472CB0.x0.xC.x1C == 0U &&
            (u32) arg0->player_standings[0].x44 == 0U)
        {
            ((u8_bits*)&arg0->_x448[1])->b1 = 1;
        }

        if ((u8) lbl_80472CB0.x0.xC.xE != 0) {
            ((u8_bits*)&arg0->_x448[2])->b5 = 1;
        }

        if ((u8) lbl_80472CB0.x0.xC.xF != 0) {
            ((u8_bits*)&arg0->_x448[2])->b4 = 1;
        }

        if ((u8) lbl_80472CB0.x0.xC.xD != 0) {
            ((u8_bits*)&arg0->_x448[1])->b0 = 1;
        } else if ((s8) arg0->player_standings[0].stocks ==
                   (s32) main_data->stocks)
        {
            ((u8_bits*)&arg0->_x448[1])->b2 = 1;
        }
    }

    for (i = 0; i < 6; i++) {
        if (Player_GetPlayerSlotType(i) == Gm_PKind_Cpu &&
            Player_GetPlayerCharacter(i) == CKIND_CREZYH)
        {
            ((u8_bits*)&arg0->_x448[0])->b0 = 1;
            return;
        }
    }
}
#pragma dont_inline reset

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

s32 fn_8017F09C(void)
{
    struct lbl_80472D28_t* data = &lbl_80472D28;
    lbl_8046B6A0_t* p = gm_8016AE38();
    if (p->x24C8.x4_6) {
        lbl_8046B6A0_t* p2 = gm_8016AE38();
        int flag;
        if (data->x118 != 0 ||
            (data->x11A != 0 && data->x11B == 0) ||
            p2->x24C8.x0_7)
        {
            flag = 0;
        } else {
            flag = 1;
        }
        if (flag != 0) {
            s32 product = p->timer_seconds * data->x108;
            s32 ret = product;
            if (product < 0) {
                ret = 0;
            }
            return ret;
        }
    }
    return 0;
}

typedef struct fn_8017F14C_arg {
    /* 0x00 */ char pad_0[0x98];
    /* 0x98 */ s32 x98;
} fn_8017F14C_arg;

#pragma dont_inline on
s32 fn_8017F14C(void* arg0)
{
    fn_8017F14C_arg* p = arg0;
    struct lbl_80472D28_t* data = &lbl_80472D28;
    if (gm_8016AE38()->x24C8.x4_7) {
        s32 val = p->x98;
        s32 ret = val;
        if (val > 9999) {
            ret = 9999;
        }
        return ret * data->x10A;
    }
    return 0;
}
#pragma dont_inline off

s32 fn_8017F1B8(void)
{
    int i;
    int mask;
    int output;

    for (i = 0; i < 256; i++) {
        if (fn_8016F1F0(i) < 0xD7) {
            mask = fn_8017F008();
            output = (u8) fn_8016F180(i);
            if (output & mask) {
                if ((u32) fn_8016F160(0, i) != 0) {
                    fn_8016F140(i);
                }
            }
        } else {
            mask = fn_8017F008();
            output = (u8) fn_8016F180(i);
            if (output & mask) {
                if ((u32) fn_801701C0(gm_8016B774(), 0, i) != 0) {
                    fn_8016F140(i);
                }
            }
        }
    }

    mask = (u8) fn_8017F008();
    return fn_8016FFD4(gm_8016B774(), mask, 0);
}

int fn_8017F294(void)
{
    return lbl_80472D28.x104;
}

s32 fn_8017F2A4(HSD_Text** arg0, f32 farg0, f32 farg1)
{
    HSD_Text* text;
    HSD_Text** ptr;
    u8* data;
    f32 x_end;
    f32 y;
    s32 temp;
    s32 i;

    temp = HSD_SisLib_803A611C(3, NULL, 9U, 0xDU, 0U, 0x14U, 0U, 0x13U);
    if (lbLang_IsSavedLanguageUS()) {
        HSD_SisLib_803A62A0(3, "SdDec.usd", "SIS_DecisionData");
    } else {
        HSD_SisLib_803A62A0(3, "SdDec.dat", "SIS_DecisionData");
    }
    *arg0 = HSD_SisLib_803A6754(3, temp);
    ptr = arg0;

    (*arg0)->default_kerning = 1;
    text = *arg0;
    text->x34.x = 0.56f;
    text->x34.y = 0.6f;
    (*arg0)->default_alignment = 2;
    x_end = 281.0f + farg0;
    for (i = 0; i < 7; i++) {
        y = (0.6f * (32.0f * (f32) i)) + farg1;
        ptr[1] = HSD_SisLib_803A5ACC(3, 0, farg0, y, 0.0f, 2.0f, 2.0f);
        text = ptr[1];
        text->x34.x = 0.56f;
        text->x34.y = 0.6f;
        ptr[1]->default_kerning = 1;
        HSD_SisLib_803A6B98(*arg0, x_end, -12.0f + y, "          ");
        ptr++;
    }
    return HSD_SisLib_803A6B98(*arg0, x_end, 9.0f + (134.40001f + farg1),
                               "               ");
    PAD_STACK(8);
}

s32 fn_8017F47C(HSD_Text** arg0, int arg1)
{
    s32* p;
    s32 prev_idx;
    int entry;
    s32 i;
    u8 mask;
    s32 idx;
    s32 val;

    entry = arg1;
    prev_idx = -999;
    mask = fn_8017F008();
    fn_8016F39C(arg0 + 1, gm_8016B774(), 7, arg1, mask, 0);

    i = 0;
    p = (s32*) arg0;

    do {
        mask = fn_8017F008();
        idx = fn_8016F548(gm_8016B774(), entry, mask, 0);
        mask = fn_8017F008();
        val = fn_8016FAD4(gm_8016B774(), (u32) idx, (s32) mask, 0);

        if (prev_idx == idx || idx < 0) {
            break;
        }

        if (p[8] != val) {
            if (val < 0) {
                HSD_SisLib_803A70A0(*arg0, i, "%s%d", "\x81\x7c", -val);
            } else {
                HSD_SisLib_803A70A0(*arg0, i, "%d", val);
            }
            p[8] = val;
        }

        prev_idx = idx;
        entry = idx + 1;
        p++;
        i++;
    } while (i < 7);

    mask = fn_8017F008();
    val = fn_8016FFD4(gm_8016B774(), (s32) mask, 0);

    if (val < 0) {
        HSD_SisLib_803A70A0(*arg0, 7, "%s%d", "\x81\x7c", -val);
    } else {
        HSD_SisLib_803A70A0(*arg0, 7, "%d", val);
    }

    mask = fn_8017F008();
    return fn_8016F548(gm_8016B774(), arg1, mask, 0);
    PAD_STACK(0x18);
}

typedef struct fn_8017FA1C_arg {
    /* 0x000 */ HSD_GObj* x0;
    /* 0x004 */ HSD_JObj* x4;
    /* 0x008 */ HSD_JObj* x8;
    /* 0x00C */ HSD_JObj* xC;
    /* 0x010 */ HSD_JObj* x10;
    /* 0x014 */ HSD_JObj* x14;
    /* 0x018 */ HSD_JObj* x18;
    /* 0x01C */ HSD_JObj* x1C;
    /* 0x020 */ HSD_JObj* x20;
    /* 0x024 */ HSD_JObj* x24;
    /* 0x028 */ char pad_28[0x24];
    /* 0x04C */ DynamicModelDesc x4C;
    /* 0x05C */ char pad_5C[0x10];
    /* 0x06C */ HSD_Text* x6C;
    /* 0x070 */ HSD_Text* x70;
    /* 0x074 */ HSD_Text* x74;
    /* 0x078 */ HSD_Text* x78;
    /* 0x07C */ HSD_Text* x7C;
    /* 0x080 */ HSD_Text* x80;
    /* 0x084 */ char pad_84[0x48];
    /* 0x0CC */ s32 xCC;
    /* 0x0D0 */ s32 xD0;
    /* 0x0D4 */ s32 xD4;
    /* 0x0D8 */ s32 xD8;
    /* 0x0DC */ s32 xDC;
    /* 0x0E0 */ s32 xE0;
    /* 0x0E4 */ s32 xE4;
    /* 0x0E8 */ char pad_E8[0x08];
    /* 0x0F0 */ s32 xF0;
    /* 0x0F4 */ s32 xF4;
    /* 0x0F8 */ s32 xF8;
    /* 0x0FC */ s32 xFC;
    /* 0x100 */ s32 x100;
    /* 0x104 */ s32 x104;
    /* 0x108 */ s16 x108;
    /* 0x10A */ s16 x10A;
    /* 0x10C */ char pad_10C[0x08];
    /* 0x114 */ u8 x114;
    /* 0x115 */ u8 x115;
    /* 0x116 */ char pad_116[2];
    /* 0x118 */ u8 x118;
    /* 0x119 */ char pad_119;
    /* 0x11A */ u8 x11A;
    /* 0x11B */ u8 x11B;
} fn_8017FA1C_arg;

extern Vec3 lbl_803B7C18;

void fn_8017F608(void* arg0)
{
    fn_8017FA1C_arg* p = arg0;
    Vec3 sp4C;
    Vec3 sp40;
    HSD_Text* text;
    lbl_8046B6A0_t* gm;
    s32 show;

    sp40 = lbl_803B7C18;

    if (p->x6C == NULL) {
        p->x6C = HSD_SisLib_803A5ACC(0, 0, 0.0f, 0.0f, 0.0f, 6.0f, 300.0f);
        HSD_SisLib_803A6368(p->x6C, 2);
    }
    if (p->x70 == NULL) {
        text = HSD_SisLib_803A5ACC(0, 0, 0.0f, 0.0f, 0.0f, 6.0f, 300.0f);
        p->x70 = text;
        if (p->x11A != 0) {
            HSD_SisLib_803A6368(p->x70, 4);
        } else {
            HSD_SisLib_803A6368(p->x70, 3);
        }
    }
    if (p->xD0 != p->xD4) {
        s32 str;
        p->xD8 = p->xD8 + 1;
        text = p->x74;
        if (text != NULL) {
            HSD_SisLib_803A5CC4(text);
        }
        p->x74 = HSD_SisLib_803A6754(0, 0);
        {
        struct lbl_80472D28_t* state = &lbl_80472D28;
        p->x74->pos_z = -10.0f;
        p->x74->default_alignment = 2;
        gm = gm_8016AE38();
        if (state->x118 != 0 ||
            (state->x11A != 0 && state->x11B == 0) ||
            (gm->x24C8.x0_7))
        {
            show = 0;
        } else {
            show = 1;
        }
        if (show == 0) {
            str = HSD_SisLib_803A6B98(p->x74, 0.0f, 0.0f, "\x81|");
            HSD_SisLib_803A7548(p->x74, str, 0.1f, 0.065f);
            p->xD4 = p->xD0;
        } else if (p->xD8 < 0x3C) {
            p->x74->default_kerning = 1;
            str = HSD_SisLib_803A6B98(p->x74, 0.0f, 0.0f, "%d\x82w%d",
                p->xD0 / p->x108, p->x108);
            HSD_SisLib_803A7548(p->x74, str, 0.089999996f, 0.065f);
        } else {
            str = HSD_SisLib_803A6B98(p->x74, 0.0f, 0.0f, "%d", p->xD0);
            HSD_SisLib_803A7548(p->x74, str, 0.1f, 0.065f);
            p->xD4 = p->xD0;
        }
        }
    }
    if (p->x11A == 0 && p->xDC != p->xE0) {
        s32 str;
        p->xE4 = p->xE4 + 1;
        text = p->x78;
        if (text != NULL) {
            HSD_SisLib_803A5CC4(text);
        }
        p->x78 = HSD_SisLib_803A6754(0, 0);
        p->x78->default_alignment = 2;
        if (p->xE4 < 0x3C) {
            p->x78->default_kerning = 1;
            str = HSD_SisLib_803A6B98(p->x78, 0.0f, 0.0f, "%d\x82w%d",
                p->xDC / p->x10A, p->x10A);
            HSD_SisLib_803A7548(p->x78, str, 0.1f, 0.065f);
        } else {
            str = HSD_SisLib_803A6B98(p->x78, 0.0f, 0.0f, "%d", p->xDC);
            HSD_SisLib_803A7548(p->x78, str, 0.1f, 0.065f);
            p->xE0 = p->xDC;
        }
    }
    lb_8000B1CC(p->x10, &sp40, &sp4C);
    text = p->x70;
    if (text != NULL) {
        f32 px, py, pz;
        px = sp4C.x;
        py = -sp4C.y;
        pz = sp4C.z;
        text->pos_x = px;
        text->pos_y = py;
        text->pos_z = pz;
    }
    text = p->x6C;
    if (text != NULL) {
        f32 px, py, pz;
        px = 0.1f + sp4C.x;
        py = -sp4C.y - 6.0f;
        pz = sp4C.z;
        text->pos_x = px;
        text->pos_y = py;
        text->pos_z = pz;
    }
    text = p->x74;
    if (text != NULL) {
        f32 px, py, pz;
        px = 6.5f + sp4C.x;
        py = -sp4C.y - 33.5f;
        pz = sp4C.z;
        text->pos_x = px;
        text->pos_y = py;
        text->pos_z = pz;
    }
    text = p->x78;
    if (text != NULL) {
        f32 px, py, pz;
        px = 6.5f + sp4C.x;
        py = -sp4C.y - 27.5f;
        pz = sp4C.z;
        text->pos_x = px;
        text->pos_y = py;
        text->pos_z = pz;
    }
    PAD_STACK(0x24);
}

extern s32 lbl_804D65C0;

s32 fn_8017FA1C(void* arg0)
{
    fn_8017FA1C_arg* p = arg0;
    Vec3 sp14;
    s32 step;
    s32 target_val;
    s32 diff;
    s32 abs_step;
    f32 px, py, pz;

    PAD_STACK(4);

    if (HSD_JObjGetFlags(p->xC) & 0x10) {
        if (p->x80 != NULL) {
            HSD_SisLib_803A5CC4(p->x80);
        }
        p->x80 = NULL;
        p->x100 = p->xFC - 1;
        return 0;
    }
    if ((p->xFC && p->xFC) && p->xFC) {
    }
    abs_step = p->x104;
    step = lbl_804D65C0;
    target_val = abs_step;
    diff = target_val - p->xFC;

    if (step < 0) {
        abs_step = -step;
    } else {
        abs_step = step;
    }

    if (diff < 0) {
        diff = -diff;
    }

    if (diff <= abs_step) {
        p->xFC = target_val;
        p->x115 = 1;
    } else {
        p->xFC += step;
        p->x115 = 0;
    }

    if (p->xFC != p->x100) {
        int str;
        if (p->x80 != NULL) {
            HSD_SisLib_803A5CC4(p->x80);
        }
        p->x80 = HSD_SisLib_803A6754(0, 0);
        p->x80->default_alignment = 2;
        str = HSD_SisLib_803A6B98(p->x80, 0.0f, 0.0f, "%d", p->xFC);
        HSD_SisLib_803A7548(p->x80, str, 0.1f, 0.08f);
        p->x100 = p->xFC;
    }

    if (p->x80 != NULL) {
        HSD_Text* text;
        lb_8000B1CC(p->xC, NULL, &sp14);
        py = -sp14.y - 30.6f;
        px = 16.0f + sp14.x;
        pz = sp14.z;
        text = p->x80;
        text->pos_x = px;
        text->pos_y = py;
        text->pos_z = pz;
    }

    return 1;
}

void fn_8017FBA4(void* arg0)
{
    fn_8017FA1C_arg* p = arg0;
    int tmp;
    Vec3 sp24;
    f32 sx, sy;
    int str;

    if (HSD_JObjGetFlags(p->x8) & 0x10) {
        if (p->x7C != NULL) {
            HSD_SisLib_803A5CC4(p->x7C);
        }
        p->x7C = NULL;
        p->xF4 = p->xF0 - 1;
        return;
    }

    if (p->xF0 != p->xF4) {
        if (p->x7C != NULL) {
            HSD_SisLib_803A5CC4(p->x7C);
        }
        p->x7C = HSD_SisLib_803A6754(0, 0);
        tmp = HSD_SisLib_803A6B98(p->x7C, 0.0f, 0.0f, "%d", p->xF0);
        HSD_SisLib_803A7548(p->x7C, tmp, 0.1f, 0.065f);
        p->xF4 = p->xF0;
    }

    sx = HSD_JObjGetScaleX(p->x8->parent);
    sy = HSD_JObjGetScaleY(p->x8->parent);

    if (p->x7C != NULL) {
        HSD_SisLib_803A5CC4(p->x7C);
    }
    p->x7C = HSD_SisLib_803A6754(0, 0);
    p->x7C->default_alignment = 2;
    p->xF8 = p->xF8 + 1;

    if (p->xF8 < 0xC) {
        HSD_SisLib_803A7548(p->x7C,
            HSD_SisLib_803A6B98(p->x7C, 0.0f, 0.0f, "%s %d",
                                "\x81{", p->xCC),
            0.1f * sx, 0.065f * sy);
    } else if (p->xF8 < 0x20) {
        HSD_SisLib_803A7548(p->x7C,
            HSD_SisLib_803A6B98(p->x7C, 0.0f, 0.0f, "%s %d",
                                "\x81{", p->xDC + p->xD0),
            0.1f * sx, 0.065f * sy);
    } else {
        if (p->xF0 >= 0) {
            str = HSD_SisLib_803A6B98(p->x7C, 0.0f, 0.0f, "%s %d",
                                      "\x81{", p->xF0);
        } else {
            str = HSD_SisLib_803A6B98(p->x7C, 0.0f, 0.0f, "%d",
                                      p->xF0, p->xF0);
        }
        HSD_SisLib_803A7548(p->x7C, str, 0.1f * sx, 0.065f * sy);
    }

    if (p->x7C != NULL) {
        f32 px, py, pz;
        HSD_Text* text;
        lb_8000B1CC(p->x8, NULL, &sp24);
        py = -sp24.y - 31.0f;
        px = 8.5f + sp24.x;
        pz = sp24.z;
        text = p->x7C;
        text->pos_x = px;
        text->pos_y = py;
        text->pos_z = pz;
    }
    PAD_STACK(4);
}

void fn_8017FE54(HSD_GObj* gobj)
{
    RegClearEv* ev = gobj->user_data;

    lb_800122C8(ev->x1C, 0, 0, 1);
    lb_800138D8(lbl_80472D28.x2C,
                (int)(120.0F * lbl_80472D28.x10C) + 1);

    ev->x20 = 0.0225F * (f32) lbl_80472D28.x110 - 0.175F;

    if (ev->x20 < 0.05F) {
        ev->x20 = 0.0F;
    }
    if (ev->x20 > 1.0F) {
        ev->x20 = 1.0F;
    }
}

void fn_8017FF1C(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    struct lbl_80472D28_t* state = &lbl_80472D28;
    s32 result;
    s32 i;
    u8 mask;
    HSD_JObj* sp28;

    jobj = gobj->hsd_obj;
    HSD_JObjAnimAll(gobj->hsd_obj);

    if (state->x118 == 0) {
        fn_8017F608(state);
    }

    result = fn_8017FA1C(state);
    fn_8017FBA4(state);

    if (state->x117 != 0 && state->x110 > 0x29U) {
        state->xC0 =
            fn_8017F47C(&state->x84, (s32) state->xC0);

        mask = fn_8017F008();
        if (fn_8016F9A8(gm_8016B774(), state->xC0, mask, 0) > 7) {
            state->x11F = 0;
        } else {
            state->x11F = 1;
        }

        mask = fn_8017F008();
        if (fn_8016F870(gm_8016B774(), state->xC0, mask, 0) < 0) {
            state->x11E = 1;
        } else {
            state->x11E = 0;
        }

        if (state->x110 % 30 == 0 && state->xC8 == 0) {
            mask = fn_8017F008();
            if (fn_8016F9A8(gm_8016B774(), state->xC0, mask, 0) > 7) {
                state->xC0 = (u16) (state->xC0 + 1);
            } else {
                state->xC8 = 1;
                state->xC4 = state->x110;
            }
        }

        {
            u64 buttons = gm_801A36A0(Player_GetPlayerId(0));
            u64 repeat = gm_801A36C0(Player_GetPlayerId(0));
            if (((repeat | buttons) & 0x20004) | ((repeat | buttons) & 0)) {
                mask = fn_8017F008();
                if (fn_8016F740(gm_8016B774(), state->xC0, mask,
                                0) > 0)
                {
                    mask = fn_8017F008();
                    if (fn_8016F9A8(gm_8016B774(), state->xC0, mask,
                                    0) > 7)
                    {
                        mask = fn_8017F008();
                        state->xC0 = fn_8016F740(gm_8016B774(),
                                                 state->xC0, mask, 0);
                        state->xC8 = 1;
                        state->xC4 = state->x110;
                    }
                }
            } else {
                buttons = gm_801A36A0(Player_GetPlayerId(0));
                repeat = gm_801A36C0(Player_GetPlayerId(0));
                if (((repeat | buttons) & 0x10008) | ((repeat | buttons) & 0))
                {
                    mask = fn_8017F008();
                    if (fn_8016F870(gm_8016B774(), state->xC0, mask,
                                    0) >= 0)
                    {
                        mask = fn_8017F008();
                        state->xC0 = fn_8016F870(gm_8016B774(),
                                                 state->xC0, mask, 0);
                        state->xC8 = 1;
                        state->xC4 = state->x110;
                    }
                }
            }
        }
    }

    if (state->x11A != 0 && state->x110 > 0x14U &&
        state->x11D < state->x11C &&
        (s32) (0.5f * (f32) (state->x110 - 0x14)) > (s32) state->x11D)
    {
        lb_80011E24(jobj, &sp28, state->x11D + 7, -1);
        HSD_JObjClearFlagsAll(sp28, 0x10);
        state->x11D = (u8) (state->x11D + 1);
    }

    if (state->x115 == 0 && result != 0) {
        fn_80168F2C(0);
    }

    for (i = 0; i < 6; i++) {
        if (Player_GetPlayerSlotType(i) == Gm_PKind_Human &&
            (HSD_PadMasterStatus[(u8) Player_GetPlayerId(i)].trigger &
             0x100))
        {
            state->xFC = state->x104;
            state->x115 = 1;
            break;
        }
    }

    if (state->x110 > 0x3EU) {
        for (i = 0; i < 6; i++) {
            if (Player_GetPlayerSlotType(i) == Gm_PKind_Human &&
                (HSD_PadMasterStatus[(u8) Player_GetPlayerId(i)].trigger &
                 0x1000))
            {
                state->xFC = state->x104;
                state->x116 = 1;
                lbAudioAx_80024030(1);
                break;
            }
        }
    }

    if (state->x11E != 0) {
        HSD_JObjSetFlagsAll(state->x20, 0x10);
    } else {
        HSD_JObjClearFlagsAll(state->x20, 0x10);
    }

    if (state->x11F != 0) {
        HSD_JObjSetFlagsAll(state->x24, 0x10);
    } else {
        HSD_JObjClearFlagsAll(state->x24, 0x10);
    }

    if (state->x10C < 1.0f) {
        state->x10C += 0.05f;
    } else {
        state->x10C = 1.0f;
    }

    if (state->x110 + 0x10000 != 0xFFFF) {
        state->x110 = state->x110 + 1;
    }
    PAD_STACK(0x1C);
}

s32 fn_801803FC(void* arg0)
{
    fn_8017FA1C_arg* p = arg0;
    HSD_JObj* sp10;
    struct lbl_80472D28_t* state = &lbl_80472D28;
    DynamicModelDesc* mdl = &p->x4C;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    HSD_JObj* temp;
    f32 frame;
    s32 i;

    gobj = GObj_Create(0xEU, 0xEU, 0U);
    p->x0 = gobj;
    if (gobj == NULL) {
        HSD_JObjAnimAll((HSD_JObj*) gobj->hsd_obj);
        OSReport("Error : gobj don\'t get (gmRegClearAddModel)\n");
        OSPanic(__FILE__, 0x42C, "");
    }
    jobj = HSD_JObjLoadJoint(mdl->joint);
    if (jobj == NULL) {
        OSReport("Error : jobj don\'t get (gmRegClearAddModel)\n");
        OSPanic(__FILE__, 0x432, "");
    }
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xBU, 0U);
    HSD_GObj_SetupProc(gobj, (HSD_GObjEvent) fn_8017FF1C, 0x11U);
    fn_801689E4(jobj, mdl, 0);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);
    {
        lb_8001204C(jobj, &p->x4, lbl_803D8B88, 0xA);
    }
    if (state->x117 == 0) {
        HSD_JObjSetFlagsAll(p->x14, 0x10U);
        HSD_JObjSetFlagsAll(p->x20, 0x10U);
        HSD_JObjSetFlagsAll(p->x24, 0x10U);
    }
    if (p->x11A != 0) {
        for (i = 0; i < 0xA; i++) {
            lb_80011E24(jobj, &sp10, i + 7, -1);
            HSD_JObjSetFlagsAll(sp10, 0x10U);
        }
        HSD_JObjSetFlagsAll(p->x10, 0x10U);
    } else {
        HSD_JObjSetFlagsAll(p->x1C, 0x10U);
        if (p->x118 != 0) {
            HSD_JObjSetFlagsAll(p->x18, 0x10U);
        }
    }
    temp = p->x4;
    if (p->x114 != 0) {
        frame = 1.0f;
    } else {
        frame = 0.0f;
    }
    HSD_AObjSetCurrentFrame(temp->u.dobj->mobj->tobj->aobj, frame);
    HSD_AObjSetRate(temp->u.dobj->mobj->tobj->aobj, 0.0f);
    if (p->x118 == 0) {
        fn_8017F608(arg0);
    }
    fn_8017FBA4(arg0);
    return fn_8017FA1C(arg0);
    PAD_STACK(4);
}

void fn_80180630(int arg0, int arg1, int arg2, bool arg3,
                 lbl_8046B6A0_24C_t* arg4)
{
    struct lbl_80472D28_t* state = &lbl_80472D28;
    s32 sp64;
    s32 sp60;
    s32 sp5C;
    s32 sp58;
    void* sp38;
    HSD_Archive* archive;
    HSD_GObj* light_gobj;
    HSD_GObj* cam_gobj;
    lbl_8046B6A0_t* temp;
    s32 total;
    s32 var_r4;
    s32 var_r27;
    s32 var_r3;
    u16 var_r28;
    u8 mask;
    u8 var_r0;

    var_r27 = 0;
    var_r28 = arg4->x58[0].xE;
    memzero(state, 0x120);
    state->xD4 = -1;
    state->xD8 = 0;
    state->xE0 = -1;
    state->xE4 = 0;
    state->xEC = -1;
    state->xF4 = -1;
    state->x100 = -1;
    state->x11E = 1;
    state->x11F = 1;
    state->x108 = 0x64;
    state->x10A = 0x64;
    state->x114 = (u8) arg3;

    switch (arg2) {
    case 1:
        Ground_801C1DE4(&sp60, &sp64);
        state->x11A = 1;
        state->x11C = (u8) (sp64 - sp60);
        state->x108 = 0xC8;
        if (sp60 == 0) {
            state->x11B = 1;
        }
        break;
    case 3:
        temp = gm_8016AE38();
        state->x118 = 1;
        if ((u8) temp->match_result == 6) {
            grPushOn_80219204(Ground_801C1DD4(), (int*) &sp5C, (int*) &sp58);
            var_r27 = sp5C;
            var_r28 = (u16) sp58;
            state->x108 = 0x1F4;
        }
        break;
    case 2:
        state->x119 = 1;
        break;
    }

    fn_8016F344(gm_8016B774());

    if (state->x11A == 0 && state->x118 == 0 &&
        state->x119 == 0 &&
        (mask = fn_8017F008(),
         fn_8016F9A8(gm_8016B774(), 0, mask, 0) != 0))
    {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    state->x117 = var_r0;

    if (state->x117 != 0) {
        state->xC8 = 0;
    } else {
        state->xC8 = 1;
    }

    if (state->x118 == 0) {
        state->xD0 = fn_8017F09C();
        state->xDC = fn_8017F14C(arg4);
    }

    if (state->x117 != 0) {
        state->xE8 = fn_8017F1B8();
    }

    state->xF0 =
        state->xDC + (state->xD0 + var_r27 + state->xE8);
    state->xFC = arg0 + arg1;
    state->xCC = arg1;

    total = arg0 + (state->xCC + state->xF0);
    var_r4 = total;
    if (total > 999999999) {
        var_r4 = 999999999;
    } else if (var_r4 < 0) {
        var_r4 = 0;
    }
    state->x104 = var_r4;
    lbl_804D65C0 = (var_r4 - (arg0 + arg1)) / 10;

    archive =
        lbArchive_80016DBC("GmRegClr", &sp38, "ScGamRegClear_scene_data", 0);
    state->x48 = archive;
    if (sp38 == NULL) {
        OSReport("Error : Cannot open archive file (File Name : %s).",
                 "GmRegClr", archive);
    }
    fn_80168A6C(sp38, &state->x4C, 0);

    light_gobj = GObj_Create(0xBU, 3U, 0U);
    HSD_GObjObject_80390A70(light_gobj, (u8) HSD_GObj_804D784A,
                            lb_80011AC4(state->x5C));
    GObj_SetupGXLink(light_gobj, HSD_GObj_LObjCallback, 0xAU, 0U);

    cam_gobj = GObj_Create(0xEU, 0xEU, 0U);
    HSD_GObjObject_80390A70(cam_gobj, HSD_GObj_804D784B,
                            HSD_CObjLoadDesc(state->x60));
    GObj_SetupGXLinkMax(cam_gobj, HSD_GObj_803910D8, 8U);
    ((u32*) &cam_gobj->gxlink_prios)[1] = 0x4C00;
    ((u32*) &cam_gobj->gxlink_prios)[0] = 0;

    HSD_SisLib_803A611C(0, cam_gobj, 9U, 0xDU, 0U, 0xEU, 0U, 0x13U);
    if (lbLang_IsSavedLanguageUS() != 0) {
        HSD_SisLib_803A62A0(0, "SdClr.usd", "SIS_ClearData");
    } else {
        HSD_SisLib_803A62A0(0, "SdClr.dat", "SIS_ClearData");
    }

    fn_801803FC(state);
    fn_80168F7C();

    if (HSD_Randi(2) != 0) {
        var_r3 = 0xA;
    } else {
        var_r3 = 0xB;
    }
    lbAudioAx_80023F28(var_r3);

    Camera_8002F7AC(0);
    lb_800121FC(&state->x30, 0x280, 0x1E0, GX_TF_RGB5A3, 0);
    state->x2C = cam_gobj;
    lb_800138EC((s32) &state->x30, NULL, 2U, 0x32, 0.0f, 0.0f, 1.0f, 1.0f);
    lb_800138D8(state->x2C, 1);
    lb_800138CC(state->x2C, fn_8017FE54);

    if (gm_8016AE50()->x1_1 && var_r28 != 0) {
        if (state->x118 == 0) {
            un_802FF128(0x5A, 0x1AE, (s32) var_r28, 5);
        } else {
            un_802FF128(0x86, 0xC8, (s32) var_r28, 5);
        }
    }

    arg4->x58[0].xE = var_r28;
    fn_8017F2A4(&state->x84, 264.0f, 211.0f);
    PAD_STACK(0x30);
}

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

void gm_80180B18(void)
{
    int i;

    for (i = 0; i < 0x1B; i++) {
        u8 idx = gm_80164024((u8) i);
        lbl_80472E48.x14[gm_80164024((u8) i)] =
            (u32) *gmMainLib_8015D06C(idx) / 10;
    }
}

void gm_80180BA0(void)
{
    int i;

    for (i = 0; i < 0x1B; i++) {
        u8 idx = gm_80164024((u8) i);
        *gmMainLib_8015D06C(gm_80164024((u8) i)) = lbl_80472E48.x14[idx] * 0xA;
    }
}

void fn_80180C14(HSD_GObj* gobj)
{
    HSD_JObj* jobj = gobj->hsd_obj;

    if ((lbl_80472E48.x0 & 3) != 0) {
        HSD_JObjClearFlagsAll(jobj, 0x10);
        HSD_JObjAnimAll(jobj);
    }
}

static s32 lbl_804D65D4;

void fn_80180C60(HSD_GObj* gobj)
{
    typedef struct {
        u8 b76 : 2, b54 : 2, b32 : 2, b10 : 2;
    } x0_2bits;
    HSD_JObj* jobj = gobj->hsd_obj;
    s32 dist;
    s32 disp;
    s32 d;
    u32 b76;

    dist = (s32) (0.1f * Ground_801C57F0());
    if (dist < 0) {
        dist = 0;
    }

    lbl_80472E48.x80 = dist;
    b76 = ((u8) lbl_80472E48.x0 >> 6) & 3;

    if (b76 != 0 && (((u8) lbl_80472E48.x0 >> 4) & 3)) {
        ifTime_HideTimers();
        if (lbl_80472E48.x80 == lbl_80472E48.x84) {
            lbl_80472E48.x8C = lbl_80472E48.x8C + 1;
        } else {
            lbl_80472E48.x8C = 0;
        }
        if (lbl_80472E48.x8C > 0x3C) {
            ((x0_2bits*) &lbl_80472E48.x0)->b32 = 1;
            if (dist == 0 && !(lbl_80472E48.x0 & 3)) {
                ((x0_2bits*) &lbl_80472E48.x0)->b10 = 1;
            }
        }
    } else {
        if (b76 != 0) {
            ifTime_HideTimers();
            if (lbl_80472E48.x80 == lbl_80472E48.x84) {
                lbl_80472E48.x8C = lbl_80472E48.x8C + 1;
            } else {
                lbl_80472E48.x8C = 0;
            }
            if (lbl_80472E48.x8C > 0x78) {
                ((x0_2bits*) &lbl_80472E48.x0)->b32 = 1;
                if (!(lbl_80472E48.x0 & 3)) {
                    ((x0_2bits*) &lbl_80472E48.x0)->b10 = 1;
                }
            }
        } else if (gm_8016AEEC() == 0 && gm_8016AEFC() == 0x3B) {
            ((x0_2bits*) &lbl_80472E48.x0)->b76 = 1;
            ifTime_HideTimers();
            Player_80031790(0);
        }
        if (Ground_801C1DC0() != 0) {
            if (!(((u8) lbl_80472E48.x0 >> 6) & 3)) {
                ((x0_2bits*) &lbl_80472E48.x0)->b76 = 1;
                ifTime_HideTimers();
                Player_80031790(0);
            }
            if (!(((u8) lbl_80472E48.x0 >> 4) & 3)) {
                ((x0_2bits*) &lbl_80472E48.x0)->b54 = 1;
                Player_80031790(0);
            }
            lbl_80472E48.x8C = 0;
        }
    }

    if (!(((u8) lbl_80472E48.x0 >> 2) & 3)) {
        HSD_JObjReqAnimAll(jobj, 0.0f);
    } else if (lbl_80472E48.x0 & 3) {
        HSD_JObjSetFlagsAll(jobj, 0x10U);
    } else if (dist > lbl_80472E48.x14[gm_80164024((u8) lbl_80472E48.unk_4)]) {
        if (lbl_804D65D4 == 0) {
            lbAudioAx_800237A8(0x9C40, 0x7F, 0x40);
            lbAudioAx_800237A8(0x144, 0x7F, 0x40);
            gm_80167858((s32) (s8) lbl_80472E48.x10,
                        (s32) Player_GetNametagSlotID(0), 0xD, 0x5A);
            lbl_804D65D4 = 1;
        }
        HSD_JObjClearFlagsAll(
            HSD_JObjGetNext(
                HSD_JObjGetChild(
                    HSD_JObjGetChild(jobj))),
            0x10U);
    }

    if (lbLang_IsSavedLanguageUS() != 0) {
        disp = (s32) ((f64) (f32) dist / 0.304788);
    } else {
        disp = dist;
    }
    if (disp > 0x1869F) {
        disp = 0x1869F;
    }

    /* ones digit */
    HSD_JObjReqAnimAll(
        HSD_JObjGetNext(
            HSD_JObjGetNext(
                HSD_JObjGetChild(
                    HSD_JObjGetChild(jobj)))),
        (f32) (disp % 10));

    /* tens digit */
    HSD_JObjReqAnimAll(
        HSD_JObjGetNext(
            HSD_JObjGetNext(
                HSD_JObjGetNext(
                    HSD_JObjGetChild(
                        HSD_JObjGetChild(jobj))))),
        (f32) ((disp / 10) % 10));

    /* hundreds digit */
    d = disp / 100;
    if (d != 0) {
        HSD_JObjReqAnimAll(
            HSD_JObjGetNext(
                HSD_JObjGetNext(
                    HSD_JObjGetNext(
                        HSD_JObjGetNext(
                            HSD_JObjGetChild(
                                HSD_JObjGetChild(jobj)))))),
            (f32) (d % 10));
    } else {
        HSD_JObjReqAnimAll(
            HSD_JObjGetNext(
                HSD_JObjGetNext(
                    HSD_JObjGetNext(
                        HSD_JObjGetNext(
                            HSD_JObjGetChild(
                                HSD_JObjGetChild(jobj)))))),
            10.0f);
    }

    /* thousands digit */
    d = disp / 1000;
    if (d != 0) {
        HSD_JObjReqAnimAll(
            HSD_JObjGetNext(
                HSD_JObjGetNext(
                    HSD_JObjGetNext(
                        HSD_JObjGetNext(
                            HSD_JObjGetNext(
                                HSD_JObjGetChild(
                                    HSD_JObjGetChild(jobj))))))),
            (f32) (d % 10));
    } else {
        HSD_JObjReqAnimAll(
            HSD_JObjGetNext(
                HSD_JObjGetNext(
                    HSD_JObjGetNext(
                        HSD_JObjGetNext(
                            HSD_JObjGetNext(
                                HSD_JObjGetChild(
                                    HSD_JObjGetChild(jobj))))))),
            10.0f);
    }

    /* ten-thousands digit */
    d = disp / 10000;
    if (d != 0) {
        HSD_JObjReqAnimAll(
            HSD_JObjGetNext(
                HSD_JObjGetNext(
                    HSD_JObjGetNext(
                        HSD_JObjGetNext(
                            HSD_JObjGetNext(
                                HSD_JObjGetNext(
                                    HSD_JObjGetChild(
                                        HSD_JObjGetChild(jobj)))))))),
            (f32) (d % 10));
    } else {
        HSD_JObjReqAnimAll(
            HSD_JObjGetNext(
                HSD_JObjGetNext(
                    HSD_JObjGetNext(
                        HSD_JObjGetNext(
                            HSD_JObjGetNext(
                                HSD_JObjGetNext(
                                    HSD_JObjGetChild(
                                        HSD_JObjGetChild(jobj)))))))),
            10.0f);
    }

    HSD_JObjAnimAll(jobj);
    lbl_80472E48.x84 = lbl_80472E48.x80;
    if (lbl_80472E48.x80 > lbl_80472E48.x88 + 0xA) {
        lbl_80472E48.x88 = lbl_80472E48.x80;
        lbAudioAx_80023870(0xBB, 0x7F, 0x40, 0x8A);
    }
}

extern s32 lbl_804D65D8;

void fn_80181598(void)
{
    u32 mode;

    PAD_STACK(0x20);

    if (gm_801A4624() != 0) {
        return;
    }

    mode = lbl_80472E48.x0 & 3;

    if (mode != 0) {
        if (mode == 1) {
            lbAudioAx_800237A8(0xC0, 0x7F, 0x40);
            lbAudioAx_800237A8(0x148, 0x7F, 0x40);
            mode = 2;
            lbl_80472E48.x0 = (lbl_80472E48.x0 & ~3) | mode;
        }
        lbl_804D65D8 += 1;
        if (lbl_804D65D8 >= 0xF0 ||
            (lbl_804D65D8 > 0x3C &&
             (HSD_PadCopyStatus[lbl_80472E48.x10].trigger & 0x100)))
        {
            gm_8016B328();
            return;
        }
    }

    if (((lbl_80472E48.x0 >> 2) & 3) != 0 &&
        ((mode = lbl_80472E48.x0 & 3, mode == 0) || mode == 3))
    {
        lbl_80472E48.xC += 1;
        if (lbl_80472E48.xC > 0x3C &&
            (lbl_80472E48.xC >= 0xF0 ||
             (HSD_PadCopyStatus[lbl_80472E48.x10].trigger & 0x100)))
        {
            if (lbl_80472E48.x80 >
                lbl_80472E48.x14[gm_80164024((u8) lbl_80472E48.unk_4)])
            {
                lbl_80472E48.x14[gm_80164024((u8) lbl_80472E48.unk_4)] =
                    lbl_80472E48.x80;
            }
            gm_8016B328();
        }
    }
}

static DynamicModelDesc** lbl_804D65CC;
static DynamicModelDesc** lbl_804D65D0;
extern HSD_Archive* lbl_804D65C8;

void fn_80181708(void)
{
    HSD_GObj* new_var;
    typedef struct {
        u8 b76 : 2, b54 : 2, b32 : 2, b10 : 2;
    } x0_2bits;
    HSD_JObj* jobj;
    HSD_GObj* gobj;

    lbl_80472E48.x80 = 0;
    lbl_80472E48.x84 = 0;
    lbl_80472E48.x88 = 0;
    lbl_80472E48.x8C = 0;
    ((x0_2bits*) &lbl_80472E48.x0)->b76 = 0;
    ((x0_2bits*) &lbl_80472E48.x0)->b54 = 0;
    ((x0_2bits*) &lbl_80472E48.x0)->b32 = 0;
    ((x0_2bits*) &lbl_80472E48.x0)->b10 = 0;
    lbl_80472E48.xC = 0;
    lbl_80472E48.x10 = (s8) Player_GetPlayerId(0);
    lbl_804D65D4 = 0;
    lbl_804D65D8 = 0;

    HSD_GObj_SetupProc(
        GObj_Create(0xEU, 0x11U, 0U),
        (void (*)(HSD_GObj*)) fn_80181598, 0x15U);

    gobj = GObj_Create(0xEU, 0xFU, 0U);
    jobj = HSD_JObjLoadJoint((*lbl_804D65CC)->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xBU, 0U);
    HSD_GObj_SetupProc(gobj, fn_80180C14, 0x15U);
    gm_8016895C(jobj, *lbl_804D65CC, 0);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);
    HSD_JObjSetFlagsAll(jobj, 0x10U);

    gobj = (new_var = GObj_Create(0xEU, 0xFU, 0U));
    jobj = HSD_JObjLoadJoint((*lbl_804D65D0)->joint);
    HSD_GObjObject_80390A70(new_var, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(new_var, HSD_GObj_JObjCallback, 0xBU, 0U);
    HSD_GObj_SetupProc(new_var, fn_80180C60, 0x15U);
    gm_8016895C(jobj, *lbl_804D65D0, 0);
    HSD_JObjReqAnimAll(jobj, 10.0f);
    HSD_JObjAnimAll(jobj);
    HSD_JObjClearFlagsAll(jobj, 0x10U);

    HSD_JObjSetFlagsAll(
        HSD_JObjGetNext(HSD_JObjGetChild(HSD_JObjGetChild(jobj))),
        0x10U);
    HSD_JObjClearFlagsAll(
        HSD_JObjGetNext(HSD_JObjGetNext(HSD_JObjGetChild(
            HSD_JObjGetChild(jobj)))),
        0x10U);

    gm_80168F88();
}

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

struct {
    u8 x0;
    u16 x2;
    int x4;
    int x8;
    int xC;
    int x10;
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

extern u8 lbl_803D8D08[];

void gm_80181A44(int c_kind, int arg1, bool arg2)
{
    u8* base;

    base = lbl_803D8D08;

    switch (arg1) {
    case 0x21:
        (base + 0x6C)[c_kind] = arg2;
        break;
    case 0x22:
        (base + 0x12C)[c_kind] = arg2;
        break;
    case 0x23:
        (base + 0x1EC)[c_kind] = arg2;
        break;
    case 0x24:
        (base + 0x2AC)[c_kind] = arg2;
        break;
    case 0x25:
        (base + 0x36C)[c_kind] = arg2;
        break;
    case 0x26:
        (base + 0x42C)[c_kind] = arg2;
        break;
    }
}

void gm_80181AC8(int c_kind, int arg1, u16 arg2)
{
    u8* base;

    base = lbl_803D8D08;

    switch (arg1) {
    case 0x21:
        ((s16*) (base + 0x88))[c_kind] = arg2;
        break;
    case 0x22:
        ((s16*) (base + 0x148))[c_kind] = arg2;
        break;
    case 0x23:
        ((s16*) (base + 0x208))[c_kind] = arg2;
        break;
    case 0x24:
        ((s16*) (base + 0x2C8))[c_kind] = arg2;
        break;
    case 0x25:
        ((s16*) (base + 0x388))[c_kind] = arg2;
        break;
    case 0x26:
        ((s16*) (base + 0x448))[c_kind] = arg2;
        break;
    }
}

void gm_80181B64(int c_kind, int arg1, s32 arg2)
{
    u8* base;

    base = lbl_803D8D08;

    switch (arg1) {
    case 0x21:
        ((s32*) base)[c_kind] = arg2;
        break;
    case 0x22:
        ((s32*) (base + 0xC0))[c_kind] = arg2;
        break;
    case 0x23:
        ((s32*) (base + 0x180))[c_kind] = arg2;
        break;
    case 0x24:
        ((s32*) (base + 0x240))[c_kind] = arg2;
        break;
    case 0x25:
        ((s32*) (base + 0x300))[c_kind] = arg2;
        break;
    case 0x26:
        ((s32*) (base + 0x3C0))[c_kind] = arg2;
        break;
    }
}

#pragma dont_inline on
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
#pragma dont_inline reset

s32 fn_80181C80(s32 arg0)
{
    s32 var_r29;
    s32 var_r30;
    volatile s32 sp38;
    PlayerInitData sp10;

    gm_801A4310();
    var_r30 = 0;
    sp10 = lbl_80472ED8.xC;

    for (var_r29 = 1; var_r29 < 6; var_r29++) {
        if (Player_GetFalls(var_r29) == 0 &&
            Player_GetPlayerSlotType(var_r29) != Gm_PKind_NA)
        {
            var_r30++;
        } else {
            sp38 = var_r29;
        }
    }

    if ((s32) lbl_80472ED8.x54[arg0].x4 > var_r30 &&
        lbl_80472ED8.x8 > 0x5A)
    {
        if (Player_GetPlayerSlotType(sp38) != Gm_PKind_NA) {
            Player_SetFalls(sp38, 0);
            Player_SetSuicideCount(sp38, 0);
            fn_8016EF98(sp38);
        }
        lbl_80472ED8.x54[arg0].x0 = -2;
        sp10.team = !Player_GetTeam(0);
        sp10.c_kind = lbl_80472ED8.x54[arg0].x5;
        sp10.cpu_level = lbl_80472ED8.x54[arg0].x6;
        sp10.xE = lbl_80472ED8.x54[arg0].x7;
        sp10.x18 = lbl_80472ED8.x54[arg0].x8;
        sp10.x1C = lbl_80472ED8.x54[arg0].xC;
        gm_8016EDDC(sp38, &sp10);
        Player_SetNametagSlotID(sp38, 0x78);
        un_802FD28C(sp38);
        lbl_80472ED8.x0 += 1;
    }
    return lbl_80472ED8.x0;
    PAD_STACK(8);
}

void fn_80181E18(void)
{
    s32 mode;
    s32 var_r29;
    s32 next;
    s32 temp;
    s32 count;
    s32 i;

    mode = gm_801A4310();

    if (lbl_80472ED8.x8 <= 0x5A) {
        lbl_80472ED8.x8 += 1;
    }

    if (mode < 0x25) {
        if (mode < 0x23) {
            if (mode < 0x21) {

            } else {
                Player_GetFalls(0);
            }
        } else if (gm_8016AEEC() == 0 && gm_8016AEFC() == 0x3B) {
            lbl_80472ED8.x6BC = 1;
            gm_8016B33C(7);
            gm_8016B328();
        }
    } else if (mode < 0x27) {
        if (Player_GetFalls(0) != 0) {
            gm_8016B33C(5);
            gm_8016B328();
        }
    }

    for (var_r29 = 0; var_r29 < 101; var_r29++) {
        if (lbl_80472ED8.x54[var_r29].x0 == -2) {
            continue;
        }

        if (lbl_80472ED8.x6C4 < 0x23) {
            if (lbl_80472ED8.x6C4 < 0x21) {

            } else {
                lbl_80472ED8.x6C0 = gm_8016AEDC();
            }
        }

        temp = var_r29 - fn_80181BFC(NULL);
        if (temp < 0) {
            temp = 0;
        }
        lbl_80472ED8.x6BE = (s16) (temp + lbl_80472ED8.x4);

        switch (mode) {
        case 0x21:
            temp = var_r29 - fn_80181BFC(NULL);
            if (temp < 0) temp = 0;
            ifStock_802FA2D0(0xA - (temp + lbl_80472ED8.x4));
            break;
        case 0x22:
            temp = var_r29 - fn_80181BFC(NULL);
            if (temp < 0) temp = 0;
            ifStock_802FA2D0(0x64 - (temp + lbl_80472ED8.x4));
            break;
        default:
            temp = var_r29 - fn_80181BFC(NULL);
            if (temp < 0) temp = 0;
            ifStock_802FA2D0(temp + lbl_80472ED8.x4);
            break;
        }

        next = lbl_80472ED8.x54[var_r29].x0;

        if (next == -1) {
            fn_80181C80(var_r29);
            return;
        }

        if (next == 0x3E7) {
            count = 0;
            for (i = 1; i < 6; i++) {
                if (Player_GetFalls(i) == 0 &&
                    Player_GetPlayerSlotType(i) != Gm_PKind_NA)
                {
                    count += 1;
                }
            }
            if (count == 0) {
                lbl_80472ED8.x6BC = 1;
                gm_8016B33C(7);
                gm_8016B328();
            }
        } else {
            if (next < var_r29) {
                s32 k;
                for (k = next; k < var_r29; k++) {
                    lbl_80472ED8.x54[k].x0 = -1;
                    lbl_80472ED8.x4 += 1;
                }
            }
            fn_80181C80(lbl_80472ED8.x54[var_r29].x0);
            temp = var_r29 - fn_80181BFC(NULL);
            if (temp < 0) {
                temp = 0;
            }
            ifStock_802FA2D0(temp + lbl_80472ED8.x4);
        }
        break;
    }
    PAD_STACK(16);
}

void gm_80182174(void)
{
    u8* data = lbl_803D8D08;
    s32 mode;
    s32 i;
    RegClearSpawnEntry* src;
    RegClearSpawnEntry* dst;

    mode = gm_801A4310();

    lbArchive_80016DBC(
        (const char*) &data[0x480], &lbl_80472ED8.x6A4,
        (const char*) &data[0x490], &lbl_80472ED8.x6A8,
        (const char*) &data[0x4AC], &lbl_80472ED8.x6AC,
        (const char*) &data[0x4C8], &lbl_80472ED8.x6B0,
        (const char*) &data[0x4E4], &lbl_80472ED8.x6B4,
        (const char*) &data[0x500], &lbl_80472ED8.x6B8,
        (const char*) &data[0x51C], 0);

    lbl_80472ED8.x0 = 0;
    lbl_80472ED8.x4 = 0;
    lbl_80472ED8.x8 = 0;

    gm_8016795C(&lbl_80472ED8.xC);

    lbl_80472ED8.xC.c_kind = 0x1B;
    lbl_80472ED8.xC.slot_type = 1;
    lbl_80472ED8.xC.stocks = 1;
    lbl_80472ED8.xC.xD_b4 = 1;

    switch (mode) {
    case 0x21:
        src = lbl_80472ED8.x6A4;
        dst = lbl_80472ED8.x54;
        for (i = 0; i < 101; i++) {
            dst->x0 = src->x0;
            dst->x4 = src->x4;
            dst->x5 = src->x5;
            dst->x8 = src->x8;
            dst->xC = src->xC;
            dst->x6 = src->x6;
            dst->x7 = src->x7;
            if (src->x0 == 0x3E7) break;
            src++;
            dst++;
        }
        break;
    case 0x22:
        src = lbl_80472ED8.x6A8;
        dst = lbl_80472ED8.x54;
        for (i = 0; i < 101; i++) {
            dst->x0 = src->x0;
            dst->x4 = src->x4;
            dst->x5 = src->x5;
            dst->x8 = src->x8;
            dst->xC = src->xC;
            dst->x6 = src->x6;
            dst->x7 = src->x7;
            if (src->x0 == 0x3E7) break;
            src++;
            dst++;
        }
        break;
    case 0x23:
        src = lbl_80472ED8.x6AC;
        dst = lbl_80472ED8.x54;
        for (i = 0; i < 101; i++) {
            dst->x0 = src->x0;
            dst->x4 = src->x4;
            dst->x5 = src->x5;
            dst->x8 = src->x8;
            dst->xC = src->xC;
            dst->x6 = src->x6;
            dst->x7 = src->x7;
            if (src->x0 == 0x3E7) break;
            src++;
            dst++;
        }
        break;
    case 0x24:
        src = lbl_80472ED8.x6B0;
        dst = lbl_80472ED8.x54;
        for (i = 0; i < 101; i++) {
            dst->x0 = src->x0;
            dst->x4 = src->x4;
            dst->x5 = src->x5;
            dst->x8 = src->x8;
            dst->xC = src->xC;
            dst->x6 = src->x6;
            dst->x7 = src->x7;
            if (src->x0 == 0x3E7) break;
            src++;
            dst++;
        }
        break;
    case 0x25:
        src = lbl_80472ED8.x6B4;
        dst = lbl_80472ED8.x54;
        for (i = 0; i < 101; i++) {
            dst->x0 = src->x0;
            dst->x4 = src->x4;
            dst->x5 = src->x5;
            dst->x8 = src->x8;
            dst->xC = src->xC;
            dst->x6 = src->x6;
            dst->x7 = src->x7;
            if (src->x0 == 0x3E7) break;
            src++;
            dst++;
        }
        break;
    case 0x26:
        src = lbl_80472ED8.x6B8;
        dst = lbl_80472ED8.x54;
        for (i = 0; i < 101; i++) {
            dst->x0 = src->x0;
            dst->x4 = src->x4;
            dst->x5 = src->x5;
            dst->x8 = src->x8;
            dst->xC = src->xC;
            dst->x6 = src->x6;
            dst->x7 = src->x7;
            if (src->x0 == 0x3E7) break;
            src++;
            dst++;
        }
        break;
    }

    lbl_80472ED8.x6CC = Player_GetPlayerId(0);
    lbl_80472ED8.x6CD = Player_GetNametagSlotID(0);
    HSD_GObj_SetupProc(GObj_Create(0xFU, 0x11U, 0U),
                       (HSD_GObjEvent) fn_80181E18, 0x15U);
    gm_80168F88();
    PAD_STACK(8);
}

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

void gm_80182554(int arg0, int arg1)
{
    lbl_80472ED8.x6C8 = arg0;
    lbl_80472ED8.x6C4 = arg1;
    lbl_80472ED8.x6BC = 0;
    lbl_80472ED8.x6C0 = 0;
    lbl_80472ED8.x6BE = 0;
}

typedef struct {
    /* 0x00 */ u32 scores[27];
    /* 0x6C */ u8 icons[28];
    /* 0x88 */ u16 times[28];
} RecordBlock; /* 0xC0 */

s32 gm_80182578(void)
{
    RecordBlock* blocks = (RecordBlock*) lbl_803D8D08;
    int idx = lbl_80472ED8.x6C8;
    s32 mode = lbl_80472ED8.x6C4;
    int time_val;
    u32 score_val;

    switch (mode) {
    case 33: time_val = blocks[0].times[idx]; break;
    case 34: time_val = blocks[1].times[idx]; break;
    case 35: time_val = blocks[2].times[idx]; break;
    case 36: time_val = blocks[3].times[idx]; break;
    case 37: time_val = blocks[4].times[idx]; break;
    case 38: time_val = blocks[5].times[idx]; break;
    default: time_val = 0; break;
    }

    switch (mode) {
    case 33: score_val = blocks[0].scores[idx]; break;
    case 34: score_val = blocks[1].scores[idx]; break;
    case 35: score_val = blocks[2].scores[idx]; break;
    case 36: score_val = blocks[3].scores[idx]; break;
    case 37: score_val = blocks[4].scores[idx]; break;
    case 38: score_val = blocks[5].scores[idx]; break;
    default: score_val = 0; break;
    }

    if (mode < 0x25) {
        if (mode < 0x23) {
            if (mode < 0x21) {
                return mode;
            }
            if (mode == 0x21) {
                mode = gmMainLib_8015D6BC(gm_80164024((u8) idx));
            } else {
                mode = gmMainLib_8015D710(gm_80164024((u8) idx));
            }
            if ((u8) lbl_80472ED8.x6BC != 0) {
                u32 score_store = (u32) lbl_80472ED8.x6C0;
                if (score_store < score_val) {
                    int m = lbl_80472ED8.x6C4;
                    int i = lbl_80472ED8.x6C8;
                    switch (m) {
                    case 33: blocks[0].icons[i] = (u8) lbl_80472ED8.x6BC; break;
                    case 34: blocks[1].icons[i] = (u8) lbl_80472ED8.x6BC; break;
                    case 35: blocks[2].icons[i] = (u8) lbl_80472ED8.x6BC; break;
                    case 36: blocks[3].icons[i] = (u8) lbl_80472ED8.x6BC; break;
                    case 37: blocks[4].icons[i] = (u8) lbl_80472ED8.x6BC; break;
                    case 38: blocks[5].icons[i] = (u8) lbl_80472ED8.x6BC; break;
                    }
                    switch (m) {
                    case 33: blocks[0].scores[i] = score_store; break;
                    case 34: blocks[1].scores[i] = score_store; break;
                    case 35: blocks[2].scores[i] = score_store; break;
                    case 36: blocks[3].scores[i] = score_store; break;
                    case 37: blocks[4].scores[i] = score_store; break;
                    case 38: blocks[5].scores[i] = score_store; break;
                    }
                    {
                        u16 time_store = lbl_80472ED8.x6BE;
                        switch (m) {
                        case 33: blocks[0].times[i] = time_store; break;
                        case 34: blocks[1].times[i] = time_store; break;
                        case 35: blocks[2].times[i] = time_store; break;
                        case 36: blocks[3].times[i] = time_store; break;
                        case 37: blocks[4].times[i] = time_store; break;
                        case 38: blocks[5].times[i] = time_store; break;
                        }
                    }
                }
                return mode;
            }
            if ((s32) lbl_80472ED8.x6BE > (s32) time_val && mode == 0) {
                int m = lbl_80472ED8.x6C4;
                int i = lbl_80472ED8.x6C8;
                switch (m) {
                case 33: blocks[0].times[i] = (u16) lbl_80472ED8.x6BE; break;
                case 34: blocks[1].times[i] = (u16) lbl_80472ED8.x6BE; break;
                case 35: blocks[2].times[i] = (u16) lbl_80472ED8.x6BE; break;
                case 36: blocks[3].times[i] = (u16) lbl_80472ED8.x6BE; break;
                case 37: blocks[4].times[i] = (u16) lbl_80472ED8.x6BE; break;
                case 38: blocks[5].times[i] = (u16) lbl_80472ED8.x6BE; break;
                }
            }
            return mode;
        }
        if ((u8) lbl_80472ED8.x6BC != 0) {
            u16 time_store = lbl_80472ED8.x6BE;
            if ((s32) time_store > (s32) time_val) {
                switch (mode) {
                case 33: blocks[0].icons[idx] = (u8) lbl_80472ED8.x6BC; break;
                case 34: blocks[1].icons[idx] = (u8) lbl_80472ED8.x6BC; break;
                case 35: blocks[2].icons[idx] = (u8) lbl_80472ED8.x6BC; break;
                case 36: blocks[3].icons[idx] = (u8) lbl_80472ED8.x6BC; break;
                case 37: blocks[4].icons[idx] = (u8) lbl_80472ED8.x6BC; break;
                case 38: blocks[5].icons[idx] = (u8) lbl_80472ED8.x6BC; break;
                }
                switch (mode) {
                case 33: blocks[0].times[idx] = time_store; break;
                case 34: blocks[1].times[idx] = time_store; break;
                case 35: blocks[2].times[idx] = time_store; break;
                case 36: blocks[3].times[idx] = time_store; break;
                case 37: blocks[4].times[idx] = time_store; break;
                case 38: blocks[5].times[idx] = time_store; break;
                }
            }
        }
        return mode;
    } else if (mode < 0x27) {
        if ((s32) lbl_80472ED8.x6BE > (s32) time_val) {
            switch (mode) {
            case 33: blocks[0].times[idx] = (u16) lbl_80472ED8.x6BE; break;
            case 34: blocks[1].times[idx] = (u16) lbl_80472ED8.x6BE; break;
            case 35: blocks[2].times[idx] = (u16) lbl_80472ED8.x6BE; break;
            case 36: blocks[3].times[idx] = (u16) lbl_80472ED8.x6BE; break;
            case 37: blocks[4].times[idx] = (u16) lbl_80472ED8.x6BE; break;
            case 38: blocks[5].times[idx] = (u16) lbl_80472ED8.x6BE; break;
            }
        }
        return mode;
    }
    return mode;
    PAD_STACK(0x48);
}

void fn_80182B5C(void)
{
    RecordBlock* blocks = (RecordBlock*) lbl_803D8D08;
    int mode = lbl_80472ED8.x6C4;
    int idx = lbl_80472ED8.x6C8;
    int var_r6;
    u32 var_r30;

    switch (mode) {
    case 33: var_r6 = blocks[0].times[idx]; break;
    case 34: var_r6 = blocks[1].times[idx]; break;
    case 35: var_r6 = blocks[2].times[idx]; break;
    case 36: var_r6 = blocks[3].times[idx]; break;
    case 37: var_r6 = blocks[4].times[idx]; break;
    case 38: var_r6 = blocks[5].times[idx]; break;
    default: var_r6 = 0; break;
    }

    switch (mode) {
    case 33: var_r30 = blocks[0].scores[idx]; break;
    case 34: var_r30 = blocks[1].scores[idx]; break;
    case 35: var_r30 = blocks[2].scores[idx]; break;
    case 36: var_r30 = blocks[3].scores[idx]; break;
    case 37: var_r30 = blocks[4].scores[idx]; break;
    case 38: var_r30 = blocks[5].scores[idx]; break;
    default: var_r30 = 0; break;
    }

    switch (mode) {
    case 33:
        gmMainLib_8015D6BC(gm_80164024((u8) idx));
        goto func;
    case 34:
        gmMainLib_8015D710(gm_80164024((u8) idx));
    func:
        if (lbl_80472ED8.x6BC != 0) {
            if ((u32) lbl_80472ED8.x6C0 < var_r30) {
                gm_8016B350(0x9C40);
                gm_8016B364(0x144);
                gm_80167858((s32) lbl_80472ED8.x6CC, (s32) lbl_80472ED8.x6CD,
                            0xD, 0x5A);
                return;
            }
        } else {
            gm_8016B364(0x148);
            gm_8016B378(0x28);
            return;
        }
        break;
    case 35:
    case 36:
        if (lbl_80472ED8.x6BC != 0 && (s32) lbl_80472ED8.x6BE > var_r6) {
            gm_8016B350(0x9C40);
            gm_8016B364(0x144);
            gm_80167858((s32) lbl_80472ED8.x6CC, (s32) lbl_80472ED8.x6CD, 0xD,
                        0x5A);
        }
        break;
    case 37:
    case 38:
        if ((s32) lbl_80472ED8.x6BE > var_r6) {
            gm_8016B350(0x9C40);
            gm_8016B364(0x144);
            gm_80167858((s32) lbl_80472ED8.x6CC,
                        (s32) lbl_80472ED8.x6CD, 0xD, 0x5A);
        }
        break;
    }
    PAD_STACK(24);
}

static UnkMultimanData lbl_804D65E0;

UnkMultimanData* gm_80182DF0(int c_kind, int arg1)
{
    UnkMultimanData* result = &lbl_804D65E0;
    u8* base = lbl_803D8D08;

    switch (arg1) {
    case 33:
        result->x0_0 = (base + 0x6C)[c_kind];
        result->x2 = ((u16*)(base + 0x88))[c_kind];
        result->x4 = ((s32*)base)[c_kind];
        break;
    case 34:
        result->x0_0 = (base + 0x12C)[c_kind];
        result->x2 = ((u16*)(base + 0x148))[c_kind];
        result->x4 = ((s32*)(base + 0xC0))[c_kind];
        break;
    case 35:
        result->x0_0 = (base + 0x1EC)[c_kind];
        result->x2 = ((u16*)(base + 0x208))[c_kind];
        break;
    case 36:
        result->x0_0 = (base + 0x2AC)[c_kind];
        result->x2 = ((u16*)(base + 0x2C8))[c_kind];
        break;
    case 37:
        result->x0_0 = (base + 0x36C)[c_kind];
        result->x2 = ((u16*)(base + 0x388))[c_kind];
        break;
    case 38:
        result->x0_0 = (base + 0x42C)[c_kind];
        result->x2 = ((u16*)(base + 0x448))[c_kind];
        break;
    }
    return result;
}

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
    HSD_GObj_SetupProc(GObj_Create(0xF, 0x11, 0), fn_80182F40, 0x15);
}
