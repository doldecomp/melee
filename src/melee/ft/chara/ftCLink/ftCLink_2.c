#include "ftCLink_2.h"

#include "ftCLink_Init.h"

#include "ft/ft_81B.h"
#include "ft/ft_877.h"
#include "ft/ftanim.h"
#include "ft/ftparts.h"
#include "ftLink/ftlink.h"
#include "it/code_8027CF30.h"

void ftCLink_80149354(HSD_GObj* gobj)
{
    void* temp_r3;
    Fighter* fp;
    Fighter* ft2;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    fp = ft2 = gobj->user_data;

    if (fp->x2204_ftcmd_var1 == 1 && fp->fv.cl.x2244 == 0) {
        temp_r3 = func_802C8B28(gobj, &fp->cur_pos,
                                ftParts_8007500C(ft2, 0x1F), fp->facing_dir);
        fp->fv.cl.x2244 = (u32) temp_r3;
        if (temp_r3 != NULL) {
            fp->cb.x21E4_callback_OnDeath2 = ftLink_800EAF58;
            fp->cb.x21DC_callback_OnTakeDamage = ftLink_800EAF58;
        }
    } else if (ft2->x2204_ftcmd_var1 == 2) {
        ftCLink_80149268(gobj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        checkFighter2244(gobj);
        func_8008A2BC(gobj);
    }
}

void ftCLink_8014943C(HSD_GObj* gobj)
{
    func_800DED30(gobj);
}

void ftCLink_8014945C(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCLink_8014947C(HSD_GObj* gobj)
{
    ft_80084280(gobj);
}
