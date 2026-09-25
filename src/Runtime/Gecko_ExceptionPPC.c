#include "Gecko_ExceptionPPC.h"

#include "platform.h"

typedef union MWE_GeckoVector64 {
    f64 d;
    f32 f[2];
} MWE_GeckoVector64;

typedef struct GeckoFPRContext {
    f64 d;
    MWE_GeckoVector64 v;
} GeckoFPRContext;

typedef struct ThrowContext {
    GeckoFPRContext FPR[32];
    s32 GPR[32];
    s32 CR;
    char* SP;
    char* FP;
    char* throwSP;
    char* returnaddr;
    char* throwtype;
    void* location;
    void* dtor;
    void* catchinfo;
} ThrowContext;

typedef struct ProcessInfo {
    __eti_init_info* exception_info;
    char* TOC;
    int active;
} ProcessInfo;

static ProcessInfo fragment_info[1];

int __register_fragment(struct __eti_init_info* info, char* TOC)
{
    ProcessInfo* f;
    int i;

    for (i = 0, f = fragment_info; i < 1; ++i, ++f) {
        if (f->active == 0) {
            f->exception_info = info;
            f->TOC = TOC;
            f->active = 1;
            return i;
        }
    }

    return -1;
}

void __unregister_fragment(int fragmentID)
{
    ProcessInfo* f;
    if (fragmentID >= 0 && fragmentID < 1) {
        f = &fragment_info[fragmentID];
        f->exception_info = 0;
        f->TOC = 0;
        f->active = 0;
    }
}

#ifdef MWERKS_GEKKO
static asm void ExPPC_LongJump(register ThrowContext* context,
                               register void* newRTOC, register void* newPC)
{
    // clang-format off
    nofralloc

    mr r8, newPC
    mr RTOC, newRTOC
    lwz    r0, context->CR
    mtcrf 255, r0

    lmw r13, context->GPR[13]

    la r7, context->FPR[14].v
    psq_lx fp14, 0, r7, 0, 0
    lfd fp14, context->FPR[14].d

    la r7, context->FPR[15].v
    psq_lx fp15, 0, r7, 0, 0
    lfd fp15, context->FPR[15].d

    la r7, context->FPR[16].v
    psq_lx fp16, 0, r7, 0, 0
    lfd fp16, context->FPR[16].d

    la r7, context->FPR[17].v
    psq_lx fp17, 0, r7, 0, 0
    lfd fp17, context->FPR[17].d

    la r7, context->FPR[18].v
    psq_lx fp18, 0, r7, 0, 0
    lfd fp18, context->FPR[18].d

    la r7, context->FPR[19].v
    psq_lx fp19, 0, r7, 0, 0
    lfd fp19, context->FPR[19].d

    la r7, context->FPR[20].v
    psq_lx fp20, 0, r7, 0, 0
    lfd fp20, context->FPR[20].d

    la r7, context->FPR[21].v
    psq_lx fp21, 0, r7, 0, 0
    lfd fp21, context->FPR[21].d

    la r7, context->FPR[22].v
    psq_lx fp22, 0, r7, 0, 0
    lfd fp22, context->FPR[22].d

    la r7, context->FPR[23].v
    psq_lx fp23, 0, r7, 0, 0
    lfd fp23, context->FPR[23].d

    la r7, context->FPR[24].v
    psq_lx fp24, 0, r7, 0, 0
    lfd fp24, context->FPR[24].d

    la r7, context->FPR[25].v
    psq_lx fp25, 0, r7, 0, 0
    lfd fp25, context->FPR[25].d

    la r7, context->FPR[26].v
    psq_lx fp26, 0, r7, 0, 0
    lfd fp26, context->FPR[26].d

    la r7, context->FPR[27].v
    psq_lx fp27, 0, r7, 0, 0
    lfd fp27, context->FPR[27].d

    la r7, context->FPR[28].v
    psq_lx fp28, 0, r7, 0, 0
    lfd fp28, context->FPR[28].d

    la r7, context->FPR[29].v
    psq_lx fp29, 0, r7, 0, 0
    lfd fp29, context->FPR[29].d

    la r7, context->FPR[30].v
    psq_lx fp30, 0, r7, 0, 0
    lfd fp30, context->FPR[30].d

    la r7, context->FPR[31].v
    psq_lx fp31, 0, r7, 0, 0
    lfd fp31, context->FPR[31].d

    mtlr r8

    lwz SP, context->throwSP
    lwz r3, context->SP
    lwz r3, 0(r3)
    stw r3, 0(SP)
    blr
} // clang-format on
#endif
