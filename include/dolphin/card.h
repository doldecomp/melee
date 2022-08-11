#ifndef DOLPHIN_CARD_H
#define DOLPHIN_CARD_H

#include <dolphin/types.h>

s32 CARDClose(void *);
s32 CARDOpen(s32, s32, void *);
s32 CARDWrite(void*, u8*, u32, s32); 
s32 CARDRead(void*, u8*, u32, s32);  
s32 CARDFastOpen(s32, s32, void*);  

#endif