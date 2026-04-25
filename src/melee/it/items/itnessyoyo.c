#include "itnessyoyo.h"

#include <placeholder.h>

#include "ft/chara/ftNess/ftNs_AttackHi4.h"
#include "ft/ftlib.h"
#include "ft/inlines.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/items/itlinkhookshot.h"
#include "it/itYoyo.h"
#include "lb/lb_00B0.h"
#include "lb/lbvector.h"
#include "mp/mpcoll.h"

#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjuserdata.h>
#include <MSL/math_ppc.h>

void it_802BE598(Item_GObj* gobj)
{
    it_8026B724(gobj);
}

void it_802BE5B8(Item_GObj* gobj)
{
    it_8026B73C(gobj);
}

void it_802BE5D8(void* arg, float frame)
{
    HSD_GObj* gobj = arg;
    Item* ip = gobj->user_data;
    itYoyoAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    HSD_JObj* jobj = ip->xDD4_itemVar.nessyoyo.x18;
    HSD_JObjRemoveAnimAll(jobj);
    HSD_JObjAddAnimAll(jobj, NULL, attrs->x58_yoyo_matanim, NULL);
    lb_8000BA0C(jobj, 1.0F);
    HSD_JObjReqAnimAll(jobj, frame);
    HSD_JObjAnimAll(jobj);
}

extern const Vec3 it_803B8698;

HSD_GObj* it_802BE65C(Item* ip, HSD_JObj* bone_jobj)
{
    Vec3 zero_vel = it_803B8698;
    ItemLink* prev_link = NULL;
    ItemLink* head_link = NULL;
    ItemLink* tail_link = NULL;
    HSD_GObj* result = NULL;
    itYoyoAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    s32 count = attrs->x0_CHARGE_SPAWN_POS;
    int i;

    for (i = 0; i < count; i++) {
        HSD_GObj* link_gobj = GObj_Create(7, 0xA, 0);
        ItemLink* link;

        if (link_gobj == NULL) {
            while (prev_link != NULL) {
                HSD_GObjPLink_80390228(prev_link->gobj);
                prev_link = prev_link->next;
            }
            return NULL;
        }

        link = HSD_ObjAlloc(&item_link_alloc_data);
        it_80275328(link_gobj, link);
        GObj_InitUserData(link_gobj, 6, it_802A2474, link);

        if (i == 0) {
            link->next = NULL;
            head_link = link;
            link->jobj = bone_jobj;
            link->gobj = link_gobj;
            link->vel = zero_vel;
            link->pos = ip->pos;
            link->x2C_b0 = false;
            it_802A24D0(link, 1.0f);
            HSD_GObjObject_80390A70(
                link_gobj, HSD_GObj_804D7849,
                HSD_JObjLoadJoint(attrs->x50_string_joint));
            GObj_SetupGXLink(link_gobj, it_802A24A0, 6, 0);
        } else if (i == count - 1) {
            prev_link->prev = link;
            link->prev = NULL;
            tail_link = link;
            link->next = prev_link;
            link->jobj = bone_jobj;
            link->gobj = link_gobj;
            link->vel = zero_vel;
            link->pos = ip->pos;
            link->x2C_b0 = true;
            it_802A24D0(link, 2.0f * ftLib_80086A0C(ip->owner));
            {
                HSD_JObj* jobj = HSD_JObjLoadJoint(attrs->x54_yoyo_joint);
                HSD_GObjObject_80390A70(link_gobj, HSD_GObj_804D7849, jobj);
                GObj_SetupGXLink(link_gobj, HSD_GObj_JObjCallback, 6, 0);
                ip->xDD4_itemVar.nessyoyo.x18 = jobj;
                result = link_gobj->hsd_obj;
            }
        } else {
            prev_link->prev = link;
            link->next = prev_link;
            link->jobj = bone_jobj;
            link->gobj = link_gobj;
            link->vel = zero_vel;
            link->pos = ip->pos;
            link->x2C_b0 = false;
            it_802A24D0(link, 1.0f);
            HSD_GObjObject_80390A70(
                link_gobj, HSD_GObj_804D7849,
                HSD_JObjLoadJoint(attrs->x50_string_joint));
            GObj_SetupGXLink(link_gobj, it_802A24A0, 6, 0);
        }
        prev_link = link;
    }
    ip->xDD4_itemVar.nessyoyo.x8 = tail_link;
    ip->xDD4_itemVar.nessyoyo.xC = head_link;
    return result;
}

