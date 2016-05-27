#include "../head/UDP_head.h"


int main()
{
    /* Create socket */
    int serfd = socket(AF_INET, SOCK_DGRAM, 0);
    assert(serfd != -1);

    /* Set the structure */
    struct sockaddr_in saddr;
    saddr.sin_family        = AF_INET;
    saddr.sin_port          = htons(PORT);
    saddr.sin_addr.s_addr  = htonl(INADDR_ANY);

    /* Bind the port */
    assert(bind(serfd, (struct sockaddr *)&saddr, sizeof(saddr)) != -1);

    /* Execute recvfrom function */
    char buf[BUFLEN];
    struct sockaddr_in caddr;
    int    addrsz = sizeof(caddr);
    recvfrom(serfd, buf, BUFLEN, 0, (struct sockaddr *)&caddr, &addrsz);

    /* Show result */
    printf("Rst:%s\n", buf);

    return 0;
}

