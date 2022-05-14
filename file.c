#include <stdio.h>
#include <stdlib.h>

// 1 for success, 0 for failure 测试

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

char *file_get_contents(const char *filename, long *read_size)
{
	if (read_size != NULL)
		*read_size = 0;

	FILE *fp = fopen(filename, "r");
	if (!fp)
		return NULL;

	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char *buffer = (char *)malloc(size + 1);
	buffer[size] = '\0';

	long i;
	for (i = 0; i < size; i++)
	{
		buffer[i] = fgetc(fp);
		if (feof(fp))
		{
			break;
		}
	}
	buffer[i] = '\0';

	if (read_size != NULL)
		*read_size = i;

	if (ferror(fp))
	{
		free(buffer);
		return NULL;
	}

	fclose(fp);
	return buffer;
}

// int main()
// {
// 	long *len = malloc(sizeof(int));
// 	char *receiver = file_get_contents("file.c", len);
// 	system("CHCP 65001");
// 	printf(receiver);
// 	printf("\n%d", *len);
// }