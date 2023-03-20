#ifndef _screen_h_
#define _screen_h_

#include "zf_common_headfile.h"
#include "common.h"

//========================TFT180 自定义全局变量========================//
extern tft180_dir_enum tft180_display_dir;
extern tft180_font_size_enum tft180_display_font;
extern uint8 tft180_x_max;
extern uint8 tft180_y_max;
//========================TFT180 自定义全局变量========================//

//========================TFT180 自定义基础函数========================//
void tft180_set_default_dir(tft180_dir_enum dir);
void tft180_set_default_font(tft180_font_size_enum font);
void tft180_set_default_color(uint16 pencolor, uint16 bgcolor);
void tft180_show_styled_char(uint16 x, uint16 y, const char dat, bool reverse, bool underline);
void tft180_show_styled_string(horizontal_align_enum string_align, uint16 offset, uint16 y, const char dat[], bool reverse, bool underline);
//========================TFT180 自定义基础函数========================//

#endif
