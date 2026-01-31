#include "itfushigibana.h"

#include <placeholder.h>
#include <platform.h>

#include "ef/eflib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

ItemStateTable it_803F82F0[] = {
    { 0, itFushigibana_UnkMotion0_Anim, itFushigibana_UnkMotion0_Phys,
      itFushigibana_UnkMotion0_Coll },
    { 1, itFushigibana_UnkMotion1_Anim, itFushigibana_UnkMotion1_Phys,
      itFushigibana_UnkMotion1_Coll },
    { 2, itFushigibana_UnkMotion2_Anim, itFushigibana_UnkMotion2_Phys,
      itFushigibana_UnkMotion2_Coll }
};

void it_2725_Logic29_Spawned(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    itFushigibanaAttributes* attrs =
        item->xC4_article_data->x4_specialAttributes;
    it_80279CDC(gobj, attrs->x0);
    Item_8026AE84(item, 0x272f, 0x7f, 0x40);
    it_80275158(gobj, attrs->x4);
    item->xDD4_itemVar.fushigibana.x60.b0 = false;
    item->xDD4_itemVar.fushigibana.x64 = attrs->x8;
    it_802D70A4(gobj);
}

void it_802D705C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDCE_flag.b7 = 0;
    it_80273454(gobj);
    it_802D718C(gobj);
}

void it_802D70A4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    it_80273670(gobj, 0, 0.0f);
    it_8026BDB4(gobj);
}

bool itFushigibana_UnkMotion0_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void itFushigibana_UnkMotion0_Phys(Item_GObj* gobj)
{
    it_8027A09C(gobj);
}

bool itFushigibana_UnkMotion0_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, (void (*)(HSD_GObj*)) it_802D705C);
}

void it_802D718C(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    item->entered_hitlag = efLib_PauseAll;
    item->exited_hitlag = efLib_ResumeAll;
    item->xDD4_itemVar.fushigibana.x60.b0 = true;
}

static void itFushigibana_UnkMotion1_Anim_inline1(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    item->entered_hitlag = efLib_PauseAll;
    item->exited_hitlag = efLib_ResumeAll;
    item->xDD4_itemVar.fushigibana.x60.b0 = true;
}

static bool itFushigibana_UnkMotion1_Anim_inline2(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    item->xD44_lifeTimer -= 1.0f;
    if (item->xD44_lifeTimer <= 0) {
        return true;
    } else {
        return false;
    }
}

bool itFushigibana_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    itFushigibanaAttributes* attrs =
        item->xC4_article_data->x4_specialAttributes;
    if (it_80272C6C(gobj) == 0) {
        itFushigibana_UnkMotion1_Anim_inline1(gobj);
    }
    if (!item->xDD4_itemVar.fushigibana.x64) {
        item->xDD4_itemVar.fushigibana.x64 = attrs->x8;
        it_80275288(gobj, 4, 0x2730);
    }
    item->xDD4_itemVar.fushigibana.x64 -= 1.0f;
    return itFushigibana_UnkMotion1_Anim_inline2(gobj);
}

void itFushigibana_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itFushigibana_UnkMotion1_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026D62C(gobj, (HSD_GObjEvent) it_802D7328);
    it_80276CB8(gobj);
    return false;
}

void it_802D7328(Item_GObj* gobj)
{
    PAD_STACK(8);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    it_80273670(gobj, 0, 0);
}

bool itFushigibana_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itFushigibana_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itFushigibana_UnkMotion2_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802D705C);
    return false;
}
