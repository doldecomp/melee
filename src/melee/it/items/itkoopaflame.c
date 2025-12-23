#include "itkoopaflame.h"

#include <placeholder.h>
#include <platform.h>

#include <melee/it/forward.h>
#include <melee/lb/forward.h>

#include <sysdolphin/baselib/random.h>
#include <melee/db/db.h>
#include <melee/ef/eflib.h>
#include <melee/ef/efsync.h>
#include <melee/ft/chara/ftKirby/ftKb_Init.h>
#include <melee/ft/chara/ftKoopa/ftKp_SpecialN.h>
#include <melee/it/inlines.h>
#include <melee/it/it_266F.h>
#include <melee/it/it_26B1.h>
#include <melee/it/it_2725.h>
#include <melee/it/item.h>
#include <melee/lb/lbvector.h>
#include <MSL/math.h>
#include <MSL/trigf.h>

#define itkpf_Floor 1
#define itkpf_Ceiling 2
#define itkpf_LeftWall 4
#define itkpf_RightWall 8

typedef struct itKoopaFlame_Attributes {
    float x0_lifetime;        // 28.0
    float x4_hitbox_lifetime; // 20.0
    float x8_min_speed;       // 1.9
    float xC_max_speed;       // 2.2
    float x10_min_angle;      // 2.1816616
    float x14_max_angle;      // 2.5307274
} itKoopaFlame_Attributes;

ItemStateTable ItemStateTable_KoopaFlame[] = {
    {
        0,
        itKoopaFlame_UnkMotion0_Anim,
        itKoopaFlame_UnkMotion0_Phys,
        itKoopaFlame_UnkMotion0_Coll,
    },
};

static inline void clamp_angle(float* f)
{
    while (*f < -M_PI) {
        *f += 2 * M_PI;
    }
    while (*f > M_PI) {
        *f -= 2 * M_PI;
    }
}

static inline void clamp_angle_2(float* f)
{
    while (*f > M_PI) {
        *f -= 2 * M_PI;
    }
    while (*f < -M_PI) {
        *f += 2 * M_PI;
    }
}

void itKoopaFlame_Update_Direction(Item_GObj* gobj, int flags)
{
    Item* it = GET_ITEM(gobj);
    Vec vec = it->xDD4_itemVar.koopaflame.xC_direction;
    clamp_angle(&it->xDD4_itemVar.koopaflame.x24_angle);
    if ((flags & itkpf_Floor) != 0) {
        vec.x += it->x378_itemColl.floor.normal.x;
        vec.y += it->x378_itemColl.floor.normal.y;
    }
    if ((flags & itkpf_Ceiling) != 0) {
        vec.x += it->x378_itemColl.ceiling.normal.x;
        vec.y += it->x378_itemColl.ceiling.normal.y;
    }
    if ((flags & itkpf_LeftWall) != 0) {
        vec.x += it->x378_itemColl.left_facing_wall.normal.x;
        vec.y += it->x378_itemColl.left_facing_wall.normal.y;
    }
    if ((flags & itkpf_RightWall) != 0) {
        vec.x += it->x378_itemColl.right_facing_wall.normal.x;
        vec.y += it->x378_itemColl.right_facing_wall.normal.y;
    }
    lbVector_Normalize(&vec);
    it->xDD4_itemVar.koopaflame.xC_direction = vec;
}

void itKoopaFlame_Update_Angle(Item_GObj* gobj, int flags)
{
    Item* it = GET_ITEM(gobj);
    if (flags != 0) {
        float f31 = atan2f(it->xDD4_itemVar.koopaflame.x18_vel.x,
                           it->xDD4_itemVar.koopaflame.x18_vel.y) -
                    atan2f(it->xDD4_itemVar.koopaflame.xC_direction.x,
                           it->xDD4_itemVar.koopaflame.xC_direction.y);
        float f0, f1, f2;
        clamp_angle_2(&f31);
        if (f31 == 0.0f) {
            f1 = 0.0f;
        } else {
            f1 = lbVector_Angle(&it->xDD4_itemVar.koopaflame.xC_direction,
                                &it->xDD4_itemVar.koopaflame.x18_vel);
            if (ABS(f31) < M_PI_2) {
                f2 = 0.02f * (ABS(f31) / M_PI);
            } else {
                f2 = 0.5f * (ABS(f31) / M_PI);
            }
            if (f31 < 0.0f) {
                f0 = -f2;
            } else {
                f0 = f2;
            }
            f1 *= f0;
        }
        it->xDD4_itemVar.koopaflame.x24_angle -= f1;
        clamp_angle(&it->xDD4_itemVar.koopaflame.x24_angle);
    }
}

