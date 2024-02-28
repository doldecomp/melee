#include <platform.h>

typedef struct _SisLibUnkStruct2 {
    /*0x00*/ u8 x0_padding[0x8 - 0x0];
    /*0x08*/ u8* x08_arr; // Unknown length as of right now
} SisLibUnkStruct2;

typedef struct _SisLibUnkStruct {
    /*0x00*/ u8 x0_padding[0xC - 0x0];
    /*0x0C*/ SisLibUnkStruct2* x0C_ptr;
    /*0x10*/ u8 x10_padding[0x14 - 0x10];
} SisLibUnkStruct;

typedef struct _gmCameraUnkStruct3 {
    /*0x00*/ u8 x0_padding[0x24 - 0x0];
    /*0x24*/ float x24;
    /*0x28*/ float x28;
    /*0x2C*/ u8 x2C_padding[0x49 - 0x2C];
    /*0x49*/ u8 x49;
} gmCameraUnkStruct3;

typedef struct _gmCameraUnkStruct2 {
    /*0x00*/ u8 x0_padding[0x24 - 0x0];
    /*0x24*/ u32 x24;
    /*0x28*/ u32 x28;
    /*0x2C*/ int x2C;
    /*0x30*/ u32 x30;
} gmCameraUnkStruct2;

typedef struct _gmCameraUnkStruct {
    /*0x00*/ u8 x0_padding[0x20 - 0x0];
    /*0x20*/ u32 x20;
    /*0x24*/ u32 x24;
    /*0x28*/ u8 x28_padding[0x54 - 0x28];
    /*0x54*/ u32 x54;
} gmCameraUnkStruct;

typedef struct _gmCameraUnkStructPtrs {
    /*0x00*/ u8 x0_padding[0x58 - 0x0];
} gmCameraUnkStruct2Ptrs;

union _gmCameraUnkUnion {
    gmCameraUnkStruct gcus;
    // gmCameraUnkStruct2* gcus2_ptrs[0x58/4];
    gmCameraUnkStruct2Ptrs gcus2_ptrs;
};

/// @todo #HSD_SisLib_804D1124 is of type #SIS.
extern SisLibUnkStruct HSD_SisLib_804D1124;

u8* gmCamera_801A2224(u8* arg0, u32 arg1)
{
    u32 masked_arg1;
    u32 cond_flag = 0;
    u8* slus2_arr_ptr = (HSD_SisLib_804D1124.x0C_ptr->x08_arr);

    if (arg1 >= 0x2710U) {
        arg1 = 0x270F;
    }

    if (arg1 >= 0x3E8U) {
        masked_arg1 = (arg1 / 500) & 0x07FFFFFE;
        arg0[0] = slus2_arr_ptr[0 + masked_arg1];
        arg0[1] = slus2_arr_ptr[1 + masked_arg1];
        arg1 %= 0x3E8;
        cond_flag = 1U;
        arg0 += 2;
    }
    if ((arg1 >= 0x64U) || (cond_flag != 0)) {
        masked_arg1 = (arg1 / 50) & 0x0FFFFFFE;
        arg0[0] = slus2_arr_ptr[0 + masked_arg1];
        arg0[1] = slus2_arr_ptr[1 + masked_arg1];
        arg1 %= 0x64;
        cond_flag += 1;
        arg0 += 2;
    }
    if ((arg1 >= 0xAU) || (cond_flag != 0)) {
        masked_arg1 = (arg1 / 5) & 0x3FFFFFFE;
        arg0[0] = slus2_arr_ptr[0 + masked_arg1];
        arg0[1] = slus2_arr_ptr[1 + masked_arg1];
        arg1 %= 0xA;
        arg0 += 2;
    }
    *(arg0++) = slus2_arr_ptr[0 + arg1 * 2];
    *(arg0++) = slus2_arr_ptr[1 + arg1 * 2];
    *arg0 = 0;
    return arg0;
}

void* HSD_SisLib_803A5ACC(u8, int, float, float, float); /* extern */
void HSD_SisLib_803A6368(void*, u32);                    /* extern */
void HSD_SisLib_803A6530(u32, u32, u32);                 /* extern */
void HSD_SisLib_803A660C(u32, u32, u32);                 /* extern */

extern union _gmCameraUnkUnion gmCamera_80479BC8;
extern float gmCamera_804DA9B8;
extern float gmCamera_804DA9BC;
extern float gmCamera_804DA9C0;

