#include "ftCh_Init.h"

#include "ft/fighter.h"
#include "ft/ft_0877.h"
#include "ft/ftbosslib.h"
#include "ft/ftcamera.h"
#include "ft/inlines.h"
#include "ft/types.h"

MotionState ftCh_Init_MotionStateTable[] = {
    { 295, 0, 0x01000000, ftCh_MS_341_Anim, ftCh_MS_341_IASA, ftCh_MS_341_Phys,
      ftCh_MS_341_Coll, ftCamera_UpdateCameraBox },
    { 296, 0, 0x01000000, ftCh_MS_341_Anim, ftCh_MS_341_IASA, ftCh_MS_341_Phys,
      ftCh_MS_341_Coll, ftCamera_UpdateCameraBox },
    { 297, 0, 0x01000000, ftCh_MS_343_Anim, ftCh_MS_343_IASA, ftCh_MS_343_Phys,
      ftCh_MS_343_Coll, ftCamera_UpdateCameraBox },
    { 298, 0, 0x01000000, ftCh_MS_344_Anim, ftCh_MS_344_IASA, ftCh_MS_344_Phys,
      ftCh_MS_344_Coll, ftCamera_UpdateCameraBox },
    { 299, 0, 0x01000000, ftCh_MS_345_Anim, ftCh_MS_345_IASA, ftCh_MS_345_Phys,
      ftCh_MS_345_Coll, ftCamera_UpdateCameraBox },
    { 300, 0, 0x01000000, ftCh_MS_346_Anim, ftCh_MS_346_IASA, ftCh_MS_346_Phys,
      ftCh_MS_346_Coll, ftCamera_UpdateCameraBox },
    { 301, 0, 0x01000000, ftCh_Slap_Anim, ftCh_Slap_IASA, ftCh_Slap_Phys,
      ftCh_Slap_Coll, ftCamera_UpdateCameraBox },
    { 302, 0, 0x01000000, ftCh_MS_348_Anim, ftCh_MS_348_IASA, ftCh_MS_348_Phys,
      ftCh_MS_348_Coll, ftCamera_UpdateCameraBox },
    { 303, 0, 0x01000000, ftCh_Sweep_Anim, ftCh_Sweep_IASA, ftCh_Sweep_Phys,
      ftCh_Sweep_Coll, ftCamera_UpdateCameraBox },
    { 304, 0, 0x01000000, ftCh_MS_350_Anim, ftCh_MS_350_IASA, ftCh_MS_350_Phys,
      ftCh_Sweep_Coll, ftCamera_UpdateCameraBox },
    { 305, 0, 0x01000000, ftCh_Walk_Anim, ftCh_Walk_IASA, ftCh_Walk_Phys,
      ftCh_Walk_Coll, ftCamera_UpdateCameraBox },
    { 306, 0, 0x01000000, ftCh_MS_352_Anim, ftCh_MS_352_IASA, ftCh_MS_352_Phys,
      ftCh_MS_352_Coll, ftCamera_UpdateCameraBox },
    { 307, 0, 0x01000000, ftCh_MS_353_Anim, ftCh_MS_353_IASA, ftCh_MS_353_Phys,
      ftCh_MS_353_Coll, ftCamera_UpdateCameraBox },
    { 308, 0, 0x01000000, ftCh_Drill_Anim, ftCh_Drill_IASA, ftCh_Drill_Phys,
      ftCh_Drill_Coll, ftCamera_UpdateCameraBox },
    { 309, 0, 0x01000000, ftCh_Punch_Anim, ftCh_Punch_IASA, ftCh_Punch_Phys,
      ftCh_Punch_Coll, ftCamera_UpdateCameraBox },
    { 310, 0, 0x01000000, ftCh_MS_356_Anim, ftCh_Punch_IASA, ftCh_Punch_Phys,
      ftCh_Punch_Coll, ftCamera_UpdateCameraBox },
    { 311, 0, 0x01000000, ftCh_MS_357_Anim, ftCh_MS_357_IASA, ftCh_MS_357_Phys,
      ftCh_MS_357_Coll, ftCamera_UpdateCameraBox },
    { 312, 0, 0x01000000, ftCh_GroundSlap_Anim, ftCh_GroundSlap_IASA,
      ftCh_GroundSlap_Phys, ftCh_GroundSlap_Coll, ftCamera_UpdateCameraBox },
    { 313, 0, 0x01000000, ftCh_Poke_Anim, ftCh_Poke_IASA, ftCh_Poke_Phys,
      ftCh_Poke_Coll, ftCamera_UpdateCameraBox },
    { 314, 0, 0x01000000, ftCh_MS_360_Anim, ftCh_MS_360_IASA, ftCh_MS_360_Phys,
      ftCh_MS_360_Coll, ftCamera_UpdateCameraBox },
    { 315, 0, 0x01000000, ftCh_MS_361_Anim, ftCh_MS_361_IASA, ftCh_MS_361_Phys,
      ftCh_MS_361_Coll, ftCamera_UpdateCameraBox },
    { 316, 0, 0x01000000, ftCh_Lasers_Anim, ftCh_Lasers_IASA, ftCh_Lasers_Phys,
      ftCh_Lasers_Coll, ftCamera_UpdateCameraBox },
    { 317, 0, 0x01000000, ftCh_MS_363_Anim, ftCh_MS_363_IASA, ftCh_MS_363_Phys,
      ftCh_MS_363_Coll, ftCamera_UpdateCameraBox },
    { 318, 0, 0x01000000, ftCh_MS_364_Anim, ftCh_MS_364_IASA, ftCh_MS_364_Phys,
      ftCh_MS_364_Coll, ftCamera_UpdateCameraBox },
    { 319, 0, 0x01000000, ftCh_Gun_Anim, ftCh_Gun_IASA, ftCh_Gun_Phys,
      ftCh_Gun_Coll, ftCamera_UpdateCameraBox },
    { 320, 0, 0x01000000, ftCh_Gun_Anim, ftCh_Gun_IASA, ftCh_Gun_Phys,
      ftCh_Gun_Coll, ftCamera_UpdateCameraBox },
    { 321, 0, 0x01000000, ftCh_Jet_Anim, ftCh_Jet_IASA, ftCh_Jet_Phys,
      ftCh_Jet_Coll, ftCamera_UpdateCameraBox },
    { 322, 0, 0x01000000, ftCh_MS_368_Anim, ftCh_MS_368_IASA, ftCh_MS_368_Phys,
      ftCh_MS_368_Coll, ftCamera_UpdateCameraBox },
    { 323, 0, 0x01000000, ftCh_MS_369_Anim, ftCh_MS_369_IASA, ftCh_MS_369_Phys,
      ftCh_MS_369_Coll, ftCamera_UpdateCameraBox },
    { 324, 0, 0x01000000, ftCh_Ram_Anim, ftCh_Ram_IASA, ftCh_Ram_Phys,
      ftCh_Ram_Coll, ftCamera_UpdateCameraBox },
    { 325, 0, 0x01000000, ftCh_Crush_Anim, ftCh_Crush_IASA, ftCh_Crush_Phys,
      ftCh_Crush_Coll, ftCamera_UpdateCameraBox },
    { 326, 0, 0x01000000, ftCh_MS_372_Anim, ftCh_MS_372_IASA, ftCh_MS_372_Phys,
      ftCh_MS_372_Coll, ftCamera_UpdateCameraBox },
    { 327, 0, 0x01000000, ftCh_MS_373_Anim, ftCh_MS_373_IASA, ftCh_MS_373_Phys,
      ftCh_MS_373_Coll, ftCamera_UpdateCameraBox },
    { 328, 0, 0x01000000, ftCh_MS_374_Anim, ftCh_MS_374_IASA, ftCh_MS_374_Phys,
      ftCh_MS_374_Coll, ftCamera_UpdateCameraBox },
    { 329, 0, 0x01000000, ftCh_MS_375_Anim, ftCh_MS_375_IASA, ftCh_MS_375_Phys,
      ftCh_MS_375_Coll, ftCamera_UpdateCameraBox },
    { 330, 0, 0x01000000, ftCh_MS_376_Anim, ftCh_MS_376_IASA, ftCh_MS_376_Phys,
      ftCh_MS_376_Coll, ftCamera_UpdateCameraBox },
    { 331, 0, 0x01000000, ftCh_MS_377_Anim, ftCh_MS_377_IASA, ftCh_MS_377_Phys,
      ftCh_MS_377_Coll, ftCamera_UpdateCameraBox },
    { 332, 0, 0x01000000, ftCh_MS_378_Anim, ftCh_MS_378_IASA, ftCh_MS_378_Phys,
      ftCh_MS_378_Coll, ftCamera_UpdateCameraBox },
    { 333, 0, 0x01000000, ftCh_GrabUnk0_Anim, ftCh_GrabUnk0_IASA,
      ftCh_GrabUnk0_Phys, ftCh_GrabUnk0_Coll, ftCamera_UpdateCameraBox },
    { 334, 0, 0x01000000, ftCh_GrabUnk1_Anim, ftCh_GrabUnk1_IASA,
      ftCh_GrabUnk1_Phys, ftCh_GrabUnk1_Coll, ftCamera_UpdateCameraBox },
    { 335, 0, 0x01000000, ftCh_MS_381_Anim, ftCh_MS_381_IASA, ftCh_MS_381_Phys,
      ftCh_MS_381_Coll, ftCamera_UpdateCameraBox },
    { 336, 0, 0x01000000, ftCh_MS_382_Anim, ftCh_MS_382_IASA, ftCh_MS_382_Phys,
      ftCh_MS_382_Coll, ftCamera_UpdateCameraBox },
    { 337, 0, 0x01000000, ftCh_MS_383_Anim, ftCh_MS_383_IASA, ftCh_MS_383_Phys,
      ftCh_MS_383_Coll, ftCamera_UpdateCameraBox },
    { 338, 0, 0x01000000, ftCh_MS_384_Anim, ftCh_MS_384_IASA, ftCh_MS_384_Phys,
      ftCh_MS_384_Coll, ftCamera_UpdateCameraBox },
    { 339, 0, 0x01000000, ftCh_MS_385_Anim, ftCh_MS_385_IASA, ftCh_MS_385_Phys,
      ftCh_MS_385_Coll, ftCamera_UpdateCameraBox },
    { 340, 0, 0x01000000, ftCh_MS_386_Anim, ftCh_MS_385_IASA, ftCh_MS_385_Phys,
      ftCh_MS_385_Coll, ftCamera_UpdateCameraBox },
    { 341, 0, 0x01000000, ftCh_MS_387_Anim, ftCh_MS_387_IASA, ftCh_MS_387_Phys,
      ftCh_MS_387_Coll, ftCamera_UpdateCameraBox },
    { 342, 0, 0x01000000, ftCh_MS_388_Anim, NULL, ftCh_MS_388_Phys,
      ftCh_MS_388_Coll, ftCamera_UpdateCameraBox },
    { 343, 0, 0x01000000, ftCh_MS_388_Anim, NULL, ftCh_MS_388_Phys,
      ftCh_MS_388_Coll, ftCamera_UpdateCameraBox },
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
