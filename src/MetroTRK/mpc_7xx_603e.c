#include "mpc_7xx_603e.h"

#include "MetroTRK/m7xx_m603e_reg.h"
#include "MetroTRK/ppc_targimpl.h"

static int const target_cpu_minor_type = 84;

ASM void TRKSaveExtended1Block(void)
{
#ifdef __MWERKS__ // clang-format off
        nofralloc

        lis       r2, gTRKCPUState@h
        ori       r2, r2, gTRKCPUState@l

        mfsr      r16, 0
        mfsr      r17, 1
        mfsr      r18, 2
        mfsr      r19, 3
        mfsr      r20, 4
        mfsr      r21, 5
        mfsr      r22, 6
        mfsr      r23, 7
        mfsr      r24, 8
        mfsr      r25, 9
        mfsr      r26, 10
        mfsr      r27, 11
        mfsr      r28, 12
        mfsr      r29, 13
        mfsr      r30, 14
        mfsr      r31, 15
        stmw      r16, ProcessorState_PPC.Extended1.SR[0](r2)

        mftb      r10, 268
        mftb      r11, 269
        mfspr     r12, 1008
        mfspr     r13, 1009

        mfspr     r14, 27

        mfspr     r15, 287
        mfspr     r16, 528
        mfspr     r17, 529
        mfspr     r18, 530
        mfspr     r19, 531
        mfspr     r20, 532
        mfspr     r21, 533
        mfspr     r22, 534
        mfspr     r23, 535
        mfspr     r24, 536
        mfspr     r25, 537
        mfspr     r26, 538
        mfspr     r27, 539
        mfspr     r28, 540
        mfspr     r29, 541
        mfspr     r30, 542
        mfspr     r31, 543
        stmw      r10, ProcessorState_PPC.Extended1.TBL(r2)

        mfspr     r22, 25
        mfspr     r23, 19
        mfspr     r24, 18
        mfspr     r25, 272
        mfspr     r26, 273
        mfspr     r27, 274
        mfspr     r28, 275

        li        r29, 0
        mfspr     r30, 1010
        mfspr     r31, 282
        stmw      r22, ProcessorState_PPC.Extended1.SDR1(r2)

        mfspr     r20, 912
        mfspr     r21, 913
        mfspr     r22, 914
        mfspr     r23, 915
        mfspr     r24, 916
        mfspr     r25, 917
        mfspr     r26, 918
        mfspr     r27, 919
        mfspr     r28, 920
        mfspr     r29, 921
        mfspr     r30, 922
        mfspr     r31, 923
        stmw      r20, ProcessorState_PPC.Extended1.GQR(r2)

        b         __7xx_specific_save

        mfspr     r16, 928
        mfspr     r17, 935
        mfspr     r18, 936
        mfspr     r19, 937
        mfspr     r20, 938
        mfspr     r21, 939
        mfspr     r22, 940
        mfspr     r23, 941
        mfspr     r24, 942
        mfspr     r25, 943
        mfspr     r26, 944
        mfspr     r27, 951
        mfspr     r28, 959
        mfspr     r29, 1014
        mfspr     r30, 1015
        mfspr     r31, 1023
        stmw      r16, ProcessorState_PPC.Extended1.UMMCR2(r2)

    __7xx_specific_save:

        mfspr     r19, 1013
        mfspr     r20, 953
        mfspr     r21, 954
        mfspr     r22, 957
        mfspr     r23, 958
        mfspr     r24, 955
        mfspr     r25, 952
        mfspr     r26, 956
        mfspr     r27, 1020
        mfspr     r28, 1021
        mfspr     r29, 1022
        mfspr     r30, 1019
        mfspr     r31, 1017
        stmw      r19, ProcessorState_PPC.Extended1.DABR(r2)

        b quit

        mfspr     r25, 976
        mfspr     r26, 977
        mfspr     r27, 978
        mfspr     r28, 979
        mfspr     r29, 980
        mfspr     r30, 981
        mfspr     r31, 982
        stmw      r25, ProcessorState_PPC.Extended1.DMISS(r2)

        mfdec     r31
        stw       r31, ProcessorState_PPC.Extended1.DEC(r2)
    quit:
        blr
    #endif // clang-format on
}

