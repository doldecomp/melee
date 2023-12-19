/*
Code sections:
    .text0: 0x00000100  0x80003100  0x80005520
    .text1: 0x00002520  0x80005940  0x803B7240
Data sections:
    .data0: 0x003B3E20  0x80005520  0x800056C0
    .data1: 0x003B3FC0  0x800056C0  0x80005940
    .data2: 0x003B4240  0x803B7240  0x803B7260
    .data3: 0x003B4260  0x803B7260  0x803B7280
    .data4: 0x003B4280  0x803B7280  0x803B9840
    .data5: 0x003B6840  0x803B9840  0x804316C0
    .data6: 0x0042E6C0  0x804D36A0  0x804D63A0
    .data7: 0x004313C0  0x804D79E0  0x804DEC00
BSS section:
    .bss:   0x00000000  0x804316C0  0x804D79C9
Entry Point: 0x8000522C
*/
# PowerPC Register Constants
.set r0, 0
.set r1, 1
.set r2, 2
.set r3, 3
.set r4, 4
.set r5, 5
.set r6, 6
.set r7, 7
.set r8, 8
.set r9, 9
.set r10, 10
.set r11, 11
.set r12, 12
.set r13, 13
.set r14, 14
.set r15, 15
.set r16, 16
.set r17, 17
.set r18, 18
.set r19, 19
.set r20, 20
.set r21, 21
.set r22, 22
.set r23, 23
.set r24, 24
.set r25, 25
.set r26, 26
.set r27, 27
.set r28, 28
.set r29, 29
.set r30, 30
.set r31, 31
.set f0, 0
.set f1, 1
.set f2, 2
.set f3, 3
.set f4, 4
.set f5, 5
.set f6, 6
.set f7, 7
.set f8, 8
.set f9, 9
.set f10, 10
.set f11, 11
.set f12, 12
.set f13, 13
.set f14, 14
.set f15, 15
.set f16, 16
.set f17, 17
.set f18, 18
.set f19, 19
.set f20, 20
.set f21, 21
.set f22, 22
.set f23, 23
.set f24, 24
.set f25, 25
.set f26, 26
.set f27, 27
.set f28, 28
.set f29, 29
.set f30, 30
.set f31, 31
.set qr0, 0
.set qr1, 1
.set qr2, 2
.set qr3, 3
.set qr4, 4
.set qr5, 5
.set qr6, 6
.set qr7, 7

.set NULL, 0
.set U32_TO_F32, 0x4330000000000000
.set S32_TO_F32, 0x4330000080000000
.set U8_MAX, 0xFF
.set U16_MAX, 0xFFFF
.set U32_MAX, 0xFFFFFFFF
.set S8_MAX, 0x7F
.set S16_MAX, 0x7FFF
.set S32_MAX, 0x7FFFFFFF
.set F32_MAX, 0x7F7FFFFF
