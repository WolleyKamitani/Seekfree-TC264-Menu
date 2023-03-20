#include "menu.h"

menu_struct menu = {NULL, NULL, NULL, PAGE_ITEM, FALSE, STEP_1};

/**
 * @brief �ڲ˵��в���ָ�����Ƶ�ҳ��
 *
 * @param target_page_name �����ҵ�ҳ������
 * @return menu_page_struct* �����ҵ�ҳ��ָ��
 */
menu_page_struct *menu_search_page(const char target_page_name[])
{
    menu_page_struct *target_page = menu.first_page;

    while (target_page != NULL)
    {
        if (strcmp(target_page->name, target_page_name) == 0)
        {
            return target_page;
        }

        target_page = target_page->next_page;
    }

    return NULL;
}

/**
 * @brief ��ָ��ҳ���в���ָ�����ƵĲ˵���
 *
 * @param target_page �����ҵ�ҳ��
 * @param target_item_name �����ҵĲ˵�������
 * @return menu_item_struct* �����ҵĲ˵���ָ��
 */
menu_item_struct *menu_search_item(menu_page_struct *target_page, const char target_item_name[])
{
    for (uint8 i = 0; i < target_page->items_count; i++)
    {
        if (strcmp(target_page->items[i].name, target_item_name) == 0)
        {
            return &target_page->items[i];
        }
    }

    return NULL;
}

/**
 * @brief ��������ʼ���²˵�ҳ��
 *
 * @param page_name �˵�ҳ������
 * @return menu_page_struct* �´����Ĳ˵�ҳ��ָ��
 */
menu_page_struct *menu_init_page(const char page_name[])
{
    // �����²˵�ҳ�沢����Ƿ񴴽��ɹ�
    menu_page_struct *new_page = (menu_page_struct *)malloc(sizeof(menu_page_struct));
    zf_assert(new_page != NULL);

    // ���˵�ҳ�����Ƴ����Ƿ񳬳�����
    zf_assert(strlen(page_name) <= PAGE_MAX_NAME_LEN);
    strcpy(new_page->name, page_name);

    // ��ʼ���˵�ҳ��
    new_page->prev_page = NULL;
    new_page->next_page = NULL;
    new_page->items_count = 0;

    return new_page;
}

/**
 * @brief ����²˵�ҳ��
 *
 * @param page_name �˵�ҳ������
 */
void menu_add_page(const char page_name[])
{
    // ����Ƿ��Ѵ���ͬ��ҳ��
    zf_assert(menu_search_page(page_name) != NULL);

    // ��ʼ���²˵�ҳ��
    menu_page_struct *new_page = menu_init_page(page_name);

    if (menu.last_page == NULL)
    {
        // �����ǰ�˵���û��ҳ�棬����ҳ������Ϊ��һ��ҳ��
        menu.first_page = new_page;
        menu.last_page = new_page;
    }
    else
    {
        // ������ҳ����ӵ���ǰ�˵������һ��ҳ�����
        menu.last_page->next_page = new_page;
        new_page->prev_page = menu.last_page;
        menu.last_page = new_page;
    }
}

/**
 * @brief ����²˵���
 *
 * @param page_name �˵�ҳ������
 * @param item_name �˵�������
 * @param item_data �˵�������
 * @param item_type �˵�������
 * @param auto_refresh �Ƿ��Զ�����
 */
void menu_add_item(const char page_name[], const char item_name[], void *item_data, menu_item_type_enum item_type, bool auto_refresh)
{
    // ���Ҫ��Ӳ˵����ҳ���Ƿ����
    menu_page_struct *target_page = menu_search_page(page_name);
    zf_assert(target_page != NULL);

    // ���˵������Ƴ����Ƿ񳬳�����
    zf_assert(strlen(item_name) <= ITEM_MAX_NAME_LEN);

    // ����Ƿ��Ѵ���ͬ���˵���
    zf_assert(menu_search_item(target_page, item_name) == NULL);

    // ��ȡ�²˵����ָ��
    menu_item_struct *new_item = &target_page->items[target_page->items_count++];

    // ��ʼ���²˵���
    strcpy(new_item->name, item_name);
    new_item->type = item_type;
    new_item->data = item_data;
    new_item->auto_refresh = auto_refresh;
}

