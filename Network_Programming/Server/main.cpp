#include "common.h"

int main(int argc, char **argv)
{
    int lisSocfd, cliSocfd, n;
    struct sockaddr_in servaddr, clientaddr;
    pthread_attr_t pthread_attr;
    ClientSockSt cliSock;
    pthread_t thread_id;
    int opt = 1;
    socklen_t client_addr_len;

    if ((lisSocfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_n_die("Socket Error");

    if (setsockopt(lisSocfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
        err_n_die("SetSockOpt");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(SERVER_PORT);

    if ((bind(lisSocfd, (SA *)&servaddr, sizeof(servaddr))) < 0)
        err_n_die("Bind Failed");

    if ((listen(lisSocfd, 5)) < 0)
        err_n_die("Listen Failed");

    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        err_n_die("signal");

    if (signal(SIGTERM, signal_handler) == SIG_ERR)
        err_n_die("signal");
    if (signal(SIGINT, signal_handler) == SIG_ERR)
        err_n_die("signal");

    if (pthread_attr_init(&pthread_attr) != 0)
        err_n_die("pthread_attr_init");

    if (pthread_attr_setdetachstate(&pthread_attr, PTHREAD_CREATE_DETACHED) != 0)
        err_n_die("pthread_attr_setdetachstate");

    printf("Waiting for the connection on port %d\n", SERVER_PORT);
    fflush(stdout);
    while ((cliSocfd = accept(lisSocfd, (SA *)&clientaddr, &client_addr_len)))
    {
        cliSock.serAcpSock = cliSocfd;
        cliSock.cliSockaddr.sin_addr = clientaddr.sin_addr;
        cliSock.cliSockaddr.sin_port = clientaddr.sin_port;
        printf("%d\n", cliSock.serAcpSock);
        printf("%u\n", ntohs(cliSock.cliSockaddr.sin_port));
        printf("%s\n", inet_ntoa(cliSock.cliSockaddr.sin_addr));

        if ((pthread_create(&thread_id, &pthread_attr, connectionHandler, &cliSock)) < 0)
            err_n_die("Cannot create thread.");
    }

    if (cliSocfd < 0)
        err_n_die("Accept Failed");

    close(cliSocfd);
    close(lisSocfd);
}
