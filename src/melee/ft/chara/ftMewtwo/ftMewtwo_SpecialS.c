#include "ftmewtwo.h"

#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"

// 0x8014665C
// https://decomp.me/scratch/ktG8y // Set flags
void ftMewtwo_SpecialS_SetFlags(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_8007E2F4(fp, 0x1FF);
    func_8007E2FC(gobj);
    fp->x221E_flag.bits.b6 = 0;
    fp->x2222_flag.bits.b2 = 1;
}

static inline void ftMewtwo_SpecialS_SetGrab(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->x1A58_interactedFighter == NULL) {
        func_8007E2D0(fp, 0x40, ftMewtwo_SpecialS_SetFlags, NULL,
                      func_800BCF18);
    } else {
        func_8007E2F4(fp, 0x1FF);
    }
}

// 0x801466C4
// https://decomp.me/scratch/X6OTU // Mewtwo's grounded Confusion Action State
// handler
void ftMewtwo_SpecialS_StartAction(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    fp->x2210_ThrowFlags.flags = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->mv.mt.SpecialS.isConfusionReflect = false;

    Fighter_ActionStateChange_800693AC(gobj, AS_MEWTWO_SPECIALS, 0, NULL, 0.0f,
                                       1.0f, 0.0f);
    func_8006EBA4(gobj);

    ftMewtwo_SpecialS_SetGrab(gobj);
    fp->cb.x21BC_callback_Accessory4 = ftMewtwo_SpecialS_ReflectThink;
}

static inline void ftMewtwo_SpecialAirS_SetGrab(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->x1A58_interactedFighter == NULL) {
        func_8007E2D0(fp, 0x40, ftMewtwo_SpecialS_SetFlags, NULL,
                      func_800BD000);
    } else {
        func_8007E2F4(fp, 0x1FF);
    }
}

// 0x8014677C
// https://decomp.me/scratch/4DvVc // Mewtwo's aerial Confusion Action State
// handler
void ftMewtwo_SpecialAirS_StartAction(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    fp->x2210_ThrowFlags.flags = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->mv.mt.SpecialS.isConfusionReflect = false;

    if (fp->ev.mt.x223C_isConfusionBoost == false) {
        fp->x80_self_vel.y = mewtwoAttrs->x18_MEWTWO_CONFUSION_AIR_BOOST;
        fp->ev.mt.x223C_isConfusionBoost = true;
    }

    Fighter_ActionStateChange_800693AC(gobj, AS_MEWTWO_SPECIALAIRS, 0, NULL,
                                       0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);

    ftMewtwo_SpecialAirS_SetGrab(gobj);
    fp->cb.x21BC_callback_Accessory4 = ftMewtwo_SpecialS_ReflectThink;
}

static inline void ftMewtwo_SetGrabVictim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_GObj* victimGObj;

    if ((u32) fp->x2200_ftcmd_var0 != 0) {
        victimGObj = fp->x1A58_interactedFighter;
        if (victimGObj != NULL) {
            func_8007E2F4(fp, 0);
            func_800DE2A8(gobj, victimGObj);
            func_80090780(victimGObj);
            fp->x2200_ftcmd_var0 = 0;
        }
    }
}

// 0x80146858
// https://decomp.me/scratch/PYxCI // Mewtwo's grounded Confusion Animation
// callback
void ftMewtwo_SpecialS_Anim(HSD_GObj* gobj)
{
    ftMewtwo_SetGrabVictim(gobj);

    if (!ftAnim_IsFramesRemaining(gobj))
        func_8008A2BC(gobj);
}

// 0x801468EC
// https://decomp.me/scratch/rpTDv // Mewtwo's aerial Confusion Animation
// callback
void ftMewtwo_SpecialAirS_Anim(HSD_GObj* gobj)
{
    ftMewtwo_SetGrabVictim(gobj);

    if (!ftAnim_IsFramesRemaining(gobj))
        func_800CC730(gobj);
}

// 0x80146980 - Mewtwo's grounded Confusion IASA callback
void ftMewtwo_SpecialS_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x80146984 - Mewtwo's aerial Confusion IASA callback
void ftMewtwo_SpecialAirS_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x80146988
// https://decomp.me/scratch/o5TC6 // Mewtwo's grounded Confusion Physics
// callback
void ftMewtwo_SpecialS_Phys(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
    func_8007AEF8(gobj);
}

