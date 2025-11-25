#include "player.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_0877.h"
#include "ft/ft_0D31.h"
#include "ft/ftdata.h"
#include "ft/ftdemo.h"
#include "ft/ftlib.h"
#include "ft/types.h"
#include "ftKirby/ftKb_Init.h"
#include "gm/gm_unsplit.h"
#include "if/ifstatus.h"
#include "lb/lbarchive.h"

#include "pl/forward.h"

#include "pl/plattack.h"
#include "pl/plbonus.h"
#include "pl/plstale.h"
#include "pl/types.h"

#include <dolphin/mtx.h>
#include <dolphin/os.h>
#include <baselib/debug.h>
#include <baselib/gobjplink.h>
#include <baselib/objalloc.h>

typedef struct _ftMapping {
    s8 internal_id;
    s8 extra_internal_id;
    s8 has_transformation;
} ftMapping;

/// TODO delete after fixing functions that use this
struct Unk_Struct_w_Array {
    char some_str[8 + 4]; //"PdPm.dat"
    char another_str[16 + 4];
    S8Vec3 vec_arr[30]; /// ftMapping_list
};

//// .data
char str_PdPmdat_start_of_data[] = "PdPm.dat";
char str_plLoadCommonData[] = "plLoadCommonData";

ftMapping ftMapping_list[CHKIND_MAX] = { //////ftMapping_list
    /* CKIND_CAPTAIN   */ { FTKIND_CAPTAIN, 0xFF },
    /* CKIND_DONKEY    */ { FTKIND_DONKEY, 0xFF },
    /* CKIND_FOX       */ { FTKIND_FOX, 0xFF },
    /* CKIND_GAMEWATCH */ { FTKIND_GAMEWATCH, 0xFF },
    /* CKIND_KIRBY     */ { FTKIND_KIRBY, 0xFF },
    /* CKIND_KOOPA     */ { FTKIND_KOOPA, 0xFF },
    /* CKIND_LINK      */ { FTKIND_LINK, 0xFF },
    /* CKIND_LUIGI     */ { FTKIND_LUIGI, 0xFF },
    /* CKIND_MARIO     */ { FTKIND_MARIO, 0xFF },
    /* CKIND_MARS      */ { FTKIND_MARS, 0xFF },
    /* CKIND_MEWTWO    */ { FTKIND_MEWTWO, 0xFF },
    /* CKIND_NESS      */ { FTKIND_NESS, 0xFF },
    /* CKIND_PEACH     */ { FTKIND_PEACH, 0xFF },
    /* CKIND_PIKACHU   */ { FTKIND_PIKACHU, 0xFF },
    /* CKIND_POPONANA  */ { FTKIND_POPO, FTKIND_NANA },
    /* CKIND_PURIN     */ { FTKIND_PURIN, 0xFF },
    /* CKIND_SAMUS     */ { FTKIND_SAMUS, 0xFF },
    /* CKIND_YOSHI     */ { FTKIND_YOSHI, 0xFF },
    /* CKIND_ZELDA     */ { FTKIND_ZELDA, FTKIND_SEAK, true },
    /* CKIND_SEAK      */ { FTKIND_SEAK, FTKIND_ZELDA, true },
    /* CKIND_FALCO     */ { FTKIND_FALCO, 0xFF },
    /* CKIND_CLINK     */ { FTKIND_CLINK, 0xFF },
    /* CKIND_DRMARIO   */ { FTKIND_DRMARIO, 0xFF },
    /* CKIND_EMBLEM    */ { FTKIND_EMBLEM, 0xFF },
    /* CKIND_PICHU     */ { FTKIND_PICHU, 0xFF },
    /* CKIND_GANON     */ { FTKIND_GANON, 0xFF },
    /* CKIND_MASTERH   */ { FTKIND_MASTERH, 0xFF },
    /* CKIND_BOY       */ { FTKIND_BOY, 0xFF },
    /* CKIND_GIRL      */ { FTKIND_GIRL, 0xFF },
    /* CKIND_GKOOPS    */ { FTKIND_GKOOPS, 0xFF },
    /* CKIND_CREZYH    */ { FTKIND_CREZYH, 0xFF },
    /* CHKIND_SANDBAG  */ { FTKIND_SANDBAG, 0xFF },
    /* CHKIND_POPO     */ { FTKIND_POPO, 0xFF }
};

////.bss
StaticPlayer player_slots[PL_SLOT_MAX];
HSD_ObjAllocData Player_AllocData;

pl_804D6470_t* pl_804D6470;

/// @todo This can be used in more places when functions are fixed to use
///       correct structs.
static inline bool hasExtraFighterId(ftMapping* data)
{
    return data->extra_internal_id != -1;
}

static inline void Player_CheckSlot(int slot)
{
    if (slot < 0 || !(slot < PL_SLOT_MAX)) {
        OSReport("cant get player struct! %d\n", slot);
        __assert(__FILE__, 102, "0");
    }
}

// Matches when everything is moved over
StaticPlayer* Player_GetPtrForSlot(int slot)
{
    Player_CheckSlot(slot);
    return &player_slots[slot];
}

void Player_80031790(int slot)
{
    StaticPlayer* player;
    int i;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    if ((player->slot_type == Gm_PKind_Human) ||
        (player->slot_type == Gm_PKind_Cpu))
    {
        for (i = 0; i < 2; i++) {
            /// transformed will either be [1,0] (normal) or [0,1]
            /// (transformed) checks to see if the player is in a transformed
            /// state, and calls the function only once depending on the state
            if ((player->player_entity[player->transformed[i]])) {
                ftLib_800867E8(player->player_entity[player->transformed[i]]);
            }
        }
    }
}

void Player_80031848(int slot)
{
    StaticPlayer* player;
    int i;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    if ((player->slot_type == Gm_PKind_Human) ||
        (player->slot_type == Gm_PKind_Cpu))
    {
        for (i = 0; i < 2; i++) {
            /// transformed will either be [1,0] (normal) or [0,1]
            /// (transformed) checks to see if the player is in a transformed
            /// state, and calls the function only once depending on the state
            if ((player->player_entity[player->transformed[i]])) {
                ftLib_8008688C(player->player_entity[player->transformed[i]]);
            }
        }
    }
}

