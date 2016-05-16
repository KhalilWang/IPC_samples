#include "../head/socket_head.h"

void fork_for_client(int cfd, int sfd);
void client_work(int chid);
void print_addr(struct sockaddr_in addr);

void fork_for_client(int cfd, int sfd)
{
    int chid = fork();
    if(chid > 0){
        /* Accept The Require Again*/
        struct sockaddr_in caddr;
        socklen_t caddrsz = sizeof(caddr); // For Receiving Information of ClientAddr
        int _cfd = accept(sfd, (struct sockaddr *)&caddr, &caddrsz);
        print_addr(caddr);
        fork_for_client(_cfd, sfd);
    }else if(chid ==  0){

        /* Client Does Its Work */
        client_work(getpid());

    }else if(chid < 0){
         printf("Fork Error!\n");
    }
}

void client_work(int chid)
{
    int num = 5;
    while(num--){
         printf("chid:[%d] > %d\n", chid, num);
         sleep(1);
    }
    printf("%d Over.\n", chid);
    exit(0);
}

void print_addr(struct sockaddr_in src)
{
    printf("addr[%s] Connected\n", inet_ntoa(src.sin_addr));
}

int main()
{
    /* Create Socket */
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sfd != -1);

    /* Set Addr */
    struct sockaddr_in saddr;
    saddr.sin_family        = AF_INET;
    saddr.sin_port          = htons(PORT);
    saddr.sin_addr.s_addr   = htonl(INADDR_ANY);

    /* Bind The Port */
    assert(bind(sfd, (struct sockaddr *)&saddr, sizeof(saddr)) != -1);

    /* Listen To The Port */
    assert(listen(sfd, BACKLOG) != -1);

    /* Accept The Require */
    printf("Waiting..\n");
    struct sockaddr_in caddr;
    socklen_t caddrsz = sizeof(caddr); // For Receiving Information of ClientAddr
    int cfd = accept(sfd, (struct sockaddr *)&caddr, &caddrsz);
    print_addr(caddr);

    /* Fork To Handle The Client */
    fork_for_client(cfd, sfd);

    close(sfd);
    return 0;
}
