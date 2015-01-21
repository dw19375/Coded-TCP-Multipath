//
//  default_config.h
//  Coded-TCP-Multipath-Xcode
//
//  Created by Jason Cloud on 1/20/15.
//  Copyright (c) 2015 MIT. All rights reserved.
//

#ifndef DEFAULT_CONFIG_H
#define DEFAULT_CONFIG_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

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

proxy_config getconfig();

#endif /* DEFAULT_CONFIG_H */