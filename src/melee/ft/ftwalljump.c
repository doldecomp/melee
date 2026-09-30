/**
 * @file ftwalljump.c
 * @brief Handles wall jump physics and collision checks
 * @details Evaluates controller inputs and collision environments to trigger wall jumps, accommodating for moving walls/platforms.
 * Module prefix: ft (Fighter)
 */

#include "ftwalljump.h"

#include <Runtime/platform.h>

#include "fighter.h"
#include "kinds/ftCommon/forward.h"
#include "kinds/ftCommon/ftCo_PassiveWall.h"
#include "types.h"
#include <dolphin/mtx.h>
#include <melee/mp/mplib.h>

static int const max_input_frames = 254;

/**
 * @brief Checks and executes a wall jump if conditions are met (Interrupt_Walljump)
 * @param gobj Fighter GObj
 * @return True if a wall jump was started, false otherwise
 */
bool ftWallJump_8008169C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->can_walljump) {
        CollData* coll_data = &fp->coll_data;
        if ((fp->coll_data.env_flags & Collide_RightWallHug) ||
            (coll_data->env_flags & Collide_LeftWallHug))
        {
            // Collide_RightWallHug means hugging a right-facing wall (a wall on the player's left)
            s32 hugging_right_facing_wall = coll_data->env_flags & Collide_RightWallHug;

            // Identifies which side the wall is on (-1.f for left wall, +1.f for right wall)
            float wall_dir = hugging_right_facing_wall ? -1.f : +1.f;

            // Increment the wall jump input timer if the player is maintaining contact
            // with the same wall. Otherwise, evaluate initial contact conditions.
            if ((fp->wall_jump_input_timer < max_input_frames) &&
                (wall_dir == fp->x2110_walljumpWallSide))
            {
                fp->wall_jump_input_timer++;
            } else {
                Vec3 ecb_pos;
                Vec3 wall_vel;

                u8 _[8]; // Padding/unused

                if (hugging_right_facing_wall) {
                    // Compute absolute position of the ECB's left vertex
                    ecb_pos.x = coll_data->ecb.left.x;
                    ecb_pos.y = coll_data->ecb.left.y;
                    ecb_pos.z = 0.0f;
                    ecb_pos.x += fp->cur_pos.x;
                    ecb_pos.y += fp->cur_pos.y;
                    ecb_pos.z += fp->cur_pos.z;
                    
                    // Fetch the velocity of the wall (e.g., if it's a moving platform)
                    if (!mpGetSpeed(coll_data->right_facing_wall.index, &ecb_pos,
                                    &wall_vel))
                    {
                        wall_vel.x = 0.0f;
                    }
                } else {
                    // Compute absolute position of the ECB's right vertex
                    ecb_pos.x = coll_data->ecb.right.x;
                    ecb_pos.y = coll_data->ecb.right.y;
                    ecb_pos.z = 0.0f;
                    ecb_pos.x += fp->cur_pos.x;
                    ecb_pos.y += fp->cur_pos.y;
                    ecb_pos.z += fp->cur_pos.z;
                    
                    // Fetch the velocity of the wall (e.g., if it's a moving platform)
                    if (!mpGetSpeed(coll_data->left_facing_wall.index, &ecb_pos,
                                    &wall_vel))
                    {
                        wall_vel.x = 0.0f;
                    }
                }

                {
                    // Calculate approach speed relative to the wall to account for moving stages
                    float wall_relative_velocity =
                        fp->pos_delta.x - wall_vel.x;
                    wall_relative_velocity = wall_relative_velocity < 0
                                                 ? -wall_relative_velocity
                                                 : wall_relative_velocity;

                    // If approaching fast enough, begin the wall jump input window
                    if (wall_relative_velocity >
                        fp->co_attrs.wall_jump_min_approach_speed)
                    {
                        fp->x2110_walljumpWallSide = wall_dir;
                        fp->wall_jump_input_timer = 0U;
                    }
                }
            }

            if (
                // Is the wall jump input timer within the allowed window?
                fp->wall_jump_input_timer < p_ftCommonData->x768 &&
                ((
                     // Wall on the left & control stick smashed right?
                     fp->x2110_walljumpWallSide == -1 &&
                     fp->input.lstick[0].x >= p_ftCommonData->x76C) ||
                 (
                     // Wall on the right & control stick smashed left?
                     fp->x2110_walljumpWallSide == +1 &&
                     fp->input.lstick[0].x <= -p_ftCommonData->x76C)) &&
                // Has the control stick been smashed recently (prevent holding it)?
                fp->active_timer.lstick.x < p_ftCommonData->x770)
            {
                // Execute the wall jump
                ftCo_800C1E64(gobj, ftCo_MS_PassiveWallJump,
                              p_ftCommonData->x774, fp->x1969_walljumpUsed,
                              fp->x2110_walljumpWallSide);

                fp->wall_jump_input_timer = max_input_frames;
                if (fp->x1969_walljumpUsed < 255) {
                    fp->x1969_walljumpUsed++;
                }
                return true;
            }
        } else {
            fp->wall_jump_input_timer = max_input_frames;
        }
    }

    return false;
}
