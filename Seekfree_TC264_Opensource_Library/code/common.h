#ifndef _common_h_
#define _common_h_

#include "zf_common_headfile.h"

//========================ʵ�ò����ṹ��========================//
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
//========================ʵ�ò����ṹ��========================//

//========================��ʽ����ػ�������========================//
void format_int(char *format_res, int64 data, uint8 max_len);
void format_uint(char *format_res, uint64 data, uint8 max_len);
void format_float(char *format_res, double data, uint8 max_len);
//========================��ʽ����ػ�������========================//

#endif