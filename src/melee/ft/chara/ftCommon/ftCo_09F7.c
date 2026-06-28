#include "ftCo_09F7.h"

#include <placeholder.h>

#include "ef/efasync.h"
#include "ft/fighter.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include <math.h>
#include <trigf.h>
#include <baselib/gobj.h>
#include <melee/ft/ftcmdscript.h>

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

/*  args:
gobj
gfx_id
bone
use_common_bone_id
destroy_on_state_change
offset
range
*/
void ftCo_8009F834(Fighter_GObj* gobj, int arg1, enum Fighter_Part arg2,
                   int arg3, int arg4, Vec3* arg5, Vec3* arg6, f32 arg7)
{
    Vec3 spA8;
    Vec3 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    Vec3 sp84;
    f32 sp80;
    f32 sp7C;
    int gfx_id;
    Fighter* fp;
    Fighter* temp_r9;
    Fighter* temp_r9_2;
    enum Fighter_Part part;
    f32 temp_f1;
    f32 scale_y;
    f32 temp_f2;
    f32 z_range;
    f32 floor_angle;
    f32 random_or_angle;
    u8 temp_r3;
    PAD_STACK(68);

    gfx_id = arg1;
    part = arg2;
    fp = gobj->user_data;
    if (arg4 == 0) {
        goto block_2;
    }
    fp->x2219_b0 = true;
block_2:
    if (part != 0x8D) {
        goto block_5;
    }

    part = ((int*) fp->ft_data->x54)[fp->x2220_b0];

    fp->x2220_b0++;
    if (fp->x2220_b0 < 5) {
        goto block_9;
    }
    fp->x2220_b0 = 0;
    goto block_9;
block_5:
    if (part != 0x8E) {
        goto block_7;
    }
    part = fp->ft_data->x8->x10;
    goto block_9;
block_7:
    if (arg3 == 0) {
        goto block_9;
    }
    part = ftParts_GetBoneIndex(fp, part);
block_9:
    if (gfx_id < 0x250) {
        goto block_11;
    }
    if ((gfx_id / 1000) != 0x1E) {
        goto block_12;
    }
block_11:
    spA8 = *arg5;
    spA8.x += 2.0f * arg6->x * (HSD_Randf() - 0.5f);
    spA8.y += 2.0f * arg6->y * (HSD_Randf() - 0.5f);
    temp_f1 = HSD_Randf() - 0.5f;
    temp_f2 = 2.0f * arg6->z;
    spA8.z += temp_f2 * temp_f1;
    temp_r9 = gobj->user_data;
    efAsync_Spawn(gobj, &temp_r9->x60C, 2, gfx_id, fp->parts[part].joint,
                  &spA8);
    return;
block_12:
    switch (gfx_id) {
    case 0x402:
    case 0x403:
    case 0x409:
    case 0x412:
    case 0x413:
    case 0x414:
    case 0x422:
    case 0x487:
    case 0x4D1:
    case 0x4E5:
    case 0x4E6:
    case 0x4FE:
    case 0x500:
    case 0x501:
    case 0x502:
        goto block_61;
    case 0x446:
    case 0x448:
    case 0x4E1:
        goto block_62;
    case 0x415:
    case 0x41E:
    case 0x428:
    case 0x429:
    case 0x42A:
        goto block_63;
    case 0x495:
        goto block_64;
    case 0x49D:
        goto block_65;
    case 0x438:
    case 0x439:
        goto block_66;
    case 0x423:
    case 0x424:
    case 0x4C1:
    case 0x4C2:
    case 0x4C4:
    case 0x4C5:
        goto block_67;
    default:
        goto block_70;
    }
block_61:
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 0, gfx_id,
                  fp->parts[part].joint);
    return;
block_62:
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 7, gfx_id,
                  fp->parts[part].joint, arg5);
    return;
block_63:
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 3, gfx_id,
                  fp->parts[part].joint, &fp->ft_data->x0->x168);
    return;
block_64: {
    HSD_JObj* joint = fp->parts[part].joint;
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 3, gfx_id, joint,
                  &fp->facing_dir);
}
    return;
block_65:
    sp9C = *arg5;
    sp98 = 0.017453292f * (256.0f * arg6->x);
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 6, gfx_id,
                  fp->parts[part].joint, &sp9C, &fp->facing_dir, &sp98);
    return;
block_66:
    scale_y = fp->x34_scale.y;
    sp94 = scale_y * fp->co_attrs.x144;
    temp_r9_2 = gobj->user_data;
    efAsync_Spawn(gobj, &temp_r9_2->x60C, 3, 0x438, fp->parts[part].joint,
                  &sp94);
    return;
block_67:
    sp90 = 0.0f;
    if (fp->ground_or_air != GA_Ground) {
        goto block_69;
    }
    floor_angle =
        atan2f(-fp->coll_data.floor.normal.x, fp->coll_data.floor.normal.y);
    sp90 = floor_angle;
block_69:
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 3, gfx_id,
                  fp->parts[part].joint, &sp90);
    return;
