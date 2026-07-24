#include "gm_17E4.h"

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

static UnkAdventureData lbl_80472C30;

UnkAdventureData* gm_GetAdventureData(void)
{
    return &lbl_80472C30;
}

u8 gm_8017E430(void)
{
    return gm_GetAdventureData()->x0.slot;
}

u8 gm_8017E440(void)
{
    UnkAdventureData* r31 = gm_GetAdventureData();
    if (gm_801677F8(r31->x0.slot, r31->x0.x4) == false) {
        return 4;
    }
    return r31->x0.slot;
}

u8 gm_8017E48C(GameScene* scene)
{
    u8 count = 0;
    int i;
    for (i = 0; scene->idx != gm_803DE1B8_Scenes[i].idx; i++) {
        if (gm_803DE1B8_Scenes[i].info.class_id == GS_VS) {
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
    return lbl_803D7AC0.entries[stage_slot + difficulty * 5].stage_kind;
}

f32 gm_8017E528(u8 difficulty, u8 stage_slot)
{
    return lbl_803D7AC0.entries[stage_slot + difficulty * 5].scale0_pct /
           100.0F;
}

f32 gm_8017E578(u8 difficulty, u8 stage_slot)
{
    return lbl_803D7AC0.entries[stage_slot + difficulty * 5].scale1_pct /
           100.0F;
}

u8 gm_8017E5C8(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D7AC0.entries[stage_slot + difficulty * 5].pad_6[arg2 * 3];
}

u8 gm_8017E5FC(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D7AC0.entries[stage_slot + difficulty * 5]
        .pad_6[1 + arg2 * 3];
}

u8 gm_8017E630(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D7AC0.entries[stage_slot + (u8) difficulty * 5]
        .pad_6[arg2 * 3 + 2];
}

f32 gm_8017E664(u8 difficulty, u8 stage_slot)
{
    return lbl_803D7AC0.entries[stage_slot + difficulty * 5].scale0_pct /
           100.0F;
}

f32 gm_8017E6B4(u8 difficulty, u8 stage_slot)
{
    return lbl_803D7AC0.entries[stage_slot + difficulty * 5].scale1_pct /
           100.0F;
}

u8 gm_8017E704(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D7AC0.entries[stage_slot + difficulty * 5]
        .pad_6[0x0E + arg2 * 3];
}

u8 gm_8017E738(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D7AC0.entries[stage_slot + difficulty * 5]
        .pad_6[0xF + arg2 * 3];
}

u8 gm_8017E76C(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D7AC0.entries[stage_slot + difficulty * 5]
        .pad_6[0x10 + (arg2 * 3)];
}

void gm_8017E7A0(u8 matchResult)
{
    if (matchResult == OUTCOME_TIMEOUT) {
        Player_LoseStock(0);
        ifStatus_802F6948(0);
        ifStatus_802F6E3C(0);
    }
}

bool gm_8017E7E0(void)
{
    return gm_GetAdventureData()->x7C == 0x14;
}

void gm_8017E7FC(u8 matchResult)
{
    UnkAdventureData* r31 = gm_GetAdventureData();
    bool cond;

    if (gm_GetCurrentGameMode() == GM_ADVENTURE && r31->x0.cpu_level >= 2 &&
        r31->x0.xC.x20 + gm_8016AEDC() < 0xFD20U)
    {
        cond = true;
    } else {
        cond = false;
    }

    if (!cond) {
        struct StartMeleeRules* rules = gm_GetRules();
        rules->x4_5 = 1;
        r31->x77 = 0;
        gm_SetPendingSceneIndex(0x5A);
    } else {
        r31->x77 = 1;
        gm_SetPendingSceneIndex(0x5A);
    }
}

typedef struct {
    u8 b7 : 1, b6 : 1, b5 : 1, b4 : 1, b3 : 1, b2 : 1, b1 : 1, b0 : 1;
} u8_bits;

#pragma dont_inline on
void fn_8017E8A4(int arg0_int)
{
    MatchEnd* arg0 = (MatchEnd*) arg0_int;
    lbl_8046B6A0_t* gm = gm_16AE_GetUnkData_0();
    struct gm_803DE650_t* stage = gm_8017E4C4(gm_GetCurrentSceneIndex());
    UnkAdventureData* adv = &lbl_80472C30;
    u8* flags = arg0->_x448;
    gmm_x0_528_t* main_data;
    u32 total_time;
    int i;

    if (fn_8017E318() > 0) {
        ((u8_bits*) &flags[2])->b3 = 1;
    }

    if (gm->x24C8.x4_5) {
        main_data = gmMainLib_8015CDD4();
        total_time = adv->x0.xC.x20 + gm_8016AEDC();
        ((u8_bits*) &flags[0])->b6 = 1;

        if ((u8) adv->x0.cpu_level == 4) {
            ((u8_bits*) &flags[0])->b3 = 1;
        }

        if (total_time < 0xC4E0U) {
            ((u8_bits*) &flags[2])->b6 = 1;
        } else if (total_time < 0x13560U) {
            ((u8_bits*) &flags[2])->b7 = 1;
        }

        if ((u32) adv->x0.xC.x1C == 0U &&
            (u32) arg0->player_standings[0].x44 == 0U)
        {
            ((u8_bits*) &flags[1])->b1 = 1;
        }

        if ((u8) adv->x0.xC.xE != 0) {
            ((u8_bits*) &flags[2])->b5 = 1;
        }

        if ((u8) adv->x0.xC.xF != 0) {
            ((u8_bits*) &flags[2])->b4 = 1;
        }

        if ((u8) adv->x0.xC.xD != 0) {
            ((u8_bits*) &flags[1])->b0 = 1;
        } else if ((s8) arg0->player_standings[0].stocks ==
                   (s32) main_data->stocks)
        {
            ((u8_bits*) &arg0->_x448[1])->b2 = 1;
        }
    }

    if (stage->x0 == 3) {
        for (i = 0; i < 6; i++) {
            if (Player_GetPlayerSlotType(i) == Gm_PKind_Cpu &&
                Player_GetPlayerCharacter(i) == CKIND_LUIGI)
            {
                ((u8_bits*) &flags[1])->b7 = 1;
                return;
            }
        }
    }

    if (stage->x0 == 0x11) {
        if (gm->unk_C >= 5) {
            ((u8_bits*) &flags[1])->b6 = 1;
            return;
        }
    }

    if (stage->x0 == 0x25) {
        ((u8_bits*) &flags[1])->b5 = 1;
        return;
    } else if (stage->x0 == 0x53) {
        for (i = 0; i < 6; i++) {
            if (Player_GetPlayerSlotType(i) == Gm_PKind_Cpu &&
                Player_GetPlayerCharacter(i) == CKIND_LUIGI)
            {
                ((u8_bits*) &flags[1])->b4 = 1;
                return;
            }
        }
    }

    if (stage->x0 == 0x5C) {
        ((u8_bits*) &flags[1])->b3 = 1;
    }

    PAD_STACK(8);
}
#pragma dont_inline reset
