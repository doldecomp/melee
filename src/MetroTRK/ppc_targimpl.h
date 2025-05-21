#ifndef _METROTRK_PPC_TARGIMPL_H
#define _METROTRK_PPC_TARGIMPL_H

#include <platform.h>

#include "MetroTRK/m7xx_m603e_reg.h"
#include "MetroTRK/ppc_reg.h"
#include "MetroTRK/trk.h"

typedef struct TRKState_PPC {
    /* 0x00 */ DefaultType GPR[32];
    /* 0x80 */ DefaultType LR;
    /* 0x84 */ DefaultType CTR;
    /* 0x88 */ DefaultType XER;
    /* 0x8C */ Extended1Type MSR;
    /* 0x90 */ Extended1Type DAR;
    /* 0x94 */ Extended1Type DSISR;
    /* 0x98 */ bool stopped;
    /* 0x9C */ bool inputActivated;
    /* 0xA0 */ u8* inputPendingPtr;
} TRKState_PPC; // size = 0xA4

extern TRKState_PPC gTRKState;

typedef struct ProcessorRestoreFlags_PPC {
    /* 0x00 */ u8 TBR;
    /* 0x01 */ u8 DEC;
    /* 0x02 */ u8 linker_padding[9 - 2];
} ProcessorRestoreFlags_PPC; // size = 0x09

extern ProcessorRestoreFlags_PPC gTRKRestoreFlags;
extern ProcessorState_PPC gTRKCPUState;

u32 __TRK_get_MSR(void);
void __TRK_set_MSR(register u32 val);
u32 __TRK_get_PVR(void);
u32 __TRK_get_IBAT0U(void);
u32 __TRK_get_IBAT0L(void);
u32 __TRK_get_IBAT1U(void);
u32 __TRK_get_IBAT1L(void);
u32 __TRK_get_IBAT2U(void);
u32 __TRK_get_IBAT2L(void);
u32 __TRK_get_IBAT3U(void);
u32 __TRK_get_IBAT3L(void);
u32 __TRK_get_DBAT0U(void);
u32 __TRK_get_DBAT0L(void);
u32 __TRK_get_DBAT1U(void);
u32 __TRK_get_DBAT1L(void);
u32 __TRK_get_DBAT2U(void);
u32 __TRK_get_DBAT2L(void);
u32 __TRK_get_DBAT3U(void);
u32 __TRK_get_DBAT3L(void);

DSError TRKPPCAccessSPR(void* srcDestPtr, u32 spr, bool read);
DSError TRKPPCAccessPairedSingleRegister(void* srcDestPtr, u32 psr, bool read);
DSError TRKPPCAccessFPRegister(void* srcDestPtr, u32 fpr, bool read);
DSError TRKPPCAccessSpecialReg(void* srcDestPtr, u32* instructionData,
                               bool read);
void TRKPostInterruptEvent(void);
u32 ConvertAddress(u32);

#endif
