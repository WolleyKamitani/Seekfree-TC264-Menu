#include "common.h"

/**
 * @brief ��ʽ��������Ϊ��ѧ������
 *
 * @param format_res ��ʽ�����
 * @param data ����ʽ������
 * @param max_len �ַ�����󳤶�
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
 * @brief ��ʽ������Ϊ�ַ���
 *
 * @param format_res ��ʽ�����
 * @param data ����ʽ������
 * @param max_len �ַ�����󳤶�
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
 * @brief ��ʽ���޷�������Ϊ�ַ���
 *
 * @param format_res ��ʽ�����
 * @param data ����ʽ������
 * @param max_len �ַ�����󳤶�
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
 * @brief ��ʽ��������Ϊ�ַ���
 *
 * @param format_res ��ʽ�����
 * @param data ����ʽ������
 * @param max_len �ַ�����󳤶�
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