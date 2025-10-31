#include "ftCo_SpecialAir.h"

#include "math.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/ftcommon.h"
#include "ft/ftdata.h"
#include "ft/types.h"

#include <baselib/forward.h>

#include <common_structs.h>
#include <dolphin/mtx.h>

bool ftCo_SpecialAir_CheckInput(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->input.x668 & HSD_PAD_B) {
        if (fp->input.lstick.y >= p_ftCommonData->x21C) {
            if (ftData_SpecialAirHi[fp->kind] == NULL) {
                return false;
            }
            ftData_SpecialAirHi[fp->kind](gobj);
            fp->x2227_b5 = true;
            return true;
        }
        if (fp->input.lstick.y <= -p_ftCommonData->x21C) {
            if (ftData_SpecialAirLw[fp->kind] == NULL) {
                return false;
            }
            ftData_SpecialAirLw[fp->kind](gobj);
            fp->x2227_b5 = true;
            return true;
        }
        if (ABS(fp->input.lstick.x) >= p_ftCommonData->x218) {
            if (ftData_SpecialAirS[fp->kind] == NULL) {
                return false;
            }
            if (fp->input.lstick.x * fp->facing_dir < -p_ftCommonData->x220) {
                ftCommon_UpdateFacing(fp);
            }
            ftData_SpecialAirS[fp->kind](gobj);
            fp->x2227_b5 = true;
            return true;
        }
        if (ftData_SpecialAirN[fp->kind] == NULL) {
            return false;
        }
        if (fp->x676_x < p_ftCommonData->x224 &&
            ((fp->facing_dir == -1 && fp->x2228_b7 == 1) ||
             (fp->facing_dir == +1 && fp->x2228_b7 == 0)))
        {
            fp->facing_dir = -fp->facing_dir;
        }
        ftData_SpecialAirN[fp->kind](gobj);
        fp->x2227_b5 = true;
        return true;
    }
    return false;
}
