#include "itcerebi.h"

#include "baselib/random.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "gr/stage.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

/* 2D3F6C */ static void it_802D3F6C(Item_GObj* gobj);
/* 2D3FA0 */ static void it_802D3FA0(Item_GObj* gobj);
/* 2D4024 */ static bool itCerebi_UnkMotion1_Anim(Item_GObj* gobj);
/* 2D4064 */ static void itCerebi_UnkMotion1_Phys(Item_GObj*);
/* 2D4068 */ static bool itCerebi_UnkMotion1_Coll(Item_GObj*);
/* 2D4070 */ static void it_802D4070(Item_GObj* gobj);
/* 2D40FC */ static bool itCerebi_UnkMotion2_Anim(Item_GObj* gobj);
/* 2D4140 */ static void itCerebi_UnkMotion2_Phys(Item_GObj* gobj);
/* 2D4160 */ static bool itCerebi_UnkMotion2_Coll(Item_GObj*);
/* 2D4168 */ static void it_802D4168(Item_GObj*);
/* 2D41DC */ static bool itCerebi_UnkMotion0_Anim(Item_GObj* gobj);
/* 2D4200 */ static void itCerebi_UnkMotion0_Phys(Item_GObj* gobj);
/* 2D429C */ static bool itCerebi_UnkMotion0_Coll(Item_GObj* gobj);

ItemStateTable it_803F80F8[] = {
    { 0, itCerebi_UnkMotion0_Anim, itCerebi_UnkMotion0_Phys,
      itCerebi_UnkMotion0_Coll },
    { 1, itCerebi_UnkMotion1_Anim, itCerebi_UnkMotion1_Phys,
      itCerebi_UnkMotion1_Coll },
    { 2, itCerebi_UnkMotion2_Anim, itCerebi_UnkMotion2_Phys,
      itCerebi_UnkMotion2_Coll },
};

void itCerebi_Logic23_Spawned(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    float* attr = item->xC4_article_data->x4_specialAttributes;
    item->facing_dir = 0.0f;
    it_802D4168(gobj);
    it_80279CDC(gobj, *attr);
}

void it_802D3F4C(Item_GObj* gobj, Item_GObj* arg1)
{
    it_8026B894(gobj, arg1);
}

void it_802D3F6C(Item_GObj* gobj)
{
    it_80273454(gobj);
    it_802D3FA0(gobj);
}

void it_802D3FA0(Item_GObj* gobj)
{
    f32 f;
    Item* item;
    HSD_JObj* jobj;

    item = GET_ITEM(gobj);
    jobj = GET_JOBJ(gobj);
    f = 1.0f;
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    item->entered_hitlag = efLib_PauseAll;
    item->exited_hitlag = efLib_ResumeAll;
    efSync_Spawn(0x472, gobj, jobj, &f);
}

bool itCerebi_UnkMotion1_Anim(Item_GObj* gobj)
{
    if (it_80272C6C(gobj) == 0) {
        it_802D4070(gobj);
    }
    return false;
}

void itCerebi_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itCerebi_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802D4070(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    float* attrs = item->xC4_article_data->x4_specialAttributes;

    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    item->entered_hitlag = efLib_PauseAll;
    item->exited_hitlag = efLib_ResumeAll;
    if (HSD_Randi(2) != 0) {
        item->x40_vel.x = attrs[1];
    } else {
        item->x40_vel.x = -attrs[1];
    }
    item->x40_vel.y = attrs[2];
}

bool itCerebi_UnkMotion2_Anim(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    if (item->pos.y > Stage_GetBlastZoneTopOffset()) {
        return true;
    }
    return false;
}

void itCerebi_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    item->x40_vel.y +=
        ((float*) item->xC4_article_data->x4_specialAttributes)[3];
}

bool itCerebi_UnkMotion2_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802D4168(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);

    it_802762BC(item);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    item->entered_hitlag = efLib_PauseAll;
    item->exited_hitlag = efLib_ResumeAll;
    it_80273670(gobj, 0, 0.0f);
}

bool itCerebi_UnkMotion0_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void itCerebi_UnkMotion0_Phys(Item_GObj* gobj)
{
    HSD_JObj* jobj;
    Item* item;
    float f;

    if (it_8027A09C(gobj)) {
        it_80273454(gobj);
        item = GET_ITEM(gobj);
        jobj = GET_JOBJ(gobj);
        f = 1.0f;
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
        item->entered_hitlag = efLib_PauseAll;
        item->exited_hitlag = efLib_ResumeAll;
        efSync_Spawn(0x472, gobj, jobj, &f);
    }
}

bool itCerebi_UnkMotion0_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, it_802D3F6C);
}
