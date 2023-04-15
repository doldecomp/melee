#include "ftcrazyhand.h"

#include "ft/fighter.h"
#include "ft/ft_0877.h"
#include "ft/ftbosslib.h"
#include "ft/ftcamera.h"
#include "ft/inlines.h"
#include "ft/types.h"

MotionState ftCh_Init_MotionStateTable[] = {
    { 295, 0, 0x01000000, ftCh_80156404, ftCh_80156A70, ftCh_80156AB4,
      ftCh_80156AD4, ftCamera_UpdateCameraBox },
    { 296, 0, 0x01000000, ftCh_80156404, ftCh_80156A70, ftCh_80156AB4,
      ftCh_80156AD4, ftCamera_UpdateCameraBox },
    { 297, 0, 0x01000000, ftCh_80156FDC, ftCh_80157018, ftCh_8015705C,
      ftCh_8015707C, ftCamera_UpdateCameraBox },
    { 298, 0, 0x01000000, ftCh_801570CC, ftCh_80157108, ftCh_8015714C,
      ftCh_8015716C, ftCamera_UpdateCameraBox },
    { 299, 0, 0x01000000, ftCh_80157204, ftCh_801572D4, ftCh_80157318,
      ftCh_80157378, ftCamera_UpdateCameraBox },
    { 300, 0, 0x01000000, ftCh_801573C8, ftCh_80157424, ftCh_80157404,
      ftCh_80157468, ftCamera_UpdateCameraBox },
    { 301, 0, 0x01000000, ftCh_801574B8, ftCh_801574F4, ftCh_80157538,
      ftCh_80157558, ftCamera_UpdateCameraBox },
    { 302, 0, 0x01000000, ftCh_801575A8, ftCh_801575E4, ftCh_80157628,
      ftCh_80157648, ftCamera_UpdateCameraBox },
    { 303, 0, 0x01000000, ftCh_801576B0, ftCh_80157724, ftCh_80157768,
      ftCh_801578E4, ftCamera_UpdateCameraBox },
    { 304, 0, 0x01000000, ftCh_80157844, ftCh_80157880, ftCh_801578C4,
      ftCh_801578E4, ftCamera_UpdateCameraBox },
    { 305, 0, 0x01000000, ftCh_80157934, ftCh_8015798C, ftCh_801579D0,
      ftCh_801579F0, ftCamera_UpdateCameraBox },
    { 306, 0, 0x01000000, ftCh_80157A40, ftCh_80157ABC, ftCh_80157B00,
      ftCh_80157B54, ftCamera_UpdateCameraBox },
    { 307, 0, 0x01000000, ftCh_80157BAC, ftCh_80157BE8, ftCh_80157C2C,
      ftCh_80157C4C, ftCamera_UpdateCameraBox },
    { 308, 0, 0x01000000, ftCh_80157CB0, ftCh_80157CEC, ftCh_80157D30,
      ftCh_80157DF4, ftCamera_UpdateCameraBox },
    { 309, 0, 0x01000000, ftCh_80157EA0, ftCh_80157F84, ftCh_80157FC8,
      ftCh_80158140, ftCamera_UpdateCameraBox },
    { 310, 0, 0x01000000, ftCh_80157F48, ftCh_80157F84, ftCh_80157FC8,
      ftCh_80158140, ftCamera_UpdateCameraBox },
    { 311, 0, 0x01000000, ftCh_801581A4, ftCh_801581E0, ftCh_80158224,
      ftCh_801582D4, ftCamera_UpdateCameraBox },
    { 312, 0, 0x01000000, ftCh_80158340, ftCh_8015837C, ftCh_801583C0,
      ftCh_801583E0, ftCamera_UpdateCameraBox },
    { 313, 0, 0x01000000, ftCh_80158450, ftCh_801584CC, ftCh_80158510,
      ftCh_80158530, ftCamera_UpdateCameraBox },
    { 314, 0, 0x01000000, ftCh_8015870C, ftCh_80158748, ftCh_8015878C,
      ftCh_801587AC, ftCamera_UpdateCameraBox },
    { 315, 0, 0x01000000, ftCh_80158814, ftCh_80158850, ftCh_80158894,
      ftCh_801588B4, ftCamera_UpdateCameraBox },
    { 316, 0, 0x01000000, ftCh_80158BBC, ftCh_80158C44, ftCh_80158C88,
      ftCh_80158DF8, ftCamera_UpdateCameraBox },
    { 317, 0, 0x01000000, ftCh_80158E7C, ftCh_80158ECC, ftCh_80158F10,
      ftCh_80158F30, ftCamera_UpdateCameraBox },
    { 318, 0, 0x01000000, ftCh_80159134, ftCh_801591C0, ftCh_80159204,
      ftCh_80159264, ftCamera_UpdateCameraBox },
    { 319, 0, 0x01000000, ftCh_8015ACD0, ftCh_8015AD28, ftCh_8015AD6C,
      ftCh_8015ADCC, ftCamera_UpdateCameraBox },
    { 320, 0, 0x01000000, ftCh_8015ACD0, ftCh_8015AD28, ftCh_8015AD6C,
      ftCh_8015ADCC, ftCamera_UpdateCameraBox },
    { 321, 0, 0x01000000, ftCh_80159388, ftCh_8015940C, ftCh_80159450,
      ftCh_801594B0, ftCamera_UpdateCameraBox },
    { 322, 0, 0x01000000, ftCh_80159534, ftCh_80159608, ftCh_8015964C,
      ftCh_8015966C, ftCamera_UpdateCameraBox },
    { 323, 0, 0x01000000, ftCh_801596D0, ftCh_80159788, ftCh_801597CC,
      ftCh_801597EC, ftCamera_UpdateCameraBox },
    { 324, 0, 0x01000000, ftCh_80158FB4, ftCh_80158FF0, ftCh_80159034,
      ftCh_80159094, ftCamera_UpdateCameraBox },
    { 325, 0, 0x01000000, ftCh_80159858, ftCh_801598A0, ftCh_801598E4,
      ftCh_80159904, ftCamera_UpdateCameraBox },
    { 326, 0, 0x01000000, ftCh_801599C0, ftCh_80159A08, ftCh_80159A4C,
      ftCh_80159AA0, ftCamera_UpdateCameraBox },
    { 327, 0, 0x01000000, ftCh_80159D04, ftCh_80159E8C, ftCh_80159ED0,
      ftCh_80159F3C, ftCamera_UpdateCameraBox },
    { 328, 0, 0x01000000, ftCh_80159F8C, ftCh_80159FC8, ftCh_8015A00C,
      ftCh_8015A02C, ftCamera_UpdateCameraBox },
    { 329, 0, 0x01000000, ftCh_8015A0C4, ftCh_8015A10C, ftCh_8015A150,
      ftCh_8015A180, ftCamera_UpdateCameraBox },
    { 330, 0, 0x01000000, ftCh_8015A20C, ftCh_8015A248, ftCh_8015A28C,
      ftCh_8015A2AC, ftCamera_UpdateCameraBox },
    { 331, 0, 0x01000000, ftCh_8015A318, ftCh_8015A38C, ftCh_8015A3D0,
      ftCh_8015A3F0, ftCamera_UpdateCameraBox },
    { 332, 0, 0x01000000, ftCh_8015A464, ftCh_8015A4F8, ftCh_8015A53C,
      ftCh_8015A55C, ftCamera_UpdateCameraBox },
    { 333, 0, 0x01000000, ftCh_8015A5D0, ftCh_8015A664, ftCh_8015A6A8,
      ftCh_8015A6C8, ftCamera_UpdateCameraBox },
    { 334, 0, 0x01000000, ftCh_8015A6CC, ftCh_8015A750, ftCh_8015A794,
      ftCh_8015A7B4, ftCamera_UpdateCameraBox },
    { 335, 0, 0x01000000, ftCh_8015A7B8, ftCh_8015A820, ftCh_8015A864,
      ftCh_8015A884, ftCamera_UpdateCameraBox },
    { 336, 0, 0x01000000, ftCh_8015A8D4, ftCh_8015A910, ftCh_8015A954,
      ftCh_8015A974, ftCamera_UpdateCameraBox },
    { 337, 0, 0x01000000, ftCh_8015A978, ftCh_8015AA00, ftCh_8015AA44,
      ftCh_8015AAA4, ftCamera_UpdateCameraBox },
    { 338, 0, 0x01000000, ftCh_8015AB04, ftCh_8015AB84, ftCh_8015ABC8,
      ftCh_8015ABCC, ftCamera_UpdateCameraBox },
    { 339, 0, 0x01000000, ftCh_8015AF04, ftCh_8015B0FC, ftCh_8015B140,
      ftCh_8015B170, ftCamera_UpdateCameraBox },
    { 340, 0, 0x01000000, ftCh_8015B000, ftCh_8015B0FC, ftCh_8015B140,
      ftCh_8015B170, ftCamera_UpdateCameraBox },
    { 341, 0, 0x01000000, ftCh_8015B22C, ftCh_8015B274, ftCh_8015B2B8,
      ftCh_8015B2BC, ftCamera_UpdateCameraBox },
    { 342, 0, 0x01000000, ftCh_8015BB70, NULL, ftCh_8015BBD8, ftCh_8015BC38,
      ftCamera_UpdateCameraBox },
    { 343, 0, 0x01000000, ftCh_8015BB70, NULL, ftCh_8015BBD8, ftCh_8015BC38,
      ftCamera_UpdateCameraBox },
};

char ftCh_Init_DatFilename[] = "PlCh.dat";
char ftCh_Init_DataName[] = "ftDataCrazyhand";
char ftCh_Init_803D4834[] = "PlChNr.dat";
char ftCh_Init_803D4840[] = "PlyCrazyhand_Share_joint";
char ftCh_Init_AnimDatFilename[] = "PlChAJ.dat";

Fighter_CostumeStrings ftCh_Init_CostumeStrings[] = {
    { ftCh_Init_803D4834, ftCh_Init_803D4840, NULL },
};

void ftCh_Init_OnDeath(HSD_GObj* gobj)
{
    return;
}

void ftCh_Init_OnLoad(HSD_GObj* gobj)
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

void ftCh_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftCrazyHandAttributes);
}
