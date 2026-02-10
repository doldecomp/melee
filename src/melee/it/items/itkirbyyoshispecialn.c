#include "itkirbyyoshispecialn.h"

#include <platform.h>

#include "ft/chara/ftKirby/ftKb_Init.h"
#include "ft/ftlib.h"

#include "ftKirby/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lb_00B0.h"

#include <common_structs.h>

/* 2F2E68 */ static bool itKirbyyoshispecialn_UnkMotion0_Anim(Item_GObj* gobj);
/* 2F2E70 */ static void itKirbyyoshispecialn_UnkMotion0_Phys(Item_GObj* gobj);
/* 2F2E74 */ static bool itKirbyyoshispecialn_UnkMotion0_Coll(Item_GObj* gobj);

ItemStateTable it_803F9490[] = {
    { -1, itKirbyyoshispecialn_UnkMotion0_Anim,
      itKirbyyoshispecialn_UnkMotion0_Phys,
      itKirbyyoshispecialn_UnkMotion0_Coll },
};

/// @@todo Shared code with #it_802F2BFC.
void it_802F2D98(Item_GObj* gobj, Fighter_GObj* owner_gobj)
{
    Item* item = GET_ITEM(gobj);
    item->atk_victim = owner_gobj;
    item->grab_victim = owner_gobj;
    it_8026C220(gobj, owner_gobj);
    item->xDD0_flag.b1 = false;
    item->xBC_itemStateContainer = it_803F9490;
    it_80274F48(gobj, item->xC4_article_data->x10_modelDesc->x8_bone_attach_id,
                owner_gobj, ftKb_SpecialNYs_80109238(owner_gobj));
    Item_80268E5C(gobj, 0, 0);
    it_802762BC(item);
    it_802756D0(gobj);
    it_80274ECC(gobj, true);
    it_80274C88(gobj);
    it_8026BD54(gobj);
    it_80273408(gobj);
}

bool itKirbyyoshispecialn_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itKirbyyoshispecialn_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itKirbyyoshispecialn_UnkMotion0_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802F2E7C(Item_GObj* gobj, bool has_destroy_type)
{
    Item* item = GET_ITEM(gobj);
    it_80275070(gobj,
                item->xC4_article_data->x10_modelDesc->x8_bone_attach_id);
    lb_8000B1CC(ftLib_80086630(item->grab_victim,
                               ftKb_SpecialNYs_80109238(item->grab_victim)),
                NULL, &item->pos);
    it_8027B4A4(item->grab_victim, gobj);
    it_8027B378(item->grab_victim, gobj, 0);
    if (has_destroy_type) {
        item->destroy_type = 0;
    }
    item->atk_victim = NULL;
    item->grab_victim = NULL;
    it_8027CE44(gobj);
    Item_8026A8EC(gobj);
}
