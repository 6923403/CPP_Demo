Server = server
Client = client
CC = g++
all: server client 
server: server
	$(CC) -Wall -O2 server.cpp -o $(Server)

client: client
	$(CC) -Wall -O2 client.cpp -o $(Client)

.PHONY: clean
clean:
	rm $(Server) $(Client)
