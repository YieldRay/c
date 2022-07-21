#include <stdio.h>
#include <stdlib.h>

char *exec_command(const char *command, const int char_length)
{
    FILE *fp = NULL;
    fp = popen(command, "r");
    if (!fp)
        return NULL;
    char *buf = (char *)malloc(sizeof(char) * char_length);
    for (int i = 0; i < char_length; i++)
        buf[i] = '\0';
    int ret = fread(buf, 1, char_length - 1, fp);
    pclose(fp);
    if (ret > 0)
        return buf;
    free(buf);
    return NULL;
}

// int main(void)
// {
//     printf("%s", exec_command("explorer http://nodejs.cn/download/", 100));
// }
