/*
 * util.h
 * 
 * Various utility functions.
 */

#ifndef UTIL_H
#define UTIL_H

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <string.h>
#include <stdint.h>

#define TRUE 1
#define FALSE 0
#define MIN(x,y) (y)^(((x) ^ (y)) &  - ((x) < (y)))
#define MAX(x,y) (y)^(((x) ^ (y)) & - ((x) > (y)))

typedef int bool;
typedef struct timeval timeval_t;

/* Function declarations */
double getTime(void);
uint8_t FFmult(uint8_t x, uint8_t y);
uint8_t xFFlog(uint8_t x);
uint8_t fastFFmult(uint8_t x, uint8_t logy);
void seedfastrand(uint32_t seed);
uint32_t fastrand();
int getRandomNumber();

#ifdef __MACH__
#include <sys/time.h>
#endif
//portable clock_gettime 
#define CLOCK_REALTIME  0 // dummy constant
int clock_gettime(int dummy, struct timespec* t);

#endif /* UTIL_H */ 
