#include "screen.h"

static uint16 tft180_pencolor = TFT180_DEFAULT_PENCOLOR;
static uint16 tft180_bgcolor = TFT180_DEFAULT_BGCOLOR;

static tft180_dir_enum tft180_display_dir = TFT180_DEFAULT_DISPLAY_DIR;
static tft180_font_size_enum tft180_display_font = TFT180_DEFAULT_DISPLAY_FONT;

static uint8 tft180_x_max = 128;
static uint8 tft180_y_max = 160;

/**
 * @brief TFT180 获取字符宽度
 *
 * @return uint16 字符宽度
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
 * @brief TFT180 获取字符高度
 *
 * @return uint16 字符高度
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
 * @brief 设置默认显示方向
 *
 * @param dir 显示方向 参照 zf_device_tft180.h 内 tft180_dir_enum 枚举体定义
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
 * @brief 设置默认显示字体
 *
 * @param font 显示字体 参照 zf_device_tft180.h 内 tft180_font_size_enum 枚举体定义
 */
void tft180_set_default_font(tft180_font_size_enum font)
{
    tft180_display_font = font;
    tft180_set_font(font);
}

/**
 * @brief 设置默认显示颜色
 *
 * @param pencolor 颜色格式 RGB565 或者可以使用 zf_common_font.h 内常用颜色宏定义
 * @param bgcolor 颜色格式 RGB565 或者可以使用 zf_common_font.h 内常用颜色宏定义
 */
void tft180_set_default_color(uint16 pencolor, uint16 bgcolor)
{
    tft180_pencolor = pencolor;
    tft180_bgcolor = bgcolor;
    tft180_set_color(pencolor, bgcolor);
}

/**
 * @brief TFT180 显示特殊样式字符
 *
 * @param x 坐标 x 方向的起点 参数范围 [0, tft180_x_max-1]
 * @param y 坐标 y 方向的起点 参数范围 [0, tft180_y_max-1]
 * @param dat 需要显示的字符
 * @param reverse 是否反色显示
 * @param underline 是否显示下划线
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
 * @brief TFT180 显示特殊样式字符串
 *
 * @param string_pos 字符串显示位置 参照 screen.h 内 tft180_string_pos_enum 枚举体定义
 * @param offset 坐标 x 方向的偏移量 当 string_pos 为 STRING_LEFT 时偏移量向左
 * @param y 坐标 y 方向的起点 参数范围 [0, tft180_y_max-1]
 * @param dat 需要显示的字符串
 * @param reverse 是否反色显示
 * @param underline 是否显示下划线
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

    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < tft180_x_max);
    zf_assert(y < tft180_y_max);

    uint16 j = 0;
    while (dat[j] != '\0')
    {
        tft180_show_styled_char(x + tft180_char_pixel_width() * j, y, dat[j], reverse, underline);
        j++;
    }
}
