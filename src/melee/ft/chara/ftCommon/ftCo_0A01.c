#include "ftCo_0A01.h"

#include "ftCo_0B3E.h"
#include "ftpickupitem.h"

#include <placeholder.h>
#include <platform.h>

#include "ft/chara/ftPopo/ftPp_1211.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_0877.h"
#include "ft/ftlib.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"
#include "ftDonkey/forward.h"
#include "ftKoopa/forward.h"
#include "ftPopo/forward.h"

#include "gm/gm_unsplit.h"
#include "gr/grbigblue.h"
#include "gr/grcorneria.h"
#include "gr/grinishie1.h"
#include "gr/ground.h"
#include "gr/grvenom.h"
#include "gr/stage.h"
#include "gr/types.h"
#include "it/inlines.h"
#include "it/item.h"
#include "it/types.h"

#include "lb/forward.h"

#include "lb/lbcollision.h"
#include "mp/mpisland.h"
#include "mp/mplib.h"
#include "mp/types.h"
#include "pl/player.h"

#include <math.h>
#include <math_ppc.h>
#include <dolphin/mtx.h>
#include <MetroTRK/intrinsics.h>

/**
 * Priority table, mapping ItemKind to priority number,
 * for which items the CPU should prefer to target.
 * Higher numbers are preferred.
 */
int ftCo_803C5A68[] = {
    1, 0, 0, 1, 0, 0, 0, 1, 7, 6, 5, 4, 4, 3, 1, 1, 2, 1,
    5, 2, 2, 2, 3, 3, 3, 4, 0, 0, 8, 4, 1, 4, 4, 5, 5,
};

/* static */ extern StageBlastZone* ftCo_803C6594[];
/* 0A2638 */ static void ftCo_800B1DA0(Fighter* fp);

void ftCo_800A0148(Fighter* fp)
{
    struct Fighter_x1A88_t* x1A88 = &fp->x1A88;

    if (fp->cur_pos.y + x1A88->x558 > Stage_GetBlastZoneTopOffset()) {
        ftCo_800B46B8(fp, 0x80, 0);
        ftCo_800B46B8(fp, 0x81, 0);
        ftCo_800B463C(fp, 0x7F);
    } else if (ftCo_800A1CA8(fp)) {
        ftCo_800B46B8(fp, 0x80, 0);
        ftCo_800B46B8(fp, 0x81, 0);
        ftCo_800B46B8(fp, 0x8E, 0xA);
        ftCo_800B463C(fp, 8);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 7);
        ftCo_800B46B8(fp, 0x8E, 0xA);
        ftCo_800B463C(fp, 8);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 0x7F);
    } else if (ABS(x1A88->x54.x - fp->cur_pos.x) > 30.0) {
        ftCo_800B463C(fp, 8);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B46B8(fp, 0x8F, 0x7F);
        ftCo_800B463C(fp, 7);
        ftCo_800B46B8(fp, 0x8E, 0xA);
        ftCo_800B463C(fp, 8);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 0x7F);
    } else {
        ftCo_800B463C(fp, 8);
        ftCo_800B46B8(fp, 0x80, 0);
        ftCo_800B46B8(fp, 0x81, 0);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 7);
        ftCo_800B46B8(fp, 0x8E, 0xA);
        ftCo_800B463C(fp, 8);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 0x7F);
    }
}

void ftCo_800A0384(Fighter* fp)
{
    if (fp->cur_pos.y + fp->x1A88.x558 > Stage_GetBlastZoneTopOffset()) {
        ftCo_800B46B8(fp, 0x80, 0);
        ftCo_800B46B8(fp, 0x81, 0);
        ftCo_800B463C(fp, 0x7F);
    } else if (ftCo_800A1CA8(fp)) {
        ftCo_800B46B8(fp, 0x80, 0);
        ftCo_800B46B8(fp, 0x81, 0);
        ftCo_800B46B8(fp, 0x8E, 0xA);
        ftCo_800B463C(fp, 8);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 7);
        ftCo_800B46B8(fp, 0x8E, 0xA);
        ftCo_800B463C(fp, 8);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 0x7F);
    } else {
        ftCo_800B463C(fp, 8);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B46B8(fp, 0x91, 0x7F);
        ftCo_800B463C(fp, 7);
        ftCo_800B46B8(fp, 0x8E, 0xA);
        ftCo_800B463C(fp, 8);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 0x7F);
    }
}

void ftCo_800A0508(Fighter* fp)
{
    ftCo_800B46B8(fp, 0x80, 0);
    ftCo_800B46B8(fp, 0x81, 0);
    ftCo_800B463C(fp, 7);
    ftCo_800B46B8(fp, 0x8E, 1);
    ftCo_800B463C(fp, 8);

    /// @todo Shared code with #ftCo_800A963C?
    ftCo_800B46B8(fp, 0x8E, 0x1E);
    ftCo_800B46B8(fp, 0x91, 0x50);
    ftCo_800B46B8(fp, 0x81, 0x7F);
    ftCo_800B463C(fp, 9);
    ftCo_800B46B8(fp, 0x8E, 1);
    ftCo_800B463C(fp, 0xA);

    ftCo_800B46B8(fp, 0x81, 0);
    ftCo_800B463C(fp, 0x7F);
    ftCo_800B463C(fp, 0x7F);
}

void ftCo_800A05F4(Fighter* fp)
{
    if (fp->cur_pos.y + fp->x1A88.x558 > Stage_GetBlastZoneTopOffset()) {
        ftCo_800B46B8(fp, 0x80, 0);
        ftCo_800B46B8(fp, 0x81, 0);
        ftCo_800B463C(fp, 0x7F);
    } else if (ftCo_800A1CA8(fp)) {
        ftCo_800B46B8(fp, 0x80, 0);
        ftCo_800B46B8(fp, 0x81, 0);
        ftCo_800B46B8(fp, 0x8E, 0xA);
        ftCo_800B463C(fp, 8);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 7);
        ftCo_800B46B8(fp, 0x8E, 0xA);
        ftCo_800B463C(fp, 8);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 0x7F);
    } else {
        ftCo_800B46B8(fp, 0x80, 0);
        ftCo_800B46B8(fp, 0x81, 0);
        ftCo_800B463C(fp, 8);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B46B8(fp, 0x94, 0x7F);
        ftCo_800B463C(fp, 7);
        ftCo_800B46B8(fp, 0x8E, 0xA);
        ftCo_800B463C(fp, 8);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 0x7F);
    }
}

void ftCo_800A0798(Fighter* fp)
{
    if (ftCo_800A1CA8(fp)) {
        ftCo_800B46B8(fp, 0x80, 0);
        ftCo_800B46B8(fp, 0x81, 0);
        ftCo_800B46B8(fp, 0x8E, 0xA);
        ftCo_800B463C(fp, 8);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 7);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 8);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 0x7F);
    } else {
        ftCo_800B46B8(fp, 0x80, 0);
        ftCo_800B46B8(fp, 0x81, 0);
        ftCo_800B463C(fp, 8);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B46B8(fp, 0x95, 0x7F);
        ftCo_800B463C(fp, 7);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 8);
        ftCo_800B46B8(fp, 0x8E, 5);
        ftCo_800B463C(fp, 0x7F);
    }
}

void ftCo_800A08F0(Fighter* fp)
{
    ftCo_800B46B8(fp, 0x80, 0);
    ftCo_800B46B8(fp, 0x81, 0);
    if (fp->motion_id == ftCo_MS_SquatRv || fp->motion_id == ftCo_MS_Squat || fp->motion_id == ftCo_MS_SquatWait) {
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 0x7F);
        return;
    }
    if (fp->kind == FTKIND_NANA) {
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B46B8(fp, 0x81, 0x81);
        ftCo_800B46B8(fp, 0x8E, 5);
        ftCo_800B46B8(fp, 0x80, 0);
        ftCo_800B46B8(fp, 0x81, 0);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 0x7F);
        return;
    }
    switch (fp->x1A88.x10) {
    case 0:
        ftCo_800B46B8(fp, 0x8E, 0x2D);
        break;
    case 1:
    case 2:
        ftCo_800B46B8(fp, 0x8E, 0x1E);
        break;
    case 3:
    case 4:
        ftCo_800B46B8(fp, 0x8E, 0xF);
        break;
    case 5:
    case 6:
        ftCo_800B46B8(fp, 0x8E, 0xA);
        break;
    case 7:
    case 8:
        ftCo_800B46B8(fp, 0x8E, 5);
        break;
    case 9:
        ftCo_800B46B8(fp, 0x8E, 1);
        break;
    }
    ftCo_800B46B8(fp, 0x81, 0x81);
    ftCo_800B46B8(fp, 0x8E, 5);
    ftCo_800B46B8(fp, 0x80, 0);
    ftCo_800B46B8(fp, 0x81, 0);
    ftCo_800B46B8(fp, 0x8E, 1);
    ftCo_800B463C(fp, 0x7F);
}

void ftCo_800A0AF4(Fighter* fp)
{
    float rand = HSD_Randf();
    if (rand < 0.6f) {
        ftCo_800B46B8(fp, 0x80, 0);
        ftCo_800B46B8(fp, 0x81, 0x50);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B46B8(fp, 0x81, 0);
        ftCo_800B463C(fp, 0x7F);
    } else if (rand < 0.8f) {
        ftCo_800B463C(fp, 0xA);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 9);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 0xA);
        ftCo_800B463C(fp, 0x7F);
    } else if (rand < 0.9f) {
        ftCo_800B463C(fp, 2);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 1);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 2);
        ftCo_800B463C(fp, 0x7F);
    } else {
        ftCo_800B463C(fp, 8);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 7);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 8);
        ftCo_800B463C(fp, 0x7F);
    }
}

void ftCo_800A0C8C(Fighter* fp)
{
    ftCo_800B463C(fp, 127);
}

void ftCo_800A0CB0(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    if (fp->x1A88.x7C % 600 == 0) {
        float x = HSD_Randf();
        float rand;
        x = x * x * x;
        rand = 1.0F - x;
        switch (fp->kind) {
        case FTKIND_DONKEY:
        case FTKIND_KOOPA:
            data->x56C = 9.0 * rand;
            return;
        case FTKIND_GKOOPS:
            data->x56C = 18.0 * rand;
            return;
        case FTKIND_NANA:
            data->x56C = 1.0 * rand;
            return;
        default:
            data->x56C = 4.0 * rand;
            return;
        }
    }
}

