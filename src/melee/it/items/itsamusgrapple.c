#include "itsamusgrapple.h"

#include "itlinkhookshot.h"
#include "placeholder.h"

#include "baselib/forward.h"

#include "dolphin/types.h"
#include "ef/efsync.h"
#include "ft/chara/ftCommon/ftCo_AirCatch.h"
#include "ft/chara/ftCommon/ftCo_CliffJump.h"
#include "ft/chara/ftCommon/ftCo_DamageFall.h"
#include "ft/chara/ftSamus/types.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ftSamus/types.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/itCharItems.h"
#include "it/item.h"
#include "lb/lbvector.h"
#include "mp/mpcoll.h"
#include "mp/mplib.h"

#include <baselib/gobj.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/jobj.h>
#include <baselib/random.h>

extern Vec3 it_803B8674;
typedef struct {
    s32 data[5];
} itSamusGrapple_HitboxData;
extern itSamusGrapple_HitboxData it_803B8660;

static inline bool samus_grapple_fighter_compare(FtMotionId id)
{
    if ((id == 0x165) || (id == 0x166) || (id == 0xD4) || (id == 0xD6)) {
        return true;
    }
    return false;
}

static inline void samus_grapple_init_link(ItemLink* link, HSD_JObj* jobj,
                                           HSD_GObj* gobj, Vec3* pos)
{
    link->jobj = jobj;
    link->gobj = gobj;
    link->vel = *pos;
    link->pos = *pos;
    link->x2C_b0 = 0;
    link->x2C_b1 = 0;
    link->x2C_b2 = 0;
    link->coll_data.cur_pos = link->pos;
    link->coll_data.last_pos = link->coll_data.cur_pos;
    mpColl_80041EE4(&link->coll_data);
}

static inline f32 samus_grapple_calc_grav(f32 vel_y)
{
    if (HSD_Randf() > 0.9) {
        if (vel_y < 0.0) {
            return -((0.6f * HSD_Randf()) - vel_y);
        } else {
            return (0.6f * HSD_Randf()) + vel_y;
        }
    } else {
        return 0.0f;
    }
}

static inline void samus_grapple_setup_pos(ItemLink* link, Vec3* pos, Mtx m)
{
    PSMTXIdentity(m);
    HSD_JObjSetupMatrix(link->jobj);
    pos->x = link->jobj->mtx[0][3];
    pos->y = link->jobj->mtx[1][3];
    pos->z = link->jobj->mtx[2][3];
}

static inline void samus_grapple_anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemLink* link;
    HSD_JObjAnimAll(GET_JOBJ(gobj));
    link = ip->xDD4_itemVar.samusgrapple.x4;
    while (link != NULL) {
        HSD_JObjAnimAll(link->gobj->hsd_obj);
        link = link->prev;
    }
}

static inline void samus_grapple_state_sync(Fighter* fp)
{
    switch (fp->fv.ss.x2240) {
    case 0:
        if (fp->input.held_inputs & 8) {
            fp->fv.ss.x2240++;
        }
        break;
    case 1:
        if (fp->input.held_inputs & 4) {
            fp->fv.ss.x2240++;
        }
        break;
    case 2:
        if (fp->input.held_inputs & 8) {
            fp->fv.ss.x2240++;
        }
        break;
    case 3:
        if (fp->input.x668 & 0x100) {
            fp->fv.ss.x2240++;
        }
        break;
    }
}

void itSamusGrapple_Logic53_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.samusgrapple.unk_10 = NULL;
}

/// #it_802B7160

void it_802B743C(HSD_GObj* gobj, Item* ip, s32 type)
{
    itSamusGrappleAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    HSD_JObj* jobj;
    HSD_AnimJoint* anim;
    HSD_MatAnimJoint* matanim;
    HSD_ShapeAnimJoint* shapeanim;

    if (type == 0) {
        jobj = HSD_JObjLoadJoint(attrs->x64);
    } else if (type == 1) {
        jobj = HSD_JObjLoadJoint(attrs->x68);
    } else {
        jobj = HSD_JObjLoadJoint(attrs->x6C);
    }
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, it_802A24A0, 6, 0);
    if (type == 0) {
        if (attrs->x7C != NULL) {
            shapeanim = *attrs->x7C;
        } else {
            shapeanim = NULL;
        }
        if (attrs->x78 != NULL) {
            matanim = *attrs->x78;
        } else {
            matanim = NULL;
        }
        if (attrs->x74 != NULL) {
            anim = *attrs->x74;
        } else {
            anim = NULL;
        }
        HSD_JObjAddAnimAll(jobj->child, anim, matanim, shapeanim);
    } else if (type == 1) {
        if (attrs->x88 != NULL) {
            shapeanim = *attrs->x88;
        } else {
            shapeanim = NULL;
        }
        if (attrs->x84 != NULL) {
            matanim = *attrs->x84;
        } else {
            matanim = NULL;
        }
        if (attrs->x80 != NULL) {
            anim = *attrs->x80;
        } else {
            anim = NULL;
        }
        HSD_JObjAddAnimAll(jobj->child, anim, matanim, shapeanim);
    } else {
        if (attrs->x94 != NULL) {
            shapeanim = *attrs->x94;
        } else {
            shapeanim = NULL;
        }
        if (attrs->x90 != NULL) {
            matanim = *attrs->x90;
        } else {
            matanim = NULL;
        }
        if (attrs->x8C != NULL) {
            anim = *attrs->x8C;
        } else {
            anim = NULL;
        }
        HSD_JObjAddAnimAll(jobj->child, anim, matanim, shapeanim);
    }
    HSD_JObjReqAnimAll(jobj->child, 0.0f);
}

