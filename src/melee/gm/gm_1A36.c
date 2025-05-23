#include <placeholder.h>

#include "gm/gm_1A36.static.h"

#include "gmmain_lib.h"

#include "db/db_2253.h"
#include "gm/types.h"
#include "lb/lb_00B0.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbcardgame.h"
#include "lb/lbdvd.h"
#include "lb/lblanguage.h"
#include "lb/lbmthp.h"
#include "ty/toy.h"
#include "un/un_2FC9.h"

#include <dolphin/dvd/dvd.h>
#include <dolphin/os/OSRtc.h>
#include <dolphin/vi/vi.h>
#include <baselib/controller.h>
#include <baselib/devcom.h>
#include <baselib/video.h>

u64 gm_801A3680(u8 idx)
{
    return gm_80479C30[(u8) idx].button;
}

u64 gm_801A36A0(u8 idx)
{
    return gm_80479C30[(u8) idx].trigger;
}

u64 gm_801A36C0(u8 idx)
{
    return gm_80479C30[(u8) idx].unk;
}

void gm_801A36E0(s32 idx, s32 arg1)
{
    if (idx == 4) {
        gm_80479C30[0].x28 = arg1;
        gm_80479C30[1].x28 = arg1;
        gm_80479C30[2].x28 = arg1;
        gm_80479C30[3].x28 = arg1;
        return;
    }
    gm_80479C30[idx].x28 = arg1;
}

void gm_801A3714(s32 idx, u64 arg1, u64 arg2)
{
    if (arg1 & gm_80479C30[idx].button) {
        gm_80479C30[idx].button |= arg2;
    }
    if (arg1 & gm_80479C30[idx].repeat) {
        gm_80479C30[idx].repeat |= arg2;
    }
    if (arg1 & gm_80479C30[idx].trigger) {
        gm_80479C30[idx].trigger |= arg2;
    }
    if (arg1 & gm_80479C30[idx].release) {
        gm_80479C30[idx].release |= arg2;
    }
}

void gm_801A3820(s32 idx, u64 arg1, u64 arg2)
{
    u64 val;
    if (arg1 == (arg1 & gm_80479C30[idx].button)) {
        gm_80479C30[idx].button |= arg2;
    }
    if (arg1 == (arg1 & gm_80479C30[idx].repeat)) {
        gm_80479C30[idx].repeat |= arg2;
    }
    if (arg1 == (arg1 & gm_80479C30[idx].button)) {
        if (arg1 & gm_80479C30[idx].trigger) {
            gm_80479C30[idx].trigger |= arg2;
        }
    }
    if (arg1 == (arg1 & gm_80479C30[idx].button)) {
        if (arg1 & gm_80479C30[idx].release) {
            gm_80479C30[idx].release |= arg2;
        }
    }
}

void fn_801A396C(s32 idx)
{
    if (gm_80479C30[idx].button || gm_80479C30[idx].release) {
        gm_80479C30[idx].unk = gm_80479C30[idx].button;
        gm_80479C30[idx].x28 = gm_80479D24;
        gm_80479C30[idx].x2C = 0;
    }
    if (gm_80479C30[idx].x2C < gm_80479D24) {
        gm_80479C30[idx].x2C++;
    }
    if (gm_80479C30[idx].x28 != 0) {
        gm_80479C30[idx].x28--;
        gm_80479C30[idx].unk = 0;
    }
}

#pragma push
#pragma dont_inline on
void gm_801A3A74(void)
{
    gm_controller_map* controller = gm_80479C30;
    int i;
    for (i = 0; i < 4; i++) {
        controller->button = HSD_PadCopyStatus[i].button;
        controller->trigger = HSD_PadCopyStatus[i].trigger;
        controller->repeat = HSD_PadCopyStatus[i].repeat;
        controller->release = HSD_PadCopyStatus[i].release;
        gm_801A3714(i, 0x1100, ((u64) 1 << (32 + 0)));
        gm_801A3714(i, 0x200, ((u64) 1 << (32 + 1)));
        gm_801A3820(i, 0x1060, ((u64) 1 << (32 + 2)));
        gm_801A3820(i, 0x1160, ((u64) 1 << (32 + 3)));
        gm_801A3714(i, 0x10008, ((u64) 1 << (32 + 4)));
        gm_801A3714(i, 0x20004, ((u64) 1 << (32 + 5)));
        gm_801A3714(i, 0x40001, ((u64) 1 << (32 + 6)));
        gm_801A3714(i, 0x80002, ((u64) 1 << (32 + 7)));
        gm_80479D20(i);
        controller++;
    }
    controller_union.button = 0;
    controller_union.trigger = 0;
    controller_union.repeat = 0;
    controller_union.release = 0;
    controller_union.unk = 0;
    controller_union.x28 = 0;
    controller_union.x2C = 0;
    for (i = 0; i < 4; i++) {
        controller_union.button |= gm_80479C30[i].button;
        controller_union.trigger |= gm_80479C30[i].trigger;
        controller_union.repeat |= gm_80479C30[i].repeat;
        controller_union.release |= gm_80479C30[i].release;
    }
}
#pragma pop

