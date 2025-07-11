#include "gm_1601.h"

#include "gm_16AE.static.h"

#include "gmmain_lib.h"

#include <melee/cm/camera.h>
#include <melee/db/db.h>
#include <melee/ef/efasync.h>
#include <melee/ef/eflib.h>
#include <melee/ft/ftdevice.h>
#include <melee/ft/ftlib.h>
#include <melee/gm/gm_1A45.h>
#include <melee/gm/gmpause.h>
#include <melee/gr/ground.h>
#include <melee/gr/grstadium.h>
#include <melee/gr/stage.h>
#include <melee/if/ifall.h>
#include <melee/if/ifstatus.h>
#include <melee/if/iftime.h>
#include <melee/it/it_266F.h>
#include <melee/it/item.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lb_0192.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbbgflash.h>
#include <melee/lb/lbrefract.h>
#include <melee/lb/lbtime.h>
#include <melee/mn/types.h>
#include <melee/mp/mpcoll.h>
#include <melee/pl/player.h>
#include <melee/un/un_2FC9.h>
#include <melee/vi/vi1202.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/gobjproc.h>

#include <m2c_macros.h>

lbl_8046B6A0_t* gm_8016AE38(void)
{
    return &lbl_8046B6A0;
}

lbl_8046B6A0_t* gm_8016AE44(void)
{
    return &lbl_8046B6A0;
}

struct StartMeleeRules* gm_8016AE50(void)
{
    return &lbl_8046B6A0.x24C8;
}

/// #fn_8016AE60

bool gm_8016AE80(void)
{
    return lbl_8046B6A0.x24C8.xB;
}

f32 gm_8016AE94(void)
{
    return lbl_8046B6A0.unk_34;
}

u64 gm_8016AEA4(void)
{
    return lbl_8046B6A0.x24C8.x20;
}

s32 gm_8016AEB8(void)
{
    return lbl_8046B6A0.x24C8.x28;
}

bool gm_8016AEC8(void)
{
    return lbl_8046B6A0.x24C8.xC;
}

u32 gm_8016AEDC(void)
{
    return lbl_8046B6A0.unk_24;
}

bool gm_8016AEEC(void)
{
    return lbl_8046B6A0.unk_28;
}

u16 gm_8016AEFC(void)
{
    return lbl_8046B6A0.unk_2C;
}

/// #gm_8016AF0C

/// #gm_8016AF88

u16 gm_8016B004(void)
{
    return lbl_8046B6A0.x24C8.xE;
}

/// #gm_8016B014

/// #gm_8016B094

/// #gm_8016B0B4

bool gm_8016B0D4(void)
{
    return lbl_8046B6A0.x24C8.x1_7;
}

bool gm_8016B0E8(void)
{
    return lbl_8046B6A0.x24C8.x4_2;
}

bool gm_8016B0FC(void)
{
    return lbl_8046B6A0.x24C8.x2_3;
}

bool gm_8016B110(void)
{
    return lbl_8046B6A0.x24C8.x0_7;
}

bool gm_8016B124(void)
{
    return lbl_8046B6A0.x24C8.x2_1;
}

void fn_8016B138(void)
{
    lbl_8046B6A0.x24C8.x8 = 0;
}

/// #gm_8016B14C

/// #gm_8016B168

/// #gm_8016B184

/// #gm_8016B1A8

bool gm_8016B1C4(void)
{
    return lbl_8046B6A0.x24C8.x5_2;
}

bool gm_8016B1D8(void)
{
    return lbl_8046B6A0.x24C8.x5_3;
}

bool gm_8016B1EC(void)
{
    return lbl_8046B6A0.unk_0 == 0;
}

/// #gm_8016B204

bool gm_8016B238(void)
{
    return lbl_8046B6A0.x24C8.x6;
}

f32 gm_8016B248(void)
{
    return lbl_8046B6A0.x24C8.x30;
}

/// #gm_8016B258

/// #gm_SetGameSpeed

/// #gm_ResetGameSpeed

void gm_8016B328(void)
{
    M2C_FIELD(&lbl_8046B6A0, s8*, 6) = 1;
}

void gm_8016B33C(s32 arg0)
{
    M2C_FIELD(&lbl_8046B6A0, s8*, 0xB) = arg0 + 1;
}

void gm_8016B350(s32 arg0)
{
    lbl_8046B6A0.unk_10 = arg0 + 1;
}

void gm_8016B364(s32 arg0)
{
    lbl_8046B6A0.unk_14 = arg0 + 1;
}

void gm_8016B378(s8 arg0)
{
    M2C_FIELD(&lbl_8046B6A0, s8*, 0x18) = arg0;
}

