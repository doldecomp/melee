#include <platform.h>
#include <dolphin/mtx/forward.h>

#include "ft/ft_081B.h"

#include "ft/ftcommon.h"
#include "ft/types.h"

#include <placeholder.h>
#include <baselib/gobj.h>

bool ft_8008239C(HSD_GObj* gobj, s32 facing_direction,
                 float* height_attributes)
{
    NOT_IMPLEMENTED;
}

bool ft_800824A0(HSD_GObj* gobj, ftCollisionBox* arg1)
{
    NOT_IMPLEMENTED;
}

void ft_80082578(void)
{
    NOT_IMPLEMENTED;
}

void ft_80082638(ftCo_GObj* gobj, ftCollisionBox* arg1)
{
    NOT_IMPLEMENTED;
}

GroundOrAir ft_80082708(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

bool ft_800827A0(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ft_80082838(void)
{
    NOT_IMPLEMENTED;
}

bool ft_80082888(HSD_GObj* gobj, ftCollisionBox* arg1)
{
    NOT_IMPLEMENTED;
}

void ft_80082978(void)
{
    NOT_IMPLEMENTED;
}

bool ft_80082A68(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ft_80082B1C(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftCo_AirCatchHit_Coll(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ft_80082C74(HSD_GObj* gobj, HSD_GObjEvent cb)
{
    NOT_IMPLEMENTED;
}

void ft_80082D40(Fighter_GObj* gobj, float arg1)
{
    NOT_IMPLEMENTED;
}

HSD_GObj* ft_80082E3C(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ft_80082F28(ftCo_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ft_80083090(ftCo_GObj* gobj, bool (*arg1)(HSD_GObj*, enum_t),
                 HSD_GObjEvent arg2)
{
    NOT_IMPLEMENTED;
}

void ft_800831CC(HSD_GObj* gobj, bool (*arg1)(HSD_GObj*, enum_t),
                 HSD_GObjEvent arg2)
{
    NOT_IMPLEMENTED;
}

void ft_80083318(Fighter_GObj* gobj, bool (*arg1)(Fighter_GObj* gobj, enum_t),
                 HSD_GObjEvent arg2)
{
    NOT_IMPLEMENTED;
}

void ft_80083464(Fighter_GObj* gobj, bool (*arg1)(Fighter_GObj* gobj, enum_t),
                 HSD_GObjEvent arg2)
{
    NOT_IMPLEMENTED;
}

void ft_800835B0(Fighter_GObj* gobj, bool (*arg1)(Fighter_GObj*, enum_t),
                 HSD_GObjEvent arg2)
{
    NOT_IMPLEMENTED;
}

void ft_8008370C(ftCo_GObj* gobj, HSD_GObjEvent cb)
{
    NOT_IMPLEMENTED;
}

void ft_80083844(void)
{
    NOT_IMPLEMENTED;
}

void ft_80083910(void)
{
    NOT_IMPLEMENTED;
}

void ft_80083A48(void)
{
    NOT_IMPLEMENTED;
}

void ft_80083B68(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ft_80083C00(void)
{
    NOT_IMPLEMENTED;
}

void ft_80083CE4(void)
{
    NOT_IMPLEMENTED;
}

void ft_80083DCC(void)
{
    NOT_IMPLEMENTED;
}

void ft_80083E64(Fighter_GObj* gobj, ftCollisionBox* ecb, HSD_GObjEvent cb)
{
    NOT_IMPLEMENTED;
}

void ft_80083F88(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ft_8008403C(HSD_GObj* gobj, HSD_GObjEvent arg1)
{
    NOT_IMPLEMENTED;
}

void ft_80084104(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ft_800841B8(ftCo_GObj* gobj, HSD_GObjEvent cb)
{
    NOT_IMPLEMENTED;
}

void ft_80084280(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ft_800843FC(ftCo_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ft_800844EC(void)
{
    NOT_IMPLEMENTED;
}

void ft_800845B4(ftCo_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ft_800846B0(void)
{
    NOT_IMPLEMENTED;
}

void ft_800847D0(ftCo_GObj* gobj, ftCollisionBox* arg1)
{
    NOT_IMPLEMENTED;
}

void ft_800848DC(ftCo_GObj* goibj, HSD_GObjEvent cb)
{
    NOT_IMPLEMENTED;
}

void ft_800849EC(Fighter* arg0, Fighter* arg1)
{
    NOT_IMPLEMENTED;
}

bool ft_80084A18(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

float ft_GetGroundFrictionMultiplier(Fighter* fp)
{
    NOT_IMPLEMENTED;
}

void ft_80084A80(void)
{
    NOT_IMPLEMENTED;
}

bool ft_80084BFC(ftCo_GObj* gobj, int* arg1, int* arg2)
{
    NOT_IMPLEMENTED;
}

bool ft_80084C38(HSD_GObj* gobj, int* arg1, int* arg2, int* arg3, char* arg4)
{
    NOT_IMPLEMENTED;
}

bool ft_80084C74(Fighter_GObj* gobj, int* arg1, int* arg2, int* arg3)
{
    NOT_IMPLEMENTED;
}

void ft_80084CB0(Fighter* fp, ftCollisionBox* arg1)
{
    NOT_IMPLEMENTED;
}

bool ft_80084CE4(Fighter* attacker, Fighter* victim)
{
    NOT_IMPLEMENTED;
}

void ft_80084DB0(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ft_80084E1C(void)
{
    NOT_IMPLEMENTED;
}

void ft_80084EEC(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ft_80084F3C(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ft_80084FA8(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ft_80085004(ftCo_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ft_80085030(HSD_GObj* gobj, float gr_friction, float facing_dir)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->x594_b0) {
        fp->xE4_ground_accel_1 =
            fp->x6A4_transNOffset.z * facing_dir - fp->gr_vel;
    } else {
        ftCommon_8007C930(fp, gr_friction);
    }
    ftCommon_8007CB74(gobj);
}

void ft_800850E0(void);

void ft_80085088(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ft_800850B4(void)
{
    NOT_IMPLEMENTED;
}

void ft_800850E0(void)
{
    NOT_IMPLEMENTED;
}

void ft_80085134(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ft_80085154(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ft_800851C0(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ft_800851D0(void)
{
    NOT_IMPLEMENTED;
}

void ft_80085204(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}