void ftCo_800A0DA4(Fighter* fp)
{
    int i;
    FighterHurtCapsule* hurt;
    struct Fighter_x1A88_t* temp_r28;

    float scale;
    float dx;
    float var_f31;
    float var_f30;
    float var_f29;
    float dy;

    temp_r28 = &fp->x1A88;
    var_f30 = var_f31 = var_f29 = 0.0F;
    for (i = 0; i < fp->hurt_capsules_len; i++) {
        hurt = &fp->hurt_capsules[i];
        lbColl_800083C4(&hurt->capsule);

        dx = hurt->capsule.a_pos.x - fp->cur_pos.x;
        dy = hurt->capsule.a_pos.y - fp->cur_pos.y;

        scale = hurt->capsule.scale * fp->x34_scale.y;

        if (var_f31 > dx - scale) {
            var_f31 = dx - scale;
        }
        if (var_f30 < dx + scale) {
            var_f30 = dx + scale;
        }
        if (var_f29 < dy + scale) {
            var_f29 = dy + scale;
        }

        dx = hurt->capsule.b_pos.x - fp->cur_pos.x;
        dy = hurt->capsule.b_pos.y - fp->cur_pos.y;

        if (var_f31 > dx - scale) {
            var_f31 = dx - scale;
        }
        if (var_f30 < dx + scale) {
            var_f30 = dx + scale;
        }
        if (var_f29 < dy + scale) {
            var_f29 = dy + scale;
        }
    }
    if (fp->facing_dir > 0.0) {
        temp_r28->x55C = var_f30;
        temp_r28->x560 = -var_f31;
    } else {
        temp_r28->x55C = -var_f31;
        temp_r28->x560 = var_f30;
    }
    temp_r28->x564 = 0.5 * (temp_r28->x55C + temp_r28->x560);
    temp_r28->x568 = var_f29;
}

bool ftCo_800A0F00(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    struct Fighter_x1A88_t* data = &fp->x1A88;
    if (ft_80087A18(gobj)) {
        int result = ft_80087A80(gobj);
        if (result == 2) {
            return true;
        }
        if (result == 1) {
            if (data->x7C % 240 > 120) {
                return true;
            }
            return false;
        }
        return false;
    }
    return false;
}

bool ftCo_800A0FB0(Vec3* arg0, int* arg1, int arg2, int arg3, int arg4,
                   int arg5, int arg6, float arg7, float arg8, float arg9,
                   float arg10, float arg11)
{
    *arg1 = -1;
    {
        int ret = mpLib_8004F008(arg0, arg1, arg2, arg3, arg4, arg5, arg6, 0,
                                 0, arg7, arg8, arg9, arg10, arg11);
        if (ret && ftCo_800A1B38(*arg1)) {
            return false;
        }
        return ret;
    }
}

/// #ftCo_800A101C

float ftCo_800A17E4(Fighter* fp)
{
    float result;
    if (fp->x1A88.lstickX > 0) {
        result = fp->x1A88.lstickX / 127.0F;
    } else {
        result = fp->x1A88.lstickX / 128.0F;
    }
    if (result > 1.0) {
        return 1.0;
    } else if (result < -1.0) {
        return -1.0;
    }
    return result;
}

static inline float inlineB0(s8 val, float a, float b)
{
    float ret = val > 0 ? val / a : val / b;
    return ret > +1.0 ? +1.0F : ret < -1.0 ? -1.0F : ret;
}

float ftCo_800A1874(Fighter* fp)
{
    return inlineB0(fp->x1A88.lstickY, 127.0f, 128.0F);
}

float ftCo_800A1904(Fighter* fp)
{
    float ret = fp->x1A88.x8 / 255.0;
    return ret > 1.0 ? 1.0F : ret;
}

float ftCo_800A1948(Fighter* fp)
{
    float ret = fp->x1A88.rtrigger / 255.0;
    return ret > 1.0 ? 1.0F : ret;
}

HSD_Pad ftCo_800A198C(Fighter* fp)
{
    return fp->x1A88.x0;
}

float ftCo_800A1994(Fighter* fp)
{
    return inlineB0(fp->x1A88.x6, 127.0F, 128.0F);
}

float ftCo_800A1A24(Fighter* fp)
{
    return inlineB0(fp->x1A88.x7, 127.0F, 128.0F);
}

/// Compute 2D distance between two fighters
f32 ftCo_800A1AB4(Fighter* fp0, Fighter* fp1)
{
    float dx = fp0->cur_pos.x - fp1->cur_pos.x;
    float dy = fp0->cur_pos.y - fp1->cur_pos.y;
    return sqrtf(SQ(dx) + SQ(dy));
}

bool ftCo_800A1B38(enum_t arg0)
{
    if (grBigBlue_801EF844(arg0) || grInishie1_801FCAAC(arg0) ||
        grCorneria_801E2D90(arg0) || grVenom_80206D10(arg0))
    {
        return true;
    }
    return false;
}

bool ftCo_800A1BA8(Fighter* fp)
{
    Fighter* other_fp = fp->x1A88.x44;
    if (other_fp == NULL) {
        return false;
    }
    {
        Vec3 coll_vec;
        PAD_STACK(2 * 4);
        {
            UNK_T sp14;
            UNK_T sp10;
            UNK_T spC;
            if (fp->facing_dir > 0.0) {
                return mpLib_800509B8(fp->cur_pos.x, fp->cur_pos.y,
                                      other_fp->cur_pos.x, other_fp->cur_pos.y,
                                      &coll_vec, &sp10, &spC, &sp14, -1, -1);
            }
            return mpLib_800501CC(fp->cur_pos.x, fp->cur_pos.y,
                                  other_fp->cur_pos.x, other_fp->cur_pos.y,
                                  &coll_vec, &sp10, &spC, &sp14, -1, -1);
        }
    }
}

bool ftCo_800A1C44(Fighter* fp)
{
    if (fp->x2219_b1) {
        return true;
    }
    if (fp->x2164 != 0) {
        return true;
    }
    if (fp->x2168 != 0 && fp->x2338.x == 0) {
        return true;
    }
    if (fp->x221F_b3) {
        return true;
    }
    return false;
}

bool ftCo_800A1CA8(Fighter* fp)
{
    return fp->x2168 ? true : false;
}

/// #ftCo_800A1CC4

void ftCo_800A1F3C(Fighter* fp, float arg1, float arg2, float arg3)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    if (fp->x1A88.x60 == 0) {
        data->x54.x = arg1;
        data->x54.y = arg2;
        data->x38 = arg3;
        ftCo_800A1CC4(fp, ftCo_803C6594[stage_info.internal_stage_id]);
    }
}

bool ftCo_800A1F98(int x, float y)
{
    float slope;
    float intercept;
    PAD_STACK(1 * 4);

    if (stage_info.internal_stage_id != ZEBES) {
        return false;
    }
    Ground_801C4368(&slope, &intercept);
    if (y < slope) {
        return true;
    }
    if (y < intercept * x + slope) {
        return true;
    }
    return false;
}

bool ftCo_800A2040(Fighter* fp)
{
    if (Player_8003248C(fp->player_id, fp->x221F_b4) != Gm_PKind_Cpu) {
        return false;
    }
    if (fp->x1A88.xC == 5) {
        return false;
    }
    return true;
}

void ftCo_800A20A0(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    PAD_STACK(2 * 4);

    if (fp->x1A88.x44 != NULL && fp->ground_or_air == GA_Ground) {
        Fighter* other_fp = data->x44;

        if (ftCo_800A1AB4(fp, other_fp) <
            2.0f * M2C_FIELD(Fighter_804D64FC, float**, 0x20)[fp->kind])
        {
            data->xF8_b6 = true;
        } else {
            data->xF8_b6 = false;
        }
    } else {
        data->xF8_b6 = false;
    }
}

bool ftCo_800A2170(Fighter* fp0, Fighter* fp1)
{
    mp_UnkStruct0* temp_r3;

    if (fp0->ground_or_air == GA_Air) {
        return false;
    }
    if (fp1->ground_or_air == GA_Air) {
        return false;
    }
    temp_r3 = mpIsland_8005AB54(fp0->coll_data.floor.index);
    if (temp_r3 == NULL) {
        return false;
    }
    if (mpIsland_8005AB54(fp1->coll_data.floor.index) == temp_r3) {
        return true;
    }
    return false;
}

bool ftCo_800A21FC(Fighter* fp)
{
    Vec3 vec;
    mp_UnkStruct0* data0;
    struct Fighter_x1A88_t* data1 = &fp->x1A88;
    PAD_STACK(9 * 4);

    if (fp->ground_or_air == GA_Air) {
        return false;
    }
    data0 = mpIsland_8005AB54(fp->coll_data.floor.index);
    if (data0 == NULL) {
        return false;
    }
    vec.x = data1->x54.x;
    vec.y = 5.0 + data1->x54.y;
    vec.z = 0.0f;
    if (mpIsland_8005AC14(&vec, -10.0f) == data0) {
        return true;
    }
    return false;
}

/// #ftCo_800A229C

static inline bool inlineL0(mp_UnkStruct0* arg0)
{
    Item_GObj* cur;
    s32 temp_cr0_eq;
    s32 var_r0;
    Item* cur_ip;
    cur = HSD_GObj_Entities->items;
    goto loop_8;
block_3:
    cur_ip = GET_ITEM(cur);
    if (it_8026C1B4(cur) == 0) {
        goto block_7;
    }
    if (!ftCo_800A5944(cur_ip)) {
        goto block_7;
    }
    if (arg0 != mpIsland_8005AB54(cur_ip->x378_itemColl.floor.index)) {
        goto block_7;
    }
    return 1;
block_7:
    cur = cur->next;
loop_8:
    if (cur != NULL) {
        goto block_3;
    }
    if (stage_info.internal_stage_id == STORY) {
        goto block_15;
    }
    if (stage_info.internal_stage_id >= 0xA) {
        goto block_13;
    }
    if (stage_info.internal_stage_id == ZEBES) {
        goto block_16;
    }
    goto block_37;
block_13:
    temp_cr0_eq = stage_info.internal_stage_id == ONETT;
    if (temp_cr0_eq != 0) {
        goto block_21;
        goto block_37;
    block_15:
        return mpIsland_8005AC8C(arg0);
    block_16:
        if (ftCo_800A1F98(0x5A, arg0->x18) != 0) {
            return 1;
        }
        if (ftCo_800A1F98(0x5A, arg0->xC) != 0) {
            return 1;
        }
        return 0;
    }
block_21:
    if (temp_cr0_eq == 0) {
        return 0;
    }
    if (arg0->x18 <= 5.0 || Ground_801C5794() == 0) {
        return 0;
    }
    return 1;
block_37:
    return 0;
}

