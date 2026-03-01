#include "itsamusmissile.h"

#include "baselib/jobj.h"
#include "baselib/mtx.h"
#include "db/db.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ftSamus/ftSs_SpecialN.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCharItems.h"
#include "it/item.h"
#include "lb/lbvector.h"

#include <math.h>
#include <trigf.h>

bool itSamusmissile_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026E71C(gobj, it_802B701C);
    return false;
}

bool itSamusmissile_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E71C(gobj, it_802B70A0);
    return false;
}

bool itSamusmissile_UnkMotion3_Anim(Item_GObj* gobj)
{
    return it_802751D8(gobj);
}

void it_802B63F8(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSamusMissileAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;

    if (ip->xD44_lifeTimer > attrs->x4 - attrs->x8) {
        ip->xDAC_itcmd_var0 = 1;
    } else {
        ip->xDAC_itcmd_var0 = 0;
    }

    if (ip->xD44_lifeTimer == attrs->x4 - attrs->x8 &&
        ip->xDD4_itemVar.samusmissile.is_smash_missile == 0)
    {
        efLib_DestroyAll(gobj);
    }

    if (ip->xD44_lifeTimer <= (attrs->x24 - attrs->x28)) {
        ip->xDB0_itcmd_var1 = 1;
    }

    if (ip->xD44_lifeTimer <= 0.0f) {
        if (ip->xDD4_itemVar.samusmissile.is_smash_missile == 0) {
            it_802B701C(gobj);
        } else {
            it_802B70A0(gobj);
        }
    } else {
        --ip->xD44_lifeTimer;
    }
}

Item_GObj* it_802B62D0(Item_GObj* gobj, Vec3* pos, int arg2, f32 facing_dir)
{
    SpawnItem spawn;
    spawn.kind = It_Kind_Samus_Missile;
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0.0f;
    it_8026BB68(gobj, &spawn.pos);
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;

    {
        Item_GObj* new_gobj = Item_80268B18(&spawn);

        if (new_gobj != NULL) {
            Item* ip = GET_ITEM(new_gobj);

            ip->xDD4_itemVar.samusmissile.is_smash_missile = arg2;
            ip->xDD4_itemVar.samusmissile.owner = ip->owner;

            if (ip->xDD4_itemVar.samusmissile.owner != NULL) {
                ip->xDD4_itemVar.samusmissile.x4 = ftSs_SpecialS_8012A068(
                    ip->xDD4_itemVar.samusmissile.owner);
            }

            if (ip->xDD4_itemVar.samusmissile.is_smash_missile == 0) {
                it_802B66A8(new_gobj);
            } else {
                it_802B6A60(new_gobj);
            }

            db_80225DD8(new_gobj, gobj);
            return new_gobj;
        }
    }

    return NULL;
}

Item_GObj* it_802B64FC(Item_GObj* gobj)
{
    Vec3 vec3;
    Vec3 vec2;
    Vec3 vec1;
    Vec3 vec0;
    HSD_GObj* temp_r3;
    HSD_GObj* temp_ret;
    Item* ip;
    f32 temp_f2;
    f32 var_f0;
    f32 var_f1;
    itSamusMissileAttributes* sa;

    ip = GET_ITEM(gobj);
    sa = ip->xC4_article_data->x4_specialAttributes;
    vec3.x = vec3.y = vec3.z = 0.0f;
    if (it_8026B634(&ip->pos, &vec3, ip->owner, ip->facing_dir) != NULL) {
        goto block_4;
    }
    temp_ret = it_8026C258(&ip->pos, ip->facing_dir);
    // var_f1 = M2C_BITWISE(f32, temp_ret);
    temp_r3 = temp_ret;
    if (temp_r3 == NULL) {
        goto block_18;
    }
    it_8026BB88(temp_r3, &vec3);
block_4:
    var_f1 = 0.0f;
    if (vec3.x != 0.0f) {
        goto block_6;
    }
    if (vec3.y == 0.0f) {
        goto block_18;
    }
block_6:
    vec2.x = ip->x40_vel.x;
    vec2.y = ip->x40_vel.y;
    vec2.z = 0.0f;
    lbVector_NormalizeXY(&vec2);
    vec1.x = vec3.x - ip->pos.x;
    vec1.y = vec3.y - ip->pos.y;
    vec1.z = 0.0f;
    lbVector_NormalizeXY(&vec1);
    var_f1 = lbVector_AngleXY(&vec2, &vec1);
    if (var_f1 < sa->x20) {
        goto block_18;
    }
    vec0.x = vec1.x;
    vec0.y = vec1.y;
    vec0.z = vec1.z;
    lbVector_Sub(&vec0, &vec2);
    if ((vec0.y > 0.001f)) {
        ip->xDD4_itemVar.samusmissile.x8 -= M2C_FIELD(sa, f32*, 0x18);
        goto block_11;
    }
    if (!(vec0.y < 0.001f)) {
        goto block_11;
    }
    ip->xDD4_itemVar.samusmissile.x8 += sa->x18;
block_11:
    var_f1 = ip->xDD4_itemVar.samusmissile.x8;
    if (!(var_f1 < 0.0f)) {
        goto block_13;
    }
    var_f0 = -var_f1;
    goto block_14;
block_13:
    var_f0 = var_f1;
block_14:
    temp_f2 = M2C_FIELD(sa, f32*, 0x1C);
    if (!(var_f0 > temp_f2)) {
        goto block_18;
    }
    if (!(var_f1 > 0.0f)) {
        goto block_17;
    }
    ip->xDD4_itemVar.samusmissile.x8 = temp_f2;
    return NULL;
    // return M2C_BITWISE(Item_GObj*, var_f1);
block_17:
    ip->xDD4_itemVar.samusmissile.x8 = -temp_f2;
block_18:
    return NULL;
    // return M2C_BITWISE(Item_GObj*, var_f1);
}

