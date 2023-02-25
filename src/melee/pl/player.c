#include <melee/pl/player.h>

#include <dolphin/os/os.h>
#include <melee/ft/chara/ftKirby/ftkirby.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftdata.h>
#include <melee/ft/ftlib.h>
#include <melee/gm/code_801601C4.h>
#include <melee/if/ifstatus.h>
#include <melee/lb/lbarchive.h>
#include <melee/pl/pl_unknown_001.h>
#include <sysdolphin/baselib/gobjplink.h>

typedef struct _ftMapping {
    s8 internal_id;
    s8 extra_internal_id;
    s8 has_transformation;
} ftMapping;

struct plAllocInfo {
    s32 internal_id;
    u8 slot;
    s8 unk8;
    struct {
        u8 b0 : 1;
        u8 has_transformation : 1;
        u8 b2 : 1;
        u8 b3 : 1;
        u8 b4 : 1;
        u8 b5 : 1;
        u8 b6 : 1;
        u8 b7 : 1;
    } bits;
};

/// @todo Probably the same struct as above, figure out how to make them work as
///       one.
struct plAllocInfo2 {
    s32 internal_id;
    u8 slot;
    s32 unk8;
    struct {
        u8 b0 : 1;
        u8 has_transformation : 1;
        u8 b2 : 1;
        u8 b3 : 1;
        u8 b4 : 1;
        u8 b5 : 1;
        u8 b6 : 1;
        u8 b7 : 1;
    } bits;
};

/// TODO delete after fixing functions that use this
struct Unk_Struct_w_Array {
    char some_str[8 + 4]; //"PdPm.dat"
    char another_str[16 + 4];
    S8Vec3 vec_arr[30]; /// ftMapping_list
};

//// .data
char str_PdPmdat_start_of_data[] = "PdPm.dat";
char str_plLoadCommonData[] = "plLoadCommonData";

ftMapping ftMapping_list[FTKIND_MAX] = { //////ftMapping_list
    { 0x02, 0xFF, 0x00 }, { 0x03, 0xFF, 0x00 }, { 0x01, 0xFF, 0x00 },
    { 0x18, 0xFF, 0x00 }, { 0x04, 0xFF, 0x00 }, { 0x05, 0xFF, 0x00 },
    { 0x06, 0xFF, 0x00 }, { 0x11, 0xFF, 0x00 }, { 0x00, 0xFF, 0x00 },
    { 0x12, 0xFF, 0x00 }, { 0x10, 0xFF, 0x00 }, { 0x08, 0xFF, 0x00 },
    { 0x09, 0xFF, 0x00 }, { 0x0C, 0xFF, 0x00 }, { 0x0A, 0x0B, 0x00 },
    { 0x0F, 0xFF, 0x00 }, { 0x0D, 0xFF, 0x00 }, { 0x0E, 0xFF, 0x00 },
    { 0x13, 0x07, 0x01 }, { 0x07, 0x13, 0x01 }, { 0x16, 0xFF, 0x00 },
    { 0x14, 0xFF, 0x00 }, { 0x15, 0xFF, 0x00 }, { 0x1A, 0xFF, 0x00 },
    { 0x17, 0xFF, 0x00 }, { 0x19, 0xFF, 0x00 }, { 0x1B, 0xFF, 0x00 },
    { 0x1D, 0xFF, 0x00 }, { 0x1E, 0xFF, 0x00 }, { 0x1F, 0xFF, 0x00 },
    { 0x1C, 0xFF, 0x00 }, { 0x20, 0xFF, 0x00 }, { 0x0A, 0xFF, 0x00 }
};

////.bss
StaticPlayer player_slots[PL_SLOT_MAX];
HSD_ObjAllocData lbl_804587E0;

