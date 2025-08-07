#include "stdio.h"
#include "MyMenu.h"
#include <stdlib.h>
#include <windows.h>

extern Menu_t *menu;

int main() {
    system("chcp 65001 > nul");// chcp 65001
    char event = '0';
    for (;;) {
        switch (event) {
            case '1':
                Menu_QueueWrite(ENTRANCE_PARENT);
                break;
            case '2':
                Menu_QueueWrite(ENTRANCE_SUB);
                break;
            case '3':
                Menu_QueueWrite(PREV_ITEM);
                break;
            case '4':
                Menu_QueueWrite(NEXT_ITEM);
                break;
            case '5':
                return 1;
                break;
            default:
                break;
        }
        Menu_Switch(&menu);
        printf("1.返回上级菜单\n2.进入子菜单\n3.上一项\n4.下一项\n5.退出\n");
        printf("event:");
        scanf("%c", &event);
        system("cls");
    }
    return 0;
}
