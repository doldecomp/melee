#ifndef FT_CHARA_FTMASTERHAND___FTMASTERHAND_H
#define FT_CHARA_FTMASTERHAND___FTMASTERHAND_H

#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>
#include <melee/ft/ftbosslib.h>

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
void ftMasterHand_80155B80(HSD_GObj* fighter_gobj);
void ftMasterHand_8015483C(HSD_GObj* fighter_gobj);
void ftMasterHand_80155C94(HSD_GObj* fighter_gobj);
void ftMasterHand_80155D1C(HSD_GObj* interacted_fighter_gobj);
void ftMasterHand_80155D6C(HSD_GObj* interacted_fighter_gobj, s32 unused_arg);
void ftMasterHand_8014FFDC(HSD_GObj* fighter_gobj);
void ftMasterHand_8015082C(HSD_GObj* fighter_gobj);
void ftMasterHand_80150870(HSD_GObj* fighter_gobj);
void ftMasterHand_801515B8(HSD_GObj* fighter_gobj);
void ftMasterHand_801516B4(HSD_GObj* fighter_gobj);
u32 ftMasterHand_80151428(Vec* vec);
void ftMasterHand_801517B0(HSD_GObj* fighter_gobj);
void ftMasterHand_801517F4(HSD_GObj* fighter_gobj);
void ftMasterHand_80151824(void);
void ftMasterHand_80151828(HSD_GObj*); // 6 Stage Wide Slap
void ftMasterHand_80151874(HSD_GObj* fighter_gobj);
void ftMasterHand_801518B0(HSD_GObj* fighter_gobj);
void ftMasterHand_801518F4(HSD_GObj* fighter_gobj);
void ftMasterHand_80151914(void);
void ftMasterHand_8015198C(HSD_GObj* fighter_gobj);
void ftMasterHand_80151A44(HSD_GObj* fighter_gobj);
void ftMasterHand_80151A88(HSD_GObj* fighter_gobj);
void ftMasterHand_80151AC4(void);
void ftMasterHand_80151B14(HSD_GObj* fighter_gobj);
void ftMasterHand_80151B50(HSD_GObj* fighter_gobj);
void ftMasterHand_80151B70(HSD_GObj* fighter_gobj);
void ftMasterHand_80151BB4(void);
void ftMasterHand_80151BB8(HSD_GObj* fighter_gobj); // 7 Sweep
void ftMasterHand_80151C04(HSD_GObj* fighter_gobj);
void ftMasterHand_80151C40(HSD_GObj* fighter_gobj);
void ftMasterHand_80151C84(HSD_GObj* fighter_gobj);
void ftMasterHand_80151BB4(void);

#endif
