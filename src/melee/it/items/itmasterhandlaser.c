#include "itmasterhandlaser.h"

#include "math_ppc.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "baselib/jobj.h"
#include "db/db.h"
#include "ef/efsync.h"

#include "ft/forward.h"

#include "ft/inlines.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/types.h"
#include "lb/lb_00B0.h"
#include "mp/mplib.h"

#include <math.h>
#include <baselib/gobj.h>

static inline float my_sqrtf(float x)
{
    static const double _half = .5;
    static const double _three = 3.0;

    u8 _[4] = { 0 };

    volatile float y;
    if (x > 0) {
        double guess = __frsqrte((double) x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        y = (float) (x * guess);
        return y;
    }
    return x;
}

Item_GObj* it_802F0340(Item_GObj* gobj, Vec3* prev_pos, Vec3* pos,
                       Fighter_Part part, ItemKind kind, f32 facing_dir)
{
    Item_GObj* spawned;
    Fighter* fp;
    SpawnItem spawn;
    Item* ip;
    PAD_STACK(4);

    fp = GET_FIGHTER(gobj);
    spawn.kind = kind;
    spawn.prev_pos = *prev_pos;
    spawn.pos = *pos;
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0;
    spawn.x0_parent_gobj = gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;
    spawned = Item_80268B18(&spawn);
    it_802F0484(spawned);
    db_80225DD8(spawned, gobj);
    it_802750F8(spawned);
    ip = GET_ITEM(spawned);
    ip->xDD4_itemVar.masterhandlaser.x4 = part;
    ip->xDD4_itemVar.masterhandlaser.x10 = spawned->hsd_obj;
    lb_8000C2F8(ip->xDD4_itemVar.masterhandlaser.x10, fp->parts[part].joint);
    Item_802694CC(spawned);
    return spawned;
}

void it_2725_Logic84_EvtUnk(Item_GObj* gobj, Item_GObj* arg1)
{
    it_8026B894(gobj, arg1);
}

void it_802F046C(Item_GObj* gobj)
{
    if (gobj != NULL) {
        GET_ITEM(gobj)->xDD4_itemVar.masterhandlaser.x0 = true;
    }
}

void it_802F0484(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itMasterHandLaserAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->on_accessory = it_802F05A8;
    ip->xDD4_itemVar.masterhandlaser.x0 = false;
    ip->xDD4_itemVar.masterhandlaser.x8 = attrs->x4;
}

bool itMasterhandlaser_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (it_80272C6C(gobj) == 0) {
        it_802F0484(gobj);
    }
    if (ip->xDD4_itemVar.masterhandlaser.x0) {
        lb_8000C390(ip->xDD4_itemVar.masterhandlaser.x10);
        return true;
    }
    return false;
}

void itMasterhandlaser_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itMasterhandlaser_UnkMotion0_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802F05A8(Item_GObj* gobj)
{
    Vec3 sp28;
    Vec3 sp1C;
    Item* ip = GET_ITEM(gobj);
    HSD_GObj* owner = ip->owner;
    Fighter* fp = GET_FIGHTER(owner);
    PAD_STACK(8);
    it_802F063C(gobj, owner);
    lb_8000B1CC(fp->parts[ip->xDD4_itemVar.masterhandlaser.x4].joint, NULL,
                &sp28);
    lb_8000B1CC(ip->xBBC_dynamicBoneTable->bones[2], NULL, &sp1C);
    it_80275788(gobj);
    it_80275820(gobj, &sp28, &sp1C, 0);
}

void it_802F063C(Item_GObj* gobj, Item_GObj* arg1)
{
    s32 temp_r0;
    Vec3 delta;
    Vec3 pos_0;
    Vec3 pos_1;
    Vec3 pos_2;
    Fighter* fp;
    Item* ip;
    f32 var_f1;
    f32 var_f0;
    f32 var_f2;
    itMasterHandLaserAttributes* attrs;
    Vec3 translate;

    ip = GET_ITEM(gobj);
    fp = GET_FIGHTER(ip->owner);
    attrs = ip->xC4_article_data->x4_specialAttributes;
    lb_8000B804(HSD_JObjGetChild(gobj->hsd_obj), ip->xC8_joint->child);
    lb_8000B1CC(fp->parts[ip->xDD4_itemVar.masterhandlaser.x4].joint, NULL,
                &pos_0);
    translate.x = 0;
    translate.y = -attrs->x0;
    translate.z = 0;
    HSD_JObjSetTranslate(ip->xBBC_dynamicBoneTable->bones[2], &translate);
    lb_8000B1CC(ip->xBBC_dynamicBoneTable->bones[2], NULL, &pos_2);
    if (mpCheckMultiple(pos_0.x, pos_0.y, pos_2.x, pos_2.y, &pos_1, NULL, NULL,
                        NULL, 1, -1, -1) != 0)
    {
        translate.x = 0;
        translate.z = 0;
        delta.x = (pos_0.x - pos_2.x) * (pos_0.x - pos_2.x);
        delta.y = (pos_0.y - pos_2.y) * (pos_0.y - pos_2.y);
        delta.z = (pos_0.z - pos_2.z) * (pos_0.z - pos_2.z);
        var_f0 = sqrtf(delta.x + delta.y + delta.z);
        delta.x = (pos_0.x - pos_1.x) * (pos_0.x - pos_1.x);
        delta.y = (pos_0.y - pos_1.y) * (pos_0.y - pos_1.y);
        var_f1 = sqrtf(delta.x + delta.y);
        delta.x = (pos_0.x - pos_2.x) * (pos_0.x - pos_2.x);
        delta.y = (pos_0.y - pos_2.y) * (pos_0.y - pos_2.y);
        var_f2 = sqrtf(delta.x + delta.y);

        translate.y = var_f0 * -(var_f1 / var_f2);
        HSD_JObjSetTranslate(ip->xBBC_dynamicBoneTable->bones[2], &translate);

        temp_r0 = ip->xDD4_itemVar.masterhandlaser.x8 - 1;
        ip->xDD4_itemVar.masterhandlaser.x8 = temp_r0;
        if (temp_r0 < 0) {
            lb_8000B1CC(ip->xBBC_dynamicBoneTable->bones[2], NULL, &pos_2);
            efSync_Spawn(0x405, gobj, &pos_2);
            ip->xDD4_itemVar.masterhandlaser.x8 = attrs->x4;
        }
    } else {
        HSD_JObjSetTranslate(ip->xBBC_dynamicBoneTable->bones[2], &translate);
    }
}
