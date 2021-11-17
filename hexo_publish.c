/* NOTICE:
 * This script shoud be run at the ./_posts path
 * gcc hexo_publish.c -o "$hexo_publish"
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

int is_windows()
{
    char *os = getenv("OS");
    if (os != NULL)
    {
        if (strcmp(os, "Windows_NT") == 0)
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
    setlocale(LC_TIME, "zh_CN.UTF-8");
    time_t t = time(NULL);
    char *time_str = asctime(localtime(&t));
    time_str[strlen(time_str) - 1] = '\0'; // delete \n in the end
    const char *os = getenv("OS");
    char os_str[63] = "Current OS: ";
    char cmd[255] = "cd ../../ && git add . && ";
    strcat(cmd, "git commit -m 'Update at ");
    strcat(cmd, time_str);
    strcat(cmd, "' && git push");
    puts(strcat(os_str, os));
    puts("The following command will be executed: ");
    puts(cmd);
    putchar('\n');
    system(cmd);
    if (is_windows())
    {
        system("pause"); // for windows
    }
    return 0;
}
