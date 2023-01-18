#ifndef RUNTIME_GECKO_SETJMP_H
#define RUNTIME_GECKO_SETJMP_H

#include <Runtime/platform.h>

void longjmp(register* env, register int val);
int __setjmp(register* env);

#endif
