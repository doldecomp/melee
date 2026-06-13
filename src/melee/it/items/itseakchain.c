#include "itseakchain.h"

#include "it/items/itseakchain.static.h"

#include "platform.h"

#include "baselib/forward.h"

#include "baselib/gobjplink.h"
#include "baselib/jobj.h"
#include "dolphin/mtx.h"
#include "ft/ftcoll.h"
#include "ft/ftlib.h"
#include "ft/inlines.h"

#include "ftSeak/forward.h"

#include "ftSeak/ftSk_SpecialS.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCharItems.h"
#include "it/item.h"
#include "it/items/itlinkhookshot.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbvector.h"
#include "mp/mpcoll.h"
#include "MSL/math.h"

#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjuserdata.h>

ItemStateTable it_803F7438[] = {
    { -1, itSeakchain_UnkMotion4_Anim, NULL, NULL },
    { -1, itSeakchain_UnkMotion4_Anim, NULL, NULL },
    { -1, itSeakchain_UnkMotion4_Anim, NULL, NULL },
    { -1, itSeakchain_UnkMotion4_Anim, NULL, NULL },
    { -1, itSeakchain_UnkMotion4_Anim, NULL, NULL },
};

extern f32 it_804DD0E0;

void it_802BAEEC(Item_GObj* gobj)
{
    it_8026B724(gobj);
}

void it_802BAF0C(Item_GObj* gobj)
{
    it_8026B73C(gobj);
}

static inline HSD_JObj* it_802BAF2C_Load_x64(Item* ip)
{
    itSeakChain_Attrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    return HSD_JObjLoadJoint(attrs->x64_joint);
}

static inline HSD_JObj* it_802BAF2C_Load_x68(Item* ip)
{
    itSeakChain_Attrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    return HSD_JObjLoadJoint(attrs->x68_joint);
}

int it_802BAF2C(Item* ip, HSD_JObj* jobj)
{
    ItemLink* prev_link;
    ItemLink* head_link;
    ItemLink* tail_link;
    HSD_JObj* result;
    itSeakChain_Attrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    HSD_GObj* link_gobj;
    ItemLink* link;
    int i;
    Vec3 zero = it_803B8680;

    prev_link = NULL;
    for (i = 0; i < attrs->x0; i++) {
        link_gobj = GObj_Create(7, 0xA, 0);

        if (link_gobj == NULL) {
            while (prev_link != NULL) {
                HSD_GObjPLink_80390228(prev_link->gobj);
                prev_link = prev_link->next;
            }
            return 0;
        }

        link = HSD_ObjAlloc(&item_link_alloc_data);
        it_80275328(link_gobj, link);
        GObj_InitUserData(link_gobj, 6, it_802A2474, link);

        if (i == 0) {
            link->next = NULL;
            head_link = link;
            link->jobj = jobj;
            link->gobj = link_gobj;
            link->vel = zero;
            link->pos = zero;
            link->x2C_b0 = false;
            it_802A24D0(link, it_804DD0E0);
            HSD_GObjObject_80390A70(link_gobj, HSD_GObj_804D7849,
                                    it_802BAF2C_Load_x64(ip));
            GObj_SetupGXLink(link_gobj, it_802A24A0, 6, 0);
        } else if (i == attrs->x0 - 1) {
            prev_link->prev = link;
            link->prev = NULL;
            tail_link = link;
            link->next = prev_link;
            link->jobj = jobj;
            link->gobj = link_gobj;
            link->vel = zero;
            link->pos = zero;
            link->x2C_b0 = false;
            it_802A24D0(link, it_804DD0E0);
            {
                HSD_JObj* joint = it_802BAF2C_Load_x68(ip);
                HSD_GObjObject_80390A70(link_gobj, HSD_GObj_804D7849, joint);
            }
            GObj_SetupGXLink(link_gobj, HSD_GObj_JObjCallback, 6, 0);
            result = link_gobj->hsd_obj;
        } else {
            prev_link->prev = link;
            link->next = prev_link;
            link->jobj = jobj;
            link->gobj = link_gobj;
            link->vel = zero;
            link->pos = zero;
            link->x2C_b0 = false;
            it_802A24D0(link, it_804DD0E0);
            HSD_GObjObject_80390A70(link_gobj, HSD_GObj_804D7849,
                                    it_802BAF2C_Load_x64(ip));
            GObj_SetupGXLink(link_gobj, it_802A24A0, 6, 0);
        }
        prev_link = link;
    }
    ip->xDD4_itemVar.seakchain.x0 = tail_link;
    ip->xDD4_itemVar.seakchain.x4 = head_link;
    return (int) result;
}

