#include "soundtest.h"

#include "db/db.h"
#include "db/dbsound.h"

#include "gm/forward.h"

#include "gm/gm_unsplit.h"
#include "gm/gmmain_lib.h"
#include "if/textlib.h"
#include "if/types.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbcardgame.h"
#include "lb/lbcardnew.h"
#include "lb/lblanguage.h"
#include "lb/lbsnap.h"
#include "mn/inlines.h"
#include "ty/toy.h"

#include <baselib/cobj.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/lobj.h>
#include <baselib/memory.h>
#include <baselib/sobjlib.h>
#include <baselib/tobj.h>

/* 2FF88C */ static bool un_802FF88C(enum soundtest_callback_arg0);
/* 2FF934 */ static bool un_802FF934(enum soundtest_callback_arg0);
/* 2FF958 */ static bool un_802FF958(enum soundtest_callback_arg0);
/* 2FF99C */ static bool un_802FF99C(enum soundtest_callback_arg0);
/* 2FF9DC */ static bool un_802FF9DC(enum soundtest_callback_arg0);
/* 2FFB58 */ static bool un_802FFB58(enum soundtest_callback_arg0);
/* 2FFBAC */ static bool un_802FFBAC(enum soundtest_callback_arg0);
/* 2FFC30 */ static bool un_802FFC30(enum soundtest_callback_arg0);
/* 2FFC6C */ static bool un_802FFC6C(enum soundtest_callback_arg0);
/* 2FFE6C */ static bool fn_802FFE6C(enum soundtest_callback_arg0);
/* 2FFEA4 */ static bool un_802FFEA4(enum soundtest_callback_arg0);
/* 3001DC */ static bool un_803001DC(enum soundtest_callback_arg0);
/* 300218 */ static bool un_80300218(enum soundtest_callback_arg0);
/* 300248 */ static bool un_80300248(enum soundtest_callback_arg0);
/* 300290 */ static bool un_80300290(enum soundtest_callback_arg0);
/* 3002FC */ static bool un_803002FC(enum soundtest_callback_arg0);
/* 300338 */ static bool un_80300338(enum soundtest_callback_arg0);
/* 300378 */ static bool un_80300378(enum soundtest_callback_arg0);
/* 3003C4 */ static bool un_803003C4(enum soundtest_callback_arg0);
/* 300410 */ static bool un_80300410(enum soundtest_callback_arg0);
/* 300480 */ static bool un_80300480(enum soundtest_callback_arg0);
/* 3004B4 */ static bool un_803004B4(enum soundtest_callback_arg0);
/* 3004E8 */ static bool un_803004E8(enum soundtest_callback_arg0);
/* 30051C */ static bool un_8030051C(enum soundtest_callback_arg0);
/* 300550 */ static bool un_80300550(enum soundtest_callback_arg0);
/* 300584 */ static bool un_80300584(enum soundtest_callback_arg0);
/* 3005B8 */ static bool un_803005B8(enum soundtest_callback_arg0);
/* 3005EC */ static bool un_803005EC(enum soundtest_callback_arg0);
/* 300620 */ static bool un_80300620(enum soundtest_callback_arg0);
/* 300654 */ static bool un_80300654(enum soundtest_callback_arg0);
/* 300688 */ static bool un_80300688(enum soundtest_callback_arg0);
/* 3006BC */ static bool un_803006BC(enum soundtest_callback_arg0);
/* 3006F0 */ static bool un_803006F0(enum soundtest_callback_arg0);
/* 300724 */ static bool un_80300724(enum soundtest_callback_arg0);
/* 300758 */ static bool un_80300758(enum soundtest_callback_arg0);
/* 300790 */ static bool un_80300790(enum soundtest_callback_arg0);
/* 3007C8 */ static bool un_803007C8(enum soundtest_callback_arg0);
/* 3007FC */ static bool un_803007FC(enum soundtest_callback_arg0);
/* 300830 */ static bool un_80300830(enum soundtest_callback_arg0);
/* 300864 */ static bool un_80300864(enum soundtest_callback_arg0);
/* 300898 */ static bool un_80300898(enum soundtest_callback_arg0);
/* 3008CC */ static bool un_803008CC(enum soundtest_callback_arg0);
/* 300900 */ static bool un_80300900(enum soundtest_callback_arg0);
/* 300934 */ static bool un_80300934(enum soundtest_callback_arg0);
/* 300968 */ static bool un_80300968(enum soundtest_callback_arg0);
/* 3009A4 */ static bool un_803009A4(enum soundtest_callback_arg0);
/* 3009E0 */ static bool un_803009E0(enum soundtest_callback_arg0);
/* 300A88 */ static bool un_80300A88(enum soundtest_callback_arg0);
/* 300AB8 */ static bool un_80300AB8(enum soundtest_callback_arg0);
/* 300AF4 */ static bool un_80300AF4(enum soundtest_callback_arg0);
/* 300B58 */ static bool un_80300B58(enum soundtest_callback_arg0);
/* 300BBC */ static bool un_80300BBC(enum soundtest_callback_arg0);
/* 300BF8 */ static bool un_80300BF8(enum soundtest_callback_arg0);
/* 300C3C */ static bool un_80300C3C(enum soundtest_callback_arg0);
/* 300C80 */ static bool un_80300C80(enum soundtest_callback_arg0);
/* 300CC8 */ static bool fn_80300CC8(enum soundtest_callback_arg0);
/* 300D78 */ static bool un_80300D78(enum soundtest_callback_arg0);
/* 300DE0 */ static bool fn_80300DE0(enum soundtest_callback_arg0);
/* 300E74 */ static bool un_80300E74(enum soundtest_callback_arg0);
/* 300ED0 */ static bool fn_80300ED0(enum soundtest_callback_arg0);
/* 300F3C */ static bool un_80300F3C(enum soundtest_callback_arg0);
/* 300F98 */ static bool un_80300F98(enum soundtest_callback_arg0);
/* 300FEC */ static bool un_80300FEC(enum soundtest_callback_arg0);
/* 301028 */ static bool un_80301028(enum soundtest_callback_arg0);
/* 301074 */ static bool un_80301074(enum soundtest_callback_arg0);
/* 3010C0 */ static bool un_803010C0(enum soundtest_callback_arg0);
/* 30110C */ static bool fn_8030110C(enum soundtest_callback_arg0);
/* 3011EC */ static bool fn_803011EC(enum soundtest_callback_arg0);
/* 301280 */ static bool un_80301280(enum soundtest_callback_arg0);
/* 3012D4 */ static bool un_803012D4(enum soundtest_callback_arg0);
/* 301328 */ static bool un_80301328(enum soundtest_callback_arg0);
/* 30136C */ static bool un_8030136C(enum soundtest_callback_arg0);
/* 3013B0 */ static bool un_803013B0(enum soundtest_callback_arg0);
/* 3013EC */ static bool un_803013EC(enum soundtest_callback_arg0);
/* 301420 */ static bool un_80301420(enum soundtest_callback_arg0);
/* 301454 */ static bool un_80301454(enum soundtest_callback_arg0);
/* 301490 */ static bool un_80301490(enum soundtest_callback_arg0);
/* 3014CC */ static bool un_803014CC(enum soundtest_callback_arg0);
/* 301508 */ static bool un_80301508(enum soundtest_callback_arg0);
/* 301544 */ static bool un_80301544(enum soundtest_callback_arg0);
/* 301580 */ static bool un_80301580(enum soundtest_callback_arg0);
/* 3015BC */ static bool un_803015BC(enum soundtest_callback_arg0);
/* 3015F8 */ static bool un_803015F8(enum soundtest_callback_arg0);
/* 301634 */ static bool un_80301634(enum soundtest_callback_arg0);
/* 3016D8 */ static bool un_803016D8(enum soundtest_callback_arg0);
/* 301734 */ static bool un_80301734(enum soundtest_callback_arg0);
/* 30178C */ static bool un_8030178C(enum soundtest_callback_arg0);
/* 301800 */ static bool un_80301800(enum soundtest_callback_arg0);
/* 301840 */ static bool un_80301840(enum soundtest_callback_arg0);
/* 3018BC */ static bool un_803018BC(enum soundtest_callback_arg0);
/* 30191C */ static bool un_8030191C(enum soundtest_callback_arg0);
/* 301964 */ static bool un_80301964(enum soundtest_callback_arg0);
/* 301A64 */ static bool un_80301A64(enum soundtest_callback_arg0);
/* 301AD4 */ static bool un_80301AD4(enum soundtest_callback_arg0);
/* 301B48 */ static bool un_80301B48(enum soundtest_callback_arg0);
/* 301C80 */ static bool un_80301C80(enum soundtest_callback_arg0);
/* 301CE0 */ static bool un_80301CE0(enum soundtest_callback_arg0);
/* 301D40 */ static bool un_80301D40(enum soundtest_callback_arg0);
/* 301D7C */ static bool un_80301D7C(enum soundtest_callback_arg0);
/* 301DCC */ static bool un_80301DCC(enum soundtest_callback_arg0);
/* 301E08 */ static bool un_80301E08(enum soundtest_callback_arg0);
/* 2FFCC8 */ static bool fn_802FFCC8(enum soundtest_callback_arg0);

/// .bss (extern)
/* 45A6C0 */ extern u8 gmMainLib_8045A6C0[];
/* 4D6B88 */ extern int db_804D6B88;

/// Overlay used to reach the menu data through the label block that precedes
/// it, the way the original code addresses it.
struct un_803F9F28_t {
    u8 _pad0[0xA8];
    int xA8;
    u8 _padAC[0x8];
    f32 xB4;
    u8 _padB8[0x90];
    int x148;
    u8 _pad14C[0x1C];
    int x168;
    u8 _pad16C[0x8];
    f32 x174;
    u8 _pad178[0x10];
    int x188;
    u8 _pad18C[0x50];
    char x1DC[0xC];
    char x1E8[0x18];
};

struct un_803FA128_x130_t {
    int x0;
    int x4;
    int x8;
    int xC;
    int x10[4];
    int x20_pad;
    int x24[4];
    int x34_pad;
    int x38[4];
    int x48[4];
    int x58[4];
    int x68[4];
    f32 x78[4];
    f32 x88[4];
    f32 x98[4];
    int xA8[4];
    int xB8[4];
    int xC8;
    int xCC[4];
    int xDC[4];
    f32 xEC;
};

/// Overlay reaching past the end of #un_803FA128 into #un_803FA258, matching
/// how the original code addresses both blocks from a single base.
struct un_803FA128_t {
    u8 _pad0[0x130];
    struct un_803FA128_x130_t x130;
    u16 x220;
    u8 _pad222[0x2];
    u8 x224;
    u8 x225;
    u8 x226;
    u8 x227;
};

struct un_803FA258_t {
    /* 0x000 */ int x0;
    /* 0x004 */ int x4[4];
    /* 0x014 */ int x14[4];
    /* 0x024 */ int x24[4];
    /* 0x034 */ int x34;
    /* 0x038 */ int x38[4];
    /* 0x048 */ int x48[4];
    /* 0x058 */ int x58[4];
    /* 0x068 */ int x68[4];
    /* 0x078 */ f32 x78[4];
    /* 0x088 */ f32 x88[4];
    /* 0x098 */ f32 x98[4];
    /* 0x0A8 */ int xA8[4];
    /* 0x0B8 */ int xB8[4];
    /* 0x0C8 */ int xC8;
    /* 0x0CC */ int xCC[4];
    /* 0x0DC */ int xDC[4];
    /* 0x0EC */ f32 xEC;
    /* 0x0F0 */ u16 xF0;
    /* 0x0F2 */ u8 _padF2[2];
    /* 0x0F4 */ u8 xF4;
    /* 0x0F5 */ u8 xF5;
    /* 0x0F6 */ u8 xF6;
    /* 0x0F7 */ u8 xF7;
    /* 0x0F8 */ int xF8;
    /* 0x0FC */ int xFC;
    /* 0x100 */ int x100;
    /* 0x104 */ int x104;
    /* 0x108 */ int x108;
    /* 0x10C */ int x10C;
    /* 0x110 */ int x110;
    /* 0x114 */ int x114;
    /* 0x118 */ int x118;
    /* 0x11C */ int x11C;
    /* 0x120 */ int x120;
    /* 0x124 */ int x124;
    /* 0x128 */ int x128;
    /* 0x12C */ int x12C;
    /* 0x130 */ int x130;
    /* 0x134 */ int x134;
    /* 0x138 */ void* x138;
    /* 0x13C */ int x13C;
    /* 0x140 */ int x140;
    /* 0x144 */ int x144[17];
    /* 0x188 */ int x188;
    /* 0x18C */ int x18C;
};

