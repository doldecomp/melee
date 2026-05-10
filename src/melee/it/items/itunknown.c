#include "itunknown.h"

#include "cm/camera.h"
#include "ef/eflib.h"
#include "gr/stage.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lbvector.h"

#include <baselib/random.h>
#include <MSL/math.h>
#include <MSL/trigf.h>

ItemStateTable it_803F7D60[] = {
    { 0, itUnknown_UnkMotion0_Anim, itUnknown_UnkMotion0_Phys,
      itUnknown_UnkMotion0_Coll },
    { 1, itUnknown_UnkMotion1_Anim, itUnknown_UnkMotion1_Phys,
      itUnknown_UnkMotion1_Coll },
    { -1, itUnknown_UnkMotion2_Anim, itUnknown_UnkMotion2_Phys,
      itUnknown_UnkMotion2_Coll },
    {
        0,
        it_802CF120,
        it_802CF154,
        it_802CF3D8,
    },
};

// permuterslop
static inline s32 randi_perm(f32 f)
{
    return HSD_Randi(f);
}

static inline s32 randi_perm_int(int i)
{
    return HSD_Randi(i);
}

void it_802CE710(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itUnknownAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    it_80273318(gobj, attr->x24[HSD_Randi(26)]);
    if (HSD_Randi(2) != 0) {
        ip->xDD4_itemVar.unknown.x60 = 1.0f;
    } else {
        ip->xDD4_itemVar.unknown.x60 = -1.0f;
    }
    ip->xDD4_itemVar.unknown.x64.i = 0;
    ip->xDD4_itemVar.unknown.x68.i = attr->x18.i;
    ip->xDCC_flag.b3 = false;
    ip->facing_dir = 0.0F;
    it_80279CDC(gobj, attr->x0.f);
    it_802CEC24(gobj);
}

void it_802CE7CC(Item_GObj* gobj) {}

void it_802CE7D0(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

bool itUnknown_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->pos.x > Stage_GetBlastZoneRightOffset() ||
        ip->pos.x < Stage_GetBlastZoneLeftOffset() ||
        ip->pos.y > Stage_GetBlastZoneTopOffset() ||
        ip->pos.y < Stage_GetBlastZoneBottomOffset())
    {
        it_802CE8D0(gobj);
    }
    return false;
}

void itUnknown_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itUnknownAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    it_80272860(gobj, attr->xC, attr->x10);
    ip->x40_vel.x += attr->x4 * ip->xDD4_itemVar.unknown.x60;
}

bool itUnknown_UnkMotion0_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802CE8D0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itUnknownAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    Vec3 cam_pos;
    Vec3 dir;

    HSD_JObjSetFlagsAll(gobj->hsd_obj, 0x10);
    ip->x40_vel.x = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.z = 0.0f;
    switch (HSD_Randi(4)) {
    case 0:
        ip->xDD4_itemVar.unknown.x84 = 0;
        ip->xDD4_itemVar.unknown.x6C.x = Stage_GetBlastZoneRightOffset();
        ip->xDD4_itemVar.unknown.x6C.y =
            randi_perm(Stage_GetBlastZoneTopOffset() -
                       Stage_GetBlastZoneBottomOffset()) +
            Stage_GetBlastZoneBottomOffset();
        break;
    case 1:
        ip->xDD4_itemVar.unknown.x84 = 1;
        ip->xDD4_itemVar.unknown.x6C.x = Stage_GetBlastZoneLeftOffset();
        ip->xDD4_itemVar.unknown.x6C.y =
            randi_perm(Stage_GetBlastZoneTopOffset() -
                       Stage_GetBlastZoneBottomOffset()) +
            Stage_GetBlastZoneBottomOffset();
        break;
    case 2:
        ip->xDD4_itemVar.unknown.x84 = 2;
        ip->xDD4_itemVar.unknown.x6C.x =
            randi_perm(Stage_GetBlastZoneRightOffset() -
                       Stage_GetBlastZoneLeftOffset()) +
            Stage_GetBlastZoneLeftOffset();
        ip->xDD4_itemVar.unknown.x6C.y = Stage_GetBlastZoneTopOffset();
        break;
    case 3:
    default:
        ip->xDD4_itemVar.unknown.x84 = 3;
        ip->xDD4_itemVar.unknown.x6C.x =
            randi_perm(Stage_GetBlastZoneRightOffset() -
                       Stage_GetBlastZoneLeftOffset()) +
            Stage_GetBlastZoneLeftOffset();
        ip->xDD4_itemVar.unknown.x6C.y = Stage_GetBlastZoneBottomOffset();
        break;
    }
    {
        f32 zero = 0.0f;
        ip->xDD4_itemVar.unknown.x6C.z = zero;
    }
    Camera_GetTransformInterest(&cam_pos);
    lbVector_Diff(&cam_pos, &ip->xDD4_itemVar.unknown.x6C, &dir);
    ip->xDD4_itemVar.unknown.x78.vec.x = attr->x14;
    ip->xDD4_itemVar.unknown.x78.vec.y = 0.0f;
    ip->xDD4_itemVar.unknown.x78.vec.z = 0.0f;
    lbVector_Rotate(&ip->xDD4_itemVar.unknown.x78.vec, 4,
                    atan2f(dir.y, dir.x));
    it_80272980(gobj);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    if (HSD_Randi(2) != 0) {
        Item_8026AE84(ip, 0x271A, 127, 64);
    } else {
        Item_8026AE84(ip, 0x271B, 127, 64);
    }
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool itUnknown_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itUnknownAttributes* attr;
    PAD_STACK(8);
    if (--ip->xDD4_itemVar.unknown.x64.i < 0) {
        it_802CED54(gobj);
        if (--ip->xDD4_itemVar.unknown.x68.i == 0) {
            return true;
        }
        attr = ip->xC4_article_data->x4_specialAttributes;
        ip->xDD4_itemVar.unknown.x64.i = attr->x20.i + HSD_Randi(attr->x1C.i);
    }
    return false;
}