static void inlineA0(Item_GObj* gobj)
{
    if (gobj != NULL) {
        Item* ip = GET_ITEM(gobj);
        if (ip->owner != NULL) {
            ftSk_SpecialS_80110E4C(ip->owner);
        }
        ip->owner = NULL;
        ip->xDD4_itemVar.seakchain.parent_gobj = NULL;
        {
            ItemLink* cur;
            for (cur = ip->xDD4_itemVar.seakchain.x0; cur != NULL;) {
                HSD_GObj* cur_gobj = cur->gobj;
                cur = cur->next;
                HSD_GObjPLink_80390228(cur_gobj);
            }
        }
    }
}

void it_802BB20C(Item_GObj* gobj)
{
    if (GET_ITEM(gobj) != NULL) {
        inlineA0(gobj);
        Item_8026A8EC(gobj);
    }
}

Item_GObj* itSeakChain_Spawn(Fighter_GObj* parent_gobj, Point3d* arg1,
                             f32 facing_dir)
{
    SpawnItem spawn;
    Fighter* fp;
    Item_GObj* gobj;
    Item* ip;
    s32 i;
    PAD_STACK(32);

    fp = GET_FIGHTER(parent_gobj);
    spawn.kind = It_Kind_Seak_Chain;
    spawn.prev_pos = *arg1;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = parent_gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;
    gobj = Item_80268B18(&spawn);
    if (gobj != NULL) {
        ip = GET_ITEM(gobj);
        ip->xDD4_itemVar.seakchain.parent_gobj = parent_gobj;
        ip->xDD4_itemVar.seakchain.x10 = 0;
        ip->xDD4_itemVar.seakchain.x14 = 0;
        for (i = 0; i < 0xF; i++) {
            ip->xDD4_itemVar.seakchain.history[i].z = 0.0f;
            ip->xDD4_itemVar.seakchain.history[i].y = 0.0f;
            ip->xDD4_itemVar.seakchain.history[i].x = 0.0f;
        }
        it_80272A3C(GET_JOBJ(gobj));
        it_802BAF2C(ip, fp->parts[FtPart_L3rdNa].joint);
        Item_8026AB54(gobj, parent_gobj, FtPart_L3rdNa);
    }
    return gobj;
}

void fn_802BB428(Item_GObj* gobj)
{
    it_802BCA30(GET_ITEM(gobj));
}

void fn_802BB44C(Item_GObj* gobj)
{
    Vec3 vec;
    Mtx mtx;
    Item* temp_r30;
    itSeakChain_Attrs* sa;
    ItemLink* link;

    temp_r30 = GET_ITEM(gobj);
    link = temp_r30->xDD4_itemVar.seakchain.x0;
    sa = temp_r30->xC4_article_data->x4_specialAttributes;
    PSMTXIdentity(mtx);
    mtx[0][3] = 0.0f;
    mtx[1][3] = 0.0f;
    mtx[2][3] = 0.1f;
    HSD_JObjSetupMatrix(link->jobj);
    PSMTXConcat(link->jobj->mtx, mtx, mtx);
    vec.x = mtx[0][3];
    vec.y = mtx[1][3];
    vec.z = mtx[2][3];
    switch (it_802BBD64(link, &vec, sa)) {
    case 1:
        link->vel.x *= -sa->x58;
        it_802BCF2C(gobj);
        break;
    case 2:
        it_802BCED4(gobj);
        break;
    }
    it_802BCB88(temp_r30, &vec);
}

