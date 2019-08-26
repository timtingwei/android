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


## 7.20

### 文件读写操作

fopen和fclose是一种习惯性的组合
*fopen(str, FILE*, 'type');    // r, w, x, a, a+, rt;  rt允许读和写 （这些就是一些文件流的交互规则）*
`
fputc(ch, fp);             // 写入文件字符
ch = fgetc(fp);            // 读取文件字符 遍历文件内容配合 if (!feof(fp)) {}
fputs(str, fp);            // 文件写入字符串
fgets(char[], size, fp);   // 读入文件字符串
fprintf(fp, format, str);       // 文件分析常用, 把str打印到文件
fscanf();                       // 从文件扫入
`

chmod其实也是一个ELF可执行程序, 只是由系统提供的

`
还有两个没学 对数据块的操作, 放在后面学
fread(buffer, size, count, fp);
fwrite(buffer, size, count, fp);
`

fread, fwrite针对struct的文件操作进行读写, buffer指的是指针, 需要引用传入数组中的地址

## 7.21
### 快速开发一款app
用Android Studio开发App, 尽量建空项目
src->MainActivity.java 用户能看的到的界面

res/layout/activity_main.xml 布局文件
res/values/strings.xml  字符串文件, 和布局文件存在引用关系

### 配置文件
res/AndroidManifest.xml
配置文件能找到一些加固, 一些调用情况
`<intent-filter>
<!-- 中间是程序的入口界面 -->
</intent-filter>`

`编译流程: .java=>.class=>.smali=>.dex
可执行程序:.dex,   动态链接库:.so
`

练习: 用了button(按钮), TextView(文本提示框), EditText(文本编辑框)
文本编辑框有个输入类型需要选择

还没解决字体大小, 输入框的数据怎么和完成结合起来, 排列的方式

### java层实现配置文件控件的逻辑

在src/MainActivity.java文件里

1. 声明控件的成员变量
2. 在OnCreate()方法中, 初始化控件, 设置点击事件, 调用login方法
3. 在MainActivity类中实现login函数,`private boolean login(String username, String pwd)`实现密码验证的逻辑


几个小技巧
1. ctrl+shift+o 可以快速导包
2. String pwd = et_username.getText().toString().trim();   //可以从文本编辑控件获取数据
3. Toast.makeText(MainActivity.this, "Login failed!!", 1).show();  // 弹出提示框中吐司函数, 上下文, 提示字符串, 时间; 注意还要show()出来


### 反编译apk分析smali汇编语言

这块比较难的 对比着看了以下 之后可能会深入学习

### native层和jni层之间的接口

看nkd文件的解压包组成
.o文件是链接库

尝试用ndk/toolchain目录下的objdump -S 运行so文件, 得到arm汇编代码; 分析时候更多用NDA？？老师口音很重

DNK是C和JAVA之间的中间接口

纯java开发用的是android sdk开发, 自己用的辅助只要用C写好编译成apk就可以

### 安卓系统框架 和 注册方式


安卓系统框架图:
应用层开发(Android SDK开发)
框架层开发(Android SDK开发)
核心类库层(NDK开发)
安卓Runtime(Dalvik虚拟机/ART)
Linux内核 


注册方式:
java.com 意味着是静态注册: 提供JNK接口, 调用C/C++层; 逆向难度降低
.so文件里有JNI_OnL oad 基本上是动态注册: so和java层之间调用频繁, 安全较好

包名+类型+方法名

## 7.22
### native层之so的加载流程

初始化
把so载入内存
链接阶段



1.关键函数:(抢猫的思路很关键)
dlopen() 打开一个so, fopen打开文件; hook操作就是在so里面找到函数(地址), 调用函数
dlsym()  获取某个函数在内存中的地址 
调用该函数
dlerror() 处理错误的函数


2.初始化
.init()
.init_array() 

3. 常用类
Log 打印log日志信息 

4. Root权限
  shell权限只能进行部分操作
  读写内存数据=>内存页属性的修改mprotect=>r/w/x chmod 777 
  
### native层之dlopen与so链接

elfhdr: 要了解下elf文件头, readelf -e .so的读取elf文件也会出现

so文件用section来定义, section根据类型归并成段program , 程序执行时, 段的效率更高

1. 阅读代码的工具: sublime适合c, c++, java, smali

### sdk工具与环境配置

x86, arm; x86更快点, 但有些需求只能用arm

adt/sdk/tools/ddms.bat: 获取id进程信息
如果要频繁用这些命令的话, 配置一下环境

x86模拟器无法运行:adt/sdk/extras/intel/hard../IntelHaxm.exe安装一下

android studio/sdk manager.exe 
1. 更新安装 arm v7, armv8
2. 需要在options里面配置代理镜像

android studio/avd manager.exe 
创建模拟器

### IDA工具使用
.W代表32位， 4字节
CMP:比较
MOV:数据传送
LDR:寄存器和存储器的访问, 存在方向<-
PUSH: 压栈
POP: 出栈
BLX: 带链接带状态切换的跳转(无条件)

IDA按 空格 进入图表视图
Proximity browser路径视图

绿色箭头:true; 红色: false; 蓝色: 正常流程


### 汇编速成

模拟器system/bin目录下提供很多可执行文件, 可以在shell调用这些指令

system/lib 下有很多so, 动态链接库, 需要link完成一些操作

静态都放在bin目录自己完成


主题, 汇编:

ARM汇编语言
分析和修改汇编指令: 赋值, 跳转, 算术运算, 移位运算, 堆栈操作, 内存读写指令, 函数调用约定

寄存器:不是每个变量都是一个寄存器, 寄存器和存储器之间有个数据交互, 寄存器是一个桥梁. 一个存储器有若干个存储单元.

`
指令集:
跳转
寄存器和存储器数据交互
数据传送
数据算术运算
数据逻辑运算
比较指令
其他指令

寄存器寻址(7种, 常见5种)
`

练习: AR指令反复看, 分析几个简单so。补充书籍<<常用ARM指令集及汇编>>

但是我还是没有看到分析与辅助之间的联系。

// update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
