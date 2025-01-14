/// @todo Move to C file
#ifndef __GALE01_1A3680
#define __GALE01_1A3680

#include "gm_1601.h" // IWYU pragma: keep

typedef struct MajorScene MajorScene;
typedef struct MinorScene MinorScene;
typedef struct MinorSceneHandler MinorSceneHandler;

struct MinorScene {
    u8 idx;
    u8 preload;
    u16 flags;

    void (*Prep)(MinorScene*);
    void (*Decide)(MinorScene*);

    u8 class_id;

    void* unk_struct_0;
    void* unk_struct_1;
};

struct MajorScene {
    u8 preload;
    u8 idx;

    void (*Load)(void);
    void (*Unload)(void);
    void (*Init)(void);

    MinorScene* minor_scenes;
}; // 803DACA4

struct MinorSceneHandler {
    u8 class_id;

    void (*OnFrame)(void);
    void (*OnLoad)(u32);
    void (*OnLeave)(u32);
    void (*unk_func)(void);
}; // 803DA920

typedef struct {
    u8 curr_major;
    u8 pending_major;
    u8 prev_major;
    u8 curr_minor;
    u8 prev_minor;
    u8 pending_minor;
} SceneNums;

typedef struct {
    SceneNums nums;
    SceneNums nums2;
    u8 pending;
    u8 x0D;
    u8 x0E;
    u8 x0F;
    void* data;
} GameState;
STATIC_ASSERT(sizeof(GameState) == 0x14);

struct sceneData {
    u32 a;
    u8 scene_id;
};

struct gm_80479D58_t {
    /* 0x00 */ struct gm_80479D58_t* unk_0;
    /* 0x04 */ char pad_4[4];
    /* 0x08 */ s32 unk_8;
    /* 0x0C */ s32 unk_C; /* inferred */
    /* 0x10 */ u8 unk_10;
    /* 0x11 */ char pad_11[3]; /* maybe part of unk_10[4]? */
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ char pad_1C[0x24]; /* maybe part of unk_18[0xA]? */
}; /* size = 0x40 */
STATIC_ASSERT(sizeof(struct gm_80479D58_t) == 0x40);

struct gm_8049E548_t {
    /* 0x00 */ char pad_0[8];
    /* 0x08 */ s8 unk_8;
    /* 0x09 */ u8 unk_9;
    /* 0x0A */ s8 unk_A;
    /* 0x0B */ char pad_B[1];
    /* 0x0C */ u16 unk_C;
    /* 0x0E */ s8 unk_E; /* inferred */
    /* 0x0F */ char pad_F[1];
}; /* size = 0x10 */
STATIC_ASSERT(sizeof(struct gm_8049E548_t) == 0x10);

struct fn_801BA1B4_arg0_t {
    char pad_0[0x2];
    /* +2:0 */ u8 x2_b0 : 1;
    /* +2:1 */ u8 x2_b1 : 1;
    /* +2:2 */ u8 x2_b2 : 1;
    /* +2:3 */ u8 x2_b3 : 1;
    /* +2:4 */ u8 x2_b4 : 1;
    /* +2:5 */ u8 x2_b5 : 1;
    /* +2:6 */ u8 x2_b6 : 1;
    /* +2:7 */ u8 x2_b7 : 1;
};

struct fn_801BA3B4_arg0_t {
    char pad_0[0xC];
    /* +C:0 */ u8 xC_b0 : 1;
    /* +C:1 */ u8 xC_b1 : 1;
    /* +C:2 */ u8 xC_b2 : 1;
    /* +C:3 */ u8 xC_b3 : 1;
    /* +C:4 */ u8 xC_b4 : 1;
    /* +C:5 */ u8 xC_b5 : 1;
    /* +C:6 */ u8 xC_b6 : 1;
    /* +C:7 */ u8 xC_b7 : 1;
};

typedef struct gm_controller_map gm_controller_map;
struct gm_controller_map {
    u64 button;
    u64 trigger;
    u64 repeat;
    u64 release;
    u64 unk;
    s32 x28;
    s32 x2C;
};

/* 1A3F48 */ static void gm_801A3F48(MinorScene*);
/* 1A4014 */ static void gm_801A4014(MajorScene* scene);
/* 1A4284 */ static UNK_T gm_801A4284(UNK_T);
/* 1A42B4 */ static u8 gm_801A42B4(void);
/* 1A42C4 */ static u8 gm_801A42C4(void);
/* 1A42E8 */ static void gm_801A42E8(s8 arg0);
/* 1A42F8 */ static void gm_801A42F8(int);
/* 1A4310 */ static UNK_RET gm_800A4310(UNK_PARAMS);
/* 1A4320 */ static u8 gm_801A4320(void);
/* 1A4330 */ static void gm_801A4330(void*);
/* 1A4624 */ static u8 gm_801A4624(void);
/* 1A4B40 */ static void gm_801A4B40(s32 arg0);
/* 1A4B50 */ static void gm_801A4B50(s32 arg0);
/* 1A4B88 */ static void gm_801A4B88(void*);
/* 1A4BB8 */ static s32 gm_801A4BB8(void);
/* 1A4BD4 */ static void gm_801A4BD4(void);
/* 1A4CE0 */ static MinorSceneHandler* gm_801A4CE0(u8);
/* 1A4D34 */ static void gm_801A4D34(void*);
/* 1A50A0 */ static MajorScene* gm_801A50A0(void);
/* 1A50AC */ static MajorScene* gm_801A50AC(void);
/* 1A5244 */ static s8* gm_801A5244(void);
/* 1A5614 */ static void gm_801A5614(void);
/* 1ACC90 */ static void gm_801ACC90(void);
/* 1B6320 */ static UNK_T gm_801B6320(void);
/* 1B8C5C */ static void fn_801B8C5C(UNK_T);
/* 1B9FB8 */ static void fn_801B9FB8(void* arg0);
/* 1BA1B4 */ static void fn_801BA1B4(struct fn_801BA1B4_arg0_t*);
/* 1BA3B4 */ void fn_801BA3B4(struct fn_801BA3B4_arg0_t* arg0);
/* 1BA5B4 */ static void fn_801BA5B4(UNK_T);
/* 1BA7AC */ static void fn_801BA7AC(UNK_T);
/* 1BBFE4 */ static void gm_801BBFE4(void);
/* 1BEFB0 */ static u8 gm_801BEFB0(void);
/* 1BEFC0 */ static void gm_801BEFC0(s8 arg0);
/* 1BEFD0 */ static u8 gm_801BEFD0(void);
/* 1BEFE0 */ static void gm_801BEFE0(s8 arg0);
/* 1BF684 */ static void gm_801BF684(s16 arg0);
/* 1BF694 */ static u8 gm_801BF694(void);
/* 2A3EF4 */ static void gm_801A3EF4(void);
static u64 gm_803DA788;
static gm_controller_map gm_80479C30[4];
static gm_controller_map controller_union;
void (*gm_80479D20)(s32);
s32 gm_80479D24;
/* 3DA920 */ static MajorScene gm_803DA920;
/* 3DACA4 */ static MajorScene gm_803DACA4;
/* 3DD2C0 */ static int gm_803DD2C0[74];
/* 479D30 */ static GameState gm_80479D30;
/* 479D58 */ static struct gm_80479D58_t gm_80479D58;
/* 49C178 */ static s8 gm_8049C178[16];
/* 49E548 */ static struct gm_8049E548_t gm_8049E548;
/* 4D6720 */ static UNK_T gm_804D6720;
/* 4D672C */ static s32 gm_804D672C;
/* 4D6730 */ static UNK_T gm_804D6730;

#endif
