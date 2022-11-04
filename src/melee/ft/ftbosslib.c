#include <melee/ft/ftbosslib.h>

#include <dolphin/os/os.h>
#include <dolphin/types.h>
#include <melee/cm/camera.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ftlib.h>
#include <melee/lb/lbvector.h>

typedef enum {
    Gm_PKind_Human,
    Gm_PKind_Cpu,
    Gm_PKind_Demo,
    Gm_PKind_NA,
    Gm_PKind_Boss,
} Gm_PKind;

static float get_zero()
{
    // float reorder hack until hopefully fixing sqrtf fixes it
    return 0.0F;
}

void ftbosslib_8015BD20(HSD_GObj* gobj)
{
    return;
}

void ftbosslib_8015BD24(s32 arg0, f32* arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5)
{
    *arg1 = ((arg3 / arg0) + HSD_Randi(arg4 - arg5) + arg5) / arg2;
}

#include <melee/pl/player.h>

void ftbosslib_8015BDB4(HSD_GObj* arg0)
{
    Fighter* fp = arg0->user_data;
    Gm_PKind kind = Player_GetPlayerSlotType(fp->xC_playerID);
    { // TODO: assert macro
        BOOL bad = (kind == Gm_PKind_Human || kind == Gm_PKind_Boss || kind == Gm_PKind_Cpu);
        if (!bad) {
            OSReport("boss is human or boss!\n");
            __assert(__FILE__, 103, "kind == Gm_PKind_Human || kind == Gm_PKind_Boss || kind == Gm_PKind_Cpu");
        }
    }
}

static inline float my_sqrtf(float x)
{
    static const double _half = 0.5L;
    static const double _three = 3.0L;
    s32 unused = 0; // fakematch
    volatile float y;
    if (x > 0.0F) {

        double guess = __frsqrte((double) x);                 // returns an approximation to
        guess = _half * guess * (_three - guess * guess * x); // now have 12 sig bits
        guess = _half * guess * (_three - guess * guess * x); // now have 24 sig bits
        guess = _half * guess * (_three - guess * guess * x); // now have 32 sig bits
        y = (float) (x * guess);
        return y;
    }
    return x;
}

