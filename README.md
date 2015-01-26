# EmbeddedOperatingSystem

###Linux自定义内核模块编写

#### Homework2 步骤
###### 1.编写C和Makefile文件
###### 2.执行make命令 会生成一些相关文件(包括bjtu.ko)
###### 3.执行sudo insmod bjtu.ko
###### 4.执行lsmod|grep bjtu 查看插入的自定义内核模块
###### 5.执行dmesg|tail -1 查看printk打印的log信息(Module Init: bjtu kernel modules!)
###### 6.执行cd /proc/进入内核态与用户态交互的proc目录
###### 7.执行ls|grep bjtu_memoryinfo过滤
###### 8.执行cat bjtu_memoryinfo查看打印日志
###### 9.执行sudo rmmod bjtu 移除自定义内核模块bjtu.ko
###### 10.执行dmesg|tail -1 查看printk打印的log信息(Module Exit:bjtu kernel module!)

###Linux进程间通信(Socket IPC)

#### Homework3 步骤
###### 1.编译client和server,gcc client.c -o client    gcc server.c -o server
###### 2.执行server, ./server 127.0.0.1 6789
###### 3.执行client, ./client 127.0.0.1 6789
###### 4.选择运算类型(ADD SUB MUL DIV)
###### 5.查看结果
###### 6.退出client.
###### 7.退出server.
