#include <stdio.h>
#include <stdlib.h>

/**
 *
 * @param command
 * @param block_size size of the initial buffer, will automatically expand twice the size of it if needed
 * @return read content (remember to free() it), if got any error, return NULL
 */
char *exec_command(const char *command, const unsigned int block_size)

{
    FILE *fp = NULL;
    fp = popen(command, "r");
    if (!fp)
        return NULL;
    // init cache buffer
    char *buf = (char *)malloc(block_size * sizeof(char));
    // init loop var
    int c;
    unsigned long cur = 0;
    unsigned long len = block_size;
    while ((c = fgetc(fp)) != EOF)
    {
        // should put to [cur], '\0' at len-1
        if (cur >= len - 1)
        {
            len += block_size;
            char *tmp = (char *)realloc(buf, len * sizeof(char));
            // handle alloc error
            if (tmp == NULL)
            {
                free(buf);
                return NULL;
            }
            else
            {
                buf = tmp;
            }
        }
        buf[cur++] = c;
    }
    buf[cur] = '\0';

    // handle stream error
    if (ferror(fp))
    {
        pclose(fp);
        free(buf);
        return NULL;
    }
    else
    {
        pclose(fp);
    }

    return buf;
}

// int main(void)
// {
//     printf("%s", exec_command("explorer http://nodejs.cn/download/", 1024));
//     printf("%s", exec_command("ls", 1024));
// }
