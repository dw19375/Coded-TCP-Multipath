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
        .config_file="~./mpctcp/mpctcp.config",
        .logdir="~/.mpctcp",
        .logfile="~/.mpctcp/mpctcp.log",
        .pidfile="~/.mpctcp/mpctcp.pid",
#else
        .config_file="/etc/mpctcp/mpctcp.conf",
        .logdir="/var/log/mpctcp",
        .logfile="/var/log",
        .pidfile="/var/run/mpctcp.pid",
#endif
        // SOCKS Information
        .local_ip="0.0.0.0",
        .socks_port=1080,
        .port_start=8001,
        .port_end=9999,
        .max_connections=25,
        .socks_neg_rto=5,
        
        // Proxy Information
        .remote_addr="",
        .remote_port=1080,
        
        // MPCTCP Settings
        .slr_scaling=1.0,
        .cong_control="aimd",
        
        // Debug Settings
        .debug=1,
        .mpctcp_probe=0,
        
        // Configuration File Variables
        .num_vars = 15,
        .var_name = {
            "LOG_DIR", "LOG_FILE", "PID_FILE",
            "BIND_ADDR", "SOCKS_PORT", "START_PORT",
            "END_PORT", "MAX_CONNECTIONS", "SOCKS_NEGOTIATION_RTO",
            "REMOTE_ADDR", "REMOTE_PORT", "SLR_SCALING",
            "CONGESTION_CONTROL","DEBUG","MPCTCP_PROBE"
        },
        
        .var_ptr = {
            &(proxy_cfg.logdir), &(proxy_cfg.logfile), &(proxy_cfg.pidfile),
            &(proxy_cfg.local_ip), &(proxy_cfg.socks_port), &(proxy_cfg.port_start),
            &(proxy_cfg.port_end), &(proxy_cfg.max_connections), &(proxy_cfg.socks_neg_rto),
            &(proxy_cfg.remote_addr), &(proxy_cfg.remote_port), &(proxy_cfg.slr_scaling),
            &(proxy_cfg.cong_control), &(proxy_cfg.debug), &(proxy_cfg.mpctcp_probe)
        },
        
        .var_type = {
            's', 's', 's',
            's', 'n', 'n',
            'n', 'n', 'n',
            's', 'n', 'f',
            's', 'n', 'n'
        },
    };
    return proxy_cfg;
}