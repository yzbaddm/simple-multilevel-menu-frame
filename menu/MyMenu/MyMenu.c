#include "MyMenu.h"
#include <stdio.h>

extern Menu_t item2Menu[];

const MenuItem_t startItem[] = {
    {"测试菜单1", 0xff},// 这里 namelen 0xff 表示填充
    {"测试菜单2", 0xff},
    {"测试菜单3", 0xff},
    {"测试菜单4", 0xff},
    {"测试菜单5", 0xff},
    {"测试菜单6", 0xff},
    {"测试菜单7", 0xff},
    {"测试菜单8", 0xff},
};

const MenuItem_t Item1[] = {
    {"Item1菜单1", 0xff},
    {"Item1菜单2", 0xff},
    {"Item1菜单3", 0xff},
    {"Item1菜单4", 0xff},
    {"Item1菜单5", 0xff},
    {"Item1菜单6", 0xff},
    {"Item1菜单7", 0xff},
    {"Item1菜单8", 0xff},
};

const MenuItem_t Item2[] = {
    {"Item2菜单1", 0xff},
    {"Item2菜单2", 0xff},
    {"Item2菜单3", 0xff},
    {"Item2菜单4", 0xff},
    {"Item2菜单5", 0xff},
    {"Item2菜单6", 0xff},
    {"Item2菜单7", 0xff},
    {"Item2菜单8", 0xff},
};

Menu_t startMenu = {
    .menu = (MenuItem_t *)startItem,
    .index = 0,
    .itemlen = sizeof(startItem)/sizeof(MenuItem_t),
    .submenu = item2Menu,
    .parentmenu = NULL,
    .callback = MyMenu_StartItem,
};

Menu_t item2Menu[] = {
    {(MenuItem_t *)Item1, 0, sizeof(Item1)/sizeof(MenuItem_t), NULL, &startMenu, MyMenu_StartItem},
    {(MenuItem_t *)Item2, 0, sizeof(Item2)/sizeof(MenuItem_t), NULL, &startMenu, MyMenu_StartItem},
    {NULL, 0, 0, NULL, &startMenu, NULL},
    {NULL, 0, 0, NULL, &startMenu, NULL},
    {NULL, 0, 0, NULL, &startMenu, NULL},
    {NULL, 0, 0, NULL, &startMenu, NULL},
    {NULL, 0, 0, NULL, &startMenu, NULL},
    {NULL, 0, 0, NULL, &startMenu, NULL},
};

Menu_t *menu = &startMenu;

/**
 * @brief 开始菜�?
 */
void MyMenu_StartItem(MenuItem_t *menu, uint8_t index, uint8_t itemlen)
{
    for (uint8_t i = 0; i < itemlen; i ++) {
        printf("%s\r\n", menu[i].name);
    }
    printf("当前选中的菜单项是：%d\r\n", index);
}

