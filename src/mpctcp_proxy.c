#include "mpctcp_proxy.h"
#include "net_util.h"
#include "util.h"
#include "default_config.h"
#include <string.h>

int main(int argc, char *argv[])
{

	int c;
	int force_load = FALSE;
	//proxy_config proxy_cfg = getconfig();
    
	// Parse commannd line arguements
	while ((c = getopt(argc, argv, "hvc:f")) != -1)
		switch (c) 
		{
			case 'h':  //Print help
				print_help();
				exit(EXIT_SUCCESS);
			case 'v':  //Print Version
				printf("%s version %s (%s)\n", config.program_name, config.version, config.date);
				exit(EXIT_SUCCESS);
			case 'c':  //Define config file path
                strcpy(config.config_file, optarg);
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

    if (read_config())
        exit(EXIT_FAILURE);
    
	return 0;
}