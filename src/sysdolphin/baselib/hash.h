#ifndef _hash_h_
#define _hash_h_

#include <baselib/class.h>

#define hash(s) (s % 0x65)
HSD_ClassInfo* HSD_HashSearch(u32, const char* class_name, int);

#endif
