// 2551470 李中 AI拔
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "cmd_console_tools.h"
#include "cmd_hdc_tools.h"

using namespace std;

/* 在 (x, y) 处连续输出 count 个字符 ch，使用背景色 bk、前景色 fg。 */
void hdc_putchar(int x, int y, char ch, int bk, int fg, int count)
{
    int i;
    cct_gotoxy(x, y);
    cct_setcolor(bk, fg);
    for (i = 0; i < count; i++) {
        putchar(ch);
    }
}

/* 在 (x, y) 处连续输出 count 个整数 value。 */
void hdc_putint(int x, int y, int value, int bk, int fg, int count)
{
    int i;
    cct_gotoxy(x, y);
    cct_setcolor(bk, fg);
    for (i = 0; i < count; i++) {
        cout << value;
    }
}

/* 在 (x, y) 处输出字符串：每个字符重复 repeat 次，总长补齐到 count 个字符。
   count 为负时按字符串长度 * repeat 计算；字符串为空时输出 count 个空格。 */
void hdc_putstr(int x, int y, const char* str, int bk, int fg, int repeat, int count)
{
    int i, loop;
    const char* p;

    cct_gotoxy(x, y);
    cct_setcolor(bk, fg);
    if (str == NULL || *str == '\0') {
        for (i = 0; i < count; i++) {
            putchar(' ');
        }
        return;
    }
    if (repeat < 1) {
        repeat = 1;
    }
    if (count < 0) {
        count = (int)strlen(str) * repeat;
    }
    p = str;
    loop = 0;
    for (i = 0; i < count; i++) {
        if (*p == '\0') {
            p = str;
            loop++;
        }
        if (loop < repeat) {
            putchar(*p);
        } else {
            putchar(' ');
        }
        p++;
    }
}

/* 无输入时返回 -1（原库中的取键函数） */
int hdc_getch()
{
    return -1;
}

/* 什么也不做 */
void hdc_nop()
{
}

/* 取字符串长度 */
int hdc_strlen(const char* str)
{
    return (int)strlen(str);
}

/* 比较两个整数是否相等 */
int hdc_equal(int a, int b)
{
    return a == b;
}

/* 复制 count 个宽字符（每个 2 字节） */
void hdc_memcopy(void* dest, const void* src, int count)
{
    memcpy(dest, src, count << 1);
}