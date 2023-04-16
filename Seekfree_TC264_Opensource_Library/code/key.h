#ifndef _key_h_
#define _key_h_

#include "zf_common_headfile.h"
#include "menu.h"

#define KEY_NUMBER 4 // 按键数目
#define KEY_PINS                   \
    {                              \
        P22_0, P22_1, P22_2, P22_3 \
    } // 按键对应引脚

#define PRESS_THRESHOLD 10     // 按键消抖阈值
#define HOLD_THRESHOLD 300     // 按键长按阈值
#define INTERVAL_THRESHOLD 150 // 按键连按阈值

//========================按键结构体参数========================//
typedef struct
{
    uint8 value, last_value;         // 按键当前值 / 上一次值
    uint32 hold_time, interval_time; // 按键长按时间 / 按键连按时间
    uint32 click_count;              // 按键连按次数

    enum
    {
        RELEASE,   // 按键释放
        DITHER,    // 按键抖动
        PRE_CLICK, // 预双击键
        IN_CLICK,  // 已双击键
        PRESS,     // 按键按下
        HOLD,      // 按键长按
        MULTI,     // 按键连按
    } state;       // 按键状态

    bool is_press; // 按键是否按下
    bool is_hold;  // 按键是否长按
    bool is_multi; // 按键是否连按
} key_struct;
//========================按键结构体参数========================//

//========================按键基础函数========================//
void key_handler(void);
void key_action(void);
void key_list_init(uint8 pit_timer);
//========================按键基础函数========================//

#endif