static inline bool inlineL1(mp_UnkStruct0* arg0)
{
    if (stage_info.internal_stage_id != ONETT) {
        return false;
    }
    if (!(arg0->xC <= 5.0)) {
        if (Ground_801C5794() != 0) {
            return true;
        }
    }
    return false;
}

bool ftCo_800A2718(mp_UnkStruct0* arg0)
{
    PAD_STACK(4 * 4);
    if (arg0 == NULL) {
        return 0;
    }
    if (!inlineL0(arg0) && !inlineL1(arg0)) {
        return 0;
    }
    return 1;
}

bool ftCo_800A28D0(Fighter* fp, float arg1)
{
    if (fp->ground_or_air == GA_Air) {
        return false;
    }
    {
        mp_UnkStruct0* data = mpIsland_8005AB54(fp->coll_data.floor.index);
        if (data == NULL) {
            return false;
        }
        {
            float x_offset;
            if (fp->facing_dir > 0.0) {
                x_offset = ABS(data->x14 - fp->cur_pos.x);
            } else {
                x_offset = ABS(data->x8 - fp->cur_pos.x);
            }
            if (x_offset < (5.0 * arg1)) {
                return true;
            }
        }
    }
    return false;
}

bool ftCo_800A2998(Fighter* fp, float arg1)
{
    if (fp->ground_or_air == GA_Air) {
        return false;
    }
    {
        mp_UnkStruct0* data = mpIsland_8005AB54(fp->coll_data.floor.index);
        if (data == NULL) {
            return false;
        }
        {
            float diff_x8, diff_x14;
            diff_x14 = ABS(data->x14 - fp->cur_pos.x);
            diff_x8 = ABS(data->x8 - fp->cur_pos.x);
            if (diff_x14 < diff_x8) {
                if (diff_x14 < 5.0 * arg1) {
                    return true;
                }
                return false;
            }
            if (diff_x8 < 5.0 * arg1) {
                return true;
            }
        }
    }
    return false;
}

float ftCo_800A2A70(Fighter* fp, bool arg1)
{
    if (fp->ground_or_air == GA_Air) {
        return -1.0f;
    }
    {
        mp_UnkStruct0* data = mpIsland_8005AB54(fp->coll_data.floor.index);
        if (data == NULL) {
            return -1.0f;
        }
        {
            float r;
            if (arg1) {
                float x = data->x8 - fp->cur_pos.x,
                      y = data->xC - fp->cur_pos.y;
                r = sqrtf(SQ(x) + SQ(y));
            } else {
                float x = data->x14 - fp->cur_pos.x,
                      y = data->x18 - fp->cur_pos.y;
                r = sqrtf(SQ(x) + SQ(y));
            }
            return r;
        }
    }
}

bool ftCo_800A2BD4(Fighter* fp)
{
    return fp->facing_dir * (fp->x1A88.x54.x - fp->cur_pos.x) >= 0.0 ? true
                                                                     : false;
}

bool ftCo_800A2C08(Fighter* fp)
{
    Fighter* other_fp = fp->x1A88.x44;
    if (other_fp == NULL) {
        return true;
    }
    {
        float pos_x_diff = other_fp->cur_pos.x - fp->cur_pos.x;
        if (ABS(pos_x_diff) < 1.0f) {
            return true;
        }
        if (pos_x_diff * fp->facing_dir >= 0.0) {
            return true;
        }
        return false;
    }
}

/// #ftCo_800A2C80

enum_t ftCo_800A3134(Fighter* fp)
{
    switch (fp->motion_id) {
    case ftCo_MS_DownBoundD:
    case ftCo_MS_DownBoundU:
        return 1;
    case ftCo_MS_DownWaitD:
    case ftCo_MS_DownWaitU:
        return 2;
    default:
        return 0;
    }
}

bool ftCo_IsGrabbing(Fighter* fp)
{
    if (fp->motion_id == ftCo_MS_CatchWait) {
        return true;
    }
    if (fp->kind == FTKIND_DONKEY) {
        if (fp->motion_id >= ftDk_MS_ThrowFWait0 &&
            fp->motion_id <= ftDk_MS_ThrowFKneebend)
        {
            return true;
        }
    }
    if (fp->kind == FTKIND_KOOPA || fp->kind == FTKIND_GKOOPS) {
        if (fp->motion_id == ftKp_MS_SpecialSHit0_1) {
            return true;
        }
    }
    if (fp->kind == FTKIND_KIRBY) {
        if (fp->motion_id >= ftKb_MS_SpecialNCapture0 &&
            fp->motion_id <= ftKb_MS_EatTurnAir)
        {
            return true;
        }
    }
    return false;
}

bool ftCo_800A3200(Fighter* fp)
{
    switch (fp->motion_id) {
    case ftCo_MS_CliffCatch:
        return 1;
    case ftCo_MS_CliffWait:
        return 2;
    default:
        return 0;
    }
}

/// #ftCo_800A3234

static inline bool inlineC0(Fighter* fp)
{
    if (fp->coll_data.env_flags & MPCOLL_WALL) {
        return true;
    } else {
        return false;
    }
}

bool ftCo_800A3498(Fighter* fp)
{
    struct Fighter_x1A88_t* temp_r4 = &fp->x1A88;
    if (fp->x1A88.xFA_b5) {
        return false;
    }
    if (fp->ground_or_air != GA_Air) {
        return false;
    }
    if (fp->pos_delta.y > 0.0) {
        return false;
    }
    if (inlineC0(fp)) {
        return true;
    }
    if (fp->kind == FTKIND_LUIGI) {
        if (fp->pos_delta.y < 0.0) {
            return true;
        }
    } else if (temp_r4->x54.y >
               temp_r4->x568 + (fp->coll_data.cur_topn.y +
                                fp->coll_data.xA4_ecbCurrCorrect.bottom.y))
    {
        return true;
    }
    return false;
}

bool ftCo_800A3554(Fighter* fp, float arg1)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    if (fp->ground_or_air == GA_Air) {
        return false;
    }
    if (!ftCo_800A21FC(fp)) {
        return false;
    }
    {
        float x = data->x54.x - fp->cur_pos.x, y = data->x54.y - fp->cur_pos.y;
        if (sqrtf(SQ(x) + SQ(y)) < data->x38 + arg1) {
            if (data->x60 != 0) {
                data->x60 = 0;
                data->x54.x = data->x64.x;
                data->x54.y = data->x64.y;
                ftCo_800A1CC4(fp, ftCo_803C6594[stage_info.internal_stage_id]);
                return false;
            }
            return true;
        }
        return false;
    }
}

/**
 * This appears to be similar to ftCo_800A2170, but for fighter/item args.
 */
static inline bool ftCo_800A2170_it(Fighter* fp, Item* ip)
{
    mp_UnkStruct0* data;
    if (fp->ground_or_air == GA_Air) {
        return false;
    }
    if (ip->ground_or_air == GA_Air) {
        return false;
    }
    data = mpIsland_8005AB54(fp->coll_data.floor.index);
    if (data == NULL) {
        return false;
    }
    if (mpIsland_8005AB54(ip->x378_itemColl.floor.index) == data) {
        return true;
    }
    return false;
}

bool ftCo_800A3710(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    Item* ip = data->x4C;
    if (!data->xF9_b7) {
        return false;
    }
    if (ip == NULL) {
        return false;
    }
    if (!Item_IsGrabbable(ip->entity)) {
        data->x4C = NULL;
        return false;
    }
    if (fp->ground_or_air == GA_Air) {
        return false;
    }
    if (fp->item_gobj != NULL) {
        return false;
    }
    if (!ftCo_800A2170_it(fp, ip)) {
        return false;
    }
    if (ftpickupitem_80094150(fp->gobj, ip->entity)) {
        return true;
    }
    return false;
}

bool ftCo_IsAlly(Fighter* fp0, Fighter* fp1)
{
    if (fp0 == NULL) {
        return false;
    }
    if (fp1 == NULL) {
        return false;
    }
    if (fp0->player_id == fp1->player_id) {
        return true;
    }
    if (gm_8016B168()) {
        if (fp0->team == fp1->team) {
            return true;
        }
        return false;
    }
    if (gm_8016B14C()) {
        return false;
    }
    if (fp0->team == fp1->team) {
        return true;
    }
    return false;
}

static inline bool ftCo_IsAlly_dontinline(Fighter* fp0, Fighter* fp1)
{
    return ftCo_IsAlly(fp0, fp1);
}

/// #ftCo_800A3908

/// #ftCo_800A4038

/// #ftCo_800A4768

void ftCo_800A49B4(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    f32 dx = fp->cur_pos.x - data->x54.x;
    f32 dy = fp->cur_pos.y - data->x54.y;
    data->x5C = sqrtf(dx * dx + dy * dy);
}

static inline bool inlineD0(Fighter* fp, Fighter* fp1)
{
    float y, x;
    struct Fighter_x1A88_t* data = &fp->x1A88;

    y = fp1->cur_pos.y;
    x = fp1->cur_pos.x;
    if (x < Stage_GetBlastZoneLeftOffset() + data->half_width ||
        x > Stage_GetBlastZoneRightOffset() - data->half_width ||
        y < Stage_GetBlastZoneBottomOffset() + data->half_height ||
        y > Stage_GetBlastZoneTopOffset() - data->half_height)
    {
        return true;
    }
    return false;
}

static inline bool inlineD0_it(Fighter* fp, Item* it)
{
    float y, x;
    struct Fighter_x1A88_t* data = &fp->x1A88;

    y = it->pos.y;
    x = it->pos.x;
    if (x < Stage_GetBlastZoneLeftOffset() + data->half_width ||
        x > Stage_GetBlastZoneRightOffset() - data->half_width ||
        y < Stage_GetBlastZoneBottomOffset() + data->half_height ||
        y > Stage_GetBlastZoneTopOffset() - data->half_height)
    {
        return true;
    }
    return false;
}

