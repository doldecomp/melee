#include "itmew.h"

#include "ef/eflib.h"
#include "gr/stage.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/types.h"

#include <baselib/gobj.h>
#include <baselib/random.h>

void it_802D3D94(Item_GObj*); /* static */
void it_802D3C9C(Item_GObj*); /* static */
void it_802D3BE0(Item_GObj*);
M2C_UNK it_8027ADEC(M2C_UNK, Item_GObj*, HSD_JObj*, f32); /* extern */

void it_802D3B18(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    MewVars* attr = ip->xC4_article_data->x4_specialAttributes;

    ip->facing_dir = 0.0F;
    it_802D3D94(gobj);
    it_80279CDC(gobj, attr->x0);
}

void it_802D3B6C(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void it_802D3B8C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    it_80273454(gobj);
    it_802D3BE0(gobj);
    Item_8026AE84(ip, 0x2729, 0x7F, 0x40);
}

void it_802D3BE0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = HSD_GObjGetHSDObj(gobj);

    it_8027ADEC(0x46B, gobj, jobj, 2.8F);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    return;
}

bool it_802D3C50(Item_GObj* gobj)
{
    if (it_80272C6C(gobj) == false) {
        it_802D3C9C(gobj);
    }
    return false;
}

void it_802D3C90(Item_GObj* gobj) {}

bool it_802D3C94(Item_GObj* gobj)
{
    return false;
}

void it_802D3C9C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    MewVars* attr = ip->xC4_article_data->x4_specialAttributes;

    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    if (HSD_Randi(2) != 0) {
        ip->x40_vel.x = attr->x4;
    } else {
        ip->x40_vel.x = -attr->x4;
    }
    ip->x40_vel.y = attr->x8;
}

bool it_802D3D28(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->pos.y > Stage_GetBlastZoneTopOffset()) {
        return true;
    }
    return false;
}

void it_802D3D6C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    MewVars* attr = ip->xC4_article_data->x4_specialAttributes;
    ip->x40_vel.y += attr->xC;
}

bool it_802D3D8C(Item_GObj* gobj)
{
    return false;
}

void it_802D3D94(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    it_80273670(gobj, 0, 0.0F);
}

bool it_802D3E08(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void it_802D3E2C(Item_GObj* gobj)
{
    Item* temp_r31;
    Item* temp_r30;

    if (it_8027A09C(gobj) != false) {
        temp_r31 = GET_ITEM(gobj);
        it_80273454(gobj);
        temp_r30 = GET_ITEM(gobj);
        it_8027ADEC(0x46B, gobj, gobj->hsd_obj, 2.8F);
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
        temp_r30->entered_hitlag = efLib_PauseAll;
        temp_r30->exited_hitlag = efLib_ResumeAll;
        Item_8026AE84(temp_r31, 0x2729, 0x7F, 0x40);
    }
}

bool it_802D3ED0(Item_GObj* gobj)
{
    return it_8027A118(gobj, it_802D3B8C);
}

ItemStateTable it_803F80C8[] = {
    { 0, it_802D3E08, it_802D3E2C, it_802D3ED0 },
    { 1, it_802D3C50, it_802D3C90, it_802D3C94 },
    { 2, it_802D3D28, it_802D3D6C, it_802D3D8C },
};