/// #gm_801A3E88

/// #gm_801A3EF4

/// #gm_801A3F48

inline u8 matchMinor(MinorScene* scenes)
{
    u8 i;
    for (i = 0; i != 255; i++) {
        if (scenes[i].idx > gm_80479D30.nums.curr_minor) {
            return scenes[i].idx;
        }
    }
    return 0;
}

void gm_801A4014(MajorScene* scene)
{
    MinorScene* temp_r5;
    MinorScene* var_r27;
    MinorScene* var_r6;
    int var_ctr;
    int var_r3;
    int* temp_r30;
    int temp_r0;
    u8 var_r3_3;
    int var_r4;
    struct {
        u32 x0, x4, x8;
    }* temp_r25;
    MinorSceneHandler* temp_r26;
    u32 unused;

    var_r4 = gm_80479D30.nums.curr_minor;
#if 0
    gm_80479D30.nums.curr_minor = matchMinor(scene->minor_scenes);
#else
    temp_r5 = scene->minor_scenes;
    var_ctr = 0xFF - var_r4;
    if (var_r4 < 0xFF) {
    loop_1:
        var_r6 = temp_r5;
        var_r3 = 0;
        while (var_r3 < 0xFF) {
            if (var_r6->idx == 0xFF) {
                var_r4 += 1;
                goto loop_1;
            }
            if (var_r4 == var_r6->idx) {
                var_r27 = &temp_r5[var_r3];
                goto good;
            }
            var_r6 += 1;
            var_r3 += 1;
        }
    }
    var_r27 = NULL;
good:
    gm_80479D30.nums.curr_minor = (u8) var_r27->idx;
#endif
    gm_801A3F48(var_r27);
    if (var_r27->Prep != NULL) {
        var_r27->Prep(var_r27);
    }
    temp_r25 = (void*) var_r27;
    temp_r26 = gm_801A4CE0(var_r27->class_id);
    gm_801A4BD4();
    gm_801A4B88(temp_r25);
    if (temp_r26->OnLoad != NULL) {
        temp_r26->OnLoad(temp_r25->x4);
    }
    gm_801A4D34(temp_r26->OnFrame);
    temp_r30 = &gmMainLib_8046B0F0.x4;
    if (*temp_r30 == 0 && temp_r26->OnLeave != NULL) {
        temp_r26->OnLeave(temp_r25->x8);
    }
    if (*temp_r30 == 0) {
        if (var_r27->Decide != NULL) {
            var_r27->Decide(var_r27);
        }
        gm_80479D30.nums.prev_minor = gm_80479D30.nums.curr_minor;
        if (gm_80479D30.nums.pending_minor) {
            gm_80479D30.nums.curr_minor = gm_80479D30.nums.pending_minor - 1;
            gm_80479D30.nums.pending_minor = 0;
        } else {
            gm_80479D30.nums.curr_minor = matchMinor(scene->minor_scenes);
        }
    }
    lb_8001CDB4();
    lb_8001B760(0xB);
    lbMthp_8001F800();
    if (*temp_r30 != 0) {
        lbAudioAx_80027DBC();
        HSD_PadReset();
        while (lb_8001B6F8() == 0xB)
            ;
        if (DVDCheckDisk() == 0) {
            OSResetSystem(1, 0, 0);
        }
        lbMthp_8001F800();
        while (HSD_DevComIsBusy(1) != 0)
            ;
        gmMainLib_8015FBA4();
        gm_801A50AC();
        lb_8000C160(&gm_80479D30, 0x14);
        gm_801A3EF4();
        gmMainLib_8046B0F0.x0 = 1;
        gm_801A42F8(0x28);
        HSD_VISetBlack(0);
    }
}

