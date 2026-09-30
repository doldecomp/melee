/**
 * @file ftcolanim.c
 * @brief Handles Fighter Color and Material Animations
 * @details Manages flashing colors for hitstun, invincibility, metal form, cloaking device, and sleep state transitions.
 * Module prefix: ft (Fighter)
 */

#include "ftcolanim.h"

#include "fighter.h"
#include "ft_0D4D.h"
#include "ftaction.h"
#include "ftdata.h"
#include "kinds/ftCommon/ftCo_HammerWait.h"
#include <melee/gm/gm_1601.h>
#include <melee/lb/lb_013B.h>
#include <melee/pl/player.h>

#ifdef MUST_MATCH
#pragma force_active on
#endif

/* 0BFE74 */ static void ftCo_800BFE74(Fighter_GObj* gobj, CommandInfo* cmd);
/* 0BFEB4 */ static void ftCo_800BFEB4(Fighter_GObj* gobj, CommandInfo* cmd);
/* 0BFEF4 */ static void ftCo_800BFEF4(Fighter_GObj* gobj, CommandInfo* cmd);
/* 0BFE94 */ static void ftCo_800BFE94(Fighter_GObj* gobj, CommandInfo* cmd);
/* 0BFED4 */ static void ftCo_800BFED4(Fighter_GObj* gobj, CommandInfo* cmd);
/* 0BFF14 */ static void ftCo_800BFF14(Fighter_GObj* gobj, CommandInfo* cmd);

FtCmd ftCo_803C6AD0[3] = {
    ftCo_800BFE74,
    ftCo_800BFEB4,
    ftCo_800BFEF4,
};

FtCmd ftCo_803C6ADC[3] = {
    ftCo_800BFE94,
    ftCo_800BFED4,
    ftCo_800BFF14,
};

/**
 * @brief Enters the Sleep motion state and sets the fighter to invisible/sleeping
 * @param gobj Fighter GObj
 */
void ftCo_800BFD04(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_Sleep, Ft_MF_None, 0.0f, 1.0f,
                              0.0f, NULL);
    fp->invisible = true;
    fp->x221E_b1 = true;
    fp->x221E_b2 = true;
    fp->x2219_b1 = true;
    fp->x890_cameraBox->state = CmSubjectState_Inactive;
    fp->is_sleeping = true;
    fp->x221F_b1 = true;
}

/**
 * @brief Enters the Sleep motion state, handling subfighters (Ice Climbers) and game mode notification
 * @param gobj Fighter GObj
 */
void ftCo_800BFD9C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_800BFD04(gobj);
    if (fp->x2222_b5) {
        HSD_GObj* pl_gobj = Player_GetEntityAtIndex(fp->player_idx, 1);
        if (pl_gobj != NULL) {
            ftCo_800D4F24(pl_gobj, 1);
        }
    }
    gm_80167320(fp->player_idx, fp->is_sub_fighter);
}

/**
 * @brief Animation callback for the Sleep motion state
 * @param gobj Fighter GObj
 */
void ftCo_Sleep_Anim(Fighter_GObj* gobj) {}

/**
 * @brief IASA (Interruptible As Soon As) callback for the Sleep motion state
 * @param gobj Fighter GObj
 */
void ftCo_Sleep_IASA(Fighter_GObj* gobj) {}

static void ftCo_800BFE74(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftAction_80071028(gobj, cmd);
}

static void ftCo_800BFE94(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftAction_800711DC(gobj, cmd);
}

static void ftCo_800BFEB4(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftAction_80071B50(gobj, cmd);
}

static void ftCo_800BFED4(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftAction_80071CA4(gobj, cmd);
}

static void ftCo_800BFEF4(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftAction_800730B8(gobj, cmd);
}

static void ftCo_800BFF14(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftAction_80073108(gobj, cmd);
}

static void ft_800BFF34(Fighter_GObj* gobj, CommandInfo* cmd, int cmd_id)
{
    int i = cmd_id - 0x15;
    ftCo_803C6AD0[i](gobj, cmd);
}

static void ft_800BFF70(Fighter_GObj* gobj, CommandInfo* cmd, int cmd_id)
{
    int i = cmd_id - 21;
    ftCo_803C6ADC[i](gobj, cmd);
}

/**
 * @brief Resets the secondary color animation state (invincibility, metal, etc.)
 * @param fp Fighter instance data
 */
void ftCo_800BFFAC(Fighter* fp)
{
    lb_80014498(&fp->x488);
}

/**
 * @brief Applies a color animation to the fighter
 * @param fp Fighter instance data
 * @param anim_id ID of the color animation to apply
 * @param unk Unknown boolean flag
 * @return True if successful
 */
