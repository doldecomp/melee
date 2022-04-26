#include "fighter.h"

#define HALF_PI 1.5707963267948966

// external vars from asm/melee/ft/code_8008521C.s
typedef void (*ft_callback)(HSD_GObj* gobj);
typedef void (*fn_ptr_t)();


extern ft_callback ft_OnLoad[33];  // One load  callback for every character.
extern ft_callback ft_OnDeath[33]; // One death callback for every character.
extern ft_callback ft_OnAbsorb[33];
extern ft_callback lbl_803C1DB4[33];  //probably ft_OnSomething
///extern ft_callback lbl_803C125C[33]; now unused because func_8006DABC is moved to ftanim.s

extern fn_ptr_t lbl_803C10D0[33];

extern struct UnkCostumeList CostumeListsForeachCharacter[33];

extern ftData* gFtDataList[33];
extern struct ActionState ActionStateList[341];
extern struct ActionState* ActionStateTableByCharacter[33];

extern s8 lbl_803C26FC[33];

extern HSD_ObjAllocData lbl_804590AC; // from ft/ftparts.s


extern HSD_PadStatus HSD_PadRumbleData[4];

extern StageInfo stage_info; // from asm/melee/text_2.s

extern s32 g_debugLevel; // asm/melee/db/code_80225374.s

extern u8 lbl_804D7849; // asm/sysdolphin/baselib/gobj.s

// ==== fighter.c variables ====
// =============================

const Vec3 lbl_803B7488 = { 0.0f, 0.0f, 0.0f };
const Vec3 lbl_803B7494 = { 0.0f, 0.0f, 0.0f };

HSD_ObjAllocData lbl_80458FD0;
HSD_ObjAllocData lbl_80458FFC;


// TODO: verify that this is really a spawn number counter, then rename this var globally
u32 lbl_804D64F8 = 0;
#define g_spawnNumCounter lbl_804D64F8

// the following seems to be an array, initialized in reverse in Fighter_LoadCommonData
// outcommented because they are in variables.h too. uncomment this when moving data from fighter.s here.
void* lbl_804D64FC = 0;
void* lbl_804D6500 = 0;
void* lbl_804D6504 = 0;
void* lbl_804D6508 = 0;
void* lbl_804D650C = 0;
void* lbl_804D6510 = 0;
void* lbl_804D6514 = 0;
void* lbl_804D6518 = 0;
void* lbl_804D651C = 0;
void* lbl_804D6520 = 0;
void* lbl_804D6524 = 0;
void* lbl_804D6528 = 0;
void* lbl_804D652C = 0;
void* lbl_804D6530 = 0;
void* lbl_804D6534 = 0;
void* lbl_804D6538 = 0;
void* lbl_804D653C = 0;
s32** lbl_804D6540 = 0;
void* lbl_804D6544 = 0;
void* lbl_804D6548 = 0;
void* lbl_804D654C = 0;
void* lbl_804D6550 = 0;
ftCommonData* p_ftCommonData;


// ==== fighter.c functions ====
// =============================


void Fighter_800679B0()
{ 
	s32 i;

	// @WARNING: don't hardcode the allocation sizes
	HSD_ObjAllocInit(&lbl_80458FD0+0, /*size*/0x23ec, /*align*/4);
	HSD_ObjAllocInit(&lbl_80458FD0+1, /*size*/0x424 , /*align*/4);
	func_800852B0();
	Fighter_LoadCommonData();
	func_8008549C();
	func_8009F4A4();
	func_800C8064();
	func_800C8F6C();
	// @TODO: &lbl_80458FD0+2, +3, +4 are not defined in the fighter.s data section, how does this work?
	HSD_ObjAllocInit(&lbl_80458FD0+2, /*size*/0x8c0, /*align*/4);
	HSD_ObjAllocInit(&lbl_80458FD0+3, /*size*/0x1f0, /*align*/4);
	HSD_ObjAllocInit(&lbl_80458FD0+4, /*size*/0x80 , /*align*/4);

	g_spawnNumCounter = 1;

	for (i = 0; i < 33; i++)
	{
        if (lbl_803C10D0[i])
            lbl_803C10D0[i]();
	}
}

void Fighter_FirstInitialize_80067A84()
{
	Fighter_800679B0();
    // TODO: size parameter too large to be only the size. maybe this contains flags. In other function calls, size only looks plausible. Or is this virtual memory?
	HSD_ObjAllocInit(&lbl_804590AC, /*size*/0x0000800000008000, /*align*/0x20); 
}


void Fighter_LoadCommonData()
{
    void** pData;
    func_80016C64("PlCo.dat", &pData, "ftLoadCommonData", 0);

	// copy 23 4-byte chunks from pData to p_ftCommonData in reverse order, equivalent to this:
	// for(i=0; i<23; i++)
	//   (&lbl_804D64FC)[23-1-i] = pData[i];
	// loop unrolling doesn't work (only up to 8 elements)
	p_ftCommonData = pData[0]; // p_ftCommonData
	lbl_804D6550 = pData[1];
	lbl_804D654C = pData[2];
	lbl_804D6548 = pData[3];
	lbl_804D6544 = pData[4];
	lbl_804D6540 = pData[5];
	lbl_804D653C = pData[6];
	lbl_804D6538 = pData[7];
	lbl_804D6534 = pData[8];
	lbl_804D6530 = pData[9];
	lbl_804D652C = pData[10];
	lbl_804D6528 = pData[11];
	lbl_804D6524 = pData[12];
	lbl_804D6520 = pData[13];
	lbl_804D651C = pData[14];
	lbl_804D6518 = pData[15];
	lbl_804D6514 = pData[16];
	lbl_804D6510 = pData[17];
	lbl_804D650C = pData[18];
	lbl_804D6508 = pData[19];
	lbl_804D6504 = pData[20];
	lbl_804D6500 = pData[21];
	lbl_804D64FC = pData[22];
} 

void Fighter_UpdateModelScale(HSD_GObj* fighterObj)
{
    Vec scale;
    s32 unused[2];

    Fighter* fighter = fighterObj->user_data;

    HSD_JObj* jobj = fighterObj->hsd_obj;
    

    f32 modelScale_f1 = Fighter_GetModelScale(fighter); 
    if (fighter->x34_scale.z != 1.0f)
        scale.x = fighter->x34_scale.z;
    else
        scale.x = modelScale_f1;
    
    scale.y = modelScale_f1;
    scale.z = modelScale_f1;

    HSD_JObjSetScale(jobj, &scale);
}


void Fighter_UnkInitReset_80067C98(Fighter* fighter) {
	Vec3 player_coords;
	f32 x,y,z;
	Fighter* tmp_fighter;

	fighter->x8_spawnNum = Fighter_NewSpawn_80068E40();
	Player_LoadPlayerCoords(fighter->xC_playerID, &player_coords);
	fighter->x2C_facing_direction = Player_GetFacingDirection(fighter->xC_playerID);

	player_coords.x = fighter->x2C_facing_direction * func_800804EC(fighter) + player_coords.x;
	x = player_coords.x;
	fighter->xB0_pos.x = x;
	fighter->xBC_prevPos.x = x;

	y = player_coords.y;
	fighter->xB0_pos.y = y;
	fighter->xBC_prevPos.y = y;

	z = player_coords.z;
	fighter->xB0_pos.z = z;
	fighter->xBC_prevPos.z = z;

	fighter->x30_facingDirectionRepeated = fighter->x2C_facing_direction;
	fighter->x34_scale.y = fighter->x34_scale.x;

	fighter->x2220_flag.bits.b5 = 0;
	fighter->x2220_flag.bits.b6 = 0;

	fighter->x200C = 0;
	fighter->x2010 = 0;
	fighter->x2008 = 0;

	fighter->x2219_flag.bits.b1 = 0;
	fighter->x2219_flag.bits.b2 = 0;
	fighter->x2219_flag.bits.b3 = 0;
	fighter->x2219_flag.bits.b4 = 0;
	fighter->x221A_flag.bits.b5 = 0;
	fighter->x221A_flag.bits.b6 = 0;
	fighter->x221D_flag.bits.b2 = 0;
	fighter->x221E_flag.bits.b7 = 0;
	fighter->x2220_flag.bits.b7 = 0;
	fighter->x2221_flag.bits.b4 = 0;
	fighter->x2221_flag.bits.b5 = 0;
	fighter->x2221_flag.bits.b6 = 1;
	fighter->x2221_flag.bits.b7 = 0;

	fighter->x61D = 255;

	fighter->xC8_pos_delta.z = 0.0f; 
	fighter->xC8_pos_delta.y = 0.0f; 
	fighter->xC8_pos_delta.x = 0.0f; 
	fighter->x894 = 0.0f; 
	fighter->x898 = 0.0f; 

	fighter->x89C = 1.0f; 
	fighter->x8A0 = 1.0f; 
	fighter->dmg.x1850_forceApplied = 0.0f; 
	fighter->dmg.x18A4_knockbackMagnitude = 0.0f; 
	fighter->dmg.x18A8 = 0.0f; 
	fighter->dmg.x18ac_time_since_hit = -1;
	fighter->dmg.x18B0 = 0.0f; 
	fighter->dmg.x18B4_armor = 0.0f; 
	fighter->x1828 = 0;

	fighter->x221C_flag.bits.b6 = 0;

	fighter->dmg.x18a0 = 0.0f; 
	fighter->x1968_jumpsUsed = 0;
	fighter->x1969_walljumpUsed = 0;
	fighter->x196C_hitlag_mult = 0.0f; 
	fighter->x2064_ledgeCooldown = 0;

	fighter->dmg.x1830_percent = Player_GetDamage(fighter->xC_playerID);

	fighter->dmg.x1838_percentTemp = 0.0f; 

	fighter->dmg.x183C_applied = 0;
	fighter->dmg.x18C0 = 0;

	fighter->dmg.x18c4_source_ply = 6;
	fighter->dmg.x18C8 = -1;
	fighter->dmg.x18F0 = 0;
	fighter->dmg.x18CC = 0;
	fighter->dmg.x18D0 = -10;

	fighter->x221F_flag.bits.b5 = 0;
	fighter->x2221_flag.bits.b1 = 0;

	fighter->dmg.x18F4 = 0;
	fighter->dmg.x18F8 = 1;
	fighter->dmg.x18fa_model_shift_frames = 0;
	fighter->dmg.x18FD = 0;
	fighter->dmg.x18FC = 0;
	fighter->dmg.x1834 = 0.0f;

	fighter->x2222_flag.bits.b2 = 0;

	fighter->dmg.x1840 = 0;

	fighter->x2219_flag.bits.b5 = 0; 
	fighter->x2219_flag.bits.b6 = 0;
	fighter->x2219_flag.bits.b7 = 0;
	fighter->x221A_flag.bits.b0 = 0;
	fighter->x221A_flag.bits.b1 = 0;

	fighter->dmg.x1954 = 0.0f;
	fighter->dmg.x1958 = 0.0f;

	fighter->x221A_flag.bits.b2 = 0;

	fighter->dmg.x195c_hitlag_frames = 0.0f;

	fighter->x221A_flag.bits.b3 = 0;
	fighter->x1960_vibrateMult = 1.0f;
	fighter->x1964 = 0.0f;
	fighter->dmg.x189C = 0.0f;

	fighter->x2220_flag.bits.b3 = 0;
	fighter->x2220_flag.bits.b4 = 0;

	fighter->dmg.x1914 = 0;
	fighter->dmg.x1918 = 0;
	fighter->dmg.x191C = 0.0f;
	fighter->dmg.x1924 = 0;
	fighter->dmg.x1928 = 0.0f;

	fighter->x2223_flag.bits.b5 = 0;

	fighter->dmg.x1950 = 0;
	fighter->dmg.x1948 = 0;

	fighter->x2223_flag.bits.b4 = 0;

	fighter->xF8_playerNudgeVel.y = 0.0f;
	fighter->xF8_playerNudgeVel.x = 0.0f;
	fighter->x100 = -1.0f;

	fighter->x2222_flag.bits.b7 = 0;
	fighter->x2223_flag.bits.b0 = 0;
	fighter->x221A_flag.bits.b4 = 0;
	fighter->x2219_flag.bits.b0 = 0;

	fighter->x20A0 = 0;
	fighter->x2210_ThrowFlags.flags = 0;
	fighter->x2214 = 0.0f; 
	fighter->x1974_heldItem = 0;
	fighter->x1978 = 0;

	fighter->x221E_flag.bits.b3 = 1;

	fighter->x1984_heldItemSpec = 0;
	fighter->x1988 = 0;
	fighter->x198C = 0;

	fighter->x2221_flag.bits.b0 = 0;

	fighter->x1990 = 0;
	fighter->x1994 = 0;

	fighter->x221D_flag.bits.b6 = 0;
	fighter->x221B_flag.bits.b5 = 0;

	fighter->x1A58 = 0;
	fighter->x1A5C = 0;

	fighter->x221B_flag.bits.b6 = 0;

	fighter->x1A60 = 0;
	fighter->x1A64 = 0;

	fighter->x221B_flag.bits.b7 = 0;
	fighter->x221C_flag.bits.b0 = 0;

	fighter->x1064_thrownHitbox.x134 = 0;
	fighter->x221C_u16_y = 0;
	fighter->x20AC = 0;
	fighter->x221C_flag.bits.b5 = 0;

    fighter->x2150 = 
	fighter->x2154 = 
	fighter->x2158 = 
	fighter->x215C = 
	fighter->x2160 = 
	fighter->x2144 = 
	fighter->x2148 =   
	fighter->x214C = -1;
    
	fighter->x2168 = 0;
	fighter->x2164 = 0;
	fighter->x208C = 0;
	fighter->x2090 = 0;
	fighter->x2098 = 0;
	fighter->x2092 = 0;
	fighter->x2094 = 0;
	fighter->x1998_shieldHealth = p_ftCommonData->x260_startShieldHealth;

	fighter->x221A_flag.bits.b7 = 0;
    fighter->x221B_flag.bits.b0 = 0;
	fighter->x221B_flag.bits.b1 = 0;
	fighter->x221B_flag.bits.b3 = 0;
	fighter->x221B_flag.bits.b4 = 0;
	fighter->x221C_flag.bits.b3 = 0;
	fighter->x221C_flag.bits.b1 = 0;
	fighter->x221C_flag.bits.b2 = 0;

	fighter->x19A0_shieldDamageTaken = 0;
	fighter->x19A4 = 0;
	fighter->x199C_shieldLightshieldAmt = 0.0f;
	fighter->x19A8 = 0;
	fighter->x19B4_shieldUnk = 0.0f;
	fighter->x19B8_shieldUnk = 0.0f;
	fighter->x19BC_shieldDamageTaken3 = 6;

	fighter->x221F_flag.bits.b6 = 0;
	fighter->x2218_flag.bits.b3 = 0;
	fighter->x2218_flag.bits.b4 = 0;
	fighter->x1A3C = 0;
	fighter->x1A2C_reflectHitDirection = 0.0f;
	fighter->x2218_flag.bits.b6 = 0; 
	fighter->x2218_flag.bits.b7 = 0;


	fighter->x1A40 = 0.0f;

	fighter->x1A44 = 0;
	fighter->x1A48 = 0;

	fighter->x68C_transNPos.z = 0.0f;
	fighter->x68C_transNPos.y = 0.0f;
	fighter->x68C_transNPos.x = 0.0f;
	fighter->x6A4_transNOffset.z = 0.0f;
	fighter->x6A4_transNOffset.y = 0.0f;
	fighter->x6A4_transNOffset.x = 0.0f;
	fighter->x6BC_inputStickangle = 0.0f;

	fighter->x6C0.z = 0.0f; 
	fighter->x6C0.y = 0.0f; 
	fighter->x6C0.x = 0.0f; 

	fighter->x6D8.z = 0.0f; 
	fighter->x6D8.y = 0.0f; 
	fighter->x6D8.x = 0.0f; 

	fighter->x209C = 0;
	fighter->x2224_flag.bits.b1 = 0;
	fighter->cb.x21E4_callback_OnDeath2 = 0;
	fighter->x2100 = -1;
	fighter->x2101_bits_0to6 = 0;
	fighter->cb.x21B4_callback_Accessory2 = 0;
	fighter->cb.x21B8_callback_Accessory3 = 0;
	fighter->cb.x21E0_callback_OnDeath = 0;
	fighter->cb.x21E8_callback_OnDeath3 = 0;
	fighter->x221E_flag.bits.b4 = 1;
	fighter->x197C = 0;
	fighter->x2223_flag.bits.b7 = 0;
	fighter->x2028 = 0;
	fighter->x202C = 0;

	tmp_fighter = fighter;
	func_800C88A0(tmp_fighter);

	fighter->x2227_flag.bits.b3 = 0;
	fighter->x2034 = 0;
	fighter->x2038 = 0;
	fighter->x1980 = 0;

	fighter->x2224_flag.bits.b2 = fighter->x2224_flag.bits.b3 = 0;

	fighter->x2224_flag.bits.b4 = 0;
	fighter->x2108 = 0;
	fighter->x2224_flag.bits.b5 = 0;
	fighter->x1A53 = (s8) 0;
	fighter->x1A52 = (s8) 0;
	fighter->x210C_walljumpInputTimer = 254;
	fighter->dmg.x1910 = 0;
	fighter->x2225_flag.bits.b0 = 0;
	fighter->x2225_flag.bits.b2 = 1;
	fighter->x2225_flag.bits.b4 = 0;
	func_800DEEA8(fighter->x0_fighter);
	fighter->dmg.x18BC = 0.0f; 
	fighter->dmg.x18B8 = 0.0f; 
	fighter->x2226_flag.bits.b2 = 0;
	fighter->x2170 = 0.0f; 
	fighter->x2225_flag.bits.b6 = fighter->x2225_flag.bits.b5;
	fighter->dmg.x1908 = -1;
	fighter->dmg.x190C = 0;
	fighter->x2227_flag.bits.b4 = 0;
	fighter->x2138_smashSinceHitbox = -1.0f;
	fighter->x213C = -1;
	fighter->x2227_flag.bits.b5 = 0;
	fighter->x2228_flag.bits.b1 = 0;
	fighter->x2140 = 0.0f;
	fighter->x2227_flag.bits.b6 = 0;
	fighter->x2180 = 6;
	fighter->x2229_b4 = 1;
}

