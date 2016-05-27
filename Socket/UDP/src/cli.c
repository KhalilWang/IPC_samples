#include "../head/UDP_head.h"


int main()
{
    /* Create Socket */
    int serfd = socket(AF_INET, SOCK_DGRAM, 0);
    assert(serfd != -1);

    /* Set the structure */
    struct sockaddr_in saddr;
    saddr.sin_family        = AF_INET;
    saddr.sin_port          = htons(PORT);
    saddr.sin_addr.s_addr  = htonl(INADDR_ANY);

    /* Set buffer and the sockaddr */
    char buf[BUFLEN] = "Hello";
    struct sockaddr_in caddr;
    int    addrsz = sizeof(caddr);

    /* Execute sendto function */
    sendto(serfd, buf, BUFLEN, 0, (struct sockaddr *)&saddr, addrsz);

    return 0;
}

