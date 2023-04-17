#include "ftMh_Init.h"

#include "ftMh_MS_341.h"
#include "ftMh_MS_343.h"
#include "ftMh_MS_344.h"
#include "ftMh_MS_346.h"
#include "ftMh_MS_348.h"
#include "ftMh_MS_349.h"
#include "ftMh_MS_352.h"
#include "ftMh_MS_353.h"
#include "ftMh_MS_355.h"
#include "ftMh_MS_357.h"
#include "ftMh_MS_359.h"
#include "ftMh_MS_361.h"
#include "ftMh_MS_363.h"
#include "ftMh_MS_366.h"
#include "ftMh_MS_367.h"
#include "ftMh_MS_368.h"
#include "ftMh_MS_369.h"
#include "ftMh_MS_371_0.h"
#include "ftMh_MS_371_1.h"
#include "ftMh_MS_372.h"
#include "ftMh_MS_376.h"
#include "ftMh_MS_378.h"
#include "ftMh_MS_379.h"
#include "ftMh_MS_380.h"
#include "ftMh_MS_382.h"
#include "ftMh_MS_383.h"
#include "ftMh_MS_384.h"
#include "ftMh_MS_389.h"
#include "types.h"

#include "ft/ft_0877.h"
#include "ft/ftbosslib.h"
#include "ft/ftcamera.h"
#include "ft/types.h"