// 0x801469BC
// https://decomp.me/scratch/o5TC6 // Mewtwo's aerial Confusion Physics
// callback
void ftMewtwo_SpecialAirS_Phys(HSD_GObj* gobj)
{
    func_80084EEC(gobj);
    func_8007AEF8(gobj);
}

static inline void ftMewtwo_SpecialS_SetReflect(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.mt.SpecialS.isConfusionReflect != false) {
        fp->x2218_flag.bits.b3 = 1;
        fp->x2218_flag.bits.b4 = 1;
        fp->cb.x21C8_callback_OnReflectHit = ftMewtwo_SpecialS_OnReflect;
    }
}

// 0x801469F0
// https://decomp.me/scratch/W9wyx // Mewtwo's ground -> air Confusion Action
// State handler
void ftMewtwo_SpecialS_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_8007D5D4(fp);

    Fighter_ActionStateChange_800693AC(gobj, AS_MEWTWO_SPECIALAIRS,
                                       FTMEWTWO_SPECIALS_COLL_FLAG, NULL,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);

    func_8007D468(fp);

    ftMewtwo_SpecialAirS_SetGrab(gobj);

    fp->cb.x21BC_callback_Accessory4 = ftMewtwo_SpecialS_ReflectThink;

    ftMewtwo_SpecialS_SetReflect(gobj);
}

// 0x80146AD4
// https://decomp.me/scratch/gv2WK // Mewtwo's air -> ground Confusion Action
// State handler
void ftMewtwo_SpecialAirS_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_8007D7FC(fp);

    Fighter_ActionStateChange_800693AC(gobj, AS_MEWTWO_SPECIALS,
                                       FTMEWTWO_SPECIALS_COLL_FLAG, NULL,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);

    ftMewtwo_SpecialS_SetGrab(gobj);

    fp->cb.x21BC_callback_Accessory4 = ftMewtwo_SpecialS_ReflectThink;
    fp->ev.mt.x223C_isConfusionBoost = false;

    ftMewtwo_SpecialS_SetReflect(gobj);
}

// 0x80146BB8 - Mewtwo's grounded Confusion Collision callback
void ftMewtwo_SpecialS_Coll(HSD_GObj* gobj)
{
    func_8008403C(gobj, ftMewtwo_SpecialS_GroundToAir);
}

// 0x80146BE0 - Mewtwo's aerial Confusion Collision callback
void ftMewtwo_SpecialAirS_Coll(HSD_GObj* gobj)
{
    func_80082C74(gobj, ftMewtwo_SpecialAirS_AirToGround);
}

// 0x80146C08
// https://decomp.me/scratch/BDCzb // Confusion Reflect think function
void ftMewtwo_SpecialS_ReflectThink(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);
    s32 reflectFlag;

    reflectFlag = fp->x2204_ftcmd_var1;
    switch (reflectFlag) {
    case CONFUSION_REFLECT_ON:
        ftColl_CreateReflectHit(
            gobj, &mewtwoAttrs->x1C_MEWTWO_CONFUSION_REFLECTION,
            ftMewtwo_SpecialS_OnReflect); // Really? A callback that simply
                                          // returns instead of just NULL? //
        fp->x2218_flag.bits.b4 =
            1; // Here it is... the reason Confusion cannot change ownership.
        fp->mv.mt.SpecialS.isConfusionReflect = true;
        fp->x2204_ftcmd_var1 = CONFUSION_REFLECT_NONE;
        return;

    case CONFUSION_REFLECT_OFF:
        if (fp->mv.mt.SpecialS.isConfusionReflect != false) {
            fp->x2218_flag.bits.b3 = 0;
            fp->x2218_flag.bits.b4 = 0;
            fp->cb.x21C8_callback_OnReflectHit = NULL;
            fp->mv.mt.SpecialS.isConfusionReflect = false;
        }
        fp->x2204_ftcmd_var1 = CONFUSION_REFLECT_NONE;
        return;
    }
}

// 0x80146CC8 - Mewtwo's OnReflect callback
void ftMewtwo_SpecialS_OnReflect(HSD_GObj* gobj)
{
    return;
}
