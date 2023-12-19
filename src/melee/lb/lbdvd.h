#ifndef MELEE_LB_LBDVD_H
#define MELEE_LB_LBDVD_H

#include <platform.h>

#include <baselib/archive.h>

void lbDvd_80018F68(void);
void lbDvd_800178E8(s32, char*, s32, s32, s32, s32, s32, s32, s32);
HSD_Archive* lbDvd_8001819C(const char*);
void lbDvd_80017740(int, int, int, int, u32, char, short, char, int);

#endif
