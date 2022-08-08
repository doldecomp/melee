#include "fighter.h"

#define HALF_PI 1.5707963267948966

// external vars from asm/melee/ft/code_8008521C.s
typedef void (*ft_callback)(HSD_GObj* gobj);
typedef void (*fn_ptr_t)();


extern ft_callback ft_OnLoad[33];  // One load  callback for every character.
extern ft_callback ft_OnDeath[33]; // One death callback for every character.
extern ft_callback ft_OnAbsorb[33];
extern ft_callback lbl_803C1DB4[33];  //probably ft_OnSomething
extern ft_callback ft_OnUserDataRemove[33];

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
const Vec3 vec3_803B7494 = { 0.0f, 0.0f, 0.0f };

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

// TEMP HACKS TO DEAL WITH --------------------
inline HSD_JObj *getHSDJObj(HSD_GObj* hsd_gobj) {
    HSD_JObj *hsd_jobj = hsd_gobj->hsd_obj;
    return (void *)hsd_jobj;
}

// WORKAROUND
// bleeeehhhh. HSD_JObjSetScale does not have a correct inline depth due to
// inline auto preferring 3 levels of depth. TODO: Determine if the Setup MTX
// inline is fake, and correct the inline to adjust if so.
inline void HSD_JObjSetScale_Hack(HSD_JObj* jobj, Vec* scale)
{
    ((jobj) ? ((void) 0) : __assert("jobj.h", 760, "jobj")) ;
    ((scale) ? ((void) 0) : __assert("jobj.h", 761, "scale")) ;
    jobj->scale = *scale;
    if (!(jobj->flags & 0x2000000)) {
#if 0
        // this is what it should call
        HSD_JObjSetMtxDirty(jobj);
#else
        // this is the code manually inlined...
        if (jobj != ((void*)0) && !HSD_JObjMtxIsDirty(jobj)) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
#endif
    }
}
// ---------------------------------------------

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

inline void Fighter_InitScale(Fighter *ft, Vec *scale, f32 modelScale) {
    if (ft->x34_scale.z != 1.0f)
        scale->x = ft->x34_scale.z;
    else
        scale->x = modelScale;
    
    scale->y = modelScale;
    scale->z = modelScale;
}

void Fighter_UpdateModelScale(HSD_GObj* fighterObj)
{
    Fighter* fighter = getFighter(fighterObj);
    HSD_JObj* jobj = getHSDJObj(fighterObj);
    f32 modelScale_f1 = Fighter_GetModelScale(fighter);
    Vec scale;

    Fighter_InitScale(fighter, &scale, modelScale_f1);
    HSD_JObjSetScale_Hack(jobj, &scale);
}

void Fighter_UnkInitReset_80067C98(Fighter* fighter) {
	Vec3 player_coords;
	f32 x,y,z;

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
	fighter->x894_currentAnimFrame = 0.0f; 
	fighter->x898_unk = 0.0f; 

	fighter->x89C_frameSpeedMul = 1.0f; 
	fighter->x8A0_unk = 1.0f; 
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
	fighter->dmg.x189C_unk_num_frames = 0.0f;

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

	fighter->x20A0_accessory = 0;
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

	fighter->x1A58_interactedFighter = 0;
	fighter->x1A5C = 0;

	fighter->x221B_flag.bits.b6 = 0;

	fighter->x1A60 = 0;
	fighter->x1A64 = 0;

	fighter->x221B_flag.bits.b7 = 0;
	fighter->x221C_flag.bits.b0 = 0;

	fighter->x1064_thrownHitbox.x134 = 0;
	fighter->x221C_u16_y = 0;
	fighter->x20AC = NULL;
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
	fighter->ReflectAttr.x1A3C_damageOver = 0;
	fighter->ReflectAttr.x1A2C_reflectHitDirection = 0.0f;
	fighter->x2218_flag.bits.b6 = 0; 
	fighter->x2218_flag.bits.b7 = 0;


	fighter->AbsorbAttr.x1A40_absorbHitDirection = 0.0f;

	fighter->AbsorbAttr.x1A44_damageTaken = 0;
	fighter->AbsorbAttr.x1A48_hitsTaken = 0;

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

	func_800C88A0(fighter);

	fighter->x2227_flag.bits.b3 = 0;
	fighter->x2034 = 0;
	fighter->x2038 = 0;
	fighter->x1980 = 0;

	fighter->x2224_flag.bits.b2 = fighter->x2224_flag.bits.b3 = 0;

	fighter->x2224_flag.bits.b4 = 0;
	fighter->x2108 = 0;
	fighter->x2224_flag.bits.b5 = 0;
	fighter->x1A53 = 0;
	fighter->x1A52 = 0;
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
	fighter->x2114_SmashAttr.x2138_smashSinceHitbox = -1.0f;
	fighter->x213C = -1;
	fighter->x2227_flag.bits.b5 = 0;
	fighter->x2228_flag.bits.b1 = 0;
	fighter->x2140 = 0.0f;
	fighter->x2227_flag.bits.b6 = 0;
	fighter->x2180 = 6;
	fighter->x2229_b4 = 1;
}

void Fighter_UnkProcessDeath_80068354(HSD_GObj* fighterObj) {
    Fighter* ft = getFighter(fighterObj);
    
    Fighter_UnkInitReset_80067C98(ft);
    HSD_JObjSetTranslate(fighterObj->hsd_obj, &ft->xB0_pos);

    func_800D105C(fighterObj);
    func_800C09B4(fighterObj);
    func_8007E2FC(fighterObj);
    func_80088A50(ft);
    func_800890BC(ft);
    func_800892D4(ft);
    func_80081B38(fighterObj);
    func_80081938(fighterObj);

    if (ft->x2114_SmashAttr.x2135 == -1)
    {
        if (func_80082A68(fighterObj) && !ft->x2229_b6)
            func_8007D6A4(ft);
        else
            func_8007D5D4(ft);
    }
    else
        func_8007D5D4(ft);
    func_80076064(ft);
    
    HSD_JObjSetTranslate(fighterObj->hsd_obj, &ft->xB0_pos);
    Fighter_UnkApplyTransformation_8006C0F0(fighterObj);
    Fighter_UpdateModelScale(fighterObj);

    func_800BFFAC(ft);
    func_800C0074(ft);
    func_800C8438(fighterObj);
    func_800C89A0(fighterObj);
    func_800C8FC4(fighterObj);
    func_8007AFF8(fighterObj);
    func_8007B0C0(fighterObj, 0);

    if (ft_OnDeath[ft->x4_fighterKind])
        ft_OnDeath[ft->x4_fighterKind](fighterObj);

    func_800A101C(ft, Player_GetCpuType(ft->xC_playerID), Player_GetCpuLevel(ft->xC_playerID), 0);

    func_80067688(&ft->x60C);
    func_8007C17C(fighterObj);
    func_8007C630(fighterObj);
}

void Fighter_UnkUpdateCostumeJoint_800686E4(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);
    HSD_JObj *jobj;
    
    fighter->x108_costume_joint = CostumeListsForeachCharacter[fighter->x4_fighterKind].costume_list[fighter->x619_costume_id].joint;
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
    Fighter* fighter = getFighter(fighterObj);

    fighter->input.x620_lstick_x = 
    fighter->input.x624_lstick_y = 
    fighter->input.x628_lstick_x2 = 
    fighter->input.x62C_lstick_y2 = 0.0f;

    fighter->input.x644_lsubStick_y2 = 0.0f;
    fighter->input.x640_lsubStick_x2 = 0.0f;
    fighter->input.x63C_lsubStick_y = 0.0f;
    fighter->input.x638_lsubStick_x = 0.0f;

    fighter->input.x654 = 0.0f;
    fighter->input.x650 = 0.0f;

    fighter->input.x660 = 0;
    fighter->input.x66C = 0;
    fighter->input.x668 = 0;
    fighter->input.x65C_heldInputs = 0;

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

