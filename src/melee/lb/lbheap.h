#ifndef MELEE_LB_HEAP_H
#define MELEE_LB_HEAP_H

#include <placeholder.h>
#include <platform.h>

/* 0158D0 */ void lbHeap_800158D0(int, int);
/* 0158E8 */ int lbHeap_800158E8(int);
/* 015900 */ void lbHeap_80015900(void);
/* 015BB8 */ bool lbHeap_80015BB8(int);
/* 015BD0 */ void* lbHeap_80015BD0(int heap_id, size_t size);
/* 015CA8 */ void lbHeap_80015CA8(int, void*);
/* 015D6C */ int lbHeap_80015D6C(u32 heap0, void (*cb)(u32), u32 heap1);
/* 015DF8 */ void lbHeap_80015DF8(void);
/* 015F3C */ void lbHeap_80015F3C(void);

#endif