int gm_801A427C(void* arg0)
{
    return M2C_FIELD(arg0, int*, 0x10);
}

UNK_T gm_801A4284(UNK_T arg0)
{
    return M2C_FIELD(arg0, UNK_T*, 0x14);
}

void gm_801A428C(u8 arg0)
{
    gm_80479D30.nums.curr_minor = arg0;
    gm_80479D30.nums.prev_minor = arg0;
}

void gm_801A42A0(s32 arg0)
{
    gm_80479D30.nums.pending_minor = arg0 + 1;
}

u8 gm_801A42B4(void)
{
    return gm_80479D30.nums.prev_minor;
}

u8 gm_801A42C4(void)
{
    return gm_80479D30.nums.curr_minor;
}

void gm_801A42D4(void)
{
    gm_80479D30.pending = 1;
}

void gm_801A42E8(s8 arg0)
{
    M2C_FIELD(&gm_80479D30, s8*, 1) = arg0;
}

void gm_801A42F8(int arg0)
{
    gm_80479D30.nums.pending_major = arg0;
    gm_80479D30.pending = 1;
}

u8 gm_801A4310(void)
{
    return ((u8*) &gm_80479D30)[0];
}

u8 gm_801A4320(void)
{
    return gm_80479D30.nums.prev_major;
}

void gm_801A4330(void* arg0)
{
    gm_80479D30.data = arg0;
}

/// #gm_801A4340

inline MajorScene* findSceneMatching(u8 idx)
{
    MajorScene* cur;
    for (cur = gm_801A50AC(); cur->idx != 45; cur++) {
        if (cur->idx == idx) {
            return cur;
        }
    }
    return NULL;
}

u8 gm_801A43A0(u8 arg0)
{
    u8 temp_r3;
    MajorScene* var_r30;
    MajorScene* var_r3_2;
    GameState* gamestate = &gm_80479D30;
    u64 unused;

    var_r30 = findSceneMatching(arg0);

    gm_80479D30.pending = 0;
    gm_80479D30.nums.curr_minor = 0;
    gm_80479D30.nums.prev_minor = 0;
    gm_80479D30.nums.pending_minor = 0;
    lbDvd_80018F58(var_r30->preload);
    if (var_r30->Load != NULL) {
        var_r30->Load();
    }
    while (!gamestate->pending) {
        if (gm_80479D30.data != NULL &&
            (temp_r3 = (*(u8(*)(void)) gm_80479D30.data)(), temp_r3 != 45))
        {
            gm_80479D30.nums2 = gm_80479D30.nums;
            gamestate->pending = 0;
            gamestate->nums.curr_minor = 0;
            gamestate->nums.prev_minor = 0;
            gamestate->nums.pending_minor = 0;

            var_r3_2 = findSceneMatching(temp_r3);

            gm_801A4014(var_r3_2);
            if (gmMainLib_8046B0F0.x4 == 0) {
                gm_80479D30.nums = gm_80479D30.nums2;
            }
        } else {
            gm_801A4014(var_r30);
        }
    }
    if (gmMainLib_8046B0F0.x4 == 0 && var_r30->Unload != NULL) {
        var_r30->Unload();
    }
    return gm_80479D30.nums.pending_major;
}

// UnclePunch: Scene_Main
void gm_801A4510(void)
{
    u32 unused;
    MajorScene* major_scenes;
    GameState* gamestate = &gm_80479D30;
    int i;

    gm_801A50AC();
    lb_8000C160(&gm_80479D30, sizeof(GameState));
    major_scenes = gm_801A50AC();
    for (i = 0; major_scenes[i].idx != 0x2D; i++) {
        if (major_scenes[i].Init != NULL) {
            major_scenes[i].Init();
        }
    }
    if (VIGetDTVStatus() != NULL &&
        (db_804D6B30 & 0x200 || OSGetProgressiveMode() == 1))
    {
        gm_80479D30.nums.curr_major = 0x27;
    } else {
        gm_80479D30.nums.curr_major = 0x28;
    }
    gm_80479D30.nums.prev_major = 0x2D;

    while (true) {
        u8 major = gm_801A43A0(gm_80479D30.nums.curr_major);
        if (gmMainLib_8046B0F0.x4 != 0) {
            gmMainLib_8046B0F0.x4 = 0;
        }
        gamestate->nums.prev_major = gamestate->nums.curr_major;
        gamestate->nums.curr_major = major;
    }
}

