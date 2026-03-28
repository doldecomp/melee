#include "itgreatfoxlaser.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itcoll.h"
#include "it/item.h"

#include "lb/lb_00B0.h"

#include <Runtime/runtime.h>

UNK_T it_802EAF28(Item_GObj* item_gobj)
{
    return (UNK_T)GET_ITEM(item_gobj)->xDD4_itemVar.greatfoxlaser.x38;
}

/// #it_802EAF34

void it_802EB1EC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(16);
    it_8027B730(gobj);
    it_8027C56C(gobj, ip->facing_dir);
    ip->xDCC_flag.b3 = 0;
    ip->xD5C = 0;
    ip->xDC8_word.flags.x15 = 0;
    it_8027542C(gobj);
    ip->xDD4_itemVar.greatfoxlaser.x36 = 1;
    it_802EB268(gobj);
}

void it_802EB268(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_8026B3A8(gobj);
    ip->xDD4_itemVar.greatfoxlaser.x36 = 60;
    ip->xDD4_itemVar.greatfoxlaser.x34 = 0;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itGreatfoxlaser_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    f32* attr = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(8);

    if (!it_80272C6C(gobj)) {
        if (ip->xDD4_itemVar.greatfoxlaser.x38 == 0) {
            ip->x40_vel.x = attr[1] * ip->facing_dir;
            it_80272460(&ip->x5D4_hitboxes[0].hit,
                        __cvt_fp2unsigned(attr[0]), gobj);
        } else {
            ip->x40_vel.x = attr[3] * ip->facing_dir;
            it_80272460(&ip->x5D4_hitboxes[0].hit,
                        __cvt_fp2unsigned(attr[2]), gobj);
        }
    } else {
        HSD_JObj* jobj = ip->xDD4_itemVar.greatfoxlaser.x20->hsd_obj;
        Vec3 pos = ip->xDD4_itemVar.greatfoxlaser.x28;
        lb_8000B1CC(jobj, &pos, &ip->pos);
    }

    if (ip->xDD4_itemVar.greatfoxlaser.x36 == 0) {
        return true;
    }
    ip->xDD4_itemVar.greatfoxlaser.x36--;
    return false;
}

void itGreatfoxlaser_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.greatfoxlaser.x34 != 0) {
        ip->facing_dir = -ip->facing_dir;
        it_8027C56C(gobj, ip->facing_dir);
        ip = GET_ITEM(gobj);
        it_8026B3A8(gobj);
        ip->xDD4_itemVar.greatfoxlaser.x36 = 60;
        ip->xDD4_itemVar.greatfoxlaser.x34 = 0;
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    }
}

bool itGreatFoxLaser_Logic27_DmgDealt(Item_GObj* item_gobj)
{
    return false;
}

bool itGreatFoxLaser_Logic27_Clanked(Item_GObj* item_gobj)
{
    return false;
}

bool itGreatFoxLaser_Logic27_Absorbed(Item_GObj* item_gobj)
{
    return false;
}

/// #it_2725_Logic27_Reflected

void it_802EB5A8(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