static void func_8008688C_wrapper(StaticPlayer* player)
{
    if ((player->slot_type == Gm_PKind_Human) ||
        (player->slot_type == Gm_PKind_Cpu))
    {
        s32 i;
        for (i = 0; i < 2; i++) {
            if ((player->player_entity[player->transformed[i]])) {
                ftLib_8008688C(player->player_entity[player->transformed[i]]);
            }
        }
    }
}

void Player_80031900(void)
{
    int slot;
    for (slot = 0; slot < 6; slot++) {
        StaticPlayer* player = &player_slots[slot];
        Player_CheckSlot(slot);
        func_8008688C_wrapper(player);
    }
}

bool Player_800319C4(int slot, bool arg1)
{
    u8 _[4];

    int i;
    StaticPlayer* player;

    Player_CheckSlot(slot);
    player = (&player_slots[slot]);

    if (arg1) {
        for (i = 0; i < 2; i++) {
            if (!player->player_entity[player->transformed[i]]) {
                return false;
            }
        }

        return true;
    }

    for (i = 0; i < 2; i++) {
        if (player->player_entity[player->transformed[i]]) {
            return false;
        }
    }

    return true;
}

void Player_80031AD0(int slot)
{
    struct plAllocInfo first_struct;
    s32 internal_id;
    s32 has_transformation;
    s8 byte_check;
    s8* offset_arr;

    u8 unused0[4];

    StaticPlayer* player;

    struct plAllocInfo second_struct;

    u8 unused1[12];

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    // the commented line below makes more sense, but is off by one byte.
    // temp_vec = unused_ptr = ftMapping_list;
    offset_arr = (s8*) (&ftMapping_list[0].extra_internal_id);

    if (offset_arr[player->player_character * sizeof(ftMapping)] != -1) {
        player->flags.b2 = true;
    }

    internal_id = ftMapping_list[player->player_character].internal_id;
    Player_CheckSlot(slot);

    first_struct.internal_id = internal_id;
    first_struct.slot = slot;
    first_struct.b0 = false;
    first_struct.has_transformation = false;
    first_struct.x5 = -1;

    /// @todo Eliminate cast.
    player->player_entity[0] = Fighter_Create(&first_struct);
    player->player_state = 2;

    internal_id = byte_check =
        offset_arr[player->player_character * sizeof(ftMapping)];

    if (byte_check != -1) {
        has_transformation =
            ftMapping_list[player->player_character].has_transformation;

        Player_CheckSlot(slot);

        second_struct.internal_id = internal_id;
        second_struct.slot = slot;
        second_struct.b0 = true;
        second_struct.has_transformation = has_transformation;
        second_struct.x5 = -1;

        /// @todo Eliminate cast.
        player->player_entity[1] =
            Fighter_Create(&second_struct);

        if (player->player_state != 1) {
            player->player_state = 2;
        }
    }

    if (player->player_state == 2) {
        if (player->struct_func != NULL) {
            player->struct_func(slot);
        }
    }
}

void Player_80031CB0(CharacterKind kind, u8 color)
{
    if (ftMapping_list[kind].internal_id != -1) {
        ftData_800855C8(ftMapping_list[kind].internal_id, color);
    }

    if (hasExtraFighterId(&ftMapping_list[kind])) {
        ftData_800855C8(ftMapping_list[kind].extra_internal_id, color);
    }
}

void Player_80031D2C(CharacterKind kind, u8 color)
{
    if (ftMapping_list[kind].internal_id != -1) {
        ftData_8008578C(ftMapping_list[kind].internal_id, color);
    }

    if (hasExtraFighterId(&ftMapping_list[kind])) {
        ftData_8008578C(ftMapping_list[kind].extra_internal_id, color);
    }
}

void Player_80031DA8(s32 param_1, s32 param_2)
{
    ftKb_SpecialN_800EED50(param_1, param_2);
}

void Player_80031DC8(void func_arg(s32, s32))
{
    int slot;
    for (slot = 0; slot < 6; slot++) {
        Player_CheckSlot(slot);

        if (player_slots[slot].player_state) {
            func_arg(ftMapping_list[player_slots[slot].player_character]
                         .internal_id,
                     0);
            if (hasExtraFighterId(
                    &ftMapping_list[player_slots[slot].player_character]))
            {
                func_arg(ftMapping_list[player_slots[slot].player_character]
                             .extra_internal_id,
                         0);
            }
        }
    }
}

void Player_80031EBC(int slot)
{
    s32 i;
    Player_CheckSlot(slot);

    for (i = 0; i < 2; i++) {
        StaticPlayer* player = &player_slots[slot];
        if ((player->player_entity[player->transformed[i]])) {
            if (!ftLib_8008701C(player->player_entity[player->transformed[i]]))
            {
                ftCo_800D4F24(player->player_entity[player->transformed[i]],
                              1);
            }
            HSD_GObjPLink_80390228(
                player->player_entity[player->transformed[i]]);
        }
    }
}

void Player_80031FB0(int slot, s32 entity_index)
{
    u8 _[4];

    StaticPlayer* player;
    Player_CheckSlot(slot);

    player = &player_slots[slot];
    player->player_entity[player->transformed[entity_index]] = NULL;

    if (player->flags.b2 == false || Player_800319C4(slot, 0)) {
        player->player_state = 0;
    }
}

