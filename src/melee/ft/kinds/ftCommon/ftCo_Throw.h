#ifndef MELEE_FTCO_THROW_H
#define MELEE_FTCO_THROW_H

#include "ft/forward.h"

/* 0DC8D8 */ void fn_800DC8D8(Fighter_GObj* gobj);
/* 0DC8FC */ void fn_800DC8FC(Fighter_GObj* gobj);
/* 0DC920 */ void ftCo_800DC920(Fighter_GObj*, Fighter_GObj* gobj);
/* 0DCE34 */ void ftCo_800DCE34(Fighter_GObj* gobj0, Fighter_GObj* gobj1);
/* 0DCFD4 */ void ftCo_800DCFD4(Fighter_GObj* gobj);
/* 0DD100 */ void ftCo_800DD100(Fighter_GObj*);
/* 0DD168 */ void ftCo_800DD168(Fighter_GObj* gobj);
/* 0DD1E4 */ bool ftCo_800DD1E4(Fighter_GObj* gobj);
/* 0DD398 */ void ftCo_800DD398(Fighter_GObj* gobj, FtMotionId msid,
                                FtMotionId victim_msid, float anim_speed);
/* 0DD4B0 */ void ftCo_800DD4B0(Fighter_GObj* gobj, FtMotionId msid);
/* 0DD724 */ void ftCo_800DD724(Fighter_GObj* gobj);
/* 0DD8C4 */ void ftCo_ThrowF_Anim(Fighter_GObj* gobj);
/* 0DD92C */ void ftCo_ThrowF_IASA(Fighter_GObj* gobj);
/* 0DD930 */ void ftCo_ThrowF_Phys(Fighter_GObj* gobj);
/* 0DD990 */ void ftCo_ThrowF_Coll(Fighter_GObj* gobj);
/* 0DDA10 */ void ftCo_ThrowB_Anim(Fighter_GObj* gobj);
/* 0DDA5C */ void ftCo_ThrowB_IASA(Fighter_GObj* gobj);
/* 0DDA60 */ void ftCo_ThrowB_Phys(Fighter_GObj* gobj);
/* 0DDAC0 */ void ftCo_ThrowB_Coll(Fighter_GObj* gobj);
/* 0DDB40 */ void ftCo_ThrowHi_Anim(Fighter_GObj* gobj);
/* 0DDB8C */ void ftCo_ThrowHi_IASA(Fighter_GObj* gobj);
/* 0DDB90 */ void ftCo_ThrowHi_Phys(Fighter_GObj* gobj);
/* 0DDBF0 */ void ftCo_ThrowHi_Coll(Fighter_GObj* gobj);
/* 0DDC70 */ void ftCo_ThrowHi_Cam(Fighter_GObj* gobj);
/* 0DDCB4 */ void ftCo_ThrowLw_Anim(Fighter_GObj* gobj);
/* 0DDD00 */ void ftCo_ThrowLw_IASA(Fighter_GObj* gobj);
/* 0DDD04 */ void ftCo_ThrowLw_Phys(Fighter_GObj* gobj);
/* 0DDD64 */ void ftCo_ThrowLw_Coll(Fighter_GObj* gobj);
/* 0DDDE4 */ void ftCo_800DDDE4(Fighter_GObj* gobj, Fighter_GObj* gobj2,
                                bool arg);
/* 0DE2A8 */ void ftCo_800DE2A8(Fighter_GObj*, Fighter_GObj* gobj);
/* 0DE2CC */ void ftCo_800DE2CC(Fighter_GObj*, Fighter_GObj*);
/* 0DE2F0 */ void ftCo_800DE2F0(Fighter_GObj* gobj);
/* 105FEC */ void fn_80105FEC(HSD_GObj* gobj);

#endif
