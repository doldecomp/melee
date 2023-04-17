#include "ftCl_Appeal.h"

#include "ftCl_Init.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftanim.h"
#include "ft/ftparts.h"
#include "ftLink/ftLk_Init.h"
#include "it/it_27CF.h"

void ftCl_Appeal_Anim(HSD_GObj* gobj)
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
        temp_r3 = it_802C8B28(gobj, &fp->cur_pos, ftParts_8007500C(ft2, 0x1F),
                              fp->facing_dir);
        fp->fv.cl.x2244 = (u32) temp_r3;
        if (temp_r3 != NULL) {
            fp->cb.x21E4_callback_OnDeath2 = ftLk_800EAF58;
            fp->cb.x21DC_callback_OnTakeDamage = ftLk_800EAF58;
        }
    } else if (ft2->x2204_ftcmd_var1 == 2) {
        ftCl_Init_80149268(gobj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        checkFighter2244(gobj);
        ft_8008A2BC(gobj);
    }
}

void ftCl_Appeal_IASA(HSD_GObj* gobj)
{
    ftCo_Appeal_IASA(gobj);
}

void ftCl_Appeal_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCl_Appeal_Coll(HSD_GObj* gobj)
{
    ft_80084280(gobj);
}