/// new match decomp.me/scratch/oHfiV  TODO
//// old match decomp.me/scratch/8otnq
void Player_80032070(int slot, bool bool_arg)
{
    StaticPlayer* player;
    struct Unk_Struct_w_Array* unkStruct =
        (struct Unk_Struct_w_Array*) &str_PdPmdat_start_of_data;
    Player_CheckSlot(slot);
    player = &player_slots[slot];

    if (bool_arg == 0) {
        ftCo_800D4FF4(player->player_entity[player->transformed[0]]);

        if (player->flags.b2 &&
            unkStruct->vec_arr[player->player_character].z == 0 &&
            ftLib_8008701C(player->player_entity[player->transformed[1]]))
        {
            ftCo_800D4FF4(player->player_entity[player->transformed[1]]);
        }

        ifStatus_802F6E1C(slot);
        return;
    }

    if (ftLib_800873CC(player->player_entity[player->transformed[0]])) {
        ftCo_800D4FF4(player->player_entity[player->transformed[1]]);
    }
}

bool Player_8003219C(int slot)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    return ftLib_8008701C(player->player_entity[player->transformed[0]]);
}

bool Player_8003221C(int slot)
{
    StaticPlayer* player;

    if (Player_GetPlayerState(slot) == 2) {
        Player_CheckSlot(slot);
        player = &player_slots[slot];

        if (!ftLib_8008701C(player->player_entity[player->transformed[0]])) {
            return true;
        }
    }

    return false;
}

s32 Player_GetPlayerState(s32 slot)
{
    s32 state;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    state = player->player_state;
    return state;
}

CharacterKind Player_GetPlayerCharacter(int slot)
{
    u8 _[4];

    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    return player->player_character;
}

void Player_SetPlayerCharacter(s32 slot, CharacterKind value)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->player_character = value;
}

Gm_PKind Player_GetPlayerSlotType(s32 slot)
{
    Gm_PKind slot_type;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    slot_type = player->slot_type;
    return slot_type;
}

Gm_PKind Player_8003248C(s32 slot, bool arg1)
{
    Gm_PKind slot_type;
    struct Unk_Struct_w_Array* unk_struct =
        (struct Unk_Struct_w_Array*) &str_PdPmdat_start_of_data;
    StaticPlayer* player;

    Player_CheckSlot(slot);

    player = &player_slots[slot];

    if (arg1 == 1) {
        if (unk_struct->vec_arr[player->player_character].z == 0) {
            if (player->slot_type == Gm_PKind_Human ||
                player->slot_type == Gm_PKind_Cpu)
            {
                return 1;
            }
        }
    }
    slot_type = player->slot_type;

    return slot_type;
}

void Player_SetSlottype(s32 slot, Gm_PKind value)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->slot_type = value;
}

s8 Player_800325C8(CharacterKind kind, bool b)
{
    if (!b) {
        return ftMapping_list[kind].internal_id;
    } else if (b == 1) {
        return ftMapping_list[kind].extra_internal_id;
    }

    return -1;
}

s8 Player_80032610(s32 slot, bool arg1)
{ //// decomp.me/scratch/pHTx2

    struct Unk_Struct_w_Array* some_struct =
        (struct Unk_Struct_w_Array*) &str_PdPmdat_start_of_data;
    StaticPlayer* player;
    s32 error_value = -1;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    if (arg1 == 0) {
        return some_struct->vec_arr[player->player_character].x;
    }
    if (arg1 == 1) {
        return some_struct->vec_arr[player->player_character].y;
    }

    return error_value;
}

void Player_LoadPlayerCoords(s32 slot, Vec3* arg_vec)
{
    StaticPlayer* player;
    Vec3* player_vecs;

    Player_CheckSlot(slot);

    player = &player_slots[slot];
    player_vecs = player->player_poses.byIndex;
    *arg_vec = player_vecs[player->transformed[0]];
}

void Player_80032768(s32 slot, Vec3* arg_vec)
{
    StaticPlayer* player;
    Vec3* player_vecs;

    Vec3* dst_vec;
    Vec3* dst_vec2;

    Player_CheckSlot(slot);

    player = &player_slots[slot];

    player_vecs = player->player_poses.byIndex;
    dst_vec = &player_vecs[player->transformed[0]];
    *dst_vec = *arg_vec;

    player_vecs = player->player_poses.byIndex;
    dst_vec2 = &player_vecs[player->transformed[1]];
    *dst_vec2 = *arg_vec;
}

void Player_80032828(s32 slot, s32 index, Vec3* arg_vec)
{
    StaticPlayer* player;
    Vec3* player_vecs;

    Player_CheckSlot(slot);

    player = &player_slots[slot];

    player_vecs = player->player_poses.byIndex;
    player_vecs[player->transformed[index]] = *arg_vec;
}

void Player_800328D4(int slot, Vec3* arg_vec)
{
    StaticPlayer* player;
    int i;
    Vec3* player_vecs;
    Vec3* player_vecs2;

    Vec3* dst_vec;
    Vec3* dst_vec2;

    u8 _[4];

    Player_CheckSlot(slot);
    player = &player_slots[slot];
    Player_CheckSlot(slot);

    player_vecs = player->player_poses.byIndex;
    dst_vec = &player_vecs[player->transformed[0]];
    *dst_vec = *arg_vec;

    player_vecs2 = player->player_poses.byIndex;
    dst_vec2 = &player_vecs2[player->transformed[1]];
    *dst_vec2 = *arg_vec;

    for (i = 0; i < 2; i++) {
        if (player->player_entity[player->transformed[i]]) {
            ftLib_80087140(player->player_entity[player->transformed[i]]);
        }
    }
}

void Player_80032A04(int slot, Vec3* arg_vec)
{
    StaticPlayer* player;
    int i;

    Player_CheckSlot(slot);

    for (i = 0; i < 2; i++) {
        player = &player_slots[slot];

        player->player_poses.byIndex[player->transformed[i]] = *arg_vec;

        if (player->player_entity[player->transformed[i]]) {
            ftLib_80086664(player->player_entity[player->transformed[i]],
                           arg_vec);
        }
    }
}

void Player_SetPlayerAndEntityFacingDirection(s32 slot, f32 facing_dir)
{
    StaticPlayer* player;
    int i;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    for (i = 0; i < 2; i++) {
        player->facing_direction = facing_dir;

        if (player->player_entity[player->transformed[i]]) {
            ftDemo_SetFacingDirection(
                player->player_entity[player->transformed[i]], facing_dir);
        }
    }
}

