#include "efsync.h"

#include "efalt.h"
#include "efasync.h"
#include "efdata.h"
#include "eflib.h"
#include "types.h"

#include "baselib/gobj.h"
#include "baselib/jobj.h"
#include "baselib/particle.h"
#include "baselib/psstructs.h"
#include "baselib/random.h"

#include "MSL/math.h"

#include "ft/inlines.h"

/* 
 * TODO: efSync_Spawn is at 98% matching, and its associated jump
 *       table is at 60%. Unsure if we should hardcode it or try
 *       to match it as a .data-located variable.
 */

extern EF_DAT_Entry efAsync_DatEntries[51];

// Routes gfx_id to a specific spawn handler:
//
// .--------------------------------------------.
// | gfx_id range       | handler               |
// |--------------------+-----------------------|
// | 0x0000 - 0x024F    | efLib_CreateGenerator |
// | 0x7530 - 0x7917    | efLib_CreateGenerator |
// | 0x0250 - 0x0477    | efAsync_Dispatch      |
// | 0x0479 - 0x04BA    | efAlt_Spawn           |
// | 0x04BB - 0x0512    | cases in this switch  |
// *--------------------------------------------*
//
// Effects attach to a parent gobj and optionally a jobj for
// position/rotation inheritance. Note there's variadic args!
void* efSync_Spawn(s32 gfx_id, HSD_GObj* gobj, ...)
{
    va_list vlist;
    Vec3 translate;
    Vec3 scale;
    Vec3 scale_2;
    Vec3 scale_3;
    Vec3 scale_4;
    Vec3 scale_5;
    Vec3 scale_6;
    Vec3 unused;
    HSD_psAppSRT* psAppSRT;
    HSD_Generator* generator;
    void* ret_obj;
    HSD_JObj* jobj_2;
    HSD_JObj* jobj_1;
    Vec3* va_vec3;
    f64 half_pi;
    f32 va_f32_1;
    f32 rand_f32;
    f32 rand_rot_y;
    f32 rand_rot_x;
    f32 rand_param_x;
    f32 rand_param_y;
    s32 cnt_1;
    Fighter* fp;
    s32 cnt_2;
    PAD_STACK(0x4C);

    ret_obj = NULL;
    efLib_LoadKind = EF_LOADKIND_ASYNC;
    efLib_AnimCount = 0;
    va_start(vlist, gobj);
    if ((gfx_id == 0x479) && ((u32) efAsync_DatEntries[1].data == NULL)) {
        gfx_id = 0x506;
    }
    if (gfx_id < 0x250) {
        va_vec3 = va_arg(vlist, Vec3*);
        return efLib_CreateGenerator(gfx_id, va_vec3);
    }
    if (gfx_id / 1000 == 0x1E) {
        va_vec3 = va_arg(vlist, Vec3*);
        return efLib_CreateGenerator(gfx_id, va_vec3);
    }
    if (gfx_id < 0x478) {
        return efAsync_Dispatch(gfx_id, gobj, vlist);
    }
    if (gfx_id < 0x4BA) {
        return efAlt_Spawn(gfx_id, gobj, vlist);
    }
    efLib_LoadKind = EF_LOADKIND_SYNC;
    switch (gfx_id) {
    case 0x4BB:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(0x1770, gobj, va_arg(vlist, void*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->next = (void*)
                efLib_Create_AttachChild_Scale(0x1772, gobj, va_arg(vlist, HSD_JObj*));
        }
        break;
    case 0x4BC:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(0x1771, gobj, va_arg(vlist, void*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->next = (void*)
                efLib_Create_AttachChild_Scale(0x1773, gobj, va_arg(vlist, HSD_JObj*));
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
        ret_obj = efLib_Create_Attach(0x1B58U, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4C1:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(0x1B59, gobj, va_arg(vlist, void*));
        if (ret_obj != NULL) {
            va_f32_1 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, va_f32_1);
        }
        break;
    case 0x4C2:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(0x1B5A, gobj, va_arg(vlist, void*));
        if (ret_obj != NULL) {
            va_f32_1 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, va_f32_1);
        }
        break;
    case 0x4C3:
        ret_obj = efLib_CreateGenerator_AddAppSRT(0x24CU);
        if (ret_obj != NULL) {
            va_vec3 = va_arg(vlist, Vec3*);
            psAppSRT = ((HSD_Generator*) ret_obj)->appsrt;
            psAppSRT->translate = *va_vec3;
        }
        break;
    case 0x4C4:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(0x1B5B, gobj, va_arg(vlist, void*));
        if (ret_obj != NULL) {
            va_f32_1 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, va_f32_1);
        }
        break;
    case 0x4C5:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(0x1B5C, gobj, va_arg(vlist, void*));
        if (ret_obj != NULL) {
            va_f32_1 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, va_f32_1);
        }
        break;
    case 0x4C6:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(0x1F40, gobj, va_arg(vlist, void*));
        break;
    case 0x4C7:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(0x1F41, gobj, va_arg(vlist, void*));
        break;
    case 0x4C8:
        ret_obj = efLib_Create_Attach_Scale(0x1F42, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            if (*va_arg(vlist, f32*) < 0.0f) {
                half_pi = -M_PI_2;
            } else {
                half_pi = M_PI_2;
            }
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, half_pi);
            jobj_2 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjAnimAll(jobj_2);
        }
        break;
    case 0x4C9:
        ret_obj = efLib_Create_Attach_Scale(0x1F43, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            if (*va_arg(vlist, f32*) < 0.0f) {
                half_pi = -M_PI_2;
            } else {
                half_pi = M_PI_2;
            }
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, half_pi);
            jobj_2 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjAnimAll(jobj_2);
        }
        break;
    case 0x4CA:
        ret_obj = efLib_Create_Attach_Scale(0x1F44, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4CB:
        ret_obj = efLib_Create_Attach_Scale(0x1F45, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4CC:
        ret_obj = efLib_Create_Attach_Pos(0x1F46U, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            jobj_1 = gobj->hsd_obj;
            HSD_JObjGetScale(jobj_1, &scale);
            jobj_2 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetScale(jobj_2, &scale);
            ((EF_Effect*) ret_obj)->update = efLib_Cb_SetRotY_FromFighterDir;
        }
        break;
    case 0x4CD:
        ret_obj = efLib_Create_Attach(0x2328U, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4CE:
        ret_obj = efLib_CreateGenerator(0x2328U, va_arg(vlist, Vec3*));
        break;
    case 0x4CF:
    case 0x4D0: {
        EF_Effect* eff_1;
        EF_Effect* effect;
        va_f32_1 = 1.0f;
        va_vec3 = va_arg(vlist, Vec3*);
        translate = *va_vec3;
        if (gfx_id == 0x4CF) {
            va_f32_1 = *va_arg(vlist, f32*);
        }
        cnt_1 = 0;
    loop_141:
        rand_f32 = HSD_Randf();
        if (rand_f32 < 0.5f) {
            if (gfx_id == 0x4D0) {
                effect = efLib_Create_Attach_Pos(0x1CU, gobj, &translate);
            } else {
                effect = efLib_Create_Attach_Pos(0x1EU, gobj, &translate);
            }
        } else if (gfx_id == 0x4D0) {
            effect = efLib_Create_Attach_Pos(0x1DU, gobj, &translate);
        } else {
            effect = efLib_Create_Attach_Pos(0x1FU, gobj, &translate);
        }
        if (effect != NULL) {
            effect->update = efLib_Cb_SetOffset_FromParams;
            effect->lifetime = 0x32;
            rand_rot_y = M_TAU * HSD_Randf();
            rand_rot_x = M_TAU * HSD_Randf();
            jobj_1 = GET_JOBJ(effect->gobj);
            HSD_JObjSetScaleX(jobj_1, va_f32_1);
            jobj_1 = GET_JOBJ(effect->gobj);
            HSD_JObjSetScaleY(jobj_1, va_f32_1);
            jobj_1 = GET_JOBJ(effect->gobj);
            HSD_JObjSetScaleZ(jobj_1, va_f32_1);
            jobj_1 = GET_JOBJ(effect->gobj);
            HSD_JObjSetRotationY(jobj_1, rand_rot_y);
            jobj_1 = GET_JOBJ(effect->gobj);
            HSD_JObjSetRotationX(jobj_1, rand_rot_x);
            rand_param_x = sinf(rand_rot_y);
            effect->params.x = 2.0f * cosf(rand_rot_x) * rand_param_x;
            effect->params.y = 2.0f * sinf(rand_rot_x);
            rand_param_y = cosf(rand_rot_y);
            effect->params.z = 2.0f * cosf(rand_rot_x) * rand_param_y;
            if (cnt_1 != 0) {
                eff_1->next = effect;
                eff_1 = (void*) eff_1->next;
            } else {
                eff_1 = effect;
                ret_obj = eff_1;
            }
            if (++cnt_1 < 0xC) {
                goto loop_141;
            }
        }
        break;
    }
    case 0x4EE:
        ret_obj = efLib_Create_Attach(0x2710U, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4EF:
        ret_obj = efLib_Create_Attach(0x2711U, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4F0:
        ret_obj = efLib_Create_Attach_Scale(0x2712, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4D5:
        ret_obj = hsd_8039EFAC(0, 0xB, 0x2AF8, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4D6:
        ret_obj = efLib_Create_Attach_Scale(0x2AF8, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4D7:
        ret_obj = hsd_8039EFAC(0, 0xB, 0x2AF9, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4D8:
        ret_obj = efLib_CreateGenerator_AddAppSRT(0x61U);
        if (ret_obj != NULL) {
            va_vec3 = va_arg(vlist, Vec3*);
            psAppSRT = ((HSD_Generator*) ret_obj)->appsrt;
            psAppSRT->translate = *va_vec3;
            jobj_1 = GET_JOBJ(gobj);
            HSD_JObjGetScale(jobj_1, &scale_4);
            generator = ret_obj;
            generator->appsrt->scale.x = generator->appsrt->scale.y =
                generator->appsrt->scale.z = scale_4.y;
            generator->appsrt->rot.y = M_PI_2;
        }
        break;
    case 0x4D9:
        ret_obj = efLib_Create_Attach_Pos(0x2EE0U, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            if (*va_arg(vlist, f32*) < 0.0f) {
                half_pi = -M_PI_2;
            } else {
                half_pi = M_PI_2;
            }
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, half_pi);
            jobj_2 = GET_JOBJ(gobj);
            HSD_JObjGetScale(jobj_2, &scale_6);
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetScale(jobj_1, &scale_6);
        }
        break;
    case 0x4DA: {
        EF_Effect* eff_1;
        jobj_1 = va_arg(vlist, HSD_JObj*);
        ret_obj = efLib_Create_Attach_Scale(0x2EE1, gobj, jobj_1);
        if (ret_obj != NULL) {
            eff_1 = efLib_Create_Attach_Scale(0x2EE2, gobj, jobj_1);
            ((EF_Effect*) ret_obj)->next = (void*) eff_1;
            if (eff_1 != NULL) {
                ((EF_Effect*) ret_obj)->update = efLib_Cb_ftKp_SpecialHi;
            }
        }
        break;
    }
    case 0x4DB:
        ret_obj = efLib_CreateGenerator_Attach_Scale(0x2EE5, vlist, gobj);
        break;
    case 0x4DC:
        ret_obj = efLib_CreateGenerator_Attach_Scale(0x2EE6, vlist, gobj);
        break;
    case 0x4DD:
        ret_obj = efLib_CreateGenerator_Attach_Scale(0x2EE7, vlist, gobj);
        break;
    case 0x4DE:
        ret_obj = efLib_CreateGenerator_Attach_Scale(0x2EE8, vlist, gobj);
        break;
    case 0x4DF:
        ret_obj = efLib_CreateGenerator_Attach_Scale(0x143, vlist, gobj);
        break;
    case 0x4E0:
        ret_obj = efLib_Create_Attach(0x32C8U, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4E1:
        ret_obj = efLib_Create(0x32C9, gobj);
        if (ret_obj != NULL) {
            jobj_1 = va_arg(vlist, HSD_JObj*);
            ((EF_Effect*) ret_obj)->attach_jobj = jobj_1;
            ((EF_Effect*) ret_obj)->update = efLib_Cb_SetOffsetY_FromParamY;
            jobj_2 = jobj_1;
            while (HSD_JObjGetParent(jobj_2) != NULL) {
                jobj_2 = HSD_JObjGetParent(jobj_2);
            }
            HSD_JObjGetScale(jobj_1, &scale_5);
            ((EF_Effect*) ret_obj)->params = *va_arg(vlist, Vec3*);
            ((EF_Effect*) ret_obj)->params.y *= scale_5.y;
        }
        break;
    case 0x4E2:
        ret_obj = efLib_Create_Attach_Pos(0x32CAU, gobj, va_arg(vlist, Vec3*));
        break;
    case 0x4E3:
        ret_obj = efLib_CreateGenerator(0x18AU, va_arg(vlist, Vec3*));
        break;
    case 0x4E4:
        ret_obj = efLib_CreateGenerator(0x194U, va_arg(vlist, Vec3*));
        break;
    case 0x4E5:
        ret_obj = hsd_8039EFAC(0, 0, 0x17D, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4E6:
        ret_obj = hsd_8039EFAC(0, 0, 0x17E, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4E7:
        ret_obj = efLib_CreateGenerator(0x196U, va_arg(vlist, Vec3*));
        break;
    case 0x4E8:
        ret_obj = efLib_Create_Attach_Pos(0x32CBU, gobj, va_arg(vlist, Vec3*));
        break;
    case 0x4E9:
        ret_obj = hsd_8039EFAC(0, 0xE, 0x36B0, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4EA:
        ret_obj = hsd_8039EFAC(0, 0xE, 0x36B1, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4EB:
        ret_obj = efLib_CreateGenerator_AppSRT_SetFacingDir(0x36B6, vlist);
        break;
    case 0x4EC:
        ret_obj = hsd_8039EFAC(0, 0xE, 0x36B7, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4ED:
        ret_obj = efLib_Create_AttachChild(0x36B0U, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4D1:
        ret_obj = hsd_8039EFAC(0, 0, 0x64, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4D2:
        ret_obj = efLib_Create_Attach_Pos(0x3A98U, gobj, va_arg(vlist, Vec3*));
        break;
    case 0x4D3:
        jobj_1 = va_arg(vlist, HSD_JObj*);
        ret_obj = efLib_CreateGenerator_Attach_AddAppSRT(0x172, jobj_1);
        if (ret_obj != NULL) {
            efLib_CreateGenerator_Attach_AddAppSRT(0x173, jobj_1);
        }
        break;
    case 0x4D4:
        ret_obj = efLib_CreateGenerator_Attach(0x11E, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4F1:
        ret_obj = efLib_CreateGenerator_AppSRT_SetFacingDir(0x3E80, vlist);
        break;
    case 0x4F2:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(0x3E80, gobj, va_arg(vlist, void*));
        break;
    case 0x4F3:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(0x3E81, gobj, va_arg(vlist, void*));
        break;
    case 0x4F4:
        ret_obj = efLib_Create_AttachChild(0x4268U, gobj, va_arg(vlist, HSD_JObj*));
        goto block_297;
        break;
    case 0x4F5:
        ret_obj = efLib_Create_AttachChild(0x4269U, gobj, va_arg(vlist, HSD_JObj*));
    block_297:
        if (ret_obj != NULL) {
            jobj_1 = GET_JOBJ(gobj);
            HSD_JObjGetScale(jobj_1, &scale_4);
            if (GET_JOBJ(((EF_Effect*) ret_obj)->gobj) == NULL) {
                __assert("jobj.h", 823, "jobj");
            }
            jobj_2 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetScale(jobj_2, &scale_4);
        }
        break;
    case 0x4F6:
        ret_obj = efLib_Create_Attach_Scale(0x426A, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4F7:
        ret_obj = efLib_Create_Attach_Scale(0x426B, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4F8:
        ret_obj = efLib_CreateGenerator_Attach_Scale(0x6E, vlist, gobj);
        break;
    case 0x4F9:
        ret_obj = efLib_CreateGenerator_Attach_Scale(0x1C8, vlist, gobj);
        break;
    case 0x4FA:
        ret_obj = efLib_CreateGenerator_Attach_Scale(0x166, vlist, gobj);
        break;
    case 0x4FB:
        ret_obj = hsd_8039EFAC(0, 0, 0x71, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4FE:
        ret_obj = efLib_Create_Attach(0x426CU, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4FF:
    case 0x500:
        ret_obj =
            efLib_Create_Attach_Scale(0x426D, gobj,
                           ((Fighter*) gobj->user_data)->parts[1].joint);
        break;
    case 0x501:
        fp = GET_FIGHTER(gobj);
        ret_obj =
            efLib_Create_Attach_Scale(0x426E, gobj,
                           ((Fighter*) gobj->user_data)->parts[1].joint);
        if (ret_obj != NULL) {
            if (fp->facing_dir < 0.0f) {
                half_pi = -M_PI_2;
            } else {
                half_pi = M_PI_2;
            }
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, half_pi);
            ((EF_Effect*) ret_obj)->attach_jobj = fp->parts[85].joint;
            ((EF_Effect*) ret_obj)->update = efLib_Cb_LifetimeEndSpawn;
            ((EF_Effect*) ret_obj)->lifetime = 6;
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
        ret_obj = efLib_CreateGenerator(0x6AU, va_arg(vlist, Vec3*));
        break;
    case 0x504:
        ret_obj = efLib_CreateGenerator_AddAppSRT(0x6DU);
        if (ret_obj != NULL) {
            va_vec3 = va_arg(vlist, Vec3*);
            psAppSRT = ((HSD_Generator*) ret_obj)->appsrt;
            psAppSRT->translate = *va_vec3;
            jobj_1 = GET_JOBJ(gobj);
            HSD_JObjGetScale(jobj_1, &scale_3);
            generator = ret_obj;
            generator->appsrt->scale.x = generator->appsrt->scale.y =
                generator->appsrt->scale.z = scale_3.y;
        }
        break;
    case 0x505:
        ret_obj = efLib_CreateGenerator_AddAppSRT(0x79U);
        if (ret_obj != NULL) {
            va_vec3 = va_arg(vlist, Vec3*);
            psAppSRT = ((HSD_Generator*) ret_obj)->appsrt;
            psAppSRT->translate = *va_vec3;
            jobj_1 = gobj->hsd_obj;
            HSD_JObjGetScale(jobj_1, &scale_2);
            generator = ret_obj;
            generator->appsrt->scale.x = generator->appsrt->scale.y =
                generator->appsrt->scale.z = scale_2.y;
        }
        break;
    case 0x506:
        ret_obj = efLib_CreateGenerator(0x4658U, va_arg(vlist, Vec3*));
        break;
    case 0x507:
        jobj_1 = va_arg(vlist, HSD_JObj*);
        ret_obj = efLib_Create_Attach(0x4650U, gobj, jobj_1);
        if (ret_obj != NULL) {
            if (*va_arg(vlist, f32*) < 0.0f) {
                half_pi = -M_PI_2;
            } else {
                half_pi = M_PI_2;
            }
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, half_pi);
        }
        hsd_8039EFAC(0, 0x12, 0x4650, jobj_1);
        break;
    case 0x508:
        ret_obj = efLib_CreateGenerator(0x4652U, va_arg(vlist, Vec3*));
        break;
    case 0x509:
        ret_obj = efLib_Create_Attach_Scale(0x4651, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->update = efLib_Cb_ftLg_SpecialLw;
        }
        break;
    case 0x50A:
        ret_obj = hsd_8039EFAC(0, 0, 0x5F, va_arg(vlist, HSD_JObj*));
        break;
    case 0x50B:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(0x4A38, gobj, va_arg(vlist, void*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->next =
                (void*) efLib_Create_Attach_Scale_FacingDir(0x4A39, gobj, va_arg(vlist, void*));
        }
        break;
    case 0x50C:
        ret_obj = efLib_Create_Attach(0x4A3AU, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->params.z = *va_arg(vlist, f32*);
            ((EF_Effect*) ret_obj)->update = efLib_Cb_SetRotYZ_FromParamZ_FighterDir;
        }
        break;
    case 0x50D:
        ret_obj = efLib_Create_Attach(0x4A3BU, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x50E:
        ret_obj = efLib_Create_Attach_Scale(0x4A3C, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            if (*va_arg(vlist, f32*) < 0.0f) {
                half_pi = -M_PI_2;
            } else {
                half_pi = M_PI_2;
            }
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, half_pi);
        }
        break;
    case 0x50F:
        ret_obj = efLib_Create_Attach_Scale(0x4A3D, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            if (*va_arg(vlist, f32*) < 0.0f) {
                half_pi = -M_PI_2;
            } else {
                half_pi = M_PI_2;
            }
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, half_pi);
        }
        break;
    case 0x510:
        ret_obj = efLib_CreateGenerator_AppSRT_SetFacingDir(0xBF68, vlist);
        break;
    case 0x511:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(0xBF68, gobj, va_arg(vlist, void*));
        break;
    case 0x512:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(0xBF69, gobj, va_arg(vlist, void*));
        break;
    }
    while (efLib_AnimCount != 0) {
        cnt_2 = efLib_AnimCount - 1;
        efLib_AnimCount = cnt_2;
        HSD_JObjAnimAll(((EF_ParamEntry*) (((u32*) efLib_AnimQueue) + cnt_2))->gobj);
    }

    va_end(vlist);
    return ret_obj;
}
