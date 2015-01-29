#ifndef MPCTCP_PROXY_H
#define MPCTCP_PROXY_H 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "util.h"
#include "default_config.h"
#include "socks.h"
#include "net_util.h"


void start_proxy(int);
void stop_proxy();
void handle_sig(int);

#endif
