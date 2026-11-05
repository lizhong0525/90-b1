// 2551470 李中 AI拔
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include "hanoi.h"
#include "cmd_console_tools.h"
#include "cmd_hdc_tools.h"

using namespace std;

/* 全局变量：三根立柱上现有圆盘的编号（0 表示空位） */
int g_disk[3][10];
/* 总移动步数 */
int g_step;
/* 三根立柱上现有圆盘的数量 */
int g_countA;
int g_countB;
int g_countC;

/* ---------------------------------------------------------------- */
/* 复位：清空三根立柱，步数从 1 开始                                  */
/* ---------------------------------------------------------------- */
void hanoi_reset()
{
    int i;
    for (i = 0; i < 10; i++) {
        g_disk[0][i] = 0;
        g_disk[1][i] = 0;
        g_disk[2][i] = 0;
    }
    g_countA = 0;
    g_countB = 0;
    g_countC = 0;
    g_step = 1;
}

/* ---------------------------------------------------------------- */
/* 错误提示                                                          */
/* ---------------------------------------------------------------- */
void hanoi_error(int err)
{
    if (err == 1) {
        cct_gotoxy(0, HDC_MSG_Y);
        cout << "源柱为空";
        Sleep(HDC_ERROR_DELAY);
    } else if (err == 2) {
        cct_gotoxy(0, HDC_MSG_Y);
        cout << "大盘压小盘，非法移动！！";
        Sleep(HDC_ERROR_DELAY);
    }
}

/* ---------------------------------------------------------------- */
/* 菜单项 8：自动移动版本中的一次移动（同时重画数组与动画）           */
/* ---------------------------------------------------------------- */
void hanoi_move_mode8(int n, char from, char aux, char to, int speed)
{
    hanoi_update(from, to);
    hanoi_show_array(1, 1, HDC_HORIZONTAL_X, HDC_VERTICAL_Y_MODE8 + HDC_HORIZONTAL_DY, n);
    hanoi_show_array(2, 1, HDC_HORIZONTAL_X, HDC_VERTICAL_Y_MODE8 + HDC_HORIZONTAL_DY, 0);
    hanoi_show_array(3, 1, HDC_HORIZONTAL_X, HDC_VERTICAL_Y_MODE8 + HDC_HORIZONTAL_DY, 0);
    hanoi_show_vertical(1, HDC_VERTICAL_X, HDC_VERTICAL_Y_MODE8);
    hanoi_show_vertical(2, HDC_VERTICAL_X, HDC_VERTICAL_Y_MODE8);
    hanoi_show_vertical(3, HDC_VERTICAL_X, HDC_VERTICAL_Y_MODE8);
    hanoi_animate(n, from, to, speed);
    if (speed == 6) {
        int ch;
        do {
            ch = _getch();
        } while (ch != '\r');
    } else {
        Sleep(speed * HDC_SPEED_UNIT);
    }
}

/* ---------------------------------------------------------------- */
/* 移动的分发：菜单项 1/2/3/4/8 共用                                  */
/* ---------------------------------------------------------------- */
void hanoi_move(int n, char from, char aux, char to, int sel, int speed)
{
    if (sel == 1) {
        hanoi_print_mode1(n, from, aux, to);
    } else if (sel == 2) {
        hanoi_print_mode2(n, from, aux, to);
    } else if (sel == 3) {
        hanoi_print_mode3(n, from, aux, to);
    } else if (sel == 4) {
        hanoi_move_mode4(n, from, aux, to, speed);
    } else if (sel == 8) {
        hanoi_move_mode8(n, from, aux, to, speed);
    }
}

