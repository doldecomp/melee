/**
 * @file ftdata.h
 * @brief Fighter asset loading, archive parsing, and character data tables.
 * @details Declares functions and global tables for loading character DAT files
 * from disc (models, animations, special attributes, costumes, particle effects)
 * and managing runtime FigaTree animation trees.
 * Module prefix: ft (Fighter)
 */

#ifndef GALE01_085560
#define GALE01_085560

#include <Runtime/platform.h>

#include <melee/ft/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <melee/ft/types.h>

/**
 * @brief Updates self-velocity based on root bone joint translation delta relative to current position.
 * @param gobj Fighter game object pointer.
 */
/* 08521C */ void ft_8008521C(Fighter_GObj* gobj);

/**
 * @brief Resets all global fighter data pointers, costume lists, and model allocation slots.
 */
/* 0852B0 */ void ft_800852B0(void);

/**
 * @brief Resets character reference counters to zero across all character kinds.
 */
/* 08549C */ void ft_8008549C(void);

/**
 * @brief Adjusts the active reference count for a character kind, asserting on underflow.
 * @param idx Character kind index.
 * @param increment Value to add (+1 on load, -1 on unload).
 */
/* 085560 */ void ftData_80085560(int idx, int increment);

/**
 * @brief Queues asynchronous DVD file loading for a character's base DAT, costumes, anims, and effects.
 * @param kind Character kind.
 * @param color Costume index (or 0xFF for all costumes).
 */
/* 0855C8 */ void ftData_800855C8(FighterKind kind, u8 color);

/**
 * @brief Synchronously loads and parses the main character DAT archive into gFtDataList.
 * @param kind Character kind to load.
 */
/* 08572C */ void ftData_8008572C(FighterKind);

/**
 * @brief Loads Kirby copy ability hat and costume assets for copied powers.
 * @param arg0 Target parameter or hat ID.
 * @param color Hat costume color.
 */
/* 08578C */ void ftData_8008578C(int, u8 color);

/**
 * @brief Calls character-specific secondary initialization callback (e.g. Kirby hat setup).
 * @param kind Character kind.
 */
/* 0857E0 */ void ftData_800857E0(FighterKind);

/**
 * @brief Loads and parses a character's costume model and material animation archive.
 * @param kind Character kind.
 * @param costume_id Costume index.
 */
/* 085820 */ void ftData_80085820(FighterKind, int costume_id);

/**
 * @brief Loads costume model archive data (duplicate/fallback entry point).
 * @param kind Character kind.
 * @param costume_id Costume index.
 */
/* 0858E4 */ void ftData_800858E4(FighterKind, int costume_id);

/**
 * @brief Unmaps and frees a fighter's model slot allocation if no other fighter shares it.
 * @param fp Fighter state pointer.
 */
/* 0859A8 */ void ftData_800859A8(Fighter*);

/**
 * @brief Loads character animation archive (PlXxAJ.dat) and resolves animation pointers.
 * @param kind Character kind.
 */
/* 085A14 */ void ftData_80085A14(FighterKind);

/**
 * @brief Allocates fighter animation buffers and ensures character animation data is loaded.
 * @param fp Fighter state pointer.
 */
/* 085B10 */ void ftData_80085B10(Fighter*);

/**
 * @brief Allocates animation buffers and resolves FigaTree pointers for cinematic demo playback.
 * @param fp Fighter state pointer.
 * @param arg1 Starting animation index.
 * @param arg2 Ending animation index.
 */
/* 085B98 */ void ftData_80085B98(Fighter*, int, int);

/**
 * @brief Loads and relocates FigaTree animation for a motion state into primary buffer fp->x59C.
 * @details If fp is Nana and Popo has already loaded the animation, copies and relocates
 * from Popo's buffer without reloading from ARAM/DVD.
 * @param fp Target fighter state pointer.
 * @param arg1 Source fighter state pointer (e.g. Popo or self).
 * @param msid Motion state ID to load.
 */
/* 085CD8 */ void ftData_80085CD8(Fighter*, Fighter*, enum_t msid);

/**
 * @brief Loads and relocates FigaTree animation into secondary buffer fp->x5A0 for animation blending.
 * @param fp Fighter state pointer.
 * @param msid Motion state ID.
 * @return Pointer to loaded FigaTree animation structure.
 */
/* 085E50 */ FigaTree* ftData_80085E50(Fighter*, enum_t msid);

/**
 * @brief Retrieves the animation metadata structure for a motion state, falling back from Nana to Popo.
 * @param fp Fighter state pointer.
 * @param msid Motion state ID.
 * @return Pointer to animation metadata.
 */
/* 085FD4 */ struct ftData_80085FD4_ret* ftData_80085FD4(Fighter* fp,
                                                         FtMotionId msid);

/**
 * @brief Returns the primary leader fighter (Popo) if fp is Nana, or NULL otherwise.
 * @param arg0 Fighter state pointer.
 * @return Pointer to partner Popo Fighter struct, or NULL.
 */
