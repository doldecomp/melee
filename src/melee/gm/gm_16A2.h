#ifndef MELEE_GM_16A2_H
#define MELEE_GM_16A2_H

#include <melee/gm/forward.h>
#include <melee/mn/forward.h>
#include <sysdolphin/baselib/forward.h>

struct lbl_8046B488_t* gm_1601_GetUnkData(void);
s8 gm_80169370(s32);
int gm_80169384(void);
s32 gm_80169394(void);
s32 fn_801693A8(void);
bool gm_801693BC(int);
void fn_80169434(GmRouteCallback fn);
bool fn_80169444(bool);
int gm_801694A0(HSD_GObj*);
void* gm_80169520(void);
void* gm_80169530(void);
void* gm_80169540(void);
void fn_80169550(int slot);
void fn_80169574(ssize_t size, s8* buf);
void fn_801697FC(s8, s8, s8, s8, s8*);
void fn_8016989C(u8*, u8, u8, u8*, s8*);
void fn_80169900(u8, struct lbl_8046B488_t*, s8*, s8*);
s32 fn_80169A84(u8, s8*, s8*);
void fn_80169C54(s8, s8);
void fn_80169F50(s8, s8);
void fn_8016A09C(void);
void gm_8016A164(void);
s32 fn_8016A1E4(void);
bool gm_8016A1F8(void);
void gm_8016A21C(StartMeleeRules*);
s32 gm_8016A22C(s8 ckind0, s8 ckind1, s8 ckind2, u8, u8, int, int, int,
                u8 color, u8, u8, int opp_count, int, int, int, int, int, f32,
                f32);
void gm_8016A404(s32 arg0);
void gm_8016A414(f32 arg8);
void gm_8016A424(s8 arg0);
void gm_8016A434(void);
void fn_8016A450(void);
void fn_8016A46C(void);
void fn_8016A488(int);
void fn_8016A4C8(void);
void gm_8016A92C(StartMeleeRules*);
bool gm_8016A944(void);
void* gm_8016A97C(void);
struct lbl_8046B668_t* gm_8016A98C(void);
int gm_8016A998(s8, s8);
int gm_8016A9E8(u8 arg0, s8 arg1);
bool gm_8016AC44(s8 ckind, s8 costume_id);

#endif
