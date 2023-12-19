#include <platform.h>
#include "ft/forward.h"

#include "ftCo_09C4.h"

#include "ftCo_Pass.h"
#include "ftCo_Shouldered.h"

#include "ft/ftanim.h"
#include "ft/types.h"

/* 09C540 */ static void ftCo_8009C540(ftCo_GObj* gobj);

bool ftCo_8009C4F8(ftCo_GObj* gobj)
{
    if (ftCo_80099F1C(gobj)) {
        ftCo_8009C540(gobj);
        return true;
    }
    return false;
}

void ftCo_8009C540(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16] = { 0 };
#endif
    Fighter* fp = gobj->user_data;
    ftCo_8009A184(gobj, fp->x2CC->x4_motion_state + 6, Ft_MF_None, 0);
    ftAnim_SetAnimRate(gobj, 0);
    ftCo_8009C5A4(fp->victim_gobj, ftCo_MS_ShoulderedWait);
}