static inline float my_lbvector_Len(Vec3* vec)
{
    return my_sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

void ftbosslib_8015BE40(HSD_GObj* fighter_gobj, Vec* pos, f32* arg2, f32 arg3, f32 arg4)
{
    Fighter* fp;
    Vec3 diff;
    f32 distance;

    fp = fighter_gobj->user_data;
    lbvector_Diff(pos, &fp->xB0_pos, &diff); // third argument is result
    distance = my_lbvector_Len(&diff);
    if (distance < arg3) {
        *arg2 = 0.0F;
    } else {
        *arg2 = distance;
        lbvector_Normalize(&diff);
        diff.x *= distance * arg4;
        diff.y *= distance * arg4;
        diff.z *= distance * arg4;
    }
    fp->x80_self_vel.x = diff.x;
    fp->x80_self_vel.y = diff.y;
}

void ftbosslib_8015BF74(HSD_GObj* fighter_gobj, f32 arg1)
{
    Vec3 sp14;
    Fighter* fp;
    f32 temp_f1;
    f32 phi_f0;
    f32 phi_f1;

    fp = fighter_gobj->user_data;
    ftbosslib_8015C208(fighter_gobj, &sp14);
    temp_f1 = sp14.x - fp->xB0_pos.x;
    phi_f0 = fabs_inline(temp_f1);
    if (phi_f0 > arg1) {
        if (temp_f1 > get_zero()) { // float reorder hack
            phi_f1 = arg1;
        } else {
            phi_f1 = -arg1;
        }
        fp->x80_self_vel.x += phi_f1;
    } else {
        fp->x80_self_vel.x += temp_f1;
    }
}

void ftbosslib_8015C010(HSD_GObj* fighter_gobj, f32 arg1)
{
    Vec3 sp14;
    Fighter* fp;
    f32 temp_f1;
    f32 phi_f0;
    f32 phi_f0_2;

    fp = fighter_gobj->user_data;
    ftbosslib_8015C208(fighter_gobj, &sp14);
    temp_f1 = sp14.x - fp->xB0_pos.x;
    phi_f0 = fabs_inline(temp_f1);
    if (phi_f0 > arg1) {
        if (temp_f1 > 0.0F) {
            phi_f0_2 = arg1;
        } else {
            phi_f0_2 = -arg1;
        }
        fp->x80_self_vel.x = phi_f0_2;
    } else {
        fp->x80_self_vel.x = temp_f1;
    }
}

void ftbosslib_8015C09C(HSD_GObj* fighter_gobj, f32 arg1)
{
    HSD_JObj* jobj = fighter_gobj->hsd_obj;
    Fighter* fp = fighter_gobj->user_data;
    Quaternion quat = { 0 };
    s32 unused[2];

    fp->x2C_facing_direction = arg1;
    quat.y = M_PI / 2 * fp->x2C_facing_direction;
    HSD_JObjSetRotation(jobj, &quat);
}

void ftbosslib_8015C190(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    s32 unused1;
    Vec3 sp10;
    s32 unused2;

    fp = fighter_gobj->user_data;
    func_80053FF4(0, &sp10);
    if (fp->xB0_pos.x > sp10.x) {
        fp->xB0_pos.x = sp10.x;
        fp->x80_self_vel.x = 0.0F;
    }
    func_80054158(0, &sp10);
    if (fp->xB0_pos.x < sp10.x) {
        fp->xB0_pos.x = sp10.x;
        fp->x80_self_vel.x = 0.0F;
    }
}

void ftbosslib_8015C208(HSD_GObj* fighter_gobj, Vec* pos)
{
    s32 unused;
    Fighter* fp = fighter_gobj->user_data;
    HSD_GObj* gobj = ftbosslib_8015C244(fighter_gobj, &fp->xB0_pos);
    func_80086644(gobj, pos);
}

HSD_GObj* ftbosslib_8015C244(HSD_GObj* fighter_gobj, Vec* pos)
{
    return func_8008627C(pos, fighter_gobj);
}

BOOL func_8015C270(void)
{
    if (ftbosslib_8015C44C(FTKIND_MASTERH) == 0x157)
        return TRUE;

    return FALSE;
}

BOOL func_8015C2A8(void)
{
    if (ftbosslib_8015C44C(FTKIND_CREZYH) == 0x183)
        return TRUE;

    return FALSE;
}

BOOL func_8015C2E0(void)
{
    s32 x = ftbosslib_8015C44C(FTKIND_MASTERH);

    if (x == 0x158 || x == 0x159)
        return TRUE;

    return FALSE;
}

BOOL ftbosslib_8015C31C(void)
{
    s32 x = ftbosslib_8015C44C(FTKIND_CREZYH);

    if (x == 0x181 || x == 0x182)
        return TRUE;

    return FALSE;
}

BOOL func_8015C358(void)
{
    HSD_GObj* gobj = ftbosslib_8015C3E8(FTKIND_MASTERH);
    if (gobj && ((Fighter*) gobj->user_data)->x221F_flag.bits.b3) {
        return TRUE;
    }
    return FALSE;
}

BOOL ftbosslib_8015C3A0(void)
{
    HSD_GObj* gobj = ftbosslib_8015C3E8(FTKIND_CREZYH);
    if (gobj && ((Fighter*) gobj->user_data)->x221F_flag.bits.b3) {
        return TRUE;
    }
    return FALSE;
}

HSD_GObj* ftbosslib_8015C3E8(FighterKind kind)
{
    HSD_GObj* cur;
    s32 unused[2];

    for (cur = lbl_804D782C->x20_fighters; cur; cur = cur->next)
        if (kind == func_800872A4(cur))
            return cur;

    return NULL;
}

s32 ftbosslib_8015C44C(FighterKind kind)
{
    HSD_GObj* gobj = ftbosslib_8015C3E8(kind);
    s32 unused[4];

    return gobj != NULL ? func_80086C0C(gobj) : 0;
}

s32 ftbosslib_8015C4C4(void)
{
    HSD_GObj* gobj = ftbosslib_8015C3E8(FTKIND_CREZYH);
    s32 unused[6];

    return gobj != NULL ? ((Fighter*) gobj->user_data)->sa.masterhand.x2250 : 0;
}

s32 func_8015C530(u32 arg0)
{
    MasterHandAttributes* attr;
    HSD_GObj* gobj;
    s32 unused[4];

    gobj = ftbosslib_8015C3E8(FTKIND_MASTERH);
    if (gobj) {
        attr = getFighter(gobj)->x10C_ftData->ext_attr;
        switch (arg0) {
        case 0:
            return attr->x0;
        case 1:
            return attr->x4;
        case 2:
            return attr->x8;
        case 3:
            return attr->xC;
        case 4:
            return attr->x10;
        case 6:
        default:
            return attr->x14;
        }
    } else {
        return 0;
    }
}

void func_8015C5F8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    switch (HSD_Randi(4)) {
    case 0:
        func_80088148(fp, 0x4E21A, 0x7F, 0x40);
        return;
    case 1:
        func_80088148(fp, 0x4E21B, 0x7F, 0x40);
        return;
    case 2:
        func_80088148(fp, 0x4E21C, 0x7F, 0x40);
        return;
    case 3:
        func_80088148(fp, 0x4E21D, 0x7F, 0x40);
        return;
    }
}

