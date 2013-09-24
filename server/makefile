SRCS = colors.c game-structs.c linked_list.c message-processing.c messaging.c player.c reply-processing.c server.c timeout.c
HDRS = colors.h game-structs.h linked_list.h message-processing.h messaging.h player.h reply-processing.h server.h timeout.h
OBJS = colors.o game-structs.o linked_list.o message-processing.o messaging.o player.o reply-processing.o server.o timeout.o
flags = -lm -lpthread

all: server.o
	gcc -o server $(OBJS) $(flags)

server.o: colors.o linked_list.o messaging.o message-processing.o server.c server.h timeout.o
	gcc -c server.c

colors.o: colors.c colors.h
	gcc -c colors.c

messaging.o: messaging.c messaging.h
	gcc -c messaging.c

message-processing.o: linked_list.o messaging.o message-processing.c message-processing.h player.o reply-processing.o
	gcc -c message-processing.c

player.o: colors.o linked_list.o player.c player.h
	gcc -c player.c

reply-processing.o: linked_list.o reply-processing.c reply-processing.h
	gcc -c reply-processing.c

timeout.o: reply-processing.o timeout.c timeout.h
	gcc -c timeout.c

linked_list.o: game-structs.o linked_list.c linked_list.h
	gcc -c linked_list.c

game-structs.o: game-structs.c game-structs.h
	gcc -c game-structs.c

clean:
	rm -f *.o server
