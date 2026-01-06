#include "eflib.h"

#include "efasync.h"
#include "inlines.h"
#include "types.h"

#include <placeholder.h>

#include "baselib/displayfunc.h"

#include "baselib/forward.h"

#include "baselib/gobj.h"
#include "baselib/gobjgxlink.h"
#include "baselib/gobjobject.h"
#include "baselib/gobjplink.h"
#include "baselib/gobjproc.h"
#include "baselib/gobjuserdata.h"
#include "baselib/mtx.h"
#include "baselib/psdisp.h"
#include "baselib/psstructs.h"
#include "baselib/state.h"
#include "dolphin/mtx.h"

#include "ef/forward.h"
#include "ft/forward.h"

#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Bury.h"
#include "gr/grlib.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

// #include <cstddef>
#include <runtime.h>
#include <trigf.h>
#include <baselib/jobj.h>
#include <baselib/particle.h>
#include <baselib/psappsrt.h>

struct UnkStruct8039EFAC {
    char filler0[0x16];
    u16 unk16;
};

// static s8 efLib_803BF7A0[0x18] = "Duplicate Free %08X\n";
// static s8 efLib_803BF7B8[0x4C] = "can't remove no force effect!\n\0\0error
// no parent gobj!\n\0\0Over Anime Call\n"; static s8 efLib_803BF804[0xA] =
// "translate"; static s8 efLib_803BF81C[0x2C] = "!(jobj->flags &
// JOBJ_USE_QUATERNION)";
extern struct _struct_efAsync_803C025C_0xC efAsync_803C025C[51];
HSD_ObjAllocData Effect_AllocData;

struct _struct_efLib_80458EE0_0x8 efLib_80458EE0[16];
// static HSD_JObj** efLib_80458EE0;

struct struct_efLib_80458F60_0x8 {
    // Not sure about any of these types
    /* 0x0 */ HSD_GObj* unk0;
    /* 0x4 */ char pad4[2];
    /* 0x6 */ u16 unk6;
}; // size: 0x8
static struct struct_efLib_80458F60_0x8 efLib_80458F60[8]; // size: 0x40
static s8 efLib_804D39A0[8] = "eflib.c";
static s8 efLib_804D39A8 = 0x30;
static s8 efLib_804D39AC[8] = "jobj.h";
static s8 efLib_804D39B4[8] = "jobj";
static s8 efLib_804D39BC[0xC] = "scale";
u32 efLib_804D64E8;
u32 efLib_804D64EC;
s32 efLib_804D64F0;

void efLib_8005B4B8(void)
{
    HSD_GObj* gobj_1;
    HSD_GObj* gobj_2;
    s32 var_ctr;
    struct _struct_efAsync_803C025C_0xC* var_r3;

    HSD_ObjAllocInit(&Effect_AllocData, 0x2CU, 4U);
    efLib_804D64EC = 0U;
#if 1
    {
        int i;
        for (i = 0; i < 48; i++) {
            efAsync_803C025C[i].unk8 = 0;
        }
    }
#else
    efAsync_803C025C[0].unk8 = 0;
    efAsync_803C025C[1].unk8 = 0;
    efAsync_803C025C[2].unk8 = 0;
    efAsync_803C025C[3].unk8 = 0;
    efAsync_803C025C.unk38 = 0;
    efAsync_803C025C.unk44 = 0;
    efAsync_803C025C.unk50 = 0;
    efAsync_803C025C.unk5C = 0;
    efAsync_803C025C.unk68 = 0;
    efAsync_803C025C.unk74 = 0;
    efAsync_803C025C.unk80 = 0;
    efAsync_803C025C.unk8C = 0;
    efAsync_803C025C.unk98 = 0;
    efAsync_803C025C.unkA4 = 0;
    efAsync_803C025C.unkB0 = 0;
    efAsync_803C025C.unkBC = 0;
    efAsync_803C025C.unkC8 = 0;
    efAsync_803C025C.unkD4 = 0;
    efAsync_803C025C.unkE0 = 0;
    efAsync_803C025C.unkEC = 0;
    efAsync_803C025C.unkF8 = 0;
    efAsync_803C025C.unk104 = 0;
    efAsync_803C025C.unk110 = 0;
    efAsync_803C025C.unk11C = 0;
    efAsync_803C025C.unk128 = 0;
    efAsync_803C025C.unk134 = 0;
    efAsync_803C025C.unk140 = 0;
    efAsync_803C025C.unk14C = 0;
    efAsync_803C025C.unk158 = 0;
    efAsync_803C025C.unk164 = 0;
    efAsync_803C025C.unk170 = 0;
    efAsync_803C025C.unk17C = 0;
    efAsync_803C025C.unk188 = 0;
    efAsync_803C025C.unk194 = 0;
    efAsync_803C025C.unk1A0 = 0;
    efAsync_803C025C.unk1AC = 0;
    efAsync_803C025C.unk1B8 = 0;
    efAsync_803C025C.unk1C4 = 0;
    efAsync_803C025C.unk1D0 = 0;
    efAsync_803C025C.unk1DC = 0;
    efAsync_803C025C.unk1E8 = 0;
    efAsync_803C025C.unk1F4 = 0;
    efAsync_803C025C.unk200 = 0;
    efAsync_803C025C.unk20C = 0;
    efAsync_803C025C.unk218 = 0;
    efAsync_803C025C.unk224 = 0;
    efAsync_803C025C.unk230 = 0;
    efAsync_803C025C.unk23C = 0;
#endif
    // var_r3 = &efAsync_803C025C + (0x30 * 0xC);
    var_r3 = &efAsync_803C025C[48];
    var_ctr = 0x32 - 0x30;
    if (0x30 < 0x32) {
        do {
            var_r3->unk8 = 0;
            var_r3 += 0xC;
            var_ctr--;
        } while (var_ctr != 0);
    }
    hsd_8039D354(0);
    hsd_80398A08(0);
    // hsd_804D7900 = fn_8005DCD0;
    gobj_1 = GObj_Create(8U, 0xBU, 1U);
    GObj_SetupGXLink(gobj_1, fn_8005C904, 7U, 2U);
    HSD_GObjProc_8038FD54(gobj_1, efLib_8005C9A4, 0xFU);
    gobj_2 = GObj_Create(8U, 0xCU, 1U);
    GObj_SetupGXLink(gobj_2, fn_8005C904, 8U, 2U);
    HSD_GObjProc_8038FD54(gobj_2, fn_8005C9D0, 0xFU);
    HSD_JObjSetSPtclCallback(fn_8005DB20);
    HSD_JObjSetDPtclCallback(fn_8005DB70);
    psInitAppSRT(0, 0xA4);
    efAsync_80067980();
#if 1
    {
        int i;
        for (i = 0; i < 6; i++) {
            ((struct struct_efLib_80458F60_0x8*) &efLib_80458F60[i])->unk0 =
                NULL;
            ((struct struct_efLib_80458F60_0x8*) &efLib_80458F60[i])->unk6 =
                0xFF;
        }
    }
#else
    efLib_80458F60.unk0 = 0;
    efLib_80458F60.unk6 = 0xFF;
    efLib_80458F60.unk8 = 0;
    efLib_80458F60.unkE = 0xFF;
    efLib_80458F60.unk10 = 0;
    efLib_80458F60.unk16 = 0xFF;
    efLib_80458F60.unk18 = 0;
    efLib_80458F60.unk1E = 0xFF;
    efLib_80458F60.unk20 = 0;
    efLib_80458F60.unk26 = 0xFF;
    efLib_80458F60.unk28 = 0;
    efLib_80458F60.unk2E = 0xFF;
    efLib_80458F60.unk30 = 0;
    efLib_80458F60.unk36 = 0xFF;
    efLib_80458F60.unk38 = 0;
    efLib_80458F60.unk3E = 0xFF;
#endif
}

void efLib_8005B704(HSD_GObj* arg_gobj, s32 arg1)
{
    HSD_GObj* gobj_1;
    HSD_GObj* gobj_2;
    Effect* eff_1;
    Effect* eff_2;

    gobj_1 = HSD_GObj_Entities->x2C;
    while (gobj_1 != NULL) {
        eff_1 = GET_EFFECT(gobj_1);
        if ((eff_1 != NULL) && (eff_1->parent_gobj == arg_gobj)) {
            eff_1->x26 |= arg1;
        }
        gobj_1 = gobj_1->next;
    }
    gobj_2 = HSD_GObj_Entities->x30;
    while (gobj_2 != NULL) {
        eff_2 = GET_EFFECT(gobj_2);
        if ((eff_2 != NULL) && (eff_2->parent_gobj == arg_gobj)) {
            eff_2->x26 |= arg1;
        }
        gobj_2 = gobj_2->next;
    }
}

