#include "Menu.h"

struct {
    MenuEvent_t queue[MAX_MENU_EVENT];
    uint8_t     write;
    uint8_t     read;
} menuQueue = {
    .write = 0,
    .read = 0,
    .queue = {MENU_ITEM}
};

/**
 * @brief 写入菜单事件
 * 
 * @param event 菜单事件
 * @note 必须为 MenuEvent_t 的值
 * @retval 0 写入成功  1:写入失败
 */
uint8_t Menu_QueueWrite(MenuEvent_t event)
{
    if  ((menuQueue.write + 1)%MAX_MENU_EVENT != menuQueue.read) {
        menuQueue.queue[menuQueue.write] = event;
        menuQueue.write = (menuQueue.write + 1)%MAX_MENU_EVENT;
        return 0;
    }
    return 1;
}

/**
 * @brief 从菜单事件队列中读取事件
 */
static MenuEvent_t Menu_QueueRead(void)
{
    if (menuQueue.read != menuQueue.write) {
        MenuEvent_t event = menuQueue.queue[menuQueue.read];
        menuQueue.read = (menuQueue.read + 1)%MAX_MENU_EVENT;
        return event;
    }
    return MENU_ITEM;
}

/**
 * @brief 进入子菜单
 * @param pointer 全局菜单指针
 * @param index 菜单索引
 */
static void Menu_EntranceSubmenu(Menu_t **pointer, uint8_t index)
{
    Menu_t *menu = (*pointer)->submenu;
    if (menu != NULL) {
        menu = &menu[index];
        if (menu->callback != NULL) {
            *pointer = menu;
        }
    }
}

/**
 * @brief 返回父菜单
 * @param pointer 全局菜单指针
 * @param startMenu 开始菜单
 * @param index 菜单索引
 */
static void Menu_EntranceParentmenu(Menu_t **pointer)
{
    Menu_t *menu = (*pointer)->parentmenu;
    if (menu != NULL) {
        *pointer = menu;
    }
}

/**
 * @brief 进入下一项
 * @param pointer 全局菜单指针
 */
static void Menu_NextItem(Menu_t *pointer)
{
    if (pointer->index < pointer->itemlen - 1) {
        pointer->index ++;
    }
}

/**
 * @brief 进入上一项
 * @param pointer 全局菜单指针
 */
static void Menu_PrevItem(Menu_t *pointer)
{
    if (pointer->index > 0) {
        pointer->index --;
    }
}

/**
 * @brief 切换菜单, 处理菜单事件
 * @param pointer 全局当前菜单指针, 应该指向父菜单
 */
void Menu_Switch(Menu_t **pointer)
{
    Menu_t *temp = *pointer;
    MenuEvent_t index = Menu_QueueRead();

    switch (index)
    {
    case ENTRANCE_SUB:
        Menu_EntranceSubmenu(pointer, temp->index);
        break;
    case ENTRANCE_PARENT:
        Menu_EntranceParentmenu(pointer);
        break;
    case PREV_ITEM:
        Menu_PrevItem(temp);
        break;
    case NEXT_ITEM:
        Menu_NextItem(temp);
        break;
    default:
        break;
    }
    temp->callback(temp->menu, temp->index, temp->itemlen);
}

/********* 菜单文本显示功能函数 *******************************************************************************************************************/

/**
 * @brief 纵轴显示多项文本
 * 
 * @param menu      菜单指针
 * @param x         基准 X坐标
 * @param y         基准 Y坐标
 * @param itemlen   菜单项要显示的个数
 * @param skewingLen       文本显示 Y轴偏移, 一般为字体大小
 * @return NULL
 */
void Menu_ShowVerticalAxisTxt(MenuItem_t *menu, int16_t x, int16_t y, uint8_t itemlen, uint16_t skewingLen)
{
    int32_t shiftingY;
    for (uint8_t index = 0; index < itemlen; index ++)
    {
        shiftingY = y + (index * skewingLen);  // 计算 Y轴偏移

        __MENU_ShowStr(x, shiftingY, menu[index].name);
    }
}
