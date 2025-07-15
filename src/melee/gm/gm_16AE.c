#include "gm_1601.h"

#include "gm_16AE.static.h"

#include "gmmain_lib.h"

#include <melee/cm/camera.h>
#include <melee/db/db.h>
#include <melee/ef/efasync.h>
#include <melee/ef/eflib.h>
#include <melee/ft/ftdevice.h>
#include <melee/ft/ftlib.h>
#include <melee/gm/gm_1A36.h>
#include <melee/gm/gm_1A3F.h>
#include <melee/gm/gm_1A45.h>
#include <melee/gm/gm_1B03.h>
#include <melee/gm/gmpause.h>
#include <melee/gr/ground.h>
#include <melee/gr/grstadium.h>
#include <melee/gr/stage.h>
#include <melee/if/ifall.h>
#include <melee/if/ifstatus.h>
#include <melee/if/ifstock.h>
#include <melee/if/iftime.h>
#include <melee/it/it_266F.h>
#include <melee/it/item.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lb_0192.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbbgflash.h>
#include <melee/lb/lblanguage.h>
#include <melee/lb/lbrefract.h>
#include <melee/lb/lbtime.h>
#include <melee/mn/types.h>
#include <melee/mp/mpcoll.h>
#include <melee/pl/player.h>
#include <melee/pl/plbonus.h>
#include <melee/pl/plbonuslib.h>
#include <melee/un/un_2FC9.h>
#include <melee/vi/vi1202.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/gobjproc.h>

#include <m2c_macros.h>
#include <math.h>

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

UNK_T fn_8016AE60(void)
{
    return fn_80169364();
}

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

u16 gm_8016AF0C(void)
{
    int tmp = 99.0F * lbl_8046B6A0.unk_2C / 59.0F;
    u16 var_r31 = tmp;
    if (!gm_8016B110()) {
        var_r31 = 0x63 - var_r31;
    }
    return var_r31;
}

bool GetMatchTimer(int* arg0)
{
    if (arg0 != NULL && lbl_8046B6A0.x24C8.x0_6) {
        if (gm_8016B110()) {
            *arg0 = lbl_8046B6A0.x24C8.x10 - lbl_8046B6A0.unk_28;
        } else {
            *arg0 = lbl_8046B6A0.unk_28;
        }
        return true;
    }
    return false;
}

u16 gm_8016B004(void)
{
    return lbl_8046B6A0.x24C8.xE;
}

bool gm_8016B014(void)
{
    int i;
    PAD_STACK(4);

    if (lbl_8046B6A0.x24C8.x4_2 && gm_8016A1F8() == 0) {
        for (i = 1; i < 6; i++) {
            if (Player_GetPlayerState(i) != 0) {
                i = -1;
                break;
            }
        }
        if (i > 0) {
            return true;
        }
    }
    return false;
}

bool gm_8016B094(void)
{
    return lbl_8046B6A0.x24C8.x0_0 == 1;
}

bool gm_8016B0B4(void)
{
    return lbl_8046B6A0.x24C8.x0_0 == 2;
}

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

bool gm_8016B14C(void)
{
    return lbl_8046B6A0.x24C8.x8 == 0;
}

bool gm_8016B168(void)
{
    return lbl_8046B6A0.x24C8.x8 == 1;
}

bool gm_8016B184(void)
{
    if (lbl_8046B6A0.unk_7 == 1) {
        return true;
    }
    return false;
}

bool gm_8016B1A8(void)
{
    return lbl_8046B6A0.x24C8.x9 == 1;
}

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

bool gm_8016B204(void)
{
    StartMeleeRules* rules = &lbl_8046B6A0.x24C8;
    if (rules->x10 == 0 || !rules->x0_6) {
        return true;
    }
    return false;
}

bool gm_8016B238(void)
{
    return lbl_8046B6A0.x24C8.x6;
}

f32 gm_8016B248(void)
{
    return lbl_8046B6A0.x24C8.x30;
}

bool gm_8016B258(int arg0)
{
    return lbl_8046B6A0.unk_38[arg0].x4_b3;
}

void gm_SetGameSpeed(float speed)
{
    lb_80019880(1 / 60.0F / speed * OS_TIMER_CLOCK);
}

void gm_ResetGameSpeed(void)
{
    lb_80019880(1 / 60.0F / lbl_8046B6A0.x24C8.x34 * OS_TIMER_CLOCK);
}

void gm_8016B328(void)
{
    lbl_8046B6A0.unk_6 = 1;
}

void gm_8016B33C(int arg0)
{
    lbl_8046B6A0.unk_B = arg0 + 1;
}

void gm_8016B350(int arg0)
{
    lbl_8046B6A0.unk_10 = arg0 + 1;
}

void gm_8016B364(int arg0)
{
    lbl_8046B6A0.unk_14 = arg0 + 1;
}

void gm_8016B378(s8 arg0)
{
    lbl_8046B6A0.unk_18 = arg0;
}

void fn_8016B388(int arg0, s16 arg1)
{
    lbl_8046B6A0.unk_38[arg0].x6 = arg1;
}

bool gm_8016B3A0(void)
{
    if (gm_801A4310() == 0x10) {
        return true;
    }
    return false;
}

bool gm_8016B3D8(void)
{
    switch (gm_801A4310()) {
    case 3:
    case 4:
    case 5:
        return true;
    default:
        return false;
    }
}

bool gm_8016B41C(void)
{
    switch (gm_801A4310()) {
    case 3:
    case 4:
    case 5:
    case 0xF:
    case 0x1C:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x2B:
        return true;
    default:
        return false;
    }
}

static inline bool gm_8016B41C_dontinline(void)
{
    return gm_8016B41C();
}

bool gm_8016B498(void)
{
    return gm_801A4340(gm_801A4310());
}

bool fn_8016B4BC(void)
{
    u8 _[4];
    s32 spC;
    s32 sp8;

    if (gm_8016B1A8()) {
        Ground_801C1DE4(&sp8, &spC);
        if (sp8 == 0) {
            return true;
        }
    }
    return false;
}

bool fn_8016B510(void)
{
    if (lbl_8046B6A0.x24C8.x9 == 2 && Ground_801C1D98()) {
        return true;
    }
    return false;
}

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

float fn_8016B5B0(void)
{
    lbl_8046B6A0_t* tmp = &lbl_8046B6A0;
    int count;
    int i;
    PAD_STACK(4);

    if (gm_8016B41C()) {
        float var_f1 = 3.0F;
        if (lbl_8046B6A0.unk_0 != 0) {
            if (tmp->unk_8 == 1 || tmp->unk_8 == 4) {
                var_f1 *= 1.1F;
            }
        }
        return var_f1;
    }

    count = 0;
    for (i = 0; i < 6; i++) {
        if (Player_GetPlayerSlotType(i) != 3) {
            count++;
        }
    }

    switch (count) {
    case 2:
        return 0.9F;
    case 3:
        return 0.8F;
    case 4:
        return 0.7F;
    default:
        return 0.0F;
    }
}

void gm_8016B6E8(int arg0, int arg1)
{
    lbl_8046B6A0_t* tmp = &lbl_8046B6A0;
    if (arg0 == 0) {
        tmp->unk_2E = lbTime_8000AF24(tmp->unk_2E, arg1);
    }
}

u8 fn_8016B728(void)
{
    return lbl_8046B6A0.unk_C;
}

void fn_8016B738(int arg0)
{
    lbl_8046B6A0_t* tmp = &lbl_8046B6A0;
    tmp->unk_C = lbTime_8000AF74(tmp->unk_C, arg0);
}

struct lbl_8046B6A0_24C_t* gm_8016B774(void)
{
    return &lbl_8046B6A0.x24C;
}

