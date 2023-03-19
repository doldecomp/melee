#include <melee/ft/chara/ftCrazyHand/ftcrazyhand.h>

#include <melee/ft/chara/ftCrazyHand/ftcrazyhand.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftbosslib.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/types.h>

ActionState as_table_crazyhand[] = {
    { 295, 0, 0x01000000, lbl_80156404, lbl_80156A70, lbl_80156AB4,
      lbl_80156AD4, func_800761C8 },
    { 296, 0, 0x01000000, lbl_80156404, lbl_80156A70, lbl_80156AB4,
      lbl_80156AD4, func_800761C8 },
    { 297, 0, 0x01000000, lbl_80156FDC, lbl_80157018, lbl_8015705C,
      lbl_8015707C, func_800761C8 },
    { 298, 0, 0x01000000, lbl_801570CC, lbl_80157108, lbl_8015714C,
      lbl_8015716C, func_800761C8 },
    { 299, 0, 0x01000000, lbl_80157204, lbl_801572D4, lbl_80157318,
      lbl_80157378, func_800761C8 },
    { 300, 0, 0x01000000, lbl_801573C8, lbl_80157424, lbl_80157404,
      lbl_80157468, func_800761C8 },
    { 301, 0, 0x01000000, lbl_801574B8, lbl_801574F4, lbl_80157538,
      lbl_80157558, func_800761C8 },
    { 302, 0, 0x01000000, lbl_801575A8, lbl_801575E4, lbl_80157628,
      lbl_80157648, func_800761C8 },
    { 303, 0, 0x01000000, lbl_801576B0, lbl_80157724, lbl_80157768,
      lbl_801578E4, func_800761C8 },
    { 304, 0, 0x01000000, lbl_80157844, lbl_80157880, lbl_801578C4,
      lbl_801578E4, func_800761C8 },
    { 305, 0, 0x01000000, lbl_80157934, lbl_8015798C, lbl_801579D0,
      lbl_801579F0, func_800761C8 },
    { 306, 0, 0x01000000, lbl_80157A40, lbl_80157ABC, lbl_80157B00,
      lbl_80157B54, func_800761C8 },
    { 307, 0, 0x01000000, lbl_80157BAC, lbl_80157BE8, lbl_80157C2C,
      lbl_80157C4C, func_800761C8 },
    { 308, 0, 0x01000000, lbl_80157CB0, lbl_80157CEC, lbl_80157D30,
      lbl_80157DF4, func_800761C8 },
    { 309, 0, 0x01000000, lbl_80157EA0, lbl_80157F84, lbl_80157FC8,
      lbl_80158140, func_800761C8 },
    { 310, 0, 0x01000000, lbl_80157F48, lbl_80157F84, lbl_80157FC8,
      lbl_80158140, func_800761C8 },
    { 311, 0, 0x01000000, lbl_801581A4, lbl_801581E0, lbl_80158224,
      lbl_801582D4, func_800761C8 },
    { 312, 0, 0x01000000, lbl_80158340, lbl_8015837C, lbl_801583C0,
      lbl_801583E0, func_800761C8 },
    { 313, 0, 0x01000000, lbl_80158450, lbl_801584CC, lbl_80158510,
      lbl_80158530, func_800761C8 },
    { 314, 0, 0x01000000, lbl_8015870C, lbl_80158748, lbl_8015878C,
      lbl_801587AC, func_800761C8 },
    { 315, 0, 0x01000000, lbl_80158814, lbl_80158850, lbl_80158894,
      lbl_801588B4, func_800761C8 },
    { 316, 0, 0x01000000, lbl_80158BBC, lbl_80158C44, lbl_80158C88,
      lbl_80158DF8, func_800761C8 },
    { 317, 0, 0x01000000, lbl_80158E7C, lbl_80158ECC, lbl_80158F10,
      lbl_80158F30, func_800761C8 },
    { 318, 0, 0x01000000, lbl_80159134, lbl_801591C0, lbl_80159204,
      lbl_80159264, func_800761C8 },
    { 319, 0, 0x01000000, lbl_8015ACD0, lbl_8015AD28, lbl_8015AD6C,
      lbl_8015ADCC, func_800761C8 },
    { 320, 0, 0x01000000, lbl_8015ACD0, lbl_8015AD28, lbl_8015AD6C,
      lbl_8015ADCC, func_800761C8 },
    { 321, 0, 0x01000000, lbl_80159388, lbl_8015940C, lbl_80159450,
      lbl_801594B0, func_800761C8 },
    { 322, 0, 0x01000000, lbl_80159534, lbl_80159608, lbl_8015964C,
      lbl_8015966C, func_800761C8 },
    { 323, 0, 0x01000000, lbl_801596D0, lbl_80159788, lbl_801597CC,
      lbl_801597EC, func_800761C8 },
    { 324, 0, 0x01000000, lbl_80158FB4, lbl_80158FF0, lbl_80159034,
      lbl_80159094, func_800761C8 },
    { 325, 0, 0x01000000, lbl_80159858, lbl_801598A0, lbl_801598E4,
      lbl_80159904, func_800761C8 },
    { 326, 0, 0x01000000, lbl_801599C0, lbl_80159A08, lbl_80159A4C,
      lbl_80159AA0, func_800761C8 },
    { 327, 0, 0x01000000, lbl_80159D04, lbl_80159E8C, lbl_80159ED0,
      lbl_80159F3C, func_800761C8 },
    { 328, 0, 0x01000000, lbl_80159F8C, lbl_80159FC8, lbl_8015A00C,
      lbl_8015A02C, func_800761C8 },
    { 329, 0, 0x01000000, lbl_8015A0C4, lbl_8015A10C, lbl_8015A150,
      lbl_8015A180, func_800761C8 },
    { 330, 0, 0x01000000, lbl_8015A20C, lbl_8015A248, lbl_8015A28C,
      lbl_8015A2AC, func_800761C8 },
    { 331, 0, 0x01000000, lbl_8015A318, lbl_8015A38C, lbl_8015A3D0,
      lbl_8015A3F0, func_800761C8 },
    { 332, 0, 0x01000000, lbl_8015A464, lbl_8015A4F8, lbl_8015A53C,
      lbl_8015A55C, func_800761C8 },
    { 333, 0, 0x01000000, lbl_8015A5D0, lbl_8015A664, lbl_8015A6A8,
      lbl_8015A6C8, func_800761C8 },
    { 334, 0, 0x01000000, lbl_8015A6CC, lbl_8015A750, lbl_8015A794,
      lbl_8015A7B4, func_800761C8 },
    { 335, 0, 0x01000000, lbl_8015A7B8, lbl_8015A820, lbl_8015A864,
      lbl_8015A884, func_800761C8 },
    { 336, 0, 0x01000000, lbl_8015A8D4, lbl_8015A910, lbl_8015A954,
      lbl_8015A974, func_800761C8 },
    { 337, 0, 0x01000000, lbl_8015A978, lbl_8015AA00, lbl_8015AA44,
      lbl_8015AAA4, func_800761C8 },
    { 338, 0, 0x01000000, lbl_8015AB04, lbl_8015AB84, lbl_8015ABC8,
      lbl_8015ABCC, func_800761C8 },
    { 339, 0, 0x01000000, lbl_8015AF04, lbl_8015B0FC, lbl_8015B140,
      lbl_8015B170, func_800761C8 },
    { 340, 0, 0x01000000, lbl_8015B000, lbl_8015B0FC, lbl_8015B140,
      lbl_8015B170, func_800761C8 },
    { 341, 0, 0x01000000, lbl_8015B22C, lbl_8015B274, lbl_8015B2B8,
      lbl_8015B2BC, func_800761C8 },
    { 342, 0, 0x01000000, lbl_8015BB70, NULL, lbl_8015BBD8, lbl_8015BC38,
      func_800761C8 },
    { 343, 0, 0x01000000, lbl_8015BB70, NULL, lbl_8015BBD8, lbl_8015BC38,
      func_800761C8 },
};

