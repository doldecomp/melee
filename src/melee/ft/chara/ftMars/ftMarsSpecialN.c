#include <melee/ft/chara/ftMars/ftMars.h>

#include <melee/ef/eflib.h>
#include <melee/ft/code_80081B38.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftparts.h>
#include <melee/lb/lbunknown_001.h>
#include <melee/lb/lbunknown_003.h>

void ftMars_SpecialN_StartMotion(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    MarsAttributes* attrs = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    fp->cb.x21EC_callback = &ftMars_80136730;

    fp->xEC_ground_vel /= attrs->xC;
    Fighter_ChangeMotionState(gobj, 0x155, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
}

void ftMars_SpecialAirN_StartMotion(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    MarsAttributes* attrs = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    fp->cb.x21EC_callback = &ftMars_80136730;

    fp->x80_self_vel.x /= attrs->xC;

    if (fp->x80_self_vel.y <= 0.0f) {
        fp->x80_self_vel.y = 0.0f;
    }

    Fighter_ChangeMotionState(gobj, 0x159, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
}

// 80136844 00133424
// https://decomp.me/scratch/Go6FC
void ftMars_80136844(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMars_80136E74(gobj);

        if (((Fighter*) gobj->user_data)->x4_fighterKind == FTKIND_MARS)
            ft_800BFFD0(gobj->user_data, 0x63, 0);
        else
            ft_800BFFD0(gobj->user_data, 0x64, 0);
    }
}

// 801368AC 0013348C
// https://decomp.me/scratch/XBFKN
void ftMars_801368AC(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMars_80136EAC(gobj);

        if (((Fighter*) gobj->user_data)->x4_fighterKind == FTKIND_MARS)
            ft_800BFFD0(gobj->user_data, 0x63, 0);
        else
            ft_800BFFD0(gobj->user_data, 0x64, 0);
    }
}

// 80136914 001334F4
void ftMars_80136914(HSD_GObj* gobj)
{
    return;
}

// 80136918 001334F8
void ftMars_80136918(HSD_GObj* gobj)
{
    return;
}

void ftMars_8013691C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    MarsAttributes* attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    ftCommon_8007C930(fp, attr->x10);
    ftCommon_8007CB74(gobj);
}

void ftMars_8013695C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    MarsAttributes* attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    ftCommon_8007D4B8(fp);
    ftCommon_8007CE94(fp, attr->x10);
}

// 801369A4 00133584
// https://decomp.me/scratch/bR5HF
void ftMars_801369A4(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj))
        ftMars_80136A1C(gobj);
}

// 801369E0 001335C0
// https://decomp.me/scratch/cCPAH
void ftMars_801369E0(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj))
        ftMars_80136A7C(gobj);
}

// 80136A1C 001335FC
// https://decomp.me/scratch/9GhD1
void ftMars_80136A1C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCommon_8007D5D4(fp);

    Fighter_ChangeMotionState(gobj, 0x159, 0x0C4C5084, 0,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 80136A7C 0013365C
// https://decomp.me/scratch/GU6fn
void ftMars_80136A7C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, 0x155, 0x0C4C5084, 0,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftMars_80136ADC(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    s32* specialAttrs = fp->x2D4_specialAttributes;
    Vec3 sp28;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[28];
#endif

    if (fp->sv.ms.specialn.x0 % 30 == 0) {
        lb_8000B1CC(fp->x5E8_fighterBones[ftParts_8007500C(fp, 4)].x0_jobj, 0,
                    &sp28);
        lb_800119DC(&sp28, 10, 0.5f, 0.05f, 60 * M_PI / 180);
    }

    fp->sv.ms.specialn.x0++;

    if ((s32) fp->sv.ms.specialn.x0 > *specialAttrs * 30) {
        fp->x2200_ftcmd_var0 = 1;
        ftMars_80137354(gobj);
    }
}

void ftMars_80136BB4(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    MarsAttributes* attrs = fp->x2D4_specialAttributes;
    Vec3 sp28;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[28];
#endif

    if ((s32) fp->sv.ms.specialn.x0 % 30 == 0) {
        lb_8000B1CC(fp->x5E8_fighterBones[ftParts_8007500C(fp, 4)].x0_jobj, 0,
                    &sp28);
        lb_800119DC(&sp28, 10, 0.5f, 0.05f, 60 * M_PI / 180);
    }
    fp->sv.ms.specialn.x0++;
    if ((s32) fp->sv.ms.specialn.x0 > attrs->x0 * 30) {
        fp->x2200_ftcmd_var0 = 1;
        ftMars_801373B8(gobj);
    }
}

// 80136C8C 0013386C
// Interrupt_MarthNeutralBCharge
// https://decomp.me/scratch/zR8Hv
void ftMars_80136C8C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if ((fp->input.x65C_heldInputs & 0x200) == 0) {
        fp->x2200_ftcmd_var0 = 0;
        ftMars_80137354(gobj);
    }
}

