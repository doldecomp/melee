#ifndef MSL_CONSOLE_IO_H
#define MSL_CONSOLE_IO_H

#include <platform.h>

s32 MSL_ConsoleIo_80325F18(void);
int __write_console(u32, u8* buf, u32* n, void(*)());
int __read_console(u32, u8* buf, u32* n, void(*)());
int __close_console(u32);

#endif