static inline bool inlineD1(Fighter* fp)
{
    Fighter_GObj* gobj = fp->gobj;
    if (fp->x221F_b3 || fp->x2224_b2 || ftCo_800A0F00(gobj) ||
        ftLib_8008732C(gobj))
    {
        return true;
    } else {
        return false;
    }
}

Fighter* ftCo_800A4A40(Fighter* fp)
{
    Fighter* fp1;
    Fighter* cur_fp;
    Fighter_GObj* cur;
    float closest;
    float distance;

    PAD_STACK(8);

    if (fp == NULL) {
        return NULL;
    }
    cur_fp = NULL;
    for (cur = HSD_GObj_Entities->fighters; cur != NULL; cur = cur->next) {
        if (fp->gobj == cur) {
            continue;
        }
        fp1 = GET_FIGHTER(cur);
        if (inlineD0(fp, fp1)) {
            continue;
        }
        if (inlineD1(fp1)) {
            continue;
        }
        if (cur_fp == NULL) {
            cur_fp = fp1;
            closest = ftCo_800A1AB4(fp, fp1);
            continue;
        }
        fp1 = GET_FIGHTER(cur);
        distance = ftCo_800A1AB4(fp, fp1);
        if (closest > distance) {
            closest = distance;
            cur_fp = fp1;
        }
    }
    return cur_fp;
}

/// #ftCo_800A4BEC

/// #ftCo_800A4E8C

/// #ftCo_800A50D4

/// Returns the closest enemy fighter
Fighter* ftCo_800A50D4(Fighter* fp)
{
    Fighter* cur_fp;
    Fighter* closest_fp;
    HSD_GObj* cur;

    f32 closest;
    f32 distance;

    PAD_STACK(4);

    if (fp == NULL) {
        return NULL;
    }
    closest_fp = NULL;
    for (cur = HSD_GObj_Entities->fighters; cur != NULL; cur = cur->next) {

        // Ignore self
        if (fp->gobj == cur) {
            continue;
        }

        cur_fp = GET_FIGHTER(cur);

        // Ignore fighters outside the blast zones
        if (inlineD0(fp, cur_fp)) {
            continue;
        }

        // Ignore allies
        if (!ftCo_IsAlly_dontinline(fp, cur_fp)) {
            continue;
        }
        if (inlineD1(cur_fp)) {
            continue;
        }

        if (closest_fp == NULL) {
            closest_fp = cur_fp;
            closest = ftCo_800A1AB4(fp, cur_fp);
        } else {
            cur_fp = GET_FIGHTER(cur);
            distance = ftCo_800A1AB4(fp, cur_fp);
            if (closest > distance) {
                closest = distance;
                closest_fp = cur_fp;
            }
        }
    }
    return closest_fp;
}

Fighter* ftCo_800A5294(Fighter* fp, int player_id)
{
    PAD_STACK(2 * 4);
    if (fp == NULL) {
        return NULL;
    }
    {
        Fighter* cur_fp;
        HSD_GObj* cur;
        for (cur = HSD_GObj_Entities->fighters; cur != NULL; cur = cur->next) {
            if (fp->gobj != cur) {
                cur_fp = GET_FIGHTER(cur);
                if (!inlineD0(fp, cur_fp)) {
                    if (!inlineD1(cur_fp) && cur_fp->player_id == player_id) {
                        return cur_fp;
                    }
                }
            }
        }
    }
    return NULL;
}

Fighter* ftCo_800A53DC(Fighter* fp)
{
    struct Fighter_x1A88_t* temp_r31;
    HSD_GObj* var_r30;
    HSD_GObj* var_r30_2;
    Fighter* temp_r29;
    Fighter* temp_r29_3;
    Fighter* var_r28;
    int var_r27;
    Fighter_GObj* temp_r25;
    Fighter* temp_r25_2;
    Fighter_GObj* temp_r25_3;
    Fighter* temp_r25_4;

    f32 temp_f1_3;
    f32 temp_f1_6;
    f32 var_f31;

    temp_r31 = &fp->x1A88;
    if (fp == NULL) {
        return 0;
    }
    var_r28 = NULL;
    if (temp_r31->xFA_b34) {
        for (var_r30 = HSD_GObj_Entities->fighters; var_r30 != NULL; var_r30 = var_r30->next) {
            if (fp->gobj == var_r30) {
                continue;
            }
            temp_r29 = GET_FIGHTER(var_r30);
            if (inlineD0(fp, temp_r29)) {
                continue;
            }
            if (ftCo_IsAlly_dontinline(fp, temp_r29)) {
                continue;
            }
            if (ftCo_800A1C44(temp_r29)) {
                continue;
            }
            temp_r25 = temp_r29->gobj;
            if (inlineD1(temp_r29)) {
                continue;
            }
            if (ftCo_800A2040(temp_r29)) {
                continue;
            }

            if (var_r28 == NULL) {
                var_r28 = temp_r29;
                var_r27 = gm_8016C6C0(var_r30);
                var_f31 = ftCo_800A1AB4(fp, temp_r29);
            } else {
                int temp_r29_2;
                temp_r25_2 = GET_FIGHTER(var_r30);
                temp_r29_2 = gm_8016C6C0(var_r30);
                temp_f1_3 = ftCo_800A1AB4(fp, temp_r25_2);
                if (var_r27 > temp_r29_2) {
                    var_f31 = temp_f1_3;
                    var_r27 = temp_r29_2;
                    var_r28 = temp_r25_2;
                } else if (var_r27 == temp_r29_2 && var_f31 > temp_f1_3) {
                    var_f31 = temp_f1_3;
                    var_r28 = temp_r25_2;
                }
            }
        }
        if (var_r28 != NULL) {
            return var_r28;
        }
    }
    for (var_r30_2 = HSD_GObj_Entities->fighters; var_r30_2 != NULL; var_r30_2 = var_r30_2->next) {
        if (fp->gobj == var_r30_2) {
            continue;
        }
        temp_r29_3 = GET_FIGHTER(var_r30_2);
        if (inlineD0(fp, temp_r29_3)) {
            continue;
        }
        if (ftCo_IsAlly_dontinline(fp, temp_r29_3)) {
            continue;
        }
        if (ftCo_800A1C44(temp_r29_3)) {
            continue;
        }
        temp_r25_3 = temp_r29_3->gobj;
        if (inlineD1(temp_r29_3)) {
            continue;
        }
        if (var_r28 == NULL) {
            var_r28 = temp_r29_3;
            var_r27 = gm_8016C6C0(var_r30_2);
            var_f31 = ftCo_800A1AB4(fp, temp_r29_3);
        } else {
            int temp_r29_4;
            temp_r25_4 = GET_FIGHTER(var_r30_2);
            temp_r29_4 = gm_8016C6C0(var_r30_2);
            temp_f1_6 = ftCo_800A1AB4(fp, temp_r25_4);
            if (var_r27 > temp_r29_4) {
                var_f31 = temp_f1_6;
                var_r27 = temp_r29_4;
                var_r28 = temp_r25_4;
            } else if (var_r27 == temp_r29_4 && var_f31 > temp_f1_6) {
                var_f31 = temp_f1_6;
                var_r28 = temp_r25_4;
            }
        }
    }
    return var_r28;
}

Fighter* ftCo_800A589C(Fighter* fp)
{
    if (fp == NULL) {
        return NULL;
    }
    {
        Fighter_GObj* cur;
        for (cur = HSD_GObj_Entities->fighters; cur != NULL; cur = cur->next) {
            if (fp->gobj != cur) {
                Fighter* cur_fp = GET_FIGHTER(cur);
                if (fp->player_id == cur_fp->player_id) {
                    if (cur_fp->x221F_b3) {
                        return NULL;
                    }
                    return cur_fp;
                }
            }
        }
    }
    return NULL;
}

bool ftCo_800A5908(Fighter* fp)
{
    if (fp->motion_id == ftCo_MS_DeadUpFallHitCameraFlat) {
        return true;
    }
    if (fp->motion_id == ftCo_MS_DeadUpFallIce) {
        return true;
    }
    if (fp->motion_id == ftCo_MS_Turn) {
        return true;
    }
    return false;
}

bool ftCo_800A5944(Item* ip)
{
    if (ip->kind == It_Kind_BombHei) {
        return true;
    }
    if (ip->kind == It_Kind_G_Shell) {
        return true;
    }
    if (ip->kind == It_Kind_R_Shell) {
        return true;
    }
    return false;
}

bool ftCo_800A5980(Fighter* fp)
{
    if (fp->motion_id >= ftCo_MS_LandingFallSpecial &&
        fp->motion_id < ftCo_MS_Attack100Start)
    {
        return true;
    }
    if (fp->motion_id - (unsigned) ftCo_MS_Furafura <= 2 ||
        fp->motion_id == ftCo_MS_CatchAttack)
    {
        return true;
    }
    return false;
}

bool ftCo_800A59C0(Item* ip)
{
    if (ip->xCC_item_attr->x0_78 == 3) {
        return true;
    }
    return false;
}

bool ftCo_800A59E4(Fighter* fp)
{
    if (fp == NULL) {
        return false;
    }
    if (fp->motion_id == ftCo_MS_KneeBend ||
        fp->motion_id == ftCo_MS_RunDirect ||
        fp->motion_id == ftCo_MS_RunBrake ||
        fp->motion_id == ftCo_MS_Sleep ||
        fp->motion_id == ftCo_MS_Rebirth ||
        fp->motion_id == ftCo_MS_RebirthWait)
    {
        return true;
    }
    return false;
}

bool ftCo_800A5A28(Fighter* fp)
{
    switch (fp->motion_id) {
    case ftCo_MS_DeadDown:
    case ftCo_MS_DeadUpFall:
    case ftCo_MS_DeadUpFallHitCamera:
    case ftCo_MS_Wait:
    case ftCo_MS_WalkSlow:
    case ftCo_MS_WalkFast:
    case ftCo_MS_TurnRun:
    case ftCo_MS_Dash:
    case ftCo_MS_FallAerialB:
        return true;
    default:
        return false;
    }
}

