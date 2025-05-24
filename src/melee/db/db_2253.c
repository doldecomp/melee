#include "db_2253.static.h"

#include "cm/camera.h"
#include "ef/efsync.h"
#include "ft/ft_0D14.h"
#include "ft/ftlib.h"
#include "ft/inlines.h"
#include "gm/gm_1601.h"
#include "gm/gm_1A36.h"
#include "gr/ground.h"
#include "if/ifall.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/types.h"
#include "lb/lbarchive.h"
#include "lb/lbcardgame.h"
#include "pl/player.h"
#include "pl/plbonus.h"
#include "un/un_2FC9.h"

#include <common_structs.h>
#include <dolphin/base/PPCArch.h>
#include <dolphin/card/CARDMount.h>
#include <dolphin/db/db.h>
#include <dolphin/mtx/types.h>
#include <dolphin/mtx/vec.h>
#include <dolphin/vi/vi.h>
#include <baselib/controller.h>
#include <baselib/memory.h>
#include <baselib/particle.h>
#include <MSL/math.h>
#include <MSL/printf.h>
#include <MSL/string.h>
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

void fn_80225C44(void)
{
    HSD_GObj* item_gobj;
    Item* it;

    item_gobj = HSD_GObj_Entities->items;
    while (item_gobj != NULL) {
        it = item_gobj->user_data;
        it->xDAA_flag.b3 = 0;
        item_gobj = item_gobj->next;
    }
    db_8049FAA0.x20.b0 = 0;
}

void fn_80225C8C(void)
{
    HSD_GObj* item_gobj;
    Item* it;

    item_gobj = HSD_GObj_Entities->items;
    while (item_gobj != NULL) {
        it = item_gobj->user_data;
        it->xDAA_flag.b4 = 1;
        item_gobj = item_gobj->next;
    }
    db_8049FAA0.x20.b1 = 1;
}

void fn_80225CD4(void)
{
    HSD_GObj* item_gobj;
    Item* it;

    item_gobj = HSD_GObj_Entities->items;
    while (item_gobj != NULL) {
        it = item_gobj->user_data;
        it->xDAA_flag.b4 = 0;
        item_gobj = item_gobj->next;
    }
    db_8049FAA0.x20.b1 = 0;
}

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

void db_80225D64(Item_GObj* item, Fighter_GObj* owner)
{
    Item* it = GET_ITEM(item);
    it->xDAA_byte |= db_804D6B3C;
}

void fn_80225D7C(void)
{
    HSD_GObj* item_gobj;
    Item* it;

    db_804D6B3C += 1;
    if (db_804D6B3C > 3) {
        db_804D6B3C = 1;
    }
    item_gobj = HSD_GObj_Entities->items;
    while (item_gobj != NULL) {
        it = GET_ITEM(item_gobj);
        it->xDAA_byte &= 0xFC;
        it->xDAA_byte |= db_804D6B3C;
        item_gobj = item_gobj->next;
    }
}

void db_80225DD8(Item_GObj* item, Fighter_GObj* owner)
{
    Item* it = GET_ITEM(item);
    if (ftLib_80086960(owner) == 0) {
        it = GET_ITEM(item);
        it->xDAA_byte |= db_804D6B3C;
        // db_80225D64(item, owner); // stack too big
    } else {
        int x;
        it->xDAA_byte &= 0xFC;
        x = fn_8022697C(owner);
        if (x != 0) {
            it->xDAA_byte |= x & 3;
        }
    }
}

void fn_80225E6C(Fighter_GObj* owner)
{
    Item_GObj* item_gobj;
    Item* it;
    int stack[2];

    item_gobj = HSD_GObj_Entities->items;
    while (item_gobj != NULL) {
        it = GET_ITEM(item_gobj);
        if (it->owner == owner) {
            db_80225DD8(item_gobj, owner);
        }
        item_gobj = item_gobj->next;
    }
}

void fn_80225F20(int player)
{
    int x, y;

    x = fn_8022558C(player);
    if ((x & 64) != 0) {
        y = fn_802255BC(player);
        if ((y & 8) != 0) {
            if (db_8049FAA0.x10 < 0x23) {
                db_8049FAA0.x10++;
                if (db_8049FAA0.x10 == 0x23) {
                    db_8049FAA0.x10 = 0x2B;
                }
            } else if (db_8049FAA0.x10 < 0x2F) {
                db_8049FAA0.x10++;
                if (db_8049FAA0.x10 == 0x2F) {
                    db_8049FAA0.x10 = 0xD0;
                }
            } else if (db_8049FAA0.x10 < 0xE9) {
                db_8049FAA0.x10++;
            }
        }
    }

    x = fn_8022558C(player);
    if ((x & 64) != 0) {
        y = fn_802255BC(player);
        if ((y & 4) != 0) {
            if (db_8049FAA0.x10 >= 0xD0) {
                db_8049FAA0.x10--;
                if (db_8049FAA0.x10 < 0xD0) {
                    db_8049FAA0.x10 = 0x2E;
                }
            } else if (db_8049FAA0.x10 >= 0x2B) {
                db_8049FAA0.x10--;
                if (db_8049FAA0.x10 < 0x2B) {
                    db_8049FAA0.x10 = 0x22;
                }
            } else if (db_8049FAA0.x10 > 0) {
                db_8049FAA0.x10--;
            }
        }
    }

    x = fn_8022558C(player);
    if ((x & 64) != 0) {
        y = fn_802255BC(player);
        if ((y & 2) != 0) {
            if (db_8049FAA0.x14 < 0x1E) {
                db_8049FAA0.x14++;
            }
        }
    }

    x = fn_8022558C(player);
    if ((x & 64) != 0) {
        y = fn_802255BC(player);
        if ((y & 1) != 0) {
            if (db_8049FAA0.x14 > 0) {
                db_8049FAA0.x14--;
            }
        }
    }
}

