#include "ftdonkey_SpecialN.h"

#include "ftdonkey.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcoll.h"
#include "ft/inlines.h"

void ftDonkey_SetCallbacks_SpecialN(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cb.x21DC_callback_OnTakeDamage = &ftDk_Init_8010D774;
    fp->cb.x21E4_callback_OnDeath2 = &ftDk_Init_8010D774;
    fp->cb.x21F0_callback = &ftDk_SpecialN_DestroyAllEffects;
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

void ftDonkey_UpdateDKVelocityAfterPunch(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fp);
    fp->gr_vel =
        fp->facing_dir * (donkey_attr->SpecialN.x34_PUNCH_HORIZONTAL_VEL *
                          fp->mv.dk.specialn.xC);
}

void ftDk_SpecialN_StartMotion(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->fv.dk.x222C == donkey_attr->SpecialN.x2C_MAX_ARM_SWINGS) {
        Fighter_ChangeMotionState(gobj, 0x175, 0, NULL, 0.0f, 1.0f, 0.0f);
        fp->mv.dk.specialn.x8 = 1;
        fp->mv.dk.specialn.xC = fp->fv.dk.x222C;
        fp->fv.dk.x222C = 0;
    } else {
        Fighter_ChangeMotionState(gobj, 0x171, 0, NULL, 0.0f, 1.0f, 0.0f);
        fp->mv.dk.specialn.x8 = 0;
        fp->mv.dk.specialn.xC = 0;
    }
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->mv.dk.specialn.x0 = 0;
    fp->mv.dk.specialn.x4 = 0;
    fp->mv.dk.specialn.x14 = -1;
    fp->mv.dk.specialn.x10 = -1;
    ftCommon_8007D7FC(fp);
    fp->x80_self_vel.y = 0.0f;
    ftDonkey_SetCallbacks_SpecialN(gobj);
    ftAnim_8006EBA4(gobj);
}

void ftDk_SpecialAirN_StartMotion(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->fv.dk.x222C == donkey_attr->SpecialN.x2C_MAX_ARM_SWINGS) {
        Fighter_ChangeMotionState(gobj, 0x17A, 0, NULL, 0.0f, 1.0f, 0.0f);
        fp->mv.dk.specialn.x8 = 1;
        fp->mv.dk.specialn.xC = fp->fv.dk.x222C;
        fp->fv.dk.x222C = 0;
    } else {
        Fighter_ChangeMotionState(gobj, 0x176, 0, NULL, 0.0f, 1.0f, 0.0f);
        fp->mv.dk.specialn.x8 = 0;
        fp->mv.dk.specialn.xC = 0;
    }
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->mv.dk.specialn.x0 = 0;
    fp->mv.dk.specialn.x4 = 0;
    fp->mv.dk.specialn.x14 = -1;
    fp->mv.dk.specialn.x10 = -1;

    ftDonkey_SetCallbacks_SpecialN(gobj);
    ftAnim_8006EBA4(gobj);
}

void ftDk_SpecialN_8010E7B4(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, 0x172, 0, NULL, 0.0f, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialN(gobj);
    }
}

void ftDonkey_NullCallbacks(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cb.x21F0_callback = 0;
    fp->cb.x21D4_callback_EnterHitlag = 0;
    fp->cb.x21D8_callback_ExitHitlag = 0;
}

void ftDk_SpecialN_8010E840(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->x2D4_specialAttributes;
    if (0.0f == fp->x894_currentAnimFrame) {
        fp->fv.dk.x222C += 1;
        if (fp->fv.dk.x222C >= donkey_attr->SpecialN.x2C_MAX_ARM_SWINGS) {
            Fighter* fighter2 = fp;
            ft_800BFFD0(fighter2, 0x39, 0);
            fighter2->fv.dk.x222C = donkey_attr->SpecialN.x2C_MAX_ARM_SWINGS;
            ftDonkey_NullCallbacks(gobj);
            ft_8008A2BC(gobj);
        }
    }
}

