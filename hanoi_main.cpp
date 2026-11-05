// 2551470 李中 AI拔
#include <iostream>
#include <conio.h>
#include "hanoi.h"
#include "cmd_console_tools.h"
#include "cmd_hdc_tools.h"

using namespace std;

int main()
{
    int sel;
    int n;
    char from, aux, to;
    int speed;
    int ch;

    cct_setwindow(CCT_WINDOW_WIDTH, CCT_WINDOW_HEIGHT,
                  CCT_BUFFER_WIDTH, CCT_BUFFER_HEIGHT);

    for (;;) {
        hanoi_reset();
        sel = hanoi_menu() - '0';
        cout << sel << endl << endl;
        if (sel == 0) {
            break;
        }
        if (sel == 4 || sel == 8) {
            hanoi_input_params(HDC_INPUT_WITH_SPEED, &n, &from, &aux, &to, &speed);
            cct_cls();
            if (sel == 4) {
                hanoi_prepare(n, from, to, speed, HDC_VERTICAL_X, HDC_VERTICAL_Y_MODE4);
            } else {
                hanoi_prepare(n, from, to, speed, HDC_VERTICAL_X, HDC_VERTICAL_Y_MODE8);
                hanoi_draw_column(n, from, to, 0);
            }
            if (speed == 6) {
                do {
                    ch = _getch();
                } while (ch != '\r');
            }
            hanoi(n, from, aux, to, sel, speed);
            cct_gotoxy(0, HDC_PROMPT_Y);
            cout << "按回车键继续";
            do {
                ch = _getch();
            } while (ch != '\r');
        } else if (sel == 5) {
            cct_cls();
            hanoi_draw_cylinders();
            cct_gotoxy(0, HDC_PROMPT_Y);
            cout << "按回车键继续";
            do {
                ch = _getch();
            } while (ch != '\r');
        } else if (sel == 6) {
            hanoi_input_params(6, &n, &from, &aux, &to, &speed);
            cct_cls();
            hanoi_draw_column(n, from, to, 1);
            cct_gotoxy(0, HDC_PROMPT_Y);
            cout << "按回车键继续";
            do {
                ch = _getch();
            } while (ch != '\r');
        } else if (sel == 1 || sel == 2 || sel == 3) {
            hanoi_input_params(0x7b, &n, &from, &aux, &to, &speed);
            hanoi(n, from, aux, to, sel, 0);
            cout << endl << "按回车键继续";
            do {
                ch = _getch();
            } while (ch != '\r');
        } else if (sel == 7) {
            hanoi_input_params(7, &n, &from, &aux, &to, &speed);
            cct_cls();
            hanoi_first_move(n, from, aux, to);
            cct_gotoxy(0, HDC_PROMPT_Y);
            cout << "按回车键继续";
            do {
                ch = _getch();
            } while (ch != '\r');
        } else if (sel == 9) {
            hanoi_input_n(&n);
            hanoi_input_columns(&n, &from, &aux, &to);
            cct_cls();
            hanoi_game(n, from, aux, to);
            cct_gotoxy(0, HDC_PROMPT_Y);
            cout << "按回车键继续";
            do {
                ch = _getch();
            } while (ch != '\r');
        }
    }
    cout << endl << "结束" << endl;
    return 0;
}
