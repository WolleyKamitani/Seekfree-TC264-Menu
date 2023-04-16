#ifndef _key_h_
#define _key_h_

#include "zf_common_headfile.h"
#include "menu.h"

#define KEY_NUMBER 4 // ������Ŀ
#define KEY_PINS                   \
    {                              \
        P22_0, P22_1, P22_2, P22_3 \
    } // ������Ӧ����

#define PRESS_THRESHOLD 10     // ����������ֵ
#define HOLD_THRESHOLD 300     // ����������ֵ
#define INTERVAL_THRESHOLD 150 // ����������ֵ

//========================�����ṹ�����========================//
typedef struct
{
    uint8 value, last_value;         // ������ǰֵ / ��һ��ֵ
    uint32 hold_time, interval_time; // ��������ʱ�� / ��������ʱ��
    uint32 click_count;              // ������������

    enum
    {
        RELEASE,   // �����ͷ�
        DITHER,    // ��������
        PRE_CLICK, // Ԥ˫����
        IN_CLICK,  // ��˫����
        PRESS,     // ��������
        HOLD,      // ��������
        MULTI,     // ��������
    } state;       // ����״̬

    bool is_press; // �����Ƿ���
    bool is_hold;  // �����Ƿ񳤰�
    bool is_multi; // �����Ƿ�����
} key_struct;
//========================�����ṹ�����========================//

//========================������������========================//
void key_handler(void);
void key_action(void);
void key_list_init(uint8 pit_timer);
//========================������������========================//

#endif