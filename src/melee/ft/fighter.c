#include "fighter.h"


// ==== external variables ====
// ============================

// external vars from asm/melee/ft/code_8008521C.s
typedef void (*ft_callback)(HSD_GObj* gobj);
typedef void (*fn_ptr_t)();
// TODO: use something like NUM_FIGHTERS instead of hardcoding 33. The code (loops!) must also be changed.
extern ft_callback ft_OnLoad[33];  // One load  callback for every character.
extern ft_callback ft_OnDeath[33]; // One death callback for every character.
extern fn_ptr_t lbl_803C10D0[33];

extern void* ft_OnAbsorb;
extern struct Pair_Pointer_and_Flag lbl_803C0EC0[33];

extern ftData* lbl_804598B8[33];
extern struct S_TEMP3 lbl_803C2800[33];
extern struct S_TEMP3* lbl_803C12E0[33];

extern s32 lbl_803C125C;
extern s32 lbl_803C1DB4;
extern s8 lbl_803C26FC[33];

extern HSD_ObjAllocData lbl_804590AC; // from ft/ftparts.s
extern HSD_ObjAllocData lbl_80458FD0;
extern HSD_ObjAllocData lbl_80458FFC;

extern HSD_RumbleData HSD_PadRumbleData[4]; // from sysdolphin/baselib/controller.s

typedef struct StageInfo { u8 filler[0x748]; };
extern StageInfo stage_info; // from asm/melee/text_2.s

// TODO: rename this var globally
extern s32 lbl_804D4A08; // asm/melee/db/code_80225374.s
#define g_debugLevel lbl_804D4A08

extern u8 lbl_804D7849; // asm/sysdolphin/baselib/gobj.s

// ==== fighter.c variables ====
// =============================

// .section .rodata

extern const Vec3 lbl_803B7488; // = (0,0,0)
extern const Vec3 lbl_803B7494; // = (0,0,0)

// .section .data

extern char lbl_803C0530[];// = "PlCo.dat";
extern char lbl_803C053C[];// = "ftLoadCommonData";
extern char lbl_803C0550[];// = "translate";
extern char lbl_803C055C[];// = "fighter sub color num over!\n";
extern char lbl_803C057C[];// = "fighter.c";
extern char lbl_803C0588[];// = "ellegal flag fp->no_normal_motion\n";
extern char lbl_803C05AC[];
    //.asciz "fighter procUpdate pos error.\tpos.x=%f\tpos.y=%f\n"
    //.balign 4
    //.asciz "fighter procMap pos error.\tpos.x=%f\tpos.y=%f\n"
    //.balign 4
extern char lbl_803C0610[];// = "ellegal flag fp->no_reaction_always\n";

// .section .bss, "wa"

extern HSD_ObjAllocData lbl_80458FD0;
extern HSD_ObjAllocData lbl_80458FFC;

// .section .sdata

extern const char* lbl_804D3A00;// = "jobj.h";
extern const char* lbl_804D3A08;// = "jobj";
extern const char* lbl_804D3A10;// = "0";

// .section .sbss

// TODO: verify that this is really a spawn number counter, then rename this var globally
extern u32 lbl_804D64F8;// = 0;
#define g_spawnNumCounter lbl_804D64F8

// the following seems to be an array, initialized in reverse in func_80067ABC
// outcommented because they are in variables.h too. uncomment this when moving data from fighter.s here.
//extern void* lbl_804D64FC;// = 0;
//extern void* lbl_804D6500;// = 0;
//extern void* lbl_804D6504;// = 0;
//extern void* lbl_804D6508;// = 0;
//extern void* lbl_804D650C;// = 0;
//extern void* lbl_804D6510;// = 0;
//extern void* lbl_804D6514;// = 0;
//extern void* lbl_804D6518;// = 0;
//extern void* lbl_804D651C;// = 0;
//extern void* lbl_804D6520;// = 0;
//extern void* lbl_804D6524;// = 0;
//extern void* lbl_804D6528;// = 0;
//extern void* lbl_804D652C;// = 0;
//extern void* lbl_804D6530;// = 0;
//extern void* lbl_804D6534;// = 0;
//extern void* lbl_804D6538;// = 0;
//extern void* lbl_804D653C;// = 0;
//extern s32** lbl_804D6540;// = 0;
//extern void* lbl_804D6544;// = 0;
//extern void* lbl_804D6548;// = 0;
//extern void* lbl_804D654C;// = 0;
//extern void* lbl_804D6550;// = 0;
//extern ftCommonData* lbl_804D6554;// = 0; // p_ftCommonData
#define p_ftCommonData lbl_804D6554 
 
// .section .sdata2
 
extern const f32 lbl_804D8250;// = 1.0f;
extern const f32 lbl_804D8254;// = 0.0f;
extern const f32 lbl_804D8258;// = -1.0f;
extern const f32 lbl_804D8260;// used for int to float casting
extern const f32 lbl_804D8268;// = 8.55f
extern const f64 lbl_804D8270;// = 1.5707963267948966;
extern const f64 lbl_804D8278;// probably also used for int to float casting
extern const f64 lbl_804D8280;// = 0.5;
extern const f64 lbl_804D8288;// = 3.0;
extern const f32 lbl_804D8290;// = 999.0;


// ==== fighter.c functions ====
// =============================

