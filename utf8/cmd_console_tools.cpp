// 2551470 李中 AI拔
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "cmd_console_tools.h"

/* 标准输入/输出句柄：与库中全局对象一样在程序启动时初始化 */
HANDLE hConsoleIn  = GetStdHandle(STD_INPUT_HANDLE);
HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);

/* 清屏：以当前属性填满整个缓冲区，并把光标移到左上角 */
void cct_cls()
{
    COORD home;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD written;

    home.X = 0;
    home.Y = 0;
    GetConsoleScreenBufferInfo(hConsoleOut, &csbi);
    FillConsoleOutputCharacterW(hConsoleOut, L' ',
        (int)csbi.dwSize.X * (int)csbi.dwSize.Y, home, &written);
    FillConsoleOutputAttribute(hConsoleOut, csbi.wAttributes,
        (int)csbi.dwSize.X * (int)csbi.dwSize.Y, home, &written);
    SetConsoleCursorPosition(hConsoleOut, home);
}

/* 光标定位 */
void cct_gotoxy(int x, int y)
{
    COORD pos;
    pos.X = (SHORT)x;
    pos.Y = (SHORT)y;
    SetConsoleCursorPosition(hConsoleOut, pos);
}

/* 读取当前光标位置 */
void cct_getxy(int* px, int* py)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsoleOut, &csbi);
    *px = (int)csbi.dwCursorPosition.X;
    *py = (int)csbi.dwCursorPosition.Y;
}

/* 读取当前颜色：背景色、前景色 */
void cct_getcolor(int* pbk, int* pfg)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsoleOut, &csbi);
    *pbk = (int)(csbi.wAttributes >> 4);
    *pfg = (int)(csbi.wAttributes & 0x0f);
}

/* 设置颜色：参数依次为背景色、前景色 */
void cct_setcolor(int bk, int fg)
{
    SetConsoleTextAttribute(hConsoleOut, (WORD)(bk * 16 + fg));
}

/* 读取窗口宽高与缓冲区宽高 */
void cct_getwindowrect(int* pw, int* ph, int* pbw, int* pbh)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsoleOut, &csbi);
    *pw  = (csbi.srWindow.Right - csbi.srWindow.Left) + 1;
    *ph  = (csbi.srWindow.Bottom - csbi.srWindow.Top) + 1;
    *pbw = (int)csbi.dwSize.X;
    *pbh = (int)csbi.dwSize.Y;
}

/* 设置控制台窗口大小与缓冲区大小。
   w/h 为窗口尺寸；bw/bh 为缓冲区尺寸（-1 表示取窗口尺寸）。 */
void cct_setwindow(int w, int h, int bw, int bh)
{
    COORD largest;
    SMALL_RECT rect;
    COORD bufSize;
    COORD cur;                 /* 当前缓冲区尺寸 */
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int winW, winH, curW, curH;

    largest = GetLargestConsoleWindowSize(hConsoleOut);
    if (w > 0 && h > 0) {
        if (w > largest.X) w = (int)largest.X;
        if (h > largest.Y) h = (int)largest.Y;

        rect.Left = 0;
        rect.Top = 0;
        rect.Right = (SHORT)(w - 1);
        rect.Bottom = (SHORT)(h - 1);

        bufSize.X = (SHORT)w;
        if (bw != -1 && w <= bw) bufSize.X = (SHORT)bw;
        bufSize.Y = (SHORT)h;
        if (bh != -1 && h <= bh) bufSize.Y = (SHORT)bh;

        GetConsoleScreenBufferInfo(hConsoleOut, &csbi);
        winW = (csbi.srWindow.Right - csbi.srWindow.Left) + 1;
        winH = (csbi.srWindow.Bottom - csbi.srWindow.Top) + 1;
        curW = (int)csbi.dwSize.X;
        curH = (int)csbi.dwSize.Y;

        cct_cls();

        if (curW < bufSize.X) {
            if (bufSize.Y < curH) {
                cur.X = bufSize.X;
                cur.Y = (SHORT)curH;
                SetConsoleScreenBufferSize(hConsoleOut, cur);
                SetConsoleWindowInfo(hConsoleOut, TRUE, &rect);
                SetConsoleScreenBufferSize(hConsoleOut, bufSize);
            } else {
                SetConsoleScreenBufferSize(hConsoleOut, bufSize);
                SetConsoleWindowInfo(hConsoleOut, TRUE, &rect);
            }
        } else if (curH < bufSize.Y) {
            cur.X = (SHORT)curW;
            cur.Y = bufSize.Y;
            SetConsoleScreenBufferSize(hConsoleOut, cur);
            SetConsoleWindowInfo(hConsoleOut, TRUE, &rect);
            SetConsoleScreenBufferSize(hConsoleOut, bufSize);
        } else {
            SetConsoleWindowInfo(hConsoleOut, TRUE, &rect);
            SetConsoleScreenBufferSize(hConsoleOut, bufSize);
        }
    }
}

/* 设置标题 */
void cct_settitle(const char* title)
{
    SetConsoleTitleA(title);
}

