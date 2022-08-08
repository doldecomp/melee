.section .data
    .balign 8

struct_803BB0B0:
    .asciz "?"
    .balign 4
    .4byte NULL
    .4byte NULL
    .4byte 0x3F000000
    .4byte NULL
    .4byte 0xBF000000
    .4byte NULL
    .4byte 0x3F000000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x3F800000

struct_803BB0E0:
    .4byte 0xBF000000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0xBF000000
    .4byte NULL

struct_803BB0F8:
    .4byte NULL
    .4byte NULL
    .4byte 0x00000004
    .4byte NULL
    .4byte NULL
    .4byte NULL

struct_803BB110:
    .4byte 0x00000001
    .4byte NULL
    .4byte 0x01010000
    .4byte NULL

struct_803BB120:
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x3F800000
    .4byte 0x3F800000
    .4byte 0x3F800000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x01010000
    .4byte 0x00000083
    .4byte 0x3F800000
    .4byte 0x00000001
    .4byte struct_803BB0F8
    .4byte NULL
    .4byte struct_803BB110
    .4byte NULL

struct_803BB17C:
    .4byte NULL
    .4byte NULL
    .4byte 0x00000003
    .4byte NULL
    .4byte NULL
    .4byte NULL

struct_803BB194:
    .4byte 0x00000001
    .4byte NULL
    .4byte 0x01010000
    .4byte NULL
    .4byte NULL
    .4byte struct_803BB120
    .4byte 0x00000001
    .4byte 0x00000001
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x3F800000
    .4byte 0x3F800000
    .4byte 0x3F800000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x01010000
    .4byte 0x00000081
    .4byte 0x3F800000
    .4byte 0x00000001
    .4byte struct_803BB17C
    .4byte NULL
    .4byte struct_803BB194
    .4byte NULL
    .asciz "LbRf.dat"
    .balign 4
    .asciz "lbRefData"
    .balign 4
    .4byte local_80022650
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte local_80022940
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .asciz "refract_class_library"
    .balign 4
    .asciz "refract_dobj"
    .balign 4
    .asciz "refract_pobj"
    .balign 4

str_lbRefSetUnuse_error:
    .asciz "lbRefSetUnuse error!\n"
    .balign 4

str_lbrefract_c:
    .asciz "lbrefract.c"
    .balign 4


.section .rodata
    .balign 8

atanf_lookup:
    .4byte 0x3F800000
    .4byte 0xBEAAAAAA
    .4byte 0x3E4CCC81
    .4byte 0xBE123E7D
    .4byte 0x3DE21F95
    .4byte 0xBDAD417C
    .4byte 0x3D41186D
    .4byte 0x40DA826B
    .4byte 0x404F5958
    .4byte 0x40000000
    .4byte 0x3FB925AB
    .4byte 0x3F95F61A
    .4byte 0x3F851081
    .4byte 0x36EF692F
    .4byte 0x355C1DF9
    .4byte 0x00000000
    .4byte 0x35291D45
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x3EC90EAA
    .4byte 0x3F16CBE4
    .4byte 0x3F490FDA
    .4byte 0x3F7B53C5
    .4byte 0x3F96CBE2
    .4byte 0x3FAFEDD9
    .4byte 0x00000000
    .4byte 0x37185D99
    .4byte 0x32C59189
    .4byte 0x33874A9E
    .4byte 0x353CFA83
    .4byte 0x348637BD
    .4byte 0x35541063
    .4byte 0x401A8277
    .4byte 0x3FBF90C7
    .4byte 0x3F800000
    .4byte 0x3F2B0DC1
    .4byte 0x3ED413CD
    .4byte 0x3E4BAFAF
    .4byte 0x3516DC59
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000


.section .bss, "wa"
    .balign 8

skip40_804336D0:
	.skip 0x40


.section .sdata 
    .balign 8

str_0_804D3868:
    .asciz "0"
    .balign 4
    .4byte NULL


.section .sbss
    .balign 8

skip8_804D63E8:
	.skip 0x8


.section .sdata2
    .balign 8

lbl_804D7D70:
	.4byte 0x40000000

lbl_804D7D74:
	.4byte 0xBF800000

lbl_804D7D78:
	.4byte 0x00000000
	.4byte 0x00000000

lbl_804D7D80:
	.4byte 0x3FE00000
	.4byte 0x00000000

lbl_804D7D88:
	.4byte 0x40080000
	.4byte 0x00000000

lbl_804D7D90:
	.4byte 0x3F800000

lbl_804D7D94:
	.4byte 0x43000000

lbl_804D7D98:
	.4byte 0x42FE0000
	.4byte 0x00000000

lbl_804D7DA0:
	.4byte 0x43300000
	.4byte 0x00000000

lbl_804D7DA8:
	.4byte 0x3F000000

lbl_804D7DAC:
	.4byte 0xBF000000

lbl_804D7DB0:
	.4byte 0x80000000

lbl_804D7DB4:
	.4byte 0xBFC90FDB

lbl_804D7DB8:
	.4byte 0x40490FDB

lbl_804D7DBC:
	.4byte 0x00000000

lbl_804D7DC0:
	.4byte 0x3FC90FDB

lbl_804D7DC4:
	.4byte 0x3F800000

lbl_804D7DC8:
	.4byte 0x3F000000

lbl_804D7DCC:
	.4byte 0x40400000

lbl_804D7DD0:
	.4byte 0x401A827A

lbl_804D7DD4:
	.4byte 0x3ED413CD
