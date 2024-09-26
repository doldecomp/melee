#ifndef MELEE_IT_ITPKFLASH_H
#define MELEE_IT_ITPKFLASH_H

#include <platform.h>
#include <baselib/forward.h>

typedef struct itPKFlush_ItemVars {
    s32 xDD4_PKFlash;
    float xDD8_PKFlash;
    s32 xDDC_PKFlash;
    HSD_GObj* xDE0_PKFlash_Owner;
    s32 xDE4_PKFlash;
} itPKFlush_ItemVars;

typedef struct itPKFlushExplode_ItemVars {
    float xDD4;
    s32 xDD8;
    HSD_GObj* xDDC;
} itPKFlushExplode_ItemVars;

typedef struct itFlashAttributes {
    float x0_FLASH_LIFETIMER;
    float x4_FLASH_HITBOX_SIZE_MUL;
    float x8_FLASH_GRAPHIC_SIZE_INIT_MUL;
    float xC_FLASH_GRAPHIC_SIZE_GROWTH_MUL;
    float x10_FLASH_UNK1;
    float x14_FLASH_PEAK_RISE_HEIGHT;
    float x18_FLASH_CONTROL;
    float x1C_FLASH_GRAVITY;
    float x20_FLASH_UNK2;
    float x24_FLASH_UNK3;
    float x28_FLASH_EXPLOSION_DELAY;
} itFlashAttributes;

typedef struct itFlashExplAttributes {
    float x0_FLASH_EXPL_HITBOX_SIZE_MUL;
    float x4_FLASH_EXPL_GRAPHIC_SIZE_INIT;
    float x8_FLASH_EXPL_GRAPHIC_SIZE_GROWTH;
    float xC_FLASH_EXPL_BASE_DAMAGE;
    float x10_FLASH_EXPL_DAMAGE_MUL;
} itFlashExplAttributes;

#endif