void fn_802260D4(int player)
{
    HSD_GObj* temp_r30;

    temp_r30 = DevText_GetGObj();
    if (db_8049FAA0.x0 == 2) {
        DevText_ShowBackground(db_804D6B38);
        DevText_ShowText(db_804D6B38);
    } else {
        db_804D6B38 = DevText_Create(8, 20, 20, 40, 1, db_8049FA50);
        if (db_804D6B38 != NULL) {
            GXColor bg = { 0x00, 0x00, 0x00, 0xFF };
            GXColor fg = { 0x00, 0x00, 0x00, 0x00 };
            DevText_Show(temp_r30, db_804D6B38);
            DevText_HideCursor(db_804D6B38);
            DevText_SetBGColor(db_804D6B38, &bg);
            DevText_SetTextColor(db_804D6B38, &fg);
            DevText_SetScale(db_804D6B38, 12.0F, 16.0F);
        }
    }
    db_8049FAA0.x0 = 1;
}

void fn_802261BC(int player)
{
    char* item;
    db_8049FAA0.x18 = db_8049FAA0.x10;
    db_8049FAA0.x1C = db_8049FAA0.x14;
    fn_80225F20(player);
    if (db_8049FAA0.x18 != db_8049FAA0.x10 ||
        db_8049FAA0.x1C != db_8049FAA0.x14)
    {
        db_8049FAA0.xC = player;
        db_8049FAA0.x4 = 0x78;
        if (db_8049FAA0.x0 != 1) {
            fn_802260D4(player);
        }
        DevText_Erase(db_804D6B38);
        DevText_SetCursorXY(db_804D6B38, 0, 0);
        if (db_8049FAA0.x10 < 0x23) {
            item = db_803EA94C[db_8049FAA0.x10];
        } else if (db_8049FAA0.x10 < 0x2F) {
            item = db_803EAA50[db_8049FAA0.x10];
        } else if (db_8049FAA0.x10 < 0xEA) {
            // TODO: this is wrong. return when the data section is good
            item = db_803EA94C[db_8049FAA0.x10];
        } else {
            while (1) {
            }
        }
        DevText_Printf(db_804D6B38, "Item-> %s  Pokemon-> %s", item,
                       db_803EAA50[db_8049FAA0.x14]);
    }
}

void fn_802262E0(int player)
{
    int mask = HSD_PAD_DPADLEFT | HSD_PAD_DPADRIGHT | HSD_PAD_DPADUP |
               HSD_PAD_Z | HSD_PAD_R | HSD_PAD_L | HSD_PAD_A | HSD_PAD_B |
               HSD_PAD_X | HSD_PAD_Y | HSD_PAD_START;
    SpawnItem spawnItem;
    if ((fn_8022558C(player) & mask) != 0) {
        return;
    }
    if ((fn_802255A4(player) & HSD_PAD_DPADDOWN) == 0) {
        return;
    }
    spawnItem.kind = db_8049FAA0.x10;
    if (Item_80266F3C() == 0 && spawnItem.kind < 0x23) {
        return;
    }
    Player_LoadPlayerCoords(player, &spawnItem.prev_pos);
    spawnItem.prev_pos.y += 60.0F;
    spawnItem.prev_pos.z = 0.0F;
    spawnItem.pos = spawnItem.prev_pos;
    spawnItem.facing_dir = it_8026B684(&spawnItem.prev_pos);
    spawnItem.x3C_damage = 0;
    spawnItem.vel.x = spawnItem.vel.y = spawnItem.vel.z = 0.0F;
    spawnItem.x0_parent_gobj = NULL;
    spawnItem.x4_parent_gobj2 = spawnItem.x0_parent_gobj;
    spawnItem.x44_flag.b0 = 1;
    spawnItem.x40 = 0;
    if (spawnItem.kind < 0x23 && Item_804A0C64.x0 >= it_804D6D28->x0) {
        OSReport("Item Max Over.\n");
        return;
    }
    if (spawnItem.kind < 0x2F && Item_804A0C64.x2C >= it_804D6D28->x14) {
        OSReport("couldn't get Item struct.(CZako)");
        return;
    }
    if (spawnItem.kind < 0xD0 || spawnItem.kind >= 0xEA ||
        it_804A0F60[spawnItem.kind - 0xD0] != 0)
    {
        if (spawnItem.kind != 0x22 || it_8026C704() == 0) {
            {
                HSD_GObj* gobj = Item_80268B18(&spawnItem);
                if (gobj != NULL) {
                    GET_ITEM(gobj)->xDAA_flag.u8 |= db_804D6B3C;
                    efSync_Spawn(0x420, gobj, &spawnItem.prev_pos);
                }
            }
        }
    }
}

