#include "itgamewatchmanhole.h"

#include "db/db.h"
#include "ft/chara/ftGameWatch/ftGw_AttackLw3.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

HSD_GObj* it_802C65E4(Item_GObj* gobj, Vec* vec, enum Fighter_Part arg2,
                      float arg3);
void it_802C6764(Item_GObj* gobj);
void it_802C6784(Item_GObj* gobj);
void it_802C6718(Item_GObj* gobj);
bool itGamewatchmanhole_UnkMotion0_Anim(Item_GObj* gobj);

ItemStateTable it_803F78D8[] = { { 0, itGamewatchmanhole_UnkMotion0_Anim, 0,
                                   0 } };

HSD_GObj* it_802C65E4(Item_GObj* gobj, Vec* vec, enum Fighter_Part arg2,
                      float arg3)
{
    HSD_GObj* n;
    SpawnItem si;
    PAD_STACK(4);
    si.kind = It_Kind_GameWatch_Manhole;
    si.prev_pos = *vec;
    si.pos = si.prev_pos;
    si.facing_dir = arg3;
    si.x3C_damage = 0;
    si.vel.x = si.vel.y = si.vel.z = 0.0f;
    si.x0_parent_gobj = gobj;
    si.x4_parent_gobj2 = si.x0_parent_gobj;
    si.x44_flag.b0 = 1;
    si.x40 = 0;
    n = Item_80268B18(&si);
    if (n != NULL) {
        void** x = GET_ITEM(n)->xC4_article_data->x4_specialAttributes;
        Item_8026AB54(n, gobj, arg2);
        db_80225DD8(n, gobj);
        it_8027CE64(n, gobj, *x);
        return n;
    }
    return NULL;
}

void it_2725_Logic72_Destroyed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->owner != NULL) {
        ftGw_AttackLw3_ItemManholeRemove(ip->owner);
    }
}

void it_802C6718(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    if (ip != NULL) {
        if (ip->owner != NULL) {
            ftGw_AttackLw3_ItemManholeRemove(ip->owner);
        }
        Item_8026A8EC(gobj);
    }
}

void it_802C6764(Item_GObj* gobj)
{
    it_8026B724(gobj);
}

void it_802C6784(Item_GObj* gobj)
{
    it_8026B73C(gobj);
}

void it_2725_Logic72_PickedUp(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(0x10);
    ip->xDAC_itcmd_var0 = 0;
    it_8026BB44(gobj);
    if (ip->owner != NULL) {
        Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
        Item_802694CC(gobj);
    }
}

static inline bool itGamewatchmanhole_UnkMotion0_Anim_inline(Item_GObj* gobj);
static inline bool itGamewatchmanhole_UnkMotion0_Anim_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->owner != NULL) {
        return ftGw_AttackLw3_ItemCheckManholeRemove(ip->owner);
    }
    return true;
}

bool itGamewatchmanhole_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Vec vec;
    int pad;
    if (ip->xDAC_itcmd_var0 != 0) {
        HSD_JObj* jobj = NULL;
        ip->xDAC_itcmd_var0 = 0;
        it_8026BB20(gobj);
        jobj = HSD_JObjGetChild(gobj->hsd_obj);
        lb_8000B1CC(jobj, NULL, &vec);
        lb_800119DC(&vec, 120, 3.0f, 0.1f, 1.0471976f);
    }
    if (itGamewatchmanhole_UnkMotion0_Anim_inline(gobj)) {
        it_2725_Logic72_Destroyed(gobj);
        return true;
    }
    return false;
}

void it_2725_Logic72_EvtUnk(Item_GObj* gobj, Item_GObj* gobj2)
{
    it_8026B894(gobj, gobj2);
}