void Fighter_UnkProcessDeath_80068354(HSD_GObj* fighterObj) {
    Vec3 vec;
    f32 model_size;
    HSD_JObj* jobj;
    s32 unused_filler[5];

    Fighter* fighter2;
    HSD_JObj* other_jobj;

    Fighter* fighter1 = fighterObj->user_data;

    Fighter_UnkInitReset_80067C98(fighter1);
    jobj = fighterObj->hsd_obj;
    other_jobj = jobj;


    HSD_JObjSetTranslate(other_jobj, &fighter1->xB0_pos);

    func_800D105C(fighterObj);
    func_800C09B4(fighterObj);
    func_8007E2FC(fighterObj);
    func_80088A50(fighter1);
    func_800890BC(fighter1);
    func_800892D4(fighter1);
    func_80081B38(fighterObj);
    func_80081938(fighterObj);


    if (fighter1->x2135 == -1)
    {
        if (func_80082A68(fighterObj) && !fighter1->x2229_b6)
            func_8007D6A4(fighter1);
        else
            func_8007D5D4(fighter1);
    }
    else
        func_8007D5D4(fighter1);


    func_80076064(fighter1);

    other_jobj = jobj = fighterObj->hsd_obj;

    HSD_JObjSetTranslate(jobj, &fighter1->xB0_pos);

    func_8006C0F0(fighterObj);

    jobj = fighterObj->hsd_obj;

    fighter2 = fighterObj->user_data;

    model_size = Fighter_GetModelScale(fighterObj->user_data);

    if (fighter2->x34_scale.z != 1.0f)
        vec.x = fighter2->x34_scale.z;
    else
        vec.x = model_size;
    
    vec.y = model_size;
    vec.z = model_size;

    HSD_JObjSetScale(jobj, &vec);


    func_800BFFAC(fighter1);
    func_800C0074(fighter1);
    func_800C8438(fighterObj);
    func_800C89A0(fighterObj);
    func_800C8FC4(fighterObj);
    func_8007AFF8(fighterObj);
    func_8007B0C0(fighterObj, 0);


    if (ft_OnDeath[fighter1->x4_fighterKind])
        ft_OnDeath[fighter1->x4_fighterKind](fighterObj);

    func_800A101C(fighter1, Player_GetCpuType(fighter1->xC_playerID), Player_GetCpuLevel(fighter1->xC_playerID), 0);

    func_80067688(&fighter1->x60C);
    func_8007C17C(fighterObj);
    func_8007C630(fighterObj);
}


void Fighter_UnkUpdateCostumeJoint_800686E4(HSD_GObj* fighterObj) {
    HSD_JObj* jobj;

    UnkCostumeStruct* costume_list;
    Fighter* fighter = fighterObj->user_data;


    costume_list = CostumeListsForeachCharacter[fighter->x4_fighterKind].costume_list;

    fighter->x108_costume_joint = costume_list[fighter->x619_costume_id].joint;

    func_80074148();
    jobj = HSD_JObjLoadJoint(fighter->x108_costume_joint);
    func_80074170();
    func_80073758(jobj);
    func_80390A70(fighterObj, lbl_804D7849, jobj);
}


void Fighter_UnkUpdateVecFromBones_8006876C(Fighter* fighter) {

    Vec vec;
    Vec vec2;
    HSD_JObj* jobj = fighter->x5E8_fighterBones[func_8007500C(fighter, 2)].x0_jobj;

    HSD_JObjGetTranslation(jobj, &vec);

    fighter->x1A6C = (vec.y / 8.55f);

    func_8000B1CC(jobj, 0, &vec);
    func_8000B1CC(fighter->x5E8_fighterBones[func_8007500C(fighter, 1)].x0_jobj, 0, &vec2);
    fighter->x1A70.x = vec2.x - vec.x;
    fighter->x1A70.y = vec2.y - vec.y;
    fighter->x1A70.z = vec2.z - vec.z;
}


void Fighter_ResetInputData_80068854(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;

    fighter->x620_lstick_x = 
    fighter->x624_lstick_y = 
    fighter->x628_lstick_x2 = 
    fighter->x62C_lstick_y2 = 0.0f;

    fighter->x644_lsubStick_y2 = 0.0f;
    fighter->x640_lsubStick_x2 = 0.0f;
    fighter->x63C_lsubStick_y = 0.0f;
    fighter->x638_lsubStick_x = 0.0f;

    fighter->x654 = 0.0f;
    fighter->x650 = 0.0f;

    fighter->x660 = 0;
    fighter->x66C = 0;
    fighter->x668 = 0;
    fighter->x65C = 0;

    fighter->x672_input_timer_counter = 0xFE;
    fighter->x671_timer_lstick_tilt_y = 0xFE;
    fighter->x670_timer_lstick_tilt_x = 0xFE;

    fighter->x675 = 0xFE;
    fighter->x674 = 0xFE;
    fighter->x673 = 0xFE;

    fighter->x678 = 0xFE;
    fighter->x677_y = 0xFE;
    fighter->x676_x = 0xFE;

    fighter->x67B = 0xFE;
    fighter->x67A_y = 0xFE;
    fighter->x679_x = 0xFE;

    fighter->x68B = 0xFF;
    fighter->x68A = 0xFF;
    fighter->x689 = 0xFF;
    fighter->x688 = 0xFF;
    fighter->x687 = 0xFF;
    fighter->x686 = 0xFF;
    fighter->x685 = 0xFF;
    fighter->x684 = 0xFF;
    fighter->x683 = 0xFF;

    fighter->x680 = 0xFF;
    fighter->x67F = 0xFF;

    fighter->x682 = 0xFF;
    fighter->x681 = 0xFF;

    fighter->x67E = 0xFF;
    fighter->x67D = 0xFF;
    fighter->x67C = 0xFF;
}


void Fighter_UnkInitLoad_80068914(HSD_GObj* fighterObj, struct S_TEMP1* argdata) {
    u32 controller_index;
    struct RGBA* color;
    ftData** ftDataList;
    Fighter* fighter = fighterObj->user_data;
    Fighter* fighter_copy;
    s32 costume_id;

    fighter->x4_fighterKind = argdata->fighterKind;
    fighter->xC_playerID = argdata->playerID;

    fighter->x221F_flag.bits.b4 = argdata->flags.bits.b0;

    fighter->x34_scale.x = Player_GetModelScale(fighter->xC_playerID);
    fighter->x61C = argdata->unk5;
    fighter->x618_player_id = Player_GetPlayerId(fighter->xC_playerID);
    fighter->x61A_controller_index = Player_GetControllerIndex(fighter->xC_playerID);
    fighter->x2223_flag.bits.b6 = Player_GetFlagsBit5(fighter->xC_playerID);
    fighter->x2226_flag.bits.b3 = Player_GetFlagsBit6(fighter->xC_playerID);
    fighter->x2226_flag.bits.b6 = Player_GetFlagsBit7(fighter->xC_playerID);
    fighter->x2225_flag.bits.b5 = Player_GetMoreFlagsBit1(fighter->xC_playerID);
    fighter->x2225_flag.bits.b7 = Player_GetMoreFlagsBit2(fighter->xC_playerID);
    fighter->x2228_flag.bits.b3 = Player_GetMoreFlagsBit6(fighter->xC_playerID);
    fighter->x2229_b1 = Player_GetFlagsAEBit0(fighter->xC_playerID);

    if (fighter->x61A_controller_index > 4) {
        OSReport("fighter sub color num over!\n");
        __assert(__FILE__, 0x33C, "0");
    }

    controller_index = fighter->x61A_controller_index;
    if (controller_index != 0) {
        color = &p_ftCommonData->x6DC_colorsByPlayer[controller_index - 1];
        fighter->x610_color_rgba[0].r = (color->r * color->a) / 0xff;
        fighter->x610_color_rgba[0].g = (color->g * color->a) / 0xff;
        fighter->x610_color_rgba[0].b = (color->b * color->a) / 0xff;
        fighter->x610_color_rgba[0].a = color->a;
    }

    costume_id = Player_GetCostumeId(fighter->xC_playerID);
    if (costume_id >= CostumeListsForeachCharacter[fighter->x4_fighterKind].numCostumes) {
        costume_id = 0;
    }
    
    fighter->x619_costume_id = costume_id;
    fighter->x61B_team = Player_GetTeam(fighter->xC_playerID);
    ftDataList = gFtDataList;
    fighter->x0_fighter = fighterObj;
    fighter->x10C_ftData = ftDataList[fighter->x4_fighterKind];
    func_800D0FA0(fighterObj);
    fighter->x2CC = 0;
    fighter->x2D0 = 0;
    fighter->x18 = 0x155;
    fighter->x1C_actionStateList = ActionStateList;
    fighter->x20_actionStateList = ActionStateTableByCharacter[fighter->x4_fighterKind];
    fighter->x24 = fighter->x10C_ftData->xC;
    fighter->x28 = fighter->x10C_ftData->x10;

    fighter->x634 = 0.0f;
    fighter->x630 = 0.0f;
    fighter->x64C = 0.0f;
    fighter->x648 = 0.0f;
    fighter->x658 = 0.0f;
    fighter->x664 = 0;


    fighter_copy = fighterObj->user_data;
    
    fighter_copy->x650 = 
    fighter_copy->x654 = 
    fighter_copy->x638_lsubStick_x = 
    fighter_copy->x63C_lsubStick_y = 
    fighter_copy->x640_lsubStick_x2 = 
    fighter_copy->x644_lsubStick_y2 = 
    fighter_copy->x620_lstick_x = 
    fighter_copy->x624_lstick_y = 
    fighter_copy->x628_lstick_x2 = 
    fighter_copy->x62C_lstick_y2 = 0.0f;

    fighter_copy->x660 = 0;
    fighter_copy->x66C = 0;
    fighter_copy->x668 = 0;
    fighter_copy->x65C = 0;

    
    fighter_copy->x679_x = 
    fighter_copy->x67A_y = 
    fighter_copy->x67B = 

    fighter_copy->x676_x = 
    fighter_copy->x677_y = 
    fighter_copy->x678 = 

    fighter_copy->x673 = 
    fighter_copy->x674 = 
    fighter_copy->x675 = 

    fighter_copy->x670_timer_lstick_tilt_x = 
    fighter_copy->x671_timer_lstick_tilt_y = 
    fighter_copy->x672_input_timer_counter = 0xFE;


    fighter_copy->x67C = 
    fighter_copy->x67D = 
    fighter_copy->x67E = 
    fighter_copy->x681 = 
    fighter_copy->x682 = 
    fighter_copy->x67F = 
    fighter_copy->x680 = 
    fighter_copy->x683 = 
    fighter_copy->x684 = 
    fighter_copy->x685 = 
    fighter_copy->x686 = 
    fighter_copy->x687 = 
    fighter_copy->x688 = 
    fighter_copy->x689 = 
    fighter_copy->x68A = 
    fighter_copy->x68B = 0xFF;


    fighter->x594_s32 = 0;
    fighter->x21FC = 1;


    fighter->x221E_flag.bits.b0 = 0;
    fighter->x221E_flag.bits.b1 = 0;
    fighter->x221E_flag.bits.b2 = 0;
    fighter->x221F_flag.bits.b1 = 0;
    fighter->x221F_flag.bits.b2 = 0;

    fighter->x209A = 0;
    fighter->x221E_flag.bits.b5 = 0;
    fighter->x221F_flag.bits.b0 = 0;
    fighter->cb.x21EC_callback = 0;

    fighter->x221D_flag.bits.b3 = 0;
    fighter->x221D_flag.bits.b4 = 0;

    fighter->x221F_flag.bits.b3 = 0;

    fighter->x2220_flag.bits.b0 = 0;

    fighter->x2221_flag.bits.b2 = 0;

    fighter->x2229_b5_no_normal_motion = 0;
    fighter->x2229_b6 = 0;
    fighter->x2229_b7 = 0;

    fighter->x222A_flag.bits.b0 = 0;
    fighter->x222A_flag.bits.b1 = 0;

    fighter->x2228_flag.bits.b5 = 0;
    fighter->x2228_flag.bits.b6 = 0;

    fighter->x2221_flag.bits.b3 = 0;

    fighter->x2222_flag.bits.b0 = 0;
    fighter->x2222_flag.bits.b1 = 0;
    fighter->x2222_flag.bits.b4 = 0;
    fighter->x2222_flag.bits.b5 = 0;
    fighter->x2222_flag.bits.b6 = 0;


    fighter->x2223_flag.bits.b1 = 0;

    fighter->x40 = 0.0f;

    fighter->x2224_flag.bits.b7 = 0;

    fighter->x60C = 0;

    fighter->x2225_flag.bits.b3 = 0;
    fighter->x2228_flag.bits.b2 = 0;


    fighter->x2226_flag.bits.b0 = 0;
    fighter->x2226_flag.bits.b1 = 0;

    fighter->x2227_flag.bits.b0 = 0;
    fighter->x2224_flag.bits.b0 = 0;

    fighter->x2135 = -1;
    fighter->x2184 = 0;


    fighter->x2229_b3 = 0;
}


