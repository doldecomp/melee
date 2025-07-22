#include "forward.h"
#include "baselib/forward.h"

#include "efasync.static.h"

#include "efasync.h"
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

extern struct _struct_efLib_80458EE0_0x8 efLib_80458EE0[16];
extern s32 efLib_804D64E8;
extern s32 efLib_804D64F0;
static s8 efAsync_803BFB00[0x25] = "!(jobj->flags & JOBJ_USE_QUATERNION)";
static s8 efAsync_803BFD68[0xD] = "EfCoData.dat";
static s8 efAsync_803BFD78[0x13] = "effCommonDataTable";
static s8 efAsync_803BFD8C[0xD] = "EfMrData.dat";
static s8 efAsync_803BFD9C[0x12] = "effMarioDataTable";
static s8 efAsync_803BFDB0[0xD] = "EfSsData.dat";
static s8 efAsync_803BFDC0[0x12] = "effSamusDataTable";
static s8 efAsync_803BFDD4[0xD] = "EfFxData.dat";
static s8 efAsync_803BFDE4[0x10] = "effFoxDataTable";
static s8 efAsync_803BFDF4[0xD] = "EfCaData.dat";
static s8 efAsync_803BFE04[0x14] = "effCaptainDataTable";
static s8 efAsync_803BFE18[0xD] = "EfKbData.dat";
static s8 efAsync_803BFE28[0x12] = "effKirbyDataTable";
static s8 efAsync_803BFE3C[0xD] = "EfLkData.dat";
static s8 efAsync_803BFE4C[0x11] = "effLinkDataTable";
static s8 efAsync_803BFE60[0xD] = "EfPkData.dat";
static s8 efAsync_803BFE70[0x14] = "effPikachuDataTable";
static s8 efAsync_803BFE84[0xD] = "EfDkData.dat";
static s8 efAsync_803BFE94[0x13] = "effDonkeyDataTable";
static s8 efAsync_803BFEA8[0xD] = "EfYsData.dat";
static s8 efAsync_803BFEB8[0x12] = "effYoshiDataTable";
static s8 efAsync_803BFECC[0xD] = "EfNsData.dat";
static s8 efAsync_803BFEDC[0x11] = "effNessDataTable";
static s8 efAsync_803BFEF0[0xD] = "EfPrData.dat";
static s8 efAsync_803BFF00[0x12] = "effPurinDataTable";
static s8 efAsync_803BFF14[0xD] = "EfKpData.dat";
static s8 efAsync_803BFF24[0x12] = "effKoopaDataTable";
static s8 efAsync_803BFF38[0xD] = "EfMtData.dat";
static s8 efAsync_803BFF48[0x13] = "effMewtwoDataTable";
static s8 efAsync_803BFF5C[0xD] = "EfIcData.dat";
static s8 efAsync_803BFF6C[0x17] = "effIceclimberDataTable";
static s8 efAsync_803BFF84[0xD] = "EfPeData.dat";
static s8 efAsync_803BFF94[0x12] = "effPeachDataTable";
static s8 efAsync_803BFFA8[0xD] = "EfMsData.dat";
static s8 efAsync_803BFFB8[0x11] = "effMarsDataTable";
static s8 efAsync_803BFFCC[0xD] = "EfZdData.dat";
static s8 efAsync_803BFFDC[0x12] = "effZeldaDataTable";
static s8 efAsync_803BFFF0[0xD] = "EfLgData.dat";
static s8 efAsync_803C0000[0x12] = "effLuigiDataTable";
static s8 efAsync_803C0014[0xD] = "EfGnData.dat";
static s8 efAsync_803C0024[0x12] = "effGanonDataTable";
static s8 efAsync_803C0038[0xB] = "EfKbMs.dat";
static s8 efAsync_803C0044[0x16] = "effKirbyMarsDataTable";
static s8 efAsync_803C005C[0xB] = "EfKbZd.dat";
static s8 efAsync_803C0068[0x17] = "effKirbyZeldaDataTable";
static s8 efAsync_803C0080[0xD] = "EfMnData.dat";
static s8 efAsync_803C0090[0x11] = "effMenuDataTable";
static s8 efAsync_803C00A4[0xB] = "EfKbMr.dat";
static s8 efAsync_803C00B0[0x17] = "effKirbyMarioDataTable";
static s8 efAsync_803C00C8[0xB] = "EfKbFx.dat";
static s8 efAsync_803C00D4[0x15] = "effKirbyFoxDataTable";
static s8 efAsync_803C00EC[0xB] = "EfKbSs.dat";
static s8 efAsync_803C00F8[0x17] = "effKirbySamusDataTable";
static s8 efAsync_803C0110[0xB] = "EfKbPk.dat";
static s8 efAsync_803C011C[0x19] = "effKirbyPikachuDataTable";
static s8 efAsync_803C0138[0xB] = "EfKbLg.dat";
static s8 efAsync_803C0144[0x17] = "effKirbyLuigiDataTable";
static s8 efAsync_803C015C[0xB] = "EfKbCa.dat";
static s8 efAsync_803C0168[0x19] = "effKirbyCaptainDataTable";
static s8 efAsync_803C0184[0xB] = "EfKbDk.dat";
static s8 efAsync_803C0190[0x18] = "effKirbyDonkeyDataTable";
static s8 efAsync_803C01A8[0xB] = "EfKbKp.dat";
static s8 efAsync_803C01B4[0x17] = "effKirbyKoopaDataTable";
static s8 efAsync_803C01CC[0xB] = "EfKbIc.dat";
static s8 efAsync_803C01D8[0x15] = "effKirbyIceDataTable";
static s8 efAsync_803C01F0[0xB] = "EfKbGn.dat";
static s8 efAsync_803C01FC[0x17] = "effKirbyGanonDataTable";
static s8 efAsync_803C0214[0xB] = "EfKbFe.dat";
static s8 efAsync_803C0220[0x18] = "effKirbyEmblemDataTable";
static s8 efAsync_803C0238[0xD] = "EfFeData.dat";
static s8 efAsync_803C0248[0x13] = "effEmblemDataTable";
static struct _struct_efAsync_803C025C_0xC efAsync_803C025C[51] = {
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
static s8 efAsync_803C04C0[0x1B] = "[EfASync] unknown type %d\n";
static s8 efAsync_803C04DC[0xA] = "efasync.c";
static s8 efAsync_804D39E8[7] = "jobj.h";
static s8 efAsync_804D39F0[5] = "jobj";
static s8 efAsync_804D39F8 = 48;
// static f64 efAsync_804D8208 = 2 * M_PI;

// Effect* efAsync_80063930(s32 gfx_id, HSD_GObj* arg_gobj, va_list arg2) {
#if 1
void* efAsync_80063930(s32 gfx_id, HSD_GObj* arg_gobj, void* vlist)
{
    Vec3 sp1CC;
    Vec3 sp1C0;
    Vec3 sp14;
    HSD_Generator* generator_1;
    HSD_psAppSRT* psAppSRT_1;
    Effect* eff_2;
    void* void_2;
    void* void_1;
    void* ret_obj;
    f64 f64_1;
    f32 f32_2;
    f32 f32_1;
    s32 u32_2;
    s32 u32_1;
    HSD_JObj* jobj_2;
    HSD_JObj* jobj_1;
    Vec3* vec3_1;
    s32 cnt;
    // u8 unused2;
    // u16 unused3;
    PAD_STACK(0x20);
#else
void* efAsync_80063930(s32 gfx_id, HSD_GObj* arg_gobj, ...)
{
    va_list vlist;
    Vec3 sp1CC;
    Vec3 sp1C0;
    Vec3 sp14;
    HSD_Generator* generator_1;
    HSD_psAppSRT* psAppSRT_1;
    Effect* eff_2;
    void* void_2;
    void* void_1;
    void* ret_obj;
    f64 f64_1;
    f32 f32_2;
    f32 f32_1;
    s32 u32_2;
    s32 u32_1;
    HSD_JObj* jobj_2;
    HSD_JObj* jobj_1;
    Vec3* vec3_1;
    s32 cnt;
    // u8 unused2;
    // u16 unused3;
    PAD_STACK(0x20);

    va_start(vlist, arg_gobj);
#endif

    // var_r26 = saved_reg_r26;
    // temp_r3 = "!(jobj->flags & JOBJ_USE_QUATERNION)";
    ret_obj = NULL;
    switch (gfx_id) {
    case 0x3E8:
        if (HSD_Randi(8) == 0) {
            ret_obj = efLib_8005C814(9, arg_gobj, va_arg(vlist, Vec3*));
        } else {
            ret_obj = efLib_8005C814(0xA, arg_gobj, va_arg(vlist, Vec3*));
        }
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x28 |= 0x80;
            f32_1 = (0.04f * (*va_arg(vlist, f32*))) + 0.3f;
            if (f32_1 < 0.3f) {
                f32_1 = 0.3f;
            }
            if (f32_1 > 1.5f) {
                f32_1 = 1.5f;
            }
            sp1C0.x = sp1C0.y = sp1C0.z = f32_1;
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetScale(jobj_1, &sp1C0);
        }
        break;
    case 0x3E9:
        ret_obj = efLib_8005C9FC(0xC, va_arg(vlist, Vec3*));
        break;
    case 0x3EA:
        ret_obj = efLib_8005C9FC(0x14, va_arg(vlist, Vec3*));
        break;
    case 0x3EB:
        ret_obj = efLib_8005C814(7, arg_gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x28 |= 0x80;
        }
        break;
    case 0x3EC:
        ret_obj = efLib_8005C814(8, arg_gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x28 |= 0x80;
            f32_1 = (2 * M_PI * HSD_Randf());
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, f32_1);
        }
        break;
    case 0x3ED:
        vec3_1 = va_arg(vlist, Vec3*);
        f32_1 = vec3_1->x;
        sp1CC = *vec3_1;
        // ret_obj = efLib_8005C9FC(0x50, &sp1CC, f32_1, vec3_1);
        ret_obj = efLib_8005C9FC(0x50, &sp1CC);
        if (ret_obj != NULL) {
            generator_1 = efLib_8005CAB0(0x54);
            if (generator_1 != NULL) {
                psAppSRT_1 = generator_1->appsrt;
                psAppSRT_1->transform = sp1CC;
                if (*va_arg(vlist, f32*) < 0.0f) {
                    f64_1 = 0.0;
                } else {
                    f64_1 = -M_PI;
                }
                psAppSRT_1 = generator_1->appsrt;
                psAppSRT_1->rot.y = f64_1;
            }
        }
        break;
    case 0x3EE:
        ret_obj = efLib_8005C814(0x27, arg_gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            f32_1 = (2 * M_PI * HSD_Randf());
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, f32_1);
        }
        break;
    case 0x3EF:
    case 0x3F0:
        vec3_1 = va_arg(vlist, Vec3*);
        sp1CC = *vec3_1;
        if (gfx_id == 0x3F0) {
            f32_1 = *va_arg(vlist, f32*);
        } else {
            f32_1 = -*va_arg(vlist, f32*);
        }
        ret_obj = efLib_8005CB34(0x42, &sp1CC, f32_1);
        break;
    case 0x3F1:
    case 0x3F2:
        vec3_1 = va_arg(vlist, Vec3*);
        sp1CC = *vec3_1;
        if (gfx_id == 0x3F2) {
            f32_1 = *va_arg(vlist, f32*);
        } else {
            f32_1 = -*va_arg(vlist, f32*);
        }
        ret_obj = efLib_8005CB34(0x14B, &sp1CC, f32_1);
        break;
    case 0x3F3:
        ret_obj = efLib_8005C9FC(0xB, va_arg(vlist, Vec3*));
        break;
    case 0x3F4:
        ret_obj = efLib_8005C9FC(0x48, va_arg(vlist, Vec3*));
        break;
    case 0x3F5:
        ret_obj = efLib_8005C814(0x10, arg_gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x28 |= 0x80;
            if (*va_arg(vlist, f32*) < 0.0f) {
                f64_1 = -M_PI_2;
            } else {
                f64_1 = M_PI_2;
            }
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, f64_1);
        }
        break;
    case 0x3F6:
        ret_obj = efLib_8005C814(0x11, arg_gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x28 |= 0x80;
        }
        break;
    case 0x3F7:
        ret_obj = efLib_8005C814(0x12, arg_gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x28 |= 0x80;
            if (*va_arg(vlist, f32*) < 0.0f) {
                f64_1 = -M_PI_2;
            } else {
                f64_1 = M_PI_2;
            }
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, f64_1);
            f32_2 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, f32_2);
        }
        break;
    case 0x3F8:
        ret_obj = efLib_8005C814(0x13, arg_gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x28 |= 0x80;
            if (*va_arg(vlist, f32*) < 0.0f) {
                f64_1 = -M_PI_2;
            } else {
                f64_1 = M_PI_2;
            }
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, f64_1);
            f32_2 = *va_arg(vlist, f32*);
            // f64_2 = va_arg(arg2, Vec3*)->x;
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, f32_2);
            // HSD_JObjSetRotationZ(jobj_1, f64_2);
        }
        break;
    case 0x3F9:
        ret_obj = efLib_8005C814(0x14, arg_gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x28 |= 0x80;
            if (*va_arg(vlist, f32*) < 0.0f) {
                f64_1 = -M_PI_2;
            } else {
                f64_1 = M_PI_2;
            }
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, f64_1);
            f32_2 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, f32_2);
        }
        break;
    case 0x3FA:
        ret_obj = efLib_8005C814(0x15, arg_gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x28 |= 0x80;
        }
        break;
    case 0x3FB:
        ret_obj = efLib_8005C814(0x16, arg_gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x28 |= 0x80;
        }
        break;
    case 0x3FC:
        ret_obj = efLib_8005C814(0x17, arg_gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x28 |= 0x80;
        }
        break;
    case 0x3FD:
        ret_obj = efLib_8005C814(3, arg_gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x28 |= 0x80;
            if (*va_arg(vlist, f32*) < 0.0f) {
                f64_1 = -M_PI_2;
            } else {
                f64_1 = M_PI_2;
            }
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, f64_1);
            f32_2 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, f32_2);
        }
        break;
    case 0x3FE:
        vec3_1 = va_arg(vlist, Vec3*);
        sp1CC = *vec3_1;
        f32_1 = *va_arg(vlist, f32*);
        ret_obj = efLib_8005CB34(0x107, &sp1CC, f32_1);
        break;
    case 0x3FF:
        ret_obj = efLib_8005C814(5, arg_gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x28 |= 0x80;
            if (*va_arg(vlist, f32*) < 0.0f) {
                f64_1 = -M_PI_2;
            } else {
                f64_1 = M_PI_2;
            }
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, f64_1);
            f32_2 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, f32_2);
        }
        break;
    case 0x400:
    case 0x401:
        vec3_1 = va_arg(vlist, Vec3*);
        sp1CC = *vec3_1;
        if (gfx_id == 0x401) {
            f32_1 = *va_arg(vlist, f32*);
        } else {
            f32_1 = -*va_arg(vlist, f32*);
        }
        ret_obj = efLib_8005CB34(0x5A, &sp1CC, f32_1);
        break;
    case 0x402:
        ret_obj = hsd_8039EFAC(0, 0, 0x59, va_arg(vlist, HSD_JObj*));
        break;
    case 0x403:
        ret_obj = hsd_8039EFAC(0, 0, 0x5E, va_arg(vlist, HSD_JObj*));
        break;
    case 0x404:
        ret_obj = efLib_8005C814(0x18, arg_gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x28 |= 0x80;
            f32_1 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, f32_1);
        }
        break;
    case 0x405:
        ret_obj = efLib_8005C9FC(0x2C, va_arg(vlist, Vec3*));
        break;
    case 0x406:
        ret_obj = efLib_8005C814(4, arg_gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x28 |= 0x80;
            f32_1 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, f32_1);
        }
        break;
    case 0x407:
        ret_obj = efLib_8005C9FC(0x3C, va_arg(vlist, Vec3*));
        break;
    case 0x408:
        generator_1 = efLib_8005CAB0(0x3E);
        if (generator_1 != NULL) {
            vec3_1 = va_arg(vlist, Vec3*);
            psAppSRT_1 = generator_1->appsrt;
            psAppSRT_1->transform = *vec3_1;
            f32_1 = *va_arg(vlist, f32*);
            ret_obj = generator_1;
            generator_1->appsrt->rot.z = f32_1;
        }
        break;
    case 0x409:
        ret_obj = hsd_8039EFAC(0, 0, 0xE2, va_arg(vlist, HSD_JObj*));
        break;
    case 0x40A:
        generator_1 = efLib_8005CAB0(0x241);
        if (generator_1 != NULL) {
            vec3_1 = va_arg(vlist, Vec3*);
            psAppSRT_1 = generator_1->appsrt;
            psAppSRT_1->transform = *vec3_1;
            f32_1 = *va_arg(vlist, f32*);
            ret_obj = generator_1;
            generator_1->appsrt->rot.z = f32_1;
        }
        break;
    case 0x40B:
        generator_1 = efLib_8005CAB0(0x242);
        if (generator_1 != NULL) {
            vec3_1 = va_arg(vlist, Vec3*);
            psAppSRT_1 = generator_1->appsrt;
            psAppSRT_1->transform = *vec3_1;
            f32_1 = *va_arg(vlist, f32*);
            ret_obj = generator_1;
            generator_1->appsrt->rot.z = f32_1;
        }
        break;
    case 0x40C:
        ret_obj = efLib_8005C9FC(0x19, va_arg(vlist, Vec3*));
        break;
    case 0x40D:
        generator_1 = efLib_8005CAB0(0x19);
        if (generator_1 != NULL) {
            vec3_1 = va_arg(vlist, Vec3*);
            psAppSRT_1 = generator_1->appsrt;
            psAppSRT_1->transform = *vec3_1;
            jobj_1 = GET_JOBJ(arg_gobj);
            HSD_JObjGetScale(jobj_1, &sp1C0);
            ret_obj = generator_1;
            generator_1->appsrt->scale.x = generator_1->appsrt->scale.y =
                generator_1->appsrt->scale.z = sp1C0.y;
        }
        break;
    case 0x40E:
        ret_obj = efLib_8005C9FC(0x43, va_arg(vlist, Vec3*));
        break;
    case 0x40F:
        ret_obj = efLib_8005C9FC(0xE3, va_arg(vlist, Vec3*));
        break;
    case 0x410:
        ret_obj = efLib_8005C9FC(0x22A, va_arg(vlist, Vec3*));
        break;
    case 0x411:
        ret_obj = efLib_8005C9FC(0x4B, va_arg(vlist, Vec3*));
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
        ret_obj = efLib_8005C2BC(0x25, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x28 |= 0x80;
            f32_1 = *va_arg(vlist, f32*);
            sp1C0.x = sp1C0.y = sp1C0.z = f32_1;
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetScale(jobj_1, &sp1C0);
        }
        break;
    case 0x416:
        ret_obj = efLib_8005C9FC(0x196, va_arg(vlist, Vec3*));
        break;
    case 0x417:
        efLib_804D64E8 = 1;
        ret_obj = efLib_8005C1B4(0xB, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
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
            efLib_8005F774(jobj_2, 1, u32_2, u32_1);
            ((Effect*) ret_obj)->x27 |= 1;
            efLib_8005F990(arg_gobj, gfx_id);
            ((Effect*) ret_obj)->x10 = efLib_8005FAB8;
        }
        break;
    case 0x418:
        efLib_804D64E8 = 1;
        ret_obj = efLib_8005C1B4(0xC, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
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
            efLib_8005F774(jobj_2, 0, u32_2, u32_1);
            ((Effect*) ret_obj)->x27 |= 1;
            efLib_8005F990(arg_gobj, gfx_id);
            ((Effect*) ret_obj)->x10 = efLib_8005FAB8;
        }
        break;
    case 0x419:
        efLib_804D64E8 = 1;
        ret_obj = efLib_8005C1B4(0xD, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
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
                        efLib_8005F774(jobj_2, 0, u32_2, u32_1);
                        jobj_1 = jobj_2;
                    }
                }
