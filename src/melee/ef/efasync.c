#include "efasync.h"

#include "efdata.h"
#include "eflib.h"
#include "efsync.h"
#include "math.h"
#include "types.h"

#include "baselib/gobj.h"
#include "baselib/gobjproc.h"
#include "baselib/particle.h"
#include "baselib/psstructs.h"
#include "baselib/random.h"
#include "cm/camera.h"
#include "lb/lb_00B0.h"
#include "lb/lbarchive.h"
#include "lb/lbdvd.h"

/*
 * TODO: efAsync_Dispatch is the only function left to match, it
 *       currently sits at 98%, and its jump table sits at 53%.
 *       I presume that once the jump table matches then Dispatch
 *       will follow suit (?)
 */

HSD_ObjAllocData efAsync_AllocData;

void* efAsync_Dispatch(s32 gfx_id, HSD_GObj* gobj, va_list vlist)
{
    Vec3 translate;
    Vec3 scale;
    Vec3 scale_2;
    HSD_Generator* generator;
    HSD_psAppSRT* psAppSRT;
    EF_Effect* effect;
    void* va_pos;
    void* va_jobj;
    void* ret_obj;
    f64 rot_y;
    f32 f32_2;
    f32 f32_1;
    s32 u32_2;
    s32 u32_1;
    HSD_JObj* jobj_2;
    HSD_JObj* jobj_1;
    Vec3* va_vec3;
    HSD_GObj* effect_gobj;
    s32 count;
    PAD_STACK(0x20);
    ret_obj = NULL;
    switch (gfx_id) {
    case 0x3E8:
        if (HSD_Randi(8) == 0) {
            ret_obj = efLib_Create_Attach_Pos(9, gobj, va_arg(vlist, Vec3*));
        } else {
            ret_obj = efLib_Create_Attach_Pos(0xA, gobj, va_arg(vlist, Vec3*));
        }
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->state_flags |= EF_STATE_ASYNC;
            f32_1 = (0.04f * (*va_arg(vlist, f32*))) + 0.3f;
            if (f32_1 < 0.3f) {
                f32_1 = 0.3f;
            }
            if (f32_1 > 1.5f) {
                f32_1 = 1.5f;
            }
            scale.x = scale.y = scale.z = f32_1;
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetScale(jobj_1, &scale);
        }
        break;
    case 0x3E9:
        ret_obj = efLib_CreateGenerator(0xC, va_arg(vlist, Vec3*));
        break;
    case 0x3EA:
        ret_obj = efLib_CreateGenerator(0x14, va_arg(vlist, Vec3*));
        break;
    case 0x3EB:
        ret_obj = efLib_Create_Attach_Pos(7, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->state_flags |= EF_STATE_ASYNC;
        }
        break;
    case 0x3EC:
        ret_obj = efLib_Create_Attach_Pos(8, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->state_flags |= EF_STATE_ASYNC;
            f32_1 = (M_TAU * HSD_Randf());
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, f32_1);
        }
        break;
    case 0x3ED:
        va_vec3 = va_arg(vlist, Vec3*);
        f32_1 = va_vec3->x;
        translate = *va_vec3;
        ret_obj = efLib_CreateGenerator(0x50, &translate);
        if (ret_obj != NULL) {
            generator = efLib_CreateGenerator_AddAppSRT(0x54);
            if (generator != NULL) {
                psAppSRT = generator->appsrt;
                psAppSRT->translate = translate;
                if (*va_arg(vlist, f32*) < 0.0f) {
                    rot_y = 0.0;
                } else {
                    rot_y = -M_PI;
                }
                psAppSRT->rot.y = rot_y;
            }
        }
        break;
    case 0x3EE:
        ret_obj = efLib_Create_Attach_Pos(0x27, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            f32_1 = (M_TAU * HSD_Randf());
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, f32_1);
        }
        break;
    case 0x3EF:
    case 0x3F0:
        va_vec3 = va_arg(vlist, Vec3*);
        translate = *va_vec3;
        if (gfx_id == 0x3F0) {
            f32_1 = *va_arg(vlist, f32*);
        } else {
            f32_1 = -*va_arg(vlist, f32*);
        }
        ret_obj =
            efLib_CreateGenerator_Translate_FacingDir(0x42, &translate, f32_1);
        break;
    case 0x3F1:
    case 0x3F2:
        va_vec3 = va_arg(vlist, Vec3*);
        translate = *va_vec3;
        if (gfx_id == 0x3F2) {
            f32_1 = *va_arg(vlist, f32*);
        } else {
            f32_1 = -*va_arg(vlist, f32*);
        }
        ret_obj =
            efLib_CreateGenerator_Translate_FacingDir(0x14B, &translate, f32_1);
        break;
    case 0x3F3:
        ret_obj = efLib_CreateGenerator(0xB, va_arg(vlist, Vec3*));
        break;
    case 0x3F4:
        ret_obj = efLib_CreateGenerator(0x48, va_arg(vlist, Vec3*));
        break;
    case 0x3F5:
        ret_obj = efLib_Create_Attach_Pos(0x10, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->state_flags |= EF_STATE_ASYNC;
            if (*va_arg(vlist, f32*) < 0.0f) {
                rot_y = -M_PI_2;
            } else {
                rot_y = M_PI_2;
            }
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, rot_y);
        }
        break;
    case 0x3F6:
        ret_obj = efLib_Create_Attach_Pos(0x11, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->state_flags |= EF_STATE_ASYNC;
        }
        break;
    case 0x3F7:
        ret_obj = efLib_Create_Attach_Pos(0x12, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->state_flags |= EF_STATE_ASYNC;
            if (*va_arg(vlist, f32*) < 0.0f) {
                rot_y = -M_PI_2;
            } else {
                rot_y = M_PI_2;
            }
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, rot_y);
            f32_2 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, f32_2);
        }
        break;
    case 0x3F8:
        ret_obj = efLib_Create_Attach_Pos(0x13, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->state_flags |= EF_STATE_ASYNC;
            if (*va_arg(vlist, f32*) < 0.0f) {
                rot_y = -M_PI_2;
            } else {
                rot_y = M_PI_2;
            }
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, rot_y);
            f32_2 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, f32_2);
        }
        break;
    case 0x3F9:
        ret_obj = efLib_Create_Attach_Pos(0x14, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->state_flags |= EF_STATE_ASYNC;
            if (*va_arg(vlist, f32*) < 0.0f) {
                rot_y = -M_PI_2;
            } else {
                rot_y = M_PI_2;
            }
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, rot_y);
            f32_2 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, f32_2);
        }
        break;
    case 0x3FA:
        ret_obj = efLib_Create_Attach_Pos(0x15, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->state_flags |= EF_STATE_ASYNC;
        }
        break;
    case 0x3FB:
        ret_obj = efLib_Create_Attach_Pos(0x16, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->state_flags |= EF_STATE_ASYNC;
        }
        break;
    case 0x3FC:
        ret_obj = efLib_Create_Attach_Pos(0x17, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->state_flags |= EF_STATE_ASYNC;
        }
        break;
    case 0x3FD:
        ret_obj = efLib_Create_Attach_Pos(3, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->state_flags |= EF_STATE_ASYNC;
            if (*va_arg(vlist, f32*) < 0.0f) {
                rot_y = -M_PI_2;
            } else {
                rot_y = M_PI_2;
            }
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, rot_y);
            f32_2 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, f32_2);
        }
        break;
    case 0x3FE:
        va_vec3 = va_arg(vlist, Vec3*);
        translate = *va_vec3;
        f32_1 = *va_arg(vlist, f32*);
        ret_obj =
            efLib_CreateGenerator_Translate_FacingDir(0x107, &translate, f32_1);
        break;
    case 0x3FF:
        ret_obj = efLib_Create_Attach_Pos(5, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->state_flags |= EF_STATE_ASYNC;
            if (*va_arg(vlist, f32*) < 0.0f) {
                rot_y = -M_PI_2;
            } else {
                rot_y = M_PI_2;
            }
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, rot_y);
            f32_2 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, f32_2);
        }
        break;
    case 0x400:
    case 0x401:
        va_vec3 = va_arg(vlist, Vec3*);
        translate = *va_vec3;
        if (gfx_id == 0x401) {
            f32_1 = *va_arg(vlist, f32*);
        } else {
            f32_1 = -*va_arg(vlist, f32*);
        }
        ret_obj =
            efLib_CreateGenerator_Translate_FacingDir(0x5A, &translate, f32_1);
        break;
    case 0x402:
        ret_obj = hsd_8039EFAC(0, 0, 0x59, va_arg(vlist, HSD_JObj*));
        break;
    case 0x403:
        ret_obj = hsd_8039EFAC(0, 0, 0x5E, va_arg(vlist, HSD_JObj*));
        break;
    case 0x404:
        ret_obj = efLib_Create_Attach_Pos(0x18, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->state_flags |= EF_STATE_ASYNC;
            f32_1 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, f32_1);
        }
        break;
    case 0x405:
        ret_obj = efLib_CreateGenerator(0x2C, va_arg(vlist, Vec3*));
        break;
    case 0x406:
        ret_obj = efLib_Create_Attach_Pos(4, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->state_flags |= EF_STATE_ASYNC;
            f32_1 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, f32_1);
        }
        break;
    case 0x407:
        ret_obj = efLib_CreateGenerator(0x3C, va_arg(vlist, Vec3*));
        break;
    case 0x408:
        generator = efLib_CreateGenerator_AddAppSRT(0x3E);
        if (generator != NULL) {
            va_vec3 = va_arg(vlist, Vec3*);
            psAppSRT = generator->appsrt;
            psAppSRT->translate = *va_vec3;
            f32_1 = *va_arg(vlist, f32*);
            ret_obj = generator;
            generator->appsrt->rot.z = f32_1;
        }
        break;
    case 0x409:
        ret_obj = hsd_8039EFAC(0, 0, 0xE2, va_arg(vlist, HSD_JObj*));
        break;
    case 0x40A:
        generator = efLib_CreateGenerator_AddAppSRT(0x241);
        if (generator != NULL) {
            va_vec3 = va_arg(vlist, Vec3*);
            psAppSRT = generator->appsrt;
            psAppSRT->translate = *va_vec3;
            f32_1 = *va_arg(vlist, f32*);
            ret_obj = generator;
            generator->appsrt->rot.z = f32_1;
        }
        break;
    case 0x40B:
        generator = efLib_CreateGenerator_AddAppSRT(0x242);
        if (generator != NULL) {
            va_vec3 = va_arg(vlist, Vec3*);
            psAppSRT = generator->appsrt;
            psAppSRT->translate = *va_vec3;
            f32_1 = *va_arg(vlist, f32*);
            ret_obj = generator;
            generator->appsrt->rot.z = f32_1;
        }
        break;
    case 0x40C:
        ret_obj = efLib_CreateGenerator(0x19, va_arg(vlist, Vec3*));
        break;
    case 0x40D:
        generator = efLib_CreateGenerator_AddAppSRT(0x19);
        if (generator != NULL) {
            va_vec3 = va_arg(vlist, Vec3*);
            psAppSRT = generator->appsrt;
            psAppSRT->translate = *va_vec3;
            jobj_1 = GET_JOBJ(gobj);
            HSD_JObjGetScale(jobj_1, &scale);
            ret_obj = generator;
            generator->appsrt->scale.x = generator->appsrt->scale.y =
                generator->appsrt->scale.z = scale.y;
        }
        break;
    case 0x40E:
        ret_obj = efLib_CreateGenerator(0x43, va_arg(vlist, Vec3*));
        break;
    case 0x40F:
        ret_obj = efLib_CreateGenerator(0xE3, va_arg(vlist, Vec3*));
        break;
    case 0x410:
        ret_obj = efLib_CreateGenerator(0x22A, va_arg(vlist, Vec3*));
        break;
    case 0x411:
        ret_obj = efLib_CreateGenerator(0x4B, va_arg(vlist, Vec3*));
        break;
    case 0x412:
        ret_obj = hsd_8039EFAC(0, 0, 0x13, va_arg(vlist, HSD_JObj*));
        break;
    case 0x413:
        ret_obj = hsd_8039EFAC(0, 0, 0x37, va_arg(vlist, HSD_JObj*));
        break;
    case 0x414:
        ret_obj = hsd_8039EFAC(0, 0, 0xE1, va_arg(vlist, HSD_JObj*));
        break;
    case 0x415:
        ret_obj =
            efLib_Create_AttachChild(0x25, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->state_flags |= EF_STATE_ASYNC;
            f32_1 = *va_arg(vlist, f32*);
            scale.x = scale.y = scale.z = f32_1;
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetScale(jobj_1, &scale);
        }
        break;
    case 0x416:
        ret_obj = efLib_CreateGenerator(0x196, va_arg(vlist, Vec3*));
        break;
    case 0x417:
        efLib_LoadKind = EF_LOADKIND_SYNC;
        ret_obj = efLib_Create_Attach(0xB, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            u32_1 = va_arg(vlist, u32);
            if (jobj_1 == NULL) {
                jobj_2 = NULL;
            } else {
                jobj_2 = jobj_1->child;
            }
            if ((u32) (u32_1 + 0xFFA00000) == 0x6060U) {
                u32_2 = 0x808080;
            } else {
                u32_2 = 0xFFFFFF;
            }
            efLib_SetTevKonstColor(jobj_2, 1, u32_2, u32_1);
            ((EF_Effect*) ret_obj)->scale_flags |= EF_SCALE_INHERIT;
            efLib_SetParamGfxId(gobj, gfx_id);
            ((EF_Effect*) ret_obj)->update = efLib_Cb_ApplyStoredAlpha;
        }
        break;
    case 0x418:
        efLib_LoadKind = EF_LOADKIND_SYNC;
        ret_obj = efLib_Create_Attach(0xC, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            u32_1 = va_arg(vlist, u32);
            if (jobj_1 == NULL) {
                jobj_2 = NULL;
            } else {
                jobj_2 = jobj_1->child;
            }
            if ((u32) (u32_1 + 0xFFA00000) == 0x6060U) {
                u32_2 = 0x808080;
            } else {
                u32_2 = 0xFFFFFF;
            }
            efLib_SetTevKonstColor(jobj_2, 0, u32_2, u32_1);
            ((EF_Effect*) ret_obj)->scale_flags |= EF_SCALE_INHERIT;
            efLib_SetParamGfxId(gobj, gfx_id);
            ((EF_Effect*) ret_obj)->update = efLib_Cb_ApplyStoredAlpha;
        }
        break;
    case 0x419:
        efLib_LoadKind = EF_LOADKIND_SYNC;
        ret_obj = efLib_Create_Attach(0xD, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            u32_1 = va_arg(vlist, u32);
            if ((u32) (u32_1 + 0xFFA00000) == 0x6060U) {
                u32_2 = 0x808080;
            } else {
                u32_2 = 0xFFFFFF;
            }
#if 0
                {
                    int i;
                    for (i=0; i < 7; i++) {
                        if (jobj_1 == NULL) {
                            jobj_2 = NULL;
                        } else {
                            jobj_2 = jobj_1->child;
                        }
                        efLib_SetTevKonstColor(jobj_2, 0, u32_2, u32_1);
                        jobj_1 = jobj_2;
                    }
                }
#else
            if (jobj_1 == NULL) {
                jobj_2 = NULL;
            } else {
                jobj_2 = jobj_1->child;
            }
            efLib_SetTevKonstColor(jobj_2, 0, u32_2, u32_1);
            if (jobj_2 == NULL) {
                jobj_2 = NULL;
            } else {
                jobj_2 = jobj_2->next;
            }
            efLib_SetTevKonstColor(jobj_2, 0, u32_2, u32_1);
            if (jobj_2 == NULL) {
                jobj_2 = NULL;
            } else {
                jobj_2 = jobj_2->next;
            }
            efLib_SetTevKonstColor(jobj_2, 0, u32_2, u32_1);
            if (jobj_2 == NULL) {
                jobj_2 = NULL;
            } else {
                jobj_2 = jobj_2->next;
            }
            efLib_SetTevKonstColor(jobj_2, 0, u32_2, u32_1);
            if (jobj_2 == NULL) {
                jobj_2 = NULL;
            } else {
                jobj_2 = jobj_2->next;
            }
            efLib_SetTevKonstColor(jobj_2, 0, u32_2, u32_1);
            if (jobj_2 == NULL) {
                jobj_2 = NULL;
            } else {
                jobj_2 = jobj_2->next;
            }
            efLib_SetTevKonstColor(jobj_2, 0, u32_2, u32_1);
            if (jobj_2 == NULL) {
                jobj_1 = NULL;
            } else {
                jobj_1 = jobj_2->next;
            }
            efLib_SetTevKonstColor(jobj_1, 0, u32_2, u32_1);
#endif
            ((EF_Effect*) ret_obj)->scale_flags |= EF_SCALE_INHERIT;
            efLib_SetParamGfxId(gobj, gfx_id);
            ((EF_Effect*) ret_obj)->update = efLib_Cb_ApplyStoredAlpha;
        }
        break;
    case 0x41A:
        efLib_LoadKind = EF_LOADKIND_SYNC;
        ret_obj = efLib_Create_Attach(0xE, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            u32_1 = va_arg(vlist, u32);
            if (jobj_1 == NULL) {
                jobj_2 = NULL;
            } else {
                jobj_2 = jobj_1->child;
            }
            if ((u32) (u32_1 + 0xFFA00000) == 0x6060U) {
                u32_2 = 0x808080;
            } else {
                u32_2 = 0xFFFFFF;
            }
            efLib_SetTevKonstColor(jobj_2, 0, u32_2, u32_1);
            ((EF_Effect*) ret_obj)->scale_flags |= EF_SCALE_INHERIT;
            efLib_SetParamGfxId(gobj, gfx_id);
            ((EF_Effect*) ret_obj)->update = efLib_Cb_ApplyStoredAlpha;
        }
        break;
    case 0x41B:
        efLib_LoadKind = EF_LOADKIND_SYNC;
        ret_obj = efLib_CreateGenerator_AddAppSRT(0x31);
        if (ret_obj != NULL) {
            jobj_1 = va_arg(vlist, HSD_JObj*);
            lb_8000B1CC(jobj_1, NULL,
                        &((HSD_Generator*) ret_obj)->appsrt->translate);
            HSD_JObjGetScale(jobj_1, &scale_2);
            generator = ret_obj;
            generator->appsrt->scale.x = generator->appsrt->scale.y =
                generator->appsrt->scale.z = scale_2.y;
        }
        break;
    case 0x41C:
        ret_obj = efLib_CreateGenerator(0x5D, va_arg(vlist, Vec3*));
        break;
    case 0x41D:
        ret_obj = efLib_Create_Attach_Pos(0xF, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->state_flags |= EF_STATE_ASYNC;
        }
        break;
    case 0x41E:
        ret_obj = efLib_CreateGenerator_AppSRT_SetScale(0x55, vlist);
        break;
    case 0x41F:
        ret_obj = efLib_CreateGenerator(0x5C, va_arg(vlist, Vec3*));
        break;
    case 0x420:
        ret_obj = efLib_CreateGenerator(0x159, va_arg(vlist, Vec3*));
        break;
    case 0x421:
        ret_obj = efLib_CreateGenerator(0x3F, va_arg(vlist, Vec3*));
        break;
    case 0x422:
        ret_obj = hsd_8039EFAC(0, 0, 0x5B, va_arg(vlist, HSD_JObj*));
        break;
    case 0x423:
        ret_obj = efLib_Create_Attach(1, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, f32_1);
        }
        break;
    case 0x424:
        ret_obj = efLib_Create_Attach(2, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, f32_1);
        }
        break;
    case 0x425:
        ret_obj = efLib_CreateGenerator(0x7E, va_arg(vlist, Vec3*));
        break;
    case 0x426:
        ret_obj = efLib_CreateGenerator(0x7F, va_arg(vlist, Vec3*));
        break;
    case 0x427:
        va_vec3 = va_arg(vlist, Vec3*);
        u32_1 = 0;
        translate = *va_vec3;
    loop_406:
        ret_obj = efLib_Create_Attach_Pos(0x1B, gobj, &translate);
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->update = efLib_Cb_Fall_FromParamY;
            ((EF_Effect*) ret_obj)->lifetime = 0x28;
            ((EF_Effect*) ret_obj)->params.y = (0.4f * HSD_Randf()) + 2.8f;
            f32_1 = (M_TAU * HSD_Randf());
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, f32_1);
            if (u32_1 != 0) {
                effect->next = ret_obj;
                effect = (void*) effect->next;
            } else {
                effect = ret_obj;
                ret_obj = effect;
            }
            if (++u32_1 < 6) {
                goto loop_406;
            }
        }
        break;
    case 0x428:
        ret_obj = efLib_CreateGenerator_AppSRT_SetScale(0xCA, vlist);
        break;
    case 0x429:
        ret_obj = efLib_CreateGenerator_AppSRT_SetScale(0xCE, vlist);
        break;
    case 0x42A:
        ret_obj = efLib_CreateGenerator_AppSRT_SetScale(0xCF, vlist);
        break;
    case 0x42B:
        efLib_LoadKind = EF_LOADKIND_SYNC;
        ret_obj = efLib_Create_Attach_Pos(0x19, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            f32_1 = *va_arg(vlist, f32*);
            HSD_JObjSetRotationZ(jobj_1, f32_1);
            f32_2 = *va_arg(vlist, f32*);
            scale.z = scale.y = scale.x = f32_2;
            HSD_JObjSetScale(jobj_1, &scale);
            if (jobj_1 == NULL) {
                jobj_2 = NULL;
            } else {
                jobj_2 = jobj_1->parent;
            }
            u32_1 = va_arg(vlist, u32);
            u32_2 = va_arg(vlist, u32);
            efLib_SetTevKonstColor(jobj_2, 0, u32_2, u32_1);
        }
        break;
    case 0x42C:
        efLib_LoadKind = EF_LOADKIND_SYNC;
        ret_obj = efLib_Create_Attach_Pos(0x1A, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            f32_1 = *va_arg(vlist, f32*);
            HSD_JObjSetRotationZ(jobj_1, f32_1);
        }
        break;
    case 0x42D:
        efLib_LoadKind = EF_LOADKIND_SYNC;
        ret_obj = efLib_CreateGenerator(0x121, va_arg(vlist, Vec3*));
        break;
    case 0x42E:
        va_vec3 = va_arg(vlist, Vec3*);
        translate = *va_vec3;
        f32_1 = *va_arg(vlist, f32*);
        ret_obj =
            efLib_CreateGenerator_Translate_FacingDir(0x13C, &translate, f32_1);
        break;
    case 0x42F:
        ret_obj = efLib_Create_Attach_Pos(0x20, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            if (*va_arg(vlist, f32*) < 0.0f) {
                rot_y = -M_PI_2;
            } else {
                rot_y = M_PI_2;
            }
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, rot_y);
        }
        break;
    case 0x430:
        va_vec3 = va_arg(vlist, Vec3*);
        translate = *va_vec3;
        f32_1 = *va_arg(vlist, f32*);
        ret_obj =
            efLib_CreateGenerator_Translate_FacingDir(0x140, &translate, f32_1);
        break;
    case 0x431:
        ret_obj = efLib_Create_Attach_Pos(0x21, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            if (*va_arg(vlist, f32*) < 0.0f) {
                rot_y = -M_PI_2;
            } else {
                rot_y = M_PI_2;
            }
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, rot_y);
        }
        break;
    case 0x432:
        ret_obj = efLib_CreateGenerator_AddAppSRT(0x145);
        if (ret_obj != NULL) {
            va_vec3 = va_arg(vlist, Vec3*);
            psAppSRT = ((HSD_Generator*) ret_obj)->appsrt;
            psAppSRT->translate = *va_vec3;
            f32_1 = *va_arg(vlist, f32*);
            generator = ret_obj;
            generator->appsrt->scale.x = generator->appsrt->scale.y =
                generator->appsrt->scale.z = f32_1;
        }
        break;
    case 0x433:
        ret_obj = hsd_8039EFAC(0, 0, 0x115, va_arg(vlist, HSD_JObj*));
        break;
    case 0x434:
        ret_obj = efLib_CreateGenerator(0x14D, va_arg(vlist, Vec3*));
        break;
    case 0x435:
        u32_1 = 0x14E;
        goto block_515;
    case 0x436:
        u32_1 = 0x153;
        goto block_515;
    case 0x437:
        u32_1 = 0x156;
    block_515:
        ret_obj = efLib_CreateGenerator_AddAppSRT(u32_1);
        if (ret_obj != NULL) {
            va_vec3 = va_arg(vlist, Vec3*);
            psAppSRT = ((HSD_Generator*) ret_obj)->appsrt;
            psAppSRT->translate = *va_vec3;
            ((HSD_Generator*) ret_obj)->appsrt->rot.y = M_PI_2;
            generator = ret_obj;
            generator->appsrt->rot.z = *va_arg(vlist, f32*);
        }
        break;
    case 0x438:
        ret_obj = efLib_Create_Attach(0x22, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            jobj_1 = GET_JOBJ(gobj);
            f32_1 = HSD_JObjGetRotationY(jobj_1);
            jobj_2 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_2, f32_1);
            ((EF_Effect*) ret_obj)->update = efLib_Cb_SetScale_FromParamX;
            ((EF_Effect*) ret_obj)->params.x = *va_arg(vlist, f32*);
        }
        break;
    case 0x439:
        ret_obj = efLib_Create_Attach(0x23, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetScaleX(jobj_1, f32_1);
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetScaleY(jobj_1, f32_1);
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetScaleZ(jobj_1, f32_1);
        }
        break;
    case 0x43A:
        ret_obj = efLib_CreateGenerator(0x193, va_arg(vlist, Vec3*));
        break;
    case 0x43B:
        ret_obj = efLib_CreateGenerator(0x192, va_arg(vlist, Vec3*));
        break;
    case 0x43C:
        ret_obj = efLib_CreateGenerator(0x1A0, va_arg(vlist, Vec3*));
        break;
    case 0x43D:
        ret_obj = hsd_8039EFAC(0, 0, 0x1AF, va_arg(vlist, HSD_JObj*));
        break;
    case 0x43E:
        efLib_LoadKind = EF_LOADKIND_SYNC;
        ret_obj = efLib_Create_Attach(0x24, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetScaleX(jobj_1, f32_1);
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetScaleY(jobj_1, f32_1);
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetScaleZ(jobj_1, f32_1);
        }
        break;
    case 0x43F:
        efLib_LoadKind = EF_LOADKIND_SYNC;
        ret_obj = efLib_CreateGenerator_AddAppSRT(0xCA);
        if (ret_obj != NULL) {
            va_vec3 = va_arg(vlist, Vec3*);
            psAppSRT = ((HSD_Generator*) ret_obj)->appsrt;
            psAppSRT->translate = *va_vec3;
            f32_1 = *va_arg(vlist, f32*);
            generator = ret_obj;
            generator->appsrt->scale.x = generator->appsrt->scale.y =
                generator->appsrt->scale.z = f32_1;
        }
        break;
    case 0x440:
        va_vec3 = va_arg(vlist, Vec3*);
        translate = *va_vec3;
        f32_1 = *va_arg(vlist, f32*);
        ret_obj =
            efLib_CreateGenerator_Translate_FacingDir(0x1D8, &translate, f32_1);
        break;
    case 0x441:
        ret_obj = efLib_CreateGenerator(0x1FB, va_arg(vlist, Vec3*));
        break;
    case 0x442:
        ret_obj = efLib_CreateGenerator(0x1DC, va_arg(vlist, Vec3*));
        break;
    case 0x443:
        ret_obj = efLib_CreateGenerator_AddAppSRT(0x1F1);
        if (ret_obj != NULL) {
            va_vec3 = va_arg(vlist, Vec3*);
            psAppSRT = ((HSD_Generator*) ret_obj)->appsrt;
            psAppSRT->translate = *va_vec3;
            f32_1 = *va_arg(vlist, f32*);
            generator = ret_obj;
            generator->appsrt->scale.x = generator->appsrt->scale.y =
                generator->appsrt->scale.z = f32_1;
        }
        break;
    case 0x444:
        ret_obj = efLib_CreateGenerator(0x1FF, va_arg(vlist, Vec3*));
        break;
    case 0x445:
        ret_obj = efLib_CreateGenerator(0x209, va_arg(vlist, Vec3*));
        break;
    case 0x446:
        jobj_1 = va_arg(vlist, HSD_JObj*);
        va_vec3 = va_arg(vlist, Vec3*);
        ret_obj =
            efLib_CreateGenerator_AppSRT_SetPos(0x1B, gobj, jobj_1, va_vec3);
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->lifetime = 0x16;
        }
        break;
    case 0x447:
        efLib_LoadKind = EF_LOADKIND_SYNC;
        ret_obj = efLib_Create_Attach_Pos(0x28, gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->update = efLib_Cb_ftCo_Bury;
            if (gfx_id == 0x447) {
                f32_1 = *va_arg(vlist, f32*);
                scale.x = scale.y = scale.z = f32_1;
                jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
                HSD_JObjSetScale(jobj_1, &scale);
            }
        }
        break;
    case 0x448:
        va_jobj = va_arg(vlist, void*);
        va_pos = va_arg(vlist, void*);
        ret_obj =
            efLib_CreateGenerator_AppSRT_SetPos(0x92, gobj, va_jobj, va_pos);
        if (ret_obj != NULL) {
            ((EF_Effect*) ret_obj)->lifetime = 0xB4;
        }
        break;
    case 0x449:
        ret_obj = efLib_Create_Attach(0x26, gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x44A:
        f32_1 = 0.5f;
        goto block_636;
    case 0x44B:
        f32_1 = 1.0f;
        goto block_636;
    case 0x44C:
        f32_1 = 2.0f;
    block_636:
        ret_obj = efLib_CreateGenerator_AddAppSRT(0x237);
        if (ret_obj != NULL) {
            va_vec3 = va_arg(vlist, Vec3*);
            psAppSRT = ((HSD_Generator*) ret_obj)->appsrt;
            psAppSRT->translate = *va_vec3;
            generator = ret_obj;
            generator->appsrt->scale.x = generator->appsrt->scale.y =
                generator->appsrt->scale.z = f32_1;
        }
        break;
    case 0x44D:
        ret_obj = efLib_CreateGenerator_AppSRT_SetScale(0x48, vlist);
        break;
    case 0x44E:
    case 0x457:
        ret_obj = efLib_CreateGenerator_AppSRT_SetFacingDirScale(0xDA, vlist);
        break;
    case 0x44F:
    case 0x458:
        ret_obj = efLib_CreateGenerator_AppSRT_SetFacingDirScale(0xDB, vlist);
        break;
    case 0x450:
    case 0x459:
        ret_obj = efLib_CreateGenerator_AppSRT_SetFacingDirScale(0xDC, vlist);
        break;
    case 0x451:
    case 0x45A:
        ret_obj = efLib_CreateGenerator_AppSRT_SetFacingDirScale(0xDD, vlist);
        break;
    case 0x453:
        lb_8000B1CC(va_arg(vlist, HSD_JObj*), NULL, &translate);
        generator = efLib_CreateGenerator_Translate_FacingDir(
            0x234, &translate, *va_arg(vlist, f32*));
        if (generator != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            ret_obj = generator;
            generator->appsrt->scale.x = generator->appsrt->scale.y =
                generator->appsrt->scale.z = f32_1;
        }
        break;
    case 0x454:
        lb_8000B1CC(va_arg(vlist, HSD_JObj*), NULL, &translate);
        generator = efLib_CreateGenerator_Translate_FacingDir(
            0x235, &translate, *va_arg(vlist, f32*));
        if (generator != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            ret_obj = generator;
            generator->appsrt->scale.x = generator->appsrt->scale.y =
                generator->appsrt->scale.z = f32_1;
        }
        break;
    case 0x455:
        lb_8000B1CC(va_arg(vlist, HSD_JObj*), NULL, &translate);
        generator = efLib_CreateGenerator_Translate_FacingDir(
            0x236, &translate, *va_arg(vlist, f32*));
        if (generator != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            ret_obj = generator;
            generator->appsrt->scale.x = generator->appsrt->scale.y =
                generator->appsrt->scale.z = f32_1;
        }
        break;
    case 0x456:
        lb_8000B1CC(va_arg(vlist, HSD_JObj*), NULL, &translate);
        generator = efLib_CreateGenerator_Translate_FacingDir(
            0x23D, &translate, *va_arg(vlist, f32*));
        if (generator != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            ret_obj = generator;
            generator->appsrt->scale.x = generator->appsrt->scale.y =
                generator->appsrt->scale.z = f32_1;
        }
        break;
    case 0x452:
        generator = efLib_CreateGenerator_AddAppSRT(0x21E);
        if (generator != NULL) {
            lb_8000B1CC(va_arg(vlist, HSD_JObj*), NULL,
                        &generator->appsrt->translate);
            f32_1 = *va_arg(vlist, f32*);
            ret_obj = generator;
            generator->appsrt->scale.x = generator->appsrt->scale.y =
                generator->appsrt->scale.z = f32_1;
        }
        break;
    case 0x45B:
        ret_obj = efLib_CreateGenerator_AppSRT_SetScale(0x8C, vlist);
        break;
    case 0x45C:
        ret_obj = efLib_CreateGenerator_AppSRT_SetScale(0x8D, vlist);
        break;
    case 0x45D:
        generator = efLib_CreateGenerator_AddAppSRT(0x23F);
        if (generator != NULL) {
            lb_8000B1CC(va_arg(vlist, HSD_JObj*), NULL,
                        &generator->appsrt->translate);
            f32_1 = *va_arg(vlist, f32*);
            ret_obj = generator;
            generator->appsrt->scale.x = generator->appsrt->scale.y =
                generator->appsrt->scale.z = f32_1;
        }
        break;
    case 0x45E:
        generator = efLib_CreateGenerator_AddAppSRT(0x240);
        if (generator != NULL) {
            lb_8000B1CC(va_arg(vlist, HSD_JObj*), NULL,
                        &generator->appsrt->translate);
            f32_1 = *va_arg(vlist, f32*);
            ret_obj = generator;
            generator->appsrt->scale.x = generator->appsrt->scale.y =
                generator->appsrt->scale.z = f32_1;
        }
        break;
    case 0x45F:
        ret_obj = efLib_CreateGenerator_AppSRT_SetScale(0x8E, vlist);
        break;
    case 0x460:
        ret_obj = efLib_CreateGenerator_AppSRT_SetScale(0x99, vlist);
        break;
    case 0x461:
        ret_obj = efLib_CreateGenerator_AppSRT_SetScale(0x95, vlist);
        break;
    case 0x462:
        ret_obj = efLib_CreateGenerator_AppSRT_SetScale(0x219, vlist);
        break;
    case 0x463:
        ret_obj = efLib_Create_Attach(0x29, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            scale.x = scale.y = scale.z = f32_1;
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetScale(jobj_1, &scale);
        }
        break;
    case 0x464:
        ret_obj = efLib_Create_Attach(0x2A, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            scale.x = scale.y = scale.z = f32_1;
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetScale(jobj_1, &scale);
        }
        break;
    case 0x465:
        ret_obj = efLib_CreateGenerator_AppSRT_SetScale(0x88, vlist);
        break;
    case 0x466:
        ret_obj = efLib_CreateGenerator_AppSRT_SetScale(0x89, vlist);
        break;
    case 0x467:
        ret_obj = efLib_CreateGenerator_AppSRT_SetScale(0x8A, vlist);
        break;
    case 0x468:
        ret_obj = efLib_Create_Attach(0x2C, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            scale.x = scale.y = scale.z = f32_1;
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetScale(jobj_1, &scale);
        }
        break;
    case 0x469:
        ret_obj = efLib_Create_Attach(0x2E, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            scale.x = scale.y = scale.z = f32_1;
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetScale(jobj_1, &scale);
        }
        break;
    case 0x46A:
        generator = efLib_CreateGenerator_AddAppSRT(0xAC);
        if (generator != NULL) {
            lb_8000B1CC(va_arg(vlist, HSD_JObj*), NULL,
                        &generator->appsrt->translate);
            f32_1 = *va_arg(vlist, f32*);
            generator->appsrt->scale.x = generator->appsrt->scale.y =
                generator->appsrt->scale.z = f32_1;
            jobj_1 = GET_JOBJ(gobj);
            f32_2 = HSD_JObjGetRotationY(jobj_1);
            ret_obj = generator;
            generator->appsrt->rot.y = jobj_1->rotate.y;
        }
        break;
    case 0x46B:
        ret_obj = efLib_Create_Attach(0x2B, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            scale.x = scale.y = scale.z = f32_1;
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetScale(jobj_1, &scale);
        }
        break;
    case 0x46C:
        generator = efLib_CreateGenerator_AddAppSRT(0x9E);
        if (generator != NULL) {
            lb_8000B1CC(va_arg(vlist, HSD_JObj*), NULL,
                        &generator->appsrt->translate);
            f32_1 = *va_arg(vlist, f32*);
            generator->appsrt->scale.x = generator->appsrt->scale.y =
                generator->appsrt->scale.z = f32_1;
            jobj_1 = gobj->hsd_obj;
            f32_2 = HSD_JObjGetRotationY(jobj_1);
            ret_obj = generator;
            generator->appsrt->rot.y = jobj_1->rotate.y;
        }
        break;
    case 0x46D:
        ret_obj = efLib_Create_Attach(0x2D, gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            scale.x = scale.y = scale.z = f32_1;
            jobj_1 = GET_JOBJ(((EF_Effect*) ret_obj)->gobj);
            HSD_JObjSetScale(jobj_1, &scale);
        }
        break;
    case 0x46E:
        ret_obj = efLib_CreateGenerator_AppSRT_SetScale(0xAE, vlist);
        break;
    case 0x46F:
        ret_obj = efLib_CreateGenerator_AppSRT_SetScale(0xA0, vlist);
        break;
    case 0x470:
        ret_obj = efLib_CreateGenerator_AppSRT_SetScale(0x21B, vlist);
        break;
    case 0x471:
        ret_obj = efLib_CreateGenerator_AppSRT_SetScale(0x220, vlist);
        break;
    case 0x472:
        ret_obj = efLib_CreateGenerator_AppSRT_SetScale(0x131, vlist);
        break;
    case 0x473:
        ret_obj = hsd_8039EFAC(0, 0, 0x82, va_arg(vlist, HSD_JObj*));
        break;
    case 0x477:
        ret_obj = efLib_CreateGenerator(0x7918, va_arg(vlist, Vec3*));
        break;
    case 0x474:
        ret_obj = efLib_CreateGenerator(0xF7, va_arg(vlist, Vec3*));
        break;
    case 0x475:
        ret_obj = efLib_CreateGenerator(0xFC, va_arg(vlist, Vec3*));
        break;
    case 0x476:
        ret_obj = efLib_CreateGenerator(0xFF, va_arg(vlist, Vec3*));
        break;
    }
    while (efLib_AnimCount != 0) {
        count = efLib_AnimCount - 1;
        efLib_AnimCount = count;
        HSD_JObjAnimAll((efLib_AnimQueue[count].gobj));
    }