void it_802BE958(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    if (ip != NULL) {
        if (gobj != NULL) {
            if (ip->owner != NULL) {
                ftNs_AttackHi4_YoyoItemSetFlag(ip->owner);
            }
            ip->owner = NULL;
            {
                ItemLink* link = ip->xDD4_itemVar.nessyoyo.x8;
                while (link != NULL) {
                    HSD_GObj* gobj = link->gobj;
                    link = link->next;
                    HSD_GObjPLink_80390228(gobj);
                }
            }
        }
        Item_8026A8EC(gobj);
    }
}

HSD_GObj* it_802BE9D8(HSD_GObj* owner, f32 facing_dir, Vec3* pos, s32 action)
{
    SpawnItem spawn;
    Item_GObj* gobj;

    spawn.kind = It_Kind_Ness_Yoyo;
    spawn.prev_pos = *pos;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = owner;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;
    gobj = Item_80268B18(&spawn);
    if (gobj != NULL) {
        Item* ip = GET_ITEM(gobj);
        Fighter* fp;
        HSD_JObj* yoyo_jobj;
        itYoyoAttributes* attrs;

        ip->xDD4_itemVar.nessyoyo.x10 = owner;
        ip->xDD4_itemVar.nessyoyo.x0 = action;
        if (ip->xDD4_itemVar.nessyoyo.x0 == 0x159) {
            ip->facing_dir *= -1.0f;
        }
        fp = owner->user_data;
        it_802BE65C(ip, fp->parts[FtPart_R2ndNa].joint);
        Item_8026AB54(gobj, owner, FtPart_R2ndNa);
        ip = GET_ITEM(gobj);
        yoyo_jobj = ip->xDD4_itemVar.nessyoyo.x18;
        attrs = ip->xC4_article_data->x4_specialAttributes;
        HSD_JObjRemoveAnimAll(yoyo_jobj);
        HSD_JObjAddAnimAll(yoyo_jobj, NULL, attrs->x58_yoyo_matanim, NULL);
        lb_8000BA0C(yoyo_jobj, 1.0f);
        HSD_JObjReqAnimAll(yoyo_jobj, 0.0f);
        HSD_JObjAnimAll(yoyo_jobj);
    }
    return gobj;
}

void itNessyoyo_UnkMotion0_Phys(Item_GObj* gobj)
{
    it_802BF900(GET_ITEM(gobj));
}

extern const f32 it_804DD150;

void itNessyoyo_UnkMotion1_Phys(Item_GObj* gobj)
{
    Vec3 pos;
    f32 pad[1];
    Mtx m;
    Item* ip = GET_ITEM(gobj);
    itYoyoAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    ItemLink* link1 = ip->xDD4_itemVar.nessyoyo.x8;

    PSMTXIdentity(m);
    m[0][3] = it_804DD150;
    m[1][3] = it_804DD150;
    m[2][3] = it_804DD150;
    HSD_JObjSetupMatrix(link1->jobj);
    PSMTXConcat(link1->jobj->mtx, m, m);
    pos.x = m[0][3];
    pos.y = m[1][3];
    pos.z = m[2][3];
    it_802BF28C(link1, &pos, attrs, ip);
    it_802BFAFC(ip, &pos);
}

