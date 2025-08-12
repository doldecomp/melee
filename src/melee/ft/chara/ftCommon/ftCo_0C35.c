#include "ftCo_0C35.h"

#include "ftCo_Damage.h"

#include <placeholder.h>
#include <platform.h>

#include "ft/fighter.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"

#include <common_structs.h>
#include <math.h>
#include <dolphin/mtx.h>
#include <baselib/jobj.h>
#include <MSL/trigf.h>

static void inlineA0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->dmg.x18F4 = p_ftCommonData->x648;
    fp->dmg.x18F4 = fp->dmg.x18F4;
    if (fp->dmg.x18F4 > fp->dmg.x1954) {
        fp->dmg.x1954 = fp->dmg.x18F4;
    }
    fp->x2220_b4 = true;
    Fighter_UnkRecursiveFunc_8006D044(gobj);
}

void ftCo_800C3598(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    inlineA0(gobj);
    {
        float mag = fp->ground_or_air == GA_Air ? p_ftCommonData->x64C
                                                : p_ftCommonData->x650;
        float angle = ftCo_Damage_CalcAngle(fp, fp->dmg.kb_applied);
        float x = mag * cosf(angle);
        float y = mag * sinf(angle);
        if (fp->ground_or_air == GA_Air) {
            ftCo_Damage_CalcVel(fp, x * fp->dmg.facing_dir_1, y);
            fp->xF0_ground_kb_vel = 0;
        } else {
            fp->xF0_ground_kb_vel = x * fp->dmg.facing_dir_1;
            fp->xF0_ground_kb_vel = fp->xF0_ground_kb_vel;
            ftCo_Damage_CalcVel(
                fp, fp->coll_data.floor.normal.y * fp->xF0_ground_kb_vel,
                -fp->coll_data.floor.normal.x * fp->xF0_ground_kb_vel);
        }
        ftCommon_800804FC(fp);
    }
}

void ftCo_800C36DC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    inlineA0(gobj);
    fp->xF0_ground_kb_vel = p_ftCommonData->x654 * -fp->specialn_facing_dir;
    fp->xF0_ground_kb_vel = fp->xF0_ground_kb_vel;
    ftCo_Damage_CalcVel(fp,
                        fp->coll_data.floor.normal.y * fp->xF0_ground_kb_vel,
                        -fp->coll_data.floor.normal.x * fp->xF0_ground_kb_vel);
}

void ftCo_800C37A0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->dmg.x18F4 != 0) {
        Fighter_Part part = ftParts_GetBoneIndex(fp, FtPart_TransN);
        HSD_JObj* jobj = fp->parts[part].x4_jobj2;
        {
            float rot_y = M_PI *
                          (float) (p_ftCommonData->x648 - fp->dmg.x18F4) /
                          (float) p_ftCommonData->x648;
            fp->dmg.x18F4 -= 1;
            ftParts_80075AF0(fp, part, rot_y);
            HSD_JObjSetRotationY(jobj, rot_y);
            if (fp->dmg.x18F4 == 0) {
                fp->x2220_b4 = false;
                fp->facing_dir = -fp->facing_dir;
                ftParts_80075AF0(fp, FtPart_TopN, M_PI_2 * fp->facing_dir);
                ftParts_80075AF0(fp, part, 0);
                HSD_JObjSetRotationY(jobj, 0);
                if (fp->x21F8 != NULL) {
                    fp->x21F8(gobj);
                }
            }
        }
    }
}