f32 Player_80032BB0(s32 slot)
{
    StaticPlayer* player;
    f32 temp;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    temp = ftLib_800869F8(player->player_entity[player->transformed[0]]);
    return temp / player->model_scale;
}

void Player_SetScale(s32 slot, f32 scale)
{
    StaticPlayer* player;
    s32 i;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->model_scale = scale;
    for (i = 0; i < 2; i++) {
        if (player->player_entity[player->transformed[i]]) {
            ftLib_SetScale(player->player_entity[player->transformed[i]],
                           scale);
        }
    }
}

void Player_GetSpawnPlatformPos(s32 slot, Vec3* arg_vec)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    *arg_vec = player->player_poses.byVecName.spawn_platform_final_pos;
}

void Player_SetSpawnPlatformPos(s32 slot, Vec3* arg_vec)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->player_poses.byVecName.spawn_platform_final_pos = *arg_vec;
}

void Player_GetSomePos(s32 slot, Vec3* arg_vec)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    *arg_vec = player->player_poses.byVecName.some_other_player_pos;
}

void Player_SetSomePos(s32 slot, Vec3* arg_vec)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->player_poses.byVecName.some_other_player_pos = *arg_vec;
}

s32 Player_80032F30(s32 slot)
{
    StaticPlayer* player;
    s32 value;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    value = player->unk4E;
    return value;
}

void Player_80032FA4(s32 slot, s32 arg)
{
    StaticPlayer* player;

    u8 _[4];

    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->unk4E = arg;
}

f32 Player_GetFacingDirection(s32 slot)
{
    u8 _[4];
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    return player->facing_direction;
}

void Player_SetFacingDirection(s32 slot, f32 direction)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->facing_direction = direction;
}

void Player_SetFacingDirectionConditional(s32 slot, bool b, f32 direction)
{
    u8 _[4];

    if (!b) {
        StaticPlayer* player;
        Player_CheckSlot(slot);
        player = &player_slots[slot];
        player->facing_direction = direction;
    }
}

u32 Player_GetCostumeId(int slot)
{
    u8 costume_id;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    costume_id = player->costume_id;
    return costume_id;
}

void Player_SetCostumeId(int slot, int costume_id)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->costume_id = costume_id;
}

u8 Player_GetControllerIndex(int slot)
{
    s8 controller_index;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    controller_index = player->controller_index;
    return controller_index;
}

void Player_SetControllerIndex(int slot, s8 controller_index)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->controller_index = controller_index;
}

int Player_GetTeam(int slot)
{
    int team;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    team = player->team;
    return team;
}

void Player_SetTeam(int slot, s8 team)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->team = team;
}

int Player_GetPlayerId(int slot)
{
    u8 player_id;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player_id = player->player_id;
    return player_id;
}

void Player_SetPlayerId(int slot, int player_id)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->player_id = player_id;
}

int Player_GetCpuLevel(int slot)
{
    int cpu_level;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    cpu_level = player->cpu_level;
    return cpu_level;
}

void Player_SetPlayerAndEntityCpuLevel(int slot, int cpu_level)
{
    StaticPlayer* player;
    int i;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->cpu_level = cpu_level;

    for (i = 0; i < 2; i++) {
        if (player->player_entity[player->transformed[i]]) {
            ft_80087BEC(player->player_entity[player->transformed[i]],
                        cpu_level);
        }
    }
}

int Player_GetCpuType(int slot)
{
    int cpu_type;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    cpu_type = player->cpu_type;
    return cpu_type;
}

void Player_SetPlayerAndEntityCpuType(int slot, int cpu_type)
{
    StaticPlayer* player;
    int i;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->cpu_type = cpu_type;

    for (i = 0; i < 2; i++) {
        if (player->player_entity[player->transformed[i]]) {
            ft_80087BC0(player->player_entity[player->transformed[i]],
                        cpu_type);
        }
    }
}

int Player_GetHandicap(int slot)
{
    u8 handicap;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    handicap = player->handicap;
    return handicap;
}

void Player_SetHandicap(int slot, s8 handicap)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->handicap = handicap;
}

f32 Player_GetUnk50(int slot)
{
    f32 unk50;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    unk50 = player->unk50;
    return unk50;
}

f32 Player_GetAttackRatio(int slot)
{
    f32 attack_ratio;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    attack_ratio = player->attack_ratio;
    return attack_ratio;
}

void Player_SetAttackRatio(int slot, f32 attack_ratio)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->attack_ratio = attack_ratio;
}

f32 Player_GetDefenseRatio(int slot)
{
    f32 defense_ratio;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    defense_ratio = player->defense_ratio;
    return defense_ratio;
}

void Player_SetDefenseRatio(int slot, f32 defense_ratio)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->defense_ratio = defense_ratio;
}

f32 Player_GetModelScale(int slot)
{
    f32 model_scale;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    model_scale = player->model_scale;
    return model_scale;
}

void Player_SetModelScale(int slot, f32 model_scale)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->model_scale = model_scale;
}

s32 Player_80033BB8(int slot)
{
    return gm_8016C5C0(slot);
}

s32 Player_GetStocks(int slot)
{
    s8 stocks;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    stocks = player->stocks;
    return stocks;
}

int Player_GetP1Stock(void)
{
    return player_slots[0].stocks;
}

void Player_SetStocks(int slot, int stocks)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->stocks = stocks;
}

void Player_LoseStock(int slot)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];

    if (player->stocks > 0) {
        player->stocks = player->stocks - 1;
    }
}

int Player_GetCoins(int slot)
{
    int current_coins;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    current_coins = player->current_coins;
    return current_coins;
}

void Player_SetCoins(int slot, int current_coins)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->current_coins = current_coins;
}

int Player_GetTotalCoins(int slot)
{
    int total_coins;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    total_coins = player->total_coins;
    return total_coins;
}

void Player_SetTotalCoins(int slot, int coins)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->total_coins = coins;
}

