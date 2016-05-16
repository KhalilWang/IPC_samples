#一个帮助学习进程间通信技术的repo

> 进程间通信技术(Inter-Process Communication)是很重要的UNIX编程学习方向

###文件结构
.
├── Create_IPC_key
│   ├── ftok.c
│   └── mykey
├── Fifo
│   ├── cli
│   ├── cli.cpp
│   ├── fifo_head.h
│   ├── Makefile
│   ├── read_fifo
│   ├── ser
│   ├── ser.cpp
│   └── write_fifo
├── MsgQueue
│   ├── msgopt
│   └── msgopt.c
├── Readme.md
└── Socket
    ├── bin
    ├── head
    │   └── socket_head.h
    ├── Makefile
    └── src
        ├── cli.c
        └── ser.c

###现有IPC样本数:
 - Socket        套接字通信
 - Message Queue 消息队列
 - Fifo          有名管道
 - Key           如何创建IPCkey

 即将不停完善...
