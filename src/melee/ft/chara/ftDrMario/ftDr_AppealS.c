#include "ftDr_AppealS.h"

#include "ftDr_Init.h"

#include <platform.h>

#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/types.h"
#include "ftCommon/ftCo_AppealS.h"
#include "ftMario/ftMr_SpecialN.h"
#include "ftMario/types.h"
#include "it/items/it_27CF.h"
#include "lb/lb_00B0.h"

#include <dolphin/mtx.h>
#include <baselib/gobj.h>

void ftDr_AppealS_Anim(HSD_GObj* gobj)
{
    Vec3 sp18;
    Fighter* fp;
    u32 tmp;

    u8 _[12];

    fp = gobj->user_data;
    if (fp->cmd_vars[0] == 1 && fp->fv.mr.x2240 == 0U) {
        lb_8000B1CC(fp->parts->joint, 0, &sp18);
        tmp = ftMr_SpecialN_VitaminRandom(gobj);
        tmp = it_802C0850(gobj, &sp18, tmp, 0x31, fp->facing_dir);
        fp->fv.mr.x2240 = tmp;
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
            if (fp != NULL && fp->fv.mr.x2240 != 0) {
                it_802C0DBC(fp->fv.mr.x2240);
                fp->fv.mr.x2240 = 0;
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