void itNessyoyo_UnkMotion2_Phys(Item_GObj* gobj)
{
    Vec3 pos;
    f32 pad[1];
    Mtx m;
    Item* ip = GET_ITEM(gobj);
    itYoyoAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    ItemLink* link1 = ip->xDD4_itemVar.nessyoyo.x8;

    PSMTXIdentity(m);
    m[0][3] = it_804DD150;
    m[1][3] = it_804DD150;
    m[2][3] = it_804DD150;
    HSD_JObjSetupMatrix(link1->jobj);
    PSMTXConcat(link1->jobj->mtx, m, m);
    pos.x = m[0][3];
    pos.y = m[1][3];
    pos.z = m[2][3];
    it_802BF4A0(link1, &pos, attrs, ip);
    it_802BFAFC(ip, &pos);
}

void itNessyoyo_UnkMotion3_Phys(Item_GObj* gobj)
{
    Vec3 pos;
    Vec3 zero_vec;
    f32 pad[1];
    Mtx m;
    Item* ip = GET_ITEM(gobj);
    itYoyoAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    ItemLink* link2 = ip->xDD4_itemVar.nessyoyo.xC;

    PSMTXIdentity(m);
    m[0][3] = it_804DD150;
    m[1][3] = it_804DD150;
    m[2][3] = it_804DD150;
    HSD_JObjSetupMatrix(link2->jobj);
    PSMTXConcat(link2->jobj->mtx, m, m);
    pos.x = m[0][3];
    pos.y = m[1][3];
    pos.z = m[2][3];
    if (it_802BF800(link2, &pos, attrs, ip, ip->xDD4_itemVar.nessyoyo.x4) != 0)
    {
        zero_vec.z = it_804DD150;
        zero_vec.y = it_804DD150;
        zero_vec.x = it_804DD150;
        it_802C0010(gobj, &zero_vec);
        {
            HSD_GObj* owner = ip->xDD4_itemVar.nessyoyo.x10;
            ItemLink* link1 = ip->xDD4_itemVar.nessyoyo.x8;
            Fighter* fp = owner->user_data;
            link1->pos = fp->fv.ns.yoyo_hitbox_pos;
        }
    }
    it_802BFAFC(ip, &pos);
}

static inline void itNessyoyo_UnkMotion3_Anim_Cleanup(Item_GObj* gobj)
{
    if (gobj != NULL) {
        Item* ip = GET_ITEM(gobj);
        if (ip->owner != NULL) {
            ftNs_AttackHi4_YoyoItemSetFlag(ip->owner);
        }
        ip->owner = NULL;
        {
            ItemLink* link = ip->xDD4_itemVar.nessyoyo.x8;
            while (link != NULL) {
                HSD_GObj* tmp = link->gobj;
                link = link->next;
                HSD_GObjPLink_80390228(tmp);
            }
        }
    }
}

bool itNessyoyo_UnkMotion3_Anim(Item_GObj* gobj)
{
    bool should_cleanup;
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = ip->xDD4_itemVar.nessyoyo.x18;
    Fighter* fp = (ip->xDD4_itemVar.nessyoyo.x10)->user_data;
    HSD_JObj* child = HSD_JObjGetChild(jobj);

    if (child != NULL) {
        f32 rot = HSD_JObjGetRotationX(child) + fp->fv.ns.x223C;
        HSD_JObjSetRotationX(child, rot);
    }
    {
        HSD_GObj* owner = GET_ITEM(gobj)->owner;
        if (owner != NULL) {
            enum_t action = ftLib_80086C0C(owner);
            if (action >= 0x156 && action <= 0x15B) {
                should_cleanup = false;
            } else {
                should_cleanup = true;
            }
        } else {
            should_cleanup = true;
        }
    }
    if (should_cleanup) {
        itNessyoyo_UnkMotion3_Anim_Cleanup(gobj);
        return true;
    }
    return false;
}