void efLib_8005B780(HSD_GObj* gobj)
{
    Effect* effect;
    PAD_STACK(4);

    effect = GET_EFFECT(gobj);
    if ((effect != NULL) && (effect->x29 == 0) && (gobj != NULL)) {
        {
            int i;
            for (i = 0; i < sizeof(struct struct_efLib_80458F60_0x8); i++) {
                if (efLib_80458F60[i].unk0 == gobj) {
                    efLib_80458F60[i].unk0 = NULL;
                }
            }
        }
        if (gobj->obj_kind == HSD_GObj_804D7849) {
            HSD_JObjWalkTree(gobj->hsd_obj, hsd_8039D688, NULL);
        }
        HSD_GObjPLink_80390228(gobj);
    }
}

void efLib_DestroyAll(HSD_GObj* arg_gobj)
{
    HSD_GObj* gobj_2;
    HSD_GObj* gobj_3;
    HSD_GObj* gobj_5;
    HSD_GObj* gobj_4;
    HSD_GObj* gobj_1;
    Effect* eff_1;
    Effect* eff_2;
    PAD_STACK(48);

    {
        int i;
        for (i = 0; i < sizeof(struct struct_efLib_80458F60_0x8); i++) {
            if (efLib_80458F60[i].unk0 == arg_gobj) {
                efLib_80458F60[i].unk0 = NULL;
            }
        }
    }
    gobj_1 = HSD_GObj_Entities->x2C;
    while (gobj_1 != NULL) {
        eff_1 = GET_EFFECT(gobj_1);
        gobj_2 = gobj_1->next;
        if ((eff_1 != NULL) && (eff_1->parent_gobj == arg_gobj)) {
            gobj_3 = eff_1->gobj;
            if (gobj_3->obj_kind == HSD_GObj_804D7849) {
                HSD_JObjWalkTree(gobj_3->hsd_obj, hsd_8039D688, NULL);
            }
            HSD_GObjPLink_80390228(eff_1->gobj);
        }
        gobj_1 = gobj_2;
    }
    gobj_4 = HSD_GObj_Entities->x30;
    while (gobj_4 != NULL) {
        eff_2 = GET_EFFECT(gobj_4);
        gobj_4 = gobj_4->next;
        if ((eff_2 != NULL) && (eff_2->parent_gobj == arg_gobj)) {
            gobj_5 = eff_2->gobj;
            if (gobj_5->obj_kind == HSD_GObj_804D7849) {
                HSD_JObjWalkTree(gobj_5->hsd_obj, hsd_8039D688, NULL);
            }
            HSD_GObjPLink_80390228(eff_2->gobj);
        }
    }
    if (arg_gobj->obj_kind == HSD_GObj_804D7849) {
        HSD_JObjWalkTree(arg_gobj->hsd_obj, hsd_8039D688, NULL);
    }
}

void efLib_PauseAll(HSD_GObj* arg_gobj)
{
    HSD_GObj* gobj_1;
    HSD_GObj* gobj_2;
    Effect* eff_1;
    Effect* eff_2;

    gobj_1 = HSD_GObj_Entities->x2C;
    while (gobj_1 != NULL) {
        eff_1 = GET_EFFECT(gobj_1);
        if ((eff_1 != NULL) && (eff_1->parent_gobj == arg_gobj)) {
            eff_1->x28 = (eff_1->x28 & 0x80) | 1;
        }
        gobj_1 = gobj_1->next;
    }
    gobj_2 = HSD_GObj_Entities->x30;
    while (gobj_2 != NULL) {
        eff_2 = GET_EFFECT(gobj_2);
        if ((eff_2 != NULL) && (eff_2->parent_gobj == arg_gobj)) {
            eff_2->x28 = (eff_2->x28 & 0x80) | 1;
        }
        gobj_2 = gobj_2->next;
    }
}

void efLib_ResumeAll(HSD_GObj* arg_gobj)
{
    HSD_GObj* gobj_1;
    HSD_GObj* gobj_2;
    Effect* eff_1;
    Effect* eff_2;

    gobj_1 = HSD_GObj_Entities->x2C;
    while (gobj_1 != NULL) {
        eff_1 = GET_EFFECT(gobj_1);
        if ((eff_1 != NULL) && (eff_1->parent_gobj == arg_gobj)) {
            eff_1->x28 &= 0x80;
        }
        gobj_1 = gobj_1->next;
    }
    gobj_2 = HSD_GObj_Entities->x30;
    while (gobj_2 != NULL) {
        eff_2 = GET_EFFECT(gobj_2);
        if ((eff_2 != NULL) && (eff_2->parent_gobj == arg_gobj)) {
            eff_2->x28 &= 0x80;
        }
        gobj_2 = gobj_2->next;
    }
}

// Arg is type Effect*, but forced to be void to fit the function template in
// GObj_InitUserData
void Effect_RemoveUserData(void* effect)
{
    if (((Effect*) effect)->gobj != NULL) {
        if (((Effect*) effect)->x29 == 0) {
            efLib_804D64EC--;
        }
        HSD_ObjFree(&Effect_AllocData, effect);
        return;
    }
    OSReport("Duplicate Free %08X\n", effect);
    __assert("eflib.c", 0x35U, "0");
}

#pragma dont_inline on
void efLib_8005BBB4(u32 arg1, f32 arg8)
{
    HSD_GObj* gobj;
    HSD_GObj* next;
    u32 unused1;
    f32 unused2;

    unused1 = arg1;
    unused2 = arg8;

    gobj = HSD_GObj_Entities->x2C;
    while (gobj != NULL) {
        next = gobj->next;
        efLib_8005B780(gobj);
        if (efLib_804D64EC < 0x40U) {
            return;
        }
        gobj = next;
    }

    gobj = HSD_GObj_Entities->x30;
    while (gobj != NULL) {
        next = gobj->next;
        efLib_8005B780(gobj);
        if (efLib_804D64EC < 0x40U) {
            return;
        }
        gobj = next;
    }

    OSReport("can't remove no force effect!\n\0\0error no parent "
             "gobj!\n\0\0Over Anime Call\n");
    __assert("eflib.c", 0x4DU, "0");

#if 0
loop_3:
    if (gobj == NULL) {
        gobj = HSD_GObj_Entities->x30;
    loop_7:
        if (gobj == NULL) {
            OSReport("can't remove no force effect!\n\0\0error no parent "
                     "gobj!\n\0\0Over Anime Call\n",
                     var_r4, var_f1);
            __assert("eflib.c", 0x4DU, "0");
        } else {
            gobj_3 = gobj_2->next;
            // temp_ret = efLib_8005B780(gobj_2); // which gobj?
            // efLib_8005B780(gobj_2);
            // var_f1 = (bitwise f32) temp_ret;
            // var_r4 = (u32) (u64) temp_ret;
            if (efLib_804D64EC >= 0x40U) {
                gobj_2 = gobj_3;
                goto loop_7;
            }
        }
    } else {
        gobj_4 = gobj_1->next;
        // temp_ret_2 = efLib_8005B780();
        // efLib_8005B780(gobj_1);
        // var_f1 = (bitwise f32) temp_ret_2;
        // var_r4 = (u32) (u64) temp_ret_2;
        if ((u32) efLib_804D64EC >= 0x40U) {
            gobj_1 = gobj_4;
            goto loop_3;
        }
    }
#endif
}
#pragma dont_inline reset

void fn_8005BC50(HSD_GObj* gobj)
{
    Vec3 sp1C;
    efLib_UnkCallback eff_cb;
    HSD_JObj* jobj_2;
    HSD_JObj* jobj_4;
    HSD_JObj* jobj_3;
    u16 u16_1;
    s8 s8_1;
    u8 bit_chk;
    HSD_JObj* jobj_1;
    Effect* effect;

    effect = GET_EFFECT(gobj);
    jobj_1 = GET_JOBJ(gobj);
    bit_chk = effect->x28;
    switch (bit_chk) {
    case 1:
        effect->x28++;
        /* fallthrough */
    default:
        u16_1 = effect->x24;
        if (u16_1 != 0) {
            u16_1--;
            effect->x24 = u16_1;
            if (u16_1 == 0) {
                HSD_GObjPLink_80390228(gobj);
                return;
            }
        }
        s8_1 = effect->x27;
        if (s8_1 != 0) {
            jobj_2 = effect->xC;
            if (jobj_2 != NULL) {
                if (jobj_2 == NULL) {
                    jobj_3 = NULL;
                } else {
                    jobj_3 = jobj_2->parent;
                }
                if (jobj_3 != NULL) {
                    if (jobj_2 != NULL) {
                        HSD_JObjMtxIsDirty(jobj_2);
                    }
                    if (effect->x27 & 1) {
                        jobj_4 = effect->xC;
                        HSD_MtxGetScale(HSD_JObjGetMtxPtr(jobj_4), &sp1C);
                    }
                } else if (s8_1 & 1) {
                    HSD_JObjGetScale(jobj_1, &sp1C);
                }
                if (effect->x27 & 1) {
                    sp1C.x = sp1C.z = sp1C.y;
                    HSD_JObjSetScale(jobj_2, &sp1C);
                }
            }
        }
        HSD_JObjAnimAll(jobj_1);
        eff_cb = effect->x10;
        if (eff_cb != NULL) {
            eff_cb(effect);
        }
    case 2:
        return;
    }
}

