#include "ftwalljump.h"

#include "fighter.h"
#include "ft_877.h"
#include "inlines.h"

#include "mp/mplib.h"

#include <dolphin/mtx/types.h>
#include <baselib/gobj.h>

static int const max_input_frames = 254;

/// UnclePunch Map file: Interrupt_Walljump
/// @returns: @c true if this function started a walljump, otherwise @c false.
bool ftWallJump_8008169C(HSD_GObj* gobj)
{
    Fighter* fp0 = GET_FIGHTER(gobj);

    // is a walljump character? is airborne?
    if (fp0->x2224_flag.bits.b7) {
        CollData* coll_data = &fp0->x6F0_collData;
        if ((fp0->x6F0_collData.x134_envFlags & MPCOLL_FLAGS_B11) ||
            (coll_data->x134_envFlags & MPCOLL_FLAGS_B5))
        {
            s32 env_flags = coll_data->x134_envFlags & MPCOLL_FLAGS_B11;

            // side of the collision?
            f32 wall_dir = env_flags ? -1.f : +1.f;

            // x210C_walljumpInputTimer = some walljump animation/input timer?
            // is initialized in the else-block when the user does the right
            // inputs. gets incremented here every frame.
            if ((fp0->x210C_walljumpInputTimer < max_input_frames) &&
                (wall_dir == fp0->x2110_walljumpWallSide))
            {
                fp0->x210C_walljumpInputTimer++;
            } else {
                Vec3 wall_pos, ecb;

                /// @todo Unused stack.
#ifdef MUST_MATCH
                u8 _[8];
#endif

                if (env_flags) {
                    // compute absolte position of the ECB's left vertex?
                    ecb.x = coll_data->xA4_ecbCurrCorrect.left.x;
                    ecb.y = coll_data->xA4_ecbCurrCorrect.left.y;
                    ecb.z = 0.0f;
                    ecb.x += fp0->cur_pos.x;
                    ecb.y += fp0->cur_pos.y;
                    ecb.z += fp0->cur_pos.z;
                    // compute distance to the wall?
                    if (!func_800567C0(coll_data->x174_leftwall.index, &ecb,
                                       &wall_pos))
                        wall_pos.x = 0.0f;
                } else {
                    // compute absolte position of the ECB's right vertex?
                    ecb.x = coll_data->xA4_ecbCurrCorrect.right.x;
                    ecb.y = coll_data->xA4_ecbCurrCorrect.right.y;
                    ecb.z = 0.0f;
                    ecb.x += fp0->cur_pos.x;
                    ecb.y += fp0->cur_pos.y;
                    ecb.z += fp0->cur_pos.z;
                    // compute distance to the wall?
                    if (!func_800567C0(coll_data->x160_rightwall.index, &ecb,
                                       &wall_pos))
                        wall_pos.x = 0.0f;
                }

                {
                    // not sure what this computes, I guess it checks if we are
                    // close to the wall and move towards it with sufficent
                    // speed
                    f32 x_diff = fp0->pos_delta.x - wall_pos.x;
                    x_diff = x_diff < 0 ? -x_diff : x_diff;

                    if (x_diff > fp0->x110_attr.x258) {
                        // walljump input phase one completed, now start the
                        // walljump input timer and check for the control stick
                        // movement away from the wall in the next phase
                        fp0->x2110_walljumpWallSide = wall_dir;
                        fp0->x210C_walljumpInputTimer = 0U;
                    }
                }
            }

            if (
                // walljump timer within limits?
                fp0->x210C_walljumpInputTimer < p_ftCommonData->x768 &&
                ((
                     // left wall & control stick right?
                     fp0->x2110_walljumpWallSide == -1 &&
                     fp0->input.x620_lstick_x >= p_ftCommonData->x76C) ||
                 (
                     // right wall & control stick left?
                     fp0->x2110_walljumpWallSide == +1 &&
                     fp0->input.x620_lstick_x <= -p_ftCommonData->x76C)) &&
                // control stick didn't stay too long in the tilt area?
                fp0->x670_timer_lstick_tilt_x < p_ftCommonData->x770)
            {
                // do a walljump!
                func_800C1E64(gobj, ftCo_MS_PassiveWallJump,
                              p_ftCommonData->x774, fp0->x1969_walljumpUsed,
                              fp0->x2110_walljumpWallSide);

                fp0->x210C_walljumpInputTimer = max_input_frames;
                if (fp0->x1969_walljumpUsed < 255)
                    fp0->x1969_walljumpUsed++;
                return true;
            }
        } else {
            fp0->x210C_walljumpInputTimer = max_input_frames;
        }
    }

    return false;
}