#if 1
#else
    va_end(vlist);
#endif
    return ret_obj;
}

/* 3C025C */ EF_DAT_Entry efAsync_DatEntries[51] = {
    { "EfCoData.dat", "effCommonDataTable", NULL },
    { "EfMrData.dat", "effMarioDataTable", NULL },
    { "EfSsData.dat", "effSamusDataTable", NULL },
    { "EfFxData.dat", "effFoxDataTable", NULL },
    { "EfCaData.dat", "effCaptainDataTable", NULL },
    { "EfKbData.dat", "effKirbyDataTable", NULL },
    { "EfLkData.dat", "effLinkDataTable", NULL },
    { "EfPkData.dat", "effPikachuDataTable", NULL },
    { "EfDkData.dat", "effDonkeyDataTable", NULL },
    { "EfYsData.dat", "effYoshiDataTable", NULL },
    { "EfNsData.dat", "effNessDataTable", NULL },
    { "EfPrData.dat", "effPurinDataTable", NULL },
    { "EfKpData.dat", "effKoopaDataTable", NULL },
    { "EfMtData.dat", "effMewtwoDataTable", NULL },
    { "EfIcData.dat", "effIceclimberDataTable", NULL },
    { "EfPeData.dat", "effPeachDataTable", NULL },
    { "EfMsData.dat", "effMarsDataTable", NULL },
    { "EfZdData.dat", "effZeldaDataTable", NULL },
    { "EfLgData.dat", "effLuigiDataTable", NULL },
    { "EfGnData.dat", "effGanonDataTable", NULL },
    { "EfKbMs.dat", "effKirbyMarsDataTable", NULL },
    { "EfKbZd.dat", "effKirbyZeldaDataTable", NULL },
    { NULL, NULL, NULL },
    { NULL, NULL, NULL },
    { NULL, NULL, NULL },
    { NULL, NULL, NULL },
    { NULL, NULL, NULL },
    { NULL, NULL, NULL },
    { NULL, NULL, NULL },
    { NULL, NULL, NULL },
    { NULL, NULL, NULL },
    { "EfMnData.dat", "effMenuDataTable", NULL },
    { "EfKbMr.dat", "effKirbyMarioDataTable", NULL },
    { "EfKbFx.dat", "effKirbyFoxDataTable", NULL },
    { "EfKbSs.dat", "effKirbySamusDataTable", NULL },
    { NULL, NULL, NULL },
    { "EfKbPk.dat", "effKirbyPikachuDataTable", NULL },
    { "EfKbLg.dat", "effKirbyLuigiDataTable", NULL },
    { "EfKbCa.dat", "effKirbyCaptainDataTable", NULL },
    { "EfKbDk.dat", "effKirbyDonkeyDataTable", NULL },
    { NULL, NULL, NULL },
    { "EfKbKp.dat", "effKirbyKoopaDataTable", NULL },
    { NULL, NULL, NULL },
    { NULL, NULL, NULL },
    { NULL, NULL, NULL },
    { NULL, NULL, NULL },
    { "EfKbIc.dat", "effKirbyIceDataTable", NULL },
    { "EfKbGn.dat", "effKirbyGanonDataTable", NULL },
    { "EfKbFe.dat", "effKirbyEmblemDataTable", NULL },
    { "EfFeData.dat", "effEmblemDataTable", NULL },
    { NULL, NULL, NULL },
};

