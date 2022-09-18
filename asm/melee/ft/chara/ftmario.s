.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.section .data
    .balign 8
.global as_table_mario
as_table_mario:
    .4byte 0xFFFFFFFF
    .4byte NULL
    .4byte 0x01000000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0xFFFFFFFF
    .4byte NULL
    .4byte 0x01000000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x00000127
    .4byte 0x00340111
    .4byte 0x12000000
    .4byte ftMario_SpecialN_Anim
    .4byte ftMario_SpecialN_IASA
    .4byte ftMario_SpecialN_Phys
    .4byte ftMario_SpecialN_Coll
    .4byte func_800761C8
    .4byte 0x00000128
    .4byte 0x00340511
    .4byte 0x12000000
    .4byte ftMario_SpecialAirN_Anim
    .4byte ftMario_SpecialAirN_IASA
    .4byte ftMario_SpecialAirN_Phys
    .4byte ftMario_SpecialAirN_Coll
    .4byte func_800761C8
    .4byte 0x00000129
    .4byte 0x00341012
    .4byte 0x13000000
    .4byte ftMario_SpecialS_Anim
    .4byte ftMario_SpecialS_IASA
    .4byte ftMario_SpecialS_Phys
    .4byte ftMario_SpecialS_Coll
    .4byte func_800761C8
    .4byte 0x0000012A
    .4byte 0x00341012
    .4byte 0x13000000
    .4byte ftMario_SpecialAirS_Anim
    .4byte ftMario_SpecialAirS_IASA
    .4byte ftMario_SpecialAirS_Phys
    .4byte ftMario_SpecialAirS_Coll
    .4byte func_800761C8
    .4byte 0x0000012B
    .4byte 0x00340213
    .4byte 0x14000000
    .4byte ftMario_SpecialHi_Anim
    .4byte ftMario_SpecialHi_IASA
    .4byte ftMario_SpecialHi_Phys
    .4byte ftMario_SpecialHi_Coll
    .4byte func_800761C8
    .4byte 0x0000012C
    .4byte 0x00340613
    .4byte 0x14000000
    .4byte ftMario_SpecialAirHi_Anim
    .4byte ftMario_SpecialAirHi_IASA
    .4byte ftMario_SpecialAirHi_Phys
    .4byte ftMario_SpecialAirHi_Coll
    .4byte func_800761C8
    .4byte 0x0000012D
    .4byte 0x00340214
    .4byte 0x15000000
    .4byte ftMario_SpecialLw_Anim
    .4byte ftMario_SpecialLw_IASA
    .4byte ftMario_SpecialLw_Phys
    .4byte ftMario_SpecialLw_Coll
    .4byte func_800761C8
    .4byte 0x0000012E
    .4byte 0x00340614
    .4byte 0x15000000
    .4byte ftMario_SpecialAirLw_Anim
    .4byte ftMario_SpecialAirLw_IASA
    .4byte ftMario_SpecialAirLw_Phys
    .4byte ftMario_SpecialAirLw_Coll
    .4byte func_800761C8
.global lbl_803C7260
lbl_803C7260:
    .4byte 0x0000000E
    .4byte NULL
    .4byte 0x01000000
    .4byte NULL
    .4byte NULL
    .4byte func_800C7158
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000F
    .4byte NULL
    .4byte 0x01000000
    .4byte NULL
    .4byte NULL
    .4byte func_800C7200
    .4byte NULL
    .4byte NULL