#else
            if (jobj_1 == NULL) {
                jobj_2 = NULL;
            } else {
                jobj_2 = jobj_1->child;
            }
            efLib_8005F774(jobj_2, 0, u32_2, u32_1);
            if (jobj_2 == NULL) {
                jobj_2 = NULL;
            } else {
                jobj_2 = jobj_2->next;
            }
            efLib_8005F774(jobj_2, 0, u32_2, u32_1);
            if (jobj_2 == NULL) {
                jobj_2 = NULL;
            } else {
                jobj_2 = jobj_2->next;
            }
            efLib_8005F774(jobj_2, 0, u32_2, u32_1);
            if (jobj_2 == NULL) {
                jobj_2 = NULL;
            } else {
                jobj_2 = jobj_2->next;
            }
            efLib_8005F774(jobj_2, 0, u32_2, u32_1);
            if (jobj_2 == NULL) {
                jobj_2 = NULL;
            } else {
                jobj_2 = jobj_2->next;
            }
            efLib_8005F774(jobj_2, 0, u32_2, u32_1);
            if (jobj_2 == NULL) {
                jobj_2 = NULL;
            } else {
                jobj_2 = jobj_2->next;
            }
            efLib_8005F774(jobj_2, 0, u32_2, u32_1);
            if (jobj_2 == NULL) {
                jobj_1 = NULL;
            } else {
                jobj_1 = jobj_2->next;
            }
            efLib_8005F774(jobj_1, 0, u32_2, u32_1);
