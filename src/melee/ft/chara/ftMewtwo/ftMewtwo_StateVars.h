#ifndef _FTMEWTWO_STATEVARS_H_
#define _FTMEWTWO_STATEVARS_H_

#include <types.h>
#include <sysdolphin/baselib/gobj.h>

typedef struct ftMewtwoSpecialHi {

	s32 travelFrames; // 0x2340 - Number of frames Teleport's zoom animation lasts for
	f32 stickX;
	f32 stickY;
	s32 unk4; // 0x234C - ???
	f32 velX;
	f32 velY;
	f32 groundVelX;

} ftMewtwoSpecialHi;

typedef struct ftMewtwoSpecialS {

	u8 isConfusionReflect : 1; // 0x2340 - ???

} ftMewtwoSpecialS;

typedef union ftMewtwoStateVars {

	ftMewtwoSpecialS SpecialS;
	ftMewtwoSpecialHi specialHi;

} ftMewtwoStateVars;

#endif