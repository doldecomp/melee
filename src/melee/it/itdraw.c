/**
 * @file itdraw.c
 * @brief Item drawing and rendering dispatch
 * @details Hooks into sysdolphin's GObj rendering pipeline to display items, their dynamic bones, and debug overlays.
 * Module prefix: it (Item)
 */
#include "itdraw.h"

#include "inlines.h"
#include "it_2725.h"
#include <melee/cm/camera.h>
#include <melee/ft/ftlib.h>
#include <melee/lb/lb_0146.h>
#include <melee/lb/lbcollision.h>
#include <melee/lb/lbgx.h>
#include <sysdolphin/baselib/tev.h>

U8Vec4 it_804D5168 = { 0xFF, 0x40, 0x80, 0x80 };

/**
 * @brief Dispatches drawing for an item's JObj tree, applying camera shake if needed.
 */
void it_8026EB18(HSD_GObj* gobj, s32 rendermode, Vec3* shake_offset)
{
    Mtx m2;
    MtxPtr mptr;
    if (shake_offset != NULL) {
        HSD_CObj* cobj = HSD_CObjGetCurrent();
        MtxPtr vmtx = (MtxPtr) &cobj->view_mtx;
        { ///< @todo This appears in several places in the codebase,
            // it's probably an inline
            Mtx m;
            PAD_STACK(4);
            MTXIdentity((MtxPtr) &m);
            m[0][3] = shake_offset->x;
            m[1][3] = shake_offset->y;
            m[2][3] = shake_offset->z;
            MTXConcat(vmtx, (MtxPtr) &m, (MtxPtr) &m2);
            mptr = (MtxPtr) &m2;
        }
    } else {
        mptr = NULL;
    }
    HSD_JObjDispAll(GET_JOBJ(gobj), mptr, HSD_GObj_80390EB8(rendermode), 0);
}

/**
 * @brief Disables rendering for specific dynamic bones within an item.
 */
void it_8026EBC8(HSD_GObj* gobj, u16 count, u8* indices)
{
    Item* ip = GET_ITEM(gobj);
    u16 cnt = 0;
    HSD_JObj* jobj;
    HSD_JObj* jobj_parent;
    u8* index = indices;
    while (cnt < count) {
        jobj = ip->xBBC_dynamicBoneTable->bones[*index];
        jobj_parent = HSD_JObjGetParent(jobj);
        if (!(HSD_JObjGetFlags(jobj_parent) & 0x10)) {
            it_80272A18(jobj);
        }
        cnt++;
        index++;
    }
}

/**
 * @brief Enables rendering for specific dynamic bones within an item.
 */
void it_8026EC54(HSD_GObj* gobj, u16 count, u8* indices)
{
    Item* ip = GET_ITEM(gobj);
    u16 cnt = 0;
    HSD_JObj* jobj;
    HSD_JObj* jobj_parent;
    u8* index = indices;
    while (cnt < count) {
        jobj = ip->xBBC_dynamicBoneTable->bones[*index];
        jobj_parent = HSD_JObjGetParent(jobj);
        if (!(HSD_JObjGetFlags(jobj_parent) & 0x10)) {
            it_80272A3C(jobj);
        }
        cnt++;
        index++;
    }
}

/**
 * @brief Draws debug hitboxes, hurtboxes, and environment collision for items.
 * @param rendermode is some kind of enum type? It gets passed to functions that check if it's 0 or 2 to run
 * @return 1 if any debug graphics were drawn, 0 otherwise.
 */
u32 it_8026ECE0(Item_GObj* gobj, u32 rendermode)
{
    Item* ip;
    u32 ret;
    u32 idx;

    ret = 0;
    ip = GET_ITEM(gobj);
    if (ip->kind == It_Kind_Unk4) {
        if (ip->xDAA.xDAA_flag.x0.b0 &&
            (ip->xDD4_itemVar.it_266F.x18.x0.b0 ||
             ip->xDD4_itemVar.it_266F.x18.x0.b1) &&
            lbColl_8000A10C(&ip->xDD4_itemVar.it_266F.x1C, rendermode, ip->scl))
        {
            ret = 1;
        }
    } else {
        if (ip->xDAA.xDAA_flag.x0.b6) {
            if (ip->xDAA.xDAA_flag.x0.b2) {
                idx = 0U;
                while (idx < 4U) {
                    if (lbColl_80009F54(&ip->x5D4_hitboxes[idx].hit, rendermode,
                                        ip->scl) != false)
                    {
                        ret = 1;
                    }
                    idx++;
                }
            }
            if (!ip->xDC8_word.flags.x13 && ip->xDAA.xDAA_flag.x0.b1) {
                if (ip->xD0C == 0) {
                    idx = 0U;
                    while (idx < ip->xAC8_hurtboxNum) {
                        if (lbColl_8000A244(&ip->xACC_itemHurtbox[idx], rendermode,
                                            NULL, 0.0f) != false)
                        {
                            ret = 1;
                        }
                        idx++;
                    }
                } else {
                    idx = 0U;
                    while (idx < ip->xAC8_hurtboxNum) {
                        if (lbColl_8000A584(&ip->xACC_itemHurtbox[idx],
                                            ip->xD0C, rendermode, NULL,
                                            0.0f) != false)
                        {
                            ret = 1;
                        }
                        idx++;
                    }
                }
            }
        }
        if (ip->xDAA.xDAA_flag.x0.b4 && ip->xDC8_word.flags.x15 &&
            (lbGx_8001E2F8((Vec4*) &ip->xBCC_unk, &ip->pos, &it_804D5168, rendermode,
                           ip->facing_dir) != false))
        {
            ret = 1;
        }
        if (ip->xDAA.xDAA_flag.x0.b3 && ip->xDD0_flag.x0.b0 &&
            (lb_800149E0((MtxPtr) &ip->xB54, rendermode) != false))
        {
            ret = 1;
        }
    }
    return ret;
}

