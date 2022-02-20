#include "fighter.h"

#include "functions.h"
#include "sysdolphin/baselib/gobjgxlink.h"
#include "sysdolphin/baselib/gobj.h"
#include "sysdolphin/baselib/jobj.h"
#include "sysdolphin/baselib/gobjuserdata.h"
#include "melee/gr/stage.h"
#include "melee/pl/player.h"

// TODO: put this in functions.h, same for ftkoopa.c
extern void* func_8007E2F4(); // ftcommon.s

#include "sysdolphin/baselib/controller.h"
extern HSD_RumbleData HSD_PadRumbleData[4];

// include random.h for HSD_Randi(s32 max_val)
#include <sysdolphin/baselib/random.h>

extern char* stage_info;

// @ha @l labels
extern s32 lbl_803C0EC0; // ft/code_8008521C.s

// TODO: rename lbl_803C10D0 to something like func_ptrs
typedef void (*fn_ptr_t)();
extern fn_ptr_t lbl_803C10D0[33]; // ft/code_8008521C.s

extern s32 lbl_803C125C; // asm/melee/ft/code_8008521C.s
extern s32 lbl_803C12E0; // asm/melee/ft/code_8008521C.s
extern s32 lbl_803C1DB4; // asm/melee/ft/code_8008521C.s
extern s32 lbl_803C26FC; // asm/melee/ft/code_8008521C.s
extern s32 lbl_803C2800; // asm/melee/ft/code_8008521C.s
extern HSD_ObjAllocData lbl_804590AC; // ft/ftparts.s
extern s32 lbl_804598B8; // asm/melee/ft/code_8008521C.s

extern void* ft_OnAbsorb; // asm/melee/ft/code_8008521C.s

// lbl_xxx(r13) labels
extern s32 lbl_804D4A08;
extern u8 lbl_804D7849;

void HSD_JObjSetMtxDirtySub(HSD_JObj*); // sysdolphin/baselib/jobj.s
void HSD_JObjRemoveAll(HSD_JObj*); // sysdolphin/baselib/jobj.s
void ft_OnDeath(); // asm/melee/ft/code_8008521C.s
void ft_OnLoad(); // asm/melee/ft/code_8008521C.s
void PSVECAdd(Vec3* a, Vec3* b, Vec3* result); // asm/dolphin/mtx/vec.s
void PSMTXConcat(); // asm/dolphin/mtx/mtx.s
void* HSD_JObjGetMtxPtr(); // asm/melee/lb/lbcollision.s
void* HSD_JObjSetupMatrixSub(); // asm/sysdolphin/baselib/jobj.s
void* HSD_JObjAnimAll(); // asm/sysdolphin/baselib/jobj.s


// .section .rodata

extern const Vec3 lbl_803B7488; // = (0,0,0)
extern const Vec3 lbl_803B7494; // = (0,0,0)

// .section .data

char lbl_803C0530[] = "PlCo.dat";
char lbl_803C053C[] = "ftLoadCommonData";
char lbl_803C0550[] = "translate";
char lbl_803C055C[] = "fighter sub color num over!\n";
char lbl_803C057C[] = "fighter.c";
char lbl_803C0588[] = "ellegal flag fp->no_normal_motion\n";
char lbl_803C05AC[];
    //.asciz "fighter procUpdate pos error.\tpos.x=%f\tpos.y=%f\n"
    //.balign 4
    //.asciz "fighter procMap pos error.\tpos.x=%f\tpos.y=%f\n"
    //.balign 4
char lbl_803C0610[];// = "ellegal flag fp->no_reaction_always\n";

// .section .bss, "wa"

extern HSD_ObjAllocData lbl_80458FD0;
extern HSD_ObjAllocData lbl_80458FFC;

// .section .sdata

extern const char* lbl_804D3A00;// = "jobj.h";
extern const char* lbl_804D3A08;// = "jobj";
extern const char* lbl_804D3A10;// = "0";
    //.asciz "0"
    //.balign 4
    //.4byte NULL

// .section .sbss

u32 lbl_804D64F8 = 0; // spawn number

// the following seems to be an array, initialized in reverse in func_80067ABC
s32 lbl_804D64FC = 0;
s32 lbl_804D6500 = 0;
s32 lbl_804D6504 = 0;
s32 lbl_804D6508 = 0;
s32 lbl_804D650C = 0;
s32 lbl_804D6510 = 0;
s32 lbl_804D6514 = 0;
s32 lbl_804D6518 = 0;
s32 lbl_804D651C = 0;
s32 lbl_804D6520 = 0;
s32 lbl_804D6524 = 0;
s32 lbl_804D6528 = 0;
s32 lbl_804D652C = 0;
s32 lbl_804D6530 = 0;
s32 lbl_804D6534 = 0;
s32 lbl_804D6538 = 0;
s32 lbl_804D653C = 0;
s32 lbl_804D6540 = 0;
s32 lbl_804D6544 = 0;
s32 lbl_804D6548 = 0;
s32 lbl_804D654C = 0;
s32 lbl_804D6550 = 0;
s32 lbl_804D6554 = 0; // struct or f32[] pointer
 
// .section .sdata2
 
extern const f32 lbl_804D8250;// = 1.0f;
extern const f32 lbl_804D8254;// = 0.0f;
extern const f32 lbl_804D8258;// = [-1.0, 0.0];
extern const f32 lbl_804D8260;// used for int to float casting
extern const f64 lbl_804D8268;// = [8.55, 0.0];
extern const f64 lbl_804D8270;// = 1.5707963267948966;
extern const f32 lbl_804D8278;// probably also used for int to float casting
extern const f64 lbl_804D8280;// = 0.5; // = [1.75, 0.0];
extern const f64 lbl_804D8288;// = 3.0;
extern const f32 lbl_804D8290;//[2] = [999.0, 0.0];

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

	lbl_804D64F8 = 1;

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
void func_80067ABC()
{
    s32* pData;
    func_80016C64(lbl_803C0530, &pData, lbl_803C053C, 0); // from lbarchive.s

	// copy 23 4-byte chunks from pData to lbl_804D6554 in reverse order
	// Would be nice to find a less repetitive way for this, loop unrolling only works up to 8 iterations.
	//for(i=0; i<23; i++)
	//   (&lbl_804D64FC)[23-1-i] = pData[i];
	lbl_804D6554 = pData[0];
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

#ifdef FIGHTER_DONE
// https://decomp.me/scratch/1sx2v
void func_80067BB4(HSD_GObj* pPlayerEntity)
{
	Vec3 scale_sp14;
	s32 dummy[2];
	//@14
	Fighter* pFighter = pPlayerEntity->user_data;//x2c r31
	//@18
	HSD_JObj* jobj = pPlayerEntity->hsd_obj;//x28 r30
	//@1c
	f32 modelScale_f1 = func_8007F694(pFighter); //PlayerLoadModelScale
	//@24
	if (pFighter->x34_scale.z != /*1.0f*/lbl_804D8250)
		scale_sp14.x = pFighter->x34_scale.z;
	else
		scale_sp14.x = modelScale_f1;
	//@40
	scale_sp14.y = modelScale_f1;
	scale_sp14.z = modelScale_f1;
	//@44,4c...
	if (jobj == 0U)
		__assert("jobj.h"/*lbl_804D3A00*/, /*line*/0x2F8, "jobj"/*lbl_804D3A08*/);
	//@60
	jobj->x2C_scale = scale_sp14;
	//@78
	if ((jobj->x14_flags & 0x02000000) == 0)
	{
		//@84
		if (jobj)
		{
			//@8c
			if (jobj == 0)
				__assert("jobj.h"/*lbl_804D3A00*/, 0x234, "jobj"/*lbl_804D3A08*/);
			//@a0
			if ((!(jobj->x14_flags & 0x800000) && (jobj->x14_flags & 0x40)) == 0)
				HSD_JObjSetMtxDirtySub(jobj);
		}
	}
}
#else
asm void func_80067BB4()
{
	nofralloc
/* 80067BB4 00064794  7C 08 02 A6 */	mflr r0
/* 80067BB8 00064798  90 01 00 04 */	stw r0, 4(r1)
/* 80067BBC 0006479C  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80067BC0 000647A0  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80067BC4 000647A4  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80067BC8 000647A8  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80067BCC 000647AC  83 C3 00 28 */	lwz r30, 0x28(r3)
/* 80067BD0 000647B0  7F E3 FB 78 */	mr r3, r31
/* 80067BD4 000647B4  48 01 7A C1 */	bl func_8007F694
/* 80067BD8 000647B8  C0 02 88 70 */	lfs f0, lbl_804D8250(r2)
/* 80067BDC 000647BC  C0 5F 00 3C */	lfs f2, 0x3c(r31)
/* 80067BE0 000647C0  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 80067BE4 000647C4  41 82 00 0C */	beq lbl_80067BF0
/* 80067BE8 000647C8  D0 41 00 14 */	stfs f2, 0x14(r1)
/* 80067BEC 000647CC  48 00 00 08 */	b lbl_80067BF4
lbl_80067BF0:
/* 80067BF0 000647D0  D0 21 00 14 */	stfs f1, 0x14(r1)
lbl_80067BF4:
/* 80067BF4 000647D4  D0 21 00 18 */	stfs f1, 0x18(r1)
/* 80067BF8 000647D8  28 1E 00 00 */	cmplwi r30, 0
/* 80067BFC 000647DC  D0 21 00 1C */	stfs f1, 0x1c(r1)
/* 80067C00 000647E0  40 82 00 14 */	bne lbl_80067C14
/* 80067C04 000647E4  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 80067C08 000647E8  38 80 02 F8 */	li r4, 0x2f8
/* 80067C0C 000647EC  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 80067C10 000647F0  48 32 06 11 */	bl __assert
lbl_80067C14:
/* 80067C14 000647F4  80 61 00 14 */	lwz r3, 0x14(r1)
/* 80067C18 000647F8  80 01 00 18 */	lwz r0, 0x18(r1)
/* 80067C1C 000647FC  90 7E 00 2C */	stw r3, 0x2c(r30)
/* 80067C20 00064800  90 1E 00 30 */	stw r0, 0x30(r30)
/* 80067C24 00064804  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80067C28 00064808  90 1E 00 34 */	stw r0, 0x34(r30)
/* 80067C2C 0006480C  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 80067C30 00064810  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 80067C34 00064814  40 82 00 4C */	bne lbl_80067C80
/* 80067C38 00064818  28 1E 00 00 */	cmplwi r30, 0
/* 80067C3C 0006481C  41 82 00 44 */	beq lbl_80067C80
/* 80067C40 00064820  40 82 00 14 */	bne lbl_80067C54
/* 80067C44 00064824  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 80067C48 00064828  38 80 02 34 */	li r4, 0x234
/* 80067C4C 0006482C  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 80067C50 00064830  48 32 05 D1 */	bl __assert
lbl_80067C54:
/* 80067C54 00064834  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 80067C58 00064838  38 60 00 00 */	li r3, 0
/* 80067C5C 0006483C  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80067C60 00064840  40 82 00 10 */	bne lbl_80067C70
/* 80067C64 00064844  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80067C68 00064848  41 82 00 08 */	beq lbl_80067C70
/* 80067C6C 0006484C  38 60 00 01 */	li r3, 1
lbl_80067C70:
/* 80067C70 00064850  2C 03 00 00 */	cmpwi r3, 0
/* 80067C74 00064854  40 82 00 0C */	bne lbl_80067C80
/* 80067C78 00064858  7F C3 F3 78 */	mr r3, r30
/* 80067C7C 0006485C  48 30 B6 6D */	bl HSD_JObjSetMtxDirtySub
lbl_80067C80:
/* 80067C80 00064860  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80067C84 00064864  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80067C88 00064868  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80067C8C 0006486C  38 21 00 28 */	addi r1, r1, 0x28
/* 80067C90 00064870  7C 08 03 A6 */	mtlr r0
/* 80067C94 00064874  4E 80 00 20 */	blr 
}
#endif

#ifdef WONT_COMPILE
// one addi r3,r27,0 should be a mr r3,r27, and it should be in a different place. 100% match otherwise.
// https://decomp.me/scratch/HXrlP
void func_800C88A0(Fighter*);
void func_800DEEA8(HSD_GObj* fighter);

//const f32 lbl_804D8250 = 1.0f;
//const f32 lbl_804D8254 = 0.0f;
//const f32 lbl_804D8258 = -1.0f;

void func_80067C98(Fighter* r27)
{
	Vec3 spC_player_coord;
	f32 x,y,z;

	r27->x8_spawnNum = func_80068E40();
	Player_800326CC(r27->xC_playerID, &spC_player_coord); //PlayerBlock_LoadPlayerCoords_StoreToR4
	r27->x2C_facing_direction = Player_GetFacingDirection(r27->xC_playerID); // PlayerBlock_LoadFacingDirection

	spC_player_coord.x = r27->x2C_facing_direction * func_800804EC(r27) + spC_player_coord.x;
	x = spC_player_coord.x;
	r27->xB0_pos.x = x;
	r27->xBC_prevPos.x = x;

	y = spC_player_coord.y;
	r27->xB0_pos.y = y;
	r27->xBC_prevPos.y = y;

	z = spC_player_coord.z;
	r27->xB0_pos.z = z;
	r27->xBC_prevPos.z = z;

	r27->x30_facingDirectionRepeated = r27->x2C_facing_direction;
	r27->x34_scale.y = r27->x34_scale.x;

	r27->x2220_flag.bits.b5 = 0;
	r27->x2220_flag.bits.b6 = 0;

	r27->x200C = 0;
	r27->x2010 = 0;
	r27->x2008 = 0;

	r27->x2219_flag.bits.b1 = 0;
	r27->x2219_flag.bits.b2 = 0;
	r27->x2219_flag.bits.b3 = 0;
	r27->x2219_flag.bits.b4 = 0;
	r27->x221A_flag.bits.b5 = 0;
	r27->x221A_flag.bits.b6 = 0;
	r27->x221D_2 = 0;
	r27->x221E_flag.bits.b7 = 0;
	r27->x2220_flag.bits.b7 = 0;
	r27->x2221_flag.bits.b4 = 0;
	r27->x2221_flag.bits.b5 = 0;
	r27->x2221_flag.bits.b6 = 1;
	r27->x2221_flag.bits.b7 = 0;

	r27->x61D = 255;

	r27->xC8_pos_delta.z /*xD0*/ = 0.0f;//lbl_804D8254
	r27->xC8_pos_delta.y /*xCC*/ = 0.0f;//lbl_804D8254
	r27->xC8_pos_delta.x = 0.0f;//lbl_804D8254
	r27->x894_animFrame = 0.0f;//lbl_804D8254
	r27->x898_animUnk = 0.0f;//lbl_804D8254

	r27->x89C_animRate = 1.0f;//lbl_804D8250
	r27->x8A0_animUnk = 1.0f;//lbl_804D8250
	r27->x1850_forceApplied = 0.0f;//lbl_804D8254
	r27->x18A4_knockbackMagnitude = 0.0f;//lbl_804D8254
	r27->x18A8 = 0.0f;//lbl_804D8254
	r27->x18AC_timeSinceHit = -1;
	r27->x18B0 = 0.0f;//lbl_804D8254
	r27->x18B4_armor = 0.0f;//lbl_804D8254
	r27->x1828 = 0;

	r27->x221C_6_hitstun = 0;

	r27->x18A0 = 0.0f;//lbl_804D8254
	r27->x1968_jumpsUsed = 0;
	r27->x1969_walljumpUsed = 0;
	r27->x196C_hitlagMult = 0.0f;//lbl_804D8254
	r27->x2064_ledgeCooldown = 0;

	//@1b4
	r27->x1830_percent = (f32) Player_GetDamage(r27->xC_playerID);

	r27->x1838_percentTemp = 0.0f;//lbl_804D8254

	r27->x183C = 0;
	r27->x18C0 = 0;

	r27->x18C4 = 6;
	r27->x18C8 = -1;
	r27->x18F0 = 0;
	r27->x18CC = 0;
	r27->x18D0 = -10;

	r27->x221F_flag.bits.b5 = 0;
	r27->x2221_flag.bits.b1 = 0;

	r27->x18F4 = 0;
	r27->x18F8 = 1;
	r27->x18FA = 0;
	r27->x18FD = 0;
	r27->x18FC = 0;
	r27->x1834 = 0.0f;//lbl_804D8254

	r27->x2222_flag.bits.b2 = 0;

	r27->x1840 = 0;

	r27->x2219_flag.bits.b5 = 0; // freeze bit?
	r27->x2219_flag.bits.b6 = 0;
	r27->x2219_flag.bits.b7 = 0;
	r27->x221A_flag.bits.b0 = 0;
	r27->x221A_flag.bits.b1 = 0;

	r27->x1954 = 0.0f;//lbl_804D8254
	r27->x1958 = 0.0f;//lbl_804D8254

	r27->x221A_flag.bits.b2 = 0;

	r27->x195C_hitlagFrames = 0.0f;//lbl_804D8254

	r27->x221A_flag.bits.b3 = 0;
	r27->x1960_vibrateMult = 1.0f;//lbl_804D8250
	r27->x1964 = 0.0f;//lbl_804D8254
	r27->x189C = 0.0f;//lbl_804D8254

	r27->x2220_flag.bits.b3 = 0;
	r27->x2220_flag.bits.b4 = 0;

	r27->x1914 = 0;
	r27->x1918 = 0;
	r27->x191C = 0.0f;//lbl_804D8254
	r27->x1924 = 0;
	r27->x1928 = 0.0f;//lbl_804D8254

	r27->x2223_flag.bits.b5 = 0;

	r27->x1950 = 0;
	r27->x1948 = 0;

	r27->x2223_flag.bits.b4 = 0;

	r27->xF8_playerNudgeVel.y/*FC*/ = 0.0f;//lbl_804D8254
	r27->xF8_playerNudgeVel.x/*F8*/ = 0.0f;//lbl_804D8254
	r27->x100 = -1.0f;//lbl_804D8258;

	r27->x2222_flag.bits.b7 = 0;
	r27->x2223_flag.bits.b0 = 0;
	r27->x221A_flag.bits.b4 = 0;
	r27->x2219_flag.bits.b0 = 0;

	r27->x20A0 = 0;
	r27->x2210_ThrowFlags.flags = 0;
	r27->x2214 = 0.0f;//lbl_804D8254
	r27->x1974_heldItem = 0;
	r27->x1978 = 0;

	r27->x221E_flag.bits.b3 = 1;

	r27->x1984_heldItemSpec = 0;
	r27->x1988 = 0;
	r27->x198C = 0;

	r27->x2221_flag.bits.b0 = 0;

	r27->x1990 = 0;
	r27->x1994 = 0;

	r27->x221D_6 = 0;
	r27->x221B_flag.bits.b5 = 0;

	r27->x1A58 = 0;
	r27->x1A5C = 0;

	r27->x221B_flag.bits.b6 = 0;

	r27->x1A60 = 0;
	r27->x1A64 = 0;

	r27->x221B_flag.bits.b7 = 0;
	r27->x221C_0 = 0;

	r27->x1064_thrownHitbox.x134 /*x1198*/ = 0;
	r27->x221C_u16_y = 0;
	r27->x20AC = 0;
	r27->x221C_5 = 0;

	r27->x214C = -1;
	r27->x2148 = -1;
	r27->x2144 = -1;
	r27->x2160 = -1;
	r27->x215C = -1;
	r27->x2158 = -1;
	r27->x2154 = -1;
	r27->x2150 = -1;
	r27->x2168 = 0;
	r27->x2164 = 0;
	r27->x208C = 0;
	r27->x2090 = 0;
	r27->x2098 = 0;
	r27->x2092 = 0;
	r27->x2094 = 0;
	r27->x1998_shieldHealth = ((f32*)lbl_804D6554)[0x260/sizeof(f32)];

	r27->x221A_flag.bits.b7 = 0;
	r27->x221B_flag.bits.b0 = 0;
	r27->x221B_flag.bits.b1 = 0;
	r27->x221B_flag.bits.b3 = 0;
	r27->x221B_flag.bits.b4 = 0;
	r27->x221C_3 = 0;
	r27->x221C_1 = 0;

	r27->x19A0_shieldDamageTaken = 0;
	r27->x19A4_shieldDamageTaken2 = 0;
	r27->x199C_shieldLightshieldAmt = 0.0f;//lbl_804D8254
	r27->x19A8_shieldDamageSource = 0;
	r27->x19B4_shieldUnk = 0.0f;//lbl_804D8254
	r27->x19B8_shieldUnk = 0.0f;//lbl_804D8254
	r27->x19BC_shieldDamageTaken3 = 6;

	r27->x221F_flag.bits.b6 = 0;
	r27->x2218_flag.bits.b3 = 0;
	r27->x2218_flag.bits.b4 = 0;
	r27->x1A3C = 0;
	r27->x1A2C_reflectHitDirection = 0.0f;//lbl_804D8254
	r27->x2218_flag.bits.b6 = 0; // addi r3, r27, 0
	r27->x2218_flag.bits.b7 = 0;

	r27->x1A40 = 0.0f;//lbl_804D8254
	// -> mr r3, r27
	r27->x1A44 = 0;
	r27->x1A48 = 0;

	r27->x68C_transNPos.z/*x694*/ = 0.0f;//lbl_804D8254
	r27->x68C_transNPos.y/*x690*/ = 0.0f;//lbl_804D8254
	r27->x68C_transNPos.x/*x68C*/ = 0.0f;//lbl_804D8254
	r27->x6A4_transNOffset.z/*x6AC*/ = 0.0f;//lbl_804D8254
	r27->x6A4_transNOffset.y/*x6A8*/ = 0.0f;//lbl_804D8254
	r27->x6A4_transNOffset.x/*x6A4*/ = 0.0f;//lbl_804D8254
	r27->x6BC_inputStickangle = 0.0f;//lbl_804D8254
	// TODO: following three elements probably a vector because of the reverse order init that happens a lot with vectors
	r27->x6C8 = 0.0f;//lbl_804D8254
	r27->x6C4 = 0.0f;//lbl_804D8254
	r27->x6C0 = 0.0f;//lbl_804D8254
	// TODO: another vector probably
	r27->x6E0 = 0.0f;//lbl_804D8254
	r27->x6DC = 0.0f;//lbl_804D8254
	r27->x6D8 = 0.0f;//lbl_804D8254

	r27->x209C = (s16) 0;
	r27->x2224_flag.bits.b1 = 0;
	r27->x21E4_callback_OnDeath2 = 0;
	r27->x2100 = -1;
	r27->x2101_bits_0to6 = 0;
	r27->x21B4_callback_Accessory2 = 0;
	r27->x21B8_callback_Accessory3 = 0;
	r27->x21E0_callback_OnDeath = 0;
	r27->x21E8_callback_OnDeath3 = 0;
	r27->x221E_flag.bits.b4 = 1;
	r27->x197C = 0;
	r27->x2223_flag.bits.b7 = 0;
	r27->x2028 = 0;
	r27->x202C = 0;

	// sets some fighter flags and values to 0, see https://decomp.me/scratch/VBrFf
	func_800C88A0(r27=r27+0); // TODO: make the compiler use mr r3,r27 instead of addi r3,r27,0 to pass the argument

	//@598
	r27->x2227_flag.bits.b3 = 0;
	r27->x2034 = 0;
	r27->x2038 = 0;
	r27->x1980 = 0;

	//@5b4 TODO: write the assembly pattern that this generates down somewhere
	r27->x2224_flag.bits.b2 = r27->x2224_flag.bits.b3 = 0;

	//@5d0
	r27->x2224_flag.bits.b4 = 0;
	r27->x2108 = 0;
	r27->x2224_flag.bits.b5 = 0;
	r27->x1A53 = (s8) 0;
	r27->x1A52 = (s8) 0;
	r27->x210C_walljumpInputTimer = 254;
	r27->x1910 = 0;
	r27->x2225_flag.bits.b0 = 0;
	r27->x2225_flag.bits.b2 = 1;
	r27->x2225_flag.bits.b4 = 0;
	func_800DEEA8(r27->x0_fighter);
	r27->x18BC = 0.0f;//lbl_804D8254
	r27->x18B8 = 0.0f;//lbl_804D8254
	r27->x2226_flag.bits.b2 = 0;
	r27->x2170 = 0.0f;//lbl_804D8254
	r27->x2225_flag.bits.b6 = r27->x2225_flag.bits.b5;
	r27->x1908 = -1;
	r27->x190C = 0;
	r27->x2227_flag.bits.b4 = 0;
	r27->x2138_smashSinceHitbox = -1.0f;//lbl_804D8258;
	r27->x213C = -1;
	r27->x2227_flag.bits.b5 = 0;
	r27->x2228_flag.bits.b1 = 0;
	r27->x2140 = 0.0f;//lbl_804D8254
	r27->x2227_flag.bits.b6 = 0;
	r27->x2180 = 6;
	r27->x2229_flag.bits.b4 = 1;
}
#else
asm void func_80067C98()
{
	nofralloc 
/* 80067C98 00064878  7C 08 02 A6 */	mflr r0
/* 80067C9C 0006487C  90 01 00 04 */	stw r0, 4(r1)
/* 80067CA0 00064880  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 80067CA4 00064884  BF 61 00 24 */	stmw r27, 0x24(r1)
/* 80067CA8 00064888  7C 7B 1B 78 */	mr r27, r3
/* 80067CAC 0006488C  48 00 11 95 */	bl func_80068E40
/* 80067CB0 00064890  90 7B 00 08 */	stw r3, 8(r27)
/* 80067CB4 00064894  38 81 00 0C */	addi r4, r1, 0xc
/* 80067CB8 00064898  88 7B 00 0C */	lbz r3, 0xc(r27)
/* 80067CBC 0006489C  4B FC AA 11 */	bl Player_800326CC
/* 80067CC0 000648A0  88 7B 00 0C */	lbz r3, 0xc(r27)
/* 80067CC4 000648A4  4B FC B3 61 */	bl Player_GetFacingDirection
/* 80067CC8 000648A8  D0 3B 00 2C */	stfs f1, 0x2c(r27)
/* 80067CCC 000648AC  7F 63 DB 78 */	mr r3, r27
/* 80067CD0 000648B0  48 01 88 1D */	bl func_800804EC
/* 80067CD4 000648B4  C0 5B 00 2C */	lfs f2, 0x2c(r27)
/* 80067CD8 000648B8  3B 80 00 00 */	li r28, 0
/* 80067CDC 000648BC  C0 01 00 0C */	lfs f0, 0xc(r1)
/* 80067CE0 000648C0  3B A0 00 01 */	li r29, 1
/* 80067CE4 000648C4  38 00 00 FF */	li r0, 0xff
/* 80067CE8 000648C8  EC 02 00 7A */	fmadds f0, f2, f1, f0
/* 80067CEC 000648CC  3B C0 FF FF */	li r30, -1
/* 80067CF0 000648D0  D0 01 00 0C */	stfs f0, 0xc(r1)
/* 80067CF4 000648D4  C0 01 00 0C */	lfs f0, 0xc(r1)
/* 80067CF8 000648D8  D0 1B 00 B0 */	stfs f0, 0xb0(r27)
/* 80067CFC 000648DC  D0 1B 00 BC */	stfs f0, 0xbc(r27)
/* 80067D00 000648E0  C0 01 00 10 */	lfs f0, 0x10(r1)
/* 80067D04 000648E4  D0 1B 00 B4 */	stfs f0, 0xb4(r27)
/* 80067D08 000648E8  D0 1B 00 C0 */	stfs f0, 0xc0(r27)
/* 80067D0C 000648EC  C0 01 00 14 */	lfs f0, 0x14(r1)
/* 80067D10 000648F0  D0 1B 00 B8 */	stfs f0, 0xb8(r27)
/* 80067D14 000648F4  D0 1B 00 C4 */	stfs f0, 0xc4(r27)
/* 80067D18 000648F8  C0 1B 00 2C */	lfs f0, 0x2c(r27)
/* 80067D1C 000648FC  D0 1B 00 30 */	stfs f0, 0x30(r27)
/* 80067D20 00064900  C0 1B 00 34 */	lfs f0, 0x34(r27)
/* 80067D24 00064904  D0 1B 00 38 */	stfs f0, 0x38(r27)
/* 80067D28 00064908  88 7B 22 20 */	lbz r3, 0x2220(r27)
/* 80067D2C 0006490C  53 83 17 7A */	rlwimi r3, r28, 2, 0x1d, 0x1d
/* 80067D30 00064910  98 7B 22 20 */	stb r3, 0x2220(r27)
/* 80067D34 00064914  88 7B 22 20 */	lbz r3, 0x2220(r27)
/* 80067D38 00064918  53 83 0F BC */	rlwimi r3, r28, 1, 0x1e, 0x1e
/* 80067D3C 0006491C  98 7B 22 20 */	stb r3, 0x2220(r27)
/* 80067D40 00064920  93 9B 20 0C */	stw r28, 0x200c(r27)
/* 80067D44 00064924  93 9B 20 10 */	stw r28, 0x2010(r27)
/* 80067D48 00064928  93 9B 20 08 */	stw r28, 0x2008(r27)
/* 80067D4C 0006492C  88 7B 22 19 */	lbz r3, 0x2219(r27)
/* 80067D50 00064930  53 83 36 72 */	rlwimi r3, r28, 6, 0x19, 0x19
/* 80067D54 00064934  98 7B 22 19 */	stb r3, 0x2219(r27)
/* 80067D58 00064938  88 7B 22 19 */	lbz r3, 0x2219(r27)
/* 80067D5C 0006493C  53 83 2E B4 */	rlwimi r3, r28, 5, 0x1a, 0x1a
/* 80067D60 00064940  98 7B 22 19 */	stb r3, 0x2219(r27)
/* 80067D64 00064944  88 7B 22 19 */	lbz r3, 0x2219(r27)
/* 80067D68 00064948  53 83 26 F6 */	rlwimi r3, r28, 4, 0x1b, 0x1b
/* 80067D6C 0006494C  98 7B 22 19 */	stb r3, 0x2219(r27)
/* 80067D70 00064950  88 7B 22 19 */	lbz r3, 0x2219(r27)
/* 80067D74 00064954  53 83 1F 38 */	rlwimi r3, r28, 3, 0x1c, 0x1c
/* 80067D78 00064958  98 7B 22 19 */	stb r3, 0x2219(r27)
/* 80067D7C 0006495C  88 7B 22 1A */	lbz r3, 0x221a(r27)
/* 80067D80 00064960  53 83 17 7A */	rlwimi r3, r28, 2, 0x1d, 0x1d
/* 80067D84 00064964  98 7B 22 1A */	stb r3, 0x221a(r27)
/* 80067D88 00064968  88 7B 22 1A */	lbz r3, 0x221a(r27)
/* 80067D8C 0006496C  53 83 0F BC */	rlwimi r3, r28, 1, 0x1e, 0x1e
/* 80067D90 00064970  98 7B 22 1A */	stb r3, 0x221a(r27)
/* 80067D94 00064974  88 7B 22 1D */	lbz r3, 0x221d(r27)
/* 80067D98 00064978  53 83 2E B4 */	rlwimi r3, r28, 5, 0x1a, 0x1a
/* 80067D9C 0006497C  98 7B 22 1D */	stb r3, 0x221d(r27)
/* 80067DA0 00064980  88 7B 22 1E */	lbz r3, 0x221e(r27)
/* 80067DA4 00064984  53 83 07 FE */	rlwimi r3, r28, 0, 0x1f, 0x1f
/* 80067DA8 00064988  98 7B 22 1E */	stb r3, 0x221e(r27)
/* 80067DAC 0006498C  88 7B 22 20 */	lbz r3, 0x2220(r27)
/* 80067DB0 00064990  53 83 07 FE */	rlwimi r3, r28, 0, 0x1f, 0x1f
/* 80067DB4 00064994  98 7B 22 20 */	stb r3, 0x2220(r27)
/* 80067DB8 00064998  88 7B 22 21 */	lbz r3, 0x2221(r27)
/* 80067DBC 0006499C  53 83 1F 38 */	rlwimi r3, r28, 3, 0x1c, 0x1c
/* 80067DC0 000649A0  98 7B 22 21 */	stb r3, 0x2221(r27)
/* 80067DC4 000649A4  88 7B 22 21 */	lbz r3, 0x2221(r27)
/* 80067DC8 000649A8  53 83 17 7A */	rlwimi r3, r28, 2, 0x1d, 0x1d
/* 80067DCC 000649AC  98 7B 22 21 */	stb r3, 0x2221(r27)
/* 80067DD0 000649B0  88 7B 22 21 */	lbz r3, 0x2221(r27)
/* 80067DD4 000649B4  53 A3 0F BC */	rlwimi r3, r29, 1, 0x1e, 0x1e
/* 80067DD8 000649B8  98 7B 22 21 */	stb r3, 0x2221(r27)
/* 80067DDC 000649BC  88 7B 22 21 */	lbz r3, 0x2221(r27)
/* 80067DE0 000649C0  53 83 07 FE */	rlwimi r3, r28, 0, 0x1f, 0x1f
/* 80067DE4 000649C4  98 7B 22 21 */	stb r3, 0x2221(r27)
/* 80067DE8 000649C8  98 1B 06 1D */	stb r0, 0x61d(r27)
/* 80067DEC 000649CC  C0 22 88 74 */	lfs f1, lbl_804D8254(r2)
/* 80067DF0 000649D0  D0 3B 00 D0 */	stfs f1, 0xd0(r27)
/* 80067DF4 000649D4  D0 3B 00 CC */	stfs f1, 0xcc(r27)
/* 80067DF8 000649D8  D0 3B 00 C8 */	stfs f1, 0xc8(r27)
/* 80067DFC 000649DC  D0 3B 08 94 */	stfs f1, 0x894(r27)
/* 80067E00 000649E0  D0 3B 08 98 */	stfs f1, 0x898(r27)
/* 80067E04 000649E4  C0 02 88 70 */	lfs f0, lbl_804D8250(r2)
/* 80067E08 000649E8  D0 1B 08 9C */	stfs f0, 0x89c(r27)
/* 80067E0C 000649EC  D0 1B 08 A0 */	stfs f0, 0x8a0(r27)
/* 80067E10 000649F0  D0 3B 18 50 */	stfs f1, 0x1850(r27)
/* 80067E14 000649F4  D0 3B 18 A4 */	stfs f1, 0x18a4(r27)
/* 80067E18 000649F8  D0 3B 18 A8 */	stfs f1, 0x18a8(r27)
/* 80067E1C 000649FC  93 DB 18 AC */	stw r30, 0x18ac(r27)
/* 80067E20 00064A00  D0 3B 18 B0 */	stfs f1, 0x18b0(r27)
/* 80067E24 00064A04  D0 3B 18 B4 */	stfs f1, 0x18b4(r27)
/* 80067E28 00064A08  93 9B 18 28 */	stw r28, 0x1828(r27)
/* 80067E2C 00064A0C  88 1B 22 1C */	lbz r0, 0x221c(r27)
/* 80067E30 00064A10  53 80 0F BC */	rlwimi r0, r28, 1, 0x1e, 0x1e
/* 80067E34 00064A14  98 1B 22 1C */	stb r0, 0x221c(r27)
/* 80067E38 00064A18  D0 3B 18 A0 */	stfs f1, 0x18a0(r27)
/* 80067E3C 00064A1C  9B 9B 19 68 */	stb r28, 0x1968(r27)
/* 80067E40 00064A20  9B 9B 19 69 */	stb r28, 0x1969(r27)
/* 80067E44 00064A24  D0 3B 19 6C */	stfs f1, 0x196c(r27)
/* 80067E48 00064A28  93 9B 20 64 */	stw r28, 0x2064(r27)
/* 80067E4C 00064A2C  88 7B 00 0C */	lbz r3, 0xc(r27)
/* 80067E50 00064A30  4B FC C4 65 */	bl Player_GetDamage
/* 80067E54 00064A34  6C 60 80 00 */	xoris r0, r3, 0x8000
/* 80067E58 00064A38  C8 22 88 80 */	lfd f1, lbl_804D8260(r2)
/* 80067E5C 00064A3C  90 01 00 1C */	stw r0, 0x1c(r1)
/* 80067E60 00064A40  3C 00 43 30 */	lis r0, 0x4330
/* 80067E64 00064A44  3B E0 00 06 */	li r31, 6
/* 80067E68 00064A48  90 01 00 18 */	stw r0, 0x18(r1)
/* 80067E6C 00064A4C  38 00 FF F6 */	li r0, -10
/* 80067E70 00064A50  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 80067E74 00064A54  EC 00 08 28 */	fsubs f0, f0, f1
/* 80067E78 00064A58  D0 1B 18 30 */	stfs f0, 0x1830(r27)
/* 80067E7C 00064A5C  C0 22 88 74 */	lfs f1, lbl_804D8254(r2)
/* 80067E80 00064A60  D0 3B 18 38 */	stfs f1, 0x1838(r27)
/* 80067E84 00064A64  93 9B 18 3C */	stw r28, 0x183c(r27)
/* 80067E88 00064A68  93 9B 18 C0 */	stw r28, 0x18c0(r27)
/* 80067E8C 00064A6C  93 FB 18 C4 */	stw r31, 0x18c4(r27)
/* 80067E90 00064A70  93 DB 18 C8 */	stw r30, 0x18c8(r27)
/* 80067E94 00064A74  93 9B 18 F0 */	stw r28, 0x18f0(r27)
/* 80067E98 00064A78  93 9B 18 CC */	stw r28, 0x18cc(r27)
/* 80067E9C 00064A7C  90 1B 18 D0 */	stw r0, 0x18d0(r27)
/* 80067EA0 00064A80  88 1B 22 1F */	lbz r0, 0x221f(r27)
/* 80067EA4 00064A84  53 80 17 7A */	rlwimi r0, r28, 2, 0x1d, 0x1d
/* 80067EA8 00064A88  98 1B 22 1F */	stb r0, 0x221f(r27)
/* 80067EAC 00064A8C  88 1B 22 21 */	lbz r0, 0x2221(r27)
/* 80067EB0 00064A90  53 80 36 72 */	rlwimi r0, r28, 6, 0x19, 0x19
/* 80067EB4 00064A94  98 1B 22 21 */	stb r0, 0x2221(r27)
/* 80067EB8 00064A98  93 9B 18 F4 */	stw r28, 0x18f4(r27)
/* 80067EBC 00064A9C  9B BB 18 F8 */	stb r29, 0x18f8(r27)
/* 80067EC0 00064AA0  B3 9B 18 FA */	sth r28, 0x18fa(r27)
/* 80067EC4 00064AA4  9B 9B 18 FD */	stb r28, 0x18fd(r27)
/* 80067EC8 00064AA8  9B 9B 18 FC */	stb r28, 0x18fc(r27)
/* 80067ECC 00064AAC  D0 3B 18 34 */	stfs f1, 0x1834(r27)
/* 80067ED0 00064AB0  88 1B 22 22 */	lbz r0, 0x2222(r27)
/* 80067ED4 00064AB4  53 80 2E B4 */	rlwimi r0, r28, 5, 0x1a, 0x1a
/* 80067ED8 00064AB8  98 1B 22 22 */	stb r0, 0x2222(r27)
/* 80067EDC 00064ABC  93 9B 18 40 */	stw r28, 0x1840(r27)
/* 80067EE0 00064AC0  88 1B 22 19 */	lbz r0, 0x2219(r27)
/* 80067EE4 00064AC4  53 80 17 7A */	rlwimi r0, r28, 2, 0x1d, 0x1d
/* 80067EE8 00064AC8  98 1B 22 19 */	stb r0, 0x2219(r27)
/* 80067EEC 00064ACC  88 1B 22 19 */	lbz r0, 0x2219(r27)
/* 80067EF0 00064AD0  53 80 0F BC */	rlwimi r0, r28, 1, 0x1e, 0x1e
/* 80067EF4 00064AD4  98 1B 22 19 */	stb r0, 0x2219(r27)
/* 80067EF8 00064AD8  88 1B 22 19 */	lbz r0, 0x2219(r27)
/* 80067EFC 00064ADC  53 80 07 FE */	rlwimi r0, r28, 0, 0x1f, 0x1f
/* 80067F00 00064AE0  98 1B 22 19 */	stb r0, 0x2219(r27)
/* 80067F04 00064AE4  88 1B 22 1A */	lbz r0, 0x221a(r27)
/* 80067F08 00064AE8  53 80 3E 30 */	rlwimi r0, r28, 7, 0x18, 0x18
/* 80067F0C 00064AEC  98 1B 22 1A */	stb r0, 0x221a(r27)
/* 80067F10 00064AF0  88 1B 22 1A */	lbz r0, 0x221a(r27)
/* 80067F14 00064AF4  53 80 36 72 */	rlwimi r0, r28, 6, 0x19, 0x19
/* 80067F18 00064AF8  98 1B 22 1A */	stb r0, 0x221a(r27)
/* 80067F1C 00064AFC  D0 3B 19 54 */	stfs f1, 0x1954(r27)
/* 80067F20 00064B00  D0 3B 19 58 */	stfs f1, 0x1958(r27)
/* 80067F24 00064B04  88 1B 22 1A */	lbz r0, 0x221a(r27)
/* 80067F28 00064B08  53 80 2E B4 */	rlwimi r0, r28, 5, 0x1a, 0x1a
/* 80067F2C 00064B0C  98 1B 22 1A */	stb r0, 0x221a(r27)
/* 80067F30 00064B10  D0 3B 19 5C */	stfs f1, 0x195c(r27)
/* 80067F34 00064B14  88 1B 22 1A */	lbz r0, 0x221a(r27)
/* 80067F38 00064B18  53 80 26 F6 */	rlwimi r0, r28, 4, 0x1b, 0x1b
/* 80067F3C 00064B1C  98 1B 22 1A */	stb r0, 0x221a(r27)
/* 80067F40 00064B20  C0 02 88 70 */	lfs f0, lbl_804D8250(r2)
/* 80067F44 00064B24  D0 1B 19 60 */	stfs f0, 0x1960(r27)
/* 80067F48 00064B28  D0 3B 19 64 */	stfs f1, 0x1964(r27)
/* 80067F4C 00064B2C  D0 3B 18 9C */	stfs f1, 0x189c(r27)
/* 80067F50 00064B30  88 1B 22 20 */	lbz r0, 0x2220(r27)
/* 80067F54 00064B34  53 80 26 F6 */	rlwimi r0, r28, 4, 0x1b, 0x1b
/* 80067F58 00064B38  98 1B 22 20 */	stb r0, 0x2220(r27)
/* 80067F5C 00064B3C  88 1B 22 20 */	lbz r0, 0x2220(r27)
/* 80067F60 00064B40  53 80 1F 38 */	rlwimi r0, r28, 3, 0x1c, 0x1c
/* 80067F64 00064B44  98 1B 22 20 */	stb r0, 0x2220(r27)
/* 80067F68 00064B48  93 9B 19 14 */	stw r28, 0x1914(r27)
/* 80067F6C 00064B4C  93 9B 19 18 */	stw r28, 0x1918(r27)
/* 80067F70 00064B50  D0 3B 19 1C */	stfs f1, 0x191c(r27)
/* 80067F74 00064B54  93 9B 19 24 */	stw r28, 0x1924(r27)
/* 80067F78 00064B58  D0 3B 19 28 */	stfs f1, 0x1928(r27)
/* 80067F7C 00064B5C  88 1B 22 23 */	lbz r0, 0x2223(r27)
/* 80067F80 00064B60  53 80 17 7A */	rlwimi r0, r28, 2, 0x1d, 0x1d
/* 80067F84 00064B64  98 1B 22 23 */	stb r0, 0x2223(r27)
/* 80067F88 00064B68  93 9B 19 50 */	stw r28, 0x1950(r27)
/* 80067F8C 00064B6C  93 9B 19 48 */	stw r28, 0x1948(r27)
/* 80067F90 00064B70  88 1B 22 23 */	lbz r0, 0x2223(r27)
/* 80067F94 00064B74  53 80 1F 38 */	rlwimi r0, r28, 3, 0x1c, 0x1c
/* 80067F98 00064B78  98 1B 22 23 */	stb r0, 0x2223(r27)
/* 80067F9C 00064B7C  D0 3B 00 FC */	stfs f1, 0xfc(r27)
/* 80067FA0 00064B80  D0 3B 00 F8 */	stfs f1, 0xf8(r27)
/* 80067FA4 00064B84  C0 02 88 78 */	lfs f0, lbl_804D8258(r2)
/* 80067FA8 00064B88  D0 1B 01 00 */	stfs f0, 0x100(r27)
/* 80067FAC 00064B8C  88 1B 22 22 */	lbz r0, 0x2222(r27)
/* 80067FB0 00064B90  53 80 07 FE */	rlwimi r0, r28, 0, 0x1f, 0x1f
/* 80067FB4 00064B94  98 1B 22 22 */	stb r0, 0x2222(r27)
/* 80067FB8 00064B98  88 1B 22 23 */	lbz r0, 0x2223(r27)
/* 80067FBC 00064B9C  53 80 3E 30 */	rlwimi r0, r28, 7, 0x18, 0x18
/* 80067FC0 00064BA0  98 1B 22 23 */	stb r0, 0x2223(r27)
/* 80067FC4 00064BA4  88 1B 22 1A */	lbz r0, 0x221a(r27)
/* 80067FC8 00064BA8  53 80 1F 38 */	rlwimi r0, r28, 3, 0x1c, 0x1c
/* 80067FCC 00064BAC  98 1B 22 1A */	stb r0, 0x221a(r27)
/* 80067FD0 00064BB0  88 1B 22 19 */	lbz r0, 0x2219(r27)
/* 80067FD4 00064BB4  53 80 3E 30 */	rlwimi r0, r28, 7, 0x18, 0x18
/* 80067FD8 00064BB8  98 1B 22 19 */	stb r0, 0x2219(r27)
/* 80067FDC 00064BBC  93 9B 20 A0 */	stw r28, 0x20a0(r27)
/* 80067FE0 00064BC0  93 9B 22 10 */	stw r28, 0x2210(r27)
/* 80067FE4 00064BC4  D0 3B 22 14 */	stfs f1, 0x2214(r27)
/* 80067FE8 00064BC8  93 9B 19 74 */	stw r28, 0x1974(r27)
/* 80067FEC 00064BCC  93 9B 19 78 */	stw r28, 0x1978(r27)
/* 80067FF0 00064BD0  88 1B 22 1E */	lbz r0, 0x221e(r27)
/* 80067FF4 00064BD4  53 A0 26 F6 */	rlwimi r0, r29, 4, 0x1b, 0x1b
/* 80067FF8 00064BD8  98 1B 22 1E */	stb r0, 0x221e(r27)
/* 80067FFC 00064BDC  93 9B 19 84 */	stw r28, 0x1984(r27)
/* 80068000 00064BE0  93 9B 19 88 */	stw r28, 0x1988(r27)
/* 80068004 00064BE4  93 9B 19 8C */	stw r28, 0x198c(r27)
/* 80068008 00064BE8  88 1B 22 21 */	lbz r0, 0x2221(r27)
/* 8006800C 00064BEC  53 80 3E 30 */	rlwimi r0, r28, 7, 0x18, 0x18
/* 80068010 00064BF0  98 1B 22 21 */	stb r0, 0x2221(r27)
/* 80068014 00064BF4  93 9B 19 90 */	stw r28, 0x1990(r27)
/* 80068018 00064BF8  93 9B 19 94 */	stw r28, 0x1994(r27)
/* 8006801C 00064BFC  88 1B 22 1D */	lbz r0, 0x221d(r27)
/* 80068020 00064C00  53 80 0F BC */	rlwimi r0, r28, 1, 0x1e, 0x1e
/* 80068024 00064C04  98 1B 22 1D */	stb r0, 0x221d(r27)
/* 80068028 00064C08  88 1B 22 1B */	lbz r0, 0x221b(r27)
/* 8006802C 00064C0C  53 80 17 7A */	rlwimi r0, r28, 2, 0x1d, 0x1d
/* 80068030 00064C10  98 1B 22 1B */	stb r0, 0x221b(r27)
/* 80068034 00064C14  93 9B 1A 58 */	stw r28, 0x1a58(r27)
/* 80068038 00064C18  93 9B 1A 5C */	stw r28, 0x1a5c(r27)
/* 8006803C 00064C1C  88 1B 22 1B */	lbz r0, 0x221b(r27)
/* 80068040 00064C20  53 80 0F BC */	rlwimi r0, r28, 1, 0x1e, 0x1e
/* 80068044 00064C24  98 1B 22 1B */	stb r0, 0x221b(r27)
/* 80068048 00064C28  93 9B 1A 60 */	stw r28, 0x1a60(r27)
/* 8006804C 00064C2C  93 9B 1A 64 */	stw r28, 0x1a64(r27)
/* 80068050 00064C30  88 1B 22 1B */	lbz r0, 0x221b(r27)
/* 80068054 00064C34  53 80 07 FE */	rlwimi r0, r28, 0, 0x1f, 0x1f
/* 80068058 00064C38  98 1B 22 1B */	stb r0, 0x221b(r27)
/* 8006805C 00064C3C  88 1B 22 1C */	lbz r0, 0x221c(r27)
/* 80068060 00064C40  53 80 3E 30 */	rlwimi r0, r28, 7, 0x18, 0x18
/* 80068064 00064C44  98 1B 22 1C */	stb r0, 0x221c(r27)
/* 80068068 00064C48  93 9B 11 98 */	stw r28, 0x1198(r27)
/* 8006806C 00064C4C  A0 1B 22 1C */	lhz r0, 0x221c(r27)
/* 80068070 00064C50  53 80 35 F2 */	rlwimi r0, r28, 6, 0x17, 0x19
/* 80068074 00064C54  B0 1B 22 1C */	sth r0, 0x221c(r27)
/* 80068078 00064C58  93 9B 20 AC */	stw r28, 0x20ac(r27)
/* 8006807C 00064C5C  88 1B 22 1C */	lbz r0, 0x221c(r27)
/* 80068080 00064C60  53 80 17 7A */	rlwimi r0, r28, 2, 0x1d, 0x1d
/* 80068084 00064C64  98 1B 22 1C */	stb r0, 0x221c(r27)
/* 80068088 00064C68  93 DB 21 4C */	stw r30, 0x214c(r27)
/* 8006808C 00064C6C  93 DB 21 48 */	stw r30, 0x2148(r27)
/* 80068090 00064C70  93 DB 21 44 */	stw r30, 0x2144(r27)
/* 80068094 00064C74  93 DB 21 60 */	stw r30, 0x2160(r27)
/* 80068098 00064C78  93 DB 21 5C */	stw r30, 0x215c(r27)
/* 8006809C 00064C7C  93 DB 21 58 */	stw r30, 0x2158(r27)
/* 800680A0 00064C80  93 DB 21 54 */	stw r30, 0x2154(r27)
/* 800680A4 00064C84  93 DB 21 50 */	stw r30, 0x2150(r27)
/* 800680A8 00064C88  93 9B 21 68 */	stw r28, 0x2168(r27)
/* 800680AC 00064C8C  93 9B 21 64 */	stw r28, 0x2164(r27)
/* 800680B0 00064C90  93 9B 20 8C */	stw r28, 0x208c(r27)
/* 800680B4 00064C94  B3 9B 20 90 */	sth r28, 0x2090(r27)
/* 800680B8 00064C98  B3 9B 20 98 */	sth r28, 0x2098(r27)
/* 800680BC 00064C9C  B3 9B 20 92 */	sth r28, 0x2092(r27)
/* 800680C0 00064CA0  93 9B 20 94 */	stw r28, 0x2094(r27)
/* 800680C4 00064CA4  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 800680C8 00064CA8  C0 03 02 60 */	lfs f0, 0x260(r3)
/* 800680CC 00064CAC  D0 1B 19 98 */	stfs f0, 0x1998(r27)
/* 800680D0 00064CB0  88 1B 22 1A */	lbz r0, 0x221a(r27)
/* 800680D4 00064CB4  53 80 07 FE */	rlwimi r0, r28, 0, 0x1f, 0x1f
/* 800680D8 00064CB8  98 1B 22 1A */	stb r0, 0x221a(r27)
/* 800680DC 00064CBC  88 1B 22 1B */	lbz r0, 0x221b(r27)
/* 800680E0 00064CC0  53 80 3E 30 */	rlwimi r0, r28, 7, 0x18, 0x18
/* 800680E4 00064CC4  98 1B 22 1B */	stb r0, 0x221b(r27)
/* 800680E8 00064CC8  88 1B 22 1B */	lbz r0, 0x221b(r27)
/* 800680EC 00064CCC  53 80 36 72 */	rlwimi r0, r28, 6, 0x19, 0x19
/* 800680F0 00064CD0  98 1B 22 1B */	stb r0, 0x221b(r27)
/* 800680F4 00064CD4  88 1B 22 1B */	lbz r0, 0x221b(r27)
/* 800680F8 00064CD8  53 80 26 F6 */	rlwimi r0, r28, 4, 0x1b, 0x1b
/* 800680FC 00064CDC  98 1B 22 1B */	stb r0, 0x221b(r27)
/* 80068100 00064CE0  88 1B 22 1B */	lbz r0, 0x221b(r27)
/* 80068104 00064CE4  53 80 1F 38 */	rlwimi r0, r28, 3, 0x1c, 0x1c
/* 80068108 00064CE8  98 1B 22 1B */	stb r0, 0x221b(r27)
/* 8006810C 00064CEC  88 1B 22 1C */	lbz r0, 0x221c(r27)
/* 80068110 00064CF0  53 80 26 F6 */	rlwimi r0, r28, 4, 0x1b, 0x1b
/* 80068114 00064CF4  98 1B 22 1C */	stb r0, 0x221c(r27)
/* 80068118 00064CF8  88 1B 22 1C */	lbz r0, 0x221c(r27)
/* 8006811C 00064CFC  53 80 36 72 */	rlwimi r0, r28, 6, 0x19, 0x19
/* 80068120 00064D00  98 1B 22 1C */	stb r0, 0x221c(r27)
/* 80068124 00064D04  88 1B 22 1C */	lbz r0, 0x221c(r27)
/* 80068128 00064D08  53 80 2E B4 */	rlwimi r0, r28, 5, 0x1a, 0x1a
/* 8006812C 00064D0C  98 1B 22 1C */	stb r0, 0x221c(r27)
/* 80068130 00064D10  93 9B 19 A0 */	stw r28, 0x19a0(r27)
/* 80068134 00064D14  93 9B 19 A4 */	stw r28, 0x19a4(r27)
/* 80068138 00064D18  D0 3B 19 9C */	stfs f1, 0x199c(r27)
/* 8006813C 00064D1C  93 9B 19 A8 */	stw r28, 0x19a8(r27)
/* 80068140 00064D20  D0 3B 19 B4 */	stfs f1, 0x19b4(r27)
/* 80068144 00064D24  D0 3B 19 B8 */	stfs f1, 0x19b8(r27)
/* 80068148 00064D28  93 FB 19 BC */	stw r31, 0x19bc(r27)
/* 8006814C 00064D2C  88 1B 22 1F */	lbz r0, 0x221f(r27)
/* 80068150 00064D30  53 80 0F BC */	rlwimi r0, r28, 1, 0x1e, 0x1e
/* 80068154 00064D34  98 1B 22 1F */	stb r0, 0x221f(r27)
/* 80068158 00064D38  88 1B 22 18 */	lbz r0, 0x2218(r27)
/* 8006815C 00064D3C  53 80 26 F6 */	rlwimi r0, r28, 4, 0x1b, 0x1b
/* 80068160 00064D40  98 1B 22 18 */	stb r0, 0x2218(r27)
/* 80068164 00064D44  88 1B 22 18 */	lbz r0, 0x2218(r27)
/* 80068168 00064D48  53 80 1F 38 */	rlwimi r0, r28, 3, 0x1c, 0x1c
/* 8006816C 00064D4C  98 1B 22 18 */	stb r0, 0x2218(r27)
/* 80068170 00064D50  93 9B 1A 3C */	stw r28, 0x1a3c(r27)
/* 80068174 00064D54  D0 3B 1A 2C */	stfs f1, 0x1a2c(r27)
/* 80068178 00064D58  88 1B 22 18 */	lbz r0, 0x2218(r27)
/* 8006817C 00064D5C  53 80 0F BC */	rlwimi r0, r28, 1, 0x1e, 0x1e
/* 80068180 00064D60  98 1B 22 18 */	stb r0, 0x2218(r27)
/* 80068184 00064D64  88 1B 22 18 */	lbz r0, 0x2218(r27)
/* 80068188 00064D68  53 80 07 FE */	rlwimi r0, r28, 0, 0x1f, 0x1f
/* 8006818C 00064D6C  98 1B 22 18 */	stb r0, 0x2218(r27)
/* 80068190 00064D70  D0 3B 1A 40 */	stfs f1, 0x1a40(r27)
/* 80068194 00064D74  7F 63 DB 78 */	mr r3, r27
/* 80068198 00064D78  93 9B 1A 44 */	stw r28, 0x1a44(r27)
/* 8006819C 00064D7C  93 9B 1A 48 */	stw r28, 0x1a48(r27)
/* 800681A0 00064D80  D0 3B 06 94 */	stfs f1, 0x694(r27)
/* 800681A4 00064D84  D0 3B 06 90 */	stfs f1, 0x690(r27)
/* 800681A8 00064D88  D0 3B 06 8C */	stfs f1, 0x68c(r27)
/* 800681AC 00064D8C  D0 3B 06 AC */	stfs f1, 0x6ac(r27)
/* 800681B0 00064D90  D0 3B 06 A8 */	stfs f1, 0x6a8(r27)
/* 800681B4 00064D94  D0 3B 06 A4 */	stfs f1, 0x6a4(r27)
/* 800681B8 00064D98  D0 3B 06 BC */	stfs f1, 0x6bc(r27)
/* 800681BC 00064D9C  D0 3B 06 C8 */	stfs f1, 0x6c8(r27)
/* 800681C0 00064DA0  D0 3B 06 C4 */	stfs f1, 0x6c4(r27)
/* 800681C4 00064DA4  D0 3B 06 C0 */	stfs f1, 0x6c0(r27)
/* 800681C8 00064DA8  D0 3B 06 E0 */	stfs f1, 0x6e0(r27)
/* 800681CC 00064DAC  D0 3B 06 DC */	stfs f1, 0x6dc(r27)
/* 800681D0 00064DB0  D0 3B 06 D8 */	stfs f1, 0x6d8(r27)
/* 800681D4 00064DB4  B3 9B 20 9C */	sth r28, 0x209c(r27)
/* 800681D8 00064DB8  88 1B 22 24 */	lbz r0, 0x2224(r27)
/* 800681DC 00064DBC  53 80 36 72 */	rlwimi r0, r28, 6, 0x19, 0x19
/* 800681E0 00064DC0  98 1B 22 24 */	stb r0, 0x2224(r27)
/* 800681E4 00064DC4  93 9B 21 E4 */	stw r28, 0x21e4(r27)
/* 800681E8 00064DC8  9B DB 21 00 */	stb r30, 0x2100(r27)
/* 800681EC 00064DCC  88 1B 21 01 */	lbz r0, 0x2101(r27)
/* 800681F0 00064DD0  53 80 0E 3C */	rlwimi r0, r28, 1, 0x18, 0x1e
/* 800681F4 00064DD4  98 1B 21 01 */	stb r0, 0x2101(r27)
/* 800681F8 00064DD8  93 9B 21 B4 */	stw r28, 0x21b4(r27)
/* 800681FC 00064DDC  93 9B 21 B8 */	stw r28, 0x21b8(r27)
/* 80068200 00064DE0  93 9B 21 E0 */	stw r28, 0x21e0(r27)
/* 80068204 00064DE4  93 9B 21 E8 */	stw r28, 0x21e8(r27)
/* 80068208 00064DE8  88 1B 22 1E */	lbz r0, 0x221e(r27)
/* 8006820C 00064DEC  53 A0 1F 38 */	rlwimi r0, r29, 3, 0x1c, 0x1c
/* 80068210 00064DF0  98 1B 22 1E */	stb r0, 0x221e(r27)
/* 80068214 00064DF4  93 9B 19 7C */	stw r28, 0x197c(r27)
/* 80068218 00064DF8  88 1B 22 23 */	lbz r0, 0x2223(r27)
/* 8006821C 00064DFC  53 80 07 FE */	rlwimi r0, r28, 0, 0x1f, 0x1f
/* 80068220 00064E00  98 1B 22 23 */	stb r0, 0x2223(r27)
/* 80068224 00064E04  93 9B 20 28 */	stw r28, 0x2028(r27)
/* 80068228 00064E08  93 9B 20 2C */	stw r28, 0x202c(r27)
/* 8006822C 00064E0C  48 06 06 75 */	bl func_800C88A0
/* 80068230 00064E10  88 7B 22 27 */	lbz r3, 0x2227(r27)
/* 80068234 00064E14  53 83 26 F6 */	rlwimi r3, r28, 4, 0x1b, 0x1b
/* 80068238 00064E18  38 00 00 FE */	li r0, 0xfe
/* 8006823C 00064E1C  98 7B 22 27 */	stb r3, 0x2227(r27)
/* 80068240 00064E20  93 9B 20 34 */	stw r28, 0x2034(r27)
/* 80068244 00064E24  93 9B 20 38 */	stw r28, 0x2038(r27)
/* 80068248 00064E28  93 9B 19 80 */	stw r28, 0x1980(r27)
/* 8006824C 00064E2C  88 7B 22 24 */	lbz r3, 0x2224(r27)
/* 80068250 00064E30  53 83 26 F6 */	rlwimi r3, r28, 4, 0x1b, 0x1b
/* 80068254 00064E34  98 7B 22 24 */	stb r3, 0x2224(r27)
/* 80068258 00064E38  54 64 E7 FE */	rlwinm r4, r3, 0x1c, 0x1f, 0x1f
/* 8006825C 00064E3C  88 7B 22 24 */	lbz r3, 0x2224(r27)
/* 80068260 00064E40  50 83 2E B4 */	rlwimi r3, r4, 5, 0x1a, 0x1a
/* 80068264 00064E44  98 7B 22 24 */	stb r3, 0x2224(r27)
/* 80068268 00064E48  88 7B 22 24 */	lbz r3, 0x2224(r27)
/* 8006826C 00064E4C  53 83 1F 38 */	rlwimi r3, r28, 3, 0x1c, 0x1c
/* 80068270 00064E50  98 7B 22 24 */	stb r3, 0x2224(r27)
/* 80068274 00064E54  93 9B 21 08 */	stw r28, 0x2108(r27)
/* 80068278 00064E58  88 7B 22 24 */	lbz r3, 0x2224(r27)
/* 8006827C 00064E5C  53 83 17 7A */	rlwimi r3, r28, 2, 0x1d, 0x1d
/* 80068280 00064E60  98 7B 22 24 */	stb r3, 0x2224(r27)
/* 80068284 00064E64  9B 9B 1A 53 */	stb r28, 0x1a53(r27)
/* 80068288 00064E68  9B 9B 1A 52 */	stb r28, 0x1a52(r27)
/* 8006828C 00064E6C  98 1B 21 0C */	stb r0, 0x210c(r27)
/* 80068290 00064E70  93 9B 19 10 */	stw r28, 0x1910(r27)
/* 80068294 00064E74  88 1B 22 25 */	lbz r0, 0x2225(r27)
/* 80068298 00064E78  53 80 3E 30 */	rlwimi r0, r28, 7, 0x18, 0x18
/* 8006829C 00064E7C  98 1B 22 25 */	stb r0, 0x2225(r27)
/* 800682A0 00064E80  88 1B 22 25 */	lbz r0, 0x2225(r27)
/* 800682A4 00064E84  53 A0 2E B4 */	rlwimi r0, r29, 5, 0x1a, 0x1a
/* 800682A8 00064E88  98 1B 22 25 */	stb r0, 0x2225(r27)
/* 800682AC 00064E8C  88 1B 22 25 */	lbz r0, 0x2225(r27)
/* 800682B0 00064E90  53 80 1F 38 */	rlwimi r0, r28, 3, 0x1c, 0x1c
/* 800682B4 00064E94  98 1B 22 25 */	stb r0, 0x2225(r27)
/* 800682B8 00064E98  80 7B 00 00 */	lwz r3, 0(r27)
/* 800682BC 00064E9C  48 07 6B ED */	bl func_800DEEA8
/* 800682C0 00064EA0  C0 22 88 74 */	lfs f1, lbl_804D8254(r2)
/* 800682C4 00064EA4  D0 3B 18 BC */	stfs f1, 0x18bc(r27)
/* 800682C8 00064EA8  D0 3B 18 B8 */	stfs f1, 0x18b8(r27)
/* 800682CC 00064EAC  88 1B 22 26 */	lbz r0, 0x2226(r27)
/* 800682D0 00064EB0  53 80 2E B4 */	rlwimi r0, r28, 5, 0x1a, 0x1a
/* 800682D4 00064EB4  98 1B 22 26 */	stb r0, 0x2226(r27)
/* 800682D8 00064EB8  D0 3B 21 70 */	stfs f1, 0x2170(r27)
/* 800682DC 00064EBC  88 7B 22 25 */	lbz r3, 0x2225(r27)
/* 800682E0 00064EC0  50 63 FF BC */	rlwimi r3, r3, 0x1f, 0x1e, 0x1e
/* 800682E4 00064EC4  98 7B 22 25 */	stb r3, 0x2225(r27)
/* 800682E8 00064EC8  93 DB 19 08 */	stw r30, 0x1908(r27)
/* 800682EC 00064ECC  93 9B 19 0C */	stw r28, 0x190c(r27)
/* 800682F0 00064ED0  88 1B 22 27 */	lbz r0, 0x2227(r27)
/* 800682F4 00064ED4  53 80 1F 38 */	rlwimi r0, r28, 3, 0x1c, 0x1c
/* 800682F8 00064ED8  98 1B 22 27 */	stb r0, 0x2227(r27)
/* 800682FC 00064EDC  C0 02 88 78 */	lfs f0, lbl_804D8258(r2)
/* 80068300 00064EE0  D0 1B 21 38 */	stfs f0, 0x2138(r27)
/* 80068304 00064EE4  93 DB 21 3C */	stw r30, 0x213c(r27)
/* 80068308 00064EE8  88 1B 22 27 */	lbz r0, 0x2227(r27)
/* 8006830C 00064EEC  53 80 17 7A */	rlwimi r0, r28, 2, 0x1d, 0x1d
/* 80068310 00064EF0  98 1B 22 27 */	stb r0, 0x2227(r27)
/* 80068314 00064EF4  88 1B 22 28 */	lbz r0, 0x2228(r27)
/* 80068318 00064EF8  53 80 36 72 */	rlwimi r0, r28, 6, 0x19, 0x19
/* 8006831C 00064EFC  98 1B 22 28 */	stb r0, 0x2228(r27)
/* 80068320 00064F00  D0 3B 21 40 */	stfs f1, 0x2140(r27)
/* 80068324 00064F04  88 1B 22 27 */	lbz r0, 0x2227(r27)
/* 80068328 00064F08  53 80 0F BC */	rlwimi r0, r28, 1, 0x1e, 0x1e
/* 8006832C 00064F0C  98 1B 22 27 */	stb r0, 0x2227(r27)
/* 80068330 00064F10  93 FB 21 80 */	stw r31, 0x2180(r27)
/* 80068334 00064F14  88 1B 22 29 */	lbz r0, 0x2229(r27)
/* 80068338 00064F18  53 A0 1F 38 */	rlwimi r0, r29, 3, 0x1c, 0x1c
/* 8006833C 00064F1C  98 1B 22 29 */	stb r0, 0x2229(r27)
/* 80068340 00064F20  BB 61 00 24 */	lmw r27, 0x24(r1)
/* 80068344 00064F24  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80068348 00064F28  38 21 00 38 */	addi r1, r1, 0x38
/* 8006834C 00064F2C  7C 08 03 A6 */	mtlr r0
/* 80068350 00064F30  4E 80 00 20 */	blr  
}
#endif

// https://decomp.me/scratch/pmxBU
asm void func_80068354()
{
	nofralloc 
/* 80068354 00064F34  7C 08 02 A6 */	mflr r0
/* 80068358 00064F38  90 01 00 04 */	stw r0, 4(r1)
/* 8006835C 00064F3C  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 80068360 00064F40  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 80068364 00064F44  93 C1 00 38 */	stw r30, 0x38(r1)
/* 80068368 00064F48  7C 7E 1B 78 */	mr r30, r3
/* 8006836C 00064F4C  93 A1 00 34 */	stw r29, 0x34(r1)
/* 80068370 00064F50  93 81 00 30 */	stw r28, 0x30(r1)
/* 80068374 00064F54  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80068378 00064F58  7F E3 FB 78 */	mr r3, r31
/* 8006837C 00064F5C  4B FF F9 1D */	bl func_80067C98
/* 80068380 00064F60  83 9E 00 28 */	lwz r28, 0x28(r30)
/* 80068384 00064F64  28 1C 00 00 */	cmplwi r28, 0
/* 80068388 00064F68  40 82 00 14 */	bne lbl_8006839C
/* 8006838C 00064F6C  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 80068390 00064F70  38 80 03 94 */	li r4, 0x394
/* 80068394 00064F74  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 80068398 00064F78  48 31 FE 89 */	bl __assert
lbl_8006839C:
/* 8006839C 00064F7C  34 1F 00 B0 */	addic. r0, r31, 0xb0
/* 800683A0 00064F80  40 82 00 18 */	bne lbl_800683B8
/* 800683A4 00064F84  3C 60 80 3C */	lis r3, lbl_803C0550@ha
/* 800683A8 00064F88  38 A3 05 50 */	addi r5, r3, lbl_803C0550@l
/* 800683AC 00064F8C  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 800683B0 00064F90  38 80 03 95 */	li r4, 0x395
/* 800683B4 00064F94  48 31 FE 6D */	bl __assert
lbl_800683B8:
/* 800683B8 00064F98  80 7F 00 B0 */	lwz r3, 0xb0(r31)
/* 800683BC 00064F9C  80 1F 00 B4 */	lwz r0, 0xb4(r31)
/* 800683C0 00064FA0  90 7C 00 38 */	stw r3, 0x38(r28)
/* 800683C4 00064FA4  90 1C 00 3C */	stw r0, 0x3c(r28)
/* 800683C8 00064FA8  80 1F 00 B8 */	lwz r0, 0xb8(r31)
/* 800683CC 00064FAC  90 1C 00 40 */	stw r0, 0x40(r28)
/* 800683D0 00064FB0  80 1C 00 14 */	lwz r0, 0x14(r28)
/* 800683D4 00064FB4  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 800683D8 00064FB8  40 82 00 4C */	bne lbl_80068424
/* 800683DC 00064FBC  28 1C 00 00 */	cmplwi r28, 0
/* 800683E0 00064FC0  41 82 00 44 */	beq lbl_80068424
/* 800683E4 00064FC4  40 82 00 14 */	bne lbl_800683F8
/* 800683E8 00064FC8  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 800683EC 00064FCC  38 80 02 34 */	li r4, 0x234
/* 800683F0 00064FD0  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 800683F4 00064FD4  48 31 FE 2D */	bl __assert
lbl_800683F8:
/* 800683F8 00064FD8  80 9C 00 14 */	lwz r4, 0x14(r28)
/* 800683FC 00064FDC  38 60 00 00 */	li r3, 0
/* 80068400 00064FE0  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80068404 00064FE4  40 82 00 10 */	bne lbl_80068414
/* 80068408 00064FE8  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8006840C 00064FEC  41 82 00 08 */	beq lbl_80068414
/* 80068410 00064FF0  38 60 00 01 */	li r3, 1
lbl_80068414:
/* 80068414 00064FF4  2C 03 00 00 */	cmpwi r3, 0
/* 80068418 00064FF8  40 82 00 0C */	bne lbl_80068424
/* 8006841C 00064FFC  7F 83 E3 78 */	mr r3, r28
/* 80068420 00065000  48 30 AE C9 */	bl HSD_JObjSetMtxDirtySub
lbl_80068424:
/* 80068424 00065004  7F C3 F3 78 */	mr r3, r30
/* 80068428 00065008  48 06 8C 35 */	bl func_800D105C
/* 8006842C 0006500C  7F C3 F3 78 */	mr r3, r30
/* 80068430 00065010  48 05 85 85 */	bl func_800C09B4
/* 80068434 00065014  7F C3 F3 78 */	mr r3, r30
/* 80068438 00065018  48 01 5E C5 */	bl func_8007E2FC
/* 8006843C 0006501C  7F E3 FB 78 */	mr r3, r31
/* 80068440 00065020  48 02 06 11 */	bl func_80088A50
/* 80068444 00065024  7F E3 FB 78 */	mr r3, r31
/* 80068448 00065028  48 02 0C 75 */	bl func_800890BC
/* 8006844C 0006502C  7F E3 FB 78 */	mr r3, r31
/* 80068450 00065030  48 02 0E 85 */	bl func_800892D4
/* 80068454 00065034  7F C3 F3 78 */	mr r3, r30
/* 80068458 00065038  48 01 96 E1 */	bl func_80081B38
/* 8006845C 0006503C  7F C3 F3 78 */	mr r3, r30
/* 80068460 00065040  48 01 94 D9 */	bl func_80081938
/* 80068464 00065044  88 1F 21 35 */	lbz r0, 0x2135(r31)
/* 80068468 00065048  7C 00 07 74 */	extsb r0, r0
/* 8006846C 0006504C  2C 00 FF FF */	cmpwi r0, -1
/* 80068470 00065050  40 82 00 38 */	bne lbl_800684A8
/* 80068474 00065054  7F C3 F3 78 */	mr r3, r30
/* 80068478 00065058  48 01 A5 F1 */	bl func_80082A68
/* 8006847C 0006505C  2C 03 00 00 */	cmpwi r3, 0
/* 80068480 00065060  41 82 00 1C */	beq lbl_8006849C
/* 80068484 00065064  88 1F 22 29 */	lbz r0, 0x2229(r31)
/* 80068488 00065068  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 8006848C 0006506C  40 82 00 10 */	bne lbl_8006849C
/* 80068490 00065070  7F E3 FB 78 */	mr r3, r31
/* 80068494 00065074  48 01 52 11 */	bl func_8007D6A4
/* 80068498 00065078  48 00 00 18 */	b lbl_800684B0
lbl_8006849C:
/* 8006849C 0006507C  7F E3 FB 78 */	mr r3, r31
/* 800684A0 00065080  48 01 51 35 */	bl func_8007D5D4
/* 800684A4 00065084  48 00 00 0C */	b lbl_800684B0
lbl_800684A8:
/* 800684A8 00065088  7F E3 FB 78 */	mr r3, r31
/* 800684AC 0006508C  48 01 51 29 */	bl func_8007D5D4
lbl_800684B0:
/* 800684B0 00065090  7F E3 FB 78 */	mr r3, r31
/* 800684B4 00065094  48 00 DB B1 */	bl func_80076064
/* 800684B8 00065098  83 9E 00 28 */	lwz r28, 0x28(r30)
/* 800684BC 0006509C  28 1C 00 00 */	cmplwi r28, 0
/* 800684C0 000650A0  40 82 00 14 */	bne lbl_800684D4
/* 800684C4 000650A4  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 800684C8 000650A8  38 80 03 94 */	li r4, 0x394
/* 800684CC 000650AC  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 800684D0 000650B0  48 31 FD 51 */	bl __assert
lbl_800684D4:
/* 800684D4 000650B4  34 1F 00 B0 */	addic. r0, r31, 0xb0
/* 800684D8 000650B8  40 82 00 18 */	bne lbl_800684F0
/* 800684DC 000650BC  3C 60 80 3C */	lis r3, lbl_803C0550@ha
/* 800684E0 000650C0  38 A3 05 50 */	addi r5, r3, lbl_803C0550@l
/* 800684E4 000650C4  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 800684E8 000650C8  38 80 03 95 */	li r4, 0x395
/* 800684EC 000650CC  48 31 FD 35 */	bl __assert
lbl_800684F0:
/* 800684F0 000650D0  80 7F 00 B0 */	lwz r3, 0xb0(r31)
/* 800684F4 000650D4  80 1F 00 B4 */	lwz r0, 0xb4(r31)
/* 800684F8 000650D8  90 7C 00 38 */	stw r3, 0x38(r28)
/* 800684FC 000650DC  90 1C 00 3C */	stw r0, 0x3c(r28)
/* 80068500 000650E0  80 1F 00 B8 */	lwz r0, 0xb8(r31)
/* 80068504 000650E4  90 1C 00 40 */	stw r0, 0x40(r28)
/* 80068508 000650E8  80 1C 00 14 */	lwz r0, 0x14(r28)
/* 8006850C 000650EC  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 80068510 000650F0  40 82 00 4C */	bne lbl_8006855C
/* 80068514 000650F4  28 1C 00 00 */	cmplwi r28, 0
/* 80068518 000650F8  41 82 00 44 */	beq lbl_8006855C
/* 8006851C 000650FC  40 82 00 14 */	bne lbl_80068530
/* 80068520 00065100  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 80068524 00065104  38 80 02 34 */	li r4, 0x234
/* 80068528 00065108  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 8006852C 0006510C  48 31 FC F5 */	bl __assert
lbl_80068530:
/* 80068530 00065110  80 9C 00 14 */	lwz r4, 0x14(r28)
/* 80068534 00065114  38 60 00 00 */	li r3, 0
/* 80068538 00065118  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8006853C 0006511C  40 82 00 10 */	bne lbl_8006854C
/* 80068540 00065120  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80068544 00065124  41 82 00 08 */	beq lbl_8006854C
/* 80068548 00065128  38 60 00 01 */	li r3, 1
lbl_8006854C:
/* 8006854C 0006512C  2C 03 00 00 */	cmpwi r3, 0
/* 80068550 00065130  40 82 00 0C */	bne lbl_8006855C
/* 80068554 00065134  7F 83 E3 78 */	mr r3, r28
/* 80068558 00065138  48 30 AD 91 */	bl HSD_JObjSetMtxDirtySub
lbl_8006855C:
/* 8006855C 0006513C  7F C3 F3 78 */	mr r3, r30
/* 80068560 00065140  48 00 3B 91 */	bl func_8006C0F0
/* 80068564 00065144  83 BE 00 2C */	lwz r29, 0x2c(r30)
/* 80068568 00065148  83 9E 00 28 */	lwz r28, 0x28(r30)
/* 8006856C 0006514C  7F A3 EB 78 */	mr r3, r29
/* 80068570 00065150  48 01 71 25 */	bl func_8007F694
/* 80068574 00065154  C0 02 88 70 */	lfs f0, lbl_804D8250(r2)
/* 80068578 00065158  C0 5D 00 3C */	lfs f2, 0x3c(r29)
/* 8006857C 0006515C  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 80068580 00065160  41 82 00 0C */	beq lbl_8006858C
/* 80068584 00065164  D0 41 00 20 */	stfs f2, 0x20(r1)
/* 80068588 00065168  48 00 00 08 */	b lbl_80068590
lbl_8006858C:
/* 8006858C 0006516C  D0 21 00 20 */	stfs f1, 0x20(r1)
lbl_80068590:
/* 80068590 00065170  D0 21 00 24 */	stfs f1, 0x24(r1)
/* 80068594 00065174  28 1C 00 00 */	cmplwi r28, 0
/* 80068598 00065178  D0 21 00 28 */	stfs f1, 0x28(r1)
/* 8006859C 0006517C  40 82 00 14 */	bne lbl_800685B0
/* 800685A0 00065180  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 800685A4 00065184  38 80 02 F8 */	li r4, 0x2f8
/* 800685A8 00065188  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 800685AC 0006518C  48 31 FC 75 */	bl __assert
lbl_800685B0:
/* 800685B0 00065190  80 61 00 20 */	lwz r3, 0x20(r1)
/* 800685B4 00065194  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800685B8 00065198  90 7C 00 2C */	stw r3, 0x2c(r28)
/* 800685BC 0006519C  90 1C 00 30 */	stw r0, 0x30(r28)
/* 800685C0 000651A0  80 01 00 28 */	lwz r0, 0x28(r1)
/* 800685C4 000651A4  90 1C 00 34 */	stw r0, 0x34(r28)
/* 800685C8 000651A8  80 1C 00 14 */	lwz r0, 0x14(r28)
/* 800685CC 000651AC  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 800685D0 000651B0  40 82 00 4C */	bne lbl_8006861C
/* 800685D4 000651B4  28 1C 00 00 */	cmplwi r28, 0
/* 800685D8 000651B8  41 82 00 44 */	beq lbl_8006861C
/* 800685DC 000651BC  40 82 00 14 */	bne lbl_800685F0
/* 800685E0 000651C0  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 800685E4 000651C4  38 80 02 34 */	li r4, 0x234
/* 800685E8 000651C8  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 800685EC 000651CC  48 31 FC 35 */	bl __assert
lbl_800685F0:
/* 800685F0 000651D0  80 9C 00 14 */	lwz r4, 0x14(r28)
/* 800685F4 000651D4  38 60 00 00 */	li r3, 0
/* 800685F8 000651D8  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 800685FC 000651DC  40 82 00 10 */	bne lbl_8006860C
/* 80068600 000651E0  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80068604 000651E4  41 82 00 08 */	beq lbl_8006860C
/* 80068608 000651E8  38 60 00 01 */	li r3, 1
lbl_8006860C:
/* 8006860C 000651EC  2C 03 00 00 */	cmpwi r3, 0
/* 80068610 000651F0  40 82 00 0C */	bne lbl_8006861C
/* 80068614 000651F4  7F 83 E3 78 */	mr r3, r28
/* 80068618 000651F8  48 30 AC D1 */	bl HSD_JObjSetMtxDirtySub
lbl_8006861C:
/* 8006861C 000651FC  7F E3 FB 78 */	mr r3, r31
/* 80068620 00065200  48 05 79 8D */	bl func_800BFFAC
/* 80068624 00065204  7F E3 FB 78 */	mr r3, r31
/* 80068628 00065208  48 05 7A 4D */	bl func_800C0074
/* 8006862C 0006520C  7F C3 F3 78 */	mr r3, r30
/* 80068630 00065210  48 05 FE 09 */	bl func_800C8438
/* 80068634 00065214  7F C3 F3 78 */	mr r3, r30
/* 80068638 00065218  48 06 03 69 */	bl func_800C89A0
/* 8006863C 0006521C  7F C3 F3 78 */	mr r3, r30
/* 80068640 00065220  48 06 09 85 */	bl func_800C8FC4
/* 80068644 00065224  7F C3 F3 78 */	mr r3, r30
/* 80068648 00065228  48 01 29 B1 */	bl func_8007AFF8
/* 8006864C 0006522C  38 7E 00 00 */	addi r3, r30, 0
/* 80068650 00065230  38 80 00 00 */	li r4, 0
/* 80068654 00065234  48 01 2A 6D */	bl func_8007B0C0
/* 80068658 00065238  80 9F 00 04 */	lwz r4, 4(r31)
/* 8006865C 0006523C  3C 60 80 3C */	lis r3, ft_OnDeath@ha
/* 80068660 00065240  38 03 11 D8 */	addi r0, r3, ft_OnDeath@l
/* 80068664 00065244  54 83 10 3A */	slwi r3, r4, 2
/* 80068668 00065248  7C 60 1A 14 */	add r3, r0, r3
/* 8006866C 0006524C  81 83 00 00 */	lwz r12, 0(r3)
/* 80068670 00065250  28 0C 00 00 */	cmplwi r12, 0
/* 80068674 00065254  41 82 00 10 */	beq lbl_80068684
/* 80068678 00065258  7D 88 03 A6 */	mtlr r12
/* 8006867C 0006525C  38 7E 00 00 */	addi r3, r30, 0
/* 80068680 00065260  4E 80 00 21 */	blrl 
lbl_80068684:
/* 80068684 00065264  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 80068688 00065268  4B FC AE C1 */	bl Player_GetCpuLevel
/* 8006868C 0006526C  7C 7D 1B 78 */	mr r29, r3
/* 80068690 00065270  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 80068694 00065274  4B FC AF DD */	bl Player_GetCpuType
/* 80068698 00065278  38 83 00 00 */	addi r4, r3, 0
/* 8006869C 0006527C  38 7F 00 00 */	addi r3, r31, 0
/* 800686A0 00065280  38 BD 00 00 */	addi r5, r29, 0
/* 800686A4 00065284  38 C0 00 00 */	li r6, 0
/* 800686A8 00065288  48 03 89 75 */	bl func_800A101C
/* 800686AC 0006528C  38 7F 06 0C */	addi r3, r31, 0x60c
/* 800686B0 00065290  4B FF EF D9 */	bl func_80067688
/* 800686B4 00065294  7F C3 F3 78 */	mr r3, r30
/* 800686B8 00065298  48 01 3A C5 */	bl func_8007C17C
/* 800686BC 0006529C  7F C3 F3 78 */	mr r3, r30
/* 800686C0 000652A0  48 01 3F 71 */	bl func_8007C630
/* 800686C4 000652A4  80 01 00 44 */	lwz r0, 0x44(r1)
/* 800686C8 000652A8  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 800686CC 000652AC  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 800686D0 000652B0  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 800686D4 000652B4  83 81 00 30 */	lwz r28, 0x30(r1)
/* 800686D8 000652B8  38 21 00 40 */	addi r1, r1, 0x40
/* 800686DC 000652BC  7C 08 03 A6 */	mtlr r0
/* 800686E0 000652C0  4E 80 00 20 */	blr  
}


asm void func_800686E4()
{
	nofralloc 
/* 800686E4 000652C4  7C 08 02 A6 */	mflr r0
/* 800686E8 000652C8  90 01 00 04 */	stw r0, 4(r1)
/* 800686EC 000652CC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800686F0 000652D0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800686F4 000652D4  93 C1 00 10 */	stw r30, 0x10(r1)
/* 800686F8 000652D8  7C 7E 1B 78 */	mr r30, r3
/* 800686FC 000652DC  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80068700 000652E0  3C 60 80 3C */	lis r3, lbl_803C0EC0@ha
/* 80068704 000652E4  38 63 0E C0 */	addi r3, r3, lbl_803C0EC0@l
/* 80068708 000652E8  80 9F 00 04 */	lwz r4, 4(r31)
/* 8006870C 000652EC  88 1F 06 19 */	lbz r0, 0x619(r31)
/* 80068710 000652F0  54 84 18 38 */	slwi r4, r4, 3
/* 80068714 000652F4  7C 63 22 14 */	add r3, r3, r4
/* 80068718 000652F8  1C 00 00 18 */	mulli r0, r0, 0x18
/* 8006871C 000652FC  80 63 00 00 */	lwz r3, 0(r3)
/* 80068720 00065300  7C 03 00 2E */	lwzx r0, r3, r0
/* 80068724 00065304  90 1F 01 08 */	stw r0, 0x108(r31)
/* 80068728 00065308  48 00 BA 21 */	bl func_80074148
/* 8006872C 0006530C  80 7F 01 08 */	lwz r3, 0x108(r31)
/* 80068730 00065310  48 30 87 15 */	bl HSD_JObjLoadJoint
/* 80068734 00065314  7C 7F 1B 78 */	mr r31, r3
/* 80068738 00065318  48 00 BA 39 */	bl func_80074170
/* 8006873C 0006531C  7F E3 FB 78 */	mr r3, r31
/* 80068740 00065320  48 00 B0 19 */	bl func_80073758
/* 80068744 00065324  88 8D C1 A9 */	lbz r4, lbl_804D7849(r13)
/* 80068748 00065328  38 7E 00 00 */	addi r3, r30, 0
/* 8006874C 0006532C  38 BF 00 00 */	addi r5, r31, 0
/* 80068750 00065330  48 32 83 21 */	bl func_80390A70
/* 80068754 00065334  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80068758 00065338  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8006875C 0006533C  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80068760 00065340  38 21 00 18 */	addi r1, r1, 0x18
/* 80068764 00065344  7C 08 03 A6 */	mtlr r0
/* 80068768 00065348  4E 80 00 20 */	blr  
}


asm void func_8006876C()
{
	nofralloc 
/* 8006876C 0006534C  7C 08 02 A6 */	mflr r0
/* 80068770 00065350  38 80 00 02 */	li r4, 2
/* 80068774 00065354  90 01 00 04 */	stw r0, 4(r1)
/* 80068778 00065358  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8006877C 0006535C  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 80068780 00065360  93 C1 00 28 */	stw r30, 0x28(r1)
/* 80068784 00065364  3B C3 00 00 */	addi r30, r3, 0
/* 80068788 00065368  48 00 C8 85 */	bl func_8007500C
/* 8006878C 0006536C  80 9E 05 E8 */	lwz r4, 0x5e8(r30)
/* 80068790 00065370  54 60 20 36 */	slwi r0, r3, 4
/* 80068794 00065374  7F E4 00 2E */	lwzx r31, r4, r0
/* 80068798 00065378  28 1F 00 00 */	cmplwi r31, 0
/* 8006879C 0006537C  40 82 00 14 */	bne lbl_800687B0
/* 800687A0 00065380  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 800687A4 00065384  38 80 03 D3 */	li r4, 0x3d3
/* 800687A8 00065388  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 800687AC 0006538C  48 31 FA 75 */	bl __assert
lbl_800687B0:
/* 800687B0 00065390  80 9F 00 38 */	lwz r4, 0x38(r31)
/* 800687B4 00065394  7F E3 FB 78 */	mr r3, r31
/* 800687B8 00065398  80 1F 00 3C */	lwz r0, 0x3c(r31)
/* 800687BC 0006539C  38 A1 00 18 */	addi r5, r1, 0x18
/* 800687C0 000653A0  C0 02 88 88 */	lfs f0, lbl_804D8268(r2)
/* 800687C4 000653A4  90 81 00 18 */	stw r4, 0x18(r1)
/* 800687C8 000653A8  38 80 00 00 */	li r4, 0
/* 800687CC 000653AC  90 01 00 1C */	stw r0, 0x1c(r1)
/* 800687D0 000653B0  80 1F 00 40 */	lwz r0, 0x40(r31)
/* 800687D4 000653B4  90 01 00 20 */	stw r0, 0x20(r1)
/* 800687D8 000653B8  C0 21 00 1C */	lfs f1, 0x1c(r1)
/* 800687DC 000653BC  EC 01 00 24 */	fdivs f0, f1, f0
/* 800687E0 000653C0  D0 1E 1A 6C */	stfs f0, 0x1a6c(r30)
/* 800687E4 000653C4  4B FA 29 E9 */	bl func_8000B1CC
/* 800687E8 000653C8  38 7E 00 00 */	addi r3, r30, 0
/* 800687EC 000653CC  38 80 00 01 */	li r4, 1
/* 800687F0 000653D0  48 00 C8 1D */	bl func_8007500C
/* 800687F4 000653D4  80 9E 05 E8 */	lwz r4, 0x5e8(r30)
/* 800687F8 000653D8  54 60 20 36 */	slwi r0, r3, 4
/* 800687FC 000653DC  38 A1 00 0C */	addi r5, r1, 0xc
/* 80068800 000653E0  7C 64 00 2E */	lwzx r3, r4, r0
/* 80068804 000653E4  38 80 00 00 */	li r4, 0
/* 80068808 000653E8  4B FA 29 C5 */	bl func_8000B1CC
/* 8006880C 000653EC  C0 21 00 0C */	lfs f1, 0xc(r1)
/* 80068810 000653F0  C0 01 00 18 */	lfs f0, 0x18(r1)
/* 80068814 000653F4  EC 01 00 28 */	fsubs f0, f1, f0
/* 80068818 000653F8  D0 1E 1A 70 */	stfs f0, 0x1a70(r30)
/* 8006881C 000653FC  C0 21 00 10 */	lfs f1, 0x10(r1)
/* 80068820 00065400  C0 01 00 1C */	lfs f0, 0x1c(r1)
/* 80068824 00065404  EC 01 00 28 */	fsubs f0, f1, f0
/* 80068828 00065408  D0 1E 1A 74 */	stfs f0, 0x1a74(r30)
/* 8006882C 0006540C  C0 21 00 14 */	lfs f1, 0x14(r1)
/* 80068830 00065410  C0 01 00 20 */	lfs f0, 0x20(r1)
/* 80068834 00065414  EC 01 00 28 */	fsubs f0, f1, f0
/* 80068838 00065418  D0 1E 1A 78 */	stfs f0, 0x1a78(r30)
/* 8006883C 0006541C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80068840 00065420  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 80068844 00065424  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 80068848 00065428  38 21 00 30 */	addi r1, r1, 0x30
/* 8006884C 0006542C  7C 08 03 A6 */	mtlr r0
/* 80068850 00065430  4E 80 00 20 */	blr  
}


asm void func_80068854()
{
	nofralloc 
/* 80068854 00065434  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 80068858 00065438  38 80 00 00 */	li r4, 0
/* 8006885C 0006543C  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 80068860 00065440  38 60 00 FE */	li r3, 0xfe
/* 80068864 00065444  38 00 00 FF */	li r0, 0xff
/* 80068868 00065448  D0 05 06 2C */	stfs f0, 0x62c(r5)
/* 8006886C 0006544C  D0 05 06 28 */	stfs f0, 0x628(r5)
/* 80068870 00065450  D0 05 06 24 */	stfs f0, 0x624(r5)
/* 80068874 00065454  D0 05 06 20 */	stfs f0, 0x620(r5)
/* 80068878 00065458  D0 05 06 44 */	stfs f0, 0x644(r5)
/* 8006887C 0006545C  D0 05 06 40 */	stfs f0, 0x640(r5)
/* 80068880 00065460  D0 05 06 3C */	stfs f0, 0x63c(r5)
/* 80068884 00065464  D0 05 06 38 */	stfs f0, 0x638(r5)
/* 80068888 00065468  D0 05 06 54 */	stfs f0, 0x654(r5)
/* 8006888C 0006546C  D0 05 06 50 */	stfs f0, 0x650(r5)
/* 80068890 00065470  90 85 06 60 */	stw r4, 0x660(r5)
/* 80068894 00065474  90 85 06 6C */	stw r4, 0x66c(r5)
/* 80068898 00065478  90 85 06 68 */	stw r4, 0x668(r5)
/* 8006889C 0006547C  90 85 06 5C */	stw r4, 0x65c(r5)
/* 800688A0 00065480  98 65 06 72 */	stb r3, 0x672(r5)
/* 800688A4 00065484  98 65 06 71 */	stb r3, 0x671(r5)
/* 800688A8 00065488  98 65 06 70 */	stb r3, 0x670(r5)
/* 800688AC 0006548C  98 65 06 75 */	stb r3, 0x675(r5)
/* 800688B0 00065490  98 65 06 74 */	stb r3, 0x674(r5)
/* 800688B4 00065494  98 65 06 73 */	stb r3, 0x673(r5)
/* 800688B8 00065498  98 65 06 78 */	stb r3, 0x678(r5)
/* 800688BC 0006549C  98 65 06 77 */	stb r3, 0x677(r5)
/* 800688C0 000654A0  98 65 06 76 */	stb r3, 0x676(r5)
/* 800688C4 000654A4  98 65 06 7B */	stb r3, 0x67b(r5)
/* 800688C8 000654A8  98 65 06 7A */	stb r3, 0x67a(r5)
/* 800688CC 000654AC  98 65 06 79 */	stb r3, 0x679(r5)
/* 800688D0 000654B0  98 05 06 8B */	stb r0, 0x68b(r5)
/* 800688D4 000654B4  98 05 06 8A */	stb r0, 0x68a(r5)
/* 800688D8 000654B8  98 05 06 89 */	stb r0, 0x689(r5)
/* 800688DC 000654BC  98 05 06 88 */	stb r0, 0x688(r5)
/* 800688E0 000654C0  98 05 06 87 */	stb r0, 0x687(r5)
/* 800688E4 000654C4  98 05 06 86 */	stb r0, 0x686(r5)
/* 800688E8 000654C8  98 05 06 85 */	stb r0, 0x685(r5)
/* 800688EC 000654CC  98 05 06 84 */	stb r0, 0x684(r5)
/* 800688F0 000654D0  98 05 06 83 */	stb r0, 0x683(r5)
/* 800688F4 000654D4  98 05 06 80 */	stb r0, 0x680(r5)
/* 800688F8 000654D8  98 05 06 7F */	stb r0, 0x67f(r5)
/* 800688FC 000654DC  98 05 06 82 */	stb r0, 0x682(r5)
/* 80068900 000654E0  98 05 06 81 */	stb r0, 0x681(r5)
/* 80068904 000654E4  98 05 06 7E */	stb r0, 0x67e(r5)
/* 80068908 000654E8  98 05 06 7D */	stb r0, 0x67d(r5)
/* 8006890C 000654EC  98 05 06 7C */	stb r0, 0x67c(r5)
/* 80068910 000654F0  4E 80 00 20 */	blr  
}


asm void func_80068914()
{
	nofralloc 
/* 80068914 000654F4  7C 08 02 A6 */	mflr r0
/* 80068918 000654F8  90 01 00 04 */	stw r0, 4(r1)
/* 8006891C 000654FC  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80068920 00065500  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80068924 00065504  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80068928 00065508  3B C3 00 00 */	addi r30, r3, 0
/* 8006892C 0006550C  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 80068930 00065510  3B A4 00 00 */	addi r29, r4, 0
/* 80068934 00065514  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80068938 00065518  80 04 00 00 */	lwz r0, 0(r4)
/* 8006893C 0006551C  90 1F 00 04 */	stw r0, 4(r31)
/* 80068940 00065520  88 04 00 04 */	lbz r0, 4(r4)
/* 80068944 00065524  98 1F 00 0C */	stb r0, 0xc(r31)
/* 80068948 00065528  88 64 00 06 */	lbz r3, 6(r4)
/* 8006894C 0006552C  88 1F 22 1F */	lbz r0, 0x221f(r31)
/* 80068950 00065530  50 60 E7 38 */	rlwimi r0, r3, 0x1c, 0x1c, 0x1c
/* 80068954 00065534  98 1F 22 1F */	stb r0, 0x221f(r31)
/* 80068958 00065538  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 8006895C 0006553C  4B FC B1 71 */	bl Player_GetModelScale
/* 80068960 00065540  D0 3F 00 34 */	stfs f1, 0x34(r31)
/* 80068964 00065544  88 1D 00 05 */	lbz r0, 5(r29)
/* 80068968 00065548  98 1F 06 1C */	stb r0, 0x61c(r31)
/* 8006896C 0006554C  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 80068970 00065550  4B FC AA ED */	bl Player_GetPlayerId
/* 80068974 00065554  98 7F 06 18 */	stb r3, 0x618(r31)
/* 80068978 00065558  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 8006897C 0006555C  4B FC A9 09 */	bl Player_GetControllerIndex
/* 80068980 00065560  98 7F 06 1A */	stb r3, 0x61a(r31)
/* 80068984 00065564  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 80068988 00065568  4B FC CF AD */	bl Player_GetFlagsBit5
/* 8006898C 0006556C  88 1F 22 23 */	lbz r0, 0x2223(r31)
/* 80068990 00065570  50 60 0F BC */	rlwimi r0, r3, 1, 0x1e, 0x1e
/* 80068994 00065574  98 1F 22 23 */	stb r0, 0x2223(r31)
/* 80068998 00065578  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 8006899C 0006557C  4B FC D0 91 */	bl Player_GetFlagsBit6
/* 800689A0 00065580  88 1F 22 26 */	lbz r0, 0x2226(r31)
/* 800689A4 00065584  50 60 26 F6 */	rlwimi r0, r3, 4, 0x1b, 0x1b
/* 800689A8 00065588  98 1F 22 26 */	stb r0, 0x2226(r31)
/* 800689AC 0006558C  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 800689B0 00065590  4B FC D1 75 */	bl Player_GetFlagsBit7
/* 800689B4 00065594  88 1F 22 26 */	lbz r0, 0x2226(r31)
/* 800689B8 00065598  50 60 0F BC */	rlwimi r0, r3, 1, 0x1e, 0x1e
/* 800689BC 0006559C  98 1F 22 26 */	stb r0, 0x2226(r31)
/* 800689C0 000655A0  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 800689C4 000655A4  4B FC D2 CD */	bl Player_GetMoreFlagsBit1
/* 800689C8 000655A8  88 1F 22 25 */	lbz r0, 0x2225(r31)
/* 800689CC 000655AC  50 60 17 7A */	rlwimi r0, r3, 2, 0x1d, 0x1d
/* 800689D0 000655B0  98 1F 22 25 */	stb r0, 0x2225(r31)
/* 800689D4 000655B4  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 800689D8 000655B8  4B FC BC 5D */	bl Player_GetMoreFlagsBit2
/* 800689DC 000655BC  88 1F 22 25 */	lbz r0, 0x2225(r31)
/* 800689E0 000655C0  50 60 07 FE */	rlwimi r0, r3, 0, 0x1f, 0x1f
/* 800689E4 000655C4  98 1F 22 25 */	stb r0, 0x2225(r31)
/* 800689E8 000655C8  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 800689EC 000655CC  4B FC C0 29 */	bl Player_GetMoreFlagsBit6
/* 800689F0 000655D0  88 1F 22 28 */	lbz r0, 0x2228(r31)
/* 800689F4 000655D4  50 60 1E F8 */	rlwimi r0, r3, 3, 0x1b, 0x1c
/* 800689F8 000655D8  98 1F 22 28 */	stb r0, 0x2228(r31)
/* 800689FC 000655DC  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 80068A00 000655E0  4B FC C1 0D */	bl Player_GetFlagsAEBit0
/* 80068A04 000655E4  88 1F 22 29 */	lbz r0, 0x2229(r31)
/* 80068A08 000655E8  50 60 36 72 */	rlwimi r0, r3, 6, 0x19, 0x19
/* 80068A0C 000655EC  98 1F 22 29 */	stb r0, 0x2229(r31)
/* 80068A10 000655F0  88 1F 06 1A */	lbz r0, 0x61a(r31)
/* 80068A14 000655F4  28 00 00 04 */	cmplwi r0, 4
/* 80068A18 000655F8  40 81 00 28 */	ble lbl_80068A40
/* 80068A1C 000655FC  3C 60 80 3C */	lis r3, lbl_803C055C@ha
/* 80068A20 00065600  4C C6 31 82 */	crclr 6
/* 80068A24 00065604  38 63 05 5C */	addi r3, r3, lbl_803C055C@l
/* 80068A28 00065608  48 2D CC 81 */	bl OSReport
/* 80068A2C 0006560C  3C 60 80 3C */	lis r3, lbl_803C057C@ha
/* 80068A30 00065610  38 63 05 7C */	addi r3, r3, lbl_803C057C@l
/* 80068A34 00065614  38 80 03 3C */	li r4, 0x33c
/* 80068A38 00065618  38 AD 83 70 */	addi r5, r13, lbl_804D3A10
/* 80068A3C 0006561C  48 31 F7 E5 */	bl __assert
lbl_80068A40:
/* 80068A40 00065620  88 7F 06 1A */	lbz r3, 0x61a(r31)
/* 80068A44 00065624  28 03 00 00 */	cmplwi r3, 0
/* 80068A48 00065628  41 82 00 94 */	beq lbl_80068ADC
/* 80068A4C 0006562C  38 03 FF FF */	addi r0, r3, -1
/* 80068A50 00065630  80 8D AE B4 */	lwz r4, lbl_804D6554(r13)
/* 80068A54 00065634  54 03 10 3A */	slwi r3, r0, 2
/* 80068A58 00065638  38 63 06 DC */	addi r3, r3, 0x6dc
/* 80068A5C 0006563C  7C 64 1A 14 */	add r3, r4, r3
/* 80068A60 00065640  88 A3 00 00 */	lbz r5, 0(r3)
/* 80068A64 00065644  3C 80 80 81 */	lis r4, 0x80808081@ha
/* 80068A68 00065648  88 03 00 03 */	lbz r0, 3(r3)
/* 80068A6C 0006564C  38 C4 80 81 */	addi r6, r4, 0x80808081@l
/* 80068A70 00065650  7C 05 01 D6 */	mullw r0, r5, r0
/* 80068A74 00065654  7C 86 00 96 */	mulhw r4, r6, r0
/* 80068A78 00065658  7C 04 02 14 */	add r0, r4, r0
/* 80068A7C 0006565C  7C 00 3E 70 */	srawi r0, r0, 7
/* 80068A80 00065660  54 04 0F FE */	srwi r4, r0, 0x1f
/* 80068A84 00065664  7C 00 22 14 */	add r0, r0, r4
/* 80068A88 00065668  98 1F 06 10 */	stb r0, 0x610(r31)
/* 80068A8C 0006566C  88 83 00 01 */	lbz r4, 1(r3)
/* 80068A90 00065670  88 03 00 03 */	lbz r0, 3(r3)
/* 80068A94 00065674  7C 04 01 D6 */	mullw r0, r4, r0
/* 80068A98 00065678  7C 86 00 96 */	mulhw r4, r6, r0
/* 80068A9C 0006567C  7C 04 02 14 */	add r0, r4, r0
/* 80068AA0 00065680  7C 00 3E 70 */	srawi r0, r0, 7
/* 80068AA4 00065684  54 04 0F FE */	srwi r4, r0, 0x1f
/* 80068AA8 00065688  7C 00 22 14 */	add r0, r0, r4
/* 80068AAC 0006568C  98 1F 06 11 */	stb r0, 0x611(r31)
/* 80068AB0 00065690  88 83 00 02 */	lbz r4, 2(r3)
/* 80068AB4 00065694  88 03 00 03 */	lbz r0, 3(r3)
/* 80068AB8 00065698  7C 04 01 D6 */	mullw r0, r4, r0
/* 80068ABC 0006569C  7C 86 00 96 */	mulhw r4, r6, r0
/* 80068AC0 000656A0  7C 04 02 14 */	add r0, r4, r0
/* 80068AC4 000656A4  7C 00 3E 70 */	srawi r0, r0, 7
/* 80068AC8 000656A8  54 04 0F FE */	srwi r4, r0, 0x1f
/* 80068ACC 000656AC  7C 00 22 14 */	add r0, r0, r4
/* 80068AD0 000656B0  98 1F 06 12 */	stb r0, 0x612(r31)
/* 80068AD4 000656B4  88 03 00 03 */	lbz r0, 3(r3)
/* 80068AD8 000656B8  98 1F 06 13 */	stb r0, 0x613(r31)
lbl_80068ADC:
/* 80068ADC 000656BC  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 80068AE0 000656C0  4B FC A6 B9 */	bl Player_GetCostumeId
/* 80068AE4 000656C4  80 1F 00 04 */	lwz r0, 4(r31)
/* 80068AE8 000656C8  3C 80 80 3C */	lis r4, lbl_803C0EC0@ha
/* 80068AEC 000656CC  38 84 0E C0 */	addi r4, r4, lbl_803C0EC0@l
/* 80068AF0 000656D0  54 00 18 38 */	slwi r0, r0, 3
/* 80068AF4 000656D4  7C 84 02 14 */	add r4, r4, r0
/* 80068AF8 000656D8  88 04 00 04 */	lbz r0, 4(r4)
/* 80068AFC 000656DC  7C 03 00 00 */	cmpw r3, r0
/* 80068B00 000656E0  41 80 00 08 */	blt lbl_80068B08
/* 80068B04 000656E4  38 60 00 00 */	li r3, 0
lbl_80068B08:
/* 80068B08 000656E8  98 7F 06 19 */	stb r3, 0x619(r31)
/* 80068B0C 000656EC  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 80068B10 000656F0  4B FC A8 61 */	bl Player_GetTeam
/* 80068B14 000656F4  98 7F 06 1B */	stb r3, 0x61b(r31)
/* 80068B18 000656F8  3C 60 80 46 */	lis r3, lbl_804598B8@ha
/* 80068B1C 000656FC  38 03 98 B8 */	addi r0, r3, lbl_804598B8@l
/* 80068B20 00065700  93 DF 00 00 */	stw r30, 0(r31)
/* 80068B24 00065704  7F C3 F3 78 */	mr r3, r30
/* 80068B28 00065708  80 9F 00 04 */	lwz r4, 4(r31)
/* 80068B2C 0006570C  54 84 10 3A */	slwi r4, r4, 2
/* 80068B30 00065710  7C 80 22 14 */	add r4, r0, r4
/* 80068B34 00065714  80 04 00 00 */	lwz r0, 0(r4)
/* 80068B38 00065718  90 1F 01 0C */	stw r0, 0x10c(r31)
/* 80068B3C 0006571C  48 06 84 65 */	bl func_800D0FA0
/* 80068B40 00065720  38 00 00 00 */	li r0, 0
/* 80068B44 00065724  90 1F 02 CC */	stw r0, 0x2cc(r31)
/* 80068B48 00065728  3C 80 80 3C */	lis r4, lbl_803C2800@ha
/* 80068B4C 0006572C  3C 60 80 3C */	lis r3, lbl_803C12E0@ha
/* 80068B50 00065730  90 1F 02 D0 */	stw r0, 0x2d0(r31)
/* 80068B54 00065734  38 A0 01 55 */	li r5, 0x155
/* 80068B58 00065738  38 84 28 00 */	addi r4, r4, lbl_803C2800@l
/* 80068B5C 0006573C  90 BF 00 18 */	stw r5, 0x18(r31)
/* 80068B60 00065740  38 C3 12 E0 */	addi r6, r3, lbl_803C12E0@l
/* 80068B64 00065744  38 A0 00 FE */	li r5, 0xfe
/* 80068B68 00065748  90 9F 00 1C */	stw r4, 0x1c(r31)
/* 80068B6C 0006574C  38 80 00 FF */	li r4, 0xff
/* 80068B70 00065750  38 60 00 01 */	li r3, 1
/* 80068B74 00065754  80 FF 00 04 */	lwz r7, 4(r31)
/* 80068B78 00065758  54 E7 10 3A */	slwi r7, r7, 2
/* 80068B7C 0006575C  7C C6 3A 14 */	add r6, r6, r7
/* 80068B80 00065760  80 C6 00 00 */	lwz r6, 0(r6)
/* 80068B84 00065764  90 DF 00 20 */	stw r6, 0x20(r31)
/* 80068B88 00065768  80 DF 01 0C */	lwz r6, 0x10c(r31)
/* 80068B8C 0006576C  80 C6 00 0C */	lwz r6, 0xc(r6)
/* 80068B90 00065770  90 DF 00 24 */	stw r6, 0x24(r31)
/* 80068B94 00065774  80 DF 01 0C */	lwz r6, 0x10c(r31)
/* 80068B98 00065778  80 C6 00 10 */	lwz r6, 0x10(r6)
/* 80068B9C 0006577C  90 DF 00 28 */	stw r6, 0x28(r31)
/* 80068BA0 00065780  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 80068BA4 00065784  D0 1F 06 34 */	stfs f0, 0x634(r31)
/* 80068BA8 00065788  D0 1F 06 30 */	stfs f0, 0x630(r31)
/* 80068BAC 0006578C  D0 1F 06 4C */	stfs f0, 0x64c(r31)
/* 80068BB0 00065790  D0 1F 06 48 */	stfs f0, 0x648(r31)
/* 80068BB4 00065794  D0 1F 06 58 */	stfs f0, 0x658(r31)
/* 80068BB8 00065798  90 1F 06 64 */	stw r0, 0x664(r31)
/* 80068BBC 0006579C  80 DE 00 2C */	lwz r6, 0x2c(r30)
/* 80068BC0 000657A0  D0 06 06 2C */	stfs f0, 0x62c(r6)
/* 80068BC4 000657A4  D0 06 06 28 */	stfs f0, 0x628(r6)
/* 80068BC8 000657A8  D0 06 06 24 */	stfs f0, 0x624(r6)
/* 80068BCC 000657AC  D0 06 06 20 */	stfs f0, 0x620(r6)
/* 80068BD0 000657B0  D0 06 06 44 */	stfs f0, 0x644(r6)
/* 80068BD4 000657B4  D0 06 06 40 */	stfs f0, 0x640(r6)
/* 80068BD8 000657B8  D0 06 06 3C */	stfs f0, 0x63c(r6)
/* 80068BDC 000657BC  D0 06 06 38 */	stfs f0, 0x638(r6)
/* 80068BE0 000657C0  D0 06 06 54 */	stfs f0, 0x654(r6)
/* 80068BE4 000657C4  D0 06 06 50 */	stfs f0, 0x650(r6)
/* 80068BE8 000657C8  90 06 06 60 */	stw r0, 0x660(r6)
/* 80068BEC 000657CC  90 06 06 6C */	stw r0, 0x66c(r6)
/* 80068BF0 000657D0  90 06 06 68 */	stw r0, 0x668(r6)
/* 80068BF4 000657D4  90 06 06 5C */	stw r0, 0x65c(r6)
/* 80068BF8 000657D8  98 A6 06 72 */	stb r5, 0x672(r6)
/* 80068BFC 000657DC  98 A6 06 71 */	stb r5, 0x671(r6)
/* 80068C00 000657E0  98 A6 06 70 */	stb r5, 0x670(r6)
/* 80068C04 000657E4  98 A6 06 75 */	stb r5, 0x675(r6)
/* 80068C08 000657E8  98 A6 06 74 */	stb r5, 0x674(r6)
/* 80068C0C 000657EC  98 A6 06 73 */	stb r5, 0x673(r6)
/* 80068C10 000657F0  98 A6 06 78 */	stb r5, 0x678(r6)
/* 80068C14 000657F4  98 A6 06 77 */	stb r5, 0x677(r6)
/* 80068C18 000657F8  98 A6 06 76 */	stb r5, 0x676(r6)
/* 80068C1C 000657FC  98 A6 06 7B */	stb r5, 0x67b(r6)
/* 80068C20 00065800  98 A6 06 7A */	stb r5, 0x67a(r6)
/* 80068C24 00065804  98 A6 06 79 */	stb r5, 0x679(r6)
/* 80068C28 00065808  98 86 06 8B */	stb r4, 0x68b(r6)
/* 80068C2C 0006580C  98 86 06 8A */	stb r4, 0x68a(r6)
/* 80068C30 00065810  98 86 06 89 */	stb r4, 0x689(r6)
/* 80068C34 00065814  98 86 06 88 */	stb r4, 0x688(r6)
/* 80068C38 00065818  98 86 06 87 */	stb r4, 0x687(r6)
/* 80068C3C 0006581C  98 86 06 86 */	stb r4, 0x686(r6)
/* 80068C40 00065820  98 86 06 85 */	stb r4, 0x685(r6)
/* 80068C44 00065824  98 86 06 84 */	stb r4, 0x684(r6)
/* 80068C48 00065828  98 86 06 83 */	stb r4, 0x683(r6)
/* 80068C4C 0006582C  98 86 06 80 */	stb r4, 0x680(r6)
/* 80068C50 00065830  98 86 06 7F */	stb r4, 0x67f(r6)
/* 80068C54 00065834  98 86 06 82 */	stb r4, 0x682(r6)
/* 80068C58 00065838  98 86 06 81 */	stb r4, 0x681(r6)
/* 80068C5C 0006583C  98 86 06 7E */	stb r4, 0x67e(r6)
/* 80068C60 00065840  98 86 06 7D */	stb r4, 0x67d(r6)
/* 80068C64 00065844  98 86 06 7C */	stb r4, 0x67c(r6)
/* 80068C68 00065848  90 1F 05 94 */	stw r0, 0x594(r31)
/* 80068C6C 0006584C  98 7F 21 FC */	stb r3, 0x21fc(r31)
/* 80068C70 00065850  88 7F 22 1E */	lbz r3, 0x221e(r31)
/* 80068C74 00065854  50 03 3E 30 */	rlwimi r3, r0, 7, 0x18, 0x18
/* 80068C78 00065858  98 7F 22 1E */	stb r3, 0x221e(r31)
/* 80068C7C 0006585C  88 7F 22 1E */	lbz r3, 0x221e(r31)
/* 80068C80 00065860  50 03 36 72 */	rlwimi r3, r0, 6, 0x19, 0x19
/* 80068C84 00065864  98 7F 22 1E */	stb r3, 0x221e(r31)
/* 80068C88 00065868  88 7F 22 1E */	lbz r3, 0x221e(r31)
/* 80068C8C 0006586C  50 03 2E B4 */	rlwimi r3, r0, 5, 0x1a, 0x1a
/* 80068C90 00065870  98 7F 22 1E */	stb r3, 0x221e(r31)
/* 80068C94 00065874  88 9F 22 1F */	lbz r4, 0x221f(r31)
/* 80068C98 00065878  50 04 36 72 */	rlwimi r4, r0, 6, 0x19, 0x19
/* 80068C9C 0006587C  38 60 FF FF */	li r3, -1
/* 80068CA0 00065880  98 9F 22 1F */	stb r4, 0x221f(r31)
/* 80068CA4 00065884  88 9F 22 1F */	lbz r4, 0x221f(r31)
/* 80068CA8 00065888  50 04 2E B4 */	rlwimi r4, r0, 5, 0x1a, 0x1a
/* 80068CAC 0006588C  98 9F 22 1F */	stb r4, 0x221f(r31)
/* 80068CB0 00065890  B0 1F 20 9A */	sth r0, 0x209a(r31)
/* 80068CB4 00065894  88 9F 22 1E */	lbz r4, 0x221e(r31)
/* 80068CB8 00065898  50 04 17 7A */	rlwimi r4, r0, 2, 0x1d, 0x1d
/* 80068CBC 0006589C  98 9F 22 1E */	stb r4, 0x221e(r31)
/* 80068CC0 000658A0  88 9F 22 1F */	lbz r4, 0x221f(r31)
/* 80068CC4 000658A4  50 04 3E 30 */	rlwimi r4, r0, 7, 0x18, 0x18
/* 80068CC8 000658A8  98 9F 22 1F */	stb r4, 0x221f(r31)
/* 80068CCC 000658AC  90 1F 21 EC */	stw r0, 0x21ec(r31)
/* 80068CD0 000658B0  88 9F 22 1D */	lbz r4, 0x221d(r31)
/* 80068CD4 000658B4  50 04 26 F6 */	rlwimi r4, r0, 4, 0x1b, 0x1b
/* 80068CD8 000658B8  98 9F 22 1D */	stb r4, 0x221d(r31)
/* 80068CDC 000658BC  88 9F 22 1D */	lbz r4, 0x221d(r31)
/* 80068CE0 000658C0  50 04 1F 38 */	rlwimi r4, r0, 3, 0x1c, 0x1c
/* 80068CE4 000658C4  98 9F 22 1D */	stb r4, 0x221d(r31)
/* 80068CE8 000658C8  88 9F 22 1F */	lbz r4, 0x221f(r31)
/* 80068CEC 000658CC  50 04 26 F6 */	rlwimi r4, r0, 4, 0x1b, 0x1b
/* 80068CF0 000658D0  98 9F 22 1F */	stb r4, 0x221f(r31)
/* 80068CF4 000658D4  88 9F 22 20 */	lbz r4, 0x2220(r31)
/* 80068CF8 000658D8  50 04 2E 34 */	rlwimi r4, r0, 5, 0x18, 0x1a
/* 80068CFC 000658DC  98 9F 22 20 */	stb r4, 0x2220(r31)
/* 80068D00 000658E0  88 9F 22 21 */	lbz r4, 0x2221(r31)
/* 80068D04 000658E4  50 04 2E B4 */	rlwimi r4, r0, 5, 0x1a, 0x1a
/* 80068D08 000658E8  98 9F 22 21 */	stb r4, 0x2221(r31)
/* 80068D0C 000658EC  88 9F 22 29 */	lbz r4, 0x2229(r31)
/* 80068D10 000658F0  50 04 17 7A */	rlwimi r4, r0, 2, 0x1d, 0x1d
/* 80068D14 000658F4  98 9F 22 29 */	stb r4, 0x2229(r31)
/* 80068D18 000658F8  88 9F 22 29 */	lbz r4, 0x2229(r31)
/* 80068D1C 000658FC  50 04 0F BC */	rlwimi r4, r0, 1, 0x1e, 0x1e
/* 80068D20 00065900  98 9F 22 29 */	stb r4, 0x2229(r31)
/* 80068D24 00065904  88 9F 22 29 */	lbz r4, 0x2229(r31)
/* 80068D28 00065908  50 04 07 FE */	rlwimi r4, r0, 0, 0x1f, 0x1f
/* 80068D2C 0006590C  98 9F 22 29 */	stb r4, 0x2229(r31)
/* 80068D30 00065910  88 9F 22 2A */	lbz r4, 0x222a(r31)
/* 80068D34 00065914  50 04 3E 30 */	rlwimi r4, r0, 7, 0x18, 0x18
/* 80068D38 00065918  98 9F 22 2A */	stb r4, 0x222a(r31)
/* 80068D3C 0006591C  88 9F 22 2A */	lbz r4, 0x222a(r31)
/* 80068D40 00065920  50 04 36 72 */	rlwimi r4, r0, 6, 0x19, 0x19
/* 80068D44 00065924  98 9F 22 2A */	stb r4, 0x222a(r31)
/* 80068D48 00065928  88 9F 22 28 */	lbz r4, 0x2228(r31)
/* 80068D4C 0006592C  50 04 17 7A */	rlwimi r4, r0, 2, 0x1d, 0x1d
/* 80068D50 00065930  98 9F 22 28 */	stb r4, 0x2228(r31)
/* 80068D54 00065934  88 9F 22 28 */	lbz r4, 0x2228(r31)
/* 80068D58 00065938  50 04 0F BC */	rlwimi r4, r0, 1, 0x1e, 0x1e
/* 80068D5C 0006593C  98 9F 22 28 */	stb r4, 0x2228(r31)
/* 80068D60 00065940  88 9F 22 21 */	lbz r4, 0x2221(r31)
/* 80068D64 00065944  50 04 26 F6 */	rlwimi r4, r0, 4, 0x1b, 0x1b
/* 80068D68 00065948  98 9F 22 21 */	stb r4, 0x2221(r31)
/* 80068D6C 0006594C  88 9F 22 22 */	lbz r4, 0x2222(r31)
/* 80068D70 00065950  50 04 3E 30 */	rlwimi r4, r0, 7, 0x18, 0x18
/* 80068D74 00065954  98 9F 22 22 */	stb r4, 0x2222(r31)
/* 80068D78 00065958  88 9F 22 22 */	lbz r4, 0x2222(r31)
/* 80068D7C 0006595C  50 04 36 72 */	rlwimi r4, r0, 6, 0x19, 0x19
/* 80068D80 00065960  98 9F 22 22 */	stb r4, 0x2222(r31)
/* 80068D84 00065964  88 9F 22 22 */	lbz r4, 0x2222(r31)
/* 80068D88 00065968  50 04 1F 38 */	rlwimi r4, r0, 3, 0x1c, 0x1c
/* 80068D8C 0006596C  98 9F 22 22 */	stb r4, 0x2222(r31)
/* 80068D90 00065970  88 9F 22 22 */	lbz r4, 0x2222(r31)
/* 80068D94 00065974  50 04 17 7A */	rlwimi r4, r0, 2, 0x1d, 0x1d
/* 80068D98 00065978  98 9F 22 22 */	stb r4, 0x2222(r31)
/* 80068D9C 0006597C  88 9F 22 22 */	lbz r4, 0x2222(r31)
/* 80068DA0 00065980  50 04 0F BC */	rlwimi r4, r0, 1, 0x1e, 0x1e
/* 80068DA4 00065984  98 9F 22 22 */	stb r4, 0x2222(r31)
/* 80068DA8 00065988  88 9F 22 23 */	lbz r4, 0x2223(r31)
/* 80068DAC 0006598C  50 04 36 72 */	rlwimi r4, r0, 6, 0x19, 0x19
/* 80068DB0 00065990  98 9F 22 23 */	stb r4, 0x2223(r31)
/* 80068DB4 00065994  D0 1F 00 40 */	stfs f0, 0x40(r31)
/* 80068DB8 00065998  88 9F 22 24 */	lbz r4, 0x2224(r31)
/* 80068DBC 0006599C  50 04 07 FE */	rlwimi r4, r0, 0, 0x1f, 0x1f
/* 80068DC0 000659A0  98 9F 22 24 */	stb r4, 0x2224(r31)
/* 80068DC4 000659A4  90 1F 06 0C */	stw r0, 0x60c(r31)
/* 80068DC8 000659A8  88 9F 22 25 */	lbz r4, 0x2225(r31)
/* 80068DCC 000659AC  50 04 26 F6 */	rlwimi r4, r0, 4, 0x1b, 0x1b
/* 80068DD0 000659B0  98 9F 22 25 */	stb r4, 0x2225(r31)
/* 80068DD4 000659B4  88 9F 22 28 */	lbz r4, 0x2228(r31)
/* 80068DD8 000659B8  50 04 2E B4 */	rlwimi r4, r0, 5, 0x1a, 0x1a
/* 80068DDC 000659BC  98 9F 22 28 */	stb r4, 0x2228(r31)
/* 80068DE0 000659C0  88 9F 22 26 */	lbz r4, 0x2226(r31)
/* 80068DE4 000659C4  50 04 3E 30 */	rlwimi r4, r0, 7, 0x18, 0x18
/* 80068DE8 000659C8  98 9F 22 26 */	stb r4, 0x2226(r31)
/* 80068DEC 000659CC  88 9F 22 26 */	lbz r4, 0x2226(r31)
/* 80068DF0 000659D0  50 04 36 72 */	rlwimi r4, r0, 6, 0x19, 0x19
/* 80068DF4 000659D4  98 9F 22 26 */	stb r4, 0x2226(r31)
/* 80068DF8 000659D8  88 9F 22 27 */	lbz r4, 0x2227(r31)
/* 80068DFC 000659DC  50 04 3E 30 */	rlwimi r4, r0, 7, 0x18, 0x18
/* 80068E00 000659E0  98 9F 22 27 */	stb r4, 0x2227(r31)
/* 80068E04 000659E4  88 9F 22 24 */	lbz r4, 0x2224(r31)
/* 80068E08 000659E8  50 04 3E 30 */	rlwimi r4, r0, 7, 0x18, 0x18
/* 80068E0C 000659EC  98 9F 22 24 */	stb r4, 0x2224(r31)
/* 80068E10 000659F0  98 7F 21 35 */	stb r3, 0x2135(r31)
/* 80068E14 000659F4  90 1F 21 84 */	stw r0, 0x2184(r31)
/* 80068E18 000659F8  88 7F 22 29 */	lbz r3, 0x2229(r31)
/* 80068E1C 000659FC  50 03 26 F6 */	rlwimi r3, r0, 4, 0x1b, 0x1b
/* 80068E20 00065A00  98 7F 22 29 */	stb r3, 0x2229(r31)
/* 80068E24 00065A04  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80068E28 00065A08  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80068E2C 00065A0C  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80068E30 00065A10  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 80068E34 00065A14  38 21 00 28 */	addi r1, r1, 0x28
/* 80068E38 00065A18  7C 08 03 A6 */	mtlr r0
/* 80068E3C 00065A1C  4E 80 00 20 */	blr  
}

#pragma push
#pragma peephole on
// increments the spawn number, returns the spawn number value before incrementing
u32 func_80068E40()
{
	u32 spawnNum = lbl_804D64F8++;
    if (lbl_804D64F8 == 0)
        lbl_804D64F8 = 1;
	return spawnNum;
}
#pragma pop
//asm u32 func_80068E40()
//{
//	nofralloc
///* 80068E40 00065A20  80 6D AE 58 */	lwz r3, lbl_804D64F8(r13)
///* 80068E44 00065A24  38 03 00 01 */	addi r0, r3, 1
///* 80068E48 00065A28  90 0D AE 58 */	stw r0, lbl_804D64F8(r13)
///* 80068E4C 00065A2C  80 0D AE 58 */	lwz r0, lbl_804D64F8(r13)
///* 80068E50 00065A30  28 00 00 00 */	cmplwi r0, 0
///* 80068E54 00065A34  4C 82 00 20 */	bnelr
///* 80068E58 00065A38  38 00 00 01 */	li r0, 1
///* 80068E5C 00065A3C  90 0D AE 58 */	stw r0, lbl_804D64F8(r13)
///* 80068E60 00065A40  4E 80 00 20 */	blr
//}


asm void func_80068E64()
{
	nofralloc 
/* 80068E64 00065A44  3C 80 80 4A */	lis r4, stage_info@ha
/* 80068E68 00065A48  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 80068E6C 00065A4C  38 64 E6 C8 */	addi r3, r4, stage_info@l
/* 80068E70 00065A50  80 03 00 88 */	lwz r0, 0x88(r3)
/* 80068E74 00065A54  2C 00 00 1B */	cmpwi r0, 0x1b
/* 80068E78 00065A58  40 82 00 14 */	bne lbl_80068E8C
/* 80068E7C 00065A5C  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 80068E80 00065A60  C0 03 07 E4 */	lfs f0, 0x7e4(r3)
/* 80068E84 00065A64  D0 05 00 3C */	stfs f0, 0x3c(r5)
/* 80068E88 00065A68  4E 80 00 20 */	blr 
lbl_80068E8C:
/* 80068E8C 00065A6C  C0 02 88 70 */	lfs f0, lbl_804D8250(r2)
/* 80068E90 00065A70  D0 05 00 3C */	stfs f0, 0x3c(r5)
/* 80068E94 00065A74  4E 80 00 20 */	blr  
}


asm void func_80068E98()
{
	nofralloc 
/* 80068E98 00065A78  7C 08 02 A6 */	mflr r0
/* 80068E9C 00065A7C  38 80 00 08 */	li r4, 8
/* 80068EA0 00065A80  90 01 00 04 */	stw r0, 4(r1)
/* 80068EA4 00065A84  38 A0 00 00 */	li r5, 0
/* 80068EA8 00065A88  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 80068EAC 00065A8C  93 E1 00 44 */	stw r31, 0x44(r1)
/* 80068EB0 00065A90  93 C1 00 40 */	stw r30, 0x40(r1)
/* 80068EB4 00065A94  93 A1 00 3C */	stw r29, 0x3c(r1)
/* 80068EB8 00065A98  3B A3 00 00 */	addi r29, r3, 0
/* 80068EBC 00065A9C  38 60 00 04 */	li r3, 4
/* 80068EC0 00065AA0  93 81 00 38 */	stw r28, 0x38(r1)
/* 80068EC4 00065AA4  48 32 73 2D */	bl func_803901F0
/* 80068EC8 00065AA8  3C 80 80 08 */	lis r4, func_80080E18@ha
/* 80068ECC 00065AAC  3B E3 00 00 */	addi r31, r3, 0
/* 80068ED0 00065AB0  38 84 0E 18 */	addi r4, r4, func_80080E18@l
/* 80068ED4 00065AB4  38 A0 00 05 */	li r5, 5
/* 80068ED8 00065AB8  38 C0 00 00 */	li r6, 0
/* 80068EDC 00065ABC  48 32 77 C1 */	bl GObj_SetupGXLink
/* 80068EE0 00065AC0  3C 60 80 46 */	lis r3, lbl_80458FD0@ha
/* 80068EE4 00065AC4  38 63 8F D0 */	addi r3, r3, lbl_80458FD0@l
/* 80068EE8 00065AC8  48 31 1C E1 */	bl HSD_ObjAlloc
/* 80068EEC 00065ACC  3C 80 80 46 */	lis r4, lbl_80458FFC@ha
/* 80068EF0 00065AD0  38 04 8F FC */	addi r0, r4, lbl_80458FFC@l
/* 80068EF4 00065AD4  3B C3 00 00 */	addi r30, r3, 0
/* 80068EF8 00065AD8  7C 03 03 78 */	mr r3, r0
/* 80068EFC 00065ADC  48 31 1C CD */	bl HSD_ObjAlloc
/* 80068F00 00065AE0  3C 80 80 07 */	lis r4, func_8006DABC@ha
/* 80068F04 00065AE4  90 7E 02 D8 */	stw r3, 0x2d8(r30)
/* 80068F08 00065AE8  38 A4 DA BC */	addi r5, r4, func_8006DABC@l
/* 80068F0C 00065AEC  38 7F 00 00 */	addi r3, r31, 0
/* 80068F10 00065AF0  38 DE 00 00 */	addi r6, r30, 0
/* 80068F14 00065AF4  38 80 00 04 */	li r4, 4
/* 80068F18 00065AF8  48 32 7C 51 */	bl GObj_InitUserData
/* 80068F1C 00065AFC  80 7D 00 00 */	lwz r3, 0(r29)
/* 80068F20 00065B00  48 01 C8 0D */	bl func_8008572C
/* 80068F24 00065B04  38 7F 00 00 */	addi r3, r31, 0
/* 80068F28 00065B08  38 9D 00 00 */	addi r4, r29, 0
/* 80068F2C 00065B0C  4B FF F9 E9 */	bl func_80068914
/* 80068F30 00065B10  3C 60 80 3C */	lis r3, lbl_803C26FC@ha
/* 80068F34 00065B14  80 9E 00 04 */	lwz r4, 4(r30)
/* 80068F38 00065B18  38 03 26 FC */	addi r0, r3, lbl_803C26FC@l
/* 80068F3C 00065B1C  7C 60 22 14 */	add r3, r0, r4
/* 80068F40 00065B20  88 63 00 00 */	lbz r3, 0(r3)
/* 80068F44 00065B24  4B FF E4 39 */	bl func_8006737C
/* 80068F48 00065B28  80 7E 00 04 */	lwz r3, 4(r30)
/* 80068F4C 00065B2C  88 9E 06 19 */	lbz r4, 0x619(r30)
/* 80068F50 00065B30  48 01 C8 D1 */	bl func_80085820
/* 80068F54 00065B34  83 9F 00 2C */	lwz r28, 0x2c(r31)
/* 80068F58 00065B38  3C 60 80 3C */	lis r3, lbl_803C0EC0@ha
/* 80068F5C 00065B3C  38 63 0E C0 */	addi r3, r3, lbl_803C0EC0@l
/* 80068F60 00065B40  80 9C 00 04 */	lwz r4, 4(r28)
/* 80068F64 00065B44  88 1C 06 19 */	lbz r0, 0x619(r28)
/* 80068F68 00065B48  54 84 18 38 */	slwi r4, r4, 3
/* 80068F6C 00065B4C  7C 63 22 14 */	add r3, r3, r4
/* 80068F70 00065B50  1C 00 00 18 */	mulli r0, r0, 0x18
/* 80068F74 00065B54  80 63 00 00 */	lwz r3, 0(r3)
/* 80068F78 00065B58  7C 03 00 2E */	lwzx r0, r3, r0
/* 80068F7C 00065B5C  90 1C 01 08 */	stw r0, 0x108(r28)
/* 80068F80 00065B60  48 00 B1 C9 */	bl func_80074148
/* 80068F84 00065B64  80 7C 01 08 */	lwz r3, 0x108(r28)
/* 80068F88 00065B68  48 30 7E BD */	bl HSD_JObjLoadJoint
/* 80068F8C 00065B6C  7C 7C 1B 78 */	mr r28, r3
/* 80068F90 00065B70  48 00 B1 E1 */	bl func_80074170
/* 80068F94 00065B74  7F 83 E3 78 */	mr r3, r28
/* 80068F98 00065B78  48 00 A7 C1 */	bl func_80073758
/* 80068F9C 00065B7C  88 8D C1 A9 */	lbz r4, lbl_804D7849(r13)
/* 80068FA0 00065B80  38 7F 00 00 */	addi r3, r31, 0
/* 80068FA4 00065B84  38 BC 00 00 */	addi r5, r28, 0
/* 80068FA8 00065B88  48 32 7A C9 */	bl func_80390A70
/* 80068FAC 00065B8C  7F C3 F3 78 */	mr r3, r30
/* 80068FB0 00065B90  48 01 CB 61 */	bl func_80085B10
/* 80068FB4 00065B94  7F C3 F3 78 */	mr r3, r30
/* 80068FB8 00065B98  48 00 BE A1 */	bl func_80074E58
/* 80068FBC 00065B9C  7F E3 FB 78 */	mr r3, r31
/* 80068FC0 00065BA0  48 00 B4 21 */	bl func_800743E0
/* 80068FC4 00065BA4  7F E3 FB 78 */	mr r3, r31
/* 80068FC8 00065BA8  48 00 73 41 */	bl func_80070308
/* 80068FCC 00065BAC  7F E3 FB 78 */	mr r3, r31
/* 80068FD0 00065BB0  48 05 F8 7D */	bl func_800C884C
/* 80068FD4 00065BB4  3C 60 80 4A */	lis r3, stage_info@ha
/* 80068FD8 00065BB8  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 80068FDC 00065BBC  38 63 E6 C8 */	addi r3, r3, stage_info@l
/* 80068FE0 00065BC0  80 03 00 88 */	lwz r0, 0x88(r3)
/* 80068FE4 00065BC4  2C 00 00 1B */	cmpwi r0, 0x1b
/* 80068FE8 00065BC8  40 82 00 14 */	bne lbl_80068FFC
/* 80068FEC 00065BCC  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 80068FF0 00065BD0  C0 03 07 E4 */	lfs f0, 0x7e4(r3)
/* 80068FF4 00065BD4  D0 04 00 3C */	stfs f0, 0x3c(r4)
/* 80068FF8 00065BD8  48 00 00 0C */	b lbl_80069004
lbl_80068FFC:
/* 80068FFC 00065BDC  C0 02 88 70 */	lfs f0, lbl_804D8250(r2)
/* 80069000 00065BE0  D0 04 00 3C */	stfs f0, 0x3c(r4)
lbl_80069004:
/* 80069004 00065BE4  7F E3 FB 78 */	mr r3, r31
/* 80069008 00065BE8  48 00 B9 C5 */	bl func_800749CC
/* 8006900C 00065BEC  7F E3 FB 78 */	mr r3, r31
/* 80069010 00065BF0  48 00 77 6D */	bl func_8007077C
/* 80069014 00065BF4  7F C3 F3 78 */	mr r3, r30
/* 80069018 00065BF8  48 03 3F 6D */	bl func_8009CF84
/* 8006901C 00065BFC  7F E3 FB 78 */	mr r3, r31
/* 80069020 00065C00  48 00 6E 29 */	bl func_8006FE48
/* 80069024 00065C04  38 7E 00 00 */	addi r3, r30, 0
/* 80069028 00065C08  38 80 00 02 */	li r4, 2
/* 8006902C 00065C0C  48 00 BF E1 */	bl func_8007500C
/* 80069030 00065C10  80 9E 05 E8 */	lwz r4, 0x5e8(r30)
/* 80069034 00065C14  54 60 20 36 */	slwi r0, r3, 4
/* 80069038 00065C18  7F 84 00 2E */	lwzx r28, r4, r0
/* 8006903C 00065C1C  28 1C 00 00 */	cmplwi r28, 0
/* 80069040 00065C20  40 82 00 14 */	bne lbl_80069054
/* 80069044 00065C24  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 80069048 00065C28  38 80 03 D3 */	li r4, 0x3d3
/* 8006904C 00065C2C  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 80069050 00065C30  48 31 F1 D1 */	bl __assert
lbl_80069054:
/* 80069054 00065C34  80 9C 00 38 */	lwz r4, 0x38(r28)
/* 80069058 00065C38  7F 83 E3 78 */	mr r3, r28
/* 8006905C 00065C3C  80 1C 00 3C */	lwz r0, 0x3c(r28)
/* 80069060 00065C40  38 A1 00 20 */	addi r5, r1, 0x20
/* 80069064 00065C44  C0 02 88 88 */	lfs f0, lbl_804D8268(r2)
/* 80069068 00065C48  90 81 00 20 */	stw r4, 0x20(r1)
/* 8006906C 00065C4C  38 80 00 00 */	li r4, 0
/* 80069070 00065C50  90 01 00 24 */	stw r0, 0x24(r1)
/* 80069074 00065C54  80 1C 00 40 */	lwz r0, 0x40(r28)
/* 80069078 00065C58  90 01 00 28 */	stw r0, 0x28(r1)
/* 8006907C 00065C5C  C0 21 00 24 */	lfs f1, 0x24(r1)
/* 80069080 00065C60  EC 01 00 24 */	fdivs f0, f1, f0
/* 80069084 00065C64  D0 1E 1A 6C */	stfs f0, 0x1a6c(r30)
/* 80069088 00065C68  4B FA 21 45 */	bl func_8000B1CC
/* 8006908C 00065C6C  38 7E 00 00 */	addi r3, r30, 0
/* 80069090 00065C70  38 80 00 01 */	li r4, 1
/* 80069094 00065C74  48 00 BF 79 */	bl func_8007500C
/* 80069098 00065C78  80 9E 05 E8 */	lwz r4, 0x5e8(r30)
/* 8006909C 00065C7C  54 60 20 36 */	slwi r0, r3, 4
/* 800690A0 00065C80  38 A1 00 2C */	addi r5, r1, 0x2c
/* 800690A4 00065C84  7C 64 00 2E */	lwzx r3, r4, r0
/* 800690A8 00065C88  38 80 00 00 */	li r4, 0
/* 800690AC 00065C8C  4B FA 21 21 */	bl func_8000B1CC
/* 800690B0 00065C90  C0 21 00 2C */	lfs f1, 0x2c(r1)
/* 800690B4 00065C94  7F C3 F3 78 */	mr r3, r30
/* 800690B8 00065C98  C0 01 00 20 */	lfs f0, 0x20(r1)
/* 800690BC 00065C9C  EC 01 00 28 */	fsubs f0, f1, f0
/* 800690C0 00065CA0  D0 1E 1A 70 */	stfs f0, 0x1a70(r30)
/* 800690C4 00065CA4  C0 21 00 30 */	lfs f1, 0x30(r1)
/* 800690C8 00065CA8  C0 01 00 24 */	lfs f0, 0x24(r1)
/* 800690CC 00065CAC  EC 01 00 28 */	fsubs f0, f1, f0
/* 800690D0 00065CB0  D0 1E 1A 74 */	stfs f0, 0x1a74(r30)
/* 800690D4 00065CB4  C0 21 00 34 */	lfs f1, 0x34(r1)
/* 800690D8 00065CB8  C0 01 00 28 */	lfs f0, 0x28(r1)
/* 800690DC 00065CBC  EC 01 00 28 */	fsubs f0, f1, f0
/* 800690E0 00065CC0  D0 1E 1A 78 */	stfs f0, 0x1a78(r30)
/* 800690E4 00065CC4  48 03 64 95 */	bl func_8009F578
/* 800690E8 00065CC8  80 9E 00 04 */	lwz r4, 4(r30)
/* 800690EC 00065CCC  3C 60 80 3C */	lis r3, ft_OnLoad@ha
/* 800690F0 00065CD0  38 03 11 54 */	addi r0, r3, ft_OnLoad@l
/* 800690F4 00065CD4  54 83 10 3A */	slwi r3, r4, 2
/* 800690F8 00065CD8  7C 60 1A 14 */	add r3, r0, r3
/* 800690FC 00065CDC  81 83 00 00 */	lwz r12, 0(r3)
/* 80069100 00065CE0  28 0C 00 00 */	cmplwi r12, 0
/* 80069104 00065CE4  41 82 00 10 */	beq lbl_80069114
/* 80069108 00065CE8  7D 88 03 A6 */	mtlr r12
/* 8006910C 00065CEC  38 7F 00 00 */	addi r3, r31, 0
/* 80069110 00065CF0  4E 80 00 21 */	blrl 
lbl_80069114:
/* 80069114 00065CF4  83 9F 00 2C */	lwz r28, 0x2c(r31)
/* 80069118 00065CF8  88 1C 22 29 */	lbz r0, 0x2229(r28)
/* 8006911C 00065CFC  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 80069120 00065D00  40 82 00 74 */	bne lbl_80069194
/* 80069124 00065D04  38 7C 00 00 */	addi r3, r28, 0
/* 80069128 00065D08  38 80 00 23 */	li r4, 0x23
/* 8006912C 00065D0C  48 01 CD 25 */	bl func_80085E50
/* 80069130 00065D10  4B FB 57 C9 */	bl func_8001E8F8
/* 80069134 00065D14  D0 3C 02 EC */	stfs f1, 0x2ec(r28)
/* 80069138 00065D18  88 1C 22 28 */	lbz r0, 0x2228(r28)
/* 8006913C 00065D1C  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 80069140 00065D20  40 82 00 54 */	bne lbl_80069194
/* 80069144 00065D24  38 7C 00 00 */	addi r3, r28, 0
/* 80069148 00065D28  38 80 00 07 */	li r4, 7
/* 8006914C 00065D2C  48 01 CD 05 */	bl func_80085E50
/* 80069150 00065D30  4B FB 57 A9 */	bl func_8001E8F8
/* 80069154 00065D34  D0 3C 02 DC */	stfs f1, 0x2dc(r28)
/* 80069158 00065D38  38 7C 00 00 */	addi r3, r28, 0
/* 8006915C 00065D3C  38 80 00 08 */	li r4, 8
/* 80069160 00065D40  48 01 CC F1 */	bl func_80085E50
/* 80069164 00065D44  4B FB 57 95 */	bl func_8001E8F8
/* 80069168 00065D48  D0 3C 02 E0 */	stfs f1, 0x2e0(r28)
/* 8006916C 00065D4C  38 7C 00 00 */	addi r3, r28, 0
/* 80069170 00065D50  38 80 00 09 */	li r4, 9
/* 80069174 00065D54  48 01 CC DD */	bl func_80085E50
/* 80069178 00065D58  4B FB 57 81 */	bl func_8001E8F8
/* 8006917C 00065D5C  D0 3C 02 E4 */	stfs f1, 0x2e4(r28)
/* 80069180 00065D60  38 7C 00 00 */	addi r3, r28, 0
/* 80069184 00065D64  38 80 00 25 */	li r4, 0x25
/* 80069188 00065D68  48 01 CC C9 */	bl func_80085E50
/* 8006918C 00065D6C  4B FB 57 6D */	bl func_8001E8F8
/* 80069190 00065D70  D0 3C 02 E8 */	stfs f1, 0x2e8(r28)
lbl_80069194:
/* 80069194 00065D74  7F E3 FB 78 */	mr r3, r31
/* 80069198 00065D78  48 01 21 89 */	bl func_8007B320
/* 8006919C 00065D7C  4B FB FE 85 */	bl func_80029020
/* 800691A0 00065D80  90 7E 08 90 */	stw r3, 0x890(r30)
/* 800691A4 00065D84  38 7E 20 A4 */	addi r3, r30, 0x20a4
/* 800691A8 00065D88  80 9F 00 28 */	lwz r4, 0x28(r31)
/* 800691AC 00065D8C  4B FA 5B A9 */	bl func_8000ED54
/* 800691B0 00065D90  3C 60 80 07 */	lis r3, func_8006A1BC@ha
/* 800691B4 00065D94  38 83 A1 BC */	addi r4, r3, func_8006A1BC@l
/* 800691B8 00065D98  38 7F 00 00 */	addi r3, r31, 0
/* 800691BC 00065D9C  38 A0 00 00 */	li r5, 0
/* 800691C0 00065DA0  48 32 6B 95 */	bl func_8038FD54
/* 800691C4 00065DA4  3C 60 80 07 */	lis r3, func_8006A360@ha
/* 800691C8 00065DA8  38 83 A3 60 */	addi r4, r3, func_8006A360@l
/* 800691CC 00065DAC  38 7F 00 00 */	addi r3, r31, 0
/* 800691D0 00065DB0  38 A0 00 01 */	li r5, 1
/* 800691D4 00065DB4  48 32 6B 81 */	bl func_8038FD54
/* 800691D8 00065DB8  3C 60 80 07 */	lis r3, func_8006ABA0@ha
/* 800691DC 00065DBC  38 83 AB A0 */	addi r4, r3, func_8006ABA0@l
/* 800691E0 00065DC0  38 7F 00 00 */	addi r3, r31, 0
/* 800691E4 00065DC4  38 A0 00 02 */	li r5, 2
/* 800691E8 00065DC8  48 32 6B 6D */	bl func_8038FD54
/* 800691EC 00065DCC  3C 60 80 07 */	lis r3, func_8006AD10@ha
/* 800691F0 00065DD0  38 83 AD 10 */	addi r4, r3, func_8006AD10@l
/* 800691F4 00065DD4  38 7F 00 00 */	addi r3, r31, 0
/* 800691F8 00065DD8  38 A0 00 03 */	li r5, 3
/* 800691FC 00065DDC  48 32 6B 59 */	bl func_8038FD54
/* 80069200 00065DE0  3C 60 80 07 */	lis r3, func_8006B82C@ha
/* 80069204 00065DE4  38 83 B8 2C */	addi r4, r3, func_8006B82C@l
/* 80069208 00065DE8  38 7F 00 00 */	addi r3, r31, 0
/* 8006920C 00065DEC  38 A0 00 04 */	li r5, 4
/* 80069210 00065DF0  48 32 6B 45 */	bl func_8038FD54
/* 80069214 00065DF4  3C 60 80 07 */	lis r3, func_8006C27C@ha
/* 80069218 00065DF8  38 83 C2 7C */	addi r4, r3, func_8006C27C@l
/* 8006921C 00065DFC  38 7F 00 00 */	addi r3, r31, 0
/* 80069220 00065E00  38 A0 00 06 */	li r5, 6
/* 80069224 00065E04  48 32 6B 31 */	bl func_8038FD54
/* 80069228 00065E08  3C 60 80 07 */	lis r3, func_8006C5F4@ha
/* 8006922C 00065E0C  38 83 C5 F4 */	addi r4, r3, func_8006C5F4@l
/* 80069230 00065E10  38 7F 00 00 */	addi r3, r31, 0
/* 80069234 00065E14  38 A0 00 07 */	li r5, 7
/* 80069238 00065E18  48 32 6B 1D */	bl func_8038FD54
/* 8006923C 00065E1C  3C 60 80 07 */	lis r3, func_8006C624@ha
/* 80069240 00065E20  38 83 C6 24 */	addi r4, r3, func_8006C624@l
/* 80069244 00065E24  38 7F 00 00 */	addi r3, r31, 0
/* 80069248 00065E28  38 A0 00 08 */	li r5, 8
/* 8006924C 00065E2C  48 32 6B 09 */	bl func_8038FD54
/* 80069250 00065E30  3C 60 80 07 */	lis r3, func_8006C80C@ha
/* 80069254 00065E34  38 83 C8 0C */	addi r4, r3, func_8006C80C@l
/* 80069258 00065E38  38 7F 00 00 */	addi r3, r31, 0
/* 8006925C 00065E3C  38 A0 00 09 */	li r5, 9
/* 80069260 00065E40  48 32 6A F5 */	bl func_8038FD54
/* 80069264 00065E44  3C 60 80 07 */	lis r3, func_8006CA5C@ha
/* 80069268 00065E48  38 83 CA 5C */	addi r4, r3, func_8006CA5C@l
/* 8006926C 00065E4C  38 7F 00 00 */	addi r3, r31, 0
/* 80069270 00065E50  38 A0 00 0C */	li r5, 0xc
/* 80069274 00065E54  48 32 6A E1 */	bl func_8038FD54
/* 80069278 00065E58  3C 60 80 07 */	lis r3, func_8006CB94@ha
/* 8006927C 00065E5C  38 83 CB 94 */	addi r4, r3, func_8006CB94@l
/* 80069280 00065E60  38 7F 00 00 */	addi r3, r31, 0
/* 80069284 00065E64  38 A0 00 0D */	li r5, 0xd
/* 80069288 00065E68  48 32 6A CD */	bl func_8038FD54
/* 8006928C 00065E6C  3C 60 80 07 */	lis r3, func_8006D1EC@ha
/* 80069290 00065E70  38 83 D1 EC */	addi r4, r3, func_8006D1EC@l
/* 80069294 00065E74  38 7F 00 00 */	addi r3, r31, 0
/* 80069298 00065E78  38 A0 00 0E */	li r5, 0xe
/* 8006929C 00065E7C  48 32 6A B9 */	bl func_8038FD54
/* 800692A0 00065E80  3C 60 80 07 */	lis r3, func_8006D9AC@ha
/* 800692A4 00065E84  38 83 D9 AC */	addi r4, r3, func_8006D9AC@l
/* 800692A8 00065E88  38 7F 00 00 */	addi r3, r31, 0
/* 800692AC 00065E8C  38 A0 00 10 */	li r5, 0x10
/* 800692B0 00065E90  48 32 6A A5 */	bl func_8038FD54
/* 800692B4 00065E94  3C 60 80 07 */	lis r3, func_8006D9EC@ha
/* 800692B8 00065E98  38 83 D9 EC */	addi r4, r3, func_8006D9EC@l
/* 800692BC 00065E9C  38 7F 00 00 */	addi r3, r31, 0
/* 800692C0 00065EA0  38 A0 00 12 */	li r5, 0x12
/* 800692C4 00065EA4  48 32 6A 91 */	bl func_8038FD54
/* 800692C8 00065EA8  3C 60 80 07 */	lis r3, func_8006DA4C@ha
/* 800692CC 00065EAC  38 83 DA 4C */	addi r4, r3, func_8006DA4C@l
/* 800692D0 00065EB0  38 7F 00 00 */	addi r3, r31, 0
/* 800692D4 00065EB4  38 A0 00 16 */	li r5, 0x16
/* 800692D8 00065EB8  48 32 6A 7D */	bl func_8038FD54
/* 800692DC 00065EBC  7F E3 FB 78 */	mr r3, r31
/* 800692E0 00065EC0  4B FF F0 75 */	bl func_80068354
/* 800692E4 00065EC4  80 1E 00 04 */	lwz r0, 4(r30)
/* 800692E8 00065EC8  2C 00 00 1B */	cmpwi r0, 0x1b
/* 800692EC 00065ECC  40 82 00 10 */	bne lbl_800692FC
/* 800692F0 00065ED0  7F E3 FB 78 */	mr r3, r31
/* 800692F4 00065ED4  48 0E 6B 1D */	bl func_8014FE10
/* 800692F8 00065ED8  48 00 00 88 */	b lbl_80069380
lbl_800692FC:
/* 800692FC 00065EDC  2C 00 00 1C */	cmpwi r0, 0x1c
/* 80069300 00065EE0  40 82 00 10 */	bne lbl_80069310
/* 80069304 00065EE4  7F E3 FB 78 */	mr r3, r31
/* 80069308 00065EE8  48 0E CC C5 */	bl func_80155FCC
/* 8006930C 00065EEC  48 00 00 74 */	b lbl_80069380
lbl_80069310:
/* 80069310 00065EF0  88 1D 00 06 */	lbz r0, 6(r29)
/* 80069314 00065EF4  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 80069318 00065EF8  41 82 00 10 */	beq lbl_80069328
/* 8006931C 00065EFC  7F E3 FB 78 */	mr r3, r31
/* 80069320 00065F00  48 05 69 E5 */	bl func_800BFD04
/* 80069324 00065F04  48 00 00 5C */	b lbl_80069380
lbl_80069328:
/* 80069328 00065F08  88 7E 00 0C */	lbz r3, 0xc(r30)
/* 8006932C 00065F0C  4B FC C4 9D */	bl Player_GetFlagsBit3
/* 80069330 00065F10  2C 03 00 00 */	cmpwi r3, 0
/* 80069334 00065F14  41 82 00 10 */	beq lbl_80069344
/* 80069338 00065F18  7F E3 FB 78 */	mr r3, r31
/* 8006933C 00065F1C  48 05 CE 75 */	bl func_800C61B0
/* 80069340 00065F20  48 00 00 40 */	b lbl_80069380
lbl_80069344:
/* 80069344 00065F24  88 1E 22 29 */	lbz r0, 0x2229(r30)
/* 80069348 00065F28  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 8006934C 00065F2C  40 82 00 10 */	bne lbl_8006935C
/* 80069350 00065F30  7F E3 FB 78 */	mr r3, r31
/* 80069354 00065F34  48 01 45 D9 */	bl func_8007D92C
/* 80069358 00065F38  48 00 00 28 */	b lbl_80069380
lbl_8006935C:
/* 8006935C 00065F3C  3C 60 80 3C */	lis r3, lbl_803C0588@ha
/* 80069360 00065F40  4C C6 31 82 */	crclr 6
/* 80069364 00065F44  38 63 05 88 */	addi r3, r3, lbl_803C0588@l
/* 80069368 00065F48  48 2D C3 41 */	bl OSReport
/* 8006936C 00065F4C  3C 60 80 3C */	lis r3, lbl_803C057C@ha
/* 80069370 00065F50  38 63 05 7C */	addi r3, r3, lbl_803C057C@l
/* 80069374 00065F54  38 80 04 29 */	li r4, 0x429
/* 80069378 00065F58  38 AD 83 70 */	addi r5, r13, lbl_804D3A10
/* 8006937C 00065F5C  48 31 EE A5 */	bl __assert
lbl_80069380:
/* 80069380 00065F60  7F E3 FB 78 */	mr r3, r31
/* 80069384 00065F64  48 01 D4 65 */	bl func_800867E8
/* 80069388 00065F68  7F E3 FB 78 */	mr r3, r31
/* 8006938C 00065F6C  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 80069390 00065F70  83 E1 00 44 */	lwz r31, 0x44(r1)
/* 80069394 00065F74  83 C1 00 40 */	lwz r30, 0x40(r1)
/* 80069398 00065F78  83 A1 00 3C */	lwz r29, 0x3c(r1)
/* 8006939C 00065F7C  83 81 00 38 */	lwz r28, 0x38(r1)
/* 800693A0 00065F80  38 21 00 48 */	addi r1, r1, 0x48
/* 800693A4 00065F84  7C 08 03 A6 */	mtlr r0
/* 800693A8 00065F88  4E 80 00 20 */	blr  
}


asm void func_800693AC(void*, s32, s32, s32, f32, f32, f32)
{
	nofralloc 
/* 800693AC 00065F8C  7C 08 02 A6 */	mflr r0
/* 800693B0 00065F90  90 01 00 04 */	stw r0, 4(r1)
/* 800693B4 00065F94  94 21 FF 60 */	stwu r1, -0xa0(r1)
/* 800693B8 00065F98  DB E1 00 98 */	stfd f31, 0x98(r1)
/* 800693BC 00065F9C  FF E0 18 90 */	fmr f31, f3
/* 800693C0 00065FA0  DB C1 00 90 */	stfd f30, 0x90(r1)
/* 800693C4 00065FA4  FF C0 10 90 */	fmr f30, f2
/* 800693C8 00065FA8  DB A1 00 88 */	stfd f29, 0x88(r1)
/* 800693CC 00065FAC  FF A0 08 90 */	fmr f29, f1
/* 800693D0 00065FB0  BE C1 00 60 */	stmw r22, 0x60(r1)
/* 800693D4 00065FB4  7C 98 23 78 */	mr r24, r4
/* 800693D8 00065FB8  7C 7E 1B 78 */	mr r30, r3
/* 800693DC 00065FBC  3B E5 00 00 */	addi r31, r5, 0
/* 800693E0 00065FC0  3A E6 00 00 */	addi r23, r6, 0
/* 800693E4 00065FC4  83 63 00 28 */	lwz r27, 0x28(r3)
/* 800693E8 00065FC8  83 43 00 2C */	lwz r26, 0x2c(r3)
/* 800693EC 00065FCC  28 1B 00 00 */	cmplwi r27, 0
/* 800693F0 00065FD0  93 1A 00 10 */	stw r24, 0x10(r26)
/* 800693F4 00065FD4  C0 1A 00 2C */	lfs f0, 0x2c(r26)
/* 800693F8 00065FD8  D0 1A 00 30 */	stfs f0, 0x30(r26)
/* 800693FC 00065FDC  40 82 00 14 */	bne lbl_80069410
/* 80069400 00065FE0  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 80069404 00065FE4  38 80 03 94 */	li r4, 0x394
/* 80069408 00065FE8  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 8006940C 00065FEC  48 31 EE 15 */	bl __assert
lbl_80069410:
/* 80069410 00065FF0  34 1A 00 B0 */	addic. r0, r26, 0xb0
/* 80069414 00065FF4  40 82 00 18 */	bne lbl_8006942C
/* 80069418 00065FF8  3C 60 80 3C */	lis r3, lbl_803C0550@ha
/* 8006941C 00065FFC  38 A3 05 50 */	addi r5, r3, lbl_803C0550@l
/* 80069420 00066000  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 80069424 00066004  38 80 03 95 */	li r4, 0x395
/* 80069428 00066008  48 31 ED F9 */	bl __assert
lbl_8006942C:
/* 8006942C 0006600C  80 7A 00 B0 */	lwz r3, 0xb0(r26)
/* 80069430 00066010  80 1A 00 B4 */	lwz r0, 0xb4(r26)
/* 80069434 00066014  90 7B 00 38 */	stw r3, 0x38(r27)
/* 80069438 00066018  90 1B 00 3C */	stw r0, 0x3c(r27)
/* 8006943C 0006601C  80 1A 00 B8 */	lwz r0, 0xb8(r26)
/* 80069440 00066020  90 1B 00 40 */	stw r0, 0x40(r27)
/* 80069444 00066024  80 1B 00 14 */	lwz r0, 0x14(r27)
/* 80069448 00066028  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8006944C 0006602C  40 82 00 4C */	bne lbl_80069498
/* 80069450 00066030  28 1B 00 00 */	cmplwi r27, 0
/* 80069454 00066034  41 82 00 44 */	beq lbl_80069498
/* 80069458 00066038  40 82 00 14 */	bne lbl_8006946C
/* 8006945C 0006603C  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 80069460 00066040  38 80 02 34 */	li r4, 0x234
/* 80069464 00066044  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 80069468 00066048  48 31 ED B9 */	bl __assert
lbl_8006946C:
/* 8006946C 0006604C  80 9B 00 14 */	lwz r4, 0x14(r27)
/* 80069470 00066050  38 60 00 00 */	li r3, 0
/* 80069474 00066054  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80069478 00066058  40 82 00 10 */	bne lbl_80069488
/* 8006947C 0006605C  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80069480 00066060  41 82 00 08 */	beq lbl_80069488
/* 80069484 00066064  38 60 00 01 */	li r3, 1
lbl_80069488:
/* 80069488 00066068  2C 03 00 00 */	cmpwi r3, 0
/* 8006948C 0006606C  40 82 00 0C */	bne lbl_80069498
/* 80069490 00066070  7F 63 DB 78 */	mr r3, r27
/* 80069494 00066074  48 30 9E 55 */	bl HSD_JObjSetMtxDirtySub
lbl_80069498:
/* 80069498 00066078  38 7E 00 00 */	addi r3, r30, 0
/* 8006949C 0006607C  38 9A 06 0C */	addi r4, r26, 0x60c
/* 800694A0 00066080  4B FF E1 85 */	bl func_80067624
/* 800694A4 00066084  57 E0 07 39 */	rlwinm. r0, r31, 0, 0x1c, 0x1c
/* 800694A8 00066088  40 82 00 2C */	bne lbl_800694D4
/* 800694AC 0006608C  88 1A 22 19 */	lbz r0, 0x2219(r26)
/* 800694B0 00066090  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 800694B4 00066094  41 82 00 0C */	beq lbl_800694C0
/* 800694B8 00066098  7F C3 F3 78 */	mr r3, r30
/* 800694BC 0006609C  48 01 1B 3D */	bl func_8007AFF8
lbl_800694C0:
/* 800694C0 000660A0  88 1A 22 19 */	lbz r0, 0x2219(r26)
/* 800694C4 000660A4  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 800694C8 000660A8  41 82 00 0C */	beq lbl_800694D4
/* 800694CC 000660AC  7F C3 F3 78 */	mr r3, r30
/* 800694D0 000660B0  48 01 2C 45 */	bl func_8007C114
lbl_800694D4:
/* 800694D4 000660B4  57 E0 05 EF */	rlwinm. r0, r31, 0, 0x17, 0x17
/* 800694D8 000660B8  40 82 00 0C */	bne lbl_800694E4
/* 800694DC 000660BC  38 00 00 00 */	li r0, 0
/* 800694E0 000660C0  90 1A 11 98 */	stw r0, 0x1198(r26)
lbl_800694E4:
/* 800694E4 000660C4  57 E0 07 7B */	rlwinm. r0, r31, 0, 0x1d, 0x1d
/* 800694E8 000660C8  40 82 00 34 */	bne lbl_8006951C
/* 800694EC 000660CC  80 1A 19 88 */	lwz r0, 0x1988(r26)
/* 800694F0 000660D0  2C 00 00 00 */	cmpwi r0, 0
/* 800694F4 000660D4  41 82 00 10 */	beq lbl_80069504
/* 800694F8 000660D8  38 7E 00 00 */	addi r3, r30, 0
/* 800694FC 000660DC  38 80 00 00 */	li r4, 0
/* 80069500 000660E0  48 01 21 2D */	bl func_8007B62C
lbl_80069504:
/* 80069504 000660E4  88 1A 22 1A */	lbz r0, 0x221a(r26)
/* 80069508 000660E8  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 8006950C 000660EC  41 82 00 10 */	beq lbl_8006951C
/* 80069510 000660F0  38 7E 00 00 */	addi r3, r30, 0
/* 80069514 000660F4  38 80 00 00 */	li r4, 0
/* 80069518 000660F8  48 01 1B A9 */	bl func_8007B0C0
lbl_8006951C:
/* 8006951C 000660FC  88 1A 22 1A */	lbz r0, 0x221a(r26)
/* 80069520 00066100  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 80069524 00066104  41 82 00 0C */	beq lbl_80069530
/* 80069528 00066108  7F C3 F3 78 */	mr r3, r30
/* 8006952C 0006610C  48 01 1F B5 */	bl func_8007B4E0
lbl_80069530:
/* 80069530 00066110  57 E0 06 F7 */	rlwinm. r0, r31, 0, 0x1b, 0x1b
/* 80069534 00066114  40 82 00 18 */	bne lbl_8006954C
/* 80069538 00066118  88 1A 22 1D */	lbz r0, 0x221d(r26)
/* 8006953C 0006611C  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 80069540 00066120  41 82 00 0C */	beq lbl_8006954C
/* 80069544 00066124  7F C3 F3 78 */	mr r3, r30
/* 80069548 00066128  48 00 B5 45 */	bl func_80074A8C
lbl_8006954C:
/* 8006954C 0006612C  57 E0 06 31 */	rlwinm. r0, r31, 0, 0x18, 0x18
/* 80069550 00066130  40 82 00 18 */	bne lbl_80069568
/* 80069554 00066134  88 1A 22 1E */	lbz r0, 0x221e(r26)
/* 80069558 00066138  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8006955C 0006613C  41 82 00 0C */	beq lbl_80069568
/* 80069560 00066140  7F C3 F3 78 */	mr r3, r30
/* 80069564 00066144  48 00 70 F1 */	bl func_80070654
lbl_80069568:
/* 80069568 00066148  57 E0 05 6B */	rlwinm. r0, r31, 0, 0x15, 0x15
/* 8006956C 0006614C  40 82 00 44 */	bne lbl_800695B0
/* 80069570 00066150  88 1A 22 21 */	lbz r0, 0x2221(r26)
/* 80069574 00066154  38 60 00 00 */	li r3, 0
/* 80069578 00066158  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 8006957C 0006615C  98 1A 22 21 */	stb r0, 0x2221(r26)
/* 80069580 00066160  7F C3 F3 78 */	mr r3, r30
/* 80069584 00066164  48 01 54 11 */	bl func_8007E994
/* 80069588 00066168  2C 03 FF FF */	cmpwi r3, -1
/* 8006958C 0006616C  41 82 00 24 */	beq lbl_800695B0
/* 80069590 00066170  7F C3 F3 78 */	mr r3, r30
/* 80069594 00066174  48 01 54 01 */	bl func_8007E994
/* 80069598 00066178  2C 03 00 06 */	cmpwi r3, 6
/* 8006959C 0006617C  41 82 00 14 */	beq lbl_800695B0
/* 800695A0 00066180  C0 22 88 74 */	lfs f1, lbl_804D8254(r2)
/* 800695A4 00066184  38 7E 00 00 */	addi r3, r30, 0
/* 800695A8 00066188  38 80 00 06 */	li r4, 6
/* 800695AC 0006618C  48 01 52 91 */	bl func_8007E83C
lbl_800695B0:
/* 800695B0 00066190  7F C3 F3 78 */	mr r3, r30
/* 800695B4 00066194  48 00 79 75 */	bl func_80070F28
/* 800695B8 00066198  7F C3 F3 78 */	mr r3, r30
/* 800695BC 0006619C  48 00 78 B9 */	bl func_80070E74
/* 800695C0 000661A0  38 7A 00 00 */	addi r3, r26, 0
/* 800695C4 000661A4  38 80 00 07 */	li r4, 7
/* 800695C8 000661A8  48 01 57 0D */	bl func_8007ECD4
/* 800695CC 000661AC  38 7A 00 00 */	addi r3, r26, 0
/* 800695D0 000661B0  38 80 00 08 */	li r4, 8
/* 800695D4 000661B4  48 01 57 01 */	bl func_8007ECD4
/* 800695D8 000661B8  38 7A 00 00 */	addi r3, r26, 0
/* 800695DC 000661BC  38 80 00 24 */	li r4, 0x24
/* 800695E0 000661C0  48 01 56 F5 */	bl func_8007ECD4
/* 800695E4 000661C4  57 E0 05 29 */	rlwinm. r0, r31, 0, 0x14, 0x14
/* 800695E8 000661C8  40 82 00 1C */	bne lbl_80069604
/* 800695EC 000661CC  38 7A 00 00 */	addi r3, r26, 0
/* 800695F0 000661D0  38 80 00 01 */	li r4, 1
/* 800695F4 000661D4  48 01 56 E1 */	bl func_8007ECD4
/* 800695F8 000661D8  38 7A 00 00 */	addi r3, r26, 0
/* 800695FC 000661DC  38 80 00 19 */	li r4, 0x19
/* 80069600 000661E0  48 01 56 D5 */	bl func_8007ECD4
lbl_80069604:
/* 80069604 000661E4  57 E0 03 DF */	rlwinm. r0, r31, 0, 0xf, 0xf
/* 80069608 000661E8  40 82 00 38 */	bne lbl_80069640
/* 8006960C 000661EC  88 1A 22 21 */	lbz r0, 0x2221(r26)
/* 80069610 000661F0  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 80069614 000661F4  41 82 00 2C */	beq lbl_80069640
/* 80069618 000661F8  7F C3 F3 78 */	mr r3, r30
/* 8006961C 000661FC  48 01 20 D1 */	bl func_8007B6EC
/* 80069620 00066200  80 8D AE B4 */	lwz r4, lbl_804D6554(r13)
/* 80069624 00066204  7F C3 F3 78 */	mr r3, r30
/* 80069628 00066208  80 84 01 34 */	lwz r4, 0x134(r4)
/* 8006962C 0006620C  48 01 21 35 */	bl func_8007B760
/* 80069630 00066210  88 1A 22 21 */	lbz r0, 0x2221(r26)
/* 80069634 00066214  38 60 00 00 */	li r3, 0
/* 80069638 00066218  50 60 36 72 */	rlwimi r0, r3, 6, 0x19, 0x19
/* 8006963C 0006621C  98 1A 22 21 */	stb r0, 0x2221(r26)
lbl_80069640:
/* 80069640 00066220  38 7A 00 00 */	addi r3, r26, 0
/* 80069644 00066224  38 80 00 00 */	li r4, 0
/* 80069648 00066228  48 01 4C AD */	bl func_8007E2F4
/* 8006964C 0006622C  80 1A 18 F4 */	lwz r0, 0x18f4(r26)
/* 80069650 00066230  2C 00 00 00 */	cmpwi r0, 0
/* 80069654 00066234  41 82 00 18 */	beq lbl_8006966C
/* 80069658 00066238  38 60 00 00 */	li r3, 0
/* 8006965C 0006623C  90 7A 18 F4 */	stw r3, 0x18f4(r26)
/* 80069660 00066240  88 1A 22 20 */	lbz r0, 0x2220(r26)
/* 80069664 00066244  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 80069668 00066248  98 1A 22 20 */	stb r0, 0x2220(r26)
lbl_8006966C:
/* 8006966C 0006624C  57 E0 03 19 */	rlwinm. r0, r31, 0, 0xc, 0xc
/* 80069670 00066250  40 82 00 14 */	bne lbl_80069684
/* 80069674 00066254  88 1A 22 22 */	lbz r0, 0x2222(r26)
/* 80069678 00066258  38 60 00 00 */	li r3, 0
/* 8006967C 0006625C  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 80069680 00066260  98 1A 22 22 */	stb r0, 0x2222(r26)
lbl_80069684:
/* 80069684 00066264  57 E0 02 11 */	rlwinm. r0, r31, 0, 8, 8
/* 80069688 00066268  40 82 00 14 */	bne lbl_8006969C
/* 8006968C 0006626C  88 1A 22 23 */	lbz r0, 0x2223(r26)
/* 80069690 00066270  38 60 00 00 */	li r3, 0
/* 80069694 00066274  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 80069698 00066278  98 1A 22 23 */	stb r0, 0x2223(r26)
lbl_8006969C:
/* 8006969C 0006627C  57 E0 01 09 */	rlwinm. r0, r31, 0, 4, 4
/* 800696A0 00066280  40 82 00 14 */	bne lbl_800696B4
/* 800696A4 00066284  88 1A 22 27 */	lbz r0, 0x2227(r26)
/* 800696A8 00066288  38 60 00 00 */	li r3, 0
/* 800696AC 0006628C  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 800696B0 00066290  98 1A 22 27 */	stb r0, 0x2227(r26)
lbl_800696B4:
/* 800696B4 00066294  57 E0 00 C7 */	rlwinm. r0, r31, 0, 3, 3
/* 800696B8 00066298  40 82 00 28 */	bne lbl_800696E0
/* 800696BC 0006629C  88 7A 22 1C */	lbz r3, 0x221c(r26)
/* 800696C0 000662A0  54 60 FF FF */	rlwinm. r0, r3, 0x1f, 0x1f, 0x1f
/* 800696C4 000662A4  41 82 00 1C */	beq lbl_800696E0
/* 800696C8 000662A8  38 00 00 00 */	li r0, 0
/* 800696CC 000662AC  50 03 0F BC */	rlwimi r3, r0, 1, 0x1e, 0x1e
/* 800696D0 000662B0  98 7A 22 1C */	stb r3, 0x221c(r26)
/* 800696D4 000662B4  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 800696D8 000662B8  80 03 04 CC */	lwz r0, 0x4cc(r3)
/* 800696DC 000662BC  B0 1A 20 98 */	sth r0, 0x2098(r26)
lbl_800696E0:
/* 800696E0 000662C0  88 1A 22 1F */	lbz r0, 0x221f(r26)
/* 800696E4 000662C4  3B A0 00 00 */	li r29, 0
/* 800696E8 000662C8  53 A0 26 F6 */	rlwimi r0, r29, 4, 0x1b, 0x1b
/* 800696EC 000662CC  98 1A 22 1F */	stb r0, 0x221f(r26)
/* 800696F0 000662D0  38 7A 06 F0 */	addi r3, r26, 0x6f0
/* 800696F4 000662D4  88 1A 22 19 */	lbz r0, 0x2219(r26)
/* 800696F8 000662D8  53 A0 36 72 */	rlwimi r0, r29, 6, 0x19, 0x19
/* 800696FC 000662DC  98 1A 22 19 */	stb r0, 0x2219(r26)
/* 80069700 000662E0  88 1A 22 19 */	lbz r0, 0x2219(r26)
/* 80069704 000662E4  53 A0 2E B4 */	rlwimi r0, r29, 5, 0x1a, 0x1a
/* 80069708 000662E8  98 1A 22 19 */	stb r0, 0x2219(r26)
/* 8006970C 000662EC  C0 02 88 70 */	lfs f0, lbl_804D8250(r2)
/* 80069710 000662F0  D0 1A 18 2C */	stfs f0, 0x182c(r26)
/* 80069714 000662F4  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 80069718 000662F8  D0 1A 18 50 */	stfs f0, 0x1850(r26)
/* 8006971C 000662FC  D0 1A 18 A8 */	stfs f0, 0x18a8(r26)
/* 80069720 00066300  D0 1A 18 B4 */	stfs f0, 0x18b4(r26)
/* 80069724 00066304  D0 1A 18 A0 */	stfs f0, 0x18a0(r26)
/* 80069728 00066308  88 1A 22 1A */	lbz r0, 0x221a(r26)
/* 8006972C 0006630C  53 A0 07 FE */	rlwimi r0, r29, 0, 0x1f, 0x1f
/* 80069730 00066310  98 1A 22 1A */	stb r0, 0x221a(r26)
/* 80069734 00066314  88 1A 22 1B */	lbz r0, 0x221b(r26)
/* 80069738 00066318  53 A0 3E 30 */	rlwimi r0, r29, 7, 0x18, 0x18
/* 8006973C 0006631C  98 1A 22 1B */	stb r0, 0x221b(r26)
/* 80069740 00066320  88 1A 22 1C */	lbz r0, 0x221c(r26)
/* 80069744 00066324  53 A0 26 F6 */	rlwimi r0, r29, 4, 0x1b, 0x1b
/* 80069748 00066328  98 1A 22 1C */	stb r0, 0x221c(r26)
/* 8006974C 0006632C  D0 1A 19 B4 */	stfs f0, 0x19b4(r26)
/* 80069750 00066330  D0 1A 19 B8 */	stfs f0, 0x19b8(r26)
/* 80069754 00066334  88 1A 22 1D */	lbz r0, 0x221d(r26)
/* 80069758 00066338  53 A0 17 7A */	rlwimi r0, r29, 2, 0x1d, 0x1d
/* 8006975C 0006633C  98 1A 22 1D */	stb r0, 0x221d(r26)
/* 80069760 00066340  88 1A 22 18 */	lbz r0, 0x2218(r26)
/* 80069764 00066344  53 A0 26 F6 */	rlwimi r0, r29, 4, 0x1b, 0x1b
/* 80069768 00066348  98 1A 22 18 */	stb r0, 0x2218(r26)
/* 8006976C 0006634C  88 1A 22 18 */	lbz r0, 0x2218(r26)
/* 80069770 00066350  53 A0 0F BC */	rlwimi r0, r29, 1, 0x1e, 0x1e
/* 80069774 00066354  98 1A 22 18 */	stb r0, 0x2218(r26)
/* 80069778 00066358  88 1A 22 1C */	lbz r0, 0x221c(r26)
/* 8006977C 0006635C  53 A0 1F 38 */	rlwimi r0, r29, 3, 0x1c, 0x1c
/* 80069780 00066360  98 1A 22 1C */	stb r0, 0x221c(r26)
/* 80069784 00066364  B3 BA 1A 6A */	sth r29, 0x1a6a(r26)
/* 80069788 00066368  88 1A 22 1D */	lbz r0, 0x221d(r26)
/* 8006978C 0006636C  53 A0 07 FE */	rlwimi r0, r29, 0, 0x1f, 0x1f
/* 80069790 00066370  98 1A 22 1D */	stb r0, 0x221d(r26)
/* 80069794 00066374  88 1A 22 1E */	lbz r0, 0x221e(r26)
/* 80069798 00066378  53 A0 3E 30 */	rlwimi r0, r29, 7, 0x18, 0x18
/* 8006979C 0006637C  98 1A 22 1E */	stb r0, 0x221e(r26)
/* 800697A0 00066380  88 1A 22 1E */	lbz r0, 0x221e(r26)
/* 800697A4 00066384  53 A0 36 72 */	rlwimi r0, r29, 6, 0x19, 0x19
/* 800697A8 00066388  98 1A 22 1E */	stb r0, 0x221e(r26)
/* 800697AC 0006638C  88 1A 22 1E */	lbz r0, 0x221e(r26)
/* 800697B0 00066390  53 A0 2E B4 */	rlwimi r0, r29, 5, 0x1a, 0x1a
/* 800697B4 00066394  98 1A 22 1E */	stb r0, 0x221e(r26)
/* 800697B8 00066398  88 1A 22 1F */	lbz r0, 0x221f(r26)
/* 800697BC 0006639C  53 A0 36 72 */	rlwimi r0, r29, 6, 0x19, 0x19
/* 800697C0 000663A0  98 1A 22 1F */	stb r0, 0x221f(r26)
/* 800697C4 000663A4  88 1A 22 1E */	lbz r0, 0x221e(r26)
/* 800697C8 000663A8  53 A0 17 7A */	rlwimi r0, r29, 2, 0x1d, 0x1d
/* 800697CC 000663AC  98 1A 22 1E */	stb r0, 0x221e(r26)
/* 800697D0 000663B0  88 1A 22 1E */	lbz r0, 0x221e(r26)
/* 800697D4 000663B4  53 A0 0F BC */	rlwimi r0, r29, 1, 0x1e, 0x1e
/* 800697D8 000663B8  98 1A 22 1E */	stb r0, 0x221e(r26)
/* 800697DC 000663BC  88 1A 22 20 */	lbz r0, 0x2220(r26)
/* 800697E0 000663C0  53 A0 26 F6 */	rlwimi r0, r29, 4, 0x1b, 0x1b
/* 800697E4 000663C4  98 1A 22 20 */	stb r0, 0x2220(r26)
/* 800697E8 000663C8  88 1A 22 20 */	lbz r0, 0x2220(r26)
/* 800697EC 000663CC  53 A0 07 FE */	rlwimi r0, r29, 0, 0x1f, 0x1f
/* 800697F0 000663D0  98 1A 22 20 */	stb r0, 0x2220(r26)
/* 800697F4 000663D4  B3 BA 20 9C */	sth r29, 0x209c(r26)
/* 800697F8 000663D8  88 1A 22 23 */	lbz r0, 0x2223(r26)
/* 800697FC 000663DC  53 A0 3E 30 */	rlwimi r0, r29, 7, 0x18, 0x18
/* 80069800 000663E0  98 1A 22 23 */	stb r0, 0x2223(r26)
/* 80069804 000663E4  88 1A 22 22 */	lbz r0, 0x2222(r26)
/* 80069808 000663E8  53 A0 26 F6 */	rlwimi r0, r29, 4, 0x1b, 0x1b
/* 8006980C 000663EC  98 1A 22 22 */	stb r0, 0x2222(r26)
/* 80069810 000663F0  88 1A 22 24 */	lbz r0, 0x2224(r26)
/* 80069814 000663F4  53 A0 17 7A */	rlwimi r0, r29, 2, 0x1d, 0x1d
/* 80069818 000663F8  98 1A 22 24 */	stb r0, 0x2224(r26)
/* 8006981C 000663FC  88 1A 22 25 */	lbz r0, 0x2225(r26)
/* 80069820 00066400  53 A0 36 72 */	rlwimi r0, r29, 6, 0x19, 0x19
/* 80069824 00066404  98 1A 22 25 */	stb r0, 0x2225(r26)
/* 80069828 00066408  88 1A 22 25 */	lbz r0, 0x2225(r26)
/* 8006982C 0006640C  53 A0 1F 38 */	rlwimi r0, r29, 3, 0x1c, 0x1c
/* 80069830 00066410  98 1A 22 25 */	stb r0, 0x2225(r26)
/* 80069834 00066414  4B FE 33 C1 */	bl func_8004CBF4
/* 80069838 00066418  7F C3 F3 78 */	mr r3, r30
/* 8006983C 0006641C  48 07 56 6D */	bl func_800DEEA8
/* 80069840 00066420  C0 02 88 78 */	lfs f0, lbl_804D8258(r2)
/* 80069844 00066424  57 E0 03 5B */	rlwinm. r0, r31, 0, 0xd, 0xd
/* 80069848 00066428  D0 1A 21 38 */	stfs f0, 0x2138(r26)
/* 8006984C 0006642C  88 1A 22 24 */	lbz r0, 0x2224(r26)
/* 80069850 00066430  53 A0 1F 38 */	rlwimi r0, r29, 3, 0x1c, 0x1c
/* 80069854 00066434  98 1A 22 24 */	stb r0, 0x2224(r26)
/* 80069858 00066438  40 82 00 18 */	bne lbl_80069870
/* 8006985C 0006643C  88 1A 22 1E */	lbz r0, 0x221e(r26)
/* 80069860 00066440  38 60 00 01 */	li r3, 1
/* 80069864 00066444  50 60 26 F6 */	rlwimi r0, r3, 4, 0x1b, 0x1b
/* 80069868 00066448  98 1A 22 1E */	stb r0, 0x221e(r26)
/* 8006986C 0006644C  48 00 00 18 */	b lbl_80069884
lbl_80069870:
/* 80069870 00066450  88 1A 22 1E */	lbz r0, 0x221e(r26)
/* 80069874 00066454  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 80069878 00066458  40 82 00 0C */	bne lbl_80069884
/* 8006987C 0006645C  7F C3 F3 78 */	mr r3, r30
/* 80069880 00066460  48 01 5C F9 */	bl func_8007F578
lbl_80069884:
/* 80069884 00066464  57 E0 02 53 */	rlwinm. r0, r31, 0, 9, 9
/* 80069888 00066468  40 82 00 14 */	bne lbl_8006989C
/* 8006988C 0006646C  88 1A 22 1E */	lbz r0, 0x221e(r26)
/* 80069890 00066470  38 60 00 01 */	li r3, 1
/* 80069894 00066474  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 80069898 00066478  98 1A 22 1E */	stb r0, 0x221e(r26)
lbl_8006989C:
/* 8006989C 0006647C  57 E0 01 4B */	rlwinm. r0, r31, 0, 5, 5
/* 800698A0 00066480  40 82 00 14 */	bne lbl_800698B4
/* 800698A4 00066484  88 1A 22 25 */	lbz r0, 0x2225(r26)
/* 800698A8 00066488  38 60 00 01 */	li r3, 1
/* 800698AC 0006648C  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 800698B0 00066490  98 1A 22 25 */	stb r0, 0x2225(r26)
lbl_800698B4:
/* 800698B4 00066494  57 E0 07 FF */	clrlwi. r0, r31, 0x1f
/* 800698B8 00066498  40 82 00 14 */	bne lbl_800698CC
/* 800698BC 0006649C  88 1A 22 1A */	lbz r0, 0x221a(r26)
/* 800698C0 000664A0  38 60 00 00 */	li r3, 0
/* 800698C4 000664A4  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 800698C8 000664A8  98 1A 22 1A */	stb r0, 0x221a(r26)
lbl_800698CC:
/* 800698CC 000664AC  57 E0 04 E7 */	rlwinm. r0, r31, 0, 0x13, 0x13
/* 800698D0 000664B0  40 82 00 0C */	bne lbl_800698DC
/* 800698D4 000664B4  7F 43 D3 78 */	mr r3, r26
/* 800698D8 000664B8  48 05 68 5D */	bl func_800C0134
lbl_800698DC:
/* 800698DC 000664BC  57 E0 07 BD */	rlwinm. r0, r31, 0, 0x1e, 0x1e
/* 800698E0 000664C0  40 82 00 18 */	bne lbl_800698F8
/* 800698E4 000664C4  88 1A 22 19 */	lbz r0, 0x2219(r26)
/* 800698E8 000664C8  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 800698EC 000664CC  41 82 00 0C */	beq lbl_800698F8
/* 800698F0 000664D0  7F C3 F3 78 */	mr r3, r30
/* 800698F4 000664D4  48 01 42 31 */	bl func_8007DB24
lbl_800698F8:
/* 800698F8 000664D8  57 E0 04 A5 */	rlwinm. r0, r31, 0, 0x12, 0x12
/* 800698FC 000664DC  40 82 00 1C */	bne lbl_80069918
/* 80069900 000664E0  80 7A 20 A0 */	lwz r3, 0x20a0(r26)
/* 80069904 000664E4  28 03 00 00 */	cmplwi r3, 0
/* 80069908 000664E8  41 82 00 10 */	beq lbl_80069918
/* 8006990C 000664EC  48 30 7C 85 */	bl HSD_JObjRemoveAll
/* 80069910 000664F0  38 00 00 00 */	li r0, 0
/* 80069914 000664F4  90 1A 20 A0 */	stw r0, 0x20a0(r26)
lbl_80069918:
/* 80069918 000664F8  80 1A 00 E0 */	lwz r0, 0xe0(r26)
/* 8006991C 000664FC  2C 00 00 00 */	cmpwi r0, 0
/* 80069920 00066500  40 82 00 CC */	bne lbl_800699EC
/* 80069924 00066504  80 1A 00 04 */	lwz r0, 4(r26)
/* 80069928 00066508  2C 00 00 09 */	cmpwi r0, 9
/* 8006992C 0006650C  40 82 00 0C */	bne lbl_80069938
/* 80069930 00066510  38 00 00 01 */	li r0, 1
/* 80069934 00066514  90 1A 22 2C */	stw r0, 0x222c(r26)
lbl_80069938:
/* 80069938 00066518  88 1A 22 21 */	lbz r0, 0x2221(r26)
/* 8006993C 0006651C  3B 20 00 00 */	li r25, 0
/* 80069940 00066520  53 20 17 7A */	rlwimi r0, r25, 2, 0x1d, 0x1d
/* 80069944 00066524  98 1A 22 21 */	stb r0, 0x2221(r26)
/* 80069948 00066528  38 80 00 01 */	li r4, 1
/* 8006994C 0006652C  38 00 FF FF */	li r0, -1
/* 80069950 00066530  88 7A 22 21 */	lbz r3, 0x2221(r26)
/* 80069954 00066534  50 83 07 FE */	rlwimi r3, r4, 0, 0x1f, 0x1f
/* 80069958 00066538  98 7A 22 21 */	stb r3, 0x2221(r26)
/* 8006995C 0006653C  88 7A 22 21 */	lbz r3, 0x2221(r26)
/* 80069960 00066540  50 83 0F BC */	rlwimi r3, r4, 1, 0x1e, 0x1e
/* 80069964 00066544  98 7A 22 21 */	stb r3, 0x2221(r26)
/* 80069968 00066548  88 7A 22 24 */	lbz r3, 0x2224(r26)
/* 8006996C 0006654C  53 23 36 72 */	rlwimi r3, r25, 6, 0x19, 0x19
/* 80069970 00066550  98 7A 22 24 */	stb r3, 0x2224(r26)
/* 80069974 00066554  88 7A 22 27 */	lbz r3, 0x2227(r26)
/* 80069978 00066558  53 23 36 72 */	rlwimi r3, r25, 6, 0x19, 0x19
/* 8006997C 0006655C  98 7A 22 27 */	stb r3, 0x2227(r26)
/* 80069980 00066560  90 1A 21 3C */	stw r0, 0x213c(r26)
/* 80069984 00066564  88 1A 22 27 */	lbz r0, 0x2227(r26)
/* 80069988 00066568  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 8006998C 0006656C  41 82 00 20 */	beq lbl_800699AC
/* 80069990 00066570  88 9A 22 1F */	lbz r4, 0x221f(r26)
/* 80069994 00066574  88 7A 00 0C */	lbz r3, 0xc(r26)
/* 80069998 00066578  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 8006999C 0006657C  4B FD 64 81 */	bl func_8003FE1C
/* 800699A0 00066580  88 1A 22 27 */	lbz r0, 0x2227(r26)
/* 800699A4 00066584  53 20 1F 38 */	rlwimi r0, r25, 3, 0x1c, 0x1c
/* 800699A8 00066588  98 1A 22 27 */	stb r0, 0x2227(r26)
lbl_800699AC:
/* 800699AC 0006658C  88 1A 22 27 */	lbz r0, 0x2227(r26)
/* 800699B0 00066590  3B 20 00 00 */	li r25, 0
/* 800699B4 00066594  53 20 17 7A */	rlwimi r0, r25, 2, 0x1d, 0x1d
/* 800699B8 00066598  98 1A 22 27 */	stb r0, 0x2227(r26)
/* 800699BC 0006659C  88 9A 22 1F */	lbz r4, 0x221f(r26)
/* 800699C0 000665A0  88 7A 00 0C */	lbz r3, 0xc(r26)
/* 800699C4 000665A4  C0 3A 21 40 */	lfs f1, 0x2140(r26)
/* 800699C8 000665A8  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 800699CC 000665AC  4B FD 69 65 */	bl func_80040330
/* 800699D0 000665B0  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 800699D4 000665B4  38 00 00 06 */	li r0, 6
/* 800699D8 000665B8  D0 1A 21 40 */	stfs f0, 0x2140(r26)
/* 800699DC 000665BC  88 7A 22 28 */	lbz r3, 0x2228(r26)
/* 800699E0 000665C0  53 23 0F BC */	rlwimi r3, r25, 1, 0x1e, 0x1e
/* 800699E4 000665C4  98 7A 22 28 */	stb r3, 0x2228(r26)
/* 800699E8 000665C8  90 1A 21 80 */	stw r0, 0x2180(r26)
lbl_800699EC:
/* 800699EC 000665CC  2C 18 00 0E */	cmpwi r24, 0xe
/* 800699F0 000665D0  41 82 00 24 */	beq lbl_80069A14
/* 800699F4 000665D4  2C 18 00 0F */	cmpwi r24, 0xf
/* 800699F8 000665D8  41 82 00 1C */	beq lbl_80069A14
/* 800699FC 000665DC  2C 18 00 10 */	cmpwi r24, 0x10
/* 80069A00 000665E0  41 82 00 14 */	beq lbl_80069A14
/* 80069A04 000665E4  2C 18 00 11 */	cmpwi r24, 0x11
/* 80069A08 000665E8  41 82 00 0C */	beq lbl_80069A14
/* 80069A0C 000665EC  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 80069A10 000665F0  D0 1A 19 6C */	stfs f0, 0x196c(r26)
lbl_80069A14:
/* 80069A14 000665F4  57 E0 05 AD */	rlwinm. r0, r31, 0, 0x16, 0x16
/* 80069A18 000665F8  40 82 00 1C */	bne lbl_80069A34
/* 80069A1C 000665FC  7F 43 D3 78 */	mr r3, r26
/* 80069A20 00066600  48 01 EE 65 */	bl func_80088884
/* 80069A24 00066604  7F 43 D3 78 */	mr r3, r26
/* 80069A28 00066608  48 01 EE B9 */	bl func_800888E0
/* 80069A2C 0006660C  7F 43 D3 78 */	mr r3, r26
/* 80069A30 00066610  48 01 ED 9D */	bl func_800887CC
lbl_80069A34:
/* 80069A34 00066614  57 E0 03 9D */	rlwinm. r0, r31, 0, 0xe, 0xe
/* 80069A38 00066618  40 82 00 0C */	bne lbl_80069A44
/* 80069A3C 0006661C  38 00 FF FF */	li r0, -1
/* 80069A40 00066620  98 1A 21 00 */	stb r0, 0x2100(r26)
lbl_80069A44:
/* 80069A44 00066624  57 E0 04 21 */	rlwinm. r0, r31, 0, 0x10, 0x10
/* 80069A48 00066628  40 82 00 0C */	bne lbl_80069A54
/* 80069A4C 0006662C  38 00 00 00 */	li r0, 0
/* 80069A50 00066630  B0 1A 20 9A */	sth r0, 0x209a(r26)
lbl_80069A54:
/* 80069A54 00066634  88 7A 22 22 */	lbz r3, 0x2222(r26)
/* 80069A58 00066638  38 80 00 00 */	li r4, 0
/* 80069A5C 0006663C  50 83 07 FE */	rlwimi r3, r4, 0, 0x1f, 0x1f
/* 80069A60 00066640  57 E0 02 D7 */	rlwinm. r0, r31, 0, 0xb, 0xb
/* 80069A64 00066644  98 7A 22 22 */	stb r3, 0x2222(r26)
/* 80069A68 00066648  41 82 00 10 */	beq lbl_80069A78
/* 80069A6C 0006664C  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 80069A70 00066650  D0 1A 01 00 */	stfs f0, 0x100(r26)
/* 80069A74 00066654  48 00 00 0C */	b lbl_80069A80
lbl_80069A78:
/* 80069A78 00066658  C0 02 88 78 */	lfs f0, lbl_804D8258(r2)
/* 80069A7C 0006665C  D0 1A 01 00 */	stfs f0, 0x100(r26)
lbl_80069A80:
/* 80069A80 00066660  57 E0 01 CF */	rlwinm. r0, r31, 0, 7, 7
/* 80069A84 00066664  40 82 00 14 */	bne lbl_80069A98
/* 80069A88 00066668  A0 1A 22 1C */	lhz r0, 0x221c(r26)
/* 80069A8C 0006666C  38 60 00 00 */	li r3, 0
/* 80069A90 00066670  50 60 35 F2 */	rlwimi r0, r3, 6, 0x17, 0x19
/* 80069A94 00066674  B0 1A 22 1C */	sth r0, 0x221c(r26)
lbl_80069A98:
/* 80069A98 00066678  C0 22 88 74 */	lfs f1, lbl_804D8254(r2)
/* 80069A9C 0006667C  38 7A 00 00 */	addi r3, r26, 0
/* 80069AA0 00066680  38 80 00 00 */	li r4, 0
/* 80069AA4 00066684  D0 3A 06 BC */	stfs f1, 0x6bc(r26)
/* 80069AA8 00066688  48 00 BE 85 */	bl func_8007592C
/* 80069AAC 0006668C  C8 22 88 90 */	lfd f1, lbl_804D8270(r2)
/* 80069AB0 00066690  7F 43 D3 78 */	mr r3, r26
/* 80069AB4 00066694  C0 1A 00 2C */	lfs f0, 0x2c(r26)
/* 80069AB8 00066698  38 80 00 00 */	li r4, 0
/* 80069ABC 0006669C  FC 21 00 32 */	fmul f1, f1, f0
/* 80069AC0 000666A0  FC 20 08 18 */	frsp f1, f1
/* 80069AC4 000666A4  48 00 C0 2D */	bl func_80075AF0
/* 80069AC8 000666A8  C0 22 88 74 */	lfs f1, lbl_804D8254(r2)
/* 80069ACC 000666AC  38 7A 00 00 */	addi r3, r26, 0
/* 80069AD0 000666B0  38 80 00 00 */	li r4, 0
/* 80069AD4 000666B4  48 00 C1 E1 */	bl func_80075CB4
/* 80069AD8 000666B8  80 1A 00 18 */	lwz r0, 0x18(r26)
/* 80069ADC 000666BC  7C 18 00 00 */	cmpw r24, r0
/* 80069AE0 000666C0  41 80 00 18 */	blt lbl_80069AF8
/* 80069AE4 000666C4  7C 00 C0 50 */	subf r0, r0, r24
/* 80069AE8 000666C8  80 7A 00 20 */	lwz r3, 0x20(r26)
/* 80069AEC 000666CC  54 00 28 34 */	slwi r0, r0, 5
/* 80069AF0 000666D0  7F 23 02 14 */	add r25, r3, r0
/* 80069AF4 000666D4  48 00 00 10 */	b lbl_80069B04
lbl_80069AF8:
/* 80069AF8 000666D8  80 7A 00 1C */	lwz r3, 0x1c(r26)
/* 80069AFC 000666DC  57 00 28 34 */	slwi r0, r24, 5
/* 80069B00 000666E0  7F 23 02 14 */	add r25, r3, r0
lbl_80069B04:
/* 80069B04 000666E4  80 1A 00 E0 */	lwz r0, 0xe0(r26)
/* 80069B08 000666E8  2C 00 00 00 */	cmpwi r0, 0
/* 80069B0C 000666EC  40 82 00 44 */	bne lbl_80069B50
/* 80069B10 000666F0  57 E0 06 73 */	rlwinm. r0, r31, 0, 0x19, 0x19
/* 80069B14 000666F4  40 82 00 3C */	bne lbl_80069B50
/* 80069B18 000666F8  88 19 00 09 */	lbz r0, 9(r25)
/* 80069B1C 000666FC  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 80069B20 00066700  41 82 00 30 */	beq lbl_80069B50
/* 80069B24 00066704  80 1A 18 C8 */	lwz r0, 0x18c8(r26)
/* 80069B28 00066708  2C 00 FF FF */	cmpwi r0, -1
/* 80069B2C 0006670C  40 82 00 24 */	bne lbl_80069B50
/* 80069B30 00066710  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 80069B34 00066714  80 03 08 14 */	lwz r0, 0x814(r3)
/* 80069B38 00066718  2C 00 00 00 */	cmpwi r0, 0
/* 80069B3C 0006671C  40 81 00 0C */	ble lbl_80069B48
/* 80069B40 00066720  90 1A 18 C8 */	stw r0, 0x18c8(r26)
/* 80069B44 00066724  48 00 00 0C */	b lbl_80069B50
lbl_80069B48:
/* 80069B48 00066728  38 00 00 01 */	li r0, 1
/* 80069B4C 0006672C  90 1A 18 C8 */	stw r0, 0x18c8(r26)
lbl_80069B50:
/* 80069B50 00066730  80 1A 20 70 */	lwz r0, 0x2070(r26)
/* 80069B54 00066734  7F 43 D3 78 */	mr r3, r26
/* 80069B58 00066738  90 01 00 50 */	stw r0, 0x50(r1)
/* 80069B5C 0006673C  88 99 00 08 */	lbz r4, 8(r25)
/* 80069B60 00066740  48 01 F5 71 */	bl func_800890D0
/* 80069B64 00066744  7F 43 D3 78 */	mr r3, r26
/* 80069B68 00066748  80 99 00 04 */	lwz r4, 4(r25)
/* 80069B6C 0006674C  48 01 FA 75 */	bl func_800895E0
/* 80069B70 00066750  88 79 00 09 */	lbz r3, 9(r25)
/* 80069B74 00066754  88 1A 22 25 */	lbz r0, 0x2225(r26)
/* 80069B78 00066758  50 60 EE F6 */	rlwimi r0, r3, 0x1d, 0x1b, 0x1b
/* 80069B7C 0006675C  98 1A 22 25 */	stb r0, 0x2225(r26)
/* 80069B80 00066760  88 1A 22 26 */	lbz r0, 0x2226(r26)
/* 80069B84 00066764  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 80069B88 00066768  41 82 00 3C */	beq lbl_80069BC4
/* 80069B8C 0006676C  88 1A 20 71 */	lbz r0, 0x2071(r26)
/* 80069B90 00066770  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 80069B94 00066774  41 82 00 14 */	beq lbl_80069BA8
/* 80069B98 00066778  38 7A 00 00 */	addi r3, r26, 0
/* 80069B9C 0006677C  38 80 00 7E */	li r4, 0x7e
/* 80069BA0 00066780  38 A0 00 00 */	li r5, 0
/* 80069BA4 00066784  48 05 EF 89 */	bl func_800C8B2C
lbl_80069BA8:
/* 80069BA8 00066788  88 1A 20 71 */	lbz r0, 0x2071(r26)
/* 80069BAC 0006678C  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 80069BB0 00066790  41 82 00 14 */	beq lbl_80069BC4
/* 80069BB4 00066794  38 7A 00 00 */	addi r3, r26, 0
/* 80069BB8 00066798  38 80 00 7F */	li r4, 0x7f
/* 80069BBC 0006679C  38 A0 00 00 */	li r5, 0
/* 80069BC0 000667A0  48 05 EF 6D */	bl func_800C8B2C
lbl_80069BC4:
/* 80069BC4 000667A4  81 9A 21 EC */	lwz r12, 0x21ec(r26)
/* 80069BC8 000667A8  28 0C 00 00 */	cmplwi r12, 0
/* 80069BCC 000667AC  41 82 00 18 */	beq lbl_80069BE4
/* 80069BD0 000667B0  7D 88 03 A6 */	mtlr r12
/* 80069BD4 000667B4  38 7E 00 00 */	addi r3, r30, 0
/* 80069BD8 000667B8  4E 80 00 21 */	blrl 
/* 80069BDC 000667BC  38 00 00 00 */	li r0, 0
/* 80069BE0 000667C0  90 1A 21 EC */	stw r0, 0x21ec(r26)
lbl_80069BE4:
/* 80069BE4 000667C4  57 E0 01 8D */	rlwinm. r0, r31, 0, 6, 6
/* 80069BE8 000667C8  40 82 00 10 */	bne lbl_80069BF8
/* 80069BEC 000667CC  7F C3 F3 78 */	mr r3, r30
/* 80069BF0 000667D0  80 81 00 50 */	lwz r4, 0x50(r1)
/* 80069BF4 000667D4  4B FC E0 6D */	bl func_80037C60
lbl_80069BF8:
/* 80069BF8 000667D8  80 19 00 00 */	lwz r0, 0(r25)
/* 80069BFC 000667DC  90 1A 00 14 */	stw r0, 0x14(r26)
/* 80069C00 000667E0  D3 DA 08 9C */	stfs f30, 0x89c(r26)
/* 80069C04 000667E4  D3 DA 08 A0 */	stfs f30, 0x8a0(r26)
/* 80069C08 000667E8  C0 1A 08 9C */	lfs f0, 0x89c(r26)
/* 80069C0C 000667EC  EC 1D 00 28 */	fsubs f0, f29, f0
/* 80069C10 000667F0  D0 1A 08 94 */	stfs f0, 0x894(r26)
/* 80069C14 000667F4  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 80069C18 000667F8  D0 1A 08 98 */	stfs f0, 0x898(r26)
/* 80069C1C 000667FC  88 7A 05 94 */	lbz r3, 0x594(r26)
/* 80069C20 00066800  54 60 CF FF */	rlwinm. r0, r3, 0x19, 0x1f, 0x1f
/* 80069C24 00066804  40 82 00 0C */	bne lbl_80069C30
/* 80069C28 00066808  54 60 F7 FF */	rlwinm. r0, r3, 0x1e, 0x1f, 0x1f
/* 80069C2C 0006680C  41 82 00 0C */	beq lbl_80069C38
lbl_80069C30:
/* 80069C30 00066810  3B 00 00 01 */	li r24, 1
/* 80069C34 00066814  48 00 00 08 */	b lbl_80069C3C
lbl_80069C38:
/* 80069C38 00066818  3B 00 00 00 */	li r24, 0
lbl_80069C3C:
/* 80069C3C 0006681C  80 1A 00 14 */	lwz r0, 0x14(r26)
/* 80069C40 00066820  2C 00 FF FF */	cmpwi r0, -1
/* 80069C44 00066824  41 82 04 9C */	beq lbl_8006A0E0
/* 80069C48 00066828  A3 9A 05 96 */	lhz r28, 0x596(r26)
/* 80069C4C 0006682C  57 E0 02 95 */	rlwinm. r0, r31, 0, 0xa, 0xa
/* 80069C50 00066830  57 9C D7 7E */	rlwinm r28, r28, 0x1a, 0x1d, 0x1f
/* 80069C54 00066834  41 82 00 28 */	beq lbl_80069C7C
/* 80069C58 00066838  88 1A 22 23 */	lbz r0, 0x2223(r26)
/* 80069C5C 0006683C  38 60 00 01 */	li r3, 1
/* 80069C60 00066840  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 80069C64 00066844  98 1A 22 23 */	stb r0, 0x2223(r26)
/* 80069C68 00066848  38 00 00 14 */	li r0, 0x14
/* 80069C6C 0006684C  98 1A 01 04 */	stb r0, 0x104(r26)
/* 80069C70 00066850  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 80069C74 00066854  FF C0 00 90 */	fmr f30, f0
/* 80069C78 00066858  D0 1A 08 9C */	stfs f0, 0x89c(r26)
lbl_80069C7C:
/* 80069C7C 0006685C  28 17 00 00 */	cmplwi r23, 0
/* 80069C80 00066860  41 82 00 28 */	beq lbl_80069CA8
/* 80069C84 00066864  80 1A 00 14 */	lwz r0, 0x14(r26)
/* 80069C88 00066868  80 77 00 2C */	lwz r3, 0x2c(r23)
/* 80069C8C 0006686C  1C 80 00 18 */	mulli r4, r0, 0x18
/* 80069C90 00066870  80 A3 00 24 */	lwz r5, 0x24(r3)
/* 80069C94 00066874  80 63 00 28 */	lwz r3, 0x28(r3)
/* 80069C98 00066878  54 00 08 3C */	slwi r0, r0, 1
/* 80069C9C 0006687C  7E C5 22 14 */	add r22, r5, r4
/* 80069CA0 00066880  7F A3 02 14 */	add r29, r3, r0
/* 80069CA4 00066884  48 00 00 20 */	b lbl_80069CC4
lbl_80069CA8:
/* 80069CA8 00066888  80 1A 00 14 */	lwz r0, 0x14(r26)
/* 80069CAC 0006688C  80 BA 00 24 */	lwz r5, 0x24(r26)
/* 80069CB0 00066890  1C 80 00 18 */	mulli r4, r0, 0x18
/* 80069CB4 00066894  80 7A 00 28 */	lwz r3, 0x28(r26)
/* 80069CB8 00066898  54 00 08 3C */	slwi r0, r0, 1
/* 80069CBC 0006689C  7E C5 22 14 */	add r22, r5, r4
/* 80069CC0 000668A0  7F A3 02 14 */	add r29, r3, r0
lbl_80069CC4:
/* 80069CC4 000668A4  80 16 00 10 */	lwz r0, 0x10(r22)
/* 80069CC8 000668A8  38 7A 00 00 */	addi r3, r26, 0
/* 80069CCC 000668AC  38 9D 00 00 */	addi r4, r29, 0
/* 80069CD0 000668B0  90 1A 05 94 */	stw r0, 0x594(r26)
/* 80069CD4 000668B4  48 03 4A E1 */	bl func_8009E7B4
/* 80069CD8 000668B8  57 E0 00 85 */	rlwinm. r0, r31, 0, 2, 2
/* 80069CDC 000668BC  40 82 03 FC */	bne lbl_8006A0D8
/* 80069CE0 000668C0  28 17 00 00 */	cmplwi r23, 0
/* 80069CE4 000668C4  41 82 00 24 */	beq lbl_80069D08
/* 80069CE8 000668C8  80 97 00 2C */	lwz r4, 0x2c(r23)
/* 80069CEC 000668CC  7F 43 D3 78 */	mr r3, r26
/* 80069CF0 000668D0  80 BA 00 14 */	lwz r5, 0x14(r26)
/* 80069CF4 000668D4  48 01 BF E5 */	bl func_80085CD8
/* 80069CF8 000668D8  38 7A 00 00 */	addi r3, r26, 0
/* 80069CFC 000668DC  38 97 00 00 */	addi r4, r23, 0
/* 80069D00 000668E0  48 01 1B CD */	bl func_8007B8CC
/* 80069D04 000668E4  48 00 00 14 */	b lbl_80069D18
lbl_80069D08:
/* 80069D08 000668E8  80 BA 00 14 */	lwz r5, 0x14(r26)
/* 80069D0C 000668EC  38 7A 00 00 */	addi r3, r26, 0
/* 80069D10 000668F0  38 9A 00 00 */	addi r4, r26, 0
/* 80069D14 000668F4  48 01 BF C5 */	bl func_80085CD8
lbl_80069D18:
/* 80069D18 000668F8  80 76 00 0C */	lwz r3, 0xc(r22)
/* 80069D1C 000668FC  38 00 00 00 */	li r0, 0
/* 80069D20 00066900  90 7A 03 EC */	stw r3, 0x3ec(r26)
/* 80069D24 00066904  90 1A 03 F0 */	stw r0, 0x3f0(r26)
/* 80069D28 00066908  C0 62 88 74 */	lfs f3, lbl_804D8254(r2)
/* 80069D2C 0006690C  FC 1D 18 00 */	fcmpu cr0, f29, f3
/* 80069D30 00066910  41 82 00 F0 */	beq lbl_80069E20
/* 80069D34 00066914  80 1A 05 90 */	lwz r0, 0x590(r26)
/* 80069D38 00066918  28 00 00 00 */	cmplwi r0, 0
/* 80069D3C 0006691C  41 82 00 50 */	beq lbl_80069D8C
/* 80069D40 00066920  C0 02 88 78 */	lfs f0, lbl_804D8258(r2)
/* 80069D44 00066924  FC 00 F8 00 */	fcmpu cr0, f0, f31
/* 80069D48 00066928  40 82 00 08 */	bne lbl_80069D50
/* 80069D4C 0006692C  48 00 00 30 */	b lbl_80069D7C
lbl_80069D50:
/* 80069D50 00066930  FC 1F 18 00 */	fcmpu cr0, f31, f3
/* 80069D54 00066934  41 82 00 0C */	beq lbl_80069D60
/* 80069D58 00066938  FC 60 F8 90 */	fmr f3, f31
/* 80069D5C 0006693C  48 00 00 20 */	b lbl_80069D7C
lbl_80069D60:
/* 80069D60 00066940  88 7D 00 00 */	lbz r3, 0(r29)
/* 80069D64 00066944  3C 00 43 30 */	lis r0, 0x4330
/* 80069D68 00066948  C8 22 88 98 */	lfd f1, lbl_804D8278(r2)
/* 80069D6C 0006694C  90 61 00 5C */	stw r3, 0x5c(r1)
/* 80069D70 00066950  90 01 00 58 */	stw r0, 0x58(r1)
/* 80069D74 00066954  C8 01 00 58 */	lfd f0, 0x58(r1)
/* 80069D78 00066958  EC 60 08 28 */	fsubs f3, f0, f1
lbl_80069D7C:
/* 80069D7C 0006695C  FC 40 F0 90 */	fmr f2, f30
/* 80069D80 00066960  7F C3 F3 78 */	mr r3, r30
/* 80069D84 00066964  EC 3D F0 28 */	fsubs f1, f29, f30
/* 80069D88 00066968  48 00 4E 61 */	bl func_8006EBE8
lbl_80069D8C:
/* 80069D8C 0006696C  7F C3 F3 78 */	mr r3, r30
/* 80069D90 00066970  48 00 4C 25 */	bl func_8006E9B4
/* 80069D94 00066974  88 1A 05 94 */	lbz r0, 0x594(r26)
/* 80069D98 00066978  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 80069D9C 0006697C  41 82 00 38 */	beq lbl_80069DD4
/* 80069DA0 00066980  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 80069DA4 00066984  D0 1A 06 B8 */	stfs f0, 0x6b8(r26)
/* 80069DA8 00066988  D0 1A 06 B4 */	stfs f0, 0x6b4(r26)
/* 80069DAC 0006698C  D0 1A 06 B0 */	stfs f0, 0x6b0(r26)
/* 80069DB0 00066990  D0 1A 06 AC */	stfs f0, 0x6ac(r26)
/* 80069DB4 00066994  D0 1A 06 A8 */	stfs f0, 0x6a8(r26)
/* 80069DB8 00066998  D0 1A 06 A4 */	stfs f0, 0x6a4(r26)
/* 80069DBC 0006699C  80 7A 06 8C */	lwz r3, 0x68c(r26)
/* 80069DC0 000669A0  80 1A 06 90 */	lwz r0, 0x690(r26)
/* 80069DC4 000669A4  90 7A 06 98 */	stw r3, 0x698(r26)
/* 80069DC8 000669A8  90 1A 06 9C */	stw r0, 0x69c(r26)
/* 80069DCC 000669AC  80 1A 06 94 */	lwz r0, 0x694(r26)
/* 80069DD0 000669B0  90 1A 06 A0 */	stw r0, 0x6a0(r26)
lbl_80069DD4:
/* 80069DD4 000669B4  88 1A 05 94 */	lbz r0, 0x594(r26)
/* 80069DD8 000669B8  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 80069DDC 000669BC  41 82 00 38 */	beq lbl_80069E14
/* 80069DE0 000669C0  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 80069DE4 000669C4  D0 1A 06 EC */	stfs f0, 0x6ec(r26)
/* 80069DE8 000669C8  D0 1A 06 E8 */	stfs f0, 0x6e8(r26)
/* 80069DEC 000669CC  D0 1A 06 E4 */	stfs f0, 0x6e4(r26)
/* 80069DF0 000669D0  D0 1A 06 E0 */	stfs f0, 0x6e0(r26)
/* 80069DF4 000669D4  D0 1A 06 DC */	stfs f0, 0x6dc(r26)
/* 80069DF8 000669D8  D0 1A 06 D8 */	stfs f0, 0x6d8(r26)
/* 80069DFC 000669DC  80 7A 06 C0 */	lwz r3, 0x6c0(r26)
/* 80069E00 000669E0  80 1A 06 C4 */	lwz r0, 0x6c4(r26)
/* 80069E04 000669E4  90 7A 06 CC */	stw r3, 0x6cc(r26)
/* 80069E08 000669E8  90 1A 06 D0 */	stw r0, 0x6d0(r26)
/* 80069E0C 000669EC  80 1A 06 C8 */	lwz r0, 0x6c8(r26)
/* 80069E10 000669F0  90 1A 06 D4 */	stw r0, 0x6d4(r26)
lbl_80069E14:
/* 80069E14 000669F4  FC 00 E8 50 */	fneg f0, f29
/* 80069E18 000669F8  D0 1A 03 E4 */	stfs f0, 0x3e4(r26)
/* 80069E1C 000669FC  48 00 00 64 */	b lbl_80069E80
lbl_80069E20:
/* 80069E20 00066A00  80 1A 05 90 */	lwz r0, 0x590(r26)
/* 80069E24 00066A04  28 00 00 00 */	cmplwi r0, 0
/* 80069E28 00066A08  41 82 00 50 */	beq lbl_80069E78
/* 80069E2C 00066A0C  C0 02 88 78 */	lfs f0, lbl_804D8258(r2)
/* 80069E30 00066A10  FC 00 F8 00 */	fcmpu cr0, f0, f31
/* 80069E34 00066A14  40 82 00 08 */	bne lbl_80069E3C
/* 80069E38 00066A18  48 00 00 30 */	b lbl_80069E68
lbl_80069E3C:
/* 80069E3C 00066A1C  FC 1F 18 00 */	fcmpu cr0, f31, f3
/* 80069E40 00066A20  41 82 00 0C */	beq lbl_80069E4C
/* 80069E44 00066A24  FC 60 F8 90 */	fmr f3, f31
/* 80069E48 00066A28  48 00 00 20 */	b lbl_80069E68
lbl_80069E4C:
/* 80069E4C 00066A2C  88 7D 00 00 */	lbz r3, 0(r29)
/* 80069E50 00066A30  3C 00 43 30 */	lis r0, 0x4330
/* 80069E54 00066A34  C8 22 88 98 */	lfd f1, lbl_804D8278(r2)
/* 80069E58 00066A38  90 61 00 5C */	stw r3, 0x5c(r1)
/* 80069E5C 00066A3C  90 01 00 58 */	stw r0, 0x58(r1)
/* 80069E60 00066A40  C8 01 00 58 */	lfd f0, 0x58(r1)
/* 80069E64 00066A44  EC 60 08 28 */	fsubs f3, f0, f1
lbl_80069E68:
/* 80069E68 00066A48  FC 20 E8 90 */	fmr f1, f29
/* 80069E6C 00066A4C  7F C3 F3 78 */	mr r3, r30
/* 80069E70 00066A50  FC 40 F0 90 */	fmr f2, f30
/* 80069E74 00066A54  48 00 4D 75 */	bl func_8006EBE8
lbl_80069E78:
/* 80069E78 00066A58  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 80069E7C 00066A5C  D0 1A 03 E4 */	stfs f0, 0x3e4(r26)
lbl_80069E80:
/* 80069E80 00066A60  7F C3 F3 78 */	mr r3, r30
/* 80069E84 00066A64  48 00 4B 31 */	bl func_8006E9B4
/* 80069E88 00066A68  2C 1C 00 00 */	cmpwi r28, 0
/* 80069E8C 00066A6C  41 82 01 24 */	beq lbl_80069FB0
/* 80069E90 00066A70  88 1D 00 00 */	lbz r0, 0(r29)
/* 80069E94 00066A74  28 00 00 00 */	cmplwi r0, 0
/* 80069E98 00066A78  41 82 01 18 */	beq lbl_80069FB0
/* 80069E9C 00066A7C  80 1A 05 E8 */	lwz r0, 0x5e8(r26)
/* 80069EA0 00066A80  57 9C 20 36 */	slwi r28, r28, 4
/* 80069EA4 00066A84  7C 60 E2 14 */	add r3, r0, r28
/* 80069EA8 00066A88  83 A3 00 04 */	lwz r29, 4(r3)
/* 80069EAC 00066A8C  28 1D 00 00 */	cmplwi r29, 0
/* 80069EB0 00066A90  40 82 00 14 */	bne lbl_80069EC4
/* 80069EB4 00066A94  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 80069EB8 00066A98  38 80 03 D3 */	li r4, 0x3d3
/* 80069EBC 00066A9C  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 80069EC0 00066AA0  48 31 E3 61 */	bl __assert
lbl_80069EC4:
/* 80069EC4 00066AA4  80 7D 00 38 */	lwz r3, 0x38(r29)
/* 80069EC8 00066AA8  80 1D 00 3C */	lwz r0, 0x3c(r29)
/* 80069ECC 00066AAC  90 61 00 44 */	stw r3, 0x44(r1)
/* 80069ED0 00066AB0  90 01 00 48 */	stw r0, 0x48(r1)
/* 80069ED4 00066AB4  80 1D 00 40 */	lwz r0, 0x40(r29)
/* 80069ED8 00066AB8  90 01 00 4C */	stw r0, 0x4c(r1)
/* 80069EDC 00066ABC  80 7A 05 E8 */	lwz r3, 0x5e8(r26)
/* 80069EE0 00066AC0  7E E3 E0 2E */	lwzx r23, r3, r28
/* 80069EE4 00066AC4  28 17 00 00 */	cmplwi r23, 0
/* 80069EE8 00066AC8  40 82 00 14 */	bne lbl_80069EFC
/* 80069EEC 00066ACC  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 80069EF0 00066AD0  38 80 03 94 */	li r4, 0x394
/* 80069EF4 00066AD4  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 80069EF8 00066AD8  48 31 E3 29 */	bl __assert
lbl_80069EFC:
/* 80069EFC 00066ADC  80 61 00 44 */	lwz r3, 0x44(r1)
/* 80069F00 00066AE0  80 01 00 48 */	lwz r0, 0x48(r1)
/* 80069F04 00066AE4  90 77 00 38 */	stw r3, 0x38(r23)
/* 80069F08 00066AE8  90 17 00 3C */	stw r0, 0x3c(r23)
/* 80069F0C 00066AEC  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 80069F10 00066AF0  90 17 00 40 */	stw r0, 0x40(r23)
/* 80069F14 00066AF4  80 17 00 14 */	lwz r0, 0x14(r23)
/* 80069F18 00066AF8  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 80069F1C 00066AFC  40 82 00 4C */	bne lbl_80069F68
/* 80069F20 00066B00  28 17 00 00 */	cmplwi r23, 0
/* 80069F24 00066B04  41 82 00 44 */	beq lbl_80069F68
/* 80069F28 00066B08  40 82 00 14 */	bne lbl_80069F3C
/* 80069F2C 00066B0C  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 80069F30 00066B10  38 80 02 34 */	li r4, 0x234
/* 80069F34 00066B14  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 80069F38 00066B18  48 31 E2 E9 */	bl __assert
lbl_80069F3C:
/* 80069F3C 00066B1C  80 97 00 14 */	lwz r4, 0x14(r23)
/* 80069F40 00066B20  38 60 00 00 */	li r3, 0
/* 80069F44 00066B24  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80069F48 00066B28  40 82 00 10 */	bne lbl_80069F58
/* 80069F4C 00066B2C  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80069F50 00066B30  41 82 00 08 */	beq lbl_80069F58
/* 80069F54 00066B34  38 60 00 01 */	li r3, 1
lbl_80069F58:
/* 80069F58 00066B38  2C 03 00 00 */	cmpwi r3, 0
/* 80069F5C 00066B3C  40 82 00 0C */	bne lbl_80069F68
/* 80069F60 00066B40  7E E3 BB 78 */	mr r3, r23
/* 80069F64 00066B44  48 30 93 85 */	bl HSD_JObjSetMtxDirtySub
lbl_80069F68:
/* 80069F68 00066B48  28 1D 00 00 */	cmplwi r29, 0
/* 80069F6C 00066B4C  40 82 00 14 */	bne lbl_80069F80
/* 80069F70 00066B50  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 80069F74 00066B54  38 80 02 BB */	li r4, 0x2bb
/* 80069F78 00066B58  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 80069F7C 00066B5C  48 31 E2 A5 */	bl __assert
lbl_80069F80:
/* 80069F80 00066B60  80 7D 00 1C */	lwz r3, 0x1c(r29)
/* 80069F84 00066B64  38 81 00 34 */	addi r4, r1, 0x34
/* 80069F88 00066B68  80 1D 00 20 */	lwz r0, 0x20(r29)
/* 80069F8C 00066B6C  90 61 00 34 */	stw r3, 0x34(r1)
/* 80069F90 00066B70  90 01 00 38 */	stw r0, 0x38(r1)
/* 80069F94 00066B74  80 7D 00 24 */	lwz r3, 0x24(r29)
/* 80069F98 00066B78  80 1D 00 28 */	lwz r0, 0x28(r29)
/* 80069F9C 00066B7C  90 61 00 3C */	stw r3, 0x3c(r1)
/* 80069FA0 00066B80  90 01 00 40 */	stw r0, 0x40(r1)
/* 80069FA4 00066B84  80 7A 05 E8 */	lwz r3, 0x5e8(r26)
/* 80069FA8 00066B88  7C 63 E0 2E */	lwzx r3, r3, r28
/* 80069FAC 00066B8C  48 00 B8 A1 */	bl func_8007584C
lbl_80069FB0:
/* 80069FB0 00066B90  88 1A 05 94 */	lbz r0, 0x594(r26)
/* 80069FB4 00066B94  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 80069FB8 00066B98  41 82 00 6C */	beq lbl_8006A024
/* 80069FBC 00066B9C  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 80069FC0 00066BA0  FC 1D 00 00 */	fcmpu cr0, f29, f0
/* 80069FC4 00066BA4  40 82 00 38 */	bne lbl_80069FFC
/* 80069FC8 00066BA8  D0 1A 06 B8 */	stfs f0, 0x6b8(r26)
/* 80069FCC 00066BAC  D0 1A 06 B4 */	stfs f0, 0x6b4(r26)
/* 80069FD0 00066BB0  D0 1A 06 B0 */	stfs f0, 0x6b0(r26)
/* 80069FD4 00066BB4  D0 1A 06 AC */	stfs f0, 0x6ac(r26)
/* 80069FD8 00066BB8  D0 1A 06 A8 */	stfs f0, 0x6a8(r26)
/* 80069FDC 00066BBC  D0 1A 06 A4 */	stfs f0, 0x6a4(r26)
/* 80069FE0 00066BC0  80 7A 06 8C */	lwz r3, 0x68c(r26)
/* 80069FE4 00066BC4  80 1A 06 90 */	lwz r0, 0x690(r26)
/* 80069FE8 00066BC8  90 7A 06 98 */	stw r3, 0x698(r26)
/* 80069FEC 00066BCC  90 1A 06 9C */	stw r0, 0x69c(r26)
/* 80069FF0 00066BD0  80 1A 06 94 */	lwz r0, 0x694(r26)
/* 80069FF4 00066BD4  90 1A 06 A0 */	stw r0, 0x6a0(r26)
/* 80069FF8 00066BD8  48 00 00 2C */	b lbl_8006A024
lbl_80069FFC:
/* 80069FFC 00066BDC  57 E0 06 B5 */	rlwinm. r0, r31, 0, 0x1a, 0x1a
/* 8006A000 00066BE0  40 82 00 24 */	bne lbl_8006A024
/* 8006A004 00066BE4  80 1A 00 E0 */	lwz r0, 0xe0(r26)
/* 8006A008 00066BE8  2C 00 00 00 */	cmpwi r0, 0
/* 8006A00C 00066BEC  40 82 00 18 */	bne lbl_8006A024
/* 8006A010 00066BF0  C0 3A 06 AC */	lfs f1, 0x6ac(r26)
/* 8006A014 00066BF4  C0 1A 00 2C */	lfs f0, 0x2c(r26)
/* 8006A018 00066BF8  EC 01 00 32 */	fmuls f0, f1, f0
/* 8006A01C 00066BFC  D0 1A 00 80 */	stfs f0, 0x80(r26)
/* 8006A020 00066C00  D0 1A 00 EC */	stfs f0, 0xec(r26)
lbl_8006A024:
/* 8006A024 00066C04  88 1A 05 94 */	lbz r0, 0x594(r26)
/* 8006A028 00066C08  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 8006A02C 00066C0C  41 82 00 6C */	beq lbl_8006A098
/* 8006A030 00066C10  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006A034 00066C14  FC 1D 00 00 */	fcmpu cr0, f29, f0
/* 8006A038 00066C18  40 82 00 38 */	bne lbl_8006A070
/* 8006A03C 00066C1C  D0 1A 06 EC */	stfs f0, 0x6ec(r26)
/* 8006A040 00066C20  D0 1A 06 E8 */	stfs f0, 0x6e8(r26)
/* 8006A044 00066C24  D0 1A 06 E4 */	stfs f0, 0x6e4(r26)
/* 8006A048 00066C28  D0 1A 06 E0 */	stfs f0, 0x6e0(r26)
/* 8006A04C 00066C2C  D0 1A 06 DC */	stfs f0, 0x6dc(r26)
/* 8006A050 00066C30  D0 1A 06 D8 */	stfs f0, 0x6d8(r26)
/* 8006A054 00066C34  80 7A 06 C0 */	lwz r3, 0x6c0(r26)
/* 8006A058 00066C38  80 1A 06 C4 */	lwz r0, 0x6c4(r26)
/* 8006A05C 00066C3C  90 7A 06 CC */	stw r3, 0x6cc(r26)
/* 8006A060 00066C40  90 1A 06 D0 */	stw r0, 0x6d0(r26)
/* 8006A064 00066C44  80 1A 06 C8 */	lwz r0, 0x6c8(r26)
/* 8006A068 00066C48  90 1A 06 D4 */	stw r0, 0x6d4(r26)
/* 8006A06C 00066C4C  48 00 00 2C */	b lbl_8006A098
lbl_8006A070:
/* 8006A070 00066C50  57 E0 06 B5 */	rlwinm. r0, r31, 0, 0x1a, 0x1a
/* 8006A074 00066C54  40 82 00 24 */	bne lbl_8006A098
/* 8006A078 00066C58  80 1A 00 E0 */	lwz r0, 0xe0(r26)
/* 8006A07C 00066C5C  2C 00 00 00 */	cmpwi r0, 0
/* 8006A080 00066C60  40 82 00 18 */	bne lbl_8006A098
/* 8006A084 00066C64  C0 3A 06 E0 */	lfs f1, 0x6e0(r26)
/* 8006A088 00066C68  C0 1A 00 2C */	lfs f0, 0x2c(r26)
/* 8006A08C 00066C6C  EC 01 00 32 */	fmuls f0, f1, f0
/* 8006A090 00066C70  D0 1A 00 80 */	stfs f0, 0x80(r26)
/* 8006A094 00066C74  D0 1A 00 EC */	stfs f0, 0xec(r26)
lbl_8006A098:
/* 8006A098 00066C78  57 E0 04 63 */	rlwinm. r0, r31, 0, 0x11, 0x11
/* 8006A09C 00066C7C  41 82 00 10 */	beq lbl_8006A0AC
/* 8006A0A0 00066C80  7F C3 F3 78 */	mr r3, r30
/* 8006A0A4 00066C84  48 00 93 F9 */	bl func_8007349C
/* 8006A0A8 00066C88  48 00 00 38 */	b lbl_8006A0E0
lbl_8006A0AC:
/* 8006A0AC 00066C8C  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006A0B0 00066C90  FC 1D 00 00 */	fcmpu cr0, f29, f0
/* 8006A0B4 00066C94  41 82 00 10 */	beq lbl_8006A0C4
/* 8006A0B8 00066C98  7F C3 F3 78 */	mr r3, r30
/* 8006A0BC 00066C9C  48 00 92 99 */	bl func_80073354
/* 8006A0C0 00066CA0  48 00 00 20 */	b lbl_8006A0E0
lbl_8006A0C4:
/* 8006A0C4 00066CA4  7F C3 F3 78 */	mr r3, r30
/* 8006A0C8 00066CA8  48 05 63 41 */	bl func_800C0408
/* 8006A0CC 00066CAC  7F C3 F3 78 */	mr r3, r30
/* 8006A0D0 00066CB0  48 00 91 71 */	bl func_80073240
/* 8006A0D4 00066CB4  48 00 00 0C */	b lbl_8006A0E0
lbl_8006A0D8:
/* 8006A0D8 00066CB8  38 00 FF FF */	li r0, -1
/* 8006A0DC 00066CBC  90 1A 00 14 */	stw r0, 0x14(r26)
lbl_8006A0E0:
/* 8006A0E0 00066CC0  80 1A 00 14 */	lwz r0, 0x14(r26)
/* 8006A0E4 00066CC4  2C 00 FF FF */	cmpwi r0, -1
/* 8006A0E8 00066CC8  40 82 00 2C */	bne lbl_8006A114
/* 8006A0EC 00066CCC  3A E0 00 00 */	li r23, 0
/* 8006A0F0 00066CD0  92 FA 05 94 */	stw r23, 0x594(r26)
/* 8006A0F4 00066CD4  7F 63 DB 78 */	mr r3, r27
/* 8006A0F8 00066CD8  48 00 66 61 */	bl func_80070758
/* 8006A0FC 00066CDC  80 7A 08 AC */	lwz r3, 0x8ac(r26)
/* 8006A100 00066CE0  48 00 66 59 */	bl func_80070758
/* 8006A104 00066CE4  92 FA 03 EC */	stw r23, 0x3ec(r26)
/* 8006A108 00066CE8  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006A10C 00066CEC  D0 1A 08 A4 */	stfs f0, 0x8a4(r26)
/* 8006A110 00066CF0  D0 1A 08 A8 */	stfs f0, 0x8a8(r26)
lbl_8006A114:
/* 8006A114 00066CF4  2C 18 00 00 */	cmpwi r24, 0
/* 8006A118 00066CF8  41 82 00 20 */	beq lbl_8006A138
/* 8006A11C 00066CFC  88 1A 05 94 */	lbz r0, 0x594(r26)
/* 8006A120 00066D00  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8006A124 00066D04  40 82 00 14 */	bne lbl_8006A138
/* 8006A128 00066D08  40 82 00 10 */	bne lbl_8006A138
/* 8006A12C 00066D0C  C0 3A 01 38 */	lfs f1, 0x138(r26)
/* 8006A130 00066D10  7F 43 D3 78 */	mr r3, r26
/* 8006A134 00066D14  48 01 2B 45 */	bl func_8007CC78
lbl_8006A138:
/* 8006A138 00066D18  80 79 00 0C */	lwz r3, 0xc(r25)
/* 8006A13C 00066D1C  38 00 00 00 */	li r0, 0
/* 8006A140 00066D20  90 7A 21 A0 */	stw r3, 0x21a0(r26)
/* 8006A144 00066D24  80 79 00 10 */	lwz r3, 0x10(r25)
/* 8006A148 00066D28  90 7A 21 9C */	stw r3, 0x219c(r26)
/* 8006A14C 00066D2C  80 79 00 14 */	lwz r3, 0x14(r25)
/* 8006A150 00066D30  90 7A 21 A4 */	stw r3, 0x21a4(r26)
/* 8006A154 00066D34  80 79 00 18 */	lwz r3, 0x18(r25)
/* 8006A158 00066D38  90 7A 21 A8 */	stw r3, 0x21a8(r26)
/* 8006A15C 00066D3C  80 79 00 1C */	lwz r3, 0x1c(r25)
/* 8006A160 00066D40  90 7A 21 AC */	stw r3, 0x21ac(r26)
/* 8006A164 00066D44  90 1A 21 B0 */	stw r0, 0x21b0(r26)
/* 8006A168 00066D48  90 1A 21 BC */	stw r0, 0x21bc(r26)
/* 8006A16C 00066D4C  90 1A 21 C0 */	stw r0, 0x21c0(r26)
/* 8006A170 00066D50  90 1A 21 C4 */	stw r0, 0x21c4(r26)
/* 8006A174 00066D54  90 1A 21 C8 */	stw r0, 0x21c8(r26)
/* 8006A178 00066D58  90 1A 21 D0 */	stw r0, 0x21d0(r26)
/* 8006A17C 00066D5C  90 1A 21 CC */	stw r0, 0x21cc(r26)
/* 8006A180 00066D60  90 1A 21 D8 */	stw r0, 0x21d8(r26)
/* 8006A184 00066D64  90 1A 21 D4 */	stw r0, 0x21d4(r26)
/* 8006A188 00066D68  90 1A 21 DC */	stw r0, 0x21dc(r26)
/* 8006A18C 00066D6C  90 1A 21 F0 */	stw r0, 0x21f0(r26)
/* 8006A190 00066D70  90 1A 21 F4 */	stw r0, 0x21f4(r26)
/* 8006A194 00066D74  90 1A 21 F8 */	stw r0, 0x21f8(r26)
/* 8006A198 00066D78  90 1A 21 E4 */	stw r0, 0x21e4(r26)
/* 8006A19C 00066D7C  80 01 00 A4 */	lwz r0, 0xa4(r1)
/* 8006A1A0 00066D80  CB E1 00 98 */	lfd f31, 0x98(r1)
/* 8006A1A4 00066D84  CB C1 00 90 */	lfd f30, 0x90(r1)
/* 8006A1A8 00066D88  CB A1 00 88 */	lfd f29, 0x88(r1)
/* 8006A1AC 00066D8C  BA C1 00 60 */	lmw r22, 0x60(r1)
/* 8006A1B0 00066D90  38 21 00 A0 */	addi r1, r1, 0xa0
/* 8006A1B4 00066D94  7C 08 03 A6 */	mtlr r0
/* 8006A1B8 00066D98  4E 80 00 20 */	blr 
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
/* 8006A7FC 000673DC  48 20 0B 05 */	bl func_8026B300
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
/* 8006A9D0 000675B0  48 20 09 31 */	bl func_8026B300
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

asm void func_8006ABA0()
{
	nofralloc
/* 8006ABA0 00067780  7C 08 02 A6 */	mflr r0
/* 8006ABA4 00067784  90 01 00 04 */	stw r0, 4(r1)
/* 8006ABA8 00067788  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8006ABAC 0006778C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8006ABB0 00067790  7C 7F 1B 78 */	mr r31, r3
/* 8006ABB4 00067794  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8006ABB8 00067798  88 03 22 1F */	lbz r0, 0x221f(r3)
/* 8006ABBC 0006779C  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 8006ABC0 000677A0  40 82 00 18 */	bne lbl_8006ABD8
/* 8006ABC4 000677A4  48 03 74 7D */	bl func_800A2040
/* 8006ABC8 000677A8  2C 03 00 00 */	cmpwi r3, 0
/* 8006ABCC 000677AC  41 82 00 0C */	beq lbl_8006ABD8
/* 8006ABD0 000677B0  7F E3 FB 78 */	mr r3, r31
/* 8006ABD4 000677B4  48 04 8D 2D */	bl func_800B3900
lbl_8006ABD8:
/* 8006ABD8 000677B8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8006ABDC 000677BC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8006ABE0 000677C0  38 21 00 18 */	addi r1, r1, 0x18
/* 8006ABE4 000677C4  7C 08 03 A6 */	mtlr r0
/* 8006ABE8 000677C8  4E 80 00 20 */	blr  
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


asm void func_8006B82C()
{
	nofralloc 
/* 8006B82C 0006840C  7C 08 02 A6 */	mflr r0
/* 8006B830 00068410  90 01 00 04 */	stw r0, 4(r1)
/* 8006B834 00068414  94 21 FF 70 */	stwu r1, -0x90(r1)
/* 8006B838 00068418  DB E1 00 88 */	stfd f31, 0x88(r1)
/* 8006B83C 0006841C  DB C1 00 80 */	stfd f30, 0x80(r1)
/* 8006B840 00068420  BF 41 00 68 */	stmw r26, 0x68(r1)
/* 8006B844 00068424  7C 7C 1B 78 */	mr r28, r3
/* 8006B848 00068428  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8006B84C 0006842C  88 03 22 1F */	lbz r0, 0x221f(r3)
/* 8006B850 00068430  3B E3 00 00 */	addi r31, r3, 0
/* 8006B854 00068434  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 8006B858 00068438  40 82 08 7C */	bne lbl_8006C0D4
/* 8006B85C 0006843C  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 8006B860 00068440  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 8006B864 00068444  40 82 05 84 */	bne lbl_8006BDE8
/* 8006B868 00068448  80 7F 20 64 */	lwz r3, 0x2064(r31)
/* 8006B86C 0006844C  2C 03 00 00 */	cmpwi r3, 0
/* 8006B870 00068450  41 82 00 0C */	beq lbl_8006B87C
/* 8006B874 00068454  38 03 FF FF */	addi r0, r3, -1
/* 8006B878 00068458  90 1F 20 64 */	stw r0, 0x2064(r31)
lbl_8006B87C:
/* 8006B87C 0006845C  80 7F 21 08 */	lwz r3, 0x2108(r31)
/* 8006B880 00068460  2C 03 00 00 */	cmpwi r3, 0
/* 8006B884 00068464  41 82 00 0C */	beq lbl_8006B890
/* 8006B888 00068468  38 03 FF FF */	addi r0, r3, -1
/* 8006B88C 0006846C  90 1F 21 08 */	stw r0, 0x2108(r31)
lbl_8006B890:
/* 8006B890 00068470  7F 83 E3 78 */	mr r3, r28
/* 8006B894 00068474  48 05 52 05 */	bl func_800C0A98
/* 8006B898 00068478  81 9F 21 A4 */	lwz r12, 0x21a4(r31)
/* 8006B89C 0006847C  28 0C 00 00 */	cmplwi r12, 0
/* 8006B8A0 00068480  41 82 00 10 */	beq lbl_8006B8B0
/* 8006B8A4 00068484  7D 88 03 A6 */	mtlr r12
/* 8006B8A8 00068488  38 7C 00 00 */	addi r3, r28, 0
/* 8006B8AC 0006848C  4E 80 00 21 */	blrl 
lbl_8006B8B0:
/* 8006B8B0 00068490  C0 22 88 74 */	lfs f1, lbl_804D8254(r2)
/* 8006B8B4 00068494  3B DF 00 8C */	addi r30, r31, 0x8c
/* 8006B8B8 00068498  C0 5F 00 8C */	lfs f2, 0x8c(r31)
/* 8006B8BC 0006849C  FC 01 10 00 */	fcmpu cr0, f1, f2
/* 8006B8C0 000684A0  40 82 00 10 */	bne lbl_8006B8D0
/* 8006B8C4 000684A4  C0 1E 00 04 */	lfs f0, 4(r30)
/* 8006B8C8 000684A8  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8006B8CC 000684AC  41 82 01 90 */	beq lbl_8006BA5C
lbl_8006B8D0:
/* 8006B8D0 000684B0  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 8006B8D4 000684B4  2C 00 00 01 */	cmpwi r0, 1
/* 8006B8D8 000684B8  40 82 01 20 */	bne lbl_8006B9F8
/* 8006B8DC 000684BC  88 1F 22 28 */	lbz r0, 0x2228(r31)
/* 8006B8E0 000684C0  C3 FE 00 00 */	lfs f31, 0(r30)
/* 8006B8E4 000684C4  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8006B8E8 000684C8  C3 DE 00 04 */	lfs f30, 4(r30)
/* 8006B8EC 000684CC  41 82 00 38 */	beq lbl_8006B924
/* 8006B8F0 000684D0  7F E3 FB 78 */	mr r3, r31
/* 8006B8F4 000684D4  48 01 14 B1 */	bl func_8007CDA4
/* 8006B8F8 000684D8  FC 40 08 90 */	fmr f2, f1
/* 8006B8FC 000684DC  C0 3E 00 00 */	lfs f1, 0(r30)
/* 8006B900 000684E0  48 01 14 6D */	bl func_8007CD6C
/* 8006B904 000684E4  D0 3E 00 00 */	stfs f1, 0(r30)
/* 8006B908 000684E8  7F E3 FB 78 */	mr r3, r31
/* 8006B90C 000684EC  48 01 14 ED */	bl func_8007CDF8
/* 8006B910 000684F0  FC 40 08 90 */	fmr f2, f1
/* 8006B914 000684F4  C0 3E 00 04 */	lfs f1, 4(r30)
/* 8006B918 000684F8  48 01 14 55 */	bl func_8007CD6C
/* 8006B91C 000684FC  D0 3E 00 04 */	stfs f1, 4(r30)
/* 8006B920 00068500  48 00 00 CC */	b lbl_8006B9EC
lbl_8006B924:
/* 8006B924 00068504  FC 20 F0 90 */	fmr f1, f30
/* 8006B928 00068508  FC 40 F8 90 */	fmr f2, f31
/* 8006B92C 0006850C  4B FB 73 05 */	bl func_80022C30
/* 8006B930 00068510  EC 5E 07 B2 */	fmuls f2, f30, f30
/* 8006B934 00068514  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006B938 00068518  EC 9F 17 FA */	fmadds f4, f31, f31, f2
/* 8006B93C 0006851C  FF E0 08 90 */	fmr f31, f1
/* 8006B940 00068520  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 8006B944 00068524  40 81 00 50 */	ble lbl_8006B994
/* 8006B948 00068528  FC 20 20 34 */	frsqrte f1, f4
/* 8006B94C 0006852C  C8 62 88 A0 */	lfd f3, lbl_804D8280(r2)
/* 8006B950 00068530  C8 42 88 A8 */	lfd f2, lbl_804D8288(r2)
/* 8006B954 00068534  FC 01 00 72 */	fmul f0, f1, f1
/* 8006B958 00068538  FC 23 00 72 */	fmul f1, f3, f1
/* 8006B95C 0006853C  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8006B960 00068540  FC 21 00 32 */	fmul f1, f1, f0
/* 8006B964 00068544  FC 01 00 72 */	fmul f0, f1, f1
/* 8006B968 00068548  FC 23 00 72 */	fmul f1, f3, f1
/* 8006B96C 0006854C  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8006B970 00068550  FC 21 00 32 */	fmul f1, f1, f0
/* 8006B974 00068554  FC 01 00 72 */	fmul f0, f1, f1
/* 8006B978 00068558  FC 23 00 72 */	fmul f1, f3, f1
/* 8006B97C 0006855C  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8006B980 00068560  FC 01 00 32 */	fmul f0, f1, f0
/* 8006B984 00068564  FC 04 00 32 */	fmul f0, f4, f0
/* 8006B988 00068568  FC 00 00 18 */	frsp f0, f0
/* 8006B98C 0006856C  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 8006B990 00068570  C0 81 00 20 */	lfs f4, 0x20(r1)
lbl_8006B994:
/* 8006B994 00068574  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 8006B998 00068578  C0 03 02 04 */	lfs f0, 0x204(r3)
/* 8006B99C 0006857C  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 8006B9A0 00068580  40 80 00 14 */	bge lbl_8006B9B4
/* 8006B9A4 00068584  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006B9A8 00068588  D0 1E 00 04 */	stfs f0, 4(r30)
/* 8006B9AC 0006858C  D0 1E 00 00 */	stfs f0, 0(r30)
/* 8006B9B0 00068590  48 00 00 3C */	b lbl_8006B9EC
lbl_8006B9B4:
/* 8006B9B4 00068594  FC 20 F8 90 */	fmr f1, f31
/* 8006B9B8 00068598  48 2B A8 89 */	bl cosf
/* 8006B9BC 0006859C  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 8006B9C0 000685A0  C0 1E 00 00 */	lfs f0, 0(r30)
/* 8006B9C4 000685A4  C0 43 02 04 */	lfs f2, 0x204(r3)
/* 8006B9C8 000685A8  EC 02 00 7C */	fnmsubs f0, f2, f1, f0
/* 8006B9CC 000685AC  FC 20 F8 90 */	fmr f1, f31
/* 8006B9D0 000685B0  D0 1E 00 00 */	stfs f0, 0(r30)
/* 8006B9D4 000685B4  48 2B AA 01 */	bl sinf
/* 8006B9D8 000685B8  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 8006B9DC 000685BC  C0 1E 00 04 */	lfs f0, 4(r30)
/* 8006B9E0 000685C0  C0 43 02 04 */	lfs f2, 0x204(r3)
/* 8006B9E4 000685C4  EC 02 00 7C */	fnmsubs f0, f2, f1, f0
/* 8006B9E8 000685C8  D0 1E 00 04 */	stfs f0, 4(r30)
lbl_8006B9EC:
/* 8006B9EC 000685CC  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006B9F0 000685D0  D0 1F 00 F0 */	stfs f0, 0xf0(r31)
/* 8006B9F4 000685D4  48 00 00 68 */	b lbl_8006BA5C
lbl_8006B9F8:
/* 8006B9F8 000685D8  C0 22 88 74 */	lfs f1, lbl_804D8254(r2)
/* 8006B9FC 000685DC  3B BF 08 44 */	addi r29, r31, 0x844
/* 8006BA00 000685E0  C0 1F 00 F0 */	lfs f0, 0xf0(r31)
/* 8006BA04 000685E4  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8006BA08 000685E8  40 82 00 08 */	bne lbl_8006BA10
/* 8006BA0C 000685EC  D0 5F 00 F0 */	stfs f2, 0xf0(r31)
lbl_8006BA10:
/* 8006BA10 000685F0  3B 7F 01 10 */	addi r27, r31, 0x110
/* 8006BA14 000685F4  38 7F 00 00 */	addi r3, r31, 0
/* 8006BA18 000685F8  48 01 90 29 */	bl func_80084A40
/* 8006BA1C 000685FC  C0 1B 00 18 */	lfs f0, 0x18(r27)
/* 8006BA20 00068600  7F E3 FB 78 */	mr r3, r31
/* 8006BA24 00068604  80 8D AE B4 */	lwz r4, lbl_804D6554(r13)
/* 8006BA28 00068608  EC 20 00 72 */	fmuls f1, f0, f1
/* 8006BA2C 0006860C  C0 04 02 00 */	lfs f0, 0x200(r4)
/* 8006BA30 00068610  EC 20 00 72 */	fmuls f1, f0, f1
/* 8006BA34 00068614  48 01 12 6D */	bl func_8007CCA0
/* 8006BA38 00068618  C0 3D 00 04 */	lfs f1, 4(r29)
/* 8006BA3C 0006861C  C0 1F 00 F0 */	lfs f0, 0xf0(r31)
/* 8006BA40 00068620  EC 01 00 32 */	fmuls f0, f1, f0
/* 8006BA44 00068624  D0 1E 00 00 */	stfs f0, 0(r30)
/* 8006BA48 00068628  C0 3D 00 00 */	lfs f1, 0(r29)
/* 8006BA4C 0006862C  C0 1F 00 F0 */	lfs f0, 0xf0(r31)
/* 8006BA50 00068630  FC 20 08 50 */	fneg f1, f1
/* 8006BA54 00068634  EC 01 00 32 */	fmuls f0, f1, f0
/* 8006BA58 00068638  D0 1E 00 04 */	stfs f0, 4(r30)
lbl_8006BA5C:
/* 8006BA5C 0006863C  C0 22 88 74 */	lfs f1, lbl_804D8254(r2)
/* 8006BA60 00068640  3B BF 00 98 */	addi r29, r31, 0x98
/* 8006BA64 00068644  C0 5F 00 98 */	lfs f2, 0x98(r31)
/* 8006BA68 00068648  FC 01 10 00 */	fcmpu cr0, f1, f2
/* 8006BA6C 0006864C  40 82 00 10 */	bne lbl_8006BA7C
/* 8006BA70 00068650  C0 1D 00 04 */	lfs f0, 4(r29)
/* 8006BA74 00068654  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8006BA78 00068658  41 82 01 50 */	beq lbl_8006BBC8
lbl_8006BA7C:
/* 8006BA7C 0006865C  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 8006BA80 00068660  2C 00 00 01 */	cmpwi r0, 1
/* 8006BA84 00068664  40 82 00 E0 */	bne lbl_8006BB64
/* 8006BA88 00068668  C3 DD 00 00 */	lfs f30, 0(r29)
/* 8006BA8C 0006866C  C3 FD 00 04 */	lfs f31, 4(r29)
/* 8006BA90 00068670  FC 40 F0 90 */	fmr f2, f30
/* 8006BA94 00068674  FC 20 F8 90 */	fmr f1, f31
/* 8006BA98 00068678  4B FB 71 99 */	bl func_80022C30
/* 8006BA9C 0006867C  EC 5F 07 F2 */	fmuls f2, f31, f31
/* 8006BAA0 00068680  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006BAA4 00068684  FF E0 08 90 */	fmr f31, f1
/* 8006BAA8 00068688  EC 9E 17 BA */	fmadds f4, f30, f30, f2
/* 8006BAAC 0006868C  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 8006BAB0 00068690  40 81 00 50 */	ble lbl_8006BB00
/* 8006BAB4 00068694  FC 20 20 34 */	frsqrte f1, f4
/* 8006BAB8 00068698  C8 62 88 A0 */	lfd f3, lbl_804D8280(r2)
/* 8006BABC 0006869C  C8 42 88 A8 */	lfd f2, lbl_804D8288(r2)
/* 8006BAC0 000686A0  FC 01 00 72 */	fmul f0, f1, f1
/* 8006BAC4 000686A4  FC 23 00 72 */	fmul f1, f3, f1
/* 8006BAC8 000686A8  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8006BACC 000686AC  FC 21 00 32 */	fmul f1, f1, f0
/* 8006BAD0 000686B0  FC 01 00 72 */	fmul f0, f1, f1
/* 8006BAD4 000686B4  FC 23 00 72 */	fmul f1, f3, f1
/* 8006BAD8 000686B8  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8006BADC 000686BC  FC 21 00 32 */	fmul f1, f1, f0
/* 8006BAE0 000686C0  FC 01 00 72 */	fmul f0, f1, f1
/* 8006BAE4 000686C4  FC 23 00 72 */	fmul f1, f3, f1
/* 8006BAE8 000686C8  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8006BAEC 000686CC  FC 01 00 32 */	fmul f0, f1, f0
/* 8006BAF0 000686D0  FC 04 00 32 */	fmul f0, f4, f0
/* 8006BAF4 000686D4  FC 00 00 18 */	frsp f0, f0
/* 8006BAF8 000686D8  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 8006BAFC 000686DC  C0 81 00 1C */	lfs f4, 0x1c(r1)
lbl_8006BB00:
/* 8006BB00 000686E0  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 8006BB04 000686E4  C0 03 03 E8 */	lfs f0, 0x3e8(r3)
/* 8006BB08 000686E8  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 8006BB0C 000686EC  40 80 00 14 */	bge lbl_8006BB20
/* 8006BB10 000686F0  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006BB14 000686F4  D0 1E 00 04 */	stfs f0, 4(r30)
/* 8006BB18 000686F8  D0 1D 00 00 */	stfs f0, 0(r29)
/* 8006BB1C 000686FC  48 00 00 3C */	b lbl_8006BB58
lbl_8006BB20:
/* 8006BB20 00068700  FC 20 F8 90 */	fmr f1, f31
/* 8006BB24 00068704  48 2B A7 1D */	bl cosf
/* 8006BB28 00068708  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 8006BB2C 0006870C  C0 1D 00 00 */	lfs f0, 0(r29)
/* 8006BB30 00068710  C0 43 03 E8 */	lfs f2, 0x3e8(r3)
/* 8006BB34 00068714  EC 02 00 7C */	fnmsubs f0, f2, f1, f0
/* 8006BB38 00068718  FC 20 F8 90 */	fmr f1, f31
/* 8006BB3C 0006871C  D0 1D 00 00 */	stfs f0, 0(r29)
/* 8006BB40 00068720  48 2B A8 95 */	bl sinf
/* 8006BB44 00068724  80 6D AE B4 */	lwz r3, lbl_804D6554(r13)
/* 8006BB48 00068728  C0 1D 00 04 */	lfs f0, 4(r29)
/* 8006BB4C 0006872C  C0 43 03 E8 */	lfs f2, 0x3e8(r3)
/* 8006BB50 00068730  EC 02 00 7C */	fnmsubs f0, f2, f1, f0
/* 8006BB54 00068734  D0 1D 00 04 */	stfs f0, 4(r29)
lbl_8006BB58:
/* 8006BB58 00068738  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006BB5C 0006873C  D0 1F 00 F4 */	stfs f0, 0xf4(r31)
/* 8006BB60 00068740  48 00 00 68 */	b lbl_8006BBC8
lbl_8006BB64:
/* 8006BB64 00068744  C0 22 88 74 */	lfs f1, lbl_804D8254(r2)
/* 8006BB68 00068748  3B 7F 08 44 */	addi r27, r31, 0x844
/* 8006BB6C 0006874C  C0 1F 00 F4 */	lfs f0, 0xf4(r31)
/* 8006BB70 00068750  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8006BB74 00068754  40 82 00 08 */	bne lbl_8006BB7C
/* 8006BB78 00068758  D0 5F 00 F4 */	stfs f2, 0xf4(r31)
lbl_8006BB7C:
/* 8006BB7C 0006875C  3B 5F 01 10 */	addi r26, r31, 0x110
/* 8006BB80 00068760  38 7F 00 00 */	addi r3, r31, 0
/* 8006BB84 00068764  48 01 8E BD */	bl func_80084A40
/* 8006BB88 00068768  C0 1A 00 18 */	lfs f0, 0x18(r26)
/* 8006BB8C 0006876C  7F E3 FB 78 */	mr r3, r31
/* 8006BB90 00068770  80 8D AE B4 */	lwz r4, lbl_804D6554(r13)
/* 8006BB94 00068774  EC 20 00 72 */	fmuls f1, f0, f1
/* 8006BB98 00068778  C0 04 03 EC */	lfs f0, 0x3ec(r4)
/* 8006BB9C 0006877C  EC 20 00 72 */	fmuls f1, f0, f1
/* 8006BBA0 00068780  48 01 12 AD */	bl func_8007CE4C
/* 8006BBA4 00068784  C0 3B 00 04 */	lfs f1, 4(r27)
/* 8006BBA8 00068788  C0 1F 00 F4 */	lfs f0, 0xf4(r31)
/* 8006BBAC 0006878C  EC 01 00 32 */	fmuls f0, f1, f0
/* 8006BBB0 00068790  D0 1D 00 00 */	stfs f0, 0(r29)
/* 8006BBB4 00068794  C0 3B 00 00 */	lfs f1, 0(r27)
/* 8006BBB8 00068798  C0 1F 00 F4 */	lfs f0, 0xf4(r31)
/* 8006BBBC 0006879C  FC 20 08 50 */	fneg f1, f1
/* 8006BBC0 000687A0  EC 01 00 32 */	fmuls f0, f1, f0
/* 8006BBC4 000687A4  D0 1D 00 04 */	stfs f0, 4(r29)
lbl_8006BBC8:
/* 8006BBC8 000687A8  C0 3F 00 E4 */	lfs f1, 0xe4(r31)
/* 8006BBCC 000687AC  38 7F 00 80 */	addi r3, r31, 0x80
/* 8006BBD0 000687B0  C0 1F 00 E8 */	lfs f0, 0xe8(r31)
/* 8006BBD4 000687B4  7C 65 1B 78 */	mr r5, r3
/* 8006BBD8 000687B8  C0 5F 00 EC */	lfs f2, 0xec(r31)
/* 8006BBDC 000687BC  EC 01 00 2A */	fadds f0, f1, f0
/* 8006BBE0 000687C0  38 9F 00 74 */	addi r4, r31, 0x74
/* 8006BBE4 000687C4  EC 02 00 2A */	fadds f0, f2, f0
/* 8006BBE8 000687C8  D0 1F 00 EC */	stfs f0, 0xec(r31)
/* 8006BBEC 000687CC  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006BBF0 000687D0  D0 1F 00 E8 */	stfs f0, 0xe8(r31)
/* 8006BBF4 000687D4  D0 1F 00 E4 */	stfs f0, 0xe4(r31)
/* 8006BBF8 000687D8  48 2D 71 5D */	bl PSVECAdd
/* 8006BBFC 000687DC  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006BC00 000687E0  D0 1F 00 7C */	stfs f0, 0x7c(r31)
/* 8006BC04 000687E4  D0 1F 00 78 */	stfs f0, 0x78(r31)
/* 8006BC08 000687E8  D0 1F 00 74 */	stfs f0, 0x74(r31)
/* 8006BC0C 000687EC  80 7F 00 80 */	lwz r3, 0x80(r31)
/* 8006BC10 000687F0  80 1F 00 84 */	lwz r0, 0x84(r31)
/* 8006BC14 000687F4  90 61 00 40 */	stw r3, 0x40(r1)
/* 8006BC18 000687F8  90 01 00 44 */	stw r0, 0x44(r1)
/* 8006BC1C 000687FC  80 1F 00 88 */	lwz r0, 0x88(r31)
/* 8006BC20 00068800  90 01 00 48 */	stw r0, 0x48(r1)
/* 8006BC24 00068804  80 1F 19 48 */	lwz r0, 0x1948(r31)
/* 8006BC28 00068808  2C 00 00 00 */	cmpwi r0, 0
/* 8006BC2C 0006880C  41 82 00 8C */	beq lbl_8006BCB8
/* 8006BC30 00068810  80 7F 19 4C */	lwz r3, 0x194c(r31)
/* 8006BC34 00068814  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8006BC38 00068818  90 01 00 5C */	stw r0, 0x5c(r1)
/* 8006BC3C 0006881C  3C 00 43 30 */	lis r0, 0x4330
/* 8006BC40 00068820  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8006BC44 00068824  90 61 00 64 */	stw r3, 0x64(r1)
/* 8006BC48 00068828  C8 62 88 80 */	lfd f3, lbl_804D8260(r2)
/* 8006BC4C 0006882C  90 01 00 60 */	stw r0, 0x60(r1)
/* 8006BC50 00068830  C0 82 88 70 */	lfs f4, lbl_804D8250(r2)
/* 8006BC54 00068834  90 01 00 58 */	stw r0, 0x58(r1)
/* 8006BC58 00068838  C8 21 00 60 */	lfd f1, 0x60(r1)
/* 8006BC5C 0006883C  C8 01 00 58 */	lfd f0, 0x58(r1)
/* 8006BC60 00068840  EC 41 18 28 */	fsubs f2, f1, f3
/* 8006BC64 00068844  C0 BF 00 A4 */	lfs f5, 0xa4(r31)
/* 8006BC68 00068848  EC 20 18 28 */	fsubs f1, f0, f3
/* 8006BC6C 0006884C  C0 1F 00 80 */	lfs f0, 0x80(r31)
/* 8006BC70 00068850  EC 00 28 28 */	fsubs f0, f0, f5
/* 8006BC74 00068854  EC 22 08 24 */	fdivs f1, f2, f1
/* 8006BC78 00068858  EC 44 08 28 */	fsubs f2, f4, f1
/* 8006BC7C 0006885C  EC 02 28 3A */	fmadds f0, f2, f0, f5
/* 8006BC80 00068860  D0 01 00 40 */	stfs f0, 0x40(r1)
/* 8006BC84 00068864  C0 3F 00 A8 */	lfs f1, 0xa8(r31)
/* 8006BC88 00068868  C0 1F 00 84 */	lfs f0, 0x84(r31)
/* 8006BC8C 0006886C  EC 00 08 28 */	fsubs f0, f0, f1
/* 8006BC90 00068870  EC 02 08 3A */	fmadds f0, f2, f0, f1
/* 8006BC94 00068874  D0 01 00 44 */	stfs f0, 0x44(r1)
/* 8006BC98 00068878  80 7F 19 4C */	lwz r3, 0x194c(r31)
/* 8006BC9C 0006887C  38 03 FF FF */	addi r0, r3, -1
/* 8006BCA0 00068880  90 1F 19 4C */	stw r0, 0x194c(r31)
/* 8006BCA4 00068884  80 1F 19 4C */	lwz r0, 0x194c(r31)
/* 8006BCA8 00068888  2C 00 00 00 */	cmpwi r0, 0
/* 8006BCAC 0006888C  40 82 00 0C */	bne lbl_8006BCB8
/* 8006BCB0 00068890  38 00 00 00 */	li r0, 0
/* 8006BCB4 00068894  90 1F 19 48 */	stw r0, 0x1948(r31)
lbl_8006BCB8:
/* 8006BCB8 00068898  C0 3F 00 B0 */	lfs f1, 0xb0(r31)
/* 8006BCBC 0006889C  C0 1F 00 F8 */	lfs f0, 0xf8(r31)
/* 8006BCC0 000688A0  EC 01 00 2A */	fadds f0, f1, f0
/* 8006BCC4 000688A4  D0 1F 00 B0 */	stfs f0, 0xb0(r31)
/* 8006BCC8 000688A8  C0 3F 00 B8 */	lfs f1, 0xb8(r31)
/* 8006BCCC 000688AC  C0 1F 00 FC */	lfs f0, 0xfc(r31)
/* 8006BCD0 000688B0  EC 01 00 2A */	fadds f0, f1, f0
/* 8006BCD4 000688B4  D0 1F 00 B8 */	stfs f0, 0xb8(r31)
/* 8006BCD8 000688B8  88 7F 22 22 */	lbz r3, 0x2222(r31)
/* 8006BCDC 000688BC  54 60 FF FF */	rlwinm. r0, r3, 0x1f, 0x1f, 0x1f
/* 8006BCE0 000688C0  41 82 00 B8 */	beq lbl_8006BD98
/* 8006BCE4 000688C4  54 60 07 FF */	clrlwi. r0, r3, 0x1f
/* 8006BCE8 000688C8  40 82 00 B0 */	bne lbl_8006BD98
/* 8006BCEC 000688CC  38 7F 00 D4 */	addi r3, r31, 0xd4
/* 8006BCF0 000688D0  38 A3 00 00 */	addi r5, r3, 0
/* 8006BCF4 000688D4  38 81 00 40 */	addi r4, r1, 0x40
/* 8006BCF8 000688D8  48 2D 70 5D */	bl PSVECAdd
/* 8006BCFC 000688DC  C0 3F 00 D4 */	lfs f1, 0xd4(r31)
/* 8006BD00 000688E0  C0 1E 00 00 */	lfs f0, 0(r30)
/* 8006BD04 000688E4  EC 01 00 2A */	fadds f0, f1, f0
/* 8006BD08 000688E8  D0 1F 00 D4 */	stfs f0, 0xd4(r31)
/* 8006BD0C 000688EC  C0 3F 00 D8 */	lfs f1, 0xd8(r31)
/* 8006BD10 000688F0  C0 1E 00 04 */	lfs f0, 4(r30)
/* 8006BD14 000688F4  EC 01 00 2A */	fadds f0, f1, f0
/* 8006BD18 000688F8  D0 1F 00 D8 */	stfs f0, 0xd8(r31)
/* 8006BD1C 000688FC  88 7F 22 10 */	lbz r3, 0x2210(r31)
/* 8006BD20 00068900  54 60 DF FF */	rlwinm. r0, r3, 0x1b, 0x1f, 0x1f
/* 8006BD24 00068904  41 82 00 18 */	beq lbl_8006BD3C
/* 8006BD28 00068908  38 00 00 00 */	li r0, 0
/* 8006BD2C 0006890C  50 03 2E B4 */	rlwimi r3, r0, 5, 0x1a, 0x1a
/* 8006BD30 00068910  98 7F 22 10 */	stb r3, 0x2210(r31)
/* 8006BD34 00068914  38 00 00 01 */	li r0, 1
/* 8006BD38 00068918  48 00 00 08 */	b lbl_8006BD40
lbl_8006BD3C:
/* 8006BD3C 0006891C  38 00 00 00 */	li r0, 0
lbl_8006BD40:
/* 8006BD40 00068920  2C 00 00 00 */	cmpwi r0, 0
/* 8006BD44 00068924  40 82 00 20 */	bne lbl_8006BD64
/* 8006BD48 00068928  7F E3 FB 78 */	mr r3, r31
/* 8006BD4C 0006892C  48 00 52 85 */	bl func_80070FD0
/* 8006BD50 00068930  2C 03 00 00 */	cmpwi r3, 0
/* 8006BD54 00068934  40 82 00 10 */	bne lbl_8006BD64
/* 8006BD58 00068938  88 1F 05 94 */	lbz r0, 0x594(r31)
/* 8006BD5C 0006893C  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8006BD60 00068940  41 82 00 24 */	beq lbl_8006BD84
lbl_8006BD64:
/* 8006BD64 00068944  38 7F 00 B0 */	addi r3, r31, 0xb0
/* 8006BD68 00068948  38 A3 00 00 */	addi r5, r3, 0
/* 8006BD6C 0006894C  38 9F 00 D4 */	addi r4, r31, 0xd4
/* 8006BD70 00068950  48 2D 6F E5 */	bl PSVECAdd
/* 8006BD74 00068954  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006BD78 00068958  D0 1F 00 DC */	stfs f0, 0xdc(r31)
/* 8006BD7C 0006895C  D0 1F 00 D8 */	stfs f0, 0xd8(r31)
/* 8006BD80 00068960  D0 1F 00 D4 */	stfs f0, 0xd4(r31)
lbl_8006BD84:
/* 8006BD84 00068964  38 7F 00 B0 */	addi r3, r31, 0xb0
/* 8006BD88 00068968  38 9D 00 00 */	addi r4, r29, 0
/* 8006BD8C 0006896C  38 A3 00 00 */	addi r5, r3, 0
/* 8006BD90 00068970  48 2D 6F C5 */	bl PSVECAdd
/* 8006BD94 00068974  48 00 00 44 */	b lbl_8006BDD8
lbl_8006BD98:
/* 8006BD98 00068978  38 7F 00 B0 */	addi r3, r31, 0xb0
/* 8006BD9C 0006897C  38 A3 00 00 */	addi r5, r3, 0
/* 8006BDA0 00068980  38 81 00 40 */	addi r4, r1, 0x40
/* 8006BDA4 00068984  48 2D 6F B1 */	bl PSVECAdd
/* 8006BDA8 00068988  C0 3F 00 B0 */	lfs f1, 0xb0(r31)
/* 8006BDAC 0006898C  38 7F 00 B0 */	addi r3, r31, 0xb0
/* 8006BDB0 00068990  C0 1E 00 00 */	lfs f0, 0(r30)
/* 8006BDB4 00068994  38 9D 00 00 */	addi r4, r29, 0
/* 8006BDB8 00068998  38 A3 00 00 */	addi r5, r3, 0
/* 8006BDBC 0006899C  EC 01 00 2A */	fadds f0, f1, f0
/* 8006BDC0 000689A0  D0 1F 00 B0 */	stfs f0, 0xb0(r31)
/* 8006BDC4 000689A4  C0 3F 00 B4 */	lfs f1, 0xb4(r31)
/* 8006BDC8 000689A8  C0 1E 00 04 */	lfs f0, 4(r30)
/* 8006BDCC 000689AC  EC 01 00 2A */	fadds f0, f1, f0
/* 8006BDD0 000689B0  D0 1F 00 B4 */	stfs f0, 0xb4(r31)
/* 8006BDD4 000689B4  48 2D 6F 81 */	bl PSVECAdd
lbl_8006BDD8:
/* 8006BDD8 000689B8  38 7C 00 00 */	addi r3, r28, 0
/* 8006BDDC 000689BC  38 81 00 4C */	addi r4, r1, 0x4c
/* 8006BDE0 000689C0  48 00 FB 45 */	bl func_8007B924
/* 8006BDE4 000689C4  48 00 00 14 */	b lbl_8006BDF8
lbl_8006BDE8:
/* 8006BDE8 000689C8  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006BDEC 000689CC  D0 01 00 54 */	stfs f0, 0x54(r1)
/* 8006BDF0 000689D0  D0 01 00 50 */	stfs f0, 0x50(r1)
/* 8006BDF4 000689D4  D0 01 00 4C */	stfs f0, 0x4c(r1)
lbl_8006BDF8:
/* 8006BDF8 000689D8  7F 83 E3 78 */	mr r3, r28
/* 8006BDFC 000689DC  48 00 A7 2D */	bl func_80076528
/* 8006BE00 000689E0  81 9F 21 D0 */	lwz r12, 0x21d0(r31)
/* 8006BE04 000689E4  28 0C 00 00 */	cmplwi r12, 0
/* 8006BE08 000689E8  41 82 00 10 */	beq lbl_8006BE18
/* 8006BE0C 000689EC  7D 88 03 A6 */	mtlr r12
/* 8006BE10 000689F0  38 7C 00 00 */	addi r3, r28, 0
/* 8006BE14 000689F4  4E 80 00 21 */	blrl 
lbl_8006BE18:
/* 8006BE18 000689F8  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 8006BE1C 000689FC  2C 00 00 00 */	cmpwi r0, 0
/* 8006BE20 00068A00  40 82 00 2C */	bne lbl_8006BE4C
/* 8006BE24 00068A04  80 7F 08 3C */	lwz r3, 0x83c(r31)
/* 8006BE28 00068A08  38 9F 00 B0 */	addi r4, r31, 0xb0
/* 8006BE2C 00068A0C  38 A1 00 24 */	addi r5, r1, 0x24
/* 8006BE30 00068A10  4B FE A9 91 */	bl func_800567C0
/* 8006BE34 00068A14  2C 03 00 00 */	cmpwi r3, 0
/* 8006BE38 00068A18  41 82 00 14 */	beq lbl_8006BE4C
/* 8006BE3C 00068A1C  38 7F 00 B0 */	addi r3, r31, 0xb0
/* 8006BE40 00068A20  38 A3 00 00 */	addi r5, r3, 0
/* 8006BE44 00068A24  38 81 00 24 */	addi r4, r1, 0x24
/* 8006BE48 00068A28  48 2D 6F 0D */	bl PSVECAdd
lbl_8006BE4C:
/* 8006BE4C 00068A2C  C0 3F 00 B0 */	lfs f1, 0xb0(r31)
/* 8006BE50 00068A30  7F 83 E3 78 */	mr r3, r28
/* 8006BE54 00068A34  C0 01 00 4C */	lfs f0, 0x4c(r1)
/* 8006BE58 00068A38  EC 01 00 2A */	fadds f0, f1, f0
/* 8006BE5C 00068A3C  D0 1F 00 B0 */	stfs f0, 0xb0(r31)
/* 8006BE60 00068A40  C0 3F 00 B4 */	lfs f1, 0xb4(r31)
/* 8006BE64 00068A44  C0 01 00 50 */	lfs f0, 0x50(r1)
/* 8006BE68 00068A48  EC 01 00 2A */	fadds f0, f1, f0
/* 8006BE6C 00068A4C  D0 1F 00 B4 */	stfs f0, 0xb4(r31)
/* 8006BE70 00068A50  C0 3F 00 B8 */	lfs f1, 0xb8(r31)
/* 8006BE74 00068A54  C0 01 00 54 */	lfs f0, 0x54(r1)
/* 8006BE78 00068A58  EC 01 00 2A */	fadds f0, f1, f0
/* 8006BE7C 00068A5C  D0 1F 00 B8 */	stfs f0, 0xb8(r31)
/* 8006BE80 00068A60  48 06 72 D9 */	bl func_800D3158
/* 8006BE84 00068A64  88 1F 22 25 */	lbz r0, 0x2225(r31)
/* 8006BE88 00068A68  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8006BE8C 00068A6C  41 82 00 3C */	beq lbl_8006BEC8
/* 8006BE90 00068A70  48 1B 8D 35 */	bl Stage_CalcUnkCamYBounds
/* 8006BE94 00068A74  C0 1F 00 C0 */	lfs f0, 0xc0(r31)
/* 8006BE98 00068A78  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8006BE9C 00068A7C  4C 40 13 82 */	cror 2, 0, 2
/* 8006BEA0 00068A80  40 82 00 88 */	bne lbl_8006BF28
/* 8006BEA4 00068A84  48 1B 8D 21 */	bl Stage_CalcUnkCamYBounds
/* 8006BEA8 00068A88  C0 1F 00 B4 */	lfs f0, 0xb4(r31)
/* 8006BEAC 00068A8C  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8006BEB0 00068A90  40 81 00 78 */	ble lbl_8006BF28
/* 8006BEB4 00068A94  88 1F 22 25 */	lbz r0, 0x2225(r31)
/* 8006BEB8 00068A98  38 60 00 00 */	li r3, 0
/* 8006BEBC 00068A9C  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 8006BEC0 00068AA0  98 1F 22 25 */	stb r0, 0x2225(r31)
/* 8006BEC4 00068AA4  48 00 00 64 */	b lbl_8006BF28
lbl_8006BEC8:
/* 8006BEC8 00068AA8  88 1F 22 2A */	lbz r0, 0x222a(r31)
/* 8006BECC 00068AAC  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 8006BED0 00068AB0  40 82 00 58 */	bne lbl_8006BF28
/* 8006BED4 00068AB4  88 1F 22 28 */	lbz r0, 0x2228(r31)
/* 8006BED8 00068AB8  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 8006BEDC 00068ABC  40 82 00 4C */	bne lbl_8006BF28
/* 8006BEE0 00068AC0  48 1B 8C B9 */	bl Stage_CalcUnkCamY
/* 8006BEE4 00068AC4  C0 1F 00 C0 */	lfs f0, 0xc0(r31)
/* 8006BEE8 00068AC8  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8006BEEC 00068ACC  4C 41 13 82 */	cror 2, 1, 2
/* 8006BEF0 00068AD0  40 82 00 38 */	bne lbl_8006BF28
/* 8006BEF4 00068AD4  48 1B 8C A5 */	bl Stage_CalcUnkCamY
/* 8006BEF8 00068AD8  C0 1F 00 B4 */	lfs f0, 0xb4(r31)
/* 8006BEFC 00068ADC  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8006BF00 00068AE0  40 80 00 28 */	bge lbl_8006BF28
/* 8006BF04 00068AE4  38 7F 00 00 */	addi r3, r31, 0
/* 8006BF08 00068AE8  38 80 00 60 */	li r4, 0x60
/* 8006BF0C 00068AEC  38 A0 00 7F */	li r5, 0x7f
/* 8006BF10 00068AF0  38 C0 00 40 */	li r6, 0x40
/* 8006BF14 00068AF4  48 01 C2 35 */	bl func_80088148
/* 8006BF18 00068AF8  88 1F 22 25 */	lbz r0, 0x2225(r31)
/* 8006BF1C 00068AFC  38 60 00 01 */	li r3, 1
/* 8006BF20 00068B00  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 8006BF24 00068B04  98 1F 22 25 */	stb r0, 0x2225(r31)
lbl_8006BF28:
/* 8006BF28 00068B08  C0 3F 18 A4 */	lfs f1, 0x18a4(r31)
/* 8006BF2C 00068B0C  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006BF30 00068B10  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8006BF34 00068B14  41 82 00 28 */	beq lbl_8006BF5C
/* 8006BF38 00068B18  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 8006BF3C 00068B1C  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 8006BF40 00068B20  40 82 00 1C */	bne lbl_8006BF5C
/* 8006BF44 00068B24  C0 3F 00 B0 */	lfs f1, 0xb0(r31)
/* 8006BF48 00068B28  48 2B 63 11 */	bl func_80322258
/* 8006BF4C 00068B2C  2C 03 00 00 */	cmpwi r3, 0
/* 8006BF50 00068B30  40 82 00 0C */	bne lbl_8006BF5C
/* 8006BF54 00068B34  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006BF58 00068B38  D0 1F 18 A4 */	stfs f0, 0x18a4(r31)
lbl_8006BF5C:
/* 8006BF5C 00068B3C  7F 83 E3 78 */	mr r3, r28
/* 8006BF60 00068B40  48 00 EF C9 */	bl func_8007AF28
/* 8006BF64 00068B44  80 0D 93 68 */	lwz r0, lbl_804D4A08(r13)
/* 8006BF68 00068B48  2C 00 00 03 */	cmpwi r0, 3
/* 8006BF6C 00068B4C  41 80 01 68 */	blt lbl_8006C0D4
/* 8006BF70 00068B50  C0 1F 00 B0 */	lfs f0, 0xb0(r31)
/* 8006BF74 00068B54  3C 00 7F 80 */	lis r0, 0x7f80
/* 8006BF78 00068B58  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 8006BF7C 00068B5C  80 81 00 18 */	lwz r4, 0x18(r1)
/* 8006BF80 00068B60  54 83 00 50 */	rlwinm r3, r4, 0, 1, 8
/* 8006BF84 00068B64  7C 03 00 00 */	cmpw r3, r0
/* 8006BF88 00068B68  41 82 00 14 */	beq lbl_8006BF9C
/* 8006BF8C 00068B6C  40 80 00 40 */	bge lbl_8006BFCC
/* 8006BF90 00068B70  2C 03 00 00 */	cmpwi r3, 0
/* 8006BF94 00068B74  41 82 00 20 */	beq lbl_8006BFB4
/* 8006BF98 00068B78  48 00 00 34 */	b lbl_8006BFCC
lbl_8006BF9C:
/* 8006BF9C 00068B7C  54 80 02 7F */	clrlwi. r0, r4, 9
/* 8006BFA0 00068B80  41 82 00 0C */	beq lbl_8006BFAC
/* 8006BFA4 00068B84  38 00 00 01 */	li r0, 1
/* 8006BFA8 00068B88  48 00 00 28 */	b lbl_8006BFD0
lbl_8006BFAC:
/* 8006BFAC 00068B8C  38 00 00 02 */	li r0, 2
/* 8006BFB0 00068B90  48 00 00 20 */	b lbl_8006BFD0
lbl_8006BFB4:
/* 8006BFB4 00068B94  54 80 02 7F */	clrlwi. r0, r4, 9
/* 8006BFB8 00068B98  41 82 00 0C */	beq lbl_8006BFC4
/* 8006BFBC 00068B9C  38 00 00 05 */	li r0, 5
/* 8006BFC0 00068BA0  48 00 00 10 */	b lbl_8006BFD0
lbl_8006BFC4:
/* 8006BFC4 00068BA4  38 00 00 03 */	li r0, 3
/* 8006BFC8 00068BA8  48 00 00 08 */	b lbl_8006BFD0
lbl_8006BFCC:
/* 8006BFCC 00068BAC  38 00 00 04 */	li r0, 4
lbl_8006BFD0:
/* 8006BFD0 00068BB0  2C 00 00 01 */	cmpwi r0, 1
/* 8006BFD4 00068BB4  41 82 00 D4 */	beq lbl_8006C0A8
/* 8006BFD8 00068BB8  C0 1F 00 B4 */	lfs f0, 0xb4(r31)
/* 8006BFDC 00068BBC  3C 00 7F 80 */	lis r0, 0x7f80
/* 8006BFE0 00068BC0  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 8006BFE4 00068BC4  80 81 00 14 */	lwz r4, 0x14(r1)
/* 8006BFE8 00068BC8  54 83 00 50 */	rlwinm r3, r4, 0, 1, 8
/* 8006BFEC 00068BCC  7C 03 00 00 */	cmpw r3, r0
/* 8006BFF0 00068BD0  41 82 00 14 */	beq lbl_8006C004
/* 8006BFF4 00068BD4  40 80 00 40 */	bge lbl_8006C034
/* 8006BFF8 00068BD8  2C 03 00 00 */	cmpwi r3, 0
/* 8006BFFC 00068BDC  41 82 00 20 */	beq lbl_8006C01C
/* 8006C000 00068BE0  48 00 00 34 */	b lbl_8006C034
lbl_8006C004:
/* 8006C004 00068BE4  54 80 02 7F */	clrlwi. r0, r4, 9
/* 8006C008 00068BE8  41 82 00 0C */	beq lbl_8006C014
/* 8006C00C 00068BEC  38 00 00 01 */	li r0, 1
/* 8006C010 00068BF0  48 00 00 28 */	b lbl_8006C038
lbl_8006C014:
/* 8006C014 00068BF4  38 00 00 02 */	li r0, 2
/* 8006C018 00068BF8  48 00 00 20 */	b lbl_8006C038
lbl_8006C01C:
/* 8006C01C 00068BFC  54 80 02 7F */	clrlwi. r0, r4, 9
/* 8006C020 00068C00  41 82 00 0C */	beq lbl_8006C02C
/* 8006C024 00068C04  38 00 00 05 */	li r0, 5
/* 8006C028 00068C08  48 00 00 10 */	b lbl_8006C038
lbl_8006C02C:
/* 8006C02C 00068C0C  38 00 00 03 */	li r0, 3
/* 8006C030 00068C10  48 00 00 08 */	b lbl_8006C038
lbl_8006C034:
/* 8006C034 00068C14  38 00 00 04 */	li r0, 4
lbl_8006C038:
/* 8006C038 00068C18  2C 00 00 01 */	cmpwi r0, 1
/* 8006C03C 00068C1C  41 82 00 6C */	beq lbl_8006C0A8
/* 8006C040 00068C20  C0 1F 00 B8 */	lfs f0, 0xb8(r31)
/* 8006C044 00068C24  3C 00 7F 80 */	lis r0, 0x7f80
/* 8006C048 00068C28  D0 01 00 10 */	stfs f0, 0x10(r1)
/* 8006C04C 00068C2C  80 81 00 10 */	lwz r4, 0x10(r1)
/* 8006C050 00068C30  54 83 00 50 */	rlwinm r3, r4, 0, 1, 8
/* 8006C054 00068C34  7C 03 00 00 */	cmpw r3, r0
/* 8006C058 00068C38  41 82 00 14 */	beq lbl_8006C06C
/* 8006C05C 00068C3C  40 80 00 40 */	bge lbl_8006C09C
/* 8006C060 00068C40  2C 03 00 00 */	cmpwi r3, 0
/* 8006C064 00068C44  41 82 00 20 */	beq lbl_8006C084
/* 8006C068 00068C48  48 00 00 34 */	b lbl_8006C09C
lbl_8006C06C:
/* 8006C06C 00068C4C  54 80 02 7F */	clrlwi. r0, r4, 9
/* 8006C070 00068C50  41 82 00 0C */	beq lbl_8006C07C
/* 8006C074 00068C54  38 00 00 01 */	li r0, 1
/* 8006C078 00068C58  48 00 00 28 */	b lbl_8006C0A0
lbl_8006C07C:
/* 8006C07C 00068C5C  38 00 00 02 */	li r0, 2
/* 8006C080 00068C60  48 00 00 20 */	b lbl_8006C0A0
lbl_8006C084:
/* 8006C084 00068C64  54 80 02 7F */	clrlwi. r0, r4, 9
/* 8006C088 00068C68  41 82 00 0C */	beq lbl_8006C094
/* 8006C08C 00068C6C  38 00 00 05 */	li r0, 5
/* 8006C090 00068C70  48 00 00 10 */	b lbl_8006C0A0
lbl_8006C094:
/* 8006C094 00068C74  38 00 00 03 */	li r0, 3
/* 8006C098 00068C78  48 00 00 08 */	b lbl_8006C0A0
lbl_8006C09C:
/* 8006C09C 00068C7C  38 00 00 04 */	li r0, 4
lbl_8006C0A0:
/* 8006C0A0 00068C80  2C 00 00 01 */	cmpwi r0, 1
/* 8006C0A4 00068C84  40 82 00 30 */	bne lbl_8006C0D4
lbl_8006C0A8:
/* 8006C0A8 00068C88  3C 60 80 3C */	lis r3, lbl_803C05AC@ha
/* 8006C0AC 00068C8C  C0 3F 00 B0 */	lfs f1, 0xb0(r31)
/* 8006C0B0 00068C90  C0 5F 00 B4 */	lfs f2, 0xb4(r31)
/* 8006C0B4 00068C94  38 63 05 AC */	addi r3, r3, lbl_803C05AC@l
/* 8006C0B8 00068C98  4C C6 32 42 */	crset 6
/* 8006C0BC 00068C9C  48 2D 95 ED */	bl OSReport
/* 8006C0C0 00068CA0  3C 60 80 3C */	lis r3, lbl_803C057C@ha
/* 8006C0C4 00068CA4  38 63 05 7C */	addi r3, r3, lbl_803C057C@l
/* 8006C0C8 00068CA8  38 80 09 D5 */	li r4, 0x9d5
/* 8006C0CC 00068CAC  38 AD 83 70 */	addi r5, r13, lbl_804D3A10
/* 8006C0D0 00068CB0  48 31 C1 51 */	bl __assert
lbl_8006C0D4:
/* 8006C0D4 00068CB4  BB 41 00 68 */	lmw r26, 0x68(r1)
/* 8006C0D8 00068CB8  80 01 00 94 */	lwz r0, 0x94(r1)
/* 8006C0DC 00068CBC  CB E1 00 88 */	lfd f31, 0x88(r1)
/* 8006C0E0 00068CC0  CB C1 00 80 */	lfd f30, 0x80(r1)
/* 8006C0E4 00068CC4  38 21 00 90 */	addi r1, r1, 0x90
/* 8006C0E8 00068CC8  7C 08 03 A6 */	mtlr r0
/* 8006C0EC 00068CCC  4E 80 00 20 */	blr  
}


asm void func_8006C0F0()
{
	nofralloc 
/* 8006C0F0 00068CD0  7C 08 02 A6 */	mflr r0
/* 8006C0F4 00068CD4  90 01 00 04 */	stw r0, 4(r1)
/* 8006C0F8 00068CD8  94 21 FF 58 */	stwu r1, -0xa8(r1)
/* 8006C0FC 00068CDC  93 E1 00 A4 */	stw r31, 0xa4(r1)
/* 8006C100 00068CE0  93 C1 00 A0 */	stw r30, 0xa0(r1)
/* 8006C104 00068CE4  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8006C108 00068CE8  C0 22 88 70 */	lfs f1, lbl_804D8250(r2)
/* 8006C10C 00068CEC  C0 04 00 3C */	lfs f0, 0x3c(r4)
/* 8006C110 00068CF0  7C 9F 23 78 */	mr r31, r4
/* 8006C114 00068CF4  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8006C118 00068CF8  41 82 01 4C */	beq lbl_8006C264
/* 8006C11C 00068CFC  80 03 00 28 */	lwz r0, 0x28(r3)
/* 8006C120 00068D00  28 00 00 00 */	cmplwi r0, 0
/* 8006C124 00068D04  7C 1E 03 78 */	mr r30, r0
/* 8006C128 00068D08  41 82 00 44 */	beq lbl_8006C16C
/* 8006C12C 00068D0C  40 82 00 14 */	bne lbl_8006C140
/* 8006C130 00068D10  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 8006C134 00068D14  38 80 02 34 */	li r4, 0x234
/* 8006C138 00068D18  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 8006C13C 00068D1C  48 31 C0 E5 */	bl __assert
lbl_8006C140:
/* 8006C140 00068D20  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 8006C144 00068D24  38 60 00 00 */	li r3, 0
/* 8006C148 00068D28  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8006C14C 00068D2C  40 82 00 10 */	bne lbl_8006C15C
/* 8006C150 00068D30  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8006C154 00068D34  41 82 00 08 */	beq lbl_8006C15C
/* 8006C158 00068D38  38 60 00 01 */	li r3, 1
lbl_8006C15C:
/* 8006C15C 00068D3C  2C 03 00 00 */	cmpwi r3, 0
/* 8006C160 00068D40  41 82 00 0C */	beq lbl_8006C16C
/* 8006C164 00068D44  7F C3 F3 78 */	mr r3, r30
/* 8006C168 00068D48  48 30 6F 11 */	bl HSD_JObjSetupMatrixSub
lbl_8006C16C:
/* 8006C16C 00068D4C  28 1E 00 00 */	cmplwi r30, 0
/* 8006C170 00068D50  40 82 00 14 */	bne lbl_8006C184
/* 8006C174 00068D54  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 8006C178 00068D58  38 80 04 78 */	li r4, 0x478
/* 8006C17C 00068D5C  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 8006C180 00068D60  48 31 C0 A1 */	bl __assert
lbl_8006C184:
/* 8006C184 00068D64  7F C3 F3 78 */	mr r3, r30
/* 8006C188 00068D68  4B F9 BB E1 */	bl HSD_JObjGetMtxPtr
/* 8006C18C 00068D6C  38 7E 00 44 */	addi r3, r30, 0x44
/* 8006C190 00068D70  38 81 00 70 */	addi r4, r1, 0x70
/* 8006C194 00068D74  48 30 D1 7D */	bl func_80379310
/* 8006C198 00068D78  28 1E 00 00 */	cmplwi r30, 0
/* 8006C19C 00068D7C  40 82 00 14 */	bne lbl_8006C1B0
/* 8006C1A0 00068D80  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 8006C1A4 00068D84  38 80 03 37 */	li r4, 0x337
/* 8006C1A8 00068D88  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 8006C1AC 00068D8C  48 31 C0 75 */	bl __assert
lbl_8006C1B0:
/* 8006C1B0 00068D90  80 9E 00 2C */	lwz r4, 0x2c(r30)
/* 8006C1B4 00068D94  7F E3 FB 78 */	mr r3, r31
/* 8006C1B8 00068D98  80 1E 00 30 */	lwz r0, 0x30(r30)
/* 8006C1BC 00068D9C  90 81 00 34 */	stw r4, 0x34(r1)
/* 8006C1C0 00068DA0  90 01 00 38 */	stw r0, 0x38(r1)
/* 8006C1C4 00068DA4  80 1E 00 34 */	lwz r0, 0x34(r30)
/* 8006C1C8 00068DA8  90 01 00 3C */	stw r0, 0x3c(r1)
/* 8006C1CC 00068DAC  48 01 34 C9 */	bl func_8007F694
/* 8006C1D0 00068DB0  28 1E 00 00 */	cmplwi r30, 0
/* 8006C1D4 00068DB4  D0 21 00 34 */	stfs f1, 0x34(r1)
/* 8006C1D8 00068DB8  40 82 00 14 */	bne lbl_8006C1EC
/* 8006C1DC 00068DBC  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 8006C1E0 00068DC0  38 80 02 BB */	li r4, 0x2bb
/* 8006C1E4 00068DC4  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 8006C1E8 00068DC8  48 31 C0 39 */	bl __assert
lbl_8006C1EC:
/* 8006C1EC 00068DCC  80 7E 00 1C */	lwz r3, 0x1c(r30)
/* 8006C1F0 00068DD0  28 1E 00 00 */	cmplwi r30, 0
/* 8006C1F4 00068DD4  80 1E 00 20 */	lwz r0, 0x20(r30)
/* 8006C1F8 00068DD8  90 61 00 18 */	stw r3, 0x18(r1)
/* 8006C1FC 00068DDC  90 01 00 1C */	stw r0, 0x1c(r1)
/* 8006C200 00068DE0  80 7E 00 24 */	lwz r3, 0x24(r30)
/* 8006C204 00068DE4  80 1E 00 28 */	lwz r0, 0x28(r30)
/* 8006C208 00068DE8  90 61 00 20 */	stw r3, 0x20(r1)
/* 8006C20C 00068DEC  90 01 00 24 */	stw r0, 0x24(r1)
/* 8006C210 00068DF0  40 82 00 14 */	bne lbl_8006C224
/* 8006C214 00068DF4  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 8006C218 00068DF8  38 80 03 D3 */	li r4, 0x3d3
/* 8006C21C 00068DFC  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 8006C220 00068E00  48 31 C0 01 */	bl __assert
lbl_8006C224:
/* 8006C224 00068E04  80 DE 00 38 */	lwz r6, 0x38(r30)
/* 8006C228 00068E08  38 61 00 40 */	addi r3, r1, 0x40
/* 8006C22C 00068E0C  80 1E 00 3C */	lwz r0, 0x3c(r30)
/* 8006C230 00068E10  38 81 00 34 */	addi r4, r1, 0x34
/* 8006C234 00068E14  38 A1 00 18 */	addi r5, r1, 0x18
/* 8006C238 00068E18  90 C1 00 28 */	stw r6, 0x28(r1)
/* 8006C23C 00068E1C  38 C1 00 28 */	addi r6, r1, 0x28
/* 8006C240 00068E20  38 E0 00 00 */	li r7, 0
/* 8006C244 00068E24  90 01 00 2C */	stw r0, 0x2c(r1)
/* 8006C248 00068E28  80 1E 00 40 */	lwz r0, 0x40(r30)
/* 8006C24C 00068E2C  90 01 00 30 */	stw r0, 0x30(r1)
/* 8006C250 00068E30  48 30 E0 01 */	bl func_8037A250
/* 8006C254 00068E34  38 61 00 40 */	addi r3, r1, 0x40
/* 8006C258 00068E38  38 81 00 70 */	addi r4, r1, 0x70
/* 8006C25C 00068E3C  38 BF 00 44 */	addi r5, r31, 0x44
/* 8006C260 00068E40  48 2D 5F A5 */	bl PSMTXConcat
lbl_8006C264:
/* 8006C264 00068E44  80 01 00 AC */	lwz r0, 0xac(r1)
/* 8006C268 00068E48  83 E1 00 A4 */	lwz r31, 0xa4(r1)
/* 8006C26C 00068E4C  83 C1 00 A0 */	lwz r30, 0xa0(r1)
/* 8006C270 00068E50  38 21 00 A8 */	addi r1, r1, 0xa8
/* 8006C274 00068E54  7C 08 03 A6 */	mtlr r0
/* 8006C278 00068E58  4E 80 00 20 */	blr  
}


asm void func_8006C27C()
{
	nofralloc 
/* 8006C27C 00068E5C  7C 08 02 A6 */	mflr r0
/* 8006C280 00068E60  90 01 00 04 */	stw r0, 4(r1)
/* 8006C284 00068E64  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8006C288 00068E68  93 E1 00 34 */	stw r31, 0x34(r1)
/* 8006C28C 00068E6C  93 C1 00 30 */	stw r30, 0x30(r1)
/* 8006C290 00068E70  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 8006C294 00068E74  7C 7D 1B 78 */	mr r29, r3
/* 8006C298 00068E78  93 81 00 28 */	stw r28, 0x28(r1)
/* 8006C29C 00068E7C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8006C2A0 00068E80  3C 60 80 3C */	lis r3, lbl_803C0530@ha
/* 8006C2A4 00068E84  3B E3 05 30 */	addi r31, r3, lbl_803C0530@l
/* 8006C2A8 00068E88  88 04 22 1F */	lbz r0, 0x221f(r4)
/* 8006C2AC 00068E8C  3B C4 00 00 */	addi r30, r4, 0
/* 8006C2B0 00068E90  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 8006C2B4 00068E94  40 82 03 20 */	bne lbl_8006C5D4
/* 8006C2B8 00068E98  80 7E 08 8C */	lwz r3, 0x88c(r30)
/* 8006C2BC 00068E9C  2C 03 00 00 */	cmpwi r3, 0
/* 8006C2C0 00068EA0  41 82 00 20 */	beq lbl_8006C2E0
/* 8006C2C4 00068EA4  38 03 FF FF */	addi r0, r3, -1
/* 8006C2C8 00068EA8  90 1E 08 8C */	stw r0, 0x88c(r30)
/* 8006C2CC 00068EAC  80 1E 08 8C */	lwz r0, 0x88c(r30)
/* 8006C2D0 00068EB0  2C 00 00 00 */	cmpwi r0, 0
/* 8006C2D4 00068EB4  40 82 00 0C */	bne lbl_8006C2E0
/* 8006C2D8 00068EB8  7F C3 F3 78 */	mr r3, r30
/* 8006C2DC 00068EBC  48 01 12 E1 */	bl func_8007D5BC
lbl_8006C2E0:
/* 8006C2E0 00068EC0  88 1E 22 23 */	lbz r0, 0x2223(r30)
/* 8006C2E4 00068EC4  38 60 00 00 */	li r3, 0
/* 8006C2E8 00068EC8  50 60 17 7A */	rlwimi r0, r3, 2, 0x1d, 0x1d
/* 8006C2EC 00068ECC  98 1E 22 23 */	stb r0, 0x2223(r30)
/* 8006C2F0 00068ED0  83 9D 00 28 */	lwz r28, 0x28(r29)
/* 8006C2F4 00068ED4  28 1C 00 00 */	cmplwi r28, 0
/* 8006C2F8 00068ED8  40 82 00 14 */	bne lbl_8006C30C
/* 8006C2FC 00068EDC  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 8006C300 00068EE0  38 80 03 94 */	li r4, 0x394
/* 8006C304 00068EE4  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 8006C308 00068EE8  48 31 BF 19 */	bl __assert
lbl_8006C30C:
/* 8006C30C 00068EEC  34 1E 00 B0 */	addic. r0, r30, 0xb0
/* 8006C310 00068EF0  40 82 00 14 */	bne lbl_8006C324
/* 8006C314 00068EF4  38 BF 00 20 */	addi r5, r31, 0x20
/* 8006C318 00068EF8  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 8006C31C 00068EFC  38 80 03 95 */	li r4, 0x395
/* 8006C320 00068F00  48 31 BF 01 */	bl __assert
lbl_8006C324:
/* 8006C324 00068F04  80 7E 00 B0 */	lwz r3, 0xb0(r30)
/* 8006C328 00068F08  80 1E 00 B4 */	lwz r0, 0xb4(r30)
/* 8006C32C 00068F0C  90 7C 00 38 */	stw r3, 0x38(r28)
/* 8006C330 00068F10  90 1C 00 3C */	stw r0, 0x3c(r28)
/* 8006C334 00068F14  80 1E 00 B8 */	lwz r0, 0xb8(r30)
/* 8006C338 00068F18  90 1C 00 40 */	stw r0, 0x40(r28)
/* 8006C33C 00068F1C  80 1C 00 14 */	lwz r0, 0x14(r28)
/* 8006C340 00068F20  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8006C344 00068F24  40 82 00 4C */	bne lbl_8006C390
/* 8006C348 00068F28  28 1C 00 00 */	cmplwi r28, 0
/* 8006C34C 00068F2C  41 82 00 44 */	beq lbl_8006C390
/* 8006C350 00068F30  40 82 00 14 */	bne lbl_8006C364
/* 8006C354 00068F34  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 8006C358 00068F38  38 80 02 34 */	li r4, 0x234
/* 8006C35C 00068F3C  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 8006C360 00068F40  48 31 BE C1 */	bl __assert
lbl_8006C364:
/* 8006C364 00068F44  80 9C 00 14 */	lwz r4, 0x14(r28)
/* 8006C368 00068F48  38 60 00 00 */	li r3, 0
/* 8006C36C 00068F4C  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8006C370 00068F50  40 82 00 10 */	bne lbl_8006C380
/* 8006C374 00068F54  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8006C378 00068F58  41 82 00 08 */	beq lbl_8006C380
/* 8006C37C 00068F5C  38 60 00 01 */	li r3, 1
lbl_8006C380:
/* 8006C380 00068F60  2C 03 00 00 */	cmpwi r3, 0
/* 8006C384 00068F64  40 82 00 0C */	bne lbl_8006C390
/* 8006C388 00068F68  7F 83 E3 78 */	mr r3, r28
/* 8006C38C 00068F6C  48 30 6F 5D */	bl HSD_JObjSetMtxDirtySub
lbl_8006C390:
/* 8006C390 00068F70  81 9E 21 A8 */	lwz r12, 0x21a8(r30)
/* 8006C394 00068F74  28 0C 00 00 */	cmplwi r12, 0
/* 8006C398 00068F78  41 82 00 18 */	beq lbl_8006C3B0
/* 8006C39C 00068F7C  7D 88 03 A6 */	mtlr r12
/* 8006C3A0 00068F80  38 7D 00 00 */	addi r3, r29, 0
/* 8006C3A4 00068F84  4E 80 00 21 */	blrl 
/* 8006C3A8 00068F88  7F A3 EB 78 */	mr r3, r29
/* 8006C3AC 00068F8C  48 08 59 79 */	bl func_800F1D24
lbl_8006C3B0:
/* 8006C3B0 00068F90  80 1E 00 E0 */	lwz r0, 0xe0(r30)
/* 8006C3B4 00068F94  2C 00 00 00 */	cmpwi r0, 0
/* 8006C3B8 00068F98  40 82 00 14 */	bne lbl_8006C3CC
/* 8006C3BC 00068F9C  88 9E 22 1F */	lbz r4, 0x221f(r30)
/* 8006C3C0 00068FA0  88 7E 00 0C */	lbz r3, 0xc(r30)
/* 8006C3C4 00068FA4  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 8006C3C8 00068FA8  4B FD 4E B9 */	bl func_80041280
lbl_8006C3CC:
/* 8006C3CC 00068FAC  80 0D 93 68 */	lwz r0, lbl_804D4A08(r13)
/* 8006C3D0 00068FB0  2C 00 00 03 */	cmpwi r0, 3
/* 8006C3D4 00068FB4  41 80 01 60 */	blt lbl_8006C534
/* 8006C3D8 00068FB8  C0 1E 00 B0 */	lfs f0, 0xb0(r30)
/* 8006C3DC 00068FBC  3C 00 7F 80 */	lis r0, 0x7f80
/* 8006C3E0 00068FC0  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 8006C3E4 00068FC4  80 81 00 20 */	lwz r4, 0x20(r1)
/* 8006C3E8 00068FC8  54 83 00 50 */	rlwinm r3, r4, 0, 1, 8
/* 8006C3EC 00068FCC  7C 03 00 00 */	cmpw r3, r0
/* 8006C3F0 00068FD0  41 82 00 14 */	beq lbl_8006C404
/* 8006C3F4 00068FD4  40 80 00 40 */	bge lbl_8006C434
/* 8006C3F8 00068FD8  2C 03 00 00 */	cmpwi r3, 0
/* 8006C3FC 00068FDC  41 82 00 20 */	beq lbl_8006C41C
/* 8006C400 00068FE0  48 00 00 34 */	b lbl_8006C434
lbl_8006C404:
/* 8006C404 00068FE4  54 80 02 7F */	clrlwi. r0, r4, 9
/* 8006C408 00068FE8  41 82 00 0C */	beq lbl_8006C414
/* 8006C40C 00068FEC  38 00 00 01 */	li r0, 1
/* 8006C410 00068FF0  48 00 00 28 */	b lbl_8006C438
lbl_8006C414:
/* 8006C414 00068FF4  38 00 00 02 */	li r0, 2
/* 8006C418 00068FF8  48 00 00 20 */	b lbl_8006C438
lbl_8006C41C:
/* 8006C41C 00068FFC  54 80 02 7F */	clrlwi. r0, r4, 9
/* 8006C420 00069000  41 82 00 0C */	beq lbl_8006C42C
/* 8006C424 00069004  38 00 00 05 */	li r0, 5
/* 8006C428 00069008  48 00 00 10 */	b lbl_8006C438
lbl_8006C42C:
/* 8006C42C 0006900C  38 00 00 03 */	li r0, 3
/* 8006C430 00069010  48 00 00 08 */	b lbl_8006C438
lbl_8006C434:
/* 8006C434 00069014  38 00 00 04 */	li r0, 4
lbl_8006C438:
/* 8006C438 00069018  2C 00 00 01 */	cmpwi r0, 1
/* 8006C43C 0006901C  41 82 00 D4 */	beq lbl_8006C510
/* 8006C440 00069020  C0 1E 00 B4 */	lfs f0, 0xb4(r30)
/* 8006C444 00069024  3C 00 7F 80 */	lis r0, 0x7f80
/* 8006C448 00069028  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 8006C44C 0006902C  80 81 00 1C */	lwz r4, 0x1c(r1)
/* 8006C450 00069030  54 83 00 50 */	rlwinm r3, r4, 0, 1, 8
/* 8006C454 00069034  7C 03 00 00 */	cmpw r3, r0
/* 8006C458 00069038  41 82 00 14 */	beq lbl_8006C46C
/* 8006C45C 0006903C  40 80 00 40 */	bge lbl_8006C49C
/* 8006C460 00069040  2C 03 00 00 */	cmpwi r3, 0
/* 8006C464 00069044  41 82 00 20 */	beq lbl_8006C484
/* 8006C468 00069048  48 00 00 34 */	b lbl_8006C49C
lbl_8006C46C:
/* 8006C46C 0006904C  54 80 02 7F */	clrlwi. r0, r4, 9
/* 8006C470 00069050  41 82 00 0C */	beq lbl_8006C47C
/* 8006C474 00069054  38 00 00 01 */	li r0, 1
/* 8006C478 00069058  48 00 00 28 */	b lbl_8006C4A0
lbl_8006C47C:
/* 8006C47C 0006905C  38 00 00 02 */	li r0, 2
/* 8006C480 00069060  48 00 00 20 */	b lbl_8006C4A0
lbl_8006C484:
/* 8006C484 00069064  54 80 02 7F */	clrlwi. r0, r4, 9
/* 8006C488 00069068  41 82 00 0C */	beq lbl_8006C494
/* 8006C48C 0006906C  38 00 00 05 */	li r0, 5
/* 8006C490 00069070  48 00 00 10 */	b lbl_8006C4A0
lbl_8006C494:
/* 8006C494 00069074  38 00 00 03 */	li r0, 3
/* 8006C498 00069078  48 00 00 08 */	b lbl_8006C4A0
lbl_8006C49C:
/* 8006C49C 0006907C  38 00 00 04 */	li r0, 4
lbl_8006C4A0:
/* 8006C4A0 00069080  2C 00 00 01 */	cmpwi r0, 1
/* 8006C4A4 00069084  41 82 00 6C */	beq lbl_8006C510
/* 8006C4A8 00069088  C0 1E 00 B8 */	lfs f0, 0xb8(r30)
/* 8006C4AC 0006908C  3C 00 7F 80 */	lis r0, 0x7f80
/* 8006C4B0 00069090  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 8006C4B4 00069094  80 81 00 18 */	lwz r4, 0x18(r1)
/* 8006C4B8 00069098  54 83 00 50 */	rlwinm r3, r4, 0, 1, 8
/* 8006C4BC 0006909C  7C 03 00 00 */	cmpw r3, r0
/* 8006C4C0 000690A0  41 82 00 14 */	beq lbl_8006C4D4
/* 8006C4C4 000690A4  40 80 00 40 */	bge lbl_8006C504
/* 8006C4C8 000690A8  2C 03 00 00 */	cmpwi r3, 0
/* 8006C4CC 000690AC  41 82 00 20 */	beq lbl_8006C4EC
/* 8006C4D0 000690B0  48 00 00 34 */	b lbl_8006C504
lbl_8006C4D4:
/* 8006C4D4 000690B4  54 80 02 7F */	clrlwi. r0, r4, 9
/* 8006C4D8 000690B8  41 82 00 0C */	beq lbl_8006C4E4
/* 8006C4DC 000690BC  38 00 00 01 */	li r0, 1
/* 8006C4E0 000690C0  48 00 00 28 */	b lbl_8006C508
lbl_8006C4E4:
/* 8006C4E4 000690C4  38 00 00 02 */	li r0, 2
/* 8006C4E8 000690C8  48 00 00 20 */	b lbl_8006C508
lbl_8006C4EC:
/* 8006C4EC 000690CC  54 80 02 7F */	clrlwi. r0, r4, 9
/* 8006C4F0 000690D0  41 82 00 0C */	beq lbl_8006C4FC
/* 8006C4F4 000690D4  38 00 00 05 */	li r0, 5
/* 8006C4F8 000690D8  48 00 00 10 */	b lbl_8006C508
lbl_8006C4FC:
/* 8006C4FC 000690DC  38 00 00 03 */	li r0, 3
/* 8006C500 000690E0  48 00 00 08 */	b lbl_8006C508
lbl_8006C504:
/* 8006C504 000690E4  38 00 00 04 */	li r0, 4
lbl_8006C508:
/* 8006C508 000690E8  2C 00 00 01 */	cmpwi r0, 1
/* 8006C50C 000690EC  40 82 00 28 */	bne lbl_8006C534
lbl_8006C510:
/* 8006C510 000690F0  C0 3E 00 B0 */	lfs f1, 0xb0(r30)
/* 8006C514 000690F4  38 7F 00 B0 */	addi r3, r31, 0xb0
/* 8006C518 000690F8  C0 5E 00 B4 */	lfs f2, 0xb4(r30)
/* 8006C51C 000690FC  4C C6 32 42 */	crset 6
/* 8006C520 00069100  48 2D 91 89 */	bl OSReport
/* 8006C524 00069104  38 7F 00 4C */	addi r3, r31, 0x4c
/* 8006C528 00069108  38 80 0A 1E */	li r4, 0xa1e
/* 8006C52C 0006910C  38 AD 83 70 */	addi r5, r13, lbl_804D3A10
/* 8006C530 00069110  48 31 BC F1 */	bl __assert
lbl_8006C534:
/* 8006C534 00069114  83 9D 00 28 */	lwz r28, 0x28(r29)
/* 8006C538 00069118  28 1C 00 00 */	cmplwi r28, 0
/* 8006C53C 0006911C  40 82 00 14 */	bne lbl_8006C550
/* 8006C540 00069120  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 8006C544 00069124  38 80 03 94 */	li r4, 0x394
/* 8006C548 00069128  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 8006C54C 0006912C  48 31 BC D5 */	bl __assert
lbl_8006C550:
/* 8006C550 00069130  34 1E 00 B0 */	addic. r0, r30, 0xb0
/* 8006C554 00069134  40 82 00 14 */	bne lbl_8006C568
/* 8006C558 00069138  38 BF 00 20 */	addi r5, r31, 0x20
/* 8006C55C 0006913C  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 8006C560 00069140  38 80 03 95 */	li r4, 0x395
/* 8006C564 00069144  48 31 BC BD */	bl __assert
lbl_8006C568:
/* 8006C568 00069148  80 7E 00 B0 */	lwz r3, 0xb0(r30)
/* 8006C56C 0006914C  80 1E 00 B4 */	lwz r0, 0xb4(r30)
/* 8006C570 00069150  90 7C 00 38 */	stw r3, 0x38(r28)
/* 8006C574 00069154  90 1C 00 3C */	stw r0, 0x3c(r28)
/* 8006C578 00069158  80 1E 00 B8 */	lwz r0, 0xb8(r30)
/* 8006C57C 0006915C  90 1C 00 40 */	stw r0, 0x40(r28)
/* 8006C580 00069160  80 1C 00 14 */	lwz r0, 0x14(r28)
/* 8006C584 00069164  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8006C588 00069168  40 82 00 4C */	bne lbl_8006C5D4
/* 8006C58C 0006916C  28 1C 00 00 */	cmplwi r28, 0
/* 8006C590 00069170  41 82 00 44 */	beq lbl_8006C5D4
/* 8006C594 00069174  40 82 00 14 */	bne lbl_8006C5A8
/* 8006C598 00069178  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 8006C59C 0006917C  38 80 02 34 */	li r4, 0x234
/* 8006C5A0 00069180  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 8006C5A4 00069184  48 31 BC 7D */	bl __assert
lbl_8006C5A8:
/* 8006C5A8 00069188  80 9C 00 14 */	lwz r4, 0x14(r28)
/* 8006C5AC 0006918C  38 60 00 00 */	li r3, 0
/* 8006C5B0 00069190  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8006C5B4 00069194  40 82 00 10 */	bne lbl_8006C5C4
/* 8006C5B8 00069198  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8006C5BC 0006919C  41 82 00 08 */	beq lbl_8006C5C4
/* 8006C5C0 000691A0  38 60 00 01 */	li r3, 1
lbl_8006C5C4:
/* 8006C5C4 000691A4  2C 03 00 00 */	cmpwi r3, 0
/* 8006C5C8 000691A8  40 82 00 0C */	bne lbl_8006C5D4
/* 8006C5CC 000691AC  7F 83 E3 78 */	mr r3, r28
/* 8006C5D0 000691B0  48 30 6D 19 */	bl HSD_JObjSetMtxDirtySub
lbl_8006C5D4:
/* 8006C5D4 000691B4  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8006C5D8 000691B8  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 8006C5DC 000691BC  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 8006C5E0 000691C0  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 8006C5E4 000691C4  83 81 00 28 */	lwz r28, 0x28(r1)
/* 8006C5E8 000691C8  38 21 00 38 */	addi r1, r1, 0x38
/* 8006C5EC 000691CC  7C 08 03 A6 */	mtlr r0
/* 8006C5F0 000691D0  4E 80 00 20 */	blr 
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


asm void func_8006C80C()
{
	nofralloc 
/* 8006C80C 000693EC  7C 08 02 A6 */	mflr r0
/* 8006C810 000693F0  90 01 00 04 */	stw r0, 4(r1)
/* 8006C814 000693F4  94 21 FF 30 */	stwu r1, -0xd0(r1)
/* 8006C818 000693F8  93 E1 00 CC */	stw r31, 0xcc(r1)
/* 8006C81C 000693FC  93 C1 00 C8 */	stw r30, 0xc8(r1)
/* 8006C820 00069400  93 A1 00 C4 */	stw r29, 0xc4(r1)
/* 8006C824 00069404  7C 7D 1B 78 */	mr r29, r3
/* 8006C828 00069408  93 81 00 C0 */	stw r28, 0xc0(r1)
/* 8006C82C 0006940C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8006C830 00069410  88 1F 22 1F */	lbz r0, 0x221f(r31)
/* 8006C834 00069414  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 8006C838 00069418  40 82 02 04 */	bne lbl_8006CA3C
/* 8006C83C 0006941C  38 7D 00 00 */	addi r3, r29, 0
/* 8006C840 00069420  38 9F 06 0C */	addi r4, r31, 0x60c
/* 8006C844 00069424  4B FF AD E1 */	bl func_80067624
/* 8006C848 00069428  83 DD 00 2C */	lwz r30, 0x2c(r29)
/* 8006C84C 0006942C  C0 22 88 70 */	lfs f1, lbl_804D8250(r2)
/* 8006C850 00069430  C0 1E 00 3C */	lfs f0, 0x3c(r30)
/* 8006C854 00069434  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8006C858 00069438  41 82 01 48 */	beq lbl_8006C9A0
/* 8006C85C 0006943C  83 9D 00 28 */	lwz r28, 0x28(r29)
/* 8006C860 00069440  28 1C 00 00 */	cmplwi r28, 0
/* 8006C864 00069444  41 82 00 44 */	beq lbl_8006C8A8
/* 8006C868 00069448  40 82 00 14 */	bne lbl_8006C87C
/* 8006C86C 0006944C  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 8006C870 00069450  38 80 02 34 */	li r4, 0x234
/* 8006C874 00069454  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 8006C878 00069458  48 31 B9 A9 */	bl __assert
lbl_8006C87C:
/* 8006C87C 0006945C  80 9C 00 14 */	lwz r4, 0x14(r28)
/* 8006C880 00069460  38 60 00 00 */	li r3, 0
/* 8006C884 00069464  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8006C888 00069468  40 82 00 10 */	bne lbl_8006C898
/* 8006C88C 0006946C  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8006C890 00069470  41 82 00 08 */	beq lbl_8006C898
/* 8006C894 00069474  38 60 00 01 */	li r3, 1
lbl_8006C898:
/* 8006C898 00069478  2C 03 00 00 */	cmpwi r3, 0
/* 8006C89C 0006947C  41 82 00 0C */	beq lbl_8006C8A8
/* 8006C8A0 00069480  7F 83 E3 78 */	mr r3, r28
/* 8006C8A4 00069484  48 30 67 D5 */	bl HSD_JObjSetupMatrixSub
lbl_8006C8A8:
/* 8006C8A8 00069488  28 1C 00 00 */	cmplwi r28, 0
/* 8006C8AC 0006948C  40 82 00 14 */	bne lbl_8006C8C0
/* 8006C8B0 00069490  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 8006C8B4 00069494  38 80 04 78 */	li r4, 0x478
/* 8006C8B8 00069498  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 8006C8BC 0006949C  48 31 B9 65 */	bl __assert
lbl_8006C8C0:
/* 8006C8C0 000694A0  7F 83 E3 78 */	mr r3, r28
/* 8006C8C4 000694A4  4B F9 B4 A5 */	bl HSD_JObjGetMtxPtr
/* 8006C8C8 000694A8  38 7C 00 44 */	addi r3, r28, 0x44
/* 8006C8CC 000694AC  38 81 00 28 */	addi r4, r1, 0x28
/* 8006C8D0 000694B0  48 30 CA 41 */	bl func_80379310
/* 8006C8D4 000694B4  28 1C 00 00 */	cmplwi r28, 0
/* 8006C8D8 000694B8  40 82 00 14 */	bne lbl_8006C8EC
/* 8006C8DC 000694BC  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 8006C8E0 000694C0  38 80 03 37 */	li r4, 0x337
/* 8006C8E4 000694C4  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 8006C8E8 000694C8  48 31 B9 39 */	bl __assert
lbl_8006C8EC:
/* 8006C8EC 000694CC  80 9C 00 2C */	lwz r4, 0x2c(r28)
/* 8006C8F0 000694D0  7F C3 F3 78 */	mr r3, r30
/* 8006C8F4 000694D4  80 1C 00 30 */	lwz r0, 0x30(r28)
/* 8006C8F8 000694D8  90 81 00 88 */	stw r4, 0x88(r1)
/* 8006C8FC 000694DC  90 01 00 8C */	stw r0, 0x8c(r1)
/* 8006C900 000694E0  80 1C 00 34 */	lwz r0, 0x34(r28)
/* 8006C904 000694E4  90 01 00 90 */	stw r0, 0x90(r1)
/* 8006C908 000694E8  48 01 2D 8D */	bl func_8007F694
/* 8006C90C 000694EC  28 1C 00 00 */	cmplwi r28, 0
/* 8006C910 000694F0  D0 21 00 88 */	stfs f1, 0x88(r1)
/* 8006C914 000694F4  40 82 00 14 */	bne lbl_8006C928
/* 8006C918 000694F8  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 8006C91C 000694FC  38 80 02 BB */	li r4, 0x2bb
/* 8006C920 00069500  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 8006C924 00069504  48 31 B8 FD */	bl __assert
lbl_8006C928:
/* 8006C928 00069508  80 7C 00 1C */	lwz r3, 0x1c(r28)
/* 8006C92C 0006950C  28 1C 00 00 */	cmplwi r28, 0
/* 8006C930 00069510  80 1C 00 20 */	lwz r0, 0x20(r28)
/* 8006C934 00069514  90 61 00 A0 */	stw r3, 0xa0(r1)
/* 8006C938 00069518  90 01 00 A4 */	stw r0, 0xa4(r1)
/* 8006C93C 0006951C  80 7C 00 24 */	lwz r3, 0x24(r28)
/* 8006C940 00069520  80 1C 00 28 */	lwz r0, 0x28(r28)
/* 8006C944 00069524  90 61 00 A8 */	stw r3, 0xa8(r1)
/* 8006C948 00069528  90 01 00 AC */	stw r0, 0xac(r1)
/* 8006C94C 0006952C  40 82 00 14 */	bne lbl_8006C960
/* 8006C950 00069530  38 6D 83 60 */	addi r3, r13, lbl_804D3A00
/* 8006C954 00069534  38 80 03 D3 */	li r4, 0x3d3
/* 8006C958 00069538  38 AD 83 68 */	addi r5, r13, lbl_804D3A08
/* 8006C95C 0006953C  48 31 B8 C5 */	bl __assert
lbl_8006C960:
/* 8006C960 00069540  80 DC 00 38 */	lwz r6, 0x38(r28)
/* 8006C964 00069544  38 61 00 58 */	addi r3, r1, 0x58
/* 8006C968 00069548  80 1C 00 3C */	lwz r0, 0x3c(r28)
/* 8006C96C 0006954C  38 81 00 88 */	addi r4, r1, 0x88
/* 8006C970 00069550  38 A1 00 A0 */	addi r5, r1, 0xa0
/* 8006C974 00069554  90 C1 00 94 */	stw r6, 0x94(r1)
/* 8006C978 00069558  38 C1 00 94 */	addi r6, r1, 0x94
/* 8006C97C 0006955C  38 E0 00 00 */	li r7, 0
/* 8006C980 00069560  90 01 00 98 */	stw r0, 0x98(r1)
/* 8006C984 00069564  80 1C 00 40 */	lwz r0, 0x40(r28)
/* 8006C988 00069568  90 01 00 9C */	stw r0, 0x9c(r1)
/* 8006C98C 0006956C  48 30 D8 C5 */	bl func_8037A250
/* 8006C990 00069570  38 61 00 58 */	addi r3, r1, 0x58
/* 8006C994 00069574  38 81 00 28 */	addi r4, r1, 0x28
/* 8006C998 00069578  38 BE 00 44 */	addi r5, r30, 0x44
/* 8006C99C 0006957C  48 2D 58 69 */	bl PSMTXConcat
lbl_8006C9A0:
/* 8006C9A0 00069580  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 8006C9A4 00069584  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 8006C9A8 00069588  40 82 00 1C */	bne lbl_8006C9C4
/* 8006C9AC 0006958C  81 9F 21 BC */	lwz r12, 0x21bc(r31)
/* 8006C9B0 00069590  28 0C 00 00 */	cmplwi r12, 0
/* 8006C9B4 00069594  41 82 00 10 */	beq lbl_8006C9C4
/* 8006C9B8 00069598  7D 88 03 A6 */	mtlr r12
/* 8006C9BC 0006959C  38 7D 00 00 */	addi r3, r29, 0
/* 8006C9C0 000695A0  4E 80 00 21 */	blrl 
lbl_8006C9C4:
/* 8006C9C4 000695A4  7F A3 EB 78 */	mr r3, r29
/* 8006C9C8 000695A8  48 00 E4 B9 */	bl func_8007AE80
/* 8006C9CC 000695AC  7F A3 EB 78 */	mr r3, r29
/* 8006C9D0 000695B0  48 00 F8 55 */	bl func_8007C224
/* 8006C9D4 000695B4  7F A3 EB 78 */	mr r3, r29
/* 8006C9D8 000695B8  48 00 FD 05 */	bl func_8007C6DC
/* 8006C9DC 000695BC  80 7F 20 A0 */	lwz r3, 0x20a0(r31)
/* 8006C9E0 000695C0  28 03 00 00 */	cmplwi r3, 0
/* 8006C9E4 000695C4  41 82 00 08 */	beq lbl_8006C9EC
/* 8006C9E8 000695C8  48 30 3F 41 */	bl HSD_JObjAnimAll
lbl_8006C9EC:
/* 8006C9EC 000695CC  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 8006C9F0 000695D0  2C 00 00 01 */	cmpwi r0, 1
/* 8006C9F4 000695D4  40 82 00 48 */	bne lbl_8006CA3C
/* 8006C9F8 000695D8  48 1B 80 A1 */	bl Stage_GetCamBoundsBottomOffset
/* 8006C9FC 000695DC  C0 1F 00 B4 */	lfs f0, 0xb4(r31)
/* 8006CA00 000695E0  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8006CA04 000695E4  40 80 00 38 */	bge lbl_8006CA3C
/* 8006CA08 000695E8  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 8006CA0C 000695EC  48 28 EC DD */	bl func_802FB6E8
/* 8006CA10 000695F0  2C 03 00 03 */	cmpwi r3, 3
/* 8006CA14 000695F4  40 82 00 28 */	bne lbl_8006CA3C
/* 8006CA18 000695F8  38 61 00 B0 */	addi r3, r1, 0xb0
/* 8006CA1C 000695FC  48 1B 81 DD */	bl Stage_UnkSetVec3TCam_Offset
/* 8006CA20 00069600  C0 5F 00 B4 */	lfs f2, 0xb4(r31)
/* 8006CA24 00069604  C0 21 00 B4 */	lfs f1, 0xb4(r1)
/* 8006CA28 00069608  C0 1F 21 40 */	lfs f0, 0x2140(r31)
/* 8006CA2C 0006960C  EC 22 08 2A */	fadds f1, f2, f1
/* 8006CA30 00069610  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8006CA34 00069614  40 80 00 08 */	bge lbl_8006CA3C
/* 8006CA38 00069618  D0 3F 21 40 */	stfs f1, 0x2140(r31)
lbl_8006CA3C:
/* 8006CA3C 0006961C  80 01 00 D4 */	lwz r0, 0xd4(r1)
/* 8006CA40 00069620  83 E1 00 CC */	lwz r31, 0xcc(r1)
/* 8006CA44 00069624  83 C1 00 C8 */	lwz r30, 0xc8(r1)
/* 8006CA48 00069628  83 A1 00 C4 */	lwz r29, 0xc4(r1)
/* 8006CA4C 0006962C  83 81 00 C0 */	lwz r28, 0xc0(r1)
/* 8006CA50 00069630  38 21 00 D0 */	addi r1, r1, 0xd0
/* 8006CA54 00069634  7C 08 03 A6 */	mtlr r0
/* 8006CA58 00069638  4E 80 00 20 */	blr 
}

asm void func_8006CA5C()
{
	nofralloc
/* 8006CA5C 0006963C  7C 08 02 A6 */	mflr r0
/* 8006CA60 00069640  90 01 00 04 */	stw r0, 4(r1)
/* 8006CA64 00069644  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8006CA68 00069648  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8006CA6C 0006964C  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8006CA70 00069650  7C 7E 1B 78 */	mr r30, r3
/* 8006CA74 00069654  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8006CA78 00069658  88 03 22 1F */	lbz r0, 0x221f(r3)
/* 8006CA7C 0006965C  3B E3 00 00 */	addi r31, r3, 0
/* 8006CA80 00069660  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 8006CA84 00069664  40 82 00 F8 */	bne lbl_8006CB7C
/* 8006CA88 00069668  48 0F E7 3D */	bl func_8016B1C4
/* 8006CA8C 0006966C  2C 03 00 00 */	cmpwi r3, 0
/* 8006CA90 00069670  40 82 00 EC */	bne lbl_8006CB7C
/* 8006CA94 00069674  7F C3 F3 78 */	mr r3, r30
/* 8006CA98 00069678  48 00 EF 75 */	bl func_8007BA0C
/* 8006CA9C 0006967C  88 1F 22 1E */	lbz r0, 0x221e(r31)
/* 8006CAA0 00069680  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 8006CAA4 00069684  41 82 00 D8 */	beq lbl_8006CB7C
/* 8006CAA8 00069688  7F C3 F3 78 */	mr r3, r30
/* 8006CAAC 0006968C  48 00 BF 81 */	bl func_80078A2C
/* 8006CAB0 00069690  80 1F 1A 58 */	lwz r0, 0x1a58(r31)
/* 8006CAB4 00069694  28 00 00 00 */	cmplwi r0, 0
/* 8006CAB8 00069698  41 82 00 64 */	beq lbl_8006CB1C
/* 8006CABC 0006969C  88 1F 22 25 */	lbz r0, 0x2225(r31)
/* 8006CAC0 000696A0  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 8006CAC4 000696A4  40 82 00 20 */	bne lbl_8006CAE4
/* 8006CAC8 000696A8  80 9F 01 0C */	lwz r4, 0x10c(r31)
/* 8006CACC 000696AC  38 7F 00 00 */	addi r3, r31, 0
/* 8006CAD0 000696B0  38 A0 00 7F */	li r5, 0x7f
/* 8006CAD4 000696B4  80 84 00 4C */	lwz r4, 0x4c(r4)
/* 8006CAD8 000696B8  38 C0 00 40 */	li r6, 0x40
/* 8006CADC 000696BC  80 84 00 30 */	lwz r4, 0x30(r4)
/* 8006CAE0 000696C0  48 01 B6 69 */	bl func_80088148
lbl_8006CAE4:
/* 8006CAE4 000696C4  80 9F 1A 58 */	lwz r4, 0x1a58(r31)
/* 8006CAE8 000696C8  38 7E 00 00 */	addi r3, r30, 0
/* 8006CAEC 000696CC  38 A0 00 00 */	li r5, 0
/* 8006CAF0 000696D0  48 00 BC 65 */	bl func_80078754
/* 8006CAF4 000696D4  81 9F 21 90 */	lwz r12, 0x2190(r31)
/* 8006CAF8 000696D8  38 7E 00 00 */	addi r3, r30, 0
/* 8006CAFC 000696DC  7D 88 03 A6 */	mtlr r12
/* 8006CB00 000696E0  4E 80 00 21 */	blrl 
/* 8006CB04 000696E4  81 9F 21 98 */	lwz r12, 0x2198(r31)
/* 8006CB08 000696E8  7F C4 F3 78 */	mr r4, r30
/* 8006CB0C 000696EC  80 7F 1A 58 */	lwz r3, 0x1a58(r31)
/* 8006CB10 000696F0  7D 88 03 A6 */	mtlr r12
/* 8006CB14 000696F4  4E 80 00 21 */	blrl 
/* 8006CB18 000696F8  48 00 00 64 */	b lbl_8006CB7C
lbl_8006CB1C:
/* 8006CB1C 000696FC  7F C3 F3 78 */	mr r3, r30
/* 8006CB20 00069700  48 00 F1 71 */	bl func_8007BC90
/* 8006CB24 00069704  80 1F 1A 60 */	lwz r0, 0x1a60(r31)
/* 8006CB28 00069708  28 00 00 00 */	cmplwi r0, 0
/* 8006CB2C 0006970C  41 82 00 50 */	beq lbl_8006CB7C
/* 8006CB30 00069710  88 1F 22 25 */	lbz r0, 0x2225(r31)
/* 8006CB34 00069714  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 8006CB38 00069718  40 82 00 20 */	bne lbl_8006CB58
/* 8006CB3C 0006971C  80 9F 01 0C */	lwz r4, 0x10c(r31)
/* 8006CB40 00069720  38 7F 00 00 */	addi r3, r31, 0
/* 8006CB44 00069724  38 A0 00 7F */	li r5, 0x7f
/* 8006CB48 00069728  80 84 00 4C */	lwz r4, 0x4c(r4)
/* 8006CB4C 0006972C  38 C0 00 40 */	li r6, 0x40
/* 8006CB50 00069730  80 84 00 30 */	lwz r4, 0x30(r4)
/* 8006CB54 00069734  48 01 B5 F5 */	bl func_80088148
lbl_8006CB58:
/* 8006CB58 00069738  7F C3 F3 78 */	mr r3, r30
/* 8006CB5C 0006973C  80 9F 1A 60 */	lwz r4, 0x1a60(r31)
/* 8006CB60 00069740  48 20 E9 45 */	bl func_8027B4A4
/* 8006CB64 00069744  81 9F 21 94 */	lwz r12, 0x2194(r31)
/* 8006CB68 00069748  28 0C 00 00 */	cmplwi r12, 0
/* 8006CB6C 0006974C  41 82 00 10 */	beq lbl_8006CB7C
/* 8006CB70 00069750  7D 88 03 A6 */	mtlr r12
/* 8006CB74 00069754  38 7E 00 00 */	addi r3, r30, 0
/* 8006CB78 00069758  4E 80 00 21 */	blrl 
lbl_8006CB7C:
/* 8006CB7C 0006975C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8006CB80 00069760  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8006CB84 00069764  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8006CB88 00069768  38 21 00 18 */	addi r1, r1, 0x18
/* 8006CB8C 0006976C  7C 08 03 A6 */	mtlr r0
/* 8006CB90 00069770  4E 80 00 20 */	blr 
}

asm void func_8006CB94()
{
	nofralloc
/* 8006CB94 00069774  7C 08 02 A6 */	mflr r0
/* 8006CB98 00069778  90 01 00 04 */	stw r0, 4(r1)
/* 8006CB9C 0006977C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8006CBA0 00069780  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8006CBA4 00069784  7C 7F 1B 78 */	mr r31, r3
/* 8006CBA8 00069788  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8006CBAC 0006978C  88 03 22 1F */	lbz r0, 0x221f(r3)
/* 8006CBB0 00069790  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 8006CBB4 00069794  40 82 00 68 */	bne lbl_8006CC1C
/* 8006CBB8 00069798  88 03 22 19 */	lbz r0, 0x2219(r3)
/* 8006CBBC 0006979C  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 8006CBC0 000697A0  40 82 00 5C */	bne lbl_8006CC1C
/* 8006CBC4 000697A4  48 00 9A 1D */	bl func_800765E0
/* 8006CBC8 000697A8  7F E3 FB 78 */	mr r3, r31
/* 8006CBCC 000697AC  48 00 C0 A5 */	bl func_80078C70
/* 8006CBD0 000697B0  7F E3 FB 78 */	mr r3, r31
/* 8006CBD4 000697B4  48 00 FB A9 */	bl func_8007C77C
/* 8006CBD8 000697B8  7F E3 FB 78 */	mr r3, r31
/* 8006CBDC 000697BC  48 00 C6 81 */	bl func_8007925C
/* 8006CBE0 000697C0  7F E3 FB 78 */	mr r3, r31
/* 8006CBE4 000697C4  48 00 EE DD */	bl func_8007BAC0
/* 8006CBE8 000697C8  7F E3 FB 78 */	mr r3, r31
/* 8006CBEC 000697CC  48 00 F8 D1 */	bl func_8007C4BC
/* 8006CBF0 000697D0  7F E3 FB 78 */	mr r3, r31
/* 8006CBF4 000697D4  48 00 DF 55 */	bl func_8007AB48
/* 8006CBF8 000697D8  7F E3 FB 78 */	mr r3, r31
/* 8006CBFC 000697DC  48 00 DF 85 */	bl func_8007AB80
/* 8006CC00 000697E0  7F E3 FB 78 */	mr r3, r31
/* 8006CC04 000697E4  48 00 EF C9 */	bl func_8007BBCC
/* 8006CC08 000697E8  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006CC0C 000697EC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8006CC10 000697F0  40 81 00 0C */	ble lbl_8006CC1C
/* 8006CC14 000697F4  7F E3 FB 78 */	mr r3, r31
/* 8006CC18 000697F8  48 01 30 65 */	bl func_8007FC7C
lbl_8006CC1C:
/* 8006CC1C 000697FC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8006CC20 00069800  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8006CC24 00069804  38 21 00 18 */	addi r1, r1, 0x18
/* 8006CC28 00069808  7C 08 03 A6 */	mtlr r0
/* 8006CC2C 0006980C  4E 80 00 20 */	blr  
}


asm void func_8006CC30()
{
	nofralloc 
/* 8006CC30 00069810  7C 08 02 A6 */	mflr r0
/* 8006CC34 00069814  90 01 00 04 */	stw r0, 4(r1)
/* 8006CC38 00069818  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8006CC3C 0006981C  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 8006CC40 00069820  FF E0 08 90 */	fmr f31, f1
/* 8006CC44 00069824  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8006CC48 00069828  7C 7F 1B 78 */	mr r31, r3
/* 8006CC4C 0006982C  48 00 00 31 */	bl func_8006CC7C
/* 8006CC50 00069830  FC 00 F8 1E */	fctiwz f0, f31
/* 8006CC54 00069834  7F E3 FB 78 */	mr r3, r31
/* 8006CC58 00069838  D8 01 00 10 */	stfd f0, 0x10(r1)
/* 8006CC5C 0006983C  80 81 00 14 */	lwz r4, 0x14(r1)
/* 8006CC60 00069840  48 01 1E 31 */	bl func_8007EA90
/* 8006CC64 00069844  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8006CC68 00069848  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 8006CC6C 0006984C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8006CC70 00069850  38 21 00 28 */	addi r1, r1, 0x28
/* 8006CC74 00069854  7C 08 03 A6 */	mtlr r0
/* 8006CC78 00069858  4E 80 00 20 */	blr  
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


asm void func_8006CF5C()
{
	nofralloc 
/* 8006CF5C 00069B3C  7C 08 02 A6 */	mflr r0
/* 8006CF60 00069B40  90 01 00 04 */	stw r0, 4(r1)
/* 8006CF64 00069B44  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8006CF68 00069B48  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8006CF6C 00069B4C  7C 7F 1B 78 */	mr r31, r3
/* 8006CF70 00069B50  88 03 22 24 */	lbz r0, 0x2224(r3)
/* 8006CF74 00069B54  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8006CF78 00069B58  40 82 00 30 */	bne lbl_8006CFA8
/* 8006CF7C 00069B5C  80 1F 18 F0 */	lwz r0, 0x18f0(r31)
/* 8006CF80 00069B60  38 7F 00 00 */	addi r3, r31, 0
/* 8006CF84 00069B64  38 A0 00 00 */	li r5, 0
/* 8006CF88 00069B68  7C 00 22 14 */	add r0, r0, r4
/* 8006CF8C 00069B6C  90 1F 18 F0 */	stw r0, 0x18f0(r31)
/* 8006CF90 00069B70  38 80 00 08 */	li r4, 8
/* 8006CF94 00069B74  48 05 30 3D */	bl func_800BFFD0
/* 8006CF98 00069B78  38 7F 00 00 */	addi r3, r31, 0
/* 8006CF9C 00069B7C  38 80 00 02 */	li r4, 2
/* 8006CFA0 00069B80  38 A0 00 00 */	li r5, 0
/* 8006CFA4 00069B84  48 01 1C 09 */	bl func_8007EBAC
lbl_8006CFA8:
/* 8006CFA8 00069B88  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8006CFAC 00069B8C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8006CFB0 00069B90  38 21 00 18 */	addi r1, r1, 0x18
/* 8006CFB4 00069B94  7C 08 03 A6 */	mtlr r0
/* 8006CFB8 00069B98  4E 80 00 20 */	blr  
}


asm void func_8006CFBC()
{
	nofralloc 
/* 8006CFBC 00069B9C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8006CFC0 00069BA0  88 04 22 19 */	lbz r0, 0x2219(r4)
/* 8006CFC4 00069BA4  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8006CFC8 00069BA8  4D 82 00 20 */	beqlr 
/* 8006CFCC 00069BAC  88 04 22 1A */	lbz r0, 0x221a(r4)
/* 8006CFD0 00069BB0  38 60 00 01 */	li r3, 1
/* 8006CFD4 00069BB4  50 60 36 72 */	rlwimi r0, r3, 6, 0x19, 0x19
/* 8006CFD8 00069BB8  98 04 22 1A */	stb r0, 0x221a(r4)
/* 8006CFDC 00069BBC  4E 80 00 20 */	blr  
}


asm void func_8006CFE0()
{
	nofralloc 
/* 8006CFE0 00069BC0  7C 08 02 A6 */	mflr r0
/* 8006CFE4 00069BC4  90 01 00 04 */	stw r0, 4(r1)
/* 8006CFE8 00069BC8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8006CFEC 00069BCC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8006CFF0 00069BD0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8006CFF4 00069BD4  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 8006CFF8 00069BD8  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8006CFFC 00069BDC  41 82 00 34 */	beq lbl_8006D030
/* 8006D000 00069BE0  88 1F 22 1A */	lbz r0, 0x221a(r31)
/* 8006D004 00069BE4  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8006D008 00069BE8  40 82 00 18 */	bne lbl_8006D020
/* 8006D00C 00069BEC  C0 3F 19 54 */	lfs f1, 0x1954(r31)
/* 8006D010 00069BF0  C0 02 88 74 */	lfs f0, lbl_804D8254(r2)
/* 8006D014 00069BF4  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8006D018 00069BF8  40 82 00 08 */	bne lbl_8006D020
/* 8006D01C 00069BFC  48 00 00 F1 */	bl func_8006D10C
lbl_8006D020:
/* 8006D020 00069C00  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 8006D024 00069C04  38 60 00 00 */	li r3, 0
/* 8006D028 00069C08  50 60 07 FE */	rlwimi r0, r3, 0, 0x1f, 0x1f
/* 8006D02C 00069C0C  98 1F 22 19 */	stb r0, 0x2219(r31)
lbl_8006D030:
/* 8006D030 00069C10  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8006D034 00069C14  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8006D038 00069C18  38 21 00 18 */	addi r1, r1, 0x18
/* 8006D03C 00069C1C  7C 08 03 A6 */	mtlr r0
/* 8006D040 00069C20  4E 80 00 20 */	blr  
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


asm void func_8006D9AC()
{
	nofralloc 
/* 8006D9AC 0006A58C  7C 08 02 A6 */	mflr r0
/* 8006D9B0 0006A590  90 01 00 04 */	stw r0, 4(r1)
/* 8006D9B4 0006A594  94 21 FF F8 */	stwu r1, -8(r1)
/* 8006D9B8 0006A598  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8006D9BC 0006A59C  88 04 22 1F */	lbz r0, 0x221f(r4)
/* 8006D9C0 0006A5A0  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 8006D9C4 0006A5A4  40 82 00 18 */	bne lbl_8006D9DC
/* 8006D9C8 0006A5A8  88 04 22 19 */	lbz r0, 0x2219(r4)
/* 8006D9CC 0006A5AC  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 8006D9D0 0006A5B0  41 82 00 08 */	beq lbl_8006D9D8
/* 8006D9D4 0006A5B4  48 00 00 08 */	b lbl_8006D9DC
lbl_8006D9D8:
/* 8006D9D8 0006A5B8  48 03 06 D1 */	bl func_8009E0A8
lbl_8006D9DC:
/* 8006D9DC 0006A5BC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8006D9E0 0006A5C0  38 21 00 08 */	addi r1, r1, 8
/* 8006D9E4 0006A5C4  7C 08 03 A6 */	mtlr r0
/* 8006D9E8 0006A5C8  4E 80 00 20 */	blr 
}

asm void func_8006D9EC()
{
	nofralloc
/* 8006D9EC 0006A5CC  7C 08 02 A6 */	mflr r0
/* 8006D9F0 0006A5D0  90 01 00 04 */	stw r0, 4(r1)
/* 8006D9F4 0006A5D4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8006D9F8 0006A5D8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8006D9FC 0006A5DC  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8006DA00 0006A5E0  7C 7E 1B 78 */	mr r30, r3
/* 8006DA04 0006A5E4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8006DA08 0006A5E8  88 1F 22 1F */	lbz r0, 0x221f(r31)
/* 8006DA0C 0006A5EC  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 8006DA10 0006A5F0  40 82 00 24 */	bne lbl_8006DA34
/* 8006DA14 0006A5F4  7F C3 F3 78 */	mr r3, r30
/* 8006DA18 0006A5F8  48 01 28 05 */	bl func_8008021C
/* 8006DA1C 0006A5FC  81 9F 21 AC */	lwz r12, 0x21ac(r31)
/* 8006DA20 0006A600  28 0C 00 00 */	cmplwi r12, 0
/* 8006DA24 0006A604  41 82 00 10 */	beq lbl_8006DA34
/* 8006DA28 0006A608  7D 88 03 A6 */	mtlr r12
/* 8006DA2C 0006A60C  38 7E 00 00 */	addi r3, r30, 0
/* 8006DA30 0006A610  4E 80 00 21 */	blrl 
lbl_8006DA34:
/* 8006DA34 0006A614  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8006DA38 0006A618  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8006DA3C 0006A61C  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8006DA40 0006A620  38 21 00 18 */	addi r1, r1, 0x18
/* 8006DA44 0006A624  7C 08 03 A6 */	mtlr r0
/* 8006DA48 0006A628  4E 80 00 20 */	blr 
}

asm void func_8006DA4C()
{
	nofralloc
/* 8006DA4C 0006A62C  7C 08 02 A6 */	mflr r0
/* 8006DA50 0006A630  90 01 00 04 */	stw r0, 4(r1)
/* 8006DA54 0006A634  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8006DA58 0006A638  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8006DA5C 0006A63C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8006DA60 0006A640  88 9F 22 1F */	lbz r4, 0x221f(r31)
/* 8006DA64 0006A644  54 80 E7 FF */	rlwinm. r0, r4, 0x1c, 0x1f, 0x1f
/* 8006DA68 0006A648  40 82 00 40 */	bne lbl_8006DAA8
/* 8006DA6C 0006A64C  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 8006DA70 0006A650  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 8006DA74 0006A654  38 BF 00 B0 */	addi r5, r31, 0xb0
/* 8006DA78 0006A658  4B FC 4D B1 */	bl Player_80032828
/* 8006DA7C 0006A65C  88 9F 22 1F */	lbz r4, 0x221f(r31)
/* 8006DA80 0006A660  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 8006DA84 0006A664  C0 3F 00 2C */	lfs f1, 0x2c(r31)
/* 8006DA88 0006A668  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 8006DA8C 0006A66C  4B FC 56 85 */	bl Player_SetFacingDirectionConditional
/* 8006DA90 0006A670  88 9F 22 1F */	lbz r4, 0x221f(r31)
/* 8006DA94 0006A674  38 BF 00 B0 */	addi r5, r31, 0xb0
/* 8006DA98 0006A678  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 8006DA9C 0006A67C  38 DF 00 BC */	addi r6, r31, 0xbc
/* 8006DAA0 0006A680  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 8006DAA4 0006A684  4B FD 20 05 */	bl func_8003FAA8
lbl_8006DAA8:
/* 8006DAA8 0006A688  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8006DAAC 0006A68C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8006DAB0 0006A690  38 21 00 18 */	addi r1, r1, 0x18
/* 8006DAB4 0006A694  7C 08 03 A6 */	mtlr r0
/* 8006DAB8 0006A698  4E 80 00 20 */	blr  
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
