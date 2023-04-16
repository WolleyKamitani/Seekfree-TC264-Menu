#include "key.h"

static key_struct key_list[KEY_NUMBER];               // �����б�
static gpio_pin_enum key_pins[KEY_NUMBER] = KEY_PINS; // ������Ӧ����
static uint8 timer = 0;                               // ����ɨ����

/**
 * @brief ����״̬���
 *
 */
void key_handler(void)
{
    // ���������б�
    for (uint8 i = 0; i < KEY_NUMBER; i++)
    {
        // ���°���״̬
        key_list[i].value = !gpio_get_level(key_pins[i]); // ��ȡ��ǰ����״̬����ת����Ϊ�͵�ƽ��ʾ���£�
        key_list[i].last_value = key_list[i].value;       // �洢��ǰ����״̬

        // �����ɿ�ʱ��������ʱ����
        if (!key_list[i].value && key_list[i].state != DITHER && key_list[i].state != HOLD)
        {
            key_list[i].hold_time = 0;
        }

        // ������������ʱ��������ʱ�ۼ�
        if (key_list[i].value && key_list[i].last_value)
        {
            key_list[i].hold_time += timer;
        }

        // ���������� PRE_CLICK �� IN_CLICK ״̬ʱ�������ʱ�ۼ�
        if (key_list[i].state == PRE_CLICK || key_list[i].state == IN_CLICK)
        {
            key_list[i].interval_time += timer;
        }
        else
        {
            key_list[i].interval_time = 0;
        }

        // ����״̬��
        switch (key_list[i].state)
        {
        case RELEASE:
            // �������״̬
            key_list[i].is_press = FALSE;
            key_list[i].is_hold = FALSE;
            key_list[i].is_multi = FALSE;
            key_list[i].click_count = 0;

            // �����ʱ��ť�Դ��ڰ���״̬������� DITHER ״̬
            if (key_list[i].value)
            {
                key_list[i].state = DITHER;
            }

            break;
        case DITHER:
            // �����������ʱ�䳬����ֵ������ HOLD ״̬
            if (key_list[i].hold_time > HOLD_THRESHOLD)
            {
                key_list[i].state = HOLD;
            }

            // ��������ͷ��Ұ���ʱ����� PRESS_THRESHOLD ��С�� HOLD_THRESHOLD������� PRE_CLICK ״̬�����ӵ������
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
            // ����������ʱ��С����ֵ�Ұ�������ʱ����� PRESS_THRESHOLD������� MULTI ״̬�����ӵ������
            if (key_list[i].interval_time < INTERVAL_THRESHOLD)
            {
                if (key_list[i].hold_time > PRESS_THRESHOLD)
                {
                    key_list[i].state = MULTI;
                    key_list[i].click_count++;
                }
                break;
            }

            // ���򣬽��� PRESS ״̬
            key_list[i].state = PRESS;
            break;
        case IN_CLICK:
            // ����������ʱ��С����ֵ�Ұ�������ʱ����� PRESS_THRESHOLD������� MULTI ״̬�����ӵ������
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
                // ����������ʱ�䳬����ֵ������ is_multi Ϊ�棬������ RELEASE ״̬
                key_list[i].is_multi = TRUE;
                key_list[i].state = RELEASE;
            }

            break;
        case PRESS:
            // ���� is_press Ϊ��
            key_list[i].is_press = TRUE;

            // ��������ͷţ����� RELEASE ״̬
            if (!key_list[i].value)
            {
                key_list[i].state = RELEASE;
            }

            break;
        case HOLD:
            // �������ͷ�ʱ������ is_hold Ϊ�棬������ RELEASE ״̬
            if (!key_list[i].value)
            {
                key_list[i].is_hold = TRUE;
                key_list[i].state = RELEASE;
            }

            break;
        case MULTI:
            // ��������ͷţ����� IN_CLICK ״̬
            if (!key_list[i].value)
            {
                key_list[i].state = IN_CLICK;
            }

            break;
        }
    }

    // ִ�а�������
    key_action();
}

/**
 * @brief ����ִ�ж���
 *        ʹ��ʱ������Ҫ�����޸�
 *
 */
void key_action(void)
{
    for (uint8 i = 0; i < KEY_NUMBER; i++)
    {
        if (key_list[i].is_press) // �����̰���Ӧ����
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

        if (key_list[i].is_hold) // ����������Ӧ����
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

        if (key_list[i].is_multi) // ����˫����Ӧ����
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
 * @brief �����б��ʼ��
 *
 * @param pit_timer ����ɨ���Ӧ�� PIT ��ʱ������
 */
void key_list_init(uint8 pit_timer)
{
    timer = pit_timer;

    for (uint8 i = 0; i < KEY_NUMBER; i++)
    {
        // ��ʼ�������ṹ��
        key_list[i].value = 0;
        key_list[i].last_value = 0;
        key_list[i].hold_time = 0;
        key_list[i].interval_time = 0;
        key_list[i].click_count = 0;
        key_list[i].state = RELEASE;
        key_list[i].is_press = FALSE;
        key_list[i].is_hold = FALSE;
        key_list[i].is_multi = FALSE;

        // ��ʼ��������Ӧ�� GPIO
        gpio_init(key_pins[i], GPI, 0, GPI_PULL_UP);
    }
}