Item_GObj* itKoopaFlame_Spawn(Fighter_GObj* parent, Vec* pos, f32 facing_dir,
                              bool unk, s32 gfx, s32 base_speed, s32 scale,
                              s32 kind)
{
    SpawnItem spawn;
    Item_GObj* gobj;
    float rng;
    float range;
    float min;
    PAD_STACK(4);
    spawn.kind = kind;
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0.0f;
    it_8026BB68(parent, &spawn.pos);
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = parent;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = 1;
    spawn.x40 = unk;
    gobj = Item_80268B18(&spawn);
    if (gobj != NULL) {
        Item* it = gobj->user_data;
        itKoopaFlame_Attributes* attrs =
            it->xC4_article_data->x4_specialAttributes;
        it->xDAC_itcmd_var0 = it->xDB0_itcmd_var1 = it->xDB4_itcmd_var2 =
            it->xDB8_itcmd_var3 = 0;
        it_80275158(gobj, (it->xDD4_itemVar.koopaflame.x2C_lifetime =
                               attrs->x0_lifetime));
        it->xDD4_itemVar.koopaflame.x0_pos = *pos;
        it->xDD4_itemVar.koopaflame.x34_base_scale = 0.0f;
        switch (it->kind) {
        case It_Kind_Koopa_Flame:
            it->xDD4_itemVar.koopaflame.x38_base_speed =
                base_speed / (float) ftKp_SpecialLw_80134DE0(it->owner);
            it->xDD4_itemVar.koopaflame.x3C_scale =
                scale / (float) ftKp_SpecialLw_80134E1C(it->owner);
            break;
        case It_Kind_Kirby_KoopaFlame:
            it->xDD4_itemVar.koopaflame.x38_base_speed =
                base_speed / (float) ftKb_SpecialNKp_800FA83C(it->owner);
            it->xDD4_itemVar.koopaflame.x3C_scale =
                scale / (float) ftKb_SpecialNKp_800FA878(it->owner);
            break;
        default:
            break;
        }
        rng = HSD_Randf();
        min = attrs->x8_min_speed;
        range = attrs->xC_max_speed - min;
        it->xDD4_itemVar.koopaflame.x28_speed =
            it->xDD4_itemVar.koopaflame.x38_base_speed * (range * rng + min);
        rng = HSD_Randf();
        range = attrs->x14_max_angle - attrs->x10_min_angle;
        it->xDD4_itemVar.koopaflame.x24_angle =
            range * rng + attrs->x10_min_angle;
        it->xDD4_itemVar.koopaflame.x24_angle =
            (it->facing_dir == 1.0f) ? it->xDD4_itemVar.koopaflame.x24_angle
                                     : -it->xDD4_itemVar.koopaflame.x24_angle;
        clamp_angle(&it->xDD4_itemVar.koopaflame.x24_angle);
        it->xDD4_itemVar.koopaflame.x40_frame_counter = 0;
        it->xDD4_itemVar.koopaflame.x30 = 0;
        it->xDD4_itemVar.koopaflame.x44_spawned = false;
        it->xDD4_itemVar.koopaflame.x48_gfx = gfx;
        it->xDD4_itemVar.koopaflame.xC_direction.x = it->facing_dir;
        it->xDD4_itemVar.koopaflame.xC_direction.y =
            it->xDD4_itemVar.koopaflame.xC_direction.z = 0;
        it->xDCC_flag.b3 = 0;
        itKoopaFlame_Setup(gobj, parent, gfx);
    }
    return gobj;
}

void itKoopaFlame_Setup(Item_GObj* gobj_i, Fighter_GObj* gobj_f, int unk)
{
    Item* it = GET_ITEM(gobj_i);
    char pad_stack[0x19C]; // PAD_STACK doesn't work here
    Vec vec;
    char pad_stack_2[0x14];
    it_8026B3A8(gobj_i);
    it->xDC8_word.flags.x13 = 0;
    it_80272940(gobj_i);
    Item_80268E5C(gobj_i, 0, ITEM_ANIM_UPDATE);
    vec = it->pos;
    Item_802694CC(gobj_i);
    itKoopaFlame_UnkMotion0_Phys(gobj_i);
    it->pos.x -= it->x40_vel.x;
    it->pos.y -= it->x40_vel.y;
    it_8026D9A0(gobj_i);
    it->pos = vec;
    db_80225DD8(gobj_i, gobj_f);
}