bool ftCo_800A5A5C(Fighter* fp)
{
    switch (fp->motion_id) {
    case ftCo_MS_DeadLeft:
    case ftCo_MS_DeadRight:
    case ftCo_MS_DeadUpStar:
    case ftCo_MS_DeadUpStarIce:
        return true;
    default:
        return false;
    }
}

bool ftCo_800A5A90(Fighter* fp)
{
    if (fp->motion_id >= ftCo_MS_SwordSwing1 &&
        fp->motion_id <= ftCo_MS_StarRodSwingDash)
    {
        return true;
    }
    if (fp->motion_id >= ftCo_MS_LGunShoot &&
        fp->motion_id <= ftCo_MS_ItemScopeAirEndEmpty)
    {
        return true;
    }
    return false;
}

bool ftCo_800A5ACC(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    if (!data->xF9_b6) {
        return false;
    }
    switch (data->x10) {
    case 0:
    case 1:
        return false;
    case 2:
        if (data->x7C % 120 > 0x64) {
            return true;
        }
        return false;
    case 3:
        if (data->x7C % 120 > 0x50) {
            return true;
        }
        return false;
    case 4:
        if (data->x7C % 120 > 0x3C) {
            return true;
        }
        return false;
    case 5:
        if (data->x7C % 120 > 0x28) {
            return true;
        }
        return false;
    case 6:
        if (data->x7C % 120 > 0x1E) {
            return true;
        }
        return false;
    case 7:
        if (data->x7C % 120 > 0x14) {
            return true;
        }
        return false;
    case 8:
        if (data->x7C % 120 > 0xA) {
            return true;
        }
        return false;
    case 9:
        return true;
    }
    return false;
}

Fighter* ftCo_800A5CE0(Fighter* fp)
{
    Fighter* cur_fp;
    Fighter* closest_enemy;
    HSD_GObj* cur;
    bool var_r0_3;

    f32 distance;
    f32 closest;

    PAD_STACK(8);

    if (fp == NULL) {
        return NULL;
    }
    if (ftCo_800A1C44(fp)) {
        return NULL;
    }
    closest_enemy = NULL;
    for (cur = HSD_GObj_Entities->fighters; cur != NULL; cur = cur->next) {
        if (fp->gobj == cur) {
            continue;
        }
        cur_fp = GET_FIGHTER(cur);
        if (inlineD1(cur_fp)) {
            continue;
        }
        if (cur_fp->x221D_b6) {
            var_r0_3 = true;
        } else if (cur_fp->x2168 != 0 && cur_fp->x2338.x == 0) {
            var_r0_3 = true;
        } else {
            var_r0_3 = false;
        }
        if (!var_r0_3) {
            continue;
        }
        if (ftCo_IsAlly_dontinline(fp, cur_fp)) {
            continue;
        }
        if (inlineD0(fp, cur_fp)) {
            continue;
        }
        if (closest_enemy == NULL) {
            closest_enemy = cur_fp;
            closest = ftCo_800A1AB4(fp, cur_fp);
        } else {
            distance = ftCo_800A1AB4(fp, cur_fp);
            if (closest > distance) {
                closest = distance;
                closest_enemy = cur_fp;
            }
        }
    }
    return closest_enemy;
}

static inline float itemDist(Fighter* fp, Item* ip)
{
    float dx, dy;
    if (ip == NULL) {
        return 10000.0F;
    }
    dx = fp->cur_pos.x - ip->pos.x;
    dy = fp->cur_pos.y - ip->pos.y;
    return sqrtf(dx * dx + dy * dy);
}

/// Decide which common item to target
Item* ftCo_800A5F4C(Fighter* fp, ItemKind arg1)
{
    Item* cur_ip;
    Item* closest_ip;
    Item_GObj* cur;
    struct Fighter_x1A88_t* data;

    f32 closest;
    f32 distance;

    data = &fp->x1A88;
    if (fp == NULL) {
        return NULL;
    }
    closest_ip = NULL;
    for (cur = HSD_GObj_Entities->items; cur != NULL; cur = cur->next) {

        /// @todo stupid stack padding hack
        cur_ip = GET_ITEM(cur);
        cur_ip = GET_ITEM(cur);
        cur_ip = GET_ITEM(cur);

        if (!Item_IsGrabbable(cur)) {
            continue;
        }

        /// Passing It_Kind_L_Gun_Ray means to target any common item
        if (arg1 != It_Kind_L_Gun_Ray && cur_ip->kind != arg1) {
            continue;
        }
        if (inlineD0_it(fp, cur_ip)) {
            continue;
        }
        if (cur_ip->kind >= It_Kind_L_Gun_Ray) {
            continue;
        }
        if (ftCo_803C5A68[cur_ip->kind] < data->x2C) {
            continue;
        }

        /// If we don't have a target yet, just pick the first item,
        /// and remember its distance.
        if (closest_ip == NULL) {
            closest_ip = cur_ip;
            closest = itemDist(fp, cur_ip);
            continue;
        }

        /// Skip items with lower priority than the current one
        if (ftCo_803C5A68[cur_ip->kind] < ftCo_803C5A68[closest_ip->kind]) {
            continue;
        }

        distance = itemDist(fp, cur_ip);
        if (closest > distance) {
            closest = distance;
            closest_ip = cur_ip;
        }
    }
    return closest_ip;
}

/// #ftCo_800A61D8

/// #ftCo_800A648C

/// #ftCo_800A6700

/// #ftCo_800A6A98

/// #ftCo_800A6D2C

/// #ftCo_800A6FC4

/// #ftCo_800A75DC

/// #ftCo_800A7AAC

void ftCo_800A80E4(Fighter* fp)
{
    Fighter* other_fp = fp->x1A88.x44;
    if (other_fp != NULL && fp->ground_or_air != GA_Air) {
        f32 dx = fp->cur_pos.x - other_fp->cur_pos.x;
        f32 dy = fp->cur_pos.y - other_fp->cur_pos.y;
        Vec3 vec;
        if (!(sqrtf(dx * dx + dy * dy) > 50.0) &&
            ftCo_800A6700(fp, &other_fp->cur_pos, &vec))
        {
            ftCo_800A1F3C(fp, vec.x, vec.y, 5.0F);
        }
    }
}

/// #ftCo_800A8210

/// #ftCo_800A866C

/// #ftCo_800A8940

void ftCo_800A8DE4(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    PAD_STACK(0x20);
    if (!fp->x1A88.xFA_b2) {
        data->xFA_b2 = true;
        data->x5C = 10000.0f;
        if (fp->facing_dir > 0.0) {
            if (!ftCo_800A4038(fp, true) && !ftCo_800A3908(fp, true)) {
                ftCo_800A4038(fp, false);
            }
        } else if (!ftCo_800A3908(fp, true) && !ftCo_800A4038(fp, true)) {
            ftCo_800A3908(fp, false);
        }
    }
}

static inline int angle_x_units(float angle)
{
    return 127.0F * cosf(angle);
}

static inline int angle_y_units(float angle)
{
    return 127.0F * sinf(angle);
}

void ftCo_800A8EB0(Fighter* fp)
{
    float angle;

    struct Fighter_x1A88_t* data = &fp->x1A88;
    if (fp->x1A88.x10 < 9) {
        ftCo_800B463C(fp, 0x7F);
        return;
    }
    ftCo_800B46B8(fp, 0x81, 0x7F);
    ftCo_800B46B8(fp, 0x80, 0);
    ftCo_800B46B8(fp, 0x88, 1);
    ftCo_800B463C(fp, 4);
    if (data->x54.x - fp->cur_pos.x > 0.0) {
        angle = M_PI;
        ftCo_800B46B8(fp, 0x80, angle_x_units(angle));
        ftCo_800B46B8(fp, 0x81, angle_y_units(angle));
        ftCo_800B46B8(fp, 0x8E, 0x14);

        angle = -M_PI_2;
        ftCo_800B46B8(fp, 0x80, angle_x_units(angle));
        ftCo_800B46B8(fp, 0x81, angle_y_units(angle));
        ftCo_800B46B8(fp, 0x8E, 0x23);

        angle = 0.0F;
        ftCo_800B46B8(fp, 0x80, angle_x_units(angle));
        ftCo_800B46B8(fp, 0x81, angle_y_units(angle));
        ftCo_800B46B8(fp, 0x8E, 0x14);

        angle = M_PI_2;
        ftCo_800B46B8(fp, 0x80, angle_x_units(angle));
        ftCo_800B46B8(fp, 0x81, angle_y_units(angle));
        ftCo_800B46B8(fp, 0x8E, 0x14);
    } else {
        angle = 0.0F;
        ftCo_800B46B8(fp, 0x80, angle_x_units(angle));
        ftCo_800B46B8(fp, 0x81, angle_y_units(angle));
        ftCo_800B46B8(fp, 0x8E, 0x14);

        angle = -M_PI_2;
        ftCo_800B46B8(fp, 0x80, angle_x_units(angle));
        ftCo_800B46B8(fp, 0x81, angle_y_units(angle));
        ftCo_800B46B8(fp, 0x8E, 0x23);

        angle = M_PI;
        ftCo_800B46B8(fp, 0x80, angle_x_units(angle));
        ftCo_800B46B8(fp, 0x81, angle_y_units(angle));
        ftCo_800B46B8(fp, 0x8E, 0x14);

        angle = M_PI_2;
        ftCo_800B46B8(fp, 0x80, angle_x_units(angle));
        ftCo_800B46B8(fp, 0x81, angle_y_units(angle));
        ftCo_800B46B8(fp, 0x8E, 0x14);
    }
    ftCo_800B463C(fp, 0x7F);
}

static inline float inverseInlineE0(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    f32 cur_pos_x = fp->cur_pos.x;
    if (cur_pos_x - data->x54.x < 0.0f) {
        return -(cur_pos_x - data->x54.x);
    } else {
        return cur_pos_x - data->x54.x;
    }
}

static inline float inlineE0(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    if (data->x54.x - fp->cur_pos.x < 0.0f) {
        return -(data->x54.x - fp->cur_pos.x);
    } else {
        return data->x54.x - fp->cur_pos.x;
    }
}

