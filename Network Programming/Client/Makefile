CC = g++
CFLAGS = -g
COMMON_OBJS = common.o
THREAD_OBJS = serverTh.o

all: $(COMMON_OBJS) $(THREAD_OBJS) TcpClient TcpServer

TcpClient: webClient.cpp
	$(CC) -o webClient webClient.cpp $(COMMON_OBJS) 

TcpServer: main.cpp
	$(CC)  -o webServer main.cpp $(COMMON_OBJS) $(THREAD_OBJS)

clean:
	rm -rf *.o *.dSYM webClient webServer