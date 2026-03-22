#include "efalt.h"

#include "eflib.h"
#include "types.h"

#include "baselib/gobj.h"
#include "baselib/jobj.h"
#include "baselib/particle.h"

#include "MSL/math.h"

#define EFALT_VA_ARG(t) (*((t*) __va_arg(vlist_arg, _var_arg_typeof(t))))

extern volatile u32 efLib_LoadKind;
extern volatile s32 efLib_AnimCount;

// There seems to be multiple spawners, one dispatcher

void* efAlt_Spawn(s32 gfx_id, HSD_GObj* gobj, va_list vlist)
{
    EF_Effect* effect;
    HSD_JObj* jobj;
    f32 rotate_y;
    Vec3 scale;
    f32* value_ptr;
    void* ret_obj;
    void* vlist_arg;

    vlist_arg = vlist;
    ret_obj = NULL;
    efLib_LoadKind = EF_LOADKIND_SYNC;
    PAD_STACK(80);

    switch (gfx_id) {
    case 0x479:
        ret_obj = efLib_CreateGenerator(0x3F2, EFALT_VA_ARG(Vec3*));
        break;
    case 0x47A: {
        f64 temp_d;
        f32 rotate_y_2;

        jobj = EFALT_VA_ARG(HSD_JObj*);
        ret_obj = efLib_Create_Attach(0x3E8U, gobj, jobj);
        if (ret_obj != NULL) {
            value_ptr = EFALT_VA_ARG(f32*);
            if (*value_ptr < 0.0f) {
                temp_d = -M_PI_2;
            } else {
                temp_d = M_PI_2;
            }
            rotate_y_2 = temp_d;
            HSD_JObjSetRotationY(GET_JOBJ(((EF_Effect*) ret_obj)->gobj),
                                 rotate_y_2);
        }
        hsd_8039EFAC(0, 1, 0x3E9, jobj);
        break;
    }
    case 0x47B:
        ret_obj = efLib_CreateGenerator(0x3EB, EFALT_VA_ARG(Vec3*));
        break;
    case 0x47C:
        ret_obj = efLib_Create_Attach_Scale(0x3E9U, gobj, EFALT_VA_ARG(HSD_JObj*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->update = efLib_Cb_ftMr_SpecialLw;
        }
        break;
    case 0x47D:
        ret_obj = hsd_8039EFAC(0, 1, 0x3F0, EFALT_VA_ARG(HSD_JObj*));
        break;
    case 0x47E:
        ret_obj = hsd_8039EFAC(0, 1, 0x3F1, EFALT_VA_ARG(HSD_JObj*));
        break;
    case 0x47F:
        ret_obj = hsd_8039EFAC(0, 2, 0x7D4, EFALT_VA_ARG(HSD_JObj*));
        break;
    case 0x480:
        ret_obj = hsd_8039EFAC(0, 2, 0x7D2, EFALT_VA_ARG(HSD_JObj*));
        break;
    case 0x481:
        ret_obj = hsd_8039EFAC(0, 2, 0x7D3, EFALT_VA_ARG(HSD_JObj*));
        break;
    case 0x482:
        ret_obj = efLib_Create_Attach(0x7D0U, gobj, EFALT_VA_ARG(HSD_JObj*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->update = efLib_Cb_SetScaleRotY_FromFighter;
        }
        break;
    case 0x483:
        ret_obj = efLib_CreateGenerator(0x7D7, EFALT_VA_ARG(Vec3*));
        break;
    case 0x484:
        ret_obj = hsd_8039EFAC(0, 2, 0x7DB, EFALT_VA_ARG(HSD_JObj*));
        break;
    case 0x485:
        ret_obj = hsd_8039EFAC(0, 2, 0x7DE, EFALT_VA_ARG(HSD_JObj*));
        break;
    case 0x486: {
        f64 temp_d;
        f32 rotate_y_2;

        ret_obj = efLib_Create_Attach_Pos(0x7D1U, gobj, EFALT_VA_ARG(Vec3*));
        if (ret_obj != NULL) {
            value_ptr = EFALT_VA_ARG(f32*);
            if (*value_ptr < 0.0f) {
                temp_d = -M_PI_2;
            } else {
                temp_d = M_PI_2;
            }
            rotate_y_2 = temp_d;
            HSD_JObjSetRotationY(GET_JOBJ(((EF_Effect*) ret_obj)->gobj),
                                 rotate_y_2);
        }
        break;
    }
    case 0x487:
        ret_obj = efLib_Create_AttachChild_Scale(0x7D2U, gobj, EFALT_VA_ARG(HSD_JObj*));
        break;
    case 0x488:
        ret_obj = efLib_Create_Attach_Scale(0xBB8U, gobj, EFALT_VA_ARG(HSD_JObj*));
        break;
    case 0x489:
        ret_obj = efLib_Create_Attach_Scale(0xBB9U, gobj, EFALT_VA_ARG(HSD_JObj*));
        break;
    case 0x48A:
        ret_obj = efLib_Create_Attach_Scale(0xBBAU, gobj, EFALT_VA_ARG(HSD_JObj*));
        break;
    case 0x48B:
        ret_obj = efLib_Create_Attach(0xBBBU, gobj, EFALT_VA_ARG(HSD_JObj*));
        break;
    case 0x48C:
        ret_obj = efLib_Create_Attach(0xBBCU, gobj, EFALT_VA_ARG(HSD_JObj*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->update = efLib_Cb_SetRotYZ_FromFighter;
        }
        break;
    case 0x48D:
        ret_obj = efLib_CreateGenerator_AppSRT_SetFacingDir(0xBC0, vlist_arg);
        break;
    case 0x48E: {
        ret_obj = efLib_Create_Attach_Pos(0xBBDU, gobj, EFALT_VA_ARG(Vec3*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            HSD_JObjSetRotationY(GET_JOBJ(effect->gobj), M_PI_2);
            HSD_JObjSetRotationZ(GET_JOBJ(effect->gobj), *EFALT_VA_ARG(f32*));
        }
        break;
    }
    case 0x48F: {
        ret_obj = efLib_Create_Attach_Scale_FacingDir(0xFA0U, gobj, EFALT_VA_ARG(HSD_JObj*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->next =
                (void*) efLib_Create_Attach_Scale_FacingDir(0xFA1U, gobj, EFALT_VA_ARG(HSD_JObj*));
        }
        break;
    }
    case 0x490: {
        ret_obj = efLib_Create_Attach(0xFA2U, gobj, EFALT_VA_ARG(HSD_JObj*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->params.z = *EFALT_VA_ARG(f32*);
            ((EF_Effect*) ret_obj)->update = efLib_Cb_SetRotYZ_FromParamZ_FighterDir;
        }
        break;
    }
    case 0x491:
        ret_obj = efLib_Create_Attach(0xFA4U, gobj, EFALT_VA_ARG(HSD_JObj*));
        break;
    case 0x492: {
        f64 temp_d;
        f32 rotate_y_2;

        ret_obj = efLib_Create_Attach_Scale(0xFA3U, gobj, EFALT_VA_ARG(HSD_JObj*));
        if (ret_obj != NULL) {
            value_ptr = EFALT_VA_ARG(f32*);
            if (*value_ptr < 0.0f) {
                temp_d = -M_PI_2;
            } else {
                temp_d = M_PI_2;
            }
            rotate_y_2 = temp_d;
            HSD_JObjSetRotationY(GET_JOBJ(((EF_Effect*) ret_obj)->gobj),
                                 rotate_y_2);
        }
        break;
    }
    case 0x493: {
        f64 temp_d;
        f32 rotate_y_2;

        ret_obj = efLib_Create_Attach_Scale(0xFA5U, gobj, EFALT_VA_ARG(HSD_JObj*));
        if (ret_obj != NULL) {
            value_ptr = EFALT_VA_ARG(f32*);
            if (*value_ptr < 0.0f) {
                temp_d = -M_PI_2;
            } else {
                temp_d = M_PI_2;
            }
            rotate_y_2 = temp_d;
            HSD_JObjSetRotationY(GET_JOBJ(((EF_Effect*) ret_obj)->gobj),
                                 rotate_y_2);
        }
        break;
    }
    case 0x494: {
        void* user_data;
        HSD_JObj** jobj_ptr;
        HSD_JObj* jobj;
        HSD_JObj* jobj_2;
        EF_Effect* effect_1;
        EF_Effect* effect_2;
        EF_Effect* next_eff;
        u16 effect_flags;

        effect_flags = 0x41;
        user_data = gobj->user_data;
        jobj_ptr = *(HSD_JObj***) ((u8*) user_data + 0x5E8);
        jobj = jobj_ptr[0xB0];
        jobj_2 = jobj_ptr[4];
        ret_obj = efLib_Create_AttachChild(0x1388U, gobj, jobj);
        if (ret_obj != NULL) {
            effect_1 = ret_obj;
            effect_1->update = efLib_Cb_SetRotYAndTransition;
            effect_1->lifetime = effect_flags;
            effect_1->user_data = NULL;
            next_eff = (void*) efLib_Create_Attach(0x1389U, gobj, jobj);
            effect_1->next = next_eff;
            if (next_eff != NULL) {
                effect_2 = (void*) effect_1->next;
                effect_2->update = efLib_Cb_SetRotYAndTransition;
                effect_2->lifetime = effect_flags;
                effect_2->user_data = user_data;
                next_eff = (void*) efLib_Create_Attach(0x138AU, gobj, jobj_2);
                effect_2->next = next_eff;
                if (next_eff != NULL) {
                    effect_1 = (void*) effect_2->next;
                    effect_1->update = efLib_Cb_SetRotYAndTransition;
                    effect_1->lifetime = effect_flags;
                    effect_1->user_data = user_data;
                }
            }
        }
        break;
    }
    case 0x495: {
        f64 temp_d;
        f32 rotate_y_2;

        ret_obj = efLib_Create_Attach_Scale(0x138BU, gobj, EFALT_VA_ARG(HSD_JObj*));
        if (ret_obj != NULL) {
            value_ptr = EFALT_VA_ARG(f32*);
            if (*value_ptr < 0.0f) {
                temp_d = -M_PI_2;
            } else {
                temp_d = M_PI_2;
            }
            rotate_y_2 = temp_d;
            HSD_JObjSetRotationY(GET_JOBJ(((EF_Effect*) ret_obj)->gobj),
                                 rotate_y_2);
        }
        break;
    }
    case 0x496:
        ret_obj = efLib_Create_Attach(0x138CU, gobj, EFALT_VA_ARG(HSD_JObj*));
        break;
    case 0x497:
        ret_obj = efLib_Create_Attach(0x138DU, gobj, EFALT_VA_ARG(HSD_JObj*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->update = efLib_Cb_SetRotY_FromFighterDir;
        }
        break;
    case 0x498:
        ret_obj = efLib_Create_AttachChild(0x138EU, gobj, EFALT_VA_ARG(HSD_JObj*));
        break;
    case 0x499:
        ret_obj = efLib_Create_AttachChild(0x138FU, gobj, EFALT_VA_ARG(HSD_JObj*));
        break;
    case 0x49A:
        ret_obj = efLib_CreateGenerator_AppSRT_SetFacingDir(0x138B, vlist_arg);
        break;
    case 0x49B:
        ret_obj = hsd_8039EFAC(0, 5, 0x138F, EFALT_VA_ARG(HSD_JObj*));
        break;
    case 0x49C:
        ret_obj = hsd_8039EFAC(0, 5, 0x1395, EFALT_VA_ARG(HSD_JObj*));
        break;
    case 0x49D: {
        HSD_JObj* jobj;

        ret_obj = efLib_Create_Attach_Pos(0x1390U, gobj, EFALT_VA_ARG(Vec3*));
        if (ret_obj != NULL) {
            HSD_JObj* gobj_jobj = GET_JOBJ(gobj);

            jobj = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetScaleX(jobj, HSD_JObjGetScaleY(gobj_jobj));
            HSD_JObjSetScaleY(jobj, HSD_JObjGetScaleY(gobj_jobj));
            HSD_JObjSetScaleZ(jobj, HSD_JObjGetScaleY(gobj_jobj));
            HSD_JObjSetTranslateZ(HSD_JObjGetChild(jobj),
                                  HSD_JObjGetTranslationZ(jobj) - 6.0f);
            if (*EFALT_VA_ARG(f32*) < 0.0f) {
                HSD_JObjSetRotationY(jobj, -M_PI_2);
                HSD_JObjSetRotationZ(jobj, -*EFALT_VA_ARG(f32*));
            } else {
                HSD_JObjSetRotationY(jobj, M_PI_2);
                HSD_JObjSetRotationZ(jobj, *EFALT_VA_ARG(f32*));
            }
            ((EF_Effect*) ret_obj)->update = efLib_Cb_SetJObjOffsetZ;
        }
        break;
    }
    case 0x49E:
        ret_obj = efLib_CreateGenerator(0x206, EFALT_VA_ARG(Vec3*));
        break;
    case 0x49F: {
        f64 temp_d;
        f32 rotate_y_2;
        HSD_JObj* jobj_2;

        jobj_2 = EFALT_VA_ARG(HSD_JObj*);
        ret_obj = efLib_Create_Attach(0x7D00U, gobj, jobj_2);
        if (ret_obj != NULL) {
            effect = ret_obj;
            value_ptr = EFALT_VA_ARG(f32*);
            if (*value_ptr < 0.0f) {
                temp_d = -M_PI_2;
            } else {
                temp_d = M_PI_2;
            }
            rotate_y_2 = temp_d;
            HSD_JObjSetRotationY(GET_JOBJ(effect->gobj), rotate_y_2);
        }
        hsd_8039EFAC(0, 0x20, 0x7D00, jobj_2);
        break;
    }
    case 0x4A0:
        ret_obj = efLib_CreateGenerator(0x7D02, EFALT_VA_ARG(Vec3*));
        break;
    case 0x4A5:
        ret_obj = efLib_CreateGenerator_Attach_Scale(0xA028, vlist_arg, gobj);
        break;
    case 0x4A6:
        ret_obj = efLib_CreateGenerator_Attach_Scale(0xA029, vlist_arg, gobj);
        break;
    case 0x4A7:
        ret_obj = efLib_CreateGenerator_Attach_Scale(0xA02A, vlist_arg, gobj);
        break;
    case 0x4A8:
        ret_obj = efLib_CreateGenerator_Attach_Scale(0xA02B, vlist_arg, gobj);
        break;
    case 0x4A1:
        jobj = EFALT_VA_ARG(HSD_JObj*);
        ret_obj = hsd_8039EFAC(0, 0x22, 0x84D4, jobj);
        break;
    case 0x4A2:
        jobj = EFALT_VA_ARG(HSD_JObj*);
        ret_obj = hsd_8039EFAC(0, 0x22, 0x84D2, jobj);
        break;
    case 0x4A3:
        jobj = EFALT_VA_ARG(HSD_JObj*);
        ret_obj = hsd_8039EFAC(0, 0x22, 0x84D3, jobj);
        break;
    case 0x4A4: {
        f64 temp_d;
        f32 rotate_y_2;

        ret_obj = efLib_Create_Attach_Pos(0x84D0U, gobj, EFALT_VA_ARG(Vec3*));
        if (ret_obj != NULL) {
            value_ptr = EFALT_VA_ARG(f32*);
            if (*value_ptr < 0.0f) {
                temp_d = -M_PI_2;
            } else {
                temp_d = M_PI_2;
            }
            rotate_y_2 = temp_d;
            HSD_JObjSetRotationY(GET_JOBJ(((EF_Effect*) ret_obj)->gobj),
                                 rotate_y_2);
        }
        break;
    }
    case 0x4A9: {
        f64 temp_d;
        f32 rotate_y_2;

        ret_obj = efLib_Create_Attach_Scale(0x9858U, gobj, EFALT_VA_ARG(HSD_JObj*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            value_ptr = EFALT_VA_ARG(f32*);
            if (*value_ptr < 0.0f) {
                temp_d = -M_PI_2;
            } else {
                temp_d = M_PI_2;
            }
            rotate_y_2 = temp_d;
            HSD_JObjSetRotationY(GET_JOBJ(effect->gobj), rotate_y_2);
            HSD_JObjAnimAll(GET_JOBJ(effect->gobj));
        }
        break;
    }
    case 0x4AA: {
        f64 temp_d;
        f32 rotate_y_2;

        ret_obj = efLib_Create_Attach_Scale(0x9859U, gobj, EFALT_VA_ARG(HSD_JObj*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            value_ptr = EFALT_VA_ARG(f32*);
            if (*value_ptr < 0.0f) {
                temp_d = -M_PI_2;
            } else {
                temp_d = M_PI_2;
            }
            rotate_y_2 = temp_d;
            HSD_JObjSetRotationY(GET_JOBJ(effect->gobj), rotate_y_2);
            HSD_JObjAnimAll(GET_JOBJ(effect->gobj));
        }
        break;
    }
    case 0x4AB: {
        ret_obj = efLib_Create_Attach_Scale_FacingDir(0x9471U, gobj, EFALT_VA_ARG(HSD_JObj*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->next =
                (void*) efLib_Create_Attach_Scale_FacingDir(0x9470U, gobj, EFALT_VA_ARG(HSD_JObj*));
        }
        break;
    }
    case 0x4AC: {
        ret_obj = efLib_Create_Attach_Pos(0x80E8U, gobj, EFALT_VA_ARG(Vec3*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            HSD_JObjSetRotationY(GET_JOBJ(effect->gobj), M_PI_2);
            HSD_JObjSetRotationZ(GET_JOBJ(effect->gobj), *EFALT_VA_ARG(f32*));
        }
        break;
    }
    case 0x4AD:
        jobj = EFALT_VA_ARG(HSD_JObj*);
        ret_obj = hsd_8039EFAC(0, 0x24, 0x8CA0, jobj);
        break;
    case 0x4AE:
        jobj = EFALT_VA_ARG(HSD_JObj*);
        ret_obj = hsd_8039EFAC(0, 0x2E, 0xB3B0, jobj);
        break;
    case 0x4AF:
        jobj = EFALT_VA_ARG(HSD_JObj*);
        ret_obj = hsd_8039EFAC(0, 0x2E, 0xB3B1, jobj);
        break;
    case 0x4B0:
        ret_obj = efLib_CreateGenerator_AppSRT_SetFacingDir(0xB3B6, vlist_arg);
        break;
    case 0x4B1: {
        HSD_JObj* input_jobj;
        f64 temp_d;
        f32 rotate_y_2;

        input_jobj = EFALT_VA_ARG(HSD_JObj*);
        ret_obj = efLib_Create_Attach(0x9088U, gobj, input_jobj);
        if (ret_obj != NULL) {
            value_ptr = EFALT_VA_ARG(f32*);
            if (*value_ptr < 0.0f) {
                temp_d = -M_PI_2;
            } else {
                temp_d = M_PI_2;
            }
            effect = ret_obj;
            rotate_y_2 = temp_d;
            HSD_JObjSetRotationY(GET_JOBJ(effect->gobj), rotate_y_2);
        }
        hsd_8039EFAC(0, 0x25, 0x9088, input_jobj);
        break;
    }
    case 0x4B2:
        ret_obj = efLib_CreateGenerator(0x908A, EFALT_VA_ARG(Vec3*));
        break;
    case 0x4B3: {
        ret_obj = efLib_Create_Attach_Scale_FacingDir(0xB799U, gobj, EFALT_VA_ARG(HSD_JObj*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->next =
                (void*) efLib_Create_Attach_Scale_FacingDir(0xB798U, gobj, EFALT_VA_ARG(HSD_JObj*));
        }
        break;
    }
    case 0x4B4:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(0x4E20U, gobj, EFALT_VA_ARG(HSD_JObj*));
        break;
    case 0x4B5:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(0x4E21U, gobj, EFALT_VA_ARG(HSD_JObj*));
        break;
    case 0x4B6:
        ret_obj = efLib_Create_AttachChild(0x5208U, gobj, EFALT_VA_ARG(HSD_JObj*));
        goto lbl_4B6_4B7_shared;
    case 0x4B7:
        ret_obj = efLib_Create_AttachChild(0x5209U, gobj, EFALT_VA_ARG(HSD_JObj*));
lbl_4B6_4B7_shared:
    if (ret_obj != NULL) {
        effect = ret_obj;
        HSD_JObjGetScale(GET_JOBJ(gobj), &scale);
        if (GET_JOBJ(effect->gobj) == NULL) {
                __assert("jobj.h", 823, "jobj");
            }
            HSD_JObjSetScale(GET_JOBJ(effect->gobj), &scale);
        }
        break;
    case 0x4B8:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(0xBB80U, gobj, EFALT_VA_ARG(HSD_JObj*));
        break;
    case 0x4B9:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(0xBB81U, gobj, EFALT_VA_ARG(HSD_JObj*));
        break;
    }

    while (efLib_AnimCount != 0) {
        s32 cnt;

        cnt = efLib_AnimCount - 1;
        efLib_AnimCount = cnt;
        // horrible. its actually just efLib_AnimQueue[cnt]
        HSD_JObjAnimAll(((EF_ParamEntry*)(((u32*)efLib_AnimQueue) + cnt))->gobj);
    }

    return ret_obj;
}
