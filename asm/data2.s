.section .data2, "wa"  # 0x803B7240 - 0x803B7260

.global lbl_803B7240
lbl_803B7240:
	.incbin "baserom.dol", 0x3B4240, 0x20
