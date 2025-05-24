#include "db_2253.static.h"

#include "ft/ftlib.h"
#include "it/inlines.h"
#include "it/item.h"
#include "it/types.h"
#include "lb/lbarchive.h"

#include <common_structs.h>
#include <dolphin/card/CARDMount.h>
#include <dolphin/mtx/types.h>
#include <dolphin/mtx/vec.h>
#include <dolphin/vi/vi.h>
#include <baselib/controller.h>
#include <MSL/trigf.h>

void db_80225374(void)
{
    PADStatus status[4];
    s32 memSize;
    s32 sectorSize;
    int done;
    int pad;

    do {
        VIWaitForRetrace();
        PADRead(status);
        done = 1;
        for (pad = 0; pad < 4; ++pad) {
            if (status[pad].err == -2 || status[pad].err == -3) {
                done = 0;
            }
        }
    } while (!done);

    for (pad = 0; pad < 4; ++pad) {
        if (status[pad].err == 0) {
            break;
        }
    }

    db_804D6B30 = (pad != 4) ? status[pad].button : 0;

    while (CARDProbeEx(0, &memSize, &sectorSize) == -1) {
        VIWaitForRetrace();
    }
}

void db_802254B8(void)
{
    struct {
        char** bonus_names;
        char** motionstate_names;
        char** submotion_names;
    }* commonData;
    int stack[2];

    if (g_debugLevel >= 3) {
        db_8049FA00[0].x10 = 0;
        db_8049FA00[0].xC = 0;
        db_8049FA00[0].x8 = 0;
        db_8049FA00[0].x0 = 0;

        db_8049FA00[1].x10 = 0;
        db_8049FA00[1].xC = 0;
        db_8049FA00[1].x8 = 0;
        db_8049FA00[1].x0 = 0;

        db_8049FA00[2].x10 = 0;
        db_8049FA00[2].xC = 0;
        db_8049FA00[2].x8 = 0;
        db_8049FA00[2].x0 = 0;

        db_8049FA00[3].x10 = 0;
        db_8049FA00[3].xC = 0;
        db_8049FA00[3].x8 = 0;
        db_8049FA00[3].x0 = 0;

        lbArchive_80016C64("DbCo.dat", (void**) &commonData,
                           "dbLoadCommonData", 0);

        bonus_names = commonData->bonus_names;
        motionstate_names = commonData->motionstate_names;
        submotion_names = commonData->submotion_names;

        fn_8022659C();
        fn_802267C8();
        fn_80225A00();
        fn_80228318();
        fn_80226E00();
        fn_80227174();
        fn_80228CF4();
        fn_80229220();
        fn_802287C4();
    }
}

int fn_8022558C(int x)
{
    return db_8049FA00[x].x0;
}

int fn_802255A4(int x)
{
    return db_8049FA00[x].x8;
}

int fn_802255BC(int x)
{
    return db_8049FA00[x].x10;
}

void db_802255D4(void)
{
    int stack[4];
    int i;

    OSReport("[all PLink num] -- Report --\n");
    for (i = 0; i < 10; i++) {
        OSReport("%5d ", i);
    }
    OSReport("\n");
    OSReport("------------------------------------------------------------\n");

    for (i = 0; i < 64; i++) {
        int count = 0;
        HSD_GObj* var_r3 = ((HSD_GObj**) HSD_GObj_Entities)[i & 0xFF];
        while (var_r3 != NULL) {
            var_r3 = var_r3->next;
            count += 1;
        }
        OSReport("%5d ", count);
        if ((i % 10) == 9) {
            OSReport("\n");
        }
    }
    OSReport("\n");
}

void db_802256CC(void)
{
    u8* peak = _stack_end + 4;
    while (*peak == 0xAA) {
        peak += 1;
    }
    OSReport("------ Thread info ------\n");
    OSReport("base:%x, end:%x, size:%d peak:%d \n", _stack_addr, _stack_end,
             _stack_addr - _stack_end, _stack_addr - peak);
    OSReport("\n");
}

static inline int db_get_pad_button(int i)
{
    return HSD_PadMasterStatus[i & 0xFF].button;
}

static inline int db_get_pad_repeat(int i)
{
    return HSD_PadMasterStatus[i & 0xFF].repeat;
}

