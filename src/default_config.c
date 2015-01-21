//
//  default_config.c
//  Coded-TCP-Multipath-Xcode
//
//  Created by Jason Cloud on 1/20/15.
//  Copyright (c) 2015 MIT. All rights reserved.
//

#include "default_config.h"



proxy_config getconfig()
{
    struct proxy_config proxy_cfg = {
      
        // Program Information
        .program_name="mpctcp",
        .version="0.0",
        .date="16 Jan 2015",
        
        // File Names/Locations
#ifdef __MACH__
        .config_file="~/.mpctcp/mpctcp.conf",
        .logdir="~/.mpctcp",
        .logfile="~/.mpctcp/mpctcp.log",
        .pidfile="~/.mpctcp/mpctcp.pid",
#else
        .config_file="/etc/mpctcp/mpctcp.conf",
        .logdir="/var/log/mpctcp",
        .logfile="/var/log",
        .pidfile="/var/run/mpctcp.pid",
#endif
        // Network Information
        .local_ip="0.0.0.0",
        .socks_port=1080,
        .port_start=8001,
        .port_end=9999
    };
    return proxy_cfg;
}