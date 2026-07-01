#ifndef GALE01_305058
#define GALE01_305058

#include <platform.h>

#include "sc/forward.h"

#include "ty/types.h"

#include <baselib/forward.h>

/* 304870 */ int Toy_GetTrophyTotal(void);
/* 3048C0 */ s32 Toy_803048C0(int);
/* 304924 */ bool Toy_80304924(int);
/* 304988 */ void Toy_80304988(int);
/* 3049F4 */ bool Toy_803049F4(int);
/* 304A58 */ void Toy_80304A58(int);
/* 304B0C */ bool Toy_80304B0C(int);
/* 304B94 */ int Toy_80304B94(int);
/* 304CC8 */ bool Toy_80304CC8(int);
/* 304D30 */ int _Toy_80304D30(void);
/* 305058 */ s32 Toy_80305058(s32, s32, s32, f32);
/* 30562C */ void Toy_SetUnlockState(enum_t, bool);
/* 305918 */ void Toy_80305918(signed char, long, long);
/* 305B88 */ s32 Toy_80305B88(void);
/* 305C44 */ s32 Toy_80305C44(void);
/* 305D00 */ float Toy_80305D00(void);
/* 305DB0 */ float Toy_80305DB0(void);
/* 305EB4 */ float Toy_80305EB4(void);
/* 305FB8 */ float Toy_80305FB8(void);
/* 3060BC */ float Toy_803060BC(int, int);
/* 3062BC */ s16 Toy_803062BC(s32 trophyId);
/* 3063D4 */ s32 Toy_803063D4(s32, s32, s32);
/* 3067BC */ void Toy_803067BC(s32, s32);
/* 3068E0 */ void Toy_803068E0(HSD_GObj* gobj, int);
/* 306930 */ void Toy_80306930(HSD_GObj*, int);
/* 306954 */ void Toy_80306954(HSD_GObj* gobj, int);
/* 306A48 */ void Toy_80306A48(HSD_JObj*, char*, char*, char*, HSD_Archive*,
                               long);
/* 306B18 */ HSD_GObjProc* Toy_80306B18(HSD_GObj* gobj, s32 anim_frame,
                                        s32 val1, s32 val2);
/* 306BB8 */ void Toy_80306BB8(HSD_GObj* gobj);
/* 306CF4 */ void Toy_RemoveUserData(void* ptr);
/* 306D14 */ void Toy_80306D14(void);
/* 306D70 */ void Toy_80306D70(s32 arg0);
/* 306EEC */ HSD_LObj* Toy_LoadLObjList(LightList**, s32*);
/* 307470 */ void Toy_80307470(s32);
/* 307E84 */ void Toy_80307E84(HSD_GObj* gobj);
/* 30813C */ char* Toy_8030813C(s32 arg0, enum_t unused);
/* 308250 */ void Toy_80308250(u8* arg0, s32 arg1, s32 arg2);
/* 3082F8 */ s32 Toy_803082F8(s16 idx);
/* 308328 */ void Toy_80308328(s32 arg0);
/* 308354 */ s32 Toy_80308354(s16 idx);
/* 3083D8 */ void Toy_803083D8(HSD_JObj* jobj, s32 arg1);
/* 3087F4 */ HSD_GObj* Toy_803087F4(void*);
/* 3102D0 */ void Toy_803102D0(void);
/* 310324 */ void Toy_80310324(void);
/* 310660 */ void Toy_80310660(s32 arg0);
/* 311680 */ void Toy_80311680(void);
/* 311960 */ void Toy_80311960(void);
/* 311AB0 */ void Toy_OnEnter_80311AB0(void*);
/* 312018 */ void Toy_OnFrame_80312018(void);
/* 3122D0 */ void Toy_OnInit_803122D0(void);
/* 31234C */ void Toy_8031234C(s32);
/* 3124BC */ void Toy_803124BC(void);
/* 31263C */ void Toy_8031263C(void);
/* 3127D4 */ void Toy_803127D4(void);
/* 3FE5E8 */ extern char Toy_str_ScMenFigure_cam_int1_camera[];
/* 4A284C */ extern unsigned short Toy_804A284C[302];
/* 4A2AA8 */ extern ToyAnimState Toy_804A2AA8;
/* 4D6EAC */ extern TyDspEntry* Toy_sbss_804D6EAC;
/* 4D6EB0 */ extern TyDspEntry* Toy_sbss_804D6EB0;
/* 4D6EC8 */ extern HSD_Archive* Toy_sbss_804D6EC8;
/* 4D6ED4 */ extern ToyCameraControl* Toy_sbss_804D6ED4;
/* 4D6ED8 */ extern ToyED8Data* Toy_sbss_804D6ED8;
/* 4D6EDC */ extern s16* Toy_sbss_804D6EDC;
/* 4D6EE0 */ extern TyDisplayData* Toy_sbss_804D6EE0;

#endif
