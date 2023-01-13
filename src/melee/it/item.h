#ifndef _item_h_
#define _item_h_

#include <common_structs.h>
#include <dolphin/mtx/mtxtypes.h>
#include <math.h>
#include <melee/ft/fighter.h>
#include <melee/gr/stage.h>
#include <melee/it/itCommonItems.h>
#include <melee/it/itkind.h>
#include <melee/it/itPKFlash.h>
#include <melee/it/itPKThunder.h>
#include <melee/it/itYoyo.h>
#include <melee/it/types.h>
#include <melee/pl/player.h>
#include <Runtime/platform.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjuserdata.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/random.h>

extern HSD_ObjAllocData lbl_804A0C38;
extern HSD_ObjAllocUnk lbl_804A0C64;
extern HSD_ObjAllocUnk2 lbl_804A0CCC;
extern S32Vec3 lbl_804A0E24;

static inline Item* GetItemData(HSD_GObj* item_gobj)
{
    Item* item_data = item_gobj->user_data;
    return item_data;
}

static inline Item* GetItemDirect(HSD_GObj* item_gobj)
{
    return item_gobj->user_data;
}

extern s8 lbl_804D6D00;
extern s32 lbl_804D6D08;
extern s32 lbl_804D6D0C;
extern u32 lbl_804D6D10;
extern u32 lbl_804D6D14;
extern ItemCommonData* lbl_804D6D28;

// FUNCTIONS
bool func_80266F3C(void); // Check if items are enabled
void func_80266F70(void); // Check to load ItCo.dat/usd
void func_80266FA8(void); // ItCo prefunction with 0
void func_8027870C(s32);  // Load ItCo.dat/usd
void func_80266FCC(void); // Init item struct?
void func_80267130(HSD_GObj* item_gobj,
                   SpawnItem* spawnItem); // Initialize item coordinates?
void func_80267454(HSD_GObj* item_gobj);  // Remove Camera Box
void func_802674AC(SpawnItem* spawnItem); // Set Item Hold kind
void func_802675A8(HSD_GObj* item_gobj);
void func_802676F4(HSD_GObj* item_gobj);
bool func_8026784C(enum_t dropItem, int unused);
void func_80267978(HSD_GObj* item_gobj); // Store Item Pointers
void func_80267AA8(HSD_GObj* item_gobj,
                   SpawnItem* spawnItem);      // Initialize item variables
void func_802680CC(HSD_GObj* item_gobj);       // Setup Item JObj
void func_8026814C(HSD_GObj* item_gobj);       // Setup item render objects?
bool func_802682F0(HSD_GObj* item_gobj);       // Initialize item bones
void func_8026849C(HSD_GObj* item_gobj);       // Set item model scale
void func_80268560(HSD_GObj* item_gobj);       // Setup item dynamics
HSD_GObj* func_8026862C(SpawnItem* spawnItem); // Create Item
void func_80268B18(
    SpawnItem* spawnItem); // Item spawn prefunction - spawn airborne
void func_80268B5C(
    SpawnItem* spawnItem); // Item spawn prefunction - spawn grounded
void func_80268B9C(SpawnItem* spawnItem); // Item spawn prefunction - spawn
                                          // grounded and toggle unknown true
void func_80268BE0(HSD_JObj* item_jobj, HSD_AnimJoint* anim_joint,
                   HSD_MatAnimJoint* matanim_joint, ItemState_ParamStruct* arg3,
                   Item* item_data); // Adds AObjs to item model
void func_80268D34(
    HSD_GObj* item_gobj,
    struct ItemStateDesc* itemStateDesc); // Unk Item AObj-related function
void func_80268DD4(HSD_GObj* item_gobj, f32 arg8); // Advance item animation?
void func_80268E40(Item* item_data,
                   struct ItemStateDesc* itemStateDesc); // Copy item script
void func_80268E5C(HSD_GObj* item_gobj, s32 itemStateID,
                   s32 itemStateFlags);  // Item State Change
void lbl_802693E4(HSD_GObj* item_gobj);  // Item Think - Hitlag
void func_802694CC(HSD_GObj* item_gobj); // Advance item animation + script?
void lbl_80269528(HSD_GObj* item_gobj);  // Item Think - Animation
bool func_802696CC(HSD_GObj* item_gobj); // Item Think - Check for Blast Zones
void func_802697D4(HSD_GObj* item_gobj); // Item Think - Physics
void func_80269978(HSD_GObj* item_gobj); // Item Think - Collision
void lbl_80269A9C(HSD_GObj* item_gobj);  // Item Think - Accessory + Camera Box
void lbl_80269B60(
    HSD_GObj* item_gobj); // Item Think - Yellow Bar Collision (cb_JumpedOn)
