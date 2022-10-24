#include <dolphin/types.h>
#include <dolphin/mtx/mtxtypes.h>

#include <functions.h>
#include <melee/pl/player.h>
#include <melee/gr/stage.h>
#include <math.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjuserdata.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/random.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/archive.h>
#include <common_structs.h>
#include <melee/ft/fighter.h>
#include <melee/it/item.h>



// 0x800765F0
// https://decomp.me/scratch/9hcKb
f32 func_800765F0(Fighter* fp, HSD_GObj* victim, f32 unk_floatvar) // Unk knockback related ?
{
    HSD_GObj* currentVictim;

    currentVictim = fp->x1A58_interactedFighter;
    if ((currentVictim != NULL) && (fp->x221B_flag.bits.b5 == 0) && (currentVictim != victim))
    {
        unk_floatvar *= p_ftCommonData->x128;
    }
    if (fp->x10_action_state_index == ASID_DAMAGEICE)
    {
        unk_floatvar *= p_ftCommonData->x714;
    }
    return unk_floatvar * fp->dmg.x182c_behavior;
}
