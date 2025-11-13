#ifndef GALE01_081B38
#define GALE01_081B38

#include <placeholder.h>
#include <platform.h>

#include "ft/types.h"

#include "ftCommon/forward.h"
#include <baselib/forward.h>

/* 081B38 */ void ft_80081B38(Fighter_GObj* gobj);
/* 081C88 */ void ft_80081C88(Fighter_GObj* dst_gobj, float scl_y);
/* 081D0C */ GroundOrAir ft_80081D0C(Fighter_GObj* gobj);
/* 081DD4 */ bool ft_80081DD4(Fighter_GObj* gobj);
/* 081F2C */ bool ft_80081F2C(Fighter_GObj* gobj);
/* 082084 */ bool ft_80082084(Fighter_GObj* gobj);
/* 0821DC */ bool ft_800821DC(Fighter_GObj* gobj);
/* 0822A4 */ bool ft_CheckGroundAndLedge(Fighter_GObj* gobj, int direction);
/* 08239C */ bool ft_8008239C(Fighter_GObj* gobj, int facing_direction,
                              ftCollisionBox* height_attributes);
/* 0824A0 */ bool ft_800824A0(Fighter_GObj*, ftCollisionBox*);
/* 082578 */ bool ft_80082578(Fighter_GObj*);
/* 082638 */ bool ft_80082638(Fighter_GObj* gobj, ftCollisionBox*);
/* 082708 */ GroundOrAir ft_80082708(Fighter_GObj* gobj);
/* 0827A0 */ bool ft_800827A0(Fighter_GObj* gobj);
/* 082838 */ ftCollisionBox* ft_80082838(ftCollisionBox*, ftCollisionBox*,
                                         float);
/* 082888 */ bool ft_80082888(Fighter_GObj*, ftCollisionBox*);
/* 082978 */ bool ft_80082978(Fighter_GObj*, ftCollisionBox*);
/* 082A68 */ bool ft_80082A68(Fighter_GObj* gobj);
/* 082B1C */ void ft_80082B1C(Fighter_GObj* gobj);
/* 082B78 */ void ftCo_AirCatchHit_Coll(Fighter_GObj*);
/* 082C74 */ void ft_80082C74(Fighter_GObj* gobj, HSD_GObjEvent);
/* 082D40 */ void ft_80082D40(Fighter_GObj* gobj, float);
/* 082E3C */ Fighter_GObj* ft_80082E3C(Fighter_GObj* gobj);
/* 082F28 */ void ft_80082F28(Fighter_GObj* gobj);
/* 083090 */ void ft_80083090(Fighter_GObj* gobj, bool (*)(Fighter_GObj*, int),
                              HSD_GObjEvent);
/* 0831CC */ void ft_800831CC(Fighter_GObj*, bool (*)(Fighter_GObj*, int),
                              HSD_GObjEvent);
/* 083318 */ void ft_80083318(Fighter_GObj* gobj,
                              bool (*)(Fighter_GObj* gobj, int),
                              HSD_GObjEvent);
/* 083464 */ void ft_80083464(Fighter_GObj* gobj,
                              bool (*)(Fighter_GObj* gobj, int),
                              HSD_GObjEvent);
/* 0835B0 */ void ft_800835B0(Fighter_GObj* gobj,
                              bool (*)(Fighter_GObj* gobj, int),
                              HSD_GObjEvent);
/* 08370C */ void ft_8008370C(Fighter_GObj* gobj, HSD_GObjEvent cb);
/* 083844 */ void ft_80083844(Fighter_GObj* gobj, HSD_GObjEvent cb);
/* 083910 */ UNK_RET ft_80083910(Fighter_GObj* gobj, HSD_GObjEvent cb);
/* 083A48 */ void ft_80083A48(Fighter_GObj* gobj, HSD_GObjEvent cb);
/* 083B68 */ void ft_80083B68(Fighter_GObj* gobj);
/* 083C00 */ void ft_80083C00(Fighter_GObj* gobj, HSD_GObjEvent cb);
/* 083CE4 */ void ft_80083CE4(Fighter_GObj* gobj, bool (*)(Fighter_GObj*, int),
                              HSD_GObjEvent cb2);
/* 083DCC */ void ft_80083DCC(Fighter_GObj* gobj);
/* 083E64 */ void ft_80083E64(Fighter_GObj* gobj, ftCollisionBox* ecb,
                              HSD_GObjEvent cb);
/* 083F88 */ void ft_80083F88(Fighter_GObj* gobj);
/* 08403C */ void ft_8008403C(Fighter_GObj*, HSD_GObjEvent);
/* 084104 */ void ft_80084104(Fighter_GObj* gobj);
/* 0841B8 */ void ft_800841B8(Fighter_GObj* gobj, HSD_GObjEvent cb);
/* 084280 */ void ft_80084280(Fighter_GObj*);
/* 0843FC */ void ft_800843FC(Fighter_GObj* gobj);
/* 0844EC */ void ft_800844EC(Fighter_GObj* gobj);
/* 0845B4 */ void ft_800845B4(Fighter_GObj* gobj);
/* 0846B0 */ void ft_800846B0(Fighter_GObj* gobj, ftCollisionBox* box,
                              HSD_GObjEvent cb);
/* 0847D0 */ void ft_800847D0(Fighter_GObj* gobj, ftCollisionBox*);
/* 0848DC */ void ft_800848DC(Fighter_GObj* gobj, HSD_GObjEvent cb);
/* 0849EC */ void ft_800849EC(Fighter*, Fighter*);
/* 084A18 */ bool ft_80084A18(Fighter_GObj*);
/* 084A40 */ float ft_GetGroundFrictionMultiplier(Fighter* fp);
/* 084A80 */ bool ft_80084A80(int arg0, Fighter_GObj* gobj, int*, int*, int*);
/* 084BFC */ bool ft_80084BFC(Fighter_GObj* gobj, int*, int*, int*);
/* 084C38 */ bool ft_80084C38(Fighter_GObj*, int*, int*, int*);
/* 084C74 */ bool ft_80084C74(Fighter_GObj*, int*, int*, int*);
/* 084CB0 */ void ft_80084CB0(Fighter*, ftCollisionBox*);
/* 084CE4 */ bool ft_80084CE4(Fighter* attacker, Fighter* victim);
/* 084DB0 */ void ft_80084DB0(Fighter_GObj*);
/* 084E1C */ void ft_80084E1C(Fighter_GObj* gobj, float, float, float);
/* 084EEC */ void ft_80084EEC(Fighter_GObj* gobj);
/* 084F3C */ void ft_80084F3C(Fighter_GObj* gobj);
/* 084FA8 */ void ft_80084FA8(Fighter_GObj* gobj);
/* 085004 */ void ft_80085004(Fighter_GObj* gobj);
/* 085030 */ void ft_80085030(Fighter_GObj*, float gr_friction,
                              float facing_dir);
/* 085088 */ void ft_80085088(Fighter_GObj*);
/* 0850B4 */ void ft_800850B4(Fighter_GObj*);
/* 0850E0 */ void ft_800850E0(Fighter_GObj*, float, float);
/* 085134 */ void ft_80085134(Fighter_GObj* gobj);
/* 085154 */ void ft_80085154(Fighter_GObj* gobj);
/* 0851C0 */ void ft_800851C0(Fighter_GObj*);
/* 0851D0 */ void ft_800851D0(Fighter_GObj*);
/* 085204 */ void ft_80085204(Fighter_GObj* gobj);

#endif