#endif
            ((Effect*) ret_obj)->x27 |= 1;
            efLib_8005F990(arg_gobj, gfx_id);
            ((Effect*) ret_obj)->x10 = efLib_8005FAB8;
        }
        break;
    case 0x41A:
        efLib_804D64E8 = 1;
        ret_obj = efLib_8005C1B4(0xE, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
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
            efLib_8005F774(jobj_2, 0, u32_2, u32_1);
            ((Effect*) ret_obj)->x27 |= 1;
            efLib_8005F990(arg_gobj, gfx_id);
            ((Effect*) ret_obj)->x10 = efLib_8005FAB8;
        }
        break;
    case 0x41B:
        efLib_804D64E8 = 1;
        ret_obj = efLib_8005CAB0(0x31);
        if (ret_obj != NULL) {
            jobj_1 = va_arg(vlist, HSD_JObj*);
            lb_8000B1CC(jobj_1, NULL,
                        &((HSD_Generator*) ret_obj)->appsrt->transform);
            HSD_JObjGetScale(jobj_1, &sp14);
            generator_1 = ret_obj;
            generator_1->appsrt->scale.x = generator_1->appsrt->scale.y =
                generator_1->appsrt->scale.z = sp14.y;
        }
        break;
    case 0x41C:
        ret_obj = efLib_8005C9FC(0x5D, va_arg(vlist, Vec3*));
        break;
    case 0x41D:
        ret_obj = efLib_8005C814(0xF, arg_gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x28 |= 0x80;
        }
        break;
    case 0x41E:
        ret_obj = efLib_8005CE48(0x55, vlist);
        break;
    case 0x41F:
        ret_obj = efLib_8005C9FC(0x5C, va_arg(vlist, Vec3*));
        break;
    case 0x420:
        ret_obj = efLib_8005C9FC(0x159, va_arg(vlist, Vec3*));
        break;
    case 0x421:
        ret_obj = efLib_8005C9FC(0x3F, va_arg(vlist, Vec3*));
        break;
    case 0x422:
        ret_obj = hsd_8039EFAC(0, 0, 0x5B, va_arg(vlist, HSD_JObj*));
        break;
    case 0x423:
        ret_obj = efLib_8005C1B4(1, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, f32_1);
        }
        break;
    case 0x424:
        ret_obj = efLib_8005C1B4(2, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationZ(jobj_1, f32_1);
        }
        break;
    case 0x425:
        ret_obj = efLib_8005C9FC(0x7E, va_arg(vlist, Vec3*));
        break;
    case 0x426:
        ret_obj = efLib_8005C9FC(0x7F, va_arg(vlist, Vec3*));
        break;
    case 0x427:
        vec3_1 = va_arg(vlist, Vec3*);
        u32_1 = 0;
        sp1CC = *vec3_1;
    loop_406:
        ret_obj = efLib_8005C814(0x1B, arg_gobj, &sp1CC);
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x10 = efLib_8005E648;
            ((Effect*) ret_obj)->x24 = 0x28;
            ((Effect*) ret_obj)->transform.y = (0.4f * HSD_Randf()) + 2.8f;
            f32_1 = (2 * M_PI * HSD_Randf());
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_1, f32_1);
            if (u32_1 != 0) {
                eff_2->x0 = ret_obj;
                eff_2 = (void*) eff_2->x0;
            } else {
                eff_2 = ret_obj;
                ret_obj = eff_2;
            }
            u32_1 += 1;
            if (u32_1 >= 6) {
            } else {
                goto loop_406;
            }
        }
        break;
    case 0x428:
        ret_obj = efLib_8005CE48(0xCA, vlist);
        break;
    case 0x429:
        ret_obj = efLib_8005CE48(0xCE, vlist);
        break;
    case 0x42A:
        ret_obj = efLib_8005CE48(0xCF, vlist);
        break;
    case 0x42B:
        efLib_804D64E8 = 1;
        ret_obj = efLib_8005C814(0x19, arg_gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            f32_1 = *va_arg(vlist, f32*);
            HSD_JObjSetRotationZ(jobj_1, f32_1);
            f32_2 = *va_arg(vlist, f32*);
            sp1C0.z = sp1C0.y = sp1C0.x = f32_2;
            HSD_JObjSetScale(jobj_1, &sp1C0);
            if (jobj_1 == NULL) {
                jobj_2 = NULL;
            } else {
                jobj_2 = jobj_1->parent;
            }
            u32_1 = va_arg(vlist, u32);
            u32_2 = va_arg(vlist, u32);
            efLib_8005F774(jobj_2, 0, u32_2, u32_1);
        }
        break;
    case 0x42C:
        efLib_804D64E8 = 1;
        ret_obj = efLib_8005C814(0x1A, arg_gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            f32_1 = *va_arg(vlist, f32*);
            HSD_JObjSetRotationZ(jobj_1, f32_1);
        }
        break;
    case 0x42D:
        efLib_804D64E8 = 1;
        ret_obj = efLib_8005C9FC(0x121, va_arg(vlist, Vec3*));
        break;
    case 0x42E:
        vec3_1 = va_arg(vlist, Vec3*);
        sp1CC = *vec3_1;
        f32_1 = *va_arg(vlist, f32*);
        ret_obj = efLib_8005CB34(0x13C, &sp1CC, f32_1);
        break;
    case 0x42F:
        ret_obj = efLib_8005C814(0x20, arg_gobj, va_arg(vlist, Vec3*));
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
    case 0x430:
        vec3_1 = va_arg(vlist, Vec3*);
        sp1CC = *vec3_1;
        f32_1 = *va_arg(vlist, f32*);
        ret_obj = efLib_8005CB34(0x140, &sp1CC, f32_1);
        break;
    case 0x431:
        ret_obj = efLib_8005C814(0x21, arg_gobj, va_arg(vlist, Vec3*));
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
    case 0x432:
        ret_obj = efLib_8005CAB0(0x145);
        if (ret_obj != NULL) {
            vec3_1 = va_arg(vlist, Vec3*);
            psAppSRT_1 = ((HSD_Generator*) ret_obj)->appsrt;
            psAppSRT_1->transform = *vec3_1;
            f32_1 = *va_arg(vlist, f32*);
            generator_1 = ret_obj;
            generator_1->appsrt->scale.x = generator_1->appsrt->scale.y =
                generator_1->appsrt->scale.z = f32_1;
        }
        break;
    case 0x433:
        ret_obj = hsd_8039EFAC(0, 0, 0x115, va_arg(vlist, HSD_JObj*));
        break;
    case 0x434:
        ret_obj = efLib_8005C9FC(0x14D, va_arg(vlist, Vec3*));
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
        ret_obj = efLib_8005CAB0(u32_1);
        if (ret_obj != NULL) {
            vec3_1 = va_arg(vlist, Vec3*);
            psAppSRT_1 = ((HSD_Generator*) ret_obj)->appsrt;
            psAppSRT_1->transform = *vec3_1;
            ((HSD_Generator*) ret_obj)->appsrt->rot.y = M_PI_2;
            generator_1 = ret_obj;
            generator_1->appsrt->rot.z = *va_arg(vlist, f32*);
        }
        break;
    case 0x438:
        ret_obj = efLib_8005C1B4(0x22, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            jobj_1 = GET_JOBJ(arg_gobj);
            f32_1 = HSD_JObjGetRotationY(jobj_1);
            jobj_2 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetRotationY(jobj_2, f32_1);
            ((Effect*) ret_obj)->x10 = efLib_8005DE94;
            ((Effect*) ret_obj)->transform.x = *va_arg(vlist, f32*);
        }
        break;
    case 0x439:
        ret_obj = efLib_8005C1B4(0x23, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetScaleX(jobj_1, f32_1);
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetScaleY(jobj_1, f32_1);
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetScaleZ(jobj_1, f32_1);
        }
        break;
    case 0x43A:
        ret_obj = efLib_8005C9FC(0x193, va_arg(vlist, Vec3*));
        break;
    case 0x43B:
        ret_obj = efLib_8005C9FC(0x192, va_arg(vlist, Vec3*));
        break;
    case 0x43C:
        ret_obj = efLib_8005C9FC(0x1A0, va_arg(vlist, Vec3*));
        break;
    case 0x43D:
        ret_obj = hsd_8039EFAC(0, 0, 0x1AF, va_arg(vlist, HSD_JObj*));
        break;
    case 0x43E:
        efLib_804D64E8 = 1;
        ret_obj = efLib_8005C1B4(0x24, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetScaleX(jobj_1, f32_1);
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetScaleY(jobj_1, f32_1);
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetScaleZ(jobj_1, f32_1);
        }
        break;
    case 0x43F:
        efLib_804D64E8 = 1;
        ret_obj = efLib_8005CAB0(0xCA);
        if (ret_obj != NULL) {
            vec3_1 = va_arg(vlist, Vec3*);
            psAppSRT_1 = ((HSD_Generator*) ret_obj)->appsrt;
            psAppSRT_1->transform = *vec3_1;
            f32_1 = *va_arg(vlist, f32*);
            generator_1 = ret_obj;
            generator_1->appsrt->scale.x = generator_1->appsrt->scale.y =
                generator_1->appsrt->scale.z = f32_1;
        }
        break;
    case 0x440:
        vec3_1 = va_arg(vlist, Vec3*);
        sp1CC = *vec3_1;
        f32_1 = *va_arg(vlist, f32*);
        ret_obj = efLib_8005CB34(0x1D8, &sp1CC, f32_1);
        break;
    case 0x441:
        ret_obj = efLib_8005C9FC(0x1FB, va_arg(vlist, Vec3*));
        break;
    case 0x442:
        ret_obj = efLib_8005C9FC(0x1DC, va_arg(vlist, Vec3*));
        break;
    case 0x443:
        ret_obj = efLib_8005CAB0(0x1F1);
        if (ret_obj != NULL) {
            vec3_1 = va_arg(vlist, Vec3*);
            psAppSRT_1 = ((HSD_Generator*) ret_obj)->appsrt;
            psAppSRT_1->transform = *vec3_1;
            f32_1 = *va_arg(vlist, f32*);
            generator_1 = ret_obj;
            generator_1->appsrt->scale.x = generator_1->appsrt->scale.y =
                generator_1->appsrt->scale.z = f32_1;
        }
        break;
    case 0x444:
        ret_obj = efLib_8005C9FC(0x1FF, va_arg(vlist, Vec3*));
        break;
    case 0x445:
        ret_obj = efLib_8005C9FC(0x209, va_arg(vlist, Vec3*));
        break;
    case 0x446:
        void_1 = va_arg(vlist, void*);
        void_2 = va_arg(vlist, void*);
        ret_obj = efLib_8005FCD8(0x1B, arg_gobj, void_1, void_2);
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x24 = 0x16;
        }
        break;
    case 0x447:
        efLib_804D64E8 = 1;
        ret_obj = efLib_8005C814(0x28, arg_gobj, va_arg(vlist, Vec3*));
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x10 = efLib_8005F748;
            if (gfx_id == 0x447) {
                f32_1 = *va_arg(vlist, f32*);
                sp1C0.x = sp1C0.y = sp1C0.z = f32_1;
                jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
                HSD_JObjSetScale(jobj_1, &sp1C0);
            }
        }
        break;
    case 0x448:
        void_1 = va_arg(vlist, void*);
        void_2 = va_arg(vlist, void*);
        ret_obj = efLib_8005FCD8(0x92, arg_gobj, void_1, void_2);
        if (ret_obj != NULL) {
            ((Effect*) ret_obj)->x24 = 0xB4;
        }
        break;
    case 0x449:
        ret_obj = efLib_8005C1B4(0x26, arg_gobj, va_arg(vlist, HSD_JObj*));
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
        ret_obj = efLib_8005CAB0(0x237);
        if (ret_obj != NULL) {
            vec3_1 = va_arg(vlist, Vec3*);
            psAppSRT_1 = ((HSD_Generator*) ret_obj)->appsrt;
            psAppSRT_1->transform = *vec3_1;
            generator_1 = ret_obj;
            generator_1->appsrt->scale.x = generator_1->appsrt->scale.y =
                generator_1->appsrt->scale.z = f32_1;
        }
        break;
    case 0x44D:
        ret_obj = efLib_8005CE48(0x48, vlist);
        break;
    case 0x44E:
    case 0x457:
        ret_obj = efLib_8005D044(0xDA, vlist);
        break;
    case 0x44F:
    case 0x458:
        ret_obj = efLib_8005D044(0xDB, vlist);
        break;
    case 0x450:
    case 0x459:
        ret_obj = efLib_8005D044(0xDC, vlist);
        break;
    case 0x451:
    case 0x45A:
        ret_obj = efLib_8005D044(0xDD, vlist);
        break;
    case 0x453:
        lb_8000B1CC(va_arg(vlist, HSD_JObj*), NULL, &sp1CC);
        generator_1 = efLib_8005CB34(0x234, &sp1CC, *va_arg(vlist, f32*));
        if (generator_1 != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            ret_obj = generator_1;
            generator_1->appsrt->scale.x = generator_1->appsrt->scale.y =
                generator_1->appsrt->scale.z = f32_1;
        }
        break;
    case 0x454:
        lb_8000B1CC(va_arg(vlist, HSD_JObj*), NULL, &sp1CC);
        generator_1 = efLib_8005CB34(0x235, &sp1CC, *va_arg(vlist, f32*));
        if (generator_1 != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            ret_obj = generator_1;
            generator_1->appsrt->scale.x = generator_1->appsrt->scale.y =
                generator_1->appsrt->scale.z = f32_1;
        }
        break;
    case 0x455:
        lb_8000B1CC(va_arg(vlist, HSD_JObj*), NULL, &sp1CC);
        generator_1 = efLib_8005CB34(0x236, &sp1CC, *va_arg(vlist, f32*));
        if (generator_1 != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            ret_obj = generator_1;
            generator_1->appsrt->scale.x = generator_1->appsrt->scale.y =
                generator_1->appsrt->scale.z = f32_1;
        }
        break;
    case 0x456:
        lb_8000B1CC(va_arg(vlist, HSD_JObj*), NULL, &sp1CC);
        generator_1 = efLib_8005CB34(0x23D, &sp1CC, *va_arg(vlist, f32*));
        if (generator_1 != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            ret_obj = generator_1;
            generator_1->appsrt->scale.x = generator_1->appsrt->scale.y =
                generator_1->appsrt->scale.z = f32_1;
        }
        break;
    case 0x452:
        generator_1 = efLib_8005CAB0(0x21E);
        if (generator_1 != NULL) {
            lb_8000B1CC(va_arg(vlist, HSD_JObj*), NULL,
                        &generator_1->appsrt->transform);
            f32_1 = *va_arg(vlist, f32*);
            ret_obj = generator_1;
            generator_1->appsrt->scale.x = generator_1->appsrt->scale.y =
                generator_1->appsrt->scale.z = f32_1;
        }
        break;
    case 0x45B:
        ret_obj = efLib_8005CE48(0x8C, vlist);
        break;
    case 0x45C:
        ret_obj = efLib_8005CE48(0x8D, vlist);
        break;
    case 0x45D:
        generator_1 = efLib_8005CAB0(0x23F);
        if (generator_1 != NULL) {
            lb_8000B1CC(va_arg(vlist, HSD_JObj*), NULL,
                        &generator_1->appsrt->transform);
            f32_1 = *va_arg(vlist, f32*);
            ret_obj = generator_1;
            generator_1->appsrt->scale.x = generator_1->appsrt->scale.y =
                generator_1->appsrt->scale.z = f32_1;
        }
        break;
    case 0x45E:
        generator_1 = efLib_8005CAB0(0x240);
        if (generator_1 != NULL) {
            lb_8000B1CC(va_arg(vlist, HSD_JObj*), NULL,
                        &generator_1->appsrt->transform);
            f32_1 = *va_arg(vlist, f32*);
            ret_obj = generator_1;
            generator_1->appsrt->scale.x = generator_1->appsrt->scale.y =
                generator_1->appsrt->scale.z = f32_1;
        }
        break;
    case 0x45F:
        ret_obj = efLib_8005CE48(0x8E, vlist);
        break;
    case 0x460:
        ret_obj = efLib_8005CE48(0x99, vlist);
        break;
    case 0x461:
        ret_obj = efLib_8005CE48(0x95, vlist);
        break;
    case 0x462:
        ret_obj = efLib_8005CE48(0x219, vlist);
        break;
    case 0x463:
        ret_obj = efLib_8005C1B4(0x29, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            sp1C0.x = sp1C0.y = sp1C0.z = f32_1;
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetScale(jobj_1, &sp1C0);
        }
        break;
    case 0x464:
        ret_obj = efLib_8005C1B4(0x2A, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            sp1C0.x = sp1C0.y = sp1C0.z = f32_1;
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetScale(jobj_1, &sp1C0);
        }
        break;
    case 0x465:
        ret_obj = efLib_8005CE48(0x88, vlist);
        break;
    case 0x466:
        ret_obj = efLib_8005CE48(0x89, vlist);
        break;
    case 0x467:
        ret_obj = efLib_8005CE48(0x8A, vlist);
        break;
    case 0x468:
        ret_obj = efLib_8005C1B4(0x2C, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            sp1C0.x = sp1C0.y = sp1C0.z = f32_1;
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetScale(jobj_1, &sp1C0);
        }
        break;
    case 0x469:
        ret_obj = efLib_8005C1B4(0x2E, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            sp1C0.x = sp1C0.y = sp1C0.z = f32_1;
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetScale(jobj_1, &sp1C0);
        }
        break;
    case 0x46A:
        generator_1 = efLib_8005CAB0(0xAC);
        if (generator_1 != NULL) {
            lb_8000B1CC(va_arg(vlist, HSD_JObj*), NULL,
                        &generator_1->appsrt->transform);
            f32_1 = *va_arg(vlist, f32*);
            generator_1->appsrt->scale.x = generator_1->appsrt->scale.y =
                generator_1->appsrt->scale.z = f32_1;
            jobj_1 = GET_JOBJ(arg_gobj);
            f32_2 = HSD_JObjGetRotationY(jobj_1);
            ret_obj = generator_1;
            generator_1->appsrt->rot.y = jobj_1->rotate.y;
        }
        break;
    case 0x46B:
        ret_obj = efLib_8005C1B4(0x2B, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            sp1C0.x = sp1C0.y = sp1C0.z = f32_1;
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetScale(jobj_1, &sp1C0);
        }
        break;
    case 0x46C:
        generator_1 = efLib_8005CAB0(0x9E);
        if (generator_1 != NULL) {
            lb_8000B1CC(va_arg(vlist, HSD_JObj*), NULL,
                        &generator_1->appsrt->transform);
            f32_1 = *va_arg(vlist, f32*);
            generator_1->appsrt->scale.x = generator_1->appsrt->scale.y =
                generator_1->appsrt->scale.z = f32_1;
            jobj_1 = arg_gobj->hsd_obj;
            f32_2 = HSD_JObjGetRotationY(jobj_1);
            ret_obj = generator_1;
            generator_1->appsrt->rot.y = jobj_1->rotate.y;
        }
        break;
    case 0x46D:
        ret_obj = efLib_8005C1B4(0x2D, arg_gobj, va_arg(vlist, HSD_JObj*));
        if (ret_obj != NULL) {
            f32_1 = *va_arg(vlist, f32*);
            sp1C0.x = sp1C0.y = sp1C0.z = f32_1;
            jobj_1 = GET_JOBJ(((Effect*) ret_obj)->gobj);
            HSD_JObjSetScale(jobj_1, &sp1C0);
        }
        break;
    case 0x46E:
        ret_obj = efLib_8005CE48(0xAE, vlist);
        break;
    case 0x46F:
        ret_obj = efLib_8005CE48(0xA0, vlist);
        break;
    case 0x470:
        ret_obj = efLib_8005CE48(0x21B, vlist);
        break;
    case 0x471:
        ret_obj = efLib_8005CE48(0x220, vlist);
        break;
    case 0x472:
        ret_obj = efLib_8005CE48(0x131, vlist);
        break;
    case 0x473:
        ret_obj = hsd_8039EFAC(0, 0, 0x82, va_arg(vlist, HSD_JObj*));
        break;
    case 0x477:
        ret_obj = efLib_8005C9FC(0x7918, va_arg(vlist, Vec3*));
        break;
    case 0x474:
        ret_obj = efLib_8005C9FC(0xF7, va_arg(vlist, Vec3*));
        break;
    case 0x475:
        ret_obj = efLib_8005C9FC(0xFC, va_arg(vlist, Vec3*));
        break;
    case 0x476:
        ret_obj = efLib_8005C9FC(0xFF, va_arg(vlist, Vec3*));
        break;
    }
    while (efLib_804D64F0 != 0) {
        cnt = efLib_804D64F0 - 1;
        efLib_804D64F0 = cnt;
        // efLib_804D64F0--;
        HSD_JObjAnimAll((efLib_80458EE0[cnt].unk0));
        // HSD_JObjAnimAll((efLib_80458EE0[efLib_804D64F0].unk0));
    }
