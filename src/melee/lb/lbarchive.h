#ifndef MELEE_LB_LBARCHIVE_H
#define MELEE_LB_LBARCHIVE_H

#include <dolphin/mtx/types.h>
#include <dolphin/types.h>
#include <sysdolphin/baselib/archive.h>

typedef struct _UnkArchiveStruct {
    struct _HSD_Archive* unk0;
    struct _UnkStageDat* unk4;
    s32 unk8;
} UnkArchiveStruct;

typedef struct _UnkStageDat {
    void* unk0;
    s32 unk4;

    struct {
        struct _HSD_Joint* unk0;
        u8 x4_fill[0x20 - 0x4];
        S16Vec* unk20;
        s32 unk24; // size of unk20 array
        u8 x28_fill[0x34 - 0x28];
    } * unk8;
    s32 unkC;

    s32* unk10;
    s32 unk14;

    u8 x18_fill[0x20 - 0x18];

    void* unk20;
    s32 unk24;

    struct _UnkStageDatInternal** unk28;
    s32 unk2C; // size
} UnkStageDat;

void lbArchive_InitializeDAT(HSD_Archive *archive, u8 *data, u32 length);
void func_80016EFC();
void func_80016BE0();
HSD_Archive* func_80016DBC(unk_t, ...);
s32 func_800171CC(void*, ...);

// vararg may start earlier
void func_80016C64(char*, unk_t*, char*, s32, ...);

#endif
