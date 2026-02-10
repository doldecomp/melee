#include "efsync.h"

#include "efasync.h"
#include "eflib.h"
#include "efsync.h"
#include "math.h"
#include "placeholder.h"
#include "types.h"

#include "baselib/forward.h"

#include "baselib/gobj.h"
#include "baselib/jobj.h"
#include "baselib/particle.h"
#include "baselib/psstructs.h"
#include "baselib/random.h"

#include "ef/forward.h"

#include "ft/inlines.h"
/// #include <cstddef>

extern struct _struct_efAsync_803C025C_0xC efAsync_803C025C[51];
extern Effect* ef_80061D70(s32, HSD_GObj*, void*);
extern struct _struct_efLib_80458EE0_0x8 efLib_80458EE0[16];
extern s32 efLib_804D64E8;
extern s32 efLib_804D64F0;
void* jumptable_803BF870[88];

void* efSync_Spawn(s32 arg_gfx_id, HSD_GObj* arg_gobj, ...)
{
    // s32* sp204;
    // ?* sp200;
    va_list vlist;
    Vec3 sp1F0;
    Vec3 sp1E4;
    Vec3 spAC;
    Vec3 spA0;
    Vec3 sp94;
    Vec3 sp88;
    Vec3 sp7C;
    Vec3 sp70;
    HSD_psAppSRT* psAppSRT_1;
    HSD_Generator* generator_1;
    Effect* eff_1;
    void* ret_obj;
    HSD_JObj* jobj_1;
    HSD_JObj* jobj_2;
    Vec3* vec3_1;
    f64 f64_1;
    f32 f32_1;
    f32 f32_2;
    f32 f32_3;
    f32 f32_4;
    f32 f32_5;
    f32 f32_6;
    s32 s32_1;
    s32 gfx_id;
    // Item* item_1;
    Fighter* fighter_1;
    s32 cnt;
    PAD_STACK(0x5C);

    va_start(vlist, arg_gobj);

    // var_r25 = saved_reg_r25;
    // if (M2C_ERROR(/* Read from unset register $cr0_eq */)) {
    //     sp28 = arg_gobj;
    //     sp30 = arg_gobj;
    //     sp38 = arg_gobj;
    //     sp40 = arg_gobj;
    //     sp48 = arg_gobj;
    //     sp50 = arg_gobj;
    //     sp58 = arg_gobj;
    //     sp60 = arg_gobj;
    // }
    // sp8 = arg_gfx_id;
    gfx_id = arg_gfx_id;
    ret_obj = NULL;
    // spC = arg_gobj;
    // sp10 = arg_gobj;
    // temp_r5 = "!(jobj->flags & JOBJ_USE_QUATERNION)";
    // sp14 = arg_gobj;
    // sp18 = arg_gobj;
    // sp1C = arg_gobj;
    // sp20 = arg_gobj;
    // sp24 = arg_gobj;
    efLib_804D64E8 = 0;
    efLib_804D64F0 = 0;
    // sp1FC = 0x02000000;
    // sp200 = &arg2;
    // sp204 = &sp8;
    if ((gfx_id == 0x479) && ((u32) efAsync_803C025C[1].unk8 == NULL)) {
        gfx_id = 0x506;
    }
    if (gfx_id < 0x250) {
        vec3_1 = va_arg(vlist, Vec3*);
        return efLib_8005C9FC(gfx_id, vec3_1);
    }
    if (gfx_id / 1000 == 0x1E) {
        vec3_1 = va_arg(vlist, Vec3*);
        return efLib_8005C9FC(gfx_id, vec3_1);
    }
    if (gfx_id < 0x478) {
        // return efAsync_80063930(gfx_id, arg_gobj, va_arg(vlist, void*));
        return efAsync_80063930(gfx_id, arg_gobj, vlist);
    }
    if (gfx_id < 0x4BA) {
        // return ef_80061D70(gfx_id, arg_gobj, va_arg(vlist, void*));
        return ef_80061D70(gfx_id, arg_gobj, vlist);
    }
    efLib_804D64E8 = 1;
    switch (gfx_id) {
    case 0x4BB:
        ret_obj = efLib_8005C6F4(0x1770, arg_gobj, va_arg(vlist, void*));
        if (ret_obj != NULL) {
            ret_obj =
                efLib_8005C5C4(0x1772, arg_gobj, va_arg(vlist, HSD_JObj*));
        }
        break;
    case 0x4BC:
        ret_obj = efLib_8005C6F4(0x1771, arg_gobj, va_arg(vlist, void*));
        if (ret_obj != NULL) {
            ret_obj =
                efLib_8005C5C4(0x1773, arg_gobj, va_arg(vlist, HSD_JObj*));
        }
        break;
    case 0x4BD:
        ret_obj = hsd_8039EFAC(0, 7, 0x1B58, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4BE:
        ret_obj = hsd_8039EFAC(0, 7, 0x1B5C, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4BF:
        jobj_1 = va_arg(vlist, HSD_JObj*);
        ret_obj = hsd_8039EFAC(0, 7, 0x1B5D, jobj_1);
        hsd_8039EFAC(0, 0, 0x5F, jobj_1);
        break;
    case 0x4C0:
        ret_obj = efLib_8005C1B4(0x1B58U, arg_gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4C1:
        ret_obj = efLib_8005C6F4(0x1B59, arg_gobj, va_arg(vlist, void*));
        if (ret_obj != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, f32_1);
        }
        break;
    case 0x4C2:
        ret_obj = efLib_8005C6F4(0x1B5A, arg_gobj, va_arg(vlist, void*));
        if (ret_obj != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, f32_1);
        }
        break;
    case 0x4C3:
        ret_obj = efLib_8005CAB0(0x24CU);
        if (ret_obj != NULL) {
            vec3_1 = va_arg(vlist, Vec3*);
            psAppSRT_1 = ((HSD_Generator*) ret_obj)->appsrt;
            psAppSRT_1->translate = *vec3_1;
        }
        break;
    case 0x4C4:
        ret_obj = efLib_8005C6F4(0x1B5B, arg_gobj, va_arg(vlist, void*));
        if (ret_obj != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, f32_1);
        }
        break;
    case 0x4C5:
        ret_obj = efLib_8005C6F4(0x1B5C, arg_gobj, va_arg(vlist, void*));
        if (ret_obj != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, f32_1);
        }
        break;
    case 0x4C6:
        ret_obj = efLib_8005C6F4(0x1F40, arg_gobj, va_arg(vlist, void*));
        break;
    case 0x4C7:
        ret_obj = efLib_8005C6F4(0x1F41, arg_gobj, va_arg(vlist, void*));
        break;
    case 0x4C8:
        ret_obj = efLib_8005C3DC(0x1F42, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            if (*va_arg(vlist, f32*) < 0.0f) {
                f64_1 = -M_PI_2;
            } else {
                f64_1 = M_PI_2;
            }
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, f64_1);
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjAnimAll(jobj_1);
        }
        break;
    case 0x4C9:
        ret_obj = efLib_8005C3DC(0x1F43, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            if (*va_arg(vlist, f32*) < 0.0f) {
                f64_1 = -M_PI_2;
            } else {
                f64_1 = M_PI_2;
            }
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, f64_1);
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjAnimAll(jobj_1);
        }
        break;
    case 0x4CA:
        ret_obj = efLib_8005C3DC(0x1F44, arg_gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4CB:
        ret_obj = efLib_8005C3DC(0x1F45, arg_gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4CC:
        ret_obj = efLib_8005C814(0x1F46U, arg_gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            jobj_1 = arg_gobj->hsd_obj;
            HSD_JObjGetScale(jobj_1, &sp1E4);
            jobj_2 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetScale(jobj_2, &sp1E4);
            ((Effect*) ret_obj)->x10 = efLib_8005E2B4;
        }
        break;
    case 0x4CD:
        ret_obj = efLib_8005C1B4(0x2328U, arg_gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4CE:
        ret_obj = efLib_8005C9FC(0x2328U, va_arg(vlist, Vec3*));
        break;
    case 0x4CF:
    case 0x4D0:
        f32_1 = 1.0f;
        vec3_1 = va_arg(vlist, Vec3*);
        sp1F0 = *vec3_1;
        if (gfx_id == 0x4CF) {
            f32_1 = *va_arg(vlist, f32*);
        }
        s32_1 = 0;
    loop_141:
        f32_2 = HSD_Randf();
        if (f32_2 < 0.5f) {
            if (gfx_id == 0x4D0) {
                ret_obj = efLib_8005C814(0x1CU, arg_gobj, &sp1F0);
            } else {
                ret_obj = efLib_8005C814(0x1EU, arg_gobj, &sp1F0);
            }
        } else if (gfx_id == 0x4D0) {
            ret_obj = efLib_8005C814(0x1DU, arg_gobj, &sp1F0);
        } else {
            ret_obj = efLib_8005C814(0x1FU, arg_gobj, &sp1F0);
        }
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x10 = efLib_8005E950;
            ((Effect*) ret_obj)->x24 = 0x32;
            f32_3 = 2 * M_PI * HSD_Randf();
            f32_4 = 2 * M_PI * HSD_Randf();
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetScaleX(jobj_1, f32_1);
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetScaleY(jobj_1, f32_1);
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetScaleZ(jobj_1, f32_1);
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, f32_3);
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationX(jobj_1, f32_4);
            f32_5 = sinf(f32_3);
            ((Effect*) ret_obj)->translate.x = 2.0f * cosf(f32_4) * f32_5;
            ((Effect*) ret_obj)->translate.y = 2.0f * sinf(f32_4);
            f32_6 = cosf(f32_3);
            ((Effect*) ret_obj)->translate.z = 2.0f * cosf(f32_4) * f32_6;
            if (s32_1 != 0) {
                eff_1->x0 = ret_obj;
                eff_1 = (void*) eff_1->x0;
            } else {
                eff_1 = ret_obj;
                ret_obj = eff_1;
            }
            s32_1 += 1;
            if (s32_1 >= 0xC) {
            } else {
                goto loop_141;
            }
        }
        break;
    case 0x4EE:
        ret_obj = efLib_8005C1B4(0x2710U, arg_gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4EF:
        ret_obj = efLib_8005C1B4(0x2711U, arg_gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4F0:
        ret_obj = efLib_8005C3DC(0x2712, arg_gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4D5:
        ret_obj = hsd_8039EFAC(0, 0xB, 0x2AF8, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4D6:
        ret_obj = efLib_8005C3DC(0x2AF8, arg_gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4D7:
        ret_obj = hsd_8039EFAC(0, 0xB, 0x2AF9, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4D8:
        ret_obj = efLib_8005CAB0(0x61U);
        if (ret_obj != NULL) {
            vec3_1 = va_arg(vlist, Vec3*);
            psAppSRT_1 = ((HSD_Generator*) ret_obj)->appsrt;
            psAppSRT_1->translate = *vec3_1;
            jobj_1 = GET_JOBJ(arg_gobj);
            HSD_JObjGetScale(jobj_1, vec3_1);
            generator_1 = ret_obj;
            generator_1->appsrt->scale.x = generator_1->appsrt->scale.y =
                generator_1->appsrt->scale.z = vec3_1->y;
            generator_1->appsrt->rot.y = M_PI_2;
        }
        break;
    case 0x4D9:
        ret_obj = efLib_8005C814(0x2EE0U, arg_gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            if (*va_arg(vlist, f32*) < 0.0f) {
                f64_1 = -M_PI_2;
            } else {
                f64_1 = M_PI_2;
            }
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, f64_1);
            jobj_2 = GET_JOBJ(arg_gobj);
            HSD_JObjGetScale(jobj_1, &sp7C);
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetScale(jobj_1, &sp7C);
        }
        break;
    case 0x4DA:
        jobj_1 = va_arg(vlist, HSD_JObj*);
        ret_obj = efLib_8005C3DC(0x2EE1, arg_gobj, jobj_1);
        if (ret_obj != NULL) {
            eff_1 = efLib_8005C3DC(0x2EE2, arg_gobj, jobj_1);
            ((Effect*) ret_obj)->x0 = (void*) eff_1;
            if (eff_1 != NULL) {
                ((Effect*) ret_obj)->x10 = efLib_8005F454;
            }
        }
        break;
    case 0x4DB:
        ret_obj = efLib_8005CD2C(0x2EE5, vlist, arg_gobj);
        break;
    case 0x4DC:
        ret_obj = efLib_8005CD2C(0x2EE6, vlist, arg_gobj);
        break;
    case 0x4DD:
        ret_obj = efLib_8005CD2C(0x2EE7, vlist, arg_gobj);
        break;
    case 0x4DE:
        ret_obj = efLib_8005CD2C(0x2EE8, vlist, arg_gobj);
        break;
    case 0x4DF:
        ret_obj = efLib_8005CD2C(0x143, vlist, arg_gobj);
        break;
    case 0x4E0:
        ret_obj = efLib_8005C1B4(0x32C8U, arg_gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4E1:
        ret_obj = efLib_8005BE88(0x32C9, arg_gobj);
        if (ret_obj != NULL) {
            jobj_1 = va_arg(vlist, HSD_JObj*);
            ((Effect*) ret_obj)->xC = jobj_1;
            ((Effect*) ret_obj)->x10 = efLib_8005DDB8;
#if 1
        loop_268:
            if (jobj_1 == NULL) {
                jobj_2 = NULL;
            } else {
                jobj_2 = jobj_1->parent;
            }
            if (jobj_2 != NULL) {
                if (jobj_1 == NULL) {
                    jobj_2 = NULL;
                } else {
                    jobj_2 = jobj_1->parent;
                }
                jobj_1 = jobj_2;
                goto loop_268;
            }
            HSD_JObjGetScale(jobj_2, &sp88);
#else
            while (jobj_1 != NULL) {
                if (jobj_1 == NULL) {
                    jobj_2 = NULL;
                } else {
                    jobj_2 = jobj_1->parent;
                }
                jobj_1 = jobj_2;
            }
            HSD_JObjGetScale(jobj_2, &sp88);

#endif
            sp88 = *va_arg(vlist, Vec3*);
            // sp88 = *vec3_1;
            ((Effect*) ret_obj)->translate = sp88;
            // ((Effect*) ret_obj)->scale = *vec3_1;
            // ((Effect*) ret_obj)->scale.x = vec3_1->x;
            // ((Effect*) ret_obj)->scale.y = vec3_1->y;
            // ((Effect*) ret_obj)->scale.z = vec3_1->z;
            ((Effect*) ret_obj)->translate.y *= sp88.y;
            // ((Effect*) ret_obj)->scale.y *= vec3_1->y;
        }
        break;
    case 0x4E2:
        ret_obj = efLib_8005C814(0x32CAU, arg_gobj, va_arg(vlist, Vec3*));
        break;
    case 0x4E3:
        ret_obj = efLib_8005C9FC(0x18AU, va_arg(vlist, Vec3*));
        break;
    case 0x4E4:
        ret_obj = efLib_8005C9FC(0x194U, va_arg(vlist, Vec3*));
        break;
    case 0x4E5:
        ret_obj = hsd_8039EFAC(0, 0, 0x17D, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4E6:
        ret_obj = hsd_8039EFAC(0, 0, 0x17E, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4E7:
        ret_obj = efLib_8005C9FC(0x196U, va_arg(vlist, Vec3*));
        break;
    case 0x4E8:
        ret_obj = efLib_8005C814(0x32CBU, arg_gobj, va_arg(vlist, Vec3*));
        break;
    case 0x4E9:
        ret_obj = hsd_8039EFAC(0, 0xE, 0x36B0, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4EA:
        ret_obj = hsd_8039EFAC(0, 0xE, 0x36B1, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4EB:
        ret_obj = efLib_8005CF40(0x36B6, vlist);
        break;
    case 0x4EC:
        ret_obj = hsd_8039EFAC(0, 0xE, 0x36B7, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4ED:
        ret_obj = efLib_8005C2BC(0x36B0U, arg_gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4D1:
        ret_obj = hsd_8039EFAC(0, 0, 0x64, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4D2:
        ret_obj = efLib_8005C814(0x3A98U, arg_gobj, va_arg(vlist, Vec3*));
        break;
    case 0x4D3:
        jobj_1 = va_arg(vlist, HSD_JObj*);
        ret_obj = efLib_8005CC84(0x172, jobj_1);
        if (ret_obj != NULL) {
            efLib_8005CC84(0x173, jobj_1);
        }
        break;
    case 0x4D4:
        ret_obj = efLib_8005CC2C(0x11E, va_arg(vlist, HSD_JObj*));
        // ret_obj = M2C_ERROR(/* Read from unset register $r3 */);
        break;
    case 0x4F1:
        // ret_obj = efLib_8005CF40(0x3E80, va_arg(vlist, void*));
        ret_obj = efLib_8005CF40(0x3E80, vlist);
        break;
    case 0x4F2:
        ret_obj = efLib_8005C6F4(0x3E80, arg_gobj, va_arg(vlist, void*));
        break;
    case 0x4F3:
        ret_obj = efLib_8005C6F4(0x3E81, arg_gobj, va_arg(vlist, void*));
        break;
    case 0x4F4:
        ret_obj = efLib_8005C2BC(0x4268U, arg_gobj, va_arg(vlist, HSD_JObj*));
        goto block_297;
        break;
    case 0x4F5:
        ret_obj = efLib_8005C2BC(0x4269U, arg_gobj, va_arg(vlist, HSD_JObj*));
    block_297:
        if (ret_obj != NULL) {
            jobj_1 = GET_JOBJ(arg_gobj);
            HSD_JObjGetScale(jobj_1, &sp94);
            jobj_2 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetScale(jobj_2, &sp94);
        }
    case 0x4F6:
        ret_obj = efLib_8005C3DC(0x426A, arg_gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4F7:
        ret_obj = efLib_8005C3DC(0x426B, arg_gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4F8:
        ret_obj = efLib_8005CD2C(0x6E, vlist, arg_gobj);
        break;
    case 0x4F9:
        ret_obj = efLib_8005CD2C(0x1C8, vlist, arg_gobj);
        break;
    case 0x4FA:
        ret_obj = efLib_8005CD2C(0x166, vlist, arg_gobj);
        break;
    case 0x4FB:
        ret_obj = hsd_8039EFAC(0, 0, 0x71, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4FE:
        ret_obj = efLib_8005C1B4(0x426CU, arg_gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4FF:
    case 0x500:
        ret_obj =
            efLib_8005C3DC(0x426D, arg_gobj,
                           ((Fighter*) arg_gobj->user_data)->parts[1].joint);
        break;
    case 0x501:
        fighter_1 = GET_FIGHTER(arg_gobj);
        ret_obj =
            efLib_8005C3DC(0x426D, arg_gobj,
                           ((Fighter*) arg_gobj->user_data)->parts[1].joint);
        if (ret_obj != NULL) {
            if (fighter_1->facing_dir < 0.0f) {
                f64_1 = -M_PI_2;
            } else {
                f64_1 = M_PI_2;
            }
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, f64_1);
            ((Effect*) ret_obj)->xC = fighter_1->parts[85].joint;
            ((Effect*) ret_obj)->x10 = efLib_8005EB70;
            ((Effect*) ret_obj)->x24 = 6;
        }
        break;
    case 0x502:
        ret_obj = hsd_8039EFAC(0, 0, 0x1A6, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4FC:
        ret_obj = hsd_8039EFAC(0, 0x11, 0x426D, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4FD:
        ret_obj = hsd_8039EFAC(0, 0x11, 0x4271, va_arg(vlist, HSD_JObj*));
        break;
    case 0x503:
        ret_obj = efLib_8005C9FC(0x6AU, va_arg(vlist, Vec3*));
        break;
    case 0x504:
        ret_obj = efLib_8005CAB0(0x6DU);
        if (ret_obj != NULL) {
            vec3_1 = va_arg(vlist, Vec3*);
            psAppSRT_1 = ((HSD_Generator*) ret_obj)->appsrt;
            psAppSRT_1->translate = *vec3_1;
            jobj_1 = GET_JOBJ(arg_gobj);
            HSD_JObjGetScale(jobj_1, &spA0);
            generator_1 = ret_obj;
            generator_1->appsrt->scale.x = generator_1->appsrt->scale.y =
                generator_1->appsrt->scale.z = spA0.y;
        }
        break;
    case 0x505:
        ret_obj = efLib_8005CAB0(0x79U);
        if (ret_obj != NULL) {
            vec3_1 = va_arg(vlist, Vec3*);
            psAppSRT_1 = ((HSD_Generator*) ret_obj)->appsrt;
            psAppSRT_1->translate = *vec3_1;
            jobj_1 = arg_gobj->hsd_obj;
            HSD_JObjGetScale(jobj_1, &spAC);
            generator_1 = ret_obj;
            generator_1->appsrt->scale.x = generator_1->appsrt->scale.y =
                generator_1->appsrt->scale.z = spAC.y;
        }
        break;
    case 0x506:
        ret_obj = efLib_8005C9FC(0x4658U, va_arg(vlist, Vec3*));
        break;
    case 0x507:
        jobj_1 = va_arg(vlist, HSD_JObj*);
        ret_obj = efLib_8005C1B4(0x4650U, arg_gobj, jobj_1);
        if (ret_obj != NULL) {
            if (*va_arg(vlist, f32*) < 0.0f) {
                f64_1 = -M_PI_2;
            } else {
                f64_1 = M_PI_2;
            }
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, f64_1);
        }
        hsd_8039EFAC(0, 0x12, 0x4650, jobj_1);
        break;
    case 0x508:
        ret_obj = efLib_8005C9FC(0x4652U, va_arg(vlist, Vec3*));
        break;
    case 0x509:
        ret_obj = efLib_8005C3DC(0x4651, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x10 = efLib_8005F270;
        }
        break;
    case 0x50A:
        ret_obj = hsd_8039EFAC(0, 0, 0x5F, va_arg(vlist, HSD_JObj*));
        break;
    case 0x50B:
        ret_obj = efLib_8005C6F4(0x4A38, arg_gobj, va_arg(vlist, void*));
        if (ret_obj != NULL) {
            ret_obj = efLib_8005C6F4(0x4A39, arg_gobj, va_arg(vlist, void*));
        }
        break;
    case 0x50C:
        ret_obj = efLib_8005C1B4(0x4A3AU, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->translate.z = *va_arg(vlist, f32*);
            ((Effect*) ret_obj)->x10 = efLib_8005EDDC;
        }
        break;
    case 0x50D:
        ret_obj = efLib_8005C1B4(0x4A3BU, arg_gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x50E:
        ret_obj = efLib_8005C3DC(0x4A3C, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            if (*va_arg(vlist, f32*) < 0.0f) {
                f64_1 = -M_PI_2;
            } else {
                f64_1 = M_PI_2;
            }
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, f64_1);
        }
        break;
    case 0x50F:
        ret_obj = efLib_8005C3DC(0x4A3D, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            if (*va_arg(vlist, f32*) < 0.0f) {
                f64_1 = -M_PI_2;
            } else {
                f64_1 = M_PI_2;
            }
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, f64_1);
        }
        break;
    case 0x510:
        ret_obj = efLib_8005CF40(0xBF68, vlist);
        break;
    case 0x511:
        ret_obj = efLib_8005C6F4(0xBF68, arg_gobj, va_arg(vlist, void*));
        break;
    case 0x512:
        ret_obj = efLib_8005C6F4(0xBF69, arg_gobj, va_arg(vlist, void*));
        break;
    }
    while (efLib_804D64F0 != 0) {
        cnt = efLib_804D64F0 - 1;
        efLib_804D64F0 = cnt;
        // efLib_804D64F0--;
        HSD_JObjAnimAll((efLib_80458EE0[cnt].unk0));
        // HSD_JObjAnimAll((efLib_80458EE0[efLib_804D64F0].unk0));
    }

    va_end(vlist);
    return ret_obj;
}