void lbl_80269BE4(HSD_GObj* item_gobj); // Item Think - Grab
void lbl_80269C5C(HSD_GObj* item_gobj); // Item Think - Hit Collision Logic
void func_80269CA0(Item* item_data, s32 damage); // Set damage taken
void func_80269CC4(HSD_GObj* item_gobj);         // Set damage struct
bool func_80269DC8(HSD_GObj* item_gobj); // Item Think - Shield Collision
bool func_80269F14(HSD_GObj* item_gobj); // Item Think - On Reflect
void func_8026A0A0(HSD_GObj* item_gobj); // Item Think - Exit Hitlag Check
void func_8026A0FC(HSD_GObj* item_gobj); // Item Think - Exit Hitlag Check 2
void func_8026A158(HSD_GObj* item_gobj); // Item Think - Enter Hitlag
void func_8026A1E8(HSD_GObj* item_gobj); // Item Think - Exit Hitlag
void lbl_8026A294(HSD_GObj* item_gobj);  // Item Think - Hit Collision
void lbl_8026A788(HSD_GObj* item_gobj);  // Item Think - Process Dynamic Bones
void func_8026A810(HSD_GObj* item_gobj); // Run Item's OnSpawn Callback
void func_8026A848(HSD_GObj* item_gobj,
                   HSD_GObj* fighter_gobj); // Remove Item from Player
void func_8026A8EC(HSD_GObj* item_gobj);    // Destroy Item
void func_8026AB54(HSD_GObj* item_gobj, HSD_GObj* pickupGFX,
                   u8 pickupSFX);                             // Make Item Held
void func_8026ABD8(HSD_GObj* item_gobj, Vec3* pos, f32 arg2); // Drop Item
void func_8026AC74(HSD_GObj* item_gobj, s32 dropGFX, s32 dropSFX,
                   f32 arg8); // This is actually another Item Drop function
void func_8026AD20(HSD_GObj* item_gobj, s32 dropGFX, s32 dropSFX,
                   f32 arg8);            // Throw Item
void func_8026ADC0(HSD_GObj* item_gobj); // Make Item Airborne
void lbl_8026AE10(void* item_data);      // Clear Item Struct ?
u32 func_8026AE60(void);                 // Increment something
void func_8026AE84(Item* item_data, enum_t sfxID, u8 pan, u8 volume);
void func_8026AF0C(Item* item_data, enum_t sfxID, u8 pan, u8 volume);
void func_8026AFA0(Item* item_data, enum_t sfxID, u8 pan, u8 volume);
void func_8026B034(Item* item_data);     // Stop Item SFX
void func_8026B074(Item* item_data);     // Stop Item SFX 2
void func_8026B0B4(HSD_GObj* item_gobj); // Stop All Item SFX
bool func_8026B1A4(HSD_GObj* item_gobj); // Check if item is grabbable
f32 func_8026B1D4(
    HSD_GObj* item_gobj,
    itHit* itemHitboxUnk); // Apply Item Damage -  may not be itHit* ???
void func_8026B294(HSD_GObj* item_gobj,
                   Vec3* pos);           // Copy Item position vector
bool func_8026B2B4(HSD_GObj* item_gobj); // Check if item is heavy
bool func_8026B2D8(HSD_GObj* item_gobj); // Check if item is heavy again?
s32 itGetKind(HSD_GObj* item_gobj);      // Get Item ID
s32 func_8026B30C(HSD_GObj* item_gobj);  // Return flag from Item Attributes
s32 func_8026B320(HSD_GObj* item_gobj);
f32 func_8026B334(HSD_GObj* item_gobj); // Return item damage multiplier
void func_8026B344(
    HSD_GObj* item_gobj,
    Vec3* pos); // Unknown item position math, related to velocity?
f32 func_8026B378(HSD_GObj* item_gobj); // Return item's X-Axis grab range?
f32 func_8026B384(HSD_GObj* item_gobj); // Return item's Y-Axis grab range?
void func_8026B390(
    HSD_GObj* item_gobj); // Toggle item flag 0x15 in 0xDC8 word ON
void func_8026B3A8(
    HSD_GObj* item_gobj);      // Toggle item flag 0x15 in 0xDC8 word OFF