/* ---------------------------------------------------------------- */
/* 菜单项 4：内部数组显示（纵向+横向）中的一次移动                    */
/* ---------------------------------------------------------------- */
void hanoi_move_mode4(int n, char from, char aux, char to, int speed)
{
    hanoi_update(from, to);
    hanoi_show_array(1, 1, HDC_HORIZONTAL_X, HDC_VERTICAL_Y_MODE4 + HDC_HORIZONTAL_DY, n);
    hanoi_show_array(2, 1, HDC_HORIZONTAL_X, HDC_VERTICAL_Y_MODE4 + HDC_HORIZONTAL_DY, 0);
    hanoi_show_array(3, 1, HDC_HORIZONTAL_X, HDC_VERTICAL_Y_MODE4 + HDC_HORIZONTAL_DY, 0);
    hanoi_show_vertical(1, HDC_VERTICAL_X, HDC_VERTICAL_Y_MODE4);
    hanoi_show_vertical(2, HDC_VERTICAL_X, HDC_VERTICAL_Y_MODE4);
    hanoi_show_vertical(3, HDC_VERTICAL_X, HDC_VERTICAL_Y_MODE4);
    if (speed == 6) {
        int ch;
        do {
            ch = _getch();
        } while (ch != '\r');
    } else {
        Sleep(speed * HDC_DELAY_MODE4);
    }
}

/* ---------------------------------------------------------------- */
/* 唯一的递归函数：把 n 个圆盘从 from 经 aux 移到 to                  */
/* 菜单项 1/2/3/4/8 共用，参数 sel 决定显示方式                       */
/* ---------------------------------------------------------------- */
void hanoi(int n, char from, char aux, char to, int sel, int speed)
{
    if (n == 1) {
        hanoi_move(1, from, aux, to, sel, speed);
        g_step++;
    } else {
        hanoi(n - 1, from, to, aux, sel, speed);
        hanoi_move(n, from, aux, to, sel, speed);
        g_step++;
        hanoi(n - 1, aux, from, to, sel, speed);
    }
}

/* ---------------------------------------------------------------- */
/* 横向输出内部数组：which 为柱号，flag 为是否定位，x/y 为位置，      */
/* n 为当前移动的盘子编号                                            */
/* ---------------------------------------------------------------- */
void hanoi_show_array(int which, int flag, int x, int y, int n)
{
    int i;
    if (flag != 0 && which == 1) {
        cct_gotoxy(x - 11, y);
    }
    if (which == 1) {
        cout << "第" << setw(4) << g_step << "步" << " #" << setw(2) << n << "  A:";
        for (i = 0; i < 10; i++) {
            if (g_disk[0][i] == 0) {
                cout << "  ";
            } else {
                cout << setw(2) << g_disk[0][i];
            }
        }
    }
    if (which == 2) {
        cout << " B:";
        for (i = 0; i < 10; i++) {
            if (g_disk[1][i] == 0) {
                cout << "  ";
            } else {
                cout << setw(2) << g_disk[1][i];
            }
        }
    }
    if (which == 3) {
        cout << " C:";
        for (i = 0; i < 10; i++) {
            if (g_disk[2][i] == 0) {
                cout << "  ";
            } else {
                cout << setw(2) << g_disk[2][i];
            }
        }
        cout << endl;
    }
}

/* ---------------------------------------------------------------- */
/* 纵向输出内部数组                                                  */
/* ---------------------------------------------------------------- */
void hanoi_show_vertical(int which, int x, int y)
{
    int i;
    if (which == 1) {
        cct_gotoxy(x, y);
        for (i = 0; i < 10; i++) {
            cout << "  ";
            cct_gotoxy(x, y - 1 - i);
        }
        cct_gotoxy(x, y);
        for (i = 0; i < 10; i++) {
            if (g_disk[0][i] != 0) {
                cout << setw(2) << g_disk[0][i];
            }
            cct_gotoxy(x, y - 1 - i);
        }
    }
    if (which == 2) {
        cct_gotoxy(x + HDC_VERTICAL_DX, y);
        for (i = 0; i < 10; i++) {
            cout << "  ";
            cct_gotoxy(x + HDC_VERTICAL_DX, y - 1 - i);
        }
        cct_gotoxy(x + HDC_VERTICAL_DX, y);
        for (i = 0; i < 10; i++) {
            if (g_disk[1][i] != 0) {
                cout << setw(2) << g_disk[1][i];
            }
            cct_gotoxy(x + HDC_VERTICAL_DX, y - 1 - i);
        }
    }
    if (which == 3) {
        cct_gotoxy(x + 22, y);
        for (i = 0; i < 10; i++) {
            cout << "  ";
            cct_gotoxy(x + 22, y - 1 - i);
        }
        cct_gotoxy(x + 22, y);
        for (i = 0; i < 10; i++) {
            if (g_disk[2][i] != 0) {
                cout << setw(2) << g_disk[2][i];
            }
            cct_gotoxy(x + 22, y - 1 - i);
        }
        cout << endl;
    }
}

