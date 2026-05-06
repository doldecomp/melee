#ifndef _DOLPHIN_DOLFORMAT_H_
#define _DOLPHIN_DOLFORMAT_H_

#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif

// Maximum number of segments allowed
#define DOL_MAX_TEXT 7
#define DOL_MAX_DATA 11

typedef struct DolImage
{
    u8 *textData[DOL_MAX_TEXT];
    u8 *dataData[DOL_MAX_DATA];
    u32 text[DOL_MAX_TEXT];
    u32 data[DOL_MAX_DATA];
    u32 textLen[DOL_MAX_TEXT];
    u32 dataLen[DOL_MAX_DATA];
    u32 bss;
    u32 bssLen;
    u32 entry;
    u8 padding[28];
} DolImage;

void *DOLLoadImage(u8 *buffer, BOOL verbose);
void DOLRunApp(void *entryPoint);

#ifdef __cplusplus
}
#endif

#endif