s32 it_802BF030(ItemLink* link, s32 arg1, f32 offset)
{
    CollData* coll = &link->coll_data;

    link->coll_data.last_pos = link->coll_data.cur_pos;
    link->coll_data.cur_pos = link->pos;
    if (mpColl_800471F8(coll)) {
        if (!link->x2C_b1 && arg1 != 0 && !link->x2C_b2) {
            link->x2C_b2 = true;
        }
        link->x2C_b1 = true;
    } else {
        link->x2C_b1 = false;
    }
    {
        s32 env = coll->env_flags;
        if (env & 0x18000) {
            coll->cur_pos.x = link->pos.x;
        } else if (env & 0xFFF) {
            if (link->next != NULL && link->next->x2C_b0 && link->prev != NULL)
            {
                coll->cur_pos.y += offset;
            }
        }
    }
    link->pos = coll->cur_pos;
    return coll->env_flags & 0x18FFF;
}

void it_802BF180(ItemLink* cur, Vec3* target, itYoyoAttributes* attrs,
                 f32 length)
{
    f32 pad_top[4];
    Vec3 dir;
    f32 pad_bottom[1];
    ItemLink* prev = cur->prev;

    it_802A3C98(&cur->pos, target, &dir);
    cur->pos.x = (dir.x * length) + target->x;
    cur->pos.y = (dir.y * length) + target->y;
    cur->pos.z = (dir.z * length) + target->z;
    while (prev != NULL) {
        prev->vel.y = 0.0f;
        it_802A4420(prev);
        it_802A43EC(prev);
        it_802A3D90(prev);
        if (it_802A3C98(&prev->pos, &cur->pos, &dir) > length) {
            prev->pos.x = (dir.x * length) + cur->pos.x;
            prev->pos.y = (dir.y * length) + cur->pos.y;
            prev->pos.z = (dir.z * length) + cur->pos.z;
        }
        cur = prev;
        prev = prev->prev;
    }
}

s32 it_802BF28C(ItemLink* link, Vec3* target, itYoyoAttributes* attrs,
                Item* ip)
{
    Vec3 dir;
    Vec3 dir2;
    f32 min_len = attrs->x10_UNK1 * ftLib_80086A0C(ip->owner);
    Fighter* fp = GET_FIGHTER(ip->xDD4_itemVar.nessyoyo.x10);
    ItemLink* cur = link;
    ItemLink* next = cur->next;
    f32 max_len = attrs->xC_SIZE * ftLib_80086A0C(ip->owner);
    PAD_STACK(8);

    cur->pos = fp->fv.ns.yoyo_hitbox_pos;
    cur->vel.z = 0.0f;
    cur->vel.y = 0.0f;
    cur->vel.x = 0.0f;

    while (next != NULL) {
        if (next->x2C_b0) {
            f32 dist;
            next->pos = *target;
            dist = it_802A3C98(&next->pos, &cur->pos, &dir);
            if (dist > max_len) {
                next->pos.x = (dir.x * max_len) + cur->pos.x;
                next->pos.y = (dir.y * max_len) + cur->pos.y;
                next->pos.z = (dir.z * max_len) + cur->pos.z;
            } else if (dist < min_len) {
                if (it_802A3C98(&next->pos, target, &dir2) <= 0.1f) {
                    next->x2C_b0 = false;
                } else {
                    next->pos.x = (dir.x * min_len) + cur->pos.x;
                    next->pos.y = (dir.y * min_len) + cur->pos.y;
                    next->pos.z = (dir.z * min_len) + cur->pos.z;
                }
            }
        } else {
            if (it_802A3C98(target, &cur->pos, &dir) > max_len) {
                next->pos.x = (dir.x * max_len) + cur->pos.x;
                next->pos.y = (dir.y * max_len) + cur->pos.y;
                next->pos.z = (dir.z * max_len) + cur->pos.z;
                next->x2C_b0 = true;
            } else {
                return 0;
            }
        }
        cur = next;
        next = next->next;
    }
    return 2;
}

