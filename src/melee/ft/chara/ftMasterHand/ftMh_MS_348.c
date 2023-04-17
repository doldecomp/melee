#include "ftMh_MS_348.h"

#include "ftMh_MS_389.h"

#include "ft/ft_081B.h"
#include "ft/ftbosslib.h"

// 80151B14 14E6F4
// https://decomp.me/scratch/hxBrR
void ftMh_MS_348_Anim(HSD_GObj* arg0)
{
    if (!ftAnim_IsFramesRemaining(arg0)) {
        ftMh_MS_389_80151018(arg0);
    }
}

// 80151B50 14E730
// https://decomp.me/scratch/zvSIb
void ftMh_MS_348_Phys(HSD_GObj* arg0)
{
    ft_80085134(arg0);
}

// 80151B70 14E750
// https://decomp.me/scratch/50coe
void ftMh_MS_348_IASA(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_MS_348_Coll(HSD_GObj* arg0) {}

// 80151BB8 14E798
// https://decomp.me/scratch/vjf0b
void ftMh_MS_348_80151BB8(HSD_GObj* arg0)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ChangeMotionState(arg0, 0x15D, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(arg0);
}
