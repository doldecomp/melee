/**
 * @file ftcolanim.h
 * @brief Handles Fighter Color and Material Animations
 * @details Manages flashing colors for hitstun, invincibility, metal form, cloaking device, and sleep state transitions.
 * Module prefix: ft (Fighter)
 */

#ifndef GALE01_0BFE6C
#define GALE01_0BFE6C

#include <melee/ft/forward.h>

/**
 * @brief Enters the Sleep motion state and sets the fighter to invisible/sleeping
 * @param gobj Fighter GObj
 */
/* 0BFD04 */ void ftCo_800BFD04(Fighter_GObj* gobj);

/**
 * @brief Enters the Sleep motion state, handling subfighters (Ice Climbers) and game mode notification
 * @param gobj Fighter GObj
 */
/* 0BFD9C */ void ftCo_800BFD9C(Fighter_GObj* gobj);

/**
 * @brief Animation callback for the Sleep motion state
 * @param gobj Fighter GObj
 */
/* 0BFE6C */ void ftCo_Sleep_Anim(Fighter_GObj* gobj);

/**
 * @brief IASA (Interruptible As Soon As) callback for the Sleep motion state
 * @param gobj Fighter GObj
 */
/* 0BFE70 */ void ftCo_Sleep_IASA(Fighter_GObj* gobj);

/**
 * @brief Resets the secondary color animation state (invincibility, metal, etc.)
 * @param fp Fighter instance data
 */
/* 0BFFAC */ void ftCo_800BFFAC(Fighter* fp);

/**
 * @brief Applies a color animation to the fighter
 * @param fp Fighter instance data
 * @param anim_id ID of the color animation to apply
 * @param unk Unknown boolean flag
 * @return True if successful
 */
/* 0BFFD0 */ bool ftCo_800BFFD0(Fighter* fp, FtColAnim anim_id, bool unk);

/**
 * @brief Resets the primary color animation state (damage/hitstun flashes)
 * @param fp Fighter instance data
 */
/* 0C0074 */ void ftCo_800C0074(Fighter* fp);

/**
 * @brief Resets the cloaking device (Spycloak) color animation state
 * @param fp Fighter instance data
 */
/* 0C0098 */ void ft_800C0098(Fighter* fp);

/**
 * @brief Resets the secondary color animation state and invokes character-specific callbacks
 * @param fp Fighter instance data
 */
/* 0C0134 */ void ftCo_800C0134(Fighter* fp);

/**
 * @brief Resets a specific color animation based on the provided animation ID
 * @param fp Fighter instance data
 * @param anim_id ID of the color animation
 */
/* 0C0200 */ void ftCo_800C0200(Fighter* fp, int anim_id);

/**
 * @brief Copies color animation state from one fighter to another (e.g., during Zelda/Sheik transformation)
 * @param src_fp Source Fighter instance data
 * @param target_fp Target Fighter instance data
 * @param anim_id ID of the color animation
 */
/* 0C0358 */ void ftCo_800C0358(Fighter* src_fp, Fighter* target_fp, s32 anim_id);

/**
 * @brief Updates all active color animations on the fighter for the current frame
 * @param gobj Fighter GObj
 */
/* 0C0408 */ void ftCo_800C0408(Fighter_GObj* gobj);

#endif