void itUnknown_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itUnknown_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802CEC24(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool itUnknown_UnkMotion2_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void itUnknown_UnkMotion2_Phys(Item_GObj* gobj)
{
    if (it_8027A09C(gobj) != 0) {
        it_80273454(gobj);
        {
            Item* ip = GET_ITEM(gobj);
            itUnknownAttributes* attr =
                ip->xC4_article_data->x4_specialAttributes;
            ip->x40_vel.y = attr->x8;
            Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
            ip->entered_hitlag = efLib_PauseAll;
            ip->exited_hitlag = efLib_ResumeAll;
        }
    }
}

bool itUnknown_UnkMotion2_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, it_802CE7CC);
}

void it_802CED54(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    SpawnItem spawn;
    f32 range;
    f32 bottom = Stage_GetCamBoundsBottomOffset();
    range = (Stage_GetCamBoundsTopOffset() - bottom) / 3.0f;

    switch (ip->xDD4_itemVar.unknown.x84) {
    case 0:
    case 1:
        spawn.prev_pos.x = ip->xDD4_itemVar.unknown.x6C.x;
        spawn.prev_pos.y =
            ip->xDD4_itemVar.unknown.x6C.y + (randi_perm(range) - range / 2);
        break;
    case 2:
    case 3:
        spawn.prev_pos.x =
            ip->xDD4_itemVar.unknown.x6C.x + (randi_perm(range) - range / 2);
        spawn.prev_pos.y = ip->xDD4_itemVar.unknown.x6C.y;
        break;
    }
    spawn.prev_pos.z = ip->xDD4_itemVar.unknown.x6C.z;
    it_8026BB88(gobj, &spawn.pos);
    spawn.facing_dir = ip->facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel = ip->xDD4_itemVar.unknown.x78.vec;
    spawn.x40 = 0;
    spawn.kind = 0xC7;
    spawn.x0_parent_gobj = ip->owner;
    spawn.x4_parent_gobj2 = gobj;
    spawn.x44_flag.b0 = false;
    Item_80268B18(&spawn);
}

void it_2725_Logic38_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itUnknownAttributes* attr = ip->xC4_article_data->x4_specialAttributes;

    it_80273318(gobj, attr->x24[randi_perm_int(26)]);
    ip->xDCC_flag.b3 = false;
    ip->xD44_lifeTimer = attr->x0.i;
    it_80274740(gobj);

    if (ABS(ip->x40_vel.x) > ABS(ip->x40_vel.y)) {
        ip->x40_vel.y *= attr->x1C.f;
        ip->xDD4_itemVar.unknown.x78.dir = 0;
    } else {
        ip->x40_vel.x *= attr->x1C.f;
        ip->xDD4_itemVar.unknown.x78.dir = 1;
    }
    ip->xDD4_itemVar.unknown.x60 = 0.0f;
    ip->xDD4_itemVar.unknown.x64.f = 0.0f;
    ip->xDD4_itemVar.unknown.x68.f = 0.0f;
    ip->xDD4_itemVar.unknown.x6C.x =
        randi_perm_int((s32) (attr->x4 + attr->x8)) - attr->x8;
    ip->xDD4_itemVar.unknown.x6C.y =
        randi_perm_int((s32) (attr->xC + attr->x10)) - attr->x10;
    ip->xDD4_itemVar.unknown.x6C.z =
        randi_perm_int((s32) (attr->x14 + attr->x18.f)) - attr->x18.f;
    it_802CF0D4(gobj);
    it_8026B3A8(gobj);
}

void itUnknown_Logic38_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void it_802CF0D4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool it_802CF120(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (--ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    return false;
}

void it_802CF154(Item_GObj* gobj)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    Item* ip = GET_ITEM(gobj);
    itUnknownAttributes* attr = ip->xC4_article_data->x4_specialAttributes;

    ip->xDD4_itemVar.unknown.x60 += ip->xDD4_itemVar.unknown.x6C.x;
    ip->xDD4_itemVar.unknown.x64.f += ip->xDD4_itemVar.unknown.x6C.y;
    ip->xDD4_itemVar.unknown.x68.f += ip->xDD4_itemVar.unknown.x6C.z;
    HSD_JObjSetRotationX(jobj, 0.017453292f * ip->xDD4_itemVar.unknown.x60);
    HSD_JObjSetRotationY(jobj, 0.017453292f * ip->xDD4_itemVar.unknown.x64.f);
    HSD_JObjSetRotationZ(jobj, 0.017453292f * ip->xDD4_itemVar.unknown.x68.f);
    if (ip->xDD4_itemVar.unknown.x78.dir != 0) {
        ip->x40_vel.x *= attr->x20.f;
    } else {
        ip->x40_vel.y *= attr->x20.f;
    }
}

bool it_802CF3D8(Item_GObj* gobj)
{
    return false;
}
