#include "ftcrazyhandrockcrush0.h"

#include "types.h"

#include <placeholder.h>
#include <Runtime/platform.h>

#include <melee/ft/fighter.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ftbosslib.h>
#include <melee/ft/inlines.h>
#include <melee/ft/types.h>
#include "ftcrazyhandtagcancel.h"
#include <melee/ft/kinds/ftMasterHand/types.h>
#include <melee/lb/lbvector.h>
#include <melee/pl/player.h>

#include <sysdolphin/baselib/forward.h>

#include <dolphin/mtx.h>
#include <sysdolphin/baselib/random.h>

static inline float my_sqrtf(float x)
{
    volatile float y;

    if (x > 0) {
        double guess = __frsqrte((double) x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        y = (float) (x * guess);
        return y;
    }
    return x;
}

static inline float my_lbVector_Len(Vec3* vec)
{
    return my_sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

void ftCh_Init_80157DF8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    PAD_STACK(8);
    Fighter_ChangeMotionState(gobj, 0x163, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->mv.ch.unk13.x0 = da->x58 + HSD_Randi(da->x54 - da->x58);
    fp->mv.ch.unk13.x4 = 0;
}

void ftCh_RockCrushUp_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->mv.ch.unk13.x4 = 1;

        if (--fp->mv.ch.unk13.x0 < 0) {
            fp->mv.ch.unk13.x4 = 0;
            fp->self_vel.x = 0;
            fp->self_vel.y = 0;

            {
                Fighter* fp = GET_FIGHTER(gobj);
                Fighter_ChangeMotionState(gobj, 0x164, 0, 0, 1.0f, 0.0f, NULL);
                ftAnim_8006EBA4(gobj);
                ft_PlaySFX(fp, 0x4E207, 127, 64);
            }
        }
    }
}

void ftCh_RockCrushWait_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_RockCrushUp_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_RockCrushUp_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ft_80085134(gobj);

    if (fp->mv.ch.unk13.x4) {
        ftData* ftData = fp->ft_data;
        ftCrazyHand_DatAttrs* da = ftData->ext_attr;

        {
            Vec3 pos;
            ftBossLib_8015C208(gobj, &pos);
            pos.x += da->x5C;
            pos.y += da->x60;
            pos.z = 0;

            {
                Vec3 vel;
                lbVector_Diff(&pos, &fp->cur_pos, &vel);
                {
                    float len = my_lbVector_Len(&vel);
                    if (len < da->x14) {
                        fp->self_vel.x = vel.x;
                        fp->self_vel.y = vel.y;
                    } else {
                        lbVector_Normalize(&vel);
                        {
                            float speed = len * da->x10;
                            vel.x *= speed;
                            vel.y *= speed;
                            vel.z *= speed;
                        }
                        fp->self_vel.x = vel.x;
                        fp->self_vel.y = vel.y;
                    }
                }
            }
        }
    }
}

void ftCh_RockCrushUp_Coll(HSD_GObj* gobj) {}
