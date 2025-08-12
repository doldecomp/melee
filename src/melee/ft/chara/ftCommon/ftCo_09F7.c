#include <placeholder.h>

#include "ftCommon/forward.h"

#include "ftCo_09F7.h"

#include "ftCo_0B3E.h"

#include "ef/efasync.h"
#include "ft/fighter.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include <math.h>
#include <trigf.h>
#include <baselib/gobj.h>

#pragma force_active on

float const ftCo_804D87C0 = 2;
float const ftCo_804D87C4 = 0.5;
float const ftCo_804D87C8 = deg_to_rad;
float const ftCo_804D87CC = 256;
float const ftCo_804D87D0 = 0;
char ftDynamics_803C57B0[] = "no effect from animlist %d\n";

struct _m2c_stack_ftCo_8009F834 {
    /* 0x00 */ char pad_0[0x7C];
    /* 0x7C */ f32 sp7C; /* inferred */
    /* 0x80 */ f32 sp80; /* inferred */
    /* 0x84 */ f32 sp84; /* inferred */
    /* 0x88 */ f32 sp88; /* inferred */
    /* 0x8C */ f32 sp8C; /* inferred */
    /* 0x90 */ f32 sp90; /* inferred */
    /* 0x94 */ f32 sp94; /* inferred */
    /* 0x98 */ f32 sp98; /* inferred */
    /* 0x9C */ f32 sp9C; /* inferred */
    /* 0xA0 */ f32 spA0; /* inferred */
    /* 0xA4 */ f32 spA4; /* inferred */
    /* 0xA8 */ f32 spA8; /* inferred */
    /* 0xAC */ f32 spAC; /* inferred */
    /* 0xB0 */ f32 spB0; /* inferred */
    /* 0xB4 */ char pad_B4[0x1C];
}; /* size = 0xD0 */

void ftCo_8009F834(Fighter_GObj* gobj, int arg1, enum Fighter_Part arg2,
                   int arg3, int arg4, Vec3* arg5, Vec3* arg6, f32 arg7)
{
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    Fighter* temp_r30;
    Fighter* temp_r9;
    Fighter* temp_r9_2;
    enum Fighter_Part temp_ret;
    enum Fighter_Part var_r27;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 var_f1;
    f32 var_f1_2;
    u8 temp_r3;

    var_f1 = arg7;
    var_r27 = arg2;
    temp_r30 = gobj->user_data;
    if (arg4 == 0) {
        goto block_2;
    }
    temp_r30->x2219_b0 = true;
block_2:
    if (var_r27 != 0x8D) {
        goto block_5;
    }

    var_r27 = temp_r30->ft_data->x54 + temp_r30->x2220_b0;

    temp_r30->x2220_b0++;
    if (temp_r30->x2220_b0 < 5) {
        goto block_9;
    }
    temp_r30->x2220_b0 = 0;
    goto block_9;
block_5:
    if (var_r27 != 0x8E) {
        goto block_7;
    }
    var_r27 = temp_r30->ft_data->x8->x10;
    goto block_9;
block_7:
    if (arg3 == 0) {
        goto block_9;
    }
    temp_ret = ftParts_GetBoneIndex(temp_r30, var_r27);
    var_f1 = M2C_BITWISE(f32, temp_ret);
    var_r27 = temp_ret;
block_9:
    if (arg1 < 0x250) {
        goto block_11;
    }
    if ((arg1 / 1000) != 0x1E) {
        goto block_12;
    }
block_11:
    spA8 = arg5->x;
    spAC = arg5->y;
    spB0 = arg5->z;
    spA8 += 2.0f * arg6->x * (HSD_Randf() - 0.5f);
    spAC += 2.0f * arg6->y * (HSD_Randf() - 0.5f);
    temp_f1 = HSD_Randf() - 0.5f;
    temp_f2 = 2.0f * arg6->z;
    spB0 += temp_f2 * temp_f1;
    temp_r9 = gobj->user_data;
    efAsync_Spawn(gobj, &temp_r9->x60C, 2, arg1,
                  temp_r30->parts[var_r27].joint, &spA8, temp_r9, temp_f1,
                  temp_f2, 2.0f);
    return;
block_12:
    if (arg1 == 0x487) {
        goto block_61;
    }
    if (arg1 >= 0x487) {
        goto block_40;
    }
    if (arg1 == 0x422) {
        goto block_61;
    }
    if (arg1 >= 0x422) {
        goto block_27;
    }
    if (arg1 >= 0x412) {
        goto block_22;
    }
    if (arg1 == 0x409) {
        goto block_61;
    }
    if (arg1 >= 0x409) {
        goto block_70;
    }
    if (arg1 >= 0x404) {
        goto block_70;
    }
    if (arg1 >= 0x402) {
        goto block_61;
    }
    goto block_70;
block_22:
    if (arg1 == 0x41E) {
        goto block_63;
    }
    if (arg1 >= 0x41E) {
        goto block_70;
    }
    if (arg1 == 0x415) {
        goto block_63;
    }
    if (arg1 >= 0x415) {
        goto block_70;
    }
    goto block_61;
block_27:
    if (arg1 >= 0x43A) {
        goto block_34;
    }
    if (arg1 >= 0x42B) {
        goto block_32;
    }
    if (arg1 >= 0x428) {
        goto block_63;
    }
    if (arg1 >= 0x425) {
        goto block_70;
    }
    goto block_67;
block_32:
    if (arg1 >= 0x438) {
        goto block_66;
    }
    goto block_70;
block_34:
    if (arg1 == 0x447) {
        goto block_70;
    }
    if (arg1 >= 0x447) {
        goto block_38;
    }
    if (arg1 >= 0x446) {
        goto block_62;
    }
    goto block_70;
block_38:
    if (arg1 >= 0x449) {
        goto block_70;
    }
    goto block_62;
block_40:
    if (arg1 == 0x4D1) {
        goto block_61;
    }
    if (arg1 >= 0x4D1) {
        goto block_51;
    }
    if (arg1 >= 0x4C1) {
        goto block_47;
    }
    if (arg1 == 0x49D) {
        goto block_65;
    }
    if (arg1 >= 0x49D) {
        goto block_70;
    }
    if (arg1 == 0x495) {
        goto block_64;
    }
    goto block_70;
block_47:
    if (arg1 == 0x4C3) {
        goto block_70;
    }
    if (arg1 < 0x4C3) {
        goto block_67;
    }
    if (arg1 >= 0x4C6) {
        goto block_70;
    }
    goto block_67;
block_51:
    if (arg1 == 0x4FE) {
        goto block_61;
    }
    if (arg1 >= 0x4FE) {
        goto block_58;
    }
    if (arg1 >= 0x4E5) {
        goto block_56;
    }
    if (arg1 == 0x4E1) {
        goto block_62;
    }
    goto block_70;
block_56:
    if (arg1 >= 0x4E7) {
        goto block_70;
    }
    goto block_61;
block_58:
    if (arg1 >= 0x503) {
        goto block_70;
    }
    if (arg1 >= 0x500) {
        goto block_61;
    }
    goto block_70;
block_61:
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 0, arg1,
                  temp_r30->parts[var_r27].joint, var_f1);
    return;
