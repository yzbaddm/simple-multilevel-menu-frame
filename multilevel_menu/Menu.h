#ifndef _MENU_H_
#define _MENU_H_

/***************** include *********************************************************/
#include <stdint.h>
#include <string.h>

/***************** 菜单 Config *****************************************************/

#define MAX_MENU_EVENT          20                // 菜单项事件缓冲大小


/***************** 菜单 ************************************************************/


    /* 菜单状态 */
    typedef enum {
        MENU_ITEM = 0,                            /* 菜单项, 无变化 */
        ENTRANCE_SUB,                             /* 进入子菜单 */
        ENTRANCE_PARENT,                          /* 退出子菜单 */
        NEXT_ITEM,                                /* 下一个菜单项 */
        PREV_ITEM,                                /* 上一个菜单项 */
    } MenuEvent_t;

    /* 菜单项, 回调函数传入参数, 允许自定义 */
    typedef struct {
        const char            *name;              /* 菜单项名称 */
        uint8_t               namelen;            /*  菜单项名称长度, 单位字节(注意: 1个字符为 2个字节) */
    } MenuItem_t;

    /* 菜单回调函数, 返回当前 菜单项 和 当前菜单的索引、 菜单项长度 */
    typedef void (*MenuCallback_t)(MenuItem_t *menu, uint8_t index, uint8_t itemlen);

    /* 菜单 */
    typedef struct menu_t {
        MenuItem_t              *menu;            /* 当前菜单的子菜单项, 数组, 需要与子菜单个数一致
                                                   注意: 本项不是必须值, 只是用于绘制画面使用, 不需要则置 NULL */
        uint8_t                 index;            /* 当前菜单选中索引, 指示菜单的位置
                                                   注意: index 从 0 开始, 初始设置不可超过 itemlen 的值 */
        uint8_t               itemlen;            /* 子菜单个数 */
        struct menu_t        *submenu;            /* 子菜单数组, 需要与 itemlen 保持一致
                                                     注意: 本项为菜单主体, 需要根据 Menu_t 的值填充 */
        struct menu_t     *parentmenu;            /* 父菜单, 如果有那么必须是具体的菜单地址, 
                                                     例如: &menu[x] (x 为菜单索引)
                                                     注意: 没有父菜单(即本项为最开始的菜单), 则置 NULL */
        MenuCallback_t       callback;            /* 菜单回调函数 */
    } Menu_t;


uint8_t Menu_QueueWrite(MenuEvent_t event);
void Menu_Switch(Menu_t **pointer);

#endif /* _MENU_H_ */
