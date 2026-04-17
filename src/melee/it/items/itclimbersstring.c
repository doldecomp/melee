#include "itclimbersstring.h"

#include "placeholder.h"

#include "dolphin/types.h"
#include "ft/chara/ftPopo/ftPp_SpecialS.h"
#include "ft/chara/ftPopo/types.h"
#include "ft/ftlib.h"
#include "ft/inlines.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCharItems.h"
#include "it/item.h"
#include "it/items/itlinkhookshot.h"
#include "lb/lbvector.h"

#include <dolphin/mtx.h>
#include <dolphin/os/OSError.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>

extern const Vec3 it_803B86B0;
extern const Vec3 it_803B86BC;

ItemStateTable it_803F76B8[] = {
    { -1, itClimbersstring_UnkMotion3_Anim, NULL, NULL },
    { -1, itClimbersstring_UnkMotion3_Anim, NULL, NULL },
    { -1, itClimbersstring_UnkMotion3_Anim, NULL, NULL },
    { -1, itClimbersstring_UnkMotion3_Anim, NULL, NULL },
};

static HSD_GObj* it_802C248C(Item* ip, HSD_JObj* jobj)
{
    itClimbersStringAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    ItemLink* prev_link;
    ItemLink* head_link;
    ItemLink* tail_link;
    HSD_GObj* result;
    Vec3 zero_vel = it_803B86B0;
    int i;
    PAD_STACK(4);

    for (i = 0; i < attrs->x0_count; i++) {
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
            link->jobj = jobj;
            link->gobj = link_gobj;
            link->vel = zero_vel;
            link->pos = ip->pos;
            link->x2C_b0 = false;
            HSD_GObjObject_80390A70(
                link_gobj, HSD_GObj_804D7849,
                HSD_JObjLoadJoint(
                    ((itClimbersStringAttributes*)
                         ip->xC4_article_data->x4_specialAttributes)
                        ->x24_joint));
            GObj_SetupGXLink(link_gobj, it_802A24A0, 6, 0);
        } else if (i == attrs->x0_count - 1) {
            prev_link->prev = link;
            link->prev = NULL;
            tail_link = link;
            link->next = prev_link;
            link->jobj = jobj;
            link->gobj = link_gobj;
            link->vel = zero_vel;
            link->pos = ip->pos;
            link->x2C_b0 = true;
            {
                HSD_JObj* tail_jobj = HSD_JObjLoadJoint(
                    ((itClimbersStringAttributes*)
                         ip->xC4_article_data->x4_specialAttributes)
                        ->x28_joint);
                HSD_GObjObject_80390A70(link_gobj, HSD_GObj_804D7849,
                                        tail_jobj);
                GObj_SetupGXLink(link_gobj, HSD_GObj_JObjCallback, 6, 0);
                ip->xDD4_itemVar.climbersstring.x14 = tail_jobj;
                result = link_gobj->hsd_obj;
            }
        } else {
            prev_link->prev = link;
            link->next = prev_link;
            link->jobj = jobj;
            link->gobj = link_gobj;
            link->vel = zero_vel;
            link->pos = ip->pos;
            link->x2C_b0 = false;
            HSD_GObjObject_80390A70(
                link_gobj, HSD_GObj_804D7849,
                HSD_JObjLoadJoint(
                    ((itClimbersStringAttributes*)
                         ip->xC4_article_data->x4_specialAttributes)
                        ->x24_joint));
            GObj_SetupGXLink(link_gobj, it_802A24A0, 6, 0);
        }
        prev_link = link;
    }
    ip->xDD4_itemVar.climbersstring.x4 = tail_link;
    ip->xDD4_itemVar.climbersstring.x8 = head_link;
    return result;
}