void* it_802B66A8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSamusMissileAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(0x8);

    ip->x40_vel.x = attrs->xC * ip->facing_dir;
    ip->x40_vel.y = 0.0f;

    ip->xDAC_itcmd_var0 = ip->xDB4_itcmd_var2 = ip->xDB8_itcmd_var3 = 0.0f;

    it_80275158(gobj, attrs->x4);

    ip->xDD4_itemVar.samusmissile.x8 = 0;

    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);

    return efSync_Spawn(0x485, gobj, itGetJObjGrandchild(gobj));
}

inline void isSamusmissile_MotionAnim(Item_GObj* gobj)
{
    it_802B63F8(gobj);
    {
        Item* ip = GET_ITEM(gobj);
        if (ip->xDB8_itcmd_var3 == 0U) {
            Fighter_GObj* owner = ip->xDD4_itemVar.samusmissile.owner;
            if (owner != NULL && ftSs_SpecialS_8012A068(owner) -
                                         ip->xDD4_itemVar.samusmissile.x4 >=
                                     2U)
            {
                it_2725_Logic52_DmgDealt(gobj);
            }
        }
    }
}

s32 itSamusmissile_UnkMotion0_Anim(Item_GObj* gobj)
{
    isSamusmissile_MotionAnim(gobj);
    return false;
}

static void inlineA0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSamusMissileAttributes* sa1 = ip->xC4_article_data->x4_specialAttributes;
    Vec3 vec;
    vec.x = sa1->xC * ip->facing_dir;
    vec.y = 0.0f;
    vec.z = 0.0f;
    lbVector_Rotate(&vec, 4,
                    ip->xDD4_itemVar.samusmissile.x8 * -ip->facing_dir);
    ip->x40_vel.x = vec.x;
    ip->x40_vel.y = vec.y;
}

void itSamusmissile_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSamusMissileAttributes* sa0 = ip->xC4_article_data->x4_specialAttributes;
    if (ip->xDAC_itcmd_var0 != 0) {
        it_802B64FC(gobj);
        inlineA0(gobj);
        HSD_JObjSetRotationX(HSD_JObjGetChild(GET_JOBJ(gobj)),
                             GET_ITEM(gobj)->xDD4_itemVar.samusmissile.x8);
    } else {
        if (VEC2_SQ_LEN(ip->x40_vel) > SQ(sa0->x14)) {
            ip->x40_vel.x *= sa0->x10;
            ip->x40_vel.y *= sa0->x10;
        }
        HSD_JObjSetRotationX(HSD_JObjGetChild(GET_JOBJ(gobj)),
                             GET_ITEM(gobj)->xDD4_itemVar.samusmissile.x8);
    }
}

void* it_802B6A60(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSamusMissileAttributes* attrs;
    PAD_STACK(0x8);

    attrs = ip->xC4_article_data->x4_specialAttributes;

    ip->x40_vel.x = attrs->x2C * ip->facing_dir;
    ip->x40_vel.y = 0.0f;

    ip->xDB0_itcmd_var1 = ip->xDB4_itcmd_var2 = ip->xDB8_itcmd_var3 = 0;

    it_80275158(gobj, attrs->x24);
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);

    return efSync_Spawn(1156, gobj, itGetJObjGrandchild(gobj));
}