/// #gm_801A45E8

u8 gm_801A4624(void)
{
    return gm_80479D58.unk_10;
}

/// #gm_801A4634

/// #gm_801A4674

/// #gm_801A46B8

/// #fn_801A46F4

/// #fn_801A47E4

/// #gm_801A48A4

/// #gm_801A4970

void gm_801A4B08(s32 arg0, s32 arg1)
{
    gm_80479D58.unk_14 = arg0;
    gm_80479D58.unk_18 = arg1;
}

/// #gm_801A4B1C

void gm_801A4B40(s32 arg0)
{
    M2C_FIELD(&gm_80479D58, s32*, 0x30) = arg0;
}

void gm_801A4B50(s32 arg0)
{
    M2C_FIELD(&gm_80479D58, s32*, 0x34) = arg0;
}

void gm_801A4B60(void)
{
    gm_80479D58.unk_C = 1;
}

void gm_801A4B74(void)
{
    gm_80479D58.unk_C = 2;
}

void gm_801A4B88(UNK_T arg0)
{
    gm_804D6720 = arg0;
}

extern void* gm_804D6720;

s32 gm_801A4B90(void)
{
    return M2C_FIELD(gm_804D6720, s32*, 4);
}

extern void* gm_804D6720;

s8* gm_801A4B9C(void)
{
    return (s8*) M2C_FIELD(gm_804D6720, s32*, 8);
}

struct gm_80479D58_t* gm_801A4BA8(void)
{
    return gm_80479D58.unk_0;
}

s32 gm_801A4BB8(void)
{
    return gm_80479D58.unk_8;
}

s32 gm_801A4BC8(void)
{
    return gm_804D672C;
}

void fn_801A4BD0(void) {}

/// #gm_801A4BD4

/// #gm_801A4CE0

/// #gm_801A4D34

MajorScene* gm_801A50A0(void)
{
    return &gm_803DA920;
}

MajorScene* gm_801A50AC(void)
{
    return &gm_803DACA4;
}

/// #gm_801A50B8

/// #gm_801A5130

/// #gm_801A51A8

/// #gm_801A5220

s8* gm_801A5244(void)
{
    return &gmMainLib_804D3EE0->unk_590;
}

UNK_T gm_801A5250(void)
{
    return &gm_804D6730;
}

/// #gm_801A5258

/// #gm_801A52D0

/// #gm_801A5360

/// #gm_801A5598

/// #gm_801A55C4

/// #gm_801A55EC

void gm_801A5614(void) {}

/// #gm_801A5618

/// #gm_801A5680

/// #gm_801A5754

/// #gm_801A57A8

/// #gm_801A583C

/// #gm_801A5AF0

/// #gm_801A5C3C

/// #gm_801A5EC8

/// #gm_801A5F00

/// #gm_801A5F64

/// #gm_801A6254

/// #gm_801A6308

/// #gm_801A632C

/// #gm_801A637C

/// #gm_801A64A8

/// #gm_801A659C

/// #gm_801A6630

/// #fn_801A6664

/// #fn_801A6844

/// #fn_801A6868

/// #gm_801A68D8

/// #fn_801A6A48

/// #fn_801A6ACC

/// #fn_801A6B6C

/// #fn_801A6C30

/// #gm_801A6C54

/// #fn_801A6D78

/// #gm_801A6DC0

/// #gm_801A6EE4

/// #gm_801A7070

/// #gm_801A79D4

/// #fn_801A7A44

/// #fn_801A7A68

/// #fn_801A7A8C

/// #gm_801A7B00

/// #fn_801A7FB4

/// #fn_801A80CC

/// #fn_801A80F0

/// #gm_801A8114

/// #fn_801A851C

/// #gm_801A85E4

/// #gm_801A8D54

/// #gm_801A9094

/// #fn_801A9498

/// #fn_801A94BC

/// #gm_801A9630

/// #gm_801A9B30

/// #gm_801A9D0C

/// #gm_801A9DD0

/// #fn_801A9FCC

/// #fn_801AA0E8

/// #gm_801AA110

/// #gm_801AA28C

/// #gm_801AA644

/// #gm_801AA664

/// #gm_801AA688

/// #gm_801AA6D8

/// #gm_801AA6FC