void fn_8016B388(ssize_t arg0, s16 arg1)
{
    M2C_FIELD((&lbl_8046B6A0 + (arg0 * 0xE)), s16*, 0x3E) = arg1;
}

/// #gm_8016B3A0

/// #gm_8016B3D8

/// #gm_8016B41C

/// #gm_8016B498

/// #fn_8016B4BC

/// #fn_8016B510

#pragma push
#pragma dont_inline on
int gm_8016B558(void)
{
    int i;
    int count;
    count = 0;
    for (i = 0; i < 6; i++) {
        if (Player_GetPlayerSlotType(i) != 3) {
            count++;
        }
    }
    return count;
}
#pragma pop

/// #fn_8016B5B0

/// #gm_8016B6E8

u8 fn_8016B728(void)
{
    return M2C_FIELD(&lbl_8046B6A0, u8*, 0xC);
}

/// #fn_8016B738

UNK_T gm_8016B774(void)
{
    return &M2C_FIELD(&lbl_8046B6A0, UNK_T*, 0x24C);
}

/// #fn_8016B784

/// #fn_8016B7B4

/// #fn_8016B7F8

/// #fn_8016B88C

/// #gm_8016B8D4

/// #fn_8016B918

/// #fn_8016BAF4

/// #fn_8016BBB4

/// #fn_8016BC74

/// #gm_8016BE80

/// #fn_8016BF74

/// #fn_8016C0C8

/// #fn_8016C35C

/// #fn_8016C46C

/// #fn_8016C4F4

/// #gm_8016C5C0

/// #gm_8016C658

/// #gm_8016C6C0

/// #gm_8016C75C

void fn_8016C7D0(HSD_GObj* gobj)
{
    fn_80171DC4(gobj);
}

/// #fn_8016C7F0

/// #fn_8016CA68

/// #fn_8016CBE8

/// #fn_8016CD98

/// #fn_8016CF4C

/// #fn_8016CFE0

/// #gm_8016D32C_OnFrame

/// #fn_8016D538

/// #fn_8016D634

void gm_8016D800(void)
{
    PAD_STACK(8);
    if (lbl_8046B6A0.x24C8.x48 != NULL) {
        lbl_8046B6A0.x24C8.x48();
    }
    switch (lbl_8046B6A0.unk_0) {
    case 0:
        fn_8016CFE0();
        break;
    case 1:
        fn_8016D634();
        break;
    case 2:
        if (fn_80180AC0() != 0) {
            lbl_8046B6A0.unk_0 = 3;
        }
        break;
    case 3:
        gm_801A4B60();
        break;
    }
    if (lbl_8046B6A0.x24C8.x4C != NULL) {
        lbl_8046B6A0.x24C8.x4C();
    }
}