Effect* efLib_8005BE88(int arg0, HSD_GObj* parent_gobj)
{
    Effect* ep;
    EffectDesc* desc;

    // desc = (void*) M2C_FIELD((&efAsync_803C025C + ((arg0 / 1000) * 0xC)),
    // s32*,
    //                          8) +
    //        ((arg0 % 1000) * 0x14);
    desc = NULL;

    if (efLib_804D64E8 == 0) {
        if (efLib_804D64EC >= 64) {
            // efLib_8005BBB4();
            efLib_8005BBB4(arg0, 0);
        }
        efLib_804D64EC += 1;
    }
    {
        Effect* ep1 = HSD_ObjAlloc(&Effect_AllocData);
        {
            Effect* ep2 = ep1;
            if (ep2 == NULL) {
                ep = NULL;
            } else {
                ep2->x0 = NULL;
                ep = ep2;
                ep2->gobj = NULL;
                ep2->xC = 0;
                ep2->x10 = 0;
                ep2->x28 = 0;
                ep2->x26 = 0;
                ep2->x27 = 0;
                ep2->x29 = efLib_804D64E8;
            }
        }
        if (ep == NULL) {
            return NULL;
        }
        if (parent_gobj == NULL && ep->x29) {
            OSReport("error no parent gobj!\n", ep1, ep1);
            __assert("eflib.c", 177, "0");
        }
    }
    {
        HSD_GObj* ret_gobj;
        { ///@ todo Inline that returns @c ret_gobj?
            u8 p_link;
            if (arg0 >= 27 || arg0 < 25) {
                p_link = 11;
            } else {
                p_link = 12;
            }
            ep->parent_gobj = parent_gobj;
            ret_gobj = GObj_Create(HSD_GOBJ_CLASS_EFFECT, p_link, 0);
        }
        {
            HSD_GObj* gobj = ret_gobj;
            ep->gobj = gobj;
            if (gobj == NULL) {
                if (ep->gobj != NULL) {
                    if (M2C_FIELD(ep, u8*, 41) == 0) {
                        efLib_804D64EC -= 1;
                    }
                    HSD_ObjFree(&Effect_AllocData, ep);
                } else {
                    OSReport("Duplicate Free %08X\n", ep, ret_gobj);
                    __assert("eflib.c", 0x35, "0");
                }
                return NULL;
            }
        }
    }
    GObj_SetupGXLink(ep->gobj, HSD_GObj_JObjCallback, 7, 1);
    GObj_InitUserData(ep->gobj, 8, Effect_RemoveUserData, ep);
    {
        HSD_JObj* jobj = HSD_JObjLoadJoint(desc->model_desc.joint);
        if (jobj == NULL) {
            HSD_GObjPLink_80390228(ep->gobj);
            return NULL;
        }
        HSD_GObjObject_80390A70(ep->gobj, HSD_GObj_804D7849, jobj);
        if (((10.0f * desc->x0) / /* % */ 10) != 0) {
            lb_80011C18(jobj, 0x08000000);
        }
        ep->x24 = desc->x0;
        if (ep->x24 != 0) {
            ++ep->x24;
        }
        {
            HSD_ShapeAnimJoint* sjoint = desc->model_desc.shapeanim_joint;
            HSD_AnimJoint* ajoint = desc->model_desc.animjoint;
            intptr_t temp_r3_5 = -((intptr_t) sjoint);
            HSD_MatAnimJoint* mjoint = desc->model_desc.matanim_joint;
            intptr_t temp_r3_6 = -((intptr_t) ajoint);
            if ((((temp_r3_5 - (temp_r3_5 - 1)) - !M2C_CARRY) |
                 (((temp_r3_6 - (temp_r3_6 - 1)) - !M2C_CARRY) | !!mjoint)) !=
                0)
            {
                HSD_JObjAddAnimAll(jobj, ajoint, mjoint, sjoint);
                HSD_JObjReqAnimAll(jobj, 0.0f);
                {
                    s32 temp_r5_2 = efLib_804D64F0;
                    s32 temp_r4_2 = temp_r5_2 + 1;
                    s32 temp_r3_7 = temp_r5_2 * 4;
                    efLib_804D64F0 = temp_r4_2;
                    efLib_80458EE0[temp_r3_7].unk0 = jobj;
                    if (efLib_804D64F0 >= 32) {
                        OSReport("Over Anime Call\n", temp_r4_2, temp_r5_2);
                        __assert("eflib.c", 224, "0");
                    }
                }
            }
        }
    }
    HSD_GObjProc_8038FD54(ep->gobj, fn_8005BC50, 15);
    return ep;
}

Effect* efLib_8005C1B4(u32 arg0, HSD_GObj* arg_gobj, HSD_JObj* arg_jobj)
{
    Vec3 sp1C;
    Effect* eff_1;
    HSD_JObj* jobj_1;

    eff_1 = efLib_8005BE88(arg0, arg_gobj);
    if (eff_1 != NULL) {
        if ((jobj_1 = GET_JOBJ(eff_1->gobj)) == NULL) {
            HSD_GObjPLink_80390228(eff_1->gobj);
            return NULL;
        }
        lb_8000C1C0(jobj_1, arg_jobj);
        lb_8000B1CC(arg_jobj, NULL, &sp1C);
        HSD_JObjSetTranslate(jobj_1, &sp1C);
        eff_1->xC = arg_jobj;
    }
    return eff_1;
}

Effect* efLib_8005C2BC(u32 arg0, HSD_GObj* arg_gobj, HSD_JObj* arg_jobj)
{
    Vec3 sp24;
    Effect* eff_1;
    HSD_JObj* jobj_1;

    eff_1 = efLib_8005BE88(arg0, arg_gobj);
    if (eff_1 != NULL) {
        jobj_1 = GET_JOBJ(eff_1->gobj);
        if (jobj_1 == NULL) {
            HSD_GObjPLink_80390228(eff_1->gobj);
            eff_1 = NULL;
        } else {
            lb_8000C1C0(jobj_1, arg_jobj);
            lb_8000B1CC(arg_jobj, NULL, &sp24);
            HSD_JObjSetTranslate(jobj_1, &sp24);
            eff_1->xC = arg_jobj;
        }
    }
    if (eff_1 != NULL) {
        lb_8000C290(GET_JOBJ(eff_1->gobj), arg_jobj);
    }
    return eff_1;
}

Effect* efLib_8005C3DC(u32 arg0, HSD_GObj* arg_gobj, HSD_JObj* arg_jobj)
{
    Vec3 sp34;
    Vec3 sp28;
    Effect* eff_1;
    HSD_GObj* gobj_1;
    HSD_JObj* jobj_1;
    HSD_JObj* jobj_2;

    eff_1 = efLib_8005BE88(arg0, arg_gobj);
    if (eff_1 != NULL) {
        gobj_1 = eff_1->gobj;
        jobj_1 = GET_JOBJ(gobj_1);
        if (jobj_1 == NULL) {
            HSD_GObjPLink_80390228(gobj_1);
            eff_1 = NULL;
        } else {
            lb_8000C1C0(jobj_1, arg_jobj);
            lb_8000B1CC(arg_jobj, NULL, &sp28);
            HSD_JObjSetTranslate(jobj_1, &sp28);
            eff_1->xC = arg_jobj;
        }
    }
    if (eff_1 != NULL) {
        jobj_1 = GET_JOBJ(arg_gobj);
        HSD_JObjGetScale(jobj_1, &sp34);
        sp34.x = sp34.z = sp34.y;
        jobj_2 = GET_JOBJ(eff_1->gobj);
        HSD_JObjSetScale(jobj_2, &sp34);
    }
    return eff_1;
}

// #pragma dont_inline on
Effect* efLib_8005C5C4(u32 arg0, HSD_GObj* arg_gobj, HSD_JObj* arg_jobj)
{
    Vec3 sp2C;
    Effect* eff_1;
    HSD_JObj* jobj_1;
    HSD_JObj* jobj_2;

    eff_1 = efLib_8005C1B4(arg0, arg_gobj, arg_jobj);
    if (eff_1 != NULL) {
        lb_8000C290(GET_JOBJ(eff_1->gobj), arg_jobj);
    }
    if (eff_1 != NULL) {
        jobj_1 = GET_JOBJ(arg_gobj);
        HSD_JObjGetScale(jobj_1, &sp2C);
        jobj_2 = GET_JOBJ(eff_1->gobj);
        HSD_JObjSetScale(jobj_2, &sp2C);
    }
    return eff_1;
}

