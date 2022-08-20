// header for shared private data of GXMisc_*.*
// todo: merge this into GXMisc.c when it's one file

#ifndef DOLPHIN_GX_GXMISC___GXMISC_H
#define DOLPHIN_GX_GXMISC___GXMISC_H

#include <dolphin/types.h>
#include <dolphin/os/OSThread.h>

/* 004D3F0C */ extern OSThreadQueue GXDrawDoneThreadQueue;
/* 004D3F08 */ extern u8 lbl_804D7328[0x4];

#endif