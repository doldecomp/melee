#include <platform.h>
#include <placeholder.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"
#include "ftDonkey/forward.h"
#include "ftKoopa/forward.h"
#include "ftPopo/forward.h"
#include "lb/forward.h"

#include "ftCo_0A01.h"

#include "ftCo_0B3E.h"
#include "ftpickupitem.h"

#include "ft/chara/ftPopo/ftPp_1211.h"
#include "ft/fighter.h"
#include "ft/ft_0877.h"
#include "ft/ftlib.h"
#include "ft/inlines.h"
#include "ft/types.h"
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
#include "lb/lbcollision.h"
#include "mp/mpisland.h"
#include "mp/mplib.h"
#include "mp/types.h"
#include "pl/player.h"

#include <math.h>
#include <math_ppc.h>
#include <dolphin/mtx.h>
#include <MetroTRK/intrinsics.h>

int ftCo_803C5A68[] = {
    1, 0, 0, 1, 0, 0, 0, 1, 7, 6, 5, 4, 4, 3, 1, 1, 2, 1,
    5, 2, 2, 2, 3, 3, 3, 4, 0, 0, 8, 4, 1, 4, 4, 5, 5,
};

/* static */ extern StageBlastZone** ftCo_803C6594;

#pragma force_active on

/// #ftCo_800A0148

void ftCo_800A0384(ftCo_Fighter* fp)
{
    if (fp->cur_pos.y + fp->x1A88.x558 > Stage_GetBlastZoneTopOffset()) {
        ftCo_800B46B8(fp, 0x80, 0);
        ftCo_800B46B8(fp, 0x81, 0);
        ftCo_800B463C(fp, 0x7F);
        return;
    }
    if (ftCo_800A1CA8(fp)) {
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
        return;
    }
    ftCo_800B463C(fp, 8);
    ftCo_800B46B8(fp, 0x8E, 1);
    ftCo_800B46B8(fp, 0x91, 0x7F);
    ftCo_800B463C(fp, 7);
    ftCo_800B46B8(fp, 0x8E, 0xA);
    ftCo_800B463C(fp, 8);
    ftCo_800B46B8(fp, 0x8E, 1);
    ftCo_800B463C(fp, 0x7F);
}

void ftCo_800A0508(ftCo_Fighter* fp)
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

void ftCo_800A05F4(ftCo_Fighter* fp)
{
    if (fp->cur_pos.y + fp->x1A88.x558 > Stage_GetBlastZoneTopOffset()) {
        ftCo_800B46B8(fp, 0x80, 0);
        ftCo_800B46B8(fp, 0x81, 0);
        ftCo_800B463C(fp, 0x7F);
        return;
    }
    if (ftCo_800A1CA8(fp)) {
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
        return;
    }
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

void ftCo_800A0798(ftCo_Fighter* fp)
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

/// #ftCo_800A08F0

void ftCo_800A0AF4(ftCo_Fighter* fp)
{
    float rand = HSD_Randf();
    if (rand < 0.6f) {
        ftCo_800B46B8(fp, 0x80, 0);
        ftCo_800B46B8(fp, 0x81, 0x50);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B46B8(fp, 0x81, 0);
        ftCo_800B463C(fp, 0x7F);
        return;
    }
    if (rand < 0.8f) {
        ftCo_800B463C(fp, 0xA);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 9);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 0xA);
        ftCo_800B463C(fp, 0x7F);
        return;
    }
    if (rand < 0.9f) {
        ftCo_800B463C(fp, 2);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 1);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B463C(fp, 2);
        ftCo_800B463C(fp, 0x7F);
        return;
    }
    ftCo_800B463C(fp, 8);
    ftCo_800B46B8(fp, 0x8E, 1);
    ftCo_800B463C(fp, 7);
    ftCo_800B46B8(fp, 0x8E, 1);
    ftCo_800B463C(fp, 8);
    ftCo_800B463C(fp, 0x7F);
}

void ftCo_800A0C8C(ftCo_Fighter* fp)
{
    ftCo_800B463C(fp, 127);
}

static inline float inlineA0(float x)
{
    return x * SQ(x);
}

