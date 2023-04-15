#include "ftMasterHand_01.h"

#include "ftMasterHand_02.h"
#include "ftMasterHand_03.h"
#include "ftMasterHand_04.h"
#include "ftMasterHand_05.h"
#include "ftMasterHand_06.h"
#include "ftMasterHand_07.h"
#include "ftMasterHand_08.h"
#include "ftMasterHand_09.h"
#include "ftMasterHand_10.h"
#include "ftMasterHand_11.h"
#include "ftMasterHand_12.h"
#include "ftMasterHand_13.h"
#include "ftMasterHand_14.h"
#include "ftMasterHand_15.h"
#include "ftMasterHand_16.h"
#include "ftMasterHand_17.h"
#include "ftMasterHand_18.h"
#include "ftMasterHand_19.h"
#include "ftMasterHand_20.h"
#include "ftMasterHand_21.h"
#include "ftMasterHand_22.h"
#include "ftMasterHand_23.h"
#include "ftMasterHand_25.h"
#include "ftMasterHand_26.h"
#include "ftMasterHand_27.h"
#include "ftMasterHand_28.h"
#include "ftMasterHand_29.h"
#include "ftMasterHand_30.h"
#include "types.h"

#include "ft/ft_0877.h"
#include "ft/ftbosslib.h"
#include "ft/ftcamera.h"
#include "ft/inlines.h"
#include "ft/types.h"

