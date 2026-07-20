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
    HSD_Text* unk10;
    HSD_Text* unk14;
    HSD_Text* unk18;
    HSD_Text* unk1C;
} soundtest_user_data;

/* 24A790 */ void mnSoundTest_8024A790(HSD_GObj*);
/* 24A958 */ void mnSoundTest_8024A958(HSD_GObj*);
/* 24AA70 */ void mnSoundTest_8024AA70(HSD_GObj*, u8);
/* 24ABF8 */ void mnSoundTest_8024ABF8(HSD_GObj*, u8);
/* 24AD58 */ void mnSoundTest_8024AD58(HSD_GObj*, u8);
/* 24AED0 */ void fn_8024AED0(HSD_GObj*);
/* 24B2B0 */ void fn_8024B2B0(HSD_GObj*);
/* 24B7E4 */ void fn_8024B7E4(HSD_GObj*);
/* 24B8B4 */ void fn_8024B8B4(HSD_GObj*, f32);
/* 24BAF0 */ void fn_8024BAF0(HSD_GObj*);
/* 24BCA0 */ void mnSoundTest_8024BCA0(int);
/* 24BEE0 */ HSD_GObjProc* mnSoundTest_8024BEE0(s32);

#endif
