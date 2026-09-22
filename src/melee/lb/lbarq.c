#include "lbarq.h"

#include <placeholder.h>

#include <dolphin/ar.h>
#include <dolphin/os.h>
#include <sysdolphin/baselib/debug.h>

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

/* 4316C0 */ lbArqGlobal lbArq_804316C0;

/// @todo Non-inlined function forces loop in ::lbArq_80014BD0 to yield to
///       interrupts. Pragma solution likely fake.
#ifdef __MWERKS__
#pragma push
#pragma dont_inline on
#endif
static lbArqState lbArq_80014ABC(lbArqNode* arg0)
{
    return arg0->state;
}
#ifdef __MWERKS__
#pragma pop
#endif

static void lbArq_80014AC4(ARQRequest* request)
{
    lbArqNode* node = request->owner;
    lbArqNode** prev;
    lbArqNode** tail;
    BOOL intr;

    intr = OSDisableInterrupts();

    /* Remove from current list (indexed by state) */
    prev = &lbArq_804316C0.list[node->state];
    while (*prev != node) {
        prev = &(*prev)->next;
    }
    *prev = node->next;

    /* Add to done list */
    tail = &lbArq_804316C0.list[LB_ARQ_STATE_DONE];
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
        prev = &lbArq_804316C0.list[node->state];
        while (*prev != node) {
            prev = &(*prev)->next;
        }
        *prev = node->next;

        /* Add to free list */
        tail = &lbArq_804316C0.list[LB_ARQ_STATE_FREE];
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
    lbArqNode* rp;
    lbArqNode** tail;
    BOOL intr;
    lbArqNode** free_head;
    lbArqNode* head;
    lbArqNode* owner;
    u32 aram;

    PAD_STACK(16);
    DCInvalidateRange(dest, length);
    intr = OSDisableInterrupts();
    head = lbArq_804316C0.list[LB_ARQ_STATE_FREE];
    rp = head;
    free_head = &lbArq_804316C0.list[LB_ARQ_STATE_FREE];
    HSD_ASSERT(0x67, rp);
    *free_head = rp->next;
    rp->callback = callback;
    rp->callback_arg = callback_arg;

    tail = &lbArq_804316C0.list[LB_ARQ_STATE_PENDING];
    while (*tail != NULL) {
        tail = &(*tail)->next;
    }
    *tail = rp;
    rp->next = NULL;
    rp->state = LB_ARQ_STATE_PENDING;

    owner = rp;
    aram = source;
    ARQPostRequest(&rp->arq, owner, ARQ_TYPE_ARAM_TO_MRAM, ARQ_PRIORITY_LOW,
                   aram, (uintptr_t) dest, length, lbArq_80014AC4);

    if (rp->callback == NULL) {
        OSRestoreInterrupts(intr);
        while (lbArq_80014ABC(rp) != LB_ARQ_STATE_DONE) {
        }
        intr = OSDisableInterrupts();
        tail = &lbArq_804316C0.list[rp->state];
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
