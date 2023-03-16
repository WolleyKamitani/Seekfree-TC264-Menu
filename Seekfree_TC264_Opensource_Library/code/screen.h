#ifndef _screen_h_
#define _screen_h_

#include "zf_common_headfile.h"

//========================TFT180 �Զ�������ṹ��========================//
typedef enum
{
    STRING_LEFT,   // �ַ���������ʾ
    STRING_CENTER, // �ַ���������ʾ
    STRING_RIGHT,  // �ַ���������ʾ
} tft180_string_pos_enum;
//========================TFT180 �Զ�������ṹ��========================//

//========================TFT180 �Զ��庯��========================//
uint16 tft180_char_pixel_width(void);
uint16 tft180_char_pixel_height(void);
void tft180_set_default_dir(tft180_dir_enum dir);
void tft180_set_default_font(tft180_font_size_enum font);
void tft180_set_default_color(uint16 pencolor, uint16 bgcolor);
void tft180_show_styled_char(uint16 x, uint16 y, const char dat, bool reverse, bool underline);
void tft180_show_styled_string(tft180_string_pos_enum string_pos, uint16 offset, uint16 y, const char dat[], bool reverse, bool underline);
//========================TFT180 �Զ��庯��========================//

#endif