// increments the spawn number, returns the spawn number value before incrementing
u32 Fighter_NewSpawn_80068E40()
{
	u32 spawnNum = g_spawnNumCounter++;
    if (g_spawnNumCounter == 0) g_spawnNumCounter = 1;
	return spawnNum;
}

void Fighter_80068E64(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;

    if (stage_info.internal_stage_id == 0x1B) {
        fighter->x34_scale.z = p_ftCommonData->x7E4_scaleZ;
    } else {
        fighter->x34_scale.z = 1.0f;
    }
}



HSD_GObj* func_80068E98(struct S_TEMP1* input) {

    Vec translation2;
    Vec translation;
    s32 unused[4];

    HSD_GObj* fighterObj;
    HSD_JObj* jobj;
    UnkCostumeStruct* costume_list;

    Fighter* fp;
    Fighter* fp1;
    Fighter* fp2;


    fighterObj = func_803901F0(4, 8, 0);
    GObj_SetupGXLink(fighterObj, &func_80080E18, 5U, 0U);
    fp = HSD_ObjAlloc(&lbl_80458FD0);
    fp->x2D8_specialAttributes2 = HSD_ObjAlloc(&lbl_80458FFC);
    GObj_InitUserData(fighterObj, 4U, &func_8006DABC, fp);
    func_8008572C(input->fighterKind);
    Fighter_UnkInitLoad_80068914(fighterObj, input);
    func_8006737C(lbl_803C26FC[fp->x4_fighterKind]);
    func_80085820(fp->x4_fighterKind, fp->x619_costume_id);
    fp1 = fighterObj->user_data;
    costume_list = CostumeListsForeachCharacter[fp1->x4_fighterKind].costume_list;
    fp1->x108_costume_joint = costume_list[fp1->x619_costume_id].joint;
    func_80074148();
    jobj = HSD_JObjLoadJoint(fp1->x108_costume_joint);
    func_80074170();
    func_80073758(jobj);
    func_80390A70(fighterObj, lbl_804D7849, jobj);
    func_80085B10(fp);
    func_80074E58(fp);
    func_800743E0(fighterObj);
    func_80070308(fighterObj);
    func_800C884C(fighterObj);
    fp2 = fighterObj->user_data;
    if (stage_info.internal_stage_id == 0x1B) {
        fp2->x34_scale.z = p_ftCommonData->x7E4_scaleZ;
    } else {
        fp2->x34_scale.z = 1.0f;
    }
    func_800749CC(fighterObj);
    func_8007077C(fighterObj);
    func_8009CF84(fp);
    func_8006FE48(fighterObj);
    jobj = fp->x5E8_fighterBones[func_8007500C(fp, 2)].x0_jobj;

    HSD_JObjGetTranslation(jobj, &translation);

    fp->x1A6C = (translation.y / 8.55f);
    func_8000B1CC(jobj, 0, &translation);
    func_8000B1CC(fp->x5E8_fighterBones[func_8007500C(fp, 1)].x0_jobj, 0, &translation2);
    fp->x1A70.x = translation2.x - translation.x;
    fp->x1A70.y = translation2.y - translation.y;
    fp->x1A70.z = translation2.z - translation.z;
    func_8009F578(fp);

    if (ft_OnLoad[fp->x4_fighterKind]) {
        ft_OnLoad[fp->x4_fighterKind](fighterObj);
    }
    fp2 = fighterObj->user_data;
    if (fp2->x2229_b5_no_normal_motion == 0) {
        
        fp2->x2EC = func_8001E8F8(func_80085E50(fp2, 0x23));
        if (fp2->x2228_flag.bits.b2 == 0) {
            
            fp2->x2DC = func_8001E8F8(func_80085E50(fp2, 7));
            
            fp2->x2E0 = func_8001E8F8(func_80085E50(fp2, 8));
            
            fp2->x2E4 = func_8001E8F8(func_80085E50(fp2, 9));
            
            fp2->x2E8 = func_8001E8F8(func_80085E50(fp2, 0x25));
        }
    }
    func_8007B320(fighterObj);
    fp->x890_cameraBox = func_80029020();

    func_8000ED54(&fp->x20A4, fighterObj->hsd_obj);
    func_8038FD54(fighterObj, &Fighter_8006A1BC, 0);
    func_8038FD54(fighterObj, &Fighter_8006A360, 1);
    func_8038FD54(fighterObj, &Fighter_8006ABA0, 2);
    func_8038FD54(fighterObj, &Fighter_Spaghetti_8006AD10, 3);
    func_8038FD54(fighterObj, (void*) &Fighter_procUpdate, 4);
    func_8038FD54(fighterObj, (void*) &func_8006C27C, 6);
    func_8038FD54(fighterObj, &func_8006C5F4, 7);
    func_8038FD54(fighterObj, &func_8006C624, 8);
    func_8038FD54(fighterObj, &func_8006C80C, 9);
    func_8038FD54(fighterObj, &func_8006CA5C, 0xC);
    func_8038FD54(fighterObj, &func_8006CB94, 0xD);
    func_8038FD54(fighterObj, &func_8006D1EC, 0xE);
    func_8038FD54(fighterObj, &func_8006D9AC, 0x10);
    func_8038FD54(fighterObj, &func_8006D9EC, 0x12);
    func_8038FD54(fighterObj, &func_8006DA4C, 0x16);
    Fighter_UnkProcessDeath_80068354(fighterObj);

    if (fp->x4_fighterKind == 0x1B) {
        func_8014FE10(fighterObj);
    }
    else if (fp->x4_fighterKind == 0x1C) {
        func_80155FCC(fighterObj);
    }
    else if (input->flags.bits.b1 != 0) {
        func_800BFD04(fighterObj);
    }
    else if (Player_GetFlagsBit3( fp->xC_playerID) != 0) {
        func_800C61B0(fighterObj);
    }
    else {
        if (!fp->x2229_b5_no_normal_motion) {
            func_8007D92C(fighterObj);
        } else {
            OSReport("ellegal flag fp->no_normal_motion\n");
            __assert(__FILE__, 1065, "0");
        }
    }
    func_800867E8(fighterObj);
    return fighterObj;
}


/// https://decomp.me/scratch/VyJpx
inline f32 pickValue(f32 argA, u8* unk_byte_ptr)
{
    return (argA == -1.0f) ? 0.0f :  (argA) ? argA : *unk_byte_ptr;
}
void Fighter_ActionStateChange_800693AC(HSD_GObj* fighterObj, s32 new_action_state_index, s32 arg2, HSD_GObj* otherObj, f32 arg8, f32 arg9, f32 argA) {
    volatile s32 volatile_integer;
    Vec translation;
    Quaternion quat;
    s32 unused[4];
    HSD_JObj* other_jobj;
    s32 bone_index;
    HSD_JObj* jobj;
    Fighter* fighter;
    struct ActionState* new_action_state;
    struct S_TEMP4* unk_struct_x18;
    u8* unk_byte_ptr;
    BOOL animflags_bool;

    
    jobj = fighterObj->hsd_obj;
    other_jobj = jobj;
    fighter = fighterObj->user_data;

    fighter->x10_action_state_index = new_action_state_index;
    fighter->x30_facingDirectionRepeated = fighter->x2C_facing_direction;
        
    HSD_JObjSetTranslate(jobj, &fighter->xB0_pos);
    func_80067624(fighterObj, &fighter->x60C);

    if ((arg2 & 8) == 0) {
        if (fighter->x2219_flag.bits.b3 != 0) {
            func_8007AFF8(fighterObj);
        }
        if (fighter->x2219_flag.bits.b4 != 0) {
            func_8007C114(fighterObj);
        }
    }

    if ((arg2 & 0x100) == 0) {
        fighter->x1198 = 0;
    }

    if ((arg2 & 4) == 0) {
        if (fighter->x1988 != 0) {
            func_8007B62C(fighterObj, 0);
        }
        if (fighter->x221A_flag.bits.b5 != 0) {
            func_8007B0C0(fighterObj, 0);
        }
    }

    if (fighter->x221A_flag.bits.b6 != 0) {
        func_8007B4E0(fighterObj);
    }

    if (((arg2 & 0x10) == 0) && (fighter->x221D_flag.bits.b2 != 0U)) {
        func_80074A8C(fighterObj);
    }

    if (((arg2 & 0x80) == 0) && ((fighter->x221E_flag.bits.b7) != 0)) {
        func_80070654(fighterObj);
    }

    if ((arg2 & 0x400) == 0) {
        fighter->x2221_flag.bits.b4 = 0;
        if ((func_8007E994(fighterObj) != -1) && (func_8007E994(fighterObj) != 6)) {
            func_8007E83C(fighterObj, 6, 0.0f);
        }
    }

    func_80070F28(fighterObj);
    func_80070E74(fighterObj);
    func_8007ECD4(fighter, 7);
    func_8007ECD4(fighter, 8);
    func_8007ECD4(fighter, 0x24);

    if ((arg2 & 0x800) == 0) {
        func_8007ECD4(fighter, 1);
        func_8007ECD4(fighter, 0x19);
    }

    if (((arg2 & 0x10000) == 0) && (fighter->x2221_flag.bits.b1 != 0U)) {
        func_8007B6EC(fighterObj);
        func_8007B760(fighterObj, p_ftCommonData->x134);
        fighter->x2221_flag.bits.b1 = 0;
    }
    func_8007E2F4(fighter, 0);

    if (fighter->dmg.x18F4 != 0) {
        fighter->dmg.x18F4 = 0;
        fighter->x2220_flag.bits.b4 = 0;
    }

    if ((arg2 & 0x80000) == 0) {
        fighter->x2222_flag.bits.b2 = 0;
    }

    if ((arg2 & 0x800000) == 0) {
        fighter->x2223_flag.bits.b4 = 0;
    }

    if ((arg2 & 0x8000000) == 0) {
        fighter->x2227_flag.bits.b2 = 0;
    }

    if (((arg2 & 0x10000000) == 0) && (fighter->x221C_flag.bits.b6 != 0U)) {
        fighter->x221C_flag.bits.b6 = 0;
        fighter->x2098 = p_ftCommonData->x4CC;
    }

    fighter->x221F_flag.bits.b3 = 0;
    fighter->x2219_flag.bits.b1 = 0;
    fighter->x2219_flag.bits.b2 = 0;

    fighter->dmg.x182c_behavior = 1.0f;
    fighter->dmg.x1850_forceApplied = 0.0f;
    fighter->dmg.x18A8 = 0.0f;
    fighter->dmg.x18B4_armor = 0.0f;
    fighter->dmg.x18a0 = 0.0f;

    fighter->x221A_flag.bits.b7 = 0;
    fighter->x221B_flag.bits.b0 = 0;
    fighter->x221C_flag.bits.b3 = 0;

    fighter->x19B4_shieldUnk = 0.0f;
    fighter->x19B8_shieldUnk = 0.0f;

    fighter->x221D_flag.bits.b5 = 0;
    fighter->x2218_flag.bits.b3 = 0;
    fighter->x2218_flag.bits.b6 = 0;
    fighter->x221C_flag.bits.b4 = 0;


    fighter->x1A6A = 0;

    fighter->x221D_flag.bits.b7 = 0;
    fighter->x221E_flag.bits.b0 = 0;
    fighter->x221E_flag.bits.b1 = 0;
    fighter->x221E_flag.bits.b2 = 0;
    fighter->x221F_flag.bits.b1 = 0;
    fighter->x221E_flag.bits.b5 = 0;
    fighter->x221E_flag.bits.b6 = 0;
    fighter->x2220_flag.bits.b3 = 0;
    fighter->x2220_flag.bits.b7 = 0;

    fighter->x209C = 0;

    fighter->x2223_flag.bits.b0 = 0;
    fighter->x2222_flag.bits.b3 = 0;
    fighter->x2224_flag.bits.b5 = 0;
    fighter->x2225_flag.bits.b1 = 0;
    fighter->x2225_flag.bits.b4 = 0;

    func_8004CBF4(&fighter->x6F0_collData);

    func_800DEEA8(fighterObj);

    fighter->x2138_smashSinceHitbox = -1.0f;
    fighter->x2224_flag.bits.b4 = 0;

    if ((arg2 & 0x40000) == 0) {
        fighter->x221E_flag.bits.b3 = 1;
    } else if (fighter->x221E_flag.bits.b3 == 0U) {
        func_8007F578(fighterObj);
    }

    if ((arg2 & 0x400000) == 0) {
        fighter->x221E_flag.bits.b4 = 1;
    }

    if ((arg2 & 0x4000000) == 0) {
        fighter->x2225_flag.bits.b2 = 1;
    }

    if ((arg2 & 1) == 0) {
        fighter->x221A_flag.bits.b4 = 0;
    }

    if ((arg2 & 0x1000) == 0) {
        func_800C0134(fighter);
    }

    if (((arg2 & 2) == 0) && (fighter->x2219_flag.bits.b0 != 0U)) {
        func_8007DB24(fighterObj);
    }

    if (((arg2 & 0x2000) == 0) && ((u32) fighter->x20A0 != 0U)) {
        HSD_JObjRemoveAll(fighter->x20A0);
        fighter->x20A0 = 0U;
    }

    if (fighter->xE0_ground_or_air == 0) {
        if (fighter->x4_fighterKind == 9) {
            fighter->sa.peach.x222C = 1;
        }
        fighter->x2221_flag.bits.b5 = 0;
        fighter->x2221_flag.bits.b7 = 1;
        fighter->x2221_flag.bits.b6 = 1;
        fighter->x2224_flag.bits.b1 = 0;
        fighter->x2227_flag.bits.b1 = 0;
        fighter->x213C = -1;

        if (fighter->x2227_flag.bits.b4 != 0U) {
            func_8003FE1C(fighter->xC_playerID, fighter->x221F_flag.bits.b4);
            fighter->x2227_flag.bits.b4 = 0;
        }
        fighter->x2227_flag.bits.b5 = 0;
        func_80040330(fighter->xC_playerID, fighter->x221F_flag.bits.b4, fighter->x2140);
        fighter->x2140 = 0.0f;
        fighter->x2228_flag.bits.b6 = 0;
        fighter->x2180 = 6;

    }

    if ((new_action_state_index != 0xE) && (new_action_state_index != 0xF) && (new_action_state_index != 0x10) && (new_action_state_index != 0x11)) {
        fighter->x196C_hitlag_mult = 0.0f;
    }

    if ((arg2 & 0x200) == 0) {
        func_80088884(fighter);
        func_800888E0(fighter);
        func_800887CC(fighter);
    }

    if ((arg2 & 0x20000) == 0) {
        fighter->x2100 = -1;
    }
    if ((arg2 & 0x8000) == 0) {
        fighter->x209A = 0;
    }

    fighter->x2222_flag.bits.b7 = 0;

    if ((arg2 & 0x100000) != 0) {
        fighter->x100 = 0.0f;
    } else {
        fighter->x100 = -1.0f;
    }

    if ((arg2 & 0x1000000) == 0) {
        fighter->x221C_u16_y = 0;
    }

    fighter->x6BC_inputStickangle = 0.0f;

    func_8007592C(fighter, 0, 0.0f);
    func_80075AF0(fighter, 0, (HALF_PI * fighter->x2C_facing_direction));
    func_80075CB4(fighter, 0, 0.0f);

    if (new_action_state_index >= fighter->x18) {
        new_action_state = &fighter->x20_actionStateList[(new_action_state_index - fighter->x18)];
    } else {
        new_action_state = &fighter->x1C_actionStateList[new_action_state_index];
    }
    

    if (fighter->xE0_ground_or_air == GA_Ground) {
        if ((arg2 & 0x40) == 0) {
            if (new_action_state->x9_flags.bits.b1 != 0  && fighter->dmg.x18C8 == -1) {
                if (p_ftCommonData->x814 > 0) {
                    fighter->dmg.x18C8 = p_ftCommonData->x814;
                } else {
                    fighter->dmg.x18C8 = 1;
                }
            }
        }
    }

    volatile_integer = fighter->x2070_int;
    func_800890D0(fighter, new_action_state->move_id);
    func_800895E0(fighter, new_action_state->x4_flags);
    fighter->x2225_flag.bits.b3 = new_action_state->x9_flags.bits.b0;

    if (fighter->x2226_flag.bits.b4 != 0U) {
        if (fighter->x2071.bits.b5 != 0U) {
            func_800C8B2C(fighter, 0x7E, 0);
        }
        if (fighter->x2071.bits.b6 != 0U) {
            func_800C8B2C(fighter, 0x7F, 0);
        }
    }

    if (fighter->cb.x21EC_callback) {
        fighter->cb.x21EC_callback(fighterObj);
        fighter->cb.x21EC_callback = 0U;
    }
    

    if ((arg2 & 0x2000000) == 0) {
        func_80037C60(fighterObj, volatile_integer);
    }

    fighter->x14_action_id = new_action_state->action_id;
    fighter->x89C = arg9;
    fighter->x8A0 = arg9;

    fighter->x894 = (arg8 - fighter->x89C);
    fighter->x898 = 0.0f;

    if ((fighter->x594_animCurrFlags1.bits.b0) || (fighter->x594_animCurrFlags1.bits.b5)) {
        animflags_bool = TRUE;
    } else {
        animflags_bool = FALSE;
    }

    if (fighter->x14_action_id != -1) {
        bone_index = fighter->x596_bits.x7;
        if ((arg2 & 0x200000) != 0) {
            fighter->x2223_flag.bits.b0 = 1;
            fighter->x104 = 0x14;
            fighter->x89C = 0.0f;
            arg9 = 0.0f;
        }

        if (otherObj != 0U) {
            Fighter* otherFighter = otherObj->user_data;
            unk_struct_x18 = &otherFighter->x24[fighter->x14_action_id];
            unk_byte_ptr = &otherFighter->x28[fighter->x14_action_id << 1];
        } else {
            unk_struct_x18 = &fighter->x24[fighter->x14_action_id];
            unk_byte_ptr = &fighter->x28[fighter->x14_action_id << 1];
        }
        fighter->x594_s32 = unk_struct_x18->x10_animCurrFlags;
        func_8009E7B4(fighter, unk_byte_ptr);
        if ((arg2 & 0x20000000) == 0) {

            if (otherObj != 0U) {
                func_80085CD8(fighter, otherObj->user_data, fighter->x14_action_id);
                func_8007B8CC(fighter, otherObj);
            } else {
                func_80085CD8(fighter, fighter, fighter->x14_action_id);
            }
            fighter->x3EC = unk_struct_x18->xC;
            fighter->x3F0 = 0;

            
            if (arg8) {
                if (fighter->x590 != 0U) {
                    func_8006EBE8(fighterObj, arg8 - arg9, arg9, pickValue(argA, unk_byte_ptr));
                }
                func_8006E9B4(fighterObj);
                if (fighter->x594_animCurrFlags1.bits.b0 != 0U) {
                    fighter->x6B0.z = 0.0f;
                    fighter->x6B0.y = 0.0f;
                    fighter->x6B0.x = 0.0f;
                    fighter->x6A4_transNOffset.z = 0.0f;
                    fighter->x6A4_transNOffset.y = 0.0f;
                    fighter->x6A4_transNOffset.x = 0.0f;
                    fighter->x698 = fighter->x68C_transNPos;
                }
                
                if (fighter->x594_animCurrFlags1.bits.b5 != 0U) {
                    fighter->x6E4.z = 0.0f;
                    fighter->x6E4.y = 0.0f;
                    fighter->x6E4.x = 0.0f;
                    fighter->x6D8.z = 0.0f;
                    fighter->x6D8.y = 0.0f;
                    fighter->x6D8.x = 0.0f;
                    fighter->x6CC = fighter->x6C0;
                }
                fighter->x3E4 = -arg8;
            } else {
                if (fighter->x590 != 0U) {
                    func_8006EBE8(fighterObj, arg8, arg9, pickValue(argA, unk_byte_ptr));
                }
                fighter->x3E4 = 0.0f;
            }

            func_8006E9B4(fighterObj);
            if ((bone_index != 0) && (*unk_byte_ptr != 0U)) {
                HSD_JObj* temp_joint = fighter->x5E8_fighterBones[bone_index].x4_jobj2;
                HSD_JObjGetTranslation(temp_joint, &translation);
                HSD_JObjSetTranslate(fighter->x5E8_fighterBones[bone_index].x0_jobj, &translation);
                HSD_JObjGetRotation(temp_joint, &quat);
                func_8007584C(fighter->x5E8_fighterBones[bone_index].x0_jobj, &quat);
            }

            if (fighter->x594_animCurrFlags1.bits.b0 != 0U) {
                if (!arg8) {
                    fighter->x6B0.z = 0.0f;
                    fighter->x6B0.y = 0.0f;
                    fighter->x6B0.x = 0.0f;
                    fighter->x6A4_transNOffset.z = 0.0f;
                    fighter->x6A4_transNOffset.y = 0.0f;
                    fighter->x6A4_transNOffset.x = 0.0f;
                    fighter->x698 = fighter->x68C_transNPos;
                } else if (((arg2 & 0x20) == 0) && (fighter->xE0_ground_or_air == GA_Ground)) {
                    f32 temp_vel = fighter->x6A4_transNOffset.z * fighter->x2C_facing_direction;
                    fighter->x80_self_vel.x = temp_vel;
                    fighter->xEC_ground_vel = temp_vel;
                }
            }

            if (fighter->x594_animCurrFlags1.bits.b5 != 0U) {
                if (!arg8) {
                    fighter->x6E4.z = 0.0f;
                    fighter->x6E4.y = 0.0f;
                    fighter->x6E4.x = 0.0f;
                    fighter->x6D8.z = 0.0f;
                    fighter->x6D8.y = 0.0f;
                    fighter->x6D8.x = 0.0f;
                    fighter->x6CC = fighter->x6C0;
                } else if (((arg2 & 0x20) == 0) && (fighter->xE0_ground_or_air == GA_Ground)) {
                    f32 temp_vel = fighter->x6D8.z * fighter->x2C_facing_direction;
                    fighter->x80_self_vel.x = temp_vel;
                    fighter->xEC_ground_vel = temp_vel;
                }
            }
            if ((arg2 & 0x4000) != 0) {
                func_8007349C(fighterObj);
            } else if (arg8) {
                func_80073354(fighterObj);
            } else {
                func_800C0408(fighterObj);
                func_80073240(fighterObj);
            }
        } else {
            fighter->x14_action_id = -1;
        }
    }
    if (fighter->x14_action_id == -1) {
        fighter->x594_s32 = 0;
        func_80070758(other_jobj);
        func_80070758(fighter->x8AC_animSkeleton);
        fighter->x3EC = 0;
        fighter->x8A4 = 0.0f;
        fighter->x8A8 = 0.0f;
    }

    if (animflags_bool) {
        if (!fighter->x594_animCurrFlags1.bits.b0 && !fighter->x594_animCurrFlags1.bits.b0) {
            func_8007CC78(fighter->x110_attr.x138_DashrunTerminalVelocity, fighter);
        }
    }

    fighter->cb.x21A0_callback_Anim = new_action_state->cb_Anim;
    fighter->cb.x219C_callback_IASA = new_action_state->cb_Input;
    fighter->cb.x21A4_callback_Phys = new_action_state->cb_Physics;
    fighter->cb.x21A8_callback_Coll = new_action_state->cb_Collision;
    fighter->cb.x21AC_callback_Cam = new_action_state->cb_Camera;

    fighter->cb.x21B0_callback_Accessory1 = 0;
    fighter->cb.x21BC_callback_Accessory4 = 0;
    fighter->cb.x21C0_callback_OnGiveDamage = 0;
    fighter->cb.x21C4_callback_OnShieldHit = 0;
    fighter->cb.x21C8_callback_OnReflectHit = 0;
    fighter->cb.x21D0_callback_EveryHitlag = 0;
    fighter->cb.x21CC_callback = 0;
    fighter->cb.x21D8_callback_ExitHitlag = 0;
    fighter->cb.x21D4_callback_EnterHitlag = 0;
    fighter->cb.x21DC_callback_OnTakeDamage = 0;
    fighter->cb.x21F0_callback = 0;
    fighter->cb.x21F4_callback = 0;
    fighter->cb.x21F8_callback = 0;
    fighter->cb.x21E4_callback_OnDeath2 = 0;
    
}


