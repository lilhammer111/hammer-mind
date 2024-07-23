# git提交约定

这里是一些常见的前缀及其含义：

1. **feat**: 表示新增了一个功能（feature），通常是在软件中添加了新的能力。
   - 例如：`feat: add user login functionality`
2. **fix**: 用于标记修复了一个 bug。
   - 例如：`fix: resolve login issue causing app crash`
3. **docs**: 表示只改变了文档。
   - 例如：`docs: update README with new integration instructions`
4. **style**: 指更改代码格式，不影响代码运行的改动（例如空格、格式化、缺少分号等）。
   - 例如：`style: apply code formatting with Prettier`
5. **refactor**: 代码重构时使用，表明代码内部结构的优化，但功能上没有新增。
   - 例如：`refactor: modularize login code to improve readability`
6. **test**: 添加或修改测试代码。
   - 例如：`test: add unit tests for user authentication`
7. **chore**: 对构建过程或辅助工具和库的更改（不包括源代码、测试代码的更改）。
   - 例如：`chore: update build scripts`
8. **perf**: 用于提升性能的代码更改。
   - 例如：`perf: optimize database query for faster retrieval times`
9. **ci**: 针对持续集成和部署系统的配置文件和脚本的更改。
   - 例如：`ci: update CI pipeline to run linting with each build`



# 程序的内存布局

程序的内存布局通常包括以下几个重要的组成成分：

1. **栈（Stack）**：用于存储局部变量和函数调用的上下文。栈是向高地址增长的。

2. **堆（Heap）**：用于动态内存分配。程序可以在运行时请求和释放堆内存，堆是向低地址增长的。

3. **全局/静态存储区（Global/Static Storage）**：存储全局变量和静态变量。这些变量在程序的整个生命周期内都存在。

4. **代码段（Code Segment）**：存储程序的指令。这部分内存是只读的，用于存储程序的可执行代码。

5. **常量区（Constant Pool）**：存储程序中的常量，通常是字符串常量。

6. **数据段（Data Segment）**：存储初始化的全局变量和静态变量。

7. **未初始化的数据段（BSS Segment）**：存储未初始化的全局变量和静态变量。这部分内存在程序启动时被清零。

8. **寄存器（Registers）**：CPU内部的存储空间，用于快速访问变量和指令。

9. **程序计数器（Program Counter）**：存储下一条指令的地址。

10. **栈帧（Stack Frame）**：每个函数调用都会有一个栈帧，包含函数的局部变量、参数、返回地址等信息。

这些组成部分在不同的编程语言和操作系统中可能有所不同，但大多数现代计算机系统都遵循类似的内存布局原则。