void fn_802264C4(int player)
{
    if (db_8049FAA0.x0 == 1 && db_8049FAA0.xC == player) {
        if (db_8049FAA0.x4 == 0) {
            db_8049FAA0.x0 = 2;
            DevText_HideBackground(db_804D6B38);
            DevText_HideText(db_804D6B38);
        } else {
            db_8049FAA0.x4 -= 1;
        }
    }
    fn_802261BC(player);
    if (gm_801A45E8(1) == 0 && gm_801A45E8(0) == 0) {
        fn_802262E0(player);
    }
    if (fn_8022558C(player) & 0x20 && fn_802255A4(player) & 8) {
        fn_80225D7C();
    }
    fn_80225A54(player);
}

void fn_8022659C(void)
{
    HSD_GObj* gobj = DevText_GetGObj();
    db_804D6B40.b0 = 0;
    db_8049FAC8.x0 = DevText_Create(6, 20, 20, 60, 7, db_8049FAC8.x4);
    if (db_8049FAC8.x0 != NULL) {
        GXColor bg = { 0xFF, 0xFF, 0xFF, 0xFF };
        GXColor fg = { 0x00, 0x00, 0x00, 0x00 };
        DevText_Show(gobj, db_8049FAC8.x0);
        DevText_HideCursor(db_8049FAC8.x0);
        DevText_SetBGColor(db_8049FAC8.x0, &bg);
        DevText_SetTextColor(db_8049FAC8.x0, &fg);
        DevText_SetScale(db_8049FAC8.x0, 9.0F, 12.0F);
    }
}

void fn_8022666C(void)
{
    int stack[2];
    DevText* text;
    StaticPlayer* player;
    s32 slot;

    if (db_804D6B40.b0) {
        text = db_8049FAC8.x0;
        DevText_Erase(text);
        DevText_SetCursorXY(text, 0, 0);
        DevText_Printf(text, "A B  C D E    F    G");
        for (slot = 0; slot < 6; slot++) {
            player = Player_GetPtrForSlot(slot);
            DevText_Printf(text, "\n%d %d %2d %d %2.2f %2.2f %2.2f",
                           player->player_state, player->cpu_level,
                           player->cpu_type, player->handicap, player->unk50,
                           player->attack_ratio, player->defense_ratio);
        }
    }
}

void fn_80226730(int arg0)
{
    if ((fn_8022558C(arg0) & 0x200) && (fn_802255A4(arg0) & 4)) {
        db_804D6B40.b0 ^= 1;
        if (db_804D6B40.b0 == 0) {
            DevText_HideBackground(db_8049FAC8.x0);
            DevText_HideText(db_8049FAC8.x0);
            return;
        }
        DevText_ShowBackground(db_8049FAC8.x0);
        DevText_ShowText(db_8049FAC8.x0);
    }
}

void fn_802267C8(void)
{
    HSD_GObj* temp_r3;

    temp_r3 = DevText_GetGObj();
    db_804D6B48.b0 = 1;
    db_804D6B48.b9 = 0;
    db_804D6B48.b3 = 0;
    db_8049FE18.x0 = DevText_Create(7, 20, 20, 60, 12, db_8049FE18.x4);
    if (db_8049FE18.x0 != NULL) {
        GXColor bg = { 0xFF, 0xFF, 0xFF, 0xFF };
        GXColor fg = { 0x00, 0x00, 0x00, 0x00 };
        DevText_Show(temp_r3, db_8049FE18.x0);
        DevText_HideCursor(db_8049FE18.x0);
        DevText_SetBGColor(db_8049FE18.x0, &bg);
        DevText_SetTextColor(db_8049FE18.x0, &fg);
        DevText_SetScale(db_8049FE18.x0, 9.0F, 12.0F);
    }
}

void fn_802268B8(void)
{
    HSD_GObj* fighter;
    if (db_804D6B48.b3 != 0) {
        db_804D6B48.b3 = (db_804D6B48.b3 << 1) & 0x3F;
    } else {
        db_804D6B48.b3 = 1;
    }
    for (fighter = HSD_GObj_Entities->fighters; fighter != NULL;
         fighter = fighter->next)
    {
        Fighter* ft = GET_FIGHTER(fighter);
        if ((!db_804D6B48.b3) && (!db_804D6B48.b3)) { // ? permuter
        }
        // ft->x21FC_flag.grouped_bits.b0_to_5 = db_804D6B48.b3;
        ft->x21FC_flag.u8 = db_804D6B48.b3;
    }
    if ((db_804D6B48.b3 & 0x02) != 0) {
        fn_80225BF0();
    } else {
        fn_80225C44();
    }
    if ((db_804D6B48.b3 & 0x08) != 0) {
        fn_80225C8C();
    } else {
        fn_80225B9C();
    }
    if ((db_804D6B48.b3 & 0x20) != 0) {
        fn_80225B48();
    } else {
        fn_80225B9C();
    }
}