void fn_802BB574(Item_GObj* gobj)
{
    Vec3 vec;
    Item* ip = GET_ITEM(gobj);
    itSeakChain_Attrs* sa = ip->xC4_article_data->x4_specialAttributes;
    Mtx mtx;
    ItemLink* link = ip->xDD4_itemVar.seakchain.x0;

    PSMTXIdentity(mtx);
    mtx[0][3] = 0.0f;
    mtx[1][3] = 0.0f;
    mtx[2][3] = 0.1f;
    HSD_JObjSetupMatrix(link->jobj);
    PSMTXConcat(link->jobj->mtx, mtx, mtx);
    vec.x = mtx[0][3];
    vec.y = mtx[1][3];
    vec.z = mtx[2][3];
    switch (it_802BBED0(link, &vec, sa)) {
    case 1:
        link->vel.x *= -sa->x58;
        break;
    case 2:
        it_802BCED4(gobj);
        break;
    }
    it_802BCB88(ip, &vec);
}

/// @todo Shared inline with #fn_802BB784 #fn_802BB574, #fn_802BB44C
void fn_802BB694(Item_GObj* gobj)
{
    Vec3 vec;
    Mtx mtx;
    Item* ip = GET_ITEM(gobj);
    ItemLink* link = ip->xDD4_itemVar.seakchain.x4;
    PSMTXIdentity(mtx);
    mtx[0][3] = 0.0f;
    mtx[1][3] = 0.0f;
    mtx[2][3] = 0.1f;
    HSD_JObjSetupMatrix(link->jobj);
    PSMTXConcat(link->jobj->mtx, mtx, mtx);
    vec.x = mtx[0][3];
    vec.y = mtx[1][3];
    vec.z = mtx[2][3];
    it_802BC080(link, &vec, ip);
    it_802BCB88(ip, &vec);
}

void fn_802BB784(Item_GObj* gobj)
{
    Vec3 vec;
    Mtx mtx;
    Item* ip;
    itSeakChain_Attrs* sa;
    ItemLink* link;

    ip = GET_ITEM(gobj);
    link = ip->xDD4_itemVar.seakchain.x4;
    sa = ip->xC4_article_data->x4_specialAttributes;
    PSMTXIdentity(mtx);
    mtx[0][3] = 0.0f;
    mtx[1][3] = 0.0f;
    mtx[2][3] = 0.1f;
    HSD_JObjSetupMatrix(link->jobj);
    PSMTXConcat(link->jobj->mtx, mtx, mtx);
    vec.x = mtx[0][3];
    vec.y = mtx[1][3];
    vec.z = mtx[2][3];
    if (it_802BC94C(link, &vec, sa, sa->x54)) {
        it_2725_Logic54_PickedUp(gobj);
    }
    it_802BCB88(ip, &vec);
}

static bool notInSpecialS(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        enum_t msid = ftLib_80086C0C(gobj);
        if ((msid >= ftSk_MS_SpecialSStart) &&
            (msid <= ftSk_MS_SpecialAirSEnd))
        {
            return false;
        }
        return true;
    }
    return true;
}

bool itSeakchain_UnkMotion4_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(2 * 4);
    if (notInSpecialS(ip->owner)) {
        inlineA0(gobj);
        return true;
    }
    return false;
}

int it_802BB938(ItemLink* link, int arg1, float arg2)
{
    CollData* coll = &link->coll_data;

    if (link->next != NULL && link->next->x2C_b0) {
        coll->last_pos = link->next->pos;
    } else {
        coll->last_pos = coll->cur_pos;
    }
    coll->cur_pos = link->pos;
    if (mpColl_80048844(coll)) {
        if (!link->x2C_b1 && arg1 != 0 && !link->x2C_b2) {
            lbAudioAx_800237A8(0x41F45, 0x7F, 0x40);
            link->x2C_b2 = 0xF; // weird; gets truncated to 0x1
        }
        link->x2C_b1 = true;
    } else {
        link->x2C_b1 = false;
        if (link->x2C_b2) {
            link->x2C_b2--;
        }
    }
    if (coll->env_flags & 0x18000) {
        coll->cur_pos.x = link->pos.x;
    } else if (coll->env_flags & 0xFFF) {
        if (link->next != NULL && link->next->x2C_b0 && link->prev != NULL) {
            coll->cur_pos.y += arg2;
        }
    }
    link->pos = coll->cur_pos;
    return coll->env_flags & 0x18FFF;
}

