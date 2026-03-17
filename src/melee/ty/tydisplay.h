#ifndef MELEE_TY_DISPLAY_H
#define MELEE_TY_DISPLAY_H

#include <placeholder.h>
#include <platform.h>

struct HSD_GObj;
struct HSD_JObj;

typedef struct TySortElem {
    s32 key;
    f32 val;
} TySortElem;

/* 3182D4 */ void un_803182D4_OnFrame(void);
/* 31830C */ void un_8031830C(TySortElem*, s32, s32);
/* 318714 */ void un_80318714(TySortElem*, s32, s32);
/* 318B1C */ void un_80318B1C(s32 arg0);
/* 318CB4 */ void un_80318CB4(s32);
/* 319540 */ void un_80319540(s32);
/* 319994 */ void un_80319994(s32);
/* 319EF0 */ void un_80319EF0(void);
/* 31A4EC */ void fn_8031A4EC(struct HSD_GObj*);
/* 31A94C */ void fn_8031A94C(struct HSD_GObj*);
/* 31B1FC */ void un_8031B1FC(void);
/* 31B328 */ void un_8031B328(void);
/* 31B460 */ void un_8031B460_OnEnter(void*);
/* 31B850 */ void un_8031B850(void);
/* 31B9A4 */ void un_8031B9A4_OnFrame(void);
/* 31B9DC */ void* un_8031B9DC(s32 id);
/* 31BA78 */ void un_8031BA78(s32, s32, f32);
/* 31BB34 */ s32 un_8031BB34(s8);
/* 31BB94 */ char* un_8031BB94(s8);
/* 31BBF4 */ s32 un_8031BBF4(s8);
/* 31BC54 */ struct HSD_GObj* un_8031BC54(s32);
/* 31BF34 */ void un_8031BF34(s32 arg0);
/* 31C1D0 */ void un_8031C1D0(void);
/* 31C2CC */ void tyDisplay_8031C2CC(void);
/* 31C2EC */ s32 tyDisplay_8031C2EC(void);
/* 31C354 */ s32 un_8031C354(s32, s32 (*)[], s32, s32);
/* 31C454 */ s32 un_8031C454(s32 arg0);
/* 31C5E4 */ struct HSD_JObj* un_8031C5E4(s32);
/* 31C8B8 */ void un_8031C8B8(void);

#endif
