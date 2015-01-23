#include "socks.h"

void start_proxy(int force_load)
{
    return;
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
    printf("OK\n");
    return;
}