#pragma push
#pragma dont_inline on
s32 it_802BBAEC(ItemLink* link, s32 arg1, f32 arg2)
{
    return it_802BB938(link, arg1, arg2);
}
#pragma pop

void it_802BBB0C(ItemLink* link, Vec3* offset, itSeakChain_Attrs* sa,
                 float scale)
{
    u8 _pad[8];
    Vec3 pos;
    ItemLink* prev = link->prev;

    it_802A3C98(&link->pos, offset, &pos);
    link->pos.x = pos.x * scale + offset->x;
    link->pos.y = pos.y * scale + offset->y;
    link->pos.z = pos.z * scale + offset->z;
    for (; prev != NULL; link = prev, prev = prev->prev) {
        prev->vel.y -= sa->x18;
        it_802A4420(prev);
        it_802A43EC(prev);
        it_802BB938(prev, 0, sa->x4);
        if (it_802A3C98(&prev->pos, &link->pos, &pos) > sa->x4) {
            prev->pos.x = pos.x * sa->x4 + link->pos.x;
            prev->pos.y = pos.y * sa->x4 + link->pos.y;
            prev->pos.z = pos.z * sa->x4 + link->pos.z;
        }
    }
}

void it_802BBC38(ItemLink* link, Vec3* offset, itSeakChain_Attrs* sa,
                 f32 scale)
{
    u8 _pad[12];
    Vec3 origin;
    u8 _pad2[4];
    ItemLink* prev = link->prev;

    it_802A3C98(&link->pos, offset, &origin);
    link->pos.x = origin.x * scale + offset->x;
    link->pos.y = origin.y * scale + offset->y;
    link->pos.z = origin.z * scale + offset->z;
    for (; prev != NULL; link = prev, prev = prev->prev) {
        prev->vel.y -= sa->x18;
        it_802A4420(prev);
        it_802A43EC(prev);
        it_802BB938(prev, 0, sa->x4);
        if (it_802A3C98(&prev->pos, &link->pos, &origin) > sa->x4) {
            prev->pos.x = origin.x * sa->x4 + link->pos.x;
            prev->pos.y = origin.y * sa->x4 + link->pos.y;
            prev->pos.z = origin.z * sa->x4 + link->pos.z;
        }
    }
}

enum_t it_802BBD64(ItemLink* link, Vec3* arg1, itSeakChain_Attrs* sa)
{
    u8 _pad[0x10];
    Vec3 vec;
    ItemLink* cur = link;
    ItemLink* prev = link->next;
    int temp_r29;

    it_802A4420(link);
    temp_r29 = it_802BB938(cur, 1, sa->x4) & 0xFFF;
    cur->pos.z = cur->pos.z;
    while (prev != NULL) {
        if (prev->x2C_b0) {
            if (it_802A3C98(&prev->pos, &cur->pos, &vec) > sa->x4) {
                prev->pos.x = vec.x * sa->x4 + cur->pos.x;
                prev->pos.y = vec.y * sa->x4 + cur->pos.y;
                prev->pos.z = vec.z * sa->x4 + cur->pos.z;
            }
            it_802A43EC(prev);
        } else {
            if (it_802A3C98(arg1, &cur->pos, &vec) > sa->x4) {
                prev->pos.x = vec.x * sa->x4 + cur->pos.x;
                prev->pos.y = vec.y * sa->x4 + cur->pos.y;
                prev->pos.z = vec.z * sa->x4 + cur->pos.z;
                prev->x2C_b0 = true;
                it_802A43B8(prev);
            } else {
                if (temp_r29 != 0) {
                    return 1;
                }
                return 0;
            }
        }
        cur = prev;
        prev = prev->next;
    }
    it_802BBB0C(cur, arg1, sa, sa->x4);
    return 2;
}

