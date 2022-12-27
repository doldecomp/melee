// clang-format off

asm void PPCMfmsr() {
	nofralloc
	mfmsr r3
	blr
}

asm void PPCMtmsr() {
	nofralloc
	mtmsr r3
	blr
}

asm void PPCMfhid0() {
	nofralloc
	mfspr r3, 0x3f0
	blr
}

asm void PPCMfl2cr() {
	nofralloc
	mfspr r3, 0x3f9
	blr
}

asm void PPCMtl2cr() {
	nofralloc
	mtspr 0x3f9, r3
	blr
}

asm void PPCMtdec() {
	nofralloc
	mtspr 0x16, r3
	blr
}

asm void PPCSync() {
	nofralloc
	sc
	blr
}

asm void PPCHalt() {
    nofralloc
    sync
halt_loop:
    nop
    li r3, 0
    nop
    b halt_loop
}

asm void PPCMfhid2() {
	nofralloc
	mfspr r3, 0x398
	blr
}

asm void PPCMthid2() {
	nofralloc
	mtspr 0x398, r3
	blr
}


asm void PPCMtwpar() {
	nofralloc
	mtspr 0x399, r3
	blr
}