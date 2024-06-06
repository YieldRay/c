#include <stdlib.h>
#include <string.h>

#ifndef __cplusplus
typedef enum bool
{
    false,
    true
} bool;
#endif

bool is_windows()
{
    const char *os = getenv("OS");
    if (os != NULL)
        if (strcmp(os, "Windows_NT") == 0)
            return true;
    return false;
}
