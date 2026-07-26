#ifndef MELEE_EF_FORWARD_H
#define MELEE_EF_FORWARD_H

#include <placeholder.h>

typedef struct EF_Effect EF_Effect;
typedef struct EF_QueuedEffect EF_QueuedEffect;
typedef struct EF_EffectDesc EF_EffectDesc;

typedef void (*EF_UpdateFn)(EF_Effect*);

typedef enum EfId {
    /* 0x03E8 */ Ef_Id_Unk1000 = 1000,
    /* 0x03E9 */ Ef_Id_Unk1001,
    /* 0x03EA */ Ef_Id_Unk1002,
    /* 0x03EB */ Ef_Id_Unk1003,
    /* 0x03EC */ Ef_Id_Unk1004,
    /* 0x03ED */ Ef_Id_Unk1005,
    /* 0x0416 */ Ef_Id_Unk1046 = 1046,
    /* 0x0479 */ Ef_Id_Unk1145 = 1145,
    /* 0x04E7 */ Ef_Id_Unk1255 = 1255,
} EfId;

#endif
