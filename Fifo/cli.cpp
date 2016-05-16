#include "fifo_head.h"

int main()
{
    Mkfifo(read_fifo_name, FILE_MODE);
    Mkfifo(write_fifo_name, FILE_MODE);

    cout << "Wating for connection...\n";
    int res = open(write_fifo_name, O_RDONLY);
    if(res == -1){
        cout << read_fifo_name << " open error!\n";
        exit(2);
    }else{
        cout << "Cli OK." << endl;
    }

    int ser = open(read_fifo_name, O_WRONLY);
    while(ser == -1){
         cout << "Waiting for Ser..." << endl;
         sleep(1);
         ser = open(read_fifo_name, O_WRONLY);
    }

    char sendbuf[BUF_LEN];
    char recvbuf[BUF_LEN];
    int chid = fork();
    if(chid == 0){
        while(1){
            cout << "Me:>";
            memset(sendbuf, 0x00, BUF_LEN);
            fgets(sendbuf, BUF_LEN, stdin);
            write(ser, sendbuf, strlen(sendbuf) + 1);
        }
    }else if(chid > 0){
        sleep(1);
        while(1){
            memset(recvbuf, 0x00, BUF_LEN);
            int rst = read(res, recvbuf, BUF_LEN);
            while(rst == 0 || rst == -1){
                sleep(1);
                cout<< "Read Once.\n";
                rst = read(res, recvbuf, BUF_LEN);
            }
            cout << endl;
            cout << "Ser:>";
            cout << recvbuf;
            cout << endl;
        }
    }else if(chid < 0){
        cout << "Fork error!\n";
    }


    return 0;
}
