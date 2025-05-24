#include "db_2253.static.h"

#include "lb/lbarchive.h"

#include <common_structs.h>
#include <dolphin/card/CARDMount.h>
#include <dolphin/mtx/types.h>
#include <dolphin/mtx/vec.h>
#include <dolphin/vi/vi.h>
#include <baselib/controller.h>
#include <MSL/trigf.h>

void db_80225374(void)
{
    PADStatus status[4];
    s32 memSize;
    s32 sectorSize;
    int done;
    int pad;

    do {
        VIWaitForRetrace();
        PADRead(status);
        done = 1;
        for (pad = 0; pad < 4; ++pad) {
            if (status[pad].err == -2 || status[pad].err == -3) {
                done = 0;
            }
        }
    } while (!done);

    for (pad = 0; pad < 4; ++pad) {
        if (status[pad].err == 0) {
            break;
        }
    }

    db_804D6B30 = (pad != 4) ? status[pad].button : 0;

    while (CARDProbeEx(0, &memSize, &sectorSize) == -1) {
        VIWaitForRetrace();
    }
}

void db_802254B8(void)
{
    struct {
        char** bonus_names;
        char** motionstate_names;
        char** submotion_names;
    }* commonData;
    int stack[2];

    if (g_debugLevel >= 3) {
        db_8049FA00[0].x10 = 0;
        db_8049FA00[0].xC = 0;
        db_8049FA00[0].x8 = 0;
        db_8049FA00[0].x0 = 0;

        db_8049FA00[1].x10 = 0;
        db_8049FA00[1].xC = 0;
        db_8049FA00[1].x8 = 0;
        db_8049FA00[1].x0 = 0;

        db_8049FA00[2].x10 = 0;
        db_8049FA00[2].xC = 0;
        db_8049FA00[2].x8 = 0;
        db_8049FA00[2].x0 = 0;

        db_8049FA00[3].x10 = 0;
        db_8049FA00[3].xC = 0;
        db_8049FA00[3].x8 = 0;
        db_8049FA00[3].x0 = 0;

        lbArchive_80016C64("DbCo.dat", (void**) &commonData,
                           "dbLoadCommonData", 0);

        bonus_names = commonData->bonus_names;
        motionstate_names = commonData->motionstate_names;
        submotion_names = commonData->submotion_names;

        fn_8022659C();
        fn_802267C8();
        fn_80225A00();
        fn_80228318();
        fn_80226E00();
        fn_80227174();
        fn_80228CF4();
        fn_80229220();
        fn_802287C4();
    }
}

/// #fn_8022558C

/// #fn_802255A4

/// #fn_802255BC

/// #db_802255D4

/// #db_802256CC

/// #db_80225754

/// #fn_80225A00

/// #fn_80225A54

u32 db_80225B0C(void)
{
    return db_8049FAA0.x20.b0;
}

u32 db_80225B20(void)
{
    return db_8049FAA0.x20.b1;
}

u32 db_80225B34(void)
{
    return db_8049FAA0.x20.b2;
}

/// #fn_80225B48

/// #fn_80225B9C

/// #fn_80225BF0

/// #fn_80225C44

/// #fn_80225C8C

/// #fn_80225CD4

s32 db_80225D1C(void)
{
    return db_8049FAA0.x14;
}

void db_80225D2C(void)
{
    db_8049FAA0.x8 = 0;
}

void db_80225D40(void)
{
    db_8049FAA0.x8 = 1;
}

s32 db_80225D54(HSD_ObjAllocUnk4* arg0)
{
    return db_8049FAA0.x8;
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
    db_804D6B50 = 0;
}

/// #fn_80226E0C

/// #fn_802270C4

/// #fn_8022713C

void fn_80227174(void)
{
    db_804D6B58 = NULL;
    db_804D6B5C = 0;
    db_804D6B5D = 0;
}

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
    db_804D6B5C = 0x3C;
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

void fn_802287C4(void)
{
    db_804D6B8C.b0 = false;
}

/// #fn_802287D8

/// #fn_80228820

void db_8022886C(void)
{
    db_804D6B94 = 0;
    db_804D6B90 = 0;
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
