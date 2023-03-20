#include "menu.h"

menu_struct menu = {NULL, NULL, NULL, PAGE_ITEM, FALSE, STEP_1};

/**
 * @brief 在菜单中查找指定名称的页面
 *
 * @param target_page_name 待查找的页面名称
 * @return menu_page_struct* 所查找的页面指针
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
 * @brief 在指定页面中查找指定名称的菜单项
 *
 * @param target_page 待查找的页面
 * @param target_item_name 待查找的菜单项名称
 * @return menu_item_struct* 所查找的菜单项指针
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
 * @brief 创建并初始化新菜单页面
 *
 * @param page_name 菜单页面名称
 * @return menu_page_struct* 新创建的菜单页面指针
 */
menu_page_struct *menu_init_page(const char page_name[])
{
    // 创建新菜单页面并检查是否创建成功
    menu_page_struct *new_page = (menu_page_struct *)malloc(sizeof(menu_page_struct));
    zf_assert(new_page != NULL);

    // 检查菜单页面名称长度是否超出限制
    zf_assert(strlen(page_name) <= PAGE_MAX_NAME_LEN);
    strcpy(new_page->name, page_name);

    // 初始化菜单页面
    new_page->prev_page = NULL;
    new_page->next_page = NULL;
    new_page->items_count = 0;

    return new_page;
}

/**
 * @brief 添加新菜单页面
 *
 * @param page_name 菜单页面名称
 */
void menu_add_page(const char page_name[])
{
    // 检查是否已存在同名页面
    zf_assert(menu_search_page(page_name) != NULL);

    // 初始化新菜单页面
    menu_page_struct *new_page = menu_init_page(page_name);

    if (menu.last_page == NULL)
    {
        // 如果当前菜单中没有页面，则将新页面设置为第一个页面
        menu.first_page = new_page;
        menu.last_page = new_page;
    }
    else
    {
        // 否则将新页面添加到当前菜单的最后一个页面后面
        menu.last_page->next_page = new_page;
        new_page->prev_page = menu.last_page;
        menu.last_page = new_page;
    }
}

/**
 * @brief 添加新菜单项
 *
 * @param page_name 菜单页面名称
 * @param item_name 菜单项名称
 * @param item_data 菜单项数据
 * @param item_type 菜单项类型
 * @param auto_refresh 是否自动更新
 */
void menu_add_item(const char page_name[], const char item_name[], void *item_data, menu_item_type_enum item_type, bool auto_refresh)
{
    // 检查要添加菜单项的页面是否存在
    menu_page_struct *target_page = menu_search_page(page_name);
    zf_assert(target_page != NULL);

    // 检查菜单项名称长度是否超出限制
    zf_assert(strlen(item_name) <= ITEM_MAX_NAME_LEN);

    // 检查是否已存在同名菜单项
    zf_assert(menu_search_item(target_page, item_name) == NULL);

    // 获取新菜单项的指针
    menu_item_struct *new_item = &target_page->items[target_page->items_count++];

    // 初始化新菜单项
    strcpy(new_item->name, item_name);
    new_item->type = item_type;
    new_item->data = item_data;
    new_item->auto_refresh = auto_refresh;
}

/**
 * @brief 将菜单项数据格式化为字符串
 *
 * @param format_res 格式化结果
 * @param menu_item 待格式化的菜单项
 */
void menu_format_data(char *format_res, menu_item_struct menu_item)
{
    switch (menu_item.type)
    {
        // 根据菜单项类型格式化数据
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
        // 如果数据长度小于最大长度，则在数据前面补空格
        char *temp = (char *)malloc(DATA_MAX_LEN + 1);
        zf_assert(temp != NULL);

        strcpy(temp, format_res);
        memset(format_res, ' ', DATA_MAX_LEN);
        strcpy(format_res + DATA_MAX_LEN - strlen(temp), temp);

        free(temp);
    }
}

/**
 * @brief 显示菜单标题
 *
 * @param reverse 是否反色显示
 * @param underline 是否显示下划线
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
 * @brief 显示调节步长
 *
 * @param reverse 是否反色显示
 * @param underline 是否显示下划线
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
 * @brief 显示菜单项名称
 *
 * @param item_index 菜单项索引
 * @param reverse 是否反色显示
 * @param underline 是否显示下划线
 */
void menu_show_item_name(uint8 item_index, bool reverse, bool underline)
{
    menu_item_struct *item = &menu.current_page->items[item_index];
    tft180_show_styled_string(LEFT, 6,
                              (2 + item_index) * LINE_HEIGHT_OFFSET + SCREEN_HEIGHT_OFFSET,
                              item->name, reverse, underline);
}

/**
 * @brief 显示菜单项数据
 *
 * @param menu_item 菜单项
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
 * @brief 显示所有菜单项
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
 * @brief 刷新所有需要自动刷新的菜单项数据
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
 * @brief 刷新菜单选择，菜单选择切换时的刷新
 *
 * @param item_index 菜单项索引
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
 * @brief 重绘菜单所有内容
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
 * @brief 菜单页面切换
 *
 * @param direction 切换方向 参照 common.h 中的 navigation_enum
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
 * @brief 菜单选中切换
 *
 * @param direction 切换方向 参照 common.h 中的 navigation_enum
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
 * @brief 激活当前选项
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
 * @brief 调整调节步长
 *
 * @param direction 调整方向 参照 common.h 中的 plus_minus_enum
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
 * @brief 调整菜单项的值
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

//========================临时测试数据========================//
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
//========================临时测试数据========================//

/**
 * @brief 菜单初始化
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
 * @brief 菜单刷新，在主循环中调用
 *
 */
void menu_refresh(void)
{
    menu_refresh_items_data();
}
