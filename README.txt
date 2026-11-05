2551470 李中 AI拔
90-b1.exe 逆向还原工程
======================================================================

一、原始程序概况
----------------------------------------------------------------------
    文件        : 90-b1.exe（98,304 字节，PE32 i386 控制台程序）
    编译器      : Microsoft Visual C++（Debug 版，MSVC 14.44，VS2022）
    程序功能    : 汉诺塔综合演示程序（菜单 1-9 加 0 退出）
    运行环境    : Windows 控制台主机（新宋体 16 点阵，120x40 窗口）
    原始工程文件: hanoi_main.cpp          -- main 函数
                  hanoi_menu.cpp          -- 菜单显示与选择
                  hanoi_multiple_solutions.cpp -- 各菜单项的实现
                  hanoi.h                 -- 头文件
                  hanoi_const_value.h     -- 只读常量定义
                  cmd_console_tools.cpp/.h-- 控制台工具函数
                  cmd_hdc_tools.cpp/.h    -- 伪图形界面基本函数

本目录下的源文件是在没有原始工程的情况下，通过反汇编与反编译（Ghidra +
人工分析）从 90-b1.exe 完整还原出来的 C++ 源代码，并经过运行时逐格比对验证。

二、还原文件清单
----------------------------------------------------------------------
    hanoi_main.cpp              main 函数与各菜单项的分派
    hanoi_menu.cpp              菜单显示与按键读取
    hanoi_multiple_solutions.cpp 输入函数、递归解法、数组显示、图形解、游戏版
    hanoi.h                     全局变量与函数声明
    hanoi_const_value.h         窗口尺寸、坐标、颜色、延时等常量
    cmd_console_tools.h/.cpp    控制台工具函数（cct_*）
    cmd_hdc_tools.h/.cpp        伪图形界面基本函数（hdc_*）
    build.bat                   编译脚本（VS2022 x86）

三、菜单与实现函数对照
----------------------------------------------------------------------
    1.基本解                    hanoi_print_mode1
    2.基本解（步数记录）        hanoi_print_mode2
    3.内部数组显示（横向）      hanoi_print_mode3
    4.内部数组显示（纵向+横向） hanoi_move_mode4 / hanoi_prepare
    5.图形解-预备-画三个圆柱    hanoi_draw_cylinders
    6.图形解-预备-在起始柱上画n个盘子 hanoi_draw_column
    7.图形解-预备-第一次移动    hanoi_first_move
    8.图形解-自动移动版本       hanoi_move_mode8 / hanoi_animate
    9.图形解-游戏版             hanoi_game
    0.退出                      main

    共用的递归函数：hanoi（把 n 个圆盘从 from 经 aux 移到 to）
    共用的输入函数：hanoi_input_params（层数、起始柱、目标柱、速度）
    共用的横向输出：hanoi_show_array
    共用的纵向输出：hanoi_show_vertical
    共用的画柱函数：hanoi_draw_cylinders
    共用的移动动画：hanoi_animate

四、关键全局变量
----------------------------------------------------------------------
    g_disk[3][10]   三根立柱上现有圆盘的编号（0 表示空位）
                    原程序地址 0x426208（A 柱）、0x426230（B 柱）、
                    0x426258（C 柱），连续存放
    g_step          总移动步数（原程序 0x426280，复位为 1，每移动一次加 1）
    g_countA/B/C    三根立柱上现有圆盘的数量（原程序 0x426284/0x426288/0x42628c）

五、控制台工具库说明
----------------------------------------------------------------------
    cmd_console_tools.cpp 中的函数与原程序对应关系：
        cct_cls            清屏（原程序 0x00414060）
        cct_mouse_disable  关闭鼠标输入（0x004141f0）
        cct_mouse_enable   打开鼠标输入（0x004142d0）
        cct_getcolor       读取前景/背景色（0x004143b0）
        cct_getwindowrect  读取窗口与缓冲区尺寸（0x004144a0）
        cct_gettitle       读取标题（0x004145a0）
        cct_show_font_info 显示当前字体信息（0x00414610）
        cct_getxy          读取光标位置（0x00414a20）
        cct_gotoxy         设置光标位置（0x00414af0）
        cct_getinput       读取控制台输入事件（0x00414bb0）
        cct_setcolor       设置颜色（0x00414f50）
        cct_setwindow      设置窗口/缓冲区尺寸（0x00414fc0）
        cct_setfontsize    按序号设置字体（0x00415400）
        cct_settitle       设置标题（0x004154b0）
        cct_setcursor      设置光标形状（0x00415510）
        cct_setfont        按名称与点阵尺寸设置字体（0x00415660）

    cmd_hdc_tools.cpp 中的函数与原程序对应关系：
        hdc_putchar        输出 count 个字符（0x00415780）
        hdc_putint         输出 count 个整数（0x00415840）
        hdc_putstr         输出字符串并按 repeat/空格补齐（0x00415900）
        hdc_getch          无输入时返回 -1（0x00415ab0）
        hdc_equal          比较两个整数（0x00415b00）
        hdc_strlen         取字符串长度（0x00415b80）
        hdc_nop            空函数（0x00415be0）
        hdc_memcopy        按宽字符复制（0x00415bf0）

    说明：cct_show_font_info、cct_getinput、hdc_getch 等函数在原程序中并未被
    汉诺塔逻辑调用（库文件整体链接进可执行文件），本工程仍按二进制中的行为
    予以还原，不影响程序运行结果。

六、编译方法
----------------------------------------------------------------------
    环境：Visual Studio 2022（x86 本机工具）
    直接运行 build.bat，或在 x86 开发者命令提示符中执行：
        cl /nologo /EHsc /Zi /MDd /D_DEBUG /Fe:rebuilt.exe
           hanoi_main.cpp hanoi_menu.cpp hanoi_multiple_solutions.cpp
           cmd_console_tools.cpp cmd_hdc_tools.cpp
    所有源文件均为 GB2312 编码。

七、验证
----------------------------------------------------------------------
    使用控制台自动化驱动程序（新建控制台 -> 启动程序 -> 注入按键事件 ->
    读取屏幕缓冲区中的每个字符及其颜色属性），对原程序与还原程序在相同
    输入下逐格比较。已验证的场景包括：
        - 主菜单显示；
        - 菜单项 1、2、3（n=2/3，不同起止柱）；
        - 菜单项 4（含动画中间状态与最终状态）；
        - 菜单项 5、6、7（奇偶两种层数）；
        - 菜单项 8（自动移动，不同起止柱与速度）；
        - 菜单项 9（游戏版：非法移动提示、胜利、退出）；
        - 输入校验（层数越界、起止柱相同等）；
        - 退出程序。
    比较结果：字符内容、颜色属性、光标位置全部一致（0 差异）。