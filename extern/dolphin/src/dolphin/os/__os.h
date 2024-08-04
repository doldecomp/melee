#ifndef _DOLPHIN_OS_INTERNAL_H_
#define _DOLPHIN_OS_INTERNAL_H_

#include <dolphin/os.h>

// OS.c
extern char * __OSExceptionNames[15]; // D ONLY

unsigned long __OSIsDebuggerPresent(void);
void __OSPSInit(void);

// OSAlloc.c
extern volatile int __OSCurrHeap;

// OSAudioSystem.c
void __OSInitAudioSystem(void);
void __OSStopAudioSystem(void);

// OSCache.c
void __OSCacheInit(void);

// OSContext.c
void __OSContextInit(void);

// OSError.c
void __OSUnhandledException(unsigned char exception, struct OSContext * context, unsigned long dsisr, unsigned long dar);

// OSInterrupt.c
extern void __RAS_OSDisableInterrupts_begin(void);
extern void __RAS_OSDisableInterrupts_end(void);

extern unsigned long long __OSSpuriousInterrupts; // D ONLY
extern char * __OSInterruptNames[33]; // D ONLY
extern char * __OSPIErrors[8]; // D ONLY

__OSInterruptHandler __OSSetInterruptHandler(__OSInterrupt interrupt, __OSInterruptHandler handler);
__OSInterruptHandler __OSGetInterruptHandler(__OSInterrupt interrupt);
void __OSInterruptInit(void);
OSInterruptMask __OSMaskInterrupts(OSInterruptMask global);
OSInterruptMask __OSUnmaskInterrupts(OSInterruptMask global);
void __OSDispatchInterrupt(__OSException exception, OSContext* context);
void __OSModuleInit(void);

// OSMutex.c
void __OSUnlockAllMutex(struct OSThread *thread);
int __OSCheckDeadLock(struct OSThread *thread);
int __OSCheckMutexes(struct OSThread *thread);

// OSResetSW.c
void __OSResetSWInterruptHandler(short exception, struct OSContext *context);

// OSRtc.c
int __OSGetRTC(unsigned long * rtc);
int __OSSetRTC(unsigned long rtc);
void __OSInitSram();
struct OSSram * __OSLockSram(void);
struct OSSramEx * __OSLockSramEx(void);
int __OSUnlockSram(int commit);
int __OSUnlockSramEx(int commit);
int __OSSyncSram(void);
int __OSCheckSram(void);
int __OSReadROM(void * buffer, long length, long offset);
int __OSReadROMAsync(void * buffer, long length, long offset, void (* callback)());
unsigned char __OSGetBootMode(void);
void __OSSetBootMode(unsigned char ntd);

// OSSync.c
extern void __OSSystemCallVectorStart();
extern void __OSSystemCallVectorEnd();

void __OSInitSystemCall(void);

// OSThread.c
void __OSThreadInit(void);
long __OSGetEffectivePriority(struct OSThread * thread);
void __OSPromoteThread(struct OSThread * thread, long priority);
void __OSReschedule(void);

// OSTime.c
void __OSSetTime(long long time);
long long __OSGetSystemTime();
void __OSSetTick(register unsigned long newTicks);

// ppc_eabi_init.c
__declspec(section ".init") asm void __init_hardware(void);
__declspec(section ".init") asm void __flush_cache(void *address, unsigned int size);
void __init_user(void);
void __init_cpp(void);
void __fini_cpp(void);
void _ExitProcess(void);

// start.c
void __start(void);

__declspec(section ".init") extern void __start(void);
__declspec(section ".init") void __copy_rom_section(void* dst, const void* src, unsigned long size);
__declspec(section ".init") void __init_bss_section(void* dst, unsigned long size);
__declspec(section ".init") extern void __init_registers(void);
__declspec(section ".init") extern void __init_data(void);

// time.dolphin.c
long long __get_clock(void);
unsigned long __get_time(void);
int __to_gm_time(void);

#endif // _DOLPHIN_OS_INTERNAL_H_