Effect* efLib_8005C6F4(u32 arg0, HSD_GObj* arg_gobj, void* unused_arg)
{
    Vec3 sp20;
    Effect* eff_1;
    HSD_JObj* jobj_1;
    HSD_JObj* jobj_2;

    eff_1 = efLib_8005C1B4(arg0, arg_gobj, NULL);
    if (eff_1 != NULL) {
        jobj_1 = GET_JOBJ(arg_gobj);
        HSD_JObjGetScale(jobj_1, &sp20);
        jobj_2 = GET_JOBJ(eff_1->gobj);
        HSD_JObjSetScale(jobj_2, &sp20);
    }
    if (eff_1 != NULL) {
        eff_1->x10 = efLib_8005E2B4;
    }
    return eff_1;
}
// #pragma dont_inline reset

Effect* efLib_8005C814(u32 arg0, HSD_GObj* arg_gobj, Vec3* arg_vec3)
{
    HSD_JObj* jobj_1;
    Effect* eff_1;

    eff_1 = efLib_8005BE88(arg0, arg_gobj);
    if (eff_1 != NULL) {
        jobj_1 = GET_JOBJ(eff_1->gobj);
        (void) jobj_1;
        HSD_JObjSetTranslate(jobj_1, arg_vec3);
    }
    return eff_1;
}

void fn_8005C904(HSD_GObj* gobj, int arg1)
{
    u32 var_r31;

    switch (arg1) {
    case 0:
        var_r31 = 0;
        break;
    case 1:
        var_r31 = 1;
        break;
    case 2:
        var_r31 = 2;
        break;
    default:
        return;
    }
    HSD_StateSetColorUpdate(1);
    if (gobj->gx_link == 7) {
        psDispParticles(5, var_r31);
        return;
    }
    psDispParticles(2, var_r31);
    return;
}

void efLib_8005C9A4(HSD_GObj* gobj)
{
    hsd_8039CEAC(0x60000);
    hsd_8039EE24(0x60000);
}

void fn_8005C9D0(HSD_GObj* gobj)
{
    hsd_8039CEAC(0x10000);
    hsd_8039EE24(0x10000);
}

HSD_Generator* efLib_8005C9FC(s32 arg0, Vec3* arg_vec3)
{
    HSD_Generator* generator;
    u8 var_r3;

    var_r3 = 0;
    switch (arg0) {
    case 0x121:
        var_r3 = 2;
        break;
    case 0xFF:
    case 0x7918:
    case 0xFC:
    case 0xF7:
        var_r3 = 1;
        break;
    }
    generator = hsd_8039F05C(var_r3, (arg0 / 1000), arg0);
    if (generator != NULL) {
        generator->pos.x = arg_vec3->x;
        generator->pos.y = arg_vec3->y;
        generator->pos.z = arg_vec3->z;
    }
    return generator;
}

HSD_Generator* efLib_8005CAB0(s32 arg0)
{
    HSD_psAppSRT* psAppSRT;
    HSD_Generator* generator;

    generator = hsd_8039F05C(0, (arg0 / 1000), arg0);
    if (generator != NULL) {
        if ((psAppSRT = generator->appsrt) == NULL) {
            psAppSRT = psAddGeneratorAppSRT_begin(generator, 1);
        }
        if (psAppSRT == NULL) {
            hsd_8039D4DC(generator);
            return NULL;
        }
    }
    return generator;
}

HSD_Generator* efLib_8005CB34(s32 arg0, Vec3* arg_vec3, f32 arg2)
{
    HSD_psAppSRT* psAppSRT;
    HSD_Generator* generator;

    generator = hsd_8039F05C(0, (arg0 / 1000), arg0);
    if (generator != NULL) {
        psAppSRT = generator->appsrt;
        if (psAppSRT == NULL) {
            psAppSRT = psAddGeneratorAppSRT_begin(generator, 1);
        }
        if (psAppSRT == NULL) {
            hsd_8039D4DC(generator);
            generator = NULL;
        }
    }
    if (generator != NULL) {
        generator->appsrt->translate = *arg_vec3;
        if (arg2 < 0.0f) {
            generator->kind |= 0x40000;
            generator->appsrt->rot.y = -M_PI_2;
        } else {
            generator->appsrt->rot.y = M_PI_2;
        }
    }
    return generator;
}

HSD_Generator* efLib_8005CC2C(s32 arg0, HSD_JObj* jobj)
{
    HSD_Generator* generator = hsd_8039EFAC(0, arg0 / 1000, arg0, jobj);
    if (generator != NULL) {
        generator->type &= ~PSAPPSRT_UNK_B10;
    }
    return generator;
}

inline HSD_Generator* efLib_8005C_inline(s32 arg0, HSD_JObj* jobj)
{
    HSD_psAppSRT* psAppSRT;
    HSD_Generator* generator;

    generator = hsd_8039EFAC(0, (arg0 / 1000), arg0, jobj);
    if (generator != NULL) {
        psAppSRT = generator->appsrt;
        if (psAppSRT == NULL) {
            psAppSRT = psAddGeneratorAppSRT_begin(generator, 0);
        }
        if (psAppSRT != NULL) {
            psAppSRT->gp = generator;
        } else {
            hsd_8039D4DC(generator);
            return NULL;
        }
        // generator->type &= ~PSAPPSRT_UNK_B09;
        generator->type &= 0xFFFFF9FF;
        generator->type |= PSAPPSRT_UNK_B11;
    }
    return generator;
}

HSD_Generator* efLib_8005CC84(s32 arg0, HSD_JObj* jobj)
{
    return efLib_8005C_inline(arg0, jobj);
}

HSD_Generator* efLib_8005CD2C(s32 arg0, void* vlist, HSD_GObj* arg_gobj)
{
    Vec3 sp18;
    HSD_Generator* generator;
    HSD_JObj* jobj_1;

    generator = efLib_8005C_inline(arg0, va_arg(vlist, HSD_JObj*));
    if (generator != NULL) {
        jobj_1 = GET_JOBJ(arg_gobj);
        HSD_JObjGetScale(jobj_1, &sp18);
        generator->appsrt->scale.x = generator->appsrt->scale.y =
            generator->appsrt->scale.z = sp18.y;
    }
    return generator;
}

HSD_Generator* efLib_8005CE48(s32 arg0, void* vlist)
{
    HSD_Generator* generator;

    generator = efLib_8005C_inline(arg0, va_arg(vlist, HSD_JObj*));
    if (generator != NULL) {
        generator->appsrt->scale.x = generator->appsrt->scale.y =
            generator->appsrt->scale.z = *va_arg(vlist, f32*);
    }
    return generator;
}

HSD_Generator* efLib_8005CF40(s32 arg0, void* vlist)
{
    HSD_Generator* generator;
    f64 f32_1;

    generator = efLib_8005C_inline(arg0, va_arg(vlist, HSD_JObj*));
    if (generator != NULL) {
        if (*va_arg(vlist, f32*) < 0.0f) {
            f32_1 = -M_PI_2;
        } else {
            f32_1 = M_PI_2;
        }
        generator->appsrt->rot.y = f32_1;
    }
    return generator;
}

HSD_Generator* efLib_8005D044(s32 arg0, void* vlist)
{
    HSD_Generator* generator;
    f64 var_f0;

    generator = efLib_8005C_inline(arg0, va_arg(vlist, HSD_JObj*));
    if (generator != NULL) {
        if (*va_arg(vlist, f32*) < 0.0f) {
            var_f0 = -M_PI_2;
        } else {
            var_f0 = M_PI_2;
        }
        generator->appsrt->rot.y = var_f0;
        generator->appsrt->scale.x = generator->appsrt->scale.y =
            generator->appsrt->scale.z = *va_arg(vlist, f32*);
    }
    return generator;
}

inline HSD_JObj* efLib_8005D174_inner_inline1(HSD_JObj* jobj_1)
{
    HSD_JObj* jobj_2;
    HSD_JObj* jobj_3;
loop_155:
    // do {
    if (jobj_1 == NULL) {
        jobj_2 = NULL;
    } else {
        jobj_2 = jobj_1->parent;
    }
    if (jobj_2 != NULL) {
        if (jobj_1 == NULL) {
            jobj_3 = NULL;
        } else {
            jobj_3 = jobj_1->parent;
        }
        jobj_1 = jobj_3;
        goto loop_155;
    }
    // } while (jobj_1 != NULL & jobj_2 != NULL);
    return jobj_1;
}

inline HSD_psAppSRT* efLib_8005D174_inner_inline2(HSD_Generator* generator_1)
{
    HSD_psAppSRT* psAppSRT_1 = generator_1->appsrt;
    if (psAppSRT_1 == NULL) {
        psAppSRT_1 = psAddGeneratorAppSRT_begin(generator_1, 1);
    }
    return psAppSRT_1;
}

