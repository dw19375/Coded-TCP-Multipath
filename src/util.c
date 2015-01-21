/*
 * util.c
 * 
 * Various utility functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <assert.h>
#include <math.h>
#include "net_util.h"
#include "util.h"



/*
 * Returns the current UNIX time in seconds.
 */
double
getTime(void){
  timeval_t time;
  gettimeofday(&time, NULL);
  return(time.tv_sec+ time.tv_usec*1.e-6);
}

// portable clock_gettime
int clock_gettime(int dummy, struct timespec* t) {
  struct timeval now;
  int rv = gettimeofday(&now, NULL);
  if (rv) 
    return rv;
  t->tv_sec  = now.tv_sec;
  t->tv_nsec = now.tv_usec * 1000;
  return 0;
}


