#include "lbarq.h"

#include <dolphin/os.h>
#include <baselib/debug.h>

u32 lbArq_80014ABC(lbArqNode* arg0)
{
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

void lbArq_80014BD0(u32 source, void* dest, size_t length, lbArqCallback callback, void* callback_arg)
{
    lbArqGlobal* global = &lbArq_804316C0;
    lbArqNode* rp;
    lbArqNode** tail;
    lbArqNode** free_head;
    BOOL intr;

    DCInvalidateRange(dest, length);
    intr = OSDisableInterrupts();
    rp = global->list[0];
    free_head = &global->list[0];
    HSD_ASSERT(0x67, rp);
    *free_head = rp->next;
    rp->callback = callback;
    rp->callback_arg = callback_arg;

    tail = &global->list[1];
    while (*tail != NULL) {
        tail = &(*tail)->next;
    }
    *tail = rp;
    rp->next = NULL;
    rp->state = 1;

    ARQPostRequest(&rp->arq, (u32) rp, 1, 0, source, (u32) dest, length, (ARQCallback) lbArq_80014AC4);

    if (rp->callback == NULL) {
        OSRestoreInterrupts(intr);
        while (lbArq_80014ABC(rp) != 2) {}
        intr = OSDisableInterrupts();
        tail = &global->list[rp->state];
        while (*tail != rp) {
            tail = &(*tail)->next;
        }
        *tail = rp->next;
        while (*free_head != NULL) {
            free_head = &(*free_head)->next;
        }
        *free_head = rp;
        rp->next = NULL;
        rp->state = 0;
    }
    OSRestoreInterrupts(intr);
}

void lbArq_80014D2C(void)
{
    lbArqGlobal* global = &lbArq_804316C0;
    lbArqNode* nodes = (lbArqNode*) global;
    lbArqNode* node;
    int i;

    global->list[0] = NULL;
    global->list[1] = NULL;
    global->list[2] = NULL;
    global->list[0] = nodes;

    for (i = 0; i < 9; i++) {
        node = &nodes[i];
        node->next = node + 1;
        node->state = 0;
    }
    node->next = NULL;
    node->state = 0;

    PAD_STACK(8);
}
