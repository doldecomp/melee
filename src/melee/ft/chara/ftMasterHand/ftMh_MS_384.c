#include "ftMh_MS_384.h"

#include "ftMh_CaptureMasterHand_0.h"
#include "ftMh_CaptureWaitMasterHand.h"
#include "ftMh_MS_389.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftbosslib.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"

void ftMh_MS_384_Anim(HSD_GObj* gobj)
{
    if (ftBossLib_8015C31C() || ftBossLib_8015C3A0() ||
        !ftAnim_IsFramesRemaining(gobj))
    {
        Fighter* fp = GET_FIGHTER(gobj);
        Fighter_UnkSetFlag_8006CFBC(gobj);
        fp->x1A5C = 0;
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_MS_384_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_MS_384_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_MS_384_Coll(HSD_GObj* gobj) {}

static void ftMh_MS_386_80155818(HSD_GObj* gobj);

void ftMh_MS_385_Anim(HSD_GObj* gobj)
{
    if (ftBossLib_8015C31C() || ftBossLib_8015C3A0() ||
        !ftAnim_IsFramesRemaining(gobj))
    {
        Fighter* fp = GET_FIGHTER(gobj);
        Fighter_UnkSetFlag_8006CFBC(gobj);
        fp->x1A5C = 0;
        ftMh_MS_386_80155818(gobj);
    }
}

void ftMh_MS_385_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_MS_385_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_MS_385_Coll(HSD_GObj* gobj) {}

/// @todo Fix weird forward declaration
extern const f32 neg1;

void ftMh_MS_386_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->x2200_ftcmd_var0 != 0) {
        fp->x2200_ftcmd_var0 = 0;
        ftMh_CaptureWaitMasterHand_80155D6C(fp->x1A58_interactedFighter,
                                            ftCo_MS_ThrownMasterHand);
        if (fp->x1A58_interactedFighter != 0) {
            HSD_GObj* victim = fp->x1A58_interactedFighter;
            Fighter* victim_fp = GET_FIGHTER(victim);
            ftCommon_8007E2F4(fp, 0);
            ft_800DE2A8(gobj, victim);
            victim_fp->dmg.x1844_direction *= neg1;
            ft_800DE7C0(victim, 0, 0);
        }
    }

    if (ftBossLib_8015C31C() || !ftAnim_IsFramesRemaining(gobj)) {
        Fighter* ft_3 = GET_FIGHTER(gobj);
        Fighter_UnkSetFlag_8006CFBC(gobj);
        ft_3->x1A5C = 0;
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_MS_386_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_MS_386_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_MS_386_Coll(HSD_GObj* gobj) {}

static void ftMh_MS_386_80155818(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_Unk387, 0, 0, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
}

void ftMh_MS_387_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_MS_387_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_MS_387_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_MS_387_Coll(HSD_GObj* gobj) {}

void ftMh_MS_388_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if ((--fp->mv.mh.unk0.x24 <= 0) && (fp->x2200_ftcmd_var0 != 0)) {
        ftMh_CaptureWaitMasterHand_80155D1C(fp->x1A58_interactedFighter);
        fp->x2200_ftcmd_var0 = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_MS_388_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_MS_388_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* attr = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18,
                       attr->x2C, attr->x28);
}

void ftMh_MS_388_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.mh.unk0.x18 == 0) {
        fp->x80_self_vel.x = fp->x80_self_vel.y = fp->x80_self_vel.z = 0;
    }
}

const f32 neg1 = -1;
