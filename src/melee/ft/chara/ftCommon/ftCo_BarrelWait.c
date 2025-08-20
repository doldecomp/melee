#include "ftCo_BarrelWait.h"

#include "ftCo_Damage.h"
#include "ftCo_Lift.h"

#include <placeholder.h>
#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcamera.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftdynamics.h"
#include "ft/types.h"
#include "gr/ground.h"

#include "lb/forward.h"

#include "lb/lbcollision.h"
#include "mp/mpcoll.h"

#include <common_structs.h>

/* 09EC44 */ static void ftCo_8009EC44(Fighter_GObj* gobj);

static inline void setCamData(ftCommonData* cd, CameraBox* cam)
{
    cam->x40 = cd->x4DC;
    cam->x48 = cd->x4E4;
}

void ftCo_8009EB18(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(4);

    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_BarrelWait, Ft_MF_None, 0.0f, 1.0f,
                              0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->death2_cb = ftCo_8009EAF8;
    fp->accessory1_cb = ftCo_8009EC44;
    ftCommon_8007E2FC(gobj);
    fp->x1988 = 2;
    fp->x221E_b0 = true;
    ftCommon_8007E2F4(fp, 0x1FF);
    setCamData(p_ftCommonData, fp->x890_cameraBox);
    ftCommon_8007EFC0(fp, 1);
}

void ftCo_BarrelWait_Anim(Fighter_GObj* gobj) {}

void ftCo_BarrelWait_IASA(Fighter_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->input.x668 & HSD_PAD_AB) {
        Ground_801C4DD0();
    }
}

void ftCo_BarrelWait_Phys(Fighter_GObj* gobj) {}

void ftCo_BarrelWait_Coll(Fighter_GObj* gobj) {}

void ftCo_8009EC44(Fighter_GObj* gobj)
{
    float param;
    PAD_STACK(4);
    Ground_801C4DA0(&GET_FIGHTER(gobj)->cur_pos, &param);
}

/// @todo Fake, need to find real size of #HurtCapsule
struct SmallerHitCapsule {
    /*  +0 */ HitCapsuleState state;
    /*  +4 */ u32 x4;
    /*  +8 */ u32 unk_count;
    /*  +C */ float damage;
    /* +10 */ Vec3 b_offset;
    /* +1C */ float scale;
    /* +20 */ int kb_angle;
    /* +24 */ u32 x24;
    /* +28 */ u32 x28;
    /* +2C */ u32 x2C;
    /* +30 */ u32 element;
    /* +34 */ char pad_34[0xFC];
};

void ftCo_8009EC70(Fighter_GObj* gobj, Vec3* pos, UNK_T arg2, float kb_angle)
{
    {
        Fighter* fp = gobj->user_data;
        fp->bury_timer_2 = p_ftCommonData->bury_timer_unk2;
        fp->cur_pos = *pos;
        mpColl_80043680(&fp->coll_data, pos);
        ftCamera_80076064(fp);
        {
            struct SmallerHitCapsule hit;
            PAD_STACK(4);
            lbColl_80008D30((HitCapsule*) &hit, arg2);
            ftColl_800788D4(gobj);
            if (kb_angle < 0) {
                kb_angle += 360;
            }
            kb_angle = fp->facing_dir < 0.0f ? kb_angle : 180.0f - kb_angle;
            fp->dmg.kb_applied =
                ftColl_80079EA8(fp, (HitCapsule*) &hit, hit.unk_count);
            fp->dmg.x1848_kb_angle = kb_angle;
            fp->dmg.facing_dir_1 = fp->facing_dir;
            fp->dmg.x184c_damaged_hurtbox = 0;
            fp->dmg.x1854_collpos = fp->cur_pos;
            fp->dmg.x1860_element = hit.element;
            Fighter_UnkTakeDamage_8006CC30(fp, hit.damage);
        }
        ftCo_8008DCE0(gobj, 91, 0);
    }
}
