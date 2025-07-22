#include <placeholder.h>

#include "baselib/forward.h"
#include "ef/forward.h"
#include "ft/forward.h"

#include "eflib.h"

#include "efasync.h"
#include "inlines.h"
#include "types.h"

#include "baselib/displayfunc.h"
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
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Bury.h"
#include "gr/grlib.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

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

static struct _struct_efLib_80458EE0_0x8 efLib_80458EE0[16];
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

// void efLib_8005B704(u32 arg0, s32 arg1) {
void efLib_8005B704(HSD_GObj* arg_gobj, s32 arg1)
{
    HSD_GObj* gobj_1;
    HSD_GObj* gobj_2;
    // Not sure if these types are correct
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
    // Not sure about types
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
    // Not sure if these types are correct
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
    // Not sure if these types are correct
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
    HSD_GObj* gobj_3;
    HSD_GObj* gobj_4;
    HSD_GObj* gobj_1;
    HSD_GObj* gobj_2;
    f32 var_f1;
    u32 var_r4;
    // void* temp_ret;
    // void* temp_ret_2;

    var_r4 = arg1;
    var_f1 = arg8;
    gobj_1 = HSD_GObj_Entities->x2C;
#if 1
    while (gobj_1 != NULL) {
        gobj_4 = gobj_1->next;
        // temp_ret_2 = efLib_8005B780();
        efLib_8005B780(gobj_1);
        // var_f1 = (bitwise f32) temp_ret_2;
        // var_r4 = (u32) (u64) temp_ret_2;
        if (efLib_804D64EC >= 0x40U) {
            gobj_1 = gobj_4;
        }
    }
    gobj_2 = HSD_GObj_Entities->x30;
    while (gobj_2 != NULL) {
        //     OSReport("can't remove no force effect!\n\0\0error no parent
        //     gobj!\n\0\0Over Anime Call\n", var_r4, var_f1);
        //     __assert("eflib.c", 0x4DU, "0");
        // } else {
        gobj_3 = gobj_2->next;
        // temp_ret = efLib_8005B780(gobj_2); // which gobj?
        efLib_8005B780(gobj_2);
        // var_f1 = (bitwise f32) temp_ret;
        // var_r4 = (u32) (u64) temp_ret;
        if (efLib_804D64EC >= 0x40U) {
            gobj_2 = gobj_3;
        }
    }
    // if (gobj_2 != NULL) {
    OSReport("can't remove no force effect!\n\0\0error no parent "
             "gobj!\n\0\0Over Anime Call\n",
             var_r4, var_f1);
    __assert("eflib.c", 0x4DU, "0");
    // }

#else
loop_3:
    if (gobj_1 == NULL) {
        gobj_2 = HSD_GObj_Entities->x30;
    loop_7:
        if (gobj_2 == NULL) {
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
    Point3d sp1C; /* compiler-managed */
    efLib_UnkCallback temp_r12;
    HSD_JObj* temp_r29;
    HSD_JObj* temp_r29_2;
    HSD_JObj* var_r0;
    s32 temp_cr0_eq;
    s32 temp_cr0_eq_2;
    s32 temp_cr0_eq_3;
    s32 temp_r4_5;
    s32 var_r3;
    s32 var_r3_2;
    u16 temp_r4_2;
    u16 temp_r4_3;
    u32 temp_r4_4;
    u8 temp_r3;
    u8 bit_chk;
    HSD_JObj* jobj_1;
    Effect* effect;

    effect = GET_EFFECT(gobj);
    jobj_1 = gobj->hsd_obj;
    bit_chk = effect->x28;
    switch ((s32) bit_chk) { /* irregular */
    case 1:
        // effect->x28 = (u8) (bit_chk + 1);
        effect->x28++;
        /* fallthrough */
    default:
        temp_r4_2 = effect->x24;
        if (temp_r4_2 != 0) {
            temp_r4_3 = temp_r4_2 - 1;
            effect->x24 = temp_r4_3;
            if (temp_r4_3 == 0) {
                HSD_GObjPLink_80390228(gobj);
                return;
            }
        }
        temp_r3 = effect->x27;
        if (temp_r3 != 0) {
            temp_r29 = effect->xC;
            temp_cr0_eq = temp_r29 == NULL;
            if (temp_cr0_eq == 0) {
                if (temp_cr0_eq != 0) {
                    var_r0 = 0U;
                } else {
                    var_r0 = temp_r29->parent;
                }
                if (var_r0 != NULL) {
                    temp_cr0_eq_2 = temp_r29 == NULL;
                    if (temp_cr0_eq_2 == 0) {
                        if (temp_cr0_eq_2 != 0) {
                            __assert("jobj.h", 0x234U, "jobj");
                        }
                        temp_r4_4 = temp_r29->flags;
                        var_r3 = 0;
                        if (!(temp_r4_4 & 0x800000) && (temp_r4_4 & 0x40)) {
                            var_r3 = 1;
                        }
                        if (var_r3 != 0) {
                            HSD_JObjSetupMatrixSub(temp_r29);
                        }
                    }
                    if (effect->x27 & 1) {
                        temp_r29_2 = effect->xC;
                        if (temp_r29_2 == NULL) {
                            __assert("jobj.h", 0x478U, "jobj");
                        }
                        HSD_JObjSetupMatrix(temp_r29_2);
                        HSD_MtxGetScale((f32(*)[4]) temp_r29_2->mtx[0], &sp1C);
                    }
                } else if (temp_r3 & 1) {
                    if (temp_r29 == NULL) {
                        __assert("jobj.h", 0x337U, "jobj");
                    }
                    sp1C.x = temp_r29->scale.x;
                    sp1C.y = temp_r29->scale.y;
                    sp1C.z = temp_r29->scale.z;
                }
                if (effect->x27 & 1) {
                    sp1C.z = sp1C.y;
                    sp1C.x = sp1C.y;
                    if (jobj_1 == NULL) {
                        __assert("jobj.h", 0x2F8U, "jobj");
                    }
                    jobj_1->scale = sp1C;
                    if (!(jobj_1->flags & 0x02000000)) {
                        temp_cr0_eq_3 = jobj_1 == NULL;
                        if (temp_cr0_eq_3 == 0) {
                            if (temp_cr0_eq_3 != 0) {
                                __assert("jobj.h", 0x234U, "jobj");
                            }
                            temp_r4_5 = jobj_1->flags;
                            var_r3_2 = 0;
                            if (!(temp_r4_5 & 0x800000) && (temp_r4_5 & 0x40))
                            {
                                var_r3_2 = 1;
                            }
                            if (var_r3_2 == 0) {
                                HSD_JObjSetMtxDirtySub((HSD_JObj*) jobj_1);
                            }
                        }
                    }
                }
            }
        }
        HSD_JObjAnimAll((HSD_JObj*) jobj_1);
        temp_r12 = effect->x10;
        if (temp_r12 != NULL) {
            temp_r12(effect);
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
        if (((10.0f * M2C_FIELD(desc, f32*, 0)) / /* % */ 10) != 0) {
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
    HSD_GObj* gobj_1;
    HSD_JObj* jobj_1;

    eff_1 = efLib_8005BE88(arg0, arg_gobj);
    if (eff_1 != NULL) {
        gobj_1 = eff_1->gobj;
        jobj_1 = GET_JOBJ(gobj_1);
        if (jobj_1 == NULL) {
            HSD_GObjPLink_80390228(gobj_1);
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
    HSD_GObj* gobj_1;
    HSD_JObj* jobj_1;
    PAD_STACK(0x4);

    eff_1 = efLib_8005BE88(arg0, arg_gobj);
    if (eff_1 != NULL) {
        gobj_1 = eff_1->gobj;
        jobj_1 = GET_JOBJ(gobj_1);
        if (jobj_1 == NULL) {
            HSD_GObjPLink_80390228(gobj_1);
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
// #pragma dont_inline reset

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

Effect* efLib_8005C814(u32 arg0, HSD_GObj* arg_gobj, Vec3* arg_vec3)
{
    Effect* eff_1;
    HSD_JObj* jobj_1;

    eff_1 = efLib_8005BE88(arg0, arg_gobj);
    if (eff_1 != NULL) {
        jobj_1 = GET_JOBJ(eff_1->gobj);
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

HSD_Generator* efLib_8005C9FC(u32 arg0, Vec3* arg1)
{
    HSD_Generator* temp_r3;
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
    temp_r3 = hsd_8039F05C(var_r3, ((arg0 / 1000) + (u32) var_r3), arg0);
    if (temp_r3 != NULL) {
        temp_r3->pos.x = arg1->x;
        temp_r3->pos.y = arg1->y;
        temp_r3->pos.z = arg1->z;
    }
    return temp_r3;
}

HSD_Generator* efLib_8005CAB0(u32 arg0)
{
    HSD_psAppSRT* var_r3;
    HSD_Generator* temp_r3;

    temp_r3 = hsd_8039F05C(0, (s8) (arg0 / 1000), (s32) arg0);
    if (temp_r3 != NULL) {
        var_r3 = temp_r3->appsrt;
        if (var_r3 == NULL) {
            var_r3 = psAddGeneratorAppSRT_begin(temp_r3, 1);
        }
        if (var_r3 == NULL) {
            hsd_8039D4DC(temp_r3);
            return NULL;
        }
    }
    return temp_r3;
}

HSD_Generator* efLib_8005CB34(u32 arg0, Vec3* arg_vec3, f32 arg2)
{
    HSD_psAppSRT* var_r3;
    HSD_Generator* var_r31;

    var_r31 = hsd_8039F05C(0, (s8) (arg0 / 1000), (s32) arg0);
    if (var_r31 != NULL) {
        var_r3 = var_r31->appsrt;
        if (var_r3 == NULL) {
            var_r3 = psAddGeneratorAppSRT_begin(var_r31, 1);
        }
        if (var_r3 == NULL) {
            hsd_8039D4DC(var_r31);
            var_r31 = NULL;
        }
    }
    if (var_r31 != NULL) {
        var_r31->appsrt->transform.x = arg_vec3->x;
        var_r31->appsrt->transform.y = arg_vec3->y;
        var_r31->appsrt->transform.z = arg_vec3->z;
        if (arg2 < 0.0f) {
            var_r31->kind |= 0x40000;
            var_r31->appsrt->rot.y = -M_PI_2;
        } else {
            var_r31->appsrt->rot.y = M_PI_2;
        }
    }
    return var_r31;
}

HSD_Generator* efLib_8005CC2C(int arg0, HSD_JObj* arg1)
{
    HSD_Generator* generator = hsd_8039EFAC(0, arg0 / 1000, arg0, arg1);
    if (generator != NULL) {
        generator->type &= ~PSAPPSRT_UNK_B10;
    }
    return generator;
}

HSD_Generator* efLib_8005CC84(u32 arg0, HSD_JObj* arg1)
{
    HSD_psAppSRT* var_r3;
    HSD_Generator* temp_r3;

    temp_r3 = hsd_8039EFAC(0, (s32) (arg0 / 1000), (s32) arg0, arg1);
    if (temp_r3 != NULL) {
        var_r3 = temp_r3->appsrt;
        if (var_r3 == NULL) {
            var_r3 = psAddGeneratorAppSRT_begin(temp_r3, 0);
        }
        if (var_r3 != NULL) {
            var_r3->gp = temp_r3;
            temp_r3->type &= 0xFFFFF9FF;
            temp_r3->type |= 0x800;
            goto block_7;
        }
        hsd_8039D4DC(temp_r3);
        return NULL;
    }
block_7:
    return temp_r3;
}

HSD_Generator* efLib_8005CD2C(u32 arg0, void* arg1, HSD_GObj* arg_gobj)
{
    Vec3 sp18;
    HSD_psAppSRT* var_r3;
    HSD_Generator* var_r30;
    HSD_JObj* jobj_1;

    var_r30 = hsd_8039EFAC(0, (s32) (arg0 / 1000), (s32) arg0,
                           va_arg(arg1, HSD_JObj*));
    if (var_r30 != NULL) {
        var_r3 = var_r30->appsrt;
        if (var_r3 == NULL) {
            var_r3 = psAddGeneratorAppSRT_begin(var_r30, 0);
        }
        if (var_r3 != NULL) {
            var_r3->gp = var_r30;
            var_r30->type &= 0xFFFFF9FF;
            var_r30->type |= 0x800;
        } else {
            hsd_8039D4DC(var_r30);
            var_r30 = NULL;
        }
    }
    if (var_r30 != NULL) {
        jobj_1 = GET_JOBJ(arg_gobj);
        HSD_JObjGetScale(jobj_1, &sp18);
        var_r30->appsrt->scale.x = var_r30->appsrt->scale.y =
            var_r30->appsrt->scale.z = sp18.y;
    }
    return var_r30;
}

HSD_Generator* efLib_8005CE48(u32 arg0, void* arg1)
{
    HSD_psAppSRT* var_r3;
    HSD_Generator* var_r31;
    f32 temp_f0;

    var_r31 = hsd_8039EFAC(0, (s32) (arg0 / 1000), (s32) arg0,
                           va_arg(arg1, HSD_JObj*));
    if (var_r31 != NULL) {
        var_r3 = var_r31->appsrt;
        if (var_r3 == NULL) {
            var_r3 = psAddGeneratorAppSRT_begin(var_r31, 0);
        }
        if (var_r3 != NULL) {
            var_r3->gp = var_r31;
            var_r31->type &= 0xFFFFF9FF;
            var_r31->type |= 0x800;
        } else {
            hsd_8039D4DC(var_r31);
            var_r31 = NULL;
        }
    }
    if (var_r31 != NULL) {
        temp_f0 = va_arg(arg1, f32);
        var_r31->appsrt->scale.x = var_r31->appsrt->scale.y =
            var_r31->appsrt->scale.z = temp_f0;
    }
    return var_r31;
}

HSD_Generator* efLib_8005CF40(u32 arg0, void* arg1)
{
    HSD_psAppSRT* var_r3;
    HSD_Generator* var_r31;
    f64 var_f0;

    var_r31 = hsd_8039EFAC(0, (s32) (arg0 / 1000), (s32) arg0,
                           va_arg(arg1, HSD_JObj*));
    if (var_r31 != NULL) {
        var_r3 = var_r31->appsrt;
        if (var_r3 == NULL) {
            var_r3 = psAddGeneratorAppSRT_begin(var_r31, 0);
        }
        if (var_r3 != NULL) {
            var_r3->gp = var_r31;
            var_r31->type &= 0xFFFFF9FF;
            var_r31->type |= 0x800;
        } else {
            hsd_8039D4DC(var_r31);
            var_r31 = NULL;
        }
    }
    if (var_r31 != NULL) {
        if (*va_arg(arg1, f32*) < 0.0f) {
            var_f0 = -M_PI_2;
        } else {
            var_f0 = M_PI_2;
        }
        var_r31->appsrt->rot.y = (f32) var_f0;
    }
    return var_r31;
}

HSD_Generator* efLib_8005D044(u32 arg0, void* arg1)
{
    HSD_psAppSRT* var_r3;
    HSD_Generator* var_r30;
    f32 temp_f0;
    f64 var_f0;

    var_r30 = hsd_8039EFAC(0, (s32) (arg0 / 1000), (s32) arg0,
                           va_arg(arg1, HSD_JObj*));
    if (var_r30 != NULL) {
        var_r3 = var_r30->appsrt;
        if (var_r3 == NULL) {
            var_r3 = psAddGeneratorAppSRT_begin(var_r30, 0);
        }
        if (var_r3 != NULL) {
            var_r3->gp = var_r30;
            var_r30->type &= 0xFFFFF9FF;
            var_r30->type |= 0x800;
        } else {
            hsd_8039D4DC(var_r30);
            var_r30 = NULL;
        }
    }
    if (var_r30 != NULL) {
        if (va_arg(arg1, f32) < 0.0f) {
            var_f0 = -M_PI_2;
        } else {
            var_f0 = M_PI_2;
        }
        var_r30->appsrt->rot.y = var_f0;
        temp_f0 = va_arg(arg1, f32);
        var_r30->appsrt->scale.x = var_r30->appsrt->scale.y =
            var_r30->appsrt->scale.z = temp_f0;
    }
    return var_r30;
}

void efLib_8005D174(s8 arg0, s32 arg1, HSD_JObj* arg2, s32 arg3)
{
    HSD_JObj* var_r0;
    HSD_JObj* var_r0_10;
    HSD_JObj* var_r0_11;
    HSD_JObj* var_r0_12;
    HSD_JObj* var_r0_13;
    HSD_JObj* var_r0_14;
    HSD_JObj* var_r0_2;
    HSD_JObj* var_r0_3;
    HSD_JObj* var_r0_4;
    HSD_JObj* var_r0_5;
    HSD_JObj* var_r0_6;
    HSD_JObj* var_r0_7;
    HSD_JObj* var_r0_8;
    HSD_JObj* var_r0_9;
    HSD_JObj* var_r31;
    Point3d* temp_r29_2;
    HSD_psAppSRT* var_r28;
    HSD_psAppSRT* var_r28_2;
    HSD_psAppSRT* var_r3_2;
    HSD_psAppSRT* var_r3_3;
    HSD_psAppSRT* var_r3_4;
    HSD_psAppSRT* var_r3_5;
    HSD_psAppSRT* var_r3_6;
    HSD_psAppSRT* var_r3_7;
    HSD_Generator* temp_r3;
    HSD_Generator* temp_r3_2;
    HSD_Generator* var_r29;
    HSD_Generator* var_r29_2;
    HSD_Generator* var_r29_3;
    HSD_Generator* var_r29_4;
    HSD_Generator* var_r29_5;
    HSD_Generator* var_r29_6;
    Vec3* vec3_1;
    s32 var_r3;
    char* temp_r5;

    var_r3 = 0;
    var_r31 = arg2;
    temp_r5 = "Duplicate Free %08X\n";
    if (arg1 != 0xFC) {
        if (arg1 < 0xFC) {
            switch (arg1) { /* switch 2; irregular */
            default:        /* switch 2 */
                var_r29 = hsd_8039EFAC(0, (s32) (arg1 / 1000), arg1, var_r31);
                if (var_r29 != NULL) {
                    var_r3_2 = var_r29->appsrt;
                    if (var_r3_2 == NULL) {
                        var_r3_2 = psAddGeneratorAppSRT_begin(var_r29, 0);
                    }
                    if (var_r3_2 != NULL) {
                        var_r3_2->gp = var_r29;
                        var_r29->type &= 0xFFFFF9FF;
                        var_r29->type |= 0x800;
                    } else {
                        hsd_8039D4DC(var_r29);
                        var_r29 = NULL;
                    }
                }
                if (var_r29 != NULL) {
                    var_r29->type |= 0x1000;
                    return;
                }
                break;
            case 0xD4: /* switch 2 */
                temp_r3 = hsd_8039F05C(2, arg0, arg1);
                if (temp_r3 != NULL) {
                    var_r28 = temp_r3->appsrt;
                    if (var_r28 == NULL) {
                        var_r28 = psAddGeneratorAppSRT_begin(temp_r3, 1);
                    }
                    if (var_r28 != NULL) {
                    loop_155:
                        if (var_r31 == NULL) {
                            var_r0 = NULL;
                        } else {
                            var_r0 = var_r31->parent;
                        }
                        if (var_r0 != NULL) {
                            if (var_r31 == NULL) {
                                var_r0_2 = NULL;
                            } else {
                                var_r0_2 = var_r31->parent;
                            }
                            var_r31 = var_r0_2;
                            goto loop_155;
                        }
                        if (var_r31 == NULL) {
                            __assert("jobj.h", 0x2E9U, "jobj");
                        }
                        var_r28->rot.z = var_r31->rotate.z;
                        if (var_r31 == NULL) {
                            __assert("jobj.h", 0x3D3U, "jobj");
                        }
                        if (var_r28->transform.x == NULL) {
                            __assert("jobj.h", 0x3D4U, temp_r5 + 0x64);
                        }
                        var_r28->transform.x = var_r31->translate.x;
                        var_r28->transform.y = var_r31->translate.y;
                        var_r28->transform.z = var_r31->translate.z;
                        if (var_r31 == NULL) {
                            __assert("jobj.h", 0x337U, "jobj");
                        }
                        if ((Vec3*) &var_r28->scale == NULL) {
                            __assert("jobj.h", 0x338U, "scale");
                        }
                        var_r28->scale.x = var_r31->scale.x;
                        var_r28->scale.y = var_r31->scale.y;
                        var_r28->scale.z = var_r31->scale.z;
                        return;
                    }
                    hsd_8039D4DC(temp_r3);
                    return;
                }
                break;
            case 0xE3: /* switch 2 */
                var_r29_2 = hsd_8039F05C(0, (s8) (arg1 / 1000), arg1);
                if (var_r29_2 != NULL) {
                    var_r3_3 = var_r29_2->appsrt;
                    if (var_r3_3 == NULL) {
                        var_r3_3 = psAddGeneratorAppSRT_begin(var_r29_2, 1);
                    }
                    if (var_r3_3 == NULL) {
                        hsd_8039D4DC(var_r29_2);
                        var_r29_2 = NULL;
                    }
                }
                if (var_r29_2 != NULL) {
                    lb_8000B1CC(var_r31, NULL, &var_r29_2->appsrt->transform);
                loop_203:
                    if (var_r31 == NULL) {
                        var_r0_3 = NULL;
                    } else {
                        var_r0_3 = var_r31->parent;
                    }
                    if (var_r0_3 != NULL) {
                        if (var_r31 == NULL) {
                            var_r0_4 = NULL;
                        } else {
                            var_r0_4 = var_r31->parent;
                        }
                        var_r31 = var_r0_4;
                        goto loop_203;
                    }
                    vec3_1 = &var_r29_2->appsrt->scale;
                    if (var_r31 == NULL) {
                        __assert("jobj.h", 0x337U, "jobj");
                    }
                    if (vec3_1 == NULL) {
                        __assert("jobj.h", 0x338U, "scale");
                    }
                    vec3_1->x = var_r31->scale.x;
                    vec3_1->y = (f32) var_r31->scale.y;
                    vec3_1->z = (f32) var_r31->scale.z;
                    return;
                }
                break;
            }
        } else if (arg1 != 0x243) {
            if (arg1 < 0x243) {
                switch (arg1) { /* switch 1; irregular */
                case 0x127:     /* switch 1 */
                    var_r29_3 =
                        hsd_8039EFAC(0, (s32) (arg1 / 1000), arg1, var_r31);
                    if (var_r29_3 != NULL) {
                        var_r3_4 = var_r29_3->appsrt;
                        if (var_r3_4 == NULL) {
                            var_r3_4 =
                                psAddGeneratorAppSRT_begin(var_r29_3, 0);
                        }
                        if (var_r3_4 != NULL) {
                            var_r3_4->gp = var_r29_3;
                            var_r29_3->type &= 0xFFFFF9FF;
                            var_r29_3->type |= 0x800;
                        } else {
                            hsd_8039D4DC(var_r29_3);
                            var_r29_3 = NULL;
                        }
                    }
                    if (var_r29_3 != NULL) {
                    loop_91:
                        if (var_r31 == NULL) {
                            var_r0_5 = NULL;
                        } else {
                            var_r0_5 = var_r31->parent;
                        }
                        if (var_r0_5 != NULL) {
                            if (var_r31 == NULL) {
                                var_r0_6 = NULL;
                            } else {
                                var_r0_6 = var_r31->parent;
                            }
                            var_r31 = var_r0_6;
                            goto loop_91;
                        }
                        if (var_r31 == NULL) {
                            __assert("jobj.h", 0x2DAU, "jobj");
                        }
                        var_r29_3->appsrt->rot.y = var_r31->rotate.y;
                        vec3_1 = &var_r29_3->appsrt->scale;
                        if (var_r31 == NULL) {
                            __assert("jobj.h", 0x337U, "jobj");
                        }
                        if (vec3_1 == NULL) {
                            __assert("jobj.h", 0x338U, "scale");
                        }
                        vec3_1->x = var_r31->scale.x;
                        vec3_1->y = (f32) var_r31->scale.y;
                        vec3_1->z = (f32) var_r31->scale.z;
                        return;
                    }
                    break;
                case 0x12A: /* switch 1 */
                case 0xA7:  /* switch 2 */
                case 0xF2:  /* switch 2 */
                case 0xAA:  /* switch 2 */
                case 0xA3:  /* switch 2 */
                case 0x6:   /* switch 2 */
                case 0x2:   /* switch 2 */
                    var_r29_4 =
                        hsd_8039EFAC(0, (s32) (arg1 / 1000), arg1, var_r31);
                    if (var_r29_4 != NULL) {
                        var_r3_5 = var_r29_4->appsrt;
                        if (var_r3_5 == NULL) {
                            var_r3_5 =
                                psAddGeneratorAppSRT_begin(var_r29_4, 0);
                        }
                        if (var_r3_5 != NULL) {
                            var_r3_5->gp = var_r29_4;
                            var_r29_4->type &= 0xFFFFF9FF;
                            var_r29_4->type |= 0x800;
                        } else {
                            hsd_8039D4DC(var_r29_4);
                            var_r29_4 = NULL;
                        }
                    }
                    if (var_r29_4 != NULL) {
                    loop_115:
                        if (var_r31 == NULL) {
                            var_r0_7 = NULL;
                        } else {
                            var_r0_7 = var_r31->parent;
                        }
                        if (var_r0_7 != NULL) {
                            if (var_r31 == NULL) {
                                var_r0_8 = NULL;
                            } else {
                                var_r0_8 = var_r31->parent;
                            }
                            var_r31 = var_r0_8;
                            goto loop_115;
                        }
                        vec3_1 = &var_r29_4->appsrt->scale;
                        if (var_r31 == NULL) {
                            __assert("jobj.h", 0x337U, "jobj");
                        }
                        if (vec3_1 == NULL) {
                            __assert("jobj.h", 0x338U, "scale");
                        }
                        vec3_1->x = var_r31->scale.x;
                        vec3_1->y = (f32) var_r31->scale.y;
                        vec3_1->z = (f32) var_r31->scale.z;
                        return;
                    }
                    break;
                }
            } else {
                switch (arg1) { /* irregular */
                default:
                    var_r29_5 =
                        hsd_8039EFAC(0, (s32) (arg1 / 1000), arg1, var_r31);
                    if (var_r29_5 != NULL) {
                        var_r3_6 = var_r29_5->appsrt;
                        if (var_r3_6 == NULL) {
                            var_r3_6 =
                                psAddGeneratorAppSRT_begin(var_r29_5, 0);
                        }
                        if (var_r3_6 != NULL) {
                            var_r3_6->gp = var_r29_5;
                            var_r29_5->type &= 0xFFFFF9FF;
                            var_r29_5->type |= 0x800;
                        } else {
                            hsd_8039D4DC(var_r29_5);
                            var_r29_5 = NULL;
                        }
                    }
                    if (var_r29_5 != NULL) {
                    loop_62:
                        if (var_r31 == NULL) {
                            var_r0_9 = NULL;
                        } else {
                            var_r0_9 = var_r31->parent;
                        }
                        if (var_r0_9 != NULL) {
                            if (var_r31 == NULL) {
                                var_r0_10 = NULL;
                            } else {
                                var_r0_10 = var_r31->parent;
                            }
                            var_r31 = var_r0_10;
                            goto loop_62;
                        }
                        if (var_r31 == NULL) {
                            __assert("jobj.h", 0x2DAU, "jobj");
                        }
                        var_r29_5->appsrt->rot.y = var_r31->rotate.y;
                        return;
                    }
                    break;
                case 0x7E2:
                    var_r29_6 = hsd_8039F05C(0, (s8) (arg1 / 1000), arg1);
                    if (var_r29_6 != NULL) {
                        var_r3_7 = var_r29_6->appsrt;
                        if (var_r3_7 == NULL) {
                            var_r3_7 =
                                psAddGeneratorAppSRT_begin(var_r29_6, 1);
                        }
                        if (var_r3_7 == NULL) {
                            hsd_8039D4DC(var_r29_6);
                            var_r29_6 = NULL;
                        }
                    }
                    if (var_r29_6 != NULL) {
                    loop_135:
                        if (var_r31 == NULL) {
                            var_r0_11 = NULL;
                        } else {
                            var_r0_11 = var_r31->parent;
                        }
                        if (var_r0_11 != NULL) {
                            if (var_r31 == NULL) {
                                var_r0_12 = NULL;
                            } else {
                                var_r0_12 = var_r31->parent;
                            }
                            var_r31 = var_r0_12;
                            goto loop_135;
                        }
                        if (var_r31 == NULL) {
                            __assert("jobj.h", 0x2DAU, "jobj");
                        }
                        var_r29_6->appsrt->rot.y = var_r31->rotate.y;
                        vec3_1 = &var_r29_6->appsrt->transform;
                        if (var_r31 == NULL) {
                            __assert("jobj.h", 0x3D3U, "jobj");
                        }
                        if (vec3_1 == NULL) {
                            __assert("jobj.h", 0x3D4U, temp_r5 + 0x64);
                        }
                        vec3_1->x = var_r31->translate.x;
                        vec3_1->y = var_r31->translate.y;
                        vec3_1->z = var_r31->translate.z;
                        return;
                    }
                    break;
                }
            }
        } else {
            temp_r3_2 = hsd_8039F05C(2, arg0, arg1);
            if (temp_r3_2 != NULL) {
                var_r28_2 = temp_r3_2->appsrt;
                if (var_r28_2 == NULL) {
                    var_r28_2 = psAddGeneratorAppSRT_begin(temp_r3_2, 1);
                }
                if (var_r28_2 != NULL) {
                loop_180:
                    if (var_r31 == NULL) {
                        var_r0_13 = NULL;
                    } else {
                        var_r0_13 = var_r31->parent;
                    }
                    if (var_r0_13 != NULL) {
                        if (var_r31 == NULL) {
                            var_r0_14 = NULL;
                        } else {
                            var_r0_14 = var_r31->parent;
                        }
                        var_r31 = var_r0_14;
                        goto loop_180;
                    }
                    if (var_r31 == NULL) {
                        __assert("jobj.h", 0x2E9U, "jobj");
                    }
                    var_r28_2->rot.z = var_r31->rotate.z;
                    if (var_r31 == NULL) {
                        __assert("jobj.h", 0x3D3U, "jobj");
                    }
                    if ((Vec3*) &var_r28_2->transform == NULL) {
                        __assert("jobj.h", 0x3D4U, temp_r5 + 0x64);
                    }
                    var_r28_2->transform.x = var_r31->translate.x;
                    var_r28_2->transform.y = var_r31->translate.y;
                    var_r28_2->transform.z = var_r31->translate.z;
                    return;
                }
                hsd_8039D4DC(temp_r3_2);
            }
        }
    } else {
        // case 0x7918:
        // case 0xFF:                                      /* switch 1 */
        // case 0xF7:                                      /* switch 2 */
        var_r3 = 1;
        if (arg3 != 0) {
            hsd_8039EFAC(var_r3, (s32) arg0, arg1, var_r31);
            return;
        }
        hsd_8039F6CC(var_r3, (s32) arg0, arg1, var_r31);
    }
}

void fn_8005DB20(s32 arg0, s32 arg1, s32 arg2, HSD_JObj* arg3)
{
    if (arg1 == 0x1E) {
        grLib_801C99C0(arg1, arg2, arg3, 0);
        return;
    }
    efLib_8005D174(arg1, arg2, arg3, 0);
}

// void fn_8005DB70(s32 arg0, s32 lo, s32 hi, HSD_JObj* jobj) {
void fn_8005DB70(int arg0, int lo, int hi, HSD_JObj* jobj)
{
    if (lo == 0x1E) {
        grLib_801C99C0(lo, hi, jobj, 1);
        return;
    }
    efLib_8005D174(lo, hi, jobj, 1);
}

void efLib_8005DBC0(HSD_Particle* particle)
{ // Particle?
    Vec3 sp28;
    Vec3 sp1C;
    s32 sp18;
    Vec3 spC;
    HSD_psAppSRT* temp_r5;

    if ((particle != NULL) &&
        (temp_r5 = particle->appsrt, ((temp_r5 == NULL) == 0)))
    {
        sp28 = temp_r5->transform;
        sp1C = temp_r5->scale;
        // spC = temp_r5->rot;
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
    sp14.y += effect->transform.y;
    HSD_JObjSetTranslate(eff_jobj, &sp14);
}

void efLib_8005DE94(Effect* effect)
{
    HSD_JObj* eff_jobj;
    f32 scale_x;
    f32 scale_y;
    f32 scale_z;

    eff_jobj = GET_JOBJ(effect->gobj);
    scale_x = effect->transform.x * HSD_JObjGetScaleX(eff_jobj);
    HSD_JObjSetScaleX(eff_jobj, scale_x);

    scale_y = effect->transform.x * HSD_JObjGetScaleY(eff_jobj);
    HSD_JObjSetScaleY(eff_jobj, scale_y);

    scale_z = effect->transform.x * HSD_JObjGetScaleZ(eff_jobj);
    HSD_JObjSetScaleZ(eff_jobj, scale_z);
}

void efLib_8005E090(Effect* effect)
{
    HSD_JObj* eff_jobj;
    f32 rotate_y;
    void* temp_r4;

    temp_r4 = effect->x14;
    eff_jobj = GET_JOBJ(effect->gobj);
    if (temp_r4 != NULL) {
        if (((HSD_JObj*) temp_r4)->scale.x < 0.0f) {
            rotate_y = -M_PI_2; // needs to load as a double/f64?
        } else {
            rotate_y = M_PI_2; // needs to load as a double/f64?
        }
        HSD_JObjSetRotationY(eff_jobj, rotate_y);
    }
    if ((u8) effect->x26 != 0) {
        effect->x24 = 0xBU;
        effect->x10 = NULL;
        HSD_JObjReqAnimAll(eff_jobj, 65.0f);
        return;
    }
    if ((u16) effect->x24 == 1) {
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
    if (((Fighter*) effect->parent_gobj->user_data)->facing_dir < 0.0f) {
        // if (GET_FIGHTER(effect->parent_gobj->user_data)->facing_dir < 0.0f)
        // {
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
    arg_effect->transform.y -= 0.2f;
    f32_1 = translate_x + sinf(rotate_y);
    HSD_JObjSetTranslateX(jobj_1, f32_1);
    f32_2 = translate_y + arg_effect->transform.y;
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
    arg_effect->transform.y -= 0.1f;
    f32_1 = translate_x + arg_effect->transform.x;
    HSD_JObjSetTranslateX(jobj_1, f32_1);
    f32_2 = translate_y + arg_effect->transform.y;
    HSD_JObjSetTranslateY(jobj_1, f32_2);
    f32_3 = translate_z + arg_effect->transform.z;
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
    Vec3 sp38;
    Vec3 sp2C;
    HSD_JObj* jobj_2;
    f32 rotate_y;
    HSD_JObj* jobj_1;
    void* user_data;
    HSD_GObj* gobj_1;
    PAD_STACK(0x10);

    gobj_1 = arg_effect->parent_gobj;
    jobj_1 = GET_JOBJ(gobj_1);
    jobj_2 = GET_JOBJ(arg_effect->gobj);
    user_data = gobj_1->user_data;
    // user_data = (void*) GET_FIGHTER(gobj_1);
    HSD_JObjGetScale(jobj_1, &sp38);
    HSD_JObjGetScale(jobj_2, &sp2C);
    sp38.x *= sp2C.x;
    sp38.y *= sp2C.y;
    sp38.z *= sp2C.z;
    HSD_JObjSetScale(jobj_2, &sp38);

    if (((Fighter*) user_data)->facing_dir < 0.0f) {
        rotate_y = -M_PI_2;
    } else {
        rotate_y = M_PI_2;
    }
    HSD_JObjSetRotationY(jobj_2, rotate_y);
}

void efLib_8005EDDC(Effect* arg_effect)
{
    HSD_JObj* jobj_1;
    f32 rotate_z;

    jobj_1 = GET_JOBJ(arg_effect->gobj);
    if ((GET_FIGHTER((Fighter_GObj*) arg_effect->parent_gobj))->facing_dir <
        0.0f)
    {
        HSD_JObjSetRotationY(jobj_1, -M_PI_2);
        rotate_z = arg_effect->transform.z;
        HSD_JObjSetRotationZ(jobj_1, rotate_z);
    } else {
        HSD_JObjSetRotationY(jobj_1, M_PI_2);
        rotate_z = -arg_effect->transform.z;
        HSD_JObjSetRotationZ(jobj_1, rotate_z);
    }
}

void efLib_8005F08C(Effect* arg_effect)
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
    if (fighter->motion_id == 349) { // Special state 8
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
    HSD_JObj* jobj_2;
    HSD_JObj* jobj_1;
    f32 rotate_z;
    Fighter* fighter;

    fighter = GET_FIGHTER(arg_effect->parent_gobj);
    jobj_1 = GET_JOBJ(arg_effect->gobj);
    jobj_2 = GET_JOBJ(arg_effect->x0->x4);
    if (fighter->motion_id == 359) { // Special state 18
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
    HSD_MObj* mobj_1;
    HSD_TObj* tobj_1;
    u32 temp_r0;
    u32 var_ctr;
    u32 var_ctr_2;
    u32 var_r4;

    dobj_1 = HSD_JObjGetDObj(arg_jobj);
    if (dobj_1 != NULL) {
        mobj_1 = dobj_1->mobj;
    } else {
        mobj_1 = NULL;
    }
    tobj_1 = HSD_MObjGetTObj(mobj_1);
    var_r4 = arg1;
    if (arg1 != 0) {
        temp_r0 = var_r4 >> 3U;
        var_ctr = temp_r0;
        if (temp_r0 != 0) {
            do {
                tobj_1 =
                    tobj_1->next->next->next->next->next->next->next->next;
                var_ctr--;
            } while (var_ctr != 0);
            var_r4 &= 7;
            if (var_r4 != 0) {
                goto block_7;
            }
        } else {
        block_7:
            var_ctr_2 = var_r4;
            while (var_ctr_2 != 0) {
                tobj_1 = tobj_1->next;
                var_ctr_2--;
            };
        }
    }
    tobj_1->tev->konst.r = arg2 >> 0x10U;
    tobj_1->tev->konst.g = arg2 >> 8U;
    // tobj_1->tev->konst.g = arg2;
    tobj_1->tev->konst.b = arg2;
    tobj_1->tev->tev0.r = arg3 >> 0x10U;
    tobj_1->tev->tev0.g = arg3 >> 8U;
    // tobj_1->tev->tev0.g = arg3;
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
    Vec3 sp14;
    HSD_JObj* jobj_1;

    lb_8000B1CC(arg_effect->xC, NULL, &sp14);
    sp14.x += arg_effect->transform.x;
    sp14.y += arg_effect->transform.y;
    sp14.z += arg_effect->transform.z;
    jobj_1 = GET_JOBJ(arg_effect->gobj);
    HSD_JObjSetTranslate(jobj_1, &sp14);
}

Effect* efLib_8005FCD8(int arg0, HSD_GObj* gobj, void* arg2, void* arg3)
{
    HSD_psAppSRT* var_r3;
    HSD_Generator* temp_r3_2;
    Effect* ep = efLib_8005BE88(0, gobj);
    if (ep != NULL) {
        ep->x10 = fn_8005FBE4;
        ep->xC = arg2;
        // ep->x18 = arg2->x0;
        ep->x14 = ((ef_UnkStruct2*) arg2)->x4;
        // ep->x18 = arg2->x8;
        temp_r3_2 = hsd_8039EFAC(0, arg0 / 1000, arg0, GET_JOBJ(ep->gobj));
        if (temp_r3_2 != NULL) {
            var_r3 = temp_r3_2->appsrt;
            if (var_r3 == NULL) {
                var_r3 = psAddGeneratorAppSRT_begin(temp_r3_2, 0);
            }
            if (var_r3 != NULL) {
                var_r3->gp = temp_r3_2;
                temp_r3_2->type &= ~PSAPPSRT_UNK_B09;
                temp_r3_2->type |= PSAPPSRT_UNK_B11;
            } else {
                hsd_8039D4DC(temp_r3_2);
            }
        }
    }
    return ep;
}
