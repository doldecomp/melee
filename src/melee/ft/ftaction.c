/**
 * @file ftaction.c
 * @brief Fighter subaction command script interpreter and action state event execution.
 * @details Implements the bytecode interpreter and event handlers for fighter subaction
 * scripts (`CommandInfo` / `fp->x3E4_fighterCmdScript`). Manages timed action state events
 * including hitbox activation/deactivation, hurtbox toggles, IASA (Interruptible As Soon As)
 * frame windows, jab combo windows, smash attack charging, audio effects, and particle GFX.
 *
 * ## Melee Action State & Animation Architecture:
 * - **Action States**: Every character action (Wait, Walk, Attack, Special, etc.) is identified
 *   by an action state ID (`FtMotionId`). Common states (0 to ~340) are indexed in
 *   `fp->x1C_actionStateList`, while character-specific states (>= `fp->x18`) are indexed in
 *   `fp->x20_actionStateList[(msid - fp->x18)]`.
 * - **MotionState Callbacks**:
 *   - `anim_cb`: Per-frame animation tick; evaluates state exit conditions, branches, or loops.
 *   - `input_cb`: Polled on actionable frames (IASA / FAF) to transition into new actions.
 *   - `phys_cb`: Computes movement, velocity integration, gravity, and traction.
 *   - `coll_cb`: Evaluates environmental collisions (ECB against floor/walls/ledges).
 *   - `cam_cb`: Updates camera framing and tracking targets.
 * - **Subaction Event Scripts**:
 *   - Bytecode streams tied to animation timelines.
 *   - Control flow opcodes 0-9 are handled by `Command_Execute` (Wait, Goto, Loop, Subroutine, Return, End).
 *   - Fighter opcodes 10+ trigger gameplay mechanics at precise animation frames (hitboxes, hurtboxes, SFX, GFX, etc.).
 *
 * Module prefix: ft (Fighter)
 */

#include "ftaction.h"

#include <Runtime/platform.h>

#include <melee/lb/forward.h>

#include <placeholder.h>

#include "fighter.h"
#include "forward.h"
#include "ft_081B.h"
#include "ft_0877.h"
#include "ft_0881.h"
#include "ft_0899.h"
#include "ft_0C88.h"
#include "ft_0DF0.h"
#include "ftanim.h"
#include "ftcolanim.h"
#include "ftcoll.h"
#include "ftcommon.h"
#include "ftdynamics.h"
#include "ftparts.h"
#include "kinds/ftCommon/ftCo_09F7.h"
#include "types.h"
#include <dolphin/mtx.h>
#include <melee/lb/inlines.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbcommand.h>
#include <melee/lb/types.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/random.h>