/// #gm_801AA774

/// #gm_801AA7C4

/// #fn_801AA7F8

/// #fn_801AA854

/// #fn_801AAA28

/// #fn_801AAABC

/// #fn_801AAB18

/// #fn_801AAB74

/// #fn_801AB200

/// #fn_801AC67C

/// #gm_801AC6D8

void gm_801ACC90(void) {}

UNK_T gm_801ACC94(void)
{
    return &gm_803DD2C0;
}

/// #gm_801ACCA0

/// #gm_801ACD8C

/// #gm_801ACE94

/// #gm_801ACF8C

/// #gm_801AD088

/// #gm_801AD254

/// #gm_801AD620

/// #gm_801AD874

/// #gm_801AD8EC

/// #fn_801AD920

/// #gm_801ADB04

/// #gm_801ADC88

/// #gm_801ADCE4

/// #gm_801ADDA8

/// #gm_801ADDD8

/// #gm_801ADE1C

/// #gm_801AE050

/// #gm_801AE44C

/// #gm_801AE544

/// #gm_801AE640

/// #gm_801AE74C

/// #gm_801AE848

/// #fn_801AE948

/// #gm_801AEBB0

/// #gm_801AECC4

/// #gm_801AEDC8

/// #gm_801AEE6C

/// #gm_801AF0D4

/// #gm_801AF250

/// #gm_801AF568

/// #gm_801B0264

/// #gm_801B0304

/// #gm_801B0348

/// #gm_801B0474

/// #gm_801B05F4

/// #gm_801B0620

/// #gm_801B0664

/// #gm_801B06B0

/// #gm_801B0730

/// #gm_801B07B4

/// #gm_801B07E8

/// #gm_801B087C

/// #gm_801B089C

/// #gm_801B099C

/// #gm_801B09C0

/// #fn_801B09F8

/// #gm_801B0A34

/// #fn_801B0A8C

/// #gm_801B0AC8

/// #gm_801B0B00

/// #gm_801B0B24

/// #gm_801B0B48

/// #gm_801B0B8C

/// #gm_801B0BF0

/// #gm_801B0C18

/// #gm_801B0C50

/// #gm_801B0C74

/// #gm_801B0CF0

/// #gm_801B0DD0

/// #gm_801B0F1C

/// #gm_801B0F60

/// #gm_801B0F90

/// #gm_801B0FB8

/// #gm_801B0FF8

/// #gm_801B138C

/// #gm_801B13B8

/// #gm_801B14A0

/// #gm_801B14DC

/// #gm_801B1514

/// #gm_801B154C

/// #gm_801B1588

/// #gm_801B15C8

/// #gm_801B1648

/// #gm_801B1688

/// #gm_801B16A8

/// #gm_801B16C8

/// #gm_801B1724

/// #gm_801B174C

/// #gm_801B1788

/// #gm_801B1810

/// #gm_801B1834

/// #gm_801B18D4

/// #gm_801B1A2C

/// #gm_801B1A84

/// #gm_801B1AD4

/// #gm_801B1B74

/// #gm_801B1C24

/// #gm_801B1EB8

/// #gm_801B1EEC

void fn_801B1F6C(void) {}

/// #gm_801B1F70

/// #gm_801B2204

/// #gm_801B2298

/// #gm_801B23C4

/// #gm_801B23F0

/// #gm_801B24B4

/// #gm_801B2510

/// #gm_801B254C

/// #gm_801B25D4

/// #gm_801B26AC

/// #gm_801B2704

/// #gm_801B2790

/// #gm_801B2AF8

/// #gm_801B2B7C

/// #gm_801B2BA4

/// #gm_801B2D54

/// #gm_801B2F78

/// #gm_801B34B8

/// #gm_801B3500

/// #gm_801B3A34

/// #gm_801B3B40

/// #gm_801B3D44

/// #gm_801B3D84

/// #gm_801B3DD8

/// #gm_801B3E44

/// #gm_801B3F18

/// #gm_801B3F40

/// #gm_801B4064

/// #gm_801B4170

/// #gm_801B4254

/// #gm_801B4294

/// #gm_801B42E8

/// #gm_801B4350

/// #gm_801B4408

/// #gm_801B4430

/// #gm_801B44A0

/// #gm_801B45A4

/// #gm_801B461C

/// #gm_801B4684

/// #gm_801B4768

/// #gm_801B47FC

