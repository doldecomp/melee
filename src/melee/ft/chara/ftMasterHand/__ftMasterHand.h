#ifndef FT_CHARA_FTMASTERHAND___FTMASTERHAND_H
#define FT_CHARA_FTMASTERHAND___FTMASTERHAND_H

#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

typedef void (*GObjCallback)(HSD_GObj* fighter_gobj);

void ftMasterHand_80154A78(HSD_GObj* fighter_gobj);
void ftMasterHand_80154C78(HSD_GObj* fighter_gobj);
void ftMasterHand_80154CF8(HSD_GObj* fighter_gobj, Fighter* fp);
void ftMasterHand_80154E78(HSD_GObj* fighter_gobj);
void ftMasterHand_80155014(HSD_GObj* fighter_gobj);
void ftMasterHand_80150DC4(HSD_GObj* fighter_gobj, GObjCallback, Vec3*);
void ftMasterHand_80150230(HSD_GObj* fighter_gobj);
void ftMasterHand_801510B0(HSD_GObj* fighter_gobj);
void ftMasterHand_80151CA8(HSD_GObj* fighter_gobj);

void ftMasterHand_80152370(HSD_GObj* fighter_gobj); // 11 Punch
void ftMasterHand_80152880(HSD_GObj* fighter_gobj);
void ftMasterHand_801530A4(HSD_GObj* fighter_gobj);
void ftMasterHand_80153820(HSD_GObj* fighter_gobj);
void ftMasterHand_80153A64(HSD_GObj* fighter_gobj);
void ftMasterHand_801541C8(HSD_GObj* fighter_gobj, GObjCallback);
void ftMasterHand_801542E0(HSD_GObj* fighter_gobj);
void ftMasterHand_801546D8(HSD_GObj* fighter_gobj);

#endif