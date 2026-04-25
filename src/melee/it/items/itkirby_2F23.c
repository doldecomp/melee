#include "itkirby_2F23.h"

#include <placeholder.h>
#include <platform.h>

#include "ft/chara/ftKirby/ftKb_Init.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "MetroTRK/intrinsics.h"
#include "MSL/math.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

f64 it_802F23AC(Item_GObj* gobj, Vec3* pos)
{
    Item* ip = GET_ITEM(gobj);
    return SQ(ip->pos.x - pos->x) + SQ(ip->pos.y - pos->y) +
           SQ(ip->pos.z - pos->z);
}

static inline void it_802F23EC_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Vec3 pos;
    Vec2 limits;

    ip->xDD4_itemVar.kirby2f23.x1D0 = ftKb_SpecialN_800F5B4C(ip->grab_victim);
    ip->xDD4_itemVar.kirby2f23.x1D4 = ftKb_SpecialN_800F5B3C(ip->grab_victim);
    ftKb_SpecialN_800F5B5C(ip->grab_victim, &pos);
    ip->xDD4_itemVar.kirby2f23.x1C8 = ip->pos.x - pos.x;
    ip->xDD4_itemVar.kirby2f23.x1CC = ip->pos.y - pos.y;
    ftKb_SpecialN_800F5B20(ip->grab_victim, &limits);
    ip->xDD4_itemVar.kirby2f23.x1D8 = limits.x;
    ip->xDD4_itemVar.kirby2f23.x1DC = limits.y;
    ip->xDD4_itemVar.kirby2f23.x1F4 = ftKb_SpecialN_800F5AF0(ip->grab_victim);
    HSD_JObjGetScale(jobj, &ip->xDD4_itemVar.kirby2f23.x1E8);
    it_802756D0(gobj);
    it_80274ECC(gobj, 1);
    it_80274C88(gobj);
    it_8026BD54(gobj);
    it_80273408(gobj);
    ip->on_accessory = it_802F258C;
}

void it_802F23EC(Item_GObj* gobj, Fighter_GObj* owner_gobj, f32 facing_dir)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    ip->atk_victim = owner_gobj;
    ip->grab_victim = owner_gobj;
    it_8026C220(gobj, owner_gobj);
    ip->xDD0_flag.b1 = false;
    ip->facing_dir = facing_dir;
    ip->xBC_itemStateContainer = it_803F9450;
    Item_80268E5C(gobj, 0, 0);
    it_802762BC(ip);
    it_802F23EC_inline(gobj);
}

bool itKirby_2F23_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itKirby_2F23_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itKirby_2F23_UnkMotion0_Coll(Item_GObj* gobj)
{
    return false;
}

static inline void it_802F258C_scale(Item_GObj* gobj, Vec3* offset)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    f32 dist = sqrtf__Ff(SQ(offset->x) + SQ(offset->y) + SQ(offset->z));

    if (dist < ip->xDD4_itemVar.kirby2f23.x1D0) {
        Vec3 scale;
        scale.x = scale.y = scale.z =
            (1.0f - ip->xDD4_itemVar.kirby2f23.x1D4) +
            ((dist / ip->xDD4_itemVar.kirby2f23.x1D0) *
             ip->xDD4_itemVar.kirby2f23.x1D4);

        scale.x *= ip->xDD4_itemVar.kirby2f23.x1E8.x;
        scale.y *= ip->xDD4_itemVar.kirby2f23.x1E8.y;
        scale.z *= ip->xDD4_itemVar.kirby2f23.x1E8.z;
        HSD_JObjSetScale(jobj, &scale);
    }
}

static inline void it_802F258C_update(Item_GObj* gobj, Vec3* offset)
{
    Item* ip = GET_ITEM(gobj);

    if (ABS(offset->x) > ip->xDD4_itemVar.kirby2f23.x1D8) {
        s32 sign = (offset->x < 0.0f) ? -1 : 1;
        offset->x = ip->xDD4_itemVar.kirby2f23.x1D8 * sign;
    }
    if (ABS(offset->y) > ip->xDD4_itemVar.kirby2f23.x1DC) {
        s32 sign = (offset->y < 0.0f) ? -1 : 1;
        offset->y = ip->xDD4_itemVar.kirby2f23.x1DC * sign;
    }

    ip->xDD4_itemVar.kirby2f23.x1C8 -= offset->x;
    ip->xDD4_itemVar.kirby2f23.x1CC -= offset->y;
    ftKb_SpecialN_800F5B5C(ip->grab_victim, offset);
    ip->pos.x = offset->x + ip->xDD4_itemVar.kirby2f23.x1C8;
    ip->pos.y = offset->y + ip->xDD4_itemVar.kirby2f23.x1CC;
    ip->pos.z = offset->z;
}

void it_802F258C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Vec3 offset;
    PAD_STACK(4);

    offset.x = ip->xDD4_itemVar.kirby2f23.x1C8;
    offset.y = ip->xDD4_itemVar.kirby2f23.x1CC;
    offset.z = 0.0f;

    it_802F258C_scale(gobj, &offset);
    it_802F258C_update(gobj, &offset);
}

void it_802F2810(HSD_GObj* gobj)
{
    Item* ip = gobj->user_data;
    Item_80268E5C(gobj, 1, 0);
    ip->on_accessory = it_802F289C;
    it_8026BB44((Item_GObj*) gobj);
    it_802756D0((Item_GObj*) gobj);
    it_802762BC(ip);
    it_80274ECC((Item_GObj*) gobj, 1);
    it_80273408((Item_GObj*) gobj);
}

bool itKirby_2F23_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

void itKirby_2F23_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itKirby_2F23_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802F289C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ftKb_SpecialN_800F5800(ip->grab_victim, &ip->pos);
}