/// .data (defined at the end of this file, so that the functions above
/// address each block through its own symbol).
/* 803F9EF0 */ extern char lbl_803F9EF0[];
/* 803F9F10 */ extern char lbl_803F9F10[];
/* 803F9F28 */ extern char un_803F9F28[];
/* 803F9F38 */ extern char un_803F9F38[];
/* 803F9F44 */ extern char un_803F9F44[];
/* 803F9F50 */ extern char un_803F9F50[];
/* 803F9F5C */ extern char un_803F9F5C[];
/* 803F9F68 */ extern char un_803F9F68[];
/* 803F9F74 */ extern char un_803F9F74[];
/* 803F9F80 */ extern char un_803F9F80[];
/* 803F9F8C */ extern char un_803F9F8C[];
/* 803F9F98 */ extern char un_803F9F98[];
/* 803F9FA4 */
/* 803FA128 */ extern int un_803FA128[76];
/* 803FA258 */ extern struct un_803FA258_t un_803FA258;
/* 803FA3E8 */ extern char* un_803FA3E8[3];
/* 803FA3F4 */ extern char un_803FA3F4[];
/* 803FA404 */ extern char un_803FA404[];
/* 803FA414 */ extern char un_803FA414[];
/* 803FA424 */ extern char un_803FA424[];
/* 803FA434 */ extern char un_803FA434[];
/* 803FA440 */ extern char* un_803FA440[5];
/* 803FA454 */ extern char un_803FA454[];
/* 803FA468 */ extern char un_803FA468[];
/* 803FA474 */ extern char un_803FA474[];
/* 803FA480 */ extern char un_803FA480[];
/* 803FA48C */ extern char un_803FA48C[];
/* 803FA498 */ extern char un_803FA498[];
/* 803FA4A8 */ extern char un_803FA4A8[];
/* 803FA4B8 */ extern char un_803FA4B8[];
/* 803FA4CC */ extern char un_803FA4CC[];
/* 803FA640 */ extern char un_803FA640[];
/* 803FA658 */ extern struct un_80304138_objalloc_t_x8 un_803FA658[8];
/* 803FA758 */ extern char un_803FA758[];
/* 803FA768 */ extern char un_803FA768[];
/* 803FA77C */ extern char un_803FA77C[];
/* 803FA810 */ extern char un_803FA810[];
/* 803FA81C */ extern char un_803FA81C[];
/* 803FA828 */ extern char un_803FA828[];
/* 803FA834 */ extern char un_803FA834[];
/* 803FA844 */ extern char* un_803FA844[4];
/* 803FA854 */ extern char un_803FA854[];
/* 803FA860 */ extern char* un_803FA860[6];
/* 803FA878 */ extern char un_803FA878[];
/* 803FA884 */ extern char un_803FA884[];
/* 803FA894 */ extern char un_803FA894[];
/* 803FA8A4 */ extern char un_803FA8A4[];
/* 803FA8B4 */ extern char un_803FA8B4[];
/* 803FA8C4 */ extern char un_803FA8C4[];
/* 803FA8D8 */ extern char un_803FA8D8[];
/* 803FA8E8 */ extern struct un_80304138_objalloc_t_x8 un_803FA8E8[9];
/* 803FAA08 */ extern char un_803FAA08[];
/* 803FAA14 */ extern char un_803FAA14[];
/* 803FAA20 */ extern char un_803FAA20[];
/* 803FAA2C */ extern char un_803FAA2C[];
/* 803FAA38 */ extern char un_803FAA38[];
/* 803FAA44 */ extern struct un_80304138_objalloc_t_x8 un_803FAA44[6];
/* 803FAB04 */ extern char un_803FAB04[];
/* 803FAB10 */ extern char un_803FAB10[];
/* 803FAB1C */ extern char un_803FAB1C[];
/* 803FAB28 */ extern char un_803FAB28[];
/* 803FAB34 */ extern char un_803FAB34[];
/* 803FAB40 */ extern char un_803FAB40[];
/* 803FAB4C */ extern char un_803FAB4C[];
/* 803FAB58 */ extern char un_803FAB58[];
/* 803FAB64 */ extern char un_803FAB64[];
/* 803FAB70 */ extern char un_803FAB70[];
/* 803FAB7C */ extern char un_803FAB7C[];
/* 803FAB88 */ extern char un_803FAB88[];
/* 803FAB94 */ extern char un_803FAB94[];
/* 803FABA0 */ extern char un_803FABA0[];
/* 803FABAC */ extern char un_803FABAC[];
/* 803FABB8 */ extern char un_803FABB8[];
/* 803FABC4 */ extern char un_803FABC4[];
/* 803FABD0 */ extern char un_803FABD0[];
/* 803FABDC */ extern char un_803FABDC[];
/* 803FABE8 */ extern char un_803FABE8[];
/* 803FABF4 */ extern char un_803FABF4[];
/* 803FAC00 */ extern char un_803FAC00[];
/* 803FAC0C */ extern char un_803FAC0C[];
/* 803FAC18 */ extern char un_803FAC18[];
/* 803FAC24 */ extern char un_803FAC24[];
/* 803FAC30 */ extern char un_803FAC30[];
/* 803FAC3C */ extern char un_803FAC3C[];
/* 803FAC48 */ extern char un_803FAC48[];
/* 803FAC54 */ extern char un_803FAC54[];
/* 803FAC60 */ extern char un_803FAC60[];
/* 803FAC6C */ extern char un_803FAC6C[];
/* 803FAC78 */ extern char un_803FAC78[];
/* 803FAC84 */ extern char un_803FAC84[];
/* 803FAC90 */ extern char un_803FAC90[];
/* 803FAC9C */ extern char un_803FAC9C[];
/* 803FACA8 */ extern char un_803FACA8[];
/* 803FACB4 */ extern char un_803FACB4[];
/* 803FACC0 */ extern char un_803FACC0[];
/* 803FACCC */ extern char un_803FACCC[];
/* 803FACD8 */ extern char un_803FACD8[];
/* 803FACE4 */ extern char un_803FACE4[];
/* 803FACF0 */ extern char un_803FACF0[];
/* 803FACFC */ extern char un_803FACFC[];
/* 803FAD08 */ extern char un_803FAD08[];
/* 803FAD14 */ extern char un_803FAD14[];
/* 803FAD20 */ extern char un_803FAD20[];
/* 803FAD2C */ extern char un_803FAD2C[];
/* 803FAD38 */ extern char un_803FAD38[];
/* 803FAD44 */ extern char un_803FAD44[];
/* 803FAD50 */ extern char un_803FAD50[];
/* 803FAD5C */ extern char un_803FAD5C[];
/* 803FAD68 */ extern char un_803FAD68[];
/* 803FAD74 */ extern char un_803FAD74[];
/* 803FAD80 */ extern char un_803FAD80[];
/* 803FAD8C */ extern char un_803FAD8C[];
/* 803FAD98 */ extern char un_803FAD98[];
/* 803FADA4 */ extern char un_803FADA4[];
/* 803FADB0 */ extern char un_803FADB0[];
/* 803FADBC */ extern char un_803FADBC[];
/* 803FADC8 */ extern char un_803FADC8[];
/* 803FADD4 */ extern char un_803FADD4[];
/* 803FADE0 */ extern char un_803FADE0[];
/* 803FADEC */ extern char un_803FADEC[];
/* 803FADF8 */ extern char un_803FADF8[];
/* 803FAE04 */ extern char un_803FAE04[];
/* 803FAE10 */ extern char un_803FAE10[];
/* 803FAE1C */ extern char un_803FAE1C[];
/* 803FAE28 */ extern char un_803FAE28[];
/* 803FAE34 */ extern char un_803FAE34[];
/* 803FAE40 */ extern char un_803FAE40[];
/* 803FAE4C */ extern char un_803FAE4C[];
/* 803FAE58 */ extern char un_803FAE58[];
/* 803FAE64 */ extern char un_803FAE64[];
/* 803FAE70 */ extern char un_803FAE70[];
/* 803FAE7C */ extern char un_803FAE7C[];
/* 803FAE88 */ extern char un_803FAE88[];
/* 803FAE94 */ extern char un_803FAE94[];
/* 803FAEA0 */ extern char un_803FAEA0[];
/* 803FAEAC */ extern char un_803FAEAC[];
/* 803FAEB8 */ extern char un_803FAEB8[];
/* 803FAEC4 */ extern char un_803FAEC4[];
/* 803FAED0 */ extern char un_803FAED0[];
/* 803FAEDC */ extern char un_803FAEDC[];
/* 803FAEE8 */ extern char un_803FAEE8[];
/* 803FAEF4 */ extern char un_803FAEF4[];
/* 803FAF00 */ extern char un_803FAF00[];
/* 803FAF0C */ extern char* un_803FAF0C[86];
/* 803FB064 */ extern char un_803FB064[];
/* 803FB074 */ extern char un_803FB074[];
/* 803FB080 */ extern char un_803FB080[];
/* 803FB090 */ extern char un_803FB090[];
/* 803FB0A0 */ extern char un_803FB0A0[];
/* 803FB0B0 */ extern char un_803FB0B0[];
/* 803FB0C0 */ extern char un_803FB0C0[];
/* 803FB0D0 */ extern char un_803FB0D0[];
/* 803FB0E0 */ extern char un_803FB0E0[];
/* 803FB0F0 */ extern char un_803FB0F0[];
/* 803FB100 */ extern char un_803FB100[];
/* 803FB110 */ extern char un_803FB110[];
/* 803FB120 */ extern char un_803FB120[];
/* 803FB130 */ extern char un_803FB130[];
/* 803FB140 */ extern char un_803FB140[];
/* 803FB14C */ extern char un_803FB14C[];
/* 803FB158 */ extern char un_803FB158[];
/* 803FB168 */ extern struct un_80304138_objalloc_t_x8 un_803FB168[16];
/* 803FB368 */ extern char un_803FB368[];
/* 803FB378 */ extern char un_803FB378[];
/* 803FB388 */ extern char un_803FB388[];
/* 803FB394 */ extern char un_803FB394[];
/* 803FB3A4 */ extern char un_803FB3A4[];
/* 803FB3B0 */ extern char un_803FB3B0[];
/* 803FB3BC */ extern char un_803FB3BC[];
/* 803FB3C8 */ extern char un_803FB3C8[];
/* 803FB3D4 */ extern char un_803FB3D4[];
/* 803FB3E0 */ extern char un_803FB3E0[];
/* 803FB3EC */ extern char un_803FB3EC[];
/* 803FB3FC */ extern char un_803FB3FC[];
/* 803FB408 */ extern char un_803FB408[];
/* 803FB414 */ extern char un_803FB414[];
/* 803FB424 */ extern char un_803FB424[];
/* 803FB434 */ extern char un_803FB434[];
/* 803FB440 */ extern char un_803FB440[];
/* 803FB44C */ extern char un_803FB44C[];
/* 803FB458 */ extern char un_803FB458[];
/* 803FB468 */ extern char un_803FB468[];
/* 803FB478 */ extern char un_803FB478[];
/* 803FB484 */ extern char un_803FB484[];
/* 803FB490 */ extern char un_803FB490[];
/* 803FB4A0 */ extern char un_803FB4A0[];
/* 803FB4B0 */ extern char un_803FB4B0[];
/* 803FB4BC */ extern char un_803FB4BC[];
/* 803FB4C8 */ extern char un_803FB4C8[];
/* 803FB4D8 */ extern char un_803FB4D8[];
/* 803FB4E4 */ extern char un_803FB4E4[];
/* 803FB4F0 */ extern char un_803FB4F0[];
/* 803FB500 */ extern char un_803FB500[];
/* 803FB510 */ extern char un_803FB510[];
/* 803FB520 */ extern char un_803FB520[];
/* 803FB52C */ extern char un_803FB52C[];
/* 803FB538 */ extern char* un_803FB538[34];
/* 803FB5C0 */ extern char un_803FB5C0[];
/* 803FB5D0 */ extern char un_803FB5D0[];
/* 803FB5DC */ extern char un_803FB5DC[];
/* 803FB5E8 */ extern char un_803FB5E8[];
/* 803FB5F4 */ extern char un_803FB5F4[];
/* 803FB600 */ extern char un_803FB600[];
/* 803FB60C */ extern struct un_80304138_objalloc_t_x8 un_803FB60C[7];
/* 803FB6EC */ extern char un_803FB6EC[];
/* 803FB6F8 */ extern char un_803FB6F8[];
/* 803FB704 */ extern char un_803FB704[];
/* 803FB710 */ extern char un_803FB710[];
/* 803FB71C */ extern char un_803FB71C[];
/* 803FB728 */ extern struct un_80304138_objalloc_t_x8 un_803FB728[6];
/* 803FB7E8 */ extern char un_803FB7E8[];
/* 803FB7F4 */ extern char un_803FB7F4[];
/* 803FB800 */ extern char un_803FB800[];
/* 803FB80C */ extern char un_803FB80C[];
/* 803FB818 */ extern char* un_803FB818[4];
/* 803FB828 */ extern char un_803FB828[];
/* 803FB834 */ extern char un_803FB834[];
/* 803FB840 */ extern char un_803FB840[];
/* 803FB84C */ extern char un_803FB84C[];
/* 803FB858 */ extern char un_803FB858[];
/* 803FB864 */ extern char un_803FB864[];
/* 803FB870 */ extern struct un_80304138_objalloc_t_x8 un_803FB870[7];
/* 803FB950 */ extern char un_803FB950[];
/* 803FB95C */ extern char un_803FB95C[];
/* 803FB968 */ extern char un_803FB968[];
/* 803FB974 */ extern char un_803FB974[];
/* 803FB980 */ extern char un_803FB980[];
/* 803FB98C */ extern struct un_80304138_objalloc_t_x8 un_803FB98C[6];
/* 803FBA4C */ extern char un_803FBA4C[];
/* 803FBA5C */ extern char un_803FBA5C[];
/* 803FBA6C */ extern char un_803FBA6C[];
/* 803FBA7C */ extern char un_803FBA7C[];
/* 803FBA8C */ extern char un_803FBA8C[];
/* 803FBA9C */ extern struct un_80304138_objalloc_t_x8 un_803FBA9C[6];
/* 803FBB5C */ extern char un_803FBB5C[];
/* 803FBB68 */ extern char un_803FBB68[];
/* 803FBB74 */ extern char un_803FBB74[];
/* 803FBB80 */ extern char un_803FBB80[];
/* 803FBB8C */ extern char un_803FBB8C[];
/* 803FBB98 */ extern struct un_80304138_objalloc_t_x8 un_803FBB98[6];
/* 803FBC58 */ extern char un_803FBC58[];
/* 803FBC6C */ extern char un_803FBC6C[];
/* 803FBC7C */ extern char un_803FBC7C[];
/* 803FBC8C */ extern char un_803FBC8C[];
/* 803FBC9C */ extern char un_803FBC9C[];
/* 803FBCAC */ extern struct un_80304138_objalloc_t_x8 un_803FBCAC[6];
/* 803FBD6C */ extern char un_803FBD6C[];
/* 803FBD80 */ extern char un_803FBD80[];
/* 803FBD90 */ extern char un_803FBD90[];
/* 803FBDA0 */ extern char un_803FBDA0[];
/* 803FBDB0 */ extern char un_803FBDB0[];
/* 803FBDC0 */ extern struct un_80304138_objalloc_t_x8 un_803FBDC0[6];
/* 803FBE80 */ extern char un_803FBE80[];
/* 803FBE8C */ extern char un_803FBE8C[];
/* 803FBE98 */ extern char un_803FBE98[];
/* 803FBEA4 */ extern char un_803FBEA4[];
/* 803FBEB0 */ extern char un_803FBEB0[];
/* 803FBEBC */ extern char un_803FBEBC[];
/* 803FBEC8 */ extern char un_803FBEC8[];
/* 803FBED4 */ extern char un_803FBED4[];
/* 803FBEE4 */ extern char un_803FBEE4[];
/* 803FBEF4 */ extern char un_803FBEF4[];
/* 803FBF00 */ extern char un_803FBF00[];
/* 803FBF10 */ extern char un_803FBF10[];
/* 803FBF20 */ extern char un_803FBF20[];
/* 803FBF30 */ extern char un_803FBF30[];
/* 803FBF40 */ extern char un_803FBF40[];
/* 803FBF50 */ extern char un_803FBF50[];
/* 803FBF5C */ extern char un_803FBF5C[];
/* 803FBF68 */ extern char un_803FBF68[];
/* 803FBF74 */ extern char* un_803FBF74[18];
/* 803FBFBC */ extern char un_803FBFBC[];
/* 803FBFCC */ extern char un_803FBFCC[];
/* 803FBFD8 */ extern char un_803FBFD8[];
/* 803FBFE4 */ extern char un_803FBFE4[];
/* 803FBFF0 */ extern char un_803FBFF0[];
/* 803FBFFC */ extern struct un_80304138_objalloc_t_x8 un_803FBFFC[6];
/* 803FC0BC */ extern char un_803FC0BC[];
/* 803FC0CC */ extern char un_803FC0CC[];
/* 803FC0D8 */ extern char un_803FC0D8[];
/* 803FC0E4 */ extern char un_803FC0E4[];
/* 803FC0F0 */ extern char un_803FC0F0[];
/* 803FC0FC */ extern struct un_80304138_objalloc_t_x8 un_803FC0FC[6];
/* 803FC1BC */ extern char un_803FC1BC[];
/* 803FC1C8 */ extern char un_803FC1C8[];
/* 803FC1D4 */ extern char un_803FC1D4[];
/* 803FC1E0 */ extern char* un_803FC1E0[3];
/* 803FC1EC */ extern char un_803FC1EC[];
/* 803FC1FC */ extern char un_803FC1FC[];
/* 803FC208 */ extern char un_803FC208[];
/* 803FC214 */ extern char un_803FC214[];
/* 803FC220 */ extern char un_803FC220[];
/* 803FC22C */ extern struct un_80304138_objalloc_t_x8 un_803FC22C[6];
/* 803FC2EC */ extern u32 un_803FC2EC[77];
/* 803FC420 */ extern char un_803FC420[];
/* 803FC42C */ extern char un_803FC42C[];
/* 803FC440 */ extern char un_803FC440[];
/* 803FC454 */ extern char un_803FC454[];
/* 803FC468 */ extern char un_803FC468[];
/* 803FC47C */ extern char un_803FC47C[];
/* 803FC490 */ extern char un_803FC490[];
/* 803FC4A4 */ extern char un_803FC4A4[];
/* 803FC4B8 */ extern char un_803FC4B8[];
/* 803FC60C */ extern char un_803FC60C[];
/* 803FC61C */ extern char un_803FC61C[];
/* 803FC62C */ extern char un_803FC62C[];
/* 803FC63C */ extern struct un_80304138_objalloc_t_x8 un_803FC63C[4];
/* 803FC6BC */ extern char un_803FC6BC[];
/* 803FC6D0 */ extern char un_803FC6D0[];
/* 803FC6DC */ extern char un_803FC6DC[];
/* 803FC6E8 */ extern char un_803FC6E8[];
/* 803FC6F4 */ extern char un_803FC6F4[];
/* 803FC700 */ extern char un_803FC700[];
/* 803FC70C */ extern struct un_80304138_objalloc_t_x8 un_803FC70C[7];
/* 803FC7EC */ extern char un_803FC7EC[];
/* 803FC804 */ extern char un_803FC804[];
/* 803FC810 */ extern char un_803FC810[];
/* 803FC81C */ extern char un_803FC81C[];
/* 803FC828 */ extern struct un_80304138_objalloc_t_x8 un_803FC828[5];
/* 803FC8C8 */ extern struct un_80304138_objalloc_t_x8 un_803FC8C8[5];
/* 803FC968 */ extern char un_803FC968[];
/* 803FC97C */ extern char un_803FC97C[];
/* 803FC98C */ extern char un_803FC98C[];
/* 803FC998 */ extern char un_803FC998[];
/* 803FC9A8 */ extern char un_803FC9A8[];
/* 803FC9BC */ extern char un_803FC9BC[];
/* 803FC9D0 */ extern char un_803FC9D0[];
/* 803FC9E8 */ extern char un_803FC9E8[];
/* 803FC9FC */ extern char un_803FC9FC[];
/* 803FCA10 */ extern char un_803FCA10[];
/* 803FCA20 */ extern char un_803FCA20[];
/* 803FCA30 */ extern char un_803FCA30[];
/* 803FCA40 */ extern struct un_80304138_objalloc_t_x8 un_803FCA40[13];
/* 803FCBE0 */ extern char un_803FCBE0[];
/* 803FCBF4 */ extern char un_803FCBF4[];
/* 803FCC08 */ extern char un_803FCC08[];
/* 803FCC18 */ extern char un_803FCC18[];
/* 803FCC28 */ extern char un_803FCC28[];
/* 803FCC38 */ extern struct un_80304138_objalloc_t_x8 un_803FCC38[6];
/* 803FCCF8 */ extern char un_803FCCF8[];
/* 803FCD04 */ extern char un_803FCD04[];
/* 803FCD10 */ extern char* un_803FCD10[3];
/* 803FCD1C */ extern char un_803FCD1C[];
/* 803FCD34 */ extern struct un_80304138_objalloc_t_x8 un_803FCD34[5];
/* 803FCDD4 */ extern char un_803FCDD4[];
/* 803FCDE8 */ extern char un_803FCDE8[];
/* 803FCDFC */ extern char un_803FCDFC[];
/* 803FCE0C */ extern char un_803FCE0C[];
/* 803FCE1C */ extern char un_803FCE1C[];
/* 803FCE34 */ extern char un_803FCE34[];
/* 803FCE4C */ extern struct un_80304138_objalloc_t_x8 un_803FCE4C[7];
/* 803FCF2C */ extern char un_803FCF2C[];
/* 803FCF38 */ extern char un_803FCF38[];
/* 803FCF44 */ extern char un_803FCF44[];
/* 803FCF50 */ extern char un_803FCF50[];
/* 803FCF5C */ extern char* un_803FCF5C[13];
/* 803FCF90 */ extern char un_803FCF90[];
/* 803FCFA0 */ extern char un_803FCFA0[];
/* 803FCFAC */ extern char un_803FCFAC[];
/* 803FCFC0 */ extern char un_803FCFC0[];
/* 803FCFD4 */ extern char un_803FCFD4[];
/* 803FCFE0 */ extern char un_803FCFE0[];
/* 803FCFEC */ extern char un_803FCFEC[];
/* 803FD000 */ extern char un_803FD000[];
/* 803FD00C */ extern char un_803FD00C[];
/* 803FD01C */ extern char un_803FD01C[];
/* 803FD034 */ extern char un_803FD034[];
/* 803FD044 */ extern char un_803FD044[];
/* 803FD058 */ extern char un_803FD058[];
/* 803FD064 */ extern struct un_80304138_objalloc_t_x8 un_803FD064[14];
/* 803FD224 */ extern char un_803FD224[];
/* 803FD230 */ extern char un_803FD230[];
/* 803FD23C */ extern char un_803FD23C[];
/* 803FD24C */ extern char un_803FD24C[];
/* 803FD258 */ extern char un_803FD258[];
/* 803FD264 */ extern char un_803FD264[];
/* 803FD274 */ extern HSD_ImageDesc un_803FD274;
/* 803FD28C */ extern char un_803FD28C[];
/* 803FD29C */ extern char un_803FD29C[];
/* 803FD2AC */ extern char un_803FD2AC[];
/* 803FD2BC */ extern char un_803FD2BC[];
/* 803FD2D0 */ extern char un_803FD2D0[];
/* 803FD2DC */ extern char un_803FD2DC[];
/* 803FD2E8 */ extern char un_803FD2E8[];
/* 803FD2F4 */ extern char un_803FD2F4[];
/* 803FD304 */ extern char un_803FD304[];
/* 803FD310 */ extern struct un_80304138_objalloc_t_x8 un_803FD310[13];
/* 803FD4B0 */ extern char* un_803FD4B0[5];
/* 803FD4C4 */ extern char un_803FD4C4[];
/* 803FD4D0 */ extern char un_803FD4D0[];
/* 803FD4DC */ extern char* un_803FD4DC[4];
/* 803FD4EC */ extern char un_803FD4EC[];
/* 803FD500 */ extern char un_803FD500[];
/* 803FD50C */ extern char un_803FD50C[];
/* 803FD51C */ extern char un_803FD51C[];
/* 803FD52C */ extern char un_803FD52C[];
/* 803FD53C */ extern char un_803FD53C[];
/* 803FD54C */ extern char un_803FD54C[];
/* 803FD55C */ extern char un_803FD55C[];
/* 803FD56C */ extern char un_803FD56C[];
/* 803FD57C */ extern char un_803FD57C[];
/* 803FD58C */ extern struct un_80304138_objalloc_t_x8 un_803FD58C[16];
/* 803FD78C */ extern char un_803FD78C[];
/* 803FD79C */ extern char un_803FD79C[];
/* 803FD7A8 */ extern char un_803FD7A8[];
/* 803FD7B4 */ extern char un_803FD7B4[];
/* 803FD7C0 */ extern char un_803FD7C0[];
/* 803FD7CC */ extern char un_803FD7CC[];
/* 803FD7DC */ extern char un_803FD7DC[];
/* 803FD7E8 */ extern char un_803FD7E8[];
/* 803FD7F4 */ extern char un_803FD7F4[];
/* 803FD800 */ extern char un_803FD800[];
/* 803FD80C */ extern char un_803FD80C[];
/* 803FD818 */ extern char un_803FD818[];
/* 803FD824 */ extern char un_803FD824[];
/* 803FD830 */ extern char un_803FD830[];
/* 803FD83C */ extern char un_803FD83C[];
/* 803FD848 */ extern char un_803FD848[];
/* 803FD854 */ extern char un_803FD854[];
/* 803FD864 */ extern struct un_80304138_objalloc_t_x8 un_803FD864[19];
/* 803FDAC4 */ extern char un_803FDAC4[];
/* 803FDAD4 */ extern char un_803FDAD4[];
/* 803FDAE4 */ extern char un_803FDAE4[];
/* 803FDAF8 */ extern struct un_80304138_objalloc_t_x8 un_803FDAF8[4];
/* 803FDB78 */ extern char un_803FDB78[];
/* 803FDB88 */ extern char un_803FDB88[];
/* 803FDB9C */ extern struct un_80304138_objalloc_t_x8 un_803FDB9C[4];