u32 func_8026B3C0(s32 itemID); // Count item entities of identical kind?
void func_8026B3F8(Article* article,
                   s32 itemID); // Store Item article pointer to table
void func_8026B40C(Article* article,
                   s32 itemID); // Store Stage Item article pointer to table
f32 func_8026B424(s32 damage);  // Item Damage Math
s32 func_8026B47C(HSD_GObj* item_gobj);  // Get heal value of healing items
bool func_8026B4F0(HSD_GObj* item_gobj); // Check if item is a healing item
f32 func_8026B54C(HSD_GObj* item_gobj);  // Get unknown float from 0x0 of item's
                                         // special attributes
f32 func_8026B560(HSD_GObj* item_gobj);  // Identical to 0x8026B54C but likely
                                        // using a different itAttributes struct
f32 func_8026B574(HSD_GObj* item_gobj); // Get unknown float from 0x4 of item's
                                        // special attributes
s32 func_8026B588(void);                // Get unknown integer from itCommonData
bool func_8026B594(HSD_GObj* item_gobj); // Check if item can fire projectiles
HSD_GObj* func_8026B5E4(Vec3* vector, Vec3* vector2,
                        HSD_GObj* item_gobj); // Unknown item camera check?
HSD_GObj* func_8026B634(Vec3* vector, Vec3* vector2,
                        HSD_GObj* item_gobj); // Unknown item camera check 2?
f32 func_8026B684(Vec3* pos); // Get facing direction of fp (?) with argument 0
f32 func_8026B6A8(
    Vec3* pos,
    HSD_GObj* arg); // Get facing direction of fp (?) with variable argument
bool func_8026B6C8(HSD_GObj* item_gobj); // Check if item is a stage item?
void func_8026B718(HSD_GObj* item_gobj,
                   f32 hitlagFrames);    // Set item's hitlag frames
void func_8026B724(HSD_GObj* item_gobj); // Toggle bit 3 of 0xDC8 word ON
void func_8026B73C(HSD_GObj* item_gobj); // Toggle bits in 0xDC8 word
bool func_8026B774(HSD_GObj* item_gobj,
                   u8 arg1);            // Bitwise operations in 0xDC8 word
s32 func_8026B7A4(HSD_GObj* item_gobj); // Get Item State ID
u8 func_8026B7B0(HSD_GObj* item_gobj);  // Get Item Team ID
s32 func_8026B7BC(HSD_GObj* item_gobj); // Get flag 0x14 of 0xDC8 word
s32 func_8026B7CC(HSD_GObj* item_gobj); // Get 0x1C of Item - something to do
                                        // with stale moves?
s32 func_8026B7D8(void);                // Get unknown var from global data
s32 func_8026B7E0(void);                // Get unknown var from global data
s32 func_8026B7E8(HSD_GObj* item_gobj); // Get bit 1 of 0xDC8 word
void func_8026B7F8(HSD_GObj* fighter_gobj); // Remove item from player on death?
bool func_8026B894(HSD_GObj* item_gobj,
                   HSD_GObj* referenced_gobj); // Remove all GObj interaction
                                               // references from item
s32 func_8026B924(
    HSD_GObj* item_gobj); // Return result of unk item check - requires -g
                          // compiler flag / Frank modifications to match
f32 func_8026B960(HSD_GObj* item_gobj); // Return float result of item kind and
                                        // state checks - requires -g compiler
                                        // flag / Frank modifications to match
void func_8026BAE8(HSD_GObj* item_gobj,
                   f32 scale_mul);       // Multiply item's scale
void func_8026BB20(HSD_GObj* item_gobj); // Clear JObj flags on item model
void func_8026BB44(HSD_GObj* item_gobj); // Set JObj flags on item model
void func_8026BB68(HSD_GObj* fighter_gobj,
                   Vec3* pos); // Adjust item's position to fp bone
void func_8026BB88(HSD_GObj* item_gobj,
                   Vec3* pos); // Adjust item's position based on ECB?
void func_8026BBCC(HSD_GObj* item_gobj,
                   Vec3* pos); // Adjust item's ECB position?
void func_8026BC14(
    HSD_GObj* item_gobj); // Check if item owner is a fp + decrement hitlag
s32 func_8026BC68(HSD_GObj* item_gobj);       // Return bit 0 of 0xDD0
HSD_GObj* func_8026BC78(HSD_GObj* item_gobj); // Get item owner
bool func_8026BC84(HSD_GObj* item_gobj);      // Get item attack kind
void func_8026BC90(HSD_GObj* item_gobj,
                   Vec3* pos);           // Unknown item ECB / position update
