#include <stdio.h>
#include <string.h>

/* 向filename覆盖写入str */
int file_put_contents(char *filename, char *input)
{
	FILE *fp;
	fp = fopen(filename, "w");
	if (!fp)
		return 0;
	fputs(input, fp);
	if (ferror(fp))
		return 0;
	fclose(fp);
	return 1;
}

/* 把filename的所有文本读入receiver，注意receiver应该足够大，防止溢出 */
int file_get_contents(char *filename, char *receiver)
{
	FILE *fp;
	fp = fopen(filename, "r");
	if (!fp)
		return 0;
	int i = 0;
	while (!feof(fp))
	{
		receiver[i++] = fgetc(fp);
	}
	if (ferror(fp))
		return 0;
	return 1;
}