/* ---------------------------------------------------------------- */
/* 图形解动画：把当前顶端圆盘从 from 柱移动到 to 柱。                  */
/* 分三段：上升、水平移动、下降；每个像素步进延时 speed%5*100 毫秒。   */
/* ---------------------------------------------------------------- */
void hanoi_animate(int n, char from, char to, int speed)
{
    int v;                    /* 被移动圆盘的编号（宽度 = 2*v+1） */
    int x, targetX, y, firstY;
    int delay;
    int i;
    int fi = from - 'A';
    int ti = to - 'A';
    int countFrom;
    int countTo;

    if (fi == 0) countFrom = g_countA;
    else if (fi == 1) countFrom = g_countB;
    else countFrom = g_countC;
    if (ti == 0) countTo = g_countA;
    else if (ti == 1) countTo = g_countB;
    else countTo = g_countC;

    v = g_disk[ti][countTo - 1];
    x = HDC_COL_A_X + fi * HDC_COL_STEP;
    targetX = HDC_COL_A_X + ti * HDC_COL_STEP;
    y = (16 - countFrom) - 1;
    firstY = y;
    delay = (speed % HDC_SPEED_MOD) * HDC_SPEED_UNIT;

    /* 第一段：向上移动到第 3 行 */
    for (; y > 2; y--) {
        if (y == firstY) {
            hdc_putchar(x - v, y, ' ', v, v + HDC_COLOR_DISK_SHIFT, v * 2 + 1);
        } else {
            hdc_putchar(x - v, y, ' ', v, v + HDC_COLOR_DISK_SHIFT, v * 2 + 1);
            hdc_putchar(x - v, y + 1, ' ', HDC_COLOR_BLACK, HDC_COLOR_WHITE, v * 2 + 1);
            hdc_putchar(x, y + 1, ' ', HDC_COLOR_POLE_BK, HDC_COLOR_POLE_TEXT, 1);
        }
        Sleep(delay);
    }
    y += 1;

    /* 第二段：水平移动到目标柱 */
    if (x < targetX) {
        for (; x < targetX + 1; x++) {
            hdc_putchar(x - v - 1, y, ' ', HDC_COLOR_BLACK, HDC_COLOR_WHITE, v * 2 + 1);
            hdc_putchar(x - v, y, ' ', v, v + HDC_COLOR_DISK_SHIFT, v * 2 + 1);
            Sleep(delay);
        }
        x -= 1;
    } else {
        for (; x > targetX - 1; x--) {
            hdc_putchar(x - v + 1, y, ' ', HDC_COLOR_BLACK, HDC_COLOR_WHITE, v * 2 + 1);
            hdc_putchar(x - v, y, ' ', v, v + HDC_COLOR_DISK_SHIFT, v * 2 + 1);
            Sleep(delay);
        }
        x += 1;
    }

    /* 第三段：向下落到目标柱顶端 */
    for (i = 0; i < (1 + 12) - countTo; i++) {
        y += 1;
        if (i == 0) {
            hdc_putchar(x - v, y - 1, ' ', HDC_COLOR_BLACK, HDC_COLOR_WHITE, v * 2 + 1);
            hdc_putchar(x - v, y, ' ', v, v + HDC_COLOR_DISK_SHIFT, v * 2 + 1);
        } else {
            hdc_putchar(x - v, y, ' ', v, v + HDC_COLOR_DISK_SHIFT, v * 2 + 1);
            hdc_putchar(x - v, y - 1, ' ', HDC_COLOR_BLACK, HDC_COLOR_WHITE, v * 2 + 1);
            hdc_putchar(x, y - 1, ' ', HDC_COLOR_POLE_BK, HDC_COLOR_POLE_TEXT, 1);
        }
        Sleep(delay);
    }
    cct_setcolor(HDC_COLOR_BLACK, HDC_COLOR_WHITE);
}
/* ---------------------------------------------------------------- */
/* 用户输入：层数                                                    */
/* ---------------------------------------------------------------- */
void hanoi_input_n(int* n)
{
    for (;;) {
        cout << "请输入汉诺塔的层数(1-10)" << endl;
        cin >> *n;
        if (cin.good() && *n >= 1 && *n <= 10) {
            cin.clear();
            cin.ignore(2048, '\n');
            break;
        } else {
            cin.clear();
            cin.ignore(2048, '\n');
        }
    }
}