s32 Player_GetUnk98(s32 slot)
{
    s32 unk98;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    unk98 = player->unk98;
    return unk98;
}

void Player_SetUnk98(s32 slot, s32 unk98)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->unk98 = unk98;
}

s32 Player_GetUnk9C(s32 slot)
{
    s32 unk9C;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    unk9C = player->unk9C;
    return unk9C;
}

void Player_SetUnk9C(s32 slot, s32 unk9C)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->unk9C = unk9C;
}

HSD_GObj* Player_GetEntity(s32 slot)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    return player->player_entity[player->transformed[0]];
}

/// @remarks Mostly called by Ice Climbers code, must be because they have 2nd
///          entity
HSD_GObj* Player_GetEntityAtIndex(int slot, int index)
{
    StaticPlayer* player;
    int entity_index;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    entity_index = player->transformed[index];
    return player->player_entity[entity_index];
}

void Player_SwapTransformedStates(s32 slot, s32 arg1, s32 arg2)
{
    u8 temp_r5;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];

    temp_r5 = player->transformed[arg1];
    player->transformed[arg1] = player->transformed[arg2];
    player->transformed[arg2] = temp_r5;
}

s32 Player_GetDamage(s32 slot)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    return player->staminas.byIndex[player->transformed[0]];
}

void Player_SetHUDDamage(s32 slot, s32 arg1)
{
    StaticPlayer* player;
    s32 i;
    Player_CheckSlot(slot);

    for (i = 0; i < 2; i++) {
        player = &player_slots[slot];
        player->staminas.byIndex[player->transformed[i]] = arg1;
        if (player->player_entity[player->transformed[i]]) {
            ftLib_800870F0(player->player_entity[player->transformed[i]],
                           arg1);
        }
    }
}

void Player_SetHPByIndex(s32 slot, s32 arg1, s32 arg2)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);

    player = &player_slots[slot];
    player->staminas.byIndex[player->transformed[arg1]] = arg2;
}

int Player_GetOtherStamina(s32 slot)
{
    s16 stamina;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    stamina = player->staminas.byName.stamina;
    return stamina;
}

void Player_SetOtherStamina(s32 slot, s32 stamina)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->staminas.byName.stamina = stamina;
}

int Player_GetRemainingHP(s32 slot)
{
    StaticPlayer* player;
    s32 result;
    u32 result2;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    result = player->staminas.byName.stamina -
             player->staminas.byIndex[player->transformed[0]];
    result2 = result;
    if (result < 0) {
        result2 = 0;
    }
    return result2;
}

bool Player_GetMoreFlagsBit2(s32 slot)
{
    StaticPlayer* player;
    u8 bit2;
    Player_CheckSlot(slot);
    player = &player_slots[slot];

    bit2 = player->more_flags.b2;
    return bit2;
}

void Player_SetMoreFlagsBit2(s32 slot, u8 bit2)
{
    StaticPlayer* player;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    player->more_flags.b2 = bit2;
}

bool Player_GetMoreFlagsBit3(s32 slot)
{
    StaticPlayer* player;
    s32 bit3;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    bit3 = player->more_flags.b3;
    return bit3;
}

void Player_SetMoreFlagsBit3(s32 slot, u8 bit3)
{
    StaticPlayer* player;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    player->more_flags.b3 = bit3;
}

void Player_SetMoreFlagsBit4(s32 slot, u8 bit4)
{
    StaticPlayer* player;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    player->more_flags.b4 = bit4;
}

bool Player_GetMoreFlagsBit4(s32 slot)
{
    StaticPlayer* player;
    u8 bit4;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    bit4 = player->more_flags.b4;
    return bit4;
}

bool Player_GetMoreFlagsBit5(s32 slot)
{
    StaticPlayer* player;
    u8 bit5;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    bit5 = player->more_flags.b5;
    return bit5;
}

void Player_SetMoreFlagsBit5(s32 slot, u8 bit5)
{
    StaticPlayer* player;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    player->more_flags.b5 = bit5;
}

bool Player_GetMoreFlagsBit6(s32 slot)
{
    StaticPlayer* player;
    u8 bit6;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    bit6 = player->more_flags.b6;
    return bit6;
}

void Player_SetMoreFlagsBit6(s32 slot, u8 bit6)
{
    StaticPlayer* player;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    player->more_flags.b6 = bit6;
}

u8 Player_GetFlagsAEBit0(s32 slot)
{
    StaticPlayer* player;
    u8 bit0;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    bit0 = player->flagsAE.b0;
    return bit0;
}

void Player_SetFlagsAEBit0(s32 slot, u8 bit0)
{
    StaticPlayer* player;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    player->flagsAE.b0 = bit0;
}

s32 Player_GetRemainingHPByIndex(s32 slot, s32 index)
{
    StaticPlayer* player;
    u32 stamina;
    s32 result;
    s32 result2;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    stamina = player->staminas.byName.stamina;
    result = stamina - player->staminas.byIndex[player->transformed[index]];
    result2 = result;
    if (result < 0) {
        result2 = 0;
    }
    return result2;
}

s32 Player_GetFalls(s32 slot)
{ /// decomp.me/scratch/8ijor
    StaticPlayer* player;
    struct Unk_Struct_w_Array* unkStruct =
        (struct Unk_Struct_w_Array*) &str_PdPmdat_start_of_data;
    Player_CheckSlot(slot);
    player = &player_slots[slot];

    if (unkStruct->vec_arr[player->player_character].y != -1 &&
        unkStruct->vec_arr[player->player_character].z != 0)
    {
        return player->falls[player->transformed[0]] +
               player->falls[player->transformed[1]];
    }

    return player->falls[player->transformed[0]];
}

s32 Player_GetFallsByIndex(s32 slot, s32 arg1)
{
    StaticPlayer* player;
    s32 falls;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    falls = player->falls[player->transformed[arg1]];
    return falls;
}

void Player_SetFalls(int slot, s32 falls)
{
    u8 _[4];

    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->falls[player->transformed[0]] = falls;
}