inline void efLib_8005D174_inline1(HSD_Generator* generator_1)
{
    if (generator_1 != NULL) {
        {
            HSD_psAppSRT* psAppSRT_1 =
                efLib_8005D174_inner_inline2(generator_1);
            if (psAppSRT_1 == NULL) {
                hsd_8039D4DC(generator_1);
                generator_1 = NULL;
            }
        }
    }
}

// Sorry for the mess!!
// The inlines were made for convenience of splitting up the inner chunks, not
// by trying to mimic original inlining Likely need to be remade to match how
// inlines were actually written For more work/alternatives for this function
// that may be helpful, see https://decomp.me/scratch/VjlDJ
void efLib_8005D174(int arg0, s32 arg1, HSD_JObj* arg_jobj, s32 arg3)
{
    // HSD_JObj* jobj_2;
    // HSD_JObj* jobj_3;
    HSD_JObj* jobj_1;
    HSD_psAppSRT* psAppSRT_1;
    HSD_Generator* generator_1;
    // Vec3* vec3_1;
    s32 chk;

    chk = 0;
    jobj_1 = arg_jobj;
    if (arg1 != 0xFC) {
        if (arg1 < 0xFC) {
            if (arg1 != 0xA7) {
                if (arg1 < 0xA7) {
                    if (arg1 < 0x2F) {
                        if (arg1 != 0x6) {
                            if (arg1 < 0x6) {
                                if (arg1 == 0x2) {
                                    goto block_428;
                                }
                            } else if (arg1 >= 0x2D) {
                                goto block_258;
                            }
                            goto block_968;
                        }
                    } else if (arg1 != 0xA3) {
                        if (arg1 < 0xA3) {
                            if (arg1 == 0x31) {
                                goto block_258;
                            }
                        }
                        goto block_968;
                    }
                    goto block_428;
                } else if (arg1 != 0xE3) {
                    if (arg1 < 0xE3) {
                        if (arg1 != 0xD4) {
                            if (arg1 < 0xD4) {
                                if (arg1 == 0xAA) {
                                    goto block_428;
                                }
                            }
                            goto block_968;
                        }
                        goto block_64c;
                    }
                    if (arg1 != 0xF7) {
                        if (arg1 < 0xF7) {
                            if (arg1 == 0xF2) {
                                goto block_428;
                            }
                        }
                        goto block_968;
                    }
                    goto block_964;
                }
                goto block_864;
            }
            goto block_428;
        } else if (arg1 != 0x243) {
            if (arg1 < 0x243) {
                if (arg1 != 0x12a) {
                    if (arg1 < 0x12a) {
                        if (arg1 != 0x127) {
                            if (arg1 < 0x127) {
                                if (arg1 == 0xff) {
                                    goto block_964;
                                }
                            }
                            goto block_968;
                        }
                        goto block_2f0;
                    }
                    if (arg1 < 0x16d) {
                        if (arg1 < 0x134) {
                            if (arg1 >= 0x132) {
                                goto block_428;
                            }
                        }
                        goto block_968;
                    }
                    if (arg1 >= 0x171) {
                        goto block_968;
                    }
                    goto block_53c;
                }
                goto block_428;
            }
            if (arg1 != 0x7918) {
                if (arg1 < 0x7918) {
                    if (arg1 < 0x4a38) {
                        if (arg1 == 0x7e2) {
                            goto block_53c;
                        }
                    } else if (arg1 < 0x4a3b) {
                        goto block_170;
                    }
                    goto block_968;
                }
                goto block_150;
            }
            goto block_964;
        }
    }
    goto block_77c;

block_150:
block_170:
    generator_1 = efLib_8005C_inline(arg1, jobj_1);
    if (generator_1 != NULL) {
        jobj_1 = efLib_8005D174_inner_inline1(jobj_1);
        generator_1->appsrt->rot.y = HSD_JObjGetRotationY(jobj_1);
    }
    return;
block_258:
    generator_1 = efLib_8005C_inline(arg1, jobj_1);
    if (generator_1 != NULL) {
        generator_1->type |= 0x1000;
    }
    return;
block_2f0:
    generator_1 = efLib_8005C_inline(arg1, jobj_1);
    if (generator_1 != NULL) {
        jobj_1 = efLib_8005D174_inner_inline1(jobj_1);
        generator_1->appsrt->rot.y = HSD_JObjGetRotationY(jobj_1);
        HSD_JObjGetScale(jobj_1, &generator_1->appsrt->scale);
    }
    return;
block_428:
    generator_1 = efLib_8005C_inline(arg1, jobj_1);
    if (generator_1 != NULL) {
        jobj_1 = efLib_8005D174_inner_inline1(jobj_1);
        HSD_JObjGetScale(jobj_1, &generator_1->appsrt->scale);
    }
    return;
block_53c:
    generator_1 = hsd_8039F05C(0, (arg1 / 1000), arg1);
    efLib_8005D174_inline1(generator_1);
    if (generator_1 != NULL) {
        jobj_1 = efLib_8005D174_inner_inline1(jobj_1);
        generator_1->appsrt->rot.y = HSD_JObjGetRotationY(jobj_1);
        HSD_JObjGetTranslation(jobj_1, &generator_1->appsrt->translate);
    }
    return;
block_64c:
    generator_1 = hsd_8039F05C(2, arg0, arg1);
    if (generator_1 != NULL) {
        psAppSRT_1 = efLib_8005D174_inner_inline2(generator_1);
        if (psAppSRT_1 != NULL) {
            jobj_1 = efLib_8005D174_inner_inline1(jobj_1);
            psAppSRT_1->rot.z = HSD_JObjGetRotationZ(jobj_1);
            HSD_JObjGetTranslation(jobj_1, &psAppSRT_1->translate);
            HSD_JObjGetScale(jobj_1, &psAppSRT_1->scale);
            return;
        }
        hsd_8039D4DC(generator_1);
    }
    return;
block_77c:
    generator_1 = hsd_8039F05C(2, arg0, arg1);
    if (generator_1 != NULL) {
        psAppSRT_1 = efLib_8005D174_inner_inline2(generator_1);
        if (psAppSRT_1 != NULL) {
            jobj_1 = efLib_8005D174_inner_inline1(jobj_1);
            psAppSRT_1->rot.z = HSD_JObjGetRotationZ(jobj_1);
            HSD_JObjGetTranslation(jobj_1, &psAppSRT_1->translate);
            return;
        }
        hsd_8039D4DC(generator_1);
    }
    return;
block_864:
    generator_1 = hsd_8039F05C(0, (arg1 / 1000), arg1);
    efLib_8005D174_inline1(generator_1);
    if (generator_1 != NULL) {
        lb_8000B1CC(jobj_1, NULL, &generator_1->appsrt->translate);
        jobj_1 = efLib_8005D174_inner_inline1(jobj_1);
        HSD_JObjGetScale(jobj_1, &generator_1->appsrt->scale);
    }
    return;
block_964:
    chk = 1;
block_968:
    if (arg3 != 0) {
        hsd_8039EFAC(chk, arg0, arg1, jobj_1);
        return;
    }
    hsd_8039F6CC(chk, arg0, arg1, jobj_1);
    return;
}

void fn_8005DB20(s32 arg0, s32 arg1, s32 arg2, HSD_JObj* arg3)
{
    if (arg1 == 0x1E) {
        grLib_801C99C0(arg1, arg2, arg3, 0);
        return;
    }
    efLib_8005D174(arg1, arg2, arg3, 0);
}

void fn_8005DB70(int arg0, int lo, int hi, HSD_JObj* jobj)
{
    if (lo == 0x1E) {
        grLib_801C99C0(lo, hi, jobj, 1);
        return;
    }
    efLib_8005D174(lo, hi, jobj, 1);
}

void efLib_8005DBC0(HSD_Particle* particle)
{
    Vec3 sp28;
    Vec3 sp1C;
    s32 sp18;
    Vec3 spC;
    HSD_psAppSRT* temp_r5;

    if ((particle != NULL) &&
        (temp_r5 = particle->appsrt, ((temp_r5 == NULL) == 0)))
    {
        sp28 = temp_r5->translate;
        sp1C = temp_r5->scale;
        spC = *(Vec3*) &temp_r5->rot;
        sp18 = temp_r5->rot.w;
        psRemoveParticleAppSRT(particle);
        HSD_PSAppSrt_803A425C(particle, 1);
        // if ((u32) M2C_ERROR(/* Read from unset register $r3 */) != 0U) {
        //     M2C_ERROR(/* Read from unset register $r3 */)->unk8 = sp28;
        //     M2C_ERROR(/* Read from unset register $r3 */)->unkC = sp2C;
        //     M2C_ERROR(/* Read from unset register $r3 */)->unk10 = sp30;
        //     M2C_ERROR(/* Read from unset register $r3 */)->unk14 = spC;
        //     M2C_ERROR(/* Read from unset register $r3 */)->unk18 = sp10;
        //     M2C_ERROR(/* Read from unset register $r3 */)->unk1C = sp14;
        //     M2C_ERROR(/* Read from unset register $r3 */)->unk20 = sp18;
        //     M2C_ERROR(/* Read from unset register $r3 */)->unk24 = sp1C;
        //     M2C_ERROR(/* Read from unset register $r3 */)->unk28 = sp20;
        //     M2C_ERROR(/* Read from unset register $r3 */)->unk2C = sp24;
        //     return;
        // }
        // particle->unk1A = 0; // cmdWait
        // particle->unk4C = 0.0f; // size
        // particle->unk2A = 1; // life
    }
}

