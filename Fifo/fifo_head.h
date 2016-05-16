#ifndef _FIFO_HEAD_H_
#define _FIFO_HEAD_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

using namespace std;

#define BUF_LEN   256
#define FILE_MODE 0777
const char *write_fifo_name = "write_fifo";
const char *read_fifo_name  = "read_fifo";

int Mkfifo(const char *pathname, mode_t mode)
{
    int res = mkfifo(pathname, mode);
    if(res == -1 && errno != EEXIST){
        cout << pathname << " mkfifo error!\n";
        exit(1);
    }

    return res;
}

#endif
