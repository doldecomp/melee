.global test
test:
stwu r1, -0x50(r1)
mflr r0
stw r0, 0x54(r1)
stfd f31, 0x40(r1)
psq_st f31, 0x48(r1), 0, qr0
stfd f30, 0x30(r1)
psq_st f30, 0x38(r1), 0, qr0
stfd f29, 0x20(r1)
psq_st f29, 0x28(r1), 0, qr0
stmw r27, 0xc(r1)

lfs f1, x@sda21(r2)

psq_l f31, 0x48(r1), 0, qr0
lfd f31, 0x40(r1)
psq_l f30, 0x38(r1), 0, qr0
lfd f30, 0x30(r1)
psq_l f29, 0x28(r1), 0, qr0
lfd f29, 0x20(r1)
lmw r27, 0xc(r1)
lwz r0, 0x54(r1)
mtlr r0
addi r1, r1, 0x50
blr
