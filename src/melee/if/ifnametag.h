#ifndef _IFNAMETAG_H_
#define _IFNAMETAG_H_

#include <platform.h>

#include "baselib/forward.h"

#define NAMETAG_DISABLED 120

/* 2FC9B4 */ float un_802FC9B4(unsigned char slot, unsigned char arg1,
                               unsigned char arg2, unsigned char arg3);
/* 2FCAC4 */ void fn_802FCAC4(HSD_GObj* gobj, int pass);
/* 2FCBA0 */ void un_802FCBA0(void);
/* 2FCC44 */ void fn_802FCC44(HSD_GObj* gobj);
/* 2FCF38 */ void NameTag_Create(int slot);
/* 2FD28C */ void un_802FD28C(int slot);
/* 2FD404 */ void un_802FD404(void);
/* 2FD428 */ void un_802FD428(void);
/* 2FD450 */ void un_802FD450(void);
/* 2FD45C */ void un_802FD45C(void);
/* 2FD468 */ void un_802FD468(void);
/* 2FD4C8 */ void un_802FD4C8(void);

#endif
