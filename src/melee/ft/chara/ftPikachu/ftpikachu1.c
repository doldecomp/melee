#include "ftPikachu/ftpikachu1.h"

#include "types.h"

#include "ft/fighter.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftPikachu/ftpikachu.h"

ActionState as_table_pikachu[] = {
    { 295, 0x00340111, 0x12000000, ftPikachu_80124908, ftPikachu_Stub_80124B6C,
      ftPikachu_80124B74, ftPikachu_ActionChange_80124BB4, func_800761C8 },
    { 296, 0x00340511, 0x12000000, ftPikachu_80124A20, ftPikachu_Stub_80124B70,
      ftPikachu_80124B94, ftPikachu_ActionChange_80124C20, func_800761C8 },
    { 297, 0x00340212, 0x13000000, ftPikachu_80124F64, ftPikachu_Stub_80124FDC,
      ftPikachu_80124FE4, ftPikachu_80125084, func_800761C8 },
    { 298, 0x00340212, 0x13000000, ftPikachu_801251BC, ftPikachu_801252FC,
      ftPikachu_8012535C, ftPikachu_8012539C, func_800761C8 },
    { 300, 0x00340212, 0x13000000, ftPikachu_Stub_8012590C,
      ftPikachu_Stub_8012594C, ftPikachu_Stub_80125954,
      ftPikachu_Stub_801259D4, func_800761C8 },
    { 301, 0x00340212, 0x13000000, ftPikachu_80125B34, ftPikachu_Stub_80125BAC,
      ftPikachu_80125BB4, ftPikachu_80125C44, func_800761C8 },
    { 299, 0x00340212, 0x13000000, ftPikachu_8012557C, ftPikachu_Stub_801256B4,
      ftPikachu_801256BC, ftPikachu_801256FC, func_800761C8 },
    { 302, 0x00340612, 0x13000000, ftPikachu_80124FA0, ftPikachu_Stub_80124FE0,
      ftPikachu_80125024, ftPikachu_801250C0, func_800761C8 },
    { 303, 0x00340612, 0x13000000, ftPikachu_8012525C, ftPikachu_8012532C,
      ftPikachu_8012537C, ftPikachu_801253D8, func_800761C8 },
    { 300, 0x00340612, 0x13000000, ftPikachu_80125910, ftPikachu_Stub_80125950,
      ftPikachu_80125958, ftPikachu_801259D8, func_800761C8 },
    { 305, 0x00340612, 0x13000000, ftPikachu_80125B70, ftPikachu_Stub_80125BB0,
      ftPikachu_80125BF4, ftPikachu_80125C80, func_800761C8 },
    { 304, 0x00340612, 0x13000000, ftPikachu_8012561C, ftPikachu_Stub_801256B8,
      ftPikachu_801256DC, ftPikachu_80125738, func_800761C8 },
    { 306, 0x00340113, 0x14000000, ftPikachu_80125ED8, ftPikachu_Stub_80125F50,
      ftPikachu_80125F58, ftPikachu_80125FD8, func_800761C8 },
    { 307, 0x00340113, 0x14000000, ftPikachu_80126144, ftPikachu_Stub_80126424,
      ftPikachu_801265D4, ftPikachu_80126614, func_800761C8 },
    { 308, 0x00340113, 0x14000000, ftPikachu_80127198, ftPikachu_Stub_801272D8,
      ftPikachu_801272E0, ftPikachu_8012738C, func_800761C8 },
    { 309, 0x00340513, 0x14000000, ftPikachu_80125F14, ftPikachu_Stub_80125F54,
      ftPikachu_80125F78, ftPikachu_80126014, func_800761C8 },
    { 310, 0x00340513, 0x14000000, ftPikachu_801262B4, ftPikachu_Stub_80126428,
      ftPikachu_801265F4, ftPikachu_801267C8, func_800761C8 },
    { 311, 0x00340513, 0x14000000, ftPikachu_80127228, ftPikachu_Stub_801272DC,
      ftPikachu_80127310, ftPikachu_801273D4, func_800761C8 },
    { 312, 0x00340014, 0x15000000, ftPikachu_ActionChange_80127CDC, NULL,
      ftPikachu_801280C8, ftPikachu_PrepCallActionChange_801281EC,
      func_800761C8 },
    { 313, 0x00340014, 0x15000000, ftPikachu_ActionChange_80127DE4, NULL,
      ftPikachu_80128108, ftPikachu_PrepCallActionChange_8012823C,
      func_800761C8 },
    { 314, 0x00340014, 0x15000000, ftPikachu_ActionChange_80127FB0, NULL,
      ftPikachu_80128148, ftPikachu_PrepCallActionChange_8012828C,
      func_800761C8 },
    { 315, 0x00340014, 0x15000000, ftPikachu_80128050, NULL,
      ftPikachu_801281AC, ftPikachu_PrepCallActionChange_801282DC,
      func_800761C8 },
    { 316, 0x00340414, 0x15000000, ftPikachu_ActionChange_80127D60, NULL,
      ftPikachu_801280E8, ftPikachu_PrepCallActionChange_80128214,
      func_800761C8 },
    { 317, 0x00340414, 0x15000000, ftPikachu_ActionChange_80127EC0, NULL,
      ftPikachu_80128128, ftPikachu_PrepCallActionChange_80128264,
      func_800761C8 },
    { 318, 0x00340414, 0x15000000, ftPikachu_ActionChange_80128000, NULL,
      ftPikachu_80128168, ftPikachu_PrepCallActionChange_801282B4,
      func_800761C8 },
    { 319, 0x00340414, 0x15000000, ftPikachu_8012808C, NULL,
      ftPikachu_801281CC, ftPikachu_PrepCallActionChange_80128304,
      func_800761C8 },
};

