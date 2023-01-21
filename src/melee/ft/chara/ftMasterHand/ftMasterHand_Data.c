#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>
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
#include <melee/ft/chara/ftMasterHand/ftMasterHand_5.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand_6.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand_7.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand_8.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand_9.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/types.h>

ActionState as_table_masterhand[] = {
    { 295, FLAGS_ZERO, 0x01000000, lbl_80150230, lbl_8015082C, lbl_80150870,
      lbl_80150890, func_800761C8 },
    { 296, FLAGS_ZERO, 0x01000000, lbl_80150230, lbl_8015082C, lbl_80150870,
      lbl_80150890, func_800761C8 },
    { 297, FLAGS_ZERO, 0x01000000, lbl_80151168, lbl_801511B0, lbl_801511F4,
      lbl_801511F8, func_800761C8 },
    { 298, FLAGS_ZERO, 0x01000000, lbl_801515B8, lbl_801517B0, lbl_801517F4,
      lbl_80151824, func_800761C8 },
    { 299, FLAGS_ZERO, 0x01000000, lbl_801516B4, lbl_801517B0, lbl_801517F4,
      lbl_80151824, func_800761C8 },
    { 300, FLAGS_ZERO, 0x01000000, lbl_80151874, lbl_801518B0, lbl_801518F4,
      lbl_80151914, func_800761C8 },
    { 301, FLAGS_ZERO, 0x01000000, lbl_8015198C, lbl_80151A44, lbl_80151A88,
      lbl_80151AC4, func_800761C8 },
    { 302, FLAGS_ZERO, 0x01000000, lbl_80151B14, lbl_80151B70, lbl_80151B50,
      lbl_80151BB4, func_800761C8 },
    { 303, FLAGS_ZERO, 0x01000000, lbl_80151C04, lbl_80151C40, lbl_80151C84,
      lbl_80151CA4, func_800761C8 },
    { 304, FLAGS_ZERO, 0x01000000, lbl_80151E10, lbl_80151E4C, lbl_80151E90,
      lbl_80151EB0, func_800761C8 },
    { 305, FLAGS_ZERO, 0x01000000, lbl_80151F00, lbl_8015204C, lbl_80152090,
      lbl_801520D4, func_800761C8 },
    { 306, FLAGS_ZERO, 0x01000000, lbl_80152138, lbl_80152174, lbl_801521B8,
      lbl_801521D8, func_800761C8 },
    { 307, FLAGS_ZERO, 0x01000000, lbl_80151D20, lbl_80151D5C, lbl_80151DA0,
      lbl_80151DC0, func_800761C8 },
    { 308, FLAGS_ZERO, 0x01000000, lbl_8015223C, lbl_80152278, lbl_801522BC,
      lbl_8015236C, func_800761C8 },
    { 309, FLAGS_ZERO, 0x01000000, lbl_801523BC, lbl_80152414, lbl_80152458,
      lbl_80152478, func_800761C8 },
    { 310, FLAGS_ZERO, 0x01000000, lbl_801524C8, lbl_80152544, lbl_80152588,
      lbl_801525DC, func_800761C8 },
    { 311, FLAGS_ZERO, 0x01000000, lbl_80152634, lbl_80152670, lbl_801526B4,
      lbl_801526D4, func_800761C8 },
    { 312, FLAGS_ZERO, 0x01000000, lbl_80152738, lbl_80152774, lbl_801527B8,
      lbl_8015287C, func_800761C8 },
    { 313, FLAGS_ZERO, 0x01000000, lbl_80152928, lbl_80152A0C, lbl_80152A50,
      lbl_80152BC8, func_800761C8 },
    { 314, FLAGS_ZERO, 0x01000000, lbl_801529D0, lbl_80152A0C, lbl_80152A50,
      lbl_80152BC8, func_800761C8 },
    { 315, FLAGS_ZERO, 0x01000000, lbl_80152C34, lbl_80152C70, lbl_80152CB4,
      lbl_80152CD4, func_800761C8 },
    { 316, FLAGS_ZERO, 0x01000000, lbl_80152D44, lbl_80152DC0, lbl_80152E04,
      lbl_80152E24, func_800761C8 },
    { 317, FLAGS_ZERO, 0x01000000, lbl_80153000, lbl_8015303C, lbl_80153080,
      lbl_801530A0, func_800761C8 },
    { 318, FLAGS_ZERO, 0x01000000, lbl_80153160, lbl_80153210, lbl_80153254,
      lbl_801533C8, func_800761C8 },
    { 319, FLAGS_ZERO, 0x01000000, lbl_8015346C, lbl_80153548, lbl_8015358C,
      lbl_801535AC, func_800761C8 },
    { 320, FLAGS_ZERO, 0x01000000, lbl_8015377C, lbl_801537B8, lbl_801537FC,
      lbl_8015381C, func_800761C8 },
    { 321, FLAGS_ZERO, 0x01000000, lbl_8015386C, lbl_801538A8, lbl_801538EC,
      lbl_8015390C, func_800761C8 },
    { 322, FLAGS_ZERO, 0x01000000, lbl_801539A4, lbl_801539EC, lbl_80153A30,
      lbl_80153A60, func_800761C8 },
    { 323, FLAGS_ZERO, 0x01000000, lbl_80153AEC, lbl_80153B28, lbl_80153B6C,
      lbl_80153B8C, func_800761C8 },
    { 324, FLAGS_ZERO, 0x01000000, lbl_80153C48, lbl_80153C90, lbl_80153CD4,
      lbl_80153D28, func_800761C8 },
    { 325, FLAGS_ZERO, 0x01000000, lbl_80153F8C, lbl_80154114, lbl_80154158,
      lbl_801541C4, func_800761C8 },
    { 326, FLAGS_ZERO, 0x01000000, lbl_80154230, lbl_80154278, lbl_801542BC,
      lbl_801542DC, func_800761C8 },
    { 327, FLAGS_ZERO, 0x01000000, lbl_80154360, lbl_801543E8, lbl_8015442C,
      lbl_8015459C, func_800761C8 },
    { 328, FLAGS_ZERO, 0x01000000, lbl_80154620, lbl_80154670, lbl_801546B4,
      lbl_801546D4, func_800761C8 },
    { 329, FLAGS_ZERO, 0x01000000, lbl_801548D8, lbl_80154964, lbl_801549A8,
      lbl_80154A08, func_800761C8 },
    { 330, FLAGS_ZERO, 0x01000000, lbl_80154D78, lbl_80154DD0, lbl_80154E14,
      lbl_80154E74, func_800761C8 },
    { 331, FLAGS_ZERO, 0x01000000, lbl_80154D78, lbl_80154DD0, lbl_80154E14,
      lbl_80154E74, func_800761C8 },
    { 332, FLAGS_ZERO, 0x01000000, lbl_80154B2C, lbl_80154BB0, lbl_80154BF4,
      lbl_80154C54, func_800761C8 },
    { 333, FLAGS_ZERO, 0x01000000, lbl_80154ED8, lbl_80154FAC, lbl_80154FF0,
      lbl_80155010, func_800761C8 },
    { 334, FLAGS_ZERO, 0x01000000, lbl_80155074, lbl_8015512C, lbl_80155170,
      lbl_80155190, func_800761C8 },
    { 335, FLAGS_ZERO, 0x01000000, lbl_80154758, lbl_80154794, lbl_801547D8,
      lbl_80154838, func_800761C8 },
    { 336, FLAGS_ZERO, 0x01000000, lbl_8015521C, lbl_80155290, lbl_801552D4,
      lbl_801552F4, func_800761C8 },
    { 337, FLAGS_ZERO, 0x01000000, lbl_80155388, lbl_8015541C, lbl_80155460,
      lbl_80155480, func_800761C8 },
    { 338, FLAGS_ZERO, 0x01000000, lbl_8015550C, lbl_80155580, lbl_801555C4,
      lbl_801555E4, func_800761C8 },
    { 339, FLAGS_ZERO, 0x01000000, lbl_801555E8, lbl_8015565C, lbl_801556A0,
      lbl_801556C0, func_800761C8 },
    { 340, FLAGS_ZERO, 0x01000000, lbl_801556C4, lbl_801557B0, lbl_801557F4,
      lbl_80155814, func_800761C8 },
    { 341, FLAGS_ZERO, 0x01000000, lbl_80155864, lbl_801558A0, lbl_801558E4,
      lbl_80155904, func_800761C8 },
    { 342, FLAGS_ZERO, 0x01000000, lbl_80155908, lbl_80155990, lbl_801559D4,
      lbl_80155A34, func_800761C8 },
    { 343, FLAGS_ZERO, 0x01000000, lbl_80150F00, NULL, lbl_80150F68,
      lbl_80150FC8, func_800761C8 },
    { 344, FLAGS_ZERO, 0x01000000, lbl_80150F00, NULL, lbl_80150F68,
      lbl_80150FC8, func_800761C8 },
};
