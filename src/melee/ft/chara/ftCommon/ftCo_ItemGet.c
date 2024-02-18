#include <platform.h>
#include "ft/forward.h"
#include "it/forward.h"
#include <dolphin/mtx/forward.h>

#include "ftCo_ItemGet.h"

#include "ftCo_HammerWait.h"
#include "ftCo_Lift.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C88.h"
#include "ft/ftanim.h"
#include "ft/ftchangeparam.h"
#include "ft/ftcommon.h"
#include "ft/ftdata.h"
#include "ft/ftlib.h"
#include "ft/types.h"
#include "ftCommon/ftCo_0A01.h"
#include "ftCommon/ftCo_WarpStar.h"
#include "ftCommon/types.h"
#include "ftDonkey/ftDk_HeavyWait0.h"
#include "it/it_26B1.h"
#include "it/item.h"
#include "pl/pl_0371.h"

#include <common_structs.h>
#include <placeholder.h>
#include <dolphin/os/OSError.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>

/* 093CF4 */ static bool ftCo_80094150(HSD_GObj* arg0, HSD_GObj* arg1);
/* 094020 */ static bool ftCo_8009447C(ftCo_GObj* gobj, HSD_GObj* item_gobj);
/* 094238 */ static void ftCo_80094694(HSD_GObj* gobj, FtMotionId msid,
                                       bool loop);
/* 0942A0 */ static ftCo_GObj* ftCo_800942A0(ftCo_GObj* gobj, u32 flags);
/* 09444C */ static void ftCo_800948A8(ftCo_GObj* gobj, Item_GObj* item_gobj);

/* static */ float const ftCo_804D8580 = 30000;
/* static */ float const ftCo_804D8584 = 1;
/* static */ float const ftCo_804D8588 = 0;

static char ftItemPickup_803C5580[] = "ftGetImmItem item_gobj is NULL!!\n";
static char assert_msg1[] = "ftpickupitem.c";
static char assert_msg2[] = "item_gobj";

/* 094B6C */ static void ftCo_80094B6C(ftCo_GObj* gobj, Item_GObj* item_gobj);

bool ftCo_80094150(ftCo_GObj* gobj, Item_GObj* item_gobj)
{
    u8 _[8] = { 0 };
    itPickup* pickup;
    Vec2* offset0;
    ftCo_Fighter* fp = gobj->user_data;
    if (Item_IsGrabbable(item_gobj) &&
        (!fp->x2222_b4 || !it_8026B47C(item_gobj)) &&
        (fp->item_gobj == NULL || it_8026B4F0(item_gobj)))
    {
        pickup = &fp->x294_itPickup;
        if (fp->ground_or_air == GA_Ground) {
            offset0 = &pickup->gr_light_offset[0];
        } else {
            offset0 = &pickup->air_light_offset[0];
        }
        {
            bool b = it_8026B2B4(item_gobj);
            Vec3 it_pos;
            it_8026B344(item_gobj, &it_pos);
            {
                float x_range = it_8026B378(item_gobj);
                float y_range = it_8026B384(item_gobj);
                Vec2* offset1 = !b ? offset0 : &pickup->gr_heavy_offset[0];
                float x1 = offset1[1].x;
                float x0 = (fp->facing_dir * offset1[0].x) + fp->cur_pos.x;
                float y0 = fp->cur_pos.y + offset1[0].y;
                float y1 = offset1[1].y;
                if (x0 - x1 - x_range < it_pos.x &&
                    x_range + (x0 + x1) > it_pos.x &&
                    y0 - y1 - y_range < it_pos.y &&
                    y_range + (y0 + y1) > it_pos.y)
                {
                    return true;
                }
            }
        }
        goto ret_false;
    }
ret_false:
    return false;
}

