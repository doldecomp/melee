#include "ftcrazyhand.h"

#include "ft/fighter.h"
#include "ft/ft_0877.h"
#include "ft/ftbosslib.h"
#include "ft/ftcamera.h"
#include "ft/inlines.h"
#include "ft/types.h"

MotionState ftCrazyHand_MotionStateTable[] = {
    { 295, 0, 0x01000000, ftCrazyHand_80156404, ftCrazyHand_80156A70,
      ftCrazyHand_80156AB4, ftCrazyHand_80156AD4, ftCamera_UpdateCameraBox },
    { 296, 0, 0x01000000, ftCrazyHand_80156404, ftCrazyHand_80156A70,
      ftCrazyHand_80156AB4, ftCrazyHand_80156AD4, ftCamera_UpdateCameraBox },
    { 297, 0, 0x01000000, ftCrazyHand_80156FDC, ftCrazyHand_80157018,
      ftCrazyHand_8015705C, ftCrazyHand_8015707C, ftCamera_UpdateCameraBox },
    { 298, 0, 0x01000000, ftCrazyHand_801570CC, ftCrazyHand_80157108,
      ftCrazyHand_8015714C, ftCrazyHand_8015716C, ftCamera_UpdateCameraBox },
    { 299, 0, 0x01000000, ftCrazyHand_80157204, ftCrazyHand_801572D4,
      ftCrazyHand_80157318, ftCrazyHand_80157378, ftCamera_UpdateCameraBox },
    { 300, 0, 0x01000000, ftCrazyHand_801573C8, ftCrazyHand_80157424,
      ftCrazyHand_80157404, ftCrazyHand_80157468, ftCamera_UpdateCameraBox },
    { 301, 0, 0x01000000, ftCrazyHand_801574B8, ftCrazyHand_801574F4,
      ftCrazyHand_80157538, ftCrazyHand_80157558, ftCamera_UpdateCameraBox },
    { 302, 0, 0x01000000, ftCrazyHand_801575A8, ftCrazyHand_801575E4,
      ftCrazyHand_80157628, ftCrazyHand_80157648, ftCamera_UpdateCameraBox },
    { 303, 0, 0x01000000, ftCrazyHand_801576B0, ftCrazyHand_80157724,
      ftCrazyHand_80157768, ftCrazyHand_801578E4, ftCamera_UpdateCameraBox },
    { 304, 0, 0x01000000, ftCrazyHand_80157844, ftCrazyHand_80157880,
      ftCrazyHand_801578C4, ftCrazyHand_801578E4, ftCamera_UpdateCameraBox },
    { 305, 0, 0x01000000, ftCrazyHand_80157934, ftCrazyHand_8015798C,
      ftCrazyHand_801579D0, ftCrazyHand_801579F0, ftCamera_UpdateCameraBox },
    { 306, 0, 0x01000000, ftCrazyHand_80157A40, ftCrazyHand_80157ABC,
      ftCrazyHand_80157B00, ftCrazyHand_80157B54, ftCamera_UpdateCameraBox },
    { 307, 0, 0x01000000, ftCrazyHand_80157BAC, ftCrazyHand_80157BE8,
      ftCrazyHand_80157C2C, ftCrazyHand_80157C4C, ftCamera_UpdateCameraBox },
    { 308, 0, 0x01000000, ftCrazyHand_80157CB0, ftCrazyHand_80157CEC,
      ftCrazyHand_80157D30, ftCrazyHand_80157DF4, ftCamera_UpdateCameraBox },
    { 309, 0, 0x01000000, ftCrazyHand_80157EA0, ftCrazyHand_80157F84,
      ftCrazyHand_80157FC8, ftCrazyHand_80158140, ftCamera_UpdateCameraBox },
    { 310, 0, 0x01000000, ftCrazyHand_80157F48, ftCrazyHand_80157F84,
      ftCrazyHand_80157FC8, ftCrazyHand_80158140, ftCamera_UpdateCameraBox },
    { 311, 0, 0x01000000, ftCrazyHand_801581A4, ftCrazyHand_801581E0,
      ftCrazyHand_80158224, ftCrazyHand_801582D4, ftCamera_UpdateCameraBox },
    { 312, 0, 0x01000000, ftCrazyHand_80158340, ftCrazyHand_8015837C,
      ftCrazyHand_801583C0, ftCrazyHand_801583E0, ftCamera_UpdateCameraBox },
    { 313, 0, 0x01000000, ftCrazyHand_80158450, ftCrazyHand_801584CC,
      ftCrazyHand_80158510, ftCrazyHand_80158530, ftCamera_UpdateCameraBox },
    { 314, 0, 0x01000000, ftCrazyHand_8015870C, ftCrazyHand_80158748,
      ftCrazyHand_8015878C, ftCrazyHand_801587AC, ftCamera_UpdateCameraBox },
    { 315, 0, 0x01000000, ftCrazyHand_80158814, ftCrazyHand_80158850,
      ftCrazyHand_80158894, ftCrazyHand_801588B4, ftCamera_UpdateCameraBox },
    { 316, 0, 0x01000000, ftCrazyHand_80158BBC, ftCrazyHand_80158C44,
      ftCrazyHand_80158C88, ftCrazyHand_80158DF8, ftCamera_UpdateCameraBox },
    { 317, 0, 0x01000000, ftCrazyHand_80158E7C, ftCrazyHand_80158ECC,
      ftCrazyHand_80158F10, ftCrazyHand_80158F30, ftCamera_UpdateCameraBox },
    { 318, 0, 0x01000000, ftCrazyHand_80159134, ftCrazyHand_801591C0,
      ftCrazyHand_80159204, ftCrazyHand_80159264, ftCamera_UpdateCameraBox },
    { 319, 0, 0x01000000, ftCrazyHand_8015ACD0, ftCrazyHand_8015AD28,
      ftCrazyHand_8015AD6C, ftCrazyHand_8015ADCC, ftCamera_UpdateCameraBox },
    { 320, 0, 0x01000000, ftCrazyHand_8015ACD0, ftCrazyHand_8015AD28,
      ftCrazyHand_8015AD6C, ftCrazyHand_8015ADCC, ftCamera_UpdateCameraBox },
    { 321, 0, 0x01000000, ftCrazyHand_80159388, ftCrazyHand_8015940C,
      ftCrazyHand_80159450, ftCrazyHand_801594B0, ftCamera_UpdateCameraBox },
    { 322, 0, 0x01000000, ftCrazyHand_80159534, ftCrazyHand_80159608,
      ftCrazyHand_8015964C, ftCrazyHand_8015966C, ftCamera_UpdateCameraBox },
    { 323, 0, 0x01000000, ftCrazyHand_801596D0, ftCrazyHand_80159788,
      ftCrazyHand_801597CC, ftCrazyHand_801597EC, ftCamera_UpdateCameraBox },
    { 324, 0, 0x01000000, ftCrazyHand_80158FB4, ftCrazyHand_80158FF0,
      ftCrazyHand_80159034, ftCrazyHand_80159094, ftCamera_UpdateCameraBox },
    { 325, 0, 0x01000000, ftCrazyHand_80159858, ftCrazyHand_801598A0,
      ftCrazyHand_801598E4, ftCrazyHand_80159904, ftCamera_UpdateCameraBox },
    { 326, 0, 0x01000000, ftCrazyHand_801599C0, ftCrazyHand_80159A08,
      ftCrazyHand_80159A4C, ftCrazyHand_80159AA0, ftCamera_UpdateCameraBox },
    { 327, 0, 0x01000000, ftCrazyHand_80159D04, ftCrazyHand_80159E8C,
      ftCrazyHand_80159ED0, ftCrazyHand_80159F3C, ftCamera_UpdateCameraBox },
    { 328, 0, 0x01000000, ftCrazyHand_80159F8C, ftCrazyHand_80159FC8,
      ftCrazyHand_8015A00C, ftCrazyHand_8015A02C, ftCamera_UpdateCameraBox },
    { 329, 0, 0x01000000, ftCrazyHand_8015A0C4, ftCrazyHand_8015A10C,
      ftCrazyHand_8015A150, ftCrazyHand_8015A180, ftCamera_UpdateCameraBox },
    { 330, 0, 0x01000000, ftCrazyHand_8015A20C, ftCrazyHand_8015A248,
      ftCrazyHand_8015A28C, ftCrazyHand_8015A2AC, ftCamera_UpdateCameraBox },
    { 331, 0, 0x01000000, ftCrazyHand_8015A318, ftCrazyHand_8015A38C,
      ftCrazyHand_8015A3D0, ftCrazyHand_8015A3F0, ftCamera_UpdateCameraBox },
    { 332, 0, 0x01000000, ftCrazyHand_8015A464, ftCrazyHand_8015A4F8,
      ftCrazyHand_8015A53C, ftCrazyHand_8015A55C, ftCamera_UpdateCameraBox },
    { 333, 0, 0x01000000, ftCrazyHand_8015A5D0, ftCrazyHand_8015A664,
      ftCrazyHand_8015A6A8, ftCrazyHand_8015A6C8, ftCamera_UpdateCameraBox },
    { 334, 0, 0x01000000, ftCrazyHand_8015A6CC, ftCrazyHand_8015A750,
      ftCrazyHand_8015A794, ftCrazyHand_8015A7B4, ftCamera_UpdateCameraBox },
    { 335, 0, 0x01000000, ftCrazyHand_8015A7B8, ftCrazyHand_8015A820,
      ftCrazyHand_8015A864, ftCrazyHand_8015A884, ftCamera_UpdateCameraBox },
    { 336, 0, 0x01000000, ftCrazyHand_8015A8D4, ftCrazyHand_8015A910,
      ftCrazyHand_8015A954, ftCrazyHand_8015A974, ftCamera_UpdateCameraBox },
    { 337, 0, 0x01000000, ftCrazyHand_8015A978, ftCrazyHand_8015AA00,
      ftCrazyHand_8015AA44, ftCrazyHand_8015AAA4, ftCamera_UpdateCameraBox },
    { 338, 0, 0x01000000, ftCrazyHand_8015AB04, ftCrazyHand_8015AB84,
      ftCrazyHand_8015ABC8, ftCrazyHand_8015ABCC, ftCamera_UpdateCameraBox },
    { 339, 0, 0x01000000, ftCrazyHand_8015AF04, ftCrazyHand_8015B0FC,
      ftCrazyHand_8015B140, ftCrazyHand_8015B170, ftCamera_UpdateCameraBox },
    { 340, 0, 0x01000000, ftCrazyHand_8015B000, ftCrazyHand_8015B0FC,
      ftCrazyHand_8015B140, ftCrazyHand_8015B170, ftCamera_UpdateCameraBox },
    { 341, 0, 0x01000000, ftCrazyHand_8015B22C, ftCrazyHand_8015B274,
      ftCrazyHand_8015B2B8, ftCrazyHand_8015B2BC, ftCamera_UpdateCameraBox },
    { 342, 0, 0x01000000, ftCrazyHand_8015BB70, NULL, ftCrazyHand_8015BBD8,
      ftCrazyHand_8015BC38, ftCamera_UpdateCameraBox },
    { 343, 0, 0x01000000, ftCrazyHand_8015BB70, NULL, ftCrazyHand_8015BBD8,
      ftCrazyHand_8015BC38, ftCamera_UpdateCameraBox },
};

