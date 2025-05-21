#ifndef _METROTRK_M7XX_M603E_REG_H
#define _METROTRK_M7XX_M603E_REG_H

#include <platform.h>

#include "MetroTRK/ppc_reg.h"

typedef struct Extended1_PPC_6xx_7xx {
    /* 0x000 */ u32 SR[16];
    /* 0x040 */ u32 TBL;
    /* 0x044 */ u32 TBU;
    /* 0x048 */ u32 HID0;
    /* 0x04C */ u32 HID1;
    /* 0x050 */ u32 MSR;
    /* 0x054 */ u32 PVR;
    /* 0x058 */ u32 IBAT0U;
    /* 0x05C */ u32 IBAT0L;
    /* 0x060 */ u32 IBAT1U;
    /* 0x064 */ u32 IBAT1L;
    /* 0x068 */ u32 IBAT2U;
    /* 0x06C */ u32 IBAT2L;
    /* 0x070 */ u32 IBAT3U;
    /* 0x074 */ u32 IBAT3L;
    /* 0x078 */ u32 DBAT0U;
    /* 0x07C */ u32 DBAT0L;
    /* 0x080 */ u32 DBAT1U;
    /* 0x084 */ u32 DBAT1L;
    /* 0x088 */ u32 DBAT2U;
    /* 0x08C */ u32 DBAT2L;
    /* 0x090 */ u32 DBAT3U;
    /* 0x094 */ u32 DBAT3L;
    /* 0x098 */ u32 DMISS;
    /* 0x09C */ u32 DCMP;
    /* 0x0A0 */ u32 HASH1;
    /* 0x0A4 */ u32 HASH2;
    /* 0x0A8 */ u32 IMISS;
    /* 0x0AC */ u32 ICMP;
    /* 0x0B0 */ u32 RPA;
    /* 0x0B4 */ u32 SDR1;
    /* 0x0B8 */ u32 DAR;
    /* 0x0BC */ u32 DSISR;
    /* 0x0C0 */ u32 SPRG0;
    /* 0x0C4 */ u32 SPRG1;
    /* 0x0C8 */ u32 SPRG2;
    /* 0x0CC */ u32 SPRG3;
    /* 0x0D0 */ u32 DEC;
    /* 0x0D4 */ u32 IABR;
    /* 0x0D8 */ u32 EAR;
    /* 0x0DC */ u32 DABR;
    /* 0x0E0 */ u32 PMC1;
    /* 0x0E4 */ u32 PMC2;
    /* 0x0E8 */ u32 PMC3;
    /* 0x0EC */ u32 PMC4;
    /* 0x0F0 */ u32 SIA;
    /* 0x0F4 */ u32 MMCR0;
    /* 0x0F8 */ u32 MMCR1;
    /* 0x0FC */ u32 THRM1;
    /* 0x100 */ u32 THRM2;
    /* 0x104 */ u32 THRM3;
    /* 0x108 */ u32 ICTC;
    /* 0x10C */ u32 L2CR;
    /* 0x110 */ u32 UMMCR2;
    /* 0x114 */ u32 UBAMR;
    /* 0x118 */ u32 UMMCR0;
    /* 0x11C */ u32 UPMC1;
    /* 0x120 */ u32 UPMC2;
    /* 0x124 */ u32 USIA;
    /* 0x128 */ u32 UMMCR1;
    /* 0x12C */ u32 UPMC3;
    /* 0x130 */ u32 UPMC4;
    /* 0x134 */ u32 USDA;
    /* 0x138 */ u32 MMCR2;
    /* 0x13C */ u32 BAMR;
    /* 0x140 */ u32 SDA;
    /* 0x144 */ u32 MSSCR0;
    /* 0x148 */ u32 MSSCR1;
    /* 0x14C */ u32 PIR;
    /* 0x150 */ u32 exceptionID;
    /* 0x154 */ u32 GQR[8];
    /* 0x158 */ u32 HID_G;
    /* 0x15C */ u32 WPAR;
    /* 0x160 */ u32 DMA_U;
    /* 0x164 */ u32 DMA_L;
} Extended1_PPC_6xx_7xx; // size = 0x168

#define DS_EXTENDED1_MIN_REGISTER_6xx_7xx 0
#define DS_EXTENDED1_MAX_REGISTER_6xx_7xx                                     \
    (sizeof(Extended1_PPC_6xx_7xx) / sizeof(Extended1Type) - 1)

typedef struct Extended2_PPC_6xx_7xx {
    /* 0x00 */ u32 PSR[32][2];
} Extended2_PPC_6xx_7xx; // size = 0x100

typedef struct ProcessorState_PPC_6xx_7xx {
    /* 0x000 */ Default_PPC Default;
    /* 0x094 */ Float_PPC Float;
    /* 0x1A0 */ Extended1_PPC_6xx_7xx Extended1;
    /* 0x2A0 */ Extended2_PPC_6xx_7xx Extended2;
    /* 0x2A4 */ DefaultType transport_handler_saved_ra;
} ProcessorState_PPC_6xx_7xx; // size = 0x2A8

typedef ProcessorState_PPC_6xx_7xx ProcessorState_PPC;

#endif