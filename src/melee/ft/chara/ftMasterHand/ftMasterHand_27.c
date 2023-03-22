#include "ftMasterHand_27.h"

#include "ftMasterHand_03.h"
#include "ftMasterHand_34.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftbosslib.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ftCrazyHand/ftcrazyhand.h"

// 80155074 151C54
// https://decomp.me/scratch/GL82m
void ftMasterHand_80155074(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->x2200_ftcmd_var0 != 0) {
        fp->x2200_ftcmd_var0 = 0;
        ftMasterHand_80155D6C(fp->x1A58_interactedFighter, 0x14A);
        if (fp->x1A58_interactedFighter != NULL) {
            HSD_GObj* victim = fp->x1A58_interactedFighter;
            ftCommon_8007E2F4(fp, 0);
            ft_800DE2A8(gobj, victim);
            ft_800DE7C0(victim, 0, 0);
        }
        fp->mv.mh.unk0.x20 = 0;
    }

    if (!ftAnim_IsFramesRemaining(gobj))
        ftMasterHand_80151018(gobj);
}

// 8015512C 151D0C
void ftMasterHand_8015512C(HSD_GObj* arg0)
{
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(arg0);
    }
}

// 80155170 151D50
void ftMasterHand_80155170(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

// 80155190 151D70
void ftMasterHand_80155190(HSD_GObj* gobj)
{
    return;
}

// 80155194 151D74
// https://decomp.me/scratch/3ppDy
void ftMasterHand_80155194(HSD_GObj* gobj)
{
    Fighter* fp;
    HSD_GObj* gobj_2;

    fp = gobj->user_data;
    gobj_2 = ftBossLib_8015C3E8(0x1C);
    if (ftBossLib_8015C31C() == 0) {
        ftCrazyHand_8015A2B0(gobj_2);
    }
    fp->x1A5C = gobj_2;
    Fighter_ChangeMotionState(gobj, 0x17E, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
}
