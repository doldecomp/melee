#include "itgamewatchjudge.h"

#include "math.h"

#include "db/db.h"
#include "ft/ftlib.h"
#include "ftGameWatch/ftGw_SpecialS.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

HSD_GObj* it_802C7774(float facing_dir, HSD_GObj* parent_gobj, Vec3* pos,
                      s32 part, u32 arg4)
{
    HSD_GObj* new_gobj;
    SpawnItem si;
    PAD_STACK(4);

    si.prev_pos = *pos;
    si.pos = si.prev_pos;
    si.kind = It_Kind_GameWatch_Judge;
    si.facing_dir = facing_dir;
    si.x3C_damage = 0;
    si.vel.x = si.vel.y = si.vel.z = 0.0f;
    si.x0_parent_gobj = parent_gobj;
    si.x4_parent_gobj2 = si.x0_parent_gobj;
    si.x44_flag.b0 = 1;
    si.x40 = 0;

    new_gobj = Item_80268B18(&si);
    if (new_gobj != NULL) {
        void** special_attrs =
            GET_ITEM(new_gobj)->xC4_article_data->x4_specialAttributes;
        Item_8026AB54(new_gobj, parent_gobj, part);
        it_80273670(new_gobj, 0, (float) (arg4 + 1));
        it_802C78B8(new_gobj);
        db_80225DD8(new_gobj, (Fighter_GObj*) parent_gobj);
        it_8027CE64(new_gobj, parent_gobj, *special_attrs);
        return new_gobj;
    }
    return NULL;
}

void it_802C7A84(Item_GObj* item_gobj)
{
    int pad[1];
    Item* item = GET_ITEM(item_gobj);

    if (item != NULL) {
        if (item->owner != NULL) {
            ftGw_SpecialS_ItemJudgementSetFlag(item->owner);
        }
        Item_8026A8EC(item_gobj);
    }
}

void itGameWatchJudge_Logic77_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void it_802C7AD0(Item_GObj* gobj)
{
    it_8026B724(gobj);
}

void it_802C7AF0(Item_GObj* gobj)
{
    it_8026B73C(gobj);
}

void itGameWatchJudge_Logic77_Destroyed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->owner != NULL) {
        ftGw_SpecialS_ItemJudgementSetFlag(ip->owner);
    }
}

void it_2725_Logic77_PickedUp(Item_GObj* item_gobj)
{
    Item* it = GET_ITEM(item_gobj);
    it->xDB0_itcmd_var1 = 0;
    it->xDAC_itcmd_var0 = 0;
    if (it->owner != NULL) {
        Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
    }
}

void it_802C78B8(Item_GObj* item_gobj)
{
    HSD_GObj* owner;
    HSD_JObj* jobj;
    HSD_JObj* child;
    f32 facing;

    owner = GET_ITEM(item_gobj)->owner;
    jobj = GET_JOBJ(item_gobj);
    if (owner != NULL) {
        facing = ftLib_800865C0(owner);
        child = itGetJObjGrandchild((Item_GObj*) jobj);
        if (facing == 1.0f) {
            HSD_JObjSetRotationY(child, M_PI);
        } else {
            HSD_JObjSetRotationY(child, 0.0f);
        }
    }
}
