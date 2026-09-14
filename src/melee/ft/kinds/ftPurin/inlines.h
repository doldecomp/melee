#ifndef MELEE_FT_CHARA_FTPURIN_INLINES_H
#define MELEE_FT_CHARA_FTPURIN_INLINES_H

#include <Runtime/platform.h>

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

#endif
