#ifndef MELEE_LB_FILE_H
#define MELEE_LB_FILE_H

#include <platform.h>

#include <sysdolphin/baselib/forward.h>

void lbFile_800161C4(int file, uintptr_t src, uintptr_t dest, size_t size,
                     int type, int pri);
char* lbFileGetFullName(const char* basename);
size_t lbFile_8001634C(int fileno);
size_t lbFileGetSize(const char* basename);
void lbFile_800164A4(int file, uintptr_t dest, size_t* size, int pri,
                     HSD_DevComCallback callback, void* args);
void lbFile_80016580(const char* basename, void* dst, size_t* size,
                     HSD_DevComCallback callback, void* args);
void lbFile_8001668C(const char* basename, void* dst, size_t* size);
void lbFile_80016760(const char* basename, void** dst, size_t* size);
bool lbFile_800168A0(int arg0, const char* basename, void** dst, size_t* size);

#endif // MELEE_LB_FILE_H