// void fn_8005DCD0(void* arg0) {
//     s8* temp_r6;

//     temp_r6 = "Duplicate Free %08X\n";
//     if ((u32) arg0->unk20 == (u32) (hsd_804D0E5C->unk258 + 0x3C)) {
//         hsd_8039D1E4(arg0, (s32) (temp_r6 + 0x70));
//     }
//     if ((u32) arg0->unk20 == (u32) (hsd_804D0E5C->unk25C + 0x3C)) {
//         hsd_8039D1E4(arg0, (s32) (temp_r6 + 0x70));
//     }
//     if ((u32) arg0->unk20 == (u32) (hsd_804D0E5C->unk260 + 0x3C)) {
//         hsd_8039D1E4(arg0, (s32) (temp_r6 + 0x70));
//     }
//     if ((u32) arg0->unk20 == (u32) (hsd_804D0E5C->unk86C + 0x3C)) {
//         hsd_8039D1E4(arg0, (s32) (temp_r6 + 0x70));
//     }
// }

void efLib_8005DDB8(Effect* effect)
{
    Vec3 sp14;
    HSD_JObj* eff_jobj;

    eff_jobj = GET_JOBJ(effect->gobj);
    lb_8000B1CC(effect->xC, NULL, &sp14);
    sp14.y += effect->translate.y;
    HSD_JObjSetTranslate(eff_jobj, &sp14);
}

void efLib_8005DE94(Effect* effect)
{
    HSD_JObj* eff_jobj;
    f32 scale_x;
    f32 scale_y;
    f32 scale_z;

    eff_jobj = GET_JOBJ(effect->gobj);
    scale_x = effect->translate.x * HSD_JObjGetScaleX(eff_jobj);
    HSD_JObjSetScaleX(eff_jobj, scale_x);

    scale_y = effect->translate.x * HSD_JObjGetScaleY(eff_jobj);
    HSD_JObjSetScaleY(eff_jobj, scale_y);

    scale_z = effect->translate.x * HSD_JObjGetScaleZ(eff_jobj);
    HSD_JObjSetScaleZ(eff_jobj, scale_z);
}

void efLib_8005E090(Effect* effect)
{
    f64 temp_d;
    f32 rotate_y;
    HSD_JObj* eff_jobj;
    HSD_JObj* temp_r4;

    temp_r4 = (HSD_JObj*) effect->x14;
    eff_jobj = GET_JOBJ(effect->gobj);
    (void) temp_r4;
    if (temp_r4 != NULL) {
        if (temp_r4->scale.x < 0.0f) {
            temp_d = -M_PI_2;
        } else {
            temp_d = M_PI_2;
        }
        rotate_y = temp_d;
        HSD_JObjSetRotationY(eff_jobj, rotate_y);
    }
    if ((u8) effect->x26 != 0) {
        effect->x24 = 0xBU;
        effect->x10 = NULL;
        HSD_JObjReqAnimAll(eff_jobj, 65.0f);
        return;
    }
    if (effect->x24 == 1) {
        effect->x24 = 6U;
        HSD_JObjReqAnimAll(eff_jobj, 60.0f);
    }
}

void efLib_8005E1D8(Effect* effect)
{
    HSD_JObj* eff_jobj_child;
    f32 translate_z;
    HSD_JObj* eff_jobj;

    eff_jobj = GET_JOBJ(effect->gobj);
    if (eff_jobj == NULL) {
        eff_jobj_child = NULL;
    } else {
        eff_jobj_child = eff_jobj->child;
    }
    translate_z = 2.0f + HSD_JObjGetTranslationZ(eff_jobj_child);
    HSD_JObjSetTranslateZ(eff_jobj_child, translate_z);
}

void efLib_8005E2B4(Effect* effect)
{
    HSD_JObj* eff_jobj;
    f32 rotate_y;
    PAD_STACK(0xC);

    eff_jobj = GET_JOBJ(effect->gobj);
    if (GET_FIGHTER(effect->parent_gobj->user_data)->facing_dir < 0.0f) {
        rotate_y = -M_PI_2; // needs to load as a double/f64?
    } else {
        rotate_y = M_PI_2; // needs to load as a double/f64?
    }
    HSD_JObjSetRotationY(eff_jobj, rotate_y);
}

void efLib_8005E3A0(Effect* arg_effect)
{
    HSD_JObj* jobj_1;
    f64 f32_1;
    Fighter* fighter;

    fighter = GET_FIGHTER(arg_effect->parent_gobj);
    jobj_1 = GET_JOBJ(arg_effect->gobj);
    f32_1 = (f32) M_PI_2 - fighter->mv.co.common.x4;
    if (fighter->facing_dir < 0.0f) {
        HSD_JObjSetRotationY(jobj_1, -M_PI_2);
        HSD_JObjSetRotationZ(jobj_1, f32_1);
    } else {
        HSD_JObjSetRotationY(jobj_1, M_PI_2);
        HSD_JObjSetRotationZ(jobj_1, f32_1);
    }
}

void efLib_8005E648(Effect* arg_effect)
{
    HSD_JObj* jobj_1;
    f32 rotate_y;
    f32 rotate_x;
    f32 translate_z;
    f32 translate_y;
    f32 translate_x;
    f32 f32_1;
    f32 f32_2;
    f32 f32_3;

    jobj_1 = GET_JOBJ(arg_effect->gobj);
    translate_x = HSD_JObjGetTranslationX(jobj_1);
    translate_y = HSD_JObjGetTranslationY(jobj_1);
    translate_z = HSD_JObjGetTranslationZ(jobj_1);
    rotate_x = HSD_JObjGetRotationX(jobj_1);
    rotate_y = HSD_JObjGetRotationY(jobj_1);
    arg_effect->translate.y -= 0.2f;
    f32_1 = translate_x + sinf(rotate_y);
    HSD_JObjSetTranslateX(jobj_1, f32_1);
    f32_2 = translate_y + arg_effect->translate.y;
    HSD_JObjSetTranslateY(jobj_1, f32_2);
    f32_3 = translate_z + cosf(rotate_y);
    HSD_JObjSetTranslateZ(jobj_1, f32_3);
    HSD_JObjSetRotationX(jobj_1, 0.5f + rotate_x);
}

void efLib_8005E950(Effect* arg_effect)
{
    HSD_JObj* jobj_1;
    f32 translate_z;
    f32 translate_y;
    f32 translate_x;
    f32 f32_1;
    f32 f32_2;
    f32 f32_3;

    jobj_1 = GET_JOBJ(arg_effect->gobj);
    translate_x = HSD_JObjGetTranslationX(jobj_1);
    translate_y = HSD_JObjGetTranslationY(jobj_1);
    translate_z = HSD_JObjGetTranslationZ(jobj_1);
    arg_effect->translate.y -= 0.1f;
    f32_1 = translate_x + arg_effect->translate.x;
    HSD_JObjSetTranslateX(jobj_1, f32_1);
    f32_2 = translate_y + arg_effect->translate.y;
    HSD_JObjSetTranslateY(jobj_1, f32_2);
    f32_3 = translate_z + arg_effect->translate.z;
    HSD_JObjSetTranslateZ(jobj_1, f32_3);
}

void efLib_8005EB70(Effect* arg_effect)
{
    if (arg_effect->x24 == 1) {
        hsd_8039EFAC(0, 0, 0x1AB, arg_effect->xC);
        arg_effect->x10 = NULL;
        arg_effect->x24 = 0x27U;
    }
}

void efLib_8005EBC8(Effect* arg_effect)
{
    f64 temp_d;
    Vec3 sp38;
    Vec3 sp2C;
    HSD_JObj* jobj_2;
    f32 rotate_y;
    HSD_JObj* jobj_1;
    void* user_data;
    HSD_GObj* gobj_1;
    PAD_STACK(0xC);

    gobj_1 = arg_effect->parent_gobj;
    jobj_1 = GET_JOBJ(gobj_1);
    jobj_2 = GET_JOBJ(arg_effect->gobj);
    user_data = gobj_1->user_data;
    user_data = (void*) GET_FIGHTER(gobj_1);
    HSD_JObjGetScale(jobj_1, &sp38);
    HSD_JObjGetScale(jobj_2, &sp2C);
    sp38.x *= sp2C.x;
    sp38.y *= sp2C.y;
    sp38.z *= sp2C.z;
    HSD_JObjSetScale(jobj_2, &sp38);

    if (((Fighter*) user_data)->facing_dir < 0.0f) {
        temp_d = -M_PI_2;
    } else {
        temp_d = M_PI_2;
    }
    rotate_y = temp_d;
    HSD_JObjSetRotationY(jobj_2, rotate_y);
}

