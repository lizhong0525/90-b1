// 2551470 李中 AI拔
#include <iostream>
#include <conio.h>
#include "hanoi.h"
#include "cmd_console_tools.h"

using namespace std;

/* 显示菜单并等待用户按 0-9 键，返回所按键的 ASCII 码。 */
int hanoi_menu()
{
    int key;

    for (;;) {
        cct_cls();
        cout << "1.基本解" << endl;
        cout << "2.基本解（步数记录）" << endl;
        cout << "3.内部数组显示（横向）" << endl;
        cout << "4.内部数组显示（纵向+横向）" << endl;
        cout << "5.图形解-预备-画三个圆柱" << endl;
        cout << "6.图形解-预备-在起始柱上画n个盘子" << endl;
        cout << "7.图形解-预备-第一次移动" << endl;
        cout << "8.图形解-自动移动版本" << endl;
        cout << "9.图形解-游戏版" << endl;
        cout << "0.退出" << endl;
        cout << "请选择[0-9] ";
        key = _getch();
        if (key >= '0' && key <= '9') {
            break;
        }
    }
    return key;
}
