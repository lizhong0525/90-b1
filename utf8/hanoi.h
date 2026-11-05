// 2551470 李中 AI拔
#ifndef HANOI_H
#define HANOI_H

#include "hanoi_const_value.h"

/* 允许使用的全局变量：
   - 圆柱上现有圆盘的编号：全局二维数组 g_disk[3][10]
   - 圆柱上现有圆盘的数量：3 个全局简单变量 g_countA/B/C
   - 总移动步数：全局变量 g_step
   - 延时：由参数传递 */
extern int g_disk[3][10];
extern int g_step;
extern int g_countA, g_countB, g_countC;

/* hanoi_menu.cpp：菜单 */
int hanoi_menu();

/* hanoi_multiple_solutions.cpp：各菜单项 */
void hanoi_reset();

void hanoi_input_n(int* n);
void hanoi_input_columns(int* n, char* from, char* aux, char* to);
void hanoi_input_speed(int* speed);
void hanoi_input_params(int mode, int* n, char* from, char* aux, char* to, int* speed);

void hanoi(int n, char from, char aux, char to, int sel, int speed);
void hanoi_move(int n, char from, char aux, char to, int sel, int speed);

void hanoi_print_mode1(int n, char from, char aux, char to);
void hanoi_print_mode2(int n, char from, char aux, char to);
void hanoi_print_mode3(int n, char from, char aux, char to);
void hanoi_move_mode4(int n, char from, char aux, char to, int speed);
void hanoi_move_mode8(int n, char from, char aux, char to, int speed);

void hanoi_update(char from, char to);
void hanoi_show_array(int which, int flag, int x, int y, int n);
void hanoi_show_vertical(int which, int x, int y);
void hanoi_draw_column(int n, char from, char to, int flag);
void hanoi_prepare(int n, char from, char to, int speed, int baseX, int baseY);
void hanoi_draw_cylinders();
void hanoi_error(int err);
void hanoi_animate(int n, char from, char to, int speed);
void hanoi_first_move(int n, char from, char aux, char to);
void hanoi_game(int n, char from, char aux, char to);

#endif /* HANOI_H */
