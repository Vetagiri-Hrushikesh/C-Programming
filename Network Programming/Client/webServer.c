#include "common.h"

int main(int argc, char **argv)
{
    int lisSocfd, cliSocfd, n;
    struct sockaddr_in servaddr;
    uint8_t buff[MAXLINE + 1];
    uint8_t recvLine[MAXLINE + 1];

    if ((lisSocfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_n_die("Socket Error");

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERVER_PORT);

    if ((bind(lisSocfd, (SA *)&servaddr, sizeof(servaddr))) < 0)
        err_n_die("Bind Failed");

    if ((listen(lisSocfd, 10)) < 0)
        err_n_die("Listen Failed");

    for (;;)
    {
        struct sockaddr_in addr;
        socklen_t addr_len;
        char clientAddress[MAXLINE + 1];

        printf("Waiting for the connection on port %d", SERVER_PORT);
        fflush(stdout);
        cliSocfd = accept(lisSocfd, (SA *)&addr, &addr_len);

        inet_ntop(AF_INET, &addr, clientAddress, MAXLINE);
        printf("Client connection :  %s\n", clientAddress);
        
        memset(recvLine, 0, MAXLINE);
        while ((n = read(cliSocfd, recvLine, MAXLINE - 1)) > 0)
        {
            fprintf(stdout, "\n%s\n\n%s", bin2hex(recvLine, n), recvLine);
            if (recvLine[n - 1] == '\n')
                break;
            memset(recvLine, 0, MAXLINE);
        }

        if (n < 0)
            err_n_die("Read Error");
        snprintf((char *)buff, sizeof(buff), "HTTP/1.0 200OK\r\n\r\nHello");
        write(cliSocfd, (char *)buff, strlen((char *)buff));
        close(cliSocfd);
    }
}