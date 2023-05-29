#ifndef GALE01_0877F8
#define GALE01_0877F8

#include "ft/forward.h"
#include <baselib/forward.h>

#include "ft/fighter.h"

extern HSD_Joint* ft_8045A1E0[6];
extern s32 ft_80459B88[FTKIND_MAX];
extern char ftMr_Init_DatFilename[];
extern char ftMr_Init_DataName[];
extern Fighter_CostumeStrings ftMr_Init_CostumeStrings[];
extern char ftMr_Init_AnimDatFilename[];

s32 ft_800877F8(Fighter_GObj*, s32);
s32 ft_80087818(Fighter_GObj*, s32);
s32 ft_80087838(Fighter_GObj* gobj);
s32 ft_80087858(Fighter_GObj* gobj);
s32 ft_80087878(Fighter_GObj*, s32);
s32 ft_800878BC(Fighter_GObj* gobj);
s32 ft_80087900(Fighter_GObj* gobj);
s32 ft_80087944(Fighter_GObj* gobj);
s32 ft_80087988(Fighter_GObj* gobj);
s32 ft_800879D8(Fighter_GObj* gobj);
s32 ft_800879F8(Fighter_GObj* gobj);
s32 ft_80087A18(Fighter_GObj* gobj);
u8 ft_80087A80(Fighter_GObj* gobj);
f32 ft_80087A8C(Fighter_GObj* gobj);
s32 ft_80087A98(Fighter_GObj* gobj);
u8 ft_80087AA4(Fighter_GObj* gobj);
u8 ft_80087AB4(Fighter_GObj* gobj);
void ft_80087AC0(Fighter_GObj*, s32);
s32 ft_80087AEC(Fighter_GObj* gobj);
s32 ft_80087B34(Fighter_GObj* gobj);
void ft_80087BAC(Fighter_GObj*, s32);
void ft_80087BC0(Fighter_GObj*, s8);
void ft_80087BEC(Fighter_GObj*, u8);
s32 ft_80087C1C(void);
s32 ft_80087C58(Fighter_GObj* gobj);
void ft_80087C64(Fighter_GObj*, s32);
s32 ft_80087C70(Fighter*, s32);
s32 ft_80087D0C(Fighter*, s32);
void ft_8008805C(Fighter*, s32);
void ft_80088080(Fighter*);
void ft_800880AC(Fighter*);
void ft_800880D8(Fighter*);
void ft_80088110(Fighter*);
void ft_80088148(Fighter*, enum_t, int, int);
void ft_800881D8(Fighter*, u32, u32, u32);
void ft_80088478(Fighter*, s32, s32, s32);
void ft_80088510(Fighter*, s32, u8, u8);
void ft_80088640(Fighter*, bool, bool, bool);
void ft_80088770(Fighter*);
void ft_800887CC(Fighter*);
void ft_80088884(Fighter*);
void ft_800888E0(Fighter*);
void ft_80088A50(Fighter*);
void ft_80088C5C(Fighter_GObj* gobj);
void ft_800890BC(Fighter*);
void ft_800890D0(Fighter*, u8);
void ft_80089228(void);
void ft_800892A0(Fighter_GObj* gobj);
void ft_800892D4(Fighter*);
void ft_800895E0(Fighter*, s32);
void ft_80089824(Fighter_GObj* gobj);
void ft_80089B08(Fighter_GObj* gobj);
bool ft_8008A1FC(Fighter_GObj* gobj);
void ft_8008A2BC(Fighter_GObj* gobj);
void ft_8008A324(Fighter_GObj* gobj);
unk_t mpColl_8004B4B0(void);
/* 0889F4 */ void ft_800889F4(Fighter* fp, FtCollisionData*);
/* 0886D8 */ void ftCo_800886D8(Fighter* fp, UNK_T, UNK_T, UNK_T);
/* 08893C */ void ft_8008893C(Fighter* fp);
/* 088828 */ void ft_80088828(Fighter* fp);
/* 088328 */ void ft_80088328(Fighter* fp, int, int, int);
/* 0885A8 */ void ft_800885A8(Fighter* fp, int, int, int);
/* 08A1B8 */ void ft_8008A1B8(Fighter_GObj* gobj, int);

#endif