static inline void it_802B75FC_inline(ItemLink* link, f32 f)
{
    link->vel = it_803B8674;
    link->pos = it_803B8674;
    link->x2C_b0 = 0;
    link->x2C_b1 = 0;
    link->x2C_b2 = 0;
    link->coll_data.cur_pos = link->pos;
    link->coll_data.last_pos = link->coll_data.cur_pos;
    mpColl_80041EE4(&link->coll_data);
    mpColl_SetECBSource_Fixed(&link->coll_data, NULL, f, f, f, f);
}

/// #it_802B75FC

void it_802B7B84(Item_GObj* gobj)
{
    if (gobj != NULL) {
        Item* ip = GET_ITEM(gobj);
        if (ip != NULL) {
            if (ip->xDD4_itemVar.samusgrapple.x8 != NULL) {
                Fighter* fp = GET_FIGHTER(ip->xDD4_itemVar.samusgrapple.x8);
                if (fp != NULL) {
                    ip->xDD4_itemVar.samusgrapple.unk_10 = NULL;
                    fp->fv.ss.x223C = 0;
                    fp->accessory2_cb = 0;
                    fp->death1_cb = 0;
                    fp->accessory3_cb = 0;
                    {
                        ItemLink* cur = ip->xDD4_itemVar.samusgrapple.x0;
                        while (cur != NULL) {
                            HSD_GObj* link_gobj = cur->gobj;
                            cur = cur->next;
                            HSD_GObjPLink_80390228(link_gobj);
                        }
                        Item_8026A8EC(gobj);
                    }
                }
            }
        }
    }
}

/// #it_802B7C18

static inline void fn_802B7E34_inline(Item* ip, Mtx m)
{
    HSD_JObj* jobj;
    ItemLink* link = ip->xDD4_itemVar.samusgrapple.x0;
    jobj = link->gobj->hsd_obj;
    HSD_JObjSetupMatrix(link->jobj);
    PSMTXIdentity(m);
    PSMTXConcat(link->jobj->mtx, m, m);
    HSD_JObjCopyMtx(jobj, m);
    jobj->flags |= 0x03800000;
    HSD_JObjSetMtxDirty(jobj);
}

static inline void link_all(HSD_JObj* jobj, ItemLink* link)
{
    HSD_JObjAnimAll(jobj);
    while (link != NULL) {
        HSD_JObjAnimAll(link->gobj->hsd_obj);
        link = link->prev;
    }
}

void fn_802B7E34(Item_GObj* gobj)
{
    Mtx m;
    Item* ip = GET_ITEM(gobj);
    Fighter* fp = GET_FIGHTER(ip->owner);
    PAD_STACK(20);
    samus_grapple_state_sync(fp);
    fn_802B7E34_inline(ip, m);

    {
        Item* ip = GET_ITEM(gobj);
        ItemLink* link;
        HSD_JObjAnimAll(GET_JOBJ(gobj));
        link = ip->xDD4_itemVar.samusgrapple.x4;
        while (link) {
            HSD_JObjAnimAll(link->gobj->hsd_obj);
            link = link->prev;
        }
    }

    // samus_grapple_anim(gobj);
    if (samus_grapple_fighter_compare(fp->motion_id)) {
        return;
    }
    it_802B7B84(gobj);
}

void itSamusgrapple_UnkMotion0_Phys(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = fn_802B7E34;
}

