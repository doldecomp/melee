#include "db_2253.static.h"

// #include "cm/camera.static.h"
#include "cm/camera.h"
#include "ef/eflib.h"
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
#include "lb/lbaudio_ax.h"
#include "lb/lbcardgame.h"
#include "lb/lbshadow.h"
#include "pl/player.h"
#include "pl/plbonus.h"
#include "un/un_2FC9.h"

#include <common_structs.h>
#include <dolphin/base/PPCArch.h>
#include <dolphin/card.h>
#include <dolphin/db.h>
#include <dolphin/mtx.h>
#include <dolphin/vi.h>
#include <baselib/controller.h>
#include <baselib/memory.h>
#include <baselib/particle.h>
#include <baselib/psappsrt.h>
#include <MSL/math.h>
#include <MSL/printf.h>
#include <MSL/string.h>
#include <MSL/trigf.h>

static inline void DevText_SetBGColor2(DevText* text, GXColor color)
{
    DevText_SetBGColor(text, &color);
}

static inline void DevText_SetTextColor2(DevText* text, GXColor color)
{
    DevText_SetTextColor(text, &color);
}

void db_GetGameLaunchButtonState(void)
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

    db_gameLaunchButtonState = (pad != 4) ? status[pad].button : 0;

    while (CARDProbeEx(0, &memSize, &sectorSize) == -1) {
        VIWaitForRetrace();
    }
}

void db_Setup(void)
{
    struct {
        char** bonus_names;
        char** motionstate_names;
        char** submotion_names;
    }* commonData;
    int stack[2];

    if (g_debugLevel >= 3) {
        db_ButtonStates[0].repeat = 0;
        db_ButtonStates[0].released = 0;
        db_ButtonStates[0].pressed = 0;
        db_ButtonStates[0].current = 0;

        db_ButtonStates[1].repeat = 0;
        db_ButtonStates[1].released = 0;
        db_ButtonStates[1].pressed = 0;
        db_ButtonStates[1].current = 0;

        db_ButtonStates[2].repeat = 0;
        db_ButtonStates[2].released = 0;
        db_ButtonStates[2].pressed = 0;
        db_ButtonStates[2].current = 0;

        db_ButtonStates[3].repeat = 0;
        db_ButtonStates[3].released = 0;
        db_ButtonStates[3].pressed = 0;
        db_ButtonStates[3].current = 0;

        lbArchive_LoadSymbols("DbCo.dat", (void**) &commonData,
                              "dbLoadCommonData", 0);

        db_bonus_names = commonData->bonus_names;
        db_motionstate_names = commonData->motionstate_names;
        db_submotion_names = commonData->submotion_names;

        fn_SetupCpuHandicapInfo();
        fn_SetupAnimationInfo();
        fn_SetupItemAndPokemonMenu();
        fn_SetupSoundInfo();
        fn_SetupMiscStageVisuals();
        fn_SetupCameraInfo();
        fn_SetupBonusInfo();
        fn_SetupObjAllocLimiter();
        fn_Setup5xSpeed();
    }
}

HSD_Pad db_ButtonsDown(int player)
{
    return db_ButtonStates[player].current;
}

HSD_Pad db_ButtonsPressed(int player)
{
    return db_ButtonStates[player].pressed;
}

HSD_Pad db_ButtonsRepeat(int player)
{
    return db_ButtonStates[player].repeat;
}

void db_PrintEntityCounts(void)
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

void db_PrintThreadInfo(void)
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

void db_RunEveryFrame(void)
{
    int stack[4];
    int i;
    int num_players;
    if (g_debugLevel < 3) {
        return;
    }
    if (ftLib_IsMasterHandPresent() || ftLib_IsCrazyHandPresent()) {
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
        db_ButtonStates[i].prev = db_ButtonStates[i].current;
        db_ButtonStates[i].current = button;
        db_ButtonStates[i].pressed =
            db_ButtonStates[i].current &
            (db_ButtonStates[i].prev ^ db_ButtonStates[i].current);
        db_ButtonStates[i].released =
            db_ButtonStates[i].prev &
            (db_ButtonStates[i].prev ^ db_ButtonStates[i].current);
        db_ButtonStates[i].repeat = repeat;
    }
    for (i = 0; i < 4; i++) {
        fn_CheckMiscVisualEffects(i);
    }
    for (i = 0; i < 4; i++) {
        fn_CheckCameraInfo(i, db_ButtonStates[i].current,
                           db_ButtonStates[i].pressed,
                           HSD_PadMasterStatus[i & 0xFF].nml_subStickX,
                           HSD_PadMasterStatus[i & 0xFF].nml_subStickY);
    }
    for (i = 0; i < 4; i++) {
        fn_CheckSoundInfo(i);
    }
    for (i = 0; i < 4; i++) {
        fn_UpdateObjAllocLimiter(i);
    }
    for (i = 0; i < 4; i++) {
        fn_CheckItemAndPokemonMenu(i);
    }
    for (i = 0; i < 4; i++) {
        fn_CheckCpuHandicapInfo(i);
    }
    fn_UpdateCpuHandicapInfo();
    for (i = 0; i < 4; i++) {
        fn_CheckAnimationInfo(i);
    }
    fn_UpdateAnimationInfo();
    for (i = 0; i < 4; i++) {
        fn_CheckMiscStageEffects(i);
    }
    for (i = 0; i < 4; i++) {
        fn_CheckBonusInfo(i);
    }
    for (i = 0; i < 4; i++) {
        fn_Check5xSpeed(i);
    }
}