// 80136CC4 001338A4
// https://decomp.me/scratch/ykJFN
void ftMars_80136CC4(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if ((fp->input.x65C_heldInputs & 0x200) == 0) {
        fp->x2200_ftcmd_var0 = 0;
        ftMars_801373B8(gobj);
    }
}

// 80136CFC 001338DC
// https://decomp.me/scratch/Q3NsK
void ftMars_80136CFC(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

// 80136D1C 001338FC
// https://decomp.me/scratch/LVDnG
void ftMars_80136D1C(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

// 80136D3C 0013391C
// https://decomp.me/scratch/XmmUv
void ftMars_80136D3C(HSD_GObj* gobj)
{
    if (ft_80082708(gobj) == 0) {
        ftMars_80136DB4(gobj);
    }
}

// 80136D78 00133958
// https://decomp.me/scratch/tjkA9
void ftMars_80136D78(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj) != 0) {
        ftMars_80136E14(gobj);
    }
}

// 80136DB4 00133994
// https://decomp.me/scratch/eJxjC
void ftMars_80136DB4(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    ftCommon_8007D5D4(gobj->user_data);
    Fighter_ChangeMotionState(gobj, 0x15A, 0x0C4C5A86, 0,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 80136E14 001339F4
// https://decomp.me/scratch/mzQdp
void ftMars_80136E14(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x156, 0x0C4C5A86, 0,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 80136E74 00133A54
// https://decomp.me/scratch/M7HBN
void ftMars_80136E74(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 0x156, 0x1200, 0, 0.0f, 1.0f, 0.0f);
}

// 80136EAC 00133A8C
// https://decomp.me/scratch/RkI7l
void ftMars_80136EAC(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 0x15A, 0x1200, 0, 0.0f, 1.0f, 0.0f);
}

// 80136EE4 00133AC4
// https://decomp.me/scratch/e4mhD
void ftMars_80136EE4(HSD_GObj* gobj)
{
    s32 ndx;
    MarsAttributes* attr;
    Fighter* fp;

    fp = gobj->user_data;
    attr = fp->x2D4_specialAttributes;
    if (fp->x2200_ftcmd_var0 == 0) {
        s32 hb = (s32) fp;
        ndx = 0;
        while (ndx < 4) {
            if (*(s32*) (hb + 0x914) == 1) {
                ftColl_8007ABD0(
                    (HitCapsule*) (hb + 0x914),

#if MUST_MATCH
                    (f32) (attr->x4 + fp->sv.ms.specialn.x0 / 30 * attr->x8),
#else
                    attr->x4 + fp->sv.ms.specialn.x0 / 30.0F * attr->x8,
#endif

                    gobj);
            }
            ndx++;
            hb += 0x138;
        }
    }
    if (fp->x894_currentAnimFrame == 9.0f) {
        Vec3 position;

        /// @todo Unused stack.
#ifdef MUST_MATCH
        u8 _[20];
#endif

        // JObj_GetWorldPos(r3=JObj,r4=UnkPointer,r5=StoreResult)
        //         Fighter_BonePersonalToCommon
        lb_8000B1CC(fp->x5E8_fighterBones[ftParts_8007500C(fp, 4)].x0_jobj, 0,
                    &position);
        // AestheticWindEffect(r3=sourcelocation,r4=duration,f1=radiusSize,f2=effectdegradation,f3=unk)
        lb_800119DC(&position, 120, 0.9f, 0.02f, 60 * M_PI / 180);
    }
    // FrameTimerCheck
    if (!ftAnim_IsFramesRemaining(gobj)) {
        // AS_014_Wait_PlayerCheck
        ft_8008A2BC(gobj);
    }
    return;
}

// 80137010 00133BF0
// https://decomp.me/scratch/pIor0
void ftMars_80137010(HSD_GObj* gobj)
{
    s32 ndx;
    MarsAttributes* attr;
    Fighter* fp;

    fp = gobj->user_data;
    attr = fp->x2D4_specialAttributes;
    if (fp->x2200_ftcmd_var0 == 0) {
        // register swap:
        // s32 ndx;
        // for (ndx = 0; ndx < 4; ndx++) {
        //     if (fp->x914[ndx].x0 == 1) {
        //         // Hitbox_ApplyDamageStalingAndMore
        //         ftColl_8007ABD0(&fp->x914[ndx], (f32) (attr->x4 +
        //         (s32)fp->sv.ms.specialn.x0 / 30 * attr->x8), gobj);
        //     }
        // }

        // matches but gross:
        s32 hb = (s32) fp;
        ndx = 0;
        while (ndx < 4) {
            if (*(s32*) (hb + 0x914) == 1) {
                ftColl_8007ABD0(
                    (HitCapsule*) (hb + 0x914),

#if MUST_MATCH
                    (f32) (attr->x4 + fp->sv.ms.specialn.x0 / 30 * attr->x8),
#else
                    attr->x4 + fp->sv.ms.specialn.x0 / 30.0F * attr->x8,
#endif

                    gobj);
            }
            ndx++;
            hb += 0x138;
        }
    }
    if (fp->x894_currentAnimFrame == 9.0f) {
        Vec3 position;

        /// @todo Unused stack.
#ifdef MUST_MATCH
        u8 _[20];
#endif

        // JObj_GetWorldPos(r3=JObj,r4=UnkPointer,r5=StoreResult)
        //         Fighter_BonePersonalToCommon
        lb_8000B1CC(fp->x5E8_fighterBones[ftParts_8007500C(fp, 4)].x0_jobj, 0,
                    &position);
        // AestheticWindEffect(r3=sourcelocation,r4=duration,f1=radiusSize,f2=effectdegradation,f3=unk)
        lb_800119DC(&position, 120, 0.9f, 0.02f, 60 * M_PI / 180);
    }
    // FrameTimerCheck
    if (!ftAnim_IsFramesRemaining(gobj)) {
        // AS_029_Fall
        ft_800CC730(gobj);
    }
    return;
}

// 8013713C 00133D1C
void ftMars_8013713C(HSD_GObj* gobj) {}

// 80137140 00133D20
void ftMars_80137140(HSD_GObj* gobj) {}

// 80137144 00133D24
// https://decomp.me/scratch/ZIl0O
void ftMars_80137144(HSD_GObj* gobj)
{
    // Physics_Friction
    ft_80084F3C(gobj);
}

// 80137164 00133D44
// https://decomp.me/scratch/8OwY9
void ftMars_80137164(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

// 80137184 00133D64
// https://decomp.me/scratch/cIi5D
void ftMars_80137184(HSD_GObj* gobj)
{
    if (ft_80082708(gobj) == 0) {
        ftMars_801371FC(gobj);
    }
}

// 801371C0 00133DA0
// https://decomp.me/scratch/rpVpQ
void ftMars_801371C0(HSD_GObj* arg0)
{
    if (ft_80081D0C(arg0) != 0) {
        ftMars_801372A8(arg0);
    }
}

// 801371FC 00133DDC
// https://decomp.me/scratch/5lf3a
void ftMars_801371FC(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    s32 thing;

    if (fp->x2200_ftcmd_var0 == 0) {
        thing = 0x15B;
    } else {
        thing = 0x15C;
    }

    // Air_StoreBool_LoseGroundJump_NoECBfor10Frames
    ftCommon_8007D5D4(fp);
    // ActionStateChange
    Fighter_ChangeMotionState(gobj, thing, 0x0C4C508E, 0,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);

    if (fp->x2219_flag.bits.b0 == 1) {
        fp->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
        fp->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
    }
}

// 801372A8 00133E88
// AS_MarthNeutralBHitAir->Ground
// https://decomp.me/scratch/IV8RT
void ftMars_801372A8(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    s32 thing;

    if (fp->x2200_ftcmd_var0 == 0) {
        thing = 0x157;
    } else {
        thing = 0x158;
    }

    // Air_SetAsGrounded2
    ftCommon_8007D7FC(fp);
    // ActionStateChange
    Fighter_ChangeMotionState(gobj, thing, 0x0C4C508E, 0,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);

    if (fp->x2219_flag.bits.b0 == 1) {
        fp->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
        fp->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
    }
}

// 80137354 00133F34
// AS_RoyNeutralBSwing
// https://decomp.me/scratch/4CbiS
void ftMars_80137354(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    s32 thing;

    if (fp->x2200_ftcmd_var0 == 0) {
        thing = 0x157;
    } else {
        thing = 0x158;
    }

    Fighter_ChangeMotionState(gobj, thing, 0, 0, 1.0f, 1.0f, 0.0f);
    fp->cb.x21BC_callback_Accessory4 = &ftMars_801365A8;
}

// 801373B8 00133F98
// https://decomp.me/scratch/mXbi4
void ftMars_801373B8(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    s32 thing;

    if (fp->x2200_ftcmd_var0 == 0) {
        thing = 0x15B;
    } else {
        thing = 0x15C;
    }

    Fighter_ChangeMotionState(gobj, thing, 0, 0, 1.0f, 1.0f, 0.0f);
    fp->cb.x21BC_callback_Accessory4 = &ftMars_8013666C;
}
