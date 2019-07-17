# 安卓逆向学习笔记

## 7.16

### 1.安装jdk jre 配置环境
./bin 环境变量, 使得能够在cmd中运行javac javah
### 2.安装Android开发环境
sdk/platform-tool配置环境变量
配置模拟器 用adb devices查看机器
进入adb shell命令行调试手机

### 3.ndk配置
设置ndk环境变量
用ndk-build命令编译jni
在ndk文件中, ndk/toolchains/*4.9/arm-linux-androideabi-readelf 以及其他文件环境变量, 供之后使用

### 4.AndroidKill配置
解压安装
反编译文件
界面介绍
字符串搜索 替换 文本和Unicode之间的转换
java源码查看

### 4.jeb配置
AndroidKill的接盘侠, ak分析不了的时候用
侧重于分析执行流程

### 5.c c++
dev-c++  看了下header files
notepad++

## 7.17

### 1.动态链接库配置
动态链接库文件编译必须在jni目录 否则无法编译
动态链接库文件 lib*-jni.so  格式就是这样
so文件由java层调用
修改Application.mk 可以更换编译后的生存平台x86 arm

**重点**
**区别1:和编译EFL文件的区别  在Android.mk中最后inlcude的参数是BUILD_EXECUTABLE**
**区别2:ELF可执行文件的.c文件包含main函数**

### 2.用c语言开发第一个辅助程序
步骤:
自己写jni包括  Android.mk Application.mk main.c
用ndk-build编译jni的可执行文件, 用于x86 arm平台
在jdk中, 创建arm模拟器
在cmd中运用 adb advices; adb push; adb shell(用于在手机上的执行adb); chmod 777 改变权限

最后可以看到测试的main函数中的打印