void func_8026BCF4(HSD_GObj* item_gobj); // Toggle bit 2 of 0xDCD OFF
void func_8026BD0C(HSD_GObj* item_gobj); // Toggle bit 2 of 0xDCD ON
void func_8026BD24(HSD_GObj* item_gobj); // Toggle bit 3 of 0xDD0 ON
void func_8026BD3C(HSD_GObj* item_gobj); // Toggle bit 3 of 0xDCC ON
void func_8026BD54(HSD_GObj* item_gobj); // Toggle bit 3 of 0xDCC OFF
void func_8026BD6C(HSD_GObj* item_gobj); // Toggle bit 3 of 0xDCD ON
void func_8026BD84(HSD_GObj* item_gobj); // Toggle bit 4 of 0xDCD ON
void func_8026BD9C(HSD_GObj* item_gobj); // Toggle 0x1A of 0xDC8 word ON
void func_8026BDB4(HSD_GObj* item_gobj); // Toggle 0x1A of 0xDC8 word OFF
void func_8026BDCC(HSD_GObj* item_gobj); // Toggle several item flags
void func_8026BE28(HSD_GObj* item_gobj); // Toggle several item flags, inverted
void* func_8026BE84(BobOmbRain* bobOmbRain);  // Bob-Omb Rain Switch
CollData* func_8026C100(HSD_GObj* item_gobj); // Get item's CollData pointer
void func_8026C16C(
    HSD_GObj* item_gobj,
    bool isHeadless); // Check if Hammer item's head should break off
void func_8026C1B4(HSD_GObj* item_gobj); // Check if item has a hitbox
u32 func_8026C1D4(void);                 // Get unknown var from r13 pointer
bool func_8026C1E8(HSD_GObj* item_gobj); // Check if item has grabbed a GObj?
void func_8026C220(HSD_GObj* item_gobj,
                   HSD_GObj* fighter_gobj); // Get item owner's port number
HSD_GObj*
func_8026C258(Vec3* vector,
              f32 facingDir); // Find the closest item to the given position?
void func_8026C334(HSD_GObj* item_gobj,
                   Vec3* pos);           // Unknown item position / ECB update
void func_8026C368(HSD_GObj* item_gobj); // Run bomb item explosion callbacks

/// Toggle bit 3 of 0xDC8 ON for all active item GObjs?
void func_8026C3FC(void);

