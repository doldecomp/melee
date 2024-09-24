#include "ft/inlines.h"
#include "ft/types.h"

void fn_800DA490(Fighter_GObj* gobj)
{
    GET_FIGHTER(gobj)->take_dmg_cb = NULL;
}

void ftCo_DamageScrew_IASA(Fighter_GObj* gobj) {}

void ftCo_DeadLeft_Cam(Fighter_GObj* gobj) {}

void ftCo_DeadRight_Cam(Fighter_GObj* gobj) {}

void ftCo_DeadDown_Cam(Fighter_GObj* gobj) {}

void ftCo_DeadUp_Cam(Fighter_GObj* gobj) {}

void ftCo_Rebirth_IASA(Fighter_GObj* gobj) {}

void ftCo_ItemScopeStart_Anim(Fighter_GObj* gobj) {}

void ftCo_ItemScopeAirStart_Anim(Fighter_GObj* gobj) {}

void ftCo_ItemScopeFire_IASA(Fighter_GObj* gobj) {}

void ftCo_ItemScopeAirFire_IASA(Fighter_GObj* gobj) {}

void ftCo_ItemScopeEnd_IASA(Fighter_GObj* gobj) {}

void ftCo_ItemScopeAirEnd_IASA(Fighter_GObj* gobj) {}

void ftCo_Catch_IASA(Fighter_GObj* gobj) {}

void ftCo_CatchDash_IASA(Fighter_GObj* gobj) {}

void ftCo_CatchPull_IASA(Fighter_GObj* gobj) {}

void ftCo_CatchWait_Anim(Fighter_GObj* gobj) {}

void ftCo_CatchAttack_IASA(Fighter_GObj* gobj) {}

void fn_800DA668(Fighter_GObj* gobj)
{
    GET_FIGHTER(gobj)->take_dmg_cb = NULL;
}

void ftCo_CatchCut_IASA(Fighter_GObj* gobj) {}

void ftCo_CapturePulledHi_Anim(Fighter_GObj* gobj) {}

void ftCo_CapturePulledHi_IASA(Fighter_GObj* gobj) {}

void ftCo_CapturePulledLw_Anim(Fighter_GObj* gobj) {}

void ftCo_CapturePulledLw_IASA(Fighter_GObj* gobj) {}

void ftCo_CaptureDamageHi_IASA(Fighter_GObj* gobj) {}

void ftCo_CaptureDamageLw_IASA(Fighter_GObj* gobj) {}

void ftCo_CaptureCut_IASA(Fighter_GObj* gobj) {}

void ftCo_ThrowF_IASA(Fighter_GObj* gobj) {}

void ftCo_ThrowB_IASA(Fighter_GObj* gobj) {}

void ftCo_ThrowHi_IASA(Fighter_GObj* gobj) {}

void ftCo_ThrowLw_IASA(Fighter_GObj* gobj) {}

void ftCo_ThrownF_IASA(Fighter_GObj* gobj) {}

void ftCo_ThrownF_Phys(Fighter_GObj* gobj) {}

void ftCo_ThrownF_Coll(Fighter_GObj* gobj) {}

void ftCo_ThrownB_IASA(Fighter_GObj* gobj) {}

void ftCo_ThrownB_Phys(Fighter_GObj* gobj) {}

void ftCo_ThrownB_Coll(Fighter_GObj* gobj) {}

void ftCo_ThrownHi_IASA(Fighter_GObj* gobj) {}

void ftCo_ThrownHi_Phys(Fighter_GObj* gobj) {}

void ftCo_ThrownHi_Coll(Fighter_GObj* gobj) {}

void ftCo_ThrownLw_IASA(Fighter_GObj* gobj) {}

void ftCo_ThrownLw_Phys(Fighter_GObj* gobj) {}

void ftCo_ThrownLw_Coll(Fighter_GObj* gobj) {}

void ftCo_800DEEA8(Fighter_GObj* gobj)
{
    GET_FIGHTER(gobj)->smash_attrs.state = SmashState_None;
}
