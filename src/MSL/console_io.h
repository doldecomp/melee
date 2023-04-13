#ifndef MSL_CONSOLE_IO_H
#define MSL_CONSOLE_IO_H

#include <platform.h>

s32 func_80325F18(void);
s32 __write_console(s32, s32 arg1, s32* arg2);
u8 __read_console(u32, u8* buf, u32* n);

#endif