static void fn_SetupItemAndPokemonMenu(void)
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

static void fn_80225A54(int player)
{
    if (g_debugLevel == 4) {
        if (db_ButtonsDown(player) & HSD_PAD_B) {
            if (db_ButtonsPressed(player) & HSD_PAD_DPADLEFT) {
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

static void fn_EnableShowCoinPickupRange(void)
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

static void fn_DisableShowCoinPickupRange(void)
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

static void fn_EnableShowEnemyStompRange(void)
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

static void fn_DisableShowEnemyStompRange(void)
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

static void fn_EnableShowItemPickupRange(void)
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

static void fn_DisableShowItemPickupRange(void)
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

static void fn_ToggleItemCollisionBubbles(void)
{
    HSD_GObj* item_gobj;
    Item* it;

    db_ShowItemCollisionBubbles += 1;
    if (db_ShowItemCollisionBubbles > 3) {
        db_ShowItemCollisionBubbles = 1;
    }
    item_gobj = HSD_GObj_Entities->items;
    while (item_gobj != NULL) {
        it = GET_ITEM(item_gobj);
        it->xDAA_byte &= 0xFC;
        it->xDAA_byte |= db_ShowItemCollisionBubbles;
        item_gobj = item_gobj->next;
    }
}

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

static void fn_80225E6C(Fighter_GObj* owner)
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

static void fn_ShowOrCreateItemAndPokemonMenu(int player)
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
            GXColor bg = { 0x00, 0x00, 0x00, 0xFF };
            GXColor fg = { 0x00, 0x00, 0x00, 0x00 };
            DevText_Show(temp_r30, db_ItemAndPokemonMenuText);
            DevText_HideCursor(db_ItemAndPokemonMenuText);
            DevText_SetBGColor2(db_ItemAndPokemonMenuText, bg);
            DevText_SetTextColor2(db_ItemAndPokemonMenuText, fg);
            DevText_SetScale(db_ItemAndPokemonMenuText, 12.0F, 16.0F);
        }
    }
    db_ItemAndPokemonMenu.DisplayStatus = 1;
}

static void fn_UpdateItemAndPokemonMenu(int player)
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
        } else if (db_ItemAndPokemonMenu.CurrentlySelectedItem < 0x2F) {
            item = db_AdventureEnemies[db_ItemAndPokemonMenu
                                           .CurrentlySelectedItem];
        } else if (db_ItemAndPokemonMenu.CurrentlySelectedItem < 0xEA) {
            item =
                db_BarrelEnemies[db_ItemAndPokemonMenu.CurrentlySelectedItem];
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
                    GET_ITEM(gobj)->xDAA_flag.u8 |=
                        db_ShowItemCollisionBubbles;
                    efSync_Spawn(0x420, gobj, &spawnItem.prev_pos);
                }
            }
        }
    }
}

static void fn_CheckItemAndPokemonMenu(int player)
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

static void fn_SetupCpuHandicapInfo(void)
{
    HSD_GObj* gobj = DevText_GetGObj();
    db_ShowCpuHandicapInfo.b0 = 0;
    db_CpuHandicapInfo.text =
        DevText_Create(6, 20, 20, 60, 7, db_CpuHandicapInfo.buf);
    if (db_CpuHandicapInfo.text != NULL) {
        GXColor bg = { 0xFF, 0xFF, 0xFF, 0xFF };
        GXColor fg = { 0x00, 0x00, 0x00, 0x00 };
        DevText_Show(gobj, db_CpuHandicapInfo.text);
        DevText_HideCursor(db_CpuHandicapInfo.text);
        DevText_SetBGColor2(db_CpuHandicapInfo.text, bg);
        DevText_SetTextColor2(db_CpuHandicapInfo.text, fg);
        DevText_SetScale(db_CpuHandicapInfo.text, 9.0F, 12.0F);
    }
}