u8 fn_8022697C(Fighter_GObj* owner)
{
    if (ftLib_80086960(owner) != 0) {
        Fighter* ft = GET_FIGHTER(owner);
        return ft->x21FC_flag.u8;
    } else {
        return 0;
    }
}

void fn_802269C0(void)
{
    Fighter_GObj* gobj;
    Fighter* ft;
    DevText* text;
    s32 print_newline;
    int stack[4];

    if (db_804D6B48.b9) {
        text = db_8049FE18.x0;
        print_newline = 0;
        DevText_Erase(text);
        DevText_SetCursorXY(text, 0, 0);
        for (gobj = HSD_GObj_Entities->fighters; gobj != NULL;
             gobj = gobj->next)
        {
            ft = gobj->user_data;
            if (print_newline == 0) {
                print_newline = 1;
            } else {
                DevText_Printf(text, "\n");
            }
            if (ft->motion_id < 0x155) {
                DevText_Printf(text, "%d %s", ft->player_id,
                               motionstate_names[ft->motion_id]);
            } else {
                DevText_Printf(text, "%d %d", ft->player_id, ft->motion_id);
            }
            DevText_SetCursorX(text, 0x17);
            if (ft->anim_id != -1) {
                if (ft->anim_id < 0x127) {
                    DevText_Printf(text, "%s", submotion_names[ft->anim_id]);
                } else {
                    DevText_Printf(text, "%d", ft->anim_id);
                }
            }
            DevText_SetCursorX(text, 0x2C);
            DevText_Printf(text, "%03.2f", ft->cur_anim_frame);
            if (ft->x221C_u16_y) {
                DevText_SetCursorX(text, 0x34);
                if (ft->x221C_u16_y & 1) {
                    DevText_Printf(text, "L");
                } else {
                    DevText_Printf(text, " ");
                }
                if (ft->x221C_u16_y & 2) {
                    DevText_Printf(text, "R");
                } else {
                    DevText_Printf(text, " ");
                }
                if (ft->x221C_u16_y & 4) {
                    DevText_Printf(text, "T");
                } else {
                    DevText_Printf(text, " ");
                }
            }
        }
    }
}

void fn_80226BD4(int arg0)
{
    HSD_GObj* gobj;
    Fighter* ft;
    if (fn_8022558C(arg0) & HSD_PAD_R) {
        if (fn_802255A4(arg0) & HSD_PAD_DPADUP) {
            db_804D6B48.b3++;
            if (db_804D6B48.b3 > 3) {
                db_804D6B48.b0 = 1;
            }
            for (gobj = HSD_GObj_Entities->fighters; gobj != NULL;
                 gobj = gobj->next)
            {
                ft = GET_FIGHTER(gobj);
                ft->x21FC_flag.u8 = db_804D6B48.b3;
            }
        }
        if ((fn_802255A4(arg0) & HSD_PAD_DPADRIGHT) &&
            Player_GetPlayerSlotType(arg0) != 3)
        {
            unsigned int x;
            gobj = Player_GetEntity(arg0);
            ft = GET_FIGHTER(gobj);
            // x = ft->x21FC_flag.grouped_bits.b6_to_7 + 1;
            x = ft->x21FC_flag.u8 + 1;
            if (x > 3) {
                ft->x21FC_flag.u8 = 1;
            } else {
                ft->x21FC_flag.u8 = x;
            }
            fn_80225E6C(gobj);
        }
        if (fn_802255A4(arg0) & HSD_PAD_DPADLEFT) {
            fn_802268B8();
        }
    }
    if ((fn_8022558C(arg0) & HSD_PAD_Y) &&
        (fn_8022558C(arg0) & HSD_PAD_DPADDOWN))
    {
        db_804D6B48.b9 = db_804D6B48.b9 ^ 1;
        if (!db_804D6B48.b9) {
            DevText_HideBackground(db_8049FE18.x0);
            DevText_HideText(db_8049FE18.x0);
        } else {
            DevText_ShowBackground(db_8049FE18.x0);
            DevText_ShowText(db_8049FE18.x0);
        }
    }
    if (fn_8022558C(arg0) & HSD_PAD_Y) {
        if ((fn_802255A4(arg0) & HSD_PAD_DPADLEFT) &&
            (Player_GetPlayerSlotType(arg0) != 3))
        {
            gobj = Player_GetEntity(arg0);
            if (fn_8022558C(arg0) & HSD_PAD_A) {
                ftCo_800D1E80(gobj);
            } else {
                ftCo_800D14E4(gobj);
            }
        }
        if ((fn_802255A4(arg0) & HSD_PAD_DPADRIGHT) &&
            (Player_GetPlayerSlotType(arg0) != 3))
        {
            gobj = Player_GetEntity(arg0);
            if (fn_8022558C(arg0) & HSD_PAD_A) {
                ftCo_800D237C(gobj);
                return;
            }
            ftCo_800D1A8C(gobj);
        }
    }
}

void fn_80226E00(void)
{
    db_804D6B50 = 0;
}

