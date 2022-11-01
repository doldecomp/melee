#ifndef FT_CHARA_FTMASTERHAND___FTMASTERHAND_H
#define FT_CHARA_FTMASTERHAND___FTMASTERHAND_H

#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

void ftMasterHand_80154A78(HSD_GObj* fighter_gobj);
void ftMasterHand_80154C78(HSD_GObj* fighter_gobj);
void ftMasterHand_80154CF8(HSD_GObj* fighter_gobj, Fighter* fp);
void ftMasterHand_80154E78(HSD_GObj* fighter_gobj);
void ftMasterHand_80155014(HSD_GObj* fighter_gobj);
void ftMasterHand_80150DC4(HSD_GObj* fighter_gobj, void (*callback)(HSD_GObj* fighter_gobj), Vec3*);
void ftMasterHand_80150230(HSD_GObj* fighter_gobj);
void ftMasterHand_801510B0(HSD_GObj* fighter_gobj);
void ftMasterHand_80151CA8(HSD_GObj* fighter_gobj);

void ftMasterHand_80152370(HSD_GObj* fighter_gobj); // 11 Punch
void ftMasterHand_80152880(HSD_GObj* fighter_gobj);

#endif