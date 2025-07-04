#include <platform.h>

#include "lb/forward.h"

#include "ftMs_SpecialLw.h"

#include "math.h"

#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftlib.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftMars/types.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

void ftMs_SpecialLw_Enter(HSD_GObj* gobj)
{
    Fighter* fp0 = GET_FIGHTER(gobj);
    fp0->self_vel.y = 0;

    Fighter_ChangeMotionState(gobj, 369, 0, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);

    {
        Fighter* fp1 = GET_FIGHTER(gobj);
        fp1->cmd_vars[1] = 0;
        fp1->mv.ms.speciallw.x0 = 0;
    }
}

void ftMs_SpecialAirLw_Enter(HSD_GObj* gobj)
{
    u8 _[4];

    {
        Fighter* fp = GET_FIGHTER(gobj);
        MarsAttributes* da = fp->dat_attrs;
        fp->self_vel.x /= da->x4C;
        fp->self_vel.y = 0;
    }

    Fighter_ChangeMotionState(gobj, 371, 0, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);

    {
        Fighter* fp;
        fp = GET_FIGHTER(gobj);
        fp->cmd_vars[1] = 0;
        fp->mv.ms.speciallw.x0 = 0;
    }
}

void ftMs_SpecialLw_Anim(HSD_GObj* gobj)
{
    u8 _[16];

    Fighter* fp = GET_FIGHTER(gobj);
    MarsAttributes* da = getFtSpecialAttrsD(fp);

    if (fp->cmd_vars[1] == 1) {
        fp->cmd_vars[1] = 2;
        ftColl_8007B1B8(gobj, (ShieldDesc*) &da->x64,
                        &ftMs_SpecialLw_80139140);
        fp->x221B_b1 = true;
        fp->shield_unk0 = da->x60;
        fp->shield_unk1 = da->x60;
    } else if (fp->cmd_vars[1] == 0) {
        fp->x221B_b0 = false;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftMs_SpecialAirLw_Anim(HSD_GObj* gobj)
{
    u8 _[16];

    Fighter* fp = GET_FIGHTER(gobj);
    MarsAttributes* da = getFtSpecialAttrsD(fp);

    if (fp->cmd_vars[1] == 1) {
        fp->cmd_vars[1] = 2;
        ftColl_8007B1B8(gobj, (ShieldDesc*) &da->x64,
                        &ftMs_SpecialLw_80139140);
        fp->x221B_b1 = true;
        fp->shield_unk0 = da->x60;
        fp->shield_unk1 = da->x60;
    } else if (fp->cmd_vars[1] == 0) {
        fp->x221B_b0 = false;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftMs_SpecialLw_IASA(HSD_GObj* gobj) {}

void ftMs_SpecialAirLw_IASA(HSD_GObj* gobj) {}

void ftMs_SpecialLw_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
    ftColl_8007AEE0(gobj);
}

void ftMs_SpecialAirLw_Phys(HSD_GObj* gobj)
{
    u8 _[16];

    Fighter* fp = gobj->user_data;
    MarsAttributes* da = getFtSpecialAttrsD(fp);
    ftCommon_8007D494(fp, da->x54, da->x58);
    ftCommon_8007CE94(fp, da->x50);
    ftColl_8007AEE0(gobj);
}

// 80138CC0 001358A0
// https://decomp.me/scratch/PQPYD
void ftMs_SpecialLw_Coll(HSD_GObj* gobj)
{
    if (ft_800827A0(gobj) == 0) {
        ftMs_SpecialLw_80138D38(gobj);
    }
}

// 80138CFC 001358DC
// https://decomp.me/scratch/ZAAJM
void ftMs_SpecialAirLw_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj) != 0) {
        ftMs_SpecialLw_80138DD0(gobj);
    }
}

void ftMs_SpecialLw_80138D38(HSD_GObj* gobj)
{
    u8 _[16];

    {
        Fighter* fp = gobj->user_data;
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 371, 0x0C4C508C, fp->cur_anim_frame, 1,
                                  0, NULL);
    }

    {
        Fighter* fp = gobj->user_data;
        MarsAttributes* da = getFtSpecialAttrsD(fp);

        if (fp->cmd_vars[1] == 2) {
            ftColl_8007B1B8(gobj, (ShieldDesc*) &da->x64,
                            &ftMs_SpecialLw_80139140);
            fp->x221B_b1 = true;
        }
    }
}

void ftMs_SpecialLw_80138DD0(HSD_GObj* gobj)
{
    u8 _[16];

    {
        Fighter* fp0 = gobj->user_data;
        ftCommon_8007D7FC(fp0);
        Fighter_ChangeMotionState(gobj, 369, 0x0C4C508C, fp0->cur_anim_frame,
                                  1, 0, NULL);
    }

    {
        Fighter* fp = gobj->user_data;
        MarsAttributes* da = getFtSpecialAttrsD(fp);

        if (fp->cmd_vars[1] == 2) {
            ftColl_8007B1B8(gobj, (ShieldDesc*) &da->x64,
                            &ftMs_SpecialLw_80139140);
            fp->x221B_b1 = true;
        }
    }
}

