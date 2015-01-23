#ifndef SOCKS_H
#define SOCKS_H 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "default_config.h"

void start_proxy(int);
void stop_proxy();

#endif