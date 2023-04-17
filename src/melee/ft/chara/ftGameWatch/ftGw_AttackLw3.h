#ifndef MELEE_FT_CHARA_FTGAMEWATCH_FTGAMEWATCH_ATTACKLW3_H
#define MELEE_FT_CHARA_FTGAMEWATCH_FTGAMEWATCH_ATTACKLW3_H

#include <platform.h>
#include <baselib/forward.h>

// Down Tilt (AttackLw3)
void ftGw_AttackLw3_ItemManholeSetup(HSD_GObj* gobj);
void ftGw_AttackLw3_ItemManholeRemove(HSD_GObj* gobj);
void ftGw_AttackLw3_ItemManholeOnDamage(HSD_GObj* gobj);
bool ftGw_AttackLw3_ItemCheckManholeRemove(HSD_GObj* gobj);
void ftGw_AttackLw3_Enter(HSD_GObj* gobj);
void ftGw_AttackLw3_Anim(HSD_GObj* gobj);
void ftGw_AttackLw3_IASA(HSD_GObj* gobj);
void ftGw_AttackLw3_Phys(HSD_GObj* gobj);
void ftGw_AttackLw3_Coll(HSD_GObj* gobj);

#endif
