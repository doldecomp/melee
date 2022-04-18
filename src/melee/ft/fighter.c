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

extern void (*ft_OnAbsorb[33])(HSD_GObj* obj);
extern struct Pair_Pointer_and_Flag lbl_803C0EC0[33];

extern ftData* lbl_804598B8[33];
extern struct S_TEMP3 lbl_803C2800[33];
extern struct S_TEMP3* lbl_803C12E0[33];

extern s32 lbl_803C125C;
extern void (*lbl_803C1DB4[33])(HSD_GObj* obj);
extern s8 lbl_803C26FC[33];

extern HSD_ObjAllocData lbl_804590AC; // from ft/ftparts.s
extern HSD_ObjAllocData lbl_80458FD0;
extern HSD_ObjAllocData lbl_80458FFC;

extern HSD_PadStatus HSD_PadRumbleData[4];

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

////https://decomp.me/scratch/nnPbg   MATCH!!!!!

void func_80067C98(Fighter* ft) {
	Vec3 spC_player_coord;
	f32 x,y,z;
	Fighter* tmp;

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
	ft->dmg.x1830_percent = Player_GetDamage(ft->xC_playerID);

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

    ft->x2150 = 
	ft->x2154 = 
	ft->x2158 = 
	ft->x215C = 
	ft->x2160 = 
	ft->x2144 = 
	ft->x2148 =   
	ft->x214C = -1;
    
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


	tmp = ft;

	ft->x1A40 = 0.0f;//lbl_804D8254
	// -> mr r3, ft

	ft->x1A44 = 0;
	ft->x1A48 = 0;

	ft->x68C_transNPos.z= 0.0f;
	ft->x68C_transNPos.y= 0.0f;
	ft->x68C_transNPos.x= 0.0f;
	ft->x6A4_transNOffset.z= 0.0f;
	ft->x6A4_transNOffset.y= 0.0f;
	ft->x6A4_transNOffset.x= 0.0f;
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

    fighter->x620_lstick_x = 
    fighter->x624_lstick_y = 
    fighter->x628 = 
    fighter->x62C = 0.0f;

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

    fighter->x672 = 0xFE;
    fighter->x671_timer_lstick_tilt_y = 0xFE;
    fighter->x670_timer_lstick_tilt_x = 0xFE;

    fighter->x675 = 0xFE;
    fighter->x674_y = 0xFE;
    fighter->x673_x = 0xFE;

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
        temp_r3_s2 = &p_ftCommonData->x6DC[temp_r3 - 1];
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
    temp_r6->x628 = 
    temp_r6->x62C = 0.0f;

    temp_r6->x660 = 0;
    temp_r6->x66C = 0;
    temp_r6->x668 = 0;
    temp_r6->x65C = 0;

    
    temp_r6->x679_x = 
    temp_r6->x67A_y = 
    temp_r6->x67B = 

    temp_r6->x676_x = 
    temp_r6->x677_y = 
    temp_r6->x678 = 

    temp_r6->x673_x = 
    temp_r6->x674_y = 
    temp_r6->x675 = 

    temp_r6->x670_timer_lstick_tilt_x = 
    temp_r6->x671_timer_lstick_tilt_y = 
    temp_r6->x672 = 0xFE;


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

/// https://decomp.me/scratch/8824p
void func_8006A1BC(HSD_GObj* fighterObj) {
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

// inline s32 checkItem_func_800C511C(struct _HSD_GObj* item, struct _HSD_GObj* fighterObj)
// {
//     if (itGetKind(item) != 0x1C) {
//         return 0;
//     } else {
//         func_800C511C(fighterObj);
//     }
// }

//// https://decomp.me/scratch/6uj7U
void func_8006A360(HSD_GObj* fighterObj, s32 unused) {
    
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
                Fighter_TakeDamage_8006CC7C(fighter, p_ftCommonData->x6F4);
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
                if (!fighter->x2226_flag.bits.b3 && fighter->x2030 == p_ftCommonData->x7D0 && func_800C8B2C(fighter, 0x7D, 0) != 0) {
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
            if (fighter->dmg.x1830_percent < (f32)  p_ftCommonData->x7B0) {
                if (func_802FC998(fighter->xC_playerID) && (Player_GetMoreFlagsBit3(fighter->xC_playerID) != 0)) {
                    fighter->dmg.x1910++;
                } else {
                    fighter->dmg.x1910 = 0;
                }

                if (fighter->dmg.x1910 >= p_ftCommonData->x7AC) {
                    Fighter_TakeDamage_8006CC7C(fighter, p_ftCommonData->x7B4);
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

        if (fighter->cb.x21CC_callback_x21cc) {
            fighter->cb.x21CC_callback_x21cc(fighterObj);
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

/// https://decomp.me/scratch/Y9c4V
void func_8006ABA0(HSD_GObj* fighterObj) {
    Fighter* fp = fighterObj->user_data;
    if ((fp->x221F_flag.bits.b3 == 0) && (func_800A2040() != 0)) {
        func_800B3900(fighterObj);
    }
}


//https://decomp.me/scratch/A7CgG
void func_8006ABEC(HSD_GObj* fighterObj) {
    
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

/// https://decomp.me/scratch/lKwFH
void func_8006AD10(HSD_GObj* fighterObj) {

    s32 unused[10];
    Fighter* fighter = fighterObj->user_data;

    if (!fighter->x221F_flag.bits.b3) {
        if (!fighter->x2224_flag.bits.b2) {
            s32 temp0;
            s32 temp1;
            s32 temp2; 

            f32 tempf1;
            f32 tempf0;
            
            if (!fighter->x221D_flag.bits.b3) {
                fighter->x628 = fighter->x630;
                fighter->x62C = fighter->x634;
                fighter->x640 = fighter->x648;
                fighter->x644 = fighter->x64C;
                fighter->x654 = fighter->x658;
                fighter->x660 = fighter->x664;
                fighter->x221D_flag.bits.b3 = 1;
            } else {
                fighter->x628 = fighter->x620_lstick_x;
                fighter->x62C = fighter->x624_lstick_y;
                fighter->x640 = fighter->x638;
                fighter->x644 = fighter->x63C;
                fighter->x654 = fighter->x650;
                fighter->x660 = fighter->x65C;
            }

            if (func_800A2040(fighter)) {

                fighter->x620_lstick_x = func_800A17E4(fighter);
                fighter->x624_lstick_y = func_800A1874(fighter);
                if (g_debugLevel < 3  &&  func_8016B41C() == 0) {
                    fighter->x638 = func_800A1994(fighter);
                    fighter->x63C = func_800A1A24(fighter);
                }
                else {
                    fighter->x638 = 0.0f;
                    fighter->x63C = 0.0f;
                }

                tempf0 = func_800A1904(fighter);
                tempf1 = func_800A1948(fighter);

                fighter->x650 = (tempf0> tempf1) ? tempf0 : tempf1;

            } else {

                fighter->x620_lstick_x = HSD_PadRumbleData[fighter->x618_player_id].nml_stickX;
                fighter->x624_lstick_y = HSD_PadRumbleData[fighter->x618_player_id].nml_stickY;

                if (g_debugLevel < 3  &&  func_8016B41C() == 0) {
                    fighter->x638 = HSD_PadRumbleData[fighter->x618_player_id].nml_subStickX;
                    fighter->x63C = HSD_PadRumbleData[fighter->x618_player_id].nml_subStickY;
                } else {
                    fighter->x638 = 0.0f;
                    fighter->x63C = 0.0f;
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

            if (fabs_inline(fighter->x638) <= p_ftCommonData->x0) {
                fighter->x638 = 0.0f;
            }
            
            if (fabs_inline(fighter->x63C) <= p_ftCommonData->x4) {
                fighter->x63C = 0.0f;
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

            if (fighter->x620_lstick_x >= p_ftCommonData->x8) {
                if (fighter->x628 >= p_ftCommonData->x8) {
                    fighter->x670_timer_lstick_tilt_x++;
                    if (fighter->x670_timer_lstick_tilt_x > 0xFE) {
                        fighter->x670_timer_lstick_tilt_x = 0xFE;
                    }
                    fighter->x673_x++;
                    if (fighter->x673_x > 0xFE) {
                        fighter->x673_x = 0xFE;
                    }
                    fighter->x679_x++;
                    if (fighter->x679_x > 0xFE) {
                        fighter->x679_x = 0xFE;
                    }
                } else {
                    fighter->x676_x = 0;
                    fighter->x673_x = 0;
                    fighter->x670_timer_lstick_tilt_x = 0;
                    fighter->x2228_flag.bits.b7 = 1;
                }
            } else if (fighter->x620_lstick_x <= -p_ftCommonData->x8) {
                if (fighter->x628 <= -p_ftCommonData->x8) {
                    fighter->x670_timer_lstick_tilt_x++;
                    if (fighter->x670_timer_lstick_tilt_x > 0xFE) {
                        fighter->x670_timer_lstick_tilt_x = 0xFE;
                    }
                    fighter->x673_x++;
                    if (fighter->x673_x > 0xFE) {
                        fighter->x673_x = 0xFE;
                    }
                    fighter->x679_x++;
                    if (fighter->x679_x > 0xFE) {
                        fighter->x679_x = 0xFE;
                    }
                } else {
                    fighter->x676_x = 0;
                    fighter->x673_x = 0;
                    fighter->x670_timer_lstick_tilt_x = 0;
                    fighter->x2228_flag.bits.b7 = 0;
                }
            } else {
                fighter->x679_x = 0xFEU;
                fighter->x673_x = 0xFEU;
                fighter->x670_timer_lstick_tilt_x = 0xFEU;
            }
        

            fighter->x677_y++;
            if (fighter->x677_y > 0xFE) {
                fighter->x677_y = 0xFE;
            }
            
            if (fighter->x624_lstick_y >= p_ftCommonData->xC) {
                if (fighter->x62C >= p_ftCommonData->xC) {
                    fighter->x671_timer_lstick_tilt_y++;
                    if (fighter->x671_timer_lstick_tilt_y > 0xFE) {
                        fighter->x671_timer_lstick_tilt_y = 0xFE;
                    }
                    fighter->x674_y++;
                    if (fighter->x674_y > 0xFE) {
                        fighter->x674_y = 0xFE;
                    }
                    fighter->x67A_y++;
                    if (fighter->x67A_y > 0xFE) {
                        fighter->x67A_y = 0xFE;
                    }
                } else {
                    fighter->x677_y = 0;
                    fighter->x674_y = 0;
                    fighter->x671_timer_lstick_tilt_y = 0;
                    fighter->x2229_b0 = 0;
                }
            } else if (fighter->x624_lstick_y <= -p_ftCommonData->xC) {
                if (fighter->x62C <= -p_ftCommonData->xC) {
                    fighter->x671_timer_lstick_tilt_y++;
                    if (fighter->x671_timer_lstick_tilt_y > 0xFE) {
                        fighter->x671_timer_lstick_tilt_y = 0xFE;
                    }
                    fighter->x674_y++;
                    if (fighter->x674_y > 0xFE) {
                        fighter->x674_y = 0xFE;
                    }
                    fighter->x67A_y++;
                    if (fighter->x67A_y > 0xFE) {
                        fighter->x67A_y = 0xFE;
                    }
                } else {
                    fighter->x677_y = 0;
                    fighter->x674_y = 0;
                    fighter->x671_timer_lstick_tilt_y = 0;
                    fighter->x2229_b0 = 1;
                }
            } else {
                fighter->x67A_y = 0xFE;
                fighter->x674_y = 0xFE;
                fighter->x671_timer_lstick_tilt_y = 0xFE;
            }
        
    
    
    
            if (func_8000D148(fighter->x628, fighter->x62C, fighter->x620_lstick_x, fighter->x624_lstick_y, 0.0f, 0.0f, p_ftCommonData->x8)) {
                fighter->x67A_y = 0;
                fighter->x679_x = 0;
            }
        
            fighter->x678++;
            if (fighter->x678 > 0xFE) {
                fighter->x678 = 0xFE;
            }
        
            if (fighter->x650 >= p_ftCommonData->x18) {
                if (fighter->x654 >= p_ftCommonData->x18) {
                    fighter->x672++;
                    if (fighter->x672 > 0xFE) {
                        fighter->x672 = 0xFE;
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
                    fighter->x672 = 0;
                }
            } else {
                fighter->x67B = 0xFE;
                fighter->x675 = 0xFE;
                fighter->x672 = 0xFE;
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
            fighter->x648 = fighter->x638;
            fighter->x64C = fighter->x63C;
            fighter->x658 = fighter->x650;
            fighter->x664 = fighter->x65C;
            fighter->x221D_flag.bits.b3 = 0;
    
            same_fighter = fighterObj->user_data;
    
            same_fighter->x650 = 
            same_fighter->x654 = 
            same_fighter->x638 = 
            same_fighter->x63C = 
            same_fighter->x640 = 
            same_fighter->x644 = 
            same_fighter->x620_lstick_x = 
            same_fighter->x624_lstick_y = 
            same_fighter->x628 = 
            same_fighter->x62C = 0.0f;
    
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
            same_fighter->x673_x = 
            same_fighter->x674_y = 
            same_fighter->x675 = 
            same_fighter->x670_timer_lstick_tilt_x = 
            same_fighter->x671_timer_lstick_tilt_y =         
            same_fighter->x672 = 0xFE;
    
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
            func_8006ABEC(fighterObj);
    
            if (fighter->cb.x219C_callback_IASA) {
                fighter->cb.x219C_callback_IASA(fighterObj);
            }
        }

    }
    
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
    s32 temp_r28 = fighter->x10;
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
            if (fighter->x1998_shieldHealth < p_ftCommonData->x260) {
                fighter->x1998_shieldHealth += p_ftCommonData->x27C;
                if (fighter->x1998_shieldHealth > p_ftCommonData->x260) {
                    fighter->x1998_shieldHealth = p_ftCommonData->x260;
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
                        __assert("fighter.c", 3085, "0");
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
