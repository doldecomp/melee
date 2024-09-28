#include "db_2253__static.h"

#include <dolphin/mtx/types.h>
#include <dolphin/mtx/vec.h>
#include <baselib/controller.h>
#include <MSL/trigf.h>

/* 4D6B50 */ static IntVec2 lbl_804D6B50;
/* 453004 */ extern UNK_T cm_80453004;
/* 4D6B5C */ extern s8 lbl_804D6B5C;

/// #db_80225374

/// #db_802254B8

/// #fn_8022558C

/// #fn_802255A4

/// #fn_802255BC

/// #db_802255D4

/// #db_802256CC

/// #db_80225754

/// #fn_80225A00

/// #fn_80225A54

/// #db_80225B0C

/// #db_80225B20

/// #db_80225B34

/// #fn_80225B48

/// #fn_80225B9C

/// #fn_80225BF0

/// #fn_80225C44

/// #fn_80225C8C

/// #fn_80225CD4

s32 db_80225D1C(void)
{
    return lbl_8049FAA0.unk_14;
}

/// #db_80225D2C

/// #db_80225D40

s32 db_80225D54(HSD_ObjAllocUnk4* arg0)
{
    return lbl_8049FAA0.unk_8;
}

/// #db_80225D64

/// #fn_80225D7C

/// #db_80225DD8

/// #fn_80225E6C

/// #fn_80225F20

/// #fn_802260D4

/// #fn_802261BC

/// #fn_802262E0

/// #fn_802264C4

/// #fn_8022659C

/// #fn_8022666C

/// #fn_80226730

/// #fn_802267C8

/// #fn_802268B8

/// #fn_8022697C

/// #fn_802269C0

/// #fn_80226BD4

void fn_80226E00(void)
{
    lbl_804D6B50.x = 0;
}

/// #fn_80226E0C

/// #fn_802270C4

/// #fn_8022713C

/// #fn_80227174

/// #fn_80227188

/// #fn_80227484

/// #fn_802277E8

/// #fn_80227904
void fn_80227904(HSD_GObj* camera, s8 port)
{
    f32 var_f1;
    f32 var_f2;
    f32 var_f2_2;
    f32 var_f3;
    u32 temp_r4;

    var_f2 = HSD_PadMasterStatus[port].nml_subStickX;
    if (var_f2 < 0.0f) {
        var_f1 = -var_f2;
    } else {
        var_f1 = var_f2;
    }
    if (var_f1 < 0.2f) {
        var_f2 = 0.0f;
    }
    var_f3 = HSD_PadMasterStatus[port].nml_subStickY;
    if (var_f3 < 0.0f) {
        var_f2_2 = -var_f3;
    } else {
        var_f2_2 = var_f3;
    }
    if (var_f2_2 < 0.2f) {
        var_f3 = 0.0f;
    }
    temp_r4 = HSD_PadMasterStatus[port].button;

    if (temp_r4 & 1) {
        fn_80227CAC(camera, var_f3);
    } else if (temp_r4 & 2) {
        fn_80227FE0(camera, -var_f2, -var_f3);
    } else {
        fn_80227B64(camera, var_f2, var_f3);
    }
    lbl_804D6B5C = 0x3C;
}
/// #fn_802279E8

/// #fn_80227B64
void fn_80227B64(HSD_GObj* camera, f32 cstick_x, f32 cstick_y)
{
    if ((cstick_x != 0.0f) || (cstick_y != 0.0f)) {
        fn_802279E8(camera, (Vec3*) &cm_80453004 + 0x6,
                    (Vec3*) &cm_80453004 + 0x5, cstick_x, cstick_y);
    }
}
/// #fn_80227BA8

/// #fn_80227CAC
void fn_80227CAC(HSD_GObj* camera, f32 cstick_y)
{
    Vec3 sp14;
    UNK_T sp10;
    s32 temp_cr0_eq;
    void* temp_r31;

    temp_cr0_eq = cstick_y == 0.0f;
    if ((temp_cr0_eq != 0) && (temp_cr0_eq != 0)) {
        temp_r31 = camera->hsd_obj;
        HSD_CObjGetEyeVector((HSD_CObj*) temp_r31, &sp14);
        PSVECScale(&sp14, &sp14,
                   HSD_CObjGetEyeDistance((HSD_CObj*) temp_r31) *
                       -((0.05f * cstick_y) - 1.0f));
        PSVECSubtract((Vec3*) &cm_80453004 + 0x5, &sp14,
                      (Vec3*) &cm_80453004 + 0x6);
    }
}

/// #fn_80227D38

/// #fn_80227EB0

/// #fn_80227FE0
void fn_80227FE0(HSD_GObj* camera, f32 cstick_x, f32 cstick_y)
{
    Vec3 sp24;
    Vec3 sp18;
    UNK_T sp20;
    Vec3* temp_r3;
    Vec3* temp_r3_2;
    Vec3* temp_r3_3;
    Vec3* temp_r3_4;
    f32 temp_f31;
    f32 temp_f31_2;
    void* temp_r30;

    if ((cstick_x != 0.0f) || (cstick_y != 0.0f)) {
        temp_r30 = camera->hsd_obj;
        temp_f31 = HSD_CObjGetEyeDistance((HSD_CObj*) temp_r30);
        temp_f31_2 =
            0.03f *
            (2.0f *
             (temp_f31 * tanf(0.017453292f *
                              HSD_CObjGetFov((HSD_CObj*) temp_r30) * 0.5f)));
        if (cstick_x != 0.0f) {
            HSD_CObjGetLeftVector((HSD_CObj*) temp_r30, &sp18);
            PSVECScale(&sp18, &sp18, temp_f31_2 * cstick_x);
            temp_r3 = (Vec3*) &cm_80453004 + 0x5;
            PSVECAdd(temp_r3, &sp18, temp_r3);
            temp_r3_2 = (Vec3*) &cm_80453004 + 0x6;
            PSVECAdd(temp_r3_2, &sp18, temp_r3_2);
        }
        if (cstick_y != 0.0f) {
            HSD_CObjGetUpVector((HSD_CObj*) temp_r30, &sp24);
            PSVECScale(&sp24, &sp24, -temp_f31_2 * cstick_y);
            temp_r3_3 = (Vec3*) &cm_80453004 + 0x5;
            PSVECAdd(temp_r3_3, &sp24, temp_r3_3);
            temp_r3_4 = (Vec3*) &cm_80453004 + 0x6;
            PSVECAdd(temp_r3_4, &sp24, temp_r3_4);
        }
    }
}
/// #fn_80228124

/// #fn_80228318

/// #fn_802283F0

/// #fn_80228620

/// #fn_8022873C

/// #fn_802287C4

/// #fn_802287D8

/// #fn_80228820

extern s32 lbl_804D6B90;
extern s32 lbl_804D6B94;

void db_8022886C(void)
{
    lbl_804D6B94 = 0;
    lbl_804D6B90 = 0;
}

/// #db_8022887C

/// #db_8022892C

/// #fn_802289F8

/// #db_80228A64

/// #fn_80228AB4

/// #fn_80228B28

/// #db_80228C4C

/// #fn_80228CF4

/// #fn_80228D18

/// #fn_80228D38

/// #fn_80228E54

/// #fn_8022900C

/// #fn_802291A0

/// #fn_80229220

/// #fn_80229240