/* ---------------------------------------------------------------- */
/* 用户输入：起始柱与目标柱，同时算出辅助柱并初始化起始柱上的圆盘     */
/* ---------------------------------------------------------------- */
void hanoi_input_columns(int* n, char* from, char* aux, char* to)
{
    int i;
    for (;;) {
        cout << "请输入起始柱(A-C)" << endl;
        cin >> *from;
        if (cin.good() && ((*from > '@' && *from < 'D') ||
                           (*from > '`' && *from < 'd'))) {
            break;
        }
        cin.clear();
        cin.ignore(2048, '\n');
    }
    if (*from < 'A' || *from > 'C') {
        cin.clear();
        cin.ignore(2048, '\n');
        *from = *from - 0x20;
    } else {
        cin.clear();
        cin.ignore(2048, '\n');
    }

    for (;;) {
        cout << "请输入目标柱(A-C)" << endl;
        cin >> *to;
        if (cin.good() && (*to > '@') &&
            ((*to < 'D') || (*to > '`' && *to < 'd'))) {
            if (*to == *from || *to == *from + 0x20) {
                cout << "目标柱(" << *to << ")不能与起始柱(" << *from << ")相同" << endl;
                cin.clear();
                cin.ignore(2048, '\n');
                continue;
            }
            break;
        }
        cin.clear();
        cin.ignore(2048, '\n');
    }
    if (*to < 'A' || *to > 'C') {
        cin.clear();
        cin.ignore(2048, '\n');
        *to = *to - 0x20;
    } else {
        cin.clear();
        cin.ignore(2048, '\n');
    }

    if (*from == 'A') {
        g_countA = *n;
        for (i = 0; i < *n; i++) {
            g_disk[0][i] = *n - i;
        }
    } else if (*from == 'B') {
        g_countB = *n;
        for (i = 0; i < *n; i++) {
            g_disk[1][i] = *n - i;
        }
    } else if (*from == 'C') {
        g_countC = *n;
        for (i = 0; i < *n; i++) {
            g_disk[2][i] = *n - i;
        }
    }

    if ((*from == 'A' && *to == 'B') || (*from == 'B' && *to == 'A')) {
        *aux = 'C';
    } else if ((*from == 'A' && *to == 'C') || (*from == 'C' && *to == 'A')) {
        *aux = 'B';
    } else if ((*from == 'C' && *to == 'B') || (*from == 'B' && *to == 'C')) {
        *aux = 'A';
    }
}

/* ---------------------------------------------------------------- */
/* 用户输入：移动速度                                                */
/* ---------------------------------------------------------------- */
void hanoi_input_speed(int* speed)
{
    for (;;) {
        cout << "请输入移动速度(0-5: 0-按回车单步演示 1-延时最长 5-延时最短)" << endl;
        cin >> *speed;
        if (cin.good() && *speed > -1 && *speed < 6) {
            break;
        }
        cin.clear();
        cin.ignore(2048, '\n');
    }
    cin.clear();
    cin.ignore(2048, '\n');
    *speed = 6 - *speed;
}

