#ifndef MELEE_FT_CHARA_FTPURIN_INLINES_H
#define MELEE_FT_CHARA_FTPURIN_INLINES_H

#include <math.h>

#include <melee/ft/ftparts.h>
#include <melee/ft/inlines.h>
#include <melee/ft/types.h>

static inline void ftPr_NormalizeAndSetRollAngle(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    while (fp->mv.pr.specialn.x14 < 0.0f) {
        fp->mv.pr.specialn.x14 += M_PI * 2;
    }
    while (fp->mv.pr.specialn.x14 > M_PI * 2) {
        fp->mv.pr.specialn.x14 -= M_PI * 2;
    }
    ftPartSetRotX(fp, FtPart_YRotN, fp->mv.pr.specialn.x14);
}

static inline void ftPr_SetFacingDir(Fighter* fp)
{
    if (fp->mv.pr.specialn.facing_dir != 0.0f) {
        fp->mv.pr.specialn.x34.x = fp->facing_dir =
            fp->mv.pr.specialn.facing_dir;
    }
    fp->mv.pr.specialn.facing_dir = 0.0f;
    fp->mv.pr.specialn.xC = 0;
}

static inline void ftPr_MirrorSpecialN(Fighter* fp)
{
    fp->self_vel.x = -fp->self_vel.x;
    fp->gr_vel = -fp->gr_vel;
    fp->xE4_ground_accel_1 = -fp->xE4_ground_accel_1;
    fp->mv.pr.specialn.x10 = -fp->mv.pr.specialn.x10;
    fp->mv.pr.specialn.x14 = -fp->mv.pr.specialn.x14;
    fp->mv.pr.specialn.x18 = -fp->mv.pr.specialn.x18;
    fp->mv.pr.specialn.x1C = -fp->mv.pr.specialn.x1C;
    fp->mv.pr.specialn.facing_dir = -fp->mv.pr.specialn.facing_dir;
    fp->mv.pr.specialn.x34.x = -fp->mv.pr.specialn.x34.x;
    fp->mv.pr.specialn.x34.y = -fp->mv.pr.specialn.x34.y;
}

#endif
