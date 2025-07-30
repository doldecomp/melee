#include "gm_1A36.h"

#include "gm/gm_1A36.static.h"

#include <melee/gm/gmscdata.h>
#include <melee/gm/types.h>

#include <baselib/controller.h>

u64 gm_801A3680(u8 idx)
{
    return controller_map.x0[idx].button;
}

u64 gm_801A36A0(u8 idx)
{
    return controller_map.x0[idx].trigger;
}

u64 gm_801A36C0(u8 idx)
{
    return controller_map.x0[idx].unk;
}

void gm_801A36E0(s32 idx, s32 arg1)
{
    if (idx == 4) {
        controller_map.x0[0].x28 = arg1;
        controller_map.x0[1].x28 = arg1;
        controller_map.x0[2].x28 = arg1;
        controller_map.x0[3].x28 = arg1;
        return;
    }
    controller_map.x0[idx].x28 = arg1;
}

void gm_801A3714(s32 idx, u64 arg1, u64 arg2)
{
    if (arg1 & controller_map.x0[idx].button) {
        controller_map.x0[idx].button |= arg2;
    }
    if (arg1 & controller_map.x0[idx].repeat) {
        controller_map.x0[idx].repeat |= arg2;
    }
    if (arg1 & controller_map.x0[idx].trigger) {
        controller_map.x0[idx].trigger |= arg2;
    }
    if (arg1 & controller_map.x0[idx].release) {
        controller_map.x0[idx].release |= arg2;
    }
}

static void gm_801A3820(s32 idx, u64 arg1, u64 arg2)
{
    struct gm_controller_map* controller = controller_map.x0;
    if (arg1 == (arg1 & controller[idx].button)) {
        controller[idx].button |= arg2;
    }
    if (arg1 == (arg1 & controller[idx].repeat)) {
        controller[idx].repeat |= arg2;
    }
    if (arg1 == (arg1 & controller[idx].button)) {
        if (arg1 & controller[idx].trigger) {
            controller[idx].trigger |= arg2;
        }
    }
    if (arg1 == (arg1 & controller[idx].button)) {
        if (arg1 & controller[idx].release) {
            controller[idx].release |= arg2;
        }
    }
}

static void fn_801A396C(int idx)
{
    struct controller_map* controller = &controller_map;
    if (controller_map.x0[idx].trigger || controller_map.x0[idx].release) {

        controller_map.x0[idx].unk = controller->x0[idx].trigger;
        controller_map.x0[idx].x28 = controller->xF4;
        controller_map.x0[idx].x2C = 0;
        return;
    }
    if (controller_map.x0[idx].x2C < controller->xFC) {
        controller_map.x0[idx].x2C++;
    }

    if (controller_map.x0[idx].x28) {
        controller_map.x0[idx].x28--;
        controller_map.x0[idx].unk = 0;
        return;
    }

    controller_map.x0[idx].unk = controller_map.x0[idx].button;

    if (controller_map.x0[idx].x2C >= controller_map.xFC) {
        controller_map.x0[idx].x28 = controller_map.xFE;
    } else if (controller_map.x0[idx].x2C >= controller_map.xF8) {
        controller_map.x0[idx].x28 = controller_map.xFA;
    } else {
        controller_map.x0[idx].x28 = controller_map.xF6;
    }
}

#pragma push
#pragma dont_inline on
void gm_801A3A74(void)
{
    struct gm_controller_map* controller = controller_map.x0;
    int i;

    PAD_STACK(0x10);

    for (i = 0; i < 4; i++) {
        controller_map.x0[i].button  = HSD_PadCopyStatus[(u8) i].button;
        controller_map.x0[i].trigger = HSD_PadCopyStatus[(u8) i].trigger;
        controller_map.x0[i].repeat  = HSD_PadCopyStatus[(u8) i].repeat;
        controller_map.x0[i].release = HSD_PadCopyStatus[(u8) i].release;
        gm_801A3714(i, 0x01100, (u64) 1 << 32);
        gm_801A3714(i, 0x00200, (u64) 1 << 33);
        gm_801A3820(i, 0x01060, (u64) 1 << 34);
        gm_801A3820(i, 0x01160, (u64) 1 << 35);
        gm_801A3714(i, 0x10008, (u64) 1 << 36);
        gm_801A3714(i, 0x20004, (u64) 1 << 37);
        gm_801A3714(i, 0x40001, (u64) 1 << 38);
        gm_801A3714(i, 0x80002, (u64) 1 << 39);
        controller_map.xF0(i);
    }
    controller_map.x0[4].button = 0;
    controller_map.x0[4].trigger = 0;
    controller_map.x0[4].repeat = 0;
    controller_map.x0[4].release = 0;
    controller_map.x0[4].unk = 0;


    for (i = 0; i < 4; i++) {
        controller[4].button  |= controller[i].button;
        controller[4].trigger |= controller[i].trigger;
        controller[4].repeat  |= controller[i].repeat;
        controller[4].release |= controller[i].release;
        controller[4].unk     |= controller[i].unk;
    }
}
#pragma pop

void gm_801A3E88(void)
{
    static struct controller_map gm_803DA788 = {
        { 0 },
        NULL,
        0x14,
        0x8,
        0x28,
        0x4,
        0x64,
        0x2,
    };

    controller_map = gm_803DA788;

    controller_map.x0[0].x28 = controller_map.xF4;
    controller_map.x0[1].x28 = controller_map.xF4;
    controller_map.x0[2].x28 = controller_map.xF4;
    controller_map.x0[3].x28 = controller_map.xF4;
    controller_map.x0[4].x28 = controller_map.xF4;
    controller_map.xF0 = fn_801A396C;
}

void gm_801A3EF4(void)
{
    MajorScene* scene;
    for (scene = gm_801A50AC(); scene->idx != MJ_COUNT; scene++) {
        if (scene->Init != NULL) {
            scene->Init();
        }
    }
}