#define it_8026EECC_VARS(ip)                                                  \
    (*(it_266F_ItemVars**) &((ip)->xDD4_itemVar.it_266F))

static inline void it_8026EECC_inline_1(HSD_GObj* gobj, s32 rendermode, Vec3* shake_offset)
{
    Item* ip = GET_ITEM(gobj);

    ip->xDCF_flag.x0.b4 = 1;
    ip->xDCF_flag.x0.b5 = 0;
    it_8026EC54(gobj, it_8026EECC_VARS(ip)->x0, it_8026EECC_VARS(ip)->x4);
    it_8026EBC8(gobj, it_8026EECC_VARS(ip)->x8, it_8026EECC_VARS(ip)->xC);
    it_8026EB18(gobj, rendermode, ip->xDCF_flag.x0.b7 ? shake_offset : NULL);
    it_8026EBC8(gobj, it_8026EECC_VARS(ip)->x0, it_8026EECC_VARS(ip)->x4);
    it_8026EC54(gobj, it_8026EECC_VARS(ip)->x8, it_8026EECC_VARS(ip)->xC);
}

static inline void it_8026EECC_inline_2(HSD_GObj* gobj, s32 rendermode, Vec3* shake_offset)
{
    Item* ip = GET_ITEM(gobj);

    ip->xDCF_flag.x0.b4 = 0;
    ip->xDCF_flag.x0.b5 = 0;
    it_8026EB18(gobj, rendermode, ip->xDCF_flag.x0.b7 ? shake_offset : NULL);
}

static inline void it_8026EECC_inline_3(HSD_GObj* gobj, s32 rendermode, Vec3* shake_offset)
{
    Item* ip = GET_ITEM(gobj);

    ip->xDCF_flag.x0.b4 = 1;
    ip->xDCF_flag.x0.b5 = 1;
    it_8026EC54(gobj, it_8026EECC_VARS(ip)->x0, it_8026EECC_VARS(ip)->x4);
    it_8026EBC8(gobj, it_8026EECC_VARS(ip)->x8, it_8026EECC_VARS(ip)->xC);
    it_8026EB18(gobj, rendermode, ip->xDCF_flag.x0.b7 ? shake_offset : NULL);
    it_8026EBC8(gobj, it_8026EECC_VARS(ip)->x0, it_8026EECC_VARS(ip)->x4);
    it_8026EC54(gobj, it_8026EECC_VARS(ip)->x8, it_8026EECC_VARS(ip)->xC);
}

static inline Item* it_8026EECC_inline_0(HSD_GObj* gobj, Vec3* shake_offset)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDCF_flag.x0.b7 = 0;
    if ((ip->owner != NULL) && ftLib_IsFighter(ip->owner)) {
        if (ftLib_GetShakeOffset(ip->owner, shake_offset)) {
            ip->xDCF_flag.x0.b7 = 1;
        }
    } else {
        shake_offset->x = shake_offset->y = shake_offset->z = 0.0F;
    }
    return GET_ITEM(gobj);
}

static inline void it_8026EECC_inline_sw(HSD_GObj* gobj, s32 rendermode, Vec3* shake_offset)
{
    Item* ip = gobj->user_data;
    switch (Camera_80031060()) {
    case 1:
        if (ip->xDCF_flag.x0.b3) {
            it_8026EECC_inline_1(gobj, rendermode, shake_offset);
            it_8026EECC_inline_2(gobj, rendermode, shake_offset);
            it_8026EECC_inline_3(gobj, rendermode, shake_offset);
        }
        break;
    case 0:
        if (!ip->xDCF_flag.x0.b3) {
            it_8026EECC_inline_2(gobj, rendermode, shake_offset);
        }
        break;
    }
}

/**
 * @brief Main render callback for items. Hooks into sysdolphin GObj display.
 */
void it_8026EECC(HSD_GObj* gobj, intptr_t rendermode)
{
    Item* ip = GET_ITEM(gobj);
    Vec3 shake_offset;

    if (ip->xDAA.xDAA_flag.x0.b7) {
        shake_offset.x = shake_offset.y = shake_offset.z = 0.0F;
        if (ip->xDC8_word.flags.x13) {
            if ((ip->owner == NULL) || !ftLib_IsFighter(ip->owner) ||
                ftLib_IsItemVisible(ip->owner, gobj))
            {
                ip = it_8026EECC_inline_0(gobj, &pos);
                it_8026EECC_inline_sw(gobj, rendermode, &shake_offset);
            }
        } else {
            it_8026EECC_inline_sw(gobj, rendermode, &shake_offset);
        }
    }
    if (it_8026ECE0((Item_GObj*) gobj, rendermode) != 0U) {
        HSD_StateInvalidate(-1);
        HSD_StateInitTev();
        HSD_ClearVtxDesc();
    }
}