void it_802BF4A0(ItemLink* link, Vec3* target, itYoyoAttributes* attrs,
                 Item* ip)
{
    Vec3 dir;
    Vec3 dir2;
    ItemLink* cur = link;
    ItemLink* next = link->next;
    ItemLink* tail;
    ItemLink* prev;
    f32 vel_x;
    f32 vel_y;
    f32 abs_vel;
    s32 coll_flags;
    s32 count = 0;
    f32 size;

    ftLib_80086A0C(ip->owner);
    vel_x = link->vel.x;
    size = attrs->xC_SIZE * ftLib_80086A0C(ip->owner);

    if (vel_x < 0.0f) {
        vel_x = -vel_x;
    }
    if (vel_x < attrs->x2C_UNK3_MOD) {
        link->vel.x += attrs->x28_YOYO_PULL_STRENGTH * ip->facing_dir;
    } else {
        link->vel.x = attrs->x2C_UNK3_MOD * ip->facing_dir;
    }

    vel_y = link->vel.y;
    if (vel_y < 0.0f) {
        vel_y = -vel_y;
    }
    if (vel_y < attrs->x38_GRAVITY_MOD) {
        link->vel.y -= attrs->x34_GRAVITY;
    } else {
        link->vel.y = -attrs->x38_GRAVITY_MOD;
    }

    it_802A4420(cur);
    coll_flags = it_802BF030(cur, 0, size);
    if (coll_flags & 0x18000) {
        link->coll_data.cur_pos.y += 0.001f;
        link->pos.y = link->coll_data.cur_pos.y;
        if (link->vel.y < 0.0f) {
            link->vel.y = 0.0f;
        }
    }

    while (next != NULL) {
        s32 charge_len;

        count++;
        if (next->x2C_b0) {
            next->vel.y -= attrs->x3C_YOYO_PULL_STRENGTH_2;
            it_802A4420(next);
            it_802BF030(cur, 0, size);
            if (it_802A3C98(&next->pos, &cur->pos, &dir) > size) {
                next->pos.x = (dir.x * size) + cur->pos.x;
                next->pos.y = (dir.y * size) + cur->pos.y;
                next->pos.z = (dir.z * size) + cur->pos.z;
            }
            it_802A43EC(next);
            it_802A42F4(next, 1.5f + target->y);
        } else {
            if (ip->xDD4_itemVar.nessyoyo.x0 == 0x156) {
                charge_len = attrs->x4_UPSMASH_CHARGE_STRING_LENGTH;
            } else {
                charge_len = attrs->x8_DOWNSMASH_CHARGE_STRING_LENGTH;
            }
            if (count > charge_len) {
                next->pos = *target;
            } else if (it_802A3C98(target, &cur->pos, &dir) > size) {
                next->pos.x = (dir.x * size) + cur->pos.x;
                next->pos.y = (dir.y * size) + cur->pos.y;
                next->pos.z = (dir.z * size) + cur->pos.z;
                next->x2C_b0 = true;
                it_802A43B8(next);
            } else if (coll_flags & 0xFFF) {
                break;
            }
        }
        cur = next;
        next = next->next;
    }

    tail = cur;
    prev = cur->prev;
    it_802A3C98(&tail->pos, target, &dir2);
    cur->pos.x = (dir2.x * size) + target->x;
    cur->pos.y = (dir2.y * size) + target->y;
    cur->pos.z = (dir2.z * size) + target->z;

    while (prev != NULL) {
        if (it_802A3C98(&prev->pos, &tail->pos, &dir2) > size) {
            prev->pos.x = (dir2.x * size) + tail->pos.x;
            prev->pos.y = (dir2.y * size) + tail->pos.y;
            prev->pos.z = (dir2.z * size) + tail->pos.z;
        }
        tail = prev;
        prev = prev->prev;
    }

    link->vel.x *= 0.9f;
}

