#include <melee/ft/chara/ftMario/ftmario.h>
#include <melee/ft/chara/ftMario/ftMario_SpecialN.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/types.h>
#include <Runtime/platform.h>

ActionState as_table_mario[] = {
    { 0xFFFFFFFF, FLAGS_ZERO, 0x01000000, NULL, NULL, NULL, NULL, NULL },
    { 0xFFFFFFFF, FLAGS_ZERO, 0x01000000, NULL, NULL, NULL, NULL, NULL },
    { 295, 0x00340111, 0x12000000, ftMario_SpecialN_Anim, ftMario_SpecialN_IASA,
      ftMario_SpecialN_Phys, ftMario_SpecialN_Coll, func_800761C8 },
    { 296, 0x00340511, 0x12000000, ftMario_SpecialAirN_Anim,
      ftMario_SpecialAirN_IASA, ftMario_SpecialAirN_Phys,
      ftMario_SpecialAirN_Coll, func_800761C8 },
    { 297, 0x00341012, 0x13000000, ftMario_SpecialS_Anim, ftMario_SpecialS_IASA,
      ftMario_SpecialS_Phys, ftMario_SpecialS_Coll, func_800761C8 },
    { 298, 0x00341012, 0x13000000, ftMario_SpecialAirS_Anim,
      ftMario_SpecialAirS_IASA, ftMario_SpecialAirS_Phys,
      ftMario_SpecialAirS_Coll, func_800761C8 },
    { 299, 0x00340213, 0x14000000, ftMario_SpecialHi_Anim,
      ftMario_SpecialHi_IASA, ftMario_SpecialHi_Phys, ftMario_SpecialHi_Coll,
      func_800761C8 },
    { 300, 0x00340613, 0x14000000, ftMario_SpecialAirHi_Anim,
      ftMario_SpecialAirHi_IASA, ftMario_SpecialAirHi_Phys,
      ftMario_SpecialAirHi_Coll, func_800761C8 },
    { 301, 0x00340214, 0x15000000, ftMario_SpecialLw_Anim,
      ftMario_SpecialLw_IASA, ftMario_SpecialLw_Phys, ftMario_SpecialLw_Coll,
      func_800761C8 },
    { 302, 0x00340614, 0x15000000, ftMario_SpecialAirLw_Anim,
      ftMario_SpecialAirLw_IASA, ftMario_SpecialAirLw_Phys,
      ftMario_SpecialAirLw_Coll, func_800761C8 },
};

ActionState lbl_803C7260[] = {
    { 14, FLAGS_ZERO, 0x01000000, NULL, NULL, func_800C7158, NULL, NULL },
    { 15, FLAGS_ZERO, 0x01000000, NULL, NULL, func_800C7200, NULL, NULL },
};
