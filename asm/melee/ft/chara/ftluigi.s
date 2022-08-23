.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240


.section .data
    .balign 8
.global as_table_luigi
as_table_luigi:
    .4byte 0x00000127
    .4byte 0x00340111
    .4byte 0x12000000
    .4byte ftLuigi_SpecialN_Anim
    .4byte ftLuigi_SpecialN_IASA
    .4byte ftLuigi_SpecialN_Phys
    .4byte ftLuigi_SpecialN_Coll
    .4byte func_800761C8
    .4byte 0x00000128
    .4byte 0x00340511
    .4byte 0x12000000
    .4byte ftLuigi_SpecialAirN_Anim
    .4byte ftLuigi_SpecialAirN_IASA
    .4byte ftLuigi_SpecialAirN_Phys
    .4byte ftLuigi_SpecialAirN_Coll
    .4byte func_800761C8
    .4byte 0x00000129
    .4byte 0x00340212
    .4byte 0x13000000
    .4byte ftLuigi_SpecialSStart_Anim
    .4byte ftLuigi_SpecialSStart_IASA
    .4byte ftLuigi_SpecialSStart_Phys
    .4byte ftLuigi_SpecialSStart_Coll
    .4byte func_800761C8
    .4byte 0x0000012A
    .4byte 0x00340212
    .4byte 0x13000000
    .4byte ftLuigi_SpecialSHold_Anim
    .4byte ftLuigi_SpecialSHold_IASA
    .4byte ftLuigi_SpecialSHold_Phys
    .4byte ftLuigi_SpecialSHold_Coll
    .4byte func_800761C8
    .4byte 0x0000012D
    .4byte 0x00340212
    .4byte 0x13000000
    .4byte ftLuigi_SpecialSFly_Anim
    .4byte ftLuigi_SpecialSFly_IASA
    .4byte ftLuigi_SpecialSFly_Phys
    .4byte ftLuigi_SpecialSFly_Coll
    .4byte func_800761C8
    .4byte 0x0000012E
    .4byte 0x00340212
    .4byte 0x13000000
    .4byte ftLuigi_SpecialSEnd_Anim
    .4byte ftLuigi_SpecialSEnd_IASA
    .4byte ftLuigi_SpecialSEnd_Phys
    .4byte ftLuigi_SpecialSEnd_Coll
    .4byte func_800761C8
    .4byte 0x0000012B
    .4byte 0x00340212
    .4byte 0x13000000
    .4byte ftLuigi_SpecialSLaunch_Anim
    .4byte ftLuigi_SpecialSLaunch_IASA
    .4byte ftLuigi_SpecialSLaunch_Phys
    .4byte ftLuigi_SpecialSLaunch_Coll
    .4byte func_800761C8
    .4byte 0x0000012C
    .4byte 0x00340212
    .4byte 0x13000000
    .4byte ftLuigi_SpecialSMisfire_Anim
    .4byte ftLuigi_SpecialSMisfire_IASA
    .4byte ftLuigi_SpecialSMisfire_Phys
    .4byte ftLuigi_SpecialSMisfire_Coll
    .4byte func_800761C8
    .4byte 0x0000012F
    .4byte 0x00340612
    .4byte 0x13000000
    .4byte ftLuigi_SpecialAirSStart_Anim
    .4byte ftLuigi_SpecialAirSStart_IASA
    .4byte ftLuigi_SpecialAirSStart_Phys
    .4byte ftLuigi_SpecialAirSStart_Coll
    .4byte func_800761C8
    .4byte 0x00000130
    .4byte 0x00340612
    .4byte 0x13000000
    .4byte ftLuigi_SpecialAirSHold_Anim
    .4byte ftLuigi_SpecialAirSHold_IASA
    .4byte ftLuigi_SpecialAirSHold_Phys
    .4byte ftLuigi_SpecialAirSHold_Coll
    .4byte func_800761C8
    .4byte 0x0000012D
    .4byte 0x00340612
    .4byte 0x13000000
    .4byte ftLuigi_SpecialAirSFly_Anim
    .4byte ftLuigi_SpecialAirSFly_IASA
    .4byte ftLuigi_SpecialAirSFly_Phys
    .4byte ftLuigi_SpecialAirSFly_Coll
    .4byte func_800761C8
    .4byte 0x00000133
    .4byte 0x00340612
    .4byte 0x13000000
    .4byte ftLuigi_SpecialAirSEnd_Anim
    .4byte ftLuigi_SpecialAirSEnd_IASA
    .4byte ftLuigi_SpecialAirSEnd_Phys
    .4byte ftLuigi_SpecialAirSEnd_Coll
    .4byte func_800761C8
    .4byte 0x00000131
    .4byte 0x00340612
    .4byte 0x13000000
    .4byte ftLuigi_SpecialAirSLaunch_Anim
    .4byte ftLuigi_SpecialAirSLaunch_IASA
    .4byte ftLuigi_SpecialAirSLaunch_Phys
    .4byte ftLuigi_SpecialAirSLaunch_Coll
    .4byte func_800761C8
    .4byte 0x00000132
    .4byte 0x00340612
    .4byte 0x13000000
    .4byte ftLuigi_SpecialAirSMisfire_Anim
    .4byte ftLuigi_SpecialAirSMisfire_IASA
    .4byte ftLuigi_SpecialAirSMisfire_Phys
    .4byte ftLuigi_SpecialAirSMisfire_Coll
    .4byte func_800761C8
    .4byte 0x00000134
    .4byte 0x00340213
    .4byte 0x14000000
    .4byte ftLuigi_SpecialHi_Anim
    .4byte ftLuigi_SpecialHi_IASA
    .4byte ftLuigi_SpecialHi_Phys
    .4byte ftLuigi_SpecialHi_Coll
    .4byte func_800761C8
    .4byte 0x00000135
    .4byte 0x00340613
    .4byte 0x14000000
    .4byte ftLuigi_SpecialAirHi_Anim
    .4byte ftLuigi_SpecialAirHi_IASA
    .4byte ftLuigi_SpecialAirHi_Phys
    .4byte ftLuigi_SpecialAirHi_Coll
    .4byte func_800761C8
    .4byte 0x00000136
    .4byte 0x00340214
    .4byte 0x15000000
    .4byte ftLuigi_SpecialLw_Anim
    .4byte ftLuigi_SpecialLw_IASA
    .4byte ftLuigi_SpecialLw_Phys
    .4byte ftLuigi_SpecialLw_Coll
    .4byte func_800761C8
    .4byte 0x00000137
    .4byte 0x00340614
    .4byte 0x15000000
    .4byte ftLuigi_SpecialAirLw_Anim
    .4byte ftLuigi_SpecialAirLw_IASA
    .4byte ftLuigi_SpecialAirLw_Phys
    .4byte ftLuigi_SpecialAirLw_Coll
    .4byte func_800761C8
