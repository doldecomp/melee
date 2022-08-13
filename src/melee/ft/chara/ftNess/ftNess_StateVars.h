#ifndef _FTNESS_STATEVARS_H_
#define _FTNESS_STATEVARS_H_

#include <types.h>
#include <sysdolphin/baselib/gobj.h>

typedef struct ftNessYoyo {

	s32 yoyoCurrentFrame;   // 0x2340 - Current frame of Up/Down Smash animation as an integer
	s32 yoyoRehitTimer;     // 0x2344 - Frames until Up/Down Smash hitbox automatically refreshes; part of why the Yo-Yo Glitch occurs
	BOOL isChargeDisable;   // 0x2348 - BOOL to indicate whether Ness can charge the Yo-Yo
	BOOL isPosUpdateMod;    // 0x234C - BOOL to indicate whether Yo-Yo hitbox position should update based on raw Vec3 input (FALSE) or modified calculations (TRUE)

} ftNessYoyo;

typedef struct ftNessSpecialN {

	s32 flashTimerLoop1;    // 0x2340 - Number of frames Ness remains in the "charge loop" animation after releasing PK Flash 
	s32 flashTimerLoop2;	// 0x2344 - Number of extra frames Ness remains in the "charge loop" animation after releasing PK Flash?
	s32 gravityDelay;		// 0x2348 - Number of frames to pass before gravity takes effect
	s32 flashTimerMin;      // 0x234C - Minimum number of frames required to pass for PK Flash to auto-release if B is not being held

} ftNessSpecialN;

typedef struct ftNessSpecialHi {

	s32 thunderColl;		// 0x2340 - PK Thunder collision type? Used to check if PK Thunder is colliding with Ness
	s32 thunderTimerLoop1;  // 0x2344 - Number of frames Ness remains in the "control loop" animation after PK Thunder despawns
	s32 thunderTimerLoop2;	// 0x2348 - Number of extra frames Ness remains in the "control loop" animation after PK Thunder despawns?
	s32 gravityDelay;       // 0x234C - Number of frames to pass before gravity takes effect
	Vec3 collPos1;          // 0x2350 - ???
	Vec3 collPos2;          // 0x235C - ???
	f32 aerialVel;          // 0x2368 - Aerial velocity of PK Thunder 2 (Self-Hit)
	f32 unkVar;				// 0x236C - Set various times but never actually used?
	f32 facingDir;          // 0x2370 - Facing direction change frorm PK Thunder collision
	Vec3 unkVector1;		// 0x2374 through 0x237C - Unused vector
	s32 jibakuGFX;			// 0x2380 - BOOL used in a weird way to switch to PK Thunder 2 GFX
	f32 fallAccel;          // 0x2384 - Fall acceleration of PK Thunder 2 (Self-Hit)
	f32 unkVar3;			// 0x2388 - Set various times but never actually used?
	f32 unkVar4;			// 0x238C - Set various times but never actually used?

} ftNessSpecialHi;

typedef struct ftNessSpecialLw {

	s32 releaseLag;			// 0x2340 - Auto lag frames after initializing PSI Magnet if B is not being held; PSI Magnet is immediately released with no lag once these frames have passed
	s32 turnFrames;         // 0x2344 - Unused turnaround timer
	BOOL isRelease;			// 0x2348 - Check if Ness is no longer holding B
	s32 gravityDelay;		// 0x234C - Number of frames to pass before gravity takes effect

} ftNessSpecialLw;

typedef union ftNessStateVars
{
	ftNessYoyo attackHi4;
	ftNessYoyo attackLw4;
	ftNessSpecialN specialN;
	ftNessSpecialHi specialHi;
	ftNessSpecialLw specialLw;

} ftNessStateVars;


#endif