static void fn_UpdateCpuHandicapInfo(void)
{
    int stack[2];
    DevText* text;
    StaticPlayer* player;
    s32 slot;

    if (db_ShowCpuHandicapInfo.b0) {
        text = db_CpuHandicapInfo.text;
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

static void fn_CheckCpuHandicapInfo(int player)
{
    if ((db_ButtonsDown(player) & HSD_PAD_B) &&
        (db_ButtonsPressed(player) & HSD_PAD_DPADDOWN))
    {
        db_ShowCpuHandicapInfo.b0 ^= 1;
        if (db_ShowCpuHandicapInfo.b0 == 0) {
            DevText_HideBackground(db_CpuHandicapInfo.text);
            DevText_HideText(db_CpuHandicapInfo.text);
            return;
        }
        DevText_ShowBackground(db_CpuHandicapInfo.text);
        DevText_ShowText(db_CpuHandicapInfo.text);
    }
}

static void fn_SetupAnimationInfo(void)
{
    HSD_GObj* temp_r3;

    temp_r3 = DevText_GetGObj();
    db_804D6B48.ShowFighterCollisionBubbles = 1;
    db_804D6B48.ShowAnimationInfo = 0;
    db_804D6B48.MiscFighterVisualsStatus = 0;
    db_AnimationInfo.text =
        DevText_Create(7, 20, 20, 60, 12, db_AnimationInfo.buf);
    if (db_AnimationInfo.text) {
        GXColor bg = { 0xFF, 0xFF, 0xFF, 0xFF };
        GXColor fg = { 0x00, 0x00, 0x00, 0x00 };
        DevText_Show(temp_r3, db_AnimationInfo.text);
        DevText_HideCursor(db_AnimationInfo.text);
        DevText_SetBGColor2(db_AnimationInfo.text, bg);
        DevText_SetTextColor2(db_AnimationInfo.text, fg);
        DevText_SetScale(db_AnimationInfo.text, 9.0F, 12.0F);
    }
}

static void fn_ToggleMiscFighterVisuals(void)
{
    HSD_GObj* fighter;
    if (db_804D6B48.MiscFighterVisualsStatus != 0) {
        db_804D6B48.MiscFighterVisualsStatus =
            (db_804D6B48.MiscFighterVisualsStatus << 1) & 0x3F;
    } else {
        db_804D6B48.MiscFighterVisualsStatus = 1;
    }
    for (fighter = HSD_GObj_Entities->fighters; fighter != NULL;
         fighter = fighter->next)
    {
        Fighter* ft = GET_FIGHTER(fighter);
        // ft->x21FC_flag.grouped_bits.b0_to_5 =
        // db_804D6B48.MiscFighterVisualsStatus;
        ft->x21FC_flag.u8 = (ft->x21FC_flag.u8 & 3) |
                            ((db_804D6B48.MiscFighterVisualsStatus << 2) & ~3);
    }
    if ((db_804D6B48.MiscFighterVisualsStatus & 0x02) != 0) {
        fn_EnableShowEnemyStompRange();
    } else {
        fn_DisableShowEnemyStompRange();
    }
    if ((db_804D6B48.MiscFighterVisualsStatus & 0x08) != 0) {
        fn_EnableShowItemPickupRange();
    } else {
        fn_DisableShowItemPickupRange();
    }
    if ((db_804D6B48.MiscFighterVisualsStatus & 0x20) != 0) {
        fn_EnableShowCoinPickupRange();
    } else {
        fn_DisableShowCoinPickupRange();
    }
}

static u8 fn_8022697C(Fighter_GObj* owner)
{
    if (ftLib_80086960(owner) != 0) {
        Fighter* ft = GET_FIGHTER(owner);
        return ft->x21FC_flag.u8;
    } else {
        return 0;
    }
}

static void fn_UpdateAnimationInfo(void)
{
    Fighter_GObj* gobj;
    Fighter* ft;
    DevText* text;
    s32 print_newline;
    int stack[4];

    if (db_804D6B48.ShowAnimationInfo) {
        text = db_AnimationInfo.text;
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
                               db_motionstate_names[ft->motion_id]);
            } else {
                DevText_Printf(text, "%d %d", ft->player_id, ft->motion_id);
            }
            DevText_SetCursorX(text, 23);
            if (ft->anim_id != -1) {
                if (ft->anim_id < 0x127) {
                    DevText_Printf(text, "%s",
                                   db_submotion_names[ft->anim_id]);
                } else {
                    DevText_Printf(text, "%d", ft->anim_id);
                }
            }
            DevText_SetCursorX(text, 44);
            DevText_Printf(text, "%03.2f", ft->cur_anim_frame);
            if (ft->x221C_u16_y) {
                DevText_SetCursorX(text, 52);
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

static void fn_CheckAnimationInfo(int player)
{
    HSD_GObj* gobj;
    Fighter* ft;
    if (db_ButtonsDown(player) & HSD_PAD_R) {
        if (db_ButtonsPressed(player) & HSD_PAD_DPADUP) {
            db_804D6B48.ShowFighterCollisionBubbles++;
            if (db_804D6B48.ShowFighterCollisionBubbles > 3) {
                db_804D6B48.ShowFighterCollisionBubbles = 1;
            }
            for (gobj = HSD_GObj_Entities->fighters; gobj != NULL;
                 gobj = gobj->next)
            {
                GET_FIGHTER(gobj)->x21FC_flag.u8 =
                    db_804D6B48.ShowFighterCollisionBubbles;
            }
        }
        if ((db_ButtonsPressed(player) & HSD_PAD_DPADRIGHT) &&
            Player_GetPlayerSlotType(player) != 3)
        {
            unsigned int x;
            gobj = Player_GetEntity(player);
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
        if (db_ButtonsPressed(player) & HSD_PAD_DPADLEFT) {
            fn_ToggleMiscFighterVisuals();
        }
    }
    if ((db_ButtonsDown(player) & HSD_PAD_Y) &&
        (db_ButtonsDown(player) & HSD_PAD_DPADDOWN))
    {
        db_804D6B48.ShowAnimationInfo = db_804D6B48.ShowAnimationInfo ^ 1;
        if (!db_804D6B48.ShowAnimationInfo) {
            DevText_HideBackground(db_AnimationInfo.text);
            DevText_HideText(db_AnimationInfo.text);
        } else {
            DevText_ShowBackground(db_AnimationInfo.text);
            DevText_ShowText(db_AnimationInfo.text);
        }
    }
    if (db_ButtonsDown(player) & HSD_PAD_Y) {
        if ((db_ButtonsPressed(player) & HSD_PAD_DPADLEFT) &&
            (Player_GetPlayerSlotType(player) != 3))
        {
            gobj = Player_GetEntity(player);
            if (db_ButtonsDown(player) & HSD_PAD_A) {
                Fighter_PoisonMushroomApply(gobj);
            } else {
                Fighter_SuperMushroomApply(gobj);
            }
        }
        if ((db_ButtonsPressed(player) & HSD_PAD_DPADRIGHT) &&
            (Player_GetPlayerSlotType(player) != 3))
        {
            gobj = Player_GetEntity(player);
            if (db_ButtonsDown(player) & HSD_PAD_A) {
                Fighter_PoisonMushroomEnd(gobj);
            } else {
                Fighter_SuperMushroomEnd(gobj);
            }
        }
    }
}

static void fn_SetupMiscStageVisuals(void)
{
    db_MiscStageVisualsStatus = 0;
}

static void fn_CheckMiscStageEffects(int player)
{
    if ((db_ButtonsDown(player) & HSD_PAD_R) &&
        (db_ButtonsPressed(player) & HSD_PAD_DPADDOWN))
    {
        db_MiscStageVisualsStatus += 1;
        switch (db_MiscStageVisualsStatus) {
        default:
            fn_802270C4(1);
            Camera_80030B0C(0);
            Camera_80030A60(0);
            Camera_80030A8C(0);
            fn_8022713C(0);
            Camera_80030B38(0);
            Camera_80030B64(0);
            Camera_80030B90(0);
            db_MiscStageVisualsStatus = 0;
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
    if ((db_ButtonsDown(player) & HSD_PAD_X) &&
        (db_ButtonsPressed(player) & HSD_PAD_DPADDOWN))
    {
        if (db_MiscVisualEffectsStatus < 2 && db_MiscVisualEffectsStatus >= 0)
        {
            Ground_ApplyStageBackgroundColor();
            Camera_SetStageVisible(1);
        } else {
            Camera_SetStageVisible(0);
        }
    }
}

static void fn_802270C4(int arg0)
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

static void fn_8022713C(int arg0)
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

static void fn_SetupCameraInfo(void)
{
    db_CameraInfoDisplay = NULL;
    db_CameraInfoDisplayTimer = 0;
    db_ShowCameraInfo = 0;
}

static void fn_80227188(void)
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
    if (db_CameraInfoDisplay != NULL) {
        if ((gobj != NULL) && (db_ShowCameraInfo != 0)) {
            if (db_CameraInfoDisplayTimer > 1) {
                cobj = gobj->hsd_obj;
                HSD_CObjGetEyePosition(cobj, &camera);
                HSD_CObjGetInterest(cobj, &interest);
                fov = HSD_CObjGetFov(cobj);
                ang = rad_to_deg *
                      atan2f(interest.y - camera.y, -(interest.z - camera.z));
                DevText_Erase(db_CameraInfoDisplay);
                DevText_SetCursorXY(db_CameraInfoDisplay, 0, 0);
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
                DevText_Printf(db_CameraInfoDisplay, "EYE %d,%d,%d", eye_x,
                               eye_y, eye_z);
                DevText_SetCursorXY(db_CameraInfoDisplay, 0, 1);
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
                DevText_Printf(db_CameraInfoDisplay, "INT %d,%d,%d", int_x,
                               int_y, int_z);
                DevText_SetCursorXY(db_CameraInfoDisplay, 0, 2);
                DevText_Printf(db_CameraInfoDisplay, "FOV %d  ANG %d",
                               (int) fov, (int) ang);
                DevText_ShowBackground(db_CameraInfoDisplay);
                DevText_ShowText(db_CameraInfoDisplay);
            } else if (db_CameraInfoDisplayTimer == 1) {
                DevText_HideBackground(db_CameraInfoDisplay);
                DevText_HideText(db_CameraInfoDisplay);
            } else {
                return;
            }
            db_CameraInfoDisplayTimer--;
        } else {
            DevText_HideBackground(db_CameraInfoDisplay);
            DevText_HideText(db_CameraInfoDisplay);
        }
    }
}

static inline void fn_CheckCameraInfo_inline(void)
{
    GXColor bg = { 0x00, 0x00, 0x00, 0x00 };
    GXColor fg = { 0xFF, 0xFF, 0xFF, 0xFF };
    HSD_GObj* gobj = DevText_GetGObj();
    if (db_CameraInfoDisplay == NULL && gobj != NULL) {
        if ((db_CameraInfoDisplay = DevText_Create(12, 420, 360, 32, 3,
                                                   db_CameraInfoDisplay_buf)))
        {
            DevText_Show(gobj, db_CameraInfoDisplay);
            DevText_HideCursor(db_CameraInfoDisplay);
            DevText_SetBGColor2(db_CameraInfoDisplay, bg);
            DevText_SetTextColor2(db_CameraInfoDisplay, fg);
            DevText_SetScale(db_CameraInfoDisplay, 12.0F, 16.0F);
            DevText_HideBackground(db_CameraInfoDisplay);
            DevText_HideText(db_CameraInfoDisplay);
        }
    }
}

static void fn_CheckCameraInfo(int player, int buttons_down,
                               int buttons_pressed, f32 cstick_x, f32 cstick_y)
{
    if (gm_8018841C() == 0 && gm_801A4310() != 0xA) {
        if (Camera_80030178() == 0 && Camera_80030154() == 0) {
            if (!(ABS(cstick_x) > 0.6F)) {
                if (ABS(cstick_y) > 0.6F) {
                    fn_CheckCameraInfo_inline();
                }
                Camera_8003006C();
            }
        } else {
            if (buttons_pressed & HSD_PAD_DPADUP) {
                fn_CheckCameraInfo_inline();
                if ((buttons_down &
                     (HSD_PAD_Y | HSD_PAD_X | HSD_PAD_L | HSD_PAD_R)) == 0)
                {
                    if (Camera_80030178() != 0) {
                        Camera_8002FEEC(player);
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
        fn_802277E8(Camera_80030A50(), player);
    } else if (Camera_80030178() != 0) {
        fn_80227904(Camera_80030A50(), player);
    }
    if (Camera_80030178() != 0 && db_MiscStageVisualsStatus - 3 <= 1) {
        if (buttons_pressed & HSD_PAD_B) {
            db_ShowCameraInfo = !db_ShowCameraInfo;
        }
    } else {
        db_ShowCameraInfo = 0;
    }
    fn_80227188();
    if ((db_ButtonsDown(player) & HSD_PAD_X) &&
        (db_ButtonsPressed(player) & HSD_PAD_DPADDOWN))
    {
        switch (db_MiscVisualEffectsStatus) {
        case 2:
            Camera_SetBackgroundColor(0xFF, 0xFF, 0xFF);
            break;
        case 3:
            Camera_SetBackgroundColor(0, 0, 0);
            break;
        }
    }
}

/// #fn_802277E8

// Debug_UpdateCamera
static void fn_80227904(HSD_GObj* camera, u8 port)
{
    f32 cstick_x;
    f32 cstick_y;
    u32 buttons;

    cstick_x = HSD_PadMasterStatus[port].nml_subStickX;
    // if (cstick_x < 0.0f) {
    //     var_f1 = -cstick_x;
    // } else {
    //     var_f1 = cstick_x;
    // }
    // if (var_f1 < 0.2f) {
    //     cstick_x = 0.0f;
    // }
    if (fabs_inline(cstick_x) < 0.2f) {
        cstick_x = 0.0f;
    }

    cstick_y = HSD_PadMasterStatus[port].nml_subStickY;
    // if (cstick_y < 0.0f) {
    //     var_f2_2 = -cstick_y;
    // } else {
    //     var_f2_2 = cstick_y;
    // }
    // if (var_f2_2 < 0.2f) {
    //     cstick_y = 0.0f;
    // }
    if (fabs_inline(cstick_y) < 0.2f) {
        cstick_x = 0.0f;
    }

    buttons = HSD_PadMasterStatus[port].button;

    if (buttons & 1) {
        fn_80227CAC(camera, cstick_y);
    } else if (buttons & 2) {
        fn_80227FE0(camera, -cstick_x, -cstick_y);
    } else {
        fn_80227B64(camera, cstick_x, cstick_y);
    }
    db_CameraInfoDisplayTimer = 0x3C;
}

// Debug_OrbitAroundInterest
void fn_802279E8(HSD_GObj* camera, Vec3* camera_pos, Vec3* camera_interest,
                 f32 cstick_x, f32 cstick_y)
{
    HSD_CObj* cobj;
    Mtx44 mtx;
    Vec3 forward_vec;
    Vec3 axis;
    Vec3 up_vec;
    f32 eye_dist;
    f32 pitch;
    f32 new_pitch;

    cobj = GET_COBJ(camera);
    if ((cstick_x != 0.0f) || (cstick_y != 0.0f)) {
        up_vec = db_803B84D8;
        HSD_CObjGetEyeVector(cobj, &forward_vec);
        pitch = 57.29578f * acosf(PSVECDotProduct(&forward_vec, &up_vec));
        new_pitch = 2.0f * cstick_y;
        if ((pitch + new_pitch) > 179.0f) {
            new_pitch = 179.0f - pitch;
        }
        if ((pitch + new_pitch) < 1.0f) {
            new_pitch = 1.0f - pitch;
        }
        VECCrossProduct(&up_vec, &forward_vec, &axis);
        VECNormalize(&axis, &axis);
        MTXRotAxisRad(mtx, &axis, 0.017453292f * new_pitch);
        MTXMultVec(mtx, &forward_vec, &forward_vec);
        eye_dist = HSD_CObjGetEyeDistance(cobj);
        MTXRotAxisRad(mtx, &up_vec, 0.017453292f * (2.0f * cstick_x));
        MTXMultVec(mtx, &forward_vec, &forward_vec);
        VECScale(&forward_vec, &forward_vec, eye_dist);
        VECSubtract(camera_interest, &forward_vec, camera_pos);
    }
}

// Debug_UpdateFreecamRotation
static void fn_80227B64(HSD_GObj* camera, f32 cstick_x, f32 cstick_y)
{
    if ((cstick_x != 0.0f) || (cstick_y != 0.0f)) {
        fn_802279E8(camera, &cm_80453004.mode8_eye_pos,
                    &cm_80453004.mode8_int_pos, cstick_x, cstick_y);
    }
}

/// #fn_80227BA8

// Debug_UpdateFreecamDolly
static void fn_80227CAC(HSD_GObj* camera, f32 cstick_y)
{
    Vec3 forward;
    HSD_CObj* cobj;

    if ((0.0f != cstick_y) && (0.0f != cstick_y)) {
        cobj = GET_COBJ(camera);
        HSD_CObjGetEyeVector(cobj, &forward);
        VECScale(&forward, &forward,
                 HSD_CObjGetEyeDistance(cobj) * (1.0f - 0.05f * cstick_y));
        VECSubtract(&cm_80453004.mode8_int_pos, &forward,
                    &cm_80453004.mode8_eye_pos);
    }
}

/// #fn_80227D38

/// #fn_80227EB0

// Debug_UpdateFreecamPosition
static void fn_80227FE0(HSD_GObj* camera, f32 cstick_x, f32 cstick_y)
{
    Vec3 up_vec;
    Vec3 left_vec;
    // fake temp variables?
    // probably an inline for getting the scale factor
    Vec3* temp_r3;
    Vec3* temp_r3_2;
    Vec3* temp_r3_3;
    Vec3* temp_r3_4;
    f32 eye_dist;
    f32 scale_factor;
    HSD_CObj* cobj;

    if ((cstick_x != 0.0f) || (cstick_y != 0.0f)) {
        cobj = GET_COBJ(camera);
        eye_dist = HSD_CObjGetEyeDistance(cobj);
        scale_factor =
            0.03f * (2.0f * (eye_dist * tanf(0.017453292f *
                                             HSD_CObjGetFov(cobj) * 0.5f)));
        if (cstick_x != 0.0f) {
            HSD_CObjGetLeftVector(cobj, &left_vec);
            VECScale(&left_vec, &left_vec, scale_factor * cstick_x);
            temp_r3 = &cm_80453004.mode8_int_pos;
            VECAdd(temp_r3, &left_vec, temp_r3);
            temp_r3_2 = &cm_80453004.mode8_eye_pos;
            VECAdd(temp_r3_2, &left_vec, temp_r3_2);
        }
        if (cstick_y != 0.0f) {
            HSD_CObjGetUpVector(cobj, &up_vec);
            VECScale(&up_vec, &up_vec, -scale_factor * cstick_y);
            temp_r3_3 = &cm_80453004.mode8_int_pos;
            VECAdd(&cm_80453004.mode8_int_pos, &up_vec, temp_r3_3);
            temp_r3_4 = &cm_80453004.mode8_eye_pos;
            VECAdd(temp_r3_4, &up_vec, temp_r3_4);
        }
    }
}

/// #fn_80228124

void fn_SetupSoundInfo(void)
{
    GXColor bg = { 0x80, 0x80, 0x80, 0x80 };
    GXColor fg = { 0xFF, 0xFF, 0xFF, 0xFF };
    db_804D6B7C = DevText_GetGObj();
    db_SoundToggles = 0;
    db_ShowSoundInfo = 0;
    db_SoundRelated_6B68 = 0;
    db_SoundRelated_6B6C = 0;
    db_SoundRelated_6B70 = 0;
    db_SoundRelated_6B74 = 0;
    if ((db_SoundInfoText =
             DevText_Create(9, 420, 60, 18, 3, db_SoundInfoText_buf)))
    {
        DevText_Show(db_804D6B7C, db_SoundInfoText);
        DevText_HideCursor(db_SoundInfoText);
        DevText_SetBGColor2(db_SoundInfoText, bg);
        DevText_SetTextColor2(db_SoundInfoText, fg);
        DevText_SetScale(db_SoundInfoText, 12, 16);
        DevText_HideBackground(db_SoundInfoText);
        DevText_HideText(db_SoundInfoText);
    }
}

void fn_UpdateSoundInfo(void)
{
    int x;
    lbAudioAx_80025098(3 < db_ShowSoundInfo ? 1 : 0);
    if (db_SoundInfoText) {
        switch (db_ShowSoundInfo) {
        case 0:
        case 1:
        case 2:
        case 3:
            DevText_HideBackground(db_SoundInfoText);
            DevText_HideText(db_SoundInfoText);
            break;
        case 4:
        case 5:
        case 6:
        case 7:
            x = lbAudioAx_80028B2C();
            if (db_SoundRelated_6B68 < x) {
                db_SoundRelated_6B68 = x;
                db_SoundRelated_6B6C = 0xF0;
            }
            db_SoundRelated_6B6C--;
            if (db_SoundRelated_6B6C <= 0) {
                db_SoundRelated_6B68 = x;
                db_SoundRelated_6B6C = 0;
            }
            x = lbAudioAx_80028B4C();
            if (db_SoundRelated_6B70 < x) {
                db_SoundRelated_6B70 = x;
                db_SoundRelated_6B74 = 0xF0;
            }
            db_SoundRelated_6B74--;
            if (db_SoundRelated_6B74 <= 0) {
                db_SoundRelated_6B70 = x;
                db_SoundRelated_6B74 = 0;
            }
            DevText_Erase(db_SoundInfoText);
            DevText_SetCursorXY(db_SoundInfoText, 1, 0);
            switch (db_SoundToggleOrder[db_SoundToggles] & 3) {
            case 0:
                DevText_Printf(db_SoundInfoText, "FGM:ON   BGM:OFF");
                break;
            case 1:
                DevText_Printf(db_SoundInfoText, "FGM:OFF  BGM:OFF");
                break;
            case 2:
                DevText_Printf(db_SoundInfoText, "FGM:OFF  BGM:ON ");
                break;
            case 3:
                DevText_Printf(db_SoundInfoText, "FGM:ON   BGM:ON ");
                break;
            }
            DevText_SetCursorXY(db_SoundInfoText, 1, 1);
            DevText_Printf(db_SoundInfoText, "PVoice  %3d  %3d\n", x,
                           db_SoundRelated_6B68);
            DevText_SetCursorXY(db_SoundInfoText, 1, 2);
            DevText_Printf(db_SoundInfoText, "VVoice  %3d  %3d\n", x,
                           db_SoundRelated_6B70);
            DevText_ShowBackground(db_SoundInfoText);
            DevText_ShowText(db_SoundInfoText);
            break;
        }
    } else {
        db_SoundRelated_6B68 = lbAudioAx_80028B2C();
        db_SoundRelated_6B6C = 0;
        db_SoundRelated_6B70 = lbAudioAx_80028B4C();
        db_SoundRelated_6B74 = 0;
    }
}

void fn_CheckSoundInfo(int player)
{
    int orig = db_SoundToggles;
    if (player == 0) {
        if (db_ButtonsPressed(player) & HSD_PAD_X) {
            if (db_ButtonsDown(player) & HSD_PAD_DPADLEFT) {
                db_SoundToggles = (db_SoundToggles + 1) % 4;
                db_ShowSoundInfo = (db_ShowSoundInfo + 1) % 8;
            }
        } else if ((db_ButtonsPressed(player) & HSD_PAD_DPADLEFT)) {
            if (db_ButtonsDown(player) & HSD_PAD_X) {
                db_SoundToggles = (db_SoundToggles + 1) % 4;
                db_ShowSoundInfo = (db_ShowSoundInfo + 1) % 8;
            }
        }
        if (db_SoundToggles != orig) {
            int temp = db_SoundToggleOrder[db_SoundToggles];
            lbAudioAx_80025064(temp & 1, temp & 2);
        }
    }
    fn_UpdateSoundInfo();
}

static void fn_CheckMiscVisualEffects(int player)
{
    if ((db_ButtonsDown(player) & HSD_PAD_X) &&
        (db_ButtonsPressed(player) & HSD_PAD_DPADDOWN))
    {
        db_MiscVisualEffectsStatus++;
        if (3 < db_MiscVisualEffectsStatus) {
            db_MiscVisualEffectsStatus = 0;
        }
        if (db_MiscVisualEffectsStatus == 0) {
            ifAll_ShowHUD();
        } else if (!ifAll_IsHUDHidden()) {
            ifAll_HideHUD();
        }
    }
}

static void fn_Setup5xSpeed(void)
{
    db_5xSpeedStatus.b0 = false;
}

static void fn_Check5xSpeed(int player)
{
    if ((db_ButtonsDown(player) & HSD_PAD_A) &&
        (db_ButtonsPressed(player) & HSD_PAD_DPADRIGHT))
    {
        fn_Toggle5xSpeed();
    }
}

static void fn_Toggle5xSpeed(void)
{
    db_5xSpeedStatus.b0 ^= 1;
    if (db_5xSpeedStatus.b0) {
        gm_SetGameSpeed(5.0f);
    } else {
        gm_ResetGameSpeed();
    }
}

void db_InitScreenshot(void)
{
    db_ScreenshotNumber = 0;
    db_ScreenshotPending = 0;
}

void db_CheckScreenshot(void)
{
    int i;

    for (i = 0; i < 4; i++) {
        if ((HSD_PadMasterStatus[i].button & HSD_PAD_Y) &&
            (HSD_PadMasterStatus[i].trigger & HSD_PAD_DPADUP))
        {
            db_ScreenshotPending = 1;
        }
    }
}

void db_TakeScreenshotIfPending(void)
{
    char spC[32];
    int temp_r3;
    int temp_r5;
    int temp_ret;
    void* var_r30;

    if (db_ScreenshotPending != 0) {
        HSD_VIWaitXFBFlush();
        temp_ret = HSD_VIGetXFBLastDrawDone();
        temp_r3 = temp_ret;
        if (temp_r3 != -1) {
            var_r30 = HSD_VIData.xfb[temp_r3].buffer;
        } else {
            OSReport("cant find xfb!\n");
            ((0) ? ((void) 0) : __assert("dbscreenshot.c", 61, "0"));
        }
        temp_r5 = db_ScreenshotNumber;
        db_ScreenshotNumber = temp_r5 + 1;
        sprintf(spC, "USB:shot/screenshot%02d.frb", temp_r5);
        fn_802289F8(spC, (int) var_r30,
                    HSD_VIData.current.vi.rmode.fbWidth *
                        HSD_VIData.current.vi.rmode.xfbHeight * 2);
        db_ScreenshotPending = 0;
    }
}

static int fn_802289F8(char* arg0, int arg1, int arg2)
{
    if (strncmp(arg0, "USB:", 4) == 0) {
        return hsd_80393A5C(arg0 + 4, arg1, arg2);
    } else {
        return -1;
    }
}

void db_ClearFPUExceptions(void)
{
    OSContext* ctx;

    PPCMtmsr(PPCMfmsr() | 0x900);
    ctx = OSGetCurrentContext();
    OSSaveFPUContext(ctx);
    ctx->fpscr &= 0xFFFFF;
    OSLoadFPUContext(ctx);
}

static void fn_HSDPanicHandler(OSContext* ctx)
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

static void fn_OSErrorHandler(u16 error, OSContext* ctx, ...)
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

void db_SetupCrashHandler(void)
{
    u16 x;
    if (DBIsDebuggerPresent() == 0) {
        void* mem = OSAllocFromArenaLo(0x2000, 4);
        hsd_80393DA0(mem, 0x2000);
        HSD_SetPanicCallback((PanicCallback) fn_HSDPanicHandler);
        for (x = 0; x < 16; x++) {
            switch (x) {
            case 4:
            case 7:
            case 8:
            case 9:
                break;
            default:
                OSSetErrorHandler(x, fn_OSErrorHandler);
            }
        }
    }
}

static void fn_SetupBonusInfo(void)
{
    fn_80228D18();
    fn_80228D38();
}

static void fn_80228D18(void)
{
    db_804D6B98.x0 = 0xFF;
    db_804D6B98.x1.b0 = 0;
}

static void fn_80228D38(void)
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
            DevText_SetBGColor2(db_804D6B9C[i].text,
                                db_TextColors[db_804D6B98.x1.b0].bg);
            DevText_SetTextColor2(db_804D6B9C[i].text,
                                  db_TextColors[db_804D6B98.x1.b0].fg);
            DevText_SetScale(db_804D6B9C[i].text, 12.0F, 16.0F);
        }
    }
}

static void fn_80228E54(int arg0, int arg1, int arg2)
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
                DevText_Printf(text, "%s", db_bonus_names[bonus]);
            } else {
                DevText_Printf(text, "%s : %d", db_bonus_names[bonus],
                               pl_80039418(arg0, bonus));
            }
            y_pos += 1;
            DevText_SetCursorXY(text, 0, y_pos);
        }
    }
}

static void fn_8022900C(int arg0)
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
                DevText_SetBGColor2(db_804D6B9C[i].text,
                                    db_TextColors[db_804D6B98.x1.b0].bg);
                DevText_SetTextColor2(db_804D6B9C[i].text,
                                      db_TextColors[db_804D6B98.x1.b0].fg);
            }
        }
    } else {
        db_804D6B98.x0 = arg0;
        for (i = 0; i < 2; i++) {
            DevText_ShowBackground(db_804D6B9C[i].text);
            DevText_ShowText(db_804D6B9C[i].text);
            DevText_SetBGColor2(db_804D6B9C[i].text,
                                db_TextColors[db_804D6B98.x1.b0].bg);
            DevText_SetTextColor2(db_804D6B9C[i].text,
                                  db_TextColors[db_804D6B98.x1.b0].fg);
        }
    }
}

