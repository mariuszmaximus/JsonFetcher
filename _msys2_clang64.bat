cd /d %~dp0
set VSCODE_EXE="C:\Users\%USERNAME%\AppData\Local\Programs\Microsoft VS Code\code.exe"
set MSYS2_ROOT=C:\msys64
set PATH=C:\Windows\System32;C:\Windows\SysWOW64\wbem;%MSYS2_ROOT%\clang64\bin;%MSYS2_ROOT%\usr\bin
%VSCODE_EXE% .\
