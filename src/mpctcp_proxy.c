#include "mpctcp_proxy.h"

int main(int argc, char *argv[])
{

	int c;
	int force_load = FALSE;
    
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
    
    if ((optind+1) > argc) {
        fprintf(stderr, "No command given. Add either 'start' or 'stop'.\n");
        exit(EXIT_FAILURE);
    }
    
    if (!strcmp(argv[optind], "start")) {
        start_proxy(force_load);
    } else if (!strcmp(argv[optind], "stop")) {
        stop_proxy();
    } else {
        fprintf(stderr, "Unknown command. Valid commands are 'start' or 'stop'");
        exit(EXIT_FAILURE);
    }
    
	exit(EXIT_SUCCESS);
}

void start_proxy(int force_load)
{
    
    FILE* pidfile;
    pid_t pid;
    struct sigaction sa;
    proxy_connections proxy_conn;
    int listen_sk;
    socklen_t sin_size;
    
    printf("Starting %s ...",config.program_name);
    fflush(stdout);
    
    if ((pidfile=fopen(config.pidfile, "r"))!=NULL && !force_load) {
        fclose(pidfile);
        fprintf(stderr, "ERROR\n \tPID file %s could not be opened (maybe %s is not running).\n",config.pidfile,config.program_name);
        exit(EXIT_FAILURE);
    }
    /*
    pid = fork();
    switch (pid) {
        case 0:
            // Child Process
            setsid();
            break;
        case -1:
            // Fork Failed
            fprintf(stderr, "ERROR\n \tfork() failed - cannont detach daemon\n");
            exit(EXIT_FAILURE);
        default:
            exit(EXIT_SUCCESS);
    }
    
    sa.sa_handler = handle_sig;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags=0;
    
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGCHLD, &sa, NULL);
    //sigaction(SIGALRM, &sa, NULL);
    */
    
    create_tcp_socket(&(proxy_conn.listen_sk), config.local_ip, config.socks_port);

    if (listen(proxy_conn.listen_sk,config.max_backlog) == -1) {
        perror("listen");
        fprintf(stderr, "Failed to setup listen on %s:%d\n",config.local_ip,config.socks_port);
        exit(EXIT_FAILURE);
    }
    
    printf("OK\n");
    fflush(stdout);
    
    //proxy_conn.client_sk = accept(proxy_conn.listen_sk, (struct sockaddr *)&(proxy_conn.client_addr), &sin_size);
}

void stop_proxy()
{
    FILE *pidfile;
    int pid;
    
    printf("Shutting down %s ...",config.program_name);
    fflush(stdout);
    
    if (!(pidfile = fopen(config.pidfile, "r"))) {
        fprintf(stderr, "ERROR\n \tPID file %s could not be opened (maybe %s is not running).\n",config.pidfile,config.program_name);
        exit(EXIT_FAILURE);
    }
    
    if (fscanf(pidfile, "%u",&pid) <= 0) {
        fprintf(stderr, "ERROR\n \tCould not read PID file %s\n",config.pidfile);
        exit(EXIT_FAILURE);
    }
    
    fclose(pidfile);
    
    if (pid <= 0) {
        fprintf(stderr, "ERROR\n \tInvalid PID");
        exit(EXIT_FAILURE);
    }
    
    if (kill(-pid,SIGTERM)) {
        fprintf(stderr, "ERROR\n \tkill() failed\n");
        exit(EXIT_FAILURE);
    }
    
    sleep(1);
    
    kill(-pid, SIGKILL);
    unlink(config.pidfile);
    printf("OK\n");
    return;
}

void handle_sig(int sig)
{
    return;
}