void* gmCamera_801A2334(int arg0, float argA, float argB)
{
    gmCameraUnkStruct3* temp_r3;
    gmCameraUnkStruct2* temp_r5;
    // gmCameraUnkStruct test;
    u32 var_r30;
    int temp_r4;
    // int temp_r4;
    gmCameraUnkStruct2** tmp_gcus2_ptr_ptr;
    int var_r0;
    u32* temp_r27;
    u32 temp_r0;

    temp_r3 =
        HSD_SisLib_803A5ACC(3, gmCamera_80479BC8.gcus.x54, gmCamera_804DA9B8,
                            gmCamera_804DA9BC, gmCamera_804DA9C0);

    temp_r3->x24 = argA;
    temp_r3->x28 = argB;
    temp_r3->x49 = 1;
    if (arg0 == 0) {
        var_r30 = 6;
        HSD_SisLib_803A6530(3, 6, 8);
    } else {
        var_r30 = 7;
        HSD_SisLib_803A6530(3, 7, 9);
    }
    temp_r4 = arg0 * 0x4;
    // tmp_gcus2_ptr_ptr = (gmCameraUnkStruct2**) (arg0 * 0x4);
    // temp_r5 = &gmCamera_80479BC8 + temp_r4;
    /// TODO: Problem here is around a4 (my code), there is a lwz r5, 0(r3)
    /// where there shouldn't be
    /*
    Target:
    r28 <- gmCamera_80479BC8
    r29 <- r3 (int arg0)
    r6 <- r29 * 0x4 (arg0 * 0x4)
    r5 <- r28 + r6
    r0 <- load r5 + 0x24

    Source:
    r4 <- gmCamera_80479BC8
    r29 <- r3 (int arg0)
    r0 <- r29 * 0x4 (arg0 * 0x4)
    r3 <- r4 + r0
    ***r5 <- load r3 + 0***
    r0 <- load r5 + 0x24
    */
    temp_r5 = (gmCameraUnkStruct2*) ((int) &(gmCamera_80479BC8.gcus2_ptrs) +
                                     temp_r4);
    // temp_r5 = gmCamera_80479BC8.gcus2_ptrs + tmp_gcus2_ptr_ptr;

    // test = gmCamera_80479BC8.gcus;
    // temp_r0 = gmCamera_80479BC8.gcus.x24;
    temp_r0 = temp_r5->x24;
    switch (temp_r0) {
    case 0:
        if ((int) temp_r5->x2C == 0) {
            temp_r5->x30 = 3;
            HSD_SisLib_803A660C(3, var_r30, 0xC);
        } else {
            temp_r27 = &(temp_r5->x28);
            temp_r4 = temp_r5->x28;
            if (temp_r4 == 0) {
                temp_r5->x30 = 2;
                HSD_SisLib_803A660C(3, var_r30, 0xC);
            } else {
                if (temp_r4 >= (int) gmCamera_80479BC8.gcus.x20) {
                    if (arg0 != 0) {
                        var_r0 = 0;
                    } else {
                        var_r0 = 1;
                    }
                } else {
                    var_r0 = 2;
                }
                //(&gmCamera_80479BC8 + temp_r4)->x30 = var_r0;
                // gmCamera_80479BC8.gcus2_ptrs[temp_r4]->x30 = var_r0;
                temp_r5->x30 = var_r0;
                // gmCamera_80479BC8.gcus2_ptrs[temp_r4]->x30 = var_r0;
                gmCamera_801A2224(/* TODO */ (u8*) *temp_r27, /* TODO */ 0);
                if ((int) *temp_r27 != 1) {
                }
                // TODO: Find third argument
                HSD_SisLib_803A660C(3, var_r30, 0xa);
            }
        }
        break;
    case 15:
        temp_r5->x30 = 5;
        HSD_SisLib_803A660C(3, var_r30, 0x10);
        break;
    case 9:
        temp_r5->x30 = 4;
        HSD_SisLib_803A660C(3, var_r30, 0xD);
        break;
    case 12:
        temp_r5->x30 = 4;
        HSD_SisLib_803A660C(3, var_r30, 0xE);
        break;
    default:
        //(&gmCamera_80479BC8 + temp_r4)->x30 = 4;
        // gmCamera_80479BC8.gcus2_ptrs[temp_r4]->x30 = 4;
        temp_r5->x30 = 4;
        HSD_SisLib_803A660C(3, var_r30, 0xF);
        break;
    }
    HSD_SisLib_803A6368(temp_r3, var_r30);
    return temp_r3;
}