#if 1
#else
    va_end(vlist);
#endif
    return ret_obj;
}

void efAsync_8006729C(int index)
{
#if 1
    char* DAT_filename;

    DAT_filename = efAsync_803C025C[index].ef_DAT_file;
    if (index < 50) {
        if (index < 0) {
            return;
        }
        if (DAT_filename != NULL) {
            lbDvd_800178E8(3, DAT_filename, 4, 4, 0, 1U, 4, 4U, index);
        }
    }
#else
    struct _struct_efAsync_803C025C_0xC data;
    char* DAT_filename;

    data = efAsync_803C025C[index];
    if (index < 50) {
        if (index < 0) {
            return;
        }
        DAT_filename = data.ef_DAT_file;
        if (DAT_filename != NULL) {
            // if ((bool) DAT_filename) {
            lbDvd_800178E8(3, DAT_filename, 4, 4, 0, 1U, 4, 4U,
                           index); // Should this function have 1 less arg?
        }
    }
#endif
}

// void efAsync_8006730C(HSD_Archive* archive, u8* data, u32 length, s32 index)
// {
void efAsync_8006730C(HSD_Archive* archive, u8* data, u32 length, int index)
{
    char* effDateTable_name;
    char* DAT_filename;
    struct _struct_efAsync_803C025C_0xC* temp_r3;

    lbArchive_InitializeDAT(archive, data, length);
    temp_r3 = HSD_ArchiveGetPublicAddress(
        archive, efAsync_803C025C[index].effDataTable_name);
    DAT_filename = temp_r3->ef_DAT_file;
    effDateTable_name = temp_r3->effDataTable_name;
    if ((bool) DAT_filename | (bool) effDateTable_name) {
        psInitDataBankLocate((HSD_Archive*) DAT_filename,
                             (HSD_Archive*) effDateTable_name, NULL);
    }
}

