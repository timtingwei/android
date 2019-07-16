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
在ndk文件中, 设置arm-linux-androideabi-readelf环境变量, 供之后使用
