/**
 * �»��߿�ͷ�ı�������Ϊ�ڲ�ʹ��
 * �����������Ҫʹ��
 *  ʾ����
#include "./colorful_print.h"
int main()
{
   colorful_print("here is some text\n", "sky_blue", "purple", -1);
   colorful_config config = {"text in struct",
                             "sky_blue",
                             "yellow",
                             -1};
   colorful_print_struct(config);
}
*/
#include <stdio.h>
#include <string.h>

typedef struct
{
   char *text;       //  ������ı�,�����Դ�����
   char *text_color; // �ı���ɫ����ѡ black red green yellow blue purple sky_blue white
   char *bg_color;   // �ı���������ѡ black red green yellow blue purple sky_blue white
   int style;        // �ı���񣬸���ʱ������0Ϊȥ����ʽ��1Ϊ�Ӵ֣�2Ϊ�ı��䵭��3Ϊб�壬4Ϊ�»��ߣ����Ӣ���ı�ʹ�ã���7Ϊ���ı��뱳������ɫ��8Ϊ�ı���ʧ��9Ϊɾ����
} colorful_config;

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
   if (strcmp(color, "purple") == 0)
      return 45;
   if (strcmp(color, "sky_blue") == 0)
      return 46;
   if (strcmp(color, "white") == 0)
      return 47;
   if (strcmp(color, "transparent") == 0)
      return 49;
   // default
   return 49;
}

int _colorful_get_text(char *color)
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
   if (strcmp(color, "purple") == 0)
      return 35;
   if (strcmp(color, "sky_blue") == 0)
      return 36;
   if (strcmp(color, "white") == 0)
      return 37;
   if (strcmp(color, "less_white") == 0)
      return 39;
   // default
   return 37;
}

void _colorful_print(char *const text, int text_color, int bg_color, int style)
{
   if (style >= 0)
      printf("\033\[%d;%d;%dm%s\033\[0m", bg_color, text_color, style, text);
   else
      printf("\033\[%d;%dm%s\033\[0m", bg_color, text_color, text);
}

void colorful_print(char *const text, char *text_color, char *bg_color, int style)
{
   int code_text_color = _colorful_get_text(text_color);
   int code_bg_color = _colorful_get_bg(bg_color);
   _colorful_print(text, code_text_color, code_bg_color, style);
}

void colorful_print_struct(colorful_config config)
{
   colorful_print(config.text, config.text_color, config.bg_color, config.style);
}