void fn_802B805C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Fighter* fp = ip->owner->user_data;
    itSamusGrappleAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    ItemLink* link;
    Vec3 pos;
    Vec3 normal;
    Vec3 pos2;
    u8 _pad2[16];
    Mtx m;
    PAD_STACK(16);

    samus_grapple_state_sync(fp);

    link = ip->xDD4_itemVar.samusgrapple.x0;
    if (!samus_grapple_fighter_compare(fp->motion_id) && !(link->next->x2C_b0))
    {
        it_802B7B84(gobj);
        return;
    }

    samus_grapple_setup_pos(link, &pos, m);

    fp = ip->owner->user_data;
    switch (it_802B9328(link, &pos, attrs, fp)) {
    case 1:
        if (fp->motion_id == 0x165) {
            ftCo_800C3CC0(ip->owner);
            it_802BAB40(gobj);
            {
                ItemLink* link2 = ip->xDD4_itemVar.samusgrapple.x0;
                pos2 = link2->pos;
                {
                    HSD_GObj* link_gobj =
                        ip->xDD4_itemVar.samusgrapple.x0->gobj;
                    efSync_Spawn(0x41C, link_gobj, &pos2, link2);
                    efSync_Spawn(0x3F1, link_gobj, &pos2, &fp->facing_dir);
                }
            }
            return;
        }
        link->vel.x *= -attrs->x0;
        it_802BAA08(gobj);
        ftCommon_8007E2F4(fp, 0);
        break;
    case 2: {
        normal = link->coll_data.floor.normal;
        lbVector_Normalize(&normal);
        lbVector_Mirror(&link->vel, &normal);
        link->vel.y *= attrs->x0;
        it_802BAA08(gobj);
        ftCommon_8007E2F4(fp, 0);
        break;
    }
    case 3:
        it_802BA9B8(gobj);
        ftCommon_8007E2F4(fp, 0);
        break;
    }
    it_802A7168(ip, &pos, fp->x34_scale.y);
    samus_grapple_anim(gobj);
}

void itSamusgrapple_UnkMotion1_Phys(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = fn_802B805C;
}

void fn_802B8384(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Fighter* fp = ip->owner->user_data;
    itSamusGrappleAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    ItemLink* link = ip->xDD4_itemVar.samusgrapple.x0;
    Vec3 pos;
    Vec3 sp5C;
    u8 _pad[4];
    Mtx m;
    PAD_STACK(20);

    samus_grapple_setup_pos(link, &pos, m);

    switch (it_802B99A0(link, &pos, attrs, fp)) {
    case 1:
        link->vel.x *= -attrs->x0;
        break;
    case 2:
        sp5C = link->coll_data.floor.normal;
        lbVector_Normalize(&sp5C);
        lbVector_Mirror(&link->vel, &sp5C);
        link->vel.y *= attrs->x0;
        break;
    case 3:
        it_802BA9B8(gobj);
        break;
    }
    it_802A7168(ip, &pos, fp->x34_scale.y);
    samus_grapple_anim(gobj);
}

void itSamusgrapple_UnkMotion2_Phys(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = fn_802B8384;
}

void fn_802B8524(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSamusGrappleAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    Fighter* fp = ip->owner->user_data;
    ItemLink* link = ip->xDD4_itemVar.samusgrapple.x4;
    Vec3 pos;
    u8 _pad[4];
    Mtx m;
    PAD_STACK(28);

    samus_grapple_setup_pos(link, &pos, m);
    it_802B9CE8(link, &pos, attrs, ip->owner->user_data);
    it_802A7168(ip, &pos, fp->x34_scale.y);
    samus_grapple_anim(gobj);
    if (samus_grapple_fighter_compare(fp->motion_id)) {
        return;
    }
    it_802BAA58(gobj);
}

void itSamusgrapple_UnkMotion3_Phys(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = fn_802B8524;
}

void fn_802B8684(Item_GObj* gobj)
{
    Vec3 pos;
    u8 _pad[4];
    Mtx m;
    Item* ip = GET_ITEM(gobj);
    itSamusGrappleAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    Fighter* fp = ip->owner->user_data;
    ItemLink* link = ip->xDD4_itemVar.samusgrapple.x4;
    f32 retract_speed;
    PAD_STACK(20);

    samus_grapple_setup_pos(link, &pos, m);

    if (fp->ground_or_air == GA_Ground) {
        retract_speed = attrs->x4C;
    } else {
        retract_speed = 2.0 * attrs->x4C;
    }
    if (it_802BA194(link, &pos, attrs, retract_speed)) {
        if (!samus_grapple_fighter_compare(fp->motion_id)) {
            it_802B7B84(gobj);
            return;
        }
        itSamusGrapple_Logic53_PickedUp(gobj);
    }
    it_802A7168(ip, &pos, fp->x34_scale.y);
    samus_grapple_anim(gobj);
}

void itSamusgrapple_UnkMotion4_Phys(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = fn_802B8684;
}

