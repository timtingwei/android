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

### 3.c的位逻辑运算符
`~按位取反  ^按位异或 &按位与 |按位或`

取反对符号位也要取反

按位异或可以对两个变量进行交换

### 4. C有参和无参宏定义
宏定义#define 分成有参数 无参数
无参数的可以定义成double 也可以是char*
有参数的如 `#define add(x, y) ((x) + (y))` 后面一定要用括号扩起来 区别优先级

还可以用`#undef`结束宏定义

## 7.18

### 1.#if #ifdef #ifndef
`
#if 可以在预处理时进行宏定义变量的条件判断(宏定义变量不分配内存空间)
#ifdef 某变量是否被宏定义
#ifndef 某变量没有被宏定义
#endif  用于结束任何一个#if
`

### 2. 内存管理

二进制不方便阅读(ELF), 转换成16进制阅读. 一个16进制操作数对应四个二进制操作数

*malloc  动态分配一段内存空间*
`(int*)malloc(sizeof(int))`
60-> 0x3c -> 111100 => 0011 1100 short 2个字节 => 0000 0000 0011 1100 int四个字节
int类型占据4字节
short类型占据2字节


*calloc 动态分配一段连续的内存空间*
`(int*)callloc(3, sizeof(int));   //等价于(int*)malloc(sizeof(int)*3)`

*free   释放内存空间*
free返回01成功与否

*realloc 重新分配内存空间*
`int* number = (int*)realloc(num_s, sizeof(int))    // 把分配给short的内存空间扩大成int`

// 如果是number是int类型的指针
number = address
number = address + 4

### 3.结构体指针

结构体指针指针变量的值, 是结构体数组的首地址

在struct 后接 student = {para1, para2, para3};  // 可以直接初始化

两种访问方式
`
(*student).num
student->num
`

字符数组的赋值方式
`strcpy(s, "mituh");    //不要直接赋值 `


### 4.共用体
union
共用体如果定义了, 相当于成员变量的最大字节类型的值
实际应用不多, 有些场合相对于struct效率更高


### 5.枚举

前面默认从0开始, 当一个数出现定义后, 其右边的数会依次+1


## 7.19

### 文件读写操作
