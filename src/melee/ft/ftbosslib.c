#include <melee/ft/ftbosslib.h>

#include <dolphin/os/os.h>
#include <melee/cm/camera.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftlib.h>
#include <melee/it/item.h>
#include <melee/lb/lbvector.h>
#include <melee/mp/mplib.h>
#include <sysdolphin/baselib/gobj.h>

typedef enum {
    Gm_PKind_Human,
    Gm_PKind_Cpu,
    Gm_PKind_Demo,
    Gm_PKind_NA,
    Gm_PKind_Boss,
} Gm_PKind;

/// @todo Float reorder hack until hopefully fixing #my_sqrtf fixes it.
static float get_zero(void)
{
    return 0.0f;
}

void func_8015BD20(HSD_GObj* gobj)
{
    return;
}

void func_8015BD24(s32 arg0, f32* arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5)
{
    *arg1 = ((s32) (arg3 / arg0) + HSD_Randi(arg4 - arg5) + arg5) / arg2;
}

void func_8015BDB4(HSD_GObj* arg0)
{
    Fighter* fp = arg0->user_data;
    Gm_PKind kind = Player_GetPlayerSlotType(fp->xC_playerID);
    { // TODO: assert macro
        bool bad = (kind == Gm_PKind_Human || kind == Gm_PKind_Boss ||
                    kind == Gm_PKind_Cpu);
        if (!bad) {
            OSReport("boss is human or boss!\n");
            __assert("ftbosslib.c", 103,
                     "kind == Gm_PKind_Human || kind == Gm_PKind_Boss || kind "
                     "== Gm_PKind_Cpu");
        }
    }
}

static inline float my_sqrtf(float x)
{
    static const double _half = .5;
    static const double _three = 3.0;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[4] = { 0 };
#endif

    volatile float y;
    if (x > 0.0f) {
        // returns an approximation to
        double guess = __frsqrte((double) x);
        // now have 12 sig bits
        guess = _half * guess * (_three - guess * guess * x);
        // now have 24 sig bits
        guess = _half * guess * (_three - guess * guess * x);
        // now have 32 sig bits
        guess = _half * guess * (_three - guess * guess * x);
        y = x * guess;
        return y;
    }
    return x;
}

