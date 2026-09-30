/**
 * @file ftwaitanim.c
 * @brief Fighter idle wait animation logic
 * @details Handles the selection and looping of idle animations when
 * a fighter is standing still.
 * Module prefix: ftCo (Common)
 */
#include "ftwaitanim.h"

#include "ftanim.h"
#include "ftdata.h"
#include "ftdynamics.h"
#include "inlines.h"
#include <melee/it/it_26B1.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/random.h>

/**
 * @brief Checks if the fighter is currently holding an item with a standard hold style
 * @param fp Fighter state
 * @return true if holding an item (and not hold kind 2), false otherwise
 */
bool ftCo_8008A698(Fighter* fp)
{
    if (fp->item_gobj != NULL && itGetHoldKind(fp->item_gobj) != 2) {
        return true;
    }
    return false;
}

/**
 * @brief Forcibly sets the fighter's idle animation to the specified ID
 * @param gobj Fighter GObj
 * @param anim_id The specific animation ID to play
 */
void ftCo_8008A6D8(Fighter_GObj* gobj, s32 anim_id)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (anim_id != -1) {
        struct Fighter_WaitAnimData* anim = &fp->x24[anim_id];
        u8(*blend_data)[2] = &fp->x28[anim_id];
        ftData_80085CD8(fp, fp, anim_id);
        fp->anim_id = anim_id;
        ftCo_8009E7B4(fp, blend_data);
        fp->x3E4_fighterCmdScript.x8.u = anim->xC;
        fp->x3E4_fighterCmdScript.loop_count = 0;
        if (fp->x590 != NULL) {
            fp->x594.x594_s32 = anim->x10_animCurrFlags;
            ftAnim_8006EBE8(gobj, 0.0F, 1.0F, (*blend_data)[0]);
        }
        fp->x3E4_fighterCmdScript.timer = 0.0f;
        ftAnim_8006EBA4(gobj);
    }
}

/**
 * @brief Internal helper to check if the current animation is one of the base idle loops (ID 2 or 31)
 * @param fp Fighter state
 * @return true if the animation is a base idle loop
 */
static inline bool inlineA0(Fighter* fp)
{
    if (fp->anim_id == 2 || fp->anim_id == 31) {
        return true;
    }
    return false;
}

/**
 * @brief Selects a random animation ID from a weighted list
 * @param wait_data Array of WaitStructs containing animation IDs and weights, terminated by -1
 * @return Selected animation ID
 */
static inline enum_t getAnimID(WaitStruct* wait_data)
{
    WaitStruct* cur_data = wait_data;
    int max = HSD_Randi(100) + 1;
    int count = 0;
    while (cur_data->u.i.x != -1) {
        count += cur_data->u.i.y;
        if (max <= count) {
            return (enum_t) cur_data->u.p.x;
        }
        cur_data += 1;
    }
    HSD_ASSERTREPORT(86, 0, "wait anim data illegal!!\n", max);
}

/**
 * @brief Updates the fighter's idle animation, randomly selecting a new one from the given list if the current one finished
 * @param gobj Fighter GObj
 * @param wait_data Pointer to the array of potential idle animations and their selection weights
 */
void ftCo_8008A7A8(Fighter_GObj* gobj, WaitStruct* wait_data)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (wait_data == NULL ||
            (fp->item_gobj != NULL && fp->kind != Ft_Kind_Mewtwo &&
             fp->kind != Ft_Kind_Fox))
        {
            enum_t temp;
            temp = fp->anim_id;
            ftCo_8008A6D8(gobj, fp->anim_id);
            return;
        }
        {
            enum_t temp, anim_id;
            do {
                temp = anim_id = getAnimID(wait_data);
            } while (!inlineA0(fp) && fp->anim_id == temp);

            /// @todo Manually inlined ftCo_8008A6D8 here, not clean but only
            ///       way I could make it match
            {
                u8(*blend_data)[2];
                struct Fighter_WaitAnimData* anim;
                Fighter* fp = GET_FIGHTER(gobj);
                if (temp != -1) {
                    anim = &fp->x24[temp];
                    blend_data = &fp->x28[temp];
                    ftData_80085CD8(fp, fp, anim_id);
                    fp->anim_id = anim_id;
                    ftCo_8009E7B4(fp, blend_data);
                    fp->x3E4_fighterCmdScript.x8.u = anim->xC;
                    fp->x3E4_fighterCmdScript.loop_count = 0;
                    if (fp->x590 != NULL) {
                        fp->x594.x594_s32 = anim->x10_animCurrFlags;
                        ftAnim_8006EBE8(gobj, 0.0F, 1.0F, (*blend_data)[0]);
                    }
                    fp->x3E4_fighterCmdScript.timer = 0.0f;
                    ftAnim_8006EBA4(gobj);
                }
            }
        }
    }
}