void fn_802B8814(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSamusGrappleAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    ItemLink* link;
    Vec3 pos;
    u8 _pad2[4];
    Mtx m;
    Fighter* fp = ip->owner->user_data;
    PAD_STACK(24);

    if (ip->xDD4_itemVar.samusgrapple.x14 != 0) {
        it_802B7B84(gobj);
        return;
    }

    link = ip->xDD4_itemVar.samusgrapple.x4;
    samus_grapple_setup_pos(link, &pos, m);

    if (it_802BA2D8(link, &pos, attrs, attrs->x54) != 0) {
        ip->xDD4_itemVar.samusgrapple.x14 = 1;
        return;
    }
    it_802A7168(ip, &pos, fp->x34_scale.y);
    samus_grapple_anim(gobj);
}

void itSamusgrapple_UnkMotion5_Phys(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = fn_802B8814;
}

static inline bool fn_802B895C_inline(Item* ip, Fighter* fp, Vec3* pos)
{
    ItemLink* head = ip->xDD4_itemVar.samusgrapple.x0;
    Vec3* head_pos = &head->pos;
    if (mpCheckAllRemap(NULL, NULL, NULL, NULL, -1, -1, pos->x, pos->y,
                        head->pos.x, head->pos.y))
    {
        return true;
    } else if (mpCheckAllRemap(NULL, NULL, NULL, NULL, -1, -1, fp->cur_pos.x,
                               fp->cur_pos.y, head_pos->x, head_pos->y))
    {
        return true;
    } else {
        return false;
    }
}

void fn_802B895C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSamusGrappleAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    Fighter* fp = ip->owner->user_data;
    ItemLink* link = ip->xDD4_itemVar.samusgrapple.x4;
    Vec3 pos;
    u8 _pad[4];
    Mtx m;
    PAD_STACK(20);

    samus_grapple_setup_pos(link, &pos, m);

    if (fn_802B895C_inline(ip, fp, &pos)) {
        ftCo_80090780(ip->owner);
        it_802B7B84(gobj);
        return;
    }
    if (it_802B9FD4(ip->xDD4_itemVar.samusgrapple.x0, &pos, attrs)) {
        it_802BABB8(gobj);
        return;
    }
    it_802A7168(ip, &pos, fp->x34_scale.y);
    samus_grapple_anim(gobj);
    if (fp->ground_or_air != GA_Air) {
        it_802BAA58(gobj);
        return;
    }
    if (fp->input.x668 & 0x100) {
        it_802BAB7C(gobj);
    }
}

void itSamusgrapple_UnkMotion6_Phys(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = fn_802B895C;
}

void fn_802B8B54(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Fighter* fp = ip->owner->user_data;
    itSamusGrappleAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    ftSs_DatAttrs* da = fp->dat_attrs;
    ItemLink* link = ip->xDD4_itemVar.samusgrapple.x4;
    Vec3 pos;
    u8 _pad[4];
    f32 dx, dy;
    u8 _pad2[24];
    Mtx m;
    PAD_STACK(28);

    samus_grapple_setup_pos(link, &pos, m);
    dx = fp->cur_pos.x - pos.x;
    dy = fp->cur_pos.y - pos.y;

    if (it_802BA3BC(ip->xDD4_itemVar.samusgrapple.x4,
                    ip->xDD4_itemVar.samusgrapple.x0, &pos, attrs,
                    attrs->x4C) != 0)
    {
        fp->cur_pos.x = pos.x + dx;
        fp->cur_pos.y = pos.y + dy;
        if (ftCo_800C3A14(ip->owner) && ft_80082E3C(ip->owner) == NULL) {
            ftCliffCommon_80081370(ip->owner);
        } else {
            fp->self_vel.x = 0.0f;
            ftCo_8009B390(ip->owner, da->xCC);
        }
        it_802B7B84(gobj);
        return;
    }
    fp->cur_pos.x = pos.x + dx;
    fp->cur_pos.y = pos.y + dy;
    it_802A7168(ip, &pos, fp->x34_scale.y);
    samus_grapple_anim(gobj);
    if (fp->ground_or_air != GA_Air) {
        it_802BAA58(gobj);
    }
}

void itSamusgrapple_UnkMotion7_Phys(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = fn_802B8B54;
}