char lbl_803D4818[] = "PlCh.dat";
char lbl_803D4824[] = "ftDataCrazyhand";
char lbl_803D4834[] = "PlChNr.dat";
char lbl_803D4840[] = "PlyCrazyhand_Share_joint";
char lbl_803D485C[] = "PlChAJ.dat";

Fighter_CostumeStrings lbl_803D4868[] = {
    { lbl_803D4834, lbl_803D4840, NULL },
};

void ftCrazyhand_OnDeath(HSD_GObj* gobj)
{
    return;
}

void ftCrazyhand_OnLoad(HSD_GObj* gobj)
{
    ftData* ftdata;
    ftCrazyHandAttributes* ftData_attr;
    void** items;
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    ftdata = fp->ft_data;
    ftData_attr = ftdata->ext_attr;
    items = ftdata->x48_items;

    PUSH_ATTRS(fp, ftCrazyHandAttributes);

    ftBossLib_8015BDB4(gobj);
    it_8026B3F8(items[0], 0x7F);
    it_8026B3F8(items[1], 0x80);
    it_8026B3F8(items[2], 0x81);
    fp->x2229_b5_no_normal_motion = 1;
    fp->x2229_b6 = 1;
    fp->x2229_b7 = 1;
    fp->x222A_flag.bits.b0 = 1;
    fp->x222A_flag.bits.b1 = 1;
    fp->x2229_b3 = 1;
    fp->cur_pos.x = ftData_attr->x18;
    fp->cur_pos.y = ftData_attr->x1C;
    fp->cur_pos.z = 0.0f;
    fp->mv.mh.unk0.x28 = 0;
    fp->mv.mh.unk0.x2C = 0;
    fp->mv.mh.unk0.x30 = 0;
    fp->mv.mh.unk0.x34 = 0;
    fp->mv.mh.unk0.x38 = -1;
    fp->mv.mh.unk0.x3C = -1;
    fp->mv.mh.unk0.x40 = -1;
    fp->mv.mh.unk0.x1C = 0.0f;
    fp->mv.mh.unk0.x20 = 0;
    fp->fv.mh.x222C = ftBossLib_8015C244(gobj, &fp->cur_pos);
    fp->fv.mh.x2238 = 1.0f;
    fp->fv.mh.x224C = 0;
    fp->fv.mh.x2250 = 0x159;
    fp->fv.mh.x2254 = 0;
    fp->x1A98 = 1;
    ftBossLib_8015BD24(fp->x1A98, &fp->fv.mh.x223C, fp->fv.ch.x2238,
                       ftData_attr->x0, ftData_attr->x8, ftData_attr->x4);
}

void ftCrazyHand_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftCrazyHandAttributes);
}
