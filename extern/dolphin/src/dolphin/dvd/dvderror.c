#include "__os.h"

#include <dolphin/os/OSRtc.h>
#include <dolphin/types.h>

u32 ErrorTable[16] = { 0x00000000, 0x00023A00, 0x00062800, 0x00030200,
                       0x00031100, 0x00052000, 0x00052001, 0x00052100,
                       0x00052400, 0x00052401, 0x00052402, 0x000B5A01,
                       0x00056300, 0x00020401, 0x00020400, 0x00040800 };

static u8 ErrorCode2Num(u32 errorCode)
{
    size_t i;

    for (i = 0; i < ARRAY_SIZE(ErrorTable); i++) {
        if (errorCode == ErrorTable[i]) {
            return i;
        }
    }

    return 29;
}

void __DVDStoreErrorCode(u32 errCode)
{
    u8 storedCode;
    u8* sramPtr;
    u32 upperByte;

    if (errCode == 0x1234567) {
        storedCode = -1;
    } else if (errCode == 0x1234568) {
        storedCode = -2;
    } else {
        upperByte = errCode >> 24;
        storedCode = ErrorCode2Num(errCode & 0xffffff);
        if (errCode >> 24 >= 6) {
            upperByte = 6;
        }
        storedCode += upperByte * 30;
    }

    sramPtr = (u8*) __OSLockSramEx();
    sramPtr[36] = storedCode;
    __OSUnlockSramEx(1);
}