/* ---------------------------------------------------------------- */
/* 菜单项 1/2/3/4/6/7/8 共用的多参数输入函数                         */
/* ---------------------------------------------------------------- */
void hanoi_input_params(int mode, int* n, char* from, char* aux, char* to, int* speed)
{
    if (mode == HDC_INPUT_WITH_SPEED) {
        hanoi_input_n(n);
        hanoi_input_columns(n, from, aux, to);
        hanoi_input_speed(speed);
    } else {
        hanoi_input_n(n);
        hanoi_input_columns(n, from, aux, to);
    }
}

/* ---------------------------------------------------------------- */
/* 菜单项 1：基本解                                                  */
/* ---------------------------------------------------------------- */
void hanoi_print_mode1(int n, char from, char aux, char to)
{
    cout << n << "#: " << from << "---->" << to << endl;
}

/* ---------------------------------------------------------------- */
/* 菜单项 2：基本解（步数记录）                                      */
/* ---------------------------------------------------------------- */
void hanoi_print_mode2(int n, char from, char aux, char to)
{
    cout << "第" << setw(4) << g_step << " 步(" << setw(2) << n << "): "
         << from << "-->" << to << endl;
}

/* ---------------------------------------------------------------- */
/* 菜单项 3：内部数组显示（横向）                                    */
/* ---------------------------------------------------------------- */
void hanoi_print_mode3(int n, char from, char aux, char to)
{
    hanoi_update(from, to);
    hanoi_show_array(1, 0, 0, 0, n);
    hanoi_show_array(2, 0, 0, 0, 0);
    hanoi_show_array(3, 0, 0, 0, 0);
}

/* ---------------------------------------------------------------- */
/* 圆形数组更新：把 from 柱顶端的圆盘移到 to 柱                      */
/* ---------------------------------------------------------------- */
void hanoi_update(char from, char to)
{
    if (from == 'A') {
        if (to == 'B') {
            g_disk[1][g_countB] = g_disk[0][g_countA - 1];
            g_disk[0][g_countA - 1] = 0;
            g_countA = g_countA - 1;
            g_countB = g_countB + 1;
        } else if (to == 'C') {
            g_disk[2][g_countC] = g_disk[0][g_countA - 1];
            g_disk[0][g_countA - 1] = 0;
            g_countA = g_countA - 1;
            g_countC = g_countC + 1;
        }
    }
    if (from == 'B') {
        if (to == 'A') {
            g_disk[0][g_countA] = g_disk[1][g_countB - 1];
            g_disk[1][g_countB - 1] = 0;
            g_countB = g_countB - 1;
            g_countA = g_countA + 1;
        } else if (to == 'C') {
            g_disk[2][g_countC] = g_disk[1][g_countB - 1];
            g_disk[1][g_countB - 1] = 0;
            g_countB = g_countB - 1;
            g_countC = g_countC + 1;
        }
    }
    if (from == 'C') {
        if (to == 'A') {
            g_disk[0][g_countA] = g_disk[2][g_countC - 1];
            g_disk[2][g_countC - 1] = 0;
            g_countC = g_countC - 1;
            g_countA = g_countA + 1;
        } else if (to == 'B') {
            g_disk[1][g_countB] = g_disk[2][g_countC - 1];
            g_disk[2][g_countC - 1] = 0;
            g_countC = g_countC - 1;
            g_countB = g_countB + 1;
        }
    }
}