block_62:
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 7, arg1,
                  temp_r30->parts[var_r27].joint, arg5, var_f1);
    return;
block_63:
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 3, arg1,
                  temp_r30->parts[var_r27].joint,
                  &temp_r30->ft_data->x0->x100[0x68], var_f1);
    return;
block_64:
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 3, arg1,
                  temp_r30->parts[var_r27].joint, &temp_r30->facing_dir,
                  var_f1);
    return;
block_65:
    sp9C = arg5->x;
    spA0 = arg5->y;
    spA4 = arg5->z;
    sp98 = 0.017453292f * (256.0f * arg6->x);
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 6, arg1,
                  temp_r30->parts[var_r27].joint, &sp9C, &temp_r30->facing_dir,
                  &sp98, 256.0f, 0.017453292f);
    return;
block_66:
    temp_f1_2 = temp_r30->x34_scale.y;
    sp94 = temp_f1_2 * M2C_BITWISE(f32, temp_r30->co_attrs.x12C);
    temp_r9_2 = gobj->user_data;
    efAsync_Spawn(gobj, &temp_r9_2->x60C, 3, 0x438,
                  temp_r30->parts[var_r27].joint, &sp94, temp_r9_2, temp_f1_2);
    return;
block_67:
    sp90 = 0.0f;
    if (temp_r30->ground_or_air != GA_Ground) {
        goto block_69;
    }
    var_f1 = atan2f(-temp_r30->coll_data.floor.normal.x,
                    temp_r30->coll_data.floor.normal.y);
    sp90 = var_f1;
block_69:
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 3, arg1,
                  temp_r30->parts[var_r27].joint, &sp90, var_f1);
    return;
block_70:
    sp84 = arg5->x;
    sp88 = arg5->y;
    sp8C = arg5->z;
    sp84 += 2.0f * arg6->x * (HSD_Randf() - 0.5f);
    sp88 += 2.0f * arg6->y * (HSD_Randf() - 0.5f);
    var_f1_2 = HSD_Randf() - 0.5f;
    temp_f2_2 = 2.0f * arg6->z;
    sp8C += temp_f2_2 * var_f1_2;
    if (arg1 >= 0x412) {
        goto block_98;
    }
    if (arg1 == 0x3FD) {
        goto block_131;
    }
    if (arg1 >= 0x3FD) {
        goto block_87;
    }
    if (arg1 >= 0x3F3) {
        goto block_81;
    }
    if (arg1 == 0x3ED) {
        goto block_130;
    }
    if (arg1 >= 0x3ED) {
        goto block_79;
    }
    if (arg1 == 0x3E8) {
        goto block_122;
    }
    if (arg1 >= 0x3E8) {
        goto block_123;
    }
    goto block_134;
block_79:
    if (arg1 >= 0x3EF) {
        goto block_130;
    }
    goto block_134;
