#include "dolphin_trk_glue.h"

#include "MetroTRK/mem_TRK.h"
#include "MetroTRK/targimpl.h"
#include "MetroTRK/trk.h"

#include <dolphin/amcstubs/AmcExi2Stubs.h>
#include <dolphin/OdemuExi2/DebuggerDriver.h>
#include <dolphin/os/OSError.h>
#include <dolphin/os/OSThread.h>

static DBCommTable gDBCommTable = { NULL, NULL, NULL, NULL, NULL, NULL, NULL };

ASM void TRKLoadContext(OSContext* ctx, register u32 val)
{
#ifdef __MWERKS__ // clang-format off
        nofralloc

        lwz r0, OSContext.gprs[0](r3)
        lwz r1, OSContext.gprs[1](r3)
        lwz r2, OSContext.gprs[2](r3)
        lhz r5, OSContext.state(r3)
        rlwinm. r6, r5, 0, 0x1E, 0x1E
        beq L_802CC24C
        rlwinm r5, r5, 0, 0x1F, 0x1D
        sth r5, OSContext.state(r3)
        lmw r5, OSContext.gprs[5](r3)
        b L_802CC250
    L_802CC24C:
        lmw r13, OSContext.gprs[13](r3)
    L_802CC250:
        mr r31, r3
        mr r3, r4
        lwz r4, OSContext.cr(r31)
        mtcrf 0xFF, r4
        lwz r4, OSContext.lr(r31)
        mtlr r4
        lwz r4, OSContext.ctr(r31)
        mtctr r4
        lwz r4, OSContext.xer(r31)
        mtxer r4
        mfmsr r4
        rlwinm r4, r4, 0, 0x11, 0xF //Turn off external exceptions
        rlwinm r4, r4, 0, 0x1F, 0x1D //Turn off recoverable exception flag
        mtmsr r4
        mtsprg 1, r2
        lwz r4, OSContext.gprs[3](r31)
        mtsprg 2, r4
        lwz r4, OSContext.gprs[4](r31)
        mtsprg 3, r4
        lwz r2, OSContext.srr0(r31)
        lwz r4, OSContext.srr1(r31)
        lwz r31, OSContext.gprs[31](r31)
        b TRKInterruptHandler
    #endif // clang-format on
}

void TRKEXICallBack(short r3, OSContext* ctx)
{
    OSEnableScheduler();
    TRKLoadContext(ctx, 0x500);
}

int InitMetroTRKCommTable(int hwId)
{
    bool isStub;

    if (hwId == HARDWARE_NDEV) {
        isStub = Hu_IsStub();
        gDBCommTable.initialize_func = (DBCommInitFunc) DBInitComm;
        gDBCommTable.initinterrupts_func = (DBCommFunc) DBInitInterrupts;
        gDBCommTable.peek_func = (DBCommFunc) DBQueryData;
        gDBCommTable.read_func = (DBCommReadFunc) DBRead;
        gDBCommTable.write_func = (DBCommWriteFunc) DBWrite;
        gDBCommTable.open_func = (DBCommFunc) DBOpen;
        gDBCommTable.close_func = (DBCommFunc) DBClose;
        return isStub;
    } else {
        isStub = AMC_IsStub();
        gDBCommTable.initialize_func = (DBCommInitFunc) EXI2_Init;
        gDBCommTable.initinterrupts_func = (DBCommFunc) EXI2_EnableInterrupts;
        gDBCommTable.peek_func = (DBCommFunc) EXI2_Poll;
        gDBCommTable.read_func = (DBCommReadFunc) EXI2_ReadN;
        gDBCommTable.write_func = (DBCommWriteFunc) EXI2_WriteN;
        gDBCommTable.open_func = (DBCommFunc) EXI2_Reserve;
        gDBCommTable.close_func = (DBCommFunc) EXI2_Unreserve;
        return isStub;
    }
}

void TRKUARTInterruptHandler(void) {}

DSError TRKInitializeIntDrivenUART(u32 r3, u32 r4, u32 r5, void* r6)
{
    gDBCommTable.initialize_func(r6, TRKEXICallBack);
    return kNoError;
}

void EnableEXI2Interrupts(void)
{
    gDBCommTable.initinterrupts_func();
}

int TRKPollUART(void)
{
    return gDBCommTable.peek_func();
}

DSError TRK_ReadUARTN(void* bytes, u32 limit)
{
    int r3 = gDBCommTable.read_func(bytes, limit);
    return !r3 ? kNoError : kUARTError;
}

DSError TRK_WriteUARTN(const void* bytes, u32 length)
{
    int r3 = gDBCommTable.write_func(bytes, length);
    return !r3 ? kNoError : kUARTError;
}

void ReserveEXI2Port(void)
{
    gDBCommTable.open_func();
}

void UnreserveEXI2Port(void)
{
    gDBCommTable.close_func();
}

#pragma push
#pragma peephole off
void TRK_board_display(char* str)
{
    OSReport(str);
}
#pragma pop
