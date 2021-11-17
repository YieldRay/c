/**
 * 下划线开头的变量或函数为内部使用
 * 非特殊情况不要使用
 *  示例：

#include "./colorful_print.h"
int main()
{
   colorful_print("here is some text\n", "cyan", "magenta", -1);

   // OR

   colorful_config config = {.text="text in struct", .text_color="cyan", .bg_color="yellow", style=-1};
   colorful_print_struct(config);
}

*/
#include <stdio.h>
#include <string.h>
#include <windows.h>

typedef struct
{
	char *text;		  //  输出的文本,不会自带换行
	char *text_color; // 文本颜色，可选 black red green yellow blue magenta cyan white
	char *bg_color;	  // 文本背景，可选 black red green yellow blue magenta cyan white
	int style;		  // 文本风格(Windows下未实现)，负数时正常，0为去除样式，1为加粗，2为文本变淡，3为斜体，4为下划线（最好英文文本使用），7为（文本与背景）反色，8为文本消失，9为删除线
} colorful_config;

int colorful_is_windows()
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

int _colorful_get_bg(char *color)
{
	if (strcmp(color, "black") == 0)
		return 40;
	if (strcmp(color, "red") == 0)
		return 41;
	if (strcmp(color, "green") == 0)
		return 42;
	if (strcmp(color, "yellow") == 0)
		return 43;
	if (strcmp(color, "blue") == 0)
		return 44;
	if (strcmp(color, "magenta") == 0)
		return 45;
	if (strcmp(color, "cyan") == 0)
		return 46;
	if (strcmp(color, "white") == 0)
		return 47;
	if (strcmp(color, "transparent") == 0)
		return 49;
	// default
	return 49;
}

int colorful_colorful_get_text(char *color)
{
	if (strcmp(color, "black") == 0)
		return 30;
	if (strcmp(color, "red") == 0)
		return 31;
	if (strcmp(color, "green") == 0)
		return 32;
	if (strcmp(color, "yellow") == 0)
		return 33;
	if (strcmp(color, "blue") == 0)
		return 34;
	if (strcmp(color, "magenta") == 0)
		return 35;
	if (strcmp(color, "cyan") == 0)
		return 36;
	if (strcmp(color, "white") == 0)
		return 37;
	if (strcmp(color, "less_white") == 0)
		return 39;
	// default
	return 37;
}

int _colorful_get_text_windows(char *color)
{
	if (strcmp(color, "black") == 0)
		return 0;
	if (strcmp(color, "red") == 0)
		return 4;
	if (strcmp(color, "green") == 0)
		return 2;
	if (strcmp(color, "yellow") == 0)
		return 6;
	if (strcmp(color, "blue") == 0)
		return 1;
	if (strcmp(color, "magenta") == 0)
		return 5;
	if (strcmp(color, "cyan") == 0)
		return 3;
	if (strcmp(color, "white") == 0)
		return 7;
	if (strcmp(color, "less_white") == 0)
		return 8;
	// default
	return 7;
}

int _colorful_get_bg_windows(char *color)
{
	if (strcmp(color, "black") == 0)
		return 0;
	if (strcmp(color, "red") == 0)
		return BACKGROUND_RED;
	if (strcmp(color, "green") == 0)
		return BACKGROUND_GREEN;
	if (strcmp(color, "yellow") == 0)
		return 0x60;
	if (strcmp(color, "blue") == 0)
		return BACKGROUND_BLUE;
	if (strcmp(color, "magenta") == 0)
		return 0x50;
	if (strcmp(color, "cyan") == 0)
		return 0x30;
	if (strcmp(color, "white") == 0)
		return 0x70;
	if (strcmp(color, "grey") == 0)
		return 0x80;
	// default
	return 0;
}

void colorful_print(char *const text, char *text_color, char *bg_color, int style)
{

	if (colorful_is_windows())
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _colorful_get_text_windows(text_color) | _colorful_get_bg_windows(bg_color));
		printf(text);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	else
	{
		int code_text_color = _colorful_get_text(text_color);
		int code_bg_color = _colorful_get_bg(bg_color);
		if (style >= 0)
			printf("\033\[%d;%d;%dm%s\033\[0m", bg_color, text_color, style, text);
		else
			printf("\033\[%d;%dm%s\033\[0m", bg_color, text_color, text);
	}
}

void colorful_print_struct(colorful_config config)
{
	colorful_print(config.text, config.text_color, config.bg_color, config.style);
}