/// #gm_801B4860

/// #gm_801B4974

/// #gm_801B4B28

/// #gm_801B4C5C

/// #gm_801B4D34

/// #gm_801B4DAC

/// #gm_801B4E58

/// #gm_801B4EB8

/// #gm_801B4F44

/// #gm_801B4FCC

/// #gm_801B5078

/// #gm_801B50C4

/// #gm_801B518C

/// #gm_801B51CC

/// #gm_801B5214

/// #gm_801B5324

/// #gm_801B5624

/// #gm_801B59AC

/// #fn_801B5AA8

/// #gm_801B5ACC

/// #gm_801B5E7C

/// #gm_801B5EB4

/// #gm_801B5EE4

/// #gm_801B5F50

/// #gm_801B5FB4

/// #gm_801B607C

/// #gm_801B60A4

/// #gm_801B62D8

UNK_T gm_801B6320(void)
{
    return &gmMainLib_804D3EE0->unk_584;
}

/// #gm_801B632C

/// #gm_801B63C4

/// #gm_801B6428

/// #gm_801B65D4

/// #gm_801B67E8

/// #gm_801B6808

/// #gm_801B6834

/// #gm_801B685C

/// #gm_801B688C

/// #gm_801B69C0

/// #gm_801B6AD8

/// #gm_801B6B70

/// #gm_801B6BE8

/// #gm_801B6F44

/// #gm_801B7044

/// #gm_801B70DC

/// #gm_801B7154

/// #gm_801B74F0

/// #gm_801B75F0

/// #gm_801B7688

/// #gm_801B7700

/// #gm_801B7AA0

/// #gm_801B7B74

/// #gm_801B7C0C

/// #gm_801B7C84

/// #gm_801B8024

/// #gm_801B8110

/// #gm_801B81A8

/// #gm_801B8220

/// #gm_801B8580

/// #gm_801B863C

/// #gm_801B86D4

/// #gm_801B874C

/// #gm_801B8AF8

/// #gm_801B8BB4

/// #gm_801B8BE0

/// #gm_801B8C08

/// #gm_801B8C30

void fn_801B8C5C(void* arg0)
{
    M2C_FIELD(arg0, s16*, 0x12) = 0x12C;
}

/// #gm_801B8C68

/// #gm_801B8C9C

/// #gm_801B8CC4

/// #gm_801B8CF4

/// #gm_801B8D14

/// #gm_801B8D34

/// #gm_801B8D60

/// #gm_801B8D88

/// #gm_801B8DA8

/// #gm_801B8DD4

/// #gm_801B8DFC

/// #gm_801B8E24

/// #fn_801B8E50

/// #gm_801B8E74

/// #gm_801B8EA8

/// #gm_801B8ED0

/// #gm_801B8F04

/// #gm_801B8F24

/// #gm_801B8F44

/// #gm_801B8F70

/// #gm_801B8F98

/// #gm_801B8FB8

/// #gm_801B8FE4

/// #gm_801B900C

/// #gm_801B9034

/// #fn_801B9060

/// #gm_801B9084

/// #gm_801B90B8

/// #gm_801B90E0

/// #gm_801B9114

/// #gm_801B9134

/// #gm_801B9154

/// #gm_801B9180

/// #gm_801B91A8

/// #gm_801B91C8

/// #gm_801B922C

/// #gm_801B9254

/// #gm_801B927C

/// #gm_801B931C

/// #gm_801B9560

/// #gm_801B95B0

/// #gm_801B95D8

/// #gm_801B9600

/// #fn_801B96E8

/// #gm_801B97C4

/// #fn_801B9850

/// #gm_801B98E8

/// #gm_801B999C

/// #gm_801B9A3C

/// #gm_801B9DD8

/// #gm_801B9EB8

/// #gm_801B9EE4

/// #gm_801B9F10

/// #gm_801B9F3C

/// #gm_801B9F64

/// #gm_801B9F8C

void fn_801B9FB8(void* arg0)
{
    M2C_FIELD(arg0, UNK_RET(**)(UNK_PARAMS), 0x38) = gm_80165290;
}

/// #gm_801B9FC8

/// #gm_801B9FFC

/// #gm_801BA024

/// #gm_801BA058

/// #gm_801BA078

/// #gm_801BA098

/// #gm_801BA0C4

/// #gm_801BA0EC

/// #gm_801BA10C

