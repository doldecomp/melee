#include <melee/it/forward.h>

#include "db.h"
#include <melee/ef/efsync.h>
#include <melee/ft/ftlib.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/if/textdraw.h>
#include <melee/if/textlib.h>
#include <melee/if/types.h>
#include <melee/it/inlines.h>
#include <melee/it/it_26B1.h>
#include <melee/it/it_3F14.h>
#include <melee/it/item.h>
#include <melee/it/itspawn.h>
#include <melee/it/types.h>
#include <melee/pl/player.h>
#include <sysdolphin/baselib/gobj.h>

/* 49FA50 */ static char db_ItemAndPokemonMenuText_buf[0x50];

/* 4D6B38 */ static DevText* db_ItemAndPokemonMenuText;
/* 4D6B3C */ static int db_ShowItemCollisionBubbles;

static struct {
    unsigned int DisplayStatus; // 0=uninitialized, 1=visible, 2=hidden
    unsigned int DisplayFadeTimer;
    int ItemSpawnsEnabled;
    int Player;
    int CurrentlySelectedItem;
    int CurrentlySelectedPokemon;
    ItemKind LastSelectedItem;
    int LastSelectedPokemon;
    u32 ShowEnemyStompRange : 1;
    u32 ShowItemPickupRange : 1;
    u32 ShowCoinPickupRange : 1;
} db_ItemAndPokemonMenu;

/* 3EA94C */ static char* db_ItemNames[] = {
    // clang-format off
    "Capsule ",
    "Box     ",
    "Taru    ",
    "Egg     ",
    "Kusudama",
    "TaruCann",
    "BombHei ",
    "Dosei   ",
    "Heart   ",
    "Tomato  ",
    "Star    ",
    "Bat     ",
    "Sword   ",
    "Parasol ",
    "G Shell ",
    "R Shell ",
    "L Gun   ",
    "Freeze  ",
    "Foods   ",
    "MSBomb  ",
    "Flipper ",
    "S Scope ",
    "StarRod ",
    "LipStick",
    "Harisen ",
    "F Flower",
    "Kinoko  ",
    "DKinoko ",
    "Hammer  ",
    "WStar   ",
    "ScBall  ",
    "RabbitC ",
    "MetalB  ",
    "Spycloak",
    "M Ball  ",
    // clang-format on
};

/* 3EAA50 */ static char* db_PokemonNames[] = {
    "Random",      "Tosakinto", "Chicorita", "Kabigon",    "Kamex",
    "Matadogas",   "Lizardon",  "Fire",      "Thunder",    "Freezer",
    "Sonans",      "Hassam",    "Unknown",   "Entei",      "Raikou",
    "Suikun",      "Kireihana", "Marumine",  "Lugia",      "Houou",
    "Metamon",     "Pippi",     "Togepy",    "Mew",        "Cerebi",
    "Hitodeman",   "Lucky",     "Porygon2",  "Hinoarashi", "Maril",
    "Fushigibana",
};

/* 3EAAFC */ static char* db_BarrelEnemies[] = { "Kuriboh ", "Leadead ",
                                                 "Octarock", "Ottosei " };

/* 3EABA8 */ static char* db_AdventureEnemies[26] = {
    // clang-format off
    "old-Kuri",
    "Mato    ",
    "Heiho   ",
    "Nokonoko",
    "Patapata",
    "likelike",
    "old-lead",
    "old-octa",
    "old-otto",
    "whitebea",
    "klap    ",
    "zgshell ",
    "zrshell ",
    // clang-format on
};

static char unused_db_string_803EAC10[] =
    "Item=%d Foods=%d Yaku=%d Sp_Item=%d Pokemon=%d PokeShot=%d CZako=%d "
    "CZakoShot=%d Zako=%d ZakoShot=%d Shot=%d Etc=%d\n";

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
    if (DbLevel == DbLKind_Develop) {
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

    item_gobj = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_ITEM];
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

    item_gobj = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_ITEM];
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

    item_gobj = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_ITEM];
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

    item_gobj = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_ITEM];
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

    item_gobj = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_ITEM];
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

    item_gobj = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_ITEM];
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

void fn_ToggleItemCollisionBubbles(void)
{
    HSD_GObj* item_gobj;
    Item* it;

    db_ShowItemCollisionBubbles += 1;
    if (db_ShowItemCollisionBubbles > 3) {
        db_ShowItemCollisionBubbles = 1;
    }
    item_gobj = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_ITEM];
    while (item_gobj != NULL) {
        it = item_gobj->user_data;
        it->xDAA_byte &= 0xFC;
        it->xDAA_byte |= db_ShowItemCollisionBubbles;
        item_gobj = item_gobj->next;
    }
}

void db_80225DD8(Item_GObj* item, Fighter_GObj* owner)
{
    Item* it = GET_ITEM(item);
    if (ftLib_IsFighter(owner) == 0) {
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

    item_gobj = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_ITEM];
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
                db_ItemAndPokemonMenu.CurrentlySelectedItem = It_Kind_Old_Kuri;
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
    if (Item_80266F3C() == 0 && spawnItem.kind < It_Common_End) {
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
    if (spawnItem.kind < It_Common_End &&
        Item_804A0C64.x0 >= (u32) it_804D6D28->x0)
    {
        OSReport("Item Max Over.\n");
        return;
    }
    if (spawnItem.kind < It_Kind_Octarock_Stone &&
        Item_804A0C64.x2C >= (u32) it_804D6D28->x14)
    {
        OSReport("couldn't get Item struct.(CZako)\n");
        return;
    }
    if (spawnItem.kind < It_Kind_Old_Kuri ||
        spawnItem.kind >= It_Kind_Arwing_Laser ||
        it_804A0F60[spawnItem.kind - It_Kind_Old_Kuri] != 0)
    {
        if (spawnItem.kind != It_Kind_M_Ball || it_8026C704() == 0) {
            {
                HSD_GObj* gobj = Item_80268B18(&spawnItem);
                if (gobj != NULL) {
                    GET_ITEM(gobj)->xDAA_flag.byte |=
                        db_ShowItemCollisionBubbles;
                    efSync_Spawn(0x420, gobj, &spawnItem.prev_pos);
                }
            }
        }
    }
}

static inline void checkToggleCollisionBubbles(int player)
{
    if (db_ButtonsDown(player) & HSD_PAD_R &&
        db_ButtonsPressed(player) & HSD_PAD_DPADUP)
    {
        fn_ToggleItemCollisionBubbles();
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
    if (gm_GetDbPauseFlag(1) == 0 && gm_GetDbPauseFlag(0) == 0) {
        db_CheckAndSpawnItem(player);
    }
    checkToggleCollisionBubbles(player);
    fn_80225A54(player);
}
