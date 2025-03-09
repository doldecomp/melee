
#include "ft/ftattacks4combo.h"

#include "ft/chara/ftCommon/ftCo_AttackS4.h"
#include "ft/chara/ftCommon/ftCo_Wait.h"
#include "ft/fighter.h"

// bool ftCo_800CECE8(ftCo_GObj* gobj) {}

// UNK_RET ftCo_800CED30(UNK_PARAMS) {}

void ftCo_AttackS42_Anim(ftCo_GObj* gobj)
{
    ftCo_AttackS4_Anim(gobj);
}

void ftCo_AttackS42_IASA(ftCo_GObj* gobj)
{
    if ((((Fighter*) gobj->user_data)->x2218 >> 7U) & 1) {
        ftCo_Wait_IASA(gobj);
    }
}

void ftCo_AttackS42_Phys(ftCo_GObj* gobj)
{
    ftCo_AttackS4_Phys(gobj);
}

void ftCo_AttackS42_Coll(ftCo_GObj* gobj)
{
    ftCo_AttackS4_Coll(gobj);
}
