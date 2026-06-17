#include "lbarq.h"

#include <dolphin/os.h>
#include <baselib/debug.h>

#pragma push
#pragma dont_inline on
lbArqState lbArq_80014ABC(lbArqNode* arg0)
{
    return arg0->state;
}
#pragma pop

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

    /* Add to done list */
    tail = &global->list[LB_ARQ_STATE_DONE];
    while (*tail != NULL) {
        tail = &(*tail)->next;
    }
    *tail = node;
    node->next = NULL;
    node->state = LB_ARQ_STATE_DONE;

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

        /* Add to free list */
        tail = &global->list[LB_ARQ_STATE_FREE];
        while (*tail != NULL) {
            tail = &(*tail)->next;
        }
        *tail = node;
        node->next = NULL;
        node->state = LB_ARQ_STATE_FREE;

        OSRestoreInterrupts(intr);
    }
}

void lbArq_80014BD0(u32 source, void* dest, size_t length,
                    lbArqCallback callback, void* callback_arg)
{
    lbArqGlobal* global = &lbArq_804316C0;
    lbArqNode* rp;
    lbArqNode* tmp;
    lbArqNode** tail;
    lbArqNode** free_head;
    BOOL intr;

    PAD_STACK(16);
    DCInvalidateRange(dest, length);
    intr = OSDisableInterrupts();
    tmp = global->list[LB_ARQ_STATE_FREE];
    rp = tmp;
    free_head = &global->list[LB_ARQ_STATE_FREE];
    HSD_ASSERT(0x67, rp);
    *free_head = rp->next;
    rp->callback = callback;
    rp->callback_arg = callback_arg;

    tail = &global->list[LB_ARQ_STATE_PENDING];
    while (*tail != NULL) {
        tail = &(*tail)->next;
    }
    *tail = rp;
    rp->next = NULL;
    rp->state = LB_ARQ_STATE_PENDING;

    ARQPostRequest(&rp->arq, (u32) rp, 1, 0, source, (u32) dest, length,
                   (ARQCallback) lbArq_80014AC4);

    if (rp->callback == NULL) {
        OSRestoreInterrupts(intr);
        while (lbArq_80014ABC(rp) != LB_ARQ_STATE_DONE) {
        }
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
        rp->state = LB_ARQ_STATE_FREE;
    }
    OSRestoreInterrupts(intr);
}

void lbArq_80014D2C(void)
{
    lbArqGlobal* global = &lbArq_804316C0;
    lbArqNode* nodes = global->nodes;
    lbArqNode* node;
    int i;

    global->list[LB_ARQ_STATE_FREE] = NULL;
    global->list[LB_ARQ_STATE_PENDING] = NULL;
    global->list[LB_ARQ_STATE_DONE] = NULL;
    global->list[LB_ARQ_STATE_FREE] = nodes;

    for (i = 0; i < 9; i++) {
        node = &nodes[i];
        node->next = node + 1;
        node->state = LB_ARQ_STATE_FREE;
    }
    node->next = NULL;
    node->state = LB_ARQ_STATE_FREE;

    PAD_STACK(8);
}