void efAsync_LoadAsync(int index)
{
    EF_DAT_Entry* entry = &efAsync_DatEntries[index];
    if (index >= 50 || index < 0) {
        return;
    }

    if (entry->ef_DAT_file == NULL) {
        return;
    }

    lbDvd_800178E8(3, entry->ef_DAT_file, 4, 4, 0, 1U, 4, 4U, index);
}

void efAsync_OnLoad(HSD_Archive* archive, u8* data, u32 length, int index)
{
    EF_DAT_Entry* result;

    lbArchive_InitializeDAT(archive, data, length);
    result = HSD_ArchiveGetPublicAddress(
        archive, efAsync_DatEntries[index].effDataTable_name);
    if ((u32) result->ef_DAT_file | (u32) result->effDataTable_name) {
        psInitDataBankLocate((HSD_Archive*) result->ef_DAT_file,
                             (HSD_Archive*) result->effDataTable_name, NULL);
    }
}

void efAsync_LoadSync(int idx)
{
    EF_DAT_Entry* spC;
    EF_DAT_Entry* lookup;
    lookup = &efAsync_DatEntries[idx];

    if (idx >= 50 || idx < 0) {
        return;
    }
    if (!lookup->ef_DAT_file) {
        return;
    }
    if (lookup->data) {
        return;
    }
    {
        bool chk = lbArchive_80017040(NULL, lookup->ef_DAT_file, &spC,
                                      lookup->effDataTable_name, 0);
        if ((u32) spC->ef_DAT_file | (u32) spC->effDataTable_name) {
            if (chk) {
                psInitDataBankLoad(idx, (void*) spC->ef_DAT_file,
                                   (void*) spC->effDataTable_name, NULL, NULL);
            } else {
                psInitDataBank(idx, (void*) spC->ef_DAT_file,
                               (void*) spC->effDataTable_name, NULL, NULL);
            }
        }
        lookup->data = &spC->data;
    }
}