/* 读取标题 */
void cct_gettitle(char* buffer, DWORD size)
{
    GetConsoleTitleA(buffer, size);
}

/* 设置光标形状 */
void cct_setcursor(int type)
{
    CONSOLE_CURSOR_INFO info;
    switch (type) {
    case 0:
        info.bVisible = TRUE;
        info.dwSize = 100;
        break;
    case 1:
        info.bVisible = TRUE;
        info.dwSize = 50;
        break;
    case 3:
        info.bVisible = FALSE;
        info.dwSize = 1;
        break;
    default:
        info.bVisible = TRUE;
        info.dwSize = 25;
        break;
    }
    SetConsoleCursorInfo(hConsoleOut, &info);
}

/* 按序号设置控制台字体（旧的控制台 API，动态获取） */
void cct_setfontsize(int index)
{
    HMODULE hMod;
    typedef BOOL (WINAPI *PFN_SetConsoleFont)(HANDLE, DWORD, void*);
    PFN_SetConsoleFont pfn;

    hMod = GetModuleHandleA("kernel32");
    if (hMod != NULL) {
        pfn = (PFN_SetConsoleFont)GetProcAddress(hMod, "SetConsoleFont");
        if (pfn != NULL) {
            pfn(hConsoleOut, (DWORD)index, NULL);
        }
    }
}

/* 按名称与点阵尺寸设置控制台字体 */
void cct_setfont(const char* name, int height, int width)
{
    CONSOLE_FONT_INFOEX info;

    memset(&info, 0, sizeof(info));
    info.cbSize = sizeof(info);
    info.dwFontSize.X = (SHORT)width;
    info.dwFontSize.Y = (SHORT)height;
    info.FontWeight = 400;
    MultiByteToWideChar(0, 0, name, -1, info.FaceName, 32);
    SetCurrentConsoleFontEx(hConsoleOut, FALSE, &info);
}

/* 关闭鼠标输入 */
void cct_mouse_disable()
{
    DWORD mode;
    GetConsoleMode(hConsoleIn, &mode);
    SetConsoleMode(hConsoleIn, mode & ~0x10);
}

/* 打开鼠标输入 */
void cct_mouse_enable()
{
    DWORD mode;
    GetConsoleMode(hConsoleIn, &mode);
    SetConsoleMode(hConsoleIn, mode | 0x10);
}

/* 读取一个控制台输入事件。
   键盘事件返回 1，鼠标事件返回 0。
   pmx/pmy 为鼠标坐标；pkey 为事件键码；
   pch1/pch2 为键盘扫描码（方向键为 0xE0 加 0x4B/0x48/0x4D/0x50）。 */
int cct_getinput(int* pmx, int* pmy, int* pkey, int* pch1, int* pch2)
{
    INPUT_RECORD ir;
    DWORD n;

    for (;;) {
        ReadConsoleInputW(hConsoleIn, &ir, 1, &n);
        if (ir.EventType == KEY_EVENT) {
            *pch1 = 0;
            *pch2 = 0;
            if (ir.Event.KeyEvent.bKeyDown) {
                switch (ir.Event.KeyEvent.wVirtualKeyCode) {
                case VK_LEFT:
                    *pch1 = 0xE0; *pch2 = 0x4B; break;
                case VK_UP:
                    *pch1 = 0xE0; *pch2 = 0x48; break;
                case VK_RIGHT:
                    *pch1 = 0xE0; *pch2 = 0x4D; break;
                case VK_DOWN:
                    *pch1 = 0xE0; *pch2 = 0x50; break;
                default:
                    break;
                }
                if (*pch1 == 0) {
                    *pch1 = (int)ir.Event.KeyEvent.uChar.AsciiChar;
                }
                return 1;
            }
        } else if (ir.EventType == MOUSE_EVENT) {
            *pmx = (int)ir.Event.MouseEvent.dwMousePosition.X;
            *pmy = (int)ir.Event.MouseEvent.dwMousePosition.Y;
            if (ir.Event.MouseEvent.dwEventFlags == MOUSE_MOVED) {
                *pkey = 1;
                return 0;
            }
            if (ir.Event.MouseEvent.dwEventFlags == 0) {
                *pkey = 0x80;
                return 0;
            }
            if (ir.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK) {
                *pkey = 2;
                return 0;
            }
        }
    }
}

/* 显示当前控制台字体信息（库中附带的演示函数） */
void cct_show_font_info()
{
    CONSOLE_FONT_INFOEX info;
    char face[64];
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    memset(&info, 0, sizeof(info));
    info.cbSize = sizeof(info);
    if (GetCurrentConsoleFontEx(hConsoleOut, FALSE, &info)) {
        WideCharToMultiByte(936, 0, info.FaceName, -1, face, sizeof(face), NULL, NULL);
        GetConsoleScreenBufferInfo(hConsoleOut, &csbi);
        printf("当前字体：%s\n", face);
        printf("    字 号 数 量 ：%d\n", 1);
        printf("    当前字号序号：%d\n", 0);
        printf("            宽度：%d pixels\n", info.dwFontSize.X);
        printf("            高度：%d pixels\n", info.dwFontSize.Y);
    }
}
