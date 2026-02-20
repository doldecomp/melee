#include "lbarq.h"

#include <dolphin/os.h>

u32 lbArq_80014ABC(lbArqNode* arg0) {
    return arg0->state;
}

void lbArq_80014AC4(lbArqHandle* handle)
{
    lbArqGlobal* global = &lbArq_804316C0;
    lbArqNode* node = handle->node;
    lbArqNode** prev;
    lbArqNode** tail;
    BOOL intr;

    intr = OSDisableInterrupts();

    /* Remove from current list (indexed by state) */
    prev = &global->list[node->state];
    while (*prev != node) {
        prev = &(*prev)->next;
    }
    *prev = node->next;

    /* Add to done list (list[2]) */
    tail = &global->list[2];
    while (*tail != NULL) {
        tail = &(*tail)->next;
    }
    *tail = node;
    node->next = NULL;
    node->state = 2;

    OSRestoreInterrupts(intr);

    /* Call callback if present */
    if (node->callback != NULL) {
        node->callback(node->callback_arg);

        intr = OSDisableInterrupts();

        /* Remove from current list again */
        prev = &global->list[node->state];
        while (*prev != node) {
            prev = &(*prev)->next;
        }
        *prev = node->next;

        /* Add to free list (list[0]) */
        tail = &global->list[0];
        while (*tail != NULL) {
            tail = &(*tail)->next;
        }
        *tail = node;
        node->next = NULL;
        node->state = 0;

        OSRestoreInterrupts(intr);
    }
}

/// #lbArq_80014BD0

/// #lbArq_80014D2C