void ftDk_SpecialN_8010E8E0(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftDonkey_NullCallbacks(gobj);
        ft_8008A2BC(gobj);
    }
}

void ftDk_SpecialN_8010E930(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->x2D4_specialAttributes;

    if (fp->x2200_ftcmd_var0) {
        if (fp->mv.dk.specialn.x8 == 0) {
            fp->mv.dk.specialn.x8++;
        }
    }
    if (fp->mv.dk.specialn.x8 == 1) {
        fp->mv.dk.specialn.x8++;
        if (fp->ground_or_air == GA_Air) {
            efSync_Spawn(0x4C9, gobj, fp->ft_bones[0].x0_jobj,
                         &fp->facing_dir);
        } else {
            efSync_Spawn(0x4C8, gobj, fp->ft_bones[0].x0_jobj,
                         &fp->facing_dir);
        }
    }
    if (fp->x914[0].state != HitCapsule_Disabled) {
        if (fp->mv.dk.specialn.x4 == 0) {
            fp->mv.dk.specialn.x4 = 1;
        }

        if (fp->mv.dk.specialn.x10 == -1) {
            fp->mv.dk.specialn.x10 = fp->x914[0].a_offset.z;
        }

        ftColl_8007ABD0(&fp->x914[0],
                        fp->mv.dk.specialn.x10 +
                            (fp->mv.dk.specialn.xC *
                             donkey_attr->SpecialN.x30_DAMAGE_PER_SWING),
                        gobj);

        if (fp->mv.dk.specialn.x14 == -1) {
            fp->mv.dk.specialn.x14 = fp->x914[1].a_offset.z;
        }

        ftColl_8007ABD0(&fp->x914[1],
                        fp->mv.dk.specialn.x14 +
                            (fp->mv.dk.specialn.xC *
                             donkey_attr->SpecialN.x30_DAMAGE_PER_SWING),
                        gobj);
    }

    if (fp->mv.dk.specialn.x4 == 1) {
        fp->mv.dk.specialn.x4 = 2;
        ftDonkey_UpdateDKVelocityAfterPunch(gobj);
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->fv.dk.x222C = 0;
        ftDonkey_NullCallbacks(gobj);
        ft_8008A2BC(gobj);
    }
}

void ftDk_SpecialN_8010EB0C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->x2200_ftcmd_var0) {
        if (fp->mv.dk.specialn.x8 == 0) {
            fp->mv.dk.specialn.x8++;
        }
    }

    if (fp->mv.dk.specialn.x8 == 1) {
        fp->mv.dk.specialn.x8++;
        if (fp->ground_or_air == GA_Air) {
            efSync_Spawn(0x4C9, gobj, fp->ft_bones[0].x0_jobj,
                         &fp->facing_dir);
        } else {
            efSync_Spawn(0x4C8, gobj, fp->ft_bones[0].x0_jobj,
                         &fp->facing_dir);
        }
    }

    if (fp->x914[0].state != HitCapsule_Disabled &&
        (fp->mv.dk.specialn.x4 == 0))
    {
        fp->mv.dk.specialn.x4 = 1;
    }

    if (fp->mv.dk.specialn.x4 == 1) {
        fp->mv.dk.specialn.x4 = 2;
        ftDonkey_UpdateDKVelocityAfterPunch(gobj);
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->fv.dk.x222C = 0;
        ftDonkey_NullCallbacks(gobj);
        ft_8008A2BC(gobj);
    }
}

void ftDk_SpecialN_8010EC5C(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, 0x177, 0, NULL, 0.0f, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialN(gobj);
    }
}

void ftDk_SpecialN_8010ECE8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->x2D4_specialAttributes;

    if (fp->x894_currentAnimFrame == 0.0f) {
        fp->fv.dk.x222C += 1;
        if (fp->fv.dk.x222C >= donkey_attr->SpecialN.x2C_MAX_ARM_SWINGS) {
            Fighter* fighter2 = fp;
            ft_800BFFD0(fighter2, 0x39, 0);
            fp->fv.dk.x222C = donkey_attr->SpecialN.x2C_MAX_ARM_SWINGS;
            ftDonkey_NullCallbacks(gobj);
            ft_800CC730(gobj);
        }
    }
}

