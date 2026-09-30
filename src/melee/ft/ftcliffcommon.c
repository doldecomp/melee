/**
 * @file ftcliffcommon.c
 * @brief Common ledge grab (CliffCatch) logic
 * @details Handles determining if a fighter can grab a ledge, snapping to it, and the initial catch animation state.
 * Module prefix: ft (Fighter)
 */

#include "ftcliffcommon.h"

#include <Runtime/platform.h>

#include "fighter.h"
#include "ft_081B.h"
#include "ft_0877.h"
#include "ft_0881.h"
#include "ftanim.h"
#include "ftcamera.h"
#include "ftcommon.h"
#include "kinds/ftCommon/ftCo_CliffWait.h"
#include "kinds/ftCommon/ftCo_Fall.h"
#include "kinds/ftCommon/ftCo_StopCeil.h"
#include "kinds/ftCommon/types.h"
#include "types.h"
#include <dolphin/mtx.h>
#include <melee/ef/efasync.h>
#include <melee/mp/mplib.h>
#include <melee/pl/plbonuslib.h>

/**
 * @brief Checks if a fighter can grab a ledge and initiates the grab if so
 * @param gobj The Fighter's GObj
 * @return true if the fighter grabbed the ledge, false otherwise
 */
bool ftCliffCommon_80081298(Fighter_GObj* gobj)
{
    Fighter* other_fp;
    Fighter_GObj* other_gobj;

    u8 _[8];

    Fighter* fp = gobj->user_data;
    
    // Fastfall / control stick down prevents ledge grab
    if (fp->input.lstick[0].y <= -p_ftCommonData->x480) {
        return false;
    }
    
    // Check if in range of a ledge and not currently sandbag (?)
    if (fp->coll_data.env_flags & Collide_LedgeGrabMask &&
        ((fp->is_sandbag & 1) == 0))
    {
        // Check if ledge is already occupied or find the occupying fighter
        other_gobj = ft_80082E3C(gobj);
        if (other_gobj == NULL) {
            // Ledge is free or successfully stolen
            pl_80040048(fp->player_idx, fp->is_sub_fighter);
            ftCliffCommon_80081370(gobj);
            return true;
        }
        
        // Ledge is occupied and cannot be grabbed
        other_fp = other_gobj->user_data;
        pl_8003FFDC(other_fp->player_idx, other_fp->is_sub_fighter,
                    fp->player_idx, fp->is_sub_fighter,
                    other_fp->mv.co.cliff.ledge_id);
        fp->x213C = other_fp->mv.co.cliff.ledge_id;
        return false;
    }
    return false;
}

/**
 * @brief Initiates the CliffCatch action state (grabbing the ledge)
 * @param gobj The Fighter's GObj
 */
void ftCliffCommon_80081370(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Vec3 ledge_pos;
    u8 _[16] = { 0 };
    {
        float facing_dir;
        {
            float ledge_dir;
            if (fp->coll_data.env_flags & Collide_LeftLedgeGrab) {
                ledge_dir = +1;
            } else {
                ledge_dir = -1;
            }
            facing_dir = fp->facing_dir;
            
            // Face the ledge
            if (facing_dir != ledge_dir) {
                fp->facing_dir = -facing_dir;
            }
        }
        ftCommon_8007D780(fp);
        ftCommon_8007D5D4(fp);
        
        // Change action state to CliffCatch (252)
        Fighter_ChangeMotionState(gobj, 252, Ft_MF_None, 0, 1, 0, NULL);
        ftAnim_8006EBA4(gobj);
        ftCommon_8007D5D4(fp);
        
        // Reset velocity/gravity etc
        ftCommon_8007EFC0(fp, p_ftCommonData->x5F0);
        ftCommon_8007E2FC(gobj);
        fp->x221D_b7 = 1;
        
        // Store the ledge ID we grabbed
        if (fp->facing_dir > 0) {
            fp->mv.co.cliff.ledge_id = fp->coll_data.ledge_id_left;
        } else {
            fp->mv.co.cliff.ledge_id = fp->coll_data.ledge_id_right;
        }
        
        // Snap to ledge position
        ftCo_CliffCatch_Phys(gobj);
        
        // Ledge grab sound
        ft_800881D8(fp, fp->ft_data->x4C_sfx->x28, 127, 64);
        ftCommon_8007E2F4(fp, 511);
        ftCommon_8007EBAC(fp, 12, 0);

        // Get the coordinate of the ledge for the visual effect
        if (fp->facing_dir > 0) {
            mpLib_80053ECC_Floor(fp->mv.co.cliff.ledge_id, &ledge_pos);
        } else {
            mpLib_80053DA4_Floor(fp->mv.co.cliff.ledge_id, &ledge_pos);
        }
    }
    {
        Fighter* fp_shadow = gobj->user_data;
        // Spawn ledge grab effect
        efAsync_Spawn(gobj, &fp_shadow->x60C, 2, 1052, 0, &ledge_pos);
    }
    // Play generic hit/catch sound
    ft_PlaySFX(fp, 4, 127, 64);
}

/**
 * @brief Animation callback for CliffCatch (catching the ledge)
 * @param gobj The Fighter's GObj
 */
void ftCo_CliffCatch_Anim(Fighter_GObj* gobj)
{
    // Transition to CliffWait (ledge hang) when the catch animation ends
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_8009A804(gobj);
    }
}

/**
 * @brief IASA callback for CliffCatch
 * @param gobj The Fighter's GObj
 */
void ftCo_CliffCatch_IASA(Fighter_GObj* gobj) {}

/**
 * @brief Physics callback for CliffCatch
 * @param gobj The Fighter's GObj
 */
void ftCo_CliffCatch_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    
    // Check if the ledge is still valid
    if (mpLib_80054ED8(fp->mv.co.cliff.ledge_id) != 0) {
        Vec3 ledge_pos;
        u8 _[4] = { 0 };
        
        // Get the coordinate of the ledge
        if (fp->facing_dir > 0) {
            mpLib_80053ECC_Floor(fp->mv.co.cliff.ledge_id, &ledge_pos);
        } else {
            mpLib_80053DA4_Floor(fp->mv.co.cliff.ledge_id, &ledge_pos);
        }
        
        // Snap fighter position to ledge based on animation translation
        fp->cur_pos.x = fp->x68C_transNPos.z * fp->facing_dir + ledge_pos.x;
        fp->cur_pos.y = ledge_pos.y + fp->x68C_transNPos.y;
    } else {
        // Ledge no longer exists (e.g. Randall moved offstage), fall
        ftCo_Fall_Enter(gobj);
    }
}

/**
 * @brief Collision callback for CliffCatch
 * @param gobj The Fighter's GObj
 */
void ftCo_CliffCatch_Coll(Fighter_GObj* gobj)
{
    u8 _[8];

    if (ft_800821DC(gobj)) {
        ft_80082B1C(gobj);
        return;
    }

    if (ftCo_8009EF68(gobj)) {
        Fighter* fp = gobj->user_data;
        fp->x2064_ledgeCooldown = p_ftCommonData->ledge_cooldown;
    }
}

/**
 * @brief Camera callback for ledge states
 * @param gobj The Fighter's GObj
 */
void ftCo_Cliff_Cam(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCamera_UpdateCameraBox(gobj);
    if ((s32) fp->ground_or_air == GA_Air) {
        mpLib_8005811C(&fp->coll_data, fp->mv.co.cliff.ledge_id);
        fp->x890_cameraBox->on_ledge = true;
    }
}