ASM void TRKRestoreExtended1Block(void)
{
#ifdef __MWERKS__ // clang-format off
        nofralloc

        lis       r2, gTRKCPUState@h
        ori       r2, r2, gTRKCPUState@l

        lis       r5, gTRKRestoreFlags@h
        ori       r5, r5, gTRKRestoreFlags@l
        lbz       r3, ProcessorRestoreFlags_PPC.TBR(r5)
        lbz       r6, ProcessorRestoreFlags_PPC.DEC(r5)

        li        r0, 0
        stb       r0, ProcessorRestoreFlags_PPC.TBR(r5)
        stb       r0, ProcessorRestoreFlags_PPC.DEC(r5)
        cmpwi     r3, 0
        beq       no_tbr_restore

        lwz       r24, ProcessorState_PPC.Extended1.TBL(r2)
        lwz       r25, ProcessorState_PPC.Extended1.TBU(r2)

        mtspr     TBR_TBL_WRITE, r24
        mtspr     TBR_TBU_WRITE, r25

    no_tbr_restore:

        lmw       r20, ProcessorState_PPC.Extended1.GQR(r2)
        mtspr     SPR_GQR0, r20
        mtspr     SPR_GQR1, r21
        mtspr     SPR_GQR2, r22
        mtspr     SPR_GQR3, r23
        mtspr     SPR_GQR4, r24
        mtspr     SPR_GQR5, r25
        mtspr     SPR_GQR6, r26
        mtspr     SPR_GQR7, r27
        mtspr     SPR_HID2, r28
        mtspr     SPR_DMAU, r30
        mtspr     SPR_DMAL, r31

        b         __603e_specific_restore

        lmw       r26, ProcessorState_PPC.Extended1.MMCR2(r2)
        mtspr     SPR_MMCR2, r26
        mtspr     SPR_BAMR, r27

        mtspr     SPR_MSSCR0, r29
        mtspr     SPR_MSSCR1, r30
        mtspr     SPR_PIR, r31

    __603e_specific_restore:

        lmw       r19, ProcessorState_PPC.Extended1.DABR(r2)
        mtspr     SPR_DABR, r19
        mtspr     SPR_PMC1, r20
        mtspr     SPR_PMC2, r21
        mtspr     SPR_PMC3, r22
        mtspr     SPR_PMC4, r23
        mtspr     SPR_SIA, r24
        mtspr     SPR_MMCR0, r25
        mtspr     SPR_MMCR1, r26

        mtspr     SPR_THRM1, r27
        mtspr     SPR_THRM2, r28
        mtspr     SPR_THRM3, r29

        mtspr     SPR_ICTC, r30
        mtspr     SPR_L2CR, r31

        b         __end_specific_restore

        cmpwi     r6, 0
        beq       no_dec_restore

        lwz       r26, ProcessorState_PPC.Extended1.DEC(r2)
        mtdec     r26

    no_dec_restore:

        lmw       r25, ProcessorState_PPC.Extended1.DMISS(r2)
        mtspr     SPR_DMISS, r25
        mtspr     SPR_DCMP, r26
        mtspr     SPR_HASH1, r27
        mtspr     SPR_HASH2, r28
        mtspr     SPR_IMISS, r29
        mtspr     SPR_ICMP, r30
        mtspr     SPR_RPA, r31

    __end_specific_restore:

        lmw       r16, ProcessorState_PPC.Extended1.SR[0](r2)
        mtsr      0, r16
        mtsr      1, r17
        mtsr      2, r18
        mtsr      3, r19
        mtsr      4, r20
        mtsr      5, r21
        mtsr      6, r22
        mtsr      7, r23
        mtsr      8, r24
        mtsr      9, r25
        mtsr      10, r26
        mtsr      11, r27
        mtsr      12, r28
        mtsr      13, r29
        mtsr      14, r30
        mtsr      15, r31

        lmw       r12, ProcessorState_PPC.Extended1.HID0(r2)
        mtspr     SPR_HID0, r12
        mtspr     SPR_HID1, r13
        mtspr     SPR_SRR1, r14
        mtspr     SPR_PVR, r15
        mtspr     SPR_IBAT0U, r16
        mtspr     SPR_IBAT0L, r17
        mtspr     SPR_IBAT1U, r18
        mtspr     SPR_IBAT1L, r19
        mtspr     SPR_IBAT2U, r20
        mtspr     SPR_IBAT2L, r21
        mtspr     SPR_IBAT3U, r22
        mtspr     SPR_IBAT3L, r23
        mtspr     SPR_DBAT0U, r24
        mtspr     SPR_DBAT0L, r25
        mtspr     SPR_DBAT1U, r26
        mtspr     SPR_DBAT1L, r27
        mtspr     SPR_DBAT2U, r28
        mtspr     SPR_DBAT2L, r29
        mtspr     SPR_DBAT3U, r30
        mtspr     SPR_DBAT3L, r31

        lmw       r22, ProcessorState_PPC.Extended1.SDR1(r2)
        mtspr     SPR_SDR1, r22
        mtspr     SPR_DAR, r23
        mtspr     SPR_DSISR, r24
        mtspr     SPR_SPRG0, r25
        mtspr     SPR_SPRG1, r26
        mtspr     SPR_SPRG2, r27
        mtspr     SPR_SPRG3, r28
        mtspr     SPR_IABR, r30
        mtspr     SPR_EAR, r31
        blr
    #endif // clang-format on
}
