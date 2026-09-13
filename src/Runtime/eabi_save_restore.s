.include "macros.inc"

.section .text, "ax"

.macro save_gpr reg, offset
.global _savegpr_\reg
_savegpr_\reg:
    stw r\reg, \offset(r11)
.endm

.macro restore_gpr reg, offset
.global _restgpr_\reg
_restgpr_\reg:
    lwz r\reg, \offset(r11)
.endm

.macro save_fpr reg, offset
.global _savefpr_\reg
_savefpr_\reg:
    stfd f\reg, \offset(r11)
.endm

.macro restore_fpr reg, offset
.global _restfpr_\reg
_restfpr_\reg:
    lfd f\reg, \offset(r11)
.endm

save_gpr 14, -72
save_gpr 15, -68
save_gpr 16, -64
save_gpr 17, -60
save_gpr 18, -56
save_gpr 19, -52
save_gpr 20, -48
save_gpr 21, -44
save_gpr 22, -40
save_gpr 23, -36
save_gpr 24, -32
save_gpr 25, -28
save_gpr 26, -24
save_gpr 27, -20
save_gpr 28, -16
save_gpr 29, -12
save_gpr 30, -8
save_gpr 31, -4
blr

restore_gpr 14, -72
restore_gpr 15, -68
restore_gpr 16, -64
restore_gpr 17, -60
restore_gpr 18, -56
restore_gpr 19, -52
restore_gpr 20, -48
restore_gpr 21, -44
restore_gpr 22, -40
restore_gpr 23, -36
restore_gpr 24, -32
restore_gpr 25, -28
restore_gpr 26, -24
restore_gpr 27, -20
restore_gpr 28, -16
restore_gpr 29, -12
restore_gpr 30, -8
restore_gpr 31, -4
blr

save_fpr 14, -144
save_fpr 15, -136
save_fpr 16, -128
save_fpr 17, -120
save_fpr 18, -112
save_fpr 19, -104
save_fpr 20, -96
save_fpr 21, -88
save_fpr 22, -80
save_fpr 23, -72
save_fpr 24, -64
save_fpr 25, -56
save_fpr 26, -48
save_fpr 27, -40
save_fpr 28, -32
save_fpr 29, -24
save_fpr 30, -16
save_fpr 31, -8
blr

restore_fpr 14, -144
restore_fpr 15, -136
restore_fpr 16, -128
restore_fpr 17, -120
restore_fpr 18, -112
restore_fpr 19, -104
restore_fpr 20, -96
restore_fpr 21, -88
restore_fpr 22, -80
restore_fpr 23, -72
restore_fpr 24, -64
restore_fpr 25, -56
restore_fpr 26, -48
restore_fpr 27, -40
restore_fpr 28, -32
restore_fpr 29, -24
restore_fpr 30, -16
restore_fpr 31, -8
blr