MasterHandAttributes* func_8015C6BC(void)
{
    HSD_GObj* gobj = ftbosslib_8015C3E8(FTKIND_MASTERH);
    Fighter* fp;
    MasterHandAttributes* ext_attr;
    s32 unused[4];

    if (gobj == NULL)
        return NULL;

    fp = gobj->user_data;

    if (fp == NULL)
        return NULL;

    ext_attr = fp->x10C_ftData->ext_attr;

    if (ext_attr == NULL)
        return NULL;

    return ext_attr;
}

s32 func_8015C74C(void)
{
    s32 unused[6];
    MasterHandAttributes* attr = func_8015C6BC();

    if (attr == NULL)
        return -1;

    return attr->x164;
}

s32 func_8015C7EC(void)
{
    s32 unused[6];
    MasterHandAttributes* attr = func_8015C6BC();

    if (attr == NULL)
        return -1;

    return attr->x168;
}

s32 func_8015C88C(void)
{
    MasterHandAttributes* attr = func_8015C6BC();
    s32 unused[6];

    if (attr == NULL)
        return -1;

    return attr->x16C;
}

s32 func_8015C92C(void)
{
    MasterHandAttributes* ext_attr = func_8015C6BC();
    s32 unused[6];

    if (ext_attr == NULL)
        return -1;

    return ext_attr->x170;
}

s32 func_8015C9CC(void)
{
    MasterHandAttributes* ext_attr = func_8015C6BC();
    s32 unused[6];

    if (ext_attr == NULL)
        return -1;

    return ext_attr->x174;
}

void func_8015CA6C_inline(s32 arg0)
{
    HSD_GObj* crazy_hand = ftbosslib_8015C3E8(FTKIND_CREZYH);

    if (crazy_hand != NULL)
        func_80086A4C(crazy_hand, arg0);
}

void func_8015CA6C(s32 arg0)
{
    HSD_GObj* master_hand;
    s32 unused[8];

    Player_80036790(0, arg0);
    master_hand = ftbosslib_8015C3E8(FTKIND_MASTERH);

    if (master_hand != NULL)
        func_80086A4C(master_hand, arg0);

    func_8015CA6C_inline(arg0);
    func_8026C3FC();
}

void func_8015CB7C(void)
{
    func_8026C42C();
}

#include <melee/cm/camera.h>

void func_8015CB9C_inline(Vec3 spC)
{
    f32 phi_f1;
    MasterHandAttributes* ext_attr = func_8015C6BC();

    if (ext_attr == NULL)
        phi_f1 = -1.0F;
    else
        phi_f1 = ext_attr->x178;

    spC.z += phi_f1;
    func_8002EA64(&spC);
    func_8002F0E4(0xA);
}

void func_8015CB9C(s32 arg0)
{
    Vec3 sp18;

    Player_LoadPlayerCoords(arg0, &sp18);
    func_8002E818(&sp18);
    func_8015CB9C_inline(sp18);
}

void func_8015CC14(void)
{
    func_8002F474();
}
