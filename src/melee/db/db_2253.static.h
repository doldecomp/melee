#ifndef __GALE01_225374
#define __GALE01_225374

#include "un/forward.h"

#include "db_2253.h" // IWYU pragma: export

// externs
extern unsigned char _stack_end[];
extern unsigned char _stack_addr[];

// rodata
static const Vec3 db_803B84D8 = { 0.0F, 1.0F, 0.0F };

// data
static char db_string_803EA6C8[] = "DATE Feb 13 2002  TIME 22:06:27";
static char db_string_803EA6E8[] = "DbCo.dat";
static char db_string_803EA6F4[] = "dbLoadCommonData";
static char db_string_803EA708[] = "[all PLink num] -- Report --\n";
static char db_string_803EA728[] =
    "------------------------------------------------------------\n";
static char db_string_803EA768[] = "------ Thread info ------\n";
static char db_string_803EA784[] = "base:%x, end:%x, size:%d peak:%d \n";
/* 3EA94C */ static char* db_ItemNames[] = {
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
/* 3EAA50 */ static char* db_PokemonNames[] = {
    "Random",      "Tosakinto", "Chicorita", "Kabigon",    "Kamex",
    "Matadogas",   "Lizardon",  "Fire",      "Thunder",    "Freezer",
    "Sonans",      "Hassam",    "Unknown",   "Entei",      "Raikou",
    "Suikun",      "Kireihana", "Marumine",  "Lugia",      "Houou",
    "Metamon",     "Pippi",     "Togepy",    "Mew",        "Cerebi",
    "Hitodeman",   "Lucky",     "Porygon2",  "Hinoarashi", "Maril",
    "Fushigibana",
};
/* 3EAAFC */ static char* db_BarrelEnemies[] = { "Kuriboh ", "Leadead ",
                                                 "Octarock", "Ottosei " };
/* 3EABA8 */ static char* db_AdventureEnemies[] = {
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
/* 3EABDC */ static int db_803EABDC[0xD] = { 0 };
static char db_string_803EAC10[0x78] =
    "Item=%d Foods=%d Yaku=%d Sp_Item=%d Pokemon=%d PokeShot=%d CZako=%d "
    "CZakoShot=%d Zako=%d ZakoShot=%d Shot=%d Etc=%d\n";
/* 3EAD40 */ static int db_SoundToggleOrder[4] = { 3, 2, 0, 1 };
/* 3EAE08 */ static struct {
    struct GXColor bg;
    struct GXColor fg;
} db_TextColors[2] = {
    { { 0x00, 0x00, 0x00, 0x00 }, { 0xFF, 0x00, 0x00, 0xFF } },
    { { 0x80, 0x40, 0xFF, 0x80 }, { 0x00, 0x00, 0x00, 0xFF } }
};

// bss
/* 49FA00 */ static struct {
    /*  +0 */ HSD_Pad current;
    /*  +4 */ HSD_Pad prev;
    /*  +8 */ HSD_Pad pressed;
    /*  +C */ HSD_Pad released;
    /* +10 */ HSD_Pad repeat;
} db_ButtonStates[4];
/* 49FA50 */ static char db_ItemAndPokemonMenuText_buf[0x50];
/* 49FAA0 */ static struct {
    unsigned int DisplayStatus; // 0=uninitialized, 1=visible, 2=hidden
    unsigned int DisplayFadeTimer;
    int ItemSpawnsEnabled;
    int Player;
    ItemKind CurrentlySelectedItem;
    int CurrentlySelectedPokemon;
    ItemKind LastSelectedItem;
    int LastSelectedPokemon;
    struct {
        u32 ShowEnemyStompRange : 1;
        u32 ShowItemPickupRange : 1;
        u32 ShowCoinPickupRange : 1;
    };
} db_ItemAndPokemonMenu;
/* 49FAC8 */ static struct {
    DevText* text;
    char buf[0x34C];
} db_CpuHandicapInfo;
/* 49FE18 */ static struct {
    DevText* text;
    char buf[0x5A4];
} db_AnimationInfo;
/* 4A03C0 */ static char db_CameraInfoDisplay_buf[0xC0];
/* 4A0480 */ static char db_SoundInfoText_buf[0x70];

// sdata
/* 4D4A08 */ int g_debugLevel = 1;
/* 4D4AF8 */ static int db_804D4AF8 = 1;

// sbss
/* 4D6B20 */ static int db_804D6B20;
/* 4D6B24 */ static char** db_submotion_names;
/* 4D6B28 */ static char** db_motionstate_names;
/* 4D6B2C */ static char** db_bonus_names;
/* 4D6B30 */ unsigned short db_gameLaunchButtonState;
/* 4D6B38 */ static DevText* db_ItemAndPokemonMenuText;
/* 4D6B3C */ static int db_ShowItemCollisionBubbles;
/* 4D6B40 */ static UnkFlagStruct db_ShowCpuHandicapInfo;
/* 4D6B48 */ static struct {
    int ShowFighterCollisionBubbles : 3;
    unsigned int MiscFighterVisualsStatus : 6;
    unsigned int ShowAnimationInfo : 1;
} db_804D6B48;
/* 4D6B50 */ static unsigned int db_MiscStageVisualsStatus;
/* 4D6B58 */ static DevText* db_CameraInfoDisplay;
/* 4D6B5C */ static unsigned char db_CameraInfoDisplayTimer;
/* 4D6B5D */ static unsigned char db_ShowCameraInfo;
/* 4D6B60 */ static int db_SoundToggles;
/* 4D6B64 */ static int db_ShowSoundInfo;
/* 4D6B68 */ static int db_SoundRelated_6B68;
/* 4D6B6C */ static int db_SoundRelated_6B6C;
/* 4D6B70 */ static int db_SoundRelated_6B70;
/* 4D6B74 */ static int db_SoundRelated_6B74;
/* 4D6B78 */ static DevText* db_SoundInfoText;
/* 4D6B7C */ static HSD_GObj* db_804D6B7C;
/* 4D6B80 */ static int db_MiscVisualEffectsStatus;
/* 4D6B88 */ static int db_804D6B88;
/* 4D6B8C */ static UnkFlagStruct db_5xSpeedStatus;
/* 4D6B90 */ static unsigned int db_ScreenshotPending;
/* 4D6B94 */ static int db_ScreenshotNumber;
/* 4D6B98 */ static struct {
    unsigned char x0;
    UnkFlagStruct x1;
} db_804D6B98;
/* 4D6B9C */ static struct {
    DevText* text;
    char buffer[1500];
}* db_804D6B9C;
/* 4D6BA0 */ static UnkFlagStruct db_804D6BA0;

// sdata2 (constants)

#endif
