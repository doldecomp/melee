/**
 * @file ftparts.h
 * @brief Fighter model parts and joint management
 * @details Handles the dynamic linking of models, joints, and DObjs for Melee fighters.
 * Module prefix: ft
 */
#ifndef GALE01_0735BC
#define GALE01_0735BC

#include <Runtime/platform.h>

#include <melee/ft/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <dolphin/mtx.h>

struct Fighter_804D6540_x0_t;

/**
 * @brief Creates a position matrix for a fighter's JObj, taking global Z-scale into account.
 * @param jobj The JObj to make the matrix for
 * @param mtx The input transform matrix
 * @param rmtx The resulting transform matrix
 */
/* 0735BC */ void ftParts_JObjMakePositionMtx(HSD_JObj*, Mtx mtx, Mtx rmtx);

/**
 * @brief Initializes the custom JObj class used by fighters.
 */
/* 073700 */ void ftParts_JObjInfoInit(void);

/**
 * @brief Changes a given JObj to use the fighter's custom JObj class.
 * @param jobj The JObj to update
 */
/* 073758 */ void ftParts_80073758(HSD_JObj*);

/**
 * @brief Loads a joint into an interpolated JObj.
 * @param jobj The JObj to load into
 * @param joint The joint data
 * @param parent The parent JObj
 * @return 0 on success
 */
/* 073780 */ s32 ftParts_IntpJObjLoad(HSD_JObj*, HSD_Joint*, HSD_JObj* parent);

/**
 * @brief Initializes the custom interpolated JObj class used by fighters.
 */
/* 0737D8 */ void ftParts_IntpJObjInfoInit(void);

/**
 * @brief Sets up a rigid matrix for a PObj during rendering.
 * @param pobj The polygon object
 * @param vmtx The view matrix
 * @param pmtx The position matrix
 * @param rendermode Rendering mode flags
 */
/* 073830 */ void ftPartsSetupRigidMtx(HSD_PObj*, Mtx vmtx, Mtx pmtx,
                                       u32 rendermode);

/**
 * @brief Sets up a shared vertex matrix for a PObj during rendering.
 * @param pobj The polygon object
 * @param vmtx The view matrix
 * @param pmtx The position matrix
 * @param rendermode Rendering mode flags
 */
/* 0739B8 */ void ftPartsSetupSharedVtxMtx(HSD_PObj*, Mtx vmtx, Mtx pmtx,
                                           u32 rendermode);

/**
 * @brief Sets up an envelope matrix for a skinning PObj during rendering.
 * @param pobj The polygon object
 * @param vmtx The view matrix
 * @param pmtx The position matrix
 * @param rendermode Rendering mode flags
 */
/* 073CA8 */ void ftPartsSetupEnvelopeMtx(HSD_PObj*, Mtx vmtx, Mtx pmtx,
                                          u32 rendermode);

/**
 * @brief Sets up matrices for a PObj based on its specific skinning/envelope type.
 * @param pobj The polygon object
 * @param vmtx The view matrix
 * @param pmtx The position matrix
 * @param rendermode Rendering mode flags
 */
/* 074048 */ void ftParts_PObjSetupMtx(HSD_PObj*, Mtx vmtx, Mtx pmtx,
                                       u32 rendermode);

/**
 * @brief Initializes the custom PObj class used by fighters.
 */
/* 0740E4 */ void ftParts_PObjInfoInit(void);

/**
 * @brief Sets the default PObj class to the fighter's custom PObj class.
 */
/* 074148 */ void ftPartsPObjSetDefaultClass(void);

/**
 * @brief Clears the default PObj class.
 */
/* 074170 */ void ftPartsPObjClearDefaultClass(void);

/**
 * @brief Traverses a JObj and updates the bone and dobj arrays.
 * @param fighter The fighter
 * @param bone The bone struct to populate
 * @param jobj The current JObj being processed
 * @param dobj_index Pointer to the running index of dobjs
 * @param tree_depth The current depth in the skeletal tree
 */
/* 074194 */ void ftParts_80074194(Fighter*, FighterBone* bone, HSD_JObj*,
                                   int* dobj_index, u32 tree_depth);

/**
 * @brief Sets up the parts structure for a fighter gobj, building out the bone list.
 * @param fighter_obj The fighter's GObj
 */