void db_80225754(void)
{
    int stack[4];
    int i;
    int num_players;
    if (g_debugLevel < 3) {
        return;
    }
    if (ftLib_800860E8() || ftLib_80086140()) {
        num_players = 2;
    } else {
        num_players = 4;
    }
    for (i = 0; i < num_players; i++) {
        int button = db_get_pad_button(i);
        int repeat = db_get_pad_repeat(i);
        if (button & HSD_PAD_DPADUP) {
            if (button & HSD_PAD_DPADLEFT) {
                button &= ~(HSD_PAD_DPADUP | HSD_PAD_DPADLEFT);
            }
            if (button & HSD_PAD_DPADRIGHT) {
                button &= ~(HSD_PAD_DPADUP | HSD_PAD_DPADRIGHT);
            }
        }
        if (button & HSD_PAD_DPADDOWN) {
            if (button & HSD_PAD_DPADLEFT) {
                button &= ~(HSD_PAD_DPADDOWN | HSD_PAD_DPADLEFT);
            }
            if (button & HSD_PAD_DPADRIGHT) {
                button &= ~(HSD_PAD_DPADDOWN | HSD_PAD_DPADRIGHT);
            }
        }
        if (repeat & HSD_PAD_DPADUP) {
            if (repeat & HSD_PAD_DPADLEFT) {
                repeat &= ~(HSD_PAD_DPADUP | HSD_PAD_DPADLEFT);
            }
            if (repeat & HSD_PAD_DPADRIGHT) {
                repeat &= ~(HSD_PAD_DPADUP | HSD_PAD_DPADRIGHT);
            }
        }
        if (repeat & HSD_PAD_DPADDOWN) {
            if (repeat & HSD_PAD_DPADLEFT) {
                repeat &= ~(HSD_PAD_DPADDOWN | HSD_PAD_DPADLEFT);
            }
            if (repeat & HSD_PAD_DPADRIGHT) {
                repeat &= ~(HSD_PAD_DPADDOWN | HSD_PAD_DPADRIGHT);
            }
        }
        db_8049FA00[i].x4 = db_8049FA00[i].x0;
        db_8049FA00[i].x0 = button;
        db_8049FA00[i].x8 =
            db_8049FA00[i].x0 & (db_8049FA00[i].x4 ^ db_8049FA00[i].x0);
        db_8049FA00[i].xC =
            db_8049FA00[i].x4 & (db_8049FA00[i].x4 ^ db_8049FA00[i].x0);
        db_8049FA00[i].x10 = repeat;
    }
    for (i = 0; i < 4; i++) {
        fn_8022873C(i);
    }
    for (i = 0; i < 4; i++) {
        fn_80227484(i, db_8049FA00[i].x0, db_8049FA00[i].x8,
                    HSD_PadMasterStatus[i & 0xFF].nml_subStickX,
                    HSD_PadMasterStatus[i & 0xFF].nml_subStickY);
    }
    for (i = 0; i < 4; i++) {
        fn_80228620(i);
    }
    for (i = 0; i < 4; i++) {
        fn_80229240(i);
    }
    for (i = 0; i < 4; i++) {
        fn_802264C4(i);
    }
    for (i = 0; i < 4; i++) {
        fn_80226730(i);
    }
    fn_8022666C();
    for (i = 0; i < 4; i++) {
        fn_80226BD4(i);
    }
    fn_802269C0();
    for (i = 0; i < 4; i++) {
        fn_80226E0C(i);
    }
    for (i = 0; i < 4; i++) {
        fn_802291A0(i);
    }
    for (i = 0; i < 4; i++) {
        fn_802287D8(i);
    }
}

void fn_80225A00(void)
{
    db_8049FAA0.x0 = 0;
    db_8049FAA0.x10 = 0x22;
    db_8049FAA0.x18 = db_8049FAA0.x10;
    db_8049FAA0.x14 = 0;
    db_8049FAA0.x1C = db_8049FAA0.x14;
    db_804D6B3C = 1;
    db_8049FAA0.x20.b0 = 0;
    db_8049FAA0.x20.b1 = 0;
}