void fn_802B8D38(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSamusGrappleAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    Fighter* fp = ip->owner->user_data;
    ItemLink* link = ip->xDD4_itemVar.samusgrapple.x4;
    Vec3 pos;
    u8 _pad2[12];
    Vec3 saved_pos;
    u8 _pad3[4];
    Mtx m;
    u8 _pad[20];
    f32 old_x, old_y;

    samus_grapple_setup_pos(link, &pos, m);

    if (fn_802B895C_inline(ip, fp, &pos)) {
        ftCo_80090780(ip->owner);
        it_802B7B84(gobj);
        return;
    }

    old_x = fp->cur_pos.x - pos.x;
    old_y = fp->cur_pos.y - pos.y;
    saved_pos = fp->cur_pos;
    it_802BA5DC(ip->xDD4_itemVar.samusgrapple.x4,
                ip->xDD4_itemVar.samusgrapple.x0, &pos, attrs);
    fp->cur_pos.x = pos.x + (old_x);
    fp->cur_pos.y = pos.y + (old_y);
    {
        f32 tmp;
        tmp = fp->self_vel.x + (fp->cur_pos.x - saved_pos.x);
        fp->self_vel.x = tmp;
        fp->pos_delta.x = tmp;
        tmp = fp->self_vel.y + (fp->cur_pos.y - saved_pos.y);
        fp->self_vel.y = tmp;
        fp->pos_delta.y = tmp;
    }
    it_802A7168(ip, &pos, fp->x34_scale.y);
    samus_grapple_anim(gobj);
    if (ip->xDD4_itemVar.samusgrapple.x16 != 0 &&
        (fp->input.held_inputs & 0x40))
    {
        fp->mv.ss.grapple.x4 += 1.0f;
    }
    if (fp->ground_or_air != GA_Air) {
        it_802BAA58(gobj);
        return;
    }
    if (fp->input.x668 & 0x100) {
        it_802BAB7C(gobj);
        return;
    }
    if (fp->mv.ss.grapple.x4-- <= 0) {
        ftCo_80090780(ip->owner);
        it_802B7B84(gobj);
    }
}

void itSamusgrapple_UnkMotion8_Phys(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = fn_802B8D38;
}

void it_802B900C(ItemLink* link, Vec3* pos, itSamusGrappleAttributes* attrs,
                 f32 dist)
{
    u8 _pad[8];
    Vec3 dir;
    ItemLink* prev = link->prev;
    f32 d;

    it_802A3C98(&link->pos, pos, &dir);
    link->pos.x = (dir.x * dist) + pos->x;
    link->pos.y = (dir.y * dist) + pos->y;
    link->pos.z = (dir.z * dist) + pos->z;

    while (prev != NULL) {
        prev->vel.y -= samus_grapple_calc_grav(prev->vel.y);
        it_802A4420(prev);
        it_802A43EC(prev);

        d = it_802A3C98(&prev->pos, &link->pos, &dir);
        if (d > attrs->x38) {
            prev->pos.x = (dir.x * attrs->x38) + link->pos.x;
            prev->pos.y = (dir.y * attrs->x38) + link->pos.y;
            prev->pos.z = (dir.z * attrs->x38) + link->pos.z;
        } else if (d < attrs->x3C) {
            prev->pos.x = (dir.x * attrs->x3C) + link->pos.x;
            prev->pos.y = (dir.y * attrs->x3C) + link->pos.y;
            prev->pos.z = (dir.z * attrs->x3C) + link->pos.z;
        }

        link = prev;
        prev = link->prev;
    }
}

void it_802B91C4(ItemLink* link, Vec3* pos, itSamusGrappleAttributes* attrs,
                 f32 dist)
{
    u8 _pad[8];
    Vec3 dir;
    ItemLink* prev = link->prev;
    f32 d;

    it_802A3C98(&link->pos, pos, &dir);
    link->pos.x = (dir.x * dist) + pos->x;
    link->pos.y = (dir.y * dist) + pos->y;
    link->pos.z = (dir.z * dist) + pos->z;

    while (prev != NULL) {
        prev->vel.y -= attrs->x44;
        it_802A4420(prev);
        it_802A43EC(prev);

        d = it_802A3C98(&prev->pos, &link->pos, &dir);
        if (d > attrs->x38) {
            prev->pos.x = (dir.x * attrs->x38) + link->pos.x;
            prev->pos.y = (dir.y * attrs->x38) + link->pos.y;
            prev->pos.z = (dir.z * attrs->x38) + link->pos.z;
        } else if (d < attrs->x3C) {
            prev->pos.x = (dir.x * attrs->x3C) + link->pos.x;
            prev->pos.y = (dir.y * attrs->x3C) + link->pos.y;
            prev->pos.z = (dir.z * attrs->x3C) + link->pos.z;
        }

        link = prev;
        prev = prev->prev;
    }
}

/// #it_802B9328

/// #it_802B99A0

