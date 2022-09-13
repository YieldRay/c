#include <stdio.h>
#include <stdlib.h>

/**
 *
 * @param filename
 * @param input
 * @return 1: success 0: fail
 */
int file_put_contents(const char *filename, const char *input)
{
	FILE *fp;
	fp = fopen(filename, "w");
	if (!fp)
		return 0;
	int result = fputs(input, fp);
	if (ferror(fp))
		return 0;
	fclose(fp);
	return 1;
}

/**
 *
 * @param filename
 * @param block_size size of the initial buffer, will automatically expand twice the size of it if needed
 * @return read content, if got any error, return NULL
 */
char *file_get_contents(const char *filename, const unsigned int block_size)
{
	FILE *fp = NULL;
	fp = fopen(filename, "r");
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
int main()
{
	char *receiver = file_get_contents("file.c", 1024);
	system("CHCP 65001");
	printf(receiver);
}
 */