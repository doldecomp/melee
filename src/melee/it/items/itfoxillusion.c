#include "itfoxillusion.h"

#include "db/db.h"
#include "ft/chara/ftFox/ftFx_SpecialS.h"
#include "ft/ftlib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCharItems.h"
#include "it/item.h"
#include "it/types.h"

#include <common_structs.h>
#include <dolphin/os/OSError.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>

ItemStateTable it_803F6818[] = {
    {
        0,
        itFoxillusion_UnkMotion0_Anim,
        itFoxillusion_UnkMotion0_Phys,
        itFoxillusion_UnkMotion0_Coll,
    },
    {
        1,
        itFoxillusion_UnkMotion1_Anim,
        itFoxillusion_UnkMotion1_Phys,
        itFoxillusion_UnkMotion1_Coll,
    },
    {
        2,
        itFoxillusion_UnkMotion2_Anim,
        itFoxillusion_UnkMotion2_Phys,
        itFoxillusion_UnkMotion2_Coll,
    },
};

void it_8029CD18(Item_GObj* item_gobj, int arg1)
{
    Item* item = GET_ITEM(item_gobj);
    HSD_JObj* jobj = item->xDD4_itemVar.foxillusion.xDDC;
    it_8026EECC(item_gobj, arg1);
    if (jobj != NULL) {
        HSD_JObjDispAll(jobj, NULL, HSD_GObj_80390EB8(arg1), 0);
    }
}

HSD_JObj* it_8029CD78(Item_GObj* item_gobj)
{
    Quaternion quat;
    HSD_JObj* temp_r30;
    HSD_JObj* temp_r29;
    Item* item;

    item = GET_ITEM(item_gobj);
    temp_r30 = GET_JOBJ(item_gobj);
    if (item->xDD4_itemVar.foxillusion.xDDC != NULL) {
        OSReport("illusion add twice.\n");
        while (1) {
        }
    }
    temp_r29 = HSD_JObjLoadJoint(item->xDD4_itemVar.foxillusion.xDD4);
    HSD_JObjGetRotation(temp_r30, &quat);
    HSD_JObjSetRotation(temp_r29, &quat);
    it_80272F7C(temp_r29, item->scl);
    return temp_r29;
}

Item_GObj* it_8029CEB4(HSD_GObj* parent, Vec3* pos, ItemKind kind, f32 dir)
{
    SpawnItem spawn;
    Item_GObj* item_gobj;

    spawn.kind = kind;
    spawn.prev_pos = *pos;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0F;
    spawn.x0_parent_gobj = parent;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = 1;
    spawn.x40 = 0;
    item_gobj = Item_80268B18(&spawn);
    if (item_gobj != NULL) {
        it_8029CFF0(item_gobj);
        db_80225DD8(item_gobj, parent);
        it_802750F8(item_gobj);
        return item_gobj;
    }
    return NULL;
}

bool itFoxIllusion_Logic14_DmgDealt(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    item->xCA8 = 0;
    return false;
}

void itFoxIllusion_Logic14_Destroyed(Item_GObj* item_gobj)
{
    u8 _[4] = { 0 };
    Item* item = GET_ITEM(item_gobj);
    if (item->xDD4_itemVar.foxillusion.xDDC != NULL) {
        HSD_JObjRemoveAll(item->xDD4_itemVar.foxillusion.xDDC);
    }
    item->xDD4_itemVar.foxillusion.xDDC = NULL;
    item->owner = NULL;
    item->xDC8_word.flags.x13 = false;
}

void it_8029CFF0(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    u8 _[4] = { 0 };

    item->xD44_lifeTimer =
        *(f32*) item->xC4_article_data->x4_specialAttributes;
    item->xD5C = 0;
    item->xDD4_itemVar.foxillusion.xDD4 =
        item->xC4_article_data->x10_modelDesc->x0_joint;
    it_8026B3A8(item_gobj);
    if (ftLib_800865CC(item->owner) == 1) {
        Item_80268E5C(item_gobj, 1, ITEM_ANIM_UPDATE);
    } else {
        Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
    }
    it_80274594(item_gobj);
    item->xDD4_itemVar.foxillusion.xDDC = NULL;
}

