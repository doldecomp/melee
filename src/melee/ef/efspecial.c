#include "efspecial.h"

#include "eflib.h"
#include "math.h"
#include "types.h"

#include "baselib/class.h"
#include "baselib/debug.h"

#include "baselib/forward.h"

#include "baselib/gobj.h"
#include "baselib/list.h"
#include "baselib/object.h"
#include "baselib/pobj.h"

#include <dolphin/mtx.h>

extern char ef_803BF9D0[];
extern char ef_804D39D8[];
extern char ef_804D39E0[];

#define efSpecial_HSD_ASSERT_MSG(line)                                        \
    (((line) == 619)                                     ? "rotate"           \
     : ((line) == 640 || (line) == 661 || (line) == 682) ? ef_803BF9D0        \
     : ((line) == 761 || (line) == 824)                  ? "scale"            \
     : ((line) == 917 || (line) == 980)                  ? "translate"        \
     : ((line) == 1171)                                  ? "mtx"              \
                                                         : ef_804D39E0)

#undef HSD_ASSERT
#define HSD_ASSERT(line, cond)                                                \
    ((cond) ? ((void) 0)                                                      \
            : __assert(ef_804D39D8, line, efSpecial_HSD_ASSERT_MSG(line)))

#include "baselib/jobj.h"