bool ftCo_800BFFD0(Fighter* fp, FtColAnim anim_id, bool unk)
{
    // Cloaking Device (Spycloak) starts at a specific index
    if (anim_id >= FtColAnim_SpycloakStart) {
        if (lb_800144C8(&fp->x508, Fighter_804D6538,
                        anim_id -= FtColAnim_SpycloakStart, unk))
        {
            return true;
        }
    } else if (Fighter_804D653C[anim_id].unk5 != 0) {
        // Secondary color animations (invincibility, metal, etc.)
        if (lb_800144C8(&fp->x488, Fighter_804D653C, anim_id, unk)) {
            return true;
        }
    } else if (lb_800144C8(&fp->x408, Fighter_804D653C, anim_id, unk)) {
        // Primary color animations (hitstun, shield breaks, damage flashes)
        return true;
    }
    return false;
}

/**
 * @brief Resets the primary color animation state (damage/hitstun flashes)
 * @param fp Fighter instance data
 */
void ftCo_800C0074(Fighter* fp)
{
    lb_80014498(&fp->x408);
}

/**
 * @brief Resets the cloaking device (Spycloak) color animation state
 * @param fp Fighter instance data
 */
void ft_800C0098(Fighter* fp)
{
    lb_80014498(&fp->x508);
    if (fp->x2226_b4) {
        ftCo_800BFFD0(fp, 0x80, 0); // Re-apply base spycloak if still active
    }
}

/**
 * @brief Resets the secondary color animation state and invokes character-specific callbacks
 * @param fp Fighter instance data
 */
void ftCo_800C0134(Fighter* fp)
{
    lb_80014498(&fp->x488);
    if (ftData_UnkMotionStates4[fp->kind] != NULL) {
        ftData_UnkMotionStates4[fp->kind](fp->gobj);
    }
    if (ftCo_800C53E4(fp) != 0) {
        ftCo_800BFFD0(fp, 0x6A, 0);
    }
}

static inline void resetColAnimX408(Fighter* fp)
{
    lb_80014498(&fp->x408);
    // Restore relevant status flashes if they should still be active
    if (fp->stamina_dead) {
        ftCo_800BFFD0(fp, 0x7A, 0);
    }
    if (fp->dmg.x18F0 != 0) {
        ftCo_800BFFD0(fp, 8, 0);
    }
    if (fp->x221D_b6) {
        ftCo_800BFFD0(fp, 0x6B, 0);
    }
    if (fp->x1994 != 0 || fp->x1990 != 0 || fp->x2221_b0) {
        ftCo_800BFFD0(fp, 9, 0);
    }
}

/**
 * @brief Resets a specific color animation based on the provided animation ID
 * @param fp Fighter instance data
 * @param anim_id ID of the color animation
 */
void ftCo_800C0200(Fighter* fp, int anim_id)
{
    if (anim_id >= FtColAnim_SpycloakStart) {
        OSReport("don't reset spycloak colanim!\n");
        __assert("ftcolanimlist.c", 0xC1, "0");
        return;
    }
    if (Fighter_804D653C[anim_id].unk5 != 0) {
        ftCo_800C0134(fp);
    } else {
        resetColAnimX408(fp);
    }
}

/**
 * @brief Copies color animation state from one fighter to another (e.g., during Zelda/Sheik transformation)
 * @param fp Source Fighter instance data
 * @param target_fp Target Fighter instance data
 * @param anim_id ID of the color animation
 */
void ftCo_800C0358(Fighter* fp, Fighter* target_fp, s32 anim_id)
{
    if (anim_id >= FtColAnim_SpycloakStart) {
        OSReport("don't reset spycloak colanim!\n");
        __assert("ftcolanimlist.c", 0xDE, "0");
        return;
    }
    if (Fighter_804D653C[anim_id].unk5 != 0) {
        target_fp->x488 = fp->x488;
    } else {
        target_fp->x408 = fp->x408;
    }
}

/**
 * @brief Updates all active color animations on the fighter for the current frame
 * @param gobj Fighter GObj
 */
void ftCo_800C0408(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    // Process cloaking device (Spycloak) animations
    while (lb_80014258(gobj, &fp->x508, ft_800BFF34)) {
        ft_800C0098(fp);
    }

    // Process primary color animations (hitstun, etc.)
    while (lb_80014258(gobj, &fp->x408, ft_800BFF34)) {
        resetColAnimX408(fp);
    }

    // Process secondary color animations (metal, invincibility, etc.)
    if (fp->x408.x28_colanim.i == 0) {
        while (lb_80014258(gobj, &fp->x488, ft_800BFF34)) {
            ftCo_800C0134(fp);
        }
    } else {
        while (lb_80014258(gobj, &fp->x488, ft_800BFF70)) {
            ftCo_800C0134(fp);
        }
    }
    fp->x2221_b3 = true;
}
