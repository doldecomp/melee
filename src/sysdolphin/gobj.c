#include "gobj.h"

#ifdef NON_MATCHING
BOOL func_80390C5C(HSD_GObj* gobj)
{
    HSD_GObjProc* p = gobj->proc;
    while (p != NULL) {
        p->flags = (p->flags & 0x7F) | 0x80;
        p = p->child;
    }
    return TRUE;
}
#else
asm BOOL func_80390C5C(HSD_GObj* gobj)
{
    nofralloc
    /* 80390C5C 0038D83C  80 83 00 18 */	lwz r4, 0x18(r3)
    /* 80390C60 0038D840  38 60 00 01 */	li r3, 1
    /* 80390C64 0038D844  48 00 00 14 */	b lbl_80390C78
lbl_80390C68:
    /* 80390C68 0038D848  88 04 00 0D */	lbz r0, 0xd(r4)
    /* 80390C6C 0038D84C  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
    /* 80390C70 0038D850  98 04 00 0D */	stb r0, 0xd(r4)
    /* 80390C74 0038D854  80 84 00 00 */	lwz r4, 0(r4)
lbl_80390C78:
    /* 80390C78 0038D858  28 04 00 00 */	cmplwi r4, 0
    /* 80390C7C 0038D85C  40 82 FF EC */	bne lbl_80390C68
    /* 80390C80 0038D860  4E 80 00 20 */	blr 
}
#endif

#ifdef NON_MATCHING
BOOL func_80390C84(HSD_GObj* gobj)
{
    HSD_GObjProc* p = gobj->proc;
    while (p != NULL) {
        p->flags = (p->flags & 0x7F);
        p = p->child;
    }
    return FALSE;
}
#else
asm BOOL func_80390C84(HSD_GObj* gobj)
{
    nofralloc
    /* 80390C84 0038D864  80 83 00 18 */	lwz r4, 0x18(r3)
    /* 80390C88 0038D868  38 60 00 00 */	li r3, 0
    /* 80390C8C 0038D86C  48 00 00 14 */	b lbl_80390CA0
lbl_80390C90:
    /* 80390C90 0038D870  88 04 00 0D */	lbz r0, 0xd(r4)
    /* 80390C94 0038D874  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
    /* 80390C98 0038D878  98 04 00 0D */	stb r0, 0xd(r4)
    /* 80390C9C 0038D87C  80 84 00 00 */	lwz r4, 0(r4)
lbl_80390CA0:
    /* 80390CA0 0038D880  28 04 00 00 */	cmplwi r4, 0
    /* 80390CA4 0038D884  40 82 FF EC */	bne lbl_80390C90
    /* 80390CA8 0038D888  4E 80 00 20 */	blr 
}
#endif
