#ifndef MELEE_GM_16F1_H
#define MELEE_GM_16F1_H

#include <placeholder.h>

#include <melee/ft/forward.h>
#include <melee/gm/forward.h>
#include <sysdolphin/baselib/forward.h>

typedef enum Gm_DecType {
    Gm_DecType_Flag,  ///< true/false boolean player bonus
    Gm_DecType_Point, ///< integer-valued player bonus
} Gm_DecType;

struct lbl_804D65A8_t;

/* 16F180 */ int fn_8016F180(int);
/* 16F1B8 */ Gm_DecType gmDecisionGetType(int kind);
/* 16F1F0 */ short fn_8016F1F0(int idx);
/* 16F208 */ int gm_8016F208(int);
/* 16F280 */ int fn_8016F280(int);
/* 16F2F8 */ int gm_8016F2F8(int, unsigned char);
/* 16F344 */ void fn_8016F344(struct lbl_8046B6A0_24C_t*);
/* 16F39C */ UNK_RET fn_8016F39C(UNK_PARAMS);
/* 16F548 */ UNK_RET fn_8016F548(UNK_PARAMS);
/* 16F740 */ UNK_RET fn_8016F740(UNK_PARAMS);
/* 16F870 */ UNK_RET fn_8016F870(UNK_PARAMS);
/* 16F9A8 */ UNK_RET fn_8016F9A8(UNK_PARAMS);
/* 16FAD4 */ int fn_8016FAD4(UNK_T, u16, int, u8);
/* 16FFD4 */ UNK_RET fn_8016FFD4(UNK_PARAMS);
/* 170110 */ int fn_80170110(UNK_T, int, int, u8);
/* 1701A0 */ UNK_RET gm_801701A0(UNK_PARAMS);
/* 1701AC */ UNK_RET fn_801701AC(UNK_PARAMS);
/* 1701B8 */ int fn_801701B8(void);
/* 1701C0 */ UNK_RET fn_801701C0(UNK_PARAMS);
/* 171A88 */ int fn_80171A88(void);
/* 171AD4 */ UNK_RET fn_80171AD4(UNK_PARAMS);
/* 171B00 */ bool fn_80171B00(int);
/* 171B2C */ bool fn_80171B2C(int);
/* 171B64 */ UNK_RET fn_80171B64(struct lbl_804D65A8_t*);
/* 171BA4 */ UNK_RET fn_80171BA4(UNK_PARAMS);
/* 171DC4 */ void fn_80171DC4(HSD_GObj*);
/* 1720B4 */ int gm_801720B4(void);
/* 1720F8 */ int gm_801720F8(void);
/* 172140 */ int gm_80172140(UNK_PARAMS);
/* 172174 */ UNK_RET gm_80172174(UNK_PARAMS);
/* 17219C */ bool gm_8017219C(u32);
/* 1721EC */ bool gm_801721EC(void);
/* 1722BC */ bool fn_801722BC(void);
/* 1722F4 */ bool fn_801722F4(void);
/* 17232C */ bool fn_8017232C(void);
/* 172380 */ bool fn_80172380(void);
/* 1723D4 */ bool fn_801723D4(void);
/* 172428 */ bool fn_80172428(void);
/* 172478 */ bool fn_80172478(void);
/* 1724C8 */ bool fn_801724C8(void);
/* 1724D0 */ bool fn_801724D0(void);
/* 172504 */ bool fn_80172504(void);
/* 172538 */ bool fn_80172538(void);
/* 17256C */ bool fn_8017256C(void);
/* 1725A8 */ bool fn_801725A8(void);
/* 1725E4 */ bool fn_801725E4(void);
/* 172624 */ bool fn_80172624(void);
/* 172664 */ bool fn_80172664(void);
/* 172698 */ bool fn_80172698(void);
/* 1726CC */ bool fn_801726CC(void);
/* 172700 */ bool fn_80172700(void);
/* 172734 */ bool fn_80172734(void);
/* 172768 */ bool fn_80172768(void);
/* 17279C */ bool fn_8017279C(int, u16);
/* 17280C */ UNK_RET fn_8017280C(UNK_PARAMS);
/* 172898 */ int gm_80172898(u16);
/* 17297C */ UNK_RET gm_8017297C(UNK_PARAMS);
/* 1729EC */ UNK_RET gm_801729EC(UNK_PARAMS);
/* 172BC4 */ bool gm_80172BC4(void);
/* 172C04 */ bool gm_80172C04(void);
/* 172C44 */ UNK_RET gm_80172C44(u32);
/* 172C78 */ bool fn_80172C78(int);
/* 172CC0 */ u8 gm_80172CC0(u8, u8); ///< returns a CPU level
/* 172D78 */ u8 gm_80172D78(void);
/* 172DD4 */ u8 gm_80172DD4(u32);
/* 172E74 */ u8 gm_80172E74(void);
/* 172F00 */ u16 gm_80172F00(u32);
/* 172FAC */ bool fn_80172FAC(void);
/* 173098 */ u8 fn_80173098(int);
/* 173224 */ u8 gm_80173224(int, int);
/* 1732D8 */ CharacterKind gm_801732D8(u8);
/* 17335C */ int gm_8017335C(void);
/* 1733D8 */ u8 gm_801733D8(void);
/* 17341C */ u16 gm_8017341C(void);
/* 173460 */ u8 gm_80173460(s8);
/* 173498 */ u16 gm_80173498(UNK_PARAMS);
/* 1734D0 */ u16 gm_801734D0(u32);
/* 173510 */ bool fn_80173510(void);
/* 1735F0 */ bool fn_801735F0(void);
/* 173644 */ bool fn_80173644(void);
/* 17367C */ bool fn_8017367C(void);
/* 1736DC */ lbl_8046DBD8_t* gm_801736DC(void);
/* 1736E8 */ void gm_801736E8(u8, u8, u8, u8, u8, u8);
/* 173754 */ bool gm_80173754(s8, u8);
/* 1737D8 */ u8 gm_801737D8(void);
/* 1737E8 */ void gm_801737E8_OnLoad(void);
/* 173834 */ UNK_RET fn_80173834(u8 ckind, u8 major, bool);
/* 17390C */ UNK_RET gm_8017390C(int, int);
/* 173AA4 */ UNK_RET gm_80173AA4(UNK_PARAMS);
/* 173B30 */ UNK_RET gm_80173B30(u32);
/* 173BC4 */ UNK_RET gm_80173BC4(s8);
/* 173C70 */ UNK_RET gm_80173C70(s8 c_kind, u32, u32, int);
/* 173D3C */ UNK_RET gm_80173D3C(int);
/* 173DE4 */ UNK_RET gm_80173DE4(MatchEnd*);
/* 173EEC */ UNK_RET gm_80173EEC(UNK_PARAMS);
/* 174180 */ UNK_RET gm_80174180(UNK_PARAMS);
/* 1741FC */ UNK_RET gm_801741FC(UNK_PARAMS);
/* 174238 */ UNK_RET gm_80174238(UNK_PARAMS);

#endif
