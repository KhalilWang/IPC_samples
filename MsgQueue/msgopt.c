#include <apue.h>

#define BUFLEN 256
#define FILE_MODE IPC_CREAT|IPC_EXCL|0666

typedef struct Msg{
    long MsgType;
    char MsgInfo[BUFLEN];
}Msg;

void create_msgqueue(char *key);
void snd_msg(char *id, char *type, char *msg);
void rcv_msg(char *id, char *type);
void delete_msgqueue(char *key);

void create_msgqueue(char *key)
{
    long msgkey = ftok(key, 1);
    if(msgkey == -1){
        printf("Ftok Error!\n");
        return;
    }
    int rst  = msgget(msgkey, FILE_MODE);
    if(rst == -1){
        printf("Create Failed!\n");
        return;
    }else{
        printf("Your Msgqueue id is <%d>! Remember!\n", rst);
        return;
    }
}

void snd_msg(char *id, char *type, char *msg)
{
    int  mid   = atoi(id);

    Msg mmsg;
    mmsg.MsgType = atol(type);
    strcpy(mmsg.MsgInfo, msg);

    int rst = msgsnd(mid, &mmsg, sizeof(mmsg), 0);
    if(rst == -1){
        printf("Send Msg Error!\n");
        return;
    }else if(rst == 0){
        printf("Send Msg Succeed!\n");
        return;
    }
}

void rcv_msg(char *id, char *type)
{
    int  mid = atoi(id);
    long mtype = atol(type);
    Msg  mmsg;
    int sz = msgrcv(mid, &mmsg, sizeof(mmsg), mtype, IPC_NOWAIT);
    if(sz == -1){
        printf("Receive Msg Failed!\n");
        return;
    }else if(sz > 0){
        printf("Msg:\n%s\n", mmsg.MsgInfo);
        return;
    }else if(sz == 0){
        printf("No Msg In Queue!\n");
        return;
    }

}
void delete_msgqueue(char *id)
{
    int mid = atoi(id);
    int rst = msgctl(mid, IPC_RMID, NULL);
    if(rst == 0){
        printf("Removed Ok!\n");
        return;
    }else{
        printf("Failed Remove MsQueue!\n");
        return;
    }
}
void usage(char **argv)
{
    printf("USAGE: %s <OPTION> <path> <MsQ_id> <Type> <Msg>\n", argv[0]);
    printf("\n");
    printf("OPTION: 0 for create msgqueue with <path>.\n");
    printf("        1 for snd <Msg> with <MsQ_id> <Type>.\n");
    printf("        2 for rcv msg with <MsQ_id> <Type>.\n");
    printf("       -1 for delete msgqueue with <MsQ_id>.\n");
    printf("        5 for show MsgQueue info.\n");
}

int main(int argc, char **argv)
{
    if(argc < 2){
        usage(argv);
        return 1;
    }

    int opt = atoi(argv[1]);
    switch(opt){
        case 0: create_msgqueue(argv[2]);break;
        case 1: snd_msg(argv[2], argv[3], argv[4]);break;
        case 2: rcv_msg(argv[2], argv[3]);break;
        case 5: system("ipcs -q");break;
        case -1: delete_msgqueue(argv[2]);break;
    }

    return 0;
}
