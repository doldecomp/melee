#ifndef DOLPHIN_AXFX_AXFX_H
#define DOLPHIN_AXFX_AXFX_H

#include <platform.h>

void* AXFXAllocFunction(size_t size);
void AXFXFreeFunction(void* ptr);
void AXFXSetHooks(void* (*alloc_hook)(size_t), void (*free_hook)(void*));

#endif
