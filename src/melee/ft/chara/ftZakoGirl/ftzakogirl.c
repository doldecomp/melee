#include <melee/ft/chara/ftZakoGirl/ftzakogirl.h>

#include <melee/ft/ftparts.h>

char lbl_803D3568[] = "PlGl.dat";
char lbl_803D3574[] = "ftDataGirl";
char lbl_803D3580[] = "PlGlNr.dat";
char lbl_803D358C[] = "PlyGirl_Share_joint";
char lbl_803D35A0[] = "PlGlAJ.dat";

#ifdef MUST_MATCH
#pragma push
#pragma force_active on
#endif

Fighter_DemoStrings ftZakoGirl_DemoStrings = {
    NULL,
    "ftDemoIntroMotionFileGirl",
    NULL,
    NULL,
};

#ifdef MUST_MATCH
#pragma pop
#endif

Fighter_CostumeStrings lbl_803D35D8[] = {
    { lbl_803D3580, lbl_803D358C, NULL },
};

void ftZakoGirl_OnDeath(HSD_GObj* gobj)
{
    func_80074A4C(gobj, 0, 0);
}

void ftZakoGirl_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    PUSH_ATTRS(fp, s32);
}

void ftZakoGirl_OnItemPickup(HSD_GObj* fighter_gobj, bool bool)
{
    Fighter_OnItemPickup(fighter_gobj, bool, 0, 0);
}

void ftZakoGirl_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 0);
}

void ftZakoGirl_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 0);
}

void ftZakoGirl_OnItemDrop(HSD_GObj* fighter_gobj, bool bool1)
{
    Fighter_OnItemDrop(fighter_gobj, bool1, 0, 0);
}

void ftZakoGirl_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, s32);
}
