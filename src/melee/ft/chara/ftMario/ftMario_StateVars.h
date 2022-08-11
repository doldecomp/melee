#ifndef _FTMARIO_STATEVARS_H_
#define _FTMARIO_STATEVARS_H_

#include <types.h>
#include <sysdolphin/baselib/gobj.h>

typedef struct ftMarioSpecialS {

	BOOL isReflect; // 0x2340 - BOOL to check if reflect bubble should be enabled

} ftMarioSpecialS;

typedef struct ftMarioSpecialLw {

	f32 groundVelX;	  // 0x2340 - Grounded momentum of Mario / Dr. Tornado
	s32 unk;          // 0x2344 - Set but never used?
	s32 unused;	      // 0x2348 - Skipped entirely
	BOOL isUnkColl;   // 0x234C - Checked in collision, related to some angle calculation

} ftMarioSpecialLw;

typedef union ftMarioStateVars {

	ftMarioSpecialS specialS;
	ftMarioSpecialLw specialLw;

} ftMarioStateVars;

#endif