/// #gm_801BA138

/// #gm_801BA160

/// #gm_801BA188

void fn_801BA1B4(struct fn_801BA1B4_arg0_t* arg0)
{
    arg0->x2_b3 = true;
}

/// #gm_801BA1C8

/// #gm_801BA1FC

/// #gm_801BA224

/// #gm_801BA258

/// #gm_801BA278

/// #gm_801BA298

/// #gm_801BA2C4

/// #gm_801BA2EC

/// #gm_801BA30C

/// #gm_801BA338

/// #gm_801BA360

/// #gm_801BA388

void fn_801BA3B4(struct fn_801BA3B4_arg0_t* arg0)
{
    arg0->xC_b4 = true;
}

/// #gm_801BA3C8

/// #gm_801BA3FC

/// #gm_801BA424

/// #gm_801BA458

/// #gm_801BA478

/// #gm_801BA498

/// #gm_801BA4C4

/// #gm_801BA4EC

/// #gm_801BA50C

/// #gm_801BA538

/// #gm_801BA560

/// #gm_801BA588

void fn_801BA5B4(void* arg0)
{
    M2C_FIELD(arg0, f32*, 0x34) = 0.5f;
}

/// #gm_801BA5C0

/// #gm_801BA5F4

/// #gm_801BA61C

/// #gm_801BA650

/// #gm_801BA670

/// #gm_801BA690

/// #gm_801BA6BC

/// #gm_801BA6E4

/// #gm_801BA704

/// #gm_801BA730

/// #gm_801BA758

/// #gm_801BA780

void fn_801BA7AC(void* arg0)
{
    M2C_FIELD(arg0, f32*, 0x34) = 1.25f;
}

/// #gm_801BA7B8

/// #gm_801BA7EC

/// #gm_801BA814

/// #gm_801BA848

/// #gm_801BA868

/// #gm_801BA888

/// #gm_801BA8B4

/// #gm_801BA8DC

/// #gm_801BA8FC

/// #gm_801BA938

/// #gm_801BAA60

/// #gm_801BAAD0

/// #gm_801BAB40

/// #gm_801BAC9C

/// #gm_801BAD70

/// #gm_801BB758

/// #gm_801BBA60

/// #gm_801BBB64

/// #gm_801BBEA8

void gm_801BBFE4(void) {}

/// #fn_801BBFE8

/// #gm_801BC00C

/// #gm_801BC488

/// #gm_801BC4F4

/// #gm_801BC670

/// #gm_801BC754

/// #gm_801BC9E8

/// #gm_801BCAF0

/// #gm_801BCC9C

/// #gm_801BCF20

/// #gm_801BCF40

/// #gm_801BD028

/// #gm_801BD164

/// #gm_801BD30C

/// #gm_801BD44C

/// #gm_801BD46C

/// #gm_801BD658

/// #gm_801BD7FC

/// #gm_801BD93C

/// #gm_801BDAD4

/// #gm_801BDAF4

/// #gm_801BDC08

/// #gm_801BDD44

/// #gm_801BDE94

/// #gm_801BE37C

/// #gm_801BE39C

/// #gm_801BE618

/// #gm_801BE638

/// #gm_801BEA10

/// #gm_801BEA4C

/// #gm_801BEA88

/// #gm_801BEAF0

/// #gm_801BEB2C

void gm_801BEB68(s32 arg0)
{
    M2C_FIELD(gmMainLib_804D3EE0, s32*, 0x548) = arg0;
}

void gm_801BEB74(u8 arg0)
{
    gmMainLib_804D3EE0->unk_535 = arg0;
}

u8 gm_801BEB80(void)
{
    return gmMainLib_804D3EE0->unk_535;
}

/// #gm_801BEB8C

static M2C_UNK gm_803DF918; /* unable to generate initializer: unknown type */

u8 gm_801BEBA8(s8 arg0)
{
    return *(&gm_803DF918 + arg0);
}

/// #gm_801BEBC0

/// #gm_801BEBF8

/// #gm_801BEC54

/// #gm_801BEC80

/// #gm_801BECA8

/// #gm_801BECD0

/// #gm_801BED14

/// #gm_801BED3C

/// #gm_801BEDA8

/// #gm_801BEE58

/// #gm_801BEE9C

/// #gm_801BEF84

void gm_801BEFA4(s8 arg0)
{
    gm_8049C178[0] = arg0;
}