#pragma push
#pragma dont_inline on
void fn_80225A54(int arg0)
{
    if (g_debugLevel == 4) {
        if (fn_8022558C(arg0) & 0x200) {
            if (fn_802255A4(arg0) & 2) {
                Item_804A0C64.x4 = Item_804A0C64.x0;
                Item_804A0C64.xC = Item_804A0C64.x8;
                Item_804A0C64.x14 = Item_804A0C64.x10;
                Item_804A0C64.x20 = Item_804A0C64.x1C;
                Item_804A0C64.x28 = Item_804A0C64.x24;
                Item_804A0C64.x30 = Item_804A0C64.x2C;
                Item_804A0C64.x38 = Item_804A0C64.x34;
                Item_804A0C64.x44 = Item_804A0C64.x40;
                Item_804A0C64.x4C = Item_804A0C64.x48;
                Item_804A0C64.x54 = Item_804A0C64.x50;
                Item_804A0C64.x5C = Item_804A0C64.x58;
                Item_804A0C64.x64 = Item_804A0C64.x60;
            }
        }
    }
}
#pragma pop

u32 db_80225B0C(void)
{
    return db_8049FAA0.x20.b0;
}

u32 db_80225B20(void)
{
    return db_8049FAA0.x20.b1;
}

u32 db_80225B34(void)
{
    return db_8049FAA0.x20.b2;
}

void fn_80225B48(void)
{
    HSD_GObj* item_gobj;
    Item* it;

    item_gobj = HSD_GObj_Entities->items;
    while (item_gobj != NULL) {
        it = GET_ITEM(item_gobj);
        if (it->kind == It_Kind_Unk4) {
            it->xDAA_flag.b0 = 1;
        }
        item_gobj = item_gobj->next;
    }
    db_8049FAA0.x20.b2 = 1;
}

void fn_80225B9C(void)
{
    HSD_GObj* item_gobj;
    Item* it;

    item_gobj = HSD_GObj_Entities->items;
    while (item_gobj != NULL) {
        it = GET_ITEM(item_gobj);
        if (it->kind == It_Kind_Unk4) {
            it->xDAA_flag.b0 = 0;
        }
        item_gobj = item_gobj->next;
    }
    db_8049FAA0.x20.b2 = 0;
}

void fn_80225BF0(void)
{
    HSD_GObj* item_gobj;
    Item* it;

    item_gobj = HSD_GObj_Entities->items;
    while (item_gobj != NULL) {
        it = GET_ITEM(item_gobj);
        if (it->xDD0_flag.b0) {
            it->xDAA_flag.b3 = 1;
        }
        item_gobj = item_gobj->next;
    }
    db_8049FAA0.x20.b0 = 1;
}

/// #fn_80225C44

/// #fn_80225C8C

/// #fn_80225CD4

s32 db_80225D1C(void)
{
    return db_8049FAA0.x14;
}

void db_80225D2C(void)
{
    db_8049FAA0.x8 = 0;
}

void db_80225D40(void)
{
    db_8049FAA0.x8 = 1;
}

s32 db_80225D54(HSD_ObjAllocUnk4* arg0)
{
    return db_8049FAA0.x8;
}

/// #db_80225D64

/// #fn_80225D7C

/// #db_80225DD8

/// #fn_80225E6C

/// #fn_80225F20

/// #fn_802260D4

/// #fn_802261BC

/// #fn_802262E0

/// #fn_802264C4

/// #fn_8022659C

/// #fn_8022666C

/// #fn_80226730

/// #fn_802267C8

/// #fn_802268B8

/// #fn_8022697C

/// #fn_802269C0

/// #fn_80226BD4

void fn_80226E00(void)
{
    db_804D6B50 = 0;
}

/// #fn_80226E0C

/// #fn_802270C4

/// #fn_8022713C

void fn_80227174(void)
{
    db_804D6B58 = NULL;
    db_804D6B5C = 0;
    db_804D6B5D = 0;
}

/// #fn_80227188

/// #fn_80227484

/// #fn_802277E8

/// #fn_80227904
void fn_80227904(HSD_GObj* camera, s8 port)
{
    f32 var_f1;
    f32 var_f2;
    f32 var_f2_2;
    f32 var_f3;
    u32 temp_r4;

    var_f2 = HSD_PadMasterStatus[port].nml_subStickX;
    if (var_f2 < 0.0f) {
        var_f1 = -var_f2;
    } else {
        var_f1 = var_f2;
    }
    if (var_f1 < 0.2f) {
        var_f2 = 0.0f;
    }
    var_f3 = HSD_PadMasterStatus[port].nml_subStickY;
    if (var_f3 < 0.0f) {
        var_f2_2 = -var_f3;
    } else {
        var_f2_2 = var_f3;
    }
    if (var_f2_2 < 0.2f) {
        var_f3 = 0.0f;
    }
    temp_r4 = HSD_PadMasterStatus[port].button;

    if (temp_r4 & 1) {
        fn_80227CAC(camera, var_f3);
    } else if (temp_r4 & 2) {
        fn_80227FE0(camera, -var_f2, -var_f3);
    } else {
        fn_80227B64(camera, var_f2, var_f3);
    }
    db_804D6B5C = 0x3C;
}
/// #fn_802279E8

