#ifndef MELEE_FT_CHARA_FTMASTERHAND_FTMASTERHAND_34_H
#define MELEE_FT_CHARA_FTMASTERHAND_FTMASTERHAND_34_H

#include <platform.h>

#include <baselib/gobj.h>

void ftMh_CaptureWaitMasterHand_80155D1C(HSD_GObj*);
void ftMh_CaptureWaitMasterHand_80155D6C(HSD_GObj*, s32);

void ftMh_CaptureWaitMasterHand_Anim(HSD_GObj* gobj);
void ftMh_CaptureWaitMasterHand_IASA(HSD_GObj* gobj);
void ftMh_CaptureWaitMasterHand_Phys(HSD_GObj* gobj);
void ftMh_CaptureWaitMasterHand_Coll(HSD_GObj* gobj);
void ftMh_CaptureWaitMasterHand_80155D6C(HSD_GObj* gobj, s32 arg1);
void ftMh_ThrownMasterHand_Anim(HSD_GObj* gobj);
void ftMh_ThrownMasterHand_IASA(HSD_GObj* gobj);
void ftMh_ThrownMasterHand_Phys(HSD_GObj* gobj);
void ftMh_ThrownMasterHand_Coll(HSD_GObj* gobj);
void ftMh_CaptureWaitMasterHand_80155D1C(HSD_GObj* gobj);

#endif
