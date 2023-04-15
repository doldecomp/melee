#include "ftZakoGirl/ftzakogirl.h"

#include "ft/ftparts.h"
#include "ft/inlines.h"

char ftGl_Init_DatFilename[] = "PlGl.dat";
char ftGl_Init_DataName[] = "ftDataGirl";
char ftGl_Init_803D3580[] = "PlGlNr.dat";
char ftGl_Init_803D358C[] = "PlyGirl_Share_joint";
char ftGl_Init_AnimDatFilename[] = "PlGlAJ.dat";

#ifdef MUST_MATCH
#pragma push
#pragma force_active on
#endif

Fighter_DemoStrings ftGl_DemoStrings = {
    NULL,
    "ftDemoIntroMotionFileGirl",
    NULL,
    NULL,
};

#ifdef MUST_MATCH
#pragma pop
#endif

Fighter_CostumeStrings ftGl_Init_CostumeStrings[] = {
    { ftGl_Init_803D3580, ftGl_Init_803D358C, NULL },
};

void ftGl_Init_OnDeath(HSD_GObj* gobj)
{
    ftParts_80074A4C(gobj, 0, 0);
}

void ftGl_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    PUSH_ATTRS(fp, s32);
}

void ftGl_Init_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 0, 0);
}

void ftGl_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 0);
}

void ftGl_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 0);
}

void ftGl_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 0, 0);
}

void ftGl_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, s32);
}
