#include "gm_17C0.h"

#include "gm_unsplit.h"

#include <math_ppc.h>
#include <dolphin/gx.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/random.h>
#include <sysdolphin/baselib/tobj.h>
#include <sysdolphin/baselib/util.h>
#include <melee/cm/camera.h>
#include <melee/ef/efasync.h>
#include <melee/ef/eflib.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ftbosslib.h>
#include <melee/ft/ftlib.h>
#include <melee/gm/types.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gr/ground.h>
#include <melee/gr/grpushon.h>
#include <melee/gr/stage.h>
#include <melee/it/item.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbbgflash.h>
#include <melee/mp/mpcoll.h>
#include <melee/pl/player.h>
#include <melee/sc/types.h>

struct lbl_80472D28_t {
    /*   +0 */ char pad_0[0x104];
    /* +104 */ int x104;
};

struct lbl_80472E48_t {
    /* 0x00 */ char pad_0[4];
    /* 0x04 */ s32 unk_4;        /* inferred */
    /* 0x08 */ s32 unk_8;        /* inferred */
    /* 0x0C */ char pad_C[0x74]; /* maybe part of unk_8[0x1E]? */
}; /* size = 0x80 */
STATIC_ASSERT(sizeof(struct lbl_80472E48_t) == 0x80);

static struct lbl_804706C0_t {
    int x0;
    int x4;
    int x8;
    int xC; // HP (stamina)
    int x10;
    int x14;
} lbl_804706C0;

static UnkAllstarData lbl_80472C30;
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
            lbBgFlash_800205F0();
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
    UnkAllstarData* temp_r30;

    temp_r30 = fn_8017DF28();
    temp_r31 = gm_8016AE44();
    temp_r31->timer_seconds = grPushOn_80219230(temp_r30->x0);
}

void gm_8017C838(void)
{
    s8 sp10[3];

    lbl_8046B6A0_t* temp_r3;
    int i;
    s8 var_r3;
    s8* var_r31;
    UnkAllstarData* temp_r30;

    PAD_STACK(8);

    temp_r30 = gm_8017E424();
    temp_r3 = gm_8016AE38();
    var_r31 = sp10;
    sp10[0] = 0x21;
    sp10[1] = 0x21;
    sp10[2] = 0x21;
    switch (temp_r3->x24C8.xE) {
    case 0x3B:
        sp10[0] = 0xE;
        break;
    case 0x3F:
        sp10[0] = 6;
        break;
    case 0x44:
        sp10[0] = 4;
        if (temp_r30->x0 == 4 && temp_r30->x1 == 0) {
            var_r3 = 1;
        } else {
            var_r3 = 0;
        }
        ftLib_80087610(var_r3);
        break;
    case 0x48:
        sp10[0] = 0xC;
        if (gm_80164840(0x18) != 0) {
            sp10[1] = 0x17;
        }
        if (gm_80164840(0xF) != 0) {
            sp10[2] = 0xF;
        }
        break;
    case 0x4C:
        sp10[0] = 0xA;
        sp10[1] = 0xB;
        break;
    case 0x4E:
        sp10[0] = 0x1D;
        sp10[1] = 0x1E;
        break;
    }

    for (i = 0; i < 3; i++) {
        if (*var_r31 != (s8) FTKIND_MAX) {
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

void gm_8017C9A8(DebugGameOverData* arg0, UnkAllstarData* arg1, u8 arg2)
{
    PAD_STACK(8);
    arg0->x0 = arg1->xC.xC;
    arg0->x8 = arg2;
    arg0->x10 = arg1->x0;
    arg0->x14 = arg1->x3;
    arg0->x15 = arg1->x4;
    arg0->x18 = gm_801623D8();
    arg0->x16 = lbl_803B7C08[arg2][arg1->x2];
}

/// #gm_8017CA38

/// #gm_8017CBAC

/// #gm_8017CD94

/// #gm_8017CE34

/// #gm_8017D7AC

/// #fn_8017D9C0

void gm_8017DB58(void* arg0)
{
    M2C_FIELD(arg0, s8*, 0) = 0x21;
    M2C_FIELD(arg0, s8*, 0xC) = 0x21;
    M2C_FIELD(arg0, s8*, 0x18) = 0x21;
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

UnkAllstarData* fn_8017DEC8(int arg0)
{
    switch (arg0) {
    case 0:
        return gm_8017E424();
    case 1:
        return gm_8017EB30();
    case 2:
        return &gm_80473A18;
    default:
        return NULL;
    }
}

UnkAllstarData* fn_8017DF28(void)
{
    switch (gm_801A4310()) {
    case MJ_CLASSIC:
        return gm_8017EB30();
    case MJ_ADVENTURE:
        return gm_8017E424();
    case MJ_ALLSTAR:
        return &gm_80473A18;
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
    UnkAllstarData* var_r3 = fn_8017DEC8(arg0);
    if (var_r3 != NULL) {
        return var_r3->x2;
    }
    return -1;
}

int gm_8017E068(void)
{
    UnkAllstarData* var_r3 = fn_8017DF28();
    if (var_r3 != NULL) {
        return var_r3->x2;
    }
    return -1;
}

int fn_8017E0E4(void)
{
    UnkAllstarData* var_r3 = fn_8017DF28();
    if (var_r3 != NULL) {
        return var_r3->xC.x0;
    }
    return -1;
}

bool fn_8017E160(void)
{
    UnkAllstarData* var_r3 = fn_8017DF28();
    struct UnkAllstarData_xC* temp_r3_2;

    if (var_r3 != NULL) {
        if (var_r3->xC.x18 != 0x21) {
            return true;
        }
        temp_r3_2 = &var_r3->xC;
        if (temp_r3_2->x24 != 0x21) {
            return true;
        }
        if (temp_r3_2->x30 != 0x21) {
            return true;
        }
        return false;
    }
    return false;
}

/// #fn_8017E21C

/// #gm_8017E280

/// #fn_8017E318

/// #fn_8017E3C8

UnkAllstarData* gm_8017E424(void)
{
    return &lbl_80472C30;
}

u8 gm_8017E430(void)
{
    return lbl_80472C30.x3;
}

/// #gm_8017E440

/// #gm_8017E48C

/// #gm_8017E4C4

/// #gm_8017E500

/// #gm_8017E528

/// #gm_8017E578

/// #gm_8017E5C8

/// #gm_8017E5FC

/// #gm_8017E630

/// #gm_8017E664

/// #gm_8017E6B4

/// #gm_8017E704

/// #gm_8017E738

/// #gm_8017E76C

/// #gm_8017E7A0

/// #gm_8017E7E0

/// #gm_8017E7FC

/// #fn_8017E8A4

UnkAllstarData* gm_8017EB30(void)
{
    return &lbl_80472CB0;
}

/// #gm_8017EB3C

/// #gm_8017EB64

/// #gm_8017EB98

/// #gm_8017EBCC

/// #gm_8017EC00

/// #gm_8017EC50

/// #gm_8017ECA0

/// #gm_8017ECD4

/// #gm_8017ED08

/// #gm_8017ED3C

/// #gm_8017ED8C

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

/// #fn_80180AC0

s32 gm_80180AE4(void)
{
    return lbl_80472EC8[0] * 0xA;
}

/// #gm_80180AF4

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

u8 gm_80181A14(void)
{
    return lbl_80473594.x0;
}

u16 gm_80181A24(void)
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
        if (Player_GetFalls(i) == 0 && Player_GetPlayerSlotType(i) != 3) {
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
        gm_801A42E8(0);
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