void Player_SetFallsByIndex(int slot, enum_t index, s32 falls)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->falls[player->transformed[index]] = falls;
}

s32 Player_GetKOsByPlayerIndex(int slot, int idx)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    return player->kos_by_player[idx];
}

void Player_UpdateKOsBySlot(int slot, bool bool_arg, int other_slot)
{
    StaticPlayer* player;
    StaticPlayer* other_player;

    u8 _[16];

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    if (!bool_arg) {
        unsigned kos = player->kos_by_player[other_slot];

        if (kos < U32_MAX) {
            player->kos_by_player[other_slot]++;
        }

        if (slot == other_slot) {
            ifStatus_802F6D10(other_slot);
        } else {
            if (gm_8016B168()) {
                Player_CheckSlot(slot);
                Player_CheckSlot(other_slot);
                other_player = &player_slots[other_slot];

                {
                    int player_team;
                    int other_player_team;
                    player_team = player->team;
                    other_player_team = other_player->team;
                    if (player_team == other_player_team) {
                        ifStatus_802F69C0(other_slot, slot);
                        return;
                    }
                }
            }

            ifStatus_802F6AF8(other_slot);
        }
    }
}

u32 Player_GetMatchFrameCount(int slot)
{
    StaticPlayer* player;
    u32 count;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    count = player->match_frame_count;
    return count;
}

void Player_UpdateMatchFrameCount(int slot, bool condition)
{
    StaticPlayer* player;
    PAD_STACK(4);

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    if ((condition == 0) && (player->match_frame_count + 0x10000) == 0xffff) {
        player->match_frame_count = gm_8016AEDC();
    }
}

u32 Player_GetSuicideCount(int slot)
{
    StaticPlayer* player;
    u32 count;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    count = player->suicide_count;
    return count;
}

void Player_SetSuicideCount(s32 slot, u32 suicide_count)
{
    StaticPlayer* player;

    if (suicide_count > 0xffff || 0 > (s32) suicide_count) {
        return;
    }

    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->suicide_count = suicide_count;
}

void Player_IncSuicideCount(s32 slot, s32 condition)
{
    StaticPlayer* player;
    u16 suicide_count;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    if (condition == 0) {
        suicide_count = player->suicide_count;
        if (suicide_count < 0xffff) {
            player->suicide_count++;
            ifStatus_802F6C04(slot);
        }
    }
}

bool Player_800353BC(s32 slot)
{
    StaticPlayer* player;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    if (player->player_state == 2 && (player->flags.b0)) {
        return 1;
    }

    return 0;
}

bool Player_8003544C(s32 slot, bool condition)
{
    u8 _[4];

    if (!condition) {
        StaticPlayer* player;

        Player_CheckSlot(slot);
        player = &player_slots[slot];

        if (player->player_state == 2 && player->flags.b0) {
            return true;
        }
    }

    return false;
}

void Player_SetFlagsBit0(int slot, bool bit0)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->flags.b0 = bit0;
}

u8 Player_GetNametagSlotID(int slot)
{
    StaticPlayer* player;
    int nametag_slot_id;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    nametag_slot_id = player->nametag_slot_id;
    return nametag_slot_id;
}

void Player_SetNametagSlotID(int slot, int nametag_slot_id)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->nametag_slot_id = nametag_slot_id;
}

s32 Player_GetFlagsBit1(s32 slot)
{
    StaticPlayer* player;
    u8 bit1;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    bit1 = player->flags.b1;
    return bit1;
}

void Player_SetFlagsBit1(s32 slot)
{
    StaticPlayer* player;
    s8 one = 1;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->flags.b1 = one;
}

void Player_UnsetFlagsBit1(int slot)
{
    u8 _[1];

    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->flags.b1 = false;
}

s32 Player_GetFlagsBit3(s32 slot)
{
    StaticPlayer* player;
    u8 bit3;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    bit3 = player->flags.b3;
    return bit3;
}

void Player_SetFlagsBit3(s32 slot, u8 bit3)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->flags.b3 = bit3;
}

int Player_GetFlagsBit4(int slot)
{
    StaticPlayer* player;
    u8 bit4;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    bit4 = player->flags.b4;
    return bit4;
}

u8 Player_GetFlagsBit5(s32 slot)
{
    StaticPlayer* player;
    u8 is_metal;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    is_metal = player->flags.is_metal;
    return is_metal;
}

void Player_SetFlagsBit5(s32 slot, u8 is_metal)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->flags.is_metal = is_metal;
}

u8 Player_GetFlagsBit6(s32 slot)
{
    StaticPlayer* player;
    u8 bit6;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    bit6 = player->flags.b6;
    return bit6;
}

void Player_SetFlagsBit6(s32 slot, u8 bit6)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->flags.b6 = bit6;
}

u8 Player_GetFlagsBit7(s32 slot)
{
    StaticPlayer* player;
    u8 bit7;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    bit7 = player->flags.b7;
    return bit7;
}

void Player_SetFlagsBit7(s32 slot, u8 bit7)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->flags.b7 = bit7;
}

bool Player_GetMoreFlagsBit0(s32 slot)
{
    StaticPlayer* player;
    u8 bit0;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    bit0 = player->more_flags.b0;
    return bit0;
}

bool Player_GetMoreFlagsBit1(s32 slot)
{
    StaticPlayer* player;
    u8 bit1;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    bit1 = player->more_flags.b1;
    return bit1;
}

void Player_SetMoreFlagsBit1(s32 slot, u8 bit1)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->more_flags.b1 = bit1;
}

s32 Player_GetUnk4D(s32 slot)
{
    StaticPlayer* player;
    u8 unk4D;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    unk4D = player->unk4D;
    return unk4D;
}

void Player_SetUnk4D(s32 slot, s8 unk4D)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->unk4D = unk4D;
}

u8 Player_GetFlagsAEBit1(s32 slot)
{
    StaticPlayer* player;
    u8 bit1;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    bit1 = player->flagsAE.b1;
    return bit1;
}

