#include "efsync.h"

#include <math.h>

#include "efalt.h"
#include "efasync.h"
#include "efdata.h"
#include "eflib.h"
#include "inlines.h"
#include "types.h"
#include <melee/ft/inlines.h>
#include <sysdolphin/baselib/generator.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/psstructs.h>
#include <sysdolphin/baselib/random.h>

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
    HSD_psAppSRT* psAppSRT;
    void* ret_obj;
    EF_Effect* effect;
    HSD_JObj* jobj_2;
    HSD_JObj* jobj_1;
    Vec3* va_vec3;
    f64 half_pi;
    f32 va_f32_1;
    f32 rand_f32;
    f32 rand_param_x;
    f32 rand_param_y;
    f32 rand_rot_y;
    Fighter* fp;
    s32 cnt_2;
    f32 rand_rot_x;
    PAD_STACK(0x44);

    efLib_AnimCount = efLib_LoadKind = (u32) (ret_obj = NULL);
    va_start(vlist, gobj);
    if ((gfx_id == 0x479) && (efAsync_DatEntries[1].data == NULL)) {
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
        ret_obj = efLib_Create_Attach_Scale_FacingDir(
            0x1770, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            effect->next = efLib_Create_AttachChild_Scale(
                0x1772, gobj, va_arg(vlist, HSD_JObj*));
        }
        break;
    case 0x4BC:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(
            0x1771, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            effect->next = efLib_Create_AttachChild_Scale(
                0x1773, gobj, va_arg(vlist, HSD_JObj*));
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
        ret_obj = efLib_Create_Attach_Scale_FacingDir(
            0x1B59, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            va_f32_1 = *va_arg(vlist, f32*);
            HSD_JObjSetRotationZ(GET_JOBJ(effect->gobj), va_f32_1);
        }
        break;
    case 0x4C2:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(
            0x1B5A, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            va_f32_1 = *va_arg(vlist, f32*);
            HSD_JObjSetRotationZ(GET_JOBJ(effect->gobj), va_f32_1);
        }
        break;
    case 0x4C3: {
        HSD_Generator* gen = efLib_CreateGenerator_AddAppSRT(0x24CU);
        if (gen != NULL) {
            va_vec3 = va_arg(vlist, Vec3*);
            ret_obj = gen;
            psAppSRT = gen->appsrt;
            psAppSRT->translate = *va_vec3;
        }
        break;
    }
    case 0x4C4:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(
            0x1B5B, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            va_f32_1 = *va_arg(vlist, f32*);
            HSD_JObjSetRotationZ(GET_JOBJ(effect->gobj), va_f32_1);
        }
        break;
    case 0x4C5:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(
            0x1B5C, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            va_f32_1 = *va_arg(vlist, f32*);
            HSD_JObjSetRotationZ(GET_JOBJ(effect->gobj), va_f32_1);
        }
        break;
    case 0x4C6:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(
            0x1F40, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4C7:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(
            0x1F41, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4C8:
        ret_obj =
            efLib_Create_Attach_Scale(0x1F42, gobj, va_arg(vlist, HSD_JObj*));
        effect = ret_obj;
        if (effect != NULL) {
            Effect_SetFacingDir(effect, *va_arg(vlist, f32*));
            jobj_2 = GET_JOBJ(effect->gobj);
            HSD_JObjAnimAll(jobj_2);
        }
        break;
    case 0x4C9:
        ret_obj =
            efLib_Create_Attach_Scale(0x1F43, gobj, va_arg(vlist, HSD_JObj*));
        effect = ret_obj;
        if (effect != NULL) {
            Effect_SetFacingDir(effect, *va_arg(vlist, f32*));
            jobj_2 = GET_JOBJ(effect->gobj);
            HSD_JObjAnimAll(jobj_2);
        }
        break;
    case 0x4CA:
        ret_obj =
            efLib_Create_Attach_Scale(0x1F44, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4CB:
        ret_obj =
            efLib_Create_Attach_Scale(0x1F45, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4CC:
        ret_obj = efLib_Create_Attach_Pos(0x1F46U, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            HSD_JObjGetScale(jobj_1 = gobj->hsd_obj, &scale);
            HSD_JObjSetScale(GET_JOBJ(effect->gobj), &scale);
            effect->update = efLib_Cb_SetRotY_FromFighterDir;
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
        EF_Effect* cur;
        EF_Effect* tail;
        s32 i;
        f32 scale_f32;
        scale_f32 = 1.0f;
        va_vec3 = va_arg(vlist, Vec3*);
        translate = *va_vec3;
        if (gfx_id == 0x4CF) {
            scale_f32 = *va_arg(vlist, f32*);
        }
        for (i = 0; i < 12; i++) {
            rand_f32 = HSD_Randf();
            if (rand_f32 < 0.5f) {
                if (gfx_id == 0x4D0) {
                    cur = efLib_Create_Attach_Pos(0x1CU, gobj, &translate);
                } else {
                    cur = efLib_Create_Attach_Pos(0x1EU, gobj, &translate);
                }
            } else if (gfx_id == 0x4D0) {
                cur = efLib_Create_Attach_Pos(0x1DU, gobj, &translate);
            } else {
                cur = efLib_Create_Attach_Pos(0x1FU, gobj, &translate);
            }
            if (cur == NULL) {
                break;
            }
            cur->update = efLib_Cb_SetOffset_FromParams;
            cur->lifetime = 0x32;
            rand_rot_y = M_TAU * HSD_Randf();
            rand_rot_x = M_TAU * HSD_Randf();
            jobj_1 = GET_JOBJ(cur->gobj);
            HSD_JObjSetScaleX(jobj_1, scale_f32);
            jobj_1 = GET_JOBJ(cur->gobj);
            HSD_JObjSetScaleY(jobj_1, scale_f32);
            jobj_1 = GET_JOBJ(cur->gobj);
            HSD_JObjSetScaleZ(jobj_1, scale_f32);
            jobj_1 = GET_JOBJ(cur->gobj);
            HSD_JObjSetRotationY(jobj_1, rand_rot_y);
            jobj_1 = GET_JOBJ(cur->gobj);
            HSD_JObjSetRotationX(jobj_1, rand_rot_x);
            rand_param_x = sinf(rand_rot_y);
            {
                f32 tmp = 2.0f * cosf(rand_rot_x);
                cur->params.x = tmp * rand_param_x;
            }
            cur->params.y = 2.0f * sinf(rand_rot_x);
            rand_param_y = cosf(rand_rot_y);
            {
                f32 tmp = 2.0f * cosf(rand_rot_x);
                cur->params.z = tmp * rand_param_y;
            }
            if (i != 0) {
                tail->next = cur;
                tail = tail->next;
            } else {
                ret_obj = tail = cur;
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
        ret_obj =
            efLib_Create_Attach_Scale(0x2712, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4D5:
        ret_obj = hsd_8039EFAC(0, 0xB, 0x2AF8, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4D6:
        ret_obj =
            efLib_Create_Attach_Scale(0x2AF8, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4D7:
        ret_obj = hsd_8039EFAC(0, 0xB, 0x2AF9, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4D8: {
        HSD_Generator* generator = efLib_CreateGenerator_AddAppSRT(0x61U);
        if (generator != NULL) {
            va_vec3 = va_arg(vlist, Vec3*);
            psAppSRT = generator->appsrt;
            psAppSRT->translate = *va_vec3;
            HSD_JObjGetScale((jobj_2 = GET_JOBJ(gobj)), &scale);
            ret_obj = generator;
            generator->appsrt->scale.x = generator->appsrt->scale.y =
                generator->appsrt->scale.z = scale.y;
            generator->appsrt->rot.y = M_PI_2;
        }
        break;
    }
    case 0x4D9:
        ret_obj = efLib_Create_Attach_Pos(0x2EE0U, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            if (*va_arg(vlist, f32*) < 0.0f) {
                half_pi = -M_PI_2;
            } else {
                half_pi = M_PI_2;
            }
            va_f32_1 = half_pi;
            effect = ret_obj;
            jobj_2 = GET_JOBJ(effect->gobj);
            HSD_JObjSetRotationY(jobj_2, va_f32_1);
            HSD_JObjGetScale((jobj_2 = GET_JOBJ(gobj)), &scale);
            jobj_2 = GET_JOBJ(effect->gobj);
            HSD_JObjSetScale(jobj_2, &scale);
        }
        break;
    case 0x4DA: {
        EF_Effect* child;
        jobj_2 = va_arg(vlist, HSD_JObj*);
        ret_obj = efLib_Create_Attach_Scale(0x2EE1, gobj, jobj_2);
        if (ret_obj != NULL) {
            effect = ret_obj;
            child = efLib_Create_Attach_Scale(0x2EE2, gobj, jobj_2);
            effect->next = child;
            if (child != NULL) {
                effect->update = efLib_Cb_ftKp_SpecialHi;
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
    case 0x4E1: {
        HSD_JObj* cursor;
        ret_obj = efLib_Create(0x32C9, gobj);
        if (ret_obj != NULL) {
            effect = ret_obj;
            jobj_1 = va_arg(vlist, HSD_JObj*);
            effect->attach_jobj = jobj_1;
            effect->update = efLib_Cb_SetOffsetY_FromParamY;
            cursor = jobj_1;
            while (HSD_JObjGetParent(cursor) != NULL) {
                jobj_1 = HSD_JObjGetParent(cursor);
                cursor = jobj_1;
            }
            HSD_JObjGetScale(cursor, &scale);
            effect->params = *va_arg(vlist, Vec3*);
            effect->params.y *= scale.y;
        }
        break;
    }
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
        ret_obj =
            efLib_Create_AttachChild(0x36B0U, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4D1:
        ret_obj = hsd_8039EFAC(0, 0, 0x64, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4D2:
        ret_obj = efLib_Create_Attach_Pos(0x3A98U, gobj, va_arg(vlist, Vec3*));
        break;
    case 0x4D3:
        jobj_2 = va_arg(vlist, HSD_JObj*);
        ret_obj = efLib_CreateGenerator_Attach_AddAppSRT(0x172, jobj_2);
        if (ret_obj != NULL) {
            efLib_CreateGenerator_Attach_AddAppSRT(0x173, jobj_2);
        }
        break;
    case 0x4D4:
        ret_obj =
            efLib_CreateGenerator_Attach(0x11E, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4F1:
        ret_obj = efLib_CreateGenerator_AppSRT_SetFacingDir(0x3E80, vlist);
        break;
    case 0x4F2:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(
            0x3E80, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4F3:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(
            0x3E81, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4F4: {
        Vec3 effect_scale;

        ret_obj =
            efLib_Create_AttachChild(0x4268U, gobj, va_arg(vlist, HSD_JObj*));
        goto copy_gobj_scale;
    case 0x4F5:
        ret_obj =
            efLib_Create_AttachChild(0x4269U, gobj, va_arg(vlist, HSD_JObj*));
    copy_gobj_scale:
        if (ret_obj != NULL) {
            HSD_JObjGetScale((jobj_2 = GET_JOBJ(gobj)), &scale);
            effect = ret_obj;
            HSD_JObjGetScale(GET_JOBJ(effect->gobj), &effect_scale);
            jobj_2 = GET_JOBJ(effect->gobj);
            HSD_JObjSetScale(jobj_2, &scale);
        }
        break;
    }
    case 0x4F6:
        ret_obj =
            efLib_Create_Attach_Scale(0x426A, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4F7:
        ret_obj =
            efLib_Create_Attach_Scale(0x426B, gobj, va_arg(vlist, HSD_JObj*));
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
        ret_obj = efLib_Create_Attach_Scale(0x426D, gobj,
                                            GET_FIGHTER(gobj)->parts[1].joint);
        break;
    case 0x501:
        fp = GET_FIGHTER(gobj);
        ret_obj = efLib_Create_Attach_Scale(0x426E, gobj,
                                            GET_FIGHTER(gobj)->parts[1].joint);
        if (ret_obj != NULL) {
            effect = ret_obj;
            if (fp->facing_dir < 0.0f) {
                half_pi = -M_PI_2;
            } else {
                half_pi = M_PI_2;
            }
            va_f32_1 = half_pi;
            jobj_2 = GET_JOBJ(effect->gobj);
            HSD_JObjSetRotationY(jobj_2, va_f32_1);
            effect->attach_jobj = fp->parts[85].joint;
            effect->update = efLib_Cb_LifetimeEndSpawn;
            effect->lifetime = 6;
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
    case 0x504: {
        HSD_Generator* generator = efLib_CreateGenerator_AddAppSRT(0x6DU);
        if (generator != NULL) {
            va_vec3 = va_arg(vlist, Vec3*);
            psAppSRT = generator->appsrt;
            psAppSRT->translate = *va_vec3;
            HSD_JObjGetScale((jobj_2 = GET_JOBJ(gobj)), &scale);
            ret_obj = generator;
            generator->appsrt->scale.x = generator->appsrt->scale.y =
                generator->appsrt->scale.z = scale.y;
        }
        break;
    }
    case 0x505: {
        HSD_Generator* generator = efLib_CreateGenerator_AddAppSRT(0x79U);
        if (generator != NULL) {
            va_vec3 = va_arg(vlist, Vec3*);
            psAppSRT = generator->appsrt;
            psAppSRT->translate = *va_vec3;
            HSD_JObjGetScale((jobj_2 = gobj->hsd_obj), &scale);
            ret_obj = generator;
            generator->appsrt->scale.x = generator->appsrt->scale.y =
                generator->appsrt->scale.z = scale.y;
        }
        break;
    }
    case 0x506:
        ret_obj = efLib_CreateGenerator(0x4658U, va_arg(vlist, Vec3*));
        break;
    case 0x507:
        jobj_1 = va_arg(vlist, HSD_JObj*);
        ret_obj = efLib_Create_Attach(0x4650U, gobj, jobj_1);
        if (ret_obj != NULL) {
            effect = ret_obj;
            if (*va_arg(vlist, f32*) < 0.0f) {
                half_pi = -M_PI_2;
            } else {
                half_pi = M_PI_2;
            }
            va_f32_1 = half_pi;
            jobj_2 = GET_JOBJ(effect->gobj);
            HSD_JObjSetRotationY(jobj_2, va_f32_1);
        }
        hsd_8039EFAC(0, 0x12, 0x4650, jobj_1);
        break;
    case 0x508:
        ret_obj = efLib_CreateGenerator(0x4652U, va_arg(vlist, Vec3*));
        break;
    case 0x509:
        ret_obj =
            efLib_Create_Attach_Scale(0x4651, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            effect->update = efLib_Cb_ftLg_SpecialLw;
        }
        break;
    case 0x50A:
        ret_obj = hsd_8039EFAC(0, 0, 0x5F, va_arg(vlist, HSD_JObj*));
        break;
    case 0x50B:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(
            0x4A38, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            effect->next = efLib_Create_Attach_Scale_FacingDir(
                0x4A39, gobj, va_arg(vlist, HSD_JObj*));
        }
        break;
    case 0x50C:
        ret_obj = efLib_Create_Attach(0x4A3AU, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            effect->params.z = *va_arg(vlist, f32*);
            effect->update = efLib_Cb_SetRotYZ_FromParamZ_FighterDir;
        }
        break;
    case 0x50D:
        ret_obj = efLib_Create_Attach(0x4A3BU, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x50E:
        ret_obj =
            efLib_Create_Attach_Scale(0x4A3C, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            if (*va_arg(vlist, f32*) < 0.0f) {
                half_pi = -M_PI_2;
            } else {
                half_pi = M_PI_2;
            }
            va_f32_1 = half_pi;
            jobj_2 = GET_JOBJ(effect->gobj);
            HSD_JObjSetRotationY(jobj_2, va_f32_1);
        }
        break;
    case 0x50F:
        ret_obj =
            efLib_Create_Attach_Scale(0x4A3D, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            if (*va_arg(vlist, f32*) < 0.0f) {
                half_pi = -M_PI_2;
            } else {
                half_pi = M_PI_2;
            }
            va_f32_1 = half_pi;
            jobj_2 = GET_JOBJ(effect->gobj);
            HSD_JObjSetRotationY(jobj_2, va_f32_1);
        }
        break;
    case 0x510:
        ret_obj = efLib_CreateGenerator_AppSRT_SetFacingDir(0xBF68, vlist);
        break;
    case 0x511:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(
            0xBF68, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x512:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(
            0xBF69, gobj, va_arg(vlist, HSD_JObj*));
        break;
    }
    while (efLib_AnimCount != 0) {
        cnt_2 = efLib_AnimCount - 1;
        efLib_AnimCount = cnt_2;
        HSD_JObjAnimAll(efLib_AnimQueue[cnt_2]);
    }

    va_end(vlist);
    return ret_obj;
}
