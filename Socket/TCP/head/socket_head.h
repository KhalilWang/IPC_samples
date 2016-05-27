#ifndef _SOCKET_HEAD_H_
#define _SOCKET_HEAD_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <netinet/in.h>

#define PORT        (9998)  //for bind
#define BACKLOG     (5)     //for listen backlog

#endif