static void fn_CheckBonusInfo(int player)
{
    if ((db_ButtonsDown(player) & HSD_PAD_B) &&
        (db_ButtonsPressed(player) & HSD_PAD_DPADLEFT))
    {
        fn_8022900C(player);
    }
    if (db_804D6B98.x0 == player) {
        if (Player_GetEntity(player) != NULL) {
            pl_80039450(player);
        }
        fn_80228E54(player, 0, 0);
    }
}

static void fn_SetupObjAllocLimiter(void)
{
    db_804D6BA0.b0 = 0;
    db_804D6BA0.b1 = 0;
}

static void fn_UpdateObjAllocLimiter(int player)
{
    int peak;

    if (g_debugLevel == 4) {
        if ((db_ButtonsDown(player) & HSD_PAD_B) &&
            (db_ButtonsPressed(player) & HSD_PAD_DPADUP))
        {
            if (db_804D6BA0.b0 == 0) {
                HSD_ObjAllocSetNumLimit(
                    &Effect_AllocData, HSD_ObjAllocGetPeak(&Effect_AllocData));
                HSD_ObjAllocEnableNumLimit(&Effect_AllocData);

                db_804D6BA0.b0 = 1;
            } else {
                HSD_ObjAllocDisableNumLimit(&Effect_AllocData);

                db_804D6BA0.b0 = 0;
            }
        }
        if ((db_ButtonsDown(player) & HSD_PAD_A) &&
            (db_ButtonsPressed(player) & HSD_PAD_DPADUP))
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