static void Fighter_UnkInitLoad_80068914_Inner1(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);
    
    fighter->input.x650 = 
    fighter->input.x654 = 
    fighter->input.x638_lsubStick_x = 
    fighter->input.x63C_lsubStick_y = 
    fighter->input.x640_lsubStick_x2 = 
    fighter->input.x644_lsubStick_y2 = 
    fighter->input.x620_lstick_x = 
    fighter->input.x624_lstick_y = 
    fighter->input.x628_lstick_x2 = 
    fighter->input.x62C_lstick_y2 = 0.0f;

    fighter->input.x660 = 0;
    fighter->input.x66C = 0;
    fighter->input.x668 = 0;
    fighter->input.x65C_heldInputs = 0;
    
    fighter->x679_x = 
    fighter->x67A_y = 
    fighter->x67B = 

    fighter->x676_x = 
    fighter->x677_y = 
    fighter->x678 = 

    fighter->x673 = 
    fighter->x674 = 
    fighter->x675 = 

    fighter->x670_timer_lstick_tilt_x = 
    fighter->x671_timer_lstick_tilt_y = 
    fighter->x672_input_timer_counter = 0xFE;

    fighter->x67C = 
    fighter->x67D = 
    fighter->x67E = 
    fighter->x681 = 
    fighter->x682 = 
    fighter->x67F = 
    fighter->x680 = 
    fighter->x683 = 
    fighter->x684 = 
    fighter->x685 = 
    fighter->x686 = 
    fighter->x687 = 
    fighter->x688 = 
    fighter->x689 = 
    fighter->x68A = 
    fighter->x68B = 0xFF;
}

void Fighter_UnkInitLoad_80068914(HSD_GObj* fighterObj, struct S_TEMP1* argdata) {
    Fighter* fighter = getFighter(fighterObj);
    u32 controller_index;
    struct RGBA* color;
    ftData** ftDataList;
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

    fighter->input.x634 = 0.0f;
    fighter->input.x630 = 0.0f;
    fighter->input.x64C = 0.0f;
    fighter->input.x648 = 0.0f;
    fighter->input.x658 = 0.0f;
    fighter->input.x664 = 0;

    Fighter_UnkInitLoad_80068914_Inner1(fighterObj);

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

    fighter->x2114_SmashAttr.x2135 = -1;
    fighter->x2184 = NULL;

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
    Fighter* fighter = (void*)getFighter(fighterObj); // bit of a fake void* cast, but a sacrifice well worth getting rid of an fp_temp and filler. TODO: Maybe we can still do better?

    if (stage_info.internal_stage_id == 0x1B) {
        fighter->x34_scale.z = p_ftCommonData->x7E4_scaleZ;
    } else {
        fighter->x34_scale.z = 1.0f;
    }
}

static void Fighter_80068E98_Inline2(HSD_GObj *fighterObj) {
    Fighter *fp = getFighter(fighterObj); // you cant do (void*) here to make it consistent, Fighter_80068E98 wont match
    if (fp->x2229_b5_no_normal_motion == 0) {
        fp->x2EC = func_8001E8F8(func_80085E50(fp, 0x23));
        if (fp->x2228_flag.bits.b2 == 0) {
            fp->x2DC = func_8001E8F8(func_80085E50(fp, 7));
            fp->x2E0 = func_8001E8F8(func_80085E50(fp, 8));
            fp->x2E4 = func_8001E8F8(func_80085E50(fp, 9));
            fp->x2E8 = func_8001E8F8(func_80085E50(fp, 0x25));
        } 
    }
}

