.SUFFIXES:.c .o
CC=gcc

SRCS=main.c
OBJS=$(SRCS:.c=.o)
EXEC=main

start: $(OBJS)
		$(CC) -o $(EXEC) $(OBJS)

.c.o:
	$(CC) -W -o $@ -c $<

clean:
	rm -rf $(EXEC) $(OBJS)