/// #fn_80227B64
void fn_80227B64(HSD_GObj* camera, f32 cstick_x, f32 cstick_y)
{
    if ((cstick_x != 0.0f) || (cstick_y != 0.0f)) {
        fn_802279E8(camera, (Vec3*) &cm_80453004 + 0x6,
                    (Vec3*) &cm_80453004 + 0x5, cstick_x, cstick_y);
    }
}
/// #fn_80227BA8

/// #fn_80227CAC
void fn_80227CAC(HSD_GObj* camera, f32 cstick_y)
{
    Vec3 sp14;
    UNK_T sp10;
    s32 temp_cr0_eq;
    void* temp_r31;

    temp_cr0_eq = cstick_y == 0.0f;
    if ((temp_cr0_eq != 0) && (temp_cr0_eq != 0)) {
        temp_r31 = camera->hsd_obj;
        HSD_CObjGetEyeVector((HSD_CObj*) temp_r31, &sp14);
        PSVECScale(&sp14, &sp14,
                   HSD_CObjGetEyeDistance((HSD_CObj*) temp_r31) *
                       -((0.05f * cstick_y) - 1.0f));
        PSVECSubtract((Vec3*) &cm_80453004 + 0x5, &sp14,
                      (Vec3*) &cm_80453004 + 0x6);
    }
}

/// #fn_80227D38

/// #fn_80227EB0

/// #fn_80227FE0
void fn_80227FE0(HSD_GObj* camera, f32 cstick_x, f32 cstick_y)
{
    Vec3 sp24;
    Vec3 sp18;
    UNK_T sp20;
    Vec3* temp_r3;
    Vec3* temp_r3_2;
    Vec3* temp_r3_3;
    Vec3* temp_r3_4;
    f32 temp_f31;
    f32 temp_f31_2;
    void* temp_r30;

    if ((cstick_x != 0.0f) || (cstick_y != 0.0f)) {
        temp_r30 = camera->hsd_obj;
        temp_f31 = HSD_CObjGetEyeDistance((HSD_CObj*) temp_r30);
        temp_f31_2 =
            0.03f *
            (2.0f *
             (temp_f31 * tanf(0.017453292f *
                              HSD_CObjGetFov((HSD_CObj*) temp_r30) * 0.5f)));
        if (cstick_x != 0.0f) {
            HSD_CObjGetLeftVector((HSD_CObj*) temp_r30, &sp18);
            PSVECScale(&sp18, &sp18, temp_f31_2 * cstick_x);
            temp_r3 = (Vec3*) &cm_80453004 + 0x5;
            PSVECAdd(temp_r3, &sp18, temp_r3);
            temp_r3_2 = (Vec3*) &cm_80453004 + 0x6;
            PSVECAdd(temp_r3_2, &sp18, temp_r3_2);
        }
        if (cstick_y != 0.0f) {
            HSD_CObjGetUpVector((HSD_CObj*) temp_r30, &sp24);
            PSVECScale(&sp24, &sp24, -temp_f31_2 * cstick_y);
            temp_r3_3 = (Vec3*) &cm_80453004 + 0x5;
            PSVECAdd(temp_r3_3, &sp24, temp_r3_3);
            temp_r3_4 = (Vec3*) &cm_80453004 + 0x6;
            PSVECAdd(temp_r3_4, &sp24, temp_r3_4);
        }
    }
}
/// #fn_80228124

/// #fn_80228318

/// #fn_802283F0

/// #fn_80228620

/// #fn_8022873C

void fn_802287C4(void)
{
    db_804D6B8C.b0 = false;
}

/// #fn_802287D8

/// #fn_80228820

void db_8022886C(void)
{
    db_804D6B94 = 0;
    db_804D6B90 = 0;
}

/// #db_8022887C

/// #db_8022892C

/// #fn_802289F8

/// #db_80228A64

/// #fn_80228AB4

/// #fn_80228B28

/// #db_80228C4C

/// #fn_80228CF4

/// #fn_80228D18

/// #fn_80228D38

/// #fn_80228E54

/// #fn_8022900C

/// #fn_802291A0

/// #fn_80229220

/// #fn_80229240
