#include "itsamusgrapple.h"

#include "itlinkhookshot.h"

#include "ft/chara/ftSamus/types.h"
#include "ft/fighter.h"
#include "ft/ftcoll.h"
#include "ftSamus/types.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/itCharItems.h"
#include "it/item.h"

#include <baselib/gobj.h>
#include <baselib/gobjplink.h>

void it_2725_Logic53_Spawned(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = NULL;
}

/// #it_802B7160

/// #it_802B743C

/// #it_802B75FC

void it_802B7B84(Item_GObj* arg0)
{
    Item* item;
    Fighter* fp;
    HSD_GObj* gobj;
    ItemLink* item_link;

    if (arg0 != NULL) {
        item = arg0->user_data;
        if (item != NULL) {
            if (item->xDD4_itemVar.samusgrapple.x8 != NULL) {
                fp = GET_FIGHTER(item->xDD4_itemVar.samusgrapple.x8);
                if (fp != NULL) {
                    item->xDD4_itemVar.samusgrapple.unk_10 = NULL;
                    fp->fv.ss.x223C = 0;
                    fp->accessory2_cb = 0;
                    fp->death1_cb = 0;
                    fp->accessory3_cb = 0;
                    item_link = item->xDD4_itemVar.linkhookshot.x0;
                    while (item_link != NULL) {
                        gobj = item_link->x1D0_GObj;
                        item_link = item_link->next;
                        HSD_GObjPLink_80390228(gobj);
                    }
                    Item_8026A8EC(arg0);
                }
            }
        }
    }
}

/// #it_802B7C18

/// #fn_802B7E34

void itSamusgrapple_UnkMotion0_Phys(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = fn_802B7E34;
}

/// #fn_802B805C

void itSamusgrapple_UnkMotion1_Phys(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = fn_802B805C;
}

/// #fn_802B8384

void itSamusgrapple_UnkMotion2_Phys(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = fn_802B8384;
}

/// #fn_802B8524

void itSamusgrapple_UnkMotion3_Phys(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = fn_802B8524;
}

/// #fn_802B8684

void itSamusgrapple_UnkMotion4_Phys(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = fn_802B8684;
}

/// #fn_802B8814

void itSamusgrapple_UnkMotion5_Phys(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = fn_802B8814;
}

/// #fn_802B895C

void itSamusgrapple_UnkMotion6_Phys(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = fn_802B895C;
}

/// #fn_802B8B54

void itSamusgrapple_UnkMotion7_Phys(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = fn_802B8B54;
}

/// #fn_802B8D38

void itSamusgrapple_UnkMotion8_Phys(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = fn_802B8D38;
}

/// #it_802B900C

/// #it_802B91C4

/// #it_802B9328

/// #it_802B99A0

/// #it_802B9CE8

/// #it_802B9FD4

/// #it_802BA194

/// #it_802BA2D8

/// #it_802BA3BC

/// #it_802BA5DC

/// #it_802BA760

void it_2725_Logic53_PickedUp(Item_GObj* gobj)
{
    PAD_STACK(16);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    it_802A2428(gobj);
}

void it_802BA9B8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
    ftColl_8007AFF8(ip->xDD4_itemVar.samusgrapple.x8);
    it_802A2428(gobj);
}

void it_802BAA08(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    ftColl_8007AFF8(ip->xDD4_itemVar.samusgrapple.x8);
    it_802A2428(gobj);
}

void it_802BAA58(Item_GObj* gobj)
{
    PAD_STACK(16);
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
    it_802A2428(gobj);
}

void it_802BAA94(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
    ftColl_8007AFF8(ip->xDD4_itemVar.samusgrapple.x8);
    it_802A2428(gobj);
}

void it_802BAAE4(Item_GObj* gobj, Vec3* vel, f32 unused)
{
    Item* ip = GET_ITEM(gobj);
    ItemLink* link = ip->xDD4_itemVar.linkhookshot.x0;
    link->x8_vel = *vel;
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    it_802A2428(gobj);
}

void it_802BAB40(Item_GObj* gobj)
{
    PAD_STACK(16);
    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
    it_802A2428(gobj);
}

void it_802BAB7C(Item_GObj* gobj)
{
    PAD_STACK(16);
    Item_80268E5C(gobj, 7, ITEM_ANIM_UPDATE);
    it_802A2428(gobj);
}

/// Set grapple beam state and store duration.
void it_802BABB8(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    Fighter* fp = ip->owner->user_data;
    ftSs_DatAttrs* da = fp->ft_data->ext_attr;
    PAD_STACK(24);
    Item_80268E5C(gobj, 8, ITEM_ANIM_UPDATE);
    it_802A2428(gobj);
    fp->mv.ss.grapple.x4 = (f32) (s32) da->xD0;
}

void it_802BAC3C(Fighter_GObj* gobj)
{
    Fighter* fp;

    fp = gobj->user_data;
    if (fp->fv.ss.x223C != NULL) {
        it_802B7B84(fp->fv.ss.x223C);
        return;
    }
    fp->accessory2_cb = NULL;
    fp->death1_cb = NULL;
    fp->accessory3_cb = NULL;
}

void it_802BAC80(HSD_GObj* arg0)
{
    Item* item;
    Fighter* fp;

    fp = arg0->user_data;
    if (fp->fv.ss.x223C != NULL) {
        item = GET_ITEM(fp->fv.ss.x223C);
        if (item->xDD4_itemVar.samusgrapple.unk_10) {
            item->xDD4_itemVar.samusgrapple.unk_10(fp->fv.ss.x223C);
        }
    }
}

/// #it_802BACC4

void it_2725_Logic53_EvtUnk(Item_GObj* gobj, Item_GObj* arg1)
{
    Item* item = GET_ITEM(gobj);
    it_8026B894(gobj, arg1);
    if (item->xDD4_itemVar.samusgrapple.x8 == arg1) {
        item->xDD4_itemVar.samusgrapple.x8 = NULL;
    }
}
