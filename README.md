# 简介
纯软件实现，代码不到200行，支持任意平台，任意深度，无需修改一行代码, 事件驱动(通过事件枚举)
# 原理:
全局创建多个 Menu_t指定 Menu_t 项内容, 再创建 Menu_t 指针(Menu_t *pxStart), 通过修改 pxStart 指针，调用回调函数实现
通过修改指针指向，调用对应回调函数实现菜单
# 使用指南:

1. 创建本体
  创建一个 Menu_t 为初始项第一项 MenuItem_t *menu，例:
  extern Menu_t menuOneSub1[];
  MenuItem_t menuItem[] = {
      {.name = "Item1", .namelen = 5},
      {.name = "Item2", .namelen = 5},
      {.name = "Item3", .namelen = 5},
      {.name = "Item4", .namelen = 5},
      {.name = "Item5", .namelen = 5},
      {.name = "Item6", .namelen = 5},
  };

  /* 开始菜单 */
  Menu_t menuOne = {
      .menu = menuItem,
      .index = 0,
      .itemlen = 6,
      .submenu = menuOneSub1,
      .parentmenu = NULL,
      .callback = Menu_Example1Callback,
  };

  /* 子菜单本体 */
  Menu_t one[] = {
      {Item1, 0, 5, NULL, &startMenu, NULL},
      {NULL, 0, 0, NULL, &startMenu, NULL},
      {NULL, 0, 0, NULL, &startMenu, NULL},
      {NULL, 0, 0, NULL, &startMenu, NULL},
      {NULL, 0, 0, NULL, &startMenu, NULL},
      {NULL, 0, 0, NULL, &startMenu, NULL},
  };

  void Menu_Example1Callback(MenuItem_t *menu, uint8_t index, uint8_t itemlen)
  {
      // 具体实现, 例:ShowXXX(xxx, xx, xxx);
  }

  menu 作为 callback 回调的参数传入实际并不重要, 主要用于绘制图像或文本UI
  index 重要，作为索引不能大于 itemlen，主要于指向选中菜单
  itemlen 重要，指示当前菜单的子菜单个数, 需要于 submenu 一致，否则有数组越界风险
  submenu 重要，指示当前菜单的子菜单本体
  parentmenu 为当前菜单的父菜单，如果作为第一项菜单没有父菜单那么置 NULL
  callback 回调函数，用于显示UI或对应进入菜单动作，无则置 NULL

  # 注意
  callback 不仅仅只用于显示UI或对应进入菜单动作, 还指示是否可以进入菜单本体置 NULL 则无法进入

2. 使用函数
  提供 Menu_QueueWrite, Menu_Switch 函数
  1. Menu_QueueWrite 函数
    Menu_QueueWrite 函数用于写入菜单事件, 例如:
    Menu_QueueWrite(NEXT_ITEM);    // 进入同级菜单下一项
    Menu_QueueWrite(ENTRANCE_SUB); // 进入菜单项下选中的子菜单
  2. Menu_Switch 函数
    使用函数必须创建 Menu_t 指针，指向开始的菜单, 例:
    Menu_t *pxStart = &menuOne;
    Menu_Switch(&pxStart);          // 传入pxStart地址

  # 注意
  Menu_Switch 函数放在主循环调用, 不需要手动更改 pxStart 指向
  Menu_Switch 托管了这些操作
## 完整伪代码
# 某 .c 文件
  #include "Menu.c"

  extern Menu_t menuOneSub1[];
  
  MenuItem_t menuItem[] = {
      {.name = "Item1", .namelen = 5},
      {.name = "Item2", .namelen = 5},
      {.name = "Item3", .namelen = 5},
      {.name = "Item4", .namelen = 5},
      {.name = "Item5", .namelen = 5},
      {.name = "Item6", .namelen = 5},
  };

  /* 开始菜单 */
  Menu_t menuOne = {
      .menu = menuItem,
      .index = 0,
      .itemlen = 6,
      .submenu = menuOneSub1,
      .parentmenu = NULL,
      .callback = Menu_Example1Callback,
  };

  /* 子菜单本体 */
  Menu_t one[] = {
      {Item1, 0, 5, NULL, &startMenu, Menu_ExampleOne_1_Callback},
      {NULL, 0, 0, NULL, &startMenu, Menu_ExampleOne_2_Callback},
      {NULL, 0, 0, NULL, &startMenu, Menu_ExampleOne_3_Callback},
      {NULL, 0, 0, NULL, &startMenu, Menu_ExampleOne_4_Callback},
      {NULL, 0, 0, NULL, &startMenu, Menu_ExampleOne_5_Callback},
      {NULL, 0, 0, NULL, &startMenu, Menu_ExampleOne_6_Callback},
  };

  Menu_t *pxStart = &menuOne;

  void Menu_Example1Callback(MenuItem_t *menu, uint8_t index, uint8_t itemlen)
  {
      // 具体实现, 例:ShowXXX(xxx, xx, xxx);
  }
 
  void Menu_ExampleOne_1_Callback(MenuItem_t *menu, uint8_t index, uint8_t itemlen)
  {
      // 具体实现, 例:ShowXXX(xxx, xx, xxx);
  }
  
  void Menu_ExampleOne_2_Callback(MenuItem_t *menu, uint8_t index, uint8_t itemlen)
  {
      // 具体实现, 例:ShowXXX(xxx, xx, xxx);
  }
  
  void Menu_ExampleOne_3_Callback(MenuItem_t *menu, uint8_t index, uint8_t itemlen)
  {
      // 具体实现, 例:ShowXXX(xxx, xx, xxx);
  }
  
  void Menu_ExampleOne_4_Callback(MenuItem_t *menu, uint8_t index, uint8_t itemlen)
  {
      // 具体实现, 例:ShowXXX(xxx, xx, xxx);
  }
  
  void Menu_ExampleOne_5_Callback(MenuItem_t *menu, uint8_t index, uint8_t itemlen)
  {
      // 具体实现, 例:ShowXXX(xxx, xx, xxx);
  }
  
  void Menu_ExampleOne_6_Callback(MenuItem_t *menu, uint8_t index, uint8_t itemlen)
  {
      // 具体实现, 例:ShowXXX(xxx, xx, xxx);
  }

# 主函数

#include "Menu.c"

extern Menu_t *pxStart;

int main(void)
{
  xx_Key_Init();
  xx_Oled_Inie();

  while (1)
  {
    if (xx_Key1_GetVal() == 短按) {
      Menu_QueueWrite(NEXT_ITEM);      // 下一项
    } else if (xx_Key1_GetVal() == 长按)  {
      Menu_QueueWrite(ENTRANCE_SUB);   // 进入子菜单
    }

    if (xx_Key2_GetVal() == 短按) {
      Menu_QueueWrite(PREV_ITEM);      // 上一项
    } else if (xx_Key2_GetVal() == 长按) {
      Menu_QueueWrite(ENTRANCE_PARENT);// 退出子菜单
    }

    Menu_Switch(&pxStart);
  }
  return -1;
}

  
