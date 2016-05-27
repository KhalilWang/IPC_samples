#Socket 网络套接字通信

TCP:
     客户端：
         1.socket(AF_INET, SOCK_STREAM, 0);              创建套结字
          `- 2.connect(sockfd, *sa_addr, addrlen);       连接端口
              `- 3.send() / recv();                      发送/接受数据
                  `- 4.close(fd);                        退出

     服务端：
         1.socket(AF_INET, SOCK_STREAM, 0);              创建套结字
          `- 2.bind(sockfd, *sa_addr, addrlen);          绑定端口
              `- 3.listen(sockfd, backlog);              监听端口
     循           `- 4.accept(sockfd, *addr, *addrlen);  等待接受请求
     环               `- 5.fork() / pthread_create();    创建进线程处理
                          `- 6.close(fd);                退出

                 listen中的backlog是可以允许的排队人数
                 --- 真正的人数是 backlog * 3 / 2 + 1
                 accept中的addr接收的是连接人的addr信息
                 accept返回的是一个sockfd！CS之间的通信由此开始！
                 通常在accept之后创建进线程来处理新的fd，
                 然后主进程继续accept来接受请求
                 进程立即fork()(线程没有独立空间，不太适合存储accept的返回值)
                 线程则需要将fd存储于栈上，使用同步技术防止fd被覆盖

     对于描述符的使用：(适合tcp， 但是这两个函数和协议无关)
         send(sockfd, *buf, len, flags);
         recv(sockfd, *buf, len, flags);

         其实就是对于read() / write()的封装

     struct sockaddr{
         sa_family_t sa_family  ;
         char        sa_data[14];
     }               //原版的sockaddr地址信息
     新版： sockaddr_in 将sa_family 转换为连续的几个变量
            sa_family_t ->  sin_family + sin_port(short) + sin_addr(32位整形)
             宏定义的##意思是将后面的的变量转为字符补在后面
 *一般采用sockaddr_in 强转为 sockaddr 使用
 端口信息采用了网络字节序：
     htonl()/htons()  host to network long/short 将端口号进行网络字节序转化
 sin_addr -> 这个结构体变量是宏定义： 接受本网段还是全网的连接
 IP地址是字符串的地址 是一个16字节的char数组 存储的IPV4的字符串
 使用inet_aton()来将字符串进行网络字节序转换 inet_ntoa()反之

 *tip: 网络传输时一定要注意内存对齐！

