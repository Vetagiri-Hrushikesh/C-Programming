#ifndef _COMMON_H_
#define _COMMON_H_

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
#include <pthread.h>

#define SERVER_PORT 8090
#define MAXLINE 4096
#define SA struct sockaddr
void err_n_die(const char *fmt, ...);
void signal_handler(int signal_number);
void *connectionHandler(void *clientSockData);

typedef struct __clientSockSt
{
    int th_id;
    int server_port;
    int serAcpSock;
    struct sockaddr_in cliSockaddr;
} ClientSockSt;

#endif