# Makefile for mpctcp_proxy

CC = clang
CFLAGS  = -g -Wall


all: mpctcp_proxy

mpctcp_proxy: mpctcp_proxy.o mpctcp_cli.o mpctcp_srv.o default_config.o socks.o pslist.o net_util.o coding_util.o util.o
	$(CC) $(CFLAGS) -o mpctcp_proxy mpctcp_proxy.o mpctcp_cli.o mpctcp_srv.o default_config.o socks.o pslist.o net_util.o coding_util.o util.o 
	
mpctcp_proxy.o: mpctcp_proxy.c mpctcp_proxy.h net_util.h util.h default_config.h socks.h
	$(CC) $(CFLAGS) -c mpctcp_proxy.c
	
mpctcp_cli.o: mpctcp_cli.c mpctcp_cli.h
	$(CC) $(CFLAGS) -c mpctcp_cli.c

mpctcp_srv.o: mpctcp_srv.c mpctcp_srv.h
	$(CC) $(CFLAGS) -c mpctcp_srv.c

default_config.o: default_config.c default_config.h
	$(CC) $(CFLAGS) -c default_config.c
	
socks.o: socks.c socks.h mpctcp_proxy.h
	$(CC) $(CFLAGS) -c socks.c 
	
pslist.o: pslist.c pslist.h net_util.h
	$(CC) $(CFLAGS) -c pslist.c

net_util.o: net_util.c net_util.h util.h
	$(CC) $(CFLAGS) -c net_util.c

coding_util.o: coding_util.c coding_util.h net_util.h
	$(CC) $(CFLAGS) -c coding_util.c

util.o: util.c util.h net_util.h
	$(CC) $(CFLAGS) -c util.c
	
clean:
	rm -f mpctcp_proxy *.o
