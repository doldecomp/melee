#include "stdlib.h"

/// Widechar to multibyte string conversion,
/// doesn't care about proper conversion though?
size_t wcstombs(char* dest, const wchar_t* src, size_t max)
{
    size_t i;
    wchar_t c;

    for (i = 0; i < max; i++) {
        c = *src++;
        *dest++ = (char) c;
        if ((char) c == '\0') {
            break;
        }
    }
    return i;
}
