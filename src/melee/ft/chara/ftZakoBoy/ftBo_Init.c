#include "ftZakoBoy/ftBo_Init.h"

#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

char ftBo_Init_DatFilename[] = "PlBo.dat";
char ftBo_Init_DataName[] = "ftDataBoy";
char ftBo_Init_803D3500[] = "PlBoNr.dat";
char ftBo_Init_803D350C[] = "PlyBoy_Share_joint";
char ftBo_Init_AnimDatFilename[] = "PlBoAJ.dat";

#ifdef MUST_MATCH
#pragma push
#pragma force_active on
#endif

Fighter_DemoStrings ftBo_Init_DemoStrings = {
    NULL,
    "ftDemoIntroMotionFileBoy",
    NULL,
    NULL,
};

#ifdef MUST_MATCH
#pragma pop
#endif

Fighter_CostumeStrings ftBo_Init_CostumeStrings[] = {
    { ftBo_Init_803D3500, ftBo_Init_803D350C, NULL },
};

void ftBo_Init_OnDeath(HSD_GObj* gobj)
{
    ftParts_80074A4C(gobj, 0, 0);
}

void ftBo_Init_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 0, 0);
}

void ftBo_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 0);
}

void ftBo_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 0);
}

void ftBo_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 0, 0);
}

void ftBo_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    PUSH_ATTRS(fp, ftZakoboyAttributes);
}

void ftBo_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftZakoboyAttributes);
}
