#ifndef _menu_h_
#define _menu_h_

#include "zf_common_headfile.h"
#include "common.h"
#include "screen.h"

#define PAGE_MAX_NAME_LEN 16 // 菜单页面名称最大长度
#define ITEM_MAX_NAME_LEN 12 // 菜单项名称最大长度
#define ITEM_MAX_COUNT 10    // 菜单项最大数量
#define DATA_MAX_LEN 7       // 菜单项数据最大长度

#define PAGE_ITEM -2 // 菜单页面项索引
#define STEP_ITEM -1 // 调节步长项索引

#define LINE_HEIGHT_OFFSET (tft180_display_dir < 2 ? 5 : 2)   // 行高偏移量
#define SCREEN_HEIGHT_OFFSET (tft180_display_dir < 2 ? 0 : 3) // 屏幕高度偏移量

//========================菜单参数结构体========================//
typedef enum
{
    TYPE_NULL,   // 空
    TYPE_BOOL,   // 布尔型
    TYPE_INT8,   // 8 位整型
    TYPE_INT16,  // 16 位整型
    TYPE_INT32,  // 32 位整型
    TYPE_INT64,  // 64 位整型
    TYPE_UINT8,  // 8 位无符号整型
    TYPE_UINT16, // 16 位无符号整型
    TYPE_UINT32, // 32 位无符号整型
    TYPE_UINT64, // 64 位无符号整型
    TYPE_FLOAT,  // 浮点型
    TYPE_DOUBLE, // 双精度浮点型
    TYPE_FUNC,   // 函数
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
    char name[16];            // 菜单项名称
    void *data;               // 菜单项数据
    menu_item_type_enum type; // 菜单项类型
    bool auto_refresh;        // 菜单项是否自动更新
} menu_item_struct;

typedef struct menu_page
{
    char name[24];                          // 菜单页面名称
    struct menu_page *prev_page;            // 上一个菜单页面
    struct menu_page *next_page;            // 下一个菜单页面
    struct menu_item items[ITEM_MAX_COUNT]; // 菜单项
    uint8 items_count;                      // 当前菜单项数量
} menu_page_struct;

typedef struct menu
{
    struct menu_page *first_page;   // 第一个菜单页面
    struct menu_page *last_page;    // 最后一个菜单页面
    struct menu_page *current_page; // 当前菜单页面
    int8 item_index;                // 当前选中菜单项
    bool item_activated;            // 当前选中是否激活
    menu_step_enum step_size;       // 调节步长
} menu_struct;
//========================菜单参数结构体========================//

//========================菜单基础函数========================//
void menu_init(void);
void menu_refresh(void);
//========================菜单基础函数========================//

#endif