#ifndef MELEE_GM_17C0_H
#define MELEE_GM_17C0_H

#include <placeholder.h>
#include <platform.h>

#include "ft/forward.h"
#include <melee/gm/forward.h>
#include <melee/gr/forward.h>
#include <melee/mn/forward.h>
#include <sysdolphin/baselib/forward.h>

/* 17C0C8 */ void fn_8017C0C8(void);
/* 17C1A4 */ void fn_8017C1A4(HSD_GObj*);
/* 17C71C */ void fn_8017C71C(void);
/* 17C7A0 */ void fn_8017C7A0(void);
/* 17C7EC */ void fn_8017C7EC(void);
/* 17C838 */ void gm_8017C838(void);
/* 17C984 */ void gm_8017C984(UNK_T);
/* 17C9A8 */ void gm_8017C9A8(DebugGameOverData*, Unk1PData*, u8);
/* 17CA38 */ UNK_RET gm_8017CA38(DebugGameOverData*, Unk1PData*,
                                 struct gmm_x0_528_t*, u8);
/* 17CBAC */ UNK_RET gm_8017CBAC(UnkAdventureData*, struct gmm_x0_528_t*, u8);
/* 17CD94 */ u8 gm_8017CD94(UnkAdventureData*, int, int, int);
/* 17CE34 */ void gm_8017CE34(StartMeleeData*, UnkAdventureData*, s8*, u8, u8,
                              u8, s32, StKind, s32 count, s32);
/* 17D7AC */ bool gm_8017D7AC(MatchExitInfo*, Unk1PData*, u8);
/* 17D9C0 */ s32 fn_8017D9C0(const u8* used_ckinds, const u8* preset_ckinds);
/* 17DB58 */ void gm_8017DB58(struct Unk1PData_x24* arg0);
/* 17DB6C */ u8 gm_8017DB6C(gm_8017DB6C_arg0_t* arg0, int index);
/* 17DB78 */ u8 gm_8017DB78(gm_8017DB6C_arg0_t* arg0, int index);
/* 17DB88 */ s32 gm_8017DB88(void* arg0, u8 arg1, s32 arg2, s32 arg3, u8* arg4,
                             u8 arg5, u8 (*arg6)(s32, s32, u8),
                             u8 (*arg7)(s32, s32, u8),
                             u8 (*arg8)(s32, s32, u8), f32 (*arg9)(s32, s32),
                             f32 (*arg10)(s32, s32));
/* 17DD7C */ s32 fn_8017DD7C(PlayerInitData* arg0, Unk1PData_x24* arg1,
                             u8 arg2);
/* 17DE54 */ s32 fn_8017DE54(u8, u8*);
/* 17DEC8 */ Unk1PData* fn_8017DEC8(int);
/* 17DF28 */ Unk1PData* fn_8017DF28(void);
/* 17DF90 */ u8 fn_8017DF90(void);
/* 17DFF4 */ int gm_8017DFF4(int);
/* 17E068 */ int gm_8017E068(void);
/* 17E0E4 */ int fn_8017E0E4(void);
/* 17E160 */ bool fn_8017E160(void);
/* 17E21C */ void fn_8017E21C(void);
/* 17E280 */ s8 gm_8017E280(u16, u32);
/* 17E318 */ int fn_8017E318(void);
/* 17E3C8 */ void fn_8017E3C8(void);

#endif