extern int lbl_804D6470;

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

    if ((player->slot_type == 0) || (player->slot_type == 1)) {
        for (i = 0; i < 2; i++) {
            /// transformed will either be [1,0] (normal) or [0,1] (transformed)
            /// checks to see if the player is in a transformed state, and calls
            /// the function only once depending on the state
            if ((player->player_entity[player->transformed[i]])) {
                func_800867E8(player->player_entity[player->transformed[i]]);
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

    if ((player->slot_type == 0) || (player->slot_type == 1)) {
        for (i = 0; i < 2; i++) {
            /// transformed will either be [1,0] (normal) or [0,1] (transformed)
            /// checks to see if the player is in a transformed state, and calls
            /// the function only once depending on the state
            if ((player->player_entity[player->transformed[i]])) {
                func_8008688C(player->player_entity[player->transformed[i]]);
            }
        }
    }
}

static void func_8008688C_wrapper(StaticPlayer* player)
{
    if ((player->slot_type == 0) || (player->slot_type == 1)) {
        s32 i;
        for (i = 0; i < 2; i++) {
            if ((player->player_entity[player->transformed[i]])) {
                func_8008688C(player->player_entity[player->transformed[i]]);
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
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[4];
#endif

    int i;
    StaticPlayer* player;

    Player_CheckSlot(slot);
    player = (&player_slots[slot]);

    if (arg1) {
        for (i = 0; i < 2; i++)
            if (!player->player_entity[player->transformed[i]])
                return false;

        return true;
    }

    for (i = 0; i < 2; i++)
        if (player->player_entity[player->transformed[i]])
            return false;

    return true;
}

void Player_80031AD0(int slot)
{
    struct plAllocInfo first_struct;
    s32 internal_id;
    s32 has_transformation;
    s8 byte_check;
    s8* offset_arr;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused0[4];
#endif

    StaticPlayer* player;

    struct plAllocInfo second_struct;

#ifdef MUST_MATCH
    u8 unused1[12];
#endif

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    // the commented line below makes more sense, but is off by one byte.
    // temp_vec = unused_ptr = ftMapping_list;
    offset_arr = (s8*) (&ftMapping_list[0].extra_internal_id);

    if (offset_arr[player->player_character * sizeof(ftMapping)] != -1)
        player->flags.b2 = true;

    internal_id = ftMapping_list[player->player_character].internal_id;
    Player_CheckSlot(slot);

    first_struct.internal_id = internal_id;
    first_struct.slot = slot;
    first_struct.bits.b0 = false;
    first_struct.bits.has_transformation = false;
    first_struct.unk8 = -1;

    /// @todo Eliminate cast.
    player->player_entity[0] = Fighter_Create((struct S_TEMP1*) &first_struct);
    player->player_state = 2;

    internal_id = byte_check =
        offset_arr[player->player_character * sizeof(ftMapping)];

    if (byte_check != -1) {
        has_transformation =
            ftMapping_list[player->player_character].has_transformation;

        Player_CheckSlot(slot);

        second_struct.internal_id = internal_id;
        second_struct.slot = slot;
        second_struct.bits.b0 = true;
        second_struct.bits.has_transformation = has_transformation;
        second_struct.unk8 = -1;

        /// @todo Eliminate cast.
        player->player_entity[1] =
            Fighter_Create((struct S_TEMP1*) &second_struct);

        if (player->player_state != 1)
            player->player_state = 2;
    }

    if (player->player_state == 2)
        if (player->struct_func != NULL)
            player->struct_func(slot);
}

void Player_80031CB0(enum_t id, int slot)
{
    if (ftMapping_list[id].internal_id != -1)
        func_800855C8(ftMapping_list[id].internal_id, slot);

    if (hasExtraFighterId(&ftMapping_list[id]))
        func_800855C8(ftMapping_list[id].extra_internal_id, slot);
}

void Player_80031D2C(enum_t id, int slot)
{
    if (ftMapping_list[id].internal_id != -1)
        func_8008578C(ftMapping_list[id].internal_id, slot);

    if (hasExtraFighterId(&ftMapping_list[id]))
        func_8008578C(ftMapping_list[id].extra_internal_id, slot);
}

void Player_80031DA8(s32 param_1, s32 param_2)
{
    func_800EED50(param_1, param_2);
}

void Player_80031DC8(void func_arg(s32, s32))
{
    int slot;
    for (slot = 0; slot < 6; slot++) {
        Player_CheckSlot(slot);

        if (player_slots[slot].player_state) {
            func_arg(
                ftMapping_list[player_slots[slot].player_character].internal_id,
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
            if (!func_8008701C(player->player_entity[player->transformed[i]])) {
                func_800D4F24(player->player_entity[player->transformed[i]], 1);
            }
            func_80390228(player->player_entity[player->transformed[i]]);
        }
    }
}

void Player_80031FB0(int slot, s32 entity_index)
{
/// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[4];
#endif

    StaticPlayer* player;
    Player_CheckSlot(slot);

    player = &player_slots[slot];
    player->player_entity[player->transformed[entity_index]] = NULL;

    if (player->flags.b2 == false || Player_800319C4(slot, 0))
        player->player_state = 0;
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
        func_800D4FF4(player->player_entity[player->transformed[0]]);

        if (player->flags.b2 &&
            unkStruct->vec_arr[player->player_character].z == 0 &&
            func_8008701C(player->player_entity[player->transformed[1]]))
        {
            func_800D4FF4(player->player_entity[player->transformed[1]]);
        }

        func_802F6E1C(slot);
        return;
    }

    if (func_800873CC(player->player_entity[player->transformed[0]]))
        func_800D4FF4(player->player_entity[player->transformed[1]]);
}

void Player_8003219C(int slot)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    func_8008701C(player->player_entity[player->transformed[0]]);
}

bool Player_8003221C(int slot)
{
    StaticPlayer* player;

    if (Player_GetPlayerState(slot) == 2) {
        Player_CheckSlot(slot);
        player = &player_slots[slot];

        if (!func_8008701C(player->player_entity[player->transformed[0]]))
            return true;
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

enum_t Player_GetPlayerCharacter(int slot)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[4];
#endif

    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    return player->player_character;
}

void Player_SetPlayerCharacter(s32 slot, s32 value)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->player_character = value;
}

s32 Player_GetPlayerSlotType(s32 slot)
{
    s32 slot_type;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    slot_type = player->slot_type;
    return slot_type;
}

s32 Player_8003248C(s32 slot, bool arg1)
{ /// decomp.me/scratch/3yC1W

    s32 slot_type;
    struct Unk_Struct_w_Array* unk_struct =
        (struct Unk_Struct_w_Array*) &str_PdPmdat_start_of_data;
    StaticPlayer* player;

    Player_CheckSlot(slot);

    player = &player_slots[slot];

    if (arg1 == 1) {
        if (unk_struct->vec_arr[player->player_character].z == 0) {
            if (player->slot_type == 0 || player->slot_type == 1) {
                return 1;
            }
        }
    }
    slot_type = player->slot_type;

    return slot_type;
}

void Player_SetSlottype(s32 slot, s32 value)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->slot_type = value;
}

s8 Player_800325C8(s32 slot, bool b)
{
    if (!b) {
        return ftMapping_list[slot].internal_id;
    } else if (b == 1) {
        return ftMapping_list[slot].extra_internal_id;
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

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[4];
#endif

    Player_CheckSlot(slot);
    player = &player_slots[slot];
    Player_CheckSlot(slot);

    player_vecs = player->player_poses.byIndex;
    dst_vec = &player_vecs[player->transformed[0]];
    *dst_vec = *arg_vec;

    player_vecs2 = player->player_poses.byIndex;
    dst_vec2 = &player_vecs2[player->transformed[1]];
    *dst_vec2 = *arg_vec;

    for (i = 0; i < 2; i++)
        if (player->player_entity[player->transformed[i]])
            func_80087140(player->player_entity[player->transformed[i]]);
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
            func_80086664(player->player_entity[player->transformed[i]],
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

        if (player->player_entity[player->transformed[i]])
            func_SetEntityFacingDirection(
                player->player_entity[player->transformed[i]], facing_dir);
    }
}

f32 Player_80032BB0(s32 slot)
{
    StaticPlayer* player;
    f32 temp;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    temp = func_800869F8(player->player_entity[player->transformed[0]]);
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
            ftData_SetScale(player->player_entity[player->transformed[i]],
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

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[4];
#endif

    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->unk4E = arg;
}

f32 Player_GetFacingDirection(s32 slot)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[4];
#endif
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
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[4];
#endif

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

void Player_SetCostumeId(int slot, s8 costume_id)
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

s8 Player_GetTeam(int slot)
{
    s8 team;
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

s8 Player_GetPlayerId(int slot)
{
    s8 player_id;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player_id = player->player_id;
    return player_id;
}

void Player_SetPlayerId(int slot, s8 player_id)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->player_id = player_id;
}

s8 Player_GetCpuLevel(int slot)
{
    s8 cpu_level;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    cpu_level = player->cpu_level;
    return cpu_level;
}

void Player_SetPlayerAndEntityCpuLevel(int slot, s8 cpu_level)
{
    StaticPlayer* player;
    int i;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->cpu_level = cpu_level;

    for (i = 0; i < 2; i++) {
        if (player->player_entity[player->transformed[i]]) {
            func_80087BEC(player->player_entity[player->transformed[i]],
                          cpu_level);
        }
    }
}

s8 Player_GetCpuType(int slot)
{
    s8 cpu_type;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    cpu_type = player->cpu_type;
    return cpu_type;
}

void Player_SetPlayerAndEntityCpuType(int slot, s8 cpu_type)
{
    StaticPlayer* player;
    int i;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->cpu_type = cpu_type;

    for (i = 0; i < 2; i++) {
        if (player->player_entity[player->transformed[i]]) {
            func_80087BC0(player->player_entity[player->transformed[i]],
                          cpu_type);
        }
    }
}

s8 Player_GetHandicap(int slot)
{
    s8 handicap;
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
    return func_8016C5C0(slot);
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

    if (player->stocks > 0)
        player->stocks = player->stocks - 1;
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

HSD_GObj* Player_GetEntityAtIndex(s32 slot, s32 index)
{ //   Mostly called by Ice Climbers code, must be because they have 2nd entity
    StaticPlayer* player;
    s32 entity_index;
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
            func_800870F0(player->player_entity[player->transformed[i]], arg1);
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

s16 Player_GetOtherStamina(s32 slot)
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

u32 Player_GetRemainingHP(s32 slot)
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

u8 Player_GetMoreFlagsBit2(s32 slot)
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

s32 Player_GetMoreFlagsBit3(s32 slot)
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

s32 Player_GetMoreFlagsBit4(s32 slot)
{
    StaticPlayer* player;
    u8 bit4;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    bit4 = player->more_flags.b4;
    return bit4;
}

u8 Player_GetMoreFlagsBit5(s32 slot)
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

u8 Player_GetMoreFlagsBit6(s32 slot)
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

u32 Player_GetRemainingHPByIndex(s32 slot, s32 index)
{
    StaticPlayer* player;
    u32 stamina;
    s32 result;
    u32 result2;
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
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[4];
#endif

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

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[16];
#endif

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    if (!bool_arg) {
        uint kos = player->kos_by_player[other_slot];

        if (kos < U32_MAX)
            player->kos_by_player[other_slot]++;

        if (slot == other_slot) {
            func_802F6D10(other_slot);
        } else {
            if (func_8016B168()) {
                Player_CheckSlot(slot);
                Player_CheckSlot(other_slot);
                other_player = &player_slots[other_slot];

                {
                    int player_team;
                    int other_player_team;
                    player_team = player->team;
                    other_player_team = other_player->team;
                    if (player_team == other_player_team) {
                        func_802F69C0(other_slot, slot);
                        return;
                    }
                }
            }

            func_802F6AF8(other_slot);
        }
    }
}

uint Player_GetMatchFrameCount(int slot)
{
    StaticPlayer* player;
    uint count;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    count = player->match_frame_count;
    return count;
}

void Player_UpdateMatchFrameCount(int slot, bool condition)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[4];
#endif

    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];

    if ((condition == 0) && (player->match_frame_count + 0x10000) == 0xffff)
        player->match_frame_count = func_8016AEDC();
}

uint Player_GetSuicideCount(int slot)
{
    StaticPlayer* player;
    uint count;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    count = player->suicide_count;
    return count;
}

void Player_SetSuicideCount(s32 slot, u32 suicide_count)
{
    StaticPlayer* player;

    if (suicide_count > 0xffff || 0 > (s32) suicide_count)
        return;

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
            func_802F6C04(slot);
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
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[4];
#endif

    if (!condition) {
        StaticPlayer* player;

        Player_CheckSlot(slot);
        player = &player_slots[slot];

        if (player->player_state == 2 && player->flags.b0)
            return true;
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
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[1];
#endif

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

u8 Player_GetFlagsBit4(s32 slot)
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
    u8 bit5;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    bit5 = player->flags.b5;
    return bit5;
}

void Player_SetFlagsBit5(s32 slot, u8 bit5)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->flags.b5 = bit5;
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

u8 Player_GetMoreFlagsBit0(s32 slot)
{
    StaticPlayer* player;
    u8 bit0;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    bit0 = player->more_flags.b0;
    return bit0;
}

u8 Player_GetMoreFlagsBit1(s32 slot)
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

/// @remarks Output is actually @c void, but needs #u8 to match. Most likely a
/// typo by HAL.
u8 Player_SetFlagsAEBit1(s32 slot, u8 bit1)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player_slots[slot].flagsAE.b1 = bit1;
}

u8 Player_GetUnk4C(s32 slot)
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

void Player_80036058(s32 slot)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    func_80086F4C(player->player_entity[player->transformed[0]]);
}

void Player_800360D8(s32 slot)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    func_80086F80(player->player_entity[player->transformed[0]]);
}

void Player_SetStructFunc(s32 slot, void* arg_func)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->struct_func = arg_func;
}

s32* Player_GetTotalAttackCountPtr(s32 slot)
{
    StaticPlayer* player;
    s32* attack_count;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    attack_count = &player->total_attack_count;
    return attack_count;
}

s32* Player_GetStaleMoveTableIndexPtr(s32 slot)
{
    StaticPlayer* player;
    s32* stale_move_table_index;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    stale_move_table_index = &player->stale_move_table_current_write_index;
    return stale_move_table_index;
}

s32* Player_GetUnk6A8Ptr(s32 slot)
{
    StaticPlayer* player;
    s32* unk6A8;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    unk6A8 = &player->unk6A8;
    return unk6A8;
}

s32* Player_GetStaleMoveTableIndexPtr2(s32 slot)
{
    StaticPlayer* player;
    s32* stale_move_table_index;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    stale_move_table_index = &player->stale_move_table_current_write_index;
    return stale_move_table_index;
}

s32 Player_80036394(s32 slot)
{
    StaticPlayer* player;
    HSD_GObj* entity;
    Player_CheckSlot(slot);
    player = &player_slots[slot];

    entity = player->player_entity[player->transformed[0]];

    if (entity) {
        return func_800872A4(entity);
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
        return func_80087300(entity);
    }
    return 6;
}

void Player_SetUnk45(s32 slot, s8 unk45)
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
    if (player->slot_type == 0) {
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
            func_80087AC0(player->player_entity[player->transformed[i]], arg1);
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
            func_80086A4C(player->player_entity[player->transformed[i]], arg1);
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
            func_80087BAC(player->player_entity[player->transformed[i]], arg1);
        }
    }
}

