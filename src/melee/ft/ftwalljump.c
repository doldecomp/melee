#include <functions.h>
#include <sysdolphin/baselib/gobj.h>
#include <fighter.h>

extern ftCommonData* p_ftCommonData; // defined in fighter.s
#define p_ftcommon_r4 p_ftCommonData

#define MAX_WALLJUMP_INPUT_FRAMES 254

// https://decomp.me/scratch/f74Cl
// UnclePunch Map file: Interrupt_Walljump
// @Returns: true if this function started a walljump
BOOL func_8008169C(HSD_GObj* pPlayerEntityStruct/*r3*/)
{
    Fighter* fp_r31 = (Fighter*) pPlayerEntityStruct->user_data;
    CollData* pCollData_r6;
    s32 wallSideFlag_r0;
    f32 deltaX_f1;
    f32 wallSide_f31;

    Vec wallPos_sp24;
    Vec ecb_sp18;
    s32 dummy3[3];

	// is a walljump character? is airborne?
    if (fp_r31->x2224_flag.bits.b7)
    {
        pCollData_r6 = &fp_r31->x6F0_collData;
        if ((fp_r31->x6F0_collData.x134_envFlags & 0x800) || (pCollData_r6->x134_envFlags & 0x20))
        {
            wallSideFlag_r0 = pCollData_r6->x134_envFlags & 0x800;
            wallSide_f31 = wallSideFlag_r0 ? -1.0f : 1.0f; // side of the collision?

			// x210C_walljumpInputTimer = some walljump animation/input timer?
			// is initialized in the else-block when the user does the right inputs.
			// gets incremented here every frame.
            if ((fp_r31->x210C_walljumpInputTimer < MAX_WALLJUMP_INPUT_FRAMES) && (wallSide_f31 == fp_r31->x2110_walljumpWallSide))
            {
                fp_r31->x210C_walljumpInputTimer++;
            }
            else
            {
                if (wallSideFlag_r0)
                {
					// compute absolte position of the ECB's left vertex?
                    ecb_sp18.x = pCollData_r6->xBC_ecbCurrCorrect_left.x;
                    ecb_sp18.y = pCollData_r6->xBC_ecbCurrCorrect_left.y;
                    ecb_sp18.z = 0.0f;
                    ecb_sp18.x += fp_r31->xB0_pos.x;
                    ecb_sp18.y += fp_r31->xB0_pos.y;
                    ecb_sp18.z += fp_r31->xB0_pos.z;
					// compute distance to the wall?
                    if (!func_800567C0(pCollData_r6->x174_leftwall_index, &ecb_sp18, &wallPos_sp24))
                        wallPos_sp24.x = 0.0f;
                }
                else
                {
					// compute absolte position of the ECB's right vertex?
                    ecb_sp18.x = pCollData_r6->xB4_ecbCurrCorrect_right.x;
                    ecb_sp18.y = pCollData_r6->xB4_ecbCurrCorrect_right.y;
                    ecb_sp18.z = 0.0f;
                    ecb_sp18.x += fp_r31->xB0_pos.x;
                    ecb_sp18.y += fp_r31->xB0_pos.y;
                    ecb_sp18.z += fp_r31->xB0_pos.z;
					// compute distance to the wall?
                    if (!func_800567C0(pCollData_r6->x160_rightwall_index, &ecb_sp18, &wallPos_sp24))
                        wallPos_sp24.x = 0.0f;
                }
				// not sure what this computes, I guess it checks if we are close to the wall and move towards it with sufficent speed
                deltaX_f1 = fp_r31->xC8_pos_delta.x - wallPos_sp24.x;
                deltaX_f1 = (deltaX_f1 < 0.0f) ? -deltaX_f1 : deltaX_f1;
                if (deltaX_f1 > fp_r31->x110_attr.x258)
                {
					// walljump input phase one completed, now start the walljump input timer
					// and check for the control stick movement away from the wall in the next phase
                    fp_r31->x2110_walljumpWallSide = wallSide_f31;
                    fp_r31->x210C_walljumpInputTimer = 0U;
                }
            }
            if (
                    (f32)fp_r31->x210C_walljumpInputTimer < p_ftcommon_r4->x768 && // walljump timer within limits?
                    (
                        (fp_r31->x2110_walljumpWallSide == -1.0f && fp_r31->input.x620_lstick_x >=  p_ftcommon_r4->x76C) || // left wall & control stick right?
                        (fp_r31->x2110_walljumpWallSide ==  1.0f && fp_r31->input.x620_lstick_x <= -p_ftcommon_r4->x76C)    // right wal & control stick left?
                    )
                    && (f32)fp_r31->x670_timer_lstick_tilt_x < p_ftcommon_r4->x770 // control stick didn't stay too long in the tilt area?
                )
            {
				// do a walljump!
                func_800C1E64(pPlayerEntityStruct, 0xCB, p_ftcommon_r4->x774, fp_r31->x1969_walljumpUsed, fp_r31->x2110_walljumpWallSide);
                fp_r31->x210C_walljumpInputTimer = MAX_WALLJUMP_INPUT_FRAMES;
                if (fp_r31->x1969_walljumpUsed < 255)
                    fp_r31->x1969_walljumpUsed++;
                return 1;
            }
        }
        else
        {
            fp_r31->x210C_walljumpInputTimer = MAX_WALLJUMP_INPUT_FRAMES;
        }
    }
    return 0;
}