/* 07121C */ static void ftAction_8007121C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 0715EC */ static void ftAction_800715EC(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 07162C */ static void ftAction_8007162C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 07168C */ static void ftAction_8007168C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 07169C */ static void ftAction_8007169C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 0716F8 */ static void ftAction_800716F8(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071708 */ static void ftAction_80071708(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071774 */ static void ftAction_80071774(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071784 */ static void ftAction_80071784(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 0717C8 */ static void ftAction_800717C8(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 0717D8 */ static void ftAction_800717D8(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071810 */ static void ftAction_80071810(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071820 */ static void ftAction_80071820(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 0718A4 */ static void ftAction_800718A4(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071908 */ static void ftAction_80071908(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 07192C */ static void ftAction_8007192C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071950 */ static void ftAction_80071950(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071974 */ static void ftAction_80071974(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071998 */ static void ftAction_80071998(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071A14 */ static void ftAction_80071A14(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071A58 */ static void ftAction_80071A58(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071A9C */ static void ftAction_80071A9C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071AE8 */ static void ftAction_80071AE8(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071B28 */ static void ftAction_80071B28(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071CCC */ static void ftAction_80071CCC(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071D30 */ static void ftAction_80071D30(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071D40 */ static void ftAction_80071D40(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071D94 */ static void ftAction_80071D94(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071DCC */ static void ftAction_80071DCC(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071E04 */ static void ftAction_80071E04(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071F0C */ static void ftAction_80071F0C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071F34 */ static void ftAction_80071F34(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071F78 */ static void ftAction_80071F78(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071FA0 */ static void ftAction_80071FA0(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071FC8 */ static void ftAction_80071FC8(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 0722C8 */ static void ftAction_800722C8(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072320 */ static void ftAction_80072320(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 0726C0 */ static void ftAction_800726C0(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 0726F4 */ static void ftAction_800726F4(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 0727C8 */ static void ftAction_800727C8(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 07283C */ static void ftAction_8007283C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072894 */ static void ftAction_80072894(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 0728F8 */ static void ftAction_800728F8(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 07296C */ static void ftAction_8007296C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 07297C */ static void ftAction_8007297C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 0729C4 */ static void ftAction_800729C4(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 0729D4 */ static void ftAction_800729D4(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072A4C */ static void ftAction_80072A4C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072A5C */ static void ftAction_80072A5C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072AAC */ static void ftAction_80072AAC(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072ABC */ static void ftAction_80072ABC(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072B04 */ static void ftAction_80072B04(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072B14 */ static void ftAction_80072B14(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072B3C */ static void ftAction_80072B3C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072B84 */ static void ftAction_80072B84(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072B94 */ static void ftAction_80072B94(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072BE4 */ static void ftAction_80072BE4(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072BF4 */ static void ftAction_80072BF4(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072C5C */ static void ftAction_80072C5C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072C6C */ static void ftAction_80072C6C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072CB0 */ static void ftAction_80072CB0(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072CD8 */ static void ftAction_80072CD8(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072E24 */ static void ftAction_80072E24(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072E4C */ static void ftAction_80072E4C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072FE0 */ static void ftAction_80072FE0(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 073008 */ static void ftAction_80073008(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 07309C */ static void ftAction_8007309C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 073118 */ static void ftAction_80073118(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 07320C */ static void ftAction_8007320C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);

/**
 * @brief Standard execution dispatch table for fighter subaction opcodes 10 through 58.
 * @details Indexed by `(eventCode - 10)`. Called during normal frame-by-frame execution in ftAction_80073240.
 */
static FtCmd ftAction_803C06E8[] = {
    ftAction_80071028, ftAction_8007121C, ftAction_8007162C, ftAction_8007169C,
    ftAction_80071708, ftAction_80071784, ftAction_800717D8, ftAction_80071B50,
    ftAction_80071CCC, ftAction_80071820, ftAction_800718A4, ftAction_80071908,
    ftAction_8007192C, ftAction_80071950, ftAction_80071974, ftAction_80071998,
    ftAction_80071A14, ftAction_80071A58, ftAction_80071A9C, ftAction_80071AE8,
    ftAction_80071B28, ftAction_80071D40, ftAction_80071D94, ftAction_80071DCC,
    ftAction_80071E04, ftAction_80071F34, ftAction_80071F78, ftAction_80071FA0,
    ftAction_80071FC8, ftAction_80072320, ftAction_800726F4, ftAction_800727C8,
    ftAction_80072894, ftAction_800728F8, ftAction_8007297C, ftAction_800729D4,
    ftAction_80072A5C, ftAction_80072ABC, ftAction_80072B14, ftAction_80072B3C,
    ftAction_80072B94, ftAction_80072BF4, ftAction_80072C6C, ftAction_80072CB0,
    ftAction_80072CD8, ftAction_80072E4C, ftAction_80073008, ftAction_800730B8,
    ftAction_80073118,
};

/**
 * @brief Mid-animation catchup dispatch table for fighter subaction opcodes 10 through 58.
 * @details Indexed by `(eventCode - 10)`. Used during ftAction_80073354 when entering an action
 * state mid-animation (`anim_start > 0`). Skips transient audio and visual effects while executing
 * persistent hitbox, hurtbox, and state flag updates.
 */
static FtCmd ftAction_803C07AC[ARRAY_SIZE(ftAction_803C06E8)] = {
    ftAction_800711DC, ftAction_800715EC, ftAction_8007168C, ftAction_800716F8,
    ftAction_80071774, ftAction_800717C8, ftAction_80071810, ftAction_80071CA4,
    ftAction_80071D30, ftAction_80071820, ftAction_800718A4, ftAction_80071908,
    ftAction_8007192C, ftAction_80071950, ftAction_80071974, ftAction_80071998,
    ftAction_80071A14, ftAction_80071A58, ftAction_80071A9C, ftAction_80071AE8,
    ftAction_80071B28, ftAction_80071D40, ftAction_80071D94, ftAction_80071DCC,
    ftAction_80071F0C, ftAction_80071F34, ftAction_80071F78, ftAction_80071FA0,
    ftAction_800722C8, ftAction_800726C0, ftAction_800726F4, ftAction_8007283C,
    ftAction_80072894, ftAction_8007296C, ftAction_800729C4, ftAction_80072A4C,
    ftAction_80072AAC, ftAction_80072B04, ftAction_80072B14, ftAction_80072B84,
    ftAction_80072BE4, ftAction_80072C5C, ftAction_80072C6C, ftAction_80072CB0,
    ftAction_80072E24, ftAction_80072FE0, ftAction_8007309C, ftAction_80073108,
    ftAction_8007320C,
};

/**
 * @brief Bytecode command payload word counts for subaction opcodes 10 through 58.
 * @details Used by ftAction_8007349C for rapid script pointer skipping when Ft_MF_UpdateCmd is active.
 */
static u8 ftAction_803C0870[ARRAY_SIZE(ftAction_803C06E8)] = {
    05, 05, 01, 01, 01, 01, 01, 03, 01, 01, 01, 01, 01, 01, 01, 01, 01,
    01, 01, 01, 01, 01, 01, 01, 03, 01, 01, 01, 07, 04, 01, 01, 01, 01,
    01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 03, 03, 02, 01, 04
};

/**
 * @brief Subaction opcode 10: Spawns particle graphic effects (GFX).
 * @details Reads bone attachments, positional offsets, and range vectors (scaled by 1/256)
 * to spawn particle effects via ftCo_8009F834. If fighter is invisible, skips execution.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80071028(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    float unk;
    Vec3 offset;
    Vec3 range;
    int bone;
    int use_common_bone_id;
    int destroy_on_state_change;
    u32 gfx_id;
    {
        if (!fp->invisible) {
            if (cmd->x8.u->spawn_gfx_0.useUnkBone) {
                bone = fp->ft_data->x8->x12;
            } else {
                bone = cmd->x8.u->spawn_gfx_0.boneId;
            }
            use_common_bone_id = cmd->x8.u->spawn_gfx_0.useCommonBoneIDs;
            destroy_on_state_change =
                cmd->x8.u->spawn_gfx_0.destroyOnStateChange;

            NEXT_CMD(cmd);
            gfx_id = cmd->x8.u->spawn_gfx_1.gfxID;
            unk = cmd->x8.u->spawn_gfx_1.unkFloat;

            NEXT_CMD(cmd);
            // 0.003906f = 1.0f / 256.0f (Q8 fixed-point coordinate divisor)
            offset.x = 0.003906f * cmd->x8.u->spawn_gfx_2.offsetZ;
            offset.y = 0.003906f * cmd->x8.u->spawn_gfx_2.offsetY;

            NEXT_CMD(cmd);
            offset.z = 0.003906f * cmd->x8.u->spawn_gfx_3.offsetX;
            range.x = 0.003906f * cmd->x8.u->spawn_gfx_3.rangeZ;

            NEXT_CMD(cmd);
            range.y = 0.003906f * cmd->x8.u->spawn_gfx_4.rangeY;
            range.z = 0.003906f * cmd->x8.u->spawn_gfx_4.rangeX;

            NEXT_CMD(cmd);
            ftCo_8009F834(gobj, gfx_id, bone, use_common_bone_id,
                          destroy_on_state_change, &offset, &range, unk);
        } else {
            ftAction_800711DC(gobj, cmd);
        }
    }
}

/**
 * @brief Subaction opcode 10 skip: Skips GFX spawn command payload (5 words).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_800711DC(Fighter_GObj* gobj, CommandInfo* cmd)
{
    SKIP_CMD(cmd, 5);
}

/**
 * @brief Subaction opcode 11: Creates and activates an offensive hitbox capsule.
 * @details Configures a HitCapsule in fp->x914[id] with damage, bone attachment, radius scale,
 * position offsets, trajectory angle, base knockback (BKB), knockback growth (KGB), weight-dependent
 * set knockback (WKB), element (fire/electric/etc.), shield damage, and sound effects.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_8007121C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp;
    HitCapsule* hitbox;
    u32 hit_group;
    u32 idx;
    struct spawn_hitbox_skip* skip;
    PAD_STACK(8);

    fp = GET_FIGHTER(gobj);
    skip = (struct spawn_hitbox_skip*) cmd->x8.u;
    if ((skip->xF_b4) && (fp->x1064_thrownHitbox.x134.owner == NULL)) {
        ftAction_800715EC(gobj, cmd);
    } else {
        hit_group = cmd->x8.u->create_hitbox_0.hit_group;
        if (((hitbox = &fp->x914[cmd->x8.u->create_hitbox_0.id])->state ==
             HitCapsule_Disabled) ||
            (hitbox->x4 != hit_group))
        {
            hitbox->x4 = hit_group;
            hitbox->state = HitCapsule_Enabled;
            fp->x2219_b3 = 1;
            ftColl_800768A0(fp, hitbox);
        }
        idx = cmd->x8.u->create_hitbox_0.bone;
        if (cmd->x8.u->create_hitbox_0.use_common_bone_ids) {
            hitbox->jobj = fp->parts[ftParts_GetBoneIndex(
                                         fp, cmd->x8.u->create_hitbox_0.bone)]
                               .joint;
        } else {
            hitbox->jobj = fp->parts[idx].joint;
        }
        ftColl_8007ABD0(hitbox, cmd->x8.u->create_hitbox_0.damage, gobj);
        NEXT_CMD(cmd);
        // Hitbox radius scale (0.003906f = 1/256)
        hitbox->scale = 0.003906f * cmd->x8.u->create_hitbox_1.size;
        hitbox->b_offset.x = 0.003906f * cmd->x8.u->create_hitbox_1.z_offset;
        NEXT_CMD(cmd);
        hitbox->b_offset.y = 0.003906f * cmd->x8.u->create_hitbox_2.y_offset;
        hitbox->b_offset.z = 0.003906f * cmd->x8.u->create_hitbox_2.x_offset;
        NEXT_CMD(cmd);
        // Trajectory angle in degrees (e.g. 361 = Sakurai angle)
        ftColl_8007AC9C(hitbox, cmd->x8.u->create_hitbox_3.angle, gobj);
        hitbox->x24 = cmd->x8.u->create_hitbox_3.knockback_growth;
        hitbox->x28 = cmd->x8.u->create_hitbox_3.weight_set_knockback;
        hitbox->x43_b0 = cmd->x8.u->create_hitbox_3.item_hit_interaction;
        hitbox->x43_b1 = cmd->x8.u->create_hitbox_3.ignore_fighter_scale;
        hitbox->x40_b0 = cmd->x8.u->create_hitbox_3.clank;
        hitbox->x40_b1 = cmd->x8.u->create_hitbox_3.rebound;
        NEXT_CMD(cmd);
        hitbox->x2C = cmd->x8.u->create_hitbox_4.base_knockback;
        hitbox->element = cmd->x8.u->create_hitbox_4.element;
        hitbox->x34 = cmd->x8.u->create_hitbox_4.shield_damage;
        hitbox->sfx_severity = cmd->x8.u->create_hitbox_4.hit_sfx_severity;
        hitbox->sfx_kind = cmd->x8.u->create_hitbox_4.hit_sfx_kind;
        hitbox->x40_b2 = cmd->x8.u->create_hitbox_4.hit_aerial;
        hitbox->x40_b3 = cmd->x8.u->create_hitbox_4.hit_grounded;
        NEXT_CMD(cmd);
        hitbox->x42_b5 = 1;
        hitbox->x42_b7 = 1;
        hitbox->x41_b4 = 0;
        hitbox->x41_b6 = 0;
        hitbox->x41_b5 = 0;
        hitbox->x42_b0 = 0;
        hitbox->x42_b4 = 0;
        hitbox->x41_b7 = 0;
        hitbox->x134.hit_grabbed_victim_only =
            cmd->x8.u->create_hitbox_5.x1_b4;
        hitbox->x42_b1 = 1;
        hitbox->x42_b2 = 0;
        hitbox->x43_b2 = 0;
        if ((HSD_GObj_CurrentInvokedProc != NULL) &&
            (HSD_GObj_CurrentInvokedProc->s_link > 9))
        {
            ftColl_8007AD18(fp, hitbox);
        }
    }
    ftCommon_80080484(fp);
}

/**
 * @brief Subaction opcode 11 skip: Skips hitbox creation payload (5 words).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_800715EC(Fighter_GObj* gobj, CommandInfo* cmd)
{
    SKIP_CMD(cmd, 5);
}

/**
 * @brief Subaction opcode 12: Dynamically updates active hitbox damage.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_8007162C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    HitCapsule* hit =
        &GET_FIGHTER(gobj)->x914[cmd->x8.u->set_hitbox_damage.idx];
    ftColl_8007ABD0(hit, cmd->x8.u->set_hitbox_damage.value, gobj);
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 12 skip: Skips damage update payload (1 word).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_8007168C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    SKIP_CMD(cmd, 1);
}

/**
 * @brief Subaction opcode 13: Dynamically updates active hitbox radius scale.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_8007169C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HitCapsule* hit = &fp->x914[cmd->x8.u->set_hitbox_scale.idx];
    hit->scale = 0.003906f * cmd->x8.u->set_hitbox_scale.value;
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 13 skip: Skips scale update payload (1 word).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_800716F8(Fighter_GObj* gobj, CommandInfo* cmd)
{
    SKIP_CMD(cmd, 1);
}

/**
 * @brief Subaction opcode 14: Updates internal hitbox flags (x42_b5 / x42_b7).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80071708(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HitCapsule* hit = &fp->x914[cmd->x8.u->set_hitbox_x42_b57.idx];
    switch (cmd->x8.u->set_hitbox_x42_b57.type) {
    case 0:
        hit->x42_b5 = cmd->x8.u->set_hitbox_x42_b57.value;
        break;
    case 1:
        hit->x42_b7 = cmd->x8.u->set_hitbox_x42_b57.value;
        break;
    }
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 14 skip: Skips hitbox flags payload (1 word).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80071774(Fighter_GObj* gobj, CommandInfo* cmd)
{
    SKIP_CMD(cmd, 1);
}

/**
 * @brief Subaction opcode 15: Deactivates a specific active hitbox capsule.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80071784(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftColl_8007AFC8(gobj, cmd->x8.u->set_throw_flags.hit_idx);
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 15 skip: Skips deactivate hitbox payload (1 word).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_800717C8(Fighter_GObj* gobj, CommandInfo* cmd)
{
    SKIP_CMD(cmd, 1);
}

/**
 * @brief Subaction opcode 16: Deactivates all active hitboxes on the fighter.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_800717D8(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftColl_8007AFF8(gobj);
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 16 skip: Skips clear all hitboxes payload (1 word).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80071810(Fighter_GObj* gobj, CommandInfo* cmd)
{
    SKIP_CMD(cmd, 1);
}

/**
 * @brief Subaction opcode 19: Sets a command script variable in fp->cmd_vars[0..3].
 * @details Used by fighter code as an animation milestone signal (e.g. projectile launch,
 * charge release point, transition triggers).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80071820(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);

    switch (cmd->x8.u->set_cmd_var.idx) {
    case 0:
        fp->cmd_vars[0] = cmd->x8.u->set_cmd_var.value;
        break;
    case 1:
        fp->cmd_vars[1] = cmd->x8.u->set_cmd_var.value;
        break;
    case 2:
        fp->cmd_vars[2] = cmd->x8.u->set_cmd_var.value;
        break;
    case 3:
        fp->cmd_vars[3] = cmd->x8.u->set_cmd_var.value;
        break;
    }
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 20: Sets throw release flags (b3 / b4) and syncs command timer.
 * @details Marks the exact animation frame where the grabbed opponent is released from the throw.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_800718A4(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    switch (cmd->x8.u->set_throw_flags.hit_idx) {
    case 0:
        fp->x2210.x0.throw_flags_b3 = true;
        fp->cmd_timer = cmd->timer;
        break;
    case 1:
        fp->x2210.x0.throw_flags_b4 = true;
        break;
    }
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 21: Sets throw flag 1 (`throw_flags_b1`).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80071908(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2210.x0.throw_flags_b1 = true;
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 22: Sets throw flag 2 (`throw_flags_b2`), updating victim position.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_8007192C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2210.x0.throw_flags_b2 = true;
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 23: Enables action interruption (IASA / FAF).
 * @details Sets `fp->allow_interrupt = true`. Signals the start of the Interruptible As Soon As window,
 * allowing the player to cancel the remaining recovery animation into a new action (jump, shield, tilt, etc.).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80071950(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->allow_interrupt = true;
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 24: Sets throw flag 0 (`throw_flags_b0`).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80071974(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2210.x0.throw_flags_b0 = true;
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 25: Configures airborne / grounded environment physics state.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80071998(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    switch (cmd->x8.u->set_airborne_state.state) {
    case 0:
        ftCommon_8007D7FC(fp);
        break;
    case 1:
        ftCommon_8007D5D4(fp);
        break;
    case 2:
        ftCommon_8007D60C(fp);
        break;
    }
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 26: Sets full-body collision / intangibility state.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80071A14(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftColl_8007B62C(gobj, cmd->x8.u->set_airborne_state.state);
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 27: Globally enables or disables all hurt capsules on the fighter.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80071A58(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftColl_8007B0C0(gobj, cmd->x8.u->set_airborne_state.state);
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 28: Sets the hurt capsule status for a specific skeletal bone.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80071A9C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftColl_8007B128(gobj, cmd->x8.u->set_hurt_state.bone_idx,
                    cmd->x8.u->set_hurt_state.state);
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 29: Enables the jab combo continuation window.
 * @details Sets `fp->x2218_b1 = true`, allowing subsequent presses of the attack button
 * to chain Jab 1 into Jab 2, or Jab 2 into Jab 3.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80071AE8(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!cmd->x8.u->set_jab_combo.disabled || fp->x197C != NULL) {
        fp->x2218_b1 = true;
    }
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 30: Enables the rapid jab transition window.
 * @details Sets `fp->x2218_b2` to enable mashing attack inputs to transition into infinite rapid jab.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80071B28(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2218_b2 = cmd->x8.u->set_jab_rapid.state;
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 17: Plays fighter sound effect (SFX) or executes audio behavior.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80071B50(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp;
    u32 sfx;
    u8 vol;
    u8 pan;
    s32 behavior;

    fp = GET_FIGHTER(gobj);
    behavior = cmd->x8.u->sound_effect_0.behavior;
    NEXT_CMD(cmd);

    switch (behavior) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        sfx = cmd->x8.u->sound_effect_1.sfx_id;
        NEXT_CMD(cmd);
        vol = cmd->x8.u->sound_effect_2.volume;
        pan = cmd->x8.u->sound_effect_2.panning;

        switch (behavior) {
        case 0:
            ft_PlaySFX(fp, sfx, vol, pan);
            break;
        case 1:
            ft_80088478(fp, sfx, vol, pan);
            break;
        case 2:
            ft_800881D8(fp, sfx, vol, pan);
            break;
        case 3:
            ft_80088510(fp, sfx, vol, pan);
            break;
        case 4:
            ft_800885A8(fp, sfx, vol, pan);
            break;
        case 5:
            ft_80088640(fp, sfx, vol, pan);
            break;
        case 6:
            ft_80088328(fp, sfx, vol, pan);
            break;
        }
        break;

    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        NEXT_CMD(cmd);
        switch (behavior) {
        case 10:
            ft_80088828(fp);
            break;
        case 11:
            ft_80088770(fp);
            break;
        case 12:
            ft_80088884(fp);
            break;
        case 13:
            ft_800888E0(fp);
            break;
        case 14:
            ft_8008893C(fp);
            break;
        case 15:
            ft_800887CC(fp);
            break;
        }
        break;

    default:
        break;
    }

    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 17 skip: Skips audio command payload (3 words).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80071CA4(Fighter_GObj* gobj, CommandInfo* cmd)
{
    SKIP_CMD(cmd, 3);
}

/**
 * @brief Subaction opcode 18: Plays character smash attack charge/release sound effects.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80071CCC(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtSFX* sfx = fp->ft_data->x4C_sfx;
    FtSFXArr* sfx_smash = sfx->smash;
    if (sfx_smash == NULL) {
        NEXT_CMD(cmd);
    } else {
        ft_800889F4(fp, sfx_smash);
        NEXT_CMD(cmd);
    }
}

/**
 * @brief Subaction opcode 18 skip: Skips smash SFX command payload (1 word).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80071D30(Fighter_GObj* gobj, CommandInfo* cmd)
{
    SKIP_CMD(cmd, 1);
}

/**
 * @brief Subaction opcode 31: Sets display object (DObj) render flags.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80071D40(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftParts_80074B0C(gobj, cmd->x8.u->set_dobj_flags.idx,
                     cmd->x8.u->set_dobj_flags.value);
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 32: Resets fighter model parts to default state.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80071D94(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftParts_80074A8C(gobj);
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 33: Alternate reset for fighter model parts.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80071DCC(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftParts_80074ACC(gobj);
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 34: Configures thrown opponent body collision hitbox.
 * @details When throwing an opponent, turns their body into a damaging projectile hitbox (in fp->xDF4).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80071E04(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HitCapsule* hit = &fp->xDF4[cmd->x8.u->set_throw_hitbox_0.idx];
    ftColl_8007ABD0(hit, cmd->x8.u->set_throw_hitbox_0.damage, gobj);
    NEXT_CMD(cmd);

    ftColl_8007AC9C(hit, cmd->x8.u->set_throw_hitbox_1.unk0, gobj);
    hit->x24 = cmd->x8.u->set_throw_hitbox_1.hit_x24;
    hit->x28 = cmd->x8.u->set_throw_hitbox_1.hit_x28;
    NEXT_CMD(cmd);

    hit->x2C = cmd->x8.u->set_throw_hitbox_2.hit_x2C;
    hit->element = cmd->x8.u->set_throw_hitbox_2.element;
    hit->sfx_severity = cmd->x8.u->set_throw_hitbox_2.sfx_severity;
    hit->sfx_kind = cmd->x8.u->set_throw_hitbox_2.sfx_kind;
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 34 skip: Skips thrown hitbox payload (3 words).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80071F0C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    SKIP_CMD(cmd, 3);
}

/**
 * @brief Subaction opcode 35: Updates held item pickup/attachment visibility.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80071F34(Fighter_GObj* gobj, CommandInfo* cmd)
{
    PAD_STACK(8);
    ftCommon_8007F5CC(gobj, cmd->x8.u->unk27.value);
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 36: Toggles article / accessory visibility.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80071F78(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x221E_b4 = cmd->x8.u->set_article_vis.value;
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 37: Toggles fighter body model visibility.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80071FA0(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x221E_b5 = cmd->x8.u->set_fighter_vis.value;
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 38: Randomly selects and plays one of up to 6 sound effects.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80071FC8(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp;
    s32 rand;
    u8 volume;
    u8 panning;
    u32 behavior;
    s32 sfx_id;

    fp = GET_FIGHTER(gobj);
    volume = cmd->x8.u->pseudo_random_sfx_0.volume;
    panning = cmd->x8.u->pseudo_random_sfx_0.panning;
    behavior = cmd->x8.u->pseudo_random_sfx_0.behavior;
    rand = cmd->x8.u->pseudo_random_sfx_0.random_range;
    NEXT_CMD(cmd);
    rand = HSD_Randi(rand);
    switch (rand) {
    case 0:
        sfx_id = cmd->x8.u->pseudo_random_sfx_1.sfx_id;
        NEXT_CMD(cmd);
        NEXT_CMD(cmd);
        NEXT_CMD(cmd);
        NEXT_CMD(cmd);
        NEXT_CMD(cmd);
        break;
    case 1:
        NEXT_CMD(cmd);
        sfx_id = cmd->x8.u->pseudo_random_sfx_1.sfx_id;
        NEXT_CMD(cmd);
        NEXT_CMD(cmd);
        NEXT_CMD(cmd);
        NEXT_CMD(cmd);
        break;
    case 2:
        NEXT_CMD(cmd);
        NEXT_CMD(cmd);
        sfx_id = cmd->x8.u->pseudo_random_sfx_1.sfx_id;
        NEXT_CMD(cmd);
        NEXT_CMD(cmd);
        NEXT_CMD(cmd);
        break;
    case 3:
        NEXT_CMD(cmd);
        NEXT_CMD(cmd);
        NEXT_CMD(cmd);
        sfx_id = cmd->x8.u->pseudo_random_sfx_1.sfx_id;
        NEXT_CMD(cmd);
        NEXT_CMD(cmd);
        break;
    case 4:
        NEXT_CMD(cmd);
        NEXT_CMD(cmd);
        NEXT_CMD(cmd);
        NEXT_CMD(cmd);
        sfx_id = cmd->x8.u->pseudo_random_sfx_1.sfx_id;
        NEXT_CMD(cmd);
        break;
    case 5:
        NEXT_CMD(cmd);
        NEXT_CMD(cmd);
        NEXT_CMD(cmd);
        NEXT_CMD(cmd);
        NEXT_CMD(cmd);
        sfx_id = cmd->x8.u->pseudo_random_sfx_1.sfx_id;
        break;
    }
    NEXT_CMD(cmd);
    switch (behavior) {
    case 0:
        ft_PlaySFX(fp, sfx_id, volume, panning);
        return;
    case 1:
        ft_80088478(fp, sfx_id, volume, panning);
        return;
    case 2:
        ft_800881D8(fp, sfx_id, volume, panning);
        return;
    case 3:
        ft_80088510(fp, sfx_id, volume, panning);
        return;
    case 4:
        ft_800885A8(fp, sfx_id, volume, panning);
        return;
    case 5:
        ft_80088640(fp, sfx_id, volume, panning);
        return;
    case 6:
        ft_80088328(fp, sfx_id, volume, panning);
    default:
        return;
    }
}

/**
 * @brief Subaction opcode 38 skip: Skips random SFX payload (7 words).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_800722C8(Fighter_GObj* gobj, CommandInfo* cmd)
{
    SKIP_CMD(cmd, 7);
}

/**
 * @brief Subaction opcode 39: Plays directional/spatial stage audio with channel routing.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80072320(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp;
    u8 pitch_select;
    s32 voice_channel;
    s32 sfx_channel_group;
    s32 sfx;
    u32 behavior;
    u32 sfx_base;
    f32 direction;
    s32 sfx_param0;
    s32 sfx_param1;
    s32 sfx_param2;

    fp = GET_FIGHTER(gobj);
    pitch_select = cmd->x8.u->stage_sfx_0.pitch_select;
    behavior = cmd->x8.u->stage_sfx_0.sfx_base;
    sfx_base = cmd->x8.u->stage_sfx_0.x2_b0_7;

    switch (pitch_select) {
    case 0:
        direction = 0.0f;
        break;
    case 1:
        direction = 1.0f;
        break;
    case 2:
        direction = -1.0f;
        break;
    case 3:
        direction = fp->facing_dir;
        break;
    }

    NEXT_CMD(cmd);
    sfx = ft_80087D0C(fp, cmd->x8.u->stage_sfx_1.sfx_id);
    NEXT_CMD(cmd);
    sfx_param2 = cmd->x8.u->stage_sfx_2.x2_b0_15;
    NEXT_CMD(cmd);
    sfx_param0 = cmd->x8.u->stage_sfx_3.x2_b0_7;
    sfx_param1 = cmd->x8.u->stage_sfx_3.x3_b0_7;
    NEXT_CMD(cmd);

    switch (sfx_base) {
    case 0:
        sfx_channel_group = 0;
        voice_channel = -1;
        fp->x2160 = lbAudioAx_800264E4(
            lbAudioAx_800263E8(direction, gobj, behavior, sfx, 127, 127,
                               sfx_param0, sfx_param1, sfx_param2, sfx_channel_group, voice_channel));
        break;

    case 1:
        sfx_channel_group = fp->player_idx + fp->is_sub_fighter;
        fp->x214C = lbAudioAx_800264E4(lbAudioAx_800263E8(
            direction, gobj, behavior, sfx, 127, 127, sfx_param0, sfx_param1,
            sfx_param2, sfx_channel_group + 0x36, -1));
        break;

    case 2:
        if (!fp->x2225_b6) {
            sfx_channel_group = fp->player_idx + fp->is_sub_fighter;
            fp->x2144 = lbAudioAx_800264E4(lbAudioAx_800263E8(
                direction, gobj, behavior, sfx, 127, 127, sfx_param0,
                sfx_param1, sfx_param2, sfx_channel_group + 0x1E, -1));
            break;
        }
        switch (fp->kind) {
        case Ft_Kind_GameWatch:
        case Ft_Kind_Samus:
            sfx_channel_group = fp->player_idx + fp->is_sub_fighter;
            fp->x2144 = lbAudioAx_800264E4(lbAudioAx_800263E8(
                direction, gobj, behavior, sfx, 127, 127, sfx_param0,
                sfx_param1, sfx_param2, sfx_channel_group + 0x1E, -1));
            break;
        default:
            break;
        }
        break;

    case 3:
        sfx_channel_group = fp->player_idx + fp->is_sub_fighter;
        fp->x2150 = lbAudioAx_800264E4(lbAudioAx_800263E8(
            direction, gobj, behavior, sfx, 127, 127, sfx_param0, sfx_param1,
            sfx_param2, sfx_channel_group + 0x42, -1));
        break;

    case 4:
        sfx_channel_group = fp->player_idx + fp->is_sub_fighter;
        fp->x2154 = lbAudioAx_800264E4(lbAudioAx_800263E8(
            direction, gobj, behavior, sfx, 127, 127, sfx_param0, sfx_param1,
            sfx_param2, sfx_channel_group + 0x4E, -1));
        break;

    case 5:
        sfx_channel_group = fp->player_idx + fp->is_sub_fighter;
        fp->x2158 = lbAudioAx_800264E4(lbAudioAx_800263E8(
            direction, gobj, behavior, sfx, 127, 127, sfx_param0, sfx_param1,
            sfx_param2, sfx_channel_group + 0x5A, -1));
        break;

    case 6:
        if (!fp->x2225_b6) {
            sfx_channel_group = fp->player_idx + fp->is_sub_fighter;
            fp->x2148 = lbAudioAx_800264E4(lbAudioAx_800263E8(
                direction, gobj, behavior, sfx, 127, 127, sfx_param0,
                sfx_param1, sfx_param2, sfx_channel_group + 0x2A, -1));
            break;
        default:
            break;
        }

        switch (fp->kind) {
        case Ft_Kind_GameWatch:
        case Ft_Kind_Samus:
            sfx_channel_group = fp->player_idx + fp->is_sub_fighter;
            fp->x2148 = lbAudioAx_800264E4(lbAudioAx_800263E8(
                direction, gobj, behavior, sfx, 127, 127, sfx_param0,
                sfx_param1, sfx_param2, sfx_channel_group + 0x2A, -1));
            break;
        default:
            break;
        }
        break;
    }
}

/**
 * @brief Subaction opcode 39 skip: Skips spatial stage audio payload (4 words).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_800726C0(Fighter_GObj* gobj, CommandInfo* cmd)
{
    SKIP_CMD(cmd, 4);
}

/**
 * @brief Subaction opcode 40: Sets texture animation frame (facial expressions/eyes).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_800726F4(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftAnim_800704F0(gobj, cmd->x8.u->set_tex_anim.idx,
                    cmd->x8.u->set_tex_anim.frame);
    if (cmd->x8.u->set_tex_anim.b) {
        ftAnim_800704F0(gobj, cmd->x8.u->set_tex_anim.idx2,
                        cmd->x8.u->set_tex_anim.frame);
    }
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 41: Applies an animation sequence to a specific body part.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_800727C8(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftAnim_ApplyPartAnim(gobj, cmd->x8.u->part_anim.unk1,
                          cmd->x8.u->part_anim.unk2, cmd->x8.u->part_anim.unk3);
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 41 alternate: Applies part animation with default frame (0.0f).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_8007283C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftAnim_ApplyPartAnim(gobj, cmd->x8.u->part_anim.unk1,
                          cmd->x8.u->part_anim.unk2, 0.0f);
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 42: Updates Peach's parasol status.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80072894(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftCommon_8007E83C(gobj, cmd->x8.u->unk9.unk1, cmd->x8.u->unk9.unk2);
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 43: Initiates controller rumble pattern.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_800728F8(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (cmd->x8.u->unk10.unk1) {
        ftCommon_8007EC30(cmd->x8.u->unk10.unk2, cmd->x8.u->unk10.unk3);
    } else {
        ftCommon_8007EBAC(fp, cmd->x8.u->unk10.unk2, cmd->x8.u->unk10.unk3);
    }
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 43 skip: Advances past rumble command (1 word).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_8007296C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 44: Stops controller rumble effect.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_8007297C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007ECD4(fp, cmd->x8.u->unk11.unk1);
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 44 skip: Advances past stop rumble command.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_800729C4(Fighter_GObj* gobj, CommandInfo* cmd)
{
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 45: Sets looping controller rumble pattern.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_800729D4(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int unk2 = cmd->x8.u->unk12.unk2;
    int unk3 = cmd->x8.u->unk12.unk3;
    switch (cmd->x8.u->unk12.unk1) {
    case 0:
        ftCommon_8007EEC8(fp, unk2, unk3);
        break;
    case 1:
        ftCommon_8007EF5C(fp, unk2);
        break;
    }
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 45 skip: Advances past loop rumble command.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80072A4C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 46: Starts color/material flash animation (ColAnim).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80072A5C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_800BFFD0(fp, cmd->x8.u->unk13.unk1, cmd->x8.u->unk13.unk2);
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 46 skip: Advances past start ColAnim command.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80072AAC(Fighter_GObj* gobj, CommandInfo* cmd)
{
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 47: Stops active color animation (ColAnim).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80072ABC(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftCo_800C0200(GET_FIGHTER(gobj), cmd->x8.u->unk14.unk1);
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 47 skip: Advances past stop ColAnim command.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80072B04(Fighter_GObj* gobj, CommandInfo* cmd)
{
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 48: Sets intangible / invincible state flag.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80072B14(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x221E_b1 = cmd->x8.u->unk15.unk1;
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 49: Configures sword trail visual effect.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80072B3C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2100 = cmd->x8.u->unk16.unk4;
    fp->x2101_bits_8 = cmd->x8.u->unk16.unk3;
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 49 skip: Advances past sword trail command.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80072B84(Fighter_GObj* gobj, CommandInfo* cmd)
{
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 50: Updates dynamic bone secondary physics simulation.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80072B94(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_8009E318(gobj, cmd->x8.u->unk17.unk1, fp->cur_anim_frame);
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 50 skip: Advances past dynamic bone command.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80072BE4(Fighter_GObj* gobj, CommandInfo* cmd)
{
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 51: Inflicts self-damage recoil directly to the fighter.
 * @details Notably used on Pichu's electric attacks (inflicting self-percent).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80072BF4(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_TakeDamage_8006CC7C(fp, cmd->x8.u->unk18.damage_amount);
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 51 skip: Advances past self-damage command.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80072C5C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 52: Triggers camera focus or zoom event.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80072C6C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ft_8008A1B8(gobj, cmd->x8.u->unk19.unk1);
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 53: Updates model flag x2225_b2.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80072CB0(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2225_b2 = cmd->x8.u->unk20.unk1;
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 54: Spawns surface-dependent footstep sound and dust particle GFX.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80072CD8(Fighter_GObj* gobj, CommandInfo* cmd)
{
    int surface_sfx_id;
    int play_default_sfx;
    int gfx_id;
    CommandInfo _cmd;
    u32 cmd_words[3];
    Vec3 offset;
    Vec3 range;
    u32 part;
    Fighter* fp;
    u32 unused;

    fp = gobj->user_data;
    play_default_sfx = 1;

    if (ft_80084BFC(gobj, &surface_sfx_id, &play_default_sfx, &gfx_id) != false) {
        if (surface_sfx_id != -1) {
            _cmd.x8.u = (union CmdUnion*) cmd_words;
            cmd_words[0] = *(u32*) cmd->x8.u;
            cmd_words[1] = surface_sfx_id;
            cmd_words[2] = *(u32*) ((u8*) cmd->x8.u + 8);
            ftAction_80071B50(gobj, &_cmd);
        }

        if (gfx_id != -1) {
            offset.z = 0.0f;
            range.z = 0.0f;
            offset.y = 0.0f;
            range.y = 0.0f;
            offset.x = 0.0f;
            range.x = 0.0f;

            if (!cmd->x8.u->footstep_fx_0.use_alt_bone) {
                part = fp->ft_data->x8->x13;
            } else {
                part = fp->ft_data->x8->x14;
            }
            ftCo_8009F834(gobj, gfx_id, part, 0, 0, &offset, &range, 0.0f);
        }
    }

    if (play_default_sfx != 0) {
        ftAction_80071B50(gobj, cmd);
        return;
    }

    ++cmd->x8.u;
    ++cmd->x8.u;
    ++cmd->x8.u;
}

/**
 * @brief Subaction opcode 54 skip: Skips footstep audio and GFX payload (3 words).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80072E24(Fighter_GObj* gobj, CommandInfo* cmd)
{
    SKIP_CMD(cmd, 3);
}

/**
 * @brief Subaction opcode 55: Spawns surface-dependent landing sound and impact dust GFX.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80072E4C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    int landing_sfx_id;
    int play_default_sfx;
    int gfx_id;
    CommandInfo _cmd;
    u32 cmd_words[3];
    Vec3 offset;
    Vec3 range;
    Fighter* fp;
    s32 cmd_flag;
    u32 unused;

    fp = gobj->user_data;
    play_default_sfx = 1;
    gfx_id = -1;
    cmd_flag = cmd->x8.u->unk_fx_0.x1_b0_7;
    cmd_flag &= 1;
    if ((ft_80084C38(gobj, &landing_sfx_id, &play_default_sfx, &gfx_id) != false) &&
        (cmd_flag == 0) && (landing_sfx_id != -1))
    {
        _cmd.x8.u = (union CmdUnion*) cmd_words;
        cmd_words[0] = *(u32*) cmd->x8.u;
        cmd_words[1] = landing_sfx_id;
        cmd_words[2] = ((u32*) cmd->x8.u)[2];
        ftAction_80071B50(gobj, &_cmd);
    }

    if (gfx_id == -1) {
        gfx_id = ((u16*) cmd->x8.u)[1];
    }
    offset.z = 0.0f;
    range.z = 0.0f;
    offset.y = 0.0f;
    range.y = 0.0f;
    offset.x = 0.0f;
    range.x = 0.0f;
    ftCo_8009F834(gobj, gfx_id, FtPart_TopN, 0, 0, &offset, &range, 0.0f);
    if (play_default_sfx != 0) {
        ft_PlaySFX(fp, 0x46, 0x7FU, 0x40U);
        if (cmd_flag == 0) {
            ftAction_80071B50(gobj, cmd);
        }
    }
    if ((play_default_sfx == 0) || (cmd_flag != 0)) {
        ++cmd->x8.u;
        ++cmd->x8.u;
        ++cmd->x8.u;
    }
    ftCommon_8007EBAC(fp, 0x16U, 0U);
}

/**
 * @brief Subaction opcode 55 skip: Skips landing audio and GFX payload (3 words).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80072FE0(Fighter_GObj* gobj, CommandInfo* cmd)
{
    SKIP_CMD(cmd, 3);
}

/**
 * @brief Subaction opcode 56: Initializes smash attack charging state window.
 * @details Reads charge frame limit (typically 60 frames max), damage growth rate,
 * and charging flash color animation. Delegates to ftCo_800DEE84.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80073008(Fighter_GObj* gobj, CommandInfo* cmd)
{
    f32 charge_frames;
    f32 charge_rate;
    f32 color_anim;
    f32 dmg_mult;

    charge_rate = cmd->x8.u->smash_charge_0.charge_rate;
    charge_frames = cmd->x8.u->smash_charge_0.charge_frames;
    dmg_mult = 0.003906f * charge_rate;
    NEXT_CMD(cmd);
    color_anim = cmd->x8.u->smash_charge_1.color_anim;
    NEXT_CMD(cmd);
    ftCo_800DEE84(gobj, (s32) color_anim, charge_frames, dmg_mult);
}

/**
 * @brief Subaction opcode 56 skip: Skips smash charge initialization payload (2 words).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_8007309C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    SKIP_CMD(cmd, 2);
}

/**
 * @brief Subaction opcode 57: Updates body collision and shield parameters.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_800730B8(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_800C8B60(fp, cmd->x8.u->unk21.unk1, cmd->x8.u->unk21.unk2);
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 57 skip: Advances past body parameter command.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80073108(Fighter_GObj* gobj, CommandInfo* cmd)
{
    NEXT_CMD(cmd);
}

/**
 * @brief Subaction opcode 58: Spawns wind hazard push field / wind velocity effect.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_80073118(Fighter_GObj* gobj, CommandInfo* cmd)
{
    u8 idx;
    s32 timer;
    f32 x;
    f32 y;
    f32 mag;
    f32 decay_amt;
    f32 angle;

    idx = cmd->x8.u->wind_fx_0.bone;
    NEXT_CMD(cmd);

    x = 0.003906f * cmd->x8.u->wind_fx_1.timer;
    y = 0.003906f * cmd->x8.u->wind_fx_1.x;
    NEXT_CMD(cmd);

    mag = 0.003906f * cmd->x8.u->wind_fx_2.y;
    decay_amt = 0.003906f * cmd->x8.u->wind_fx_2.mag;
    NEXT_CMD(cmd);

    timer = cmd->x8.u->wind_fx_3.angle;
    angle = 0.003906f * cmd->x8.u->wind_fx_3.decay;
    NEXT_CMD(cmd);

    ftCo_8009E714(gobj, idx, timer, x, y, mag, decay_amt, angle);
}

/**
 * @brief Subaction opcode 58 skip: Skips wind hazard command payload (4 words).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
void ftAction_8007320C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    SKIP_CMD(cmd, 4);
}

/// Helper macro to cast script event pointer to default event structure.
#define gmScriptEventCast(p_event, type) ((type*) (p_event))

/**
 * @brief Main per-frame subaction command script execution interpreter tick.
 * @details Runs during each animation frame update. Decrements script timer by `fp->frame_speed_mul`,
 * executes control flow commands (opcodes 0-9) via `Command_Execute`, and dispatches fighter
 * action events (opcodes 10+) via `ftAction_803C06E8`.
 * @param fighter_gobj Fighter game object pointer.
 */
void ftAction_80073240(Fighter_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    CommandInfo* cmd = &fp->x3E4_fighterCmdScript;
    u32 event_code;
    fp->x3E4_fighterCmdScript.frame_count = fp->cur_anim_frame + fp->x898_unk;
    if (fp->x3E4_fighterCmdScript.x8.u != NULL) {
        if (cmd->timer != F32_MAX) {
            cmd->timer -= fp->frame_speed_mul;
        }
        do {
            if (cmd->x8.u == NULL) {
                break;
            }
            if (F32_MAX == cmd->timer) {
                if (cmd->frame_count >= fp->frame_speed_mul) {
                    break;
                }
                cmd->timer = -cmd->frame_count;
            } else if (cmd->timer > 0.0f) {
                break;
            }
            event_code =
                gmScriptEventCast(cmd->x8.u, gmScriptEventDefault)
                    ->opcode;
            if (Command_Execute(cmd, event_code) == false) {
                event_code -= 0xA;
                ftAction_803C06E8[event_code](fighter_gobj, cmd);
            }
        } while (F32_MAX != cmd->timer);
    }
}

/**
 * @brief Fast-forward subaction script catchup interpreter tick for mid-animation starts.
 * @details Executed when entering an action state with anim_start > 0. Executes persistent
 * state commands (hitbox creation, hurtbox state, flags) via ftAction_803C07AC while skipping
 * one-shot audio and visual effects. Resets throw flags if timer changes and finishes.
 * @param gobj Fighter game object pointer.
 */
void ftAction_80073354(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    CommandInfo* cmd = (&fp->x3E4_fighterCmdScript);
    u32 event_code;

    fp->x3E4_fighterCmdScript.frame_count = fp->cur_anim_frame + fp->x898_unk;
    fp->x2210.throw_flags = 0;
    if (fp->x3E4_fighterCmdScript.x8.u != NULL) {
        if (cmd->timer != F32_MAX) {
            cmd->timer -= fp->frame_speed_mul;
        }
        do {
            if (cmd->x8.u == NULL) {
                break;
            }
            if (cmd->timer == F32_MAX) {
                if (cmd->frame_count >= fp->frame_speed_mul) {
                    break;
                }
                cmd->timer = -cmd->frame_count;
            } else if (cmd->timer > 0.0f) {
                break;
            }
            {
                float prev_timer = cmd->timer;
                event_code =
                    gmScriptEventCast(cmd->x8.u, gmScriptEventDefault)->opcode;
                if (Command_Execute(cmd, event_code) == false) {
                    event_code -= 0xA;
                    ftAction_803C07AC[event_code](gobj, cmd);
                }
                if (cmd->timer != prev_timer && cmd->timer <= 0.0f) {
                    fp->x2210.throw_flags = 0;
                }
            }
        } while (cmd->timer != F32_MAX);
    }
}

/**
 * @brief Fast-forward subaction command skip loop when Ft_MF_UpdateCmd is active.
 * @details Advances the command script up to the current animation frame by rapidly
 * advancing script pointers using bytecode payload word lengths from `ftAction_803C0870`.
 * @param gobj Fighter game object pointer.
 */
void ftAction_8007349C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CommandInfo* cmd = (&fp->x3E4_fighterCmdScript);
    PAD_STACK(8);
    fp->x3E4_fighterCmdScript.frame_count = fp->cur_anim_frame + fp->x898_unk;
    if (fp->x3E4_fighterCmdScript.x8.u == NULL) {
        return;
    }
    if (cmd->timer != F32_MAX) {
        cmd->timer -= fp->frame_speed_mul;
    }
    do {
        if (cmd->x8.u == NULL) {
            break;
        }
        if (cmd->timer == F32_MAX) {
            if (cmd->frame_count >= fp->frame_speed_mul) {
                break;
            }
            cmd->timer = -cmd->frame_count;
        } else if (cmd->timer > 0.0f) {
            break;
        }
        {
            u32 opcode = cmd->x8.u->Command_09.id;
            if (!Command_Execute(cmd, opcode)) {
                cmd->x8.u += ftAction_803C0870[opcode - 10];
            }
        }
    } while (cmd->timer != F32_MAX);
}