void Player_800368F8(s32 slot)
{
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    func_80086BB4(player->player_entity[player->transformed[0]]);
}

void Player_80036978(s32 slot, s32 arg1)
{
    StaticPlayer* player;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[4];
#endif

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    /// @todo Eliminate cast.
    func_80086B90(player->player_entity[player->transformed[0]], (Vec3*) arg1);
}

void Player_InitOrResetPlayer(s32 slot)
{
    StaticPlayer* player;
    u8* transformed0;
    u8* transformed1;
    f32 zerofloat;
    f32 onefloat;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[56];
#endif

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
    player->slot_type = 3;
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
    player->flags.b5 = 0;
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
    func_8003891C(slot);
}

void Player_80036D24(s32 slot)
{
    Player_InitOrResetPlayer(slot);
    func_80038F10(slot);
}

void Player_InitAllPlayers(void)
{
    int i;
    func_8003715C();
    func_80037590();

    for (i = 0; i < PL_SLOT_MAX; i++) {
        Player_InitOrResetPlayer(i);
        func_8003891C(i);
    }
}

void Player_80036DA4(void)
{
    HSD_ObjAllocInit(&lbl_804587E0, 8, 4);
    Fighter_FirstInitialize_80067A84();
}

void Player_80036DD8(void)
{
    int* sp8;

    func_80016C64(str_PdPmdat_start_of_data, &sp8, str_plLoadCommonData, 0);
    lbl_804D6470 = *sp8;
}