char lbl_803D4818[] = "PlCh.dat";
char lbl_803D4824[] = "ftDataCrazyhand";
char lbl_803D4834[] = "PlChNr.dat";
char lbl_803D4840[] = "PlyCrazyhand_Share_joint";
char lbl_803D485C[] = "PlChAJ.dat";

Fighter_CostumeStrings lbl_803D4868[] = {
    { lbl_803D4834, lbl_803D4840, NULL },
};

void ftCrazyhand_OnDeath(HSD_GObj* fighter_gobj)
{
    return;
}

void ftCrazyhand_OnLoad(HSD_GObj* fighter_gobj)
{
    ftData* ftdata;
    ftCrazyHandAttributes* ftData_attr;
    void** items;
    Fighter* fp;

    fp = GET_FIGHTER(fighter_gobj);
    ftdata = fp->x10C_ftData;
    ftData_attr = ftdata->ext_attr;
    items = ftdata->x48_items;

    PUSH_ATTRS(fp, ftCrazyHandAttributes);

    func_8015BDB4(fighter_gobj);
    func_8026B3F8(items[0], 0x7F);
    func_8026B3F8(items[1], 0x80);
    func_8026B3F8(items[2], 0x81);
    fp->x2229_b5_no_normal_motion = 1;
    fp->x2229_b6 = 1;
    fp->x2229_b7 = 1;
    fp->x222A_flag.bits.b0 = 1;
    fp->x222A_flag.bits.b1 = 1;
    fp->x2229_b3 = 1;
    fp->xB0_pos.x = ftData_attr->x18;
    fp->xB0_pos.y = ftData_attr->x1C;
    fp->xB0_pos.z = 0.0f;
    fp->x2368 = 0;
    fp->x236C = 0;
    fp->masterhandVars.x2370 = 0;
    fp->masterhandVars.x2374 = 0;
    fp->masterhandVars.x2378 = -1;
    fp->masterhandVars.x237C = -1;
    fp->masterhandVars.x2380 = -1;
    fp->x235C = 0.0f;
    fp->x2360 = 0;
    fp->ev.mh.x222C = func_8015C244(fighter_gobj, &fp->xB0_pos);
    fp->ev.mh.x2238 = 1.0f;
    fp->ev.mh.x224C = 0;
    fp->ev.mh.x2250 = 0x159;
    fp->ev.mh.x2254 = 0;
    fp->x1A98 = 1;
    func_8015BD24(fp->x1A98, &fp->ev.mh.x223C, fp->ev.ch.x2238, ftData_attr->x0,
                  ftData_attr->x8, ftData_attr->x4);
}

void ftCrazyHand_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftCrazyHandAttributes);
}
