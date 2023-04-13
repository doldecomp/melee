#ifndef DOLPHIN_AXFX_AXFX_H
#define DOLPHIN_AXFX_AXFX_H

#include <platform.h>

any_t AXFXAllocFunction(size_t size);
void AXFXFreeFunction(any_t ptr);
void AXFXSetHooks(any_t (*alloc_hook)(size_t), void (*free_hook)(any_t));

#endif