s32 itSamusmissile_UnkMotion1_Anim(Item_GObj* gobj)
{
    isSamusmissile_MotionAnim(gobj);
    return false;
}

void itSamusmissile_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSamusMissileAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;

    if (ip->xDB0_itcmd_var1 != 0) {
        ip->x40_vel.x = attrs->x30 * ip->facing_dir + ip->x40_vel.x;
        {
            float xvel = ABS(ip->x40_vel.x);
            float maxSpeed = attrs->x34;
            if (xvel > maxSpeed) {
                if (ip->facing_dir == +1.0f) {
                    ip->x40_vel.x = +maxSpeed;
                } else {
                    ip->x40_vel.x = -maxSpeed;
                }
            }
        }
    }
}

bool it_2725_Logic52_DmgDealt(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->xDD4_itemVar.samusmissile.is_smash_missile == NULL) {
        if (ip->msid != 2) {
            it_802B701C(gobj);
        }
    } else if (ip->msid != 3) {
        it_802B70A0(gobj);
    }
    return false;
}

bool it_2725_Logic52_Clanked(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->xDD4_itemVar.samusmissile.is_smash_missile == NULL) {
        if (ip->msid != 2) {
            it_802B701C(gobj);
        }
    } else if (ip->msid != 3) {
        it_802B70A0(gobj);
    }
    return false;
}

bool it_2725_Logic52_HitShield(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->xDD4_itemVar.samusmissile.is_smash_missile == NULL) {
        if (ip->msid != 2) {
            it_802B701C(gobj);
        }
    } else if (ip->msid != 3) {
        it_802B70A0(gobj);
    }
    return false;
}

bool it_2725_Logic52_ShieldBounced(Item_GObj* arg0)
{
    Item* ip = GET_ITEM(arg0);
    HSD_JObj* jobj = GET_JOBJ(arg0);
    if (ip->xDD4_itemVar.samusmissile.is_smash_missile != 0) {
        itColl_BounceOffShield(arg0);
        {
            f32 temp_f1 = atan2f(ip->x40_vel.x, ip->x40_vel.y);
            f32 var_f31;
            if (ip->facing_dir == +1.0f) {
                var_f31 = temp_f1 - M_PI_2;
            } else {
                var_f31 = 270 * deg_to_rad - temp_f1;
            }
            HSD_JObjSetRotationX(HSD_JObjGetChild(jobj), var_f31);
        }
    }
    return false;
}

bool it_2725_Logic52_Reflected(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSamusMissileAttributes* sa = ip->xC4_article_data->x4_specialAttributes;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    PAD_STACK(6 * 4);
    ip->xDB8_itcmd_var3 = 1;
    it_80273030(gobj);
    if (ip->xDD4_itemVar.samusmissile.is_smash_missile) {
        ip->x40_vel.x = sa->x2C * ip->facing_dir;
    }
    if (ip->x40_vel.y < 0.0f) {
        ip->x40_vel.y = -ip->x40_vel.y * ip->xC70;
    }
    HSD_JObjSetRotationY(jobj, (float) M_PI_2 * ip->facing_dir);
    efLib_DestroyAll(gobj);
    if (!ip->xDD4_itemVar.samusmissile.is_smash_missile) {
        efSync_Spawn(1157, gobj, itGetJObjGrandchild(gobj));
    } else {
        efSync_Spawn(1156, gobj, itGetJObjGrandchild(gobj));
    }
    return false;
}

void it_802B701C(Item_GObj* gobj)
{
    PAD_STACK(0x10);
    it_8026BB44(gobj);
    it_8026BD24(gobj);
    it_8027518C(gobj);
    it_80273454(gobj);
    efLib_DestroyAll(gobj);
    it_80272B40(gobj);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

void it_802B70A0(Item_GObj* gobj)
{
    PAD_STACK(0x10);
    it_8026BB44(gobj);
    it_8026BD24(gobj);
    it_8027518C(gobj);
    it_80273454(gobj);
    efLib_DestroyAll(gobj);
    it_80272A60(gobj);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
}

void it_2725_Logic52_EvtUnk(Item_GObj* gobj, Item_GObj* arg1)
{
    Item* ip = GET_ITEM(gobj);
    it_8026B894(gobj, arg1);
    if (ip->xDD4_itemVar.samusmissile.owner == arg1) {
        ip->xDD4_itemVar.samusmissile.owner = NULL;
    }
}
