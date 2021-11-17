#include <stdio.h>
#include <string.h>
#define MAX_SIZE 65536

/* 向filename覆盖写入str */
int file_put_contents(char *filename, char *str) {

	FILE *fp;

	fp = fopen(filename, "w");

	if (!fp)
		return 0;

	fputs(str, fp);

	if (ferror(fp))
		return 0;

	fclose(fp);

	return 1;
}

/* 把filename的所有文本读入receiver，注意receiver应该足够大 */
int file_get_contents(char *filename, char *receiver) {
	FILE *fp;

	fp = fopen(filename, "r");

	if (!fp)
		return 0;

	char contents[MAX_SIZE] = {'\0'};

	int i = 0;

	while (!feof(fp)) {
		contents[i++] = fgetc(fp);
	}

	if (ferror(fp))
		return 0;

	strcpy(receiver, contents);

	return 1;
}