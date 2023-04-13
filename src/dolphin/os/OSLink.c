#include <platform.h>

#include <dolphin/os/OSLink.h>

#define OS_MODULE_LIST_ADDR 0x800030C8
#define OS_STRING_TABLE_ADDR 0x800030D0
#define OS_BASE_CACHED 0x80003000

struct OSModuleQueue { /* Relocatable Module Queue @ 800030c8 */
    int* pFirst;
    int* pLast;
};

extern struct OSModuleQueue __OSModuleInfoList AT_ADDRESS(OS_BASE_CACHED |
                                                          OS_MODULE_LIST_ADDR);
extern const void* __OSStringTable AT_ADDRESS(OS_BASE_CACHED |
                                              OS_STRING_TABLE_ADDR);

void __OSModuleInit(void)
{
    __OSModuleInfoList.pLast = 0;
    __OSModuleInfoList.pFirst = 0;
    __OSStringTable = 0;
}