void it_802B9CE8(ItemLink* link, Vec3* pos, itSamusGrappleAttributes* attrs,
                 Fighter* fp)
{
    ItemLink* prev;
    f32 d;
    Item* grapple_ip = fp->fv.ss.x223C->user_data;
    u8 _pad[12];
    Fighter* new_var;
    Vec3 dir;
    Vec3* dir_ptr;
    f32 friction;
    itSamusGrapple_HitboxData hitbox_data;
    PAD_STACK(8);

    new_var = fp;
    if (new_var->ground_or_air == GA_Ground &&
        grapple_ip->xDD4_itemVar.samusgrapple.x16 == 1)
    {
        if (new_var->input.x668 & 0x100) {
            hitbox_data = it_803B8660;
            ftColl_8007AFF8(new_var->gobj);
            it_802B7160(new_var->gobj, &hitbox_data);
            grapple_ip->xDD4_itemVar.samusgrapple.x16++;
        } else {
            ftColl_8007AFF8(new_var->gobj);
        }
    }
    prev = link->prev;
    while (prev != NULL && !link->x2C_b0) {
        link = prev;
        prev = prev->prev;
    }
    link->vel.y -= samus_grapple_calc_grav(link->vel.y);
    it_802A4420(link);
    d = it_802A3C98(&link->pos, pos, &dir);
    if (d > attrs->x38) {
        link->pos.x = (dir.x * attrs->x38) + pos->x;
        link->pos.y = (dir.y * attrs->x38) + pos->y;
        link->pos.z = (dir.z * attrs->x38) + pos->z;
    }
    while (prev != NULL) {
        prev->vel.y -= samus_grapple_calc_grav(prev->vel.y);
        it_802A4420(prev);
        d = it_802A3C98(&prev->pos, &link->pos, &dir);
        dir_ptr = &dir;
        if (d > attrs->x38) {
            prev->pos.x = (dir_ptr->x * attrs->x38) + link->pos.x;
            prev->pos.y = (dir_ptr->y * attrs->x38) + link->pos.y;
            prev->pos.z = (dir_ptr->z * attrs->x38) + link->pos.z;
        } else if (d < attrs->x3C) {
            prev->pos.x = (dir_ptr->x * attrs->x3C) + link->pos.x;
            prev->pos.y = (dir_ptr->y * attrs->x3C) + link->pos.y;
            prev->pos.z = (dir_ptr->z * attrs->x3C) + link->pos.z;
        }
        link = prev;
        prev = prev->prev;
    }
    if (link->vel.x > attrs->x58) {
        link->vel.x -= attrs->x58;
    } else if (link->vel.x < -attrs->x58) {
        link->vel.x += attrs->x58;
    } else {
        link->vel.x = 0.0f;
    }
}

bool it_802B9FD4(ItemLink* link, Vec3* pos, itSamusGrappleAttributes* attrs)
{
    ItemLink* next;
    Vec3 dir;
    PAD_STACK(4);

    it_802A4454(link);
    next = link->next;

    while (next != NULL) {
        if (next->x2C_b0) {
            next->vel.y -= samus_grapple_calc_grav(next->vel.y);
            it_802A4420(next);
            if (it_802A3C98(&next->pos, &link->pos, &dir) > attrs->x38) {
                next->pos.x = (dir.x * attrs->x38) + link->pos.x;
                next->pos.y = (dir.y * attrs->x38) + link->pos.y;
                next->pos.z = (dir.z * attrs->x38) + link->pos.z;
            }
            it_802A43EC(next);
        } else {
            if (it_802A3C98(pos, &link->pos, &dir) > attrs->x38) {
                next->pos.x = (dir.x * attrs->x38) + link->pos.x;
                next->pos.y = (dir.y * attrs->x38) + link->pos.y;
                next->pos.z = (dir.z * attrs->x38) + link->pos.z;
                next->x2C_b0 = 1;
                it_802A43B8(next);
            } else {
                return false;
            }
        }
        link = next;
        next = link->next;
    }
    return true;
}

bool it_802BA194(ItemLink* link, Vec3* pos, itSamusGrappleAttributes* attrs,
                 f32 target_dist)
{
    ItemLink* next;
    ItemLink* cur;
    ItemLink* iter;
    f32 d, remaining;
    bool result;
    u8 _pad[16];
    Vec3 dir;

    cur = link;
    next = link->prev;

    while (next != NULL && !cur->x2C_b0) {
        cur = next;
        next = next->prev;
    }

    d = it_802A3C98(&cur->pos, pos, &dir);

    while (next != NULL && target_dist > d) {
        cur->x2C_b0 = 0;
        d = it_802A3C98(&next->pos, pos, &dir);
        cur = next;
        next = next->prev;
    }

    remaining = d - target_dist;
    it_802B900C(cur, pos, attrs, MAX(remaining, attrs->x38));

    if (next != NULL) {
        result = false;
    } else {
        result = true;
    }

    iter = link;
    while (iter != NULL) {
        f32 dx = iter->pos.x - iter->coll_data.last_pos.x;
        f32 dz = iter->pos.z - iter->coll_data.last_pos.z;
        iter->vel.x += 0.12 * (dx - iter->vel.x);
        iter->vel.z += 0.12 * (dz - iter->vel.z);
        iter = iter->prev;
    }
    return result;
}

