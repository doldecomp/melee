#ifndef GALE01_014ABC
#define GALE01_014ABC

#include <dolphin/ar.h>
#include <placeholder.h>
#include <platform.h>

typedef void (*lbArqCallback)(void* arg);

typedef struct lbArqNode {
    /* 0x00 */ struct lbArqNode* next;
    /* 0x04 */ u32 state;
    /* 0x08 */ ARQRequest arq;
    /* 0x28 */ lbArqCallback callback;
    /* 0x2C */ void* callback_arg;
} lbArqNode;

typedef struct lbArqGlobal {
    /* 0x000 */ u8 pad[0x1E0];
    /* 0x1E0 */ lbArqNode* list[3];
} lbArqGlobal;

typedef struct lbArqHandle {
    /* 0x00 */ void* unk0;
    /* 0x04 */ lbArqNode* node;
} lbArqHandle;

extern lbArqGlobal lbArq_804316C0;

/* 014ABC */ s32 lbArq_80014ABC(UNK_T);
/* 014AC4 */ void lbArq_80014AC4(lbArqHandle* handle);
/* 014BD0 */ void lbArq_80014BD0(u32, void*, size_t, UNK_T, UNK_T);
/* 014D2C */ void lbArq_80014D2C(void);

#endif
