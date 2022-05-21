#include <dolphin/types.h>

#include "sysdolphin/baselib/gobj.h"

#include "melee/ft/ftcommon.h"
#include "melee/ft/ftcliffcommon.h"
#include "melee/lb/lbvector.h"

typedef struct _ftPikachuAttributes {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    u32 x14;
    u32 x18;
    f32 x1C;
    f32 x20;
    f32 x24;
    f32 x28;
    f32 x2C;
    f32 x30;
    f32 x34;
    f32 x38;
    f32 x3C;
    f32 x40;
    f32 x44;
    f32 x48;
    f32 x4C;
    f32 x50;
    f32 x54;
    f32 x58;
    s32 x5C;
    s32 x60;
    f32 x64;
    f32 x68;
    Vec x6C_scale;
    f32 x78;
    Vec x7C_scale;
    f32 x88;
    f32 x8C;

    f32 x90;
    f32 x94;
    f32 x98;
    f32 x9C;

    s32 xA0;
    f32 xA4;
    s32 xA8;
    f32 xAC;

    f32 xB0;
    f32 xB4;
    f32 xB8;
    f32 xBC;

    f32 xC0;
    f32 xC4;
    f32 xC8;
    f32 xCC;

    f32 xD0;
    s32 xD4;
    s32 xD8;
    u32 xDC;

    f32 xE0_array_start;  /// TODO xE0 appears to be array of 6 floats, or two vecs
    f32 xE4;
    f32 xE8;
    f32 xEC;
    f32 xF0;
    f32 xF4;
} ftPikachuAttributes;


/// TODO put the rest of function headers here and rename all of the functions
///pika1
void ftPikachu_OnLoadForPichu(Fighter* fighter);
void ftPikachu_OnLoad(HSD_GObj* fighterObj);
void ftPikachu_OnDeath(HSD_GObj* fighterObj);
void ftPikachu_UnkHeldItemAction_801244B8(HSD_GObj* fighterObj, s32 arg1);

///pika2
void func_80124DC8(HSD_GObj* fighterObj);
void func_80124C90(HSD_GObj* fighterObj);
void func_80124D2C(HSD_GObj* fighterObj);


//pika3
void func_801250FC(HSD_GObj* fighterObj);
void func_8012515C(HSD_GObj* fighterObj);
void func_80125414(HSD_GObj* fighterObj);
void func_80125474(HSD_GObj* fighterObj);
void func_801254D4(HSD_GObj* fighterObj);
void func_80125528(HSD_GObj* fighterObj);
void func_80125774(HSD_GObj* fighterObj);
void func_801257D4(HSD_GObj* fighterObj);
void func_80125834(HSD_GObj* fighterObj);
void func_801258A0(HSD_GObj* fighterObj);
void func_80125A54(HSD_GObj* fighterObj);
void func_80125CD0(HSD_GObj* fighterObj);
void func_80125D28_file_end(HSD_GObj* fighterObj);

///pika4
void func_80126084(HSD_GObj* fighterObj);
void func_801260E4(HSD_GObj* fighterObj);
void func_80126A2C(HSD_GObj* fighterObj);
void func_80126AA4(HSD_GObj* fighterObj);
void func_80126C0C(HSD_GObj* fighterObj);
void func_80126E1C(HSD_GObj* fighterObj);
void func_8012744C(HSD_GObj* fighterObj);
void func_801274AC(HSD_GObj* fighterObj);
void func_80127534_file_end(HSD_GObj* fighterObj);