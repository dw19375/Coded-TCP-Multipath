#ifndef SOCKS_H
#define SOCKS_H 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <signal.h>
#include "default_config.h"
#include "mpctcp_proxy.h"

void handle_con(proxy_connections *);

#endif