bool it_802BA2D8(ItemLink* link, Vec3* pos, itSamusGrappleAttributes* attrs,
                 f32 target_dist)
{
    ItemLink* next;
    ItemLink* cur;
    f32 d, remaining, max_dist;
    u8 _pad[8];
    Vec3 dir;

    cur = link;
    next = link->prev;

    while (next != NULL && !cur->x2C_b0) {
        cur = next;
        next = next->prev;
    }

    d = it_802A3C98(&cur->pos, pos, &dir);

    while (next != NULL && target_dist > d) {
        cur->x2C_b0 = 0;
        d = it_802A3C98(&next->pos, pos, &dir);
        cur = next;
        next = next->prev;
    }

    remaining = d - target_dist;
    max_dist = attrs->x38;
    if (remaining > max_dist) {
        remaining = max_dist;
    }
    it_802B900C(cur, pos, attrs, remaining);

    if (next != NULL) {
        return false;
    }
    return true;
}

bool it_802BA3BC(ItemLink* tail, ItemLink* head, Vec3* pos,
                 itSamusGrappleAttributes* attrs, f32 target_dist)
{
    u8 _pad[8];
    Vec3 dir;
    Vec3 saved_pos;
    ItemLink* next_tail;
    ItemLink* link;
    s32 count;
    f32 d, remaining, max_dist;

    it_802A4454(head);
    count = 0;
    next_tail = tail->prev;
    saved_pos = head->pos;

    while (next_tail != NULL && !tail->x2C_b0) {
        tail = next_tail;
        next_tail = next_tail->prev;
    }

    it_802B91C4(tail, pos, attrs, attrs->x38);
    head->pos = saved_pos;

    d = it_802A3C98(&tail->pos, pos, &dir);

    while (next_tail != NULL && target_dist > d) {
        tail->x2C_b0 = 0;
        d = it_802A3C98(&next_tail->pos, pos, &dir);
        tail = next_tail;
        next_tail = next_tail->prev;
    }

    remaining = d - target_dist;
    max_dist = attrs->x38;
    if (remaining > max_dist) {
        remaining = max_dist;
    }
    it_802B91C4(tail, pos, attrs, remaining);
    head->pos = saved_pos;

    link = head->next;
    while (link != NULL && link->x2C_b0) {
        count++;
        if (it_802A3C98(&link->pos, &head->pos, &dir) > attrs->x38) {
            link->pos.x = (dir.x * attrs->x38) + head->pos.x;
            link->pos.y = (dir.y * attrs->x38) + head->pos.y;
            link->pos.z = (dir.z * attrs->x38) + head->pos.z;
        }
        head = link;
        link = head->next;
    }

    if (it_802A3C98(pos, &head->pos, &dir) > attrs->x38) {
        pos->x = (dir.x * attrs->x38) + head->pos.x;
        pos->y = (dir.y * attrs->x38) + head->pos.y;
        pos->z = (dir.z * attrs->x38) + head->pos.z;
    }

    if (count != 0) {
        return false;
    }
    return true;
}

void it_802BA5DC(ItemLink* tail, ItemLink* head, Vec3* pos,
                 itSamusGrappleAttributes* attrs)
{
    Vec3 saved_pos;
    Vec3 dir;
    ItemLink* link;
    ItemLink* next;
    ItemLink* cur;
    bool retracted;
    PAD_STACK(12);

    it_802A4454(head);
    cur = tail;
    saved_pos = head->pos;
    next = tail->prev;

    while (next != NULL && !cur->x2C_b0) {
        cur = next;
        next = next->prev;
    }

    it_802B91C4(cur, pos, attrs, attrs->x38);
    retracted = false;
    head->pos = saved_pos;

    link = head->next;
    while (link != NULL && link->x2C_b0) {
        if (!retracted) {
            if (it_802A3C98(&link->pos, &head->pos, &dir) > attrs->x38) {
                link->pos.x = (dir.x * attrs->x38) + head->pos.x;
                link->pos.y = (dir.y * attrs->x38) + head->pos.y;
                link->pos.z = (dir.z * attrs->x38) + head->pos.z;
            } else {
                retracted = true;
            }
        }
        head = link;
        link = link->next;
    }

    if (it_802A3C98(pos, &head->pos, &dir) > attrs->x38) {
        pos->x = (dir.x * attrs->x38) + head->pos.x;
        pos->y = (dir.y * attrs->x38) + head->pos.y;
        pos->z = (dir.z * attrs->x38) + head->pos.z;
    }
}