enum_t it_802BBED0(ItemLink* link, Point3d* arg1, itSeakChain_Attrs* sa)
{
    u8 _pad[16];
    Point3d pos;
    ItemLink *cur = link, *prev = link->next;

    link->vel.y -= sa->x18;
    it_802A4420(cur);

    {
        int temp_r29 = it_802BB938(cur, 1, sa->x4) & 0xFFF;
        float vel_scale = 1.0f;
        while (prev != NULL) {
            if (prev->x2C_b0) {
                prev->vel.y = -((sa->x18 * vel_scale) - prev->vel.y);
                vel_scale *= sa->x34;
                it_802A4420(prev);
                if (it_802A3C98(&prev->pos, &cur->pos, &pos) > sa->x4) {
                    prev->pos.x = pos.x * sa->x4 + cur->pos.x;
                    prev->pos.y = pos.y * sa->x4 + cur->pos.y;
                    prev->pos.z = pos.z * sa->x4 + cur->pos.z;
                }
                it_802A43EC(prev);
            } else {
                if (it_802A3C98(arg1, &cur->pos, &pos) > sa->x4) {
                    prev->pos.x = pos.x * sa->x4 + cur->pos.x;
                    prev->pos.y = pos.y * sa->x4 + cur->pos.y;
                    prev->pos.z = pos.z * sa->x4 + cur->pos.z;
                    prev->x2C_b0 = true;
                    it_802A43B8(prev);
                } else {
                    if (temp_r29 != 0) {
                        return 1;
                    }
                    return 0;
                }
            }
            cur = prev;
            prev = prev->next;
        }
        it_802BBB0C(cur, arg1, sa, sa->x4);
        return 2;
    }
}

static inline void itSeakChain_clamp_x10(ItemLink* link,
                                         itSeakChain_Attrs* attrs)
{
    f32 value = link->vel.x;
    f32 limit = attrs->x10;

    if (value > limit) {
        link->vel.x = value - limit;
    } else if (value < -limit) {
        link->vel.x = value + limit;
    } else {
        link->vel.x = 0.0f;
    }
}

static inline void itSeakChain_clamp_x14(ItemLink* link,
                                         itSeakChain_Attrs* attrs)
{
    f32 value = link->vel.x;
    f32 limit = attrs->x14;

    if (value > limit) {
        link->vel.x = value - limit;
    } else if (value < -limit) {
        link->vel.x = value + limit;
    } else {
        link->vel.x = 0.0f;
    }
}