void efLib_8005EDDC(Effect* arg_effect)
{
    HSD_JObj* jobj_1;
    f32 rotate_z;

    jobj_1 = GET_JOBJ(arg_effect->gobj);
    if ((GET_FIGHTER(arg_effect->parent_gobj))->facing_dir < 0.0f) {
        HSD_JObjSetRotationY(jobj_1, -M_PI_2);
        rotate_z = arg_effect->translate.z;
        HSD_JObjSetRotationZ(jobj_1, rotate_z);
    } else {
        HSD_JObjSetRotationY(jobj_1, M_PI_2);
        rotate_z = -arg_effect->translate.z;
        HSD_JObjSetRotationZ(jobj_1, rotate_z);
    }
}

void efLib_8005F08C(Effect* arg_effect)
{
    f32 rotate_z;
    HSD_JObj* jobj_1;
    HSD_JObj* jobj_3;
    HSD_JObj* jobj_2;
    Fighter* fighter;

    jobj_1 = GET_JOBJ(arg_effect->gobj);
    if (jobj_1 == NULL) {
        jobj_2 = NULL;
    } else {
        jobj_2 = jobj_1->child;
    }
    if (jobj_2 == NULL) {
        jobj_3 = NULL;
    } else {
        jobj_3 = jobj_2->next;
    }
    fighter = GET_FIGHTER(arg_effect->parent_gobj);
    if (fighter->motion_id == 349) {
        HSD_JObjClearFlagsAll(jobj_3, 0x10U);
    } else {
        HSD_JObjSetFlagsAll(jobj_3, 0x10U);
    }
    if ((fighter->cmd_vars[3] != 0U) && ((s32) fighter->mv.co.common.xC != 0))
    {
        rotate_z = -atan2f(fighter->coll_data.floor.normal.x,
                           fighter->coll_data.floor.normal.y);
        HSD_JObjSetRotationZ(jobj_1, rotate_z);
    } else {
        HSD_JObjSetRotationZ(jobj_1, 0.0f);
    }
}

void efLib_8005F270(Effect* arg_effect)
{
    HSD_JObj* jobj_1;
    HSD_JObj* jobj_3;
    HSD_JObj* jobj_2;
    f32 rotate_z;
    Fighter* fighter;

    jobj_1 = GET_JOBJ(arg_effect->gobj);
    if (jobj_1 == NULL) {
        jobj_2 = NULL;
    } else {
        jobj_2 = jobj_1->child;
    }
    if (jobj_2 == NULL) {
        jobj_3 = NULL;
    } else {
        jobj_3 = jobj_2->next;
    }
    fighter = GET_FIGHTER(arg_effect->parent_gobj);
    if (fighter->motion_id == 357) { // Special state 16
        HSD_JObjClearFlagsAll(jobj_3, 0x10U);
    } else {
        HSD_JObjSetFlagsAll(jobj_3, 0x10U);
    }
    if ((fighter->cmd_vars[3] != 0U) && ((s32) fighter->mv.co.common.xC != 0))
    {
        rotate_z = -atan2f(fighter->coll_data.floor.normal.x,
                           fighter->coll_data.floor.normal.y);
        HSD_JObjSetRotationZ(jobj_1, rotate_z);
    } else {
        HSD_JObjSetRotationZ(jobj_1, 0.0f);
    }
}

void efLib_8005F454(Effect* arg_effect)
{
    f32 rotate_z;
    HSD_JObj* jobj_1;
    HSD_JObj* jobj_2;
    Fighter* fighter;

    fighter = GET_FIGHTER(arg_effect->parent_gobj);
    jobj_1 = GET_JOBJ(arg_effect->gobj);
    jobj_2 = GET_JOBJ(arg_effect->x0->x4);
    if (fighter->motion_id == 359) {
        HSD_JObjClearFlagsAll(jobj_2, 0x10U);
    } else {
        HSD_JObjSetFlagsAll(jobj_2, 0x10U);
    }
    if ((fighter->cmd_vars[2] & 1) && ((s32) fighter->mv.co.common.x10 != 0)) {
        rotate_z = -atan2f(fighter->coll_data.floor.normal.x,
                           fighter->coll_data.floor.normal.y);
        HSD_JObjSetRotationZ(jobj_1, rotate_z);
        HSD_JObjSetRotationZ(jobj_2, rotate_z);
    } else {
        HSD_JObjSetRotationZ(jobj_1, 0.0f);
        HSD_JObjSetRotationZ(jobj_2, 0.0f);
    }
}

void efLib_8005F748(Effect* arg_effect)
{
    ftCo_800C0FCC(arg_effect->gobj, arg_effect->parent_gobj);
}

void efLib_8005F774(HSD_JObj* arg_jobj, s32 arg1, u32 arg2, u32 arg3)
{
    HSD_DObj* dobj_1;
    HSD_TObj* tobj_1;
    s32 ctr;
    s32 i;

    dobj_1 = HSD_JObjGetDObj(arg_jobj);
    if (dobj_1 != NULL) {
        tobj_1 = HSD_MObjGetTObj(dobj_1->mobj);
    } else {
        tobj_1 = HSD_MObjGetTObj(NULL);
    }

    i = arg1;
    if (arg1 != 0) {
        ctr = (u32) i >> 3;
        if (ctr != 0) {
            do {
                tobj_1 = tobj_1->next;
                tobj_1 = tobj_1->next;
                tobj_1 = tobj_1->next;
                tobj_1 = tobj_1->next;
                tobj_1 = tobj_1->next;
                tobj_1 = tobj_1->next;
                tobj_1 = tobj_1->next;
                tobj_1 = tobj_1->next;
            } while (--ctr != 0);
            i &= 7;
            if (i == 0) {
                goto done;
            }
        }
        do {
            tobj_1 = tobj_1->next;
        } while (--i != 0);
    }
done:
    tobj_1->tev->konst.r = arg2 >> 0x10U;
    tobj_1->tev->konst.g = arg2 >> 8U;
    tobj_1->tev->konst.b = arg2;
    tobj_1->tev->tev0.r = arg3 >> 0x10U;
    tobj_1->tev->tev0.g = arg3 >> 8U;
    tobj_1->tev->tev0.b = arg3;
}

void efLib_8005F864(HSD_GObj* gobj, s8 arg1, f32 arg2, f32 arg3)
{
    s32 var_r8;
    struct _struct_efLib_80458EE0_0x8* temp_r5;
    struct _struct_efLib_80458EE0_0x8* temp_r6;
    struct _struct_efLib_80458EE0_0x8* temp_r6_10;
    struct _struct_efLib_80458EE0_0x8* temp_r6_2;
    struct _struct_efLib_80458EE0_0x8* temp_r6_3;
    struct _struct_efLib_80458EE0_0x8* temp_r6_4;
    struct _struct_efLib_80458EE0_0x8* temp_r6_5;
    struct _struct_efLib_80458EE0_0x8* temp_r6_6;
    struct _struct_efLib_80458EE0_0x8* temp_r6_7;
    struct _struct_efLib_80458EE0_0x8* temp_r6_8;
    struct _struct_efLib_80458EE0_0x8* temp_r6_9;
    struct _struct_efLib_80458EE0_0x8* temp_r7;

    // temp_r7 = efLib_80458EE0 + 0x80;
    temp_r7 = &efLib_80458EE0[16];
    var_r8 = 0;
    // if ((efLib_80458EE0[15].unk0 == gobj) ||
    //     (temp_r6 = temp_r7, var_r8 = 1, (((u32) temp_r7[1].unk0 == gobj) !=
    //     0)) || (temp_r6_2 = temp_r6 + 8, var_r8 = 2, (((u32) temp_r6->unk8
    //     == gobj) != 0)) || (temp_r6_3 = temp_r6_2 + 8, var_r8 = 3, (((u32)
    //     temp_r6_2->unk8 == gobj) != 0)) || (temp_r6_4 = temp_r6_3 + 8,
    //     var_r8 = 4, (((u32) temp_r6_3->unk8 == gobj) != 0)) || (temp_r6_5 =
    //     temp_r6_4 + 8, var_r8 = 5, (((u32) temp_r6_4->unk8 == gobj) != 0))
    //     || (var_r8 = 6, (((u32) temp_r6_5->unk8 == gobj) != 0)) || (var_r8 =
    //     7, (((u32) (temp_r6_5 + 8)->unk8 == gobj) != 0)) || (var_r8 = 0,
    //     (((u32) temp_r7->unk0 == 0U) != 0))
    //     || (temp_r6_6 = &temp_r7[1], var_r8 = 1, (((u32) temp_r7[1].unk0 ==
    //     0U) != 0))
    //     || (temp_r6_7 = temp_r6_6 + 8, var_r8 = 2, (((u32) temp_r6_6->unk8
    //     == 0U) != 0))
    //     || (temp_r6_8 = temp_r6_7 + 8, var_r8 = 3, (((u32) temp_r6_7->unk8
    //     == 0U) != 0))
    //     || (temp_r6_9 = temp_r6_8 + 8, var_r8 = 4, (((u32) temp_r6_8->unk8
    //     == 0U) != 0))
    //     || (temp_r6_10 = temp_r6_9 + 8, var_r8 = 5, (((u32) temp_r6_9->unk8
    //     == 0U) != 0))
    //     || (var_r8 = 6, (((u32) temp_r6_10->unk8 == 0U) != 0))
    //     || (var_r8 = 7, (((u32) (temp_r6_10 + 8)->unk8 == 0U) != 0))) {
    if (efLib_80458EE0[15].unk0 == gobj) {
        // temp_r5 = &efLib_80458EE0[var_r8];
        temp_r5 = &efLib_80458EE0[0];
        // temp_r5->unk80 = gobj;
        temp_r5[16].unk0 = gobj;
        // temp_r5->unk86 = (s16) arg1;
        temp_r5[16].unk6 = (s16) arg1;
    }
}