/* ---------------------------------------------------------------- */
/* 在指定立柱上画出 n 个圆盘（菜单项 6 以及 7/8/9 的起始画面）        */
/* flag 为 1 时先输出一行说明                                        */
/* ---------------------------------------------------------------- */
void hanoi_draw_column(int n, char from, char to, int flag)
{
    int x, y, c;

    if (flag == 1) {
        cout << "从 " << from << "移动到 " << to << "，共" << setw(2) << n << "层" << endl;
    }
    hanoi_draw_cylinders();
    x = (from - 'A') * HDC_COL_STEP + HDC_COL_A_X;
    y = HDC_POLE_BOTTOM_Y;
    for (c = 0; c < n; c++) {
        hdc_putchar(x - (n - c), y, ' ', n - c, n - c + HDC_COLOR_DISK_SHIFT,
                    (n - c) * 2 + 1);
        Sleep(HDC_DELAY_PREP);
        y = y - 1;
    }
    cct_setcolor(HDC_COLOR_BLACK, HDC_COLOR_WHITE);
}

/* ---------------------------------------------------------------- */
/* 画出三个圆柱：底座 + 立柱（立柱逐行向上生长，带延时）              */
/* ---------------------------------------------------------------- */
void hanoi_draw_cylinders()
{
    int x, y, i, j;

    x = HDC_BASE_START_X;
    y = HDC_BASE_Y;
    for (i = 0; i < 3; i++) {
        hdc_putchar(x, y, ' ', HDC_COLOR_POLE_BK, HDC_COLOR_POLE_TEXT, HDC_BASE_WIDTH);
        x = x + HDC_COL_STEP;
    }
    y = HDC_POLE_BOTTOM_Y;
    for (i = 0; i < 12; i++) {
        x = HDC_COL_A_X;
        for (j = 0; j < 3; j++) {
            hdc_putchar(x, y, ' ', HDC_COLOR_POLE_BK, HDC_COLOR_POLE_TEXT, 1);
            Sleep(HDC_DELAY_PREP);
            x = x + HDC_COL_STEP;
        }
        y = y - 1;
    }
    cct_setcolor(HDC_COLOR_BLACK, HDC_COLOR_WHITE);
}

/* ---------------------------------------------------------------- */
/* 图形解预备画面：说明行 + 横向数组 + 竖直数组 + 底座与柱名          */
/* baseX/baseY 为竖直数组显示的基准坐标                              */
/* ---------------------------------------------------------------- */
void hanoi_prepare(int n, char from, char to, int speed, int baseX, int baseY)
{
    int ch;

    cout << "从 " << from << "移动到 " << to << "，共" << setw(2) << n
         << "层，延时设置为 " << (6 - speed) << endl;
    hanoi_show_array(1, 1, baseX + 12, baseY + HDC_HORIZONTAL_DY, 0);
    cct_gotoxy(baseX + 1, baseY + HDC_HORIZONTAL_DY);
    cout << "       起始：";
    cct_gotoxy(baseX + 0x25, baseY + HDC_HORIZONTAL_DY);
    hanoi_show_array(2, 1, baseX + 12, baseY + HDC_HORIZONTAL_DY, 0);
    hanoi_show_array(3, 1, baseX + 12, baseY + HDC_HORIZONTAL_DY, 0);
    if (speed == 0) {
        do {
            ch = _getch();
        } while (ch != '\r');
    }
    cct_gotoxy(baseX, baseY + 1);
    cout << setfill('=') << setw(26) << ' ' << setfill(' ');
    cct_gotoxy(baseX + 1, baseY + 2);
    cout << "A";
    cct_gotoxy(baseX + 12, baseY + 2);
    cout << "B";
    cct_gotoxy(baseX + 23, baseY + 2);
    cout << "C";
    hanoi_show_vertical(1, baseX, baseY);
    hanoi_show_vertical(2, baseX, baseY);
    hanoi_show_vertical(3, baseX, baseY);
}

/* ---------------------------------------------------------------- */
/* 菜单项 7：图形解-预备-第一次移动                                  */
/* ---------------------------------------------------------------- */
void hanoi_first_move(int n, char from, char aux, char to)
{
    hanoi_draw_column(n, from, to, 1);
    if (n % 2 == 0) {
        hanoi_update(from, aux);
        hanoi_animate(n, from, aux, 1);
    } else {
        hanoi_update(from, to);
        hanoi_animate(n, from, to, 1);
    }
}