MotionState ftMh_Init_MotionStateTable[] = {
    { 295, 0, 0x01000000, ftMh_MS_341_Anim, ftMh_MS_341_IASA, ftMh_MS_341_Phys,
      ftMh_MS_341_Coll, ftCamera_UpdateCameraBox },
    { 296, 0, 0x01000000, ftMh_MS_341_Anim, ftMh_MS_341_IASA, ftMh_MS_341_Phys,
      ftMh_MS_341_Coll, ftCamera_UpdateCameraBox },
    { 297, 0, 0x01000000, ftMh_MS_343_Anim, ftMh_MS_343_IASA, ftMh_MS_343_Phys,
      ftMh_MS_343_Coll, ftCamera_UpdateCameraBox },
    { 298, 0, 0x01000000, ftMh_MS_344_Anim, ftMh_MS_344_IASA, ftMh_MS_344_Phys,
      ftMh_MS_344_Coll, ftCamera_UpdateCameraBox },
    { 299, 0, 0x01000000, ftMh_MS_345_Anim, ftMh_MS_344_IASA, ftMh_MS_344_Phys,
      ftMh_MS_344_Coll, ftCamera_UpdateCameraBox },
    { 300, 0, 0x01000000, ftMh_MS_346_Anim, ftMh_MS_346_IASA, ftMh_MS_346_Phys,
      ftMh_MS_346_Coll, ftCamera_UpdateCameraBox },
    { 301, 0, 0x01000000, ftMh_MS_347_Anim, ftMh_MS_347_IASA, ftMh_MS_347_Phys,
      ftMh_MS_347_Coll, ftCamera_UpdateCameraBox },
    { 302, 0, 0x01000000, ftMh_MS_348_Anim, ftMh_MS_348_IASA, ftMh_MS_348_Phys,
      ftMh_MS_348_Coll, ftCamera_UpdateCameraBox },
    { 303, 0, 0x01000000, ftMh_MS_349_Anim, ftMh_MS_349_IASA, ftMh_MS_349_Phys,
      ftMh_MS_349_Coll, ftCamera_UpdateCameraBox },
    { 304, 0, 0x01000000, ftMh_MS_350_Anim, ftMh_MS_350_IASA, ftMh_MS_350_Phys,
      ftMh_MS_350_Coll, ftCamera_UpdateCameraBox },
    { 305, 0, 0x01000000, ftMh_MS_351_Anim, ftMh_MS_351_IASA, ftMh_MS_351_Phys,
      ftMh_MS_351_Coll, ftCamera_UpdateCameraBox },
    { 306, 0, 0x01000000, ftMh_MS_352_Anim, ftMh_MS_352_IASA, ftMh_MS_352_Phys,
      ftMh_MS_352_Coll, ftCamera_UpdateCameraBox },
    { 307, 0, 0x01000000, ftMh_MS_353_Anim, ftMh_MS_353_IASA, ftMh_MS_353_Phys,
      ftMh_MS_353_Coll, ftCamera_UpdateCameraBox },
    { 308, 0, 0x01000000, ftMh_MS_354_Anim, ftMh_MS_354_IASA, ftMh_MS_354_Phys,
      ftMh_MS_354_Coll, ftCamera_UpdateCameraBox },
    { 309, 0, 0x01000000, ftMh_MS_355_Anim, ftMh_MS_355_IASA, ftMh_MS_355_Phys,
      ftMh_MS_355_Coll, ftCamera_UpdateCameraBox },
    { 310, 0, 0x01000000, ftMh_MS_356_Anim, ftMh_MS_356_IASA, ftMh_MS_356_Phys,
      ftMh_MS_356_Coll, ftCamera_UpdateCameraBox },
    { 311, 0, 0x01000000, ftMh_MS_357_Anim, ftMh_MS_357_IASA, ftMh_MS_357_Phys,
      ftMh_MS_357_Coll, ftCamera_UpdateCameraBox },
    { 312, 0, 0x01000000, ftMh_MS_358_Anim, ftMh_MS_358_IASA, ftMh_MS_358_Phys,
      ftMh_MS_358_Coll, ftCamera_UpdateCameraBox },
    { 313, 0, 0x01000000, ftMh_MS_359_Anim, ftMh_MS_359_IASA, ftMh_MS_359_Phys,
      ftMh_MS_359_Coll, ftCamera_UpdateCameraBox },
    { 314, 0, 0x01000000, ftMh_MS_360_Anim, ftMh_MS_359_IASA, ftMh_MS_359_Phys,
      ftMh_MS_359_Coll, ftCamera_UpdateCameraBox },
    { 315, 0, 0x01000000, ftMh_MS_361_Anim, ftMh_MS_361_IASA, ftMh_MS_361_Phys,
      ftMh_MS_361_Coll, ftCamera_UpdateCameraBox },
    { 316, 0, 0x01000000, ftMh_MS_362_Anim, ftMh_MS_362_IASA, ftMh_MS_362_Phys,
      ftMh_MS_362_Coll, ftCamera_UpdateCameraBox },
    { 317, 0, 0x01000000, ftMh_MS_363_Anim, ftMh_MS_363_IASA, ftMh_MS_363_Phys,
      ftMh_MS_363_Coll, ftCamera_UpdateCameraBox },
    { 318, 0, 0x01000000, ftMh_MS_364_Anim, ftMh_MS_364_IASA, ftMh_MS_364_Phys,
      ftMh_MS_364_Coll, ftCamera_UpdateCameraBox },
    { 319, 0, 0x01000000, ftMh_MS_365_Anim, ftMh_MS_365_IASA, ftMh_MS_365_Phys,
      ftMh_MS_365_Coll, ftCamera_UpdateCameraBox },
    { 320, 0, 0x01000000, ftMh_MS_366_Anim, ftMh_MS_366_IASA, ftMh_MS_366_Phys,
      ftMh_MS_366_Coll, ftCamera_UpdateCameraBox },
    { 321, 0, 0x01000000, ftMh_MS_367_Anim, ftMh_MS_367_IASA, ftMh_MS_367_Phys,
      ftMh_MS_367_Coll, ftCamera_UpdateCameraBox },
    { 322, 0, 0x01000000, ftMh_MS_368_Anim, ftMh_MS_368_IASA, ftMh_MS_368_Phys,
      ftMh_MS_368_Coll, ftCamera_UpdateCameraBox },
    { 323, 0, 0x01000000, ftMh_MS_369_Anim, ftMh_MS_369_IASA, ftMh_MS_369_Phys,
      ftMh_MS_369_Coll, ftCamera_UpdateCameraBox },
    { 324, 0, 0x01000000, ftMh_MS_370_Anim, ftMh_MS_370_IASA, ftMh_MS_370_Phys,
      ftMh_MS_370_Coll, ftCamera_UpdateCameraBox },
    { 325, 0, 0x01000000, ftMh_MS_371_Anim, ftMh_MS_371_IASA, ftMh_MS_371_Phys,
      ftMh_MS_371_Coll, ftCamera_UpdateCameraBox },
    { 326, 0, 0x01000000, ftMh_MS_372_Anim, ftMh_MS_372_IASA, ftMh_MS_372_Phys,
      ftMh_MS_372_Coll, ftCamera_UpdateCameraBox },
    { 327, 0, 0x01000000, ftMh_MS_373_Anim, ftMh_MS_373_IASA, ftMh_MS_373_Phys,
      ftMh_MS_373_Coll, ftCamera_UpdateCameraBox },
    { 328, 0, 0x01000000, ftMh_MS_374_Anim, ftMh_MS_374_IASA, ftMh_MS_374_Phys,
      ftMh_MS_374_Coll, ftCamera_UpdateCameraBox },
    { 329, 0, 0x01000000, ftMh_MS_375_Anim, ftMh_MS_375_IASA, ftMh_MS_375_Phys,
      ftMh_MS_375_Coll, ftCamera_UpdateCameraBox },
    { 330, 0, 0x01000000, ftMh_MS_376_Anim, ftMh_MS_376_IASA, ftMh_MS_376_Phys,
      ftMh_MS_376_Coll, ftCamera_UpdateCameraBox },
    { 331, 0, 0x01000000, ftMh_MS_376_Anim, ftMh_MS_376_IASA, ftMh_MS_376_Phys,
      ftMh_MS_376_Coll, ftCamera_UpdateCameraBox },
    { 332, 0, 0x01000000, ftMh_MS_378_Anim, ftMh_MS_378_IASA, ftMh_MS_378_Phys,
      ftMh_MS_378_Coll, ftCamera_UpdateCameraBox },
    { 333, 0, 0x01000000, ftMh_MS_379_Anim, ftMh_MS_379_IASA, ftMh_MS_379_Phys,
      ftMh_MS_379_Coll, ftCamera_UpdateCameraBox },
    { 334, 0, 0x01000000, ftMh_MS_380_Anim, ftMh_MS_380_IASA, ftMh_MS_380_Phys,
      ftMh_MS_380_Coll, ftCamera_UpdateCameraBox },
    { 335, 0, 0x01000000, ftMh_MS_381_Anim, ftMh_MS_381_IASA, ftMh_MS_381_Phys,
      ftMh_MS_381_Coll, ftCamera_UpdateCameraBox },
    { 336, 0, 0x01000000, ftMh_MS_382_Anim, ftMh_MS_382_IASA, ftMh_MS_382_Phys,
      ftMh_MS_382_Coll, ftCamera_UpdateCameraBox },
    { 337, 0, 0x01000000, ftMh_MS_383_Anim, ftMh_MS_383_IASA, ftMh_MS_383_Phys,
      ftMh_MS_383_Coll, ftCamera_UpdateCameraBox },
    { 338, 0, 0x01000000, ftMh_MS_384_Anim, ftMh_MS_384_IASA, ftMh_MS_384_Phys,
      ftMh_MS_384_Coll, ftCamera_UpdateCameraBox },
    { 339, 0, 0x01000000, ftMh_MS_385_Anim, ftMh_MS_385_IASA, ftMh_MS_385_Phys,
      ftMh_MS_385_Coll, ftCamera_UpdateCameraBox },
    { 340, 0, 0x01000000, ftMh_MS_386_Anim, ftMh_MS_386_IASA, ftMh_MS_386_Phys,
      ftMh_MS_386_Coll, ftCamera_UpdateCameraBox },
    { 341, 0, 0x01000000, ftMh_MS_387_Anim, ftMh_MS_387_IASA, ftMh_MS_387_Phys,
      ftMh_MS_387_Coll, ftCamera_UpdateCameraBox },
    { 342, 0, 0x01000000, ftMh_MS_388_Anim, ftMh_MS_388_IASA, ftMh_MS_388_Phys,
      ftMh_MS_388_Coll, ftCamera_UpdateCameraBox },
    { 343, 0, 0x01000000, ftMh_MS_389_Anim, NULL, ftMh_MS_389_Phys,
      ftMh_MS_389_Coll, ftCamera_UpdateCameraBox },
    { 344, 0, 0x01000000, ftMh_MS_389_Anim, NULL, ftMh_MS_389_Phys,
      ftMh_MS_389_Coll, ftCamera_UpdateCameraBox },
};