void it_802BC080(ItemLink* link, Vec3* target, Item* ip)
{
    struct {
        Vec3 dir;
        u8 pad[16];
    } stack;
    f32 lstick_x, lstick_y;
    ItemLink* iter = link->prev;
    ItemLink* cur = link;
    itSeakChain_Attrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    s32 last_idx = (s32) (0.5f * attrs->x0 - 1.0f);
    Fighter* fp;
    s32 env_flags;
    s32 use_arg = 0;
    s32 counter;
    s32 coll_arg;
    f32 scale;
    s32 mode;
    int i;
    PAD_STACK(12);

    while (iter != NULL && !cur->x2C_b0) {
        cur = iter;
        iter = iter->prev;
    }

    if (ip->xDD4_itemVar.seakchain.x18 != 0) {
        coll_arg = 1;
    } else {
        coll_arg = 0;
    }
    fp = GET_FIGHTER(ip->xDD4_itemVar.seakchain.parent_gobj);

    for (i = 0; last_idx > i; i++) {
        ip->xDD4_itemVar.seakchain.history[last_idx - i].x =
            ip->xDD4_itemVar.seakchain.history[last_idx - 1 - i].x;
        ip->xDD4_itemVar.seakchain.history[last_idx - i].y =
            ip->xDD4_itemVar.seakchain.history[last_idx - 1 - i].y;
    }

    if (ABS(fp->fv.sk.lstick_delta.x) > attrs->x48) {
        s32 sign = (fp->fv.sk.lstick_delta.x < 0.0f) ? -1 : 1;
        if (ip->facing_dir == sign) {
            ip->xDD4_itemVar.seakchain.history[0].x =
                fp->fv.sk.lstick_delta.x * attrs->x38;
        } else {
            ip->xDD4_itemVar.seakchain.history[0].x =
                fp->fv.sk.lstick_delta.x * attrs->x3C;
        }
    } else {
        ip->xDD4_itemVar.seakchain.history[0].x = 0.0f;
    }

    if (ABS(fp->fv.sk.lstick_delta.y) > attrs->x48) {
        s32 sign = (fp->fv.sk.lstick_delta.y < 0.0f) ? -1 : 1;
        if (sign > 0.0f) {
            ip->xDD4_itemVar.seakchain.history[0].y =
                fp->fv.sk.lstick_delta.y * attrs->x40;
        } else {
            ip->xDD4_itemVar.seakchain.history[0].y =
                fp->fv.sk.lstick_delta.y * attrs->x44;
        }
    } else {
        ip->xDD4_itemVar.seakchain.history[0].y = 0.0f;
    }

    ip->xDD4_itemVar.seakchain.x18 = *(s32*) &fp->mv.co.common.x1C;

    cur->vel.x += ip->xDD4_itemVar.seakchain.history[0].x * attrs->x1C;
    cur->vel.y += ip->xDD4_itemVar.seakchain.history[0].y * attrs->x20;
    itSeakChain_clamp_x10(cur, attrs);
    if (ABS(cur->vel.x) > attrs->x24) {
        if (cur->vel.x > 0.0f) {
            cur->vel.x = attrs->x24;
        } else {
            cur->vel.x = -attrs->x24;
        }
    }
    if (cur->vel.y > attrs->x18 - attrs->x28) {
        cur->vel.y -= attrs->x18;
    } else if (cur->vel.y < -attrs->x18 - attrs->x28) {
        cur->vel.y += attrs->x18;
    }
    if (ABS(cur->vel.y) > attrs->x2C) {
        if (cur->vel.y > 0.0f) {
            cur->vel.y = attrs->x2C;
        } else {
            cur->vel.y = -attrs->x2C;
        }
    }

    it_802A4420(cur);

    scale = 1.0f;
    scale *= attrs->x34;
    if (it_802A3C98(&cur->pos, target, &stack.dir) > attrs->x4) {
        cur->pos.x = stack.dir.x * attrs->x4 + target->x;
        cur->pos.y = stack.dir.y * attrs->x4 + target->y;
        cur->pos.z = stack.dir.z * attrs->x4 + target->z;
    }

    use_arg = ip->xDD4_itemVar.seakchain.x10;
    lstick_x = ftSk_SpecialS_80110F58(ip->xDD4_itemVar.seakchain.parent_gobj);
    lstick_y = ftSk_SpecialS_80110F64(ip->xDD4_itemVar.seakchain.parent_gobj);
    if (ABS(lstick_x) < attrs->x48 && ABS(lstick_y) < attrs->x48) {
        mode = 3;
    } else if (lstick_y < -0.5f) {
        mode = 1;
    } else {
        mode = 2;
    }

    counter = 0;
    while (iter != NULL) {
        f32 dx, dy;
        s32 idx = (s32) (0.5f * (counter + 1));
        f32 fx = attrs->x1C;
        f32 fy = attrs->x20;
        dx = scale * (ip->xDD4_itemVar.seakchain.history[idx].x * fx);
        dy = scale * (ip->xDD4_itemVar.seakchain.history[idx].y * fy);
        if (use_arg != 0) {
            dx *= attrs->x30;
        }
        iter->vel.x += dx;
        iter->vel.y += dy;

        {
            f32 lim = attrs->x10 * scale;
            if (iter->vel.x > lim) {
                iter->vel.x -= lim;
            } else if (iter->vel.x < -attrs->x10 * scale) {
                iter->vel.x += lim;
            } else {
                iter->vel.x = 0.0f;
            }
        }
        {
            if (ABS(iter->vel.x) > attrs->x24 * scale) {
                if (iter->vel.x > 0.0f) {
                    iter->vel.x = attrs->x24 * scale;
                } else {
                    iter->vel.x = -attrs->x24 * scale;
                }
            }
        }
        {
            f32 vy_lim = attrs->x18 * scale;
            if (iter->vel.y > vy_lim - attrs->x28) {
                iter->vel.y -= vy_lim;
            } else if (iter->vel.y < -attrs->x18 * scale - attrs->x28) {
                iter->vel.y += vy_lim;
            }
        }
        {
            if (ABS(iter->vel.y) > attrs->x2C * scale) {
                if (iter->vel.y > 0.0f) {
                    iter->vel.y = attrs->x2C * scale;
                } else {
                    iter->vel.y = -attrs->x2C * scale;
                }
            }
        }

        counter++;
        scale *= attrs->x34;
        it_802A4420(iter);

        if (counter > mode) {
            if (counter % 5 == 0) {
                env_flags = it_802BBAEC(iter, coll_arg, attrs->x4);
            } else {
                env_flags = it_802BBAEC(iter, 0, attrs->x4);
            }
        } else {
            env_flags = 0;
        }
        env_flags &= 0x18000;
        if (env_flags != 0) {
            if (ABS(iter->vel.y) > attrs->x60) {
                iter->vel.y *= -attrs->x5C;
            } else {
                itSeakChain_clamp_x14(iter, attrs);
                iter->vel.y = 0.0f;
            }
        }

        if (it_802A3C98(&iter->pos, &cur->pos, &stack.dir) > attrs->x4) {
            iter->pos.x = stack.dir.x * attrs->x4 + cur->pos.x;
            iter->pos.y = stack.dir.y * attrs->x4 + cur->pos.y;
            iter->pos.z = stack.dir.z * attrs->x4 + cur->pos.z;
        }

        cur = iter;
        iter = iter->prev;
    }
    ip->xDD4_itemVar.seakchain.x10 = env_flags;
}

