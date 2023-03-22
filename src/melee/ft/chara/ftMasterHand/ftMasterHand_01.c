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

#include "ft/ft_unknown_006.h"
#include "ft/ftbosslib.h"
#include "ft/ftcamera.h"
#include "ft/inlines.h"
#include "ft/types.h"

MotionState ftMasterHand_MotionStateTable[] = {
    { 295, 0, 0x01000000, ftMasterHand_80150230, ftMasterHand_8015082C,
      ftMasterHand_80150870, ftMasterHand_80150890, ftCamera_UpdateCameraBox },
    { 296, 0, 0x01000000, ftMasterHand_80150230, ftMasterHand_8015082C,
      ftMasterHand_80150870, ftMasterHand_80150890, ftCamera_UpdateCameraBox },
    { 297, 0, 0x01000000, ftMasterHand_80151168, ftMasterHand_801511B0,
      ftMasterHand_801511F4, ftMasterHand_801511F8, ftCamera_UpdateCameraBox },
    { 298, 0, 0x01000000, ftMasterHand_801515B8, ftMasterHand_801517B0,
      ftMasterHand_801517F4, ftMasterHand_80151824, ftCamera_UpdateCameraBox },
    { 299, 0, 0x01000000, ftMasterHand_801516B4, ftMasterHand_801517B0,
      ftMasterHand_801517F4, ftMasterHand_80151824, ftCamera_UpdateCameraBox },
    { 300, 0, 0x01000000, ftMasterHand_80151874, ftMasterHand_801518B0,
      ftMasterHand_801518F4, ftMasterHand_80151914, ftCamera_UpdateCameraBox },
    { 301, 0, 0x01000000, ftMasterHand_8015198C, ftMasterHand_80151A44,
      ftMasterHand_80151A88, ftMasterHand_80151AC4, ftCamera_UpdateCameraBox },
    { 302, 0, 0x01000000, ftMasterHand_80151B14, ftMasterHand_80151B70,
      ftMasterHand_80151B50, ftMasterHand_80151BB4, ftCamera_UpdateCameraBox },
    { 303, 0, 0x01000000, ftMasterHand_80151C04, ftMasterHand_80151C40,
      ftMasterHand_80151C84, ftMasterHand_80151CA4, ftCamera_UpdateCameraBox },
    { 304, 0, 0x01000000, ftMasterHand_80151E10, ftMasterHand_80151E4C,
      ftMasterHand_80151E90, ftMasterHand_80151EB0, ftCamera_UpdateCameraBox },
    { 305, 0, 0x01000000, ftMasterHand_80151F00, ftMasterHand_8015204C,
      ftMasterHand_80152090, ftMasterHand_801520D4, ftCamera_UpdateCameraBox },
    { 306, 0, 0x01000000, ftMasterHand_80152138, ftMasterHand_80152174,
      ftMasterHand_801521B8, ftMasterHand_801521D8, ftCamera_UpdateCameraBox },
    { 307, 0, 0x01000000, ftMasterHand_80151D20, ftMasterHand_80151D5C,
      ftMasterHand_80151DA0, ftMasterHand_80151DC0, ftCamera_UpdateCameraBox },
    { 308, 0, 0x01000000, ftMasterHand_8015223C, ftMasterHand_80152278,
      ftMasterHand_801522BC, ftMasterHand_8015236C, ftCamera_UpdateCameraBox },
    { 309, 0, 0x01000000, ftMasterHand_801523BC, ftMasterHand_80152414,
      ftMasterHand_80152458, ftMasterHand_80152478, ftCamera_UpdateCameraBox },
    { 310, 0, 0x01000000, ftMasterHand_801524C8, ftMasterHand_80152544,
      ftMasterHand_80152588, ftMasterHand_801525DC, ftCamera_UpdateCameraBox },
    { 311, 0, 0x01000000, ftMasterHand_80152634, ftMasterHand_80152670,
      ftMasterHand_801526B4, ftMasterHand_801526D4, ftCamera_UpdateCameraBox },
    { 312, 0, 0x01000000, ftMasterHand_80152738, ftMasterHand_80152774,
      ftMasterHand_801527B8, ftMasterHand_8015287C, ftCamera_UpdateCameraBox },
    { 313, 0, 0x01000000, ftMasterHand_80152928, ftMasterHand_80152A0C,
      ftMasterHand_80152A50, ftMasterHand_80152BC8, ftCamera_UpdateCameraBox },
    { 314, 0, 0x01000000, ftMasterHand_801529D0, ftMasterHand_80152A0C,
      ftMasterHand_80152A50, ftMasterHand_80152BC8, ftCamera_UpdateCameraBox },
    { 315, 0, 0x01000000, ftMasterHand_80152C34, ftMasterHand_80152C70,
      ftMasterHand_80152CB4, ftMasterHand_80152CD4, ftCamera_UpdateCameraBox },
    { 316, 0, 0x01000000, ftMasterHand_80152D44, ftMasterHand_80152DC0,
      ftMasterHand_80152E04, ftMasterHand_80152E24, ftCamera_UpdateCameraBox },
    { 317, 0, 0x01000000, ftMasterHand_80153000, ftMasterHand_8015303C,
      ftMasterHand_80153080, ftMasterHand_801530A0, ftCamera_UpdateCameraBox },
    { 318, 0, 0x01000000, ftMasterHand_80153160, ftMasterHand_80153210,
      ftMasterHand_80153254, ftMasterHand_801533C8, ftCamera_UpdateCameraBox },
    { 319, 0, 0x01000000, ftMasterHand_8015346C, ftMasterHand_80153548,
      ftMasterHand_8015358C, ftMasterHand_801535AC, ftCamera_UpdateCameraBox },
    { 320, 0, 0x01000000, ftMasterHand_8015377C, ftMasterHand_801537B8,
      ftMasterHand_801537FC, ftMasterHand_8015381C, ftCamera_UpdateCameraBox },
    { 321, 0, 0x01000000, ftMasterHand_8015386C, ftMasterHand_801538A8,
      ftMasterHand_801538EC, ftMasterHand_8015390C, ftCamera_UpdateCameraBox },
    { 322, 0, 0x01000000, ftMasterHand_801539A4, ftMasterHand_801539EC,
      ftMasterHand_80153A30, ftMasterHand_80153A60, ftCamera_UpdateCameraBox },
    { 323, 0, 0x01000000, ftMasterHand_80153AEC, ftMasterHand_80153B28,
      ftMasterHand_80153B6C, ftMasterHand_80153B8C, ftCamera_UpdateCameraBox },
    { 324, 0, 0x01000000, ftMasterHand_80153C48, ftMasterHand_80153C90,
      ftMasterHand_80153CD4, ftMasterHand_80153D28, ftCamera_UpdateCameraBox },
    { 325, 0, 0x01000000, ftMasterHand_80153F8C, ftMasterHand_80154114,
      ftMasterHand_80154158, ftMasterHand_801541C4, ftCamera_UpdateCameraBox },
    { 326, 0, 0x01000000, ftMasterHand_80154230, ftMasterHand_80154278,
      ftMasterHand_801542BC, ftMasterHand_801542DC, ftCamera_UpdateCameraBox },
    { 327, 0, 0x01000000, ftMasterHand_80154360, ftMasterHand_801543E8,
      ftMasterHand_8015442C, ftMasterHand_8015459C, ftCamera_UpdateCameraBox },
    { 328, 0, 0x01000000, ftMasterHand_80154620, ftMasterHand_80154670,
      ftMasterHand_801546B4, ftMasterHand_801546D4, ftCamera_UpdateCameraBox },
    { 329, 0, 0x01000000, ftMasterHand_801548D8, ftMasterHand_80154964,
      ftMasterHand_801549A8, ftMasterHand_80154A08, ftCamera_UpdateCameraBox },
    { 330, 0, 0x01000000, ftMasterHand_80154D78, ftMasterHand_80154DD0,
      ftMasterHand_80154E14, ftMasterHand_80154E74, ftCamera_UpdateCameraBox },
    { 331, 0, 0x01000000, ftMasterHand_80154D78, ftMasterHand_80154DD0,
      ftMasterHand_80154E14, ftMasterHand_80154E74, ftCamera_UpdateCameraBox },
    { 332, 0, 0x01000000, ftMasterHand_80154B2C, ftMasterHand_80154BB0,
      ftMasterHand_80154BF4, ftMasterHand_80154C54, ftCamera_UpdateCameraBox },
    { 333, 0, 0x01000000, ftMasterHand_80154ED8, ftMasterHand_80154FAC,
      ftMasterHand_80154FF0, ftMasterHand_80155010, ftCamera_UpdateCameraBox },
    { 334, 0, 0x01000000, ftMasterHand_80155074, ftMasterHand_8015512C,
      ftMasterHand_80155170, ftMasterHand_80155190, ftCamera_UpdateCameraBox },
    { 335, 0, 0x01000000, ftMasterHand_80154758, ftMasterHand_80154794,
      ftMasterHand_801547D8, ftMasterHand_80154838, ftCamera_UpdateCameraBox },
    { 336, 0, 0x01000000, ftMasterHand_8015521C, ftMasterHand_80155290,
      ftMasterHand_801552D4, ftMasterHand_801552F4, ftCamera_UpdateCameraBox },
    { 337, 0, 0x01000000, ftMasterHand_80155388, ftMasterHand_8015541C,
      ftMasterHand_80155460, ftMasterHand_80155480, ftCamera_UpdateCameraBox },
    { 338, 0, 0x01000000, ftMasterHand_8015550C, ftMasterHand_80155580,
      ftMasterHand_801555C4, ftMasterHand_801555E4, ftCamera_UpdateCameraBox },
    { 339, 0, 0x01000000, ftMasterHand_801555E8, ftMasterHand_8015565C,
      ftMasterHand_801556A0, ftMasterHand_801556C0, ftCamera_UpdateCameraBox },
    { 340, 0, 0x01000000, ftMasterHand_801556C4, ftMasterHand_801557B0,
      ftMasterHand_801557F4, ftMasterHand_80155814, ftCamera_UpdateCameraBox },
    { 341, 0, 0x01000000, ftMasterHand_80155864, ftMasterHand_801558A0,
      ftMasterHand_801558E4, ftMasterHand_80155904, ftCamera_UpdateCameraBox },
    { 342, 0, 0x01000000, ftMasterHand_80155908, ftMasterHand_80155990,
      ftMasterHand_801559D4, ftMasterHand_80155A34, ftCamera_UpdateCameraBox },
    { 343, 0, 0x01000000, ftMasterHand_80150F00, NULL, ftMasterHand_80150F68,
      ftMasterHand_80150FC8, ftCamera_UpdateCameraBox },
    { 344, 0, 0x01000000, ftMasterHand_80150F00, NULL, ftMasterHand_80150F68,
      ftMasterHand_80150FC8, ftCamera_UpdateCameraBox },
};

