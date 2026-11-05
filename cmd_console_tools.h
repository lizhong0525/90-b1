// 2551470 李中 AI拔
#ifndef CMD_CONSOLE_TOOLS_H
#define CMD_CONSOLE_TOOLS_H

#include <windows.h>

/* 控制台标准句柄（启动时由全局对象初始化） */
extern HANDLE hConsoleIn;
extern HANDLE hConsoleOut;

/* 清屏：用当前属性清空整个缓冲区并把光标移回左上角 */
void cct_cls();

/* 光标定位/读取 */
void cct_gotoxy(int x, int y);
void cct_getxy(int* px, int* py);

/* 窗口与缓冲区尺寸 */
void cct_getwindowrect(int* pw, int* ph, int* pbw, int* pbh);
void cct_setwindow(int w, int h, int bw, int bh);

/* 颜色 */
void cct_getcolor(int* pbk, int* pfg);
void cct_setcolor(int bk, int fg);

/* 标题 */
void cct_settitle(const char* title);
void cct_gettitle(char* buffer, DWORD size);

/* 光标形状：0 大，1 中，2 小，3 隐藏 */
void cct_setcursor(int type);

/* 字体：按序号（旧的控制台 API）或按名称+点阵尺寸 */
void cct_setfontsize(int index);
void cct_setfont(const char* name, int height, int width);

/* 鼠标输入开关（控制台输入模式） */
void cct_mouse_disable();
void cct_mouse_enable();

/* 控制台输入：返回 0 表示鼠标事件，1 表示键盘事件 */
int cct_getinput(int* pmx, int* pmy, int* pkey, int* pch1, int* pch2);

/* 显示当前控制台字体信息（库中的演示/调试函数） */
void cct_show_font_info();

#endif /* CMD_CONSOLE_TOOLS_H */