void fn_80226E0C(int arg0)
{
    if ((fn_8022558C(arg0) & 0x20) && (fn_802255A4(arg0) & 4)) {
        db_804D6B50 += 1;
        switch (db_804D6B50) {
        default:
            fn_802270C4(1);
            Camera_80030B0C(0);
            Camera_80030A60(0);
            Camera_80030A8C(0);
            fn_8022713C(0);
            Camera_80030B38(0);
            Camera_80030B64(0);
            Camera_80030B90(0);
            db_804D6B50 = 0;
            break;
        case 1:
            fn_802270C4(0);
            Camera_80030B0C(0);
            Camera_80030A60(0);
            Camera_80030A8C(0);
            fn_8022713C(0);
            Camera_80030B38(0);
            Camera_80030B64(0);
            Camera_80030B90(0);
            break;
        case 2:
            fn_802270C4(1);
            Camera_80030B0C(1);
            Camera_80030A60(0);
            Camera_80030A8C(1);
            fn_8022713C(0);
            Camera_80030B38(0);
            Camera_80030B64(0);
            Camera_80030B90(1);
            break;
        case 3:
            fn_802270C4(0);
            Camera_80030B0C(0);
            Camera_80030A60(0);
            Camera_80030A8C(1);
            fn_8022713C(1);
            Camera_80030B38(0);
            Camera_80030B64(0);
            Camera_80030B90(1);
            break;
        case 4:
            fn_802270C4(0);
            Camera_80030B0C(0);
            Camera_80030A60(1);
            Camera_80030A8C(1);
            fn_8022713C(1);
            Camera_80030B38(0);
            Camera_80030B64(0);
            Camera_80030B90(1);
            break;
        case 5:
            fn_802270C4(0);
            Camera_80030B0C(0);
            Camera_80030A60(1);
            Camera_80030A8C(1);
            fn_8022713C(1);
            Camera_80030B38(1);
            Camera_80030B64(0);
            Camera_80030B90(1);
            break;
        case 6:
            fn_802270C4(0);
            Camera_80030B0C(0);
            Camera_80030A60(1);
            Camera_80030A8C(1);
            fn_8022713C(1);
            Camera_80030B38(0);
            Camera_80030B64(1);
            Camera_80030B90(1);
            break;
        }
    }
    if ((fn_8022558C(arg0) & 0x400) && (fn_802255A4(arg0) & 4)) {
        if (db_804D6B80 < 2 && db_804D6B80 >= 0) {
            Ground_801C1FFC();
            Camera_80030AA4(1);
        } else {
            Camera_80030AA4(0);
        }
    }
}

void fn_802270C4(int arg0)
{
    Fighter_GObj* gobj;
    Fighter* ft;
    int stack;

    for (gobj = HSD_GObj_Entities->fighters; gobj != NULL; gobj = gobj->next) {
        ft = GET_FIGHTER(gobj);
        if ((ft != NULL) && (ft->x20A8 != 0)) {
            ft->x20A4.b5 = !arg0;
            lbShadow_8000EEE0(gobj);
        }
    }
}

void fn_8022713C(int arg0)
{
    HSD_GObj* gobj;
    struct {
        u8 pad[0x10];
        UnkFlagStruct x10;
    }* thing;

    for (gobj = HSD_GObj_Entities->x14; gobj != NULL; gobj = gobj->next) {
        thing = gobj->user_data;
        if (thing != NULL) {
            thing->x10.b7 = arg0;
        }
    }
}

void fn_80227174(void)
{
    db_804D6B58 = NULL;
    db_804D6B5C = 0;
    db_804D6B5D = 0;
}

void fn_80227188(void)
{
    Vec3 camera;
    Vec3 interest;
    HSD_CObj* cobj;
    HSD_GObj* gobj;
    float fov, ang;
    int eye_x, eye_y, eye_z;
    int int_x, int_y, int_z;
    int stack;

    gobj = Camera_80030A50();
    if (db_804D6B58 != NULL) {
        if ((gobj != NULL) && (db_804D6B5D != 0)) {
            if (db_804D6B5C > 1) {
                cobj = gobj->hsd_obj;
                HSD_CObjGetEyePosition(cobj, &camera);
                HSD_CObjGetInterest(cobj, &interest);
                fov = HSD_CObjGetFov(cobj);
                ang = rad_to_deg *
                      atan2f(interest.y - camera.y, -(interest.z - camera.z));
                DevText_Erase(db_804D6B58);
                DevText_SetCursorXY(db_804D6B58, 0, 0);
                if (ABS(camera.z) > 99999.0F) {
                    eye_z = -1;
                } else {
                    eye_z = camera.z;
                }
                if (ABS(camera.y) > 99999.0F) {
                    eye_y = -1;
                } else {
                    eye_y = camera.y;
                }
                if (ABS(camera.x) > 99999.0F) {
                    eye_x = -1;
                } else {
                    eye_x = camera.x;
                }
                DevText_Printf(db_804D6B58, "EYE %d,%d,%d", eye_x, eye_y,
                               eye_z);
                DevText_SetCursorXY(db_804D6B58, 0, 1);
                if (ABS(interest.z) > 99999.0F) {
                    int_z = -1;
                } else {
                    int_z = interest.z;
                }
                if (ABS(interest.y) > 99999.0F) {
                    int_y = -1;
                } else {
                    int_y = interest.y;
                }
                if (ABS(interest.x) > 99999.0F) {
                    int_x = -1;
                } else {
                    int_x = interest.x;
                }
                DevText_Printf(db_804D6B58, "INT %d,%d,%d", int_x, int_y,
                               int_z);
                DevText_SetCursorXY(db_804D6B58, 0, 2);
                DevText_Printf(db_804D6B58, "FOV %d  ANG %d", (int) fov,
                               (int) ang);
                DevText_ShowBackground(db_804D6B58);
                DevText_ShowText(db_804D6B58);
            } else if (db_804D6B5C == 1) {
                DevText_HideBackground(db_804D6B58);
                DevText_HideText(db_804D6B58);
            } else {
                return;
            }
            db_804D6B5C--;
        } else {
            DevText_HideBackground(db_804D6B58);
            DevText_HideText(db_804D6B58);
        }
    }
}

