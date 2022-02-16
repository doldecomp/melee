#include <dolphin/types.h>
#include <sysdolphin/baselib/gobj.h>
#include "fighter.h"

extern ftCommonData* lbl_804D6554; // defined in fighter.s

// UnclePunch Map file: Collision_GetPositionDifference(r3=GroundID,r4=XYZCoords,r5=UnkReturnVector)
s32 func_800567C0(s32 /*wallID?*/, Vec3* /*ecb_side_vertex?*/, Vec3* /*result, I looked at the assembly and this is a Vec3*/);

// UnclePunch Map file: AS_203_PassiveWalljump_Walljump
void func_800C1E64(HSD_GObj* pPlayerEntityStruct, s32, s32, u8, f32);

// https://decomp.me/scratch/f74Cl
// UnclePunch Map file: Interrupt_Walljump
BOOL func_8008169C(HSD_GObj* pPlayerEntityStruct/*r3*/)
{
    Fighter* pCharData_r31 = (Fighter*) pPlayerEntityStruct->user_data;
    CollData* pCollData_r6;
    ftCommonData* p_ftcommon_r4;
    s32 some_flag_r0;
    f32 deltaX_f1;
    f32 phi_f31;

    Vec3 some_vec_sp24;
    Vec3 ecb_sp18;
    s32 dummy3[3];

    if (pCharData_r31->x2224_flag.bits.b7)
    {
        pCollData_r6 = &pCharData_r31->x6F0_collData;
        if ((pCharData_r31->x6F0_collData.x134_envFlags/*total offset x824*/ & 0x800) || (pCollData_r6->x134_envFlags & 0x20))
        {
            some_flag_r0 = pCollData_r6->x134_envFlags & 0x800;
            phi_f31 = some_flag_r0 ? -1.0f : 1.0f;// facing direction?

            if ((pCharData_r31->x210C/*stored in r3*/ < 0xFEU) && (phi_f31 == pCharData_r31->x2110))
            {
                pCharData_r31->x210C = (u8) (pCharData_r31->x210C/*stored in r3*/ + 1);
            }
            else
            {
                if (some_flag_r0)
                {
                    ecb_sp18.x = pCollData_r6->xBC_ecbCurrCorrect_left.x;
                    ecb_sp18.y = pCollData_r6->xBC_ecbCurrCorrect_left.y;
                    ecb_sp18.z = 0.0f;
                    ecb_sp18.x += pCharData_r31->xB0_pos.x;
                    ecb_sp18.y += pCharData_r31->xB0_pos.y;
                    ecb_sp18.z += pCharData_r31->xB0_pos.z;
                    if (!func_800567C0(pCollData_r6->x174_leftwall_index, &ecb_sp18, &some_vec_sp24))
                        some_vec_sp24.x = 0.0f;
                }
                else
                {
                    ecb_sp18.x = pCollData_r6->xB4_ecbCurrCorrect_right.x;
                    ecb_sp18.y = pCollData_r6->xB4_ecbCurrCorrect_right.y;
                    ecb_sp18.z = 0.0f;
                    ecb_sp18.x += pCharData_r31->xB0_pos.x;
                    ecb_sp18.y += pCharData_r31->xB0_pos.y;
                    ecb_sp18.z += pCharData_r31->xB0_pos.z;
                    if (!func_800567C0(pCollData_r6->x160_rightwall_index, &ecb_sp18, &some_vec_sp24))
                        some_vec_sp24.x = 0.0f;
                }
                deltaX_f1 = pCharData_r31->xC8_pos_delta.x - some_vec_sp24.x;
                deltaX_f1 = (deltaX_f1 < 0.0f) ? -deltaX_f1 : deltaX_f1;
                if (deltaX_f1 > pCharData_r31->x258)
                {
                    pCharData_r31->x2110 = phi_f31;
                    pCharData_r31->x210C = 0U;
                }
            }
            p_ftcommon_r4 = lbl_804D6554;
            if (
                    (f32) pCharData_r31->x210C < p_ftcommon_r4->x768 &&
                    (
                        (pCharData_r31->x2110 == -1.0f && pCharData_r31->x620_lstick_x >=  p_ftcommon_r4->x76C) ||
                        (pCharData_r31->x2110 ==  1.0f && pCharData_r31->x620_lstick_x <= -p_ftcommon_r4->x76C)
                    )
                    && (f32)pCharData_r31->x670_timer_lstick_tilt_x < p_ftcommon_r4->x770
                )
            {
                func_800C1E64(pPlayerEntityStruct, 0xCB, p_ftcommon_r4->x774, pCharData_r31->x1969_walljumps_used, pCharData_r31->x2110);
                pCharData_r31->x210C = 0xFEU;
                if (pCharData_r31->x1969_walljumps_used < 0xFFU)
                    pCharData_r31->x1969_walljumps_used++;
                return 1;
            }
        }
        else
        {
            pCharData_r31->x210C = 0xFEU;
        }
    }
    return 0;
}
