#ifndef _FTLUIGI_STATEVARS_H_
#define _FTLUIGI_STATEVARS_H_

#include <types.h>
#include <sysdolphin/baselib/gobj.h>

typedef struct ftLuigiSpecialS {

	s32 chargeFrames; // 0x2340 - Number of frames Green Missile has been charged
	BOOL isMisfire;   // 0x2344 - Check if Green Missile will misfire

} ftLuigiSpecialS;

typedef struct ftLuigiSpecialLw {

	f32 groundVelX;	  // 0x2340 - Grounded momentum of Luigi Cyclone
	s32 unk;          // 0x2344 - Set but never used?
	s32 unused;	      // 0x2348 - Skipped entirely
	BOOL isUnkColl;   // 0x234C - Checked in collision, related to some angle calculation

} ftLuigiSpecialLw;

typedef union ftLuigiStateVars {

	ftLuigiSpecialS specialS;
	ftLuigiSpecialLw specialLw;

} ftLuigiStateVars;

#endif