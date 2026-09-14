#ifndef MSL_CONSOLE_IO_H
#define MSL_CONSOLE_IO_H

#include <Runtime/platform.h>

#include <stdio.h>

s32 MSL_ConsoleIo_80325F18(void);
int __write_console(__file_handle, u8* buf, size_t* n, __idle_proc f);
int __read_console(__file_handle, u8* buf, size_t* n, __idle_proc f);
int __close_console(__file_handle);

#endif
