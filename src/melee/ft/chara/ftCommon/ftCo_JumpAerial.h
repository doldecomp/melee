#ifndef GALE01_0CB6EC
#define GALE01_0CB6EC

#include <placeholder.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"

/* 0CB6EC */ void ft_800CB6EC(Fighter* fp, s32 arg1);
/* 0CB804 */ bool ft_did_jump(Fighter* fp, bool);
/* 0CB870 */ bool ftCo_800CB870(Fighter_GObj* gobj);
/* 0CB8E0 */ bool ftCo_800CB8E0(Fighter_GObj* gobj);
/* 0CB950 */ bool ftCo_JumpAerial_CheckInput(Fighter_GObj* gobj, bool);
/* 0CBAC4 */ void ftCo_800CBAC4(Fighter_GObj*, FtMotionId, Vec3*, bool);
/* 0CBBC0 */ void ftCo_JumpAerial_Enter_Basic(Fighter_GObj* gobj);
/* 0CBD18 */ void ftNs_JumpAerial_Enter(Fighter_GObj* gobj);
/* 0CBE98 */ void ftYs_JumpAerial_Enter(Fighter_GObj* gobj);
/* 0CC0E8 */ void ftPe_JumpAerial_Enter(Fighter_GObj* gobj);
/* 0CC238 */ void ftMt_JumpAerial_Enter(Fighter_GObj* gobj);
/* 0CC388 */ void ftCo_JumpAerial_Anim(Fighter_GObj* gobj);
/* 0CC4F8 */ void ftCo_JumpAerial_IASA(Fighter_GObj* gobj);
/* 0CC634 */ void ftCo_JumpAerial_Phys(Fighter_GObj* gobj);
/* 0CC6C8 */ void ftCo_JumpAerial_Phys_Cb(Fighter_GObj* gobj);
/* 0CC700 */ void ftCo_JumpAerial_Coll(Fighter_GObj* gobj);

#endif
