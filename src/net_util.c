/*
 * net_util.c
 * 
 * Contains various network related utility functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <assert.h>
#include <math.h>
#include "net_util.h"
#include "util.h"

void
htonpData(Data_Pckt* msg)
{
  if( NULL != msg )
  {
    // Let's not worry about doubles, since they should be in
    // IEEE 754 standard format anyway.
    msg->flag         = htonl(msg->flag);
    msg->seqno        = htonl(msg->seqno);
    msg->num_packets  = htons(msg->num_packets);
    msg->coeff_seed   = htons(msg->coeff_seed);
  }
  // Data is all in bytes, so don't need to do anything
}

void
ntohpData(Data_Pckt* msg)
{
  if( NULL != msg )
  {
    // Let's not worry about doubles, since they should be in
    // IEEE 754 standard format anyway.
    msg->flag         = ntohl(msg->flag);
    msg->seqno        = ntohl(msg->seqno);
    msg->num_packets  = ntohs(msg->num_packets);
    msg->coeff_seed   = ntohs(msg->coeff_seed);
  }
  // Data is all in bytes, so don't need to do anything
}

/* 
 * Old Code from Coded-TCP
 */
/*
void
prettyPrint(char** coeffs, int window){
  int i,j;
  printf("\n\n**Matrix**\n");
  for(i = 0; i < BLOCK_SIZE; i++)
  {
    for(j = 0; j < BLOCK_SIZE; j++)
    {
      if(j < i || j >= i + window)
      {
        printf("0 ");
      }
      else
      {
        printf("%d ", (uint8_t) coeffs[i][j-i]);
      }
    }
    printf("\n");
  }
}
*/
