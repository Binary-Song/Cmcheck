# Cmcheck

## Cmcheck
Cmcheck 是一个C语言内存泄漏检查工具。

## 使用方法
- 1. 将mcheck.cpp编译成库。
- 2. 在需要检查的.c源文件里`#include`mcheck.h，该文件中的`malloc`和`free`即可被映射到它们的tracked版本。如果想检查`calloc`和`realloc`，自行修改mcheck.h。
- 3. 在程序出口附近调用`DumpMemRecord()`函数，即可显示此时未释放的内存。
- 4. 编译时记得链接mcheck库。