#include "ftwalljump.h"

#include "fighter.h"

#include <platform.h>

#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_PassiveWall.h"
#include "mp/mplib.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

static int const max_input_frames = 254;

/// UnclePunch Map file: Interrupt_Walljump
/// @returns: @c true if this function started a walljump, otherwise @c false.
bool ftWallJump_8008169C(HSD_GObj* gobj)
{
    Fighter* fp0 = GET_FIGHTER(gobj);

    if (fp0->can_walljump) {
        CollData* coll_data = &fp0->coll_data;
        if ((fp0->coll_data.env_flags & Collide_RightWallHug) ||
            (coll_data->env_flags & Collide_LeftWallHug))
        {
            s32 env_flags = coll_data->env_flags & Collide_RightWallHug;

            // side of the collision?
            float wall_dir = env_flags ? -1.f : +1.f;

            // wall_jump_input_timer = some walljump animation/input timer?
            // is initialized in the else-block when the user does the right
            // inputs. gets incremented here every frame.
            if ((fp0->wall_jump_input_timer < max_input_frames) &&
                (wall_dir == fp0->x2110_walljumpWallSide))
            {
                fp0->wall_jump_input_timer++;
            } else {
                Vec3 wall_pos, ecb;

                u8 _[8];

                if (env_flags) {
                    // compute absolte position of the ECB's left vertex?
                    ecb.x = coll_data->ecb.left.x;
                    ecb.y = coll_data->ecb.left.y;
                    ecb.z = 0.0f;
                    ecb.x += fp0->cur_pos.x;
                    ecb.y += fp0->cur_pos.y;
                    ecb.z += fp0->cur_pos.z;
                    // compute distance to the wall?
                    if (!mpGetSpeed(coll_data->right_facing_wall.index, &ecb,
                                    &wall_pos))
                    {
                        wall_pos.x = 0.0f;
                    }
                } else {
                    // compute absolte position of the ECB's right vertex?
                    ecb.x = coll_data->ecb.right.x;
                    ecb.y = coll_data->ecb.right.y;
                    ecb.z = 0.0f;
                    ecb.x += fp0->cur_pos.x;
                    ecb.y += fp0->cur_pos.y;
                    ecb.z += fp0->cur_pos.z;
                    // compute distance to the wall?
                    if (!mpGetSpeed(coll_data->left_facing_wall.index, &ecb,
                                    &wall_pos))
                    {
                        wall_pos.x = 0.0f;
                    }
                }

                {
                    // not sure what this computes, I guess it checks if we are
                    // close to the wall and move towards it with sufficent
                    // speed
                    float x_diff = fp0->pos_delta.x - wall_pos.x;
                    x_diff = x_diff < 0 ? -x_diff : x_diff;

                    if (x_diff > fp0->co_attrs.x148) {
                        // walljump input phase one completed, now start the
                        // walljump input timer and check for the control stick
                        // movement away from the wall in the next phase
                        fp0->x2110_walljumpWallSide = wall_dir;
                        fp0->wall_jump_input_timer = 0U;
                    }
                }
            }

            if (
                // walljump timer within limits?
                fp0->wall_jump_input_timer < p_ftCommonData->x768 &&
                ((
                     // left wall & control stick right?
                     fp0->x2110_walljumpWallSide == -1 &&
                     fp0->input.lstick.x >= p_ftCommonData->x76C) ||
                 (
                     // right wall & control stick left?
                     fp0->x2110_walljumpWallSide == +1 &&
                     fp0->input.lstick.x <= -p_ftCommonData->x76C)) &&
                // control stick didn't stay too long in the tilt area?
                fp0->x670_timer_lstick_tilt_x < p_ftCommonData->x770)
            {
                // do a walljump!
                ftCo_800C1E64(gobj, ftCo_MS_PassiveWallJump,
                              p_ftCommonData->x774, fp0->x1969_walljumpUsed,
                              fp0->x2110_walljumpWallSide);

                fp0->wall_jump_input_timer = max_input_frames;
                if (fp0->x1969_walljumpUsed < 255) {
                    fp0->x1969_walljumpUsed++;
                }
                return true;
            }
        } else {
            fp0->wall_jump_input_timer = max_input_frames;
        }
    }

    return false;
}