/// .sdata
/* 804D5850 */ static int un_804D5850 = 127;
/* 804D5854 */ static int un_804D5854 = 127;
/* 804D5858 */ static int un_804D5858 = 127;
/* 804D585C */ static int un_804D585C = -1;
/* 804D5860 */ static char un_804D5860[] = "NONE";
/* 804D5868 */ static char un_804D5868[] = "ACTIVED";
/* 804D5870 */ static char un_804D5870[] = "AUTO";
/* 804D5878 */ static char un_804D5878[] = "OFF";
/* 804D587C */ static char un_804D587C[] = "ON";
/* 804D5880 */ static char* un_804D5880[2] = { un_804D5878, un_804D587C };
/* 804D5888 */ static char* un_804D5888[2] = { un_803FA3F4, un_803FA404 };
/* 804D5890 */ static char un_804D5890[] = "Master";
/* 804D5898 */ static char un_804D5898[] = "Develop";
/* 804D58A0 */ static char un_804D58A0[] = "Addr4 :";
/* 804D58A8 */ static char un_804D58A8[] = "u32   :";
/* 804D58B0 */ static char un_804D58B0[] = "Addr2 :";
/* 804D58B8 */ static char un_804D58B8[] = "u16   :";
/* 804D58C0 */ static char un_804D58C0[] = "Addr  :";
/* 804D58C8 */ static char un_804D58C8[] = "u8    :";
/* 804D58D0 */ static char un_804D58D0[] = "Nothing";
/* 804D58D8 */ static char un_804D58D8[] = "Verylow";
/* 804D58E0 */ static char un_804D58E0[] = "Low";
/* 804D58E4 */ static char un_804D58E4[] = "Middle";
/* 804D58EC */ static char un_804D58EC[] = "High";
/* 804D58F4 */ static char un_804D58F4[] = "Rule";
/* 804D58FC */ static char* un_804D58FC[2] = { un_803FB064, un_803FB074 };
/* 804D5908 */ static int un_804D5908 ATTRIBUTE_ALIGN(8) = 1;
/* 804D590C */ static int un_804D590C = 1;
/* 804D5910 */ static int un_804D5910 = 1;
/* 804D5914 */ static char un_804D5914[] = "SIMPLE";
/* 804D591C */ static char un_804D591C[] = "Chara :";
/* 804D5924 */ static char un_804D5924[] = "Color :";
/* 804D592C */ static char un_804D592C[] = "Mode :";
/* 804D5934 */ static char un_804D5934[] = "Luigi";
/* 804D593C */ static char un_804D593C[] = "Mars";
/* 804D5944 */ static char un_804D5944[] = "Mewtwo";
/* 804D594C */ static char un_804D594C[] = "Purin";
/* 804D5954 */ static char un_804D5954[] = "Falco";
/* 804D595C */ static char un_804D595C[] = "C-Link";
/* 804D5964 */ static char un_804D5964[] = "Roi";
/* 804D5968 */ static char un_804D5968[] = "Pichu";
/* 804D5970 */ static char un_804D5970[] = "Ganon";
/* 804D5978 */ static char un_804D5978[] = "<Init>\n";
/* 804D5980 */ static char un_804D5980[] = "<Save>\n";
/* 804D5988 */ static char un_804D5988[] = "<Load>\n";
/* 804D5990 */ HSD_SObjDesc un_804D5990 = { &un_803FD274, NULL };
/* 804D5998 */ static char un_804D5998[] = "Init";
/* 804D59A0 */ static char un_804D59A0[] = "Format";
/* 804D59A8 */ static char un_804D59A8[] = "Create";
/* 804D59B0 */ static char un_804D59B0[] = "Save";
/* 804D59B8 */ static char un_804D59B8[] = "Load";
/* 804D59C0 */ static char un_804D59C0[] = "Delete";
/* 804D59C8 */ static char un_804D59C8[] = "Normal";
/* 804D59D0 */ static char un_804D59D0[] = "Team";
/* 804D59D8 */ static char un_804D59D8[] = "Giant";
/* 804D59E0 */ static char un_804D59E0[] = "Bonus";
/* 804D59E8 */ static char un_804D59E8[] = "Corps";
/* 804D59F0 */ static char un_804D59F0[] = "Target";
/* 804D59F8 */ static char un_804D59F8[] = "TEST >";

/// .sbss
/* 4D6DA8 */ static int* un_804D6DA8;
/* 4D6DAC */ static int un_804D6DAC;
/* 4D6DB0 */ static int un_804D6DB0;
/* 4D6DB4 */ static int un_804D6DB4;
/* 4D6DB8 */ static int un_804D6DB8;
/* 4D6DBC */ static int un_804D6DBC;
/* 4D6DC0 */ static int un_804D6DC0;
/* 4D6DC8 */ static s32 un_804D6DC8 ATTRIBUTE_ALIGN(8);
/* 4D6DCC */ static s32 un_804D6DCC;
/* 4D6DD0 */ static f32 un_804D6DD0;
/* 4D6DD4 */ static s32 un_804D6DD4;
/* 4D6DD8 */ static s32 un_804D6DD8;
/* 4D6DDC */ static s32 un_804D6DDC;
/* 4D6DE0 */ static s32 un_804D6DE0;
/* 4D6DE4 */ static s32 un_804D6DE4;
/* 4D6DE8 */ static s32 un_804D6DE8;
/* 4D6DEC */ static s32 un_804D6DEC;
/* 4D6DF0 */ static s32 un_804D6DF0;
/* 4D6DF4 */ static s32 un_804D6DF4;
/* 4D6DF8 */ static s32 un_804D6DF8;
/* 4D6DFC */ static s32 un_804D6DFC;
/* 4D6E00 */ static enum_t un_804D6E00;
/* 4D6E04 */ static void* un_804D6E04;
/* 4D6E08 */ static HSD_GObj* un_804D6E08;
/* 4D6E0C */ static s32 un_804D6E0C;
/* 4D6E10 */ static s32 un_804D6E10;
/* 4D6E14 */ static s32 un_804D6E14;

void un_802FF7DC(void)
{
    struct un_803F9F28_t* data = (struct un_803F9F28_t*) un_803F9F28;
    int* syms;
    lbArchive_LoadSymbols(data->x1DC, &un_804D6DA8, data->x1E8, 0);
    syms = un_804D6DA8;
    data->xB4 = syms[0];
    data->xA8 = syms[1];
    data->x148 = syms[2];
    data->x168 = syms[3];
    data->x174 = syms[4];
    data->x188 = syms[7];
}

bool un_802FF884(char* arg0)
{
    return false;
}

bool un_802FF88C(enum soundtest_callback_arg0 arg0)
{
    un_804D5858 = 0x7F;
    un_804D6DB8 = 0;
    un_804D5854 = 0x7F;
    un_804D5850 = 0x7F;
    un_804D6DB4 = 0;
    un_804D6DB0 = 0;
    un_804D6DC0 = 0;
    un_804D585C = -1;
    un_804D6DBC = lbAudioAx_80024BD0();
    lbAudioAx_800236DC();
    lbAudioAx_800245D4(0x7F);
    lbAudioAx_800245F4(0x7F);
    lbAudioAx_80024614(0x7F);
    if (un_80302DF0()) {
        un_80302DF8(un_80302DF0(), fn_802FFCC8);
    }
    {
        un_80304138_objalloc_t* x = un_80302DF0();
        x->x4->scale_x = 16.0f;
        x->x4->scale_y = 32.0f;
    }
    return 1;
}

bool un_802FF934(enum soundtest_callback_arg0 arg0)
{
    lbAudioAx_80024C08(un_804D6DBC);
}

bool un_802FF958(enum soundtest_callback_arg0 arg0)
{
    u8 tmp = un_804D5854;
    lbAudioAx_800245F4(tmp);
    tmp = un_804D5858;
    lbAudioAx_80024614(tmp);
    tmp = un_804D5850;
    lbAudioAx_800245D4(tmp);
    return 0;
}

bool un_802FF99C(enum soundtest_callback_arg0 arg0)
{
    u8 tmp = un_804D6DAC;
    lbAudioAx_80024634(tmp);
    un_802FFB58(arg0);
    return 0;
}

bool un_802FF9DC(enum soundtest_callback_arg0 arg0)
{
    s32 i;
    s32 total;

    i = un_804D6DB4 = 0;
    for (; i < un_804D6DB0; i++) {
        un_804D6DB4 += ((int**) un_804D6DA8)[6][i];
    }
    un_803F9FA4.entries[7].x14 = (f32) un_804D6DB4;
    total = un_804D6DB4 + ((int**) un_804D6DA8)[6][un_804D6DB0];
    un_803F9FA4.entries[7].x18 = (f32) total;
    return 0;
}

bool un_802FFB58(enum soundtest_callback_arg0 arg0)
{
    if (arg0 == 1) {
        lbAudioAx_80023694();
        lbAudioAx_80023B24(((int**) un_804D6DA8)[5][un_804D6DB4]);
    } else if (arg0 == 0) {
        lbAudioAx_80023694();
    }
    return 0;
}

bool un_802FFBAC(enum soundtest_callback_arg0 arg0)
{
    if (arg0 == 1) {
        if (un_804D585C == un_804D6DB8) {
            int x = (un_804D6DC0 + 1) & 1;
            un_804D6DC0 = x;
            lbAudioAx_80024E50(x);
        } else {
            lbAudioAx_80023F28(un_804D6DB8);
            un_804D585C = un_804D6DB8;
            un_804D6DC0 = 0;
        }
    } else if (arg0 == 0) {
        lbAudioAx_800236DC();
        un_804D585C = -1;
        un_804D6DC0 = 0;
    }
    return 0;
}

bool un_802FFC30(enum soundtest_callback_arg0 arg0)
{
    lbAudioAx_800236DC();
    lbAudioAx_800245D4(0x7F);
    lbAudioAx_800245F4(0x7F);
    lbAudioAx_80024614(0x7F);
    return true;
}

bool un_802FFC6C(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80023694();
        sfxBack();
        lbAudioAx_800236DC();
        lbAudioAx_800245D4(0x7F);
        lbAudioAx_800245F4(0x7F);
        lbAudioAx_80024614(0x7F);
        gm_ChangeGameModeAfterCurrentScene(GM_TITLE);
        gm_801A4B60();
    }
    return true;
}

bool fn_802FFCC8(enum soundtest_callback_arg0 arg0)
{
    return false;
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void un_802FFCD0(int count, void* data)
{
    int* arr = data;
    int i;
    for (i = 0; i < count; i++) {
        arr[i] = arr[count];
    }
}
#ifdef MUST_MATCH
#pragma pop
#endif

void un_802FFD94(int arg0, void* arg1, soundtest_callback arg2)
{
    struct un_80304138_objalloc_t* d;
    if (arg0 == 1) {
        d = un_80302DF0();
        sfxForward();
        un_80304210(d, arg1, 0, -60, 0);
        un_80302DF8(un_80302DF0(), arg2);
    }
}

bool fn_802FFE0C(enum soundtest_callback_arg0 arg0)
{
    switch (arg0) {
    case 0:
        sfxBack();
        un_80304334(un_80302DF0());
        break;
    case 6:
        sfxForward();
        gm_SetPendingSceneIndex(4);
        gm_801A4B60();
        break;
    default:
        break;
    }
    return 0;
}

bool fn_802FFE6C(enum soundtest_callback_arg0 update_scene)
{
    bool res = update_scene;
    if (update_scene == false) {
        sfxBack();
        un_80304334(un_80302DF0());
        res = false;
    }

    return res;
}

bool un_802FFEA4(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        sfxForward();
        gm_SetPendingSceneIndex(0x4);
        gm_801A4B60();
    }

    return false;
}

void un_802FFEE0(struct UnkSoundTestData0* arg0)
{
    u16 val = MIN((u16) un_803FA258.x12C, 0x3E);
    arg0->x0 = val;
    arg0->x2 = un_803FA258.x130;
    arg0->x4 = 0x98967F;
    arg0->x8 = 0;
}

void un_802FFF2C(StartMeleeData* arg0)
{
    StartMeleeRules* r = &arg0->rules;
    struct un_803FA128_t* s = (struct un_803FA128_t*) un_803FA128;
    struct un_803FA128_x130_t* sp;
    s32 i;
    u16 timer;

    gm_80167A64(r);
    r->x2_2 = 0;
    r->is_teams = s->x130.xC;
    switch (s->x130.xC8) {
    case 0:
        r->match_mode = 0;
        timer = s->x130.xCC[1] + s->x130.xCC[0] * 0x3C;
        if (timer != 0) {
            r->time_limit = timer;
            r->x0_6 = 1;
        } else {
            r->x0_6 = 0;
        }
        break;
    case 1:
        r->match_mode = 1;
        r->x0_6 = 0;
        break;
    case 2:
        r->match_mode = 2;
        timer = s->x130.xCC[1] + s->x130.xCC[0] * 0x3C;
        if (timer != 0) {
            r->time_limit = timer;
            r->x0_6 = 1;
        } else {
            r->x0_6 = 0;
        }
        break;
    default:
        r->match_mode = 0;
        r->x0_6 = 0;
        break;
    }
    r->stkind = s->x130.x8;
    r->x20 = -1;
    r->xB = s->x130.xCC[3] - 1;
    r->xC = -1;
    r->x30 = s->x130.xEC;
    gm_80167A14(arg0->players);
    sp = &s->x130;
    for (i = 0; i < 4; i++) {
        arg0->players[i].c_kind = sp->x10[i];
        arg0->players[i].slot_type = sp->x24[i];
        arg0->players[i].color = sp->x38[i];
        arg0->players[i].sub_color = sp->x48[i];
        arg0->players[i].team = sp->x58[i];
        arg0->players[i].xC_b0 = sp->xDC[i];
        arg0->players[i].x12 = sp->x68[i];
        arg0->players[i].x18 = sp->x78[i];
        arg0->players[i].x1C = sp->x88[i];
        arg0->players[i].xE = sp->xA8[i];
        arg0->players[i].cpu_level = sp->xB8[i];
        arg0->players[i].stocks = s->x130.xCC[2];
        arg0->players[i].xC_b1 = 0;
        arg0->players[i].x20 = sp->x98[i];
    }
}

bool un_803001DC(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        sfxForward();
        gm_SetPendingSceneIndex(0x1);
        gm_801A4B60();
    }

    return false;
}

bool un_80300218(enum soundtest_callback_arg0 arg0)
{
    lbLang_SetSavedLanguage(un_803FA258.x0);
    return 0;
}

bool un_80300248(enum soundtest_callback_arg0 arg0)
{
    if (un_803FA258.x4[0] && arg0 == 1) {
        sfxForward();
        gmMainLib_8015FB68();
    }
    return 0;
}

bool un_80300290(enum soundtest_callback_arg0 arg0)
{
    if (arg0 == 1) {
        struct un_80304138_objalloc_t* x = un_80302DF0();
        sfxForward();
        un_80304210(x, &un_803FA658, 0, -60, 0);
        un_80302DF8(un_80302DF0(), fn_802FFE6C);
    }
    return 0;
}

