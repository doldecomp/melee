/**
 * @file ftmetal.c
 * @brief Fighter metal form effects and shader updates
 * @details Handles the transition, rendering flags, and shader setup when a fighter picks up a Metal Box.
 * Module prefix: ft
 */
#include "ftmetal.h"

#include "fighter.h"
#include "ft_081B.h"
#include "ftanim.h"
#include "ftchangeparam.h"
#include "ftcommon.h"
#include "ftmaterial.h"
#include "ftparts.h"
#include "types.h"
#include <melee/lb/lb_00B0.h>
#include <sysdolphin/baselib/id.h>

/**
 * @brief Reverts a fighter's metal effect, resetting the JObj and DObj flags to their original rendering modes.
 * @param fp The fighter
 */
void ft_800C8170(Fighter* fp)
{
    int i;
    HSD_JObj* jobj;
    HSD_DObj* dobj;
    HSD_MObj* mobj;
    u32 flags;

    PAD_STACK(8);

    for (i = 0; i < ftPartsTable[fp->kind]->parts_num; i++) {
        if (fp->parts[i].x8.x0.flags_b1) {
            FighterBone* bone = &fp->parts[i];
            jobj = bone->joint;
            dobj = HSD_JObjGetDObj(jobj);
            flags = 0;
            if (bone->x8.x0.flags_b7) {
                flags |= JOBJ_LIGHTING;
            }
            if (bone->x8.x0.flags2_b0) {
                flags |= JOBJ_TEXGEN;
            }
            if (bone->x8.x0.flags2_b1) {
                flags |= JOBJ_SPECULAR;
            }
            if (bone->x8.x0.flags2_b2) {
                flags |= JOBJ_UNK_B18;
            }
            if (bone->x8.x0.flags2_b3) {
                flags |= JOBJ_UNK_B20;
            }
            if (bone->x8.x0.flags2_b4) {
                flags |= JOBJ_UNK_B19;
            }
            HSD_JObjClearFlags(jobj, 0x50180);
            HSD_JObjSetFlags(jobj, flags);
            while (dobj != NULL) {
                if (dobj != NULL) {
                    mobj = dobj->mobj;
                } else {
                    mobj = NULL;
                }
                switch (mobj->rendermode & RENDER_BLENDING) {
                case 0:
                    HSD_DObjModifyFlags(dobj, 2, 0xE);
                    break;
                case RENDER_XLU:
                    HSD_DObjModifyFlags(dobj, 8, 0xE);
                    break;
                case RENDER_XLU | RENDER_NO_ZUPDATE:
                    HSD_DObjModifyFlags(dobj, 4, 0xE);
                    break;
                default:
                    OSReport("mobj has unexpected blending flags (0x%x).",
                             dobj->mobj->rendermode);
                    HSD_Panic("ftmetal.c", 0x73, "");
                    break;
                }
                dobj = dobj != NULL ? dobj->next : NULL;
            }
        }
    }
}

/**
 * @brief Applies the metal state shader to all active joints and dobjs on the fighter.
 * @param fp The fighter
 */
static inline void enableMetal(Fighter* fp)
{
    HSD_DObj* dobj;
    int i;
    HSD_JObj* jobj;

    for (i = 0; i < ftPartsTable[fp->kind]->parts_num; i++) {
        if (fp->parts[i].x8.x0.flags_b1) {
            jobj = fp->parts[i].joint;
            dobj = HSD_JObjGetDObj(jobj);
            HSD_JObjSetFlags(jobj, 0x50180);
            HSD_JObjClearFlags(jobj, 0x180000);
            while (dobj != NULL) {
                HSD_DObjModifyFlags(dobj, 2, 0xE);
                dobj = dobj != NULL ? dobj->next : NULL;
            }
        }
    }
    ftCommon_80080460(fp);
}

/**
 * @brief Turns a fighter metal for a specific duration with given health (stamina).
 * @param fighter_gobj The fighter's GObj
 * @param timer How many frames the metal effect lasts
 * @param health Additional stamina/health properties for the metal state
 */
void ftCo_800C8348(Fighter_GObj* fighter_gobj, int timer, int health)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    PAD_STACK(0x10);

    fp->metal_timer = timer;
    fp->metal_health = health;

    if (fp->is_metal) {
        return;
    }
    fp->is_metal = true;

    enableMetal(fp);
}

/**
 * @brief Applies or reapplies the metal state based on the fighter's is_always_metal flag.
 * @param gobj The fighter's GObj
 */
