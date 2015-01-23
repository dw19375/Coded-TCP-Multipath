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
    htonpHdr( &(msg->hdr) );
  }
  // Data is all in bytes, so don't need to do anything
}

void
ntohpData(Data_Pckt* msg)
{
  if( NULL != msg )
  {
    ntohpHdr( &(msg->hdr) );
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

/*
 * pack_hdr
 * 
 * Packs header into unambiguous format to be sent across 
 * the network.  Input data is assumed to be in host byte order
 * and output data is in network byte order.
 * 
 * Parameters:
 *    buf   - Pointer to buffer to fill.
 *    hdr   - Pointer to packet header.
 *    
 * Returns number of bytes written into buf.
 */
int pack_hdr( char* buf, Pckt_Header hdr )
{
  int retval = 0;
  /*
   * Extract value of flag in case of size mismatch.  If hdr.flag
   * is too large, the LSBs will be assigned to flag.  If hdr.flag
   * is too small, it will fill the LSBs of flag.
   */
  uint32_t flag = htonl( (uint32_t)(hdr.flag) );

  if( NULL != buf )
  {
    // Convert hdr to network byte order
    htonpHdr( &hdr );
    
    // Size of double shouldn't vary at all.
    memcpy( buf, &hdr.tstamp, sizeof(double) );
    retval += sizeof(double);
    
    // Use local copy of flag.
    memcpy( buf + retval, &flag, sizeof(uint32_t) );
    retval += sizeof(uint32_t);
    
    // Copy other data, which are just ints.
    memcpy( buf + retval, &hdr.seqno , sizeof(uint32_t) );
    retval += sizeof(uint32_t);
    
    memcpy( buf + retval, &hdr.num_packets , sizeof(uint16_t) );
    retval += sizeof(uint16_t);
    
    memcpy( buf + retval, &hdr.coeff_seed , sizeof(uint16_t) );
    retval += sizeof(uint16_t);
  }
  
  return retval;
}
  

/*
 * unpack_hdr
 * 
 * Unpacks header from network format.  Data is assumed to be in
 * network byte order.
 * 
 * Parameters:
 *    buf   - Pointer to raw header data.
 *    hdr   - Pointer to packet header to fill.
 * 
 * Returns number of bytes read into buf.
 */
int unpack_hdr( char* buf, Pckt_Header* hdr )
{
  int retval = 0;
  
  if( NULL != buf && NULL != hdr )
  {
    // doubles should all be the same size.
    hdr->tstamp = *((double*)buf);
    retval += sizeof(double);
    buf += retval;
    
    hdr->flag = *((uint32_t*)buf);
    retval += sizeof(uint32_t);
    buf += retval;
    
    hdr->seqno = *((uint32_t*)buf);
    retval += sizeof(uint32_t);
    buf += retval;
    
    hdr->num_packets = *((uint16_t*)buf);
    retval += sizeof(uint16_t);
    buf += retval;
    
    hdr->coeff_seed = *((uint16_t*)buf);
    retval += sizeof(uint16_t);
    buf += retval;
    
    // Convert to host byte order
    ntohpHdr( hdr );
  }
  
  return retval;
}


