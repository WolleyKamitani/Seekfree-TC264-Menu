#include "key.h"

typedef void (*key_action_func)(void);

/**
 * @brief 按键对应动作 按需求自行修改
 *        从左到右依次对应按键释放 消抖 短按和长按状态 填写函数需要是没有参数的函数
 *
 */
static key_action_func key_actions[KEY_NUMBER][4] = {
    {NULL, NULL, NULL, NULL},
    {NULL, NULL, menu_activate_item, NULL},
    {NULL, NULL, menu_short_press_prev_navigation, menu_long_press_prev_navigation},
    {NULL, NULL, menu_short_press_next_navigation, menu_long_press_next_navigation},
};

/**
 * @brief 按键执行动作
 *        按键数目和对应引脚在 zf_device_key.h 内修改
 *
 */
void key_perform_action(void)
{
    static key_state_enum last_key_state[KEY_NUMBER] = {KEY_RELEASE};
    key_state_enum key_state[KEY_NUMBER];

    for (uint8 i = 0; i < KEY_NUMBER; i++)
    {
        key_state[i] = key_get_state(i);
        if (key_state[i] != last_key_state[i])
        {
            key_actions[i][last_key_state[i]]();
        }
        last_key_state[i] = key_state[i];
    }
}