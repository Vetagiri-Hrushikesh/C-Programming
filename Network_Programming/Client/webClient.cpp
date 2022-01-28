#include "common.h"

int main(int argc, char **argv)
{
    int sockfd, n;
    int sendBytes;
    struct sockaddr_in servaddr;

    if (argc != 2)
        err_n_die("usage: %s <server address>", argv[0]);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_n_die("Error while creating the socket");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVER_PORT);

    if ((inet_pton(AF_INET, argv[1], &servaddr.sin_addr)) <= 0)
        err_n_die("inet_pton error for %s", argv[1]);

    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
        err_n_die("Connection failed");

    int fromServ;
    while ((n = read(sockfd, &fromServ, sizeof(fromServ))) > 0)
        printf("%d\n", ntohl(fromServ));

    if (n < 0)
        err_n_die("read error");

    exit(0);
}