/**
 * @brief ���˵������ݸ�ʽ��Ϊ�ַ���
 *
 * @param format_res ��ʽ�����
 * @param menu_item ����ʽ���Ĳ˵���
 */
void menu_format_data(char *format_res, menu_item_struct menu_item)
{
    switch (menu_item.type)
    {
        // ���ݲ˵������͸�ʽ������
    case TYPE_BOOL:
        strcpy(format_res, *(bool *)menu_item.data ? "TRUE" : "FALSE");
        break;
    case TYPE_INT8:
        format_int(format_res, *(int8 *)menu_item.data, DATA_MAX_LEN);
        break;
    case TYPE_INT16:
        format_int(format_res, *(int16 *)menu_item.data, DATA_MAX_LEN);
        break;
    case TYPE_INT32:
        format_int(format_res, *(int32 *)menu_item.data, DATA_MAX_LEN);
        break;
    case TYPE_INT64:
        format_int(format_res, *(int64 *)menu_item.data, DATA_MAX_LEN);
        break;
    case TYPE_UINT8:
        format_uint(format_res, *(uint8 *)menu_item.data, DATA_MAX_LEN);
        break;
    case TYPE_UINT16:
        format_uint(format_res, *(uint16 *)menu_item.data, DATA_MAX_LEN);
        break;
    case TYPE_UINT32:
        format_uint(format_res, *(uint32 *)menu_item.data, DATA_MAX_LEN);
        break;
    case TYPE_UINT64:
        format_uint(format_res, *(uint64 *)menu_item.data, DATA_MAX_LEN);
        break;
    case TYPE_FLOAT:
        format_float(format_res, *(float *)menu_item.data, DATA_MAX_LEN);
        break;
    case TYPE_DOUBLE:
        format_float(format_res, *(double *)menu_item.data, DATA_MAX_LEN);
        break;
    default:
        format_res[0] = '\0';
        break;
    }

    if (strlen(format_res) < DATA_MAX_LEN)
    {
        // ������ݳ���С����󳤶ȣ���������ǰ�油�ո�
        char *temp = (char *)malloc(DATA_MAX_LEN + 1);
        zf_assert(temp != NULL);

        strcpy(temp, format_res);
        memset(format_res, ' ', DATA_MAX_LEN);
        strcpy(format_res + DATA_MAX_LEN - strlen(temp), temp);

        free(temp);
    }
}

/**
 * @brief ��ʾ�˵�����
 *
 * @param reverse �Ƿ�ɫ��ʾ
 * @param underline �Ƿ���ʾ�»���
 */
void menu_show_title(bool reverse, bool underline)
{
    if (menu.current_page->prev_page != NULL)
    {
        tft180_show_styled_string(LEFT, 0, 0, ">", FALSE, FALSE);
    }

    if (menu.current_page->next_page != NULL)
    {
        tft180_show_styled_string(RIGHT, 0, 0, "<", FALSE, FALSE);
    }

    char title[24];
    sprintf(title, "<%s>", menu.current_page->name);

    tft180_show_styled_string(CENTER, 0, 0, title, reverse, underline);
}

/**
 * @brief ��ʾ���ڲ���
 *
 * @param reverse �Ƿ�ɫ��ʾ
 * @param underline �Ƿ���ʾ�»���
 */
void menu_show_step(bool reverse, bool underline)
{
    char step[12];

    switch (menu.step_size)
    {
    case STEP_0_01:
        strcpy(step, "STEP:0.01");
        break;
    case STEP_0_1:
        strcpy(step, "STEP: 0.1");
        break;
    case STEP_1:
        strcpy(step, "STEP:   1");
        break;
    case STEP_10:
        strcpy(step, "STEP:  10");
        break;
    case STEP_100:
        strcpy(step, "STEP: 100");
        break;
    }

    tft180_show_styled_string(CENTER, 0, LINE_HEIGHT_OFFSET + SCREEN_HEIGHT_OFFSET, step, reverse, underline);
}

/**
 * @brief ��ʾ�˵�������
 *
 * @param item_index �˵�������
 * @param reverse �Ƿ�ɫ��ʾ
 * @param underline �Ƿ���ʾ�»���
 */