void Fighter_8006A1BC(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;

    if (!fighter->x221F_flag.bits.b3) {
        if (fighter->dmg.x1954 > 0.0f) {
            fighter->dmg.x1954 -= 1.0f;
            if (fighter->dmg.x1954 <= 0.0f) {
                fighter->dmg.x1954 = 0.0f;
                if (!fighter->x221A_flag.bits.b2 && !fighter->x2219_flag.bits.b7) {
                    func_8006D10C(fighterObj);
                }
            }
        }

        if (fighter->x221A_flag.bits.b1) {
            func_8006CFE0(fighterObj);
            fighter->x221A_flag.bits.b1 = 0;
        }

        if (fighter->dmg.x195c_hitlag_frames > 0.0f) {
            fighter->dmg.x195c_hitlag_frames -= 1.0f;
            if (fighter->dmg.x195c_hitlag_frames <= 0.0f) {
                f32 temp;
                fighter->dmg.x195c_hitlag_frames = 0.0f;
                if (fighter->x221A_flag.bits.b3) {
                    func_80090718(fighter);
                    fighter->x221A_flag.bits.b3 = 0;
                }
                if ((!fighter->dmg.x1954) && !fighter->x2219_flag.bits.b7) {
                    func_8006D10C(fighterObj);
                }
                fighter->x221A_flag.bits.b2 = 0;
            }
        }
        func_800C37A0(fighterObj);

        while (fighter->x200C != 0) {
            func_800D14E4(fighterObj);
            fighter->x200C--;
        }

        while (fighter->x2010 != 0) {
            func_800D1E80(fighterObj);
            fighter->x2010--;
        }

        func_800819A8(fighterObj);
        fighter->x2219_flag.bits.b6 = fighter->x2219_flag.bits.b5;
    }
}


void Fighter_8006A360(HSD_GObj* fighterObj) {
    
    Vec vec1;
    Fighter* fighter = fighterObj->user_data;
    s32 unused;

    if (!fighter->x221F_flag.bits.b3) {
        fighter->xC8_pos_delta.x = fighter->xB0_pos.x - fighter->xBC_prevPos.x;
        fighter->xC8_pos_delta.y = fighter->xB0_pos.y - fighter->xBC_prevPos.y;
        fighter->xC8_pos_delta.z = fighter->xB0_pos.z - fighter->xBC_prevPos.z;

        fighter->xBC_prevPos = fighter->xB0_pos;

        if (fighter->dmg.x18C8 != -1 && fighter->dmg.x18C8 > 0) {
            fighter->dmg.x18C8--;
            if (fighter->dmg.x18C8 == 0) {
                fighter->dmg.x18c4_source_ply = 6;
                fighter->dmg.x18C8 = -1;
                fighter->dmg.x18D0 = -0xA;
            }
        }

        if (fighter->x1990) {
            fighter->x1990--;
            if (fighter->x1990 == 0 && !fighter->x2221_flag.bits.b0) {
                fighter->x198C = fighter->x1994 != 0 ? 1 : 0;

                if (func_800C0694(fighter) == 9) {
                    func_800C0200(fighter, 9);
                }
            }
        }

        if (fighter->x1994) {
            fighter->x1994--;
            if (fighter->x1994 == 0) {
                fighter->x198C = (fighter->x2221_flag.bits.b0 || fighter->x1990 != 0) ? 2 : 0;

                if (func_800C0694(fighter) == 9) {
                    func_800C0200(fighter, 9);
                }
            }
        }

        if (fighter->x221D_flag.bits.b6) {
            if (fighter->x2004) {
                fighter->x2004--;
                if (fighter->x2004 == 0) {
                    fighter->x221D_flag.bits.b6 = 0;
                    if (func_800C0694(fighter) == 0x6B) {
                        func_800C0200(fighter, 0x6B);
                    }
                } else if (fighter->x2004 == func_8026B588()) {
                    func_800880D8(fighter);
                }
            }
        }

        if (fighter->x2220_flag.bits.b5 || fighter->x2220_flag.bits.b6) {
            if (fighter->x2008) fighter->x2008--;

            if (fighter->x2008 == 0) {
                if (fighter->x2220_flag.bits.b5) {
                    func_800D1A8C(fighterObj);
                } else if (fighter->x2220_flag.bits.b6) {
                    func_800D237C(fighterObj);
                }
            }
        }

        if (fighter->x197C) {
            if (fighter->x2014) {
                fighter->x2014--;
                if (fighter->x2014 == 0) {
                    func_8007F8E8(fighterObj);
                    func_8026A8EC(fighter->x197C);
                    func_8007F9B4(fighterObj);
                }
            }
        }

        if (fighter->x2223_flag.bits.b7) {
            if (fighter->x2028) {
                fighter->x2028--;
                if (!fighter->x2028 || fighter->x202C <= 0) {
                    func_800C8540(fighterObj);
                }
            }
        }

        
        if (fighter->x2227_flag.bits.b3) {
            if (fighter->x2034) {
                fighter->x2034--;
                if (!fighter->x2034 || fighter->x2038 <= 0) {
                    func_800C9034(fighterObj);
                    return;
                }
            }
        }

        if (fighter->x1980) {
            fighter->x2018--;
            fighter->x201C--;

            if (fighter->x201C == 0) {
                Fighter_TakeDamage_8006CC7C(fighter, p_ftCommonData->x6F4_unkDamage);
                fighter->x201C = p_ftCommonData->x6F8;
            }

            if (fighter->x2018 <= 0) {
                vec1 = lbl_803B7488;

                func_8007F8E8(fighterObj);
                func_8026ABD8(fighter->x1980, &vec1, 0.0f);
                func_8007FF74(fighterObj);
            }
        }


        if (fighter->x2226_flag.bits.b4) {
            if (fighter->x2030) {
                fighter->x2030--;
                if (fighter->x2030 == 0) {
                    func_800C8A64(fighterObj);
                    return;
                }
                if (!fighter->x2226_flag.bits.b3 && fighter->x2030 == p_ftCommonData->x7D0 && func_800C8B2C(fighter, 0x7D, 0)) {
                    fighter->x2226_flag.bits.b7 = 1;
                }
            }
        }

        if (fighter->x2221_flag.bits.b4) {
            if (fighter->x2104) {
                fighter->x2104--;
                if (fighter->x2104 == 0) {
                    fighter->x2221_flag.bits.b4 = 0;

                    if (fighter->x1974_heldItem && itGetKind(fighter->x1974_heldItem) == 0x67) {
                        fighter->x2221_flag.bits.b5 = 1;
                        func_800968C8(fighterObj);
                    } else {
                        func_80095744(fighterObj, 0);
                    }
                    
                }
            }
        }

        if (!fighter->x221F_flag.bits.b4 && func_80031144() == 1.0f) {
            if (fighter->dmg.x1830_percent < p_ftCommonData->x7B0) {
                if (func_802FC998(fighter->xC_playerID) && (Player_GetMoreFlagsBit3(fighter->xC_playerID) != 0)) {
                    fighter->dmg.x1910++;
                } else {
                    fighter->dmg.x1910 = 0;
                }

                if (fighter->dmg.x1910 >= p_ftCommonData->x7AC) {
                    Fighter_TakeDamage_8006CC7C(fighter, p_ftCommonData->x7B4_unkDamage);
                    fighter->dmg.x1910 = 0;
                }
            }
        }

        if (fighter->dmg.x18F0) {
            fighter->dmg.x18F0--;
            if (fighter->dmg.x1830_percent > 0.0f) {
                fighter->dmg.x1830_percent--;
                func_80088640(fighter, 0x7D, 0x7F, 0x40);
                Player_SetHPByIndex(fighter->xC_playerID, fighter->x221F_flag.bits.b4, fighter->dmg.x1830_percent);
                func_80040B8C(fighter->xC_playerID, fighter->x221F_flag.bits.b4, 1);
            }

            if (fighter->dmg.x1830_percent <= 0.0f) {
                fighter->dmg.x1830_percent = 0.0f;
                fighter->dmg.x18F0 = 0;
            }

            if (fighter->dmg.x18F0 == 0) {
                if (func_800C0694(fighter) == 8) {
                    func_800C0200(fighter, 8);
                }
                func_8007ECD4(fighter, 2);
            }
        }

        if (fighter->x1974_heldItem) {
            if (itGetKind(fighter->x1974_heldItem) != 0x1C) {
                (void)fighter;
            } else {
                func_800C511C(fighterObj);
            }
        }

        if (fighter->dmg.x18fa_model_shift_frames) {
            fighter->dmg.x18fa_model_shift_frames--;
            fighter->dmg.x18FC++;
            if (fighter->dmg.x18FC >= fighter->dmg.x18FD) {
                fighter->dmg.x18FC = 0;
            }
        }

        if (lbl_803C1DB4[fighter->x4_fighterKind]) {
            lbl_803C1DB4[fighter->x4_fighterKind](fighterObj);
        }

        if (fighter->cb.x21CC_callback) {
            fighter->cb.x21CC_callback(fighterObj);
        }

        if (!fighter->x2219_flag.bits.b5) {
            if (fighter->x209A > 1  &&  !fighter->x221D_flag.bits.b4) {
                fighter->x209A--;
            }
            if (fighter->x2223_flag.bits.b0) {
                if (fighter->x104 == 0x14U) {
                    func_8006F0FC(fighterObj, 0.0f);
                } else {
                    fighter->x89C += fighter->x8A0;
                }
                fighter->x104--;
                if (fighter->x104 == 0) {
                    func_8006F0FC(fighterObj, fighter->x89C);
                    fighter->x104 = 0x14U;
                }
            }

            if (fighter->x2138_smashSinceHitbox != -1.0f) {
                fighter->x2138_smashSinceHitbox++;
            }

            if (fighter->dmg.x18ac_time_since_hit != -1) {
                fighter->dmg.x18ac_time_since_hit++;
            }
            func_8006EBA4(fighterObj);
            func_800D71D8(fighterObj);
            func_800764DC(fighterObj);

            if (!fighter->x221C_flag.bits.b6) {
                func_800411C4(fighter->xC_playerID, fighter->x221F_flag.bits.b4);
            }
            func_800DEF38(fighterObj);

            if (fighter->cb.x21A0_callback_Anim) {
                fighter->cb.x21A0_callback_Anim(fighterObj);
            }
            
        }

        func_8007E0E4(fighterObj);
        func_800C0408(fighterObj);
    }

}

