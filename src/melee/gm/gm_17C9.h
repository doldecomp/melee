#ifndef MELEE_GM_GM_17C9_H
#define MELEE_GM_GM_17C9_H

#include <placeholder.h>
#include <platform.h>

#include <melee/gm/forward.h>
#include <melee/gr/forward.h>
#include <melee/mn/forward.h>

/* 17C984 */ void gm_8017C984(UNK_T);
/* 17C9A8 */ void gm_8017C9A8(DebugGameOverData*, Unk1PData*, u8);
/* 17CA38 */ UNK_RET gm_8017CA38(DebugGameOverData*, Unk1PData*,
                                 struct gmm_x0_528_t*, u8);
/* 17CBAC */ UNK_RET gm_8017CBAC(UnkAdventureData*, struct gmm_x0_528_t*, u8);
/* 17CD94 */ u8 gm_8017CD94(UnkAdventureData*, int, int, int);
/* 17CE34 */ s32 gm_8017CE34(StartMeleeData*, UnkAdventureData*, s8*, u8, u8,
                             u8, s32, InternalStageId, s32 count, s32);
/* 17D7AC */ bool gm_8017D7AC(MatchExitInfo*, Unk1PData*, u8);
/* 17D9C0 */ s32 fn_8017D9C0(u8*, u8*);
/* 17DB58 */ void gm_8017DB58(struct Unk1PData_x24*);
/* 17DB6C */ u8 gm_8017DB6C(gm_8017DB6C_arg0_t*, int);
/* 17DB78 */ u8 gm_8017DB78(gm_8017DB6C_arg0_t*, int);
/* 17DB88 */ s32 gm_8017DB88(void*, u8, s32, s32, u8*, u8,
                             u8 (*)(s32, s32, u8), u8 (*)(s32, s32, u8),
                             u8 (*)(s32, s32, u8), f32 (*)(s32, s32),
                             f32 (*)(s32, s32));
/* 17DD7C */ s32 fn_8017DD7C(PlayerInitData*, Unk1PData_x24*, u8);
/* 17DE54 */ s32 fn_8017DE54(u8, u8*);
/* 17DEC8 */ Unk1PData* fn_8017DEC8(int);
/* 17DF28 */ Unk1PData* fn_8017DF28(void);
/* 17DF90 */ u8 fn_8017DF90(void);
/* 17DFF4 */ int gm_8017DFF4(int);
/* 17E068 */ bool gm_8017E068(void);
/* 17E0E4 */ int fn_8017E0E4(void);
/* 17E160 */ bool fn_8017E160(void);
/* 17E21C */ void fn_8017E21C(void);
/* 17E280 */ s8 gm_8017E280(u16, u32);
/* 17E318 */ int fn_8017E318(void);
/* 17E3C8 */ void fn_8017E3C8(void);

#endif