s32 it_802BF800(ItemLink* cur, Vec3* pos, itYoyoAttributes* attrs, Item* ip,
                f32 dist)
{
    Vec3 dir;
    ItemLink* prev;
    f32 size = attrs->xC_SIZE * ftLib_80086A0C(ip->owner);
    f32 len;
    f32 step;

    prev = cur->prev;

    while (prev != NULL && !cur->x2C_b0) {
        cur = prev;
        prev = prev->prev;
    }
    len = it_802A3C98(&cur->pos, pos, &dir);
    while (prev != NULL && dist > len) {
        cur->x2C_b0 = false;
        len = it_802A3C98(&prev->pos, pos, &dir);
        cur = prev;
        prev = prev->prev;
    }
    step = len - dist;
    if (step > size) {
        step = size;
    }
    it_802BF180(cur, pos, attrs, step);
    if (prev != NULL) {
        return 0;
    }
    return 1;
}

extern const Vec3 it_803B86A4;

void it_802BF900(Item* ip)
{
    Mtx trans;
    Mtx scale;
    ItemLink* link1 = ip->xDD4_itemVar.nessyoyo.x8;
    HSD_JObj* target = (HSD_JObj*) link1->gobj->hsd_obj;
    Vec3 offset = it_803B86A4;
    f32 scl = ftLib_80086A0C(ip->owner);

    HSD_JObjSetupMatrix(link1->jobj);
    PSMTXIdentity(trans);
    trans[0][3] = offset.x * scl;
    trans[1][3] = offset.y * scl;
    trans[2][3] = offset.z * scl;
    PSMTXConcat(link1->jobj->mtx, trans, trans);
    PSMTXIdentity(scale);
    scale[0][0] *= scl;
    scale[1][0] *= scl;
    scale[2][0] *= scl;
    scale[0][1] *= scl;
    scale[1][1] *= scl;
    scale[2][1] *= scl;
    scale[0][2] *= scl;
    scale[1][2] *= scl;
    scale[2][2] *= scl;
    PSMTXConcat(trans, scale, trans);
    HSD_JObjCopyMtx(target, trans);
    target->flags |=
        JOBJ_USER_DEF_MTX | JOBJ_MTX_INDEP_PARENT | JOBJ_MTX_INDEP_SRT;
    HSD_JObjSetMtxDirty(target);
}

void it_802BFAFC(Item* ip, Vec3* target)
{
    ItemLink* link = ip->xDD4_itemVar.nessyoyo.xC;

    while (!link->x2C_b0) {
        link = link->prev;
    }

    while (link != NULL) {
        Vec3 next_pos;
        Vec3 prev_pos;
        Vec3 link_pos;
        Vec3 dir;
        HSD_JObj* jobj;
        Mtx m;
        f32 scale;

        if (link->next != NULL) {
            if (link->next->x2C_b0) {
                next_pos = link->next->pos;
            } else {
                next_pos = *target;
            }
        } else {
            next_pos = *target;
        }

        if (link->prev != NULL) {
            prev_pos = link->prev->pos;
        } else {
            prev_pos = link->pos;
        }

        jobj = link->gobj->hsd_obj;
        link_pos = link->pos;
        HSD_JObjSetTranslate(jobj, &link_pos);

        dir.x = prev_pos.x - next_pos.x;
        dir.y = prev_pos.y - next_pos.y;
        dir.z = prev_pos.z - next_pos.z;
        lbVector_Normalize(&dir);

        if (jobj == ip->xDD4_itemVar.nessyoyo.x18) {
            if (ip->facing_dir == 1.0f) {
                dir.x = 1.0f;
            } else {
                dir.x = -1.0f;
            }
            dir.z = 0.0f;
            dir.y = 0.0f;
        }

        if (jobj == ip->xDD4_itemVar.nessyoyo.x18) {
            Fighter* fp = ip->xDD4_itemVar.nessyoyo.x10->user_data;
            fp->fv.ns.yoyo_hitbox_pos = link->pos;
        }

        it_802A6DC8(jobj, &link_pos, &dir);

        if (jobj != ip->xDD4_itemVar.nessyoyo.x18) {
            scale = ((itYoyoAttributes*)
                         ip->xC4_article_data->x4_specialAttributes)
                        ->xC_SIZE;
        } else {
            scale = 1.0f;
        }
        scale *= ftLib_80086A0C(ip->owner);
        PSMTXCopy(jobj->mtx, m);
        m[0][0] *= scale;
        m[1][0] *= scale;
        m[2][0] *= scale;
        m[0][1] *= scale;
        m[1][1] *= scale;
        m[2][1] *= scale;
        m[0][2] *= scale;
        m[1][2] *= scale;
        m[2][2] *= scale;
        PSMTXCopy(m, jobj->mtx);

        link = link->prev;
    }
}

