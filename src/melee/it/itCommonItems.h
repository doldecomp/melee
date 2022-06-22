#ifndef _itCommonItems_h_
#define _itCommonItems_h_

#include <dolphin/types.h>

typedef struct BobOmbVars
{
	s32 xDD4;
	s32 xDD8;
	s32 xDDC;
	s32 xDE0;
	s32 xDE4;
	s32 xDE8;
	f32 xDEC;
}BobOmbVars;

typedef struct HeartContainerVars
{
	s32 xDD4_heal;
}HeartContainerVars;

typedef struct MaximTomatoVars
{
	s32 xDD4_heal;
}MaximTomatoVars;

typedef struct FoodVars
{
	s32 xDD4_unk;
	s32 xDD8_heal;
}FoodVars;

typedef struct EggVars // Eggs spawned on Yoshi stages / by Chansey //
{
	u8 filler[0x60];
	s32 xE34_heal;
}EggVars;

typedef struct WhispyAppleVars
{
	s32 xDD4_heal;
}WhispyAppleVars;

typedef struct itUnkAttributes // Might be shared? //
{
	f32 x0_float;
	f32 x4_float;
}itUnkAttributes;

#endif