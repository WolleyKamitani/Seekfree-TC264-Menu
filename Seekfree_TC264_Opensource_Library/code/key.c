#include "key.h"

/**
 * @brief 按键对应动作 按需求自行修改
 *
 */
void key_action(void)
{
    switch (key_get_state(KEY_1))
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

    switch (key_get_state(KEY_2))
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

    switch (key_get_state(KEY_3))
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

    switch (key_get_state(KEY_4))
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