#ifdef BUGFIX
void Player_SetFlagsAEBit1(int slot, u8 bit1)
#else
u8 Player_SetFlagsAEBit1(int slot, u8 bit1)
#endif
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->flagsAE.b1 = bit1;
}

int Player_GetUnk4C(s32 slot)
{
    StaticPlayer* player;
    u8 unk4C;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    unk4C = player->unk4C;
    return unk4C;
}

void Player_SetUnk4C(s32 slot, u8 unk4C)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->unk4C = unk4C;
}

bool Player_80036058(s32 slot)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    return ftLib_80086F4C(player->player_entity[player->transformed[0]]);
}

float Player_800360D8(s32 slot)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    return ftLib_80086F80(player->player_entity[player->transformed[0]]);
}

void Player_SetStructFunc(s32 slot, void* arg_func)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->struct_func = arg_func;
}

plActionStats* Player_GetActionStats(int slot)
{
    StaticPlayer* player;
    plActionStats* attack_count;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    attack_count = &player->stale_moves.total_attack_count_struct;
    return attack_count;
}

StaleMoveTable* Player_GetStaleMoveTableIndexPtr(s32 slot)
{
    StaticPlayer* player;
    StaleMoveTable* stale_move_table;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    stale_move_table = &player->stale_moves;
    return stale_move_table;
}

struct pl_x5EC_t* Player_GetUnk6A8Ptr(int slot)
{
    StaticPlayer* player;
    struct pl_x5EC_t* unk6A8;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    unk6A8 = &player->stale_moves.x5EC;
    return unk6A8;
}

pl_StaleMoveTableExt_t* Player_GetStaleMoveTableIndexPtr2(s32 slot)
{
    StaticPlayer* player;
    pl_StaleMoveTableExt_t* stale_move_table;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    stale_move_table = (pl_StaleMoveTableExt_t*) (&player->stale_moves);
    return stale_move_table;
}

FighterKind Player_80036394(s32 slot)
{
    StaticPlayer* player;
    HSD_GObj* entity;
    Player_CheckSlot(slot);
    player = &player_slots[slot];

    entity = player->player_entity[player->transformed[0]];

    if (entity) {
        return ftLib_800872A4(entity);
    }
    return -1;
}

s32 Player_80036428(s32 slot)
{
    StaticPlayer* player;
    HSD_GObj* entity;
    Player_CheckSlot(slot);
    player = &player_slots[slot];

    entity = player->player_entity[player->transformed[0]];

    if (entity) {
        return ftLib_80087300(entity);
    }
    return 6;
}

void Player_SetUnk45(s32 slot, int unk45)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->unk45 = unk45;
}

u8 Player_GetUnk45(s32 slot)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    if (player->slot_type == Gm_PKind_Human) {
        return player->unk45;
    }

    return 4;
}

void Player_UpdateJoystickCountByIndex(s32 slot, s32 index)
{
    StaticPlayer* player;
    s32 transformed;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    transformed = player->transformed[index];
    player->joystick_direction_input_count[transformed]++;
}

s32 Player_GetJoystickCountByIndex(s32 slot, s32 index)
{
    StaticPlayer* player;
    s32 transformed;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    transformed = player->transformed[index];
    return player->joystick_direction_input_count[transformed];
}

void Player_800366DC(s32 slot, s32 arg1)
{
    StaticPlayer* player;
    s32 i;
    Player_CheckSlot(slot);
    player = &player_slots[slot];

    for (i = 0; i < 2; i++) {
        if (player->player_entity[player->transformed[i]]) {
            ft_80087AC0(player->player_entity[player->transformed[i]], arg1);
        }
    }
}

void Player_80036790(s32 slot, f32 arg1)
{
    StaticPlayer* player;
    s32 i;
    Player_CheckSlot(slot);
    player = &player_slots[slot];

    for (i = 0; i < 2; i++) {
        if (player->player_entity[player->transformed[i]]) {
            ftLib_80086A4C(player->player_entity[player->transformed[i]],
                           arg1);
        }
    }
}

void Player_80036844(s32 slot, s32 arg1)
{
    StaticPlayer* player;
    s32 i;
    Player_CheckSlot(slot);
    player = &player_slots[slot];

    for (i = 0; i < 2; i++) {
        if (player->player_entity[player->transformed[i]]) {
            ft_80087BAC(player->player_entity[player->transformed[i]], arg1);
        }
    }
}

bool Player_800368F8(int slot)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    return ftLib_80086BB4(player->player_entity[player->transformed[0]]);
}

void Player_80036978(s32 slot, s32 arg1)
{
    StaticPlayer* player;

    u8 _[4];

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    /// @todo Eliminate cast.
    ftLib_80086B90(player->player_entity[player->transformed[0]],
                   (Vec3*) arg1);
}