void fn_8016B784(void)
{
    lbl_8046B6A0.unk_5 = 1;
    grStadium_801D4150();
}

void fn_8016B7B4(int arg0)
{
    Ground_801C1154();
    if (arg0 == 3) {
        grStadium_801D4084();
    } else {
        grStadium_801D410C();
    }
    un_802FD404();
}

void fn_8016B7F8(void)
{
    lbl_8046B6A0_t* tmp = &lbl_8046B6A0;
    PAD_STACK(4);

    ftLib_800868A4();
    Stage_802252E4((InternalStageId) tmp->x24C8.xE, NULL);
    grStadium_801D4040();
    if (!tmp->x24C8.x1_3) {
        ifStatus_802F6EA4(4, -1, -1, 0, NULL, fn_8016B784);
    } else {
        ifStatus_802F6EA4(8, -1, -1, 0, NULL, fn_8016B784);
    }
    un_802FD428();
}

void fn_8016B88C(int arg0)
{
    Ground_801C1158();
    if (arg0 == 0) {
        grStadium_801D40C8();
    }
    lbl_8046B6A0.unk_5 = 0;
}

void gm_8016B8D4(s32 arg0, s32 arg1)
{
    u8 tmp = arg1;
    lbl_8046B6A0.unk_38[arg0].x1 = 0x82;
    lbl_8046B6A0.unk_38[arg0].x2 = tmp;
    grStadium_801D3B4C(arg0, tmp);
}

static inline int fn_8016B918_inline(int var_r31)
{
    int team = Player_GetTeam(var_r31);
    int i;
    for (i = 0; i < 6; i++) {
        if (Player_GetPlayerSlotType(i) != 3 &&
            var_r31 != i &&
            team == Player_GetTeam(i) &&
            Player_GetStocks(i) > 1) {
            return i;
        }
    }
    return 6;
}

void fn_8016B918(void)
{
    HSD_PadStatus* temp_r3_3;
    int temp_r30;
    int temp_r3_2;
    bool var_r0;
    bool var_r0_2;
    int var_r28;
    int var_r31;
    int i;
    StartMeleeRules* temp_r3;
    PAD_STACK(0x10);

    temp_r3 = &lbl_8046B6A0.x24C8;
    if (!temp_r3->x4_1) {
        return;
    }
    if (temp_r3->x8 != 1) {
        return;
    }

    for (i = 0; i < 6; i++) {
        if (Player_GetPlayerSlotType(i) != 3 &&
            Player_GetEntity(i) != NULL &&
            Player_8003219C(i) != 0 &&
            Player_GetStocks(i) == 0) {
            var_r0 = true;
        } else {
            var_r0 = false;
        }
        if (!var_r0) {
            continue;
        }
        temp_r3_2 = Player_GetPlayerId(i);
        if (g_debugLevel >= 3) {
            temp_r3_3 = &HSD_PadCopyStatus[(u8) temp_r3_2];
            if ((temp_r3_3->trigger & 8) && (temp_r3_3->button & HSD_PAD_X)) {
                var_r0_2 = true;
            } else {
                var_r0_2 = false;
            }
        } else {
            var_r0_2 = HSD_PadCopyStatus[(u8) temp_r3_2].trigger & HSD_PAD_START;
        }
        if (var_r0_2 != 0) {
            var_r28 = fn_8016B918_inline(i);
            if (var_r28 != 6 && ifStock_802F7EFC(i, var_r28) == 0) {
                Player_LoseStock(var_r28);
                Player_SetStocks(i, Player_GetStocks(i) + 1);
                gm_8016C658(i);
                fn_8016719C(i, 0);
            }
        }
    }
}

bool fn_8016BAF4(void)
{
    int i;
    for (i = 0; i < 4; i++) {
        HSD_PadStatus* pad = &HSD_PadMasterStatus[(u8) i];
        if (pad->err == 0 && (pad->trigger & 0x1000)) {
            return true;
        }
    }
    return false;
}

bool fn_8016BBB4(void)
{
    int i;
    for (i = 0; i < 4; i++) {
        HSD_PadStatus* pad = &HSD_PadMasterStatus[(u8) i];
        if (pad->err == 0 && (pad->trigger & 0x10)) {
            return true;
        }
    }
    return false;
}

int fn_8016BC74(void)
{
    HSD_PadStatus* temp_r3_3;
    HSD_PadStatus* temp_r4;
    bool var_r0_2;
    bool var_r0_3;
    int var_r30;
    int var_r29;
    int temp_r3;
    PAD_STACK(0x18);

    if (gm_8016B41C() || gm_801A4310() == 0x14 ||
        (gm_801A4310() == 2 && gm_801A42C4() == 0x81)) {
        temp_r3 = Player_GetPlayerId(0);
        temp_r4 = &HSD_PadCopyStatus[(u8) temp_r3];
        if (temp_r4->err == 0) {
            if (g_debugLevel >= 3) {
                if ((temp_r4->trigger & 8) &&
                    (temp_r4->button & HSD_PAD_X)) {
                    var_r0_2 = 1;
                } else {
                    var_r0_2 = 0;
                }
            } else {
                var_r0_2 = temp_r4->trigger & 0x1000;
            }
            if (var_r0_2 != 0) {
                return temp_r3;
            }
        }
    } else {
        for (var_r30 = 0; var_r30 < 4; var_r30++) {
            temp_r3_3 = &HSD_PadCopyStatus[(u8) var_r30];
            if (temp_r3_3->err == 0) {
                if (g_debugLevel >= 3) {
                    if ((temp_r3_3->trigger & 8) &&
                        (temp_r3_3->button & HSD_PAD_X)) {
                        var_r0_3 = 1;
                    } else {
                        var_r0_3 = 0;
                    }
                } else {
                    var_r0_3 = temp_r3_3->trigger & 0x1000;
                }
                if (var_r0_3) {
                    for (var_r29 = 0; var_r29 < 6; var_r29++) {
                        if (Player_GetPlayerSlotType(var_r29) != 3 &&
                            Player_GetEntity(var_r29) != NULL &&
                            Player_8003219C(var_r29) == 0 &&
                            var_r30 == Player_GetPlayerId(var_r29)) {
                            return var_r30;
                        }
                    }
                }
            }
        }
    }
    return -1;
}

int gm_8016BE80(void)
{
    HSD_PadStatus* temp_r3;
    bool var_r0;
    int var_r30;
    int var_r29;
    PAD_STACK(0x10);

    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        temp_r3 = &HSD_PadCopyStatus[(u8) var_r30];
        if (temp_r3->err == 0) {
            if (g_debugLevel >= 3) {
                if ((temp_r3->trigger & 8) &&
                    (temp_r3->button & HSD_PAD_X)) {
                    var_r0 = 1;
                } else {
                    var_r0 = 0;
                }
            } else {
                var_r0 = temp_r3->trigger & 0x1000;
            }
            if (var_r0 != 0) {
                if (var_r30 == 3) {
                    return var_r30;
                }
                for (var_r29 = 0; var_r29 < 6; var_r29++) {
                    if (var_r30 == Player_GetPlayerId(var_r29) &&
                        Player_GetPlayerSlotType(var_r29) != 3) {
                        return var_r30;
                    }
                }
            }
        }
    }
    return -1;
}

