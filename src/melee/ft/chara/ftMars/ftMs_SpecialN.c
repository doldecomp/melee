#include "ft/forward.h"

#include "ftMs_SpecialN.h"

#include "ef/eflib.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ftMars/ftMs_Init.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include <dolphin/mtx/types.h>

void ftMs_SpecialN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    MarsAttributes* attrs = fp->dat_attrs;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    fp->cb.x21EC_callback = &ftMs_SpecialN_80136730;

    fp->gr_vel /= attrs->xC;
    Fighter_ChangeMotionState(gobj, 0x155, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
}

void ftMs_SpecialAirN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    MarsAttributes* attrs = fp->dat_attrs;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    fp->cb.x21EC_callback = &ftMs_SpecialN_80136730;

    fp->self_vel.x /= attrs->xC;

    if (fp->self_vel.y <= 0.0f) {
        fp->self_vel.y = 0.0f;
    }

    Fighter_ChangeMotionState(gobj, 0x159, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
}

// 80136844 00133424
// https://decomp.me/scratch/Go6FC
void ftMs_SpecialNStart_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMs_SpecialN_80136E74(gobj);

        if (((Fighter*) gobj->user_data)->kind == FTKIND_MARS) {
            ft_800BFFD0(gobj->user_data, 0x63, 0);
        } else {
            ft_800BFFD0(gobj->user_data, 0x64, 0);
        }
    }
}

// 801368AC 0013348C
// https://decomp.me/scratch/XBFKN
void ftMs_SpecialAirNStart_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMs_SpecialN_80136EAC(gobj);

        if (((Fighter*) gobj->user_data)->kind == FTKIND_MARS) {
            ft_800BFFD0(gobj->user_data, 0x63, 0);
        } else {
            ft_800BFFD0(gobj->user_data, 0x64, 0);
        }
    }
}

// 80136914 001334F4
void ftMs_SpecialNStart_IASA(HSD_GObj* gobj)
{
    return;
}

// 80136918 001334F8
void ftMs_SpecialAirNStart_IASA(HSD_GObj* gobj)
{
    return;
}

void ftMs_SpecialNStart_Phys(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    MarsAttributes* attr = fp->dat_attrs;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    ftCommon_8007C930(fp, attr->x10);
    ftCommon_8007CB74(gobj);
}

void ftMs_SpecialAirNStart_Phys(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    MarsAttributes* attr = fp->dat_attrs;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    ftCommon_8007D4B8(fp);
    ftCommon_8007CE94(fp, attr->x10);
}

// 801369A4 00133584
// https://decomp.me/scratch/bR5HF
void ftMs_SpecialNStart_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ftMs_SpecialN_80136A1C(gobj);
    }
}

// 801369E0 001335C0
// https://decomp.me/scratch/cCPAH
void ftMs_SpecialAirNStart_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ftMs_SpecialN_80136A7C(gobj);
    }
}

// 80136A1C 001335FC
// https://decomp.me/scratch/9GhD1
void ftMs_SpecialN_80136A1C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCommon_8007D5D4(fp);

    Fighter_ChangeMotionState(gobj, 0x159, 0x0C4C5084, 0, fp->cur_anim_frame,
                              1.0f, 0.0f);
}

// 80136A7C 0013365C
// https://decomp.me/scratch/GU6fn
void ftMs_SpecialN_80136A7C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, 0x155, 0x0C4C5084, 0, fp->cur_anim_frame,
                              1.0f, 0.0f);
}

void ftMs_SpecialNLoop_Anim(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    s32* specialAttrs = fp->dat_attrs;
    Vec3 sp28;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[28];
#endif

    if (fp->mv.ms.specialn.x0 % 30 == 0) {
        lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_HipN)].x0_jobj, 0,
                    &sp28);
        lb_800119DC(&sp28, 10, 0.5, 0.05, 60 * DEG_TO_RAD);
    }

    fp->mv.ms.specialn.x0++;

    if ((s32) fp->mv.ms.specialn.x0 > *specialAttrs * 30) {
        fp->cmd_vars[0] = 1;
        ftMs_SpecialN_80137354(gobj);
    }
}

void ftMs_SpecialAirNLoop_Anim(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    MarsAttributes* attrs = fp->dat_attrs;
    Vec3 sp28;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[28];
#endif

    if ((s32) fp->mv.ms.specialn.x0 % 30 == 0) {
        lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_HipN)].x0_jobj, 0,
                    &sp28);
        lb_800119DC(&sp28, 10, 0.5, 0.05, 60 * DEG_TO_RAD);
    }
    fp->mv.ms.specialn.x0++;
    if ((s32) fp->mv.ms.specialn.x0 > attrs->x0 * 30) {
        fp->cmd_vars[0] = 1;
        ftMs_SpecialN_801373B8(gobj);
    }
}

