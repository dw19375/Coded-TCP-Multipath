#include "mpctcp_proxy.h"
#include "net_util.h"
#include "util.h"
#include "default_config.h"

int main(int argc, char *argv[])
{

	int c;
	int force_load = FALSE;
	proxy_config proxy_cfg = getconfig();

	// Parse commannd line arguements
	while ((c = getopt(argc, argv, "hvcf:")) != 1)
		switch (c) 
		{
			case 'h':  //Print help
				print_help(&proxy_cfg);
				exit(EXIT_SUCCESS);
			case 'v':  //Print Version
				printf("%s version %s (%s)\n", proxy_cfg.program_name, proxy_cfg.version, proxy_cfg.date);
				exit(EXIT_SUCCESS);
			case 'c':  //Define config file path
				strcpy(proxy_cfg.config_file,optarg);
				break;
			case 'f': //Force load sockets
				force_load = TRUE;
				break;
			case '?':
				if (optopt == 'c')
					fprintf(stderr, "Option -%c requires an arguement.\n", optopt);
				else
					fprintf(stderr, "Unknown option '-%c'.\n", optopt);
				exit(EXIT_FAILURE);
			default:
				exit(EXIT_FAILURE);
		}
	/* code */
	return 0;
}