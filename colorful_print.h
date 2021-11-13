typedef struct
{
    char *text;       //  输出的文本,不会自带换行
    char *text_color; // 文本颜色，可选 black red green yellow blue purple sky_blue white
    char *bg_color;   // 文本背景，可选 black red green yellow blue purple sky_blue white
    int style;        // 文本风格，负数时正常，0为去除样式，1为加粗，2为文本变淡，3为斜体，4为下划线（最好英文文本使用），7为（文本与背景）反色，8为文本消失，9为删除线
} colorful_config;
void colorful_print(char *const text, char *text_color, char *bg_color, int style);
void colorful_print_struct(colorful_config config);