void fn_8016D8AC(int arg0, struct PlayerInitData* arg1)
{
    Player_SetSlottype(arg0, arg1->x1);
    Player_SetPlayerCharacter(arg0, arg1->x0);

    lbl_8046B6A0.unk_38[arg0].x0 = arg1->x0;

    Player_SetStocks(arg0, arg1->x2);
    Player_SetCostumeId(arg0, arg1->x3);
    Player_SetControllerIndex(arg0, arg1->x7);
    if (arg1->x4 == 0) {
        Player_SetPlayerId(arg0, arg0);
    } else {
        Player_SetPlayerId(arg0, arg1->x4 - 1);
    }
    if (arg1->x1 == 0 && (HSD_PadCopyStatus[(u8) Player_GetPlayerId(arg0)].button & HSD_PAD_A) && (Player_GetPlayerCharacter(arg0) == CKIND_ZELDA || Player_GetPlayerCharacter(arg0) == CKIND_SEAK)) {
        if (Player_GetPlayerCharacter(arg0) == CKIND_ZELDA) {
            Player_SetPlayerCharacter(arg0, CKIND_SEAK);
        } else {
            Player_SetPlayerCharacter(arg0, CKIND_ZELDA);
        }
        lbl_8046B6A0.unk_38[arg0].x4_b4 = 1;
    }

    lbl_8046B6A0.unk_38[arg0].x3 = arg1->x5;

    Player_SetHandicap(arg0, (s8) arg1->x8);
    Player_SetTeam(arg0, (s8) arg1->x9);
    Player_SetFlagsBit0(arg0, arg1->xC_b0);
    Player_SetNametagSlotID(arg0, arg1->xA);
    if (arg1->xC_b1) {
        lbl_8046B6A0.unk_A += 5;
        Player_SetFlagsBit3(arg0, 1);
        Player_SetUnk4C(arg0, lbl_8046B6A0.unk_A);
    }
    Player_SetPlayerAndEntityCpuType(arg0, arg1->xE);
    Player_SetPlayerAndEntityCpuLevel(arg0, arg1->xF);
    if (arg1->x10 != 0) {
        Player_SetHUDDamage(arg0, arg1->x10);
    } else {
        Player_SetHUDDamage(arg0, arg1->x12);
    }

    lbl_8046B6A0.unk_38[arg0].x6 = arg1->x12;

    if (arg1->xC_b7) {
        Player_SetMoreFlagsBit2(arg0, 1);
    } else {
        Player_SetMoreFlagsBit2(arg0, 0);
    }
    Player_SetOtherStamina(arg0, arg1->x14);
    Player_SetModelScale(arg0, arg1->x20);
    Player_SetAttackRatio(arg0, arg1->x18);
    Player_SetDefenseRatio(arg0, arg1->x1C);
    if (arg1->xC_b6) {
        Player_SetMoreFlagsBit1(arg0, 1);
    } else {
        Player_SetMoreFlagsBit1(arg0, 0);
    }

    lbl_8046B6A0.unk_38[arg0].x4_b1 = arg1->xC_b3;
    lbl_8046B6A0.unk_38[arg0].x4_b0 = arg1->xC_b2;
    if (arg1->xC_b2) {
        Player_SetFlagsBit5(arg0, 1);
    } else {
        Player_SetFlagsBit5(arg0, 0);
    }
    lbl_8046B6A0.unk_38[arg0].x4_b2 = arg1->xC_b4;
    if (arg1->xC_b4) {
        Player_SetFlagsBit6(arg0, 1);
        Player_SetFlagsBit7(arg0, 0);
    } else {
        Player_SetFlagsBit6(arg0, 0);
        Player_SetFlagsBit7(arg0, 0);
    }
    if (arg1->xC_b5) {
        Player_SetFlagsAEBit0(arg0, 1);
    } else {
        Player_SetFlagsAEBit0(arg0, 0);
    }
    if (!arg1->xD_b2) {
        Player_SetMoreFlagsBit3(arg0, 1);
    } else {
        Player_SetMoreFlagsBit3(arg0, 0);
    }
    Player_SetMoreFlagsBit4(arg0, arg1->xD_b3);
    if (arg1->xD_b4) {
        Player_SetMoreFlagsBit5(arg0, 1);
    } else {
        Player_SetMoreFlagsBit5(arg0, 0);
    }
    lbl_8046B6A0.unk_38[arg0].x4_b3 = arg1->xD_b1;
    Player_SetMoreFlagsBit6(arg0, arg1->xB);
    Player_SetFacingDirection(arg0, arg1->x6);
    lbl_8046B6A0.unk_38[arg0].x4_b5 = arg1->xD_b0;
}

static struct {
    u32 x0, x4, x8, xC;
} lbl_803D5620 = { 0 };
static struct {
    u32 x0, x4, x8, xC, x10, x14;
} lbl_803D5630 = { 0 };

void fn_8016DCC0(StartMeleeData* arg0)
{
    int i;

    memzero(&lbl_8046B6A0, 0x24C8);
    lbl_8046B6A0.unk_D = 6;
    lbl_8046B6A0.unk_1C = &lbl_803D5630;
    lbl_8046B6A0.unk_20 = &lbl_803D5620;
    lbl_8046B6A0.unk_0 = 0;

    lbl_8046B6A0.x24C8 = arg0->rules;

    lbl_8046B6A0.unk_251 = arg0->rules.x0_0;
    lbl_8046B6A0.unk_252 = arg0->rules.x8;
    if (arg0->rules.x7 != 0) {
        lbl_8046B6A0.unk_B = arg0->rules.x7;
    }
    lbl_8046B6A0.unk_258 = arg0->rules.xC;
    Camera_80030E34(arg0->rules.x2C);

    if (lbl_8046B6A0.x24C8.x0_6) {
        if (lbl_8046B6A0.x24C8.x0_7) {
            if (arg0->rules.x14 != 0) {
                lbl_8046B6A0.unk_2C = arg0->rules.x14 - 1;
            } else {
                lbl_8046B6A0.unk_2C = 0;
            }
            lbl_8046B6A0.x24C8.x10 = -1;
            lbl_8046B6A0.unk_28 = arg0->rules.x10;
        } else {
            if (arg0->rules.x10 == 0) {
                lbl_8046B6A0.unk_28 = -1;
            } else {
                lbl_8046B6A0.unk_28 = arg0->rules.x10;
            }
            if (arg0->rules.x14 != 0) {
                lbl_8046B6A0.unk_2C = arg0->rules.x14 - 1;
            } else {
                lbl_8046B6A0.unk_2C = 0x3B;
            }
        }
    } else if (lbl_8046B6A0.x24C8.x1_0) {
        lbl_8046B6A0.unk_28 = arg0->rules.x10;
        if (arg0->rules.x14 != 0) {
            lbl_8046B6A0.unk_2C = arg0->rules.x14;
        } else {
            lbl_8046B6A0.unk_2C = 0;
        }
    }
    if (arg0->rules.x54 != NULL) {
        lbl_8046B6A0.unk_7 = 1;
    } else {
        lbl_8046B6A0.unk_7 = 0;
    }
    Player_InitAllPlayers();

    switch (lbl_8046B6A0.unk_7) {
    case 0:
    case 2:
    case 3:
        for (i = 0; i < 6; i++) {
            fn_8016D8AC(i, &arg0->players[i]);
        }
        break;
    case 1:
        fn_8016D8AC(0, &arg0->players[0]);
        for (i = 1; i < 6; i++) {
            Player_SetSlottype(i, 3);
        }
        if (arg0->rules.x54->x10_b1) {
            fn_8016A09C();
        }
    }
}

