// 2551470 李中 AI拔
#ifndef HANOI_CONST_VALUE_H
#define HANOI_CONST_VALUE_H

/* 只读常量定义（对应 hanoi_const_value.h）
   控制台窗口与伪图形界面参数。 */

/* 控制台窗口与缓冲区尺寸 */
const int CCT_WINDOW_WIDTH   = 120;      /* 窗口宽度（字符列数） */
const int CCT_WINDOW_HEIGHT  = 40;       /* 窗口高度（字符行数） */
const int CCT_BUFFER_WIDTH   = 120;      /* 缓冲区宽度 */
const int CCT_BUFFER_HEIGHT  = 9000;     /* 缓冲区高度 */

/* 三根立柱的中心横坐标 */
const int HDC_COL_A_X = 12;
const int HDC_COL_B_X = 47;
const int HDC_COL_C_X = 82;
const int HDC_COL_STEP = 35;             /* 立柱间距 */

/* 圆柱（立柱）图形 */
const int HDC_POLE_TOP_Y   = 4;          /* 立柱最上一行 */
const int HDC_POLE_BOTTOM_Y = 15;        /* 立柱最下一行 */
const int HDC_BASE_Y       = 16;         /* 底座所在行 */
const int HDC_BASE_START_X = 1;          /* 底座起始列 */
const int HDC_BASE_WIDTH   = 23;         /* 底座宽度 */

/* 竖直（纵向）数组显示 */
const int HDC_VERTICAL_X = 8;            /* 竖直显示的基准列 */
const int HDC_VERTICAL_Y_MODE4 = 19;     /* 菜单项 4 的基准行 */
const int HDC_VERTICAL_Y_MODE8 = 28;     /* 菜单项 8、9 的基准行 */
const int HDC_VERTICAL_DX = 11;          /* 相邻立柱在竖直显示中的列距 */

/* 横向数组显示 */
const int HDC_HORIZONTAL_X = 20;         /* 横向显示的基准列 */
const int HDC_HORIZONTAL_DY = 6;         /* 横向显示相对竖直基准的偏移 */

/* 颜色：控制台属性 = 背景色 * 16 + 前景色 */
const int HDC_COLOR_BLACK      = 0;
const int HDC_COLOR_WHITE      = 7;
const int HDC_COLOR_POLE_BK    = 14;     /* 立柱背景色 */
const int HDC_COLOR_POLE_TEXT  = 15;     /* 立柱前景色 */
const int HDC_COLOR_DISK_SHIFT = 1;      /* 盘子前景色相对背景色的偏移 */

/* 延时（毫秒） */
const int HDC_DELAY_PREP   = 100;        /* 预备演示每步延时 */
const int HDC_DELAY_ANIM   = 100;        /* 动画每步延时（速度 1 时） */
const int HDC_DELAY_MODE4  = 150;        /* 菜单项 4 每次移动后的延时 */
const int HDC_ERROR_DELAY  = 1000;       /* 错误提示停留时间 */
const int HDC_SPEED_MOD    = 5;          /* 速度取模 */
const int HDC_SPEED_UNIT   = 100;        /* 速度单位延时 */

/* 命令输入区域 */
const int HDC_CMD_X = 59;                /* 命令输入起始列 */
const int HDC_CMD_Y = 35;                /* 命令输入行 */
const int HDC_CMD_CLEAR_LEN = 100;       /* 命令区域清除长度 */
const int HDC_MSG_Y = 36;                /* 提示信息行 */

/* 输入参数模式：需要输入移动速度 */
const int HDC_INPUT_WITH_SPEED = 0x30;

/* 提示行 */
const int HDC_PROMPT_Y = 37;             /* "按回车键继续"所在行 */

#endif /* HANOI_CONST_VALUE_H */