void ftCo_800A92CC(Fighter* fp)
{
    if (inverseInlineE0(fp) > 60.0) {
        ftCo_800B46B8(fp, 0x81, 0x7F);
        ftCo_800B46B8(fp, 0x80, 0);
        ftCo_800B46B8(fp, 0x88, 1);
        ftCo_800B463C(fp, 4);
        ftCo_800B46B8(fp, 0x81, 0x58);
        ftCo_800B46B8(fp, 0x90, 0x58);
        ftCo_800B46B8(fp, 0x8E, 0xF);
        ftCo_800B46B8(fp, 0x90, 0x7F);
        ftCo_800B46B8(fp, 0x81, 0);
        ftCo_800B46B8(fp, 0x8E, 0xF);
        ftCo_800B463C(fp, 0x7F);
        return;
    }
    ftCo_800B46B8(fp, 0x81, 0x7F);
    ftCo_800B46B8(fp, 0x80, 0);
    ftCo_800B46B8(fp, 0x88, 1);
    ftCo_800B463C(fp, 4);
    ftCo_800B46B8(fp, 0x8E, 0xF);
    if (HSD_Randf() > 0.5) {
        ftCo_800B46B8(fp, 0x90, 0x58);
        ftCo_800B46B8(fp, 0x81, 0x58);
    } else {
        ftCo_800B46B8(fp, 0x90, 0x7F);
        ftCo_800B46B8(fp, 0x81, 0);
    }
    ftCo_800B46B8(fp, 0x8E, 0xF);
    ftCo_800B463C(fp, 0x7F);
}

void ftCo_800A949C(Fighter* fp)
{
    if (inlineE0(fp) > 30.0) {
        ftCo_800B46B8(fp, 0x80, 0);
        ftCo_800B46B8(fp, 0x81, 0);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B46B8(fp, 0x81, 0x7F);
        ftCo_800B46B8(fp, 0x90, 0x7F);
        ftCo_800B46B8(fp, 0x88, 0x28);
        ftCo_800B46B8(fp, 0x81, 0);
        ftCo_800B46B8(fp, 0x80, 0);
        ftCo_800B463C(fp, 4);
        ftCo_800B46B8(fp, 0x8E, 1);
    } else {
        ftCo_800B46B8(fp, 0x80, 0);
        ftCo_800B46B8(fp, 0x81, 0);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B46B8(fp, 0x81, 0x7F);
        ftCo_800B46B8(fp, 0x80, 0);
        ftCo_800B46B8(fp, 0x88, 0x28);
        ftCo_800B46B8(fp, 0x81, 0);
        ftCo_800B463C(fp, 4);
        ftCo_800B46B8(fp, 0x8E, 1);
    }
    ftCo_800B463C(fp, 0x7F);
}

void ftCo_800A963C(Fighter* fp)
{
    PAD_STACK(4 * 14);
    ftCo_800B46B8(fp, 0x81, 0x58);
    ftCo_800B46B8(fp, 0x90, 0x58);
    ftCo_800B46B8(fp, 0x88, 1);
    ftCo_800B463C(fp, 4);
    ftCo_800B46B8(fp, 0x90, 0x7F);
    ftCo_800B463C(fp, 0x7F);
}

#pragma push
#pragma dont_inline on
void ftCo_800A96B8(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    u32 temp_r0;

    if (fp->x1A88.x54.y > fp->coll_data.cur_topn.y + fp->coll_data.xA4_ecbCurrCorrect.bottom.y) {
        return;
    }
    switch (fp->kind) {
    case 0:
        ftCo_800B46B8(fp, 0x81, 0x58);
        ftCo_800B46B8(fp, 0x90, 0x58);
        ftCo_800B46B8(fp, 0x88, 1);
        ftCo_800B463C(fp, 4);
        ftCo_800B46B8(fp, 0x90, 0x7F);
        ftCo_800B463C(fp, 0x7F);
        return;
    case 12:
    case 23:
        ftCo_800A92CC(fp);
        return;
    case 1:
    case 22:
        ftCo_800B46B8(fp, 0x81, 0x58);
        ftCo_800B46B8(fp, 0x90, 0x58);
        ftCo_800B46B8(fp, 0x88, 1);
        ftCo_800B463C(fp, 4);
        ftCo_800B46B8(fp, 0x8E, 0x28);
        ftCo_800B463C(fp, 0x7F);
        return;
    case 14:
        ftCo_800B463C(fp, 0x7F);
        return;
    case 8:
        if (fp->cur_pos.y > data->x54.y - 10.0) {
            ftCo_800B463C(fp, 0x7F);
        } else {
            ftCo_800A8EB0(fp);
        }
        return;
    case 17:
        ftCo_800B46B8(fp, 0x81, 0);
        ftCo_800B46B8(fp, 0x90, 0x7F);
        ftCo_800B46B8(fp, 0x88, 1);
        ftCo_800B463C(fp, 4);
        ftCo_800B46B8(fp, 0x8E, 0x28);
        ftCo_800B463C(fp, 0x7F);
        return;
    case 19:
        ftCo_800A949C(fp);
        return;
    case 13:
        ftCo_800A963C(fp);
        return;
    default:
        ftCo_800B46B8(fp, 0x81, 0x58);
        ftCo_800B46B8(fp, 0x90, 0x58);
        ftCo_800B46B8(fp, 0x88, 1);
        ftCo_800B463C(fp, 4);
        ftCo_800B46B8(fp, 0x90, 0x7F);
        ftCo_800B463C(fp, 0x7F);
        return;
    }
}
#pragma pop

/// #ftCo_800A9904

/// #ftCo_800A9CB4

void ftCo_800AA320(Fighter* fp, int* arg1, int* arg2)
{
    if (fp->kind == FTKIND_NANA) {
        *arg1 = 0x40;
        *arg2 = 0x7F;
        return;
    }
    switch (fp->x1A88.x10) {
    case 0:
        *arg1 = 1;
        *arg2 = 0x43;
        return;
    case 1:
        *arg1 = 2;
        *arg2 = 0x48;
        return;
    case 2:
        *arg1 = 2;
        *arg2 = 0x4D;
        return;
    case 3:
        *arg1 = 2;
        *arg2 = 0x52;
        return;
    case 4:
        *arg1 = 2;
        *arg2 = 0x57;
        return;
    case 5:
        *arg1 = 2;
        *arg2 = 0x5C;
        return;
    case 6:
        *arg1 = 4;
        *arg2 = 0x61;
        return;
    case 7:
        *arg1 = 4;
        *arg2 = 0x6B;
        return;
    case 8:
        *arg1 = 8;
        *arg2 = 0x75;
        return;
    case 9:
        *arg1 = 8;
        *arg2 = 0x7F;
        return;
    }
}

/// #ftCo_800AA42C

/// #ftCo_800AA844

static inline bool inlineF0(Fighter* fp)
{
    if (fp->motion_id == ftCo_MS_Ottotto ||
        fp->motion_id == ftCo_MS_OttottoWait)
    {
        return true;
    }
    return false;
}

void ftCo_800AABC8(Fighter* fp)
{
    PAD_STACK(2 * 4);
    if (inlineF0(fp)) {
        ftCo_800B46B8(fp, 0x81, 0);
        ftCo_800B46B8(fp, 0x80, 0);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B46B8(fp, 0x91, 0x7F);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B46B8(fp, 0x80, 0);
        ftCo_800B463C(fp, 0x7F);
    } else {
        int a, b;
        ftCo_800AA320(fp, &a, &b);
        ftCo_800B46B8(fp, 0x81, 0);
        ftCo_800B4778(fp, 0xC2, a & 0xFF, b & 0xFF);
        ftCo_800B463C(fp, 0x7F);
    }
}

/// #ftCo_800AACD0

/// #ftCo_800AAF48

/// #ftCo_800AB224

void ftCo_800ABA34(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    if (fp->x1A88.xC == 11) {
        if (fp->item_gobj == NULL) {
            ftCo_800B4880(fp, 38);
            return;
        }
    } else if (data->xC == 12) {
        if (data->x7C % 30 == 0) {
            ftCo_800B4880(fp, 38);
            return;
        }
    } else if (data->xC == 16 && fp->ground_or_air == GA_Ground &&
               data->x7C % 300 == 0)
    {
        ftCo_800A05F4(fp);
        return;
    }
    if ((fp->kind == FTKIND_ZELDA || fp->kind == FTKIND_SEAK) && data->xF8_b5)
    {
        ftCo_800B4880(fp, 38);
        data->xF8_b5 = false;
        return;
    }
    if (ftCo_800A5CE0(fp) == NULL && fp->motion_id == ftCo_MS_RebirthWait) {
        ftCo_800A08F0(fp);
        return;
    }
    if (fp->ground_or_air == GA_Air) {
        ftCo_800A9CB4(fp);
        return;
    }
    ftCo_800AB224(fp);
}

/// #ftCo_800ABBA8

static inline bool inlineG0(Fighter* fp)
{
    enum_t temp_r0 = fp->motion_id;
    bool ret;
    if (temp_r0 == 224) {
        ret = 1;
    } else if (temp_r0 == 227) {
        ret = 1;
    } else if ((temp_r0 >= 266) && (temp_r0 <= 270)) {
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}

void ftCo_800AC30C(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    PAD_STACK(4 * 4);
    if (!inlineG0(fp)) {
        data->x18 = data->x1C;
        ftCo_800B463C(fp, 0x7F);
        return;
    }
    if (data->x7C % 3 == 0 && !(data->x10 * 0.1F < HSD_Randf())) {
        if (fp->x1A88.lstickX < 0) {
            ftCo_800B46B8(fp, 0x80, 0x7F);
        } else {
            ftCo_800B46B8(fp, 0x80, 0x81);
        }
        ftCo_800B463C(fp, 0x7F);
    }
}

static inline enum_t inlineH0(Fighter* fp)
{
    if (fp->motion_id == ftCo_MS_BarrelWait) {
        return 1;
    }
    if (fp->motion_id == ftCo_MS_Barrel) {
        return 2;
    }
    return 0;
}

static inline void inlineH1(Fighter* fp, struct Fighter_x1A88_t* data)
{
    if (data->x7C % ((10 - data->x10) * 5) == 0 && HSD_Randf() < 0.5f) {
        ftCo_800B463C(fp, 1);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 2);
        ftCo_800B463C(fp, 0x7F);
    } else {
        ftCo_800B463C(fp, 0x7F);
    }
}

