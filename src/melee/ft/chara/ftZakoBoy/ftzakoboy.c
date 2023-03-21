#include <melee/ft/chara/ftZakoBoy/ftzakoboy.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/types.h>

char lbl_803D34E8[] = "PlBo.dat";
char lbl_803D34F4[] = "ftDataBoy";
char lbl_803D3500[] = "PlBoNr.dat";
char lbl_803D350C[] = "PlyBoy_Share_joint";
char lbl_803D3520[] = "PlBoAJ.dat";

#ifdef MUST_MATCH
#pragma push
#pragma force_active on
#endif

Fighter_DemoStrings ftZakoBoy_DemoStrings = {
    NULL,
    "ftDemoIntroMotionFileBoy",
    NULL,
    NULL,
};

#ifdef MUST_MATCH
#pragma pop
#endif

Fighter_CostumeStrings lbl_803D3558[] = {
    { lbl_803D3500, lbl_803D350C, NULL },
};

void ftZakoBoy_OnDeath(HSD_GObj* gobj)
{
    func_80074A4C(gobj, 0, 0);
}

void ftZakoBoy_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 0, 0);
}

void ftZakoBoy_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 0);
}

void ftZakoBoy_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 0);
}

void ftZakoBoy_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 0, 0);
}

void ftZakoBoy_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    PUSH_ATTRS(fp, ftZakoboyAttributes);
}

void ftZakoBoy_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftZakoboyAttributes);
}
