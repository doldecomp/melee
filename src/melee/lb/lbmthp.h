#ifndef GALE01_01E8F8
#define GALE01_01E8F8

#include <sysdolphin/baselib/forward.h>

#include <stddef.h>

void lbMthp_8001F410(const char* filename, u32* rate_table, void* buf,
                     size_t heap_size, int loop);
void lbMthp_8001F578(void);
int lbMthp_8001F5C4(void);
u32 lbMthp_8001F5D4(void);
int lbMthp_8001F5E4(void);
int lbMthp_8001F5F4(void);
int lbMthp_8001F604(void);
void lbMthp_8001F614(int arg0);
HSD_SObj* lbMthp_8001F624(HSD_GObj*, int, int);
void lbMthp_8001F67C(HSD_GObj*, int);
void lbMthp_8001F800(void);
void lbMthp_8001F87C(void);
HSD_SObj* lbMthp8001F890(HSD_GObj*);
void lbMthp8001F928(HSD_GObj*, int);
void lbMthp8001FAA0(const char* filename, int, int);

#endif