bool un_803002FC(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        sfxForward();
        gm_SetPendingSceneIndex(0x2);
        gm_801A4B60();
    }

    return false;
}

bool un_80300338(enum soundtest_callback_arg0 arg0)
{
    struct un_803FA128_t* data = (struct un_803FA128_t*) un_803FA128;
    u8* src;

    src = gmMainLib_8045A6C0;
    src = src + data->x220;

    data->x224 = src[0x1868];
    data->x225 = src[0x1869];
    data->x226 = src[0x186A];
    data->x227 = src[0x186B];
    return 0;
}

bool un_80300378(enum soundtest_callback_arg0 arg0)
{
    struct un_803FA128_t* data = (struct un_803FA128_t*) un_803FA128;
    u8* ptr;

    data->x220 &= 0xFFFE;

    ptr = gmMainLib_8045A6C0;
    ptr = ptr + data->x220;

    data->x224 = ptr[0x1868];
    data->x225 = ptr[0x1869];
    data->x226 = ptr[0x186A];
    data->x227 = ptr[0x186B];

    return 0;
}

bool un_803003C4(enum soundtest_callback_arg0 arg0)
{
    struct un_803FA128_t* data = (struct un_803FA128_t*) un_803FA128;
    u8* ptr;

    data->x220 &= 0xFFFC;

    ptr = gmMainLib_8045A6C0;
    ptr = ptr + data->x220;

    data->x224 = ptr[0x1868];
    data->x225 = ptr[0x1869];
    data->x226 = ptr[0x186A];
    data->x227 = ptr[0x186B];

    return 0;
}

bool un_80300410(enum soundtest_callback_arg0 arg0)
{
    struct un_803FA128_t* data = (struct un_803FA128_t*) un_803FA128;

    if (arg0 == 1) {
        u8* dst;
        sfxForward();
        dst = gmMainLib_8045A6C0;
        dst += data->x220;
        dst[0x1868] = data->x224;
        dst[0x1869] = data->x225;
        dst[0x186A] = data->x226;
        dst[0x186B] = data->x227;
    }
    return 0;
}

/// these will try to inline un_802FFD94 otherwise
#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
bool un_80300480(enum soundtest_callback_arg0 arg0)
{
    un_802FFD94(arg0, &un_803FB168, fn_802FFE0C);
    return 0;
}

bool un_803004B4(enum soundtest_callback_arg0 arg0)
{
    un_802FFD94(arg0, &un_803FA8E8, fn_802FFE6C);
    return 0;
}

bool un_803004E8(enum soundtest_callback_arg0 arg0)
{
    un_802FFD94(arg0, &un_803FAA44, fn_802FFE6C);
    return 0;
}

bool un_8030051C(enum soundtest_callback_arg0 arg0)
{
    un_802FFD94(arg0, &un_803FB60C, fn_802FFE6C);
    return 0;
}

bool un_80300550(enum soundtest_callback_arg0 arg0)
{
    un_802FFD94(arg0, &un_803FB728, fn_802FFE6C);
    return 0;
}

bool un_80300584(enum soundtest_callback_arg0 arg0)
{
    un_802FFD94(arg0, &un_803FB870, fn_802FFE6C);
    return 0;
}

bool un_803005B8(enum soundtest_callback_arg0 arg0)
{
    un_802FFD94(arg0, &un_803FB98C, fn_802FFE6C);
    return 0;
}

bool un_803005EC(enum soundtest_callback_arg0 arg0)
{
    un_802FFD94(arg0, &un_803FBA9C, fn_802FFE6C);
    return 0;
}

bool un_80300620(enum soundtest_callback_arg0 arg0)
{
    un_802FFD94(arg0, &un_803FBB98, fn_802FFE6C);
    return 0;
}

bool un_80300654(enum soundtest_callback_arg0 arg0)
{
    un_802FFD94(arg0, &un_803FBCAC, fn_802FFE6C);
    return 0;
}

bool un_80300688(enum soundtest_callback_arg0 arg0)
{
    un_802FFD94(arg0, &un_803FBDC0, fn_802FFE6C);
    return 0;
}

bool un_803006BC(enum soundtest_callback_arg0 arg0)
{
    un_802FFD94(arg0, &un_803FBFFC, fn_802FFE6C);
    return 0;
}

bool un_803006F0(enum soundtest_callback_arg0 arg0)
{
    un_802FFD94(arg0, &un_803FC0FC, fn_802FFE6C);
    return 0;
}

bool un_80300724(enum soundtest_callback_arg0 arg0)
{
    un_802FFD94(arg0, &un_803FC22C, fn_802FFE6C);
    return 0;
}
#ifdef MUST_MATCH
#pragma pop
#endif

bool un_80300758(enum soundtest_callback_arg0 arg0)
{
    if (arg0 == 1) {
        un_802FFCD0(4, (u8*) &un_803FA258 + 0x10);
    }
}

bool un_80300790(enum soundtest_callback_arg0 arg0)
{
    if (arg0 == 1) {
        un_802FFCD0(4, (u8*) &un_803FA258 + 0x24);
    }
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
bool un_803007C8(enum soundtest_callback_arg0 arg0)
{
    un_802FFD94(arg0, &un_803FC63C, fn_802FFE6C);
    return 0;
}

bool un_803007FC(enum soundtest_callback_arg0 arg0)
{
    un_802FFD94(arg0, &un_803FCA40, fn_802FFE6C);
    return 0;
}

bool un_80300830(enum soundtest_callback_arg0 arg0)
{
    un_802FFD94(arg0, &un_803FCC38, fn_802FFE6C);
    return 0;
}

bool un_80300864(enum soundtest_callback_arg0 arg0)
{
    un_802FFD94(arg0, &un_803FCE4C, fn_802FFE6C);
    return 0;
}

bool un_80300898(enum soundtest_callback_arg0 arg0)
{
    un_802FFD94(arg0, &un_803FD064, fn_802FFE6C);
    return 0;
}

bool un_803008CC(enum soundtest_callback_arg0 arg0)
{
    un_802FFD94(arg0, &un_803FDAF8, fn_802FFE6C);
    return 0;
}

bool un_80300900(enum soundtest_callback_arg0 arg0)
{
    un_802FFD94(arg0, &un_803FDB9C, fn_802FFE6C);
    return 0;
}

bool un_80300934(enum soundtest_callback_arg0 arg0)
{
    un_802FFD94(arg0, &un_803FD310, fn_802FFE6C);
    return 0;
}
#ifdef MUST_MATCH
#pragma pop
#endif

bool un_80300968(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        sfxForward();
        gm_ChangeGameModeAfterCurrentScene(GM_HANYU_CSS);
        gm_801A4B60();
    }

    return false;
}

bool un_803009A4(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        sfxForward();
        gm_ChangeGameModeAfterCurrentScene(GM_HANYU_SSS);
        gm_801A4B60();
    }

    return false;
}

bool un_803009E0(enum soundtest_callback_arg0 arg0)
{
    s32* new_var;
    switch (un_804D6DD8) {
    case 2:
        new_var = gmMainLib_8015D06C((u8) un_804D6DC8);
        {
            u32 val = (u32) (*new_var);
            un_804D6DD0 = (float) (val / 100U);
            break;
        }

    case 3: {
        s32 result = gmMainLib_8015D48C((u8) un_804D6DC8);
        gmMainLib_8015D4E8((u8) un_804D6DC8, result);
        un_804D6DCC = result;
        break;
    }
    }
    return 0;
}

bool un_80300A88(enum soundtest_callback_arg0 arg0)
{
    switch (un_804D6DD8) {
    case 2:
        break;
    case 3:
        if (un_804D6DCC >= 1) {
            un_804D6DCC = 1;
        }
        break;
    }
    return 0;
}

bool un_80300AB8(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        sfxForward();
        gm_SetPendingSceneIndex(0x4);
        gm_801A4B60();
    }

    return false;
}

bool un_80300AF4(enum soundtest_callback_arg0 arg0)
{
    if (arg0 == 1) {
        struct un_803FA258_t* data;
        sfxForward();
        data = &un_803FA258;
        data->x4[1] = 0x3F;
        data->x4[3] = 0xE;
        data->x24[1] = 3;
        data->x24[2] = 3;
        data->x24[3] = 3;
        gm_SetPendingSceneIndex(4);
        gm_801A4B60();
    }
    return false;
}

bool un_80300B58(enum soundtest_callback_arg0 arg0)
{
    if (arg0 == 1) {
        struct un_803FA258_t* data;
        sfxForward();
        {
            struct un_803FA258_t* data = &un_803FA258;
            data->x4[1] = 0x3B;
            data->x4[3] = 0x2;
            data->x24[1] = 3;
            data->x24[2] = 3;
            data->x24[3] = 3;
        }
        gm_SetPendingSceneIndex(4);
        gm_801A4B60();
    }
    return false;
}

bool un_80300BBC(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        Toy_803124BC();
        Toy_80311680();
        gm_ChangeGameModeAfterCurrentScene(GM_TOY_GALLERY);
        gm_801A4B60();
    }

    return false;
}

bool un_80300BF8(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        Toy_803124BC();
        Toy_SetUnlockState(0xE6, true);
        gm_ChangeGameModeAfterCurrentScene(GM_MENU);
        gm_801A4B60();
    }

    return false;
}

bool un_80300C3C(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        Toy_803124BC();
        Toy_SetUnlockState(0xC9, true);
        gm_ChangeGameModeAfterCurrentScene(GM_MENU);
        gm_801A4B60();
    }

    return false;
}

bool un_80300C80(enum soundtest_callback_arg0 arg0)
{
    if (arg0 == 1) {
        u32* ptr = gmMainLib_8015CCF0();
        *ptr = un_804D6DDC * 10;
        Toy_803124BC();
        gm_ChangeGameModeAfterCurrentScene(GM_MENU);
        gm_801A4B60();
    }
    return false;
}

bool fn_80300CC8(enum soundtest_callback_arg0 arg0)
{
    int* r29;
    int* r30;
    int* r31;

    switch (arg0) {
    case 0:
        sfxBack();
        un_80304334(un_80302DF0());
        break;
    case 6:
        sfxForward();
        r29 = gmMainLib_GetTimeMatchTotal();
        r30 = gmMainLib_GetStockMatchTotal();
        r31 = gmMainLib_GetCoinMatchTotal();
        {
            int* ptr = gmMainLib_GetBonusMatchTotal();
            *r29 = un_804D6DE0;
            *r30 = un_804D6DE4;
            *r31 = un_804D6DE8;
            *ptr = un_804D6DEC;
        }
        gm_ChangeGameModeAfterCurrentScene(GM_MENU);
        gm_801A4B60();
        break;
    default:
        break;
    }
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
bool un_80300D78(enum soundtest_callback_arg0 arg0)
{
    if (arg0 == 1) {
        lbAudioAx_80024030(1);
        un_804D6DE0 = un_804D6DF0;
        un_804D6DE4 = un_804D6DF0;
        un_804D6DE8 = un_804D6DF0;
        un_804D6DEC = un_804D6DF0;
        un_802FFD94(arg0, &un_803FC70C, fn_80300CC8);
    }
    return 0;
}
#ifdef MUST_MATCH
#pragma pop
#endif

bool fn_80300DE0(enum soundtest_callback_arg0 arg0)
{
    s32* ptr;

    ptr = gmMainLib_8015D06C(un_804D6DC8);
    switch (arg0) {
    case 0:
        sfxBack();
        un_80304334(un_80302DF0());
        break;
    case 6:
        sfxForward();
        *ptr = (u32) (100.0f * un_804D6DD0);
        gm_ChangeGameModeAfterCurrentScene(GM_MENU);
        gm_801A4B60();
        break;
    default:
        break;
    }
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
bool un_80300E74(enum soundtest_callback_arg0 arg0)
{
    if (arg0 == 1) {
        lbAudioAx_80024030(1);
        un_804D6DD8 = 2;
        un_802FFD94(arg0, &un_803FC8C8, fn_80300DE0);
    }
    return 0;
}
#ifdef MUST_MATCH
#pragma pop
#endif

bool fn_80300ED0(enum soundtest_callback_arg0 arg0)
{
    switch (arg0) {
    case 0:
        sfxBack();
        un_80304334(un_80302DF0());
        break;
    case 6:
        sfxForward();
        gmMainLib_8015D4E8(un_804D6DC8, un_804D6DCC);
        gm_ChangeGameModeAfterCurrentScene(GM_MENU);
        gm_801A4B60();
        break;
    default:
        break;
    }
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
bool un_80300F3C(enum soundtest_callback_arg0 arg0)
{
    if (arg0 == 1) {
        lbAudioAx_80024030(1);
        un_804D6DD8 = 3;
        un_802FFD94(arg0, &un_803FC828, fn_80300ED0);
    }
    return 0;
}
#ifdef MUST_MATCH
#pragma pop
#endif

bool un_80300F98(enum soundtest_callback_arg0 arg0)
{
    s32* temp_r31;

    if (arg0 == 1) {
        temp_r31 = gmMainLib_GetKOTotal();
        sfxForward();
        *temp_r31 = un_804D6DF4;
        gm_ChangeGameModeAfterCurrentScene(GM_MENU);
        gm_801A4B60();
    }
    return 0;
}

bool un_80300FEC(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        sfxForward();
        gm_SetPendingSceneIndex(0x4);
        gm_801A4B60();
    }

    return false;
}

bool un_80301028(enum soundtest_callback_arg0 arg0)
{
    if (arg0 == 1) {
        struct gmm_x0_528_t* ptr = gmMainLib_8015CDD4();
        ptr->x5 = un_804D5908 - 1;
        sfxForward();
        gm_ChangeGameModeAfterCurrentScene(GM_ADVENTURE);
        gm_801A4B60();
    }
    return 0;
}

bool un_80301074(enum soundtest_callback_arg0 arg0)
{
    if (arg0 == 1) {
        struct gmm_x0_528_t* ptr = gmMainLib_8015CDC8();
        ptr->x5 = un_804D590C - 1;
        sfxForward();
        gm_ChangeGameModeAfterCurrentScene(GM_CLASSIC);
        gm_801A4B60();
    }
    return 0;
}

bool un_803010C0(enum soundtest_callback_arg0 arg0)
{
    if (arg0 == 1) {
        struct gmm_x0_528_t* ptr = gmMainLib_8015CDE0();
        ptr->x5 = un_804D5910 - 1;
        sfxForward();
        gm_ChangeGameModeAfterCurrentScene(GM_ALLSTAR);
        gm_801A4B60();
    }
    return 0;
}

bool fn_8030110C(enum soundtest_callback_arg0 arg0)
{
    switch (arg0) {
    case 0:
        sfxBack();
        un_80304334(un_80302DF0());
        break;
    case 6:
        sfxForward();
        gm_801BEFA4(un_804D6DF8);
        gm_801BEFC0(un_804D6DFC);
        {
            struct gmm_x0_528_t* ptr = gmMainLib_8015CDC8();
            ptr->c_kind = (s8) un_804D6DF8;
            ptr->color = (u8) un_804D6DFC;
        }
        switch (un_804D6E00) {
        case 0:
            gm_ChangeGameModeAfterCurrentScene(GM_DEBUG_GOVER);
            gm_801BF040(0x15);
            break;
        case 1:
            gm_ChangeGameModeAfterCurrentScene(GM_DEBUG_GOVER);
            gm_801BF040(0x16);
            break;
        case 2:
            gm_ChangeGameModeAfterCurrentScene(GM_DEBUG_GOVER);
            gm_801BF040(0x17);
            break;
        }
        gm_801A4B60();
        break;
    default:
        break;
    }
    return 0;
}

bool fn_803011EC(enum soundtest_callback_arg0 arg0)
{
    switch (arg0) {
    case 0:
        sfxBack();
        un_80304334(un_80302DF0());
        break;
    case 6:
        sfxForward();
        gm_801BEFA4(un_804D6DF8);
        gm_801BEFC0(un_804D6DFC);
        {
            s8 c_kind = (s8) un_804D6DF8;
            gm_GetAllStarData()->x0.ckind = c_kind;
        }
        {
            u8 color = (u8) un_804D6DFC;
            gm_GetAllStarData()->x0.color = color;
        }
        gm_ChangeGameModeAfterCurrentScene(GM_CLASSIC_GOVER);
        gm_801A4B60();
        break;
    default:
        break;
    }
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
bool un_80301280(enum soundtest_callback_arg0 arg0)
{
    if (arg0 == 1) {
        lbAudioAx_80024030(1);
        un_802FFD94(arg0, &un_803FCD34, fn_803011EC);
    }
    return 0;
}

bool un_803012D4(enum soundtest_callback_arg0 arg0)
{
    if (arg0 == 1) {
        lbAudioAx_80024030(1);
        un_802FFD94(arg0, &un_803FCD34, fn_8030110C);
    }
    return 0;
}
#ifdef MUST_MATCH
#pragma pop
#endif

bool un_80301328(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        sfxForward();
        gm_801BF708(0x0);
        gm_ChangeGameModeAfterCurrentScene(GM_OPENING_MV);
        gm_801A4B60();
    }

    return false;
}

bool un_8030136C(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        sfxForward();
        gm_801BF708(0x5);
        gm_ChangeGameModeAfterCurrentScene(GM_OPENING_MV);
        gm_801A4B60();
    }

    return false;
}

bool un_803013B0(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        sfxForward();
        gm_ChangeGameModeAfterCurrentScene(GM_DEBUG_CUTSCENE);
        gm_801A4B60();
    }

    return false;
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
bool un_803013EC(enum soundtest_callback_arg0 arg0)
{
    un_802FFD94(arg0, &un_803FD58C, un_80301B48);
    return 0;
}

bool un_80301420(enum soundtest_callback_arg0 arg0)
{
    un_802FFD94(arg0, &un_803FD864, un_80301C80);
    return 0;
}
#ifdef MUST_MATCH
#pragma pop
#endif

bool un_80301454(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        sfxForward();
        gm_ChangeGameModeAfterCurrentScene(GM_BOOT);
        gm_801A4B60();
    }

    return false;
}

