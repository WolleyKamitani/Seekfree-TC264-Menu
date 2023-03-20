#include "common.h"

/**
 * @brief 格式化浮点数为科学计数法
 *
 * @param format_res 格式化结果
 * @param data 待格式化数据
 * @param max_len 字符串最大长度
 */
void format_exp(char *format_res, double data, uint8 max_len)
{
    uint8 exp = 0;
    while (data >= 10 || data <= -10)
    {
        data /= 10;
        exp++;
    }

    sprintf(format_res, "%.*fe%d",
            max_len - (data >= 0 ? 4 : 5) - (int)log10(exp),
            data, exp);
}

/**
 * @brief 格式化整数为字符串
 *
 * @param format_res 格式化结果
 * @param data 待格式化数据
 * @param max_len 字符串最大长度
 */
void format_int(char *format_res, int64 data, uint8 max_len)
{
    char buf[24];
    sprintf(buf, "%lld", data);

    if (strlen(buf) > max_len)
    {
        format_exp(buf, (double)data, max_len);
    }

    strcpy(format_res, buf);
}

/**
 * @brief 格式化无符号整数为字符串
 *
 * @param format_res 格式化结果
 * @param data 待格式化数据
 * @param max_len 字符串最大长度
 */
void format_uint(char *format_res, uint64 data, uint8 max_len)
{
    char buf[24];
    sprintf(buf, "%llu", data);

    if (strlen(buf) > max_len)
    {
        format_exp(buf, (double)data, max_len);
    }

    strcpy(format_res, buf);
}

/**
 * @brief 格式化浮点数为字符串
 *
 * @param format_res 格式化结果
 * @param data 待格式化数据
 * @param max_len 字符串最大长度
 */
void format_float(char *format_res, double data, uint8 max_len)
{
    char buf[24];
    sprintf(buf, "%.2f", data);

    if (strlen(buf) > max_len)
    {
        format_exp(buf, data, max_len);
    }

    strcpy(format_res, buf);
}