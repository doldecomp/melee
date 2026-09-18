#ifndef SYSDOLPHIN_BASELIB_CRYPT_H
#define SYSDOLPHIN_BASELIB_CRYPT_H

#include <Runtime/platform.h>

/// Simple additive checksum using the MD5 intial state. Not the MD5 algorithm.
void HSD_Checksum(u8* src, int len, void* dest);

/// @returns 0 if success, -1 if error
int HSD_Encrypt(u8* data, int len);

/// @returns 0 if success, -1 if error
int HSD_Decrypt(u8* data, int len);

#endif