void efLib_8005F990(HSD_GObj* gobj, s32 arg1)
{
    s32 var_r8;
    struct _struct_efLib_80458EE0_0x8* temp_r5;
    struct _struct_efLib_80458EE0_0x8* temp_r6;
    struct _struct_efLib_80458EE0_0x8* temp_r6_10;
    struct _struct_efLib_80458EE0_0x8* temp_r6_2;
    struct _struct_efLib_80458EE0_0x8* temp_r6_3;
    struct _struct_efLib_80458EE0_0x8* temp_r6_4;
    struct _struct_efLib_80458EE0_0x8* temp_r6_5;
    struct _struct_efLib_80458EE0_0x8* temp_r6_6;
    struct _struct_efLib_80458EE0_0x8* temp_r6_7;
    struct _struct_efLib_80458EE0_0x8* temp_r6_8;
    struct _struct_efLib_80458EE0_0x8* temp_r6_9;
    struct _struct_efLib_80458EE0_0x8* temp_r7;

    // temp_r7 = efLib_80458EE0 + 0x80;
    temp_r7 = &efLib_80458EE0[16];
    var_r8 = 0;
    // if (((u32) efLib_80458EE0->unk80 == gobj) ||
    // (temp_r6 = &temp_r7[1], var_r8 = 1, (((u32) temp_r7[1].unk0 == gobj) !=
    // 0)) || (temp_r6_2 = temp_r6 + 8, var_r8 = 2, (((u32) temp_r6->unk8 ==
    // gobj) != 0)) || (temp_r6_3 = temp_r6_2 + 8, var_r8 = 3, (((u32)
    // temp_r6_2->unk8 == gobj) != 0)) || (temp_r6_4 = temp_r6_3 + 8, var_r8 =
    // 4, (((u32) temp_r6_3->unk8 == gobj) != 0)) || (temp_r6_5 = temp_r6_4 +
    // 8, var_r8 = 5, (((u32) temp_r6_4->unk8 == gobj) != 0)) || (var_r8 = 6,
    // (((u32) temp_r6_5->unk8 == gobj) != 0)) || (var_r8 = 7, (((u32)
    // (temp_r6_5 + 8)->unk8 == gobj) != 0)) || (var_r8 = 0, (((u32)
    // temp_r7->unk0 == 0U) != 0)) || (temp_r6_6 = &temp_r7[1], var_r8 = 1,
    // (((u32) temp_r7[1].unk0 == 0U) != 0)) || (temp_r6_7 = temp_r6_6 + 8,
    // var_r8 = 2, (((u32) temp_r6_6->unk8 == 0U) != 0)) || (temp_r6_8 =
    // temp_r6_7 + 8, var_r8 = 3, (((u32) temp_r6_7->unk8 == 0U) != 0)) ||
    // (temp_r6_9 = temp_r6_8 + 8, var_r8 = 4, (((u32) temp_r6_8->unk8 == 0U)
    // != 0)) || (temp_r6_10 = temp_r6_9 + 8, var_r8 = 5, (((u32)
    // temp_r6_9->unk8 == 0U) != 0)) || (var_r8 = 6, (((u32) temp_r6_10->unk8
    // == 0U) != 0)) || (var_r8 = 7, (((u32) (temp_r6_10 + 8)->unk8 == 0U) !=
    // 0))) {
    if (efLib_80458EE0[15].unk0 == gobj) {
        // temp_r5 = &efLib_80458EE0[var_r8];
        temp_r5 = &efLib_80458EE0[0];
        // temp_r5->unk80 = gobj;
        temp_r5[16].unk0 = gobj;
        // temp_r5->unk86 = (s16) arg1;
        temp_r5[16].unk6 = (s16) arg1;
    }
}

void efLib_8005FAB8(Effect* arg_effect)
{
    HSD_DObj* dobj_1;
    HSD_DObj* temp_r3_3;
    HSD_JObj* jobj_2;
    HSD_MObj* mobj_1;
    HSD_MObj* var_r3_2;
    HSD_TObj* tobj_1;
    s32 var_ctr;
    s32 var_r29;
    s32 var_r6;
    struct _struct_efLib_80458EE0_0x8* temp_r4;
    struct _struct_efLib_80458EE0_0x8* temp_r5;
    struct _struct_efLib_80458EE0_0x8* var_r5;
    HSD_JObj* jobj_1;

    jobj_1 = GET_JOBJ(arg_effect->gobj);
    if (jobj_1 == NULL) {
        jobj_2 = NULL;
    } else {
        jobj_2 = jobj_1->child;
    }
    dobj_1 = HSD_JObjGetDObj(jobj_2);
    if (dobj_1 != NULL) {
        mobj_1 = dobj_1->mobj;
    } else {
        mobj_1 = NULL;
    }
    tobj_1 = HSD_MObjGetTObj(mobj_1);
    var_ctr = 8;
    var_r5 = &efLib_80458EE0[16];
    var_r6 = 0;
loop_7:
    if ((u32) var_r5->unk0 == (u32) arg_effect->parent_gobj) {
        temp_r5 = &efLib_80458EE0[var_r6];
        // if ((u16) temp_r5->unk84 == 0x417) {
        if (efLib_80458EE0[15].pad4 == 0x417) {
            tobj_1 = tobj_1->next;
        }
        temp_r4 = &efLib_80458EE0[var_r6];
        // tobj_1->tev->konst.a = (u8) temp_r4->unk86;
        tobj_1->tev->konst.a = efLib_80458EE0[15].unk6;
        // if ((u16) *(temp_r5 + 0x84) == 0x419) {
        if (efLib_80458EE0[15].pad4 == 0x419) {
            var_r29 = 0;
            do {
                jobj_2 = jobj_2->next;
                temp_r3_3 = HSD_JObjGetDObj(jobj_2);
                if (temp_r3_3 != NULL) {
                    var_r3_2 = temp_r3_3->mobj;
                } else {
                    var_r3_2 = NULL;
                }
                var_r29 += 1;
                // HSD_MObjGetTObj(var_r3_2)->tev->konst.a = (u8) (temp_r4 +
                // 0x80)->unk6;
                HSD_MObjGetTObj(var_r3_2)->tev->konst.a =
                    efLib_80458EE0[15].unk6;
            } while (var_r29 < 6);
        }
    } else {
        var_r5 += 8;
        var_r6 += 1;
        var_ctr -= 1;
        if (var_ctr == 0) {
            return;
        }
        goto loop_7;
    }
}

void fn_8005FBE4(Effect* arg_effect)
{
    HSD_JObj* jobj_1;
    Vec3 sp14;

    lb_8000B1CC(arg_effect->xC, NULL, &sp14);
    sp14.x += arg_effect->translate.x;
    sp14.y += arg_effect->translate.y;
    sp14.z += arg_effect->translate.z;
    jobj_1 = GET_JOBJ(arg_effect->gobj);
    HSD_JObjSetTranslate(jobj_1, &sp14);
}

Effect* efLib_8005FCD8(int arg0, HSD_GObj* gobj, HSD_JObj* jobj, Vec3* vec)
{
    Effect* ep = efLib_8005BE88(0, gobj);
    if (ep != NULL) {
        ep->x10 = fn_8005FBE4;
        ep->xC = jobj;
        ep->translate = *vec;
        efLib_8005C_inline(arg0, GET_JOBJ(ep->gobj));
    }
    return ep;
}
