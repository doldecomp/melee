#ifndef MELEE_MN_SOUNDTEST_H
#define MELEE_MN_SOUNDTEST_H

#include <placeholder.h>
#include <baselib/controller.h>
#include <baselib/sislib.h>
extern HSD_PadStatus HSD_PadCopyStatus[4];

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u16 unk4;
    f32 unk8;
    f32 unkC;
    UNK_T unk10;
    HSD_Text* unk14;
    HSD_Text* unk18;
    HSD_Text* unk1C;
} soundtest_user_data;

typedef struct {
    /*  +0 */ u16 classifier;
    /*  +2 */ u8 p_link;
    /*  +3 */ u8 gx_link;
    /*  +4 */ u8 p_priority;
    /*  +5 */ u8 render_priority;
    /*  +6 */ u8 obj_kind;
    /*  +7 */ u8 user_data_kind;
    /*  +8 */ HSD_GObj* next;
    /*  +C */ HSD_GObj* prev;
    /* +10 */ HSD_GObj* next_gx;
    /* +14 */ HSD_GObj* prev_gx;
    /* +18 */ HSD_GObjProc* proc;
    /* +1C */ GObj_RenderFunc render_cb;
    /* +20 */ u64 gxlink_prios;
    /* +28 */ void* hsd_obj;
    /* +2C */ soundtest_user_data* user_data;
    /* +30 */ void (*user_data_remove_func)(void* data);
    /* +34 */ void* x34_unk;
} Soundtest_GObj;

/* 24A790 */ void mnSoundTest_8024A790(HSD_GObj*);
/* 24A958 */ void mnSoundTest_8024A958(Soundtest_GObj*);
/* 24AA70 */ void mnSoundTest_8024AA70(HSD_GObj*, u8);
/* 24ABF8 */ void mnSoundTest_8024ABF8(HSD_GObj*, u8);
/* 24AD58 */ void mnSoundTest_8024AD58(HSD_GObj*, u8);
/* 24AED0 */ void fn_8024AED0(HSD_GObj*);
/* 24B2B0 */ void fn_8024B2B0(HSD_GObj*);
/* 24B7E4 */ UNK_RET fn_8024B7E4(UNK_PARAMS);
/* 24B8B4 */ UNK_RET fn_8024B8B4(UNK_PARAMS);
/* 24BAF0 */ UNK_RET fn_8024BAF0(UNK_PARAMS);
/* 24BCA0 */ UNK_RET mnSoundTest_8024BCA0(UNK_PARAMS);
/* 24BEE0 */ UNK_RET mnSoundTest_8024BEE0(int);

#endif