int fn_8016BF74(void)
{
    bool var_r0;
    int var_r0_2;
    bool var_r0_3;
    lbl_8046B6A0_t* tmp = &lbl_8046B6A0;
    PAD_STACK(0x8);

    if (lbl_8046B6A0.x24C8.x4_2 && Player_GetP1Stock() == 0) {
        return 4;
    }
    if (lbl_8046B6A0.unk_7 == 1) {
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (var_r0 && fn_8016A1E4() != 0 && fn_801693A8() == 0) {
        var_r0_2 = 5;
    } else {
        var_r0_2 = 0;
    }
    if (var_r0_2 != 0) {
        return 5;
    }
    if (lbl_8046B6A0.unk_7 == 0) {
        var_r0_3 = 1;
    } else {
        var_r0_3 = 0;
    }
    if (var_r0_3 != 0 && !lbl_8046B6A0.x24C8.x5_1 &&
        (lbl_8046B6A0.x24C8.x0_0 == 1 || tmp->x24C8.x4_2)) {

        int i;
        int var_r31 = 0;
        int var_r29 = 0;
        for (i = 0; i < 6; i++) {
            if (Player_GetPlayerSlotType(i) != 3) {
                if (Player_GetStocks(i) == 0) {
                    var_r31 += 1;
                }
                var_r29 += 1;
            }
        }

        if (var_r31 >= var_r29 - 1) {
            return 2;
        }
    }
    return 0;
}

int fn_8016C0C8(void)
{
    int i;
    bool var_r0;
    int var_r0_2;
    bool var_r0_3;
    bool var_r0_4;
    int var_r29;
    int var_r29_2;
    int var_r28;
    int var_r28_2;
    int var_r27;
    int var_r27_2;

    s16 sp14[5];
    PAD_STACK(0xC);

    if (lbl_8046B6A0.x24C8.x4_2) {
        var_r28 = 0;
        var_r27 = 0;
        if (Player_GetP1Stock() == 0) {
            return 4;
        }
        if (lbl_8046B6A0.unk_7 == 1) {
            var_r0 = true;
        } else {
            var_r0 = false;
        }
        if (var_r0 && fn_8016A1E4() != 0 && fn_801693A8() == 0) {
            var_r0_2 = 5;
        } else {
            var_r0_2 = 0;
        }
        if (var_r0_2 != 0) {
            return 5;
        }
        if (lbl_8046B6A0.unk_7 == 0) {
            var_r0_3 = true;
        } else {
            var_r0_3 = false;
        }
        if (var_r0_3 && !lbl_8046B6A0.x24C8.x5_1) {
            for (var_r29 = 0; var_r29 < 6; var_r29++) {
                if (Player_GetFlagsBit1(var_r29) == 0 &&
                    Player_GetPlayerSlotType(var_r29) != 3 &&
                    Player_GetEntity(var_r29) != NULL) {
                    if (Player_GetTeam(var_r29) != Player_GetTeam(0)) {
                        var_r28 += Player_GetStocks(var_r29);
                        var_r27 += 1;
                    }
                }
            }
            if (var_r27 != 0 && var_r28 == 0) {
                return 3;
            }
        }
    }
    if (lbl_8046B6A0.unk_7 == 0) {
        var_r0_4 = true;
    } else {
        var_r0_4 = false;
    }
    if (var_r0_4 && lbl_8046B6A0.x24C8.x0_0 == 1) {
        var_r28_2 = 0;
        var_r29_2 = 0;
        memset(sp14, -1, sizeof(sp14));

        for (var_r27_2 = 0; var_r27_2 < 6; var_r27_2++) {
            if (Player_GetPlayerSlotType(var_r27_2) != 3) {
                if (sp14[Player_GetTeam(var_r27_2)] == -1) {
                    sp14[Player_GetTeam(var_r27_2)] = Player_GetStocks(var_r27_2);
                    var_r28_2++;
                } else {
                    sp14[Player_GetTeam(var_r27_2)] += Player_GetStocks(var_r27_2);
                }
            }
        }

        for (i = 0; i < 5; i++) {
            if (sp14[i] == 0) {
                var_r29_2++;
            }
        }
        if (var_r29_2 >= var_r28_2 - 1) {
            return 3;
        }
    }
    return 0;
}

int fn_8016C35C(void)
{
    int temp_r3;
    int temp_r3_2;
    lbl_8046B6A0_t* tmp = &lbl_8046B6A0;
    PAD_STACK(0x8);

    if (lbl_8046B6A0.unk_8 != 0) {
        return lbl_8046B6A0.unk_8;
    }
    if (lbl_8046B6A0.unk_6 == 1) {
        return 9;
    }
    if (lbl_8046B6A0.x24C8.x5_0) {
        return 0;
    }
    if (tmp->x24C8.x0_6) {
        if (tmp->x24C8.x0_7) {
            if (lbl_8046B6A0.unk_28 == lbl_8046B6A0.x24C8.x10 &&
                lbl_8046B6A0.unk_2C == 0) {
                return 1;
            }
        } else {
            if (lbl_8046B6A0.unk_28 == 0 &&
                lbl_8046B6A0.unk_2C == 0x3B) {
                return 1;
            }
        }
    }
    if (lbl_8046B6A0.x24C8.x8 == 0) {
        temp_r3_2 = fn_8016BF74();
        if (temp_r3_2 != 0) {
            return temp_r3_2;
        }
    }
    if (lbl_8046B6A0.x24C8.x8 == 1) {
        temp_r3 = fn_8016C0C8();
        if (temp_r3 != 0) {
            return temp_r3;
        }
    }
    if (Ground_801C1D84() != 0) {
        return 6;
    }
    return 0;
}

void fn_8016C46C(int arg0)
{
    if (lbl_8046B6A0.unk_9 != 0) {
        switch (gm_801A4310()) {
        case 3:
            fn_8017EE40(arg0);
            return;
        case 4:
            fn_8017E8A4(arg0);
            return;
        case 5:
            fn_8018A364(arg0);
            break;
        }
    }
}

static inline void fn_8016C46C_dontinline(int arg0)
{
    fn_8016C46C(arg0);
}

void fn_8016C4F4(struct lbl_8046B6A0_24C_t* arg0)
{
    struct lbl_8046B6A0_24C_44C_t* x44C = arg0->x44C;
    int i;
    int j;

    for (i = 0; i < 6; i++) {
        if (arg0->x58[i].x0 != 3) {
            pl_80039450(i);
            for (j = 0; j < 0x101; j++) {
                x44C[i].x0[j] = fn_80170110(arg0, j, 2, i);
                if (x44C[i].x0[j] != 0) {
                    x44C[i].x104[j] = fn_8016FAD4(arg0, fn_8016F1F0(j), 2, i);
                } else {
                    x44C[i].x104[j] = 0;
                }
            }
        }
    }
}

int gm_8016C5C0(int pl_slot)
{
    struct lbl_8046B6A0_24C_t* tmp = gm_8016B774();
    PAD_STACK(8);

    if (tmp->x0 != (UNK_T) gm_801A4BA8()) {
        tmp->x0 = (UNK_T) gm_801A4BA8();
        gm_80166378(tmp);
    }
    if (lbl_8046B6A0.x24C8.x8 == 0) {
        return tmp->x58[pl_slot].x5;
    }
    return tmp->x24[tmp->x58[pl_slot].x7].x0;
}

int gm_8016C658(int arg0)
{
    struct lbl_8046B6A0_24C_t* temp_r31;
    PAD_STACK(8);

    temp_r31 = &lbl_8046B6A0.x24C;
    if (lbl_8046B6A0.x24C.x0 != (UNK_T) gm_801A4BA8()) {
        lbl_8046B6A0.x24C.x0 = (UNK_T) gm_801A4BA8();
        gm_80166378(&lbl_8046B6A0.x24C);
    }
    return temp_r31->x58[arg0].x2C;
}

s32 gm_8016C6C0(HSD_GObj* arg0)
{
    PAD_STACK(0x10);
    return gm_8016C5C0(ftLib_80086BE0(arg0));
}

int gm_8016C75C(HSD_GObj* arg0)
{
    struct lbl_8046B6A0_24C_t* tmp;
    PAD_STACK(8);

    tmp = &lbl_8046B6A0.x24C;
    if (tmp->x0 != (UNK_T) gm_801A4BA8()) {
        tmp->x0 = (UNK_T) gm_801A4BA8();
        gm_80166378(tmp);
    }
    return tmp->x58[ftLib_80086BE0(arg0)].x20;
}

void fn_8016C7D0(HSD_GObj* gobj)
{
    fn_80171DC4(gobj);
}

void fn_8016C7F0(void)
{
    s32 sp24;
    s32 sp20;
    u8 _[0x18];

    s32* temp_r30_2;
    int var_r29;
    u8 var_r29_2;
    int var_r28;
    u8* temp_r29_2;
    u8* temp_r30;

    if (lbl_8046B6A0.x24C8.x50 != NULL) {
        lbl_8046B6A0.x24C8.x50(lbl_8046B6A0.unk_8);
    }
    HSD_PadRumbleRemoveAll();
    for (var_r29 = 0; var_r29 < 4; var_r29++) {
        HSD_PadRumbleOn(var_r29);
    }
    if (!lbl_8046B6A0.x24C8.x1_5) {
        lbAudioAx_800236DC();
    }
    lbAudioAx_80023694();
    lbAudioAx_80024C84();
    ifTime_802F4248();
    if (lbl_8046B6A0.unk_8 == 4 && lbl_8046B6A0.x24C8.x4_3) {
        gm_80167858(Player_GetPlayerId(0), Player_GetNametagSlotID(0), 0xD, 0);
        Camera_80030E44(4, NULL);
    }
    if (gm_801A4310() == 0xF || (gm_801A4310() == 3 && lbl_8046B6A0.x24C8.xE >= 0x21 && lbl_8046B6A0.x24C8.xE <= 0x3A)) {
        temp_r29_2 = (u8*) gm_801B6320();
        temp_r30 = gm_8017EB30();
        var_r28 = 0;
        if (gm_801A4310() == 0xF) {
            var_r29_2 = gm_80164024(*temp_r29_2);
        } else {
            var_r29_2 = gm_80164024(*temp_r30);
        }
        temp_r30_2 = gmMainLib_8015D438(var_r29_2);
        gmMainLib_8015D450(var_r29_2);
        Ground_801C1DE4(&sp24, &sp20);
        if (gmMainLib_8015D48C(var_r29_2) == 0) {
            if (sp24 == 0) {
                var_r28 = 1;
            }
        } else if (sp24 == 0 && *temp_r30_2 > lbl_8046B6A0.unk_24) {
            var_r28 = 1;
        }
        if (var_r28 != 0) {
            lbl_8046B6A0.unk_10 = 0x9C41;
            lbl_8046B6A0.unk_14 = 0x145;
            gm_80167858(Player_GetPlayerId(0), Player_GetNametagSlotID(0), 0xD, 0x5A);
        } else if (sp24 > 0) {
            lbl_8046B6A0.unk_14 = 0x149;
            lbl_8046B6A0.unk_18 = 0x28;
        }
    }
    if (gm_801A4310() == 0x2B && lbl_8046B6A0.unk_10 == 0x9C41) {
        gm_80167858(Player_GetPlayerId(0), Player_GetNametagSlotID(0), 0xD, 0x5A);
    }
    switch (gm_801A4310()) {
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x26:
        fn_80182B5C();
    }
}

static inline s8 fn_8016CA68_inline(int var_r31)
{
    int var_r30;
    for (var_r30 = 0; var_r30 < 6; var_r30++) {
        if (var_r31 == Player_GetPlayerId(var_r30) &&
            Player_GetPlayerSlotType(var_r30) == 0) {
            return var_r30;
        }
    }
    return -1;
}

void fn_8016CA68(lbl_8046B6A0_t* arg0, int arg1)
{
    int var_r31;
    s8 var_r0;
    u8 var_r4;

    if (arg0->unk_4 == 0 && arg0->unk_5 != 0 && !arg0->x24C8.x2_4) {
        if (arg0->x24C8.x40 != NULL) {
            var_r31 = arg0->x24C8.x40();
        } else {
            var_r31 = fn_8016BC74();
        }
        if (var_r31 != -1) {
            lbAudioAx_80024E84(1);
            lbAudioAx_80024030(5);
            ifAll_802F3394();
            if (arg0->x24C8.x3_7) {
                ifTime_802F40B8();
            }
            if (!arg0->x24C8.x3_6) {
                var_r4 = 0;
                if (arg0->x24C8.x3_5) {
                    var_r4 |= 1;
                }
                if (arg0->x24C8.x3_3) {
                    var_r4 |= 2;
                }
                if (arg0->x24C8.x3_1) {
                    var_r4 |= 4;
                }
                gm_801A0FEC(var_r31, var_r4);
            }
            gm_801A4634(arg1);
            if (arg0->x24C8.x4_0) {
                var_r0 = fn_8016CA68_inline(var_r31);
                if (arg0->x24C8.x3C != NULL) {
                    arg0->x24C8.x3C(var_r0);
                } else {
                    fn_80165108(var_r0, var_r31);
                }
            }
            HSD_PadRumblePauseAll();
            arg0->unk_1 = var_r31;
            arg0->unk_2 = 0xA;
        }
    }
}

static inline int fn_8016CBE8_inline(void)
{
    HSD_PadStatus* pad;
    bool var_r0;
    int i;
    for (i = 0; i < 4; i++) {
        pad = &HSD_PadCopyStatus[(u8) i];
        if (pad->err == 0) {
            if (g_debugLevel >= 3) {
                if ((pad->trigger & 8) && (pad->button & HSD_PAD_X)) {
                    var_r0 = true;
                } else {
                    var_r0 = false;
                }
            } else {
                var_r0 = pad->trigger & 0x1000;
            }
            if (var_r0) {
                return i;
            }
        }
    }
    return -1;
}

void fn_8016CBE8(lbl_8046B6A0_t* arg0, int arg1)
{
    int i;
    PAD_STACK(0x14);

    if (arg0->unk_2 != 0) {
        return;
    }
    if (arg0->unk_5 == 0) {
        return;
    }
    if (arg0->x24C8.x2_4) {
        return;
    }

    i = fn_8016CBE8_inline();

    if (i != -1 && i == arg0->unk_1) {
        lbAudioAx_80024E84(0);
        gm_801A4674(arg1);
        ifAll_802F33CC();
        gm_801A10FC(i);
        HSD_PadRumbleUnpauseAll();
        if (arg0->x24C8.x4_0) {
            if (arg0->x24C8.x38 != NULL) {
                arg0->x24C8.x38(i);
            } else {
                Ground_801C5800();
            }
        }
        arg0->unk_4 = 0xA;
    }
}

void fn_8016CD98(lbl_8046B6A0_t* arg0)
{
    s32 temp_r3_4;
    s32 var_r3;
    u16 temp_r3_2;
    u8 temp_r0_2;
    u8 temp_r3_5;
    int i;
    PAD_STACK(4);

    if (arg0->unk_5 == 0) {
       return;
    }

    if (gm_801A4624() == 0 || gm_801A46B8(0) != 0 || arg0->x24C8.x3_7 == 1) {
        if (arg0->unk_24 < -1) {
            arg0->unk_24++;
        }
        if (arg0->x24C8.x0_6) {
            if (++arg0->unk_2C >= 0x3C) {
                arg0->unk_2C = 0;
                if (arg0->x24C8.x0_7) {
                    if (arg0->unk_28 < -1) {
                        arg0->unk_28++;
                    }
                } else {
                    if (arg0->unk_28 != 0) {
                        if (arg0->unk_28 < 6 && ifTime_802F4898() == 0) {
                            temp_r3_4 = lbl_8046B6A0.unk_1C[arg0->unk_28];
                            if (temp_r3_4 >= 0) {
                                lbAudioAx_800237A8(temp_r3_4, 0x7FU, 0x40U);
                            }
                        }
                        arg0->unk_28 -= 1;
                    }
                }
            }
        }
        for (i = 0; i < 4; i++) {
            temp_r3_5 = arg0->unk_38[i].x1;
            if (arg0->unk_38[i].x1 != 0) {
                arg0->unk_38[i].x1--;
                temp_r0_2 = arg0->unk_38[i].x1;
                if (temp_r0_2 == 0x50) {
                    if (arg0->unk_38[i].x2 == 0) {
                        var_r3 = arg0->unk_20[i];
                    } else {
                        var_r3 = 0x7C865;
                    }
                    lbAudioAx_80023870(var_r3, 0x7F, 0x40, 0x19);
                } else if (temp_r0_2 == 0) {
                    lbAudioAx_80023870(0x7C852, 0x7F, 0x40, 0x19);
                }
            }
        }
    }
}

void fn_8016CF4C(int arg0, int arg1)
{
    gm_801A10FC(arg0);
    lbl_8046B6A0.unk_8 = arg1;
    if (arg1 != 8 && g_debugLevel >= 3) {
        gm_801A4674(1);
        if (lbl_8046B6A0.x24C8.xD > 1) {
            lbl_8046B6A0.unk_30 = lbl_8046B6A0.x24C8.xD - 1;
        }
        fn_8016C7F0();
        lbAudioAx_80024D50();
        gm_801A4634(4);
        lbl_8046B6A0.unk_0 = 1;
        return;
    }
    fn_8016C7F0();
    gm_801A4B60();
}

static inline void fn_8016CF4C_dontinline(int arg0, int arg1)
{
    fn_8016CF4C(arg0, arg1);
}

static inline void fn_8016CFE0_inline(void)
{
    lbl_8046B6A0_t* tmp;
    int i;

    if (g_debugLevel >= 3 && gm_801A46B8(0) != 0 &&
        (HSD_PadCopyStatus->button & 0x1160) == 0x1160) {
        fn_8016C7F0();
        gm_801A4B60();
    }

    tmp = &lbl_8046B6A0;
    for (i = 0; i < 6; i++) {
        if (tmp->unk_38[i].xA != 0) {
            if (--tmp->unk_38[i].xA == 0) {
                fn_8016719C(i, tmp->unk_38[i].xB);
            }
        }
    }
}

void fn_8016CFE0(void)
{
    lbl_8046B6A0_t* tmp = &lbl_8046B6A0;
    s64 var_r29_2;
    int var_r29;
    int var_r4;
    PAD_STACK(0x10);

    fn_8016CFE0_inline();

    fn_8016A4C8();
    fn_8016758C();
    if (gm_801A45E8(1) != 0) {
        var_r4 = fn_8016CBE8_inline();
        if (g_debugLevel >= 3) {
            var_r29 = 0x160;
        } else {
            var_r29 = 0x1160;
        }
        var_r29_2 = var_r29;
        if (tmp->x24C8.x3_4 && tmp->unk_2 == 0 && tmp->unk_3 == 0) {
            if ((var_r29_2 & gm_801A36A0(tmp->unk_1))) {
                if (!(var_r29_2 & gm_801A3680(tmp->unk_1))) {
                    fn_8016CF4C_dontinline(var_r4, 7);
                    return;
                }
            }
        }
        if (tmp->x24C8.x3_2 && tmp->unk_2 == 0 && tmp->unk_3 == 0) {
            if ((gm_801A36A0(tmp->unk_1) & 0x10) != 0) {
                fn_8016CF4C_dontinline(var_r4, 8);
                return;
            }
        }
        fn_8016CBE8(tmp, 1);
        if (tmp->unk_2 != 0) {
            tmp->unk_2--;
        }
        goto block_50;
    } else {
        tmp->unk_8 = fn_8016C35C();
        if (tmp->unk_8 == 0) {
            fn_8016CA68(tmp, 1);
            if (tmp->unk_4 != 0) {
                tmp->unk_4--;
            }
        } else {
            goto block_51;
        }
block_50:
        fn_8016B918();
        tmp->unk_8 = fn_8016C35C();
    }
    if (tmp->unk_8 != 0) {
block_51:
        fn_8016C7F0();
        ifStatus_802F7034(fn_8016B88C);
        lbAudioAx_80024D50();
        gm_801A4634(4);
        tmp->unk_0 = 1;
    } else {
        fn_8016CD98(tmp);
    }
}

void gm_8016D32C_OnFrame(void)
{
    int i;
    lbl_8046B6A0_t* tmp = &lbl_8046B6A0;
    PAD_STACK(0x28);

    fn_8016CFE0_inline();

    fn_8016758C();
    if (gm_801A45E8(2) != 0) {
        fn_8016CBE8_inline();
        fn_8016CBE8(tmp, 2);
        if (tmp->unk_2 != 0) {
            tmp->unk_2--;
        }
    } else {
        fn_8016CA68(tmp, 2);
        if (tmp->unk_4 != 0) {
            tmp->unk_4--;
        }
    }
    fn_8016CD98(tmp);
    tmp->unk_8 = fn_8016C35C();
    if (tmp->unk_8 != 0) {
        fn_8016C7F0();
        gm_801A4B60();
    }
}

bool fn_8016D538(void)
{
    bool result = true;
    PAD_STACK(4);

    if (gm_8016B3D8()) {
        if (fn_8017DF90() == 0 && gm_801A42C4() == 0x49) {
            result = true;
        } else {
            if (gm_8016B184() && fn_801693A8() != 0) {
                result = false;
            } else if (lbl_8046B6A0.x24C8.x5_1) {
                result = false;
            }
        }
        if (fn_8017DF90() == 1 && (fn_8017DEC8(1)[8] & 0x20)) {
            result = false;
        }
    }
    return result;
}

static inline void fn_8016D634_inline(struct lbl_8046B6A0_24C_t* dst)
{
    lbl_8046B6A0_t* tmp = &lbl_8046B6A0;
    if (lbl_8046B6A0.unk_E == 0) {
        *dst = tmp->x24C;
        dst->x6 = tmp->x24C8.x8;
        dst->x4 = tmp->unk_8;
        gm_80166378(dst);
        fn_8016C46C_dontinline((int) dst);
        if (tmp->unk_8 != 7 && tmp->unk_8 != 8) {
            fn_8016C4F4(dst);
        }
        tmp->unk_E = 1;
    } else {
        *dst = tmp->x24C;
    }
}

void fn_8016D634(void)
{
    lbl_8046B6A0_t* tmp = &lbl_8046B6A0;
    struct lbl_8046B6A0_24C_t* temp_r6;

    PAD_STACK(8);

    if (++lbl_8046B6A0.unk_30 <= lbl_8046B6A0.x24C8.xD) {
        return;
    }
    if (gm_8016B3D8()) {
        pl_80040688(0, lbl_8046B6A0.unk_D, fn_8016D538());
    }
    gm_801A4B1C();
    if (lbl_8046B6A0.x24C8.x4_4 && lbl_8046B6A0.unk_8 != 1 &&
        (lbl_8046B6A0.x24C8.x9 == 1 || Player_GetStocks(0) > 0)) {
        un_802FD668();
        ifAll_802F3A64();
        gm_801A4674(4);
        gm_801A4634(5);
        lbl_8046B6A0.unk_9 = 1;
        temp_r6 = &tmp->x24C;
        if (lbl_8046B6A0.unk_E == 0) {
            *temp_r6 = tmp->x24C;
            temp_r6->x6 = lbl_8046B6A0.x24C8.x8;
            temp_r6->x4 = tmp->unk_8;
            gm_80166378(temp_r6);
            fn_8016C46C_dontinline((int) temp_r6);
            if (tmp->unk_8 != 7 && tmp->unk_8 != 8) {
                fn_8016C4F4(temp_r6);
            }
            tmp->unk_E = 1;
        } else {
            *temp_r6 = tmp->x24C;
        }
        fn_80180630(tmp->x24C8.x18, 0, tmp->x24C8.x9, tmp->x24C8.x4_5, temp_r6);
        lbl_8046B6A0.unk_0 = 2;
    } else {
        lbl_8046B6A0.unk_0 = 3;
    }
}

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
    lbl_8046B6A0_t* tmp = gm_8016AE38();
    PAD_STACK(4);

    Player_SetSlottype(arg0, arg1->x1);
    Player_SetPlayerCharacter(arg0, arg1->x0);

    tmp->unk_38[arg0].x0 = arg1->x0;

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
        tmp->unk_38[arg0].x4_b4 = 1;
    }

    tmp->unk_38[arg0].x3 = arg1->x5;

    Player_SetHandicap(arg0, (s8) arg1->x8);
    Player_SetTeam(arg0, (s8) arg1->x9);
    Player_SetFlagsBit0(arg0, arg1->xC_b0);
    Player_SetNametagSlotID(arg0, arg1->xA);
    if (arg1->xC_b1) {
        tmp->unk_A += 5;
        Player_SetFlagsBit3(arg0, 1);
        Player_SetUnk4C(arg0, tmp->unk_A);
    }
    Player_SetPlayerAndEntityCpuType(arg0, arg1->xE);
    Player_SetPlayerAndEntityCpuLevel(arg0, arg1->xF);
    if (arg1->x10 != 0) {
        Player_SetHUDDamage(arg0, arg1->x10);
    } else {
        Player_SetHUDDamage(arg0, arg1->x12);
    }

    tmp->unk_38[arg0].x6 = arg1->x12;

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

    tmp->unk_38[arg0].x4_b1 = arg1->xC_b3;
    tmp->unk_38[arg0].x4_b0 = arg1->xC_b2;
    if (arg1->xC_b2) {
        Player_SetFlagsBit5(arg0, 1);
    } else {
        Player_SetFlagsBit5(arg0, 0);
    }
    tmp->unk_38[arg0].x4_b2 = arg1->xC_b4;
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
    tmp->unk_38[arg0].x4_b3 = arg1->xD_b1;
    Player_SetMoreFlagsBit6(arg0, arg1->xB);
    Player_SetFacingDirection(arg0, arg1->x6);
    tmp->unk_38[arg0].x4_b5 = arg1->xD_b0;
}