bool itFoxillusion_UnkMotion0_Anim(Item_GObj* item_gobj)
{
    Item* temp_r31;
    Item* item;

    temp_r31 = GET_ITEM(item_gobj);
    if (temp_r31->owner != NULL &&
        ftFx_SpecialS_GetCmdVar2(temp_r31->owner) == 2 &&
        temp_r31->xDD4_itemVar.foxillusion.xDDC == NULL)
    {
        temp_r31->xDD4_itemVar.foxillusion.xDDC = it_8029CD78(item_gobj);
    }
    item = GET_ITEM(item_gobj);
    if (item->owner != NULL ? ftFx_SpecialS_CheckGhostRemove(item->owner) : 1)
    {
        return true;
    }
    temp_r31->xD44_lifeTimer -= 1.0F;
    if (temp_r31->xD44_lifeTimer <= 0.0F) {
        temp_r31->xD44_lifeTimer = 0.0F;
        it_8029D798(item_gobj);
    }
    return false;
}

void itFoxillusion_UnkMotion0_Phys(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    HSD_JObj* jobj = GET_JOBJ(item_gobj);
    HSD_JObj* ghost_jobj = item->xDD4_itemVar.foxillusion.xDDC;
    if (item->owner != NULL) {
        ftFx_SpecialS_CopyGhostPosIndexed(item->owner, 1, &item->pos);
        HSD_JObjSetRotationX(
            jobj, ftFx_SpecialS_ReturnFloatVarIndexed(item->owner, 1));
        if (ghost_jobj != NULL) {
            Vec3 ghost_pos;
            ftFx_SpecialS_CopyGhostPosIndexed(item->owner, 3, &ghost_pos);
            HSD_JObjSetTranslate(ghost_jobj, &ghost_pos);
            HSD_JObjSetRotationX(
                ghost_jobj,
                ftFx_SpecialS_ReturnFloatVarIndexed(item->owner, 3));
        }
    }
}

bool itFoxillusion_UnkMotion0_Coll(Item_GObj* arg0)
{
    return false;
}

bool itFoxillusion_UnkMotion1_Anim(Item_GObj* item_gobj)
{
    return itFoxillusion_UnkMotion0_Anim(item_gobj);
}

void itFoxillusion_UnkMotion1_Phys(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    HSD_JObj* jobj = GET_JOBJ(item_gobj);
    HSD_JObj* ghost_jobj = item->xDD4_itemVar.foxillusion.xDDC;
    if (item->owner != NULL) {
        ftFx_SpecialS_CopyGhostPosIndexed(item->owner, 1, &item->pos);
        HSD_JObjSetRotationX(
            jobj, ftFx_SpecialS_ReturnFloatVarIndexed(item->owner, 1));
        if (ghost_jobj != NULL) {
            Vec3 ghost_pos;
            u8 _[8] = { 0 };
            ftFx_SpecialS_CopyGhostPosIndexed(item->owner, 3, &ghost_pos);
            HSD_JObjSetTranslate(ghost_jobj, &ghost_pos);
            HSD_JObjSetRotationX(
                ghost_jobj,
                ftFx_SpecialS_ReturnFloatVarIndexed(item->owner, 3));
        }
    }
}

bool itFoxillusion_UnkMotion1_Coll(Item_GObj* arg0)
{
    return false;
}

void it_8029D798(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    HSD_JObj* jobj = GET_JOBJ(item_gobj);
    f32* attr = item->xC4_article_data->x4_specialAttributes;
    item->xD44_lifeTimer = attr[1];
    it_80272A3C(jobj);
    Item_80268E5C(item_gobj, 2, ITEM_ANIM_UPDATE);
}

bool itFoxillusion_UnkMotion2_Anim(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    bool tmp = item->owner != NULL
                   ? ftFx_SpecialS_CheckGhostRemove(item->owner)
                   : true;
    if (tmp) {
        return true;
    }
    item->xD44_lifeTimer -= 1.0F;
    if (item->xD44_lifeTimer <= 0.0F) {
        item->xD44_lifeTimer = 0.0F;
        return true;
    }
    return false;
}

void itFoxillusion_UnkMotion2_Phys(Item_GObj* item_gobj)
{
    Vec3 sp10;
    Item* item = GET_ITEM(item_gobj);
    HSD_JObj* jobj = item->xDD4_itemVar.foxillusion.xDDC;
    if (item->owner != NULL && jobj != NULL) {
        ftFx_SpecialS_CopyGhostPosIndexed(item->owner, 3, &sp10);
        HSD_JObjSetTranslate(jobj, &sp10);
    }
}

bool itFoxillusion_UnkMotion2_Coll(Item_GObj* arg0)
{
    return false;
}

void it_8029D948(Item_GObj* item_gobj, HSD_GObj* ref)
{
    it_8026B894(item_gobj, ref);
}
