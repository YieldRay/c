/**
 * Convert .cmd .bat .sh to executive program (execute line by line, so multi-line command is not supported)
 * Make sure you have gcc installed as the program run gcc to build the executive program
 * 
 * Build The Converter Program
 * gcc convert.c -o convert
 * 
 * Run The Program
 * ./convert scriptName.bat programName
 * or
 * ./convert
 * scriptName.bat programName
 */
#define MAX_SINGLE_LINE 127
#define MAX_TOTAL_LINE 255
#define MAX_TOTAL_CODE 4095
#define TEMP_FILE_NAME "tmepScriptConvertCode.c"
#define DELETE_TEMP_FILE 0
#define WINDOWS_PAUSE 1
#define RUN_GENERATED_PROGRAM 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_windows();
void file_put_contents(char *filename, char *str);
void gcc_build_source_code(char *input, char *output);
void generate_program_code(char *code_receiver, int argc, char cmd[argc][MAX_SINGLE_LINE]);

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        puts("Usage:  ./convert scriptName.bat programName");
        if (argc != 1)
            exit(0);
    }
    char input[MAX_SINGLE_LINE], output[MAX_SINGLE_LINE];
    if (argc == 1)
    {
        scanf("%s %s", input, output);
    }
    else
    {
        strcpy(input, argv[1]);
        strcpy(output, argv[2]);
    }
    FILE *fp;
    fp = fopen(input, "r");
    if (fp == NULL)
    {
        puts("Error:  Please make sure the program has promission (chmod)");
        exit(0);
    }
    char lines[MAX_TOTAL_LINE][MAX_SINGLE_LINE];
    int i = 0;
    while (!feof(fp))
    {
        fscanf(fp, "%[^\n]", lines[i]); // read the file line by line
        i++;                            // i - total lines
        if (fgetc(fp) != '\n')
        {
            break;
        }
    }

    char source_code[MAX_TOTAL_CODE];
    generate_program_code(source_code, i, lines);
    file_put_contents(TEMP_FILE_NAME, source_code);
    gcc_build_source_code(TEMP_FILE_NAME, output);
    if (DELETE_TEMP_FILE)
    {
        if (remove(TEMP_FILE_NAME) == 0)
        {
            puts("Notice:  Temp code has beem removed");
        }
        else
        {
            puts("Error:  Fail to remove temp file");
        }
    }
    if (RUN_GENERATED_PROGRAM)
    {
        printf("Run Program:  %s\n\n", output);
        if (is_windows())
            system(output);
        else
        {
            if (output[0] == '.' || output[0] == '/' || output[1] == '/' || output[1] == '.')
            {
                system(output);
            }
            else
            {
                char output_path[MAX_SINGLE_LINE] = "./";
                strcat(output_path, output);
                system(output_path);
            }
        }
    }

    return 0;
}

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
    char contents[MAX_TOTAL_CODE];
    fp = fopen(filename, "r");
    int i = 0;
    while (!feof(fp))
    {
        contents[i++] = fgetc(fp);
    }
    contents[i - 1] = '\0';
    strcpy(receiver, contents);
}

void gcc_build_source_code(char *input, char *output)
{
    char cmd[MAX_SINGLE_LINE] = "gcc ";
    strcat(cmd, input);
    strcat(cmd, " -o ");
    strcat(cmd, output);
    system(cmd);
}

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
/**
 * generate program code by the command list, execute the listed command line by line
 */
void generate_program_code(char *code_receiver, int argc, char cmd[argc][MAX_SINGLE_LINE])
{
    char source_code[MAX_TOTAL_CODE] = "#include <stdlib.h>\nint main(){\n";
    for (int i = 0; i < argc; i++)
    {
        char line[MAX_SINGLE_LINE] = "    system(\""; //system() the command line by line
        strcat(line, cmd[i]);
        strcat(line, "\");\n");    // insert each line to system("");
        strcat(source_code, line); // append every system(command)
    }
    if (WINDOWS_PAUSE && is_windows())
    { // if allow, in windows system, "pause" command will be executed in the end
        strcat(source_code, "system(\"pause\");");
    }
    strcat(source_code, "}");
    strcpy(code_receiver, source_code);
}