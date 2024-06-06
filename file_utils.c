#include <stdio.h>
#include <stdlib.h>

/**
 * Writes the input string to a file.
 *
 * @param filename The name of the file.
 * @param input The string to write to the file.
 * @return 0 on success, otherwise failure.
 */
int file_put_contents(const char *filename, const char *input)
{
	FILE *fp = fopen(filename, "w");

	if (!fp)
		return 1;

	if (fputs(input, fp) == EOF)
	{
		fclose(fp);
		return 2;
	}

	if (fclose(fp) == EOF)
		return 3;

	return 0;
}

/**
 * Reads the entire content of a file into a dynamically allocated buffer.
 *
 * @param filename The name of the file.
 * @return A pointer to the buffer containing the file content (remember to free() it). If an error occurs, returns NULL.
 */
char *file_get_contents(const char *filename)
{
	const size_t block_size = 128;
	FILE *fp = fopen(filename, "r");
	if (!fp)
		return NULL;

	// Initialize the buffer
	char *buf = (char *)malloc(block_size * sizeof(char));
	if (buf == NULL)
	{
		fclose(fp);
		return NULL;
	}

	// Initialize loop variables
	int c;
	size_t cur = 0;
	size_t len = block_size;

	// Read the file content
	while ((c = fgetc(fp)) != EOF)
	{
		// Resize the buffer if needed
		if (cur >= len - 1)
		{
			len += block_size;
			char *tmp = (char *)realloc(buf, len * sizeof(char));
			if (tmp == NULL)
			{
				free(buf);
				fclose(fp);
				return NULL;
			}
			buf = tmp;
		}
		buf[cur++] = (char)c;
	}
	buf[cur] = '\0';

	// Handle stream error
	if (ferror(fp))
	{
		free(buf);
		fclose(fp);
		return NULL;
	}

	fclose(fp);
	return buf;
}