void menu_show_item_name(uint8 item_index, bool reverse, bool underline)
{
    menu_item_struct *item = &menu.current_page->items[item_index];
    tft180_show_styled_string(LEFT, 6,
                              (2 + item_index) * LINE_HEIGHT_OFFSET + SCREEN_HEIGHT_OFFSET,
                              item->name, reverse, underline);
}

/**
 * @brief ��ʾ�˵�������
 *
 * @param menu_item �˵���
 */
void menu_show_item_data(uint8 item_index)
{
    char format_res[DATA_MAX_LEN + 1];
    menu_format_data(format_res, menu.current_page->items[item_index]);
    tft180_show_styled_string(RIGHT, 6,
                              (2 + item_index) * LINE_HEIGHT_OFFSET + SCREEN_HEIGHT_OFFSET,
                              format_res, FALSE, FALSE);
}

/**
 * @brief ��ʾ���в˵���
 *
 */
void menu_show_items(void)
{
    for (uint8 i = 0; i < menu.current_page->items_count; i++)
    {
        menu_show_item_name(i, FALSE, menu.item_index == i);
        menu_show_item_data(i);
    }
}

/**
 * @brief ˢ��������Ҫ�Զ�ˢ�µĲ˵�������
 *
 */
void menu_refresh_items_data()
{
    for (uint8 i = 0; i < menu.current_page->items_count; i++)
    {
        if (menu.current_page->items[i].auto_refresh)
        {
            menu_show_item_data(i);
        }
    }
}

/**
 * @brief ˢ�²˵�ѡ�񣬲˵�ѡ���л�ʱ��ˢ��
 *
 * @param item_index �˵�������
 */
void menu_refresh_item(int8 item_index)
{
    switch (item_index)
    {
    case PAGE_ITEM:
        menu_show_title(menu.item_activated, !menu.item_activated);
        break;
    case STEP_ITEM:
        menu_show_step(menu.item_activated, !menu.item_activated);
        break;
    default:
        menu_show_item_name(item_index, menu.item_activated, !menu.item_activated);
        break;
    }
}

/**
 * @brief �ػ�˵���������
 *
 */
void menu_repaint(void)
{
    tft180_clear();

    if (menu.item_index == PAGE_ITEM)
    {
        menu_show_title(menu.item_activated, !menu.item_activated);
    }
    else
    {
        menu_show_title(FALSE, FALSE);
    }

    if (menu.item_index == STEP_ITEM)
    {
        menu_show_step(menu.item_activated, !menu.item_activated);
    }
    else
    {
        menu_show_step(FALSE, FALSE);
    }

    menu_show_items();
}

/**
 * @brief �˵�ҳ���л�
 *
 * @param direction �л����� ���� common.h �е� navigation_enum
 */
void menu_turn_page(navigation_enum direction)
{
    menu_page_struct *last_page = menu.current_page;

    switch (direction)
    {
    case PREV:
        menu.current_page = menu.current_page->prev_page ? menu.current_page->prev_page : menu.current_page;
        break;
    case NEXT:
        menu.current_page = menu.current_page->next_page ? menu.current_page->next_page : menu.current_page;
        break;
    }

    if (last_page != menu.current_page)
    {
        menu.item_index = menu.item_index == PAGE_ITEM ? PAGE_ITEM : 0;
        menu_refresh();
    }
}

/**
 * @brief �˵�ѡ���л�
 *
 * @param direction �л����� ���� common.h �е� navigation_enum
 */
void menu_turn_item(navigation_enum direction)
{
    int8 last_item_index = menu.item_index;
    menu.item_index += direction == PREV
                           ? (menu.item_index == PAGE_ITEM ? 0 : -1)
                           : (menu.item_index == (menu.current_page->items_count - 1) ? 0 : 1);

    if (last_item_index != menu.item_index)
    {
        menu_refresh_item(last_item_index);
        menu_refresh_item(menu.item_index);
    }
}

/**
 * @brief ���ǰѡ��
 *
 */
void menu_activate_item(void)
{
    if (menu.item_index >= 0 && menu.current_page->items[menu.item_index].type == TYPE_FUNC)
    {
        ((void (*)(void))menu.current_page->items[menu.item_index].data)();
    }
    else
    {
        menu.item_activated = !menu.item_activated;
        menu_refresh_item(menu.item_index);
    }
}

/**
 * @brief �������ڲ���
 *
 * @param direction �������� ���� common.h �е� plus_minus_enum
 */
