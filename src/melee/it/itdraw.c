#include "it/itdraw.h"

#include "inlines.h"

#include "cm/camera.h"
#include "ft/ftlib.h"
#include "it/it_2725.h"
#include "lb/lb_00F9.h"
#include "lb/lbcollision.h"
#include "lb/lbgx.h"

#include <baselib/tev.h>

U8Vec4 it_804D5168 = { 0xFF, 0x40, 0x80, 0x80 };

void it_8026EB18(HSD_GObj* gobj, s32 arg1, Vec3* arg2)
{
    Mtx m2;
    MtxPtr var_r30;
    if (arg2 != NULL) {
        HSD_CObj* cobj = HSD_CObjGetCurrent();
        MtxPtr temp_r30 = (MtxPtr) &cobj->view_mtx;
        { ///< @todo This appears in several places in the codebase,
            // it's probably an inline
            Mtx m;
            PAD_STACK(1 * 4);
            PSMTXIdentity((MtxPtr) &m);
            m[0][3] = arg2->x;
            m[1][3] = arg2->y;
            m[2][3] = arg2->z;
            PSMTXConcat(temp_r30, (MtxPtr) &m, (MtxPtr) &m2);
            var_r30 = (MtxPtr) &m2;
        }
    } else {
        var_r30 = NULL;
    }
    HSD_JObjDispAll(GET_JOBJ(gobj), var_r30, HSD_GObj_80390EB8(arg1), 0U);
}

void it_8026EBC8(HSD_GObj* gobj, u16 arg1, u8* arg2)
{
    Item* ip = GET_ITEM(gobj);
    u16 cnt = 0;
    HSD_JObj* jobj;
    HSD_JObj* jobj_parent;
    u8* index = arg2;
    while (cnt < arg1) {
        jobj = ip->xBBC_dynamicBoneTable->bones[*index];
        jobj_parent = HSD_JObjGetParent(jobj);
        if (!(HSD_JObjGetFlags(jobj_parent) & 0x10)) {
            it_80272A18(jobj);
        }
        cnt++;
        index++;
    }
}

void it_8026EC54(HSD_GObj* gobj, u16 arg1, u8* arg2)
{
    Item* ip = GET_ITEM(gobj);
    u16 cnt = 0;
    HSD_JObj* jobj;
    HSD_JObj* jobj_parent;
    u8* index = arg2;
    while (cnt < arg1) {
        jobj = ip->xBBC_dynamicBoneTable->bones[*index];
        jobj_parent = HSD_JObjGetParent(jobj);
        if (!(HSD_JObjGetFlags(jobj_parent) & 0x10)) {
            it_80272A3C(jobj);
        }
        cnt++;
        index++;
    }
}

/// arg1 is some kind of enum type? It gets passed to functions that check if
/// it's 0 or 2 to run
u32 it_8026ECE0(Item_GObj* gobj, u32 arg1)
{
    Item* ip;
    u32 ret;
    u32 idx;

    ret = 0;
    ip = GET_ITEM(gobj);
    if (ip->kind == It_Kind_Unk4) {
        if (ip->xDAA_flag.b0 &&
            (ip->xDD4_itemVar.it_266F.x18.b0 ||
             ip->xDD4_itemVar.it_266F.x18.b1) &&
            lbColl_8000A10C(&ip->xDD4_itemVar.it_266F.x1C, arg1, ip->scl))
        {
            ret = 1;
        }
    } else {
        if (ip->xDAA_flag.b6) {
            if (ip->xDAA_flag.b2) {
                idx = 0U;
                while (idx < 4U) {
                    if (lbColl_80009F54(&ip->x5D4_hitboxes[idx].hit, arg1,
                                        ip->scl) != false)
                    {
                        ret = 1;
                    }
                    idx++;
                }
            }
            if (!ip->xDC8_word.flags.x13 && ip->xDAA_flag.b1) {
                if (ip->xD0C == 0) {
                    idx = 0U;
                    while (idx < ip->xAC8_hurtboxNum) {
                        if (lbColl_8000A244(&ip->xACC_itemHurtbox[idx], arg1,
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
                                            ip->xD0C, arg1, NULL,
                                            0.0f) != false)
                        {
                            ret = 1;
                        }
                        idx++;
                    }
                }
            }
        }
        if (ip->xDAA_flag.b4 && ip->xDC8_word.flags.x15 &&
            (lbGx_8001E2F8((Vec4*) &ip->xBCC_unk, &ip->pos, &it_804D5168, arg1,
                           ip->facing_dir) != false))
        {
            ret = 1;
        }
        if (ip->xDAA_flag.b3 && ip->xDD0_flag.b0 &&
            (lb_800149E0((MtxPtr) &ip->xB54, arg1) != false))
        {
            ret = 1;
        }
    }
    return ret;
}

