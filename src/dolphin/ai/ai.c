#include <placeholder.h>

#include <dolphin/ai/ai.h>
#include <dolphin/dsp/dsp.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSTime.h>

static AISCallback __AIS_Callback;
static AIDCallback __AID_Callback;
static u8* __CallbackStack;

#ifdef MWERKS_GEKKO
static u8* __OldStack;
#endif

static vs32 __AI_init_flag;
static OSTime bound_32KHz;
static OSTime bound_48KHz;
static OSTime min_wait;
static OSTime max_wait;
static OSTime buffer;

static void __AI_set_stream_sample_rate(u32 rate);
static void __AISHandler(__OSInterrupt, OSContext*);
static void __AIDHandler(__OSInterrupt, OSContext*);
static void __AICallbackStackSwitch(register AIDCallback);
static void __AI_SRC_INIT(void);

AIDCallback AIRegisterDMACallback(AIDCallback callback)
{
    s32 oldInts;
    AIDCallback ret;

    ret = __AID_Callback;
    oldInts = OSDisableInterrupts();
    __AID_Callback = callback;
    OSRestoreInterrupts(oldInts);
    return ret;
}

void AIInitDMA(u32 addr, u32 length)
{
    s32 oldInts;
    oldInts = OSDisableInterrupts();
    __DSPRegs[24] = (u16) ((__DSPRegs[24] & ~0x3FF) | (addr >> 16));
    __DSPRegs[25] = (u16) ((__DSPRegs[25] & ~0xFFE0) | (0xffff & addr));
    __DSPRegs[27] =
        (u16) ((__DSPRegs[27] & ~0x7FFF) | (u16) ((length >> 5) & 0xFFFF));
    OSRestoreInterrupts(oldInts);
}

void AIStartDMA(void)
{
    __DSPRegs[27] |= 0x8000;
}

void AIResetStreamSampleCount(void)
{
    __AIRegs[0] = (__AIRegs[0] & ~0x20) | 0x20;
}

void AISetStreamTrigger(u32 trigger)
{
    __AIRegs[3] = trigger;
}

void AISetStreamPlayState(u32 state)
{
    s32 oldInts;
    u8 volRight;
    u8 volLeft;

    if (state == AIGetStreamPlayState()) {
        return;
    }
    if ((AIGetStreamSampleRate() == 0U) && (state == 1)) {
        volRight = AIGetStreamVolRight();
        volLeft = AIGetStreamVolLeft();
        AISetStreamVolRight(0);
        AISetStreamVolLeft(0);
        oldInts = OSDisableInterrupts();
        __AI_SRC_INIT();
        __AIRegs[0] = (__AIRegs[0] & ~0x20) | 0x20;
        __AIRegs[0] = (__AIRegs[0] & ~1) | 1;
        OSRestoreInterrupts(oldInts);
        AISetStreamVolLeft(volRight);
        AISetStreamVolRight(volLeft);
    } else {
        __AIRegs[0] = (__AIRegs[0] & ~1) | state;
    }
}

u32 AIGetStreamPlayState(void)
{
    return __AIRegs[0] & 1;
}

void AISetDSPSampleRate(u32 rate)
{
    u32 state;
    s32 oldInts;
    u8 left;
    u8 right;
    u32 sampleRate;

    if (rate == AIGetDSPSampleRate()) {
        return;
    }

    __AIRegs[0] &= ~0x40;
    if (rate == 0) {
        left = AIGetStreamVolLeft();
        right = AIGetStreamVolRight();
        state = AIGetStreamPlayState();
        sampleRate = AIGetStreamSampleRate();
        AISetStreamVolLeft(0);
        AISetStreamVolRight(0);
        oldInts = OSDisableInterrupts();
        __AI_SRC_INIT();
        __AIRegs[0] = (__AIRegs[0] & ~0x20) | 0x20;
        __AIRegs[0] = (__AIRegs[0] & ~2) | (sampleRate * 2);
        __AIRegs[0] = (__AIRegs[0] & ~1) | state;
        __AIRegs[0] |= 0x40;
        OSRestoreInterrupts(oldInts);
        AISetStreamVolLeft(left);
        AISetStreamVolRight(right);
    }
}

u32 AIGetDSPSampleRate(void)
{
    return ((__AIRegs[0] >> 6) & 1) ^ 1;
}

void AISetStreamSampleRate(u32 rate)
{
    if (rate == 1) {
        __AI_set_stream_sample_rate(rate);
    }
}

static void __AI_set_stream_sample_rate(u32 rate)
{
    s32 oldInts;
    s32 state;
    u8 left;
    u8 right;
    s32 temp_r26;

    if (rate == AIGetStreamSampleRate()) {
        return;
    }
    state = AIGetStreamPlayState();
    left = AIGetStreamVolLeft();
    right = AIGetStreamVolRight();
    AISetStreamVolRight(0);
    AISetStreamVolLeft(0);
    temp_r26 = __AIRegs[0] & 0x40;
    __AIRegs[0] &= ~0x40;
    oldInts = OSDisableInterrupts();
    __AI_SRC_INIT();
    __AIRegs[0] |= temp_r26;
    __AIRegs[0] = (__AIRegs[0] & ~0x20) | 0x20;
    __AIRegs[0] = (__AIRegs[0] & ~2) | (rate * 2);
    OSRestoreInterrupts(oldInts);
    AISetStreamPlayState(state);
    AISetStreamVolLeft(left);
    AISetStreamVolRight(right);
}