void fn_80227484(int arg0, int arg1, int arg2, f32 arg3, f32 arg4)
{
    if (gm_8018841C() == 0 && gm_801A4310() != 0xA) {
        if (Camera_80030178() == 0 && Camera_80030154() == 0) {
            if (!(ABS(arg3) > 0.6F)) {
                if (ABS(arg4) > 0.6F) {
                    GXColor bg = { 0x00, 0x00, 0x00, 0x00 };
                    GXColor fg = { 0xFF, 0xFF, 0xFF, 0xFF };
                    HSD_GObj* gobj = DevText_GetGObj();
                    if (db_804D6B58 == NULL && gobj != NULL) {
                        if ((db_804D6B58 = DevText_Create(12, 420, 360, 32, 3,
                                                          db_804A03C0)))
                        {
                            DevText_Show(gobj, db_804D6B58);
                            DevText_HideCursor(db_804D6B58);
                            DevText_SetBGColor(db_804D6B58, &bg);
                            DevText_SetTextColor(db_804D6B58, &fg);
                            DevText_SetScale(db_804D6B58, 12.0F, 16.0F);
                            DevText_HideBackground(db_804D6B58);
                            DevText_HideText(db_804D6B58);
                        }
                    }
                }
                Camera_8003006C();
            }
        } else {
            if (arg2 & 8) {
                GXColor bg = { 0x00, 0x00, 0x00, 0x00 };
                GXColor fg = { 0xFF, 0xFF, 0xFF, 0xFF };
                HSD_GObj* gobj = DevText_GetGObj();
                if (db_804D6B58 == NULL && gobj != NULL) {
                    if ((db_804D6B58 =
                             DevText_Create(12, 420, 360, 32, 3, db_804A03C0)))
                    {
                        DevText_Show(gobj, db_804D6B58);
                        DevText_HideCursor(db_804D6B58);
                        DevText_SetBGColor(db_804D6B58, &bg);
                        DevText_SetTextColor(db_804D6B58, &fg);
                        DevText_SetScale(db_804D6B58, 12.0F, 16.0F);
                        DevText_HideBackground(db_804D6B58);
                        DevText_HideText(db_804D6B58);
                    }
                }
                if ((arg1 & 0xC60) == 0) {
                    if (Camera_80030178() != 0) {
                        Camera_8002FEEC(arg0);
                    } else if (Camera_80030154() != 0) {
                        Camera_800300F0();
                    } else {
                        Camera_8003006C();
                    }
                }
            }
        }
    }
    if (Camera_80030154() != 0) {
        fn_802277E8(Camera_80030A50(), arg0);
    } else if (Camera_80030178() != 0) {
        fn_80227904(Camera_80030A50(), arg0);
    }
    if (Camera_80030178() != 0 && db_804D6B50 - 3 <= 1) {
        if (arg2 & 0x200) {
            db_804D6B5D = !db_804D6B5D;
        }
    } else {
        db_804D6B5D = 0;
    }
    fn_80227188();
    if ((fn_8022558C(arg0) & 0x400) && (fn_802255A4(arg0) & 4)) {
        switch (db_804D6B80) {
        case 2:
            Camera_80030740(0xFF, 0xFF, 0xFF);
            break;
        case 3:
            Camera_80030740(0, 0, 0);
            break;
        }
    }
}

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

void fn_8022873C(int arg0)
{
    if ((fn_8022558C(arg0) & 0x400) && (fn_802255A4(arg0) & 0x4)) {
        db_804D6B80++;
        if (3 < db_804D6B80) {
            db_804D6B80 = 0;
        }
        if (db_804D6B80 == 0) {
            ifAll_802F36A4();
        } else if (!ifAll_802F36B0()) {
            ifAll_802F3698();
        }
    }
}

void fn_802287C4(void)
{
    db_804D6B8C.b0 = false;
}

void fn_802287D8(int arg0)
{
    if ((fn_8022558C(arg0) & 0x100) && (fn_802255A4(arg0) & 0x2)) {
        fn_80228820();
    }
}

void fn_80228820(void)
{
    db_804D6B8C.b0 ^= 1;
    if (db_804D6B8C.b0) {
        gm_8016B274(5.0f);
    } else {
        gm_8016B2C8();
    }
}

void db_8022886C(void)
{
    db_804D6B94 = 0;
    db_804D6B90 = 0;
}