static inline float my_lbvector_Len(Vec3* vec)
{
    return my_sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

void func_8015BE40(HSD_GObj* gobj, Vec3* arg1, f32* arg2, f32 arg3, f32 arg4)
{
    Fighter* fp = gobj->user_data;
    Vec3 diff;
    lbvector_Diff(arg1, &fp->xB0_pos, &diff);

    {
        f32 distance = my_lbvector_Len(&diff);
        if (distance < arg3) {
            *arg2 = 0.0f;
        } else {
            *arg2 = distance;
            lbvector_Normalize(&diff);
            diff.x *= distance * arg4;
            diff.y *= distance * arg4;
            diff.z *= distance * arg4;
        }
    }

    fp->x80_self_vel.x = diff.x;
    fp->x80_self_vel.y = diff.y;
}

void func_8015BF74(HSD_GObj* fighter_gobj, f32 x_diff_max)
{
    Fighter* fp = fighter_gobj->user_data;
    Vec3 vec;

    func_8015C208(fighter_gobj, &vec);

    {
        f32 x_diff = vec.x - fp->xB0_pos.x;
        f32 abs_x_diff = fabs_inline(x_diff);
        if (abs_x_diff > x_diff_max)
            fp->x80_self_vel.x += x_diff > 0 ? x_diff_max : -x_diff_max;
        else
            fp->x80_self_vel.x += x_diff;
    }
}

void func_8015C010(HSD_GObj* fighter_gobj, f32 x_diff_max)
{
    Vec3 vec;
    Fighter* fp = fighter_gobj->user_data;
    func_8015C208(fighter_gobj, &vec);

    {
        f32 x_diff = vec.x - fp->xB0_pos.x;
        f32 abs_x_diff = fabs_inline(x_diff);
        if (abs_x_diff > x_diff_max)
            fp->x80_self_vel.x = x_diff > 0 ? x_diff_max : -x_diff_max;
        else
            fp->x80_self_vel.x = x_diff;
    }
}

void func_8015C09C(HSD_GObj* fighter_gobj, f32 facing_dir)
{
    HSD_JObj* jobj = GET_JOBJ(fighter_gobj);
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    Quaternion quat = { 0 };

    fp->facing_dir = facing_dir;
    quat.y = M_PI_2 * fp->facing_dir;
    HSD_JObjSetRotation(jobj, &quat);
}

void func_8015C190(HSD_GObj* arg0)
{
    Fighter* fp = GET_FIGHTER(arg0);
    Vec3 vec;

    func_80053FF4(0, &vec);
    if (fp->xB0_pos.x > vec.x) {
        fp->xB0_pos.x = vec.x;
        fp->x80_self_vel.x = 0;
    }

    func_80054158(0, &vec);
    if (fp->xB0_pos.x < vec.x) {
        fp->xB0_pos.x = vec.x;
        fp->x80_self_vel.x = 0;
    }
}

void func_8015C208(HSD_GObj* arg0, Vec3* arg1)
{
    Fighter* fp = GET_FIGHTER(arg0);
    HSD_GObj* gobj = func_8015C244(arg0, &fp->xB0_pos);
    func_80086644(gobj, arg1);
}

HSD_GObj* func_8015C244(HSD_GObj* arg0, Vec3* arg1)
{
    return func_8008627C(arg1, arg0);
}

bool func_8015C270(void)
{
    /// @todo Get ASID
    if (func_8015C44C(FTKIND_MASTERH) == 0x157)
        return 1;

    return 0;
}

bool func_8015C2A8(void)
{
    /// @todo Get ASID
    if (func_8015C44C(FTKIND_CREZYH) == 0x183)
        return true;

    return false;
}

bool func_8015C2E0(void)
{
    /// @todo Get ASIDs
    enum_t asid = func_8015C44C(FTKIND_MASTERH);
    if (asid == 0x158 || asid == 0x159)
        return true;

    return false;
}

bool func_8015C31C(void)
{
    /// @todo Get ASIDs
    enum_t asid = func_8015C44C(FTKIND_CREZYH);
    if (asid == 0x181 || asid == 0x182)
        return true;

    return false;
}

bool func_8015C358(void)
{
    HSD_GObj* gobj = func_8015C3E8(FTKIND_MASTERH);
    if (gobj && GET_FIGHTER(gobj)->x221F_flag.bits.b3)
        return true;

    return false;
}

bool func_8015C3A0(void)
{
    HSD_GObj* gobj = func_8015C3E8(FTKIND_CREZYH);
    if (gobj && GET_FIGHTER(gobj)->x221F_flag.bits.b3)
        return true;

    return false;
}

/// get_fighter_gobj(FighterKind)
HSD_GObj* func_8015C3E8(FighterKind kind)
{
    HSD_GObj* cur;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[8];
#endif

    for (cur = lbl_804D782C->x20_fighters; cur; cur = cur->next) {
        if (kind == func_800872A4(cur))
            return cur;
    }

    return NULL;
}

enum_t func_8015C44C(FighterKind kind)
{
    HSD_GObj* gobj = func_8015C3E8(kind);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[16];
#endif

    if (gobj != NULL) {
        // DataOffset_ActionStateLoad
        return func_80086C0C(gobj);
    } else {
        return ASID_DEADDOWN;
    }
}

s32 func_8015C4C4(void)
{
    HSD_GObj* gobj = func_8015C3E8(FTKIND_CREZYH);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[24];
#endif

    if (gobj)
        return GET_FIGHTER(gobj)->sa.masterhand.x2250;

    return 0;
}

s32 func_8015C530(u32 arg0)
{
    MasterHandAttributes* attr;
    HSD_GObj* gobj;
    s32 unused[4];

    gobj = func_8015C3E8(FTKIND_MASTERH);
    if (gobj) {
        attr = GET_FIGHTER(gobj)->x10C_ftData->ext_attr;
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

void func_8015C5F8(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    switch (HSD_Randi(4)) {
    case 0:
        func_80088148(fp, 0x4E21A, 0x7F, 0x40); // SFX_PlayCharacterSFX
        return;
    case 1:
        func_80088148(fp, 0x4E21B, 0x7F, 0x40); // SFX_PlayCharacterSFX
        return;
    case 2:
        func_80088148(fp, 0x4E21C, 0x7F, 0x40); // SFX_PlayCharacterSFX
        return;
    case 3:
        func_80088148(fp, 0x4E21D, 0x7F, 0x40); // SFX_PlayCharacterSFX
        return;
    }
}

MasterHandAttributes* func_8015C6BC(void)
{
    HSD_GObj* gobj = func_8015C3E8(FTKIND_MASTERH);
    Fighter* fp;
    MasterHandAttributes* attr;
    s32 unused[4];

    if (!gobj) {
        return 0;
    }
    fp = gobj->user_data;
    if (!fp) {
        return 0;
    }
    attr = fp->x10C_ftData->ext_attr;
    if (!attr) {
        return 0;
    }
    return attr;
}

s32 func_8015C74C(void)
{
    s32 unused[6];
    MasterHandAttributes* attr = func_8015C6BC();
    if (attr == 0U) {
        return -1;
    }
    return attr->x164;
}

s32 func_8015C7EC(void)
{
    s32 unused[6];
    MasterHandAttributes* attr = func_8015C6BC();
    if (attr == 0U) {
        return -1;
    }
    return attr->x168;
}

s32 func_8015C88C(void)
{
    MasterHandAttributes* attr = func_8015C6BC();
    s32 unused[6];
    if (attr == 0) {
        return -1;
    }
    return attr->x16C;
}

s32 func_8015C92C(void)
{
    MasterHandAttributes* attr = func_8015C6BC();
    s32 unused[6];
    if (attr == 0) {
        return -1;
    }
    return attr->x170;
}

s32 func_8015C9CC(void)
{
    MasterHandAttributes* attr = func_8015C6BC();
    s32 unused[6];
    if (attr == 0) {
        return -1;
    }
    return attr->x174;
}

void func_8015CA6C_inline(s32 arg0)
{
    HSD_GObj* crazy_hand = func_8015C3E8(FTKIND_CREZYH);
    if (crazy_hand) {
        func_80086A4C(crazy_hand, arg0);
    }
}
void func_8015CA6C(s32 arg0)
{
    HSD_GObj* master_hand;
    s32 unused[8];

    Player_80036790(0, arg0);
    master_hand = func_8015C3E8(FTKIND_MASTERH);
    if (master_hand) {
        func_80086A4C(master_hand, arg0);
    }
    func_8015CA6C_inline(arg0);
    func_8026C3FC();
}

void func_8015CB7C(void)
{
    func_8026C42C();
}

void func_8015CB9C_inline(Vec3 spC)
{
    f32 phi_f1;
    MasterHandAttributes* attr;
    attr = func_8015C6BC();
    if (attr == 0) {
        phi_f1 = -1.0f;
    } else {
        phi_f1 = attr->x178;
    }
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
