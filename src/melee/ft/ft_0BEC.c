#include "ft/forward.h"

#include "ft_0BEC.h"

#include "ft/ftparts.h"
#include "ftFox/types.h"
#include "ftMario/ftMr_SpecialN.h"
#include "it/it_26B1.h"
#include "it/items/itdrmariopill.h"
#include "it/items/itfoxblaster.h"
#include "it/items/itnessbat.h"

static inline void setupInitialState(Fighter_GObj* gobj,
                                     FtMotionId initial_motion)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, initial_motion, Ft_MF_None, 0.f, 1.f, 0.f,
                              NULL);
    fp->x2219_b2 = true;
    fp->x2219_b1 = true;
    fp->x2228_b1 = true;
    fp->item_gobj = NULL;
    fp->x1984_heldItemSpec = NULL;
}

void ftCo_800BECB0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    setupInitialState(gobj, ftCo_MS_DeadDown);
    switch (fp->kind) {
    case FTKIND_FOX: {
        ftFox_DatAttrs* da = fp->dat_attrs;
        fp->item_gobj =
            it_802AE994(gobj, ftParts_8007500C(fp, FtPart_RThumbNb),
                        da->x20_FOX_BLASTER_GUN_ITKIND);
        it_8026BAE8(fp->item_gobj,
                    fp->x34_scale.y * fp->co_attrs.model_scaling);
    }
    }
}

void ftCo_800BED84(Fighter_GObj* gobj) {}

static inline void FoxHelper(Fighter_GObj* gobj, Fighter* fp)
{
    ftFox_DatAttrs* da = fp->dat_attrs;
    fp->item_gobj = it_802AE994(gobj, ftParts_8007500C(fp, FtPart_RThumbNb),
                                da->x20_FOX_BLASTER_GUN_ITKIND);
    it_8026BAE8(fp->item_gobj, fp->x34_scale.y * fp->co_attrs.model_scaling);
}

static inline void DocHelper(Fighter_GObj* gobj, Fighter* fp)
{
    ftCo_DatAttrs* co;
    fp->item_gobj =
        it_802C09C4(gobj, &fp->cur_pos, ftMr_SpecialN_VitaminRandom(gobj),
                    0x31, 1, 0, fp->facing_dir);
    co = &fp->co_attrs;
    it_8026BAE8(fp->item_gobj,
                0.71428f * (fp->x34_scale.y * co->model_scaling));
    fp->x1984_heldItemSpec =
        it_802C09C4(gobj, &fp->cur_pos, ftMr_SpecialN_VitaminRandom(gobj),
                    0x31, 0, 0, fp->facing_dir);
    it_8026BAE8(fp->x1984_heldItemSpec,
                0.71428f * (fp->x34_scale.y * co->model_scaling));
}

void ftCo_800BED88(Fighter_GObj* gobj)
{
    ///@todo Unused stack
#ifdef MUST_MATCH
    s32 unused;
#endif
    Fighter* fp = gobj->user_data;

    setupInitialState(gobj, 2);

    switch (fp->kind) {
    case FTKIND_FOX: {
        FoxHelper(gobj, fp);
        break;
    }
    case FTKIND_DRMARIO: {
        DocHelper(gobj, fp);
        break;
    }
    }
}

void ftCo_800BEF00(Fighter_GObj* gobj) {}

void ftCo_800BEF04(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_DeadUpStarIce, Ft_MF_None, 0, 1, 0,
                              NULL);
    fp->x2219_b2 = true;
    fp->x2219_b1 = true;
    fp->x2228_b1 = true;
    fp->item_gobj = NULL;
    fp->x1984_heldItemSpec = NULL;
    switch (fp->kind) {
    case FTKIND_NESS: {
        fp->item_gobj =
            it_802AD590(gobj, ftParts_8007500C(fp, FtPart_RThumbNb));
        it_8026BAE8(fp->item_gobj,
                    0.8f * (fp->x34_scale.y * fp->co_attrs.model_scaling));
    }
    }
}

void ftCo_800BEFD0(Fighter_GObj* gobj) {}
