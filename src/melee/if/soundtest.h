#ifndef _SOUNDTEST_H_
#define _SOUNDTEST_H_

#include <platform.h>

#include "if/forward.h"

#include "if/types.h"

#include "mn/forward.h"

/* 2FF7DC */ void un_802FF7DC(void);
/* 2FF884 */ bool un_802FF884(char*);
/* 2FFCC8 */ bool fn_802FFCC8(void);
/* 2FFCD0 */ void un_802FFCD0(int, void*);
/* 2FFD94 */ void un_802FFD94(int a, void* b, soundtest_callback c);
/* 2FFEE0 */ void un_802FFEE0(s32*);
/* 2FFF2C */ void un_802FFF2C(StartMeleeData*);
/* 301BA8 */ void un_80301BA8(void* out);
/* 301C64 */ void un_80301C64(un_80301C64_t*);

#endif