void ftDk_SpecialN_8010ED88(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftDonkey_NullCallbacks(gobj);
        ft_800CC730(gobj);
    }
}

void ftDk_SpecialN_8010EDD8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->x2200_ftcmd_var0) {
        if (fp->mv.dk.specialn.x8 == 0) {
            fp->mv.dk.specialn.x8++;
        }
    }
    if (fp->mv.dk.specialn.x8 == 1) {
        fp->mv.dk.specialn.x8++;
        if (fp->ground_or_air == GA_Air) {
            efSync_Spawn(0x4C9, gobj, fp->ft_bones[0].x0_jobj,
                         &fp->facing_dir);
        } else {
            efSync_Spawn(0x4C8, gobj, fp->ft_bones[0].x0_jobj,
                         &fp->facing_dir);
        }
    }
    if (fp->x914[0].state != HitCapsule_Disabled) {
        if (fp->mv.dk.specialn.x10 == -1) {
            fp->mv.dk.specialn.x10 = fp->x914[0].a_offset.z;
        }
        ftColl_8007ABD0(&fp->x914[0],
                        fp->mv.dk.specialn.x10 +
                            (fp->mv.dk.specialn.xC *
                             donkey_attr->SpecialN.x30_DAMAGE_PER_SWING),
                        gobj);
        if (fp->mv.dk.specialn.x14 == -1) {
            fp->mv.dk.specialn.x14 = fp->x914[1].a_offset.z;
        }
        ftColl_8007ABD0(&fp->x914[1],
                        fp->mv.dk.specialn.x14 +
                            (fp->mv.dk.specialn.xC *
                             donkey_attr->SpecialN.x30_DAMAGE_PER_SWING),
                        gobj);
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->fv.dk.x222C = 0;
        ftDonkey_NullCallbacks(gobj);
        if (donkey_attr->SpecialN.x38_LANDING_LAG == 0.0f) {
            ft_800CC730(gobj);
        } else {
            ft_80096900(gobj, 1, 0, 1, 1.0f,
                        donkey_attr->SpecialN.x38_LANDING_LAG);
        }
    }
}

void ftDk_SpecialN_8010EF7C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->x2200_ftcmd_var0) {
        if (fp->mv.dk.specialn.x8 == 0) {
            fp->mv.dk.specialn.x8++;
        }
    }

    if (fp->mv.dk.specialn.x8 == 1) {
        fp->mv.dk.specialn.x8++;
        if (fp->ground_or_air == GA_Air) {
            efSync_Spawn(0x4C9, gobj, fp->ft_bones[0].x0_jobj,
                         &fp->facing_dir);
        } else {
            efSync_Spawn(0x4C8, gobj, fp->ft_bones[0].x0_jobj,
                         &fp->facing_dir);
        }
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->fv.dk.x222C = 0;
        ftDonkey_NullCallbacks(gobj);
        if (donkey_attr->SpecialN.x38_LANDING_LAG == 0.0f) {
            ft_800CC730(gobj);
        } else {
            ft_80096900(gobj, 1, 0, 1, 1.0f,
                        donkey_attr->SpecialN.x38_LANDING_LAG);
        }
    }
}

void ftDk_SpecialN_8010F094(HSD_GObj* gobj) {}

void ftDk_SpecialN_8010F098(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ft_8009917C(gobj)) {
        if ((fp->input.x668 & 0x200)) {
            Fighter_ChangeMotionState(gobj, 0x174, 0, NULL, 0.0f, 1.0f, 0.0f);
            fp->mv.dk.specialn.xC = fp->fv.dk.x222C;
            fp->fv.dk.x222C = 0;
            ftDonkey_SetCallbacks_SpecialN(gobj);
            ftAnim_8006EBA4(gobj);
        }
        if ((fp->input.x668 & 0x80000000)) {
            fp->mv.dk.specialn.x0 = 1;
        }
        if ((fp->x894_currentAnimFrame == 0.0f) && (fp->mv.dk.specialn.x0)) {
            Fighter_ChangeMotionState(gobj, 0x173, 0, NULL, 0.0f, 1.0f, 0.0f);
            ftDonkey_SetCallbacks_SpecialN(gobj);
        }
    }
}

