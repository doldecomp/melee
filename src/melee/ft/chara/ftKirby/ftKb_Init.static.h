#ifndef __GALE01_0EE528
#define __GALE01_0EE528

#include "ftkirby.h" // IWYU pragma: export

#include <placeholder.h>

typedef struct ftKirby_CostumeArchive {
    /* +0 */ HSD_Joint* joint;
    /* +4 */ HSD_MatAnimJoint* matanim;
} ftKirby_CostumeArchive;

extern HSD_GObjEvent ftKb_Init_803C9CC8[];
extern HSD_GObjEvent ftKb_Init_803C9DD0[];
extern HSD_GObjEvent ftKb_Init_803C9E54[];
extern ftKirby_CostumeArchive* ftKb_Init_803C9FC8[];
extern char ftKb_Init_assert_msg_0[];
extern char ftKb_Init_assert_msg_1[];
extern char ftKb_Init_assert_msg_2[];

/* 0F6178 */ static void fn_800F6178(Fighter_GObj*);
/* 0F6210 */ static void fn_800F6210(Fighter_GObj*);
/* 0F6280 */ static void fn_800F6280(Fighter_GObj*);
/* 0F6318 */ static void fn_800F6318(Fighter_GObj*);

#endif