bool itKoopaFlame_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    itKoopaFlame_Attributes* attrs =
        it->xC4_article_data->x4_specialAttributes;
    HSD_JObj* jobj = HSD_GObjGetHSDObj(gobj); // GET_JOBJ does not work here!
    Vec vec;
    if (it->x5D4_hitboxes[0].hit.state != HitCapsule_Disabled) {
        if (it->xDD4_itemVar.koopaflame.x34_base_scale == 0.0f) {
            it->xDD4_itemVar.koopaflame.x34_base_scale =
                it->x5D4_hitboxes[0].hit.scale;
        }
        it->x5D4_hitboxes[0].hit.scale =
            it->xDD4_itemVar.koopaflame.x34_base_scale *
            it->xDD4_itemVar.koopaflame.x3C_scale;
    }
    vec.x = vec.y = vec.z = it->xDD4_itemVar.koopaflame.x3C_scale;
    HSD_JObjSetScale(jobj, &vec);
    it->xDD4_itemVar.koopaflame.x40_frame_counter += 1;
    if (it->xDD4_itemVar.koopaflame.x40_frame_counter >
        attrs->x4_hitbox_lifetime)
    {
        it_802725D4(gobj);
    }
    if (!it->xDD4_itemVar.koopaflame.x44_spawned) {
        it->xDD4_itemVar.koopaflame.x44_spawned = true;
        switch (it->kind) {
        case It_Kind_Koopa_Flame:
            efSync_Spawn(1243 + it->xDD4_itemVar.koopaflame.x48_gfx, gobj,
                         jobj);
            break;
        case It_Kind_Kirby_KoopaFlame:
            efSync_Spawn(1189 + it->xDD4_itemVar.koopaflame.x48_gfx, gobj,
                         jobj);
            break;
        default:
            break;
        }
    }
    return it_80273130(gobj);
}

void itKoopaFlame_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    PAD_STACK(4);
    it->xDD4_itemVar.koopaflame.x0_pos = it->pos;
    it->xDD4_itemVar.koopaflame.x18_vel.x = it->x40_vel.x =
        it->xDD4_itemVar.koopaflame.x28_speed *
        sinf(it->xDD4_itemVar.koopaflame.x24_angle);
    it->xDD4_itemVar.koopaflame.x18_vel.y = it->x40_vel.y =
        it->xDD4_itemVar.koopaflame.x28_speed *
        cosf(it->xDD4_itemVar.koopaflame.x24_angle);
    it->xDD4_itemVar.koopaflame.x18_vel.z = it->x40_vel.z = 0.0f;
    lbVector_Normalize(&it->xDD4_itemVar.koopaflame.x18_vel);
}

bool itKoopaFlame_UnkMotion0_Coll(Item_GObj* gobj)
{
    int flags;
    Item* it = GET_ITEM(gobj);
    int flags2;
    PAD_STACK(0x1E0);
    clamp_angle(&it->xDD4_itemVar.koopaflame.x24_angle);
    it->x378_itemColl.ecb_source.up = 3.0f;
    it->x378_itemColl.ecb_source.down = 3.0f;
    it->x378_itemColl.ecb_source.front = 3.0f;
    it->x378_itemColl.ecb_source.back = 3.0f;
    flags = 0;
    it_8026D9A0(gobj);
    if (it->x378_itemColl.env_flags & Collide_FloorMask) {
        flags |= itkpf_Floor;
    }
    if (it->x378_itemColl.env_flags & Collide_CeilingMask) {
        flags |= itkpf_Ceiling;
    }
    if (it->x378_itemColl.env_flags & Collide_LeftWallMask) {
        flags |= itkpf_LeftWall;
    }
    if (it->x378_itemColl.env_flags & Collide_RightWallMask) {
        flags |= itkpf_RightWall;
    }
    if ((flags2 = flags) != 0) {
        itKoopaFlame_Update_Direction(gobj, flags2);
        itKoopaFlame_Update_Angle(gobj, flags2);
    }
    return false;
}

bool it_2725_Logic111_DmgDealt(Item_GObj* gobj)
{
    return false;
}

bool it_2725_Logic111_Reflected(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    it->xDD4_itemVar.koopaflame.x24_angle += M_PI;
    clamp_angle(&it->xDD4_itemVar.koopaflame.x24_angle);
    it->facing_dir = -it->facing_dir;
    it->x40_vel.x = -it->x40_vel.x;
    it->x40_vel.y = -it->x40_vel.y;
    return false;
}

bool it_2725_Logic111_Clanked(Item_GObj* gobj)
{
    return false;
}

bool it_2725_Logic111_Absorbed(Item_GObj* gobj)
{
    efLib_DestroyAll(gobj);
    return true;
}

bool it_2725_Logic111_ShieldBounced(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    lbVector_Mirror(&it->x40_vel, &it->xC58);
    it->x40_vel.z = 0.0f;
    it->xDD4_itemVar.koopaflame.x24_angle =
        atan2f(it->x40_vel.y, it->x40_vel.x);
    clamp_angle(&it->xDD4_itemVar.koopaflame.x24_angle);
    return false;
}

bool it_2725_Logic111_HitShield(Item_GObj* gobj)
{
    return false;
}

void it_2725_Logic111_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
