# 使用Msys2配置MinGW-W64

## 下载地址  
- 官方安装器：访问 MSYS2 官网并下载最新的 `msys2-x86_64-*.exe` 安装包.
- 官方仓库：在 https://repo.msys2.org/distrib/x86_64/ 可找到 `.exe`、`.tar.xz` 和 `.tar.zst` 
- 国内镜像：访问 https://mirrors.tuna.tsinghua.edu.cn/msys2/distrib/x86_64/ 下载相同文件.

C:\msys64\mingw64\bin 目录为空是因为 MSYS2 默认只安装了最基础的运行环境，不会自动包含任何 MinGW-w64 的工具链，需要通过 pacman 手动安装对应的软件包才能在该目录中看到可执行文件。

## 安装MingW64  
- 首次更新：在 MSYS2 终端（通过 msys2.exe 启动）中执行  
  ```bash
  pacman -Syu
  ```
  更新核心包后，关闭并重新打开终端，再次运行  
  ```bash
  pacman -Su
  ```
  以确保系统完整升级.
- 安装工具链：在同一 MSYS2 终端中执行  
  ```bash
  pacman -S --needed base-devel mingw-w64-x86_64-toolchain
  ```
  该命令将安装 gcc、g++、make 等常用工具，并将可执行文件放入 C:\msys64\mingw64\bin 目录.
- 验证  
安装完成后，可在 PowerShell 或 CMD 中运行  
```bash
C:\msys64\mingw64\bin\gcc --version
```
或在 VSCode 终端中执行 `g++ --version` 来确认工具链已正确安装并可用.

VSCode C++环境配置涉及安装Microsoft C/C++扩展、设置MinGW路径、创建c_cpp_properties.json、tasks.json和launch.json配置文件，并调整终端为UTF-8编码以确保中文正常显示。

## 扩展安装
打开VSCode，按Ctrl+Shift+X进入扩展市场，搜索并安装“Microsoft C/C++”扩展以支持语法高亮、 IntelliSense 和调试功能。可选安装“Code Runner”扩展用于快速运行代码，或“C/C++ Extension Pack”以获取完整工具集。安装后，重启VSCode以激活扩展。

## PATH 和编译器配置
确保MinGW-w64的bin目录（如C:\msys64\mingw64\bin）已添加到Windows系统PATH环境变量中：在“系统属性”中编辑“环境变量”，添加该路径，然后重启VSCode。在VSCode中，按Ctrl+Shift+P打开命令面板，选择“C/C++: Select a Configuration...”并选择“Win32”或自定义MinGW路径，以让IntelliSense识别GCC头文件。验证配置：打开终端运行`g++ --version`，应显示GCC版本信息。

## c_cpp_properties.json 配置
在项目文件夹中创建.vscode目录，按Ctrl+Shift+P选择“C/C++: Edit Configurations (JSON)”，生成c_cpp_properties.json文件。配置内容如下，确保includePath包含MinGW的C++头文件路径（如C:\msys64\mingw64\include\c++\14.2.0），以支持<bits/stdc++.h>等头文件：
```json
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**",
                "C:/msys64/mingw64/include/c++/14.2.0",
                "C:/msys64/mingw64/include/c++/14.2.0/x86_64-w64-mingw32",
                "C:/msys64/mingw64/include/c++/14.2.0/backward",
                "C:/msys64/mingw64/include"
            ],
            "defines": ["_DEBUG", "UNICODE", "_UNICODE"],
            "compilerPath": "C:/msys64/mingw64/bin/g++.exe",
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "windows-gcc-x64"
        }
    ],
    "version": 4
}
```
保存后，扩展会自动扫描路径，解决“bits/stdc++.h not found”错误。

## tasks.json 配置
按Ctrl+Shift+P选择“Tasks: Configure Task”，然后“Create tasks.json file from template” > “Others”，生成tasks.json文件。配置构建任务以使用g++编译，支持C++17标准和多文件项目：
```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "type": "cppbuild",
            "label": "C/C++: g++.exe build active file",
            "command": "C:/msys64/mingw64/bin/g++.exe",
            "args": [
                "-fdiagnostics-color=always",
                "-g",
                "${file}",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe"
            ],
            "options": {
                "cwd": "${fileDirname}"
            },
            "problemMatcher": ["$gcc"],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "compiler: C:/msys64/mingw64/bin/g++.exe"
        }
    ]
}
```
按Ctrl+Shift+B运行构建任务，生成.exe文件。

## launch.json 配置
按Ctrl+Shift+D打开调试视图，点击“create a launch.json file” > “C++ (GDB/LLDB)”，选择g++生成launch.json。配置调试器路径和预构建任务，支持断点调试：
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "C/C++: g++ build and debug active file",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}\\${fileBasenameNoExtension}.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "C:/msys64/mingw64/bin/gdb.exe",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "C/C++: g++.exe build active file"
        }
    ]
}
```
按F5启动调试，确保“program”指向编译后的.exe。

## 终端 UTF-8 和中文显示配置
在VSCode设置（Ctrl+,）中搜索“terminal.integrated.defaultProfile.windows”，设置为“Command Prompt”。编辑settings.json添加终端启动命令以启用UTF-8编码：
```json
{
    "terminal.integrated.defaultProfile.windows": "Command Prompt",
    "terminal.integrated.profiles.windows": {
        "Command Prompt": {
            "path": [
                "${env:windir}\\Sysnative\\cmd.exe",
                "${env:windir}\\System32\\cmd.exe"
            ],
            "args": ["/K", "chcp 65001"]
        }
    },
    "files.encoding": "utf8"
}
```
这会在终端启动时运行`chcp 65001`，确保输出支持中文。对于源文件，确保文件编码为UTF-8（右下角状态栏选择“UTF-8”并保存）。

## 测试验证
创建test.cpp文件：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    cout << "Hello, 中文测试!" << endl;
    return 0;
}
```
按Ctrl+Shift+B构建，然后F5调试或在终端运行`./test.exe`，确认无头文件错误且中文输出正常。如果调试中断点，检查launch.json路径是否正确。