void Player_InitOrResetPlayer(s32 slot)
{
    StaticPlayer* player;
    u8* transformed0;
    u8* transformed1;
    f32 zerofloat;
    f32 onefloat;

    u8 _[56];

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    player->player_state = 0;
    player->player_character = 8;
    transformed0 = &player->transformed[0];
    transformed1 = &player->transformed[1];

    zerofloat = 0.0f;
    player->player_poses.byIndex[*transformed0].z = zerofloat;
    player->player_poses.byIndex[*transformed0].y = zerofloat;
    player->player_poses.byIndex[*transformed0].x = zerofloat;

    player->player_poses.byIndex[*transformed1].z = zerofloat;
    player->player_poses.byIndex[*transformed1].y = zerofloat;
    player->player_poses.byIndex[*transformed1].x = zerofloat;

    player->player_poses.byIndex[2].z = zerofloat;
    player->player_poses.byIndex[2].y = zerofloat;
    player->player_poses.byIndex[2].x = zerofloat;
    player->player_poses.byIndex[3].z = zerofloat;
    player->player_poses.byIndex[3].y = zerofloat;
    player->player_poses.byIndex[3].x = zerofloat;

    player->costume_id = 0;
    player->slot_type = Gm_PKind_NA;
    player->transformed[0] = 0;
    player->transformed[1] = 1;

    player->unk45 = 0;
    player->controller_index = 0;
    player->team = 0;
    player->player_id = 0;
    player->cpu_level = 0;

    player->cpu_type = 4;

    player->handicap = 0;
    player->unk4C = 0;

    player->unk4D = 4;
    player->unk4E = -1;

    onefloat = 1.0;
    player->unk50 = onefloat;
    player->attack_ratio = onefloat;
    player->defense_ratio = onefloat;
    player->model_scale = onefloat;

    player->staminas.byIndex[player->transformed[0]] = 0;
    player->staminas.byIndex[player->transformed[1]] = 0;
    player->staminas.byIndex[2] = 0;

    player->falls[player->transformed[0]] = 0;
    player->falls[player->transformed[1]] = 0;

    player->kos_by_player[0] = 0;
    player->kos_by_player[1] = 0;
    player->kos_by_player[2] = 0;
    player->kos_by_player[3] = 0;
    player->kos_by_player[4] = 0;
    player->kos_by_player[5] = 0;

    player->match_frame_count = -1;
    player->suicide_count = 0;
    player->stocks = 0;

    player->current_coins = 0;
    player->total_coins = 0;
    player->unk98 = 0;
    player->unk9C = 0;

    player->joystick_direction_input_count[*transformed0] = 0;
    player->joystick_direction_input_count[*transformed1] = 0;

    player->flags.b0 = 0;
    player->nametag_slot_id = 0;
    player->flags.b1 = 0;
    player->flags.b2 = 0;
    player->flags.b3 = 0;
    player->flags.b4 = 0;
    player->flags.is_metal = false;
    player->flags.b6 = 0;
    player->flags.b7 = 0;

    player->more_flags.b0 = 0;
    player->more_flags.b1 = 0;
    player->more_flags.b2 = 0;
    player->more_flags.b3 = 0;
    player->more_flags.b4 = 0;
    player->more_flags.b5 = 0;
    player->more_flags.b6 = 0;

    player->flagsAE.b0 = 0;
    player->flagsAE.b1 = 0;

    player->player_entity[*transformed0] = 0;
    player->player_entity[*transformed1] = 0;

    player->struct_func = 0;
}

void Player_80036CF0(s32 slot)
{
    Player_InitOrResetPlayer(slot);
    pl_8003891C(slot);
}

void Player_80036D24(s32 slot)
{
    Player_InitOrResetPlayer(slot);
    pl_80038F10(slot);
}

void Player_InitAllPlayers(void)
{
    int i;
    plStale_InitAttackInstance();
    plAttack_80037590();

    for (i = 0; i < PL_SLOT_MAX; i++) {
        Player_InitOrResetPlayer(i);
        pl_8003891C(i);
    }
}

void Player_80036DA4(void)
{
    HSD_ObjAllocInit(&Player_AllocData, 8, 4);
    Fighter_FirstInitialize_80067A84();
}

void Player_80036DD8(void)
{
    void** sp8;

    lbArchive_LoadSymbols(str_PdPmdat_start_of_data, (void**) &sp8,
                          str_plLoadCommonData, 0);
    pl_804D6470 = *sp8;
}

void Player_80036E20(CharacterKind ckind, HSD_Archive* archive, s32 arg2)
{
    struct Unk_Struct_w_Array* unkStruct =
        (struct Unk_Struct_w_Array*) &str_PdPmdat_start_of_data;
    ftDemo_SetArchiveData(unkStruct->vec_arr[ckind].x, archive, arg2);
    if ((unkStruct->vec_arr[ckind].y != -1) &&
        (unkStruct->vec_arr[ckind].z == 0))
    {
        ftDemo_SetArchiveData(unkStruct->vec_arr[ckind].y, archive, arg2);
    }
}

s32 Player_80036EA0(s32 slot)
{
    StaticPlayer* player;
    HSD_GObj* entity;
    Player_CheckSlot(slot);
    player = &player_slots[slot];

    entity = player->player_entity[player->transformed[0]];

    if (entity) {
        /// @todo Eliminate cast.
        return (s32) ftLib_800865F0(entity);
    }

    return 0;
}

void Player_80036F34(s32 slot, s32 arg1)
{
    struct plAllocInfo2 some_struct;
    u8 _;
    StaticPlayer* player;

    Player_CheckSlot(slot);
    player = &player_slots[slot];
    some_struct.internal_id =
        ftMapping_list[player->player_character].internal_id;
    some_struct.slot = slot;
    some_struct.has_transformation = 0;
    some_struct.unk8 = arg1;
    some_struct.b0 = 0;

    player->slot_type = Gm_PKind_Demo;
    player->player_entity[0] = ftDemo_CreateFighter(&some_struct);
    if ((ftMapping_list[player->player_character].extra_internal_id != -1) &&
        (ftMapping_list[player->player_character].has_transformation == 0))
    {
        some_struct.internal_id =
            ftMapping_list[player->player_character].extra_internal_id;
        some_struct.has_transformation = 1;
        player->player_entity[1] = ftDemo_CreateFighter(&some_struct);
    }
}

void Player_80037054(s32 slot, s32 arg1)
{
    struct plAllocInfo2 some_struct;
    u8 _;
    StaticPlayer* player;

    Player_CheckSlot(slot);
    player = &player_slots[slot];
    some_struct.internal_id =
        ftMapping_list[player->player_character].internal_id;
    some_struct.slot = slot;
    some_struct.has_transformation = 0;
    some_struct.unk8 = arg1;
    some_struct.b0 = 1;

    player->slot_type = Gm_PKind_Demo;
    player->player_entity[0] = ftDemo_CreateFighter(&some_struct);
    if ((ftMapping_list[player->player_character].extra_internal_id != -1) &&
        (ftMapping_list[player->player_character].has_transformation == 0))
    {
        some_struct.internal_id =
            ftMapping_list[player->player_character].extra_internal_id;
        some_struct.has_transformation = 1;
        player->player_entity[1] = ftDemo_CreateFighter(&some_struct);
    }
}
