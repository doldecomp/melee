#include "gmmenu.h"
#include "dolphin/types.h"
#include "gm/gm_1601.h"
#include "gm/gm_17C0.h"
#include "gm/gm_1A3F.h"
#include "gm/gm_1B03.h"

#include <melee/gm/types.h>

void gm_801A50B8_OnLoad(void)
{
    u8 var_r0;
    struct UnkAllstarData* temp_r3;

    temp_r3 = gm_8017EB30();
    var_r0 = temp_r3->x0;
    if (temp_r3->x0 == 0x12 && temp_r3->xC.x6 != 0) {
        var_r0 = 0x13;
    } else {
        var_r0 = temp_r3->x0;
    }
    gm_801BEFA4(var_r0 & 0xFF);
    gm_801BEFC0(temp_r3->x1);
    gm_801BF000(temp_r3->x3);
    gm_801BEFE0(temp_r3->x4);
    gm_801BF020(1);
}

void gm_801A5130_OnLoad(void)
{
    u8 var_r0;
    struct UnkAllstarData* temp_r3;

    temp_r3 = gm_8017E424();
    var_r0 = temp_r3->x0;
    if (temp_r3->x0 == 0x12 && temp_r3->xC.x6 != 0) {
        var_r0 = 0x13;
    } else {
        var_r0 = temp_r3->x0;
    }
    gm_801BEFA4(var_r0 & 0xFF);
    gm_801BEFC0(temp_r3->x1);
    gm_801BF000(temp_r3->x3);
    gm_801BEFE0(temp_r3->x4);
    gm_801BF020(0);
}

void gm_801A51A8_OnLoad(void)
{
    struct UnkAllstarData* tmp = &gm_80473A18;
    u8 var_r0;

    if (tmp->x0 == 0x12 && tmp->xC.x6 != 0) {
        var_r0 = 0x13;
    } else {
        var_r0 = tmp->x0;
    }
    gm_801BEFA4(var_r0 & 0xFF);
    gm_801BEFC0(tmp->x1);
    gm_801BF000(tmp->x3);
    gm_801BEFE0(tmp->x4);
    gm_801BF020(2);
}

void gm_801A5220_OnLoad(void)
{
    gm_SetSceneMinor(gm_801BF718());
}