/* 0743E0 */ void ftParts_SetupParts(Fighter_GObj* fighter_obj);

/* 0743E0 */ void func_800743E0(void);

/**
 * @brief Sets up the animation skeleton secondary jobj references for a fighter.
 * @param gobj The fighter's GObj
 */
/* 07462C */ void ftParts_8007462C(Fighter_GObj*);

/**
 * @brief Loads a joint into the custom IntpJObj class.
 * @param joint The joint to load
 * @return The allocated JObj
 */
/* 07482C */ HSD_JObj* ftParts_8007482C(HSD_Joint*);

/**
 * @brief Initializes the visibility table for a fighter costume.
 * @param desc The parts description struct
 * @param vis The visibility tracking struct
 * @param costume_id The selected costume ID
 * @param dobj_list1 Primary DObj list
 * @param dobj_list2 Secondary DObj list
 */
/* 07487C */ void ftParts_8007487C(FtPartsDesc*, FtPartsVis*, u32 costume_id,
                                   DObjList*, DObjList*);

/**
 * @brief Fully sets up the part visibility for a fighter model based on their costume.
 * @param gobj The fighter's GObj
 */
/* 0749CC */ void ftParts_800749CC(Fighter_GObj*);

/**
 * @brief Sets the pending part model index for a specific model group.
 * @param gobj The fighter GObj
 * @param model_idx The model group index
 * @param val The pending value to set
 */
/* 074A4C */ void ftParts_80074A4C(Fighter_GObj*, int model_idx, int val);

/**
 * @brief Gets the pending part model index for a specific model group.
 * @param gobj The fighter GObj
 * @param model_idx The model group index
 * @return The pending index
 */
/* 074A74 */ int ftParts_80074A74(Fighter_GObj*, int model_idx);

/**
 * @brief Commits the pending part model indices into the active indices.
 * @param gobj The fighter GObj
 */
/* 074A8C */ void ftParts_80074A8C(Fighter_GObj*);

/**
 * @brief Clears the active model indices, effectively hiding model groups.
 * @param gobj The fighter GObj
 */
/* 074ACC */ void ftParts_80074ACC(Fighter_GObj*);

/**
 * @brief Sets a part model index and immediately updates DObj visibility flags.
 * @param gobj The fighter GObj
 * @param model_idx The model group index
 * @param val The model index to set
 */
/* 074B0C */ void ftParts_80074B0C(Fighter_GObj*, int model_idx, int val);

/**
 * @brief Updates DObj visibility for a given visibility index, hiding parts that don't match the active state.
 * @param fp The fighter
 * @param vis The visibility struct
 * @param idx The visibility lookup index
 * @param dobj_list The list of DObjs to apply visibility to
 */
/* 074B6C */ void ftParts_80074B6C(Fighter*, FtPartsVis*, int, DObjList*);

/**
 * @brief Clears (hides) all DObjs associated with a given visibility lookup index.
 * @param vis The visibility struct
 * @param idx The visibility lookup index
 * @param dobj_list The list of DObjs
 */
/* 074CA0 */ void ftParts_80074CA0(FtPartsVis*, int, DObjList*);

/**
 * @brief Sets (shows) all DObjs associated with a given visibility lookup index.
 * @param vis The visibility struct
 * @param idx The visibility lookup index
 * @param dobj_list The list of DObjs
 */
/* 074D7C */ void ftParts_80074D7C(FtPartsVis*, int, DObjList*);

/**
 * @brief Allocates the parts and dobj_list arrays for a newly created fighter.
 * @param fp The fighter
 */
/* 074E58 */ void ftParts_80074E58(Fighter*);

/// Fighter_BonePersonalToCommon
/**
 * @brief Gets the actual internal bone index given a canonical Fighter_Part identifier.
 * @param fp The fighter
 * @param part The canonical part (e.g. FtPart_TransN)
 * @return The mapped bone index
 */
/* 07500C */ Fighter_Part ftParts_GetBoneIndex(Fighter*, Fighter_Part);

/**
 * @brief Remaps a joint index from one fighter's parts table to another.
 * @param to_table_idx Target table index
 * @param from_table_idx Source table index
 * @param joint_idx Joint index to remap
 * @return The mapped joint index, or FTPART_INVALID
 */
