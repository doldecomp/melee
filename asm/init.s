.include "macros.inc"

.section .init  # 0x80003100 - 0x80005520

.global gTRKInterruptVectorTable
gTRKInterruptVectorTable:
    .asciz "Metrowerks Target Resident Kernel for PowerPC"
    .balign 4
/* 800032C8 000002C8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800032CC 000002CC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800032D0 000002D0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800032D4 000002D4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800032D8 000002D8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800032DC 000002DC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800032E0 000002E0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800032E4 000002E4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800032E8 000002E8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800032EC 000002EC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800032F0 000002F0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800032F4 000002F4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800032F8 000002F8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800032FC 000002FC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003300 00000300  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003304 00000304  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003308 00000308  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000330C 0000030C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003310 00000310  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003314 00000314  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003318 00000318  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000331C 0000031C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003320 00000320  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003324 00000324  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003328 00000328  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000332C 0000032C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003330 00000330  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003334 00000334  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003338 00000338  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000333C 0000033C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003340 00000340  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003344 00000344  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003348 00000348  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000334C 0000034C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003350 00000350  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003354 00000354  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003358 00000358  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000335C 0000035C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003360 00000360  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003364 00000364  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003368 00000368  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000336C 0000036C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003370 00000370  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003374 00000374  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003378 00000378  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000337C 0000037C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003380 00000380  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003384 00000384  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003388 00000388  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000338C 0000038C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003390 00000390  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003394 00000394  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003398 00000398  48 00 1E 34 */	b gTRKInterruptVectorTableEnd
/* 8000339C 0000039C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800033A0 000003A0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800033A4 000003A4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800033A8 000003A8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800033AC 000003AC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800033B0 000003B0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800033B4 000003B4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800033B8 000003B8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800033BC 000003BC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800033C0 000003C0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800033C4 000003C4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800033C8 000003C8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800033CC 000003CC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800033D0 000003D0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800033D4 000003D4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800033D8 000003D8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800033DC 000003DC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800033E0 000003E0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800033E4 000003E4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800033E8 000003E8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800033EC 000003EC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800033F0 000003F0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800033F4 000003F4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800033F8 000003F8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800033FC 000003FC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003400 00000400  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003404 00000404  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003408 00000408  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000340C 0000040C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003410 00000410  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003414 00000414  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003418 00000418  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000341C 0000041C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003420 00000420  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003424 00000424  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003428 00000428  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000342C 0000042C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003430 00000430  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003434 00000434  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003438 00000438  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000343C 0000043C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003440 00000440  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003444 00000444  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003448 00000448  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000344C 0000044C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003450 00000450  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003454 00000454  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003458 00000458  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000345C 0000045C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003460 00000460  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003464 00000464  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003468 00000468  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000346C 0000046C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003470 00000470  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003474 00000474  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003478 00000478  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000347C 0000047C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003480 00000480  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003484 00000484  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003488 00000488  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000348C 0000048C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003490 00000490  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003494 00000494  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003498 00000498  7C 51 43 A6 */	mtspr 0x111, r2
/* 8000349C 0000049C  7C 5A 02 A6 */	mfspr r2, 0x1a
/* 800034A0 000004A0  7C 00 17 AC */	icbi 0, r2
/* 800034A4 000004A4  7C 53 02 A6 */	mfdar r2
/* 800034A8 000004A8  7C 00 13 AC */	dcbi 0, r2
/* 800034AC 000004AC  7C 51 42 A6 */	mfspr r2, 0x111
/* 800034B0 000004B0  7C 51 43 A6 */	mtspr 0x111, r2
/* 800034B4 000004B4  7C 72 43 A6 */	mtspr 0x112, r3
/* 800034B8 000004B8  7C 93 43 A6 */	mtspr 0x113, r4
/* 800034BC 000004BC  7C 5A 02 A6 */	mfspr r2, 0x1a
/* 800034C0 000004C0  7C 9B 02 A6 */	mfspr r4, 0x1b
/* 800034C4 000004C4  7C 60 00 A6 */	mfmsr r3
/* 800034C8 000004C8  60 63 00 30 */	ori r3, r3, 0x30
/* 800034CC 000004CC  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 800034D0 000004D0  3C 60 80 32 */	lis r3, TRKInterruptHandler@h
/* 800034D4 000004D4  60 63 99 EC */	ori r3, r3, TRKInterruptHandler@l
/* 800034D8 000004D8  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 800034DC 000004DC  38 60 02 00 */	li r3, 0x200
/* 800034E0 000004E0  4C 00 00 64 */	rfi
/* 800034E4 000004E4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800034E8 000004E8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800034EC 000004EC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800034F0 000004F0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800034F4 000004F4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800034F8 000004F8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800034FC 000004FC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003500 00000500  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003504 00000504  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003508 00000508  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000350C 0000050C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003510 00000510  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003514 00000514  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003518 00000518  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000351C 0000051C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003520 00000520  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003524 00000524  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003528 00000528  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000352C 0000052C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003530 00000530  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003534 00000534  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003538 00000538  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000353C 0000053C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003540 00000540  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003544 00000544  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003548 00000548  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000354C 0000054C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003550 00000550  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003554 00000554  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003558 00000558  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000355C 0000055C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003560 00000560  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003564 00000564  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003568 00000568  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000356C 0000056C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003570 00000570  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003574 00000574  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003578 00000578  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000357C 0000057C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003580 00000580  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003584 00000584  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003588 00000588  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000358C 0000058C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003590 00000590  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003594 00000594  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003598 00000598  7C 51 43 A6 */	mtspr 0x111, r2
/* 8000359C 0000059C  7C 72 43 A6 */	mtspr 0x112, r3
/* 800035A0 000005A0  7C 93 43 A6 */	mtspr 0x113, r4
/* 800035A4 000005A4  7C 5A 02 A6 */	mfspr r2, 0x1a
/* 800035A8 000005A8  7C 9B 02 A6 */	mfspr r4, 0x1b
/* 800035AC 000005AC  7C 60 00 A6 */	mfmsr r3
/* 800035B0 000005B0  60 63 00 30 */	ori r3, r3, 0x30
/* 800035B4 000005B4  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 800035B8 000005B8  3C 60 80 32 */	lis r3, TRKInterruptHandler@h
/* 800035BC 000005BC  60 63 99 EC */	ori r3, r3, TRKInterruptHandler@l
/* 800035C0 000005C0  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 800035C4 000005C4  38 60 03 00 */	li r3, 0x300
/* 800035C8 000005C8  4C 00 00 64 */	rfi
/* 800035CC 000005CC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800035D0 000005D0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800035D4 000005D4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800035D8 000005D8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800035DC 000005DC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800035E0 000005E0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800035E4 000005E4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800035E8 000005E8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800035EC 000005EC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800035F0 000005F0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800035F4 000005F4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800035F8 000005F8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800035FC 000005FC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003600 00000600  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003604 00000604  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003608 00000608  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000360C 0000060C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003610 00000610  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003614 00000614  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003618 00000618  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000361C 0000061C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003620 00000620  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003624 00000624  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003628 00000628  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000362C 0000062C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003630 00000630  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003634 00000634  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003638 00000638  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000363C 0000063C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003640 00000640  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003644 00000644  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003648 00000648  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000364C 0000064C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003650 00000650  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003654 00000654  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003658 00000658  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000365C 0000065C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003660 00000660  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003664 00000664  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003668 00000668  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000366C 0000066C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003670 00000670  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003674 00000674  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003678 00000678  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000367C 0000067C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003680 00000680  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003684 00000684  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003688 00000688  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000368C 0000068C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003690 00000690  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003694 00000694  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003698 00000698  7C 51 43 A6 */	mtspr 0x111, r2
/* 8000369C 0000069C  7C 72 43 A6 */	mtspr 0x112, r3
/* 800036A0 000006A0  7C 93 43 A6 */	mtspr 0x113, r4
/* 800036A4 000006A4  7C 5A 02 A6 */	mfspr r2, 0x1a
/* 800036A8 000006A8  7C 9B 02 A6 */	mfspr r4, 0x1b
/* 800036AC 000006AC  7C 60 00 A6 */	mfmsr r3
/* 800036B0 000006B0  60 63 00 30 */	ori r3, r3, 0x30
/* 800036B4 000006B4  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 800036B8 000006B8  3C 60 80 32 */	lis r3, TRKInterruptHandler@h
/* 800036BC 000006BC  60 63 99 EC */	ori r3, r3, TRKInterruptHandler@l
/* 800036C0 000006C0  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 800036C4 000006C4  38 60 04 00 */	li r3, 0x400
/* 800036C8 000006C8  4C 00 00 64 */	rfi
/* 800036CC 000006CC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800036D0 000006D0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800036D4 000006D4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800036D8 000006D8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800036DC 000006DC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800036E0 000006E0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800036E4 000006E4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800036E8 000006E8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800036EC 000006EC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800036F0 000006F0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800036F4 000006F4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800036F8 000006F8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800036FC 000006FC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003700 00000700  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003704 00000704  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003708 00000708  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000370C 0000070C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003710 00000710  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003714 00000714  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003718 00000718  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000371C 0000071C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003720 00000720  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003724 00000724  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003728 00000728  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000372C 0000072C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003730 00000730  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003734 00000734  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003738 00000738  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000373C 0000073C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003740 00000740  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003744 00000744  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003748 00000748  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000374C 0000074C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003750 00000750  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003754 00000754  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003758 00000758  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000375C 0000075C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003760 00000760  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003764 00000764  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003768 00000768  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000376C 0000076C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003770 00000770  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003774 00000774  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003778 00000778  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000377C 0000077C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003780 00000780  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003784 00000784  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003788 00000788  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000378C 0000078C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003790 00000790  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003794 00000794  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003798 00000798  7C 51 43 A6 */	mtspr 0x111, r2
/* 8000379C 0000079C  7C 72 43 A6 */	mtspr 0x112, r3
/* 800037A0 000007A0  7C 93 43 A6 */	mtspr 0x113, r4
/* 800037A4 000007A4  7C 5A 02 A6 */	mfspr r2, 0x1a
/* 800037A8 000007A8  7C 9B 02 A6 */	mfspr r4, 0x1b
/* 800037AC 000007AC  7C 60 00 A6 */	mfmsr r3
/* 800037B0 000007B0  60 63 00 30 */	ori r3, r3, 0x30
/* 800037B4 000007B4  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 800037B8 000007B8  3C 60 80 32 */	lis r3, TRKInterruptHandler@h
/* 800037BC 000007BC  60 63 99 EC */	ori r3, r3, TRKInterruptHandler@l
/* 800037C0 000007C0  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 800037C4 000007C4  38 60 05 00 */	li r3, 0x500
/* 800037C8 000007C8  4C 00 00 64 */	rfi
/* 800037CC 000007CC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800037D0 000007D0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800037D4 000007D4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800037D8 000007D8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800037DC 000007DC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800037E0 000007E0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800037E4 000007E4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800037E8 000007E8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800037EC 000007EC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800037F0 000007F0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800037F4 000007F4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800037F8 000007F8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800037FC 000007FC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003800 00000800  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003804 00000804  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003808 00000808  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000380C 0000080C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003810 00000810  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003814 00000814  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003818 00000818  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000381C 0000081C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003820 00000820  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003824 00000824  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003828 00000828  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000382C 0000082C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003830 00000830  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003834 00000834  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003838 00000838  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000383C 0000083C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003840 00000840  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003844 00000844  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003848 00000848  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000384C 0000084C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003850 00000850  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003854 00000854  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003858 00000858  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000385C 0000085C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003860 00000860  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003864 00000864  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003868 00000868  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000386C 0000086C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003870 00000870  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003874 00000874  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003878 00000878  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000387C 0000087C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003880 00000880  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003884 00000884  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003888 00000888  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000388C 0000088C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003890 00000890  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003894 00000894  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003898 00000898  7C 51 43 A6 */	mtspr 0x111, r2
/* 8000389C 0000089C  7C 72 43 A6 */	mtspr 0x112, r3
/* 800038A0 000008A0  7C 93 43 A6 */	mtspr 0x113, r4
/* 800038A4 000008A4  7C 5A 02 A6 */	mfspr r2, 0x1a
/* 800038A8 000008A8  7C 9B 02 A6 */	mfspr r4, 0x1b
/* 800038AC 000008AC  7C 60 00 A6 */	mfmsr r3
/* 800038B0 000008B0  60 63 00 30 */	ori r3, r3, 0x30
/* 800038B4 000008B4  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 800038B8 000008B8  3C 60 80 32 */	lis r3, TRKInterruptHandler@h
/* 800038BC 000008BC  60 63 99 EC */	ori r3, r3, TRKInterruptHandler@l
/* 800038C0 000008C0  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 800038C4 000008C4  38 60 06 00 */	li r3, 0x600
/* 800038C8 000008C8  4C 00 00 64 */	rfi
/* 800038CC 000008CC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800038D0 000008D0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800038D4 000008D4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800038D8 000008D8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800038DC 000008DC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800038E0 000008E0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800038E4 000008E4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800038E8 000008E8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800038EC 000008EC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800038F0 000008F0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800038F4 000008F4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800038F8 000008F8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800038FC 000008FC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003900 00000900  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003904 00000904  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003908 00000908  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000390C 0000090C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003910 00000910  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003914 00000914  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003918 00000918  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000391C 0000091C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003920 00000920  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003924 00000924  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003928 00000928  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000392C 0000092C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003930 00000930  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003934 00000934  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003938 00000938  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000393C 0000093C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003940 00000940  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003944 00000944  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003948 00000948  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000394C 0000094C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003950 00000950  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003954 00000954  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003958 00000958  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000395C 0000095C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003960 00000960  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003964 00000964  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003968 00000968  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000396C 0000096C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003970 00000970  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003974 00000974  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003978 00000978  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000397C 0000097C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003980 00000980  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003984 00000984  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003988 00000988  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000398C 0000098C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003990 00000990  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003994 00000994  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003998 00000998  7C 51 43 A6 */	mtspr 0x111, r2
/* 8000399C 0000099C  7C 72 43 A6 */	mtspr 0x112, r3
/* 800039A0 000009A0  7C 93 43 A6 */	mtspr 0x113, r4
/* 800039A4 000009A4  7C 5A 02 A6 */	mfspr r2, 0x1a
/* 800039A8 000009A8  7C 9B 02 A6 */	mfspr r4, 0x1b
/* 800039AC 000009AC  7C 60 00 A6 */	mfmsr r3
/* 800039B0 000009B0  60 63 00 30 */	ori r3, r3, 0x30
/* 800039B4 000009B4  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 800039B8 000009B8  3C 60 80 32 */	lis r3, TRKInterruptHandler@h
/* 800039BC 000009BC  60 63 99 EC */	ori r3, r3, TRKInterruptHandler@l
/* 800039C0 000009C0  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 800039C4 000009C4  38 60 07 00 */	li r3, 0x700
/* 800039C8 000009C8  4C 00 00 64 */	rfi
/* 800039CC 000009CC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800039D0 000009D0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800039D4 000009D4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800039D8 000009D8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800039DC 000009DC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800039E0 000009E0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800039E4 000009E4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800039E8 000009E8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800039EC 000009EC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800039F0 000009F0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800039F4 000009F4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800039F8 000009F8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800039FC 000009FC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A00 00000A00  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A04 00000A04  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A08 00000A08  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A0C 00000A0C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A10 00000A10  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A14 00000A14  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A18 00000A18  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A1C 00000A1C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A20 00000A20  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A24 00000A24  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A28 00000A28  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A2C 00000A2C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A30 00000A30  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A34 00000A34  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A38 00000A38  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A3C 00000A3C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A40 00000A40  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A44 00000A44  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A48 00000A48  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A4C 00000A4C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A50 00000A50  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A54 00000A54  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A58 00000A58  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A5C 00000A5C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A60 00000A60  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A64 00000A64  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A68 00000A68  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A6C 00000A6C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A70 00000A70  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A74 00000A74  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A78 00000A78  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A7C 00000A7C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A80 00000A80  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A84 00000A84  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A88 00000A88  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A8C 00000A8C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A90 00000A90  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A94 00000A94  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003A98 00000A98  7C 51 43 A6 */	mtspr 0x111, r2
/* 80003A9C 00000A9C  7C 72 43 A6 */	mtspr 0x112, r3
/* 80003AA0 00000AA0  7C 93 43 A6 */	mtspr 0x113, r4
/* 80003AA4 00000AA4  7C 5A 02 A6 */	mfspr r2, 0x1a
/* 80003AA8 00000AA8  7C 9B 02 A6 */	mfspr r4, 0x1b
/* 80003AAC 00000AAC  7C 60 00 A6 */	mfmsr r3
/* 80003AB0 00000AB0  60 63 00 30 */	ori r3, r3, 0x30
/* 80003AB4 00000AB4  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 80003AB8 00000AB8  3C 60 80 32 */	lis r3, TRKInterruptHandler@h
/* 80003ABC 00000ABC  60 63 99 EC */	ori r3, r3, TRKInterruptHandler@l
/* 80003AC0 00000AC0  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 80003AC4 00000AC4  38 60 08 00 */	li r3, 0x800
/* 80003AC8 00000AC8  4C 00 00 64 */	rfi
/* 80003ACC 00000ACC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003AD0 00000AD0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003AD4 00000AD4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003AD8 00000AD8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003ADC 00000ADC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003AE0 00000AE0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003AE4 00000AE4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003AE8 00000AE8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003AEC 00000AEC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003AF0 00000AF0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003AF4 00000AF4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003AF8 00000AF8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003AFC 00000AFC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B00 00000B00  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B04 00000B04  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B08 00000B08  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B0C 00000B0C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B10 00000B10  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B14 00000B14  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B18 00000B18  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B1C 00000B1C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B20 00000B20  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B24 00000B24  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B28 00000B28  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B2C 00000B2C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B30 00000B30  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B34 00000B34  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B38 00000B38  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B3C 00000B3C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B40 00000B40  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B44 00000B44  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B48 00000B48  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B4C 00000B4C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B50 00000B50  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B54 00000B54  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B58 00000B58  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B5C 00000B5C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B60 00000B60  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B64 00000B64  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B68 00000B68  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B6C 00000B6C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B70 00000B70  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B74 00000B74  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B78 00000B78  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B7C 00000B7C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B80 00000B80  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B84 00000B84  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B88 00000B88  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B8C 00000B8C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B90 00000B90  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B94 00000B94  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003B98 00000B98  7C 51 43 A6 */	mtspr 0x111, r2
/* 80003B9C 00000B9C  7C 72 43 A6 */	mtspr 0x112, r3
/* 80003BA0 00000BA0  7C 93 43 A6 */	mtspr 0x113, r4
/* 80003BA4 00000BA4  7C 5A 02 A6 */	mfspr r2, 0x1a
/* 80003BA8 00000BA8  7C 9B 02 A6 */	mfspr r4, 0x1b
/* 80003BAC 00000BAC  7C 60 00 A6 */	mfmsr r3
/* 80003BB0 00000BB0  60 63 00 30 */	ori r3, r3, 0x30
/* 80003BB4 00000BB4  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 80003BB8 00000BB8  3C 60 80 32 */	lis r3, TRKInterruptHandler@h
/* 80003BBC 00000BBC  60 63 99 EC */	ori r3, r3, TRKInterruptHandler@l
/* 80003BC0 00000BC0  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 80003BC4 00000BC4  38 60 09 00 */	li r3, 0x900
/* 80003BC8 00000BC8  4C 00 00 64 */	rfi
/* 80003BCC 00000BCC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003BD0 00000BD0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003BD4 00000BD4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003BD8 00000BD8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003BDC 00000BDC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003BE0 00000BE0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003BE4 00000BE4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003BE8 00000BE8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003BEC 00000BEC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003BF0 00000BF0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003BF4 00000BF4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003BF8 00000BF8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003BFC 00000BFC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C00 00000C00  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C04 00000C04  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C08 00000C08  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C0C 00000C0C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C10 00000C10  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C14 00000C14  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C18 00000C18  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C1C 00000C1C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C20 00000C20  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C24 00000C24  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C28 00000C28  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C2C 00000C2C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C30 00000C30  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C34 00000C34  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C38 00000C38  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C3C 00000C3C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C40 00000C40  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C44 00000C44  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C48 00000C48  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C4C 00000C4C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C50 00000C50  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C54 00000C54  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C58 00000C58  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C5C 00000C5C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C60 00000C60  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C64 00000C64  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C68 00000C68  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C6C 00000C6C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C70 00000C70  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C74 00000C74  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C78 00000C78  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C7C 00000C7C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C80 00000C80  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C84 00000C84  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C88 00000C88  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C8C 00000C8C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C90 00000C90  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C94 00000C94  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C98 00000C98  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003C9C 00000C9C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003CA0 00000CA0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003CA4 00000CA4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003CA8 00000CA8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003CAC 00000CAC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003CB0 00000CB0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003CB4 00000CB4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003CB8 00000CB8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003CBC 00000CBC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003CC0 00000CC0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003CC4 00000CC4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003CC8 00000CC8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003CCC 00000CCC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003CD0 00000CD0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003CD4 00000CD4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003CD8 00000CD8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003CDC 00000CDC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003CE0 00000CE0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003CE4 00000CE4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003CE8 00000CE8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003CEC 00000CEC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003CF0 00000CF0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003CF4 00000CF4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003CF8 00000CF8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003CFC 00000CFC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D00 00000D00  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D04 00000D04  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D08 00000D08  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D0C 00000D0C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D10 00000D10  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D14 00000D14  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D18 00000D18  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D1C 00000D1C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D20 00000D20  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D24 00000D24  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D28 00000D28  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D2C 00000D2C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D30 00000D30  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D34 00000D34  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D38 00000D38  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D3C 00000D3C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D40 00000D40  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D44 00000D44  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D48 00000D48  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D4C 00000D4C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D50 00000D50  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D54 00000D54  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D58 00000D58  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D5C 00000D5C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D60 00000D60  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D64 00000D64  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D68 00000D68  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D6C 00000D6C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D70 00000D70  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D74 00000D74  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D78 00000D78  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D7C 00000D7C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D80 00000D80  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D84 00000D84  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D88 00000D88  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D8C 00000D8C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D90 00000D90  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D94 00000D94  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D98 00000D98  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003D9C 00000D9C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003DA0 00000DA0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003DA4 00000DA4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003DA8 00000DA8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003DAC 00000DAC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003DB0 00000DB0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003DB4 00000DB4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003DB8 00000DB8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003DBC 00000DBC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003DC0 00000DC0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003DC4 00000DC4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003DC8 00000DC8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003DCC 00000DCC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003DD0 00000DD0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003DD4 00000DD4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003DD8 00000DD8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003DDC 00000DDC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003DE0 00000DE0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003DE4 00000DE4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003DE8 00000DE8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003DEC 00000DEC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003DF0 00000DF0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003DF4 00000DF4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003DF8 00000DF8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003DFC 00000DFC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E00 00000E00  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E04 00000E04  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E08 00000E08  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E0C 00000E0C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E10 00000E10  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E14 00000E14  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E18 00000E18  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E1C 00000E1C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E20 00000E20  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E24 00000E24  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E28 00000E28  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E2C 00000E2C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E30 00000E30  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E34 00000E34  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E38 00000E38  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E3C 00000E3C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E40 00000E40  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E44 00000E44  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E48 00000E48  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E4C 00000E4C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E50 00000E50  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E54 00000E54  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E58 00000E58  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E5C 00000E5C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E60 00000E60  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E64 00000E64  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E68 00000E68  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E6C 00000E6C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E70 00000E70  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E74 00000E74  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E78 00000E78  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E7C 00000E7C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E80 00000E80  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E84 00000E84  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E88 00000E88  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E8C 00000E8C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E90 00000E90  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E94 00000E94  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003E98 00000E98  7C 51 43 A6 */	mtspr 0x111, r2
/* 80003E9C 00000E9C  7C 72 43 A6 */	mtspr 0x112, r3
/* 80003EA0 00000EA0  7C 93 43 A6 */	mtspr 0x113, r4
/* 80003EA4 00000EA4  7C 5A 02 A6 */	mfspr r2, 0x1a
/* 80003EA8 00000EA8  7C 9B 02 A6 */	mfspr r4, 0x1b
/* 80003EAC 00000EAC  7C 60 00 A6 */	mfmsr r3
/* 80003EB0 00000EB0  60 63 00 30 */	ori r3, r3, 0x30
/* 80003EB4 00000EB4  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 80003EB8 00000EB8  3C 60 80 32 */	lis r3, TRKInterruptHandler@h
/* 80003EBC 00000EBC  60 63 99 EC */	ori r3, r3, TRKInterruptHandler@l
/* 80003EC0 00000EC0  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 80003EC4 00000EC4  38 60 0C 00 */	li r3, 0xc00
/* 80003EC8 00000EC8  4C 00 00 64 */	rfi
/* 80003ECC 00000ECC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003ED0 00000ED0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003ED4 00000ED4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003ED8 00000ED8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003EDC 00000EDC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003EE0 00000EE0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003EE4 00000EE4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003EE8 00000EE8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003EEC 00000EEC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003EF0 00000EF0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003EF4 00000EF4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003EF8 00000EF8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003EFC 00000EFC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F00 00000F00  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F04 00000F04  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F08 00000F08  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F0C 00000F0C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F10 00000F10  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F14 00000F14  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F18 00000F18  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F1C 00000F1C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F20 00000F20  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F24 00000F24  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F28 00000F28  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F2C 00000F2C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F30 00000F30  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F34 00000F34  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F38 00000F38  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F3C 00000F3C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F40 00000F40  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F44 00000F44  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F48 00000F48  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F4C 00000F4C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F50 00000F50  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F54 00000F54  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F58 00000F58  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F5C 00000F5C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F60 00000F60  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F64 00000F64  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F68 00000F68  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F6C 00000F6C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F70 00000F70  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F74 00000F74  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F78 00000F78  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F7C 00000F7C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F80 00000F80  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F84 00000F84  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F88 00000F88  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F8C 00000F8C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F90 00000F90  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F94 00000F94  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003F98 00000F98  7C 51 43 A6 */	mtspr 0x111, r2
/* 80003F9C 00000F9C  7C 72 43 A6 */	mtspr 0x112, r3
/* 80003FA0 00000FA0  7C 93 43 A6 */	mtspr 0x113, r4
/* 80003FA4 00000FA4  7C 5A 02 A6 */	mfspr r2, 0x1a
/* 80003FA8 00000FA8  7C 9B 02 A6 */	mfspr r4, 0x1b
/* 80003FAC 00000FAC  7C 60 00 A6 */	mfmsr r3
/* 80003FB0 00000FB0  60 63 00 30 */	ori r3, r3, 0x30
/* 80003FB4 00000FB4  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 80003FB8 00000FB8  3C 60 80 32 */	lis r3, TRKInterruptHandler@h
/* 80003FBC 00000FBC  60 63 99 EC */	ori r3, r3, TRKInterruptHandler@l
/* 80003FC0 00000FC0  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 80003FC4 00000FC4  38 60 0D 00 */	li r3, 0xd00
/* 80003FC8 00000FC8  4C 00 00 64 */	rfi
/* 80003FCC 00000FCC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003FD0 00000FD0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003FD4 00000FD4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003FD8 00000FD8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003FDC 00000FDC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003FE0 00000FE0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003FE4 00000FE4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003FE8 00000FE8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003FEC 00000FEC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003FF0 00000FF0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003FF4 00000FF4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003FF8 00000FF8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80003FFC 00000FFC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004000 00001000  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004004 00001004  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004008 00001008  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000400C 0000100C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004010 00001010  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004014 00001014  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004018 00001018  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000401C 0000101C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004020 00001020  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004024 00001024  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004028 00001028  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000402C 0000102C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004030 00001030  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004034 00001034  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004038 00001038  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000403C 0000103C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004040 00001040  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004044 00001044  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004048 00001048  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000404C 0000104C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004050 00001050  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004054 00001054  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004058 00001058  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000405C 0000105C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004060 00001060  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004064 00001064  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004068 00001068  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000406C 0000106C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004070 00001070  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004074 00001074  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004078 00001078  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000407C 0000107C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004080 00001080  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004084 00001084  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004088 00001088  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000408C 0000108C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004090 00001090  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004094 00001094  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004098 00001098  7C 51 43 A6 */	mtspr 0x111, r2
/* 8000409C 0000109C  7C 72 43 A6 */	mtspr 0x112, r3
/* 800040A0 000010A0  7C 93 43 A6 */	mtspr 0x113, r4
/* 800040A4 000010A4  7C 5A 02 A6 */	mfspr r2, 0x1a
/* 800040A8 000010A8  7C 9B 02 A6 */	mfspr r4, 0x1b
/* 800040AC 000010AC  7C 60 00 A6 */	mfmsr r3
/* 800040B0 000010B0  60 63 00 30 */	ori r3, r3, 0x30
/* 800040B4 000010B4  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 800040B8 000010B8  3C 60 80 32 */	lis r3, TRKInterruptHandler@h
/* 800040BC 000010BC  60 63 99 EC */	ori r3, r3, TRKInterruptHandler@l
/* 800040C0 000010C0  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 800040C4 000010C4  38 60 0E 00 */	li r3, 0xe00
/* 800040C8 000010C8  4C 00 00 64 */	rfi
/* 800040CC 000010CC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800040D0 000010D0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800040D4 000010D4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800040D8 000010D8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800040DC 000010DC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800040E0 000010E0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800040E4 000010E4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800040E8 000010E8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800040EC 000010EC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800040F0 000010F0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800040F4 000010F4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800040F8 000010F8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800040FC 000010FC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004100 00001100  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004104 00001104  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004108 00001108  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000410C 0000110C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004110 00001110  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004114 00001114  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004118 00001118  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000411C 0000111C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004120 00001120  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004124 00001124  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004128 00001128  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000412C 0000112C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004130 00001130  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004134 00001134  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004138 00001138  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000413C 0000113C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004140 00001140  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004144 00001144  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004148 00001148  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000414C 0000114C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004150 00001150  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004154 00001154  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004158 00001158  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000415C 0000115C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004160 00001160  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004164 00001164  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004168 00001168  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000416C 0000116C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004170 00001170  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004174 00001174  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004178 00001178  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000417C 0000117C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004180 00001180  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004184 00001184  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004188 00001188  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000418C 0000118C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004190 00001190  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004194 00001194  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004198 00001198  48 00 00 54 */	b .L_800041EC
/* 8000419C 0000119C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800041A0 000011A0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800041A4 000011A4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800041A8 000011A8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800041AC 000011AC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800041B0 000011B0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800041B4 000011B4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800041B8 000011B8  7C 51 43 A6 */	mtspr 0x111, r2
/* 800041BC 000011BC  7C 72 43 A6 */	mtspr 0x112, r3
/* 800041C0 000011C0  7C 93 43 A6 */	mtspr 0x113, r4
/* 800041C4 000011C4  7C 5A 02 A6 */	mfspr r2, 0x1a
/* 800041C8 000011C8  7C 9B 02 A6 */	mfspr r4, 0x1b
/* 800041CC 000011CC  7C 60 00 A6 */	mfmsr r3
/* 800041D0 000011D0  60 63 00 30 */	ori r3, r3, 0x30
/* 800041D4 000011D4  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 800041D8 000011D8  3C 60 80 32 */	lis r3, TRKInterruptHandler@h
/* 800041DC 000011DC  60 63 99 EC */	ori r3, r3, TRKInterruptHandler@l
/* 800041E0 000011E0  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 800041E4 000011E4  38 60 0F 20 */	li r3, 0xf20
/* 800041E8 000011E8  4C 00 00 64 */	rfi
.L_800041EC:
/* 800041EC 000011EC  7C 51 43 A6 */	mtspr 0x111, r2
/* 800041F0 000011F0  7C 72 43 A6 */	mtspr 0x112, r3
/* 800041F4 000011F4  7C 93 43 A6 */	mtspr 0x113, r4
/* 800041F8 000011F8  7C 5A 02 A6 */	mfspr r2, 0x1a
/* 800041FC 000011FC  7C 9B 02 A6 */	mfspr r4, 0x1b
/* 80004200 00001200  7C 60 00 A6 */	mfmsr r3
/* 80004204 00001204  60 63 00 30 */	ori r3, r3, 0x30
/* 80004208 00001208  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 8000420C 0000120C  3C 60 80 32 */	lis r3, TRKInterruptHandler@h
/* 80004210 00001210  60 63 99 EC */	ori r3, r3, TRKInterruptHandler@l
/* 80004214 00001214  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 80004218 00001218  38 60 0F 00 */	li r3, 0xf00
/* 8000421C 0000121C  4C 00 00 64 */	rfi
/* 80004220 00001220  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004224 00001224  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004228 00001228  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000422C 0000122C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004230 00001230  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004234 00001234  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004238 00001238  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000423C 0000123C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004240 00001240  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004244 00001244  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004248 00001248  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000424C 0000124C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004250 00001250  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004254 00001254  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004258 00001258  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000425C 0000125C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004260 00001260  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004264 00001264  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004268 00001268  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000426C 0000126C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004270 00001270  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004274 00001274  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004278 00001278  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000427C 0000127C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004280 00001280  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004284 00001284  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004288 00001288  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000428C 0000128C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004290 00001290  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004294 00001294  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004298 00001298  7C 51 43 A6 */	mtspr 0x111, r2
/* 8000429C 0000129C  7C 40 00 26 */	mfcr r2
/* 800042A0 000012A0  7C 52 43 A6 */	mtspr 0x112, r2
/* 800042A4 000012A4  7C 40 00 A6 */	mfmsr r2
/* 800042A8 000012A8  74 42 00 02 */	andis. r2, r2, 2
/* 800042AC 000012AC  41 82 00 1C */	beq .L_800042C8
/* 800042B0 000012B0  7C 40 00 A6 */	mfmsr r2
/* 800042B4 000012B4  6C 42 00 02 */	xoris r2, r2, 2
/* 800042B8 000012B8  7C 00 04 AC */	sync 0
/* 800042BC 000012BC  7C 40 01 24 */	mtmsr r2
/* 800042C0 000012C0  7C 00 04 AC */	sync 0
/* 800042C4 000012C4  7C 51 43 A6 */	mtspr 0x111, r2
.L_800042C8:
/* 800042C8 000012C8  7C 52 42 A6 */	mfspr r2, 0x112
/* 800042CC 000012CC  7C 4F F1 20 */	mtcrf 0xff, r2
/* 800042D0 000012D0  7C 51 42 A6 */	mfspr r2, 0x111
/* 800042D4 000012D4  7C 51 43 A6 */	mtspr 0x111, r2
/* 800042D8 000012D8  7C 72 43 A6 */	mtspr 0x112, r3
/* 800042DC 000012DC  7C 93 43 A6 */	mtspr 0x113, r4
/* 800042E0 000012E0  7C 5A 02 A6 */	mfspr r2, 0x1a
/* 800042E4 000012E4  7C 9B 02 A6 */	mfspr r4, 0x1b
/* 800042E8 000012E8  7C 60 00 A6 */	mfmsr r3
/* 800042EC 000012EC  60 63 00 30 */	ori r3, r3, 0x30
/* 800042F0 000012F0  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 800042F4 000012F4  3C 60 80 32 */	lis r3, TRKInterruptHandler@h
/* 800042F8 000012F8  60 63 99 EC */	ori r3, r3, TRKInterruptHandler@l
/* 800042FC 000012FC  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 80004300 00001300  38 60 10 00 */	li r3, 0x1000
/* 80004304 00001304  4C 00 00 64 */	rfi
/* 80004308 00001308  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000430C 0000130C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004310 00001310  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004314 00001314  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004318 00001318  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000431C 0000131C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004320 00001320  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004324 00001324  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004328 00001328  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000432C 0000132C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004330 00001330  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004334 00001334  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004338 00001338  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000433C 0000133C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004340 00001340  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004344 00001344  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004348 00001348  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000434C 0000134C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004350 00001350  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004354 00001354  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004358 00001358  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000435C 0000135C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004360 00001360  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004364 00001364  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004368 00001368  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000436C 0000136C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004370 00001370  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004374 00001374  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004378 00001378  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000437C 0000137C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004380 00001380  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004384 00001384  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004388 00001388  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000438C 0000138C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004390 00001390  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004394 00001394  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004398 00001398  7C 51 43 A6 */	mtspr 0x111, r2
/* 8000439C 0000139C  7C 40 00 26 */	mfcr r2
/* 800043A0 000013A0  7C 52 43 A6 */	mtspr 0x112, r2
/* 800043A4 000013A4  7C 40 00 A6 */	mfmsr r2
/* 800043A8 000013A8  74 42 00 02 */	andis. r2, r2, 2
/* 800043AC 000013AC  41 82 00 1C */	beq .L_800043C8
/* 800043B0 000013B0  7C 40 00 A6 */	mfmsr r2
/* 800043B4 000013B4  6C 42 00 02 */	xoris r2, r2, 2
/* 800043B8 000013B8  7C 00 04 AC */	sync 0
/* 800043BC 000013BC  7C 40 01 24 */	mtmsr r2
/* 800043C0 000013C0  7C 00 04 AC */	sync 0
/* 800043C4 000013C4  7C 51 43 A6 */	mtspr 0x111, r2
.L_800043C8:
/* 800043C8 000013C8  7C 52 42 A6 */	mfspr r2, 0x112
/* 800043CC 000013CC  7C 4F F1 20 */	mtcrf 0xff, r2
/* 800043D0 000013D0  7C 51 42 A6 */	mfspr r2, 0x111
/* 800043D4 000013D4  7C 51 43 A6 */	mtspr 0x111, r2
/* 800043D8 000013D8  7C 72 43 A6 */	mtspr 0x112, r3
/* 800043DC 000013DC  7C 93 43 A6 */	mtspr 0x113, r4
/* 800043E0 000013E0  7C 5A 02 A6 */	mfspr r2, 0x1a
/* 800043E4 000013E4  7C 9B 02 A6 */	mfspr r4, 0x1b
/* 800043E8 000013E8  7C 60 00 A6 */	mfmsr r3
/* 800043EC 000013EC  60 63 00 30 */	ori r3, r3, 0x30
/* 800043F0 000013F0  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 800043F4 000013F4  3C 60 80 32 */	lis r3, TRKInterruptHandler@h
/* 800043F8 000013F8  60 63 99 EC */	ori r3, r3, TRKInterruptHandler@l
/* 800043FC 000013FC  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 80004400 00001400  38 60 11 00 */	li r3, 0x1100
/* 80004404 00001404  4C 00 00 64 */	rfi
/* 80004408 00001408  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000440C 0000140C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004410 00001410  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004414 00001414  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004418 00001418  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000441C 0000141C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004420 00001420  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004424 00001424  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004428 00001428  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000442C 0000142C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004430 00001430  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004434 00001434  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004438 00001438  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000443C 0000143C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004440 00001440  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004444 00001444  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004448 00001448  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000444C 0000144C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004450 00001450  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004454 00001454  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004458 00001458  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000445C 0000145C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004460 00001460  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004464 00001464  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004468 00001468  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000446C 0000146C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004470 00001470  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004474 00001474  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004478 00001478  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000447C 0000147C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004480 00001480  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004484 00001484  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004488 00001488  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000448C 0000148C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004490 00001490  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004494 00001494  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004498 00001498  7C 51 43 A6 */	mtspr 0x111, r2
/* 8000449C 0000149C  7C 40 00 26 */	mfcr r2
/* 800044A0 000014A0  7C 52 43 A6 */	mtspr 0x112, r2
/* 800044A4 000014A4  7C 40 00 A6 */	mfmsr r2
/* 800044A8 000014A8  74 42 00 02 */	andis. r2, r2, 2
/* 800044AC 000014AC  41 82 00 1C */	beq .L_800044C8
/* 800044B0 000014B0  7C 40 00 A6 */	mfmsr r2
/* 800044B4 000014B4  6C 42 00 02 */	xoris r2, r2, 2
/* 800044B8 000014B8  7C 00 04 AC */	sync 0
/* 800044BC 000014BC  7C 40 01 24 */	mtmsr r2
/* 800044C0 000014C0  7C 00 04 AC */	sync 0
/* 800044C4 000014C4  7C 51 43 A6 */	mtspr 0x111, r2
.L_800044C8:
/* 800044C8 000014C8  7C 52 42 A6 */	mfspr r2, 0x112
/* 800044CC 000014CC  7C 4F F1 20 */	mtcrf 0xff, r2
/* 800044D0 000014D0  7C 51 42 A6 */	mfspr r2, 0x111
/* 800044D4 000014D4  7C 51 43 A6 */	mtspr 0x111, r2
/* 800044D8 000014D8  7C 72 43 A6 */	mtspr 0x112, r3
/* 800044DC 000014DC  7C 93 43 A6 */	mtspr 0x113, r4
/* 800044E0 000014E0  7C 5A 02 A6 */	mfspr r2, 0x1a
/* 800044E4 000014E4  7C 9B 02 A6 */	mfspr r4, 0x1b
/* 800044E8 000014E8  7C 60 00 A6 */	mfmsr r3
/* 800044EC 000014EC  60 63 00 30 */	ori r3, r3, 0x30
/* 800044F0 000014F0  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 800044F4 000014F4  3C 60 80 32 */	lis r3, TRKInterruptHandler@h
/* 800044F8 000014F8  60 63 99 EC */	ori r3, r3, TRKInterruptHandler@l
/* 800044FC 000014FC  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 80004500 00001500  38 60 12 00 */	li r3, 0x1200
/* 80004504 00001504  4C 00 00 64 */	rfi
/* 80004508 00001508  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000450C 0000150C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004510 00001510  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004514 00001514  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004518 00001518  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000451C 0000151C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004520 00001520  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004524 00001524  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004528 00001528  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000452C 0000152C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004530 00001530  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004534 00001534  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004538 00001538  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000453C 0000153C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004540 00001540  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004544 00001544  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004548 00001548  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000454C 0000154C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004550 00001550  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004554 00001554  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004558 00001558  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000455C 0000155C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004560 00001560  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004564 00001564  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004568 00001568  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000456C 0000156C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004570 00001570  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004574 00001574  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004578 00001578  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000457C 0000157C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004580 00001580  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004584 00001584  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004588 00001588  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000458C 0000158C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004590 00001590  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004594 00001594  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004598 00001598  7C 51 43 A6 */	mtspr 0x111, r2
/* 8000459C 0000159C  7C 72 43 A6 */	mtspr 0x112, r3
/* 800045A0 000015A0  7C 93 43 A6 */	mtspr 0x113, r4
/* 800045A4 000015A4  7C 5A 02 A6 */	mfspr r2, 0x1a
/* 800045A8 000015A8  7C 9B 02 A6 */	mfspr r4, 0x1b
/* 800045AC 000015AC  7C 60 00 A6 */	mfmsr r3
/* 800045B0 000015B0  60 63 00 30 */	ori r3, r3, 0x30
/* 800045B4 000015B4  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 800045B8 000015B8  3C 60 80 32 */	lis r3, TRKInterruptHandler@h
/* 800045BC 000015BC  60 63 99 EC */	ori r3, r3, TRKInterruptHandler@l
/* 800045C0 000015C0  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 800045C4 000015C4  38 60 13 00 */	li r3, 0x1300
/* 800045C8 000015C8  4C 00 00 64 */	rfi
/* 800045CC 000015CC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800045D0 000015D0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800045D4 000015D4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800045D8 000015D8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800045DC 000015DC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800045E0 000015E0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800045E4 000015E4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800045E8 000015E8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800045EC 000015EC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800045F0 000015F0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800045F4 000015F4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800045F8 000015F8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800045FC 000015FC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004600 00001600  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004604 00001604  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004608 00001608  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000460C 0000160C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004610 00001610  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004614 00001614  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004618 00001618  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000461C 0000161C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004620 00001620  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004624 00001624  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004628 00001628  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000462C 0000162C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004630 00001630  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004634 00001634  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004638 00001638  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000463C 0000163C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004640 00001640  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004644 00001644  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004648 00001648  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000464C 0000164C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004650 00001650  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004654 00001654  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004658 00001658  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000465C 0000165C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004660 00001660  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004664 00001664  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004668 00001668  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000466C 0000166C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004670 00001670  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004674 00001674  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004678 00001678  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000467C 0000167C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004680 00001680  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004684 00001684  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004688 00001688  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000468C 0000168C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004690 00001690  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004694 00001694  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004698 00001698  7C 51 43 A6 */	mtspr 0x111, r2
/* 8000469C 0000169C  7C 72 43 A6 */	mtspr 0x112, r3
/* 800046A0 000016A0  7C 93 43 A6 */	mtspr 0x113, r4
/* 800046A4 000016A4  7C 5A 02 A6 */	mfspr r2, 0x1a
/* 800046A8 000016A8  7C 9B 02 A6 */	mfspr r4, 0x1b
/* 800046AC 000016AC  7C 60 00 A6 */	mfmsr r3
/* 800046B0 000016B0  60 63 00 30 */	ori r3, r3, 0x30
/* 800046B4 000016B4  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 800046B8 000016B8  3C 60 80 32 */	lis r3, TRKInterruptHandler@h
/* 800046BC 000016BC  60 63 99 EC */	ori r3, r3, TRKInterruptHandler@l
/* 800046C0 000016C0  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 800046C4 000016C4  38 60 14 00 */	li r3, 0x1400
/* 800046C8 000016C8  4C 00 00 64 */	rfi
/* 800046CC 000016CC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800046D0 000016D0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800046D4 000016D4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800046D8 000016D8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800046DC 000016DC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800046E0 000016E0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800046E4 000016E4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800046E8 000016E8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800046EC 000016EC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800046F0 000016F0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800046F4 000016F4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800046F8 000016F8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800046FC 000016FC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004700 00001700  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004704 00001704  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004708 00001708  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000470C 0000170C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004710 00001710  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004714 00001714  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004718 00001718  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000471C 0000171C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004720 00001720  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004724 00001724  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004728 00001728  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000472C 0000172C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004730 00001730  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004734 00001734  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004738 00001738  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000473C 0000173C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004740 00001740  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004744 00001744  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004748 00001748  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000474C 0000174C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004750 00001750  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004754 00001754  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004758 00001758  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000475C 0000175C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004760 00001760  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004764 00001764  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004768 00001768  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000476C 0000176C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004770 00001770  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004774 00001774  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004778 00001778  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000477C 0000177C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004780 00001780  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004784 00001784  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004788 00001788  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000478C 0000178C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004790 00001790  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004794 00001794  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004798 00001798  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000479C 0000179C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800047A0 000017A0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800047A4 000017A4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800047A8 000017A8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800047AC 000017AC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800047B0 000017B0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800047B4 000017B4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800047B8 000017B8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800047BC 000017BC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800047C0 000017C0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800047C4 000017C4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800047C8 000017C8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800047CC 000017CC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800047D0 000017D0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800047D4 000017D4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800047D8 000017D8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800047DC 000017DC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800047E0 000017E0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800047E4 000017E4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800047E8 000017E8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800047EC 000017EC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800047F0 000017F0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800047F4 000017F4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800047F8 000017F8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800047FC 000017FC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004800 00001800  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004804 00001804  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004808 00001808  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000480C 0000180C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004810 00001810  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004814 00001814  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004818 00001818  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000481C 0000181C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004820 00001820  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004824 00001824  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004828 00001828  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000482C 0000182C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004830 00001830  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004834 00001834  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004838 00001838  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000483C 0000183C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004840 00001840  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004844 00001844  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004848 00001848  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000484C 0000184C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004850 00001850  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004854 00001854  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004858 00001858  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000485C 0000185C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004860 00001860  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004864 00001864  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004868 00001868  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000486C 0000186C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004870 00001870  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004874 00001874  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004878 00001878  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000487C 0000187C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004880 00001880  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004884 00001884  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004888 00001888  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000488C 0000188C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004890 00001890  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004894 00001894  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004898 00001898  7C 51 43 A6 */	mtspr 0x111, r2
/* 8000489C 0000189C  7C 72 43 A6 */	mtspr 0x112, r3
/* 800048A0 000018A0  7C 93 43 A6 */	mtspr 0x113, r4
/* 800048A4 000018A4  7C 5A 02 A6 */	mfspr r2, 0x1a
/* 800048A8 000018A8  7C 9B 02 A6 */	mfspr r4, 0x1b
/* 800048AC 000018AC  7C 60 00 A6 */	mfmsr r3
/* 800048B0 000018B0  60 63 00 30 */	ori r3, r3, 0x30
/* 800048B4 000018B4  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 800048B8 000018B8  3C 60 80 32 */	lis r3, TRKInterruptHandler@h
/* 800048BC 000018BC  60 63 99 EC */	ori r3, r3, TRKInterruptHandler@l
/* 800048C0 000018C0  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 800048C4 000018C4  38 60 16 00 */	li r3, 0x1600
/* 800048C8 000018C8  4C 00 00 64 */	rfi
/* 800048CC 000018CC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800048D0 000018D0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800048D4 000018D4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800048D8 000018D8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800048DC 000018DC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800048E0 000018E0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800048E4 000018E4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800048E8 000018E8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800048EC 000018EC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800048F0 000018F0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800048F4 000018F4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800048F8 000018F8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800048FC 000018FC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004900 00001900  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004904 00001904  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004908 00001908  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000490C 0000190C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004910 00001910  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004914 00001914  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004918 00001918  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000491C 0000191C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004920 00001920  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004924 00001924  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004928 00001928  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000492C 0000192C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004930 00001930  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004934 00001934  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004938 00001938  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000493C 0000193C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004940 00001940  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004944 00001944  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004948 00001948  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000494C 0000194C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004950 00001950  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004954 00001954  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004958 00001958  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000495C 0000195C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004960 00001960  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004964 00001964  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004968 00001968  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000496C 0000196C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004970 00001970  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004974 00001974  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004978 00001978  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000497C 0000197C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004980 00001980  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004984 00001984  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004988 00001988  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000498C 0000198C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004990 00001990  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004994 00001994  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004998 00001998  7C 51 43 A6 */	mtspr 0x111, r2
/* 8000499C 0000199C  7C 72 43 A6 */	mtspr 0x112, r3
/* 800049A0 000019A0  7C 93 43 A6 */	mtspr 0x113, r4
/* 800049A4 000019A4  7C 5A 02 A6 */	mfspr r2, 0x1a
/* 800049A8 000019A8  7C 9B 02 A6 */	mfspr r4, 0x1b
/* 800049AC 000019AC  7C 60 00 A6 */	mfmsr r3
/* 800049B0 000019B0  60 63 00 30 */	ori r3, r3, 0x30
/* 800049B4 000019B4  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 800049B8 000019B8  3C 60 80 32 */	lis r3, TRKInterruptHandler@h
/* 800049BC 000019BC  60 63 99 EC */	ori r3, r3, TRKInterruptHandler@l
/* 800049C0 000019C0  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 800049C4 000019C4  38 60 17 00 */	li r3, 0x1700
/* 800049C8 000019C8  4C 00 00 64 */	rfi
/* 800049CC 000019CC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800049D0 000019D0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800049D4 000019D4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800049D8 000019D8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800049DC 000019DC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800049E0 000019E0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800049E4 000019E4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800049E8 000019E8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800049EC 000019EC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800049F0 000019F0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800049F4 000019F4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800049F8 000019F8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800049FC 000019FC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A00 00001A00  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A04 00001A04  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A08 00001A08  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A0C 00001A0C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A10 00001A10  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A14 00001A14  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A18 00001A18  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A1C 00001A1C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A20 00001A20  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A24 00001A24  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A28 00001A28  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A2C 00001A2C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A30 00001A30  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A34 00001A34  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A38 00001A38  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A3C 00001A3C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A40 00001A40  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A44 00001A44  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A48 00001A48  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A4C 00001A4C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A50 00001A50  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A54 00001A54  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A58 00001A58  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A5C 00001A5C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A60 00001A60  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A64 00001A64  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A68 00001A68  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A6C 00001A6C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A70 00001A70  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A74 00001A74  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A78 00001A78  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A7C 00001A7C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A80 00001A80  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A84 00001A84  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A88 00001A88  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A8C 00001A8C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A90 00001A90  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A94 00001A94  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A98 00001A98  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004A9C 00001A9C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004AA0 00001AA0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004AA4 00001AA4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004AA8 00001AA8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004AAC 00001AAC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004AB0 00001AB0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004AB4 00001AB4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004AB8 00001AB8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004ABC 00001ABC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004AC0 00001AC0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004AC4 00001AC4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004AC8 00001AC8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004ACC 00001ACC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004AD0 00001AD0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004AD4 00001AD4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004AD8 00001AD8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004ADC 00001ADC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004AE0 00001AE0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004AE4 00001AE4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004AE8 00001AE8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004AEC 00001AEC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004AF0 00001AF0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004AF4 00001AF4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004AF8 00001AF8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004AFC 00001AFC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B00 00001B00  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B04 00001B04  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B08 00001B08  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B0C 00001B0C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B10 00001B10  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B14 00001B14  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B18 00001B18  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B1C 00001B1C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B20 00001B20  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B24 00001B24  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B28 00001B28  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B2C 00001B2C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B30 00001B30  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B34 00001B34  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B38 00001B38  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B3C 00001B3C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B40 00001B40  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B44 00001B44  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B48 00001B48  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B4C 00001B4C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B50 00001B50  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B54 00001B54  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B58 00001B58  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B5C 00001B5C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B60 00001B60  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B64 00001B64  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B68 00001B68  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B6C 00001B6C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B70 00001B70  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B74 00001B74  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B78 00001B78  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B7C 00001B7C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B80 00001B80  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B84 00001B84  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B88 00001B88  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B8C 00001B8C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B90 00001B90  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B94 00001B94  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B98 00001B98  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004B9C 00001B9C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004BA0 00001BA0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004BA4 00001BA4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004BA8 00001BA8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004BAC 00001BAC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004BB0 00001BB0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004BB4 00001BB4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004BB8 00001BB8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004BBC 00001BBC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004BC0 00001BC0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004BC4 00001BC4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004BC8 00001BC8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004BCC 00001BCC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004BD0 00001BD0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004BD4 00001BD4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004BD8 00001BD8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004BDC 00001BDC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004BE0 00001BE0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004BE4 00001BE4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004BE8 00001BE8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004BEC 00001BEC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004BF0 00001BF0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004BF4 00001BF4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004BF8 00001BF8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004BFC 00001BFC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C00 00001C00  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C04 00001C04  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C08 00001C08  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C0C 00001C0C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C10 00001C10  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C14 00001C14  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C18 00001C18  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C1C 00001C1C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C20 00001C20  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C24 00001C24  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C28 00001C28  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C2C 00001C2C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C30 00001C30  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C34 00001C34  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C38 00001C38  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C3C 00001C3C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C40 00001C40  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C44 00001C44  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C48 00001C48  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C4C 00001C4C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C50 00001C50  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C54 00001C54  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C58 00001C58  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C5C 00001C5C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C60 00001C60  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C64 00001C64  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C68 00001C68  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C6C 00001C6C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C70 00001C70  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C74 00001C74  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C78 00001C78  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C7C 00001C7C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C80 00001C80  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C84 00001C84  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C88 00001C88  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C8C 00001C8C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C90 00001C90  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C94 00001C94  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C98 00001C98  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004C9C 00001C9C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004CA0 00001CA0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004CA4 00001CA4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004CA8 00001CA8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004CAC 00001CAC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004CB0 00001CB0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004CB4 00001CB4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004CB8 00001CB8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004CBC 00001CBC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004CC0 00001CC0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004CC4 00001CC4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004CC8 00001CC8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004CCC 00001CCC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004CD0 00001CD0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004CD4 00001CD4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004CD8 00001CD8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004CDC 00001CDC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004CE0 00001CE0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004CE4 00001CE4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004CE8 00001CE8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004CEC 00001CEC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004CF0 00001CF0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004CF4 00001CF4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004CF8 00001CF8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004CFC 00001CFC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D00 00001D00  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D04 00001D04  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D08 00001D08  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D0C 00001D0C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D10 00001D10  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D14 00001D14  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D18 00001D18  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D1C 00001D1C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D20 00001D20  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D24 00001D24  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D28 00001D28  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D2C 00001D2C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D30 00001D30  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D34 00001D34  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D38 00001D38  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D3C 00001D3C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D40 00001D40  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D44 00001D44  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D48 00001D48  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D4C 00001D4C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D50 00001D50  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D54 00001D54  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D58 00001D58  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D5C 00001D5C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D60 00001D60  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D64 00001D64  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D68 00001D68  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D6C 00001D6C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D70 00001D70  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D74 00001D74  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D78 00001D78  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D7C 00001D7C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D80 00001D80  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D84 00001D84  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D88 00001D88  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D8C 00001D8C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D90 00001D90  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D94 00001D94  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D98 00001D98  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004D9C 00001D9C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004DA0 00001DA0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004DA4 00001DA4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004DA8 00001DA8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004DAC 00001DAC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004DB0 00001DB0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004DB4 00001DB4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004DB8 00001DB8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004DBC 00001DBC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004DC0 00001DC0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004DC4 00001DC4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004DC8 00001DC8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004DCC 00001DCC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004DD0 00001DD0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004DD4 00001DD4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004DD8 00001DD8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004DDC 00001DDC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004DE0 00001DE0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004DE4 00001DE4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004DE8 00001DE8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004DEC 00001DEC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004DF0 00001DF0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004DF4 00001DF4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004DF8 00001DF8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004DFC 00001DFC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E00 00001E00  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E04 00001E04  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E08 00001E08  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E0C 00001E0C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E10 00001E10  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E14 00001E14  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E18 00001E18  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E1C 00001E1C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E20 00001E20  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E24 00001E24  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E28 00001E28  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E2C 00001E2C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E30 00001E30  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E34 00001E34  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E38 00001E38  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E3C 00001E3C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E40 00001E40  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E44 00001E44  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E48 00001E48  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E4C 00001E4C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E50 00001E50  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E54 00001E54  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E58 00001E58  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E5C 00001E5C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E60 00001E60  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E64 00001E64  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E68 00001E68  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E6C 00001E6C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E70 00001E70  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E74 00001E74  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E78 00001E78  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E7C 00001E7C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E80 00001E80  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E84 00001E84  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E88 00001E88  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E8C 00001E8C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E90 00001E90  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E94 00001E94  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004E98 00001E98  7C 51 43 A6 */	mtspr 0x111, r2
/* 80004E9C 00001E9C  7C 72 43 A6 */	mtspr 0x112, r3
/* 80004EA0 00001EA0  7C 93 43 A6 */	mtspr 0x113, r4
/* 80004EA4 00001EA4  7C 5A 02 A6 */	mfspr r2, 0x1a
/* 80004EA8 00001EA8  7C 9B 02 A6 */	mfspr r4, 0x1b
/* 80004EAC 00001EAC  7C 60 00 A6 */	mfmsr r3
/* 80004EB0 00001EB0  60 63 00 30 */	ori r3, r3, 0x30
/* 80004EB4 00001EB4  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 80004EB8 00001EB8  3C 60 80 32 */	lis r3, TRKInterruptHandler@h
/* 80004EBC 00001EBC  60 63 99 EC */	ori r3, r3, TRKInterruptHandler@l
/* 80004EC0 00001EC0  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 80004EC4 00001EC4  38 60 1C 00 */	li r3, 0x1c00
/* 80004EC8 00001EC8  4C 00 00 64 */	rfi
/* 80004ECC 00001ECC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004ED0 00001ED0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004ED4 00001ED4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004ED8 00001ED8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004EDC 00001EDC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004EE0 00001EE0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004EE4 00001EE4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004EE8 00001EE8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004EEC 00001EEC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004EF0 00001EF0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004EF4 00001EF4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004EF8 00001EF8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004EFC 00001EFC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F00 00001F00  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F04 00001F04  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F08 00001F08  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F0C 00001F0C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F10 00001F10  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F14 00001F14  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F18 00001F18  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F1C 00001F1C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F20 00001F20  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F24 00001F24  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F28 00001F28  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F2C 00001F2C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F30 00001F30  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F34 00001F34  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F38 00001F38  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F3C 00001F3C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F40 00001F40  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F44 00001F44  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F48 00001F48  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F4C 00001F4C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F50 00001F50  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F54 00001F54  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F58 00001F58  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F5C 00001F5C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F60 00001F60  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F64 00001F64  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F68 00001F68  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F6C 00001F6C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F70 00001F70  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F74 00001F74  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F78 00001F78  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F7C 00001F7C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F80 00001F80  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F84 00001F84  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F88 00001F88  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F8C 00001F8C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F90 00001F90  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F94 00001F94  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004F98 00001F98  7C 51 43 A6 */	mtspr 0x111, r2
/* 80004F9C 00001F9C  7C 72 43 A6 */	mtspr 0x112, r3
/* 80004FA0 00001FA0  7C 93 43 A6 */	mtspr 0x113, r4
/* 80004FA4 00001FA4  7C 5A 02 A6 */	mfspr r2, 0x1a
/* 80004FA8 00001FA8  7C 9B 02 A6 */	mfspr r4, 0x1b
/* 80004FAC 00001FAC  7C 60 00 A6 */	mfmsr r3
/* 80004FB0 00001FB0  60 63 00 30 */	ori r3, r3, 0x30
/* 80004FB4 00001FB4  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 80004FB8 00001FB8  3C 60 80 32 */	lis r3, TRKInterruptHandler@h
/* 80004FBC 00001FBC  60 63 99 EC */	ori r3, r3, TRKInterruptHandler@l
/* 80004FC0 00001FC0  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 80004FC4 00001FC4  38 60 1D 00 */	li r3, 0x1d00
/* 80004FC8 00001FC8  4C 00 00 64 */	rfi
/* 80004FCC 00001FCC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004FD0 00001FD0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004FD4 00001FD4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004FD8 00001FD8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004FDC 00001FDC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004FE0 00001FE0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004FE4 00001FE4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004FE8 00001FE8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004FEC 00001FEC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004FF0 00001FF0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004FF4 00001FF4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004FF8 00001FF8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80004FFC 00001FFC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005000 00002000  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005004 00002004  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005008 00002008  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000500C 0000200C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005010 00002010  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005014 00002014  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005018 00002018  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000501C 0000201C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005020 00002020  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005024 00002024  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005028 00002028  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000502C 0000202C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005030 00002030  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005034 00002034  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005038 00002038  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000503C 0000203C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005040 00002040  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005044 00002044  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005048 00002048  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000504C 0000204C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005050 00002050  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005054 00002054  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005058 00002058  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000505C 0000205C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005060 00002060  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005064 00002064  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005068 00002068  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000506C 0000206C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005070 00002070  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005074 00002074  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005078 00002078  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000507C 0000207C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005080 00002080  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005084 00002084  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005088 00002088  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000508C 0000208C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005090 00002090  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005094 00002094  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005098 00002098  7C 51 43 A6 */	mtspr 0x111, r2
/* 8000509C 0000209C  7C 72 43 A6 */	mtspr 0x112, r3
/* 800050A0 000020A0  7C 93 43 A6 */	mtspr 0x113, r4
/* 800050A4 000020A4  7C 5A 02 A6 */	mfspr r2, 0x1a
/* 800050A8 000020A8  7C 9B 02 A6 */	mfspr r4, 0x1b
/* 800050AC 000020AC  7C 60 00 A6 */	mfmsr r3
/* 800050B0 000020B0  60 63 00 30 */	ori r3, r3, 0x30
/* 800050B4 000020B4  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 800050B8 000020B8  3C 60 80 32 */	lis r3, TRKInterruptHandler@h
/* 800050BC 000020BC  60 63 99 EC */	ori r3, r3, TRKInterruptHandler@l
/* 800050C0 000020C0  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 800050C4 000020C4  38 60 1E 00 */	li r3, 0x1e00
/* 800050C8 000020C8  4C 00 00 64 */	rfi
/* 800050CC 000020CC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800050D0 000020D0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800050D4 000020D4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800050D8 000020D8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800050DC 000020DC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800050E0 000020E0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800050E4 000020E4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800050E8 000020E8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800050EC 000020EC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800050F0 000020F0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800050F4 000020F4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800050F8 000020F8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800050FC 000020FC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005100 00002100  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005104 00002104  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005108 00002108  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000510C 0000210C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005110 00002110  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005114 00002114  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005118 00002118  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000511C 0000211C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005120 00002120  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005124 00002124  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005128 00002128  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000512C 0000212C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005130 00002130  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005134 00002134  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005138 00002138  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000513C 0000213C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005140 00002140  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005144 00002144  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005148 00002148  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000514C 0000214C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005150 00002150  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005154 00002154  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005158 00002158  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000515C 0000215C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005160 00002160  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005164 00002164  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005168 00002168  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000516C 0000216C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005170 00002170  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005174 00002174  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005178 00002178  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000517C 0000217C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005180 00002180  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005184 00002184  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005188 00002188  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8000518C 0000218C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005190 00002190  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005194 00002194  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 80005198 00002198  7C 51 43 A6 */	mtspr 0x111, r2
/* 8000519C 0000219C  7C 72 43 A6 */	mtspr 0x112, r3
/* 800051A0 000021A0  7C 93 43 A6 */	mtspr 0x113, r4
/* 800051A4 000021A4  7C 5A 02 A6 */	mfspr r2, 0x1a
/* 800051A8 000021A8  7C 9B 02 A6 */	mfspr r4, 0x1b
/* 800051AC 000021AC  7C 60 00 A6 */	mfmsr r3
/* 800051B0 000021B0  60 63 00 30 */	ori r3, r3, 0x30
/* 800051B4 000021B4  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 800051B8 000021B8  3C 60 80 32 */	lis r3, TRKInterruptHandler@h
/* 800051BC 000021BC  60 63 99 EC */	ori r3, r3, TRKInterruptHandler@l
/* 800051C0 000021C0  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 800051C4 000021C4  38 60 1F 00 */	li r3, 0x1f00
/* 800051C8 000021C8  4C 00 00 64 */	rfi

.global gTRKInterruptVectorTableEnd
gTRKInterruptVectorTableEnd:
/* 800051CC 000021CC  7C 08 02 A6 */	mflr r0
/* 800051D0 000021D0  90 01 00 04 */	stw r0, 4(r1)
/* 800051D4 000021D4  94 21 FF F8 */	stwu r1, -8(r1)
/* 800051D8 000021D8  48 32 55 AD */	bl __TRK_copy_vectors
/* 800051DC 000021DC  38 21 00 08 */	addi r1, r1, 8
/* 800051E0 000021E0  80 01 00 04 */	lwz r0, 4(r1)
/* 800051E4 000021E4  7C 08 03 A6 */	mtlr r0
/* 800051E8 000021E8  4E 80 00 20 */	blr
