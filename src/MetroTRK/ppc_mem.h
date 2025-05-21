#ifndef _METROTRK_PPC_MEM_H
#define _METROTRK_PPC_MEM_H

#include <platform.h>

static inline u8 ppc_readbyte1(const u8* ptr)
{
    u32* alignedPtr = (u32*) ((u32) ptr & ~3);
    return (u8) (*alignedPtr >> ((3 - ((u32) ptr - (u32) alignedPtr)) << 3));
}

static inline void ppc_writebyte1(u8* ptr, u8 val)
{
    u32* alignedPtr = (u32*) ((u32) ptr & ~3);
    u32 v = *alignedPtr;
    u32 uVar3 = 0xFF << ((3 - ((u32) ptr - (u32) alignedPtr)) << 3);
    u32 iVar1 = (3 - ((u32) ptr - (u32) alignedPtr)) << 3;
    *alignedPtr = (v & ~uVar3) | (uVar3 & (val << iVar1));
}

#endif