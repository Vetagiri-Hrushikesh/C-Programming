#include "common.h"

void *connectionHandler(void *clientSockData)
{
    int sendData;
    unsigned char data[100];
    ClientSockSt *pCliSock = (ClientSockSt *)clientSockData;
    int newSocketfd = pCliSock->serAcpSock;
    static int sendFr = 0;

    while (1)
    {
        sendData = htonl(sendFr++);
        send(newSocketfd, &sendData, sizeof(sendData), 0);
        printf("%d\n", ntohl(sendData));
        usleep(800000);
    }
    close(newSocketfd);
    return NULL;
}