#undef HSD_ASSERT
#define HSD_ASSERT(line, cond)                                                \
    ((cond) ? ((void) 0) : __assert(__FILE__, line, #cond))

#include "baselib/particle.h"
#include "ft/inlines.h"

/* 458EE0 */ extern HSD_JObj* efLib_80458EE0[16];
/* 4D64E8 */ extern s32 efLib_804D64E8;
/* 4D64F0 */ extern s32 efLib_804D64F0;
/* 3BF9D0 */ char ef_803BF9D0[] = "!(jobj->flags & JOBJ_USE_QUATERNION)";
/* 4D39D8 */ SDATA char ef_804D39D8[] = "jobj.h";
/* 4D39E0 */ SDATA char ef_804D39E0[] = "jobj";
/* 4D81D0 */ extern const f32 ef_804D81D0;
/* 4D81D8 */ extern const f64 ef_804D81D8;
/* 4D81E0 */ extern const f64 ef_804D81E0;
/* 4D81E8 */ extern const f32 ef_804D81E8;
/* 4D81EC */ extern const f32 ef_804D81EC;
/* 4D81F0 */ extern const f32 ef_804D81F0;

void* efSync_SpawnSpecial(s32 gfx_id, HSD_GObj* arg_gobj, void* vlist)
{
    void* ret_obj;
    u8 sp_pad128[0x8];
    Vec3 sp130;
    u8 sp_pad130[0x4];
    Effect* eff_2;
    Effect* eff_1;
    Fighter* fighter_1;
    FighterBone* fighter_bone_1;
    f64 f64_1;
    f32 f32_1;
    HSD_JObj* jobj_1;
    HSD_JObj* jobj_2;
    s32 cnt;
    PAD_STACK(0x98);

    efLib_804D64E8 = 1;
    ret_obj = NULL;

    switch (gfx_id) {
    case 0x479:
        ret_obj = efLib_8005C9FC(0x3F2, va_arg(vlist, Vec3*));
        break;
    case 0x47A:
        jobj_1 = va_arg(vlist, HSD_JObj*);
        ret_obj = efLib_8005C1B4(0x3E8, arg_gobj, jobj_1);
        if (ret_obj != NULL) {
            eff_1 = ret_obj;
            if (*va_arg(vlist, f32*) < ef_804D81D0) {
                f64_1 = ef_804D81D8;
            } else {
                f64_1 = ef_804D81E0;
            }
            f32_1 = f64_1;
            HSD_JObjSetRotationY(GET_JOBJ(eff_1->gobj), f32_1);
        }
        hsd_8039EFAC(0, 1, 0x3E9, jobj_1);
        break;
    case 0x47B:
        ret_obj = efLib_8005C9FC(0x3EB, va_arg(vlist, Vec3*));
        break;
    case 0x47C:
        ret_obj = efLib_8005C3DC(0x3E9, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            eff_1 = ret_obj;
            eff_1->x10 = efLib_8005F08C;
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
        ret_obj = efLib_8005C1B4(0x7D0, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            eff_1 = ret_obj;
            eff_1->x10 = efLib_8005EBC8;
        }
        break;
    case 0x483:
        ret_obj = efLib_8005C9FC(0x7D7, va_arg(vlist, Vec3*));
        break;
    case 0x484:
        ret_obj = hsd_8039EFAC(0, 2, 0x7DB, va_arg(vlist, HSD_JObj*));
        break;
    case 0x485:
        ret_obj = hsd_8039EFAC(0, 2, 0x7DE, va_arg(vlist, HSD_JObj*));
        break;
    case 0x486:
        ret_obj = efLib_8005C814(0x7D1, arg_gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            eff_1 = ret_obj;
            if (*va_arg(vlist, f32*) < ef_804D81D0) {
                f64_1 = ef_804D81D8;
            } else {
                f64_1 = ef_804D81E0;
            }
            f32_1 = f64_1;
            HSD_JObjSetRotationY(GET_JOBJ(eff_1->gobj), f32_1);
        }
        break;
    case 0x487:
        ret_obj = efLib_8005C5C4(0x7D2, arg_gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x488:
        ret_obj = efLib_8005C3DC(0xBB8, arg_gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x489:
        ret_obj = efLib_8005C3DC(0xBB9, arg_gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x48A:
        ret_obj = efLib_8005C3DC(0xBBA, arg_gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x48B:
        ret_obj = efLib_8005C1B4(0xBBB, arg_gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x48C:
        ret_obj = efLib_8005C1B4(0xBBC, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            eff_1 = ret_obj;
            eff_1->x10 = efLib_8005E3A0;
        }
        break;
    case 0x48D:
        ret_obj = efLib_8005CF40(0xBC0, vlist);
        break;
    case 0x48E:
        ret_obj = efLib_8005C814(0xBBD, arg_gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            eff_1 = ret_obj;
            HSD_JObjSetRotationY(eff_1->gobj->hsd_obj, ef_804D81E8);
            HSD_JObjSetRotationZ(eff_1->gobj->hsd_obj, *va_arg(vlist, f32*));
        }
        break;
    case 0x48F:
        ret_obj = efLib_8005C6F4(0xFA0, arg_gobj, va_arg(vlist, void*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x0 =
                (void*) efLib_8005C6F4(0xFA1, arg_gobj, va_arg(vlist, void*));
        }
        break;
    case 0x490:
        ret_obj = efLib_8005C1B4(0xFA2, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            eff_1 = ret_obj;
            eff_1->translate.z = *va_arg(vlist, f32*);
            eff_1->x10 = efLib_8005EDDC;
        }
        break;
    case 0x491:
        ret_obj = efLib_8005C1B4(0xFA4, arg_gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x492:
        ret_obj = efLib_8005C3DC(0xFA3, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            eff_1 = ret_obj;
            if (*va_arg(vlist, f32*) < ef_804D81D0) {
                f64_1 = ef_804D81D8;
            } else {
                f64_1 = ef_804D81E0;
            }
            f32_1 = f64_1;
            HSD_JObjSetRotationY(GET_JOBJ(eff_1->gobj), f32_1);
        }
        break;
    case 0x493:
        ret_obj = efLib_8005C3DC(0xFA5, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            eff_1 = ret_obj;
            if (*va_arg(vlist, f32*) < ef_804D81D0) {
                f64_1 = ef_804D81D8;
            } else {
                f64_1 = ef_804D81E0;
            }
            f32_1 = f64_1;
            HSD_JObjSetRotationY(GET_JOBJ(eff_1->gobj), f32_1);
        }
        break;
    case 0x494:
        fighter_1 = GET_FIGHTER(arg_gobj);
        fighter_bone_1 = fighter_1->parts;
        jobj_1 = fighter_bone_1[44].joint;
        jobj_2 = fighter_bone_1[1].joint;
        ret_obj = efLib_8005C2BC(0x1388, arg_gobj, jobj_1);
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x10 = efLib_8005E090;
            ((Effect*) ret_obj)->x24 = 0x41;
            ((Effect*) ret_obj)->x14 = NULL;
            eff_1 = efLib_8005C1B4(0x1389, arg_gobj, jobj_1);
            ((Effect*) ret_obj)->x0 = (void*) eff_1;
            if (eff_1 != NULL) {
                eff_1 = (Effect*) ((Effect*) ret_obj)->x0;
                eff_1->x10 = efLib_8005E090;
                eff_1->x24 = 0x41;
                eff_1->x14 = fighter_1;
                eff_2 = efLib_8005C1B4(0x138A, arg_gobj, jobj_2);
                eff_1->x0 = (void*) eff_2;
                if (eff_2 != NULL) {
                    eff_2 = (Effect*) eff_1->x0;
                    eff_2->x10 = efLib_8005E090;
                    eff_2->x24 = 0x41;
                    eff_2->x14 = fighter_1;
                }
            }
        }
        break;
    case 0x495:
        ret_obj = efLib_8005C3DC(0x138B, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            eff_1 = ret_obj;
            if (*va_arg(vlist, f32*) < ef_804D81D0) {
                f64_1 = ef_804D81D8;
            } else {
                f64_1 = ef_804D81E0;
            }
            f32_1 = f64_1;
            HSD_JObjSetRotationY(GET_JOBJ(eff_1->gobj), f32_1);
        }
        break;
    case 0x496:
        ret_obj = efLib_8005C1B4(0x138C, arg_gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x497:
        ret_obj = efLib_8005C1B4(0x138D, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            eff_1 = ret_obj;
            eff_1->x10 = efLib_8005E2B4;
        }
        break;
    case 0x498:
        ret_obj = efLib_8005C2BC(0x138E, arg_gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x499:
        ret_obj = efLib_8005C2BC(0x138F, arg_gobj, va_arg(vlist, HSD_JObj*));
        break;
    case 0x49A:
        ret_obj = efLib_8005CF40(0x138B, vlist);
        break;
    case 0x49B:
        ret_obj = hsd_8039EFAC(0, 5, 0x138F, va_arg(vlist, HSD_JObj*));
        break;
    case 0x49C:
        ret_obj = hsd_8039EFAC(0, 5, 0x1395, va_arg(vlist, HSD_JObj*));
        break;
    case 0x49D:
        ret_obj = efLib_8005C814(0x1390, arg_gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            eff_1 = ret_obj;
            jobj_2 = arg_gobj->hsd_obj;
            jobj_1 = GET_JOBJ(eff_1->gobj);
            HSD_JObjSetScaleX(jobj_1, HSD_JObjGetScaleY(jobj_2));
            HSD_JObjSetScaleY(jobj_1, HSD_JObjGetScaleY(jobj_2));
            HSD_JObjSetScaleZ(jobj_1, HSD_JObjGetScaleY(jobj_2));
            HSD_JObjSetTranslateZ(HSD_JObjGetChild(jobj_1),
                                  HSD_JObjGetTranslationZ(jobj_1) -
                                      ef_804D81EC);
            if (*va_arg(vlist, f32*) < ef_804D81D0) {
                HSD_JObjSetRotationY(jobj_1, ef_804D81F0);
                HSD_JObjSetRotationZ(jobj_1, -*va_arg(vlist, f32*));
            } else {
                HSD_JObjSetRotationY(jobj_1, ef_804D81E8);
                HSD_JObjSetRotationZ(jobj_1, *va_arg(vlist, f32*));
            }
            eff_1->x10 = efLib_8005E1D8;
        }
        break;
    case 0x49E:
        ret_obj = efLib_8005C9FC(0x206, va_arg(vlist, Vec3*));
        break;
    case 0x49F: {
        HSD_JObj* attach_jobj;

        attach_jobj = va_arg(vlist, HSD_JObj*);
        ret_obj = efLib_8005C1B4(0x7D00, arg_gobj, attach_jobj);
        if (ret_obj != NULL) {
            eff_1 = ret_obj;
            if (*va_arg(vlist, f32*) < ef_804D81D0) {
                f64_1 = ef_804D81D8;
            } else {
                f64_1 = ef_804D81E0;
            }
            f32_1 = f64_1;
            HSD_JObjSetRotationY(GET_JOBJ(eff_1->gobj), f32_1);
        }
        hsd_8039EFAC(0, 0x20, 0x7D00, attach_jobj);
        break;
    }
    case 0x4A0:
        ret_obj = efLib_8005C9FC(0x7D02, va_arg(vlist, Vec3*));
        break;
    case 0x4A5:
        ret_obj = efLib_8005CD2C(0xA028, vlist, arg_gobj);
        break;
    case 0x4A6:
        ret_obj = efLib_8005CD2C(0xA029, vlist, arg_gobj);
        break;
    case 0x4A7:
        ret_obj = efLib_8005CD2C(0xA02A, vlist, arg_gobj);
        break;
    case 0x4A8:
        ret_obj = efLib_8005CD2C(0xA02B, vlist, arg_gobj);
        break;
    case 0x4A1:
        jobj_1 = va_arg(vlist, HSD_JObj*);
        ret_obj = hsd_8039EFAC(0, 0x22, 0x84D4, jobj_1);
        break;
    case 0x4A2:
        jobj_1 = va_arg(vlist, HSD_JObj*);
        ret_obj = hsd_8039EFAC(0, 0x22, 0x84D2, jobj_1);
        break;
    case 0x4A3:
        jobj_1 = va_arg(vlist, HSD_JObj*);
        ret_obj = hsd_8039EFAC(0, 0x22, 0x84D3, jobj_1);
        break;
    case 0x4A4:
        ret_obj = efLib_8005C814(0x84D0, arg_gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            if (*va_arg(vlist, f32*) < ef_804D81D0) {
                f64_1 = ef_804D81D8;
            } else {
                f64_1 = ef_804D81E0;
            }
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            f32_1 = f64_1;
            HSD_JObjSetRotationY(jobj_1, f32_1);
        }
        break;
    case 0x4A9:
        ret_obj = efLib_8005C3DC(0x9858, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            if (*va_arg(vlist, f32*) < ef_804D81D0) {
                f64_1 = ef_804D81D8;
            } else {
                f64_1 = ef_804D81E0;
            }
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            f32_1 = f64_1;
            HSD_JObjSetRotationY(jobj_1, f32_1);
            eff_1 = ret_obj;
            HSD_JObjAnimAll(eff_1->gobj->hsd_obj);
        }
        break;
    case 0x4AA:
        ret_obj = efLib_8005C3DC(0x9859, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            if (*va_arg(vlist, f32*) < ef_804D81D0) {
                f64_1 = ef_804D81D8;
            } else {
                f64_1 = ef_804D81E0;
            }
            eff_1 = ret_obj;
            f32_1 = f64_1;
            HSD_JObjSetRotationY(eff_1->gobj->hsd_obj, f32_1);
            HSD_JObjAnimAll(eff_1->gobj->hsd_obj);
        }
        break;
    case 0x4AB:
        ret_obj = efLib_8005C6F4(0x9471, arg_gobj, va_arg(vlist, void*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x0 =
                (void*) efLib_8005C6F4(0x9470, arg_gobj, va_arg(vlist, void*));
        }
        break;
    case 0x4AC:
        ret_obj = efLib_8005C814(0x80E8, arg_gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            eff_1 = ret_obj;
            HSD_JObjSetRotationY(eff_1->gobj->hsd_obj, ef_804D81E8);
            HSD_JObjSetRotationZ(eff_1->gobj->hsd_obj, *va_arg(vlist, f32*));
        }
        break;
    case 0x4AD:
        jobj_1 = va_arg(vlist, HSD_JObj*);
        ret_obj = hsd_8039EFAC(0, 0x24, 0x8CA0, jobj_1);
        break;
    case 0x4AE:
        jobj_1 = va_arg(vlist, HSD_JObj*);
        ret_obj = hsd_8039EFAC(0, 0x2E, 0xB3B0, jobj_1);
        break;
    case 0x4AF:
        jobj_1 = va_arg(vlist, HSD_JObj*);
        ret_obj = hsd_8039EFAC(0, 0x2E, 0xB3B1, jobj_1);
        break;
    case 0x4B0:
        ret_obj = efLib_8005CF40(0xB3B6, vlist);
        break;
    case 0x4B1: {
        HSD_JObj* attach_jobj;

        attach_jobj = va_arg(vlist, HSD_JObj*);
        ret_obj = efLib_8005C1B4(0x9088, arg_gobj, attach_jobj);
        if (ret_obj != NULL) {
            if (*va_arg(vlist, f32*) < ef_804D81D0) {
                f64_1 = ef_804D81D8;
            } else {
                f64_1 = ef_804D81E0;
            }
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            f32_1 = f64_1;
            HSD_JObjSetRotationY(jobj_1, f32_1);
        }
        hsd_8039EFAC(0, 0x25, 0x9088, attach_jobj);
        break;
    }
    case 0x4B2:
        ret_obj = efLib_8005C9FC(0x908A, va_arg(vlist, Vec3*));
        break;
    case 0x4B3:
        ret_obj = efLib_8005C6F4(0xB799, arg_gobj, va_arg(vlist, void*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x0 =
                (void*) efLib_8005C6F4(0xB798, arg_gobj, va_arg(vlist, void*));
        }
        break;
    case 0x4B4:
        ret_obj = efLib_8005C6F4(0x4E20, arg_gobj, va_arg(vlist, void*));
        break;
    case 0x4B5:
        ret_obj = efLib_8005C6F4(0x4E21, arg_gobj, va_arg(vlist, void*));
        break;
    case 0x4B6:
        ret_obj = efLib_8005C2BC(0x5208, arg_gobj, va_arg(vlist, HSD_JObj*));
        goto efSync_SpawnSpecial_case_4B6_4B7;
    case 0x4B7:
        ret_obj = efLib_8005C2BC(0x5209, arg_gobj, va_arg(vlist, HSD_JObj*));
    efSync_SpawnSpecial_case_4B6_4B7:
        if (ret_obj != NULL) {
            HSD_JObj* jobj;

            jobj_1 = GET_JOBJ(arg_gobj);
            HSD_JObjGetScale(jobj_1, &sp130);
            eff_1 = ret_obj;
            jobj = eff_1->gobj->hsd_obj;
            ((jobj) ? ((void) 0) : __assert(ef_804D39D8, 823, ef_804D39E0));
            HSD_JObjSetScale(eff_1->gobj->hsd_obj, &sp130);
        }
        break;
    case 0x4B8:
        ret_obj = efLib_8005C6F4(0xBB80, arg_gobj, va_arg(vlist, void*));
        break;
    case 0x4B9:
        ret_obj = efLib_8005C6F4(0xBB81, arg_gobj, va_arg(vlist, void*));
        break;
    }

    while (efLib_804D64F0 != 0) {
        cnt = efLib_804D64F0 - 1;
        efLib_804D64F0 = cnt;
        HSD_JObjAnimAll(efLib_80458EE0[cnt]);
    }

    return ret_obj;
}

/* 4D81D0 */ const f32 ef_804D81D0 = 0.0f;
/* 4D81D8 */ const f64 ef_804D81D8 = -M_PI_2;
/* 4D81E0 */ const f64 ef_804D81E0 = M_PI_2;
/* 4D81E8 */ const f32 ef_804D81E8 = M_PI_2;
/* 4D81EC */ const f32 ef_804D81EC = 6.0f;
/* 4D81F0 */ const f32 ef_804D81F0 = -M_PI_2;
