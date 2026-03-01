#include "itgamewatchjudge.h"

#include "math.h"

#include "ft/ftlib.h"
#include "ftGameWatch/ftGw_SpecialS.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/item.h"

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
void it_802C78B8(Item_GObj* arg0)
{
    HSD_GObj* owner;
    HSD_JObj* jobj;
    HSD_JObj* child;
    f32 facing;

    owner = GET_ITEM(arg0)->owner;
    jobj = GET_JOBJ(arg0);
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
