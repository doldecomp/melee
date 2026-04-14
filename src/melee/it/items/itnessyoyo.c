#include "itnessyoyo.h"

#include <placeholder.h>

#include "ft/chara/ftNess/ftNs_AttackHi4.h"
#include "ft/ftlib.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/item.h"
#include "it/items/itlinkhookshot.h"
#include "it/itYoyo.h"
#include "lb/lb_00B0.h"
#include "mp/mpcoll.h"

#include <baselib/gobjplink.h>
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
    HSD_JObj* jobj = ip->xDD4_itemVar.flipper.xDEC;
    HSD_JObjRemoveAnimAll(jobj);
    HSD_JObjAddAnimAll(jobj, NULL, (HSD_MatAnimJoint*) attrs->x58_UNK6, NULL);
    lb_8000BA0C(jobj, 1.0F);
    HSD_JObjReqAnimAll(jobj, frame);
    HSD_JObjAnimAll(jobj);
}

/// #it_802BE65C

void it_802BE958(void* gobj)
{
    Item* ip = ((HSD_GObj*) gobj)->user_data;
    if (ip != NULL) {
        if (gobj != NULL) {
            if (ip->owner != NULL) {
                ftNs_AttackHi4_YoyoItemSetFlag(ip->owner);
            }
            ip->owner = NULL;
            {
                ItemLink* link = (ItemLink*) ip->xDD4_itemVar.samusgrapple.x8;
                while (link != NULL) {
                    HSD_GObj* tmp = link->gobj;
                    link = link->next;
                    HSD_GObjPLink_80390228(tmp);
                }
            }
        }
        Item_8026A8EC(gobj);
    }
    PAD_STACK(8);
}

/// #it_802BE9D8

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
    ItemLink* link1 = (ItemLink*) ip->xDD4_itemVar.samusgrapple.x8;

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
    ItemLink* link1 = (ItemLink*) ip->xDD4_itemVar.samusgrapple.x8;

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
    ItemLink* link2 = (ItemLink*) ip->xDD4_itemVar.samusgrapple.xC;

    PSMTXIdentity(m);
    m[0][3] = it_804DD150;
    m[1][3] = it_804DD150;
    m[2][3] = it_804DD150;
    HSD_JObjSetupMatrix(link2->jobj);
    PSMTXConcat(link2->jobj->mtx, m, m);
    pos.x = m[0][3];
    pos.y = m[1][3];
    pos.z = m[2][3];
    if (it_802BF800(link2, &pos, attrs, ip,
                    ip->xDD4_itemVar.foxillusion.xDD8) != 0)
    {
        zero_vec.z = it_804DD150;
        zero_vec.y = it_804DD150;
        zero_vec.x = it_804DD150;
        it_802C0010(gobj, &zero_vec);
        {
            HSD_GObj* owner = (HSD_GObj*) ip->xDD4_itemVar.samusgrapple.unk_10;
            ItemLink* link1 = (ItemLink*) ip->xDD4_itemVar.samusgrapple.x8;
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
            ItemLink* link = (ItemLink*) ip->xDD4_itemVar.samusgrapple.x8;
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
    s32 should_cleanup;
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = ip->xDD4_itemVar.flipper.xDEC;
    Fighter* fp =
        ((HSD_GObj*) ip->xDD4_itemVar.samusgrapple.unk_10)->user_data;
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
                should_cleanup = 0;
            } else {
                should_cleanup = 1;
            }
        } else {
            should_cleanup = 1;
        }
    }
    if (should_cleanup != 0) {
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

/// #it_802BF28C

/// #it_802BF4A0

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
    ItemLink* link1 = (ItemLink*) ip->xDD4_itemVar.samusgrapple.x8;
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

/// #it_802BFAFC

void itNessYoyo_Logic59_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

void it_802BFE5C(Item_GObj* gobj, Vec3* pos, float unused)
{
    Item* ip = GET_ITEM(gobj);
    ItemLink* link = (ItemLink*) ip->xDD4_itemVar.samusgrapple.x8;
    float vel_x;
    link->vel = *pos;
    vel_x = link->vel.x;
    if (vel_x < 0.0f) {
        vel_x = -vel_x;
    }
    link->vel.x = ip->facing_dir * vel_x;
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

void it_802BFEC4(Item_GObj* gobj)
{
    f32 pad_top[3];
    Mtx m;
    f32 pad_bottom[3];
    Item* ip = GET_ITEM(gobj);
    ItemLink* link2 = (ItemLink*) ip->xDD4_itemVar.samusgrapple.xC;
    ItemLink* link1 = (ItemLink*) ip->xDD4_itemVar.samusgrapple.x8;

    PSMTXIdentity(m);
    m[0][3] = it_804DD150;
    m[1][3] = it_804DD150;
    m[2][3] = it_804DD150;
    HSD_JObjSetupMatrix(link2->jobj);
    PSMTXConcat(link2->jobj->mtx, m, m);
    {
        f32 dx = link1->pos.x - m[0][3];
        f32 dy = link1->pos.y - m[1][3];
        f32 dx2 = dx * dx;
        f32 dy2 = dy * dy;
        ip->xDD4_itemVar.foxillusion.xDD8 = sqrtf(dx2 + dy2);
        ip->xDD4_itemVar.foxillusion.xDD8 *= 0.1f;
    }
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
}

void it_802C0010(Item_GObj* gobj, Vec3* vel)
{
    f32 pad_top[2];
    Vec3 pos;
    f32 pad_mid[2];
    Mtx m;
    f32 pad_bottom[2];
    ItemLink* link1 = (ItemLink*) GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.x8;

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