void ftCo_800C8438(Fighter_GObj* gobj)
{
    Fighter* fp;

    PAD_STACK(0x10);

    fp = GET_FIGHTER(gobj);
    fp->is_metal = fp->is_always_metal;
    fp->metal_timer = 0;
    fp->metal_health = 0;
    if (!fp->is_metal) {
        return;
    }

    enableMetal(fp);

    ftCo_800D105C(gobj);
    ft_80081C88(gobj, fp->x34_scale.y);
}

/**
 * @brief Clears metal timers and health, removes the metal state, and reverts rendering.
 * @param gobj The fighter's GObj
 */
void ftCo_800C8540(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->metal_timer = 0;
    fp->metal_health = 0;
    if (!fp->is_always_metal) {
        fp->is_metal = false;
        ftCo_800D105C(gobj);
        ft_80081C88(gobj, fp->x34_scale.y);
        ft_800C8170(fp);
        ftCommon_80080474(fp);
    }
}

/**
 * @brief Initializes the secondary DObjs / model parts needed for the metal state.
 * @param gobj The fighter's GObj
 */
void ft_800C85B8(Fighter_GObj* gobj)
{
    HSD_Joint* curr_joint;
    s32 tree_depth;

    Fighter* fp;
    u32 part_idx;
    int dobj_count;
    HSD_JObj* part_jobj;
    int joint_idx;
    HSD_DObj* dobj;
    HSD_Joint* metal_skeleton;
    int dobj_iter_count;
    HSD_DObj* dobj_iter;

    PAD_STACK(0xC);

    fp = GET_FIGHTER(gobj);
    metal_skeleton = fp->ft_data->x5C;
    curr_joint = metal_skeleton;
    joint_idx = (dobj_count = (tree_depth = 0));
    while (curr_joint != 0) {
        if (ftParts_8007506C(fp->kind, joint_idx) != 0) {
            joint_idx++;
        } else {
            HSD_IDInsertToTable(NULL, (HSD_IDKey) curr_joint,
                                fp->parts[joint_idx].joint);
            joint_idx++;
            ftAnim_GetNextJointInTree(&curr_joint, &tree_depth);
        }
    }
    curr_joint = metal_skeleton;
    tree_depth = (part_idx = 0);
    while (curr_joint != 0) {
        if (ftParts_8007506C(fp->kind, part_idx) != 0) {
            part_idx += 1;
        } else {
            dobj_iter_count = 0;
            part_jobj = fp->parts[part_idx].joint;
            dobj = HSD_DObjLoadDesc(curr_joint->u.dobjdesc);
            if (dobj != NULL) {
                dobj_iter = HSD_JObjGetDObj(part_jobj);
                fp->parts[part_idx].x8.x0.flags2_b5 = true;
                HSD_DObjResolveRefsAll(dobj, curr_joint->u.dobjdesc);
                if (dobj_iter == NULL) {
                    HSD_JObjAddDObj(part_jobj, dobj);
                } else {
                    while (dobj_iter != NULL) {
                        if (!(dobj_iter != NULL ? dobj_iter->next : NULL)) {
                            break;
                        }
                        dobj_iter = dobj_iter != NULL ? dobj_iter->next : NULL;
                    }
                    lb_8000CE30(dobj_iter, dobj);
                }
                while (true) {
                    if (dobj == NULL) {
                        break;
                    }
                    if (dobj_count >= 0x20) {
                        HSD_ASSERTREPORT(
                            0xF8, 0, "fighter parts model dobj num over!\n");
                    }
                    fp->x203C.data[dobj_count] = dobj;
                    {
                        HSD_MObj* mobj = dobj->mobj;
                        if (mobj != NULL) {
                            hsdChangeClass(mobj, &ftMObj);
                        }
                    }
                    dobj = dobj != NULL ? dobj->next : NULL;
                    dobj_count++;
                    dobj_iter_count++;
                }
                if (dobj_iter_count >= 0x80) {
                    HSD_ASSERTREPORT(0x106, 0, "fighter dobj num over!\n");
                }
                fp->parts[part_idx].xC_u.x0.xD = dobj_count - 1;
                fp->parts[part_idx].x8.x0.flags2_b6 = true;
            }
            part_idx += 1;
            ftAnim_GetNextJointInTree(&curr_joint, &tree_depth);
        }
    }
    fp->x203C.count = dobj_count;
}