void func_8026C42C(void); // Toggle bits in 0xDC8 for all active item GObjs?
f32 func_8026B424(s32 damage);           /* extern */
u8 func_8026B7B0(HSD_GObj* item_gobj);   // Get Team ID
void func_8026BDCC(HSD_GObj* item_gobj); /* extern */
void func_8026C368(HSD_GObj* item_gobj); /* extern */
s32 func_8026D324(s32);
s32 func_8026D604(HSD_GObj* item_gobj);
void func_8026F9A0();
void func_802701BC(HSD_GObj* item_gobj);
void func_802703E8(HSD_GObj* item_gobj);
void func_802706D0(HSD_GObj* item_gobj);
void func_80270E30(HSD_GObj* item_gobj);
void func_8027137C(HSD_GObj* item_gobj);
void func_8027146C(HSD_GObj* item_gobj);
void func_802714C0(HSD_GObj* item_gobj); /* extern */
void func_80271508(HSD_GObj* item_gobj, s32 arg1);
void func_8027163C(HSD_GObj* item_gobj);
void func_80271A58(HSD_GObj* item_gobj); /* extern */
void func_802721B8(HSD_GObj* item_gobj); /* extern */
void func_80272280(HSD_GObj* item_gobj);
void func_8027163C(HSD_GObj* item_gobj);
void func_80271A58(HSD_GObj* item_gobj); /* extern */
void func_802721B8(HSD_GObj* item_gobj); /* extern */
void func_80272298(HSD_GObj* item_gobj);
void func_802722B0(HSD_GObj* item_gobj);
void func_80272304(HSD_GObj* item_gobj);
void func_80272460(itHit* hitbox, s32 damage, HSD_GObj* item_gobj);
void func_802725D4(HSD_GObj*);
void func_80272784(HSD_GObj* item_gobj);
void func_802728C8(HSD_GObj* item_gobj);
void func_80272A18(HSD_JObj* item_jobj);
void func_80272A3C(HSD_JObj* item_jobj);
bool func_80272D1C(HSD_GObj* item_gobj); // Check if GObj is Item class
s32 func_80272D40(HSD_GObj* item_gobj);  // Check GObj entity class
void func_80272F7C(HSD_JObj*, f32);
void func_802728C8(HSD_GObj* item_gobj);
void func_80273168(HSD_GObj* item_gobj);
void func_802731A4(HSD_GObj*);
void func_802731E0(HSD_GObj*);
void func_8027327C(HSD_GObj* item_gobj, s32 ID1, s32 ID2);
void func_8027346C(HSD_GObj* item_gobj); /* extern */
void func_80273484(HSD_GObj* item_gobj);
void func_80273500(HSD_GObj*, Vec3*);
void func_80273748(HSD_GObj*, s32, s32);
void func_80273B50(HSD_GObj*, Vec3*);
void func_80274198(HSD_GObj*, s32);
void func_802741F4(HSD_GObj*, s32);
void func_8027429C(HSD_GObj*, Vec3*);
void func_802742F4(HSD_GObj*, HSD_GObj*, u8);
void func_80274658(HSD_GObj*, f32);
void func_80274740(HSD_GObj* item_gobj); /* extern */
void func_80274A64(HSD_GObj* item_gobj); /* extern */
bool func_80274C78(HSD_GObj* item_gobj);
void func_80274DAC(HSD_GObj*);
void func_8027737C(HSD_GObj* item_gobj, Vec3* pos); /* extern */
void func_80274EF8(HSD_GObj* item_gobj);            // Toggle flag in 0xDC8 off
void func_80274F10(HSD_GObj* item_gobj);
void func_80275158(HSD_GObj* item_gobj, f32 lifetime); // Set item lifetime
void func_80275390(HSD_GObj*);
void func_802753BC(HSD_GObj*, s16);
void func_802753DC(HSD_GObj*);
void func_80274740(HSD_GObj* item_gobj);            /* extern */
void func_80274A64(HSD_GObj* item_gobj);            /* extern */
void func_8027737C(HSD_GObj* item_gobj, Vec3* pos); /* extern */
void func_80274EF8(HSD_GObj* item_gobj);            // Toggle flag in 0xDC8 off
void func_80275158(HSD_GObj* item_gobj, f32 lifetime); // Set item lifetime
void func_80275390(HSD_GObj*);
void func_80275474(HSD_GObj* item_gobj); // Toggle several flags in 0xDCD off
void func_802754D4(HSD_GObj*);
void func_80275504(HSD_GObj* item_gobj); // Toggle several flags in 0xDCE off
void func_802756D0(HSD_GObj* item_gobj);
void func_802756E0(HSD_GObj* item_gobj);
void func_8027574C(HSD_GObj* item_gobj);
void func_80275870(HSD_GObj* item_gobj);
void func_80275E98(HSD_GObj*, SpawnItem*);
void func_802762B0(Item*);
void func_802762BC(Item*);
void func_802799E4(HSD_GObj* item_gobj); // Advance Item Script
void func_80279B64(Item*);
void func_80279B88(Item* item_data, s32 arg1, s32 arg2);
void func_80279BBC(Item* item_data);     /* extern */
void func_80279BE0(HSD_GObj* item_gobj); /* extern */
void func_8027B0C4(HSD_GObj*, SpawnItem*);
void func_8027D670(Vec3*);
void func_8027D730(HSD_GObj*);
HSD_GObj* func_80283AE4(s32, Vec3*, s32);
void func_80283BD4(HSD_GObj*);
HSD_GObj* func_802841B4(s32, Vec3*, s32);
void func_8028428C(HSD_GObj*);
HSD_GObj* func_80284854(Vec3*);
HSD_GObj* func_80284D54(Vec3*);
HSD_GObj* func_80286088(s32);
HSD_GObj* func_802896CC(Vec3*);
void func_8028FE90(HSD_GObj*);
HSD_GObj* func_80290938(HSD_JObj*);
HSD_GObj* func_80291BE0(Vec3*);
HSD_GObj* func_80292D48(Vec3*);
HSD_GObj* func_80294DC0(Vec3*);
void func_8029D968(HSD_GObj*);
void func_802D09D0(HSD_GObj*);
void func_802799E4(HSD_GObj* item_gobj); // Advance Item Script
void func_80279B88(Item* item_data, s32 arg1, s32 arg2);
void func_80279BBC(Item* item_data);     /* extern */
void func_80279BE0(HSD_GObj* item_gobj); /* extern */
void func_8026ABD8(struct _HSD_GObj*, Vec3*, f32);

#endif
