#ifndef GALE01_085560
#define GALE01_085560

#include <platform.h>
#include <placeholder.h>

#include "ft/forward.h"
#include <baselib/forward.h>

#include "ft/types.h"

struct ftData_80086060_arg0 {
    u32 unk0;
    s32 unk4;
    s32 unk8;
    u8 unkC;
    u8 pad[0x20];
    s32 unk2C;
};

/* 085560 */ void ftData_80085560(int idx, int increment);
/* 0855C8 */ void ftData_800855C8(enum_t id, int slot);
/* 08572C */ void ftData_8008572C(s32);
/* 08578C */ void ftData_8008578C(enum_t id, int slot);
/* 0857E0 */ void ftData_800857E0(bool);
/* 085820 */ void ftData_80085820(FighterKind, int costume_id);
/* 0858E4 */ void ftData_800858E4(FighterKind, int costume_id);
/* 0859A8 */ void ftData_800859A8(Fighter*);
/* 085A14 */ void ftData_80085A14(bool);
/* 085B10 */ void ftData_80085B10(Fighter*);
/* 085B98 */ void ftData_80085B98(Fighter*, int, int);
/* 085CD8 */ void ftData_80085CD8(Fighter*, Fighter*, enum_t msid);
/* 085E50 */ lbMthp_8001E8F8_t* ftData_80085E50(Fighter*, enum_t msid);
/* 085FD4 */ struct ftData_80085FD4_ret* ftData_80085FD4(Fighter* fp,
                                                         FtMotionId msid);
/* 086060 */ Fighter* ftData_80086060(struct ftData_80086060_arg0* arg0);
/* 3C10D0 */ extern Event ftData_Table_Unk1[FTKIND_MAX];
/* 3C1154 */ extern HSD_GObjEvent ftData_OnLoad[FTKIND_MAX];
/* 3C11D8 */ extern HSD_GObjEvent ftData_OnDeath[FTKIND_MAX];
/* 3C125C */ extern HSD_GObjEvent ftData_OnUserDataRemove[FTKIND_MAX];
/* 3C13E8 */ extern HSD_GObjEvent ftData_SpecialS[FTKIND_MAX];
/* 3C146C */ extern HSD_GObjEvent ftData_SpecialAirHi[FTKIND_MAX];
/* 3C14F0 */ extern HSD_GObjEvent ftData_SpecialAirLw[FTKIND_MAX];
/* 3C1574 */ extern HSD_GObjEvent ftData_SpecialAirS[FTKIND_MAX];
/* 3C15F8 */ extern HSD_GObjEvent ftData_SpecialAirN[FTKIND_MAX];
/* 3C1808 */ extern HSD_GObjEvent ftData_OnAbsorb[FTKIND_MAX];
/* 3C188C */ extern Fighter_ItemEvent ftData_OnItemPickupExt[FTKIND_MAX];
/* 3C1DB4 */ extern HSD_GObjEvent ftData_UnkMotionStates3[FTKIND_MAX];
/* 3C1E38 */ extern HSD_GObjEvent ftData_UnkMotionStates4[FTKIND_MAX];
/* 3C20CC */ extern Fighter_UnkMtxEvent ftData_UnkMtxFunc0[FTKIND_MAX];
/* 3C2150 */ extern ftData_UnkModelStruct ftData_UnkIntBoolFunc0;
/* 3C2468 */ extern Fighter_DemoStrings* ftData_803C2468[FTKIND_MAX];
/* 3C24EC */ extern Fighter_MotionFileStringGetter ftData_803C24EC[FTKIND_MAX];
/* 3C2570 */ extern Fighter_UnkPtrEvent ftData_UnkDemoCallbacks0[FTKIND_MAX];
/* 3C25F4 */ extern ftData_UnkCountStruct ftData_UnkIntPairs[FTKIND_MAX];
/* 3C26FC */ extern s8 ftData_UnkBytePerCharacter[FTKIND_MAX];
/* 3C2800 */ extern MotionState ftData_MotionStateList[ftCo_MS_Count];
/* 3C52A0 */ extern MotionState ftData_803C52A0[14];

#endif
