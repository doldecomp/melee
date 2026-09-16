#ifndef GALE01_019880
#define GALE01_019880

#include <Runtime/platform.h>

#include <melee/lb/lbcardnew.h>

typedef enum {
    LbCardStatus_0,
    LbCardStatus_1,
    LbCardStatus_2,
    LbCardStatus_3,
    LbCardStatus_4,
} LbCardStatus;

/* 01C600 */ void lb_8001C600(void);
/* 01C87C */ u32 lb_8001C87C(void);
/* 01C8BC */ int lb_8001C8BC(void);
/* 01CBAC */ void lbCardGame_SetCardStatus(LbCardStatus status);
/* 01CBBC */ lbCardResult lb_8001CBBC(void);
/* 01CC30 */ void fn_8001CC30(bool);
/* 01CC4C */ int lb_8001CC4C(void);
/* 01CC84 */ void lb_8001CC84(void);
/* 01CDB4 */ void lb_8001CDB4(void);
/* 01CE00 */ void lbCardGame_UpdatePowerTime(void);
/* 01CE78 */ u8 lbCardGame_DecideGameMode(void);
/* 01CF18 */ void lbCardGame_InitScene(void);
/* 01D164 */ void lbCardGame_LoadArchive(int);
/* 01D1F4 */ void lbCardGame_Reset(void);
/* 01D21C */ void lbCardGame_Init(void);

#endif
