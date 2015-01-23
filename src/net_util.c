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
 * pkt2iovec
 * 
 * Fills the elements of iov with appropriate data from pkt.
 * 
 * Parameters:
 *    pkt   - Pointer to Data_Pckt to be read from
 *    iov   - Pointer to start of struct iovec array to write to.
 * 
 * If pkt is NULL, null pointers are written into elements of iov 
 * but the lengths are written into the elements of iov.
 * 
 * The array iov must contain as many elements as there are in
 * the Data_Pckt struct.  However, if pkt->buf is NULL, iov may
 * contain one fewer element.
 * 
 * Does not change byte order.
 * 
 * Returns number of elements written.
 */
int pkt2iovec( Data_Pckt *pkt, struct iovec *iov )
{
  int idx = 0;
  
  if( NULL != iov )
  {
    /*
     * Write appropriate data lengths into iov
     */
    (iov[idx++]).iov_len = sizeof(pkt->tstamp);
    (iov[idx++]).iov_len = sizeof(pkt->flag);
    (iov[idx++]).iov_len = sizeof(pkt->seqno);
    (iov[idx++]).iov_len = sizeof(pkt->payload_len);
    (iov[idx++]).iov_len = sizeof(pkt->num_packets);
    (iov[idx++]).iov_len = sizeof(pkt->coeff_seed);
    
    idx = 0;
    
    if( NULL != pkt )
    {
      (iov[idx++]).iov_base = &(pkt->tstamp);
      (iov[idx++]).iov_base = &(pkt->flag);
      (iov[idx++]).iov_base = &(pkt->seqno);
      (iov[idx++]).iov_base = &(pkt->payload_len);
      (iov[idx++]).iov_base = &(pkt->num_packets);
      (iov[idx++]).iov_base = &(pkt->coeff_seed);
      
      if( NULL != pkt->buf )
      {
        (iov[idx]).iov_base = pkt->buf;
        (iov[idx++]).iov_len = pkt->payload_len;
      }
    }
  }
  
  return idx;
}

/*
 * iovec2pkt
 * 
 * Reads an iovec into a Data_Pckt
 * 
 * Inputs:
 *    pkt   - pointer to Data_Pckt to write into.
 *    iov   - pointer to array of iovec to read from.
 * 
 * Returns number of elements read from iov
 * 
 * The array iov must contain as many elements as the struct 
 * Data_Pckt has, however if payload_len is zero, iov may contain 
 * one fewer element.
 * 
 * Does not change byte order.
 */
int iovec2pkt( Data_Pckt *pkt, struct iovec *iov )
{
  int idx = 0;
  
  if( NULL != pkt && NULL != iov )
  {
    pkt->tstamp = *((double*)(iov[idx++].iov_base));
    pkt->flag = *((uint32_t*)(iov[idx++].iov_base));
    pkt->seqno = *((uint32_t*)(iov[idx++].iov_base));
    pkt->payload_len = *((uint32_t*)(iov[idx++].iov_base));
    pkt->num_packets = *((uint16_t*)(iov[idx++].iov_base));
    pkt->coeff_seed = *((uint16_t*)(iov[idx++].iov_base));
    
    if( pkt->payload_len > 0 )
    {
      pkt->buf = (char*)(iov[idx++].iov_base);
    }
  }
  
  return idx;
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