void Fighter_8006ABA0(HSD_GObj* fighterObj) {
    Fighter* fp = fighterObj->user_data;
    if (!fp->x221F_flag.bits.b3 && func_800A2040()) {
        func_800B3900(fighterObj);
    }
}


//https://decomp.me/scratch/A7CgG
void Fighter_UnkIncrementCounters_8006ABEC(HSD_GObj* fighterObj) {
    
    Fighter* fighter = fighterObj->user_data;

    if (func_800CAE80()) {
        fighter->x68A = fighter->x685;
        fighter->x685 = 0;
    } else if (fighter->x685 < 0xFF) {
        fighter->x685++;
    }

    if (func_800D6928(fighter)) {
        fighter->x68B = fighter->x686;
        fighter->x686 = 0;
    } else if (fighter->x686 < 0xFF) {
        fighter->x686++;
    }

    if (func_800D688C(fighter)) {
        fighter->x687 = 0;
    } else if (fighter->x687 < 0xFF) {
        fighter->x687++;
    }
    if (func_800964FC(fighter)) {
        fighter->x688 = 0;
    } else if (fighter->x688 < 0xFF) {
        fighter->x688++;
    }

    if (func_800D67C4(fighter)) {
        fighter->x689 = 0;
    } else if (fighter->x689 < 0xFF) {
        fighter->x689++;
    }
}


void Fighter_Spaghetti_8006AD10(HSD_GObj* fighterObj) {

    s32 unused[10];
    Fighter* fighter = fighterObj->user_data;

    s32 temp0;
    s32 temp1;
    s32 temp2; 

    f32 tempf1;
    f32 tempf0;

    if (!fighter->x221F_flag.bits.b3) {
        if (!fighter->x2224_flag.bits.b2) {
            
            if (!fighter->x221D_flag.bits.b3) {
                fighter->x628_lstick_x2 = fighter->x630;
                fighter->x62C_lstick_y2 = fighter->x634;
                fighter->x640_lsubStick_x2 = fighter->x648;
                fighter->x644_lsubStick_y2 = fighter->x64C;
                fighter->x654 = fighter->x658;
                fighter->x660 = fighter->x664;
                fighter->x221D_flag.bits.b3 = 1;
            } else {
                fighter->x628_lstick_x2 = fighter->x620_lstick_x;
                fighter->x62C_lstick_y2 = fighter->x624_lstick_y;
                fighter->x640_lsubStick_x2 = fighter->x638_lsubStick_x;
                fighter->x644_lsubStick_y2 = fighter->x63C_lsubStick_y;
                fighter->x654 = fighter->x650;
                fighter->x660 = fighter->x65C;
            }

            if (func_800A2040(fighter)) {

                fighter->x620_lstick_x = func_800A17E4(fighter);
                fighter->x624_lstick_y = func_800A1874(fighter);
                if (g_debugLevel < 3  &&  func_8016B41C() == 0) {
                    fighter->x638_lsubStick_x = func_800A1994(fighter);
                    fighter->x63C_lsubStick_y = func_800A1A24(fighter);
                }
                else {
                    fighter->x638_lsubStick_x = 0.0f;
                    fighter->x63C_lsubStick_y = 0.0f;
                }

                tempf0 = func_800A1904(fighter);
                tempf1 = func_800A1948(fighter);

                fighter->x650 = (tempf0> tempf1) ? tempf0 : tempf1;

            } else {

                fighter->x620_lstick_x = HSD_PadRumbleData[fighter->x618_player_id].nml_stickX;
                fighter->x624_lstick_y = HSD_PadRumbleData[fighter->x618_player_id].nml_stickY;

                if (g_debugLevel < 3  &&  func_8016B41C() == 0) {
                    fighter->x638_lsubStick_x = HSD_PadRumbleData[fighter->x618_player_id].nml_subStickX;
                    fighter->x63C_lsubStick_y = HSD_PadRumbleData[fighter->x618_player_id].nml_subStickY;
                } else {
                    fighter->x638_lsubStick_x = 0.0f;
                    fighter->x63C_lsubStick_y = 0.0f;
                }

                tempf1 = HSD_PadRumbleData[fighter->x618_player_id].nml_analogR;
                tempf0 = HSD_PadRumbleData[fighter->x618_player_id].nml_analogL;

                fighter->x650 = (tempf0 > tempf1) ? tempf0 : tempf1;
            }

            if (fabs_inline(fighter->x620_lstick_x) <= p_ftCommonData->x0) {
                fighter->x620_lstick_x = 0.0f; 
            }

            if (fabs_inline(fighter->x624_lstick_y) <= p_ftCommonData->x4) {
                fighter->x624_lstick_y = 0.0f;
            }

            if (fabs_inline(fighter->x638_lsubStick_x) <= p_ftCommonData->x0) {
                fighter->x638_lsubStick_x = 0.0f;
            }
            
            if (fabs_inline(fighter->x63C_lsubStick_y) <= p_ftCommonData->x4) {
                fighter->x63C_lsubStick_y = 0.0f;
            }

            if (fighter->x650 <= p_ftCommonData->x10) {
                fighter->x650 = 0.0f;
            }

            
            if (func_800A2040(fighter)) {
                fighter->x65C = func_800A198C(fighter);
            } else {
                fighter->x65C = HSD_PadRumbleData[fighter->x618_player_id].button;
            }

            if (func_8016B0FC()) {
                fighter->x650 = 0.0f;
                if (func_800A2040(fighter)) {
                    fighter->x65C = (fighter->x65C & 0xD00);
                } else {
                    fighter->x65C = (fighter->x65C & 0x100);
                }
            } else {
                if ((fighter->x65C & 0x60)) {
                    fighter->x65C = (s32) (fighter->x65C | 0x80000000);
                    fighter->x650 = 1.0f;
                } else if (fighter->x650) {
                    fighter->x65C = (fighter->x65C | 0x80000000);
                }
                if (func_801A45E8(0) == 0) {
                    if ((fighter->x65C & 0x10)) {
                        fighter->x65C = (fighter->x65C | 0x80000000 | 0x100);
                        fighter->x650 = p_ftCommonData->x14;
                    }
                }
            }

            temp0 = fighter->x65C;
            temp1 = fighter->x660 ^ temp0;
            temp0 = temp0 & temp1;
            temp2 = fighter->x660 & temp1;

            if (fighter->x2219_flag.bits.b5) {
                fighter->x668 |= temp0;
                fighter->x66C |= temp2;
            } else {
                fighter->x668 = temp0;
                fighter->x66C = temp2;
            }

            fighter->x676_x++;
            if (fighter->x676_x > 0xFE) {
                fighter->x676_x = 0xFE;
            }

            if (fighter->x620_lstick_x >= p_ftCommonData->x8_someStickThreshold) {
                if (fighter->x628_lstick_x2 >= p_ftCommonData->x8_someStickThreshold) {
                    fighter->x670_timer_lstick_tilt_x++;
                    if (fighter->x670_timer_lstick_tilt_x > 0xFE) {
                        fighter->x670_timer_lstick_tilt_x = 0xFE;
                    }
                    fighter->x673++;
                    if (fighter->x673 > 0xFE) {
                        fighter->x673 = 0xFE;
                    }
                    fighter->x679_x++;
                    if (fighter->x679_x > 0xFE) {
                        fighter->x679_x = 0xFE;
                    }
                } else {
                    fighter->x676_x = 0;
                    fighter->x673 = 0;
                    fighter->x670_timer_lstick_tilt_x = 0;
                    fighter->x2228_flag.bits.b7 = 1;
                }
            } else if (fighter->x620_lstick_x <= -p_ftCommonData->x8_someStickThreshold) {
                if (fighter->x628_lstick_x2 <= -p_ftCommonData->x8_someStickThreshold) {
                    fighter->x670_timer_lstick_tilt_x++;
                    if (fighter->x670_timer_lstick_tilt_x > 0xFE) {
                        fighter->x670_timer_lstick_tilt_x = 0xFE;
                    }
                    fighter->x673++;
                    if (fighter->x673 > 0xFE) {
                        fighter->x673 = 0xFE;
                    }
                    fighter->x679_x++;
                    if (fighter->x679_x > 0xFE) {
                        fighter->x679_x = 0xFE;
                    }
                } else {
                    fighter->x676_x = 0;
                    fighter->x673 = 0;
                    fighter->x670_timer_lstick_tilt_x = 0;
                    fighter->x2228_flag.bits.b7 = 0;
                }
            } else {
                fighter->x679_x = 0xFEU;
                fighter->x673 = 0xFEU;
                fighter->x670_timer_lstick_tilt_x = 0xFEU;
            }
        

            fighter->x677_y++;
            if (fighter->x677_y > 0xFE) {
                fighter->x677_y = 0xFE;
            }
            
            if (fighter->x624_lstick_y >= p_ftCommonData->xC) {
                if (fighter->x62C_lstick_y2 >= p_ftCommonData->xC) {
                    fighter->x671_timer_lstick_tilt_y++;
                    if (fighter->x671_timer_lstick_tilt_y > 0xFE) {
                        fighter->x671_timer_lstick_tilt_y = 0xFE;
                    }
                    fighter->x674++;
                    if (fighter->x674 > 0xFE) {
                        fighter->x674 = 0xFE;
                    }
                    fighter->x67A_y++;
                    if (fighter->x67A_y > 0xFE) {
                        fighter->x67A_y = 0xFE;
                    }
                } else {
                    fighter->x677_y = 0;
                    fighter->x674 = 0;
                    fighter->x671_timer_lstick_tilt_y = 0;
                    fighter->x2229_b0 = 0;
                }
            } else if (fighter->x624_lstick_y <= -p_ftCommonData->xC) {
                if (fighter->x62C_lstick_y2 <= -p_ftCommonData->xC) {
                    fighter->x671_timer_lstick_tilt_y++;
                    if (fighter->x671_timer_lstick_tilt_y > 0xFE) {
                        fighter->x671_timer_lstick_tilt_y = 0xFE;
                    }
                    fighter->x674++;
                    if (fighter->x674 > 0xFE) {
                        fighter->x674 = 0xFE;
                    }
                    fighter->x67A_y++;
                    if (fighter->x67A_y > 0xFE) {
                        fighter->x67A_y = 0xFE;
                    }
                } else {
                    fighter->x677_y = 0;
                    fighter->x674 = 0;
                    fighter->x671_timer_lstick_tilt_y = 0;
                    fighter->x2229_b0 = 1;
                }
            } else {
                fighter->x67A_y = 0xFE;
                fighter->x674 = 0xFE;
                fighter->x671_timer_lstick_tilt_y = 0xFE;
            }
    
            if (func_8000D148(fighter->x628_lstick_x2, fighter->x62C_lstick_y2, fighter->x620_lstick_x, fighter->x624_lstick_y, 0.0f, 0.0f, p_ftCommonData->x8_someStickThreshold)) {
                fighter->x67A_y = 0;
                fighter->x679_x = 0;
            }
        
            fighter->x678++;
            if (fighter->x678 > 0xFE) {
                fighter->x678 = 0xFE;
            }
        
            if (fighter->x650 >= p_ftCommonData->x18) {
                if (fighter->x654 >= p_ftCommonData->x18) {
                    fighter->x672_input_timer_counter++;
                    if (fighter->x672_input_timer_counter > 0xFE) {
                        fighter->x672_input_timer_counter = 0xFE;
                    }
                    fighter->x675++;
                    if (fighter->x675 > 0xFE) {
                        fighter->x675 = 0xFE;
                    }
                    fighter->x67B++;
                    if (fighter->x67B > 0xFE) {
                        fighter->x67B = 0xFE;
                    }
                } else {
                    fighter->x67B = 0;
                    fighter->x678 = 0;
                    fighter->x675 = 0;
                    fighter->x672_input_timer_counter = 0;
                }
            } else {
                fighter->x67B = 0xFE;
                fighter->x675 = 0xFE;
                fighter->x672_input_timer_counter = 0xFE;
            }
        
            if (fighter->x668 & 0x100) {
                fighter->x683 = fighter->x67C;
                fighter->x67C = 0;
            } else if (fighter->x67C < 0xFF) {
                fighter->x67C++;
            }
        
            if (fighter->x668 & 0x200) {
                fighter->x67D = 0;
            } else if (fighter->x67D < 0xFF) {
                fighter->x67D++;
            }
        
            if (fighter->x668 & 0xC00) {
                fighter->x67E = 0;
            } else if (fighter->x67E < 0xFF) {
                fighter->x67E++;
            }
        
            if (fighter->x668 & 8) {
                fighter->x681 = 0;
            } else if (fighter->x681 < 0xFF) {
                fighter->x681++;
            }
        
            if (fighter->x668 & 4) {
                fighter->x682 = 0;
            } else if (fighter->x682 < 0xFF) {
                fighter->x682++;
            }
        
            if (fighter->x668 & 0x80000000) {
                fighter->x67F = 0;
            } else if (fighter->x67F < 0xFF) {
                fighter->x67F++;
            }
        
            if (fighter->x668 & 0x60) {
                fighter->x684 = fighter->x680;
                fighter->x680 = 0;
            } else if (fighter->x680 < 0xFF) {
                fighter->x680++;
            }
    
        }
    
        if (fighter->x221D_flag.bits.b4 || fighter->x2224_flag.bits.b2 || func_801A45E8(2)) {
            Fighter* same_fighter;
            fighter->x630 = fighter->x620_lstick_x;
            fighter->x634 = fighter->x624_lstick_y;
            fighter->x648 = fighter->x638_lsubStick_x;
            fighter->x64C = fighter->x63C_lsubStick_y;
            fighter->x658 = fighter->x650;
            fighter->x664 = fighter->x65C;
            fighter->x221D_flag.bits.b3 = 0;
    
            same_fighter = fighterObj->user_data;
    
            same_fighter->x650 = 
            same_fighter->x654 = 
            same_fighter->x638_lsubStick_x = 
            same_fighter->x63C_lsubStick_y = 
            same_fighter->x640_lsubStick_x2 = 
            same_fighter->x644_lsubStick_y2 = 
            same_fighter->x620_lstick_x = 
            same_fighter->x624_lstick_y = 
            same_fighter->x628_lstick_x2 = 
            same_fighter->x62C_lstick_y2 = 0.0f;
    
            same_fighter->x660 = 0;
            same_fighter->x66C = 0;
            same_fighter->x668 = 0;
            same_fighter->x65C = 0;
            
            same_fighter->x679_x = 
            same_fighter->x67A_y = 
            same_fighter->x67B = 
            same_fighter->x676_x = 
            same_fighter->x677_y = 
            same_fighter->x678 = 
            same_fighter->x673 = 
            same_fighter->x674 = 
            same_fighter->x675 = 
            same_fighter->x670_timer_lstick_tilt_x = 
            same_fighter->x671_timer_lstick_tilt_y =         
            same_fighter->x672_input_timer_counter = 0xFE;
    
            same_fighter->x67C = 
            same_fighter->x67D = 
            same_fighter->x67E = 
            same_fighter->x681 = 
            same_fighter->x682 = 
            same_fighter->x67F = 
            same_fighter->x680 = 
            same_fighter->x683 = 
            same_fighter->x684 = 
            same_fighter->x685 = 
            same_fighter->x686 = 
            same_fighter->x687 = 
            same_fighter->x688 = 
            same_fighter->x689 = 
            same_fighter->x68A = 
            same_fighter->x68B = 0xFF;
        }
    
        if (!fighter->x2219_flag.bits.b5) {
            if (fighter->x1980) {
               func_8007FFD8(fighter, p_ftCommonData->x6FC);
            }
            func_800DF0D0(fighterObj);
            func_8008031C(fighterObj);
            Fighter_UnkIncrementCounters_8006ABEC(fighterObj);
    
            if (fighter->cb.x219C_callback_IASA) {
                fighter->cb.x219C_callback_IASA(fighterObj);
            }
        }

    }
    
}