// 80136C8C 0013386C
// Interrupt_MarthNeutralBCharge
// https://decomp.me/scratch/zR8Hv
void ftMs_SpecialNLoop_IASA(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if ((fp->input.x65C_heldInputs & 0x200) == 0) {
        fp->cmd_vars[0] = 0;
        ftMs_SpecialN_80137354(gobj);
    }
}

// 80136CC4 001338A4
// https://decomp.me/scratch/ykJFN
void ftMs_SpecialAirNLoop_IASA(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if ((fp->input.x65C_heldInputs & 0x200) == 0) {
        fp->cmd_vars[0] = 0;
        ftMs_SpecialN_801373B8(gobj);
    }
}

// 80136CFC 001338DC
// https://decomp.me/scratch/Q3NsK
void ftMs_SpecialNLoop_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

// 80136D1C 001338FC
// https://decomp.me/scratch/LVDnG
void ftMs_SpecialAirNLoop_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

// 80136D3C 0013391C
// https://decomp.me/scratch/XmmUv
void ftMs_SpecialNLoop_Coll(HSD_GObj* gobj)
{
    if (ft_80082708(gobj) == 0) {
        ftMs_SpecialN_80136DB4(gobj);
    }
}

// 80136D78 00133958
// https://decomp.me/scratch/tjkA9
void ftMs_SpecialAirNLoop_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj) != 0) {
        ftMs_SpecialN_80136E14(gobj);
    }
}

// 80136DB4 00133994
// https://decomp.me/scratch/eJxjC
void ftMs_SpecialN_80136DB4(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    ftCommon_8007D5D4(gobj->user_data);
    Fighter_ChangeMotionState(gobj, 0x15A, 0x0C4C5A86, 0, fp->cur_anim_frame,
                              1.0f, 0.0f);
}

// 80136E14 001339F4
// https://decomp.me/scratch/mzQdp
void ftMs_SpecialN_80136E14(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x156, 0x0C4C5A86, 0, fp->cur_anim_frame,
                              1.0f, 0.0f);
}

// 80136E74 00133A54
// https://decomp.me/scratch/M7HBN
void ftMs_SpecialN_80136E74(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 0x156, 0x1200, 0, 0.0f, 1.0f, 0.0f);
}

// 80136EAC 00133A8C
// https://decomp.me/scratch/RkI7l
void ftMs_SpecialN_80136EAC(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 0x15A, 0x1200, 0, 0.0f, 1.0f, 0.0f);
}

// 80136EE4 00133AC4
// https://decomp.me/scratch/e4mhD
void ftMs_SpecialNEnd_Anim(HSD_GObj* gobj)
{
    s32 ndx;
    MarsAttributes* attr;
    Fighter* fp;

    fp = gobj->user_data;
    attr = fp->dat_attrs;
    if (fp->cmd_vars[0] == 0) {
        s32 hb = (s32) fp;
        ndx = 0;
        while (ndx < 4) {
            if (*(s32*) (hb + 0x914) == 1) {
                ftColl_8007ABD0(
                    (HitCapsule*) (hb + 0x914),

#if MUST_MATCH
                    (f32) (attr->x4 + fp->mv.ms.specialn.x0 / 30 * attr->x8),
#else
                    attr->x4 + fp->mv.ms.specialn.x0 / 30.0F * attr->x8,
#endif

                    gobj);
            }
            ndx++;
            hb += 0x138;
        }
    }
    if (fp->cur_anim_frame == 9.0f) {
        Vec3 position;

        /// @todo Unused stack.
#ifdef MUST_MATCH
        u8 _[20];
#endif

        // JObj_GetWorldPos(r3=JObj,r4=UnkPointer,r5=StoreResult)
        //         Fighter_BonePersonalToCommon
        lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_HipN)].x0_jobj, 0,
                    &position);
        // AestheticWindEffect(r3=sourcelocation,r4=duration,f1=radiusSize,f2=effectdegradation,f3=unk)
        lb_800119DC(&position, 120, 0.9, 0.02, 60 * DEG_TO_RAD);
    }
    // FrameTimerCheck
    if (!ftAnim_IsFramesRemaining(gobj)) {
        // MS_014_Wait_PlayerCheck
        ft_8008A2BC(gobj);
    }
    return;
}