#define SOLUTION 1
void ftMs_SpecialLwHit_Anim(HSD_GObj* gobj)
{
    ssize_t idx;

    s32 hb;
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    s32 sv1 = fp->mv.ms.speciallw.x0;

    /// @todo required for some reason
    fp->mv.ms.speciallw.x0;

    if (sv1 > 0 && ftLib_800872A4(gobj) == FTKIND_EMBLEM) {
/// @todo register swap:
#if SOLUTION == 0
        for (idx = 0; idx < 4; idx++) {
            if (fp->x914[idx].state == HitCapsule_Enabled) {
                ftColl_8007ABD0(&fp->x914[idx], fp->mv.ms.speciallw.x0, gobj);
            }
        }

// matches but gross:
#elif SOLUTION == 1
        idx = 0;
        hb = (s32) fp;
        while (idx < 4) {
            if (*(s32*) (hb + 2324) == HitCapsule_Enabled) {
                ftColl_8007ABD0((HitCapsule*) (hb + 2324),
                                fp->mv.ms.speciallw.x0, gobj);
            }
            idx++;
            hb += 312;
        }
#endif
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}
#undef SOLUTION

#define SOLUTION 1
// https://decomp.me/scratch/Jx7Ov
void ftMs_SpecialAirLwHit_Anim(HSD_GObj* gobj)
{
    ssize_t idx;

    s32 hb;
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    s32 sv1 = fp->mv.ms.speciallw.x0;

    /// @todo required for some reason
    fp->mv.ms.speciallw.x0;

    if (sv1 > 0 && ftLib_800872A4(gobj) == FTKIND_EMBLEM) {
/// @todo register swap:
#if SOLUTION == 0
        for (idx = 0; idx < 4; idx++) {
            if (fp->x914[idx].state == HitCapsule_Enabled) {
                ftColl_8007ABD0(&fp->x914[idx], fp->mv.ms.speciallw.x0, gobj);
            }
        }

// matches but gross:
#elif SOLUTION == 1
        idx = 0;
        hb = (s32) fp;
        while (idx < 4) {
            if (*(s32*) (hb + 2324) == HitCapsule_Enabled) {
                ftColl_8007ABD0((HitCapsule*) (hb + 2324),
                                fp->mv.ms.speciallw.x0, gobj);
            }
            idx++;
            hb += 312;
        }
#endif
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}
#undef SOLUTION

// 80138FC0 00135BA0
void ftMs_SpecialLwHit_IASA(HSD_GObj* gobj) {}

// 80138FC4 00135BA4
void ftMs_SpecialAirLwHit_IASA(HSD_GObj* gobj) {}

// 80138FC8 00135BA8
// https://decomp.me/scratch/u66PG
void ftMs_SpecialLwHit_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

// 80138FE8 00135BC8
// https://decomp.me/scratch/QnjxB
void ftMs_SpecialAirLwHit_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

// 80139008 00135BE8
// https://decomp.me/scratch/2SGFK
void ftMs_SpecialLwHit_Coll(HSD_GObj* gobj)
{
    if (ft_80082708(gobj) == 0) {
        ftMs_SpecialLw_80139080(gobj);
    }
}

// 80139044 00135C24
// https://decomp.me/scratch/3W48X
void ftMs_SpecialAirLwHit_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj) != 0) {
        ftMs_SpecialLw_801390E0(gobj);
    }
}

// 80139080 00135C60
// https://decomp.me/scratch/w0qtf
void ftMs_SpecialLw_80139080(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 372, 0x0C4C508E, fp->cur_anim_frame, 1, 0,
                              NULL);
}

// 801390E0 00135CC0
// https://decomp.me/scratch/qAmn3
void ftMs_SpecialLw_801390E0(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 370, 0x0C4C508E, fp->cur_anim_frame, 1, 0,
                              NULL);
}

void ftMs_SpecialLw_80139140(HSD_GObj* gobj)
{
    s32 temp_r0;

    u8 unused0[4];
    Vec3 sp18;

    u8 unused1[12];

    {
        Fighter* fp = gobj->user_data;
        MarsAttributes* da = fp->dat_attrs;

        fp->facing_dir = fp->specialn_facing_dir;
        temp_r0 = (s32) fp->x19A4;

        if (temp_r0 > 0) {
            fp->mv.ms.speciallw.x0 = (s32) (temp_r0 * da->x5C);
        }

        lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_HipN)].joint, 0,
                    &sp18);
        lb_800119DC(&sp18, 120, 0.9, 0.02, M_PI / 3);

        {
            enum_t msid;

            if (fp->ground_or_air == GA_Ground) {
                msid = 370;
            } else {
                msid = 372;
            }

            Fighter_ChangeMotionState(gobj, msid, 0, 0, 1, 0, NULL);
        }
    }

    {
        Fighter* ft_2;
        ft_2 = gobj->user_data;
        ft_2->x2219; // required for regalloc
        if (!ft_2->x2219_b0) {
            switch (ftLib_800872A4(gobj)) {
            case 18:
                efSync_Spawn(
                    1265, gobj,
                    ft_2->parts[ftParts_8007500C(ft_2, FtPart_RShoulderN)]
                        .joint,
                    &ft_2->facing_dir);
                break;
            case 26:
                efSync_Spawn(
                    1296, gobj,
                    ft_2->parts[ftParts_8007500C(ft_2, FtPart_RShoulderN)]
                        .joint,
                    &ft_2->facing_dir);
                break;
            }
            ft_2->x2219_b0 = true;
        }

        ft_2->pre_hitlag_cb = NULL;
        ft_2->post_hitlag_cb = NULL;
        ft_2->accessory4_cb = NULL;
    }
}
