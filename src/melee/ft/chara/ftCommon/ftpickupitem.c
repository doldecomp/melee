#include <platform.h>
#include <placeholder.h>

#include "ft/forward.h"
#include "it/forward.h"

#include "ftpickupitem.h"

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
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_WarpStar.h"
#include "ftCommon/types.h"
#include "ftDonkey/ftDk_HeavyWait0.h"
#include "it/it_26B1.h"
#include "it/item.h"
#include "pl/pl_040D.h"
#include "pl/plbonuslib.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <dolphin/os/OSError.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>

bool ftpickupitem_80094150(ftCo_GObj* gobj, Item_GObj* item_gobj)
{
    itPickup* pickup;
    Vec4* offset0;
    ftCo_Fighter* fp = gobj->user_data;
    PAD_STACK(8);

    if (Item_IsGrabbable(item_gobj) &&
        (!fp->x2222_b4 || !it_8026B47C(item_gobj)) &&
        (fp->item_gobj == NULL || it_8026B4F0(item_gobj)))
    {
        pickup = &fp->x294_itPickup;
        if (fp->ground_or_air == GA_Ground) {
            offset0 = &pickup->gr_light_offset;
        } else {
            offset0 = &pickup->air_light_offset;
        }
        {
            bool b = it_8026B2B4(item_gobj);
            Vec3 it_pos;
            it_8026B344(item_gobj, &it_pos);
            {
                float x_range = it_8026B378(item_gobj);
                float y_range = it_8026B384(item_gobj);
                Vec4* offset1 = !b ? offset0 : &pickup->gr_heavy_offset;
                float x1 = offset1->z;
                float x0 = (fp->facing_dir * offset1->x) + fp->cur_pos.x;
                float y0 = fp->cur_pos.y + offset1->y;
                float y1 = offset1->w;
                if (x0 - x1 - x_range < it_pos.x &&
                    x_range + (x0 + x1) > it_pos.x &&
                    y0 - y1 - y_range < it_pos.y &&
                    y_range + (y0 + y1) > it_pos.y)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

/// Find item in pickup range?
Item_GObj* ftpickupitem_800942A0(ftCo_GObj* gobj, u32 flags)
{
    itPickup* pickup;
    ftCo_Fighter* fp;
    Vec4* offset0;

    fp = GET_FIGHTER(gobj);
    pickup = &fp->x294_itPickup;
    offset0 = fp->ground_or_air == GA_Ground ? &pickup->gr_light_offset
                                             : &pickup->air_light_offset;
    if (ftCo_800A2040(fp) && (signed) fp->x1A88.xC == 28) {
        return NULL;
    }
    {
        float min_dist_sq = 30000;
        Item_GObj* cur = HSD_GObj_Entities->items;
        Item_GObj* result = NULL;
        while (cur != NULL) {
            if (Item_IsGrabbable(cur)) {
                enum_t unk_enum = it_8026B2B4(cur);
                if ((!fp->x2222_b4 || !it_8026B47C(cur)) &&
                    (fp->item_gobj == NULL || it_8026B4F0(cur)))
                {
                    if ((unk_enum == 0 && flags & (1 << 0)) ||
                        (unk_enum == 1 && flags & (1 << 1)))
                    {
                        Vec3 it_pos;
                        Vec4* vec;
                        PAD_STACK(4);

                        it_8026B344(cur, &it_pos);
                        {
                            float x_range = it_8026B378(cur);
                            float y_range = it_8026B384(cur);
                            vec = unk_enum == 0 ? offset0
                                                : &pickup->gr_heavy_offset;
                            {
                                float x1 = vec->z;
                                float x0 =
                                    fp->facing_dir * vec->x + fp->cur_pos.x;
                                float y0 = fp->cur_pos.y + vec->y;
                                float y1 = vec->w;
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

bool ftpickupitem_8009447C(ftCo_GObj* gobj, Item_GObj* item_gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (item_gobj == NULL) {
        OSReport("ftGetImmItem item_gobj is NULL!!\n");
        __assert(__FILE__, 174, "item_gobj");
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

void ftpickupitem_80094694(ftCo_GObj* gobj, FtMotionId msid, bool loop)
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
        fp->take_dmg_cb = ftpickupitem_80094DF8;
    }
}

bool ftpickupitem_80094790(ftCo_GObj* gobj)
{
    PAD_STACK(8);
    if (GET_FIGHTER(gobj)->x1978 == NULL) {
        Item_GObj* unk_gobj = ftpickupitem_800942A0(gobj, 3);
        if (unk_gobj != NULL) {
            if (!it_8026B2B4(unk_gobj)) {
                ftpickupitem_80094694(gobj, ftCo_MS_LightGet, 0);
            } else {
                ftpickupitem_80094694(gobj, ftCo_MS_HeavyGet, 0);
            }
            return true;
        }
    }
    return false;
}

void ftpickupitem_80094818(ftCo_GObj* gobj, int arg1)
{
    ftCo_Fighter* fp = gobj->user_data;
    PAD_STACK(8);
    if (fp->x1978 != NULL) {
        pl_8003E17C(fp->player_id, fp->x221F_b4, fp->x1978);
    } else if (fp->item_gobj != NULL) {
        if (ftData_OnItemPickupExt[fp->kind] != NULL) {
            ftData_OnItemPickupExt[fp->kind](gobj, arg1);
        }
        pl_8003E17C(fp->player_id, fp->x221F_b4, fp->item_gobj);
    }
}

void ftpickupitem_800948A8(ftCo_GObj* gobj, Item_GObj* item_gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    PAD_STACK(8);
    if (fp->item_gobj != NULL) {
        fp->x1978 = item_gobj;
    } else {
        fp->item_gobj = item_gobj;
    }
    ftpickupitem_80094818(gobj, true);
    {
        Fighter_Part ret_part;
        if (it_8026B2B4(item_gobj) == false) {
            if (itGetKind(item_gobj) == It_Kind_WStar) {
                ret_part = FtPart_TopN;
            } else {
                ret_part = fp->ft_data->x8->x10;
            }
        } else {
            ret_part = fp->ft_data->x8->x11;
        }
        pl_8003E854(fp->player_id, fp->x221F_b4, item_gobj);
        Item_8026AB54(item_gobj, gobj, ret_part);
        if (it_8026B2B4(item_gobj) == 1) {
            ft_800881D8(fp, fp->ft_data->x4C_sfx->x2C, 127, 64);
        }
    }
}

void ftpickupitem_Anim(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (ftCheckThrowB3(fp)) {
        Item_GObj* item_gobj =
            ftpickupitem_800942A0(gobj, fp->mv.co.itemget.x0 ? 2 : 1);
        if (item_gobj != NULL) {
            ftpickupitem_800948A8(gobj, item_gobj);
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Item_GObj* item_gobj =
            fp->x1978 != NULL
                ? fp->x1978
                : fp->item_gobj; // set the held item if not already set
        if (item_gobj != NULL) {
            if (fp->motion_id == ftCo_MS_LightGet) {
                if (ftpickupitem_8009447C(gobj, item_gobj)) {
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

void ftpickupitem_IASA(ftCo_GObj* gobj) {}

void ftpickupitem_Phys(ftCo_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftpickupitem_Coll(ftCo_GObj* gobj)
{
    ft_800841B8(gobj, ftpickupitem_80094D90);
}

void ftpickupitem_80094B6C(ftCo_GObj* gobj, Item_GObj* item_gobj)
{
    Vec3 vec;
    ftCo_Fighter* fp = gobj->user_data;
    PAD_STACK(4);
    if (item_gobj == NULL) {
        OSReport("ftGetImmItem item_gobj is NULL!!\n");
        __assert(__FILE__, 399, "item_gobj");
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

void ftpickupitem_80094D90(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    ftCo_8009750C(gobj);
    /// @todo #ftpickupitem_80094DF8
    if (fp->item_gobj != NULL) {
        ftpickupitem_80094B6C(gobj, fp->item_gobj);
    }
    if (fp->x1978 != NULL) {
        ftpickupitem_80094B6C(gobj, fp->x1978);
    }
    ftCo_800CC730(gobj);
}

void ftpickupitem_80094DF8(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->item_gobj != NULL) {
        ftpickupitem_80094B6C(gobj, fp->item_gobj);
    }
    if (fp->x1978 != NULL) {
        ftpickupitem_80094B6C(gobj, fp->x1978);
    }
}
