CC = clang
CFLAGS = -g
COMMON_OBJS = common.o

all: $(COMMON_OBJS) TcpClient TcpServer

TcpClient: webClient.c
	$(CC) $(CFLAGS) -o webClient webClient.c $(COMMON_OBJS)

TcpServer: webServer.c
	$(CC) $(CFLAGS) -o webServer webServer.c $(COMMON_OBJS)

clean:
	rm -rf *.o *.dSYM webClient webServer