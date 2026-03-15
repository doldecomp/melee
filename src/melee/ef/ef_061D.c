#include "ef_061D.h"

#include "eflib.h"
#include "types.h"

#include "baselib/forward.h"

#include "baselib/gobj.h"
#include "baselib/jobj.h"
#include "baselib/particle.h"

// WIP CLEAN THIS UP AND SYNC

#define EF061D_VA_ARG(t) (*((t*) __va_arg(vlist_arg, _var_arg_typeof(t))))

extern volatile u32 efLib_804D64E8;
extern volatile s32 efLib_804D64F0;

void* efSync_SpawnSpecial(s32 gfx_id, HSD_GObj* gobj, va_list vlist)
{
    Effect* effect;
    HSD_JObj* jobj;
    f32 rotate_y;
    Vec3 scale;
    f32* value_ptr;
    void* ret_obj;
    void* vlist_arg;

    vlist_arg = vlist;
    ret_obj = NULL;
    efLib_804D64E8 = 1;
    PAD_STACK(80);

    switch (gfx_id) {
    case 0x479:
        ret_obj = efLib_8005C9FC(0x3F2, EF061D_VA_ARG(Vec3*));
        break;
    case 0x47A: {
        f64 temp_d;
        f32 rotate_y_2;

        jobj = EF061D_VA_ARG(HSD_JObj*);
        ret_obj = efLib_8005C1B4(0x3E8U, gobj, jobj);
        if (ret_obj != NULL) {
            value_ptr = EF061D_VA_ARG(f32*);
            if (*value_ptr < 0.0f) {
                temp_d = -1.5707963267948966;
            } else {
                temp_d = 1.5707963267948966;
            }
            rotate_y_2 = temp_d;
            HSD_JObjSetRotationY(GET_JOBJ(((Effect*) ret_obj)->gobj),
                                 rotate_y_2);
        }
        hsd_8039EFAC(0, 1, 0x3E9, jobj);
        break;
    }
    case 0x47B:
        ret_obj = efLib_8005C9FC(0x3EB, EF061D_VA_ARG(Vec3*));
        break;
    case 0x47C:
        ret_obj = efLib_8005C3DC(0x3E9U, gobj, EF061D_VA_ARG(HSD_JObj*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x10 = efLib_8005F08C;
        }
        break;
    case 0x47D:
        ret_obj = hsd_8039EFAC(0, 1, 0x3F0, EF061D_VA_ARG(HSD_JObj*));
        break;
    case 0x47E:
        ret_obj = hsd_8039EFAC(0, 1, 0x3F1, EF061D_VA_ARG(HSD_JObj*));
        break;
    case 0x47F:
        ret_obj = hsd_8039EFAC(0, 2, 0x7D4, EF061D_VA_ARG(HSD_JObj*));
        break;
    case 0x480:
        ret_obj = hsd_8039EFAC(0, 2, 0x7D2, EF061D_VA_ARG(HSD_JObj*));
        break;
    case 0x481:
        ret_obj = hsd_8039EFAC(0, 2, 0x7D3, EF061D_VA_ARG(HSD_JObj*));
        break;
    case 0x482:
        ret_obj = efLib_8005C1B4(0x7D0U, gobj, EF061D_VA_ARG(HSD_JObj*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x10 = efLib_8005EBC8;
        }
        break;
    case 0x483:
        ret_obj = efLib_8005C9FC(0x7D7, EF061D_VA_ARG(Vec3*));
        break;
    case 0x484:
        ret_obj = hsd_8039EFAC(0, 2, 0x7DB, EF061D_VA_ARG(HSD_JObj*));
        break;
    case 0x485:
        ret_obj = hsd_8039EFAC(0, 2, 0x7DE, EF061D_VA_ARG(HSD_JObj*));
        break;
    case 0x486: {
        f64 temp_d;
        f32 rotate_y_2;

        ret_obj = efLib_8005C814(0x7D1U, gobj, EF061D_VA_ARG(Vec3*));
        if (ret_obj != NULL) {
            value_ptr = EF061D_VA_ARG(f32*);
            if (*value_ptr < 0.0f) {
                temp_d = -1.5707963267948966;
            } else {
                temp_d = 1.5707963267948966;
            }
            rotate_y_2 = temp_d;
            HSD_JObjSetRotationY(GET_JOBJ(((Effect*) ret_obj)->gobj),
                                 rotate_y_2);
        }
        break;
    }
    case 0x487:
        ret_obj = efLib_8005C5C4(0x7D2U, gobj, EF061D_VA_ARG(HSD_JObj*));
        break;
    case 0x488:
        ret_obj = efLib_8005C3DC(0xBB8U, gobj, EF061D_VA_ARG(HSD_JObj*));
        break;
    case 0x489:
        ret_obj = efLib_8005C3DC(0xBB9U, gobj, EF061D_VA_ARG(HSD_JObj*));
        break;
    case 0x48A:
        ret_obj = efLib_8005C3DC(0xBBAU, gobj, EF061D_VA_ARG(HSD_JObj*));
        break;
    case 0x48B:
        ret_obj = efLib_8005C1B4(0xBBBU, gobj, EF061D_VA_ARG(HSD_JObj*));
        break;
    case 0x48C:
        ret_obj = efLib_8005C1B4(0xBBCU, gobj, EF061D_VA_ARG(HSD_JObj*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x10 = efLib_8005E3A0;
        }
        break;
    case 0x48D:
        ret_obj = efLib_8005CF40(0xBC0, vlist_arg);
        break;
    case 0x48E: {
        ret_obj = efLib_8005C814(0xBBDU, gobj, EF061D_VA_ARG(Vec3*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            HSD_JObjSetRotationY(GET_JOBJ(effect->gobj), 1.5707964f);
            HSD_JObjSetRotationZ(GET_JOBJ(effect->gobj), *EF061D_VA_ARG(f32*));
        }
        break;
    }
    case 0x48F: {
        ret_obj = efLib_8005C6F4(0xFA0U, gobj, EF061D_VA_ARG(HSD_JObj*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x0 =
                (void*) efLib_8005C6F4(0xFA1U, gobj, EF061D_VA_ARG(HSD_JObj*));
        }
        break;
    }
    case 0x490: {
        ret_obj = efLib_8005C1B4(0xFA2U, gobj, EF061D_VA_ARG(HSD_JObj*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->translate.z = *EF061D_VA_ARG(f32*);
            ((Effect*) ret_obj)->x10 = efLib_8005EDDC;
        }
        break;
    }
    case 0x491:
        ret_obj = efLib_8005C1B4(0xFA4U, gobj, EF061D_VA_ARG(HSD_JObj*));
        break;
    case 0x492: {
        f64 temp_d;
        f32 rotate_y_2;

        ret_obj = efLib_8005C3DC(0xFA3U, gobj, EF061D_VA_ARG(HSD_JObj*));
        if (ret_obj != NULL) {
            value_ptr = EF061D_VA_ARG(f32*);
            if (*value_ptr < 0.0f) {
                temp_d = -1.5707963267948966;
            } else {
                temp_d = 1.5707963267948966;
            }
            rotate_y_2 = temp_d;
            HSD_JObjSetRotationY(GET_JOBJ(((Effect*) ret_obj)->gobj),
                                 rotate_y_2);
        }
        break;
    }
    case 0x493: {
        f64 temp_d;
        f32 rotate_y_2;

        ret_obj = efLib_8005C3DC(0xFA5U, gobj, EF061D_VA_ARG(HSD_JObj*));
        if (ret_obj != NULL) {
            value_ptr = EF061D_VA_ARG(f32*);
            if (*value_ptr < 0.0f) {
                temp_d = -1.5707963267948966;
            } else {
                temp_d = 1.5707963267948966;
            }
            rotate_y_2 = temp_d;
            HSD_JObjSetRotationY(GET_JOBJ(((Effect*) ret_obj)->gobj),
                                 rotate_y_2);
        }
        break;
    }
    case 0x494: {
        void* user_data;
        HSD_JObj** jobj_ptr;
        HSD_JObj* jobj;
        HSD_JObj* jobj_2;
        Effect* effect_1;
        Effect* effect_2;
        ef_UnkStruct2* next_eff;
        u16 effect_flags;

        effect_flags = 0x41;
        user_data = gobj->user_data;
        jobj_ptr = *(HSD_JObj***) ((u8*) user_data + 0x5E8);
        jobj = jobj_ptr[0xB0];
        jobj_2 = jobj_ptr[4];
        ret_obj = efLib_8005C2BC(0x1388U, gobj, jobj);
        if (ret_obj != NULL) {
            effect_1 = ret_obj;
            effect_1->x10 = efLib_8005E090;
            effect_1->x24 = effect_flags;
            effect_1->x14 = NULL;
            next_eff = (void*) efLib_8005C1B4(0x1389U, gobj, jobj);
            effect_1->x0 = next_eff;
            if (next_eff != NULL) {
                effect_2 = (void*) effect_1->x0;
                effect_2->x10 = efLib_8005E090;
                effect_2->x24 = effect_flags;
                effect_2->x14 = user_data;
                next_eff = (void*) efLib_8005C1B4(0x138AU, gobj, jobj_2);
                effect_2->x0 = next_eff;
                if (next_eff != NULL) {
                    effect_1 = (void*) effect_2->x0;
                    effect_1->x10 = efLib_8005E090;
                    effect_1->x24 = effect_flags;
                    effect_1->x14 = user_data;
                }
            }
        }
        break;
    }
    case 0x495: {
        f64 temp_d;
        f32 rotate_y_2;

        ret_obj = efLib_8005C3DC(0x138BU, gobj, EF061D_VA_ARG(HSD_JObj*));
        if (ret_obj != NULL) {
            value_ptr = EF061D_VA_ARG(f32*);
            if (*value_ptr < 0.0f) {
                temp_d = -1.5707963267948966;
            } else {
                temp_d = 1.5707963267948966;
            }
            rotate_y_2 = temp_d;
            HSD_JObjSetRotationY(GET_JOBJ(((Effect*) ret_obj)->gobj),
                                 rotate_y_2);
        }
        break;
    }
    case 0x496:
        ret_obj = efLib_8005C1B4(0x138CU, gobj, EF061D_VA_ARG(HSD_JObj*));
        break;
    case 0x497:
        ret_obj = efLib_8005C1B4(0x138DU, gobj, EF061D_VA_ARG(HSD_JObj*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x10 = efLib_8005E2B4;
        }
        break;
    case 0x498:
        ret_obj = efLib_8005C2BC(0x138EU, gobj, EF061D_VA_ARG(HSD_JObj*));
        break;
    case 0x499:
        ret_obj = efLib_8005C2BC(0x138FU, gobj, EF061D_VA_ARG(HSD_JObj*));
        break;
    case 0x49A:
        ret_obj = efLib_8005CF40(0x138B, vlist_arg);
        break;
    case 0x49B:
        ret_obj = hsd_8039EFAC(0, 5, 0x138F, EF061D_VA_ARG(HSD_JObj*));
        break;
    case 0x49C:
        ret_obj = hsd_8039EFAC(0, 5, 0x1395, EF061D_VA_ARG(HSD_JObj*));
        break;
    case 0x49D: {
        HSD_JObj* jobj;

        ret_obj = efLib_8005C814(0x1390U, gobj, EF061D_VA_ARG(Vec3*));
        if (ret_obj != NULL) {
            HSD_JObj* gobj_jobj = GET_JOBJ(gobj);

            jobj = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetScaleX(jobj, HSD_JObjGetScaleY(gobj_jobj));
            HSD_JObjSetScaleY(jobj, HSD_JObjGetScaleY(gobj_jobj));
            HSD_JObjSetScaleZ(jobj, HSD_JObjGetScaleY(gobj_jobj));
            HSD_JObjSetTranslateZ(HSD_JObjGetChild(jobj),
                                  HSD_JObjGetTranslationZ(jobj) - 6.0f);
            if (*EF061D_VA_ARG(f32*) < 0.0f) {
                HSD_JObjSetRotationY(jobj, -1.5707964f);
                HSD_JObjSetRotationZ(jobj, -*EF061D_VA_ARG(f32*));
            } else {
                HSD_JObjSetRotationY(jobj, 1.5707964f);
                HSD_JObjSetRotationZ(jobj, *EF061D_VA_ARG(f32*));
            }
            ((Effect*) ret_obj)->x10 = efLib_8005E1D8;
        }
        break;
    }
    case 0x49E:
        ret_obj = efLib_8005C9FC(0x206, EF061D_VA_ARG(Vec3*));
        break;
    case 0x49F: {
        f64 temp_d;
        f32 rotate_y_2;
        HSD_JObj* jobj_2;

        jobj_2 = EF061D_VA_ARG(HSD_JObj*);
        ret_obj = efLib_8005C1B4(0x7D00U, gobj, jobj_2);
        if (ret_obj != NULL) {
            effect = ret_obj;
            value_ptr = EF061D_VA_ARG(f32*);
            if (*value_ptr < 0.0f) {
                temp_d = -1.5707963267948966;
            } else {
                temp_d = 1.5707963267948966;
            }
            rotate_y_2 = temp_d;
            HSD_JObjSetRotationY(GET_JOBJ(effect->gobj), rotate_y_2);
        }
        hsd_8039EFAC(0, 0x20, 0x7D00, jobj_2);
        break;
    }
    case 0x4A0:
        ret_obj = efLib_8005C9FC(0x7D02, EF061D_VA_ARG(Vec3*));
        break;
    case 0x4A5:
        ret_obj = efLib_8005CD2C(0xA028, vlist_arg, gobj);
        break;
    case 0x4A6:
        ret_obj = efLib_8005CD2C(0xA029, vlist_arg, gobj);
        break;
    case 0x4A7:
        ret_obj = efLib_8005CD2C(0xA02A, vlist_arg, gobj);
        break;
    case 0x4A8:
        ret_obj = efLib_8005CD2C(0xA02B, vlist_arg, gobj);
        break;
    case 0x4A1:
        jobj = EF061D_VA_ARG(HSD_JObj*);
        ret_obj = hsd_8039EFAC(0, 0x22, 0x84D4, jobj);
        break;
    case 0x4A2:
        jobj = EF061D_VA_ARG(HSD_JObj*);
        ret_obj = hsd_8039EFAC(0, 0x22, 0x84D2, jobj);
        break;
    case 0x4A3:
        jobj = EF061D_VA_ARG(HSD_JObj*);
        ret_obj = hsd_8039EFAC(0, 0x22, 0x84D3, jobj);
        break;
    case 0x4A4: {
        f64 temp_d;
        f32 rotate_y_2;

        ret_obj = efLib_8005C814(0x84D0U, gobj, EF061D_VA_ARG(Vec3*));
        if (ret_obj != NULL) {
            value_ptr = EF061D_VA_ARG(f32*);
            if (*value_ptr < 0.0f) {
                temp_d = -1.5707963267948966;
            } else {
                temp_d = 1.5707963267948966;
            }
            rotate_y_2 = temp_d;
            HSD_JObjSetRotationY(GET_JOBJ(((Effect*) ret_obj)->gobj),
                                 rotate_y_2);
        }
        break;
    }
    case 0x4A9: {
        f64 temp_d;
        f32 rotate_y_2;

        ret_obj = efLib_8005C3DC(0x9858U, gobj, EF061D_VA_ARG(HSD_JObj*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            value_ptr = EF061D_VA_ARG(f32*);
            if (*value_ptr < 0.0f) {
                temp_d = -1.5707963267948966;
            } else {
                temp_d = 1.5707963267948966;
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

        ret_obj = efLib_8005C3DC(0x9859U, gobj, EF061D_VA_ARG(HSD_JObj*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            value_ptr = EF061D_VA_ARG(f32*);
            if (*value_ptr < 0.0f) {
                temp_d = -1.5707963267948966;
            } else {
                temp_d = 1.5707963267948966;
            }
            rotate_y_2 = temp_d;
            HSD_JObjSetRotationY(GET_JOBJ(effect->gobj), rotate_y_2);
            HSD_JObjAnimAll(GET_JOBJ(effect->gobj));
        }
        break;
    }
    case 0x4AB: {
        ret_obj = efLib_8005C6F4(0x9471U, gobj, EF061D_VA_ARG(HSD_JObj*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x0 = (void*) efLib_8005C6F4(
                0x9470U, gobj, EF061D_VA_ARG(HSD_JObj*));
        }
        break;
    }
    case 0x4AC: {
        ret_obj = efLib_8005C814(0x80E8U, gobj, EF061D_VA_ARG(Vec3*));
        if (ret_obj != NULL) {
            effect = ret_obj;
            HSD_JObjSetRotationY(GET_JOBJ(effect->gobj), 1.5707964f);
            HSD_JObjSetRotationZ(GET_JOBJ(effect->gobj), *EF061D_VA_ARG(f32*));
        }
        break;
    }
    case 0x4AD:
        jobj = EF061D_VA_ARG(HSD_JObj*);
        ret_obj = hsd_8039EFAC(0, 0x24, 0x8CA0, jobj);
        break;
    case 0x4AE:
        jobj = EF061D_VA_ARG(HSD_JObj*);
        ret_obj = hsd_8039EFAC(0, 0x2E, 0xB3B0, jobj);
        break;
    case 0x4AF:
        jobj = EF061D_VA_ARG(HSD_JObj*);
        ret_obj = hsd_8039EFAC(0, 0x2E, 0xB3B1, jobj);
        break;
    case 0x4B0:
        ret_obj = efLib_8005CF40(0xB3B6, vlist_arg);
        break;
    case 0x4B1: {
        HSD_JObj* input_jobj;
        f64 temp_d;
        f32 rotate_y_2;

        input_jobj = EF061D_VA_ARG(HSD_JObj*);
        ret_obj = efLib_8005C1B4(0x9088U, gobj, input_jobj);
        if (ret_obj != NULL) {
            value_ptr = EF061D_VA_ARG(f32*);
            if (*value_ptr < 0.0f) {
                temp_d = -1.5707963267948966;
            } else {
                temp_d = 1.5707963267948966;
            }
            effect = ret_obj;
            rotate_y_2 = temp_d;
            HSD_JObjSetRotationY(GET_JOBJ(effect->gobj), rotate_y_2);
        }
        hsd_8039EFAC(0, 0x25, 0x9088, input_jobj);
        break;
    }
    case 0x4B2:
        ret_obj = efLib_8005C9FC(0x908A, EF061D_VA_ARG(Vec3*));
        break;
    case 0x4B3: {
        ret_obj = efLib_8005C6F4(0xB799U, gobj, EF061D_VA_ARG(HSD_JObj*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x0 = (void*) efLib_8005C6F4(
                0xB798U, gobj, EF061D_VA_ARG(HSD_JObj*));
        }
        break;
    }
    case 0x4B4:
        ret_obj = efLib_8005C6F4(0x4E20U, gobj, EF061D_VA_ARG(HSD_JObj*));
        break;
    case 0x4B5:
        ret_obj = efLib_8005C6F4(0x4E21U, gobj, EF061D_VA_ARG(HSD_JObj*));
        break;
    case 0x4B6:
        ret_obj = efLib_8005C2BC(0x5208U, gobj, EF061D_VA_ARG(HSD_JObj*));
        goto lbl_4B6_4B7_shared;
    case 0x4B7:
        ret_obj = efLib_8005C2BC(0x5209U, gobj, EF061D_VA_ARG(HSD_JObj*));
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
        ret_obj = efLib_8005C6F4(0xBB80U, gobj, EF061D_VA_ARG(HSD_JObj*));
        break;
    case 0x4B9:
        ret_obj = efLib_8005C6F4(0xBB81U, gobj, EF061D_VA_ARG(HSD_JObj*));
        break;
    }

    while (efLib_804D64F0 != 0) {
        s32 cnt;

        cnt = efLib_804D64F0 - 1;
        efLib_804D64F0 = cnt;
        // horrible. its actually just efLib_80458EE0[cnt]
        HSD_JObjAnimAll(
            ((_struct_efLib_80458EE0*) (((u32*) efLib_80458EE0) + cnt))
                ->x0_gobj);
    }

    return ret_obj;
}
