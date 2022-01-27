#include<sys/socket.h>
#include<sys/types.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdarg.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/time.h>
#include<sys/ioctl.h>
#include<netdb.h>

#define SERVER_PORT 80
#define MAXLINE 4096
#define SA struct sockaddr

void err_n_die(const char *fmt, ...);



void err_n_die(const char* fmt, ...){
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
    if(errno_save != 0){
        fprintf(stdout, "(errno = %d) : %s\n", errno_save, strerror(errno_save));
        fprint(stdout, "\n");
        fflush(stdout);
    }
    va_end(ap);

    // This is the and_die part terminates with an error.
    exit(1);
}