void it_802C2750(Item_GObj* gobj)
{
    int unused[2];
    Item* ip = GET_ITEM(gobj);
    if (ip != NULL) {
        if (gobj != NULL) {
            if (ip->owner != NULL) {
                ftPp_SpecialS_8012114C(ip->owner);
            }
            ip->owner = NULL;
            ip->xDD4_itemVar.climbersstring.xC = NULL;
            {
                ItemLink* cur;
                for (cur = ip->xDD4_itemVar.climbersstring.x4; cur != NULL;) {
                    HSD_GObj* cur_gobj = cur->gobj;
                    cur = cur->next;
                    HSD_GObjPLink_80390228(cur_gobj);
                }
            }
        }
        Item_8026A8EC(gobj);
    }
}

Item_GObj* it_802C27D4(Fighter_GObj* owner, Vec3* pos, int msid, float dir)
{
    Fighter* fp = owner->user_data;
    SpawnItem spawn;
    Item_GObj* item_gobj;
    PAD_STACK(20);

    spawn.kind = 0x71;
    spawn.prev_pos = *pos;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = owner;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = false;
    spawn.x40 = 0;
    item_gobj = Item_80268B18(&spawn);
    if (item_gobj != NULL) {
        Item* ip = GET_ITEM(item_gobj);
        ip->xDD4_itemVar.climbersstring.xC = owner;
        it_802C248C(ip, fp->parts[FtPart_L4thNb].joint);
        Item_8026AB54(item_gobj, owner, FtPart_L4thNb);
    }
    return item_gobj;
}

static void it_802C33B8(Item* ip)
{
    Mtx m;
    ItemLink* link = ip->xDD4_itemVar.climbersstring.x4;
    HSD_JObj* jobj = GET_JOBJ(link->gobj);
    Vec3 zero = it_803B86BC;

    link->x2C_b0 = false;
    HSD_JObjSetupMatrix(link->jobj);

    PSMTXIdentity(m);
    m[0][3] = zero.x;
    m[1][3] = zero.y;
    m[2][3] = zero.z;
    PSMTXConcat(link->jobj->mtx, m, m);

    HSD_JObjCopyMtx(jobj, m);
    jobj->flags |= 0x03800000;
    HSD_JObjSetMtxDirty(jobj);
}

void fn_802C28B8(Item_GObj* gobj)
{
    it_802C33B8(GET_ITEM(gobj));
}

static void fn_802C28DC(Item_GObj* gobj)
{
    Vec3 pos;
    f32 pad[1];
    Mtx m;
    Item* ip = GET_ITEM(gobj);
    itClimbersStringAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    ItemLink* link = ip->xDD4_itemVar.climbersstring.x4;

    link->x2C_b0 = true;
    PSMTXIdentity(m);
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    HSD_JObjSetupMatrix(link->jobj);
    PSMTXConcat(link->jobj->mtx, m, m);
    pos.x = m[0][3];
    pos.y = m[1][3];
    pos.z = m[2][3];
    it_802C2EC4(link, &pos, attrs, ip);
    it_802C3520(ip, &pos);
}

static void fn_802C29E8(Item_GObj* gobj)
{
    Vec3 pos;
    f32 pad[1];
    Mtx m;
    Item* ip = GET_ITEM(gobj);
    itClimbersStringAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    ItemLink* link = ip->xDD4_itemVar.climbersstring.x4;

    link->x2C_b0 = true;
    PSMTXIdentity(m);
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    HSD_JObjSetupMatrix(link->jobj);
    PSMTXConcat(link->jobj->mtx, m, m);
    pos.x = m[0][3];
    pos.y = m[1][3];
    pos.z = m[2][3];
    it_802C30E8(link, &pos, attrs, ip);
    it_802C3520(ip, &pos);
}

static void fn_802C2AF4(HSD_GObj* gobj)
{
    Vec3 pos;
    Mtx m;
    Item* ip = GET_ITEM(gobj);
    itClimbersStringAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    ItemLink* link = ip->xDD4_itemVar.climbersstring.x8;

    PSMTXIdentity(m);
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    HSD_JObjSetupMatrix(link->jobj);
    PSMTXConcat(link->jobj->mtx, m, m);
    pos.x = m[0][3];
    pos.y = m[1][3];
    pos.z = m[2][3];
    if (it_802C32D4(link, &pos, attrs, ip,
                    ip->xDD4_itemVar.climbersstring.x0) != 0)
    {
        it_2725_Logic70_PickedUp(gobj);
    }
    it_802C3520(ip, &pos);
}