HSD_GObj* ftCo_800942A0(HSD_GObj* gobj, u32 flags)
{
    u8 _[16] = { 0 };
    ftCo_Fighter* fp = gobj->user_data;
    itPickup* pickup = &fp->x294_itPickup;
    Vec2* offset0;
    if (fp->ground_or_air == GA_Ground) {
        offset0 = &pickup->gr_light_offset[0];
    } else {
        offset0 = &pickup->air_light_offset[0];
    }
    if (ftCo_800A2040(fp) && (signed) fp->x1A94 == 28) {
        return NULL;
    }
    {
        float min_dist_sq = 30000;
        HSD_GObj* cur = HSD_GObj_Entities->items;
        HSD_GObj* result = NULL;
        while (cur != NULL) {
            if (Item_IsGrabbable(cur)) {
                enum_t unk_enum = it_8026B2B4(cur);
                if ((!fp->x2222_b4 || !it_8026B47C(cur)) &&
                    (fp->item_gobj == NULL || it_8026B4F0(cur)))
                {
                    if ((unk_enum == 0 && flags & (1 << 0)) ||
                        (unk_enum == 1 && flags & (1 << 1)))
                    {
                        Vec2* vec;
                        Vec3 it_pos;
                        it_8026B344(cur, &it_pos);
                        {
                            float x_range = it_8026B378(cur);
                            float y_range = it_8026B384(cur);
                            if (unk_enum == 0) {
                                vec = offset0;
                            } else {
                                vec = &pickup->gr_heavy_offset[0];
                            }
                            {
                                float x1 = vec[1].x;
                                float x0 =
                                    fp->facing_dir * vec[0].x + fp->cur_pos.x;
                                float y0 = fp->cur_pos.y + vec[0].y;
                                float y1 = vec[1].y;
                                if (x0 - x1 - x_range < it_pos.x &&
                                    x_range + (x0 + x1) > it_pos.x &&
                                    y0 - y1 - y_range < it_pos.y &&
                                    y_range + (y0 + y1) > it_pos.y)
                                {
                                    float y_diff = it_pos.y - y0;
                                    float x_diff = it_pos.x - x0;
                                    float dist_sq = SQ(x_diff) + SQ(y_diff);
                                    if (dist_sq < min_dist_sq) {
                                        result = cur;
                                        min_dist_sq = dist_sq;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            cur = cur->next;
        }
        return result;
    }
}

bool ftCo_8009447C(HSD_GObj* gobj, HSD_GObj* item_gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (item_gobj == NULL) {
        OSReport("ftGetImmItem item_gobj is NULL!!\n");
        __assert("ftpickupitem.c", 399, "item_gobj");
    }
    if (it_8026B30C(item_gobj) == 5) {
        switch (itGetKind(item_gobj)) {
        case It_Kind_Heart:
            Fighter_8006CF5C(fp, it_8026B47C(item_gobj));
            Item_8026A8EC(item_gobj);
            goto block_35;
        case It_Kind_Tomato:
            Fighter_8006CF5C(fp, it_8026B47C(item_gobj));
            Item_8026A8EC(item_gobj);
            goto block_35;
        case It_Kind_Foods:
            Fighter_8006CF5C(fp, it_8026B47C(item_gobj));
            Item_8026A8EC(item_gobj);
            goto block_35;
        case Pokemon_Lucky_Egg:
            Fighter_8006CF5C(fp, it_8026B47C(item_gobj));
            Item_8026A8EC(item_gobj);
            goto block_35;
        case It_Kind_WhispyHealApple:
            Fighter_8006CF5C(fp, it_8026B47C(item_gobj));
            Item_8026A8EC(item_gobj);
            goto block_35;
        case It_Kind_WStar:
            ftCo_800C4724(gobj);
            return 1;
        case It_Kind_Hammer:
            ftCo_800C52F4(gobj);
            return 1;
        case It_Kind_RabbitC:
            ftCommon_8007FA58(gobj, item_gobj);
            goto block_35;
        case It_Kind_MetalB:
            ftLib_800871A8(gobj, item_gobj);
            Item_8026A8EC(item_gobj);
            goto block_35;
        case It_Kind_Spycloak:
            ftCo_800C88D4(gobj, p_ftCommonData->x7CC, 1);
            Item_8026A8EC(item_gobj);
            goto block_35;
        case It_Kind_Coin:
            Item_8026A8EC(item_gobj);
            goto block_35;
        }
    }
block_35:
    return false;
}

void ftCo_80094694(HSD_GObj* gobj, FtMotionId msid, bool loop)
{
    ftCo_Fighter* fp = gobj->user_data;
    {
        float anim_spd;
        if (msid == ftCo_MS_HeavyGet) {
            anim_spd = ftCo_CalcYScaledKnockback(
                Fighter_804D6524, 1, fp->x34_scale.y,
                M2C_FIELD(Fighter_804D6524, float*, 8));
        } else {
            anim_spd = 1;
        }
        fp->throw_flags = 0;
        Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0, anim_spd, 0,
                                  NULL);
    }
    if (loop) {
        while (!ftCheckThrowB3(fp)) {
            ftAnim_8006EBA4(gobj);
        }
    } else {
        ftAnim_8006EBA4(gobj);
    }
    if (msid == ftCo_MS_HeavyGet) {
        fp->mv.co.itemget.x0 = true;
        fp->take_dmg_cb = ftCo_800974C4;
    } else {
        fp->mv.co.itemget.x0 = false;
        fp->take_dmg_cb = ftCo_80094DF8;
    }
}

bool ftCo_80094790(HSD_GObj* gobj)
{
    u8 _[8] = { 0 };
    if (GET_FIGHTER(gobj)->x1978 == NULL) {
        HSD_GObj* unk_gobj = ftCo_800942A0(gobj, 3);
        if (unk_gobj != NULL) {
            if (!it_8026B2B4(unk_gobj)) {
                ftCo_80094694(gobj, 92, 0);
            } else {
                ftCo_80094694(gobj, 93, 0);
            }
            return true;
        }
    }
    return false;
}

void ftCo_80094818(HSD_GObj* gobj, int arg1)
{
    u8 _[8] = { 0 };
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->x1978 != NULL) {
        pl_8003E17C(fp->player_id, fp->x221F_b4, fp->x1978);
    } else if (fp->item_gobj != NULL) {
        if (ftData_OnItemPickupExt[fp->kind] != NULL) {
            ftData_OnItemPickupExt[fp->kind](gobj, arg1);
        }
        pl_8003E17C(fp->player_id, fp->x221F_b4, fp->item_gobj);
    }
}

static inline void inlineB0(ftCo_GObj* gobj)
{
    u64 _ = { 0 };

    ftCo_Fighter* fp = gobj->user_data;
    if (fp->x1978 != NULL) {
        pl_8003E17C(fp->player_id, fp->x221F_b4, fp->x1978);
    } else if (fp->item_gobj != NULL) {
        if (ftData_OnItemPickupExt[fp->kind] != NULL) {
            ftData_OnItemPickupExt[fp->kind](gobj, true);
        }
        pl_8003E17C(fp->player_id, fp->x221F_b4, fp->item_gobj);
    }
}

void ftCo_800948A8(ftCo_GObj* gobj, Item_GObj* item_gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->item_gobj != NULL) {
        fp->x1978 = item_gobj;
    } else {
        fp->item_gobj = item_gobj;
    }
    inlineB0(gobj);
    {
        u8 ret_part;
        if (it_8026B2B4(item_gobj) == 0) {
            if (itGetKind(item_gobj) == It_Kind_WStar) {
                ret_part = 0;
            } else {
                ret_part = fp->ft_data->x8->x10;
            }
        } else {
            ret_part = fp->ft_data->x8->x11;
        }
        pl_8003E854(fp->player_id, fp->x221F_b4, item_gobj);
        Item_8026AB54(item_gobj, gobj, ret_part);
        if (it_8026B2B4(item_gobj) == 1) {
            ft_800881D8(fp, fp->ft_data->x4C_collisionData->x2C, 127, 64);
        }
    }
}

static inline enum_t inlineA0(ftCo_Fighter* fp)
{
    enum_t unk_enum;
    if (fp->mv.co.itemget.x0) {
        unk_enum = 2;
    } else {
        unk_enum = 1;
    }
    return unk_enum;
}

void ftCo_ItemGet_Anim(HSD_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (ftCheckThrowB3(fp)) {
        Item_GObj* item_gobj = ftCo_800942A0(gobj, inlineA0(fp));
        if (item_gobj != NULL) {
            ftCo_800948A8(gobj, item_gobj);
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Item_GObj* item_gobj = fp->x1978;
        if (item_gobj == NULL) {
            item_gobj = fp->item_gobj;
        }
        if (item_gobj != NULL) {
            if (fp->motion_id == ftCo_MS_LightGet) {
                if (ftCo_8009447C(gobj, item_gobj)) {
                    return;
                }
            } else {
                if (fp->x2222_b0) {
                    ftDk_MS_341_800DF980(gobj);
                } else {
                    ftCo_80096D9C(gobj);
                }
                return;
            }
        }
        ft_8008A2BC(gobj);
    }
}

void ftCo_ItemGet_IASA(HSD_GObj* gobj) {}

void ftCo_ItemGet_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_ItemGet_Coll(HSD_GObj* gobj)
{
    ft_800841B8(gobj, ftCo_80094D90);
}

void ftCo_80094B6C(HSD_GObj* gobj, HSD_GObj* item_gobj)
{
    Vec3 vec;
    u8 _[4] = { 0 };
    ftCo_Fighter* fp = gobj->user_data;
    if (item_gobj == NULL) {
        OSReport("ftGetImmItem item_gobj is NULL!!\n");
        __assert("ftpickupitem.c", 399, "item_gobj");
    }
    if (it_8026B30C(item_gobj) == 5) {
        switch (itGetKind(item_gobj)) {
        case It_Kind_Heart:
            Fighter_8006CF5C(fp, it_8026B47C(item_gobj));
            Item_8026A8EC(item_gobj);
            return;
        case It_Kind_Tomato:
            Fighter_8006CF5C(fp, it_8026B47C(item_gobj));
            Item_8026A8EC(item_gobj);
            return;
        case It_Kind_Foods:
            Fighter_8006CF5C(fp, it_8026B47C(item_gobj));
            Item_8026A8EC(item_gobj);
            return;
        case Pokemon_Lucky_Egg:
            Fighter_8006CF5C(fp, it_8026B47C(item_gobj));
            Item_8026A8EC(item_gobj);
            return;
        case It_Kind_WhispyHealApple:
            Fighter_8006CF5C(fp, it_8026B47C(item_gobj));
            Item_8026A8EC(item_gobj);
            return;
        case It_Kind_WStar:
            vec.x = vec.y = vec.z = 0;
            Item_8026ABD8(item_gobj, &vec, 1);
            return;
        case It_Kind_Hammer:
            ftCo_800C5284(gobj);
            return;
        case It_Kind_RabbitC:
            ftCommon_8007FA58(gobj, item_gobj);
            return;
        case It_Kind_MetalB:
            ftLib_800871A8(gobj, item_gobj);
            Item_8026A8EC(item_gobj);
            return;
        case It_Kind_Spycloak:
            ftCo_800C88D4(gobj, p_ftCommonData->x7CC, 1);
            Item_8026A8EC(item_gobj);
            return;
        case It_Kind_Coin:
            Item_8026A8EC(item_gobj);
            return;
        }
    }
}

void ftCo_80094D90(HSD_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    ftCo_8009750C(gobj);
    /// @todo #ftCo_80094DF8
    if (fp->item_gobj != NULL) {
        ftCo_80094B6C(gobj, fp->item_gobj);
    }
    if (fp->x1978 != NULL) {
        ftCo_80094B6C(gobj, fp->x1978);
    }
    ftCo_800CC730(gobj);
}

void ftCo_80094DF8(HSD_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->item_gobj != NULL) {
        ftCo_80094B6C(gobj, fp->item_gobj);
    }
    if (fp->x1978 != NULL) {
        ftCo_80094B6C(gobj, fp->x1978);
    }
}
