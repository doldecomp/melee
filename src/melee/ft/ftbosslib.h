#ifndef MELEE_FT_FTBOSSLIB_H
#define MELEE_FT_FTBOSSLIB_H

#include <melee/ft/fighter.h>

HSD_GObj* ftbosslib_8015C3E8(s32); // ftbosslib_8015C3E8(FighterKind)
s32 ftbosslib_8015C44C(s32);       // ftbosslib_8015C44C(FighterKind)
void ftbosslib_8015BD20(HSD_GObj* fighter_gobj);
void ftbosslib_8015BD24(s32, f32*, f32, s32, s32, s32);
void ftbosslib_8015BDB4(HSD_GObj* fighter_gobj);
void ftbosslib_8015BE40(HSD_GObj* fighter_gobj, Vec* pos, f32*, f32, f32);
void ftbosslib_8015BF74(HSD_GObj* fighter_gobj, f32);
void ftbosslib_8015C010(HSD_GObj* fighter_gobj, f32);
void ftbosslib_8015C09C(HSD_GObj* fighter_gobj, f32);

#endif
