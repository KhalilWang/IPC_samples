#include "../head/socket_head.h"

int main()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    assert(fd != -1);

    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port   = htons(PORT);
    struct in_addr in;
    inet_aton("127.0.0.1", &in);
    saddr.sin_addr   = in;

    connect(fd, (struct sockaddr *)&saddr, sizeof(saddr));
    printf("Ok!\n");

    close(fd);
    return 0;
}
