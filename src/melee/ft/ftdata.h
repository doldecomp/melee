#ifndef GALE01_085560
#define GALE01_085560

#include <Runtime/platform.h>

#include <melee/ft/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <melee/ft/types.h>

/* 08521C */ void ft_8008521C(Fighter_GObj* gobj);
/* 0852B0 */ void ft_800852B0(void);
/* 08549C */ void ft_8008549C(void);
/* 085560 */ void ftData_80085560(int idx, int increment);
/* 0855C8 */ void ftData_800855C8(FighterKind kind, u8 color);
/* 08572C */ void ftData_8008572C(FighterKind);
/* 08578C */ void ftData_8008578C(int, u8 color);
/* 0857E0 */ void ftData_800857E0(FighterKind);
/* 085820 */ void ftData_80085820(FighterKind, int costume_id);
/* 0858E4 */ void ftData_800858E4(FighterKind, int costume_id);
/* 0859A8 */ void ftData_800859A8(Fighter*);
/* 085A14 */ void ftData_80085A14(FighterKind);
/* 085B10 */ void ftData_80085B10(Fighter*);
/* 085B98 */ void ftData_80085B98(Fighter*, int, int);
/* 085CD8 */ void ftData_80085CD8(Fighter*, Fighter*, enum_t msid);
/* 085E50 */ FigaTree* ftData_80085E50(Fighter*, enum_t msid);
/* 085FD4 */ struct ftData_80085FD4_ret* ftData_80085FD4(Fighter* fp,
                                                         FtMotionId msid);
/* 086060 */ Fighter* ftData_80086060(Fighter* arg0);
/* 3C0EC0 */ extern struct UnkCostumeList
    CostumeListsForeachCharacter[Ft_Kind_Max];
/* 3C0FC8 */ extern struct ftData_UnkCountStruct ftData_Table_Unk0[Ft_Kind_Max];
/* 3C10D0 */ extern Event ftData_Table_Unk1[Ft_Kind_Max];
/* 3C10D0 */ extern struct ftData_UnkCountStruct
    ftData_UnkIntPairs[Ft_Kind_Max];
/* 3C1154 */ extern HSD_GObjEvent ftData_OnLoad[Ft_Kind_Max];
/* 3C11D8 */ extern HSD_GObjEvent ftData_OnDeath[Ft_Kind_Max];
/* 3C125C */ extern HSD_GObjEvent ftData_OnUserDataRemove[Ft_Kind_Max];
/* 3C13E8 */ extern HSD_GObjEvent ftData_SpecialS[Ft_Kind_Max];
/* 3C146C */ extern HSD_GObjEvent ftData_SpecialAirHi[Ft_Kind_Max];
/* 3C14F0 */ extern HSD_GObjEvent ftData_SpecialAirLw[Ft_Kind_Max];
/* 3C1574 */ extern HSD_GObjEvent ftData_SpecialAirS[Ft_Kind_Max];
/* 3C15F8 */ extern HSD_GObjEvent ftData_SpecialAirN[Ft_Kind_Max];
/* 3C167C */ extern HSD_GObjEvent ftData_SpecialN[Ft_Kind_Max];
/* 3C1700 */ extern HSD_GObjEvent ftData_SpecialLw[Ft_Kind_Max];
/* 3C1784 */ extern HSD_GObjEvent ftData_SpecialHi[Ft_Kind_Max];
/* 3C1808 */ extern HSD_GObjEvent ftData_OnAbsorb[Ft_Kind_Max];
/* 3C188C */ extern Fighter_ItemEvent ftData_OnItemPickupExt[Ft_Kind_Max];
/* 3C1DB4 */ extern HSD_GObjEvent ftData_UnkMotionStates3[Ft_Kind_Max];
/* 3C1E38 */ extern HSD_GObjEvent ftData_UnkMotionStates4[Ft_Kind_Max];
/* 3C20CC */ extern Fighter_UnkMtxEvent ftData_UnkMtxFunc0[Ft_Kind_Max];
/* 3C2150 */ extern ftData_UnkModelStruct ftData_UnkIntBoolFunc0;
/* 3C2468 */ extern Fighter_DemoStrings* ftData_803C2468[Ft_Kind_Max];
/* 3C24EC */ extern Fighter_MotionFileStringGetter ftData_803C24EC[Ft_Kind_Max];
/* 3C2570 */ extern Fighter_UnkPtrEvent ftData_UnkDemoCallbacks0[Ft_Kind_Max];
/* 3C26FC */ extern u8 ftData_UnkBytePerCharacter[Ft_Kind_Max];
/* 3C2800 */ extern MotionState ftData_MotionStateList[ftCo_MS_Count];
/* 3C52A0 */ extern MotionState ftData_803C52A0[14];
/* 4598B8 */ extern ftData* gFtDataList[Ft_Kind_Max];

#endif