// 80137010 00133BF0
// https://decomp.me/scratch/pIor0
void ftMs_SpecialAirNEnd_Anim(HSD_GObj* gobj)
{
    s32 ndx;
    MarsAttributes* attr;
    Fighter* fp;

    fp = gobj->user_data;
    attr = fp->dat_attrs;
    if (fp->cmd_vars[0] == 0) {
        // register swap:
        // s32 ndx;
        // for (ndx = 0; ndx < 4; ndx++) {
        //     if (fp->x914[ndx].x0 == 1) {
        //         // Hitbox_ApplyDamageStalingAndMore
        //         ftColl_8007ABD0(&fp->x914[ndx], (f32) (attr->x4 +
        //         (s32)fp->mv.ms.specialn.x0 / 30 * attr->x8), gobj);
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
                    (f32) (attr->x4 + fp->mv.ms.specialn.x0 / 30 * attr->x8),
#else
                    attr->x4 + fp->mv.ms.specialn.x0 / 30.0F * attr->x8,
#endif

                    gobj);
            }
            ndx++;
            hb += 0x138;
        }
    }
    if (fp->cur_anim_frame == 9.0f) {
        Vec3 pos;

        /// @todo Unused stack.
#ifdef MUST_MATCH
        u8 _[20];
#endif

        // JObj_GetWorldPos(r3=JObj,r4=UnkPointer,r5=StoreResult)
        //         Fighter_BonePersonalToCommon
        lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_HipN)].x0_jobj, 0,
                    &pos);
        // AestheticWindEffect(r3=sourcelocation,r4=duration,f1=radiusSize,f2=effectdegradation,f3=unk)
        lb_800119DC(&pos, 120, 0.9, 0.02, 60 * DEG_TO_RAD);
    }
    // FrameTimerCheck
    if (!ftAnim_IsFramesRemaining(gobj)) {
        // MS_029_Fall
        ft_800CC730(gobj);
    }
    return;
}

// 8013713C 00133D1C
void ftMs_SpecialNEnd_IASA(HSD_GObj* gobj) {}

// 80137140 00133D20
void ftMs_SpecialAirNEnd_IASA(HSD_GObj* gobj) {}

// 80137144 00133D24
// https://decomp.me/scratch/ZIl0O
void ftMs_SpecialNEnd_Phys(HSD_GObj* gobj)
{
    // Physics_Friction
    ft_80084F3C(gobj);
}

// 80137164 00133D44
// https://decomp.me/scratch/8OwY9
void ftMs_SpecialAirNEnd_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

// 80137184 00133D64
// https://decomp.me/scratch/cIi5D
void ftMs_SpecialNEnd_Coll(HSD_GObj* gobj)
{
    if (ft_80082708(gobj) == 0) {
        ftMs_SpecialN_801371FC(gobj);
    }
}

// 801371C0 00133DA0
// https://decomp.me/scratch/rpVpQ
void ftMs_SpecialAirNEnd_Coll(HSD_GObj* arg0)
{
    if (ft_80081D0C(arg0) != 0) {
        ftMs_SpecialN_801372A8(arg0);
    }
}

// 801371FC 00133DDC
// https://decomp.me/scratch/5lf3a
void ftMs_SpecialN_801371FC(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    s32 thing;

    if (fp->cmd_vars[0] == 0) {
        thing = 0x15B;
    } else {
        thing = 0x15C;
    }

    // Air_StoreBool_LoseGroundJump_NoECBfor10Frames
    ftCommon_8007D5D4(fp);
    // MotionStateChange
    Fighter_ChangeMotionState(gobj, thing, 0x0C4C508E, 0, fp->cur_anim_frame,
                              1.0f, 0.0f);

    if (fp->x2219_b0 == 1) {
        fp->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
        fp->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
    }
}

// 801372A8 00133E88
// MS_MarthNeutralBHitAir->Ground
// https://decomp.me/scratch/IV8RT
void ftMs_SpecialN_801372A8(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    s32 thing;

    if (fp->cmd_vars[0] == 0) {
        thing = 0x157;
    } else {
        thing = 0x158;
    }

    // Air_SetAsGrounded2
    ftCommon_8007D7FC(fp);
    // MotionStateChange
    Fighter_ChangeMotionState(gobj, thing, 0x0C4C508E, 0, fp->cur_anim_frame,
                              1.0f, 0.0f);

    if (fp->x2219_b0 == 1) {
        fp->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
        fp->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
    }
}

// 80137354 00133F34
// MS_RoyNeutralBSwing
// https://decomp.me/scratch/4CbiS
void ftMs_SpecialN_80137354(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    s32 thing;

    if (fp->cmd_vars[0] == 0) {
        thing = 0x157;
    } else {
        thing = 0x158;
    }

    Fighter_ChangeMotionState(gobj, thing, 0, 0, 1.0f, 1.0f, 0.0f);
    fp->cb.x21BC_callback_Accessory4 = &ftMs_SpecialN_801365A8;
}

// 801373B8 00133F98
// https://decomp.me/scratch/mXbi4
void ftMs_SpecialN_801373B8(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    s32 thing;

    if (fp->cmd_vars[0] == 0) {
        thing = 0x15B;
    } else {
        thing = 0x15C;
    }

    Fighter_ChangeMotionState(gobj, thing, 0, 0, 1.0f, 1.0f, 0.0f);
    fp->cb.x21BC_callback_Accessory4 = &ftMs_SpecialN_8013666C;
}
