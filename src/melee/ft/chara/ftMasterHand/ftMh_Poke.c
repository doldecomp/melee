#include <platform.h>

#include "ftMh_Poke.h"

#include "ftMh_Wait1_2.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftanim.h"
#include "ft/ftbosslib.h"
#include "ft/types.h"
#include "ftMasterHand/types.h"
#include "lb/lbvector.h"
#include "pl/player.h"

#include <dolphin/mtx.h>
#include <baselib/random.h>
#include <MetroTRK/intrinsics.h>

void ftMh_PaperCrush_Coll(HSD_GObj* gobj) {}

void ftMh_MS_358_80152880(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;

    u8 _[8];

    Fighter_ChangeMotionState(gobj, ftMh_MS_Poke1, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
    fp->mv.mh.unk13.x0 = da->x94 + HSD_Randi(da->x90 - da->x94);
    fp->mv.mh.unk13.x4 = 0;
}

void ftMh_Poke1_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->mv.mh.unk13.x4 = 1;

        if (--fp->mv.mh.unk13.x0 < 0) {
            fp->mv.mh.unk13.x4 = 0;
            fp->self_vel.x = 0;
            fp->self_vel.y = 0;

            {
                Fighter* fp = GET_FIGHTER(gobj);
                Fighter_ChangeMotionState(gobj, ftMh_MS_Poke2, 0, 0, 1, 0, 0);
                ftAnim_8006EBA4(gobj);
                ft_PlaySFX(fp, 320007, 127, 64);
            }
        }
    }
}

void ftMh_Poke2_Anim(HSD_GObj* arg0)
{
    if (!ftAnim_IsFramesRemaining(arg0)) {
        ftMh_MS_389_80151018(arg0);
    }
}

void ftMh_Poke1_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

static inline float my_sqrtf(float x)
{
    static const double _half = .5;
    static const double _three = 3.0;

    u8 _[4] = { 0 };

    volatile float y;
    if (x > 0) {
        double guess = __frsqrte((double) x); // returns an approximation to
        guess = _half * guess *
                (_three - guess * guess * x); // now have 12 sig bits
        guess = _half * guess *
                (_three - guess * guess * x); // now have 24 sig bits
        guess = _half * guess *
                (_three - guess * guess * x); // now have 32 sig bits
        y = (float) (x * guess);
        return y;
    }
    return x;
}

static inline float my_lbVector_Len(Vec3* vec)
{
    return my_sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

void ftMh_Poke1_Phys(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ft_80085134(gobj);

    if (fp->mv.mh.unk13.x4) {
        ftData* ftData = fp->ft_data;
        ftMasterHand_SpecialAttrs* da = ftData->ext_attr;

        {
            Vec3 pos;
            ftBossLib_8015C208(gobj, &pos);
            pos.x += da->x98;
            pos.y += da->x9C;
            pos.z = 0;

            {
                Vec3 vel;
                lbVector_Diff(&pos, &fp->cur_pos, &vel);
                {
                    float len = my_lbVector_Len(&vel);
                    if (len < da->x2C) {
                        fp->self_vel.x = vel.x;
                        fp->self_vel.y = vel.y;
                    } else {
                        lbVector_Normalize(&vel);
                        {
                            float speed = len * da->x28;
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