bool it_802BA760(ItemLink* link, Vec3* pos, itSamusGrappleAttributes* attrs,
                 Fighter* fp)
{
    Vec3 dir;
    ftSs_DatAttrs* da = fp->ft_data->ext_attr;
    ItemLink* cur;
    ItemLink* next;
    PAD_STACK(16);

    if ((fp->motion_id == 0xD4 && (fp->mv.ss.unk7.x0 < da->xA0)) ||
        (fp->motion_id == 0xD6 && (fp->mv.ss.unk7.x0 < da->xB0)) ||
        (fp->motion_id == 0x165 && (fp->mv.ss.unk7.x0 < da->xC0)))
    {
        return true;
    } else {
        cur = link;
        next = link->next;
        while (next != NULL) {
            if (next->x2C_b0) {
                if (it_802A3C98(&next->pos, &cur->pos, &dir) > attrs->x38) {
                    next->pos.x = (dir.x * attrs->x38) + cur->pos.x;
                    next->pos.y = (dir.y * attrs->x38) + cur->pos.y;
                    next->pos.z = (dir.z * attrs->x38) + cur->pos.z;
                }
                it_802A43EC(next);
            } else {
                if (it_802A3C98(pos, &cur->pos, &dir) > attrs->x38) {
                    next->pos.x = (dir.x * attrs->x38) + cur->pos.x;
                    next->pos.y = (dir.y * attrs->x38) + cur->pos.y;
                    next->pos.z = (dir.z * attrs->x38) + cur->pos.z;
                    next->x2C_b0 = 1;
                    it_802A43B8(next);
                } else {
                    return false;
                }
            }
            cur = next;
            next = next->next;
        }
        it_802B900C(cur, pos, attrs, attrs->x38);
        return false;
    }
}

void itSamusGrapple_Logic53_PickedUp(Item_GObj* gobj)
{
    PAD_STACK(16);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    it_802A2428(gobj);
}

void it_802BA9B8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
    ftColl_8007AFF8(ip->xDD4_itemVar.samusgrapple.x8);
    it_802A2428(gobj);
}

void it_802BAA08(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    ftColl_8007AFF8(ip->xDD4_itemVar.samusgrapple.x8);
    it_802A2428(gobj);
}

void it_802BAA58(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
    it_802A2428(gobj);
}

void it_802BAA94(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
    ftColl_8007AFF8(ip->xDD4_itemVar.samusgrapple.x8);
    it_802A2428(gobj);
}

void it_802BAAE4(Item_GObj* gobj, Vec3* vel, f32 unused)
{
    Item* ip = GET_ITEM(gobj);
    ItemLink* link = ip->xDD4_itemVar.samusgrapple.x0;
    link->vel = *vel;
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    it_802A2428(gobj);
}

void it_802BAB40(Item_GObj* gobj)
{
    PAD_STACK(16);
    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
    it_802A2428(gobj);
}

void it_802BAB7C(Item_GObj* gobj)
{
    PAD_STACK(16);
    Item_80268E5C(gobj, 7, ITEM_ANIM_UPDATE);
    it_802A2428(gobj);
}

/// Set grapple beam state and store duration.
void it_802BABB8(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    Fighter* fp = ip->owner->user_data;
    ftSs_DatAttrs* da = fp->ft_data->ext_attr;
    PAD_STACK(24);
    Item_80268E5C(gobj, 8, ITEM_ANIM_UPDATE);
    it_802A2428(gobj);
    fp->mv.ss.grapple.x4 = (f32) (s32) da->xD0;
}

void it_802BAC3C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.ss.x223C != NULL) {
        it_802B7B84(fp->fv.ss.x223C);
        return;
    }
    fp->accessory2_cb = NULL;
    fp->death1_cb = NULL;
    fp->accessory3_cb = NULL;
}

void it_802BAC80(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.ss.x223C != NULL) {
        Item* ip = GET_ITEM(fp->fv.ss.x223C);
        if (ip->xDD4_itemVar.samusgrapple.unk_10) {
            ip->xDD4_itemVar.samusgrapple.unk_10(fp->fv.ss.x223C);
        }
    }
}

void it_802BACC4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;
    u8 _pad[8];
    Mtx m;
    Mtx m2;
    PAD_STACK(4);

    if (fp->fv.ss.x223C != NULL) {
        Item* ip = GET_ITEM(fp->fv.ss.x223C);
        itSamusGrappleAttributes* attrs =
            ip->xC4_article_data->x4_specialAttributes;
        ItemLink* link = ip->xDD4_itemVar.samusgrapple.x0;

        samus_grapple_setup_pos(link, &pos, m);

        if (it_802BA760(link, &pos, attrs, fp)) {
            fn_802B7E34_inline(ip, m2);
        } else {
            it_802A7168(ip, &pos, fp->x34_scale.y);
        }
    }
}

void itSamusGrapple_Logic53_EvtUnk(Item_GObj* gobj, Item_GObj* arg1)
{
    Item* item = GET_ITEM(gobj);
    it_8026B894(gobj, arg1);
    if (item->xDD4_itemVar.samusgrapple.x8 == arg1) {
        item->xDD4_itemVar.samusgrapple.x8 = NULL;
    }
}