void itNessYoyo_Logic59_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

void it_802BFE5C(Item_GObj* gobj, Vec3* pos, float unused)
{
    Item* ip = GET_ITEM(gobj);
    ItemLink* link = ip->xDD4_itemVar.nessyoyo.x8;
    float vel_x;
    link->vel = *pos;
    vel_x = link->vel.x;
    if (vel_x < 0.0f) {
        vel_x = -vel_x;
    }
    link->vel.x = ip->facing_dir * vel_x;
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

static inline float my_sqrtf(float x)
{
    static const double _half = .5;
    static const double _three = 3.0;

    u8 _[12] = { 0 };

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

#define HYPOT(x, y) my_sqrtf((x) * (x) + (y) * (y))

void it_802BFEC4(Item_GObj* gobj)
{
    u8 _pad[16];
    Mtx m;
    Item* ip = GET_ITEM(gobj);
    ItemLink* link2 = ip->xDD4_itemVar.nessyoyo.xC;
    ItemLink* link1 = ip->xDD4_itemVar.nessyoyo.x8;

    PSMTXIdentity(m);
    m[0][3] = it_804DD150;
    m[1][3] = it_804DD150;
    m[2][3] = it_804DD150;
    HSD_JObjSetupMatrix(link2->jobj);
    PSMTXConcat(link2->jobj->mtx, m, m);
    ip->xDD4_itemVar.nessyoyo.x4 =
        HYPOT(link1->pos.x - m[0][3], link1->pos.y - m[1][3]);
    ip->xDD4_itemVar.nessyoyo.x4 *= 0.1f;
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
}

void it_802C0010(Item_GObj* gobj, Vec3* vel)
{
    f32 pad_top[2];
    Vec3 pos;
    f32 pad_mid[2];
    Mtx m;
    f32 pad_bottom[2];
    ItemLink* link1 = GET_ITEM(gobj)->xDD4_itemVar.nessyoyo.x8;

    PSMTXIdentity(m);
    m[0][3] = it_804DD150;
    m[1][3] = it_804DD150;
    m[2][3] = it_804DD150;
    HSD_JObjSetupMatrix(link1->jobj);
    PSMTXConcat(link1->jobj->mtx, m, m);
    pos.x = m[0][3];
    pos.y = m[1][3];
    pos.z = m[2][3];
    link1->pos = pos;
    link1->coll_data.cur_pos = link1->pos;
    link1->coll_data.last_pos = link1->coll_data.cur_pos;
    link1->x2C_b0 = true;
    link1->vel = *vel;
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

#ifdef MWERKS_GEKKO

#pragma push
asm void it_2725_Logic59_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    // clang-format off
    nofralloc
    mflr r0
    stw r0, 0x4(r1)
    stwu r1, -0x20(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    mr r30, r4
    lwz r31, 0x2c(r3)
    bl it_8026B894
    lwz r0, 0xde4(r31)
    cmplw r0, r30
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    addi r1, r1, 0x20
    mtlr r0
    blr
    // clang-format on
}
#pragma pop

#else

void it_2725_Logic59_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    NOT_IMPLEMENTED;
}

#endif
