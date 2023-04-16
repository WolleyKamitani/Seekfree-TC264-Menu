#ifndef _common_h_
#define _common_h_

#include "zf_common_headfile.h"

//========================实用参数结构体========================//
typedef enum
{
    LEFT,
    CENTER,
    RIGHT,
} horizontal_align_enum;

typedef enum
{
    PREV,
    NEXT,
} navigation_enum;

typedef enum
{
    PLUS,
    MINUS,
} plus_minus_enum;
//========================实用参数结构体========================//

//========================格式化相关基础函数========================//
void format_int(char *format_res, int64 data, uint8 max_len);
void format_uint(char *format_res, uint64 data, uint8 max_len);
void format_float(char *format_res, double data, uint8 max_len);
//========================格式化相关基础函数========================//

#endif