.global lbl_803D0868
lbl_803D0868:
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
.global lbl_803D08A8
lbl_803D08A8:
    .asciz "PlLg.dat"
    .balign 4
.global lbl_803D08B4
lbl_803D08B4:
    .asciz "ftDataLuigi"
    .balign 4
.global lbl_803D08C0
lbl_803D08C0:
    .asciz "PlLgNr.dat"
    .balign 4
.global lbl_803D08CC
lbl_803D08CC:
    .asciz "PlyLuigi5K_Share_joint"
    .balign 4
.global lbl_803D08E4
lbl_803D08E4:
    .asciz "PlyLuigi5K_Share_matanim_joint"
    .balign 4
.global lbl_803D0904
lbl_803D0904:
    .asciz "PlLgWh.dat"
    .balign 4
.global lbl_803D0910
lbl_803D0910:
    .asciz "PlyLuigi5KWh_Share_joint"
    .balign 4
.global lbl_803D092C
lbl_803D092C:
    .asciz "PlyLuigi5KWh_Share_matanim_joint"
    .balign 4
.global lbl_803D0950
lbl_803D0950:
    .asciz "PlLgAq.dat"
    .balign 4
.global lbl_803D095C
lbl_803D095C:
    .asciz "PlyLuigi5KAq_Share_joint"
    .balign 4
.global lbl_803D0978
lbl_803D0978:
    .asciz "PlyLuigi5KAq_Share_matanim_joint"
    .balign 4
.global lbl_803D099C
lbl_803D099C:
    .asciz "PlLgPi.dat"
    .balign 4
.global lbl_803D09A8
lbl_803D09A8:
    .asciz "PlyLuigi5KPi_Share_joint"
    .balign 4
.global lbl_803D09C4
lbl_803D09C4:
    .asciz "PlyLuigi5KPi_Share_matanim_joint"
    .balign 4
.global lbl_803D09E8
lbl_803D09E8:
    .asciz "PlLgAJ.dat"
    .balign 4
.global lbl_803D09F4
lbl_803D09F4:
    .asciz "ftDemoResultMotionFileLuigi"
    .balign 4
.global lbl_803D0A10
lbl_803D0A10:
    .asciz "ftDemoIntroMotionFileLuigi"
    .balign 4
.global lbl_803D0A2C
lbl_803D0A2C:
    .asciz "ftDemoEndingMotionFileLuigi"
    .balign 4
.global lbl_803D0A48
lbl_803D0A48:
    .asciz "ftDemoViWaitMotionFileLuigi"
    .balign 4
.global lbl_803D0A64
lbl_803D0A64:
    .4byte lbl_803D09F4
    .4byte lbl_803D0A10
    .4byte lbl_803D0A2C
    .4byte lbl_803D0A48
.global lbl_803D0A74
lbl_803D0A74:
    .asciz "ftDemoVi0102MotionFileLuigi"
    .balign 4
.global lbl_803D0A90
lbl_803D0A90:
    .asciz "ftDemoVi1101MotionFileLuigi"
    .balign 4
.global lbl_803D0AAC
lbl_803D0AAC:
    .4byte lbl_803D0A74
    .4byte lbl_803D0A90
.global lbl_803D0AB4
lbl_803D0AB4:
    .4byte lbl_803D08C0
    .4byte lbl_803D08CC
    .4byte lbl_803D08E4
    .4byte lbl_803D0904
    .4byte lbl_803D0910
    .4byte lbl_803D092C
    .4byte lbl_803D0950
    .4byte lbl_803D095C
    .4byte lbl_803D0978
    .4byte lbl_803D099C
    .4byte lbl_803D09A8
    .4byte lbl_803D09C4
    .4byte NULL
.global lbl_803D0AE8
lbl_803D0AE8:
    .4byte 0x41400000
    .4byte NULL
    .4byte 0xC0C00000
    .4byte 0x40C00000
    .4byte 0x40C00000
    .4byte 0x40C00000
