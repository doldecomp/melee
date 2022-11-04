#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

#include <melee/cm/camera.h>

static void ftMasterHand_801511FC(HSD_GObj* fighter_gobj);

void ftMasterHand_801510B0(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* attr = fp->x10C_ftData->ext_attr;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x157, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
    fp->xB0_pos.x = attr->x30_pos2.x;
    fp->xB0_pos.y = attr->x30_pos2.y;
    fp->xB0_pos.z = 0.0F;
    fp->cb.x21BC_callback_Accessory4 = &ftMasterHand_801511FC;
    fp->x2340_stateVar1 = 0;
    func_800881D8(fp, 0x4E201, 0x7F, 0x40 /*, ftMasterHand_801511FC */); // probs same file if ftMasterHand_801511FC is getting implicitly passed.
    ftbosslib_8015C09C(fighter_gobj, -1.0F);
}

void ftMasterHand_80151168(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        Fighter* fp = fighter_gobj->user_data;
        u32 unk[2];
        fp->sa.masterhand.x2258 = 0x155;
        ftMasterHand_80151018(fighter_gobj);
    }
}

#include <melee/pl/player.h>

void ftMasterHand_801511B0(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (!Player_GetPlayerSlotType(fp->xC_playerID))
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_801511F4(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_801511F8(HSD_GObj* fighter_gobj)
{
    return;
}

#include <melee/cm/camera.h>

static void ftMasterHand_801511FC(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    HSD_GObj* tmp_gobj;
    s32 unused[4];

    switch (fp->x2340_stateVar1) {
    case 0: {
        tmp_gobj = func_8008627C(&fp->xB0_pos, fighter_gobj);

        if (tmp_gobj != NULL)
            func_8002E6FC(func_80086BE0(tmp_gobj));
        else
            func_8002E6FC(0);

        func_8002ED9C(40.0F);
        func_8002EEC8(45.0F);
        func_8002EC7C(-M_PI);
        func_8002EF14();
        func_8002EC7C(0.0F);
        func_8002F0E4(0x78);
        fp->x2340_stateVar1 = 1;
        break;
    }
    case 1: {
        if (func_8002F260()) {
            func_8002E948(&ftMasterHand_80151428);
            func_8002ED9C(120.0F);
            func_8002F0E4(0x14);
            fp->x2340_stateVar1 = 2;
        }
        break;
    }
    case 2: {
        if (func_8002F260()) {
            func_8002EC7C(1.5707963705062866F);
            func_8002F0E4(0x3C);
            fp->x2340_stateVar1 = 3;
        }
        break;
    }
    case 3: {
        if (func_8002F260()) {
            func_8002ED9C(90.0F);
            func_8002EC7C(-0.3490658402442932F);
            func_8002EB5C(-0.2617993950843811F);
            func_8002EF14();
            fp->x2340_stateVar1 = 4;
        }
        break;
    }
    case 4: {
        func_8002F274();
        fp->x2348_stateVar3 = 0x78;
        fp->x2340_stateVar1 = 5;
        break;
    }
    case 5: {
        if (--fp->x2348_stateVar3 == 0) {
            func_8002EC7C(-0.3490658402442932F);
            func_8002EF14();
            func_8002ED9C(120.0F);
            fp->x2348_stateVar3 = 0x1E;
            fp->x2340_stateVar1 = 6;
        }
        break;
    }
    case 6: {
        if (--fp->x2348_stateVar3 == 0) {
            func_8002EC7C(0.3490658402442932F);
            func_8002EF14();
            fp->x2348_stateVar3 = 0x1E;
            fp->x2340_stateVar1 = 7;
        }
        break;
    }
    case 7: {
        if (--fp->x2348_stateVar3 == 0) {
            func_8002ED9C(180.0F);
            func_8002EC7C(-1.5707963705062866F);
            func_8002EB5C(-0.3490658402442932F);
            func_8002EF14();
            fp->x2348_stateVar3 = 0x32;
            fp->x2340_stateVar1 = 8;
        }
        break;
    }
    case 8: {
        func_8002F274();
        fp->x2340_stateVar1 = 9;
        break;
    }
    case 9: {
        if (--fp->x2348_stateVar3 == 0) {
            func_8002F474();
            fp->x2340_stateVar1 = 10;
        }
        break;
    }
    }
}
