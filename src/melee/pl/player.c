#include "melee/pl/player.h"

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

/// TODO probably the same struct as above, figure out how to make them work as one
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
    char some_str[8+4];  //"PdPm.dat"
    char another_str[16+4]; 
    S8Vec vec_arr[30];  ///ftMapping_list
};


//// .data
char str_PdPmdat_start_of_data[] = "PdPm.dat"; 
char str_plLoadCommonData[] = "plLoadCommonData"; 
ftMapping ftMapping_list[33] = {   //////ftMapping_list
    { 0x02, 0xFF, 0x00 },
    { 0x03, 0xFF, 0x00 },
    { 0x01, 0xFF, 0x00 },
    { 0x18, 0xFF, 0x00 },
    { 0x04, 0xFF, 0x00 },
    { 0x05, 0xFF, 0x00 },
    { 0x06, 0xFF, 0x00 },
    { 0x11, 0xFF, 0x00 },
    { 0x00, 0xFF, 0x00 },
    { 0x12, 0xFF, 0x00 },
    { 0x10, 0xFF, 0x00 },
    { 0x08, 0xFF, 0x00 },
    { 0x09, 0xFF, 0x00 },
    { 0x0C, 0xFF, 0x00 },
    { 0x0A, 0x0B, 0x00 },
    { 0x0F, 0xFF, 0x00 },
    { 0x0D, 0xFF, 0x00 },
    { 0x0E, 0xFF, 0x00 },
    { 0x13, 0x07, 0x01 },
    { 0x07, 0x13, 0x01 },
    { 0x16, 0xFF, 0x00 },
    { 0x14, 0xFF, 0x00 },
    { 0x15, 0xFF, 0x00 },
    { 0x1A, 0xFF, 0x00 },
    { 0x17, 0xFF, 0x00 },
    { 0x19, 0xFF, 0x00 },
    { 0x1B, 0xFF, 0x00 },
    { 0x1D, 0xFF, 0x00 },
    { 0x1E, 0xFF, 0x00 },
    { 0x1F, 0xFF, 0x00 },
    { 0x1C, 0xFF, 0x00 },
    { 0x20, 0xFF, 0x00 },
    { 0x0A, 0xFF, 0x00 }
};


////.bss
StaticPlayer player_slots[6]; 
HSD_ObjAllocData lbl_804587E0;

extern s32 lbl_804D6470;

extern void ftData_SetScale();
extern void func_SetEntityFacingDirection();
extern void func_80087140();
extern void func_80086664();
extern s32 func_8008701C(HSD_GObj*);
extern s32 func_800873CC();
extern s32 func_8016C5C0(s32);
extern void func_802F6E1C(s32);
extern void func_800D4FF4(HSD_GObj*);
extern f32 func_800869F8(HSD_GObj*);
extern void func_80087BEC(HSD_GObj*, s8);
extern void func_80087BC0(HSD_GObj*, s8);
extern void func_800870F0(HSD_GObj*, s32);
extern void func_802F6D10(s32);
extern void func_802F6AF8(s32);
extern void func_802F69C0(s32, s32);
extern void func_802F6C04(s32);
extern s32 func_8016B168();
extern BOOL func_80086F4C(HSD_GObj*);
extern double func_80086F80(HSD_GObj*);
extern s32 func_800872A4(HSD_GObj*);
extern s32 func_80087300(HSD_GObj*);
extern void func_80087AC0(HSD_GObj*, s32);
extern void func_80086A4C(HSD_GObj*, f32);
extern void func_80087BAC(HSD_GObj*, s32);
extern void func_80086BB4(HSD_GObj*);
extern void func_80086B90(HSD_GObj*, s32);
extern void func_8003891C(s32);
extern void func_80038F10(s32);
extern void func_8003715C();
extern void func_80037590();
extern void Fighter_FirstInitialize_80067A84();
extern void func_800BEB60(s32, s32, s32);
extern s32 func_800865F0(HSD_GObj*);
extern HSD_GObj* func_800BE7E0(struct plAllocInfo2*);
extern HSD_GObj* Fighter_80068E98(struct plAllocInfo*);

inline hasExtraFighterID(ftMapping* data) { return data->extra_internal_id != -1; } ///TODO this can be used in more places when functions are fixed to use correct structs

void inline Player_CheckSlot(s32 slot)
{
    if (slot < 0 || 6 <= slot) {
        OSReport("cant get player struct! %d\n", slot);
        __assert(__FILE__, 102, "0");
    }
}

// Matches when everything is moved over
StaticPlayer* Player_GetPtrForSlot(s32 slot)  
{
    Player_CheckSlot(slot);
    return &player_slots[slot];
}