/// #fn_8016DEEC

/// #fn_8016E124

/// #fn_8016E2BC

/// #fn_8016E5C0

void fn_8016E730(StartMeleeData* arg0)
{
    HSD_GObj* temp_r30;
    f32 var_f0;
    s32 temp_r3;
    lbl_8046B6A0_t* r30;

    db_Setup();
    gm_801A4B08(fn_8016BAF4, fn_8016BBB4);
    gm_801A4B40(db_RunEveryFrame);
    gm_801A4B50(1);
    lb_80019880((0.016666667f / arg0->rules.x34) * OS_TIMER_CLOCK);
    Camera_80028B9C(0x46);
    Camera_80030688();
    fn_8016DCC0(arg0);
    lbRefract_800222A4();
    lb_8000FCDC();
    efLib_8005B4B8();
    efAsync_8006737C(0);
    efAsync_8006737C(0x1F);
    Player_80036DD8();
    ftCo_800C06C0();
    mpColl_80041C78();
    Ground_801C0378(0x40);
    Stage_802251E8((enum InternalStageId) arg0->rules.xE, NULL);

    r30 = &lbl_8046B6A0;
    if (gm_8016B41C() != 0) {
        var_f0 = 1.0f;
    } else {
        temp_r3 = gm_8016B558();
        switch (temp_r3) {                          /* irregular */
        case 2:
            var_f0 = 1.0f;
            break;
        case 3:
            var_f0 = 1.1f;
            break;
        case 4:
            var_f0 = 1.2f;
            break;
        default:
            var_f0 = 1.0f;
            break;
        }
    }
    r30->unk_34 = var_f0;
    Item_80266F70();
    Item_80266FCC();
    it_8026D018();
    lbAudioAx_8002785C();
    Stage_8022524C();
    Camera_80030730(Ground_801C20D0());
    fn_8016E2BC();
    Stage_80225298();
    Ground_801C5800();
    Camera_8002F3AC();
    fn_801A1134();
    un_80321900();
    if (lbl_8046B6A0.x24C8.x38 != NULL) {
        lbl_8046B6A0.x24C8.x38(0);
        Camera_8002F3AC();
    }
    ifAll_802F390C();
    lbBgFlash_80021A18(0xFF);
    if (arg0->rules.x44 != NULL) {
        arg0->rules.x44();
    }
    temp_r30 = gm_801A4BC8();
    fn_80171AD4();
    if (temp_r30 != NULL) {
        HSD_GObjProc_8038FD54(temp_r30, fn_8016C7D0, 0x14);
    }
    if (!arg0->rules.x1_4) {
        Stage_80225074(fn_8016E5C0(arg0));
    }
}

void gm_8016E934_OnEnter(void* arg0)
{
    StartMeleeData* tmp = arg0;
    fn_8016E730(tmp);
    if (tmp->rules.x1_2) {
        ifStatus_802F6EA4(8, -1, -1, 0, fn_8016B7B4, fn_8016B7F8);
    } else {
        ifStatus_802F6EA4(3, -1, -1, 0, fn_8016B7B4, fn_8016B7F8);
    }
    ifTime_802F446C();
    ifStatus_802F665C(tmp->rules.x0_3);
}

/// #gm_8016E9C8

void gm_8016EBC0_OnEnter(void* arg0)
{
    StartMeleeData* tmp = arg0;
    tmp->rules.x6 = true;
    fn_8016E730(tmp);
    ifStatus_802F6EA4(1, -1, -1, 0, fn_8016B7B4, fn_8016B7F8);
    ifTime_802F446C();
    ifStatus_802F665C(tmp->rules.x0_3);
}

