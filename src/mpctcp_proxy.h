#ifndef MPCTCP_PROXY_H
#define MPCTCP_PROXY_H 

#include <stdlib.h>

typedef struct proxy_config {
	char program_name[128];
	char version[128];
	char date[128];
	char config_file[256];
	char logdir[265];
	char logfile[256];
	char pidfile[256];
	char local_ip[256];
	int socks_port;
	int port_start;
	int port_end;
} proxy_config;

#endif