void it_802C2CA8(ItemLink* link, Vec3* target,
                 itClimbersStringAttributes* attrs, f32 length)
{
    u8 _pad[8];
    Vec3 dir;
    ItemLink* prev = link->prev;

    it_802A3C98(&link->pos, target, &dir);
    link->pos.x = (dir.x * length) + target->x;
    link->pos.y = (dir.y * length) + target->y;
    link->pos.z = (dir.z * length) + target->z;
    while (prev != NULL) {
        if (prev->x2C_b0) {
            if (it_802A3C98(&prev->pos, &link->pos, &dir) > attrs->x8) {
                prev->pos.x = (dir.x * attrs->x8) + link->pos.x;
                prev->pos.y = (dir.y * attrs->x8) + link->pos.y;
                prev->pos.z = (dir.z * attrs->x8) + link->pos.z;
            }
        }
        link = prev;
        prev = prev->prev;
    }
}

void it_802C2DB0(ItemLink* cur, Vec3* target,
                 itClimbersStringAttributes* attrs, f32 length)
{
    u8 _pad[12];
    Vec3 dir;
    ItemLink* prev = cur->prev;
    PAD_STACK(4);

    it_802A3C98(&cur->pos, target, &dir);
    cur->pos.x = (dir.x * length) + target->x;
    cur->pos.y = (dir.y * length) + target->y;
    cur->pos.z = (dir.z * length) + target->z;
    while (prev != NULL) {
        prev->vel.y -= attrs->x14;
        it_802A4420(prev);
        if (it_802A3C98(&prev->pos, &cur->pos, &dir) > attrs->x8) {
            prev->pos.x = (dir.x * attrs->x8) + cur->pos.x;
            prev->pos.y = (dir.y * attrs->x8) + cur->pos.y;
            prev->pos.z = (dir.z * attrs->x8) + cur->pos.z;
        }
        cur = prev;
        prev = prev->prev;
    }
}

void it_802C3520(Item* ip, Vec3* target)
{
    HSD_JObj* jobj;
    ItemLink* link = ip->xDD4_itemVar.climbersstring.x8;
    itClimbersStringAttributes* attrs;
    Vec3 next_pos;
    Vec3 prev_pos;
    Vec3 link_pos;
    Vec3 dir;
    Mtx m;
    // PAD_STACK(8);

    while (!link->x2C_b0) {
        link = link->prev;
    }

    while (link != NULL) {
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

        jobj = GET_JOBJ(link->gobj);
        link_pos = link->pos;
        HSD_JObjSetTranslate(jobj, &link_pos);

        dir.x = prev_pos.x - next_pos.x;
        dir.y = prev_pos.y - next_pos.y;
        dir.z = prev_pos.z - next_pos.z;
        lbVector_Normalize(&dir);

        it_802A6DC8(jobj, &link_pos, &dir);

        attrs = ip->xC4_article_data->x4_specialAttributes;
        PSMTXCopy(jobj->mtx, m);
        m[0][0] *= attrs->x8;
        m[1][0] *= attrs->x8;
        m[2][0] *= attrs->x8;
        m[0][1] *= attrs->x8;
        m[1][1] *= attrs->x8;
        m[2][1] *= attrs->x8;
        m[0][2] *= attrs->x8;
        m[1][2] *= attrs->x8;
        m[2][2] *= attrs->x8;
        PSMTXCopy(m, jobj->mtx);

        link = link->prev;
    }
}

static inline void it_802C2CA8_outline(ItemLink* link, Vec3* target,
                                       itClimbersStringAttributes* attrs,
                                       f32 length)
{
    it_802C2CA8(link, target, attrs, length);
}

