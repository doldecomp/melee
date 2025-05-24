#ifndef __GALE01_225374
#define __GALE01_225374

#include "un/forward.h"

#include "db_2253.h" // IWYU pragma: export

// externs
extern UNK_T cm_80453004;
extern HSD_ObjAllocUnk4 it_804A0E30;
extern unsigned char _stack_end[];
extern unsigned char _stack_addr[];
void lbShadow_8000EEE0(HSD_GObj*);

// rodata
const Vec3 db_803B84D8 = { 0.0F, 1.0F, 0.0F };

// data
char db_803EA6C8[] = "DATE Feb 13 2002  TIME 22:06:27";
char db_string_803EA6E8[] = "DbCo.dat";
char db_string_803EA6F4[] = "dbLoadCommonData";
char db_string_803EA708[] = "[all PLink num] -- Report --\n";
char db_string_803EA728[] =
    "------------------------------------------------------------\n";
char db_string_803EA768[] = "------ Thread info ------\n";
char db_string_803EA784[] = "base:%x, end:%x, size:%d peak:%d \n";
char* db_803EA94C[] = {
    // clang-format off
    "Capsule ",
    "Box     ",
    "Taru    ",
    "Egg     ",
    "Kusudama",
    "TaruCann",
    "BombHei ",
    "Dosei   ",
    "Heart   ",
    "Tomato  ",
    "Star    ",
    "Bat     ",
    "Sword   ",
    "Parasol ",
    "G Shell ",
    "R Shell ",
    "L Gun   ",
    "Freeze  ",
    "Foods   ",
    "MSBomb  ",
    "Flipper ",
    "S Scope ",
    "StarRod ",
    "LipStick",
    "Harisen ",
    "F Flower",
    "Kinoko  ",
    "DKinoko ",
    "Hammer  ",
    "WStar   ",
    "ScBall  ",
    "RabbitC ",
    "MetalB  ",
    "Spycloak",
    "M Ball  ",
    // clang-format on
};
char* db_803EAA50[] = {
    "Random",      "Tosakinto", "Chicorita", "Kabigon",    "Kamex",
    "Matadogas",   "Lizardon",  "Fire",      "Thunder",    "Freezer",
    "Sonans",      "Hassam",    "Unknown",   "Entei",      "Raikou",
    "Suikun",      "Kireihana", "Marumine",  "Lugia",      "Houou",
    "Metamon",     "Pippi",     "Togepy",    "Mew",        "Cerebi",
    "Hitodeman",   "Lucky",     "Porygon2",  "Hinoarashi", "Maril",
    "Fushigibana",
};
char* db_803EAAFC[] = { "Kuriboh ", "Leadead ", "Octarock", "Ottosei " };
char* db_803EABA8[] = {
    // clang-format off
    "old-Kuri",
    "Mato    ",
    "Heiho   ",
    "Nokonoko",
    "Patapata",
    "likelike",
    "old-lead",
    "old-octa",
    "old-otto",
    "whitebea",
    "klap    ",
    "zgshell ",
    "zrshell ",
    // clang-format on
};
int db_803EABDC[0xD] = { 0 };
char db_string_803EAC10[0x78] =
    "Item=%d Foods=%d Yaku=%d Sp_Item=%d Pokemon=%d PokeShot=%d CZako=%d "
    "CZakoShot=%d Zako=%d ZakoShot=%d Shot=%d Etc=%d\n";
int db_803EAD40[4] = { 3, 2, 0, 1 };
struct {
    struct GXColor bg;
    struct GXColor fg;
} db_803EAE08[2] = {
    { { 0x00, 0x00, 0x00, 0x00 }, { 0xFF, 0x00, 0x00, 0xFF } },
    { { 0x80, 0x40, 0xFF, 0x80 }, { 0x00, 0x00, 0x00, 0xFF } }
};

// bss
struct {
    int x0;
    int x4;
    int x8;
    int xC;
    int x10;
} db_8049FA00[4];
char db_8049FA50[0x50];
struct {
    unsigned int x0;
    unsigned int x4;
    int x8;
    int xC;
    ItemKind x10;
    int x14;
    ItemKind x18;
    int x1C;
    UnkFlagStruct x20;
    int x24;
} db_8049FAA0;
struct {
    DevText* x0;
    char x4[0x34C];
} db_8049FAC8;
struct {
    DevText* x0;
    char x4[0x5A4];
} db_8049FE18;
char db_804A03C0[0xC0];
char db_804A0480[0x70];

// sdata
int g_debugLevel = 1;
int db_804D4AF8 = 1;

// sbss
int db_804D6B20;
char** submotion_names;
char** motionstate_names;
char** bonus_names;
unsigned short db_804D6B30;
DevText* db_804D6B38;
int db_804D6B3C;
UnkFlagStruct db_804D6B40;
struct {
    int b0 : 3;
    unsigned int b3 : 6;
    unsigned int b9 : 1;
    int b10 : 1;
    int b11 : 1;
    int b12 : 1;
    int b13 : 1;
    int b14 : 1;
    int b15 : 1;
    int b16 : 1;
    int b17 : 1;
    int b18 : 1;
    int b19 : 1;
    int b20 : 1;
    int b21 : 1;
    int b22 : 1;
    int b23 : 1;
    int b24 : 1;
    int b25 : 1;
    int b26 : 1;
    int b27 : 1;
    int b28 : 1;
    int b29 : 1;
    int b30 : 1;
    int b31 : 1;
} db_804D6B48;
unsigned int db_804D6B50;
DevText* db_804D6B58;
unsigned char db_804D6B5C;
unsigned char db_804D6B5D;
int db_804D6B60;
int db_804D6B64;
int db_804D6B68;
int db_804D6B6C;
int db_804D6B70;
int db_804D6B74;
int db_804D6B78;
int db_804D6B7C;
int db_804D6B80;
int db_804D6B88;
UnkFlagStruct db_804D6B8C;
unsigned int db_804D6B90;
int db_804D6B94;
struct {
    unsigned char x0;
    UnkFlagStruct x1;
} db_804D6B98;
struct {
    DevText* text;
    char buffer[1500];
}* db_804D6B9C;
UnkFlagStruct db_804D6BA0;

// sdata2 (constants)

#endif