void efAsync_QueueProcessDeferred(HSD_GObj* gobj, EF_QueuedEffect* queued_effect)
{
    Vec3 sp4C;
    Vec3 sp40;
    Vec3 sp34;
    Vec3 sp28;
    Vec3 sp1C;
    Vec3 sp10;
    HSD_JObj* jobj;
    u32 gfx_id;
    u8 spawn_kind;

    spawn_kind = queued_effect->spawn_kind;
    gfx_id = queued_effect->gfx_id;
    jobj = queued_effect->jobj;
    switch (spawn_kind) {
    case EF_SPAWN_ATTACH:
        efSync_Spawn(gfx_id, gobj, jobj);
        break;
    case EF_SPAWN_POS:
        lb_8000B1CC(jobj, NULL, &sp4C);
        efSync_Spawn(gfx_id, gobj, &sp4C);
        break;
    case EF_SPAWN_POS_OFFSET:
        lb_8000B1CC(jobj, &queued_effect->params, &sp40);
        efSync_Spawn(gfx_id, gobj, &sp40);
        break;
    case EF_SPAWN_ATTACH_PARAM:
        efSync_Spawn(gfx_id, gobj, jobj, &queued_effect->params);
        break;
    case EF_SPAWN_POS_PARAM:
        lb_8000B1CC(jobj, NULL, &sp34);
        efSync_Spawn(gfx_id, gobj, &sp34, &queued_effect->params);
        break;
    case EF_SPAWN_POS_OFFSET_PARAM:
        lb_8000B1CC(jobj, &queued_effect->params, &sp28);
        efSync_Spawn(gfx_id, gobj, &sp28, &queued_effect->extra1);
        break;
    case EF_SPAWN_POS_OFFSET_PARAM2:
        lb_8000B1CC(jobj, &queued_effect->params, &sp1C);
        efSync_Spawn(gfx_id, gobj, &sp1C, &queued_effect->extra1,
                     &queued_effect->extra2);
        break;
    case EF_SPAWN_ATTACH_OFFSET:
        efSync_Spawn(gfx_id, gobj, jobj, &queued_effect->params);
        break;
    case EF_SPAWN_CAMERA_SHAKE:
        lb_8000B1CC(jobj, &queued_effect->params, &sp10);
        Camera_80030E44(gfx_id, &sp10);
        break;
    default:
        HSD_ASSERTREPORT(0x7CU, 0, "[EfASync] unknown type %d\n", spawn_kind,
                         jobj);
        break;
    }
    HSD_ObjFree(&efAsync_AllocData, queued_effect);
}