//// https://decomp.me/scratch/oFu1o
void Fighter_procUpdate(HSD_GObj* fighterObj, s32 dummy) {

    Fighter* fighter = fighterObj->user_data;
    Vec3 windOffset; 

    if (fighter->x221F_flag.bits.b3) return;
    
    
    if (!fighter->x2219_flag.bits.b5)
    {
        Vec3* p_kb_vel;
        Vec3* pAtkShieldKB;
        float kb_vel_x, atkShieldKB_X;
        Vec3 selfVel; 

        
        if (fighter->x2064_ledgeCooldown) fighter->x2064_ledgeCooldown -= 1;

        if (fighter->x2108) fighter->x2108 -= 1;
        
        func_800C0A98(fighterObj);

		if (fighter->cb.x21A4_callback_Phys) {
			fighter->cb.x21A4_callback_Phys(fighterObj);
        }

        p_kb_vel = &fighter->x8c_kb_vel;
		if ((kb_vel_x = p_kb_vel->x) != 0 || p_kb_vel->y != 0)
        {
            
			if (fighter->xE0_ground_or_air == GA_Air) 
            {
                
				float kb_vel_x = p_kb_vel->x;
				float kb_vel_y = p_kb_vel->y;

				if (fighter->x2228_flag.bits.b2) 
                {
                	p_kb_vel->x = func_8007CD6C(p_kb_vel->x, func_8007CDA4(fighter));
					p_kb_vel->y = func_8007CD6C(p_kb_vel->y, func_8007CDF8(fighter));
                }
                else 
                {
                    
                    float kb_angle = func_someCalcAngle_80022C30(kb_vel_y, kb_vel_x);
					float kb_vel_len = sqrtf(kb_vel_x * kb_vel_x + kb_vel_y * kb_vel_y);
					
                    if (kb_vel_len < p_ftCommonData->x204_knockbackFrameDecay) 
                    {
						p_kb_vel->y = 0; 
                        p_kb_vel->x = 0;
                    }
					else
                    {

						p_kb_vel->x -= p_ftCommonData->x204_knockbackFrameDecay * cosf(kb_angle);
                        p_kb_vel->y -= p_ftCommonData->x204_knockbackFrameDecay * sinf(kb_angle);
                    }
                }
                
				fighter->xF0_ground_kb_vel = 0; 
            }
			else
            {
                
                Vec3* pNormal = &fighter->x6F0_collData.x154_groundNormal;  
                struct attr* pAttr;
                
				if (fighter->xF0_ground_kb_vel == 0)
					fighter->xF0_ground_kb_vel = kb_vel_x;
                
                
                pAttr = &fighter->x110_attr; 
                func_8007CCA0(fighter,
                    /*effective friction - ground multiplier is usually 1. last factor was 1 when I looked*/
                    func_80084A40(fighter) * pAttr->x128_GroundFriction * p_ftCommonData->x200);

				// set knockback velocity to ground_kb_vel * surfaceTangent
                p_kb_vel->x =  pNormal->y * fighter->xF0_ground_kb_vel;
                p_kb_vel->y = -pNormal->x * fighter->xF0_ground_kb_vel;
            }
        }
        //Now handle the attacker's shield knockback in a similar way
        pAtkShieldKB = &fighter->x98_atk_shield_kb;
        if ((atkShieldKB_X = pAtkShieldKB->x) != 0 || pAtkShieldKB->y != 0)
        {
            
            if (fighter->xE0_ground_or_air == GA_Air)
            {
                
                float kb_x = pAtkShieldKB->x;
                float kb_y = pAtkShieldKB->y;
                float atkShieldKBAngle = func_someCalcAngle_80022C30(kb_y, kb_x);
                
                float atkShieldKB_len = sqrtf(kb_x*kb_x + kb_y*kb_y);
                
                if (atkShieldKB_len < p_ftCommonData->x3E8_shieldKnockbackFrameDecay)
                {
                    // BUG IN THE MELEE CODE THAT CAUSES THE INVISIBLE CEILING GLITCH
                    // The next line should be 'pAtkShieldKB->y = 0', but instead it is:
                    p_kb_vel->y = 0;
                    pAtkShieldKB->x = 0;
                }
                else
                {
                    // again, the better implementation would be:
                    // *pAtkShieldKB *= (atkShieldKB_len - p_stc_ftcommon->x3e8_shield_kb_frameDecay)/atkShieldKB_len
                    //float atkShieldKBAngle = atan2_80022C30(pAtkShieldKB->y, pAtkShieldKB->x);
                    pAtkShieldKB->x -= p_ftCommonData->x3E8_shieldKnockbackFrameDecay * cosf(atkShieldKBAngle);
                    pAtkShieldKB->y -= p_ftCommonData->x3E8_shieldKnockbackFrameDecay * sinf(atkShieldKBAngle);
                }
                fighter->xF4_ground_attacker_shield_kb_vel = 0;
            }
            else
            {
                
                float effectiveFriction;
                Vec3* pNormal = &fighter->x6F0_collData.x154_groundNormal; // ground_normal offset inside fighter is 0x844, surface normal points out of the surface. 
                struct attr* pAttr;
                
                if (fighter->xF4_ground_attacker_shield_kb_vel == 0)
                    fighter->xF4_ground_attacker_shield_kb_vel = atkShieldKB_X;
                
                pAttr = &fighter->x110_attr; 
                
                func_8007CE4C(fighter,
                    /* effectiveFriction - the last constant variable differs from the one for the knockback friction above*/
                    func_80084A40(fighter) * pAttr->x128_GroundFriction * p_ftCommonData->x3EC_shieldGroundFrictionMultiplier);
                
                pAtkShieldKB->x =  pNormal->y * fighter->xF4_ground_attacker_shield_kb_vel;
                pAtkShieldKB->y = -pNormal->x * fighter->xF4_ground_attacker_shield_kb_vel;
            }
        }

        
		fighter->xEC_ground_vel += fighter->xE4_ground_accel_1 + fighter->xE8_ground_accel_2;
        
		fighter->xE8_ground_accel_2 = 0;
        fighter->xE4_ground_accel_1 = 0;

        //self_vel += anim_vel
		PSVECAdd(&fighter->x80_self_vel, &fighter->x74_anim_vel, &fighter->x80_self_vel);
        
		fighter->x74_anim_vel.z = 0;
        fighter->x74_anim_vel.y = 0;
        fighter->x74_anim_vel.x = 0;
		
		//copy selfVel into a stack storage variable
		selfVel = fighter->x80_self_vel;
		
		// TODO: these double_lower_32bit variables are probably integer counters that get decremented each frame,
        // but I was not able to trigger the following condition.
		// The double value construction then is only used as an interpolation tool between selfVel and some UnkVel2.
		if (fighter->dmg.x1948 != 0)
        {
            // The compiler casts an u32 integer 'val' to a double type using
            // double v = *(double*)&(0x43300000_00000000 | val ^ 0x80000000) - *(double*)&43300000_80000000
            // which is all that happens in the lengthy assembly generated by this
			float C = 1.0f - (float)fighter->dmg.x194C / (float)fighter->dmg.x1948;
			
            selfVel.x = C * (fighter->x80_self_vel.x - fighter->xA4_unk_vel.x) + fighter->xA4_unk_vel.x;
            selfVel.y = C * (fighter->x80_self_vel.y - fighter->xA4_unk_vel.y) + fighter->xA4_unk_vel.y;
            
            fighter->dmg.x194C--;
			if (fighter->dmg.x194C == 0)
				fighter->dmg.x1948 = 0;
        }

		// add some horizontal+depth offset to the position? Why is there no vertical component?
		fighter->xB0_pos.x += fighter->xF8_playerNudgeVel.x;
		fighter->xB0_pos.z += fighter->xF8_playerNudgeVel.y;
        
        if (fighter->x2222_flag.bits.b6 && !fighter->x2222_flag.bits.b7)
        {
            s32 bit;
            
            // fighter->xD4_unk_vel += selfVel
			PSVECAdd(&fighter->xD4_unk_vel, &selfVel, &fighter->xD4_unk_vel);
			
            fighter->xD4_unk_vel.x += p_kb_vel->x;
            fighter->xD4_unk_vel.y += p_kb_vel->y;
            
            if (fighter->x2210_ThrowFlags.b2)
            {
			    fighter->x2210_ThrowFlags.b2 = 0;
                bit = 1;
            }
            else
                bit = 0;
			

			if (bit || func_80070FD0(fighter) || fighter->x594_animCurrFlags1.bits.b7)
            {
                
                // fighter->xB0_position += fighter->xD4_unk_vel
				PSVECAdd(&fighter->xB0_pos, &fighter->xD4_unk_vel, &fighter->xB0_pos);
				// TODO: we set this velocity to 0 after applying it -> Is this SDI or ASDI?
                fighter->xD4_unk_vel.z = 0;
                fighter->xD4_unk_vel.y = 0;
                fighter->xD4_unk_vel.x = 0;
            }
			// fighter->xB0_position += *pAtkShieldKB
            PSVECAdd(&fighter->xB0_pos, (Vec3*)pAtkShieldKB, &fighter->xB0_pos);
        }
		else
        {
            //fighter@r31.position@0xB0.xyz += selfVel + pAtkShieldKB
			PSVECAdd(&fighter->xB0_pos, &selfVel, &fighter->xB0_pos);
			fighter->xB0_pos.x += p_kb_vel->x;
            fighter->xB0_pos.y += p_kb_vel->y;
            PSVECAdd(&fighter->xB0_pos, (Vec3*)pAtkShieldKB, &fighter->xB0_pos);
        }
		//accumulate wind hazards into the windOffset vector
		func_getWindOffsetVec_8007B924(fighterObj, /*result vec3*/&windOffset);
    }
    else
    {
        
        windOffset.z = 0;
        windOffset.y = 0;
        windOffset.x = 0;
    }
    
    func_80076528(fighterObj);

    
	if (fighter->cb.x21D0_callback_EveryHitlag) {
        fighter->cb.x21D0_callback_EveryHitlag(fighterObj);
    }
		 
    
	if (fighter->xE0_ground_or_air == GA_Ground)
    {
        
        s32 dummy2;
		Vec3 difference; 
		// I think this function always returns r3=1, but it contains two __assert functions. But I guess these just stop or reset the game.
		// result is written to where r5 points to, which is 'difference' in this case
		if (func_800567C0(fighter->x6F0_collData.x14C_groundIndex, &fighter->xB0_pos, &difference))
			//fighter->position += difference
			PSVECAdd(&fighter->xB0_pos, &difference, &fighter->xB0_pos);
    }
	
	
	fighter->xB0_pos.x += windOffset.x;
    fighter->xB0_pos.y += windOffset.y;
    fighter->xB0_pos.z += windOffset.z;

    // TODO: do the bitflag tests here tell us if the player is dead?
	func_800D3158(fighterObj);
    
	if (fighter->x2225_flag.bits.b0)
    {
		// if position.y crossed (0.25*stage.blastBottom+0.75*stage.cameraBottom) + stage.crowdReactStart from below...
		if (fighter->xBC_prevPos.y <= Stage_CalcUnkCamYBounds() &&
		    fighter->xB0_pos.y >  Stage_CalcUnkCamYBounds()) {
			    fighter->x2225_flag.bits.b0 = 0;
            }
    }
	else
    {
        
		if (!fighter->x222A_flag.bits.b1 && !fighter->x2228_flag.bits.b5)
        {
			// if position.y crossed 0.5*(stage.blastBottom+stage.cameraBottom) + stage.crowdReactStart from above...
			if (fighter->xBC_prevPos.y >= Stage_CalcUnkCamY() &&
			    fighter->xB0_pos.y <  Stage_CalcUnkCamY())
            {
				// plays this sound you always hear when you get close to the bottom blast zone
				func_80088148(fighter, 96, 127, 64);
				fighter->x2225_flag.bits.b0 = 1;
            }
        }
    }
	
	if (fighter->dmg.x18A4_knockbackMagnitude && 
        !fighter->x221C_flag.bits.b6 &&
		!func_80322258(fighter->xB0_pos.x))
        
    {
        
		fighter->dmg.x18A4_knockbackMagnitude = 0.0f; 
    }
    

	func_8007AF28(fighterObj);
	
	if (g_debugLevel >= 3 && 
        (fpclassify(fighter->xB0_pos.x)==FP_NAN || 
         fpclassify(fighter->xB0_pos.y)==FP_NAN || 
         fpclassify(fighter->xB0_pos.z)==FP_NAN)) 
	{
		OSReport("fighter procUpdate pos error.\tpos.x=%f\tpos.y=%f\n", fighter->xB0_pos.x, fighter->xB0_pos.y);
        __assert(__FILE__ , /*line*/2517, "0");
    }
    
}

