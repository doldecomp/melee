#ifndef FT_CHARA_FTMASTERHAND___FTMASTERHAND_H
#define FT_CHARA_FTMASTERHAND___FTMASTERHAND_H

#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

#include <melee/ft/ftbosslib.h>

typedef void (*GObjCallback)(HSD_GObj* fighter_gobj);

void ftMasterHand_80154A78(HSD_GObj* fighter_gobj);
void ftMasterHand_80154C78(HSD_GObj* fighter_gobj);
void ftMasterHand_80154CF8(HSD_GObj* fighter_gobj, Fighter* fp);
void ftMasterHand_80154E78(HSD_GObj* fighter_gobj);
void ftMasterHand_80155014(HSD_GObj* fighter_gobj);
void ftMasterHand_80150DC4(HSD_GObj* fighter_gobj, GObjCallback, Vec3*);
void ftMasterHand_80150230(HSD_GObj* fighter_gobj);
void ftMasterHand_801510B0(HSD_GObj* fighter_gobj);
void ftMasterHand_80151CA8(HSD_GObj* fighter_gobj);
void ftMasterHand_80152370(HSD_GObj* fighter_gobj); // 11 Punch
void ftMasterHand_80152880(HSD_GObj* fighter_gobj);
void ftMasterHand_801530A4(HSD_GObj* fighter_gobj);
void ftMasterHand_80153820(HSD_GObj* fighter_gobj);
void ftMasterHand_80153A64(HSD_GObj* fighter_gobj);
void ftMasterHand_801541C8(HSD_GObj* fighter_gobj, GObjCallback);
void ftMasterHand_801542E0(HSD_GObj* fighter_gobj);
void ftMasterHand_801546D8(HSD_GObj* fighter_gobj);
void ftMasterHand_80155B80(HSD_GObj* fighter_gobj);
void ftMasterHand_8015483C(HSD_GObj* fighter_gobj);
void ftMasterHand_80155C94(HSD_GObj* fighter_gobj);
void ftMasterHand_80155D1C(HSD_GObj* interacted_gobj);
void ftMasterHand_80155D6C(HSD_GObj* interacted_gobj, s32 unused_arg);
void ftMasterHand_8014FFDC(HSD_GObj* fighter_gobj);
void ftMasterHand_8015082C(HSD_GObj* fighter_gobj);
void ftMasterHand_80150870(HSD_GObj* fighter_gobj);
void ftMasterHand_801515B8(HSD_GObj* fighter_gobj);
void ftMasterHand_801516B4(HSD_GObj* fighter_gobj);
u32 ftMasterHand_80151428(Vec* vec);
void ftMasterHand_801517B0(HSD_GObj* fighter_gobj);
void ftMasterHand_801517F4(HSD_GObj* fighter_gobj);
void ftMasterHand_80151824(void);
void ftMasterHand_80151828(HSD_GObj*); // 6 Stage Wide Slap
void ftMasterHand_80151874(HSD_GObj* fighter_gobj);
void ftMasterHand_801518B0(HSD_GObj* fighter_gobj);
void ftMasterHand_801518F4(HSD_GObj* fighter_gobj);
void ftMasterHand_80151914(void);
void ftMasterHand_8015198C(HSD_GObj* fighter_gobj);
void ftMasterHand_80151A44(HSD_GObj* fighter_gobj);
void ftMasterHand_80151A88(HSD_GObj* fighter_gobj);
void ftMasterHand_80151AC4(void);
void ftMasterHand_80151B14(HSD_GObj* fighter_gobj);
void ftMasterHand_80151B50(HSD_GObj* fighter_gobj);
void ftMasterHand_80151B70(HSD_GObj* fighter_gobj);
void ftMasterHand_80151BB4(void);
void ftMasterHand_80151BB8(HSD_GObj* fighter_gobj); // 7 Sweep
void ftMasterHand_80151C04(HSD_GObj* fighter_gobj);
void ftMasterHand_80151C40(HSD_GObj* fighter_gobj);
void ftMasterHand_80151C84(HSD_GObj* fighter_gobj);
void ftMasterHand_80151D20(HSD_GObj* fighter_gobj);
void ftMasterHand_80151CA4(void);
void ftMasterHand_80151D5C(HSD_GObj* fighter_gobj);
void ftMasterHand_80151DA0(HSD_GObj* fighter_gobj);
void ftMasterHand_80151DC0(void);
void ftMasterHand_80151DC4(HSD_GObj* fighter_gobj); // 9 Walk
void ftMasterHand_80151E10(HSD_GObj* fighter_gobj);
void ftMasterHand_80151E4C(HSD_GObj* fighter_gobj);
void ftMasterHand_80151E90(HSD_GObj* fighter_gobj);
void ftMasterHand_80151EB0(void);
void ftMasterHand_8015204C(HSD_GObj* fighter_gobj);
void ftMasterHand_80152090(HSD_GObj* fighter_gobj);
void ftMasterHand_801520D4(void);
void ftMasterHand_80152138(HSD_GObj* fighter_gobj);
void ftMasterHand_80152174(HSD_GObj* fighter_gobj);
void ftMasterHand_801521B8(HSD_GObj* fighter_gobj);
void ftMasterHand_801521D8(void);
void ftMasterHand_801521DC(HSD_GObj* fighter_gobj); // 10 Drill
void ftMasterHand_8015223C(HSD_GObj* fighter_gobj);
void ftMasterHand_80152278(HSD_GObj* fighter_gobj);
void ftMasterHand_801522BC(HSD_GObj* fighter_gobj);
void ftMasterHand_8015236C(void);
void ftMasterHand_801523BC(HSD_GObj* fighter_gobj);
void ftMasterHand_80152414(HSD_GObj* fighter_gobj);
void ftMasterHand_80152458(HSD_GObj* fighter_gobj);
void ftMasterHand_80152478(HSD_GObj* fighter_gobj);
void ftMasterHand_801524C8(HSD_GObj* fighter_gobj);
void ftMasterHand_80152544(HSD_GObj* fighter_gobj);
void ftMasterHand_80152588(HSD_GObj* fighter_gobj);
void ftMasterHand_801525DC(HSD_GObj* fighter_gobj);
void ftMasterHand_80152634(HSD_GObj* fighter_gobj);
void ftMasterHand_80152670(HSD_GObj* fighter_gobj);
void ftMasterHand_801526B4(HSD_GObj* fighter_gobj);
void ftMasterHand_801526D4(HSD_GObj* fighter_gobj);
void ftMasterHand_801526D8(HSD_GObj* fighter_gobj); // 12 Ground Slap
void ftMasterHand_80152738(HSD_GObj* fighter_gobj);
void ftMasterHand_80152774(HSD_GObj* fighter_gobj);
void ftMasterHand_801527B8(HSD_GObj* fighter_gobj);
void ftMasterHand_8015287C(HSD_GObj* fighter_gobj);
void ftMasterHand_80152928(HSD_GObj* fighter_gobj);
void ftMasterHand_801529D0(HSD_GObj* fighter_gobj);
void ftMasterHand_80152A0C(HSD_GObj* fighter_gobj);
void ftMasterHand_80152A50(HSD_GObj* fighter_gobj);
void ftMasterHand_80152BC8(HSD_GObj* fighter_gobj);
void ftMasterHand_80152BCC(HSD_GObj* fighter_gobj); // 14 Lasers
void ftMasterHand_80152C34(HSD_GObj* fighter_gobj);
void ftMasterHand_80152C70(HSD_GObj* fighter_gobj);
void ftMasterHand_80152CB4(HSD_GObj* fighter_gobj);
void ftMasterHand_80152CD4(HSD_GObj* fighter_gobj);
void ftMasterHand_80152D44(HSD_GObj* fighter_gobj);
void ftMasterHand_80152DC0(HSD_GObj* fighter_gobj);
void ftMasterHand_80152E04(HSD_GObj* fighter_gobj);
void ftMasterHand_80152E24(HSD_GObj* fighter_gobj);
void ftMasterHand_80153000(HSD_GObj* fighter_gobj);
void ftMasterHand_8015303C(HSD_GObj* fighter_gobj);
void ftMasterHand_80153080(HSD_GObj* fighter_gobj);
void ftMasterHand_801530A0(HSD_GObj* fighter_gobj);
void ftMasterHand_80153160(HSD_GObj* fighter_gobj);
void ftMasterHand_80153210(HSD_GObj* fighter_gobj);
void ftMasterHand_80153254(HSD_GObj* fighter_gobj);
void ftMasterHand_801533C8(HSD_GObj* fighter_gobj);
void ftMasterHand_8015346C(HSD_GObj* fighter_gobj);
void ftMasterHand_80153548(HSD_GObj* fighter_gobj);
void ftMasterHand_8015358C(HSD_GObj* fighter_gobj);
void ftMasterHand_801535AC(HSD_GObj* fighter_gobj);
void ftMasterHand_8015377C(HSD_GObj* fighter_gobj);
void ftMasterHand_801537B8(HSD_GObj* fighter_gobj);
void ftMasterHand_801537FC(HSD_GObj* fighter_gobj);
void ftMasterHand_8015381C(HSD_GObj* fighter_gobj);
void ftMasterHand_8015386C(HSD_GObj* fighter_gobj);
void ftMasterHand_801538A8(HSD_GObj* fighter_gobj);
void ftMasterHand_801538EC(HSD_GObj* fighter_gobj);
void ftMasterHand_8015390C(HSD_GObj* fighter_gobj);
void ftMasterHand_801539A4(HSD_GObj* fighter_gobj);
void ftMasterHand_801539EC(HSD_GObj* fighter_gobj);
void ftMasterHand_80153A30(HSD_GObj* fighter_gobj);
void ftMasterHand_80153A60(HSD_GObj* fighter_gobj);
void ftMasterHand_80153AEC(HSD_GObj* fighter_gobj);
void ftMasterHand_80153B28(HSD_GObj* fighter_gobj);
void ftMasterHand_80153B6C(HSD_GObj* fighter_gobj);
void ftMasterHand_80153B8C(HSD_GObj* fighter_gobj);
void ftMasterHand_80153B90(HSD_GObj* fighter_gobj); // 19 Ram
void ftMasterHand_80153C48(HSD_GObj* fighter_gobj);
void ftMasterHand_80153C90(HSD_GObj* fighter_gobj);
void ftMasterHand_80153CD4(HSD_GObj* fighter_gobj);
void ftMasterHand_80153D28(HSD_GObj* fighter_gobj);
void ftMasterHand_80153D2C(HSD_GObj* fighter_gobj); // 20 Crush
void ftMasterHand_80153F8C(HSD_GObj* fighter_gobj);
void ftMasterHand_80154114(HSD_GObj* fighter_gobj);
void ftMasterHand_80154158(HSD_GObj* fighter_gobj);
void ftMasterHand_801541C4(HSD_GObj* fighter_gobj);
void ftMasterHand_80154230(HSD_GObj* fighter_gobj, u32, u32);
void ftMasterHand_80154278(HSD_GObj* fighter_gobj);
void ftMasterHand_801542BC(HSD_GObj* fighter_gobj);
void ftMasterHand_801542DC(HSD_GObj* fighter_gobj);
void ftMasterHand_80154360(HSD_GObj* fighter_gobj, u32);
void ftMasterHand_801543E8(HSD_GObj* fighter_gobj);
void ftMasterHand_8015442C(HSD_GObj* fighter_gobj);
void ftMasterHand_8015459C(HSD_GObj* fighter_gobj);
void ftMasterHand_80154620(HSD_GObj* fighter_gobj);
void ftMasterHand_80154670(HSD_GObj* fighter_gobj);
void ftMasterHand_801546B4(HSD_GObj* fighter_gobj);
void ftMasterHand_801546D4(HSD_GObj* fighter_gobj);
void ftMasterHand_80154758(HSD_GObj* fighter_gobj);
void ftMasterHand_80154794(HSD_GObj* fighter_gobj);
void ftMasterHand_801547D8(HSD_GObj* fighter_gobj);
void ftMasterHand_80154838(HSD_GObj* fighter_gobj);
void ftMasterHand_801548D8(HSD_GObj* fighter_gobj);
void ftMasterHand_80154964(HSD_GObj* fighter_gobj);
void ftMasterHand_801549A8(HSD_GObj* fighter_gobj);
void ftMasterHand_80154A08(HSD_GObj* fighter_gobj);
void ftMasterHand_80154B2C(HSD_GObj* fighter_gobj);
void ftMasterHand_80154BB0(HSD_GObj* fighter_gobj);
void ftMasterHand_80154BF4(HSD_GObj* fighter_gobj);
void ftMasterHand_80154C54(HSD_GObj* fighter_gobj);
void ftMasterHand_80154D78(HSD_GObj* fighter_gobj, unk_t, unk_t);
void ftMasterHand_80154DD0(HSD_GObj* fighter_gobj);
void ftMasterHand_80154E14(HSD_GObj* fighter_gobj);
void ftMasterHand_80154E74(HSD_GObj* fighter_gobj);
void ftMasterHand_80154ED8(HSD_GObj* fighter_gobj, unk_t, unk_t);
void ftMasterHand_80154FAC(HSD_GObj* fighter_gobj);
void ftMasterHand_80154FF0(HSD_GObj* fighter_gobj);
void ftMasterHand_80155010(HSD_GObj* fighter_gobj);
void ftMasterHand_80155074(HSD_GObj* fighter_gobj, unk_t, unk_t);
void ftMasterHand_8015512C(HSD_GObj* fighter_gobj);
void ftMasterHand_80155170(HSD_GObj* fighter_gobj);
void ftMasterHand_80155190(HSD_GObj* fighter_gobj);
void ftMasterHand_80155194(HSD_GObj* fighter_gobj); // 27 Crazy Hand Combo Attack 1
void ftMasterHand_8015521C(HSD_GObj* fighter_gobj);
void ftMasterHand_80155290(HSD_GObj* fighter_gobj);
void ftMasterHand_801552D4(HSD_GObj* fighter_gobj);
void ftMasterHand_801552F4(HSD_GObj* fighter_gobj);
void ftMasterHand_801552F8(HSD_GObj* fighter_gobj); // 28 Crazy Hand Combo Attack 2
void ftMasterHand_80155388(HSD_GObj* fighter_gobj, unk_t, unk_t);
void ftMasterHand_8015541C(HSD_GObj* fighter_gobj);
void ftMasterHand_80155460(HSD_GObj* fighter_gobj);
void ftMasterHand_80155480(HSD_GObj* fighter_gobj);
void ftMasterHand_80155484(HSD_GObj* fighter_gobj); // 29 Crazy Hand Combo Attack 3
void ftMasterHand_8015550C(HSD_GObj* fighter_gobj);
void ftMasterHand_80155580(HSD_GObj* fighter_gobj);
void ftMasterHand_801555C4(HSD_GObj* fighter_gobj);
void ftMasterHand_801555E4(HSD_GObj* fighter_gobj);
void ftMasterHand_801555E8(HSD_GObj* fighter_gobj);
void ftMasterHand_8015565C(HSD_GObj* fighter_gobj);
void ftMasterHand_801556A0(HSD_GObj* fighter_gobj);
void ftMasterHand_801556C0(HSD_GObj* fighter_gobj);
void ftMasterHand_801556C4(HSD_GObj* fighter_gobj, unk_t, unk_t, unk_t, unk_t);
void ftMasterHand_801557B0(HSD_GObj* fighter_gobj);
void ftMasterHand_801557F4(HSD_GObj* fighter_gobj);
void ftMasterHand_80155814(HSD_GObj* fighter_gobj);
void ftMasterHand_80155864(HSD_GObj* fighter_gobj);
void ftMasterHand_801558A0(HSD_GObj* fighter_gobj);
;
void ftMasterHand_801558E4(HSD_GObj* fighter_gobj);
void ftMasterHand_80155904(HSD_GObj* fighter_gobj);
void ftMasterHand_80155908(HSD_GObj* fighter_gobj);
void ftMasterHand_80155990(HSD_GObj* fighter_gobj);
void ftMasterHand_801559D4(HSD_GObj* fighter_gobj);
void ftMasterHand_80155A34(HSD_GObj* fighter_gobj);
void ftMasterHand_OnGrabFighter_Victim(HSD_GObj* self_gobj, HSD_GObj* victim_gobj);
void ftMasterHand_80155B70(HSD_GObj* fighter_gobj);
void ftMasterHand_80155B74(HSD_GObj* fighter_gobj);
void ftMasterHand_80155B78(HSD_GObj* fighter_gobj);

static void ftMasterHand_CheckPlayerSlotBossStub(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

#endif
