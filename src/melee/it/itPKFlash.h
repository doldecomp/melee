#ifndef _itPKFlash_h_
#define _itPKFlash_h_

#include <dolphin/types.h>

typedef struct PKFlashVars
{
    s32 xDD4_PKFlash;
    f32 xDD8_PKFlash;
    s32 xDDC_PKFlash;
    HSD_GObj* xDE0_PKFlash_Owner;
    s32 xDE4_PKFlash;
}PKFlashVars;

typedef struct PKFlashExplVars
{
    f32 xDD4;
    s32 xDD8;
    HSD_GObj* xDDC;
}PKFlashExplVars;

typedef struct itFlashAttributes
{
    f32 x0_FLASH_LIFETIMER;
    f32 x4_FLASH_HITBOX_SIZE_MUL;
    f32 x8_FLASH_GRAPHIC_SIZE_INIT_MUL;
    f32 xC_FLASH_GRAPHIC_SIZE_GROWTH_MUL;
    f32 x10_FLASH_UNK1;
    f32 x14_FLASH_PEAK_RISE_HEIGHT;
    f32 x18_FLASH_CONTROL;
    f32 x1C_FLASH_GRAVITY;
    f32 x20_FLASH_UNK2;
    f32 x24_FLASH_UNK3;
    f32 x28_FLASH_EXPLOSION_DELAY;
} itFlashAttributes;

typedef struct itFlashExplAttributes
{
    f32 x0_FLASH_EXPL_HITBOX_SIZE_MUL;
    f32 x4_FLASH_EXPL_GRAPHIC_SIZE_INIT;
    f32 x8_FLASH_EXPL_GRAPHIC_SIZE_GROWTH;
    f32 xC_FLASH_EXPL_BASE_DAMAGE;
    f32 x10_FLASH_EXPL_DAMAGE_MUL;

} itFlashExplAttributes;

#endif