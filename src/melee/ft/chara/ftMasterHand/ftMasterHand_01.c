#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand_05.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand_06.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand_07.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand_08.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand_09.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand_10.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand_11.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand_12.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand_13.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand_14.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand_15.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand_16.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand_17.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand_18.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand_19.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand_20.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand_22.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand_23.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand_25.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand_26.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand_27.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand_28.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand_29.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand_30.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftbosslib.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/types.h>

ActionState as_table_masterhand[] = {
    { 295, 0, 0x01000000, lbl_80150230, lbl_8015082C, lbl_80150870,
      lbl_80150890, func_800761C8 },
    { 296, 0, 0x01000000, lbl_80150230, lbl_8015082C, lbl_80150870,
      lbl_80150890, func_800761C8 },
    { 297, 0, 0x01000000, lbl_80151168, lbl_801511B0, lbl_801511F4,
      lbl_801511F8, func_800761C8 },
    { 298, 0, 0x01000000, lbl_801515B8, lbl_801517B0, lbl_801517F4,
      lbl_80151824, func_800761C8 },
    { 299, 0, 0x01000000, lbl_801516B4, lbl_801517B0, lbl_801517F4,
      lbl_80151824, func_800761C8 },
    { 300, 0, 0x01000000, lbl_80151874, lbl_801518B0, lbl_801518F4,
      lbl_80151914, func_800761C8 },
    { 301, 0, 0x01000000, lbl_8015198C, lbl_80151A44, lbl_80151A88,
      lbl_80151AC4, func_800761C8 },
    { 302, 0, 0x01000000, lbl_80151B14, lbl_80151B70, lbl_80151B50,
      lbl_80151BB4, func_800761C8 },
    { 303, 0, 0x01000000, lbl_80151C04, lbl_80151C40, lbl_80151C84,
      lbl_80151CA4, func_800761C8 },
    { 304, 0, 0x01000000, lbl_80151E10, lbl_80151E4C, lbl_80151E90,
      lbl_80151EB0, func_800761C8 },
    { 305, 0, 0x01000000, lbl_80151F00, lbl_8015204C, lbl_80152090,
      lbl_801520D4, func_800761C8 },
    { 306, 0, 0x01000000, lbl_80152138, lbl_80152174, lbl_801521B8,
      lbl_801521D8, func_800761C8 },
    { 307, 0, 0x01000000, lbl_80151D20, lbl_80151D5C, lbl_80151DA0,
      lbl_80151DC0, func_800761C8 },
    { 308, 0, 0x01000000, lbl_8015223C, lbl_80152278, lbl_801522BC,
      lbl_8015236C, func_800761C8 },
    { 309, 0, 0x01000000, lbl_801523BC, lbl_80152414, lbl_80152458,
      lbl_80152478, func_800761C8 },
    { 310, 0, 0x01000000, lbl_801524C8, lbl_80152544, lbl_80152588,
      lbl_801525DC, func_800761C8 },
    { 311, 0, 0x01000000, lbl_80152634, lbl_80152670, lbl_801526B4,
      lbl_801526D4, func_800761C8 },
    { 312, 0, 0x01000000, lbl_80152738, lbl_80152774, lbl_801527B8,
      lbl_8015287C, func_800761C8 },
    { 313, 0, 0x01000000, lbl_80152928, lbl_80152A0C, lbl_80152A50,
      lbl_80152BC8, func_800761C8 },
    { 314, 0, 0x01000000, lbl_801529D0, lbl_80152A0C, lbl_80152A50,
      lbl_80152BC8, func_800761C8 },
    { 315, 0, 0x01000000, lbl_80152C34, lbl_80152C70, lbl_80152CB4,
      lbl_80152CD4, func_800761C8 },
    { 316, 0, 0x01000000, lbl_80152D44, lbl_80152DC0, lbl_80152E04,
      lbl_80152E24, func_800761C8 },
    { 317, 0, 0x01000000, lbl_80153000, lbl_8015303C, lbl_80153080,
      lbl_801530A0, func_800761C8 },
    { 318, 0, 0x01000000, lbl_80153160, lbl_80153210, lbl_80153254,
      lbl_801533C8, func_800761C8 },
    { 319, 0, 0x01000000, lbl_8015346C, lbl_80153548, lbl_8015358C,
      lbl_801535AC, func_800761C8 },
    { 320, 0, 0x01000000, lbl_8015377C, lbl_801537B8, lbl_801537FC,
      lbl_8015381C, func_800761C8 },
    { 321, 0, 0x01000000, lbl_8015386C, lbl_801538A8, lbl_801538EC,
      lbl_8015390C, func_800761C8 },
    { 322, 0, 0x01000000, lbl_801539A4, lbl_801539EC, lbl_80153A30,
      lbl_80153A60, func_800761C8 },
    { 323, 0, 0x01000000, lbl_80153AEC, lbl_80153B28, lbl_80153B6C,
      lbl_80153B8C, func_800761C8 },
    { 324, 0, 0x01000000, lbl_80153C48, lbl_80153C90, lbl_80153CD4,
      lbl_80153D28, func_800761C8 },
    { 325, 0, 0x01000000, lbl_80153F8C, lbl_80154114, lbl_80154158,
      lbl_801541C4, func_800761C8 },
    { 326, 0, 0x01000000, lbl_80154230, lbl_80154278, lbl_801542BC,
      lbl_801542DC, func_800761C8 },
    { 327, 0, 0x01000000, lbl_80154360, lbl_801543E8, lbl_8015442C,
      lbl_8015459C, func_800761C8 },
    { 328, 0, 0x01000000, lbl_80154620, lbl_80154670, lbl_801546B4,
      lbl_801546D4, func_800761C8 },
    { 329, 0, 0x01000000, lbl_801548D8, lbl_80154964, lbl_801549A8,
      lbl_80154A08, func_800761C8 },
    { 330, 0, 0x01000000, lbl_80154D78, lbl_80154DD0, lbl_80154E14,
      lbl_80154E74, func_800761C8 },
    { 331, 0, 0x01000000, lbl_80154D78, lbl_80154DD0, lbl_80154E14,
      lbl_80154E74, func_800761C8 },
    { 332, 0, 0x01000000, lbl_80154B2C, lbl_80154BB0, lbl_80154BF4,
      lbl_80154C54, func_800761C8 },
    { 333, 0, 0x01000000, lbl_80154ED8, lbl_80154FAC, lbl_80154FF0,
      lbl_80155010, func_800761C8 },
    { 334, 0, 0x01000000, lbl_80155074, lbl_8015512C, lbl_80155170,
      lbl_80155190, func_800761C8 },
    { 335, 0, 0x01000000, lbl_80154758, lbl_80154794, lbl_801547D8,
      lbl_80154838, func_800761C8 },
    { 336, 0, 0x01000000, lbl_8015521C, lbl_80155290, lbl_801552D4,
      lbl_801552F4, func_800761C8 },
    { 337, 0, 0x01000000, lbl_80155388, lbl_8015541C, lbl_80155460,
      lbl_80155480, func_800761C8 },
    { 338, 0, 0x01000000, lbl_8015550C, lbl_80155580, lbl_801555C4,
      lbl_801555E4, func_800761C8 },
    { 339, 0, 0x01000000, lbl_801555E8, lbl_8015565C, lbl_801556A0,
      lbl_801556C0, func_800761C8 },
    { 340, 0, 0x01000000, lbl_801556C4, lbl_801557B0, lbl_801557F4,
      lbl_80155814, func_800761C8 },
    { 341, 0, 0x01000000, lbl_80155864, lbl_801558A0, lbl_801558E4,
      lbl_80155904, func_800761C8 },
    { 342, 0, 0x01000000, lbl_80155908, lbl_80155990, lbl_801559D4,
      lbl_80155A34, func_800761C8 },
    { 343, 0, 0x01000000, lbl_80150F00, NULL, lbl_80150F68, lbl_80150FC8,
      func_800761C8 },
    { 344, 0, 0x01000000, lbl_80150F00, NULL, lbl_80150F68, lbl_80150FC8,
      func_800761C8 },
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
    MasterHandAttributes* ftData_attr;
    void** items;
    Fighter* fp;

    fp = gobj->user_data;
    ftdata = fp->x10C_ftData;
    ftData_attr = ftdata->ext_attr;
    items = ftdata->x48_items;

    PUSH_ATTRS(fp, MasterHandAttributes);

    func_8015BDB4(gobj);
    func_8026B3F8(items[0], 0x7D);
    func_8026B3F8(items[1], 0x7E);
    fp->x2229_b5_no_normal_motion = 1;
    fp->x2229_b6 = 1;
    fp->x2229_b7 = 1;
    fp->x222A_flag.bits.b0 = 1;
    fp->x222A_flag.bits.b1 = 1;
    fp->x2229_b3 = 1;
    fp->xB0_pos.x = ftData_attr->x30_pos2.x;
    fp->xB0_pos.y = ftData_attr->x30_pos2.y;
    fp->xB0_pos.z = 0.0f;
    fp->masterhandVars.x2374 = 0;
    fp->masterhandVars.x2378 = 0;
    fp->masterhandVars.x237C = 0;
    fp->x2380 = 0;
    fp->masterhandVars.x2368 = -1;
    fp->masterhandVars.x236C = -1;
    fp->masterhandVars.x2370 = -1;
    fp->masterhandVars.x235C = 0.0f;
    fp->masterhandVars.x2360 = 0;
    fp->sa.masterhand.x222C = func_8015C244(gobj, &fp->xB0_pos);
    fp->sa.masterhand.x2238 = 1.0f;
    fp->sa.masterhand.x224C = 0;
    fp->sa.masterhand.x2250 = 0x15B;
    fp->sa.masterhand.x2254 = 0;
    fp->x1A98 = 1;
    func_8015BD24(fp->x1A98, &fp->sa.masterhand.x223C, fp->sa.masterhand.x2238,
                  ftData_attr->x18, ftData_attr->x20, ftData_attr->x1C);
}
