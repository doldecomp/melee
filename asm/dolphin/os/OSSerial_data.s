.include "macros.inc"

.section .data
    .balign 8
.global lbl_80402358
lbl_80402358:
    .4byte 0xFFFFFFFF
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
.global lbl_8040236C
lbl_8040236C:
    .4byte 0x00000008
    .4byte 0x00000008
    .4byte 0x00000008
    .4byte 0x00000008
    .4byte 0x4E6F2072
    .4byte 0x6573706F
    .4byte 0x6E736500
    .4byte 0x4E363420
    .4byte 0x636F6E74
    .4byte 0x726F6C6C
    .4byte 0x65720000
    .4byte 0x4E363420
    .4byte 0x6D696372
    .4byte 0x6F70686F
    .4byte 0x6E650000
    .4byte 0x4E363420
    .4byte 0x6B657962
    .4byte 0x6F617264
    .4byte NULL
    .4byte 0x4E363420
    .4byte 0x6D6F7573
    .4byte 0x65000000
    .4byte 0x47616D65
    .4byte 0x426F7920
    .4byte 0x41647661
    .4byte 0x6E636500
    .4byte 0x5374616E
    .4byte 0x64617264
    .4byte 0x20636F6E
    .4byte 0x74726F6C
    .4byte 0x6C657200
    .4byte 0x57697265
    .4byte 0x6C657373
    .4byte 0x20726563
    .4byte 0x65697665
    .4byte 0x72000000
    .4byte 0x57617665
    .4byte 0x42697264
    .4byte 0x20636F6E
    .4byte 0x74726F6C
    .4byte 0x6C657200
    .4byte 0x4B657962
    .4byte 0x6F617264
    .4byte NULL
    .4byte NULL

.section .bss, "wa"
    .balign 8
.global Packet
Packet:
    .skip 0x80
.global Alarm
Alarm:
    .skip 0xA0
.global lbl_804A7ED8
lbl_804A7ED8:
    .skip 0x20
.global lbl_804A7EF8
lbl_804A7EF8:
    .skip 0x20
.global lbl_804A7F18
lbl_804A7F18:
    .skip 0x40
.global lbl_804A7F58
lbl_804A7F58:
    .skip 0x60

.section .sbss
    .balign 8
.global lbl_804D73C8
lbl_804D73C8:
    .skip 0x4
.global lbl_804D73CC
lbl_804D73CC:
    .skip 0x4
.global __PADFixBits
__PADFixBits:
    .skip 0x8