void db_8022887C(void)
{
    int i;

    for (i = 0; i < 4; i++) {
        if ((HSD_PadMasterStatus[i].button & HSD_PAD_Y) &&
            (HSD_PadMasterStatus[i].trigger & HSD_PAD_DPADUP))
        {
            db_804D6B90 = 1;
        }
    }
}

void db_8022892C(void)
{
    char spC[32];
    int temp_r3;
    int temp_r5;
    int temp_ret;
    void* var_r30;

    if (db_804D6B90 != 0) {
        HSD_VIWaitXFBFlush();
        temp_ret = HSD_VIGetXFBLastDrawDone();
        temp_r3 = temp_ret;
        if (temp_r3 != -1) {
            var_r30 = HSD_VIData.xfb[temp_r3].buffer;
        } else {
            OSReport("cant find xfb!\n");
            ((0) ? ((void) 0) : __assert("dbscreenshot.c", 61, "0"));
        }
        temp_r5 = db_804D6B94;
        db_804D6B94 = temp_r5 + 1;
        sprintf(spC, "USB:shot/screenshot%02d.frb", temp_r5);
        fn_802289F8(spC, (int) var_r30,
                    HSD_VIData.current.vi.rmode.fbWidth *
                        HSD_VIData.current.vi.rmode.xfbHeight * 2);
        db_804D6B90 = 0;
    }
}

int fn_802289F8(char* arg0, int arg1, int arg2)
{
    if (strncmp(arg0, "USB:", 4) == 0) {
        return hsd_80393A5C(arg0 + 4, arg1, arg2);
    } else {
        return -1;
    }
}

void db_80228A64(void)
{
    OSContext* ctx;

    PPCMtmsr(PPCMfmsr() | 0x900);
    ctx = OSGetCurrentContext();
    OSSaveFPUContext(ctx);
    ctx->fpscr &= 0xFFFFF;
    OSLoadFPUContext(ctx);
}

void fn_80228AB4(OSContext* ctx)
{
    HSD_VISetUserPreRetraceCallback(NULL);
    HSD_VISetUserPostRetraceCallback(NULL);
    lb_80019A48();
    OSReport("%s\n", "DATE Feb 13 2002  TIME 22:06:27");
    Exception_ReportStackTrace(ctx, 0x10);
    hsd_80397DFC(0x1388);
    Exception_StoreDebugLevel(g_debugLevel);
    hsd_80397DA4(ctx);
}

void fn_80228B28(u16 error, OSContext* ctx, ...)
{
    int dsisr, dar;

    va_list va;
    va_start(va, ctx);

    dsisr = va_arg(va, int);
    dar = va_arg(va, int);

    HSD_VISetUserPreRetraceCallback(NULL);
    HSD_VISetUserPostRetraceCallback(NULL);
    lb_80019A48();
    OSReport("%s\n", "DATE Feb 13 2002  TIME 22:06:27");
    Exception_ReportStackTrace(ctx, 0x10);
    Exception_ReportCodeline(error, dsisr, dar, ctx);
    hsd_80397DFC(0x1388);
    Exception_StoreDebugLevel(g_debugLevel);
    hsd_80397DA4(ctx);

    va_end(va);
}

void db_80228C4C(void)
{
    u16 x;
    if (DBIsDebuggerPresent() == 0) {
        void* mem = OSAllocFromArenaLo(0x2000, 4);
        hsd_80393DA0(mem, 0x2000);
        HSD_SetPanicCallback((PanicCallback) fn_80228AB4);
        for (x = 0; x < 16; x++) {
            switch (x) {
            case 4:
            case 7:
            case 8:
            case 9:
                break;
            default:
                OSSetErrorHandler(x, fn_80228B28);
            }
        }
    }
}

void fn_80228CF4(void)
{
    fn_80228D18();
    fn_80228D38();
}

void fn_80228D18(void)
{
    db_804D6B98.x0 = 0xFF;
    db_804D6B98.x1.b0 = 0;
}

void fn_80228D38(void)
{
    HSD_GObj* gobj;
    int i;
    gobj = DevText_GetGObj();
    db_804D6B9C = HSD_MemAlloc(sizeof(*db_804D6B9C) * 2);
    for (i = 0; i < 2; i++) {
        db_804D6B9C[i].text =
            DevText_Create(i + 10, i * 300, 0, 25, 30, db_804D6B9C[i].buffer);
        if (db_804D6B9C[i].text != NULL) {
            DevText_Show(gobj, db_804D6B9C[i].text);
            DevText_HideCursor(db_804D6B9C[i].text);
            DevText_SetBGColor(db_804D6B9C[i].text,
                               &db_803EAE08[db_804D6B98.x1.b0].bg);
            DevText_SetTextColor(db_804D6B9C[i].text,
                                 &db_803EAE08[db_804D6B98.x1.b0].fg);
            DevText_SetScale(db_804D6B9C[i].text, 12.0F, 16.0F);
        }
    }
}

