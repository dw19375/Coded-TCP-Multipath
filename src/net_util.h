#ifndef NET_UTIL_H
#define NET_UTIL_H

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <string.h>

#define NETIFDOWN	0
#define NETIFUP		1

struct addr_list
{
	int active;
	char if_name[10];
	struct sockaddr_in addr;
	struct addr_list * next;
	int sk;
};






#endif