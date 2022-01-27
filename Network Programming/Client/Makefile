CC = clang
CFLAGS = -g

all: TcpClient
TcpClient: webClient.c
	$(CC) $(CFLAGS) -o webClient webClient.c

clean:
	rm -rf *.dSYM webClient