#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

// 801510B0 14DC90
// https://decomp.me/scratch/sIqel
void func_801510B0(HSD_GObj* gobj) {
    Fighter* r31_fp;
    MasterHandAttributes* r30_attributes;

    r31_fp = gobj->user_data;
    r30_attributes = r31_fp->x10C_ftData->ext_attr;
    Fighter_ActionStateChange_800693AC(gobj, 0x157, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
    r31_fp->xB0_pos.x = r30_attributes->x30_pos2.x;
    r31_fp->xB0_pos.y = r30_attributes->x30_pos2.y;
    r31_fp->xB0_pos.z = 0.0f;
    r31_fp->cb.x21BC_callback_Accessory4 = &lbl_801511FC;
    r31_fp->x2340_stateVar1 = 0;
    func_800881D8(r31_fp, 0x4E201, 0x7F, 0x40 /*, lbl_801511FC */); // probs same file if lbl_801511FC is getting implicitly passed.
    // func_800881D8(r31_fp, 0x4E201, 0x7F, 0x40, lbl_801511FC);
    func_8015C09C(gobj, -1.0f);
}



// 80151168 14DD48
// https://decomp.me/scratch/896fc
void lbl_80151168(HSD_GObj* gobj) {
    Fighter* r4_fp;
    u32 unk[2];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        r4_fp = gobj->user_data;
        r4_fp->sa.masterhand.x2258 = 0x155;
        func_80151018(gobj);
    }
}



// 801511B0 14DD90
// https://decomp.me/scratch/lkMK2
void lbl_801511B0(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;

    if (!Player_GetPlayerSlotType(fp->xC_playerID)) {
        func_8015BD20(gobj);
    }
}



// 801511F4 14DDD4
// https://decomp.me/scratch/xs8Nh
void lbl_801511F4(HSD_GObj* gobj) {

}



// 801511F8 14DDD8
// https://decomp.me/scratch/5Mb62
void lbl_801511F8(HSD_GObj* gobj) {

}



// 801511FC 14DDDC
void lbl_801511FC(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    HSD_GObj* tmp_gobj;
    s32 unused[4];
    switch(fp->x2340_stateVar1) {
        case 0:
            tmp_gobj = func_8008627C(&fp->xB0_pos, gobj);
            if (tmp_gobj != 0) {
                func_8002E6FC(func_80086BE0(tmp_gobj));
            } else {
                func_8002E6FC(0);
            }
            func_8002ED9C(40.0f);
            func_8002EEC8(45.0f);
            func_8002EC7C(-M_PI);
            func_8002EF14();
            func_8002EC7C(0.0f);
            func_8002F0E4(0x78);
            fp->x2340_stateVar1 = 1;
            break;
        case 1:
            if (func_8002F260() != 0) {
                func_8002E948(&lbl_80151428);
                func_8002ED9C(120.0f);
                func_8002F0E4(0x14);
                fp->x2340_stateVar1 = 2;
            }
            break;
        case 2:
            if (func_8002F260() != 0) {
                func_8002EC7C(1.5707963705062866f);
                func_8002F0E4(0x3C);
                fp->x2340_stateVar1 = 3;
            }
            break;
        case 3:
            if (func_8002F260() != 0) {
                func_8002ED9C(90.0f);
                func_8002EC7C(-0.3490658402442932f);
                func_8002EB5C(-0.2617993950843811f);
                func_8002EF14();
                fp->x2340_stateVar1 = 4;
            }
            break;
        case 4:
            func_8002F274();
            fp->x2348_stateVar3 = 0x78;
            fp->x2340_stateVar1 = 5;
            break;
        case 5:
            if (--fp->x2348_stateVar3 == 0) {
                func_8002EC7C(-0.3490658402442932f);
                func_8002EF14();
                func_8002ED9C(120.0f);
                fp->x2348_stateVar3 = 0x1E;
                fp->x2340_stateVar1 = 6;
            }
            break;
        case 6:
            if (--fp->x2348_stateVar3 == 0) {
                func_8002EC7C(0.3490658402442932f);
                func_8002EF14();
                fp->x2348_stateVar3 = 0x1E;
                fp->x2340_stateVar1 = 7;
            }
            break;
        case 7:
            if (--fp->x2348_stateVar3 == 0) {
                func_8002ED9C(180.0f);
                func_8002EC7C(-1.5707963705062866f);
                func_8002EB5C(-0.3490658402442932f);
                func_8002EF14();
                fp->x2348_stateVar3 = 0x32;
                fp->x2340_stateVar1 = 8;
            }
            break;
        case 8:
            func_8002F274();
            fp->x2340_stateVar1 = 9;
            break;
        case 9:
            if (--fp->x2348_stateVar3 == 0) {
                func_8002F474();
                fp->x2340_stateVar1 = 10;
            }
            break;
        // no default
    }
}