s32 it_802C30E8(ItemLink* link, Vec3* target,
                itClimbersStringAttributes* attrs, Item* ip)
{
    u8 _pad[8];
    Vec3 dir;
    ItemLink* cur = link;
    ItemLink* iter = link->next;
    s32 counter;
    Fighter* fp = GET_FIGHTER(ip->xDD4_itemVar.climbersstring.xC);
    PAD_STACK(8);

    link->vel.y -= 0.9f * attrs->x14;

    if (fp->fv.pp.x2240.x != 0.0f || fp->fv.pp.x2240.y != 0.0f) {
        link->pos = fp->fv.pp.x2240;
    } else {
        it_802A4420(cur);
    }

    counter = 0;
    while (iter != NULL) {
        counter++;
        if (iter->x2C_b0) {
            iter->vel.y -= attrs->x14;
            it_802A4420(iter);
            if (it_802A3C98(&iter->pos, &cur->pos, &dir) > attrs->x8) {
                iter->pos.x = (dir.x * attrs->x8) + cur->pos.x;
                iter->pos.y = (dir.y * attrs->x8) + cur->pos.y;
                iter->pos.z = (dir.z * attrs->x8) + cur->pos.z;
            }
        } else {
            if (counter > attrs->x4) {
                iter->pos = *target;
            } else {
                if (it_802A3C98(target, &cur->pos, &dir) > attrs->x8) {
                    iter->pos.x = (dir.x * attrs->x8) + cur->pos.x;
                    iter->pos.y = (dir.y * attrs->x8) + cur->pos.y;
                    iter->pos.z = (dir.z * attrs->x8) + cur->pos.z;
                    iter->x2C_b0 = true;
                } else {
                    return 0;
                }
            }
        }
        cur = iter;
        iter = iter->next;
    }

    it_802C2CA8_outline(cur, target, attrs, attrs->x8);
    link->vel.x *= 0.9f;
    return 2;
}

s32 it_802C2EC4(ItemLink* link, Vec3* target,
                itClimbersStringAttributes* attrs, Item* ip)
{
    u8 _pad[8];
    Vec3 dir;
    Vec3 dir2;
    ItemLink* cur = link;
    ItemLink* iter = link->next;
    Fighter* fp = GET_FIGHTER(ip->xDD4_itemVar.climbersstring.xC);
    PAD_STACK(4);

    if (fp->fv.pp.x2240.x != 0.0f || fp->fv.pp.x2240.y != 0.0f) {
        link->pos = fp->fv.pp.x2240;
    }
    link->vel.x = link->vel.y = link->vel.z = 0.0f;

    while (iter != NULL) {
        if (iter->x2C_b0) {
            f32 dist;
            iter->pos = *target;
            dist = it_802A3C98(&iter->pos, &cur->pos, &dir);
            if (dist > attrs->x8) {
                iter->pos.x = (dir.x * attrs->x8) + cur->pos.x;
                iter->pos.y = (dir.y * attrs->x8) + cur->pos.y;
                iter->pos.z = (dir.z * attrs->x8) + cur->pos.z;
            } else if (dist < attrs->xC) {
                if (it_802A3C98(&iter->pos, target, &dir2) <= 0.1f) {
                    iter->x2C_b0 = false;
                } else {
                    iter->pos.x = (dir.x * attrs->xC) + cur->pos.x;
                    iter->pos.y = (dir.y * attrs->xC) + cur->pos.y;
                    iter->pos.z = (dir.z * attrs->xC) + cur->pos.z;
                }
            }
        } else {
            if (it_802A3C98(target, &cur->pos, &dir) > attrs->x8) {
                iter->pos.x = (dir.x * attrs->x8) + cur->pos.x;
                iter->pos.y = (dir.y * attrs->x8) + cur->pos.y;
                iter->pos.z = (dir.z * attrs->x8) + cur->pos.z;
                iter->x2C_b0 = true;
            } else {
                return 0;
            }
        }
        cur = iter;
        iter = iter->next;
    }
    return 2;
}

bool it_802C32D4(ItemLink* link, Vec3* pos, itClimbersStringAttributes* attrs,
                 Item* ip, f32 dist)
{
    u8 _pad[16];
    Vec3 dir;
    ItemLink* prev;
    ItemLink* cur = link;
    f32 len;
    f32 step;
    f32 foo;

    prev = link->prev;
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
    foo = attrs->x8;
    step = len - dist;
    if (step > foo) {
        step = foo;
    }
    it_802C2DB0(cur, pos, attrs, step);
    if (prev != NULL) {
        return false;
    }
    return true;
}