int it_802BC94C(ItemLink* arg0, Vec3* arg1, itSeakChain_Attrs* sa, f32 farg0)
{
    u8 _padA[8];
    ItemLink *var_r30, *var_r29;
    Vec3 sp18;
    float var_f1;

    for (var_r29 = arg0, var_r30 = arg0->prev;
         var_r30 != NULL && !var_r29->x2C_b0;)
    {
        var_r29 = var_r30;
        var_r30 = var_r30->prev;
    }
    var_f1 = it_802A3C98(&var_r29->pos, arg1, &sp18);
    while (var_r30 != NULL && farg0 > var_f1) {
        var_r29->x2C_b0 = false;
        var_f1 = it_802A3C98(&var_r30->pos, arg1, &sp18);
        var_r29 = var_r30;
        var_r30 = var_r30->prev;
    }
    var_f1 -= farg0;
    if (var_f1 > sa->x4) {
        var_f1 = sa->x4;
    }
    it_802BBC38(var_r29, arg1, sa, var_f1);
    if (var_r30 != NULL) {
        return false;
    }
    return true;
}

void it_802BCA30(Item* ip)
{
    ItemLink* link = ip->xDD4_itemVar.seakchain.x0;
    HSD_JObj* jobj0 = link->gobj->hsd_obj;
    Mtx mtx;
    Vec3 vec = it_803B868C;
    PAD_STACK(3 * 4);
    HSD_JObjSetupMatrix(link->jobj);
    PSMTXIdentity(mtx);
    mtx[0][3] = vec.x;
    mtx[1][3] = vec.y;
    mtx[2][3] = vec.z;
    PSMTXConcat(link->jobj->mtx, mtx, mtx);
    HSD_JObjCopyMtx(jobj0, mtx);
    jobj0->flags |=
        JOBJ_USER_DEF_MTX | JOBJ_MTX_INDEP_PARENT | JOBJ_MTX_INDEP_SRT;
    HSD_JObjSetMtxDirty(jobj0);
}

static inline ItemLink* it_802BCB88_prev(ItemLink* link)
{
    return link->prev;
}

