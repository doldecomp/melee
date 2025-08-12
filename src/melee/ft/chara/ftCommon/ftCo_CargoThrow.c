#include <platform.h>

#include "ft/forward.h"

#include "ftCo_CargoThrow.h"

#include "ftCo_CargoFall.h"
#include "ftCo_CargoWait.h"
#include "ftCo_Damage.h"
#include "math.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftDonkey/types.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

/* 09C02C */ static bool ftCo_8009C02C(Fighter_GObj* gobj, FtMotionId msid);
/* 09C170 */ static void ftCo_8009C170(Fighter_GObj* gobj);
/* 09C45C */ static void ftCo_8009C45C(Fighter_GObj* gobj);

void ftCo_CargoWait2_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCo_8008F744(gobj);
    if (!fp->x221C_b6) {
        if (fp->ground_or_air == GA_Air) {
            ftCo_8009BC58(gobj);
        } else {
            ftCo_8009B518(gobj);
        }
    }
}

void ftCo_CargoWait2_Phys(Fighter_GObj* gobj)
{
    ftCo_Damage_Phys(gobj);
}

void ftCo_CargoWait2_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Ground) {
        if (ft_80082708(gobj) == GA_Ground) {
            ftCommon_8007D5D4(fp);
        }
    } else if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
    }
}

static inline FtMotionId inlineA0(Fighter* fp)
{
    FtMotionId msid = fp->motion_id;
    if (fp->input.x668 & HSD_PAD_AB) {
        if (ABS(fp->input.lstick.x) >= p_ftCommonData->x98) {
            if (fp->input.lstick.x * fp->facing_dir > 0) {
                msid = fp->x2CC->x4_motion_state;
                msid += 10;
            } else {
                msid = fp->x2CC->x4_motion_state;
                msid += 11;
            }
        } else {
            if (fp->input.lstick.y >=
                p_ftCommonData->attackhi3_stick_threshold_y)
            {
                msid = fp->x2CC->x4_motion_state;
                msid += 12;
            } else if (fp->input.lstick.y <= p_ftCommonData->xB0) {
                msid = fp->x2CC->x4_motion_state;
                msid += 13;
            }
        }
    }
    return msid;
}

bool ftCo_8009BF3C(Fighter_GObj* gobj)
{
    FtMotionId msid = inlineA0(gobj->user_data);
    if (msid != GET_FIGHTER(gobj)->motion_id) {
        ftCo_8009C02C(gobj, msid);
        return true;
    }
    return false;
}

bool ftCo_8009C02C(Fighter_GObj* gobj, FtMotionId msid)
{
    u8 _[16] = { 0 };
    Fighter* fp = gobj->user_data;
    {
        MotionFlags mf;
        FtMotionId msid1;
        if (fp->ground_or_air == GA_Air) {
            mf = 1;
        } else {
            mf = 0;
        }
        if (fp->ground_or_air == GA_Air) {
            msid1 = msid + 4;
        } else {
            msid1 = msid;
        }
        Fighter_ChangeMotionState(gobj, msid1, mf, 0, 1, 0, NULL);
    }
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
    {
        FtMotionId msid1 = msid;
        msid1 -= fp->x2CC->x4_motion_state + 10;
        msid1 += ftCo_MS_ThrownFF;
        return ftCo_800DE3FC(fp->victim_gobj, msid1, 1);
    }
}

void ftCo_CargoThrowF_Anim(Fighter_GObj* gobj)
{
    ftCo_800DD724(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D92C(gobj);
    }
}

void ftCo_CargoThrowF_IASA(Fighter_GObj* gobj)
{
    ftCo_ThrowF_IASA(gobj);
}

void ftCo_CargoThrowF_Phys(Fighter_GObj* gobj)
{
    ftCo_ThrowF_Phys(gobj);
}

static inline void inlineB0(Fighter_GObj* gobj, FtMotionId msid)
{
    Fighter* fp = gobj->user_data;
    float facing_dir = fp->facing_dir;
    if (facing_dir != fp->facing_dir1) {
        fp->facing_dir = fp->facing_dir1;
    }
    Fighter_ChangeMotionState(gobj, msid,
                              Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim |
                                  Ft_MF_UpdateCmd | Ft_MF_SkipItemVis |
                                  Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |
                                  Ft_MF_SkipModelFlags | Ft_MF_Unk27,
                              fp->cur_anim_frame, 1, 0, NULL);
    fp->facing_dir = facing_dir;
    ftCommon_8007E2F4(fp, 0x1FF);
}

static inline void inlineB1(Fighter_GObj* gobj, FighterEvent cb, int offset)
{
    Fighter* fp = GET_FIGHTER(gobj);
    cb(fp);
    inlineB0(gobj, fp->motion_id + offset);
}

void ftCo_8009C170(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    inlineB1(gobj, ftCommon_8007D5D4, 4);
}

void ftCo_CargoThrowF_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, ftCo_8009C170);
}

void ftCo_CargoThrowB_Anim(Fighter_GObj* gobj)
{
    ftCo_ThrowB_Anim(gobj);
}

void ftCo_CargoThrowB_IASA(Fighter_GObj* gobj)
{
    ftCo_ThrowB_IASA(gobj);
}

void ftCo_CargoThrowB_Phys(Fighter_GObj* gobj)
{
    ftCo_ThrowB_Phys(gobj);
}

void ftCo_CargoThrowB_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, ftCo_8009C170);
}

void ftCo_CargoThrowHi_Anim(Fighter_GObj* gobj)
{
    ftCo_ThrowHi_Anim(gobj);
}

void ftCo_CargoThrowHi_IASA(Fighter_GObj* gobj)
{
    ftCo_ThrowHi_IASA(gobj);
}

void ftCo_CargoThrowHi_Phys(Fighter_GObj* gobj)
{
    ftCo_ThrowHi_Phys(gobj);
}

void ftCo_CargoThrowHi_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, ftCo_8009C170);
}

void ftCo_CargoThrowLw_Anim(Fighter_GObj* gobj)
{
    ftCo_ThrowLw_Anim(gobj);
}

void ftCo_CargoThrowLw_IASA(Fighter_GObj* gobj)
{
    ftCo_ThrowLw_IASA(gobj);
}

void ftCo_CargoThrowLw_Phys(Fighter_GObj* gobj)
{
    ftCo_ThrowLw_Phys(gobj);
}

void ftCo_CargoThrowLw_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, ftCo_8009C170);
}

void ftCo_CargoThrowAir_Anim(Fighter_GObj* gobj)
{
    ftCo_800DD724(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D92C(gobj);
    }
}

void ftCo_CargoThrowAir_IASA(Fighter_GObj* gobj) {}

void ftCo_CargoThrowAir_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftCo_CargoThrowAir_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, ftCo_8009C45C);
}

void ftCo_8009C45C(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    inlineB1(gobj, ftCommon_8007D7FC, -4);
}
