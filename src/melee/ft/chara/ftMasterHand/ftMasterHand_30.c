#include "ftMasterHand_30.h"

#include "ftMasterHand_03.h"
#include "ftMasterHand_31.h"
#include "ftMasterHand_34.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftbosslib.h"
#include "ft/ftcommon.h"

/// @todo Fix weird forward declaration
extern const f32 neg1;

// 8015550C 1520EC
// https://decomp.me/scratch/wrO5N
void ftMh_MS_384_Anim(HSD_GObj* gobj)
{
    if (ftBossLib_8015C31C() || ftBossLib_8015C3A0() ||
        !ftAnim_IsFramesRemaining(gobj))
    {
        Fighter* fp = gobj->user_data;
        Fighter_UnkSetFlag_8006CFBC(gobj);
        fp->x1A5C = 0;
        ftMh_MS_389_80151018(gobj);
    }
}

// 80155580 152160
void ftMh_MS_384_IASA(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

// 801555C4 1521A4
void ftMh_MS_384_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

// 801555E4 1521C4
void ftMh_MS_384_Coll(HSD_GObj* gobj)
{
    return;
}

// 801555E8 1521C8
// https://decomp.me/scratch/mvCUe
void ftMh_MS_385_Anim(HSD_GObj* gobj)
{
    if (ftBossLib_8015C31C() || ftBossLib_8015C3A0() ||
        !ftAnim_IsFramesRemaining(gobj))
    {
        Fighter* fp = gobj->user_data;
        Fighter_UnkSetFlag_8006CFBC(gobj);
        fp->x1A5C = 0;
        ftMh_MS_386_80155818(gobj);
    }
}

// 8015565C 15223C
void ftMh_MS_385_IASA(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

// 801556A0 152280
void ftMh_MS_385_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

// 801556C0 1522A0
void ftMh_MS_385_Coll(HSD_GObj* gobj)
{
    return;
}

// 801556C4 1522A4
// https://decomp.me/scratch/Uuy48
void ftMh_MS_386_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->x2200_ftcmd_var0 != 0) {
        fp->x2200_ftcmd_var0 = 0;
        ftMh_CaptureWaitMasterHand_80155D6C(fp->x1A58_interactedFighter, 0x14A);
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

// 801557B0 152390
void ftMh_MS_386_IASA(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

// 801557F4 1523D4
void ftMh_MS_386_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

// 80155814 1523F4
void ftMh_MS_386_Coll(HSD_GObj* gobj)
{
    return;
}

// 80155818 1523F8
// https://decomp.me/scratch/qSDro
void ftMh_MS_386_80155818(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 0x183, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
}

// 80155864 152444
// https://decomp.me/scratch/ln57J
void ftMh_MS_387_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_389_80151018(gobj);
    }
}

// 801558A0 152480
void ftMh_MS_387_IASA(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

// 801558E4 1524C4
void ftMh_MS_387_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

// 80155904 1524E4
void ftMh_MS_387_Coll(HSD_GObj* gobj)
{
    return;
}

// 80155908 1524E8
// https://decomp.me/scratch/jo0OK
void ftMh_MS_388_Anim(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if ((--fp->sv.mh.unk0.x24 <= 0.0f) && (fp->x2200_ftcmd_var0 != 0)) {
        ftMh_CaptureWaitMasterHand_80155D1C(fp->x1A58_interactedFighter);
        fp->x2200_ftcmd_var0 = 0;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_389_80151018(gobj);
    }
}

// 80155990 152570
void ftMh_MS_388_IASA(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

// 801559D4 1525B4
// https://decomp.me/scratch/cRlBe
void ftMh_MS_388_Phys(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftMasterHand_SpecialAttrs* attr = fp->x10C_ftData->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->sv.mh.unk0.xC, &fp->sv.mh.unk0.x18,
                       attr->x2C, attr->x28);
}

// 80155A34 152614
// https://decomp.me/scratch/OedGK
void ftMh_MS_388_Coll(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    if (fp->sv.mh.unk0.x18 == 0.0f) {
        fp->x80_self_vel.z = 0.0f;
        fp->x80_self_vel.y = 0.0f;
        fp->x80_self_vel.x = 0.0f;
    }
}

const f32 neg1 = -1.0f;
