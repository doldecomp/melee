#include "efalt.h"

#include <math.h>
#include <placeholder.h>

#include "efdata.h"
#include "eflib.h"
#include "inlines.h"
#include "types.h"
#include <melee/ft/types.h>
#include <sysdolphin/baselib/generator.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/jobj.h>

// There seems to be multiple spawners, one dispatcher

void* efAlt_Spawn(s32 gfx_id, HSD_GObj* gobj, va_list vlist)
{
    EF_Effect* effect;
    HSD_JObj* jobj;
    f32 rotate_y;
    Vec3 scale;
    void* ret_obj;

    ret_obj = NULL;
    efLib_LoadKind = EF_LOADKIND_SYNC;
    PAD_STACK(24);

    switch (gfx_id) {
    case 0x479:
        ret_obj = efLib_CreateGenerator(0x3F2, va_arg(vlist, Vec3*));
        break;
    case 0x47A: {
        jobj = va_arg(vlist, HSD_JObj*);
        ret_obj = efLib_Create_Attach(0x3E8U, gobj, jobj);
        if (ret_obj != NULL) {
            effect = ret_obj;
            Effect_SetFacingDir(effect, *va_arg(vlist, f32*));
        }
        hsd_8039EFAC(0, 1, 0x3E9, jobj);
        break;
    }
    case 0x47B:
        ret_obj = efLib_CreateGenerator(0x3EB, va_arg(vlist, Vec3*));
        break;
    case 0x47C:
        ret_obj =
            efLib_Create_Attach_Scale(0x3E9U, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            effect->update = efLib_Cb_ftMr_SpecialLw;
        }
        break;
    case 0x47D:
        ret_obj = hsd_8039EFAC(0, 1, 0x3F0, va_arg(vlist, HSD_JObj*));
        break;
    case 0x47E:
        ret_obj = hsd_8039EFAC(0, 1, 0x3F1, va_arg(vlist, HSD_JObj*));
        break;
    case 0x47F:
        ret_obj = hsd_8039EFAC(0, 2, 0x7D4, va_arg(vlist, HSD_JObj*));
        break;
    case 0x480:
        ret_obj = hsd_8039EFAC(0, 2, 0x7D2, va_arg(vlist, HSD_JObj*));
        break;
    case 0x481:
        ret_obj = hsd_8039EFAC(0, 2, 0x7D3, va_arg(vlist, HSD_JObj*));
        break;
    case 0x482:
        ret_obj = efLib_Create_Attach(0x7D0U, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            effect->update = efLib_Cb_SetScaleRotY_FromFighter;
        }
        break;
    case 0x483:
        ret_obj = efLib_CreateGenerator(0x7D7, va_arg(vlist, Vec3*));
        break;
    case 0x484:
        ret_obj = hsd_8039EFAC(0, 2, 0x7DB, va_arg(vlist, HSD_JObj*));
        break;
    case 0x485:
        ret_obj = hsd_8039EFAC(0, 2, 0x7DE, va_arg(vlist, HSD_JObj*));
        break;
    case 0x486: {
        ret_obj = efLib_Create_Attach_Pos(0x7D1U, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            Effect_SetFacingDir(effect, *va_arg(vlist, f32*));
        }
        break;
    }
    case 0x487:
        ret_obj = efLib_Create_AttachChild_Scale(0x7D2U, gobj,
                                                 va_arg(vlist, HSD_JObj*));
        break;
    case 0x488:
        ret_obj =
            efLib_Create_Attach_Scale(0xBB8U, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x489:
        ret_obj =
            efLib_Create_Attach_Scale(0xBB9U, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x48A:
        ret_obj =
            efLib_Create_Attach_Scale(0xBBAU, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x48B:
        ret_obj = efLib_Create_Attach(0xBBBU, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x48C:
        ret_obj = efLib_Create_Attach(0xBBCU, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            effect->update = efLib_Cb_SetRotYZ_FromFighter;
        }
        break;
    case 0x48D:
        ret_obj = efLib_CreateGenerator_AppSRT_SetFacingDir(0xBC0, vlist);
        break;
    case 0x48E: {
        ret_obj = efLib_Create_Attach_Pos(0xBBDU, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            HSD_JObjSetRotationY(GET_JOBJ(effect->gobj), M_PI_2);
            HSD_JObjSetRotationZ(GET_JOBJ(effect->gobj), *va_arg(vlist, f32*));
        }
        break;
    }
    case 0x48F: {
        ret_obj = efLib_Create_Attach_Scale_FacingDir(
            0xFA0U, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            effect->next = efLib_Create_Attach_Scale_FacingDir(
                0xFA1U, gobj, va_arg(vlist, HSD_JObj*));
        }
        break;
    }
    case 0x490: {
        ret_obj = efLib_Create_Attach(0xFA2U, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            effect->params.z = *va_arg(vlist, f32*);
            effect->update = efLib_Cb_SetRotYZ_FromParamZ_FighterDir;
        }
        break;
    }
    case 0x491:
        ret_obj = efLib_Create_Attach(0xFA4U, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x492: {
        ret_obj =
            efLib_Create_Attach_Scale(0xFA3U, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            Effect_SetFacingDir(effect, *va_arg(vlist, f32*));
        }
        break;
    }
    case 0x493: {
        ret_obj =
            efLib_Create_Attach_Scale(0xFA5U, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            Effect_SetFacingDir(effect, *va_arg(vlist, f32*));
        }
        break;
    }
    case 0x494: {
        Fighter* fp;
        HSD_JObj* r3rd_joint;
        HSD_JObj* trans_joint;
        EF_Effect* effect_1;
        EF_Effect* effect_2;
        EF_Effect* next_eff;
        u16 lifetime;

        lifetime = 0x41;
        fp = gobj->user_data;
        r3rd_joint = fp->parts[FtPart_R3rdNa].joint;
        trans_joint = fp->parts[FtPart_TransN].joint;
        ret_obj = efLib_Create_AttachChild(0x1388, gobj, r3rd_joint);
        if (ret_obj != NULL) {
            effect_1 = ret_obj;
            effect_1->update = efLib_Cb_SetRotYAndTransition;
            effect_1->lifetime = lifetime;
            effect_1->user_data = NULL;
            next_eff = efLib_Create_Attach(0x1389, gobj, r3rd_joint);
            effect_1->next = next_eff;
            if (next_eff != NULL) {
                effect_2 = effect_1->next;
                effect_2->update = efLib_Cb_SetRotYAndTransition;
                effect_2->lifetime = lifetime;
                effect_2->user_data = fp;
                next_eff = efLib_Create_Attach(0x138A, gobj, trans_joint);
                effect_2->next = next_eff;
                if (next_eff != NULL) {
                    effect_1 = effect_2->next;
                    effect_1->update = efLib_Cb_SetRotYAndTransition;
                    effect_1->lifetime = lifetime;
                    effect_1->user_data = fp;
                }
            }
        }
        break;
    }
    case 0x495: {
        ret_obj =
            efLib_Create_Attach_Scale(0x138BU, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            Effect_SetFacingDir(effect, *va_arg(vlist, f32*));
        }
        break;
    }
    case 0x496:
        ret_obj = efLib_Create_Attach(0x138CU, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x497:
        ret_obj = efLib_Create_Attach(0x138DU, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            effect->update = efLib_Cb_SetRotY_FromFighterDir;
        }
        break;
    case 0x498:
        ret_obj =
            efLib_Create_AttachChild(0x138EU, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x499:
        ret_obj =
            efLib_Create_AttachChild(0x138FU, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x49A:
        ret_obj = efLib_CreateGenerator_AppSRT_SetFacingDir(0x138B, vlist);
        break;
    case 0x49B:
        ret_obj = hsd_8039EFAC(0, 5, 0x138F, va_arg(vlist, HSD_JObj*));
        break;
    case 0x49C:
        ret_obj = hsd_8039EFAC(0, 5, 0x1395, va_arg(vlist, HSD_JObj*));
        break;
    case 0x49D: {
        HSD_JObj* jobj;

        ret_obj = efLib_Create_Attach_Pos(0x1390U, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            HSD_JObj* gobj_jobj = GET_JOBJ(gobj);

            effect = ret_obj;

            jobj = GET_JOBJ(effect->gobj);
            HSD_JObjSetScaleX(jobj, HSD_JObjGetScaleY(gobj_jobj));
            HSD_JObjSetScaleY(jobj, HSD_JObjGetScaleY(gobj_jobj));
            HSD_JObjSetScaleZ(jobj, HSD_JObjGetScaleY(gobj_jobj));
            HSD_JObjSetTranslateZ(HSD_JObjGetChild(jobj),
                                  HSD_JObjGetTranslationZ(jobj) - 6.0f);
            if (*va_arg(vlist, f32*) < 0.0f) {
                HSD_JObjSetRotationY(jobj, -M_PI_2);
                HSD_JObjSetRotationZ(jobj, -*va_arg(vlist, f32*));
            } else {
                HSD_JObjSetRotationY(jobj, M_PI_2);
                HSD_JObjSetRotationZ(jobj, *va_arg(vlist, f32*));
            }
            effect->update = efLib_Cb_SetJObjOffsetZ;
        }
        break;
    }
    case 0x49E:
        ret_obj = efLib_CreateGenerator(0x206, va_arg(vlist, Vec3*));
        break;
    case 0x49F: {
        HSD_JObj* jobj_2;

        jobj_2 = va_arg(vlist, HSD_JObj*);
        ret_obj = efLib_Create_Attach(0x7D00U, gobj, jobj_2);
        if (ret_obj != NULL) {
            effect = ret_obj;
            Effect_SetFacingDir(effect, *va_arg(vlist, f32*));
        }
        hsd_8039EFAC(0, 0x20, 0x7D00, jobj_2);
        break;
    }
    case 0x4A0:
        ret_obj = efLib_CreateGenerator(0x7D02, va_arg(vlist, Vec3*));
        break;
    case 0x4A5:
        ret_obj = efLib_CreateGenerator_Attach_Scale(0xA028, vlist, gobj);
        break;
    case 0x4A6:
        ret_obj = efLib_CreateGenerator_Attach_Scale(0xA029, vlist, gobj);
        break;
    case 0x4A7:
        ret_obj = efLib_CreateGenerator_Attach_Scale(0xA02A, vlist, gobj);
        break;
    case 0x4A8:
        ret_obj = efLib_CreateGenerator_Attach_Scale(0xA02B, vlist, gobj);
        break;
    case 0x4A1:
        jobj = va_arg(vlist, HSD_JObj*);
        ret_obj = hsd_8039EFAC(0, 0x22, 0x84D4, jobj);
        break;
    case 0x4A2:
        jobj = va_arg(vlist, HSD_JObj*);
        ret_obj = hsd_8039EFAC(0, 0x22, 0x84D2, jobj);
        break;
    case 0x4A3:
        jobj = va_arg(vlist, HSD_JObj*);
        ret_obj = hsd_8039EFAC(0, 0x22, 0x84D3, jobj);
        break;
    case 0x4A4: {
        ret_obj = efLib_Create_Attach_Pos(0x84D0U, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            Effect_SetFacingDir(effect, *va_arg(vlist, f32*));
        }
        break;
    }
    case 0x4A9: {
        ret_obj =
            efLib_Create_Attach_Scale(0x9858U, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            Effect_SetFacingDir(effect, *va_arg(vlist, f32*));
            HSD_JObjAnimAll(GET_JOBJ(effect->gobj));
        }
        break;
    }
    case 0x4AA: {
        ret_obj =
            efLib_Create_Attach_Scale(0x9859U, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            Effect_SetFacingDir(effect, *va_arg(vlist, f32*));
            HSD_JObjAnimAll(GET_JOBJ(effect->gobj));
        }
        break;
    }
    case 0x4AB: {
        ret_obj = efLib_Create_Attach_Scale_FacingDir(
            0x9471U, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            effect->next = efLib_Create_Attach_Scale_FacingDir(
                0x9470U, gobj, va_arg(vlist, HSD_JObj*));
        }
        break;
    }
    case 0x4AC: {
        ret_obj = efLib_Create_Attach_Pos(0x80E8U, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            HSD_JObjSetRotationY(GET_JOBJ(effect->gobj), M_PI_2);
            HSD_JObjSetRotationZ(GET_JOBJ(effect->gobj), *va_arg(vlist, f32*));
        }
        break;
    }
    case 0x4AD:
        jobj = va_arg(vlist, HSD_JObj*);
        ret_obj = hsd_8039EFAC(0, 0x24, 0x8CA0, jobj);
        break;
    case 0x4AE:
        jobj = va_arg(vlist, HSD_JObj*);
        ret_obj = hsd_8039EFAC(0, 0x2E, 0xB3B0, jobj);
        break;
    case 0x4AF:
        jobj = va_arg(vlist, HSD_JObj*);
        ret_obj = hsd_8039EFAC(0, 0x2E, 0xB3B1, jobj);
        break;
    case 0x4B0:
        ret_obj = efLib_CreateGenerator_AppSRT_SetFacingDir(0xB3B6, vlist);
        break;
    case 0x4B1: {
        HSD_JObj* input_jobj;

        input_jobj = va_arg(vlist, HSD_JObj*);
        ret_obj = efLib_Create_Attach(0x9088U, gobj, input_jobj);
        if (ret_obj != NULL) {
            effect = ret_obj;
            Effect_SetFacingDir(effect, *va_arg(vlist, f32*));
        }
        hsd_8039EFAC(0, 0x25, 0x9088, input_jobj);
        break;
    }
    case 0x4B2:
        ret_obj = efLib_CreateGenerator(0x908A, va_arg(vlist, Vec3*));
        break;
    case 0x4B3: {
        ret_obj = efLib_Create_Attach_Scale_FacingDir(
            0xB799U, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            effect->next = efLib_Create_Attach_Scale_FacingDir(
                0xB798U, gobj, va_arg(vlist, HSD_JObj*));
        }
        break;
    }
    case 0x4B4:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(
            0x4E20U, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4B5:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(
            0x4E21U, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4B6: {
        Vec3 effect_scale;

        ret_obj =
            efLib_Create_AttachChild(0x5208U, gobj, va_arg(vlist, HSD_JObj*));
        goto copy_gobj_scale;
    case 0x4B7:
        ret_obj =
            efLib_Create_AttachChild(0x5209U, gobj, va_arg(vlist, HSD_JObj*));
    copy_gobj_scale:
        if (ret_obj != NULL) {
            effect = ret_obj;
            HSD_JObjGetScale(GET_JOBJ(gobj), &scale);
            HSD_JObjGetScale(GET_JOBJ(effect->gobj), &effect_scale);
            HSD_JObjSetScale(GET_JOBJ(effect->gobj), &scale);
        }
        break;
    }
    case 0x4B8:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(
            0xBB80U, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x4B9:
        ret_obj = efLib_Create_Attach_Scale_FacingDir(
            0xBB81U, gobj, va_arg(vlist, HSD_JObj*));
        break;
    }

    while (efLib_AnimCount != 0) {
        s32 cnt;

        cnt = efLib_AnimCount - 1;
        efLib_AnimCount = cnt;
        HSD_JObjAnimAll(efLib_AnimQueue[cnt]);
    }

    return ret_obj;
}