char ftMh_Init_DatFilename[] = "PlMh.dat";
char ftMh_Init_DataName[] = "ftDataMasterhand";
char ftMh_Init_803D4090[] = "PlMhNr.dat";
char ftMh_Init_803D409C[] = "PlyMasterhand_Share_joint";
char ftMh_Init_AnimDatFilename[] = "PlMhAJ.dat";

Fighter_CostumeStrings ftMh_Init_CostumeStrings[] = {
    { ftMh_Init_803D4090, ftMh_Init_803D409C, NULL },
};

// 8014FC68 0014C848
void ftMh_Init_OnDeath(HSD_GObj* gobj)
{
    return;
}

// 8014FC6C 0014C84C
// https://decomp.me/scratch/Tbp9G
void ftMh_Init_OnLoad(HSD_GObj* gobj)
{
    ftData* ftdata;
    ftMasterHand_SpecialAttrs* ftData_attr;
    void** items;
    Fighter* fp;

    fp = gobj->user_data;
    ftdata = fp->x10C_ftData;
    ftData_attr = ftdata->ext_attr;
    items = ftdata->x48_items;

    PUSH_ATTRS(fp, ftMasterHand_SpecialAttrs);

    ftBossLib_8015BDB4(gobj);
    it_8026B3F8(items[0], 0x7D);
    it_8026B3F8(items[1], 0x7E);
    fp->x2229_b5_no_normal_motion = 1;
    fp->x2229_b6 = 1;
    fp->x2229_b7 = 1;
    fp->x222A_flag.bits.b0 = 1;
    fp->x222A_flag.bits.b1 = 1;
    fp->x2229_b3 = 1;
    fp->cur_pos.x = ftData_attr->x30_pos2.x;
    fp->cur_pos.y = ftData_attr->x30_pos2.y;
    fp->cur_pos.z = 0.0f;
    fp->sv.mh.unk0.x34 = 0;
    fp->sv.mh.unk0.x38 = 0;
    fp->sv.mh.unk0.x3C = 0;
    fp->sv.mh.unk0.x40 = 0;
    fp->sv.mh.unk0.x28 = -1;
    fp->sv.mh.unk0.x2C = -1;
    fp->sv.mh.unk0.x30 = -1;
    fp->sv.mh.unk0.x1C = 0.0f;
    fp->sv.mh.unk0.x20 = 0;
    fp->ev.mh.x222C = ftBossLib_8015C244(gobj, &fp->cur_pos);
    fp->ev.mh.x2238 = 1.0f;
    fp->ev.mh.x224C = 0;
    fp->ev.mh.x2250 = 0x15B;
    fp->ev.mh.x2254 = 0;
    fp->x1A98 = 1;
    ftBossLib_8015BD24(fp->x1A98, &fp->ev.mh.x223C, fp->ev.mh.x2238,
                       ftData_attr->x18, ftData_attr->x20, ftData_attr->x1C);
}