char lbl_803CE0B8[] = "PlPk.dat";
char lbl_803CE0C4[] = "ftDataPikachu";
char lbl_803CE0D4[] = "PlPkNr.dat";
char lbl_803CE0E0[] = "PlyPikachu5K_Share_joint";
char lbl_803CE0FC[] = "PlyPikachu5K_Share_matanim_joint";
char lbl_803CE120[] = "PlPkRe.dat";
char lbl_803CE12C[] = "PlyPikachu5KRe_Share_joint";
char lbl_803CE148[] = "PlyPikachu5KRe_Share_matanim_joint";
char lbl_803CE16C[] = "PlPkBu.dat";
char lbl_803CE178[] = "PlyPikachu5KBu_Share_joint";
char lbl_803CE194[] = "PlyPikachu5KBu_Share_matanim_joint";
char lbl_803CE1B8[] = "PlPkGr.dat";
char lbl_803CE1C4[] = "PlyPikachu5KGr_Share_joint";
char lbl_803CE1E0[] = "PlyPikachu5KGr_Share_matanim_joint";
char lbl_803CE204[] = "PlPkAJ.dat";

Fighter_DemoStrings lbl_803CE290 = {
    "ftDemoResultMotionFilePikachu",
    "ftDemoIntroMotionFilePikachu",
    "ftDemoEndingMotionFilePikachu",
    "ftDemoViWaitMotionFilePikachu",
};

Fighter_CostumeStrings lbl_803CE2A0[] = {
    { lbl_803CE0D4, lbl_803CE0E0, lbl_803CE0FC },
    { lbl_803CE120, lbl_803CE12C, lbl_803CE148 },
    { lbl_803CE16C, lbl_803CE178, lbl_803CE194 },
    { lbl_803CE1B8, lbl_803CE1C4, lbl_803CE1E0 },
};

void ftPikachu_OnLoadForPichu(Fighter* fp)
{
    PUSH_ATTRS(fp, ftPikachuAttributes);
}

void ftPikachu_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    void** item_list = fp->x10C_ftData->x48_items;

    PUSH_ATTRS(fp, ftPikachuAttributes);

    {
        ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;
        func_8026B3F8(item_list[0], pika_attr->xDC);
        func_8026B3F8(item_list[1], pika_attr->x14);
        func_8026B3F8(item_list[2], pika_attr->x18);
    }
}

void ftPikachu_OnDeath(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    func_80074A4C(gobj, 0, 0);
    func_80074A4C(gobj, 1, 0);
}

void ftPikachu_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 0, 0);
}

void ftPikachu_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 0);
}

void ftPikachu_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 0);
}

void ftPikachu_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 0, 0);
}

void ftPikachu_8012467C(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    func_80074A4C(gobj, 1, -1);
    func_80074B0C(gobj, 1, 0);
}

void ftPikachu_801246C0(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    func_80074A4C(gobj, 1, 0);
    func_80074B0C(gobj, 1, 0);
}

void ftPikachu_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftPikachuAttributes);
    if (fp->x34_scale.y != 1.0f) {
        SCALE_HEIGHT_ATTRS(6);
    }
}

void ftPikachu_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftPikachu_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}