bool un_80301490(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        sfxForward();
        gm_SetPendingSceneIndex(0xD);
        gm_801A4B60();
    }

    return false;
}

bool un_803014CC(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        sfxForward();
        gm_SetPendingSceneIndex(0x7);
        gm_801A4B60();
    }

    return false;
}

bool un_80301508(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        sfxForward();
        gm_SetPendingSceneIndex(0x3);
        gm_801A4B60();
    }

    return false;
}

bool un_80301544(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        sfxForward();
        gm_SetPendingSceneIndex(0x9);
        gm_801A4B60();
    }

    return false;
}

bool un_80301580(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        sfxForward();
        gm_SetPendingSceneIndex(0xC);
        gm_801A4B60();
    }

    return false;
}

bool un_803015BC(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        sfxForward();
        gm_ChangeGameModeAfterCurrentScene(GM_PROGRESSIVE_SCAN);
        gm_801A4B60();
    }

    return false;
}

bool un_803015F8(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        sfxForward();
        gm_SetPendingSceneIndex(0xA);
        gm_801A4B60();
    }

    return false;
}

bool un_80301634(enum soundtest_callback_arg0 arg0)
{
    HSD_GObj* gobj;
    void* r31;
    void* r3;

    OSReport(un_804D5978);
    lb_8001C550();
    lb_8001D164(0);
    r31 = HSD_MemAlloc(lbSnap_8001E210());
    r3 = HSD_MemAlloc(lbSnap_8001E204());
    lbSnap_8001E218(r3, r31);
    un_804D6E04 = HSD_MemAlloc(0x96000);
    gobj = GObj_Create(0x13, 0x14, 0);
    HSD_SObjLib_803A55DC(gobj, 0x280, 0x1E0, 0xC);
    gobj->gxlink_prios = 0x40000;
    un_804D6E08 = 0;
    return 0;
}

bool un_803016D8(enum soundtest_callback_arg0 arg0)
{
    if (arg0 != 1) {
        return 0;
    }
    OSReport(un_803FD224);
    {
        s32 result = lb_8001B8C8(0);
        OSReport(un_803FD230, result);
    }
    return 0;
}

bool un_80301734(enum soundtest_callback_arg0 arg0)
{
    if (arg0 != 1) {
        return 0;
    }
    OSReport(un_803FD23C);
    {
        s32 result = lb_8001C87C();
        OSReport(un_803FD230, result);
    }
    return 0;
}

bool un_8030178C(enum soundtest_callback_arg0 arg0)
{
    if (arg0 != 1) {
        return 0;
    }
    OSReport(un_803FD24C);
    {
        s32 result = lb_8001C8BC();
        OSReport(un_803FD230, result);
        if (result == 0) {
            lb_8001CBAC(0);
        }
    }
    return 0;
}

bool un_80301800(enum soundtest_callback_arg0 arg0)
{
    if (arg0 != 1) {
        return 0;
    }
    OSReport(un_804D5980);
    lb_8001CE00();
    return 0;
}

bool un_80301840(enum soundtest_callback_arg0 arg0)
{
    if (arg0 != 1) {
        return 0;
    }
    OSReport(un_804D5988);
    {
        s32 result = lb_8001CBBC();
        gmMainLib_8015FA34(result);
        if (result == 0 || result == 2) {
            lb_8001CBAC(0);
        }
        OSReport(un_803FD230, result);
    }
    return 0;
}

bool un_803018BC(enum soundtest_callback_arg0 arg0)
{
    if (arg0 != 1) {
        return 0;
    }
    OSReport(un_803FD258);
    {
        s32 result = lb_8001CC4C();
        OSReport(un_803FD230, result);
    }
    lb_8001CBAC(4);
    return 0;
}

bool un_8030191C(enum soundtest_callback_arg0 arg0)
{
    if (arg0 != 1) {
        return 0;
    }
    OSReport(un_803FD264);
    lbSnap_8001D40C(0);
    return 0;
}

bool un_80301964(enum soundtest_callback_arg0 arg0)
{
    if (arg0 != 1) {
        return 0;
    }

    OSReport(un_803FD28C);

    if (lbSnap_8001E058(0, un_804D6E0C) == 0xB) {
        s32 result;
        do {
            result = lb_8001B6F8();
        } while (result == 0xB);

        if (result == 0 && lbSnap_8001DE8C(un_804D6E04) != 0) {
            HSD_GObj* gobj;
            HSD_SObj* sobj;

            if (un_804D6E08 != NULL) {
                HSD_GObjPLink_80390228(un_804D6E08);
            }

            gobj = GObj_Create(0xE, 0xF, 0);
            GObj_SetupGXLink(gobj, HSD_SObjLib_803A49E0, 0x12, 0);
            un_803FD274.image_ptr = un_804D6E04;
            sobj = HSD_SObjLib_803A477C(gobj, &un_804D5990, 0, 0, 0x80, 0);
            sobj->x10 = 320.0f;
            sobj->x14 = 240.0f;
            sobj->x40 |= 2;
            un_804D6E08 = gobj;
        }
    }

    return 0;
}

bool un_80301A64(enum soundtest_callback_arg0 arg0)
{
    s32 result;

    if (arg0 != 1) {
        return 0;
    }

    OSReport(un_803FD29C);
    result = lbSnap_8001D5FC(0, un_804D6E10);
    if (result == 0xB) {
        do {
            result = lb_8001B6F8();
        } while (result == 0xB);

        if (result == 0) {
            lbSnap_8001D40C(0);
        }
    }
    return 0;
}

bool un_80301AD4(enum soundtest_callback_arg0 arg0)
{
    s32 result;

    if (arg0 != 1) {
        return 0;
    }

    OSReport(un_803FD2AC);
    result = lbSnap_8001D7B0(0, un_804D6E14, un_804D6E10);
    if (result == 0xB) {
        do {
            result = lb_8001B6F8();
        } while (result == 0xB);

        if (result == 0) {
            lbSnap_8001D40C(0);
        }
    }
    return 0;
}

bool un_80301B48(enum soundtest_callback_arg0 arg0)
{
    switch (arg0) {
    case 0:
        sfxBack();
        un_80304334(un_80302DF0());
        break;
    case 6:
        sfxForward();
        gm_SetPendingSceneIndex(6);
        gm_801A4B60();
        break;
    default:
        break;
    }
    return false;
}

void un_80301BA8(struct UnkSoundTestData1* out)
{
    out->unk_0 = un_803FA258.x104;
    out->unk_4 = un_803FA258.x108;
    out->unk_A = un_803FA258.x100;
    out->unk_B = un_803FA258.x10C;
    out->unk_C = un_803FA258.x11C;
    out->unk_8 = 0;
    out->unk_9 = 0x78;
    out->unk_D = un_803FA258.x110;
    out->unk_19 = un_803FA258.xF8;
    out->unk_E = un_803FA258.x114;
    out->unk_1A = un_803FA258.xF8;
    out->unk_F = un_803FA258.x118;
    out->unk_1B = un_803FA258.xF8;
    out->unk_10 = un_803FA258.x120;
    out->unk_1C = un_803FA258.xFC;
    out->unk_11 = un_803FA258.x124;
    out->unk_1D = un_803FA258.xFC;
    out->unk_12 = un_803FA258.x128;
    out->unk_1E = un_803FA258.xFC;
    out->unk_13 = 0;
    out->unk_14 = 0;
    out->unk_15 = 0;
    out->unk_16 = 0;
    out->unk_17 = 0;
    out->unk_18 = 0;
}

void un_80301C64(un_80301C64_t* arg0)
{
    arg0->x0 = un_803FA258.x138;
    arg0->x4 = 0;
}

bool un_80301C80(enum soundtest_callback_arg0 arg0)
{
    switch (arg0) {
    case 0:
        sfxBack();
        un_80304334(un_80302DF0());
        break;
    case 6:
        sfxForward();
        gm_SetPendingSceneIndex(0xB);
        gm_801A4B60();
        break;
    default:
        break;
    }
    return 0;
}

bool un_80301CE0(enum soundtest_callback_arg0 arg0)
{
    switch (arg0) {
    case 6:
        sfxForward();
        gm_SetPendingSceneIndex(0xB);
        gm_801A4B60();
        break;
    case 1:
        un_802FFCD0(4, un_803FA258.x144);
        break;
    default:
        break;
    }
}

bool un_80301D40(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        sfxForward();
        gm_ChangeGameModeAfterCurrentScene(GM_CAMERA_VS);
        gm_801A4B60();
    }

    return false;
}

bool un_80301D7C(enum soundtest_callback_arg0 arg0)
{
    if (arg0 == 1) {
        sfxForward();
        gm_801BEB74(un_803FA258.x188 - 1);
        gm_ChangeGameModeAfterCurrentScene(GM_EVENT);
        gm_801A4B60();
    }
    return 0;
}

bool un_80301DCC(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        sfxForward();
        gm_SetPendingSceneIndex(0x4);
        gm_801A4B60();
    }

    return false;
}

bool un_80301E08(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        sfxForward();
        gm_SetPendingSceneIndex(0xE);
        gm_801A4B60();
    }

    return false;
}

/// .data
/* 803F9EF0 */ char lbl_803F9EF0[0x20] = "Remove Target %x (n %x) Id %d\n";
/* 803F9F10 */ char lbl_803F9F10[0x18] = "Remove All Over\n";
/* 803F9F28 */ char un_803F9F28[] = "Sound Test Menu";
/* 803F9F38 */ char un_803F9F38[] = "Sound Mode ";
/* 803F9F44 */ char un_803F9F44[] = "Mas Volume";
/* 803F9F50 */ char un_803F9F50[] = "FGM Volume";
/* 803F9F5C */ char un_803F9F5C[] = "BGM Volume";
/* 803F9F68 */ char un_803F9F68[] = "DSP Level";
/* 803F9F74 */ char un_803F9F74[] = "FGM Group";
/* 803F9F80 */ char un_803F9F80[] = "FGM Name";
/* 803F9F8C */ char un_803F9F8C[] = "BGM Name";
/* 803F9F98 */ char un_803F9F98[] = "-- EXIT --";

/* 803F9FA4 */ struct SoundTestMenuData un_803F9FA4 = {
    {
        { 0, un_802FF88C, un_803F9F28, NULL, NULL, 0.0f, 0.0f, 0.0f },
        { 2, un_802FF934, un_803F9F38, NULL, &un_804D6DBC, 0.0f, 0.0f, 0.0f },
        { 3, un_802FF958, un_803F9F44, NULL, &un_804D5850, 0.0f, 127.0f,
          1.0f },
        { 3, un_802FF958, un_803F9F50, NULL, &un_804D5854, 0.0f, 127.0f,
          1.0f },
        { 3, un_802FF958, un_803F9F5C, NULL, &un_804D5858, 0.0f, 127.0f,
          1.0f },
        { 3, un_802FF99C, un_803F9F68, NULL, &un_804D6DAC, 0.0f, 127.0f,
          1.0f },
        { 2, un_802FF9DC, un_803F9F74, NULL, &un_804D6DB0, 0.0f, 55.0f, 1.0f },
        { 2, un_802FFB58, un_803F9F80, NULL, &un_804D6DB4, 0.0f, 0.0f, 0.0f },
        { 2, un_802FFBAC, un_803F9F8C, NULL, &un_804D6DB8, 0.0f, 98.0f, 1.0f },
        { 1, un_802FFC6C, un_803F9F98, NULL, NULL, 0.0f, 0.0f, 0.0f },
        { 9, un_802FFC30, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
    },
    "SmSt.dat",
    "smSoundTestLoadData",
};
/* 803FA128 */ int un_803FA128[76] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 3, 2, 2, 5, 5, 4, 6, 6, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 6, 6, 5, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5,
};
/* 803FA258 */ struct un_803FA258_t un_803FA258 = {
    /* 0x000 */ 0,
    /* 0x004 */ { 0, 32, 0, 6 },
    /* 0x014 */ { 8, 6, 6, 8 },
    /* 0x024 */ { 0, 0, 3, 3 },
    /* 0x034 */ 0,
    /* 0x038 */ { 0, 0, 0, 0 },
    /* 0x048 */ { 0, 0, 0, 0 },
    /* 0x058 */ { 0, 0, 0, 0 },
    /* 0x068 */ { 0, 0, 0, 0 },
    /* 0x078 */ { 1.0f, 1.0f, 1.0f, 1.0f },
    /* 0x088 */ { 1.0f, 1.0f, 1.0f, 1.0f },
    /* 0x098 */ { 1.0f, 1.0f, 1.0f, 1.0f },
    /* 0x0A8 */ { 4, 4, 4, 4 },
    /* 0x0B8 */ { 5, 5, 5, 5 },
    /* 0x0C8 */ 0,
    /* 0x0CC */ { 0, 0, 0, 0 },
    /* 0x0DC */ { 0, 0, 0, 0 },
    /* 0x0EC */ 1.0f,
    /* 0x0F0 */ 0x0,
    /* 0x0F2 */ { 0, 0 },
    /* 0x0F4 */ 0x0,
    /* 0x0F5 */ 0x0,
    /* 0x0F6 */ 0x0,
    /* 0x0F7 */ 0x0,
    /* 0x0F8 */ 0,
    /* 0x0FC */ 1,
    /* 0x100 */ 1,
    /* 0x104 */ 0,
    /* 0x108 */ 0,
    /* 0x10C */ 1,
    /* 0x110 */ 0,
    /* 0x114 */ 0,
    /* 0x118 */ 0,
    /* 0x11C */ 1,
    /* 0x120 */ 0,
    /* 0x124 */ 0,
    /* 0x128 */ 0,
    /* 0x12C */ 0,
    /* 0x130 */ 0,
    /* 0x134 */ 0,
    /* 0x138 */ NULL,
    /* 0x13C */ 0,
    /* 0x140 */ 0,
    /* 0x144 */ { 0, 0, 0, 0, 0, 1, 1, 1, 3, 1, 2, 3, 3, 0, 0, 0, 0 },
    /* 0x188 */ 1,
    /* 0x18C */ 0,
};
/* 803FA3E8 */ char* un_803FA3E8[3] = { un_804D5860, un_804D5868,
                                        un_804D5870 };
/* 803FA3F4 */ char un_803FA3F4[] = "GmLangTypeJP";
/* 803FA404 */ char un_803FA404[] = "GmLangTypeUS";
/* 803FA414 */ char un_803FA414[] = "No-Debug-Rom";
/* 803FA424 */ char un_803FA424[] = "Debug-Develop";
/* 803FA434 */ char un_803FA434[] = "Debug-Rom";
/* 803FA440 */ char* un_803FA440[5] = { un_804D5890, un_803FA414, un_803FA424,
                                        un_803FA434, un_804D5898 };
