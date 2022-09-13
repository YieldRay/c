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
 * @return read content (remember to free() it), if got any error, return NULL
 */
char *file_get_contents(const char *filename, const unsigned int block_size)
{
	FILE *fp = NULL;
	fp = fopen(filename, "r");
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
		fclose(fp);
		free(buf);
		return NULL;
	}
	else
	{
		fclose(fp);
	}

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