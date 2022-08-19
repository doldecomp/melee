.include "macros.inc"

.section .data

.set lbl_8033DFF0, GXInitLightSpot + 0x60 + 0xF0
.set lbl_8033DF10, GXInitLightSpot + 0x60 + 0x10
.set lbl_8033DF24, GXInitLightSpot + 0x60 + 0x24
.set lbl_8033DF40, GXInitLightSpot + 0x60 + 0x40
.set lbl_8033DF5C, GXInitLightSpot + 0x60 + 0x5C
.set lbl_8033DF88, GXInitLightSpot + 0x60 + 0x88
.set lbl_8033DFB8, GXInitLightSpot + 0x60 + 0xB8

.global jtbl_80401298
jtbl_80401298:
	.4byte lbl_8033DFF0
	.4byte lbl_8033DF10
	.4byte lbl_8033DF24
	.4byte lbl_8033DF40
	.4byte lbl_8033DF5C
	.4byte lbl_8033DF88
	.4byte lbl_8033DFB8
    .4byte NULL

.section .sdata2

.global lbl_804DE230
lbl_804DE230:
	.float 0.0

.global lbl_804DE234
lbl_804DE234:
	.float 90.0

.global lbl_804DE238
lbl_804DE238:
	.float 3.1415927410125732

.global lbl_804DE23C
lbl_804DE23C:
	.float 180.0

.global lbl_804DE240
lbl_804DE240:
	.float -1000.0

.global lbl_804DE244
lbl_804DE244:
	.float 1000.0

.global lbl_804DE248
lbl_804DE248:
	.float 1.0

.global lbl_804DE24C
lbl_804DE24C:
	.float 2.0

.global lbl_804DE250
lbl_804DE250:
	.float -1.0

.global lbl_804DE254
lbl_804DE254:
	.float -4.0

.global lbl_804DE258
lbl_804DE258:
	.float 4.0

.global lbl_804DE25C
lbl_804DE25C:
	.float -2.0

.global lbl_804DE260
lbl_804DE260:
	.double 3.0517578125e-05
