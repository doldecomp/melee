#include "ftPe_AttackS4.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Wait.h"
#include "ftPeach/types.h"

#include <baselib/random.h>

void ftPe_AttackS4_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->allow_interrupt = false;
    fp->cmd_vars[0] = 0;
    {
        FtMotionId msid;
        do {
            int const min = ftPe_MS_AttackS4Club;
            int const max = ftPe_MS_AttackS4Racket;
            msid = HSD_Randi(max - min + 1) + min;
        } while (msid == fp->fv.pe.attacks4_motion_id);
        fp->fv.pe.attacks4_motion_id = msid;
        Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0, 1, 0, NULL);
    }
    ftAnim_8006EBA4(gobj);
}

void ftPe_AttackS4_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftPe_AttackS4_IASA(HSD_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->allow_interrupt) {
        ftCo_Wait_IASA(gobj);
    }
}

void ftPe_AttackS4_Phys(HSD_GObj* gobj)
{
    ft_80084FA8(gobj);
}

void ftPe_AttackS4_Coll(HSD_GObj* gobj)
{
    ft_80084104(gobj);
}
