rem 2551470 ÀîÖÐ AI°Î
@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\18\BuildTools\VC\Auxiliary\Build\vcvars32.bat" >nul
cd /d "%~dp0"
cl /nologo /EHsc /Zi /MDd /D_DEBUG /Fe:rebuilt.exe hanoi_main.cpp hanoi_menu.cpp hanoi_multiple_solutions.cpp cmd_console_tools.cpp cmd_hdc_tools.cpp