void ftCo_800AC434(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    Vec3 vec;
    float f;
    enum_t barrel_state = inlineH0(fp);
    PAD_STACK(5 * 4);

    if (barrel_state == 0) {
        data->x18 = data->x1C;
        ftCo_800B463C(fp, 0x7F);
        return;
    }
    if (barrel_state == 1) {
        PAD_STACK(1 * 4);
        Ground_801C4DA0(&vec, &f);
    } else {
        inlineH1(fp, data);
        return;
    }
    if (f >= -0.26179938577115536 && f <= 0.0) {
        ftCo_800B463C(fp, 1);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 2);
        ftCo_800B463C(fp, 0x7F);
    } else {
        ftCo_800B463C(fp, 0x7F);
    }
}

/// #ftCo_800AC5A0

/// #ftCo_800AC7D4

/// #ftCo_800ACB44

/// #ftCo_800ACD5C

void ftCo_800AD42C(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    if (!ftCo_800A3554(fp, 1.0f)) {
        data->x18 = data->x1C;
        ftCo_800B463C(fp, 0x7F);
        return;
    }
    if (fp->ground_or_air == GA_Air) {
        ftCo_800B46B8(fp, 0x80, 0);
        ftCo_800B46B8(fp, 0x81, 0);
        ftCo_800B463C(fp, 0x7F);
        return;
    }
    ftCo_800B46B8(fp, 0x80, 0);
    ftCo_800B46B8(fp, 0x81, 0);
    ftCo_800B463C(fp, 8);
    ftCo_800B46B8(fp, 0x8E, 1);
    ftCo_800B463C(fp, 7);
    ftCo_800B46B8(fp, 0x8E, p_ftCommonData->x74 + 1);
    ftCo_800B463C(fp, 8);
    ftCo_800B46B8(fp, 0x8E, 5);
    ftCo_800B463C(fp, 0x7F);
}

/// #ftCo_800AD54C

/// #ftCo_800AD7FC

/// #ftCo_800ADC28

/// #ftCo_800ADE48

/// #ftCo_800AE7AC

/// #ftCo_800AEA8C

/// #ftCo_800AECF0

/// #ftCo_800AEFB8

/// #ftCo_800AF290

/// #ftCo_800AF78C

static inline bool inlineI1(struct Fighter_x1A88_t* data)
{
    if (data->x18 != data->x20 && data->x18 != data->x1C) {
        data->x60 = 0;
    }
    if (data->x18 == 4) {
        return false;
    } else {
        data->xFA_b2 = false;
        return true;
    }
}

static inline bool inlineI1_alt(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    if (data->x18 != data->x20 && data->x18 != data->x1C) {
        data->x60 = 0;
    }
    if (data->x18 == 4) {
        return false;
    } else {
        data->xFA_b2 = false;
        return true;
    }
}

static inline bool inlineI2(Item_GObj* gobj)
{
    ItemKind temp_r0 = GET_ITEM(gobj)->kind;
    if (temp_r0 == It_Kind_Heart) {
        return true;
    }
    if (temp_r0 == It_Kind_Tomato) {
        return true;
    }
    if (temp_r0 == It_Kind_Foods) {
        return true;
    }
    return false;
}

void ftCo_800AFC40(Fighter* fp)
{
    struct Fighter_x1A88_t* temp_r31;
    struct Fighter_x1A88_t* temp_r28;

    Fighter* temp_r3_3;
    s32 var_r0;
    struct Fighter_x1A88_t* temp_r4;

    PAD_STACK(0x10);

    temp_r31 = &fp->x1A88;
    if (fp->x221D_b6) {
        var_r0 = 1;
    } else if (fp->x2168 != 0 && fp->x2338.x == 0) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        ftCo_800AECF0(fp);
        return;
    }
    temp_r31->xF8_b0 = true;
    temp_r31->xF9_b2 = true;
    temp_r31->xF9_b4 = true;
    temp_r31->xF9_b3 = true;
    temp_r31->xF9_b5 = true;
    temp_r31->xF9_b6 = true;
    temp_r31->xF9_b7 = false;
    temp_r31->xF9_b1 = false;
    fp->x1A88.x44 = ftCo_800A4BEC(fp);
    temp_r28 = &fp->x1A88;
    if (fp->item_gobj != NULL && !inlineI2(fp->item_gobj)) {
        temp_r28->x4C = NULL;
    } else {
        if (fp->x2168 != 0) {
            temp_r28->x4C = NULL;
        } else {
            temp_r28->x4C = ftCo_800A5F4C(fp, It_Kind_L_Gun_Ray);
        }
    }
    fp->x1A88.x50 = ftCo_800A648C(fp);
    temp_r4 = &fp->x1A88;
    if (inlineI1(temp_r4)) {
        temp_r3_3 = ftCo_800A50D4(fp);
        if (temp_r3_3 != NULL) {
            ftCo_800A75DC(fp, temp_r3_3);
        } else {
            ftCo_800A75DC(fp, temp_r31->x44);
        }
    }
    ftCo_800ADE48(fp);
}

/// #ftCo_800AFE3C

/// #ftCo_800B00F8

/// #ftCo_800B04DC

static inline void inlineI0(Fighter* fp, struct Fighter_x1A88_t* data)
{
    data->xF8_b0 = false;
    data->xF9_b2 = true;
    data->xF9_b4 = true;
    data->xF9_b3 = false;
    data->xF9_b5 = false;
    data->xF9_b6 = false;
    data->xF9_b7 = false;
    data->xF9_b1 = false;
    fp->x1A88.x44 = ftCo_800A4BEC(fp);
}

static inline void inlineI3(Fighter* fp, struct Fighter_x1A88_t* data)
{
    struct Fighter_x1A88_t* fp_data = &fp->x1A88;
    if (inlineI1(fp_data)) {
        if (data->xFB_b0) {
            ftCo_800A8DE4(fp);
        } else {
            ftCo_800A7AAC(fp);
        }
    }
}

void ftCo_800B0760(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    PAD_STACK(2 * 4);
    inlineI0(fp, data);
    if (fp->item_gobj != NULL) {
        if (!inlineI2(fp->item_gobj)) {
            data->x4C = NULL;
        }
    } else {
        if (fp->x2168 != 0) {
            data->x4C = NULL;
        } else {
            data->x4C = ftCo_800A5F4C(fp, It_Kind_L_Gun_Ray);
        }
    }
    fp->x1A88.x50 = ftCo_800A648C(fp);
    inlineI3(fp, data);
    ftCo_800ADE48(fp);
}

/// @todo Maybe a macro?
static inline float inlineM0(float x)
{
    return x >= 0 ? 127.0F * x : 128.0F * x;
}

void ftCo_800B0918(Fighter* fp0, Fighter* fp1)
{
    struct Fighter_x1A88_t* temp_r4 = &fp1->x1A88;
    temp_r4->x444 = temp_r4->x444->x1C;
    temp_r4->x448 = temp_r4->x448->x1C;
    if (temp_r4->x444 == temp_r4->x444) {
        temp_r4->x444 = &temp_r4->xFC;
    }
    if (temp_r4->x448 == temp_r4->x444) {
        temp_r4->x448 = &temp_r4->xFC;
    }
    temp_r4->x444->x6 = inlineM0(fp0->input.lstick.x);
    temp_r4->x444->x7 = inlineM0(fp0->input.lstick.y);
    temp_r4->x444->x8 = inlineM0(fp0->input.cstick.x);
    temp_r4->x444->x9 = inlineM0(fp0->input.cstick.y);
    temp_r4->x444->x4 = fp0->input.x650;
    temp_r4->x444->x5 = fp0->input.x650;
    temp_r4->x444->x0 = fp0->input.held_inputs;
    {
        struct Fighter_x1A88_xFC_t* temp_r6 = temp_r4->x444;
        temp_r6->cur_pos = fp0->cur_pos;
        temp_r4->x444->facing_dir = fp0->facing_dir;
    }
}

static inline bool inlineJ0(Fighter* fp, Fighter* nana_fp)
{
    if (fp->motion_id == ftCo_MS_FireFlowerShoot ||
        fp->motion_id == ftCo_MS_FireFlowerShootAir)
    {
        return false;
    }
    if (nana_fp->motion_id == ftPp_MS_SpecialLw &&
        fp->motion_id < ftCo_MS_Count)
    {
        return true;
    } else {
        return false;
    }
}

void ftCo_800B0AF4(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    Fighter* nana_fp = ftCo_800A589C(fp);
    if (nana_fp != NULL && data->xFA_b7) {
        if (inlineJ0(fp, nana_fp)) {
            fp->facing_dir = -nana_fp->facing_dir;
            ftPp_SpecialLw_Enter(fp->gobj);
            return;
        }
        data->lstickX = data->x448->x6;
        data->lstickY = data->x448->x7;
        data->x6 = data->x448->x8;
        data->x7 = data->x448->x9;
        data->x0 = data->x448->x0;
        data->x8 = data->x448->x4;
        data->rtrigger = data->x448->x5;
        if (fp->x2225_b3) {
            fp->cur_pos.x =
                0.95 * fp->cur_pos.x + 0.05 * data->x448->cur_pos.x;
            fp->cur_pos.y =
                0.95 * fp->cur_pos.y + 0.05 * data->x448->cur_pos.y;
            if (fp->motion_id != ftPp_MS_SpecialLw &&
                fp->motion_id != ftPp_MS_SpecialAirLw)
            {
                fp->facing_dir = data->x448->facing_dir;
            }
        }
    }
}

