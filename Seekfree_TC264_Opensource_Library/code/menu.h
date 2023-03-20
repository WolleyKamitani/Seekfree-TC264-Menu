#ifndef _menu_h_
#define _menu_h_

#include "zf_common_headfile.h"
#include "common.h"
#include "screen.h"

#define PAGE_MAX_NAME_LEN 16 // �˵�ҳ��������󳤶�
#define ITEM_MAX_NAME_LEN 12 // �˵���������󳤶�
#define ITEM_MAX_COUNT 10    // �˵����������
#define DATA_MAX_LEN 7       // �˵���������󳤶�

#define PAGE_ITEM -2 // �˵�ҳ��������
#define STEP_ITEM -1 // ���ڲ���������

#define LINE_HEIGHT_OFFSET (tft180_display_dir < 2 ? 5 : 2)   // �и�ƫ����
#define SCREEN_HEIGHT_OFFSET (tft180_display_dir < 2 ? 0 : 3) // ��Ļ�߶�ƫ����

//========================�˵������ṹ��========================//
typedef enum
{
    TYPE_NULL,   // ��
    TYPE_BOOL,   // ������
    TYPE_INT8,   // 8 λ����
    TYPE_INT16,  // 16 λ����
    TYPE_INT32,  // 32 λ����
    TYPE_INT64,  // 64 λ����
    TYPE_UINT8,  // 8 λ�޷�������
    TYPE_UINT16, // 16 λ�޷�������
    TYPE_UINT32, // 32 λ�޷�������
    TYPE_UINT64, // 64 λ�޷�������
    TYPE_FLOAT,  // ������
    TYPE_DOUBLE, // ˫���ȸ�����
    TYPE_FUNC,   // ����
} menu_item_type_enum;

typedef enum
{
    STEP_0_01,
    STEP_0_1,
    STEP_1,
    STEP_10,
    STEP_100,
} menu_step_enum;

typedef struct menu_item
{
    char name[16];            // �˵�������
    void *data;               // �˵�������
    menu_item_type_enum type; // �˵�������
    bool auto_refresh;        // �˵����Ƿ��Զ�����
} menu_item_struct;

typedef struct menu_page
{
    char name[24];                          // �˵�ҳ������
    struct menu_page *prev_page;            // ��һ���˵�ҳ��
    struct menu_page *next_page;            // ��һ���˵�ҳ��
    struct menu_item items[ITEM_MAX_COUNT]; // �˵���
    uint8 items_count;                      // ��ǰ�˵�������
} menu_page_struct;

typedef struct menu
{
    struct menu_page *first_page;   // ��һ���˵�ҳ��
    struct menu_page *last_page;    // ���һ���˵�ҳ��
    struct menu_page *current_page; // ��ǰ�˵�ҳ��
    int8 item_index;                // ��ǰѡ�в˵���
    bool item_activated;            // ��ǰѡ���Ƿ񼤻�
    menu_step_enum step_size;       // ���ڲ���
} menu_struct;
//========================�˵������ṹ��========================//

//========================�˵���������========================//
void menu_init(void);
void menu_refresh(void);
//========================�˵���������========================//

#endif