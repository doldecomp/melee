#ifndef _DOLPHIN_SIPRIV
#define _DOLPHIN_SIPRIV

#include <platform.h>

#include <dolphin/os.h>

typedef void (*SICallback)(s32 chan, u32 sr, OSContext* context);
typedef void (*SITypeAndStatusCallback)(s32 chan, u32 type);

typedef struct SIPacket {
    s32 chan;
    void* output;
    u32 outputBytes;
    void* input;
    u32 inputBytes;
    SICallback callback;
    OSTime fire;
} SIPacket;

void SIInit(void);
u32 SIGetStatus(s32 chan);

bool SIBusy(void);
bool SIIsChanBusy(s32 chan);

bool SITransfer(s32 chan, void* output, u32 outputBytes, void* input,
                u32 inputBytes, SICallback callback, OSTime delay);
u32 SISync(void);

void SISetCommand(s32 chan, u32 command);
u32 SIGetCommand(s32 chan);
void SITransferCommands(void);
u32 SISetXY(u32 x, u32 y);
u32 SIEnablePolling(u32 poll);
u32 SIDisablePolling(u32 poll);
bool SIGetResponse(s32 chan, void* data);

bool SIRegisterPollingHandler(__OSInterruptHandler handler);
bool SIUnregisterPollingHandler(__OSInterruptHandler handler);

u32 SIGetType(s32 chan);
u32 SIGetTypeAsync(s32 chan, SITypeAndStatusCallback callback);
u32 SIDecodeType(u32 type);

#endif // _DOLPHIN_SIPRIV