void efAsync_QueueFlush(HSD_GObj* gobj, void* arg_struct)
{
    EF_QueuedEffect* temp_r31;
    EF_QueuedEffect* var_r4;

    var_r4 = ((EF_QueuedEffect*) arg_struct)->next;
    while (var_r4 != NULL) {
        temp_r31 = var_r4->next;
        efAsync_QueueProcessDeferred(gobj, var_r4);
        var_r4 = temp_r31;
    }
    ((EF_QueuedEffect*) arg_struct)->next = NULL;
}

void efAsync_QueueClear(void* arg_struct)
{
    EF_QueuedEffect* temp_r30;
    EF_QueuedEffect* var_r4;

    var_r4 = ((EF_QueuedEffect*) arg_struct)->next;
    while (var_r4 != NULL) {
        temp_r30 = var_r4->next;
        HSD_ObjFree(&efAsync_AllocData, var_r4);
        var_r4 = temp_r30;
    }
    ((EF_QueuedEffect*) arg_struct)->next = NULL;
}

void efAsync_Spawn(HSD_GObj* gobj, void* queue_head, u32 spawn_kind,
                   u32 gfx_id, HSD_JObj* jobj, ...)
{
    va_list vlist;
    Vec3* va_vec3;
    f32* extra1;
    f32* extra2;
    EF_QueuedEffect* queued;
    PAD_STACK(0x4);

    va_start(vlist, jobj);
    queued = HSD_ObjAlloc(&efAsync_AllocData);
    queued->spawn_kind = spawn_kind;
    queued->gfx_id = gfx_id;
    queued->jobj = jobj;
    switch (spawn_kind) {
    case EF_SPAWN_POS_OFFSET:
        queued->params = *va_arg(vlist, Vec3*);
        break;
    case EF_SPAWN_ATTACH_PARAM:
        queued->params.x = *va_arg(vlist, f32*);
        break;
    case EF_SPAWN_POS_PARAM:
        queued->params.x = *va_arg(vlist, f32*);
        break;
    case EF_SPAWN_POS_OFFSET_PARAM:
        va_vec3 = va_arg(vlist, Vec3*);
        extra2 = va_arg(vlist, f32*);
        queued->params = *va_vec3;
        queued->extra1 = *extra2;
        break;
    case EF_SPAWN_POS_OFFSET_PARAM2:
        va_vec3 = va_arg(vlist, Vec3*);
        extra1 = va_arg(vlist, f32*);
        extra2 = va_arg(vlist, f32*);
        queued->params = *va_vec3;
        queued->extra1 = *extra1;
        queued->extra2 = *extra2;
        break;
    case EF_SPAWN_ATTACH_OFFSET:
        queued->params = *va_arg(vlist, Vec3*);
        break;
    case EF_SPAWN_CAMERA_SHAKE:
        queued->params = *va_arg(vlist, Vec3*);
        break;
    default:
        HSD_ASSERTREPORT(0xF6U, 0, "[EfASync] unknown type %d\n", spawn_kind);
        break;
    }
    va_end(sp80);
    if ((HSD_GObj_804D7838 != NULL) && (HSD_GObj_804D7838->s_link < 9U)) {
        queued->next = ((EF_QueuedEffect*) queue_head)->next;
        ((EF_QueuedEffect*) queue_head)->next = queued;
        return;
    }
    efAsync_QueueProcessDeferred(gobj, queued);
}

void efAsync_QueueInit(void)
{
    HSD_ObjAllocInit(&efAsync_AllocData,
                     sizeof(struct EF_QueuedEffect_ObjAlloc), 4U);
}
