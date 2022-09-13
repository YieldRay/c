#include <stdio.h>
#include <stdlib.h>

/**
 * exec a command via popen(), it's synchronized
 * @param command
 * @param block_size
 * @return
 */
char *exec_command(const char *command, const unsigned int block_size)
{
    FILE *fp = NULL;
    fp = popen(command, "r");
    if (!fp)
        return NULL;
    // init cache block
    char *buf = (char *)malloc(block_size * sizeof(char));
    // start loop
    int c;
    unsigned long cur = 0;
    unsigned long len = block_size;
    while ((c = fgetc(fp)) != EOF)
    {
        // should put to [cur], '\0' at len-1
        if (cur >= len - 1)
        {
            len += block_size;
            buf = (char *)realloc(buf, len * sizeof(char));
            if (buf == NULL)
                return NULL;
        }
        buf[cur++] = c;
    }
    buf[cur] = '\0';

    if (ferror(fp))
    {
        free(buf);
        return NULL;
    }
    pclose(fp);

    return buf;
}

/*
int main(void)
{
    printf("%s", exec_command("explorer http://nodejs.cn/download/", 100));
    printf("%s", exec_command("ls", 100));
}
 */
