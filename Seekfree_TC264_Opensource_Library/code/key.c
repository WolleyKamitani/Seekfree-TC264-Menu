#include "key.h"

static key_struct key_list[KEY_NUMBER];               // 按键列表
static gpio_pin_enum key_pins[KEY_NUMBER] = KEY_PINS; // 按键对应引脚
static uint8 timer = 0;                               // 按键扫描间隔

/**
 * @brief 按键状态检测
 *
 */
void key_handler(void)
{
    // 遍历按键列表
    for (uint8 i = 0; i < KEY_NUMBER; i++)
    {
        // 更新按键状态
        key_list[i].value = !gpio_get_level(key_pins[i]); // 获取当前按键状态（翻转，因为低电平表示按下）
        key_list[i].last_value = key_list[i].value;       // 存储当前按键状态

        // 按键松开时，长按计时清零
        if (!key_list[i].value && key_list[i].state != DITHER && key_list[i].state != HOLD)
        {
            key_list[i].hold_time = 0;
        }

        // 按键持续按下时，长按计时累加
        if (key_list[i].value && key_list[i].last_value)
        {
            key_list[i].hold_time += timer;
        }

        // 当按键处于 PRE_CLICK 或 IN_CLICK 状态时，间隔计时累加
        if (key_list[i].state == PRE_CLICK || key_list[i].state == IN_CLICK)
        {
            key_list[i].interval_time += timer;
        }
        else
        {
            key_list[i].interval_time = 0;
        }

        // 按键状态机
        switch (key_list[i].state)
        {
        case RELEASE:
            // 清除按键状态
            key_list[i].is_press = FALSE;
            key_list[i].is_hold = FALSE;
            key_list[i].is_multi = FALSE;
            key_list[i].click_count = 0;

            // 如果此时按钮仍处于按下状态，则进入 DITHER 状态
            if (key_list[i].value)
            {
                key_list[i].state = DITHER;
            }

            break;
        case DITHER:
            // 如果按键持续时间超过阈值，进入 HOLD 状态
            if (key_list[i].hold_time > HOLD_THRESHOLD)
            {
                key_list[i].state = HOLD;
            }

            // 如果按键释放且按下时间大于 PRESS_THRESHOLD 且小于 HOLD_THRESHOLD，则进入 PRE_CLICK 状态并增加点击次数
            if (!key_list[i].value)
            {
                if (key_list[i].hold_time > PRESS_THRESHOLD && key_list[i].hold_time < HOLD_THRESHOLD)
                {
                    key_list[i].state = PRE_CLICK;
                    key_list[i].click_count++;
                }
                else
                {
                    key_list[i].state = RELEASE;
                }
            }

            break;
        case PRE_CLICK:
            // 如果按键间隔时间小于阈值且按键按下时间大于 PRESS_THRESHOLD，则进入 MULTI 状态并增加点击次数
            if (key_list[i].interval_time < INTERVAL_THRESHOLD)
            {
                if (key_list[i].hold_time > PRESS_THRESHOLD)
                {
                    key_list[i].state = MULTI;
                    key_list[i].click_count++;
                }
                break;
            }

            // 否则，进入 PRESS 状态
            key_list[i].state = PRESS;
            break;
        case IN_CLICK:
            // 如果按键间隔时间小于阈值且按键按下时间大于 PRESS_THRESHOLD，则进入 MULTI 状态并增加点击次数
            if (key_list[i].interval_time < INTERVAL_THRESHOLD)
            {
                if (key_list[i].hold_time > PRESS_THRESHOLD)
                {
                    key_list[i].state = MULTI;
                    key_list[i].click_count++;
                }
            }
            else
            {
                // 如果按键间隔时间超过阈值，设置 is_multi 为真，并返回 RELEASE 状态
                key_list[i].is_multi = TRUE;
                key_list[i].state = RELEASE;
            }

            break;
        case PRESS:
            // 设置 is_press 为真
            key_list[i].is_press = TRUE;

            // 如果按键释放，进入 RELEASE 状态
            if (!key_list[i].value)
            {
                key_list[i].state = RELEASE;
            }

            break;
        case HOLD:
            // 当按键释放时，设置 is_hold 为真，并返回 RELEASE 状态
            if (!key_list[i].value)
            {
                key_list[i].is_hold = TRUE;
                key_list[i].state = RELEASE;
            }

            break;
        case MULTI:
            // 如果按键释放，进入 IN_CLICK 状态
            if (!key_list[i].value)
            {
                key_list[i].state = IN_CLICK;
            }

            break;
        }
    }

    // 执行按键动作
    key_action();
}

/**
 * @brief 按键执行动作
 *        使用时根据需要自行修改
 *
 */
void key_action(void)
{
    for (uint8 i = 0; i < KEY_NUMBER; i++)
    {
        if (key_list[i].is_press) // 按键短按对应动作
        {
            switch (i)
            {
            case 0:
                break;
            case 1:
                menu_activate_item();
                break;
            case 2:
                menu_navigation_action(PREV, FALSE);
                break;
            case 3:
                menu_navigation_action(NEXT, FALSE);
                break;
            default:
                break;
            }
        }

        if (key_list[i].is_hold) // 按键长按对应动作
        {
            switch (i)
            {
            case 0:
                break;
            case 1:
                break;
            case 2:
                menu_navigation_action(PREV, TRUE);
                break;
            case 3:
                menu_navigation_action(NEXT, TRUE);
                break;
            default:
                break;
            }
        }

        if (key_list[i].is_multi) // 按键双击对应动作
        {
            switch (i)
            {
            case 0:
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            default:
                break;
            }
        }
    }
}

/**
 * @brief 按键列表初始化
 *
 * @param pit_timer 按键扫描对应的 PIT 定时器周期
 */
void key_list_init(uint8 pit_timer)
{
    timer = pit_timer;

    for (uint8 i = 0; i < KEY_NUMBER; i++)
    {
        // 初始化按键结构体
        key_list[i].value = 0;
        key_list[i].last_value = 0;
        key_list[i].hold_time = 0;
        key_list[i].interval_time = 0;
        key_list[i].click_count = 0;
        key_list[i].state = RELEASE;
        key_list[i].is_press = FALSE;
        key_list[i].is_hold = FALSE;
        key_list[i].is_multi = FALSE;

        // 初始化按键对应的 GPIO
        gpio_init(key_pins[i], GPI, 0, GPI_PULL_UP);
    }
}
