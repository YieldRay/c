#include <stdlib.h>
#include <string.h>

int is_windows()
{
    const char *os = getenv("OS");
    if (os != NULL)
        if (strcmp(os, "Windows_NT") == 0)
            return 1;
    return 0;
}
