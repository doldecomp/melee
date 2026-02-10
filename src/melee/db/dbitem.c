#include "db.h"

#include "dbitem.static.h"

#include "ef/efsync.h"
#include "ft/ftlib.h"
#include "gm/gm_unsplit.h"
#include "if/textdraw.h"
#include "if/textlib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/types.h"
#include "pl/player.h"

#include <sysdolphin/baselib/gobj.h>

void fn_SetupItemAndPokemonMenu(void)
{
    db_ItemAndPokemonMenu.DisplayStatus = 0;
    db_ItemAndPokemonMenu.CurrentlySelectedItem = 0x22;
    db_ItemAndPokemonMenu.LastSelectedItem =
        db_ItemAndPokemonMenu.CurrentlySelectedItem;
    db_ItemAndPokemonMenu.CurrentlySelectedPokemon = 0;
    db_ItemAndPokemonMenu.LastSelectedPokemon =
        db_ItemAndPokemonMenu.CurrentlySelectedPokemon;
    db_ShowItemCollisionBubbles = 1;
    db_ItemAndPokemonMenu.ShowEnemyStompRange = 0;
    db_ItemAndPokemonMenu.ShowItemPickupRange = 0;
}

void fn_80225A54(int player)
{
    if (g_debugLevel == 4) {
        if (db_ButtonsDown(player) & HSD_PAD_B) {
            if (db_ButtonsPressed(player) & HSD_PAD_DPADRIGHT) {
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

u32 db_ShowEnemyStompRange(void)
{
    return db_ItemAndPokemonMenu.ShowEnemyStompRange;
}

u32 db_ShowItemPickupRange(void)
{
    return db_ItemAndPokemonMenu.ShowItemPickupRange;
}

u32 db_ShowCoinPickupRange(void)
{
    return db_ItemAndPokemonMenu.ShowCoinPickupRange;
}

void fn_EnableShowCoinPickupRange(void)
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
    db_ItemAndPokemonMenu.ShowCoinPickupRange = 1;
}

void fn_DisableShowCoinPickupRange(void)
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
    db_ItemAndPokemonMenu.ShowCoinPickupRange = 0;
}

void fn_EnableShowEnemyStompRange(void)
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
    db_ItemAndPokemonMenu.ShowEnemyStompRange = 1;
}

void fn_DisableShowEnemyStompRange(void)
{
    HSD_GObj* item_gobj;
    Item* it;

    item_gobj = HSD_GObj_Entities->items;
    while (item_gobj != NULL) {
        it = item_gobj->user_data;
        it->xDAA_flag.b3 = 0;
        item_gobj = item_gobj->next;
    }
    db_ItemAndPokemonMenu.ShowEnemyStompRange = 0;
}

void fn_EnableShowItemPickupRange(void)
{
    HSD_GObj* item_gobj;
    Item* it;

    item_gobj = HSD_GObj_Entities->items;
    while (item_gobj != NULL) {
        it = item_gobj->user_data;
        it->xDAA_flag.b4 = 1;
        item_gobj = item_gobj->next;
    }
    db_ItemAndPokemonMenu.ShowItemPickupRange = 1;
}

void fn_DisableShowItemPickupRange(void)
{
    HSD_GObj* item_gobj;
    Item* it;

    item_gobj = HSD_GObj_Entities->items;
    while (item_gobj != NULL) {
        it = item_gobj->user_data;
        it->xDAA_flag.b4 = 0;
        item_gobj = item_gobj->next;
    }
    db_ItemAndPokemonMenu.ShowItemPickupRange = 0;
}

s32 db_GetCurrentlySelectedPokemon(void)
{
    return db_ItemAndPokemonMenu.CurrentlySelectedPokemon;
}

void db_DisableItemSpawns(void)
{
    db_ItemAndPokemonMenu.ItemSpawnsEnabled = 0;
}

void db_EnableItemSpawns(void)
{
    db_ItemAndPokemonMenu.ItemSpawnsEnabled = 1;
}

s32 db_AreItemSpawnsEnabled(void)
{
    return db_ItemAndPokemonMenu.ItemSpawnsEnabled;
}

void db_80225D64(Item_GObj* item, Fighter_GObj* owner)
{
    Item* it = GET_ITEM(item);
    it->xDAA_byte |= db_ShowItemCollisionBubbles;
}

/// TODO avoid auto-inlining into fn_CheckItemAndPokemonMenu
#pragma push
#pragma dont_inline on
void fn_ToggleItemCollisionBubbles(void)
{
    HSD_GObj* item_gobj;
    Item* it;

    db_ShowItemCollisionBubbles += 1;
    if (db_ShowItemCollisionBubbles > 3) {
        db_ShowItemCollisionBubbles = 1;
    }
    item_gobj = HSD_GObj_Entities->items;
    while (item_gobj != NULL) {
        it = item_gobj->user_data;
        it->xDAA_byte &= 0xFC;
        it->xDAA_byte |= db_ShowItemCollisionBubbles;
        item_gobj = item_gobj->next;
    }
}
#pragma pop

void db_80225DD8(Item_GObj* item, Fighter_GObj* owner)
{
    Item* it = GET_ITEM(item);
    if (ftLib_80086960(owner) == 0) {
        it = GET_ITEM(item);
        it->xDAA_byte |= db_ShowItemCollisionBubbles;
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

void fn_80225E6C(Fighter_GObj* owner, Fighter* fp)
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

void db_HandleItemPokemonMenuInput(int player)
{
    if ((db_ButtonsDown(player) & HSD_PAD_L) &&
        (db_ButtonsRepeat(player) & HSD_PAD_DPADUP))
    {
        if (db_ItemAndPokemonMenu.CurrentlySelectedItem < 0x23) {
            db_ItemAndPokemonMenu.CurrentlySelectedItem++;
            if (db_ItemAndPokemonMenu.CurrentlySelectedItem == 0x23) {
                db_ItemAndPokemonMenu.CurrentlySelectedItem = 0x2B;
            }
        } else if (db_ItemAndPokemonMenu.CurrentlySelectedItem < 0x2F) {
            db_ItemAndPokemonMenu.CurrentlySelectedItem++;
            if (db_ItemAndPokemonMenu.CurrentlySelectedItem == 0x2F) {
                db_ItemAndPokemonMenu.CurrentlySelectedItem = 0xD0;
            }
        } else if (db_ItemAndPokemonMenu.CurrentlySelectedItem < 0xE9) {
            db_ItemAndPokemonMenu.CurrentlySelectedItem++;
        }
    }

    if ((db_ButtonsDown(player) & HSD_PAD_L) &&
        (db_ButtonsRepeat(player) & HSD_PAD_DPADDOWN))
    {
        if (db_ItemAndPokemonMenu.CurrentlySelectedItem >= 0xD0) {
            db_ItemAndPokemonMenu.CurrentlySelectedItem--;
            if (db_ItemAndPokemonMenu.CurrentlySelectedItem < 0xD0) {
                db_ItemAndPokemonMenu.CurrentlySelectedItem = 0x2E;
            }
        } else if (db_ItemAndPokemonMenu.CurrentlySelectedItem >= 0x2B) {
            db_ItemAndPokemonMenu.CurrentlySelectedItem--;
            if (db_ItemAndPokemonMenu.CurrentlySelectedItem < 0x2B) {
                db_ItemAndPokemonMenu.CurrentlySelectedItem = 0x22;
            }
        } else if (db_ItemAndPokemonMenu.CurrentlySelectedItem > 0) {
            db_ItemAndPokemonMenu.CurrentlySelectedItem--;
        }
    }
    if ((db_ButtonsDown(player) & HSD_PAD_L) &&
        (db_ButtonsRepeat(player) & HSD_PAD_DPADRIGHT))
    {
        if (db_ItemAndPokemonMenu.CurrentlySelectedPokemon < 0x1E) {
            db_ItemAndPokemonMenu.CurrentlySelectedPokemon++;
        }
    }

    if ((db_ButtonsDown(player) & HSD_PAD_L) &&
        (db_ButtonsRepeat(player) & HSD_PAD_DPADLEFT))
    {
        if (db_ItemAndPokemonMenu.CurrentlySelectedPokemon > 0) {
            db_ItemAndPokemonMenu.CurrentlySelectedPokemon--;
        }
    }
}

void fn_ShowOrCreateItemAndPokemonMenu(int player)
{
    HSD_GObj* temp_r30;

    temp_r30 = DevText_GetGObj();
    if (db_ItemAndPokemonMenu.DisplayStatus == 2) {
        DevText_ShowBackground(db_ItemAndPokemonMenuText);
        DevText_ShowText(db_ItemAndPokemonMenuText);
    } else {
        db_ItemAndPokemonMenuText =
            DevText_Create(8, 20, 20, 40, 1, db_ItemAndPokemonMenuText_buf);
        if (db_ItemAndPokemonMenuText != NULL) {
            GXColor bg = { 0x80, 0x40, 0xFF, 0xFF };
            GXColor fg = { 0x00, 0x00, 0x00, 0xFF };
            DevText_Show(temp_r30, db_ItemAndPokemonMenuText);
            DevText_HideCursor(db_ItemAndPokemonMenuText);
            DevText_SetBGColor(db_ItemAndPokemonMenuText, bg);
            DevText_SetTextColor(db_ItemAndPokemonMenuText, fg);
            DevText_SetScale(db_ItemAndPokemonMenuText, 12.0F, 16.0F);
        }
    }
    db_ItemAndPokemonMenu.DisplayStatus = 1;
}

void fn_UpdateItemAndPokemonMenu(int player)
{
    char* item;
    db_ItemAndPokemonMenu.LastSelectedItem =
        db_ItemAndPokemonMenu.CurrentlySelectedItem;
    db_ItemAndPokemonMenu.LastSelectedPokemon =
        db_ItemAndPokemonMenu.CurrentlySelectedPokemon;
    db_HandleItemPokemonMenuInput(player);
    if (db_ItemAndPokemonMenu.LastSelectedItem !=
            db_ItemAndPokemonMenu.CurrentlySelectedItem ||
        db_ItemAndPokemonMenu.LastSelectedPokemon !=
            db_ItemAndPokemonMenu.CurrentlySelectedPokemon)
    {
        db_ItemAndPokemonMenu.Player = player;
        db_ItemAndPokemonMenu.DisplayFadeTimer = 0x78;
        if (db_ItemAndPokemonMenu.DisplayStatus != 1) {
            fn_ShowOrCreateItemAndPokemonMenu(player);
        }
        DevText_Erase(db_ItemAndPokemonMenuText);
        DevText_SetCursorXY(db_ItemAndPokemonMenuText, 0, 0);
        if (db_ItemAndPokemonMenu.CurrentlySelectedItem < 0x23) {
            item = db_ItemNames[db_ItemAndPokemonMenu.CurrentlySelectedItem];
        } else if (db_ItemAndPokemonMenu.CurrentlySelectedItem <
                   It_Kind_Octarock_Stone)
        {
            item =
                db_BarrelEnemies[db_ItemAndPokemonMenu.CurrentlySelectedItem -
                                 It_Kind_Kuriboh];
        } else if (db_ItemAndPokemonMenu.CurrentlySelectedItem <
                   It_Kind_Arwing_Laser)
        {
            item = db_AdventureEnemies[db_ItemAndPokemonMenu
                                           .CurrentlySelectedItem -
                                       It_Kind_Old_Kuri];
        } else {
            while (1) {
            }
        }
        DevText_Printf(
            db_ItemAndPokemonMenuText, "Item-> %s  Pokemon-> %s", item,
            db_PokemonNames[db_ItemAndPokemonMenu.CurrentlySelectedPokemon]);
    }
}

void db_CheckAndSpawnItem(int player)
{
    int mask = HSD_PAD_DPADLEFT | HSD_PAD_DPADRIGHT | HSD_PAD_DPADUP |
               HSD_PAD_Z | HSD_PAD_R | HSD_PAD_L | HSD_PAD_A | HSD_PAD_B |
               HSD_PAD_X | HSD_PAD_Y | HSD_PAD_START;
    SpawnItem spawnItem;
    if ((db_ButtonsDown(player) & mask) != 0) {
        return;
    }
    if ((db_ButtonsPressed(player) & HSD_PAD_DPADDOWN) == 0) {
        return;
    }
    spawnItem.kind = db_ItemAndPokemonMenu.CurrentlySelectedItem;
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
    if (spawnItem.kind < 0x23 && Item_804A0C64.x0 >= (u32) it_804D6D28->x0) {
        OSReport("Item Max Over.\n");
        return;
    }
    if (spawnItem.kind < 0x2F && Item_804A0C64.x2C >= (u32) it_804D6D28->x14) {
        OSReport("couldn't get Item struct.(CZako)\n");
        return;
    }
    if (spawnItem.kind < 0xD0 || spawnItem.kind >= 0xEA ||
        it_804A0F60[spawnItem.kind - 0xD0] != 0)
    {
        if (spawnItem.kind != 0x22 || it_8026C704() == 0) {
            {
                HSD_GObj* gobj = Item_80268B18(&spawnItem);
                if (gobj != NULL) {
                    GET_ITEM(gobj)->xDAA_flag.u8 |=
                        db_ShowItemCollisionBubbles;
                    efSync_Spawn(0x420, gobj, &spawnItem.prev_pos);
                }
            }
        }
    }
}

void fn_CheckItemAndPokemonMenu(int player)
{
    if (db_ItemAndPokemonMenu.DisplayStatus == 1 &&
        db_ItemAndPokemonMenu.Player == player)
    {
        if (db_ItemAndPokemonMenu.DisplayFadeTimer == 0) {
            db_ItemAndPokemonMenu.DisplayStatus = 2;
            DevText_HideBackground(db_ItemAndPokemonMenuText);
            DevText_HideText(db_ItemAndPokemonMenuText);
        } else {
            db_ItemAndPokemonMenu.DisplayFadeTimer -= 1;
        }
    }
    fn_UpdateItemAndPokemonMenu(player);
    if (gm_801A45E8(1) == 0 && gm_801A45E8(0) == 0) {
        db_CheckAndSpawnItem(player);
    }
    if (db_ButtonsDown(player) & HSD_PAD_R &&
        db_ButtonsPressed(player) & HSD_PAD_DPADUP)
    {
        fn_ToggleItemCollisionBubbles();
    }
    fn_80225A54(player);
}
