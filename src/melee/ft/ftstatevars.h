// This is a file to include all existing StateVar headers until they're finalized.

#ifndef _FTSTATEVARS_H_
#define _FTSTATEVARS_H_

#include <melee/ft/chara/ftMario/ftMario_StateVars.h>
#include <melee/ft/chara/ftCaptain/ftCaptain_StateVars.h>
#include <melee/ft/chara/ftFox/ftFox_StateVars.h>
#include <melee/ft/chara/ftNess/ftNess_StateVars.h>
#include <melee/ft/chara/ftLuigi/ftLuigi_StateVars.h>
#include <melee/ft/chara/ftMewtwo/ftMewtwo_StateVars.h>
#include <melee/ft/chara/ftGameWatch/ftGameWatch_StateVars.h>

typedef struct ftCliffCommonVars {

	s32 ledgeID; // 0x2340 - Used to check against opponent's variable @ 0x213C while they're occupying a ledge within grab range

} ftCliffCommonVars;

typedef union ftCommonStateVars {

	ftCliffCommonVars cliffCommon;

} ftCommonStateVars;

#endif