// https://decomp.me/scratch/6HYyw
void func_8006C0F0(HSD_GObj* fighterObj) 
{

    Mtx mtx1;
    Mtx mtx2;
    Vec scale;
    Vec translation;
    Quaternion rotation;

    Vec unused;

    HSD_JObj* jobj_userdata;
    HSD_JObj* jobj;
    
    jobj_userdata = fighterObj->user_data;

    if (jobj_userdata->translate.y != 1.0f) {

        jobj = fighterObj->hsd_obj;

        HSD_JObjSetupMatrix(jobj);


        HSD_JObjGetMtx(jobj, &mtx1);

        HSD_JObjGetScale(jobj, &scale);
        scale.x = Fighter_GetModelScale((Fighter*)jobj_userdata);

        HSD_JObjGetRotation(jobj, &rotation);

        HSD_JObjGetTranslation(jobj, &translation);

        func_8037A250(&mtx2, &scale, &rotation, &translation, 0);
        PSMTXConcat(&mtx2, &mtx1, &jobj_userdata->mtx);

    }

     
}

///https://decomp.me/scratch/m9K8F
////latest with correct inlines: https://decomp.me/scratch/m9K8F
void func_8006C27C(HSD_GObj* fighterObj, s32 unused, s32 unused2, s32 unused3) {

    Fighter* fighter_r4;

    fighter_r4 = fighterObj->user_data;


    if (fighter_r4->x221F_flag.bits.b3 == 0U) {

        if (fighter_r4->x6F0_collData.x1A0 != 0) {
            fighter_r4->x6F0_collData.x1A0 = fighter_r4->x6F0_collData.x1A0 - 1;
            if (fighter_r4->x6F0_collData.x1A0 == 0) {
                func_8007D5BC(fighter_r4);
            }
        }

        fighter_r4->x2223_flag.bits.b5 = 0;

        HSD_JObjSetTranslate(fighterObj->hsd_obj, &fighter_r4->xB0_pos);

        if (fighter_r4->cb.x21A8_callback_Coll != 0U) {
            fighter_r4->cb.x21A8_callback_Coll(fighterObj);
            func_800F1D24(fighterObj);
        }

        if (fighter_r4->xE0_ground_or_air == 0) {
            func_80041280(fighter_r4->xC_playerID, fighter_r4->x221F_flag.bits.b4);
        }

        if (g_debugLevel >= 3) {
            if (fpclassify(fighter_r4->xB0_pos.x) == FP_NAN ||
                fpclassify(fighter_r4->xB0_pos.y) == FP_NAN ||
                fpclassify(fighter_r4->xB0_pos.z) == FP_NAN)
            {
                /////"fighter procMap pos error.\tpos.x=%f\tpos.y=%f\n"
                ///// Todo wrong offset from data start
                OSReport("fighter procMap pos error.\tpos.x=%f\tpos.y=%f\n", fighter_r4->xB0_pos.x, fighter_r4->xB0_pos.y);
                __assert(__FILE__, 0xA1E, "0");
            }
        }

        HSD_JObjSetTranslate(fighterObj->hsd_obj, &fighter_r4->xB0_pos);

    }
}

void func_8006C5F4(HSD_GObj* pPlayerEntityStruct/*r3*/)
{
    Fighter* pFighter = (Fighter*) pPlayerEntityStruct->user_data;
	if (!pFighter->x221F_flag.bits.b3)
		func_80089B08(pPlayerEntityStruct);
}



/////https://decomp.me/scratch/6AwUk
void func_8006C624(HSD_GObj* fighterObj) {

    s32 unused[2];
    Fighter* fighter_r31 = fighterObj->user_data;

    if (!fighter_r31->x221F_flag.bits.b3) {
        if (fighter_r31->x2219_flag.bits.b5) {
            if (fighter_r31->cb.x21B8_callback_Accessory3) {
                fighter_r31->cb.x21B8_callback_Accessory3(fighterObj);
            }
            return;
        }
        if (fighter_r31->cb.x21B4_callback_Accessory2) {
            fighter_r31->cb.x21B4_callback_Accessory2(fighterObj);
            HSD_JObjSetTranslate(fighterObj->hsd_obj, &fighter_r31->xB0_pos);
        }

        if (fighter_r31->cb.x21B0_callback_Accessory1) {
            fighter_r31->cb.x21B0_callback_Accessory1(fighterObj);
            HSD_JObjSetTranslate(fighterObj->hsd_obj, &fighter_r31->xB0_pos);
        }
    }


}


////https://decomp.me/scratch/Ak3qm
void func_8006C80C(HSD_GObj* fighterObj) {

    Vec spB0;

    Quaternion rotation;
    Vec translation;
    Vec scale;

    Mtx mtx2;
    Mtx mtx1;

    Vec unused;
    Vec unused2;
    s32 unused3;

    HSD_JObj* jobj;
    HSD_JObj* jobj_userdata;

    HSD_JObj* temp_ptr;
    HSD_JObj* temp_ptr2;

    Fighter* fighter_r31;

    fighter_r31 = fighterObj->user_data;


    if (fighter_r31->x221F_flag.bits.b3 == 0) {
        func_80067624(fighterObj, &fighter_r31->x60C);
        temp_ptr = jobj_userdata = fighterObj->user_data;

        if (temp_ptr->translate.y != 1.0f) {

            temp_ptr2 = jobj = fighterObj->hsd_obj;

            HSD_JObjSetupMatrix(temp_ptr2);

            HSD_JObjGetMtx(jobj, &mtx1);

            HSD_JObjGetScale(jobj, &scale);
            scale.x = Fighter_GetModelScale((Fighter*)jobj_userdata);

            HSD_JObjGetRotation(jobj, &rotation);

            HSD_JObjGetTranslation(jobj, &translation);

            func_8037A250(&mtx2, &scale, &rotation, &translation, 0);
            PSMTXConcat(&mtx2, &mtx1, &jobj_userdata->mtx);

        }

        if (fighter_r31->x2219_flag.bits.b5 == 0) {
            if (fighter_r31->cb.x21BC_callback_Accessory4 != 0U) {
                fighter_r31->cb.x21BC_callback_Accessory4(fighterObj);
            }
        }

        func_8007AE80(fighterObj);
        func_8007C224(fighterObj);
        func_8007C6DC(fighterObj);

        if (fighter_r31->x20A0 != 0U) {
            HSD_JObjAnimAll(fighter_r31->x20A0);
        }

        if (fighter_r31->xE0_ground_or_air == 1) {
            if (fighter_r31->xB0_pos.y < Stage_GetCamBoundsBottomOffset()) {
                s32 temp_ret = func_802FB6E8(fighter_r31->xC_playerID);
                if (temp_ret == 3) {
                    Stage_UnkSetVec3TCam_Offset(&spB0);
                    if (fighter_r31->xB0_pos.y + spB0.y < fighter_r31->x2140) {
                        fighter_r31->x2140 = fighter_r31->xB0_pos.y + spB0.y;
                    }
                }
            }
        }

    }

}

//// https://decomp.me/scratch/DN71r
void func_8006CA5C(HSD_GObj* fighterObj) {

    Fighter* fighter_r31 = fighterObj->user_data;

    if (fighter_r31->x221F_flag.bits.b3 == 0 && func_8016B1C4() == 0) {
        func_8007BA0C(fighterObj);
        if (fighter_r31->x221E_flag.bits.b6) {
            func_80078A2C(fighterObj);
            if (fighter_r31->x1A58) {
                if (fighter_r31->x2225_flag.bits.b1 == 0) {
                    func_80088148(fighter_r31, fighter_r31->x10C_ftData->x4C_collisionData->x30, 0x7F, 0x40);
                }
                func_80078754(fighterObj, fighter_r31->x1A58, 0);
                fighter_r31->cb.x2190_callback_OnGrabFighter_Self(fighterObj);
                fighter_r31->cb.x2198_callback_OnGrabFighter_Victim(fighter_r31->x1A58, fighterObj);
                return;
            }
            func_8007BC90(fighterObj);

            if (fighter_r31->x1A60) {
                if (fighter_r31->x2225_flag.bits.b1 == 0) {
                    func_80088148(fighter_r31, fighter_r31->x10C_ftData->x4C_collisionData->x30, 0x7F, 0x40);
                }
                func_8027B4A4(fighterObj, fighter_r31->x1A60);
                if (fighter_r31->cb.x2194_callback) {
                    fighter_r31->cb.x2194_callback(fighterObj);
                }
            }
        }

    }
}


void func_8006CB94(HSD_GObj* fighterObj) {
    Fighter* fighter_r31 = fighterObj->user_data;

    if (fighter_r31->x221F_flag.bits.b3 == 0 && fighter_r31->x2219_flag.bits.b1 == 0) {
        func_800765E0();
        func_80078C70(fighterObj);
        func_8007C77C(fighterObj);
        func_8007925C(fighterObj);
        func_8007BAC0(fighterObj);
        func_8007C4BC(fighterObj);
        func_8007AB48(fighterObj);
        func_8007AB80(fighterObj);
        if (func_8007BBCC(fighterObj) > 0.0f) {
            func_8007FC7C(fighterObj);
        }
    }
}

///https://decomp.me/scratch/UC5Tf
void func_8006CC30(f32 arg0, void* unk_ptr) {
    Fighter_TakeDamage_8006CC7C(unk_ptr, arg0);
    func_8007EA90(unk_ptr, arg0);
}


///https://decomp.me/scratch/KPwpm
void Fighter_TakeDamage_8006CC7C(Fighter* fighter, f32 damage_amount) {

    if (!fighter->x2226_flag.bits.b4 || fighter->x2226_flag.bits.b3) {
        fighter->dmg.x1830_percent += damage_amount;
        if (fighter->x2028) {
            fighter->x202C -= damage_amount;
        }

        if (fighter->x2034) {
            fighter->x2038 -= damage_amount;
        }

        if (fighter->dmg.x1830_percent > 999.0f) {
            fighter->dmg.x1830_percent = 999.0f;
        }
        Player_SetHPByIndex(fighter->xC_playerID, fighter->x221F_flag.bits.b4, fighter->dmg.x1830_percent);
        func_8003EC9C(fighter->xC_playerID, fighter->x221F_flag.bits.b4, fighter->dmg.x1830_percent, damage_amount);
        func_800C8C84(fighter->x0_fighter);
        
    }
}


///https://decomp.me/scratch/9QvFG   ///// Not quite matched
void func_8006CDA4(Fighter* fighter, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_r5;
    
    s32 phi_r31 = 0;
    Vec vec;

    if (fighter->x1974_heldItem && !func_8026B2B4(fighter->x1974_heldItem)) {
        phi_r31 = 1;
    }

    
    temp_r5 = !((fighter->x2220_flag.bits.b3 || fighter->x2220_flag.bits.b4 || func_8008E984(fighter)));
    vec = lbl_803B7494;


    if ((fighter->x10_action_state_index) != 0x145 && ((fighter->x10_action_state_index - 0x122) > 1U) &&  fighter->dmg.x1860_dealt != 0xAU  && !fighter->x2226_flag.bits.b2) {
        if (   ///// giant if condition
                phi_r31 && temp_r5 && ((HSD_Randi(p_ftCommonData->x418) < arg1)
                ||
                ((((func_8026B30C(fighter->x1974_heldItem) == 3) && 
                func_8026B594(fighter->x1974_heldItem))) && 
                !HSD_Randi(p_ftCommonData->x41C)))
            ) 
            {
            if (fighter->x1978) {
                func_8026ABD8(fighter->x1978, &vec, 1.0f);
            }
            func_8026ABD8(fighter->x1974_heldItem, &vec, 1.0f);
        }
        if (fighter->x197C) {
            if (HSD_Randi(p_ftCommonData->x418) < arg1) {
                func_8007F8E8(fighter->x0_fighter);
                func_8026ABD8(fighter->x197C, &vec, 1.0f);
                func_8007F9B4(fighter->x0_fighter);
            }
        }
    }

}

////https://decomp.me/scratch/rKHVB
void func_8006CF5C(Fighter* fighter, s32 arg1) {

   if (fighter->x2224_flag.bits.b2 == 0) {
       fighter->dmg.x18F0 += arg1;
       func_800BFFD0(fighter, 8, 0);
       func_8007EBAC(fighter, 2, 0);
   }
}


///https://decomp.me/scratch/UV4by
void func_8006CFBC(HSD_GObj* fighterObj) {
    Fighter* fighter_r4 = fighterObj->user_data;

    if (fighter_r4->x2219_flag.bits.b7){
        fighter_r4->x221A_flag.bits.b1 = 1;
    }

}

////https://decomp.me/scratch/M9nCw

void func_8006CFE0(HSD_GObj* fighterObj) {
    Fighter* fighter_r31;
    fighter_r31 = fighterObj->user_data;

    if (fighter_r31->x2219_flag.bits.b7) {
        if (fighter_r31->x221A_flag.bits.b2 == 0) {
            if (!fighter_r31->dmg.x1954){
                func_8006D10C(fighterObj);
            }
        }
        fighter_r31->x2219_flag.bits.b7 = 0;
    }
}

///https://decomp.me/scratch/osZ8G
void func_8006D044(HSD_GObj* fighterObj) {
    s32 unused[5];
    HSD_GObj* otherObj;
    Fighter* fighter = fighterObj->user_data;

    if (fighter->cb.x21D4_callback_EnterHitlag) {
        fighter->cb.x21D4_callback_EnterHitlag(fighterObj);
    }

    fighter->x2219_flag.bits.b5 = 1;

    otherObj = fighter->x1A5C;
    if (fighter->x1A5C && !fighter->x2219_flag.bits.b7) {
        Fighter* other_fighter = fighter->x1A5C->user_data;
        other_fighter->x2219_flag.bits.b7 = 1;
        other_fighter = otherObj->user_data;
        if (other_fighter->cb.x21D4_callback_EnterHitlag) {
            other_fighter->cb.x21D4_callback_EnterHitlag(otherObj);
        }
        other_fighter->x2219_flag.bits.b5 = 1;

        otherObj = other_fighter->x1A5C;
        if (otherObj && !other_fighter->x2219_flag.bits.b7) {
            Fighter* other_fighter2 = otherObj->user_data;
            other_fighter2->x2219_flag.bits.b7 = 1;
            func_8006D044(otherObj);
        }
    }
}