static inline void itClimbersstring_Cleanup(Item_GObj* gobj)
{
    if (gobj != NULL) {
        Item* ip = GET_ITEM(gobj);
        if (ip->owner != NULL) {
            ftPp_SpecialS_8012114C(ip->owner);
        }
        ip->owner = NULL;
        ip->xDD4_itemVar.climbersstring.xC = NULL;
        {
            ItemLink* cur;
            for (cur = ip->xDD4_itemVar.climbersstring.x4; cur != NULL;) {
                HSD_GObj* cur_gobj = cur->gobj;
                cur = cur->next;
                HSD_GObjPLink_80390228(cur_gobj);
            }
        }
    }
}

bool itClimbersstring_UnkMotion3_Anim(Item_GObj* gobj)
{
    s32 should_cleanup;
    Item* ip = GET_ITEM(gobj);

    if (ip->owner != NULL) {
        enum_t action = ftLib_80086C0C(ip->owner);
        if (action >= 0x15B && action <= 0x164) {
            should_cleanup = 0;
        } else {
            should_cleanup = 1;
        }
    } else {
        should_cleanup = 1;
    }
    if (should_cleanup != 0) {
        itClimbersstring_Cleanup(gobj);
        return true;
    }
    return false;
    PAD_STACK(8);
}

void it_2725_Logic70_EvtUnk(Item_GObj* arg0, Item_GObj* arg1)
{
    Item* ip = GET_ITEM((HSD_GObj*) arg0);
    it_8026B894(arg0, (HSD_GObj*) arg1);
    if (ip->xDD4_itemVar.climbersstring.xC == arg1) {
        ip->xDD4_itemVar.climbersstring.xC = NULL;
    }
}

void it_802C3810(Item_GObj* gobj)
{
    Item* item;
    int unused[2];

    item = gobj->user_data;
    Item_80268E5C(gobj, 2, 2);
    it_8026BB20(gobj);
    item->on_accessory = fn_802C29E8;
}

void it_802C3864(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    u8 _pad[16];
    ItemLink* link = ip->xDD4_itemVar.climbersstring.x8;
    Mtx mtx;
    PAD_STACK(8);

    PSMTXIdentity(mtx);
    mtx[0][3] = 0.0f;
    mtx[1][3] = 0.0f;
    mtx[2][3] = 0.0f;

    {
        Item* ip2 = ip;
        HSD_JObjSetupMatrix(link->jobj);
        PSMTXConcat(link->jobj->mtx, mtx, mtx);
        ip2->xDD4_itemVar.climbersstring.x0 = 2.25f;
    }
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
    it_8026BB20(gobj);
    ip->on_accessory = fn_802C2AF4;
}

void it_802C3950(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemLink* link = ip->xDD4_itemVar.climbersstring.x4;
    Vec3 result;
    u8 _pad[8];
    Mtx mtx;
    PAD_STACK(8);

    PSMTXIdentity(mtx);
    mtx[0][3] = 0.0f;
    mtx[1][3] = 0.0f;
    mtx[2][3] = 0.0f;
    HSD_JObjSetupMatrix(link->jobj);
    PSMTXConcat(link->jobj->mtx, mtx, mtx);
    result.x = mtx[0][3];
    result.y = mtx[1][3];
    result.z = mtx[2][3];
    link->pos = result;
    link->coll_data.cur_pos = link->pos;
    link->coll_data.last_pos = link->coll_data.cur_pos;
    link->x2C_b0 = 1;
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    it_8026BB20(gobj);
    ip->on_accessory = fn_802C28DC;
}

void it_2725_Logic70_PickedUp(Item_GObj* gobj)
{
    short pad;
    void (*new_var)(Item_GObj* gobj);
    Item* ip = gobj->user_data;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    it_8026BB44(gobj);
    new_var = &fn_802C28B8;
    ip->on_accessory = *new_var;
}
