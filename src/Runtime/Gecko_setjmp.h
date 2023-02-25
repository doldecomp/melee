#ifndef RUNTIME_GECKO_SETJMP_H
#define RUNTIME_GECKO_SETJMP_H

#include <Runtime/platform.h>

void longjmp(unk_t env, int val);
int __setjmp(unk_t env, unk_t, unk_t);

#endif
