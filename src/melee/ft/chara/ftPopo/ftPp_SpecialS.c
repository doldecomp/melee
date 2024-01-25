#include <platform.h>

#include "ft/fighter.h"
#include "ft/ftparts.h"
#include "ft/types.h"

#include <melee/ft/chara/ftPopo/ftPp_SpecialS.h>

extern f32 const ftPp_Init_804D9848; // 0.0f

static void setRefGObjFlagAndClear(Fighter* fp)
{
    Fighter_GObj* gobj = fp->x1A5C;
    Fighter* ref_fp;

    if (gobj != NULL) {
        ref_fp = gobj->user_data;
        Fighter_UnkSetFlag_8006CFBC(gobj);
        ref_fp->x1A5C = NULL;
    }
    fp->x1A5C = NULL;
}

void ftPp_SpecialS_8011F68C(Fighter_GObj* gobj)
{
    Fighter* fp;
    u8 _[16];

    fp = gobj->user_data;
    ftParts_8007592C(fp, 0, ftPp_Init_804D9848);
    Fighter_UnkSetFlag_8006CFBC(gobj);
    setRefGObjFlagAndClear(fp);
}

bool ftPp_SpecialS_8011F6FC(HSD_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);

        if (fp != NULL) {
            return fp->cmd_vars[1];
        }
    }

    return true;
}
