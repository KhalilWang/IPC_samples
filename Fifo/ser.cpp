#include "fifo_head.h"

int main()
{
    Mkfifo(write_fifo_name, FILE_MODE);
    Mkfifo(read_fifo_name, FILE_MODE);

    cout << "Wating for connection...\n";
    int res = open(write_fifo_name, O_WRONLY);
    if(res == -1){
        cout << write_fifo_name << " open error!\n";
        exit(2);
    }else{
        cout << "Ser OK." << endl;
    }

    int cli = open(read_fifo_name, O_RDONLY);
    while(cli == -1){
         cout << "Waiting for Cli..." << endl;
         sleep(1);
         cli = open(read_fifo_name, O_RDONLY);
    }

    char sendbuf[BUF_LEN];
    char recvbuf[BUF_LEN];
    int chid = fork();
    if(chid == 0){
        while(1){
            cout << "Me:>";
            memset(sendbuf, 0x00, BUF_LEN);
            fgets(sendbuf, BUF_LEN, stdin);
            write(res, sendbuf, strlen(sendbuf) + 1);
        }
    }else if(chid > 0){
        sleep(1);
        while(1){
            memset(recvbuf, 0x00, BUF_LEN);
            int rst = read(cli, recvbuf, BUF_LEN);
            while(rst == 0 || rst == -1){
                sleep(1);
                cout << "Read once.\n";
                rst = read(cli, recvbuf, BUF_LEN);
            }
            cout << "Cli:>";
            cout << recvbuf;
            cout << endl;
        }
    }else if(chid < 0){
        cout << "Fork error!\n";
    }



    return 0;
}