void gm_8016EC28_OnEnter(void* arg0)
{
    StartMeleeData* tmp = arg0;
    struct lbl_8046B6A0_t* tmp2;

    fn_8016E730(tmp);
    Ground_801C1154();
    grStadium_801D410C();
    un_802FD404();
    tmp2 = &lbl_8046B6A0;
    ftLib_800868A4();
    Stage_802252E4((InternalStageId) tmp2->x24C8.xE, NULL);
    grStadium_801D4040();
    if (!lbl_8046B6A0.x24C8.x1_3) {
        ifStatus_802F6EA4(4, -1, -1, 0, 0, fn_8016B784);
    } else {
        ifStatus_802F6EA4(8, -1, -1, 0, 0, fn_8016B784);
    }
    un_802FD428();
    ifStatus_802F665C(tmp->rules.x0_3);
    fn_8018A000();
}

/// #gm_8016EC28_OnEnter

/// #gm_8016ECE8

/// #gm_8016EDDC

/// #fn_8016EF98

/// #gm_8016F00C

/// #fn_8016F030

/// #gm_8016F088

/// #gm_8016F120

/// #fn_8016F140

/// #fn_8016F160

/// #fn_8016F180

/// #gmDecisionGetType

short fn_8016F1F0(int idx)
{
    return lbl_803D5A4C[idx].x0;
}

/// #gm_8016F208

/// #fn_8016F280

/// #gm_8016F2F8

/// #fn_8016F344

/// #fn_8016F39C

/// #fn_8016F548

/// #fn_8016F740

/// #fn_8016F870

/// #fn_8016F9A8

static u8 lbl_8046DBC8[0xe];
void fn_80171AD4(void)
{
    memzero(&lbl_8046DBC8, 0xE);
}

/// #fn_8016FFD4

/// #fn_80170110

void gm_801701A0(void)
{
    lbl_804D65A0 = 1;
}

void fn_801701AC(void)
{
    lbl_804D65A0 = 0;
}

u8 fn_801701B8(void)
{
    return lbl_804D65A0;
}

/// #fn_801701C0

/// #fn_80171A88

/// #fn_80171AD4

/// #fn_80171B00

/// #fn_80171B2C

/// #fn_80171B64

/// #fn_80171BA4

/// #fn_80171DC4

/// #gm_801720B4

/// #gm_801720F8

/// #gm_80172140

/// #gm_80172174

/// #gm_8017219C

/// #gm_801721EC

/// #fn_801722BC

/// #fn_801722F4

/// #fn_8017232C

/// #fn_80172380

/// #fn_801723D4

/// #fn_80172428

/// #fn_80172478

bool fn_801724C8(void)
{
    return false;
}

/// #fn_801724D0

/// #fn_80172504

/// #fn_80172538

/// #fn_8017256C

/// #fn_801725A8

/// #fn_801725E4

/// #fn_80172624

/// #fn_80172664

/// #fn_80172698

/// #fn_801726CC

/// #fn_80172700

/// #fn_80172734

/// #fn_80172768

/// #fn_8017279C

/// #fn_8017280C

/// #gm_80172898

/// #gm_8017297C

/// #gm_801729EC

/// #gm_80172BC4

/// #gm_80172C04

/// #gm_80172C44

/// #fn_80172C78

/// #gm_80172CC0

/// #gm_80172D78

/// #gm_80172DD4

/// #gm_80172E74

/// #gm_80172F00

/// #fn_80172FAC

/// #fn_80173098

/// #gm_80173224

/// #gm_801732D8

/// #gm_8017335C

/// #gm_801733D8

/// #gm_8017341C

/// #gm_80173460

/// #gm_80173498

/// #gm_801734D0

/// #fn_80173510

/// #fn_801735F0

/// #fn_80173644

/// #fn_8017367C

UNK_T gm_801736DC(void)
{
    return &lbl_8046DBD8;
}

/// #gm_801736E8

/// #gm_80173754

u8 gm_801737D8(void)
{
    return M2C_FIELD(&lbl_8046DBD8, u8*, 6);
}

/// #gm_801737E8_OnLoad

/// #fn_80173834

/// #gm_8017390C

/// #gm_80173AA4

/// #gm_80173B30

/// #gm_80173BC4

/// #gm_80173C70

/// #gm_80173D3C

/// #gm_80173DE4

/// #gm_80173EEC

/// #gm_80174180

/// #gm_801741FC

/// #gm_80174238