void func_800679B0()
{ 
	s32 i;

	// @WARNING: don't hardcode the allocation sizes
	HSD_ObjAllocInit(&lbl_80458FD0+0, /*size*/0x23ec, /*align*/4);
	HSD_ObjAllocInit(&lbl_80458FD0+1, /*size*/0x424 , /*align*/4);
	func_800852B0();
	func_80067ABC();
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

void func_80067A84()
{
	func_800679B0();
	HSD_ObjAllocInit(&lbl_804590AC, /*size*/0x0000800000008000, /*align*/0x20); // TODO: size parameter too large to be only the size. maybe this contains flags. In other function calls, size only looks plausible. Or is this virtual memory?
}

// https://decomp.me/scratch/vwlfi
/// updated context https://decomp.me/scratch/R2MBC
void func_80067ABC()
{
    void** pData;
    func_80016C64(lbl_803C0530, &pData, lbl_803C053C, 0);

	// copy 23 4-byte chunks from pData to lbl_804D6554 in reverse order, equivalent to this:
	// for(i=0; i<23; i++)
	//   (&lbl_804D64FC)[23-1-i] = pData[i];
	// loop unrolling doesn't work (only up to 8 elements)
	lbl_804D6554 = pData[0]; // p_ftCommonData
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

// https://decomp.me/scratch/Pc28y
// Matches
void func_80067BB4(HSD_GObj* pPlayerEntity)
{
    Vec scale_sp14;
    s32 unused;

    Fighter* pFighter = pPlayerEntity->user_data;

    HSD_JObj* jobj = pPlayerEntity->hsd_obj;
    //@1c
    f32 modelScale_f1 = func_8007F694(pFighter); 
    if (pFighter->x34_scale.z != 1.0f)
        scale_sp14.x = pFighter->x34_scale.z;
    else
        scale_sp14.x = modelScale_f1;
    
    scale_sp14.y = modelScale_f1;
    scale_sp14.z = modelScale_f1;

    HSD_JObjSetScale(jobj, &scale_sp14);
}

// Fake Match:  https://decomp.me/scratch/Pegi9
// Fake Match:  https://decomp.me/scratch/dEh27
// https://decomp.me/scratch/Xx6cI -- No Match, one mr instruction is shifted.

void func_80067C98(register Fighter* ft) {
	Vec3 spC_player_coord;
	f32 x,y,z;
	register Fighter* tmp;

	ft->x8_spawnNum = func_80068E40();
	Player_800326CC(ft->xC_playerID, &spC_player_coord); //PlayerBlock_LoadPlayerCoords_StoreToR4
	ft->x2C_facing_direction = Player_GetFacingDirection(ft->xC_playerID); // PlayerBlock_LoadFacingDirection

	spC_player_coord.x = ft->x2C_facing_direction * func_800804EC(ft) + spC_player_coord.x;
	x = spC_player_coord.x;
	ft->xB0_pos.x = x;
	ft->xBC_prevPos.x = x;

	y = spC_player_coord.y;
	ft->xB0_pos.y = y;
	ft->xBC_prevPos.y = y;

	z = spC_player_coord.z;
	ft->xB0_pos.z = z;
	ft->xBC_prevPos.z = z;

	ft->x30_facingDirectionRepeated = ft->x2C_facing_direction;
	ft->x34_scale.y = ft->x34_scale.x;

	ft->x2220_flag.bits.b5 = 0;
	ft->x2220_flag.bits.b6 = 0;

	ft->x200C = 0;
	ft->x2010 = 0;
	ft->x2008 = 0;

	ft->x2219_flag.bits.b1 = 0;
	ft->x2219_flag.bits.b2 = 0;
	ft->x2219_flag.bits.b3 = 0;
	ft->x2219_flag.bits.b4 = 0;
	ft->x221A_flag.bits.b5 = 0;
	ft->x221A_flag.bits.b6 = 0;
	ft->x221D_flag.bits.b2 = 0;
	ft->x221E_flag.bits.b7 = 0;
	ft->x2220_flag.bits.b7 = 0;
	ft->x2221_flag.bits.b4 = 0;
	ft->x2221_flag.bits.b5 = 0;
	ft->x2221_flag.bits.b6 = 1;
	ft->x2221_flag.bits.b7 = 0;

	ft->x61D = 255;

	ft->xC8_pos_delta.z /*xD0*/ = 0.0f;//lbl_804D8254
	ft->xC8_pos_delta.y /*xCC*/ = 0.0f;//lbl_804D8254
	ft->xC8_pos_delta.x = 0.0f;//lbl_804D8254
	ft->x894 = 0.0f;//lbl_804D8254
	ft->x898 = 0.0f;//lbl_804D8254

	ft->x89C = 1.0f;//lbl_804D8250
	ft->x8A0 = 1.0f;//lbl_804D8250
	ft->dmg.x1850_forceApplied = 0.0f;//lbl_804D8254
	ft->dmg.x18A4_knockbackMagnitude = 0.0f;//lbl_804D8254
	ft->dmg.x18A8 = 0.0f;//lbl_804D8254
	ft->dmg.x18ac_time_since_hit = -1;
	ft->dmg.x18B0 = 0.0f;//lbl_804D8254
	ft->dmg.x18B4_armor = 0.0f;//lbl_804D8254
	ft->x1828 = 0;

	ft->x221C_flag.bits.b6 = 0;

	ft->dmg.x18a0 = 0.0f;//lbl_804D8254
	ft->x1968_jumpsUsed = 0;
	ft->x1969_walljumpUsed = 0;
	ft->x196C_hitlag_mult = 0.0f;//lbl_804D8254
	ft->x2064_ledgeCooldown = 0;

	//@1b4
	ft->dmg.x1838_percentTemp = Player_GetDamage(ft->xC_playerID);

	ft->dmg.x1838_percentTemp = 0.0f;//lbl_804D8254

	ft->dmg.x183C_applied = 0;
	ft->dmg.x18C0 = 0;

	ft->dmg.x18c4_source_ply = 6;
	ft->dmg.x18C8 = -1;
	ft->dmg.x18F0 = 0;
	ft->dmg.x18CC = 0;
	ft->dmg.x18D0 = -10;

	ft->x221F_flag.bits.b5 = 0;
	ft->x2221_flag.bits.b1 = 0;

	ft->dmg.x18F4 = 0;
	ft->dmg.x18F8 = 1;
	ft->dmg.x18fa_model_shift_frames = 0;
	ft->dmg.x18FD = 0;
	ft->dmg.x18FC = 0;
	ft->dmg.x1834 = 0.0f;//lbl_804D8254

	ft->x2222_flag.bits.b2 = 0;

	ft->dmg.x1840 = 0;

	ft->x2219_flag.bits.b5 = 0; // freeze bit?
	ft->x2219_flag.bits.b6 = 0;
	ft->x2219_flag.bits.b7 = 0;
	ft->x221A_flag.bits.b0 = 0;
	ft->x221A_flag.bits.b1 = 0;

	ft->dmg.x1954 = 0.0f;//lbl_804D8254
	ft->dmg.x1958 = 0.0f;//lbl_804D8254

	ft->x221A_flag.bits.b2 = 0;

	ft->dmg.x195c_hitlag_frames = 0.0f;//lbl_804D8254

	ft->x221A_flag.bits.b3 = 0;
	ft->x1960_vibrateMult = 1.0f;//lbl_804D8250
	ft->x1964 = 0.0f;//lbl_804D8254
	ft->dmg.x189C = 0.0f;//lbl_804D8254

	ft->x2220_flag.bits.b3 = 0;
	ft->x2220_flag.bits.b4 = 0;

	ft->dmg.x1914 = 0;
	ft->dmg.x1918 = 0;
	ft->dmg.x191C = 0.0f;//lbl_804D8254
	ft->dmg.x1924 = 0;
	ft->dmg.x1928 = 0.0f;//lbl_804D8254

	ft->x2223_flag.bits.b5 = 0;

	ft->dmg.x1950 = 0;
	ft->dmg.x1948 = 0;

	ft->x2223_flag.bits.b4 = 0;

	ft->xF8_playerNudgeVel.y/*FC*/ = 0.0f;//lbl_804D8254
	ft->xF8_playerNudgeVel.x/*F8*/ = 0.0f;//lbl_804D8254
	ft->x100 = -1.0f;//lbl_804D8258;

	ft->x2222_flag.bits.b7 = 0;
	ft->x2223_flag.bits.b0 = 0;
	ft->x221A_flag.bits.b4 = 0;
	ft->x2219_flag.bits.b0 = 0;

	ft->x20A0 = 0;
	ft->x2210_ThrowFlags.flags = 0;
	ft->x2214 = 0.0f;//lbl_804D8254
	ft->x1974_heldItem = 0;
	ft->x1978 = 0;

	ft->x221E_flag.bits.b3 = 1;

	ft->x1984_heldItemSpec = 0;
	ft->x1988 = 0;
	ft->x198C = 0;

	ft->x2221_flag.bits.b0 = 0;

	ft->x1990 = 0;
	ft->x1994 = 0;

	ft->x221D_flag.bits.b6 = 0;
	ft->x221B_flag.bits.b5 = 0;

	ft->x1A58 = 0;
	ft->x1A5C = 0;

	ft->x221B_flag.bits.b6 = 0;

	ft->x1A60 = 0;
	ft->x1A64 = 0;

	ft->x221B_flag.bits.b7 = 0;
	ft->x221C_flag.bits.b0 = 0;

	ft->x1064_thrownHitbox.x134 /*x1198*/ = 0;
	ft->x221C_u16_y = 0;
	ft->x20AC = 0;
	ft->x221C_flag.bits.b5 = 0;

	ft->x214C = -1;
	ft->x2148 = -1;
	ft->x2144 = -1;
	ft->x2160 = -1;
	ft->x215C = -1;
	ft->x2158 = -1;
	ft->x2154 = -1;
	ft->x2150 = -1;
	ft->x2168 = 0;
	ft->x2164 = 0;
	ft->x208C = 0;
	ft->x2090 = 0;
	ft->x2098 = 0;
	ft->x2092 = 0;
	ft->x2094 = 0;
	ft->x1998_shieldHealth = p_ftCommonData->x260;

	ft->x221A_flag.bits.b7 = 0;
    ft->x221B_flag.bits.b0 = 0;
	ft->x221B_flag.bits.b1 = 0;
	ft->x221B_flag.bits.b3= 0;
	ft->x221B_flag.bits.b4 = 0;
	ft->x221C_flag.bits.b3 = 0;
	ft->x221C_flag.bits.b1 = 0;
	ft->x221C_flag.bits.b2 = 0;

	ft->x19A0_shieldDamageTaken = 0;
	ft->x19A4 = 0;
	ft->x199C_shieldLightshieldAmt = 0.0f;//lbl_804D8254
	ft->x19A8 = 0;
	ft->x19B4_shieldUnk = 0.0f;//lbl_804D8254
	ft->x19B8_shieldUnk = 0.0f;//lbl_804D8254
	ft->x19BC_shieldDamageTaken3 = 6;

	ft->x221F_flag.bits.b6 = 0;
	ft->x2218_flag.bits.b3 = 0;
	ft->x2218_flag.bits.b4 = 0;
	ft->x1A3C = 0;
	ft->x1A2C_reflectHitDirection = 0.0f;//lbl_804D8254
	ft->x2218_flag.bits.b6 = 0; // addi r3, ft, 0
	ft->x2218_flag.bits.b7 = 0;

	asm {
		mr tmp, ft
	}

	ft->x1A40 = 0.0f;//lbl_804D8254
	// -> mr r3, ft


	ft->x1A44 = 0;
	ft->x1A48 = 0;

	ft->x68C_transNPos.z/*x694*/ = 0.0f;//lbl_804D8254
	ft->x68C_transNPos.y/*x690*/ = 0.0f;//lbl_804D8254
	ft->x68C_transNPos.x/*x68C*/ = 0.0f;//lbl_804D8254
	ft->x6A4_transNOffset.z/*x6AC*/ = 0.0f;//lbl_804D8254
	ft->x6A4_transNOffset.y/*x6A8*/ = 0.0f;//lbl_804D8254
	ft->x6A4_transNOffset.x/*x6A4*/ = 0.0f;//lbl_804D8254
	ft->x6BC_inputStickangle = 0.0f;//lbl_804D8254
	// TODO: following three elements probably a vector because of the reverse order init that happens a lot with vectors
	ft->x6C0.z = 0.0f;//lbl_804D8254
	ft->x6C0.y = 0.0f;//lbl_804D8254
	ft->x6C0.x = 0.0f;//lbl_804D8254
	// TODO: another vector probably
	ft->x6D8.z = 0.0f;//lbl_804D8254
	ft->x6D8.y = 0.0f;//lbl_804D8254
	ft->x6D8.x = 0.0f;//lbl_804D8254

	ft->x209C = 0;
	ft->x2224_flag.bits.b1 = 0;
	ft->cb.x21E4_callback_OnDeath2 = 0;
	ft->x2100 = -1;
	ft->x2101_bits_0to6 = 0;
	ft->cb.x21B4_callback_Accessory2 = 0;
	ft->cb.x21B8_callback_Accessory3 = 0;
	ft->cb.x21E0_callback_OnDeath = 0;
	ft->cb.x21E8_callback_OnDeath3 = 0;
	ft->x221E_flag.bits.b4 = 1;
	ft->x197C = 0;
	ft->x2223_flag.bits.b7 = 0;
	ft->x2028 = 0;
	ft->x202C = 0;

	// sets some fighter flags and values to 0, see https://decomp.me/scratch/VBrFf
	// using ft=tmp makes the compiler use the correct mr r3,ft instead of addi r3,ft,0.
	// The mr is still in the wrong place.
	func_800C88A0(tmp);


	//@598
	ft->x2227_flag.bits.b3 = 0;
	ft->x2034 = 0;
	ft->x2038 = 0;
	ft->x1980 = 0;

	//@5b4 TODO: write the assembly pattern that this generates down somewhere
	ft->x2224_flag.bits.b2 = ft->x2224_flag.bits.b3 = 0;

	//@5d0
	ft->x2224_flag.bits.b4 = 0;
	ft->x2108 = 0;
	ft->x2224_flag.bits.b5 = 0;
	ft->x1A53 = (s8) 0;
	ft->x1A52 = (s8) 0;
	ft->x210C_walljumpInputTimer = 254;
	ft->dmg.x1910 = 0;
	ft->x2225_flag.bits.b0 = 0;
	ft->x2225_flag.bits.b2 = 1;
	ft->x2225_flag.bits.b4 = 0;
	func_800DEEA8(tmp->x0_fighter);
	ft->dmg.x18BC = 0.0f;//lbl_804D8254
	ft->dmg.x18B8 = 0.0f;//lbl_804D8254
	ft->x2226_flag.bits.b2 = 0;
	ft->x2170 = 0.0f;//lbl_804D8254
	ft->x2225_flag.bits.b6 = ft->x2225_flag.bits.b5;
	ft->dmg.x1908 = -1;
	ft->dmg.x190C = 0;
	ft->x2227_flag.bits.b4 = 0;
	ft->x2138_smashSinceHitbox = -1.0f;//lbl_804D8258;
	ft->x213C = -1;
	ft->x2227_flag.bits.b5 = 0;
	ft->x2228_flag.bits.b1 = 0;
	ft->x2140 = 0.0f;//lbl_804D8254
	ft->x2227_flag.bits.b6 = 0;
	ft->x2180 = 6;
	ft->x2229_b4 = 1;
}


//// https://decomp.me/scratch/vhZiK
// Matches
void func_80068354(HSD_GObj* fighterObj/*r30*/) {
 	void (*temp_r12)(HSD_GObj* gobj);
    Vec3 vec_sp20;
    f32 temp_f1;
    HSD_JObj* jobj;

    Fighter* fighter_r29;
    s32 unused[2];
    HSD_JObj* temp_r28;
    // s32 dummy[4];void* dummyx;

    //@20
    Fighter* fighter_r31;
    fighter_r31  = fighterObj->user_data;


    //@24
    func_80067C98(fighter_r31);
    jobj = fighterObj->hsd_obj;
    temp_r28 = jobj;

    //@2c
    // HSD_JObjCheckObj(jobj);
    HSD_JObjSetTranslate(temp_r28, &fighter_r31->xB0_pos);

    //@d0
    func_800D105C(fighterObj);
    func_800C09B4(fighterObj);
    func_8007E2FC(fighterObj);
    func_80088A50(fighter_r31);
    func_800890BC(fighter_r31);
    func_800892D4(fighter_r31);
    func_80081B38(fighterObj);
    func_80081938(fighterObj);
    //@110
    if (fighter_r31->x2135 == -1)
    {
        if (func_80082A68(fighterObj) && !fighter_r31->x2229_b6)
            func_8007D6A4(fighter_r31);
        else
            func_8007D5D4(fighter_r31);
    }
    else
        func_8007D5D4(fighter_r31);
    //@15c
    func_80076064(fighter_r31);
    //@164
    temp_r28 = jobj = fighterObj->hsd_obj;
    // HSD_JObjCheckObj(jobj);
    HSD_JObjSetTranslate(jobj, &fighter_r31->xB0_pos);

    //@208
    func_8006C0F0(fighterObj);
    //@210
        jobj = fighterObj->hsd_obj;

    fighter_r29 = fighterObj->user_data;
    //@218
    temp_f1 = func_8007F694(fighterObj->user_data);
    //@220
    if (1.0f/*lbl_804D8250*/ != fighter_r29->x34_scale.z)
        vec_sp20.x = fighter_r29->x34_scale.z;
    else
        //@238
        vec_sp20.x = temp_f1;
    //@23c
    vec_sp20.y = temp_f1;
    vec_sp20.z = temp_f1;
    //@248
    HSD_JObjSetScale(jobj, &vec_sp20);


    //@2c8
    func_800BFFAC(fighter_r31);
    func_800C0074(fighter_r31);
    func_800C8438(fighterObj);
    func_800C89A0(fighterObj);
    func_800C8FC4(fighterObj);
    func_8007AFF8(fighterObj);
    func_8007B0C0(fighterObj, 0);
    //@304
    if (ft_OnDeath[fighter_r31->x4_fighterKind])
        ft_OnDeath[fighter_r31->x4_fighterKind](fighterObj);
    //@330
    func_800A101C(fighter_r31, Player_GetCpuType(fighter_r31->xC_playerID), Player_GetCpuLevel(fighter_r31->xC_playerID), 0);
    //@358
    func_80067688(&fighter_r31->x60C);
    func_8007C17C(fighterObj);
    func_8007C630(fighterObj);
}



///https://decomp.me/scratch/ozjB3
void func_800686E4(HSD_GObj* fighterObj) {
    HSD_JObj* jobj;

    UnkFighterJointStruct* temp_r3;
    Fighter* fighter_r31;
    fighter_r31  = fighterObj->user_data;


    temp_r3 = lbl_803C0EC0[fighter_r31->x4_fighterKind].unk_fighter_struct;

    fighter_r31->x108_costume_archive = temp_r3[fighter_r31->x619_costume_id].joint;

    func_80074148();
    jobj = HSD_JObjLoadJoint(fighter_r31->x108_costume_archive);
    func_80074170();
    func_80073758(jobj);
    func_80390A70(fighterObj, lbl_804D7849, jobj);
}


///https://decomp.me/scratch/5mxVU
void func_8006876C(Fighter* fighter) {

    Vec vec;
    Vec vec2;
    HSD_JObj* temp_r31 = fighter->x5E8_fighterBones[func_8007500C(fighter, 2)].x0_jobj;

    HSD_JObjGetTranslation(temp_r31, &vec);

    fighter->x1A6C = (vec.y / 8.55f);

    func_8000B1CC(temp_r31, 0, &vec);
    func_8000B1CC(fighter->x5E8_fighterBones[func_8007500C(fighter, 1)].x0_jobj, 0, &vec2);
    fighter->x1A70.x = vec2.x - vec.x;
    fighter->x1A70.y = vec2.y - vec.y;
    fighter->x1A70.z = vec2.z - vec.z;
}

///https://decomp.me/scratch/a0kYg
void func_80068854(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;

    fighter->x62C = 0.0f;
    fighter->x628_lstick_z = 0.0f;
    fighter->x624_lstick_y = 0.0f;
    fighter->x620_lstick_x = 0.0f;

    fighter->x644 = 0.0f;
    fighter->x640 = 0.0f;
    fighter->x63C = 0.0f;
    fighter->x638 = 0.0f;

    fighter->x654 = 0.0f;
    fighter->x650 = 0.0f;

    fighter->x660 = 0;
    fighter->x66C = 0;
    fighter->x668 = 0;
    fighter->x65C = 0;

    fighter->x672_timer_lstick_tilt_z = 0xFE;
    fighter->x671_timer_lstick_tilt_y = 0xFE;
    fighter->x670_timer_lstick_tilt_x = 0xFE;

    fighter->x675_z = 0xFE;
    fighter->x674_y = 0xFE;
    fighter->x673_x = 0xFE;

    fighter->x678_z = 0xFE;
    fighter->x677_y = 0xFE;
    fighter->x676_x = 0xFE;

    fighter->x67B_z = 0xFE;
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


///https://decomp.me/scratch/4m0tc  ///NON_MATCHING  but very close, 1 or 2 register swaps
//// updated - https://decomp.me/scratch/Bihks
//// matched!!! - https://decomp.me/scratch/1ubn4
void func_80068914(HSD_GObj* fighterObj, struct S_TEMP1* argdata) {
    u32 temp_r3;
    struct RGBA* temp_r3_s2;
    ftData** temp_r4;
    Fighter* fighter_r31;
    Fighter* temp_r6;
    s32 phi_r3;

    fighter_r31  = fighterObj->user_data;

    fighter_r31->x4_fighterKind = argdata->fighterKind;
    fighter_r31->xC_playerID = argdata->playerID;

    fighter_r31->x221F_flag.bits.b4 = argdata->unk6.bits.b0;

    fighter_r31->x34_scale.x = Player_GetModelScale(fighter_r31->xC_playerID);
    fighter_r31->x61C = argdata->unk5;
    fighter_r31->x618_player_id = Player_GetPlayerId(fighter_r31->xC_playerID);
    fighter_r31->x61A_controller_index = Player_GetControllerIndex(fighter_r31->xC_playerID);
    fighter_r31->x2223_flag.bits.b6 = Player_GetFlagsBit5(fighter_r31->xC_playerID);
    fighter_r31->x2226_flag.bits.b3 = Player_GetFlagsBit6(fighter_r31->xC_playerID);
    fighter_r31->x2226_flag.bits.b6 = Player_GetFlagsBit7(fighter_r31->xC_playerID);
    fighter_r31->x2225_flag.bits.b5 = Player_GetMoreFlagsBit1(fighter_r31->xC_playerID);
    fighter_r31->x2225_flag.bits.b7 = Player_GetMoreFlagsBit2(fighter_r31->xC_playerID);
    fighter_r31->x2228_flag.bits.b3 = Player_GetMoreFlagsBit6(fighter_r31->xC_playerID);
    fighter_r31->x2229_b1 = Player_GetFlagsAEBit0(fighter_r31->xC_playerID);

    if (fighter_r31->x61A_controller_index > 4) {
        OSReport("fighter sub color num over!\n");
        __assert("fighter.c", 0x33C, "0");
    }

    temp_r3 = fighter_r31->x61A_controller_index;
    if (temp_r3 != 0) {
        temp_r3_s2 = &p_ftCommonData->filler_x6DC[temp_r3 - 1];
        fighter_r31->filler_x610[0] = (temp_r3_s2->r * temp_r3_s2->a) / 0xff;
        fighter_r31->filler_x610[1] = (temp_r3_s2->g * temp_r3_s2->a) / 0xff;
        fighter_r31->filler_x610[2] = (temp_r3_s2->b * temp_r3_s2->a) / 0xff;
        fighter_r31->filler_x610[3] = temp_r3_s2->a;
    }

    phi_r3 = Player_GetCostumeId(fighter_r31->xC_playerID);
    if (phi_r3 >= lbl_803C0EC0[fighter_r31->x4_fighterKind].flag) {
        phi_r3 = 0;
    }
    
    fighter_r31->x619_costume_id = phi_r3;
    fighter_r31->x61B_team = Player_GetTeam(fighter_r31->xC_playerID);
    temp_r4 = lbl_804598B8;
    fighter_r31->x0_fighter = fighterObj;
    fighter_r31->x10C_ftData = temp_r4[fighter_r31->x4_fighterKind];
    func_800D0FA0(fighterObj);
    fighter_r31->x2CC = 0;
    fighter_r31->x2D0 = 0;
    fighter_r31->x18 = 0x155;
    fighter_r31->x1C = lbl_803C2800;
    fighter_r31->x20 = lbl_803C12E0[fighter_r31->x4_fighterKind];
    fighter_r31->x24 = fighter_r31->x10C_ftData->xC;
    fighter_r31->x28 = fighter_r31->x10C_ftData->x10;

    fighter_r31->x634 = 0.0f;
    fighter_r31->x630 = 0.0f;
    fighter_r31->x64C = 0.0f;
    fighter_r31->x648 = 0.0f;
    fighter_r31->x658 = 0.0f;
    fighter_r31->x664 = 0;


    temp_r6 = fighterObj->user_data;
    
    temp_r6->x650 = 
    temp_r6->x654 = 
    temp_r6->x638 = 
    temp_r6->x63C = 
    temp_r6->x640 = 
    temp_r6->x644 = 
    temp_r6->x620_lstick_x = 
    temp_r6->x624_lstick_y = 
    temp_r6->x628_lstick_z = 
    temp_r6->x62C = 0.0f;

    temp_r6->x660 = 0;
    temp_r6->x66C = 0;
    temp_r6->x668 = 0;
    temp_r6->x65C = 0;

    
    temp_r6->x679_x = 
    temp_r6->x67A_y = 
    temp_r6->x67B_z = 

    temp_r6->x676_x = 
    temp_r6->x677_y = 
    temp_r6->x678_z = 

    temp_r6->x673_x = 
    temp_r6->x674_y = 
    temp_r6->x675_z = 

    temp_r6->x670_timer_lstick_tilt_x = 
    temp_r6->x671_timer_lstick_tilt_y = 
    temp_r6->x672_timer_lstick_tilt_z = 0xFE;


    temp_r6->x67C = 
    temp_r6->x67D = 
    temp_r6->x67E = 
    temp_r6->x681 = 
    temp_r6->x682 = 
    temp_r6->x67F = 
    temp_r6->x680 = 
    temp_r6->x683 = 
    temp_r6->x684 = 
    temp_r6->x685 = 
    temp_r6->x686 = 
    temp_r6->x687 = 
    temp_r6->x688 = 
    temp_r6->x689 = 
    temp_r6->x68A = 
    temp_r6->x68B = 0xFF;


    fighter_r31->x594_s32 = 0;
    fighter_r31->x21FC = 1;


    fighter_r31->x221E_flag.bits.b0 = 0;
    fighter_r31->x221E_flag.bits.b1 = 0;
    fighter_r31->x221E_flag.bits.b2 = 0;
    fighter_r31->x221F_flag.bits.b1 = 0;
    fighter_r31->x221F_flag.bits.b2 = 0;

    fighter_r31->x209A = 0;
    fighter_r31->x221E_flag.bits.b5 = 0;
    fighter_r31->x221F_flag.bits.b0 = 0;
    fighter_r31->cb.x21EC_callback = 0;

    fighter_r31->x221D_flag.bits.b3 = 0;
    fighter_r31->x221D_flag.bits.b4 = 0;

    fighter_r31->x221F_flag.bits.b3 = 0;

    fighter_r31->x2220_flag.bits.b0 = 0;

    fighter_r31->x2221_flag.bits.b2 = 0;

    fighter_r31->x2229_b5_no_normal_motion = 0;
    fighter_r31->x2229_b6 = 0;
    fighter_r31->x2229_b7 = 0;

    fighter_r31->x222A_flag.bits.b0 = 0;
    fighter_r31->x222A_flag.bits.b1 = 0;

    fighter_r31->x2228_flag.bits.b5 = 0;
    fighter_r31->x2228_flag.bits.b6 = 0;

    fighter_r31->x2221_flag.bits.b3 = 0;

    fighter_r31->x2222_flag.bits.b0 = 0;
    fighter_r31->x2222_flag.bits.b1 = 0;
    fighter_r31->x2222_flag.bits.b4 = 0;
    fighter_r31->x2222_flag.bits.b5 = 0;
    fighter_r31->x2222_flag.bits.b6 = 0;


    fighter_r31->x2223_flag.bits.b1 = 0;

    fighter_r31->x40 = 0.0f;

    fighter_r31->x2224_flag.bits.b7 = 0;

    fighter_r31->x60C = 0;

    fighter_r31->x2225_flag.bits.b3 = 0;
    fighter_r31->x2228_flag.bits.b2 = 0;


    fighter_r31->x2226_flag.bits.b0 = 0;
    fighter_r31->x2226_flag.bits.b1 = 0;

    fighter_r31->x2227_flag.bits.b0 = 0;
    fighter_r31->x2224_flag.bits.b0 = 0;

    fighter_r31->x2135 = -1;
    fighter_r31->x2184 = 0;


    fighter_r31->x2229_b3 = 0;
}


#pragma push
#pragma peephole on
// increments the spawn number, returns the spawn number value before incrementing
u32 func_80068E40()
{
	u32 spawnNum = g_spawnNumCounter++;
    if (g_spawnNumCounter == 0)
        g_spawnNumCounter = 1;
	return spawnNum;
}
#pragma pop


///https://decomp.me/scratch/nNDzr
void func_80068E64(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;

    if (stage_info.internal_stage_id == 0x1B) {
        fighter->x34_scale.z = p_ftCommonData->x7E4;
    } else {
        fighter->x34_scale.z = 1.0f;
    }
}

///https://decomp.me/scratch/BQ1u9
HSD_GObj* func_80068E98(struct S_TEMP1* input) {

    Vec vec2;
    Vec vec;
    s32 unused[4];

    s32 temp_r0;

    HSD_GObj* temp_r31;
    HSD_JObj* temp_r28_2;
    UnkFighterJointStruct* joint_struct;

    Fighter* temp_r28;
    Fighter* fp;
    Fighter* temp_r4_3;

    

    temp_r31 = func_803901F0(4, 8, 0);
    GObj_SetupGXLink(temp_r31, &func_80080E18, 5U, 0U);
    fp = HSD_ObjAlloc(&lbl_80458FD0);
    fp->x2D8_specialAttributes2 = HSD_ObjAlloc(&lbl_80458FFC);
    GObj_InitUserData(temp_r31, 4U, &func_8006DABC, fp);
    func_8008572C(input->fighterKind);
    func_80068914(temp_r31, input);
    func_8006737C(lbl_803C26FC[fp->x4_fighterKind]);
    func_80085820(fp->x4_fighterKind, fp->x619_costume_id);
    temp_r28 = temp_r31->user_data;
    joint_struct = lbl_803C0EC0[temp_r28->x4_fighterKind].unk_fighter_struct;
    temp_r28->x108_costume_archive = joint_struct[temp_r28->x619_costume_id].joint;
    func_80074148();
    temp_r28_2 = HSD_JObjLoadJoint(temp_r28->x108_costume_archive);
    func_80074170();
    func_80073758(temp_r28_2);
    func_80390A70(temp_r31, lbl_804D7849, temp_r28_2);
    func_80085B10(fp);
    func_80074E58(fp);
    func_800743E0(temp_r31);
    func_80070308(temp_r31);
    func_800C884C(temp_r31);
    temp_r4_3 = temp_r31->user_data;
    if (stage_info.internal_stage_id == 0x1B) {
        temp_r4_3->x34_scale.z = p_ftCommonData->x7E4;
    } else {
        temp_r4_3->x34_scale.z = 1.0f;
    }
    func_800749CC(temp_r31);
    func_8007077C(temp_r31);
    func_8009CF84(fp);
    func_8006FE48(temp_r31);
    temp_r28_2 = fp->x5E8_fighterBones[func_8007500C(fp, 2)].x0_jobj;

    HSD_JObjGetTranslation(temp_r28_2, &vec);

    fp->x1A6C = (vec.y / 8.55f);
    func_8000B1CC(temp_r28_2, 0, &vec);
    func_8000B1CC(fp->x5E8_fighterBones[func_8007500C(fp, 1)].x0_jobj, 0, &vec2);
    fp->x1A70.x = vec2.x - vec.x;
    fp->x1A70.y = vec2.y - vec.y;
    fp->x1A70.z = vec2.z - vec.z;
    func_8009F578(fp);

    if (ft_OnLoad[fp->x4_fighterKind] != 0U) {
        ft_OnLoad[fp->x4_fighterKind](temp_r31);
    }
    temp_r4_3 = temp_r31->user_data;
    if (temp_r4_3->x2229_b5_no_normal_motion == 0) {
        temp_r0 = func_80085E50(temp_r4_3, 0x23);
        temp_r4_3->x2EC = func_8001E8F8(temp_r0);
        if (temp_r4_3->x2228_flag.bits.b2 == 0) {
            temp_r0 = func_80085E50(temp_r4_3, 7);
            temp_r4_3->x2DC = func_8001E8F8(temp_r0);
            temp_r0 = func_80085E50(temp_r4_3, 8);
            temp_r4_3->x2E0 = func_8001E8F8(temp_r0);
            temp_r0 = func_80085E50(temp_r4_3, 9);
            temp_r4_3->x2E4 = func_8001E8F8(temp_r0);
            temp_r0 = func_80085E50(temp_r4_3, 0x25);
            temp_r4_3->x2E8 = func_8001E8F8(temp_r0);
        }
    }
    func_8007B320(temp_r31);
    fp->x890 = func_80029020();
    func_8000ED54(&fp->x20A4, temp_r31->hsd_obj);
    func_8038FD54(temp_r31, &func_8006A1BC, 0);
    func_8038FD54(temp_r31, &func_8006A360, 1);
    func_8038FD54(temp_r31, &func_8006ABA0, 2);
    func_8038FD54(temp_r31, &func_8006AD10, 3);
    func_8038FD54(temp_r31, &Fighter_procUpdate, 4);
    func_8038FD54(temp_r31, &func_8006C27C, 6);
    func_8038FD54(temp_r31, &func_8006C5F4, 7);
    func_8038FD54(temp_r31, &func_8006C624, 8);
    func_8038FD54(temp_r31, &func_8006C80C, 9);
    func_8038FD54(temp_r31, &func_8006CA5C, 0xC);
    func_8038FD54(temp_r31, &func_8006CB94, 0xD);
    func_8038FD54(temp_r31, &func_8006D1EC, 0xE);
    func_8038FD54(temp_r31, &func_8006D9AC, 0x10);
    func_8038FD54(temp_r31, &func_8006D9EC, 0x12);
    func_8038FD54(temp_r31, &func_8006DA4C, 0x16);
    func_80068354(temp_r31);
    temp_r0 = fp->x4_fighterKind;
    if (temp_r0 == 0x1B) {
        func_8014FE10(temp_r31);
    }
    else if (temp_r0 == 0x1C) {
        func_80155FCC(temp_r31);
    }
    else if (input->unk6.bits.b1 != 0) {
        func_800BFD04(temp_r31);
    }
    else if (Player_GetFlagsBit3( fp->xC_playerID) != 0) {
        func_800C61B0(temp_r31);
    }
    else {
        if (!fp->x2229_b5_no_normal_motion) {
            func_8007D92C(temp_r31);
        } else {
            OSReport("ellegal flag fp->no_normal_motion\n");
            __assert("fighter.c", 1065, "0");
        }
    }
    func_800867E8(temp_r31);
    return temp_r31;
}

/// https://decomp.me/scratch/VyJpx
inline f32 pickValue(f32 argA, u8* unk_byte_ptr)
{
    return (argA == -1.0f) ? 0.0f :  (argA) ? argA : *unk_byte_ptr;
}
void Fighter_ActionStateChange_800693AC(HSD_GObj* fighterObj, s32 arg1, s32 arg2, HSD_GObj* otherObj, f32 arg8, f32 arg9, f32 argA) {
    volatile s32 volatile_integer;
    Vec translation;
    Quaternion quat;
    s32 unused[4];
    HSD_JObj* other_jobj;
    s32 bone_index;
    HSD_JObj* jobj;
    Fighter* fp;
    struct S_TEMP3* struct_w_flags_and_callbacks;
    struct S_TEMP4* unk_struct_x18;
    u8* unk_byte_ptr;
    BOOL animflags_bool;

    
    jobj = fighterObj->hsd_obj;
    other_jobj = jobj;
    fp = fighterObj->user_data;

    fp->x10 = arg1;
    fp->x30_facingDirectionRepeated = fp->x2C_facing_direction;
        
    HSD_JObjSetTranslate(jobj, &fp->xB0_pos);
    func_80067624(fighterObj, &fp->x60C);

    if ((arg2 & 8) == 0) {
        if (fp->x2219_flag.bits.b3 != 0) {
            func_8007AFF8(fighterObj);
        }
        if (fp->x2219_flag.bits.b4 != 0) {
            func_8007C114(fighterObj);
        }
    }

    if ((arg2 & 0x100) == 0) {
        fp->x1198 = 0;
    }

    if ((arg2 & 4) == 0) {
        if (fp->x1988 != 0) {
            func_8007B62C(fighterObj, 0);
        }
        if (fp->x221A_flag.bits.b5 != 0) {
            func_8007B0C0(fighterObj, 0);
        }
    }

    if (fp->x221A_flag.bits.b6 != 0) {
        func_8007B4E0(fighterObj);
    }

    if (((arg2 & 0x10) == 0) && (fp->x221D_flag.bits.b2 != 0U)) {
        func_80074A8C(fighterObj);
    }

    if (((arg2 & 0x80) == 0) && ((fp->x221E_flag.bits.b7) != 0)) {
        func_80070654(fighterObj);
    }

    if ((arg2 & 0x400) == 0) {
        fp->x2221_flag.bits.b4 = 0;
        if ((func_8007E994(fighterObj) != -1) && (func_8007E994(fighterObj) != 6)) {
            func_8007E83C(fighterObj, 6, 0.0f);
        }
    }

    func_80070F28(fighterObj);
    func_80070E74(fighterObj);
    func_8007ECD4(fp, 7);
    func_8007ECD4(fp, 8);
    func_8007ECD4(fp, 0x24);

    if ((arg2 & 0x800) == 0) {
        func_8007ECD4(fp, 1);
        func_8007ECD4(fp, 0x19);
    }

    if (((arg2 & 0x10000) == 0) && (fp->x2221_flag.bits.b1 != 0U)) {
        func_8007B6EC(fighterObj);
        func_8007B760(fighterObj, p_ftCommonData->x134);
        fp->x2221_flag.bits.b1 = 0;
    }
    func_8007E2F4(fp, 0);

    if (fp->dmg.x18F4 != 0) {
        fp->dmg.x18F4 = 0;
        fp->x2220_flag.bits.b4 = 0;
    }

    if ((arg2 & 0x80000) == 0) {
        fp->x2222_flag.bits.b2 = 0;
    }

    if ((arg2 & 0x800000) == 0) {
        fp->x2223_flag.bits.b4 = 0;
    }

    if ((arg2 & 0x8000000) == 0) {
        fp->x2227_flag.bits.b2 = 0;
    }

    if (((arg2 & 0x10000000) == 0) && (fp->x221C_flag.bits.b6 != 0U)) {
        fp->x221C_flag.bits.b6 = 0;
        fp->x2098 = p_ftCommonData->x4CC;
    }

    fp->x221F_flag.bits.b3 = 0;
    fp->x2219_flag.bits.b1 = 0;
    fp->x2219_flag.bits.b2 = 0;

    fp->dmg.x182c_behavior = 1.0f;
    fp->dmg.x1850_forceApplied = 0.0f;
    fp->dmg.x18A8 = 0.0f;
    fp->dmg.x18B4_armor = 0.0f;
    fp->dmg.x18a0 = 0.0f;

    fp->x221A_flag.bits.b7 = 0;
    fp->x221B_flag.bits.b0 = 0;
    fp->x221C_flag.bits.b3 = 0;

    fp->x19B4_shieldUnk = 0.0f;
    fp->x19B8_shieldUnk = 0.0f;

    fp->x221D_flag.bits.b5 = 0;
    fp->x2218_flag.bits.b3 = 0;
    fp->x2218_flag.bits.b6 = 0;
    fp->x221C_flag.bits.b4 = 0;


    fp->x1A6A = 0;

    fp->x221D_flag.bits.b7 = 0;
    fp->x221E_flag.bits.b0 = 0;
    fp->x221E_flag.bits.b1 = 0;
    fp->x221E_flag.bits.b2 = 0;
    fp->x221F_flag.bits.b1 = 0;
    fp->x221E_flag.bits.b5 = 0;
    fp->x221E_flag.bits.b6 = 0;
    fp->x2220_flag.bits.b3 = 0;
    fp->x2220_flag.bits.b7 = 0;

    fp->x209C = 0;

    fp->x2223_flag.bits.b0 = 0;
    fp->x2222_flag.bits.b3 = 0;
    fp->x2224_flag.bits.b5 = 0;
    fp->x2225_flag.bits.b1 = 0;
    fp->x2225_flag.bits.b4 = 0;

    func_8004CBF4(&fp->x6F0_collData);

    func_800DEEA8(fighterObj);

    fp->x2138_smashSinceHitbox = -1.0f;
    fp->x2224_flag.bits.b4 = 0;

    if ((arg2 & 0x40000) == 0) {
        fp->x221E_flag.bits.b3 = 1;
    } else if (fp->x221E_flag.bits.b3 == 0U) {
        func_8007F578(fighterObj);
    }

    if ((arg2 & 0x400000) == 0) {
        fp->x221E_flag.bits.b4 = 1;
    }

    if ((arg2 & 0x4000000) == 0) {
        fp->x2225_flag.bits.b2 = 1;
    }

    if ((arg2 & 1) == 0) {
        fp->x221A_flag.bits.b4 = 0;
    }

    if ((arg2 & 0x1000) == 0) {
        func_800C0134(fp);
    }

    if (((arg2 & 2) == 0) && (fp->x2219_flag.bits.b0 != 0U)) {
        func_8007DB24(fighterObj);
    }

    if (((arg2 & 0x2000) == 0) && ((u32) fp->x20A0 != 0U)) {
        HSD_JObjRemoveAll(fp->x20A0);
        fp->x20A0 = 0U;
    }

    if (fp->xE0_ground_or_air == 0) {
        if (fp->x4_fighterKind == 9) {
            fp->x222C = 1;
        }
        fp->x2221_flag.bits.b5 = 0;
        fp->x2221_flag.bits.b7 = 1;
        fp->x2221_flag.bits.b6 = 1;
        fp->x2224_flag.bits.b1 = 0;
        fp->x2227_flag.bits.b1 = 0;
        fp->x213C = -1;

        if (fp->x2227_flag.bits.b4 != 0U) {
            func_8003FE1C(fp->xC_playerID, fp->x221F_flag.bits.b4);
            fp->x2227_flag.bits.b4 = 0;
        }
        fp->x2227_flag.bits.b5 = 0;
        func_80040330(fp->xC_playerID, fp->x221F_flag.bits.b4, fp->x2140);
        fp->x2140 = 0.0f;
        fp->x2228_flag.bits.b6 = 0;
        fp->x2180 = 6;

    }

    if ((arg1 != 0xE) && (arg1 != 0xF) && (arg1 != 0x10) && (arg1 != 0x11)) {
        fp->x196C_hitlag_mult = 0.0f;
    }

    if ((arg2 & 0x200) == 0) {
        func_80088884(fp);
        func_800888E0(fp);
        func_800887CC(fp);
    }

    if ((arg2 & 0x20000) == 0) {
        fp->x2100 = -1;
    }
    if ((arg2 & 0x8000) == 0) {
        fp->x209A = 0;
    }

    fp->x2222_flag.bits.b7 = 0;

    if ((arg2 & 0x100000) != 0) {
        fp->x100 = 0.0f;
    } else {
        fp->x100 = -1.0f;
    }

    if ((arg2 & 0x1000000) == 0) {
        fp->x221C_u16_y = 0;
    }

    fp->x6BC_inputStickangle = 0.0f;

    func_8007592C(fp, 0, 0.0f);
    func_80075AF0(fp, 0, (1.5707963267948966 * fp->x2C_facing_direction));
    func_80075CB4(fp, 0, 0.0f);

    if (arg1 >= fp->x18) {
        struct_w_flags_and_callbacks = &fp->x20[(arg1 - fp->x18)];
    } else {
        struct_w_flags_and_callbacks = &fp->x1C[arg1];
    }
    

    if (fp->xE0_ground_or_air == GA_Ground) {
        if ((arg2 & 0x40) == 0) {
            if (struct_w_flags_and_callbacks->flags9.bits.b1 != 0  && fp->dmg.x18C8 == -1) {
                if (p_ftCommonData->x814 > 0) {
                    fp->dmg.x18C8 = p_ftCommonData->x814;
                } else {
                    fp->dmg.x18C8 = 1;
                }
            }
        }
    }

    volatile_integer = fp->x2070_int;
    func_800890D0(fp, struct_w_flags_and_callbacks->flags8);
    func_800895E0(fp, struct_w_flags_and_callbacks->x4);
    fp->x2225_flag.bits.b3 = struct_w_flags_and_callbacks->flags9.bits.b0;

    if (fp->x2226_flag.bits.b4 != 0U) {
        if (fp->x2071.bits.b5 != 0U) {
            func_800C8B2C(fp, 0x7E, 0);
        }
        if (fp->x2071.bits.b6 != 0U) {
            func_800C8B2C(fp, 0x7F, 0);
        }
    }

    if (fp->cb.x21EC_callback) {
        fp->cb.x21EC_callback(fighterObj);
        fp->cb.x21EC_callback = 0U;
    }
    

    if ((arg2 & 0x2000000) == 0) {
        func_80037C60(fighterObj, volatile_integer);
    }

    fp->x14 = struct_w_flags_and_callbacks->id;
    fp->x89C = arg9;
    fp->x8A0 = arg9;

    fp->x894 = (arg8 - fp->x89C);
    fp->x898 = 0.0f;

    if ((fp->x594_animCurrFlags1.bits.b0) || (fp->x594_animCurrFlags1.bits.b5)) {
        animflags_bool = TRUE;
    } else {
        animflags_bool = FALSE;
    }

    if (fp->x14 != -1) {
        bone_index = fp->x596_bits.x7;
        if ((arg2 & 0x200000) != 0) {
            fp->x2223_flag.bits.b0 = 1;
            fp->x104 = 0x14;
            fp->x89C = 0.0f;
            arg9 = 0.0f;
        }

        if (otherObj != 0U) {
            Fighter* otherFighter = otherObj->user_data;
            unk_struct_x18 = &otherFighter->x24[fp->x14];
            unk_byte_ptr = &otherFighter->x28[fp->x14 << 1];
        } else {
            unk_struct_x18 = &fp->x24[fp->x14];
            unk_byte_ptr = &fp->x28[fp->x14 << 1];
        }
        fp->x594_s32 = unk_struct_x18->x10_animCurrFlags;
        func_8009E7B4(fp, unk_byte_ptr);
        if ((arg2 & 0x20000000) == 0) {

            if (otherObj != 0U) {
                func_80085CD8(fp, otherObj->user_data, fp->x14);
                func_8007B8CC(fp, otherObj);
            } else {
                func_80085CD8(fp, fp, fp->x14);
            }
            fp->x3EC = unk_struct_x18->xC;
            fp->x3F0 = 0;

            
            if (arg8) {
                if (fp->x590 != 0U) {
                    func_8006EBE8(fighterObj, arg8 - arg9, arg9, pickValue(argA, unk_byte_ptr));
                }
                func_8006E9B4(fighterObj);
                if (fp->x594_animCurrFlags1.bits.b0 != 0U) {
                    fp->x6B0.z = 0.0f;
                    fp->x6B0.y = 0.0f;
                    fp->x6B0.x = 0.0f;
                    fp->x6A4_transNOffset.z = 0.0f;
                    fp->x6A4_transNOffset.y = 0.0f;
                    fp->x6A4_transNOffset.x = 0.0f;
                    fp->x698 = fp->x68C_transNPos;
                }
                
                if (fp->x594_animCurrFlags1.bits.b5 != 0U) {
                    fp->x6E4.z = 0.0f;
                    fp->x6E4.y = 0.0f;
                    fp->x6E4.x = 0.0f;
                    fp->x6D8.z = 0.0f;
                    fp->x6D8.y = 0.0f;
                    fp->x6D8.x = 0.0f;
                    fp->x6CC = fp->x6C0;
                }
                fp->x3E4 = -arg8;
            } else {
                if (fp->x590 != 0U) {
                    func_8006EBE8(fighterObj, arg8, arg9, pickValue(argA, unk_byte_ptr));
                }
                fp->x3E4 = 0.0f;
            }

            func_8006E9B4(fighterObj);
            if ((bone_index != 0) && (*unk_byte_ptr != 0U)) {
                HSD_JObj* temp_joint = fp->x5E8_fighterBones[bone_index].x4_jobj2;
                HSD_JObjGetTranslation(temp_joint, &translation);
                HSD_JObjSetTranslate(fp->x5E8_fighterBones[bone_index].x0_jobj, &translation);
                HSD_JObjGetRotation(temp_joint, &quat);
                func_8007584C(fp->x5E8_fighterBones[bone_index].x0_jobj, &quat);
            }

            if (fp->x594_animCurrFlags1.bits.b0 != 0U) {
                if (!arg8) {
                    fp->x6B0.z = 0.0f;
                    fp->x6B0.y = 0.0f;
                    fp->x6B0.x = 0.0f;
                    fp->x6A4_transNOffset.z = 0.0f;
                    fp->x6A4_transNOffset.y = 0.0f;
                    fp->x6A4_transNOffset.x = 0.0f;
                    fp->x698 = fp->x68C_transNPos;
                } else if (((arg2 & 0x20) == 0) && (fp->xE0_ground_or_air == GA_Ground)) {
                    f32 temp_vel = fp->x6A4_transNOffset.z * fp->x2C_facing_direction;
                    fp->x80_self_vel.x = temp_vel;
                    fp->xEC_ground_vel = temp_vel;
                }
            }

            if (fp->x594_animCurrFlags1.bits.b5 != 0U) {
                if (!arg8) {
                    fp->x6E4.z = 0.0f;
                    fp->x6E4.y = 0.0f;
                    fp->x6E4.x = 0.0f;
                    fp->x6D8.z = 0.0f;
                    fp->x6D8.y = 0.0f;
                    fp->x6D8.x = 0.0f;
                    fp->x6CC = fp->x6C0;
                } else if (((arg2 & 0x20) == 0) && (fp->xE0_ground_or_air == GA_Ground)) {
                    f32 temp_vel = fp->x6D8.z * fp->x2C_facing_direction;
                    fp->x80_self_vel.x = temp_vel;
                    fp->xEC_ground_vel = temp_vel;
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
            fp->x14 = -1;
        }
    }
    if (fp->x14 == -1) {
        fp->x594_s32 = 0;
        func_80070758(other_jobj);
        func_80070758(fp->x8AC_animSkeleton);
        fp->x3EC = 0;
        fp->x8A4 = 0.0f;
        fp->x8A8 = 0.0f;
    }

    if (animflags_bool) {
        if (!fp->x594_animCurrFlags1.bits.b0 && !fp->x594_animCurrFlags1.bits.b0) {
            func_8007CC78(fp->x110_attr.x138_DashrunTerminalVelocity, fp);
        }
    }

    fp->cb.x21A0_callback_Anim = struct_w_flags_and_callbacks->cb_Anim;
    fp->cb.x219C_callback_IASA = struct_w_flags_and_callbacks->cb_Input;
    fp->cb.x21A4_callback_Phys = struct_w_flags_and_callbacks->cb_Physics;
    fp->cb.x21A8_callback_Coll = struct_w_flags_and_callbacks->cb_Collision;
    fp->cb.x21AC_callback_Cam = struct_w_flags_and_callbacks->cb_Camera;

    fp->cb.x21B0_callback_Accessory1 = 0;
    fp->cb.x21BC_callback_Accessory4 = 0;
    fp->cb.x21C0_callback_OnGiveDamage = 0;
    fp->cb.x21C4_callback_OnShieldHit = 0;
    fp->cb.x21C8_callback_OnReflectHit = 0;
    fp->cb.x21D0_callback_EveryHitlag = 0;
    fp->cb.x21CC_callback_x21cc = 0;
    fp->cb.x21D8_callback_ExitHitlag = 0;
    fp->cb.x21D4_callback_EnterHitlag = 0;
    fp->cb.x21DC_callback_OnTakeDamage = 0;
    fp->cb.x21F0_callback = 0;
    fp->cb.x21F4_callback = 0;
    fp->cb.x21F8_callback = 0;
    fp->cb.x21E4_callback_OnDeath2 = 0;
    
}

asm static void func_8006A1BC()
{
	nofralloc
/* 8006A1BC 00066D9C  7C 08 02 A6 */	mflr r0
/* 8006A1C0 00066DA0  90 01 00 04 */	stw r0, 4(r1)
/* 8006A1C4 00066DA4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8006A1C8 00066DA8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8006A1CC 00066DAC  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8006A1D0 00066DB0  7C 7E 1B 78 */	mr r30, r3
/* 8006A1D4 00066DB4  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8006A1D8 00066DB8  88 03 22 1F */	lbz r0, 0x221f(r3)
/* 8006A1DC 00066DBC  3B E3 00 00 */	addi r31, r3, 0
/* 8006A1E0 00066DC0  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 8006A1E4 00066DC4  40 82 01 64 */	bne lbl_8006A348
/* 8006A1E8 00066DC8  C0 5F 19 54 */	lfs f2, 0x1954(r31)
/* 8006A1EC 00066DCC  C0 22 88 74 */	lfs f1, lbl_804D8254(r2)
/* 8006A1F0 00066DD0  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 8006A1F4 00066DD4  40 81 00 44 */	ble lbl_8006A238
/* 8006A1F8 00066DD8  C0 02 88 70 */	lfs f0, lbl_804D8250(r2)
/* 8006A1FC 00066DDC  EC 02 00 28 */	fsubs f0, f2, f0
/* 8006A200 00066DE0  D0 1F 19 54 */	stfs f0, 0x1954(r31)
/* 8006A204 00066DE4  C0 1F 19 54 */	lfs f0, 0x1954(r31)
/* 8006A208 00066DE8  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8006A20C 00066DEC  4C 40 13 82 */	cror 2, 0, 2
/* 8006A210 00066DF0  40 82 00 28 */	bne lbl_8006A238
/* 8006A214 00066DF4  D0 3F 19 54 */	stfs f1, 0x1954(r31)
/* 8006A218 00066DF8  88 1F 22 1A */	lbz r0, 0x221a(r31)
/* 8006A21C 00066DFC  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8006A220 00066E00  40 82 00 18 */	bne lbl_8006A238
/* 8006A224 00066E04  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 8006A228 00066E08  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8006A22C 00066E0C  40 82 00 0C */	bne lbl_8006A238
/* 8006A230 00066E10  7F C3 F3 78 */	mr r3, r30
/* 8006A234 00066E14  48 00 2E D9 */	bl func_8006D10C
lbl_8006A238:
/* 8006A238 00066E18  88 1F 22 1A */	lbz r0, 0x221a(r31)
/* 8006A23C 00066E1C  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 8006A240 00066E20  41 82 00 1C */	beq lbl_8006A25C
/* 8006A244 00066E24  7F C3 F3 78 */	mr r3, r30
/* 8006A248 00066E28  48 00 2D 99 */	bl func_8006CFE0
/* 8006A24C 00066E2C  88 1F 22 1A */	lbz r0, 0x221a(r31)
/* 8006A250 00066E30  38 60 00 00 */	li r3, 0
/* 8006A254 00066E34  50 60 36 72 */	rlwimi r0, r3, 6, 0x19, 0x19
/* 8006A258 00066E38  98 1F 22 1A */	stb r0, 0x221a(r31)
lbl_8006A25C:
/* 8006A25C 00066E3C  C0 5F 19 5C */	lfs f2, 0x195c(r31)
/* 8006A260 00066E40  C0 22 88 74 */	lfs f1, lbl_804D8254(r2)
/* 8006A264 00066E44  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 8006A268 00066E48  40 81 00 7C */	ble lbl_8006A2E4
/* 8006A26C 00066E4C  C0 02 88 70 */	lfs f0, lbl_804D8250(r2)
/* 8006A270 00066E50  EC 02 00 28 */	fsubs f0, f2, f0
/* 8006A274 00066E54  D0 1F 19 5C */	stfs f0, 0x195c(r31)
/* 8006A278 00066E58  C0 1F 19 5C */	lfs f0, 0x195c(r31)
/* 8006A27C 00066E5C  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8006A280 00066E60  4C 40 13 82 */	cror 2, 0, 2
/* 8006A284 00066E64  40 82 00 60 */	bne lbl_8006A2E4
/* 8006A288 00066E68  D0 3F 19 5C */	stfs f1, 0x195c(r31)
/* 8006A28C 00066E6C  88 1F 22 1A */	lbz r0, 0x221a(r31)
/* 8006A290 00066E70  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 8006A294 00066E74  41 82 00 1C */	beq lbl_8006A2B0
/* 8006A298 00066E78  7F E3 FB 78 */	mr r3, r31
/* 8006A29C 00066E7C  48 02 64 7D */	bl func_80090718
/* 8006A2A0 00066E80  88 1F 22 1A */	lbz r0, 0x221a(r31)
/* 8006A2A4 00066E84  38 60 00 00 */	li r3, 0
/* 8006A2A8 00066E88  50 60 26 F6 */	rlwimi r0, r3, 4, 0x1b, 0x1b
/* 8006A2AC 00066E8C  98 1F 22 1A */	stb r0, 0x221a(r31)
lbl_8006A2B0:
/* 8006A2B0 00066E90  C0 3F 19 54 */	lfs f1, 0x1954(r31)
/* 8006A2B4 00066E94  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006A2B8 00066E98  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8006A2BC 00066E9C  40 82 00 18 */	bne lbl_8006A2D4
/* 8006A2C0 00066EA0  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 8006A2C4 00066EA4  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8006A2C8 00066EA8  40 82 00 0C */	bne lbl_8006A2D4
/* 8006A2CC 00066EAC  7F C3 F3 78 */	mr r3, r30
/* 8006A2D0 00066EB0  48 00 2E 3D */	bl func_8006D10C
lbl_8006A2D4:
/* 8006A2D4 00066EB4  88 1F 22 1A */	lbz r0, 0x221a(r31)
/* 8006A2D8 00066EB8  38 60 00 00 */	li r3, 0
/* 8006A2DC 00066EBC  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 8006A2E0 00066EC0  98 1F 22 1A */	stb r0, 0x221a(r31)
lbl_8006A2E4:
/* 8006A2E4 00066EC4  7F C3 F3 78 */	mr r3, r30
/* 8006A2E8 00066EC8  48 05 94 B9 */	bl func_800C37A0
/* 8006A2EC 00066ECC  48 00 00 18 */	b lbl_8006A304
lbl_8006A2F0:
/* 8006A2F0 00066ED0  7F C3 F3 78 */	mr r3, r30
/* 8006A2F4 00066ED4  48 06 71 F1 */	bl func_800D14E4
/* 8006A2F8 00066ED8  80 7F 20 0C */	lwz r3, 0x200c(r31)
/* 8006A2FC 00066EDC  38 03 FF FF */	addi r0, r3, -1
/* 8006A300 00066EE0  90 1F 20 0C */	stw r0, 0x200c(r31)
lbl_8006A304:
/* 8006A304 00066EE4  80 1F 20 0C */	lwz r0, 0x200c(r31)
/* 8006A308 00066EE8  2C 00 00 00 */	cmpwi r0, 0
/* 8006A30C 00066EEC  40 82 FF E4 */	bne lbl_8006A2F0
/* 8006A310 00066EF0  48 00 00 18 */	b lbl_8006A328
lbl_8006A314:
/* 8006A314 00066EF4  7F C3 F3 78 */	mr r3, r30
/* 8006A318 00066EF8  48 06 7B 69 */	bl func_800D1E80
/* 8006A31C 00066EFC  80 7F 20 10 */	lwz r3, 0x2010(r31)
/* 8006A320 00066F00  38 03 FF FF */	addi r0, r3, -1
/* 8006A324 00066F04  90 1F 20 10 */	stw r0, 0x2010(r31)
lbl_8006A328:
/* 8006A328 00066F08  80 1F 20 10 */	lwz r0, 0x2010(r31)
/* 8006A32C 00066F0C  2C 00 00 00 */	cmpwi r0, 0
/* 8006A330 00066F10  40 82 FF E4 */	bne lbl_8006A314
/* 8006A334 00066F14  7F C3 F3 78 */	mr r3, r30
/* 8006A338 00066F18  48 01 76 71 */	bl func_800819A8
/* 8006A33C 00066F1C  88 7F 22 19 */	lbz r3, 0x2219(r31)
/* 8006A340 00066F20  50 63 FF BC */	rlwimi r3, r3, 0x1f, 0x1e, 0x1e
/* 8006A344 00066F24  98 7F 22 19 */	stb r3, 0x2219(r31)
lbl_8006A348:
/* 8006A348 00066F28  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8006A34C 00066F2C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8006A350 00066F30  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8006A354 00066F34  38 21 00 18 */	addi r1, r1, 0x18
/* 8006A358 00066F38  7C 08 03 A6 */	mtlr r0
/* 8006A35C 00066F3C  4E 80 00 20 */	blr  
}


asm void func_8006A360()
{
	nofralloc 
/* 8006A360 00066F40  7C 08 02 A6 */	mflr r0
/* 8006A364 00066F44  90 01 00 04 */	stw r0, 4(r1)
/* 8006A368 00066F48  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8006A36C 00066F4C  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8006A370 00066F50  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8006A374 00066F54  7C 7E 1B 78 */	mr r30, r3
/* 8006A378 00066F58  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8006A37C 00066F5C  88 03 22 1F */	lbz r0, 0x221f(r3)
/* 8006A380 00066F60  3B E3 00 00 */	addi r31, r3, 0
/* 8006A384 00066F64  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 8006A388 00066F68  40 82 08 00 */	bne lbl_8006AB88
/* 8006A38C 00066F6C  C0 3F 00 B0 */	lfs f1, 0xb0(r31)
/* 8006A390 00066F70  C0 1F 00 BC */	lfs f0, 0xbc(r31)
/* 8006A394 00066F74  EC 01 00 28 */	fsubs f0, f1, f0
/* 8006A398 00066F78  D0 1F 00 C8 */	stfs f0, 0xc8(r31)
/* 8006A39C 00066F7C  C0 3F 00 B4 */	lfs f1, 0xb4(r31)
/* 8006A3A0 00066F80  C0 1F 00 C0 */	lfs f0, 0xc0(r31)
/* 8006A3A4 00066F84  EC 01 00 28 */	fsubs f0, f1, f0
/* 8006A3A8 00066F88  D0 1F 00 CC */	stfs f0, 0xcc(r31)
/* 8006A3AC 00066F8C  C0 3F 00 B8 */	lfs f1, 0xb8(r31)
/* 8006A3B0 00066F90  C0 1F 00 C4 */	lfs f0, 0xc4(r31)
/* 8006A3B4 00066F94  EC 01 00 28 */	fsubs f0, f1, f0
/* 8006A3B8 00066F98  D0 1F 00 D0 */	stfs f0, 0xd0(r31)
/* 8006A3BC 00066F9C  80 7F 00 B0 */	lwz r3, 0xb0(r31)
/* 8006A3C0 00066FA0  80 1F 00 B4 */	lwz r0, 0xb4(r31)
/* 8006A3C4 00066FA4  90 7F 00 BC */	stw r3, 0xbc(r31)
/* 8006A3C8 00066FA8  90 1F 00 C0 */	stw r0, 0xc0(r31)
/* 8006A3CC 00066FAC  80 1F 00 B8 */	lwz r0, 0xb8(r31)
/* 8006A3D0 00066FB0  90 1F 00 C4 */	stw r0, 0xc4(r31)
/* 8006A3D4 00066FB4  80 7F 18 C8 */	lwz r3, 0x18c8(r31)
/* 8006A3D8 00066FB8  2C 03 FF FF */	cmpwi r3, -1
/* 8006A3DC 00066FBC  41 82 00 38 */	beq lbl_8006A414
/* 8006A3E0 00066FC0  2C 03 00 00 */	cmpwi r3, 0
/* 8006A3E4 00066FC4  40 81 00 30 */	ble lbl_8006A414
/* 8006A3E8 00066FC8  38 03 FF FF */	addi r0, r3, -1
/* 8006A3EC 00066FCC  90 1F 18 C8 */	stw r0, 0x18c8(r31)
/* 8006A3F0 00066FD0  80 1F 18 C8 */	lwz r0, 0x18c8(r31)
/* 8006A3F4 00066FD4  2C 00 00 00 */	cmpwi r0, 0
/* 8006A3F8 00066FD8  40 82 00 1C */	bne lbl_8006A414
/* 8006A3FC 00066FDC  38 00 00 06 */	li r0, 6
/* 8006A400 00066FE0  90 1F 18 C4 */	stw r0, 0x18c4(r31)
/* 8006A404 00066FE4  38 60 FF FF */	li r3, -1
/* 8006A408 00066FE8  38 00 FF F6 */	li r0, -10
/* 8006A40C 00066FEC  90 7F 18 C8 */	stw r3, 0x18c8(r31)
/* 8006A410 00066FF0  90 1F 18 D0 */	stw r0, 0x18d0(r31)
lbl_8006A414:
/* 8006A414 00066FF4  80 7F 19 90 */	lwz r3, 0x1990(r31)
/* 8006A418 00066FF8  2C 03 00 00 */	cmpwi r3, 0
/* 8006A41C 00066FFC  41 82 00 5C */	beq lbl_8006A478
/* 8006A420 00067000  38 03 FF FF */	addi r0, r3, -1
/* 8006A424 00067004  90 1F 19 90 */	stw r0, 0x1990(r31)
/* 8006A428 00067008  80 1F 19 90 */	lwz r0, 0x1990(r31)
/* 8006A42C 0006700C  2C 00 00 00 */	cmpwi r0, 0
/* 8006A430 00067010  40 82 00 48 */	bne lbl_8006A478
/* 8006A434 00067014  88 1F 22 21 */	lbz r0, 0x2221(r31)
/* 8006A438 00067018  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8006A43C 0006701C  40 82 00 3C */	bne lbl_8006A478
/* 8006A440 00067020  80 1F 19 94 */	lwz r0, 0x1994(r31)
/* 8006A444 00067024  2C 00 00 00 */	cmpwi r0, 0
/* 8006A448 00067028  41 82 00 0C */	beq lbl_8006A454
/* 8006A44C 0006702C  38 00 00 01 */	li r0, 1
/* 8006A450 00067030  48 00 00 08 */	b lbl_8006A458
lbl_8006A454:
/* 8006A454 00067034  38 00 00 00 */	li r0, 0
lbl_8006A458:
/* 8006A458 00067038  90 1F 19 8C */	stw r0, 0x198c(r31)
/* 8006A45C 0006703C  7F E3 FB 78 */	mr r3, r31
/* 8006A460 00067040  48 05 62 35 */	bl func_800C0694
/* 8006A464 00067044  2C 03 00 09 */	cmpwi r3, 9
/* 8006A468 00067048  40 82 00 10 */	bne lbl_8006A478
/* 8006A46C 0006704C  38 7F 00 00 */	addi r3, r31, 0
/* 8006A470 00067050  38 80 00 09 */	li r4, 9
/* 8006A474 00067054  48 05 5D 8D */	bl func_800C0200
lbl_8006A478:
/* 8006A478 00067058  80 7F 19 94 */	lwz r3, 0x1994(r31)
/* 8006A47C 0006705C  2C 03 00 00 */	cmpwi r3, 0
/* 8006A480 00067060  41 82 00 6C */	beq lbl_8006A4EC
/* 8006A484 00067064  38 03 FF FF */	addi r0, r3, -1
/* 8006A488 00067068  90 1F 19 94 */	stw r0, 0x1994(r31)
/* 8006A48C 0006706C  80 1F 19 94 */	lwz r0, 0x1994(r31)
/* 8006A490 00067070  2C 00 00 00 */	cmpwi r0, 0
/* 8006A494 00067074  40 82 00 58 */	bne lbl_8006A4EC
/* 8006A498 00067078  88 1F 22 21 */	lbz r0, 0x2221(r31)
/* 8006A49C 0006707C  38 60 00 01 */	li r3, 1
/* 8006A4A0 00067080  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8006A4A4 00067084  40 82 00 14 */	bne lbl_8006A4B8
/* 8006A4A8 00067088  80 1F 19 90 */	lwz r0, 0x1990(r31)
/* 8006A4AC 0006708C  2C 00 00 00 */	cmpwi r0, 0
/* 8006A4B0 00067090  40 82 00 08 */	bne lbl_8006A4B8
/* 8006A4B4 00067094  38 60 00 00 */	li r3, 0
lbl_8006A4B8:
/* 8006A4B8 00067098  2C 03 00 00 */	cmpwi r3, 0
/* 8006A4BC 0006709C  41 82 00 0C */	beq lbl_8006A4C8
/* 8006A4C0 000670A0  38 00 00 02 */	li r0, 2
/* 8006A4C4 000670A4  48 00 00 08 */	b lbl_8006A4CC
lbl_8006A4C8:
/* 8006A4C8 000670A8  38 00 00 00 */	li r0, 0
lbl_8006A4CC:
/* 8006A4CC 000670AC  90 1F 19 8C */	stw r0, 0x198c(r31)
/* 8006A4D0 000670B0  7F E3 FB 78 */	mr r3, r31
/* 8006A4D4 000670B4  48 05 61 C1 */	bl func_800C0694
/* 8006A4D8 000670B8  2C 03 00 09 */	cmpwi r3, 9
/* 8006A4DC 000670BC  40 82 00 10 */	bne lbl_8006A4EC
/* 8006A4E0 000670C0  38 7F 00 00 */	addi r3, r31, 0
/* 8006A4E4 000670C4  38 80 00 09 */	li r4, 9
/* 8006A4E8 000670C8  48 05 5D 19 */	bl func_800C0200
lbl_8006A4EC:
/* 8006A4EC 000670CC  88 1F 22 1D */	lbz r0, 0x221d(r31)
/* 8006A4F0 000670D0  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 8006A4F4 000670D4  41 82 00 6C */	beq lbl_8006A560
/* 8006A4F8 000670D8  80 7F 20 04 */	lwz r3, 0x2004(r31)
/* 8006A4FC 000670DC  2C 03 00 00 */	cmpwi r3, 0
/* 8006A500 000670E0  41 82 00 60 */	beq lbl_8006A560
/* 8006A504 000670E4  38 03 FF FF */	addi r0, r3, -1
/* 8006A508 000670E8  90 1F 20 04 */	stw r0, 0x2004(r31)
/* 8006A50C 000670EC  80 1F 20 04 */	lwz r0, 0x2004(r31)
/* 8006A510 000670F0  2C 00 00 00 */	cmpwi r0, 0
/* 8006A514 000670F4  40 82 00 34 */	bne lbl_8006A548
/* 8006A518 000670F8  88 1F 22 1D */	lbz r0, 0x221d(r31)
/* 8006A51C 000670FC  38 60 00 00 */	li r3, 0
/* 8006A520 00067100  50 60 0F BC */	rlwimi r0, r3, 1, 0x1e, 0x1e
/* 8006A524 00067104  98 1F 22 1D */	stb r0, 0x221d(r31)
/* 8006A528 00067108  7F E3 FB 78 */	mr r3, r31
/* 8006A52C 0006710C  48 05 61 69 */	bl func_800C0694
/* 8006A530 00067110  2C 03 00 6B */	cmpwi r3, 0x6b
/* 8006A534 00067114  40 82 00 2C */	bne lbl_8006A560
/* 8006A538 00067118  38 7F 00 00 */	addi r3, r31, 0
/* 8006A53C 0006711C  38 80 00 6B */	li r4, 0x6b
/* 8006A540 00067120  48 05 5C C1 */	bl func_800C0200
/* 8006A544 00067124  48 00 00 1C */	b lbl_8006A560
lbl_8006A548:
/* 8006A548 00067128  48 20 10 41 */	bl func_8026B588
/* 8006A54C 0006712C  80 1F 20 04 */	lwz r0, 0x2004(r31)
/* 8006A550 00067130  7C 00 18 00 */	cmpw r0, r3
/* 8006A554 00067134  40 82 00 0C */	bne lbl_8006A560
/* 8006A558 00067138  7F E3 FB 78 */	mr r3, r31
/* 8006A55C 0006713C  48 01 DB 7D */	bl func_800880D8
lbl_8006A560:
/* 8006A560 00067140  88 7F 22 20 */	lbz r3, 0x2220(r31)
/* 8006A564 00067144  54 60 F7 FF */	rlwinm. r0, r3, 0x1e, 0x1f, 0x1f
/* 8006A568 00067148  40 82 00 0C */	bne lbl_8006A574
/* 8006A56C 0006714C  54 60 FF FF */	rlwinm. r0, r3, 0x1f, 0x1f, 0x1f
/* 8006A570 00067150  41 82 00 4C */	beq lbl_8006A5BC
lbl_8006A574:
/* 8006A574 00067154  80 7F 20 08 */	lwz r3, 0x2008(r31)
/* 8006A578 00067158  2C 03 00 00 */	cmpwi r3, 0
/* 8006A57C 0006715C  41 82 00 0C */	beq lbl_8006A588
/* 8006A580 00067160  38 03 FF FF */	addi r0, r3, -1
/* 8006A584 00067164  90 1F 20 08 */	stw r0, 0x2008(r31)
lbl_8006A588:
/* 8006A588 00067168  80 1F 20 08 */	lwz r0, 0x2008(r31)
/* 8006A58C 0006716C  2C 00 00 00 */	cmpwi r0, 0
/* 8006A590 00067170  40 82 00 2C */	bne lbl_8006A5BC
/* 8006A594 00067174  88 7F 22 20 */	lbz r3, 0x2220(r31)
/* 8006A598 00067178  54 60 F7 FF */	rlwinm. r0, r3, 0x1e, 0x1f, 0x1f
/* 8006A59C 0006717C  41 82 00 10 */	beq lbl_8006A5AC
/* 8006A5A0 00067180  7F C3 F3 78 */	mr r3, r30
/* 8006A5A4 00067184  48 06 74 E9 */	bl func_800D1A8C
/* 8006A5A8 00067188  48 00 00 14 */	b lbl_8006A5BC
lbl_8006A5AC:
/* 8006A5AC 0006718C  54 60 FF FF */	rlwinm. r0, r3, 0x1f, 0x1f, 0x1f
/* 8006A5B0 00067190  41 82 00 0C */	beq lbl_8006A5BC
/* 8006A5B4 00067194  7F C3 F3 78 */	mr r3, r30
/* 8006A5B8 00067198  48 06 7D C5 */	bl func_800D237C
lbl_8006A5BC:
/* 8006A5BC 0006719C  80 1F 19 7C */	lwz r0, 0x197c(r31)
/* 8006A5C0 000671A0  28 00 00 00 */	cmplwi r0, 0
/* 8006A5C4 000671A4  41 82 00 3C */	beq lbl_8006A600
/* 8006A5C8 000671A8  80 7F 20 14 */	lwz r3, 0x2014(r31)
/* 8006A5CC 000671AC  2C 03 00 00 */	cmpwi r3, 0
/* 8006A5D0 000671B0  41 82 00 30 */	beq lbl_8006A600
/* 8006A5D4 000671B4  38 03 FF FF */	addi r0, r3, -1
/* 8006A5D8 000671B8  90 1F 20 14 */	stw r0, 0x2014(r31)
/* 8006A5DC 000671BC  80 1F 20 14 */	lwz r0, 0x2014(r31)
/* 8006A5E0 000671C0  2C 00 00 00 */	cmpwi r0, 0
/* 8006A5E4 000671C4  40 82 00 1C */	bne lbl_8006A600
/* 8006A5E8 000671C8  7F C3 F3 78 */	mr r3, r30
/* 8006A5EC 000671CC  48 01 52 FD */	bl func_8007F8E8
/* 8006A5F0 000671D0  80 7F 19 7C */	lwz r3, 0x197c(r31)
/* 8006A5F4 000671D4  48 20 02 F9 */	bl func_8026A8EC
/* 8006A5F8 000671D8  7F C3 F3 78 */	mr r3, r30
/* 8006A5FC 000671DC  48 01 53 B9 */	bl func_8007F9B4
lbl_8006A600:
/* 8006A600 000671E0  88 1F 22 23 */	lbz r0, 0x2223(r31)
/* 8006A604 000671E4  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8006A608 000671E8  41 82 00 38 */	beq lbl_8006A640
/* 8006A60C 000671EC  80 7F 20 28 */	lwz r3, 0x2028(r31)
/* 8006A610 000671F0  2C 03 00 00 */	cmpwi r3, 0
/* 8006A614 000671F4  41 82 00 2C */	beq lbl_8006A640
/* 8006A618 000671F8  38 03 FF FF */	addi r0, r3, -1
/* 8006A61C 000671FC  90 1F 20 28 */	stw r0, 0x2028(r31)
/* 8006A620 00067200  80 1F 20 28 */	lwz r0, 0x2028(r31)
/* 8006A624 00067204  2C 00 00 00 */	cmpwi r0, 0
/* 8006A628 00067208  41 82 00 10 */	beq lbl_8006A638
/* 8006A62C 0006720C  80 1F 20 2C */	lwz r0, 0x202c(r31)
/* 8006A630 00067210  2C 00 00 00 */	cmpwi r0, 0
/* 8006A634 00067214  41 81 00 0C */	bgt lbl_8006A640
lbl_8006A638:
/* 8006A638 00067218  7F C3 F3 78 */	mr r3, r30
/* 8006A63C 0006721C  48 05 DF 05 */	bl func_800C8540
lbl_8006A640:
/* 8006A640 00067220  88 1F 22 27 */	lbz r0, 0x2227(r31)
/* 8006A644 00067224  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 8006A648 00067228  41 82 00 3C */	beq lbl_8006A684
/* 8006A64C 0006722C  80 7F 20 34 */	lwz r3, 0x2034(r31)
/* 8006A650 00067230  2C 03 00 00 */	cmpwi r3, 0
/* 8006A654 00067234  41 82 00 30 */	beq lbl_8006A684
/* 8006A658 00067238  38 03 FF FF */	addi r0, r3, -1
/* 8006A65C 0006723C  90 1F 20 34 */	stw r0, 0x2034(r31)
/* 8006A660 00067240  80 1F 20 34 */	lwz r0, 0x2034(r31)
/* 8006A664 00067244  2C 00 00 00 */	cmpwi r0, 0
/* 8006A668 00067248  41 82 00 10 */	beq lbl_8006A678
/* 8006A66C 0006724C  80 1F 20 38 */	lwz r0, 0x2038(r31)
/* 8006A670 00067250  2C 00 00 00 */	cmpwi r0, 0
/* 8006A674 00067254  41 81 00 10 */	bgt lbl_8006A684
lbl_8006A678:
/* 8006A678 00067258  7F C3 F3 78 */	mr r3, r30
/* 8006A67C 0006725C  48 05 E9 B9 */	bl func_800C9034
/* 8006A680 00067260  48 00 05 08 */	b lbl_8006AB88
lbl_8006A684:
/* 8006A684 00067264  80 1F 19 80 */	lwz r0, 0x1980(r31)
/* 8006A688 00067268  28 00 00 00 */	cmplwi r0, 0
/* 8006A68C 0006726C  41 82 00 AC */	beq lbl_8006A738
/* 8006A690 00067270  80 7F 20 18 */	lwz r3, 0x2018(r31)
/* 8006A694 00067274  38 03 FF FF */	addi r0, r3, -1
/* 8006A698 00067278  90 1F 20 18 */	stw r0, 0x2018(r31)
/* 8006A69C 0006727C  80 7F 20 1C */	lwz r3, 0x201c(r31)
/* 8006A6A0 00067280  38 03 FF FF */	addi r0, r3, -1
/* 8006A6A4 00067284  90 1F 20 1C */	stw r0, 0x201c(r31)
/* 8006A6A8 00067288  80 1F 20 1C */	lwz r0, 0x201c(r31)
/* 8006A6AC 0006728C  2C 00 00 00 */	cmpwi r0, 0
/* 8006A6B0 00067290  40 82 00 3C */	bne lbl_8006A6EC
/* 8006A6B4 00067294  80 8D AE B4 */	lwz r4, lbl_804D6554(r13)
/* 8006A6B8 00067298  3C 00 43 30 */	lis r0, 0x4330
/* 8006A6BC 0006729C  C8 22 88 80 */	lfd f1, lbl_804D8260(r2)
/* 8006A6C0 000672A0  7F E3 FB 78 */	mr r3, r31
/* 8006A6C4 000672A4  80 84 06 F4 */	lwz r4, 0x6f4(r4)
/* 8006A6C8 000672A8  6C 84 80 00 */	xoris r4, r4, 0x8000
/* 8006A6CC 000672AC  90 81 00 24 */	stw r4, 0x24(r1)
/* 8006A6D0 000672B0  90 01 00 20 */	stw r0, 0x20(r1)
/* 8006A6D4 000672B4  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 8006A6D8 000672B8  EC 20 08 28 */	fsubs f1, f0, f1
/* 8006A6DC 000672BC  48 00 25 A1 */	bl func_8006CC7C
/* 8006A6E0 000672C0  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 8006A6E4 000672C4  80 03 06 F8 */	lwz r0, 0x6f8(r3)
/* 8006A6E8 000672C8  90 1F 20 1C */	stw r0, 0x201c(r31)
lbl_8006A6EC:
/* 8006A6EC 000672CC  80 1F 20 18 */	lwz r0, 0x2018(r31)
/* 8006A6F0 000672D0  2C 00 00 00 */	cmpwi r0, 0
/* 8006A6F4 000672D4  41 81 00 44 */	bgt lbl_8006A738
/* 8006A6F8 000672D8  3C 60 80 3B */	lis r3, lbl_803B7488@ha
/* 8006A6FC 000672DC  38 A3 74 88 */	addi r5, r3, lbl_803B7488@l
/* 8006A700 000672E0  80 85 00 00 */	lwz r4, 0(r5)
/* 8006A704 000672E4  7F C3 F3 78 */	mr r3, r30
/* 8006A708 000672E8  80 05 00 04 */	lwz r0, 4(r5)
/* 8006A70C 000672EC  90 81 00 10 */	stw r4, 0x10(r1)
/* 8006A710 000672F0  90 01 00 14 */	stw r0, 0x14(r1)
/* 8006A714 000672F4  80 05 00 08 */	lwz r0, 8(r5)
/* 8006A718 000672F8  90 01 00 18 */	stw r0, 0x18(r1)
/* 8006A71C 000672FC  48 01 51 CD */	bl func_8007F8E8
/* 8006A720 00067300  80 7F 19 80 */	lwz r3, 0x1980(r31)
/* 8006A724 00067304  38 81 00 10 */	addi r4, r1, 0x10
/* 8006A728 00067308  C0 22 88 74 */	lfs f1, lbl_804D8254(r2)
/* 8006A72C 0006730C  48 20 04 AD */	bl func_8026ABD8
/* 8006A730 00067310  7F C3 F3 78 */	mr r3, r30
/* 8006A734 00067314  48 01 58 41 */	bl func_8007FF74
lbl_8006A738:
/* 8006A738 00067318  88 1F 22 26 */	lbz r0, 0x2226(r31)
/* 8006A73C 0006731C  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 8006A740 00067320  41 82 00 74 */	beq lbl_8006A7B4
/* 8006A744 00067324  80 7F 20 30 */	lwz r3, 0x2030(r31)
/* 8006A748 00067328  2C 03 00 00 */	cmpwi r3, 0
/* 8006A74C 0006732C  41 82 00 68 */	beq lbl_8006A7B4
/* 8006A750 00067330  38 03 FF FF */	addi r0, r3, -1
/* 8006A754 00067334  90 1F 20 30 */	stw r0, 0x2030(r31)
/* 8006A758 00067338  80 9F 20 30 */	lwz r4, 0x2030(r31)
/* 8006A75C 0006733C  2C 04 00 00 */	cmpwi r4, 0
/* 8006A760 00067340  40 82 00 10 */	bne lbl_8006A770
/* 8006A764 00067344  7F C3 F3 78 */	mr r3, r30
/* 8006A768 00067348  48 05 E2 FD */	bl func_800C8A64
/* 8006A76C 0006734C  48 00 04 1C */	b lbl_8006AB88
lbl_8006A770:
/* 8006A770 00067350  88 1F 22 26 */	lbz r0, 0x2226(r31)
/* 8006A774 00067354  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 8006A778 00067358  40 82 00 3C */	bne lbl_8006A7B4
/* 8006A77C 0006735C  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 8006A780 00067360  80 03 07 D0 */	lwz r0, 0x7d0(r3)
/* 8006A784 00067364  7C 04 00 00 */	cmpw r4, r0
/* 8006A788 00067368  40 82 00 2C */	bne lbl_8006A7B4
/* 8006A78C 0006736C  38 7F 00 00 */	addi r3, r31, 0
/* 8006A790 00067370  38 80 00 7D */	li r4, 0x7d
/* 8006A794 00067374  38 A0 00 00 */	li r5, 0
/* 8006A798 00067378  48 05 E3 95 */	bl func_800C8B2C
/* 8006A79C 0006737C  2C 03 00 00 */	cmpwi r3, 0
/* 8006A7A0 00067380  41 82 00 14 */	beq lbl_8006A7B4
/* 8006A7A4 00067384  88 1F 22 26 */	lbz r0, 0x2226(r31)
/* 8006A7A8 00067388  38 60 00 01 */	li r3, 1
/* 8006A7AC 0006738C  50 60 07 FE */	rlwimi r0, r3, 0, 0x1f, 0x1f
/* 8006A7B0 00067390  98 1F 22 26 */	stb r0, 0x2226(r31)
lbl_8006A7B4:
/* 8006A7B4 00067394  88 1F 22 21 */	lbz r0, 0x2221(r31)
/* 8006A7B8 00067398  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 8006A7BC 0006739C  41 82 00 74 */	beq lbl_8006A830
/* 8006A7C0 000673A0  80 7F 21 04 */	lwz r3, 0x2104(r31)
/* 8006A7C4 000673A4  2C 03 00 00 */	cmpwi r3, 0
/* 8006A7C8 000673A8  41 82 00 68 */	beq lbl_8006A830
/* 8006A7CC 000673AC  38 03 FF FF */	addi r0, r3, -1
/* 8006A7D0 000673B0  90 1F 21 04 */	stw r0, 0x2104(r31)
/* 8006A7D4 000673B4  80 1F 21 04 */	lwz r0, 0x2104(r31)
/* 8006A7D8 000673B8  2C 00 00 00 */	cmpwi r0, 0
/* 8006A7DC 000673BC  40 82 00 54 */	bne lbl_8006A830
/* 8006A7E0 000673C0  88 1F 22 21 */	lbz r0, 0x2221(r31)
/* 8006A7E4 000673C4  38 60 00 00 */	li r3, 0
/* 8006A7E8 000673C8  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 8006A7EC 000673CC  98 1F 22 21 */	stb r0, 0x2221(r31)
/* 8006A7F0 000673D0  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 8006A7F4 000673D4  28 03 00 00 */	cmplwi r3, 0
/* 8006A7F8 000673D8  41 82 00 2C */	beq lbl_8006A824
/* 8006A7FC 000673DC  48 20 0B 05 */	bl itGetKind
/* 8006A800 000673E0  2C 03 00 67 */	cmpwi r3, 0x67
/* 8006A804 000673E4  40 82 00 20 */	bne lbl_8006A824
/* 8006A808 000673E8  88 1F 22 21 */	lbz r0, 0x2221(r31)
/* 8006A80C 000673EC  38 60 00 01 */	li r3, 1
/* 8006A810 000673F0  50 60 17 7A */	rlwimi r0, r3, 2, 0x1d, 0x1d
/* 8006A814 000673F4  98 1F 22 21 */	stb r0, 0x2221(r31)
/* 8006A818 000673F8  7F C3 F3 78 */	mr r3, r30
/* 8006A81C 000673FC  48 02 C0 AD */	bl func_800968C8
/* 8006A820 00067400  48 00 00 10 */	b lbl_8006A830
lbl_8006A824:
/* 8006A824 00067404  38 7E 00 00 */	addi r3, r30, 0
/* 8006A828 00067408  38 80 00 00 */	li r4, 0
/* 8006A82C 0006740C  48 02 AF 19 */	bl func_80095744
lbl_8006A830:
/* 8006A830 00067410  88 1F 22 1F */	lbz r0, 0x221f(r31)
/* 8006A834 00067414  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 8006A838 00067418  40 82 00 C0 */	bne lbl_8006A8F8
/* 8006A83C 0006741C  4B FC 69 09 */	bl func_80031144
/* 8006A840 00067420  C0 02 88 70 */	lfs f0, lbl_804D8250(r2)
/* 8006A844 00067424  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8006A848 00067428  40 82 00 B0 */	bne lbl_8006A8F8
/* 8006A84C 0006742C  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 8006A850 00067430  3C 00 43 30 */	lis r0, 0x4330
/* 8006A854 00067434  C8 22 88 80 */	lfd f1, lbl_804D8260(r2)
/* 8006A858 00067438  80 63 07 B0 */	lwz r3, 0x7b0(r3)
/* 8006A85C 0006743C  C0 5F 18 30 */	lfs f2, 0x1830(r31)
/* 8006A860 00067440  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8006A864 00067444  90 61 00 24 */	stw r3, 0x24(r1)
/* 8006A868 00067448  90 01 00 20 */	stw r0, 0x20(r1)
/* 8006A86C 0006744C  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 8006A870 00067450  EC 00 08 28 */	fsubs f0, f0, f1
/* 8006A874 00067454  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8006A878 00067458  40 80 00 80 */	bge lbl_8006A8F8
/* 8006A87C 0006745C  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 8006A880 00067460  48 29 21 19 */	bl func_802FC998
/* 8006A884 00067464  2C 03 00 00 */	cmpwi r3, 0
/* 8006A888 00067468  41 82 00 24 */	beq lbl_8006A8AC
/* 8006A88C 0006746C  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 8006A890 00067470  4B FC 9E 9D */	bl Player_GetMoreFlagsBit3
/* 8006A894 00067474  2C 03 00 00 */	cmpwi r3, 0
/* 8006A898 00067478  41 82 00 14 */	beq lbl_8006A8AC
/* 8006A89C 0006747C  80 7F 19 10 */	lwz r3, 0x1910(r31)
/* 8006A8A0 00067480  38 03 00 01 */	addi r0, r3, 1
/* 8006A8A4 00067484  90 1F 19 10 */	stw r0, 0x1910(r31)
/* 8006A8A8 00067488  48 00 00 0C */	b lbl_8006A8B4
lbl_8006A8AC:
/* 8006A8AC 0006748C  38 00 00 00 */	li r0, 0
/* 8006A8B0 00067490  90 1F 19 10 */	stw r0, 0x1910(r31)
lbl_8006A8B4:
/* 8006A8B4 00067494  80 8D AE B4 */	lwz r4, lbl_804D6554(r13)
/* 8006A8B8 00067498  80 7F 19 10 */	lwz r3, 0x1910(r31)
/* 8006A8BC 0006749C  80 04 07 AC */	lwz r0, 0x7ac(r4)
/* 8006A8C0 000674A0  7C 03 00 00 */	cmpw r3, r0
/* 8006A8C4 000674A4  41 80 00 34 */	blt lbl_8006A8F8
/* 8006A8C8 000674A8  80 84 07 B4 */	lwz r4, 0x7b4(r4)
/* 8006A8CC 000674AC  3C 00 43 30 */	lis r0, 0x4330
/* 8006A8D0 000674B0  C8 22 88 80 */	lfd f1, lbl_804D8260(r2)
/* 8006A8D4 000674B4  38 7F 00 00 */	addi r3, r31, 0
/* 8006A8D8 000674B8  6C 84 80 00 */	xoris r4, r4, 0x8000
/* 8006A8DC 000674BC  90 81 00 24 */	stw r4, 0x24(r1)
/* 8006A8E0 000674C0  90 01 00 20 */	stw r0, 0x20(r1)
/* 8006A8E4 000674C4  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 8006A8E8 000674C8  EC 20 08 28 */	fsubs f1, f0, f1
/* 8006A8EC 000674CC  48 00 23 91 */	bl func_8006CC7C
/* 8006A8F0 000674D0  38 00 00 00 */	li r0, 0
/* 8006A8F4 000674D4  90 1F 19 10 */	stw r0, 0x1910(r31)
lbl_8006A8F8:
/* 8006A8F8 000674D8  80 7F 18 F0 */	lwz r3, 0x18f0(r31)
/* 8006A8FC 000674DC  2C 03 00 00 */	cmpwi r3, 0
/* 8006A900 000674E0  41 82 00 C4 */	beq lbl_8006A9C4
/* 8006A904 000674E4  38 03 FF FF */	addi r0, r3, -1
/* 8006A908 000674E8  90 1F 18 F0 */	stw r0, 0x18f0(r31)
/* 8006A90C 000674EC  C0 3F 18 30 */	lfs f1, 0x1830(r31)
/* 8006A910 000674F0  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006A914 000674F4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8006A918 000674F8  40 81 00 58 */	ble lbl_8006A970
/* 8006A91C 000674FC  C0 02 88 70 */	lfs f0, lbl_804D8250(r2)
/* 8006A920 00067500  38 7F 00 00 */	addi r3, r31, 0
/* 8006A924 00067504  38 80 00 7D */	li r4, 0x7d
/* 8006A928 00067508  EC 01 00 28 */	fsubs f0, f1, f0
/* 8006A92C 0006750C  38 A0 00 7F */	li r5, 0x7f
/* 8006A930 00067510  38 C0 00 40 */	li r6, 0x40
/* 8006A934 00067514  D0 1F 18 30 */	stfs f0, 0x1830(r31)
/* 8006A938 00067518  48 01 DD 09 */	bl func_80088640
/* 8006A93C 0006751C  C0 1F 18 30 */	lfs f0, 0x1830(r31)
/* 8006A940 00067520  88 9F 22 1F */	lbz r4, 0x221f(r31)
/* 8006A944 00067524  FC 00 00 1E */	fctiwz f0, f0
/* 8006A948 00067528  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 8006A94C 0006752C  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 8006A950 00067530  D8 01 00 20 */	stfd f0, 0x20(r1)
/* 8006A954 00067534  80 A1 00 24 */	lwz r5, 0x24(r1)
/* 8006A958 00067538  4B FC 9A C1 */	bl Player_SetHPByIndex
/* 8006A95C 0006753C  88 9F 22 1F */	lbz r4, 0x221f(r31)
/* 8006A960 00067540  38 A0 00 01 */	li r5, 1
/* 8006A964 00067544  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 8006A968 00067548  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 8006A96C 0006754C  4B FD 62 21 */	bl func_80040B8C
lbl_8006A970:
/* 8006A970 00067550  C0 3F 18 30 */	lfs f1, 0x1830(r31)
/* 8006A974 00067554  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006A978 00067558  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8006A97C 0006755C  4C 40 13 82 */	cror 2, 0, 2
/* 8006A980 00067560  40 82 00 10 */	bne lbl_8006A990
/* 8006A984 00067564  D0 1F 18 30 */	stfs f0, 0x1830(r31)
/* 8006A988 00067568  38 00 00 00 */	li r0, 0
/* 8006A98C 0006756C  90 1F 18 F0 */	stw r0, 0x18f0(r31)
lbl_8006A990:
/* 8006A990 00067570  80 1F 18 F0 */	lwz r0, 0x18f0(r31)
/* 8006A994 00067574  2C 00 00 00 */	cmpwi r0, 0
/* 8006A998 00067578  40 82 00 2C */	bne lbl_8006A9C4
/* 8006A99C 0006757C  7F E3 FB 78 */	mr r3, r31
/* 8006A9A0 00067580  48 05 5C F5 */	bl func_800C0694
/* 8006A9A4 00067584  2C 03 00 08 */	cmpwi r3, 8
/* 8006A9A8 00067588  40 82 00 10 */	bne lbl_8006A9B8
/* 8006A9AC 0006758C  38 7F 00 00 */	addi r3, r31, 0
/* 8006A9B0 00067590  38 80 00 08 */	li r4, 8
/* 8006A9B4 00067594  48 05 58 4D */	bl func_800C0200
lbl_8006A9B8:
/* 8006A9B8 00067598  38 7F 00 00 */	addi r3, r31, 0
/* 8006A9BC 0006759C  38 80 00 02 */	li r4, 2
/* 8006A9C0 000675A0  48 01 43 15 */	bl func_8007ECD4
lbl_8006A9C4:
/* 8006A9C4 000675A4  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 8006A9C8 000675A8  28 03 00 00 */	cmplwi r3, 0
/* 8006A9CC 000675AC  41 82 00 1C */	beq lbl_8006A9E8
/* 8006A9D0 000675B0  48 20 09 31 */	bl itGetKind
/* 8006A9D4 000675B4  2C 03 00 1C */	cmpwi r3, 0x1c
/* 8006A9D8 000675B8  41 82 00 08 */	beq lbl_8006A9E0
/* 8006A9DC 000675BC  48 00 00 0C */	b lbl_8006A9E8
lbl_8006A9E0:
/* 8006A9E0 000675C0  7F C3 F3 78 */	mr r3, r30
/* 8006A9E4 000675C4  48 05 A7 39 */	bl func_800C511C
lbl_8006A9E8:
/* 8006A9E8 000675C8  A0 7F 18 FA */	lhz r3, 0x18fa(r31)
/* 8006A9EC 000675CC  28 03 00 00 */	cmplwi r3, 0
/* 8006A9F0 000675D0  41 82 00 30 */	beq lbl_8006AA20
/* 8006A9F4 000675D4  38 03 FF FF */	addi r0, r3, -1
/* 8006A9F8 000675D8  B0 1F 18 FA */	sth r0, 0x18fa(r31)
/* 8006A9FC 000675DC  88 7F 18 FC */	lbz r3, 0x18fc(r31)
/* 8006AA00 000675E0  38 03 00 01 */	addi r0, r3, 1
/* 8006AA04 000675E4  98 1F 18 FC */	stb r0, 0x18fc(r31)
/* 8006AA08 000675E8  88 7F 18 FC */	lbz r3, 0x18fc(r31)
/* 8006AA0C 000675EC  88 1F 18 FD */	lbz r0, 0x18fd(r31)
/* 8006AA10 000675F0  7C 03 00 40 */	cmplw r3, r0
/* 8006AA14 000675F4  41 80 00 0C */	blt lbl_8006AA20
/* 8006AA18 000675F8  38 00 00 00 */	li r0, 0
/* 8006AA1C 000675FC  98 1F 18 FC */	stb r0, 0x18fc(r31)
lbl_8006AA20:
/* 8006AA20 00067600  80 9F 00 04 */	lwz r4, 4(r31)
/* 8006AA24 00067604  3C 60 80 3C */	lis r3, lbl_803C1DB4@ha
/* 8006AA28 00067608  38 03 1D B4 */	addi r0, r3, lbl_803C1DB4@l
/* 8006AA2C 0006760C  54 83 10 3A */	slwi r3, r4, 2
/* 8006AA30 00067610  7C 60 1A 14 */	add r3, r0, r3
/* 8006AA34 00067614  81 83 00 00 */	lwz r12, 0(r3)
/* 8006AA38 00067618  28 0C 00 00 */	cmplwi r12, 0
/* 8006AA3C 0006761C  41 82 00 10 */	beq lbl_8006AA4C
/* 8006AA40 00067620  7D 88 03 A6 */	mtlr r12
/* 8006AA44 00067624  38 7E 00 00 */	addi r3, r30, 0
/* 8006AA48 00067628  4E 80 00 21 */	blrl 
lbl_8006AA4C:
/* 8006AA4C 0006762C  81 9F 21 CC */	lwz r12, 0x21cc(r31)
/* 8006AA50 00067630  28 0C 00 00 */	cmplwi r12, 0
/* 8006AA54 00067634  41 82 00 10 */	beq lbl_8006AA64
/* 8006AA58 00067638  7D 88 03 A6 */	mtlr r12
/* 8006AA5C 0006763C  38 7E 00 00 */	addi r3, r30, 0
/* 8006AA60 00067640  4E 80 00 21 */	blrl 
lbl_8006AA64:
/* 8006AA64 00067644  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 8006AA68 00067648  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 8006AA6C 0006764C  40 82 01 0C */	bne lbl_8006AB78
/* 8006AA70 00067650  A0 7F 20 9A */	lhz r3, 0x209a(r31)
/* 8006AA74 00067654  28 03 00 01 */	cmplwi r3, 1
/* 8006AA78 00067658  40 81 00 18 */	ble lbl_8006AA90
/* 8006AA7C 0006765C  88 1F 22 1D */	lbz r0, 0x221d(r31)
/* 8006AA80 00067660  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 8006AA84 00067664  40 82 00 0C */	bne lbl_8006AA90
/* 8006AA88 00067668  38 03 FF FF */	addi r0, r3, -1
/* 8006AA8C 0006766C  B0 1F 20 9A */	sth r0, 0x209a(r31)
lbl_8006AA90:
/* 8006AA90 00067670  88 1F 22 23 */	lbz r0, 0x2223(r31)
/* 8006AA94 00067674  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8006AA98 00067678  41 82 00 5C */	beq lbl_8006AAF4
/* 8006AA9C 0006767C  88 1F 01 04 */	lbz r0, 0x104(r31)
/* 8006AAA0 00067680  28 00 00 14 */	cmplwi r0, 0x14
/* 8006AAA4 00067684  40 82 00 14 */	bne lbl_8006AAB8
/* 8006AAA8 00067688  7F C3 F3 78 */	mr r3, r30
/* 8006AAAC 0006768C  C0 22 88 74 */	lfs f1, lbl_804D8254(r2)
/* 8006AAB0 00067690  48 00 46 4D */	bl func_8006F0FC
/* 8006AAB4 00067694  48 00 00 14 */	b lbl_8006AAC8
lbl_8006AAB8:
/* 8006AAB8 00067698  C0 3F 08 9C */	lfs f1, 0x89c(r31)
/* 8006AABC 0006769C  C0 1F 08 A0 */	lfs f0, 0x8a0(r31)
/* 8006AAC0 000676A0  EC 01 00 2A */	fadds f0, f1, f0
/* 8006AAC4 000676A4  D0 1F 08 9C */	stfs f0, 0x89c(r31)
lbl_8006AAC8:
/* 8006AAC8 000676A8  88 7F 01 04 */	lbz r3, 0x104(r31)
/* 8006AACC 000676AC  38 03 FF FF */	addi r0, r3, -1
/* 8006AAD0 000676B0  98 1F 01 04 */	stb r0, 0x104(r31)
/* 8006AAD4 000676B4  88 1F 01 04 */	lbz r0, 0x104(r31)
/* 8006AAD8 000676B8  28 00 00 00 */	cmplwi r0, 0
/* 8006AADC 000676BC  40 82 00 18 */	bne lbl_8006AAF4
/* 8006AAE0 000676C0  7F C3 F3 78 */	mr r3, r30
/* 8006AAE4 000676C4  C0 3F 08 9C */	lfs f1, 0x89c(r31)
/* 8006AAE8 000676C8  48 00 46 15 */	bl func_8006F0FC
/* 8006AAEC 000676CC  38 00 00 14 */	li r0, 0x14
/* 8006AAF0 000676D0  98 1F 01 04 */	stb r0, 0x104(r31)
lbl_8006AAF4:
/* 8006AAF4 000676D4  C0 02 88 78 */	lfs f0, lbl_804D8258(r2)
/* 8006AAF8 000676D8  C0 3F 21 38 */	lfs f1, 0x2138(r31)
/* 8006AAFC 000676DC  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8006AB00 000676E0  41 82 00 10 */	beq lbl_8006AB10
/* 8006AB04 000676E4  C0 02 88 70 */	lfs f0, lbl_804D8250(r2)
/* 8006AB08 000676E8  EC 01 00 2A */	fadds f0, f1, f0
/* 8006AB0C 000676EC  D0 1F 21 38 */	stfs f0, 0x2138(r31)
lbl_8006AB10:
/* 8006AB10 000676F0  80 7F 18 AC */	lwz r3, 0x18ac(r31)
/* 8006AB14 000676F4  2C 03 FF FF */	cmpwi r3, -1
/* 8006AB18 000676F8  41 82 00 0C */	beq lbl_8006AB24
/* 8006AB1C 000676FC  38 03 00 01 */	addi r0, r3, 1
/* 8006AB20 00067700  90 1F 18 AC */	stw r0, 0x18ac(r31)
lbl_8006AB24:
/* 8006AB24 00067704  7F C3 F3 78 */	mr r3, r30
/* 8006AB28 00067708  48 00 40 7D */	bl func_8006EBA4
/* 8006AB2C 0006770C  7F C3 F3 78 */	mr r3, r30
/* 8006AB30 00067710  48 06 C6 A9 */	bl func_800D71D8
/* 8006AB34 00067714  7F C3 F3 78 */	mr r3, r30
/* 8006AB38 00067718  48 00 B9 A5 */	bl func_800764DC
/* 8006AB3C 0006771C  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 8006AB40 00067720  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 8006AB44 00067724  40 82 00 14 */	bne lbl_8006AB58
/* 8006AB48 00067728  88 9F 22 1F */	lbz r4, 0x221f(r31)
/* 8006AB4C 0006772C  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 8006AB50 00067730  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 8006AB54 00067734  4B FD 66 71 */	bl func_800411C4
lbl_8006AB58:
/* 8006AB58 00067738  7F C3 F3 78 */	mr r3, r30
/* 8006AB5C 0006773C  48 07 43 DD */	bl func_800DEF38
/* 8006AB60 00067740  81 9F 21 A0 */	lwz r12, 0x21a0(r31)
/* 8006AB64 00067744  28 0C 00 00 */	cmplwi r12, 0
/* 8006AB68 00067748  41 82 00 10 */	beq lbl_8006AB78
/* 8006AB6C 0006774C  7D 88 03 A6 */	mtlr r12
/* 8006AB70 00067750  38 7E 00 00 */	addi r3, r30, 0
/* 8006AB74 00067754  4E 80 00 21 */	blrl 
lbl_8006AB78:
/* 8006AB78 00067758  7F C3 F3 78 */	mr r3, r30
/* 8006AB7C 0006775C  48 01 35 69 */	bl func_8007E0E4
/* 8006AB80 00067760  7F C3 F3 78 */	mr r3, r30
/* 8006AB84 00067764  48 05 58 85 */	bl func_800C0408
lbl_8006AB88:
/* 8006AB88 00067768  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8006AB8C 0006776C  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8006AB90 00067770  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 8006AB94 00067774  38 21 00 30 */	addi r1, r1, 0x30
/* 8006AB98 00067778  7C 08 03 A6 */	mtlr r0
/* 8006AB9C 0006777C  4E 80 00 20 */	blr 
}

/// https://decomp.me/scratch/Y9c4V
void func_8006ABA0(HSD_GObj* fighterObj) {
    Fighter* fp = fighterObj->user_data;
    if ((fp->x221F_flag.bits.b3 == 0) && (func_800A2040() != 0)) {
        func_800B3900(fighterObj);
    }
}


asm void func_8006ABEC()
{
	nofralloc 
/* 8006ABEC 000677CC  7C 08 02 A6 */	mflr r0
/* 8006ABF0 000677D0  90 01 00 04 */	stw r0, 4(r1)
/* 8006ABF4 000677D4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8006ABF8 000677D8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8006ABFC 000677DC  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8006AC00 000677E0  48 06 02 81 */	bl func_800CAE80
/* 8006AC04 000677E4  2C 03 00 00 */	cmpwi r3, 0
/* 8006AC08 000677E8  41 82 00 18 */	beq lbl_8006AC20
/* 8006AC0C 000677EC  88 7F 06 85 */	lbz r3, 0x685(r31)
/* 8006AC10 000677F0  38 00 00 00 */	li r0, 0
/* 8006AC14 000677F4  98 7F 06 8A */	stb r3, 0x68a(r31)
/* 8006AC18 000677F8  98 1F 06 85 */	stb r0, 0x685(r31)
/* 8006AC1C 000677FC  48 00 00 18 */	b lbl_8006AC34
lbl_8006AC20:
/* 8006AC20 00067800  88 7F 06 85 */	lbz r3, 0x685(r31)
/* 8006AC24 00067804  28 03 00 FF */	cmplwi r3, 0xff
/* 8006AC28 00067808  40 80 00 0C */	bge lbl_8006AC34
/* 8006AC2C 0006780C  38 03 00 01 */	addi r0, r3, 1
/* 8006AC30 00067810  98 1F 06 85 */	stb r0, 0x685(r31)
lbl_8006AC34:
/* 8006AC34 00067814  7F E3 FB 78 */	mr r3, r31
/* 8006AC38 00067818  48 06 BC F1 */	bl func_800D6928
/* 8006AC3C 0006781C  2C 03 00 00 */	cmpwi r3, 0
/* 8006AC40 00067820  41 82 00 18 */	beq lbl_8006AC58
/* 8006AC44 00067824  88 7F 06 86 */	lbz r3, 0x686(r31)
/* 8006AC48 00067828  38 00 00 00 */	li r0, 0
/* 8006AC4C 0006782C  98 7F 06 8B */	stb r3, 0x68b(r31)
/* 8006AC50 00067830  98 1F 06 86 */	stb r0, 0x686(r31)
/* 8006AC54 00067834  48 00 00 18 */	b lbl_8006AC6C
lbl_8006AC58:
/* 8006AC58 00067838  88 7F 06 86 */	lbz r3, 0x686(r31)
/* 8006AC5C 0006783C  28 03 00 FF */	cmplwi r3, 0xff
/* 8006AC60 00067840  40 80 00 0C */	bge lbl_8006AC6C
/* 8006AC64 00067844  38 03 00 01 */	addi r0, r3, 1
/* 8006AC68 00067848  98 1F 06 86 */	stb r0, 0x686(r31)
lbl_8006AC6C:
/* 8006AC6C 0006784C  7F E3 FB 78 */	mr r3, r31
/* 8006AC70 00067850  48 06 BC 1D */	bl func_800D688C
/* 8006AC74 00067854  2C 03 00 00 */	cmpwi r3, 0
/* 8006AC78 00067858  41 82 00 10 */	beq lbl_8006AC88
/* 8006AC7C 0006785C  38 00 00 00 */	li r0, 0
/* 8006AC80 00067860  98 1F 06 87 */	stb r0, 0x687(r31)
/* 8006AC84 00067864  48 00 00 18 */	b lbl_8006AC9C
lbl_8006AC88:
/* 8006AC88 00067868  88 7F 06 87 */	lbz r3, 0x687(r31)
/* 8006AC8C 0006786C  28 03 00 FF */	cmplwi r3, 0xff
/* 8006AC90 00067870  40 80 00 0C */	bge lbl_8006AC9C
/* 8006AC94 00067874  38 03 00 01 */	addi r0, r3, 1
/* 8006AC98 00067878  98 1F 06 87 */	stb r0, 0x687(r31)
lbl_8006AC9C:
/* 8006AC9C 0006787C  7F E3 FB 78 */	mr r3, r31
/* 8006ACA0 00067880  48 02 B8 5D */	bl func_800964FC
/* 8006ACA4 00067884  2C 03 00 00 */	cmpwi r3, 0
/* 8006ACA8 00067888  41 82 00 10 */	beq lbl_8006ACB8
/* 8006ACAC 0006788C  38 00 00 00 */	li r0, 0
/* 8006ACB0 00067890  98 1F 06 88 */	stb r0, 0x688(r31)
/* 8006ACB4 00067894  48 00 00 18 */	b lbl_8006ACCC
lbl_8006ACB8:
/* 8006ACB8 00067898  88 7F 06 88 */	lbz r3, 0x688(r31)
/* 8006ACBC 0006789C  28 03 00 FF */	cmplwi r3, 0xff
/* 8006ACC0 000678A0  40 80 00 0C */	bge lbl_8006ACCC
/* 8006ACC4 000678A4  38 03 00 01 */	addi r0, r3, 1
/* 8006ACC8 000678A8  98 1F 06 88 */	stb r0, 0x688(r31)
lbl_8006ACCC:
/* 8006ACCC 000678AC  7F E3 FB 78 */	mr r3, r31
/* 8006ACD0 000678B0  48 06 BA F5 */	bl func_800D67C4
/* 8006ACD4 000678B4  2C 03 00 00 */	cmpwi r3, 0
/* 8006ACD8 000678B8  41 82 00 10 */	beq lbl_8006ACE8
/* 8006ACDC 000678BC  38 00 00 00 */	li r0, 0
/* 8006ACE0 000678C0  98 1F 06 89 */	stb r0, 0x689(r31)
/* 8006ACE4 000678C4  48 00 00 18 */	b lbl_8006ACFC
lbl_8006ACE8:
/* 8006ACE8 000678C8  88 7F 06 89 */	lbz r3, 0x689(r31)
/* 8006ACEC 000678CC  28 03 00 FF */	cmplwi r3, 0xff
/* 8006ACF0 000678D0  40 80 00 0C */	bge lbl_8006ACFC
/* 8006ACF4 000678D4  38 03 00 01 */	addi r0, r3, 1
/* 8006ACF8 000678D8  98 1F 06 89 */	stb r0, 0x689(r31)
lbl_8006ACFC:
/* 8006ACFC 000678DC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8006AD00 000678E0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8006AD04 000678E4  38 21 00 18 */	addi r1, r1, 0x18
/* 8006AD08 000678E8  7C 08 03 A6 */	mtlr r0
/* 8006AD0C 000678EC  4E 80 00 20 */	blr 
}

asm void func_8006AD10()
{
	nofralloc
/* 8006AD10 000678F0  7C 08 02 A6 */	mflr r0
/* 8006AD14 000678F4  90 01 00 04 */	stw r0, 4(r1)
/* 8006AD18 000678F8  94 21 FF 88 */	stwu r1, -0x78(r1)
/* 8006AD1C 000678FC  DB E1 00 70 */	stfd f31, 0x70(r1)
/* 8006AD20 00067900  93 E1 00 6C */	stw r31, 0x6c(r1)
/* 8006AD24 00067904  93 C1 00 68 */	stw r30, 0x68(r1)
/* 8006AD28 00067908  7C 7E 1B 78 */	mr r30, r3
/* 8006AD2C 0006790C  93 A1 00 64 */	stw r29, 0x64(r1)
/* 8006AD30 00067910  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8006AD34 00067914  88 03 22 1F */	lbz r0, 0x221f(r3)
/* 8006AD38 00067918  3B E3 00 00 */	addi r31, r3, 0
/* 8006AD3C 0006791C  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 8006AD40 00067920  40 82 0A CC */	bne lbl_8006B80C
/* 8006AD44 00067924  88 1F 22 24 */	lbz r0, 0x2224(r31)
/* 8006AD48 00067928  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8006AD4C 0006792C  40 82 09 2C */	bne lbl_8006B678
/* 8006AD50 00067930  88 1F 22 1D */	lbz r0, 0x221d(r31)
/* 8006AD54 00067934  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 8006AD58 00067938  40 82 00 48 */	bne lbl_8006ADA0
/* 8006AD5C 0006793C  C0 1F 06 30 */	lfs f0, 0x630(r31)
/* 8006AD60 00067940  38 60 00 01 */	li r3, 1
/* 8006AD64 00067944  D0 1F 06 28 */	stfs f0, 0x628(r31)
/* 8006AD68 00067948  C0 1F 06 34 */	lfs f0, 0x634(r31)
/* 8006AD6C 0006794C  D0 1F 06 2C */	stfs f0, 0x62c(r31)
/* 8006AD70 00067950  C0 1F 06 48 */	lfs f0, 0x648(r31)
/* 8006AD74 00067954  D0 1F 06 40 */	stfs f0, 0x640(r31)
/* 8006AD78 00067958  C0 1F 06 4C */	lfs f0, 0x64c(r31)
/* 8006AD7C 0006795C  D0 1F 06 44 */	stfs f0, 0x644(r31)
/* 8006AD80 00067960  C0 1F 06 58 */	lfs f0, 0x658(r31)
/* 8006AD84 00067964  D0 1F 06 54 */	stfs f0, 0x654(r31)
/* 8006AD88 00067968  80 1F 06 64 */	lwz r0, 0x664(r31)
/* 8006AD8C 0006796C  90 1F 06 60 */	stw r0, 0x660(r31)
/* 8006AD90 00067970  88 1F 22 1D */	lbz r0, 0x221d(r31)
/* 8006AD94 00067974  50 60 26 F6 */	rlwimi r0, r3, 4, 0x1b, 0x1b
/* 8006AD98 00067978  98 1F 22 1D */	stb r0, 0x221d(r31)
/* 8006AD9C 0006797C  48 00 00 34 */	b lbl_8006ADD0
lbl_8006ADA0:
/* 8006ADA0 00067980  C0 1F 06 20 */	lfs f0, 0x620(r31)
/* 8006ADA4 00067984  D0 1F 06 28 */	stfs f0, 0x628(r31)
/* 8006ADA8 00067988  C0 1F 06 24 */	lfs f0, 0x624(r31)
/* 8006ADAC 0006798C  D0 1F 06 2C */	stfs f0, 0x62c(r31)
/* 8006ADB0 00067990  C0 1F 06 38 */	lfs f0, 0x638(r31)
/* 8006ADB4 00067994  D0 1F 06 40 */	stfs f0, 0x640(r31)
/* 8006ADB8 00067998  C0 1F 06 3C */	lfs f0, 0x63c(r31)
/* 8006ADBC 0006799C  D0 1F 06 44 */	stfs f0, 0x644(r31)
/* 8006ADC0 000679A0  C0 1F 06 50 */	lfs f0, 0x650(r31)
/* 8006ADC4 000679A4  D0 1F 06 54 */	stfs f0, 0x654(r31)
/* 8006ADC8 000679A8  80 1F 06 5C */	lwz r0, 0x65c(r31)
/* 8006ADCC 000679AC  90 1F 06 60 */	stw r0, 0x660(r31)
lbl_8006ADD0:
/* 8006ADD0 000679B0  7F E3 FB 78 */	mr r3, r31
/* 8006ADD4 000679B4  48 03 72 6D */	bl func_800A2040
/* 8006ADD8 000679B8  2C 03 00 00 */	cmpwi r3, 0
/* 8006ADDC 000679BC  41 82 00 84 */	beq lbl_8006AE60
/* 8006ADE0 000679C0  7F E3 FB 78 */	mr r3, r31
/* 8006ADE4 000679C4  48 03 6A 01 */	bl func_800A17E4
/* 8006ADE8 000679C8  D0 3F 06 20 */	stfs f1, 0x620(r31)
/* 8006ADEC 000679CC  7F E3 FB 78 */	mr r3, r31
/* 8006ADF0 000679D0  48 03 6A 85 */	bl func_800A1874
/* 8006ADF4 000679D4  D0 3F 06 24 */	stfs f1, 0x624(r31)
/* 8006ADF8 000679D8  80 0D 93 68 */	lwz r0, lbl_804D4A08(r13)
/* 8006ADFC 000679DC  2C 00 00 03 */	cmpwi r0, 3
/* 8006AE00 000679E0  40 80 00 2C */	bge lbl_8006AE2C
/* 8006AE04 000679E4  48 10 06 19 */	bl func_8016B41C
/* 8006AE08 000679E8  2C 03 00 00 */	cmpwi r3, 0
/* 8006AE0C 000679EC  40 82 00 20 */	bne lbl_8006AE2C
/* 8006AE10 000679F0  7F E3 FB 78 */	mr r3, r31
/* 8006AE14 000679F4  48 03 6B 81 */	bl func_800A1994
/* 8006AE18 000679F8  D0 3F 06 38 */	stfs f1, 0x638(r31)
/* 8006AE1C 000679FC  7F E3 FB 78 */	mr r3, r31
/* 8006AE20 00067A00  48 03 6C 05 */	bl func_800A1A24
/* 8006AE24 00067A04  D0 3F 06 3C */	stfs f1, 0x63c(r31)
/* 8006AE28 00067A08  48 00 00 10 */	b lbl_8006AE38
lbl_8006AE2C:
/* 8006AE2C 00067A0C  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006AE30 00067A10  D0 1F 06 38 */	stfs f0, 0x638(r31)
/* 8006AE34 00067A14  D0 1F 06 3C */	stfs f0, 0x63c(r31)
lbl_8006AE38:
/* 8006AE38 00067A18  7F E3 FB 78 */	mr r3, r31
/* 8006AE3C 00067A1C  48 03 6A C9 */	bl func_800A1904
/* 8006AE40 00067A20  7F E3 FB 78 */	mr r3, r31
/* 8006AE44 00067A24  FF E0 08 90 */	fmr f31, f1
/* 8006AE48 00067A28  48 03 6B 01 */	bl func_800A1948
/* 8006AE4C 00067A2C  FC 1F 08 40 */	fcmpo cr0, f31, f1
/* 8006AE50 00067A30  40 81 00 08 */	ble lbl_8006AE58
/* 8006AE54 00067A34  FC 20 F8 90 */	fmr f1, f31
lbl_8006AE58:
/* 8006AE58 00067A38  D0 3F 06 50 */	stfs f1, 0x650(r31)
/* 8006AE5C 00067A3C  48 00 00 B4 */	b lbl_8006AF10
lbl_8006AE60:
/* 8006AE60 00067A40  88 1F 06 18 */	lbz r0, 0x618(r31)
/* 8006AE64 00067A44  3C 60 80 4C */	lis r3, HSD_PadRumbleData@ha
/* 8006AE68 00067A48  3B A3 21 CC */	addi r29, r3, HSD_PadRumbleData@l
/* 8006AE6C 00067A4C  1C 00 00 44 */	mulli r0, r0, 0x44
/* 8006AE70 00067A50  7C 7D 02 14 */	add r3, r29, r0
/* 8006AE74 00067A54  C0 03 00 20 */	lfs f0, 0x20(r3)
/* 8006AE78 00067A58  D0 1F 06 20 */	stfs f0, 0x620(r31)
/* 8006AE7C 00067A5C  88 1F 06 18 */	lbz r0, 0x618(r31)
/* 8006AE80 00067A60  1C 00 00 44 */	mulli r0, r0, 0x44
/* 8006AE84 00067A64  7C 7D 02 14 */	add r3, r29, r0
/* 8006AE88 00067A68  C0 03 00 24 */	lfs f0, 0x24(r3)
/* 8006AE8C 00067A6C  D0 1F 06 24 */	stfs f0, 0x624(r31)
/* 8006AE90 00067A70  80 0D 93 68 */	lwz r0, lbl_804D4A08(r13)
/* 8006AE94 00067A74  2C 00 00 03 */	cmpwi r0, 3
/* 8006AE98 00067A78  40 80 00 3C */	bge lbl_8006AED4
/* 8006AE9C 00067A7C  48 10 05 81 */	bl func_8016B41C
/* 8006AEA0 00067A80  2C 03 00 00 */	cmpwi r3, 0
/* 8006AEA4 00067A84  40 82 00 30 */	bne lbl_8006AED4
/* 8006AEA8 00067A88  88 1F 06 18 */	lbz r0, 0x618(r31)
/* 8006AEAC 00067A8C  1C 00 00 44 */	mulli r0, r0, 0x44
/* 8006AEB0 00067A90  7C 7D 02 14 */	add r3, r29, r0
/* 8006AEB4 00067A94  C0 03 00 28 */	lfs f0, 0x28(r3)
/* 8006AEB8 00067A98  D0 1F 06 38 */	stfs f0, 0x638(r31)
/* 8006AEBC 00067A9C  88 1F 06 18 */	lbz r0, 0x618(r31)
/* 8006AEC0 00067AA0  1C 00 00 44 */	mulli r0, r0, 0x44
/* 8006AEC4 00067AA4  7C 7D 02 14 */	add r3, r29, r0
/* 8006AEC8 00067AA8  C0 03 00 2C */	lfs f0, 0x2c(r3)
/* 8006AECC 00067AAC  D0 1F 06 3C */	stfs f0, 0x63c(r31)
/* 8006AED0 00067AB0  48 00 00 10 */	b lbl_8006AEE0
lbl_8006AED4:
/* 8006AED4 00067AB4  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006AED8 00067AB8  D0 1F 06 38 */	stfs f0, 0x638(r31)
/* 8006AEDC 00067ABC  D0 1F 06 3C */	stfs f0, 0x63c(r31)
lbl_8006AEE0:
/* 8006AEE0 00067AC0  88 1F 06 18 */	lbz r0, 0x618(r31)
/* 8006AEE4 00067AC4  3C 60 80 4C */	lis r3, HSD_PadRumbleData@ha
/* 8006AEE8 00067AC8  38 63 21 CC */	addi r3, r3, HSD_PadRumbleData@l
/* 8006AEEC 00067ACC  1C 00 00 44 */	mulli r0, r0, 0x44
/* 8006AEF0 00067AD0  7C 63 02 14 */	add r3, r3, r0
/* 8006AEF4 00067AD4  C0 23 00 34 */	lfs f1, 0x34(r3)
/* 8006AEF8 00067AD8  C0 03 00 30 */	lfs f0, 0x30(r3)
/* 8006AEFC 00067ADC  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8006AF00 00067AE0  40 81 00 08 */	ble lbl_8006AF08
/* 8006AF04 00067AE4  48 00 00 08 */	b lbl_8006AF0C
lbl_8006AF08:
/* 8006AF08 00067AE8  FC 00 08 90 */	fmr f0, f1
lbl_8006AF0C:
/* 8006AF0C 00067AEC  D0 1F 06 50 */	stfs f0, 0x650(r31)
lbl_8006AF10:
/* 8006AF10 00067AF0  C0 3F 06 20 */	lfs f1, 0x620(r31)
/* 8006AF14 00067AF4  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006AF18 00067AF8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8006AF1C 00067AFC  40 80 00 08 */	bge lbl_8006AF24
/* 8006AF20 00067B00  FC 20 08 50 */	fneg f1, f1
lbl_8006AF24:
/* 8006AF24 00067B04  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 8006AF28 00067B08  C0 03 00 00 */	lfs f0, 0(r3)
/* 8006AF2C 00067B0C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8006AF30 00067B10  4C 40 13 82 */	cror 2, 0, 2
/* 8006AF34 00067B14  40 82 00 0C */	bne lbl_8006AF40
/* 8006AF38 00067B18  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006AF3C 00067B1C  D0 1F 06 20 */	stfs f0, 0x620(r31)
lbl_8006AF40:
/* 8006AF40 00067B20  C0 3F 06 24 */	lfs f1, 0x624(r31)
/* 8006AF44 00067B24  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006AF48 00067B28  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8006AF4C 00067B2C  40 80 00 08 */	bge lbl_8006AF54
/* 8006AF50 00067B30  FC 20 08 50 */	fneg f1, f1
lbl_8006AF54:
/* 8006AF54 00067B34  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 8006AF58 00067B38  C0 03 00 04 */	lfs f0, 4(r3)
/* 8006AF5C 00067B3C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8006AF60 00067B40  4C 40 13 82 */	cror 2, 0, 2
/* 8006AF64 00067B44  40 82 00 0C */	bne lbl_8006AF70
/* 8006AF68 00067B48  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006AF6C 00067B4C  D0 1F 06 24 */	stfs f0, 0x624(r31)
lbl_8006AF70:
/* 8006AF70 00067B50  C0 3F 06 38 */	lfs f1, 0x638(r31)
/* 8006AF74 00067B54  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006AF78 00067B58  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8006AF7C 00067B5C  40 80 00 08 */	bge lbl_8006AF84
/* 8006AF80 00067B60  FC 20 08 50 */	fneg f1, f1
lbl_8006AF84:
/* 8006AF84 00067B64  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 8006AF88 00067B68  C0 03 00 00 */	lfs f0, 0(r3)
/* 8006AF8C 00067B6C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8006AF90 00067B70  4C 40 13 82 */	cror 2, 0, 2
/* 8006AF94 00067B74  40 82 00 0C */	bne lbl_8006AFA0
/* 8006AF98 00067B78  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006AF9C 00067B7C  D0 1F 06 38 */	stfs f0, 0x638(r31)
lbl_8006AFA0:
/* 8006AFA0 00067B80  C0 3F 06 3C */	lfs f1, 0x63c(r31)
/* 8006AFA4 00067B84  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006AFA8 00067B88  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8006AFAC 00067B8C  40 80 00 08 */	bge lbl_8006AFB4
/* 8006AFB0 00067B90  FC 20 08 50 */	fneg f1, f1
lbl_8006AFB4:
/* 8006AFB4 00067B94  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 8006AFB8 00067B98  C0 03 00 04 */	lfs f0, 4(r3)
/* 8006AFBC 00067B9C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8006AFC0 00067BA0  4C 40 13 82 */	cror 2, 0, 2
/* 8006AFC4 00067BA4  40 82 00 0C */	bne lbl_8006AFD0
/* 8006AFC8 00067BA8  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006AFCC 00067BAC  D0 1F 06 3C */	stfs f0, 0x63c(r31)
lbl_8006AFD0:
/* 8006AFD0 00067BB0  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 8006AFD4 00067BB4  C0 3F 06 50 */	lfs f1, 0x650(r31)
/* 8006AFD8 00067BB8  C0 03 00 10 */	lfs f0, 0x10(r3)
/* 8006AFDC 00067BBC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8006AFE0 00067BC0  4C 40 13 82 */	cror 2, 0, 2
/* 8006AFE4 00067BC4  40 82 00 0C */	bne lbl_8006AFF0
/* 8006AFE8 00067BC8  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006AFEC 00067BCC  D0 1F 06 50 */	stfs f0, 0x650(r31)
lbl_8006AFF0:
/* 8006AFF0 00067BD0  7F E3 FB 78 */	mr r3, r31
/* 8006AFF4 00067BD4  48 03 70 4D */	bl func_800A2040
/* 8006AFF8 00067BD8  2C 03 00 00 */	cmpwi r3, 0
/* 8006AFFC 00067BDC  41 82 00 14 */	beq lbl_8006B010
/* 8006B000 00067BE0  7F E3 FB 78 */	mr r3, r31
/* 8006B004 00067BE4  48 03 69 89 */	bl func_800A198C
/* 8006B008 00067BE8  90 7F 06 5C */	stw r3, 0x65c(r31)
/* 8006B00C 00067BEC  48 00 00 20 */	b lbl_8006B02C
lbl_8006B010:
/* 8006B010 00067BF0  88 9F 06 18 */	lbz r4, 0x618(r31)
/* 8006B014 00067BF4  3C 60 80 4C */	lis r3, HSD_PadRumbleData@ha
/* 8006B018 00067BF8  38 03 21 CC */	addi r0, r3, HSD_PadRumbleData@l
/* 8006B01C 00067BFC  1C 64 00 44 */	mulli r3, r4, 0x44
/* 8006B020 00067C00  7C 60 1A 14 */	add r3, r0, r3
/* 8006B024 00067C04  80 03 00 00 */	lwz r0, 0(r3)
/* 8006B028 00067C08  90 1F 06 5C */	stw r0, 0x65c(r31)
lbl_8006B02C:
/* 8006B02C 00067C0C  48 10 00 D1 */	bl func_8016B0FC
/* 8006B030 00067C10  2C 03 00 00 */	cmpwi r3, 0
/* 8006B034 00067C14  41 82 00 3C */	beq lbl_8006B070
/* 8006B038 00067C18  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006B03C 00067C1C  7F E3 FB 78 */	mr r3, r31
/* 8006B040 00067C20  D0 1F 06 50 */	stfs f0, 0x650(r31)
/* 8006B044 00067C24  48 03 6F FD */	bl func_800A2040
/* 8006B048 00067C28  2C 03 00 00 */	cmpwi r3, 0
/* 8006B04C 00067C2C  41 82 00 14 */	beq lbl_8006B060
/* 8006B050 00067C30  80 1F 06 5C */	lwz r0, 0x65c(r31)
/* 8006B054 00067C34  70 00 0D 00 */	andi. r0, r0, 0xd00
/* 8006B058 00067C38  90 1F 06 5C */	stw r0, 0x65c(r31)
/* 8006B05C 00067C3C  48 00 00 80 */	b lbl_8006B0DC
lbl_8006B060:
/* 8006B060 00067C40  80 1F 06 5C */	lwz r0, 0x65c(r31)
/* 8006B064 00067C44  54 00 05 EE */	rlwinm r0, r0, 0, 0x17, 0x17
/* 8006B068 00067C48  90 1F 06 5C */	stw r0, 0x65c(r31)
/* 8006B06C 00067C4C  48 00 00 70 */	b lbl_8006B0DC
lbl_8006B070:
/* 8006B070 00067C50  80 7F 06 5C */	lwz r3, 0x65c(r31)
/* 8006B074 00067C54  54 60 06 75 */	rlwinm. r0, r3, 0, 0x19, 0x1a
/* 8006B078 00067C58  41 82 00 18 */	beq lbl_8006B090
/* 8006B07C 00067C5C  64 60 80 00 */	oris r0, r3, 0x8000
/* 8006B080 00067C60  90 1F 06 5C */	stw r0, 0x65c(r31)
/* 8006B084 00067C64  C0 02 88 70 */	lfs f0, lbl_804D8250(r2)
/* 8006B088 00067C68  D0 1F 06 50 */	stfs f0, 0x650(r31)
/* 8006B08C 00067C6C  48 00 00 1C */	b lbl_8006B0A8
lbl_8006B090:
/* 8006B090 00067C70  C0 3F 06 50 */	lfs f1, 0x650(r31)
/* 8006B094 00067C74  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006B098 00067C78  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8006B09C 00067C7C  41 82 00 0C */	beq lbl_8006B0A8
/* 8006B0A0 00067C80  64 60 80 00 */	oris r0, r3, 0x8000
/* 8006B0A4 00067C84  90 1F 06 5C */	stw r0, 0x65c(r31)
lbl_8006B0A8:
/* 8006B0A8 00067C88  38 60 00 00 */	li r3, 0
/* 8006B0AC 00067C8C  48 13 95 3D */	bl func_801A45E8
/* 8006B0B0 00067C90  2C 03 00 00 */	cmpwi r3, 0
/* 8006B0B4 00067C94  40 82 00 28 */	bne lbl_8006B0DC
/* 8006B0B8 00067C98  80 7F 06 5C */	lwz r3, 0x65c(r31)
/* 8006B0BC 00067C9C  54 60 06 F7 */	rlwinm. r0, r3, 0, 0x1b, 0x1b
/* 8006B0C0 00067CA0  41 82 00 1C */	beq lbl_8006B0DC
/* 8006B0C4 00067CA4  64 60 80 00 */	oris r0, r3, 0x8000
/* 8006B0C8 00067CA8  60 00 01 00 */	ori r0, r0, 0x100
/* 8006B0CC 00067CAC  90 1F 06 5C */	stw r0, 0x65c(r31)
/* 8006B0D0 00067CB0  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 8006B0D4 00067CB4  C0 03 00 14 */	lfs f0, 0x14(r3)
/* 8006B0D8 00067CB8  D0 1F 06 50 */	stfs f0, 0x650(r31)
lbl_8006B0DC:
/* 8006B0DC 00067CBC  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 8006B0E0 00067CC0  80 7F 06 5C */	lwz r3, 0x65c(r31)
/* 8006B0E4 00067CC4  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 8006B0E8 00067CC8  80 9F 06 60 */	lwz r4, 0x660(r31)
/* 8006B0EC 00067CCC  7C 80 1A 78 */	xor r0, r4, r3
/* 8006B0F0 00067CD0  7C 63 00 38 */	and r3, r3, r0
/* 8006B0F4 00067CD4  7C 84 00 38 */	and r4, r4, r0
/* 8006B0F8 00067CD8  41 82 00 20 */	beq lbl_8006B118
/* 8006B0FC 00067CDC  80 1F 06 68 */	lwz r0, 0x668(r31)
/* 8006B100 00067CE0  7C 00 1B 78 */	or r0, r0, r3
/* 8006B104 00067CE4  90 1F 06 68 */	stw r0, 0x668(r31)
/* 8006B108 00067CE8  80 1F 06 6C */	lwz r0, 0x66c(r31)
/* 8006B10C 00067CEC  7C 00 23 78 */	or r0, r0, r4
/* 8006B110 00067CF0  90 1F 06 6C */	stw r0, 0x66c(r31)
/* 8006B114 00067CF4  48 00 00 0C */	b lbl_8006B120
lbl_8006B118:
/* 8006B118 00067CF8  90 7F 06 68 */	stw r3, 0x668(r31)
/* 8006B11C 00067CFC  90 9F 06 6C */	stw r4, 0x66c(r31)
lbl_8006B120:
/* 8006B120 00067D00  88 7F 06 76 */	lbz r3, 0x676(r31)
/* 8006B124 00067D04  38 03 00 01 */	addi r0, r3, 1
/* 8006B128 00067D08  98 1F 06 76 */	stb r0, 0x676(r31)
/* 8006B12C 00067D0C  88 1F 06 76 */	lbz r0, 0x676(r31)
/* 8006B130 00067D10  28 00 00 FE */	cmplwi r0, 0xfe
/* 8006B134 00067D14  40 81 00 0C */	ble lbl_8006B140
/* 8006B138 00067D18  38 00 00 FE */	li r0, 0xfe
/* 8006B13C 00067D1C  98 1F 06 76 */	stb r0, 0x676(r31)
lbl_8006B140:
/* 8006B140 00067D20  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 8006B144 00067D24  C0 1F 06 20 */	lfs f0, 0x620(r31)
/* 8006B148 00067D28  C0 23 00 08 */	lfs f1, 8(r3)
/* 8006B14C 00067D2C  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8006B150 00067D30  4C 41 13 82 */	cror 2, 1, 2
/* 8006B154 00067D34  40 82 00 9C */	bne lbl_8006B1F0
/* 8006B158 00067D38  C0 1F 06 28 */	lfs f0, 0x628(r31)
/* 8006B15C 00067D3C  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8006B160 00067D40  4C 41 13 82 */	cror 2, 1, 2
/* 8006B164 00067D44  40 82 00 68 */	bne lbl_8006B1CC
/* 8006B168 00067D48  88 7F 06 70 */	lbz r3, 0x670(r31)
/* 8006B16C 00067D4C  38 03 00 01 */	addi r0, r3, 1
/* 8006B170 00067D50  98 1F 06 70 */	stb r0, 0x670(r31)
/* 8006B174 00067D54  88 1F 06 70 */	lbz r0, 0x670(r31)
/* 8006B178 00067D58  28 00 00 FE */	cmplwi r0, 0xfe
/* 8006B17C 00067D5C  40 81 00 0C */	ble lbl_8006B188
/* 8006B180 00067D60  38 00 00 FE */	li r0, 0xfe
/* 8006B184 00067D64  98 1F 06 70 */	stb r0, 0x670(r31)
lbl_8006B188:
/* 8006B188 00067D68  88 7F 06 73 */	lbz r3, 0x673(r31)
/* 8006B18C 00067D6C  38 03 00 01 */	addi r0, r3, 1
/* 8006B190 00067D70  98 1F 06 73 */	stb r0, 0x673(r31)
/* 8006B194 00067D74  88 1F 06 73 */	lbz r0, 0x673(r31)
/* 8006B198 00067D78  28 00 00 FE */	cmplwi r0, 0xfe
/* 8006B19C 00067D7C  40 81 00 0C */	ble lbl_8006B1A8
/* 8006B1A0 00067D80  38 00 00 FE */	li r0, 0xfe
/* 8006B1A4 00067D84  98 1F 06 73 */	stb r0, 0x673(r31)
lbl_8006B1A8:
/* 8006B1A8 00067D88  88 7F 06 79 */	lbz r3, 0x679(r31)
/* 8006B1AC 00067D8C  38 03 00 01 */	addi r0, r3, 1
/* 8006B1B0 00067D90  98 1F 06 79 */	stb r0, 0x679(r31)
/* 8006B1B4 00067D94  88 1F 06 79 */	lbz r0, 0x679(r31)
/* 8006B1B8 00067D98  28 00 00 FE */	cmplwi r0, 0xfe
/* 8006B1BC 00067D9C  40 81 00 E8 */	ble lbl_8006B2A4
/* 8006B1C0 00067DA0  38 00 00 FE */	li r0, 0xfe
/* 8006B1C4 00067DA4  98 1F 06 79 */	stb r0, 0x679(r31)
/* 8006B1C8 00067DA8  48 00 00 DC */	b lbl_8006B2A4
lbl_8006B1CC:
/* 8006B1CC 00067DAC  38 00 00 00 */	li r0, 0
/* 8006B1D0 00067DB0  98 1F 06 76 */	stb r0, 0x676(r31)
/* 8006B1D4 00067DB4  38 60 00 01 */	li r3, 1
/* 8006B1D8 00067DB8  98 1F 06 73 */	stb r0, 0x673(r31)
/* 8006B1DC 00067DBC  98 1F 06 70 */	stb r0, 0x670(r31)
/* 8006B1E0 00067DC0  88 1F 22 28 */	lbz r0, 0x2228(r31)
/* 8006B1E4 00067DC4  50 60 07 FE */	rlwimi r0, r3, 0, 0x1f, 0x1f
/* 8006B1E8 00067DC8  98 1F 22 28 */	stb r0, 0x2228(r31)
/* 8006B1EC 00067DCC  48 00 00 B8 */	b lbl_8006B2A4
lbl_8006B1F0:
/* 8006B1F0 00067DD0  FC 20 08 50 */	fneg f1, f1
/* 8006B1F4 00067DD4  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8006B1F8 00067DD8  4C 40 13 82 */	cror 2, 0, 2
/* 8006B1FC 00067DDC  40 82 00 98 */	bne lbl_8006B294
/* 8006B200 00067DE0  C0 1F 06 28 */	lfs f0, 0x628(r31)
/* 8006B204 00067DE4  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8006B208 00067DE8  4C 40 13 82 */	cror 2, 0, 2
/* 8006B20C 00067DEC  40 82 00 68 */	bne lbl_8006B274
/* 8006B210 00067DF0  88 7F 06 70 */	lbz r3, 0x670(r31)
/* 8006B214 00067DF4  38 03 00 01 */	addi r0, r3, 1
/* 8006B218 00067DF8  98 1F 06 70 */	stb r0, 0x670(r31)
/* 8006B21C 00067DFC  88 1F 06 70 */	lbz r0, 0x670(r31)
/* 8006B220 00067E00  28 00 00 FE */	cmplwi r0, 0xfe
/* 8006B224 00067E04  40 81 00 0C */	ble lbl_8006B230
/* 8006B228 00067E08  38 00 00 FE */	li r0, 0xfe
/* 8006B22C 00067E0C  98 1F 06 70 */	stb r0, 0x670(r31)
lbl_8006B230:
/* 8006B230 00067E10  88 7F 06 73 */	lbz r3, 0x673(r31)
/* 8006B234 00067E14  38 03 00 01 */	addi r0, r3, 1
/* 8006B238 00067E18  98 1F 06 73 */	stb r0, 0x673(r31)
/* 8006B23C 00067E1C  88 1F 06 73 */	lbz r0, 0x673(r31)
/* 8006B240 00067E20  28 00 00 FE */	cmplwi r0, 0xfe
/* 8006B244 00067E24  40 81 00 0C */	ble lbl_8006B250
/* 8006B248 00067E28  38 00 00 FE */	li r0, 0xfe
/* 8006B24C 00067E2C  98 1F 06 73 */	stb r0, 0x673(r31)
lbl_8006B250:
/* 8006B250 00067E30  88 7F 06 79 */	lbz r3, 0x679(r31)
/* 8006B254 00067E34  38 03 00 01 */	addi r0, r3, 1
/* 8006B258 00067E38  98 1F 06 79 */	stb r0, 0x679(r31)
/* 8006B25C 00067E3C  88 1F 06 79 */	lbz r0, 0x679(r31)
/* 8006B260 00067E40  28 00 00 FE */	cmplwi r0, 0xfe
/* 8006B264 00067E44  40 81 00 40 */	ble lbl_8006B2A4
/* 8006B268 00067E48  38 00 00 FE */	li r0, 0xfe
/* 8006B26C 00067E4C  98 1F 06 79 */	stb r0, 0x679(r31)
/* 8006B270 00067E50  48 00 00 34 */	b lbl_8006B2A4
lbl_8006B274:
/* 8006B274 00067E54  38 60 00 00 */	li r3, 0
/* 8006B278 00067E58  98 7F 06 76 */	stb r3, 0x676(r31)
/* 8006B27C 00067E5C  98 7F 06 73 */	stb r3, 0x673(r31)
/* 8006B280 00067E60  98 7F 06 70 */	stb r3, 0x670(r31)
/* 8006B284 00067E64  88 1F 22 28 */	lbz r0, 0x2228(r31)
/* 8006B288 00067E68  50 60 07 FE */	rlwimi r0, r3, 0, 0x1f, 0x1f
/* 8006B28C 00067E6C  98 1F 22 28 */	stb r0, 0x2228(r31)
/* 8006B290 00067E70  48 00 00 14 */	b lbl_8006B2A4
lbl_8006B294:
/* 8006B294 00067E74  38 00 00 FE */	li r0, 0xfe
/* 8006B298 00067E78  98 1F 06 79 */	stb r0, 0x679(r31)
/* 8006B29C 00067E7C  98 1F 06 73 */	stb r0, 0x673(r31)
/* 8006B2A0 00067E80  98 1F 06 70 */	stb r0, 0x670(r31)
lbl_8006B2A4:
/* 8006B2A4 00067E84  88 7F 06 77 */	lbz r3, 0x677(r31)
/* 8006B2A8 00067E88  38 03 00 01 */	addi r0, r3, 1
/* 8006B2AC 00067E8C  98 1F 06 77 */	stb r0, 0x677(r31)
/* 8006B2B0 00067E90  88 1F 06 77 */	lbz r0, 0x677(r31)
/* 8006B2B4 00067E94  28 00 00 FE */	cmplwi r0, 0xfe
/* 8006B2B8 00067E98  40 81 00 0C */	ble lbl_8006B2C4
/* 8006B2BC 00067E9C  38 00 00 FE */	li r0, 0xfe
/* 8006B2C0 00067EA0  98 1F 06 77 */	stb r0, 0x677(r31)
lbl_8006B2C4:
/* 8006B2C4 00067EA4  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 8006B2C8 00067EA8  C0 1F 06 24 */	lfs f0, 0x624(r31)
/* 8006B2CC 00067EAC  C0 23 00 0C */	lfs f1, 0xc(r3)
/* 8006B2D0 00067EB0  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8006B2D4 00067EB4  4C 41 13 82 */	cror 2, 1, 2
/* 8006B2D8 00067EB8  40 82 00 98 */	bne lbl_8006B370
/* 8006B2DC 00067EBC  C0 1F 06 2C */	lfs f0, 0x62c(r31)
/* 8006B2E0 00067EC0  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8006B2E4 00067EC4  4C 41 13 82 */	cror 2, 1, 2
/* 8006B2E8 00067EC8  40 82 00 68 */	bne lbl_8006B350
/* 8006B2EC 00067ECC  88 7F 06 71 */	lbz r3, 0x671(r31)
/* 8006B2F0 00067ED0  38 03 00 01 */	addi r0, r3, 1
/* 8006B2F4 00067ED4  98 1F 06 71 */	stb r0, 0x671(r31)
/* 8006B2F8 00067ED8  88 1F 06 71 */	lbz r0, 0x671(r31)
/* 8006B2FC 00067EDC  28 00 00 FE */	cmplwi r0, 0xfe
/* 8006B300 00067EE0  40 81 00 0C */	ble lbl_8006B30C
/* 8006B304 00067EE4  38 00 00 FE */	li r0, 0xfe
/* 8006B308 00067EE8  98 1F 06 71 */	stb r0, 0x671(r31)
lbl_8006B30C:
/* 8006B30C 00067EEC  88 7F 06 74 */	lbz r3, 0x674(r31)
/* 8006B310 00067EF0  38 03 00 01 */	addi r0, r3, 1
/* 8006B314 00067EF4  98 1F 06 74 */	stb r0, 0x674(r31)
/* 8006B318 00067EF8  88 1F 06 74 */	lbz r0, 0x674(r31)
/* 8006B31C 00067EFC  28 00 00 FE */	cmplwi r0, 0xfe
/* 8006B320 00067F00  40 81 00 0C */	ble lbl_8006B32C
/* 8006B324 00067F04  38 00 00 FE */	li r0, 0xfe
/* 8006B328 00067F08  98 1F 06 74 */	stb r0, 0x674(r31)
lbl_8006B32C:
/* 8006B32C 00067F0C  88 7F 06 7A */	lbz r3, 0x67a(r31)
/* 8006B330 00067F10  38 03 00 01 */	addi r0, r3, 1
/* 8006B334 00067F14  98 1F 06 7A */	stb r0, 0x67a(r31)
/* 8006B338 00067F18  88 1F 06 7A */	lbz r0, 0x67a(r31)
/* 8006B33C 00067F1C  28 00 00 FE */	cmplwi r0, 0xfe
/* 8006B340 00067F20  40 81 00 E8 */	ble lbl_8006B428
/* 8006B344 00067F24  38 00 00 FE */	li r0, 0xfe
/* 8006B348 00067F28  98 1F 06 7A */	stb r0, 0x67a(r31)
/* 8006B34C 00067F2C  48 00 00 DC */	b lbl_8006B428
lbl_8006B350:
/* 8006B350 00067F30  38 60 00 00 */	li r3, 0
/* 8006B354 00067F34  98 7F 06 77 */	stb r3, 0x677(r31)
/* 8006B358 00067F38  98 7F 06 74 */	stb r3, 0x674(r31)
/* 8006B35C 00067F3C  98 7F 06 71 */	stb r3, 0x671(r31)
/* 8006B360 00067F40  88 1F 22 29 */	lbz r0, 0x2229(r31)
/* 8006B364 00067F44  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 8006B368 00067F48  98 1F 22 29 */	stb r0, 0x2229(r31)
/* 8006B36C 00067F4C  48 00 00 BC */	b lbl_8006B428
lbl_8006B370:
/* 8006B370 00067F50  FC 20 08 50 */	fneg f1, f1
/* 8006B374 00067F54  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8006B378 00067F58  4C 40 13 82 */	cror 2, 0, 2
/* 8006B37C 00067F5C  40 82 00 9C */	bne lbl_8006B418
/* 8006B380 00067F60  C0 1F 06 2C */	lfs f0, 0x62c(r31)
/* 8006B384 00067F64  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8006B388 00067F68  4C 40 13 82 */	cror 2, 0, 2
/* 8006B38C 00067F6C  40 82 00 68 */	bne lbl_8006B3F4
/* 8006B390 00067F70  88 7F 06 71 */	lbz r3, 0x671(r31)
/* 8006B394 00067F74  38 03 00 01 */	addi r0, r3, 1
/* 8006B398 00067F78  98 1F 06 71 */	stb r0, 0x671(r31)
/* 8006B39C 00067F7C  88 1F 06 71 */	lbz r0, 0x671(r31)
/* 8006B3A0 00067F80  28 00 00 FE */	cmplwi r0, 0xfe
/* 8006B3A4 00067F84  40 81 00 0C */	ble lbl_8006B3B0
/* 8006B3A8 00067F88  38 00 00 FE */	li r0, 0xfe
/* 8006B3AC 00067F8C  98 1F 06 71 */	stb r0, 0x671(r31)
lbl_8006B3B0:
/* 8006B3B0 00067F90  88 7F 06 74 */	lbz r3, 0x674(r31)
/* 8006B3B4 00067F94  38 03 00 01 */	addi r0, r3, 1
/* 8006B3B8 00067F98  98 1F 06 74 */	stb r0, 0x674(r31)
/* 8006B3BC 00067F9C  88 1F 06 74 */	lbz r0, 0x674(r31)
/* 8006B3C0 00067FA0  28 00 00 FE */	cmplwi r0, 0xfe
/* 8006B3C4 00067FA4  40 81 00 0C */	ble lbl_8006B3D0
/* 8006B3C8 00067FA8  38 00 00 FE */	li r0, 0xfe
/* 8006B3CC 00067FAC  98 1F 06 74 */	stb r0, 0x674(r31)
lbl_8006B3D0:
/* 8006B3D0 00067FB0  88 7F 06 7A */	lbz r3, 0x67a(r31)
/* 8006B3D4 00067FB4  38 03 00 01 */	addi r0, r3, 1
/* 8006B3D8 00067FB8  98 1F 06 7A */	stb r0, 0x67a(r31)
/* 8006B3DC 00067FBC  88 1F 06 7A */	lbz r0, 0x67a(r31)
/* 8006B3E0 00067FC0  28 00 00 FE */	cmplwi r0, 0xfe
/* 8006B3E4 00067FC4  40 81 00 44 */	ble lbl_8006B428
/* 8006B3E8 00067FC8  38 00 00 FE */	li r0, 0xfe
/* 8006B3EC 00067FCC  98 1F 06 7A */	stb r0, 0x67a(r31)
/* 8006B3F0 00067FD0  48 00 00 38 */	b lbl_8006B428
lbl_8006B3F4:
/* 8006B3F4 00067FD4  38 00 00 00 */	li r0, 0
/* 8006B3F8 00067FD8  98 1F 06 77 */	stb r0, 0x677(r31)
/* 8006B3FC 00067FDC  38 60 00 01 */	li r3, 1
/* 8006B400 00067FE0  98 1F 06 74 */	stb r0, 0x674(r31)
/* 8006B404 00067FE4  98 1F 06 71 */	stb r0, 0x671(r31)
/* 8006B408 00067FE8  88 1F 22 29 */	lbz r0, 0x2229(r31)
/* 8006B40C 00067FEC  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 8006B410 00067FF0  98 1F 22 29 */	stb r0, 0x2229(r31)
/* 8006B414 00067FF4  48 00 00 14 */	b lbl_8006B428
lbl_8006B418:
/* 8006B418 00067FF8  38 00 00 FE */	li r0, 0xfe
/* 8006B41C 00067FFC  98 1F 06 7A */	stb r0, 0x67a(r31)
/* 8006B420 00068000  98 1F 06 74 */	stb r0, 0x674(r31)
/* 8006B424 00068004  98 1F 06 71 */	stb r0, 0x671(r31)
lbl_8006B428:
/* 8006B428 00068008  C0 A2 88 74 */	lfs f5, lbl_804D8254(r2)
/* 8006B42C 0006800C  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 8006B430 00068010  FC C0 28 90 */	fmr f6, f5
/* 8006B434 00068014  C0 3F 06 28 */	lfs f1, 0x628(r31)
/* 8006B438 00068018  C0 5F 06 2C */	lfs f2, 0x62c(r31)
/* 8006B43C 0006801C  C0 7F 06 20 */	lfs f3, 0x620(r31)
/* 8006B440 00068020  C0 9F 06 24 */	lfs f4, 0x624(r31)
/* 8006B444 00068024  C0 E3 00 08 */	lfs f7, 8(r3)
/* 8006B448 00068028  4B FA 1D 01 */	bl func_8000D148
/* 8006B44C 0006802C  2C 03 00 00 */	cmpwi r3, 0
/* 8006B450 00068030  41 82 00 10 */	beq lbl_8006B460
/* 8006B454 00068034  38 00 00 00 */	li r0, 0
/* 8006B458 00068038  98 1F 06 7A */	stb r0, 0x67a(r31)
/* 8006B45C 0006803C  98 1F 06 79 */	stb r0, 0x679(r31)
lbl_8006B460:
/* 8006B460 00068040  88 7F 06 78 */	lbz r3, 0x678(r31)
/* 8006B464 00068044  38 03 00 01 */	addi r0, r3, 1
/* 8006B468 00068048  98 1F 06 78 */	stb r0, 0x678(r31)
/* 8006B46C 0006804C  88 1F 06 78 */	lbz r0, 0x678(r31)
/* 8006B470 00068050  28 00 00 FE */	cmplwi r0, 0xfe
/* 8006B474 00068054  40 81 00 0C */	ble lbl_8006B480
/* 8006B478 00068058  38 00 00 FE */	li r0, 0xfe
/* 8006B47C 0006805C  98 1F 06 78 */	stb r0, 0x678(r31)
lbl_8006B480:
/* 8006B480 00068060  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 8006B484 00068064  C0 1F 06 50 */	lfs f0, 0x650(r31)
/* 8006B488 00068068  C0 23 00 18 */	lfs f1, 0x18(r3)
/* 8006B48C 0006806C  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8006B490 00068070  4C 41 13 82 */	cror 2, 1, 2
/* 8006B494 00068074  40 82 00 90 */	bne lbl_8006B524
/* 8006B498 00068078  C0 1F 06 54 */	lfs f0, 0x654(r31)
/* 8006B49C 0006807C  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8006B4A0 00068080  4C 41 13 82 */	cror 2, 1, 2
/* 8006B4A4 00068084  40 82 00 68 */	bne lbl_8006B50C
/* 8006B4A8 00068088  88 7F 06 72 */	lbz r3, 0x672(r31)
/* 8006B4AC 0006808C  38 03 00 01 */	addi r0, r3, 1
/* 8006B4B0 00068090  98 1F 06 72 */	stb r0, 0x672(r31)
/* 8006B4B4 00068094  88 1F 06 72 */	lbz r0, 0x672(r31)
/* 8006B4B8 00068098  28 00 00 FE */	cmplwi r0, 0xfe
/* 8006B4BC 0006809C  40 81 00 0C */	ble lbl_8006B4C8
/* 8006B4C0 000680A0  38 00 00 FE */	li r0, 0xfe
/* 8006B4C4 000680A4  98 1F 06 72 */	stb r0, 0x672(r31)
lbl_8006B4C8:
/* 8006B4C8 000680A8  88 7F 06 75 */	lbz r3, 0x675(r31)
/* 8006B4CC 000680AC  38 03 00 01 */	addi r0, r3, 1
/* 8006B4D0 000680B0  98 1F 06 75 */	stb r0, 0x675(r31)
/* 8006B4D4 000680B4  88 1F 06 75 */	lbz r0, 0x675(r31)
/* 8006B4D8 000680B8  28 00 00 FE */	cmplwi r0, 0xfe
/* 8006B4DC 000680BC  40 81 00 0C */	ble lbl_8006B4E8
/* 8006B4E0 000680C0  38 00 00 FE */	li r0, 0xfe
/* 8006B4E4 000680C4  98 1F 06 75 */	stb r0, 0x675(r31)
lbl_8006B4E8:
/* 8006B4E8 000680C8  88 7F 06 7B */	lbz r3, 0x67b(r31)
/* 8006B4EC 000680CC  38 03 00 01 */	addi r0, r3, 1
/* 8006B4F0 000680D0  98 1F 06 7B */	stb r0, 0x67b(r31)
/* 8006B4F4 000680D4  88 1F 06 7B */	lbz r0, 0x67b(r31)
/* 8006B4F8 000680D8  28 00 00 FE */	cmplwi r0, 0xfe
/* 8006B4FC 000680DC  40 81 00 38 */	ble lbl_8006B534
/* 8006B500 000680E0  38 00 00 FE */	li r0, 0xfe
/* 8006B504 000680E4  98 1F 06 7B */	stb r0, 0x67b(r31)
/* 8006B508 000680E8  48 00 00 2C */	b lbl_8006B534
lbl_8006B50C:
/* 8006B50C 000680EC  38 00 00 00 */	li r0, 0
/* 8006B510 000680F0  98 1F 06 7B */	stb r0, 0x67b(r31)
/* 8006B514 000680F4  98 1F 06 78 */	stb r0, 0x678(r31)
/* 8006B518 000680F8  98 1F 06 75 */	stb r0, 0x675(r31)
/* 8006B51C 000680FC  98 1F 06 72 */	stb r0, 0x672(r31)
/* 8006B520 00068100  48 00 00 14 */	b lbl_8006B534
lbl_8006B524:
/* 8006B524 00068104  38 00 00 FE */	li r0, 0xfe
/* 8006B528 00068108  98 1F 06 7B */	stb r0, 0x67b(r31)
/* 8006B52C 0006810C  98 1F 06 75 */	stb r0, 0x675(r31)
/* 8006B530 00068110  98 1F 06 72 */	stb r0, 0x672(r31)
lbl_8006B534:
/* 8006B534 00068114  80 1F 06 68 */	lwz r0, 0x668(r31)
/* 8006B538 00068118  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 8006B53C 0006811C  41 82 00 18 */	beq lbl_8006B554
/* 8006B540 00068120  88 7F 06 7C */	lbz r3, 0x67c(r31)
/* 8006B544 00068124  38 00 00 00 */	li r0, 0
/* 8006B548 00068128  98 7F 06 83 */	stb r3, 0x683(r31)
/* 8006B54C 0006812C  98 1F 06 7C */	stb r0, 0x67c(r31)
/* 8006B550 00068130  48 00 00 18 */	b lbl_8006B568
lbl_8006B554:
/* 8006B554 00068134  88 7F 06 7C */	lbz r3, 0x67c(r31)
/* 8006B558 00068138  28 03 00 FF */	cmplwi r3, 0xff
/* 8006B55C 0006813C  40 80 00 0C */	bge lbl_8006B568
/* 8006B560 00068140  38 03 00 01 */	addi r0, r3, 1
/* 8006B564 00068144  98 1F 06 7C */	stb r0, 0x67c(r31)
lbl_8006B568:
/* 8006B568 00068148  80 1F 06 68 */	lwz r0, 0x668(r31)
/* 8006B56C 0006814C  54 00 05 AD */	rlwinm. r0, r0, 0, 0x16, 0x16
/* 8006B570 00068150  41 82 00 10 */	beq lbl_8006B580
/* 8006B574 00068154  38 00 00 00 */	li r0, 0
/* 8006B578 00068158  98 1F 06 7D */	stb r0, 0x67d(r31)
/* 8006B57C 0006815C  48 00 00 18 */	b lbl_8006B594
lbl_8006B580:
/* 8006B580 00068160  88 7F 06 7D */	lbz r3, 0x67d(r31)
/* 8006B584 00068164  28 03 00 FF */	cmplwi r3, 0xff
/* 8006B588 00068168  40 80 00 0C */	bge lbl_8006B594
/* 8006B58C 0006816C  38 03 00 01 */	addi r0, r3, 1
/* 8006B590 00068170  98 1F 06 7D */	stb r0, 0x67d(r31)
lbl_8006B594:
/* 8006B594 00068174  80 1F 06 68 */	lwz r0, 0x668(r31)
/* 8006B598 00068178  54 00 05 2B */	rlwinm. r0, r0, 0, 0x14, 0x15
/* 8006B59C 0006817C  41 82 00 10 */	beq lbl_8006B5AC
/* 8006B5A0 00068180  38 00 00 00 */	li r0, 0
/* 8006B5A4 00068184  98 1F 06 7E */	stb r0, 0x67e(r31)
/* 8006B5A8 00068188  48 00 00 18 */	b lbl_8006B5C0
lbl_8006B5AC:
/* 8006B5AC 0006818C  88 7F 06 7E */	lbz r3, 0x67e(r31)
/* 8006B5B0 00068190  28 03 00 FF */	cmplwi r3, 0xff
/* 8006B5B4 00068194  40 80 00 0C */	bge lbl_8006B5C0
/* 8006B5B8 00068198  38 03 00 01 */	addi r0, r3, 1
/* 8006B5BC 0006819C  98 1F 06 7E */	stb r0, 0x67e(r31)
lbl_8006B5C0:
/* 8006B5C0 000681A0  80 1F 06 68 */	lwz r0, 0x668(r31)
/* 8006B5C4 000681A4  54 00 07 39 */	rlwinm. r0, r0, 0, 0x1c, 0x1c
/* 8006B5C8 000681A8  41 82 00 10 */	beq lbl_8006B5D8
/* 8006B5CC 000681AC  38 00 00 00 */	li r0, 0
/* 8006B5D0 000681B0  98 1F 06 81 */	stb r0, 0x681(r31)
/* 8006B5D4 000681B4  48 00 00 18 */	b lbl_8006B5EC
lbl_8006B5D8:
/* 8006B5D8 000681B8  88 7F 06 81 */	lbz r3, 0x681(r31)
/* 8006B5DC 000681BC  28 03 00 FF */	cmplwi r3, 0xff
/* 8006B5E0 000681C0  40 80 00 0C */	bge lbl_8006B5EC
/* 8006B5E4 000681C4  38 03 00 01 */	addi r0, r3, 1
/* 8006B5E8 000681C8  98 1F 06 81 */	stb r0, 0x681(r31)
lbl_8006B5EC:
/* 8006B5EC 000681CC  80 1F 06 68 */	lwz r0, 0x668(r31)
/* 8006B5F0 000681D0  54 00 07 7B */	rlwinm. r0, r0, 0, 0x1d, 0x1d
/* 8006B5F4 000681D4  41 82 00 10 */	beq lbl_8006B604
/* 8006B5F8 000681D8  38 00 00 00 */	li r0, 0
/* 8006B5FC 000681DC  98 1F 06 82 */	stb r0, 0x682(r31)
/* 8006B600 000681E0  48 00 00 18 */	b lbl_8006B618
lbl_8006B604:
/* 8006B604 000681E4  88 7F 06 82 */	lbz r3, 0x682(r31)
/* 8006B608 000681E8  28 03 00 FF */	cmplwi r3, 0xff
/* 8006B60C 000681EC  40 80 00 0C */	bge lbl_8006B618
/* 8006B610 000681F0  38 03 00 01 */	addi r0, r3, 1
/* 8006B614 000681F4  98 1F 06 82 */	stb r0, 0x682(r31)
lbl_8006B618:
/* 8006B618 000681F8  80 1F 06 68 */	lwz r0, 0x668(r31)
/* 8006B61C 000681FC  54 00 00 01 */	rlwinm. r0, r0, 0, 0, 0
/* 8006B620 00068200  41 82 00 10 */	beq lbl_8006B630
/* 8006B624 00068204  38 00 00 00 */	li r0, 0
/* 8006B628 00068208  98 1F 06 7F */	stb r0, 0x67f(r31)
/* 8006B62C 0006820C  48 00 00 18 */	b lbl_8006B644
lbl_8006B630:
/* 8006B630 00068210  88 7F 06 7F */	lbz r3, 0x67f(r31)
/* 8006B634 00068214  28 03 00 FF */	cmplwi r3, 0xff
/* 8006B638 00068218  40 80 00 0C */	bge lbl_8006B644
/* 8006B63C 0006821C  38 03 00 01 */	addi r0, r3, 1
/* 8006B640 00068220  98 1F 06 7F */	stb r0, 0x67f(r31)
lbl_8006B644:
/* 8006B644 00068224  80 1F 06 68 */	lwz r0, 0x668(r31)
/* 8006B648 00068228  54 00 06 75 */	rlwinm. r0, r0, 0, 0x19, 0x1a
/* 8006B64C 0006822C  41 82 00 18 */	beq lbl_8006B664
/* 8006B650 00068230  88 7F 06 80 */	lbz r3, 0x680(r31)
/* 8006B654 00068234  38 00 00 00 */	li r0, 0
/* 8006B658 00068238  98 7F 06 84 */	stb r3, 0x684(r31)
/* 8006B65C 0006823C  98 1F 06 80 */	stb r0, 0x680(r31)
/* 8006B660 00068240  48 00 00 18 */	b lbl_8006B678
lbl_8006B664:
/* 8006B664 00068244  88 7F 06 80 */	lbz r3, 0x680(r31)
/* 8006B668 00068248  28 03 00 FF */	cmplwi r3, 0xff
/* 8006B66C 0006824C  40 80 00 0C */	bge lbl_8006B678
/* 8006B670 00068250  38 03 00 01 */	addi r0, r3, 1
/* 8006B674 00068254  98 1F 06 80 */	stb r0, 0x680(r31)
lbl_8006B678:
/* 8006B678 00068258  88 1F 22 1D */	lbz r0, 0x221d(r31)
/* 8006B67C 0006825C  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 8006B680 00068260  40 82 00 20 */	bne lbl_8006B6A0
/* 8006B684 00068264  88 1F 22 24 */	lbz r0, 0x2224(r31)
/* 8006B688 00068268  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8006B68C 0006826C  40 82 00 14 */	bne lbl_8006B6A0
/* 8006B690 00068270  38 60 00 02 */	li r3, 2
/* 8006B694 00068274  48 13 8F 55 */	bl func_801A45E8
/* 8006B698 00068278  2C 03 00 00 */	cmpwi r3, 0
/* 8006B69C 0006827C  41 82 00 FC */	beq lbl_8006B798
lbl_8006B6A0:
/* 8006B6A0 00068280  C0 1F 06 20 */	lfs f0, 0x620(r31)
/* 8006B6A4 00068284  38 A0 00 00 */	li r5, 0
/* 8006B6A8 00068288  38 60 00 FE */	li r3, 0xfe
/* 8006B6AC 0006828C  D0 1F 06 30 */	stfs f0, 0x630(r31)
/* 8006B6B0 00068290  38 00 00 FF */	li r0, 0xff
/* 8006B6B4 00068294  C0 1F 06 24 */	lfs f0, 0x624(r31)
/* 8006B6B8 00068298  D0 1F 06 34 */	stfs f0, 0x634(r31)
/* 8006B6BC 0006829C  C0 1F 06 38 */	lfs f0, 0x638(r31)
/* 8006B6C0 000682A0  D0 1F 06 48 */	stfs f0, 0x648(r31)
/* 8006B6C4 000682A4  C0 1F 06 3C */	lfs f0, 0x63c(r31)
/* 8006B6C8 000682A8  D0 1F 06 4C */	stfs f0, 0x64c(r31)
/* 8006B6CC 000682AC  C0 1F 06 50 */	lfs f0, 0x650(r31)
/* 8006B6D0 000682B0  D0 1F 06 58 */	stfs f0, 0x658(r31)
/* 8006B6D4 000682B4  80 9F 06 5C */	lwz r4, 0x65c(r31)
/* 8006B6D8 000682B8  90 9F 06 64 */	stw r4, 0x664(r31)
/* 8006B6DC 000682BC  88 9F 22 1D */	lbz r4, 0x221d(r31)
/* 8006B6E0 000682C0  50 A4 26 F6 */	rlwimi r4, r5, 4, 0x1b, 0x1b
/* 8006B6E4 000682C4  98 9F 22 1D */	stb r4, 0x221d(r31)
/* 8006B6E8 000682C8  80 9E 00 2C */	lwz r4, 0x2c(r30)
/* 8006B6EC 000682CC  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006B6F0 000682D0  D0 04 06 2C */	stfs f0, 0x62c(r4)
/* 8006B6F4 000682D4  D0 04 06 28 */	stfs f0, 0x628(r4)
/* 8006B6F8 000682D8  D0 04 06 24 */	stfs f0, 0x624(r4)
/* 8006B6FC 000682DC  D0 04 06 20 */	stfs f0, 0x620(r4)
/* 8006B700 000682E0  D0 04 06 44 */	stfs f0, 0x644(r4)
/* 8006B704 000682E4  D0 04 06 40 */	stfs f0, 0x640(r4)
/* 8006B708 000682E8  D0 04 06 3C */	stfs f0, 0x63c(r4)
/* 8006B70C 000682EC  D0 04 06 38 */	stfs f0, 0x638(r4)
/* 8006B710 000682F0  D0 04 06 54 */	stfs f0, 0x654(r4)
/* 8006B714 000682F4  D0 04 06 50 */	stfs f0, 0x650(r4)
/* 8006B718 000682F8  90 A4 06 60 */	stw r5, 0x660(r4)
/* 8006B71C 000682FC  90 A4 06 6C */	stw r5, 0x66c(r4)
/* 8006B720 00068300  90 A4 06 68 */	stw r5, 0x668(r4)
/* 8006B724 00068304  90 A4 06 5C */	stw r5, 0x65c(r4)
/* 8006B728 00068308  98 64 06 72 */	stb r3, 0x672(r4)
/* 8006B72C 0006830C  98 64 06 71 */	stb r3, 0x671(r4)
/* 8006B730 00068310  98 64 06 70 */	stb r3, 0x670(r4)
/* 8006B734 00068314  98 64 06 75 */	stb r3, 0x675(r4)
/* 8006B738 00068318  98 64 06 74 */	stb r3, 0x674(r4)
/* 8006B73C 0006831C  98 64 06 73 */	stb r3, 0x673(r4)
/* 8006B740 00068320  98 64 06 78 */	stb r3, 0x678(r4)
/* 8006B744 00068324  98 64 06 77 */	stb r3, 0x677(r4)
/* 8006B748 00068328  98 64 06 76 */	stb r3, 0x676(r4)
/* 8006B74C 0006832C  98 64 06 7B */	stb r3, 0x67b(r4)
/* 8006B750 00068330  98 64 06 7A */	stb r3, 0x67a(r4)
/* 8006B754 00068334  98 64 06 79 */	stb r3, 0x679(r4)
/* 8006B758 00068338  98 04 06 8B */	stb r0, 0x68b(r4)
/* 8006B75C 0006833C  98 04 06 8A */	stb r0, 0x68a(r4)
/* 8006B760 00068340  98 04 06 89 */	stb r0, 0x689(r4)
/* 8006B764 00068344  98 04 06 88 */	stb r0, 0x688(r4)
/* 8006B768 00068348  98 04 06 87 */	stb r0, 0x687(r4)
/* 8006B76C 0006834C  98 04 06 86 */	stb r0, 0x686(r4)
/* 8006B770 00068350  98 04 06 85 */	stb r0, 0x685(r4)
/* 8006B774 00068354  98 04 06 84 */	stb r0, 0x684(r4)
/* 8006B778 00068358  98 04 06 83 */	stb r0, 0x683(r4)
/* 8006B77C 0006835C  98 04 06 80 */	stb r0, 0x680(r4)
/* 8006B780 00068360  98 04 06 7F */	stb r0, 0x67f(r4)
/* 8006B784 00068364  98 04 06 82 */	stb r0, 0x682(r4)
/* 8006B788 00068368  98 04 06 81 */	stb r0, 0x681(r4)
/* 8006B78C 0006836C  98 04 06 7E */	stb r0, 0x67e(r4)
/* 8006B790 00068370  98 04 06 7D */	stb r0, 0x67d(r4)
/* 8006B794 00068374  98 04 06 7C */	stb r0, 0x67c(r4)
lbl_8006B798:
/* 8006B798 00068378  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 8006B79C 0006837C  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 8006B7A0 00068380  40 82 00 6C */	bne lbl_8006B80C
/* 8006B7A4 00068384  80 1F 19 80 */	lwz r0, 0x1980(r31)
/* 8006B7A8 00068388  28 00 00 00 */	cmplwi r0, 0
/* 8006B7AC 0006838C  41 82 00 30 */	beq lbl_8006B7DC
/* 8006B7B0 00068390  80 8D AE B4 */	lwz r4, lbl_804D6554(r13)
/* 8006B7B4 00068394  3C 00 43 30 */	lis r0, 0x4330
/* 8006B7B8 00068398  C8 22 88 80 */	lfd f1, lbl_804D8260(r2)
/* 8006B7BC 0006839C  7F E3 FB 78 */	mr r3, r31
/* 8006B7C0 000683A0  80 84 06 FC */	lwz r4, 0x6fc(r4)
/* 8006B7C4 000683A4  6C 84 80 00 */	xoris r4, r4, 0x8000
/* 8006B7C8 000683A8  90 81 00 5C */	stw r4, 0x5c(r1)
/* 8006B7CC 000683AC  90 01 00 58 */	stw r0, 0x58(r1)
/* 8006B7D0 000683B0  C8 01 00 58 */	lfd f0, 0x58(r1)
/* 8006B7D4 000683B4  EC 20 08 28 */	fsubs f1, f0, f1
/* 8006B7D8 000683B8  48 01 48 01 */	bl func_8007FFD8
lbl_8006B7DC:
/* 8006B7DC 000683BC  7F C3 F3 78 */	mr r3, r30
/* 8006B7E0 000683C0  48 07 38 F1 */	bl func_800DF0D0
/* 8006B7E4 000683C4  7F C3 F3 78 */	mr r3, r30
/* 8006B7E8 000683C8  48 01 4B 35 */	bl func_8008031C
/* 8006B7EC 000683CC  7F C3 F3 78 */	mr r3, r30
/* 8006B7F0 000683D0  4B FF F3 FD */	bl func_8006ABEC
/* 8006B7F4 000683D4  81 9F 21 9C */	lwz r12, 0x219c(r31)
/* 8006B7F8 000683D8  28 0C 00 00 */	cmplwi r12, 0
/* 8006B7FC 000683DC  41 82 00 10 */	beq lbl_8006B80C
/* 8006B800 000683E0  7D 88 03 A6 */	mtlr r12
/* 8006B804 000683E4  38 7E 00 00 */	addi r3, r30, 0
/* 8006B808 000683E8  4E 80 00 21 */	blrl 
lbl_8006B80C:
/* 8006B80C 000683EC  80 01 00 7C */	lwz r0, 0x7c(r1)
/* 8006B810 000683F0  CB E1 00 70 */	lfd f31, 0x70(r1)
/* 8006B814 000683F4  83 E1 00 6C */	lwz r31, 0x6c(r1)
/* 8006B818 000683F8  83 C1 00 68 */	lwz r30, 0x68(r1)
/* 8006B81C 000683FC  83 A1 00 64 */	lwz r29, 0x64(r1)
/* 8006B820 00068400  38 21 00 78 */	addi r1, r1, 0x78
/* 8006B824 00068404  7C 08 03 A6 */	mtlr r0
/* 8006B828 00068408  4E 80 00 20 */	blr  
}


//// https://decomp.me/scratch/kNXEu
void Fighter_procUpdate(HSD_GObj* pPlayerEntityStruct, s32 dummy) {
    //@1c
    Fighter* pCharData = pPlayerEntityStruct->user_data;
    //float atkShieldKB_len; // 0x1c
    //float kb_vel_len; // 0x20
    Vec3 windOffset; // 0x4c
    //@20
    if (pCharData->x221F_flag.bits.b3) // if pCharData->byte_at_0x221F & 0b10000
		return;
    
    //@30
    if (!pCharData->x2219_flag.bits.b5)
    {
        Vec3* p_kb_vel;
        Vec3* pAtkShieldKB;
        float kb_vel_x, atkShieldKB_X;
        Vec3 selfVel; // 0x40

        //@3c
        if (pCharData->x2064_ledgeCooldown != 0)
			pCharData->x2064_ledgeCooldown -= 1;
        if (pCharData->x2108 != 0)
			pCharData->x2108 -= 1;
        
        //@64
        func_800C0A98(pPlayerEntityStruct);

        //@6c
		if (pCharData->cb.x21A4_callback_Phys != 0)
			pCharData->cb.x21A4_callback_Phys(pPlayerEntityStruct); // AS_Physics_Func callback @0x21A4
        //@84
        p_kb_vel = &pCharData->x8c_kb_vel;
		if ((kb_vel_x = p_kb_vel->x) != 0 || p_kb_vel->y != 0)
        {
            //@a4
			if (pCharData->xE0_ground_or_air == 1) // # 0=grounded, 1=airborne.
            {
                //@b0
				float kb_vel_x = p_kb_vel->x;
				float kb_vel_y = p_kb_vel->y;
				// I was not able to trigger this case in normal gameplay yet. spreadsheet comment: facing angle? hi-pitch, lo-pitch, noCliffCatch
				if (pCharData->x2228_flag.bits.b2) // equivalent to x2228 & 0b0010_0000
                {
                	p_kb_vel->x = func_8007CD6C(p_kb_vel->x, func_8007CDA4(pCharData));
					p_kb_vel->y = func_8007CD6C(p_kb_vel->y, func_8007CDF8(pCharData));
                }
                else //@f8
                {
                    
                    float kb_angle = func_80022C30(kb_vel_y, kb_vel_x);
                    //@104
					float kb_vel_len = sqrtf(kb_vel_x * kb_vel_x + kb_vel_y * kb_vel_y);
					
					//@168 decrement knockback velocity magnitude
                    if (kb_vel_len < p_ftCommonData->x204_knockbackFrameDecay) // kb_frameDecay offset is 0x204, value always 0.051?
                    {
						p_kb_vel->y = 0; // 0.0f@toc-0x778C
                        p_kb_vel->x = 0;
                    }
					else
                    {
                        // What we want to achieve is this:
                        // 	*p_kb_vel *= (kb_vel_len - kb_frameDecay)/kb_vel_len
                        // But this is implemented very inefficiently like this:
                        // (Also this doesn't work properly for 180° angles)
						p_kb_vel->x -= p_ftCommonData->x204_knockbackFrameDecay * cosf(kb_angle);//@188
                        p_kb_vel->y -= p_ftCommonData->x204_knockbackFrameDecay * sinf(kb_angle);//@1a8
                    }
                }
                //@1c0
				pCharData->xF0_ground_kb_vel = 0; // 0.0f@toc-0x778C
            }
			else
            {
                // @1cc
                //float effectiveFriction;
                Vec3* pNormal = &pCharData->x6F0_collData.x154_groundNormal; // ground_normal offset inside pCharData is 0x844, surface normal points out of the surface. 
                struct attr* pAttr;
                // This is probably triggered when transitioning from the air to the ground, for example with ASDI down after getting hit.
				if (pCharData->xF0_ground_kb_vel == 0)
					pCharData->xF0_ground_kb_vel = kb_vel_x;
                //@1e4
                pAttr = &pCharData->x110_attr; // attr has offset 0x110
                func_8007CCA0(pCharData,
                    /*effective friction - ground multiplier is usually 1. last factor was 1 when I looked*/
                    func_80084A40(pCharData) * pAttr->x128_GroundFriction * p_ftCommonData->x200);
				// @210 set knockback velocity to ground_kb_vel * surfaceTangent
                p_kb_vel->x =  pNormal->y * pCharData->xF0_ground_kb_vel;
                // @220
                p_kb_vel->y = -pNormal->x * pCharData->xF0_ground_kb_vel;
            }
        }
        //@230 Now handle the attacker's shield knockback in a similar way
        pAtkShieldKB = &pCharData->x98_atk_shield_kb;
        if ((atkShieldKB_X = pAtkShieldKB->x) != 0 || pAtkShieldKB->y != 0)
        {
            //@250
            if (pCharData->xE0_ground_or_air == 1)
            {
                //@25c
                float kb_x = pAtkShieldKB->x;
                float kb_y = pAtkShieldKB->y;
                float atkShieldKBAngle = func_80022C30(kb_y, kb_x);
                //@270
                float atkShieldKB_len = sqrtf(kb_x*kb_x + kb_y*kb_y);
                //@2d4
                if (atkShieldKB_len < p_ftCommonData->x3E8_shieldKnockbackFrameDecay)
                {
                    //@2e4
                    // BUG IN THE MELEE CODE THAT CAUSES THE INVISIBLE CEILING GLITCH
                    // The next line should be 'pAtkShieldKB->y = 0', but instead it is:
                    p_kb_vel->y = 0;
                    pAtkShieldKB->x = 0;
                }
                else
                {
                    //@2f4
                    // again, the better implementation would be:
                    // *pAtkShieldKB *= (atkShieldKB_len - p_stc_ftcommon->x3e8_shield_kb_frameDecay)/atkShieldKB_len
                    //float atkShieldKBAngle = atan2_80022C30(pAtkShieldKB->y, pAtkShieldKB->x);
                    pAtkShieldKB->x -= p_ftCommonData->x3E8_shieldKnockbackFrameDecay * cosf(atkShieldKBAngle);
                    pAtkShieldKB->y -= p_ftCommonData->x3E8_shieldKnockbackFrameDecay * sinf(atkShieldKBAngle);
                }
                pCharData->xF4_ground_attacker_shield_kb_vel = 0; // 0 = TOC.float@-0x778C
            }
            else
            {
                //@338
                float effectiveFriction;
                Vec3* pNormal = &pCharData->x6F0_collData.x154_groundNormal; // ground_normal offset inside pCharData is 0x844, surface normal points out of the surface. 
                struct attr* pAttr;
                //@344
                if (pCharData->xF4_ground_attacker_shield_kb_vel == 0)
                    pCharData->xF4_ground_attacker_shield_kb_vel = atkShieldKB_X;
                //@350
                pAttr = &pCharData->x110_attr; // attr has offset 0x110
                //@374
                func_8007CE4C(pCharData,
                    /* effectiveFriction - the last constant variable differs from the one for the knockback friction above*/
                    func_80084A40(pCharData) * pAttr->x128_GroundFriction * p_ftCommonData->x3EC_shieldGroundFrictionMultiplier);
                //@378
                pAtkShieldKB->x =  pNormal->y * pCharData->xF4_ground_attacker_shield_kb_vel;
                pAtkShieldKB->y = -pNormal->x * pCharData->xF4_ground_attacker_shield_kb_vel;
            }
        }

        //@39c update ground velocity
		pCharData->xEC_ground_vel += pCharData->xE4_ground_accel_1 + pCharData->xE8_ground_accel_2;
        //@3c0
		pCharData->xE8_ground_accel_2 = 0;
        pCharData->xE4_ground_accel_1 = 0;

        //@3cc self_vel += anim_vel
		PSVECAdd(&pCharData->x80_self_vel, &pCharData->x74_anim_vel, &pCharData->x80_self_vel);
        //@3d0
		pCharData->x74_anim_vel.z = 0;
        pCharData->x74_anim_vel.y = 0;
        pCharData->x74_anim_vel.x = 0;
		
		//@3e0 copy selfVel into a stack storage variable
		selfVel = pCharData->x80_self_vel;
		
		// TODO: these double_lower_32bit variables are probably integer counters that get decremented each frame,
        // but I was not able to trigger the following condition.
		//@3f8 The double value construction then is only used as an interpolation tool between selfVel and some UnkVel2.
		if (pCharData->dmg.x1948 != 0)
        {
            //@404
            // The compiler casts an u32 integer 'val' to a double type using
            // double v = *(double*)&(0x43300000_00000000 | val ^ 0x80000000) - *(double*)&43300000_80000000
            // which is all that happens in the lengthy assembly generated by this
			float C = 1.0f - (float)pCharData->dmg.x194C / (float)pCharData->dmg.x1948;
			
            selfVel.x = C * (pCharData->x80_self_vel.x - pCharData->xA4_unk_vel.x) + pCharData->xA4_unk_vel.x;
            //@458
            selfVel.y = C * (pCharData->x80_self_vel.y - pCharData->xA4_unk_vel.y) + pCharData->xA4_unk_vel.y;
            //@46c
            pCharData->dmg.x194C--;
			if (pCharData->dmg.x194C == 0)
				pCharData->dmg.x1948 = 0;
        }
		//@48c add some horizontal+depth offset to the position? Why is there no vertical component?
		pCharData->xB0_pos.x += pCharData->xF8_playerNudgeVel.x;
		pCharData->xB0_pos.z += pCharData->xF8_playerNudgeVel.y;
        //@4ac
        if (pCharData->x2222_flag.bits.b6 && !pCharData->x2222_flag.bits.b7)
        {
            s32 bit;
            //@4c0
            // pCharData->xD4_unk_vel += selfVel
			PSVECAdd(&pCharData->xD4_unk_vel, &selfVel, &pCharData->xD4_unk_vel);
			//@4d0
            pCharData->xD4_unk_vel.x += p_kb_vel->x;
            pCharData->xD4_unk_vel.y += p_kb_vel->y;
            //@4f0
            if (pCharData->x2210_ThrowFlags.b2)
            {
			    pCharData->x2210_ThrowFlags.b2 = 0;
                bit = 1;
            }
            else
                bit = 0;
			//@514
			if (bit || func_80070FD0(pCharData) != 0 || pCharData->x594_animCurrFlags1.bits.b1)
            {
                //@538
                // pCharData->xB0_position += pCharData->xD4_unk_vel
				PSVECAdd(&pCharData->xB0_pos, &pCharData->xD4_unk_vel, &pCharData->xB0_pos);
				// TODO: we set this velocity to 0 after applying it -> Is this SDI or ASDI?
                pCharData->xD4_unk_vel.z = 0;
                pCharData->xD4_unk_vel.y = 0;
                pCharData->xD4_unk_vel.x = 0;
            }
			//@558 pCharData->xB0_position += *pAtkShieldKB
            PSVECAdd(&pCharData->xB0_pos, (Vec3*)pAtkShieldKB, &pCharData->xB0_pos);
        }
		else
        {
            //pCharData@r31.position@0xB0.xyz += selfVel + pAtkShieldKB
			PSVECAdd(&pCharData->xB0_pos, &selfVel, &pCharData->xB0_pos);
			pCharData->xB0_pos.x += p_kb_vel->x;
            pCharData->xB0_pos.y += p_kb_vel->y;
            PSVECAdd(&pCharData->xB0_pos, (Vec3*)pAtkShieldKB, &pCharData->xB0_pos);
        }
		//@5ac accumulate wind hazards into the windOffset vector
		func_8007B924(pPlayerEntityStruct, /*result vec3*/&windOffset);
    }
    else
    {
        //@5bc
        windOffset.z = 0;
        windOffset.y = 0;
        windOffset.x = 0;
    }
    //@5cc
    func_80076528(pPlayerEntityStruct);

    //@5d4
	if (pCharData->cb.x21D0_callback_EveryHitlag != 0)
		pCharData->cb.x21D0_callback_EveryHitlag(pPlayerEntityStruct); // void (*EveryHitlag_x21D0)(GOBJ *fighter)
    
    //@5ec
	if (pCharData->xE0_ground_or_air == 0)
    {
        //@5f8
        s32 dummy2;
		Vec3 difference; // 0x24
		// I think this function always returns r3=1, but it contains two __assert functions. But I guess these just stop or reset the game.
		// result is written to where r5 points to, which is 'difference' in this case
		if (func_800567C0(pCharData->x6F0_collData.x14C_groundIndex/*groundID field not documented*/, /*Vec3*/&pCharData->xB0_pos, &difference))
			//@610 pCharData->position += difference
			PSVECAdd(&pCharData->xB0_pos, &difference, &pCharData->xB0_pos);
    }
	
	//@620
	pCharData->xB0_pos.x += windOffset.x;
    pCharData->xB0_pos.y += windOffset.y;
    pCharData->xB0_pos.z += windOffset.z;

    //@654 TODO: do the bitflag tests here tell us if the player is dead?
	func_800D3158(pPlayerEntityStruct);
    //@658
	if (pCharData->x2225_flag.bits.b0)
    {
		//@664 if position.y crossed (0.25*stage.blastBottom+0.75*stage.cameraBottom) + stage.crowdReactStart from below...
		if (pCharData->xBC_prevPos.y <= Stage_CalcUnkCamYBounds() &&
		    pCharData->xB0_pos.y >  Stage_CalcUnkCamYBounds())
			pCharData->x2225_flag.bits.b0 = 0;

    }
	else
    {
        //@69c
		if ((pCharData->x222A_flag.bits.b1 == 0) && (/*!x2228_6*/((pCharData->x2228_flag.bits.b5) & 1) == 0))
        {
			//@6b4 if position.y crossed 0.5*(stage.blastBottom+stage.cameraBottom) + stage.crowdReactStart from above...
			if (pCharData->xBC_prevPos.y >= Stage_CalcUnkCamY() &&
			    pCharData->xB0_pos.y <  Stage_CalcUnkCamY())
            {
				//@6e8 plays this sound you always hear when you get close to the bottom blast zone
				func_80088148(pCharData, 96, 127, 64);
                //@6ec
				pCharData->x2225_flag.bits.b0 = 1;
            }
        }
    }
	//@6fc
	if (pCharData->dmg.x18A4_knockbackMagnitude  && // 0.0f@toc-0x778C
        pCharData->x221C_flag.bits.b6 == 0 &&
		!func_80322258(pCharData->xB0_pos.x))
        // not sure when we reach this point, but often around the end of knockback, sometimes completely unrelated
    {
        // @728
		pCharData->dmg.x18A4_knockbackMagnitude = 0.0f; // 0.0f@toc-0x778C
    }
    //@730
	func_8007AF28(pPlayerEntityStruct);
	//@738 The following classify_float calls are inlined by the compiler. The classify_float function does not appear to be in the melee DOL, maybe it was optimized away by the linker.
	if (g_debugLevel >= 3 && // This value is zero and I think it always will be. Probably some debug level indicator, because only a NaN test follows next.
        (fpclassify(pCharData->xB0_pos.x)==FP_NAN || // @744
         fpclassify(pCharData->xB0_pos.y)==FP_NAN || // @7ac
         fpclassify(pCharData->xB0_pos.z)==FP_NAN)) // @814
	{
		//@87c CR.bits[6] = 1;  // this instruction is generated by the compiler because OSReport is a variadic function. bit[0] = leftmost bit
		OSReport("fighter procUpdate pos error.  pos.x=%f    pos.y=%f\n"/*r3 = 0x803C0000 + 1452*/, pCharData->xB0_pos.x, pCharData->xB0_pos.y);
		//@894 TODO: use __FILE__ __LINE__ macros instead?
        __assert("fighter.c" /*filename pointer = 0x803C0000 + 1404*/, /*line*/2517, /*output*/"0"/*r5 = r13 - 31888*/);
    }
    //@8a8 stack unwind
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

    if (jobj_userdata->translate.y != -1.0f) {

        jobj = fighterObj->user_data;

        HSD_JObjSetupMatrix(jobj);


        HSD_JObjGetMtx(jobj, &mtx1);

        HSD_JObjGetScale(jobj, &scale);
        scale.x = func_8007F694((Fighter*)jobj_userdata);

        HSD_JObjGetRotation(jobj, &rotation);

        HSD_JObjGetTranslation(jobj, &translation);

        func_8037A250(&mtx2, &scale, &rotation, &translation, 0);
        PSMTXConcat(&mtx2, &mtx1, &jobj_userdata->mtx);

    }

        
}

///https://decomp.me/scratch/m9K8F
////latest with correct inlines: https://decomp.me/scratch/m9K8F
void func_8006C27C(HSD_GObj* fighterObj, s32 unused) {

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
                __assert("fighter.c", 0xA1E, "0");
            }
        }

        HSD_JObjSetTranslate(fighterObj->hsd_obj, &fighter_r4->xB0_pos);

    }
}


#pragma push
#pragma peephole on
void func_8006C5F4(HSD_GObj* pPlayerEntityStruct/*r3*/)
{
    Fighter* pFighter = (Fighter*) pPlayerEntityStruct->user_data;
	if (!pFighter->x221F_flag.bits.b3)
		func_80089B08(pPlayerEntityStruct);
}
#pragma pop

asm void func_8006C624()
{
	nofralloc
/* 8006C624 00069204  7C 08 02 A6 */	mflr r0
/* 8006C628 00069208  90 01 00 04 */	stw r0, 4(r1)
/* 8006C62C 0006920C  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8006C630 00069210  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8006C634 00069214  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8006C638 00069218  7C 7E 1B 78 */	mr r30, r3
/* 8006C63C 0006921C  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 8006C640 00069220  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8006C644 00069224  88 1F 22 1F */	lbz r0, 0x221f(r31)
/* 8006C648 00069228  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 8006C64C 0006922C  40 82 01 A4 */	bne lbl_8006C7F0
/* 8006C650 00069230  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 8006C654 00069234  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 8006C658 00069238  41 82 00 20 */	beq lbl_8006C678
/* 8006C65C 0006923C  81 9F 21 B8 */	lwz r12, 0x21b8(r31)
/* 8006C660 00069240  28 0C 00 00 */	cmplwi r12, 0
/* 8006C664 00069244  41 82 01 8C */	beq lbl_8006C7F0
/* 8006C668 00069248  7D 88 03 A6 */	mtlr r12
/* 8006C66C 0006924C  38 7E 00 00 */	addi r3, r30, 0
/* 8006C670 00069250  4E 80 00 21 */	blrl 
/* 8006C674 00069254  48 00 01 7C */	b lbl_8006C7F0
lbl_8006C678:
/* 8006C678 00069258  81 9F 21 B4 */	lwz r12, 0x21b4(r31)
/* 8006C67C 0006925C  28 0C 00 00 */	cmplwi r12, 0
/* 8006C680 00069260  41 82 00 B4 */	beq lbl_8006C734
/* 8006C684 00069264  7D 88 03 A6 */	mtlr r12
/* 8006C688 00069268  38 7E 00 00 */	addi r3, r30, 0
/* 8006C68C 0006926C  4E 80 00 21 */	blrl 
/* 8006C690 00069270  83 BE 00 28 */	lwz r29, 0x28(r30)
/* 8006C694 00069274  28 1D 00 00 */	cmplwi r29, 0
/* 8006C698 00069278  40 82 00 14 */	bne lbl_8006C6AC
/* 8006C69C 0006927C  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 8006C6A0 00069280  38 80 03 94 */	li r4, 0x394
/* 8006C6A4 00069284  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 8006C6A8 00069288  48 31 BB 79 */	bl __assert
lbl_8006C6AC:
/* 8006C6AC 0006928C  34 1F 00 B0 */	addic. r0, r31, 0xb0
/* 8006C6B0 00069290  40 82 00 18 */	bne lbl_8006C6C8
/* 8006C6B4 00069294  3C 60 80 3C */	lis r3, lbl_803C0550@ha
/* 8006C6B8 00069298  38 A3 05 50 */	addi r5, r3, lbl_803C0550@l
/* 8006C6BC 0006929C  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 8006C6C0 000692A0  38 80 03 95 */	li r4, 0x395
/* 8006C6C4 000692A4  48 31 BB 5D */	bl __assert
lbl_8006C6C8:
/* 8006C6C8 000692A8  80 7F 00 B0 */	lwz r3, 0xb0(r31)
/* 8006C6CC 000692AC  80 1F 00 B4 */	lwz r0, 0xb4(r31)
/* 8006C6D0 000692B0  90 7D 00 38 */	stw r3, 0x38(r29)
/* 8006C6D4 000692B4  90 1D 00 3C */	stw r0, 0x3c(r29)
/* 8006C6D8 000692B8  80 1F 00 B8 */	lwz r0, 0xb8(r31)
/* 8006C6DC 000692BC  90 1D 00 40 */	stw r0, 0x40(r29)
/* 8006C6E0 000692C0  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 8006C6E4 000692C4  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8006C6E8 000692C8  40 82 00 4C */	bne lbl_8006C734
/* 8006C6EC 000692CC  28 1D 00 00 */	cmplwi r29, 0
/* 8006C6F0 000692D0  41 82 00 44 */	beq lbl_8006C734
/* 8006C6F4 000692D4  40 82 00 14 */	bne lbl_8006C708
/* 8006C6F8 000692D8  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 8006C6FC 000692DC  38 80 02 34 */	li r4, 0x234
/* 8006C700 000692E0  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 8006C704 000692E4  48 31 BB 1D */	bl __assert
lbl_8006C708:
/* 8006C708 000692E8  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 8006C70C 000692EC  38 60 00 00 */	li r3, 0
/* 8006C710 000692F0  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8006C714 000692F4  40 82 00 10 */	bne lbl_8006C724
/* 8006C718 000692F8  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8006C71C 000692FC  41 82 00 08 */	beq lbl_8006C724
/* 8006C720 00069300  38 60 00 01 */	li r3, 1
lbl_8006C724:
/* 8006C724 00069304  2C 03 00 00 */	cmpwi r3, 0
/* 8006C728 00069308  40 82 00 0C */	bne lbl_8006C734
/* 8006C72C 0006930C  7F A3 EB 78 */	mr r3, r29
/* 8006C730 00069310  48 30 6B B9 */	bl HSD_JObjSetMtxDirtySub
lbl_8006C734:
/* 8006C734 00069314  81 9F 21 B0 */	lwz r12, 0x21b0(r31)
/* 8006C738 00069318  28 0C 00 00 */	cmplwi r12, 0
/* 8006C73C 0006931C  41 82 00 B4 */	beq lbl_8006C7F0
/* 8006C740 00069320  7D 88 03 A6 */	mtlr r12
/* 8006C744 00069324  38 7E 00 00 */	addi r3, r30, 0
/* 8006C748 00069328  4E 80 00 21 */	blrl 
/* 8006C74C 0006932C  83 BE 00 28 */	lwz r29, 0x28(r30)
/* 8006C750 00069330  28 1D 00 00 */	cmplwi r29, 0
/* 8006C754 00069334  40 82 00 14 */	bne lbl_8006C768
/* 8006C758 00069338  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 8006C75C 0006933C  38 80 03 94 */	li r4, 0x394
/* 8006C760 00069340  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 8006C764 00069344  48 31 BA BD */	bl __assert
lbl_8006C768:
/* 8006C768 00069348  34 1F 00 B0 */	addic. r0, r31, 0xb0
/* 8006C76C 0006934C  40 82 00 18 */	bne lbl_8006C784
/* 8006C770 00069350  3C 60 80 3C */	lis r3, lbl_803C0550@ha
/* 8006C774 00069354  38 A3 05 50 */	addi r5, r3, lbl_803C0550@l
/* 8006C778 00069358  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 8006C77C 0006935C  38 80 03 95 */	li r4, 0x395
/* 8006C780 00069360  48 31 BA A1 */	bl __assert
lbl_8006C784:
/* 8006C784 00069364  80 7F 00 B0 */	lwz r3, 0xb0(r31)
/* 8006C788 00069368  80 1F 00 B4 */	lwz r0, 0xb4(r31)
/* 8006C78C 0006936C  90 7D 00 38 */	stw r3, 0x38(r29)
/* 8006C790 00069370  90 1D 00 3C */	stw r0, 0x3c(r29)
/* 8006C794 00069374  80 1F 00 B8 */	lwz r0, 0xb8(r31)
/* 8006C798 00069378  90 1D 00 40 */	stw r0, 0x40(r29)
/* 8006C79C 0006937C  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 8006C7A0 00069380  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8006C7A4 00069384  40 82 00 4C */	bne lbl_8006C7F0
/* 8006C7A8 00069388  28 1D 00 00 */	cmplwi r29, 0
/* 8006C7AC 0006938C  41 82 00 44 */	beq lbl_8006C7F0
/* 8006C7B0 00069390  40 82 00 14 */	bne lbl_8006C7C4
/* 8006C7B4 00069394  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 8006C7B8 00069398  38 80 02 34 */	li r4, 0x234
/* 8006C7BC 0006939C  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 8006C7C0 000693A0  48 31 BA 61 */	bl __assert
lbl_8006C7C4:
/* 8006C7C4 000693A4  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 8006C7C8 000693A8  38 60 00 00 */	li r3, 0
/* 8006C7CC 000693AC  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8006C7D0 000693B0  40 82 00 10 */	bne lbl_8006C7E0
/* 8006C7D4 000693B4  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8006C7D8 000693B8  41 82 00 08 */	beq lbl_8006C7E0
/* 8006C7DC 000693BC  38 60 00 01 */	li r3, 1
lbl_8006C7E0:
/* 8006C7E0 000693C0  2C 03 00 00 */	cmpwi r3, 0
/* 8006C7E4 000693C4  40 82 00 0C */	bne lbl_8006C7F0
/* 8006C7E8 000693C8  7F A3 EB 78 */	mr r3, r29
/* 8006C7EC 000693CC  48 30 6A FD */	bl HSD_JObjSetMtxDirtySub
lbl_8006C7F0:
/* 8006C7F0 000693D0  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8006C7F4 000693D4  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8006C7F8 000693D8  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 8006C7FC 000693DC  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 8006C800 000693E0  38 21 00 28 */	addi r1, r1, 0x28
/* 8006C804 000693E4  7C 08 03 A6 */	mtlr r0
/* 8006C808 000693E8  4E 80 00 20 */	blr  
}


////https://decomp.me/scratch/YXlQh
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
        func_80067624(fighterObj, fighter_r31->x60C);
        temp_ptr = jobj_userdata = fighterObj->user_data;

        if (temp_ptr->translate.y != -1.0f) {

            temp_ptr2 = jobj = fighterObj->hsd_obj;

            HSD_JObjSetupMatrix(temp_ptr2);

            HSD_JObjGetMtx(jobj, &mtx1);

            HSD_JObjGetScale(jobj, &scale);
            scale.x = func_8007F694((Fighter*)jobj_userdata);

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

///https://decomp.me/scratch/HIIOt
void func_8006CA5C(HSD_GObj* fighterObj) {

    Fighter* fighter_r31 = fighterObj->user_data;

    if (fighter_r31->x221F_flag.bits.b3 == 0 && func_8016B1C4() == 0) {
        func_8007BA0C(fighterObj);
        if (fighter_r31->x221E_flag.bits.b6) {
            func_80078A2C(fighterObj);
            if (fighter_r31->x1A58) {
                if (fighter_r31->x2225_flag.bits.b1 == 0) {
                    func_80088148(fighter_r31, ((struct S_TEMP2*)fighter_r31->x10C_ftData->ext_attr)->unk30, 0x7F, 0x40);
                }
                func_80078754(fighterObj, fighter_r31->x1A58, 0);
                fighter_r31->cb.x2190_callback_OnGrabFighter_Self(fighterObj);
                fighter_r31->cb.x2198_callback_OnGrabFighter_Victim(fighter_r31->x1A58, fighterObj);
                return;
            }
            func_8007BC90(fighterObj);

            if (fighter_r31->x1A60) {
                if (fighter_r31->x2225_flag.bits.b1 == 0) {
                    func_80088148(fighter_r31, ((struct S_TEMP2*)fighter_r31->x10C_ftData->ext_attr)->unk30, 0x7F, 0x40);
                }
                func_8027B4A4(fighterObj, fighter_r31->x1A60);
                if (fighter_r31->cb.x2194_callback_x2194) {
                    fighter_r31->cb.x2194_callback_x2194(fighterObj);
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
    func_8006CC7C();
    func_8007EA90(unk_ptr, arg0);
}


asm void func_8006CC7C()
{
	nofralloc 
/* 8006CC7C 0006985C  7C 08 02 A6 */	mflr r0
/* 8006CC80 00069860  90 01 00 04 */	stw r0, 4(r1)
/* 8006CC84 00069864  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8006CC88 00069868  DB E1 00 28 */	stfd f31, 0x28(r1)
/* 8006CC8C 0006986C  FF E0 08 90 */	fmr f31, f1
/* 8006CC90 00069870  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8006CC94 00069874  7C 7F 1B 78 */	mr r31, r3
/* 8006CC98 00069878  88 63 22 26 */	lbz r3, 0x2226(r3)
/* 8006CC9C 0006987C  54 60 EF FF */	rlwinm. r0, r3, 0x1d, 0x1f, 0x1f
/* 8006CCA0 00069880  41 82 00 0C */	beq lbl_8006CCAC
/* 8006CCA4 00069884  54 60 E7 FF */	rlwinm. r0, r3, 0x1c, 0x1f, 0x1f
/* 8006CCA8 00069888  41 82 00 E4 */	beq lbl_8006CD8C
lbl_8006CCAC:
/* 8006CCAC 0006988C  C0 1F 18 30 */	lfs f0, 0x1830(r31)
/* 8006CCB0 00069890  EC 00 F8 2A */	fadds f0, f0, f31
/* 8006CCB4 00069894  D0 1F 18 30 */	stfs f0, 0x1830(r31)
/* 8006CCB8 00069898  80 1F 20 28 */	lwz r0, 0x2028(r31)
/* 8006CCBC 0006989C  2C 00 00 00 */	cmpwi r0, 0
/* 8006CCC0 000698A0  41 82 00 38 */	beq lbl_8006CCF8
/* 8006CCC4 000698A4  80 7F 20 2C */	lwz r3, 0x202c(r31)
/* 8006CCC8 000698A8  3C 00 43 30 */	lis r0, 0x4330
/* 8006CCCC 000698AC  C8 22 88 80 */	lfd f1, lbl_804D8260(r2)
/* 8006CCD0 000698B0  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8006CCD4 000698B4  90 61 00 1C */	stw r3, 0x1c(r1)
/* 8006CCD8 000698B8  90 01 00 18 */	stw r0, 0x18(r1)
/* 8006CCDC 000698BC  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 8006CCE0 000698C0  EC 00 08 28 */	fsubs f0, f0, f1
/* 8006CCE4 000698C4  EC 00 F8 28 */	fsubs f0, f0, f31
/* 8006CCE8 000698C8  FC 00 00 1E */	fctiwz f0, f0
/* 8006CCEC 000698CC  D8 01 00 10 */	stfd f0, 0x10(r1)
/* 8006CCF0 000698D0  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8006CCF4 000698D4  90 1F 20 2C */	stw r0, 0x202c(r31)
lbl_8006CCF8:
/* 8006CCF8 000698D8  80 1F 20 34 */	lwz r0, 0x2034(r31)
/* 8006CCFC 000698DC  2C 00 00 00 */	cmpwi r0, 0
/* 8006CD00 000698E0  41 82 00 38 */	beq lbl_8006CD38
/* 8006CD04 000698E4  80 7F 20 38 */	lwz r3, 0x2038(r31)
/* 8006CD08 000698E8  3C 00 43 30 */	lis r0, 0x4330
/* 8006CD0C 000698EC  C8 22 88 80 */	lfd f1, lbl_804D8260(r2)
/* 8006CD10 000698F0  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8006CD14 000698F4  90 61 00 14 */	stw r3, 0x14(r1)
/* 8006CD18 000698F8  90 01 00 10 */	stw r0, 0x10(r1)
/* 8006CD1C 000698FC  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 8006CD20 00069900  EC 00 08 28 */	fsubs f0, f0, f1
/* 8006CD24 00069904  EC 00 F8 28 */	fsubs f0, f0, f31
/* 8006CD28 00069908  FC 00 00 1E */	fctiwz f0, f0
/* 8006CD2C 0006990C  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 8006CD30 00069910  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8006CD34 00069914  90 1F 20 38 */	stw r0, 0x2038(r31)
lbl_8006CD38:
/* 8006CD38 00069918  C0 3F 18 30 */	lfs f1, 0x1830(r31)
/* 8006CD3C 0006991C  C0 02 88 B0 */	lfs f0, lbl_804D8290(r2)
/* 8006CD40 00069920  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8006CD44 00069924  40 81 00 08 */	ble lbl_8006CD4C
/* 8006CD48 00069928  D0 1F 18 30 */	stfs f0, 0x1830(r31)
lbl_8006CD4C:
/* 8006CD4C 0006992C  C0 1F 18 30 */	lfs f0, 0x1830(r31)
/* 8006CD50 00069930  88 9F 22 1F */	lbz r4, 0x221f(r31)
/* 8006CD54 00069934  FC 00 00 1E */	fctiwz f0, f0
/* 8006CD58 00069938  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 8006CD5C 0006993C  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 8006CD60 00069940  D8 01 00 10 */	stfd f0, 0x10(r1)
/* 8006CD64 00069944  80 A1 00 14 */	lwz r5, 0x14(r1)
/* 8006CD68 00069948  4B FC 76 B1 */	bl Player_SetHPByIndex
/* 8006CD6C 0006994C  88 9F 22 1F */	lbz r4, 0x221f(r31)
/* 8006CD70 00069950  FC 40 F8 90 */	fmr f2, f31
/* 8006CD74 00069954  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 8006CD78 00069958  C0 3F 18 30 */	lfs f1, 0x1830(r31)
/* 8006CD7C 0006995C  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 8006CD80 00069960  4B FD 1F 1D */	bl func_8003EC9C
/* 8006CD84 00069964  80 7F 00 00 */	lwz r3, 0(r31)
/* 8006CD88 00069968  48 05 BE FD */	bl func_800C8C84
lbl_8006CD8C:
/* 8006CD8C 0006996C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8006CD90 00069970  CB E1 00 28 */	lfd f31, 0x28(r1)
/* 8006CD94 00069974  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8006CD98 00069978  38 21 00 30 */	addi r1, r1, 0x30
/* 8006CD9C 0006997C  7C 08 03 A6 */	mtlr r0
/* 8006CDA0 00069980  4E 80 00 20 */	blr  
}


asm void func_8006CDA4()
{
	nofralloc 
/* 8006CDA4 00069984  7C 08 02 A6 */	mflr r0
/* 8006CDA8 00069988  90 01 00 04 */	stw r0, 4(r1)
/* 8006CDAC 0006998C  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8006CDB0 00069990  93 E1 00 34 */	stw r31, 0x34(r1)
/* 8006CDB4 00069994  3B E0 00 00 */	li r31, 0
/* 8006CDB8 00069998  93 C1 00 30 */	stw r30, 0x30(r1)
/* 8006CDBC 0006999C  3B C4 00 00 */	addi r30, r4, 0
/* 8006CDC0 000699A0  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 8006CDC4 000699A4  7C 7D 1B 78 */	mr r29, r3
/* 8006CDC8 000699A8  93 81 00 28 */	stw r28, 0x28(r1)
/* 8006CDCC 000699AC  80 63 19 74 */	lwz r3, 0x1974(r3)
/* 8006CDD0 000699B0  28 03 00 00 */	cmplwi r3, 0
/* 8006CDD4 000699B4  41 82 00 14 */	beq lbl_8006CDE8
/* 8006CDD8 000699B8  48 1F E4 DD */	bl func_8026B2B4
/* 8006CDDC 000699BC  2C 03 00 00 */	cmpwi r3, 0
/* 8006CDE0 000699C0  40 82 00 08 */	bne lbl_8006CDE8
/* 8006CDE4 000699C4  3B E0 00 01 */	li r31, 1
lbl_8006CDE8:
/* 8006CDE8 000699C8  88 7D 22 20 */	lbz r3, 0x2220(r29)
/* 8006CDEC 000699CC  3B 80 00 01 */	li r28, 1
/* 8006CDF0 000699D0  38 9C 00 00 */	addi r4, r28, 0
/* 8006CDF4 000699D4  54 60 E7 FF */	rlwinm. r0, r3, 0x1c, 0x1f, 0x1f
/* 8006CDF8 000699D8  40 82 00 10 */	bne lbl_8006CE08
/* 8006CDFC 000699DC  54 60 EF FF */	rlwinm. r0, r3, 0x1d, 0x1f, 0x1f
/* 8006CE00 000699E0  40 82 00 08 */	bne lbl_8006CE08
/* 8006CE04 000699E4  38 80 00 00 */	li r4, 0
lbl_8006CE08:
/* 8006CE08 000699E8  2C 04 00 00 */	cmpwi r4, 0
/* 8006CE0C 000699EC  40 82 00 18 */	bne lbl_8006CE24
/* 8006CE10 000699F0  7F A3 EB 78 */	mr r3, r29
/* 8006CE14 000699F4  48 02 1B 71 */	bl func_8008E984
/* 8006CE18 000699F8  2C 03 00 00 */	cmpwi r3, 0
/* 8006CE1C 000699FC  40 82 00 08 */	bne lbl_8006CE24
/* 8006CE20 00069A00  3B 80 00 00 */	li r28, 0
lbl_8006CE24:
/* 8006CE24 00069A04  3C 60 80 3B */	lis r3, lbl_803B7494@ha
/* 8006CE28 00069A08  38 83 74 94 */	addi r4, r3, lbl_803B7494@l
/* 8006CE2C 00069A0C  80 64 00 00 */	lwz r3, 0(r4)
/* 8006CE30 00069A10  7F 85 00 34 */	cntlzw r5, r28
/* 8006CE34 00069A14  80 04 00 04 */	lwz r0, 4(r4)
/* 8006CE38 00069A18  54 A5 D9 7E */	srwi r5, r5, 5
/* 8006CE3C 00069A1C  90 61 00 18 */	stw r3, 0x18(r1)
/* 8006CE40 00069A20  90 01 00 1C */	stw r0, 0x1c(r1)
/* 8006CE44 00069A24  80 04 00 08 */	lwz r0, 8(r4)
/* 8006CE48 00069A28  90 01 00 20 */	stw r0, 0x20(r1)
/* 8006CE4C 00069A2C  80 7D 00 10 */	lwz r3, 0x10(r29)
/* 8006CE50 00069A30  2C 03 01 45 */	cmpwi r3, 0x145
/* 8006CE54 00069A34  41 82 00 E8 */	beq lbl_8006CF3C
/* 8006CE58 00069A38  38 03 FE DE */	addi r0, r3, -290
/* 8006CE5C 00069A3C  28 00 00 01 */	cmplwi r0, 1
/* 8006CE60 00069A40  40 81 00 DC */	ble lbl_8006CF3C
/* 8006CE64 00069A44  80 1D 18 60 */	lwz r0, 0x1860(r29)
/* 8006CE68 00069A48  28 00 00 0A */	cmplwi r0, 0xa
/* 8006CE6C 00069A4C  41 82 00 D0 */	beq lbl_8006CF3C
/* 8006CE70 00069A50  88 1D 22 26 */	lbz r0, 0x2226(r29)
/* 8006CE74 00069A54  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8006CE78 00069A58  40 82 00 C4 */	bne lbl_8006CF3C
/* 8006CE7C 00069A5C  2C 1F 00 00 */	cmpwi r31, 0
/* 8006CE80 00069A60  41 82 00 7C */	beq lbl_8006CEFC
/* 8006CE84 00069A64  2C 05 00 00 */	cmpwi r5, 0
/* 8006CE88 00069A68  41 82 00 74 */	beq lbl_8006CEFC
/* 8006CE8C 00069A6C  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 8006CE90 00069A70  80 63 04 18 */	lwz r3, 0x418(r3)
/* 8006CE94 00069A74  48 31 36 ED */	bl HSD_Randi
/* 8006CE98 00069A78  7C 03 F0 00 */	cmpw r3, r30
/* 8006CE9C 00069A7C  41 80 00 38 */	blt lbl_8006CED4
/* 8006CEA0 00069A80  80 7D 19 74 */	lwz r3, 0x1974(r29)
/* 8006CEA4 00069A84  48 1F E4 69 */	bl func_8026B30C
/* 8006CEA8 00069A88  2C 03 00 03 */	cmpwi r3, 3
/* 8006CEAC 00069A8C  40 82 00 50 */	bne lbl_8006CEFC
/* 8006CEB0 00069A90  80 7D 19 74 */	lwz r3, 0x1974(r29)
/* 8006CEB4 00069A94  48 1F E6 E1 */	bl func_8026B594
/* 8006CEB8 00069A98  2C 03 00 00 */	cmpwi r3, 0
/* 8006CEBC 00069A9C  41 82 00 40 */	beq lbl_8006CEFC
/* 8006CEC0 00069AA0  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 8006CEC4 00069AA4  80 63 04 1C */	lwz r3, 0x41c(r3)
/* 8006CEC8 00069AA8  48 31 36 B9 */	bl HSD_Randi
/* 8006CECC 00069AAC  2C 03 00 00 */	cmpwi r3, 0
/* 8006CED0 00069AB0  40 82 00 2C */	bne lbl_8006CEFC
lbl_8006CED4:
/* 8006CED4 00069AB4  80 7D 19 78 */	lwz r3, 0x1978(r29)
/* 8006CED8 00069AB8  28 03 00 00 */	cmplwi r3, 0
/* 8006CEDC 00069ABC  41 82 00 10 */	beq lbl_8006CEEC
/* 8006CEE0 00069AC0  C0 22 88 70 */	lfs f1, lbl_804D8250(r2)
/* 8006CEE4 00069AC4  38 81 00 18 */	addi r4, r1, 0x18
/* 8006CEE8 00069AC8  48 1F DC F1 */	bl func_8026ABD8
lbl_8006CEEC:
/* 8006CEEC 00069ACC  80 7D 19 74 */	lwz r3, 0x1974(r29)
/* 8006CEF0 00069AD0  38 81 00 18 */	addi r4, r1, 0x18
/* 8006CEF4 00069AD4  C0 22 88 70 */	lfs f1, lbl_804D8250(r2)
/* 8006CEF8 00069AD8  48 1F DC E1 */	bl func_8026ABD8
lbl_8006CEFC:
/* 8006CEFC 00069ADC  80 1D 19 7C */	lwz r0, 0x197c(r29)
/* 8006CF00 00069AE0  28 00 00 00 */	cmplwi r0, 0
/* 8006CF04 00069AE4  41 82 00 38 */	beq lbl_8006CF3C
/* 8006CF08 00069AE8  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 8006CF0C 00069AEC  80 63 04 18 */	lwz r3, 0x418(r3)
/* 8006CF10 00069AF0  48 31 36 71 */	bl HSD_Randi
/* 8006CF14 00069AF4  7C 03 F0 00 */	cmpw r3, r30
/* 8006CF18 00069AF8  40 80 00 24 */	bge lbl_8006CF3C
/* 8006CF1C 00069AFC  80 7D 00 00 */	lwz r3, 0(r29)
/* 8006CF20 00069B00  48 01 29 C9 */	bl func_8007F8E8
/* 8006CF24 00069B04  80 7D 19 7C */	lwz r3, 0x197c(r29)
/* 8006CF28 00069B08  38 81 00 18 */	addi r4, r1, 0x18
/* 8006CF2C 00069B0C  C0 22 88 70 */	lfs f1, lbl_804D8250(r2)
/* 8006CF30 00069B10  48 1F DC A9 */	bl func_8026ABD8
/* 8006CF34 00069B14  80 7D 00 00 */	lwz r3, 0(r29)
/* 8006CF38 00069B18  48 01 2A 7D */	bl func_8007F9B4
lbl_8006CF3C:
/* 8006CF3C 00069B1C  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8006CF40 00069B20  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 8006CF44 00069B24  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 8006CF48 00069B28  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 8006CF4C 00069B2C  83 81 00 28 */	lwz r28, 0x28(r1)
/* 8006CF50 00069B30  38 21 00 38 */	addi r1, r1, 0x38
/* 8006CF54 00069B34  7C 08 03 A6 */	mtlr r0
/* 8006CF58 00069B38  4E 80 00 20 */	blr  
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
            if (fighter_r31->dmg.x1954 == lbl_804D8254){
                func_8006D10C();
            }
        }
        fighter_r31->x2219_flag.bits.b7 = 0;
    }
}

asm void func_8006D044()
{
	nofralloc 
/* 8006D044 00069C24  7C 08 02 A6 */	mflr r0
/* 8006D048 00069C28  90 01 00 04 */	stw r0, 4(r1)
/* 8006D04C 00069C2C  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8006D050 00069C30  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8006D054 00069C34  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8006D058 00069C38  81 9F 21 D4 */	lwz r12, 0x21d4(r31)
/* 8006D05C 00069C3C  28 0C 00 00 */	cmplwi r12, 0
/* 8006D060 00069C40  41 82 00 0C */	beq lbl_8006D06C
/* 8006D064 00069C44  7D 88 03 A6 */	mtlr r12
/* 8006D068 00069C48  4E 80 00 21 */	blrl 
lbl_8006D06C:
/* 8006D06C 00069C4C  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 8006D070 00069C50  38 A0 00 01 */	li r5, 1
/* 8006D074 00069C54  50 A0 17 7A */	rlwimi r0, r5, 2, 0x1d, 0x1d
/* 8006D078 00069C58  98 1F 22 19 */	stb r0, 0x2219(r31)
/* 8006D07C 00069C5C  80 7F 1A 5C */	lwz r3, 0x1a5c(r31)
/* 8006D080 00069C60  28 03 00 00 */	cmplwi r3, 0
/* 8006D084 00069C64  41 82 00 74 */	beq lbl_8006D0F8
/* 8006D088 00069C68  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 8006D08C 00069C6C  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8006D090 00069C70  40 82 00 68 */	bne lbl_8006D0F8
/* 8006D094 00069C74  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8006D098 00069C78  88 04 22 19 */	lbz r0, 0x2219(r4)
/* 8006D09C 00069C7C  50 A0 07 FE */	rlwimi r0, r5, 0, 0x1f, 0x1f
/* 8006D0A0 00069C80  98 04 22 19 */	stb r0, 0x2219(r4)
/* 8006D0A4 00069C84  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8006D0A8 00069C88  81 9F 21 D4 */	lwz r12, 0x21d4(r31)
/* 8006D0AC 00069C8C  28 0C 00 00 */	cmplwi r12, 0
/* 8006D0B0 00069C90  41 82 00 0C */	beq lbl_8006D0BC
/* 8006D0B4 00069C94  7D 88 03 A6 */	mtlr r12
/* 8006D0B8 00069C98  4E 80 00 21 */	blrl 
lbl_8006D0BC:
/* 8006D0BC 00069C9C  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 8006D0C0 00069CA0  38 A0 00 01 */	li r5, 1
/* 8006D0C4 00069CA4  50 A0 17 7A */	rlwimi r0, r5, 2, 0x1d, 0x1d
/* 8006D0C8 00069CA8  98 1F 22 19 */	stb r0, 0x2219(r31)
/* 8006D0CC 00069CAC  80 7F 1A 5C */	lwz r3, 0x1a5c(r31)
/* 8006D0D0 00069CB0  28 03 00 00 */	cmplwi r3, 0
/* 8006D0D4 00069CB4  41 82 00 24 */	beq lbl_8006D0F8
/* 8006D0D8 00069CB8  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 8006D0DC 00069CBC  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8006D0E0 00069CC0  40 82 00 18 */	bne lbl_8006D0F8
/* 8006D0E4 00069CC4  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8006D0E8 00069CC8  88 04 22 19 */	lbz r0, 0x2219(r4)
/* 8006D0EC 00069CCC  50 A0 07 FE */	rlwimi r0, r5, 0, 0x1f, 0x1f
/* 8006D0F0 00069CD0  98 04 22 19 */	stb r0, 0x2219(r4)
/* 8006D0F4 00069CD4  4B FF FF 51 */	bl func_8006D044
lbl_8006D0F8:
/* 8006D0F8 00069CD8  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8006D0FC 00069CDC  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8006D100 00069CE0  38 21 00 30 */	addi r1, r1, 0x30
/* 8006D104 00069CE4  7C 08 03 A6 */	mtlr r0
/* 8006D108 00069CE8  4E 80 00 20 */	blr  
}


asm void func_8006D10C()
{
	nofralloc 
/* 8006D10C 00069CEC  7C 08 02 A6 */	mflr r0
/* 8006D110 00069CF0  90 01 00 04 */	stw r0, 4(r1)
/* 8006D114 00069CF4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8006D118 00069CF8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8006D11C 00069CFC  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8006D120 00069D00  81 9F 21 D8 */	lwz r12, 0x21d8(r31)
/* 8006D124 00069D04  28 0C 00 00 */	cmplwi r12, 0
/* 8006D128 00069D08  41 82 00 0C */	beq lbl_8006D134
/* 8006D12C 00069D0C  7D 88 03 A6 */	mtlr r12
/* 8006D130 00069D10  4E 80 00 21 */	blrl 
lbl_8006D134:
/* 8006D134 00069D14  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 8006D138 00069D18  38 60 00 00 */	li r3, 0
/* 8006D13C 00069D1C  50 60 17 7A */	rlwimi r0, r3, 2, 0x1d, 0x1d
/* 8006D140 00069D20  98 1F 22 19 */	stb r0, 0x2219(r31)
/* 8006D144 00069D24  80 7F 1A 5C */	lwz r3, 0x1a5c(r31)
/* 8006D148 00069D28  28 03 00 00 */	cmplwi r3, 0
/* 8006D14C 00069D2C  41 82 00 8C */	beq lbl_8006D1D8
/* 8006D150 00069D30  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 8006D154 00069D34  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8006D158 00069D38  40 82 00 80 */	bne lbl_8006D1D8
/* 8006D15C 00069D3C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8006D160 00069D40  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 8006D164 00069D44  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8006D168 00069D48  41 82 00 70 */	beq lbl_8006D1D8
/* 8006D16C 00069D4C  88 1F 22 1A */	lbz r0, 0x221a(r31)
/* 8006D170 00069D50  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8006D174 00069D54  40 82 00 54 */	bne lbl_8006D1C8
/* 8006D178 00069D58  C0 3F 19 54 */	lfs f1, 0x1954(r31)
/* 8006D17C 00069D5C  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006D180 00069D60  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8006D184 00069D64  40 82 00 44 */	bne lbl_8006D1C8
/* 8006D188 00069D68  81 9F 21 D8 */	lwz r12, 0x21d8(r31)
/* 8006D18C 00069D6C  28 0C 00 00 */	cmplwi r12, 0
/* 8006D190 00069D70  41 82 00 0C */	beq lbl_8006D19C
/* 8006D194 00069D74  7D 88 03 A6 */	mtlr r12
/* 8006D198 00069D78  4E 80 00 21 */	blrl 
lbl_8006D19C:
/* 8006D19C 00069D7C  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 8006D1A0 00069D80  38 60 00 00 */	li r3, 0
/* 8006D1A4 00069D84  50 60 17 7A */	rlwimi r0, r3, 2, 0x1d, 0x1d
/* 8006D1A8 00069D88  98 1F 22 19 */	stb r0, 0x2219(r31)
/* 8006D1AC 00069D8C  80 7F 1A 5C */	lwz r3, 0x1a5c(r31)
/* 8006D1B0 00069D90  28 03 00 00 */	cmplwi r3, 0
/* 8006D1B4 00069D94  41 82 00 14 */	beq lbl_8006D1C8
/* 8006D1B8 00069D98  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 8006D1BC 00069D9C  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8006D1C0 00069DA0  40 82 00 08 */	bne lbl_8006D1C8
/* 8006D1C4 00069DA4  4B FF FE 1D */	bl func_8006CFE0
lbl_8006D1C8:
/* 8006D1C8 00069DA8  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 8006D1CC 00069DAC  38 60 00 00 */	li r3, 0
/* 8006D1D0 00069DB0  50 60 07 FE */	rlwimi r0, r3, 0, 0x1f, 0x1f
/* 8006D1D4 00069DB4  98 1F 22 19 */	stb r0, 0x2219(r31)
lbl_8006D1D8:
/* 8006D1D8 00069DB8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8006D1DC 00069DBC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8006D1E0 00069DC0  38 21 00 20 */	addi r1, r1, 0x20
/* 8006D1E4 00069DC4  7C 08 03 A6 */	mtlr r0
/* 8006D1E8 00069DC8  4E 80 00 20 */	blr 
}

asm void func_8006D1EC()
{
	nofralloc
/* 8006D1EC 00069DCC  7C 08 02 A6 */	mflr r0
/* 8006D1F0 00069DD0  90 01 00 04 */	stw r0, 4(r1)
/* 8006D1F4 00069DD4  94 21 FF A0 */	stwu r1, -0x60(r1)
/* 8006D1F8 00069DD8  DB E1 00 58 */	stfd f31, 0x58(r1)
/* 8006D1FC 00069DDC  DB C1 00 50 */	stfd f30, 0x50(r1)
/* 8006D200 00069DE0  BF 21 00 34 */	stmw r25, 0x34(r1)
/* 8006D204 00069DE4  7C 7F 1B 78 */	mr r31, r3
/* 8006D208 00069DE8  3B A0 00 00 */	li r29, 0
/* 8006D20C 00069DEC  3B 60 00 00 */	li r27, 0
/* 8006D210 00069DF0  3B 40 00 00 */	li r26, 0
/* 8006D214 00069DF4  3B 20 00 00 */	li r25, 0
/* 8006D218 00069DF8  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8006D21C 00069DFC  88 1E 22 1F */	lbz r0, 0x221f(r30)
/* 8006D220 00069E00  83 9E 00 10 */	lwz r28, 0x10(r30)
/* 8006D224 00069E04  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 8006D228 00069E08  40 82 07 68 */	bne lbl_8006D990
/* 8006D22C 00069E0C  88 1E 22 1A */	lbz r0, 0x221a(r30)
/* 8006D230 00069E10  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8006D234 00069E14  40 82 00 3C */	bne lbl_8006D270
/* 8006D238 00069E18  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 8006D23C 00069E1C  C0 3E 19 98 */	lfs f1, 0x1998(r30)
/* 8006D240 00069E20  C0 03 02 60 */	lfs f0, 0x260(r3)
/* 8006D244 00069E24  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8006D248 00069E28  40 80 00 28 */	bge lbl_8006D270
/* 8006D24C 00069E2C  C0 03 02 7C */	lfs f0, 0x27c(r3)
/* 8006D250 00069E30  EC 01 00 2A */	fadds f0, f1, f0
/* 8006D254 00069E34  D0 1E 19 98 */	stfs f0, 0x1998(r30)
/* 8006D258 00069E38  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 8006D25C 00069E3C  C0 1E 19 98 */	lfs f0, 0x1998(r30)
/* 8006D260 00069E40  C0 23 02 60 */	lfs f1, 0x260(r3)
/* 8006D264 00069E44  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8006D268 00069E48  40 81 00 08 */	ble lbl_8006D270
/* 8006D26C 00069E4C  D0 3E 19 98 */	stfs f1, 0x1998(r30)
lbl_8006D270:
/* 8006D270 00069E50  88 1E 22 1A */	lbz r0, 0x221a(r30)
/* 8006D274 00069E54  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8006D278 00069E58  41 82 00 9C */	beq lbl_8006D314
/* 8006D27C 00069E5C  80 8D AE B4 */	lwz r4, lbl_804D6554(r13)
/* 8006D280 00069E60  3C 00 43 30 */	lis r0, 0x4330
/* 8006D284 00069E64  80 7E 19 A0 */	lwz r3, 0x19a0(r30)
/* 8006D288 00069E68  C0 44 02 DC */	lfs f2, 0x2dc(r4)
/* 8006D28C 00069E6C  C0 04 02 E0 */	lfs f0, 0x2e0(r4)
/* 8006D290 00069E70  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8006D294 00069E74  90 61 00 2C */	stw r3, 0x2c(r1)
/* 8006D298 00069E78  EC 00 10 28 */	fsubs f0, f0, f2
/* 8006D29C 00069E7C  C0 3E 19 9C */	lfs f1, 0x199c(r30)
/* 8006D2A0 00069E80  90 01 00 28 */	stw r0, 0x28(r1)
/* 8006D2A4 00069E84  C8 82 88 80 */	lfd f4, lbl_804D8260(r2)
/* 8006D2A8 00069E88  C8 61 00 28 */	lfd f3, 0x28(r1)
/* 8006D2AC 00069E8C  EC 21 10 3A */	fmadds f1, f1, f0, f2
/* 8006D2B0 00069E90  C0 42 88 70 */	lfs f2, lbl_804D8250(r2)
/* 8006D2B4 00069E94  EC 63 20 28 */	fsubs f3, f3, f4
/* 8006D2B8 00069E98  C0 84 02 84 */	lfs f4, 0x284(r4)
/* 8006D2BC 00069E9C  C0 04 02 88 */	lfs f0, 0x288(r4)
/* 8006D2C0 00069EA0  EC 22 08 28 */	fsubs f1, f2, f1
/* 8006D2C4 00069EA4  C0 5E 19 98 */	lfs f2, 0x1998(r30)
/* 8006D2C8 00069EA8  EC 23 00 72 */	fmuls f1, f3, f1
/* 8006D2CC 00069EAC  EC 04 00 7A */	fmadds f0, f4, f1, f0
/* 8006D2D0 00069EB0  EC 02 00 28 */	fsubs f0, f2, f0
/* 8006D2D4 00069EB4  D0 1E 19 98 */	stfs f0, 0x1998(r30)
/* 8006D2D8 00069EB8  C0 3E 19 98 */	lfs f1, 0x1998(r30)
/* 8006D2DC 00069EBC  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006D2E0 00069EC0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8006D2E4 00069EC4  40 80 00 30 */	bge lbl_8006D314
/* 8006D2E8 00069EC8  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 8006D2EC 00069ECC  3B 40 00 01 */	li r26, 1
/* 8006D2F0 00069ED0  C0 03 02 80 */	lfs f0, 0x280(r3)
/* 8006D2F4 00069ED4  D0 1E 19 98 */	stfs f0, 0x1998(r30)
/* 8006D2F8 00069ED8  88 9E 22 1F */	lbz r4, 0x221f(r30)
/* 8006D2FC 00069EDC  88 DE 22 1F */	lbz r6, 0x221f(r30)
/* 8006D300 00069EE0  80 7E 19 BC */	lwz r3, 0x19bc(r30)
/* 8006D304 00069EE4  54 84 FF FE */	rlwinm r4, r4, 0x1f, 0x1f, 0x1f
/* 8006D308 00069EE8  88 BE 00 0C */	lbz r5, 0xc(r30)
/* 8006D30C 00069EEC  54 C6 EF FE */	rlwinm r6, r6, 0x1d, 0x1f, 0x1f
/* 8006D310 00069EF0  4B FD 0D 49 */	bl func_8003E058
lbl_8006D314:
/* 8006D314 00069EF4  C0 5E 18 9C */	lfs f2, 0x189c(r30)
/* 8006D318 00069EF8  C0 22 88 74 */	lfs f1, lbl_804D8254(r2)
/* 8006D31C 00069EFC  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 8006D320 00069F00  40 81 00 38 */	ble lbl_8006D358
/* 8006D324 00069F04  C0 02 88 70 */	lfs f0, lbl_804D8250(r2)
/* 8006D328 00069F08  EC 02 00 28 */	fsubs f0, f2, f0
/* 8006D32C 00069F0C  D0 1E 18 9C */	stfs f0, 0x189c(r30)
/* 8006D330 00069F10  C0 1E 18 9C */	lfs f0, 0x189c(r30)
/* 8006D334 00069F14  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8006D338 00069F18  4C 40 13 82 */	cror 2, 0, 2
/* 8006D33C 00069F1C  40 82 00 1C */	bne lbl_8006D358
/* 8006D340 00069F20  C0 1E 18 50 */	lfs f0, 0x1850(r30)
/* 8006D344 00069F24  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8006D348 00069F28  40 82 00 10 */	bne lbl_8006D358
/* 8006D34C 00069F2C  D0 3E 18 9C */	stfs f1, 0x189c(r30)
/* 8006D350 00069F30  7F E3 FB 78 */	mr r3, r31
/* 8006D354 00069F34  48 00 EA E9 */	bl func_8007BE3C
lbl_8006D358:
/* 8006D358 00069F38  C3 DE 18 50 */	lfs f30, 0x1850(r30)
/* 8006D35C 00069F3C  C0 22 88 74 */	lfs f1, lbl_804D8254(r2)
/* 8006D360 00069F40  FC 1E 08 00 */	fcmpu cr0, f30, f1
/* 8006D364 00069F44  41 82 01 7C */	beq lbl_8006D4E0
/* 8006D368 00069F48  83 5E 00 E0 */	lwz r26, 0xe0(r30)
/* 8006D36C 00069F4C  7F C3 F3 78 */	mr r3, r30
/* 8006D370 00069F50  D0 3E 18 9C */	stfs f1, 0x189c(r30)
/* 8006D374 00069F54  C3 FE 18 38 */	lfs f31, 0x1838(r30)
/* 8006D378 00069F58  FC 20 F8 90 */	fmr f1, f31
/* 8006D37C 00069F5C  4B FF F9 01 */	bl func_8006CC7C
/* 8006D380 00069F60  FC 00 F8 1E */	fctiwz f0, f31
/* 8006D384 00069F64  7F C3 F3 78 */	mr r3, r30
/* 8006D388 00069F68  D8 01 00 28 */	stfd f0, 0x28(r1)
/* 8006D38C 00069F6C  80 81 00 2C */	lwz r4, 0x2c(r1)
/* 8006D390 00069F70  48 01 17 01 */	bl func_8007EA90
/* 8006D394 00069F74  7F C3 F3 78 */	mr r3, r30
/* 8006D398 00069F78  48 02 05 99 */	bl func_8008D930
/* 8006D39C 00069F7C  7F C3 F3 78 */	mr r3, r30
/* 8006D3A0 00069F80  48 08 88 05 */	bl func_800F5BA4
/* 8006D3A4 00069F84  81 9E 21 F0 */	lwz r12, 0x21f0(r30)
/* 8006D3A8 00069F88  28 0C 00 00 */	cmplwi r12, 0
/* 8006D3AC 00069F8C  41 82 00 10 */	beq lbl_8006D3BC
/* 8006D3B0 00069F90  7D 88 03 A6 */	mtlr r12
/* 8006D3B4 00069F94  38 7F 00 00 */	addi r3, r31, 0
/* 8006D3B8 00069F98  4E 80 00 21 */	blrl 
lbl_8006D3BC:
/* 8006D3BC 00069F9C  88 1E 22 29 */	lbz r0, 0x2229(r30)
/* 8006D3C0 00069FA0  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8006D3C4 00069FA4  40 82 00 B8 */	bne lbl_8006D47C
/* 8006D3C8 00069FA8  80 1E 18 28 */	lwz r0, 0x1828(r30)
/* 8006D3CC 00069FAC  2C 00 00 02 */	cmpwi r0, 2
/* 8006D3D0 00069FB0  41 82 00 48 */	beq lbl_8006D418
/* 8006D3D4 00069FB4  40 80 00 14 */	bge lbl_8006D3E8
/* 8006D3D8 00069FB8  2C 00 00 00 */	cmpwi r0, 0
/* 8006D3DC 00069FBC  41 82 00 18 */	beq lbl_8006D3F4
/* 8006D3E0 00069FC0  40 80 00 20 */	bge lbl_8006D400
/* 8006D3E4 00069FC4  48 00 00 58 */	b lbl_8006D43C
lbl_8006D3E8:
/* 8006D3E8 00069FC8  2C 00 00 04 */	cmpwi r0, 4
/* 8006D3EC 00069FCC  40 80 00 50 */	bge lbl_8006D43C
/* 8006D3F0 00069FD0  48 00 00 3C */	b lbl_8006D42C
lbl_8006D3F4:
/* 8006D3F4 00069FD4  7F E3 FB 78 */	mr r3, r31
/* 8006D3F8 00069FD8  48 02 18 99 */	bl func_8008EC90
/* 8006D3FC 00069FDC  48 00 00 40 */	b lbl_8006D43C
lbl_8006D400:
/* 8006D400 00069FE0  7F E3 FB 78 */	mr r3, r31
/* 8006D404 00069FE4  48 01 07 55 */	bl func_8007DB58
/* 8006D408 00069FE8  7F E3 FB 78 */	mr r3, r31
/* 8006D40C 00069FEC  C0 22 88 74 */	lfs f1, lbl_804D8254(r2)
/* 8006D410 00069FF0  48 02 14 F9 */	bl func_8008E908
/* 8006D414 00069FF4  48 00 00 28 */	b lbl_8006D43C
lbl_8006D418:
/* 8006D418 00069FF8  7F E3 FB 78 */	mr r3, r31
/* 8006D41C 00069FFC  48 01 07 3D */	bl func_8007DB58
/* 8006D420 0006A000  7F E3 FB 78 */	mr r3, r31
/* 8006D424 0006A004  48 02 15 AD */	bl func_8008E9D0
/* 8006D428 0006A008  48 00 00 14 */	b lbl_8006D43C
lbl_8006D42C:
/* 8006D42C 0006A00C  7F E3 FB 78 */	mr r3, r31
/* 8006D430 0006A010  48 01 07 29 */	bl func_8007DB58
/* 8006D434 0006A014  7F E3 FB 78 */	mr r3, r31
/* 8006D438 0006A018  48 02 17 21 */	bl func_8008EB58
lbl_8006D43C:
/* 8006D43C 0006A01C  83 BE 18 3C */	lwz r29, 0x183c(r30)
/* 8006D440 0006A020  7F C3 F3 78 */	mr r3, r30
/* 8006D444 0006A024  80 9E 18 60 */	lwz r4, 0x1860(r30)
/* 8006D448 0006A028  7F 86 E3 78 */	mr r6, r28
/* 8006D44C 0006A02C  C0 3E 19 60 */	lfs f1, 0x1960(r30)
/* 8006D450 0006A030  38 BD 00 00 */	addi r5, r29, 0
/* 8006D454 0006A034  38 FA 00 00 */	addi r7, r26, 0
/* 8006D458 0006A038  3B 60 00 01 */	li r27, 1
/* 8006D45C 0006A03C  48 02 31 39 */	bl func_80090594
/* 8006D460 0006A040  C0 1E 18 38 */	lfs f0, 0x1838(r30)
/* 8006D464 0006A044  7F C3 F3 78 */	mr r3, r30
/* 8006D468 0006A048  FC 00 00 1E */	fctiwz f0, f0
/* 8006D46C 0006A04C  D8 01 00 28 */	stfd f0, 0x28(r1)
/* 8006D470 0006A050  80 81 00 2C */	lwz r4, 0x2c(r1)
/* 8006D474 0006A054  48 01 18 DD */	bl func_8007ED50
/* 8006D478 0006A058  48 00 02 28 */	b lbl_8006D6A0
lbl_8006D47C:
/* 8006D47C 0006A05C  80 1E 00 04 */	lwz r0, 4(r30)
/* 8006D480 0006A060  2C 00 00 1C */	cmpwi r0, 0x1c
/* 8006D484 0006A064  41 82 00 20 */	beq lbl_8006D4A4
/* 8006D488 0006A068  40 80 00 28 */	bge lbl_8006D4B0
/* 8006D48C 0006A06C  2C 00 00 1B */	cmpwi r0, 0x1b
/* 8006D490 0006A070  40 80 00 08 */	bge lbl_8006D498
/* 8006D494 0006A074  48 00 00 1C */	b lbl_8006D4B0
lbl_8006D498:
/* 8006D498 0006A078  7F E3 FB 78 */	mr r3, r31
/* 8006D49C 0006A07C  48 0E 29 BD */	bl func_8014FE58
/* 8006D4A0 0006A080  48 00 00 34 */	b lbl_8006D4D4
lbl_8006D4A4:
/* 8006D4A4 0006A084  7F E3 FB 78 */	mr r3, r31
/* 8006D4A8 0006A088  48 0E 8B 6D */	bl func_80156014
/* 8006D4AC 0006A08C  48 00 00 28 */	b lbl_8006D4D4
lbl_8006D4B0:
/* 8006D4B0 0006A090  3C 60 80 3C */	lis r3, lbl_803C0610@ha
/* 8006D4B4 0006A094  4C C6 31 82 */	crclr 6
/* 8006D4B8 0006A098  38 63 06 10 */	addi r3, r3, lbl_803C0610@l
/* 8006D4BC 0006A09C  48 2D 81 ED */	bl OSReport
/* 8006D4C0 0006A0A0  3C 60 80 3C */	lis r3, lbl_803C057C@ha
/* 8006D4C4 0006A0A4  38 63 05 7C */	addi r3, r3, lbl_803C057C@l
/* 8006D4C8 0006A0A8  38 80 0C 0D */	li r4, 0xc0d
/* 8006D4CC 0006A0AC  38 AD 83 70 */	addi r5, r13, lbl_804D3A10
/* 8006D4D0 0006A0B0  48 31 AD 51 */	bl __assert
lbl_8006D4D4:
/* 8006D4D4 0006A0B4  7F E3 FB 78 */	mr r3, r31
/* 8006D4D8 0006A0B8  48 02 14 F9 */	bl func_8008E9D0
/* 8006D4DC 0006A0BC  48 00 01 C4 */	b lbl_8006D6A0
lbl_8006D4E0:
/* 8006D4E0 0006A0C0  C0 1E 18 A0 */	lfs f0, 0x18a0(r30)
/* 8006D4E4 0006A0C4  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8006D4E8 0006A0C8  41 82 00 10 */	beq lbl_8006D4F8
/* 8006D4EC 0006A0CC  83 BE 18 40 */	lwz r29, 0x1840(r30)
/* 8006D4F0 0006A0D0  3B 20 00 01 */	li r25, 1
/* 8006D4F4 0006A0D4  48 00 01 AC */	b lbl_8006D6A0
lbl_8006D4F8:
/* 8006D4F8 0006A0D8  80 1E 19 A4 */	lwz r0, 0x19a4(r30)
/* 8006D4FC 0006A0DC  2C 00 00 00 */	cmpwi r0, 0
/* 8006D500 0006A0E0  41 82 00 4C */	beq lbl_8006D54C
/* 8006D504 0006A0E4  2C 1A 00 00 */	cmpwi r26, 0
/* 8006D508 0006A0E8  41 82 00 24 */	beq lbl_8006D52C
/* 8006D50C 0006A0EC  7F E3 FB 78 */	mr r3, r31
/* 8006D510 0006A0F0  48 02 B6 11 */	bl func_80098B20
/* 8006D514 0006A0F4  38 7E 00 00 */	addi r3, r30, 0
/* 8006D518 0006A0F8  38 80 00 82 */	li r4, 0x82
/* 8006D51C 0006A0FC  38 A0 00 7F */	li r5, 0x7f
/* 8006D520 0006A100  38 C0 00 40 */	li r6, 0x40
/* 8006D524 0006A104  48 01 AC 25 */	bl func_80088148
/* 8006D528 0006A108  48 00 00 1C */	b lbl_8006D544
lbl_8006D52C:
/* 8006D52C 0006A10C  81 9E 21 C4 */	lwz r12, 0x21c4(r30)
/* 8006D530 0006A110  28 0C 00 00 */	cmplwi r12, 0
/* 8006D534 0006A114  41 82 00 10 */	beq lbl_8006D544
/* 8006D538 0006A118  7D 88 03 A6 */	mtlr r12
/* 8006D53C 0006A11C  38 7F 00 00 */	addi r3, r31, 0
/* 8006D540 0006A120  4E 80 00 21 */	blrl 
lbl_8006D544:
/* 8006D544 0006A124  83 BE 19 A4 */	lwz r29, 0x19a4(r30)
/* 8006D548 0006A128  48 00 01 58 */	b lbl_8006D6A0
lbl_8006D54C:
/* 8006D54C 0006A12C  80 1E 19 18 */	lwz r0, 0x1918(r30)
/* 8006D550 0006A130  2C 00 00 00 */	cmpwi r0, 0
/* 8006D554 0006A134  41 82 00 40 */	beq lbl_8006D594
/* 8006D558 0006A138  C0 1E 19 1C */	lfs f0, 0x191c(r30)
/* 8006D55C 0006A13C  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8006D560 0006A140  41 82 00 2C */	beq lbl_8006D58C
/* 8006D564 0006A144  80 1E 1A 58 */	lwz r0, 0x1a58(r30)
/* 8006D568 0006A148  28 00 00 00 */	cmplwi r0, 0
/* 8006D56C 0006A14C  40 82 00 20 */	bne lbl_8006D58C
/* 8006D570 0006A150  80 1E 1A 60 */	lwz r0, 0x1a60(r30)
/* 8006D574 0006A154  28 00 00 00 */	cmplwi r0, 0
/* 8006D578 0006A158  40 82 00 14 */	bne lbl_8006D58C
/* 8006D57C 0006A15C  7F E3 FB 78 */	mr r3, r31
/* 8006D580 0006A160  48 01 05 D9 */	bl func_8007DB58
/* 8006D584 0006A164  7F E3 FB 78 */	mr r3, r31
/* 8006D588 0006A168  48 02 C8 15 */	bl func_80099D9C
lbl_8006D58C:
/* 8006D58C 0006A16C  83 BE 19 18 */	lwz r29, 0x1918(r30)
/* 8006D590 0006A170  48 00 01 10 */	b lbl_8006D6A0
lbl_8006D594:
/* 8006D594 0006A174  80 1E 19 14 */	lwz r0, 0x1914(r30)
/* 8006D598 0006A178  2C 00 00 00 */	cmpwi r0, 0
/* 8006D59C 0006A17C  41 82 00 50 */	beq lbl_8006D5EC
/* 8006D5A0 0006A180  81 9E 21 C0 */	lwz r12, 0x21c0(r30)
/* 8006D5A4 0006A184  28 0C 00 00 */	cmplwi r12, 0
/* 8006D5A8 0006A188  41 82 00 10 */	beq lbl_8006D5B8
/* 8006D5AC 0006A18C  7D 88 03 A6 */	mtlr r12
/* 8006D5B0 0006A190  38 7F 00 00 */	addi r3, r31, 0
/* 8006D5B4 0006A194  4E 80 00 21 */	blrl 
lbl_8006D5B8:
/* 8006D5B8 0006A198  88 1E 20 73 */	lbz r0, 0x2073(r30)
/* 8006D5BC 0006A19C  80 9E 19 14 */	lwz r4, 0x1914(r30)
/* 8006D5C0 0006A1A0  28 00 00 46 */	cmplwi r0, 0x46
/* 8006D5C4 0006A1A4  3B A4 00 00 */	addi r29, r4, 0
/* 8006D5C8 0006A1A8  40 82 00 18 */	bne lbl_8006D5E0
/* 8006D5CC 0006A1AC  38 7E 00 00 */	addi r3, r30, 0
/* 8006D5D0 0006A1B0  38 80 00 0E */	li r4, 0xe
/* 8006D5D4 0006A1B4  38 A0 00 00 */	li r5, 0
/* 8006D5D8 0006A1B8  48 01 15 D5 */	bl func_8007EBAC
/* 8006D5DC 0006A1BC  48 00 00 C4 */	b lbl_8006D6A0
lbl_8006D5E0:
/* 8006D5E0 0006A1C0  7F C3 F3 78 */	mr r3, r30
/* 8006D5E4 0006A1C4  48 01 18 29 */	bl func_8007EE0C
/* 8006D5E8 0006A1C8  48 00 00 B8 */	b lbl_8006D6A0
lbl_8006D5EC:
/* 8006D5EC 0006A1CC  80 1E 19 24 */	lwz r0, 0x1924(r30)
/* 8006D5F0 0006A1D0  2C 00 00 00 */	cmpwi r0, 0
/* 8006D5F4 0006A1D4  41 82 00 0C */	beq lbl_8006D600
/* 8006D5F8 0006A1D8  7C 1D 03 78 */	mr r29, r0
/* 8006D5FC 0006A1DC  48 00 00 A4 */	b lbl_8006D6A0
lbl_8006D600:
/* 8006D600 0006A1E0  80 1E 1A 3C */	lwz r0, 0x1a3c(r30)
/* 8006D604 0006A1E4  2C 00 00 00 */	cmpwi r0, 0
/* 8006D608 0006A1E8  41 82 00 10 */	beq lbl_8006D618
/* 8006D60C 0006A1EC  7F E3 FB 78 */	mr r3, r31
/* 8006D610 0006A1F0  48 02 B6 8D */	bl func_80098C9C
/* 8006D614 0006A1F4  48 00 00 8C */	b lbl_8006D6A0
lbl_8006D618:
/* 8006D618 0006A1F8  C0 1E 1A 2C */	lfs f0, 0x1a2c(r30)
/* 8006D61C 0006A1FC  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8006D620 0006A200  41 82 00 20 */	beq lbl_8006D640
/* 8006D624 0006A204  81 9E 21 C8 */	lwz r12, 0x21c8(r30)
/* 8006D628 0006A208  28 0C 00 00 */	cmplwi r12, 0
/* 8006D62C 0006A20C  41 82 00 74 */	beq lbl_8006D6A0
/* 8006D630 0006A210  7D 88 03 A6 */	mtlr r12
/* 8006D634 0006A214  38 7F 00 00 */	addi r3, r31, 0
/* 8006D638 0006A218  4E 80 00 21 */	blrl 
/* 8006D63C 0006A21C  48 00 00 64 */	b lbl_8006D6A0
lbl_8006D640:
/* 8006D640 0006A220  C0 1E 1A 40 */	lfs f0, 0x1a40(r30)
/* 8006D644 0006A224  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8006D648 0006A228  41 82 00 34 */	beq lbl_8006D67C
/* 8006D64C 0006A22C  80 9E 00 04 */	lwz r4, 4(r30)
/* 8006D650 0006A230  3C 60 80 3C */	lis r3, ft_OnAbsorb@ha
/* 8006D654 0006A234  38 03 18 08 */	addi r0, r3, ft_OnAbsorb@l
/* 8006D658 0006A238  54 83 10 3A */	slwi r3, r4, 2
/* 8006D65C 0006A23C  7C 60 1A 14 */	add r3, r0, r3
/* 8006D660 0006A240  81 83 00 00 */	lwz r12, 0(r3)
/* 8006D664 0006A244  28 0C 00 00 */	cmplwi r12, 0
/* 8006D668 0006A248  41 82 00 38 */	beq lbl_8006D6A0
/* 8006D66C 0006A24C  7D 88 03 A6 */	mtlr r12
/* 8006D670 0006A250  38 7F 00 00 */	addi r3, r31, 0
/* 8006D674 0006A254  4E 80 00 21 */	blrl 
/* 8006D678 0006A258  48 00 00 28 */	b lbl_8006D6A0
lbl_8006D67C:
/* 8006D67C 0006A25C  80 1E 20 AC */	lwz r0, 0x20ac(r30)
/* 8006D680 0006A260  28 00 00 00 */	cmplwi r0, 0
/* 8006D684 0006A264  41 82 00 1C */	beq lbl_8006D6A0
/* 8006D688 0006A268  81 9E 21 F4 */	lwz r12, 0x21f4(r30)
/* 8006D68C 0006A26C  28 0C 00 00 */	cmplwi r12, 0
/* 8006D690 0006A270  41 82 00 10 */	beq lbl_8006D6A0
/* 8006D694 0006A274  7D 88 03 A6 */	mtlr r12
/* 8006D698 0006A278  38 7F 00 00 */	addi r3, r31, 0
/* 8006D69C 0006A27C  4E 80 00 21 */	blrl 
lbl_8006D6A0:
/* 8006D6A0 0006A280  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006D6A4 0006A284  FC 1E 00 00 */	fcmpu cr0, f30, f0
/* 8006D6A8 0006A288  40 82 00 40 */	bne lbl_8006D6E8
/* 8006D6AC 0006A28C  C3 DE 18 38 */	lfs f30, 0x1838(r30)
/* 8006D6B0 0006A290  FC 1E 00 00 */	fcmpu cr0, f30, f0
/* 8006D6B4 0006A294  41 82 00 34 */	beq lbl_8006D6E8
/* 8006D6B8 0006A298  7F C3 F3 78 */	mr r3, r30
/* 8006D6BC 0006A29C  FC 20 F0 90 */	fmr f1, f30
/* 8006D6C0 0006A2A0  4B FF F5 BD */	bl func_8006CC7C
/* 8006D6C4 0006A2A4  FC 00 F0 1E */	fctiwz f0, f30
/* 8006D6C8 0006A2A8  7F C3 F3 78 */	mr r3, r30
/* 8006D6CC 0006A2AC  D8 01 00 28 */	stfd f0, 0x28(r1)
/* 8006D6D0 0006A2B0  80 81 00 2C */	lwz r4, 0x2c(r1)
/* 8006D6D4 0006A2B4  48 01 13 BD */	bl func_8007EA90
/* 8006D6D8 0006A2B8  7F C3 F3 78 */	mr r3, r30
/* 8006D6DC 0006A2BC  48 08 85 59 */	bl func_800F5C34
/* 8006D6E0 0006A2C0  7F C3 F3 78 */	mr r3, r30
/* 8006D6E4 0006A2C4  48 01 2E 19 */	bl func_800804FC
lbl_8006D6E8:
/* 8006D6E8 0006A2C8  7F E3 FB 78 */	mr r3, r31
/* 8006D6EC 0006A2CC  48 05 B6 15 */	bl func_800C8D00
/* 8006D6F0 0006A2D0  2C 1D 00 00 */	cmpwi r29, 0
/* 8006D6F4 0006A2D4  41 82 00 EC */	beq lbl_8006D7E0
/* 8006D6F8 0006A2D8  C0 3E 19 60 */	lfs f1, 0x1960(r30)
/* 8006D6FC 0006A2DC  38 7D 00 00 */	addi r3, r29, 0
/* 8006D700 0006A2E0  38 9C 00 00 */	addi r4, r28, 0
/* 8006D704 0006A2E4  48 01 03 71 */	bl func_8007DA74
/* 8006D708 0006A2E8  D0 3E 19 5C */	stfs f1, 0x195c(r30)
/* 8006D70C 0006A2EC  C0 1E 19 5C */	lfs f0, 0x195c(r30)
/* 8006D710 0006A2F0  C0 3E 19 64 */	lfs f1, 0x1964(r30)
/* 8006D714 0006A2F4  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8006D718 0006A2F8  40 80 00 08 */	bge lbl_8006D720
/* 8006D71C 0006A2FC  D0 3E 19 5C */	stfs f1, 0x195c(r30)
lbl_8006D720:
/* 8006D720 0006A300  C0 3E 19 5C */	lfs f1, 0x195c(r30)
/* 8006D724 0006A304  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006D728 0006A308  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8006D72C 0006A30C  40 81 00 BC */	ble lbl_8006D7E8
/* 8006D730 0006A310  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 8006D734 0006A314  C0 03 01 94 */	lfs f0, 0x194(r3)
/* 8006D738 0006A318  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8006D73C 0006A31C  40 81 00 08 */	ble lbl_8006D744
/* 8006D740 0006A320  D0 1E 19 5C */	stfs f0, 0x195c(r30)
lbl_8006D744:
/* 8006D744 0006A324  88 1E 22 1A */	lbz r0, 0x221a(r30)
/* 8006D748 0006A328  38 60 00 01 */	li r3, 1
/* 8006D74C 0006A32C  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 8006D750 0006A330  2C 1B 00 00 */	cmpwi r27, 0
/* 8006D754 0006A334  98 1E 22 1A */	stb r0, 0x221a(r30)
/* 8006D758 0006A338  41 82 00 10 */	beq lbl_8006D768
/* 8006D75C 0006A33C  88 1E 22 1A */	lbz r0, 0x221a(r30)
/* 8006D760 0006A340  50 60 26 F6 */	rlwimi r0, r3, 4, 0x1b, 0x1b
/* 8006D764 0006A344  98 1E 22 1A */	stb r0, 0x221a(r30)
lbl_8006D768:
/* 8006D768 0006A348  2C 19 00 00 */	cmpwi r25, 0
/* 8006D76C 0006A34C  41 82 00 0C */	beq lbl_8006D778
/* 8006D770 0006A350  C0 1E 19 5C */	lfs f0, 0x195c(r30)
/* 8006D774 0006A354  D0 1E 18 9C */	stfs f0, 0x189c(r30)
lbl_8006D778:
/* 8006D778 0006A358  88 1E 22 19 */	lbz r0, 0x2219(r30)
/* 8006D77C 0006A35C  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 8006D780 0006A360  40 82 00 68 */	bne lbl_8006D7E8
/* 8006D784 0006A364  83 3F 00 2C */	lwz r25, 0x2c(r31)
/* 8006D788 0006A368  81 99 21 D4 */	lwz r12, 0x21d4(r25)
/* 8006D78C 0006A36C  28 0C 00 00 */	cmplwi r12, 0
/* 8006D790 0006A370  41 82 00 10 */	beq lbl_8006D7A0
/* 8006D794 0006A374  7D 88 03 A6 */	mtlr r12
/* 8006D798 0006A378  38 7F 00 00 */	addi r3, r31, 0
/* 8006D79C 0006A37C  4E 80 00 21 */	blrl 
lbl_8006D7A0:
/* 8006D7A0 0006A380  88 19 22 19 */	lbz r0, 0x2219(r25)
/* 8006D7A4 0006A384  38 A0 00 01 */	li r5, 1
/* 8006D7A8 0006A388  50 A0 17 7A */	rlwimi r0, r5, 2, 0x1d, 0x1d
/* 8006D7AC 0006A38C  98 19 22 19 */	stb r0, 0x2219(r25)
/* 8006D7B0 0006A390  80 79 1A 5C */	lwz r3, 0x1a5c(r25)
/* 8006D7B4 0006A394  28 03 00 00 */	cmplwi r3, 0
/* 8006D7B8 0006A398  41 82 00 30 */	beq lbl_8006D7E8
/* 8006D7BC 0006A39C  88 19 22 19 */	lbz r0, 0x2219(r25)
/* 8006D7C0 0006A3A0  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8006D7C4 0006A3A4  40 82 00 24 */	bne lbl_8006D7E8
/* 8006D7C8 0006A3A8  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8006D7CC 0006A3AC  88 04 22 19 */	lbz r0, 0x2219(r4)
/* 8006D7D0 0006A3B0  50 A0 07 FE */	rlwimi r0, r5, 0, 0x1f, 0x1f
/* 8006D7D4 0006A3B4  98 04 22 19 */	stb r0, 0x2219(r4)
/* 8006D7D8 0006A3B8  4B FF F8 6D */	bl func_8006D044
/* 8006D7DC 0006A3BC  48 00 00 0C */	b lbl_8006D7E8
lbl_8006D7E0:
/* 8006D7E0 0006A3C0  7F C3 F3 78 */	mr r3, r30
/* 8006D7E4 0006A3C4  48 02 2F 35 */	bl func_80090718
lbl_8006D7E8:
/* 8006D7E8 0006A3C8  88 1E 22 1A */	lbz r0, 0x221a(r30)
/* 8006D7EC 0006A3CC  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8006D7F0 0006A3D0  40 82 00 14 */	bne lbl_8006D804
/* 8006D7F4 0006A3D4  C0 3E 19 58 */	lfs f1, 0x1958(r30)
/* 8006D7F8 0006A3D8  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006D7FC 0006A3DC  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8006D800 0006A3E0  41 82 00 B4 */	beq lbl_8006D8B4
lbl_8006D804:
/* 8006D804 0006A3E4  88 1E 22 19 */	lbz r0, 0x2219(r30)
/* 8006D808 0006A3E8  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 8006D80C 0006A3EC  40 82 00 5C */	bne lbl_8006D868
/* 8006D810 0006A3F0  83 3F 00 2C */	lwz r25, 0x2c(r31)
/* 8006D814 0006A3F4  81 99 21 D4 */	lwz r12, 0x21d4(r25)
/* 8006D818 0006A3F8  28 0C 00 00 */	cmplwi r12, 0
/* 8006D81C 0006A3FC  41 82 00 10 */	beq lbl_8006D82C
/* 8006D820 0006A400  7D 88 03 A6 */	mtlr r12
/* 8006D824 0006A404  38 7F 00 00 */	addi r3, r31, 0
/* 8006D828 0006A408  4E 80 00 21 */	blrl 
lbl_8006D82C:
/* 8006D82C 0006A40C  88 19 22 19 */	lbz r0, 0x2219(r25)
/* 8006D830 0006A410  38 A0 00 01 */	li r5, 1
/* 8006D834 0006A414  50 A0 17 7A */	rlwimi r0, r5, 2, 0x1d, 0x1d
/* 8006D838 0006A418  98 19 22 19 */	stb r0, 0x2219(r25)
/* 8006D83C 0006A41C  80 79 1A 5C */	lwz r3, 0x1a5c(r25)
/* 8006D840 0006A420  28 03 00 00 */	cmplwi r3, 0
/* 8006D844 0006A424  41 82 00 24 */	beq lbl_8006D868
/* 8006D848 0006A428  88 19 22 19 */	lbz r0, 0x2219(r25)
/* 8006D84C 0006A42C  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8006D850 0006A430  40 82 00 18 */	bne lbl_8006D868
/* 8006D854 0006A434  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8006D858 0006A438  88 04 22 19 */	lbz r0, 0x2219(r4)
/* 8006D85C 0006A43C  50 A0 07 FE */	rlwimi r0, r5, 0, 0x1f, 0x1f
/* 8006D860 0006A440  98 04 22 19 */	stb r0, 0x2219(r4)
/* 8006D864 0006A444  4B FF F7 E1 */	bl func_8006D044
lbl_8006D868:
/* 8006D868 0006A448  88 1E 22 1A */	lbz r0, 0x221a(r30)
/* 8006D86C 0006A44C  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8006D870 0006A450  41 82 00 28 */	beq lbl_8006D898
/* 8006D874 0006A454  88 1E 22 19 */	lbz r0, 0x2219(r30)
/* 8006D878 0006A458  38 60 00 01 */	li r3, 1
/* 8006D87C 0006A45C  50 60 07 FE */	rlwimi r0, r3, 0, 0x1f, 0x1f
/* 8006D880 0006A460  98 1E 22 19 */	stb r0, 0x2219(r30)
/* 8006D884 0006A464  38 60 00 00 */	li r3, 0
/* 8006D888 0006A468  88 1E 22 1A */	lbz r0, 0x221a(r30)
/* 8006D88C 0006A46C  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 8006D890 0006A470  98 1E 22 1A */	stb r0, 0x221a(r30)
/* 8006D894 0006A474  48 00 00 20 */	b lbl_8006D8B4
lbl_8006D898:
/* 8006D898 0006A478  C0 3E 19 58 */	lfs f1, 0x1958(r30)
/* 8006D89C 0006A47C  C0 1E 19 54 */	lfs f0, 0x1954(r30)
/* 8006D8A0 0006A480  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8006D8A4 0006A484  40 81 00 08 */	ble lbl_8006D8AC
/* 8006D8A8 0006A488  D0 3E 19 54 */	stfs f1, 0x1954(r30)
lbl_8006D8AC:
/* 8006D8AC 0006A48C  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006D8B0 0006A490  D0 1E 19 58 */	stfs f0, 0x1958(r30)
lbl_8006D8B4:
/* 8006D8B4 0006A494  C0 9E 19 28 */	lfs f4, 0x1928(r30)
/* 8006D8B8 0006A498  C0 62 88 74 */	lfs f3, lbl_804D8254(r2)
/* 8006D8BC 0006A49C  FC 04 18 00 */	fcmpu cr0, f4, f3
/* 8006D8C0 0006A4A0  41 82 00 34 */	beq lbl_8006D8F4
/* 8006D8C4 0006A4A4  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 8006D8C8 0006A4A8  C0 1E 19 2C */	lfs f0, 0x192c(r30)
/* 8006D8CC 0006A4AC  C0 43 03 E0 */	lfs f2, 0x3e0(r3)
/* 8006D8D0 0006A4B0  C0 23 03 E4 */	lfs f1, 0x3e4(r3)
/* 8006D8D4 0006A4B4  FC 00 18 40 */	fcmpo cr0, f0, f3
/* 8006D8D8 0006A4B8  EC 04 08 BA */	fmadds f0, f4, f2, f1
/* 8006D8DC 0006A4BC  40 80 00 08 */	bge lbl_8006D8E4
/* 8006D8E0 0006A4C0  48 00 00 08 */	b lbl_8006D8E8
lbl_8006D8E4:
/* 8006D8E4 0006A4C4  FC 00 00 50 */	fneg f0, f0
lbl_8006D8E8:
/* 8006D8E8 0006A4C8  D0 1E 00 F4 */	stfs f0, 0xf4(r30)
/* 8006D8EC 0006A4CC  7F E3 FB 78 */	mr r3, r31
/* 8006D8F0 0006A4D0  48 01 09 B5 */	bl func_8007E2A4
lbl_8006D8F4:
/* 8006D8F4 0006A4D4  C0 22 88 74 */	lfs f1, lbl_804D8254(r2)
/* 8006D8F8 0006A4D8  38 60 00 00 */	li r3, 0
/* 8006D8FC 0006A4DC  D0 3E 18 38 */	stfs f1, 0x1838(r30)
/* 8006D900 0006A4E0  90 7E 18 3C */	stw r3, 0x183c(r30)
/* 8006D904 0006A4E4  90 7E 18 28 */	stw r3, 0x1828(r30)
/* 8006D908 0006A4E8  D0 3E 18 50 */	stfs f1, 0x1850(r30)
/* 8006D90C 0006A4EC  D0 3E 18 A0 */	stfs f1, 0x18a0(r30)
/* 8006D910 0006A4F0  90 7E 18 40 */	stw r3, 0x1840(r30)
/* 8006D914 0006A4F4  90 7E 19 14 */	stw r3, 0x1914(r30)
/* 8006D918 0006A4F8  90 7E 19 18 */	stw r3, 0x1918(r30)
/* 8006D91C 0006A4FC  D0 3E 19 1C */	stfs f1, 0x191c(r30)
/* 8006D920 0006A500  90 7E 20 AC */	stw r3, 0x20ac(r30)
/* 8006D924 0006A504  88 1E 22 1C */	lbz r0, 0x221c(r30)
/* 8006D928 0006A508  50 60 17 7A */	rlwimi r0, r3, 2, 0x1d, 0x1d
/* 8006D92C 0006A50C  98 1E 22 1C */	stb r0, 0x221c(r30)
/* 8006D930 0006A510  90 7E 19 24 */	stw r3, 0x1924(r30)
/* 8006D934 0006A514  D0 3E 19 28 */	stfs f1, 0x1928(r30)
/* 8006D938 0006A518  90 7E 19 A0 */	stw r3, 0x19a0(r30)
/* 8006D93C 0006A51C  90 7E 19 A4 */	stw r3, 0x19a4(r30)
/* 8006D940 0006A520  90 7E 19 A8 */	stw r3, 0x19a8(r30)
/* 8006D944 0006A524  90 7E 1A 3C */	stw r3, 0x1a3c(r30)
/* 8006D948 0006A528  D0 3E 1A 2C */	stfs f1, 0x1a2c(r30)
/* 8006D94C 0006A52C  D0 3E 1A 40 */	stfs f1, 0x1a40(r30)
/* 8006D950 0006A530  90 7E 1A 44 */	stw r3, 0x1a44(r30)
/* 8006D954 0006A534  90 7E 1A 48 */	stw r3, 0x1a48(r30)
/* 8006D958 0006A538  C0 02 88 70 */	lfs f0, lbl_804D8250(r2)
/* 8006D95C 0006A53C  D0 1E 19 60 */	stfs f0, 0x1960(r30)
/* 8006D960 0006A540  D0 3E 19 64 */	stfs f1, 0x1964(r30)
/* 8006D964 0006A544  90 7E 19 50 */	stw r3, 0x1950(r30)
/* 8006D968 0006A548  88 1E 22 19 */	lbz r0, 0x2219(r30)
/* 8006D96C 0006A54C  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 8006D970 0006A550  41 82 00 10 */	beq lbl_8006D980
/* 8006D974 0006A554  80 1E 18 F4 */	lwz r0, 0x18f4(r30)
/* 8006D978 0006A558  2C 00 00 00 */	cmpwi r0, 0
/* 8006D97C 0006A55C  41 82 00 0C */	beq lbl_8006D988
lbl_8006D980:
/* 8006D980 0006A560  7F E3 FB 78 */	mr r3, r31
/* 8006D984 0006A564  48 05 56 55 */	bl func_800C2FD8
lbl_8006D988:
/* 8006D988 0006A568  7F C3 F3 78 */	mr r3, r30
/* 8006D98C 0006A56C  48 03 34 19 */	bl func_800A0DA4
lbl_8006D990:
/* 8006D990 0006A570  BB 21 00 34 */	lmw r25, 0x34(r1)
/* 8006D994 0006A574  80 01 00 64 */	lwz r0, 0x64(r1)
/* 8006D998 0006A578  CB E1 00 58 */	lfd f31, 0x58(r1)
/* 8006D99C 0006A57C  CB C1 00 50 */	lfd f30, 0x50(r1)
/* 8006D9A0 0006A580  38 21 00 60 */	addi r1, r1, 0x60
/* 8006D9A4 0006A584  7C 08 03 A6 */	mtlr r0
/* 8006D9A8 0006A588  4E 80 00 20 */	blr  
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


asm void func_8006DABC()
{
	nofralloc 
/* 8006DABC 0006A69C  7C 08 02 A6 */	mflr r0
/* 8006DAC0 0006A6A0  3C 80 80 3C */	lis r4, lbl_803C125C@ha
/* 8006DAC4 0006A6A4  90 01 00 04 */	stw r0, 4(r1)
/* 8006DAC8 0006A6A8  3C C0 80 46 */	lis r6, lbl_80458FD0@ha
/* 8006DACC 0006A6AC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8006DAD0 0006A6B0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8006DAD4 0006A6B4  3B E6 8F D0 */	addi r31, r6, lbl_80458FD0@l
/* 8006DAD8 0006A6B8  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8006DADC 0006A6BC  3B C3 00 00 */	addi r30, r3, 0
/* 8006DAE0 0006A6C0  80 03 00 04 */	lwz r0, 4(r3)
/* 8006DAE4 0006A6C4  54 05 10 3A */	slwi r5, r0, 2
/* 8006DAE8 0006A6C8  38 04 12 5C */	addi r0, r4, lbl_803C125C@l
/* 8006DAEC 0006A6CC  7C 80 2A 14 */	add r4, r0, r5
/* 8006DAF0 0006A6D0  81 84 00 00 */	lwz r12, 0(r4)
/* 8006DAF4 0006A6D4  28 0C 00 00 */	cmplwi r12, 0
/* 8006DAF8 0006A6D8  41 82 00 10 */	beq lbl_8006DB08
/* 8006DAFC 0006A6DC  80 7E 00 00 */	lwz r3, 0(r30)
/* 8006DB00 0006A6E0  7D 88 03 A6 */	mtlr r12
/* 8006DB04 0006A6E4  4E 80 00 21 */	blrl 
lbl_8006DB08:
/* 8006DB08 0006A6E8  80 7E 00 00 */	lwz r3, 0(r30)
/* 8006DB0C 0006A6EC  48 00 DD DD */	bl func_8007B8E8
/* 8006DB10 0006A6F0  38 7E 06 0C */	addi r3, r30, 0x60c
/* 8006DB14 0006A6F4  4B FF 9B 75 */	bl func_80067688
/* 8006DB18 0006A6F8  80 7E 00 00 */	lwz r3, 0(r30)
/* 8006DB1C 0006A6FC  48 1F DC DD */	bl func_8026B7F8
/* 8006DB20 0006A700  80 7E 08 90 */	lwz r3, 0x890(r30)
/* 8006DB24 0006A704  4B FB B5 B1 */	bl func_800290D4
/* 8006DB28 0006A708  7F C3 F3 78 */	mr r3, r30
/* 8006DB2C 0006A70C  48 03 05 A9 */	bl func_8009E0D4
/* 8006DB30 0006A710  80 7E 00 00 */	lwz r3, 0(r30)
/* 8006DB34 0006A714  48 00 8A 79 */	bl func_800765AC
/* 8006DB38 0006A718  80 7E 00 00 */	lwz r3, 0(r30)
/* 8006DB3C 0006A71C  48 01 B1 21 */	bl func_80088C5C
/* 8006DB40 0006A720  38 7E 20 A4 */	addi r3, r30, 0x20a4
/* 8006DB44 0006A724  4B FA 13 49 */	bl func_8000EE8C
/* 8006DB48 0006A728  80 7E 20 A0 */	lwz r3, 0x20a0(r30)
/* 8006DB4C 0006A72C  28 03 00 00 */	cmplwi r3, 0
/* 8006DB50 0006A730  41 82 00 08 */	beq lbl_8006DB58
/* 8006DB54 0006A734  48 30 3A 3D */	bl HSD_JObjRemoveAll
lbl_8006DB58:
/* 8006DB58 0006A738  80 7E 08 AC */	lwz r3, 0x8ac(r30)
/* 8006DB5C 0006A73C  48 30 3A 35 */	bl HSD_JObjRemoveAll
/* 8006DB60 0006A740  80 7E 21 84 */	lwz r3, 0x2184(r30)
/* 8006DB64 0006A744  48 30 35 F9 */	bl HSD_JObjUnref
/* 8006DB68 0006A748  7F C3 F3 78 */	mr r3, r30
/* 8006DB6C 0006A74C  48 01 7E 3D */	bl func_800859A8
/* 8006DB70 0006A750  80 7E 05 88 */	lwz r3, 0x588(r30)
/* 8006DB74 0006A754  48 2F 90 61 */	bl func_80366BD4
/* 8006DB78 0006A758  88 9E 22 1F */	lbz r4, 0x221f(r30)
/* 8006DB7C 0006A75C  88 7E 00 0C */	lbz r3, 0xc(r30)
/* 8006DB80 0006A760  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 8006DB84 0006A764  4B FC 44 2D */	bl Player_80031FB0
/* 8006DB88 0006A768  38 7F 00 DC */	addi r3, r31, 0xdc
/* 8006DB8C 0006A76C  80 9E 05 9C */	lwz r4, 0x59c(r30)
/* 8006DB90 0006A770  48 30 D1 91 */	bl HSD_ObjFree
/* 8006DB94 0006A774  38 7F 00 DC */	addi r3, r31, 0xdc
/* 8006DB98 0006A778  80 9E 05 A0 */	lwz r4, 0x5a0(r30)
/* 8006DB9C 0006A77C  48 30 D1 85 */	bl HSD_ObjFree
/* 8006DBA0 0006A780  38 7F 00 58 */	addi r3, r31, 0x58
/* 8006DBA4 0006A784  80 9E 05 E8 */	lwz r4, 0x5e8(r30)
/* 8006DBA8 0006A788  48 30 D1 79 */	bl HSD_ObjFree
/* 8006DBAC 0006A78C  38 7F 00 84 */	addi r3, r31, 0x84
/* 8006DBB0 0006A790  80 9E 05 F0 */	lwz r4, 0x5f0(r30)
/* 8006DBB4 0006A794  48 30 D1 6D */	bl HSD_ObjFree
/* 8006DBB8 0006A798  38 7F 00 B0 */	addi r3, r31, 0xb0
/* 8006DBBC 0006A79C  80 9E 20 40 */	lwz r4, 0x2040(r30)
/* 8006DBC0 0006A7A0  48 30 D1 61 */	bl HSD_ObjFree
/* 8006DBC4 0006A7A4  38 7F 00 2C */	addi r3, r31, 0x2c
/* 8006DBC8 0006A7A8  80 9E 02 D8 */	lwz r4, 0x2d8(r30)
/* 8006DBCC 0006A7AC  48 30 D1 55 */	bl HSD_ObjFree
/* 8006DBD0 0006A7B0  38 7F 00 00 */	addi r3, r31, 0
/* 8006DBD4 0006A7B4  38 9E 00 00 */	addi r4, r30, 0
/* 8006DBD8 0006A7B8  48 30 D1 49 */	bl HSD_ObjFree
/* 8006DBDC 0006A7BC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8006DBE0 0006A7C0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8006DBE4 0006A7C4  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8006DBE8 0006A7C8  38 21 00 18 */	addi r1, r1, 0x18
/* 8006DBEC 0006A7CC  7C 08 03 A6 */	mtlr r0
/* 8006DBF0 0006A7D0  4E 80 00 20 */	blr  
}
