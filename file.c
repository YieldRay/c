#include <stdio.h>

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

int file_get_contents(char *filename, char *receiver)
{
	FILE *fp;
	fp = fopen(filename, "r");
	if (!fp)
		return 0;
	char *ptr = receiver;
	while (!feof(fp))
	{
		*(ptr++) = fgetc(fp);
	}
	if (ferror(fp))
		return 0;
	return 1;
}