void it_802BCB88(Item* ip, Vec3* vec)
{
    ItemLink* link = ip->xDD4_itemVar.seakchain.x4;
    itSeakChain_Attrs* sa = ip->xC4_article_data->x4_specialAttributes;
    HSD_JObj* jobj;
    int count;
    int stride = sa->x0 / 3;
    while (!link->x2C_b0) {
        link = link->prev;
    }
    {
        ItemLink* cur;
        Vec3 pos0;
        count = 0;
        for (; link != NULL; link = link->prev) {
            cur = link->next;
            if (cur != NULL) {
                if (cur->x2C_b0) {
                    pos0 = cur->pos;
                } else {
                    pos0 = *vec;
                }
            } else {
                pos0 = *vec;
            }
            cur = it_802BCB88_prev(link);
            {
                Vec3 pos1;
                if (cur != NULL) {
                    pos1 = cur->pos;
                } else {
                    pos1 = link->pos;
                }
                {
                    jobj = GET_JOBJ(link->gobj);
                    {
                        Vec3 translate = link->pos;
                        HSD_JObjSetTranslate(jobj, &translate);
                        if (count % stride == 0) {
                            int i;
                            for (i = 3; i > count / stride; i--) {
                                ftSk_SpecialS_UpdateHitboxes(
                                    ip->xDD4_itemVar.seakchain.parent_gobj,
                                    &translate, i - 1);
                            }
                        }
                        if (link->prev == NULL) {
                            ftSk_SpecialS_UpdateHitboxes(
                                ip->xDD4_itemVar.seakchain.parent_gobj,
                                &translate, 3);
                        }
                        count++;
                        {
                            Vec3 dir;
                            dir.x = pos1.x - pos0.x;
                            dir.y = pos1.y - pos0.y;
                            dir.z = pos1.z - pos0.z;
                            lbVector_Normalize(&dir);
                            it_802A6DC8(jobj, &translate, &dir);
                        }
                    }
                    {
                        Mtx mtx;
                        PSMTXCopy(jobj->mtx, mtx);
                        mtx[0][0] *= sa->x4;
                        mtx[1][0] *= sa->x4;
                        mtx[2][0] *= sa->x4;
                        mtx[0][1] *= sa->x4;
                        mtx[1][1] *= sa->x4;
                        mtx[2][1] *= sa->x4;
                        mtx[0][2] *= sa->x4;
                        mtx[1][2] *= sa->x4;
                        mtx[2][2] *= sa->x4;
                        PSMTXCopy(mtx, jobj->mtx);
                    }
                }
            }
        }
    }
}

void it_2725_Logic54_PickedUp(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    PAD_STACK(8);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    item->on_accessory = fn_802BB428;
}

void it_802BCED4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(2 * 4);
    ftColl_8007AFF8(ip->xDD4_itemVar.seakchain.parent_gobj);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
    ip->on_accessory = fn_802BB694;
}

void it_802BCF2C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(2 * 4);
    ftColl_8007AFF8(ip->xDD4_itemVar.seakchain.parent_gobj);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    ip->on_accessory = fn_802BB574;
}

void it_802BCF84(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(4);
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
    ip->on_accessory = fn_802BB784;
}

void it_802BCFC4(Item_GObj* gobj, Vec3* vel)
{
    PAD_STACK(2 * 4);
    {
        Item* ip = GET_ITEM(gobj);
        ItemLink* link = ip->xDD4_itemVar.seakchain.x0;
        Vec3 pos;
        PAD_STACK(2 * 4);
        {
            Mtx mtx;
            PAD_STACK(2 * 4);
            PSMTXIdentity(mtx);
            mtx[0][3] = 0.0f;
            mtx[1][3] = 0.0f;
            mtx[2][3] = 0.1f;
            HSD_JObjSetupMatrix(link->jobj);
            PSMTXConcat(link->jobj->mtx, mtx, mtx);
            {
                pos.x = mtx[0][3];
                pos.y = mtx[1][3];
                pos.z = mtx[2][3];
                link->pos = pos;
            }
            it_8026BB68(ip->xDD4_itemVar.seakchain.parent_gobj,
                        &link->coll_data.cur_pos);
            link->coll_data.last_pos = link->coll_data.cur_pos;
            link->x2C_b0 = true;
            link->vel = *vel;
            Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
            ip->on_accessory = fn_802BB44C;
        }
    }
}

void itSeakChain_Logic54_EvtUnk(Item_GObj* gobj, Fighter_GObj* ref_gobj)
{
    Item* item = GET_ITEM(gobj);
    it_8026B894(gobj, ref_gobj);
    if (item->xDD4_itemVar.seakchain.parent_gobj == ref_gobj) {
        item->xDD4_itemVar.seakchain.parent_gobj = NULL;
    }
}