void ftCo_800A0CB0(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    if (fp->x1A88.x7C % 600 == 0) {
        float rand = 1.0F - inlineA0(HSD_Randf());
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
    Fighter* var_r31;
    HurtCapsule* hurt;
    float temp_f0;
    float temp_f0_2;
    float temp_f0_3;
    float temp_f0_4;
    float temp_f0_5;
    float temp_f0_6;
    float temp_f1;
    float temp_f3;
    float temp_f4;
    float temp_f5;
    float temp_f6;
    float var_f29;
    float var_f30;
    float var_f31;
    int var_r30;
    struct Fighter_x1A88_t* temp_r28;

    var_r31 = fp;
    temp_r28 = &fp->x1A88;
    var_r30 = 0;
    var_f29 = 0.0f;
    var_f31 = 0.0f;
    var_f30 = 0.0f;
    while (var_r30 < (int) fp->hurt_capsules_len) {
        hurt = var_r31->hurt_capsules;
        lbColl_800083C4(hurt);
        temp_f5 = fp->cur_pos.x;
        temp_f4 = hurt->a_pos.x - temp_f5;
        temp_f3 = hurt->scale * fp->x34_scale.y;
        temp_f6 = fp->cur_pos.y;
        temp_f0 = temp_f4 - temp_f3;
        if (var_f31 > temp_f0) {
            var_f31 = temp_f0;
        }
        temp_f0_2 = temp_f4 + temp_f3;
        if (var_f30 < temp_f0_2) {
            var_f30 = temp_f0_2;
        }
        temp_f0_3 = (hurt->a_pos.y - temp_f6) + temp_f3;
        if (var_f29 < temp_f0_3) {
            var_f29 = temp_f0_3;
        }
        temp_f1 = hurt->b_pos.x - temp_f5;
        temp_f0_4 = temp_f1 - temp_f3;
        if (var_f31 > temp_f0_4) {
            var_f31 = temp_f0_4;
        }
        temp_f0_5 = temp_f1 + temp_f3;
        if (var_f30 < temp_f0_5) {
            var_f30 = temp_f0_5;
        }
        temp_f0_6 = (hurt->b_pos.y - temp_f6) + temp_f3;
        if (var_f29 < temp_f0_6) {
            var_f29 = temp_f0_6;
        }
        var_r31 += 0x4C;
        var_r30 += 1;
    }
    if (fp->facing_dir > (float) 0.0) {
        M2C_FIELD(temp_r28, float*, 0x55C) = var_f30;
        M2C_FIELD(temp_r28, float*, 0x560) = (float) -var_f31;
    } else {
        M2C_FIELD(temp_r28, float*, 0x55C) = (float) -var_f31;
        M2C_FIELD(temp_r28, float*, 0x560) = var_f30;
    }
    M2C_FIELD(temp_r28, float*, 0x564) =
        (float) (0.5 * (f64) (M2C_FIELD(temp_r28, float*, 0x55C) +
                              M2C_FIELD(temp_r28, float*, 0x560)));
    M2C_FIELD(temp_r28, float*, 0x568) = var_f29;
}

bool ftCo_800A0F00(ftCo_GObj* gobj)
{
    struct Fighter_x1A88_t* data = &GET_FIGHTER(gobj)->x1A88;
    PAD_STACK(4);
    if (ft_80087A18(gobj)) {
        /// @todo This matches if #ft_80087A80 returns an `int`.
        int result = ft_80087A80(gobj);
        if (result == 2) {
            return 1;
        }
        if (result == 1) {
            if (data->x7C % 240 > 120) {
                return 1;
            }
            return 0;
        }
        return 0;
    }
    return 0;
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

float ftCo_800A17E4(ftCo_Fighter* fp)
{
    float result;
    if ((s8) fp->x1A88.x4 > 0) {
        result = (s8) fp->x1A88.x4 / 127.0f;
    } else {
        result = (s8) fp->x1A88.x4 * 0.0078125f;
    }
    if (result > 1.0) {
        return 1.0;
    }
    if (result < -1.0) {
        result = -1.0;
    }
    return result;
}

static inline float inlineB0(s8 val, float a, float b)
{
    float ret = val > 0 ? val / a : val * b;
    return ret > +1.0 ? +1.0F : ret < -1.0 ? -1.0F : ret;
}

float ftCo_800A1874(ftCo_Fighter* fp)
{
    return inlineB0(fp->x1A88.x5, 127.0f, deg_to_rad);
}

float ftCo_800A1904(ftCo_Fighter* fp)
{
    float ret = fp->x1A88.x8 / 255.0;
    return ret > 1.0 ? 1.0F : ret;
}

float ftCo_800A1948(ftCo_Fighter* fp)
{
    float ret = fp->x1A88.x9 / 255.0;
    return ret > 1.0 ? 1.0F : ret;
}

HSD_Pad ftCo_800A198C(ftCo_Fighter* fp)
{
    return fp->x1A88.x0;
}

float ftCo_800A1994(Fighter* fp)
{
    return inlineB0(fp->x1A88.x6, 127.0f, 128.0f);
}

float ftCo_800A1A24(ftCo_Fighter* fp)
{
    return inlineB0(fp->x1A88.x7, 127.0f, deg_to_rad);
}

f32 ftCo_800A1AB4(Fighter* fp0, Fighter* fp1)
{
    return sqrtf(SQ(fp0->cur_pos.y - fp1->cur_pos.y) +
                 SQ(fp0->cur_pos.x - fp1->cur_pos.x));
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

bool ftCo_800A1BA8(ftCo_Fighter* fp)
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

bool ftCo_800A1C44(ftCo_Fighter* fp)
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

bool ftCo_800A1CA8(ftCo_Fighter* fp)
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

bool ftCo_800A2040(ftCo_Fighter* fp)
{
    if (Player_8003248C(fp->player_id, fp->x221F_b4) != 1) {
        return false;
    }
    if ((signed) fp->x1A88.xC == 5) {
        return false;
    }
    return true;
}

/// #ftCo_800A20A0

void ftCo_800A20A0(ftCo_Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    PAD_STACK(2 * 4);

    if (fp->x1A88.x44 != NULL && fp->ground_or_air == GA_Ground) {
        ftCo_Fighter* other_fp = data->x44;
        float diff_y, diff_x;
        diff_x = fp->cur_pos.x - other_fp->cur_pos.x;
        diff_y = fp->cur_pos.y - other_fp->cur_pos.y;
        if (sqrtf__Ff(SQ(diff_x) + SQ(diff_y)) <
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
    if (fp0->ground_or_air == GA_Air) {
        return false;
    }
    if (fp1->ground_or_air == GA_Air) {
        return false;
    }
    {
        mp_UnkStruct0* data = mpIsland_8005AB54(fp0->coll_data.floor.index);
        if (data == NULL) {
            return false;
        }
        if (mpIsland_8005AB54(fp1->coll_data.floor.index) == data) {
            return true;
        }
    }
    return false;
}

bool ftCo_800A21FC(ftCo_Fighter* fp)
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

bool ftCo_800A2BD4(ftCo_Fighter* fp)
{
    return fp->facing_dir * (fp->x1A88.x54.x - fp->cur_pos.x) >= 0.0 ? true
                                                                     : false;
}

bool ftCo_800A2C08(Fighter* fp)
{
    ftCo_Fighter* other_fp = fp->x1A88.x44;
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

bool ftCo_IsGrabbing(ftCo_Fighter* fp)
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

bool ftCo_800A3200(ftCo_Fighter* fp)
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

static inline bool inlineC0(ftCo_Fighter* fp)
{
    if (fp->coll_data.env_flags & MPCOLL_WALL) {
        return true;
    } else {
        return false;
    }
}

bool ftCo_800A3498(ftCo_Fighter* fp)
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

bool ftCo_800A3554(ftCo_Fighter* fp, float arg1)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
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

bool ftCo_800A3710(ftCo_Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    Fighter* other_fp = fp->x1A88.x4C;
    if (!fp->x1A88.xF9_b7) {
        return false;
    }
    {
        if (other_fp == NULL) {
            return false;
        }
        if (Item_IsGrabbable(M2C_FIELD(data, HSD_GObj**, 4)) == 0) {
            data->x4C = NULL;
            return false;
        }
        if (fp->ground_or_air == GA_Air) {
            return false;
        }
        if (fp->item_gobj != NULL) {
            return false;
        }
        if (!ftCo_800A2170(fp, other_fp)) {
            return false;
        }
        if (ftpickupitem_80094150(fp->gobj,
                                  M2C_FIELD(other_fp, HSD_GObj**, 4)))
        {
            return true;
        }
        return false;
    }
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

/// #ftCo_800A3908

/// #ftCo_800A4038

/// #ftCo_800A4768

void ftCo_800A49B4(ftCo_Fighter* fp)
{
    float spC;
    float temp_f2;
    float temp_f3;
    float var_f4;
    f64 temp_f1;
    f64 temp_f1_2;
    f64 temp_f1_3;

    temp_f3 = M2C_FIELD(fp, float*, 0xB4) - M2C_FIELD(fp, float*, 0x1AE0);
    temp_f2 = M2C_FIELD(fp, float*, 0xB0) - M2C_FIELD(fp, float*, 0x1ADC);
    var_f4 = (temp_f2 * temp_f2) + (temp_f3 * temp_f3);
    if (var_f4 > 0.0f) {
        temp_f1 = __frsqrte(var_f4);
        temp_f1_2 =
            0.5 * temp_f1 * -(((f64) var_f4 * (temp_f1 * temp_f1)) - 3.0);
        temp_f1_3 = 0.5 * temp_f1_2 *
                    -(((f64) var_f4 * (temp_f1_2 * temp_f1_2)) - 3.0);
        spC = (float) ((f64) var_f4 *
                       (0.5 * temp_f1_3 *
                        -(((f64) var_f4 * (temp_f1_3 * temp_f1_3)) - 3.0)));
        var_f4 = spC;
    }
    M2C_FIELD((fp + 0x1A88), float*, 0x5C) = var_f4;
}

static inline bool inlineD0(ftCo_Fighter* fp, ftCo_Fighter* fp1)
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

static inline bool inlineD1(ftCo_Fighter* fp)
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

static inline void inlineD3(ftCo_Fighter* fp) {}

ftCo_Fighter* ftCo_800A4A40(ftCo_Fighter* fp)
{
    if (fp == NULL) {
        return NULL;
    }
    {
        ftCo_GObj* cur;
        ftCo_Fighter* cur_fp = NULL;
        float var_f31;
        PAD_STACK(6 * 4);
        for (cur = HSD_GObj_Entities->fighters; cur != NULL; cur = cur->next) {
            if (fp->gobj != cur) {
                ftCo_Fighter* fp1 = GET_FIGHTER(cur);
                if (!inlineD0(fp, fp1)) {
                    if (!inlineD1(fp1)) {
                        if (cur_fp == NULL) {
                            float x = fp->cur_pos.x - fp1->cur_pos.x,
                                  y = fp->cur_pos.y - fp1->cur_pos.y;
                            cur_fp = fp1;
                            var_f31 = sqrtf__Ff(SQ(x) + SQ(y));
                        } else {
                            ftCo_Fighter* fp1 = cur->user_data;
                            float x = fp->cur_pos.x - fp1->cur_pos.x,
                                  y = fp->cur_pos.y - fp1->cur_pos.y,
                                  temp_f1_3 = sqrtf__Ff(SQ(x) + SQ(y));
                            if (var_f31 > temp_f1_3) {
                                var_f31 = temp_f1_3;
                                cur_fp = fp1;
                            }
                        }
                    }
                }
            }
        }
        return cur_fp;
    }
}

/// #ftCo_800A4BEC

/// #ftCo_800A4E8C

/// #ftCo_800A50D4

static inline void inlineD2(ftCo_Fighter* var_r28, ftCo_Fighter* fp,
                            ftCo_Fighter* temp_r31, ftCo_Fighter* temp_r29)
{
    f32 var_f31 = 0;
    f32 temp_f1;
    f32 temp_f2;
    f32 temp_f1_2;
    f32 temp_f2_2;
    f32 temp_f1_3;
    HSD_GObj* var_r27 = NULL;
    if (!(ftCo_IsAlly(fp, temp_r29) != 0)) {
        return;
    }
    if (inlineD1(temp_r29) == 0) {
        if (var_r28 == NULL) {
            var_r28 = temp_r29;
            temp_f1 = fp->cur_pos.y - M2C_FIELD(temp_r29, f32*, 0xB4);
            temp_f2 = fp->cur_pos.x - M2C_FIELD(temp_r29, f32*, 0xB0);
            var_f31 = sqrtf__Ff((temp_f2 * temp_f2) + (temp_f1 * temp_f1));
        } else {
            ftCo_Fighter* fp1;
            fp1 = GET_FIGHTER(var_r27);
            temp_f1_2 = fp->cur_pos.y - M2C_FIELD(fp1, f32*, 0xB4);
            temp_f2_2 = fp->cur_pos.x - M2C_FIELD(fp1, f32*, 0xB0);
            temp_f1_3 =
                sqrtf__Ff((temp_f2_2 * temp_f2_2) + (temp_f1_2 * temp_f1_2));
            if (var_f31 > temp_f1_3) {
                var_f31 = temp_f1_3;
                var_r28 = fp1;
            }
        }
    }
}

Fighter* ftCo_800A50D4(ftCo_Fighter* fp)
{
    Fighter_GObj* temp_r30;
    HSD_GObj* var_r27;
    f32 temp_f29;
    f32 temp_f30;
    s32 var_r0;
    s32 var_r0_2;
    void* temp_r31;
    void* var_r28;
    void* temp_r29 = NULL;

    // var_f31 = saved_reg_f31;
    if (fp == NULL) {
        return NULL;
    }

    /// @todo #ftCo_800A4A40 but with #ftCo_IsAlly. Same inline somehow.
    temp_r31 = fp + 0x1A88;
    var_r28 = NULL;
    var_r27 = HSD_GObj_Entities->fighters;
loop_24:
    if (var_r27 != NULL) {
        if (fp->gobj != var_r27) {
            if (inlineD0(fp, temp_r31) == 0) {
                inlineD2(var_r28, fp, temp_r31, temp_r29);
            }
        }
        var_r27 = var_r27->next;
        goto loop_24;
    }
    return var_r28;
}

ftCo_Fighter* ftCo_800A5294(ftCo_Fighter* fp, int player_id)
{
    PAD_STACK(2 * 4);
    if (fp == NULL) {
        return NULL;
    }
    {
        ftCo_Fighter* cur_fp;
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

/// #ftCo_800A53DC

ftCo_Fighter* ftCo_800A589C(Fighter* fp)
{
    if (fp == NULL) {
        return NULL;
    }
    {
        ftCo_GObj* cur;
        for (cur = HSD_GObj_Entities->fighters; cur != NULL; cur = cur->next) {
            if (fp->gobj != cur) {
                ftCo_Fighter* cur_fp = GET_FIGHTER(cur);
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

bool ftCo_800A5908(ftCo_Fighter* fp)
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

bool ftCo_800A5980(ftCo_Fighter* fp)
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

bool ftCo_800A59C0(UNK_T arg0)
{
    if ((u32) (((u8) *M2C_FIELD(arg0, u8**, 0xCC) >> 3U) & 0xF) == 3) {
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
        fp->motion_id - (unsigned) ftCo_MS_RunDirect <= 1 ||
        fp->motion_id - (unsigned) ftCo_MS_Sleep <= 2)
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

bool ftCo_800A5A90(ftCo_Fighter* fp)
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

/// #ftCo_800A5ACC

/// #ftCo_800A5CE0

/// #ftCo_800A5F4C

/// #ftCo_800A61D8

/// #ftCo_800A648C

/// #ftCo_800A6700

/// #ftCo_800A6A98

/// #ftCo_800A6D2C

/// #ftCo_800A6FC4

/// #ftCo_800A75DC

/// #ftCo_800A7AAC

/// #ftCo_800A80E4

void ftCo_800A80E4(Fighter* fp)
{
    Fighter* other_fp = fp->x1A88.x44;
    if (other_fp != NULL && (fp->ground_or_air != GA_Air)) {
        Vec3 vec;
        if (!(ftCo_800A1AB4(fp, other_fp) > 50.0) &&
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

/// #ftCo_800A8EB0

static inline float inverseInlineE0(ftCo_Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    f32 cur_pos_x = fp->cur_pos.x;
    if (cur_pos_x - data->x54.x < 0.0f) {
        return -(cur_pos_x - data->x54.x);
    } else {
        return cur_pos_x - data->x54.x;
    }
}

static inline float inlineE0(ftCo_Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    if (data->x54.x - fp->cur_pos.x < 0.0f) {
        return -(data->x54.x - fp->cur_pos.x);
    } else {
        return data->x54.x - fp->cur_pos.x;
    }
}

void ftCo_800A92CC(ftCo_Fighter* fp)
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

void ftCo_800A949C(ftCo_Fighter* fp)
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

void ftCo_800A963C(ftCo_Fighter* fp)
{
    PAD_STACK(4 * 14);
    ftCo_800B46B8(fp, 0x81, 0x58);
    ftCo_800B46B8(fp, 0x90, 0x58);
    ftCo_800B46B8(fp, 0x88, 1);
    ftCo_800B463C(fp, 4);
    ftCo_800B46B8(fp, 0x90, 0x7F);
    ftCo_800B463C(fp, 0x7F);
}

/// #ftCo_800A96B8

/// #ftCo_800A9904

/// #ftCo_800A9CB4

void ftCo_800AA320(ftCo_Fighter* fp, int* arg1, int* arg2)
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

static inline bool inlineF0(ftCo_Fighter* fp)
{
    if (fp->motion_id == ftCo_MS_Ottotto ||
        fp->motion_id == ftCo_MS_OttottoWait)
    {
        return true;
    }
    return false;
}

void ftCo_800AABC8(ftCo_Fighter* fp)
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

void ftCo_800ABA34(ftCo_Fighter* fp)
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

static inline bool inlineG0(ftCo_Fighter* fp)
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
        if (fp->x1A88.x4 < 0) {
            ftCo_800B46B8(fp, 0x80, 0x7F);
        } else {
            ftCo_800B46B8(fp, 0x80, 0x81);
        }
        ftCo_800B463C(fp, 0x7F);
    }
}

static inline enum_t inlineH0(ftCo_Fighter* fp)
{
    if (fp->motion_id == ftCo_MS_BarrelWait) {
        return 1;
    }
    if (fp->motion_id == ftCo_MS_Barrel) {
        return 2;
    }
    return 0;
}

static inline void inlineH1(ftCo_Fighter* fp, struct Fighter_x1A88_t* data)
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

void ftCo_800AC434(ftCo_Fighter* fp)
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

void ftCo_800AD42C(ftCo_Fighter* fp)
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

void ftCo_800AFC40(ftCo_Fighter* fp)
{
    Fighter* temp_r3_3;
    Item_GObj* temp_r3;
    enum ItemKind temp_r0;
    s32 temp_r3_2;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r27;
    struct Fighter_x1A88_t* temp_r28;
    struct Fighter_x1A88_t* temp_r4;
    void* temp_r31;

    temp_r31 = fp + 0x1A88;
    if (fp->x221D_b6) {
        var_r0 = 1;
    } else if ((fp->x2168 != 0) && (fp->x2338.x == 0)) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        ftCo_800AECF0(fp);
        return;
    }
    var_r27 = 1;
    M2C_FIELD(temp_r31, u8*, 0xF8) = M2C_FIELD(temp_r31, u8*, 0xF8) | 0x80;
    M2C_FIELD(temp_r31, u8*, 0xF9) = M2C_FIELD(temp_r31, u8*, 0xF9) | 0x20;
    M2C_FIELD(temp_r31, u8*, 0xF9) = M2C_FIELD(temp_r31, u8*, 0xF9) | 8;
    M2C_FIELD(temp_r31, u8*, 0xF9) = M2C_FIELD(temp_r31, u8*, 0xF9) | 0x10;
    M2C_FIELD(temp_r31, u8*, 0xF9) = M2C_FIELD(temp_r31, u8*, 0xF9) | 4;
    M2C_FIELD(temp_r31, u8*, 0xF9) = M2C_FIELD(temp_r31, u8*, 0xF9) | 2;
    M2C_FIELD(temp_r31, u8*, 0xF9) = M2C_FIELD(temp_r31, u8*, 0xF9) & ~1;
    M2C_FIELD(temp_r31, u8*, 0xF9) = M2C_FIELD(temp_r31, u8*, 0xF9) & ~0x40;
    fp->x1A88.x44 = ftCo_800A4BEC(fp);
    temp_r28 = &fp->x1A88;
    temp_r3 = fp->item_gobj;
    if (temp_r3 != NULL) {
        temp_r0 = GET_ITEM(temp_r3)->kind;
        switch (temp_r0) { /* irregular */
        case It_Kind_Heart:
            break;
        case It_Kind_Tomato:
            break;
        case It_Kind_Foods:
            break;
        default:
            var_r27 = 0;
            break;
        }
        if (var_r27 == 0) {
            temp_r28->x4C = NULL;
        } else {
            goto block_18;
        }
    } else {
    block_18:
        if (fp->x2168 != 0) {
            temp_r28->x4C = NULL;
        } else {
            temp_r28->x4C = ftCo_800A5F4C(fp, 0x23);
        }
    }
    fp->x1A88.x50 = ftCo_800A648C(fp);
    temp_r4 = &fp->x1A88;
    temp_r3_2 = fp->x1A88.x18;
    if ((temp_r3_2 != fp->x1A88.x20) && (temp_r3_2 != temp_r4->x1C)) {
        temp_r4->x60 = 0;
    }
    if (temp_r4->x18 == 4) {
        var_r0_2 = 0;
    } else {
        M2C_FIELD(temp_r4, u8*, 0xFA) = M2C_FIELD(temp_r4, u8*, 0xFA) & ~0x20;
        var_r0_2 = 1;
    }
    if (var_r0_2 != 0) {
        temp_r3_3 = ftCo_800A50D4(fp);
        if (temp_r3_3 != NULL) {
            ftCo_800A75DC(fp, temp_r3_3);
        } else {
            ftCo_800A75DC(fp, M2C_FIELD(temp_r31, Fighter**, 0x44));
        }
    }
    ftCo_800ADE48(fp);
}

/// #ftCo_800AFE3C

/// #ftCo_800B00F8

/// #ftCo_800B04DC

static inline void inlineI0(ftCo_Fighter* fp, struct Fighter_x1A88_t* data)
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

static inline bool inlineI2(Item_GObj* gobj)
{
    int temp_r0 = GET_ITEM(gobj)->kind;
    switch (temp_r0) { /* irregular */
    case It_Kind_Heart:
    case It_Kind_Tomato:
    case It_Kind_Foods:
        return 1;
    default:
        return 0;
    }
}

static inline void inlineI3(ftCo_Fighter* fp, struct Fighter_x1A88_t* data)
{
    struct Fighter_x1A88_t* fp_data = &fp->x1A88;
    if (inlineI1(fp_data) != 0) {
        if (data->xFB_b0) {
            ftCo_800A8DE4(fp);
        } else {
            ftCo_800A7AAC(fp);
        }
    }
}

void ftCo_800B0760(ftCo_Fighter* fp)
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
            data->x4C = ftCo_800A5F4C(fp, 35);
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

static inline bool inlineJ0(ftCo_Fighter* fp, ftCo_Fighter* nana_fp)
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

void ftCo_800B0AF4(ftCo_Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    Fighter* nana_fp = ftCo_800A589C(fp);
    if (nana_fp != NULL && data->xFA_b7) {
        if (inlineJ0(fp, nana_fp)) {
            fp->facing_dir = -nana_fp->facing_dir;
            ftPp_SpecialLw_Enter(fp->gobj);
            return;
        }
        data->x4 = data->x448->x6;
        data->x5 = data->x448->x7;
        data->x6 = data->x448->x8;
        data->x7 = data->x448->x9;
        data->x0 = data->x448->x0;
        data->x8 = data->x448->x4;
        data->x9 = data->x448->x5;
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
    switch (temp_r5) { /* irregular */
    case 0xFC:
        var_r0 = 1;
        break;
    case 0xFD:
        var_r0 = 2;
        break;
    default:
        var_r0 = 0;
        break;
    }
    if (var_r0 == 0) {
        if (temp_r5 == 0xE0) {
            var_r0_2 = 1;
        } else if (temp_r5 == 0xE3) {
            var_r0_2 = 1;
        } else if ((temp_r5 >= 0x10A) && (temp_r5 <= 0x10E)) {
            var_r0_2 = 1;
        } else {
            var_r0_2 = 0;
        }
        if (var_r0_2 == 0) {
            if ((temp_r5 - 0xF5) <= 1) {
                var_r0_3 = 1;
            } else {
                var_r0_3 = 0;
            }
            if (var_r0_3 != 0) {
                /* Duplicate return node #21. Try simplifying control flow for
                 * better match */
                return 0;
            }
            if ((temp_r5 >= 0x120) && (temp_r5 <= 0x121)) {
                return 0;
            }
            if ((temp_r5 >= 0xC) && (temp_r5 <= 0xD)) {
                return 0;
            }
            if ((temp_r5 >= 0x131) && (temp_r5 <= 0x132)) {
                return 0;
            }
            if ((temp_r5 >= 0x91) && (temp_r5 <= 0x93)) {
                return 0;
            }
            temp_r5_2 = fp0->item_gobj;
            if (temp_r5_2 != NULL) {
                temp_r0 = GET_ITEM(temp_r5_2)->kind;
                if (temp_r0 != It_Kind_Egg) {
                    if (temp_r0 < 3) {
                        if (temp_r0 < 1) {
                            goto block_41;
                        }
                        goto block_40;
                    }
                    if (temp_r0 < 6) {
                    block_40:
                        var_r0_4 = 1;
                    } else {
                        goto block_41;
                    }
                } else {
                block_41:
                    var_r0_4 = 0;
                }
                if (var_r0_4 != 0) {
                    return 0;
                }
                goto block_44;
            }
        block_44:
            if ((fp1->ground_or_air == GA_Ground) &&
                (fp0->ground_or_air == GA_Air) &&
                (fp1->cur_pos.y > fp0->cur_pos.y) && (fp0->pos_delta.y < 0.0f))
            {
                return 0;
            }
            if ((M2C_FIELD(fp0, u8*, 0x2225) >> 4) & 1) {
                return 1;
            }
            temp_r0_2 = fp0->motion_id;
            if (temp_r0_2 < 0x2C) {
                if (temp_r0_2 != 0x29) {
                    if ((temp_r0_2 < 0x29) && (temp_r0_2 < 0x27)) {
                        /* Duplicate return node #60. Try simplifying control
                         * flow for better match */
                        return 0;
                    }
                    /* Duplicate return node #59. Try simplifying control flow
                     * for better match */
                    return 1;
                }
                /* Duplicate return node #60. Try simplifying control flow for
                 * better match */
                return 0;
            }
            if (temp_r0_2 < 0x4B) {
                if (temp_r0_2 < 0x46) {
                    /* Duplicate return node #60. Try simplifying control flow
                     * for better match */
                    return 0;
                }
                return 1;
            }
            return 0;
        }
        /* Duplicate return node #21. Try simplifying control flow for better
         * match */
        return 0;
    }
    return 0;
}

static inline bool inlineK0(ftCo_Fighter* fp0)
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
    s32 var_r0;
    s32 var_r0_2;

    if (ftCo_800B0CA8(fp0, fp1) != 0) {
        struct Fighter_x1A88_t* data = &fp0->x1A88;
        if (fp1->ground_or_air == GA_Air) {
            return false;
        }
        if (fp0->ground_or_air == GA_Air) {
            return false;
        }
        if (!data->xFB_b0) {
            struct Fighter_x1A88_t* data = &fp0->x1A88;
            if (inlineK0(fp0)) {
                if (!inlineI1(data) && fp0->motion_id != ftCo_MS_Wait) {
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

/// #ftCo_800B395C