block_70:
    sp84 = *arg5;
    sp84.x += 2.0f * arg6->x * (HSD_Randf() - 0.5f);
    sp84.y += 2.0f * arg6->y * (HSD_Randf() - 0.5f);
    random_or_angle = HSD_Randf() - 0.5f;
    z_range = 2.0f * arg6->z;
    sp84.z += random_or_angle * z_range;
    if (gfx_id >= 0x412) {
        goto block_98;
    }
    if (gfx_id == 0x3FD) {
        goto block_131;
    }
    if (gfx_id >= 0x3FD) {
        goto block_87;
    }
    if (gfx_id >= 0x3F3) {
        goto block_81;
    }
    if (gfx_id == 0x3ED) {
        goto block_130;
    }
    if (gfx_id >= 0x3ED) {
        goto block_79;
    }
    if (gfx_id == 0x3E8) {
        goto block_122;
    }
    if (gfx_id >= 0x3E8) {
        goto block_123;
    }
    goto block_134;
block_79:
    if (gfx_id >= 0x3EF) {
        goto block_130;
    }
    goto block_134;
block_81:
    if (gfx_id == 0x3F6) {
        goto block_123;
    }
    if (gfx_id >= 0x3F6) {
        goto block_85;
    }
    if (gfx_id >= 0x3F5) {
        goto block_130;
    }
    goto block_123;
block_85:
    if (gfx_id >= 0x3FA) {
        goto block_123;
    }
    goto block_131;
block_87:
    if (gfx_id == 0x405) {
        goto block_123;
    }
    if (gfx_id >= 0x405) {
        goto block_94;
    }
    if (gfx_id >= 0x402) {
        goto block_92;
    }
    if (gfx_id == 0x3FF) {
        goto block_131;
    }
    goto block_130;
block_92:
    if (gfx_id >= 0x404) {
        goto block_124;
    }
    goto block_134;
block_94:
    if (gfx_id == 0x407) {
        goto block_123;
    }
    if (gfx_id < 0x407) {
        goto block_124;
    }
    if (gfx_id >= 0x40C) {
        goto block_123;
    }
    goto block_134;
block_98:
    if (gfx_id == 0x44B) {
        goto block_123;
    }
    if (gfx_id >= 0x44B) {
        goto block_112;
    }
    if (gfx_id == 0x41F) {
        goto block_123;
    }
    if (gfx_id >= 0x41F) {
        goto block_107;
    }
    if (gfx_id >= 0x41C) {
        goto block_105;
    }
    if (gfx_id == 0x416) {
        goto block_123;
    }
    goto block_134;
block_105:
    if (gfx_id >= 0x41E) {
        goto block_134;
    }
    goto block_123;
block_107:
    if (gfx_id >= 0x425) {
        goto block_110;
    }
    if (gfx_id == 0x421) {
        goto block_123;
    }
    goto block_134;
block_110:
    if (gfx_id >= 0x427) {
        goto block_134;
    }
    goto block_123;
block_112:
    if (gfx_id == 0x513) {
        goto block_127;
    }
    if (gfx_id >= 0x513) {
        goto block_119;
    }
    if (gfx_id >= 0x4E2) {
        goto block_117;
    }
    if (gfx_id == 0x4D9) {
        goto block_130;
    }
    goto block_134;
block_117:
    if (gfx_id >= 0x4E5) {
        goto block_134;
    }
    goto block_123;
block_119:
    if (gfx_id == 0x515) {
        goto block_129;
    }
    if (gfx_id >= 0x515) {
        goto block_134;
    }
    goto block_128;
block_122:
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 5, gfx_id,
                  fp->parts[part].joint, &sp84, &p_ftCommonData->x564);
    return;
block_123: {
    HSD_JObj* joint = fp->parts[part].joint;
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 2, gfx_id, joint, &sp84);
}
    return;
block_124:
    sp80 = 0.0f;
    if (fp->ground_or_air != GA_Ground) {
        goto block_126;
    }
    random_or_angle =
        atan2f(-fp->coll_data.floor.normal.x, fp->coll_data.floor.normal.y);
    sp80 = random_or_angle;
block_126: {
    HSD_JObj* joint = fp->parts[part].joint;
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 5, gfx_id, joint, &sp84,
                  &sp80);
}
    return;
block_127:
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 8, 2, fp->parts[part].joint,
                  &sp84);
    return;
block_128:
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 8, 3, fp->parts[part].joint,
                  &sp84);
    return;
block_129:
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 8, 4, fp->parts[part].joint,
                  &sp84);
    return;
block_130:
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 5, gfx_id,
                  fp->parts[part].joint, &sp84, &fp->facing_dir);
    return;
block_131:
    sp7C = 0.0f;
    if (fp->ground_or_air != GA_Ground) {
        goto block_133;
    }
    random_or_angle =
        atan2f(-fp->coll_data.floor.normal.x, fp->coll_data.floor.normal.y);
    sp7C = random_or_angle;
block_133:
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 6, gfx_id,
                  fp->parts[part].joint, &sp84, &fp->facing_dir, &sp7C);
    return;
block_134:
    OSReport("no effect from animlist %d\n", gfx_id);
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
