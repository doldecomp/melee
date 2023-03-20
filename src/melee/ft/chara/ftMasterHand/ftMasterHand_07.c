#include "ftMasterHand_07.h"

#include "ftMasterHand_03.h"

#include "ft/code_80081B38.h"
#include "ft/ftbosslib.h"

// 80151B14 14E6F4
// https://decomp.me/scratch/hxBrR
void lbl_80151B14(HSD_GObj* arg0)
{
    if (!ftAnim_IsFramesRemaining(arg0))
        func_80151018(arg0);
}

// 80151B50 14E730
// https://decomp.me/scratch/zvSIb
void lbl_80151B50(HSD_GObj* arg0)
{
    func_80085134(arg0);
}

// 80151B70 14E750
// https://decomp.me/scratch/50coe
void lbl_80151B70(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        func_8015BD20(gobj);
}

void lbl_80151BB4(HSD_GObj* arg0) {}

// 80151BB8 14E798
// https://decomp.me/scratch/vjf0b
void lbl_80151BB8(HSD_GObj* arg0)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ActionStateChange_800693AC(arg0, 0x15D, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(arg0);
}
