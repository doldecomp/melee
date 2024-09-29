#include "axdriver.static.h"

#include <sysdolphin/baselib/axdriver.h>
#include <sysdolphin/baselib/debug.h>

u8* AXDriverAlloc(s32 size)
{
    u8* ptr = &AXDriver_804D77D4[axfxallocsize];

    // increment the size by the amount we will be indexing to.
    axfxallocsize += size;

    // size exceeds the max allowed; the pointer that we return would be
    // outside the heap. Raise an assert.
    if (axfxallocsize >= axfxmaxsize) {
        __assert(AXDriver_80408140, 78, AXDriver_8040814C);
    }
    return ptr;
}

void AXDriverFree(void* ptr) {}

void AXDriverUnlink(HSD_SM* v, HSD_SM** head)
{
    HSD_SM* p;
    HSD_SM* n;

    if (v != NULL) {
        p = v->prev;
        n = v->next;
        v->next = NULL;
        v->prev = NULL;
        if (p != NULL) {
            p->next = n;
        }
        if (n != NULL) {
            n->prev = p;
        }
        if (*head == v) {
            *head = n;
        }
        if (*head == v) {
            __assert(AXDriver_80408140, 113, AXDriver_80408168);
        }
    }
}

/// #AXDriverKeyOff

/// #HSD_AudioSFXKeyOffAll

/// #HSD_AudioSFXKeyOffTrack

/// #AXDriver_8038BF6C

/// #fn_8038C678

/// #AXDriver_8038C6C0

/// #fn_8038CC1C

/// #fn_8038CEA4

/// #fn_8038CF48

/// #AXDriver_8038CFF4

/// #AXDriver_8038D2B4

/// #AXDriver_8038D3B8

/// #AXDriver_8038D4E4

/// #AXDriver_8038D5B4

/// #AXDriver_8038D914

/// #AXDriver_8038D9D8

void fn_8038DA5C(s32 arg0)
{
    if (arg0 != -1) {
        AXDriver_804D77EC = 1;
    }
}

/// #AXDriver_8038DA70

/// #AXDriver_8038DCFC

/// #AXDriverSetupAux

/// #AXDriver_8038E034

/// #AXDriver_8038E30C

/// #AXDriver_8038E37C

/// #AXDriver_8038E498

extern s32 AXDriver_804D77C8;

s32 AXDriver_8038E5D4(void)
{
    return AXDriver_804D77C8;
}

extern s32 AXDriver_804D77D0;

s32 AXDriver_8038E5DC(void)
{
    return AXDriver_804D77D0;
}

/// #AXDriver_8038E5E4

/// #AXDriver_8038E6C0

/// #AXDriver_8038E768

/// #AXDriver_8038E844

/// #AXDriver_8038E8EC

/// #AXDriver_8038E968

/// #AXDriver_8038E9A8

/// #AXDriver_8038E9E0

/// #AXDriver_8038EA18