block_81:
    if (arg1 == 0x3F6) {
        goto block_123;
    }
    if (arg1 >= 0x3F6) {
        goto block_85;
    }
    if (arg1 >= 0x3F5) {
        goto block_130;
    }
    goto block_123;
block_85:
    if (arg1 >= 0x3FA) {
        goto block_123;
    }
    goto block_131;
block_87:
    if (arg1 == 0x405) {
        goto block_123;
    }
    if (arg1 >= 0x405) {
        goto block_94;
    }
    if (arg1 >= 0x402) {
        goto block_92;
    }
    if (arg1 == 0x3FF) {
        goto block_131;
    }
    goto block_130;
block_92:
    if (arg1 >= 0x404) {
        goto block_124;
    }
    goto block_134;
block_94:
    if (arg1 == 0x407) {
        goto block_123;
    }
    if (arg1 < 0x407) {
        goto block_124;
    }
    if (arg1 >= 0x40C) {
        goto block_123;
    }
    goto block_134;
block_98:
    if (arg1 == 0x44B) {
        goto block_123;
    }
    if (arg1 >= 0x44B) {
        goto block_112;
    }
    if (arg1 == 0x41F) {
        goto block_123;
    }
    if (arg1 >= 0x41F) {
        goto block_107;
    }
    if (arg1 >= 0x41C) {
        goto block_105;
    }
    if (arg1 == 0x416) {
        goto block_123;
    }
    goto block_134;
block_105:
    if (arg1 >= 0x41E) {
        goto block_134;
    }
    goto block_123;
block_107:
    if (arg1 >= 0x425) {
        goto block_110;
    }
    if (arg1 == 0x421) {
        goto block_123;
    }
    goto block_134;
block_110:
    if (arg1 >= 0x427) {
        goto block_134;
    }
    goto block_123;
block_112:
    if (arg1 == 0x513) {
        goto block_127;
    }
    if (arg1 >= 0x513) {
        goto block_119;
    }
    if (arg1 >= 0x4E2) {
        goto block_117;
    }
    if (arg1 == 0x4D9) {
        goto block_130;
    }
    goto block_134;
block_117:
    if (arg1 >= 0x4E5) {
        goto block_134;
    }
    goto block_123;
block_119:
    if (arg1 == 0x515) {
        goto block_129;
    }
    if (arg1 >= 0x515) {
        goto block_134;
    }
    goto block_128;
block_122:
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 5, arg1,
                  temp_r30->parts[var_r27].joint, &sp84, &p_ftCommonData->x564,
                  var_f1_2, temp_f2_2, 2.0f);
    return;
block_123:
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 2, arg1,
                  temp_r30->parts[var_r27].joint, &sp84, var_f1_2, temp_f2_2,
                  2.0f);
    return;
block_124:
    sp80 = 0.0f;
    if (temp_r30->ground_or_air != GA_Ground) {
        goto block_126;
    }
    var_f1_2 = atan2f(-temp_r30->coll_data.floor.normal.x,
                      temp_r30->coll_data.floor.normal.y);
    sp80 = var_f1_2;
block_126:
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 5, arg1,
                  temp_r30->parts[var_r27].joint, &sp84, &sp80, var_f1_2);
    return;
block_127:
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 8, 2,
                  temp_r30->parts[var_r27].joint, &sp84, var_f1_2, temp_f2_2,
                  2.0f);
    return;
block_128:
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 8, 3,
                  temp_r30->parts[var_r27].joint, &sp84, var_f1_2, temp_f2_2,
                  2.0f);
    return;
block_129:
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 8, 4,
                  temp_r30->parts[var_r27].joint, &sp84, var_f1_2, temp_f2_2,
                  2.0f);
    return;
block_130:
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 5, arg1,
                  temp_r30->parts[var_r27].joint, &sp84, &temp_r30->facing_dir,
                  var_f1_2, temp_f2_2, 2.0f);
    return;
block_131:
    sp7C = 0.0f;
    if (temp_r30->ground_or_air != GA_Ground) {
        goto block_133;
    }
    var_f1_2 = atan2f(-temp_r30->coll_data.floor.normal.x,
                      temp_r30->coll_data.floor.normal.y);
    sp7C = var_f1_2;
block_133:
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 6, arg1,
                  temp_r30->parts[var_r27].joint, &sp84, &temp_r30->facing_dir,
                  &sp7C, var_f1_2);
    return;
block_134:
    OSReport("no effect from animlist %d\n", arg1);
    return;
}

void ftCo_800A0098(Fighter* arg0)
{
    ftCo_800B46B8(arg0, 0x80, 0);
    ftCo_800B46B8(arg0, 0x81, 0);
    ftCo_800B46B8(arg0, 0x8E, 1);
    ftCo_800B46B8(arg0, 0x91, 0xB0);
    ftCo_800B46B8(arg0, 0x8E, 1);
    ftCo_800B46B8(arg0, 0x81, 0);
    ftCo_800B46B8(arg0, 0x8E, 0xA);
    ftCo_800B46B8(arg0, 0x80, 0);
    ftCo_800B463C(arg0, 0x7F);
}
