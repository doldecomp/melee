#ifndef _melee_it_id_h_
#define _melee_it_id_h_

// Based on "ID Lists" on the SSBM datasheet
// https://docs.google.com/spreadsheets/d/1JX2w-r2fuvWuNgGb6D3Cs4wHQKLFegZe2jhbBuIhCG8
enum {
    It_Kind_Capsule = 0x00,
    It_Kind_Box = 0x01,
    It_Kind_Taru = 0x02, // Barrel
    /*
    0x03, // Egg
    0x04, // Party Ball (Kusudama)
    0x05, // Barrel Cannon (TaruCann)
    0x06, // Bob-omb (BombHei)
    0x07, // Mr. Saturn (Dosei)
    0x08, // Heart Container
    0x09, // Maxim Tomato
    0x0A, // Starman (Super Star)
    0x0B, // Home-Run Bat
    0x0C, // Beam Sword
    0x0D, // Parasol
    0x0E, // Green Shell (G Shell)
    0x0F, // Red Shell (R Shell)
    0x10, // Ray Gun (L Gun)
    0x11, // Freezie (Freeze)
    0x12, // Food
    0x13, // Proximity Mine (MSBomb)
    0x14, // Flipper
    0x15, // Super Scope (S Scope)
    0x16, // Star Rod
    0x17, // Lip's Stick
    0x18, // Fan (Harisen)
    0x19, // Fire Flower (F Flower)
    0x1A, // Super Mushroom (Kinoko)

    0x1D, // Warp Star (WStar)
    0x1E, // Screw Attack (ScBall)
    0x1F, // Bunny Hood (RabbitC)
    */
    It_Kind_MetalB = 0x20, // Metal Box
    /*
    0x21, // Cloaking Device (SpyCloak)
    0x22, // Poké Ball (M Ball)

    // ITEM RELATED
    0x23, // Ray Gun recoil effect
    0x24, // Star Rod Star
    0x25, // Lips Stick Dust
    0x26, // Super Scope Beam
    0x27, // Ray Gun Beam
    0x28, // Hammer Head
    0x29, // Flower
    0x2A, // Yoshi's egg (Event)

    // MONSTERS
    0x2B, // Goomba (DKuriboh)
    0x2C, // Redead (Leadead)
    0x2D, // Octarok (Octarock)
    0x2E, // Ottosea
    0x2F, // Stone(Octarok Projectile)

    // CHARACTER RELATED
    */
    It_Kind_MarioFireball = 0x30, // Mario's fireball special
    /*
    0x31, // MAYBE Dr. Mario's pill?
    0x32, // Kirby's Cutter beam
    0x33, // Kirby's Hammer
    0x34, //
    0x35, //
    0x36, // Fox's Laser
    0x37, // Falco's Laser
    0x38, // Fox's afterimage
    */
    It_Kind_FalcoAfterimage = 0x39,
    /*
    0x3A, // Link's bomb
    0x3B, // Young Link's bomb
    0x3C, // Link's boomerang
    0x3D, // Young Link's boomerang
    0x3E, // Link's Hookshot
    0x3F, // Young Link's Hookshot
    0x40, // Arrow
    0x41, // Fire Arrow
    0x42, // PK Fire
    0x43, // PK Flash
    0x44, // PK Flash
    0x45, // PK Thunder (Primary)
    0x46, // PK Thunder
    0x47, // PK Thunder
    0x48, // PK Thunder
    0x49, // PK Thunder
    0x4A, // Fox's Blaster
    0x4B, // Falco's Blaster
    0x4C, // Link's Arrow
    0x4D, // Young Link's arrow
    0x4E, // PK Flash (explosion)
    0x4F, // Needle(thrown)
    0x50, // Needle
    0x51, // Pikachu's Thunder
    0x52, // Pichu's Thunder
    0x53, // Mario's cape
    0x54, // Dr.Mario's cape
    0x55, // Smoke (Sheik)
    0x56, // Yoshi's egg(thrown)
    0x57, //         Yoshi's Tongue??
    0x58, // Yoshi's Star
    0x59, // Pikachu's thunder (B)
    0x5A, // Pikachu's thunder (B)
    0x5B, // Pichu's thunder (B)
    0x5C, // Pichu's thunder (B)
    0x5D, // Samus's bomb
    0x5E, // Samus's chargeshot
    0x5F, // Missile
    0x60, // Grapple beam
    0x61, // Sheik's chain
    */
    It_Kind_PeachUnk = 0x62,
    It_Kind_PeachTurnip = 0x63,
    It_Kind_KoopaFlame = 0x64, // Bowser's flame
    /*
    0x65, // Ness's bat
    0x66, // Yoyo
    */
    It_Kind_PeachParasol = 0x67,
    It_Kind_PeachToad = 0x68, // Peach's toad special
    /*
    0x69, // Luigi's fire
    0x6A, // Ice(Iceclimbers)
    0x6B, // Blizzard
    0x6C, // Zelda's fire
    0x6D, // Zelda's fire (explosion)
    0x6E, //
    */
    It_Kind_PeachToadSpore = 0x6F, // Peach toad's spore effect
    /*
    0x70, // Mewtwo's Shadowball
    0x71, // Iceclimbers' Up , //B
    0x72, // Pesticide
    0x73, // Manhole
    0x74, // Fire(G&W)
    0x75, // Parashute
    0x76, // Turtle
    0x77, // Sperky
    0x78, // Judge
    0x79, //
    0x7A, // Sausage
    */
    It_Kind_ClinkMilk = 0x7B, // Milk (Young Link)
    /*
    0x7C, // Firefighter(G&W)
    0x7D, // Masterhand's Laser
    0x7E, // Masterhand's Bullet
    0x7F, // Crazyhand's Laser
    0x80, // Crazyhand's Bullet
    0x81, // Crazyhand's Bomb
    0x82, // Kirby copy Mario's Fire (B)
    0x83, // Kirby copy Dr. Mario's Capsule (B)
    0x84, // Kirby copy Luigi's Fire (B)
    0x85, // Kirby copy IceClimber's IceCube (B)
    0x86, // Kirby copy Peach's Toad (B)
    0x87, // Kirby copy Toad's Spore (B)
    0x88, // Kirby copy Fox's Laser (B)
    0x89, // Kirby copy Falco's Laser (B)
    0x8A, // Kirby copy Fox's Blaster (B)
    0x8B, // Kirby copy Falco's Blaster (B)
    0x8C, // Kirby copy Link's Arrow (B)
    0x8D, // Kirby copy Young Link's Arrow (B)
    0x8E, // Kirby copy Link's Arrow (B)
    0x8F, // Kirby copy Young Link's Arrow (B)
    0x90, // Kirby copy Mewtwo's Shadowball (B)
    0x91, // Kirby copy PK Flash (B)
    0x92, // Kirby copy PK Flash Explosion (B)
    0x93, // Kirby copy Pikachu's Thunder (B)
    0x94, // Kirby copy Pikachu's Thunder (B)
    0x95, // Kirby copy Pichu's Thunder (B)
    0x96, // Kirby copy Pichu's Thunder (B)
    0x97, // Kirby copy Samus' Chargeshot (B)
    0x98, // Kirby copy Sheik's Needle (thrown) (B)
    0x99, // Kirby copy Sheik's Needle (ground) (B)
    0x9A, // Kirby copy Bowser's Flame (B)
    0x9B, // Kirby copy Mr. Game & Watch's Sausage (B)
    0x9C, // (unique)
    0x9D, // Yoshi's Tongue?? (B)
    0x9E, // (unique)
    0x9F, // Coin
    0xA0, // (unique)

    // POKEMON
    0xA0     , //  Used for Random Pokemon value
    0xA1, // Goldeen (Tosakinto)
    0xA2, // Chicorita
    0xA3, // Snorlax
    0xA4, // Blastoise
    0xA5, // Weezing (Matadogas)
    0xA6, // Charizard (Lizardon)
    0xA7, // Moltres
    0xA8, // Zapdos
    0xA9, // Articuno
    0xAA, // Wobbuffet
    0xAB, // Scizor
    0xAC, // Unown
    0xAD, // Entei
    0xAE, // Raikou
    0xAF, // Suicune
    0xB0, // Bellossom (Kireihana)
    0xB1, // Electrode (Marumine)
    0xB2, // Lugia
    0xB3, // Ho-oh
    0xB4, // Ditto (Metamon)
    0xB5, // Clefairy
    0xB6, // Togepi
    0xB7, // Mew
    0xB8, // Celebi
    0xB9, // Staryu (Hitodeman)
    0xBA, // Chansey
    0xBB, // Porygon2
    0xBC, // Cyndaquil (Hinoarashi)
    0xBD, // Marill
    0xBE, // Venusaur (Fushigibana)

    // POKEMON RELATED
    0xBF, // Chicorita's Leaf
    0xC0, // Blastoise's Water
    0xC1, // Weezing's Gas
    0xC2, // Weezing's Gas
    0xC3, // Charizard's Breath
    0xC4, // Charizard's Breath
    0xC5, // Charizard's Breath
    0xC6, // Charizard's Breath
    0xC7, // Mini-Unowns
    0xC8, // Lugia's Aeroblast
    0xC9, // Lugia's Aeroblast
    0xCA, // Lugia's Aeroblast
    0xCB, // Ho-Oh's Flame
    0xCC, // Staryu's Star
    0xCD, // Healing Egg
    0xCE, // Cyndaquil's Fire
    0xCF, //

    // MONSTERS 2
    0xD0, // Old Goomba (Old-Kuri)
    0xD1, // Target (Mato)
    */
    It_Kind_Heiho = 0xD2, // Yoshi's story Shy Guy
    /*
    0xD3, // Koopa(Green) (Nokonoko)
    0xD4, // Koopa(Red) (PataPata)
    0xD5, // Likelile
    0xD6, // Old Redead (old-lead) [invalid]
    0xD7, // Old Octorok(old-octa) [invalid]
    0xD8, // Old Ottosea (old-otto)
    0xD9, // White Bear (whitebea)
    0xDA, // Klap
    0xDB, // Green Shell (zgshell)
    0xDC, // Red Shell (green act) (zrshell)

    // STAGE SPECIFIC
    0xDD, // Tingle (on balloon)
    0xDE, // [Invalid]
    0xDF, // [Invalid]
    0xE0, // [Invalid]
    0xE1, // Apple
    0xE2, // Healing Apple
    0xE3, // [Invalid]
    0xE4, // [Invalid]
    0xE5, // [Invalid]
    0xE6, // Tool (Flatzone)
    0xE7, // [Invalid]
    0xE8, // [Invalid]
    0xE9, // Birdo
    0xEA, // Arwing Laser
    0xEB, // Great Fox's Laser
    0xEC, // Birdo's Egg
    */
};

#endif