/* ---------------------------------------------------------------- */
/* 菜单项 9：图形解-游戏版                                           */
/* ---------------------------------------------------------------- */
void hanoi_game(int n, char from, char aux, char to)
{
    char buf[100];
    int target;
    int i;
    int ch;
    char src, dst;

    target = (int)to - 0x40;
    hanoi_prepare(n, from, to, 1, HDC_VERTICAL_X, HDC_VERTICAL_Y_MODE8);
    hanoi_draw_column(n, from, to, 0);
    cct_gotoxy(0, 0x23);
    cout << "请输入移动的柱号（命令形式：AC=A顶端的盘子移动到C，Q=退出）：";

    for (;;) {
        memset(buf, 0, 100);
        hdc_putchar(0x3b, 0x23, ' ', HDC_COLOR_BLACK, HDC_COLOR_WHITE, HDC_CMD_CLEAR_LEN);
        hdc_putchar(0, 0x24, ' ', HDC_COLOR_BLACK, HDC_COLOR_WHITE, HDC_CMD_CLEAR_LEN);
        cct_gotoxy(0x3b, 0x23);
        for (i = 0; i < 100; i++) {
            ch = cin.get();
            buf[i] = (char)ch;
            if (buf[i] == '\n') {
                break;
            }
        }
        if ((buf[0] == 'q' || buf[0] == 'Q') && buf[1] == '\n') {
            cct_gotoxy(0, 0x24);
            cout << "游戏终止！！";
            return;
        }
        if (buf[2] != '\n' || buf[0] == buf[1]) {
            continue;
        }
        if (buf[0] == 'A' || buf[0] == 'a') {
            src = 'A';
            if (buf[1] == 'B' || buf[1] == 'b') dst = 'B';
            else if (buf[1] == 'C' || buf[1] == 'c') dst = 'C';
            else continue;
        } else if (buf[0] == 'B' || buf[0] == 'b') {
            src = 'B';
            if (buf[1] == 'A' || buf[1] == 'a') dst = 'A';
            else if (buf[1] == 'C' || buf[1] == 'c') dst = 'C';
            else continue;
        } else if (buf[0] == 'C' || buf[0] == 'c') {
            src = 'C';
            if (buf[1] == 'A' || buf[1] == 'a') dst = 'A';
            else if (buf[1] == 'B' || buf[1] == 'b') dst = 'B';
            else continue;
        } else {
            continue;
        }

        {
            int *cntSrc;
            int *cntDst;
            int *arrSrc;
            int *arrDst;
            if (src == 'A') { arrSrc = g_disk[0]; cntSrc = &g_countA; }
            else if (src == 'B') { arrSrc = g_disk[1]; cntSrc = &g_countB; }
            else { arrSrc = g_disk[2]; cntSrc = &g_countC; }
            if (dst == 'A') { arrDst = g_disk[0]; cntDst = &g_countA; }
            else if (dst == 'B') { arrDst = g_disk[1]; cntDst = &g_countB; }
            else { arrDst = g_disk[2]; cntDst = &g_countC; }

            if (arrSrc[0] == 0) {
                hanoi_error(1);
                continue;
            }
            if (*cntDst != 0 && arrDst[*cntDst - 1] < arrSrc[*cntSrc - 1]) {
                hanoi_error(2);
                continue;
            }
            hanoi_move_mode8(arrSrc[*cntSrc - 1], src, aux, dst, 1);
        }
        g_step = g_step + 1;
        if (target == 1 && g_countA == n) {
            cct_gotoxy(1, 0x24);
            cout << "游戏结束！！";
            return;
        }
        if (target == 2 && g_countB == n) {
            cct_gotoxy(1, 0x24);
            cout << "游戏结束！！";
            return;
        }
        if (target == 3 && g_countC == n) {
            cct_gotoxy(1, 0x24);
            cout << "游戏结束！！";
            return;
        }
    }
}
