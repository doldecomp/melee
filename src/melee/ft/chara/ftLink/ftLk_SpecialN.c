#include <platform.h>
#include "ftLink/forward.h"

#include "ftLk_SpecialN.h"

#include "ftLk_Init.h"

#include "ft/fighter.h"
#include "it/it_27CF.h"

#ifdef MWERKS_GEKKO
/* static */ float const ftLk_Init_804D9340 = 0.0;
/* static */ float const ftLk_Init_804D9344 = 0.0872664600610733;
/* static */ double const ftLk_Init_804D9348 = 0.0078125;
#endif

ftLk_SpecialNIndex ftLk_SpecialN_GetIndex(HSD_GObj* gobj)
{
    ftLk_SpecialNIndex result = ftLk_SpecialNIndex_None;
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL && fp->fv.lk.x14 != NULL) {
            FtMotionId msid = fp->motion_id;
            switch (msid) {
            case ftLk_MS_SpecialNStart:
            case ftLk_MS_SpecialNLoop:
            case ftLk_MS_SpecialNEnd:
            case ftLk_MS_SpecialAirNStart:
            case ftLk_MS_SpecialAirNLoop:
            case ftLk_MS_SpecialAirNEnd:
                result = msid - ftLk_MS_SpecialNStart;
            }
        }
    }
    return result;
}

void ftLk_SpecialN_UnsetFv10(HSD_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL && fp->fv.lk.x10 != NULL) {
            fp->fv.lk.x10 = NULL;
            if (fp->fv.lk.boomerang_gobj == NULL && fp->fv.lk.x14 == NULL) {
                /// @todo Does this actually do anything? Doesn't seem to
                /// return @c bool.
                ftLk_Init_BoomerangExists(gobj);
            }
        }
    }
}

void ftLk_SpecialN_UnsetFv14(HSD_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL && fp->fv.lk.x14 != NULL) {
            fp->fv.lk.x14 = NULL;
            if (fp->fv.lk.boomerang_gobj == NULL && fp->fv.lk.x10 == NULL) {
                /// @todo Does this actually do anything? Doesn't seem to
                /// return @c bool.
                ftLk_Init_BoomerangExists(gobj);
            }
        }
    }
}

bool ftLk_SpecialN_IsActiveAnd2071b6(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    switch (fp->motion_id) {
    case ftLk_MS_SpecialNStart:
    case ftLk_MS_SpecialNLoop:
    case ftLk_MS_SpecialNEnd:
    case ftLk_MS_SpecialAirNStart:
    case ftLk_MS_SpecialAirNLoop:
    case ftLk_MS_SpecialAirNEnd:
        if (!fp->x2070.x2071_b6) {
            return false;
        }
        /// @attention Fall-through.
    default:
        return true;
    }
}

void ftLk_SpecialN_ProcessFv10(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.lk.x10 != NULL) {
        it_802A8A7C(fp->fv.lk.x10);
        fp->fv.lk.x10 = NULL;
        ftLk_Init_BoomerangExists(gobj);
    }
}

void ftLk_SpecialN_ProcessFv14(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.lk.x14 != NULL) {
        it_802AF304(fp->fv.lk.x14);
        fp->fv.lk.x14 = NULL;
        ftLk_Init_BoomerangExists(gobj);
    }
}