//// https://decomp.me/scratch/yD4Ne
void func_8006D10C(HSD_GObj* fighterObj) {
    s32 unused[2];
    HSD_GObj* otherObj;
    HSD_GObj* otherObj2;

    Fighter* fighter = fighterObj->user_data;

    if (fighter->cb.x21D8_callback_ExitHitlag) {
        fighter->cb.x21D8_callback_ExitHitlag(fighterObj);
    }

    fighter->x2219_flag.bits.b5 = 0;
    otherObj2 = otherObj = fighter->x1A5C;

    if (otherObj2 && !fighter->x2219_flag.bits.b7) {
        Fighter* new_fighter = otherObj->user_data;
        if (new_fighter->x2219_flag.bits.b7) {

            if (!new_fighter->x221A_flag.bits.b2 && !new_fighter->dmg.x1954) {
                if (new_fighter->cb.x21D8_callback_ExitHitlag) {
                    new_fighter->cb.x21D8_callback_ExitHitlag(otherObj);
                }
                new_fighter->x2219_flag.bits.b5 = 0;
                if (new_fighter->x1A5C && !new_fighter->x2219_flag.bits.b7) {
                    func_8006CFE0(new_fighter->x1A5C);
                }
                    
            }
            
            new_fighter->x2219_flag.bits.b7 = 0;
        }
    }
}

///https://decomp.me/scratch/U3gL9
void func_8006D1EC(HSD_GObj* fighterObj) {

    f32 temp_f30;

    f32 temp_f1;
    f32 temp_f2;

    s32 unused[6];

    
    Fighter* fighter = fighterObj->user_data;
    Fighter* fighter_r25;
    HSD_GObj* temp_obj;

    s32 phi_r29;

    s32 temp_r26;
    s32 temp_r28 = fighter->x10_action_state_index;
    s32 temp_r29;

    s32 phi_r27;

    s32 phi_r26;
    s32 phi_r25;
    
    phi_r25 =
    phi_r26 =
    phi_r27 =
    phi_r29 = 0;

    if (!fighter->x221F_flag.bits.b3) {

        if (!fighter->x221A_flag.bits.b7) {
            if (fighter->x1998_shieldHealth < p_ftCommonData->x260_startShieldHealth) {
                fighter->x1998_shieldHealth += p_ftCommonData->x27C;
                if (fighter->x1998_shieldHealth > p_ftCommonData->x260_startShieldHealth) {
                    fighter->x1998_shieldHealth = p_ftCommonData->x260_startShieldHealth;
                }
            }
        }

        if (fighter->x221A_flag.bits.b7) {
            temp_f2 = p_ftCommonData->x2DC;
            fighter->x1998_shieldHealth -= (p_ftCommonData->x284 * ((fighter->x19A0_shieldDamageTaken) * (1.0f - ((fighter->x199C_shieldLightshieldAmt * (p_ftCommonData->x2E0 - temp_f2)) + temp_f2)))) + p_ftCommonData->x288;
            if (fighter->x1998_shieldHealth < 0.0f) {
                phi_r26 = 1;
                fighter->x1998_shieldHealth = p_ftCommonData->x280;
                /// this function is called when shield is broken
                func_8003E058(fighter->x19BC_shieldDamageTaken3, fighter->x221F_flag.bits.b6, fighter->xC_playerID, fighter->x221F_flag.bits.b4);
            }
        }

        if (fighter->dmg.x189C > 0.0f) {
            fighter->dmg.x189C--;
            if (fighter->dmg.x189C <= 0.0f && !fighter->dmg.x1850_forceApplied) {
                fighter->dmg.x189C = 0.0f;
                func_8007BE3C(fighterObj);
            }
        }

        // temp_f30 = fighter->dmg.x1850_forceApplied;
        if (temp_f30 = fighter->dmg.x1850_forceApplied) {
            temp_r26 = fighter->xE0_ground_or_air;
            fighter->dmg.x189C = 0.0f;
            temp_f2 = fighter->dmg.x1838_percentTemp;
            Fighter_TakeDamage_8006CC7C( fighter, fighter->dmg.x1838_percentTemp);
            func_8007EA90(fighter, temp_f2);
            func_8008D930(fighter);
            func_800F5BA4(fighter);

            if (fighter->cb.x21F0_callback) {
                fighter->cb.x21F0_callback(fighterObj);
            }

            if (!fighter->x2229_b7) {

                switch (fighter->x1828) {
                    case 0:
                        func_8008EC90(fighterObj);
                        break;
                    case 1:
                        func_8007DB58(fighterObj);
                        func_8008E908(fighterObj, 0.0f);
                        break;
                    case 2:
                        func_8007DB58(fighterObj);
                        func_8008E9D0(fighterObj);
                        break;
                    case 3:
                        func_8007DB58(fighterObj);
                        func_8008EB58(fighterObj);
                        break;
                }

                temp_r29 = fighter->dmg.x183C_applied;
                phi_r27 = 1;
                func_80090594(fighter, fighter->dmg.x1860_dealt, temp_r29, temp_r28, temp_r26, fighter->x1960_vibrateMult);
                func_8007ED50(fighter, fighter->dmg.x1838_percentTemp);
                phi_r29 = temp_r29;
                
            } else {

                switch (fighter->x4_fighterKind) {
                    case 0x1B:
                        func_8014FE58(fighterObj);
                        break;
                    case 0x1C:
                        func_80156014(fighterObj);
                        break;
                    default:
                        OSReport("ellegal flag fp->no_reaction_always\n");
                        __assert(__FILE__, 3085, "0");
                }
                func_8008E9D0(fighterObj);
            }
        } else if (fighter->dmg.x18a0) {
            phi_r29 = fighter->dmg.x1840;
            phi_r25 = 1;
        } else if (fighter->x19A4) {
            if (phi_r26) {
                func_80098B20(fighterObj);
                func_80088148(fighter, 0x82, 0x7F, 0x40);
            } else {
                if (fighter->cb.x21C4_callback_OnShieldHit) {
                    fighter->cb.x21C4_callback_OnShieldHit(fighterObj);
                }
            }
            phi_r29 = fighter->x19A4;
        } else if (fighter->dmg.x1918) {
            if ((fighter->dmg.x191C) && (!fighter->x1A58) && (!fighter->x1A60)) {
                func_8007DB58(fighterObj);
                func_80099D9C(fighterObj);
            }
            phi_r29 = fighter->dmg.x1918;
        } else if (fighter->dmg.x1914) {
            if (fighter->cb.x21C0_callback_OnGiveDamage) {
                fighter->cb.x21C0_callback_OnGiveDamage(fighterObj);
            }
            phi_r29 = fighter->dmg.x1914;
            if (fighter->x2073 == 0x46U) {
                func_8007EBAC(fighter, 0xE, 0);
            } else {
                func_8007EE0C(fighter, fighter->dmg.x1914);
            }
        } else {
            if (fighter->dmg.x1924) {
                phi_r29 = fighter->dmg.x1924;
            } else if (fighter->x1A3C) {
                func_80098C9C(fighterObj);
            } else if (fighter->x1A2C_reflectHitDirection) {
                if (fighter->cb.x21C8_callback_OnReflectHit) {
                    fighter->cb.x21C8_callback_OnReflectHit(fighterObj);
                }
            } else if (fighter->x1A40) {
                if (ft_OnAbsorb[fighter->x4_fighterKind]) {
                    ft_OnAbsorb[fighter->x4_fighterKind](fighterObj);
                }
            } else if (fighter->x20AC) {
                if (fighter->cb.x21F4_callback) {
                    fighter->cb.x21F4_callback(fighterObj);
                }
            }
        }

        if (!temp_f30) {
            f32 newtemp;
            newtemp = fighter->dmg.x1838_percentTemp;
            temp_f30 = newtemp;
            if (temp_f30) {
                Fighter_TakeDamage_8006CC7C(fighter, newtemp);
                func_8007EA90(fighter, temp_f30);
                func_800F5C34(fighter);
                func_800804FC(fighter);
            }
        }
        func_800C8D00(fighterObj);

        
        if (phi_r29) {
            fighter->dmg.x195c_hitlag_frames = func_8007DA74(phi_r29, temp_r28, fighter->x1960_vibrateMult);
            if (fighter->dmg.x195c_hitlag_frames < fighter->x1964) {
                fighter->dmg.x195c_hitlag_frames = fighter->x1964;
            }
            if (fighter->dmg.x195c_hitlag_frames > 0.0f) {
                if (fighter->dmg.x195c_hitlag_frames > p_ftCommonData->x194) {
                    fighter->dmg.x195c_hitlag_frames = p_ftCommonData->x194;
                }
                fighter->x221A_flag.bits.b2 = 1;
                if (phi_r27) {
                    fighter->x221A_flag.bits.b3 = 1;
                }
                if (phi_r25) {
                    fighter->dmg.x189C = fighter->dmg.x195c_hitlag_frames;
                }
                if (!fighter->x2219_flag.bits.b5) {
                    // HSD_GObj* temp_obj;
                    fighter_r25 = fighterObj->user_data;
                    if (fighter_r25->cb.x21D4_callback_EnterHitlag) {
                        fighter_r25->cb.x21D4_callback_EnterHitlag(fighterObj);
                    }
                    fighter_r25->x2219_flag.bits.b5 = 1;
                    // temp_obj = fighter_r25->x1A5C;
                    if ((temp_obj = fighter_r25->x1A5C) && !fighter_r25->x2219_flag.bits.b7) {
                        ((Fighter*)temp_obj->user_data)->x2219_flag.bits.b7 = 1;
                        func_8006D044(temp_obj);
                    }
                }
            }
        } else {
            func_80090718(fighter);
        }

        if (fighter->x221A_flag.bits.b0 || fighter->dmg.x1958) {
            if (!fighter->x2219_flag.bits.b5) {
                // HSD_GObj* temp_obj;
                fighter_r25 = fighterObj->user_data;
                if (fighter_r25->cb.x21D4_callback_EnterHitlag) {
                    fighter_r25->cb.x21D4_callback_EnterHitlag(fighterObj);
                }
                fighter_r25->x2219_flag.bits.b5 = 1;
                temp_obj = fighter_r25->x1A5C;
                if ((temp_obj) && !fighter_r25->x2219_flag.bits.b7) {
                    ((Fighter*)temp_obj->user_data)->x2219_flag.bits.b7 = 1;
                    func_8006D044(temp_obj);
                }
            }

            if (fighter->x221A_flag.bits.b0) {
                fighter->x2219_flag.bits.b7 = 1;
                fighter->x221A_flag.bits.b0 = 0;
            } else {
                if (fighter->dmg.x1958 > fighter->dmg.x1954) {
                    fighter->dmg.x1954 = fighter->dmg.x1958;
                }
                fighter->dmg.x1958 = 0.0f;
            }
        }


        if (fighter->dmg.x1928) {
            temp_f2 = (fighter->dmg.x1928 * p_ftCommonData->x3E0) + p_ftCommonData->x3E4;
            fighter->xF4_ground_attacker_shield_kb_vel = (fighter->dmg.x192c < 0.0f) ? temp_f2 : -temp_f2;
            func_8007E2A4(fighterObj);
        }

        fighter->dmg.x1838_percentTemp = 0.0f;
        fighter->dmg.x183C_applied = 0;
        fighter->x1828 = 0;
        fighter->dmg.x1850_forceApplied = 0.0f;
        fighter->dmg.x18a0 = 0.0f;
        fighter->dmg.x1840 = 0;
        fighter->dmg.x1914 = 0;
        fighter->dmg.x1918 = 0;
        fighter->dmg.x191C = 0.0f;
        fighter->x20AC = 0;
        fighter->x221C_flag.bits.b5 = 0;
        
        fighter->dmg.x1924 = 0;
        fighter->dmg.x1928 = 0.0f;
        fighter->x19A0_shieldDamageTaken = 0;
        fighter->x19A4 = 0;
        fighter->x19A8 = 0;
        fighter->x1A3C = 0;
        fighter->x1A2C_reflectHitDirection = 0.0f;
        fighter->x1A40 = 0.0f;
        fighter->x1A44 = 0;
        fighter->x1A48 = 0;
        fighter->x1960_vibrateMult = 1.0f;
        fighter->x1964 = 0.0f;
        fighter->dmg.x1950 = 0;

        if (!fighter->x2219_flag.bits.b6 || fighter->dmg.x18F4) {
            func_800C2FD8(fighterObj);
        }
        func_800A0DA4(fighter);
        
    }

}

///https://decomp.me/scratch/GmsSV
void func_8006D9AC(HSD_GObj* fighterObj) {
    Fighter* fighter_r4;
    fighter_r4  = fighterObj->user_data;

    if (fighter_r4->x221F_flag.bits.b3 || fighter_r4->x2219_flag.bits.b5) return;

    func_8009E0A8(fighterObj);
}

//https://decomp.me/scratch/PcHW6
void func_8006D9EC(HSD_GObj* fighterObj) {
    Fighter* fp = fighterObj->user_data;

    if (fp->x221F_flag.bits.b3 == 0) {
        func_8008021C(fighterObj);
        if (fp->cb.x21AC_callback_Cam) {
            fp->cb.x21AC_callback_Cam(fighterObj);
        }
    }

}

///https://decomp.me/scratch/4PdL1
void func_8006DA4C(HSD_GObj* fighterObj) {
    Fighter* fp = fighterObj->user_data;

    if (fp->x221F_flag.bits.b3 == 0) {
        Player_80032828(fp->xC_playerID, fp->x221F_flag.bits.b4, &fp->xB0_pos);
        Player_SetFacingDirectionConditional(fp->xC_playerID, fp->x221F_flag.bits.b4, fp->x2C_facing_direction);
        func_8003FAA8(fp->xC_playerID, fp->x221F_flag.bits.b4, &fp->xB0_pos, &fp->xBC_prevPos);
    }
}

///https://decomp.me/scratch/8gk4A   ///// Not quite matched

////// MOVED to ftanim.s

// void func_8006DABC(Fighter* fighter) {

//     // void (*func_array)(HSD_GObj* obj) = &lbl_803C125C;
//     // void (**func_array)(HSD_GObj* obj) = lbl_803C125C;
//     void (*selected_func)(HSD_GObj* obj); 
    
//     HSD_ObjAllocData* objAllocData = &lbl_80458FD0;

//     if (selected_func = lbl_803C125C[fighter->x4_fighterKind]) {
//         selected_func(fighter->x0_fighter);
//     }
    
//     func_8007B8E8(fighter->x0_fighter);
//     func_80067688(&fighter->x60C);
//     func_8026B7F8(fighter->x0_fighter);
//     func_800290D4(fighter->x890);
//     func_8009E0D4(fighter);
//     func_800765AC(fighter->x0_fighter);
//     func_80088C5C(fighter->x0_fighter);
//     func_8000EE8C(&fighter->x20A4);
//     if (fighter->x20A0) {
//         HSD_JObjRemoveAll(fighter->x20A0);
//     }
//     HSD_JObjRemoveAll(fighter->x8AC_animSkeleton);
//     HSD_JObjUnref((void*)fighter->x2184); //fighter->x2148
//     func_800859A8(fighter);
//     func_80366BD4(fighter->x588);
//     Player_80031FB0(fighter->xC_playerID, fighter->x221F_flag.bits.b4);
//     HSD_ObjFree(&objAllocData[(0xDC / 40)], (void*)fighter->x59C);
//     HSD_ObjFree(&objAllocData[(0xDC / 40)], (void*)fighter->x5A0);
//     HSD_ObjFree(&objAllocData[(0x58 / 40)], (void*)fighter->x5E8_fighterBones);
//     HSD_ObjFree(&objAllocData[(0x84 / 40)], (void*)fighter->x5F0);
//     HSD_ObjFree(&objAllocData[(0xB0 / 40)], (void*)fighter->x2040);
//     HSD_ObjFree(&objAllocData[(0x2C / 40)], (void*)fighter->x2D8_specialAttributes2);
//     HSD_ObjFree(&objAllocData[(0x2C / 40)], fighter);
// }