HSD_GObj* Fighter_80068E98(struct S_TEMP1* input) {
    HSD_GObj* fighterObj;
    Fighter* fp;
    HSD_JObj* jobj;

    fighterObj = func_803901F0(4, 8, 0);
    GObj_SetupGXLink(fighterObj, &func_80080E18, 5U, 0U);
    fp = HSD_ObjAlloc(&lbl_80458FD0);
    fp->x2D8_specialAttributes2 = HSD_ObjAlloc(&lbl_80458FFC);
    GObj_InitUserData(fighterObj, 4U, &Fighter_Unload_8006DABC, fp);
    func_8008572C(input->fighterKind);
    Fighter_UnkInitLoad_80068914(fighterObj, input);
    func_8006737C(lbl_803C26FC[fp->x4_fighterKind]);
    func_80085820(fp->x4_fighterKind, fp->x619_costume_id);
    
    Fighter_UnkUpdateCostumeJoint_800686E4(fighterObj); 
    
    func_80085B10(fp);
    func_80074E58(fp);
    func_800743E0(fighterObj);
    func_80070308(fighterObj);
    func_800C884C(fighterObj);

    Fighter_80068E64(fighterObj);
    
    func_800749CC(fighterObj);
    func_8007077C(fighterObj);
    func_8009CF84(fp);
    func_8006FE48(fighterObj);

    Fighter_UnkUpdateVecFromBones_8006876C(fp);
    
    func_8009F578(fp);

    if (ft_OnLoad[fp->x4_fighterKind]) {
        ft_OnLoad[fp->x4_fighterKind](fighterObj);
    }

    Fighter_80068E98_Inline2(fighterObj);

    func_8007B320(fighterObj);
    fp->x890_cameraBox = func_80029020();

    jobj = getHSDJObj(fighterObj);
    func_8000ED54(&fp->x20A4, jobj);
    func_8038FD54(fighterObj, &Fighter_8006A1BC, 0);
    func_8038FD54(fighterObj, &Fighter_8006A360, 1);
    func_8038FD54(fighterObj, &Fighter_8006ABA0, 2);
    func_8038FD54(fighterObj, &Fighter_Spaghetti_8006AD10, 3);
    func_8038FD54(fighterObj, (void*) &Fighter_procUpdate, 4);
    func_8038FD54(fighterObj, (void*) &Fighter_8006C27C, 6);
    func_8038FD54(fighterObj, &Fighter_8006C5F4, 7);
    func_8038FD54(fighterObj, &Fighter_CallAcessoryCallbacks_8006C624, 8);
    func_8038FD54(fighterObj, &Fighter_8006C80C, 9);
    func_8038FD54(fighterObj, &Fighter_UnkProcessGrab_8006CA5C, 0xC);
    func_8038FD54(fighterObj, &Fighter_8006CB94, 0xD);
    func_8038FD54(fighterObj, &Fighter_UnkProcessShieldHit_8006D1EC, 0xE);
    func_8038FD54(fighterObj, &Fighter_8006D9AC, 0x10);
    func_8038FD54(fighterObj, &Fighter_UnkCallCameraCallback_8006D9EC, 0x12);
    func_8038FD54(fighterObj, &Fighter_8006DA4C, 0x16);
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
    HSD_JObj* jobj = fighterObj->hsd_obj;
    Fighter* fighter = fighterObj->user_data;
    struct ActionState* new_action_state;
    struct S_TEMP4* unk_struct_x18;
    s32 bone_index;
    u8* unk_byte_ptr;
    BOOL animflags_bool;

    fighter->x10_action_state_index = new_action_state_index;
    fighter->x30_facingDirectionRepeated = fighter->x2C_facing_direction;
        
    HSD_JObjSetTranslate(jobj, &fighter->xB0_pos);
    func_80067624(fighterObj, &fighter->x60C);
    
    if ((arg2 & FIGHTER_HIT_NOUPDATE) == 0) {
        if (fighter->x2219_flag.bits.b3 != 0) {
            func_8007AFF8(fighterObj);
        }
        if (fighter->x2219_flag.bits.b4 != 0) {
            func_8007C114(fighterObj);
        }
    }

    if ((arg2 & FIGHTER_THROW_EXCEPTION_NOUPDATE) == 0) {
        fighter->x1064_thrownHitbox.x134 = 0;
    }

    if ((arg2 & FIGHTER_HITSTATUS_COLANIM_PRESERVE) == 0) {
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
    

    if (((arg2 & FIGHTER_MODEL_NOUPDATE) == 0) && (fighter->x221D_flag.bits.b2 != 0U)) {
        func_80074A8C(fighterObj);
    }

    if (((arg2 & FIGHTER_MATANIM_NOUPDATE) == 0) && ((fighter->x221E_flag.bits.b7) != 0)) {
        func_80070654(fighterObj);
    }

    if ((arg2 & FIGHTER_PARASOL_NOUPDATE) == 0) {
        fighter->x2221_flag.bits.b4 = 0;
        if ((ftGetParasolStatus(fighterObj) != -1) && (ftGetParasolStatus(fighterObj) != 6)) {
            func_8007E83C(fighterObj, 6, 0.0f);
        }
    }
    
    func_80070F28(fighterObj);
    func_80070E74(fighterObj);
    func_8007ECD4(fighter, 7);
    func_8007ECD4(fighter, 8);
    func_8007ECD4(fighter, 0x24);

    if ((arg2 & FIGHTER_RUMBLE_NOUPDATE) == 0) {
        func_8007ECD4(fighter, 1);
        func_8007ECD4(fighter, 0x19);
    }

    if (((arg2 & FIGHTER_PART_HITSTATUS_COLANIM_PRESERVE) == 0) && (fighter->x2221_flag.bits.b1 != 0U)) {
        func_8007B6EC(fighterObj);
        func_8007B760(fighterObj, p_ftCommonData->x134);
        fighter->x2221_flag.bits.b1 = 0;
    }
    func_8007E2F4(fighter, 0);

    if (fighter->dmg.x18F4 != 0) {
        fighter->dmg.x18F4 = 0;
        fighter->x2220_flag.bits.b4 = 0;
    }

    if ((arg2 & FIGHTER_SKIP_UNK_0x2222) == 0) {
        fighter->x2222_flag.bits.b2 = 0;
    }

    if ((arg2 & FIGHTER_METALB_NOUPDATE) == 0) {
        fighter->x2223_flag.bits.b4 = 0;
    }

    if ((arg2 & FIGHTER_UNK_0x2227) == 0) {
        fighter->x2227_flag.bits.b2 = 0;
    }

    if (((arg2 & FIGHTER_HITSTUN_FLAG_NOUPDATE) == 0) && (fighter->x221C_flag.bits.b6 != 0U)) {
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

    fighter->x2114_SmashAttr.x2138_smashSinceHitbox = -1.0f;
    fighter->x2224_flag.bits.b4 = 0;

    if ((arg2 & FIGHTER_ITEMVIS_NOUPDATE) == 0) {
        fighter->x221E_flag.bits.b3 = 1;
    } else if (fighter->x221E_flag.bits.b3 == 0U) {
        func_8007F578(fighterObj);
    }

    if ((arg2 & FIGHTER_MODELPART_VIS_NOUPDATE) == 0) {
        fighter->x221E_flag.bits.b4 = 1;
    }

    if ((arg2 & FIGHTER_MODEL_FLAG_NOUPDATE) == 0) {
        fighter->x2225_flag.bits.b2 = 1;
    }

    if ((arg2 & FIGHTER_FASTFALL_PRESERVE) == 0) {
        fighter->x221A_flag.bits.b4 = 0;
    }

    if ((arg2 & FIGHTER_COLANIM_NOUPDATE) == 0) {
        func_800C0134(fighter);
    }

    if (((arg2 & FIGHTER_GFX_PRESERVE) == 0) && (fighter->x2219_flag.bits.b0 != 0U)) {
        func_8007DB24(fighterObj);
    }

    if (((arg2 & FIGHTER_ACCESSORY_PRESERVE) == 0) && ((u32) fighter->x20A0_accessory != 0U)) {
        HSD_JObjRemoveAll(fighter->x20A0_accessory);
        fighter->x20A0_accessory = 0U;
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

    if ((arg2 & FIGHTER_SFX_PRESERVE) == 0) {
        func_80088884(fighter);
        func_800888E0(fighter);
        func_800887CC(fighter);
    }

    if ((arg2 & FIGHTER_SWORDTRAIL_PRESERVE) == 0) {
        fighter->x2100 = -1;
    }
    if ((arg2 & FIGHTER_NAMETAGVIS_NOUPDATE) == 0) {
        fighter->x209A = 0;
    }

    fighter->x2222_flag.bits.b7 = 0;

    if ((arg2 & FIGHTER_PHYS_UNKUPDATE) != 0) {
        fighter->x100 = 0.0f;
    } else {
        fighter->x100 = -1.0f;
    }

    if ((arg2 & FIGHTER_UNK_0x1000000) == 0) {
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

    // looks gross, used to declare the volatile here to maintain the stack order.
    // TODO: There has to be some way to get rid of this while maintaining the
    // effect it has on the stack.
    if (1) {
        volatile s32 volatile_integer = fighter->x2070_int;
        func_800890D0(fighter, new_action_state->move_id);
        func_800895E0(fighter, new_action_state->x4_flags);
        fighter->x2225_flag.bits.b3 = new_action_state->x9_flags.bits.b0;

        if (fighter->x2226_flag.bits.b4 != 0U) {
            if (fighter->x2071_b5 != 0U) {
                func_800C8B2C(fighter, 0x7E, 0);
            }
            if (fighter->x2071_b6 != 0U) {
                func_800C8B2C(fighter, 0x7F, 0);
            }
        }

        if (fighter->cb.x21EC_callback) {
            fighter->cb.x21EC_callback(fighterObj);
            fighter->cb.x21EC_callback = 0U;
        }

        if ((arg2 & FIGHTER_ATTACKCOUNT_NOUPDATE) == 0) {
            func_80037C60(fighterObj, volatile_integer);
        }

        fighter->x14_action_id = new_action_state->action_id;
        fighter->x89C_frameSpeedMul = arg9;
        fighter->x8A0_unk = arg9;
    
        fighter->x894_currentAnimFrame = (arg8 - fighter->x89C_frameSpeedMul);
        fighter->x898_unk = 0.0f;
    
        
        
        if ((fighter->x594_animCurrFlags1.bits.b0) || (fighter->x594_animCurrFlags1.bits.b5)) {
            animflags_bool = TRUE;
        } else {
            animflags_bool = FALSE;
        }
    
        if (fighter->x14_action_id != -1) {
            Vec translation;
            Quaternion quat;

            bone_index = fighter->x596_bits.x7;

            if ((arg2 & FIGHTER_FREEZESTATE) != 0) {
                fighter->x2223_flag.bits.b0 = 1;
                fighter->x104 = 0x14;
                fighter->x89C_frameSpeedMul = 0.0f;
                arg9 = 0.0f;
            }
    
            if (otherObj != NULL) {
                unk_struct_x18 = &((Fighter*)otherObj->user_data)->x24[fighter->x14_action_id];
                unk_byte_ptr = &((Fighter*)otherObj->user_data)->x28[fighter->x14_action_id << 1];
            } else {
                unk_struct_x18 = &fighter->x24[fighter->x14_action_id];
                unk_byte_ptr = &fighter->x28[fighter->x14_action_id << 1];
            }
            fighter->x594_s32 = unk_struct_x18->x10_animCurrFlags;
            func_8009E7B4(fighter, unk_byte_ptr);
            if ((arg2 & FIGHTER_ANIM_NOUPDATE) == 0) {
    
                if (otherObj != 0U) {
                    func_80085CD8(fighter, getFighter(otherObj), fighter->x14_action_id);
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
                        float c = 0.0f;
                        fighter->x6B0.x = fighter->x6B0.y = fighter->x6B0.z = c;
                        fighter->x6A4_transNOffset.x = fighter->x6A4_transNOffset.y = fighter->x6A4_transNOffset.z = c;
                        fighter->x698 = fighter->x68C_transNPos;
                    }
                    
                    if (fighter->x594_animCurrFlags1.bits.b5 != 0U) {
                        float c = 0.0f;
                        fighter->x6E4.x = fighter->x6E4.y = fighter->x6E4.z = c;
                        fighter->x6D8.x = fighter->x6D8.y = fighter->x6D8.z = c;
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
                        float c = 0.0f;
                        fighter->x6B0.x = fighter->x6B0.y = fighter->x6B0.z = c;
                        fighter->x6A4_transNOffset.x = fighter->x6A4_transNOffset.y = fighter->x6A4_transNOffset.z = c;
                        fighter->x698 = fighter->x68C_transNPos;
                    } else if (((arg2 & FIGHTER_ANIMVEL_NOUPDATE) == 0) && (fighter->xE0_ground_or_air == GA_Ground)) {
                        f32 temp_vel = fighter->x6A4_transNOffset.z * fighter->x2C_facing_direction;
                        fighter->x80_self_vel.x = temp_vel;
                        fighter->xEC_ground_vel = temp_vel;
                    }
                }
    
                if (fighter->x594_animCurrFlags1.bits.b5 != 0U) {
                    if (!arg8) {
                        float c = 0.0f;
                        fighter->x6E4.x = fighter->x6E4.y = fighter->x6E4.z = c;
                        fighter->x6D8.x = fighter->x6D8.y = fighter->x6D8.z = c;
                        fighter->x6CC = fighter->x6C0;
                    } else if (((arg2 & FIGHTER_ANIMVEL_NOUPDATE) == 0) && (fighter->xE0_ground_or_air == GA_Ground)) {
                        f32 temp_vel = fighter->x6D8.z * fighter->x2C_facing_direction;
                        fighter->x80_self_vel.x = temp_vel;
                        fighter->xEC_ground_vel = temp_vel;
                    }
                }
                if ((arg2 & FIGHTER_CMD_UPDATE) != 0) {
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
            func_80070758(jobj);
            func_80070758(fighter->x8AC_animSkeleton);
            fighter->x3EC = 0;
            fighter->x8A4_animBlendFrames = 0;
            fighter->x8A8_unk = 0;
        }
    
        if (animflags_bool) {
            if (!fighter->x594_animCurrFlags1.bits.b0 && !fighter->x594_animCurrFlags1.bits.b0) {
                !fighter;
                func_8007CC78(fighter, fighter->x110_attr.x138_DashrunTerminalVelocity);
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
}

void Fighter_8006A1BC(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;

    if (!fighter->x221F_flag.bits.b3) {
        if (fighter->dmg.x1954 > 0.0f) {
            fighter->dmg.x1954 -= 1.0f;
            if (fighter->dmg.x1954 <= 0.0f) {
                fighter->dmg.x1954 = 0.0f;
                if (!fighter->x221A_flag.bits.b2 && !fighter->x2219_flag.bits.b7) {
                    Fighter_8006D10C(fighterObj);
                }
            }
        }

        if (fighter->x221A_flag.bits.b1) {
            Fighter_8006CFE0(fighterObj);
            fighter->x221A_flag.bits.b1 = 0;
        }

        if (fighter->dmg.x195c_hitlag_frames > 0.0f) {
            fighter->dmg.x195c_hitlag_frames -= 1.0f;
            if (fighter->dmg.x195c_hitlag_frames <= 0.0f) {
                fighter->dmg.x195c_hitlag_frames = 0.0f;
                if (fighter->x221A_flag.bits.b3) {
                    func_80090718(fighter);
                    fighter->x221A_flag.bits.b3 = 0;
                }
                if ((!fighter->dmg.x1954) && !fighter->x2219_flag.bits.b7) {
                    Fighter_8006D10C(fighterObj);
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
                // im not sure of whatever is here, but a void ptr downcast to get rid of filler seems like a better tradeoff...
                void *fighterVoid = fighter;
                (void)fighterVoid;
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
                    fighter->x89C_frameSpeedMul += fighter->x8A0_unk;
                }
                fighter->x104--;
                if (fighter->x104 == 0) {
                    func_8006F0FC(fighterObj, fighter->x89C_frameSpeedMul);
                    fighter->x104 = 0x14U;
                }
            }

            if (fighter->x2114_SmashAttr.x2138_smashSinceHitbox != -1.0f) {
                fighter->x2114_SmashAttr.x2138_smashSinceHitbox++;
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

// the stick pairs seen in input structs might make more sense as an array of 2, or a struct of 2 floats.. if it still matches.
#define SET_STICKS(stickXPtr, stickYPtr, x, y) \
    do { \
        f32 *stickX = (f32*)&stickXPtr; \
        f32 *stickY = (f32*)&stickYPtr; \
        *stickX = x; \
        *stickY = y; \
    } while(0)

#define CLEAR_STICKS(stickXPtr) \
    do { \
        f32 *stick = (f32*)&stickXPtr; \
        stick[0] = 0.0f; \
        stick[1] = 0.0f; \
    } while(0)

static void Fighter_Spaghetti_8006AD10_Inner1(Fighter* fighter) {
    s32 temp0_loc[2];

    temp0_loc[0] = (fighter->input.x65C_heldInputs & (fighter->input.x660 ^ fighter->input.x65C_heldInputs));
    temp0_loc[1] = (fighter->input.x660 & (fighter->input.x660 ^ fighter->input.x65C_heldInputs));

    if (fighter->x2219_flag.bits.b5) {
        fighter->input.x668 |= temp0_loc[0];
        fighter->input.x66C |= temp0_loc[1];
    } else {
        fighter->input.x668 = temp0_loc[0];
        fighter->input.x66C = temp0_loc[1];
    }
}

void Fighter_Spaghetti_8006AD10(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;

    f32 tempf1;
    f32 tempf0;

    if (!fighter->x221F_flag.bits.b3) {
        if (!fighter->x2224_flag.bits.b2) {
            
            if (!fighter->x221D_flag.bits.b3) {
                SET_STICKS(fighter->input.x628_lstick_x2, fighter->input.x62C_lstick_y2, fighter->input.x630, fighter->input.x634);
                SET_STICKS(fighter->input.x640_lsubStick_x2, fighter->input.x644_lsubStick_y2, fighter->input.x648, fighter->input.x64C);
                fighter->input.x654 = fighter->input.x658;
                fighter->input.x660 = fighter->input.x664;
                fighter->x221D_flag.bits.b3 = 1;
            } else {
                SET_STICKS(fighter->input.x628_lstick_x2, fighter->input.x62C_lstick_y2, fighter->input.x620_lstick_x, fighter->input.x624_lstick_y);
                SET_STICKS(fighter->input.x640_lsubStick_x2, fighter->input.x644_lsubStick_y2, fighter->input.x638_lsubStick_x, fighter->input.x63C_lsubStick_y);
                fighter->input.x654 = fighter->input.x650;
                fighter->input.x660 = fighter->input.x65C_heldInputs;
            }

            if (func_800A2040(fighter)) {
                SET_STICKS(fighter->input.x620_lstick_x, fighter->input.x624_lstick_y, func_800A17E4(fighter), func_800A1874(fighter));
                if (g_debugLevel < 3  &&  func_8016B41C() == 0) {
                    SET_STICKS(fighter->input.x638_lsubStick_x, fighter->input.x63C_lsubStick_y, func_800A1994(fighter), func_800A1A24(fighter));
                }
                else {
                    CLEAR_STICKS(fighter->input.x638_lsubStick_x);
                }

                tempf0 = func_800A1904(fighter);
                tempf1 = func_800A1948(fighter);

                fighter->input.x650 = (tempf0 > tempf1) ? tempf0 : tempf1;

            } else {
                SET_STICKS(fighter->input.x620_lstick_x, fighter->input.x624_lstick_y, HSD_PadRumbleData[fighter->x618_player_id].nml_stickX, HSD_PadRumbleData[fighter->x618_player_id].nml_stickY);
                if (g_debugLevel < 3  &&  func_8016B41C() == 0) {
                    SET_STICKS(fighter->input.x638_lsubStick_x, fighter->input.x63C_lsubStick_y, HSD_PadRumbleData[fighter->x618_player_id].nml_subStickX, HSD_PadRumbleData[fighter->x618_player_id].nml_subStickY);
                } else {
                    CLEAR_STICKS(fighter->input.x638_lsubStick_x);
                }

                tempf1 = HSD_PadRumbleData[fighter->x618_player_id].nml_analogR;
                tempf0 = HSD_PadRumbleData[fighter->x618_player_id].nml_analogL;

                fighter->input.x650 = (tempf0 > tempf1) ? tempf0 : tempf1;
            }

            if (fabs_inline(fighter->input.x620_lstick_x) <= p_ftCommonData->x0) {
                fighter->input.x620_lstick_x = 0.0f; 
            }

            if (fabs_inline(fighter->input.x624_lstick_y) <= p_ftCommonData->x4) {
                fighter->input.x624_lstick_y = 0.0f;
            }

            if (fabs_inline(fighter->input.x638_lsubStick_x) <= p_ftCommonData->x0) {
                fighter->input.x638_lsubStick_x = 0.0f;
            }
            
            if (fabs_inline(fighter->input.x63C_lsubStick_y) <= p_ftCommonData->x4) {
                fighter->input.x63C_lsubStick_y = 0.0f;
            }

            if (fighter->input.x650 <= p_ftCommonData->x10) {
                fighter->input.x650 = 0.0f;
            }

            
            if (func_800A2040(fighter)) {
                fighter->input.x65C_heldInputs = func_800A198C(fighter);
            } else {
                fighter->input.x65C_heldInputs = HSD_PadRumbleData[fighter->x618_player_id].button;
            }

            if (func_8016B0FC()) {
                fighter->input.x650 = 0.0f;
                if (func_800A2040(fighter)) {
                    fighter->input.x65C_heldInputs = (fighter->input.x65C_heldInputs & 0xD00);
                } else {
                    fighter->input.x65C_heldInputs = (fighter->input.x65C_heldInputs & 0x100);
                }
            } else {
                if ((fighter->input.x65C_heldInputs & 0x60)) {
                    fighter->input.x65C_heldInputs = (s32) (fighter->input.x65C_heldInputs | 0x80000000);
                    fighter->input.x650 = 1.0f;
                } else if (fighter->input.x650) {
                    fighter->input.x65C_heldInputs = (fighter->input.x65C_heldInputs | 0x80000000);
                }
                if (func_801A45E8(0) == 0) {
                    if ((fighter->input.x65C_heldInputs & 0x10)) {
                        fighter->input.x65C_heldInputs = (fighter->input.x65C_heldInputs | 0x80000000 | 0x100);
                        fighter->input.x650 = p_ftCommonData->x14;
                    }
                }
            }

            Fighter_Spaghetti_8006AD10_Inner1(fighter);

            fighter->x676_x++;
            if (fighter->x676_x > 0xFE) {
                fighter->x676_x = 0xFE;
            }

            if (fighter->input.x620_lstick_x >= p_ftCommonData->x8_someStickThreshold) {
                if (fighter->input.x628_lstick_x2 >= p_ftCommonData->x8_someStickThreshold) {
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
            } else if (fighter->input.x620_lstick_x <= -p_ftCommonData->x8_someStickThreshold) {
                if (fighter->input.x628_lstick_x2 <= -p_ftCommonData->x8_someStickThreshold) {
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
            
            if (fighter->input.x624_lstick_y >= p_ftCommonData->xC) {
                if (fighter->input.x62C_lstick_y2 >= p_ftCommonData->xC) {
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
            } else if (fighter->input.x624_lstick_y <= -p_ftCommonData->xC) {
                if (fighter->input.x62C_lstick_y2 <= -p_ftCommonData->xC) {
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
    
            if (func_8000D148(fighter->input.x628_lstick_x2, fighter->input.x62C_lstick_y2, fighter->input.x620_lstick_x, fighter->input.x624_lstick_y, 0.0f, 0.0f, p_ftCommonData->x8_someStickThreshold)) {
                fighter->x67A_y = 0;
                fighter->x679_x = 0;
            }
        
            fighter->x678++;
            if (fighter->x678 > 0xFE) {
                fighter->x678 = 0xFE;
            }
        
            if (fighter->input.x650 >= p_ftCommonData->x18) {
                if (fighter->input.x654 >= p_ftCommonData->x18) {
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
        
            if (fighter->input.x668 & 0x100) {
                fighter->x683 = fighter->x67C;
                fighter->x67C = 0;
            } else if (fighter->x67C < 0xFF) {
                fighter->x67C++;
            }
        
            if (fighter->input.x668 & 0x200) {
                fighter->x67D = 0;
            } else if (fighter->x67D < 0xFF) {
                fighter->x67D++;
            }
        
            if (fighter->input.x668 & 0xC00) {
                fighter->x67E = 0;
            } else if (fighter->x67E < 0xFF) {
                fighter->x67E++;
            }
        
            if (fighter->input.x668 & 8) {
                fighter->x681 = 0;
            } else if (fighter->x681 < 0xFF) {
                fighter->x681++;
            }
        
            if (fighter->input.x668 & 4) {
                fighter->x682 = 0;
            } else if (fighter->x682 < 0xFF) {
                fighter->x682++;
            }
        
            if (fighter->input.x668 & 0x80000000) {
                fighter->x67F = 0;
            } else if (fighter->x67F < 0xFF) {
                fighter->x67F++;
            }
        
            if (fighter->input.x668 & 0x60) {
                fighter->x684 = fighter->x680;
                fighter->x680 = 0;
            } else if (fighter->x680 < 0xFF) {
                fighter->x680++;
            }
    
        }
    
        if (fighter->x221D_flag.bits.b4 || fighter->x2224_flag.bits.b2 || func_801A45E8(2)) {
            fighter->input.x630 = fighter->input.x620_lstick_x;
            fighter->input.x634 = fighter->input.x624_lstick_y;
            fighter->input.x648 = fighter->input.x638_lsubStick_x;
            fighter->input.x64C = fighter->input.x63C_lsubStick_y;
            fighter->input.x658 = fighter->input.x650;
            fighter->input.x664 = fighter->input.x65C_heldInputs;
            fighter->x221D_flag.bits.b3 = 0;
    
            Fighter_UnkInitLoad_80068914_Inner1(fighterObj);
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
#define VEC_CLEAR(vec)                               \
    do {                                             \
        Vec* vecLocal = (void*)&vec;                 \
        f32 c = 0;                                   \
        vecLocal->x = vecLocal->y = vecLocal->z = c; \
    } while(0)

void Fighter_procUpdate(HSD_GObj* fighterObj, s32 dummy) {
    Fighter* fighter = fighterObj->user_data;
    Vec3 windOffset; 

    if (fighter->x221F_flag.bits.b3) {
        return;
    }
    
    if (!fighter->x2219_flag.bits.b5)
    {
        Vec3* p_kb_vel;
        Vec3* pAtkShieldKB;
        Vec3 selfVel;
        float kb_vel_x, kb_vel_y, atkShieldKB_X;

        if (fighter->x2064_ledgeCooldown) 
            fighter->x2064_ledgeCooldown -= 1;

        if (fighter->x2108) 
            fighter->x2108 -= 1;
        
        func_800C0A98(fighterObj);

		if (fighter->cb.x21A4_callback_Phys) {
			fighter->cb.x21A4_callback_Phys(fighterObj);
        }

        p_kb_vel = &fighter->x8c_kb_vel;
		if ((kb_vel_x = p_kb_vel->x) != 0 || p_kb_vel->y != 0)
        {
			if (fighter->xE0_ground_or_air == GA_Air) 
            {
				kb_vel_x = p_kb_vel->x;
				kb_vel_y = p_kb_vel->y;

				if (fighter->x2228_flag.bits.b2) 
                {
                	p_kb_vel->x = func_8007CD6C(p_kb_vel->x, func_8007CDA4(fighter));;
					p_kb_vel->y = func_8007CD6C(p_kb_vel->y, func_8007CDF8(fighter));;
                }
                else 
                {
                    float kb_angle = atan2f(kb_vel_y, kb_vel_x);
					
                    if (sqrtf(kb_vel_x * kb_vel_x + kb_vel_y * kb_vel_y) < p_ftCommonData->x204_knockbackFrameDecay) 
                    {
						p_kb_vel->x = p_kb_vel->y = 0; 
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
                float atkShieldKBAngle = atan2f(kb_y, kb_x);

                if (sqrtf(kb_x*kb_x + kb_y*kb_y) < p_ftCommonData->x3E8_shieldKnockbackFrameDecay)
                {
                    // BUG IN THE MELEE CODE THAT CAUSES THE INVISIBLE CEILING GLITCH
                    // The next line should be 'pAtkShieldKB->y = 0', but instead it is:
                    pAtkShieldKB->x = p_kb_vel->y = 0;
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
        fighter->xE4_ground_accel_1 = fighter->xE8_ground_accel_2 = 0;

        //self_vel += anim_vel
		PSVECAdd(&fighter->x80_self_vel, &fighter->x74_anim_vel, &fighter->x80_self_vel);
        VEC_CLEAR(fighter->x74_anim_vel);
		
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
			float C1 = 1.0f;
            float C2 = C1 - (float)fighter->dmg.x194C / (float)fighter->dmg.x1948;
			
            selfVel.x = C2 * (fighter->x80_self_vel.x - fighter->xA4_unk_vel.x) + fighter->xA4_unk_vel.x;
            selfVel.y = C2 * (fighter->x80_self_vel.y - fighter->xA4_unk_vel.y) + fighter->xA4_unk_vel.y;
            
            fighter->dmg.x194C--;
			if (fighter->dmg.x194C == 0)
				fighter->dmg.x1948 = 0;
        }

		// add some horizontal+depth offset to the position? Why is there no vertical component?
        fighter->xB0_pos.x += fighter->xF8_playerNudgeVel.x;
        fighter->xB0_pos.y += 0;
        fighter->xB0_pos.z += fighter->xF8_playerNudgeVel.y;
        
        if (fighter->x2222_flag.bits.b6 && !fighter->x2222_flag.bits.b7)
        {
            s32 bit;

            // fighter->xD4_unk_vel += selfVel
			PSVECAdd(&fighter->xD4_unk_vel, &selfVel, &fighter->xD4_unk_vel);
			
            fighter->xD4_unk_vel.x += p_kb_vel->x;
            fighter->xD4_unk_vel.y += p_kb_vel->y;
            fighter->xD4_unk_vel.z += 0.0f;

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
                VEC_CLEAR(fighter->xD4_unk_vel);
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
            fighter->xB0_pos.z += 0;

            PSVECAdd(&fighter->xB0_pos, (Vec3*)pAtkShieldKB, &fighter->xB0_pos);
        }
		//accumulate wind hazards into the windOffset vector
		func_getWindOffsetVec_8007B924(fighterObj, /*result vec3*/&windOffset);
    }
    else
    {
        VEC_CLEAR(windOffset);
    }
    
    func_80076528(fighterObj);
    
	if (fighter->cb.x21D0_callback_EveryHitlag) {
        fighter->cb.x21D0_callback_EveryHitlag(fighterObj);
    }
    
	if (fighter->xE0_ground_or_air == GA_Ground)
    {
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

inline HSD_JObj* Fighter_UnkApplyTransformation_8006C0F0_Inner1(HSD_JObj* jobj, Mtx *mtx)
{
    func_80379310(&jobj->mtx, mtx);
    return jobj;
}

void Fighter_UnkApplyTransformation_8006C0F0(HSD_GObj* fighterObj) 
{
    Fighter* fighter = fighterObj->user_data;

    if (fighter->x34_scale.z != 1.0f) {
        HSD_JObj* jobj = fighterObj->hsd_obj;
        Mtx mtx1;
        Mtx mtx2;
        Vec scale;
        Vec translation;
        Quaternion rotation;

        HSD_JObjSetupMatrix(jobj);
        HSD_JObjGetMtx(jobj);
        HSD_JObjGetScale(Fighter_UnkApplyTransformation_8006C0F0_Inner1(jobj, &mtx1), &scale);

        scale.x = Fighter_GetModelScale(fighter);

        HSD_JObjGetRotation(jobj, &rotation);
        HSD_JObjGetTranslation(jobj, &translation);

        func_8037A250(&mtx2, &scale, &rotation, &translation, 0);
        PSMTXConcat(mtx2, mtx1, fighter->x44_mtx);
    }
}

void Fighter_8006C27C(HSD_GObj* fighterObj, s32 unused, s32 unused2, s32 unused3) {

    Fighter* fighter = fighterObj->user_data;

    if (!fighter->x221F_flag.bits.b3) {

        if (fighter->x6F0_collData.x19C) {
            fighter->x6F0_collData.x19C = fighter->x6F0_collData.x19C - 1;
            if (!fighter->x6F0_collData.x19C) {
                func_8007D5BC(fighter);
            }
        }

        fighter->x2223_flag.bits.b5 = 0;

        HSD_JObjSetTranslate(fighterObj->hsd_obj, &fighter->xB0_pos);

        if (fighter->cb.x21A8_callback_Coll) {
            fighter->cb.x21A8_callback_Coll(fighterObj);
            func_800F1D24(fighterObj);
        }

        if (fighter->xE0_ground_or_air == GA_Ground) {
            func_80041280(fighter->xC_playerID, fighter->x221F_flag.bits.b4);
        }

        if (g_debugLevel >= 3) {
            if (fpclassify(fighter->xB0_pos.x) == FP_NAN ||
                fpclassify(fighter->xB0_pos.y) == FP_NAN ||
                fpclassify(fighter->xB0_pos.z) == FP_NAN)
            {
                OSReport("fighter procMap pos error.\tpos.x=%f\tpos.y=%f\n", fighter->xB0_pos.x, fighter->xB0_pos.y);
                __assert(__FILE__, 2590, "0");
            }
        }

        HSD_JObjSetTranslate(fighterObj->hsd_obj, &fighter->xB0_pos);

    }
}

void Fighter_8006C5F4(HSD_GObj* fighterObj)
{
    Fighter* fighter = fighterObj->user_data;
	if (!fighter->x221F_flag.bits.b3)
		func_80089B08(fighterObj);
}

void Fighter_CallAcessoryCallbacks_8006C624(HSD_GObj* fighterObj) {
    Fighter* fighter_r31 = fighterObj->user_data;
    s32 bit = fighter_r31->x221F_flag.bits.b3;

    if (!bit) {
        s32 bit = fighter_r31->x2219_flag.bits.b5;
        if (bit) {
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

inline float Fighter_8006C80C_Inline_1(Fighter* fighter, Vec* cam_offset) {
    return fighter->xB0_pos.y + cam_offset->y;
}

void Fighter_8006C80C(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;

    if (!fighter->x221F_flag.bits.b3) {
        func_80067624(fighterObj, &fighter->x60C);
        Fighter_UnkApplyTransformation_8006C0F0(fighterObj);

        if (!fighter->x2219_flag.bits.b5) {
            if (fighter->cb.x21BC_callback_Accessory4) {
                fighter->cb.x21BC_callback_Accessory4(fighterObj);
            }
        }

        func_8007AE80(fighterObj);
        func_8007C224(fighterObj);
        func_8007C6DC(fighterObj);

        if (fighter->x20A0_accessory) {
            HSD_JObjAnimAll(fighter->x20A0_accessory);
        }

        if (fighter->xE0_ground_or_air == GA_Air && fighter->xB0_pos.y < Stage_GetCamBoundsBottomOffset()) {
            if (func_802FB6E8(fighter->xC_playerID) == 3) {
                Vec cam_offset;
                Stage_UnkSetVec3TCam_Offset(&cam_offset);
            
                if (Fighter_8006C80C_Inline_1(fighter, &cam_offset) < fighter->x2140) {
                    fighter->x2140 = Fighter_8006C80C_Inline_1(fighter, &cam_offset);
                }
            }
        }
    }
}

void Fighter_UnkProcessGrab_8006CA5C(HSD_GObj* fighterObj) {

    Fighter* fighter = fighterObj->user_data;

    if (!fighter->x221F_flag.bits.b3 && !func_8016B1C4()) {
        func_8007BA0C(fighterObj);
        if (fighter->x221E_flag.bits.b6) {
            func_80078A2C(fighterObj);
            if (fighter->x1A58_interactedFighter) {
                if (!fighter->x2225_flag.bits.b1) {
                    func_80088148(fighter, fighter->x10C_ftData->x4C_collisionData->x30, 0x7F, 0x40);
                }
                func_80078754(fighterObj, fighter->x1A58_interactedFighter, 0);
                fighter->cb.x2190_callback_OnGrabFighter_Self(fighterObj);
                fighter->cb.x2198_callback_OnGrabFighter_Victim(fighter->x1A58_interactedFighter, fighterObj);
                return;
            }
            func_8007BC90(fighterObj);

            if (fighter->x1A60) {
                if (!fighter->x2225_flag.bits.b1) {
                    func_80088148(fighter, fighter->x10C_ftData->x4C_collisionData->x30, 0x7F, 0x40);
                }
                func_8027B4A4(fighterObj, fighter->x1A60);
                if (fighter->cb.x2194_callback) {
                    fighter->cb.x2194_callback(fighterObj);
                }
            }
        }

    }
}


void Fighter_8006CB94(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    f32 func_8007BBCC_float_output;

    if (!fighter->x221F_flag.bits.b3 && !fighter->x2219_flag.bits.b1) {
        func_800765E0();
        func_80078C70(fighterObj);
        func_8007C77C(fighterObj);
        func_8007925C(fighterObj);
        func_8007BAC0(fighterObj);
        func_8007C4BC(fighterObj);
        func_8007AB48(fighterObj);
        func_8007AB80(fighterObj);
        func_8007BBCC_float_output = func_8007BBCC(fighterObj);
        if (func_8007BBCC_float_output > 0.0f) {
            func_8007FC7C(fighterObj, func_8007BBCC_float_output);
        }
    }
}


void Fighter_UnkTakeDamage_8006CC30(Fighter* fighter, f32 arg0) {
    Fighter_TakeDamage_8006CC7C(fighter, arg0);
    func_8007EA90(fighter, arg0);
}

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

///https://decomp.me/scratch/9QvFG  
void Fighter_8006CDA4(Fighter* fighter, s32 arg1, s32 arg2, s32 arg3) {
    BOOL temp_bool;
    BOOL hold_item_bool = 0;
    Vec vec;

    if (fighter->x1974_heldItem && !func_8026B2B4(fighter->x1974_heldItem)) {
        hold_item_bool = 1;
    }

    
    temp_bool = !((fighter->x2220_flag.bits.b3 || fighter->x2220_flag.bits.b4 || func_8008E984(fighter)));
    vec = vec3_803B7494;


    if ((fighter->x10_action_state_index) != 0x145 && ((fighter->x10_action_state_index - 0x122) > 1U) &&  fighter->dmg.x1860_dealt != 0xAU  && !fighter->x2226_flag.bits.b2) {
        if (   ///// giant if condition
                hold_item_bool && temp_bool && ((HSD_Randi(p_ftCommonData->x418) < arg1)
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

void Fighter_8006CF5C(Fighter* fighter, s32 arg1) {

   if (!fighter->x2224_flag.bits.b2) {
       fighter->dmg.x18F0 += arg1;
       func_800BFFD0(fighter, 8, 0);
       func_8007EBAC(fighter, 2, 0);
   }
}


void Fighter_UnkSetFlag_8006CFBC(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;

    if (fighter->x2219_flag.bits.b7){
        fighter->x221A_flag.bits.b1 = 1;
    }

}

void Fighter_8006CFE0(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;

    if (fighter->x2219_flag.bits.b7) {
        if (!fighter->x221A_flag.bits.b2) {
            if (!fighter->dmg.x1954){
                Fighter_8006D10C(fighterObj);
            }
        }
        fighter->x2219_flag.bits.b7 = 0;
    }
}

void Fighter_UnkRecursiveFunc_8006D044(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;

    if (fighter->cb.x21D4_callback_EnterHitlag) {
        fighter->cb.x21D4_callback_EnterHitlag(fighterObj);
    }

    fighter->x2219_flag.bits.b5 = 1;

    if (fighter->x1A5C && !fighter->x2219_flag.bits.b7) {
        HSD_GObj* jobj = fighter->x1A5C;

        (getFighter(fighter->x1A5C))->x2219_flag.bits.b7 = 1;

        Fighter_UnkRecursiveFunc_8006D044(jobj);
    }
}

static void Fighter_8006D10C_Inline2(Fighter* new_fighter) {
    HSD_GObj* gobj = new_fighter->x1A5C;
    if (gobj && !new_fighter->x2219_flag.bits.b7) {
        Fighter_8006CFE0(gobj);
    }
}

static void Fighter_8006D10C_Inline1(HSD_GObj* otherObj) {
    Fighter* new_fighter = otherObj->user_data;
    if (new_fighter->x2219_flag.bits.b7) {
        if (!new_fighter->x221A_flag.bits.b2 && !new_fighter->dmg.x1954) {
            if (new_fighter->cb.x21D8_callback_ExitHitlag) {
                new_fighter->cb.x21D8_callback_ExitHitlag(otherObj);
            }
            new_fighter->x2219_flag.bits.b5 = 0;
            Fighter_8006D10C_Inline2(new_fighter);        
        }
        new_fighter->x2219_flag.bits.b7 = 0;
    }
}

void Fighter_8006D10C(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);

    if (fighter->cb.x21D8_callback_ExitHitlag) {
        fighter->cb.x21D8_callback_ExitHitlag(fighterObj);
    }

    fighter->x2219_flag.bits.b5 = 0;

    if (fighter->x1A5C && !fighter->x2219_flag.bits.b7) {
        Fighter_8006D10C_Inline1(fighter->x1A5C);
    }
}

void Fighter_UnkProcessShieldHit_8006D1EC(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    BOOL bool1 = 0;
    s32 action_state_index = fighter->x10_action_state_index;
    BOOL bool2 = 0;
    BOOL bool3 = 0;
    BOOL bool4 = 0;
    f32 forceAppliedOnHit;

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
            fighter->x1998_shieldHealth -= (p_ftCommonData->x284 * ((fighter->x19A0_shieldDamageTaken) * (1.0f - ((fighter->x199C_shieldLightshieldAmt * (p_ftCommonData->x2E0 - p_ftCommonData->x2DC)) + p_ftCommonData->x2DC)))) + p_ftCommonData->x288;
            if (fighter->x1998_shieldHealth < 0.0f) {
                bool3 = 1;
                fighter->x1998_shieldHealth = p_ftCommonData->x280_unkShieldHealth;
                /// this function is called when shield is broken
                func_8003E058(fighter->x19BC_shieldDamageTaken3, fighter->x221F_flag.bits.b6, fighter->xC_playerID, fighter->x221F_flag.bits.b4);
            }
        }

        if (fighter->dmg.x189C_unk_num_frames > 0.0f) {
            fighter->dmg.x189C_unk_num_frames--;
            if (fighter->dmg.x189C_unk_num_frames <= 0.0f && !fighter->dmg.x1850_forceApplied) {
                fighter->dmg.x189C_unk_num_frames = 0.0f;
                func_8007BE3C(fighterObj);
            }
        }

        forceAppliedOnHit = fighter->dmg.x1850_forceApplied;
        if (forceAppliedOnHit) {
            s32 ground_or_air = fighter->xE0_ground_or_air;
            BOOL damage_bool;

            fighter->dmg.x189C_unk_num_frames = 0.0f;
            Fighter_UnkTakeDamage_8006CC30(fighter, fighter->dmg.x1838_percentTemp);
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

                damage_bool = fighter->dmg.x183C_applied;
                bool2 = 1;
                func_80090594(fighter, fighter->dmg.x1860_dealt, damage_bool, action_state_index, ground_or_air, fighter->x1960_vibrateMult);
                func_8007ED50(fighter, fighter->dmg.x1838_percentTemp);
                bool1 = damage_bool;
                
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
            bool1 = fighter->dmg.x1840;
            bool4 = 1;
        } else if (fighter->x19A4) {
            if (bool3) {
                func_80098B20(fighterObj);
                func_80088148(fighter, 0x82, 0x7F, 0x40);
            } else {
                if (fighter->cb.x21C4_callback_OnShieldHit) {
                    fighter->cb.x21C4_callback_OnShieldHit(fighterObj);
                }
            }
            bool1 = fighter->x19A4;
        } else if (fighter->dmg.x1918) {
            if ((fighter->dmg.x191C) && (!fighter->x1A58_interactedFighter) && (!fighter->x1A60)) {
                func_8007DB58(fighterObj);
                func_80099D9C(fighterObj);
            }
            bool1 = fighter->dmg.x1918;
        } else if (fighter->dmg.x1914) {
            if (fighter->cb.x21C0_callback_OnGiveDamage) {
                fighter->cb.x21C0_callback_OnGiveDamage(fighterObj);
            }
            bool1 = fighter->dmg.x1914;
            if (fighter->x2073 == 0x46U) {
                func_8007EBAC(fighter, 0xE, 0);
            } else {
                func_8007EE0C(fighter, fighter->dmg.x1914);
            }
        } else {
            if (fighter->dmg.x1924) {
                bool1 = fighter->dmg.x1924;
            } else if (fighter->ReflectAttr.x1A3C_damageOver) {
                func_80098C9C(fighterObj);
            } else if (fighter->ReflectAttr.x1A2C_reflectHitDirection) {
                if (fighter->cb.x21C8_callback_OnReflectHit) {
                    fighter->cb.x21C8_callback_OnReflectHit(fighterObj);
                }
            } else if (fighter->AbsorbAttr.x1A40_absorbHitDirection) {
                if (ft_OnAbsorb[fighter->x4_fighterKind]) {
                    ft_OnAbsorb[fighter->x4_fighterKind](fighterObj);
                }
            } else if (fighter->x20AC) {
                if (fighter->cb.x21F4_callback) {
                    fighter->cb.x21F4_callback(fighterObj);
                }
            }
        }

        if(!forceAppliedOnHit && fighter->dmg.x1838_percentTemp) {
            Fighter_UnkTakeDamage_8006CC30(fighter, fighter->dmg.x1838_percentTemp);
            func_800F5C34(fighter);
            func_800804FC(fighter);
        }
        func_800C8D00(fighterObj);
        
        if (bool1) {
            fighter->dmg.x195c_hitlag_frames = func_8007DA74(bool1, action_state_index, fighter->x1960_vibrateMult);
            if (fighter->dmg.x195c_hitlag_frames < fighter->x1964) {
                fighter->dmg.x195c_hitlag_frames = fighter->x1964;
            }
            if (fighter->dmg.x195c_hitlag_frames > 0.0f) {
                if (fighter->dmg.x195c_hitlag_frames > p_ftCommonData->x194_unkHitLagFrames) {
                    fighter->dmg.x195c_hitlag_frames = p_ftCommonData->x194_unkHitLagFrames;
                }
                fighter->x221A_flag.bits.b2 = 1;
                if (bool2) {
                    fighter->x221A_flag.bits.b3 = 1;
                }
                if (bool4) {
                    fighter->dmg.x189C_unk_num_frames = fighter->dmg.x195c_hitlag_frames;
                }
                if (!fighter->x2219_flag.bits.b5) {
                    Fighter_UnkRecursiveFunc_8006D044(fighterObj);
                }
            }
        } else {
            func_80090718(fighter);
        }

        if (fighter->x221A_flag.bits.b0 || fighter->dmg.x1958) {
            if (!fighter->x2219_flag.bits.b5) {
                Fighter_UnkRecursiveFunc_8006D044(fighterObj);
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
            float eval = (fighter->dmg.x1928 * p_ftCommonData->x3E0) + p_ftCommonData->x3E4;
            fighter->xF4_ground_attacker_shield_kb_vel = (fighter->dmg.x192c < 0.0f) ? eval : -eval;
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
        fighter->x20AC = NULL;
        fighter->x221C_flag.bits.b5 = 0;
        
        fighter->dmg.x1924 = 0;
        fighter->dmg.x1928 = 0.0f;
        fighter->x19A0_shieldDamageTaken = 0;
        fighter->x19A4 = 0;
        fighter->x19A8 = 0;
        fighter->ReflectAttr.x1A3C_damageOver = 0;
        fighter->ReflectAttr.x1A2C_reflectHitDirection = 0.0f;
        fighter->AbsorbAttr.x1A40_absorbHitDirection = 0.0f;
        fighter->AbsorbAttr.x1A44_damageTaken = 0;
        fighter->AbsorbAttr.x1A48_hitsTaken = 0;
        fighter->x1960_vibrateMult = 1.0f;
        fighter->x1964 = 0.0f;
        fighter->dmg.x1950 = 0;

        if (!fighter->x2219_flag.bits.b6 || fighter->dmg.x18F4) {
            func_800C2FD8(fighterObj);
        }
        func_800A0DA4(fighter);   
    }
}

void Fighter_8006D9AC(HSD_GObj* fighterObj) {
    Fighter* fighter;
    fighter  = fighterObj->user_data;

    if (fighter->x221F_flag.bits.b3 || fighter->x2219_flag.bits.b5) return;

    func_8009E0A8(fighterObj);
}


void Fighter_UnkCallCameraCallback_8006D9EC(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;

    if (!fighter->x221F_flag.bits.b3) {
        func_8008021C(fighterObj);
        if (fighter->cb.x21AC_callback_Cam) {
            fighter->cb.x21AC_callback_Cam(fighterObj);
        }
    }

}


void Fighter_8006DA4C(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;

    if (!fighter->x221F_flag.bits.b3) {
        Player_80032828(fighter->xC_playerID, fighter->x221F_flag.bits.b4, &fighter->xB0_pos);
        Player_SetFacingDirectionConditional(fighter->xC_playerID, fighter->x221F_flag.bits.b4, fighter->x2C_facing_direction);
        func_8003FAA8(fighter->xC_playerID, fighter->x221F_flag.bits.b4, &fighter->xB0_pos, &fighter->xBC_prevPos);
    }
}

///https://decomp.me/scratch/MGqg7  --- very weird match using uninitialized pointer and compiler warning

inline HSD_ObjAllocData* sub_func(Fighter* uninitalized_fighter, Fighter* fighter_real) {

    HSD_ObjAllocData* objAllocData = &lbl_80458FD0;
    
    if (ft_OnUserDataRemove[uninitalized_fighter->x4_fighterKind]) {
        ft_OnUserDataRemove[uninitalized_fighter->x4_fighterKind](fighter_real->x0_fighter);
    }

    return objAllocData;
}

void Fighter_Unload_8006DABC(Fighter* fighter) {
    Fighter* uninitalized_fighter;

    HSD_ObjAllocData *objAllocData = &lbl_80458FD0;
    objAllocData = sub_func(uninitalized_fighter, fighter);

    func_8007B8E8(fighter->x0_fighter);
    func_80067688(&fighter->x60C);
    func_8026B7F8(fighter->x0_fighter);
    func_800290D4(fighter->x890_cameraBox);
    func_8009E0D4(fighter);
    func_800765AC(fighter->x0_fighter);
    func_80088C5C(fighter->x0_fighter);
    func_8000EE8C(&fighter->x20A4);
    if (fighter->x20A0_accessory) {
        HSD_JObjRemoveAll(fighter->x20A0_accessory);
    }
    HSD_JObjRemoveAll(fighter->x8AC_animSkeleton);
    HSD_JObjUnref(fighter->x2184);
    func_800859A8(fighter);
    func_80366BD4(fighter->x588);
    Player_80031FB0(fighter->xC_playerID, fighter->x221F_flag.bits.b4);
    
    HSD_ObjFree(&objAllocData[(0xDC / 40)], fighter->x59C);
    HSD_ObjFree(&objAllocData[(0xDC / 40)], fighter->x5A0);
    HSD_ObjFree(&objAllocData[(0x58 / 40)], fighter->x5E8_fighterBones);
    HSD_ObjFree(&objAllocData[(0x84 / 40)], fighter->x5F0);
    HSD_ObjFree(&objAllocData[(0xB0 / 40)], fighter->x2040);
    HSD_ObjFree(&objAllocData[(0x2C / 40)], fighter->x2D8_specialAttributes2);
    HSD_ObjFree(objAllocData, fighter);

}
