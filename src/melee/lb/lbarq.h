#ifndef GALE01_014ABC
#define GALE01_014ABC

#include <placeholder.h>
#include <platform.h>

#include <dolphin/ar.h>

typedef void (*lbArqCallback)(void* arg);

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

/* 014ABC */ lbArqState lbArq_80014ABC(lbArqNode* arg0);
/* 014AC4 */ void lbArq_80014AC4(lbArqHandle* handle);
/* 014BD0 */ void lbArq_80014BD0(u32, void*, size_t, lbArqCallback, void*);
/* 014D2C */ void lbArq_80014D2C(void);

#endif
