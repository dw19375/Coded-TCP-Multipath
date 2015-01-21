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

/*  Make sure this compiles
 
void htonpHdr( Pckt_Header* hdr )
{
  if( NULL != hdr )
  {
    // Let's not worry about doubles, since they should be in
    // IEEE 754 standard format anyway.
    hdr->flag         = (flag_t) htonl(hdr->flag);
    hdr->seqno        = htonl(hdr->seqno);
    hdr->num_packets  = htons(hdr->num_packets);
    hdr->coeff_seed   = htons(hdr->coeff_seed);
  }  
}

void ntohpHdr( Pckt_Header* hdr )
{
  if( NULL != hdr )
  {
    // Let's not worry about doubles, since they should be in
    // IEEE 754 standard format anyway.
    hdr->flag         = (flag_t) ntohl(hdr->flag);
    hdr->seqno        = ntohl(hdr->seqno);
    hdr->num_packets  = ntohs(hdr->num_packets);
    hdr->coeff_seed   = ntohs(hdr->coeff_seed);
  }
}

void
htonpData(Data_Pckt* msg)
{
  if( NULL != msg )
  {
    htonpHdr( msg->hdr );
  }
  // Data is all in bytes, so don't need to do anything
}

void
htonpAck(Ack_Pckt* msg)
{
  if( NULL != msg )
  {
    htonpHdr( msg->hdr );
  }
}

void
ntohpData(Data_Pckt* msg)
{
  if( NULL != msg )
  {
    ntohpHdr( msg->hdr );
  }
  // Data is all in bytes, so don't need to do anything
}

void
ntohpAck(Ack_Pckt* msg)
{
  if( NULL != msg )
  {
    ntohpHdr( msg->hdr );
  }
}

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