u32 AIGetStreamSampleRate(void)
{
    return (__AIRegs[0] >> 1) & 1;
}

void AISetStreamVolLeft(u8 volume)
{
    __AIRegs[1] = (__AIRegs[1] & ~0xFF) | (volume & 0xFF);
}

u8 AIGetStreamVolLeft(void)
{
    return __AIRegs[1];
}

void AISetStreamVolRight(u8 volume)
{
    __AIRegs[1] = (__AIRegs[1] & ~0xFF00) | ((volume & 0xFF) << 8);
}

u8 AIGetStreamVolRight(void)
{
    return __AIRegs[1] >> 8;
}

void AIInit(u8* stack)
{
    if (__AI_init_flag == true) {
        return;
    }

    bound_32KHz = OSNanosecondsToTicks(31524);
    bound_48KHz = OSNanosecondsToTicks(42024);
    min_wait = OSNanosecondsToTicks(42000);
    max_wait = OSNanosecondsToTicks(63000);
    buffer = OSNanosecondsToTicks(3000);

    AISetStreamVolRight(0);
    AISetStreamVolLeft(0);
    AISetStreamTrigger(0);
    AIResetStreamSampleCount();
    AISetStreamSampleRate(1);
    AISetDSPSampleRate(0);
    __AIS_Callback = 0;
    __AID_Callback = 0;
    __CallbackStack = stack;
    __OSSetInterruptHandler(5, __AIDHandler);
    __OSUnmaskInterrupts(0x04000000);
    __OSSetInterruptHandler(8, __AISHandler);
    __OSUnmaskInterrupts(0x800000);
    __AI_init_flag = true;
}

static void __AISHandler(__OSInterrupt interrupt, OSContext* context)
{
    OSContext tmpContext;
    __AIRegs[0] |= 8;
    OSClearContext(&tmpContext);
    OSSetCurrentContext(&tmpContext);
    if (__AIS_Callback != NULL) {
        __AIS_Callback(__AIRegs[2]);
    }
    OSClearContext(&tmpContext);
    OSSetCurrentContext(context);
}

static void __AIDHandler(__OSInterrupt interrupt, struct OSContext* context)
{
    OSContext tempContext;
    u32 temp = __DSPRegs[5];
    __DSPRegs[5] = (temp & ~0xA0) | 8;
    OSClearContext(&tempContext);
    OSSetCurrentContext(&tempContext);
    if (__AID_Callback) {
        if (__CallbackStack) {
            __AICallbackStackSwitch(__AID_Callback);
        } else {
            __AID_Callback();
        }
    }

    OSClearContext(&tempContext);
    OSSetCurrentContext(context);
}

#ifdef MWERKS_GEKKO
static asm void __AICallbackStackSwitch(register AIDCallback cb)
{ // clang-format off
    fralloc

    // Store current stack
    lis r5, __OldStack@ha
    addi r5, r5, __OldStack@l
    stw r1, 0(r5)

    // Load stack for callback
    lis r5, __CallbackStack@ha
    addi r5, r5, __CallbackStack@l
    lwz r1, 0(r5)

    // Run callback
    subi r1, r1, 8
    mtlr cb
    blrl

    // Restore old stack
    lis r5, __OldStack@ha
    addi r5, r5, __OldStack@l
    lwz r1, 0(r5)

    frfree
    blr
} // clang-format on
#else

static void __AICallbackStackSwitch(AIDCallback cb)
{
    NOT_IMPLEMENTED;
}
#endif

static inline void waitForAIRegs(void)
{
    u32 temp = __AIRegs[2];

    while (temp == __AIRegs[2]) {
        continue;
    }
}

static void __AI_SRC_INIT(void)
{
    u8 _[16];

    OSTime rise48 = 0;
    uint done = false;
    OSTime temp = 0;

    while (!done) {
        OSTime diff;

        __AIRegs[0] = (__AIRegs[0] & ~(1 << 5)) | (1 << 5);
        __AIRegs[0] &= ~(1 << 1);
        __AIRegs[0] = (__AIRegs[0] & ~(1 << 0)) | (1 << 0);

        waitForAIRegs();

        {
            /// @todo Probably its own function, but it has two return values
            ///       (@c rise48 and @c diff).
            OSTime rise32 = OSGetTime();

            __AIRegs[0] = (__AIRegs[0] & ~(1 << 1)) | (1 << 1);
            __AIRegs[0] = (__AIRegs[0] & ~(1 << 0)) | (1 << 0);

            waitForAIRegs();

            rise48 = OSGetTime();

            diff = rise48 - rise32;
        }

        __AIRegs[0] &= ~(1 << 1);
        __AIRegs[0] &= ~(1 << 0);

        if (diff < bound_32KHz - buffer) {
            temp = min_wait;
            done = true;
        } else if (diff >= bound_32KHz + buffer && diff < bound_48KHz - buffer)
        {
            temp = max_wait;
            done = true;
        } else {
            done = false;
        }
    }

    while (rise48 + temp > OSGetTime()) {
        continue;
    }
}