bool ftCo_800B0CA8(Fighter* fp0, Fighter* fp1)
{
    Item_GObj* temp_r5_2;
    enum ItemKind temp_r0;
    s32 temp_r0_2;
    s32 temp_r5;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r0_3;
    s32 var_r0_4;

    temp_r5 = fp1->motion_id;
    if (ftCo_800A3200(fp1) != 0) {
        goto jmp_9c;
    } else {
        if (temp_r5 == ftCo_MS_CaptureWaitHi) {
            var_r0_2 = 1;
        } else if (temp_r5 == ftCo_MS_CaptureWaitLw) {
            var_r0_2 = 1;
        } else if (temp_r5 >= ftCo_MS_ShoulderedWait && temp_r5 <= ftCo_MS_ShoulderedTurn) {
            var_r0_2 = 1;
        } else {
            var_r0_2 = 0;
        }
        if (var_r0_2 != 0) {
            goto jmp_9c;
        } else {
            if (temp_r5  == ftCo_MS_Ottotto || temp_r5 == ftCo_MS_OttottoWait) {
                var_r0_3 = 1;
            } else {
                var_r0_3 = 0;
            }
            if (var_r0_3 != 0) {
                /// @todo fakematched control flow
jmp_9c:
                return false;
            }
            if (temp_r5 >= ftCo_MS_CaptureKirby && temp_r5 <= ftCo_MS_CaptureWaitKirby) {
                return false;
            }
            if (temp_r5 >= ftCo_MS_Rebirth && temp_r5 <= ftCo_MS_RebirthWait) {
                return false;
            }
            if (temp_r5 >= ftCo_MS_WarpStarJump && temp_r5 <= ftCo_MS_WarpStarFall) {
                return false;
            }
            if (temp_r5 >= ftCo_MS_ItemParasolFall && temp_r5 <= ftCo_MS_ItemParasolDamageFall) {
                return false;
            }
            temp_r5_2 = fp0->item_gobj;
            if (temp_r5_2 != NULL) {
                temp_r0 = GET_ITEM(temp_r5_2)->kind;
                switch (temp_r0) {
                case It_Kind_Box:
                case It_Kind_Taru:
                case It_Kind_Kusudama:
                case It_Kind_TaruCann:
                    var_r0_4 = true;
                    break;
                default:
                    var_r0_4 = false;
                }
                if (var_r0_4 != 0) {
                    return false;
                }
            }
            if (fp1->ground_or_air == GA_Ground &&
                fp0->ground_or_air == GA_Air &&
                fp1->cur_pos.y > fp0->cur_pos.y && fp0->pos_delta.y < 0.0f)
            {
                return false;
            }
            if (fp0->x2225_b3) {
                return true;
            }
            switch (fp0->motion_id) {
            case ftCo_MS_Squat:
            case ftCo_MS_SquatWait:
            case ftCo_MS_Landing:
            case ftCo_MS_LandingFallSpecial:
            case ftCo_MS_LandingAirN:
            case ftCo_MS_LandingAirF:
            case ftCo_MS_LandingAirB:
            case ftCo_MS_LandingAirHi:
            case ftCo_MS_LandingAirLw:
                return true;
            }
        }
    }
    return false;
}

static inline bool inlineK0(Fighter* fp0)
{
    if (fp0->motion_id >= 361 && fp0->motion_id <= 366) {
        return true;
    } else {
        return false;
    }
}

bool ftCo_800B0E98(Fighter* fp0, Fighter* fp1)
{
    s32 temp_r0;

    if (ftCo_800B0CA8(fp0, fp1) != 0) {
        struct Fighter_x1A88_t* data = &fp0->x1A88;
        if (fp1->ground_or_air == GA_Air) {
            return false;
        }
        if (fp0->ground_or_air == GA_Air) {
            return false;
        }
        if (!data->xFB_b0) {
            if (inlineK0(fp0)) {
                if (!inlineI1_alt(fp0) && fp0->motion_id != ftCo_MS_Wait) {
                    return false;
                }
                {
                    float x = fp0->pos_delta.x - fp1->pos_delta.x,
                          y = fp0->pos_delta.y - fp1->pos_delta.y,
                          r = fp0->co_attrs.mid_walk_point;
                    if (SQ(x) + SQ(y) > SQ(r)) {
                        return false;
                    }
                }
                {
                    float x = fp0->cur_pos.x - fp1->cur_pos.x,
                          y = fp1->cur_pos.y - fp0->cur_pos.y;
                    if (SQ(x) + SQ(y) < SQ(25.0)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

/// #ftCo_800B101C

/// #ftCo_800B126C

/// #ftCo_800B1478

/// #ftCo_800B17D0

/// #ftCo_800B1AB8

void ftCo_800B1DA0(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    PAD_STACK(6 * 4);
    inlineI0(fp, data);
    if (inlineI1(data) && data->x7C % 60 * 5 == 0 && HSD_Randf() < 0.5) {
        ftCo_800A8940(fp);
    }
    ftCo_800ADE48(fp);
}

/// #ftCo_800B1EF0

/// #ftCo_800B21C8

/// #ftCo_800B24B8

/// #ftCo_800B2790

/// #ftCo_800B2AFC

/// #ftCo_800B33B0

void ftCo_800B3900(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);

    ftCo_800B33B0(fp);
    ftCo_800B2AFC(fp);
    ftCo_800B2790(fp);
    ftCo_800B3E04(fp);
    ftCo_800B0AF4(fp);
    fp->x1A88.x7C += 1;
}

bool ftCo_800B395C(Fighter_GObj* gobj, int arg1)
{
    Fighter* fp;
    int temp_r0_2;
    struct Fighter_x1A88_t* temp_r30;

    GXColor sp84;
    GXColor sp80;
    Mtx sp50;
    Vec3 sp44;
    Vec3 sp38;

    fp = GET_FIGHTER(gobj);
    temp_r30 = &fp->x1A88;
    if (Player_8003248C(fp->player_id, fp->x221F_b4) == Gm_PKind_Cpu) {
        switch (temp_r30->x18) {
        case 2:
        case 3:
            sp84.r = 0xFF;
            sp80.r = 0xFF;
            sp84.g = 0;
            sp80.g = 0;
            sp84.b = 0;
            sp80.b = 0;
            sp84.a = 0x60;
            sp80.a = 0x60;
            break;
        case 7:
            sp84.r = 0;
            sp80.r = 0;
            sp84.g = 0;
            sp80.g = 0;
            sp84.b = 0xFF;
            sp80.b = 0xFF;
            sp84.a = 0x60;
            sp80.a = 0x60;
            break;
        case 4:
            sp84.r = 0xFF;
            sp80.r = 0xFF;
            sp84.g = 0xFF;
            sp80.g = 0xFF;
            sp84.b = 0xFF;
            sp80.b = 0xFF;
            sp84.a = 0xFF;
            sp80.a = 0xFF;
            break;
        case 10:
            sp84.r = 0xFF;
            sp80.r = 0xFF;
            sp84.g = 0;
            sp80.g = 0;
            sp84.b = 0xFF;
            sp80.b = 0xFF;
            sp84.a = 0x60;
            sp80.a = 0x60;
            break;
        case 1:
            sp84.r = 0;
            sp80.r = 0;
            sp84.g = 0xFF;
            sp80.g = 0xFF;
            sp84.b = 0;
            sp80.b = 0;
            sp84.a = 0x60;
            sp80.a = 0x60;
            break;
        case 18:
            sp84.r = 0;
            sp80.r = 0;
            sp84.g = 0;
            sp80.g = 0;
            sp84.b = 0;
            sp80.b = 0;
            sp84.a = 0x60;
            sp80.a = 0x60;
            break;
        default:
            sp84.r = 0xFF;
            sp80.r = 0xFF;
            sp84.g = 0xFF;
            sp80.g = 0xFF;
            sp84.b = 0;
            sp80.b = 0;
            sp84.a = 0x60;
            sp80.a = 0x60;
            break;
        }
        sp44.x = temp_r30->x54.x;
        sp44.y = temp_r30->x54.y;
        sp44.z = 0.0f;
        PSMTXIdentity(sp50);
        lbColl_800096B4(sp50, sp44, sp44, &sp84, &sp80, 5.0f);
        sp84.r = 0xFF;
        sp84.g = 0xFF;
        sp84.b = 0;
        sp84.a = 0x60;
        if (fp->facing_dir > 0.0) {
            sp44.x = fp->cur_pos.x - temp_r30->x560;
            sp44.y = fp->cur_pos.y + temp_r30->x568;
            sp44.z = fp->cur_pos.z;
            sp38.x = fp->cur_pos.x + temp_r30->x55C;
            sp38.y = fp->cur_pos.y;
            sp38.z = fp->cur_pos.z;
        } else {
            sp44.x = fp->cur_pos.x - temp_r30->x55C;
            sp44.y = fp->cur_pos.y + temp_r30->x568;
            sp44.z = fp->cur_pos.z;
            sp38.x = fp->cur_pos.x + temp_r30->x560;
            sp38.y = fp->cur_pos.y;
            sp38.z = fp->cur_pos.z;
        }
        if (temp_r30->xF8_b7) {
            temp_r0_2 = temp_r30->x7C % 3;
            if (temp_r0_2 == 1) {
                sp84.r = 0xFF;
                sp84.g = 0xFF;
                sp84.b = 0;
                sp84.a = 0xFF;
                lbColl_80009DD4(&sp44, &sp38, &sp84);
            } else if (temp_r0_2 == 2) {
                sp84.r = 0;
                sp84.g = 0;
                sp84.b = 0;
                sp84.a = 0;
                lbColl_80009DD4(&sp44, &sp38, &sp84);
            } else {
                sp84.r = 0xFF;
                sp84.g = 0xFF;
                sp84.b = 0xFF;
                sp84.a = 0xFF;
                lbColl_80009DD4(&sp44, &sp38, &sp84);
            }
        } else {
            lbColl_80009DD4(&sp44, &sp38, &sp84);
        }
        if (temp_r30->x18 == 2) {
            sp84.r = 0xFF;
            sp84.g = 0;
            sp84.b = 0;
            sp84.a = 0x60;
            if (fp->facing_dir > 0.0) {
                sp44.x = fp->cur_pos.x + temp_r30->x6C.x;
                sp44.y = fp->cur_pos.y + temp_r30->x74.y;
                sp44.z = fp->cur_pos.z;
                sp38.x = fp->cur_pos.x + temp_r30->x74.x;
                sp38.y = fp->cur_pos.y + temp_r30->x6C.y;
                sp38.z = fp->cur_pos.z;
            } else {
                sp44.x = fp->cur_pos.x - temp_r30->x74.x;
                sp44.y = fp->cur_pos.y + temp_r30->x74.y;
                sp44.z = fp->cur_pos.z;
                sp38.x = fp->cur_pos.x - temp_r30->x6C.x;
                sp38.y = fp->cur_pos.y + temp_r30->x6C.y;
                sp38.z = fp->cur_pos.z;
            }
            lbColl_80009DD4(&sp44, &sp38, &sp84);
        }
        return true;
    }
    return false;
}
