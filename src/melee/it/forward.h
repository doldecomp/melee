#ifndef MELEE_IT_FORWARD_H
#define MELEE_IT_FORWARD_H

typedef struct Article Article;
typedef struct BobOmbRain BobOmbRain;
typedef struct CameraBoxFlags CameraBoxFlags;
typedef struct DynamicBoneTable DynamicBoneTable;
typedef struct ECB ECB;
typedef struct flag32 flag32;
typedef struct HSD_ObjAllocUnk HSD_ObjAllocUnk;
typedef struct HSD_ObjAllocUnk2 HSD_ObjAllocUnk2;
typedef struct HSD_ObjAllocUnk4 HSD_ObjAllocUnk4;
typedef struct HSD_ObjAllocUnk5 HSD_ObjAllocUnk5;
typedef struct HSD_ObjAllocUnk6 HSD_ObjAllocUnk6;
typedef struct Item Item;
typedef struct Item_DynamicBones Item_DynamicBones;
typedef struct ItemAttr ItemAttr;
typedef struct ItemCommonData ItemCommonData;
typedef struct ItemDynamics ItemDynamics;
typedef struct ItemDynamicsDesc ItemDynamicsDesc;
typedef struct ItemLogicTable ItemLogicTable;
typedef struct ItemModelDesc ItemModelDesc;
typedef struct ItemModStruct ItemModStruct;
typedef struct ItemStateArray ItemStateArray;
typedef struct ItemStateContainer ItemStateContainer;
typedef struct ItemStateDesc ItemStateDesc;
typedef struct ItemStateTable ItemStateTable;
typedef struct itHit itHit;
typedef struct itHurt itHurt;
typedef struct SpawnItem SpawnItem;
typedef struct UnkItemArticles3 UnkItemArticles3;

typedef enum Item_StateChangeFlags {
    ITEM_UNK_0x1 = (1 << 0),
    ITEM_ANIM_UPDATE = (1 << 1),
    ITEM_DROP_UPDATE = (1 << 2),
    ITEM_MODEL_UPDATE = (1 << 3),
    ITEM_HIT_PRESERVE = (1 << 4),
    ITEM_SFX_PRESERVE = (1 << 5),
    ITEM_COLANIM_PRESERVE = (1 << 6),
    ITEM_UNK_UPDATE = (1 << 7),
    ITEM_CMD_UPDATE = (1 << 8),
} Item_StateChangeFlags;

typedef enum Item_UnkKinds {
    ITEM_UNK_MATO = 4,
    ITEM_UNK_LOCKON = 5,
    ITEM_UNK_ENEMY = 6,
} Item_UnkKinds;

#endif
