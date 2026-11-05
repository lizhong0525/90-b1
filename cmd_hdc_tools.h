// 2551470 李中 AI拔
#ifndef CMD_HDC_TOOLS_H
#define CMD_HDC_TOOLS_H

/* 伪图形界面（HDC：字符单元格模拟的图形界面）基本绘图函数。
   所有坐标均以控制台字符单元格为单位，(x, y) 为左上角。 */

/* 在 (x, y) 处连续输出 count 个字符 ch，使用背景色 bk、前景色 fg */
void hdc_putchar(int x, int y, char ch, int bk, int fg, int count);

/* 在 (x, y) 处连续输出 count 个整数 value */
void hdc_putint(int x, int y, int value, int bk, int fg, int count);

/* 在 (x, y) 处输出字符串（按 repeat 重复、用空格补齐到 count 个字符） */
void hdc_putstr(int x, int y, const char* str, int bk, int fg, int repeat, int count);

/* 无输入时返回 -1（原库中的取键函数） */
int hdc_getch();

/* 什么也不做 */
void hdc_nop();

/* 取字符串长度 */
int hdc_strlen(const char* str);

/* 比较两个整数是否相等 */
int hdc_equal(int a, int b);

/* 复制 count 个宽字符（2 字节） */
void hdc_memcopy(void* dest, const void* src, int count);

#endif /* CMD_HDC_TOOLS_H */