void menu_adjust_step(plus_minus_enum direction)
{
    menu.step_size = direction == MINUS
                         ? (menu.step_size == STEP_1 ? STEP_100 : menu.step_size - 1)
                         : (menu.step_size == STEP_100 ? STEP_1 : menu.step_size + 1);

    if (menu.item_index == STEP_ITEM)
    {
        menu_refresh_item(STEP_ITEM);
    }
    else
    {
        menu_show_step(FALSE, FALSE);
    }
}

/**
 * @brief �����˵����ֵ
 *
 * @param direction
 */
void menu_adjust_value(plus_minus_enum direction)
{
    switch (menu.item_index)
    {
    case PAGE_ITEM:
        menu_turn_page((navigation_enum)direction);
        break;
    case STEP_ITEM:
        menu_adjust_step(direction);
        break;
    default:
    {
        menu_item_struct *item = &menu.current_page->items[menu.item_index];
        float adjust_step = direction == MINUS
                                ? -powf(10, menu.step_size - 2)
                                : powf(10, menu.step_size - 2);

        switch (item->type)
        {
        case TYPE_BOOL:
            *((bool *)(item->data)) = *((bool *)(item->data)) ? false : true;
            break;
        case TYPE_INT8:
            *((int8 *)(item->data)) += adjust_step;
            break;
        case TYPE_INT16:
            *((int16 *)(item->data)) += adjust_step;
            break;
        case TYPE_INT32:
            *((int32 *)(item->data)) += adjust_step;
            break;
        case TYPE_INT64:
            *((int64 *)(item->data)) += adjust_step;
            break;
        case TYPE_UINT8:
            *((uint8 *)(item->data)) += adjust_step;
            break;
        case TYPE_UINT16:
            *((uint16 *)(item->data)) += adjust_step;
            break;
        case TYPE_UINT32:
            *((uint32 *)(item->data)) += adjust_step;
            break;
        case TYPE_UINT64:
            *((uint64 *)(item->data)) += adjust_step;
            break;
        case TYPE_FLOAT:
            *((float *)(item->data)) += adjust_step;
            break;
        case TYPE_DOUBLE:
            *((double *)(item->data)) += adjust_step;
            break;
        default:
            break;
        }

        menu_show_item_data(menu.item_index);
        break;
    }
    }
}

//========================��ʱ��������========================//
int8 int8_test = 123;
int16 int16_test = -12345;
int32 int32_test = 1234567;
int64 int64_test = -1000000;
uint8 uint8_test = 123;
uint16 uint16_test = 12345;
uint32 uint32_test = 1234567;
uint64 uint64_test = 10000000;
float float_test = 123.45;
double double_test = -123.45;
bool bool_test = true;
void drawsmile() { tft180_show_styled_string(CENTER, 0, 150, ":)", FALSE, FALSE); }
//========================��ʱ��������========================//

/**
 * @brief �˵���ʼ��
 *
 */
void menu_init(void)
{
    menu_add_page("MAIN");
    menu_add_item("MAIN", "float", &float_test, TYPE_FLOAT, TRUE);
    menu_add_item("MAIN", "double", &double_test, TYPE_DOUBLE, TRUE);
    menu_add_item("MAIN", "bool", &bool_test, TYPE_BOOL, TRUE);
    menu_add_page("SETTING");
    menu_add_item("SETTING", "int8", &int8_test, TYPE_INT8, TRUE);
    menu_add_item("SETTING", "int16", &int16_test, TYPE_INT16, TRUE);
    menu_add_item("SETTING", "int32", &int32_test, TYPE_INT32, TRUE);
    menu_add_item("SETTING", "int64", &int64_test, TYPE_INT64, TRUE);
    menu_add_item("SETTING", "uint8", &uint8_test, TYPE_UINT8, TRUE);
    menu_add_item("SETTING", "uint16", &uint16_test, TYPE_UINT16, TRUE);
    menu_add_item("SETTING", "uint32", &uint32_test, TYPE_UINT32, TRUE);
    menu_add_item("SETTING", "uint64", &uint64_test, TYPE_UINT64, TRUE);
    menu_add_page("TEST");

    menu_repaint();
}

/**
 * @brief �˵�ˢ�£�����ѭ���е���
 *
 */
void menu_refresh(void)
{
    menu_refresh_items_data();
}
