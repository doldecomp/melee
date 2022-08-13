#ifndef _itPKThunder_h_
#define _itPKThunder_h_

#include <dolphin/types.h>

typedef struct itPKThunderAttributes
{
	f32 x0_PKTHUNDER_LIFETIME;
	f32 x4_PKTHUNDER_SPEED;
	f32 x8_PKTHUNDER_SPAWN_ANGLE;
	f32 xC_PKTHUNDER_STICK_THRESHOLD;
	f32 x10_PKTHUNDER_TURN_RADIUS;
} itPKThunderAttributes;

typedef struct PKThunderVars
{
	HSD_GObj* xDD4[6]; // GObj pointers?
	Vec3 xDEC; // Start of vars
	Vec3 xDFC;
	Vec3 xE08;
	Vec3 xE14;
	Vec3 xE20;
	Vec3 xE2C;
	Vec3 xE38;
	Vec3 xE44;
	Vec3 xE50;
	Vec3 xE5C;
	Vec3 xE68;
	Vec3 xE74;
	Vec3 xE80;
	Vec3 xE8C;
	Vec3 xE98;
	Vec3 xEA0;
	f32 xEAC; // PK Thunder release angles?
	f32 xEB0;
	f32 xEB4;
	f32 xEB8;
	f32 xEBC;
	f32 xEC0;
	f32 xEC4;
	f32 xEC8;
	f32 xECC;
	f32 xED0;
	f32 xED4;
	f32 xED8;
	f32 xEDC;
	f32 xEE0;
	f32 xEE4;
	f32 xEE8;
	s32 xEEC;
	s32 xEF0;
	HSD_GObj* xEF4; // MOAR pointars!
	HSD_GObj* xEF8;
	HSD_GObj* xEFC;
	HSD_GObj* xF00;
	HSD_GObj* xF04;
	HSD_GObj* xF08;
} PKThunderVars;

#endif