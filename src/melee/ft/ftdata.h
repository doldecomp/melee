#ifndef MELEE_FT_FTDATA_H
#define MELEE_FT_FTDATA_H

#include <ctypes.h>
#include <melee/ft/enums.h>

typedef struct _HSD_GObj HSD_GObj;
typedef struct _Fighter Fighter;

void func_80085A14(u32);
unk_t func_80085B98();
unk_t func_800858E4();
extern void (*lbl_803C20CC[66])(HSD_GObj*, s32, void*);
extern unk_t lbl_803C1364;
extern unk_t lbl_803C2570;
extern unk_t lbl_803C52A0;
extern unk_t lbl_803C2468;
extern unk_t lbl_803C25F4;
extern unk_t lbl_803C24EC;
extern unk_t lbl_803C1E38;
void func_800855C8(s32 id, s32 slot);
void func_8008572C(u32);
void func_8008578C(s32 id, s32 slot);
void func_800857E0(u32);
void func_80085820(FighterKind kind, s32 costume_id);
void func_800859A8(Fighter* fp);

#endif
