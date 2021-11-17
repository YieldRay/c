typedef struct
{
	char *text;		  //  输出的文本
	char *text_color; // 文本颜色
	char *bg_color;	  // 文本背景
	int style;		  // 文本风格
} colorful_config;

void colorful_print(char *const text, char *text_color, char *bg_color, int style);
void colorful_print_struct(colorful_config config);