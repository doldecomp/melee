#ifndef _CHARPIPELINE_STRUCTURES_DOLPHINSTRING_H_
#define _CHARPIPELINE_STRUCTURES_DOLPHINSTRING_H_

#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif

u8 Strcat(char *str1, char *str2, char *dst, u32 dst_size);
void Strcpy(char *dst, char *src, u32 dst_size);
s8 Strcmp(char *str1, char *str2);
u32 Strlen(char *str);

#ifdef __cplusplus
}
#endif

#endif
