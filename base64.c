#include <stdlib.h>
#include <string.h>

// int main()
// {
//     puts(base64_encode("AAAAA"));  // => QUFBQUE=
// }

// ascii 1 byte = 8 bits
// binary per 6 bits offset by 2 bits(00) to form 1 byte
// then become an ascii character
// add '=' to the end of the ascii string for padding 2 bits

// ascii    char   base64
// 65-90    A-Z      0-25
// 97-122   a-z      26-51
// 48-51    0-9      52-61
// 43       +        62
// 37       /        63

char *base64_encode(const char *str)
{
    char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int len = strlen(str);
    int group = len % 3 == 0 ? len / 3 : len / 3 + 1;
    int outlen = group * 4;
    char *out = (char *)malloc(sizeof(char) * (outlen + 1));
    out[outlen] = '\0';
    int instep = 0;
    int outstep = 0;
    for (int i = 0; i < group; i++)
    {
        out[outstep++] = base64_table[(str[instep] >> 2)];
        out[outstep++] = base64_table[(str[instep] << 4 & 0b00110000) | (str[instep + 1] >> 4)];
        out[outstep++] = base64_table[(str[instep + 1] << 2 & 0b00111100) | (str[instep + 2] >> 6)];
        out[outstep++] = base64_table[(str[instep + 2] & 0b00111111)];
        instep += 3;
    }
    switch (len % 3)
    {
    case 2: // has 2 in 3, need 1 '='
        out[outlen - 1] = '=';
        break;
    case 1: // has 1 in 3, need 2 '='
        out[outstep - 1] = '=';
        out[outstep - 2] = '=';
        break;
    }

    return out;
}

char *base64_decode(const char *str)
{
    char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int len = strlen(str);
    int equal_count = 0; // 0 or 1 or 2
    for (int i = len - 1; i >= 0; i--)
    {
        if (str[i] == '=')
            equal_count++;
        else
            break;
    }
    int group = len / 4;
    int outlen = group * 3 - equal_count;
    char *out = (char *)malloc(sizeof(char) * (outlen + 1));
    int instep = 0;
    int outstep = 0;
    for (int i = 0; i < group; i++) // use strchr may cause low performance, but here is just for test
    {
        int a = strchr(base64_table, str[instep++]) - base64_table;
        int b = strchr(base64_table, str[instep++]) - base64_table;
        int c = strchr(base64_table, str[instep++]) - base64_table;
        int d = strchr(base64_table, str[instep++]) - base64_table;
        out[outstep++] = (a << 2 & 0b11111100) | (b >> 4 & 0b00000011);
        out[outstep++] = (b << 4 & 0b11110000) | (c >> 2 & 0b00001111);
        out[outstep++] = (c << 6 & 0b11000000) | (d & 0b00111111);
    }
    out[outlen] = '\0';
    return out;
}
