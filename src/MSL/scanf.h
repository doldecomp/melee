#ifndef _MSL_COMMON_SCANF_H
#define _MSL_COMMON_SCANF_H

#include <MSL/ansi_files.h>
#include <MSL/stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

enum __ReadProcActions {
    __GetAChar,
    __UngetAChar,
    __TestForError
};

enum __WReadProcActions {
    __GetAwChar,
    __UngetAwChar,
    __TestForwcsError
};

typedef struct {
    char* CharStr;
    size_t MaxCharCount;
    size_t CharsWritten;
} __OutStrCtrl;

typedef struct {
    char* NextChar;
    int NullCharDetected;
} __InStrCtrl;

typedef struct {
    wchar_t* wCharStr;
    size_t MaxCharCount;
    size_t CharsWritten;
} __wOutStrCtrl;

typedef struct {
    wchar_t* wNextChar;
    int wNullCharDetected;
} __wInStrCtrl;

#ifdef __cplusplus
}
#endif

#endif /* _MSL_COMMON_SCANF_H */
