#ifndef _FTGAMEWATCH_STATEVARS_H_
#define _FTGAMEWATCH_STATEVARS_H_

#include <types.h>
#include <sysdolphin/baselib/gobj.h>

typedef struct ftGameWatchAttack11 {

	BOOL unk;		// 0x2340 - Set to 0 but never used?

} ftGameWatchAttack11;

typedef struct ftGameWatchSpecialLw {

	BOOL isRelease; // 0x2340 - BOOL to check if Mr. Game & Watch is no longer holding B
	s32 turnFrames; // 0x2344 - Number of frames it takes Mr. Game & Watch to turn around on command

} ftGameWatchSpecialLw;

typedef union ftGameWatchVars {

	ftGameWatchAttack11 Attack11;
	ftGameWatchSpecialLw SpecialLw;

} ftGameWatchStateVars;

#endif