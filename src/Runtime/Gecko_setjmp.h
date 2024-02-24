#ifndef RUNTIME_GECKO_SETJMP_H
#define RUNTIME_GECKO_SETJMP_H

#include <platform.h>

#include <placeholder.h>

int __setjmp(void* env, UNK_T, UNK_T);
void longjmp(void* env, int val);

#endif
