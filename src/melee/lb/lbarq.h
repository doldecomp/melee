#ifndef GALE01_014ABC
#define GALE01_014ABC

#include <stddef.h>

typedef void (*lbArqCallback)(void* arg);

void lbArq_80014BD0(unsigned int, void*, size_t, lbArqCallback, void*);
void lbArq_80014D2C(void);

#endif
