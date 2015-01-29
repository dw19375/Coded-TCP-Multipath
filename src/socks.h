#ifndef SOCKS_H
#define SOCKS_H 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <signal.h>
#include "default_config.h"
#include "mpctcp_proxy.h"

typedef struct proxy_connections {
  //int listen_sk;
  int client_sk;
  struct sockaddr_storage client_addr;
} proxy_connections;


int handle_con(proxy_connections *);

#endif