/* 075028 */ int ftPartsRemap(size_t to_table_idx, size_t from_table_idx,
                              size_t joint_idx);
/// Upper bound on FighterPartsTable::parts_num; sizes fp->parts.
#define MAX_FT_PARTS 140

/**
 * @brief Checks if a specific part is excluded or disabled for a fighter kind.
 * @param ftkind The fighter kind (e.g. Fox, Mario)
 * @param part The part index
 * @return A bitmask if the part is disabled, 0 otherwise
 */
/* 07506C */ u32 ftParts_8007506C(FighterKind ftkind, int part);

/**
 * @brief Applies model events and visibility updates for a fighter.
 * @param fp The fighter
 * @param event_idx Event type index
 * @param is_visible True to show, false to hide
 */
/* 0750C8 */ void ftParts_800750C8(Fighter*, enum_t, bool);

/**
 * @brief Finds the n-th TObj within a DObjList.
 * @param dobj_list The list of DObjs
 * @param n The zero-based index of the TObj to find
 * @return Pointer to the TObj
 */
/* 075240 */ HSD_TObj*
ftParts_80075240(DObjList*, int n); ///< finds the n-th TObj in a DObjList

/**
 * @brief Inserts a new JObj into the skeleton relative to a root JObj.
 * @param type Insertion type (0: child, 1: child sibling, 2: parent child, 3: sibling)
 * @param root The reference JObj
 * @param new_jobj The newly inserted JObj
 */
/* 075304 */ void ftParts_80075304(u8, HSD_JObj*, HSD_JObj*);

/**
 * @brief Dynamically attaches a joint (like an item or weapon) to a fighter bone.
 * @param fighter The fighter
 * @param attach_info Info detailing where and how to attach
 * @param joint The joint to attach
 */
/* 0753D4 */ void ftParts_800753D4(Fighter*, struct Fighter_804D6540_x0_t*,
                                   HSD_Joint*);

/**
 * @brief Removes a dynamically attached joint from a fighter bone.
 * @param fighter The fighter
 * @param attach_info Info detailing what to remove
 */
/* 0755E8 */ void ftParts_800755E8(Fighter*, struct Fighter_804D6540_x0_t*);

/**
 * @brief Gathers DObjs from a dynamically attached JObj hierarchy.
 * @param gobj Unused fighter gobj
 * @param jobj The root JObj of the attachment
 * @param dobj_list List to populate
 */
/* 075650 */ void ftParts_80075650(Fighter_GObj*, HSD_JObj*, struct DObjList*);

/**
 * @brief Sets the rotation of a JObj and clears its quaternion flag.
 * @param jobj The JObj
 * @param quat Quaternion rotation
 */
/* 07584C */ void ftParts_JObjSetRotation(HSD_JObj*, Quaternion*);

/**
 * @brief Sets the X rotation for a specific fighter part.
 * @param fp The fighter
 * @param part_idx The bone/part index
 * @param rotate_x Rotation angle in radians
 */
/* 07592C */ void ftPartSetRotX(Fighter*, int part_idx, f32 rotate_x);

/**
 * @brief Sets the Y rotation for a specific fighter part.
 * @param fp The fighter
 * @param part_idx The bone/part index
 * @param rotate_y Rotation angle in radians
 */
/* 075AF0 */ void ftPartSetRotY(Fighter*, int part_idx, f32 rotate_y);

/**
 * @brief Sets the Z rotation for a specific fighter part.
 * @param fp The fighter
 * @param part_idx The bone/part index
 * @param rotate_z Rotation angle in radians
 */
/* 075CB4 */ void ftPartSetRotZ(Fighter*, int part_idx, f32 rotate_z);

/// @returns Blend frames.
/**
 * @brief Gets the X rotation of a specific fighter part.
 * @param fp The fighter
 * @param part_idx The bone/part index
 * @return Rotation angle in radians
 */
/* 075E78 */ float ftPartGetRotX(Fighter*, int part_idx);

/**
 * @brief Gets the Z rotation of a specific fighter part.
 * @note Actually returns RotationY from the internal structure.
 * @param fp The fighter
 * @param part_idx The bone/part index
 * @return Rotation angle in radians
 */
/* 075F48 */ float ftPartGetRotZ(Fighter*, int part_idx);

#endif