/* 803FA454 */ char un_803FA454[] = "Versus Mode    >";
/* 803FA468 */ char un_803FA468[] = "Result Test";
/* 803FA474 */ char un_803FA474[] = "Language : ";
/* 803FA480 */ char un_803FA480[] = "Publicity: ";
/* 803FA48C */ char un_803FA48C[] = "DbLevel : ";
/* 803FA498 */ char un_803FA498[] = "Ik Debug Flag :";
/* 803FA4A8 */ char un_803FA4A8[] = "New DefCalc :";
/* 803FA4B8 */ char un_803FA4B8[] = "Global Data Edit >";
/* 803FA4CC */ char un_803FA4CC[] = "Mode Team Test >";
/* 803FA4E0 */ struct un_80304138_objalloc_t_x8 un_803FA4E0[11] = {
    { 0, NULL, db_build_timestamp, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_803001DC, un_803FA454, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80301420, un_803FA468, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 2, un_80300218, un_803FA474, un_804D5888, &un_803FA258.x0, 0.0f, 2.0f,
      0.0f },
    { 2, un_80300248, un_803FA480, un_804D5880, &un_803FA258.x4[0], 0.0f, 2.0f,
      0.0f },
    { 2, NULL, un_803FA48C, un_803FA440, &DbLevel, 0.0f, 5.0f, 0.0f },
    { 3, NULL, un_803FA498, NULL, &db_804D4AF8, 0.0f, 1.0f, 1.0f },
    { 3, NULL, un_803FA4A8, NULL, &db_804D6B88, 0.0f, 1.0f, 1.0f },
    { 1, un_80300290, un_803FA4B8, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_803002FC, un_803FA4CC, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FA640 */ char un_803FA640[] = "< Global Data Edit >";
/* 803FA658 */ struct un_80304138_objalloc_t_x8 un_803FA658[8] = {
    { 0, NULL, un_803FA640, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 6, un_803003C4, un_804D58A0, NULL, &un_803FA258.xF0, 0.0f, 0.0f, 4.0f },
    { 7, un_80300410, un_804D58A8, NULL, &un_803FA258.xF4, 0.0f, 0.0f, 1.0f },
    { 6, un_80300378, un_804D58B0, NULL, &un_803FA258.xF0, 0.0f, 0.0f, 2.0f },
    { 6, un_80300410, un_804D58B8, NULL, &un_803FA258.xF4, 0.0f, 0.0f, 1.0f },
    { 6, un_80300338, un_804D58C0, NULL, &un_803FA258.xF0, 0.0f, 0.0f, 1.0f },
    { 5, un_80300410, un_804D58C8, NULL, &un_803FA258.xF4, 0.0f, 0.0f, 1.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FA758 */ char un_803FA758[] = "<VERSUS MODE>";
/* 803FA768 */ char un_803FA768[] = "MODE : DaiRanTou >";
/* 803FA77C */ char un_803FA77C[] = "MODE : Rule      >";
/* 803FA790 */ struct un_80304138_objalloc_t_x8 un_803FA790[4] = {
    { 0, NULL, un_803FA758, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80300480, un_803FA768, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_803004B4, un_803FA77C, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FA810 */ char un_803FA810[] = "Time Mode ";
/* 803FA81C */ char un_803FA81C[] = "Stock Mode";
/* 803FA828 */ char un_803FA828[] = "Coin Mode";
/* 803FA834 */ char un_803FA834[] = "Endless Mode";
/* 803FA844 */ char* un_803FA844[4] = { un_803FA810, un_803FA81C, un_803FA828,
                                        un_803FA834 };
/* 803FA854 */ char un_803FA854[] = "Veryhigh";
/* 803FA860 */ char* un_803FA860[6] = {
    un_804D58D0, un_804D58D8, un_804D58E0,
    un_804D58E4, un_804D58EC, un_803FA854
};
/* 803FA878 */ char un_803FA878[] = "< Rule >";
/* 803FA884 */ char un_803FA884[] = "Time(Min)  :";
/* 803FA894 */ char un_803FA894[] = "Time(Sec)  :";
/* 803FA8A4 */ char un_803FA8A4[] = "Stock(cnt) :";
/* 803FA8B4 */ char un_803FA8B4[] = "DamageRatio:";
/* 803FA8C4 */ char un_803FA8C4[] = "Vibration Select ->";
/* 803FA8D8 */ char un_803FA8D8[] = "Item Switch:";
/* 803FA8E8 */ struct un_80304138_objalloc_t_x8 un_803FA8E8[9] = {
    { 0, NULL, un_803FA878, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 2, NULL, un_804D58F4, un_803FA844, &un_803FA258.xC8, 0.0f, 4.0f, 0.0f },
    { 3, NULL, un_803FA884, NULL, &un_803FA258.xCC[0], 0.0f, 100.0f, 1.0f },
    { 3, NULL, un_803FA894, NULL, &un_803FA258.xCC[1], 0.0f, 59.0f, 1.0f },
    { 3, NULL, un_803FA8A4, NULL, &un_803FA258.xCC[2], -1.0f, 99.0f, 1.0f },
    { 8, NULL, un_803FA8B4, NULL, &un_803FA258.xEC, 0.0f, 3.0f, 0.1f },
    { 1, un_803004E8, un_803FA8C4, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 2, NULL, un_803FA8D8, un_803FA860, &un_803FA258.xCC[3], 0.0f, 6.0f,
      0.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FAA08 */ char un_803FAA08[] = "< Rumble >";
/* 803FAA14 */ char un_803FAA14[] = "Rumble_1 :";
/* 803FAA20 */ char un_803FAA20[] = "Rumble_2 :";
/* 803FAA2C */ char un_803FAA2C[] = "Rumble_3 :";
/* 803FAA38 */ char un_803FAA38[] = "Rumble_4 :";
/* 803FAA44 */ struct un_80304138_objalloc_t_x8 un_803FAA44[6] = {
    { 0, NULL, un_803FAA08, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 2, NULL, un_803FAA14, un_804D5880, &un_803FA258.xDC[0], 0.0f, 2.0f,
      0.0f },
    { 2, NULL, un_803FAA20, un_804D5880, &un_803FA258.xDC[1], 0.0f, 2.0f,
      0.0f },
    { 2, NULL, un_803FAA2C, un_804D5880, &un_803FA258.xDC[2], 0.0f, 2.0f,
      0.0f },
    { 2, NULL, un_803FAA38, un_804D5880, &un_803FA258.xDC[3], 0.0f, 2.0f,
      0.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FAB04 */ char un_803FAB04[] = "dummy   ";
/* 803FAB10 */ char un_803FAB10[] = "TEST    ";
/* 803FAB1C */ char un_803FAB1C[] = "Izumi   ";
/* 803FAB28 */ char un_803FAB28[] = "PStadium";
/* 803FAB34 */ char un_803FAB34[] = "Castle  ";
/* 803FAB40 */ char un_803FAB40[] = "Kongo   ";
/* 803FAB4C */ char un_803FAB4C[] = "Zebes   ";
/* 803FAB58 */ char un_803FAB58[] = "Corneria";
/* 803FAB64 */ char un_803FAB64[] = "Story   ";
/* 803FAB70 */ char un_803FAB70[] = "Onett   ";
/* 803FAB7C */ char un_803FAB7C[] = "MuteCity";
/* 803FAB88 */ char un_803FAB88[] = "RCruise ";
/* 803FAB94 */ char un_803FAB94[] = "Garden  ";
/* 803FABA0 */ char un_803FABA0[] = "GreatBay";
/* 803FABAC */ char un_803FABAC[] = "Shrine  ";
/* 803FABB8 */ char un_803FABB8[] = "Kraid   ";
/* 803FABC4 */ char un_803FABC4[] = "Yoster  ";
/* 803FABD0 */ char un_803FABD0[] = "Greens  ";
/* 803FABDC */ char un_803FABDC[] = "Fourside";
/* 803FABE8 */ char un_803FABE8[] = "Inishie1";
/* 803FABF4 */ char un_803FABF4[] = "Inishie2";
/* 803FAC00 */ char un_803FAC00[] = "Akaneia ";
/* 803FAC0C */ char un_803FAC0C[] = "Venom   ";
/* 803FAC18 */ char un_803FAC18[] = "Pura    ";
/* 803FAC24 */ char un_803FAC24[] = "BigBlue ";
/* 803FAC30 */ char un_803FAC30[] = "Icemt   ";
/* 803FAC3C */ char un_803FAC3C[] = "Icetop  ";
/* 803FAC48 */ char un_803FAC48[] = "Flatzone";
/* 803FAC54 */ char un_803FAC54[] = "old ppp ";
/* 803FAC60 */ char un_803FAC60[] = "old yosh";
/* 803FAC6C */ char un_803FAC6C[] = "old kong";
/* 803FAC78 */ char un_803FAC78[] = "battle  ";
/* 803FAC84 */ char un_803FAC84[] = "last    ";
/* 803FAC90 */ char un_803FAC90[] = "TMario  ";
/* 803FAC9C */ char un_803FAC9C[] = "TCaptain";
/* 803FACA8 */ char un_803FACA8[] = "TClink  ";
/* 803FACB4 */ char un_803FACB4[] = "TDonkey ";
/* 803FACC0 */ char un_803FACC0[] = "TDrmario";
/* 803FACCC */ char un_803FACCC[] = "TFalco  ";
/* 803FACD8 */ char un_803FACD8[] = "TFox    ";
/* 803FACE4 */ char un_803FACE4[] = "TIceclim";
/* 803FACF0 */ char un_803FACF0[] = "TKirby  ";
/* 803FACFC */ char un_803FACFC[] = "TKoopa  ";
/* 803FAD08 */ char un_803FAD08[] = "TLink   ";
/* 803FAD14 */ char un_803FAD14[] = "TLuigi  ";
/* 803FAD20 */ char un_803FAD20[] = "TMars   ";
/* 803FAD2C */ char un_803FAD2C[] = "TMewtwo ";
/* 803FAD38 */ char un_803FAD38[] = "TNess   ";
/* 803FAD44 */ char un_803FAD44[] = "TPeach  ";
/* 803FAD50 */ char un_803FAD50[] = "TPichu  ";
/* 803FAD5C */ char un_803FAD5C[] = "TPikachu";
/* 803FAD68 */ char un_803FAD68[] = "TPurin  ";
/* 803FAD74 */ char un_803FAD74[] = "TSamus  ";
/* 803FAD80 */ char un_803FAD80[] = "TSeak   ";
/* 803FAD8C */ char un_803FAD8C[] = "TYoshi  ";
/* 803FAD98 */ char un_803FAD98[] = "TZelda  ";
/* 803FADA4 */ char un_803FADA4[] = "TGamewat";
/* 803FADB0 */ char un_803FADB0[] = "TEmblem ";
/* 803FADBC */ char un_803FADBC[] = "TGanon  ";
/* 803FADC8 */ char un_803FADC8[] = "1-1kinoko ";
/* 803FADD4 */ char un_803FADD4[] = "1-2castle ";
/* 803FADE0 */ char un_803FADE0[] = "2-1kongo  ";
/* 803FADEC */ char un_803FADEC[] = "2-2garden ";
/* 803FADF8 */ char un_803FADF8[] = "3-1meikyu ";
/* 803FAE04 */ char un_803FAE04[] = "3-2shrine ";
/* 803FAE10 */ char un_803FAE10[] = "4-1zebes  ";
/* 803FAE1C */ char un_803FAE1C[] = "4-2dassyut";
/* 803FAE28 */ char un_803FAE28[] = "5-1greens ";
/* 803FAE34 */ char un_803FAE34[] = "5-2greens ";
/* 803FAE40 */ char un_803FAE40[] = "5-3greens ";
/* 803FAE4C */ char un_803FAE4C[] = "6-1corneri";
/* 803FAE58 */ char un_803FAE58[] = "6-2corneri";
/* 803FAE64 */ char un_803FAE64[] = "7pstadium ";
/* 803FAE70 */ char un_803FAE70[] = "8-1bbroute";
/* 803FAE7C */ char un_803FAE7C[] = "8-2mutecit";
/* 803FAE88 */ char un_803FAE88[] = "9-1onett  ";
/* 803FAE94 */ char un_803FAE94[] = "10-1icemt ";
/* 803FAEA0 */ char un_803FAEA0[] = "10-2      ";
/* 803FAEAC */ char un_803FAEAC[] = "11-1battle";
/* 803FAEB8 */ char un_803FAEB8[] = "11-2battle";
/* 803FAEC4 */ char un_803FAEC4[] = "12-1last  ";
/* 803FAED0 */ char un_803FAED0[] = "12-2last  ";
/* 803FAEDC */ char un_803FAEDC[] = "tukisusume";
/* 803FAEE8 */ char un_803FAEE8[] = "figureget ";
/* 803FAEF4 */ char un_803FAEF4[] = "homerun   ";
/* 803FAF00 */ char un_803FAF00[] = "heal      ";
/* 803FAF0C */ char* un_803FAF0C[86] = {
    un_803FAB04, un_803FAB10, un_803FAB1C, un_803FAB28, un_803FAB34,
    un_803FAB40, un_803FAB4C, un_803FAB58, un_803FAB64, un_803FAB70,
    un_803FAB7C, un_803FAB88, un_803FAB94, un_803FABA0, un_803FABAC,
    un_803FABB8, un_803FABC4, un_803FABD0, un_803FABDC, un_803FABE8,
    un_803FABF4, un_803FAC00, un_803FAC0C, un_803FAC18, un_803FAC24,
    un_803FAC30, un_803FAC3C, un_803FAC48, un_803FAC54, un_803FAC60,
    un_803FAC6C, un_803FAC78, un_803FAC84, un_803FAC90, un_803FAC9C,
    un_803FACA8, un_803FACB4, un_803FACC0, un_803FACCC, un_803FACD8,
    un_803FACE4, un_803FACF0, un_803FACFC, un_803FAD08, un_803FAD14,
    un_803FAD20, un_803FAD2C, un_803FAD38, un_803FAD44, un_803FAD50,
    un_803FAD5C, un_803FAD68, un_803FAD74, un_803FAD80, un_803FAD8C,
    un_803FAD98, un_803FADA4, un_803FADB0, un_803FADBC, un_803FADC8,
    un_803FADD4, un_803FADE0, un_803FADEC, un_803FADF8, un_803FAE04,
    un_803FAE10, un_803FAE1C, un_803FAE28, un_803FAE34, un_803FAE40,
    un_803FAE4C, un_803FAE58, un_803FAE64, un_803FAE70, un_803FAE7C,
    un_803FAE88, un_803FAE94, un_803FAEA0, un_803FAEAC, un_803FAEB8,
    un_803FAEC4, un_803FAED0, un_803FAEDC, un_803FAEE8, un_803FAEF4,
    un_803FAF00
};
/* 803FB064 */ char un_803FB064[] = "Battle Royal";
/* 803FB074 */ char un_803FB074[] = "Team Battle";
/* 803FB080 */ char un_803FB080[] = "< DaiRanTou >";
/* 803FB090 */ char un_803FB090[] = "Char  Select ->";
/* 803FB0A0 */ char un_803FB0A0[] = "Scale Select ->";
/* 803FB0B0 */ char un_803FB0B0[] = "Kind  Select ->";
/* 803FB0C0 */ char un_803FB0C0[] = "Color Select ->";
/* 803FB0D0 */ char un_803FB0D0[] = "  Sub Color  ->";
/* 803FB0E0 */ char un_803FB0E0[] = "Damage Set   ->";
/* 803FB0F0 */ char un_803FB0F0[] = "  OffenceRatio>";
/* 803FB100 */ char un_803FB100[] = "  DefenceRatio>";
/* 803FB110 */ char un_803FB110[] = "CpuType  Set ->";
/* 803FB120 */ char un_803FB120[] = "CpuLevel Set ->";
/* 803FB130 */ char un_803FB130[] = "Team  Select ->";
/* 803FB140 */ char un_803FB140[] = "Stage   :";
/* 803FB14C */ char un_803FB14C[] = "MeleeKind :";
/* 803FB158 */ char un_803FB158[] = "-----------EXIT";
/* 803FB168 */ struct un_80304138_objalloc_t_x8 un_803FB168[16] = {
    { 0, NULL, un_803FB080, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_8030051C, un_803FB090, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80300550, un_803FB0A0, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80300584, un_803FB0B0, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_803005B8, un_803FB0C0, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_803005EC, un_803FB0D0, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80300620, un_803FB0E0, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80300654, un_803FB0F0, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80300688, un_803FB100, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_803006BC, un_803FB110, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_803006F0, un_803FB120, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80300724, un_803FB130, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 2, NULL, un_803FB140, un_803FAF0C, &un_803FA258.x4[1], 0.0f, 86.0f,
      0.0f },
    { 2, NULL, un_803FB14C, un_804D58FC, &un_803FA258.x4[2], 0.0f, 2.0f,
      0.0f },
    { 1, un_802FFEA4, un_803FB158, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FB368 */ char un_803FB368[] = "CKind_Captain";
/* 803FB378 */ char un_803FB378[] = "CKind_Donkey";
/* 803FB388 */ char un_803FB388[] = "CKind_Fox";
/* 803FB394 */ char un_803FB394[] = "CKind_GameWatch";
/* 803FB3A4 */ char un_803FB3A4[] = "CKind_Kirby";
/* 803FB3B0 */ char un_803FB3B0[] = "CKind_Koopa";
/* 803FB3BC */ char un_803FB3BC[] = "CKind_Link";
/* 803FB3C8 */ char un_803FB3C8[] = "CKind_Luigi";
/* 803FB3D4 */ char un_803FB3D4[] = "CKind_Mario";
/* 803FB3E0 */ char un_803FB3E0[] = "CKind_Mars";
/* 803FB3EC */ char un_803FB3EC[] = "CKind_Mewtwo";
/* 803FB3FC */ char un_803FB3FC[] = "CKind_Ness";
/* 803FB408 */ char un_803FB408[] = "CKind_Peach";
/* 803FB414 */ char un_803FB414[] = "CKind_Pikachu";
/* 803FB424 */ char un_803FB424[] = "CKind_PopoNana";
/* 803FB434 */ char un_803FB434[] = "CKind_Purin";
/* 803FB440 */ char un_803FB440[] = "CKind_Samus";
/* 803FB44C */ char un_803FB44C[] = "CKind_Yoshi";
/* 803FB458 */ char un_803FB458[] = "CKind_Ze->Se";
/* 803FB468 */ char un_803FB468[] = "CKind_Se->Ze";
/* 803FB478 */ char un_803FB478[] = "CKind_Falco";
/* 803FB484 */ char un_803FB484[] = "CKind_Clink";
/* 803FB490 */ char un_803FB490[] = "CKind_Drmario";
/* 803FB4A0 */ char un_803FB4A0[] = "CKind_Emblem";
/* 803FB4B0 */ char un_803FB4B0[] = "CKind_Pichu";
/* 803FB4BC */ char un_803FB4BC[] = "CKind_Ganon";
/* 803FB4C8 */ char un_803FB4C8[] = "CKind_MasterH";
/* 803FB4D8 */ char un_803FB4D8[] = "CKind_Boy";
/* 803FB4E4 */ char un_803FB4E4[] = "CKind_Girl";
/* 803FB4F0 */ char un_803FB4F0[] = "CKind_GKoops";
/* 803FB500 */ char un_803FB500[] = "Ckind_CrezyH";
/* 803FB510 */ char un_803FB510[] = "ChKind_Sandbag";
/* 803FB520 */ char un_803FB520[] = "ChKind_Popo";
/* 803FB52C */ char un_803FB52C[] = "ChKind_None";
/* 803FB538 */ char* un_803FB538[34] = {
    un_803FB368, un_803FB378, un_803FB388, un_803FB394, un_803FB3A4,
    un_803FB3B0, un_803FB3BC, un_803FB3C8, un_803FB3D4, un_803FB3E0,
    un_803FB3EC, un_803FB3FC, un_803FB408, un_803FB414, un_803FB424,
    un_803FB434, un_803FB440, un_803FB44C, un_803FB458, un_803FB468,
    un_803FB478, un_803FB484, un_803FB490, un_803FB4A0, un_803FB4B0,
    un_803FB4BC, un_803FB4C8, un_803FB4D8, un_803FB4E4, un_803FB4F0,
    un_803FB500, un_803FB510, un_803FB520, un_803FB52C
};
/* 803FB5C0 */ char un_803FB5C0[] = "< CharSelect >";
/* 803FB5D0 */ char un_803FB5D0[] = "Chara_1 :";
/* 803FB5DC */ char un_803FB5DC[] = "Chara_2 :";
/* 803FB5E8 */ char un_803FB5E8[] = "Chara_3 :";
/* 803FB5F4 */ char un_803FB5F4[] = "Chara_4 :";
/* 803FB600 */ char un_803FB600[] = "All Char :";
/* 803FB60C */ struct un_80304138_objalloc_t_x8 un_803FB60C[7] = {
    { 0, NULL, un_803FB5C0, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 2, NULL, un_803FB5D0, un_803FB538, &un_803FA258.x4[3], 0.0f, 34.0f,
      0.0f },
    { 2, NULL, un_803FB5DC, un_803FB538, &un_803FA258.x14[0], 0.0f, 34.0f,
      0.0f },
    { 2, NULL, un_803FB5E8, un_803FB538, &un_803FA258.x14[1], 0.0f, 34.0f,
      0.0f },
    { 2, NULL, un_803FB5F4, un_803FB538, &un_803FA258.x14[2], 0.0f, 34.0f,
      0.0f },
    { 2, un_80300758, un_803FB600, un_803FB538, &un_803FA258.x14[3], 0.0f,
      34.0f, 0.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FB6EC */ char un_803FB6EC[] = "< Scale >";
/* 803FB6F8 */ char un_803FB6F8[] = "Scale__1 :";
/* 803FB704 */ char un_803FB704[] = "Scale__2 :";
/* 803FB710 */ char un_803FB710[] = "Scale__3 :";
/* 803FB71C */ char un_803FB71C[] = "Scale__4 :";
/* 803FB728 */ struct un_80304138_objalloc_t_x8 un_803FB728[6] = {
    { 0, NULL, un_803FB6EC, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 8, NULL, un_803FB6F8, NULL, &un_803FA258.x98[0], 0.1f, 5.0f, 0.1f },
    { 8, NULL, un_803FB704, NULL, &un_803FA258.x98[1], 0.1f, 5.0f, 0.1f },
    { 8, NULL, un_803FB710, NULL, &un_803FA258.x98[2], 0.1f, 5.0f, 0.1f },
    { 8, NULL, un_803FB71C, NULL, &un_803FA258.x98[3], 0.1f, 5.0f, 0.1f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FB7E8 */ char un_803FB7E8[] = "Gm_Human";
/* 803FB7F4 */ char un_803FB7F4[] = "Gm_Cpu  ";
/* 803FB800 */ char un_803FB800[] = "Gm_Demo ";
/* 803FB80C */ char un_803FB80C[] = "Gm_None ";
/* 803FB818 */ char* un_803FB818[4] = { un_803FB7E8, un_803FB7F4, un_803FB800,
                                        un_803FB80C };
/* 803FB828 */ char un_803FB828[] = "< P Kind >";
/* 803FB834 */ char un_803FB834[] = "PKind__1 :";
/* 803FB840 */ char un_803FB840[] = "PKind__2 :";
/* 803FB84C */ char un_803FB84C[] = "PKind__3 :";
/* 803FB858 */ char un_803FB858[] = "PKind__4 :";
/* 803FB864 */ char un_803FB864[] = "All PKind :";
/* 803FB870 */ struct un_80304138_objalloc_t_x8 un_803FB870[7] = {
    { 0, NULL, un_803FB828, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 2, NULL, un_803FB834, un_803FB818, &un_803FA258.x24[0], 0.0f, 4.0f,
      0.0f },
    { 2, NULL, un_803FB840, un_803FB818, &un_803FA258.x24[1], 0.0f, 4.0f,
      0.0f },
    { 2, NULL, un_803FB84C, un_803FB818, &un_803FA258.x24[2], 0.0f, 4.0f,
      0.0f },
    { 2, NULL, un_803FB858, un_803FB818, &un_803FA258.x24[3], 0.0f, 4.0f,
      0.0f },
    { 2, un_80300790, un_803FB864, un_803FB818, &un_803FA258.x34, 0.0f, 4.0f,
      0.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FB950 */ char un_803FB950[] = "< Color >";
/* 803FB95C */ char un_803FB95C[] = "Color_1 :";
/* 803FB968 */ char un_803FB968[] = "Color_2 :";
/* 803FB974 */ char un_803FB974[] = "Color_3 :";
/* 803FB980 */ char un_803FB980[] = "Color_4 :";
/* 803FB98C */ struct un_80304138_objalloc_t_x8 un_803FB98C[6] = {
    { 0, NULL, un_803FB950, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 3, NULL, un_803FB95C, NULL, &un_803FA258.x38[0], 0.0f, 9.0f, 1.0f },
    { 3, NULL, un_803FB968, NULL, &un_803FA258.x38[1], 0.0f, 9.0f, 1.0f },
    { 3, NULL, un_803FB974, NULL, &un_803FA258.x38[2], 0.0f, 9.0f, 1.0f },
    { 3, NULL, un_803FB980, NULL, &un_803FA258.x38[3], 0.0f, 9.0f, 1.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FBA4C */ char un_803FBA4C[] = "< Sub Color >";
/* 803FBA5C */ char un_803FBA5C[] = "SubColor_1 :";
/* 803FBA6C */ char un_803FBA6C[] = "SubColor_2 :";
/* 803FBA7C */ char un_803FBA7C[] = "SubColor_3 :";
/* 803FBA8C */ char un_803FBA8C[] = "SubColor_4 :";
/* 803FBA9C */ struct un_80304138_objalloc_t_x8 un_803FBA9C[6] = {
    { 0, NULL, un_803FBA4C, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 3, NULL, un_803FBA5C, NULL, &un_803FA258.x48[0], 0.0f, 9.0f, 1.0f },
    { 3, NULL, un_803FBA6C, NULL, &un_803FA258.x48[1], 0.0f, 9.0f, 1.0f },
    { 3, NULL, un_803FBA7C, NULL, &un_803FA258.x48[2], 0.0f, 9.0f, 1.0f },
    { 3, NULL, un_803FBA8C, NULL, &un_803FA258.x48[3], 0.0f, 9.0f, 1.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FBB5C */ char un_803FBB5C[] = "< Damage >";
/* 803FBB68 */ char un_803FBB68[] = "Damage_1 :";
/* 803FBB74 */ char un_803FBB74[] = "Damage_2 :";
/* 803FBB80 */ char un_803FBB80[] = "Damage_3 :";
/* 803FBB8C */ char un_803FBB8C[] = "Damage_4 :";
/* 803FBB98 */ struct un_80304138_objalloc_t_x8 un_803FBB98[6] = {
    { 0, NULL, un_803FBB5C, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 3, NULL, un_803FBB68, NULL, &un_803FA258.x68[0], 0.0f, 999.0f, 1.0f },
    { 3, NULL, un_803FBB74, NULL, &un_803FA258.x68[1], 0.0f, 999.0f, 1.0f },
    { 3, NULL, un_803FBB80, NULL, &un_803FA258.x68[2], 0.0f, 999.0f, 1.0f },
    { 3, NULL, un_803FBB8C, NULL, &un_803FA258.x68[3], 0.0f, 999.0f, 1.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FBC58 */ char un_803FBC58[] = "< Offence Ratio >";
/* 803FBC6C */ char un_803FBC6C[] = "OffRatio_1 :";
/* 803FBC7C */ char un_803FBC7C[] = "OffRatio_2 :";
/* 803FBC8C */ char un_803FBC8C[] = "OffRatio_3 :";
/* 803FBC9C */ char un_803FBC9C[] = "OffRatio_4 :";
/* 803FBCAC */ struct un_80304138_objalloc_t_x8 un_803FBCAC[6] = {
    { 0, NULL, un_803FBC58, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 8, NULL, un_803FBC6C, NULL, &un_803FA258.x78[0], 0.0f, 3.0f, 0.1f },
    { 8, NULL, un_803FBC7C, NULL, &un_803FA258.x78[1], 0.0f, 3.0f, 0.1f },
    { 8, NULL, un_803FBC8C, NULL, &un_803FA258.x78[2], 0.0f, 3.0f, 0.1f },
    { 8, NULL, un_803FBC9C, NULL, &un_803FA258.x78[3], 0.0f, 3.0f, 0.1f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FBD6C */ char un_803FBD6C[] = "< Defence Ratio >";
/* 803FBD80 */ char un_803FBD80[] = "DefRatio_1 :";
/* 803FBD90 */ char un_803FBD90[] = "DefRatio_2 :";
/* 803FBDA0 */ char un_803FBDA0[] = "DefRatio_3 :";
/* 803FBDB0 */ char un_803FBDB0[] = "DefRatio_4 :";
/* 803FBDC0 */ struct un_80304138_objalloc_t_x8 un_803FBDC0[6] = {
    { 0, NULL, un_803FBD6C, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 8, NULL, un_803FBD80, NULL, &un_803FA258.x88[0], 0.0f, 3.0f, 0.1f },
    { 8, NULL, un_803FBD90, NULL, &un_803FA258.x88[1], 0.0f, 3.0f, 0.1f },
    { 8, NULL, un_803FBDA0, NULL, &un_803FA258.x88[2], 0.0f, 3.0f, 0.1f },
    { 8, NULL, un_803FBDB0, NULL, &un_803FA258.x88[3], 0.0f, 3.0f, 0.1f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FBE80 */ char un_803FBE80[] = "CpTp_Stay  ";
/* 803FBE8C */ char un_803FBE8C[] = "CpTp_Walk  ";
/* 803FBE98 */ char un_803FBE98[] = "CpTp_Escape";
/* 803FBEA4 */ char un_803FBEA4[] = "CpTp_Jump  ";
/* 803FBEB0 */ char un_803FBEB0[] = "CpTp_Normal";
/* 803FBEBC */ char un_803FBEBC[] = "CpTp_Manual";
/* 803FBEC8 */ char un_803FBEC8[] = "CpTp_Nana  ";
/* 803FBED4 */ char un_803FBED4[] = "CpTp_Defensive";
/* 803FBEE4 */ char un_803FBEE4[] = "CpTp_Struggle";
/* 803FBEF4 */ char un_803FBEF4[] = "CpTp_Freak ";
/* 803FBF00 */ char un_803FBF00[] = "CpTp_Cooperate";
/* 803FBF10 */ char un_803FBF10[] = "CpTp_SpLwLink";
/* 803FBF20 */ char un_803FBF20[] = "CpTp_SpLwSamus";
/* 803FBF30 */ char un_803FBF30[] = "CpTp_OnlyItem";
/* 803FBF40 */ char un_803FBF40[] = "CpTp_EvZelda";
/* 803FBF50 */ char un_803FBF50[] = "CpTp_NoAct";
/* 803FBF5C */ char un_803FBF5C[] = "CpTp_Air";
/* 803FBF68 */ char un_803FBF68[] = "CpTp_Item";
/* 803FBF74 */ char* un_803FBF74[18] = {
    un_803FBE80, un_803FBE8C, un_803FBE98, un_803FBEA4, un_803FBEB0,
    un_803FBEBC, un_803FBEC8, un_803FBED4, un_803FBEE4, un_803FBEF4,
    un_803FBF00, un_803FBF10, un_803FBF20, un_803FBF30, un_803FBF40,
    un_803FBF50, un_803FBF5C, un_803FBF68
};
/* 803FBFBC */ char un_803FBFBC[] = "< Cpu Type >";
/* 803FBFCC */ char un_803FBFCC[] = "Type__C1 :";
/* 803FBFD8 */ char un_803FBFD8[] = "Type__C2 :";
/* 803FBFE4 */ char un_803FBFE4[] = "Type__C3 :";
/* 803FBFF0 */ char un_803FBFF0[] = "Type__C4 :";
/* 803FBFFC */ struct un_80304138_objalloc_t_x8 un_803FBFFC[6] = {
    { 0, NULL, un_803FBFBC, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 2, NULL, un_803FBFCC, un_803FBF74, &un_803FA258.xA8[0], 0.0f, 18.0f,
      0.0f },
    { 2, NULL, un_803FBFD8, un_803FBF74, &un_803FA258.xA8[1], 0.0f, 18.0f,
      0.0f },
    { 2, NULL, un_803FBFE4, un_803FBF74, &un_803FA258.xA8[2], 0.0f, 18.0f,
      0.0f },
    { 2, NULL, un_803FBFF0, un_803FBF74, &un_803FA258.xA8[3], 0.0f, 18.0f,
      0.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FC0BC */ char un_803FC0BC[] = "< Cpu Level >";
/* 803FC0CC */ char un_803FC0CC[] = "Level_C1 :";
/* 803FC0D8 */ char un_803FC0D8[] = "Level_C2 :";
/* 803FC0E4 */ char un_803FC0E4[] = "Level_C3 :";
/* 803FC0F0 */ char un_803FC0F0[] = "Level_C4 :";
/* 803FC0FC */ struct un_80304138_objalloc_t_x8 un_803FC0FC[6] = {
    { 0, NULL, un_803FC0BC, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 3, NULL, un_803FC0CC, NULL, &un_803FA258.xB8[0], 0.0f, 9.0f, 1.0f },
    { 3, NULL, un_803FC0D8, NULL, &un_803FA258.xB8[1], 0.0f, 9.0f, 1.0f },
    { 3, NULL, un_803FC0E4, NULL, &un_803FA258.xB8[2], 0.0f, 9.0f, 1.0f },
    { 3, NULL, un_803FC0F0, NULL, &un_803FA258.xB8[3], 0.0f, 9.0f, 1.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FC1BC */ char un_803FC1BC[] = "Red-Team";
/* 803FC1C8 */ char un_803FC1C8[] = "Green-Team";
/* 803FC1D4 */ char un_803FC1D4[] = "Blue-Team";
/* 803FC1E0 */ char* un_803FC1E0[3] = { un_803FC1BC, un_803FC1C8,
                                        un_803FC1D4 };
/* 803FC1EC */ char un_803FC1EC[] = "< Team Select >";
/* 803FC1FC */ char un_803FC1FC[] = "Team_1 :";
/* 803FC208 */ char un_803FC208[] = "Team_2 :";
/* 803FC214 */ char un_803FC214[] = "Team_3 :";
/* 803FC220 */ char un_803FC220[] = "Team_4 :";
/* 803FC22C */ struct un_80304138_objalloc_t_x8 un_803FC22C[6] = {
    { 0, NULL, un_803FC1EC, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 2, NULL, un_803FC1FC, un_803FC1E0, &un_803FA258.x58[0], 0.0f, 3.0f,
      0.0f },
    { 2, NULL, un_803FC208, un_803FC1E0, &un_803FA258.x58[1], 0.0f, 3.0f,
      0.0f },
    { 2, NULL, un_803FC214, un_803FC1E0, &un_803FA258.x58[2], 0.0f, 3.0f,
      0.0f },
    { 2, NULL, un_803FC220, un_803FC1E0, &un_803FA258.x58[3], 0.0f, 3.0f,
      0.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FC2EC */ u32 un_803FC2EC[77] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001,
    0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000003,
    0x00000002, 0x00000002, 0x00000005, 0x00000005, 0x00000004, 0x00000006,
    0x00000006, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008,
    0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008,
    0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008,
    0x00000005, 0x00000005, 0x00000005, 0x00000005, 0x00000005, 0x00000005,
    0x00000005, 0x00000005, 0x00000005, 0x00000005, 0x00000005, 0x00000005,
    0x00000005, 0x00000006, 0x00000006, 0x00000005, 0x00000007, 0x00000007,
    0x00000007, 0x00000007, 0x00000007, 0x00000007, 0x00000005, 0x00000005,
    0x00000005, 0x00000005, 0x00000005, 0x00000005, 0x00000005,
};
/* 803FC420 */ char un_803FC420[] = "<TEST MODE>";
/* 803FC42C */ char un_803FC42C[] = "MODE : Hanyu    >";
/* 803FC440 */ char un_803FC440[] = "MODE : Otoguro  >";
/* 803FC454 */ char un_803FC454[] = "MODE : Taniguti >";
/* 803FC468 */ char un_803FC468[] = "MODE : Nagasima >";
/* 803FC47C */ char un_803FC47C[] = "MODE : Kim      >";
/* 803FC490 */ char un_803FC490[] = "MODE : Sakoda   >";
/* 803FC4A4 */ char un_803FC4A4[] = "MODE : Sugano   >";
/* 803FC4B8 */ char un_803FC4B8[] = "MODE : Yoshiki  >";
/* 803FC4CC */ struct un_80304138_objalloc_t_x8 un_803FC4CC[10] = {
    { 0, NULL, un_803FC420, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_803007C8, un_803FC42C, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_803007FC, un_803FC440, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80300830, un_803FC454, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80300864, un_803FC468, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80300898, un_803FC47C, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_803008CC, un_803FC490, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80300900, un_803FC4A4, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80300934, un_803FC4B8, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FC60C */ char un_803FC60C[] = "< Hanyu Test >";
/* 803FC61C */ char un_803FC61C[] = "Select Char  >";
/* 803FC62C */ char un_803FC62C[] = "Select Stage >";
/* 803FC63C */ struct un_80304138_objalloc_t_x8 un_803FC63C[4] = {
    { 0, NULL, un_803FC60C, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80300968, un_803FC61C, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_803009A4, un_803FC62C, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FC6BC */ char un_803FC6BC[] = "< Melee Count Set >";
/* 803FC6D0 */ char un_803FC6D0[] = "Time     >";
/* 803FC6DC */ char un_803FC6DC[] = "Stock    >";
/* 803FC6E8 */ char un_803FC6E8[] = "Coin     >";
/* 803FC6F4 */ char un_803FC6F4[] = "Decision >";
/* 803FC700 */ char un_803FC700[] = "Default  >";
/* 803FC70C */ struct un_80304138_objalloc_t_x8 un_803FC70C[7] = {
    { 0, NULL, un_803FC6BC, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 3, NULL, un_803FC6D0, NULL, &un_804D6DE0, 0.0f, 1e+06f, 1.0f },
    { 3, NULL, un_803FC6DC, NULL, &un_804D6DE4, 0.0f, 1e+06f, 1.0f },
    { 3, NULL, un_803FC6E8, NULL, &un_804D6DE8, 0.0f, 1e+06f, 1.0f },
    { 3, NULL, un_803FC6F4, NULL, &un_804D6DEC, 0.0f, 1e+06f, 1.0f },
    { 3, NULL, un_803FC700, NULL, &un_804D6DF0, 0.0f, 1e+06f, 1000.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FC7EC */ char un_803FC7EC[] = "< Player Count Set >";
/* 803FC804 */ char un_803FC804[] = "Chara   :";
/* 803FC810 */ char un_803FC810[] = "Count   :";
/* 803FC81C */ char un_803FC81C[] = "Default :";
/* 803FC828 */ struct un_80304138_objalloc_t_x8 un_803FC828[5] = {
    { 0, NULL, un_803FC7EC, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 2, un_803009E0, un_803FC804, un_803FB538, &un_804D6DC8, 0.0f, 34.0f,
      0.0f },
    { 3, un_80300A88, un_803FC810, NULL, &un_804D6DCC, 0.0f, 1e+06f, 1.0f },
    { 3, NULL, un_803FC81C, NULL, &un_804D6DD4, 0.0f, 1e+06f, 10.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FC8C8 */ struct un_80304138_objalloc_t_x8 un_803FC8C8[5] = {
    { 0, NULL, un_803FC7EC, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 2, un_803009E0, un_803FC804, un_803FB538, &un_804D6DC8, 0.0f, 34.0f,
      0.0f },
    { 8, un_80300A88, un_803FC810, NULL, &un_804D6DD0, 0.0f, 1e+06f, 0.1f },
    { 3, NULL, un_803FC81C, NULL, &un_804D6DD4, 0.0f, 1e+06f, 10.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FC968 */ char un_803FC968[] = "< Otoguro Test >";
/* 803FC97C */ char un_803FC97C[] = "Set Gold Coin :";
/* 803FC98C */ char un_803FC98C[] = "Figure Max";
/* 803FC998 */ char un_803FC998[] = "Samus Mask Get";
/* 803FC9A8 */ char un_803FC9A8[] = "Mario & Yoshi Get";
/* 803FC9BC */ char un_803FC9BC[] = "Set Melee Count >";
/* 803FC9D0 */ char un_803FC9D0[] = "Set HomeRun Record >";
/* 803FC9E8 */ char un_803FC9E8[] = "Set Target Clear >";
/* 803FC9FC */ char un_803FC9FC[] = "Set Beat Total :";
/* 803FCA10 */ char un_803FCA10[] = "Go to  Meikyu";
/* 803FCA20 */ char un_803FCA20[] = "Go to  Kinoko";
/* 803FCA30 */ char un_803FCA30[] = "Melee  Start";
/* 803FCA40 */ struct un_80304138_objalloc_t_x8 un_803FCA40[13] = {
    { 0, NULL, un_803FC968, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 3, un_80300C80, un_803FC97C, NULL, &un_804D6DDC, 0.0f, 999.0f, 1.0f },
    { 1, un_80300BBC, un_803FC98C, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80300BF8, un_803FC998, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80300C3C, un_803FC9A8, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80300D78, un_803FC9BC, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80300E74, un_803FC9D0, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80300F3C, un_803FC9E8, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 3, un_80300F98, un_803FC9FC, NULL, &un_804D6DF4, 0.0f, 1e+08f, 1.0f },
    { 1, un_80300AF4, un_803FCA10, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80300B58, un_803FCA20, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80300AB8, un_803FCA30, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FCBE0 */ char un_803FCBE0[] = "< Taniguti Test >";
/* 803FCBF4 */ char un_803FCBF4[] = "Melee    Start >";
/* 803FCC08 */ char un_803FCC08[] = "Reg:Normal  >";
/* 803FCC18 */ char un_803FCC18[] = "Reg:Easy    >";
/* 803FCC28 */ char un_803FCC28[] = "Reg:Allstar >";
/* 803FCC38 */ struct un_80304138_objalloc_t_x8 un_803FCC38[6] = {
    { 0, NULL, un_803FCBE0, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80300FEC, un_803FCBF4, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 3, un_80301028, un_803FCC08, NULL, &un_804D5908, 1.0f, 12.0f, 1.0f },
    { 3, un_80301074, un_803FCC18, NULL, &un_804D590C, 1.0f, 11.0f, 1.0f },
    { 3, un_803010C0, un_803FCC28, NULL, &un_804D5910, 1.0f, 13.0f, 1.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FCCF8 */ char un_803FCCF8[] = "ADVENTURE";
/* 803FCD04 */ char un_803FCD04[] = "ALL-STAR";
/* 803FCD10 */ char* un_803FCD10[3] = { un_804D5914, un_803FCCF8,
                                        un_803FCD04 };
/* 803FCD1C */ char un_803FCD1C[] = "< Regular Ending Test >";
/* 803FCD34 */ struct un_80304138_objalloc_t_x8 un_803FCD34[5] = {
    { 0, NULL, un_803FCD1C, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 2, NULL, un_804D591C, un_803FB538, &un_804D6DF8, 0.0f, 34.0f, 0.0f },
    { 3, NULL, un_804D5924, NULL, &un_804D6DFC, 0.0f, 9.0f, 1.0f },
    { 2, NULL, un_804D592C, un_803FCD10, &un_804D6E00, 0.0f, 3.0f, 0.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FCDD4 */ char un_803FCDD4[] = "< Nagasima Test >";
/* 803FCDE8 */ char un_803FCDE8[] = "Visual-Scene Start";
/* 803FCDFC */ char un_803FCDFC[] = "Opening Start";
/* 803FCE0C */ char un_803FCE0C[] = "Omake15 Start";
/* 803FCE1C */ char un_803FCE1C[] = "RegularEnding Test >";
/* 803FCE34 */ char un_803FCE34[] = "RegularEnding Real >";
/* 803FCE4C */ struct un_80304138_objalloc_t_x8 un_803FCE4C[7] = {
    { 0, NULL, un_803FCDD4, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_803013B0, un_803FCDE8, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80301328, un_803FCDFC, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_8030136C, un_803FCE0C, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_803012D4, un_803FCE1C, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80301280, un_803FCE34, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FCF2C */ char un_803FCF2C[] = "NoChara 0";
/* 803FCF38 */ char un_803FCF38[] = "GameWatch";
/* 803FCF44 */ char un_803FCF44[] = "Dr Mario";
/* 803FCF50 */ char un_803FCF50[] = "NoChara 12";
/* 803FCF5C */ char* un_803FCF5C[13] = { un_803FCF2C, un_803FCF38, un_804D5934,
                                         un_804D593C, un_804D5944, un_804D594C,
                                         un_804D5954, un_804D595C, un_803FCF44,
                                         un_804D5964, un_804D5968, un_804D5970,
                                         un_803FCF50 };
/* 803FCF90 */ char un_803FCF90[] = "< Kim Test >";
/* 803FCFA0 */ char un_803FCFA0[] = "Result Test";
/* 803FCFAC */ char un_803FCFAC[] = "Card Check - scene>";
/* 803FCFC0 */ char un_803FCFC0[] = "Card Check - mode >";
/* 803FCFD4 */ char un_803FCFD4[] = "EasyEnd :";
/* 803FCFE0 */ char un_803FCFE0[] = "GoHoubi Id:";
/* 803FCFEC */ char un_803FCFEC[] = "GoHoubi Figure :";
/* 803FD000 */ char un_803FD000[] = "Intro Easy ";
/* 803FD00C */ char un_803FD00C[] = "AllStar Enemy :";
/* 803FD01C */ char un_803FD01C[] = "Test Movie Opening >";
/* 803FD034 */ char un_803FD034[] = "KUMITE SUB :";
/* 803FD044 */ char un_803FD044[] = "Progressive Test ";
/* 803FD058 */ char un_803FD058[] = "Approach :";
/* 803FD064 */ struct un_80304138_objalloc_t_x8 un_803FD064[14] = {
    { 0, NULL, un_803FCF90, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80301420, un_803FCFA0, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80301490, un_803FCFAC, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80301454, un_803FCFC0, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 2, un_80301544, un_803FCFD4, un_803FB538, &un_803FA258.x134, 0.0f, 34.0f,
      0.0f },
    { 3, un_80301508, un_803FCFE0, NULL, &un_803FA258.x12C, 0.0f, 65.0f,
      1.0f },
    { 3, un_80301508, un_803FCFEC, NULL, &un_803FA258.x130, 0.0f, 299.0f,
      1.0f },
    { 1, un_803013EC, un_803FD000, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 2, un_803014CC, un_803FD00C, un_803FB538, &un_803FA258.x138, 0.0f, 34.0f,
      0.0f },
    { 1, un_80301580, un_803FD01C, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 2, NULL, un_803FD034, un_803FB538, &un_803FA258.x13C, 0.0f, 34.0f,
      0.0f },
    { 1, un_803015BC, un_803FD044, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 2, un_803015F8, un_803FD058, un_803FCF5C, &un_803FA258.x140, 0.0f, 13.0f,
      0.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FD224 */ char un_803FD224[] = "<Format>\n";
/* 803FD230 */ char un_803FD230[] = "result %d\n";
/* 803FD23C */ char un_803FD23C[] = "<Accessable>\n";
/* 803FD24C */ char un_803FD24C[] = "<Create>\n";
/* 803FD258 */ char un_803FD258[] = "<Delete>\n";
/* 803FD264 */ char un_803FD264[] = "<SnapMount0>\n";
/* 803FD274 */ HSD_ImageDesc un_803FD274 = {
    NULL, 640, 480, GX_TF_RGB565, 0, 0.0f, 0.0f,
};
/* 803FD28C */ char un_803FD28C[] = "<SnapLoad0>\n";
/* 803FD29C */ char un_803FD29C[] = "<SnapDelete0>\n";
/* 803FD2AC */ char un_803FD2AC[] = "<SnapSwap0>\n";
/* 803FD2BC */ char un_803FD2BC[] = "< Yoshiki Test >";
/* 803FD2D0 */ char un_803FD2D0[] = "Accessable";
/* 803FD2DC */ char un_803FD2DC[] = "SnapMount0";
/* 803FD2E8 */ char un_803FD2E8[] = "SnapLoad0 ";
/* 803FD2F4 */ char un_803FD2F4[] = "SnapDelete0 ";
/* 803FD304 */ char un_803FD304[] = "SnapSwap0 ";
/* 803FD310 */ struct un_80304138_objalloc_t_x8 un_803FD310[13] = {
    { 0, NULL, un_803FD2BC, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80301634, un_804D5998, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_803016D8, un_804D59A0, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80301734, un_803FD2D0, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_8030178C, un_804D59A8, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80301800, un_804D59B0, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80301840, un_804D59B8, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_803018BC, un_804D59C0, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_8030191C, un_803FD2DC, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 3, un_80301964, un_803FD2E8, NULL, &un_804D6E0C, 0.0f, 127.0f, 1.0f },
    { 3, un_80301A64, un_803FD2F4, NULL, &un_804D6E10, 0.0f, 127.0f, 1.0f },
    { 3, un_80301AD4, un_803FD304, NULL, &un_804D6E14, 0.0f, 127.0f, 1.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FD4B0 */ char* un_803FD4B0[5] = { un_804D59C8, un_804D59D0, un_804D59D8,
                                        un_804D59E0, un_804D59E8 };
/* 803FD4C4 */ char un_803FD4C4[] = "Tukisusume";
/* 803FD4D0 */ char un_803FD4D0[] = "FigureGet";
/* 803FD4DC */ char* un_803FD4DC[4] = { un_804D59C8, un_804D59F0, un_803FD4C4,
                                        un_803FD4D0 };
/* 803FD4EC */ char un_803FD4EC[] = "<INTRO EASY TEST>";
/* 803FD500 */ char un_803FD500[] = "StageNum : ";
/* 803FD50C */ char un_803FD50C[] = "Stage Flag :";
/* 803FD51C */ char un_803FD51C[] = "Stage Type :";
/* 803FD52C */ char un_803FD52C[] = "DISP LEFT NUM :";
/* 803FD53C */ char un_803FD53C[] = "DISP RIGHTNUM :";
/* 803FD54C */ char un_803FD54C[] = "METAL LEFT  :";
/* 803FD55C */ char un_803FD55C[] = "METAL RIGHT :";
/* 803FD56C */ char un_803FD56C[] = "LEFT PLAYER :";
/* 803FD57C */ char un_803FD57C[] = "RIGHT PLAYER:";
/* 803FD58C */ struct un_80304138_objalloc_t_x8 un_803FD58C[16] = {
    { 0, NULL, un_803FD4EC, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 3, NULL, un_803FD500, NULL, &un_803FA258.x100, 1.0f, 9.0f, 1.0f },
    { 2, NULL, un_803FD50C, un_803FD4B0, &un_803FA258.x104, 0.0f, 5.0f, 0.0f },
    { 2, NULL, un_803FD51C, un_803FD4DC, &un_803FA258.x108, 0.0f, 4.0f, 0.0f },
    { 3, NULL, un_803FD52C, NULL, &un_803FA258.x10C, 1.0f, 3.0f, 1.0f },
    { 3, NULL, un_803FD53C, NULL, &un_803FA258.x11C, 1.0f, 3.0f, 1.0f },
    { 3, NULL, un_803FD54C, NULL, &un_803FA258.xF8, 0.0f, 1.0f, 1.0f },
    { 3, NULL, un_803FD55C, NULL, &un_803FA258.xFC, 0.0f, 1.0f, 1.0f },
    { 2, NULL, un_803FD56C, un_803FB538, &un_803FA258.x110, 0.0f, 34.0f,
      0.0f },
    { 2, NULL, un_803FD56C, un_803FB538, &un_803FA258.x114, 0.0f, 34.0f,
      0.0f },
    { 2, NULL, un_803FD56C, un_803FB538, &un_803FA258.x118, 0.0f, 34.0f,
      0.0f },
    { 2, NULL, un_803FD57C, un_803FB538, &un_803FA258.x120, 0.0f, 34.0f,
      0.0f },
    { 2, NULL, un_803FD57C, un_803FB538, &un_803FA258.x124, 0.0f, 34.0f,
      0.0f },
    { 2, NULL, un_803FD57C, un_803FB538, &un_803FA258.x128, 0.0f, 34.0f,
      0.0f },
    { 1, un_80301B48, un_804D59F8, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FD78C */ char un_803FD78C[] = "<RESULT TEST>";
/* 803FD79C */ char un_803FD79C[] = "1P KIND :";
/* 803FD7A8 */ char un_803FD7A8[] = "2P KIND :";
/* 803FD7B4 */ char un_803FD7B4[] = "3P KIND :";
/* 803FD7C0 */ char un_803FD7C0[] = "4P KIND :";
/* 803FD7CC */ char un_803FD7CC[] = "All Player :";
/* 803FD7DC */ char un_803FD7DC[] = "1P RANK :";
/* 803FD7E8 */ char un_803FD7E8[] = "2P RANK :";
/* 803FD7F4 */ char un_803FD7F4[] = "3P RANK :";
/* 803FD800 */ char un_803FD800[] = "4P RANK :";
/* 803FD80C */ char un_803FD80C[] = "1P WIN  :";
/* 803FD818 */ char un_803FD818[] = "2P WIN  :";
/* 803FD824 */ char un_803FD824[] = "3P WIN  :";
/* 803FD830 */ char un_803FD830[] = "4P WIN  :";
/* 803FD83C */ char un_803FD83C[] = "ALL COLOR :";
/* 803FD848 */ char un_803FD848[] = "STEP ANIM :";
/* 803FD854 */ char un_803FD854[] = "PANEL HIDDEN :";
/* 803FD864 */ struct un_80304138_objalloc_t_x8 un_803FD864[19] = {
    { 0, NULL, un_803FD78C, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 2, NULL, un_803FD79C, un_803FB538, &un_803FA258.x144[0], 0.0f, 34.0f,
      0.0f },
    { 2, NULL, un_803FD7A8, un_803FB538, &un_803FA258.x144[1], 0.0f, 34.0f,
      0.0f },
    { 2, NULL, un_803FD7B4, un_803FB538, &un_803FA258.x144[2], 0.0f, 34.0f,
      0.0f },
    { 2, NULL, un_803FD7C0, un_803FB538, &un_803FA258.x144[3], 0.0f, 34.0f,
      0.0f },
    { 2, un_80301CE0, un_803FD7CC, un_803FB538, &un_803FA258.x144[4], 0.0f,
      34.0f, 0.0f },
    { 3, NULL, un_803FD7DC, NULL, &un_803FA258.x144[5], 1.0f, 4.0f, 1.0f },
    { 3, NULL, un_803FD7E8, NULL, &un_803FA258.x144[6], 1.0f, 4.0f, 1.0f },
    { 3, NULL, un_803FD7F4, NULL, &un_803FA258.x144[7], 1.0f, 4.0f, 1.0f },
    { 3, NULL, un_803FD800, NULL, &un_803FA258.x144[8], 1.0f, 4.0f, 1.0f },
    { 3, NULL, un_803FD80C, NULL, &un_803FA258.x144[9], 1.0f, 3.0f, 1.0f },
    { 3, NULL, un_803FD818, NULL, &un_803FA258.x144[10], 1.0f, 3.0f, 1.0f },
    { 3, NULL, un_803FD824, NULL, &un_803FA258.x144[11], 1.0f, 3.0f, 1.0f },
    { 3, NULL, un_803FD830, NULL, &un_803FA258.x144[12], 1.0f, 3.0f, 1.0f },
    { 3, NULL, un_803FD83C, NULL, &un_803FA258.x144[15], 0.0f, 9.0f, 1.0f },
    { 3, NULL, un_803FD848, NULL, &un_803FA258.x144[13], 0.0f, 1.0f, 1.0f },
    { 3, NULL, un_803FD854, NULL, &un_803FA258.x144[14], 0.0f, 1.0f, 1.0f },
    { 1, un_80301C80, un_804D59F8, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FDAC4 */ char un_803FDAC4[] = "< Sakoda Test >";
/* 803FDAD4 */ char un_803FDAD4[] = "Event Stage :";
/* 803FDAE4 */ char un_803FDAE4[] = "FixCamera Start >";
/* 803FDAF8 */ struct un_80304138_objalloc_t_x8 un_803FDAF8[4] = {
    { 0, NULL, un_803FDAC4, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 3, un_80301D7C, un_803FDAD4, NULL, &un_803FA258.x188, 1.0f, 51.0f,
      1.0f },
    { 1, un_80301D40, un_803FDAE4, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FDB78 */ char un_803FDB78[] = "< Sugano Test >";
/* 803FDB88 */ char un_803FDB88[] = "STAFFROLL START >";
/* 803FDB9C */ struct un_80304138_objalloc_t_x8 un_803FDB9C[4] = {
    { 0, NULL, un_803FDB78, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80301DCC, un_803FCBF4, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80301E08, un_803FDB88, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