void Player_80031790(s32 slot) {  

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

void Player_80031848(s32 slot) { 
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

void inline func_8008688C_wrapper(StaticPlayer* player)   
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

void Player_80031900() { 
    s32 slot;
    for (slot = 0; slot < 6; slot++) {
        StaticPlayer* player = &player_slots[slot];
        Player_CheckSlot(slot);
        func_8008688C_wrapper(player);
    }
}

BOOL Player_800319C4(s32 slot, BOOL arg1) {  

    s32 unused;

    s32 i;
    StaticPlayer* player;

    Player_CheckSlot(slot);
    player = (&player_slots[slot]);


    if (arg1) {
        for (i = 0; i < 2; i++) {
            if (!player->player_entity[player->transformed[i]]) {
                return FALSE;
            }
        }
        return TRUE;
    }

    for (i = 0; i < 2; i++) {
        if (player->player_entity[player->transformed[i]]) {
            return FALSE;
        } 
    }
    
    return TRUE;

}

void Player_80031AD0(s32 slot) {  ///decomp.me/scratch/lYkLv

    struct plAllocInfo first_struct;
    s32 internal_id;
    s32 has_transformation;
    s8 byte_check;
    s8* offset_arr;
    s32 unused;
    StaticPlayer* player;

    struct plAllocInfo second_struct;

    s32 unused_buffer[3]; 


    Player_CheckSlot(slot);
    player = &player_slots[slot];

    /// the commented line below makes more sense, but is off by one byte.
    //  temp_vec = unused_ptr = ftMapping_list;    //// replace
    offset_arr = (s8*) (&ftMapping_list[0].extra_internal_id);
    if (offset_arr[player->player_character * sizeof(ftMapping)] != -1) {
        player->flags.b2 = 1;
    }

    internal_id = ftMapping_list[player->player_character].internal_id;
    Player_CheckSlot(slot);

    first_struct.internal_id = internal_id;
    first_struct.slot = slot;
    first_struct.bits.b0 = 0; 
    first_struct.bits.has_transformation = 0;  
    first_struct.unk8 = -1;

    player->player_entity[0] = Fighter_80068E98(&first_struct);
    player->player_state = 2;

    internal_id = byte_check = offset_arr[player->player_character * sizeof(ftMapping)];
    if (byte_check != -1) {
        has_transformation = ftMapping_list[player->player_character].has_transformation;
        Player_CheckSlot(slot);
        second_struct.internal_id = internal_id;
        second_struct.slot = slot;
        second_struct.bits.b0 = 1;  
        second_struct.bits.has_transformation = has_transformation; 
        second_struct.unk8 = -1;

        player->player_entity[1] = Fighter_80068E98(&second_struct);
        if (player->player_state != 1) {
            player->player_state = 2;
        }
    }
    if (player->player_state == 2) {
        if (player->struct_func != 0) {
            player->struct_func(slot);
        }
    }
}

void Player_80031CB0(s32 id, s32 slot) { 
    if (ftMapping_list[id].internal_id != -1) {
        func_800855C8(ftMapping_list[id].internal_id, slot);
    }
    if (hasExtraFighterID(&ftMapping_list[id])) {
        func_800855C8(ftMapping_list[id].extra_internal_id, slot);
    }
}


void Player_80031D2C(s32 id, s32 slot) {   
    if (ftMapping_list[id].internal_id != -1) {
        func_8008578C(ftMapping_list[id].internal_id, slot);
    }
    if (hasExtraFighterID(&ftMapping_list[id])) {
        func_8008578C(ftMapping_list[id].extra_internal_id, slot);
    }
}

void Player_80031DA8(s32 param_1, s32 param_2)
{
    func_800EED50(param_1, param_2);
}

void Player_80031DC8(void func_arg(s32, s32)) {  

    s32 slot;
    for (slot = 0; slot < 6; slot++) {
        Player_CheckSlot(slot);

        if (player_slots[slot].player_state) {
            func_arg(ftMapping_list[player_slots[slot].player_character].internal_id, 0);
            if (hasExtraFighterID(&ftMapping_list[player_slots[slot].player_character])) {
                func_arg(ftMapping_list[player_slots[slot].player_character].extra_internal_id, 0);
            }
        }
    }
}

void Player_80031EBC(s32 slot) { 

    s32 i;
    Player_CheckSlot(slot);

    for (i = 0; i < 2; i++) {
        StaticPlayer*player = &player_slots[slot];
        if ((player->player_entity[player->transformed[i]])) {
            if (!func_8008701C(player->player_entity[player->transformed[i]])) {
                func_800D4F24(player->player_entity[player->transformed[i]], 1);
            }
            func_80390228(player->player_entity[player->transformed[i]]);
        }
    }

}

void Player_80031FB0(s32 slot, s32 entity_index) { 
    s32 unused;
    StaticPlayer* player;
    Player_CheckSlot(slot);

    player = &player_slots[slot];
    player->player_entity[player->transformed[entity_index]] = 0;
    if (((player->flags.b2 == 0) || Player_800319C4(slot, 0) != 0)) {
        player->player_state = 0;
    }
}

/// new match decomp.me/scratch/oHfiV  TODO
//// old match decomp.me/scratch/8otnq
void Player_80032070(s32 slot, BOOL bool_arg) {   
    StaticPlayer* player;
    struct Unk_Struct_w_Array* unkStruct = (struct Unk_Struct_w_Array*) &str_PdPmdat_start_of_data;
    Player_CheckSlot(slot);
    player = &player_slots[slot];

    
    if (bool_arg == 0) {
        func_800D4FF4(player->player_entity[player->transformed[0]]);
        if((player->flags.b2) 
                && unkStruct->vec_arr[player->player_character].z == 0 
                && func_8008701C(player->player_entity[player->transformed[1]])) 
        {
            func_800D4FF4(player->player_entity[player->transformed[1]]);
        }
        func_802F6E1C(slot);
        return;
    }

    if (func_800873CC(player->player_entity[player->transformed[0]])) {
        func_800D4FF4(player->player_entity[player->transformed[1]]);
    }
}


void Player_8003219C(s32 slot) {  
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    func_8008701C(player->player_entity[player->transformed[0]]);
}

BOOL Player_8003221C(s32 slot) {   

    StaticPlayer* player;

    if (Player_GetPlayerState(slot) == 2) {   ///2 means in-game
        Player_CheckSlot(slot);
        player = &player_slots[slot];

        if (!func_8008701C(player->player_entity[player->transformed[0]])) {
            return 1;
        }

    }

    return 0;
}


s32 Player_GetPlayerState(s32 slot) { 
    s32 state;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    state = player->player_state;
    return state;
}

s32 Player_GetPlayerCharacter(s32 slot) {  
    s32 unused;
    StaticPlayer* player; 
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    return player->player_character;
}

void Player_SetPlayerCharacter(s32 slot, s32 value) {  
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->player_character = value;
}

s32 Player_GetPlayerSlotType(s32 slot) { 
    s32 slot_type;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    slot_type = player->slot_type;
    return slot_type;
}

s32 Player_8003248C(s32 slot, BOOL arg1) {   /// decomp.me/scratch/3yC1W
    
    s32 slot_type;
    struct Unk_Struct_w_Array* unk_struct = (struct Unk_Struct_w_Array*) &str_PdPmdat_start_of_data;
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

void Player_SetSlottype(s32 slot, s32 value) { 
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->slot_type = value;
}

s8 Player_800325C8(s32 slot, BOOL b) { 
    
    
    if (!b) {
        return ftMapping_list[slot].internal_id;
    }
    else if (b == 1) {
        return ftMapping_list[slot].extra_internal_id;
    }

    return -1;
}

s8 Player_80032610(s32 slot, BOOL arg1) {  //// decomp.me/scratch/pHTx2

    struct Unk_Struct_w_Array* some_struct = (struct Unk_Struct_w_Array*) &str_PdPmdat_start_of_data;
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

void Player_LoadPlayerCoords(s32 slot, Vec* arg_vec) {
    StaticPlayer* player;
    Vec* player_vecs;

    Player_CheckSlot(slot);

    player = &player_slots[slot];
    player_vecs = player->player_poses.byIndex;
    *arg_vec = player_vecs[player->transformed[0]];
}


void Player_80032768(s32 slot, Vec* arg_vec) { 
    StaticPlayer* player;
    Vec* player_vecs;

    Vec* dst_vec;
    Vec* dst_vec2;

    Player_CheckSlot(slot);

    player = &player_slots[slot];

    player_vecs = player->player_poses.byIndex;
    dst_vec = &player_vecs[player->transformed[0]];
    *dst_vec = *arg_vec;

    player_vecs = player->player_poses.byIndex;
    dst_vec2 = &player_vecs[player->transformed[1]];
    *dst_vec2 = *arg_vec;
}

void Player_80032828(s32 slot, s32 index, Vec* arg_vec) {  
    StaticPlayer* player;
    Vec* player_vecs;

    Player_CheckSlot(slot);

    player = &player_slots[slot];

    player_vecs = player->player_poses.byIndex;
    player_vecs[player->transformed[index]] = *arg_vec;

}

void Player_800328D4(s32 slot, Vec* arg_vec) {  
    StaticPlayer* player;
    s32 i;
    Vec* player_vecs;
    Vec* player_vecs2;

    Vec* dst_vec;
    Vec* dst_vec2;

    Vec* unused;

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
            func_80087140(player->player_entity[player->transformed[i]]);
        }
    }
}

void Player_80032A04(s32 slot, Vec* arg_vec) {  
    StaticPlayer* player;
    s32 i;

    Player_CheckSlot(slot);

    for (i = 0; i < 2; i++) {
        player = &player_slots[slot];

        player->player_poses.byIndex[player->transformed[i]] = *arg_vec;
                
        if (player->player_entity[player->transformed[i]]) {
            func_80086664(player->player_entity[player->transformed[i]], arg_vec);
        }
    }
}

void Player_SetPlayerAndEntityFacingDirection(s32 slot, f32 direction) {  
    StaticPlayer* player;
    s32 i;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    for (i = 0; i < 2; i++) {
        player->facing_direction = direction;
        if (player->player_entity[player->transformed[i]]) {
            func_SetEntityFacingDirection(direction, player->player_entity[player->transformed[i]]);
        }
    }
}

f32 Player_80032BB0(s32 slot) {   
    StaticPlayer* player;
    f32 temp;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    temp = func_800869F8(player->player_entity[player->transformed[0]]);
    return temp / player->model_scale;

}


void Player_SetScale(s32 slot, f32 scale) {  
    StaticPlayer* player;
    s32 i;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->model_scale = scale;
    for (i = 0; i < 2; i++) {
        if (player->player_entity[player->transformed[i]]) {
            ftData_SetScale(scale, player->player_entity[player->transformed[i]]);
        }
    }

}

void Player_GetSpawnPlatformPos(s32 slot, Vec* arg_vec) { 
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    *arg_vec = player->player_poses.byVecName.spawn_platform_final_pos;
}

void Player_SetSpawnPlatformPos(s32 slot, Vec* arg_vec) {  
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->player_poses.byVecName.spawn_platform_final_pos = *arg_vec;
}

void Player_GetSomePos(s32 slot, Vec* arg_vec) {  
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    *arg_vec = player->player_poses.byVecName.some_other_player_pos;
}

void Player_SetSomePos(s32 slot, Vec* arg_vec) {  
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->player_poses.byVecName.some_other_player_pos = *arg_vec;
}

s32 Player_80032F30(s32 slot) { 
    StaticPlayer* player;
    s32 value;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    value = player->unk4E;
    return value;
}


void Player_80032FA4(s32 slot, s32 arg) {  
    StaticPlayer* player;
    s32 value;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->unk4E = arg;
}


f32 Player_GetFacingDirection(s32 slot) {  
    StaticPlayer* player;
    s32 value;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    return player->facing_direction;
}

void Player_SetFacingDirection(s32 slot, f32 direction) {  
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->facing_direction = direction;
}

void Player_SetFacingDirectionConditional(s32 slot, BOOL b, f32 direction) { 
    StaticPlayer* player;
    s32 unused;
    if (!b) {
        Player_CheckSlot(slot);
        player = &player_slots[slot];
        player->facing_direction = direction;
    }
}

u32 Player_GetCostumeId(s32 slot) {   
    u8 costume_id;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    costume_id = player->costume_id;
    return costume_id;
}

void Player_SetCostumeId(s32 slot, s8 costume_id) { 
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->costume_id = costume_id;
}

u8 Player_GetControllerIndex(s32 slot) {   
    s8 controller_index;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    controller_index = player->controller_index;
    return controller_index;
}

void Player_SetControllerIndex(s32 slot, s8 controller_index) {    
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->controller_index = controller_index;
}

s8 Player_GetTeam(s32 slot) {  
    s8 team;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    team = player->team;
    return team;
}

void Player_SetTeam(s32 slot, s8 team) {  
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->team = team;
}


s8 Player_GetPlayerId(s32 slot) {  
    s8 player_id;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player_id = player->player_id;
    return player_id;
}

void Player_SetPlayerId(s32 slot, s8 player_id) {
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->player_id = player_id;
}


s8 Player_GetCpuLevel(s32 slot) {  
    s8 cpu_level;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    cpu_level = player->cpu_level;
    return cpu_level;
}


void Player_SetPlayerAndEntityCpuLevel(s32 slot, s8 cpu_level) {   
    StaticPlayer* player;
    s32 i;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->cpu_level = cpu_level;
    for (i = 0; i < 2; i++){
        if (player->player_entity[player->transformed[i]]) {
            func_80087BEC(player->player_entity[player->transformed[i]], cpu_level);
        }
    }
}

s8 Player_GetCpuType(s32 slot) {  
    s8 cpu_type;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    cpu_type = player->cpu_type;
    return cpu_type;
}


void Player_SetPlayerAndEntityCpuType(s32 slot, s8 cpu_type) { 
    StaticPlayer* player;
    s32 i;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->cpu_type = cpu_type;
    for (i = 0; i < 2; i++){
        if (player->player_entity[player->transformed[i]]) {
            func_80087BC0(player->player_entity[player->transformed[i]], cpu_type);
        }
    }
}

s8 Player_GetHandicap(s32 slot) {  
    s8 handicap;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    handicap = player->handicap;
    return handicap;
}

void Player_SetHandicap(s32 slot, s8 handicap) { 
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->handicap = handicap;
}

f32 Player_GetUnk50(s32 slot) {  
    f32 unk50;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    unk50 = player->unk50;
    return unk50;
}

f32 Player_GetAttackRatio(s32 slot) {  
    f32 attack_ratio;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    attack_ratio = player->attack_ratio;
    return attack_ratio;
}

void Player_SetAttackRatio(s32 slot, f32 attack_ratio) {  
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->attack_ratio = attack_ratio;
}

f32 Player_GetDefenseRatio(s32 slot) {   
    f32 defense_ratio;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    defense_ratio = player->defense_ratio;
    return defense_ratio;
}

void Player_SetDefenseRatio(s32 slot, f32 defense_ratio) {  
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->defense_ratio = defense_ratio;
}

f32 Player_GetModelScale(s32 slot) { 
    f32 model_scale;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    model_scale = player->model_scale;
    return model_scale;
}

void Player_SetModelScale(s32 slot, f32 model_scale) {   
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->model_scale = model_scale;
}

s32 Player_80033BB8(s32 slot) {  
    return func_8016C5C0(slot);
}

s32 Player_GetStocks(s32 slot) { 
    s8 stocks;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    stocks = player->stocks;
    return stocks;
}


s32 Player_GetP1Stock() {  
    return player_slots[0].stocks;
}


void Player_SetStocks(s32 slot, s32 stocks) {  
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->stocks = stocks;
}

void Player_LoseStock(s32 slot) {   
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    if (player->stocks > 0){
        player->stocks = player->stocks - 1;
    }
}

s32 Player_GetCoins(s32 slot) {  
    s32 current_coins;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    current_coins = player->current_coins;
    return current_coins;
}

void Player_SetCoins(s32 slot, s32 current_coins) {   
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->current_coins = current_coins;
}

s32 Player_GetTotalCoins(s32 slot) {  
    s32 total_coins;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    total_coins = player->total_coins;
    return total_coins;
}

void Player_SetTotalCoins(s32 slot, s32 coins) {  
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->total_coins = coins;
}

s32 Player_GetUnk98(s32 slot) {
    s32 unk98;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    unk98 = player->unk98;
    return unk98;
}

void Player_SetUnk98(s32 slot, s32 unk98) { 
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->unk98 = unk98;
}

s32 Player_GetUnk9C(s32 slot) {   
    s32 unk9C;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    unk9C = player->unk9C;
    return unk9C;
}

void Player_SetUnk9C(s32 slot, s32 unk9C) { 
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->unk9C = unk9C;
}

HSD_GObj* Player_GetEntity(s32 slot) {  
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    return player->player_entity[player->transformed[0]];
}

HSD_GObj* Player_GetEntityAtIndex(s32 slot, s32 index) {  //   Mostly called by Ice Climbers code, must be because they have 2nd entity
    StaticPlayer* player;
    s32 entity_index;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    entity_index = player->transformed[index];
    return player->player_entity[entity_index];
}

void Player_SwapTransformedStates(s32 slot, s32 arg1, s32 arg2) {  
    u8 temp_r5;
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];

    temp_r5 = player->transformed[arg1];
    player->transformed[arg1] = player->transformed[arg2];
    player->transformed[arg2] = temp_r5;
}

s32 Player_GetDamage(s32 slot) {   
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    return player->staminas.byIndex[player->transformed[0]];
}

void Player_SetHUDDamage(s32 slot,s32 arg1) {  
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

void Player_SetHPByIndex(s32 slot, s32 arg1, s32 arg2) {  
    StaticPlayer* player;
    Player_CheckSlot(slot);

    player = &player_slots[slot];
    player->staminas.byIndex[player->transformed[arg1]] = arg2;
}

s16 Player_GetOtherStamina(s32 slot) {  
    s16 stamina; 
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    stamina = player->staminas.byName.stamina;
    return stamina;
}

void Player_SetOtherStamina(s32 slot, s32 stamina) {  
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->staminas.byName.stamina = stamina;
}

u32 Player_GetRemainingHP(s32 slot) {  
    StaticPlayer* player;
    s32 result;
    u32 result2;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    result = player->staminas.byName.stamina - player->staminas.byIndex[player->transformed[0]];
    result2 = result;
    if (result < 0) { result2 = 0; }
    return result2;
}

u8 Player_GetMoreFlagsBit2(s32 slot) { 
    StaticPlayer* player;
    u8 bit2;
    Player_CheckSlot(slot);
    player = &player_slots[slot];

    bit2 = player->more_flags.b2;
    return bit2;
}

void Player_SetMoreFlagsBit2(s32 slot, u8 bit2) {  
    StaticPlayer* player;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    player->more_flags.b2 = bit2;
}

s32 Player_GetMoreFlagsBit3(s32 slot) {   
    StaticPlayer* player;
    s32 bit3;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    bit3 = player->more_flags.b3;
    return bit3;
}

void Player_SetMoreFlagsBit3(s32 slot, u8 bit3) {   
    StaticPlayer* player;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    player->more_flags.b3 = bit3;
}

void Player_SetMoreFlagsBit4(s32 slot, u8 bit4) {
    StaticPlayer* player;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    player->more_flags.b4 = bit4;
}

s32 Player_GetMoreFlagsBit4(s32 slot) {
    StaticPlayer* player;
    u8 bit4;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    bit4 = player->more_flags.b4;
    return bit4;
}

u8 Player_GetMoreFlagsBit5(s32 slot) { 
    StaticPlayer* player;
    u8 bit5;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    bit5 = player->more_flags.b5;
    return bit5;
}


void Player_SetMoreFlagsBit5(s32 slot, u8 bit5) {
    StaticPlayer* player;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    player->more_flags.b5 = bit5;
}

u8 Player_GetMoreFlagsBit6(s32 slot) {  
    StaticPlayer* player;
    u8 bit6;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    bit6 = player->more_flags.b6;
    return bit6;
}


void Player_SetMoreFlagsBit6(s32 slot, u8 bit6) {   
    StaticPlayer* player;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    player->more_flags.b6 = bit6;
}

u8 Player_GetFlagsAEBit0(s32 slot) {   
    StaticPlayer* player;
    u8 bit0;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    bit0 = player->flagsAE.b0;
    return bit0;
}

void Player_SetFlagsAEBit0(s32 slot, u8 bit0) {   
    StaticPlayer* player;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    player->flagsAE.b0 = bit0;
}

u32 Player_GetRemainingHPByIndex(s32 slot, s32 index) { 
    StaticPlayer* player;
    u32 stamina;
    s32 result;
    u32 result2;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    stamina = player->staminas.byName.stamina;
    result = stamina - player->staminas.byIndex[player->transformed[index]];
    result2 = result;
    if (result < 0) { result2 = 0; }
    return result2;
}

s32 Player_GetFalls(s32 slot) {  /// decomp.me/scratch/8ijor
    StaticPlayer* player;
    struct Unk_Struct_w_Array* unkStruct = (struct Unk_Struct_w_Array*) &str_PdPmdat_start_of_data;
    Player_CheckSlot(slot);
    player = &player_slots[slot];

    if (unkStruct->vec_arr[player->player_character].y != -1 && unkStruct->vec_arr[player->player_character].z != 0) {
        return player->falls[player->transformed[0]] + player->falls[player->transformed[1]];
    }

    return player->falls[player->transformed[0]];
}

s32 Player_GetFallsByIndex(s32 slot, s32 arg1) {  
    StaticPlayer* player;
    s32 falls;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    falls = player->falls[player->transformed[arg1]];
    return falls;
}

void Player_SetFalls(s32 slot, s32 falls) {   
    StaticPlayer* player;
    s32 unused;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->falls[player->transformed[0]] = falls;
}

void Player_SetFallsByIndex(s32 slot, s32 index, s32 falls) {   
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->falls[player->transformed[index]] = falls;
}


s32 Player_GetKOsByPlayerIndex(s32 slot, s32 index) {   
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    return player->kos_by_player[index];
}

void Player_UpdateKOsBySlot(s32 slot, BOOL bool_arg, s32 other_slot) {  
    StaticPlayer* player;
    StaticPlayer* other_player;

    s32 unused[4];

    s32 player_team;
    s32 other_player_team;

    s32 kos;

    Player_CheckSlot(slot);
    player = &player_slots[slot];


    if (bool_arg == 0) {
        kos = player->kos_by_player[other_slot];

        if (kos < -1U) {
            player->kos_by_player[other_slot]++;
        }

        if (slot == other_slot){
            func_802F6D10(other_slot);
        } else {

            if (func_8016B168() != 0) {
                Player_CheckSlot(slot);
                Player_CheckSlot(other_slot);
                other_player = &player_slots[other_slot];
                player_team = player->team;
                other_player_team = other_player->team;
                if (player_team == other_player_team) {
                    func_802F69C0(other_slot, slot);
                    return;
                }
            }

            func_802F6AF8(other_slot);
        }
    }
}


u32 Player_GetMatchFrameCount(s32 slot) {   
    StaticPlayer* player;
    s32 count;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    count = player->match_frame_count;
    return count;
}


void Player_UpdateMatchFrameCount(s32 slot, BOOL condition) {   
    StaticPlayer* player;
    s32 unused;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    if ((condition == 0) && (player->match_frame_count + 0x10000) == 0xffff) {
        player->match_frame_count = func_8016AEDC();
    }
}


u16 Player_GetSuicideCount(s32 slot) { 
    StaticPlayer* player;
    u16 count;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    count = player->suicide_count;
    return count;
}

void Player_SetSuicideCount(s32 slot, u32 suicide_count) {  
    StaticPlayer* player;
    if (suicide_count > 0xffff || 0 >(s32)suicide_count) {
        return;
    }
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->suicide_count = suicide_count;
}

void Player_IncSuicideCount(s32 slot, s32 condition) {   
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

BOOL Player_800353BC(s32 slot) {   
    StaticPlayer* player;

    Player_CheckSlot(slot);
    player = &player_slots[slot];

    if (player->player_state == 2 && (player->flags.b0)) {
        return 1;
    }

    return 0;
}

BOOL Player_8003544C(s32 slot, BOOL condition) {  
    StaticPlayer* player;

    s32 unused;

    if (condition == FALSE) {
        Player_CheckSlot(slot);
        player = &player_slots[slot];

        if (player->player_state == 2 && (player->flags.b0)) {
            return TRUE;
        }
    }

    return 0;
}

void Player_SetFlagsBit0(s32 slot, s32 bit0) {  
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->flags.b0 = bit0;
}


s8 Player_GetNametagSlotID(s32 slot) {  
    StaticPlayer* player;
    s32 nametag_slot_id;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    nametag_slot_id = player->nametag_slot_id;
    return nametag_slot_id & 0xFF;
}

void Player_SetNametagSlotID(s32 slot, s32 nametag_slot_id) {  
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->nametag_slot_id = nametag_slot_id;
}


s32 Player_GetFlagsBit1(s32 slot) {  
    StaticPlayer* player;
    u8 bit1;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    bit1 = player->flags.b1;
    return bit1;
}

void Player_SetFlagsBit1(s32 slot) {  
    StaticPlayer* player;
    s8 one = 1;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->flags.b1 = one;
}


void Player_UnsetFlagsBit1(s32 slot) {  
    StaticPlayer* player;
    s8 zero = 0;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->flags.b1 = zero;
}

s32 Player_GetFlagsBit3(s32 slot) {  
    StaticPlayer* player;
    u8 bit3;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    bit3 = player->flags.b3;
    return bit3;
}

void Player_SetFlagsBit3(s32 slot, u8 bit3) {  
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->flags.b3 = bit3;
}


u8 Player_GetFlagsBit4(s32 slot) {  
    StaticPlayer* player;
    u8 bit4;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    bit4 = player->flags.b4;
    return bit4;
}

u8 Player_GetFlagsBit5(s32 slot) {  
    StaticPlayer* player;
    u8 bit5;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    bit5 = player->flags.b5;
    return bit5;
}

void Player_SetFlagsBit5(s32 slot, u8 bit5) {   
    StaticPlayer* player;   
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->flags.b5 = bit5;
}


u8 Player_GetFlagsBit6(s32 slot) { 
    StaticPlayer* player;
    u8 bit6;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    bit6 = player->flags.b6;
    return bit6;
}

void Player_SetFlagsBit6(s32 slot, u8 bit6) { 
    StaticPlayer* player;   
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->flags.b6 = bit6;
}

u8 Player_GetFlagsBit7(s32 slot) {   
    StaticPlayer* player;
    u8 bit7;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    bit7 = player->flags.b7;
    return bit7;
}

void Player_SetFlagsBit7(s32 slot, u8 bit7) {  
    StaticPlayer* player;   
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->flags.b7 = bit7;
}

u8 Player_GetMoreFlagsBit0(s32 slot) { 
    StaticPlayer* player;
    u8 bit0;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    bit0 = player->more_flags.b0;
    return bit0;
}

u8 Player_GetMoreFlagsBit1(s32 slot) {   
    StaticPlayer* player;
    u8 bit1;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    bit1 = player->more_flags.b1;
    return bit1;
}

void Player_SetMoreFlagsBit1(s32 slot, u8 bit1) { 
    StaticPlayer* player;   
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->more_flags.b1 = bit1;
}

s32 Player_GetUnk4D(s32 slot) {   
    StaticPlayer* player;
    u8 unk4D;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    unk4D = player->unk4D;
    return unk4D;
}


void Player_SetUnk4D(s32 slot, s8 unk4D) {   
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->unk4D = unk4D;
}

u8 Player_GetFlagsAEBit1(s32 slot) {  
    StaticPlayer* player;
    u8 bit1;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    bit1 = player->flagsAE.b1;
    return bit1;
}

////output is actually void, but needs u8 to match, most likely typo from Nintendo
u8 Player_SetFlagsAEBit1(s32 slot, u8 bit1) {  
    StaticPlayer* player; 
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player_slots[slot].flagsAE.b1 = bit1;
}

u8 Player_GetUnk4C(s32 slot) {  
    StaticPlayer* player;
    u8 unk4C;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    unk4C = player->unk4C;
    return unk4C;
}

void Player_SetUnk4C(s32 slot, u8 unk4C) {
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->unk4C = unk4C;
}

void Player_80036058(s32 slot) {   
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    func_80086F4C(player->player_entity[player->transformed[0]]);
}

void Player_800360D8(s32 slot) {  
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    func_80086F80(player->player_entity[player->transformed[0]]);
}

void Player_SetStructFunc(s32 slot, void* arg_func) { 
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->struct_func = arg_func;
}

s32* Player_GetTotalAttackCountPtr(s32 slot) {  
    StaticPlayer* player;
    s32* attack_count;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    attack_count = &player->total_attack_count;
    return attack_count;
}

s32* Player_GetStaleMoveTableIndexPtr(s32 slot) {  
    StaticPlayer* player;
    s32* stale_move_table_index;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    stale_move_table_index = &player->stale_move_table_current_write_index;
    return stale_move_table_index;
}

s32* Player_GetUnk6A8Ptr(s32 slot) {   
    StaticPlayer* player;
    s32* unk6A8;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    unk6A8 = &player->unk6A8;
    return unk6A8;
}

s32* Player_GetStaleMoveTableIndexPtr2(s32 slot) { 
    StaticPlayer* player;
    s32* stale_move_table_index;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    stale_move_table_index = &player->stale_move_table_current_write_index;
    return stale_move_table_index;
}

s32 Player_80036394(s32 slot) { 
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

s32 Player_80036428(s32 slot) {  
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

void Player_SetUnk45(s32 slot, s8 unk45) {  
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    player->unk45 = unk45;
}

u8 Player_GetUnk45(s32 slot) {  
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    if (player->slot_type == 0) {
        return player->unk45;
    }

    return 4;
}


void Player_UpdateJoystickCountByIndex(s32 slot, s32 index) {   
    StaticPlayer* player;
    s32 transformed;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    transformed = player->transformed[index];
    player->joystick_direction_input_count[transformed]++;
}


s32 Player_GetJoystickCountByIndex(s32 slot, s32 index) {  
    StaticPlayer* player;
    s32 transformed;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    transformed = player->transformed[index];
    return player->joystick_direction_input_count[transformed];
}

void Player_800366DC(s32 slot, s32 arg1) {  
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

void Player_80036790(s32 slot, f32 arg1) {   
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

void Player_80036844(s32 slot, s32 arg1) {  
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

void Player_800368F8(s32 slot) {  
    StaticPlayer* player;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    func_80086BB4(player->player_entity[player->transformed[0]]);
}

void Player_80036978(s32 slot, s32 arg1) {  
    StaticPlayer* player;
    s32 unused;
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    func_80086B90(player->player_entity[player->transformed[0]], arg1);
}



void Player_InitOrResetPlayer(s32 slot) {   
    StaticPlayer* player;
    u8 *transformed0;
    u8 *transformed1;
    f32 zerofloat;
    f32 onefloat;
    s32 unused[14];

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
    player->transformed[1] =  1;

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

    player->falls[player->transformed[0]] =  0;
    player->falls[player->transformed[1]] =  0;

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

void Player_80036CF0(s32 slot) {   
    Player_InitOrResetPlayer(slot);
    func_8003891C(slot);
}


void Player_80036D24(s32 slot) {   
    Player_InitOrResetPlayer(slot);
    func_80038F10(slot);
}

void Player_InitAllPlayers() {   
    s32 i;
    func_8003715C();
    func_80037590();

    for (i = 0; i < 6; i++) {
        Player_InitOrResetPlayer(i);
        func_8003891C(i);
    }
}

void Player_80036DA4() { 
    HSD_ObjAllocInit(&lbl_804587E0, 8, 4);
    Fighter_FirstInitialize_80067A84();
}

void Player_80036DD8() {   
    s32 *sp8;

    func_80016C64(str_PdPmdat_start_of_data, &sp8, str_plLoadCommonData, 0);
    lbl_804D6470 = *sp8;
}

void Player_80036E20(s32 arg0, s32 arg1, s32 arg2) {   /// decomp.me/scratch/J1Elr
    struct Unk_Struct_w_Array* unkStruct = (struct Unk_Struct_w_Array*) &str_PdPmdat_start_of_data;
    func_800BEB60(unkStruct->vec_arr[arg0].x, arg1, arg2);
    if ((unkStruct->vec_arr[arg0].y != -1) && (unkStruct->vec_arr[arg0].z == 0)) {
        func_800BEB60(unkStruct->vec_arr[arg0].y, arg1, arg2);
    }
}

s32 Player_80036EA0(s32 slot) { 
    StaticPlayer* player;
    HSD_GObj* entity;
    Player_CheckSlot(slot);
    player = &player_slots[slot];

    entity = player->player_entity[player->transformed[0]];

    if (entity) { return func_800865F0(entity);  } 

    return 0;
}

void Player_80036F34(s32 slot, s32 arg1) { 
    struct plAllocInfo2 some_struct;
    u8 unused;

    StaticPlayer* player;
    
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    some_struct.internal_id = ftMapping_list[player->player_character].internal_id;
    some_struct.slot = slot;  
    some_struct.bits.has_transformation = 0; 
    some_struct.unk8 = arg1;  
    some_struct.bits.b0 = 0;


    player->slot_type = 2;
    player->player_entity[0] = func_800BE7E0(&some_struct);
    if ((ftMapping_list[player->player_character].extra_internal_id != -1) && (ftMapping_list[player->player_character].has_transformation == 0)) {
        some_struct.internal_id = ftMapping_list[player->player_character].extra_internal_id;
        some_struct.bits.has_transformation = 1;
        player->player_entity[1] = func_800BE7E0(&some_struct);
    }  
}


void Player_80037054(s32 slot, s32 arg1) { 
    struct plAllocInfo2 some_struct;
    u8 unused;

    StaticPlayer* player;
    
    Player_CheckSlot(slot);
    player = &player_slots[slot];
    some_struct.internal_id = ftMapping_list[player->player_character].internal_id;  
    some_struct.slot = slot;  
    some_struct.bits.has_transformation = 0;  
    some_struct.unk8 = arg1;  
    some_struct.bits.b0 = 1;


    player->slot_type = 2;
    player->player_entity[0] = func_800BE7E0(&some_struct);
    if ((ftMapping_list[player->player_character].extra_internal_id != -1) && (ftMapping_list[player->player_character].has_transformation == 0)) {
        some_struct.internal_id = ftMapping_list[player->player_character].extra_internal_id;
        some_struct.bits.has_transformation = 1;
        player->player_entity[1] = func_800BE7E0(&some_struct);
    }
}