void fn_80228E54(int arg0, int arg1, int arg2)
{
    DevText* text;
    s32 temp_r4;
    s32 bonus;
    s32 y_pos;

    y_pos = 0;
    text = db_804D6B9C[arg1].text;
    DevText_Erase(text);
    DevText_SetCursorXY(text, 0, 0);
    if (arg1 == 0) {
        DevText_Printf(text, "1P %7d 2P %7d\n", gm_8016C658(0),
                       gm_8016C658(1));
        DevText_Printf(text, "3P %7d 4P %7d\n", gm_8016C658(2),
                       gm_8016C658(3));
        DevText_Printf(text, "%dP screen %d", arg0 + 1, arg1);
        y_pos = 3;
    }
    DevText_SetCursorXY(text, 0, y_pos);
    for (bonus = arg2; bonus < 0xD7; bonus++) {
        if (pl_80039418(arg0, bonus) != 0) {
            if (y_pos >= 0x1E) {
                temp_r4 = arg1 + 1;
                if (temp_r4 < 2) {
                    fn_80228E54(arg0, temp_r4, bonus);
                    return;
                }
                DevText_Printf(text, "screen over!!");
                return;
            }
            if (gm_8016F1B8(bonus) == 0) {
                DevText_Printf(text, "%s", bonus_names[bonus]);
            } else {
                DevText_Printf(text, "%s : %d", bonus_names[bonus],
                               pl_80039418(arg0, bonus));
            }
            y_pos += 1;
            DevText_SetCursorXY(text, 0, y_pos);
        }
    }
}

void fn_8022900C(int arg0)
{
    int i;

    if (db_804D6B98.x0 == arg0) {
        if (db_804D6B98.x1.b0) {
            db_804D6B98.x0 = 0xFF;
            db_804D6B98.x1.b0 = 0;
            for (i = 0; i < 2; i++) {
                DevText_HideBackground(db_804D6B9C[i].text);
                DevText_HideText(db_804D6B9C[i].text);
            }
        } else {
            db_804D6B98.x1.b0 = 1;
            for (i = 0; i < 2; i++) {
                DevText_SetBGColor(db_804D6B9C[i].text,
                                   &db_803EAE08[db_804D6B98.x1.b0].bg);
                DevText_SetTextColor(db_804D6B9C[i].text,
                                     &db_803EAE08[db_804D6B98.x1.b0].fg);
            }
        }
    } else {
        db_804D6B98.x0 = arg0;
        for (i = 0; i < 2; i++) {
            DevText_ShowBackground(db_804D6B9C[i].text);
            DevText_ShowText(db_804D6B9C[i].text);
            DevText_SetBGColor(db_804D6B9C[i].text,
                               &db_803EAE08[db_804D6B98.x1.b0].bg);
            DevText_SetTextColor(db_804D6B9C[i].text,
                                 &db_803EAE08[db_804D6B98.x1.b0].fg);
        }
    }
}

void fn_802291A0(int arg0)
{
    if ((fn_8022558C(arg0) & HSD_PAD_B) &&
        (fn_802255A4(arg0) & HSD_PAD_DPADLEFT))
    {
        fn_8022900C(arg0);
    }
    if (db_804D6B98.x0 == arg0) {
        if (Player_GetEntity(arg0) != NULL) {
            pl_80039450(arg0);
        }
        fn_80228E54(arg0, 0, 0);
    }
}

void fn_80229220(void)
{
    db_804D6BA0.b0 = 0;
    db_804D6BA0.b1 = 0;
}

void fn_80229240(int arg0)
{
    int peak;

    if (g_debugLevel == 4) {
        if ((fn_8022558C(arg0) & HSD_PAD_B) &&
            (fn_802255A4(arg0) & HSD_PAD_DPADUP))
        {
            if (db_804D6BA0.b0 == 0) {
                HSD_ObjAllocSetNumLimit(&efLib_80458EB0,
                                        HSD_ObjAllocGetPeak(&efLib_80458EB0));
                HSD_ObjAllocEnableNumLimit(&efLib_80458EB0);

                db_804D6BA0.b0 = 1;
            } else {
                HSD_ObjAllocDisableNumLimit(&efLib_80458EB0);

                db_804D6BA0.b0 = 0;
            }
        }
        if ((fn_8022558C(arg0) & HSD_PAD_A) &&
            (fn_802255A4(arg0) & HSD_PAD_DPADUP))
        {
            if (db_804D6BA0.b1 == 0) {
                HSD_ObjAllocSetNumLimit(&hsd_804D0F60,
                                        HSD_ObjAllocGetPeak(&hsd_804D0F60));
                HSD_ObjAllocEnableNumLimit(&hsd_804D0F60);
                HSD_ObjAllocSetNumLimit(&hsd_804D0F90,
                                        HSD_ObjAllocGetPeak(&hsd_804D0F90));
                HSD_ObjAllocEnableNumLimit(&hsd_804D0F90);
                HSD_ObjAllocSetNumLimit(
                    &HSD_PSAppSrt_804D10B0,
                    HSD_ObjAllocGetPeak(&HSD_PSAppSrt_804D10B0));
                HSD_ObjAllocEnableNumLimit(&HSD_PSAppSrt_804D10B0);

                db_804D6BA0.b1 = 1;
            } else {
                HSD_ObjAllocDisableNumLimit(&hsd_804D0F60);
                HSD_ObjAllocDisableNumLimit(&hsd_804D0F90);
                HSD_ObjAllocDisableNumLimit(&HSD_PSAppSrt_804D10B0);

                db_804D6BA0.b1 = 0;
            }
        }
    }
}
