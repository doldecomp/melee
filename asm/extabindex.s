.section extabindex_, "wa"  # 0x800056C0 - 0x80005940

	.incbin "baserom.dol", 0x3B3FC0, 0x258
.global lbl_80005918
lbl_80005918:
	.incbin "baserom.dol", 0x3B4218, 0x28