void efAsync_8006737C(s8 index)
{
    struct _struct_efAsync_803C025C_0xC* spC;
    bool chk;
    char* effDateTable_name;
    char* DAT_filename;
    struct _struct_efAsync_803C025C_0xC* temp_r31;

    temp_r31 = &efAsync_803C025C[index];
    if (index < 50) {
        if (index < 0) {
            return;
        }
        DAT_filename = temp_r31->ef_DAT_file;
        if ((DAT_filename != NULL) && ((void*) temp_r31->unk8 == NULL)) {
            chk = lbArchive_80017040(NULL, DAT_filename, &spC,
                                     temp_r31->effDataTable_name, 0);
            DAT_filename = spC->ef_DAT_file;
            effDateTable_name = spC->effDataTable_name;
            if ((bool) effDateTable_name | (bool) DAT_filename) {
                if (chk) {
                    // psInitDataBankLoad((s32) index, (s32* ) DAT_filename,
                    // (s32* ) effDateTable_name, NULL, NULL);
                    psInitDataBankLoad(index, (void*) DAT_filename,
                                       (void*) effDateTable_name, NULL, NULL);
                } else {
                    psInitDataBank(index, (void*) DAT_filename,
                                   (void*) effDateTable_name, NULL, NULL);
                }
            }
            temp_r31->unk8 = spC->unk8;
        }
    }
}