MotionState ftMh_Init_MotionStateTable[] = {
    { 295, 0, 0x01000000, ftMh_Unk02_80150230, ftMh_Unk02_8015082C,
      ftMh_Unk02_80150870, ftMh_Unk02_80150890, ftCamera_UpdateCameraBox },
    { 296, 0, 0x01000000, ftMh_Unk02_80150230, ftMh_Unk02_8015082C,
      ftMh_Unk02_80150870, ftMh_Unk02_80150890, ftCamera_UpdateCameraBox },
    { 297, 0, 0x01000000, ftMh_Unk04_80151168, ftMh_Unk04_801511B0,
      ftMh_Unk04_801511F4, ftMh_Unk04_801511F8, ftCamera_UpdateCameraBox },
    { 298, 0, 0x01000000, ftMh_Unk05_801515B8, ftMh_Unk06_801517B0,
      ftMh_Unk06_801517F4, ftMh_Unk06_80151824, ftCamera_UpdateCameraBox },
    { 299, 0, 0x01000000, ftMh_Unk05_801516B4, ftMh_Unk06_801517B0,
      ftMh_Unk06_801517F4, ftMh_Unk06_80151824, ftCamera_UpdateCameraBox },
    { 300, 0, 0x01000000, ftMh_Unk06_80151874, ftMh_Unk06_801518B0,
      ftMh_Unk06_801518F4, ftMh_Unk06_80151914, ftCamera_UpdateCameraBox },
    { 301, 0, 0x01000000, ftMh_Unk06_8015198C, ftMh_Unk06_80151A44,
      ftMh_Unk06_80151A88, ftMh_Unk06_80151AC4, ftCamera_UpdateCameraBox },
    { 302, 0, 0x01000000, ftMh_Unk07_80151B14, ftMh_Unk07_80151B70,
      ftMh_Unk07_80151B50, ftMh_Unk07_80151BB4, ftCamera_UpdateCameraBox },
    { 303, 0, 0x01000000, ftMh_Unk08_80151C04, ftMh_Unk08_80151C40,
      ftMh_Unk08_80151C84, ftMh_Unk08_80151CA4, ftCamera_UpdateCameraBox },
    { 304, 0, 0x01000000, ftMh_Unk09_80151E10, ftMh_Unk09_80151E4C,
      ftMh_Unk09_80151E90, ftMh_Unk09_80151EB0, ftCamera_UpdateCameraBox },
    { 305, 0, 0x01000000, ftMh_Unk09_80151F00, ftMh_Unk09_8015204C,
      ftMh_Unk09_80152090, ftMh_Unk09_801520D4, ftCamera_UpdateCameraBox },
    { 306, 0, 0x01000000, ftMh_Unk10_80152138, ftMh_Unk10_80152174,
      ftMh_Unk10_801521B8, ftMh_Unk10_801521D8, ftCamera_UpdateCameraBox },
    { 307, 0, 0x01000000, ftMh_Unk09_80151D20, ftMh_Unk09_80151D5C,
      ftMh_Unk09_80151DA0, ftMh_Unk09_80151DC0, ftCamera_UpdateCameraBox },
    { 308, 0, 0x01000000, ftMh_Unk10_8015223C, ftMh_Unk10_80152278,
      ftMh_Unk10_801522BC, ftMh_Unk11_8015236C, ftCamera_UpdateCameraBox },
    { 309, 0, 0x01000000, ftMh_Unk11_801523BC, ftMh_Unk11_80152414,
      ftMh_Unk11_80152458, ftMh_Unk11_80152478, ftCamera_UpdateCameraBox },
    { 310, 0, 0x01000000, ftMh_Unk11_801524C8, ftMh_Unk11_80152544,
      ftMh_Unk11_80152588, ftMh_Unk11_801525DC, ftCamera_UpdateCameraBox },
    { 311, 0, 0x01000000, ftMh_Unk12_80152634, ftMh_Unk12_80152670,
      ftMh_Unk12_801526B4, ftMh_Unk12_801526D4, ftCamera_UpdateCameraBox },
    { 312, 0, 0x01000000, ftMh_Unk12_80152738, ftMh_Unk12_80152774,
      ftMh_Unk12_801527B8, ftMh_Unk13_8015287C, ftCamera_UpdateCameraBox },
    { 313, 0, 0x01000000, ftMh_Unk13_80152928, ftMh_Unk13_80152A0C,
      ftMh_Unk13_80152A50, ftMh_Unk14_80152BC8, ftCamera_UpdateCameraBox },
    { 314, 0, 0x01000000, ftMh_Unk13_801529D0, ftMh_Unk13_80152A0C,
      ftMh_Unk13_80152A50, ftMh_Unk14_80152BC8, ftCamera_UpdateCameraBox },
    { 315, 0, 0x01000000, ftMh_Unk14_80152C34, ftMh_Unk14_80152C70,
      ftMh_Unk14_80152CB4, ftMh_Unk14_80152CD4, ftCamera_UpdateCameraBox },
    { 316, 0, 0x01000000, ftMh_Unk14_80152D44, ftMh_Unk14_80152DC0,
      ftMh_Unk14_80152E04, ftMh_Unk14_80152E24, ftCamera_UpdateCameraBox },
    { 317, 0, 0x01000000, ftMh_Unk15_80153000, ftMh_Unk15_8015303C,
      ftMh_Unk15_80153080, ftMh_Unk15_801530A0, ftCamera_UpdateCameraBox },
    { 318, 0, 0x01000000, ftMh_Unk15_80153160, ftMh_Unk15_80153210,
      ftMh_Unk15_80153254, ftMh_Unk15_801533C8, ftCamera_UpdateCameraBox },
    { 319, 0, 0x01000000, ftMh_Unk15_8015346C, ftMh_Unk15_80153548,
      ftMh_Unk15_8015358C, ftMh_Unk15_801535AC, ftCamera_UpdateCameraBox },
    { 320, 0, 0x01000000, ftMh_Unk16_8015377C, ftMh_Unk16_801537B8,
      ftMh_Unk16_801537FC, ftMh_Unk16_8015381C, ftCamera_UpdateCameraBox },
    { 321, 0, 0x01000000, ftMh_Unk17_8015386C, ftMh_Unk17_801538A8,
      ftMh_Unk17_801538EC, ftMh_Unk17_8015390C, ftCamera_UpdateCameraBox },
    { 322, 0, 0x01000000, ftMh_Unk17_801539A4, ftMh_Unk18_801539EC,
      ftMh_Unk18_80153A30, ftMh_Unk18_80153A60, ftCamera_UpdateCameraBox },
    { 323, 0, 0x01000000, ftMh_Unk19_80153AEC, ftMh_Unk19_80153B28,
      ftMh_Unk19_80153B6C, ftMh_Unk19_80153B8C, ftCamera_UpdateCameraBox },
    { 324, 0, 0x01000000, ftMh_Unk19_80153C48, ftMh_Unk19_80153C90,
      ftMh_Unk19_80153CD4, ftMh_Unk20_80153D28, ftCamera_UpdateCameraBox },
    { 325, 0, 0x01000000, ftMh_Unk20_80153F8C, ftMh_Unk20_80154114,
      ftMh_Unk20_80154158, ftMh_Unk21_801541C4, ftCamera_UpdateCameraBox },
    { 326, 0, 0x01000000, ftMh_Unk22_80154230, ftMh_Unk22_80154278,
      ftMh_Unk22_801542BC, ftMh_Unk22_801542DC, ftCamera_UpdateCameraBox },
    { 327, 0, 0x01000000, ftMh_Unk22_80154360, ftMh_Unk22_801543E8,
      ftMh_Unk22_8015442C, ftMh_Unk22_8015459C, ftCamera_UpdateCameraBox },
    { 328, 0, 0x01000000, ftMh_Unk22_80154620, ftMh_Unk22_80154670,
      ftMh_Unk22_801546B4, ftMh_Unk22_801546D4, ftCamera_UpdateCameraBox },
    { 329, 0, 0x01000000, ftMh_Unk22_801548D8, ftMh_Unk22_80154964,
      ftMh_Unk22_801549A8, ftMh_Unk22_80154A08, ftCamera_UpdateCameraBox },
    { 330, 0, 0x01000000, ftMh_Unk25_80154D78, ftMh_Unk25_80154DD0,
      ftMh_Unk25_80154E14, ftMh_Unk25_80154E74, ftCamera_UpdateCameraBox },
    { 331, 0, 0x01000000, ftMh_Unk25_80154D78, ftMh_Unk25_80154DD0,
      ftMh_Unk25_80154E14, ftMh_Unk25_80154E74, ftCamera_UpdateCameraBox },
    { 332, 0, 0x01000000, ftMh_Unk23_80154B2C, ftMh_Unk23_80154BB0,
      ftMh_Unk23_80154BF4, ftMh_Unk23_80154C54, ftCamera_UpdateCameraBox },
    { 333, 0, 0x01000000, ftMh_Unk25_80154ED8, ftMh_Unk26_80154FAC,
      ftMh_Unk26_80154FF0, ftMh_Unk26_80155010, ftCamera_UpdateCameraBox },
    { 334, 0, 0x01000000, ftMh_Unk27_80155074, ftMh_Unk27_8015512C,
      ftMh_Unk27_80155170, ftMh_Unk27_80155190, ftCamera_UpdateCameraBox },
    { 335, 0, 0x01000000, ftMh_Unk22_80154758, ftMh_Unk22_80154794,
      ftMh_Unk22_801547D8, ftMh_Unk22_80154838, ftCamera_UpdateCameraBox },
    { 336, 0, 0x01000000, ftMh_Unk28_8015521C, ftMh_Unk28_80155290,
      ftMh_Unk28_801552D4, ftMh_Unk28_801552F4, ftCamera_UpdateCameraBox },
    { 337, 0, 0x01000000, ftMh_Unk29_80155388, ftMh_Unk29_8015541C,
      ftMh_Unk29_80155460, ftMh_Unk29_80155480, ftCamera_UpdateCameraBox },
    { 338, 0, 0x01000000, ftMh_Unk30_8015550C, ftMh_Unk30_80155580,
      ftMh_Unk30_801555C4, ftMh_Unk30_801555E4, ftCamera_UpdateCameraBox },
    { 339, 0, 0x01000000, ftMh_Unk30_801555E8, ftMh_Unk30_8015565C,
      ftMh_Unk30_801556A0, ftMh_Unk30_801556C0, ftCamera_UpdateCameraBox },
    { 340, 0, 0x01000000, ftMh_Unk30_801556C4, ftMh_Unk30_801557B0,
      ftMh_Unk30_801557F4, ftMh_Unk30_80155814, ftCamera_UpdateCameraBox },
    { 341, 0, 0x01000000, ftMh_Unk30_80155864, ftMh_Unk30_801558A0,
      ftMh_Unk30_801558E4, ftMh_Unk30_80155904, ftCamera_UpdateCameraBox },
    { 342, 0, 0x01000000, ftMh_Unk30_80155908, ftMh_Unk30_80155990,
      ftMh_Unk30_801559D4, ftMh_Unk30_80155A34, ftCamera_UpdateCameraBox },
    { 343, 0, 0x01000000, ftMh_Unk03_80150F00, NULL, ftMh_Unk03_80150F68,
      ftMh_Unk03_80150FC8, ftCamera_UpdateCameraBox },
    { 344, 0, 0x01000000, ftMh_Unk03_80150F00, NULL, ftMh_Unk03_80150F68,
      ftMh_Unk03_80150FC8, ftCamera_UpdateCameraBox },
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
    ftdata = fp->ft_data;
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
    fp->mv.mh.unk0.x34 = 0;
    fp->mv.mh.unk0.x38 = 0;
    fp->mv.mh.unk0.x3C = 0;
    fp->mv.mh.unk0.x40 = 0;
    fp->mv.mh.unk0.x28 = -1;
    fp->mv.mh.unk0.x2C = -1;
    fp->mv.mh.unk0.x30 = -1;
    fp->mv.mh.unk0.x1C = 0.0f;
    fp->mv.mh.unk0.x20 = 0;
    fp->fv.mh.x222C = ftBossLib_8015C244(gobj, &fp->cur_pos);
    fp->fv.mh.x2238 = 1.0f;
    fp->fv.mh.x224C = 0;
    fp->fv.mh.x2250 = 0x15B;
    fp->fv.mh.x2254 = 0;
    fp->x1A98 = 1;
    ftBossLib_8015BD24(fp->x1A98, &fp->fv.mh.x223C, fp->fv.mh.x2238,
                       ftData_attr->x18, ftData_attr->x20, ftData_attr->x1C);
}
