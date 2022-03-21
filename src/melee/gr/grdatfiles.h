#ifndef _grdatfiles_h_
#define _grdatfiles_h_

#include "stage.h"

// Appears to be related to stage audio
typedef struct _UnkBgmStruct {
    s32 x0;
    s32 x4;
    s32 x8;
    u32 xC;
    u32 x10;
    s16 x14;
    s16 x16;
    s16 x18;
    u8 pad[0x64 - 0x1A];
} UnkBgmStruct;

// TODO: what is this struct?
typedef struct _UnkStage6B0 {
    f32 x0;
    s16 x4;
    u8 x6_pad[2];
    s16 x8;
    s16 xA;
    s32 xC;
    s32 x10;
    s32 x14;
    f32 x18;
    f32 x1C, x20, x24, x28;
    u8 x2C_pad[0x2E - 0x2C];
    s16 x2E;
    s32 x30;
    s32 x34;
    s32 x38;
    f32 x3C, x40, x44, x48;
    BOOL x4C_fixed_cam;
    f32 x50, x54, x58, x5C, x60, x64;
    s16 x68;
    u8 x6C_pad[0xB0 - 0x6A];
    struct _UnkBgmStruct* xB0;
    s32 xB4; // number of entries in xB0
    s32 xB8;
    s32 xBC;
    s32 xC0;
    s32 xC4;
    s32 xC8;
    s32 xCC;
    s32 xD0;
    s32 xD4;
    s32 xD8;
} UnkStage6B0;

typedef struct _UnkStageDat {
    void* unk0;
    s32 unk4;

    struct {
        struct _HSD_Joint* unk0;
        u8 x4_fill[0x20 - 0x4];
        S16Vec* unk20;
        s32 unk24; // size of unk20 array
        u8 x28_fill[0x34 - 0x28];
    }* unk8;
    s32 unkC;

    s32* unk10;
    s32 unk14;

    u8 x18_fill[0x20 - 0x18];

    void* unk20;
    s32 unk24;

    struct _UnkStageDatInternal** unk28;
    s32 unk2C; // size
} UnkStageDat;

typedef struct _UnkArchiveStruct {
    struct _HSD_Archive* unk0;
    struct _UnkStageDat* unk4;
    s32 unk8;
} UnkArchiveStruct;

void func_801C5FC0(struct _HSD_Archive*, void* data, u32 length);
void func_801C6038(void*, s32, s32);
static void func_801C6228(struct _UnkStageDat*);
void func_801C6288(void);
static struct _UnkArchiveStruct* func_801C62B4(void);
struct _UnkArchiveStruct* func_801C6324(void);
struct _UnkArchiveStruct* func_801C6330(s32);
struct _UnkArchiveStruct* func_801C6478(void* data, s32 length);

#endif