void efAsync_8006744C(HSD_GObj* gobj, ef_UnkStruct3* arg1)
{
    Vec3 sp4C;
    Vec3 sp40;
    Vec3 sp34;
    Vec3 sp28;
    Vec3 sp1C;
    Vec3 sp10;
    HSD_JObj* jobj;
    u32 gfx_id;
    u8 eff_type;

    eff_type = arg1->eff_type;
    gfx_id = arg1->gfx_id;
    jobj = arg1->xC;
    switch (eff_type) {
    case 0:
        efSync_Spawn(gfx_id, gobj, jobj);
        break;
    case 1:
        lb_8000B1CC(jobj, NULL, &sp4C);
        efSync_Spawn(gfx_id, gobj, &sp4C);
        break;
    case 2:
        lb_8000B1CC(jobj, &arg1->x10, &sp40);
        efSync_Spawn(gfx_id, gobj, &sp40);
        break;
    case 3:
        efSync_Spawn(gfx_id, gobj, jobj, &arg1->x10);
        break;
    case 4:
        lb_8000B1CC(jobj, NULL, &sp34);
        efSync_Spawn(gfx_id, gobj, &sp34, &arg1->x10);
        break;
    case 5:
        lb_8000B1CC(jobj, &arg1->x10, &sp28);
        efSync_Spawn(gfx_id, gobj, &sp28, &arg1->x1C);
        break;
    case 6:
        lb_8000B1CC(jobj, &arg1->x10, &sp1C);
        efSync_Spawn(gfx_id, gobj, &sp1C, &arg1->x1C, &arg1->x20);
        break;
    case 7:
        efSync_Spawn(gfx_id, gobj, jobj, &arg1->x10);
        break;
    case 8:
        lb_8000B1CC(jobj, &arg1->x10, &sp10);
        Camera_80030E44(gfx_id, &sp10);
        break;
    default:
        OSReport("[EfASync] unknown type %d\n", eff_type, jobj);
        __assert("efasync.c", 0x7CU, "0");
        break;
    }
    HSD_ObjFree(&efSync_80458FA0, arg1);
}

