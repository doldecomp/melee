#include <melee/ft/chara/ftMario/ftmario.h>
#include <melee/ft/chara/ftMario/ftMario_SpecialN.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/types.h>
#include <Runtime/platform.h>

ActionState as_table_mario[] = {
    { 0xFFFFFFFF, FLAGS_ZERO, 0x01000000, NULL, NULL, NULL, NULL, NULL },
    { 0xFFFFFFFF, FLAGS_ZERO, 0x01000000, NULL, NULL, NULL, NULL, NULL },
    { 0x00000127, 0x00340111, 0x12000000, ftMario_SpecialN_Anim,
      ftMario_SpecialN_IASA, ftMario_SpecialN_Phys, ftMario_SpecialN_Coll,
      func_800761C8 },
    { 0x00000128, 0x00340511, 0x12000000, ftMario_SpecialAirN_Anim,
      ftMario_SpecialAirN_IASA, ftMario_SpecialAirN_Phys,
      ftMario_SpecialAirN_Coll, func_800761C8 },
    { 0x00000129, 0x00341012, 0x13000000, ftMario_SpecialS_Anim,
      ftMario_SpecialS_IASA, ftMario_SpecialS_Phys, ftMario_SpecialS_Coll,
      func_800761C8 },
    { 0x0000012A, 0x00341012, 0x13000000, ftMario_SpecialAirS_Anim,
      ftMario_SpecialAirS_IASA, ftMario_SpecialAirS_Phys,
      ftMario_SpecialAirS_Coll, func_800761C8 },
    { 0x0000012B, 0x00340213, 0x14000000, ftMario_SpecialHi_Anim,
      ftMario_SpecialHi_IASA, ftMario_SpecialHi_Phys, ftMario_SpecialHi_Coll,
      func_800761C8 },
    { 0x0000012C, 0x00340613, 0x14000000, ftMario_SpecialAirHi_Anim,
      ftMario_SpecialAirHi_IASA, ftMario_SpecialAirHi_Phys,
      ftMario_SpecialAirHi_Coll, func_800761C8 },
    { 0x0000012D, 0x00340214, 0x15000000, ftMario_SpecialLw_Anim,
      ftMario_SpecialLw_IASA, ftMario_SpecialLw_Phys, ftMario_SpecialLw_Coll,
      func_800761C8 },
    { 0x0000012E, 0x00340614, 0x15000000, ftMario_SpecialAirLw_Anim,
      ftMario_SpecialAirLw_IASA, ftMario_SpecialAirLw_Phys,
      ftMario_SpecialAirLw_Coll, func_800761C8 },
};
