#include "lbarq.h"

#include <placeholder.h>

#include <dolphin/ar.h>
#include <dolphin/os.h>
#include <baselib/debug.h>

typedef enum lbArqState {
    LB_ARQ_STATE_FREE = 0,
    LB_ARQ_STATE_PENDING = 1,
    LB_ARQ_STATE_DONE = 2,
} lbArqState;

typedef struct lbArqNode {
    /* 0x00 */ struct lbArqNode* next;
    /* 0x04 */ lbArqState state;
    /* 0x08 */ ARQRequest arq;
    /* 0x28 */ lbArqCallback callback;
    /* 0x2C */ void* callback_arg;
} lbArqNode;

typedef struct lbArqGlobal {
    /* 0x000 */ lbArqNode nodes[10];
    /* 0x1E0 */ lbArqNode* list[3];
} lbArqGlobal;

typedef struct lbArqHandle {
    /* 0x00 */ void* unk0;
    /* 0x04 */ lbArqNode* node;
} lbArqHandle;

/* 4316C0 */ lbArqGlobal lbArq_804316C0;

#pragma push
#pragma dont_inline on
static lbArqState lbArq_80014ABC(lbArqNode* arg0)
{
    return arg0->state;
}
#pragma pop

static void lbArq_80014AC4(lbArqHandle* handle)
{
    lbArqGlobal* global = &lbArq_804316C0;
    lbArqNode* node = handle->node;
    lbArqNode** prev;
    lbArqNode** tail;
    uintptr_t offset;
    BOOL intr;

    intr = OSDisableInterrupts();

    /* Remove from current list (indexed by state) */
    offset = node->state * 4;
    offset += 0x1E0;
    offset += (uintptr_t) global;
    prev = (lbArqNode**) offset;
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

void lbArq_80014BD0(unsigned int source, void* dest, size_t length,
                    lbArqCallback callback, void* callback_arg)
{
    u32 source_tmp;
    lbArqNode* rp_tmp;
    lbArqGlobal* global = &lbArq_804316C0;
    lbArqNode* rp;
    lbArqNode** tail;
    BOOL intr;
    lbArqNode** free_head;
    lbArqNode* tmp;

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

    rp_tmp = rp;
    source_tmp = source;
    ARQPostRequest(&rp->arq, (u32) rp_tmp, 1, 0, source_tmp, (uintptr_t) dest,
                   length, (ARQCallback) lbArq_80014AC4);

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
