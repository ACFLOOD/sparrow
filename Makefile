OBJS = sparrow.o thread_manage.o file.o ev_loop.o config.o async_log.o
CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall -lpthread -lrt $(DEBUG)

sparrow: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o sparrow

sparrow.o: sparrow.c sparrow.h global.h  ev_loop.h async_log.h thread_manage.h config.h file.h mime.h
	$(CC) $(CFLAGS)  sparrow.c

thread_manage.o: thread_manage.c thread_manage.h sparrow.h global.h async_log.h ev_loop.h  config.h file.h mime.h
	$(CC) $(CFLAGS) thread_manage.c

ev_loop.o: ev_loop.c ev_loop.h async_log.h
	$(CC) $(CFLAGS) ev_loop.c

file.o: file.c file.h
	$(CC) $(CFLAGS) file.c

async_log.o: async_log.c async_log.h
	$(CC) $(CFLAGS) async_log.c

config.o: config.c config.h
	$(CC) $(CFLAGS) config.c



clean:
	rm *.o sparrow