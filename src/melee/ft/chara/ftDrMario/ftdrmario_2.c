#include "ftdrmario.h"

#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"
#include "ftMario/ftmario.h"
#include "it/code_8027CF30.h"
#include "lb/lbunknown_001.h"

void ftDrMario_80149954(HSD_GObj* gobj)
{
    Vec3 sp18;
    Fighter* fp;
    u32 tmp;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[12];
#endif

    fp = gobj->user_data;
    if (fp->x2200_ftcmd_var0 == 1 && fp->ev.mr.x2240 == 0U) {
        lb_8000B1CC(fp->x5E8_fighterBones->x0_jobj, 0, &sp18);
        tmp = ftMario_SpecialN_VitaminRandom(gobj);
        tmp = it_802C0850(gobj, &sp18, tmp, 0x31, fp->facing_dir);
        fp->ev.mr.x2240 = tmp;
        if (tmp != 0) {
            fp->cb.x21E4_callback_OnDeath2 = ftDrMario_80149540;
            fp->cb.x21DC_callback_OnTakeDamage = ftDrMario_80149540;
        }
    } else if (fp->x2200_ftcmd_var0 == 2) {
        ftDrMario_801497CC(gobj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (gobj != NULL) {
            fp = gobj->user_data;
            if (fp != NULL && fp->ev.mr.x2240 != 0) {
                it_802C0DBC(fp->ev.mr.x2240);
                fp->ev.mr.x2240 = 0;
            }
        }
        if (gobj != NULL) {
            fp = gobj->user_data;
            if (fp != NULL) {
                fp->cb.x21DC_callback_OnTakeDamage = 0;
                fp->cb.x21E4_callback_OnDeath2 = 0;
            }
        }
        ft_8008A2BC(gobj);
    }
}

void ftDrMario_80149A6C(HSD_GObj* gobj)
{
    ft_800DED30(gobj);
}

void ftDrMario_80149A8C(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDrMario_80149AAC(HSD_GObj* gobj)
{
    ft_80084280(gobj);
}
