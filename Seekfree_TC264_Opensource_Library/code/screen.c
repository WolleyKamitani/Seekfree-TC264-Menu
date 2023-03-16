#include "screen.h"

static uint16 tft180_pencolor = TFT180_DEFAULT_PENCOLOR;
static uint16 tft180_bgcolor = TFT180_DEFAULT_BGCOLOR;

static tft180_dir_enum tft180_display_dir = TFT180_DEFAULT_DISPLAY_DIR;
static tft180_font_size_enum tft180_display_font = TFT180_DEFAULT_DISPLAY_FONT;

static uint8 tft180_x_max = 128;
static uint8 tft180_y_max = 160;

/**
 * @brief TFT180 ��ȡ�ַ����
 *
 * @return uint16 �ַ����
 */
uint16 tft180_char_pixel_width(void)
{
    switch (tft180_display_font)
    {
    case TFT180_6X8_FONT:
        return 6;
    case TFT180_8X16_FONT:
        return 8;
    case TFT180_16X16_FONT:
        return 16;
    default:
        return 0;
    }
}

/**
 * @brief TFT180 ��ȡ�ַ��߶�
 *
 * @return uint16 �ַ��߶�
 */
uint16 tft180_char_pixel_height(void)
{
    switch (tft180_display_font)
    {
    case TFT180_6X8_FONT:
        return 8;
    case TFT180_8X16_FONT:
        return 16;
    case TFT180_16X16_FONT:
        return 16;
    default:
        return 0;
    }
}

/**
 * @brief ����Ĭ����ʾ����
 *
 * @param dir ��ʾ���� ���� zf_device_tft180.h �� tft180_dir_enum ö���嶨��
 */
void tft180_set_default_dir(tft180_dir_enum dir)
{
    tft180_display_dir = dir;
    if (dir < 2)
    {
        tft180_x_max = 128;
        tft180_y_max = 160;
    }
    else
    {
        tft180_x_max = 160;
        tft180_y_max = 128;
    }
    tft180_set_dir(dir);
}

/**
 * @brief ����Ĭ����ʾ����
 *
 * @param font ��ʾ���� ���� zf_device_tft180.h �� tft180_font_size_enum ö���嶨��
 */
void tft180_set_default_font(tft180_font_size_enum font)
{
    tft180_display_font = font;
    tft180_set_font(font);
}

/**
 * @brief ����Ĭ����ʾ��ɫ
 *
 * @param pencolor ��ɫ��ʽ RGB565 ���߿���ʹ�� zf_common_font.h �ڳ�����ɫ�궨��
 * @param bgcolor ��ɫ��ʽ RGB565 ���߿���ʹ�� zf_common_font.h �ڳ�����ɫ�궨��
 */
void tft180_set_default_color(uint16 pencolor, uint16 bgcolor)
{
    tft180_pencolor = pencolor;
    tft180_bgcolor = bgcolor;
    tft180_set_color(pencolor, bgcolor);
}

/**
 * @brief TFT180 ��ʾ������ʽ�ַ�
 *
 * @param x ���� x �������� ������Χ [0, tft180_x_max-1]
 * @param y ���� y �������� ������Χ [0, tft180_y_max-1]
 * @param dat ��Ҫ��ʾ���ַ�
 * @param reverse �Ƿ�ɫ��ʾ
 * @param underline �Ƿ���ʾ�»���
 */
void tft180_show_styled_char(uint16 x, uint16 y, const char dat, bool reverse, bool underline)
{
    if (reverse)
    {
        tft180_set_color(tft180_bgcolor, tft180_pencolor);
    }

    tft180_show_char(x, y, dat);
    tft180_set_color(tft180_pencolor, tft180_bgcolor);

    if (underline)
    {
        tft180_draw_line(x,
                         y + tft180_char_pixel_height(),
                         x + tft180_char_pixel_width(),
                         y + tft180_char_pixel_height(),
                         tft180_pencolor);
    }
}

/**
 * @brief TFT180 ��ʾ������ʽ�ַ���
 *
 * @param string_pos �ַ�����ʾλ�� ���� screen.h �� tft180_string_pos_enum ö���嶨��
 * @param offset ���� x �����ƫ���� �� string_pos Ϊ STRING_LEFT ʱƫ��������
 * @param y ���� y �������� ������Χ [0, tft180_y_max-1]
 * @param dat ��Ҫ��ʾ���ַ���
 * @param reverse �Ƿ�ɫ��ʾ
 * @param underline �Ƿ���ʾ�»���
 */
void tft180_show_styled_string(tft180_string_pos_enum string_pos, uint16 offset, uint16 y, const char dat[], bool reverse, bool underline)
{
    uint16 x;
    switch (string_pos)
    {
    case STRING_LEFT:
        x = offset;
        break;
    case STRING_CENTER:
        x = (tft180_x_max - 1 - strlen(dat) * tft180_char_pixel_width()) / 2 + offset;
        break;
    case STRING_RIGHT:
        x = tft180_x_max - 1 - strlen(dat) * tft180_char_pixel_width() - offset;
        break;
    }

    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x < tft180_x_max);
    zf_assert(y < tft180_y_max);

    uint16 j = 0;
    while (dat[j] != '\0')
    {
        tft180_show_styled_char(x + tft180_char_pixel_width() * j, y, dat[j], reverse, underline);
        j++;
    }
}