void fn_8016DCC0(StartMeleeData* arg0)
{
    lbl_8046B6A0_t* tmp = &lbl_8046B6A0;
    int i;

    memzero(&lbl_8046B6A0, 0x24C8);
    lbl_8046B6A0.unk_D = 6;
    lbl_8046B6A0.unk_1C = (void*) &lbl_803D5630;
    lbl_8046B6A0.unk_20 = (void*) &lbl_803D5620;
    lbl_8046B6A0.unk_0 = 0;

    lbl_8046B6A0.x24C8 = arg0->rules;

    lbl_8046B6A0.x24C.x5 = arg0->rules.x0_0;
    lbl_8046B6A0.x24C.x6 = arg0->rules.x8;
    if (arg0->rules.x7 != 0) {
        lbl_8046B6A0.unk_B = arg0->rules.x7;
    }
    lbl_8046B6A0.x24C.xC = arg0->rules.xC;
    Camera_80030E34(arg0->rules.x2C);

    if (tmp->x24C8.x0_6) {
        if (tmp->x24C8.x0_7) {
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

void fn_8016DEEC(void)
{
    lbl_8046B6A0_t* tmp = &lbl_8046B6A0;
    lbl_8046B6A0_t* tmp2 = &lbl_8046B6A0;
    float sp18[6];
    Vec3 spC;
    float temp_f0;
    float var_f1;
    float var_f26;
    float var_f25;
    int var_r25;
    int i;
    int j;
    int var_r23;

    for (i = 0; i < 6; i++) {
        if (Player_GetPlayerSlotType(i) != 3) {
            if (tmp->unk_38[i].x3 == -1) {
                Stage_80224E64(i, &spC);
            } else {
                int x = tmp2->unk_38[i].x3;
                Stage_80224E64(x, &spC);
            }
            sp18[i] = spC.x;
        }
    }
    for (i = 0; i < 6; i++) {
        if (Player_GetPlayerSlotType(i) != 3 && Player_GetFacingDirection(i) == 0.0f) {
            var_r23 = -1;

            for (j = 0; j < 6; j++) {
                if (j != i &&
                    Player_GetPlayerSlotType(j) != 3 &&
                    (tmp->x24C8.x8 != 1 || Player_GetTeam(i) != Player_GetTeam(j))) {
                    if (var_r23 == -1 || var_f25 < (var_f26 = fabs_inline(sp18[i] - sp18[j]))) {
                        var_r23 = j;
                        var_f25 = var_f26;
                    }
                }
            }
            if (var_r23 == -1) {
                var_f1 = 1.0f;
            } else {
                temp_f0 = sp18[var_r23] - sp18[i];
                if (temp_f0 < -5.0F) {
                    var_f1 = -1.0F;
                } else if (temp_f0 > 5.0F) {
                    var_f1 = +1.0F;
                } else if (Player_GetFacingDirection(var_r23) == +1.0F) {
                    var_f1 = -1.0F;
                } else if (Player_GetFacingDirection(var_r23) == -1.0F) {
                    var_f1 = +1.0F;
                } else {
                    var_f1 = +1.0F;
                }
            }
            Player_SetFacingDirection(i, var_f1);
        }
    }
}

void fn_8016E124(void)
{
    int var_r27 = 0;
    int i;
    int j;
    int temp_r3;

    int sp10[7];

    for (i = 0; i < 7; i++) {
        sp10[i] = -1;
    }

    for (i = 0; i < 6; i++) {
        if (Player_GetPlayerSlotType(i) != 3 &&
            Player_GetPlayerCharacter(i) == CKIND_KIRBY) {
            s8 temp_r3 = Player_GetCostumeId(i);
            bool var_r5 = false;
            for (j = 0; j < var_r27; j++) {
                if (temp_r3 == sp10[j]) {
                    var_r5 = true;
                    break;
                }
            }
            if (!var_r5) {
                sp10[var_r27] = temp_r3;
                var_r27++;
            }
        }
    }
    if (var_r27 > 0) {
        for (i = 0; i < 6; i++) {
            if (Player_GetPlayerSlotType(i) != 3) {
                temp_r3 = Player_80032610(i, 0);
                if (temp_r3 != -1 && temp_r3 != 4) {
                    for (j = 0; j < var_r27; j++) {
                        Player_80031DA8(temp_r3, sp10[j]);
                    }
                }
                temp_r3 = Player_80032610(i, 1);
                if (temp_r3 != -1 && temp_r3 != 4) {
                    for (j = 0; j < var_r27; j++) {
                        Player_80031DA8(temp_r3, sp10[j]);
                    }
                }
            }
        }
    }
}

void fn_8016E2BC(void)
{
    lbl_8046B6A0_t* tmp = &lbl_8046B6A0;
    u8 _[4];
    Vec3 sp24;
    Vec3 sp18;
    float var_f1;
    float var_f1_2;
    bool var_r0;
    int i;
    int temp_r27;
    int temp_r24;
    PAD_STACK(0x10);

    Player_80036DA4();
    if (tmp->unk_7 == 1) {
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (var_r0) {
        if (tmp->unk_38[0].x3 == -1) {
            Stage_80224E64(0, &sp24);
        } else {
            int x = tmp->unk_38[0].x3;
            Stage_80224E64(x, &sp24);
        }
        if (Player_GetFacingDirection(0) == 0.0F) {
            if (Stage_80224DC8(tmp->x24C8.xE) != 0) {
                Player_SetFacingDirection(0, 1.0F);
            } else {
                if (sp24.x >= 0.0F) {
                    var_f1 = -1.0F;
                } else {
                    var_f1 = +1.0F;
                }
                Player_SetFacingDirection(0, var_f1);
            }
        }
        Player_80032768(0, &sp24);
        temp_r27 = tmp->x24C8.x8 == 1;
        Player_SetUnk45(0, fn_80160840(gm_80160854(Player_GetPlayerId(0), Player_GetTeam(0), temp_r27, Player_GetPlayerSlotType(0))));
        Player_80031AD0(0);
        if (tmp->unk_38[0].x4_b4) {
            lbAudioAx_800237A8(0x41F4E, 0x7F, 0x40);
        }
        fn_80169C54(Player_GetPlayerCharacter(0), Player_GetCostumeId(0));
        fn_80169F50(Player_GetPlayerCharacter(0), Player_GetCostumeId(0));
    } else {
        fn_8016DEEC();
        for (i = 0; i < 6; i++) {
            if (Player_GetPlayerSlotType(i) != 3) {
                if (tmp->unk_38[i].x3 == -1) {
                    Stage_80224E64(i, &sp18);
                } else {
                    Stage_80224E64(tmp->unk_38[i].x3, &sp18);
                }
                if (Player_GetFacingDirection(i) == 0.0F) {
                    if (Stage_80224DC8(tmp->x24C8.xE) != 0) {
                        Player_SetFacingDirection(i, 1.0F);
                    } else {
                        if (sp18.x >= 0.0F) {
                            var_f1_2 = -1.0F;
                        } else {
                            var_f1_2 = +1.0F;
                        }
                        Player_SetFacingDirection(i, var_f1_2);
                    }
                }
                Player_80032768(i, &sp18);
                temp_r24 = tmp->x24C8.x8 == 1;
                Player_SetUnk45(i, fn_80160840(
                    gm_80160854(Player_GetPlayerId(i), Player_GetTeam(i),
                                temp_r24, Player_GetPlayerSlotType(i))));
                Player_80031AD0(i);
                if (tmp->unk_38[i].x4_b4) {
                    lbAudioAx_800237A8(0x41F4E, 0x7F, 0x40);
                }
            }
        }
        fn_8016E124();
    }
}

bool fn_8016E5C0(StartMeleeData* arg0)
{
    bool var_r4;
    bool var_r6;
    int i;

    if (arg0->rules.xA != 0) {
        return arg0->rules.xA;
    }
    var_r4 = false;
    var_r6 = false;
    for (i = 0; i < 6; i++) {
        if (arg0->players[i].x1 == 0) {
            var_r4 = true;
            if (!(HSD_PadCopyStatus[(u8) i].button & (HSD_PAD_L | HSD_PAD_R))) {
                var_r6 = true;
                break;
            }
        }
    }

    if (var_r4 && !var_r6) {
        return true;
    }
    return false;
}

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
    if (gm_8016B41C_dontinline() != 0) {
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
        ifStatus_802F6EA4(8, -1, -1, 0, (void*) fn_8016B7B4, fn_8016B7F8);
    } else {
        ifStatus_802F6EA4(3, -1, -1, 0, (void*) fn_8016B7B4, fn_8016B7F8);
    }
    ifTime_802F446C();
    ifStatus_802F665C(tmp->rules.x0_3);
}

struct EndMeleeData {
    /* 00 */ u32 x0;
    /* 04 */ u32 x4;
    /* 08 */ u32 x8;
    /* 0C */ struct lbl_8046B6A0_24C_t xC;
};

static inline bool gm_8016E9C8_inline() {
    switch (gm_801A4310()) {
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x1D:
    case 0x1E:
    case 0x1F:
    case 0x2A:
    case 0x2C:
        return true;
    default:
        return false;
    }
}

void gm_8016E9C8(void* arg0_raw)
{
    struct EndMeleeData* arg0 = arg0_raw;
    lbl_8046B6A0_t* tmp = &lbl_8046B6A0;
    int i;

    if (lbl_8046B6A0.unk_E == 0) {
        arg0->xC = lbl_8046B6A0.x24C;
        arg0->xC.x6 = lbl_8046B6A0.x24C8.x8;
        arg0->xC.x4 = lbl_8046B6A0.unk_8;
        gm_80166378(&arg0->xC);
        fn_8016C46C_dontinline((int) &arg0->xC);
        if (tmp->unk_8 != 7 && tmp->unk_8 != 8) {
            fn_8016C4F4(&arg0->xC);
        }
        tmp->unk_E = 1;
    } else {
        arg0->xC = lbl_8046B6A0.x24C;
    }
    if (lbl_8046B6A0.x24C8.x4_4) {
        arg0->x0 = fn_8017F294();
    } else {
        arg0->x0 = lbl_8046B6A0.x24C8.x18;
    }
    arg0->x4 = lbl_8046B6A0.unk_28;
    arg0->x8 = Ground_801C5ABC();

    if (gm_8016B3D8() || gm_8016E9C8_inline() || gm_801A4310() == 2) {
        if (lbl_8046B6A0.unk_8 != 7 && lbl_8046B6A0.unk_8 != 8) {
            for (i = 0; i < 6; i++) {
                if (Player_GetPlayerSlotType(i) == 0) {
                    gmMainLib_8015D00C(gm_80164024(Player_GetPlayerCharacter(i)));
                }
            }
        }
    }
}

void gm_8016EBC0_OnEnter(void* arg0)
{
    StartMeleeData* tmp = arg0;
    tmp->rules.x6 = true;
    fn_8016E730(tmp);
    ifStatus_802F6EA4(1, -1, -1, 0, (void*) fn_8016B7B4, fn_8016B7F8);
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

float gm_8016ECE8(void)
{
    float var_f29;
    int count;
    int i;

    count = 0;
    var_f29 = 0.0F;
    for (i = 0; i < 6; i++) {
        CharacterKind kind = Player_GetPlayerCharacter(i);
        if (kind == CKIND_MASTERH || kind == CKIND_CREZYH) {
            var_f29 += (float) Player_GetRemainingHP(i) / Player_GetOtherStamina(i);
            count++;
        }
    }
    if (count > 0) {
        var_f29 /= count;
    }
    return var_f29;
}

static inline void gm_8016EDDC_inline(int arg0, int temp_r3, Vec3* sp18)
{
}

bool gm_8016EDDC(int arg0, PlayerInitData* arg1)
{
    lbl_8046B6A0_t* tmp = &lbl_8046B6A0;
    Vec3 sp18;
    float var_f1;
    u8 temp_r30;
    u8 temp_r29;
    int temp_r27;
    s8 temp_r3;
    PAD_STACK(4);

    if (lbl_8046B6A0.unk_7 == 0 && Player_GetPlayerSlotType(arg0) == 3 &&
        Player_GetEntity(arg0) == NULL) {

        Player_80036D24(arg0);
        fn_8016D8AC(arg0, arg1);

        temp_r3 = tmp->unk_38[arg0].x3;
        if (temp_r3 == -1) {
            Stage_80224E64(arg0, &sp18);
        } else {
            Stage_80224E64(temp_r3, &sp18);
        }

        if (Player_GetFacingDirection(arg0) == 0.0F) {
            if (Stage_80224DC8(lbl_8046B6A0.x24C8.xE) != 0) {
                Player_SetFacingDirection(arg0, 1.0F);
            } else {
                if (sp18.x >= 0.0F) {
                    var_f1 = -1.0F;
                } else {
                    var_f1 = +1.0F;
                }
                Player_SetFacingDirection(arg0, var_f1);
            }
        }
        Player_80032768(arg0, &sp18);
        temp_r27 = lbl_8046B6A0.x24C8.x8 == 1;
        Player_SetUnk45(arg0, fn_80160840(
            gm_80160854(Player_GetPlayerId(arg0), Player_GetTeam(arg0),
                        temp_r27, Player_GetPlayerSlotType(arg0))));
        Player_80031AD0(arg0);
        if (lbl_8046B6A0.unk_38[arg0].x4_b4) {
            lbAudioAx_800237A8(0x41F4E, 0x7F, 0x40);
        }
        fn_8016E124();
        Player_80031848(arg0);
        ifStatus_802F6508(arg0);
        un_802FD28C(arg0);
        return true;
    }
    return false;
}

bool fn_8016EF98(int arg0)
{
    if (lbl_8046B6A0.unk_7 == 0 && Player_GetEntity(arg0) != NULL) {
        ifStatus_802F6788(arg0);
        Player_80031EBC(arg0);
        Player_SetSlottype(arg0, 3);
        return 1;
    }
    return 0;
}

void gm_8016F00C(int arg0)
{
    fn_8016719C(arg0, 0);
}

void fn_8016F030(StartMeleeData* arg0)
{
    int i;
    gm_80167A64(&arg0->rules);
    for (i = 0; i < 6; i++) {
        gm_8016795C(&arg0->players[i]);
    }
}

void gm_8016F088(StartMeleeData* arg0)
{
    int var_r3;
    int temp_r3;
    int i;

    for (i = 0; i < 6; i++) {
        if (arg0->players[i].x1 == 0 && i < 4) {
            temp_r3 = arg0->players[i].x4;
            if (temp_r3 == 0) {
                var_r3 = i;
            } else {
                var_r3 = temp_r3 - 1;
            }
            arg0->players[i].xC_b0 = gm_801677F8(var_r3, arg0->players[i].xA);
        } else {
            arg0->players[i].xC_b0 = false;
        }
    }
}

void gm_8016F120(int arg0)
{
    gmMainLib_8015DADC(arg0);
}

void fn_8016F140(int arg0)
{
    gmMainLib_8015DAB4(arg0);
}

void fn_8016F160(int arg0, int arg1)
{
    pl_80039418(arg0, arg1);
}

int fn_8016F180(int arg0)
{
    struct lbl_803D5A4C_t* curr = lbl_803D5A4C;
    while (curr->x0 != arg0) {
        if (curr->x0 == 0x29A) {
            return 0;
        }
        curr++;
    }
    return curr->x4;
}

int gmDecisionGetType(int kind)
{
    struct lbl_803D5A4C_t* curr = lbl_803D5A4C;
    while (curr->x0 != kind) {
        if (curr->x0 == 0x29A) {
            return 0;
        }
        curr++;
    }
    return curr->x5;
}

short fn_8016F1F0(int idx)
{
    return lbl_803D5A4C[idx].x0;
}

int gm_8016F208(int arg0)
{
    struct lbl_803D5A4C_t* curr = lbl_803D5A4C;
    while (curr->x0 != arg0) {
        if (curr->x0 == 0x29A) {
            return 0;
        }
        curr++;
    }
    if (curr->x2 == 0xDE && lbLang_IsSettingUS()) {
        return 0x102;
    }
    return curr->x2;
}

int fn_8016F280(int arg0)
{
    return gm_8016F208(arg0) - 2;
}

int gm_8016F2F8(int arg0, u8 arg1)
{
    struct lbl_803D5A4C_t* curr = lbl_803D5A4C;
    while (curr->x0 != arg0) {
        if (curr->x0 == 0x29A) {
            return -1;
        }
        curr++;
    }
    return lbl_803D5648[curr->x2 - 2];
}

void fn_8016F344(struct lbl_8046B6A0_24C_t* arg0)
{
    struct lbl_8046B6A0_24C_58_t* curr = arg0->x58;
    int i;
    for (i = 0; i < 4; i++) {
        if (curr->x0 != 3) {
            pl_80039450(i);
        }
        curr++;
    }
}

/// #fn_8016F39C

/// #fn_8016F548

/// #fn_8016F740

/// #fn_8016F870

/// #fn_8016F9A8

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

static inline bool gm_80173EEC_inline(void)
{
    int i;
    bool result = true;

    for (i = 0; i < 0x100; i++) {
        if (i != 0x29 && i - 0x42 > 1U && i != 0xB9 &&
            i - 0xC9 > 1U && i != 9 && gmMainLib_8015DADC(i) == 0) {
            result = false;
            break;
        }
    }
    return result;
}

void gm_80173EEC(void)
{
    int i;
    u16* temp_r29;
    u8 temp_r3;

    for (i = 0; i < 0x19; i++) {
        temp_r29 = &gmMainLib_8015EDBC()->x18[i];
        if (*temp_r29 >= 0x64) {
            temp_r3 = gm_8016400C(i);
            fn_80172C78(gm_80160474(temp_r3, 3));
            if (temp_r3 == 0x12) {
                fn_80172C78(gm_80160474(0x13, 3));
            }
            if (temp_r3 == 0x13) {
                fn_80172C78(gm_80160474(0x12, 3));
            }
        }
        if (*temp_r29 >= 0xC8) {
            temp_r3 = gm_8016400C(i);
            fn_80172C78(gm_80160474(temp_r3, 4));
            if (temp_r3 == 0x12) {
                fn_80172C78(gm_80160474(0x13, 4));
            }
            if (temp_r3 == 0x13) {
                fn_80172C78(gm_80160474(0x12, 4));
            }
        }
        if (*temp_r29 >= 0x12C) {
            temp_r3 = gm_8016400C(i);
            fn_80172C78(gm_80160474(temp_r3, 5));
            if (temp_r3 == 0x12) {
                fn_80172C78(gm_80160474(0x13, 5));
            }
            if (temp_r3 == 0x13) {
                fn_80172C78(gm_80160474(0x12, 5));
            }
        }
    }

    if (fn_80164B48() != 0) {
        fn_80172C78(0xA0);
    }
    if (gm_80164ABC() != 0) {
        fn_80172C78(0x9F);
    }
    if (gmMainLib_8015EE90() != 0) {
        fn_80172C78(0xDC);
    }
    if (gmMainLib_8015EDBC()->x14 >= 0x2710) {
        fn_80172C78(0x10C);
    }
    if (gmMainLib_8015D94C(0x1A) != 0) {
        fn_80172C78(0x96);
    }
    if (un_803045A0() != 0) {
        fn_80172C78(0x116);
    }
    if (un_80304690() != 0) {
        fn_80172C78(0xAF);
    }
    if (un_80304780() != 0) {
        fn_80172C78(0x100);
    }

    if (gm_80173EEC_inline()) {
        fn_80172C78(0x123);
    }
}

/// #gm_80174180

/// #gm_801741FC

/// #gm_80174238