void ftDk_SpecialN_8010F1D8(HSD_GObj* gobj) {}

void ftDk_SpecialN_8010F1DC(HSD_GObj* gobj) {}

void ftDk_SpecialN_8010F1E0(HSD_GObj* gobj) {}

void ftDk_SpecialN_8010F1E4(HSD_GObj* gobj) {}

void ftDk_SpecialN_8010F1E8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if ((fp->input.x668 & 0x200)) {
        Fighter_ChangeMotionState(gobj, 0x179, 0, NULL, 0.0f, 1.0f, 0.0f);
        fp->mv.dk.specialn.xC = fp->fv.dk.x222C;
        fp->fv.dk.x222C = 0;
        ftDonkey_SetCallbacks_SpecialN(gobj);
        ftAnim_8006EBA4(gobj);
    }
    if ((fp->input.x668 & 0x80000000)) {
        fp->mv.dk.specialn.x0 = 1;
    }
    if ((fp->x894_currentAnimFrame == 0.0f) && (fp->mv.dk.specialn.x0)) {
        Fighter_ChangeMotionState(gobj, 0x178, 0, NULL, 0.0f, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialN(gobj);
    }
}

void ftDk_SpecialN_8010F31C(HSD_GObj* gobj) {}

void ftDk_SpecialN_8010F320(HSD_GObj* gobj) {}

void ftDk_SpecialN_8010F324(HSD_GObj* gobj) {}

void ftDk_SpecialN_8010F328(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_SpecialN_8010F348(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_SpecialN_8010F368(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_SpecialN_8010F388(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_SpecialN_8010F3A8(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_SpecialN_8010F3C8(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftDk_SpecialN_8010F3E8(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftDk_SpecialN_8010F408(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftDk_SpecialN_8010F428(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftDk_SpecialN_8010F448(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftDk_SpecialN_8010F468(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ft_80082708(gobj)) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x176, 0x0C4C5080, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialN(gobj);
    }
}

void ftDk_SpecialN_8010F50C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ft_80082708(gobj)) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x177, 0x0C4C5080, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialN(gobj);
    }
}

void ftDk_SpecialN_8010F5B0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ft_80082708(gobj)) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x178, 0x0C4C5080, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialN(gobj);
    }
}

void ftDk_SpecialN_8010F654(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_800827A0(gobj) == 0) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x179, 0x0C4D508E, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialN(gobj);
    }
}

void ftDk_SpecialN_8010F6F8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_800827A0(gobj) == 0) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x17A, 0x0C4D508E, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialN(gobj);
    }
}

void ftDk_SpecialN_8010F79C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_80081D0C(gobj) == 1) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 0x171, 0x0C4C5080, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialN(gobj);
    }
}

void ftDk_SpecialN_8010F840(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_80081D0C(gobj) == 1) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 0x172, 0x0C4C5080, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialN(gobj);
    }
}

void ftDk_SpecialN_8010F8E4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_80081D0C(gobj) == 1) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 0x173, 0x0C4C5080, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialN(gobj);
    }
}

void ftDk_SpecialN_8010F988(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_80081D0C(gobj)) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 0x174, 0x0C4D508E, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialN(gobj);
    }
}

void ftDk_SpecialN_8010FA2C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_80081D0C(gobj)) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 0x175, 0x0C4D508E, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialN(gobj);
    }
}

void ftDk_SpecialN_DestroyAllEffects(HSD_GObj* gobj)
{
    efLib_DestroyAll(gobj);
}

void ftDk_SpecialN_DestroyAllEffectsPlus(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->fv.dk.x222C = 0;
    efLib_DestroyAll(gobj);
}
