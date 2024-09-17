#include <platform.h>
#include <placeholder.h>

#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSSerial.h>
#include <dolphin/os/OSTime.h>
#include <dolphin/sipriv.h>

extern UNK_T OSSerial_804D73C8;
extern UNK_T VIGetCurrentLine(UNK_PARAMS);

static bool SIGetResponseRaw(s32 chan);
static void GetTypeCallback(s32 chan, u32 error, OSContext* context);
static bool __SITransfer(void);
static bool SIEnablePollingInterrupt(bool enable);

extern struct {
    enum_t status;
    u32 xy;
    s32 _[0x20 - 0x8];
} Si;

bool SIBusy(void)
{
    if (Si.status != -1) {
        return true;
    }

    return false;
}

extern struct {
    s32 x0;
    u8 pad[32 - 4];
} Packet[];

bool SIIsChanBusy(s32 status)
{
    bool result = true;

    if (Packet[status].x0 == -1 && Si.status != status) {
        result = false;
    }

    return result;
}

static void CompleteTransfer(void)
{
    NOT_IMPLEMENTED;
}

static void SIInterruptHandler(void)
{
    NOT_IMPLEMENTED;
}

static bool SIEnablePollingInterrupt(bool enable)
{
    NOT_IMPLEMENTED;
}

bool SIRegisterPollingHandler(__OSInterruptHandler handler)
{
    NOT_IMPLEMENTED;
}

bool SIUnregisterPollingHandler(__OSInterruptHandler handler)
{
    NOT_IMPLEMENTED;
}

void SIInit(void)
{
    NOT_IMPLEMENTED;
}

static bool __SITransfer(void)
{
    NOT_IMPLEMENTED;
}

u32 SIGetStatus(s32 chan)
{
    NOT_IMPLEMENTED;
}

extern volatile struct {
    u32 command, x4, x8;
} SIRegs[] AT_ADDRESS(0xCC006400);

void SISetCommand(s32 index, u32 value)
{
    SIRegs[index].command = value;
}

void SITransferCommands(void)
{
    SIRegs[4].x8 = 0x80000000;
}

u32 SISetXY(u32 x, u32 y)
{
    bool intr;
    u32 temp_r4 = (x << 0x10);
    temp_r4 |= (y << 8);
    intr = OSDisableInterrupts();
    Si.xy &= 0xFC0000FF;
    Si.xy |= temp_r4;
    temp_r4 = Si.xy;
    OSRestoreInterrupts(intr);
    return temp_r4;
}

u32 SIEnablePolling(u32 poll)
{
    NOT_IMPLEMENTED;
}

u32 SIDisablePolling(u32 poll)
{
    NOT_IMPLEMENTED;
}

bool SIGetResponseRaw(s32 chan)
{
    NOT_IMPLEMENTED;
}

bool SIGetResponse(s32 chan, void* data)
{
    NOT_IMPLEMENTED;
}

static void AlarmHandler(void)
{
    NOT_IMPLEMENTED;
}

bool SITransfer(s32 chan, void* output, u32 outputBytes, void* input,
                u32 inputBytes, SICallback callback, OSTime delay)
{
    NOT_IMPLEMENTED;
}

void GetTypeCallback(s32 chan, u32 error, OSContext* context)
{
    NOT_IMPLEMENTED;
}

u32 SIGetType(s32 arg0)
{
    NOT_IMPLEMENTED;
}

u32 SIGetTypeAsync(s32 chan, SITypeAndStatusCallback callback)
{
    NOT_IMPLEMENTED;
}
