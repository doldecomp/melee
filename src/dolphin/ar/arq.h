#ifndef DOLPHIN_AR_ARQ_H
#define DOLPHIN_AR_ARQ_H

#include <platform.h>

#define ARQ_CHUNK_SIZE_DEFAULT 4096

typedef enum ARQType {
    ARQ_TYPE_MRAM_TO_ARAM,
    ARQ_TYPE_ARAM_TO_MRAM,
} ARQType;

typedef enum ARQPrio {
    ARQ_PRIORITY_LOW,
    ARQ_PRIORITY_HIGH,
} ARQPrio;

typedef struct ARQRequest ARQRequest;

typedef void (*ARQCallback)(ARQRequest*);

struct ARQRequest {
    ARQRequest* next;
    u32 owner;
    u32 type;
    ARQPrio priority;
    u32 source;
    u32 dest;
    size_t length;
    ARQCallback callback;
};

void ARQInit(void);
void ARQReset(void);
void ARQPostRequest(ARQRequest* task, u32 owner, ARQType type,
                    ARQPrio priority, u32 source, u32 dest, size_t length,
                    ARQCallback callback);
size_t ARQGetChunkSize(void);

void __ARQPopTaskQueueHi(void);
void __ARQServiceQueueLo(void);
void __ARQCallbackHack(ARQRequest*);
void __ARQInitTempQueue(void);
void __ARQPushTempQueue(ARQRequest* task);
void __ARQInterruptServiceRoutine(void);

#endif // DOLPHIN_AR_ARQ_H