void efAsync_80067624(HSD_GObj* gobj, void* arg_struct)
// void efAsync_80067624(HSD_GObj* gobj, ef_UnkStruct3* arg_struct)
{
    ef_UnkStruct3* temp_r31;
    ef_UnkStruct3* var_r4;

    var_r4 = ((ef_UnkStruct3*) arg_struct)->next;
    while (var_r4 != NULL) {
        temp_r31 = var_r4->next;
        efAsync_8006744C(gobj, var_r4);
        var_r4 = temp_r31;
    }
    ((ef_UnkStruct3*) arg_struct)->next = NULL;
}

void efAsync_80067688(void* arg_struct)
// void efAsync_80067688(ef_UnkStruct3* arg_struct)
{
    ef_UnkStruct3* temp_r30;
    ef_UnkStruct3* var_r4;

    var_r4 = ((ef_UnkStruct3*) arg_struct)->next;
    while (var_r4 != NULL) {
        temp_r30 = var_r4->next;
        HSD_ObjFree(&efSync_80458FA0, var_r4);
        var_r4 = temp_r30;
    }
    ((ef_UnkStruct3*) arg_struct)->next = NULL;
}

void efAsync_Spawn(HSD_GObj* gobj, void* arg1, u32 eff_type, u32 gfx_id,
                   HSD_JObj* jobj, ...)
{
    // void efAsync_Spawn(HSD_GObj* gobj, ef_UnkStruct3* arg1, enum_t eff_type,
    // u32 gfx_id, HSD_JObj* jobj, ...) {
    va_list vlist;
    f32* f32_2;
    f32* f32_1;
    Vec3* vec3_1;
    ef_UnkStruct3* ef_unkstruct3_1;
    PAD_STACK(0x4);

    va_start(vlist, jobj);
    ef_unkstruct3_1 = HSD_ObjAlloc(&efSync_80458FA0);
    ef_unkstruct3_1->eff_type = eff_type;
    ef_unkstruct3_1->gfx_id = gfx_id;
    ef_unkstruct3_1->xC = jobj;
    switch (eff_type) {
    case 2:
        ef_unkstruct3_1->x10 = *va_arg(vlist, Vec3*);
        break;
    case 3:
        ef_unkstruct3_1->x10.x = *va_arg(vlist, f32*);
        break;
    case 4:
        ef_unkstruct3_1->x10.x = *va_arg(vlist, f32*);
        break;
    case 5:
        vec3_1 = va_arg(vlist, Vec3*);
        f32_1 = va_arg(vlist, f32*);
        ef_unkstruct3_1->x10 = *vec3_1;
        ef_unkstruct3_1->x1C = *f32_1;
        break;
    case 6:
        vec3_1 = va_arg(vlist, Vec3*);
        f32_2 = va_arg(vlist, f32*);
        f32_1 = va_arg(vlist, f32*);
        ef_unkstruct3_1->x10 = *vec3_1;
        ef_unkstruct3_1->x1C = *f32_2;
        ef_unkstruct3_1->x20 = *f32_1;
        break;
    case 7:
        ef_unkstruct3_1->x10 = *va_arg(vlist, Vec3*);
        break;
    case 8:
        ef_unkstruct3_1->x10 = *va_arg(vlist, Vec3*);
        break;
    default:
        OSReport("[EfASync] unknown type %d\n", eff_type);
        __assert("efasync.c", 0xF6U, "0");
        break;
    }
    va_end(sp80);
    if ((HSD_GObj_804D7838 != NULL) && (HSD_GObj_804D7838->s_link < 9U)) {
        ef_unkstruct3_1->next = ((ef_UnkStruct3*) arg1)->next;
        ((ef_UnkStruct3*) arg1)->next = ef_unkstruct3_1;
        return;
    }
    efAsync_8006744C(gobj, ef_unkstruct3_1);
}

void efAsync_80067980(void)
{
    HSD_ObjAllocInit(&efSync_80458FA0,
                     sizeof(struct efAsync_80067980_objalloc_t), 4U);
    // HSD_ObjAllocInit(&efSync_80458FA0, sizeof(struct ef_UnkStruct3), 4U);
}
