#include "key.h"

/**
 * @brief 按键对应动作 按需求自行修改
 *
 */
void key_action(void)
{
    static key_state_enum last_key_state[KEY_NUMBER] = {KEY_RELEASE};
    key_state_enum key_state[KEY_NUMBER] = {key_get_state(KEY_1),
                                            key_get_state(KEY_2),
                                            key_get_state(KEY_3),
                                            key_get_state(KEY_4)};

    if (key_state[KEY_1] == KEY_RELEASE)
    {
        switch (last_key_state[KEY_1])
        {
        case KEY_RELEASE:
            break;
        case KEY_CHECK_SHOCK:
            break;
        case KEY_SHORT_PRESS:
            break;
        case KEY_LONG_PRESS:
            break;
        }
    }

    if (key_state[KEY_2] == KEY_RELEASE)
    {
        switch (last_key_state[KEY_2])
        {
        case KEY_RELEASE:
            break;
        case KEY_CHECK_SHOCK:
            break;
        case KEY_SHORT_PRESS:
            menu_activate_item();
            break;
        case KEY_LONG_PRESS:
            break;
        }
    }

    if (key_state[KEY_3] == KEY_RELEASE)
    {
        switch (last_key_state[KEY_3])
        {
        case KEY_RELEASE:
            break;
        case KEY_CHECK_SHOCK:
            break;
        case KEY_SHORT_PRESS:
            menu_navigation_action(PREV, FALSE);
            break;
        case KEY_LONG_PRESS:
            menu_navigation_action(PREV, TRUE);
            break;
        }
    }

    if (key_state[KEY_4] == KEY_RELEASE)
    {
        switch (last_key_state[KEY_4])
        {
        case KEY_RELEASE:
            break;
        case KEY_CHECK_SHOCK:
            break;
        case KEY_SHORT_PRESS:
            menu_navigation_action(NEXT, FALSE);
            break;
        case KEY_LONG_PRESS:
            menu_navigation_action(NEXT, TRUE);
            break;
        }
    }

    for (uint8_t i = 0; i < KEY_NUMBER; i++)
    {
        last_key_state[i] = key_state[i];
    }
}