char lbl_803D4070[] = "PlMh.dat";
char lbl_803D407C[] = "ftDataMasterhand";
char lbl_803D4090[] = "PlMhNr.dat";
char lbl_803D409C[] = "PlyMasterhand_Share_joint";
char lbl_803D40B8[] = "PlMhAJ.dat";

Fighter_CostumeStrings lbl_803D40C4[] = {
    { lbl_803D4090, lbl_803D409C, NULL },
};

// 8014FC68 0014C848
void ftMasterhand_OnDeath(HSD_GObj* gobj)
{
    return;
}

// 8014FC6C 0014C84C
// https://decomp.me/scratch/Tbp9G
void ftMasterhand_OnLoad(HSD_GObj* gobj)
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

    func_8015BDB4(gobj);
    func_8026B3F8(items[0], 0x7D);
    func_8026B3F8(items[1], 0x7E);
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
    fp->fv.mh.x222C = func_8015C244(gobj, &fp->cur_pos);
    fp->fv.mh.x2238 = 1.0f;
    fp->fv.mh.x224C = 0;
    fp->fv.mh.x2250 = 0x15B;
    fp->fv.mh.x2254 = 0;
    fp->x1A98 = 1;
    func_8015BD24(fp->x1A98, &fp->fv.mh.x223C, fp->fv.mh.x2238,
                  ftData_attr->x18, ftData_attr->x20, ftData_attr->x1C);
}
