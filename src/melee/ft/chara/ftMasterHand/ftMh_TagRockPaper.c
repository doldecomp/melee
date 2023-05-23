#include "ftMh_TagRockPaper.h"

#include "ftMh_TagCancel.h"
#include "ftMh_ThrownMasterHand.h"
#include "ftMh_Wait1_2.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftbosslib.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"

void ftMh_TagRockPaper_Anim(HSD_GObj* gobj)
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

void ftMh_TagRockPaper_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_TagRockPaper_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_TagRockPaper_Coll(HSD_GObj* gobj) {}

static void ftMh_MS_386_80155818(HSD_GObj* gobj);

void ftMh_TagGrab_Anim(HSD_GObj* gobj)
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

void ftMh_TagGrab_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_TagGrab_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_TagGrab_Coll(HSD_GObj* gobj) {}

/// @todo Fix weird forward declaration
extern const f32 neg1;

void ftMh_TagSqueeze_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->cmd_vars[0] != 0) {
        fp->cmd_vars[0] = 0;
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

void ftMh_TagSqueeze_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_TagSqueeze_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_TagSqueeze_Coll(HSD_GObj* gobj) {}

static void ftMh_MS_386_80155818(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_TagFail, 0, 0, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
}

void ftMh_TagFail_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_TagFail_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_TagFail_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_TagFail_Coll(HSD_GObj* gobj) {}

void ftMh_TagCancel_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if ((--fp->mv.mh.unk0.x24 <= 0) && (fp->cmd_vars[0] != 0)) {
        ftMh_CaptureWaitMasterHand_80155D1C(fp->x1A58_interactedFighter);
        fp->cmd_vars[0] = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_TagCancel_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_TagCancel_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18, da->x2C,
                       da->x28);
}

void ftMh_TagCancel_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.mh.unk0.x18 == 0) {
        fp->self_vel.x = fp->self_vel.y = fp->self_vel.z = 0;
    }
}

const f32 neg1 = -1;