u8 gm_801BEFB0(void)
{
    return gm_8049C178[0];
}

void gm_801BEFC0(s8 arg0)
{
    gm_8049C178[1] = arg0;
}

u8 gm_801BEFD0(void)
{
    return M2C_FIELD(&gm_8049C178, u8*, 1);
}

void gm_801BEFE0(s8 arg0)
{
    M2C_FIELD(&gm_8049C178, s8*, 0xA) = arg0;
}

u8 gm_801BEFF0(void)
{
    return M2C_FIELD(&gm_8049C178, u8*, 0xA);
}

void gm_801BF000(s8 arg0)
{
    M2C_FIELD(&gm_8049C178, s8*, 9) = arg0;
}

u8 gm_801BF010(void)
{
    return M2C_FIELD(&gm_8049C178, u8*, 9);
}

void gm_801BF020(s8 arg0)
{
    M2C_FIELD(&gm_8049C178, s8*, 8) = arg0;
}

u8 gm_801BF030(void)
{
    return M2C_FIELD(&gm_8049C178, u8*, 8);
}

void gm_801BF040(s8 arg0)
{
    M2C_FIELD(&gm_8049C178, s8*, 2) = arg0;
}

u8 gm_801BF050(void)
{
    return M2C_FIELD(&gm_8049C178, u8*, 2);
}

/// #gm_801BF060

/// #gm_801BF128

/// #gm_801BF3F8

/// #gm_801BF4DC

void gm_801BF634(s32 arg0, s8 arg1)
{
    gm_8049E548.pad_0[arg0] = arg1;
}

u8 gm_801BF648(s32 arg0)
{
    return gm_8049E548.pad_0[arg0];
}

void gm_801BF65C(s32 arg0, s8 arg1)
{
    M2C_FIELD(&gm_8049E548.pad_0[arg0], s8*, 4) = arg1;
}

u8 gm_801BF670(s32 arg0)
{
    return M2C_FIELD(&gm_8049E548.pad_0[arg0], u8*, 4);
}

void gm_801BF684(s16 arg0)
{
    gm_8049E548.unk_C = arg0;
}

u8 gm_801BF694(void)
{
    return gm_8049E548.unk_C;
}

void gm_801BF6A8(s8 arg0)
{
    gm_8049E548.unk_A = arg0;
}

u8 gm_801BF6B8(void)
{
    return gm_8049E548.unk_A;
}

void gm_801BF6C8(s8 arg0)
{
    gm_8049E548.unk_8 = arg0;
}

u8 gm_801BF6D8(void)
{
    return gm_8049E548.unk_8;
}

void gm_801BF6E8(s8 arg0)
{
    M2C_FIELD(&gm_8049E548, s8*, 9) = arg0;
}

u8 gm_801BF6F8(void)
{
    return gm_8049E548.unk_9;
}

void gm_801BF708(s8 arg0)
{
    gm_8049E548.unk_E = arg0;
}

u8 gm_801BF718(void)
{
    return gm_8049E548.unk_E;
}

/// #gm_801BF728

/// #gm_801BF834

/// #gm_801BF85C

/// #gm_801BF898

/// #gm_801BF8B8

/// #gm_801BF8D8

/// #gm_801BF8F8

/// #gm_801BF920

/// #gm_801BF948

enum {
    TROPHY_PIKMIN = 0x113,
};

enum {
    LANG_JP = 0,
};

void gm_801BF9A8(UNK_T data)
{
    struct sceneData* scene_data;

    scene_data = gm_801A4284(data);

    if (!un_803048C0(TROPHY_PIKMIN)) {
        if (!lb_8001C2D8(0, "01",
                         lbLang_GetLanguageSetting() == LANG_JP ? "GPIJ"
                                                                : "GPIE",
                         "Pikmin dataFile"))
        {
            un_803124BC();
            Trophy_SetUnlockState(TROPHY_PIKMIN, true);
        }
    }

    // Set scene exit callback?
    gm_801A4330(&lb_8001CE78);

    // Enter major scene
    // Gekko "boot to CSS" code changes scene_id to a hardcoded 2
    gm_801A42F8(scene_data->scene_id);
}

/// #gm_801BFA3C

/// #gm_801BFA6C

/// #gm_801BFABC

/// #gm_801BFBA8

/// #gm_801BFC60

/// #gm_801BFCFC

/// #gm_801BFF7C
