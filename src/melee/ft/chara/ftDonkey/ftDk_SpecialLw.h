#ifndef MELEE_FT_CHARA_FTDONKEY_FTDONKEY_SPECIALLW_H
#define MELEE_FT_CHARA_FTDONKEY_FTDONKEY_SPECIALLW_H

#include <platform.h>
#include <baselib/forward.h>

void ftDk_SpecialLwEnd_Anim(HSD_GObj* gobj);
void ftDk_SpecialLwEnd_IASA(HSD_GObj* gobj);
void ftDk_SpecialLw_Enter(HSD_GObj* gobj);
void ftDk_SpecialLwEnd_Phys(HSD_GObj* gobj);
void ftDk_SpecialLwEnd_Coll(HSD_GObj* gobj);
void ftDk_MS_386_Anim(HSD_GObj* gobj);
void ftDk_MS_386_IASA(HSD_GObj* gobj);
void ftDk_MS_386_Phys(HSD_GObj* gobj);
void ftDk_MS_386_Coll(HSD_GObj* gobj);
void ftDk_SpecialLwStart_Anim(HSD_GObj* gobj);
void ftDk_SpecialLwStart_IASA(HSD_GObj* gobj);
void ftDk_SpecialLwStart_Phys(HSD_GObj* gobj);
void ftDk_SpecialLwStart_Coll(HSD_GObj* gobj);
void ftDk_SpecialLwLoop_Anim(HSD_GObj* gobj);
void ftDk_SpecialLwLoop_IASA(HSD_GObj* gobj);
void ftDk_SpecialLwLoop_Phys(HSD_GObj* gobj);
void ftDk_SpecialLwLoop_Coll(HSD_GObj* gobj);
void callback(HSD_GObj* gobj);
void ftDonkey_8010DE88_inner(HSD_GObj* gobj);

#endif
