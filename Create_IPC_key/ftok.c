#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define KEY 0xabcd0000

int main()
{
    char pathname[] = "mykey";
    key_t key;
    key = ftok(pathname, 0xFF);

    if(key == -1){
        printf("key = %d\n", key);
    }

    key_t sem_id;
    sem_id = semget(key, 1, IPC_CREAT|IPC_EXCL);
    if(sem_id == -1){
        printf("Semget Error!\n");
    }


    return 0;
}
