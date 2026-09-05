#include "ftdrmarioappeals.h"

#include "ftdrmario.h"

#include <melee/ft/forward.h>

#include <dolphin/mtx.h>
#include <sysdolphin/baselib/gobj.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/kinds/ftCommon/ftCo_AppealS.h>
#include <melee/ft/kinds/ftMario/ftmariospecialn.h>
#include <melee/ft/kinds/ftMario/types.h>
#include <melee/ft/types.h>
#include <melee/it/kinds/itdrmariopill.h>
#include <melee/lb/lb_00B0.h>
#include <Runtime/platform.h>

void ftDr_AppealS_Anim(HSD_GObj* gobj)
{
    Vec3 sp18;
    Fighter* fp;
    HSD_GObj* tmp;
    int vitamin_idx;

    u8 _[12];

    fp = gobj->user_data;
    if (fp->cmd_vars[0] == 1 && fp->u.mr.x2240 == NULL) {
        lb_8000B1CC(fp->parts->joint, 0, &sp18);
        vitamin_idx = ftMr_SpecialN_VitaminRandom(gobj);
        tmp = itDrMarioPill_Appeal_Spawn(
            gobj, &sp18, vitamin_idx, It_Kind_DrMario_Vitamin, fp->facing_dir);
        fp->u.mr.x2240 = tmp;
        if (tmp != 0) {
            fp->death2_cb = ftDr_Init_80149540;
            fp->take_dmg_cb = ftDr_Init_80149540;
        }
    } else if (fp->cmd_vars[0] == 2) {
        ftDr_Init_801497CC(gobj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (gobj != NULL) {
            fp = gobj->user_data;
            if (fp != NULL && fp->u.mr.x2240 != 0) {
                itDrMarioPill_802C0DBC(fp->u.mr.x2240);
                fp->u.mr.x2240 = 0;
            }
        }
        if (gobj != NULL) {
            fp = gobj->user_data;
            if (fp != NULL) {
                fp->take_dmg_cb = 0;
                fp->death2_cb = 0;
            }
        }
        ft_8008A2BC(gobj);
    }
}

void ftDr_AppealS_IASA(HSD_GObj* gobj)
{
    ftCo_AppealS_IASA(gobj);
}

void ftDr_AppealS_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDr_AppealS_Coll(HSD_GObj* gobj)
{
    ft_80084280(gobj);
}
