#include <stdio.h>
#define MAX_SIZE 65536
void file_put_contents(char *filename, char *str)
{
    FILE *fp;
    fp = fopen(filename, "w");
    fputs(str, fp);
    fclose(fp);
}

void file_get_contents(char *filename, char *receiver)
{
    FILE *fp;
    char contents[MAX_SIZE];
    fp = fopen(filename, "r");
    int i = 0;
    while (!feof(fp))
    {
        contents[i++] = fgetc(fp);
    }
    contents[i - 1] = '\0';
    strcpy(receiver, contents);
}