/* 086060 */ Fighter* ftData_80086060(Fighter* arg0);

/// Per-character costume list descriptors (joint models and costume counts).
/* 3C0EC0 */ extern struct UnkCostumeList
    CostumeListsForeachCharacter[Ft_Kind_Max];

/// Per-character subaction animation counts.
/* 3C0FC8 */ extern struct ftData_UnkCountStruct
    ftData_Table_Unk0[Ft_Kind_Max];

/// Per-character secondary initialization callbacks (e.g. Kirby hat init).
/* 3C10D0 */ extern Event ftData_Table_Unk1[Ft_Kind_Max];

/// Per-character demo animation count descriptors.
/* 3C10D0 */ extern struct ftData_UnkCountStruct
    ftData_UnkIntPairs[Ft_Kind_Max];

/// Per-character load callbacks called upon character spawn.
/* 3C1154 */ extern HSD_GObjEvent ftData_OnLoad[Ft_Kind_Max];

/// Per-character death callbacks invoked upon KO.
/* 3C11D8 */ extern HSD_GObjEvent ftData_OnDeath[Ft_Kind_Max];

/// Per-character user data removal callbacks (cleanup).
/* 3C125C */ extern HSD_GObjEvent ftData_OnUserDataRemove[Ft_Kind_Max];

/// Ground Side Special (Side-B) entry functions per character.
/* 3C13E8 */ extern HSD_GObjEvent ftData_SpecialS[Ft_Kind_Max];

/// Aerial Up Special (Up-B) entry functions per character.
/* 3C146C */ extern HSD_GObjEvent ftData_SpecialAirHi[Ft_Kind_Max];

/// Aerial Down Special (Down-B) entry functions per character.
/* 3C14F0 */ extern HSD_GObjEvent ftData_SpecialAirLw[Ft_Kind_Max];

/// Aerial Side Special (Side-B) entry functions per character.
/* 3C1574 */ extern HSD_GObjEvent ftData_SpecialAirS[Ft_Kind_Max];

/// Aerial Neutral Special (Neutral-B) entry functions per character.
/* 3C15F8 */ extern HSD_GObjEvent ftData_SpecialAirN[Ft_Kind_Max];

/// Ground Neutral Special (Neutral-B) entry functions per character.
/* 3C167C */ extern HSD_GObjEvent ftData_SpecialN[Ft_Kind_Max];

/// Ground Down Special (Down-B) entry functions per character.
/* 3C1700 */ extern HSD_GObjEvent ftData_SpecialLw[Ft_Kind_Max];

/// Ground Up Special (Up-B) entry functions per character.
/* 3C1784 */ extern HSD_GObjEvent ftData_SpecialHi[Ft_Kind_Max];

/// Energy projectile absorption callbacks (Ness PSI Magnet, G&W Oil Panic).
/* 3C1808 */ extern HSD_GObjEvent ftData_OnAbsorb[Ft_Kind_Max];

/// Extended item pickup callbacks (Link/Young Link bomb/boomerang stow).
/* 3C188C */ extern Fighter_ItemEvent ftData_OnItemPickupExt[Ft_Kind_Max];

/// Special character motion state callbacks (e.g. Kirby/Bowser special state handlers).
/* 3C1DB4 */ extern HSD_GObjEvent ftData_UnkMotionStates3[Ft_Kind_Max];

/// Special character charge/state handlers (e.g. DK Giant Punch, Samus Charge Shot).
/* 3C1E38 */ extern HSD_GObjEvent ftData_UnkMotionStates4[Ft_Kind_Max];

/// Character bone matrix update callbacks.
/* 3C20CC */ extern Fighter_UnkMtxEvent ftData_UnkMtxFunc0[Ft_Kind_Max];

/// Model group visibility callbacks (high poly, low poly, metal models).
/* 3C2150 */ extern ftData_UnkModelStruct ftData_UnkIntBoolFunc0;

/// Cinematic demo animation filename tables per character.
/* 3C2468 */ extern Fighter_DemoStrings* ftData_803C2468[Ft_Kind_Max];

/// Motion file string resolution callbacks per character.
/* 3C24EC */ extern Fighter_MotionFileStringGetter
    ftData_803C24EC[Ft_Kind_Max];

/// Demo animation pointer event callbacks per character.
/* 3C2570 */ extern Fighter_UnkPtrEvent ftData_UnkDemoCallbacks0[Ft_Kind_Max];

/// Async particle effect bank IDs per character (-1 if none).
/* 3C26FC */ extern u8 ftData_UnkBytePerCharacter[Ft_Kind_Max];

/// Global common motion state definition list (Wait, Walk, Attack, etc.).
/* 3C2800 */ extern MotionState ftData_MotionStateList[ftCo_MS_Count];

/// Sub-action motion state table entries.
/* 3C52A0 */ extern MotionState ftData_803C52A0[14];

/// Global array of parsed character data pointers loaded from PlXx.dat archives.
/* 4598B8 */ extern ftData* gFtDataList[Ft_Kind_Max];

#endif
