#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Executes a command and reads its output into a dynamically allocated buffer.
 *
 * @param command The command to execute.
 * @return A pointer to the buffer containing the command output (remember to free() it). If an error occurs, returns NULL.
 */
char *exec_command(const char *command)
{
    const size_t block_size = 128;
    if (command == NULL)
    {
        return NULL;
    }

    FILE *fp = popen(command, "r");
    if (fp == NULL)
    {
        return NULL;
    }

    char *buf = (char *)malloc(block_size * sizeof(char));
    if (buf == NULL)
    {
        pclose(fp);
        return NULL;
    }

    size_t cur = 0;
    size_t len = block_size;
    char temp_buf[block_size]; // Temporary buffer for reading chunks

    while (fgets(temp_buf, sizeof(temp_buf), fp) != NULL)
    {
        size_t temp_len = strlen(temp_buf);
        if (cur + temp_len >= len)
        {
            len += block_size + temp_len;
            char *tmp = (char *)realloc(buf, len * sizeof(char));
            if (tmp == NULL)
            {
                free(buf);
                pclose(fp);
                return NULL;
            }
            buf = tmp;
        }
        strcpy(buf + cur, temp_buf);
        cur += temp_len;
    }

    if (ferror(fp))
    {
        free(buf);
        pclose(fp);
        return NULL;
    }

    pclose(fp);
    return buf;
}
