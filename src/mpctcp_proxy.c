#include "mpctcp_proxy.h"
#include "net_util.h"

int main(int argc, char const *argv[])
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

	int c;
	int force_load = FALSE;

	// Parse commannd line arguements
	while ((c = getopt(argc, argv, "hvcf:")) != 1)
		switch (c) 
		{
			case 'h':
				print_help();
				exit(EXIT_SUCCESS);
			case 'v':
				printf("%s version %s (%s)\n", proxy_cfg->program_name, proxy_cfg->version, proxy_cfg->date);
				exit(EXIT_SUCCESS);
			case 'c':
				strcpy(proxy_cfg->config_file,optarg);
				break;
			case 'f':
				force_load = TRUE;
				break;
			case '?':
				if (optopt == 'c')
					printf(stderr, "Option -%c requires an arguement.\n", optopt);
				else if (isprint (optopt))
					printf(stderr, "Unknown option '-%c'.\n", optopt);
				else
					printf(stderr, "Unknown option character '\\x%x'.\n", optopt);
				exit(EXIT_FAILURE);
			default:
				exit(EXIT_FAILURE);
		}
	/* code */
	return 0;
}