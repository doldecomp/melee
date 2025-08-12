#include "ft_0BF0.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ftparts.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftFox/types.h"
#include "ftMario/ftMr_SpecialN.h"
#include "it/items/itdrmariopill.h"
#include "it/items/itfoxblaster.h"
#include "it/items/itnessbat.h"

void ftCo_800BF034(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_DeadUpFallHitCameraIce, Ft_MF_None,
                              0, 1, 0, NULL);
    fp->x2219_b2 = true;
    fp->x2219_b1 = true;
    switch (fp->kind) {
    case FTKIND_FOX: {
        ftFox_DatAttrs* da = fp->dat_attrs;
        fp->item_gobj =
            it_802AE994(gobj, ftParts_GetBoneIndex(fp, FtPart_RThumbNb),
                        da->x20_FOX_BLASTER_GUN_ITKIND);
        return;
    }
    case FTKIND_NESS: {
        fp->item_gobj =
            it_802AD590(gobj, ftParts_GetBoneIndex(fp, FtPart_RThumbNb));
        return;
    }
    }
}

void ftCo_800BF108(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_Sleep, Ft_MF_None, 0, 1, 0, NULL);
    fp->x2219_b2 = true;
    fp->x2219_b1 = true;
    switch (fp->kind) {
    case FTKIND_FOX: {
        ftFox_DatAttrs* da = fp->dat_attrs;
        fp->item_gobj =
            it_802AE994(gobj, ftParts_GetBoneIndex(fp, FtPart_RThumbNb),
                        da->x20_FOX_BLASTER_GUN_ITKIND);
        return;
    }
    case FTKIND_NESS: {
        fp->item_gobj =
            it_802AD590(gobj, ftParts_GetBoneIndex(fp, FtPart_RThumbNb));
        return;
    }
    case FTKIND_DRMARIO: {
        fp->item_gobj = it_802C09C4(
            gobj, &fp->cur_pos, ftMr_SpecialN_VitaminRandom(gobj), 49, 2,
            ftParts_GetBoneIndex(fp, FtPart_RThumbNb), fp->facing_dir);
        return;
    }
    }
}

bool ftCo_800BF228(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL && (fp->motion_id == ftCo_MS_DeadUpFallHitCameraIce ||
                           fp->motion_id == ftCo_MS_Sleep))
        {
            return true;
        }
    }
    return false;
}