#define it_8026EECC_VARS(ip)                                                  \
    (*(it_266F_ItemVars**) &((ip)->xDD4_itemVar.it_266F))

static inline void it_8026EECC_inline_1(HSD_GObj* gobj, s32 arg1, Vec3* pos)
{
    Vec3* new_pos = NULL;
    Item* ip = gobj->user_data;

    ip->xDCF_flag.b4 = 1;
    ip->xDCF_flag.b5 = 0;
    it_8026EC54(gobj, it_8026EECC_VARS(ip)->x0, it_8026EECC_VARS(ip)->x4);
    it_8026EBC8(gobj, it_8026EECC_VARS(ip)->x8, it_8026EECC_VARS(ip)->xC);
    if (ip->xDCF_flag.b7) {
        new_pos = pos;
    }
    it_8026EB18(gobj, arg1, new_pos);
    it_8026EBC8(gobj, it_8026EECC_VARS(ip)->x0, it_8026EECC_VARS(ip)->x4);
    it_8026EC54(gobj, it_8026EECC_VARS(ip)->x8, it_8026EECC_VARS(ip)->xC);
}

static inline void it_8026EECC_inline_2(HSD_GObj* gobj, s32 arg1, Vec3* pos)
{
    Item* ip = gobj->user_data;
    Vec3* new_pos = NULL;

    ip->xDCF_flag.b4 = 0;
    ip->xDCF_flag.b5 = 0;
    if (ip->xDCF_flag.b7) {
        new_pos = pos;
    }
    it_8026EB18(gobj, arg1, new_pos);
}

static inline void it_8026EECC_inline_3(HSD_GObj* gobj, s32 arg1, Vec3* pos)
{
    Item* ip = gobj->user_data;
    Vec3* new_pos = NULL;

    ip->xDCF_flag.b4 = 1;
    ip->xDCF_flag.b5 = 1;
    it_8026EC54(gobj, it_8026EECC_VARS(ip)->x0, it_8026EECC_VARS(ip)->x4);
    it_8026EBC8(gobj, it_8026EECC_VARS(ip)->x8, it_8026EECC_VARS(ip)->xC);
    if (ip->xDCF_flag.b7) {
        new_pos = pos;
    } else {
        new_pos = NULL;
    }

    it_8026EB18(gobj, arg1, new_pos);
    it_8026EBC8(gobj, it_8026EECC_VARS(ip)->x0, it_8026EECC_VARS(ip)->x4);
    it_8026EC54(gobj, it_8026EECC_VARS(ip)->x8, it_8026EECC_VARS(ip)->xC);
}

static inline Item* it_8026EECC_inline_0(HSD_GObj* gobj, Vec3* pos)
{
    Item* ip = gobj->user_data;
    ip->xDCF_flag.b7 = 0;
    if ((ip->owner != NULL) && ftLib_80086960(ip->owner)) {
        if (ftLib_80087074(ip->owner, pos)) {
            ip->xDCF_flag.b7 = 1;
        }
    } else {
        pos->x = pos->y = pos->z = 0.0F;
    }
    return gobj->user_data;
}

void it_8026EECC(HSD_GObj* gobj, int arg1)
{
    Item* ip = gobj->user_data;
    Vec3 pos;
    PAD_STACK(48);

    if (ip->xDAA_flag.b7) {
        pos.x = pos.y = pos.z = 0.0F;
        if (ip->xDC8_word.flags.x13) {
            if ((ip->owner == NULL) || !ftLib_80086960(ip->owner) ||
                ftLib_800868D4(ip->owner, gobj))
            {
                ip = it_8026EECC_inline_0(gobj, &pos);
                switch (Camera_80031060()) {
                case 1:
                    if (ip->xDCF_flag.b3) {
                        it_8026EECC_inline_1(gobj, arg1, &pos);
                        it_8026EECC_inline_2(gobj, arg1, &pos);
                        it_8026EECC_inline_3(gobj, arg1, &pos);
                    }
                    break;
                case 0:
                    if (!ip->xDCF_flag.b3) {
                        it_8026EECC_inline_2(gobj, arg1, &pos);
                    }
                    break;
                }
            }
        } else {
            ip = gobj->user_data;
            switch (Camera_80031060()) {
            case 1:
                if (ip->xDCF_flag.b3) {
                    it_8026EECC_inline_1(gobj, arg1, &pos);
                    it_8026EECC_inline_2(gobj, arg1, &pos);
                    it_8026EECC_inline_3(gobj, arg1, &pos);
                }
                break;
            case 0:
                if (!ip->xDCF_flag.b3) {
                    it_8026EECC_inline_2(gobj, arg1, &pos);
                }
                break;
            }
        }
    }
    if (it_8026ECE0((Item_GObj*) gobj, arg1) != 0U) {
        HSD_StateInvalidate(-1);
        HSD_StateInitTev();
        HSD_ClearVtxDesc();
    }
}
