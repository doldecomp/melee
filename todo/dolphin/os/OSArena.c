#include <dolphin/os/OSArena.h>

#define ROUND(n, a) (((u32) (n) + (a) - 1) & ~((a) - 1))
#define TRUNC(n, a) (((u32) (n)) & ~((a) - 1))

void* __OSArenaHi;
void* __OSArenaLo = (void*) -1;

void* OSGetArenaHi(void)
{
    return __OSArenaHi;
}

void* OSGetArenaLo(void)
{
    return __OSArenaLo;
}

void OSSetArenaHi(void* addr)
{
    __OSArenaHi = addr;
}

void OSSetArenaLo(void* addr)
{
    __OSArenaLo = addr;
}

void* OSAllocFromArenaLo(u32 size, u32 align)
{
    void* ptr;
    u8* arenaLo;

    ptr = OSGetArenaLo();
    arenaLo = ptr = (void*) ROUND(ptr, align);
    arenaLo += size;
    arenaLo = (u8*) ROUND(arenaLo, align);
    OSSetArenaLo(arenaLo);
    return ptr;
}

void* OSAllocFromArenaHi(u32 size, u32 align)
{
    void* ptr;
    u8* arenaHi;

    arenaHi = OSGetArenaHi();
    arenaHi = (u8*) TRUNC(arenaHi, align);
    arenaHi -= size;
    arenaHi = ptr = (void*) TRUNC(arenaHi, align);
    OSSetArenaHi(arenaHi);
    return ptr;
}
