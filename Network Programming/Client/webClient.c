#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <netdb.h>

#define SERVER_PORT 80
#define MAXLINE 4096
#define SA struct sockaddr

void err_n_die(const char *fmt, ...);

int main(int argc, char **argv)
{
    int sockfd, n;
    int sendBytes;
    struct sockaddr_in servaddr;
    char sendLine[MAXLINE];
    char receiveLine[MAXLINE];

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

    sprintf(sendLine, "GET / HTPP/1.1\r\n\r\n");
    sendBytes = strlen(sendLine);

    if (write(sockfd, sendLine, sendBytes) != sendBytes)
        err_n_die("Write Error");

    memset(receiveLine, 0, MAXLINE);
    while ((n = read(sockfd, receiveLine, MAXLINE - 1)) > 0)
    {
        printf("%s", receiveLine);
    }
    if (n < 0)
        err_n_die("read error");

    exit(0);
}

void err_n_die(const char *fmt, ...)
{
    int errno_save;
    va_list ap;

    // Any system or library call
    errno_save = errno;

    // Print out the format+err to standard out
    va_start(ap, fmt);
    vfprintf(stdout, fmt, ap);
    fprintf(stdout, "\n");
    fflush(stdout);

    // Print out the error message set by errno.
    if (errno_save != 0)
    {
        fprintf(stdout, "(errno = %d) : %s\n", errno_save, strerror(errno_save));
        fprintf(stdout, "\n");
        fflush(stdout);
    }
    va_end(ap);

    // This is the and_die part terminates with an error.
    exit(1);
}