void Player_80036E20(s32 arg0, s32 arg1, s32 arg2)
{
    struct Unk_Struct_w_Array* unkStruct =
        (struct Unk_Struct_w_Array*) &str_PdPmdat_start_of_data;
    func_800BEB60(unkStruct->vec_arr[arg0].x, arg1, arg2);
    if ((unkStruct->vec_arr[arg0].y != -1) && (unkStruct->vec_arr[arg0].z == 0))
    {
        func_800BEB60(unkStruct->vec_arr[arg0].y, arg1, arg2);
    }
}

s32 Player_80036EA0(s32 slot)
{
    StaticPlayer* player;
    HSD_GObj* entity;
    Player_CheckSlot(slot);
    player = &player_slots[slot];

    entity = player->player_entity[player->transformed[0]];

    if (entity)
        /// @todo Eliminate cast.
        return (s32) func_800865F0(entity);

    return 0;
}

void Player_80036F34(s32 slot, s32 arg1)
{
    struct plAllocInfo2 some_struct;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused;
#endif

    StaticPlayer* player;

    Player_CheckSlot(slot);
    player = &player_slots[slot];
    some_struct.internal_id =
        ftMapping_list[player->player_character].internal_id;
    some_struct.slot = slot;
    some_struct.bits.has_transformation = 0;
    some_struct.unk8 = arg1;
    some_struct.bits.b0 = 0;

    player->slot_type = 2;
    player->player_entity[0] = func_800BE7E0(&some_struct);
    if ((ftMapping_list[player->player_character].extra_internal_id != -1) &&
        (ftMapping_list[player->player_character].has_transformation == 0))
    {
        some_struct.internal_id =
            ftMapping_list[player->player_character].extra_internal_id;
        some_struct.bits.has_transformation = 1;
        player->player_entity[1] = func_800BE7E0(&some_struct);
    }
}

void Player_80037054(s32 slot, s32 arg1)
{
    struct plAllocInfo2 some_struct;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused;
#endif

    StaticPlayer* player;

    Player_CheckSlot(slot);
    player = &player_slots[slot];
    some_struct.internal_id =
        ftMapping_list[player->player_character].internal_id;
    some_struct.slot = slot;
    some_struct.bits.has_transformation = 0;
    some_struct.unk8 = arg1;
    some_struct.bits.b0 = 1;

    player->slot_type = 2;
    player->player_entity[0] = func_800BE7E0(&some_struct);
    if ((ftMapping_list[player->player_character].extra_internal_id != -1) &&
        (ftMapping_list[player->player_character].has_transformation == 0))
    {
        some_struct.internal_id =
            ftMapping_list[player->player_character].extra_internal_id;
        some_struct.bits.has_transformation = 1;
        player->player_entity[1] = func_800BE7E0(&some_struct);
    }
}
