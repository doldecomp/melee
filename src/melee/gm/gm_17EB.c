#include "gm_17EB.h"

#include "gm_17C0.h"
#include "gm_17C9.h"
#include "platform.h"

#include "baselib/forward.h"

#include "dolphin/pad.h"

#include "gm/forward.h"

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
#include <melee/gm/gm_16AE.h>
#include <melee/gm/gm_16F1.h>
#include <melee/gm/gm_17AD.h>
#include <melee/gm/gm_17BA.h>
#include <melee/gm/gm_1832.h>
#include <melee/gm/gm_19EF.h>
#include <melee/gm/gm_1A36.h>
#include <melee/gm/gm_1A3F.h>
#include <melee/gm/gm_1A45.h>
#include <melee/gm/gm_1A7A.h>
#include <melee/gm/gm_1ADD.h>
#include <melee/gm/gm_1AED.h>
#include <melee/gm/gm_1B03.h>
#include <melee/gm/gm_1BA8.h>
#include <melee/gm/gm_1BFA.h>
#include <melee/gm/gmadventure.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/gmregcommon.h>
#include <melee/gm/gmtoulib.h>
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
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbbgflash.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lbcardnew.h>
#include <melee/lb/lblanguage.h>
#include <melee/lb/lbspdisplay.h>
#include <melee/lb/lbtime.h>
#include <melee/mp/mpcoll.h>
#include <melee/pl/player.h>
#include <melee/sc/types.h>
#include <melee/ty/toy.h>

typedef struct {
    u8 b7 : 1, b6 : 1, b5 : 1, b4 : 1, b3 : 1, b2 : 1, b1 : 1, b0 : 1;
} u8_bits;

typedef struct {
    Unk1PData x0;
    u8 (*x48)(u8, u8);
    u8 (*x4C)(u8, u8, u8);
    u8 (*x50)(u8, u8, u8);
    u8 (*x54)(u8, u8, u8);
    u8 (*x58)(u8, u8, u8);
    u8 (*x5C)(u8, u8, u8);
    u8 (*x60)(u8, u8, u8);
    float (*x64)(u8, u8);
    float (*x68)(u8, u8);
    float (*x6C)(u8, u8);
    float (*x70)(u8, u8);
    u16 x74;
} RegClearAllstarData;
STATIC_ASSERT(sizeof(RegClearAllstarData) == 0x78);

static RegClearAllstarData lbl_80472CB0;

UnkAllstarData* gm_GetAllStarData(void)
{
    return (UnkAllstarData*) &lbl_80472CB0;
}

u8 gm_8017EB3C(u8 difficulty, u8 stage_slot)
{
    return lbl_803D85F0.entries[stage_slot + difficulty * 5].stage_kind;
}

u8 gm_8017EB64(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D85F0.entries[stage_slot + difficulty * 5].pad_6[arg2 * 3];
}

u8 gm_8017EB98(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D85F0.entries[stage_slot + difficulty * 5]
        .pad_6[arg2 * 3 + 1];
}

u8 gm_8017EBCC(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D85F0.entries[stage_slot + difficulty * 5]
        .pad_6[arg2 * 3 + 2];
}

f32 gm_8017EC00(u8 difficulty, u8 stage_slot)
{
    return lbl_803D85F0.entries[stage_slot + difficulty * 5].scale2_pct /
           100.0F;
}

f32 gm_8017EC50(u8 difficulty, u8 stage_slot)
{
    return lbl_803D85F0.entries[stage_slot + difficulty * 5].scale3_pct /
           100.0F;
}

u8 gm_8017ECA0(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D85F0.entries[stage_slot + difficulty * 5].pad_14[arg2 * 3];
}

u8 gm_8017ECD4(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D85F0.entries[stage_slot + ((u8) difficulty * 5)]
        .pad_14[arg2 * 3 + 1];
}

u8 gm_8017ED08(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D85F0.entries[stage_slot + ((u8) difficulty * 5)]
        .pad_14[arg2 * 3 + 2];
}

f32 gm_8017ED3C(u8 difficulty, u8 stage_slot)
{
    return lbl_803D85F0.entries[stage_slot + difficulty * 5].scale0_pct /
           100.0F;
}

f32 gm_8017ED8C(u8 difficulty, u8 stage_slot)
{
    return lbl_803D85F0.entries[stage_slot + difficulty * 5].scale1_pct /
           100.0F;
}

bool fn_8017EDDC(void)
{
    UnkAllstarData* p;

    if (gm_GetCurrentGameMode() == GM_CLASSIC) {
        p = gm_GetAllStarData();
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
    RegClearAllstarData* allstar;
    gmm_x0_528_t* main_data;
    u32 total_time;
    int i;

    rules = gm_GetRules();
    allstar = &lbl_80472CB0;

    if (fn_8017E318() > 0) {
        ((u8_bits*) &arg0->_x448[2])->b3 = 1;
    }

    if (rules->x4_5) {
        main_data = gmMainLib_8015CDC8();
        total_time = allstar->x0.xC.x20 + gm_8016AEDC();
        ((u8_bits*) &arg0->_x448[0])->b7 = 1;

        if ((u8) allstar->x0.cpu_level == 4) {
            ((u8_bits*) &arg0->_x448[0])->b4 = 1;
        }

        if (total_time < 0x3840U) {
            ((u8_bits*) &arg0->_x448[2])->b6 = 1;
        } else if (total_time < 0x5460U) {
            ((u8_bits*) &arg0->_x448[2])->b7 = 1;
        }

        if ((u32) allstar->x0.xC.x1C == 0U &&
            (u32) arg0->player_standings[0].x44 == 0U)
        {
            ((u8_bits*) &arg0->_x448[1])->b1 = 1;
        }

        if ((u8) allstar->x0.xC.xE != 0) {
            ((u8_bits*) &arg0->_x448[2])->b5 = 1;
        }

        if ((u8) allstar->x0.xC.xF != 0) {
            ((u8_bits*) &arg0->_x448[2])->b4 = 1;
        }

        if ((u8) allstar->x0.xC.xD != 0) {
            ((u8_bits*) &arg0->_x448[1])->b0 = 1;
        } else if ((s8) arg0->player_standings[0].stocks ==
                   (s32) main_data->stocks)
        {
            ((u8_bits*) &arg0->_x448[1])->b2 = 1;
        }
    }

    for (i = 0; i < 6; i++) {
        if (Player_GetPlayerSlotType(i) == Gm_PKind_Cpu &&
            Player_GetPlayerCharacter(i) == CKIND_CREZYH)
        {
            ((u8_bits*) &arg0->_x448[0])->b0 = 1;
            return;
        }
    }
}
#pragma dont_inline reset
